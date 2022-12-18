/******************************************************************************
 *
 *  Copyright (C) 2014-2016 Realtek Corporation
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
 *  Filename:      poll.c
 *
 *  Description:   Contains host & controller handshake implementation
 *
 ******************************************************************************/

#define LOG_TAG "bt_poll"

#include <utils/Log.h>
#include <signal.h>
#include <time.h>
#include "bt_hci_bdroid.h"
#include "bt_vendor_lib.h"

/******************************************************************************
**  Constants & Macros
******************************************************************************/
#ifdef BLUETOOTH_RTK_HEARTBEAT
#ifndef BTPOLL_DBG
#define BTPOLL_DBG FALSE
#endif

#if (BTPOLL_DBG == TRUE)
#define BTPOLLDBG(param, ...) {ALOGD(param, ## __VA_ARGS__);}
#else
#define BTPOLLDBG(param, ...) {}
#endif

#ifndef ENABLE_BT_POLL_IN_ACTIVE_MODE
#define ENABLE_BT_POLL_IN_ACTIVE_MODE FALSE
#endif

#ifndef DEFAULT_POLL_IDLE_TIMEOUT
#define DEFAULT_POLL_IDLE_TIMEOUT    1000
#endif

/******************************************************************************
**  Externs
******************************************************************************/

extern bt_vendor_interface_t *bt_vnd_if;

/******************************************************************************
**  Local type definitions
******************************************************************************/

/* Poll state */
enum {
    POLL_DISABLED = 0,      /* initial state */
    POLL_ENABLED,
};

/* poll control block */
typedef struct
{
    uint8_t state;       /* poll state */
    uint8_t timer_created;
    timer_t timer_id;
    uint32_t timeout_ms;
} bt_poll_cb_t;


/******************************************************************************
**  Static variables
******************************************************************************/

static bt_poll_cb_t bt_poll_cb;

/******************************************************************************
**   Poll Static Functions
******************************************************************************/

/*******************************************************************************
**
** Function        poll_idle_timeout
**
** Description     Timeout thread of transport idle timer
**
** Returns         None
**
*******************************************************************************/
static void poll_idle_timeout(union sigval arg)
{
    int status;
    struct itimerspec ts;

    BTPOLLDBG("poll_idle_timeout: state %d", bt_poll_cb.state);

    if (bt_poll_cb.state == POLL_ENABLED) {
        /* Send heartbeat msg to controller */
        bthc_signal_event(HC_EVENT_POLL_IDLE_TIMEOUT);

        if (bt_poll_cb.timer_created == TRUE) {
            ts.it_value.tv_sec = bt_poll_cb.timeout_ms / 1000;
            ts.it_value.tv_nsec = 1000 * 1000 * (bt_poll_cb.timeout_ms % 1000);
            ts.it_interval.tv_sec = 0;
            ts.it_interval.tv_nsec = 0;

            status = timer_settime(bt_poll_cb.timer_id, 0, &ts, 0);
            if (status == -1)
                ALOGE("[POLL] Failed to set poll idle timeout");
        }
    }
}

/*******************************************************************************
**
** Function         poll_timer_stop
**
** Description      stop timer if allowed
**
** Returns          None
**
*******************************************************************************/
static void poll_timer_stop(void)
{
    int status;
    struct itimerspec ts;

    ALOGI("poll_timer_stop: timer_created %d", bt_poll_cb.timer_created);

    if (bt_poll_cb.timer_created == TRUE) {
        ts.it_value.tv_sec = 0;
        ts.it_value.tv_nsec = 0;
        ts.it_interval.tv_sec = 0;
        ts.it_interval.tv_nsec = 0;

        status = timer_settime(bt_poll_cb.timer_id, 0, &ts, 0);
        if (status == -1)
            ALOGE("[STOP] Failed to set poll idle timeout");
    }
}

/*****************************************************************************
**   POLL Interface Functions
*****************************************************************************/

/*******************************************************************************
**
** Function        poll_init
**
** Description     Init bt poll
**
** Returns         None
**
*******************************************************************************/
void poll_init(void)
{
    memset(&bt_poll_cb, 0, sizeof(bt_poll_cb_t));

    bt_poll_cb.state = POLL_DISABLED;
    bt_poll_cb.timeout_ms = DEFAULT_POLL_IDLE_TIMEOUT;

    ALOGI("poll_init: state %d, timeout %d ms", bt_poll_cb.state, bt_poll_cb.timeout_ms);
}

/*******************************************************************************
**
** Function        poll_cleanup
**
** Description     Poll clean up
**
** Returns         None
**
*******************************************************************************/
void poll_cleanup(void)
{
    ALOGI("poll_cleanup: timer_created %d", bt_poll_cb.timer_created);

    if (bt_poll_cb.timer_created == TRUE) {
        timer_delete(bt_poll_cb.timer_id);
    }
}

/*******************************************************************************
**
** Function        poll_enable
**
** Description     Enalbe/Disable poll
**
** Returns         None
**
*******************************************************************************/
void poll_enable(uint8_t turn_on)
{
    ALOGI("poll_enable: turn_on %d, state %d", turn_on, bt_poll_cb.state);

    if ((turn_on == TRUE) && (bt_poll_cb.state == POLL_ENABLED)) {
        ALOGI("poll_enable: poll is already on!!!");
        return;
    } else if ((turn_on == FALSE) && (bt_poll_cb.state == POLL_DISABLED)) {
        ALOGI("poll_enable: poll is already off!!!");
        return;
    }

    if (turn_on == FALSE) {
        poll_timer_stop();
        bt_poll_cb.state = POLL_DISABLED;
    } else {
        /* start poll timer when poll_timer_flush invoked first time */
        bt_poll_cb.state = POLL_ENABLED;
    }
}

/*******************************************************************************
**
** Function        poll_timer_flush
**
** Description     Called to delay notifying Bluetooth chip.
**                 Normally this is called when there is data to be sent
**                 over HCI.
**
** Returns         None
**
*******************************************************************************/
void poll_timer_flush(void)
{
    int status;
    struct itimerspec ts;
    struct sigevent se;

    BTPOLLDBG("poll_timer_flush: state %d", bt_poll_cb.state);

    if (bt_poll_cb.state != POLL_ENABLED)
        return;

    if (bt_poll_cb.timer_created == FALSE) {
        se.sigev_notify = SIGEV_THREAD;
        se.sigev_value.sival_ptr = &bt_poll_cb.timer_id;
        se.sigev_notify_function = poll_idle_timeout;
        se.sigev_notify_attributes = NULL;

        status = timer_create(CLOCK_MONOTONIC, &se, &bt_poll_cb.timer_id);

        if (status == 0)
            bt_poll_cb.timer_created = TRUE;
    }
#if (defined(ENABLE_BT_POLL_IN_ACTIVE_MODE) && (ENABLE_BT_POLL_IN_ACTIVE_MODE == FALSE))
    if (bt_poll_cb.timer_created == TRUE) {
        ts.it_value.tv_sec = bt_poll_cb.timeout_ms / 1000;
        ts.it_value.tv_nsec = 1000 * 1000 * (bt_poll_cb.timeout_ms % 1000);
        ts.it_interval.tv_sec = 0;
        ts.it_interval.tv_nsec = 0;

        status = timer_settime(bt_poll_cb.timer_id, 0, &ts, 0);
        if (status == -1)
            ALOGE("[Flush] Failed to set poll idle timeout");
    }
#endif
}
#endif
