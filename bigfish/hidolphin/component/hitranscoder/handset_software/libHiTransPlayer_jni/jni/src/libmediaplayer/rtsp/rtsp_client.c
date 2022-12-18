#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rtsp_client.h"
#include <time.h>
#include<unistd.h>
#include <asm/ioctls.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <pthread.h>
//#include "hi_mbuf.h"
#include "Hies_client.h"
#include "HiMLoger.h"

#define TAG "Rtsp_client"

RTSP_CLIENT_S g_astrRTSPClient[DefaultClientNum];
HI_BOOL         g_IS_Down;
static List_Head_S     g_astrRTSPClientFree;                       /*free session list head*/
static List_Head_S     g_astrRTSPClientBusy;                       /*busy session list head*/
static HI_BOOL  g_IsPause;
static HI_BOOL  g_bPauseFlag = HI_FALSE;
static U32      g_PauseTime;
static U32      g_ContinueTime;
static RTSP_CLIENT_S* pProtoClient = NULL;
static U32  chnId = 0;

static S16 HI_RTSP_SendMsg( S32 s32Socket, U8* pchMsgBuf, U32 u32MsgLen );
static S16  HI_RTSP_ReceiveMsg( S32 s32Socket, U8* pchMsgBuf, U32* u32MsgLen);
static S32  CreateUDPSock(S32 client_port,U8* IPaddr,HI_BOOL bool);
static S32  TransportAssemble(U8 *tranString,RTSP_TRACK_S* sTrack);
static S16    RTSP_Attribute_Clear(RTSP_PARSE_UTIL_S * self);
static HI_BOOL RTPIsComplete(U8* strBuff);
static S16 RTSP_Client_Server_GetPara_Process(RTSP_CLIENT_S*  pRTSPClient, RTSP_PARSE_UTIL_S* struAtrributeUtil);
static S16 RTSP_Client_Server_SetPara_Process(RTSP_CLIENT_S*  pRTSPClient, RTSP_PARSE_UTIL_S* struAtrributeUtil);
static S16 RTSP_Client_SetPara_Process(RTSP_CLIENT_S*  pRTSPClient,  RTSP_PARSE_UTIL_S* struAtrributeUtil);
static S16 RTSP_Client_GetPara_Process(RTSP_CLIENT_S*  pRTSPClient,  RTSP_PARSE_UTIL_S* struAtrributeUtil);
static S16 RTSP_Client_Option_Process(RTSP_CLIENT_S*  pRTSPClient, RTSP_PARSE_UTIL_S* struAtrributeUtil);
static HI_S32 Rtsp_Client_ReadSock(HI_S32 s32Socket, HI_CHAR* achMsgBuf, HI_S32 s32BufLen);
static HI_BOOL Rtsp_Client_IsRtspSocket_ReadyRead(HI_S32 s32Socket);
static S16 RTSP_SetPara_Request(RTSP_CLIENT_S*  pRTSPClient);
static S16 RTSP_Option_Request(RTSP_CLIENT_S*  pRTSPClient);
static S16 RTSP_GetPara_Request(RTSP_CLIENT_S*  pRTSPClient);
S16 RTP_ReadThreadCreate(RTSP_CLIENT_S* pRTSPClient);

/*初始化 Client Session List*/
/*init the session list*/
void HI_RTSP_ClientList_Init()
{
      U8            u8ClientNum;
      U32           u32IndexNum;
      memset(g_astrRTSPClient,0,sizeof(RTSP_CLIENT_S)*DefaultClientNum);
      INIT_LIST_HEAD(&g_astrRTSPClientFree);
      INIT_LIST_HEAD(&g_astrRTSPClientBusy);

      for(u8ClientNum = 0;u8ClientNum < DefaultClientNum;u8ClientNum++)
      {
            list_add_tail(&g_astrRTSPClient[u8ClientNum].sClientlist, &g_astrRTSPClientFree);
      }
}

/*创建一个client session, 从list中找到一个空闲的list并使用*/
/*create one client session and use it*/
S16 HI_RTSP_Client_Create(RTSP_CLIENT_S **ppRTSPClient)
{
     List_Head_S *plist = NULL;
     if(list_empty( &g_astrRTSPClientFree))
      {
            MMLOGI(TAG,"RTSP Client init free List error\n");
            return ERR_RTSP_PARAMETER;
      }
       plist = g_astrRTSPClientFree.next;
       list_del(plist);
       list_add(plist, &g_astrRTSPClientBusy);
       *ppRTSPClient = list_entry(plist, RTSP_CLIENT_S, sClientlist);
       return SUCCESS;
}

/*释放一个client session, 归还到list中*/
/*release one client session to list*/
S16    HI_RTSP_ClientList_Remove(RTSP_CLIENT_S *pRTSPClient)
{
    List_Head_S *pSessList;
    List_Head_S *pos;
    pSessList = &(pRTSPClient->sClientlist);
    list_for_each(pos, &g_astrRTSPClientBusy)
    {
        /*get the node from busy list*/
        if(pos == pSessList)
        {
            /*del the node to busy list，and add to free list*/
            list_del(pos);
            list_add(pos, &g_astrRTSPClientFree);
            break;
        }
    }
    return SUCCESS;
}
/*rtsp 客户端初始化, 设置初始状态*/
/*rtsp client Init, set the inited state*/
S16    HI_RTSP_Client_Init(RTSP_CLIENT_S *pRTSPClient,S32 s32SockId,U8* strFilePath)
{
    U8    u8Indexnum;
    pRTSPClient->s32RTSPSockId = s32SockId;
    pRTSPClient->u32Cseq = 0;
    pRTSPClient->eClentStatus = RTSP_RESPONSE_INIT;
    pRTSPClient->u32TotalSec= 0;


    for(u8Indexnum = 0;u8Indexnum < 2;u8Indexnum++)
    {
        RTSP_Track_Init(&(pRTSPClient->sTrack[u8Indexnum]),pRTSPClient);
    }
    pRTSPClient->BeginRead = HI_FALSE;
    g_IsPause = HI_FALSE;
    g_PauseTime = 0;
    g_ContinueTime = 0;
    pRTSPClient->u32PauseTime = 0;
    memset(&pRTSPClient->task , 0x00, sizeof(RTSP_Msg_Task));
    pRTSPClient->bUseUdpAcrossFlag = HI_FALSE;
    pRTSPClient->bSdpReady = HI_FALSE;
    return SUCCESS;
}

U32 getNowmTime()
{
    struct timeval now;
    S32      u32NowmTime;

    gettimeofday(&now,(struct timezone*) 0);
    u32NowmTime = now.tv_sec * 1000 + now.tv_usec /1000;
    return u32NowmTime;
}

/*rtsp 客户端销毁，释放资源*/
/*rtsp client destroy and release all the resources*/
S16 HI_RTSP_Client_Close(RTSP_CLIENT_S *pRTSPClient)
{
    //close the port and socket

    U32            u32NALUnum = 0;
    U8                    u8Indexnum;

    for(u8Indexnum = 0;u8Indexnum < 2;u8Indexnum++)
    {
        MMLOGI(TAG,"the end is %d,the begin is %d\n",pRTSPClient->sTrack[u8Indexnum]->u32RTPend,
                    pRTSPClient->sTrack[u8Indexnum]->u32RTPBegin);
            MMLOGI(TAG,"the total frame is %d\n",pRTSPClient->sTrack[u8Indexnum]->u32FrameTotal);
            MMLOGI(TAG,"eSVRType is %d\n",(pRTSPClient->sTrack[u8Indexnum]->eSvrTrackType));
            if(NULL != pRTSPClient->sTrack[u8Indexnum])
            {
                if(SUCCESS != RTSP_Track_Delinit(&(pRTSPClient->sTrack[u8Indexnum])))
                {
                        MMLOGI(TAG,"Delinit RTSP track error\n");
                }
                pRTSPClient->sTrack[u8Indexnum] = NULL;
            }
       }
        memset(pRTSPClient->strSessionAddr,0,32);
    pRTSPClient->eClentStatus = RTSP_CLIENT_INIT;
    if(pRTSPClient->pstruAtrributeUtil)
        free(pRTSPClient->pstruAtrributeUtil);
    HI_RTSP_ClientList_Remove(pRTSPClient);
    return SUCCESS;
}
/*rtsp 音视频通道属性集初始化*/
/*rtsp audio track attributes and video track attributes init*/
S16 RTSP_Track_Init(RTSP_TRACK_S** ppsTrack,RTSP_CLIENT_S* pRTSPClient)
{
    *ppsTrack = malloc(sizeof(RTSP_TRACK_S));
    if(NULL == (*ppsTrack))
    {
        MMLOGI(TAG,"malloc error\n");
        return ERR_RTSP_MEMORY;
    }
        void* pTmp = (*ppsTrack);
        MMLOGI(TAG,"RTSP_Track_Delinit malloc track 0x%08x \n", pTmp);
    memset(*ppsTrack,0,sizeof(RTSP_TRACK_S));
    (*ppsTrack)->eTrackStype = TRACK_INIT;
    (*ppsTrack)->u32FrameTotal = 0;
    (*ppsTrack)->u32FrameLost = 0;
    (*ppsTrack)->u32RTPend = 0;
    (*ppsTrack)->u32RTPBegin = 0;
    (*ppsTrack)->u32RTPLastTimeStamp = 0;
    return SUCCESS;
}
/*rtsp 音视频通道属性集去初始化*/
/*rtsp audio track attributes and video track attributes deinit*/
S16 RTSP_Track_Delinit(RTSP_TRACK_S** psTrack)
{
        RTSP_TRACK_S* pTmp = (*psTrack);
        MMLOGI(TAG,"RTSP_Track_Delinit free track 0x%08x \n", pTmp);
    if(NULL != *psTrack)
    {
        free(*psTrack);
        *psTrack = NULL;
    }
    return SUCCESS;
}

/*销毁现存所有client session, 当前仅支持单个session*/
/*destroy all the client sessions*/
S16 HI_RTSP_Client_Deinit()
{
    U8            u8ClientIndexnum;
    U8            u8Indexnum;
    U8            u8here;
    U8            u8Index;
    for(u8ClientIndexnum = 0;u8ClientIndexnum < DefaultClientNum;u8ClientIndexnum++)
    {
        for(u8Index = 0;u8Index < 2;u8Index++)
    {
        if(NULL != g_astrRTSPClient[u8ClientIndexnum].sTrack[u8Index])
        {
            free(g_astrRTSPClient[u8ClientIndexnum].sTrack[u8Index]);
            g_astrRTSPClient[u8ClientIndexnum].sTrack[u8Index] = NULL;
        }
    }
        g_astrRTSPClient[u8ClientIndexnum].eClentStatus = RTSP_CLIENT_INIT;
    }
    return SUCCESS;
}

