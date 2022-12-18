
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <float.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <errno.h>
#include "pthread.h"
#include "libavcodec/avcodec.h"
#include "Hies_proto.h"
#include "rtsp_client.h"
#include "HiMLoger.h"

#define TAG "Hies_proto"

#define true			1
#define false			0
#define HIES_FRAME_HEADLEN ((sizeof(int))+(sizeof(unsigned int))+(sizeof(unsigned int)))
/*视频帧数据结构*/
/*video frame struct*/
typedef struct _FrameInfo
{
    int pts;
    int datalen;
    int payload;
    unsigned char data[MAX_VIDEO_FRAME_SIZE];
    BOOL busy;
}FrameInfo;

/*音频帧数据结构*/
/*audio frame struct*/
typedef struct _AudFrameInfo
{
    int pts;
    int datalen;
    int payload;
    unsigned char data[MAX_AUDIO_FRAME_SIZE];
    BOOL busy;
}AudFrameInfo;

static int mFreeCount = MAX_VIDEO_BUF_NUM;
/*缓存的视频帧，最大个数为MAX_VIDEO_BUF_NUM*/
/*cached video frame , max MAX_VIDEO_BUF_NUM*/
static FrameInfo mframeBuf[MAX_VIDEO_BUF_NUM] = {0};
static pthread_cond_t m_condition;
static pthread_mutex_t m_lock;
static unsigned char* m_VdopktData;


static int mAudFreeCount = MAX_AUDIO_BUF_NUM;
/*缓存的音频帧，最大个数为MAX_AUDIO_BUF_NUM*/
/*cached audio frame , max MAX_AUDIO_BUF_NUM*/
static AudFrameInfo mAudframeBuf[MAX_AUDIO_BUF_NUM] = {0};
static pthread_cond_t m_Audcondition;
static pthread_mutex_t m_Audlock;
static unsigned char* m_AudpktData;


static volatile BOOL m_brunning=false;
static BOOL m_bReset=true;
static BOOL m_bVdoEndFlag = true;
static BOOL m_bAudEndFlag = true;
static BOOL m_bRtspEndFlag = true;
static BOOL m_bBeginReadFlag = false;


static void (*hies_log_callback)(void*, int, const char*, va_list) = NULL;
static int proto_thread_id = 0;

void HI_HIES_log_set_callback(void (*callback)(void*, int, const char*, va_list))
{
    hies_log_callback = callback;
}

double HI_HIES_getTime()
{
    struct timeval pTime;
    gettimeofday(&pTime, NULL);
    return (pTime.tv_sec + (pTime.tv_usec / 1000000.0));
}

/*解析传入的URL, 获取server IP和端口*/
/*parse the url to get ip and port*/
static int  HI_HIES_ParseUrl(char* mUrl, const char* ip,  int ipbufLen, int* port)
{
    char* ipaddr= ip;
    char iport[10] = {0};
    char* pTmp = NULL;
    char* paddr = NULL;
    pTmp = strstr(mUrl, "//");
    if(pTmp == NULL)
        return -1;
    pTmp+=strlen("//");
    if((paddr = strstr(pTmp, ":")) == NULL)
        return -1;

    if(paddr-pTmp+1 > ipbufLen)
    {
        MMLOGI(TAG,"HI_HIES_ParseUrl ip str is too long: %d!!!max: %d\n", (paddr-pTmp), ipbufLen);
        return -1;
    }
    strncpy(ipaddr, pTmp, paddr-pTmp);
    paddr+=1;
    if((pTmp = strstr(paddr, "/")) == NULL)
        return -1;
    strncpy(iport, paddr, pTmp-paddr);

    *port = atoi(iport);
    return 0;
}

/*把接收到的一帧音频，存入buffer中*/
/*put one audio frame received into cache buffer*/
void HI_HIES_put_audio(void* pbuf, int dataLen , int pts, int payload)
{
    if(mAudFreeCount == 0)
    {
        pthread_cond_signal(&m_Audcondition);
        MMLOGI(TAG,"audio buffer is full!!!\n");
        return;
    }
    int i = 0;
    for(i=0;i<MAX_AUDIO_BUF_NUM;i++)
    {
        if(!mAudframeBuf[i].busy)
            break;
    }
    mAudframeBuf[i].datalen= dataLen;
    mAudframeBuf[i].pts= pts;
    mAudframeBuf[i].payload = payload;
    memcpy( mAudframeBuf[i].data, pbuf,  dataLen);

    pthread_mutex_lock(&m_Audlock);
    mAudframeBuf[i].busy = true;
    if(mAudFreeCount > 0)
        mAudFreeCount-=1;
    //MMLOGI(TAG," put audio  frame  len : %d pts: %d  index : %d free: %d\n", dataLen,pts,  i, mAudFreeCount);
    if(mAudFreeCount == MAX_AUDIO_BUF_NUM-1)
    {
        //MMLOGI(TAG,"audio send out signal!!!\n");
        pthread_cond_signal(&m_Audcondition);
    }
    pthread_mutex_unlock(&m_Audlock);
}

