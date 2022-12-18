#ifndef __MSG_TRACE_H__
#define __MSG_TRACE_H__

#include "priv_hme.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif


#define  CAP_MSG_HEAD_LEN       20          /*length of message frame head*/
/* BEGIN: Modified by zhangcheng, 2011/2/12   PN:wj_code_0211_02 */
#define  MSG_SEND               0           /*message send direction*/
#define  MSG_RSP                1           /*message respond direction*/
/* END:   Modified by zhangcheng, 2011/2/12 */

/* BEGIN: Added by zhangcheng, 2011/1/27   PN:msg trace code*/

typedef enum 
{
    USER_GET_DEF_ATTR = 100,
    USER_GET_DEF_ATTR_RSP,
    USER_CREATE_CHN,
    USER_CREATE_CHN_RSP,
    USER_DESTROY_CHN,
    USER_DESTROY_CHN_RSP,
    USER_GET_CHN_ATTR,
    USER_GET_CHN_ATTR_RSP,
    USER_MODIFY_CHN_ATTR,
    USER_MODIFY_CHN_RSP,
    USER_PLAY_ANNOUNCEMENT,
    USER_PLAY_ANNOUNCEMENT_RSP,
    USER_STOP_ANNOUNCEMENT,
    USER_STOP_ANNOUNCEMENT_RSP,
    USER_REG_EVENT,
    USER_REG_EVENT_RSP,
    USER_GET_RTCP_STATIC_INFO,
    USER_GET_RTCP_STATIC_INFO_RSP,
    USER_CFG_RTCP,
    USER_CFG_RTCP_RSP,
}USER_CMD_TYPE;

typedef void (*VOIP_HME_TraceSendMsg)(HI_HANDLE hVoipHme,HI_U8 *pDataCapBuf, HI_U16 uwLen);
typedef void (*VOIP_HME_TraceRecvMsg)(HI_HANDLE hVoipHme,HI_U8 *pDataCapBuf, HI_U16 uwLen);
typedef struct _VOIP_HME_TRACE_STRU
{
    VOIP_HME_TraceSendMsg pTraceSendMsg;
    VOIP_HME_TraceRecvMsg pTraceRecvMsg;
}VOIP_HME_TRACE_S;

typedef struct MSF_CAP_STRU
{
    HI_U32   uiMsgCapFlag;  /*message track flag, true: need message track, false: not need message track*/
}MSF_CAP_S;
typedef struct tagMSG_RECORD_STRU
{    
    HI_U16    uwSeq;  /*the whole system sort*/
    HI_U32    uiCnxId; /*chn Id*/
    HI_U16    uwTick;  /*cpu time*/
    HI_U16    uwDspTs;  /*dsp time*/
    HI_U16    uwDirection; /*message direction 0: EXT->Engine, 1: Engine->EXT*/
    HI_U16    uwLen;
    HI_U8     acData[1]; 
}MSG_RECORD_S;

/*message frame structure*/
typedef struct tagMSG_FRAME_STRU  
{    
    HI_S8    acKeyWord[4];  /*"MSG"+VERSION_TYPE ASCII
                              for example: message of R007_MRPD version is "MSG7"*/

    HI_U16  uwFrmLen;      /*length of the whole frame, including acKeyWord*/ 
    
    MSG_RECORD_S stRecord;
}MSG_FRAME_S;

typedef struct GET_DEF_ATTR_STRU
{
    HI_U32   uiCmd;
    HI_UNF_VOIP_WORKMODE_E enWorkMode;
}GET_DEF_ATTR_S;

typedef struct GET_DEF_ATTR_RSP_STRU
{
    HI_U32   uiCmd;
    HI_S32     iRet; 
    HI_UNF_VOIP_CHN_ATTR_S stDefChAttr;
}GET_DEF_ATTR_RSP_S;



typedef struct CREARE_CHN_CMD_STRU
{
    HI_U32   uiCmd;
    HI_UNF_VOIP_WORKMODE_E    enWorkMode;   
    HI_UNF_VOIP_CHN_ATTR_S    stChAttr;      /*Tlv format*/
}CREARE_CHN_CMD_S;
typedef struct  CREARE_CHN_CMD_RSP_STRU
{
    HI_U32   uiCmd;
    HI_S32     iRet; 
    HI_HANDLE   hVoipHme;  
}CREARE_CHN_CMD_RSP_S;


typedef struct GET_CHN_ATTR_CMD_STRU
{   
    HI_U32    uiCmd;
    HI_HANDLE    hVoipHme;  
}GET_CHN_ATTR_CMD_S;

