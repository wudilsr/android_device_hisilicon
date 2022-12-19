/*-----------------------------------------------------------------------*/
/*!!Warning: Hisilicon key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCEm2UPcyllv4D4NOje6cFLSYglw6LvPA978sGAr3yTchgOI0M46H
HZIZCDLcNqR1rYgDnWEYHdqiWpPUq+8h0NKWxbZZ5sKamdK7db5jjkEnJ35bJ1W5Gh/rnhdj
qXCyr2J6P7JDt+Qpn3de+C5uTX6jbOdE5N+ih2OJLILKMZIaFRBsflC/fcFLr8zsKqs3n6aO
0NqhuqYooMA5xqjiI9A8M3OcprHRA8ZOTekvnUYOaqhpRDcTuWoZ3regJ2GLxA==#*/
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



VOID RV8HAL_V200R004_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId);
VOID RV8HAL_V200R004_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam);
VOID RV8HAL_V200R004_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam);
VOID RV8HAL_V200R004_StartVDH(RV8_DEC_PARAM_S *pRv8DecParam);




SINT32 RV8HAL_V200R004_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 RV8HAL_V200R004_StartDec( RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId )
{

    return -1;
}

VOID RV8HAL_V200R004_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId)
{
    return;
}


VOID RV8HAL_V200R004_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam)
{
    return;
}


VOID RV8HAL_V200R004_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam)
{
	    return;
}


VOID RV8HAL_V200R004_StartVDH(RV8_DEC_PARAM_S *pRv8DecParam)
{
    return;
}


#endif //__VDM_HAL_REAL8_C__
