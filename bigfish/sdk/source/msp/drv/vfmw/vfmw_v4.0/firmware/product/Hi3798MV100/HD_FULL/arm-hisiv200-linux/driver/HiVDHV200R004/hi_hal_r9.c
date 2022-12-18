/*-----------------------------------------------------------------------*/
/*!!Warning: Hisilicon key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCEm2UPcyllv4D4NOje6cFLSYglw6LvPA978sGAr3yTchgOI0M46H
HZIZCDLcNqR1rYgDnWEYHdqiWpPUq+8h0NKWxbZZ5sKamdK7db5jjkEnJ35bJ1W5Gh/rnhdj
qXCyr/grVpIQ20OuKhH/jo8Pirpc4be9PNqRoQOPmFZVZEO0BticbNID8KZr7+9dXkrf0nDQ
LT8+Zm1Mppik9hBq0rYXjQu+MKj2GFsyb32Fw4sqwUbnl3LLyHaPPTj3crq+ZA==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/












/*********************************************************************** 
*
* Copyright (c) 2010 Hisilicon - All Rights Reserved
*
* File: $vdm_hal_real9.c$
* Date: $2010/06/09$
* Revision: $v1.0$
* Purpose: HiVDHV100 IP REAL9 VDM HAL Module.
*
* Change History:
*
* Date       Author            Change
* ======     ======            ======
* 20100609   q45134            Original
*
************************************************************************/

#ifndef __VDM_HAL_REAL9_C__
#define __VDM_HAL_REAL9_C__

#include "vdm_hal.h"
#include "decparam.h"

VOID RV9HAL_V200R004_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam, SINT32 VdhId);
VOID RV9HAL_V200R004_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam);
VOID RV9HAL_V200R004_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam);
VOID RV9HAL_V200R004_StartVDH(RV9_DEC_PARAM_S *pRv9DecParam);


SINT32 RV9HAL_V200R004_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 RV9HAL_V200R004_StartDec( RV9_DEC_PARAM_S *pRv9DecParam, SINT32 VdhId )
{
    return VDMHAL_OK;
}

VOID RV9HAL_V200R004_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam, SINT32 VdhId)
{
    return;
}

VOID RV9HAL_V200R004_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam)
{
    return;
}

VOID RV9HAL_V200R004_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam)
{
	return;
}
VOID RV9HAL_V200R004_StartVDH(RV9_DEC_PARAM_S *pRv9DecParam)
{
    return;
}


#endif //__VDM_HAL_REAL9_C__
