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
/***************************************************************************
 * This implementation is a modification of
 * userial.c (Copyright (C) 2009-2012) by Broadcom Corporation
 ***************************************************************************/

#define LOG_TAG "bt_usb"

#include <utils/Log.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include "bt_hci_bdroid.h"
//#include "userial.h"
#include "utils.h"
#include "bt_vendor_lib.h"
#include <sys/prctl.h>
#include <sys/uio.h>
#include "usb_csr.h"
/******************************************************************************
**  Constants & Macros
******************************************************************************/

#ifndef USB_DBG
#define USB_DBG FALSE
#endif

#if (USB_DBG == TRUE)
#define USBDBG(param, ...) {ALOGD(param, ## __VA_ARGS__);}
#else
#define USBDBG(param, ...) {}
#endif

#define MAX_SERIAL_PORT (USERIAL_PORT_3 + 1)
#define READ_LIMIT (BTHC_USERIAL_READ_MEM_SIZE - BT_HC_HDR_SIZE)

enum {
    USB_RX_EXIT,
    USB_RX_FLOW_OFF,
    USB_RX_FLOW_ON
};

#ifndef CSR_USB_DRIVER
#define CSR_USB_DRIVER 1
#endif

#ifdef CSR_USB_DRIVER
#define BT_USB_IOV_SIZE 2
#endif
/******************************************************************************
**  Externs
******************************************************************************/

extern bt_vendor_interface_t *bt_vnd_if;

/******************************************************************************
**  Local type definitions
******************************************************************************/

typedef struct
{
    int             fd;
    uint8_t         port;
    pthread_t       read_thread;
    BUFFER_Q        rx_q;
    HC_BT_HDR      *p_rx_hdr;
} tUSB_CB;

/******************************************************************************
**  Static variables
******************************************************************************/

static tUSB_CB usb_cb;
static volatile uint8_t usb_running = 0;

/******************************************************************************
**  Static functions
******************************************************************************/
static int signal_fds[2]={0,1};
static uint8_t rx_flow_on = TRUE;
static inline int create_signal_fds(fd_set* set)
{
    if(signal_fds[0]==0 && socketpair(AF_UNIX, SOCK_STREAM, 0, signal_fds)<0)
    {
        USBDBG("create_signal_sockets:socketpair failed, errno: %d", errno);
        return -1;
    }
    FD_SET(signal_fds[0], set);
    return signal_fds[0];
}
static inline int send_wakeup_signal(char sig_cmd)
{
    USBDBG("wakeup signal sent");
    return send(signal_fds[1], &sig_cmd, sizeof(sig_cmd), 0);
}
static inline char reset_signal()
{
    char sig_recv = -1;
    recv(signal_fds[0], &sig_recv, sizeof(sig_recv), MSG_WAITALL);
    return sig_recv;
}
static inline int is_signaled(fd_set* set)
{
    return FD_ISSET(signal_fds[0], set);
}

static int select_read(int fd, struct iovec *pbuf, int len)
{
    fd_set input;
    int n = 0, ret = -1;
    char reason = 0;

    while (usb_running)
    {
        /* Initialize the input fd set */
        FD_ZERO(&input);
        if (rx_flow_on == TRUE)
        {
            FD_SET(fd, &input);
        }
        int fd_max = create_signal_fds(&input);
        fd_max = fd_max > fd ? fd_max : fd;

        /* Do the select */
        n = select(fd_max+1, &input, NULL, NULL, NULL);
        if(is_signaled(&input))
        {
            USBDBG("signalled");
            reason = reset_signal();
            if (reason == USB_RX_EXIT)
            {
                USBDBG("RX termination");
                return -1;
            }
            else if (reason == USB_RX_FLOW_OFF)
            {
                USBDBG("RX flow OFF");
                rx_flow_on = FALSE;
            }
            else if (reason == USB_RX_FLOW_ON)
            {
                USBDBG("RX flow ON");
                rx_flow_on = TRUE;
            }
        }

        if (n > 0)
        {
            /* We might have input */
            if (FD_ISSET(fd, &input))
            {
                //ret = read(fd, pbuf, (size_t)len);
                ret = readv(fd, pbuf, len);
                if (0 == ret)
                    ALOGW( "read() returned 0!" );

                return ret;
            }
        }
        else if (n < 0)
            ALOGW( "select() Failed");
        else if (n == 0)
            ALOGW( "Got a select() TIMEOUT");

    }

    return ret;
}

