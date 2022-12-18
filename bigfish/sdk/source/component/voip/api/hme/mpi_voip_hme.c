/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : HMEip_hme.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/11/23
  Description   :
  History       :
  1.Date        : 2010/11/23
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
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <linux/types.h>

#include "hi_drv_struct.h"
#include "mpi_voip_hme.h"
#include "hi_error_voip.h"
#include "msg_trace.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

static HI_S32           g_VoipHmeDevFd = -1;
static const HI_CHAR    g_VoipHmeDevName[] = "/dev/"UMAP_DEVNAME_HME;

/* BEGIN: Modified by hefeng, 2011/6/3   PN:memory statistics voip2.0*/
static pthread_t   tThreadVoipHmeEvent;
/* END:   Modified by hefeng, 2011/6/3 */

/* BEGIN: Added by zhangcheng, 2011/2/17   PN:msg trace set*/
/* BEGIN: Modified by hefeng, 2011/6/3   PN:memory statistics voip2.0*/
static pthread_t   tThreadVoipHmeUserMsgEvent;
/* END:   Modified by hefeng, 2011/6/3 */
/* END:   Added by zhangcheng, 2011/2/17 */

static VOIP_HME_EVENT_CB_S  stEventCb[HME_MAX_CHANNEL_COUNT];

/* BEGIN: Added by baiyingting, 2010/12/31   PN:DTS2011010403714*/
static HI_U32   g_u32VoipEventRunFlag;
/* END:   Added by baiyingting, 2010/12/31 */

/* BEGIN: Added by zhangcheng, 2011/2/17   PN:msg trace set*/
static HI_U32   g_u32VoipUserMsgEventRunFlag;
/* END:   Added by zhangcheng, 2011/2/17 */

#define CHECK_HME_INIT()\
do{\
	if (g_VoipHmeDevFd < 0)\
	{\
		HI_ERR_HME("HME is not init.\n");\
		return HI_ERR_VOIP_HME_NO_INIT;\
	}\
}while(0)

/* BEGIN: Modified for PN:FZH_REVIEW_101201_6 by f00172091, 2010/12/6 */
static pthread_mutex_t  g_VoipEventMutex = PTHREAD_MUTEX_INITIALIZER;
#define HI_VOIP_EVENT_LOCK()  	 (void)pthread_mutex_lock(&g_VoipEventMutex);
#define HI_VOIP_EVENT_UNLOCK()   (void)pthread_mutex_unlock(&g_VoipEventMutex);
/* END:   Modified for PN:FZH_REVIEW_101201_6 by f00172091, 2010/12/6 */

/* BEGIN: Modified by hefeng, 2011/6/3   PN:memory statistics voip2.0*/
HI_VOID* VOIP_HME_EventProc( HI_VOID *arg);
HI_VOID* VOIP_HME_UserMsgEventProc(HI_VOID *arg);
/* END:   Modified by hefeng, 2011/6/3 */

/* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
HI_S32  VOIP_HME_ErrCodeConvert(HI_S32 s32ErrCodeK,HI_S32 *s32ErrCodeUnf)
{
    const HI_S32 s32ErrCodeCenvertTable[]={
        HI_SUCCESS,
        HI_ERR_VOIP_HME_UNKNOWN,
        HI_ERR_VOIP_HME_INVALID_PARA,
        HI_ERR_VOIP_HME_INVALCHANNELID,
        HI_ERR_VOIP_HME_INVALNETPORT,
        HI_ERR_VOIP_HME_NO_INIT,
        HI_ERR_VOIP_HME_NOT_IMPLEMENTED,
        HI_ERR_VOIP_HME_NOT_SUPPORTED,
        HI_ERR_VOIP_HME_LOG_INIT,
        HI_ERR_VOIP_HME_STARTUP_FAIL,
        HI_ERR_VOIP_HME_DELETE_FAIL,
    };

    if(s32ErrCodeK < 0)
    {
        return HI_ERR_VOIP_HME_UNKNOWN;
    }
    
    s32ErrCodeK &= 0xff;
    if((HI_U32)s32ErrCodeK < (sizeof(s32ErrCodeCenvertTable)/sizeof(HI_S32)))
    {
        *s32ErrCodeUnf = s32ErrCodeCenvertTable[s32ErrCodeK];
    }
    else
    {
        *s32ErrCodeUnf = HI_ERR_VOIP_HME_UNKNOWN;
    }
    return HI_SUCCESS;
}
/* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */

HI_S32  VOIP_HME_GetEventList(HI_U32 *pEventNum, VOIP_HME_EVENT_INFO_S *pstEvent)
{
    HI_S32         Ret;
    VOIP_HME_IOCTL_GET_EVENT_S	stIoctlGetEvent;

    if (!pEventNum)
    {
        HI_ERR_HME("pointer pEventNum is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR; 
    }
	
    if (!pstEvent)
    {
        HI_ERR_HME("pointer pstEvent is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR; 
    }

    CHECK_HME_INIT();

    /* BEGIN: Modified by baiyingting, 2010/12/13   PN:DTS2010121100245*/
    stIoctlGetEvent.pstEventList = pstEvent;
    
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_GET_EVENT, &stIoctlGetEvent);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        *pEventNum = 0;
        /* BEGIN: Modified for PN:FZH_REVIEW_101201_4 by f00172091, 2010/12/1 */
        //HI_ERR_HME("get event list error %d\n",Ret);
        /* END:   Modified for PN:FZH_REVIEW_101201_4 by f00172091, 2010/12/1 */
        return Ret;
    }
    
    if (stIoctlGetEvent.uiEventNum > HME_MAX_EVENT_COUNT)
    {
        stIoctlGetEvent.uiEventNum = 0;
    }

    *pEventNum = stIoctlGetEvent.uiEventNum;
    /* END:   Modified by baiyingting, 2010/12/13 */
    
    return HI_SUCCESS;
}
/* BEGIN: Added by zhangcheng, 2011/2/17   PN:msg trace set*/
HI_S32  VOIP_HME_GetUserMsgEventList(HI_U32 *pEventNum, VOIP_HME_USER_MSG_EVENT_INFO_S *pstEvent)
{
    HI_S32         Ret;
    VOIP_HME_IOCTL_GET_USER_MSG_EVENT_S  stIoctlGetUserMsgEvent;

    if (!pEventNum)
    {
        HI_ERR_HME("pointer pEventNum is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR; 
    }
    
    if (!pstEvent)
    {
        HI_ERR_HME("pointer pstEvent is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR; 
    }

    CHECK_HME_INIT();

    stIoctlGetUserMsgEvent.pstUserMsgEventList = pstEvent;
    
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_GET_USER_MSG_EVENT, &stIoctlGetUserMsgEvent);
    if (Ret != HI_SUCCESS)
    {
        *pEventNum = 0;
        /* BEGIN: Modified for PN:FZH_REVIEW_101201_4 by f00172091, 2010/12/1 */
   //     HI_ERR_HME("get user msg event list error %d\n",Ret);
        /* END:   Modified for PN:FZH_REVIEW_101201_4 by f00172091, 2010/12/1 */
        return Ret;
    }
    
    if (stIoctlGetUserMsgEvent.uiUserMsgEventNum > HME_MAX_EVENT_COUNT)
    {
        stIoctlGetUserMsgEvent.uiUserMsgEventNum = 0;
    }

    *pEventNum = stIoctlGetUserMsgEvent.uiUserMsgEventNum;
    
    return HI_SUCCESS;
}
/* END:   Added by zhangcheng, 2011/2/17 */

HI_S32  VOIP_HME_EventInit(HI_VOID)
{
    HI_S32      Ret;
    HI_U32      i;

    HI_INFO_HME("Event initial start.\n");
    HI_VOIP_EVENT_LOCK();
    /*Initial the structure of event call back functions*/
    for(i=0;i<HME_MAX_CHANNEL_COUNT;i++)
    {
        stEventCb[i].hVoipHme = HI_INVALID_HANDLE;
        stEventCb[i].pfnEventCB = NULL;
        stEventCb[i].args = 0;
    }
    HI_VOIP_EVENT_UNLOCK();
    
    /*Create event process thread*/
    /* BEGIN: Deleted by hefeng, 2011/6/3   PN:memory statistics voip2.0*/
#if 0 
    if (HI_NULL != tThreadVoipHmeEvent)
    {
        HI_ERR_HME("tThreadVoipHmeEvent isn't NULL in VOIP_HME_EventInit\n");
        return  HI_ERR_VOIP_HME_INVALID_PARA;  
    }
#endif
    /* END:   Modified by hefeng, 2011/6/3 */

    /* BEGIN: Added by baiyingting, 2011/1/4   PN:DTS2011010403714*/
    g_u32VoipEventRunFlag = true;
    /* END:   Added by baiyingting, 2011/1/4 */
    Ret = pthread_create(&tThreadVoipHmeEvent, HI_NULL, VOIP_HME_EventProc, HI_NULL);
    if(Ret != HI_SUCCESS)
    {
        HI_ERR_HME("create pthread err.\n");        
        return HI_ERR_VOIP_HME_NO_INIT;
    }
    
    HI_INFO_HME("Event initial success.\n");
    return HI_SUCCESS;
}

/* BEGIN: Added by zhangcheng, 2011/2/17   PN:msg trace set*/
HI_S32  VOIP_HME_UserMsgEventInit(HI_VOID)
{
    HI_S32      Ret;
    
    HI_INFO_HME("UserMsgEvent initial start.\n");

    /* BEGIN: Deleted by hefeng, 2011/6/3   PN:memory statistics voip2.0*/
#if 0
    /*create event process thread*/
    if (NULL != tThreadVoipHmeUserMsgEvent)
    {
        HI_ERR_HME("tThreadVoipHmeUserMsgEvent isn't NULL in VOIP_HME_EventInit\n");
        return  HI_ERR_VOIP_HME_INVALID_PARA;  
    }
#endif
    /* END: Deleted by hefeng, 2011/6/3 */

    g_u32VoipUserMsgEventRunFlag = true;

    Ret = pthread_create(&tThreadVoipHmeUserMsgEvent, HI_NULL, VOIP_HME_UserMsgEventProc, HI_NULL);
    if(Ret != HI_SUCCESS)
    {
        HI_ERR_HME("create pthread err in VOIP_HME_UserMsgEventInit.\n");
        
        return HI_ERR_VOIP_HME_NO_INIT;
    }
    
    HI_INFO_HME("Event initial success in VOIP_HME_UserMsgEventInit.\n");
    return HI_SUCCESS;
}
/* END:   Added by zhangcheng, 2011/2/17 */
HI_S32  VOIP_HME_EventDeInit(HI_VOID)
{
    HI_S32      Ret = HI_SUCCESS;
    HI_U32  i;

    HI_INFO_HME("event deinitial start.\n");

    /* BEGIN: Modified by baiyingting, 2011/1/4   PN:DTS2011010403714*/
    /* BEGIN: Modified by baiyingting, 2010/12/22   PN:DTS2010122300084*/
    /* BEGIN: Modified by baiyingting, 2010/12/13   PN:DTS2010121100245*/
    g_u32VoipEventRunFlag = false;  
    /* BEGIN: Modified for PN:DTS2011021500145 by f00172091, 2011/3/8 */
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_EVENT_WAKE_UP);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */

    /* BEGIN: Modified by hefeng, 2011/6/3   PN:memory statistics voip2.0*/
    //if (NULL != tThreadVoipHmeEvent)
    {      
        //pthread_cancel(tThreadVoipHmeEvent);

        pthread_join(tThreadVoipHmeEvent, NULL);
    }
    /* END:  Modified for PN:DTS2011021500145 by f00172091, 2011/3/8 */
    //tThreadVoipHmeEvent = NULL;
    /* END:   Modified by hefeng, 2011/6/3 */
    /* END:   Modified by baiyingting, 2010/12/13 */
    /* END:   Modified by baiyingting, 2010/12/22 */
    /* END:   Modified by baiyingting, 2011/1/4 */
    
    HI_VOIP_EVENT_LOCK();
    /*Initial the structure of event call back functions*/
    for(i=0;i<HME_MAX_CHANNEL_COUNT;i++)
    {
        stEventCb[i].hVoipHme = HI_INVALID_HANDLE;
        stEventCb[i].pfnEventCB = NULL;
        stEventCb[i].args = 0;
    }
    HI_VOIP_EVENT_UNLOCK();

    HI_INFO_HME("event deinitial end.\n");

    return Ret;
}
/* BEGIN: Added by zhangcheng, 2011/2/28   PN:msg trace set*/
HI_S32  VOIP_HME_UserMsgEventDeInit(HI_VOID)
{
    /* BEGIN: Modified by hefeng, 2011/6/1   PN:user mode event awake*/
    HI_S32     Ret = HI_SUCCESS;
	
    g_u32VoipUserMsgEventRunFlag = false;
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_USER_MSG_EVENT_WAKE_UP);
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);

    /* BEGIN: Modified by hefeng, 2011/6/3   PN:memory statistics voip2.0*/
    //if (NULL != tThreadVoipHmeUserMsgEvent)
    {      
        //pthread_cancel(tThreadVoipHmeUserMsgEvent);
        pthread_join(tThreadVoipHmeUserMsgEvent, NULL);
    }
    //tThreadVoipHmeUserMsgEvent = NULL;
    /* END:   Modified by hefeng, 2011/6/3 */
	
    return Ret;
    /* END:   Modified by hefeng, 2011/6/1 */
}
/* END:   Added by zhangcheng, 2011/2/28 */


