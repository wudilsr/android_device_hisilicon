#include "rtkbt_ifly_voice.h"

#define RTKBT_IFLYTEK_STATE_IDLE 0x00
#define RTKBT_IFLYTEK_STATE_WAIT_ACK 0x01

#define RTKBT_IFLYTEK_EVENT_DATA_READY 0x00

tBTA_HH_DEV_CB *Global_p_dev_cb = NULL;
BOOLEAN Socket_Running = FALSE;

#define RTKBT_BUFFER_SIZE 40
#define RTKBT_PAKCET_SIZE 16
#define RTKBT_MAX_SUBFRAME 2
static struct
{
    UINT16 frame;
    UINT8 subframe;
    UINT8 widx;
    UINT8 buf[RTKBT_BUFFER_SIZE];
}RTKBT_frame_buffer;

static struct
{
    UINT8 state;
    UINT8 queue_enent;
    UINT8 buf[RTKBT_BUFFER_SIZE];
}RTKBT_control_block;

struct RcuStatusNotification
{
    unsigned char opcode;
    unsigned char args[8];
};

//receive voice data from HOGP, 16 bytes per packet, the third packet is 8 bytes + 8*0x00,
//compact them to 40 bytes and send it to iflytek via socket.
BOOLEAN RTKBT_Iflytek_send_data(tVOICE_HSDATA *voice_data)
{
    UINT8       *p = NULL;
    UINT8       pkt_size = 0;
    static UINT8 sbc_dec_buf_iflytek[RTKBT_BUFFER_SIZE];
    UINT16      frame = 0;
    UINT8       subframe = 0;
    UINT8       reserve = 0;
    BTM_TRACE_EVENT0("RTKBT_Iflytek_send_data");

    //frame(2)+subframe(1)+reserve(1)+data(16)
    p = (UINT8*)(voice_data->data);
    STREAM_TO_UINT16(frame, p);
    STREAM_TO_UINT8(subframe, p);
    STREAM_TO_UINT8(reserve, p);
    BTM_TRACE_DEBUG2("receive voice data frame:%d subframe: %d", frame,subframe);

    if(subframe == 0)
    {
        if(frame != RTKBT_frame_buffer.frame + 1)
        {
            BTM_TRACE_ERROR2("lost voice packet, now frame:%d, last frame: %d", frame, RTKBT_frame_buffer.frame);
        }
        RTKBT_frame_buffer.frame = frame;

        if(RTKBT_frame_buffer.subframe != RTKBT_MAX_SUBFRAME)
        {
            BTM_TRACE_ERROR2("lost subframe,frame last:%d, frame:%d",RTKBT_frame_buffer.subframe, subframe);
        }
        RTKBT_frame_buffer.subframe = subframe;

        RTKBT_frame_buffer.widx = 0;
        memcpy(&RTKBT_frame_buffer.buf[RTKBT_frame_buffer.widx], p, RTKBT_PAKCET_SIZE);
        RTKBT_frame_buffer.widx += RTKBT_PAKCET_SIZE;
    }
    else if (subframe == RTKBT_MAX_SUBFRAME)
    {
        if((frame != RTKBT_frame_buffer.frame) ||RTKBT_frame_buffer.subframe != RTKBT_MAX_SUBFRAME-1)
        {
            BTM_TRACE_ERROR0("the packet is error,discard");
            return FALSE;
        }
        else
	{
            RTKBT_frame_buffer.subframe = subframe;
            memcpy(&RTKBT_frame_buffer.buf[RTKBT_frame_buffer.widx], p, RTKBT_PAKCET_SIZE/2);
            RTKBT_frame_buffer.widx += RTKBT_PAKCET_SIZE/2;
            if(RTKBT_frame_buffer.widx == RTKBT_BUFFER_SIZE)
            {
		if(UIPC_RTKBT_VR_Send_noblock(UIPC_CH_ID_RTKBT_VR_AUDIO, 0, RTKBT_frame_buffer.buf, RTKBT_BUFFER_SIZE))
		{
			BTM_TRACE_ERROR0("send 40 bytes to iflytek success!");
			return TRUE;
		}
		else
		{
			BTM_TRACE_ERROR0("send 40 bytes to iflytek fail!");
			return FALSE;
		}
            }
        }
    }
    else
    {
        if((frame != RTKBT_frame_buffer.frame)||(RTKBT_frame_buffer.subframe+1) != subframe ||subframe > RTKBT_MAX_SUBFRAME)
        {
            BTM_TRACE_ERROR0("the subframe is error,discard");
            RTKBT_frame_buffer.subframe = 0;
	    RTKBT_frame_buffer.widx = 0;
            return FALSE;
        }
        else {
            RTKBT_frame_buffer.subframe = subframe;
            memcpy(&RTKBT_frame_buffer.buf[RTKBT_frame_buffer.widx], p, RTKBT_PAKCET_SIZE);
            RTKBT_frame_buffer.widx += RTKBT_PAKCET_SIZE;
        }
    }

    return TRUE;
}

