/**
 \file
 \brief demuxer manager
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author
 \date 2010-02-10
 */

#define LOG_TAG "SVR_EXTRATOR"
#include <utils/Log.h>
//#include <cutils/properties.h>
#include "hi_svr_format.h"
#include "svr_extrator_intf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/************************ Structure Definition **************************/
typedef struct tagDEMUXER_MEMBER_S
{
    HI_HANDLE hExtractor;
    HI_CHAR uri[MAX_URI_NAME_LEN];
    HI_CHAR *aszHeaders;
    HI_FORMAT_BUFFER_CONFIG_S stBufConfig;
    HI_S64 s64BufferMaxSize;
} DEMUXER_MEMBER_S;

/* demuxer, url function */
static HI_S32 SVR_DEMUXER_Find(const HI_CHAR * pszFileName, const HI_FORMAT_PROTOCOL_FUN_S *pstProtocol);
static HI_S32 SVR_DEMUXER_Open(const HI_CHAR *pszFileName, const HI_FORMAT_PROTOCOL_FUN_S *pstProtocol, HI_HANDLE *pFmtHandle);
static HI_S32 SVR_DEMUXER_FindStream(HI_HANDLE handle, HI_VOID *pArg);
static HI_S32 SVR_DEMUXER_GetInfo(HI_HANDLE fmtHandle, HI_FORMAT_FILE_INFO_S **ppstFmtInfo);
static HI_S32 SVR_DEMUXER_Read(HI_HANDLE fmtHandle, HI_FORMAT_FRAME_S *pstFmtFrame);
static HI_S32 SVR_DEMUXER_Free(HI_HANDLE fmtHandle, HI_FORMAT_FRAME_S *pstFmtFrame);
static HI_S32 SVR_DEMUXER_Invoke(HI_HANDLE fmtHandle, HI_U32 u32InvokeId, HI_VOID *pArg);
static HI_S32 SVR_DEMUXER_Close(HI_HANDLE fmtHandle);
static HI_S32 SVR_DEMUXER_SeekPts(HI_HANDLE fmtHandle, HI_S32 s32StreamIndex, HI_S64 s64Pts, HI_FORMAT_SEEK_FLAG_E eFlag);
static HI_S64 SVR_DEMUXER_SeekPos(HI_HANDLE fmtHandle, HI_S64 s64Pos, HI_S32 s32Whence);
static HI_S32 SVR_URL_Find(const HI_CHAR *pszUrl);

/** demuxer object */
HI_FORMAT_S g_stFormat_entry = {
    .pszDllName                  = (const HI_PCHAR )"libandroid_extrator.so",
    .pszFormatName               = "mp4,asf",
    .pszProtocolName             = "http",
    .stLibVersion                = {1, 0, 0, 1},
    .pszFmtDesc                  = (const HI_PCHAR)"hisilicon demuxer",
    .u32Merit                    = 0,
    .stDemuxerFun.fmt_find       = SVR_DEMUXER_Find, /*lint !e651*/
    .stDemuxerFun.fmt_open       = SVR_DEMUXER_Open,
    .stDemuxerFun.fmt_getinfo    = SVR_DEMUXER_GetInfo,
    .stDemuxerFun.fmt_find_stream= SVR_DEMUXER_FindStream,
    .stDemuxerFun.fmt_read       = SVR_DEMUXER_Read,
    .stDemuxerFun.fmt_free       = SVR_DEMUXER_Free,
    .stDemuxerFun.fmt_invoke     = SVR_DEMUXER_Invoke,
    .stDemuxerFun.fmt_close      = SVR_DEMUXER_Close,
    .stDemuxerFun.fmt_seek_pts   = SVR_DEMUXER_SeekPts,
    .stDemuxerFun.fmt_seek_pos   = SVR_DEMUXER_SeekPos,

    .stProtocolFun.url_find      = SVR_URL_Find,
    .stProtocolFun.url_open      = NULL,
    .stProtocolFun.url_read      = NULL,
    .stProtocolFun.url_seek      = NULL,
    .stProtocolFun.url_close     = NULL,
    .stProtocolFun.url_read_seek = NULL,
    .stProtocolFun.url_invoke    = NULL,

    .next           = NULL,
    .pDllModule     = NULL,
    .u32PrivateData = 0
};

