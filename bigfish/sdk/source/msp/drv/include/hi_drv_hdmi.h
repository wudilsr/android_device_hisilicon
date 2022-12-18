/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_priv_hdmi.h
  Version       : Initial Draft
  Author        : q46153 l00168554
  Created       : 2010/6/15
  Last Modified :
  Description   : hdmi ioctl and HDMI API common data structs

******************************************************************************/

#ifndef  __HI_DRV_HDMI_H__
#define  __HI_DRV_HDMI_H__

//#include "hi_common_id.h"
#include "hi_module.h"
//#include "hi_common_log.h"
#include "hi_debug.h"

#include "hi_unf_hdmi.h"
#include "hi_error_mpi.h"
#include "hi_drv_disp.h"
#include "hi_drv_video.h"

#ifdef __cplusplus
#if __cplusplus
	extern "C"{
#endif
#endif

/*
**HDMI Debug
*/
#ifndef HI_ADVCA_FUNCTION_RELEASE
#define HI_FATAL_HDMI(fmt...)       HI_FATAL_PRINT  (HI_ID_HDMI, fmt)
#define HI_ERR_HDMI(fmt...)         HI_ERR_PRINT    (HI_ID_HDMI, fmt)
#define HI_WARN_HDMI(fmt...)        HI_WARN_PRINT   (HI_ID_HDMI, fmt)
#define HI_INFO_HDMI(fmt...)        HI_INFO_PRINT   (HI_ID_HDMI, fmt)

#define debug_printk(fmt,args...) // printk(fmt,##args)
#else

#define HI_FATAL_HDMI(fmt...) 
#define HI_ERR_HDMI(fmt...) 
#define HI_WARN_HDMI(fmt...)
#define HI_INFO_HDMI(fmt...)
#define debug_printk(fmt,args...)  

#endif

/*hdmi audio interface */
typedef enum  hiHDMI_AUDIOINTERFACE_E
{
    HDMI_AUDIO_INTERFACE_I2S,
    HDMI_AUDIO_INTERFACE_SPDIF, 
    HDMI_AUDIO_INTERFACE_HBR, 
    HDMI_AUDIO_INTERFACE_BUTT
}HDMI_AUDIOINTERFACE_E;


typedef struct hiHDMI_AUDIO_ATTR_S
{
    HDMI_AUDIOINTERFACE_E   enSoundIntf;         /**<the origin of Sound,suggestion set HI_UNF_SND_INTERFACE_I2S,the parameter need consistent with Ao input *//**<CNcomment:HDMI��Ƶ��Դ, ����HI_UNF_SND_INTERFACE_I2S,�˲�����Ҫ��AO���뱣��һ�� */
    HI_BOOL                 bIsMultiChannel;     /**<set mutiChannel or stereo ;0:stereo,1:mutichannel fixup 8 channel *//**<CNcomment:������������������0:��������1:�������̶�Ϊ8���� */
	HI_U32 					u32Channels;         //��channel��multy channel���������������ں�̬�ɵ�multy channel
    HI_UNF_SAMPLE_RATE_E    enSampleRate;        /**<the samplerate of audio,this parameter consistent with AO config *//**<CNcomment:PCM��Ƶ������,�˲�����Ҫ��AO�����ñ���һ�� */
    HI_U8                   u8DownSampleParm;    /**<PCM parameter of dowmsample,default 0*//**CNcomment:PCM��Ƶ����downsample�����ʵĲ�����Ĭ��Ϊ0 */
    
    HI_UNF_BIT_DEPTH_E      enBitDepth;          //ĿǰĬ����16bit    /**<the audio bit depth,defualt 16,this parameter consistent with AO config*//**<CNcomment:��Ƶλ��Ĭ��Ϊ16,�˲�����Ҫ��AO�����ñ���һ�� */
    HI_U8                   u8I2SCtlVbit;        /**<reserve:config 0,I2S control(0x7A:0x1D)*//**CNcomment:������������Ϊ0, I2S control (0x7A:0x1D) */

    HI_UNF_EDID_AUDIO_FORMAT_CODE_E enAudioCode;
}HDMI_AUDIO_ATTR_S;

#if defined(HI_HDMI_SUPPORT_2_0)
typedef enum
{
	DRV_HDMI_HV_SYNC_POL_HPVP,
	DRV_HDMI_HV_SYNC_POL_HPVN,
	DRV_HDMI_HV_SYNC_POL_HNVP,
	DRV_HDMI_HV_SYNC_POL_HNVN
} HI_DRV_HDMI_HVSYNC_POLARITY_E;

typedef enum {
	DRV_HDMI_ACTIVE_ASPECT_16_9_TOP = 2,
	DRV_HDMI_ACTIVE_ASPECT_14_9_TOP = 3,
	DRV_HDMI_ACTIVE_ASPECT_16_9_CENTER = 4,
	DRV_HDMI_ACTIVE_ASPECT_PICTURE = 8,
	DRV_HDMI_ACTIVE_ASPECT_4_3 = 9,
	DRV_HDMI_ACTIVE_ASPECT_16_9 = 10,
	DRV_HDMI_ACTIVE_ASPECT_14_9 = 11,
	DRV_HDMI_ACTIVE_ASPECT_4_3_SP_14_9 = 13,
	DRV_HDMI_ACTIVE_ASPECT_16_9_SP_14_9 = 14,
	DRV_HDMI_ACTIVE_ASPECT_16_9_SP_4_3 = 15,
}HI_DRV_HDMI_ACTIVE_ASPECT_E;

/*In order to extern ,so we define struct*/
typedef struct hiHDMI_VIDEO_ATTR_S
{

    HI_DRV_DISP_FMT_E             enVideoFmt;          /**<video fromat ,the format must consistent with display  config*//**<CNcomment:��Ƶ��ʽ,�˲�����Ҫ��Display���õ���ʽ����һ�� */
    HI_U32                        u32ClkFs; 
    HI_U32                        u32PixelRepeat;       
    HI_UNF_EDID_3D_TYPE_E         enStereoMode;
    HI_DRV_HDMI_HVSYNC_POLARITY_E enHvSyncPol;
    HI_UNF_HDMI_DEEP_COLOR_E      enInBitDepth;
    HI_U32                        u32ColorSpace;
    HI_U32                        u32DispRatioWidth;
    HI_U32                        u32DispRatioHeight;    
/*
    HI_UNF_HDMI_VIDEO_MODE_E      enInColorSpace; 
    HI_UNF_HDMI_COLORSPACE_E      enColorimetry;
    HI_UNF_HDMI_RGB_QUAN_RAGE_E   enRGBQuantization;
    HI_UNF_HDMI_YCC_QUAN_RAGE_E   enYCCQuantization;

    HI_UNF_HDMI_ASPECT_RATIO_E    enPictureAspect;
    HI_DRV_HDMI_ACTIVE_ASPECT_E   enActiveAspect; 
    HI_UNF_HDMI_PICTURE_SCALING_E enPictureScaling;
*/
    
  
}HDMI_VIDEO_ATTR_S;
#else
/*In order to extern ,so we define struct*/
typedef struct hiHDMI_VIDEO_ATTR_S
{
    HI_DRV_DISP_FMT_E       enVideoFmt;          /**<video fromat ,the format must consistent with display  config*//**<CNcomment:��Ƶ��ʽ,�˲�����Ҫ��Display���õ���ʽ����һ�� */
    HI_BOOL                 b3DEnable;           /**<0:disable 3d,1,enable 3d mode*//**<CNcomment:< 0:3D�����1:3Dģʽ�� */
    HI_U32                  u83DParam;           /**<3D Parameter,defualt HI_FALSE*//**<CNcomment:< 3D Parameter, Ĭ��ΪHI_FALSE */
}HDMI_VIDEO_ATTR_S;

/*In order to extern ,so we define struct*/
typedef struct hiHDMI_APP_ATTR_S
{
	HI_BOOL                 bEnableHdmi;         /**<force to HDMI or DVI,the value must set before HI_UNF_HDMI_Start or behind HI_UNF_HDMI_Stop*//**<CNcomment:�Ƿ�ǿ��HDMI,����ΪDVI.��ֵ������ HI_UNF_HDMI_Start֮ǰ����HI_UNF_HDMI_Stop֮������  */
    HI_BOOL                 bEnableVideo;        /**<parameter must set HI_TRUE,or the HDMI diver will force to set HI_TRUE*//**<CNcomment:������HI_TRUE, �����HI_FALSE:HDMI������ǿ������ΪHI_TRUE */
    HI_BOOL                 bEnableAudio;        /**<Enable flag of Audio*//**CNcomment:�Ƿ�Enable��Ƶ */

    HI_UNF_HDMI_VIDEO_MODE_E enVidOutMode;       /**<HDMI output vedio mode VIDEO_MODE_YCBCR,VIDEO_MODE_YCBCR444��VIDEO_MODE_YCBCR422��VIDEO_MODE_RGB444 *//**<CNcomment:HDMI�����Ƶģʽ��VIDEO_MODE_YCBCR444��VIDEO_MODE_YCBCR422��VIDEO_MODE_RGB444 */
    HI_UNF_HDMI_DEEP_COLOR_E enDeepColorMode;    /**<Deep Color output mode,defualt: HI_UNF_HDMI_DEEP_COLOR_24BIT *//**<CNcomment:DeepColor���ģʽ, Ĭ��ΪHI_UNF_HDMI_DEEP_COLOR_24BIT */
    HI_BOOL                 bxvYCCMode;          /**<the xvYCC output mode,default:HI_FALSE*//**<CNcomment:< xvYCC���ģʽ��Ĭ��ΪHI_FALSE */

    HI_BOOL                 bEnableAviInfoFrame; /**<Enable flag of AVI InfoFrame,suggestion:enable *//**<CNcomment:�Ƿ�ʹ�� AVI InfoFrame������ʹ�� */
    HI_BOOL                 bEnableSpdInfoFrame; /**<Enable flag of SPD info frame,suggestion:disable*//**<CNcomment:�Ƿ�ʹ�� SPD InfoFrame�� ����ر� */
    HI_BOOL                 bEnableMpegInfoFrame;/**<Enable flag of MPEG info frame,suggestion:disable*//**<CNcomment:�Ƿ�ʹ�� MPEG InfoFrame�� ����ر� */
    HI_BOOL                 bEnableAudInfoFrame; /**<Enable flag of Audio InfoFrame,suggestion:enable*//**<CNcomment:�Ƿ�ʹ�� AUDIO InfoFrame������ʹ�� */

    HI_U32                  bDebugFlag;          /**<the flag of hdmi dubug,suggestion:disable*//**<CNcomment:< �Ƿ�ʹ�� ��hdmi�ڲ�debug��Ϣ�� ����ر� */
    HI_BOOL                 bHDCPEnable;         /**<0:HDCP disable mode,1:eable HDCP mode*//**<CNcomment:< 0:HDCP�����1:HDCPģʽ�� */
}HDMI_APP_ATTR_S;



/*hdmi struct */
typedef struct hiHDMI_ATTR_S
{
	HDMI_AUDIO_ATTR_S  stAudioAttr;
    HDMI_VIDEO_ATTR_S  stVideoAttr;
    HDMI_APP_ATTR_S    stAppAttr;
}HDMI_ATTR_S;
#endif

typedef struct hiHDMI_AUDIO_CAPABILITY_S
{
    HI_BOOL             bAudioFmtSupported[HI_UNF_EDID_AUDIO_FORMAT_CODE_BUTT]; /**<Audio capability,reference EIA-CEA-861-D,table 37,HI_TRUE:support this Audio type;HI_FALSE,nonsupport this Audio type*//**<CNcomment:��Ƶ������, ��ο�EIA-CEA-861-D ��37;HI_TRUE��ʾ֧��������ʾ��ʽ��HI_FALSE��ʾ��֧�� */
    HI_U32              u32AudioSampleRateSupported[MAX_SAMPE_RATE_NUM]; /**<PCM smprate capability,0: illegal value,other is support PCM smprate *//**<CNcomment:PCM��Ƶ��������������0Ϊ�Ƿ�ֵ������Ϊ֧�ֵ���Ƶ������ */
    HI_U32              u32MaxPcmChannels;        /**<Audio max PCM Channels number*//**CNcomment:��Ƶ����PCMͨ���� */
}HI_DRV_HDMI_AUDIO_CAPABILITY_S;



HI_S32  HI_DRV_HDMI_Init(HI_VOID);
HI_VOID  HI_DRV_HDMI_Deinit(HI_VOID);
HI_S32 HI_DRV_HDMI_Open(HI_UNF_HDMI_ID_E enHdmi);
HI_S32 HI_DRV_HDMI_Close(HI_UNF_HDMI_ID_E enHdmi);

HI_S32 HI_DRV_HDMI_GetPlayStatus(HI_UNF_HDMI_ID_E enHdmi, HI_U32 *pu32Status);
HI_S32 HI_DRV_HDMI_GetAOAttr(HI_UNF_HDMI_ID_E enHdmi, HDMI_AUDIO_ATTR_S *pstHDMIAOAttr);
HI_S32 HI_DRV_HDMI_SetAOAttr(HI_UNF_HDMI_ID_E enHdmi, HDMI_AUDIO_ATTR_S *pstHDMIAOAttr);
HI_S32 HI_DRV_HDMI_GetSinkCapability(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_EDID_BASE_INFO_S *pstSinkCap);
HI_S32 HI_DRV_HDMI_GetAudioCapability(HI_UNF_HDMI_ID_E enHdmi, HI_DRV_HDMI_AUDIO_CAPABILITY_S *pstAudCap);
HI_S32 HI_DRV_HDMI_SetAudioMute(HI_UNF_HDMI_ID_E enHdmi);
HI_S32 HI_DRV_HDMI_SetAudioUnMute(HI_UNF_HDMI_ID_E enHdmi);

HI_S32 HI_DRV_HDMI_Detach(HI_UNF_HDMI_ID_E enHdmi);
#if defined(HI_HDMI_SUPPORT_2_0)
HI_S32 HI_DRV_HDMI_PreFormat(HI_UNF_HDMI_ID_E enHdmi);
HI_S32 HI_DRV_HDMI_SetFormat(HI_UNF_HDMI_ID_E enHdmi, HDMI_VIDEO_ATTR_S *pstVideoAttr);
HI_S32 HI_DRV_HDMI_Attach(HI_UNF_HDMI_ID_E enHdmi, HDMI_VIDEO_ATTR_S *pstVideoAttr);
#else
HI_S32 HI_DRV_HDMI_PreFormat(HI_UNF_HDMI_ID_E enHdmi, HI_DRV_DISP_FMT_E enEncodingFormat);
HI_S32 HI_DRV_HDMI_SetFormat(HI_UNF_HDMI_ID_E enHdmi, HI_DRV_DISP_FMT_E enFmt, HI_DRV_DISP_STEREO_E enStereo);
HI_S32 HI_DRV_HDMI_Attach(HI_UNF_HDMI_ID_E enHdmi,HI_DRV_DISP_FMT_E enFmt, HI_DRV_DISP_STEREO_E enStereo);
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
/*--------------------------END-------------------------------*/
