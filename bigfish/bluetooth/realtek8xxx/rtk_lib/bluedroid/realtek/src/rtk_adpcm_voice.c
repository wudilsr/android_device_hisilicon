#if 0
#include <stdio.h>
#include <unistd.h>
#include "btm_int.h"
#include "bt_utils.h"
#include "bt_trace.h"
#include "gki.h"
#include "gki_target.h"
#include "rtk_adpcm.h"
#include "adpcm.h"
#include "bta_att_api.h"
#include "uipc.h"
#include <sys/time.h>
#include <pthread.h>

static tADPCM_REC_CB adpcm_rec_cb;
#define RTK_STORAGE_PCM_FILE  "/data/misc/bluedroid/voice.pcm"
#define VOHOG_LOCK()  pthread_mutex_lock(&adpcm_rec_cb.mutex);
#define VOHOG_UNLOCK() pthread_mutex_unlock(&adpcm_rec_cb.mutex);
static BOOLEAN      mutex_init = FALSE;

//////////////////deal with the buffer/////////////////////////////////////////////
#define ADPCM_VOICE_DATA_BUFFER_SIZE    (21)
#define ADPCM_VOICE_DATA_BLOCK_SIZE   (1020)
//buffer save 20 frame
static struct
{
    UINT8 ridx;
    UINT8 widx;
    UINT8 buf[ADPCM_VOICE_DATA_BUFFER_SIZE][ADPCM_VOICE_DATA_BLOCK_SIZE];
}adpcm_voice_data_buffer;

static UINT8 tempData[ADPCM_VOICE_DATA_BLOCK_SIZE];



static INT32 getDATAfrombuffer(UINT8 * buf, UINT32 len)
{
    INT32 res = 0;

    VOHOG_LOCK();
    if(adpcm_voice_data_buffer.ridx == adpcm_voice_data_buffer.widx)
    {
        VOHOG_UNLOCK();
        return 0;
    }

    BTM_TRACE_DEBUG2("getPCMfrombuffer ridx:%d widx:%d\n", adpcm_voice_data_buffer.ridx, adpcm_voice_data_buffer.widx);

    if(adpcm_voice_data_buffer.ridx != adpcm_voice_data_buffer.widx)
    {
        memcpy(buf,adpcm_voice_data_buffer.buf[adpcm_voice_data_buffer.ridx],len);
    }
    VOHOG_UNLOCK();
    return 1;
}

static INT32 saveDATAtobuffer(UINT8 * buf, UINT32 len)
{
    INT32 res = 0;
    VOHOG_LOCK();

    memcpy(adpcm_voice_data_buffer.buf[adpcm_voice_data_buffer.widx],buf,len);
    adpcm_voice_data_buffer.widx ++;
    adpcm_voice_data_buffer.widx %= ADPCM_VOICE_DATA_BUFFER_SIZE;


    if(adpcm_voice_data_buffer.widx == adpcm_voice_data_buffer.ridx)
    {
        BTM_TRACE_DEBUG0("the adpcm buffer is full,discard the old frame");
        adpcm_voice_data_buffer.ridx ++;
        adpcm_voice_data_buffer.ridx %= ADPCM_VOICE_DATA_BUFFER_SIZE;
    }
    BTM_TRACE_DEBUG2("savePCMfrombuffer ridx:%d widx:%d\n", adpcm_voice_data_buffer.ridx, adpcm_voice_data_buffer.widx);
    VOHOG_UNLOCK();
    return 1;
}

static BOOLEAN isEmpty()
{
    if(adpcm_voice_data_buffer.ridx == adpcm_voice_data_buffer.widx)
        return TRUE;
    else
        return FALSE;
}

static void resetBuffer()
{
    VOHOG_LOCK();
    memset(&adpcm_voice_data_buffer,0,sizeof(adpcm_voice_data_buffer));
    VOHOG_UNLOCK();
}
/////////////////////////////////////////////////////////////////

/////////////////////deal with pthread////////////////////////////////////////////////