/*同URL指示的服务器建立TCP连接*/
/*connect with url server*/
S16 RTSP_Setup_SvrSocket(RTSP_Msg_Task *task,RTSP_CLIENT_S *pRTSPClient)
{
    S32         s32Socket;
    int strLen = sizeof(struct sockaddr_in);
    U8*         pTemp;
    U8*         pFile;
   struct sockaddr_in addr;
    if(NULL == pRTSPClient || RTSP_RESPONSE_INIT != pRTSPClient->eClentStatus || NULL == task)
    {
            MMLOGI(TAG,"the setup socket can't process");
            return ERR_RTSP_PARAMETER;
    }
    MMLOGI(TAG,"start socket\n");
    MMLOGI(TAG,"the task url is %s\n",task->strURL);
    if(NULL != (pTemp = strstr(task->strURL,"rtsp://")))
    {
        pTemp += strlen("rtsp://");
        strncpy(pRTSPClient->strSvrIPAddr, task->strIP, MAX_IP_STR_LEN);
        pFile = strchr(pTemp,'/');
        if(pFile)
            strcpy(pRTSPClient->strSvrPath,pFile);
    }
    else
    {
        MMLOGI(TAG,"url is not rtsp req  return failed\n");
        return ERR_RTSP_PARAMETER;
    }
    pRTSPClient->eClientRequestSort = task->eSort;
    pRTSPClient->u32Vechn = task->VechnNum;

      memset(&addr,0,sizeof(struct sockaddr_in));
        addr.sin_addr.s_addr = inet_addr(pRTSPClient->strSvrIPAddr);
    MMLOGI(TAG,"the ip is %s\n",pRTSPClient->strSvrIPAddr);
    MMLOGI(TAG,"file is %s\n",pRTSPClient->strSvrPath,pFile);
    MMLOGI(TAG,"port is %d\n",task->port);
    addr.sin_port = htons(task->port);
    addr.sin_family = AF_INET;

    s32Socket = socket(AF_INET,SOCK_STREAM,0);
    if(s32Socket < 0)
        MMLOGI(TAG,"socket error\n");
    unsigned long ul = 1;
    fd_set fset;
    struct timeval tval;
    int error=-1;
    int len = sizeof(int);
    tval.tv_sec = 3;
    tval.tv_usec = 500000;
    ioctl(s32Socket, FIONBIO, &ul);
    if(connect(s32Socket,(struct sockaddr *)(&addr),sizeof(struct sockaddr_in)) < 0)
    {
        if(errno !=  EINPROGRESS)
        {
            MMLOGI(TAG,"connect error happened \n");
            return ERR_RTSP_PROCFAILURE;
        }
        FD_ZERO(&fset);
        FD_SET(s32Socket,&fset);
        MMLOGI(TAG,"select enter\n");
        if(select(s32Socket+1, NULL, &fset, NULL,&tval) <= 0)
        {
            MMLOGI(TAG,"Socket connect error\n");
            return ERR_RTSP_PROCFAILURE;
        }
        MMLOGI(TAG,"select out\n");
        getsockopt(s32Socket, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len);
        if(error != 0)
        {
            MMLOGI(TAG,"getsockopt  error\n");
            return ERR_RTSP_PROCFAILURE;
        }
    }
    else
    {
        MMLOGI(TAG,"connect success \n");
    }
    ul = 0;
    ioctl(s32Socket, FIONBIO, &ul);
    pRTSPClient->s32RTSPSockId = s32Socket;
    pRTSPClient->u32SvrRTSPPort = task->port;
    return SUCCESS;
}

/*获取 server 端IP地址的函数*/
/*get the server IP*/
void RTSP_Client_SOCKET_GetHostIP(S32 s32SockId,U8* IPAddr)
{
    S32 namelen = 0;
    struct sockaddr_in addr;
    namelen = sizeof(struct sockaddr);
    getsockname(s32SockId, (struct sockaddr *)&addr, &namelen);
    strcpy(IPAddr, inet_ntoa( addr.sin_addr ));
}

RTSP_CLIENT_S* RTSP_Client_Get_CurSessionPtr(HI_VOID)
{
    return pProtoClient;
}

HI_S32 RTSP_Client_EnvInit(RTSP_Msg_Task *task)
{
    RTSP_CLIENT_S*       pRTSPClient = NULL;
    RTSP_PARSE_UTIL_S* pstruAtrributeUtil = NULL;

    HI_RTSP_ClientList_Init();
    if(ERR_RTSP_PARAMETER == HI_RTSP_Client_Create(&pRTSPClient))
    {
        MMLOGI(TAG,"client rtsp create error\n");
        return ERR_RTSP_PARAMETER;
    }
    pProtoClient = pRTSPClient;
    HI_RTSP_Client_Init(pRTSPClient,0,"/");
    if(SUCCESS != RTSP_Setup_SvrSocket(task,pRTSPClient))
    {
        MMLOGI(TAG,"setup socket error\n");
        HI_RTSP_ClientList_Remove(pRTSPClient);
        return ERR_RTSP_PROCFAILURE;
    }
    pRTSPClient->task = *task;
    pstruAtrributeUtil = malloc(sizeof(RTSP_PARSE_UTIL_S));
    if(!pstruAtrributeUtil)
    {
        MMLOGI(TAG,"malloc  pstruAtrributeUtil error\n");
        close(pRTSPClient->s32RTSPSockId);
        HI_RTSP_ClientList_Remove(pRTSPClient);
        return ERR_RTSP_MEMORY;
    }
    pRTSPClient->pstruAtrributeUtil = pstruAtrributeUtil;
    if(strstr(pRTSPClient->task.strURL, "udpAcross")
        ||strstr(pRTSPClient->task.strURL, "udpacross"))
    {
        pRTSPClient->bUseUdpAcrossFlag = HI_TRUE;
    }
    else
        pRTSPClient->bUseUdpAcrossFlag = HI_FALSE;
    return HI_SUCCESS;
}
/*rtsp 客户端协议控制循环主流程，相关的rtsp 连接建立过程都在
    此函数中实现*/
/*main stream of rtsp client protocol controller loop are realized in this function */
S16 RTSP_Client_Process(void)
{
    RTSP_CLIENT_S*       pRTSPClient = pProtoClient;
    S32                  s32ret;
    g_IS_Down = HI_FALSE;

    while(pRTSPClient->eClentStatus != RTSP_CLIENT_BUTT)
    {
        if(SUCCESS != RTSP_Client_Status_Operate(pRTSPClient, pRTSPClient->pstruAtrributeUtil))
        {
            MMLOGI(TAG,"status operation error\n");
            pRTSPClient->eClentStatus = RTSP_CLIENT_TEARDOWN;
        }
        if(RTSP_CLIENT_TEARDOWN == pRTSPClient->eClentStatus)
        {
            if(SUCCESS != RTSP_Client_TeardownProcess(pRTSPClient))
            {
                MMLOGI(TAG,"TearDown Process error\n");
            }
            HI_RTSP_Client_Close(pRTSPClient);
            MMLOGI(TAG,"teardown is called!\n");
            break;
        }
    }
    MMLOGI(TAG,"destroy called finished!\n");
    return SUCCESS;
}

void RTSP_Client_MsgTeardown()
{
    g_IS_Down = HI_TRUE;
    return;
}

void RTSP_Client_MsgPause()
{
    g_IsPause = HI_TRUE;
    return;
}

void RTSP_Client_MsgContinue()
{
    g_IsPause = HI_FALSE;
    return;
}
/*rtsp PLAY 请求，服务器返回的回应字段解析*/
/*parsing response of rtsp PLAY request from server*/
S16 RTSP_PLAY_Parse(RTSP_CLIENT_S* pRTSPClient,RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    RTSP_TRACK_S*               sTrack;
    U32                           u32IndexNum;
    U8*                           pchStrKey;
    U8*                           pchStrValue;
    U8*                           pchTemp;

    for(u32IndexNum = 0;u32IndexNum < struAtrributeUtil->s32AttbriNum;u32IndexNum++)
    {
        if(NULL != (pchStrKey = strstr(struAtrributeUtil->struAttribute[u32IndexNum].strKey,"RTP-Info")))
        {
            pchStrValue = struAtrributeUtil->struAttribute[u32IndexNum].strValue;
            break;
        }
    }
    pchTemp = pchStrValue;
    for(u32IndexNum = 0;u32IndexNum < 2;u32IndexNum++)
    {
        sTrack = pRTSPClient->sTrack[u32IndexNum];
        if(NULL != (pchTemp = strstr(pchTemp,"trackID=")))
        {
            pchTemp += strlen("trackID=");
            if(sTrack->u32TrackId = atoi(pchTemp))
            {
                if(NULL == (pchTemp = strstr(pchTemp,"seq=")))
                    return ERR_RTSP_PARAMETER;
                pchTemp += strlen("seq=");
                pRTSPClient->u32LastVdecTime = 0;
                if(NULL == (pchTemp = strstr(pchTemp,"rtptime=")))
                    return ERR_RTSP_PARAMETER;
                pchTemp += strlen("rtptime=");
                sTrack->u32RTPLastTimeStamp = atoi(pchTemp);
                sTrack->u32RTPtimeStamp = sTrack->u32RTPLastTimeStamp;
            }
        }
        //pchTemp = strchr(pchTemp,',');
    }
    return SUCCESS;
}

/*当前rtsp session 处于PAUSE状态，向server 发送PLAY 请求*/
S16 RTSP_Client_Continue(RTSP_CLIENT_S*   pRTSPClient,RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    U8      strRequest[256];
    U8      strTemp[64];
    S32     s32IndexNum;
    S32     s32Ret;

    memset(strRequest,0,sizeof(strRequest));
    pRTSPClient->u32Cseq++;
    strcat(strRequest,"PLAY rtsp://");
    strcat(strRequest,pRTSPClient->strSvrIPAddr);
    strcat(strRequest,pRTSPClient->strSvrPath);
    strcat(strRequest,"/ RTSP/1.0\r\n");
    sprintf(strTemp,"Cseq:%d\r\n",pRTSPClient->u32Cseq);
    strcat(strRequest,strTemp);
    sprintf(strTemp,"Session:%s\r\n\r\n",pRTSPClient->strSessionAddr);
    strcat(strRequest,strTemp);
    HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,strRequest,strlen(strRequest));
    memset(struAtrributeUtil,0,sizeof(RTSP_PARSE_UTIL_S));
    s32Ret = RTSP_ReponseParse(pRTSPClient->s32RTSPSockId,struAtrributeUtil);
    if(SUCCESS != s32Ret)
    {
       MMLOGI(TAG,"RTSP Setup Receive and Parse error status is %d\n",s32Ret);
       return ERR_RTSP_PROCFAILURE;
    }

    pRTSPClient->eClentStatus = RTSP_CLIENT_PLAY;
    g_IsPause = HI_FALSE;
    pRTSPClient->u32PauseTime += getNowmTime() - g_PauseTime;
    return HI_SUCCESS;
}

/*rtsp 客户端状态转换流程, rtsp连接建立过程，以及客户端，服务端
    指令交互处理过程处理*/
/*rtsp client state change process,  the connection of rtsp establishment , and the control instruction
    communication between client and server*/
