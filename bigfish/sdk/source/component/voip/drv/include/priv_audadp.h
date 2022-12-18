
/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : priv_hme.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011/3/2
  Description   :
  History       :
  1.Date        : 2011/3/2
    Author      : f00172091
    Modification: Created file

******************************************************************************/

#ifndef __MPI_PRIV_AUDADP_H__
#define __MPI_PRIV_AUDADP_H__

//#include "hi_common.h"
#include "hi_unf_voip.h"
#include "hi_module.h"
#include "hi_debug.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define AUDADP_PERIOD_TIME  10           /*sample period, unit is ms*/

#define HI_AUDADP_ERR(fmt...) \
            HI_ERR_PRINT(HI_ID_AUDADP, fmt)

#define HI_AUDADP_INFO(fmt...) \
            HI_INFO_PRINT(HI_ID_AUDADP, fmt)

#define HI_AUDADP_WARN(fmt...) \
            HI_WARN_PRINT(HI_ID_AUDADP, fmt)

#define CHECK_NULL_PTR(ptr)\
do{\
    if(NULL == ptr )\
    {\
        return HI_ERR_VOIP_HME_NULL_PTR;\
    }\
}while(0)

#define CHECK_DEV_ID(dev)\
do{\
     if((dev <0 )||(dev>=HI_UNF_VOIP_AUD_DEV_BUTT))\
     {\
        return HI_ERR_VOIP_HME_INVALID_PARA;\
     }\
}while(0)

/** Audio device running control */
typedef enum _AUDADP_DEV_RUN_CTRL
{
    AUDADP_DEV_RUN_CTRL_CLOSE = 0,
    AUDADP_DEV_RUN_CTRL_OPEN,
    AUDADP_DEV_RUN_CTRL_RUN,
    AUDADP_DEV_RUN_CTRL_MAX
}AUDADP_DEV_RUN_CTRL;

typedef struct
{
    HI_U32      u32RunCtrl;              /**< AUDADP_DEV_RUN_CTRL*/ 
    HI_S32      s32AudioDevId;
    HI_S32      s32CardNo;               /**< The card number of ALSA device*/ 
    HI_CHAR     s8Name[HI_ALSA_AUD_DEV_NAME_LEN];
    HI_S32      s32SampleRate;           /**< [8000,16000,32000,48000]*/
    HI_S32      s32BitPerSample;         /**< [16]*/
    HI_S32      s32Channels;             /**< [1]*/
    HI_U32      u32FrameIndex;
    HI_S32      s32Status;
    HI_U32      u32Type;                 /**< HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E*/
}AUDADP_DRV_DEVICE_ATTR;

/** Audio frame head struct */
typedef struct _AUDADP_AUDIO_FRAME_HEAD_S
{
    HI_S32  s32AudioDevId;          /**< audio device id*/
    HI_S32  s32BitPerSample;       /**< bits per sample*/
    HI_U32  u32SampleRate;         /**< sample rate*/
    HI_U32  u32Channels;           /**< channels*/
    HI_U32  u32PtsMs;              /**< time stamp in ms*/
    HI_U32  u32FrameIndex;         /**< frame index */
    HI_U32  u32DataLen;         /**< data length*/
}AUDADP_AUDIO_FRAME_HEAD_S;

typedef struct
{
    HI_S32  s32AudioDevId;                      /**< audio device id*/
    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;   /**< operating flag */
}AUDADP_IOCTL_CLEAR_BUFFER_S;

typedef struct
{
    HI_S32  s32AudioDevId;                      /**< audio device id*/
    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;   /**< operating flag */
    AUDADP_DRV_DEVICE_ATTR *pstAudInDev;          
    AUDADP_DRV_DEVICE_ATTR *pstAudOutDev;          
}AUDADP_IOCTL_SET_ATTR_S;

#define CMD_AUDADP_PTHREAD_WAKE_UP		_IO(HI_ID_AUDADP, 1)
#define CMD_AUDADP_CLEAR_BUFFER		    _IOW(HI_ID_AUDADP, 2, AUDADP_IOCTL_CLEAR_BUFFER_S)
#define CMD_AUDADP_SET_ATTR		        _IOW(HI_ID_AUDADP, 3, AUDADP_IOCTL_SET_ATTR_S)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __MPI_PRIV_VO_H__ */


