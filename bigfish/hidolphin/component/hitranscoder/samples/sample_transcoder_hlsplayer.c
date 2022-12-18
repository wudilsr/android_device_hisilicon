#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "hi_type.h"
#include "hi_transcoder.h"
#include "hi_muxer.h"
#include "hi_protocol.h"
#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_adp_audio.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_mpi.h"
#include "hi_unf_venc.h"
#include "hi_unf_aenc.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "HA.AUDIO.AAC.encode.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "hi_http_intf.h"
#include "hi_hls_intf.h"

//#include "hi_tran_log.h"
//#include "hi_rtsp_wfd.h"
#define  PLAY_DMX_ID  0

pthread_t   g_TsThd;
pthread_mutex_t g_TsMutex;
HI_BOOL     g_bStopTsThread = HI_FALSE;
HI_HANDLE          g_TsBuf;
HI_HANDLE          g_hAvplay;
HI_HANDLE g_hTranHandle;
HI_HANDLE hProtoHandle;
PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;
FILE               *g_pTsFile = HI_NULL;
HI_S32 vid_width = 0;
HI_S32 vid_height = 0;
HI_S32 vid_bitrate = 0;
HI_S32 aud_sampleRate = 0;


#define MAX_FILE_NAME_LEN  (1024)

HI_CHAR g_fileName[MAX_FILE_NAME_LEN];
HI_S32 g_TranOuts32X;                    /*转码的起始位置 X 坐标*/
HI_S32 g_TranOuts32Y;                    /*转码的起始位置 Y 坐标*/
HI_S32 g_TranOuts32Width = 720;                /*视频分辨率--高*/
HI_S32 g_TranOuts32Height = 576;               /*视频分辨率--宽*/
HI_U32 g_TranOutu32VideoBitRate = 1024 * 1024;             /*视频比特率*/
HI_S32 g_TranOuts32VideoFrameRate = 25;           /*视频帧率*/
HI_S32 g_TranOuts32AudioSampleRate = 48000;          /*音频采样率*/
HI_S32 g_TranOuts32AudioBandWidth = 16;           /*音频采样宽度*/
HI_S32 g_TranOuts32AudioChannels = 2;            /*音频采样的声道数量*/
HI_S32 g_TranOuts32Gop = 10;            /*视频I帧间隔*/
HI_S32 g_s32DefaultTsDuration = 1;            /*HLS default ts file time length, range 1---10*/
HI_S32 g_s32DefaultMaxTsFileCnt = 3;            /*max valid ts file number in refreshed m3u8 file*/

Transcoder_ProtocolType g_TranProtocolType = TRANSCODER_PROTOCOL_SAMPLE;
HI_HANDLE  g_hHlsCtxHandle;

HI_VOID TsTthread(HI_VOID *args)
{
    HI_UNF_STREAM_BUF_S   StreamBuf;
    HI_U32                Readlen;
    HI_S32                Ret;
    HI_S32                s32Ret;
    while (!g_bStopTsThread)
    {
        pthread_mutex_lock(&g_TsMutex);
        Ret = HI_UNF_DMX_GetTSBuffer(g_TsBuf, 188*50, &StreamBuf, 1000);
        if (Ret != HI_SUCCESS )
        {
            usleep(20000);
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), 188*50, g_pTsFile);
        if(Readlen <= 0)
        {
            printf("read ts file end and rewind!hProtoHandle : %d\n",hProtoHandle);
            HI_Protocol_WFD_SetClientCommand(hProtoHandle, WFD_SOURCE_METHOD_RESET,HI_TRUE);
            rewind(g_pTsFile);
            pthread_mutex_unlock(&g_TsMutex);
            HLS_Set_ChannelChangeFlag(g_hHlsCtxHandle);
            continue;
        }

        Ret = HI_UNF_DMX_PutTSBuffer(g_TsBuf, Readlen);
        if (Ret != HI_SUCCESS )
        {
            printf("call HI_UNF_DMX_PutTSBuffer failed.\n");
        }
        pthread_mutex_unlock(&g_TsMutex);
    }

    Ret = HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    if (Ret != HI_SUCCESS )
    {
        printf("call HI_UNF_DMX_ResetTSBuffer failed.\n");
    }

    return;
}

static HI_VOID Transcoder_SetDefaultAttr(Transcoder_HandleAttr* stTranHandleAttr)
{
    stTranHandleAttr->audioCodec = TRANSCODER_CODEC_ID_AACLC;
    stTranHandleAttr->videoCodec = TRANSCODER_CODEC_ID_H264;
    stTranHandleAttr->hSrc = g_hAvplay;
    stTranHandleAttr->pNodifySrcFunc = HI_NULL;
    stTranHandleAttr->s32AudioBandWidth = 16;
    stTranHandleAttr->s32AudioChannels = 2;
    stTranHandleAttr->s32AudioSampleRate = 48000;
    stTranHandleAttr->s32Height = 576;
    stTranHandleAttr->u32VideoBitRate = 512 * 1024;
    stTranHandleAttr->s32VideoFrameRate = 25;
    stTranHandleAttr->s32Width = 720;
    stTranHandleAttr->SourceType = 0;
    stTranHandleAttr->bCycle = HI_FALSE;
}

