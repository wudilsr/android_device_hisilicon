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

//#include "hi_rtsp_wfd.h"
#define  PLAY_DMX_ID  0

pthread_t   g_TsThd;
pthread_mutex_t g_TsMutex;
HI_BOOL     g_bStopTsThread = HI_FALSE;
HI_HANDLE          g_TsBuf;
HI_HANDLE          g_hAvplay;
HI_HANDLE          g_hLayer;
HI_HANDLE g_hTranHandle;
HI_HANDLE hProtoHandle;
PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;
FILE               *g_pTsFile = HI_NULL;
HI_S32 vid_width = 0;
HI_S32 vid_height = 0;
HI_S32 vid_bitrate = 0;
HI_S32 aud_sampleRate = 0;


HI_CHAR g_fileName[32];
HI_CHAR g_ImgName[32];
HI_S32 g_TranOuts32X;                    /*转码的起始位置 X 坐标*/
HI_S32 g_TranOuts32Y;                    /*转码的起始位置 Y 坐标*/
HI_S32 g_TranOuts32Width = 720;                /*视频分辨率--高*/
HI_S32 g_TranOuts32Height = 576;               /*视频分辨率--宽*/
HI_U32 g_TranOutu32VideoBitRate = 1024 * 1024;             /*视频比特率*/
HI_S32 g_TranOuts32VideoFrameRate = 30;           /*视频帧率*/
HI_S32 g_TranOuts32AudioSampleRate = 48000;          /*音频采样率*/
HI_S32 g_TranOuts32AudioBandWidth = 16;           /*音频采样宽度*/
HI_S32 g_TranOuts32AudioChannels = 2;            /*音频采样的声道数量*/
HI_S32 g_TranOuts32Gop = 10;                    /*I帧间隔*/
Transcoder_ProtocolType g_TranProtocolType = TRANSCODER_PROTOCOL_BUTT;

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
    stTranHandleAttr->s32Gop = 10;
    stTranHandleAttr->SourceType = 0;
    stTranHandleAttr->bCycle = HI_FALSE;
}
HI_S32 print_failed(HI_S32 ret, const char *func, HI_S32 line)
{

    printf("\e[33;1mFailed: 0x%X, %s, %d\n\e[0m", ret, func, line);

    return 0;
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
    const char* pgop = "gop=";

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
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pVideoFrameRate)))
    {
        pTmpPoint += strlen((char*)pVideoFrameRate);
        g_TranOuts32VideoFrameRate = atoi(pTmpPoint);
        printf("tran video framerate : %d\n",g_TranOuts32VideoFrameRate);
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

        memcpy(g_fileName,pTmpPoint,strlen(pTmpPoint) + 1);
        printf("tran file name : %s\n",g_fileName);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)protocol)))
    {
        pTmpPoint += strlen((char*)protocol);
        if(HI_NULL != strstr(pTmpPoint,(char*)"http"))
        {
            g_TranProtocolType = TRANSCODER_PROTOCOL_HTTP;
        }
        else if(HI_NULL != strstr(pTmpPoint,(char*)"rtsp"))
        {
            g_TranProtocolType = TRANSCODER_PROTOCOL_RTSP;
        }
        else if(HI_NULL != strstr(pTmpPoint,(char*)"local"))
        {
            g_TranProtocolType = TRANSCODER_PROTOCOL_SAMPLE;
        }
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pband)))
    {
        pTmpPoint += strlen((char*)pband);
        g_TranOuts32AudioBandWidth = atoi(pTmpPoint);
        printf("audio  pband : %d\n",g_TranOuts32AudioBandWidth);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pgop)))
    {
        pTmpPoint += strlen((char*)pgop);
        g_TranOuts32Gop = atoi(pTmpPoint);
        printf("tran video pgop : %d\n",g_TranOuts32Gop);
    }
    else
    {
        printf("parse error!!! argv : %s\n",pCommandStr);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

HI_VOID main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                s32Ret = HI_SUCCESS,index = 0;
    HI_HANDLE               hWin = 0;
    HI_HANDLE               hAvplay = 0;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_CHAR                 InputCmd[32] = {0};
    HI_UNF_ENC_FMT_E   enFormat = HI_UNF_ENC_FMT_1080i_50;
    HI_U32             ProgNum = 0;
    HI_UNF_AENC_ATTR_S stAencAttr;
    AAC_ENC_CONFIG stAACEncCfg;
    Transcoder_HandleAttr stTranHandleAttr;
    ProtocolAttr protoAttr;
    g_fileName[0] = '\0';
    g_ImgName[0] = '\0';
    HI_U32 value;
    HI_CHAR    InputValue[32];
    for(index = 1;index < argc;index++)
    {
        ParseCmd(argv[index]);
    }

    if (g_TranProtocolType == TRANSCODER_PROTOCOL_BUTT)
    {
        printf("Usage: sample_transcoder_osdplayer  [w=1280] [h=720 ] [f=25] [b=4*1024*1024] [pro=http]\n"
                    "pro:protocol:rtsp|http|local\n"
                    "w:width:320|640|720|1280|1920\n"
                    "h:height:240|480|576|720|1080\n"
                    "f:framerate:10|15|20|25|30\n"
                    "b:videorbitrate:256*1024|512*1024|1024*1024|2*1024*1024|4*1024*1024|8*1024*1024\n"
               );
        printf("Example:./sample_transcoder_osdplayer  f=25 w=1280 h=720 pro=rtsp b=4*1024*1024\n");
        return ;
    }

    FILE* pImgFile = NULL;
    /*-------------common init---------*/
    HI_SYS_Init();
    //HI_SYS_PreAV(NULL);
    s32Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call SndInit failed.\n");
        goto SYS_DEINIT;
    }
    #if 1
    s32Ret = HI_UNF_DISP_Init();
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_DISP_Init failed.\n");
        goto SND_DEINIT;
    }

   // s32Ret |= HI_UNF_DISP_SetLayerZorder(HI_UNF_DISP_HD0, HI_UNF_DISP_LAYER_OSD_0, HI_LAYER_ZORDER_MOVETOP);
    s32Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);

   s32Ret |= HIADP_VO_CreatWin(HI_NULL,&hWin);
    if (HI_SUCCESS != s32Ret)
    {
       printf("call VoInit failed.\n");

       HIADP_VO_DeInit();
       goto DISP_DEINIT;
    }

    #endif
    /*-------------avplay video init---------*/
