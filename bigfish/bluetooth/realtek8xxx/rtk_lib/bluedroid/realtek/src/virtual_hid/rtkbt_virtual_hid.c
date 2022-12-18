#include <ctype.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <linux/uhid.h>
#include "btif_hh.h"
#include "bta_api.h"
#include "bta_hh_api.h"
#include "bta_hh_co.h"
#include "bt_trace.h"
#include "btm_int.h"
#include "btm_api.h"
#include "btif_hh.h"
#include <../../bta/hh/bta_hh_int.h>
//#include "btm_api.h"

#include "rtkbt_virtual_hid.h"

extern tBTA_HH_DEV_CB * RTKBT_Iflytek_get_dev_cb(void);

#define POWER_KEY_SHORT 0
#define POWER_KEY_LONG 1

const char *rtk_dev_path = "/dev/uhid";
char *dev_name = "rtkbt_virtual_hid";
char *rcu_dev_name = "iflytek_remote";
const UINT16 REPORT_LEN = 9;
const UINT16 PRODUCT_ID = 0x2850;
const UINT16 VENDOR_ID = 0x0bda;
const UINT16 VERSION = 0;
const UINT8 CONTROL_CODE = 0;
UINT8 power_key_down[9]= {0x01,0x00,0x00,0x3b,0x00,0x00,0x00,0x00,0x00};
UINT8 down_down[9]= {0x01,0x00,0x00,0x51,0x00,0x00,0x00,0x00,0x00};
UINT8 right_down[9]= {0x01,0x00,0x00,0x4F,0x00,0x00,0x00,0x00,0x00};
UINT8 ok_down[9]= {0x01,0x00,0x00,0x28,0x00,0x00,0x00,0x00,0x00};
UINT8 key_up[9]= {0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
UINT8 vendor_command_tv_on[7]= {0x00,0x01,0x01,0x20,0x00,0x60,0x00};
UINT8 vendor_command_tv_off[7]= {0x00,0x00,0x01,0x0A,0x00,0x64,0x00};
int uhid_fd = -1;
int thread_id = -1;
int  keep_polling = 0;
int last_key_index = -1;

int rcu_uhid_fd = -1;

//keymap
#define MAP_LEN 177
UINT8 map[MAP_LEN] = {0x05,0x01,0x09,0x06,0xa1,0x01,0x85,0x01,0x05,0x07,0x19,0xe0,0x29,0xe7,0x15,0x00,0x25,0x01,0x75,0x01,
                    0x95,0x08,0x81,0x02,0x95,0x01,0x75,0x08,0x81,0x01,0x95,0x05,0x75,0x01,0x05,0x08,0x19,0x01,0x29,0x05,
                    0x91,0x02,0x95,0x01,0x75,0x03,0x91,0x01,0x95,0x06,0x75,0x08,0x15,0x00,0x25,0xa4,0x05,0x07,0x19,0x00,
                    0x29,0xa4,0x81,0x00,0xc0,0x05,0x01,0x09,0x02,0xa1,0x01,0x85,0x03,0x09,0x01,0xa1,0x00,0x05,0x09,0x19,
                    0x01,0x29,0x03,0x15,0x00,0x25,0x01,0x95,0x03,0x75,0x01,0x81,0x02,0x95,0x01,0x75,0x05,0x81,0x01,0x05,
                    0x01,0x09,0x30,0x09,0x31,0x09,0x38,0x15,0x81,0x25,0x7f,0x75,0x08,0x95,0x03,0x81,0x06,0xc0,0xc0,0x06,
                    0x12,0xff,0x0a,0x12,0xff,0xa1,0x01,0x85,0xfd,0x09,0x01,0x75,0x08,0x95,0x01,0x16,0x00,0x00,0x26,0xff,
                    0x00,0x19,0x00,0x29,0xff,0x81,0x00,0xc0,0x06,0x12,0xff,0x0a,0x12,0xff,0xa1,0x01,0x85,0xfc,0x09,0x01,
                    0x75,0x08,0x95,0xeb,0x16,0x00,0x00,0x26,0xff,0x00,0x19,0x00,0x29,0xff,0x81,0x00,0xc0};
static inline pthread_t create_thread(void *(*start_routine)(void *), void * arg){
    APPL_TRACE_DEBUG0("create_thread: entered");
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
    pthread_t thread_id = -1;
    if ( pthread_create(&thread_id, &thread_attr, start_routine, arg)!=0 )
    {
        APPL_TRACE_ERROR1("pthread_create : %s", strerror(errno));
        return -1;
    }
    APPL_TRACE_DEBUG0("create_thread: thread created successfully");
    return thread_id;
}
/* Internal function to parse the events received from UHID driver*/
static int uhid_event(int *p_fd)
{
    struct uhid_event ev;
    BT_HDR  *p_buf;
    UINT8 *data ;
    ssize_t ret;
    memset(&ev, 0, sizeof(ev));
#ifdef BLUETOOTH_RTK_VR
    btif_hh_device_t *p_dev_send = NULL;
    tBTA_HH_DEV_CB * p_dev = RTKBT_Iflytek_get_dev_cb();
    if(p_dev)
        p_dev_send = btif_hh_find_connected_dev_by_handle(p_dev->hid_handle);
#endif
    if(!p_fd)
    {
        APPL_TRACE_ERROR1("%s: Device not found",__FUNCTION__)
        return -1;
    }
    ret = read(*p_fd, &ev, sizeof(ev));
    if (ret == 0) {
        APPL_TRACE_ERROR2("%s: Read HUP on uhid-cdev %s", __FUNCTION__,
                                                 strerror(errno));
        return -EFAULT;
    } else if (ret < 0) {
        APPL_TRACE_ERROR2("%s:Cannot read uhid-cdev: %s", __FUNCTION__,
                                                strerror(errno));
        return -errno;
    } else if (ret != sizeof(ev)) {
        APPL_TRACE_ERROR3("%s:Invalid size read from uhid-dev: %ld != %lu",
                            __FUNCTION__, ret, sizeof(ev));
        return -EFAULT;
    }

    switch (ev.type) {
        case UHID_START:
            APPL_TRACE_DEBUG0("UHID_START from uhid-dev\n");
        break;

        case UHID_STOP:
            APPL_TRACE_DEBUG0("UHID_STOP from uhid-dev\n");
        break;

        case UHID_OPEN:
            APPL_TRACE_DEBUG0("UHID_OPEN from uhid-dev\n");
        break;

        case UHID_CLOSE:
            APPL_TRACE_DEBUG0("UHID_CLOSE from uhid-dev\n");
        break;

        case UHID_OUTPUT:
            APPL_TRACE_DEBUG2("vhid..uHID_OUTPUT: Report type = %d, report_size = %d"
                                ,ev.u.output.rtype, ev.u.output.size);
#ifdef BLUETOOTH_RTK_VR
            if(!p_dev_send)
                break;
            //Send SET_REPORT with feature report if the report type in output event is FEATURE
            if(ev.u.output.rtype == UHID_FEATURE_REPORT) {
                btif_hh_setreport(p_dev_send,BTHH_FEATURE_REPORT,ev.u.output.size,ev.u.output.data);
            } else if(ev.u.output.rtype == UHID_OUTPUT_REPORT) {
            if(ev.u.output.size > 0){
                if((p_buf = (BT_HDR *) GKI_getbuf((UINT16)(sizeof(BT_HDR) + ev.u.output.size ))) != NULL)
                {
                    memset(p_buf, 0, sizeof(BT_HDR) + ev.u.output.size);
                    p_buf->len = ev.u.output.size;
                    p_buf->layer_specific = BTA_HH_RPTT_OUTPUT;
                    data = (UINT8 *)(p_buf + 1);
                    memcpy(data, ev.u.output.data, ev.u.output.size);
                    APPL_TRACE_DEBUG0("BTA_HhSendData to send output data!");
                    BTA_HhSendData(p_dev_send->dev_handle, NULL, p_buf);
                    GKI_freebuf(p_buf);
                }
            } else {
                APPL_TRACE_DEBUG0("not send output data!");
              }
            } else {
                btif_hh_setreport(p_dev_send,BTHH_INPUT_REPORT,ev.u.output.size,ev.u.output.data);
            }
#endif
        break;

        case UHID_OUTPUT_EV:
            APPL_TRACE_DEBUG0("UHID_OUTPUT_EV from uhid-dev\n");
        break;

        case UHID_FEATURE:
            APPL_TRACE_DEBUG0("UHID_FEATURE from uhid-dev\n");
        break;

        case UHID_FEATURE_ANSWER:
            APPL_TRACE_DEBUG0("UHID_FEATURE_ANSWER from uhid-dev\n");
        break;

        default:
            APPL_TRACE_DEBUG1("Invalid event from uhid-dev: %u\n", ev.type);
    }

    return 0;
}
static void *poll_event_thread(void *arg)
{

    int *p_fd = arg;
    APPL_TRACE_DEBUG2("%s: Thread created fd = %d", __FUNCTION__, *p_fd);
    struct pollfd pfds[1];
    int ret;
	  int i = 0;
    pfds[0].fd = *p_fd;
    pfds[0].events = POLLIN;

    while(keep_polling){
        ret = poll(pfds, 1, 500);
        if (ret < 0) {
            APPL_TRACE_ERROR2("%s: Cannot poll for fds: %s\n", __FUNCTION__, strerror(errno));
            break;
        }
        if (pfds[0].revents & POLLIN) {
            APPL_TRACE_DEBUG0("btif_hh_poll_event_thread: POLLIN");
            ret = uhid_event(p_fd);
            if (ret){
                break;
            }
        }
    }
    thread_id = -1;
    return 0;
}

static inline void close_poll_thread(int thread_id)
{
    APPL_TRACE_DEBUG1("%s", __FUNCTION__);
    keep_polling = 0;
    if(thread_id > 0)
#ifdef BLUETOOTH_RTK
        pthread_detach(thread_id);
        return;
#endif
        pthread_join(thread_id,NULL);
    return;
}
static int uhid_write(int fd, const struct uhid_event *ev)
{
    ssize_t ret;
    ret = write(fd, ev, sizeof(*ev));
    if (ret < 0){
        int rtn = -errno;
        APPL_TRACE_ERROR2("%s: Cannot write to uhid:%s", __FUNCTION__, strerror(errno));
        return rtn;
    } else if (ret != sizeof(*ev)) {
        APPL_TRACE_ERROR3("%s: Wrong size written to uhid: %ld != %lu",
                                                    __FUNCTION__, ret, sizeof(*ev));
        return -EFAULT;
    } else {
        return 0;
    }
}

int send_power_key(UINT8 *key_report)
{
    if(uhid_fd < 0) {
        APPL_TRACE_DEBUG0("uhid_fd < 0 !!!");
    return 0;
    }
    APPL_TRACE_DEBUG0("send_power_key: UHID write");
    struct uhid_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_INPUT;
    ev.u.input.size = REPORT_LEN;
    if(REPORT_LEN > sizeof(ev.u.input.data)){
        APPL_TRACE_WARNING1("%s:report size greater than allowed size",__FUNCTION__);
        return -1;
    }

    memcpy(ev.u.input.data, key_report, REPORT_LEN);

    return uhid_write(uhid_fd, &ev);

}

void send_hid_info(int fd, char *dev_name, UINT16 vendor_id,
                             UINT16 product_id, UINT16 version, UINT8 ctry_code,
                             int dscp_len, UINT8 *p_dscp)
{
    int result;
    struct uhid_event ev;

    if (fd < 0) {
        BTM_TRACE_WARNING0("fd < 0!!!");
        return;
    }

    BTM_TRACE_WARNING4("%s: fd = %d, name = [%s], dscp_len = %d", __FUNCTION__,
                                                                    fd, dev_name, dscp_len);
    BTM_TRACE_WARNING5("%s: vendor_id = 0x%04x, product_id = 0x%04x, version= 0x%04x,"
                                                                    "ctry_code=0x%02x",__FUNCTION__,
                                                                    vendor_id, product_id,
                                                                    version, ctry_code);

//Create and send hid descriptor to kernel
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_CREATE;
    strncpy((char*)ev.u.create.name, dev_name, sizeof(ev.u.create.name) - 1);
    ev.u.create.rd_size = dscp_len;
    ev.u.create.rd_data = p_dscp;
    ev.u.create.bus = BUS_BLUETOOTH;
    ev.u.create.vendor = vendor_id;
    ev.u.create.product = product_id;
    ev.u.create.version = version;
    ev.u.create.country = ctry_code;
    result = uhid_write(fd, &ev);

    BTM_TRACE_WARNING4("%s: fd = %d, dscp_len = %d, result = %d", __FUNCTION__,
                                                                    fd, dscp_len, result);

    if (result) {
        BTM_TRACE_WARNING2("%s: Error: failed to send DSCP, result = %d", __FUNCTION__, result);

        /* The HID report descriptor is corrupted. Close the driver. */
        close(fd);
        uhid_fd = -1;
    }
}

BOOLEAN RTKBT_vhid_setup() {
    if(uhid_fd<0) {
        BTM_TRACE_WARNING0("RTKBT_uhid_setup");
        uhid_fd = open(rtk_dev_path, O_RDWR | O_CLOEXEC);
        if (uhid_fd < 0) {
            BTM_TRACE_WARNING2("%s: Error: failed to open rcu_uhid, err:%s",
                                                                    __FUNCTION__,strerror(errno));
            return FALSE;
        } else
            BTM_TRACE_WARNING2("%s: uhid fd = %d", __FUNCTION__, uhid_fd);
        send_hid_info(uhid_fd, dev_name, VENDOR_ID, PRODUCT_ID, VERSION, CONTROL_CODE, MAP_LEN, map);

    } else
        BTM_TRACE_WARNING0("RTKBT_uhid_setup already setup!");

    BTM_RegisterForVSEvents ((tBTM_VS_EVT_CB *)RTKBT_process_vendor_event, TRUE);
    //BTM_VendorSpecificCommand(0x91, sizeof(vendor_command_tv_off), vendor_command_tv_off, NULL);
    return TRUE;
}

BOOLEAN RTKBT_rcu_vhid_setup() {
    if(rcu_uhid_fd<0) {
        BTM_TRACE_WARNING0("RTKBT_uhid_setup");
            rcu_uhid_fd = open(rtk_dev_path, O_RDWR | O_CLOEXEC);
            if (rcu_uhid_fd < 0) {
                BTM_TRACE_WARNING2("%s: Error: failed to open rcu_uhid, err:%s",
                                                                            __FUNCTION__,strerror(errno));
                return FALSE;
            } else
                BTM_TRACE_WARNING2("%s: rcu_uhid fd = %d", __FUNCTION__, rcu_uhid_fd);
        send_hid_info(rcu_uhid_fd, rcu_dev_name, RCU_VENDOR_ID, RCU_PRODUCT_ID, RCU_VERSION, RCU_COUNTRYCODE, RCU_MAP_LEN, rcu_map);
        keep_polling = 1;
        thread_id = create_thread(poll_event_thread, (void*)&rcu_uhid_fd);
    } else
        BTM_TRACE_WARNING0("RTKBT_rcu_uhid_setup already setup!");
    return TRUE;
}

void RTKBT_vhid_destroy()
{
    BTM_TRACE_WARNING0("RTKBT_uhid_destroy");
    struct uhid_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_DESTROY;
    uhid_write(uhid_fd, &ev);
    close(uhid_fd);
    uhid_fd = -1;

    BTM_RegisterForVSEvents ((tBTM_VS_EVT_CB *)RTKBT_process_vendor_event, FALSE);

    //BTM_VendorSpecificCommand(0x91, sizeof(vendor_command_tv_off), vendor_command_tv_off, NULL);
}

void RTKBT_rcu_vhid_destroy() {
    BTM_TRACE_WARNING0("RTKBT_rcu_uhid_destroy");
    if(rcu_uhid_fd < 0)
        return;
    struct uhid_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_DESTROY;
    uhid_write(rcu_uhid_fd, &ev);
    close_poll_thread(thread_id);
    close(rcu_uhid_fd);
    rcu_uhid_fd = -1;
    thread_id = -1;
}

void RTKBT_process_vendor_event(UINT8 len, UINT8  *data)
{
        BTM_TRACE_WARNING0("RTKBT_send_vendor_event");
    BTM_TRACE_WARNING1("len = %d", len);
    int i, key_index, key_type;
    for(i=0; i<len; i++)
        BTM_TRACE_WARNING1("%d", data[i]);
    if(len == 3 && data[0] == 0x2F)
    {
        key_index = data[1];
        key_type = data[2];
    } else
        return;

    if(key_index == last_key_index)
        return;
    if(key_type == POWER_KEY_LONG)
    {
        //long press power key
        send_power_key(power_key_down);
        usleep(1000000);
        send_power_key(key_up);
        /*
        //down key to select power off
        usleep(200000);
        send_power_key(down_down);
        send_power_key(key_up);

        //ok key
        usleep(200000);
        send_power_key(ok_down);
        send_power_key(key_up);

        //cancel or Ok, to select OK
        usleep(200000);
        send_power_key(down_down);
        send_power_key(key_up);

        usleep(200000);
        send_power_key(right_down);
        send_power_key(key_up);

        usleep(200000);
        send_power_key(ok_down);
        send_power_key(key_up);
        */
    } else if(key_type == POWER_KEY_SHORT)
    {
        send_power_key(power_key_down);
        send_power_key(key_up);
    }

    last_key_index = key_index;
}

BOOLEAN RTKBT_send_rcu_data(UINT16 vendor_id, UINT16  product_id, UINT8 *p_rpt, UINT16 len)
{
    if((vendor_id == RCU_VENDOR_ID) && (product_id == RCU_PRODUCT_ID)) {
        if(rcu_uhid_fd < 0) {
        APPL_TRACE_DEBUG0("uhid_fd < 0 !!!");
        return FALSE;
    }
    APPL_TRACE_DEBUG0("RTKBT_send_rcu_data");
    struct uhid_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_INPUT;
    ev.u.input.size = len;
    if(len > sizeof(ev.u.input.data)){
        APPL_TRACE_WARNING1("%s:report size greater than allowed size",__FUNCTION__);
        return FALSE;
    }

    memcpy(ev.u.input.data, p_rpt, len);

    if(uhid_write(rcu_uhid_fd, &ev) < 0)
        return FALSE;
    }
    return TRUE;
}