S32 RTSP_Client_Status_Operate(RTSP_CLIENT_S*   pRTSPClient, RTSP_PARSE_UTIL_S* pstruAtrributeUtil )
{
        U32        ReceiveMsgLen;

        memset(pstruAtrributeUtil,0,sizeof(RTSP_PARSE_UTIL_S));
        if(NULL == pRTSPClient && RTSP_CLIENT_BUTT == pRTSPClient->eClentStatus)
        {
                MMLOGI(TAG,"RTSPClient parameter error\n");
                return ERR_RTSP_PARAMETER;
        }
        switch(pRTSPClient->eClentStatus)
        {
                case RTSP_CLIENT_INIT:
                    if(SUCCESS != RTSP_Client_InitProcess(pRTSPClient))
                    {
                        MMLOGI(TAG,"InitProcess error\n");
                        return ERR_RTSP_PROCFAILURE;
                    }
                    break;
                case RTSP_CLIENT_OPTION:
                    if(SUCCESS != RTSP_Client_Option_Process(pRTSPClient, pstruAtrributeUtil))
                    {
                        MMLOGI(TAG,"InitProcess error\n");
                        return ERR_RTSP_PROCFAILURE;
                    }
                    break;
                case RTSP_CLIENT_GET_PARAMETER:
                    if(SUCCESS != RTSP_Client_GetPara_Process(pRTSPClient, pstruAtrributeUtil))
                    {
                        MMLOGI(TAG,"getParameter Process error\n");
                        return ERR_RTSP_PROCFAILURE;
                    }
                    break;
                case RTSP_CLIENT_SET_PARAMETER:
                    if(SUCCESS != RTSP_Client_SetPara_Process(pRTSPClient, pstruAtrributeUtil))
                    {
                        MMLOGI(TAG,"getParameter Process error\n");
                        return ERR_RTSP_PROCFAILURE;
                    }
                    break;
                case RTSP_CLIENT_DESCRIBE:
                    if(SUCCESS != RTSP_Client_DescribeProcess(pRTSPClient,pstruAtrributeUtil))
                    {
                        MMLOGI(TAG,"Describe Process error\n");
                        return ERR_RTSP_PROCFAILURE;
                    }
                    break;
                case RTSP_CLIENT_SETUP:
                      if(SUCCESS != RTSP_Client_SetupProcess(pRTSPClient,pstruAtrributeUtil))
                        {
                            MMLOGI(TAG,"Setup Process error\n");
                            return ERR_RTSP_PROCFAILURE;
                         }
                    break;
                case RTSP_CLIENT_PLAY:
                case RTSP_CLIENT_READY:
                    if(SUCCESS != RTSP_Client_PlayProcess(pRTSPClient,pstruAtrributeUtil))
                    {
                        MMLOGI(TAG,"Play Process error\n");
                        return ERR_RTSP_PROCFAILURE;
                    }
                    break;
                case RTSP_SERVER_GET_PARAMETER:
                      if(SUCCESS != RTSP_Client_Server_GetPara_Process(pRTSPClient,pstruAtrributeUtil))
                        {
                            MMLOGI(TAG,"Setup Process error\n");
                            return ERR_RTSP_PROCFAILURE;
                         }
                    break;
                case RTSP_SERVER_SET_PARAMETER:
                      if(SUCCESS != RTSP_Client_Server_SetPara_Process(pRTSPClient,pstruAtrributeUtil))
                        {
                            MMLOGI(TAG,"Setup Process error\n");
                            return ERR_RTSP_PROCFAILURE;
                         }
                    break;
                case RTSP_CLIENT_PAUSE:
                    if( HI_FALSE == g_IsPause )
                    {
                        RTSP_Client_Continue(pRTSPClient,pstruAtrributeUtil);
                    }else
                    {
                        #if 0
                        if(SUCCESS != RTSP_Client_PauseWait(pRTSPClient))
                        {
                            printf("Pause Process error\n");
                            return ERR_RTSP_PROCFAILURE;
                        }
                        #endif
                    }
                    break;
        }

        if(pRTSPClient->eClentStatus ==  RTSP_CLIENT_PLAY
            ||pRTSPClient->eClentStatus ==  RTSP_CLIENT_PAUSE)
        {
            if(HI_TRUE == Rtsp_Client_IsRtspSocket_ReadyRead(pRTSPClient->s32RTSPSockId))
            {
                HI_S32 ret = 0;

                memset(pRTSPClient->pchReceiveMsg,0,BufferSize);
                ret = Rtsp_Client_ReadSock(pRTSPClient->s32RTSPSockId, pRTSPClient->pchReceiveMsg, (BufferSize));
                if(HI_FAILURE == ret)
                {
                    pRTSPClient->eClentStatus = RTSP_CLIENT_TEARDOWN;
                    MMLOGI(TAG,"error happened,  jump to teardown \n");
                    return HI_FAILURE;
                }
                /*检测服务器传来的数据是否是正确的控制指令，不是就不处理*/
                /*check if data from server is one of GET_PARAMETER , SET_PARAMETER, no handle for neither*/
                if(NULL != strstr(pRTSPClient->pchReceiveMsg,"GET_PARAMETER"))
                {
                    pRTSPClient->ePrevClentStatus = pRTSPClient->eClentStatus;
                    pRTSPClient->eClentStatus = RTSP_SERVER_GET_PARAMETER;
                }
                else if(NULL != strstr(pRTSPClient->pchReceiveMsg,"SET_PARAMETER"))
                {
                    pRTSPClient->ePrevClentStatus = pRTSPClient->eClentStatus;
                    pRTSPClient->eClentStatus = RTSP_SERVER_SET_PARAMETER;
                    return SUCCESS;
                }
            }
        }
        return SUCCESS;
}

S16 RTSP_Client_InitProcess(RTSP_CLIENT_S*  pRTSPClient)
{
    pRTSPClient->eClentStatus = RTSP_CLIENT_OPTION;
    return SUCCESS;
}
/*获取SET_PARAMETER  的命令类型, RESET, PAUSE, CHANGE_AUDIO_TRACK, SEEK*/
/*get the command type , one of  RESET, PAUSE, CHANGE_AUDIO_TRACK, SEEK*/
S16 Rtsp_Client_GetCommandType(HI_CHAR* strMSgBuf, HI_S32* pType, HI_CHAR* typeStr)
{
    RTSP_SETPARA_COMMAND type = SETPARA_COMMAND_BUTT;
    HI_CHAR  cmdBuf[10] = {0};
    HI_CHAR* pbufPtr = strMSgBuf;
    HI_CHAR* pTmp1 = NULL;
    HI_CHAR* pTmp2 = NULL;

    pTmp1 =strstr(pbufPtr, "X_Support_method:");
    if(!pTmp1)
    {
        MMLOGI(TAG,"could not find command \n");
        return HI_FAILURE;
    }
    pTmp1+=strlen("X_Support_method: ");
    pTmp2 =strstr(pTmp1, "\r\n");
    memcpy(cmdBuf, pTmp1, pTmp2-pTmp1);
    cmdBuf[9] = 0;
    if(!strcmp(cmdBuf, "RESET"))
    {
        type = SETPARA_COMMAND_RESET;
    }
    else if(!strcmp(cmdBuf, "PAUSE"))
    {
        type = SETPARA_COMMAND_PAUSE;
    }
    else if(!strcmp(cmdBuf, "CHANGE_AUDIO_TRACK"))
    {
        type = SETPARA_COMMAND_CHANGE_AUDIOTRACK;
    }
    else if(!strcmp(cmdBuf, "SEEK"))
    {
        type = SETPARA_COMMAND_SEEK;
    }
    else
    {
        MMLOGI(TAG,"the input command not supported\n");
        return HI_FAILURE;
    }
    *pType = (HI_S32)type;
    strncpy(typeStr, cmdBuf, strlen(cmdBuf));
    return HI_SUCCESS;
}

/*从服务器返回的response中解析Cseq 大小*/
/*parse the cseq num in the response of getpara or setpara*/
HI_S32 Rtsp_Client_ParseCSeq(HI_CHAR* strMSgBuf, void* pCSeq)
{
    const HI_CHAR*    strCSeq = "CSeq";
    const HI_CHAR* strCseq = "Cseq";
    const HI_CHAR* strcseq = "cseq";
    HI_CHAR*    pchPos = HI_NULL;
    HI_CHAR     pWorkTmp[12];

    HI_U32 *pu32CSeq = (HI_U32 *)pCSeq;

    memcpy(pWorkTmp,strCSeq,(HI_U32)strlen(strCSeq) + 1);
    pchPos = strstr(strMSgBuf, pWorkTmp);
    if(HI_NULL == pchPos)
    {
        memcpy(pWorkTmp,strCseq,(HI_U32)strlen(strCseq) + 1);
        pchPos = strstr(strMSgBuf,pWorkTmp);
    }
    if(HI_NULL == pchPos)
    {
        memcpy(pWorkTmp,strcseq,(HI_U32)strlen(strcseq) + 1);
        pchPos = strstr(strMSgBuf,pWorkTmp);
    }

    if(HI_NULL == pchPos)
    {
        MMLOGI(TAG,"RTSP Server Could not Find CSeq!\n");
        MMLOGI(TAG,"cseq err msg: %s\n",strMSgBuf);
        return HI_FAILURE;
    }
    *pu32CSeq = (HI_U32)atoi(pchPos + 5);

    return HI_SUCCESS;
}

/*处理从服务端发来get_parameter请求*/
/*handlr for get_parameter request  from server*/
static S16 RTSP_Client_Server_GetPara_Process(RTSP_CLIENT_S*  pRTSPClient, RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    HI_CHAR pSendMsg[BufferSize];
    HI_CHAR achCSeqTmp[ 20 ];
    HI_U32 u32Cseq = 0;

    Rtsp_Client_ParseCSeq(pRTSPClient->pchReceiveMsg, &u32Cseq);
    sprintf(pSendMsg, "RTSP/1.0 200 OK \r\n");
    sprintf(achCSeqTmp, "CSeq: %d\r\n\r\n", u32Cseq);
    strcat(pSendMsg, achCSeqTmp);
    strcat(pSendMsg,"Content-Type: text/parameters\r\n");
    strcat(pSendMsg,"Content-Length: 141\r\n");
    strcat(pSendMsg,"X_Support_method: RESET, PAUSE, CHANGE_AUDIO_TRACK, SEEK\r\n\r\n");
    MMLOGI(TAG,"str len is %d  str: %s \n",strlen(pSendMsg), pSendMsg);
    HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,pSendMsg,strlen(pSendMsg));

    pRTSPClient->eClentStatus = pRTSPClient->ePrevClentStatus;
    MMLOGI(TAG,"after getpara status: %d\n", pRTSPClient->eClentStatus);
    return SUCCESS;
}

/*处理从服务端发来的set_parameter请求中指定的command RESET,
    执行客户端断开重连操作*/
/*handlr for set_parameter request  from server with command RESET,  execute command
    client reconnect to server*/
S16 RTSP_Client_Handle_Command_Reset(RTSP_CLIENT_S*  pRTSPClient)
{
    S32 s32Ret = SUCCESS;
    if(SUCCESS != RTSP_Client_TeardownRequest(pRTSPClient))
    {
        MMLOGI(TAG,"Teardown Request send error\n");
        return ERR_RTSP_PROCFAILURE;
    }
    pRTSPClient->eClentStatus = RTSP_CLIENT_TEARDOWN;
    s32Ret = pthread_join(pRTSPClient->RTPVideoReadThread, 0);
    if(s32Ret < 0)
    {
        MMLOGI(TAG,"the errorno is %d\n",errno);
    }
    pRTSPClient->RTPVideoReadThread = 0;
    s32Ret = pthread_join(pRTSPClient->RTPAudioReadThread, 0);
     if(s32Ret < 0)
    {
        MMLOGI(TAG,"the errorno is %d\n",errno);
    }
    pRTSPClient->RTPAudioReadThread = 0;
    if(pRTSPClient->u32CliAudioRTPSock > 0)
    {
        close(pRTSPClient->u32CliAudioRTPSock);
        pRTSPClient->u32CliAudioRTPSock = 0;
    }
    if(pRTSPClient->u32CliVideoRTPSock > 0)
    {
        close(pRTSPClient->u32CliVideoRTPSock);
        pRTSPClient->u32CliVideoRTPSock = 0;
    }
    if(pRTSPClient->s32RTSPSockId > 0)
    {
        close(pRTSPClient->s32RTSPSockId);
        pRTSPClient->s32RTSPSockId = 0;
    }
    usleep(200000);
    HI_HIES_Reset_mediaBuf();
     pRTSPClient->eClentStatus = RTSP_CLIENT_INIT;
    memset(pRTSPClient->strSessionAddr,0,32);
    memset(pRTSPClient->sTrack[0],0,sizeof(RTSP_TRACK_S));
    memset(pRTSPClient->sTrack[1],0,sizeof(RTSP_TRACK_S));
    g_IsPause = HI_FALSE;
    g_PauseTime = 0;
    g_ContinueTime = 0;
    pRTSPClient->u32PauseTime = 0;
    pRTSPClient->bUdpAudFlag = HI_FALSE;
    pRTSPClient->bUdpVdoFlag = HI_FALSE;
    MMLOGI(TAG,"RTSP_Client_Handle_Command_Reset\n");
    //usleep(2000000);
    if(SUCCESS != RTSP_Setup_SvrSocket(&pRTSPClient->task,pRTSPClient))
    {
         MMLOGI(TAG,"setup socket error\n");
         return ERR_RTSP_PROCFAILURE;
    }
    MMLOGI(TAG,"RTSP_Setup_SvrSocket ok\n");
    return HI_SUCCESS;
}