/*把接收到的一帧视频，存入buffer中*/
/*put one video frame received into cache buffer*/
void HI_HIES_put_video(void* pbuf, int dataLen , int pts, int payload)
{
    static BOOL bLastIFameLost = false;
    if(mFreeCount == 0)
    {
        pthread_cond_signal(&m_condition);
        MMLOGI(TAG,"video buffer is full!!!,payload: %d\n", payload);
        if(payload == 5)
            bLastIFameLost = true;
        return;
    }
    if(payload == 5)
        bLastIFameLost = false;
    if(!bLastIFameLost)
    {
        int i = 0;
        for(i=0;i<MAX_VIDEO_BUF_NUM;i++)
        {
            if(!mframeBuf[i].busy)
                break;
        }
        mframeBuf[i].datalen= dataLen;
        mframeBuf[i].pts= pts;
        mframeBuf[i].payload = payload;
        memcpy( mframeBuf[i].data, pbuf,  dataLen);
        pthread_mutex_lock(&m_lock);
        mframeBuf[i].busy = true;
        mFreeCount-=1;
        //MMLOGI(TAG," put video frame  len : %d pts: %d  index : %d free: %d\n", dataLen,pts,  i, mFreeCount);
        if(mFreeCount == MAX_VIDEO_BUF_NUM-1)
            pthread_cond_signal(&m_condition);
        pthread_mutex_unlock(&m_lock);
    }
    else
    {
        MMLOGI(TAG,"lost this  video frame\n");
    }
}

void HI_HIES_set_ResetFlag(BOOL bFlag)
{
    m_bReset = bFlag;
}

void HI_HIES_put_frame(void* pbuf, int dataLen , int pts, int payload)
{
    if(!m_bBeginReadFlag)
        return;
    if(payload == 10)
    {
        HI_HIES_put_audio(pbuf, dataLen, pts, payload);
    }
    else
    {
        /*如果发生过protocol 重置, 需保证第一帧视频要是I 帧*/
        /*if protocol reset happened, need to ensure the frist video frame to be I frame*/
        if(m_bReset)
        {
            if(payload != 5)
                return;
            m_bReset = false;
            MMLOGI(TAG,"first put video buffer is key frame!!!\n");
        }
        HI_HIES_put_video(pbuf, dataLen, pts, payload);
    }
}

void HI_HIES_Reset_mediaBuf(void)
{
    MMLOGI(TAG,"HI_HIES_Reset_mediaBuf begin\n");
    pthread_mutex_lock(&m_lock);
    mFreeCount = MAX_VIDEO_BUF_NUM;
    memset((void*)&mframeBuf[0], 0x00, MAX_VIDEO_BUF_NUM*sizeof(FrameInfo));
    pthread_mutex_unlock(&m_lock);

    pthread_mutex_lock(&m_Audlock);
    mAudFreeCount = MAX_AUDIO_BUF_NUM;
    memset((void*)&mAudframeBuf[0], 0x00, MAX_AUDIO_BUF_NUM*sizeof(AudFrameInfo));
    pthread_mutex_unlock(&m_Audlock);
    MMLOGI(TAG,"HI_HIES_Reset_mediaBuf end\n");
}

/*udp 网络包解包，当前udp包头结构为:
    顺序数(2字节), 负载类型(1 字节),  开始结束标示(1 byte), 后边跟着帧数据*/
/* demux the udp package, the current udp packge header struct:
    seqnum(2 byte), payloadtype(1 byte),  begin or end marker(1 byte), followed with frame data*/
void HI_HIES_Demux_Package(char* inBuf, int bufLen, char** data,  int* seqNum, int* marker, int* pt,  int* dataLen)
{
    char* pbuf = inBuf;
    int seq = 0;
    memcpy(&seq, pbuf, 2);
    *seqNum = seq;
    *pt = pbuf[2];
    *marker = pbuf[3];
    *data = &pbuf[4];
    *dataLen = bufLen-4;
}

void HI_HIES_Put_VideoFrame(char* pBuf, int lastMarker, int dataLen, int ptype)
{
    int i_ptype = 0;
    unsigned int i_pts = 0;
    unsigned int  i_dataLen = 0;
    char* pdata = pBuf;
    static BOOL i_bDropFlag = false;

    if(lastMarker == 0)
    {
        MMLOGI(TAG,"video last pack may lost len: %d \n", dataLen);
    }
    memcpy(&i_ptype, pdata, sizeof(int));
    pdata+=sizeof(int);
    memcpy(&i_pts, pdata,  sizeof(unsigned int));
    pdata+=sizeof(unsigned int);
    memcpy(&i_dataLen, pdata, sizeof(unsigned int));
    pdata+=sizeof(unsigned int);
    //MMLOGI(TAG,"video rev pt: %d, pts: %d, len: %d\n", i_ptype, i_pts, i_dataLen);
    /*如果payload type 不在视频帧范围内，可能是帧头丢失，丢弃该帧*/
    /*if the frame payload type is not one of 1, 5, 7, 8. then maybe frame header are lost*/
    if(i_ptype > 10 || i_ptype < 0)
    {
        MMLOGI(TAG,"video invalid data, maybe first package  lost pt: %d\n", ptype);
        memset(pBuf, 0x00, MAX_VIDEO_FRAME_SIZE);
        /*如果一帧头数据丢掉了，并且该帧是I 帧的话，丢帧直到下个
            完整的I帧到来*/
        /* if I frame data at begining are lost,  then lost all coming frames until the next frame is completed I frame*/
        if(ptype == 5)
            i_bDropFlag = true;
        return;
    }
    if(i_ptype !=  ptype)
    {
        MMLOGI(TAG,"payload type is not correct pack pt: %d, %d \n", i_ptype, ptype);
    }
    if(i_dataLen > MAX_VIDEO_FRAME_SIZE)
    {
        MMLOGI(TAG,"video buf size is not big enough\n");
        return;
    }
    if(i_dataLen + HIES_FRAME_HEADLEN != dataLen)
    {
        MMLOGI(TAG,"may lost some pack, recv len: %d \n", dataLen);
        i_dataLen = dataLen - HIES_FRAME_HEADLEN;
    }
    if(ptype == 5)
        i_bDropFlag = false;
    if(!i_bDropFlag)
        HI_HIES_put_frame(pdata, i_dataLen, i_pts, i_ptype);
}

