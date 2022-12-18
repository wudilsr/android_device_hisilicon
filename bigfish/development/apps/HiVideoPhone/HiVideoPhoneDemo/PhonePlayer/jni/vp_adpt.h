#ifndef VP_ADPT_H
#define VP_ADPT_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_unf_common.h"

#define AUD_DEV_PLAYBACK_DIRECTION  0
#define AUD_DEV_CAPTURE_DIRECTION   1
#define AUD_DEV_DEF_INDEV_NUM       0
#define AUD_DEV_DEF_OUTDEV_NUM      0

typedef enum hiADP_ENGINE_STATE_E
{
    HI_ENGINE_INITED = 0x1,
    HI_ENGINE_OPENED = 0x2,
    HI_ENGINE_STARTED = 0x4,
    HI_ENGINE_BUTT = 0x0
} HI_ADP_ENGINE_STATE_E;

typedef enum hiADP_RESOLUTION_E
{
    HI_RESOLUTION_176_144 = 0,
    HI_RESOLUTION_320_240,
    HI_RESOLUTION_352_288,
    HI_RESOLUTION_640_480,
   // HI_RESOLUTION_720_576,
    HI_RESOLUTION_1280_720,
    HI_RESOLUTION_1920_1080,
    HI_RESOLUTION_BUTT
}HI_ADP_RESOLUTION_E;

typedef enum hiADP_OPTIONAL_CONFIG_E
{
    HI_OPTIONAL_CONFIG_VENC_PROFILE = 0,
    HI_OPTIONAL_CONFIG_RTP_SPLIT_SIZE,
    HI_OPTIONAL_CONFIG_RTP_RECVBUF_SIZE,
    HI_OPTIONAL_CONFIG_RTP_RECVBUF_NUM,
    HI_OPTIONAL_CONFIG_RTP_SORT_DEPTH,
    HI_OPTIONAL_CONFIG_NET_IP_TYPE,
    HI_OPTIONAL_CONFIG_BUTT
}HI_ADP_OPTIONAL_CONFIG_E;

typedef struct
{
    HI_U32 u32AudDevId;                         /* HI_UNF_VOIP_AUDIO_DEVICE_E */
    HI_S32 s32SndCardNo;                        /* ALSA sound card number */
    HI_U32 u32AudDevTpye;                       /* HI_VOIP_AUDIO_DEVICE_TYPE_E */
    HI_CHAR szName[30];   /*card name*/
}HI_AUD_DEV_INFO_S;

typedef enum hiADP_STATICS_E
{
    PACKET_INRATE = 0,
    PACKET_OUTRATE,
    PACKET_INLOSTRATE ,
    PACKET_INDELAYTIME,
    VIDEO_WIDTH,
    VIDEO_HEIGHT,
    STATIC_BUTT
}HI_ADP_STATICS_E;

HI_S32 Hi_Adp_Video_Init(HI_VOID);
HI_S32 Hi_Adp_Video_Deinit(HI_VOID);
HI_S32 Hi_Adp_Video_Open(HI_RECT_S stLocalWinRect, HI_RECT_S stRemotewinRect,  HI_ADP_RESOLUTION_E eSetRes, HI_S32 s32VoFormat, HI_U32 u32CapFmRate);
HI_S32 Hi_Adp_Video_Close();
HI_S32 Hi_Adp_Video_Start(const HI_CHAR *pLoacalIp, HI_S32 s32LoalPort,const HI_CHAR *pRemoteIp, HI_S32 s32RemotePort, 
                                     HI_S32 s32EncFR, HI_S32 s32Payload, HI_S32 s32TargetBR, HI_S32 s32Gop);
HI_S32 Hi_Adp_Video_Stop(HI_VOID);

HI_S32 Hi_Adp_Video_EnableLocal(HI_BOOL bEnable);
HI_S32 Hi_Adp_Video_EnableRemote(HI_BOOL bEnable);

HI_S32 Hi_Adp_Video_SetWindowShow(HI_S32 lrwindow, HI_S32 showorhide);
HI_S32 Hi_Adp_Video_SetWindowZorder(HI_S32 lrwindow, HI_S32 zorder);
HI_S32 Hi_Adp_Video_SetWindowPos(HI_S32 lrwindow, HI_S32 X, HI_S32 Y, HI_S32 W, HI_S32 H );

HI_S32 Hi_Adp_Video_SetCheckSpan(HI_S32 s32Span);
HI_S32 Hi_Adp_Video_CheckPacket();
HI_DOUBLE Hi_Adp_Video_GetVideoStatics(HI_ADP_STATICS_E enVideoStatic);

HI_S32 Hi_Adp_Video_GetOptionalConfig(HI_S32 OptionType);
HI_S32 Hi_Adp_Video_SetOptionalConfig(HI_S32 OptionType, HI_S32 Value);

HI_S32 Hi_Adp_Audio_Init(HI_VOID);
HI_S32 Hi_Adp_Audio_Deinit(HI_VOID);
HI_S32 Hi_Adp_Audio_Open(HI_U32 u32AudSelectInDevNum, HI_U32 u32AudSelectOutDevNum);
HI_S32 Hi_Adp_Audio_Start(const HI_CHAR *pLoacalIp, HI_U32 uLocalPort, const HI_CHAR *pRemoteIp, HI_U32 uRemotePort);
HI_S32 Hi_Adp_Audio_Stop(HI_VOID);
HI_S32 Hi_Adp_Audio_Close(HI_VOID);
HI_S32 Hi_Adp_Audio_GetAudDevList(HI_AUD_DEV_INFO_S *pstAudInDevList, HI_AUD_DEV_INFO_S *pstAudOutDevList);
HI_S32 Hi_Adp_Audio_SetMute(HI_S32 sDevice);
HI_S32 Hi_Adp_Audio_SetUnMute(HI_S32 sDevice);
HI_S32 Hi_Adp_Audio_SetVolume(HI_S32 sDevice, HI_S32 s32Volume);
HI_S32 Hi_Adp_Audio_SetGain(HI_S32 sDevice, HI_S32 s32Gain);
HI_S32 Hi_Adp_Audio_SetCheckSpan(HI_S32 s32Span);
HI_S32 Hi_Adp_Audio_CheckPacket();
HI_S32 Hi_Adp_Audio_EnableAEC(HI_S32 s32Enable);
HI_S32 Hi_Adp_Audio_EnableANS(HI_S32 s32Enable);
HI_S32 Hi_Adp_Audio_EnableAGC(HI_S32 s32Enable);
HI_S32 Hi_Adp_Audio_EnableVAD(HI_S32 s32Enable);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __vp_adpt_ h*/

