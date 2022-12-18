#ifndef __HI_SVR_PROC_H__
#define __HI_SVR_PROC_H__

#include "hi_type.h"


typedef struct hiSVR_PLAYER_PROC_SEEKINFO_S
{
//trace seek
    HI_U32      u32DoReadSeek;
    HI_U32      u32ReadSeekDone;
    HI_U32      u32DoSeekFrameBinary;  //ff_seek_frame_binary
    HI_U32      u32SeekFrameBinaryDone;
    HI_U32      u32DoSeekFrameGeneric;
    HI_U32      u32SeekFrameGenericDone;
//trace switch-pg
    HI_U32      u32DoInitInput;
    HI_U32      u32DoAvioOpenH;
    HI_U32      u32AvioOpenHDone;
    HI_U32      u32DoAvProbeInputBuffer;
    HI_U32      u32AvProbeInputBufferDone;
    HI_U32      u32FindEndPtsStart;
    HI_U32      u32FindEndPtsDone;
    HI_U32      u32EstimateDurationStart;
    HI_U32      u32EstimateDurationDone;
    HI_U32      u32DoPAdaptStart;
    HI_U32      u32DoPAdaptStartDone;
    HI_U32      u32FirstVidFrameRead;
    HI_U32      u32FirstAudFrameRead;
    HI_U32      u32FirstVidFrameSent;
    HI_U32      u32FirstAudFrameSent;

//for hi_svr_format
    HI_U32      u32DoHiSvrFormatSeekPts;
    HI_U32      u32CmdSeek;
    HI_U32      u32DoAvformatOpenInput;
    HI_U32      u32AvformatOpenInputDone;
    HI_U32      u32DoSvrFormatFindStream;
    HI_U32      u32SvrFormatFindStreamDone;
    HI_U32      u32DoSvrFormatGetFileInfo;
    HI_U32      u32SvrFormatGetFileInfoDone;

} HI_SVR_PLAYER_PROC_SEEKINFO_S;


typedef enum hiSVR_PLAYER_PROC_SWITCHPG_INFOTYPE_E
{
    HI_SVR_PLAYER_PROC_DO_STOP=1,
    HI_SVR_PLAYER_PROC_HIMEDIAPLAYER_CONSTRUCT,
    HI_SVR_PLAYER_PROC_SETDATASOURCE,
    HI_SVR_PLAYER_PROC_UNF_AVPLAY_CREATE,
    HI_SVR_PLAYER_PROC_DO_PREPARE,
    HI_SVR_PLAYER_PROC_PREPARE_ASYNC_COMPLETE,
    HI_SVR_PLAYER_PROC_DO_START_ENTER,
    HI_SVR_PLAYER_PROC_PLAYER_STATE_PLAY,
    HI_SVR_PLAYER_PROC_MEDIA_INFO_FIRST_FRAME_TIME,
    HI_SVR_PLAYER_PROC_DO_RESET,
    HI_SVR_PLAYER_PROC_DO_DESTRUCTOR,

} HI_SVR_PLAYER_PROC_SWITCHPG_INFOTYPE_E;

typedef struct hiSVR_PLAYER_PROC_SWITCHPG_S
{
    HI_SVR_PLAYER_PROC_SWITCHPG_INFOTYPE_E eType;
    HI_U32 u32DoStop;       //1
    HI_U32 u32HiMediaPlayerConstruct; //2
    HI_U32 u32SetDataSource;        //3
    HI_U32 u32DoCreateAVPlay;  //4
    HI_U32 u32DoPrepare;            //5
    HI_U32 u32prepareAsyncComplete; //6
    HI_U32 u32DoStartEnter;         //7
    HI_U32 u32PlayedEvent;  //8
    HI_U32 u32FirstFrameTime;  //9
    HI_U32 u32DoReset;              //10
    HI_U32 u32DoDestructor;         //11

} HI_SVR_PLAYER_PROC_SWITCHPG_S;



#endif /* __HI_SVR_PROC_H__ */
