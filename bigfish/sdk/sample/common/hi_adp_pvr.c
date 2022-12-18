/**
\file
\brief common function of PVR
\copyright Shenzhen Hisilicon Co., Ltd.
\version draft
\author QuYaxin 46153
\date 2010-3-26
*/

#include "hi_adp.h"
#include "hi_adp_pvr.h"
#include "hi_adp_mpi.h"
#include "hi_adp_demux.h"

//#define PVR_ADVCA_MODE /*if use ADVCA mode,define PVR_ADVCA_MODE*/
/***************************** Macro Definition ******************************/



/*************************** Structure Definition ****************************/
typedef struct hiTS_SEND_ARGS_S
{
    HI_U32 u32DmxId;
    HI_U32 u32PortId;
    FILE   *pTsFile;
} TS_SEND_ARGS_S;

typedef struct tagPVREventType
{
    HI_U8 szEventTypeName[128];
    HI_UNF_PVR_EVENT_E eEventID;
}PVR_EVENT_TYPE_ST;

typedef struct hiCODEC_VIDEO_CMD_S
{
    HI_U32      u32CmdID;   /**<Commond ID*/ /**<CNcomment: 命令ID*/
    HI_VOID     *pPara;     /**<Control parameter*/ /**<CNcomment: 命令携带参数*/
}HI_CODEC_VIDEO_CMD_S;

/********************** Global Variable declaration **************************/
HI_BOOL             g_bIsRecStop = HI_FALSE;
static HI_BOOL      g_bStopTsThread = HI_FALSE;
HI_HANDLE           g_hTsBufForPlayBack;


static PVR_EVENT_TYPE_ST g_stEventType[] = {
    {"HI_UNF_PVR_EVENT_PLAY_EOF",       HI_UNF_PVR_EVENT_PLAY_EOF},
    {"HI_UNF_PVR_EVENT_PLAY_SOF",       HI_UNF_PVR_EVENT_PLAY_SOF},
    {"HI_UNF_PVR_EVENT_PLAY_ERROR",     HI_UNF_PVR_EVENT_PLAY_ERROR},
    {"HI_UNF_PVR_EVENT_PLAY_REACH_REC", HI_UNF_PVR_EVENT_PLAY_REACH_REC},
    {"HI_UNF_PVR_EVENT_PLAY_RESV",      HI_UNF_PVR_EVENT_PLAY_RESV},
    {"HI_UNF_PVR_EVENT_REC_DISKFULL",   HI_UNF_PVR_EVENT_REC_DISKFULL},
    {"HI_UNF_PVR_EVENT_REC_ERROR",      HI_UNF_PVR_EVENT_REC_ERROR},
    {"HI_UNF_PVR_EVENT_REC_OVER_FIX",   HI_UNF_PVR_EVENT_REC_OVER_FIX},
    {"HI_UNF_PVR_EVENT_REC_REACH_PLAY", HI_UNF_PVR_EVENT_REC_REACH_PLAY},
    {"HI_UNF_PVR_EVENT_REC_DISK_SLOW",  HI_UNF_PVR_EVENT_REC_DISK_SLOW},
    {"HI_UNF_PVR_EVENT_REC_RESV",       HI_UNF_PVR_EVENT_REC_RESV},
    {"HI_UNF_PVR_EVENT_BUTT",           HI_UNF_PVR_EVENT_BUTT}
};

HI_U8* PVR_GetEventTypeStringByID(HI_UNF_PVR_EVENT_E eEventID);

/******************************* API declaration *****************************/
#if 1
HI_VOID SearchFileTsSendThread(HI_VOID *args)
{
    HI_U32 u32Readlen;
    HI_S32 Ret;
    HI_HANDLE       hTsBuf;
    TS_SEND_ARGS_S  *pstPara = args;
    HI_UNF_STREAM_BUF_S stStreamBuf;

    Ret = HI_UNF_DMX_AttachTSPort(pstPara->u32DmxId, pstPara->u32PortId);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call VoInit failed.\n");
        return;
    }

    Ret = HI_UNF_DMX_CreateTSBuffer(pstPara->u32PortId, 0x200000, &hTsBuf);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_DMX_CreateTSBuffer failed.\n");
        return;
    }

    while (!g_bStopTsThread)
    {
        Ret = HI_UNF_DMX_GetTSBuffer(hTsBuf, 188*50, &stStreamBuf, 0);
        if (Ret != HI_SUCCESS )
        {
            usleep(10 * 1000) ;
            continue;
        }

        u32Readlen = fread(stStreamBuf.pu8Data, sizeof(HI_S8), 188*50, pstPara->pTsFile);
        if(u32Readlen <= 0)
        {
            sample_common_printf("read ts file error!\n");
            rewind(pstPara->pTsFile);
            continue;
        }

        Ret = HI_UNF_DMX_PutTSBuffer(hTsBuf, u32Readlen);
        if (Ret != HI_SUCCESS )
        {
            sample_common_printf("call HI_UNF_DMX_PutTSBuffer failed.\n");
        }
    }

    Ret = HI_UNF_DMX_DestroyTSBuffer(hTsBuf);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_DMX_DestroyTSBuffer failed.\n");
    }
    HI_UNF_DMX_DetachTSPort(pstPara->u32DmxId);

    return;
}

HI_S32 PVR_SearchFile(HI_U32 u32DmxId, HI_U32 u32PortId, const HI_CHAR *pszFileName, PMT_COMPACT_TBL **ppProgTbl)
{
    HI_S32 Ret;
    pthread_t TsThd;
    TS_SEND_ARGS_S stPara;
    FILE *pTsFile;

    pTsFile = fopen(pszFileName, "rb");

    stPara.u32DmxId = u32DmxId;
    stPara.u32PortId = u32PortId;
    stPara.pTsFile = (FILE *)pTsFile;

    g_bStopTsThread = HI_FALSE;
    pthread_create(&TsThd, HI_NULL, (HI_VOID *)SearchFileTsSendThread, &stPara);


    sleep(1);

    HIADP_Search_Init();
    Ret = HIADP_Search_GetAllPmt(u32DmxId, ppProgTbl);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HIADP_Search_GetAllPmt failed.\n");
    }
    HIADP_Search_DeInit();

    g_bStopTsThread =HI_TRUE;
    pthread_join(TsThd, HI_NULL);
    fclose(pTsFile);

    return Ret;
}

#endif

