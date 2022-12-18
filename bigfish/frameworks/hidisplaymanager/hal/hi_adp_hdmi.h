#ifndef _HI_ADP_HDMI_H_
#define _HI_ADP_HDMI_H_

#include "hi_unf_hdmi.h"

typedef void (*User_HDMI_CallBack)(HI_UNF_HDMI_EVENT_TYPE_E event, HI_VOID *pPrivateData);

HI_UNF_ENC_FMT_E stringToUnfFmt(HI_CHAR *pszFmt);
HI_S32 HIADP_HDMI_Init(HI_UNF_HDMI_ID_E enHDMIId, HI_UNF_ENC_FMT_E enWantFmt);
HI_S32 HIADP_HDMI_DeInit(HI_UNF_HDMI_ID_E enHDMIId);
HI_VOID HDMI_PrintSinkCap(HI_UNF_EDID_BASE_INFO_S *pCapbility);

#endif
