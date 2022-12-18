#include <unistd.h>
#include <sys/time.h>
#include "btm_int.h"
#include "uipc.h"
#include "bt_utils.h"
#include "bt_trace.h"
#include "gki.h"
#include "gki_target.h"
#include "btui.h"
#include "sbc.h"
#include "audio_sco_hw.h"


#if (BTM_SCO_INCLUDED == TRUE)

#if BTM_DYNAMIC_MEMORY == FALSE
extern tBTM_CB  btm_cb;
#endif

#if (BTM_SCO_HCI_INCLUDED == TRUE )

static tBTUI_SCO_CODEC_CFG btui_sco_codec_cfg;
static UINT16 btui_sco_codec_handle = 0;

#define BTUI_SCO_CODEC_BLOCK_SIZE       (240)       //subbanks*blocklength*channel*2 = 8*15*1*2 = 240
static UINT8 pcm_buffer[BTUI_SCO_CODEC_BLOCK_SIZE*10];
static UINT32 pcm_buffer_idx = 0;

static INT32 btui_cb_sco_hci = FALSE;
struct btui_cfg_st btui_cfg = {TRUE,TRUE,TRUE};
struct btui_cb_st btui_cb = {FALSE};
static BOOLEAN      btui_chanel_status[UIPC_CH_NUM];
static sbc_t        sbc_enc;
static sbc_t        sbc_dec;
static BOOLEAN      msbc_init = FALSE;
static UINT32       evt_filter = 0;
static UINT32       evt_filter_cnt = 0;
struct timeval      evt_filter_tv;

UINT16 btui_msbc_h2[] = {0x0801,0x3801,0xc801,0xf801};

#define BTUI_SCO_OUT_RINGBUFSIZE    (8)
#ifdef BTUI_SCO_OUT_RINGBUFSIZE
static struct
{
    UINT32 ridx;
    UINT32 widx;
    UINT8  buf[BTUI_SCO_OUT_RINGBUFSIZE][SCO_OUT_BUFSIZE];
    UINT32 readptr[BTUI_SCO_OUT_RINGBUFSIZE];
}btui_sco_out_buffer;