static void read_data_and_process(void)
{
    UINT8 data[20];
    UINT32 n, i;
    BT_HDR *p_buf;
    UINT8 *p;

    n = UIPC_Read_noblock(UIPC_CH_ID_RTKBT_DATA, NULL, data, 20);

    /* detach on ctrl channel means audioflinger process was terminated */
    if (n == 0)
    {
        APPL_TRACE_EVENT0("CTRL CH DETACHED");
        UIPC_Close(UIPC_CH_ID_RTKBT_DATA);
        return;
    } else if (n > 0)
    {
	    if((p_buf = (BT_HDR *) GKI_getbuf((UINT16)(sizeof(BT_HDR) + n + 1))) != NULL)
	    {
	        memset(p_buf, 0, sizeof(BT_HDR) + n +1);
	        p_buf->len = n + 1;
	        *(UINT8 *)(p_buf + 1) = RTKBT_IFLYTEK_OUTPUT_DATA;
		p =(UINT8 *)(p_buf + 1) + 1;
		memcpy(p, data, n);
		APPL_TRACE_EVENT1("send data to RCU with len=%d", n);
	        bta_hh_le_write_rpt(Global_p_dev_cb,
	                            0,
	                            BTA_GATTC_TYPE_WRITE_NO_RSP,
	                            RTKBT_OUTPUT_REPORT_TYPE,
	                            p_buf,
	                            BTA_HH_SET_RPT_EVT);
	        GKI_freebuf(p_buf);
	    }
    }

    APPL_TRACE_EVENT0("wait for ack!");
    RTKBT_control_block.state = RTKBT_IFLYTEK_STATE_WAIT_ACK;
}

static void process_ack()
{
	APPL_TRACE_EVENT0("process ack!");
	if(RTKBT_control_block.state == RTKBT_IFLYTEK_STATE_WAIT_ACK)
	{
		RTKBT_control_block.state = RTKBT_IFLYTEK_STATE_IDLE;
		if(RTKBT_control_block.queue_enent == RTKBT_IFLYTEK_EVENT_DATA_READY)
			read_data_and_process();
	}
}

void RTKBT_Iflytek_process_data_from_RCU(UINT8 report_id, UINT8* data, UINT16 len)
{
	BTM_TRACE_EVENT2("RTKBT_Iflytek_process_input_data with report_id = %d, len = %d", report_id, len);
	if(report_id == RTKBT_IFLYTEK_INPUT_DATA)
		UIPC_RTKBT_VR_Send_noblock(UIPC_CH_ID_RTKBT_DATA, 0, data, len);
	else if (report_id == RTKBT_IFLYTEK_INPUT_ACK)
		process_ack();
}

static void RTKBT_Iflytek_process_data_from_socket(void)
{
	APPL_TRACE_EVENT0("RTKBT_Iflytek_recv_data");
	if(RTKBT_control_block.state == RTKBT_IFLYTEK_STATE_IDLE)
	{
		APPL_TRACE_EVENT0("state is idle!read date and send it.");
		read_data_and_process();
	} else if(RTKBT_control_block.state == RTKBT_IFLYTEK_STATE_WAIT_ACK)
	{
		APPL_TRACE_EVENT0("state is wait ack!queue this event!");
		RTKBT_control_block.queue_enent = RTKBT_IFLYTEK_EVENT_DATA_READY;
	}
}

static void RTKBT_Iflytek_recv_data_from_socket(void)
{
	APPL_TRACE_EVENT0("RTKBT_Iflytek_recv_data");
	if(RTKBT_control_block.state == RTKBT_IFLYTEK_STATE_IDLE)
	{
		APPL_TRACE_EVENT0("state is idle!read date and send it.");
		read_data_and_process();
	} else if(RTKBT_control_block.state == RTKBT_IFLYTEK_STATE_WAIT_ACK)
	{
		APPL_TRACE_EVENT0("state is wait ack!queue this event!");
		RTKBT_control_block.queue_enent = RTKBT_IFLYTEK_EVENT_DATA_READY;
	}
}

