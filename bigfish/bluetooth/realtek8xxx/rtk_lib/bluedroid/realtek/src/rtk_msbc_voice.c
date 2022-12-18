#ifdef BLUETOOTH_RTK_VR
#include <stdio.h>
#include <unistd.h>
#include "btm_int.h"
#include "bt_utils.h"
#include "bt_trace.h"
#include "gki.h"
#include "gki_target.h"
#include "rtk_msbc.h"
#include "sbc.h"
#include "uipc.h"
#include <sys/time.h>
#include <pthread.h>
#include "bta_api.h"
#include "bta_hh_api.h"
#include <../../bta/hh/bta_hh_int.h>
#include "bta_api.h"
#include <string.h>
#include "btm_api.h"
#include "btm_ble_api.h"
#include "bta_hh_co.h"
#include "bta_gatt_api.h"
#include "srvc_api.h"

#define MSBC_VOICE_DATA_BLOCK_SIZE      (240)       //subbanks*blocklength*channel*2 = 8*15*1*2 = 240
#define BTUI_SBC_BLOCK_SIZE (58)
#define RTK_STORAGE_PCM_FILE  "/data/misc/bluedroid/voice.pcm"
#define VOICE_LOCK()  pthread_mutex_lock(&msbc_rec_cb.mutex);
#define VOICE_UNLOCK() pthread_mutex_unlock(&msbc_rec_cb.mutex);
#define SOCKET_LOCK()  pthread_mutex_lock(&msbc_rec_cb.socket_mutex);
#define SOCKET_UNLOCK() pthread_mutex_unlock(&msbc_rec_cb.socket_mutex);

static sbc_t        sbc_dec;
static BOOLEAN      msbc_init = FALSE;
static BOOLEAN      mutex_init = FALSE;
static BOOLEAN      channel_flag = FALSE;
static UINT16       pkt_num_last = 0;
static tMSBC_REC_CB msbc_rec_cb;
static tMSBC_RR_CB msbc_rr_cb;  //for record request thread

static volatile BOOLEAN      Audio_state = FALSE;
static volatile BOOLEAN      start_request_state = FALSE;
static volatile BOOLEAN     not_send_stop_request = FALSE;
static volatile BOOLEAN     keep_voice_rec = FALSE;

//////////////////deal with the buffer/////////////////////////////////////////////
#define VOICE_DATA_BUFFER_SIZE  (81)
//buffer save 80 frame = 20 packet, save 20*30ms = 600ms voice data
static struct
{
    UINT8 ridx;
    UINT8 widx;
    UINT8 buf[VOICE_DATA_BUFFER_SIZE][MSBC_VOICE_DATA_BLOCK_SIZE];
}voice_data_buffer;

static UINT8    pcmData[MSBC_VOICE_DATA_BLOCK_SIZE];

//add for iflytek
static struct
{
    UINT16 pkt_num;
    UINT8 frame_id;
    UINT8 widx;
    UINT8 buf[BTUI_SBC_BLOCK_SIZE];
}frame_buffer;
//add for iflytek end

static UINT8 get_output_rpt_id(UINT32 remote_controller_id)
{
    switch(remote_controller_id)
    {
        case RTKBT_RCUID_MDT:
            return RTKBT_OUTPUT_REPORT_MDT;

        case RTKBT_RCUID_IFLYTEK:
            return RTKBT_OUTPUT_REPORT_IFLYTEK;

        default:
            return 0xFF;
    }
}

static UINT8 get_input_data(UINT32 remote_controller_id)
{
    switch(remote_controller_id)
    {
        case RTKBT_RCUID_MDT:
            return RTKBT_INPUT_DATA_MDT;

        case RTKBT_RCUID_IFLYTEK:
            return RTKBT_INPUT_DATA_IFLYTEK;

        default:
            return 0xFF;
    }
}

static INT32 getPCMfrombuffer(UINT8 * buf, UINT32 len)
{
    INT32 res = 0;

    VOICE_LOCK();
    if(voice_data_buffer.ridx == voice_data_buffer.widx)
    {
        VOICE_UNLOCK();
        return 0;
    }

    BTM_TRACE_DEBUG2("getPCMfrombuffer ridx:%d widx:%d\n", voice_data_buffer.ridx, voice_data_buffer.widx);

    if(voice_data_buffer.ridx != voice_data_buffer.widx)
    {
        memcpy(buf,voice_data_buffer.buf[voice_data_buffer.ridx],len);
    }
    VOICE_UNLOCK();
    return 1;
}