/*处理服务端setpara Pause命令，发送pause到服务端，使客户和服务端都暂停*/
/*server setpara request command: Pause handle, client send pause to server to pause the video and audio stream*/
S16 RTSP_Client_Handle_Command_Pause(RTSP_CLIENT_S*  pRTSPClient, RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    if(SUCCESS != RTSP_Client_PauseProcess(pRTSPClient, struAtrributeUtil))
    {
        MMLOGI(TAG,"RTSP_Client_PauseProcess error\n");
        return ERR_RTSP_PROCFAILURE;
    }
    //usleep(2000000);
    if(pRTSPClient->ePrevClentStatus != RTSP_CLIENT_PLAY)
    {
        MMLOGI(TAG,"Pause should happened at play state!!!!!\n");
        return ERR_RTSP_PROCFAILURE;
    }
    else
    {
        g_bPauseFlag = HI_TRUE;
        pRTSPClient->eClentStatus = RTSP_CLIENT_READY;
    }
    return HI_SUCCESS;
}

S16 RTSP_Client_Handle_Command_Change_AudioTrack(RTSP_CLIENT_S*  pRTSPClient)
{
    return HI_SUCCESS;
}

S16 RTSP_Client_Handle_Command_Seek(RTSP_CLIENT_S*  pRTSPClient)
{
    return HI_SUCCESS;
}

/*处理从服务端发来的set_parameter请求*/
/*handlr for set_parameter request  from server*/
static S16 RTSP_Client_Server_SetPara_Process(RTSP_CLIENT_S*  pRTSPClient, RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    HI_CHAR pSendMsg[BufferSize] = {0};
    HI_U32 u32Cseq = 0;
    HI_CHAR achCSeqTmp[20] = {0};
    HI_S32 iCmdType = 0;
    HI_CHAR iCmdStr[10] = {0};
    HI_S16 iRet = HI_SUCCESS;

    Rtsp_Client_ParseCSeq(pRTSPClient->pchReceiveMsg, &u32Cseq);
    iRet = Rtsp_Client_GetCommandType(pRTSPClient->pchReceiveMsg, &iCmdType, iCmdStr);
    if(iRet == HI_FAILURE)
    {
        MMLOGI(TAG,"Rtsp_Client_GetCommandType failed\n");
        return HI_FAILURE;
    }
    sprintf(pSendMsg, "RTSP/1.0 200 OK \r\n");
    sprintf(achCSeqTmp, "CSeq: %d\r\n", pRTSPClient->u32Cseq );
    strcat(pSendMsg, achCSeqTmp);
    strcat(pSendMsg,"Content-Type: text/parameters\r\n");
    strcat(pSendMsg,"Content-Length: 302\r\n");
    strcat(pSendMsg,"X_Support_method: ");
    strcat(pSendMsg,iCmdStr);
    strcat(pSendMsg,"\r\n\r\n");
    MMLOGI(TAG,"send: \n str len is %d  \n str: %s \n",strlen(pSendMsg), pSendMsg);
    HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,pSendMsg,strlen(pSendMsg));
    usleep(50000);
    switch(iCmdType)
    {
        case SETPARA_COMMAND_RESET:
            iRet = RTSP_Client_Handle_Command_Reset(pRTSPClient);
            if(iRet == HI_FAILURE)
            {
                MMLOGI(TAG,"RTSP_Client_Handle_Command_Reset failed\n");
            }
            break;

        case SETPARA_COMMAND_PAUSE:
            iRet = RTSP_Client_Handle_Command_Pause(pRTSPClient, struAtrributeUtil);
            if(iRet == HI_FAILURE)
            {
                MMLOGI(TAG,"RTSP_Client_Handle_Command_Pause failed\n");
            }
            break;

        case SETPARA_COMMAND_CHANGE_AUDIOTRACK:
            iRet = RTSP_Client_Handle_Command_Change_AudioTrack(pRTSPClient);
            if(iRet == HI_FAILURE)
            {
                MMLOGI(TAG,"RTSP_Client_Handle_Command_Change_AudioTrack failed\n");
            }
            break;

        case SETPARA_COMMAND_SEEK:
            iRet = RTSP_Client_Handle_Command_Seek(pRTSPClient);
            if(iRet == HI_FAILURE)
            {
                MMLOGI(TAG,"RTSP_Client_Handle_Command_Seek failed\n");
            }
            break;

        default:
            break;
    }
    MMLOGI(TAG,"RTSP_Client_Server_SetPara_Process  ret: %d \n", iRet);
    return iRet;
}

/*发送SET_PARAMETER 请求，并处理从服务端发来的回应*/
/*handlr for set_parameter, sended by client ,response  from server*/
static S16 RTSP_Client_SetPara_Process(RTSP_CLIENT_S*  pRTSPClient,  RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    RTSP_SetPara_Request(pRTSPClient);
    if(SUCCESS != RTSP_ReponseParse(pRTSPClient->s32RTSPSockId, struAtrributeUtil))
    {
            MMLOGI(TAG,"Decribe Response parse error\n");
            return ERR_RTSP_PROCFAILURE;
    }
    if(pRTSPClient->bReset == HI_TRUE)
    {
        pRTSPClient->bReset = HI_FALSE;
        pRTSPClient->eClentStatus = pRTSPClient->ePrevClentStatus;
    }
    else
    {
        RTSP_Attribute_Clear(struAtrributeUtil);
        pRTSPClient->eClentStatus = RTSP_CLIENT_DESCRIBE;
    }
    return SUCCESS;
}

/*发送OPTIONS 请求，并处理从服务端发来的回应*/
/*handlr for OPTIONS, sended by client ,response  from server*/
static S16 RTSP_Client_Option_Process(RTSP_CLIENT_S*  pRTSPClient, RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    MMLOGI(TAG,"RTSP_Client_Option_Process enter\n");
    if(SUCCESS != RTSP_Option_Request(pRTSPClient))
    {
        MMLOGI(TAG,"RTSP_Option_Request error\n");
        return ERR_RTSP_PROCFAILURE;
    }

    if(SUCCESS != RTSP_ReponseParse(pRTSPClient->s32RTSPSockId, struAtrributeUtil))
    {
            MMLOGI(TAG,"Decribe Response parse error\n");
            return ERR_RTSP_PROCFAILURE;
    }
    //RTSP_Client_TeardownProcess(pRTSPClient);
    RTSP_Attribute_Clear(struAtrributeUtil);
    pRTSPClient->eClentStatus = RTSP_CLIENT_GET_PARAMETER;
    return SUCCESS;
}
/*发送GET_PARAMETER 请求，并处理从服务端发来的回应*/
/*handlr for GET_PARAMETER, sended by client ,response  from server*/
static S16 RTSP_Client_GetPara_Process(RTSP_CLIENT_S*  pRTSPClient,  RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    RTSP_GetPara_Request(pRTSPClient);
    if(SUCCESS != RTSP_ReponseParse(pRTSPClient->s32RTSPSockId, struAtrributeUtil))
    {
            MMLOGI(TAG,"Decribe Response parse error\n");
            return ERR_RTSP_PROCFAILURE;
    }
    HI_S32 i = 0;
    HI_BOOL iNeedSleep = HI_FALSE;
    for(i=0; i< struAtrributeUtil->s32AttbriNum; i++)
    {
        U8* iKey = struAtrributeUtil->struAttribute[i].strKey;
        U8* iVaule = struAtrributeUtil->struAttribute[i].strValue;
        if(!strcmp(struAtrributeUtil->struAttribute[i].strKey, "X_Support_method"))
        {
            /*检测X_Support_method字段的值，如果是WAIT, 需要等待300ms
            , 再重发get para 请求*/
            /*if the value of X_Support_method is wait, then need wait for server's correct state
                and send again get para request*/
            if(HI_NULL != strstr(iVaule, "WAIT/PLAY"))
            {
                MMLOGI(TAG,"client could linkIn to server\n");
                break;
            }
            else if(HI_NULL != strstr(iVaule, "WAIT"))
            {
                MMLOGI(TAG,"client should  wait\n");
                iNeedSleep = HI_TRUE;
            }
            else
            {
                MMLOGI(TAG,"the value is not supported !!!!!\n");
                return ERR_RTSP_PROCFAILURE;
            }
        }
    }
    RTSP_Attribute_Clear(struAtrributeUtil);
    if(iNeedSleep == HI_TRUE)
    {
        usleep(100000);
        pRTSPClient->eClentStatus = RTSP_CLIENT_GET_PARAMETER;
        return SUCCESS;
    }
    else
    {
        pRTSPClient->eClentStatus = RTSP_CLIENT_SET_PARAMETER;
        return SUCCESS;
    }
    //RTSP_Client_TeardownProcess(pRTSPClient);
}
/*发送DESCRIBE 请求，并处理从服务端发来的回应，解析sdp 字段
    获取编码和其他一些必须的信息*/
/*handlr for DESCRIBE, sended by client ,response  from server, parse the sdp from server to
    get the encoder type and other arbitary info*/
