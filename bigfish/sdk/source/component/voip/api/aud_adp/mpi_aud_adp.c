/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : HMEip_hme.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011/3/3
  Description   :
  History       :
  1.Date        : 2011/3/3
    Author      : f00172091
    Modification: Created file

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <linux/types.h>


#include "hi_module.h"
#include "hi_mpi_mem.h"


#include "alsa/asoundlib.h"
#include "mpi_aud_adp.h"

#include "hi_drv_struct.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

static HI_S32           g_AudAdpDevFd = -1;
static const HI_CHAR    g_AudAdpDevName[] = "/dev/"UMAP_DEVNAME_AUDADP;

typedef struct _AUDADP_THREAD_STRU
{
    pthread_t   tThread;
    pthread_mutex_t  tMutex;
    HI_U32   u32RunFlag;
} AUDADP_THREAD_STRU;

static AUDADP_THREAD_STRU  stThreadAudIn;
static AUDADP_THREAD_STRU  stThreadAudOut;
static AUDADP_THREAD_STRU  stThreadMonitor;     /*To monitor the audio device status*/

#define AUDADP_AUD_IN_LOCK()  	 (void)pthread_mutex_lock(&stThreadAudIn.tMutex);
#define AUDADP_AUD_IN_UNLOCK()   (void)pthread_mutex_unlock(&stThreadAudIn.tMutex);
#define AUDADP_AUD_OUT_LOCK()  	 (void)pthread_mutex_lock(&stThreadAudOut.tMutex);
#define AUDADP_AUD_OUT_UNLOCK()   (void)pthread_mutex_unlock(&stThreadAudOut.tMutex);

#define CHECK_AUDADP_INIT()\
do{\
	if (g_AudAdpDevFd < 0)\
	{\
		HI_AUDADP_ERR("AUDADP is not init.\n");\
		return HI_ERR_VOIP_HME_NO_INIT;\
	}\
}while(0)

#define AUDADP_ALSA_BUFFER_SIZE    4096     /*Should large than the audio packet size : frame head + (channels*bitspersample/8)*samplerate*10/1000 */
#define AUDADP_OPEN_ERR_DELAY   150     /*20ms*150*/
#define AUDADP_BLUETOOTH_OPEN_ERR_DELAY   100     /*20ms*100*/

typedef struct
{
    AUDADP_DEV_RUN_CTRL      u32RunCtrl;
    HI_S32      s32AudioDevId;
    HI_S32      s32CardNo;               /**< The card number of ALSA device*/ 
    HI_CHAR     s8Name[HI_ALSA_AUD_DEV_NAME_LEN];
    HI_S32      s32SampleRate;           /**< [8000,16000,32000,48000]*/
    HI_S32      s32BitPerSample;         /**< [16]*/
    HI_S32      s32Channels;             /**< [1]*/
    HI_U32      u32FrameIndex;
    HI_S32      s32Status;
    HI_U32      u32OpenDelayCnt;
    snd_pcm_stream_t stream;
    snd_pcm_t   *pHandle;
    snd_pcm_uframes_t   period_frames;  /*The number of sample point in 10ms*/
    HI_S32      nfds;
    struct pollfd *pfds;
} AUDADP_ALSA_DEVICE_ATTR;

typedef struct _AUDADP_ALSA_DEVICE
{
    AUDADP_ALSA_DEVICE_ATTR stAudInDev;
    AUDADP_ALSA_DEVICE_ATTR stAudOutDev;
} AUDADP_ALSA_DEVICE;

static AUDADP_ALSA_DEVICE stAudDevList[HI_UNF_VOIP_AUD_DEV_BUTT];

typedef struct _AUDADP_EVENT_CB_S
{
    HI_UNF_AUDADP_EVENT_CB_FN pfnAudadpEventCb;
    HI_UNF_AUDADP_EVENT_S stAudAdpEvent;
} AUDADP_EVENT_CB_S;

static AUDADP_EVENT_CB_S stAudadpEventCb;