static void data_socket_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event)
{
    APPL_TRACE_DEBUG1("DATA-CTRL-CHANNEL EVENT %s", dump_uipc_event(event));

    switch(event)
    {
        case UIPC_OPEN_EVT:
            APPL_TRACE_DEBUG1("DATA-CTRL-CHANNEL EVENT %s", dump_uipc_event(event));
            break;

        case UIPC_CLOSE_EVT:
            if (Socket_Running)
                UIPC_Open(UIPC_CH_ID_RTKBT_DATA , data_socket_cb);
            break;

        case UIPC_RX_DATA_EVT:
            APPL_TRACE_EVENT0("btif_voice_ctrl_cb, the event is UIPC_RX_DATA_EVT");

        case UIPC_RX_DATA_READY_EVT:
            RTKBT_Iflytek_recv_data_from_socket();
            break;

        default :
            APPL_TRACE_ERROR1("### DATA-CTRL-CHANNEL EVENT %d NOT HANDLED ###", event);
            break;
    }
}

void RTKBT_Iflytek_set_dev_cb(tBTA_HH_DEV_CB *p_dev_cb)
{
   Global_p_dev_cb = p_dev_cb;
}

tBTA_HH_DEV_CB * RTKBT_Iflytek_get_dev_cb(void)
{
    return Global_p_dev_cb;
}

static UINT8 RTKBT_Iflytek_get_output_rpt_id(UINT32 remote_controller_id)
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

//send start/stop request to RCU.
void RTKBT_Iflytek_send_request(tBTA_HH_DEV_CB *p_dev_cb, UINT8 opcode)
{
    APPL_TRACE_DEBUG1("RTKBT_Iflytek_send_request!with opcode = %d", opcode);
    BT_HDR  *p_buf_voice;
    tBTA_HH_DEV_CB *p_dev_cb_temp;
    tBTA_HH_RPT_TYPE voice_output_r_type;
    UINT8 voice_output_rpt_id;
    UINT16 len;
    UINT32 remote_controller_id = RTKBT_VR_get_remote_controller_id();

    voice_output_rpt_id = RTKBT_Iflytek_get_output_rpt_id(remote_controller_id);
    voice_output_r_type = RTKBT_OUTPUT_REPORT_TYPE;

    p_dev_cb_temp = p_dev_cb;
    len = 0x02;
    if((p_buf_voice = (BT_HDR *) GKI_getbuf((UINT16)(sizeof(BT_HDR) + len))) != NULL)
    {
        memset(p_buf_voice, 0, sizeof(BT_HDR) + len);
        /*set the value of rec_stop_res*/
        p_buf_voice->len = len;
        *(UINT8 *)(p_buf_voice + 1) = voice_output_rpt_id;
        *((UINT8 *)(p_buf_voice + 1) + 1) = opcode;
        APPL_TRACE_DEBUG0("send write request");
        bta_hh_le_write_rpt(p_dev_cb_temp,
                            0,
                            BTA_GATTC_TYPE_WRITE_NO_RSP,
                            voice_output_r_type,
                            p_buf_voice,
                            BTA_HH_SET_RPT_EVT);
        GKI_freebuf(p_buf_voice);
    }
    else{
        APPL_TRACE_DEBUG0("get buf wrong!");
    }
}

static void RTKBT_Iflytek_recv_voice_ctrl_data(void)
{
    UINT8 cmd[9], opcode = 0xFF;
    int n, i;

    n = UIPC_Read(UIPC_CH_ID_RTKBT_VR_CTRL, NULL, cmd, 9);

    /* detach on ctrl channel means audioflinger process was terminated */
    if (n == 0)
    {
        APPL_TRACE_EVENT0("CTRL CH DETACHED");
        UIPC_Close(UIPC_CH_ID_RTKBT_VR_CTRL);
        /* we can operate only on datachannel, if af client wants to
           do send additional commands the ctrl channel would be reestablished */
        //btif_audiopath_detached();
        return;
    }

    APPL_TRACE_DEBUG1("receive voice-ctrl-cmd read num_of_data = %d ", n);
    for (i=0; i< n; i++)
		APPL_TRACE_DEBUG2("data[%d] = %d ", i, cmd[i]);
    //receive start or stop cmd from service
    if( 9 == n && (cmd[0] == 0x01 || cmd[0] == 0x02)) {
	//receive control command from iflytek
	opcode = cmd[0];
    } else{
        //clear the memory
        UIPC_Ioctl(UIPC_CH_ID_RTKBT_VR_CTRL,UIPC_REQ_RX_FLUSH,NULL);
        APPL_TRACE_EVENT0("it is wrong cmd send from service");
    }

    APPL_TRACE_EVENT1("opcode = %d",opcode);
    switch(opcode)
    {
        case VOHOG_CTRL_CMD_START:
            APPL_TRACE_EVENT0("start command!");
            if(RTKBT_Iflytek_get_dev_cb() != NULL) {
		 RTKBT_Iflytek_send_request(RTKBT_Iflytek_get_dev_cb(), VOHOG_CTRL_CMD_START);
            }
            else{
                APPL_TRACE_EVENT0("not start send record!");

            }
        break;

        case VOHOG_CTRL_CMD_STOP:
            APPL_TRACE_EVENT0("stop record!");
            //stop record
            if(RTKBT_Iflytek_get_dev_cb() != NULL)
                RTKBT_Iflytek_send_request(RTKBT_Iflytek_get_dev_cb(), 0x00);
        break;

        default:
            APPL_TRACE_ERROR0("Unknown cmd!");
        break;
    }

    APPL_TRACE_EVENT0("voice-ctrl-cmd DOWN!");
}