void HI_HIES_Put_AudioFrame(char* pBuf, int lastMarker, int dataLen)
{
    int i_ptype = 0;
    unsigned int i_pts = 0;
    unsigned int  i_dataLen = 0;
    char* pdata = pBuf;

    if(lastMarker)
    {
        memcpy(&i_ptype, pdata, sizeof(int));
        pdata+=sizeof(int);
        memcpy(&i_pts, pdata,  sizeof(unsigned int));
        pdata+=sizeof(unsigned int);
        memcpy(&i_dataLen, pdata, sizeof(unsigned int));
        pdata+=sizeof(unsigned int);
        //MMLOGI(TAG,"audio rev pt: %d, pts: %d, len: %d\n", i_ptype, i_pts, i_dataLen);
        /*如果payload type 不在音频帧范围内，可能是帧头丢失，丢弃该帧*/
        /*if the frame payload type is not 10. then maybe frame header are lost*/
        if(i_ptype != 10)
        {
            MMLOGI(TAG,"audio invalid data, maybe some package are lost \n");
            memset(pBuf, 0x00, MAX_AUDIO_FRAME_SIZE);
            return;
        }
        if(i_dataLen > MAX_AUDIO_FRAME_SIZE)
        {
            MMLOGI(TAG,"audio buf size is not big enough\n");
            return;
        }
        if(i_dataLen + HIES_FRAME_HEADLEN != dataLen)
        {
            MMLOGI(TAG,"audio may lost some pack, recv len: %d \n", dataLen);
            return;
        }
        HI_HIES_put_frame(pdata, i_dataLen, i_pts, i_ptype);
    }
    else
    {
        MMLOGI(TAG,"audio last pack may lost\n");
    }

}

void HI_HIES_VideoError_Handler(RTSP_CLIENT_S* pClient)
{
    pClient->eClentStatus = RTSP_CLIENT_TEARDOWN;
    m_brunning = false;
    pthread_cond_signal(&m_condition);
}
/* 视频udp数据接受线程，通过对udp包起始包标示，结束包标示，和
    包Sequence num 来区分视频帧，并送入视频buffer, 等待被解码显示*/