S16 RTSP_Client_DescribeProcess(RTSP_CLIENT_S*  pRTSPClient, RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    U16                                         AttributeNum;
    U8*                                          strValue;
    U8*                                          strKey;
    U16                                         eType = 0;
    RTSP_PARSE_UTIL_S*       struAtrribute = struAtrributeUtil;
    S32                                          s32TrackIndex = 0;
    RTSP_TRACK_S*                 sTrackInstance = NULL;
    U8*                                          pstrTemp;
    U8*                                          pstrIndex;

    RTSP_Describe_Request(pRTSPClient);
    if(SUCCESS != RTSP_ReponseParse(pRTSPClient->s32RTSPSockId,struAtrributeUtil))
    {
        MMLOGI(TAG,"Decribe Response parse error\n");
        return ERR_RTSP_PROCFAILURE;
    }
    //RTSP_Client_TeardownProcess(pRTSPClient);
    for(AttributeNum = 0;AttributeNum < struAtrribute->s32AttbriNum;AttributeNum++)
    {
        strKey = struAtrribute->struAttribute[AttributeNum].strKey;
        strValue = struAtrribute->struAttribute[AttributeNum].strValue;
        eType = struAtrribute->struAttribute[AttributeNum].eStype;
        //MMLOGI(TAG,"cur key : %s cur value: %s type : %d \n", strKey, strValue, eType);
        if(NULL != (pstrTemp = strstr(strValue,"npt=")))
        {
            pstrTemp = strchr(pstrTemp,'-');
            pstrTemp += 1;
            MMLOGI(TAG,"the total time is %d\n",atoi(pstrTemp));
            pRTSPClient->u32TotalSec = atoi(pstrTemp) + 1;
        }
        if(SDP_M == eType)
        {
            s32TrackIndex+=1;
            if(s32TrackIndex > 2)
            {
                MMLOGI(TAG,"track size large than 2 !!!!!\n");
                return ERR_RTSP_PROCFAILURE;
            }
            sTrackInstance = pRTSPClient->sTrack[(s32TrackIndex-1)];
            if(NULL != strstr(strValue,"video"))
            {
                MMLOGI(TAG,"cur track video !!!!!\n");
                sTrackInstance->eTrackStype  = TRACK_VIDEO;
            }
            else if(NULL != strstr(strValue,"audio"))
            {
                MMLOGI(TAG,"cur track audio !!!!!\n");
                sTrackInstance->eTrackStype  =  TRACK_AUDIO;
            }
            else
            {
                MMLOGI(TAG,"parse error media stype\n");
                return ERR_RTSP_PROCFAILURE;
            }
        }
        else
        {
            if(NULL != strstr(strKey,"b=AS"))
            {
                sTrackInstance->u32Track_As = atoi(strValue);
            }
            if(NULL != strstr(strKey,"a=rtpmap"))
            {
                strcpy(sTrackInstance->strRTP_MAP,strValue);
            }
            if(NULL!= strstr(strKey,"a=control"))
            {
                if(strchr(strValue,'*'))
                {
                    continue;
                }
                else if(NULL !=(pstrTemp = strstr(strValue,"trackID=")) )
                {
                    sTrackInstance->u32TrackId=atoi(pstrTemp+ strlen("trackID="));
                    pRTSPClient->eClientRequestSort = Darwin_Server;
                    sTrackInstance->eSvrTrackType = Darwin_Server;
                }
                else
                {
                    pRTSPClient->eClientRequestSort = HI_Rtsp_Server;
                    sTrackInstance->eSvrTrackType = HI_Rtsp_Server;
                }
            }
            if(NULL != strstr(strKey,"a=cliprect"))
            {
                sscanf(strValue,"%d,%d,%d,%d",&(sTrackInstance->sPrec.RecX),&(sTrackInstance->sPrec.RecY),
                                                                  &(sTrackInstance->sPrec.Height),&(sTrackInstance->sPrec.Width));
                MMLOGI(TAG,"sdp width: %d height: %d\n",
                    sTrackInstance->sPrec.Width, sTrackInstance->sPrec.Height);
            }
            if(NULL != strstr(strKey,"a=fmtp"))
            {
                sTrackInstance->u32FTMP = atoi(strValue);
                if(NULL != (pstrTemp=strstr(strValue,"profile-level-id=")))
                {
                    pstrTemp += strlen("profile-level-id=");
                    sTrackInstance->u32Profile_Level_id = atoi(pstrTemp);
                }
                if(NULL != (pstrTemp=strstr(strValue,"config=")))
                {
                    pstrTemp += strlen("config=");
                    strcpy(sTrackInstance->strTrack_Config,pstrTemp);
                    sTrackInstance->strTrack_Config[strlen(pstrTemp)+1] = '\0';
                }
                if(NULL != (pstrTemp = strstr(strValue,"sprop-parameter-sets=")))
                {
                     pstrTemp += strlen("sprop-parameter-sets=");
                    if(NULL!=(pstrIndex = strchr(pstrTemp,';')))
                    {
                        strncpy(sTrackInstance->strSPSTags,pstrTemp,pstrIndex - pstrTemp);
                        sTrackInstance->SPSlen = pstrIndex - pstrTemp;
                    }
                    else
                    {
                        strcpy(sTrackInstance->strSPSTags,pstrTemp);
                        sTrackInstance->PPSlen = strlen(pstrTemp);
                    }
                    MMLOGI(TAG,"the sps is %s\n",sTrackInstance->strSPSTags);
                    pRTSPClient->bSdpReady = HI_TRUE;
                }
            }
        }
    }
    pRTSPClient->eClentStatus = RTSP_CLIENT_SETUP;
    RTSP_Attribute_Clear(struAtrribute);
    return SUCCESS;
}
/*解析服务端回应的所有属性集*/
/*parse all the attributes like "key=value" , and store them */
S16 RTSP_ReponseParse(S32 s32SockId,RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    U8          pchReceiveMsg[BufferSize*2];
    U32        ReceiveMsgLen;
    S32         s32RTSPstatus;
    U16             AttributeNum;
    memset(pchReceiveMsg,0,BufferSize*2);
    if(SUCCESS != HI_RTSP_ReceiveMsg(s32SockId, pchReceiveMsg, &ReceiveMsgLen))
    {
        MMLOGI(TAG,"RTSP haven't receive anything\n");
        return ERR_RTSP_PROCFAILURE;
    }
    if(ReceiveMsgLen == 0)
    {
        MMLOGI(TAG,"RTSP ReceiveMsgLen : 0\n");
        return ERR_RTSP_PROCFAILURE;
    }
    pchReceiveMsg[ReceiveMsgLen] = '\0';
    MMLOGI(TAG,"the receive msg is :\n%s\n",pchReceiveMsg);
    MMLOGI(TAG,"the receive msg len is %d\n",ReceiveMsgLen);
    if(SUCCESS != RTSP_Attribute_Parse(pchReceiveMsg,&s32RTSPstatus,struAtrributeUtil))
    {
            MMLOGI(TAG,"Attribute parse error\n");
            return ERR_RTSP_PROCFAILURE;
    }
    if(RTSP_RESPONSE_ERR == s32RTSPstatus || RTSP_RESPONSE_BAD == s32RTSPstatus)
    {
            MMLOGI(TAG,"Server Option return 404\n");
            return ERR_RTSP_PROCFAILURE;
    }
    if(RTSP_RESPONSE_OK == s32RTSPstatus)
        return SUCCESS;
    else
        return s32RTSPstatus;
}

HI_VOID* RTSP_Client_VideoUdpAcross(HI_VOID* arg)
{
    RTSP_CLIENT_S* pRTSPClient = pProtoClient;
    HI_U8 SendInfo[100] = "send udp across";
    HI_U8 irecvbuf[1000] = {0};
    HI_S32 s32Socket;
    struct sockaddr_in addr;
    struct sockaddr_in  srvAddr;
    HI_U32 port = 0;
    HI_U32 revLen = 0;
    HI_U8 i = 0;
    fd_set tReadFd;
    struct timeval tTimeOut;
    HI_BOOL bChangeFlag = HI_FALSE;
    HI_S32 tmp = 1;

    memset(&addr,0,sizeof(struct sockaddr_in));
    memset(&srvAddr,0,sizeof(struct sockaddr_in));
    s32Socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(s32Socket < 0)
    {
        MMLOGI(TAG,"RTSP_Client_VideoUdpAcross socket create  error\n");
        return NULL;
    }
    if(setsockopt(s32Socket, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp)) < 0)
    {
        MMLOGI(TAG,"set socket SO_REUSEADDR opt error\n");
        return -1;
    }
    port = pRTSPClient->u32CliVideoRTPPort - 1;
    addr.sin_addr.s_addr = inet_addr(pRTSPClient->strSvrIPAddr);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    int len=sizeof(struct sockaddr);
    MMLOGI(TAG,"video server rtp ip is %s\n", pRTSPClient->strSvrIPAddr);
    MMLOGI(TAG,"video server rtp port is %d\n", port);
    for( i=0; i < 2; i++ )
    {
        if(sendto(s32Socket, SendInfo, strlen(SendInfo)+1, 0, (struct sockaddr*)&addr,len)<0)
        {
            MMLOGI(TAG,"sendto  error\n");
            return ERR_RTSP_PROCFAILURE;
        }
        MMLOGI(TAG,"video send out %s\n", SendInfo);
        FD_ZERO(&tReadFd);
        FD_SET(s32Socket, &tReadFd);
        tTimeOut.tv_sec = 1;
        tTimeOut.tv_usec = 0;
        if(select(s32Socket+1, &tReadFd, 0, 0, &tTimeOut) > 0)
        {
            if(FD_ISSET(s32Socket, &tReadFd))
            {
                revLen = recvfrom(s32Socket, irecvbuf, 100, 0,  (struct sockaddr *)&srvAddr, &len);
                if (revLen < 0)
                {
                    perror("recvfrom");
                    return HI_NULL;
                }
                MMLOGI(TAG,"video recv: %s  ip: %s port: %d \n",
                    irecvbuf, inet_ntoa(srvAddr.sin_addr), ntohs(srvAddr.sin_port));
                //if(strstr(irecvbuf, "change port"))
                {
                    bChangeFlag = HI_TRUE;
                    break;
                }
            }
        }
    }
    if(bChangeFlag == HI_TRUE)
    {
        MMLOGI(TAG,"video change port  sockfd old : %d new: %d \n",
            pRTSPClient->u32CliVideoRTPSock, s32Socket);
        if(pRTSPClient->u32CliVideoRTPSock > 0)
            close(pRTSPClient->u32CliVideoRTPSock);
        pRTSPClient->u32CliVideoRTPSock = s32Socket;
        pRTSPClient->bUdpVdoFlag = HI_TRUE;
    }
    MMLOGI(TAG,"RTSP_Client_VideoUdpAcross exit  \n");
    return HI_NULL;
}

HI_VOID* RTSP_Client_AudioUdpAcross(HI_VOID* arg)
{
    RTSP_CLIENT_S* pRTSPClient = pProtoClient;
    HI_U8 SendInfo[100] = "send udp across";
    HI_U8 irecvbuf[1000] = {0};
    HI_S32 s32Socket;
    struct sockaddr_in  srvAddr;
    struct sockaddr_in addr;
    HI_U32 port = 0;
    HI_U32 revLen = 0;
    HI_U8 i = 0;
    fd_set tReadFd;
    struct timeval tTimeOut;
    HI_BOOL bChangeFlag = HI_FALSE;
    HI_S32 tmp = 1;

    memset(&addr,0,sizeof(struct sockaddr_in));
    s32Socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(s32Socket < 0)
    {
        MMLOGI(TAG,"RTSP_Client_AudioUdpAcross socket create  error\n");
        return NULL;
    }
    if(setsockopt(s32Socket, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp)) < 0)
    {
        MMLOGI(TAG,"set socket SO_REUSEADDR opt error\n");
        return -1;
    }
    port = pRTSPClient->u32CliAudioRTPPort + 2;
    addr.sin_addr.s_addr = inet_addr(pRTSPClient->strSvrIPAddr);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    int len=sizeof(struct sockaddr);
    MMLOGI(TAG,"audio server rtp ip is %s\n", pRTSPClient->strSvrIPAddr);
    MMLOGI(TAG,"audio server rtp port is %d\n", port);
    for( i=0; i < 2; i++ )
    {
        if(sendto(s32Socket, SendInfo, strlen(SendInfo)+1, 0, (struct sockaddr*)&addr,len)<0)
        {
            MMLOGI(TAG,"sendto  error\n");
            return ERR_RTSP_PROCFAILURE;
        }
        MMLOGI(TAG,"audio send out %s\n", SendInfo);
        FD_ZERO(&tReadFd);
        FD_SET(s32Socket, &tReadFd);
        tTimeOut.tv_sec = 0;
        tTimeOut.tv_usec = 300000;
        if(select(s32Socket+1, &tReadFd, 0, 0, &tTimeOut) > 0)
        {
            if(FD_ISSET(s32Socket, &tReadFd))
            {
                revLen = recvfrom(s32Socket, irecvbuf, 100, 0,  (struct sockaddr *)&srvAddr, &len);
                if (revLen < 0)
                {
                    perror("recvfrom");
                    return HI_NULL;
                }
                MMLOGI(TAG,"audio recv: %s  ip: %s port: %d \n",
                    irecvbuf, inet_ntoa(srvAddr.sin_addr), ntohs(srvAddr.sin_port));
                if(strstr(irecvbuf, "change port"))
                {
                    bChangeFlag = HI_TRUE;
                    break;
                }
            }
        }
    }
    if(bChangeFlag == HI_TRUE)
    {
        MMLOGI(TAG,"audio change port  sockfd old : %d new: %d \n",
            pRTSPClient->u32CliAudioRTPSock, s32Socket);
        if(pRTSPClient->u32CliAudioRTPSock != 0)
            close(pRTSPClient->u32CliAudioRTPSock);
        pRTSPClient->u32CliAudioRTPSock = s32Socket;
        pRTSPClient->bUdpAudFlag = HI_TRUE;
    }
    MMLOGI(TAG,"RTSP_Client_AudioUdpAcross exit  \n");
    return HI_NULL;
}

