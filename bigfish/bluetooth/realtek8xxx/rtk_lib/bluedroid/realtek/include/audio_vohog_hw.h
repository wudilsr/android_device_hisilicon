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

/*****************************************************************************
 *
 *  Filename:      audio_vohog_hw.h
 *
 *  Description:
 *
 *****************************************************************************/

#ifndef AUDIO_VOHOG_HW_H
#define AUDIO_VOHOG_HW_H

/*****************************************************************************
**  Constants & Macros
******************************************************************************/

//#define VOHOG_AUDIO_HARDWARE_INTERFACE "audio.sco"
#define VOHOG_DATA_IN_PATH "/data/misc/bluedroid/.vohog_in"
#define VOHOG_CTRL_PATH "/data/misc/bluedroid/.vohog_ctrl"

#define VOHOG_SAMPLE_RATE_16K       (16000)
#define VOHOG_USE_MSBC              (1)
#define VOHOG_SKT_DISCONNECTED      (-1)

#if(VOHOG_USE_MSBC == 1)
#define VOHOG_IN_BUFSIZE    (240)
#else
#define VOHOG_IN_BUFSIZE    (1024)      //nordic buffer
#endif


#define VOHOG_CTRL_CMD_START  1
#define VOHOG_CTRL_CMD_STOP   2

typedef enum {
    VOHOG_CTRL_ACK_SUCCESS  = 1,
    VOHOG_CTRL_ACK_FAILURE
} tVOICE_CTRL_ACK;

/*****************************************************************************
**  Type definitions for callback functions
******************************************************************************/

/*****************************************************************************
**  Type definitions and return values
******************************************************************************/

/*****************************************************************************
**  Extern variables and functions
******************************************************************************/

/*****************************************************************************
**  Functions
******************************************************************************/


/*****************************************************************************
**
** Function
**
** Description
**
** Returns
**
******************************************************************************/

#endif /* AUDIO_VOHOG_HW_H */

