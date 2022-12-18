
/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : priv_hme.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/11/24
  Description   :
  History       :
  1.Date        : 2010/11/24
    Author      : f00172091
    Modification: Created file

******************************************************************************/

#ifndef __MPI_PRIV_HME_H__
#define __MPI_PRIV_HME_H__

#include "hi_unf_voip.h"
#include "HME_Common_Defines.h"
#include "hi_module.h"
#include "hi_debug.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define HI_ERR_HME(fmt...) \
            HI_TRACE(HI_TRACE_LEVEL_ERROR, HI_ID_VOIP_HME, fmt)

#define HI_WARN_HME(fmt...) \
            HI_TRACE(HI_TRACE_LEVEL_WARN, HI_ID_VOIP_HME, fmt)

/* BEGIN: Modified by baiyingting, 2010/12/13   PN:DTS2010121100245*/
#define HI_INFO_HME(fmt...) \
            HI_TRACE(HI_TRACE_LEVEL_INFO, HI_ID_VOIP_HME, fmt)
/* END:   Modified by baiyingting, 2010/12/13 */

/* BEGIN: Modified by baiyingting, 2010/12/10   PN:DTS2010121100245*/
#define HME_MAX_CHN_EVENT_COUNT 20
#define HME_MAX_EVENT_COUNT (HME_MAX_CHANNEL_COUNT * HME_MAX_CHN_EVENT_COUNT)
/* END:   Modified by baiyingting, 2010/12/10 */

typedef struct
{
    HI_HANDLE   hVoipHme;
    HI_UNF_VOIP_EVENT_E enEvent;
    HI_S32 s32EventValue;
    HI_U32  args;
}VOIP_HME_EVENT_INFO_S;
/* BEGIN: Added by zhangcheng, 2011/2/17   PN:msg trace set*/
typedef struct
{
    HI_U32 uiChnId;
    HI_U32 uiUserMsgFlag;/*true: start user mode message capture, false: stop user mode message capture*/
    HI_U8  aucUsersPath[HME_MAX_USER_MSG_TRACE_PATH];  /*saving direction of user mode message track file*/
}VOIP_HME_USER_MSG_EVENT_INFO_S;
/* END:   Added by zhangcheng, 2011/2/17 */

typedef struct
{
    HI_HANDLE   hVoipHme;
    HI_UNF_VOIP_EVENT_CB_FN pfnEventCB;
    HI_U32  args;
}VOIP_HME_EVENT_CB_S;

typedef struct
{
    /* BEGIN: Modified for PN:FZH_REVIEW_101201_3 by f00172091, 2010/12/1 */
    HI_UNF_VOIP_WORKMODE_E  enWorkMode;     /*input*/
    /* END:   Modified for PN:FZH_REVIEW_101201_3 by f00172091, 2010/12/1 */
    HI_HANDLE   hVoipHme;  
    /* BEGIN: Added by baiyingting, 2010/12/13   PN:DTS2010121100245*/
    HI_U32      uiAttrLen;   /*the length of data pChAttr pointing*/
    /* END:   Added by baiyingting, 2010/12/13 */
    HI_VOID *pChAttr;      /*Tlv format*/
}VOIP_HME_IOCTL_CH_ATTR_S;
  
typedef struct
{
    HI_HANDLE   hVoipHme;     
    HI_UNF_VOIP_PLAY_TONE_ATTR_S *pstToneAttr;
}VOIP_HME_IOCTL_PLAY_TONE_S;

typedef struct
{
    HI_HANDLE   hVoipHme;     
    HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S *pstAnnAttr;
}VOIP_HME_IOCTL_PLAY_ANN_S;

typedef struct
{
    HI_HANDLE   hVoipHme;
    HI_U32  u32Direction;
}VOIP_HME_IOCTL_STOP_ANN_S;

/* BEGIN: Modified by baiyingting, 2010/12/13   PN:DTS2010121100245*/
typedef struct
{
    HI_U32  uiEventNum;
    VOIP_HME_EVENT_INFO_S *pstEventList;
}VOIP_HME_IOCTL_GET_EVENT_S;
/* END:   Modified by baiyingting, 2010/12/13 */