/*分别发送Audio 和 video SETUP 请求，并分别处理从服务端发来的回应*/
/*handlr for SETUP, sended by client twice for audio and video,response  from server*/
S16 RTSP_Client_SetupProcess(RTSP_CLIENT_S* pRTSPClient,RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    U8                                            u8TrackIndex;
    S32                                           AttributeNum;
    U8*                                          strValue;
    U8*                                          strKey;
    RTSP_TRACK_S*            sTrack;

     for(u8TrackIndex = 0;u8TrackIndex < 2;u8TrackIndex++)
    {
        MMLOGI(TAG,"before setup etype is %d\n",pRTSPClient->sTrack[u8TrackIndex]->eTrackStype);
    }
    if(RTSP_CLIENT_SETUP != pRTSPClient->eClentStatus)
    {
            MMLOGI(TAG,"setup status error\n");
            return ERR_RTSP_PARAMETER;
    }
    for(u8TrackIndex = 0;u8TrackIndex < 2;u8TrackIndex++)
    {
        sTrack = pRTSPClient->sTrack[u8TrackIndex];
        if(sTrack->eTrackStype != TRACK_AUDIO && sTrack->eTrackStype != TRACK_VIDEO)
                continue;
        if(NULL != strstr(sTrack->strRTP_MAP,"H264"))
        {
            sTrack->eMediaSort = H264_MODE;
        }else if(NULL != strstr(sTrack->strRTP_MAP,"AMR"))
        {
            sTrack->eMediaSort = AMR_MODE;
        }else if(NULL != strstr(sTrack->strRTP_MAP,"MP4"))
        {
            sTrack->eMediaSort = MP4_MODE;
        }else
        {
            sTrack->eMediaSort = BUTT_MODE;
        }
        if(SUCCESS != RTSP_SETUP_Request(pRTSPClient,pRTSPClient->sTrack[u8TrackIndex]))
        {
                MMLOGI(TAG,"RTSP Client Request Setup Request Send error\n");
                return ERR_RTSP_PROCFAILURE;
        }
         memset(struAtrributeUtil,0,sizeof(RTSP_PARSE_UTIL_S));
        if(SUCCESS != RTSP_ReponseParse(pRTSPClient->s32RTSPSockId,struAtrributeUtil))
        {
            MMLOGI(TAG,"RTSP Setup Receive and Parse error\n");
            return ERR_RTSP_PROCFAILURE;
        }

        for(AttributeNum = 0;AttributeNum < struAtrributeUtil->s32AttbriNum;AttributeNum++)
        {
            strKey = struAtrributeUtil->struAttribute[AttributeNum].strKey;
            strValue = struAtrributeUtil->struAttribute[AttributeNum].strValue;
            if(NULL != strstr(strKey,"Session"))
            {
                strcpy(pRTSPClient->strSessionAddr,strValue);
            }
            if(NULL != strstr(strKey,"Transport"))
            {
                if(SUCCESS != TransportAssemble(strValue,pRTSPClient->sTrack[u8TrackIndex]))
                {
                    MMLOGI(TAG,"TransportAssemble is error\n");
                    return ERR_RTSP_PROCFAILURE;
                }
            }
          }
        if(pRTSPClient->bUseUdpAcrossFlag)
        {
            if(sTrack->eTrackStype == TRACK_AUDIO)
            {
                HI_S32 ret = SUCCESS;
                HI_S32 thread_id = 0;
                pRTSPClient->u32CliAudioRTPPort = sTrack->u32RTPPort;
                pthread_create(&(thread_id),NULL,RTSP_Client_AudioUdpAcross,NULL);
                if(SUCCESS != ret)
                {
                    MMLOGI(TAG,"create RTSP_Client_AudioUdpAcross  error\n");
                    return ERR_RTSP_PROCFAILURE;
                }
                pthread_detach(thread_id);
            }
            else
            {
                HI_S32 ret = SUCCESS;
                HI_S32 thread_id = 0;
                pRTSPClient->u32CliVideoRTPPort = sTrack->u32RTPPort;
                pthread_create(&(thread_id),NULL,RTSP_Client_VideoUdpAcross,NULL);
                if(SUCCESS != ret)
                {
                    MMLOGI(TAG,"create RTSP_Client_VideoUdpAcross  error\n");
                    return ERR_RTSP_PROCFAILURE;
                }
                pthread_detach(thread_id);
            }
        }
    }
    pRTSPClient->eClentStatus = RTSP_CLIENT_READY;
    RTSP_Attribute_Clear(struAtrributeUtil);
    return SUCCESS;
}
/*发送PLAY 请求，并处理从服务端发来的回应*/
/*handlr for PLAY, sended by client ,response  from server*/
S16 RTSP_Client_PlayProcess(RTSP_CLIENT_S* pRTSPClient,RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    S32                                    s32IndexNum;
    S32                                    s32SockId;
    S32                                    s32RTPSockid;
    S32                                    s32StrRecvLen;
    RTP_HDR_S                               sRTPhdr;
    RTSP_TRACK_S*                           sTrack;
    S32                                        S32Ret;
    U32                                        u32Port;
    U8                                        Ipaddr[20];
    S32 iSleepTime = 0;
    strcpy(Ipaddr,pRTSPClient->strSvrIPAddr);
    if(RTSP_CLIENT_READY == pRTSPClient->eClentStatus)
    {
        if(pRTSPClient->bUseUdpAcrossFlag)
        {
            while(pRTSPClient->bUdpAudFlag != HI_TRUE
                && pRTSPClient->bUdpVdoFlag != HI_TRUE)
            {
                usleep(100000);
                if(iSleepTime > 10)
                {
                    MMLOGI(TAG,"udpAcross do not take action error\n");
                    return HI_FAILURE;
                }
                iSleepTime++;
            }
        }
        if(SUCCESS != RTSP_Play_Request(pRTSPClient))
        {
            MMLOGI(TAG,"Play send request error\n");
            return ERR_RTSP_PROCFAILURE;
        }
        for(s32IndexNum = 0;s32IndexNum < 2;s32IndexNum++)
        {
            if(TRACK_AUDIO == pRTSPClient->sTrack[s32IndexNum]->eTrackStype)
            {
                s32RTPSockid = pRTSPClient->u32CliAudioRTPSock;
            }
            if(TRACK_VIDEO == pRTSPClient->sTrack[s32IndexNum]->eTrackStype)
            {
                s32RTPSockid = pRTSPClient->u32CliVideoRTPSock;
            }
            pRTSPClient->sTrack[s32IndexNum]->u32RTPSock = s32RTPSockid;
        }
        memset(struAtrributeUtil,0,sizeof(RTSP_PARSE_UTIL_S));
        S32Ret= RTSP_ReponseParse(pRTSPClient->s32RTSPSockId,struAtrributeUtil);
        if(SUCCESS != S32Ret)
        {
            MMLOGI(TAG,"RTSP Play Receive and Parse error\n");
            return ERR_RTSP_PROCFAILURE;
        }
        HI_S32 i = 0;
        HI_BOOL iNeedSleep = HI_FALSE;
        for(i=0; i< struAtrributeUtil->s32AttbriNum; i++)
        {
            U8* iKey = struAtrributeUtil->struAttribute[i].strKey;
            U8* iVaule = struAtrributeUtil->struAttribute[i].strValue;
            /*检测X_Support_method字段的值，如果是WAIT, 需要等待300ms
            , 再重发play 请求*/
            /*if the value of X_Support_method is wait, then need wait for server's correct state
                and send again play request*/
            if(!strcmp(struAtrributeUtil->struAttribute[i].strKey, "X_Support_method"))
            {
                if(HI_NULL != strstr(iVaule, "WAIT/PLAY"))
                {
                    MMLOGI(TAG,"client could linkIn to server\n");
                    break;
                }
                else if(HI_NULL != strstr(iVaule, "WAIT"))
                {
                    MMLOGI(TAG,"client should  wait\n");
                    iNeedSleep = HI_TRUE;
                }
                else
                {
                    MMLOGI(TAG,"the value is not supported !!!!!\n");
                    return ERR_RTSP_PROCFAILURE;
                }
            }
        }
        MMLOGI(TAG,"RTSP_Attribute_Clear\n");
        RTSP_Attribute_Clear(struAtrributeUtil);
        if(iNeedSleep == HI_TRUE)
        {
            usleep(100000);
            return SUCCESS;
        }
        else
        {
            g_IsPause = HI_FALSE;
        }
        //if(SUCCESS != RTSP_PLAY_Parse(pRTSPClient,struAtrributeUtil))
        //{
           // MMLOGI(TAG,"RTSP Play Prase error\n");
           // return ERR_RTSP_PROCFAILURE;
        //}

        HI_HIES_set_ResetFlag(HI_TRUE);
        if(RTP_ReadThreadCreate(pRTSPClient) != SUCCESS)
        {
            MMLOGI(TAG,"RTP_ReadThreadCreate error\n");
            return HI_FAILURE;
        }
        MMLOGI(TAG,"RTP_ReadThreadCreate\n");
        pRTSPClient->eClentStatus = RTSP_CLIENT_PLAY;
    }

    if(HI_TRUE == g_IS_Down)
    {
        pRTSPClient->eClentStatus = RTSP_CLIENT_TEARDOWN;
        MMLOGI(TAG,"msg teardown called\n");
        return SUCCESS;
    }
    if(HI_TRUE == g_IsPause)
    {
        if(SUCCESS != RTSP_Client_PauseProcess(pRTSPClient,struAtrributeUtil))
        {
            MMLOGI(TAG,"RTSP Pause error");
            return ERR_RTSP_PROCFAILURE;
        }
        pRTSPClient->eClentStatus = RTSP_CLIENT_PAUSE;
        return SUCCESS;
    }
    if(g_bPauseFlag == HI_TRUE)
    {
        g_bPauseFlag = HI_FALSE;
       // if(SUCCESS != RTSP_Client_PauseProcess(pRTSPClient, struAtrributeUtil))
        {
        //    MMLOGI(TAG,"RTSP_Client_PauseProcess error\n");
        //    return ERR_RTSP_PROCFAILURE;
        }
       // pRTSPClient->eClentStatus = RTSP_CLIENT_READY;
    }
    return SUCCESS;
}

/*读取server发回的信息*/
/*read server network response data with socket connected to server*/
static HI_S32 Rtsp_Client_ReadSock(HI_S32 s32Socket, HI_CHAR* achMsgBuf, HI_S32 s32BufLen)
{
    HI_S32 s32MsgLen;

    s32MsgLen = recv(s32Socket, achMsgBuf, (HI_U32)s32BufLen, MSG_NOSIGNAL);
    if(0 >= s32MsgLen)
    {
        perror("receive error!\n");
        return HI_FAILURE;
    }

    if(s32MsgLen < s32BufLen)
    {
        achMsgBuf[s32MsgLen] = '\0';
    }
    else
    {
        achMsgBuf[s32BufLen-1] = '\0';
    }
    MMLOGI(TAG,"Recv:\n%s\n s32MsgLen : %d\n",achMsgBuf,s32MsgLen);
    return HI_SUCCESS;
}

