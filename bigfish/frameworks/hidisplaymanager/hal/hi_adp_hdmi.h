#ifndef _HI_ADP_HDMI_H_
#define _HI_ADP_HDMI_H_

#include "hi_unf_hdmi.h"
typedef enum hiSTB_Linux_Key
{
    KEY_POWER                 = 116,
    KEY_UP                    = 103,
    KEY_DOWN                  = 108,
    KEY_LEFT                  = 105,
    KEY_RIGHT                 = 106,
    KEY_ENTER                 = 28,
    KEY_BACK                  = 158,
    KEY_MENU                  = 139,
    KEY_PAGE_UP               = 104,
    KEY_PAGE_DOWN             = 109,
    KEY_FAST_FORWARD          = 159,
    KEY_REWIND                = 168,
    KEY_NUM_0                 = 11,
    KEY_NUM_1                 = 2,
    KEY_NUM_2                 = 3,
    KEY_NUM_3                 = 4,
    KEY_NUM_4                 = 5,
    KEY_NUM_5                 = 6,
    KEY_NUM_6                 = 7,
    KEY_NUM_7                 = 8,
    KEY_NUM_8                 = 9,
    KEY_NUM_9                 = 10,
    KEY_PLAY                  = 164,
    KEY_STOP                  = 128,
    KEY_HOME                  = 102,
    KEY_VOLUME_UP             = 115,
    KEY_VOLUME_DOWN           = 114
}HISTB_LINUX_KEY;
typedef void (*User_HDMI_CallBack)(HI_UNF_HDMI_EVENT_TYPE_E event, HI_VOID *pPrivateData);

HI_UNF_ENC_FMT_E stringToUnfFmt(HI_CHAR *pszFmt);
HI_S32 HIADP_HDMI_Init(HI_UNF_HDMI_ID_E enHDMIId, HI_UNF_ENC_FMT_E enWantFmt);
HI_S32 HIADP_HDMI_DeInit(HI_UNF_HDMI_ID_E enHDMIId);
HI_S32 HDMI_CEC_Standy();
HI_VOID HDMI_PrintSinkCap(HI_UNF_EDID_BASE_INFO_S *pCapbility);

#endif
