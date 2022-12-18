/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_voip.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/11/24
  Description   :
  History       :
  1.Date        : 2010/11/24
    Author      : f00172091
    Modification: Created file

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "mpi_voip_hme.h"
//#include "hi_unf_voip.h"
#include "hi_error_voip.h"
//#include "Hi_type.h"
#include "msg_trace.h"
extern VOIP_HME_TRACE_S g_stHmeTrace;
#include "mpi_aud_adp.h"


HI_S32 HI_UNF_VOIP_Init(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = HI_MPI_VOIP_HME_Init();
    
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159 */
    if(HI_SUCCESS == s32Ret)
    {
        /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
        VOIP_HME_InitCapMsg();
        /* END:   Added by zhangcheng, 2011/2/12 */
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    return s32Ret;
}

HI_S32 HI_UNF_VOIP_DeInit(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = HI_MPI_VOIP_HME_DeInit();
    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    VOIP_HME_DeInitCapMsg();
    /* END:   Added by zhangcheng, 2011/2/12 */

    return s32Ret;
}

HI_S32 HI_UNF_VOIP_GetChDefaultAttr(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstDefChAttr)
{
    HI_S32 s32Ret;
	
    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    GET_DEF_ATTR_S stGetDefAttrCmd;
    GET_DEF_ATTR_RSP_S stGetDefAttrCmdRsp;

    
    stGetDefAttrCmd.uiCmd = USER_GET_DEF_ATTR;
    stGetDefAttrCmd.enWorkMode = enWorkMode;

    /* BEGIN: modified by hefeng, 2011/2/28   PN:DTS2011022304159 */
    if(HI_NULL != g_stHmeTrace.pTraceSendMsg)
    {
        g_stHmeTrace.pTraceSendMsg(HI_INVALID_HANDLE, (HI_U8 *)(&stGetDefAttrCmd), sizeof(GET_DEF_ATTR_S));
    }
    /* END:   modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/2/12 */

    s32Ret = HI_MPI_VOIP_HME_GetChDefaultAttr(enWorkMode,pstDefChAttr);

    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    stGetDefAttrCmdRsp.uiCmd = USER_GET_DEF_ATTR_RSP;
    stGetDefAttrCmdRsp.iRet = s32Ret;
    if(HI_NULL != pstDefChAttr)
    {
        stGetDefAttrCmdRsp.stDefChAttr = *pstDefChAttr;
    }
    
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL !=  g_stHmeTrace.pTraceRecvMsg)
    {
        g_stHmeTrace.pTraceRecvMsg(HI_INVALID_HANDLE, (HI_U8 *)(&stGetDefAttrCmdRsp), sizeof(GET_DEF_ATTR_RSP_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/2/12 */
    return s32Ret;
    
}

/* BEGIN: Modified for PN:FZH_REVIEW_101201_3 by f00172091, 2010/12/1 */
HI_S32 HI_UNF_VOIP_CreateChannel(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr, HI_HANDLE *phVoip)
{  
    HI_S32 s32Ret;
	
    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    CREARE_CHN_CMD_S  stCreateChCmd;
    CREARE_CHN_CMD_RSP_S stCreateChCmdRsp;

    if(!pstChAttr)
    {
        HI_ERR_HME("pointer pChAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    if(!phVoip)
    {
        HI_ERR_HME("pointer phVoipHme is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    stCreateChCmd.uiCmd = USER_CREATE_CHN;
    stCreateChCmd.enWorkMode = enWorkMode;
    stCreateChCmd.stChAttr = *pstChAttr;
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceSendMsg)
    {
        g_stHmeTrace.pTraceSendMsg(HI_INVALID_HANDLE, (HI_U8 *)(&stCreateChCmd), sizeof(CREARE_CHN_CMD_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/2/12 */


    s32Ret = HI_MPI_VOIP_HME_CreateChannel(enWorkMode,pstChAttr,phVoip);

    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    stCreateChCmdRsp.uiCmd = USER_CREATE_CHN_RSP;
    stCreateChCmdRsp.iRet = s32Ret;
    stCreateChCmdRsp.hVoipHme = *phVoip;
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceRecvMsg)
    {
        g_stHmeTrace.pTraceRecvMsg(stCreateChCmdRsp.hVoipHme, (HI_U8 *)(&stCreateChCmdRsp), sizeof(CREARE_CHN_CMD_RSP_S));    
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/2/12 */

    return s32Ret;
}
/* END:   Modified for PN:FZH_REVIEW_101201_3 by f00172091, 2010/12/1 */

HI_S32 HI_UNF_VOIP_DestroyChannel(HI_HANDLE hVoip)
{
    HI_S32 s32Ret;
   
    /* BEGIN: Added by hefeng, 2011/2/12   PN:msg trace code*/
    DESTROY_CHN_CMD_S stDestroyChnCmd;
    DESTROY_CHN_CMD_RSP_S stDestroyChnCmdRsp;
    
    stDestroyChnCmd.uiCmd = USER_DESTROY_CHN;
    stDestroyChnCmd.hVoipHme = hVoip;

    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceSendMsg)
    {
        g_stHmeTrace.pTraceSendMsg(hVoip, (HI_U8 *)(&stDestroyChnCmd), sizeof(DESTROY_CHN_CMD_S));    
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by hefeng, 2011/2/12 */
    s32Ret = HI_MPI_VOIP_HME_DestroyChannel(hVoip);
    /* BEGIN: Added by hefeng, 2011/2/12   PN:msg trace code*/
    stDestroyChnCmdRsp.uiCmd = USER_DESTROY_CHN_RSP;
    stDestroyChnCmdRsp.iRet = s32Ret;
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceRecvMsg)
    {
        g_stHmeTrace.pTraceRecvMsg(hVoip, (HI_U8 *)(&stDestroyChnCmdRsp), sizeof(DESTROY_CHN_CMD_RSP_S));
    } 
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by hefeng, 2011/2/12 */

    return s32Ret;
}

HI_S32 HI_UNF_VOIP_GetChAttr(HI_HANDLE hVoip, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
	
    /* BEGIN: Modified by zhangcheng, 2011/2/12   PN:msg trace code*/
    GET_CHN_ATTR_CMD_S stGetChAttrCmd;
    GET_CHN_ATTR_CMD_RSP_S stGetChAttrCmdRsp; 
    stGetChAttrCmd.uiCmd = USER_GET_CHN_ATTR;
    stGetChAttrCmd.hVoipHme = hVoip;
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceSendMsg)	
    {
        g_stHmeTrace.pTraceSendMsg(hVoip, (HI_U8 *)(&stGetChAttrCmd), sizeof(GET_CHN_ATTR_CMD_S));    
    } 
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Modified by zhangcheng, 2011/2/12 */

    s32Ret = HI_MPI_VOIP_HME_GetChAttr(hVoip, pstChAttr);

     /* BEGIN: Added by zhangcheng, 2011/1/28   PN:msg trace code*/
    stGetChAttrCmdRsp.uiCmd = USER_GET_CHN_ATTR_RSP;
    stGetChAttrCmdRsp.iRet = s32Ret;
    if(HI_NULL != pstChAttr)
    {
        stGetChAttrCmdRsp.stChAttr = *pstChAttr;
    }
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceRecvMsg)
    {
        g_stHmeTrace.pTraceRecvMsg(hVoip, (HI_U8 *)(&stGetChAttrCmdRsp), sizeof(GET_CHN_ATTR_CMD_RSP_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/1/28 */

    return s32Ret;
}

HI_S32 HI_UNF_VOIP_ModifyChnAttr(HI_HANDLE hVoip, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr)
{
    HI_S32 s32Ret;
    /* BEGIN: Modified by zhangcheng, 2011/2/12   PN:msg trace code*/
    MODIFY_CHN_ATTR_CMD_S     stModifyChAttrCmd;
    MODIFY_CHN_ATTR_CMD_RSP_S      stModifyChnAttrCmdRsp;

    if(!pstChAttr)
    {
        HI_ERR_HME("pointer pChAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }
	
    stModifyChAttrCmd.uiCmd = USER_MODIFY_CHN_ATTR;
    stModifyChAttrCmd.hVoipHme = hVoip;
    stModifyChAttrCmd.stChAttr = *pstChAttr;
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceSendMsg)
    {
        g_stHmeTrace.pTraceSendMsg(hVoip, (HI_U8 *)(& stModifyChAttrCmd), sizeof(MODIFY_CHN_ATTR_CMD_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Modified by zhangcheng, 2011/2/12 */

    s32Ret = HI_MPI_VOIP_HME_ModifyChnAttr(hVoip, pstChAttr);

    /* BEGIN: Added by zhangcheng, 2011/1/28   PN:msg trace code*/
    /* BEGIN: Modified by zhangcheng, 2011/2/12   PN: wj_code_0211_06*/
    stModifyChnAttrCmdRsp.uiCmd = USER_MODIFY_CHN_RSP;
    /* END:   Modified by zhangcheng, 2011/2/12 */
    stModifyChnAttrCmdRsp.iRet = s32Ret;
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceRecvMsg)
    {
        g_stHmeTrace.pTraceRecvMsg(hVoip, (HI_U8 *)(&stModifyChnAttrCmdRsp), sizeof(MODIFY_CHN_ATTR_CMD_RSP_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/1/28 */
    return s32Ret;
}

#if 0
HI_S32 HI_UNF_VOIP_GetChSubAttr(HI_HANDLE hVoip, UNF_VOIP_ATTR_ID_E enAttrID, HI_VOID *pChSubAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_VOIP_CHN_ATTR_S	stChAttr;

    if(!pChSubAttr)
    {
        HI_ERR_HME("pointer pChSubAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }
       
    s32Ret = HI_MPI_VOIP_HME_GetChAttr(hVoip, &stChAttr);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    switch(enAttrID)
    {
            case HI_UNF_VOIP_ATTR_ID_DSP:
                memcpy((HI_U8 *)pChSubAttr, (HI_U8 *)&stChAttr.stDspPara, sizeof(HI_UNF_VOIP_DSP_CONFIG_PARA_S));
                break;

            case HI_UNF_VOIP_ATTR_ID_EC:
                memcpy((HI_U8 *)pChSubAttr, (HI_U8 *)&stChAttr.stEcPara, sizeof(HI_UNF_VOICE_CONFIG_PARA_S));
                break;
                
            case HI_UNF_VOIP_ATTR_ID_JB:
                memcpy((HI_U8 *)pChSubAttr, (HI_U8 *)&stChAttr.stJBPara, sizeof(HI_UNF_JB_CONFIG_PARA_S));
                break;

            case HI_UNF_VOIP_ATTR_ID_VQE:
                memcpy((HI_U8 *)pChSubAttr, (HI_U8 *)&stChAttr.stVQEPara, sizeof(HI_UNF_VQE_CONFIG_PARA_S));
                break;
                
            case HI_UNF_VOIP_ATTR_ID_NET:
                memcpy((HI_U8 *)pChSubAttr, (HI_U8 *)&stChAttr.stNetPara, sizeof(HI_UNF_NET_CONFIG_PARA_S));
                break;

            case HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV:
                memcpy((HI_U8 *)pChSubAttr, (HI_U8 *)&stChAttr.stAudevPara, sizeof(HI_UNF_AUDDEV_PARA_S));
                break;

            default:
                HI_ERR_HME("para enAttrID is invalid.\n");
                s32Ret = HI_ERR_VOIP_HME_INVALID_PARA;
                break;
        }
    
    return s32Ret;
}

HI_S32 HI_UNF_VOIP_ModifyChnSubAttr(HI_HANDLE hVoip, UNF_VOIP_ATTR_ID_E enAttrID, HI_VOID *pChSubAttr)
{
    HI_S32 s32Ret;
    HI_UNF_VOIP_CHN_ATTR_S	stChAttr;

    if(!pChSubAttr)
    {
        HI_ERR_HME("pointer pChSubAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }
       
    s32Ret = HI_MPI_VOIP_HME_GetChAttr(hVoip, &stChAttr);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    switch(enAttrID)
    {
            case HI_UNF_VOIP_ATTR_ID_DSP:
                memcpy((HI_U8 *)&stChAttr.stDspPara, (HI_U8 *)pChSubAttr, sizeof(HI_UNF_VOIP_DSP_CONFIG_PARA_S));
                break;

            case HI_UNF_VOIP_ATTR_ID_EC:
                memcpy((HI_U8 *)&stChAttr.stEcPara, (HI_U8 *)pChSubAttr, sizeof(HI_UNF_VOICE_CONFIG_PARA_S));
                break;
                
            case HI_UNF_VOIP_ATTR_ID_JB:
                memcpy((HI_U8 *)&stChAttr.stJBPara, (HI_U8 *)pChSubAttr, sizeof(HI_UNF_JB_CONFIG_PARA_S));
                break;

            case HI_UNF_VOIP_ATTR_ID_VQE:
                memcpy((HI_U8 *)&stChAttr.stVQEPara, (HI_U8 *)pChSubAttr, sizeof(HI_UNF_VQE_CONFIG_PARA_S));
                break;
                
            case HI_UNF_VOIP_ATTR_ID_NET:
                memcpy((HI_U8 *)&stChAttr.stNetPara, (HI_U8 *)pChSubAttr, sizeof(HI_UNF_NET_CONFIG_PARA_S));
                break;

            case HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV:
                memcpy((HI_U8 *)&stChAttr.stAudevPara, (HI_U8 *)pChSubAttr, sizeof(HI_UNF_AUDDEV_PARA_S));
                break;

            default:
                HI_ERR_HME("para enAttrID is invalid.\n");
                return HI_ERR_VOIP_HME_INVALID_PARA;
        }

    s32Ret = HI_MPI_VOIP_HME_ModifyChnAttr(hVoip, &stChAttr);

    return s32Ret;
}
#endif

/* BEGIN: Deleted by wangjuan, 2011/1/5   PN:Do not support this function*/
#if 0
HI_S32 HI_UNF_VOIP_PlayTone(HI_HANDLE hVoip, HI_UNF_VOIP_PLAY_TONE_ATTR_S *pstToneAttr)
{
    HI_S32 s32Ret;

    s32Ret = HI_MPI_VOIP_HME_PlayTone(hVoip, pstToneAttr);

    return s32Ret;
}

HI_S32 HI_UNF_VOIP_StopTone(HI_HANDLE hVoip)
{
    HI_S32 s32Ret;

    s32Ret = HI_MPI_VOIP_HME_StopTone(hVoip);

    return s32Ret;
}
#endif

HI_S32 HI_UNF_VOIP_PlayAnnouncement(HI_HANDLE hVoip, HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S *pstAnnAttr)
{
    HI_S32 s32Ret;
	
    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    PLAY_ANNOUNCEMENT_CMD_S       stPlayAnnouncementCmd;
    PLAY_ANNOUNCEMENT_CMD_RSP_S        stPlayAnnouncementCmdRsp;

    stPlayAnnouncementCmd.uiCmd = USER_PLAY_ANNOUNCEMENT;
    stPlayAnnouncementCmd.hVoipHme = hVoip;
    if(HI_NULL != pstAnnAttr)
    {
        stPlayAnnouncementCmd.stAnnAttr = *pstAnnAttr;
    }
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceSendMsg)
    {
        g_stHmeTrace.pTraceSendMsg(hVoip, (HI_U8 *)(&stPlayAnnouncementCmd), sizeof(PLAY_ANNOUNCEMENT_CMD_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/2/12 */
    
    s32Ret = HI_MPI_VOIP_HME_PlayAnnouncement(hVoip, pstAnnAttr);

    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    stPlayAnnouncementCmdRsp.uiCmd = USER_PLAY_ANNOUNCEMENT_RSP;
    stPlayAnnouncementCmdRsp.iRet = s32Ret;
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceRecvMsg)
    {
        g_stHmeTrace.pTraceRecvMsg(hVoip, (HI_U8 *)(&stPlayAnnouncementCmdRsp), sizeof(PLAY_ANNOUNCEMENT_CMD_RSP_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/2/12 */
    return s32Ret;
}

HI_S32 HI_UNF_VOIP_StopAnnouncement(HI_HANDLE hVoip, HI_U32 u32Direction)
{   
    HI_S32 s32Ret;

    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    STOP_ANNOUNCEMENT_CMD_S stStopAnnounceMent;
    STOP_ANNOUNCEMENT_CMD_RSP_S stStopPlayAnnounceMentRsp;
    stStopAnnounceMent.uiCmd = USER_STOP_ANNOUNCEMENT;
    stStopAnnounceMent.u32Direction = u32Direction;
    stStopAnnounceMent.hVoipHme = hVoip;

    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceSendMsg)
    {
        g_stHmeTrace.pTraceSendMsg(hVoip, (HI_U8 *)(&stStopAnnounceMent), sizeof(STOP_ANNOUNCEMENT_CMD_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/2/12 */
    
    s32Ret = HI_MPI_VOIP_HME_StopAnnouncement(hVoip,u32Direction);
    
    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    stStopPlayAnnounceMentRsp.iRet = s32Ret;
    stStopPlayAnnounceMentRsp.uiCmd = USER_STOP_ANNOUNCEMENT_RSP;
	
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceRecvMsg)
    {
        g_stHmeTrace.pTraceRecvMsg(hVoip, (HI_U8 *)(&stStopPlayAnnounceMentRsp), sizeof(STOP_ANNOUNCEMENT_CMD_RSP_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/2/12 */

    return s32Ret;
}

HI_S32 HI_UNF_VOIP_RegisterEvent(HI_HANDLE hVoip, HI_UNF_VOIP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args)
{
    HI_S32 s32Ret;
	
    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    REG_EVENT_S stRegEventCmd;
    REG_EVENT_RSP_S stRegEventCmdRsp;
    stRegEventCmd.uiCmd = USER_REG_EVENT;
    stRegEventCmd.hVoipHme = hVoip;
    stRegEventCmd.pfnEventCB = pfnEventCB;
    stRegEventCmd.args = u32Args;

    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceSendMsg)
    {
        g_stHmeTrace.pTraceSendMsg(hVoip, (HI_U8 *)(&stRegEventCmd), sizeof(REG_EVENT_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/2/12 */

    s32Ret = HI_MPI_VOIP_HME_RegisterEvent(hVoip, pfnEventCB, u32Args);

    /* BEGIN: Added by zhangcheng, 2011/2/12   PN:msg trace code*/
    stRegEventCmdRsp.uiCmd = USER_REG_EVENT_RSP;
    stRegEventCmdRsp.iRet = s32Ret;
	
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceRecvMsg)
    {
        g_stHmeTrace.pTraceRecvMsg(hVoip, (HI_U8 *)(&stRegEventCmdRsp), sizeof(REG_EVENT_RSP_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by zhangcheng, 2011/2/12 */

    return s32Ret;
}

HI_S32 HI_UNF_VOIP_GetRtcpStaticInfo(HI_HANDLE hVoip, HI_UNF_VOIP_RTCP_STATIC_INFO_S * pstRtcpInfo)
{
    HI_S32 s32Ret;

    /* BEGIN: Added by hefeng, 2011/2/12   PN:msg trace code*/
    GET_RTCP_STATIC_INFO_S stGetRtcpStatInfoCmd;
    GET_RTCP_STATIC_INFO_RSP_S stGetRtcpStatInfoCmdRsp;

    /* BEGIN: Modified by hefeng, 2011/2/12   PN:wj_code_0211_03*/
    stGetRtcpStatInfoCmd.uiCmd = USER_GET_RTCP_STATIC_INFO;
    /* END:   Modified by hefeng, 2011/2/12 */
    stGetRtcpStatInfoCmd.hVoipHme = hVoip;

    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceSendMsg)
    {
        g_stHmeTrace.pTraceSendMsg(hVoip, (HI_U8 *)(&stGetRtcpStatInfoCmd), sizeof(GET_RTCP_STATIC_INFO_S));
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by hefeng, 2011/2/12 */ 
    s32Ret = HI_MPI_VOIP_HME_GetRtcpStaticInfo(hVoip, pstRtcpInfo);
    /* BEGIN: Added by hefeng, 2011/2/12   PN:msg trace code*/
    /* BEGIN: Modified by hefeng, 2011/2/12   PN:wj_code_0211_05*/
    stGetRtcpStatInfoCmdRsp.uiCmd = USER_GET_RTCP_STATIC_INFO_RSP; 
    /* END:   Modified by hefeng, 2011/2/12 */
    stGetRtcpStatInfoCmdRsp.iRet = s32Ret;
    /* BEGIN: Added by caizhigang, 2011/2/28   PN:DTS2011022801935 */
    if(HI_NULL != pstRtcpInfo)
    /* END:   Added by caizhigang, 2011/2/28 */
    {
        stGetRtcpStatInfoCmdRsp.stRtcpInfo = *pstRtcpInfo;        
    }    
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceRecvMsg)
    {
        g_stHmeTrace.pTraceRecvMsg(hVoip, (HI_U8 *)(&stGetRtcpStatInfoCmdRsp), sizeof(GET_RTCP_STATIC_INFO_RSP_S));    
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by hefeng, 2011/2/12 */
        
    return s32Ret;
}

HI_S32 HI_UNF_VOIP_CfgRtcp(HI_HANDLE hVoip, HI_UNF_VOIP_CFG_RTCP_ATTR_S * pstRtcpAttr)
{
    HI_S32 s32Ret;

    /* BEGIN: Added by hefeng, 2011/2/12   PN:msg trace code*/
    CFG_RTCP_CMD_S stCfgRtcpCmd;
    CFG_RTCP_CMD_RSP_S stCfgRtcpCmdRsp;

    stCfgRtcpCmd.uiCmd = USER_CFG_RTCP;
    stCfgRtcpCmd.hVoipHme = hVoip;
    if(HI_NULL != pstRtcpAttr)
    {
        stCfgRtcpCmd.stRtcpAttr = *pstRtcpAttr;
    }
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceSendMsg)
    {
        g_stHmeTrace.pTraceSendMsg(hVoip, (HI_U8*)(&stCfgRtcpCmd), sizeof(CFG_RTCP_CMD_S));    
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by hefeng, 2011/2/12 */
    s32Ret = HI_MPI_VOIP_HME_CfgRtcp(hVoip, pstRtcpAttr);
    /* BEGIN: Added by hefeng, 2011/2/12   PN:msg trace code*/
    /* BEGIN: Modified by hefeng, 2011/2/12   PN:wj_code_0211_04*/
    stCfgRtcpCmdRsp.uiCmd = USER_CFG_RTCP_RSP;
    /* END:   Modified by hefeng, 2011/2/12 */
    stCfgRtcpCmdRsp.iRet = s32Ret;
    
    /* BEGIN: Modified by hefeng, 2011/2/28   PN:DTS2011022304159*/
    if(HI_NULL != g_stHmeTrace.pTraceRecvMsg)
    {
        g_stHmeTrace.pTraceRecvMsg(hVoip, (HI_U8*)(&stCfgRtcpCmdRsp), sizeof(CFG_RTCP_CMD_RSP_S)); 
    }
    /* END:   Modified by hefeng, 2011/2/28 */
    /* END:   Added by hefeng, 2011/2/12 */
        
    return s32Ret;
}

/******************************* Voip Audio Adapter ******************************/

HI_S32 HI_UNF_AUDADP_Init(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    
    s32Ret = HI_MPI_AUDADP_Init();
        
    return s32Ret;
}

HI_S32 HI_UNF_AUDADP_DeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_AUDADP_DeInit();
    
    return s32Ret;
}

HI_S32 HI_UNF_AUDADP_AudDev_Open(HI_UNF_AUDADP_AUDDEV_PARA_S *pstAudDev,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    HI_S32 s32Ret = HI_SUCCESS;
    
    s32Ret = HI_MPI_AUDADP_AudDev_Open(pstAudDev, stAudDevOptFlag);
    
    return s32Ret;
}

HI_S32 HI_UNF_AUDADP_AudDev_Close(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_AUDADP_AudDev_Close(s32AudioDevId, stAudDevOptFlag);
    
    return s32Ret;
}

HI_S32 HI_UNF_AUDADP_AudDev_Start(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_AUDADP_AudDev_Start(s32AudioDevId, stAudDevOptFlag);
    
    return s32Ret;
}

HI_S32 HI_UNF_AUDADP_AudDev_Stop(HI_S32 s32AudioDevId,
                    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_AUDADP_AudDev_Stop(s32AudioDevId, stAudDevOptFlag);
    
    return s32Ret;
}

HI_S32 HI_UNF_AUDADP_AudDev_GetStatus(HI_S32 s32AudioDevId, HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType, HI_UNF_AUDADP_STATUS_E *ps32Status)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_AUDADP_AudDev_GetStatus(s32AudioDevId, enAudioDevType, (HI_S32 *)ps32Status);
    
    return s32Ret;
}

HI_S32 HI_UNF_AUDADP_RegisterEvent(HI_UNF_AUDADP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args)
{
    HI_S32 s32Ret = HI_SUCCESS;
    
    s32Ret = HI_MPI_AUDADP_RegisterEvent(pfnEventCB, u32Args);
    
    return s32Ret;
}

HI_S32 HI_ALSA_GetAudioDevList(HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType,HI_ALSA_CARD_INFO_S * pstCardList,HI_U32 u32Max,HI_U32 *pu32Count)
{
    HI_S32 s32Ret = HI_SUCCESS;
    
    s32Ret = HI_MPI_ALSA_GetAudioDevList(enAudioDevType, pstCardList, u32Max, pu32Count);
    
    return s32Ret;

}

HI_S32 HI_ALSA_GetAudioDevRateRange(HI_ALSA_CARD_INFO_S * pstCardInfo, HI_U32 *pu32Min, HI_U32 *pu32Max)
{
    HI_S32 s32Ret = HI_SUCCESS;
    
    s32Ret = HI_MPI_ALSA_GetAudioDevRateRange(pstCardInfo, pu32Min, pu32Max);
    
    return s32Ret;
}