/*检测是否有网络数据到来*/
/*detect if there are network data coming*/
static HI_BOOL Rtsp_Client_IsRtspSocket_ReadyRead(HI_S32 s32Socket)
{
    fd_set tReadFd;
    struct timeval tTimeOut;

    FD_ZERO(&tReadFd);
    /*lint -e573  -e737 -e778*/
    FD_SET(s32Socket, &tReadFd);
    tTimeOut.tv_sec = 0;
    tTimeOut.tv_usec = 30000;
    if(select(s32Socket+1, &tReadFd, 0, 0, &tTimeOut) > 0)
    {
        /*lint -e573  -e737 -e778*/
        if(FD_ISSET(s32Socket, &tReadFd))
        {
            return HI_TRUE;
        }
    }
    else
    {
        return HI_FALSE;
    }
    return HI_FALSE;
}

/*发送TEARDOWN 请求，终止此rtsp 连接,销毁响应线程资源, socket资源*/
/*send TEARDOWN to server and  destroy related worker thread and socket*/
S16 RTSP_Client_TeardownProcess(RTSP_CLIENT_S* pRTSPClient)
{
    S32 s32IndexNum;
    S32 s32Ret;
    U32 u32SockId;
    U32 u32Port;
    U8 * IPaddr;
    MMLOGI(TAG,"teardown is call\n");
    if(SUCCESS != RTSP_Client_TeardownRequest(pRTSPClient))
    {
        MMLOGI(TAG,"Teardown Request send error\n");
        return ERR_RTSP_PROCFAILURE;
    }
    usleep(100000);
    if(pRTSPClient->u32CliAudioRTPSock > 0)
    {
        close(pRTSPClient->u32CliAudioRTPSock);
        pRTSPClient->u32CliAudioRTPSock = 0;
    }
    if(pRTSPClient->u32CliVideoRTPSock > 0)
    {
        close(pRTSPClient->u32CliVideoRTPSock);
        pRTSPClient->u32CliVideoRTPSock = 0;
    }
    if(pRTSPClient->s32RTSPSockId > 0)
    {
        close(pRTSPClient->s32RTSPSockId);
        pRTSPClient->s32RTSPSockId = 0;
    }
    if(pRTSPClient->RTPVideoReadThread > 0)
    {
        s32Ret = pthread_join(pRTSPClient->RTPVideoReadThread, 0);
        if(s32Ret < 0)
        {
            MMLOGI(TAG,"the errorno is %d\n",errno);
        }
    }
    if(pRTSPClient->RTPAudioReadThread > 0)
    {
        s32Ret = pthread_join(pRTSPClient->RTPAudioReadThread, 0);
         if(s32Ret < 0)
        {
            MMLOGI(TAG,"the errorno is %d\n",errno);
        }
    }
    pRTSPClient->bSdpReady = HI_FALSE;
    return SUCCESS;
}

/*发送SET_PARAMETER请求到服务端，指定要求的音视频编码类型*/
/*send SET_PARAMETER request through socket connected with server, specialize the codec type of audio and video*/
static S16 RTSP_SetPara_Request(RTSP_CLIENT_S*  pRTSPClient)
{
    U8      strRequest[300];
    U8      strCmp[50];
    U32     len;

    memset(strRequest,0,sizeof(strRequest));
    pRTSPClient->u32Cseq++;
    strcat(strRequest,"SET_PARAMETER rtsp://");
    strcat(strRequest,pRTSPClient->strSvrIPAddr);
    strcat(strRequest,"/wfd1.0");
    strcat(strRequest," RTSP/1.0\r\n");
    sprintf(strCmp,"Cseq:%d\r\n",pRTSPClient->u32Cseq);
    strcat(strRequest,strCmp);
    strcat(strRequest,"Accept:application/sdp\r\n");
    strcat(strRequest,"wfd_video_formats: H264\r\n");
    strcat(strRequest,"wfd_audio_codecs: LPCM\r\n");
    strcat(strRequest,"wfd_presentation_URL: rtsp://");
    strcat(strRequest,pRTSPClient->strSvrIPAddr);
    strcat(strRequest,"/wfd1.0/streamid=0 Audio/streamid=1\r\n");
    strcat(strRequest,"\r\n");
    HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,strRequest,strlen(strRequest));
    return SUCCESS;
}

/*发送OPTIONS请求到服务端*/
/*send OPTIONS request through socket connected with server*/
static S16 RTSP_Option_Request(RTSP_CLIENT_S*  pRTSPClient)
{
    U8      strRequest[1024];
    U8      strCmp[20];
    U8      strTmp[200];
    U32     len;
    S32  Ret = HI_SUCCESS;

    memset(strRequest,0,sizeof(strRequest));
    pRTSPClient->u32Cseq++;
    strcat(strRequest,"OPTIONS * ");
    sprintf(strTmp,"rtsp://%s%s",pRTSPClient->strSvrIPAddr, pRTSPClient->strSvrPath);
    strcat(strRequest,strTmp);
    strcat(strRequest," RTSP/1.0\r\n");
    sprintf(strCmp,"Cseq:%d\r\n",pRTSPClient->u32Cseq);
    strcat(strRequest,strCmp);
    strcat(strRequest,"Require: org.wfa.wfd1.0\r\n\r\n");
    Ret = HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,strRequest,strlen(strRequest));
    if(Ret != HI_SUCCESS)
    {
        MMLOGI(TAG,"HI_RTSP_SendMsg error\n");
        return HI_FAILURE;
    }
    return SUCCESS;
}
/*发送GET_PARAMETER请求到服务端, 请求返回服务端支持的编码类型*/
/*send GET_PARAMETER request through socket connected with server, ask server return the codec type supported*/
static S16 RTSP_GetPara_Request(RTSP_CLIENT_S*  pRTSPClient)
{
    U8      strRequest[300];
    U8      strCmp[20];
    U32     len;

    memset(strRequest,0,sizeof(strRequest));
    pRTSPClient->u32Cseq++;
    strcat(strRequest,"GET_PARAMETER rtsp://");
    strcat(strRequest,pRTSPClient->strSvrIPAddr);
    strcat(strRequest,"/wfd1.0");
    strcat(strRequest," RTSP/1.0\r\n");
    sprintf(strCmp,"Cseq:%d\r\n",pRTSPClient->u32Cseq);
    strcat(strRequest,strCmp);
    strcat(strRequest,"Content-Type: text/parameters\r\n");
    strcat(strRequest,"Content-Length: 141\r\n");
    strcat(strRequest,"wfd_video_formats\r\n");
    strcat(strRequest,"wfd_audio_codecs\r\n");
    strcat(strRequest,"X_Support_Command\r\n");
    strcat(strRequest,"X_Command_Parameter\r\n\r\n");
    HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,strRequest,strlen(strRequest));
    return SUCCESS;
}

/*发送DESCRIBE请求到服务端*/
/*send DESCRIBE request through socket connected with server*/
S16 RTSP_Describe_Request(RTSP_CLIENT_S*  pRTSPClient)
{
    U8      strRequest[200];
    U8      strCmp[20];
    U32     len;
 #if 1
    memset(strRequest,0,sizeof(strRequest));
    pRTSPClient->u32Cseq++;
    strcat(strRequest,"DESCRIBE rtsp://");
    strcat(strRequest,pRTSPClient->strSvrIPAddr);
    strcat(strRequest,pRTSPClient->strSvrPath);
    strcat(strRequest," RTSP/1.0\r\n");
    sprintf(strCmp,"Cseq:%d\r\n",pRTSPClient->u32Cseq);
    strcat(strRequest,strCmp);
    strcat(strRequest,"Accept:application/sdp\r\n");
    strcat(strRequest,"User-Agent:VLC media player (LIVE555 Streaming Media v2008.07.24)\r\n\r\n");
    #endif
    MMLOGI(TAG,"str len is %d\n",strlen(strRequest));
    HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,strRequest,strlen(strRequest));
    return SUCCESS;
}

/*发送SETUP请求到服务端, 一次为audio，一次为video*/
/*send SETUP request twice through socket connected with server, for audio and video*/
S16 RTSP_SETUP_Request(RTSP_CLIENT_S*  pRTSPClient,RTSP_TRACK_S* sTrack)
{
    U8              strRequestBuf[500];
    U8              strTmp[100];
    U32             u32RTPPort;

    if(NULL == pRTSPClient || NULL == sTrack)
    {
            MMLOGI(TAG,"setup parameter error\n");
            return ERR_RTSP_PARAMETER;
    }
    if(TRACK_AUDIO != sTrack->eTrackStype && TRACK_VIDEO != sTrack->eTrackStype)
    {
            return SUCCESS;
    }
    pRTSPClient->u32Cseq++;
    memset(strRequestBuf,0,sizeof(strRequestBuf));
    strcat(strRequestBuf,"SETUP rtsp://");
    strcat(strRequestBuf,pRTSPClient->strSvrIPAddr);
    strcat(strRequestBuf,pRTSPClient->strSvrPath);
    if(Darwin_Server == pRTSPClient->eClientRequestSort)
    {
        sprintf(strTmp,"/trackID=%d RTSP/1.0\r\n",sTrack->u32TrackId);
    }else if(HI_Rtsp_Server == pRTSPClient->eClientRequestSort)
    {
        if(TRACK_AUDIO == sTrack->eTrackStype)
            sprintf(strTmp,"/audio RTSP/1.0\r\n");
        else if(TRACK_VIDEO == sTrack->eTrackStype)
            sprintf(strTmp,"/video RTSP/1.0\r\n");
        else
        {
            MMLOGI(TAG,"Media Type error in setup\n");
            return ERR_RTSP_PARAMETER;
        }
    }else
    {
            MMLOGI(TAG,"Media Type error in setup\n");
            return ERR_RTSP_PARAMETER;
    }
    U8        Sockbuf[BufferSize*10];
    MMLOGI(TAG,"eTrackStype is %d\n",sTrack->eTrackStype);
     if(TRACK_AUDIO == sTrack->eTrackStype)
    {
    //here need be change
        u32RTPPort = DefaultAudioRTPPort;
        HI_S32 iSocket= 0;
        iSocket = CreateUDPSock(u32RTPPort,pRTSPClient->strSvrIPAddr,HI_TRUE);
        if(iSocket <= 0)
        {
            MMLOGI(TAG,"audio CreateUDPSock  error\n");
            return ERR_RTSP_PARAMETER;
        }
        pRTSPClient->u32CliAudioRTPSock = iSocket;
        sTrack->u32RTPSock = pRTSPClient->u32CliAudioRTPSock;
        MMLOGI(TAG,"AudioRTP is %d\n",pRTSPClient->u32CliAudioRTPSock);
     }
    else if(TRACK_VIDEO == sTrack->eTrackStype)
    {
        u32RTPPort = DefaultVideoRTPPort;
        HI_S32 iSocket= 0;
        iSocket = CreateUDPSock(u32RTPPort,pRTSPClient->strSvrIPAddr,HI_TRUE);
        if(iSocket <= 0)
        {
            MMLOGI(TAG,"video CreateUDPSock  error\n");
            return ERR_RTSP_PARAMETER;
        }
        pRTSPClient->u32CliVideoRTPSock = iSocket;
        sTrack->u32RTPSock = pRTSPClient->u32CliVideoRTPSock;
        MMLOGI(TAG,"VideoRTP is %d\n",pRTSPClient->u32CliVideoRTPSock);
    }
    strcat(strRequestBuf,strTmp);
    sprintf(strTmp,"CSeq :%d\r\n",pRTSPClient->u32Cseq);
    strcat(strRequestBuf,strTmp);
    if(NULL != pRTSPClient->strSessionAddr)
    {
        sprintf(strTmp,"Session: %s\r\n",pRTSPClient->strSessionAddr);
        strcat(strRequestBuf,strTmp);
    }
    sprintf(strTmp,"Transport: RTP/AVP;unicast;client_port=%d-%d\r\n\r\n",u32RTPPort,u32RTPPort+1);
    strcat(strRequestBuf,strTmp);

    HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,strRequestBuf,strlen(strRequestBuf));
    return SUCCESS;
}