HI_S32 PVR_SavePorgInfo(PVR_PROG_INFO_S *pstProgInfo, HI_CHAR *pszPvrRecFile)
{
    HI_S32 ret;
    PVR_PROG_INFO_S stUserData;

    SAMPLE_CheckNullPTR(pstProgInfo);

    memcpy(&stUserData, pstProgInfo, sizeof(PVR_PROG_INFO_S));
    stUserData.u32MagicNumber = PVR_PROG_INFO_MAGIC;

    ret = HI_UNF_PVR_SetUsrDataInfoByFileName(pszPvrRecFile, (HI_U8*)&stUserData, sizeof(PVR_PROG_INFO_S));
    if (HI_SUCCESS != ret)
    {
        sample_common_printf("PVR_SetUsrDataInfoByFileName ERR:%#x.\n", ret);
        return ret;
    }

    usleep(10*1000);
    sample_common_printf("\n------------------\n");
    sample_common_printf("File Info:\n");
    sample_common_printf("Pid:  A=%d/%#x, V=%d/%#x.\n",pstProgInfo->AElementPid,
                                         pstProgInfo->AElementPid,
                                         pstProgInfo->VElementPid,
                                         pstProgInfo->VElementPid);
    sample_common_printf("Type: A=%d, V=%d.\n", pstProgInfo->AudioType, pstProgInfo->VideoType);
    sample_common_printf("isClearStream: %d, isEncrypt: %d.\n", pstProgInfo->stRecAttr.bIsClearStream, pstProgInfo->stRecAttr.stEncryptCfg.bDoCipher);
    sample_common_printf("indexType: %d, bRewind: %d. u64MaxSize: 0x%llx\n", pstProgInfo->stRecAttr.enIndexType, pstProgInfo->stRecAttr.bRewind, pstProgInfo->stRecAttr.u64MaxFileSize);
    sample_common_printf("------------------\n\n");
    usleep(10*1000);


    return HI_SUCCESS;
}

HI_S32 PVR_GetPorgInfo(PVR_PROG_INFO_S *pstProgInfo, const HI_CHAR *pszPvrRecFile)
{
    HI_S32 ret;
    HI_U32 u32DataRead;
    PVR_PROG_INFO_S stUserData;

    SAMPLE_CheckNullPTR(pstProgInfo);
    SAMPLE_CheckNullPTR(pszPvrRecFile);

    ret = HI_UNF_PVR_GetUsrDataInfoByFileName(pszPvrRecFile, (HI_U8*)&stUserData,
                                sizeof(PVR_PROG_INFO_S), &u32DataRead);
    if (HI_SUCCESS != ret)
    {
        sample_common_printf("PVR_SetUsrDataInfoByFileName ERR:%#x.\n", ret);
        return ret;
    }

    if (PVR_PROG_INFO_MAGIC == stUserData.u32MagicNumber)
    {
        memcpy(pstProgInfo, &(stUserData),  sizeof(PVR_PROG_INFO_S));
    }
    else
    {
        //HI_U32 temp1 = 0;
        sample_common_printf("Can  only play the program record by sample. \n");

        return HI_FAILURE;

    }

    usleep(10*1000);
    sample_common_printf("\n------------------\n");
    sample_common_printf("File Info:\n");
    if (pstProgInfo->AElementNum > 0)
    {
        sample_common_printf("Audio:\n");
        sample_common_printf("   PID = %#x\n",pstProgInfo->AElementPid);
        sample_common_printf("   Type= %d\n", pstProgInfo->AudioType);
    }
    else
    {
        sample_common_printf("Audio: none\n");
    }
    if (pstProgInfo->VElementNum > 0)
    {
        sample_common_printf("Video:\n");
        sample_common_printf("   PID = %#x\n",pstProgInfo->VElementPid);
        sample_common_printf("   Type= %d\n", pstProgInfo->VideoType);
    }
    else
    {
        sample_common_printf("Video: none\n\n");
    }

    sample_common_printf("isClearStream: %d, isEncrypt: %d.\n", pstProgInfo->stRecAttr.bIsClearStream, pstProgInfo->stRecAttr.stEncryptCfg.bDoCipher);
    sample_common_printf("indexType: %d, bRewind: %d. u64MaxSize: 0x%llx\n", pstProgInfo->stRecAttr.enIndexType, pstProgInfo->stRecAttr.bRewind, pstProgInfo->stRecAttr.u64MaxFileSize);
    sample_common_printf("------------------\n");
    usleep(10*1000);

    return HI_SUCCESS;
}

HI_S32 PVR_checkIdx(char *pfileName)
{
    HI_S32 ret = 0;
    HI_S32 s32Pos;
    HI_S32 s32ReadNum;
    HI_S32 s32FileTsFd;
    PVR_IDX_HEADER_INFO_S stHeadInfo = {0};
    FILE *fpIndex;

    char indexName[256];
    snprintf(indexName, sizeof(indexName), "%s.idx", pfileName);

    fpIndex = fopen(indexName, "rb");
    if (NULL == fpIndex)
    {
        sample_common_printf("can't open file %s to read!\n", indexName);
        return 2;
    }

    s32FileTsFd = open(pfileName, O_RDONLY);
    if (s32FileTsFd == -1)
    {
        sample_common_printf("can't open ts file %s to read!\n", indexName);
        fclose(fpIndex);
        return 2;
    }
    fseek(fpIndex, 0, SEEK_END);
    s32Pos = ftell(fpIndex);
    rewind(fpIndex);

    s32ReadNum = fread(&stHeadInfo, 1, sizeof(PVR_IDX_HEADER_INFO_S), fpIndex);
    if (s32ReadNum != sizeof(PVR_IDX_HEADER_INFO_S))
    {
            perror("read failed:");
            sample_common_printf("read head failed: want%d, get:%d\n", sizeof(PVR_IDX_HEADER_INFO_S), s32ReadNum);
            return 3;
    }
    else
    {
        if (stHeadInfo.u32StartCode == 0x5A5A5A5A)
        {
            sample_common_printf("This index file has head info: head size=%u, fileSize=%llu\n", stHeadInfo.u32HeaderLen, stHeadInfo.u64ValidSize);
            sample_common_printf("IndexEntrySize: %d, index file size:%d, headifo len:%d\n",
                     sizeof(PVR_INDEX_ENTRY_S), s32Pos, stHeadInfo.u32HeaderLen);
            fseek(fpIndex, stHeadInfo.u32HeaderLen, SEEK_SET);
        }
        else
        {
            sample_common_printf("This index file has NO head info\n");
            return 3;
        }
    }
    sample_common_printf("\nframe info:\n");
    sample_common_printf("====frame start:%d\n", stHeadInfo.stCycInfo.u32StartFrame);
    sample_common_printf("====frame end:  %d\n", stHeadInfo.stCycInfo.u32EndFrame);
    sample_common_printf("====frame last: %d\n", stHeadInfo.stCycInfo.u32LastFrame);

    close(s32FileTsFd);
    fclose(fpIndex);
    if (ret)
    {
        sample_common_printf("\n------------End of file. index check failed, err:%d-------\n", ret);
    }
    else
    {
        sample_common_printf("\n------------End of file. index check ok-------\n");
    }
    return ret;
}