static INT32 savePCMtobuffer(UINT8 * buf, UINT32 len)
{
    INT32 res = 0;
    VOICE_LOCK();

    memcpy(voice_data_buffer.buf[voice_data_buffer.widx],buf,len);
    voice_data_buffer.widx ++;
    voice_data_buffer.widx %= VOICE_DATA_BUFFER_SIZE;

    if(voice_data_buffer.widx == voice_data_buffer.ridx)
    {
        BTM_TRACE_DEBUG0("the buffer is full,discard the old frame");
        voice_data_buffer.ridx ++;
        voice_data_buffer.ridx %= VOICE_DATA_BUFFER_SIZE;
    }
    BTM_TRACE_DEBUG2("savePCMtobuffer ridx:%d widx:%d\n", voice_data_buffer.ridx, voice_data_buffer.widx);
    VOICE_UNLOCK();
    return 1;
}

static BOOLEAN isBufferEmpty()
{
    VOICE_LOCK();
    if(voice_data_buffer.ridx == voice_data_buffer.widx){
        VOICE_UNLOCK();
        return TRUE;
    }
    else{
        VOICE_UNLOCK();
        return FALSE;
    }
}

static void resetPCMBuffer()
{
    VOICE_LOCK();
    memset(&voice_data_buffer,0,sizeof(voice_data_buffer));
    VOICE_UNLOCK();
}

static void msbc_voice_in_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event)
{
    switch(event)
    {
        case UIPC_OPEN_EVT:
            msbc_rec_cb.channel_status = TRUE;
            BTM_TRACE_DEBUG0("msbc_voice_in_cb: UIPC_OPEN_EVT");
            break;

        case UIPC_CLOSE_EVT:
            VOICE_LOCK();
            //msbc_rec_cb.p_dev_cb = NULL;
            //msbc_rec_cb.conn_id = 0;
            msbc_rec_cb.channel_status = FALSE;
            channel_flag = FALSE;
            VOICE_UNLOCK();
            BTM_TRACE_DEBUG0("msbc_voice_in_cb: UIPC_CLOSE_EVT");
            break;

        case UIPC_RX_DATA_EVT:
            break;

        case UIPC_RX_DATA_READY_EVT:
            BTM_TRACE_DEBUG0("msbc_voice_in_cb: UIPC_RX_DATA_READY_EVT");
            break;
        case UIPC_TX_DATA_READY_EVT:
            break;

        default :
            BTM_TRACE_ERROR1("### SCO-CHANNEL EVENT %d NOT HANDLED ###", event);
            break;
    }
}

/* blocking call */
void stop_thread(void)
{
    /* request shutdown of read thread */
    VOICE_LOCK();
    msbc_rec_cb.running = 0;
    msbc_rr_cb.running = 0;
    //msbc_rec_cb.p_dev_cb = NULL;
    //msbc_rec_cb.conn_id = 0;
    not_send_stop_request = FALSE;
    start_request_state = FALSE;
    Audio_state = FALSE;
    VOICE_UNLOCK();

    /* wait until thread is fully terminated */
    if (msbc_rec_cb.tid > 0)
        pthread_join(msbc_rec_cb.tid, NULL);

    SOCKET_LOCK();
    UIPC_Close(UIPC_CH_ID_RTKBT_VR_AUDIO);
    usleep(1100000);
    SOCKET_UNLOCK();

    if (msbc_rr_cb.tid > 0)
        pthread_join(msbc_rr_cb.tid, NULL);
}

/***************deal with pthread****************/