static INT32 getscofrombuffer(UINT8 * buf, UINT32 len)
{
    INT32 res = 0;

    if(btui_sco_out_buffer.ridx == btui_sco_out_buffer.widx)
        return 0;

    if(btui_sco_out_buffer.readptr[btui_sco_out_buffer.ridx] > (SCO_OUT_BUFSIZE-len))
    {
        btui_sco_out_buffer.readptr[btui_sco_out_buffer.ridx] = 0;
        btui_sco_out_buffer.ridx ++;
        btui_sco_out_buffer.ridx %= BTUI_SCO_OUT_RINGBUFSIZE;
    }
    //BTM_TRACE_DEBUG4("UIPC_Read_noblock() ridx:%d widx:%d btui_sco_out_buffer.readptr[%d]=%d", btui_sco_out_buffer.ridx, btui_sco_out_buffer.widx,btui_sco_out_buffer.ridx,btui_sco_out_buffer.readptr[btui_sco_out_buffer.ridx]);

    if(btui_sco_out_buffer.ridx != btui_sco_out_buffer.widx)
    {
        memcpy(buf,&(btui_sco_out_buffer.buf[btui_sco_out_buffer.ridx][btui_sco_out_buffer.readptr[btui_sco_out_buffer.ridx]]),len);
        btui_sco_out_buffer.readptr[btui_sco_out_buffer.ridx] += len;
        res = len;
    }

    return res;
}
#endif
static void btui_sco_out_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event)
{
    switch(event)
    {
        case UIPC_OPEN_EVT:
            btui_chanel_status[ch_id] = TRUE;
            break;

        case UIPC_CLOSE_EVT:
            btui_chanel_status[ch_id] = FALSE;
            UIPC_Open(ch_id, btui_sco_out_cb);
            UIPC_Ioctl(ch_id, UIPC_SET_READ_POLL_TMO, 0);
            break;

        case UIPC_RX_DATA_EVT:
            break;

        case UIPC_RX_DATA_READY_EVT:
        {
            INT32 res_len,expect_len;
            BTM_TRACE_DEBUG2("%s: UIPC_Read_noblock() btui_sco_codec_cfg.p_cback %p", __FUNCTION__, btui_sco_codec_cfg.p_cback);
            if(btui_sco_codec_cfg.p_cback){
                res_len = UIPC_Read_noblock(ch_id, NULL, btui_sco_out_buffer.buf[btui_sco_out_buffer.widx], SCO_OUT_BUFSIZE);
                if(res_len > 0)
                {
                    BTM_TRACE_DEBUG4("%s: UIPC_Read_noblock() res_len %d, btui_sco_codec_cfg.cb_event %d, btui_sco_codec_handle %d", __FUNCTION__, res_len, btui_sco_codec_cfg.cb_event, btui_sco_codec_handle);
                    if(res_len != SCO_OUT_BUFSIZE)
                    {
                        BTM_TRACE_WARNING2("UIPC_Read_noblock() res_len=%d expect_len=%d", res_len, SCO_OUT_BUFSIZE);
                        memset(&(btui_sco_out_buffer.buf[btui_sco_out_buffer.widx][res_len]), 0, SCO_OUT_BUFSIZE-res_len);
                    }
                    if(((btui_sco_out_buffer.ridx + BTUI_SCO_OUT_RINGBUFSIZE -1 - btui_sco_out_buffer.widx)%BTUI_SCO_OUT_RINGBUFSIZE) > 0)
                    {
                        btui_sco_out_buffer.widx ++;
                        btui_sco_out_buffer.widx %= BTUI_SCO_OUT_RINGBUFSIZE;
                    }else
                        BTM_TRACE_WARNING2("UIPC_Read_noblock() ridx:%d widx:%d", btui_sco_out_buffer.ridx, btui_sco_out_buffer.widx);
                    btui_sco_codec_cfg.p_cback(btui_sco_codec_cfg.cb_event, btui_sco_codec_handle);
                }
            }else{
                UINT8 buf[48];
                BTM_TRACE_ERROR0("### no callbacks ###");
                while(UIPC_Read_noblock(UIPC_CH_ID_SCO_OUT, NULL, buf, sizeof(buf)) == sizeof(buf))
                    ;
            }
            break;
        }
        case UIPC_TX_DATA_READY_EVT:
            break;

        default :
            BTM_TRACE_ERROR1("### SCO-CHANNEL EVENT %d NOT HANDLED ###", event);
            break;
    }
}

static void btui_sco_in_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event)
{

    switch(event)
    {
        case UIPC_OPEN_EVT:
            btui_chanel_status[ch_id] = TRUE;
            UIPC_Ioctl(ch_id, UIPC_SET_SNDBUFSIZE, (void *)(SCO_IN_BUFSIZE*20));
            UIPC_Ioctl(ch_id, UIPC_REG_REMOVE_ACTIVE_READSET, NULL);
            break;

        case UIPC_CLOSE_EVT:
            btui_chanel_status[ch_id] = FALSE;
            UIPC_Open(ch_id, btui_sco_in_cb);
            UIPC_Ioctl(ch_id, UIPC_SET_READ_POLL_TMO, 0);
            break;

        case UIPC_RX_DATA_EVT:
            break;

        case UIPC_RX_DATA_READY_EVT:
            BTM_TRACE_ERROR1("%s UIPC_RX_DATA_READY_EVT", __FUNCTION__);
            break;

        case UIPC_TX_DATA_READY_EVT:
            BTM_TRACE_ERROR1("%s UIPC_TX_DATA_READY_EVT", __FUNCTION__);
            break;

        default :
            BTM_TRACE_ERROR1("### SCO-CHANNEL EVENT %d NOT HANDLED ###", event);
            break;
    }
}
static void btui_sco_ctrl_handler(tUIPC_CH_ID ch_id, char * cmd, int len)
{
    BTM_TRACE_ERROR3("btui_sco_ctrl_handler cmd(%d,%s,%d)",ch_id,cmd,len);
    if(strcmp(cmd,SCO_CTRL_GETSAMPLERATE) == 0)
    {
        if(btui_sco_codec_handle)
        {
            if(btm_cb.sco_cb.codec_in_use == BTM_SCO_CODEC_MSBC)
                strcat(cmd,"=16000");
            else
                strcat(cmd,"=8000");
        }else
            strcat(cmd,"=0");
        BTM_TRACE_ERROR3("btui_sco_ctrl_handler response(%d,%s,%d)",ch_id,cmd,len);
        UIPC_Send(ch_id, 0, (uint8_t*)cmd, strlen(cmd));
    }
}
static void btui_sco_ctrl_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event)
{
    char buf[64];
    int len;

    memset(buf,0,sizeof(buf));
    switch(event)
    {
        case UIPC_OPEN_EVT:
            btui_chanel_status[ch_id] = TRUE;
            break;

        case UIPC_CLOSE_EVT:
            btui_chanel_status[ch_id] = FALSE;
            UIPC_Open(ch_id, btui_sco_ctrl_cb);
            UIPC_Ioctl(ch_id, UIPC_SET_READ_POLL_TMO, 0);
            break;

        case UIPC_RX_DATA_EVT:
            break;

        case UIPC_RX_DATA_READY_EVT:
        {
            len = UIPC_Read(ch_id, 0, (uint8_t*)buf, sizeof(buf));
            if(len >= 0)
                btui_sco_ctrl_handler(ch_id, buf, len);
            break;
        }
        case UIPC_TX_DATA_READY_EVT:
            break;

        default :
            BTM_TRACE_ERROR1("### SCO-CHANNEL EVENT %d NOT HANDLED ###", event);
            break;
    }
}