HI_S32 PVR_RecStart(char *path, PMT_COMPACT_PROG *pstProgInfo, HI_U32 u32DemuxID,
                    HI_BOOL bRewind, HI_BOOL bDoCipher, HI_U64 u64MaxSize, HI_U32 *pu32RecChn)
{
    HI_U32 u32RecChn;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32VidPid = 0;
    HI_U32 u32AudPid = 0;
    HI_UNF_PVR_REC_ATTR_S stRecAttr;
    PVR_PROG_INFO_S       stFileInfo;
    HI_CHAR               szFileName[PVR_MAX_FILENAME_LEN];

    stRecAttr.u32DemuxID    = u32DemuxID;

    if (pstProgInfo->AElementNum > 0)
    {
        u32AudPid = pstProgInfo->AElementPid;
    }

    if (pstProgInfo->VElementNum > 0)
    {
        u32VidPid = pstProgInfo->VElementPid;
        stRecAttr.u32IndexPid   = u32VidPid;
        stRecAttr.enIndexType   = HI_UNF_PVR_REC_INDEX_TYPE_VIDEO;
        stRecAttr.enIndexVidType = pstProgInfo->VideoType;
    }
    else
    {
        stRecAttr.u32IndexPid   = u32AudPid;
        stRecAttr.enIndexType   = HI_UNF_PVR_REC_INDEX_TYPE_AUDIO;
        stRecAttr.enIndexVidType = HI_UNF_VCODEC_TYPE_BUTT;
    }

    snprintf(szFileName, sizeof(szFileName), "rec_v%d_a%d.ts",
                        pstProgInfo->VElementPid,
                        pstProgInfo->AElementPid);

    snprintf(stRecAttr.szFileName, sizeof(stRecAttr.szFileName), "%s/", path);

    strncat(stRecAttr.szFileName, szFileName, sizeof(szFileName) - strlen(stRecAttr.szFileName));

    stRecAttr.u32FileNameLen = strlen(stRecAttr.szFileName);
    stRecAttr.u32ScdBufSize = PVR_STUB_SC_BUF_SZIE;
    stRecAttr.u32DavBufSize = PVR_STUB_TSDATA_SIZE;
    stRecAttr.enStreamType  = HI_UNF_PVR_STREAM_TYPE_TS;
    stRecAttr.bRewind = bRewind;
    stRecAttr.u64MaxFileSize= u64MaxSize;//source;
    stRecAttr.u64MaxTimeInMs= 0;
    stRecAttr.bIsClearStream = HI_TRUE;
    stRecAttr.u32UsrDataInfoSize = sizeof(PVR_PROG_INFO_S) + 100;/*the one in index file is a multipleit of 40 bytes*//*CNcomment:索引文件里是40个字节对齐的*/

    stRecAttr.stEncryptCfg.bDoCipher = bDoCipher;
    stRecAttr.stEncryptCfg.enType = HI_UNF_CIPHER_ALG_AES;
    stRecAttr.stEncryptCfg.u32KeyLen = 16;          /*strlen(PVR_CIPHER_KEY)*/
    SAMPLE_RUN(HI_UNF_PVR_RecCreateChn(&u32RecChn, &stRecAttr), ret);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    SAMPLE_RUN(HI_UNF_PVR_RecAddPID(u32RecChn, 0), ret);
    SAMPLE_RUN(HI_UNF_PVR_RecAddPID(u32RecChn, pstProgInfo->PmtPid), ret);
    if (pstProgInfo->AElementNum > 0)
    {
        SAMPLE_RUN(HI_UNF_PVR_RecAddPID(u32RecChn, u32AudPid), ret);
    }

    if (pstProgInfo->VElementNum > 0)
    {
        SAMPLE_RUN(HI_UNF_PVR_RecAddPID(u32RecChn, u32VidPid), ret);
    }

    SAMPLE_RUN(HI_UNF_PVR_RecStartChn(u32RecChn), ret);
    if (HI_SUCCESS != ret)
    {
        HI_UNF_PVR_RecDelAllPID(u32RecChn);
        HI_UNF_PVR_RecDestroyChn(u32RecChn);
        return ret;
    }

    stFileInfo.ProgID = pstProgInfo->ProgID;
    stFileInfo.PmtPid = pstProgInfo->PmtPid;
    stFileInfo.PcrPid = pstProgInfo->PcrPid;
    stFileInfo.VideoType = pstProgInfo->VideoType;
    stFileInfo.VElementNum = pstProgInfo->VElementNum;
    stFileInfo.VElementPid = pstProgInfo->VElementPid;
    stFileInfo.AudioType = pstProgInfo->AudioType;
    stFileInfo.AElementNum = pstProgInfo->AElementNum;
    stFileInfo.AElementPid = pstProgInfo->AElementPid;
    memcpy(stFileInfo.Audioinfo, pstProgInfo->Audioinfo, PROG_MAX_AUDIO*sizeof(PMT_AUDIO));
    stFileInfo.SubtType = pstProgInfo->SubtType;
    stFileInfo.u16SubtitlingNum = pstProgInfo->u16SubtitlingNum;
    memcpy(stFileInfo.SubtitingInfo, pstProgInfo->SubtitingInfo, SUBTITLING_MAX*sizeof(PMT_SUBTITLE));
    memcpy(&(stFileInfo.stSCTESubtInfo), &(pstProgInfo->stSCTESubtInfo), sizeof(PMT_SCTE_SUBTITLE_S));
    stFileInfo.u16ClosedCaptionNum = pstProgInfo->u16ClosedCaptionNum;
    memcpy(stFileInfo.stClosedCaption, pstProgInfo->stClosedCaption, CAPTION_SERVICE_MAX*sizeof(PMT_CLOSED_CAPTION_S));
    stFileInfo.u16ARIBCCPid = pstProgInfo->u16ARIBCCPid;
    stFileInfo.u16TtxNum = pstProgInfo->u16TtxNum;
    memcpy(stFileInfo.stTtxInfo, pstProgInfo->stTtxInfo, TTX_MAX*sizeof(PMT_TTX_S));

    memcpy(&(stFileInfo.stRecAttr), &stRecAttr, sizeof(stFileInfo.stRecAttr));

    SAMPLE_RUN(PVR_SavePorgInfo(&stFileInfo, stRecAttr.szFileName), ret);
    if (HI_SUCCESS != ret)
    {
        HI_UNF_PVR_RecStopChn(u32RecChn);
        HI_UNF_PVR_RecDelAllPID(u32RecChn);
        HI_UNF_PVR_RecDestroyChn(u32RecChn);
        return ret;
    }

    *pu32RecChn = u32RecChn;

    return HI_SUCCESS;
}