void* HI_HIES_get_VideoData(void* arg)
{
    RTSP_CLIENT_S* pClient = NULL;
    struct sockaddr_in  srvAddr;
    char irecvbuf[2048] = {0};
    int revLen = 0;
    BOOL i_bHead = true;
    unsigned char* ibufer = NULL;
    unsigned char* i_Ptr = NULL;
    char* pdata = NULL;
    int seqNum = 0;
    int i_ptype = 0;
    int i_Lastptype = 0;
    int marker = 0;
    int lastMarker = 0;
    int dataLen = 0;
    int packNum = 0;
    int len = sizeof(struct sockaddr_in);
    fd_set read_fds;
    struct timeval time_val;
    int ret = 0;
    double i_sucessTime = 0;
    int i_LastSeqNum = 0;
    int packLen = 0;

    m_bVdoEndFlag = false;
    pClient = RTSP_Client_Get_CurSessionPtr();
    time_val.tv_sec  = 2;
    time_val.tv_usec = 0;
    int i_sock_fd = pClient->u32CliVideoRTPSock;
    int revBufSize = 65536;
    if (setsockopt(i_sock_fd, SOL_SOCKET, SO_RCVBUF, &revBufSize, sizeof(revBufSize)) < 0)
    {
        MMLOGI(TAG,"video setsockopt SO_RCVBUF failed\n");
        HI_HIES_VideoError_Handler(pClient);
        goto Ret;
    }
    ibufer = av_mallocz(MAX_VIDEO_FRAME_SIZE);
    if(!ibufer)
    {
        MMLOGI(TAG,"malloc failed\n");
        HI_HIES_VideoError_Handler(pClient);
        goto Ret;
    }
    i_Ptr = ibufer;
    i_sucessTime = HI_HIES_getTime();
    while(pClient->eClentStatus != RTSP_CLIENT_TEARDOWN
                && pClient->eClentStatus != RTSP_CLIENT_PAUSE
                && pClient->eClentStatus != RTSP_CLIENT_INIT)
    {
        FD_ZERO(&read_fds);
        /*lint -e573  -e737 -e778*/
        FD_SET(i_sock_fd, &read_fds);
        ret = select(i_sock_fd+1,&read_fds,NULL,NULL,&time_val);
        if(ret <= 0)
        {
            if(HI_HIES_getTime() -i_sucessTime > 10)
            {
                MMLOGI(TAG,"video recv time out  !!!\n");
                HI_HIES_VideoError_Handler(pClient);
                break;
            }
            continue;
        }
        /*lint -e573  -e737 -e778*/
        if(FD_ISSET(i_sock_fd,&read_fds))
        {
            revLen = recvfrom(i_sock_fd, irecvbuf, 2048, 0,  (struct sockaddr *)&srvAddr, &len);
            //MMLOGI(TAG,"vdo rev len: %d ,  \n", revLen);
            if(revLen < 0)
            {
                MMLOGI(TAG, "video recvfrom error sock: %d  errno: %d\n", i_sock_fd, errno);
                HI_HIES_VideoError_Handler(pClient);
                break;
            }
            if(revLen == 0)
                continue;
            i_sucessTime = HI_HIES_getTime();
            HI_HIES_Demux_Package(irecvbuf, revLen, &pdata, &seqNum, &marker, &i_ptype, &dataLen);
            //MMLOGI(TAG,"video rev len: %d , marker: %d  seq: %d  pt: %d \n", revLen, marker, seqNum, i_ptype);
            if(i_LastSeqNum ==0)
            {
                i_LastSeqNum = seqNum;
                i_Lastptype = i_ptype;
            }
            /*如果下一包的seq num比上包小，则丢弃*/
            /*if the seq num smaller than prev, lost it*/
            if(seqNum < i_LastSeqNum)
            {
                /*视频包的起始Seq 是1234，最大包Seq为65534，当到最大Seq时
                    需要环回计数，不能丢弃*/
                /*the seq for video package range from 1234 to 65534, when reach 65534, need to loop to begin*/
                if(seqNum == 1234 && i_LastSeqNum == 65534)
                {
                    MMLOGI(TAG, "video seq num loop happened \n");
                }
                else
                {
                    packNum = 0;
                    i_Ptr = ibufer;
                    memset(ibufer, 0x00, MAX_VIDEO_FRAME_SIZE);
                    continue;
                }
            }

            if(packNum == 0)
            {
                i_Lastptype = i_ptype;
                i_LastSeqNum = seqNum;
                if(marker == 0)
                {
                    if(packLen > MAX_VIDEO_FRAME_SIZE)
                    {
                        MMLOGI(TAG, "error happened, video packet len: %d  is large than max length \n", packLen);
                        HI_HIES_VideoError_Handler(pClient);
                        break;
                    }
                    memcpy(i_Ptr, pdata, dataLen);
                    i_Ptr+=dataLen;
                    packLen+=dataLen;
                    packNum+=1;
                }
                else if(marker == 1)
                {
                    memcpy(i_Ptr, pdata, dataLen);
                    HI_HIES_Put_VideoFrame(ibufer, marker, dataLen, i_Lastptype);
                    packLen = 0;
                    i_Ptr = ibufer;
                    packNum = 0;
                    lastMarker = 0;
                }
            }
            else
            {
                /*当发生Seq num切换时，认为一帧接收完毕*/
                /*when the seq num changed, one frame should receive completely*/
                if(seqNum != i_LastSeqNum)
                {
                    //MMLOGI(TAG,"already receive one frame , pack count: %d last marker: %d \n", packNum, lastMarker);
                    HI_HIES_Put_VideoFrame(ibufer, lastMarker, (i_Ptr-ibufer), i_Lastptype);
                    packNum = 0;
                    packLen = 0;
                    i_Ptr = ibufer;
                    i_LastSeqNum = seqNum;
                    i_Lastptype = i_ptype;
                    if(marker == 0)
                    {
                        if(packLen > MAX_VIDEO_FRAME_SIZE)
                        {
                            MMLOGI(TAG, "error happened, video packet len: %d  is large than max length \n", packLen);
                            HI_HIES_VideoError_Handler(pClient);
                            break;
                        }
                        memcpy(i_Ptr, pdata, dataLen);
                        i_Ptr+=dataLen;
                        packLen+=dataLen;
                        packNum+=1;
                    }
                    else if(marker == 1)
                    {
                        memcpy(i_Ptr, pdata, dataLen);
                        HI_HIES_Put_VideoFrame(ibufer, marker, dataLen, i_Lastptype);
                        packNum = 0;
                        lastMarker = 0;
                    }
                }
                else
                {
                    if(packLen > MAX_VIDEO_FRAME_SIZE)
                    {
                        MMLOGI(TAG, "error happened, video packet len: %d  is large than max length \n", packLen);
                        HI_HIES_VideoError_Handler(pClient);
                        break;
                    }
                    memcpy(i_Ptr, pdata, dataLen);
                    i_Ptr+=dataLen;
                    packLen+=dataLen;
                    packNum+=1;
                }
            }
            lastMarker = marker;
            //MMLOGI(TAG,"vdo recv   success\n");
        }
    }
Ret:
    if(ibufer)
        av_free(ibufer);
    m_bVdoEndFlag = true;
    MMLOGI(TAG,"HI_HIES_get_VideoData  exit \n");
    return 0;
}
void HI_HIES_AudioError_Handler(RTSP_CLIENT_S* pClient)
{
    m_brunning = false;
    pClient->eClentStatus = RTSP_CLIENT_TEARDOWN;
    pthread_cond_signal(&m_Audcondition);
}

/* 音频udp数据接受线程，通过对udp包起始包标示，结束包标示，和
    包Sequence num 来区分音频帧，并送入音频buffer, 等待被解码播放*/