void msbc_setup()
{
    if(msbc_init)
    {
        sbc_reinit(&sbc_enc,0);
        sbc_reinit(&sbc_dec,0);
    }else{
        memset(&sbc_enc,0,sizeof(sbc_enc));
        memset(&sbc_dec,0,sizeof(sbc_dec));
        sbc_init(&sbc_enc,0);
        sbc_init(&sbc_dec,0);
        msbc_init = TRUE;
    }
}
void btui_sco_init(void)
{
    BTM_TRACE_ERROR1("%s", __FUNCTION__);
    msbc_setup();
    memset(btui_chanel_status,0,sizeof(btui_chanel_status));
    memset(&btui_sco_codec_cfg,0,sizeof(btui_sco_codec_cfg));
    memset(&btui_sco_out_buffer,0,sizeof(btui_sco_out_buffer));
    btui_sco_codec_cfg.pool_id = HCI_SCO_POOL_ID;
    UIPC_Init(NULL);
    UIPC_Open(UIPC_CH_ID_SCO_OUT, btui_sco_out_cb);
    UIPC_Ioctl(UIPC_CH_ID_SCO_OUT, UIPC_SET_READ_POLL_TMO, 0);
    UIPC_Open(UIPC_CH_ID_SCO_IN, btui_sco_in_cb);
    UIPC_Ioctl(UIPC_CH_ID_SCO_IN, UIPC_SET_READ_POLL_TMO, 0);
    UIPC_Open(UIPC_CH_ID_SCO_CTRL, btui_sco_ctrl_cb);
    UIPC_Ioctl(UIPC_CH_ID_SCO_CTRL, UIPC_SET_READ_POLL_TMO, 0);
}

BOOLEAN btui_sco_codec_init(UINT32 rx_bw, UINT32 tx_bw)
{
    msbc_setup();
    BTM_TRACE_ERROR3("%s(%d,%d)", __FUNCTION__, rx_bw, tx_bw);
    return TRUE;
}

BOOLEAN btui_sco_codec_open(tBTUI_SCO_CODEC_CFG * cfg)
{
    BTM_TRACE_ERROR4("%s({pool_id:%d,pkt_size:%d,cb_event:%d,p_cback:*})", __FUNCTION__, cfg->pool_id, cfg->pkt_size, cfg->cb_event);

    memcpy(&btui_sco_codec_cfg, cfg, sizeof(tBTUI_SCO_CODEC_CFG));
    return TRUE;
}

BOOLEAN btui_sco_codec_start(UINT16 handle)
{
    BTM_TRACE_ERROR2("%s(%d)", __FUNCTION__, handle);
    btui_sco_codec_handle = handle;
    return TRUE;
}

BOOLEAN btui_sco_codec_close()
{
    BTM_TRACE_ERROR1("%s()", __FUNCTION__);
    btui_sco_codec_handle = 0;
    return TRUE;
}

#define HCI_DATA_HANDLE_MASK 0x0FFF