HI_S32 PVR_RecStop(HI_U32 u32RecChnID)
{
    HI_S32 ret;
    HI_S32 ret2;
    HI_UNF_PVR_REC_ATTR_S stRecAttr;


    SAMPLE_RUN(HI_UNF_PVR_RecGetChn(u32RecChnID, &stRecAttr), ret2);
    SAMPLE_RUN(HI_UNF_PVR_RecStopChn(u32RecChnID), ret);
    SAMPLE_RUN(HI_UNF_PVR_RecDelAllPID(u32RecChnID), ret);
    SAMPLE_RUN(HI_UNF_PVR_RecDestroyChn(u32RecChnID), ret);
    if (HI_SUCCESS == ret2)
    {
        if (!stRecAttr.stEncryptCfg.bDoCipher)
        {
            //SAMPLE_RUN(PVR_checkIdx(stRecAttr.szFileName), ret);
        }
    }

    return ret;
}


HI_S32 PVR_SwitchDmxSource(HI_U32 dmxId, HI_U32 protId)
{
    HI_S32 ret;

    HI_UNF_DMX_DetachTSPort(dmxId);

    SAMPLE_RUN(HI_UNF_DMX_AttachTSPort(dmxId, protId), ret);

    return ret;
}

HI_S32 PVR_SetAvplayPidAndCodecType(HI_HANDLE hAvplay, const PMT_COMPACT_PROG *pProgInfo)
{
//    HI_U32 i;
    HI_U32 u32VidPid;
    HI_U32 u32AudPid;
    HI_U32 u32AudType;
    HI_S32 Ret;
    HI_UNF_VCODEC_TYPE_E enVidType;
    HI_UNF_VCODEC_ATTR_S stVdecAttr;
    HI_UNF_ACODEC_ATTR_S stAdecAttr;
    //HI_UNF_AVPLAY_STOP_OPT_S    stStopOption;
    
    /*
    stStopOption.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    stStopOption.u32TimeoutMs = 0;

    Ret = HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &stStopOption);
    if (Ret != HI_SUCCESS )
    {
        printf("call HI_UNF_AVPLAY_Stop failed.\n");
        //return Ret;
    }
    */
    HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr);
    HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_ADEC, &stAdecAttr);

    if (pProgInfo->VElementNum > 0)
    {
        u32VidPid = pProgInfo->VElementPid;
        enVidType = pProgInfo->VideoType;
    }
    else
    {
        u32VidPid = INVALID_TSPID;
        enVidType = HI_UNF_VCODEC_TYPE_BUTT;
    }

    if (pProgInfo->AElementNum > 0)
    {
        u32AudPid  = pProgInfo->AElementPid;
        u32AudType = pProgInfo->AudioType;
    }
    else
    {
        u32AudPid = INVALID_TSPID;
        u32AudType = 0xffffffff;
    }

    if (u32VidPid != INVALID_TSPID)
    {
        stVdecAttr.enType = enVidType;
        Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr);
        if (Ret != HI_SUCCESS)
        {
            sample_common_printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
            return Ret;
        }

        Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VID_PID, &u32VidPid);
        if (Ret != HI_SUCCESS)
        {
            sample_common_printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
            return Ret;
        }
    }

    if (u32AudPid != INVALID_TSPID)
    {
        Ret = HIADP_AVPlay_SetAdecAttr(hAvplay, u32AudType, HD_DEC_MODE_RAWPCM, 1);
        Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &u32AudPid);
        if (HI_SUCCESS != Ret)
        {
            sample_common_printf("HIADP_AVPlay_SetAdecAttr failed:%#x\n",Ret);
            return Ret;
        }
    }

    return HI_SUCCESS;
}



