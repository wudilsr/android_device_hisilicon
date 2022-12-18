#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include "hi_protocol.h"
#include "hi_muxer.h"
#include "hi_transcoder.h"
#include "hi_proto_intf.h"

typedef struct stSampleLocalInfo_S
{
    HI_CHAR pCharLocalPath[256];
    HI_CHAR pCharAudioPath[256];
    HI_HANDLE hTranHandle;
    pthread_t processPthreadID;
    Transcoder_MuxerType muxerType;
    HI_HANDLE hMuxerHandle;
    HI_HANDLE hReadHandle;
}SampleLocalInfo_S;

static SampleLocalInfo_S s_SampleLocalInfo;


static HI_BOOL bSample_Local_StopFlag = HI_FALSE;

static HI_VOID* sample_local_fileProcess(const HI_VOID* arg)
{
    SampleLocalInfo_S* pstSampleInfo;
    TRANSCODER_STRAM stTranStream;
    HI_BOOL bFirstFlag = HI_FALSE;
    HI_S32 s32Ret,s32MuxerLen;
    HI_CHAR pstMuxerBuffer[512 * 1024];
    FILE* pLocalFs = HI_NULL;
    FILE* pAudioFS = HI_NULL;

    pstSampleInfo = (SampleLocalInfo_S*)&s_SampleLocalInfo;
    for(;;)
    {
        s32MuxerLen = 512 * 1024;
        if(bSample_Local_StopFlag)
        {
            break;
        }
        if(!pstSampleInfo->hMuxerHandle || !pstSampleInfo->hTranHandle)
        {
            usleep(500000);
            printf("hMuxerHandle : %x,hTranHandle : %x\n",pstSampleInfo->hMuxerHandle,pstSampleInfo->hTranHandle);
            bFirstFlag = HI_FALSE;
            continue;
        }

        if(HI_FALSE == bFirstFlag)
        {
            pLocalFs = fopen(pstSampleInfo->pCharLocalPath,"wb");
            if(HI_NULL == pLocalFs)
            {
                printf("fopen error!!\n");
                return HI_NULL;
            }
            if(pstSampleInfo->muxerType == TRANSCODER_MUTEX_ES)
            {
                pAudioFS = fopen(pstSampleInfo->pCharAudioPath,"wb");
                if(HI_NULL == pAudioFS)
                {
                    printf("fopen error!!\n");
                    return HI_NULL;
                }
            }
            s32Ret = HI_Transcoder_Start(pstSampleInfo->hTranHandle,HI_TRUE);
            if(HI_SUCCESS != s32Ret)
            {
                printf("sample_local_fileProcess HI_Transcoder_Start error!!\n");
                break;
            }
            s32Ret = HI_Muxer_GetHeader(pstSampleInfo->hMuxerHandle,pstMuxerBuffer,&s32MuxerLen);
            if(HI_SUCCESS != s32Ret)
            {
                printf("HI_Muxer_GetHeader error!!\n");
                break;
            }
            fwrite(pstMuxerBuffer,1,(HI_U32)s32MuxerLen,pLocalFs);
            bFirstFlag = HI_TRUE;
            continue;
        }
        s32Ret = HI_Transcoder_ReadStream(pstSampleInfo->hReadHandle,&stTranStream);
        if(HI_SUCCESS != s32Ret)
        {
            usleep(40000);
            continue;
        }
        if(TRANSCODER_MUTEX_ES != pstSampleInfo->muxerType)
        {
  //          printf("before HI_Muxer_DoMuxer!!\n");
            s32Ret = HI_Muxer_DoMuxer(pstSampleInfo->hMuxerHandle,pstMuxerBuffer,&s32MuxerLen,&stTranStream);
            if(HI_SUCCESS != s32Ret)
            {
                printf("HI_Muxer_DoMuxer error!!\n");
                break;
            }
            if(HI_NULL != pLocalFs)
            {
                fwrite(pstMuxerBuffer,1,(HI_U32)s32MuxerLen,pLocalFs);
            }
        }else
        {

            s32Ret = HI_Muxer_DoMuxer(pstSampleInfo->hMuxerHandle,pstMuxerBuffer,&s32MuxerLen,&stTranStream);
            if(HI_SUCCESS != s32Ret)
            {
                printf("HI_Muxer_DoMuxer error!!\n");
                break;
            }
            if(PAYLOAD_AUDIO_FRAME == stTranStream.ePayloadType )
            {
                if(HI_NULL != pAudioFS)
                {
                    fwrite(pstMuxerBuffer,1,(HI_U32)s32MuxerLen,pAudioFS);
                }
            }else
            {
                if(HI_NULL != pLocalFs)
                {
                    fwrite(pstMuxerBuffer,1,(HI_U32)s32MuxerLen,pLocalFs);
                }
            }
        }
    }
    return HI_NULL;
}