/*发送PLAY请求到服务端*/
/*send PLAY request through socket connected with server*/
S16 RTSP_Play_Request(RTSP_CLIENT_S*  pRTSPClient)
{
     U8      strRequest[200];
     U8      strTemp[50];

     memset(strRequest,0,sizeof(strRequest));
     pRTSPClient->u32Cseq++;
     strcat(strRequest,"PLAY rtsp://");
     strcat(strRequest,pRTSPClient->strSvrIPAddr);
     strcat(strRequest,pRTSPClient->strSvrPath);
     strcat(strRequest," RTSP/1.0\r\n");
     sprintf(strTemp,"Cseq:%d\r\n",pRTSPClient->u32Cseq);
     strcat(strRequest,strTemp);
     sprintf(strTemp,"Session:%s\r\n",pRTSPClient->strSessionAddr);
     strcat(strRequest,strTemp);
     strcat(strRequest,"Range: npt=0.000-\r\n\r\n");
    HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,strRequest,strlen(strRequest));
     return SUCCESS;
}

/*发送PAUSE 请求, 处理回馈, 并结束数据接收线程，*/
/*send pause request , handle response and ends the receiver threads*/
S16 RTSP_Client_PauseProcess(RTSP_CLIENT_S*  pRTSPClient,RTSP_PARSE_UTIL_S* struAtrributeUtil)
{
    U8      strRequest[256];
    U8      strTemp[64];
    S32     s32Ret;

    memset(strRequest,0,sizeof(strRequest));
    pRTSPClient->u32Cseq++;
    g_PauseTime = getNowmTime();
    strcat(strRequest,"PAUSE rtsp://");
    strcat(strRequest,pRTSPClient->strSvrIPAddr);
    strcat(strRequest,pRTSPClient->strSvrPath);
    strcat(strRequest,"/ RTSP/1.0\r\n");
    sprintf(strTemp,"Cseq:%d\r\n",pRTSPClient->u32Cseq);
    strcat(strRequest,strTemp);
    sprintf(strTemp,"Session:%s\r\n\r\n",pRTSPClient->strSessionAddr);
    strcat(strRequest,strTemp);
    HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,strRequest,strlen(strRequest));
    memset(struAtrributeUtil,0,sizeof(RTSP_PARSE_UTIL_S));
    s32Ret = RTSP_ReponseParse(pRTSPClient->s32RTSPSockId,struAtrributeUtil);
    if(SUCCESS != s32Ret)
    {
       MMLOGI(TAG,"RTSP Setup Receive and Parse error\n");
       return ERR_RTSP_PROCFAILURE;
    }
    pRTSPClient->eClentStatus = RTSP_CLIENT_PAUSE;
    usleep(100000);
    s32Ret = pthread_join(pRTSPClient->RTPVideoReadThread, 0);
    if(s32Ret < 0)
    {
        MMLOGI(TAG,"the errorno is %d\n",errno);
    }
    s32Ret = pthread_join(pRTSPClient->RTPAudioReadThread, 0);
     if(s32Ret < 0)
    {
        MMLOGI(TAG,"the errorno is %d\n",errno);
    }
    HI_HIES_Reset_mediaBuf();
    pRTSPClient->RTPVideoReadThread = 0;
    pRTSPClient->RTPAudioReadThread = 0;
    return SUCCESS;
}

/*发送TEARDOWN到服务器，终止此次连接*/
/*send TEARDOWN request to server to ends up this connection */
S16 RTSP_Client_TeardownRequest(RTSP_CLIENT_S*  pRTSPClient)
{
    U8         strRequest[1024];
    U8        strTemp[50];
    //RTP_OPERATEUTIL* struAtrributeUtil =  &(pRTSPClient->);
    memset(strRequest,0,sizeof(strRequest));
    pRTSPClient->u32Cseq++;
    strcat(strRequest,"TEARDOWN rtsp://");
    strcat(strRequest,pRTSPClient->strSvrIPAddr);
    strcat(strRequest,pRTSPClient->strSvrPath);
    strcat(strRequest," RTSP/1.0\r\n");
    sprintf(strTemp,"Cseq:%d\r\n",pRTSPClient->u32Cseq);
    strcat(strRequest,strTemp);
    sprintf(strTemp,"Session:%s\r\n\r\n",pRTSPClient->strSessionAddr);
    strcat(strRequest,strTemp);
    HI_RTSP_SendMsg(pRTSPClient->s32RTSPSockId,strRequest,strlen(strRequest));

    return SUCCESS;
}
static S32  TransportAssemble(U8 *tranString,RTSP_TRACK_S* sTrack)
{
    U8*         pchTran;
    U8*         pchTemp;
    U64        u32SSRC;
    U32     u32Port;

    if(NULL == (pchTran = strstr(tranString,"server_port=")))
    {
        MMLOGI(TAG,"Transport message error\n");
        return ERR_RTSP_PROCFAILURE;
    }
    pchTran += strlen("server_port=");
    pchTemp = strchr(pchTran,'-') + 1;
    u32Port = atoi(pchTemp);
    sTrack->u32RTPPort = u32Port-1;
    if(NULL != (pchTran = strstr(tranString,"ssrc=")))
    {
        sscanf(pchTran,"ssrc=%x",&u32SSRC);
        MMLOGI(TAG,"the ssrc is %x\n",u32SSRC);
    }
    MMLOGI(TAG,"eType is %d\n",sTrack->eTrackStype);
    return SUCCESS;
}
static S16 HI_RTSP_SendMsg( S32 s32Socket, U8* pchMsgBuf, U32 u32MsgLen )
{
    fd_set                    tWriteFd;
    struct timeval            tTimeOut;
    U32                            uSendSize;
    S32                            u32ActSend = 0;

    if( 0 == pchMsgBuf)
    {
        MMLOGI(TAG,"Rtsp Server Send Message Failed!Message Buffer is Null.\n");
        return ERR_RTSP_PROCFAILURE;
    }
    FD_ZERO( &tWriteFd );
    FD_SET( s32Socket, &tWriteFd );
    tTimeOut.tv_sec = 3;
    tTimeOut.tv_usec = 0;
    if(select( s32Socket+ 1, 0, &tWriteFd, 0, &tTimeOut ) <= 0)
    {
        MMLOGI(TAG,"Rtsp Client Send Message Failed!Socket Not Ready.[Sock: %d]\n", s32Socket );
        return ERR_RTSP_PROCFAILURE;
    }
    u32ActSend = send( s32Socket, pchMsgBuf, u32MsgLen, 0 );
    if(u32ActSend < 0)
    {
        MMLOGI(TAG,"send error\n");
        return ERR_RTSP_PROCFAILURE;
    }
    pchMsgBuf[u32ActSend] = '\0';
    MMLOGI(TAG,"Rtsp Client Send Message :\n%s\n,u32ActSend  = %d\n", pchMsgBuf,u32ActSend );
    return SUCCESS;
}

static S16  HI_RTSP_ReceiveMsg( S32 s32Socket, U8* pchMsgBuf, U32* u32MsgLen)
{
        fd_set            tReadFd;
        struct timeval    tTimeOut;
        U32                     u32ActReadLen;
        U8                       pchReadBuf[BufferSize];
        S32                     iRet = HI_SUCCESS;

        FD_ZERO( &tReadFd );
    FD_SET( s32Socket, &tReadFd );
    tTimeOut.tv_sec = 8;
    tTimeOut.tv_usec = 0;
    iRet = select( s32Socket+ 1, &tReadFd,0, 0, &tTimeOut );
    if( 0 > iRet)
    {
        MMLOGI(TAG,"Rtsp Client Read Message Failed!Socket Not Ready.[Sock: %d]\n", s32Socket );
        return ERR_RTSP_PROCFAILURE;
    }
    else if(iRet == 0)
    {
        MMLOGI(TAG,"HI_RTSP_ReceiveMsg timeout after 8s \n", s32Socket );
        return ERR_RTSP_PROCFAILURE;
    }
    u32ActReadLen = recv(s32Socket,pchReadBuf,BufferSize,MSG_NOSIGNAL);
    if(u32ActReadLen <= 0)
    {
        MMLOGI(TAG,"RTSP recv error\n");
        return ERR_RTSP_PROCFAILURE;
    }
    *u32MsgLen = u32ActReadLen;
    if(u32ActReadLen < 0)
    {
        MMLOGI(TAG,"RTSP can't read from Server\n");
        return ERR_RTSP_PROCFAILURE;
    }
    strncpy(pchMsgBuf,pchReadBuf,*u32MsgLen);
    pchMsgBuf[*u32MsgLen] = 0;
    return SUCCESS;
}

static S32 CreateUDPSock( S32 client_port,U8* IPaddr,HI_BOOL bool)
{
    struct sockaddr_in    tClientAddr;
    U32                u32Len;
    U32                bufffersize = BufferSize *50;
    S32                s32RtpSock;
    int                    ret;
    int                    tmp = 1;

    u32Len = sizeof( tClientAddr );
    s32RtpSock = socket( AF_INET, SOCK_DGRAM, 0 );
    tClientAddr.sin_port = htons( client_port );
    tClientAddr.sin_family = AF_INET;
    tClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(HI_TRUE == bool)
    {
        if(ret =setsockopt(s32RtpSock,SOL_SOCKET,SO_RCVBUF,&bufffersize,sizeof(bufffersize)))
        {
            MMLOGI(TAG,"set socket opt error\n");
            return -1;
        }
    }
    if(setsockopt(s32RtpSock, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp)) < 0)
    {
        MMLOGI(TAG,"set socket SO_REUSEADDR opt error\n");
        return -1;
    }
    ret = bind(s32RtpSock,(struct sockaddr *)(&tClientAddr),u32Len);
    if(0 > ret)
    {
        MMLOGI(TAG,"bind error\n");
        return -1;
    }
    return s32RtpSock;
}

static S16    RTSP_Attribute_Clear(RTSP_PARSE_UTIL_S * self)
{
    U32     u32Attribute;

    for(u32Attribute = 0;u32Attribute < self->s32AttbriNum;u32Attribute++)
    {
        memset(self->struAttribute->strKey,0,sizeof(self->struAttribute->strKey));
        memset(self->struAttribute->strValue,0,sizeof(self->struAttribute->strValue));
    }
    self->s32AttbriNum = 0;
    return SUCCESS;
}

static double getTime()
{
    struct timeval pTime;
    gettimeofday(&pTime, NULL);
    return (pTime.tv_sec + (pTime.tv_usec / 1000000.0));
}

/*创建音频，视频数据接收线程*/
/*create threads for audio and video data receiver*/
S16 RTP_ReadThreadCreate(RTSP_CLIENT_S* pRTSPClient)
{
    S32 ret;
    pRTSPClient->u32BeginTime = getNowmTime();
    if(pRTSPClient->RTPVideoReadThread !=0 || pRTSPClient->RTPAudioReadThread != 0)
    {
        MMLOGI(TAG,"video and audio read thread already exist, error happened\n");
        return ERR_RTSP_PROCFAILURE;
    }
    ret = pthread_create(&(pRTSPClient->RTPVideoReadThread),NULL,HI_HIES_get_VideoData,NULL);
    if(SUCCESS != ret)
    {
        MMLOGI(TAG,"read thread error\n");
        return ERR_RTSP_PROCFAILURE;
    }
    //pthread_detach(pRTSPClient->RTPVideoReadThread);
    ret = pthread_create(&(pRTSPClient->RTPAudioReadThread),NULL,HI_HIES_get_AudioData,NULL);
    if(SUCCESS != ret)
    {
        MMLOGI(TAG,"read thread error\n");
        return ERR_RTSP_PROCFAILURE;
    }
    //pthread_detach(pRTSPClient->RTPAudioReadThread);
    return SUCCESS;
}