HI_S32  VOIP_HME_EventCb_ChAdd(HI_HANDLE hVoipHme)
{
    HI_U32      i;
    
    HI_VOIP_EVENT_LOCK();

    for(i=0;i<HME_MAX_CHANNEL_COUNT;i++)
    {
        if(stEventCb[i].hVoipHme == hVoipHme)
        {
            HI_VOIP_EVENT_UNLOCK();
            return  HI_SUCCESS;
        }
    }

    for(i=0;i<HME_MAX_CHANNEL_COUNT;i++)
    {
        if(stEventCb[i].hVoipHme == HI_INVALID_HANDLE)
        {
            stEventCb[i].hVoipHme = hVoipHme;
            stEventCb[i].pfnEventCB = NULL;
            stEventCb[i].args = 0;
            HI_VOIP_EVENT_UNLOCK();
            return  HI_SUCCESS;
        }
    }
    HI_VOIP_EVENT_UNLOCK();
    HI_ERR_HME("stEventCb is full.\n");
 
    return HI_ERR_VOIP_HME_CREATE_ERR;
}

HI_S32  VOIP_HME_EventCb_ChRemove(HI_HANDLE hVoipHme)
{
    HI_U32      i;

    HI_VOIP_EVENT_LOCK();
    for(i=0;i<HME_MAX_CHANNEL_COUNT;i++)
    {
        if(stEventCb[i].hVoipHme == hVoipHme)
        {
            stEventCb[i].hVoipHme = HI_INVALID_HANDLE;
            stEventCb[i].pfnEventCB = NULL;
            stEventCb[i].args = 0;
            //return HI_SUCCESS;
        }
    }
    HI_VOIP_EVENT_UNLOCK();
    return HI_SUCCESS;
}

/* BEGIN: Modified by hefeng, 2011/6/3   PN:memory statistics voip2.0*/
HI_VOID* VOIP_HME_EventProc(HI_VOID *arg)
/* END:   Modified by hefeng, 2011/6/3 */
{
    /* BEGIN: Modified by baiyingting, 2010/12/22   PN:DTS2010122300084*/
    /* BEGIN: Modified by baiyingting, 2010/12/10   PN:DTS2010121100245  change pstEventList into local variable*/
    HI_S32  Ret;
    HI_U32  EventNum = 0;
    HI_U32  j;      //event index
    HI_U32  i;
    static VOIP_HME_EVENT_INFO_S stEventList[HME_MAX_EVENT_COUNT];

    HI_INFO_HME("Event proc start.\n");

    /* BEGIN: Modified by baiyingting, 2011/1/4   PN:DTS2011010403714*/
    while (true == g_u32VoipEventRunFlag)
    /* END:   Modified by baiyingting, 2011/1/4 */
    {
        //usleep(30*1000);
               
        Ret = VOIP_HME_GetEventList(&EventNum, stEventList);
        if(Ret != HI_SUCCESS)
        {
            continue;
        }

        HI_VOIP_EVENT_LOCK();
        for(j=0;j<EventNum;j++)
        {
            for(i=0;i<HME_MAX_CHANNEL_COUNT;i++)
            {
                if(stEventCb[i].hVoipHme == stEventList[j].hVoipHme)
                {
                    HI_INFO_HME("Event call back, ch [%x], event [%d], value [%d].\n",stEventCb[i].hVoipHme, stEventList[j].enEvent, stEventList[j].s32EventValue);
                    /* BEGIN: Modified for PN:FZH_REVIEW_101201_7 by f00172091, 2010/12/3 */
                    if(stEventCb[i].pfnEventCB != NULL)
                    {
                        Ret = stEventCb[i].pfnEventCB(stEventCb[i].hVoipHme, stEventList[j].enEvent, stEventList[j].s32EventValue, stEventCb[i].args);
                    }
                    /* END:   Modified for PN:FZH_REVIEW_101201_7 by f00172091, 2010/12/3 */
                    break;
                }
            }
            /* BEGIN: Deleted by baiyingting, 2010/12/13   PN:DTS2010121100245*/
            /*EventNum--;*/
            /* END: Deleted by baiyingting, 2010/12/13 */
        }
        HI_VOIP_EVENT_UNLOCK();
    }

    HI_INFO_HME("Event proc end.\n");
    /* END:   Modified by baiyingting, 2010/12/10 */
    /* END:   Modified by baiyingting, 2010/12/22 */

    /* BEGIN: Modified by baiyingting, 2011/1/4   PN:DTS2011010403714*/
    pthread_exit(NULL);
    /* END:   Modified by baiyingting, 2011/1/4 */
	return NULL;
}
/* BEGIN: Deleted by baiyingting, 2010/12/11   PN:DTS2010120904773*/