#if 0
    s32Ret |= HIADP_VO_CreatWin(HI_NULL,&hWin);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call VoInit failed.\n");
        HIADP_VO_DeInit();
        goto DISP_DEINIT;
    }

    s32Ret = HI_UNF_DMX_Init();
    s32Ret |= HI_UNF_DMX_AttachTSPort(PLAY_DMX_ID,3);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call VoInit failed.\n");
        goto VO_DEINIT;
    }

    s32Ret = HI_UNF_DMX_CreateTSBuffer(3, 0x200000, &g_TsBuf);
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
        goto TSBUF_FREE;
    }

    s32Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    AvplayAttr.u32DemuxId = PLAY_DMX_ID;
    AvplayAttr.stStreamAttr.u32VidBufSize = (9*1024*1024);
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
        goto VCHN_CLOSE;
    }
    s32Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }
    s32Ret = HI_UNF_SND_Attach(HI_UNF_SND_0, hAvplay, HI_UNF_SND_MIX_TYPE_MASTER, 100);
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
    HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    pthread_mutex_unlock(&g_TsMutex);
    s32Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum,HI_TRUE);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call SwitchProg failed.\n");
        goto AVPLAY_STOP;
    }
#endif
    /*-------------osd image layer init---------*/
#if 0
    s32Ret = HI_GO_Init();
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_GO_Init failed.\n");
        goto AVPLAY_STOP;
    }
    s32Ret = show_pic();
    if (s32Ret != HI_SUCCESS)
    {
        printf("call show_pic failed.\n");
        goto HIGO_DEINIT;
    }
    s32Ret = HI_UNF_VO_SetAlpha(HI_UNF_VO_HD0, 128);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_SetAlpha failed.\n");
        goto PIC_DEINIT;
    }
