#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "hi_type.h"
#include "svr_extrator_intf.h"

#define SAMPLE_PRINTF printf

#define SAMPLE_SLEEP(ms) \
    do \
    { \
        struct timespec _ts; \
        _ts.tv_sec = (ms) >= 1000 ? (ms)/1000 : 0; \
        _ts.tv_nsec = (_ts.tv_sec > 0) ? ((ms)%1000)*1000000 : (ms)*1000000; \
        (HI_VOID)nanosleep(&_ts, NULL); \
    } while (0)

HI_S32 dumpFileInfo(HI_FORMAT_FILE_INFO_S* pstFileInfo)
{
    HI_U32 i = 0, j = 0;

    SAMPLE_PRINTF("*************************************************\n");

    if (HI_FORMAT_STREAM_TS == pstFileInfo->eStreamType)
    { SAMPLE_PRINTF("Stream type: %s \n", "TS"); }
    else
    { SAMPLE_PRINTF("Stream type: %s \n", "ES"); }

    if (HI_FORMAT_SOURCE_LOCAL == pstFileInfo->eSourceType)
    { SAMPLE_PRINTF("Source type: %s \n", "LOCAL"); }
    else if (HI_FORMAT_SOURCE_NET_VOD == pstFileInfo->eSourceType)
    { SAMPLE_PRINTF("Source type: %s \n", "VOD"); }
    else if (HI_FORMAT_SOURCE_NET_LIVE == pstFileInfo->eSourceType)
    { SAMPLE_PRINTF("Source type: %s \n", "LIVE"); }

    SAMPLE_PRINTF("File size:   %lld bytes \n", pstFileInfo->s64FileSize);
    SAMPLE_PRINTF("Start time:  %lld:%lld:%lld \n",
                  pstFileInfo->s64StartTime / (1000 * 3600),
                  (pstFileInfo->s64StartTime % (1000 * 3600)) / (1000 * 60),
                  ((pstFileInfo->s64StartTime % (1000 * 3600)) % (1000 * 60)) / 1000);
    SAMPLE_PRINTF("Duration:    %lld:%lld:%lld \n",
                  pstFileInfo->s64Duration / (1000 * 3600),
                  (pstFileInfo->s64Duration % (1000 * 3600)) / (1000 * 60),
                  ((pstFileInfo->s64Duration % (1000 * 3600)) % (1000 * 60)) / 1000);
    SAMPLE_PRINTF("bps:         %u bits/s \n", pstFileInfo->u32Bitrate);

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

HI_S32 main(HI_S32 argc, HI_CHAR** argv)
{
    HI_S32 s32Ret = 0;
    HI_FORMAT_FILE_INFO_S* pstFileInfo = NULL;

    if (argc < 2)
    { return HI_FAILURE; }

    printf("file path = %s \n", argv[1]);

    HI_HANDLE extractor;

    s32Ret = SVR_EXTRACTOR_Create(&extractor);

    if (HI_SUCCESS != s32Ret)
    { return HI_FAILURE; }

    s32Ret = SVR_EXTRACTOR_SetDataSource(extractor, argv[1], NULL, NULL);

    if (HI_SUCCESS != s32Ret)
    {
        printf("Set data source fail \n");
        goto err;
    }

    s32Ret = SVR_EXTRACTOR_GetFileInfo(extractor, &pstFileInfo);

    if (HI_SUCCESS != s32Ret)
    {
        printf("Get file information fail \n");
        goto err;
    }

    dumpFileInfo(pstFileInfo);

    HI_FORMAT_FRAME_S stFrame;
    FILE* pfile = NULL;

    pfile = fopen("/mnt/vid_es.h264", "w+b");
    if (NULL == pfile)
    {
        printf("Open file fail \n");
        goto err;
    }

    while (1)
    {
        s32Ret = SVR_EXTRACTOR_ReadFrame(extractor, &stFrame);

        printf("read frame ret = 0x%x, header size = %d, frame size = %d \n",
               s32Ret, stFrame.u32FrameHeaderLen, stFrame.u32Len);

        if (HI_SUCCESS == s32Ret)
        {
            if (NULL != stFrame.pu8FrameHeader)
            { (HI_VOID)fwrite(stFrame.pu8FrameHeader, 1, stFrame.u32FrameHeaderLen, pfile); }

            (HI_VOID)fwrite(stFrame.pu8Addr, 1, stFrame.u32Len, pfile);
        }
        else
        {
            break;
        }

        SVR_EXTRACTOR_Free(extractor, &stFrame);
        SAMPLE_SLEEP(100);
    }

    fclose(pfile);

err:
    SVR_EXTRACTOR_Delete(extractor);

    return HI_FAILURE;
}