#define HCID_GET_HANDLE_EVENT(p)  (UINT16)((*((UINT8 *)((p) + 1) + p->offset) + \
                                           (*((UINT8 *)((p) + 1) + p->offset + 1) << 8)))

#define HCID_GET_HANDLE(u16) (UINT16)((u16) & HCI_DATA_HANDLE_MASK)
#define HCI_DATA_EVENT_MASK   3
#define HCI_DATA_EVENT_OFFSET 12
#define HCID_GET_EVENT(u16)   (UINT8)(((u16) >> HCI_DATA_EVENT_OFFSET) & HCI_DATA_EVENT_MASK)

BOOLEAN btui_sco_codec_inqdata(BT_HDR  *p_buf)
{
    static UINT8    pcm[BTUI_SCO_CODEC_BLOCK_SIZE];
    static UINT32   pcm_idx = 0;
    UINT8       *p = NULL;
    UINT8       pkt_size = 0;
    UINT8       pkt_status = 0;
    UINT16      handle;
    INT32       len;

#ifdef RTK_BT_DEBUG
    static UINT32   progress = 0;
    progress++;
    if((progress % 200) == 0)
        BTM_TRACE_ERROR5("btui_sco_codec_inqdata() codec:%d, evt:0x%08x, layer:%d, off:0x%08x, len:0x%08x", btm_cb.sco_cb.codec_in_use, p_buf->event, p_buf->layer_specific, p_buf->offset, p_buf->len);
#endif

    p = (UINT8 *)(p_buf + 1) + p_buf->offset;
    STREAM_TO_UINT16 (handle, p);
    pkt_status = HCID_GET_EVENT(handle);
    handle   = HCID_GET_HANDLE (handle);
    STREAM_TO_UINT8 (pkt_size, p);
    if(pkt_status == 2)
    {
        GKI_freebuf(p_buf);
        return TRUE;
    }

    if(btm_cb.sco_cb.codec_in_use != BTM_SCO_CODEC_MSBC)
    {
//      p = (UINT8 *)(p_buf + 1) + p_buf->offset + 3;
        if((pcm_idx+(p_buf->len - 3)) > BTUI_SCO_CODEC_BLOCK_SIZE)
        {
            if(pcm_idx != BTUI_SCO_CODEC_BLOCK_SIZE)
                BTM_TRACE_WARNING2("btui_sco_codec_inqdata() codec:%d, pcm_idx=%d", btm_cb.sco_cb.codec_in_use, pcm_idx);
            if(btui_chanel_status[UIPC_CH_ID_SCO_IN])
            {
                len = UIPC_Send_noblock(UIPC_CH_ID_SCO_IN, 0, pcm, BTUI_SCO_CODEC_BLOCK_SIZE);
                if(len != BTUI_SCO_CODEC_BLOCK_SIZE)
                    BTM_TRACE_WARNING3("btui_sco_codec_inqdata() codec:%d, UIPC_Send_noblock(%d) return %d", btm_cb.sco_cb.codec_in_use, BTUI_SCO_CODEC_BLOCK_SIZE, len);
            }
            pcm_idx = 0;
        }
        memcpy(&pcm[pcm_idx],p, (p_buf->len - 3));
        pcm_idx += (p_buf->len - 3);
        GKI_freebuf(p_buf);
    }else{
#define BTUI_SBC_BLOCK_SIZE (60)
        static UINT8    sbc_dec_buf[BTUI_SBC_BLOCK_SIZE*40];
        static UINT32   sbc_dec_widx = 0;
        static UINT32   sbc_dec_ridx = 0;
        static UINT32   sbc_dec_seq = 0;
        int writen = 0,res = 0;

        if((pkt_size != 48)||((pkt_status != 0)&&(pkt_status != 2)))
            BTM_TRACE_WARNING4("btui_sco_codec_inqdata() pkt_status %d, pkt_size %d, sbc_dec_widx=[%d-%d]", pkt_status, pkt_size,sbc_dec_widx,sbc_dec_widx+(p_buf->len-3));
        if(sbc_dec_ridx == sbc_dec_widx)
        {
            if(sbc_dec_ridx != 240)
                BTM_TRACE_DEBUG2("sbc_dec: reset to head(%d - %d)", sbc_dec_ridx, sbc_dec_widx);
            sbc_dec_widx = 0;
            sbc_dec_ridx = 0;
        }else if((sbc_dec_ridx > sizeof(sbc_dec_buf)/2))
        {
            BTM_TRACE_DEBUG4("sbc_dec: data move to head(%d - %d) [%02x %02x]", sbc_dec_ridx, sbc_dec_widx,sbc_dec_buf[sbc_dec_ridx],sbc_dec_buf[sbc_dec_ridx+1]);
            memcpy(sbc_dec_buf,&sbc_dec_buf[sbc_dec_ridx],sbc_dec_widx-sbc_dec_ridx);
            sbc_dec_widx -= sbc_dec_ridx;
            sbc_dec_ridx = 0;
        }

        memcpy(&sbc_dec_buf[sbc_dec_widx],p,(p_buf->len-3));
        sbc_dec_widx += (p_buf->len - 3);
        GKI_freebuf(p_buf);

        while((sbc_dec_ridx+BTUI_SBC_BLOCK_SIZE) <= sbc_dec_widx)
        {
            if((sbc_dec_buf[sbc_dec_ridx]==0x01)&&((sbc_dec_buf[sbc_dec_ridx+1]&0x0f)==0x08))
            {
//              BTM_TRACE_ERROR4("got frame sbc_dec_ridx[%d-%d] [%02x%02x]",sbc_dec_ridx,sbc_dec_ridx+60,sbc_dec_buf[sbc_dec_ridx+1],sbc_dec_buf[sbc_dec_ridx]);
                if(sbc_dec_seq != ((sbc_dec_buf[sbc_dec_ridx+1] >> 5)&0x3))
                {
                    BTM_TRACE_WARNING2("Seq %d Expected %d",((sbc_dec_buf[sbc_dec_ridx+1] >> 5)&0x3),sbc_dec_seq);
                    sbc_dec_seq = ((sbc_dec_buf[sbc_dec_ridx+1] >> 5)&0x3);
                }
                sbc_dec_ridx += 2;

                res = sbc_decode(&sbc_dec, &sbc_dec_buf[sbc_dec_ridx], sbc_dec_widx-sbc_dec_ridx, pcm, BTUI_SCO_CODEC_BLOCK_SIZE, &writen);
                if(res > 0)
                {
                    if(btui_chanel_status[UIPC_CH_ID_SCO_IN])
                    {
                        len = UIPC_Send_noblock(UIPC_CH_ID_SCO_IN, 0, pcm, writen);
                        if(len != writen)
                            BTM_TRACE_WARNING3("btui_sco_codec_inqdata() codec:%d, UIPC_Send_noblock(%d) return %d", btm_cb.sco_cb.codec_in_use, writen, len);
                    }
                    if(writen != 240)
                        BTM_TRACE_WARNING2("sbc_decode res:%d writen:%d", res, writen);
                    sbc_dec_ridx += res;
                    if(sbc_dec_buf[sbc_dec_ridx] != 0x01) // 1 byte padding
                        sbc_dec_ridx++;
                    sbc_dec_seq ++;
                    sbc_dec_seq %= 4;
                }else{
                    BTM_TRACE_WARNING3("sbc_decode fail[res=%d] %d[%02x]",res,sbc_dec_ridx,sbc_dec_buf[sbc_dec_ridx]);
                }
            }else{
//              BTM_TRACE_ERROR2("sbc_decode skip %d[%02x]",sbc_dec_ridx,sbc_dec_buf[sbc_dec_ridx]);
                sbc_dec_ridx++;
            }
        }
    }
    return TRUE;
}
#define BTM_PCM_BLOCK_SIZE  (48)
BOOLEAN btui_sco_codec_readbuf(BT_HDR  **pp_buf)
{
    static BT_HDR * p_buf = NULL;
    UINT8       *p;
    UINT32      len;
    static UINT8    pcm[BTUI_SCO_CODEC_BLOCK_SIZE];
    static UINT32   pcm_idx = 0;
#define BTUI_SCO_ENC_BUF_SIZE (60*5)
    static UINT8    sbc_enc_buf[BTUI_SCO_ENC_BUF_SIZE];
    static UINT32   pcm_enc_widx = 0;
    static UINT32   pcm_enc_ridx = 0;
    static UINT32   pcm_enc_seq = 0;

#ifdef RTK_BT_DEBUG
    static UINT32   progress = 0;
    progress++;
    if((progress % 200) == 0)
        BTM_TRACE_ERROR1("btui_sco_codec_readbuf, codec_in_use %d", btm_cb.sco_cb.codec_in_use);
#endif

    if(btm_cb.sco_cb.codec_in_use != BTM_SCO_CODEC_MSBC)
    {
        if(p_buf == NULL)
            p_buf = GKI_getpoolbuf(btui_sco_codec_cfg.pool_id); // 3 for HCI SCO header's length
        if(p_buf == NULL)
        {
            *pp_buf = NULL;
            evt_filter &= ~UIPC_RX_DATA_READY_EVT;
            return FALSE;
        }
        p_buf->offset = 3;
        p = (UINT8 *)(p_buf + 1) + 3;
        p_buf->len = getscofrombuffer(p, BTM_PCM_BLOCK_SIZE);
        if(p_buf->len > 0){
            *pp_buf = p_buf;
            p_buf = NULL;
        }else{
            *pp_buf = NULL;
            evt_filter &= ~UIPC_RX_DATA_READY_EVT;
//          GKI_freebuf(p_buf);
        }
        return TRUE;
    }else{
        if((pcm_enc_widx - pcm_enc_ridx) >=  BTM_SCO_DATA_SIZE_MAX)
        {
            p_buf = GKI_getpoolbuf(btui_sco_codec_cfg.pool_id); // 3 for HCI SCO header's length
            if(p_buf == NULL)
            {
                BTM_TRACE_ERROR0("btui_sco_codec_readbuf: Failed to get GKI pool buf");
                *pp_buf = NULL;
                return FALSE;
            }
            p_buf->offset = 3;
            p = (UINT8 *)(p_buf + 1) + 3;
            memcpy(p, &sbc_enc_buf[pcm_enc_ridx], BTM_SCO_DATA_SIZE_MAX);
            pcm_enc_ridx += BTM_SCO_DATA_SIZE_MAX;
            p_buf->len = BTM_SCO_DATA_SIZE_MAX;

            *pp_buf = p_buf;
            return TRUE;
        }else{
#if 0
            memcpy(sbc_enc_buf, &sbc_enc_buf[pcm_enc_ridx], pcm_enc_widx - pcm_enc_ridx);
            pcm_enc_widx -= pcm_enc_ridx;
            pcm_enc_ridx = 0;
#endif
        }

        if(pcm_enc_widx == pcm_enc_ridx)
        {
//          BTM_TRACE_ERROR2("sbc_encode reset to head(%d,%d)", pcm_enc_ridx, pcm_enc_widx);
            pcm_enc_ridx = pcm_enc_widx = 0;
        }
        len = getscofrombuffer(&pcm[pcm_idx], (BTUI_SCO_CODEC_BLOCK_SIZE-pcm_idx));
        while(len > 0){
            pcm_idx += len;
            if(pcm_idx >= BTUI_SCO_CODEC_BLOCK_SIZE)
            {
                int writen = 0;

                pcm_idx = 0;

                if(sbc_encode(&sbc_enc, pcm, BTUI_SCO_CODEC_BLOCK_SIZE, &sbc_enc_buf[pcm_enc_widx+2], (BTUI_SCO_ENC_BUF_SIZE-pcm_enc_widx-2), &writen) <= 0){
                    BTM_TRACE_ERROR3("sbc_encode BTUI_SCO_CODEC_BLOCK_SIZE:%d pcm_enc_widx:%d BTUI_SCO_ENC_BUF_SIZE:%d fail", BTUI_SCO_CODEC_BLOCK_SIZE, pcm_enc_widx, BTUI_SCO_ENC_BUF_SIZE);
                }else{
                    *(UINT16*)(&(sbc_enc_buf[pcm_enc_widx])) = btui_msbc_h2[pcm_enc_seq%4];
                    pcm_enc_seq ++;
                    pcm_enc_widx += writen+2;
                    sbc_enc_buf[pcm_enc_widx++] = 0x00; //pad
                }
                if((pcm_enc_widx - pcm_enc_ridx) >=  BTM_SCO_DATA_SIZE_MAX)
                {
                    p_buf = GKI_getpoolbuf(btui_sco_codec_cfg.pool_id); // 3 for HCI SCO header's length
                    if(p_buf == NULL)
                    {
                        *pp_buf = NULL;
                        evt_filter &= ~UIPC_RX_DATA_READY_EVT;
                        return FALSE;
                    }
                    p_buf->offset = 3;
                    p = (UINT8 *)(p_buf + 1) + 3;
                    memcpy(p, &sbc_enc_buf[pcm_enc_ridx], BTM_SCO_DATA_SIZE_MAX);
                    pcm_enc_ridx += BTM_SCO_DATA_SIZE_MAX;
                    p_buf->len = BTM_SCO_DATA_SIZE_MAX;

                    *pp_buf = p_buf;
                    return TRUE;
                }
            }
            len = getscofrombuffer(&pcm[pcm_idx], (BTUI_SCO_CODEC_BLOCK_SIZE-pcm_idx));
        }
        *pp_buf = 0;
        evt_filter &= ~UIPC_RX_DATA_READY_EVT;
        return FALSE;
    }

    return TRUE;
}