typedef struct GET_CHN_ATTR_CMD_RSP_STRU
{
    HI_U32    uiCmd;
    HI_S32     iRet;  
    HI_UNF_VOIP_CHN_ATTR_S   stChAttr;
}GET_CHN_ATTR_CMD_RSP_S;

typedef struct MODIFY_CHN_ATTR_CMD_STRU
{
    HI_U32    uiCmd;
    HI_HANDLE    hVoipHme;
    HI_UNF_VOIP_CHN_ATTR_S    stChAttr;      /*Tlv format*/
}MODIFY_CHN_ATTR_CMD_S;

typedef struct MODIFY_CHN_ATTR_CMD_RSP_STRU
{
    HI_U32     uiCmd;
    HI_S32     iRet;  
}MODIFY_CHN_ATTR_CMD_RSP_S;

typedef struct PLAY_ANNOUNCEMENT_CMD_STRU
{
    HI_U32      uiCmd;
    HI_HANDLE   hVoipHme;
    HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S stAnnAttr;
}PLAY_ANNOUNCEMENT_CMD_S;

typedef struct PLAY_ANNOUNCEMENT_CMD_RSP_STRU
{   
    HI_U32     uiCmd;
    HI_S32     iRet;  
}PLAY_ANNOUNCEMENT_CMD_RSP_S;

typedef struct STOP_ANNOUNCEMENT_CMD_STRU
{
    HI_U32      uiCmd;
    HI_HANDLE   hVoipHme;
    HI_U32      u32Direction;
}STOP_ANNOUNCEMENT_CMD_S;


typedef struct STOP_ANNOUNCEMENT_CMD_RSP_STRU
{
    HI_U32      uiCmd;
    HI_S32      iRet; 
}STOP_ANNOUNCEMENT_CMD_RSP_S;

/* BEGIN: Added by hefeng, 2011/1/28   PN:msg trace code*/
typedef struct DESTROY_CHN_CMD_STRU
{
    HI_U32 uiCmd;
    HI_HANDLE  hVoipHme;
}DESTROY_CHN_CMD_S;

typedef struct DESTROY_CHN_CMD_RSP_STUR
{
    HI_U32 uiCmd;
    HI_S32 iRet;
}DESTROY_CHN_CMD_RSP_S;

typedef struct GET_RTCP_STATIC_INFO_STRU
{
    HI_U32 uiCmd;
    HI_HANDLE   hVoipHme;
}GET_RTCP_STATIC_INFO_S;

typedef struct GET_RTCP_STATIC_INFO_RSP_STRU
{
    HI_U32 uiCmd;
    HI_S32 iRet; 
    HI_UNF_VOIP_RTCP_STATIC_INFO_S stRtcpInfo;
}GET_RTCP_STATIC_INFO_RSP_S;


typedef struct REG_EVENT_STRU
{
    HI_U32 uiCmd;
    HI_HANDLE hVoipHme;
    HI_UNF_VOIP_EVENT_CB_FN pfnEventCB;
    HI_U32 args;
}REG_EVENT_S;

typedef struct REG_EVENT_RSP_STRU
{  
    HI_U32 uiCmd;
    HI_S32 iRet; 

}REG_EVENT_RSP_S;

typedef struct CFG_RTCP_CMD_STRU
{
    HI_U32 uiCmd;
    HI_HANDLE   hVoipHme;
    HI_UNF_VOIP_CFG_RTCP_ATTR_S stRtcpAttr;
}CFG_RTCP_CMD_S;

typedef struct CFG_RTCP_CMD_RSP_STRU
{
    HI_U32 uiCmd; 
    HI_S32 iRet;
}CFG_RTCP_CMD_RSP_S;


/* END:   Added by hefeng, 2011/1/28 */
HI_VOID VOIP_HME_InitCapMsg();
HI_VOID VOIP_HME_DeInitCapMsg();
HI_VOID VOIP_HME_CapMsg(HI_HANDLE hVoipHme, HI_U8 *pucDataCapBuf, HI_U16 uwLen, HI_U16  uwDirection);
HI_VOID  VOIP_HME_CapSendMsg(HI_HANDLE hVoipHme, HI_U8 *pucDataCapBuf, HI_U16 uwLen);
HI_VOID  VOIP_HME_CapRecvMsg(HI_HANDLE hVoipHme, HI_U8 *pucDataCapBuf, HI_U16 uwLen);
HI_VOID VOIP_HME_SetMsgCapFlag(int32 iChnId, uint32 uiFlag,HI_U8 *aucUsersPath);
HI_U32 VOIP_HME_GetMsgCapFlag(HI_U32 uiChnId);

HI_VOID VOIP_HME_ClearAllMsgCapFlag();
HI_U32 VOIP_HME_TimeGetTime(void);
/* END:   Added by zhangcheng, 2011/1/27 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif



#endif