static void voice_task(void *arg)
{
    BTM_TRACE_WARNING0("VOICE THREAD START");
    int i = 0;
    int j = 0;
    while(i<3000)
    {
        if(Audio_state == TRUE)
        {
            BTM_TRACE_WARNING0("Audio_state is ok");
            break;
        }
        i++;
        usleep(1000);
    }
    if(Audio_state == FALSE)
    {
        BTM_TRACE_WARNING0("Audio_state is not ok!");
        if((not_send_stop_request == FALSE) && (start_request_state == TRUE)){
            RTKBT_VR_send_stop_request(msbc_rec_cb.p_dev_cb);
        }
        VOICE_LOCK();
        msbc_rec_cb.running = 0;
        not_send_stop_request = FALSE;
        start_request_state = FALSE;
        Audio_state = FALSE;
        VOICE_UNLOCK();
        SOCKET_LOCK();
        UIPC_Close(UIPC_CH_ID_RTKBT_VR_AUDIO);
        SOCKET_UNLOCK();
    }
    while (1)
    {
        if(msbc_rec_cb.running)
        {
            if(start_request_state == FALSE)
            {
                if((j != 0) && (j%200 == 0) && (j < 800))
                {
                    RTKBT_VR_send_start_request(msbc_rec_cb.p_dev_cb);
                    BTM_TRACE_WARNING0("resend start msbc voice rec!");
                }
                j++;
            }
            if(msbc_rec_cb.channel_status)
            {
                if(!isBufferEmpty())
                {
                    if(getPCMfrombuffer(pcmData,MSBC_VOICE_DATA_BLOCK_SIZE))
                    {
                        if(UIPC_RTKBT_VR_Send_noblock(UIPC_CH_ID_RTKBT_VR_AUDIO, 0, pcmData, MSBC_VOICE_DATA_BLOCK_SIZE))
                        {
                            BTM_TRACE_DEBUG0("send data sucess");
                            voice_data_buffer.ridx ++;
                            voice_data_buffer.ridx %= VOICE_DATA_BUFFER_SIZE;
                        } else {
                            BTM_TRACE_ERROR0("send data failed");
                        }
                    }
                }
                else{
                    BTIF_TRACE_VERBOSE0("The buffer is Empty, the data send from msbc_voice_decode!");
                }
            }
            else if (!channel_flag) {
                usleep(100000);
                SOCKET_LOCK();
                channel_flag = UIPC_Open(UIPC_CH_ID_RTKBT_VR_AUDIO, msbc_voice_in_cb);
                if(channel_flag)
                    UIPC_Ioctl(UIPC_CH_ID_RTKBT_VR_AUDIO, UIPC_SET_READ_POLL_TMO, 0);
                SOCKET_UNLOCK();
                BTIF_TRACE_DEBUG1("The data channel open in voice_task, channel_flag = %d", channel_flag)
            }
        }
        else {
            BTM_TRACE_DEBUG0("thread is stop!");
            msbc_rec_cb.p_dev_cb = NULL;
            msbc_rec_cb.conn_id = 0;
            //msbc_rec_cb.channel_status = FALSE;
            resetPCMBuffer();
//            UIPC_Close(UIPC_CH_ID_RTKBT_VR_AUDIO);
            break;
        }
        usleep(1000);
    }
    msbc_rec_cb.tid = 0;
    BTM_TRACE_WARNING0("VOICE THREAD DONE");
}

static void keep_voice_task(void *arg)
{
    int i = 0;
    int j = 0;
    while(j<3000)
    {
        if(Audio_state == TRUE)
        {
            break;
        }
        j++;
        usleep(1000);
    }
    if(Audio_state == FALSE)
    {
        msbc_rr_cb.running =0;
        goto close_task;
    }

    BTM_TRACE_WARNING0("KEEP VOICE THREAD START");
    while(msbc_rr_cb.running)
    {
        while(i < TIME_OUT)
        {
            i++;
            if(msbc_rec_cb.running == 0)
            {
                keep_voice_rec = FALSE;
                break;
             }
            keep_voice_rec = TRUE;
            usleep(100000);
        }
        if( (keep_voice_rec == TRUE) && (msbc_rec_cb.running != 0) &&
            (msbc_rec_cb.channel_status != 0) && (not_send_stop_request == FALSE))
        {
            i = 0;
            /*send start record start command*/
            BTM_TRACE_WARNING0("send start request");
            if(msbc_rec_cb.p_dev_cb == NULL)
            {
                BTM_TRACE_WARNING0("p_dev_cb is null");
                break;
            }
            if(RTKBT_VR_get_remote_controller_id() == RTKBT_RCUID_MDT)
                RTKBT_VR_send_start_request(msbc_rec_cb.p_dev_cb);
        }
        else
            break;
    }
close_task:
    msbc_rr_cb.tid = 0;
    msbc_rr_cb.running = 0;
    keep_voice_rec == FALSE;
    BTM_TRACE_WARNING0("KEEP VOICE THREAD DONE");
}