/* BEGIN: Added by zhangcheng, 2011/2/17   PN:msg trace set*/
/* BEGIN: Modified by hefeng, 2011/6/3   PN:memory statistics voip2.0*/
HI_VOID* VOIP_HME_UserMsgEventProc(HI_VOID *arg)
/* END:   Modified by hefeng, 2011/6/3 */
{
    HI_S32  Ret;
    HI_U32  EventNum = 0;
    HI_U32  i;      //event index
    static VOIP_HME_USER_MSG_EVENT_INFO_S stUserMsgEventList[HME_MAX_EVENT_COUNT];
    HI_INFO_HME("UserMsgEvent proc start.\n");

    /* BEGIN: Modified by baiyingting, 2011/1/4   PN:DTS2011010403714*/
    while (true == g_u32VoipUserMsgEventRunFlag)
    /* END:   Modified by baiyingting, 2011/1/4 */
    {
        //usleep(30*1000);
               
        Ret = VOIP_HME_GetUserMsgEventList(&EventNum, stUserMsgEventList);
        if(Ret != HI_SUCCESS)
        {
            continue;
        }
        
        for(i=0;i<EventNum;i++)
        {
            VOIP_HME_SetMsgCapFlag((HI_S32)stUserMsgEventList[i].uiChnId, stUserMsgEventList[i].uiUserMsgFlag, stUserMsgEventList[i].aucUsersPath);
        }
    }

    HI_INFO_HME("User msg Event proc end.\n");
    /* END:   Modified by baiyingting, 2010/12/10 */
    /* END:   Modified by baiyingting, 2010/12/22 */

    /* BEGIN: Modified by baiyingting, 2011/1/4   PN:DTS2011010403714*/
    pthread_exit(NULL);
    /* END:   Modified by baiyingting, 2011/1/4 */
	return NULL;
}
/* END:   Added by zhangcheng, 2011/2/17 */
#if 0
/*****************************************************************************
*   Prototype    : VOIP_HME_ParseChTlvAttr
*   Description  : parse the channel attributes (tlv format)
*   Input        : 
*        HI_VOID *pTlv :                     
*   Output       : 
*        HI_UNF_VOIP_CHN_ATTR_S *pstChAttr  :
*   Return Value : static HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
static HI_S32 VOIP_HME_ParseChTlvAttr(HI_VOID *pTlvParas,HI_UNF_VOIP_CHN_ATTR_S *pstChAttr)
{
    HI_UNF_VOIP_TLV_HEAD_S *pstTlvHead = NULL;
    HI_S32 sTlvLen;

    if(!pTlvParas)
    {
        HI_ERR_HME("pointer pTlvParas is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    if(!pstChAttr)
    {
        HI_ERR_HME("pointer pstChAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    pstTlvHead = (HI_UNF_VOIP_TLV_HEAD_S *)pTlvParas;
    sTlvLen = pstTlvHead->u16BlockLen;

    if (sTlvLen < HI_NUF_TVL_HEAD_LEN)
    {
        HI_ERR_HME("usMsgTotalLen is error\n");
        return HI_ERR_VOIP_HME_INVALID_PARA;        
    }
    pstTlvHead =(HI_UNF_VOIP_TLV_HEAD_S *)((HI_U8 *)pstTlvHead + HI_NUF_TVL_HEAD_LEN);
    sTlvLen -= HI_NUF_TVL_HEAD_LEN;
    
    /*find all IE until arravie message end*/
    while (sTlvLen > 0)
    {
        switch (pstTlvHead->u16BlockType)
        {
            case HI_UNF_VOIP_ATTR_ID_DSP:
                if(pstTlvHead->u16BlockLen == sizeof(HI_UNF_VOIP_DSP_CONFIG_PARA_S))
                {
                    memcpy((HI_U8 *)&pstChAttr->stDspHead, (HI_U8 *)pstTlvHead, HI_NUF_TVL_HEAD_LEN);
                    memcpy((HI_U8 *)&pstChAttr->stDspPara, (HI_U8 *)pstTlvHead+HI_NUF_TVL_HEAD_LEN, pstTlvHead->u16BlockLen);
                }
                break;

            case HI_UNF_VOIP_ATTR_ID_EC:
                if(pstTlvHead->u16BlockLen == sizeof(HI_UNF_VOICE_CONFIG_PARA_S))
                {
                    memcpy((HI_U8 *)&pstChAttr->stEcHead, (HI_U8 *)pstTlvHead, HI_NUF_TVL_HEAD_LEN);
                    memcpy((HI_U8 *)&pstChAttr->stEcPara, (HI_U8 *)pstTlvHead+HI_NUF_TVL_HEAD_LEN, pstTlvHead->u16BlockLen);
                }
                break;
                
            case HI_UNF_VOIP_ATTR_ID_JB:
                if(pstTlvHead->u16BlockLen == sizeof(HI_UNF_JB_CONFIG_PARA_S))
                {
                    memcpy((HI_U8 *)&pstChAttr->stJBHead, (HI_U8 *)pstTlvHead, HI_NUF_TVL_HEAD_LEN);
                    memcpy((HI_U8 *)&pstChAttr->stJBPara, (HI_U8 *)pstTlvHead+HI_NUF_TVL_HEAD_LEN, pstTlvHead->u16BlockLen);
                }
                break;

            case HI_UNF_VOIP_ATTR_ID_VQE:
                if(pstTlvHead->u16BlockLen == sizeof(HI_UNF_VQE_CONFIG_PARA_S))
                {
                    memcpy((HI_U8 *)&pstChAttr->stVQEHead, (HI_U8 *)pstTlvHead, HI_NUF_TVL_HEAD_LEN);
                    memcpy((HI_U8 *)&pstChAttr->stVQEPara, (HI_U8 *)pstTlvHead+HI_NUF_TVL_HEAD_LEN, pstTlvHead->u16BlockLen);
                }
                break;
                
            case HI_UNF_VOIP_ATTR_ID_NET:
                if(pstTlvHead->u16BlockLen == sizeof(HI_UNF_NET_CONFIG_PARA_S))
                {
                    memcpy((HI_U8 *)&pstChAttr->stNetHead, (HI_U8 *)pstTlvHead, HI_NUF_TVL_HEAD_LEN);
                    memcpy((HI_U8 *)&pstChAttr->stNetPara, (HI_U8 *)pstTlvHead+HI_NUF_TVL_HEAD_LEN, pstTlvHead->u16BlockLen);
                }
                break;

            case HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV:
                if(pstTlvHead->u16BlockLen == sizeof(HI_UNF_AUDDEV_PARA_S))
                {
                    memcpy((HI_U8 *)&pstChAttr->stAudevHead, (HI_U8 *)pstTlvHead, HI_NUF_TVL_HEAD_LEN);
                    memcpy((HI_U8 *)&pstChAttr->stAudevPara, (HI_U8 *)pstTlvHead+HI_NUF_TVL_HEAD_LEN, pstTlvHead->u16BlockLen);
                }
                break;

            default:
                break;
        }

        sTlvLen -= (HI_NUF_TVL_HEAD_LEN + pstTlvHead->u16BlockLen);
        pstTlvHead =(HI_UNF_VOIP_TLV_HEAD_S *)((HI_U8 *)pstTlvHead + HI_NUF_TVL_HEAD_LEN + pstTlvHead->u16BlockLen);
    }

    return HI_SUCCESS;
}
#endif
/* END: Deleted by baiyingting, 2010/12/11 */

/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_Init
*   Description  : initial hme voip module
*   Input        : HI_VOID  
*   Output       : None
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/25
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_VOIP_HME_Init(HI_VOID)
{
    struct stat st;
    HI_S32 Ret;
    HI_INFO_HME("Initial start.\n");

    /* BEGIN: Modified by wangjuan, 2011/1/24   PN:WJ_CODE_Resample*/
    /* BEGIN: Modified by wangjuan, 2010/12/16   PN:DTS2010121503003 */
    /* BEGIN: Modified by zhangcheng, 2011/2/11   PN:A9B02_ZC_0210_01 */
    /* It has been opened in the process, and return success */
    /* END:   Modified by zhangcheng, 2011/2/11 */
    if (g_VoipHmeDevFd > 0)
    {
        /* BEGIN: Added by baiyingting, 2010/12/21   PN:DTS2010122300084*/
        HI_WARN_HME("HME has been opened, g_VoipHmeDevFd:%d", g_VoipHmeDevFd);
        /* END:   Added by baiyingting, 2010/12/21 */
        return HI_SUCCESS;
    }
    /* END:   Modified by wangjuan, 2011/1/24 */

    if (HI_FAILURE == stat(g_VoipHmeDevName, &st))
    {
        HI_ERR_HME("HME is not exist.\n");
        return HI_ERR_VOIP_HME_DEV_NOT_EXIST;
    }

    if (!S_ISCHR (st.st_mode))
    {
        HI_ERR_HME("HME is not device.\n");
        return HI_ERR_VOIP_HME_NOT_DEV_FILE;
    }

    g_VoipHmeDevFd = open(g_VoipHmeDevName, O_RDWR|O_NONBLOCK, 0);

    /* BEGIN: Modified by baiyingting, 2010/12/13   PN:DTS2010121100245*/
    if (g_VoipHmeDevFd <= 0)
    {
        HI_ERR_HME("open HME err.\n");
        return HI_ERR_VOIP_HME_DEV_OPEN_ERR;
    }
    /* END:   Modified by baiyingting, 2010/12/13 */

    Ret = VOIP_HME_EventInit();
    if(HI_SUCCESS != Ret)
    {
        close(g_VoipHmeDevFd);
        g_VoipHmeDevFd = -1;

        HI_ERR_HME("event init err.\n");
        return HI_ERR_VOIP_HME_NO_INIT;
    }
    /* BEGIN: Added by zhangcheng, 2011/2/17   PN:msg trace set*/
    Ret = VOIP_HME_UserMsgEventInit();
    if(HI_SUCCESS != Ret)
    {
        close(g_VoipHmeDevFd);
        g_VoipHmeDevFd = -1;

        HI_ERR_HME("user msg event init err.\n");
        return HI_ERR_VOIP_HME_NO_INIT;
    }
    HI_INFO_HME("Initial end.\n");
    /* END:   Added by zhangcheng, 2011/2/17 */

    return HI_SUCCESS;
}