/************************ Macro Definition **************************/
#define  SVR_NULL_STR ""
#define  SVR_PRINTF   ALOGE
#define  SAMPLE_PRINTF ALOGE
/************************ Api Definition ****************************/

HI_S32 dumpFileInfo(HI_FORMAT_FILE_INFO_S *pstFileInfo)
{
    HI_U32 i = 0, j = 0;

    SAMPLE_PRINTF("*************************************************\n");
    if (HI_FORMAT_STREAM_TS == pstFileInfo->eStreamType)
        SAMPLE_PRINTF("Stream type: %s \n", "TS");
    else
        SAMPLE_PRINTF("Stream type: %s \n", "ES");

    if (HI_FORMAT_SOURCE_LOCAL == pstFileInfo->eSourceType)
        SAMPLE_PRINTF("Source type: %s \n", "LOCAL");
    else if (HI_FORMAT_SOURCE_NET_VOD == pstFileInfo->eSourceType)
        SAMPLE_PRINTF("Source type: %s \n", "VOD");
    else if (HI_FORMAT_SOURCE_NET_LIVE == pstFileInfo->eSourceType)
        SAMPLE_PRINTF("Source type: %s \n", "LIVE");

    SAMPLE_PRINTF("File size:   %lld bytes \n", pstFileInfo->s64FileSize);
    SAMPLE_PRINTF("Start time:  %lld:%lld:%lld \n",
        pstFileInfo->s64StartTime / (1000 * 3600),
        (pstFileInfo->s64StartTime % (1000 * 3600)) / (1000 * 60),
        ((pstFileInfo->s64StartTime % (1000 * 3600)) % (1000 * 60)) / 1000);
    SAMPLE_PRINTF("Duration:    %lld:%lld:%lld \n",
        pstFileInfo->s64Duration / (1000 * 3600),
        (pstFileInfo->s64Duration % (1000 * 3600)) / (1000 * 60),
        ((pstFileInfo->s64Duration % (1000 * 3600)) % (1000 * 60)) / 1000);
    SAMPLE_PRINTF("bps:         %d bits/s \n", pstFileInfo->u32Bitrate);

    for (i = 0; i < (int)pstFileInfo->u32ProgramNum; i++)
    {
        SAMPLE_PRINTF("Program %d: \n", i);

        for (j = 0; j < pstFileInfo->pastProgramInfo[i].u32VidStreamNum; j++)
        {
            SAMPLE_PRINTF("   video %d info: \n", j);
            SAMPLE_PRINTF("     stream idx:   %d \n", pstFileInfo->pastProgramInfo[i].pastVidStream[j].s32StreamIndex);
            SAMPLE_PRINTF("     format:       %d \n", pstFileInfo->pastProgramInfo[i].pastVidStream[j].u32Format);
            SAMPLE_PRINTF("     w * h:        %d * %d \n",
                pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16Width,
                pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16Height);
            SAMPLE_PRINTF("     fps:          %d.%d \n",
                pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16FpsInteger,
                pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16FpsDecimal);
            SAMPLE_PRINTF("     bps:          %d bits/s \n", pstFileInfo->pastProgramInfo[i].pastVidStream[j].u32Bitrate);
            SAMPLE_PRINTF("     duration:     %lld:%lld:%lld \n",
                pstFileInfo->pastProgramInfo[i].pastVidStream[j].s64Duration / (1000 * 3600),
                (pstFileInfo->pastProgramInfo[i].pastVidStream[j].s64Duration  % (1000 * 3600)) / (1000 * 60),
                ((pstFileInfo->pastProgramInfo[i].pastVidStream[j].s64Duration  % (1000 * 3600)) % (1000 * 60)) / 1000);
        }

        for (j = 0; j < (int)pstFileInfo->pastProgramInfo[i].u32AudStreamNum; j++)
        {
            SAMPLE_PRINTF("   audio %d info: \n", j);
            SAMPLE_PRINTF("     stream idx:   %d \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].s32StreamIndex);
            SAMPLE_PRINTF("     format:       %d \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u32Format);
            SAMPLE_PRINTF("     samplerate:   %d Hz \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u32SampleRate);
            SAMPLE_PRINTF("     bitpersample: %d \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u16BitPerSample);
            SAMPLE_PRINTF("     channels:     %d \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u16Channels);
            SAMPLE_PRINTF("     bps:          %d bits/s \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u16BitPerSample);
            SAMPLE_PRINTF("     lang:         %s \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].aszLanguage);
            SAMPLE_PRINTF("     subID:        %d \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].s32SubStreamID);
            SAMPLE_PRINTF("     duration:     %lld:%lld:%lld \n",
                pstFileInfo->pastProgramInfo[i].pastAudStream[j].s64Duration / (1000 * 3600),
                (pstFileInfo->pastProgramInfo[i].pastAudStream[j].s64Duration  % (1000 * 3600)) / (1000 * 60),
                ((pstFileInfo->pastProgramInfo[i].pastAudStream[j].s64Duration  % (1000 * 3600)) % (1000 * 60)) / 1000);
        }

        for (j = 0; j < (int)pstFileInfo->pastProgramInfo[i].u32SubStreamNum; j++)
        {
            SAMPLE_PRINTF("   subtitle %d info: \n", j);
            SAMPLE_PRINTF("     stream idx:   %d \n", pstFileInfo->pastProgramInfo[i].pastSubStream[j].s32StreamIndex);
            SAMPLE_PRINTF("     format:       %d \n", pstFileInfo->pastProgramInfo[i].pastSubStream[j].u32Format);
            SAMPLE_PRINTF("     lang:         %s \n", (char*)(pstFileInfo->pastProgramInfo[i].pastSubStream[j].paszLanguage));
            SAMPLE_PRINTF("     be ext sub:   %d \n", pstFileInfo->pastProgramInfo[i].pastSubStream[j].bExtSub);
            SAMPLE_PRINTF("     sub u16OriginalFrameHeight: %d \n", pstFileInfo->pastProgramInfo[i].pastSubStream[j].u16OriginalFrameHeight);
            SAMPLE_PRINTF("     sub u16OriginalFrameWidth:  %d \n", pstFileInfo->pastProgramInfo[i].pastSubStream[j].u16OriginalFrameWidth);

        }
    }
    SAMPLE_PRINTF("*************************************************\n");

    return HI_SUCCESS;
}

static HI_S32 SVR_DEMUXER_Find(const HI_CHAR *pszFileName, const HI_FORMAT_PROTOCOL_FUN_S *pstProtocol)
{
    HI_BOOL bUseThisDMX = HI_FALSE;
    HI_S32 len = strlen(pszFileName);

    /*check format for the extractor,if not SS ASF playready or widevine,exit*/

    if (len>=4 && (strstr(pszFileName, ".pyv")
                 || strstr(pszFileName, ".pya")))
    {
        SVR_PRINTF("this is playready");
        bUseThisDMX = HI_TRUE;
    }
    else if (len >= 9 && !strcasecmp("/Manifest", &pszFileName[len - 9]))
    {
        SVR_PRINTF("this is smooth streaming");
        bUseThisDMX = HI_TRUE;
    }
    else if (len >= 11 && !strncasecmp("widevine://", pszFileName, 11))
    {
        SVR_PRINTF("this is widevine");
        bUseThisDMX = HI_TRUE;
    }
    else if (strstr(pszFileName, ".wvm"))
    {
        SVR_PRINTF("this is widevine");
        bUseThisDMX = HI_TRUE;
    }

    if (bUseThisDMX == HI_FALSE)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 SVR_DEMUXER_Open(const HI_CHAR *pszFileName, const HI_FORMAT_PROTOCOL_FUN_S *pstProtocol, HI_HANDLE *pFmtHandle)
{
    HI_S32 s32Ret = HI_FAILURE;
    DEMUXER_MEMBER_S *phandle = NULL;

    if (NULL == pszFileName || NULL == pFmtHandle)
        return HI_FAILURE;

    phandle = (DEMUXER_MEMBER_S*)malloc(sizeof(DEMUXER_MEMBER_S));

    if (NULL != phandle)
    {
        memset(phandle, 0, sizeof(DEMUXER_MEMBER_S));
    }
    else
    {
        SVR_PRINTF("[%s:%d] malloc member fail ", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    if (strlen(pszFileName) < MAX_URI_NAME_LEN)
    {
        memcpy(phandle->uri, pszFileName, strlen(pszFileName));
    }
    else
    {
        goto err;
    }

    *pFmtHandle = (HI_U32)phandle;

    return HI_SUCCESS;
err:
    if (NULL != phandle)
    {
        free(phandle);
        phandle = NULL;
    }

    return HI_FAILURE;
}

static HI_S32 SVR_DEMUXER_FindStream(HI_HANDLE fmtHandle, HI_VOID *pArg)
{
    HI_S32 s32Ret = HI_FAILURE;
    DEMUXER_MEMBER_S *pstDemuxer = (DEMUXER_MEMBER_S*)fmtHandle;
    HI_HANDLE extractor;
    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;

    if (NULL == pstDemuxer)
        return HI_FAILURE;

    s32Ret = SVR_EXTRACTOR_Create(&extractor);

    if (HI_SUCCESS != s32Ret)
    {
        SVR_PRINTF("[%s:%d] extractor create fail ", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    (void)SVR_EXTRACTOR_Invoke(extractor, HI_FORMAT_INVOKE_SET_BUFFER_CONFIG, (void *)&pstDemuxer->stBufConfig);
    (void)SVR_EXTRACTOR_Invoke(extractor, HI_FORMAT_INVOKE_SET_BUFFER_MAX_SIZE, (void *)&pstDemuxer->s64BufferMaxSize);
    SVR_PRINTF("[%s:%d] SVR_EXTRACTOR_SetDataSource with  aszHeaders:%s", __FUNCTION__, __LINE__, pstDemuxer->aszHeaders);
    s32Ret = SVR_EXTRACTOR_SetDataSource(extractor, pstDemuxer->uri, pstDemuxer->aszHeaders, pArg);

    if (HI_SUCCESS != s32Ret)
    {
        SVR_PRINTF("[%s:%d] set data source fail ", __FUNCTION__, __LINE__);
        goto err;
    }

    s32Ret = SVR_EXTRACTOR_GetFileInfo(extractor, &pstFileInfo);

    if (HI_SUCCESS != s32Ret)
    {
        SVR_PRINTF("[%s:%d] get file info fail ", __FUNCTION__, __LINE__);
        goto err;
    }

    dumpFileInfo(pstFileInfo);

    pstDemuxer->hExtractor = extractor;

    return HI_SUCCESS;

err:
    SVR_EXTRACTOR_Delete(extractor);

    return HI_FAILURE;
}

static HI_S32 SVR_DEMUXER_GetInfo(HI_HANDLE fmtHandle, HI_FORMAT_FILE_INFO_S **ppstFmtInfo)
{
    HI_S32 s32Ret = HI_FAILURE;
    DEMUXER_MEMBER_S *pstDemuxer = (DEMUXER_MEMBER_S*)fmtHandle;
    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;

    if (NULL == pstDemuxer)
        return HI_FAILURE;

    s32Ret = SVR_EXTRACTOR_GetFileInfo(pstDemuxer->hExtractor, &pstFileInfo);

    if (HI_SUCCESS != s32Ret)
    {
        //SVR_PRINTF("[%s:%d] get file info fail ", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    *ppstFmtInfo = pstFileInfo;

    return HI_SUCCESS;
}

static HI_S32 SVR_DEMUXER_Read(HI_HANDLE fmtHandle, HI_FORMAT_FRAME_S *pstFmtFrame)
{
    HI_S32 s32Ret = HI_FAILURE;
    DEMUXER_MEMBER_S *pstDemuxer = (DEMUXER_MEMBER_S*)fmtHandle;

    if (NULL == pstDemuxer)
        return HI_FAILURE;

    s32Ret = SVR_EXTRACTOR_ReadFrame(pstDemuxer->hExtractor, pstFmtFrame);

    return s32Ret;
}

static HI_S32 SVR_DEMUXER_Free(HI_HANDLE fmtHandle, HI_FORMAT_FRAME_S *pstFmtFrame)
{
    HI_S32 s32Ret = HI_FAILURE;
    DEMUXER_MEMBER_S *pstDemuxer = (DEMUXER_MEMBER_S*)fmtHandle;

    if (NULL == pstDemuxer)
        return HI_FAILURE;

    s32Ret = SVR_EXTRACTOR_Free(pstDemuxer->hExtractor, pstFmtFrame);

    return s32Ret;
}

static HI_S32 SVR_DEMUXER_Invoke(HI_HANDLE fmtHandle, HI_U32 u32InvokeId, HI_VOID *pArg)
{
    HI_S32 s32Ret = HI_FAILURE;
    DEMUXER_MEMBER_S *pstDemuxer = (DEMUXER_MEMBER_S*)fmtHandle;

    if (NULL == pstDemuxer)
        return HI_FAILURE;

    if (HI_FORMAT_INVOKE_SET_COOKIE == u32InvokeId)
    {
        if (NULL == pArg)
        {
            return HI_FAILURE;
        }
        SVR_PRINTF("Set cookie data = 0x%x", pArg);
        pstDemuxer->aszHeaders = (HI_CHAR*)(*((HI_U32 *) pArg));
        SVR_PRINTF("pstDemuxer->aszHeaders: %s", pstDemuxer->aszHeaders);
        return HI_SUCCESS;
    }
    else if (HI_FORMAT_INVOKE_SET_BUFFER_CONFIG == u32InvokeId)
    {
        if (NULL == pArg)
        {
            return HI_FAILURE;
        }
        //for the para check has being down in hiplayer,this place use the value directly
        memcpy(&pstDemuxer->stBufConfig, pArg, sizeof(HI_FORMAT_BUFFER_CONFIG_S));
    }
    else if (HI_FORMAT_INVOKE_SET_BUFFER_MAX_SIZE == u32InvokeId)
    {
        if (NULL == pArg)
        {
            return HI_FAILURE;
        }
        pstDemuxer->s64BufferMaxSize = *(HI_S64*)pArg;
    }

    s32Ret = SVR_EXTRACTOR_Invoke(pstDemuxer->hExtractor, u32InvokeId, pArg);

    return s32Ret;
}

static HI_S32 SVR_DEMUXER_SeekPts(HI_HANDLE fmtHandle, HI_S32 s32StreamIndex, HI_S64 s64Pts, HI_FORMAT_SEEK_FLAG_E eFlag)
{
    HI_S32 s32Ret = HI_FAILURE;
    DEMUXER_MEMBER_S *pstDemuxer = (DEMUXER_MEMBER_S*)fmtHandle;

    if (NULL == pstDemuxer)
        return HI_FAILURE;

    s32Ret = SVR_EXTRACTOR_Seek(pstDemuxer->hExtractor, s64Pts);

    return s32Ret;
}

static HI_S64 SVR_DEMUXER_SeekPos(HI_HANDLE fmtHandle, HI_S64 s64Pos, HI_S32 s32Whence)
{
    DEMUXER_MEMBER_S *pstDemuxer = (DEMUXER_MEMBER_S*)fmtHandle;

    return HI_SUCCESS;
}

static HI_S32 SVR_DEMUXER_Close(HI_HANDLE fmtHandle)
{
    HI_S32 s32Ret = HI_FAILURE;
    DEMUXER_MEMBER_S *pstDemuxer = (DEMUXER_MEMBER_S*)fmtHandle;

    if (NULL == pstDemuxer)
        return HI_FAILURE;

    SVR_EXTRACTOR_Delete(pstDemuxer->hExtractor);
    free(pstDemuxer);
    pstDemuxer = NULL;

    return HI_SUCCESS;
}

static HI_S32 SVR_URL_Find(const HI_CHAR *pszUrl)
{
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
