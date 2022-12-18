#ifndef _ICUNIT_ICUNIT_INC
#define _ICUNIT_ICUNIT_INC

#include "iCunit_config.h"
#include "sre_buildef.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif/* __cpluscplus */
#endif /* __cpluscplus */

#if ((OS_HARDWARE_PLATFORM != OS_DSP170) && (OS_HARDWARE_PLATFORM != OS_RISC170))
#define OS_SEC_ICUNIT
#else
#define OS_SEC_ICUNIT     __attribute__((section(".os.data.icunit")))
#endif

OS_SEC_ICUNIT ICUNIT_CASE_S iCunit_CaseArray[ICUNIT_CASE_SIZE];
OS_SEC_ICUNIT ICUNIT_SUIT_S iCunit_SuitArray[ICUNIT_SUIT_SIZE];


OS_SEC_ICUNIT iUINT32 iCunit_Init_Success = 0x0000FFFF;
OS_SEC_ICUNIT iUINT32 iCunit_Case_Cnt = 0xFFFF;
OS_SEC_ICUNIT iUINT32 iCunit_Suit_Cnt = 0xFFFF;
OS_SEC_ICUNIT iUINT32 iCunit_Case_Idx = 0xFFFF;
OS_SEC_ICUNIT iUINT32 iCunit_Suit_Idx = 0xFFFF;
OS_SEC_ICUNIT iUINT32 _reboot_case_idx = (iUINT32)-1;
OS_SEC_ICUNIT iUINT32 _reboot_suit_idx = (iUINT32)-1;
OS_SEC_ICUNIT iUINT32 iCunit_Case_FailedCnt = 0;
OS_SEC_ICUNIT iUINT32 iCunit_Suit_FailedCnt = 0;
OS_SEC_ICUNIT iUINT32 iCunit_ErrLog_AddSuit = 0;
OS_SEC_ICUNIT iUINT32 iCunit_ErrLog_AddCase = 0;
OS_SEC_ICUNIT iUINT32 _reboot_flag = 0;
OS_SEC_ICUNIT iUINT32 iCunit_bak_buff = 0;

OS_SEC_ICUNIT iUINT32 iCunit_errLineNo;  /* ´íÎóÐÐºÅ */
OS_SEC_ICUNIT iUINT32 iCunit_errCode;    /* ¼ÇÂ¼´íÎóÂë */



#if (OS_HARDWARE_PLATFORM == OS_C64XPLUS)
    #pragma DATA_SECTION(iCunit_CaseArray, ".os_bss")
    #pragma DATA_SECTION(iCunit_SuitArray, ".os_bss")
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif/* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_ICUNIT_INC */
