/*****************************************************************************/
/*                                                                           */
/*                Copyright 2008 - 2050, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* Author: Cao Xingguo                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2012-11-20                                                          */
/*                                                                           */
/* Description:                                                              */
/*     Macros used in assembly code                                          */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2012-11-20                                                       */
/*    Author: Wang daneng                                                    */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef _UNI_ASM_PH
#define _UNI_ASM_PH

#define  ARM_MODE_ARM           0x00000000u
#define  ARM_MODE_THUMB         0x00000020u

#define  ARM_SVC_MODE_THUMB    (0x00000013uL + ARM_MODE_THUMB)
#define  ARM_SVC_MODE_ARM      (0x00000013uL + ARM_MODE_ARM)
#define  ARM_PSR_ASY_ABORT_MASK     0x100
#define  ARM_PSR_IRQ_DIS        0x80
#define  ARM_PSR_FIQ_DIS        0x40

#if (OS_BYTE_ORDER == OS_BIG_ENDIAN)
#define ARM_PSR_ENDIAN     0x200
#else
#define ARM_PSR_ENDIAN   0
#endif

#endif /* _UNI_ASM_PH */