void* HI_HIES_get_AudioData(void* arg)
{
    RTSP_CLIENT_S* pClient = NULL;
    struct sockaddr_in  srvAddr;
    char irecvbuf[2048] = {0};
    int revLen = 0;
    BOOL i_bHead = true;
    unsigned char* ibufer = NULL;
    unsigned char* i_Ptr = NULL;
    char* pdata = NULL;
    int seqNum = 0;
    int i_ptype = 0;
    int marker = 0;
    int lastMarker = 0;
    int dataLen = 0;
    int packNum = 0;
    int i_LastSeqNum = 0;
    int len = sizeof(struct sockaddr_in);
    fd_set read_fds;
    struct timeval time_val;
    int ret = 0;
    double i_sucessTime = 0;

    pClient = RTSP_Client_Get_CurSessionPtr();
    time_val.tv_sec  = 2;
    time_val.tv_usec = 0;
    int i_sock_fd = pClient->u32CliAudioRTPSock;
    int revBufSize = 65536;
    if (setsockopt(i_sock_fd, SOL_SOCKET, SO_RCVBUF, &revBufSize, sizeof(revBufSize)) < 0)
    {
        MMLOGI(TAG,"audio setsockopt SO_RCVBUF failed\n");
        HI_HIES_AudioError_Handler(pClient);
        goto Ret;
    }
    MMLOGI(TAG, "session ptr: 0x%08x ,sockfd: %d \n", pClient,  i_sock_fd);
    ibufer = av_mallocz(MAX_AUDIO_FRAME_SIZE);
    if(!ibufer)
    {
        MMLOGI(TAG,"malloc failed\n");
        HI_HIES_AudioError_Handler(pClient);
        goto Ret;
    }
    i_Ptr = ibufer;
    i_sucessTime = HI_HIES_getTime();
    while(pClient->eClentStatus != RTSP_CLIENT_TEARDOWN
            && pClient->eClentStatus != RTSP_CLIENT_PAUSE
            && pClient->eClentStatus != RTSP_CLIENT_INIT)
    {
        FD_ZERO(&read_fds);
        /*lint -e573  -e737 -e778*/
        FD_SET(i_sock_fd, &read_fds);
        ret = select(i_sock_fd+1,&read_fds,NULL,NULL,&time_val);
        if(ret <= 0)
        {
            if(HI_HIES_getTime() -i_sucessTime > 10)
            {
                MMLOGI(TAG,"audio recv time out  !!!\n");
                HI_HIES_AudioError_Handler(pClient);
                break;
            }
            continue;
        }
        /*lint -e573  -e737 -e778*/
        if(FD_ISSET(i_sock_fd,&read_fds))
        {
            revLen = recvfrom(i_sock_fd, irecvbuf, 2048, 0,  (struct sockaddr *)&srvAddr, &len);
            //MMLOGI(TAG,"aud rev len: %d ,  \n", revLen);
            if(revLen < 0)
            {
                MMLOGI(TAG, "recvfrom error socket: %d errno: %d\n", i_sock_fd, errno);
                HI_HIES_AudioError_Handler(pClient);
                break;
            }
            if(revLen == 0)
                continue;
            i_sucessTime = HI_HIES_getTime();
            HI_HIES_Demux_Package(irecvbuf, revLen, &pdata, &seqNum, &marker, &i_ptype, &dataLen);
            //MMLOGI(TAG,"audio rev len: %d , marker: %d  seq: %d pt: %d \n", revLen, marker, seqNum, i_ptype);
            if(i_LastSeqNum ==0)
            {
                i_LastSeqNum = seqNum;
            }
            /*如果下一包的seq num比上包小，则丢弃*/
            /*if the seq num smaller than prev, lost it*/
            if(seqNum < i_LastSeqNum)
            {
                /*音频包的起始Seq 是1235，最大包Seq为65534，当到最大Seq时
                    需要环回计数，不能丢弃*/
                /*the seq for audio package range from 1235 to 65534, when reach 65534, need to loop to begin*/
                if(seqNum == 1235 && i_LastSeqNum == 65534)
                {
                    MMLOGI(TAG, "audio seq num loop happened \n");
                }
                else
                {
                    packNum = 0;
                    i_Ptr = ibufer;
                    memset(ibufer, 0x00, MAX_AUDIO_FRAME_SIZE);
                    continue;
                }
            }

            if(packNum == 0)
            {
                i_LastSeqNum = seqNum;
                if(marker == 0)
                {
                    memcpy(i_Ptr, pdata, dataLen);
                    i_Ptr+=dataLen;
                    packNum+=1;
                }
                else if(marker == 1)
                {
                    memcpy(i_Ptr, pdata, dataLen);
                    HI_HIES_Put_AudioFrame(ibufer, marker, dataLen);
                    i_Ptr = ibufer;
                    packNum = 0;
                    lastMarker = 0;
                    if(i_LastSeqNum == 65535)
                        i_LastSeqNum = 0;
                }
            }
            else
            {
                if(seqNum != i_LastSeqNum)
                {
                    //MMLOGI(TAG,"already receive one audio  frame , pack count: %d last marker: %d \n", packNum, lastMarker);
                    HI_HIES_Put_AudioFrame(ibufer, lastMarker, (i_Ptr-ibufer));
                    packNum = 0;
                    i_Ptr = ibufer;
                    i_LastSeqNum = seqNum;
                    if(marker == 0)
                    {
                        memcpy(i_Ptr, pdata, dataLen);
                        i_Ptr+=dataLen;
                        packNum+=1;
                    }
                    else if(marker == 1)
                    {
                        memcpy(i_Ptr, pdata, dataLen);
                        HI_HIES_Put_AudioFrame(ibufer, marker, dataLen);
                        packNum = 0;
                        lastMarker = 0;
                    }
                }
                else
                {
                    if(i_Ptr - ibufer > MAX_AUDIO_FRAME_SIZE)
                    {
                        MMLOGI(TAG,"error happened, audio dataLen :%d large than max \n", i_Ptr - ibufer);
                        HI_HIES_AudioError_Handler(pClient);
                        break;
                    }
                    memcpy(i_Ptr, pdata, dataLen);
                    i_Ptr+=dataLen;
                    packNum+=1;
                }
            }
            lastMarker = marker;
            //MMLOGI(TAG,"aud recv  handle success\n");
        }
    }
Ret:
    if(ibufer)
        av_free(ibufer);
    m_bAudEndFlag = true;
    MMLOGI(TAG,"HI_HIES_get_AudioData  exit\n");
    return 0;
}

static int  HI_HIES_handle_Response(int isock)
{
    char revBuf[2048] = {0};

    recv(isock, revBuf, 2048, 0);

    MMLOGI(TAG, "rev http response: %s \n", revBuf);
    if(strstr(revBuf, "HTTP/1.1 200 OK"))
    {
        return 0;
    }

}