int start_thread(void)
{
    BTM_TRACE_WARNING0("cheng_@start thread");
    msbc_rec_cb.running = 1;
    msbc_rr_cb.running = 1;

    if(msbc_rec_cb.tid > 0)
    {
        BTM_TRACE_WARNING0("the voice pthread is already start,can't start again");
        return -1;
    }

    if(msbc_rr_cb.tid > 0)
    {
        BTM_TRACE_WARNING0("the keep record pthread is already start,can't start again");
        return -1;
    }

    if ((pthread_create(&msbc_rec_cb.tid, (const pthread_attr_t *) NULL, (void*)voice_task, NULL) < 0) ||
            (pthread_create(&msbc_rr_cb.tid, (const pthread_attr_t *) NULL, (void*)keep_voice_task, NULL) < 0))
    {
        BTM_TRACE_ERROR0("uipc_thread_create voice pthread_create failed");
        stop_thread();
        return -1;
    }
    return 0;
}

void rtk_msbc_setup()
{
    if(msbc_init)
    {
        sbc_reinit(&sbc_dec,0);
    }else{
        memset(&sbc_dec,0,sizeof(sbc_dec));
        sbc_init(&sbc_dec,0);
        msbc_init = TRUE;
    }
}

BOOLEAN RTKBT_VR_start_msbc_voice_rec(tBTA_HH_DEV_CB *p_dev_cb, UINT16 conn_id)
{
    //remove file pcm to data
    //remove(RTK_STORAGE_PCM_FILE);
    if(msbc_rec_cb.p_dev_cb == NULL){
        msbc_rec_cb.p_dev_cb = p_dev_cb;
        msbc_rec_cb.conn_id = conn_id;
        SOCKET_LOCK();
        if(msbc_rec_cb.channel_status != FALSE){
            BTM_TRACE_ERROR0("data channel socket is not closed for now!");
            usleep(300);
        }
        SOCKET_UNLOCK();
    }
    else{
        if(msbc_rec_cb.conn_id != conn_id){
            BTM_TRACE_ERROR0("Another device Already have started voice record!");
        }
        else{
            BTM_TRACE_ERROR0("This device Already have started voice record!");
        }
        return FALSE;
    }

    rtk_msbc_setup();
    BTM_TRACE_DEBUG1("%s\n", __FUNCTION__);

    if(!mutex_init)
    {
        const pthread_mutexattr_t attr = PTHREAD_MUTEX_RECURSIVE;
        pthread_mutex_init(&msbc_rec_cb.mutex, &attr);

        const pthread_mutexattr_t socket_attr = PTHREAD_MUTEX_NORMAL;
        pthread_mutex_init(&msbc_rec_cb.socket_mutex, &socket_attr);
    }
    resetPCMBuffer();
    //add for iflytek
    memset(&frame_buffer,0,sizeof(frame_buffer));
    frame_buffer.frame_id = 4;
    //add for iflytek end
    //UIPC_Init(NULL);
    SOCKET_LOCK();
    channel_flag = UIPC_Open(UIPC_CH_ID_RTKBT_VR_AUDIO, msbc_voice_in_cb);
    if(channel_flag)
        UIPC_Ioctl(UIPC_CH_ID_RTKBT_VR_AUDIO, UIPC_SET_READ_POLL_TMO, 0);
    SOCKET_UNLOCK();

    if(start_thread() < 0)
    {
        SOCKET_LOCK();
        UIPC_Close(UIPC_CH_ID_RTKBT_VR_AUDIO);
        BTM_TRACE_ERROR0("UIPC_CLOSE before sleep +++");
        usleep(1100000);
        BTM_TRACE_ERROR0("UIPC_CLOSE after sleep ---");
        SOCKET_UNLOCK();
        return FALSE;
    }
    /*send start record start request*/
    RTKBT_VR_send_start_request(msbc_rec_cb.p_dev_cb);
    return TRUE;
}

