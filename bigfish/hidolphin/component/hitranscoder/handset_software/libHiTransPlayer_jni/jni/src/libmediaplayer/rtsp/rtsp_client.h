#ifndef RTSP_CLIENT_H
#define RTSP_CLIENT_H


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "rtsp_common.h"
#include "hi_list.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define MAX_IP_STR_LEN  (64)
#define MAX_URL_STR_LEN  (1024)

typedef enum E_MEDIA_CENTER_SORT
{
    Media_Center = 0,
    RTSP_Client,
    SORT_BUTT
}MEDIA_CENTER_SORT;

typedef struct s_MSG_Media_Center
{
    MEDIA_CENTER_SORT          task_Sort;
    HI_CHAR                       strFilePath[20];
    HI_CHAR                       strFileName[20];
    RTSP_CLIENT_STATUS         Operate;
}MSG_Media_Center;

typedef enum E_RTSP_String_Stype
{
    BASE = 1,
    SDP_V,
    SDP_O,
    SDP_S,
    SDP_C,
    SDP_T,
    SDP_M,
    SDP_A,
    OTHER
}RTSP_STRING_STYPE;

typedef struct F_RTSP_MSG_Task
{
    RTSP_SvrSort                 eSort;
    U8                           strPath[128];
    U8                           strURL[MAX_URL_STR_LEN];
    RTSP_CLIENT_STATUS           eMethord;
    U8                           VechnNum;
    U8                           strIP[MAX_IP_STR_LEN];
    S32                         port;
}RTSP_Msg_Task;

typedef struct F_RTSP_PARSE_ATTRIBUTE_S
{
    U8                                             strKey[128];
    U8                                             strValue[200];
    U16        eStype;
}RTSP_PARSE_ATTRIBUTE_S;

typedef struct F_RTSP_PARSE_UTIL_S
{
    RTSP_PARSE_ATTRIBUTE_S         struAttribute[MAX_Attribute_NUM];
    S32                            s32AttbriNum;
}RTSP_PARSE_UTIL_S;

typedef struct F_RTSP_CLIENT_S
{
    List_Head_S                sClientlist;
    U32                     u32Vechn;
    U32                        u32Cseq;
    S32                        s32RTSPSockId;
    U32                        u32SvrRTSPPort;
    U32                        u32CliAudioRTPSock;
    U32                        u32CliVideoRTPSock;
    U32                        u32CliAudioRTPPort;
    U32                        u32CliVideoRTPPort;
    U32                     u32TotalSec;
    U32                     u32LastVdecTime;
    volatile RTSP_CLIENT_STATUS        eClentStatus;
         RTSP_CLIENT_STATUS        ePrevClentStatus;
    RTSP_SvrSort            eClientRequestSort;
    RTSP_OUTSort            eOutPutStype;
    pthread_cond_t            condDecPro;
    pthread_mutex_t            mutexDecPro;
    U32                     RTPVideoReadThread;
    U32             RTPAudioReadThread;
    U32                     AdecTOAoThread;
    U32                        u32BeginTime;
    U32                     u32PauseTime;
    HI_BOOL                    BeginRead;
    RTSP_TRACK_S*            sTrack[2];
    U8                        strSessionAddr[32];
    U8                        strSvrIPAddr[MAX_IP_STR_LEN];
    U8                        strClientIPAddr[MAX_IP_STR_LEN];
    U8                        strSvrPath[64];
        U8          pchReceiveMsg[BufferSize];
    RTSP_Msg_Task task;
    HI_BOOL bReset;
    volatile HI_BOOL bUdpVdoFlag;
    volatile HI_BOOL bUdpAudFlag;
    HI_BOOL bSdpReady;
    HI_BOOL bUseUdpAcrossFlag;
    RTSP_PARSE_UTIL_S* pstruAtrributeUtil;
}RTSP_CLIENT_S;

typedef struct F_RTSP_MSG_Response_S
{

}RTSP_MSG_RESPONSE;

void HI_RTSP_ClientList_Init();
S16 HI_RTSP_Client_Create(RTSP_CLIENT_S **ppRTSPClient);
S16    HI_RTSP_ClientList_Remove(RTSP_CLIENT_S *pRTSPClient);
S16    HI_RTSP_Client_Init(RTSP_CLIENT_S *pRTSPClient,S32 s32SockId,U8* strFilePath);
S16 HI_RTSP_Client_Close(RTSP_CLIENT_S *pRTSPClient);
S16 RTSP_Track_Init(RTSP_TRACK_S** ppsTrack,RTSP_CLIENT_S* pRTSPClient);
S16 RTSP_Track_Delinit(RTSP_TRACK_S** psTrack);
S16 HI_RTSP_Client_Deinit();

S32 RTSP_Attribute_Parse(U8* strParseArg,S32* RTSPStatus,RTSP_PARSE_UTIL_S* self);

S16 RTSP_Setup_SvrSocket(RTSP_Msg_Task *task,RTSP_CLIENT_S *pRTSPClient);
S16 RTSP_Client_Process();
S32 RTSP_Client_Status_Operate(RTSP_CLIENT_S*       pRTSPClient,  RTSP_PARSE_UTIL_S* pstruAtrributeUtil );
S16 RTSP_Client_InitProcess(RTSP_CLIENT_S*       pRTSPClient);
S16 RTSP_Client_DescribeProcess(RTSP_CLIENT_S*  pRTSPClient, RTSP_PARSE_UTIL_S* struAtrributeUtil);
S16 RTSP_Client_SetupProcess(RTSP_CLIENT_S* pRTSPClient,RTSP_PARSE_UTIL_S* struAtrributeUtil);
S16 RTSP_Client_PlayProcess(RTSP_CLIENT_S* pRTSPClient,RTSP_PARSE_UTIL_S* struAtrributeUtil);
S16 RTSP_Client_TeardownProcess(RTSP_CLIENT_S* pRTSPClient);
S16 RTSP_Client_PauseProcess(RTSP_CLIENT_S*  pRTSPClient,RTSP_PARSE_UTIL_S* struAtrributeUtil);
S16 RTSP_Client_Continue(RTSP_CLIENT_S*   pRTSPClient,RTSP_PARSE_UTIL_S* struAtrributeUtil);
S16 RTSP_Client_PauseWait(RTSP_CLIENT_S* pRTSPClient);

S32  RTSP_Cient_OptionCircinal(RTSP_CLIENT_S* pRTSPClient,RTSP_PARSE_UTIL_S *struAtrributeUtil);
S16 RTSP_Describe_Request( RTSP_CLIENT_S*  pRTSPClient);
S16 RTSP_Client_TeardownRequest(RTSP_CLIENT_S* pRTSPClient);
S16 RTSP_ReponseParse(S32 s32SockId,RTSP_PARSE_UTIL_S* struAtrributeUtil);
S16 RTSP_SETUP_Request(RTSP_CLIENT_S*  pRTSPClient,RTSP_TRACK_S* sTrack);
S16 RTSP_Play_Request(RTSP_CLIENT_S*  pRTSPClient);
S16 RTSP_PLAY_Parse(RTSP_CLIENT_S* pRTSPClient,RTSP_PARSE_UTIL_S* struAtrributeUtil);
HI_VOID* RTSP_Client_Protocol_Process(HI_VOID* arg);

void RTSP_Client_MsgTeardown();
S16 RTSP_Client_Process();
RTSP_CLIENT_S* RTSP_Client_Get_CurSessionPtr(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