static void work_task(void *arg)
{
    BTM_TRACE_WARNING0("WORK THREAD START");
    while (1)
    {
        VOHOG_LOCK();
        if(adpcm_rec_cb.running)
        {
           if(adpcm_rec_cb.channel_status)
           {
                if(!isEmpty())
                {
                    if(getDATAfrombuffer(tempData,ADPCM_VOICE_DATA_BLOCK_SIZE))
                    {
                        if(UIPC_RTKBT_VR_Send_noblock(UIPC_CH_ID_RTKBT_VR_AUDIO, 0, tempData, ADPCM_VOICE_DATA_BLOCK_SIZE))
                        {
                            BTM_TRACE_DEBUG0("send data sucess");

                            adpcm_voice_data_buffer.ridx ++;
                            adpcm_voice_data_buffer.ridx %= ADPCM_VOICE_DATA_BUFFER_SIZE;

                        } else {
                            BTM_TRACE_ERROR0("send data failed");
                        }
                   }

                }
           }
        } else {
            if(adpcm_rec_cb.channel_status)
            {
                BTM_TRACE_WARNING0("close thread: channel is connected");
                if(isEmpty())
                {
                    BTM_TRACE_WARNING0("the buffer is empty, close socket");
                    resetBuffer();
                    UIPC_Close(UIPC_CH_ID_RTKBT_VR_AUDIO);
                    VOHOG_UNLOCK();
                    break;
                }  else {
                    BTM_TRACE_WARNING0("the buffer is not empty, send data");
                    if(getDATAfrombuffer(tempData,ADPCM_VOICE_DATA_BLOCK_SIZE))
                    {
                        if(UIPC_RTKBT_VR_Send_noblock(UIPC_CH_ID_RTKBT_VR_AUDIO, 0, tempData, ADPCM_VOICE_DATA_BLOCK_SIZE))
                        {
                            BTM_TRACE_DEBUG0("send data sucess");

                            adpcm_voice_data_buffer.ridx ++;
                            adpcm_voice_data_buffer.ridx %= ADPCM_VOICE_DATA_BUFFER_SIZE;

                        } else {
                            BTM_TRACE_ERROR0("send data failed,close socket");
                            resetBuffer();
                            UIPC_Close(UIPC_CH_ID_RTKBT_VR_AUDIO);
                            VOHOG_UNLOCK();
                            break;
                        }
                   }

                }
            }else {
                BTM_TRACE_WARNING0("close thread: the socket is not connected");
                VOHOG_UNLOCK();
                break;
            }

        }
        VOHOG_UNLOCK();
        usleep(1000);
    }
    adpcm_rec_cb.tid = 0;
    BTM_TRACE_WARNING0("VOICE THREAD DONE");
}

int start_work_thread(void)
{
    adpcm_rec_cb.running = 1;

    if(adpcm_rec_cb.tid > 0)
    {
        BTM_TRACE_WARNING0("the pthread is already start,can't start again");
        return -1;
    }

    if (pthread_create(&adpcm_rec_cb.tid, (const pthread_attr_t *) NULL, (void*)work_task, NULL) < 0)
    {
        BTM_TRACE_ERROR0("uipc_thread_create pthread_create failed");
        return -1;
    }

    return 0;
}

/* blocking call */
void stop_work_thread(void)
{
    /* request shutdown of read thread */
    VOHOG_LOCK();
    adpcm_rec_cb.running = 0;
    VOHOG_UNLOCK();

    /* wait until thread is fully terminated */
    if (adpcm_rec_cb.tid > 0)
        pthread_join(adpcm_rec_cb.tid, NULL);
}
////////////////////////////////////////////////////////////////////////////////////////
static void voice_out_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event)
{
    switch(event)
    {
        case UIPC_OPEN_EVT:
            adpcm_rec_cb.channel_status = TRUE;
            BTM_TRACE_ERROR1("voice_out_cb:event %d\n",event);
            break;

        case UIPC_CLOSE_EVT:
            adpcm_rec_cb.channel_status = FALSE;
            BTM_TRACE_ERROR1("voice_out_cb:event %d\n",event);
            break;

        case UIPC_RX_DATA_EVT:
            break;

        case UIPC_RX_DATA_READY_EVT:

            break;
        case UIPC_TX_DATA_READY_EVT:
            break;

        default :
            BTM_TRACE_ERROR1("### SCO-CHANNEL EVENT %d NOT HANDLED ###", event);
            break;
    }
}


void start_adpcm_voice_rec(void)
{
    remove(RTK_STORAGE_PCM_FILE);

    BTM_TRACE_ERROR1("%s\n", __FUNCTION__);
    if (adpcm_rec_cb.adpcm_state == NULL)
    {
       BTM_TRACE_DEBUG0("init the adpcm");
       adpcm_rec_cb.adpcm_state = adpcm_decode_alloc();
    }
    adpcm_rec_cb.n_20bytes_pkts = 0;

    if(!mutex_init)
    {
        const pthread_mutexattr_t attr = PTHREAD_MUTEX_RECURSIVE;
        pthread_mutex_init(&adpcm_rec_cb.mutex, &attr);
    }
    memset(&adpcm_voice_data_buffer,0,sizeof(adpcm_voice_data_buffer));
    UIPC_Open(UIPC_CH_ID_RTKBT_VR_AUDIO, voice_out_cb);
    UIPC_Ioctl(UIPC_CH_ID_RTKBT_VR_AUDIO, UIPC_SET_READ_POLL_TMO, 0);

    start_work_thread();
}

