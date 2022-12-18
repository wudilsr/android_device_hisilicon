/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _BDROID_BUILDCFG_H
#define _BDROID_BUILDCFG_H

#define BTM_DEF_LOCAL_NAME   "Realtek Bluetooth"

// SERVICE_CLASS:0x1A (Bit17 -Networking,Bit19 - Capturing,Bit20 -Object Transfer)
// MAJOR CLASS: COMPUTER
// MINOR CLASS: TABLET
#define BTA_DM_COD {0x1A, 0x01, 0x1C}

#define BTA_GATT_DEBUG TRUE

#define PRELOAD_MAX_RETRY_ATTEMPTS (3)
#define HCI_MAX_SIMUL_CMDS (1)
#define BTM_BLE_SCAN_SLOW_INT_1 (96)
#define BTM_BLE_SCAN_SLOW_WIN_1 (24)
#define REMOTE_CONTROLLER_ID (1)

#ifdef BLUETOOTH_RTK_SCO
#define BTM_SCO_DATA_SIZE_MAX 48
#define BTM_SCO_HCI_INCLUDED TRUE
#define BTM_WBS_INCLUDED TRUE
#define BTIF_HF_FEATURES   ( BTA_AG_FEAT_3WAY | \
                             BTA_AG_FEAT_ECNR   | \
                             BTA_AG_FEAT_CODEC  | \
                             BTA_AG_FEAT_REJECT | \
                             BTA_AG_FEAT_ECS    | \
                             BTA_AG_FEAT_EXTERR | \
                             BTA_AG_FEAT_BTRH   | \
                             BTA_AG_FEAT_VREC   | \
                             BTA_AG_FEAT_UNAT)
#else
#define BTIF_HF_SERVICES (BTA_HSP_SERVICE_MASK)
#define BTIF_HF_SERVICE_NAMES  { BTIF_HSAG_SERVICE_NAME, NULL }
#endif

#define BTA_DISABLE_DELAY 1000 /* in milliseconds */
#define BTA_HOST_INTERLEAVE_SEARCH TRUE
#endif