void RTKBT_VR_restart_msbc_voice_rec(void)
{
    rtk_msbc_setup();
    BTM_TRACE_DEBUG1("%s\n", __FUNCTION__);
    resetPCMBuffer();
    if (msbc_rec_cb.channel_status == FALSE)
    {
        BTM_TRACE_ERROR0("the socket is already close,re-open");
        UIPC_Open(UIPC_CH_ID_RTKBT_VR_AUDIO, msbc_voice_in_cb);
        UIPC_Ioctl(UIPC_CH_ID_RTKBT_VR_AUDIO, UIPC_SET_READ_POLL_TMO, 0);
    }
    if (msbc_rec_cb.tid == 0)
    {
        BTM_TRACE_ERROR0("the thread is already stop,restart");
        start_thread();
    }
}

void RTKBT_VR_stop_msbc_voice_rec(void)
{
    BTM_TRACE_DEBUG1("%s\n", __FUNCTION__);
    if(not_send_stop_request == FALSE){
        RTKBT_VR_send_stop_request(msbc_rec_cb.p_dev_cb);
    }
    else
    {
        BTM_TRACE_DEBUG0("cheng_@RTKBT_VR_stop_msbc_voice_rec not send stop request");
    }
    stop_thread();
}

BOOLEAN RTKBT_VR_msbc_voice_decode_MDT(tVOICE_HSDATA *voice_data)
{
    BTM_TRACE_EVENT0("cheng_@RTKBT_VR_msbc_voice_decode_MDT");
    static UINT8    pcm[MSBC_VOICE_DATA_BLOCK_SIZE];
    UINT8       *p = NULL;
    UINT8       pkt_size = 0;

    static UINT8    sbc_dec_buf[BTUI_SBC_BLOCK_SIZE*10];
    static UINT32   sbc_dec_widx = 0;
    static UINT32   sbc_dec_ridx = 0;
    int writen = 0,res = 0;
    UINT16     pkt_num = 0;

    //save pcm data to XXX.pcm
    /*FILE *fp;
    fp = fopen (RTK_STORAGE_PCM_FILE, "a+");
    if (fp == NULL)
    {
        BTM_TRACE_WARNING0("open file failed\n");
        return FALSE;
    }*/
    VOICE_LOCK();
    if((msbc_rec_cb.p_dev_cb == NULL) && (msbc_rec_cb.running == 0)){
        APPL_TRACE_DEBUG0("cheng_@ p_dev_cb is null or voice task is done!");
        //close fp
        //fclose(fp);
        VOICE_UNLOCK();
        return FALSE;
    }
    VOICE_UNLOCK();

    if(sbc_dec_ridx == sbc_dec_widx)
    {
        sbc_dec_widx = 0;
        sbc_dec_ridx = 0;
    }
    else
    {
        APPL_TRACE_DEBUG0("cheng_@ ridx and widx is not the same!");
        sbc_dec_widx = 0;
        sbc_dec_ridx = 0;
    }
    //reportID(1)+num(2)+voice(232)
    BTM_TRACE_EVENT1("voice_decode report_id:%d", voice_data->data[0]);
    p = (UINT8*)(voice_data->data+1);
    STREAM_TO_UINT16(pkt_num,p);
    BTM_TRACE_EVENT1("voice_decode pkt_num:%d ", pkt_num);
    pkt_size = voice_data->data_len - 3;
    memcpy(&sbc_dec_buf[sbc_dec_widx],p,pkt_size);
    sbc_dec_widx += pkt_size;
    BTM_TRACE_EVENT2("voice_decode pkt_num:%d pkt_num_last: %d", pkt_num,pkt_num_last);
    pkt_num_last ++;
    if(pkt_num != pkt_num_last)
    {
        BTM_TRACE_ERROR2("lost voice packet,pkt_num:%d pkt_num_last: %d",pkt_num,pkt_num_last-1);
        pkt_num_last = pkt_num;
    }

    while((sbc_dec_ridx+BTUI_SBC_BLOCK_SIZE) <= sbc_dec_widx)
    {
        res = sbc_decode(&sbc_dec, &sbc_dec_buf[sbc_dec_ridx], sbc_dec_widx-sbc_dec_ridx, pcm, MSBC_VOICE_DATA_BLOCK_SIZE, &writen);
        if(res > 0)
        {
            //save pcm data to XXX.pcm
            if(240 == writen){
                BTM_TRACE_DEBUG2("save pcm data res:%d writen:%d\n", res, writen);
                //fwrite(pcm, writen, 1, fp);
            }
            BTM_TRACE_DEBUG2("sbc_decode res:%d writen:%d\n", res, writen);
            if(msbc_rec_cb.channel_status)
            {
                if(isBufferEmpty())
                {
                    BTM_TRACE_DEBUG0("the buffer empty,send data to socket");
                    if(!UIPC_RTKBT_VR_Send_noblock(UIPC_CH_ID_RTKBT_VR_AUDIO, 0, pcm, writen))
                    {
                        BTM_TRACE_WARNING0("send data fail, save data to buffer");
                        savePCMtobuffer(pcm, writen);
                    }
                } else {
                    BTM_TRACE_DEBUG0("the buffer is not empty, save data to buffer");
                    savePCMtobuffer(pcm, writen);
                }
            } else {
                if(!msbc_rec_cb.channel_status)
                {
                    BTM_TRACE_DEBUG0("socket is close");
                }
                savePCMtobuffer(pcm, writen);
            }

            sbc_dec_ridx += res;
            sbc_dec_ridx ++;
        }else{
            BTM_TRACE_ERROR3("sbc_decode fail[res=%d] %d[%02x]\n",res,sbc_dec_ridx,sbc_dec_buf[sbc_dec_ridx]);
            sbc_dec_ridx ++;
        }
    }

    //free(voice_data);
    //close save pcm data
    //BTM_TRACE_WARNING0("fseek to the end \n");
    //fseek(fp,0,SEEK_END);
    //int lSize = ftell(fp);
    //BTM_TRACE_WARNING1("file length %d\n",lSize);
    //fclose(fp);
    APPL_TRACE_DEBUG0("cheng_@ msbc free data buffer!");
    return TRUE;
}