/*启动rtsp 协议运行*/
/*start the rtsp protocol session*/
 HI_VOID* HI_HIES_Protocol_Process(HI_VOID* arg)
{
    S16 Ret = HI_SUCCESS;
    MMLOGI(TAG, "HI_HIES_Protocol_Process \n");
    m_bRtspEndFlag = false;
    Ret = RTSP_Client_Process();
    m_brunning = false;
    pthread_cond_signal(&m_condition);
    pthread_cond_signal(&m_Audcondition);
    m_bRtspEndFlag = true;
    return NULL;
}

 int  HI_HIES_Connect(char* mUrl)
{
    int sock_fd = 0;
    char ipaddr[MAX_IP_STR_LEN] = {0};
    char sendBuf[1024] = {0};
    char* pbuf = (char*)sendBuf;
    int iport = 0;
    int ret = 0;
    RTSP_Msg_Task task = {0};

    MMLOGI(TAG, "input url: %s \n", mUrl);
    if(HI_HIES_ParseUrl(mUrl, ipaddr, MAX_IP_STR_LEN, &iport) == -1)
    {
        MMLOGI(TAG, "HI_HIES_ParseUrl \n");
        return -1;
    }
    /*port:
    1~~1023: well know port, better do  not use to avoid conflict
    1024~~49151: register port, prefer to be used as service port
    49152~~65535: dynamic or private port, for private use*/
    if(iport <=0 || (iport > 0 && iport < 1024))
    {
        MMLOGI(TAG, "network port: %d should be in range 1024~~65535\n", iport);
        return -1;
    }
    MMLOGI(TAG, "IP: %s , port: %d \n", ipaddr, iport);
    strncpy(task.strURL, mUrl, MAX_URL_STR_LEN);
    strncpy(task.strIP, ipaddr, MAX_IP_STR_LEN);
    task.port = iport;
    m_brunning = true;
    ret = RTSP_Client_EnvInit(&task);
    if(ret <0)
    {
        MMLOGI(TAG, "RTSP_Client_EnvInit error \n");
        return -1;
    }
    ret = pthread_create(&proto_thread_id, 0, HI_HIES_Protocol_Process, NULL);
    if(ret <0)
    {
        MMLOGI(TAG, "pthread_create error \n");
        return -1;
    }
    //pthread_detach(ithread_id);
    if(m_brunning == false)
    {
        MMLOGI(TAG, "rtsp enviroment setup  error \n");
        return -1;
    }
    MMLOGI(TAG, "begin recv\n");
    return 0;
}

int HI_HIES_Init_Proto(void)
{
    pthread_cond_init(&m_condition, NULL);
    pthread_mutex_init(&m_lock, NULL);

    m_VdopktData = (char*)av_mallocz(MAX_VIDEO_FRAME_SIZE);
    if (!m_VdopktData)
    {
        MMLOGI(TAG, "m_VdopktData malloc error \n");
        return -1;
    }
    memset((void*)&mframeBuf[0], 0x00, MAX_VIDEO_BUF_NUM*sizeof(FrameInfo));

    pthread_cond_init(&m_Audcondition, NULL);
    pthread_mutex_init(&m_Audlock, NULL);

    m_AudpktData = (char*)av_mallocz(MAX_AUDIO_FRAME_SIZE);
    if (!m_AudpktData)
    {
        MMLOGI(TAG, "m_AudpktData malloc error \n");
        return -1;
    }
    m_bBeginReadFlag = false;
    memset((void*)&mAudframeBuf[0], 0x00, MAX_AUDIO_BUF_NUM*sizeof(AudFrameInfo));
    return 0;
}


/*去初始化协议，停掉rtsp session，关掉数据接收线程*/
/*deinit protocol, stop rtsp session, close the data receiver*/
int HI_HIES_DeInit_Proto(void)
{
    char sendBuf[1024] = {0};
    RTSP_Client_MsgTeardown();
    MMLOGI(TAG, "send  teardown to server \n");
    if(pthread_join(proto_thread_id, 0) < 0)
    {
        MMLOGI(TAG, "pthread_join proto_thread_id failed\n");
    }
    //usleep(100000);
    m_brunning = false;
    HI_HIES_Reset_mediaBuf();
    int i = 0;
    for(i=0; i < 3; i++)
    {
        pthread_cond_signal(&m_condition);
        pthread_cond_signal(&m_Audcondition);
    }
    //usleep(100000);
    pthread_cond_destroy(&m_condition);
    pthread_mutex_destroy(&m_lock);
    MMLOGI(TAG, "m_VdopktData: 0x%08x \n", m_VdopktData);
    if(m_VdopktData)
    {
        av_free(m_VdopktData);
        m_VdopktData = NULL;
    }
    MMLOGI(TAG, "before destroy m_Audcondition\n");
    pthread_cond_destroy(&m_Audcondition);
    pthread_mutex_destroy(&m_Audlock);
    MMLOGI(TAG, "m_AudpktData: 0x%08x \n", m_AudpktData);
    if(m_AudpktData)
    {
        av_free(m_AudpktData);
        m_AudpktData = NULL;
    }
    HI_S32 iSleepTime = 0;
    while(!m_bVdoEndFlag || !m_bAudEndFlag || !m_bRtspEndFlag)
    {
        MMLOGI(TAG, "audio and video thread have not cease\n");
        usleep(200000);
        if(iSleepTime > 20)
        {
            break;
        }
        iSleepTime += 1;
    }
    m_bBeginReadFlag = false;
    MMLOGI(TAG, "HI_HIES_DeInit_Proto  success out \n");
    return 0;
}

/*从audio buffer 中读取音频帧，如果当前没有数据可读，会
    wait在这里，直到等到数据ready的通知*/
/*get audio frame from audio buffer, if there no data, we'll wait here until
    receive the signal of ready to read*/