static void control_socketl_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event)
{
    APPL_TRACE_DEBUG1("VOICE-CTRL-CHANNEL EVENT %s", dump_uipc_event(event));

    switch(event)
    {
        case UIPC_OPEN_EVT:
            APPL_TRACE_DEBUG1("VOICE-CTRL-CHANNEL EVENT %s", dump_uipc_event(event));
            break;

        case UIPC_CLOSE_EVT:
           // if (HH_task_running)
           //     UIPC_Open(UIPC_CH_ID_RTKBT_VR_CTRL , btif_voice_ctrl_cb);
            break;

        case UIPC_RX_DATA_EVT:
            APPL_TRACE_EVENT0("btif_voice_ctrl_cb, the event is UIPC_RX_DATA_EVT");

        case UIPC_RX_DATA_READY_EVT:
            RTKBT_Iflytek_recv_voice_ctrl_data();
            break;

        default :
            APPL_TRACE_ERROR1("### VOICE-CTRL-CHANNEL EVENT %d NOT HANDLED ###", event);
            break;
    }
}


void RTKBT_Iflytek_init() {
	APPL_TRACE_DEBUG0("RTKBT_Iflytek_init to create ctrl and data socket");
	RTKBT_control_block.state = RTKBT_IFLYTEK_STATE_IDLE;
	while(TRUE != UIPC_Open(UIPC_CH_ID_RTKBT_VR_AUDIO, NULL))
	{
		usleep(10000);
		APPL_TRACE_DEBUG0("wait for close");
	}
	while(TRUE != UIPC_Open(UIPC_CH_ID_RTKBT_VR_CTRL , control_socketl_cb))
	{
		usleep(10000);
		APPL_TRACE_DEBUG0("wait for close");
	}
	while(TRUE != UIPC_Open(UIPC_CH_ID_RTKBT_DATA , data_socket_cb))
	{
		UIPC_Close(UIPC_CH_ID_RTKBT_DATA);
		usleep(10000);
		APPL_TRACE_DEBUG0("wait for close");
	}

	Socket_Running = TRUE;
}

/*
typedef struct
{
    unsigned char opcode;//0xFF ctrl socket close by server
    unsigned char param[8];
} t_vf_sock_param __attribute__ ((packed));*/
void RTKBT_Iflytek_cleanup() {
	APPL_TRACE_DEBUG0("RTKBT_Iflytek_cleanup to close ctrl and data socket");
	UINT8 data[9] = {0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
        UIPC_RTKBT_VR_Send_noblock(UIPC_CH_ID_RTKBT_VR_CTRL, 0, data, 9);
        UIPC_Close(UIPC_CH_ID_RTKBT_VR_CTRL);
        UIPC_Close(UIPC_CH_ID_RTKBT_VR_AUDIO);
	UIPC_Close(UIPC_CH_ID_RTKBT_DATA);
	Socket_Running = FALSE;
}
INT32 RTKBT_Iflytek_NotifyRcuStatus(unsigned char status,bt_bdaddr_t * addr)
{
    struct RcuStatusNotification notification;
    INT32 res=0;

    notification.opcode = 0xfe;
    notification.args[0] = status;
    memcpy(&notification.args[1], addr, 6);
    notification.args[7] = 0;
    res = UIPC_Send(UIPC_CH_ID_RTKBT_VR_CTRL, 0, (UINT8*)&notification,sizeof(notification));
    APPL_TRACE_DEBUG2("RTKBT_NotifyRcuStatus status=%d res = %d\n", status, res);
    APPL_TRACE_DEBUG6("RTKBT_NotifyRcuStatus Addr:%02x:%02x:%02x:%02x:%02x:%02x)\n", addr->address[0], addr->address[1], addr->address[2], addr->address[3], addr->address[4], addr->address[5]);
    return res;
}