void frame_decode(void *input, int input_len)
{
    int writen = 0,res = 0;
    static UINT8    pcm_iflytek[MSBC_VOICE_DATA_BLOCK_SIZE];

    //save pcm data to XXX.pcm
    //FILE *fp;
    //fp = fopen (RTK_STORAGE_PCM_FILE, "a+");
    //if (fp == NULL)
    //{
        //BTM_TRACE_WARNING0("open file failed\n");
    //}

    res = sbc_decode(&sbc_dec, input, input_len, pcm_iflytek, MSBC_VOICE_DATA_BLOCK_SIZE, &writen);
    if(res > 0)
    {
        //save pcm data
        //fwrite(pcm_iflytek, writen, 1, fp);
        //BTM_TRACE_DEBUG2("sbc_decode res:%d writen:%d\n", res, writen);
        if(msbc_rec_cb.channel_status)
        {
            if(isBufferEmpty())
            {
                BTM_TRACE_DEBUG0("the buffer empty,send data to socket");
                if(!UIPC_RTKBT_VR_Send_noblock(UIPC_CH_ID_RTKBT_VR_AUDIO, 0, pcm_iflytek, writen))
                {
                    BTM_TRACE_WARNING0("send data fail, save data to buffer");
                    savePCMtobuffer(pcm_iflytek, writen);
                }
            } else {
                BTM_TRACE_DEBUG0("the buffer is not empty, save data to buffer");
                savePCMtobuffer(pcm_iflytek, writen);
            }
        } else {
            if(!msbc_rec_cb.channel_status)
            {
                BTM_TRACE_DEBUG0("socket is close");
            }
            savePCMtobuffer(pcm_iflytek, writen);
        }
    }else{
        BTM_TRACE_ERROR1("sbc_decode fail[res=%d]",res);
    }
    //close save pcm data
    //BTM_TRACE_WARNING0("fseek to the end \n");
    //fseek(fp,0,SEEK_END);
    //int lSize = ftell(fp);
    //BTM_TRACE_WARNING1("file length %d\n",lSize);
    //fclose(fp);
}