/*set audio and video PID attribution,start to play*//*CNcomment:设置音视频PID属性,开始播放*/
HI_S32 PVR_StartLivePlay(HI_HANDLE hAvplay, const PMT_COMPACT_PROG *pProgInfo)
{
    HI_U32 ret = HI_SUCCESS;
    HI_U32 u32Pid = 0;
    HI_UNF_AVPLAY_MEDIA_CHAN_E enMediaType = 0;
    HI_UNF_AVPLAY_FRMRATE_PARAM_S stFrmRateAttr = {0};
    HI_UNF_SYNC_ATTR_S stSyncAttr = {0};
    HI_CODEC_VIDEO_CMD_S  stVdecCmdPara = {0};
    HI_UNF_AVPLAY_TPLAY_OPT_S stTplayOpts = {0};

    PVR_SetAvplayPidAndCodecType(hAvplay, pProgInfo);

    ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &u32Pid);
    if ((HI_SUCCESS != ret) || (0x1fff == u32Pid))
    {
        sample_common_printf("has no audio stream!\n");
    }
    else
    {
        enMediaType |= HI_UNF_AVPLAY_MEDIA_CHAN_AUD;
    }

    ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VID_PID, &u32Pid);
    if ((HI_SUCCESS != ret) || (0x1fff == u32Pid))
    {
        sample_common_printf("has no video stream!\n");
    }
    else
    {
        enMediaType |= HI_UNF_AVPLAY_MEDIA_CHAN_VID;
    }

    if ((enMediaType & HI_UNF_AVPLAY_MEDIA_CHAN_AUD) && (enMediaType & HI_UNF_AVPLAY_MEDIA_CHAN_VID))
    {
        /*enable vo frame rate detect*//*CNcomment:使能VO自动帧率检测*/
        stFrmRateAttr.enFrmRateType = HI_UNF_AVPLAY_FRMRATE_TYPE_PTS;
        stFrmRateAttr.stSetFrmRate.u32fpsInteger = 0;
        stFrmRateAttr.stSetFrmRate.u32fpsDecimal = 0;
        if (HI_SUCCESS != HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_FRMRATE_PARAM, &stFrmRateAttr))
        {
            sample_common_printf("set frame to VO fail.\n");
            return HI_FAILURE;
        }

        /*enable avplay A/V sync*//*CNcomment:使能avplay音视频同步*/
        if (HI_SUCCESS != HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr))
        {
            sample_common_printf("get avplay sync stRecAttr fail!\n");
            return HI_FAILURE;
        }

        stSyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
        stSyncAttr.stSyncStartRegion.s32VidPlusTime = 60;
        stSyncAttr.stSyncStartRegion.s32VidNegativeTime = -20;
        stSyncAttr.u32PreSyncTimeoutMs = 1000;
        stSyncAttr.bQuickOutput = HI_FALSE;

        if (HI_SUCCESS != HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr))
        {
            sample_common_printf("set avplay sync stRecAttr fail!\n");
            return HI_FAILURE;
        }
    }

    /*start to play audio and video*//*CNcomment:开始音视频播放*/
    SAMPLE_RUN(HI_UNF_AVPLAY_Start(hAvplay, enMediaType, NULL), ret);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    /*set avplay trick mode to normal*//*CNcomment:设置avplay特技模式为正常*/
    if (enMediaType & HI_UNF_AVPLAY_MEDIA_CHAN_VID)
    {
        stTplayOpts.enTplayDirect = HI_UNF_AVPLAY_TPLAY_DIRECT_FORWARD;
        stTplayOpts.u32SpeedInteger = 1;
        stTplayOpts.u32SpeedDecimal = 0;
        stVdecCmdPara.u32CmdID = HI_UNF_AVPLAY_SET_TPLAY_PARA_CMD;
        stVdecCmdPara.pPara = &stTplayOpts;
        ret = HI_UNF_AVPLAY_Invoke(hAvplay, HI_UNF_AVPLAY_INVOKE_VCODEC, (void *)&stVdecCmdPara);
        if (HI_SUCCESS != ret)
        {
            sample_common_printf("Resume Avplay trick mode to normal fail.\n");
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 PVR_StopLivePlay(HI_HANDLE hAvplay)
{
    HI_UNF_AVPLAY_STOP_OPT_S stStopOption;

    stStopOption.enMode = HI_UNF_AVPLAY_STOP_MODE_STILL;
    stStopOption.u32TimeoutMs = 0;

    sample_common_printf("stop live play ...\n");

    /*stop playing audio and video*//*CNcomment:停止音视频设备*/
    return HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &stStopOption);
}


/*start playback*//*CNcomment:开始回放*/
HI_S32 PVR_StartPlayBack(const HI_CHAR *pszFileName, HI_U32 *pu32PlayChn, HI_HANDLE hAvplay)
{
    HI_S32 ret;
    HI_U32 u32PlayChn;
    HI_U32 u32Pid = 0;
    PVR_PROG_INFO_S        stFileInfo;
    HI_UNF_PVR_PLAY_ATTR_S stRecAttr;
    PMT_COMPACT_TBL        *pstPmttal;
    HI_UNF_AVPLAY_MEDIA_CHAN_E enMediaType = 0;
    HI_UNF_AVPLAY_FRMRATE_PARAM_S stFrmRateAttr = {0};
    HI_UNF_SYNC_ATTR_S stSyncAttr = {0};
    HI_UNF_AVPLAY_TPLAY_OPT_S stTplayOpts = {0};
    HI_CODEC_VIDEO_CMD_S  stVdecCmdPara = {0};
    PMT_COMPACT_PROG stProgInfoTmp;

    SAMPLE_CheckNullPTR(pszFileName);
    SAMPLE_CheckNullPTR(pu32PlayChn);

    SAMPLE_RUN(PVR_GetPorgInfo(&stFileInfo, pszFileName), ret);
    if (HI_SUCCESS != ret)
    {
        PRINT_SMP("Can NOT get prog INFO, can't play.\n");
        PVR_SearchFile(PVR_DMX_ID_LIVE, PVR_DMX_PORT_ID_PLAYBACK, pszFileName, &pstPmttal);
        PVR_SetAvplayPidAndCodecType(hAvplay, &(pstPmttal->proginfo[0]));

        memcpy(stRecAttr.szFileName, pszFileName, strlen(pszFileName) + 1);
        stRecAttr.u32FileNameLen = strlen(pszFileName);
        stRecAttr.enStreamType = HI_UNF_PVR_STREAM_TYPE_TS;
        stRecAttr.bIsClearStream = HI_TRUE;
    }
    else
    {

        stProgInfoTmp.ProgID = stFileInfo.ProgID;
        stProgInfoTmp.PmtPid = stFileInfo.PmtPid;
        stProgInfoTmp.PcrPid = stFileInfo.PcrPid;
        stProgInfoTmp.VideoType = stFileInfo.VideoType;
        stProgInfoTmp.VElementNum = stFileInfo.VElementNum;
        stProgInfoTmp.VElementPid = stFileInfo.VElementPid;
        stProgInfoTmp.AudioType = stFileInfo.AudioType;
        stProgInfoTmp.AElementNum = stFileInfo.AElementNum;
        stProgInfoTmp.AElementPid = stFileInfo.AElementPid;
        memcpy(stProgInfoTmp.Audioinfo, stFileInfo.Audioinfo, PROG_MAX_AUDIO*sizeof(PMT_AUDIO));
        stProgInfoTmp.SubtType = stFileInfo.SubtType;
        stProgInfoTmp.u16SubtitlingNum = stFileInfo.u16SubtitlingNum;
        memcpy(stProgInfoTmp.SubtitingInfo, stFileInfo.SubtitingInfo, SUBTITLING_MAX*sizeof(PMT_SUBTITLE));
        memcpy(&(stProgInfoTmp.stSCTESubtInfo), &(stFileInfo.stSCTESubtInfo), sizeof(PMT_SCTE_SUBTITLE_S));
        stProgInfoTmp.u16ClosedCaptionNum = stFileInfo.u16ClosedCaptionNum;
        memcpy(stProgInfoTmp.stClosedCaption, stFileInfo.stClosedCaption, CAPTION_SERVICE_MAX*sizeof(PMT_CLOSED_CAPTION_S));
        stProgInfoTmp.u16ARIBCCPid = stFileInfo.u16ARIBCCPid;
        stProgInfoTmp.u16TtxNum = stFileInfo.u16TtxNum;
        memcpy(stProgInfoTmp.stTtxInfo, stFileInfo.stTtxInfo, TTX_MAX*sizeof(PMT_TTX_S));

        PVR_SetAvplayPidAndCodecType(hAvplay, &(stProgInfoTmp));

        memcpy(stRecAttr.szFileName, pszFileName, strlen(pszFileName) + 1);
        stRecAttr.u32FileNameLen = strlen(pszFileName);
        stRecAttr.enStreamType = stFileInfo.stRecAttr.enStreamType;
        stRecAttr.bIsClearStream = stFileInfo.stRecAttr.bIsClearStream;
    }

    if (1 == stFileInfo.stRecAttr.stEncryptCfg.bDoCipher&&ret==HI_SUCCESS)
    {
        memcpy(&(stRecAttr.stDecryptCfg), &(stFileInfo.stRecAttr.stEncryptCfg), sizeof(HI_UNF_PVR_CIPHER_S));

        sample_common_printf("cipher info:\n");
        sample_common_printf("  enType:%d\n", stRecAttr.stDecryptCfg.enType);
    }
    else
    {
        sample_common_printf("cipher info: not encrypt\n");
        stRecAttr.stDecryptCfg.bDoCipher = HI_FALSE;
    }

    ret = HI_UNF_DMX_AttachTSPort(PVR_DMX_ID_LIVE, PVR_DMX_PORT_ID_PLAYBACK);
    if (ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_DMX_AttachTSPort failed.\n");
        HI_UNF_DMX_DeInit();
        return ret;
    }

    SAMPLE_RUN(HI_UNF_DMX_CreateTSBuffer(PVR_DMX_PORT_ID_PLAYBACK, 768*1024, &g_hTsBufForPlayBack), ret);
    if (ret != HI_SUCCESS)
    {
        HI_UNF_DMX_DetachTSPort(PVR_DMX_ID_LIVE);
        HI_UNF_DMX_DeInit();
        return ret;
    }
    /*create new play channel*//*CNcomment:申请新的播放通道*/
    SAMPLE_RUN(HI_UNF_PVR_PlayCreateChn(&u32PlayChn, &stRecAttr, hAvplay, g_hTsBufForPlayBack), ret);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &u32Pid);
    if ((HI_SUCCESS != ret) || (0x1fff == u32Pid))
    {
        sample_common_printf("has no audio stream!\n");
    }
    else
    {
        enMediaType |= HI_UNF_AVPLAY_MEDIA_CHAN_AUD;
    }

    ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VID_PID, &u32Pid);
    if ((HI_SUCCESS != ret) || (0x1fff == u32Pid))
    {
        sample_common_printf("has no video stream!\n");
    }
    else
    {
        enMediaType |= HI_UNF_AVPLAY_MEDIA_CHAN_VID;
    }

    /*enable avplay A/V sync*//*CNcomment:使能avplay音视频同步*/
    if (HI_SUCCESS != HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr))
    {
        sample_common_printf("get avplay sync stRecAttr fail!\n");
        return HI_FAILURE;
    }
    stSyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    stSyncAttr.stSyncStartRegion.s32VidPlusTime = 60;
    stSyncAttr.stSyncStartRegion.s32VidNegativeTime = -20;
    stSyncAttr.u32PreSyncTimeoutMs = 1000;
    stSyncAttr.bQuickOutput = HI_FALSE;

    if (HI_SUCCESS != HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr))
    {
        sample_common_printf("set avplay sync stRecAttr fail!\n");
        return HI_FAILURE;
    }

    /*if you wanna get better figure display performance in pvr fast backward playing,
      pls check the extra_disp in bootargs is large enough, and then enable the following codes*/
    /*
    HI_U32 u32DispOptimizeFlag = 1;
    ret = HI_UNF_AVPLAY_Invoke(hAvplay, HI_UNF_AVPLAY_INVOKE_SET_DISP_OPTIMIZE_FLAG, &u32DispOptimizeFlag);
    if (HI_SUCCESS != ret)
    {
        printf("call HI_UNF_AVPLAY_Invoke failed.\n");
        HI_UNF_PVR_PlayDestroyChn(u32PlayChn);
        return ret;
    }*/

    SAMPLE_RUN(HI_UNF_PVR_PlayStartChn(u32PlayChn), ret);
    if (HI_SUCCESS != ret)
    {
        HI_UNF_PVR_PlayDestroyChn(u32PlayChn);
        return ret;
    }

    /*enable vo frame rate detect*//*CNcomment:使能VO自动帧率检测*/
    stFrmRateAttr.enFrmRateType = HI_UNF_AVPLAY_FRMRATE_TYPE_PTS;
    stFrmRateAttr.stSetFrmRate.u32fpsInteger = 0;
    stFrmRateAttr.stSetFrmRate.u32fpsDecimal = 0;
    if (HI_SUCCESS != HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_FRMRATE_PARAM, &stFrmRateAttr))
    {
        sample_common_printf("set frame to VO fail.\n");
        return HI_FAILURE;
    }

    /*set avplay trick mode to normal*//*CNcomment:设置avplay特技模式为正常*/
    if (enMediaType & HI_UNF_AVPLAY_MEDIA_CHAN_VID)
    {
        stTplayOpts.enTplayDirect = HI_UNF_AVPLAY_TPLAY_DIRECT_FORWARD;
        stTplayOpts.u32SpeedInteger = 1;
        stTplayOpts.u32SpeedDecimal = 0;
        stVdecCmdPara.u32CmdID = HI_UNF_AVPLAY_SET_TPLAY_PARA_CMD;
        stVdecCmdPara.pPara = &stTplayOpts;
        ret = HI_UNF_AVPLAY_Invoke(hAvplay, HI_UNF_AVPLAY_INVOKE_VCODEC, (void *)&stVdecCmdPara);
        if (HI_SUCCESS != ret)
        {
            sample_common_printf("Resume Avplay trick mode to normal fail.\n");
            return HI_FAILURE;
        }
    }

    *pu32PlayChn = u32PlayChn;
    return HI_SUCCESS;
}


