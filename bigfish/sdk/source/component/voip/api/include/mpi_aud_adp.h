/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_aud_adp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011/3/3
  Description   :
  History       :
  1.Date        : 2011/3/3
    Author      : f00172091
    Modification: Created file

*******************************************************************************/


#ifndef __MPI_AUD_ADP_H__
#define __MPI_AUD_ADP_H__

#include "priv_audadp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

HI_S32 HI_MPI_AUDADP_Init(HI_VOID);
HI_S32 HI_MPI_AUDADP_DeInit(HI_VOID);
HI_S32 HI_MPI_AUDADP_AudDev_Open(HI_UNF_AUDADP_AUDDEV_PARA_S *pstAudDev, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);
HI_S32 HI_MPI_AUDADP_AudDev_Close(HI_S32 s32AudioDevId, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);
HI_S32 HI_MPI_AUDADP_AudDev_Start(HI_S32 s32AudioDevId, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);
HI_S32 HI_MPI_AUDADP_AudDev_Stop(HI_S32 s32AudioDevId, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);
HI_S32 HI_MPI_AUDADP_AudDev_GetStatus(HI_S32 s32AudioDevId, HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType, HI_S32 *ps32Status);
HI_S32 HI_MPI_AUDADP_RegisterEvent(HI_UNF_AUDADP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args);
HI_S32 HI_MPI_ALSA_GetAudioDevList(HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType,HI_ALSA_CARD_INFO_S * pstCardList,HI_U32 u32Max,HI_U32 *pu32Count);
HI_S32 HI_MPI_ALSA_GetAudioDevRateRange(HI_ALSA_CARD_INFO_S * pstCardInfo, HI_U32 *pu32Min, HI_U32 *pu32Max);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