/* BEGIN: Added by zhangcheng, 2011/2/17   PN:msg trace set*/
typedef struct
{
    HI_U32  uiUserMsgEventNum;
    VOIP_HME_USER_MSG_EVENT_INFO_S *pstUserMsgEventList;
}VOIP_HME_IOCTL_GET_USER_MSG_EVENT_S;
/* END:   Added by zhangcheng, 2011/2/17 */
typedef struct
{
    HI_HANDLE   hVoipHme;
    HI_UNF_VOIP_RTCP_STATIC_INFO_S * pstRtcpInfo;
}VOIP_HME_IOCTL_GET_RTCP_INFO_S;

typedef struct
{
    HI_HANDLE   hVoipHme;     
    HI_UNF_VOIP_CFG_RTCP_ATTR_S * pstRtcpAttr;
}VOIP_HME_IOCTL_CFG_RTCP_S;


#define CMD_HME_GET_CH_DEFAULT_ATTR		_IOWR(HI_ID_VOIP_HME,  1, VOIP_HME_IOCTL_CH_ATTR_S)
#define CMD_HME_CREATE_CHANNEL			_IOWR(HI_ID_VOIP_HME,  2, VOIP_HME_IOCTL_CH_ATTR_S)
#define CMD_HME_DESTROY_CHANNEL			_IOW(HI_ID_VOIP_HME,  3, HI_U32)
#define CMD_HME_GET_CH_ATTR				_IOWR(HI_ID_VOIP_HME,  4, VOIP_HME_IOCTL_CH_ATTR_S)
#define CMD_HME_MODIFY_CHANNEL			_IOW(HI_ID_VOIP_HME,  5, VOIP_HME_IOCTL_CH_ATTR_S)
#define CMD_HME_PLAY_TONE					_IOW(HI_ID_VOIP_HME,  6, VOIP_HME_IOCTL_PLAY_TONE_S)
#define CMD_HME_STOP_TONE					_IOW(HI_ID_VOIP_HME,  7, HI_U32)
#define CMD_HME_PLAY_ANNOUNCEMENT		_IOW(HI_ID_VOIP_HME,  8, VOIP_HME_IOCTL_PLAY_ANN_S)
#define CMD_HME_STOP_ANNOUNCEMENT		_IOW(HI_ID_VOIP_HME,  9, VOIP_HME_IOCTL_STOP_ANN_S)
#define CMD_HME_GET_EVENT			            _IOWR(HI_ID_VOIP_HME,  10, VOIP_HME_IOCTL_GET_EVENT_S)
#define CMD_HME_GET_RTCP_INFO		        	_IOWR(HI_ID_VOIP_HME,  11, VOIP_HME_IOCTL_GET_RTCP_INFO_S)
#define CMD_HME_CFG_RTCP                            _IOW(HI_ID_VOIP_HME,  12, VOIP_HME_IOCTL_CFG_RTCP_S)
/* BEGIN: Added by zhangcheng, 2011/2/17   PN:msg trace set*/
#define CMD_HME_GET_USER_MSG_EVENT			            _IOWR(HI_ID_VOIP_HME,  13, VOIP_HME_IOCTL_GET_EVENT_S)
/* END:   Added by zhangcheng, 2011/2/17 */
/* BEGIN: Modified for PN: DTS2011021500145 by FangZhonghua, 2011/3/8 */
#define CMD_HME_EVENT_WAKE_UP           _IO(HI_ID_VOIP_HME,  14)
/* END:  Modified for PN: DTS2011021500145 by FangZhonghua, 2011/3/8 */


/* BEGIN: Added by hefeng, 2011/6/1   PN: user mode event awake*/
#define CMD_HME_USER_MSG_EVENT_WAKE_UP        _IO(HI_ID_VOIP_HME, 15)
/* END:   Added by hefeng, 2011/6/1 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __MPI_PRIV_VO_H__ */