/*stop playback*//*CNcomment: 停止回放 */
HI_VOID PVR_StopPlayBack(HI_U32 u32PlayChn)
{
    HI_UNF_AVPLAY_STOP_OPT_S stStopOpt;
    HI_UNF_PVR_PLAY_ATTR_S stPlayAttr;

    stStopOpt.enMode = HI_UNF_AVPLAY_STOP_MODE_STILL;
    stStopOpt.u32TimeoutMs = 0;
    (HI_VOID)HI_UNF_PVR_PlayGetChn(u32PlayChn, &stPlayAttr);
    (HI_VOID)HI_UNF_PVR_PlayStopChn(u32PlayChn, &stStopOpt);
    (HI_VOID)HI_UNF_PVR_PlayDestroyChn(u32PlayChn);
    (HI_VOID)HI_UNF_DMX_DestroyTSBuffer(g_hTsBufForPlayBack);
    (HI_VOID)HI_UNF_DMX_DetachTSPort(PVR_DMX_ID_LIVE);
}

HI_S32 PVR_AvplayInit(HI_HANDLE hWin, HI_HANDLE *phAvplay, HI_HANDLE* phSoundTrack)
{
    HI_S32                   Ret;
    HI_HANDLE                hAvplay;
    HI_UNF_AVPLAY_ATTR_S     stAvplayAttr;
    HI_UNF_SYNC_ATTR_S       stSyncAttr;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;

    if (phSoundTrack == NULL)
    {
        return HI_FAILURE;
    }

    Ret = HIADP_AVPlay_RegADecLib();
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HIADP_AVPlay_RegADecLib failed.\n");
        return Ret;
    }


    Ret = HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_Init failed.\n");
        return Ret;
    }

    Ret = HI_UNF_AVPLAY_GetDefaultConfig(&stAvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_GetDefaultConfig failed.\n");
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    stAvplayAttr.u32DemuxId = PVR_DMX_ID_LIVE;

//#ifdef S_SUPPORT_4PLUS64
    stAvplayAttr.stStreamAttr.u32VidBufSize = 2*1024*1024;
    stAvplayAttr.stStreamAttr.u32AudBufSize = 192*1024;
//#endif

    Ret = HI_UNF_AVPLAY_Create(&stAvplayAttr, &hAvplay);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_Create failed.\n");
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_GetAttr failed.\n");
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    stSyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    stSyncAttr.stSyncStartRegion.s32VidPlusTime = 60;
    stSyncAttr.stSyncStartRegion.s32VidNegativeTime = -20;
    stSyncAttr.u32PreSyncTimeoutMs = 1000;
    stSyncAttr.bQuickOutput = HI_FALSE;

    Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        return Ret;
    }

    Ret = HI_UNF_VO_AttachWindow(hWin, hAvplay);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_VO_AttachWindow failed.\n");
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        HI_UNF_VO_DetachWindow(hWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        return Ret;
    }
    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr, phSoundTrack);
    if (Ret != HI_SUCCESS)
    {
        HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
        HI_UNF_VO_DetachWindow(hWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_SND_Attach(*phSoundTrack, hAvplay);
    if (Ret != HI_SUCCESS)
    {
        HI_UNF_SND_DestroyTrack(*phSoundTrack);
        sample_common_printf("call HI_SND_Attach failed.\n");
        HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
        HI_UNF_VO_DetachWindow(hWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    *phAvplay = hAvplay;
    return HI_SUCCESS;
}

HI_S32  PVR_AvplayDeInit(HI_HANDLE hAvplay, HI_HANDLE hWin, HI_HANDLE hSoundTrack)
{
    HI_S32                   Ret;
    HI_UNF_AVPLAY_STOP_OPT_S stStopOpt;

    stStopOpt.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    stStopOpt.u32TimeoutMs = 0;

    Ret = HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &stStopOpt);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_AVPLAY_Stop failed.\n");
    }

    HI_UNF_VO_SetWindowEnable(hWin,HI_FALSE);

    Ret = HI_UNF_SND_Detach(hSoundTrack, hAvplay);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_SND_Detach failed.\n");
    }

    Ret = HI_UNF_SND_DestroyTrack(hSoundTrack);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_SND_DestroyTrack failed.\n");
    }

    Ret = HI_UNF_VO_DetachWindow(hWin, hAvplay);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_VO_DetachWindow failed.\n");
    }

    Ret = HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_AVPLAY_ChnClose failed.\n");
    }

    Ret = HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_AVPLAY_ChnClose failed.\n");
    }

    Ret = HI_UNF_AVPLAY_Destroy(hAvplay);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_AVPLAY_Destroy failed.\n");
    }

    Ret = HI_UNF_AVPLAY_DeInit();
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_AVPLAY_DeInit failed.\n");
    }

    return HI_SUCCESS;
}