static HI_S32 AUDADP_AlsaDev_MonoProc(HI_U8 *pu8Src,
                                      HI_U32 u32FrameLen,
                                      HI_U32 u32BitRate)
{
    HI_U8 *pu8Tmp = NULL, *pu8Dst = NULL;
    HI_U16 *pu16Tmp = NULL, *pu16Dst = NULL;
    HI_U32 i, j, u32RealLen;
    
    if (pu8Src == NULL || u32FrameLen == 0)
    {
        return HI_FAILURE;
    }

    if (u32BitRate == 8)
    {
        u32RealLen = u32FrameLen;
        pu8Tmp = pu8Src;
        pu8Dst = pu8Src;
        for (i = 0; i < u32RealLen; i = i + 2)
        {
            *pu8Dst = *(pu8Tmp + i);
            pu8Dst++;
        }
    }
    else if (u32BitRate == 16)
    {
        u32RealLen = u32FrameLen/2;
        pu16Tmp = (HI_U16 *)pu8Src;
        pu16Dst = (HI_U16 *)pu8Src;
        for (i = 0; i < u32RealLen; i = i + 2)
        {
            *pu16Dst = *(pu16Tmp + i);
            pu16Dst++;
        }
    }
    else
    {
        HI_AUDADP_ERR("Bit isn't right\n");
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

static HI_S32 AUDADP_Drv_Clear_Buffer(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    HI_S32 ret;
    AUDADP_IOCTL_CLEAR_BUFFER_S stIoctlClearBuff;

    stIoctlClearBuff.s32AudioDevId = s32AudioDevId;
    stIoctlClearBuff.stAudDevOptFlag = stAudDevOptFlag;
    ret = ioctl(g_AudAdpDevFd, CMD_AUDADP_CLEAR_BUFFER, &stIoctlClearBuff);
    return ret;
}

static HI_S32 AUDADP_Drv_SetAttr(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    HI_S32 ret;
    
    AUDADP_ALSA_DEVICE_ATTR *pstAudDev = HI_NULL;
    AUDADP_DRV_DEVICE_ATTR stDrvAudInDev;
    AUDADP_DRV_DEVICE_ATTR stDrvAudOutDev;
    AUDADP_IOCTL_SET_ATTR_S stIoctlSetAttr;

    memset(&stDrvAudInDev,0,sizeof(AUDADP_DRV_DEVICE_ATTR));
    memset(&stDrvAudOutDev,0,sizeof(AUDADP_DRV_DEVICE_ATTR));
    memset(&stIoctlSetAttr,0,sizeof(AUDADP_IOCTL_SET_ATTR_S));
    
    stIoctlSetAttr.s32AudioDevId = s32AudioDevId;
    stIoctlSetAttr.stAudDevOptFlag = stAudDevOptFlag;
    if(stAudDevOptFlag.bit1AudInDev)
    {
        pstAudDev = &stAudDevList[s32AudioDevId].stAudInDev;
        stDrvAudInDev.s32AudioDevId = pstAudDev->s32AudioDevId;
        stDrvAudInDev.u32RunCtrl = pstAudDev->u32RunCtrl;
        stDrvAudInDev.s32CardNo = pstAudDev->s32CardNo;
        stDrvAudInDev.s32SampleRate = pstAudDev->s32SampleRate;
        stDrvAudInDev.s32BitPerSample = pstAudDev->s32BitPerSample;
        stDrvAudInDev.s32Channels = pstAudDev->s32Channels;
        stDrvAudInDev.u32FrameIndex = pstAudDev->u32FrameIndex;
        stDrvAudInDev.s32Status = pstAudDev->s32Status;
        stDrvAudInDev.u32Type = HI_UNF_VOIP_AUD_IN_DEV;
        memcpy(stDrvAudInDev.s8Name,pstAudDev->s8Name,HI_ALSA_AUD_DEV_NAME_LEN);
        
        stIoctlSetAttr.pstAudInDev = &stDrvAudInDev;
    }
    
    if(stAudDevOptFlag.bit1AudOutDev)
    {
        pstAudDev = &stAudDevList[s32AudioDevId].stAudOutDev;
        stDrvAudOutDev.s32AudioDevId = pstAudDev->s32AudioDevId;
        stDrvAudOutDev.u32RunCtrl = pstAudDev->u32RunCtrl;
        stDrvAudOutDev.s32CardNo = pstAudDev->s32CardNo;
        stDrvAudOutDev.s32SampleRate = pstAudDev->s32SampleRate;
        stDrvAudOutDev.s32BitPerSample = pstAudDev->s32BitPerSample;
        stDrvAudOutDev.s32Channels = pstAudDev->s32Channels;
        stDrvAudOutDev.u32FrameIndex = pstAudDev->u32FrameIndex;
        stDrvAudOutDev.s32Status = pstAudDev->s32Status;
        stDrvAudOutDev.u32Type = HI_UNF_VOIP_AUD_OUT_DEV;
        memcpy(stDrvAudOutDev.s8Name,pstAudDev->s8Name,HI_ALSA_AUD_DEV_NAME_LEN);

        stIoctlSetAttr.pstAudOutDev = &stDrvAudOutDev;
    }
    ret = ioctl(g_AudAdpDevFd, CMD_AUDADP_SET_ATTR, &stIoctlSetAttr);
    return ret;
}

static HI_S32 AUDADP_Event_Callback(AUDADP_ALSA_DEVICE_ATTR *pstAudDev,HI_UNF_AUDADP_EVENT_E enAudadpEvent)
{
    if(NULL != stAudadpEventCb.pfnAudadpEventCb)
    {
        stAudadpEventCb.stAudAdpEvent.s32AudioDevId = pstAudDev->s32AudioDevId;
        stAudadpEventCb.stAudAdpEvent.enEvent = enAudadpEvent;
        if(pstAudDev->stream == SND_PCM_STREAM_CAPTURE)
        {
            stAudadpEventCb.stAudAdpEvent.enAudioDevType = HI_UNF_VOIP_AUD_IN_DEV;
        }
        else
        {
            stAudadpEventCb.stAudAdpEvent.enAudioDevType = HI_UNF_VOIP_AUD_OUT_DEV;
        }
        stAudadpEventCb.stAudAdpEvent.enStatus = pstAudDev->s32Status;
        (HI_VOID)stAudadpEventCb.pfnAudadpEventCb(&stAudadpEventCb.stAudAdpEvent);
    }
    return HI_SUCCESS;
}
    
static HI_S32  AUDADP_AlsaDev_Open(AUDADP_ALSA_DEVICE_ATTR *pstAudDev)
{
    HI_S32 err;
    snd_pcm_hw_params_t *hw_params = NULL;
    HI_S32 open_mode=0;
    HI_S32 dir;
    snd_pcm_uframes_t   period_frames;
    snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

    HI_AUDADP_INFO("ALSA OPEN %s device [%d - %s] start.\n",snd_pcm_stream_name(pstAudDev->stream),pstAudDev->s32AudioDevId,pstAudDev->s8Name);

    pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENING;
     
    if ((err = snd_pcm_open(&pstAudDev->pHandle, pstAudDev->s8Name, pstAudDev->stream, open_mode)) < 0) {
        HI_AUDADP_ERR("cannot open audio device %s (%s)\n", 
        	 pstAudDev->s8Name,
        	 snd_strerror(err));
    	goto exit_alsa_dev_close;
    }
    HI_AUDADP_INFO("snd_pcm_open() %s %s OK, stream %d, handle %x!\n",pstAudDev->stream?"AudInDev":"AudOutDev",pstAudDev->s8Name,pstAudDev->stream,pstAudDev->pHandle);

    if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
    	HI_AUDADP_ERR("cannot allocate hardware parameter structure (%s)\n",
    		 snd_strerror(err));
    	goto exit_alsa_dev_close;
    }
    HI_AUDADP_INFO("snd_pcm_hw_params_malloc()  OK!\n");
    
    if ((err = snd_pcm_hw_params_any(pstAudDev->pHandle, hw_params)) < 0) {
    	HI_AUDADP_ERR("cannot initialize hardware parameter structure (%s)\n",
    		 snd_strerror(err));
    	goto exit_free_hw_params;
    }
    HI_AUDADP_INFO("snd_pcm_hw_params_any()  OK!\n");

    if ((err = snd_pcm_hw_params_set_access(pstAudDev->pHandle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
    	HI_AUDADP_ERR("cannot set access type (%s)\n",
    		 snd_strerror(err));
    	goto exit_free_hw_params;
    }
    HI_AUDADP_INFO("snd_pcm_hw_params_set_access()  OK!\n");

    if(pstAudDev->s32BitPerSample == 16)
    {
        format = SND_PCM_FORMAT_S16_LE;
    }
    else
    {
        HI_AUDADP_ERR("unsupport sample format %d!\n",pstAudDev->s32BitPerSample);
    	goto exit_free_hw_params;
    }

    if ((err = snd_pcm_hw_params_set_format(pstAudDev->pHandle, hw_params, format)) < 0) {
    	HI_AUDADP_ERR("cannot set sample format [%d] (%s)\n",
             format,
    		 snd_strerror(err));
    	goto exit_free_hw_params;
    }
    HI_AUDADP_INFO("snd_pcm_hw_params_set_format()  OK!\n");

    if(pstAudDev->stream == SND_PCM_STREAM_PLAYBACK)
    {
        err = snd_pcm_hw_params_set_channels_near(pstAudDev->pHandle, hw_params, (HI_U32 *)&pstAudDev->s32Channels);
    }
    else
    {
        err = snd_pcm_hw_params_set_channels(pstAudDev->pHandle, hw_params, (HI_U32)pstAudDev->s32Channels);
//modify by x00190696
/*some devices(C920) only supports stereo channels.*/
        if (err < 0)
        {
            if (pstAudDev->s32Channels == 1)
            {
                err = snd_pcm_hw_params_set_channels(pstAudDev->pHandle, hw_params, 2);
                pstAudDev->s32Channels = 2;
            }
        }
//modify by x00190696        
    }
    if (err < 0)
    {
    	HI_AUDADP_ERR("cannot set channel count [%d] (%s)\n",
             pstAudDev->s32Channels,
    		 snd_strerror(err));
    	goto exit_free_hw_params;

    }
    HI_AUDADP_INFO("snd_pcm_hw_params_set_channels()  OK!, channels is %d\n",pstAudDev->s32Channels);

    if ((err = snd_pcm_hw_params_set_rate(pstAudDev->pHandle, hw_params, (HI_U32)pstAudDev->s32SampleRate, 0)) < 0) {
    	HI_AUDADP_ERR("cannot set sample rate [%d] (%s)\n",
             pstAudDev->s32SampleRate,
    		 snd_strerror(err));
    	goto exit_free_hw_params;
    }
    HI_AUDADP_INFO("snd_pcm_hw_params_set_rate()  OK, rate is %d\n",pstAudDev->s32SampleRate);

    pstAudDev->period_frames = (HI_U32)(pstAudDev->s32SampleRate * AUDADP_PERIOD_TIME/1000);
    err = snd_pcm_hw_params_set_period_size(pstAudDev->pHandle, hw_params, pstAudDev->period_frames, 0);
    if(err < 0)
    {   
        HI_AUDADP_ERR("cannot set period size %d frames, (%s)\n", pstAudDev->period_frames, snd_strerror (err));
    }
    HI_AUDADP_INFO("set period size %d frames OK.\n",pstAudDev->period_frames);

    if ((err = snd_pcm_hw_params(pstAudDev->pHandle, hw_params)) < 0) {
    	HI_AUDADP_ERR( "cannot set parameters (%d:%s)\n",err,
    		 snd_strerror(err));
    	goto exit_free_hw_params;
    }
    HI_AUDADP_INFO("snd_pcm_hw_params()  OK!\n");
    
    if ((err = snd_pcm_hw_params_get_period_size(hw_params,&period_frames, &dir)) < 0) {
        HI_AUDADP_ERR("cannot get period size (%s)\n",
        	 snd_strerror(err));
        goto exit_free_hw_params;
    }
    if(period_frames != pstAudDev->period_frames)
    {
        HI_AUDADP_ERR("get wrong period size %d frames.\n",(int)period_frames);
        goto exit_free_hw_params;
    }
    else
    {
        HI_AUDADP_INFO("get period size success %d frames.\n",(int)period_frames);
    }

    snd_pcm_hw_params_free(hw_params);

    snd_pcm_prepare(pstAudDev->pHandle);

    pstAudDev->nfds = snd_pcm_poll_descriptors_count(pstAudDev->pHandle);
    HI_AUDADP_INFO("get poll descriptors count %d .\n",pstAudDev->nfds);
    if(pstAudDev->nfds > 0)
    {
        pstAudDev->pfds = HI_MALLOC(HI_ID_AUDADP, sizeof(struct pollfd)* (HI_U32)pstAudDev->nfds);
        if(NULL != pstAudDev->pfds)
        {
            snd_pcm_poll_descriptors(pstAudDev->pHandle, pstAudDev->pfds, (HI_U32)pstAudDev->nfds);
        }
    }
    pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
    pstAudDev->u32FrameIndex = 0;
    (HI_VOID)AUDADP_Event_Callback(pstAudDev, HI_UNF_AUDADP_EVENT_OPEN_SUCCESS);
    
    {
        HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;
        memset(&stAudDevOptFlag,0,sizeof(HI_UNF_AUDDEV_OPT_FLAG_S));
        if(pstAudDev->stream == SND_PCM_STREAM_PLAYBACK)
        {
            stAudDevOptFlag.bit1AudOutDev = 1;
        }
        else
        {
            stAudDevOptFlag.bit1AudInDev = 1;
        }
        (HI_VOID)AUDADP_Drv_SetAttr(pstAudDev->s32AudioDevId, stAudDevOptFlag);
    }
    HI_AUDADP_INFO("ALSA OPEN %s device [%d - %s] success.\n",snd_pcm_stream_name(pstAudDev->stream),pstAudDev->s32AudioDevId,pstAudDev->s8Name);
    
    return HI_SUCCESS;
        
exit_free_hw_params:
   if(NULL != hw_params)
    {
        snd_pcm_hw_params_free(hw_params);
        hw_params = NULL;
    }

exit_alsa_dev_close:
    if(NULL != pstAudDev->pHandle)
    {
        snd_pcm_drop(pstAudDev->pHandle);
        snd_pcm_close(pstAudDev->pHandle);
        pstAudDev->pHandle = NULL;
    }
    pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_ERROR;
    (HI_VOID)AUDADP_Event_Callback(pstAudDev, HI_UNF_AUDADP_EVENT_OPEN_FAILURE);
    
    {
        HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;
        memset(&stAudDevOptFlag,0,sizeof(HI_UNF_AUDDEV_OPT_FLAG_S));
        if(pstAudDev->stream == SND_PCM_STREAM_PLAYBACK)
        {
            stAudDevOptFlag.bit1AudOutDev = 1;
        }
        else
        {
            stAudDevOptFlag.bit1AudInDev = 1;
        }
        (HI_VOID)AUDADP_Drv_SetAttr(pstAudDev->s32AudioDevId, stAudDevOptFlag);
    }
    
    HI_AUDADP_INFO("ALSA OPEN %s device [%d - %s] failure.\n",snd_pcm_stream_name(pstAudDev->stream),pstAudDev->s32AudioDevId,pstAudDev->s8Name);
    return HI_FAILURE;
}

static HI_S32  AUDADP_AlsaDev_Close(AUDADP_ALSA_DEVICE_ATTR *pstAudDev)
{
    if(NULL != pstAudDev->pHandle)
    {
        snd_pcm_drop(pstAudDev->pHandle);
        snd_pcm_close(pstAudDev->pHandle);
//        usleep(10*1000);
        pstAudDev->pHandle = NULL;
        
        if(NULL != pstAudDev->pfds)
        {
            HI_FREE(HI_ID_AUDADP, pstAudDev->pfds);
            pstAudDev->pfds = NULL;
            pstAudDev->nfds = 0;
        }
    }
    
    if((HI_UNF_AUDADP_STATUS_ERROR != pstAudDev->s32Status)&&(HI_UNF_AUDADP_STATUS_BLUETOOTH_NOT_CONNECTED != pstAudDev->s32Status))
    {
        pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_CLOSED;
        (HI_VOID)AUDADP_Event_Callback(pstAudDev, HI_UNF_AUDADP_EVENT_CLOSED);

        {
            HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;
            memset(&stAudDevOptFlag,0,sizeof(HI_UNF_AUDDEV_OPT_FLAG_S));
            if(pstAudDev->stream == SND_PCM_STREAM_PLAYBACK)
            {
                stAudDevOptFlag.bit1AudOutDev = 1;
            }
            else
            {
                stAudDevOptFlag.bit1AudInDev = 1;
            }
            (HI_VOID)AUDADP_Drv_SetAttr(pstAudDev->s32AudioDevId, stAudDevOptFlag);
        }
            
    }

    HI_AUDADP_INFO("ALSA CLOSE %s device [%d - %s] end.\n",snd_pcm_stream_name(pstAudDev->stream),pstAudDev->s32AudioDevId,pstAudDev->s8Name);
        
    return HI_SUCCESS;
}

    
static HI_S32  AUDADP_AlsaDev_Start(AUDADP_ALSA_DEVICE_ATTR *pstAudDev)
{
    if(NULL != pstAudDev->pHandle)
    {
//        snd_pcm_start(pstAudDev->pHandle);
//        snd_pcm_prepare(pstAudDev->pHandle);
        if(pstAudDev->s32Status == HI_UNF_AUDADP_STATUS_OPENED)
        {
            pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_RUNNING;

            {
                HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;
                memset(&stAudDevOptFlag,0,sizeof(HI_UNF_AUDDEV_OPT_FLAG_S));
                if(pstAudDev->stream == SND_PCM_STREAM_PLAYBACK)
                {
                    stAudDevOptFlag.bit1AudOutDev = 1;
                }
                else
                {
                    stAudDevOptFlag.bit1AudInDev = 1;
                }
                (HI_VOID)AUDADP_Drv_SetAttr(pstAudDev->s32AudioDevId, stAudDevOptFlag);
            }

        }
    }

    HI_AUDADP_INFO("ALSA START %s device [%d - %s] end.\n",snd_pcm_stream_name(pstAudDev->stream),pstAudDev->s32AudioDevId,pstAudDev->s8Name);

    return HI_SUCCESS;
}

static HI_S32  AUDADP_AlsaDev_Stop(AUDADP_ALSA_DEVICE_ATTR *pstAudDev)
{
    if(NULL != pstAudDev->pHandle)
    {
//        snd_pcm_drop(pstAudDev->pHandle);
        if(pstAudDev->s32Status == HI_UNF_AUDADP_STATUS_RUNNING)
        {
            pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;

            {
                HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;
                memset(&stAudDevOptFlag,0,sizeof(HI_UNF_AUDDEV_OPT_FLAG_S));
                if(pstAudDev->stream == SND_PCM_STREAM_PLAYBACK)
                {
                    stAudDevOptFlag.bit1AudOutDev = 1;
                }
                else
                {
                    stAudDevOptFlag.bit1AudInDev = 1;
                }
                (HI_VOID)AUDADP_Drv_SetAttr(pstAudDev->s32AudioDevId, stAudDevOptFlag);
            }

        }
    }

    HI_AUDADP_INFO("ALSA STOP %s device [%d - %s] end.\n",snd_pcm_stream_name(pstAudDev->stream),pstAudDev->s32AudioDevId,pstAudDev->s8Name);
    return HI_SUCCESS;
}

static HI_S32 AUDADP_Poll_AlsaEvents(AUDADP_ALSA_DEVICE_ATTR *pstAudDev)
{
    HI_S32  s32Ret = HI_SUCCESS;
    snd_pcm_state_t pcm_state;
    HI_U16  revents;
    HI_U16  i;
    
    if((NULL != pstAudDev->pHandle)&&(NULL != pstAudDev->pfds))
    {
        poll(pstAudDev->pfds, (HI_U32)pstAudDev->nfds, 0);
        s32Ret = snd_pcm_poll_descriptors_revents(pstAudDev->pHandle, pstAudDev->pfds, (HI_U32)pstAudDev->nfds, &revents);
        if(s32Ret < 0)
        {
            return s32Ret;
        }
        pcm_state = snd_pcm_state(pstAudDev->pHandle);
        if((SND_PCM_STATE_DISCONNECTED == pcm_state)||(revents&(POLLERR|POLLHUP|POLLNVAL)))
        {
            HI_AUDADP_ERR("snd pcm state is %d\n", (int)pcm_state);
            HI_AUDADP_ERR("poll descriptors revents is %d\n", revents);
            for(i=0;i<pstAudDev->nfds;i++)
            {
                HI_AUDADP_ERR("pfds[%d].revents is 0x%x\n",i,pstAudDev->pfds[i].revents);
            }

            pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_ERROR;
            (HI_VOID)AUDADP_Event_Callback(pstAudDev, HI_UNF_AUDADP_EVENT_STREAM_ERROR);
            (HI_VOID)AUDADP_AlsaDev_Close(pstAudDev);

            {
                HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;
                memset(&stAudDevOptFlag,0,sizeof(HI_UNF_AUDDEV_OPT_FLAG_S));
                if(pstAudDev->stream == SND_PCM_STREAM_PLAYBACK)
                {
                    stAudDevOptFlag.bit1AudOutDev = 1;
                }
                else
                {
                    stAudDevOptFlag.bit1AudInDev = 1;
                }
                (HI_VOID)AUDADP_Drv_SetAttr(pstAudDev->s32AudioDevId, stAudDevOptFlag);
            }
            
            pstAudDev->u32OpenDelayCnt = AUDADP_OPEN_ERR_DELAY;
        }
    }
    return s32Ret;          
}

static HI_VOID *AUDADP_Audio_In_Proc(HI_VOID *arg)
{
    AUDADP_ALSA_DEVICE_ATTR *pstAudInDev;
    HI_S32  ret;
    HI_U32  i;
    HI_U32  u32ActiveDevCnt = 0;
    AUDADP_AUDIO_FRAME_HEAD_S   *pstFrameHead = NULL;
    HI_CHAR *pBuffer = NULL;
    HI_CHAR *pdata = NULL;
    HI_U32 period_bytes = 0;
    struct timeval stTimeCur;

    HI_AUDADP_INFO("Audio in proc start.\n");

    pBuffer = (char *) HI_MALLOC(HI_ID_AUDADP,AUDADP_ALSA_BUFFER_SIZE);
    if(NULL == pBuffer)
    {
        HI_AUDADP_ERR("malloc buffer failed.\n");
        pthread_exit(NULL);
        return NULL;
    }

    pstFrameHead = (AUDADP_AUDIO_FRAME_HEAD_S *)pBuffer;
    pdata = pBuffer + sizeof(AUDADP_AUDIO_FRAME_HEAD_S);
    
    while(0 != stThreadAudIn.u32RunFlag)
    {
        for(i=0;i<HI_UNF_VOIP_AUD_DEV_BUTT;i++)
        {
            if(0 == stThreadAudIn.u32RunFlag)
            {
                break;
            }
            
            AUDADP_AUD_IN_LOCK();
            pstAudInDev = &stAudDevList[i].stAudInDev;
            if((NULL == pstAudInDev->pHandle)
                ||(HI_UNF_AUDADP_STATUS_RUNNING != pstAudInDev->s32Status)
                ||(AUDADP_DEV_RUN_CTRL_RUN != pstAudInDev->u32RunCtrl))
            {
                AUDADP_AUD_IN_UNLOCK();
                continue;
            }
            AUDADP_AUD_IN_UNLOCK();
#if 0            
            ret = snd_pcm_avail(pstAudInDev->pHandle);
            if(ret < 0)
            {
                AUDADP_Poll_AlsaEvents(pstAudInDev);
            }
            else if(ret < pstAudInDev->period_frames)
            {
                continue;
            }
#endif            
            ret = snd_pcm_readi(pstAudInDev->pHandle, pdata, pstAudInDev->period_frames);
            AUDADP_AUD_IN_LOCK();
            if((NULL == pstAudInDev->pHandle)
                ||(HI_UNF_AUDADP_STATUS_RUNNING != pstAudInDev->s32Status)
                ||(AUDADP_DEV_RUN_CTRL_RUN != pstAudInDev->u32RunCtrl))
            {
                AUDADP_AUD_IN_UNLOCK();
                continue;
            }

            if(ret == -EPIPE)
            {
                /* EPIPE means overrun */
                HI_AUDADP_WARN("overrun occurred\n");
                snd_pcm_prepare(pstAudInDev->pHandle);
                AUDADP_AUD_IN_UNLOCK();
                continue;
            }
            else if(ret == -EAGAIN)
            {
                HI_AUDADP_INFO("try again\n");
                AUDADP_AUD_IN_UNLOCK();
                continue;
            }
            else if(ret < 0)
            {
                HI_AUDADP_ERR("error from read: %d, %s\n", ret,snd_strerror(ret));
                (HI_VOID)AUDADP_Poll_AlsaEvents(pstAudInDev);
                AUDADP_AUD_IN_UNLOCK();
                continue;
            }
            else if(ret != (int)pstAudInDev->period_frames)
            {
                AUDADP_AUD_IN_UNLOCK();
                HI_AUDADP_WARN("short read, read %d frames\n", ret);
                continue;
            }
            period_bytes =  (HI_U32)(ret * pstAudInDev->s32Channels * pstAudInDev->s32BitPerSample/8);

            pstFrameHead->s32AudioDevId = (HI_S32)i;
            pstFrameHead->s32BitPerSample = pstAudInDev->s32BitPerSample;
            pstFrameHead->u32SampleRate = (HI_U32)pstAudInDev->s32SampleRate;
            pstFrameHead->u32Channels = (HI_U32)pstAudInDev->s32Channels;
            gettimeofday(&stTimeCur, NULL);
            pstFrameHead->u32PtsMs = (HI_U32)stTimeCur.tv_usec/1000;
            pstFrameHead->u32FrameIndex = pstAudInDev->u32FrameIndex++;
            pstFrameHead->u32DataLen = period_bytes;
            
            AUDADP_AUD_IN_UNLOCK();

//modify by x00190696
//voip2.0 only supprort mono type
            if (pstAudInDev->s32Channels == 2)
            {
                ret = AUDADP_AlsaDev_MonoProc((HI_U8 *)pdata, period_bytes,pstAudInDev->s32BitPerSample);
                if (ret != HI_SUCCESS)
                {
                    HI_AUDADP_WARN("mono proc failed\n");
                }
                else
                {
                    pstFrameHead->u32Channels = 1;
                    period_bytes = period_bytes/2;
                    pstFrameHead->u32DataLen = period_bytes;
                }
            }
//modify by x00190696
            
            ret = write(g_AudAdpDevFd,pBuffer,sizeof(AUDADP_AUDIO_FRAME_HEAD_S) + period_bytes);
            if((HI_U32)ret != sizeof(AUDADP_AUDIO_FRAME_HEAD_S) + period_bytes)
            {
                HI_AUDADP_WARN("write data error, AudInDev %s, writed %d, expected %d.\n",pstAudInDev->s8Name,ret,sizeof(AUDADP_AUDIO_FRAME_HEAD_S) + period_bytes);
            }
            
            u32ActiveDevCnt++;

        }

        if((0 == u32ActiveDevCnt)&&(0 != stThreadAudIn.u32RunFlag))
        {
            usleep(5*1000);
        }
        else
        {
            u32ActiveDevCnt = 0;
        }
    }

    if(NULL != pBuffer)
    {
        HI_FREE(HI_ID_AUDADP, pBuffer);
    }

    HI_AUDADP_INFO("Audio in proc end.\n");
    pthread_exit(NULL);
    return NULL;
}


static HI_VOID *AUDADP_Audio_Out_Proc(HI_VOID *arg)
{
    HI_S32  ret;
    AUDADP_ALSA_DEVICE_ATTR *pstAudOutDev;
    AUDADP_AUDIO_FRAME_HEAD_S   *pstFrameHead = NULL;
    HI_CHAR *pReadBuf = NULL;
    HI_CHAR *pWriteBuf = NULL;
    HI_CHAR *pdata = NULL;
    snd_pcm_uframes_t   period_frames;
    HI_BOOL     bDelayFlag = HI_FALSE;
    
    HI_AUDADP_INFO("Audio out proc start.\n");

    pReadBuf = (HI_CHAR *) HI_MALLOC(HI_ID_AUDADP,AUDADP_ALSA_BUFFER_SIZE);
    if(HI_NULL == pReadBuf)
    {
        HI_AUDADP_ERR("malloc buffer failed.\n");
        pthread_exit(NULL);
        return HI_NULL;
    }

    pWriteBuf = (HI_CHAR *) HI_MALLOC(HI_ID_AUDADP,AUDADP_ALSA_BUFFER_SIZE);
    if(HI_NULL == pWriteBuf)
    {
        HI_FREE(HI_ID_AUDADP, pReadBuf);
        HI_AUDADP_ERR("malloc buffer failed.\n");
        pthread_exit(NULL);
        return HI_NULL;
    }

    pstFrameHead = (AUDADP_AUDIO_FRAME_HEAD_S *)pReadBuf;
    
    while(0 != stThreadAudOut.u32RunFlag)
    {
        if(bDelayFlag)
        {
            bDelayFlag = HI_FALSE;
            usleep(5*1000);
        }
        
        ret = read(g_AudAdpDevFd,pReadBuf,AUDADP_ALSA_BUFFER_SIZE);
        if((HI_U32)ret < sizeof(AUDADP_AUDIO_FRAME_HEAD_S))
        {
            HI_AUDADP_INFO("read data error %d .\n",ret);
            bDelayFlag = HI_TRUE;
            continue;
        }
        
        if((HI_U32)ret != sizeof(AUDADP_AUDIO_FRAME_HEAD_S)+pstFrameHead->u32DataLen)
        {
            HI_AUDADP_INFO("data length error %d .\n",ret);
            bDelayFlag = HI_TRUE;
            continue;
        }
        
        AUDADP_AUD_OUT_LOCK();

        pstAudOutDev = &stAudDevList[pstFrameHead->s32AudioDevId].stAudOutDev;
        if((NULL == pstAudOutDev->pHandle)
            ||(HI_UNF_AUDADP_STATUS_RUNNING != pstAudOutDev->s32Status)
            ||(AUDADP_DEV_RUN_CTRL_RUN != pstAudOutDev->u32RunCtrl))
        {
            HI_AUDADP_INFO("audio device %d is inactive.\n",pstFrameHead->s32AudioDevId);
            bDelayFlag = HI_TRUE;
            AUDADP_AUD_OUT_UNLOCK();
            continue;
        }

        period_frames = (HI_U32)(pstFrameHead->u32DataLen/(pstFrameHead->u32Channels * pstFrameHead->s32BitPerSample/8));
    #if 0    
        if(0==(pstFrameHead->u32FrameIndex%500))
        {
            HI_AUDADP_INFO("\n%s(), received audio data, FrameIndex: %d, RunCtrl: %d , len : %d\n",__FUNCTION__,pstFrameHead->u32FrameIndex,pstAudOutDev->u32RunCtrl,pstFrameHead->u32DataLen);
        }
    #endif    
        if(pstAudOutDev->s32Channels == 1)
        {
            pdata = pReadBuf + sizeof(AUDADP_AUDIO_FRAME_HEAD_S);
        }
        else if(pstAudOutDev->s32Channels == 2)
        {
            HI_U32 i;
            HI_S16 * ps16Src = (HI_S16 *)(pReadBuf + sizeof(AUDADP_AUDIO_FRAME_HEAD_S));
            HI_S16 * ps16Dest = (HI_S16 *)pWriteBuf;;

            for(i=0;i<period_frames;i++)
            {
               *ps16Dest++ = *ps16Src;
               *ps16Dest++ = *ps16Src;
               ps16Src++;
            }
            pdata = pWriteBuf;
        }
        else
        {
            AUDADP_AUD_OUT_UNLOCK();
            continue;
        }
        
        ret = snd_pcm_writei(pstAudOutDev->pHandle, pdata, period_frames);
        
        if (ret == -EPIPE)
        {
            /* EPIPE means underrun */
            int error;
            if(pstAudOutDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_BLUETOOTH)
            {
                if((error = snd_pcm_prepare(pstAudOutDev->pHandle)) < 0)
                    {
                        HI_AUDADP_ERR("snd_pcm_prepare error (%s)\n",snd_strerror(error));
                    }
            }

            else
            {
                    
                snd_pcm_status_t *status;           	
            	snd_pcm_status_alloca(&status);
                error = snd_pcm_status(pstAudOutDev->pHandle, status);
            	if (error < 0)
                {
                    HI_AUDADP_ERR("underrun occurred, snd_pcm_status error (%s)\n",snd_strerror(error));
            	}
                else
                {
            	    HI_AUDADP_INFO("underrun occurred, state = %s\n", snd_pcm_state_name(snd_pcm_status_get_state(status)));
                    if (snd_pcm_status_get_state(status) == SND_PCM_STATE_XRUN)
                    {
                        if((error = snd_pcm_prepare(pstAudOutDev->pHandle)) < 0)
                        {
                            HI_AUDADP_ERR("snd_pcm_prepare error (%s)\n",snd_strerror(error));
                        }
                	}
                }
            }
        }
        else if(ret == -EAGAIN)
        {
            HI_AUDADP_INFO("try again\n");
        }
        else if(ret < 0)
        {
            HI_AUDADP_ERR("error from writei: %d, %s\n",ret,snd_strerror(ret));
            (HI_VOID)AUDADP_Poll_AlsaEvents(pstAudOutDev);
        }
        else if (ret != (int)period_frames)
        {
            HI_AUDADP_WARN("short write, write %d frames, should write %d frames.\n", ret,(int)period_frames);
        } 
        
        AUDADP_AUD_OUT_UNLOCK();
    }

    if(HI_NULL != pReadBuf)
    {
        HI_FREE(HI_ID_AUDADP, pReadBuf);
    }
    if(HI_NULL != pWriteBuf)
    {
        HI_FREE(HI_ID_AUDADP, pWriteBuf);
    }
    HI_AUDADP_INFO("Audio out proc end.\n");
    pthread_exit(NULL);
    return HI_NULL;
}

static HI_S32 AUDADP_AudDev_Ctrl(AUDADP_ALSA_DEVICE_ATTR *pstAudDev)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if(pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
        return HI_SUCCESS;
    
    if((pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)&&(pstAudDev->s32CardNo < 0))
        return HI_SUCCESS;

    if(AUDADP_DEV_RUN_CTRL_CLOSE == pstAudDev->u32RunCtrl)
    {
        if(NULL != pstAudDev->pHandle) // close
        {
            s32Ret = AUDADP_AlsaDev_Close(pstAudDev);
        }
    }
    else
    {
        if(NULL == pstAudDev->pHandle) // open
        {
            if(pstAudDev->u32OpenDelayCnt > 0)
            {
               pstAudDev->u32OpenDelayCnt--; 
            }
            else
            {
#if 0
                if(HI_UNF_VOIP_AUD_DEV_BLUETOOTH == pstAudDev->s32AudioDevId) 
                {
                    return HI_FAILURE; // not support
                }
                else
#endif
                {
                    s32Ret = AUDADP_AlsaDev_Open(pstAudDev);
                    if(HI_SUCCESS != s32Ret)
                    {
                        pstAudDev->u32OpenDelayCnt = AUDADP_OPEN_ERR_DELAY;
                    }
                }
            }
        }
        
        if(AUDADP_DEV_RUN_CTRL_RUN == pstAudDev->u32RunCtrl)
        {
            if(HI_UNF_AUDADP_STATUS_OPENED == pstAudDev->s32Status)
            {
                (HI_VOID)AUDADP_AlsaDev_Start(pstAudDev);
            }
        }
        else
        {
            if(HI_UNF_AUDADP_STATUS_RUNNING == pstAudDev->s32Status)
            {
                (HI_VOID)AUDADP_AlsaDev_Stop(pstAudDev);
            }
        }

        if((AUDADP_DEV_RUN_CTRL_OPEN == pstAudDev->u32RunCtrl)&&(HI_UNF_AUDADP_STATUS_OPENED == pstAudDev->s32Status))
        {
            (HI_VOID)AUDADP_Poll_AlsaEvents(pstAudDev);        
        }
        
    }
    return s32Ret;
}

static HI_VOID *AUDADP_AudDev_Monitor(HI_VOID *arg)
{
    AUDADP_ALSA_DEVICE_ATTR *pstAudDev;
    HI_U32  i;
    HI_BOOL bAllClosed = HI_TRUE;
    HI_S32  s32Ret;

    HI_AUDADP_INFO("Audio device monitor thread start.\n");
//    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    while(1)
    {
        usleep(20*1000);
        for(i=0;i<HI_UNF_VOIP_AUD_DEV_BUTT;i++)
        {
            AUDADP_AUD_IN_LOCK();
            s32Ret = AUDADP_AudDev_Ctrl(&stAudDevList[i].stAudInDev);
            AUDADP_AUD_IN_UNLOCK();

            AUDADP_AUD_OUT_LOCK();
            s32Ret = AUDADP_AudDev_Ctrl(&stAudDevList[i].stAudOutDev);
            AUDADP_AUD_OUT_UNLOCK();
        }

        /*Wait all closed*/
        if(0 == stThreadMonitor.u32RunFlag)
        {
            bAllClosed = HI_TRUE;
            for(i=0;i<HI_UNF_VOIP_AUD_DEV_BUTT;i++)
            {
                AUDADP_AUD_IN_LOCK();
                pstAudDev = &stAudDevList[i].stAudInDev;
                if(NULL!=pstAudDev->pHandle)
                {
                    bAllClosed = HI_FALSE;
                    AUDADP_AUD_IN_UNLOCK();
                    break;
                }
                AUDADP_AUD_IN_UNLOCK();

                AUDADP_AUD_OUT_LOCK();
                pstAudDev = &stAudDevList[i].stAudOutDev;
                if(NULL!=pstAudDev->pHandle)
                {
                    bAllClosed = HI_FALSE;
                    AUDADP_AUD_OUT_UNLOCK();
                    break;
                }
                AUDADP_AUD_OUT_UNLOCK();
            }
            
            if(HI_TRUE == bAllClosed)
            {
                break;
            }
        }
    }
    
    HI_AUDADP_INFO("Audio device monitor thread end.\n");
    pthread_exit(NULL);
	return NULL;
}


static HI_S32  AUDADP_Thread_Init(HI_VOID)
{
    HI_S32      Ret;

    HI_AUDADP_INFO("Thread initial start.\n");

    memset(&stThreadMonitor, 0, sizeof(AUDADP_THREAD_STRU));
    Ret = pthread_mutex_init(&stThreadMonitor.tMutex,NULL);
    if(Ret != HI_SUCCESS)
    {
        HI_AUDADP_ERR("Initial thread mutex err.\n");
        return HI_FAILURE;
    }
    stThreadMonitor.u32RunFlag = 1;
    Ret = pthread_create(&stThreadMonitor.tThread, HI_NULL, AUDADP_AudDev_Monitor, HI_NULL);
    if(Ret != HI_SUCCESS)
    {
        HI_AUDADP_ERR("create audio device monitor pthread err.\n");
        pthread_mutex_destroy(&stThreadMonitor.tMutex);
        return HI_FAILURE;
    }

    memset(&stThreadAudIn, 0, sizeof(AUDADP_THREAD_STRU));
    Ret = pthread_mutex_init(&stThreadAudIn.tMutex,NULL);
    if(Ret != HI_SUCCESS)
    {
        HI_AUDADP_ERR("Initial thread mutex err.\n");
        goto Close_Monitor_Thread;
    }
    stThreadAudIn.u32RunFlag = 1;
    Ret = pthread_create(&stThreadAudIn.tThread, HI_NULL, AUDADP_Audio_In_Proc, HI_NULL);
    if(Ret != HI_SUCCESS)
    {
        HI_AUDADP_ERR("create audio in pthread err.\n");
        pthread_mutex_destroy(&stThreadAudIn.tMutex);
        goto Close_Monitor_Thread;
    }

    memset(&stThreadAudOut,0,sizeof(AUDADP_THREAD_STRU));
    Ret = pthread_mutex_init(&stThreadAudOut.tMutex,NULL);
    if(Ret != HI_SUCCESS)
    {
        HI_AUDADP_ERR("Initial thread mutex err.\n");
        goto Close_AudIn_Thread;
    }
    stThreadAudOut.u32RunFlag = 1;
    Ret = pthread_create(&stThreadAudOut.tThread, HI_NULL, AUDADP_Audio_Out_Proc, HI_NULL);
    if(Ret != HI_SUCCESS)
    {
        HI_AUDADP_ERR("create audio out pthread err.\n");
        stThreadAudOut.u32RunFlag = 0;
        pthread_mutex_destroy(&stThreadAudOut.tMutex);
        goto Close_AudIn_Thread;
    }
    
    HI_AUDADP_INFO("Thread initial success.\n");
    return HI_SUCCESS;

Close_AudIn_Thread:
    stThreadAudIn.u32RunFlag = 0;
    pthread_join(stThreadAudIn.tThread, NULL);
    memset(&stThreadAudIn,0,sizeof(AUDADP_THREAD_STRU));
    pthread_mutex_destroy(&stThreadAudIn.tMutex);

Close_Monitor_Thread:
    stThreadMonitor.u32RunFlag = 0;
    pthread_join(stThreadMonitor.tThread, NULL);
    memset(&stThreadMonitor,0,sizeof(AUDADP_THREAD_STRU));
    pthread_mutex_destroy(&stThreadMonitor.tMutex);
    
    HI_AUDADP_ERR("Thread initial failure.\n");
    return HI_FAILURE;
}

static HI_S32  AUDADP_Thread_DeInit(HI_VOID)
{
    HI_S32      Ret;

    HI_AUDADP_INFO("Thread deinitial start.\n");

    stThreadAudIn.u32RunFlag = 0;
    pthread_join(stThreadAudIn.tThread, NULL);
    pthread_mutex_destroy(&stThreadAudIn.tMutex);
    memset(&stThreadAudIn,0,sizeof(AUDADP_THREAD_STRU));
    
    stThreadAudOut.u32RunFlag = 0;
    Ret = ioctl(g_AudAdpDevFd,CMD_AUDADP_PTHREAD_WAKE_UP);
    if (Ret != HI_SUCCESS)
    {
        HI_AUDADP_INFO("Send wake up audio out pthread command failure.\n");
    }
    pthread_join(stThreadAudOut.tThread, NULL);
    pthread_mutex_destroy(&stThreadAudOut.tMutex);
    memset(&stThreadAudOut,0,sizeof(AUDADP_THREAD_STRU));

    stThreadMonitor.u32RunFlag = 0;
//    pthread_cancel(stThreadMonitor.tThread);
    pthread_join(stThreadMonitor.tThread, NULL);
    pthread_mutex_destroy(&stThreadMonitor.tMutex);
    memset(&stThreadMonitor,0,sizeof(AUDADP_THREAD_STRU));

    HI_AUDADP_INFO("Thread deinitial end.\n");

    return Ret;
}

HI_S32 HI_MPI_ALSA_GetAudioDevList(HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType,HI_ALSA_CARD_INFO_S * pstCardList,HI_U32 u32Max,HI_U32 *pu32Count)
{
	snd_ctl_t *handle;
	HI_S32 card, err;
	snd_ctl_card_info_t *info;
	snd_pcm_info_t *pcminfo;
	snd_pcm_stream_t stream;
    HI_U32 i = 0;
    
    CHECK_NULL_PTR(pstCardList);
    CHECK_NULL_PTR(pu32Count);
    if(u32Max == 0)
        return HI_ERR_VOIP_HME_INVALID_PARA;
    *pu32Count = 0;
    
    snd_ctl_card_info_alloca(&info);
    snd_pcm_info_alloca(&pcminfo);

    if(HI_UNF_VOIP_AUD_IN_DEV == enAudioDevType)
        stream = SND_PCM_STREAM_CAPTURE;
    else
        stream = SND_PCM_STREAM_PLAYBACK;

    card = -1;
    if (snd_card_next(&card) < 0 || card < 0) {
        HI_AUDADP_ERR("no soundcards found...\n");
        return HI_SUCCESS;
    }
//	HI_AUDADP_INFO("\n**** List of %s Hardware Devices ****\n",snd_pcm_stream_name(stream));
    while (card >= 0) {
        char name[32];
        snprintf(name, sizeof(name), "hw:%d", card);
        if ((err = snd_ctl_open(&handle, name, 0)) < 0) {
            HI_AUDADP_ERR("control open (%i): %s\n", card, snd_strerror(err));
            goto next_card;
        }
        if ((err = snd_ctl_card_info(handle, info)) < 0) {
            HI_AUDADP_ERR("control hardware info (%i): %s\n", card, snd_strerror(err));
            snd_ctl_close(handle);
            goto next_card;
        }
        
        snd_pcm_info_set_stream(pcminfo, stream);
        if ((err = snd_ctl_pcm_info(handle, pcminfo)) < 0) {
            if (err != -ENOENT)
                HI_AUDADP_INFO("control digital audio info (%i): %s\n", card, snd_strerror(err));
            else
                HI_AUDADP_INFO("get pcm info failure (%i): %s\n", card, snd_strerror(err));
            snd_ctl_close(handle);
            goto next_card;
		}
   #if 0     
        HI_AUDADP_INFO("\ncard %i info: %s\n",card,snd_ctl_name(handle));
        HI_AUDADP_INFO("type: %s\n",snd_pcm_stream_name(stream));
        HI_AUDADP_INFO("id: %s\n",snd_ctl_card_info_get_id(info));
        HI_AUDADP_INFO("name: %s\n",snd_ctl_card_info_get_name(info));
        HI_AUDADP_INFO("driver: %s\n",snd_ctl_card_info_get_driver(info));
        HI_AUDADP_INFO("longname: %s\n",snd_ctl_card_info_get_longname(info));
        HI_AUDADP_INFO("mixername: %s\n",snd_ctl_card_info_get_mixername(info));
        HI_AUDADP_INFO("components: %s\n",snd_ctl_card_info_get_components(info));
        HI_AUDADP_INFO("pcm_name: %s\n",snd_pcm_info_get_name(pcminfo));
    #endif
        pstCardList[i].s32CardNo = card;
        pstCardList[i].enType = enAudioDevType;
        if(NULL == snd_ctl_card_info_get_name(info))
        {
            strncpy(pstCardList[i].szName,"unKnow",sizeof(pstCardList[i].szName));
        }
        else
        {
            strncpy(pstCardList[i].szName,snd_ctl_card_info_get_name(info),sizeof(pstCardList[i].szName));
            pstCardList[i].szName[HI_ALSA_AUD_DEV_NAME_LEN -1] = '\0';
        }
        
        i++;
        snd_ctl_close(handle);
        if(i >= u32Max)
            break;
        next_card:
        if (snd_card_next(&card) < 0) {
            HI_AUDADP_ERR("snd_card_next\n");
            break;
        }
    }

    *pu32Count = i;
    usleep(100*1000);
    return HI_SUCCESS;
}

HI_S32 HI_MPI_ALSA_GetAudioDevRateRange(HI_ALSA_CARD_INFO_S * pstCardInfo, HI_U32 *pu32Min, HI_U32 *pu32Max)
{
    HI_S32 err = 0;
    HI_CHAR name[HI_ALSA_AUD_DEV_NAME_LEN];
    snd_pcm_t *pHandle = NULL;
    snd_pcm_hw_params_t *hw_params = NULL;
    snd_pcm_stream_t stream;
    HI_S32 dir;

    CHECK_NULL_PTR(pstCardInfo);
    CHECK_NULL_PTR(pu32Min);
    CHECK_NULL_PTR(pu32Max);
#if 0
    if(pstCardInfo->s32CardNo < 0)
        return HI_ERR_VOIP_HME_INVALID_PARA;
#endif
    
    *pu32Min = 0;
    *pu32Max = 0;

    if(HI_UNF_VOIP_AUD_IN_DEV == pstCardInfo->enType)
    {
        stream = SND_PCM_STREAM_CAPTURE;
        AUDADP_AUD_IN_LOCK();
    }
    else
    {
        stream = SND_PCM_STREAM_PLAYBACK;
        AUDADP_AUD_OUT_LOCK();
    }
    
    snprintf(name, sizeof(name), "hw:%d", pstCardInfo->s32CardNo);  
    if ((err = snd_pcm_open(&pHandle, name, stream, 0)) < 0) {
        HI_AUDADP_ERR("cannot open audio device %s (%s)\n", 
        	 name,
        	 snd_strerror(err));
    	goto exit_alsa_dev_close;
    }
    HI_AUDADP_INFO("snd_pcm_open() %s %s OK, handle %x!\n",snd_pcm_stream_name(stream),name,pHandle);

    if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
    	HI_AUDADP_ERR("cannot allocate hardware parameter structure (%s)\n",
    		 snd_strerror(err));
    	goto exit_alsa_dev_close;
    }
    HI_AUDADP_INFO("snd_pcm_hw_params_malloc()  OK!\n");
    
    if ((err = snd_pcm_hw_params_any(pHandle, hw_params)) < 0) {
    	HI_AUDADP_ERR("cannot initialize hardware parameter structure (%s)\n",
    		 snd_strerror(err));
    	goto exit_free_hw_params;
    }
    HI_AUDADP_INFO("snd_pcm_hw_params_any()  OK!\n");
    
    if ((err = snd_pcm_hw_params_get_rate_min(hw_params, pu32Min, &dir)) < 0) {
        HI_AUDADP_ERR("cannot get rate min (%s)\n",
        	 snd_strerror(err));
    	goto exit_free_hw_params;
    }
    HI_AUDADP_INFO("get rate min success, value is [%d]\n",*pu32Min);

    if ((err = snd_pcm_hw_params_get_rate_max(hw_params, pu32Max, &dir)) < 0) {
        HI_AUDADP_ERR("cannot get rate max (%s)\n",
        	 snd_strerror(err));
    	goto exit_free_hw_params;
    }
    HI_AUDADP_INFO("get rate max success, value is [%d]\n",*pu32Max);
        
exit_free_hw_params:
   if(NULL != hw_params)
    {
        snd_pcm_hw_params_free(hw_params);
        hw_params = NULL;
    }

exit_alsa_dev_close:
    if(NULL != pHandle)
    {
        snd_pcm_close(pHandle);
        pHandle = NULL;
    }
    
    if(HI_UNF_VOIP_AUD_IN_DEV == pstCardInfo->enType)
    {
        AUDADP_AUD_IN_UNLOCK();
    }
    else
    {
        AUDADP_AUD_OUT_UNLOCK();
    }

    usleep(100*1000);

    if(err < 0 )  
        return HI_ERR_VOIP_HME_INVALID_OPT;
    else
        return HI_SUCCESS;
}

HI_S32 HI_MPI_AUDADP_AudDev_Open(HI_UNF_AUDADP_AUDDEV_PARA_S *pstAudDevPara,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    AUDADP_ALSA_DEVICE_ATTR *pstAudDev;
        
    const HI_CHAR * AudInDevName[] = {
        "sio_ai",          
        "hi_bluetooth",          
        "usb_mic",          
    };

    const HI_CHAR * AudOutDevName[] = {
        "sio_ao",          
        "hi_bluetooth",          
        "ao",          
    };

    CHECK_AUDADP_INIT();
    CHECK_NULL_PTR(pstAudDevPara);
    CHECK_DEV_ID(pstAudDevPara->s32AudioDevId);
    
    (HI_VOID)AUDADP_Drv_Clear_Buffer(pstAudDevPara->s32AudioDevId, stAudDevOptFlag);

    if(stAudDevOptFlag.bit1AudInDev)
    {
//        if(pstAudDevPara->s32AudioDevId != HI_UNF_VOIP_AUD_DEV_SIO)   // not SIO
        {
            if(((pstAudDevPara->s32AiSampleRate != 8000)
		   &&(pstAudDevPara->s32AiSampleRate != 16000)
		   &&(pstAudDevPara->s32AiSampleRate != 32000)
		   &&(pstAudDevPara->s32AiSampleRate != 48000))
                ||(pstAudDevPara->s32AiBitPerSample != 16)
                ||(pstAudDevPara->s32AiChannels != 1))
            {
                HI_AUDADP_ERR("Invalid audio in device para.\n");            
                return HI_ERR_VOIP_HME_INVALID_PARA;
            }

            if((pstAudDevPara->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)&&(pstAudDevPara->s32AiCardNo < 0))
            {
                HI_AUDADP_ERR("Invalid audio in device card number.\n");            
                return HI_ERR_VOIP_HME_INVALID_PARA;
            }
            
            AUDADP_AUD_IN_LOCK();
            pstAudDev = &stAudDevList[pstAudDevPara->s32AudioDevId].stAudInDev;
            memset(pstAudDev,0,sizeof(AUDADP_ALSA_DEVICE_ATTR));
            pstAudDev->s32AudioDevId = pstAudDevPara->s32AudioDevId;
            if((pstAudDevPara->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)&&(pstAudDevPara->s32AiCardNo >= 0))
            {
                pstAudDev->s32CardNo = pstAudDevPara->s32AiCardNo;
                snprintf(pstAudDev->s8Name,sizeof(pstAudDev->s8Name),"hw:%d",pstAudDevPara->s32AiCardNo);
            }   
            else
            {
                pstAudDev->s32CardNo = -1;
                strncpy(pstAudDev->s8Name,AudInDevName[pstAudDevPara->s32AudioDevId],sizeof(pstAudDev->s8Name));
                pstAudDev->s8Name[HI_ALSA_AUD_DEV_NAME_LEN -1] = '\0';
            }
            pstAudDev->s32SampleRate = pstAudDevPara->s32AiSampleRate;
            pstAudDev->s32BitPerSample = pstAudDevPara->s32AiBitPerSample;
            pstAudDev->s32Channels = pstAudDevPara->s32AiChannels;
            pstAudDev->stream = SND_PCM_STREAM_CAPTURE;
            if(AUDADP_DEV_RUN_CTRL_CLOSE == pstAudDev->u32RunCtrl)
            {
                pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_OPEN;
            }
            
            if(pstAudDevPara->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
            }
            AUDADP_AUD_IN_UNLOCK();
            HI_AUDADP_INFO("Open audio in device %d.\n",pstAudDevPara->s32AudioDevId);
        }
    }

    if(stAudDevOptFlag.bit1AudOutDev)
    {
//        if(pstAudDevPara->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_BLUETOOTH)   // is bluetooth
        {
            if(((pstAudDevPara->s32AoSampleRate != 8000)
		   &&(pstAudDevPara->s32AoSampleRate != 16000)
		   &&(pstAudDevPara->s32AoSampleRate != 32000)
		   &&(pstAudDevPara->s32AoSampleRate != 48000))
                ||(pstAudDevPara->s32AoBitPerSample != 16)
                ||(pstAudDevPara->s32AoChannels != 1))
            {
                HI_AUDADP_ERR("Invalid audio out device para.\n");            
                return HI_ERR_VOIP_HME_INVALID_PARA;
            }
            
            AUDADP_AUD_OUT_LOCK();
            pstAudDev = &stAudDevList[pstAudDevPara->s32AudioDevId].stAudOutDev;
            memset(pstAudDev,0,sizeof(AUDADP_ALSA_DEVICE_ATTR));
            pstAudDev->s32AudioDevId = pstAudDevPara->s32AudioDevId;
            if((pstAudDevPara->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)&&(pstAudDevPara->s32AoCardNo >= 0))
            {
                pstAudDev->s32CardNo = pstAudDevPara->s32AoCardNo;
                snprintf(pstAudDev->s8Name,sizeof(pstAudDev->s8Name),"hw:%d",pstAudDevPara->s32AoCardNo);
            }
            else
            {
                pstAudDev->s32CardNo = -1;
                strncpy(pstAudDev->s8Name,AudOutDevName[pstAudDevPara->s32AudioDevId],sizeof(pstAudDev->s8Name));
                pstAudDev->s8Name[HI_ALSA_AUD_DEV_NAME_LEN -1] = '\0';
            }
            pstAudDev->s32SampleRate = pstAudDevPara->s32AoSampleRate;
            pstAudDev->s32BitPerSample = pstAudDevPara->s32AoBitPerSample;
            pstAudDev->s32Channels = pstAudDevPara->s32AoChannels;
            pstAudDev->stream = SND_PCM_STREAM_PLAYBACK;
            if(AUDADP_DEV_RUN_CTRL_CLOSE == pstAudDev->u32RunCtrl)
            {
                pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_OPEN;
            }
            
            if(pstAudDevPara->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
            }
            else if((pstAudDevPara->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)&&(pstAudDevPara->s32AoCardNo < 0))   //hiao
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
            }
                
            AUDADP_AUD_OUT_UNLOCK();
            HI_AUDADP_INFO("Open audio out device %d.\n",pstAudDevPara->s32AudioDevId);
        }
    }

    (HI_VOID)AUDADP_Drv_SetAttr(pstAudDevPara->s32AudioDevId, stAudDevOptFlag);
    return HI_SUCCESS;
}

HI_S32 HI_MPI_AUDADP_AudDev_Close(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    AUDADP_ALSA_DEVICE_ATTR *pstAudDev;
    HI_U32 i = 0;

    CHECK_AUDADP_INIT();
    CHECK_DEV_ID(s32AudioDevId);
    if (stAudDevList[s32AudioDevId].stAudInDev.u32RunCtrl == AUDADP_DEV_RUN_CTRL_CLOSE &&
        stAudDevList[s32AudioDevId].stAudOutDev.u32RunCtrl == AUDADP_DEV_RUN_CTRL_CLOSE)
    {
        HI_AUDADP_INFO("Audio device has closed yet\n");
        return HI_SUCCESS;
    }

    if(stAudDevOptFlag.bit1AudInDev)
    {
//        if(s32AudioDevId != HI_UNF_VOIP_AUD_DEV_SIO)
        {
            HI_AUDADP_INFO("Close audio in device %d.\n",s32AudioDevId);
            AUDADP_AUD_IN_LOCK();
            pstAudDev = &stAudDevList[s32AudioDevId].stAudInDev;
            pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_CLOSE;
            if(pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_CLOSED;
            }
            
            AUDADP_AUD_IN_UNLOCK();
            
            i = 0;
            do
            {
                AUDADP_AUD_IN_LOCK();
                if(pstAudDev->pHandle == NULL)
                {
                    AUDADP_AUD_IN_UNLOCK();
                    break;
                }
                AUDADP_AUD_IN_UNLOCK();
                usleep(10*1000);
                i++;
            }while(i < 10);
            
        }
    }

    if(stAudDevOptFlag.bit1AudOutDev)
    {
//        if(s32AudioDevId == HI_UNF_VOIP_AUD_DEV_BLUETOOTH)
        {
            HI_AUDADP_INFO("Close audio out device %d.\n",s32AudioDevId);
            AUDADP_AUD_OUT_LOCK();
            pstAudDev = &stAudDevList[s32AudioDevId].stAudOutDev;
            pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_CLOSE;

            if(pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_CLOSED;
            }
            else if((pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)&&(pstAudDev->s32CardNo < 0))   //hiao
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_CLOSED;
            }
            AUDADP_AUD_OUT_UNLOCK();
            
            i = 0;
            do
            {
                AUDADP_AUD_OUT_LOCK();
                if(pstAudDev->pHandle == NULL)
                {
                    AUDADP_AUD_OUT_UNLOCK();
                    break;
                }
                AUDADP_AUD_OUT_UNLOCK();
                usleep(10*1000);
                i++;
            }while(i < 10);
            
        }
    }

    (HI_VOID)AUDADP_Drv_SetAttr(s32AudioDevId, stAudDevOptFlag);
    (HI_VOID)AUDADP_Drv_Clear_Buffer(s32AudioDevId, stAudDevOptFlag);
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_AUDADP_AudDev_Start(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    AUDADP_ALSA_DEVICE_ATTR *pstAudDev;

    CHECK_AUDADP_INIT();
    CHECK_DEV_ID(s32AudioDevId);
    if (stAudDevList[s32AudioDevId].stAudInDev.u32RunCtrl == AUDADP_DEV_RUN_CTRL_CLOSE &&
        stAudDevList[s32AudioDevId].stAudOutDev.u32RunCtrl == AUDADP_DEV_RUN_CTRL_CLOSE)
    {
        HI_AUDADP_ERR("Audio device hasn't open yet\n");
        return HI_FAILURE;
    }  
    
    (HI_VOID)AUDADP_Drv_Clear_Buffer(s32AudioDevId, stAudDevOptFlag);

    if(stAudDevOptFlag.bit1AudInDev)
    {
//        if(s32AudioDevId != HI_UNF_VOIP_AUD_DEV_SIO)
        {
            AUDADP_AUD_IN_LOCK();
            pstAudDev = &stAudDevList[s32AudioDevId].stAudInDev;
            if(pstAudDev->u32RunCtrl != AUDADP_DEV_RUN_CTRL_CLOSE)
            {
                pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_RUN;
            }

            if(pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_RUNNING;
            }
            AUDADP_AUD_IN_UNLOCK();
            HI_AUDADP_INFO("Start audio in device %d.\n",s32AudioDevId);
        }
    }

    if(stAudDevOptFlag.bit1AudOutDev)
    {
//        if(s32AudioDevId == HI_UNF_VOIP_AUD_DEV_BLUETOOTH)
        {
            AUDADP_AUD_OUT_LOCK();
            pstAudDev = &stAudDevList[s32AudioDevId].stAudOutDev;
            if(pstAudDev->u32RunCtrl != AUDADP_DEV_RUN_CTRL_CLOSE)
            {
                pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_RUN;
            }
            
            if(pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_RUNNING;
            }
            else if((pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)&&(pstAudDev->s32CardNo < 0))   //hiao
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_RUNNING;
            }
            AUDADP_AUD_OUT_UNLOCK();
            HI_AUDADP_INFO("Start audio out device %d.\n",s32AudioDevId);
        }
    }

    (HI_VOID)AUDADP_Drv_SetAttr(s32AudioDevId, stAudDevOptFlag);

    return HI_SUCCESS;
}

