/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  Filename:      bt_vendor_brcm.c
 *
 *  Description:   Broadcom vendor specific library implementation
 *
 ******************************************************************************/

// CSR porting
#if 0
#define LOG_TAG "bt_vendor"

#include <utils/Log.h>
#include "bt_vendor_brcm.h"
#include "upio.h"
#include "userial_vendor.h"

#ifndef BTVND_DBG
#define BTVND_DBG FALSE
#endif

#if (BTVND_DBG == TRUE)
#define BTVNDDBG(param, ...) {ALOGD(param, ## __VA_ARGS__);}
#else
#define BTVNDDBG(param, ...) {}
#endif

/******************************************************************************
**  Externs
******************************************************************************/

void hw_config_start(void);
uint8_t hw_lpm_enable(uint8_t turn_on);
uint32_t hw_lpm_get_idle_timeout(void);
void hw_lpm_set_wake_state(uint8_t wake_assert);
#if (SCO_CFG_INCLUDED == TRUE)
void hw_sco_config(void);
#endif
void vnd_load_conf(const char *p_path);

/******************************************************************************
**  Variables
******************************************************************************/

bt_vendor_callbacks_t *bt_vendor_cbacks = NULL;
uint8_t vnd_local_bd_addr[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/******************************************************************************
**  Local type definitions
******************************************************************************/

/******************************************************************************
**  Static Variables
******************************************************************************/

static const tUSERIAL_CFG userial_init_cfg =
{
    (USERIAL_DATABITS_8 | USERIAL_PARITY_NONE | USERIAL_STOPBITS_1),
    USERIAL_BAUD_115200
};

/******************************************************************************
**  Functions
******************************************************************************/

/*****************************************************************************
**
**   BLUETOOTH VENDOR INTERFACE LIBRARY FUNCTIONS
**
*****************************************************************************/

static int init(const bt_vendor_callbacks_t* p_cb, unsigned char *local_bdaddr)
{
    ALOGI("init");

    if (p_cb == NULL)
    {
        ALOGE("init failed with no user callbacks!");
        return -1;
    }

#if (VENDOR_LIB_RUNTIME_TUNING_ENABLED == TRUE)
    ALOGW("*****************************************************************");
    ALOGW("*****************************************************************");
    ALOGW("** Warning - BT Vendor Lib is loaded in debug tuning mode!");
    ALOGW("**");
    ALOGW("** If this is not intentional, rebuild libbt-vendor.so ");
    ALOGW("** with VENDOR_LIB_RUNTIME_TUNING_ENABLED=FALSE and ");
    ALOGW("** check if any run-time tuning parameters needed to be");
    ALOGW("** carried to the build-time configuration accordingly.");
    ALOGW("*****************************************************************");
    ALOGW("*****************************************************************");
#endif

    userial_vendor_init();
    upio_init();

    vnd_load_conf(VENDOR_LIB_CONF_FILE);

    /* store reference to user callbacks */
    bt_vendor_cbacks = (bt_vendor_callbacks_t *) p_cb;

    /* This is handed over from the stack */
    memcpy(vnd_local_bd_addr, local_bdaddr, 6);

    return 0;
}


/** Requested operations */
static int op(bt_vendor_opcode_t opcode, void *param)
{
    int retval = 0;

    BTVNDDBG("op for %d", opcode);

    switch(opcode)
    {
        case BT_VND_OP_POWER_CTRL:
            {
                int *state = (int *) param;
                if (*state == BT_VND_PWR_OFF)
                    upio_set_bluetooth_power(UPIO_BT_POWER_OFF);
                else if (*state == BT_VND_PWR_ON)
                    upio_set_bluetooth_power(UPIO_BT_POWER_ON);
            }
            break;

        case BT_VND_OP_FW_CFG:
            {
                hw_config_start();
            }
            break;

        case BT_VND_OP_SCO_CFG:
            {
#if (SCO_CFG_INCLUDED == TRUE)
                hw_sco_config();
#else
                retval = -1;
#endif
            }
            break;

        case BT_VND_OP_USERIAL_OPEN:
            {
                int (*fd_array)[] = (int (*)[]) param;
                int fd, idx;
                fd = userial_vendor_open((tUSERIAL_CFG *) &userial_init_cfg);
                if (fd != -1)
                {
                    for (idx=0; idx < CH_MAX; idx++)
                        (*fd_array)[idx] = fd;

                    retval = 1;
                }
                /* retval contains numbers of open fd of HCI channels */
            }
            break;

        case BT_VND_OP_USERIAL_CLOSE:
            {
                userial_vendor_close();
            }
            break;

        case BT_VND_OP_GET_LPM_IDLE_TIMEOUT:
            {
                uint32_t *timeout_ms = (uint32_t *) param;
                *timeout_ms = hw_lpm_get_idle_timeout();
            }
            break;

        case BT_VND_OP_LPM_SET_MODE:
            {
                uint8_t *mode = (uint8_t *) param;
                retval = hw_lpm_enable(*mode);
            }
            break;

        case BT_VND_OP_LPM_WAKE_SET_STATE:
            {
                uint8_t *state = (uint8_t *) param;
                uint8_t wake_assert = (*state == BT_VND_LPM_WAKE_ASSERT) ? \
                                        TRUE : FALSE;

                hw_lpm_set_wake_state(wake_assert);
            }
            break;
    }

    return retval;
}

/** Closes the interface */
static void cleanup( void )
{
    BTVNDDBG("cleanup");

    upio_cleanup();

    bt_vendor_cbacks = NULL;
}

// Entry point of DLib
const bt_vendor_interface_t BLUETOOTH_VENDOR_LIB_INTERFACE = {
    sizeof(bt_vendor_interface_t),
    init,
    op,
    cleanup
};

#else

#define LOG_TAG "bt_vendor"

#include <utils/Log.h>
//#include "bt_vendor_brcm.h"
//#include "userial_vendor.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "bt_vendor_lib.h"
//#ifndef BTVND_DBG
#define BTVND_DBG TRUE
//#endif

//#if (BTVND_DBG == TRUE)
#define BTVNDDBG(param, ...) {ALOGE(param, ## __VA_ARGS__);}
//#else
//#define BTVNDDBG(param, ...) {}
//#endif

#define DEFAULT_BT_USB_DEVICE_NAME  "/dev/bt_usb0"
int usb_fd;

/******************************************************************************
**  Variables
******************************************************************************/

bt_vendor_callbacks_t *bt_vendor_cbacks = NULL;
uint8_t vnd_local_bd_addr[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/******************************************************************************
**  Local type definitions
******************************************************************************/

// Victor add
static int read_pskey(int fd, uint16_t key, uint16_t length, uint16_t stores, uint16_t* ps_value);
static int write_pskey(int fd, uint16_t key, uint16_t length, uint16_t stores, uint16_t* ps_value);
static int hci_send_bccmd(int fd, uint16_t type, uint16_t varid, uint8_t* buf, uint16_t payload_length);


static int init(const bt_vendor_callbacks_t* p_cb, unsigned char *local_bdaddr)
{
    BTVNDDBG("init");
    ALOGE("libbt_vendor.so int");
    if (p_cb == NULL)
    {
        ALOGE("init failed with no user callbacks!");
        return -1;
    }

    /* store reference to user callbacks */
    bt_vendor_cbacks = (bt_vendor_callbacks_t *) p_cb;

    /* This is handed over from the stack */
    memcpy(vnd_local_bd_addr, local_bdaddr, 6);
    return 0;
}

int usb_vendor_reset()
 {
	 static char  has_been_reseted = 0 ;
	 
	 if (has_been_reseted != 0 ) // only reset once 
		return 1;
		
	 has_been_reseted = 1;
     BTVNDDBG("usb_vendor_reset");
     int bt_usb_fd = -1;
     int count;
     char devName[255] = "/dev/bt_usb0";
 
     uint8_t BcCmdReset[22] = { 0x00, 0xFC, 0x13, 0xC2, 0x02, 0x00, 0x09,
                                                 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00,
                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
     
     do 
     {
        BTVNDDBG("usb_vendor_reset: try to open /dev/bt_usb0");
        bt_usb_fd = open(devName, O_RDWR); 
        usleep(500000);
     } while ( bt_usb_fd < 0 ) ;
    
     BTVNDDBG("usb_vendor_reset: open /dev/bt_usb0 ok, write reset commond");
     uint8_t channel = 5;
     struct iovec out[2];
     out[0].iov_base = &channel;
     out[0].iov_len  = 1;
     out[1].iov_base = BcCmdReset;
     out[1].iov_len  = 22; 
     writev(bt_usb_fd,out,2);
     close(bt_usb_fd);
     bt_usb_fd = -1;
     usleep(2000000);  // wait bt_usb0 to disapear
     do 
     {
        BTVNDDBG("usb_vendor_reset: waiting for /dev/bt_usb0 to go back") ;
        bt_usb_fd = open(devName, O_RDWR); 
        usleep(200000);
     } while ( bt_usb_fd < 0) ; 

     BTVNDDBG("usb_vendor_reset: finished");
     close(bt_usb_fd);
     return 1;
 }
 

void usb_vendor_close()
{
	BTVNDDBG("usb_vendor_close %d",usb_fd);
	    if(usb_fd > 0)
	close(usb_fd);
	usb_fd=-1;
}

int usb_vendor_open()
{
    BTVNDDBG("usb_vendor_open");
   
    int bt_usb_fd = -1;
    char devName[255] = DEFAULT_BT_USB_DEVICE_NAME;
#if 0    
    if(!usb_vendor_reset())
    {
        BTVNDDBG("couldn't reset the chip");
        return -1;
    }
#endif
	property_set("bluetooth.status","on");
    /* property_set("bluetooth.status","true");
    char btstate[20];
    while(property_get("bluetooth.status",btstate)) 
    {
	if(strcmp(btstate,"on") == 0) {
		BTVNDDBG("bluetooth turned on ");
		break;
	}
	else {
		BTVNDDBG("bluetoot status still %s",btstate);
		usleep(100000);
	}
    }
*/
    bt_usb_fd = open(devName, O_NONBLOCK|O_RDWR);    
    if(bt_usb_fd)
    {
        usb_fd = bt_usb_fd;
        BTVNDDBG(" usb device opened %d",bt_usb_fd);
    }
    return bt_usb_fd;
}

/** Requested operations */
static int op(bt_vendor_opcode_t opcode, void *param)
{
    int retval = 0;

    BTVNDDBG("op for %d", opcode);

    switch(opcode)
    {
        case BT_VND_OP_POWER_CTRL:
           /* {
                int *state = (int *) param ;
                if (*state == BT_VND_PWR_ON)
                {
                    BTVNDDBG("BT_VND_OP_POWER_CTRL POWER ON ");
                    usb_vendor_reset();
                }
            }*/
            break;

        case BT_VND_OP_FW_CFG:
            {
		if(bt_vendor_cbacks){
                   BTVNDDBG("BT_VND_OP_FW_CFG: Bluetooth Firmware and smd is initialized");
                   bt_vendor_cbacks->fwcfg_cb(BT_VND_OP_RESULT_SUCCESS);
                }
            }
            break;

        case BT_VND_OP_SCO_CFG:
            {
		bt_vendor_cbacks->scocfg_cb(BT_VND_OP_RESULT_SUCCESS);
            }
            break;

        case BT_VND_OP_USERIAL_OPEN:
            {
                int (*fd_array)[] = (int (*)[]) param;
                int fd, idx;

                fd = usb_vendor_open();

                if (fd != -1)
                {
                    for (idx=0; idx < CH_MAX; idx++)
                        (*fd_array)[idx] = fd;

                    retval = 1;
                }
                /* retval contains numbers of open fd of HCI channels */
                #if 0
                {
                  uint16_t ps_value[32];
                  int ret, i;
           
                  BTVNDDBG("Trying to read pskey_usr41");

                  ret = read_pskey(fd, 0x02b3, 2, 0x3, ps_value);

                  for(i=0; i<ret; i++){
                      BTVNDDBG("0x%4x", ps_value[i]);
                  }

                  BTVNDDBG("Trying to read pskey_usr42");

                  ret = read_pskey(fd, 0x02b4, 17, 0x3, ps_value);

                  for(i=0; i<ret; i++){
                      BTVNDDBG("0x%4x", ps_value[i]);
                  }

                  
                  BTVNDDBG("Trying to delete paired information from Bluetooth chip");

                  ps_value[0]=0xffff;
                  ps_value[1]=0xffff;
                  ret = write_pskey(fd, 0x02b3, 2, 0x1, ps_value);
                  
                }
                #endif
            }
            break;

        case BT_VND_OP_USERIAL_CLOSE:
        	usb_vendor_close();
            break;

        case BT_VND_OP_GET_LPM_IDLE_TIMEOUT:
            break;

        case BT_VND_OP_LPM_SET_MODE:
            {
                bt_vendor_cbacks->lpm_cb(BT_VND_OP_RESULT_SUCCESS); //dummy
            }
            break;

        case BT_VND_OP_LPM_WAKE_SET_STATE:
            break;
    }

    return retval;
}

/** Closes the interface */
static void cleanup( void )
{
    BTVNDDBG("cleanup");
    if(usb_fd > 0)
    {
        close(usb_fd);
        usb_fd = -1;
    }
    bt_vendor_cbacks = NULL;
}

// Entry point of DLib
const bt_vendor_interface_t BLUETOOTH_VENDOR_LIB_INTERFACE = {
    sizeof(bt_vendor_interface_t),
    init,
    op,
    cleanup
};

#if 0
#define BT_USB_IOV_SIZE 2

uint16_t seqno;

static int write_usb(int fd, uint8_t* p, uint16_t len)
{
      uint8_t channel;
      uint8_t ret;
      struct iovec out[BT_USB_IOV_SIZE];

      channel = 5;  //command
      out[0].iov_base = &channel;
      out[0].iov_len  = 1;
      out[1].iov_base = p;
      out[1].iov_len  = len;
      ret = writev(fd,out,BT_USB_IOV_SIZE);
      BTVNDDBG("write usb returned %d",ret);
      return len;

}

static int read_usb(int fd, uint8_t* buf, uint16_t* len)
{
  int n;
  uint8_t channel;
  struct iovec iosz[1];
  struct iovec io[BT_USB_IOV_SIZE];
  uint32_t data_len;

  iosz[0].iov_base = &data_len;
  iosz[0].iov_len = sizeof(data_len);

  n = readv(fd, iosz,1);

  BTVNDDBG("read_usb read data length return %d", n);
  if(n > 0){

    BTVNDDBG("data length %d", data_len);

    io[0].iov_base = &channel;
    io[0].iov_len  = sizeof(uint8_t);
    io[1].iov_base = buf;
    io[1].iov_len  = data_len;

    n = readv(fd, io, BT_USB_IOV_SIZE);
    BTVNDDBG("read_usb read data return %d", n);
    if(n > 0){
      return data_len;
    }
  }

  return -1;
}


#define BCCMD_TYPE_GETREQ  0x0000
#define BCCMD_TYPE_GETREP  0x0001
#define BCCMD_TYPE_SETREQ  0x0002

#define BCCMD_VARID_PS  0x7003
#define BCCMD_VARID_PS_SIZE  0x3006

#define BCCMD_STATUS_OK  0x0000
#define BCCMD_STATUS_NO_SUCH_VARID  0x0001
#define BCCMD_STATUS_TOO_BIG  0x0002
#define BCCMD_STATUS_NO_VALUE  0x0003
#define BCCMD_STATUS_BAD_REQ  0x0004
#define BCCMD_STATUS_NO_ACCESS  0x0005
#define BCCMD_STATUS_READ_ONLY  0x0006
#define BCCMD_STATUS_WRITE_ONLY  0x0007
#define BCCMD_STATUS_ERROR  0x0008
#define BCCMD_STATUS_PERMISSION_DENIED  0x0009
static int write_pskey(int fd, uint16_t key, uint16_t length, uint16_t stores, uint16_t* ps_value)
{
  uint8_t buf[256];
  uint16_t payload_length = length*2 + 6;
  uint16_t i;
  int n;

  buf[0] = key & 0xff;
  buf[1] = key >> 8;
  buf[2] = length & 0xff;
  buf[3] = length >> 8;
  buf[4] = stores & 0xff;
  buf[5] = stores >> 8;
  
  for(i=0; i<length; i++)
  {
    buf[6 + i*2] = (*(ps_value + i)) & 0xff;
    buf[7 + i*2] = (*(ps_value + i)) >> 8;
  }

  hci_send_bccmd(fd, BCCMD_TYPE_SETREQ, BCCMD_VARID_PS, buf, payload_length);

  usleep(200000);

  n = read_usb(fd, buf, sizeof(buf));
  if(n>0){
    uint16_t status;
/*
Byte 0 -- 0xFF (event code)
Byte 1 -- Parameter total length
Byte 2 -- Payload descriptor
Byte 3,4 -- Type
Byte 5,6 -- length
Byte 7.8 -- sqeno
Byte 9,10 -- varid
Byte 11,12 -- status
*/
    status = buf[12] << 8 | buf[11];
    if(status == BCCMD_STATUS_OK){
       BTVNDDBG("pskey write succeed");
       n = payload_length;
    }
    else{
      BTVNDDBG("pskey write failed, status 0x%4x", status);
      n= -1;
    }  
  
  }

  return n;
}


static int read_pskey(int fd, uint16_t key, uint16_t length, uint16_t stores, uint16_t* ps_value)
{
uint8_t buf[256];
uint16_t payload_length = length*2 + 6;
int n, i;

buf[0] = key & 0xff;
buf[1] = key >> 8;
buf[2] = length & 0xff;
buf[3] = length >> 8;
buf[4] = stores & 0xff;
buf[5] = stores >> 8;

hci_send_bccmd(fd, BCCMD_TYPE_GETREQ, BCCMD_VARID_PS, buf, payload_length);

usleep(200000);

n = read_usb(fd, buf, sizeof(buf));

if(n > 0){
  uint16_t status;
  uint16_t ps_value_length;
/*
Byte 0 -- 0xFF (event code)
Byte 1 -- Parameter total length
Byte 2 -- Payload descriptor
Byte 3,4 -- Type
Byte 5,6 -- length
Byte 7.8 -- sqeno
Byte 9,10 -- varid
Byte 11,12 -- status
Byte 13,14 -- key
Byte 15,16 -- length
Byte 17,18 -- stores
Byte 19,...  PS Value

*/

  status = buf[12] <<8 | buf[11];
  if(status == 0){
    ps_value_length = buf[16] << 8 | buf[15];
    BTVNDDBG("pskey read succeed, ps_value_length %d", ps_value_length);
    
    for(i=0;i<ps_value_length;i++)
      ps_value[i] = buf[19+i*2] | buf[20+i*2] << 8;

    n=ps_value_length;
  }
  else{
    BTVNDDBG("pskey read failed, error %d", status);
    n = -1;

  }

}

return n;
}


static int hci_send_bccmd(int fd, uint16_t type, uint16_t varid, uint8_t* buf, uint16_t payload_length)
{
uint8_t hci_command[256];
uint16_t length = (payload_length < 8) ? 9 : ((payload_length + 1) / 2) + 5;
uint8_t parameter_total_length = length*2 + 1;
uint16_t hci_command_length = parameter_total_length + 3;

// ???
//hci_command[0]=0x01;
// opcode OGF 0x3F OCF 0x0000
hci_command[0]=0x00;
hci_command[1]=0xFC;
// parameter total length
hci_command[2] = parameter_total_length;
// Payload descriptor : first packet, last packet, BCCMD channel
hci_command[3]=0xC2;
// type
hci_command[4]=type & 0xff;
hci_command[5]=type >> 8;
// length
hci_command[6]=length & 0xff;
hci_command[7]=length >> 9;
// seqno
seqno ++;
hci_command[8]=seqno & 0xff;
hci_command[9]=seqno >> 8;
// varid
hci_command[10]=varid & 0xff;
hci_command[11]=varid >> 8;
// status
hci_command[12]=0;
hci_command[13]=0;
// payload
memcpy(&hci_command[14], buf, payload_length);

return write_usb(fd, hci_command, hci_command_length);
}

#endif
#endif
