/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : voip_hme.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/11/23
  Description   :
  History       :
  1.Date        : 2010/11/23
    Author      : f00172091
    Modification: Created file

*******************************************************************************/


#ifndef __VOIP_HME_H__
#define __VOIP_HME_H__

#include "priv_hme.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

HI_S32  HI_MPI_VOIP_HME_Init(HI_VOID);
HI_S32 HI_MPI_VOIP_HME_DeInit(HI_VOID);
HI_S32 HI_MPI_VOIP_HME_GetChDefaultAttr(HI_UNF_VOIP_WORKMODE_E enWorkMode,HI_UNF_VOIP_CHN_ATTR_S *pstDefChAttr);
/* BEGIN: Modified for PN:FZH_REVIEW_101201_3 by f00172091, 2010/12/1 */
HI_S32 HI_MPI_VOIP_HME_CreateChannel(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr, HI_HANDLE *phVoipHme);
/* END:   Modified for PN:FZH_REVIEW_101201_3 by f00172091, 2010/12/1 */
HI_S32 HI_MPI_VOIP_HME_DestroyChannel(HI_HANDLE hVoipHme);
HI_S32 HI_MPI_VOIP_HME_GetChAttr(HI_HANDLE hVoipHme, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr);
HI_S32 HI_MPI_VOIP_HME_ModifyChnAttr(HI_HANDLE hVoipHme, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr);
HI_S32 HI_MPI_VOIP_HME_PlayTone(HI_HANDLE hVoipHme, HI_UNF_VOIP_PLAY_TONE_ATTR_S *pstToneAttr);
HI_S32 HI_MPI_VOIP_HME_StopTone(HI_HANDLE hVoipHme);
HI_S32 HI_MPI_VOIP_HME_PlayAnnouncement(HI_HANDLE hVoipHme, HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S *pstAnnAttr);
HI_S32 HI_MPI_VOIP_HME_StopAnnouncement(HI_HANDLE hVoipHme,HI_U32 u32Direction);
HI_S32 HI_MPI_VOIP_HME_RegisterEvent(HI_HANDLE hVoipHme, HI_UNF_VOIP_EVENT_CB_FN pfnEventCB, HI_U32 args);
HI_S32 HI_MPI_VOIP_HME_GetRtcpStaticInfo(HI_HANDLE hVoipHme, HI_UNF_VOIP_RTCP_STATIC_INFO_S * pstRtcpInfo);
HI_S32 HI_MPI_VOIP_HME_CfgRtcp(HI_HANDLE hVoipHme, HI_UNF_VOIP_CFG_RTCP_ATTR_S * pstRtcpAttr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