HI_VOID PVR_CallBack(HI_U32 u32ChnID, HI_UNF_PVR_EVENT_E EventType, HI_S32 s32EventValue, HI_VOID *args)
{

    sample_common_printf("==============call back================\n");

    if (EventType > HI_UNF_PVR_EVENT_REC_RESV)
    {
        sample_common_printf("====callback error!!!\n");
        return;
    }

    sample_common_printf("====channel     %d\n", u32ChnID);
    sample_common_printf("====event:%s    %d\n", PVR_GetEventTypeStringByID(EventType), EventType);
    sample_common_printf("====event value %d\n", s32EventValue);


    if (EventType == HI_UNF_PVR_EVENT_PLAY_EOF)
    {
        sample_common_printf("==========play to end of file======\n");
    }
    if (EventType == HI_UNF_PVR_EVENT_PLAY_SOF)
    {
        sample_common_printf("==========play to start of file======\n");
    }
    if (EventType == HI_UNF_PVR_EVENT_PLAY_ERROR)
    {
        sample_common_printf("==========play internal error, check if the disk is insert to the box======\n");
    }
    if (EventType == HI_UNF_PVR_EVENT_PLAY_REACH_REC)
    {
        sample_common_printf("==========play reach to record ======\n");
    }

    if (EventType == HI_UNF_PVR_EVENT_REC_DISKFULL)
    {
        sample_common_printf("\n====disk full,  stop record=====\n\n");

        HI_UNF_PVR_RecStopChn(u32ChnID);
        g_bIsRecStop = HI_TRUE;
    }
    if (EventType == HI_UNF_PVR_EVENT_REC_ERROR)
    {
        sample_common_printf("======disk write error, please check if the disk is insert to the box.====\n");
    }
    if (EventType == HI_UNF_PVR_EVENT_REC_OVER_FIX)
    {
        sample_common_printf("\n======reach the fixed size.==========\n\n");
    }
    if (EventType == HI_UNF_PVR_EVENT_REC_REACH_PLAY)
    {
        sample_common_printf("\n======record reach to play.==========\n\n");
    }
    if (EventType == HI_UNF_PVR_EVENT_REC_DISK_SLOW)
    {
        sample_common_printf("======disk is too slow, the stream record would be error.====\n");
    }

    sample_common_printf("=======================================\n\n");

    return;
}

