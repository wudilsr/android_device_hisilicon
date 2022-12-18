/**
 * @file sre_fsem.ph
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：快速信号量的内部头文件。 \n
 */

#ifndef _SRE_FSEM_PH
#define _SRE_FSEM_PH

#include "sre_base.h"
#include "sre_fsem.h"
#include "sre_task.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define  OS_FSEM_COUNT_MAX   0x7FFFFFFF

typedef UINT32 (* MCFSEM_POST_FUNC)(TASK_PID_T uwTaskPID);

#define OS_MCFSEM_POST(uwTaskPID) ((g_pfnMcFsemPost == NULL)?OS_ERRNO_FSEM_POST_FAIL:g_pfnMcFsemPost(uwTaskPID))

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _SRE_FSEM_PH */

/*
 * History: \n
 * 2009-10-30, z00134877, Create this file. \n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