/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_DeInit
*   Description  : hme voip module deinitial
*   Input        : HI_VOID  
*   Output       : None
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/25
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_VOIP_HME_DeInit(HI_VOID)
{
    HI_INFO_HME("Deinitial start.\n");

    if (g_VoipHmeDevFd < 0)
    {
        return HI_SUCCESS;
    }

    /* BEGIN: Modified by baiyingting, 2010/12/22   PN:DTS2010122300084*/
    /* Should exit the event process thread at first because it will access the device*/
    (HI_VOID)VOIP_HME_EventDeInit();
    /* BEGIN: Added by zhangcheng, 2011/2/28   PN:msg trace set*/
    (HI_VOID)VOIP_HME_UserMsgEventDeInit();
    /* END:   Added by zhangcheng, 2011/2/28 */
    
    close(g_VoipHmeDevFd);

    g_VoipHmeDevFd = -1;
    /* END:   Modified by baiyingting, 2010/12/22 */
    
    HI_INFO_HME("Deinitial end.\n");
    return HI_SUCCESS;
}

/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_GetChDefaultAttr
*   Description  : Get the voip channel default attribute para, TLV format
*   Input        : 
*       HI_UNF_VOIP_WORKMODE_E enWorkMode :
*   Output       : 
*       HI_UNF_VOIP_CHN_ATTR_S *pstDefChAttr :
*   Return Value : HI_S32
		0 : success
		others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
const HI_UNF_DSP_CONFIG_BODY_S stDefaultDspPara = {
    (HI_U8)HI_UNF_VOIP_MODE_VOIVE,    //u8WorkMode
    (HI_U8)2,                                            //u8ConnectMode,  TERMINAL_MODE_SENDRECV
    (HI_U16)0,                                          //usCodec,  CODER_DECODER_G711A
    (HI_U8)8,                                          //u8RtpPT,  EN_VOIP_MEDIA_PROTOCOL_G711A
    (HI_U8)10,                                         //u8PacketPeriod,   HME_PCMLEN_10MS
    (HI_U8)0,                                          //u8DtmfTransMode
    (HI_U8)0,                                          //u8V34Control
};

const   HI_UNF_VOICE_CONFIG_BODY_S stDefaultEcPara = {
    (HI_U8)1,      //u8EcEnableFlag, EC On
    (HI_U8)0,       //u8NlpEnableFlag
    (HI_U8)0,       //u8NlpMode
    (HI_U8)0,       //u8VadEnableFlag
    (HI_U8)0,      //u8VadMode
    (HI_U8)0,       //u8CngEnableFlag
    (HI_U8)0,       //u8CngLevel
    (HI_U8)0,       //u8PlcMode
    (HI_U8)100,       //u8InputVolume
    (HI_U8)100,       //u8OutputVolume
    (HI_U8)0,       //u8InputMute
    (HI_U8)0,       //u8OutputMute
    (HI_S8)0,       //u8InputGain
    (HI_S8)0        //u8OutputGain
};

const HI_UNF_JB_CONFIG_BODY_S stDefaultJBPara = {
    (HI_U8)0,       //u8JbMode
/* BEGIN: Modified for PN:WJ_REVIEW_1202_3 by f00172091, 2010/12/3 */
    (HI_U8)0,       //u8JbInit
/* END:   Modified for PN:WJ_REVIEW_1202_3 by f00172091, 2010/12/3 */
    (HI_U8)150,       //u8JbMax
    (HI_U8)0,       //u8JbMin
};

#if 0
const HI_UNF_VQE_CONFIG_BODY_S stDefaultVQEPara = {
    (HI_U8)0,       //u8AgcFlag
    (HI_U8)13,       //u8AgcTargetValue
    (HI_U8)0,       //u8AnrFlag
    (HI_U8)0,       //u8AnrTargetValue
};

#else

const HI_UNF_VQE_CONFIG_BODY_S stDefaultVQEPara = {
    (HI_U8)0,       //ucLocalAgcFlag
/* BEGIN: Modified for PN:WJ_REVIEW_1202_4 by f00172091, 2010/12/3 */
    (HI_U8)0,       //ucLocalAgcValue, reserved
/* END:   Modified for PN:WJ_REVIEW_1202_4 by f00172091, 2010/12/3 */
    (HI_U8)0,       //ucRemoteAgcFlag
/* BEGIN: Modified for PN:WJ_REVIEW_1202_4 by f00172091, 2010/12/3 */
    (HI_U8)0,       //ucRemoteAgcValue ,reserved
/* END:   Modified for PN:WJ_REVIEW_1202_4 by f00172091, 2010/12/3 */
    (HI_U8)1,       //ucLocalAnrFlag
    (HI_U8)0,       //ucLocalAnrValue

    (HI_U8)1,       //ucRemoteAnrFlag
    (HI_U8)0,       //ucRemoteAnrValue
};

#endif

const HI_UNF_NET_CONFIG_BODY_S stDefaultNetPara = {
    (HI_U32)4,       //sip_len
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},       //sip[16]
    (HI_U32)4,       //dip_len
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},       //dip[16]

    (HI_U16)8192,       //sport
    (HI_U16)6000,       //dport

    (HI_U32)0x00,       //mask
    (HI_U32)0x10,       //ip_tos
    (HI_U32)0,       //vlan_en
    (HI_U32)0,       //vlan_pri
    (HI_U32)0,       //vlan_pid
    (HI_U32)0x0800,       //protocol
};

const HI_UNF_AUDDEV_BODY_S stDefaultAudDevPara = {
    (HI_S32)0,      //iAudioDevId
    /* audio input */ 
    (HI_S32)8000,      //iAiSampleRate
/* BEGIN: Modified for PN:WJ_REVIEW_1202_2 by f00172091, 2010/12/3 */
    (HI_S32)16,      //iAiBitPerSample
/* END:   Modified for PN:WJ_REVIEW_1202_2 by f00172091, 2010/12/3 */
    (HI_S32)1,      //iAiChannels
    /* audio output */ 
    (HI_S32)8000,      //iAoSampleRate
/* BEGIN: Modified for PN:WJ_REVIEW_1202_2 by f00172091, 2010/12/3 */
    (HI_S32)16,      //iAoBitPerSample
/* END:   Modified for PN:WJ_REVIEW_1202_2 by f00172091, 2010/12/3 */
    (HI_S32)1,      //iAoChannels
};