HI_S32 Sample_Protocol_Create(HI_HANDLE* hProtocolHandle,const ProtocolAttr* pstTranAttr)
{
    HI_S32 s32Ret;

    if(pstTranAttr->u32ProtocolType  != TRANSCODER_PROTOCOL_SAMPLE)
    {
        return HI_FAILURE;
    }

    memset(&s_SampleLocalInfo,0,sizeof(ProtocolAttr));
    s_SampleLocalInfo.muxerType = TRANSCODER_MUTEX_TS;
//    s_SampleLocalInfo.muxerType = TRANSCODER_MUTEX_ES;
    if(TRANSCODER_MUTEX_FLV == s_SampleLocalInfo.muxerType)
    {
        strcpy(s_SampleLocalInfo.pCharLocalPath,"./local.flv");
    }
    else if(TRANSCODER_MUTEX_TS == s_SampleLocalInfo.muxerType)
    {
        strcpy(s_SampleLocalInfo.pCharLocalPath,"./local.ts");
    }
    else if(TRANSCODER_MUTEX_ES == s_SampleLocalInfo.muxerType)
    {
        strcpy(s_SampleLocalInfo.pCharLocalPath,"./local.h264");
        strcpy(s_SampleLocalInfo.pCharAudioPath,"./local.aac");
        s32Ret = HI_Muxer_RegistMuxer("libmuxer_es.so");
        if(HI_SUCCESS != s32Ret)
        {
            printf("HI_Muxer_RegistMuxer error!!\n");
            return HI_NULL;
        }
    }
    *hProtocolHandle = ((HI_HANDLE)(&s_SampleLocalInfo));
    return HI_SUCCESS;
}

HI_S32 Sample_Protocol_Destroy(HI_HANDLE hProtocolHandle)
{
    HI_S32 s32Ret;
    SampleLocalInfo_S* pSamLocalInfo = HI_NULL;
    pSamLocalInfo = (SampleLocalInfo_S*)hProtocolHandle;

    s32Ret = HI_Muxer_Destroy(pSamLocalInfo->hMuxerHandle);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Muxer_Destroy error!!!\n");
        return HI_FAILURE;
    }
    pSamLocalInfo->hMuxerHandle = HI_NULL;
    return HI_SUCCESS;
}

HI_S32 Sample_Protocol_Regist(HI_HANDLE pProtocolHandle,HI_HANDLE hTranHandle)
{
    SampleLocalInfo_S *pstSampleInfo = (SampleLocalInfo_S*)pProtocolHandle;
    Transcoder_HandleAttr transcoder_Attr;
    Transcoder_MuxerAttr muxer_Attr;
    HI_S32 s32Ret;
    pstSampleInfo->hTranHandle = (HI_HANDLE)hTranHandle;
    s32Ret = HI_Transcoder_GetAttr(pstSampleInfo->hTranHandle,TRANSCODER_ALL_ATTR,&transcoder_Attr);
    if(HI_SUCCESS !=  s32Ret)
    {
        printf("Sample_Protocol_Regist HI_Transcoder_GetAttr error!!\n");
        return HI_FAILURE;
    }
    s32Ret = HI_Transcoder_RegisterHandle(pstSampleInfo->hTranHandle,&pstSampleInfo->hReadHandle);
    if(HI_SUCCESS !=  s32Ret)
    {
        printf("Sample_Protocol_Regist HI_Transcoder_RegisterHandle error!!\n");
        return HI_FAILURE;
    }
    printf("HI_Transcoder_RegisterHandle hTranHandle : %x,hReadHandle : %x\n",
                pstSampleInfo->hTranHandle,pstSampleInfo->hReadHandle);
    muxer_Attr.audioCodec = transcoder_Attr.audioCodec;
    muxer_Attr.s32AudioBandWidth = transcoder_Attr.s32AudioBandWidth;
    muxer_Attr.s32AudioChannels = transcoder_Attr.s32AudioChannels;
    muxer_Attr.s32AudioSampleRate = transcoder_Attr.s32AudioSampleRate;
    muxer_Attr.s32Height = transcoder_Attr.s32Height;
    muxer_Attr.s32VideoBitRate = transcoder_Attr.s32VideoBitRate;
    muxer_Attr.s32VideoFrameRate = transcoder_Attr.s32VideoFrameRate;
    muxer_Attr.s32Width = transcoder_Attr.s32Width;
    muxer_Attr.videoCodec = transcoder_Attr.videoCodec;
    s32Ret = HI_Muxer_Create(&pstSampleInfo->hMuxerHandle,pstSampleInfo->muxerType,&muxer_Attr);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Muxer_Create error!!!\n");
        return HI_FAILURE;
    }
    s32Ret = pthread_create(&s_SampleLocalInfo.processPthreadID,HI_NULL,sample_local_fileProcess,HI_NULL);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

HI_S32 Sample_Protocol_DeRegist(HI_HANDLE pProtocolHandle,HI_HANDLE hTranHandle)
{
    HI_S32 s32Ret;
    SampleLocalInfo_S *pstSampleInfo = (SampleLocalInfo_S*)pProtocolHandle;

    bSample_Local_StopFlag = HI_TRUE;
    s32Ret = pthread_join(s_SampleLocalInfo.processPthreadID,0);
    if(HI_SUCCESS != s32Ret)
    {
        printf("pthread_join error!!!\n");
        return HI_FAILURE;
    }
    s32Ret = HI_Transcoder_Stop(pstSampleInfo->hTranHandle,HI_TRUE);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Transcoder_Stop error!!\n");
        return HI_FAILURE;
    }
    s32Ret = HI_Transcoder_DeRegisterHandle(pstSampleInfo->hReadHandle);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Transcoder_DeRegisterHandle error!!!\n");
        return HI_FAILURE;
    }
    pstSampleInfo->hReadHandle = HI_NULL;
    return HI_SUCCESS;
}


HI_ProtocolInfo_S hi_protocol_entry = {
  .szName = (const HI_PCHAR)"local",
  .enProtocolType = TRANSCODER_PROTOCOL_SAMPLE,
  .pszDescription = (const HI_PCHAR)"local_default",
  .pDllModule = HI_NULL,
  .ProtocolCreate = Sample_Protocol_Create,
  .ProtocolDestroy = Sample_Protocol_Destroy,
  .ProtocolRegist = Sample_Protocol_Regist,
  .ProtocolDeRegist = Sample_Protocol_DeRegist,
  .next = HI_NULL,
};
