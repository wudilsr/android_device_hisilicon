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
#include "hi_drv_struct.h"
#include "mpi_aud_adp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

static HI_S32           g_AudAdpDevFd = -1;
static const HI_CHAR    g_AudAdpDevName[] = "/dev/"UMAP_DEVNAME_AUDADP;

typedef struct
{
    AUDADP_DRV_DEVICE_ATTR stAudInDev;
    AUDADP_DRV_DEVICE_ATTR stAudOutDev;
}AUDADP_DRV_DEVICE_S;

static AUDADP_DRV_DEVICE_S stAudDevList[HI_UNF_VOIP_AUD_DEV_BUTT];

#define CHECK_AUDADP_INIT()\
do{\
	if (g_AudAdpDevFd < 0)\
	{\
		HI_AUDADP_ERR("AUDADP is not init.\n");\
		return HI_ERR_VOIP_HME_NO_INIT;\
	}\
}while(0)

static HI_S32 AUDADP_Drv_SetAttr(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    HI_S32 ret;
    
    AUDADP_IOCTL_SET_ATTR_S stIoctlSetAttr;

    memset(&stIoctlSetAttr,0,sizeof(AUDADP_IOCTL_SET_ATTR_S));
    
    stIoctlSetAttr.s32AudioDevId = s32AudioDevId;
    stIoctlSetAttr.stAudDevOptFlag = stAudDevOptFlag;
    if(stAudDevOptFlag.bit1AudInDev)
    {
        stIoctlSetAttr.pstAudInDev = &stAudDevList[s32AudioDevId].stAudInDev;
    }
    
    if(stAudDevOptFlag.bit1AudOutDev)
    {
        stIoctlSetAttr.pstAudOutDev = &stAudDevList[s32AudioDevId].stAudOutDev;
    }
    ret = ioctl(g_AudAdpDevFd, CMD_AUDADP_SET_ATTR, &stIoctlSetAttr);
    return ret;
}

HI_S32 HI_MPI_ALSA_GetAudioDevList(HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType,HI_ALSA_CARD_INFO_S * pstCardList,HI_U32 u32Max,HI_U32 *pu32Count)
{
    return HI_ERR_VOIP_HME_NOT_SUPPORTED;
}

HI_S32 HI_MPI_ALSA_GetAudioDevRateRange(HI_ALSA_CARD_INFO_S * pstCardInfo, HI_U32 *pu32Min, HI_U32 *pu32Max)
{
    return HI_ERR_VOIP_HME_NOT_SUPPORTED;
}

HI_S32  HI_MPI_AUDADP_AudDev_Open(HI_UNF_AUDADP_AUDDEV_PARA_S *pstAudDevPara,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    AUDADP_DRV_DEVICE_ATTR *pstAudDev;

    CHECK_AUDADP_INIT();
    CHECK_NULL_PTR(pstAudDevPara);
    if(pstAudDevPara->s32AudioDevId != HI_UNF_VOIP_AUD_DEV_SIO)
    {
        HI_AUDADP_ERR("Invalid audio device id.\n");            
    	return HI_ERR_VOIP_HME_INVALID_PARA;
    }

    if(stAudDevOptFlag.bit1AudInDev)
    {
        if(((pstAudDevPara->s32AiSampleRate != 8000))
            ||(pstAudDevPara->s32AiBitPerSample != 16)
            ||(pstAudDevPara->s32AiChannels != 1))
        {
            HI_AUDADP_ERR("Invalid audio in device para.\n");            
            return HI_ERR_VOIP_HME_INVALID_PARA;
        }

        pstAudDev = &stAudDevList[pstAudDevPara->s32AudioDevId].stAudInDev;
        memset(pstAudDev,0,sizeof(AUDADP_DRV_DEVICE_ATTR));
        pstAudDev->s32AudioDevId = pstAudDevPara->s32AudioDevId;
        pstAudDev->s32CardNo = pstAudDevPara->s32AiCardNo;
        sprintf(pstAudDev->s8Name,"sio_ai");
        pstAudDev->s32SampleRate = pstAudDevPara->s32AiSampleRate;
        pstAudDev->s32BitPerSample = pstAudDevPara->s32AiBitPerSample;
        pstAudDev->s32Channels = pstAudDevPara->s32AiChannels;
        pstAudDev->u32Type = HI_UNF_VOIP_AUD_IN_DEV;
        pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_OPEN;
        pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
    }

    if(stAudDevOptFlag.bit1AudOutDev)
    {
        if(((pstAudDevPara->s32AoSampleRate != 8000))
            ||(pstAudDevPara->s32AoBitPerSample != 16)
            ||(pstAudDevPara->s32AoChannels != 1))
        {
            HI_AUDADP_ERR("Invalid audio out device para.\n");            
            return HI_ERR_VOIP_HME_INVALID_PARA;
        }

        pstAudDev = &stAudDevList[pstAudDevPara->s32AudioDevId].stAudOutDev;
        memset(pstAudDev,0,sizeof(AUDADP_DRV_DEVICE_ATTR));
        pstAudDev->s32AudioDevId = pstAudDevPara->s32AudioDevId;
        pstAudDev->s32CardNo = pstAudDevPara->s32AoCardNo;
        sprintf(pstAudDev->s8Name,"sio_ao");
        pstAudDev->s32SampleRate = pstAudDevPara->s32AiSampleRate;
        pstAudDev->s32BitPerSample = pstAudDevPara->s32AiBitPerSample;
        pstAudDev->s32Channels = pstAudDevPara->s32AiChannels;
        pstAudDev->u32Type = HI_UNF_VOIP_AUD_OUT_DEV;
        pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_OPEN;
        pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
    }
    
    (HI_VOID)AUDADP_Drv_SetAttr(pstAudDevPara->s32AudioDevId, stAudDevOptFlag);
    return HI_SUCCESS;
}