#endif
    /*-------------HiTranscoder init---------*/
    memset(&stTranHandleAttr,0,sizeof(Transcoder_HandleAttr));
    s32Ret = HI_Transcoder_Init();
    if(HI_SUCCESS != s32Ret)
    {
        printf("Test_Trans_Init error\n");
        goto PIC_DEINIT;
    }
    Transcoder_SetDefaultAttr(&stTranHandleAttr);
    stTranHandleAttr.u32VideoBitRate = g_TranOutu32VideoBitRate;
    stTranHandleAttr.s32AudioSampleRate = g_TranOuts32AudioSampleRate;
    stTranHandleAttr.s32Width = g_TranOuts32Width;
    stTranHandleAttr.s32Height= g_TranOuts32Height;
    stTranHandleAttr.s32AudioChannels = g_TranOuts32AudioChannels;
    stTranHandleAttr.s32VideoFrameRate = g_TranOuts32VideoFrameRate;
    stTranHandleAttr.s32Gop = g_TranOuts32Gop;
    stTranHandleAttr.SourceType = TRANSCODER_SOURCE_OSD_VO_PCM;
    stTranHandleAttr.hSrc = 0;
    printf("HI_Transcoder_Create enter u32VideoBitRate : %d\n",stTranHandleAttr.u32VideoBitRate);
    s32Ret = HI_Transcoder_Create(&g_hTranHandle,&stTranHandleAttr);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Transcoder_Create error\n");
        goto TRANS_DEINIT;
    }
    printf("HI_Transcoder_Create success\n");


    s32Ret = HI_Protocol_Init();
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Protocol_Init error\n");
        goto TRANS_DESTROY;
    }
    if(g_TranProtocolType == TRANSCODER_PROTOCOL_SAMPLE)
    {
        s32Ret = HI_Protocol_RegistProtocol("libprotocol_local.so");
        if(HI_SUCCESS != s32Ret)
        {
           printf("HI_Protocol_RegistProtocol error!\n");
        }
    }
    s32Ret = HI_Muxer_Init();
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Muxer_Init error\n");
        goto PROTOCOL_DEINIT;
    }
    protoAttr.s32Port = 4098;
    protoAttr.s32UserNum = 8;
    protoAttr.SourceHandle = g_hAvplay;
    protoAttr.u32ProtocolType = g_TranProtocolType;

    printf("HI_Protocol_Create enter\n");
    s32Ret = HI_Protocol_Create(&hProtoHandle,&protoAttr);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Protocol_Create error\n");
        goto MUXER_DEINIT;
    }
    printf("HI_Protocol_Create success\n");

    s32Ret = HI_Protocol_RegistHandle(hProtoHandle,g_hTranHandle);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Protocol_RegistHandle error\n");
        goto PROTOCOL_DESTROY;
    }
    printf("begin wait for network req\n");
    for(;;)
    {
        printf("please input the 'q' to quit,'r'to set resolution ratio,'f' to set frameRate,'b'to set biteRate,'g'to set gop!\n");
        fgets(InputCmd, 30, stdin);
        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
        switch(InputCmd[0])
        {
            case 'b':
                printf("please input the biteRate value,eg:350000,4000000,10000000\n");
                fgets(InputValue, 30, stdin);
                value = atoi(InputValue);
                if((value < 32*1024)||(value > 42*1024*1024))
                {
                    printf("input the wrong biteRate value\n");
                }
                else
                {
                    s32Ret = HI_Transcoder_GetAttr((HI_HANDLE)g_hTranHandle,TRANSCODER_ALL_ATTR, &stTranHandleAttr);
                    if(HI_SUCCESS != s32Ret)
                    {
                        printf("HI_Transcoder_GetAttr failed\n");
                        continue;
                    }
                    stTranHandleAttr.u32VideoBitRate = value;
                    s32Ret = HI_Transcoder_SetAttr( (HI_HANDLE)g_hTranHandle,TRANSCODER_ALL_ATTR,&stTranHandleAttr);
                    if(HI_SUCCESS != s32Ret)
                    {
                        printf("HI_Transcoder_SetAttr failed\n");
                    }
                }
                continue;
            case 'f':
                printf("please input the frameRate value\n");
                fgets(InputValue, 30, stdin);
                value = atoi(InputValue);
                if((value < 1)||(value > 60))
                {
                    printf("input the wrong  frameRate value\n");
                }
                else
                {
                    s32Ret = HI_Transcoder_GetAttr((HI_HANDLE)g_hTranHandle,TRANSCODER_ALL_ATTR, &stTranHandleAttr);
                    if(HI_SUCCESS != s32Ret)
                    {
                        printf("HI_Transcoder_GetAttr failed\n");
                        continue;
                    }
                    stTranHandleAttr.s32VideoFrameRate = value;
                    s32Ret = HI_Transcoder_SetAttr( (HI_HANDLE)g_hTranHandle,TRANSCODER_ALL_ATTR,&stTranHandleAttr);
                    if(HI_SUCCESS != s32Ret)
                    {
                        printf("HI_Transcoder_SetAttr failed\n");
                    }
                }
                continue;
            case 'r':
                printf("Usage:suggest resolution ratio is :\n"
                      "QCIF:176*144,CIF:352*288,QVGA:320*240,VGA:640*480,D1:720*576,720P:1280*720,1080P:1920*1080\n"
                "please input the width value first\n");
                fgets(InputValue, 30, stdin);
                value = atoi(InputValue);
                if((value < 176)||(value > 1920))
                {
                    printf("input the wrong width value\n");
                    continue;
                }
                else
                {
                    s32Ret = HI_Transcoder_GetAttr((HI_HANDLE)g_hTranHandle,TRANSCODER_ALL_ATTR, &stTranHandleAttr);
                    if(HI_SUCCESS != s32Ret)
                    {
                        printf("HI_Transcoder_GetAttr failed\n");
                        continue;
                    }
                    stTranHandleAttr.s32Width = value;
                }
                printf("then please input the height value \n");
                fgets(InputValue, 30, stdin);
                value = atoi(InputValue);
                if((value < 144)||(value > 1088))
                {
                    printf("input the wrong height value\n");
                }
                else
                {
                    stTranHandleAttr.s32Height = value;
                    s32Ret = HI_Transcoder_SetAttr( (HI_HANDLE)g_hTranHandle,TRANSCODER_ALL_ATTR,&stTranHandleAttr);
                    if(HI_SUCCESS != s32Ret)
                    {
                        printf("HI_Transcoder_SetAttr failed\n");
                    }

                }
                continue;
            case 'g':
                printf("please input the GOP value\n");
                fgets(InputValue, 30, stdin);
                value = atoi(InputValue);
                if((value < 1)||(value > 65535))
                {
                    printf("input the wrong gop value\n");
                }
                else
                {
                    s32Ret = HI_Transcoder_GetAttr((HI_HANDLE)g_hTranHandle,TRANSCODER_ALL_ATTR, &stTranHandleAttr);
                    if(HI_SUCCESS != s32Ret)
                    {
                        printf("HI_Transcoder_GetAttr failed\n");
                        continue;
                    }
                    stTranHandleAttr.s32Gop= value;
                    s32Ret = HI_Transcoder_SetAttr( (HI_HANDLE)g_hTranHandle,TRANSCODER_ALL_ATTR,&stTranHandleAttr);
                    if(HI_SUCCESS != s32Ret)
                    {
                        printf("HI_Transcoder_SetAttr failed\n");
                    }
                }
                continue;
        }
    }
    g_bStopTsThread = HI_TRUE;
    //pthread_join(g_TsThd,0);
    s32Ret = HI_Protocol_UnRegistHandle(hProtoHandle,g_hTranHandle);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Protocol_UnRegistHandle error\n");
    }

