/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCDadN5jJKSuVyxmmaCmKFU6eJEbB2fyHF9weu4/jer/hxLHb+S1e
E0zVg4C3NiZh4b+GnwjAHj8JYHgZh/mRmQnWI+jpdzDE6SuWDZQOnsbFmrAH9gMFQaPapBXM
WRNYqSKgRgNu0Dto76P+cDnLAlz/s4yBVDIstTGHyej6paR0sUAluYHgX3+QRhnbYL2EVjac
6k6O2vLEbyMq9sHTJpufMwt255poQucTEQjGYBUewy2JuR5MUhM+GRmA/m+vzw==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/




/*********************************************************************** 
*
* Copyright (c) 2010 Hisilicon - All Rights Reserved
*
* File: $vdm_hal_real8.c$
* Date: $2010/06/09$
* Revision: $v1.0$
* Purpose: HiVDHV100 IP REAL8 VDM HAL Module.
*
* Change History:
*
* Date       Author            Change
* ======     ======            ======
* 20100609   q45134            Original
*
************************************************************************/

#ifndef __VDM_HAL_REAL8_C__
#define __VDM_HAL_REAL8_C__

#include "vdm_hal.h"
#include "decparam.h"

VOID RV8HAL_V300R001_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId);
VOID RV8HAL_V300R001_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam);
VOID RV8HAL_V300R001_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam);
VOID RV8HAL_V300R001_StartVDH(RV8_DEC_PARAM_S *pRv8DecParam);


SINT32 RV8HAL_V300R001_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 RV8HAL_V300R001_StartDec( RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId )
{
    return -1;
}

VOID RV8HAL_V300R001_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId)
{
    return;
}


VOID RV8HAL_V200R004_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam)
{
    return;
}


VOID RV8HAL_V300R001_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam)
{
	return;
}


VOID RV8HAL_V300R001_StartVDH(RV8_DEC_PARAM_S *pRv8DecParam)
{
    return;
}


#endif //__VDM_HAL_REAL8_C__
