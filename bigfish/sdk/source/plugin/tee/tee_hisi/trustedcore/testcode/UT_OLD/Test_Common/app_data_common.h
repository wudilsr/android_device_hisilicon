/**
* @file app_data_common.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：测试文件的头文件。 \n
*/

#ifndef _APP_DATA_COMMON_H
#define _APP_DATA_COMMON_H
#include "sre_base.h"
#include "iCunit.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define UT_STATMEM_SIZE      0x00001000          //私有静态内存单元测试使用分区大小
extern volatile UINT32 g_aucMcRet[20];

extern UINT8 taskOnebuf1[404];
extern  UINT8 taskOneBuf2[404];
extern UINT8 taskTwobuf1[404];
extern UINT8 taskTwoBuf2[404];
extern UINT8 taskThreebuf1[404];
extern UINT8 taskThreebuf2[404];

#define APP_SEC_BSS_M2
#define APP_SEC_DATA_M2
#define APP_SEC_BSS_M3
#define APP_SEC_DATA_M3
#define APP_SEC_BSS_DDR
#define APP_SEC_DATA_DDR

#define APP_SEC_BSS_M3_SHARE
#define APP_SEC_DATA_M3_SHARE
#define APP_SEC_BSS_DDR_SHARE
#define APP_SEC_DATA_DDR_SHARE

#define APP_SEC_BSS_M3_SHARE_NC
#define APP_SEC_DATA_M3_SHARE_NC
#define APP_SEC_BSS_DDR_SHARE_NC
#define APP_SEC_DATA_DDR_SHARE_NC


#ifndef TEST_SEC_BSS
#define TEST_SEC_BSS          __attribute__((section(".test.bss")))
#endif

//1
#if(OS_HARDWARE_PLATFORM == OS_CORTEX_A9)

#ifndef OS_SEC_TEST_TEXT
#define OS_SEC_TEST_TEXT   __attribute__((section(".os.test.text")))
#endif

#ifndef OS_SEC_TEST2_TEXT
#define OS_SEC_TEST2_TEXT   __attribute__((section(".os.test2.text")))
#endif

#ifndef OS_SEC_TEST3_TEXT
#define OS_SEC_TEST3_TEXT   __attribute__((section(".os.test3.text")))
#endif

#ifndef OS_SEC_TEST4_TEXT
#define OS_SEC_TEST4_TEXT   __attribute__((section(".os.test4.text")))
#endif

#ifndef OS_SEC_TEST5_TEXT
#define OS_SEC_TEST5_TEXT   __attribute__((section(".os.test5.text")))
#endif

#ifndef OS_SEC_TEST6_TEXT
#define OS_SEC_TEST6_TEXT   __attribute__((section(".os.test6.text")))
#endif

#ifndef OS_SEC_TEST7_TEXT
#define OS_SEC_TEST7_TEXT   __attribute__((section(".os.test7.text")))
#endif

#ifndef OS_SEC_TEST8_TEXT
#define OS_SEC_TEST8_TEXT   __attribute__((section(".os.test8.text")))
#endif

#ifndef OS_SEC_TEST9_TEXT
#define OS_SEC_TEST9_TEXT   __attribute__((section(".os.test9.text")))
#endif

#ifndef OS_SEC_TEXT_UT
#define OS_SEC_TEXT_UT    __attribute__((section(".os.test.text")))
#endif

#ifndef OS_SEC_TEXT1_UT
#define OS_SEC_TEXT1_UT    __attribute__((section(".os.test.text")))
#endif

#ifndef OS_SEC_TEXT2_UT
#define OS_SEC_TEXT2_UT    __attribute__((section(".os.test.text")))
#endif

#ifndef OS_SEC_TEXT3_UT
#define OS_SEC_TEXT3_UT    __attribute__((section(".os.test.text")))
#endif

#ifndef OS_SEC_TEXT4_UT
#define OS_SEC_TEXT4_UT    __attribute__((section(".os.test.text")))
#endif

#ifndef OS_SEC_TEXT5_UT
#define OS_SEC_TEXT5_UT    __attribute__((section(".os.test.text")))
#endif

#else
#define OS_SEC_TEST_TEXT
#define OS_SEC_TEST2_TEXT
#define OS_SEC_TEST3_TEXT
#define OS_SEC_TEST4_TEXT
#define OS_SEC_TEST5_TEXT
#define OS_SEC_TEST6_TEXT
#define OS_SEC_TEST7_TEXT
#define OS_SEC_TEST8_TEXT
#define OS_SEC_TEST9_TEXT
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /*_APP_DATA_COMMON_H*/
/**
 * History:
 * 2009-8-13 q00144072: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