HI_S32 HI_MPI_AUDADP_AudDev_Stop(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    AUDADP_ALSA_DEVICE_ATTR *pstAudDev;
    
    CHECK_AUDADP_INIT();
    CHECK_DEV_ID(s32AudioDevId);
    if (stAudDevList[s32AudioDevId].stAudInDev.u32RunCtrl == AUDADP_DEV_RUN_CTRL_CLOSE &&
        stAudDevList[s32AudioDevId].stAudOutDev.u32RunCtrl == AUDADP_DEV_RUN_CTRL_CLOSE)
    {
        HI_AUDADP_ERR("Audio device hasn't open yet\n");
        return HI_FAILURE;
    }

    if(stAudDevOptFlag.bit1AudInDev)
    {
//        if(s32AudioDevId != HI_UNF_VOIP_AUD_DEV_SIO)
        {
            AUDADP_AUD_IN_LOCK();
            pstAudDev = &stAudDevList[s32AudioDevId].stAudInDev;
            if(pstAudDev->u32RunCtrl == AUDADP_DEV_RUN_CTRL_RUN)
            {
                pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_OPEN;
            }

            if(pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
            }

            AUDADP_AUD_IN_UNLOCK();
        }
    }

    if(stAudDevOptFlag.bit1AudOutDev)
    {
//        if(s32AudioDevId == HI_UNF_VOIP_AUD_DEV_BLUETOOTH)
        {
            AUDADP_AUD_OUT_LOCK();
            pstAudDev = &stAudDevList[s32AudioDevId].stAudOutDev;
            if(pstAudDev->u32RunCtrl == AUDADP_DEV_RUN_CTRL_RUN)
            {
                pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_OPEN;
            }
            
            if(pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
            }
            else if((pstAudDev->s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)&&(pstAudDev->s32CardNo < 0))   //hiao
            {
                pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
            }
            AUDADP_AUD_OUT_UNLOCK();
        }
    }

    (HI_VOID)AUDADP_Drv_SetAttr(s32AudioDevId, stAudDevOptFlag);
    (HI_VOID)AUDADP_Drv_Clear_Buffer(s32AudioDevId, stAudDevOptFlag);
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_AUDADP_AudDev_GetStatus(HI_S32 s32AudioDevId, HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType, HI_S32 *ps32Status)
{
    CHECK_AUDADP_INIT();
    CHECK_DEV_ID(s32AudioDevId);
    CHECK_NULL_PTR(ps32Status);

    if(HI_UNF_VOIP_AUD_IN_DEV == enAudioDevType)
    {
        *ps32Status = stAudDevList[s32AudioDevId].stAudInDev.s32Status;
    }
    else
    {
        *ps32Status = stAudDevList[s32AudioDevId].stAudOutDev.s32Status;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_AUDADP_RegisterEvent(HI_UNF_AUDADP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args)
{
    CHECK_AUDADP_INIT();
    stAudadpEventCb.pfnAudadpEventCb = pfnEventCB;
    stAudadpEventCb.stAudAdpEvent.u32Args = u32Args;
    return HI_SUCCESS;
}

HI_S32 HI_MPI_AUDADP_Init(HI_VOID)
{
    struct stat st;
    HI_S32 Ret;
        
    HI_AUDADP_INFO("Initial start.\n");

    if (g_AudAdpDevFd >= 0)
    {
        HI_AUDADP_ERR("HME has been opened, g_AudAdpDevFd:%d\n", g_AudAdpDevFd);
        return HI_SUCCESS;
    }

    if (HI_FAILURE == stat(g_AudAdpDevName, &st))
    {
        HI_AUDADP_ERR("%s is not exist.\n",g_AudAdpDevName);
        return HI_ERR_VOIP_HME_DEV_NOT_EXIST;
    }

    if (!S_ISCHR (st.st_mode))
    {
        HI_AUDADP_ERR("%s is not device.\n",g_AudAdpDevName);
        return HI_ERR_VOIP_HME_NOT_DEV_FILE;
    }

    g_AudAdpDevFd = open(g_AudAdpDevName, O_RDWR|O_NONBLOCK, 0);

    if (g_AudAdpDevFd < 0)
    {
        HI_AUDADP_ERR("open %s err.\n",g_AudAdpDevName);
        return HI_ERR_VOIP_HME_DEV_OPEN_ERR;
    }

    memset(&stAudDevList,0,sizeof(AUDADP_ALSA_DEVICE)*HI_UNF_VOIP_AUD_DEV_BUTT);  
    Ret = AUDADP_Thread_Init();
    if(HI_SUCCESS != Ret)
    {
        close(g_AudAdpDevFd);
        g_AudAdpDevFd = -1;

        HI_AUDADP_ERR("Process init err.\n");
        return HI_ERR_VOIP_HME_UNKNOWN;
    }
    memset(&stAudadpEventCb,0,sizeof(AUDADP_EVENT_CB_S));
    HI_AUDADP_INFO("Initial end.\n");

    return HI_SUCCESS;
}


HI_S32 HI_MPI_AUDADP_DeInit(HI_VOID)
{
    HI_U32  i;
    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;

    HI_AUDADP_INFO("Deinitial start.\n");

    if (g_AudAdpDevFd < 0)
    {
        return HI_SUCCESS;
    }

    stAudDevOptFlag.bit1AudInDev = 1;
    stAudDevOptFlag.bit1AudOutDev = 1;
    stAudDevOptFlag.bit30Resv = 0;
    for(i=0;i<HI_UNF_VOIP_AUD_DEV_BUTT;i++)
    {
        HI_MPI_AUDADP_AudDev_Close((HI_S32)i,stAudDevOptFlag);
    }

    (HI_VOID)AUDADP_Thread_DeInit();
    
    close(g_AudAdpDevFd);

    g_AudAdpDevFd = -1;
    
    HI_AUDADP_INFO("Deinitial end.\n");
    return HI_SUCCESS;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

