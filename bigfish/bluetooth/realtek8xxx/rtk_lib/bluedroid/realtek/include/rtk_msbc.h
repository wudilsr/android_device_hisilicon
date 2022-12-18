#ifdef BLUETOOTH_RTK_VR

#ifndef RTK_PATCH_H
#define RTK_PATCH_H

#include "bt_target.h"
#include <pthread.h>
#include <hardware/bluetooth.h>
#include <../../bta/hh/bta_hh_int.h>
#include "bta_gatt_api.h"
#include "rtkbt_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RTK_PATCH_DEBUG
/************************************************
********voice remote controller properties*******
*************************************************/
#define RTKBT_INPUT_REPORT 0xFD

#define RTKBT_INPUT_DATA_MDT   0x5A
#define RTKBT_OUTPUT_REPORT_MDT 0x5A

#define RTKBT_INPUT_DATA_IFLYTEK   0xFC
#define RTKBT_OUTPUT_REPORT_IFLYTEK 0xFB

#define RTKBT_INPUT_REPORT_TYPE     0x01
#define RTKBT_INPUT_DATA_TYPE       0x01
#define RTKBT_OUTPUT_REPORT_TYPE    0x02

#define TIME_OUT 10
#define RTKBT_MTU_SIZE      512

typedef struct
{
    UINT16 data_len;
    UINT8 *data;
}tVOICE_HSDATA;


typedef struct {
    pthread_t tid; /* main thread id */
    int running;
    pthread_mutex_t mutex;
    pthread_mutex_t socket_mutex;
    BOOLEAN  channel_status;
    UINT16 conn_id;
    tBTA_HH_DEV_CB *p_dev_cb;
} tMSBC_REC_CB;

/*for record thread*/
typedef struct {
    pthread_t tid; /* main thread id */
    int running;
} tMSBC_RR_CB;

BT_API  BOOLEAN RTKBT_VR_start_msbc_voice_rec(tBTA_HH_DEV_CB *p_dev_cb, UINT16 conn_id);
BT_API  void RTKBT_VR_restart_msbc_voice_rec(void);
BT_API  void RTKBT_VR_stop_msbc_voice_rec(void);
BT_API  BOOLEAN RTKBT_VR_msbc_voice_decode_MDT(tVOICE_HSDATA *voice_data);
BT_API  BOOLEAN RTKBT_VR_msbc_voice_decode_iflytek(tVOICE_HSDATA *voice_data);
BT_API  void RTKBT_VR_send_stop_request(tBTA_HH_DEV_CB *p_dev_cb);
BT_API  void RTKBT_VR_send_start_request(tBTA_HH_DEV_CB *p_dev_cb);
BT_API  void RTKBT_VR_device_disconn(UINT16 conn_id);
BT_API  void RTKBT_VR_cmd_acknowledge(int status);
BT_API  void RTKBT_VR_not_snd_stop_request(BOOLEAN permission);
BT_API  BOOLEAN RTKBT_VR_get_msbc_status(void);
BT_API  tBTA_HH_DEV_CB * RTKBT_VR_get_dev_cb(void);

BT_API void bta_hh_le_write_rpt(tBTA_HH_DEV_CB *p_cb, UINT8 srvc_inst,
                         tBTA_GATTC_WRITE_TYPE   write_type,
                         tBTA_HH_RPT_TYPE r_type,
                         BT_HDR *p_buf, UINT16 w4_evt );
BT_API tBTA_HH_LE_RPT * bta_hh_le_find_report_entry(tBTA_HH_DEV_CB *p_cb,
                                             UINT8  srvc_inst_id,  /* service instance ID */
                                             UINT16 rpt_uuid,
                                             UINT8  char_inst_id);
BT_API tBTA_HH_DEV_CB * bta_hh_le_find_dev_cb_by_conn_id(UINT16 conn_id);
BT_API void RTKBT_VR_Audio_set_ok(BOOLEAN state);
BT_API void RTKBT_VR_start_request_ok(BOOLEAN state);
BT_API BOOLEAN RTKBT_VR_start_request_status(void);

BT_API UINT32 RTKBT_VR_get_remote_controller_id(void);

BT_API void RTKBT_VR_get_report_id(UINT8 *voice_input_data, UINT8 *voice_output_rpt_id, UINT32 remote_controller_id);

#ifdef __cplusplus
}
#endif

#endif
#endif