int HI_HIES_read_audio_stream(void* ptr, int* dataSize, int64_t* pts)
{
    int ret = 0;
    if(mAudFreeCount == MAX_AUDIO_BUF_NUM)
    {
        //MMLOGI(TAG,"HI_HIES_read_audio_stream wait \n");
        pthread_mutex_lock(&m_Audlock);
        pthread_cond_wait(&m_Audcondition, &m_Audlock);
        //MMLOGI(TAG,"audio recv  signal!!!\n");
    }
    else
    {
        pthread_mutex_lock(&m_Audlock);
    }
    if(!m_brunning)
    {
        MMLOGI(TAG, "m_brunning is false \n");
        pthread_mutex_unlock(&m_Audlock);
        return -1;
    }
    int iminPts = 0;
    int iminIdx = 0;
    int i = 0;
    for(i=0; i< MAX_AUDIO_BUF_NUM; i++)
    {
        if(mAudframeBuf[i].busy
            && (iminPts == 0 ||mAudframeBuf[i].pts < iminPts))
        {
            iminPts = mAudframeBuf[i].pts;
            iminIdx = i;
        }
    }
    //MMLOGI(TAG,"read audio frame index: %d  datalen: %d pts: %d \n", iminIdx, mAudframeBuf[iminIdx].datalen, mAudframeBuf[iminIdx].pts);
    if(mAudframeBuf[iminIdx].datalen==0)
    {
        mAudframeBuf[iminIdx].busy =false;
        MMLOGI(TAG, "audio buffer len  is 0 \n");
        pthread_mutex_unlock(&m_Audlock);
        return -1;
    }
    AudFrameInfo* pFrame = &mAudframeBuf[iminIdx];
    if(pFrame->datalen > *dataSize)
    {
        mAudframeBuf[iminIdx].busy =false;
        MMLOGI(TAG, "audio buffer length is too small\n");
        pthread_mutex_unlock(&m_Audlock);
        return -1;
    }
    *dataSize = pFrame->datalen;
    *pts = pFrame->pts;
    memcpy(ptr, pFrame->data, pFrame->datalen);
    mAudFreeCount+=1;
    pFrame->busy = false;
    pthread_mutex_unlock(&m_Audlock);
    return 0;
}

/*从视频 缓冲区 中读取视频帧，如果当前没有数据可读，会
    wait在这里，直到等到数据ready的通知*/
/*get video frame from video buffer, if there no data, we'll wait here until
    receive the signal of ready to read*/
int HI_HIES_read_video_stream(void* ptr, int* dataSize, int64_t* pts, int* pType)
{
    //MMLOGI(TAG,"HI_HIES_read_video_stream enter \n");
    if(!m_bBeginReadFlag)
    {
        m_bBeginReadFlag = true;
    }
    if(mFreeCount == MAX_VIDEO_BUF_NUM)
    {
        //MMLOGI(TAG,"HI_HIES_read_video_stream wait \n");
        pthread_mutex_lock(&m_lock);
        pthread_cond_wait(&m_condition, &m_lock);
    }
    else
    {
        pthread_mutex_lock(&m_lock);
    }
    if(!m_brunning)
    {
        MMLOGI(TAG, "m_brunning is false \n");
        pthread_mutex_unlock(&m_lock);
        return -1;
    }
    int iminPts = 0;
    int iminIdx = 0;
    int i = 0;
    for(i=0; i< MAX_VIDEO_BUF_NUM; i++)
    {
        if(mframeBuf[i].busy
            && (iminPts == 0 ||mframeBuf[i].pts < iminPts))
        {
            iminPts = mframeBuf[i].pts;
            iminIdx = i;
        }
    }
    FrameInfo* pFrame = &mframeBuf[iminIdx];
    //MMLOGI(TAG,"read video frame index: %d  datalen: %d pts: %d \n", iminIdx, pFrame->datalen, pFrame->pts);

    if(mframeBuf[iminIdx].datalen==0)
    {
        mframeBuf[iminIdx].busy = false;
        MMLOGI(TAG, "video buffer len  is 0 \n");
        pthread_mutex_unlock(&m_lock);
        return -1;
    }
    if(pFrame->datalen > *dataSize)
    {
        mframeBuf[iminIdx].busy = false;
        MMLOGI(TAG, "buffer length is too small\n");
        pthread_mutex_unlock(&m_lock);
        return -1;
    }
    *dataSize = pFrame->datalen;
    *pts = pFrame->pts;
    *pType = pFrame->payload;
    memcpy(ptr, pFrame->data, pFrame->datalen);
    mFreeCount+=1;
    pFrame->busy = false;
    pthread_mutex_unlock(&m_lock);
    return 0;
}

static int unbase64char(char ch)
{
    char CharSet[64]={
    	'A','B','C','D','E','F','G','H',
    	'I','J','K','L','M','N','O','P',
    	'Q','R','S','T','U','V','W','X',
    	'Y','Z','a','b','c','d','e','f',
    	'g','h','i','j','k','l','m','n',
    	'o','p','q','r','s','t','u','v',
    	'w','x','y','z','0','1','2','3',
    	'4','5','6','7','8','9','+','/'};
	int i;
    for(i=0;i<=63;i++) if(CharSet[i]==ch) break;
    	return i;
}


int HI_UnBase64Parameter(char *src,char *d,int* outlen)
{
    char *s = src;
    char *origd = d;
    int i;
    unsigned char In[4];
    unsigned char Out[3];
//    printf("before sps is %s length is %d\n",s,length);
    if(!s||!d) return 0;
    for(;*s != 0;)
    {
        if(*s=='\n') s++;
        In[0]=s[0];
        In[1]=s[1];
        In[2]=s[2];
        In[3]=s[3];
        if(In[2]!='='&&In[3]!='=')
        {
            In[0]=unbase64char(In[0]);
            In[1]=unbase64char(In[1]);
            In[2]=unbase64char(In[2]);
            In[3]=unbase64char(In[3]);
            Out[0]=In[0]<<2|(In[1]&0x30)>>4;
            Out[1]=(In[1]&0x0f)<<4|(In[2]&0x3c)>>2;
            Out[2]=(In[2]&0x03)<<6|In[3]&0x3f;
            d[0]=Out[0];
            d[1]=Out[1];
            d[2]=Out[2];
            s+=4;
            d+=3;
        }
        else if(In[2]=='='&&In[3]=='=')
        {
            In[0]=unbase64char(In[0]);
            In[1]=unbase64char(In[1]);
            Out[0]=In[0]<<2|(In[1]&0x30)>>4;
            d[0]=Out[0];
            s+=4;
            d+=1;
        }
        else if(In[2]!='='&&In[3]=='=')
        {
            In[0]=unbase64char(In[0]);
            In[1]=unbase64char(In[1]);
            In[2]=unbase64char(In[2]);
            Out[0]=In[0]<<2|(In[1]&0x30)>>4;
            Out[1]=(In[1]&0x0f)<<4|(In[2]&0x3c)>>2;
            d[0]=Out[0];
            d[1]=Out[1];
            s+=4;
            d+=2;
        }
    }
    printf("the after len is %d\n",d - origd);
    *outlen = d - origd;
    *d='\0';
    return SUCCESS;
}

