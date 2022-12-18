/**
* @file sre_sys.ph
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：系统信息的内部头文件。 \n
*/

#ifndef _SRE_SYS_PH
#define _SRE_SYS_PH

#include "sre_sys.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


//*****************************************************************************
// OS Flag Definitions - These indicate OS status
//*****************************************************************************

#define OS_FLG_HWI_ACTIVE                                   0x0001
#define OS_FLG_BGD_ACTIVE                                   0x0002
#define OS_FLG_SWI_ACTIVE                                   0x0004
#define OS_FLG_TICK_ACTIVE                                  0x0008
#define OS_FLG_SYS_ACTIVE                                   0x0010

#define OS_FLG_SWI_ENABLE                                   0x0100
#define OS_FLG_SWI_REQ                                      0x0200
#define OS_FLG_TSK_REQ                                      0x1000
#define OS_FLG_TSK_SWHK                                     0x2000      /* 任务切换时是否调用切换入口函数 */

#define OS_FLG_TSK_THD                                      0x8000      /* 任务切换阀值开关 */

#define OS_SYS_VER_NAME_LEN                                 32

#define OS_SYS_CPU_START_ID                                 12          /* CPU核起始ID */
#define OS_SYS_CPU_END_ID                                   16          /* CPU核结束ID */


#define OS_SYS_MV_32_BIT                                    32
#define OS_SYS_MS_PER_SECOND                                1000
#define OS_SYS_US_PER_SECOND                                1000000

#define OS_SYS_APPVER_NAME_MAX                              64
#define OS_SYS_MAGIC_WORD                                   0xAAAAAAAA
#define OS_SYS_EMPTY_STACK                                  0xCACACACA


#define OS_SYS_PID_BASE                                     (SRE_GetCoreID() << 8)

#define OS_INT_ACTIVE                                       (g_vuwUniFlag & (OS_FLG_HWI_ACTIVE | OS_FLG_SWI_ACTIVE))
#define OS_INT_INACTIVE                                     (!(OS_INT_ACTIVE))


typedef enum
{
    OS_HWI_CREATE = 0,
    OS_HWI_DELETE,
    OS_SWI_CREATE,
    OS_SWI_DELETE,
    OS_TSK_CREATE,
    OS_TSK_DELETE,
    OS_THREAD_BUTT
}OS_THREAD_OPTION_TYPE_E;

typedef UINTPTR (* OS_UINTPTR_FUNC)(VOID);
typedef UINT32 (* OS_THREAD_OPTION_FUNC)(UINT32 uwID, OS_THREAD_OPTION_TYPE_E enAction);
typedef VOID ( *TICK_DISP_FUNC )(VOID);

extern UINT32 g_vuwUniFlag;
extern OS_IDLE_HOOK m_pfnSysIdlePrefixHook;
extern volatile OS_IDLE_HOOK m_pfnSysIdleHook;

extern UINT16 g_usSwiMaxNum;
extern UINT32 g_uwTskMaxNum;
extern UINT32 g_uwThreadNum;
extern UINT32  g_uwSampleNum;
extern UINT32  g_uwPerformanceBase;

extern VOID osReboot();
//extern UINT32 osGetCoreID();

#define osSRSet(uwValue)   uwValue = uwValue
#define osSRGet()    0

extern UINT32 osHookAdd(const OS_VOID_FUNC pfnHook,
                        OS_VOID_FUNC apfHookTbl[],
                        UINT32 *puwUsedEntries,
                        const UINT32 uwMaxEntries);
extern UINT32 osHookDel(const OS_VOID_FUNC pfnHook,
                        OS_VOID_FUNC apfHookTbl[],
                        UINT32 *puwUsedEntries);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_SYS_PH */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