/* BEGIN: Added by wangjuan, 2011/1/22   PN:WJ_CODE_Resample*/
const HI_UNF_DIGIT_CONFIG_BODY_S stDefaultDigitalPara = {
    (HI_U32)0,
};
/* END:   Added by wangjuan, 2011/1/22 */

HI_S32  HI_MPI_VOIP_HME_GetChDefaultAttr(HI_UNF_VOIP_WORKMODE_E enWorkMode,HI_UNF_VOIP_CHN_ATTR_S *pstDefChAttr)
{
    #if 0
    HI_S32         Ret;
    VOIP_HME_IOCTL_DEF_CH_ATTR_S	stIoctlDefChAttr;
    #endif
   
    if (enWorkMode != HI_UNF_VOIP_MODE_VOIVE)
    {
        HI_ERR_HME("para enWorkMode is invalid.\n");
        return HI_ERR_VOIP_HME_INVALID_PARA;
    }
    
    if(!pstDefChAttr)
    {
        HI_ERR_HME("pointer pstDefChAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }
    
    CHECK_HME_INIT();
    #if 0    
    stIoctlDefChAttr.enWorkMode = enWorkMode;
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_GET_CH_DEFAULT_ATTR, &stIoctlDefChAttr);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    Ret = VOIP_HME_ParseChTlvAttr(stIoctlDefChAttr.pDefChAttr,pstDefChAttr);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }
    #else
    memset(pstDefChAttr,0,sizeof(HI_UNF_VOIP_CHN_ATTR_S));
    pstDefChAttr->stTlvHead.u16BlockLen = sizeof(HI_UNF_VOIP_CHN_ATTR_S);

    pstDefChAttr->stDspHead.u16BlockType = HI_UNF_VOIP_ATTR_ID_DSP;
    pstDefChAttr->stDspHead.u16BlockLen = sizeof(HI_UNF_VOIP_DSP_CONFIG_PARA_S);
    pstDefChAttr->stDspPara.stBody = stDefaultDspPara;

    pstDefChAttr->stEcHead.u16BlockType = HI_UNF_VOIP_ATTR_ID_EC;
    pstDefChAttr->stEcHead.u16BlockLen = sizeof(HI_UNF_VOICE_CONFIG_PARA_S);
    pstDefChAttr->stEcPara.stBody = stDefaultEcPara;

    pstDefChAttr->stJBHead.u16BlockType = HI_UNF_VOIP_ATTR_ID_JB;
    pstDefChAttr->stJBHead.u16BlockLen = sizeof(HI_UNF_JB_CONFIG_PARA_S);
    pstDefChAttr->stJBPara.stBody = stDefaultJBPara;

    pstDefChAttr->stVQEHead.u16BlockType = HI_UNF_VOIP_ATTR_ID_VQE;
    pstDefChAttr->stVQEHead.u16BlockLen = sizeof(HI_UNF_VQE_CONFIG_PARA_S);
    pstDefChAttr->stVQEPara.stBody = stDefaultVQEPara;

    pstDefChAttr->stNetHead.u16BlockType = HI_UNF_VOIP_ATTR_ID_NET;
    pstDefChAttr->stNetHead.u16BlockLen = sizeof(HI_UNF_NET_CONFIG_PARA_S);
    pstDefChAttr->stNetPara.stBody = stDefaultNetPara;
    
    pstDefChAttr->stAudevHead.u16BlockType = HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV;
    pstDefChAttr->stAudevHead.u16BlockLen = sizeof(HI_UNF_AUDDEV_PARA_S);
    pstDefChAttr->stAudevPara.stBody = stDefaultAudDevPara;

    /* BEGIN: Added by wangjuan, 2011/1/22   PN:WJ_CODE_Resample*/
    pstDefChAttr->stDigitHead.u16BlockType = HI_UNF_VOIP_ATTR_ID_CFG_LOCAL_RECV_DIGITAL;
    pstDefChAttr->stDigitHead.u16BlockLen = sizeof(HI_UNF_DIGIT_CONFIG_PARA_S);
    pstDefChAttr->stDigitPara.stBody = stDefaultDigitalPara;
    /* END:   Added by wangjuan, 2011/1/22 */ 
    #endif
    return HI_SUCCESS;
}