PROTOCOL_DESTROY:
    s32Ret = HI_Protocol_destory(hProtoHandle);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Protocol_destory error\n");
    }

MUXER_DEINIT:
    s32Ret = HI_Muxer_DeInit();
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Muxer_DeInit error\n");
    }

PROTOCOL_DEINIT:
    s32Ret = HI_Protocol_DeInit();
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Protocol_DeInit error\n");
    }

TRANS_DESTROY:
    s32Ret = HI_Transcoder_Destroy(g_hTranHandle);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Transcoder_Destroy error\n");
    }

TRANS_DEINIT:
    s32Ret = HI_Transcoder_DeInit();
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_Transcoder_DeInit error\n");
    }

PIC_DEINIT:
    //HI_GO_DestroyLayer(g_hLayer);

HIGO_DEINIT:
    //HI_GO_Deinit();
    #if 0
AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

PSISI_FREE:
    printf("PSISI_FREE begin!!\n");
    HIADP_Search_DeInit();
    g_bStopTsThread = HI_TRUE;
//    pthread_join(g_TsThd, HI_NULL);
    pthread_mutex_destroy(&g_TsMutex);
    printf("PSISI_FREE finish!!\n");
SND_DETACH:
    HI_UNF_SND_Detach(HI_UNF_SND_0, hAvplay);

WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(hWin,HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, hAvplay);

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
#endif


VO_DEINIT:
    HI_UNF_VO_DestroyWindow(hWin);
    HIADP_VO_DeInit();

DISP_DEINIT:
    HI_UNF_DISP_DeInit();


SND_DEINIT:
    HIADP_Snd_DeInit();

SYS_DEINIT:
    HI_SYS_DeInit();
    if(g_pTsFile)
        fclose(g_pTsFile);
    g_pTsFile = HI_NULL;

    return ;
}