HI_S32 PVR_RegisterCallBacks(HI_VOID)
{
    HI_S32 Ret;

    Ret = HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_PLAY_EOF, PVR_CallBack, NULL);
    Ret |= HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_PLAY_SOF, PVR_CallBack, NULL);
    Ret |= HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_PLAY_ERROR, PVR_CallBack, NULL);
    Ret |= HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_PLAY_REACH_REC, PVR_CallBack, NULL);
    Ret |= HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_REC_DISKFULL, PVR_CallBack, NULL);
    Ret |= HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_REC_OVER_FIX, PVR_CallBack, NULL);
    Ret |= HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_REC_DISK_SLOW, PVR_CallBack, NULL);
    Ret |= HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_REC_REACH_PLAY, PVR_CallBack, NULL);
    Ret |= HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_REC_ERROR, PVR_CallBack, NULL);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_PVR_RegisterEvent failed.\n");
        return Ret;
    }

    return HI_SUCCESS;
}

HI_U8* PVR_GetEventTypeStringByID(HI_UNF_PVR_EVENT_E eEventID)
{
    HI_U32 u32EventNum = sizeof(g_stEventType)/sizeof(g_stEventType[0]);
    HI_U32 i;
    HI_U8* pszRet = HI_NULL;

    for (i = 0; i < u32EventNum; i++)
    {
        if (eEventID == g_stEventType[i].eEventID)
        {
            pszRet = g_stEventType[i].szEventTypeName;
            break;
        }
    }

    if (i == u32EventNum)
    {
       pszRet = g_stEventType[u32EventNum - 1].szEventTypeName;
    }

    return pszRet;
}


typedef struct tagNET_STREAM_PARAM
{
    HI_U16   u16Port;
    HI_CHAR  szIgmpAddr[16];
    pthread_t hNetStreamThread;
    HI_BOOL   bStopNetStreamThread;
}NET_STREAM_PARAM_S;

NET_STREAM_PARAM_S g_stNetThreadParam = {0};

HI_VOID * NetStream(HI_VOID *args)
{
    HI_S32              SocketFd = -1;
    struct sockaddr_in  ServerAddr;
    in_addr_t           IpAddr;
    struct ip_mreq      Mreq;
    HI_U32              u32AddrLen;
    HI_U32              u32ReadLen;
    HI_U32              u32GetBufCount=0;
    HI_U32              u32ReceiveCount=0;
    HI_S32              Ret;
    HI_HANDLE           hTsBuf = 0;
    HI_UNF_STREAM_BUF_S stStreamBuf;
    NET_STREAM_PARAM_S  *pstThreadParam = (NET_STREAM_PARAM_S*)args;

    if (pstThreadParam == NULL)
    {
        return NULL;
    }

    do
    {
        Ret = HI_UNF_DMX_CreateTSBuffer(PVR_DMX_PORT_ID_IP, 0x200000, &hTsBuf);
        if (Ret != HI_SUCCESS)
        {
            break;
        }

        SocketFd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
        if (SocketFd < 0)
        {
            sample_common_printf("wait send TS to port %d.\n", PVR_DMX_PORT_ID_IP);
            break;
        }

        ServerAddr.sin_family = AF_INET;
        ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        ServerAddr.sin_port = htons(pstThreadParam->u16Port);

        if (bind(SocketFd,(struct sockaddr *)(&ServerAddr),sizeof(struct sockaddr_in)) < 0)
        {
            sample_common_printf("socket bind error [%d].\n", errno);
            break;;
        }

        IpAddr = inet_addr(pstThreadParam->szIgmpAddr);

        sample_common_printf("========================g_pszMultiAddr = %s, g_u16UdpPort=%u\n", pstThreadParam->szIgmpAddr, pstThreadParam->u16Port);
        if (IpAddr)
        {
            Mreq.imr_multiaddr.s_addr = IpAddr;
            Mreq.imr_interface.s_addr = htonl(INADDR_ANY);
            if (setsockopt(SocketFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &Mreq, sizeof(struct ip_mreq)))
            {
                sample_common_printf("wait send TS to port %d.\n", PVR_DMX_PORT_ID_IP);
                break;
            }
        }

        u32AddrLen = sizeof(ServerAddr);

        while (pstThreadParam->bStopNetStreamThread == HI_FALSE)
        {
            Ret = HI_UNF_DMX_GetTSBuffer(hTsBuf, 188*50, &stStreamBuf, 0);
            if (Ret != HI_SUCCESS)
            {
                u32GetBufCount++;
                if(u32GetBufCount >= 10)
                {
                    sample_common_printf("########## TS come too fast! #########, Ret=%d\n", Ret);
                    u32GetBufCount=0;
                }

                usleep(10000) ;
                continue;
            }
            u32GetBufCount=0;

            u32ReadLen = recvfrom(SocketFd, stStreamBuf.pu8Data, stStreamBuf.u32Size, 0,
                               (struct sockaddr *)&ServerAddr, &u32AddrLen);
            if (u32ReadLen <= 0)
            {
                u32ReceiveCount++;
                if (u32ReceiveCount >= 50)
                {
                    sample_common_printf("########## TS come too slow or net error! #########\n");
                    u32ReceiveCount = 0;
                }
            }
            else
            {
                u32ReceiveCount = 0;
                Ret = HI_UNF_DMX_PutTSBuffer(hTsBuf, u32ReadLen);
                if (Ret != HI_SUCCESS )
                {
                    sample_common_printf("call HI_UNF_DMX_PutTSBuffer failed.\n");
                }
            }
        }
    }while(0);

    if (SocketFd != -1)
    {
        close(SocketFd);
        SocketFd = -1;
    }

    if (hTsBuf != 0)
    {
        HI_UNF_DMX_DestroyTSBuffer(hTsBuf);
        hTsBuf = 0;
    }

    return NULL;
}

HI_U32 PVR_StartNetStream(HI_CHAR* pszIgmpAddr, HI_U16 u16Port)
{
    if (pszIgmpAddr == NULL)
    {
        return HI_FAILURE;
    }

    if (g_stNetThreadParam.hNetStreamThread == 0)
    {
        g_stNetThreadParam.bStopNetStreamThread = HI_FALSE;
        memset(g_stNetThreadParam.szIgmpAddr, 0, sizeof(g_stNetThreadParam.szIgmpAddr));
        memcpy(g_stNetThreadParam.szIgmpAddr, pszIgmpAddr, sizeof(g_stNetThreadParam.szIgmpAddr));

        g_stNetThreadParam.u16Port     = u16Port;
        pthread_create(&g_stNetThreadParam.hNetStreamThread, HI_NULL, NetStream, &g_stNetThreadParam);
    }

    return HI_SUCCESS;
}

HI_U32 PVR_StopNetStream()
{
    if (g_stNetThreadParam.hNetStreamThread != 0)
    {
        g_stNetThreadParam.bStopNetStreamThread = HI_TRUE;

        pthread_join(g_stNetThreadParam.hNetStreamThread, HI_NULL);
    }

    return HI_FAILURE;
}

