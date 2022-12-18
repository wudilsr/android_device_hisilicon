#ifndef __SCTE_SUBT_DATA_H__
#define __SCTE_SUBT_DATA_H__

#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

HI_S32 SCTE_SUBT_Data_Init(HI_VOID);

HI_S32 SCTE_SUBT_Data_DeInit(HI_VOID);

HI_S32 SCTE_SUBT_Data_Create(HI_HANDLE hParse, HI_HANDLE *phData);

HI_S32 SCTE_SUBT_Data_Destroy(HI_HANDLE hData);

HI_S32 SCTE_SUBT_Data_Reset(HI_HANDLE hData);

HI_S32 SCTE_SUBT_Data_Inject(HI_HANDLE hData, const HI_U8 *pu8Data, HI_U32 u32DataSize);

#ifdef __cplusplus
}
#endif

#endif
