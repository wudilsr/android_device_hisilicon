#ifndef __RTSP_COMMON_H
#define __RTSP_COMMON_H


#include "hi_list.h"
#include "hi_rtp.h"
#include "hi_type.h"
#define ERR_RTSP_PARAMETER      (-1)
#define ERR_RTSP_CONFIG                (-2)
#define ERR_RTSP_MEMORY             (-3)
#define ERR_RTSP_PROCFAILURE   (-4)
#define ERR_RTSP_BYE            (-5)
#define SUCCESS                                     (0)
#define SUC_IGNORE                             (1)
#define MAX_Attribute_NUM               (50)
#define SIZE_AUDIO_PACK                 (32)

#define RTPBufferSize (1024*1024)
#define BufferSize 1024*2
#define DefaultClientNum 8
#define ServerPort 4098
#define DefaultVideoRTCPPort    1211
#define DefaultAudioRTCPPort    1213
#define DefaultVideoRTPPort        1210
#define DefaultAudioRTPPort        1212
#define DefaultAudioSSRC         0x00136937
#define DefaultVedioSSRC        0x00133790

typedef HI_U64      U64;
typedef HI_U32 U32;
typedef HI_U16 U16;
typedef HI_S16 S16;
typedef HI_U8 U8;
typedef HI_S32 S32;


typedef enum E_RTSP_SERVER_SORT
{
    Darwin_Server,
    HI_Rtsp_Server,
    UnKnown
}RTSP_SvrSort;
typedef enum E_RTSP_OUTPUT_SORT
{
    LocalHost,
    HI_Rtsp_VO,
    UnKnownVO
}RTSP_OUTSort;

typedef enum E_RTSP_CLIENT_STATUS
{
    RTSP_CLIENT_INIT = 0,
    RTSP_CLIENT_OPTION = 1,
    RTSP_CLIENT_GET_PARAMETER ,
    RTSP_CLIENT_SET_PARAMETER,
    RTSP_CLIENT_DESCRIBE,
    RTSP_CLIENT_SETUP,
    RTSP_CLIENT_READY,
    RTSP_CLIENT_PLAY,
    RTSP_CLIENT_PAUSE,
    RTSP_SERVER_GET_PARAMETER,
    RTSP_SERVER_SET_PARAMETER,
    RTSP_CLIENT_TEARDOWN,
    RTSP_CLIENT_BUTT
}RTSP_CLIENT_STATUS;

typedef enum E_RTSP_SETPARA_COMMAND
{
    SETPARA_COMMAND_RESET = 0,
    SETPARA_COMMAND_PAUSE = 1,
    SETPARA_COMMAND_CHANGE_AUDIOTRACK,
    SETPARA_COMMAND_SEEK,
    SETPARA_COMMAND_BUTT
}RTSP_SETPARA_COMMAND;

typedef enum E_RTSP_RESPONSE_STATUS
{
    RTSP_RESPONSE_INIT = 0,
    RTSP_RESPONSE_OK = 200,
    RTSP_RESPONSE_ERR = 400,
    RTSP_RESPONSE_BAD = 404,
    RTSP_RESPONSE_OPTION = 501,
    RTSP_RESPONSE_BUTT
}RTSP_RESPONSE_STATUS;

typedef enum E_RTSP_TRACK_TYPE
{
    TRACK_INIT = 0,
    TRACK_AUDIO,
    TRACK_VIDEO,
    TRACK_BUTT
}RTSP_TRACK_TYPE;

typedef enum E_RTCP_TRACK_STAUTS
{
    RTCP_INIT,
    RTCP_SEND_REPORT,
    RTCP_REPECT_REPORT,
    RTCP_GOODBYE,
    RTCP_BUTT
}RTCP_TRACK_STAUTS;

typedef enum E_Media_Type
{
    H264_MODE = 1,
    AMR_MODE = 2,
    AAC_MODE = 3,
    MP4_MODE = 4,
    BUTT_MODE
}MEDIA_TYPE;

typedef struct F_RTCP_LIVE_KEEPER
{
    RTCP_TRACK_STAUTS                           eRTCPStatus;
    RTSP_TRACK_TYPE                                eMediaStype;
    U32                                            u32RTPNumKeep;
    U32                                            u32SSRC;
    S32                                            s32STransit;
    U32                                            s32Jitter;
    U32                                         u32LastSeq;
    //need init in sr get
    S32                                            s32BeginTimeStamp;
    S32                                            s32BegineNPTTime;

    S32                                            u32RightNowTimeStamp;
    //need init in play rtsp response
    U32                                         u32HighestSeq;
    U32                                            u32BeginSeq;
    U32                                            u32Fraction;
    U32                                            u32LastSRNPTTime;
    U32                                            u32LastRRMPTtime;
    U32                                            u32DelaySR;
    //need init in init
    S32                                            U32RTPTotal;
    U32                                            u32SRTimeBegin;
    U32                                            u32RTPOctNum;
    U32                                            u32RTPPackNum;
}RTCP_LIVE_KEEPER;

typedef struct F_RTSP_TRACK_S
{
    U32                    u32Profile_Level_id;
    U32                    u32Track_As;
    U32                    u32FTMP;
    U32                    u32TrackId;
    U32                 u32Vechn;
    U32                    u32RTPtimeStamp;
    RTSP_TRACK_TYPE        eTrackStype;
    MEDIA_TYPE          eMediaSort;
    U32                    u32RTCPSock;
    U32                    u32RTCPSvrSock;
    U32                    u32RTPSock;
    U32                    u32FrameTotal;
    U32                    u32FrameLost;
    U32                 u32RTPend;
    U32                 u32RTPBegin;
    RTCP_LIVE_KEEPER*    sRTCPKeeper;
    U32                    eSvrTrackType;
    U32                    u32RTPLastTimeStamp;
    U8                    strRTP_MAP[64];
    U8                    strTrack_Config[200];
    U8                              strSPSTags[256];
    U32                 SPSlen;
    U32                 PPSlen;
    U32                 u32RTPPort;
    struct S_Cliprec
    {
        U32        RecX;
        U32        RecY;
        U32        Height;
        U32        Width;
    }sPrec;
}RTSP_TRACK_S;




#endif
