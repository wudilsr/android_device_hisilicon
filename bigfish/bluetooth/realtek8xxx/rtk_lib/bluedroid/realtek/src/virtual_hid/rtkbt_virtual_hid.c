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
#include "bt_trace.h"
#include "btm_int.h"
#include "btm_api.h"
//#include "btm_api.h"

#include "rtkbt_virtual_hid.h"
#define POWER_KEY_SHORT 0
#define POWER_KEY_LONG 1

const char *rtk_dev_path = "/dev/uhid";
char *dev_name = "rtkbt_virtual_hid";
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
int last_key_index = -1;

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
                    BTM_TRACE_WARNING2("%s: Error: failed to open uhid, err:%s",
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