/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_CreateChannel
*   Description  : create voip channel
*   Input        : 
*       HI_UNF_VOIP_CHN_ATTR_S *pstChAttr :
*   Output       : 
*       HI_HANDLE *phVoipHme :
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
/* BEGIN: Modified for PN:FZH_REVIEW_101201_3 by f00172091, 2010/12/1 */
HI_S32 HI_MPI_VOIP_HME_CreateChannel(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr, HI_HANDLE *phVoipHme)
/* END:   Modified for PN:FZH_REVIEW_101201_3 by f00172091, 2010/12/1 */
{
    /* BEGIN: Modified by zhangcheng, 2011/1/28   PN:msg trace code*/
    HI_S32         Ret = HI_SUCCESS;
    /* END:   Modified by zhangcheng, 2011/1/28 */
    VOIP_HME_IOCTL_CH_ATTR_S    stIoctlCreateCh;
   
    if(!pstChAttr)
    {
        HI_ERR_HME("pointer pChAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    if(!phVoipHme)
    {
        HI_ERR_HME("pointer phVoipHme is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    CHECK_HME_INIT();

    /* BEGIN: Added by baiyingting, 2010/12/13   PN:DTS2010121100245*/
    stIoctlCreateCh.uiAttrLen = pstChAttr->stTlvHead.u16BlockLen;
    /* END:   Added by baiyingting, 2010/12/13 */
    stIoctlCreateCh.pChAttr = (HI_VOID *)pstChAttr;
    /* BEGIN: Modified for PN:FZH_REVIEW_101201_3 by f00172091, 2010/12/1 */
    stIoctlCreateCh.enWorkMode = enWorkMode;
    /* END:   Modified for PN:FZH_REVIEW_101201_3 by f00172091, 2010/12/1 */
    
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_CREATE_CHANNEL, &stIoctlCreateCh);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_HME("create voip channel failure\n"); 
        return Ret;
    }
    /* END:   Modified by zhangcheng, 2011/2/11 */

    Ret = VOIP_HME_EventCb_ChAdd(stIoctlCreateCh.hVoipHme);
    if (Ret != HI_SUCCESS)
    {
        /* BEGIN: Modified for PN:FZH_REVIEW_101201_8 by f00172091, 2010/12/3 */
        ioctl(g_VoipHmeDevFd, CMD_HME_DESTROY_CHANNEL, &stIoctlCreateCh.hVoipHme);
        /* END:   Modified for PN:FZH_REVIEW_101201_8 by f00172091, 2010/12/3 */
        HI_ERR_HME("Add channel resource for event call back func failure, %d.\n",Ret);
        return Ret;
    }  
       
    *phVoipHme = stIoctlCreateCh.hVoipHme;

    HI_INFO_HME("create channel success, handle is [%x].\n",*phVoipHme);
    return HI_SUCCESS;
}


/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_DestroyChannel
*   Description  : destroy channel
*   Input        : 
*       HI_HANDLE hVoipHme :
*   Output       : None
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_VOIP_HME_DestroyChannel(HI_HANDLE hVoipHme)
{
    HI_S32      Ret ;

    if (HI_INVALID_HANDLE == hVoipHme)
    {
        HI_ERR_HME("handle hVoipHme is invalid, [%x].\n",hVoipHme);
        return HI_ERR_VOIP_HME_INVALID_PARA; 
    }

    CHECK_HME_INIT();

    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_DESTROY_CHANNEL, &hVoipHme);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if(Ret != HI_SUCCESS)
    {
        HI_ERR_HME("Destroy channel error, handle [%x] ,Err [%d].\n",hVoipHme,Ret);
        return HI_ERR_VOIP_HME_DESTROY_ERR;
    }
    (HI_VOID)VOIP_HME_EventCb_ChRemove(hVoipHme);
    return Ret;
}


/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_GetChAttr
*   Description  : get channel attribute
*   Input        : 
*        HI_HANDLE hVoipHme :       
*   Output       : 
*        HI_UNF_VOIP_CHN_ATTR_S *pstChAttr :  
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_VOIP_HME_GetChAttr(HI_HANDLE hVoipHme, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr)
{
    /* BEGIN: Modified by zhangcheng, 2011/1/30   PN:msg trace code*/
    HI_S32         Ret = HI_SUCCESS;
    /* END:   Modified by zhangcheng, 2011/1/30 */
    VOIP_HME_IOCTL_CH_ATTR_S	stIoctlChAttr;
	
    if (HI_INVALID_HANDLE == hVoipHme)
    {
        HI_ERR_HME("handle hVoipHme is invalid.\n");
        return HI_ERR_VOIP_HME_INVALID_PARA; 
    }

    if(!pstChAttr)
    {
        HI_ERR_HME("pointer pstChAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    CHECK_HME_INIT();

    /* BEGIN: Modified by baiyingting, 2010/12/10   PN:DTS2010120904773*/
    stIoctlChAttr.hVoipHme = hVoipHme;
    stIoctlChAttr.pChAttr = pstChAttr;
    
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_GET_CH_ATTR, &stIoctlChAttr);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_HME("Modify channel failure, handle [%x] ,Err [%d].\n",hVoipHme,Ret);
        
    }  
    /* END:   Modified by baiyingting, 2010/12/10 */
    return Ret;
}


/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_ModifyChn
*   Description  : modify channel attribute
*   Input        : 
*       HI_HANDLE hVoipHme :                            
*       HI_UNF_VOIP_CHN_ATTR_S *pstChAttr :  
*   Output       : None
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_VOIP_HME_ModifyChnAttr(HI_HANDLE hVoipHme, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr)
{
    /* BEGIN: Modified by zhangcheng, 2011/1/28   PN:msg trace code*/
    HI_S32         Ret = HI_SUCCESS;
    /* END:   Modified by zhangcheng, 2011/1/28 */
    VOIP_HME_IOCTL_CH_ATTR_S	stIoctlChAttr;
	
    if (HI_INVALID_HANDLE == hVoipHme)
    {
        HI_ERR_HME("handle hVoipHme is invalid.\n");
        return HI_ERR_VOIP_HME_INVALID_PARA; 
    }

    if(!pstChAttr)
    {
        HI_ERR_HME("pointer pstChAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    CHECK_HME_INIT();

    stIoctlChAttr.hVoipHme = hVoipHme;
    /* BEGIN: Added by wangjuan, 2010/12/14   PN:DTS2010121403139*/
    stIoctlChAttr.uiAttrLen = pstChAttr->stTlvHead.u16BlockLen;
    /* END:   Added by wangjuan, 2010/12/14 */
    stIoctlChAttr.pChAttr = (HI_VOID *)pstChAttr;
    
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_MODIFY_CHANNEL, &stIoctlChAttr);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_HME("Modify channel failure, handle [%x] ,Err [%d].\n",hVoipHme,Ret);
    }
    return Ret;
}


/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_PlayTone
*   Description  : play tone
*   Input        : 
*       HI_HANDLE hVoipHme :         
*       HI_UNF_VOIP_PLAY_TONE_ATTR_S *pstToneAttr :  
*   Output       : None
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_VOIP_HME_PlayTone(HI_HANDLE hVoipHme, HI_UNF_VOIP_PLAY_TONE_ATTR_S *pstToneAttr)
{
    HI_S32         Ret;
    VOIP_HME_IOCTL_PLAY_TONE_S	stIoctlToneAttr;
	
    if (HI_INVALID_HANDLE == hVoipHme)
    {
        HI_ERR_HME("handle hVoipHme is invalid.\n");
        return HI_ERR_VOIP_HME_INVALID_PARA; 
    }

    if(!pstToneAttr)
    {
        HI_ERR_HME("pointer pstToneAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    CHECK_HME_INIT();

    stIoctlToneAttr.hVoipHme = hVoipHme;
    stIoctlToneAttr.pstToneAttr = pstToneAttr;
    
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_PLAY_TONE, &stIoctlToneAttr);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_HME("Play Tone failure, handle [%x] ,Err [%d].\n",hVoipHme,Ret);
        return Ret;
    }
    
    return HI_SUCCESS;

}

/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_StopTone
*   Description  : stop play tone
*   Input        : 
*       HI_HANDLE hVoipHme :  
*   Output       : None
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_VOIP_HME_StopTone(HI_HANDLE hVoipHme)
{
    HI_S32      Ret;

    if (HI_INVALID_HANDLE == hVoipHme)
    {
        HI_ERR_HME("handle hVoipHme is invalid.\n");
        return HI_ERR_VOIP_HME_INVALID_PARA; 
    }

    CHECK_HME_INIT();

    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_STOP_TONE, &hVoipHme);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_HME("Stop Tone failure, handle [%x] ,Err [%d].\n",hVoipHme,Ret);
        return Ret;
    }
    
    return HI_SUCCESS;
}