static void *csr_usb_rx_thread(void * arg)
{
    int n;int i;
    uint8_t channel;
    struct iovec io[BT_USB_IOV_SIZE];
    struct iovec iosz[1];
    USBDBG("Entering csr usb_read_thread()");
    prctl(PR_SET_NAME, (unsigned long)"usb_read", 0, 0, 0);
    rx_flow_on = TRUE;
    usb_running = 1;
    uint8_t *read_buf;
     HC_BT_HDR *p_buf = NULL;

    while (usb_running)
    {
        uint32_t buflen; /* MessageStructure.buflen is of type CsrUint32 */

        iosz[0].iov_base = &buflen;
        iosz[0].iov_len = sizeof(buflen);

        n = select_read(usb_cb.fd, iosz,1);
        //n = readv(usb_cb.fd, iosz, 1);

        if (n > 0)
        {
            if (bt_hc_cbacks)
            {
                p_buf = (HC_BT_HDR *) bt_hc_cbacks->alloc( \
                                                BTHC_USERIAL_READ_MEM_SIZE);
            }
            else
                p_buf = NULL;

            if (p_buf != NULL)
            {
                p_buf->offset = 0;
                p_buf->layer_specific = 0;
            }
            else
            {
                utils_delay(100);
                ALOGW("usb_read_thread() failed to gain buffers");
                continue;
            }
        }
        else
        {
            /* read error, bail out */
            USBDBG("exiting thread 1");
            break;
        }

        io[0].iov_base = &channel;
        io[0].iov_len  = sizeof(uint8_t);
        io[1].iov_base = (uint8_t*)((uint8_t *) (p_buf + 1) + 1);
        io[1].iov_len  = buflen;

        //USBDBG("read...\n");
        n = select_read(usb_cb.fd, io, BT_USB_IOV_SIZE);
        //n = readv(usb_cb.fd, io, BT_USB_IOV_SIZE);
        if(n<0)
        {
            USBDBG("exiting thread 2");
            break;
        }
        USBDBG("readv return: n=%d, bufflen: %d, channel %d\n",n,buflen,channel);
        if (buflen > 0)
        {
           switch(channel)
           {
              case 5: //HCI
                 USBDBG("readv returned event data 0x%2x",*((uint8_t *)(p_buf+1)+1));
		*((uint8_t *) (p_buf + 1)) = 0x04;//event type. sachin todo
                break;
              case 6://ACL
                 USBDBG("readv returned acl data 0x%2x",*((uint8_t *)(p_buf+1)+1));
		*((uint8_t *) (p_buf + 1)) = 2;//acl type
                break;
              default:
		*((uint8_t *) (p_buf + 1)) = 0x04;
            }
            p_buf->len = (uint16_t)buflen + 1; //type added
            utils_enqueue(&(usb_cb.rx_q), p_buf);
            bthc_signal_event(HC_EVENT_RX);
        }
        read_buf = NULL;
    }
    usb_running = 0;
    USBDBG("Leaving usb_read_thread()");
    pthread_exit(NULL);

    return NULL;    // Compiler friendly
}

/*****************************************************************************
**   Userial API Functions
*****************************************************************************/

/*******************************************************************************
**
** Function        usb_init
**
** Description     Initializes the usb driver
**
** Returns         TRUE/FALSE
**
*******************************************************************************/
uint8_t usb_init(void)
{
    USBDBG("usb_init");
    memset(&usb_cb, 0, sizeof(tUSB_CB));
    usb_cb.fd = -1;
    utils_queue_init(&(usb_cb.rx_q));
    return TRUE;
}


/*******************************************************************************
**
** Function        usb_open
**
** Description     Open Bluetooth device with the port ID
**
** Returns         TRUE/FALSE
**
*******************************************************************************/
uint8_t usb_open(uint8_t port)
{
    struct sched_param param;
    int policy, result;
    pthread_attr_t thread_attr;
    int fd_array[CH_MAX];

    USBDBG("usb_open(port:%d)", port);

    if (usb_running)
    {
        /* Userial is open; close it first */
        usb_close();
        utils_delay(50);
    }

    /* Calling vendor-specific part */
    if (bt_vnd_if)
    {
        result = bt_vnd_if->op(BT_VND_OP_USERIAL_OPEN, &fd_array);

        if (result != 1)
        {
            USBDBG("usb_open: wrong numbers of open fd in vendor lib [%d]!",
                    result);
            USBDBG("usb_open: HCI UART expects only one open fd");
            bt_vnd_if->op(BT_VND_OP_USERIAL_CLOSE, NULL);
            return FALSE;
        }

        usb_cb.fd = fd_array[0];
    }
    else
    {
        USBDBG("usb_open: missing vendor lib interface !!!");
        USBDBG("usb_open: unable to open UART port");
        return FALSE;
    }

    if (usb_cb.fd == -1)
    {
        USBDBG("usb_open: failed to open UART port");
        return FALSE;
    }

    USBDBG( "fd = %d", usb_cb.fd);

    usb_cb.port = port;

    pthread_attr_init(&thread_attr);
    if (pthread_create(&(usb_cb.read_thread), &thread_attr, csr_usb_rx_thread, NULL) != 0 )
    {
        USBDBG("pthread_create failed!");
        return FALSE;
    }

    if(pthread_getschedparam(usb_cb.read_thread, &policy, &param)==0)
    {
        policy = BTHC_LINUX_BASE_POLICY;
#if (BTHC_LINUX_BASE_POLICY!=SCHED_NORMAL)
        param.sched_priority = BTHC_USERIAL_READ_THREAD_PRIORITY;
#endif
        result = pthread_setschedparam(usb_cb.read_thread, policy, &param);
        if (result != 0)
        {
            ALOGW("usb_open: pthread_setschedparam failed (%s)", \
                  strerror(result));
        }
    }

    return TRUE;
}