HI_S32  HI_MPI_AUDADP_AudDev_Close(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    AUDADP_DRV_DEVICE_ATTR *pstAudDev;

    CHECK_AUDADP_INIT();
    if(s32AudioDevId != HI_UNF_VOIP_AUD_DEV_SIO)
    {
    	return HI_ERR_VOIP_HME_INVALID_PARA;
    }  

    if(stAudDevOptFlag.bit1AudInDev)
    {

        pstAudDev = &stAudDevList[s32AudioDevId].stAudInDev;
        pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_CLOSE;
        pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_CLOSED;
    }

    if(stAudDevOptFlag.bit1AudOutDev)
    {

        pstAudDev = &stAudDevList[s32AudioDevId].stAudOutDev;
        pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_CLOSE;
        pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_CLOSED;
    }
    
    (HI_VOID)AUDADP_Drv_SetAttr(s32AudioDevId, stAudDevOptFlag);
    
    return HI_SUCCESS;
}

HI_S32  HI_MPI_AUDADP_AudDev_Start(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    AUDADP_DRV_DEVICE_ATTR *pstAudDev;

    CHECK_AUDADP_INIT();
    if(s32AudioDevId != HI_UNF_VOIP_AUD_DEV_SIO)
    {
    	return HI_ERR_VOIP_HME_INVALID_PARA;
    }  

    if(stAudDevOptFlag.bit1AudInDev)
    {

        pstAudDev = &stAudDevList[s32AudioDevId].stAudInDev;
        if(pstAudDev->u32RunCtrl != AUDADP_DEV_RUN_CTRL_CLOSE)
        {
            pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_RUN;
            pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_RUNNING;
        }
    }

    if(stAudDevOptFlag.bit1AudOutDev)
    {

        pstAudDev = &stAudDevList[s32AudioDevId].stAudOutDev;
        if(pstAudDev->u32RunCtrl != AUDADP_DEV_RUN_CTRL_CLOSE)
        {
            pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_RUN;
            pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_RUNNING;
        }
    }
    
    (HI_VOID)AUDADP_Drv_SetAttr(s32AudioDevId, stAudDevOptFlag);
    
    return HI_SUCCESS;
}

HI_S32  HI_MPI_AUDADP_AudDev_Stop(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    AUDADP_DRV_DEVICE_ATTR *pstAudDev;

    CHECK_AUDADP_INIT();
    if(s32AudioDevId != HI_UNF_VOIP_AUD_DEV_SIO)
    {
    	return HI_ERR_VOIP_HME_INVALID_PARA;
    }  

    if(stAudDevOptFlag.bit1AudInDev)
    {

        pstAudDev = &stAudDevList[s32AudioDevId].stAudInDev;
        if(pstAudDev->u32RunCtrl != AUDADP_DEV_RUN_CTRL_CLOSE)
        {
            pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_OPEN;
            pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
        }
    }

    if(stAudDevOptFlag.bit1AudOutDev)
    {

        pstAudDev = &stAudDevList[s32AudioDevId].stAudOutDev;
        if(pstAudDev->u32RunCtrl != AUDADP_DEV_RUN_CTRL_CLOSE)
        {
            pstAudDev->u32RunCtrl = AUDADP_DEV_RUN_CTRL_OPEN;
            pstAudDev->s32Status = HI_UNF_AUDADP_STATUS_OPENED;
        }
    }
    
    (HI_VOID)AUDADP_Drv_SetAttr(s32AudioDevId, stAudDevOptFlag);
    
    return HI_SUCCESS;
}

HI_S32  HI_MPI_AUDADP_AudDev_GetStatus(HI_S32 s32AudioDevId, HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType, HI_S32 *ps32Status)
{
    CHECK_AUDADP_INIT();
    CHECK_NULL_PTR(ps32Status);
    if(s32AudioDevId != HI_UNF_VOIP_AUD_DEV_SIO)
    {
    	return HI_ERR_VOIP_HME_INVALID_PARA;
    }
    
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
    return HI_SUCCESS;
}


HI_S32 HI_MPI_AUDADP_Init(HI_VOID)
{
    struct stat st;
            
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
   
    HI_AUDADP_INFO("Initial end.\n");

    return HI_SUCCESS;
}


HI_S32 HI_MPI_AUDADP_DeInit(HI_VOID)
{

    HI_AUDADP_INFO("Deinitial start.\n");

    if (g_AudAdpDevFd < 0)
    {
        return HI_SUCCESS;
    }
    
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