void stop_adpcm_voice_rec(void)
{
    BTM_TRACE_ERROR1("%s\n", __FUNCTION__);
    if (adpcm_rec_cb.adpcm_state != NULL)
    {
        adpcm_decode_free(adpcm_rec_cb.adpcm_state);
        adpcm_rec_cb.adpcm_state = NULL;
    }

    stop_work_thread();
}

BOOLEAN adpcm_voice_encode(tBTA_ATT_HSDATA *att_data)
{
    //BTM_TRACE_DEBUG0("adpcm_voice_encode");
    uint8_t buffer[MAX_FRAME_SIZE];
    int size;
    int frame_size;
    UINT8       *p = NULL;
    FILE *fp;
    fp = fopen (RTK_STORAGE_PCM_FILE, "a+");
    if (fp == NULL)
    {
       BTM_TRACE_WARNING0("open file failed\n");
       return FALSE;
    }

    p = (UINT8*)(att_data->data+3);
    size = att_data->data_len - 3;

    /* we must receive 12 20-bytes packets followed by a 19-bytes packet */
    switch (size) {
    case 20:
        adpcm_rec_cb.n_20bytes_pkts++;
        if (adpcm_rec_cb.n_20bytes_pkts > 12){
            BTM_TRACE_DEBUG0("20bytes pkt is exceed 12");
            adpcm_rec_cb.n_20bytes_pkts = 1;
            memcpy(adpcm_rec_cb.buffer + (adpcm_rec_cb.n_20bytes_pkts - 1) * 20,p, 20);
        } else {
            memcpy(adpcm_rec_cb.buffer + (adpcm_rec_cb.n_20bytes_pkts - 1) * 20,p, 20);
        }
        break;
    case 19:
        if (adpcm_rec_cb.n_20bytes_pkts != 12) {
            BTM_TRACE_DEBUG0("20bytes pkt!=12,discard the frame");
            adpcm_rec_cb.n_20bytes_pkts = 0;
        } else {
            memcpy(adpcm_rec_cb.buffer + adpcm_rec_cb.n_20bytes_pkts * 20, p, 19);
            adpcm_rec_cb.n_20bytes_pkts = 0;
            frame_size = adpcm_decode(adpcm_rec_cb.adpcm_state, buffer, adpcm_rec_cb.buffer,ADPCM_ENCODED_FRAME_SIZE);
            BTM_TRACE_DEBUG1("frame size= %d",frame_size);
            if(frame_size == 1020)
            {
                fwrite(buffer, frame_size, 1, fp);
                if(adpcm_rec_cb.channel_status)
                {
                    if(isEmpty())
                    {
                        BTM_TRACE_DEBUG0("the buffer empty,send data to socket");
                        VOHOG_LOCK();
                        if(!UIPC_RTKBT_VR_Send_noblock(UIPC_CH_ID_RTKBT_VR_AUDIO, 0, buffer, frame_size))
                        {
                           BTM_TRACE_WARNING0("send data fail, save data to buffer");
                           saveDATAtobuffer(buffer, frame_size);
                        }
                        VOHOG_UNLOCK();
                    } else {
                        BTM_TRACE_DEBUG0("the buffer is not empty, save data to buffer");
                        saveDATAtobuffer(buffer, frame_size);
                    }
                } else {
                    if(!adpcm_rec_cb.channel_status)
                    {
                        BTM_TRACE_DEBUG0("socket is close");
                    }
                    saveDATAtobuffer(buffer, frame_size);
                }
            }else {
                BTM_TRACE_DEBUG0("frame_size is error");
            }
        }
        break;
    default:
        BTM_TRACE_DEBUG0("size is error");
    }
    //BTM_TRACE_DEBUG1("20bytes pkt= %d",adpcm_rec_cb.n_20bytes_pkts);
    free(att_data);
    //fseek(fp,0,SEEK_END);
    //int lSize = ftell(fp);
    //BTM_TRACE_WARNING1("file length %d\n",lSize);
    fclose(fp);
    return TRUE;
}

#endif