tBTM_STATUS BTM_ConfigScoPath (tBTM_SCO_ROUTE_TYPE path,tBTM_SCO_DATA_CB *p_sco_data_cb,tBTM_SCO_PCM_PARAM *p_pcm_param,BOOLEAN err_data_rpt)
{
    if(p_pcm_param != NULL){
        BTM_TRACE_ERROR6("BTM_ConfigScoPath(%d,*,{rate:%d,frame_type:%d,sync_mode:%d,clock_mode:%d},%d)", path, p_pcm_param->pcm_intf_rate, p_pcm_param->frame_type, p_pcm_param->sync_mode, p_pcm_param->clock_mode, err_data_rpt);
    }else{
        BTM_TRACE_ERROR2("BTM_ConfigScoPath(%d,*,*,%d)", path, err_data_rpt);
    }
    btm_cb.sco_cb.sco_path = path;
    btm_cb.sco_cb.p_data_cb = p_sco_data_cb;
    if(p_pcm_param != NULL)
    {
        memcpy(&(btm_cb.sco_cb.sco_pcm_param), p_pcm_param, sizeof(tBTM_SCO_PCM_PARAM));
    }

    return BTM_SUCCESS;
}
#endif
#if (BTM_WBS_INCLUDED == TRUE )
tBTM_STATUS BTM_SetWBSCodec (tBTM_SCO_CODEC_TYPE codec_type)
{
    BTM_TRACE_ERROR2("%s(%d)", __FUNCTION__, codec_type);

    return BTM_SUCCESS;
}
tBTM_STATUS BTM_ConfigI2SPCM (tBTM_SCO_CODEC_TYPE codec_type, UINT8 role, UINT8 sample_rate, UINT8 clock_rate)
{
    BTM_TRACE_ERROR5("%s(%d,%d,%d,%d)", __FUNCTION__, codec_type, role, sample_rate, clock_rate);

    btm_cb.sco_cb.codec_in_use = codec_type;
    if(codec_type == BTM_SCO_CODEC_MSBC)
    {
/*
        if(msbc_init)
        {
            sbc_reinit(&sbc_enc,0);
            sbc_reinit(&sbc_dec,0);
        }else{
            sbc_init(&sbc_enc,0);
            sbc_init(&sbc_dec,0);
            msbc_init = TRUE;
        }
*/
    }
    return BTM_SUCCESS;
}

#endif

#else

#if (BTM_SCO_HCI_INCLUDED == TRUE )
tBTM_STATUS BTM_ConfigScoPath (tBTM_SCO_ROUTE_TYPE path,tBTM_SCO_DATA_CB *p_sco_data_cb,tBTM_SCO_PCM_PARAM *p_pcm_param,BOOLEAN err_data_rpt)
{
    return BTM_SUCCESS;
}
#endif
#if (BTM_WBS_INCLUDED == TRUE )
tBTM_STATUS BTM_SetWBSCodec (tBTM_SCO_CODEC_TYPE codec_type)
{
    return BTM_SUCCESS;
}
tBTM_STATUS BTM_ConfigI2SPCM (tBTM_SCO_CODEC_TYPE codec_type, UINT8 role, UINT8 sample_rate, UINT8 clock_rate)
{
    return BTM_SUCCESS;
}
#endif

#endif