/*******************************************************************************
**
** Function        usb_read
**
** Description     Read data from the usb port
**
** Returns         Number of bytes actually read from the usb port and
**                 copied into p_data.  This may be less than len.
**
*******************************************************************************/
uint16_t  usb_read(uint16_t msg_id, uint8_t *p_buffer, uint16_t len)
{
    uint16_t total_len = 0;
    uint16_t copy_len = 0;
    uint8_t *p_data = NULL;

    do
    {
        if(usb_cb.p_rx_hdr != NULL)
        {
            p_data = ((uint8_t *)(usb_cb.p_rx_hdr + 1)) + \
                     (usb_cb.p_rx_hdr->offset);

            if((usb_cb.p_rx_hdr->len) <= (len - total_len))
                copy_len = usb_cb.p_rx_hdr->len;
            else
                copy_len = (len - total_len);

            memcpy((p_buffer + total_len), p_data, copy_len);

            total_len += copy_len;

            usb_cb.p_rx_hdr->offset += copy_len;
            usb_cb.p_rx_hdr->len -= copy_len;

            if(usb_cb.p_rx_hdr->len == 0)
            {
                if (bt_hc_cbacks)
                    bt_hc_cbacks->dealloc((TRANSAC) usb_cb.p_rx_hdr, \
                                              (char *) (usb_cb.p_rx_hdr+1));

                usb_cb.p_rx_hdr = NULL;
            }
        }

        if(usb_cb.p_rx_hdr == NULL)
        {
            usb_cb.p_rx_hdr=(HC_BT_HDR *)utils_dequeue(&(usb_cb.rx_q));
        }
    } while ((usb_cb.p_rx_hdr != NULL) && (total_len < len));

    return total_len;
}

static int write_usb(int fd, uint8_t* p, uint16_t len)
{
      uint8_t channel;
      uint8_t ret;

      uint8_t type;
      type = *p;
      switch(type)
		{
		   case 1: //command
		       channel = 5;
		       break;
		   case 2: //acl data
		       channel = 6;
		       break;
		   default:
		channel = 5;
		}

      if(channel == 5)
      {
        usleep(1* 1000);
      }

      struct iovec out[BT_USB_IOV_SIZE];
      out[0].iov_base = &channel;
      out[0].iov_len  = 1;
      out[1].iov_base = (uint8_t*)p+1;//skip over "type"
      out[1].iov_len  = len-1;
      ret = writev(fd,out,BT_USB_IOV_SIZE);
      USBDBG("write usb type: %d returned %d", type, ret);
      return len ;

}


/*******************************************************************************
**
** Function        usb_write
**
** Description     Write data to the usb port
**
** Returns         Number of bytes actually written to the usb port. This
**                 may be less than len.
**
*******************************************************************************/
uint16_t usb_write(uint16_t msg_id, uint8_t *p_data, uint16_t len)
{
    int ret, total = 0;
    USBDBG("usb writee len %d",len);

    while(len != 0)
    {
        ret = write_usb(usb_cb.fd, p_data+total, len);
        total += ret;
        len -= ret;
        USBDBG("usb write len remaining %d",len);
    }

    return ((uint16_t)total);
}

/*******************************************************************************
**
** Function        usb_close
**
** Description     Close the usb port
**
** Returns         None
**
*******************************************************************************/
void usb_close(void)
{
    int result;
    TRANSAC p_buf;

    USBDBG("usb_close(fd:%d)", usb_cb.fd);

    if (usb_running)
    {
        send_wakeup_signal(USB_RX_EXIT);
    }

    if ((result=pthread_join(usb_cb.read_thread, NULL)) < 0)
        USBDBG( "pthread_join() FAILED result:%d", result);

    /* Calling vendor-specific part */
    if (bt_vnd_if)
        bt_vnd_if->op(BT_VND_OP_USERIAL_CLOSE, NULL);

    usb_cb.fd = -1;

    if (bt_hc_cbacks)
    {
        while ((p_buf = utils_dequeue (&(usb_cb.rx_q))) != NULL)
        {
            bt_hc_cbacks->dealloc(p_buf, (char *) ((HC_BT_HDR *)p_buf+1));
        }
    }
    USBDBG("usb close done");
}

/*******************************************************************************
**
** Function        usb_ioctl
**
** Description     ioctl inteface
**
** Returns         None
**
*******************************************************************************/
void usb_ioctl(userial_ioctl_op_t op, void *p_data)
{
    return;
}