/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_PlayAnnouncement
*   Description  : play announcement
*   Input        : 
*       HI_HANDLE hVoipHme :
*       HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S *pstAnnAttr :  
*   Output       : None
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_VOIP_HME_PlayAnnouncement(HI_HANDLE hVoipHme, HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S *pstAnnAttr)
{
    /* BEGIN: Added by zhangcheng, 2011/1/28   PN:msg trace code*/
    HI_S32         Ret = HI_SUCCESS;
    /* END:   Added by zhangcheng, 2011/1/28 */
    VOIP_HME_IOCTL_PLAY_ANN_S	stIoctlPlayAnn;
    
    if (HI_INVALID_HANDLE == hVoipHme)
    {
        HI_ERR_HME("handle hVoipHme is invalid.\n");
        return HI_ERR_VOIP_HME_INVALID_PARA; 
    }

    if(!pstAnnAttr)
    {
        HI_ERR_HME("pointer pstAnnAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    if((pstAnnAttr->u32DataAddr == 0)||(pstAnnAttr->u32DataLen == 0))
    {
        HI_ERR_HME("Invalid audio file .\n");
        return HI_ERR_VOIP_HME_INVALID_PARA;
    }
    
    CHECK_HME_INIT();

    stIoctlPlayAnn.hVoipHme = hVoipHme;
    stIoctlPlayAnn.pstAnnAttr = pstAnnAttr;
    
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_PLAY_ANNOUNCEMENT, &stIoctlPlayAnn);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_HME("Play announcement failure, handle [%x] ,Err [%d].\n",hVoipHme,Ret);
    }
    return Ret;

}

/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_StopAnnouncement
*   Description  : stop play announcement
*   Input        :   
*       HI_HANDLE hVoipHme :
*   Output       : None
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_VOIP_HME_StopAnnouncement(HI_HANDLE hVoipHme,HI_U32 u32Direction)
{
    /* BEGIN: Modified by zhangcheng, 2011/1/30   PN:msg trace code*/
    HI_S32      Ret = HI_SUCCESS;
    /* END:   Modified by zhangcheng, 2011/1/30 */
    VOIP_HME_IOCTL_STOP_ANN_S	stIoctlStopAnn;

    if (HI_INVALID_HANDLE == hVoipHme)
    {
        HI_ERR_HME("handle hVoipHme is invalid.\n");
        return HI_ERR_VOIP_HME_INVALID_PARA; 
    }

    CHECK_HME_INIT();
    stIoctlStopAnn.hVoipHme = hVoipHme;
    stIoctlStopAnn.u32Direction = u32Direction;
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_STOP_ANNOUNCEMENT, &stIoctlStopAnn);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_HME("Stop announcement failure, handle [%x] ,Err [%d].\n",hVoipHme,Ret);
    }
    return Ret;
}

/*****************************************************************************
*   Prototype    : HI_MPI_VOIP_HME_RegisterEvent
*   Description  : register event
*   Input        : 
*       HI_HANDLE hVoipHme :
*       HI_UNF_VOIP_EVENT_CB_FN pfnEventCB :  
*       HI_U32 args :  user private data , should be return when call pfnEventCB                   
*   Output       : None
*   Return Value : HI_S32
*        0 : success
*        others : failure
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2010/11/24
*           Author       : f00172091
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_VOIP_HME_RegisterEvent(HI_HANDLE hVoipHme, HI_UNF_VOIP_EVENT_CB_FN pfnEventCB, HI_U32 args)
{
    HI_U32      i;
    if (HI_INVALID_HANDLE == hVoipHme)
    {
        HI_ERR_HME("handle hVoipHme is invalid.\n");
        return HI_ERR_VOIP_HME_INVALID_PARA; 
    }

    /* BEGIN: Deleted by wangjuan, 2010/12/10   PN:DTS2010120903238 */
    /*To unregister the event process function by use null pointer*/
    #if 0
    if(!pfnEventCB)
    {
        HI_ERR_HME("pointer pfnEventCB is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }
    #endif
    /* END: Deleted by wangjuan, 2010/12/10 */

    CHECK_HME_INIT();

    /* BEGIN: Modified by wangjuan, 2010/12/14   PN:WJ_CODE_REVIEW*/
    HI_VOIP_EVENT_LOCK();

    for(i=0;i<HME_MAX_CHANNEL_COUNT;i++)
    {
        if(stEventCb[i].hVoipHme == hVoipHme)
        {
            stEventCb[i].pfnEventCB = pfnEventCB;
            stEventCb[i].args = args;
            HI_VOIP_EVENT_UNLOCK();
            return  HI_SUCCESS;
        }
    }

    HI_VOIP_EVENT_UNLOCK();
    /* END:   Modified by wangjuan, 2010/12/14 */

    HI_ERR_HME("channel %8x is not exist.\n",hVoipHme);
    return HI_ERR_VOIP_HME_NOT_EXIST;

}

HI_S32 HI_MPI_VOIP_HME_GetRtcpStaticInfo(HI_HANDLE hVoipHme, HI_UNF_VOIP_RTCP_STATIC_INFO_S * pstRtcpInfo)
{
    /* BEGIN: Modified by hefeng, 2011/1/28   PN:msg trace code*/
    HI_S32         Ret = HI_SUCCESS; 
    /* END:   Modified by hefeng, 2011/1/28 */
    VOIP_HME_IOCTL_GET_RTCP_INFO_S   stIoctlGetRtcpInfo;
        
    if (HI_INVALID_HANDLE == hVoipHme)
    {
        HI_ERR_HME("handle hVoipHme is invalid.\n");
        return HI_ERR_VOIP_HME_INVALID_PARA; 
    }

    if(!pstRtcpInfo)
    {
        HI_ERR_HME("pointer pstRtcpInfo is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    CHECK_HME_INIT();

    stIoctlGetRtcpInfo.hVoipHme = hVoipHme;
    stIoctlGetRtcpInfo.pstRtcpInfo = pstRtcpInfo;
    
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_GET_RTCP_INFO, &stIoctlGetRtcpInfo);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_HME("Get Rtcp info failure, handle [%x] ,Err [%d].\n",hVoipHme,Ret);
    }
    return Ret;
}

HI_S32 HI_MPI_VOIP_HME_CfgRtcp(HI_HANDLE hVoipHme, HI_UNF_VOIP_CFG_RTCP_ATTR_S * pstRtcpAttr)
{
    /* BEGIN: Modified by hefeng, 2011/1/28   PN:msg trace code*/
    HI_S32         Ret = HI_SUCCESS;
    /* END:   Modified by hefeng, 2011/1/28 */
    VOIP_HME_IOCTL_CFG_RTCP_S stIoctlCfgRtcp;
        
    if (HI_INVALID_HANDLE == hVoipHme)
    {
        HI_ERR_HME("handle hVoipHme is invalid.\n");
        return HI_ERR_VOIP_HME_INVALID_PARA; 
    }

    if(!pstRtcpAttr)
    {
        HI_ERR_HME("pointer pstRtcpAttr is null.\n");
        return HI_ERR_VOIP_HME_NULL_PTR;
    }

    CHECK_HME_INIT();

    stIoctlCfgRtcp.hVoipHme = hVoipHme;
    stIoctlCfgRtcp.pstRtcpAttr = pstRtcpAttr;
    
    Ret = ioctl(g_VoipHmeDevFd, CMD_HME_CFG_RTCP, &stIoctlCfgRtcp);
    /* BEGIN: Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    (HI_VOID)VOIP_HME_ErrCodeConvert(Ret, &Ret);
    /* END:   Modified for PN:DTS2011040600979 by f00172091, 2011/4/8 */
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_HME("Config RTCP failure, handle [%x] ,Err [%d].\n",hVoipHme,Ret);
    }
    return Ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

