#include <stdio.h>
#include <unistd.h>
#include "btm_int.h"
#include "bt_trace.h"
#include "gki.h"
#include "gki_target.h"
#include "uipc.h"
#include "rtk_msbc.h"
#include "audio_vohog_hw.h"
#include <../../bta/hh/bta_hh_int.h>

#define RTKBT_IFLYTEK_INPUT_ACK 0xFF
#define RTKBT_IFLYTEK_INPUT_DATA 0xFF
#define RTKBT_IFLYTEK_OUTPUT_DATA 0xFF

BT_API  void RTKBT_VR_set_dev_cb(tBTA_HH_DEV_CB *p_dev_cb);
BT_API  void RTKBT_Iflytek_init();
BT_API  void RTKBT_Iflytek_cleanup();
BT_API  void RTKBT_Iflytek_process_data_from_RCU(UINT8 report_id, UINT8* data, UINT16 len);
BT_API  INT32 RTKBT_Iflytek_NotifyRcuStatus(unsigned char status,bt_bdaddr_t * addr);

