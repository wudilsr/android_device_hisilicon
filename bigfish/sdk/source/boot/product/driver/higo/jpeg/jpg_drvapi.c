#if 1
/*******************************************************************************
 *              Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: jpgdrv_api.c
 * Description: jpg
 *
 * History:
 * Version   Date             Author    DefectNum    Description
 * main\1    2008-04-07       d37024    HI_NULL      Create this file.
 ******************************************************************************/

#include "jpg_common.h"
#include "jpg_type.h"

#include "hi_reg_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */


//static VCOS_sem_t s_semEngage;
static HI_VOID *s_pRegAddr = HI_NULL;


#define JPGDRV_CHECK(jpgfd) \
do {\
    if (0 >= jpgfd) \
    { \
        HI_TRACE(HI_LOG_LEVEL_ERROR, JPEG, \
                 "%s\n", "Dev don't open.");\
        return HI_ERR_JPG_DEV_NOOPEN;\
    }\
}while(0)

#define JPGDRV_REGISTER_LENGTH 0x108



//HI_U32 X5_REGS[0x64F] = {0};

HI_S32 HI_JPG_Open(HI_VOID)
{

    return HI_SUCCESS;
}
HI_S32 HI_JPG_Close(HI_VOID)
{

    return HI_SUCCESS;
}
HI_S32 JPGDRV_GetDevice(HI_VOID)
{
    return HI_SUCCESS;
}
HI_S32 JPGDRV_ReleaseDevice(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 JPGDRV_GetRegisterAddr(HI_VOID **pRegPtr, HI_VOID **pRstRegPtr, HI_VOID **pVhbRegPtr)
{
#ifndef JPG_OS_BOOT

#else
    U_PERI_CRG31 unTempValue;

    s_pRegAddr = (HI_VOID*)JPEG_HW_ADDRESS;

    unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;

    unTempValue.bits.jpgd_cken  = 0x1;
    unTempValue.bits.jpgd_srst_req = 0x0;

    g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;

    {
        HI_U32  *pMaskReg = (HI_U32 *)s_pRegAddr + 0x104;
        pMaskReg[0] = 0x0;
    }

    *pRegPtr = (HI_VOID*)JPEG_HW_ADDRESS;

#endif
    return HI_SUCCESS;
}

#define  JPGHDEC_READ_REG(baseaddr, offset, value) \
{\
    ((value) = *(volatile HI_U32 *)((HI_U32)(baseaddr) + (offset)) );\
}

HI_S32 JPGDRV_GetIntStatus(JPG_INTTYPE_E *pIntType, HI_U32 TimeOut)
{
    HI_U32    IntVal = 0;
    HI_U32    Addr;

#ifndef JPG_OS_BOOT


#else
	Addr = JPEG_HW_ADDRESS + 0x100;  /* X5_JPGREG_INT */
    IntVal = (*(HI_U32*)(Addr))&0x7;
//    printf("++Addr 0x%x inval %d\n",Addr,IntVal);
    if(IntVal == 1)
    	{
    	*pIntType = JPG_INTTYPE_FINISH;
    	}
    else if(IntVal == 4)
    	{
    	*pIntType = JPG_INTTYPE_CONTINUE;
    	}
    else  if(IntVal == 2)
    	{
    	*pIntType = JPG_INTTYPE_ERROR;
    	}
    else *pIntType = JPG_INTTYPE_NONE;

   if(IntVal != 0)
        (*(HI_U32*)(Addr)) = IntVal;
#endif
    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#endif