BOOLEAN RTKBT_VR_msbc_voice_decode_iflytek(tVOICE_HSDATA *voice_data)
{
    UINT8       *p = NULL;
    UINT8       pkt_size = 0;
    static UINT8 sbc_dec_buf_iflytek[BTUI_SBC_BLOCK_SIZE];
    UINT16      pkt_num = 0;
    UINT8       frame_id = 0;
    BTM_TRACE_EVENT0("cheng_@RTKBT_VR_msbc_voice_decode_iflytek");

    if((msbc_rec_cb.p_dev_cb == NULL) && (msbc_rec_cb.running == 0)){
        return FALSE;
    }

    //reportID(1)+num(2)+packetID(1)+voice
    p = (UINT8*)(voice_data->data+1);
    STREAM_TO_UINT16(pkt_num,p);
    STREAM_TO_UINT8(frame_id,p);
    pkt_size = voice_data->data_len - 4;
    BTM_TRACE_DEBUG3("voice_encode_mode2 pkt_num:%d frameID: %d pkt_size:%d", pkt_num,frame_id,pkt_size);

    if(frame_id == 0)
    {
        if(pkt_num != frame_buffer.pkt_num+1)
        {
            BTM_TRACE_ERROR2("lost voice packet,pkt_num:%d pkt_num_last: %d",pkt_num,frame_buffer.pkt_num);
        }
        frame_buffer.pkt_num = pkt_num;
        if(frame_buffer.frame_id != 3)
        {
            BTM_TRACE_ERROR2("lost frame,frame last:%d, frame:%d",frame_buffer.frame_id,frame_id);
        }
        frame_buffer.frame_id = frame_id;
        frame_buffer.widx = 0;
        memcpy(&frame_buffer.buf[frame_buffer.widx],p,pkt_size);
        frame_buffer.widx += pkt_size;
    }
    else if (frame_id == 3)
    {
        if((pkt_num != frame_buffer.pkt_num)||frame_buffer.frame_id !=2)
        {
            BTM_TRACE_ERROR0("the pkt is error,discard");
            frame_buffer.frame_id = 4;
            return FALSE;
        }
        else {
            frame_buffer.frame_id = frame_id;
            memcpy(&frame_buffer.buf[frame_buffer.widx],p,pkt_size);
            frame_buffer.widx += pkt_size;
            if(frame_buffer.widx == 64)
            {
                //encode the packet
                memcpy(&sbc_dec_buf_iflytek,&frame_buffer.buf,BTUI_SBC_BLOCK_SIZE);

                if(msbc_rec_cb.p_dev_cb == NULL){
                APPL_TRACE_DEBUG0("cheng_@ msbc free data buffer!");
                return FALSE;
            }
                frame_decode(&sbc_dec_buf_iflytek, BTUI_SBC_BLOCK_SIZE);
            } else {
                BTM_TRACE_ERROR1("the pkt size is %d,error discard",frame_buffer.widx);
            }
        }

    }
    else
    {
        if((pkt_num != frame_buffer.pkt_num)||(frame_buffer.frame_id+1)!= frame_id ||frame_id>3)
        {
            BTM_TRACE_ERROR0("the pkt is error,discard");
            frame_buffer.frame_id = 4;
            return FALSE;
        }
        else {
            frame_buffer.frame_id = frame_id;
            memcpy(&frame_buffer.buf[frame_buffer.widx],p,pkt_size);
            frame_buffer.widx += pkt_size;
        }
    }
    //BTM_TRACE_DEBUG3("frame_buffer pkt_num:%d frameID: %d widx:%d", frame_buffer.pkt_num,frame_buffer.frame_id,frame_buffer.widx);
    return TRUE;
}