static HI_S32 ParseCmd(char* pCommandStr)
{
    HI_U32 u32BitRateX = 0,u32BitRateY = 0,u32BitRateZ = 0;
    const char* pWidth = "w=";
    const char* pHeight = "h=";
    const char* pVideoBitRate = "b=";
    const char* pVideoFrameRate = "f=";
    const char* pAudioSampleRate = "s=";
    const char* pAudioChannel = "c=";
    const char* pfreq = "freq=";
    const char* psrate = "srate=";
    const char* pqam = "qam=";
    const char* protocol = "pro=";
    const char* pfile = "file=";
    const char* mulFlag = "*";
    const char* pband = "band=";

    char* pTmpPoint = HI_NULL;
    if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pWidth)))
    {
        pTmpPoint += strlen((char*)pWidth);
        g_TranOuts32Width = atoi(pTmpPoint);
        printf("tran width : %d\n",g_TranOuts32Width);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pHeight)))
    {
        pTmpPoint += strlen((char*)pHeight);
        g_TranOuts32Height = atoi(pTmpPoint);
        printf("tran height : %d\n",g_TranOuts32Height);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pVideoBitRate)))
    {
        pTmpPoint += strlen((char*)pVideoBitRate);
        u32BitRateX = atoi(pTmpPoint);
        if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)mulFlag)))
        {
            pTmpPoint += strlen((char*)mulFlag);
            u32BitRateY = atoi(pTmpPoint);
            printf("pTmpPoint : %s\n",pTmpPoint);
            if(HI_NULL != (pTmpPoint = strstr(pTmpPoint,(char*)mulFlag)))
            {
                printf("~~pTmpPoint : %s\n",pTmpPoint);
            pTmpPoint += strlen((char*)mulFlag);
                u32BitRateZ = atoi(pTmpPoint);
                g_TranOutu32VideoBitRate = u32BitRateX * u32BitRateY * u32BitRateZ;
            }else
            {
            g_TranOutu32VideoBitRate = u32BitRateX * u32BitRateY;
            }
        }else
        {
            g_TranOutu32VideoBitRate = u32BitRateX;
        }
        printf("tran video bitrate : %d\n",g_TranOutu32VideoBitRate);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pAudioSampleRate)))
    {
        pTmpPoint += strlen((char*)pAudioSampleRate);
        g_TranOuts32AudioSampleRate = atoi(pTmpPoint);
        printf("tran audio samplerate : %d\n",g_TranOuts32AudioSampleRate);
    }

    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pAudioChannel)))
    {
        pTmpPoint += strlen((char*)pAudioChannel);
        g_TranOuts32AudioChannels = atoi(pTmpPoint);
        printf("tran audio samplerate : %d\n",g_TranOuts32AudioChannels);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pfile)))
    {
        pTmpPoint += strlen((char*)pfile);
        if(strlen(pTmpPoint) + 1 > MAX_FILE_NAME_LEN)
        {
            printf("tran file name is too long: %s max len: %d \n",pTmpPoint, MAX_FILE_NAME_LEN);
            return HI_FAILURE;
        }
        memcpy(g_fileName,pTmpPoint,strlen(pTmpPoint) + 1);
        printf("tran file name : %s\n",g_fileName);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pband)))
    {
        pTmpPoint += strlen((char*)pband);
        g_TranOuts32AudioBandWidth = atoi(pTmpPoint);
        printf("audio  pband : %d\n",g_TranOuts32AudioBandWidth);
    }
    else
    {
        printf("parse error!!! argv : %s\n",pCommandStr);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

typedef struct _TsSendJob
{
    HI_S32 sendSocket;
    HI_U32 seqNum;
    volatile HI_BOOL bneedHanleJobFlag;
}TsSendJob;

typedef enum _HlsRunState
{
    HLS_STATE_INIT,
    HLS_STATE_IDLE,
    HLS_STATE_READY,
    HLS_STATE_LINKED,
    HLS_STATE_ERROR,
    HLS_STATE_STOPING,
    HLS_STATE_BUTT
}HlsRunState;

typedef enum _HlsDeviceType
{
    HLS_DEVIECE_IOS7,
    HLS_DEVIECE_IOS6,
    HLS_DEVIECE_IOS5,
    HLS_DEVIECE_OTHER,
    HLS_DEVIECE_BUTT
}HlsDeviceType;

#define MAX_IP_LEN  (64)

typedef struct _HlsHandleCtx
{
    HI_HANDLE hTranscoderHandle;
    HI_HANDLE hProtocolHandle;
    HI_HANDLE hMuxerHandle;
    HI_HANDLE hReadMbufHdl;
    HI_HANDLE hHlsHandle;
    pthread_t  sourceThreadID;
    pthread_t  listenThreadID;
    /*flag to control the HLS state listen Loop thread, determine
    runnning or exit*/
    HI_BOOL bListenLoopFlag;
    /*flag to indicate: the http req is the first starting request from client;
    default: false, when receive first http req, set to true*/
    HI_BOOL bfirstReqFlag;
    HI_BOOL bSourceLoopFlag;
    HI_BOOL bHandleExceptFlag;
    TsSendJob sendJob;
    HlsRunState eState;
    HlsDeviceType eCurType;
    HI_CHAR ipStr[MAX_IP_LEN];
    HI_S32 bFristAudioFlag;
    HI_S32 bFristVidFlag;
    HI_U32 u32lastVidPts;
    HI_U32 u32lastAudPts;
}HlsHandleCtx;


#define HTTP_RESP_OK  (200)
#define HTTP_RESP_PARTIAL_CONTENT  (206)
#define HTTP_RESP_NOT_ACCEPTABLE (406)
#define HTTP_MAX_HEADER_LEN (1024)

#define  MAX_VID_FRAME_LEN  (512*1024)
#define HLS_AUD_PTS_INTERVAL  (21)
#define HLS_VID_PTS_INTERVAL  (40)

#define HLS_M3U8_FILE_SUFFIX  ".m3u8"
#define HLS_TS_FILE_SUFFIX  ".ts"

#define HTTP_CONTENT_TYPE_TEXT  "text/plain"
#define HTTP_CONTENT_TYPE_APP  "application/vnd.apple.mpegurl"

#define HLS_TSDUARTION_COMMON  (1)
#define HLS_TSDUARTION_IOS5_6  (2)
#define HLS_TSFILECNT_COMMON  (3)
#define HLS_TSFILECNT_IOS5_6  (5)


#include <utils/Log.h>
#define Printf(fmt...)\
do{\
    printf("[%s,%s, %d]",__FILE__,__FUNCTION__,__LINE__);\
    printf(fmt);\
}while(0)

#define SAMPLE_PRINT(fmt...) Printf(fmt)

#define  ENTER_SAMPLE_FUNC  //SAMPLE_PRINT("Enter Function\n")

#define CHECK(Condition) \
do{\
        if(!Condition)\
        {\
            HLS_PRINT("Check"#Condition "error \n");\
            return HI_FAILURE;\
        }\
}while(0)

#define  LEAVE_SAMPLE_FUNC  //SAMPLE_PRINT("Leave Function\n")

#ifndef ABS
#define ABS(a,b) ((a) < (b)? ((b) - (a)) : ((a) - (b)))
#endif

static HI_U32 getMsTime()
{
    struct timeval pTime;
    gettimeofday(&pTime, NULL);
    return (((pTime.tv_sec)*(1000)) + (pTime.tv_usec / 1000));
}

static HI_VOID TransAttr_To_MuxerAttr(const Transcoder_HandleAttr* transAttr,
    Transcoder_MuxerAttr* muxerAttr)
{
    muxerAttr->audioCodec = transAttr->audioCodec;
    muxerAttr->videoCodec = transAttr->videoCodec;
    muxerAttr->s32Width = transAttr->s32Width;
    muxerAttr->s32Height = transAttr->s32Height;
    muxerAttr->u32VideoBitRate = transAttr->u32VideoBitRate;
    muxerAttr->s32VideoFrameRate = transAttr->s32VideoFrameRate;
    muxerAttr->s32AudioSampleRate = transAttr->s32AudioSampleRate;
    muxerAttr->s32AudioBandWidth = transAttr->s32AudioBandWidth;
    muxerAttr->s32AudioChannels = transAttr->s32AudioChannels;
}

static HI_S32 SOCKET_GetPeerIPPort(HI_S32 socketID, HI_CHAR* ip, HI_U16 *port)
{
    HI_S32 namelen = 0;
    HI_S32 s32Ret;
    struct sockaddr addr;
    struct sockaddr_in addr_in;
    namelen = sizeof(struct sockaddr_in);
    s32Ret = getpeername(socketID, &addr, (HI_U32*)&namelen);
    if(0 != s32Ret)
    {
        Printf("socketID : %d getpeername error!!\n",socketID);
        return HI_FAILURE;
    }
    memcpy(&addr_in,&addr,sizeof(struct sockaddr_in));
    *port = (unsigned short)ntohs(addr_in.sin_port);
    strncpy(ip, (HI_CHAR*)inet_ntoa(addr_in.sin_addr), MAX_IP_LEN-1);

    return HI_SUCCESS;
}

HI_VOID HLS_Add_TsSend_Job(HlsHandleCtx* phlsCtx, HI_U32 seqNum, HI_S32 sockfd)
{
    ENTER_SAMPLE_FUNC;
    if(phlsCtx->sendJob.bneedHanleJobFlag && phlsCtx->sendJob.seqNum == 0)
    {
        Printf("should not happened , when add job, must been in idle!\n");
        return;
    }
    phlsCtx->sendJob.bneedHanleJobFlag = HI_TRUE;
    phlsCtx->sendJob.seqNum = seqNum;
    phlsCtx->sendJob.sendSocket = sockfd;
    LEAVE_SAMPLE_FUNC;
}

HI_VOID HLS_Remove_TsSend_Job(HlsHandleCtx* pHlsCtx)
{
    //ENTER_SAMPLE_FUNC;
    close(pHlsCtx->sendJob.sendSocket);
    pHlsCtx->sendJob.sendSocket = -1;
    pHlsCtx->sendJob.seqNum = 0;
    pHlsCtx->sendJob.bneedHanleJobFlag = HI_FALSE;
    //LEAVE_SAMPLE_FUNC;
}

/*Parse device type of client with User-Agent info in http req,
 the main point is to differ the ios device type; according test,
 ios device user-Agent pattern:
 iPad; CPU OS 6_1_3
 iPhone; CPU OS 6_1_3
 iPhone OS 7_0_2
 ;then we parse ios version with info above*/
HlsDeviceType HLS_Parse_DeviceType(HI_CHAR* pHttpReq)
{
    HI_CHAR* pUrl = pHttpReq;
    HI_CHAR* pTmp = HI_NULL;
    HI_CHAR* pBegin = HI_NULL;
    HI_CHAR* pEnd = HI_NULL;
    HlsDeviceType retType = HLS_DEVIECE_OTHER;

    pTmp = strstr(pUrl, "User-Agent:");

    if(!pTmp)
    {
        Printf("there no user agent info \n");
        retType = HLS_DEVIECE_OTHER;
    }
    else
    {
        pTmp+=strlen("User-Agent:");
        if(strstr(pTmp, "iPhone") || strstr(pTmp, "iPad"))
        {
            /*ipad or iphone device*/
            HI_CHAR version[16] = {0};
            HI_CHAR majorVer[4] = {0};
            HI_S32  iosMajorVer = 0;
            pBegin = strstr(pTmp, "OS");
            if(!pBegin)
            {
                Printf("there no OS info, maybe not ios device, device parse error \n");
                return HLS_DEVIECE_OTHER;
            }
            pBegin+=strlen("OS");
            pBegin+=strlen(" ");
            pEnd = strstr(pBegin, " ");
            if(!pEnd)
            {
                Printf("ios userAgent pattern parse error \n");
                return HLS_DEVIECE_OTHER;
            }
            strncpy(version, pBegin, pEnd-pBegin);
            majorVer[0] = version[0];
            iosMajorVer =  atoi(majorVer);
            Printf("IOS device version: %s major: %d \n", version, iosMajorVer);
            if(5 == iosMajorVer)
                retType = HLS_DEVIECE_IOS5;
            else if(6 == iosMajorVer)
                retType = HLS_DEVIECE_IOS6;
            else if(7 == iosMajorVer)
                retType = HLS_DEVIECE_IOS7;
            else
                retType = HLS_DEVIECE_OTHER;
        }
        else
            retType = HLS_DEVIECE_OTHER;
    }
    return retType;
}

HI_VOID HLS_Client_ChangeIP(HlsHandleCtx* phlsCtx, HI_S32 socket)
{
    HI_CHAR ipStr[MAX_IP_LEN] = {0};
    HI_U16 port = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = SOCKET_GetPeerIPPort(socket, ipStr, &port);
    if(HI_SUCCESS != s32Ret)
    {
        Printf("SOCKET_GetPeerIPPort error!!\n");
    }

    memset(phlsCtx->ipStr, 0x00, MAX_IP_LEN);
    strncpy(phlsCtx->ipStr, ipStr, MAX_IP_LEN-1);
}

HI_BOOL HLS_Check_Client_Change(HlsHandleCtx* phlsCtx, HI_S32 socket)
{
    HI_CHAR ipStr[MAX_IP_LEN] = {0};
    HI_U16 port = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = SOCKET_GetPeerIPPort(socket, ipStr, &port);
    if(HI_SUCCESS != s32Ret)
    {
        Printf("SOCKET_GetPeerIPPort error!!\n");
        return HI_FALSE;
    }
    /*frist link, nochange*/
    if(strlen(phlsCtx->ipStr) == 0)
    {
        strncpy(phlsCtx->ipStr, ipStr, MAX_IP_LEN-1);
        return HI_FALSE;
    }

    if(!strcmp(phlsCtx->ipStr, ipStr))
        return HI_FALSE;
    else
        return HI_TRUE;

    return HI_FALSE;
}

/*for ios5, ios6 devices, the irregular audio pts will cause the audio disorder,
  on our platform, the aud pts is disorder; then we recalculate audio pts, and
  video pts for synchronizing;
  we assume the audio samplerate is 48000, samples per frame is 1024,
  then audio pts interval is 21, video pts interval is 40; based on audio,
  video do synchronizing */
HI_VOID HLS_Recalculate_MediaPts(HlsHandleCtx* pHlsCtx, TRANSCODER_STRAM* pstTranStream)
{
    if(PAYLOAD_AUDIO_FRAME == pstTranStream->ePayloadType)
    {
        if(!pHlsCtx->bFristAudioFlag)
        {
            pHlsCtx->bFristAudioFlag = 1;
            pHlsCtx->u32lastAudPts = pstTranStream->enDataStream.stAencStream.u32PtsMs;
        }
        else
        {
            pHlsCtx->u32lastAudPts = pHlsCtx->u32lastAudPts + HLS_AUD_PTS_INTERVAL;
        }
        //Printf("aud  real: %d pts: %d  \n", stTranStream.enDataStream.stAencStream.u32PtsMs, u32lastAudPts);
        pstTranStream->enDataStream.stAencStream.u32PtsMs = pHlsCtx->u32lastAudPts;
    }
    else if(PAYLOAD_VIDEO_KEY_FRAME == pstTranStream->ePayloadType
        || PAYLOAD_VIDEO_NORMAL_FRAME == pstTranStream->ePayloadType)
    {
        if(!pHlsCtx->bFristVidFlag)
        {
            pHlsCtx->bFristVidFlag = 1;
            pHlsCtx->u32lastVidPts = pstTranStream->enDataStream.stVencStream.u32PtsMs;
        }
        else
        {
            if(ABS(pHlsCtx->u32lastVidPts, pHlsCtx->u32lastAudPts) > (2*(HLS_VID_PTS_INTERVAL)))
            {
                if(pHlsCtx->u32lastVidPts > pHlsCtx->u32lastAudPts)
                    pHlsCtx->u32lastVidPts = pHlsCtx->u32lastVidPts + 0;
                else
                    pHlsCtx->u32lastVidPts = pHlsCtx->u32lastVidPts + (2*(HLS_VID_PTS_INTERVAL));
            }
            else
                pHlsCtx->u32lastVidPts = pHlsCtx->u32lastVidPts + HLS_VID_PTS_INTERVAL;
        }

        //Printf("vid  real: %d pts: %d  \n", stTranStream.enDataStream.stVencStream.u32PtsMs, u32lastVidPts);
        pstTranStream->enDataStream.stVencStream.u32PtsMs = pHlsCtx->u32lastVidPts;
    }
    else
    {
        pstTranStream->enDataStream.stVencStream.u32PtsMs = pHlsCtx->u32lastVidPts + HLS_VID_PTS_INTERVAL;
    }
}

HI_VOID* HLS_Write_Source_Thread(HI_VOID* args)
{
    TRANSCODER_STRAM stTranStream;
    HI_U8* pstMuxerBuffer = HI_NULL;
    HI_S32 s32MuxerLen = 0;
    HlsHandleCtx* pHlsCtx = (HlsHandleCtx*)args;
    TsFrameInfo frameInfo;
    HI_S32 s32Ret = HI_SUCCESS;
    TsMediaInfo mediaInfo = {0};
    HI_BOOL bNeedRecalculatePts = HI_FALSE;

    pstMuxerBuffer = (HI_U8*)malloc(MAX_VID_FRAME_LEN);
    if(!pstMuxerBuffer)
    {
        Printf("malloc  pstMuxerBuffer error!!\n");
        return HI_NULL;
    }

    HI_Protocol_HLS_GetAttr(pHlsCtx->hHlsHandle, &mediaInfo);
    /*before beginning write ts stream to hls proto, fix the
    hls related attribute with device type to get best playing experience*/
    if(pHlsCtx->eCurType == HLS_DEVIECE_IOS7
        ||pHlsCtx->eCurType == HLS_DEVIECE_OTHER)
    {
        mediaInfo.s32TsDuration = HLS_TSDUARTION_COMMON;
        mediaInfo.s32MaxTsFileCnt = HLS_TSFILECNT_COMMON;
    }
    else
    {
        mediaInfo.s32TsDuration = HLS_TSDUARTION_IOS5_6;
        bNeedRecalculatePts = HI_TRUE;
        mediaInfo.s32MaxTsFileCnt = HLS_TSFILECNT_IOS5_6;
    }
    HI_Protocol_HLS_SetAttr(pHlsCtx->hHlsHandle, &mediaInfo);
    Printf("current link device type is : %d \n", pHlsCtx->eCurType);

    while(pHlsCtx->bSourceLoopFlag)
    {
        s32Ret = HI_Transcoder_ReadStream(pHlsCtx->hReadMbufHdl, &stTranStream);
        if(HI_SUCCESS != s32Ret)
        {
            usleep(40000);
            continue;
        }
        if(bNeedRecalculatePts)
            HLS_Recalculate_MediaPts(pHlsCtx, &stTranStream);
        s32MuxerLen = MAX_VID_FRAME_LEN;
        s32Ret = HI_Muxer_DoMuxer(pHlsCtx->hMuxerHandle, pstMuxerBuffer, &s32MuxerLen,&stTranStream);
        if(HI_SUCCESS != s32Ret)
        {
            Printf("HI_Muxer_DoMuxer failed!!\n");
            continue;
        }
        if(PAYLOAD_AUDIO_FRAME != stTranStream.ePayloadType)
        {
            //Printf("ts pt: %d  len: %d\n", stTranStream.ePayloadType, s32MuxerLen);
        }
        frameInfo.nBufLen = s32MuxerLen;
        frameInfo.pBuf = pstMuxerBuffer;
        frameInfo.payloadtype = stTranStream.ePayloadType;
        if(PAYLOAD_AUDIO_FRAME == stTranStream.ePayloadType)
        {
            frameInfo.pts = stTranStream.enDataStream.stAencStream.u32PtsMs;
        }else
        {
            frameInfo.pts = stTranStream.enDataStream.stVencStream.u32PtsMs;
        }
        s32Ret = HI_Protocol_HLS_WriteTsFrame(pHlsCtx->hHlsHandle, &frameInfo);
        if(HI_SUCCESS != s32Ret)
        {
            Printf("HI_Protocol_HLS_WriteTsFrame error!!\n");
            pHlsCtx->eState = HLS_STATE_ERROR;
            break;
        }
    }

    free(pstMuxerBuffer);

    pHlsCtx->bFristAudioFlag = 0;
    pHlsCtx->bFristVidFlag = 0;
    pHlsCtx->u32lastVidPts = 0;
    pHlsCtx->u32lastAudPts = 0;
    Printf("HLS_Write_Source_Thread exit sucess!!\n");
    return NULL;
}

HI_S32 HLS_closeSource(HlsHandleCtx* pHlsCtx)
{
    ENTER_SAMPLE_FUNC;
    HI_S32 iRet = HI_SUCCESS;
    Printf("HLS_closeSource enter\n");
    pHlsCtx->bSourceLoopFlag = HI_FALSE;

    iRet = pthread_join(pHlsCtx->sourceThreadID, NULL);
    if(iRet != HI_SUCCESS)
    {
        Printf("pthread_join pHlsCtx->sourceThreadID failed\n");
    }
    pHlsCtx->sourceThreadID = 0;

    iRet  = HI_Muxer_Destroy(pHlsCtx->hMuxerHandle);
    if (HI_SUCCESS != iRet )
    {
        Printf("call HI_Muxer_Destroy failed.\n");
    }

    iRet  = HI_Muxer_DeInit();
    if (HI_SUCCESS != iRet )
    {
        Printf("call HI_Muxer_DeInit failed.\n");
    }

    iRet  = HI_Transcoder_Stop(pHlsCtx->hTranscoderHandle, HI_TRUE);
    if (HI_SUCCESS != iRet )
    {
        Printf("call HI_Transcoder_Stop failed.\n");
    }

    iRet  = HI_Transcoder_DeRegisterHandle(pHlsCtx->hReadMbufHdl);
    if (HI_SUCCESS != iRet )
    {
        Printf("call HI_Transcoder_DeRegisterHandle failed.\n");
    }
    LEAVE_SAMPLE_FUNC;
    Printf("HLS_closeSource exit \n");

    return HI_SUCCESS;
}

HI_S32 HLS_openSource(HlsHandleCtx* pHlsCtx)
{
    ENTER_SAMPLE_FUNC;
    HI_S32 iRet = HI_SUCCESS;

    iRet = HI_Transcoder_RegisterHandle(pHlsCtx->hTranscoderHandle,&pHlsCtx->hReadMbufHdl);
    if(iRet != HI_SUCCESS)
    {
        Printf("HI_Transcoder_RegisterHandle error Ret: %d\n",iRet);
        goto Err_Ret;
    }

    iRet = HI_Transcoder_Start(pHlsCtx->hTranscoderHandle, HI_TRUE);
    if(iRet != HI_SUCCESS)
    {
        Printf("HI_Transcoder_Start failed s32Ret : %d\n", iRet);
        goto Trans_Dereg;
    }
    Transcoder_MuxerAttr MuxerAttr;
    Transcoder_HandleAttr transAttr;
    memset(&transAttr, 0x00, sizeof(Transcoder_HandleAttr));
    memset(&MuxerAttr, 0x00, sizeof(Transcoder_MuxerAttr));
    iRet  = HI_Transcoder_GetAttr(pHlsCtx->hTranscoderHandle, TRANSCODER_ALL_ATTR, &transAttr);
    if (HI_SUCCESS != iRet)
    {
        Printf("call HI_Transcoder_GetAttr failed.\n");
        goto Trans_Stop;
    }
    TransAttr_To_MuxerAttr(&transAttr, &MuxerAttr);
    iRet  = HI_Muxer_Init();
    if (HI_SUCCESS != iRet)
    {
        Printf("call HI_Muxer_Init failed.\n");
        goto Trans_Stop;
    }
    iRet = HI_Muxer_Create(&pHlsCtx->hMuxerHandle, TRANSCODER_MUTEX_TS, &MuxerAttr);
    if(HI_SUCCESS != iRet)
    {
        Printf("HI_Muxer_Create failed\n");
        goto Muxer_Deinit;
    }
    pHlsCtx->bSourceLoopFlag = HI_TRUE;
    iRet = pthread_create((pthread_t*)&pHlsCtx->sourceThreadID,HI_NULL,HLS_Write_Source_Thread,(HI_VOID*)pHlsCtx);
    if (iRet != HI_SUCCESS)
    {
        Printf("pthread_create error.\r\n");
        goto Muxer_Destoy;
    }
    LEAVE_SAMPLE_FUNC;
    return HI_SUCCESS;

Muxer_Destoy:
    iRet = HI_Muxer_Destroy(pHlsCtx->hMuxerHandle);
    if(HI_SUCCESS != iRet)
        Printf("HI_Muxer_Destroy failed ret: %d \n", iRet);

Muxer_Deinit:
    iRet = HI_Muxer_DeInit();
    if(HI_SUCCESS != iRet)
        Printf("HI_Muxer_DeInit failed ret: %d \n", iRet);

Trans_Stop:
    iRet = HI_Transcoder_Stop(pHlsCtx->hTranscoderHandle, HI_TRUE);
    if(HI_SUCCESS != iRet)
        Printf("HI_Transcoder_Stop failed ret: %d \n", iRet);

Trans_Dereg:
    iRet = HI_Transcoder_DeRegisterHandle(pHlsCtx->hReadMbufHdl);
    if(HI_SUCCESS != iRet)
        Printf("HI_Transcoder_DeRegisterHandle failed ret: %d \n", iRet);

Err_Ret:
    return HI_FAILURE;
}

HI_VOID* HLS_Status_Listen_Thread(HI_VOID* args)
{
    HlsHandleCtx* pHlsCtx = (HlsHandleCtx*)args;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 timeOutTime = 0;
    HI_U8* pfileBuf = NULL;
    HI_CHAR pHeader[HTTP_MAX_HEADER_LEN] = {0};
    HI_S32 fileLen = 0;
    TsFileInfo tsFile;

    s32Ret = HLS_openSource(pHlsCtx);
    if(HI_SUCCESS != s32Ret)
    {
        Printf("HLS_openSource failed \n");
        return HI_NULL;
    }
    HI_S32 s32TsDuration = 0;
    if(pHlsCtx->eCurType == HLS_DEVIECE_IOS7
        ||pHlsCtx->eCurType == HLS_DEVIECE_OTHER)
        s32TsDuration = HLS_TSDUARTION_COMMON;
    else
        s32TsDuration = HLS_TSDUARTION_IOS5_6;
    tsFile.pBuf = (HI_U8*)malloc(s32TsDuration*BUF_SIZE_1_5M);
    if(!tsFile.pBuf)
    {
        Printf("malloc tsFile.pBuf failed \n");
        HLS_closeSource(pHlsCtx);
        return HI_NULL;
    }
    timeOutTime = getMsTime();
    while(pHlsCtx->bListenLoopFlag)
    {
        tsFile.nBufLen = s32TsDuration*BUF_SIZE_1_5M;
        tsFile.bPtsExceptionFlag = HI_FALSE;
        if(pHlsCtx->sendJob.bneedHanleJobFlag)
        {
            if(pHlsCtx->eState != HLS_STATE_LINKED)
            {
                pHlsCtx->eState = HLS_STATE_LINKED;
                HLS_Client_ChangeIP(pHlsCtx, pHlsCtx->sendJob.sendSocket);
            }
            s32Ret = HI_Protocol_HLS_GetTsFileBySeq(pHlsCtx->hHlsHandle, pHlsCtx->sendJob.seqNum, &tsFile);
            if(HI_SUCCESS != s32Ret)
            {
                Printf("HI_Protocol_HLS_GetTsFileBySeq error!\n");
                break;
            }
            if(pHlsCtx->bHandleExceptFlag && tsFile.bPtsExceptionFlag)
            {
                Printf("ts jump happened, ignore this ts file to avoid player stop\n");
                tsFile.nBufLen = TS_SEGMENT_MAXLEN;
                tsFile.bPtsExceptionFlag = HI_FALSE;
                s32Ret = HI_Protocol_HLS_GetTsFileBySeq(pHlsCtx->hHlsHandle, pHlsCtx->sendJob.seqNum-1, &tsFile);
                if(HI_SUCCESS != s32Ret)
                {
                    Printf("HI_Protocol_HLS_GetTsFileBySeq error!\n");
                    break;
                }
            }
            memset(pHeader, 0x00 , 1024);
            HTTP_Protocol_GetReplyHeader(HTTP_RESP_OK, tsFile.nBufLen,  HTTP_CONTENT_TYPE_TEXT,
                tsFile.ETAG, pHeader, HTTP_MAX_HEADER_LEN);
            s32Ret = HTTP_Protocol_Send(pHlsCtx->sendJob.sendSocket, pHeader, strlen(pHeader));
            if(HI_SUCCESS != s32Ret)
            {
                Printf("HI_Protocol_HLS_Send error!\n");
                HLS_Remove_TsSend_Job(pHlsCtx);
                continue;
            }
            Printf("begin send fileSequence%d.ts len: %d \n", pHlsCtx->sendJob.seqNum, tsFile.nBufLen);
            s32Ret = HTTP_Protocol_Send(pHlsCtx->sendJob.sendSocket, tsFile.pBuf ,tsFile.nBufLen);
            if(HI_SUCCESS != s32Ret)
            {
                Printf("HI_Protocol_HLS_Send error!\n");
                HLS_Remove_TsSend_Job(pHlsCtx);
                continue;
            }
            Printf("end send fileSequence%d \n", pHlsCtx->sendJob.seqNum);
            HLS_Remove_TsSend_Job(pHlsCtx);
            /*refresh timeout time*/
            timeOutTime = getMsTime();

        }
        else
        {
            if(getMsTime() -timeOutTime > 3000)
            {
                /*wait for 3s ,no new ts request,just think the last client connection is broken */
                if(pHlsCtx->eState == HLS_STATE_LINKED)
                {
                    Printf("client %s connection end!\n", pHlsCtx->ipStr);
                    pHlsCtx->eState = HLS_STATE_READY;
                }
            }
            if(getMsTime() -timeOutTime > 20000)
            {
                /*wait for 20s ,no new ts request,so stop the source */
                Printf("wait for 10s, there no ts request , just stop the hls refresh!\n");
                break;
            }
            usleep(10000);
        }
        if(pHlsCtx->eState == HLS_STATE_BUTT
            || pHlsCtx->eState == HLS_STATE_ERROR)
        {
            Printf("state %d ,listen thread  exit  \n", pHlsCtx->eState);
            break;
        }
    }
    pHlsCtx->eState = HLS_STATE_STOPING;
    s32Ret =  HLS_closeSource(pHlsCtx);
    if(s32Ret != HI_SUCCESS)
    {
        Printf("HLS_openSource failed \n");
    }
    if(tsFile.pBuf)
    {
        free(tsFile.pBuf);
        tsFile.pBuf = HI_NULL;
    }
    if(pHlsCtx->sendJob.sendSocket >0)
    {
        close(pHlsCtx->sendJob.sendSocket);
        pHlsCtx->sendJob.sendSocket = -1;
    }
    pHlsCtx->sendJob.bneedHanleJobFlag = HI_FALSE;
    HI_Protocol_HLS_Reset(pHlsCtx->hHlsHandle);
    pHlsCtx->bfirstReqFlag = HI_FALSE;
    pHlsCtx->bListenLoopFlag = HI_FALSE;
    pHlsCtx->eState = HLS_STATE_IDLE;
    Printf("HLS_Status_Listen_Thread exit \n");
    return HI_NULL;
}

HI_BOOL HLS_Check_Platform_Change(HlsHandleCtx* phlsCtx, HI_CHAR* pHttpReq)
{
    HlsDeviceType eType = HLS_DEVIECE_BUTT;
    HI_BOOL bchange = HI_FALSE;

    eType = HLS_Parse_DeviceType(pHttpReq);
    if(phlsCtx->eCurType == HLS_DEVIECE_BUTT)
    {
        phlsCtx->eCurType = eType;
    }

    if(phlsCtx->eCurType != eType)
    {
        /*when device type changed between ios5 and ios6, assume
        no platform change*/
        if((HLS_DEVIECE_IOS6 == phlsCtx->eCurType&& HLS_DEVIECE_IOS5 == eType)
            ||(HLS_DEVIECE_IOS5 == phlsCtx->eCurType&& HLS_DEVIECE_IOS6 == eType))
            bchange = HI_FALSE;
        else
            bchange = HI_TRUE;
    }
    return bchange;
}

HI_S32 HLS_Req_Handler_Callback(HI_S32 socket, HI_CHAR* pHttpReq, HI_S32  ReqLen,
    HI_VOID* pUserData, HI_S32 dataLen)
{
    ENTER_SAMPLE_FUNC;
    HI_CHAR pReqStr[4*1024] = {0};
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CHAR pHeader[HTTP_MAX_HEADER_LEN] = {0};

    strncpy(pReqStr, pHttpReq, ReqLen);
    HlsHandleCtx* phlsCtx = (HlsHandleCtx*)pUserData;
    /*if be stoping, wait for state idle*/
    if(phlsCtx->eState == HLS_STATE_STOPING)
    {
        Printf("HLS proto is being reset !\n");
        HTTP_Protocol_GetReplyHeader(HTTP_RESP_NOT_ACCEPTABLE, 0, HI_NULL,
            HI_NULL, pHeader, HTTP_MAX_HEADER_LEN);
        s32Ret = HTTP_Protocol_Send(socket, pHeader,strlen(pHeader));
        if(HI_SUCCESS != s32Ret)
        {
            Printf("HI_Protocol_HLS_Send error!\n");
        }
        close(socket);
        Printf("state is not correct cur: %d, just refuse this connect !\n", phlsCtx->eState);
        return HI_SUCCESS;
    }

    if(HLS_Check_Client_Change(phlsCtx, socket) && phlsCtx->eState == HLS_STATE_LINKED)
    {
        HTTP_Protocol_GetReplyHeader(HTTP_RESP_NOT_ACCEPTABLE, 0, HI_NULL,
            HI_NULL, pHeader, HTTP_MAX_HEADER_LEN);
        s32Ret = HTTP_Protocol_Send(socket, pHeader,strlen(pHeader));
        if(HI_SUCCESS != s32Ret)
        {
            Printf("HI_Protocol_HLS_Send error!\n");
        }
        close(socket);
        Printf("client already connected, just refuse this connect !\n");
        return HI_SUCCESS;
    }

    if(HLS_Check_Client_Change(phlsCtx, socket) && HLS_Check_Platform_Change(phlsCtx, pHttpReq) == HI_TRUE)
    {
        Printf("HLS_Platform_Change happened! listenThreadId: %d \n", (HI_S32)phlsCtx->listenThreadID);
        phlsCtx->bListenLoopFlag = HI_FALSE;
        if(phlsCtx->listenThreadID != 0)
        {
            pthread_join(phlsCtx->listenThreadID, NULL);
            phlsCtx->listenThreadID = 0;
        }
        phlsCtx->bfirstReqFlag = HI_FALSE;
    }
    if(!phlsCtx->bfirstReqFlag)
    {
        if((strstr(pReqStr, HLS_M3U8_FILE_SUFFIX)
            ||(strstr(pReqStr, FILENAME_PRFIX) && strstr(pReqStr, HLS_TS_FILE_SUFFIX))))
        {
            phlsCtx->bListenLoopFlag = HI_TRUE;
            phlsCtx->eCurType = HLS_Parse_DeviceType(pHttpReq);
            s32Ret = pthread_create((pthread_t*)&phlsCtx->listenThreadID,HI_NULL,HLS_Status_Listen_Thread,(HI_VOID*)phlsCtx);
            if (s32Ret != HI_SUCCESS)
            {
                Printf("pthread_create sourceThreadID error.\n");
                return HI_FAILURE;
            }
            HI_S32 s32TimoutTimes = 0;
            while(!HI_Protocol_HLS_IsM3U8FileReady(phlsCtx->hHlsHandle))
            {
                if(s32TimoutTimes > 500)
                {
                    Printf("wait for 10s , m3u8file could not been generated.\n");
                    return HI_FAILURE;
                }
                usleep(20000);
                s32TimoutTimes++;
            }
            phlsCtx->eState = HLS_STATE_READY;
            phlsCtx->bfirstReqFlag = HI_TRUE;
        }
        else
            return HI_FAILURE;
    }

    if(phlsCtx->eState != HLS_STATE_READY
        && phlsCtx->eState != HLS_STATE_LINKED)
    {
        Printf("current state is not right, current eState: %d !\n", phlsCtx->eState);
        return HI_FAILURE;
    }

    if(strstr(pReqStr, HLS_M3U8_FILE_SUFFIX))
    {
        M3U8FileInfo fileInfo;

        Printf("send m3u8 file enter!\n");
        if(phlsCtx->eState != HLS_STATE_LINKED)
        {
            phlsCtx->eState = HLS_STATE_LINKED;
            HLS_Client_ChangeIP(phlsCtx, socket);
        }
        memset(&fileInfo, 0x00, sizeof(M3U8FileInfo));
        fileInfo.nBufLen = MAX_M3U8_FILE_LEN;
        s32Ret = HI_Protocol_HLS_GetLatestM3U8File(phlsCtx->hHlsHandle, &fileInfo);
        if (s32Ret != HI_SUCCESS)
        {
            Printf("HI_Protocol_HLS_GetLatestM3U8File error.\r\n");
            return HI_FAILURE;
        }
        HTTP_Protocol_GetReplyHeader(HTTP_RESP_OK, fileInfo.nBufLen, HTTP_CONTENT_TYPE_APP,
            fileInfo.ETAG, pHeader, HTTP_MAX_HEADER_LEN);
        s32Ret = HTTP_Protocol_Send(socket, pHeader,strlen(pHeader));
        if(HI_SUCCESS != s32Ret)
        {
            Printf("HI_Protocol_HLS_Send error!\n");
        }
        s32Ret = HTTP_Protocol_Send(socket, fileInfo.pBuf, fileInfo.nBufLen);
        if(HI_SUCCESS != s32Ret)
        {
            Printf("HI_Protocol_HLS_Send error!\n");
        }
        Printf("send m3u8 file end!\n");
        close(socket);
    }
    else if(strstr(pReqStr, FILENAME_PRFIX) && strstr(pReqStr, HLS_TS_FILE_SUFFIX))
    {
        HI_CHAR* pBegin = strstr(pReqStr, FILENAME_PRFIX);
        if(!pBegin)
        {
            Printf("could not find %s \n", FILENAME_PRFIX);
            return HI_FAILURE;
        }
        pBegin+=strlen(FILENAME_PRFIX);
        HI_CHAR* pEnd = strstr(pReqStr, HLS_TS_FILE_SUFFIX);
        HI_CHAR seqChar[10] = {0};

        memcpy(seqChar, pBegin, (pEnd -pBegin));
        Printf("parse request file sequence num : %s\n", seqChar);
        HI_U32 fileSeq = atoi(seqChar);

        HLS_Add_TsSend_Job(phlsCtx, fileSeq, socket);
    }
    else
        return HI_FAILURE;
    LEAVE_SAMPLE_FUNC;
    return HI_SUCCESS;
}

HI_S32 HLS_Destroy(HI_HANDLE hlsCtxHdl)
{
    HI_S32 iRet = HI_SUCCESS;

    HlsHandleCtx* pHlsCtx = (HlsHandleCtx*)hlsCtxHdl;
    if(!pHlsCtx)
    {
        Printf("HLS_Destroy input para error!\n");
        return HI_FAILURE;
    }
    pHlsCtx->eState = HLS_STATE_BUTT;
    if(pHlsCtx->listenThreadID != 0)
    {
        pthread_join(pHlsCtx->listenThreadID, NULL);
        pHlsCtx->listenThreadID = 0;
    }

    iRet  = HTTP_Protocol_DeRegist(pHlsCtx->hProtocolHandle, pHlsCtx->hTranscoderHandle);
    if (HI_SUCCESS != iRet )
    {
        Printf("call HTTP_Protocol_DeRegist failed.\n");
    }

    iRet  = HTTP_Protocol_Destroy(pHlsCtx->hProtocolHandle);
    if (HI_SUCCESS != iRet )
    {
        Printf("call HTTP_Protocol_Destroy failed.\n");
    }

    iRet  = HI_Transcoder_Destroy(pHlsCtx->hTranscoderHandle);
    if (HI_SUCCESS != iRet )
    {
        Printf("call HI_Transcoder_Destroy failed.\n");
    }

    iRet  = HI_Transcoder_DeInit();
    if (HI_SUCCESS != iRet)
    {
        Printf("call HI_Transcoder_DeInit failed.\n");
    }
    if(HI_SUCCESS != HI_Protocol_HLS_Destroy(pHlsCtx->hHlsHandle))
    {
        Printf("HI_Protocol_HLS_Destroy err \n");
    }
    free(pHlsCtx);
    return HI_SUCCESS;
}

HI_S32 HLS_Create(HI_HANDLE* pHlsCtxHdl, HI_HANDLE hAvplay)
{
    Transcoder_HandleAttr stTranHandleAttr;
    TsMediaInfo mediaInfo;
    HI_S32 iRet = HI_SUCCESS;

    HlsHandleCtx* pHlsCtx = malloc(sizeof(HlsHandleCtx));
    if(!pHlsCtx)
    {
        Printf("malloc phlsCtx error!\n");
        goto Err_Ret;
    }

    memset(pHlsCtx, 0x00, sizeof(HlsHandleCtx));
    mediaInfo.s32Gop = g_TranOuts32Gop;
    mediaInfo.s32FrameRate = g_TranOuts32VideoFrameRate;
    mediaInfo.s32TsDuration = g_s32DefaultTsDuration;
    mediaInfo.s32MaxTsFileCnt = g_s32DefaultMaxTsFileCnt;
    iRet = HI_Protocol_HLS_Create(&pHlsCtx->hHlsHandle, &mediaInfo);
    if(iRet != HI_SUCCESS)
    {
        Printf("HI_Protocol_HLS_Create  error!\n");
        goto Malloc_Fail;
    }

    iRet  = HI_Transcoder_Init();
    if (HI_SUCCESS != iRet )
    {
        Printf("call HI_Transcoder_Init failed.\n");
        goto HLS_Close;
    }

    memset(&stTranHandleAttr, 0x00 ,sizeof(Transcoder_HandleAttr));
    Transcoder_getDefaultAttr(&stTranHandleAttr);
    stTranHandleAttr.s32Width = g_TranOuts32Width ;
    stTranHandleAttr.s32Height = g_TranOuts32Height ;
    stTranHandleAttr.u32VideoBitRate = g_TranOutu32VideoBitRate ;
    stTranHandleAttr.s32VideoFrameRate =  g_TranOuts32VideoFrameRate;
    stTranHandleAttr.s32AudioSampleRate = g_TranOuts32AudioSampleRate;
    stTranHandleAttr.s32AudioBandWidth = g_TranOuts32AudioBandWidth;
    stTranHandleAttr.s32AudioChannels = g_TranOuts32AudioChannels;
    stTranHandleAttr.hSrc = hAvplay;
    stTranHandleAttr.bCycle = HI_FALSE;
    Printf("~!@#$~!@~!@~! u32VideoBitRate : %d\n",stTranHandleAttr.u32VideoBitRate);
    iRet = HI_Transcoder_Create(&pHlsCtx->hTranscoderHandle,&stTranHandleAttr);
    if (iRet != HI_SUCCESS)
    {
        Printf("call HI_Transcoder_Create failed.\n");
        goto Trans_Deinit;
    }

    ProtocolAttr protoAttr;
    protoAttr.s32Port = 4098;
    protoAttr.s32UserNum = 1;
    protoAttr.SourceHandle = hAvplay;
    protoAttr.u32ProtocolType = TRANSCODER_PROTOCOL_HTTP;
    iRet = HTTP_Protocol_Create(&pHlsCtx->hProtocolHandle,&protoAttr);
    if (iRet != HI_SUCCESS)
    {
        Printf("call HI_Protocol_Create failed.\n");
        goto Trans_Destroy;
    }

    iRet = HTTP_Protocol_Regist(pHlsCtx->hProtocolHandle, pHlsCtx->hTranscoderHandle);
    if (iRet != HI_SUCCESS)
    {
        Printf("call HI_Protocol_Create failed.\n");
        goto Proto_Destroy;
    }

    iRet = HTTP_Protocol_RegistHttpCallback(pHlsCtx->hProtocolHandle, HLS_Req_Handler_Callback,
        (HI_VOID*)pHlsCtx, sizeof(HlsHandleCtx));
    if (iRet != HI_SUCCESS)
    {
        Printf("call HI_Protocol_Create failed.\n");
        goto Proto_Dereg;
    }
    pHlsCtx->eState = HLS_STATE_IDLE;
    pHlsCtx->eCurType = HLS_DEVIECE_BUTT;

    *pHlsCtxHdl = (HI_HANDLE)pHlsCtx;
    return HI_SUCCESS;

Proto_Dereg:
    HTTP_Protocol_DeRegist(pHlsCtx->hProtocolHandle, pHlsCtx->hTranscoderHandle);

Proto_Destroy:
    HTTP_Protocol_Destroy(pHlsCtx->hProtocolHandle);

Trans_Destroy:
    HI_Transcoder_Destroy(pHlsCtx->hTranscoderHandle);

Trans_Deinit:
    HI_Transcoder_DeInit();

HLS_Close:
    HI_Protocol_HLS_Destroy(pHlsCtx->hHlsHandle);

Malloc_Fail:
    free(pHlsCtx);

Err_Ret:
    return HI_FAILURE;
}

HI_VOID HLS_Set_ChannelChangeFlag(HI_HANDLE hlsCtxHdl)
{
    HlsHandleCtx* pHlsCtx = (HlsHandleCtx*)hlsCtxHdl;

    pHlsCtx->bHandleExceptFlag = HI_TRUE;
}

HI_VOID main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                s32Ret = HI_SUCCESS,index;
    HI_HANDLE               hWin = 0;
    HI_HANDLE               hAvplay = 0;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_CHAR                 InputCmd[32];
    HI_UNF_ENC_FMT_E   enFormat = HI_UNF_ENC_FMT_1080i_50;
    HI_U32             ProgNum;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;
    HI_HANDLE hTrack;
    HI_UNF_AENC_ATTR_S stAencAttr;
    AAC_ENC_CONFIG stAACEncCfg;
    Transcoder_HandleAttr stTranHandleAttr;
    ProtocolAttr protoAttr;
    g_fileName[0] = '\0';
    for(index = 1;index < argc;index++)
    {
        ParseCmd(argv[index]);
    }
    if (0 == strlen(g_fileName))
    {
        printf("Usage: sample_transcoder_hlsplayer file=test.ts [w=1280] [h=720]  [b=4*1024*1024]\n"
                    "w:width:320|640|720|1280|1920\n"
                    "h:height:240|480|576|720|1080\n"
                    "b:videorbitrate:256*1024|512*1024|1024*1024|2*1024*1024|4*1024*1024|8*1024*1024"
               );
        printf("Example:./sample_transcoder_hlsplayer file=test.ts  w=1280 h=720 b=4*1024*1024\n");
        return ;
    }
    g_pTsFile = fopen(g_fileName, "rb");
    if (!g_pTsFile)
    {
        printf("open file %s error!\n", argv[1]);
        return ;
    }

    HI_SYS_Init();

        //HI_SYS_PreAV(NULL);
    s32Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call SndInit failed.\n");
        goto SYS_DEINIT;
    }

    s32Ret = HIADP_Disp_Init(enFormat);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HIADP_Disp_Init failed.\n");
        goto SND_DEINIT;
    }

    s32Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    s32Ret |= HIADP_VO_CreatWin(HI_NULL,&hWin);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call VoInit failed.\n");
        HIADP_VO_DeInit();
        goto VO_DEINIT;
    }

    s32Ret = HI_UNF_DMX_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_DMX_Init failed.\n");
        goto DISP_DEINIT;
    }
    s32Ret |= HI_UNF_DMX_AttachTSPort(PLAY_DMX_ID,HI_UNF_DMX_PORT_RAM_0);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_DMX_AttachTSPort failed.\n");
        goto VO_DEINIT;
    }

    s32Ret = HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_RAM_0, 0x200000, &g_TsBuf);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_DMX_CreateTSBuffer failed.\n");
        goto DMX_DEINIT;
    }

    s32Ret = HIADP_AVPlay_RegADecLib();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call RegADecLib failed.\n");
        goto TSBUF_FREE;
    }

    s32Ret = HI_UNF_AVPLAY_Init();
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto DMX_DEINIT;
    }

    s32Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    AvplayAttr.u32DemuxId = PLAY_DMX_ID;
    AvplayAttr.stStreamAttr.u32VidBufSize = (3*1024*1024);
    s32Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }
    g_hAvplay = hAvplay;
    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto AVPLAY_DESTROY;
    }

    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto VCHN_CLOSE;
    }
    s32Ret = HI_UNF_VO_AttachWindow(hWin, hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_VO_AttachWindow failed:%#x.\n",s32Ret);
    }
    s32Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }
    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto WIN_DETACH;
    }
    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto WIN_DETACH;
    }

    s32Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_SND_Attach failed.\n");
        goto WIN_DETACH;
    }

    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    s32Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }
    pthread_mutex_init(&g_TsMutex,NULL);
    g_bStopTsThread = HI_FALSE;
    pthread_create(&g_TsThd, HI_NULL, (HI_VOID *)TsTthread, HI_NULL);
    HIADP_Search_Init();
    s32Ret = HIADP_Search_GetAllPmt(PLAY_DMX_ID, &g_pProgTbl);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HIADP_Search_GetAllPmt failed.\n");
        goto PSISI_FREE;
    }

    ProgNum = 0;

    pthread_mutex_lock(&g_TsMutex);
    rewind(g_pTsFile);
    s32Ret = HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_DMX_ResetTSBuffer failed.\n");
        goto MUTX_UNLOCK;
    }

    s32Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum,HI_TRUE);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call SwitchProg failed.\n");
        goto AVPLAY_STOP;
    }

    pthread_mutex_unlock(&g_TsMutex);

    HI_HANDLE hlsCtx = 0;
    s32Ret = HLS_Create(&hlsCtx, hAvplay);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HLS_Create failed.\n");
        goto AVPLAY_STOP;
    }
    g_hHlsCtxHandle = hlsCtx;
    printf("begin wait for network req\n");
    for(;;)
    {
        printf("please input the q to quit!\n");
        fgets(InputCmd, 30, stdin);
        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
    }
    g_bStopTsThread = HI_TRUE;
    pthread_join(g_TsThd,0);

    HLS_Destroy(hlsCtx);

    #if 1
AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);
    #endif
MUTX_UNLOCK:
    pthread_mutex_unlock(&g_TsMutex);
PSISI_FREE:
    printf("PSISI_FREE begin!!\n");
    HIADP_Search_DeInit();
    g_bStopTsThread = HI_TRUE;
//    pthread_join(g_TsThd, HI_NULL);
    pthread_mutex_destroy(&g_TsMutex);
    printf("PSISI_FREE finish!!\n");
SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);

TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);
WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(hWin,HI_FALSE);
    s32Ret = HI_UNF_VO_DetachWindow(hWin, hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_VO_DetachWindow failed:%#x.\n",s32Ret);
    }
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

VCHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

AVPLAY_DESTROY:
    HI_UNF_AVPLAY_Destroy(hAvplay);

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

TSBUF_FREE:
    HI_UNF_DMX_DestroyTSBuffer(g_TsBuf);

DMX_DEINIT:
    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();

VO_DEINIT:
    HI_UNF_VO_DestroyWindow(hWin);
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

SND_DEINIT:
    HIADP_Snd_DeInit();

SYS_DEINIT:
    HI_SYS_DeInit();

    fclose(g_pTsFile);
    g_pTsFile = HI_NULL;

    return 1;
}
