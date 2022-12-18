#ifndef _CI_STACK_H_
#define _CI_STACK_H_

#include "hi_unf_ci.h"

typedef HI_U32 (*HI_CI_FunShowUIMenu)(HI_U8 **pu8Text, HI_U32 u32Size[], HI_U32 u32ItemNum);
typedef HI_U32 (*HI_CI_FunShowUIReq)(HI_U8 *pu8Text, HI_U32 u32Size);
typedef HI_U32 (*HI_CI_FunTune)(HI_U16 network_id,
                               HI_U16 original_network_id,
                               HI_U16 transport_stream_id,
                               HI_U16 service_id);
typedef HI_U32 (*HI_CI_FunUpdateSystemId)(HI_U16 *pu16CaIds, HI_U8 u8NumCaIds);

typedef struct hiCI_HANDLE_FUN_S
{
    HI_CI_FunUpdateSystemId UpdateSystemId;
    HI_CI_FunShowUIMenu ShowUIMenu;
    HI_CI_FunShowUIReq ShowUIReq;
    HI_CI_FunTune Tune;
}HI_CI_HANDLE_FUN_S;

HI_U32 HI_CI_Init(HI_UNF_CI_TS_MODE_E enTSMode[], HI_UNF_CI_TSI_SERIAL_PORT_E enTsiSerialPort[]);
HI_S32 HI_CI_DeInit(void);
HI_U32 HI_CI_UpdatePMT(HI_UNF_CI_PCCD_E enCardId, HI_U8  *pPmtData);
HI_U32 HI_CI_MMIEnterMenu(HI_UNF_CI_PCCD_E enCardId);
HI_U32 HI_CI_MMIMenuAnsw(HI_UNF_CI_PCCD_E enCardId, HI_U8 u32Nb);
HI_U32 HI_CI_MMIAnsw(HI_UNF_CI_PCCD_E enCardId, HI_CHAR *pu8Text, HI_U32 u32Size);
HI_U32 HI_CI_GetCaSystemID(HI_UNF_CI_PCCD_E enCardId, HI_U16 u16CaIds[], HI_U8 *pu8NumCaIds);
HI_U32 HI_CI_GetHandleFunc(HI_CI_HANDLE_FUN_S *funCI);
HI_U32 HI_CI_SetHandleFunc(HI_CI_HANDLE_FUN_S *funCI);

#endif