void RTKBT_VR_send_stop_request(tBTA_HH_DEV_CB *p_dev_cb)
{
    BT_HDR  *p_buf_voice;
    tBTA_HH_DEV_CB *p_dev_cb_temp;
    tBTA_HH_RPT_TYPE voice_output_r_type;
    UINT8 voice_output_rpt_id;
    UINT16 len;
    UINT32 remote_controller_id = RTKBT_VR_get_remote_controller_id();

    voice_output_rpt_id = get_output_rpt_id(remote_controller_id);
    voice_output_r_type = RTKBT_OUTPUT_REPORT_TYPE;

    p_dev_cb_temp = p_dev_cb;
    len = 0x02;
    if((p_buf_voice = (BT_HDR *) GKI_getbuf((UINT16)(sizeof(BT_HDR) + len))) != NULL)
    {
        //APPL_TRACE_DEBUG0("cheng_@msbc getbuf success!");
        memset(p_buf_voice, 0, sizeof(BT_HDR) + len);
        /*set the value of rec_stop_res*/
        p_buf_voice->len = len;
        *(UINT8 *)(p_buf_voice + 1) = voice_output_rpt_id;
        *((UINT8 *)(p_buf_voice + 1) + 1) = 0x00;
        APPL_TRACE_DEBUG0("cheng_@msbc send stop write request");
        bta_hh_le_write_rpt(p_dev_cb_temp,
                            0,
                            BTA_GATTC_TYPE_WRITE_NO_RSP,
                            voice_output_r_type,
                            p_buf_voice,
                            BTA_HH_SET_RPT_EVT);
        APPL_TRACE_DEBUG0("cheng_@msbc free RTKBT_VR_send_stop_request buffer");
        GKI_freebuf(p_buf_voice);
    }
    else{
        APPL_TRACE_DEBUG0("cheng_@msbc get buf wrong!");
        }
}

void RTKBT_VR_send_start_request(tBTA_HH_DEV_CB *p_dev_cb)
{
    BT_HDR  *p_buf_voice;
    tBTA_HH_DEV_CB *p_dev_cb_temp;
    tBTA_HH_RPT_TYPE voice_output_r_type;
    UINT8 voice_output_rpt_id;
    UINT16 len;
    UINT32 remote_controller_id = RTKBT_VR_get_remote_controller_id();

    voice_output_rpt_id = get_output_rpt_id(remote_controller_id);
    voice_output_r_type = RTKBT_OUTPUT_REPORT_TYPE;

    p_dev_cb_temp = p_dev_cb;
    len = 0x02;
    if((p_buf_voice = (BT_HDR *) GKI_getbuf((UINT16)(sizeof(BT_HDR) + len))) != NULL)
    {
        APPL_TRACE_DEBUG0("cheng_@msbc getbuf success!");
        memset(p_buf_voice, 0, sizeof(BT_HDR) + len);
        /*set the value of rec_stop_res*/
        p_buf_voice->len = len;
        *(UINT8 *)(p_buf_voice + 1) = voice_output_rpt_id;
        *((UINT8 *)(p_buf_voice + 1) + 1) = 0x01;
        APPL_TRACE_DEBUG0("cheng_@msbc send start write request");
        bta_hh_le_write_rpt(p_dev_cb_temp,
                            0,
                            BTA_GATTC_TYPE_WRITE_NO_RSP,
                            voice_output_r_type,
                            p_buf_voice,
                            BTA_HH_SET_RPT_EVT);
        APPL_TRACE_DEBUG0("cheng_@msbc free RTKBT_VR_send_start_request buffer");
        GKI_freebuf(p_buf_voice);
    }
    else{
        APPL_TRACE_DEBUG0("cheng_@msbc get buf wrong!");
        }
}


void RTKBT_VR_device_disconn(UINT16 conn_id)
{
    if(conn_id == msbc_rec_cb.conn_id){
        RTKBT_VR_not_snd_stop_request(TRUE);
        APPL_TRACE_DEBUG0("cheng_@The record device is disconnected!");
    }
}

void RTKBT_VR_not_snd_stop_request(BOOLEAN permission)
{
    not_send_stop_request = permission;
    APPL_TRACE_DEBUG0("cheng_@not send stop request");
}

BOOLEAN RTKBT_VR_get_msbc_status(void)
{
    return (msbc_rec_cb.running & msbc_rec_cb.channel_status);
}

tBTA_HH_DEV_CB * RTKBT_VR_get_dev_cb(void)
{
    return(msbc_rec_cb.p_dev_cb);
}

void RTKBT_VR_Audio_set_ok(BOOLEAN state)
{
    Audio_state = state;
}

void RTKBT_VR_start_request_ok(BOOLEAN state)
{
    start_request_state = state;
}

BOOLEAN RTKBT_VR_start_request_status(void)
{
    return(start_request_state);
}

void RTKBT_VR_get_report_id(UINT8 *voice_input_data,UINT8 *voice_output_rpt_id,UINT32 remote_controller_id)
{
    *voice_output_rpt_id = get_output_rpt_id(remote_controller_id);
    *voice_input_data   = get_input_data(remote_controller_id);

}

#endif