int HI_HIES_GetTrackIndex(int* index, int trackType)
{
    RTSP_CLIENT_S* pGrobalRtspClient = RTSP_Client_Get_CurSessionPtr();
    int trackindex;
    for(trackindex = 0;trackindex < 2;trackindex++)
    {
        if(pGrobalRtspClient->sTrack[trackindex]->eTrackStype == trackType)
        {
            break;
        }
    }
    if(trackindex >= 2)
    {
        MMLOGI(TAG, "do not got the Video Track Index\n");
        return -1;
    }
    *index = trackindex;
    return 0;
}

int HI_HIES_GetParameterFrame(HI_U8* pSpsBuffer,int* spsLen,HI_U8* pPPSBuffer,int* ppsLen)
{
    int s32Index = 0,trackindex = 0;
    RTSP_CLIENT_S* pGrobalRtspClient = RTSP_Client_Get_CurSessionPtr();
    char  spsBase64Buffer[128] = {0};
    int	  spsBase64Len = 0;
    char  ppsBase64Buffer[128] = {0};
    int   ppsBase64Len = 0;
    U8* pTmp = NULL;
    memset(spsBase64Buffer,0,128);
    memset(ppsBase64Buffer,0,128);
    while(s32Index < 200)
    {
        if(pGrobalRtspClient->bSdpReady == HI_TRUE)
        {
            HI_HIES_GetTrackIndex(&trackindex, TRACK_VIDEO);
            break;
        }
        usleep(25*1000);
        s32Index++;
    }
    if(s32Index == 200)
    {
        MMLOGI( TAG, "5s time out !!!!!! ");
        return HI_FAILURE;
    }
    MMLOGI( TAG, "get sps last time: %d ms\n ", (s32Index*25));
    if(!m_brunning)
    {
        MMLOGI( TAG, "rtsp client are destroyed\n ");
        return HI_FAILURE;
    }
    MMLOGI( TAG, "start parse sdp");
    if(strlen(pGrobalRtspClient->sTrack[trackindex]->strSPSTags) == 0)
    {
        MMLOGI( TAG, "sps and pps len is null  \n");
        return HI_FAILURE;
    }
    MMLOGI( TAG, "sps: %s  ", pGrobalRtspClient->sTrack[trackindex]->strSPSTags);
    pTmp = strstr(pGrobalRtspClient->sTrack[trackindex]->strSPSTags, ",");
    spsBase64Len = pTmp - pGrobalRtspClient->sTrack[trackindex]->strSPSTags;
    ppsBase64Len = pGrobalRtspClient->sTrack[trackindex]->PPSlen - spsBase64Len - 1;
    memcpy(spsBase64Buffer,pGrobalRtspClient->sTrack[trackindex]->strSPSTags,spsBase64Len);
    memcpy(ppsBase64Buffer,pGrobalRtspClient->sTrack[trackindex]->strSPSTags + spsBase64Len+ 1,ppsBase64Len);
    MMLOGI( TAG, "sps_size %d :%s pps_size %d : %s",spsBase64Len,
                spsBase64Buffer, ppsBase64Len, ppsBase64Buffer);
    HI_UnBase64Parameter(spsBase64Buffer,pSpsBuffer,spsLen);
    int i = 0;
    MMLOGI( TAG, "sps:  ");
    for(i=0; i< *spsLen; i++)
    {
        MMLOGI( TAG, "0x%02x,", pSpsBuffer[i]);
    }
    HI_UnBase64Parameter(ppsBase64Buffer,pPPSBuffer,ppsLen);
    MMLOGI( TAG, "pps:  ");
    for(i=0; i< *ppsLen; i++)
    {
        MMLOGI( TAG, "0x%02x,", pPPSBuffer[i]);
    }
    MMLOGI( TAG, "real sps_size %d  pps_size %d ",*spsLen,*ppsLen);
    return HI_SUCCESS;
}

int HI_HIES_GetVideoWidth(void)
{
    RTSP_CLIENT_S* pGrobalRtspClient = RTSP_Client_Get_CurSessionPtr();
    int trackindex;

    if(pGrobalRtspClient->bSdpReady == HI_TRUE)
    {
        HI_HIES_GetTrackIndex(&trackindex, TRACK_VIDEO);
        return pGrobalRtspClient->sTrack[trackindex]->sPrec.Width;
    }
    return 0;
}

int HI_HIES_GetVideoHeight(void)
{
    RTSP_CLIENT_S* pGrobalRtspClient = RTSP_Client_Get_CurSessionPtr();
    int trackindex;
    if(pGrobalRtspClient->bSdpReady == HI_TRUE)
    {
        HI_HIES_GetTrackIndex(&trackindex, TRACK_VIDEO);
        return pGrobalRtspClient->sTrack[trackindex]->sPrec.Height;
    }
    return 0;
}

