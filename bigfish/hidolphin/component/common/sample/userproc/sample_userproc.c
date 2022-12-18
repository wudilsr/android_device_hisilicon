#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

#include "hi_type.h"
#include "svr_proc.h"
#include "svr_debug.h"

#define DIRNAME     "sample"
#define ENTRYNAME1   "help"
#define ENTRYNAME2   "testproc2"
#define ENTRYNAME3   "testproc3"
#define ENTRYNAME4   "testproc4"

#define SAMPLE_PRINT SVR_LOG_INFO

SVR_MODULE_DECLARE("Sample_Proc");

HI_S32 Proc_Test_Show1(SVR_PROCSHOW_BUFFER_S * pstBuf, HI_VOID *pPrivData)
{
    SAMPLE_PRINT("Print in process %d, %s\n", (HI_S32)getpid(), __FUNCTION__);
    HI_S32 a=100;
    HI_S64 b = 500;
    HI_S64 c = 17592454483968;
    HI_S64 d = 20592454483968;
    SVR_PROC_Printf(pstBuf, "Test %d,%lld, %lld, %lld\n", a, b, c, d);
    
    SVR_PROC_Printf(pstBuf, "Print in process %d, %s\n", (HI_S32)getpid(), __FUNCTION__);
    SVR_PROC_Printf(pstBuf, "Invoke API \'HI_PROC_AddDir\' and \'HI_PROC_RemoveDir\' to create or remove a proc directory, the dir will be added in /proc/hisi/, for multi-process supporting, its name will be ${NAME_INPUT}_${PID}\n");
    SVR_PROC_Printf(pstBuf, "invoke API \'SVR_PROC_AddEntry\' and \'SVR_PROC_RemoveEntry\' to create or remove a proc entry,\n");
    SVR_PROC_Printf(pstBuf, "you can register a call back function \'HI_PROC_SHOW_FN\' to support read command as \'cat /proc/hisi/your_dir_pid/your_entry\',\n");
    SVR_PROC_Printf(pstBuf, "and register function \'HI_PROC_CMD_FN\' to support write command as \'echo params [...] > /proc/hisi/your_dir_pid/your_entry\'.\n");
    SVR_PROC_Printf(pstBuf, "Invoke API \'SVR_PROC_Printf\' in your \'HI_PROC_SHOW_FN\' to print info to proc entry.\n");
    SVR_PROC_Printf(pstBuf, "You can invoke it repeatedly, but the total amount of data must be less than 4KB. \n");
    return HI_SUCCESS;
}

HI_S32 Proc_Test_Show2(SVR_PROCSHOW_BUFFER_S * pstBuf, HI_VOID *pPrivData)
{
    SAMPLE_PRINT("Print in process %d, %s\n", (HI_S32)getpid(), __FUNCTION__);
    SVR_PROC_Printf(pstBuf, "Print in process %d, %s\n", (HI_S32)getpid(), __FUNCTION__);
    return HI_SUCCESS;
}

HI_S32 Proc_Test_Cmd1(HI_U32 u32Argc, HI_U8 *pu8Argv[], HI_VOID *pPrivData)
{
    HI_S32 i;

    SAMPLE_PRINT("Print in process %d, %s\n", (HI_S32)getpid(), __FUNCTION__);
    SAMPLE_PRINT("Argc: %d \n", u32Argc);
    for (i=0; i<u32Argc; i++)
    {
        SAMPLE_PRINT("\tArgv[%d]: %s \n", i, (HI_CHAR*)pu8Argv[i]);
    }

    return HI_SUCCESS;
}

HI_S32 Proc_Test_Cmd2(HI_U32 u32Argc, HI_U8 *pu8Argv[], HI_VOID *pPrivData)
{
    HI_S32 i;

    SAMPLE_PRINT("Print in process %d, %s\n", (HI_S32)getpid(), __FUNCTION__);
    SAMPLE_PRINT("Argc: %d \n", u32Argc);
    for (i=0; i<u32Argc; i++)
    {
        SAMPLE_PRINT("\tArgv[%d]: %s \n", i, (HI_CHAR*)pu8Argv[i]);
    }

    return HI_SUCCESS;
}

HI_S32 main(HI_VOID)
{
    HI_S32 s32Ret;
    SVR_PROCENTRY_S stEntry1;
    SVR_PROCENTRY_S stEntry2;
    SVR_PROCENTRY_S stEntry3;
    SVR_PROCENTRY_S stEntry4;
    HI_CHAR aszInputCmd[16];

    HI_SYS_Init();
    //SVR_MODULE_Register(HI_ID_USR_START, "TestModule");

    /* Will be added at /proc/hisi/ directory */
    s32Ret = SVR_PROC_AddDir(DIRNAME);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRINT("HI_PROC_AddDir(\"%s\") return %d\n", DIRNAME, s32Ret);
        goto sys_deinit;
    }

    /* Will be added at /proc/hisi/${DIRNAME} directory */
    stEntry1.pszDirectory = DIRNAME;
    stEntry1.pszEntryName = ENTRYNAME1;
    stEntry1.pfnShowProc = Proc_Test_Show1;
    stEntry1.pfnCmdProc = Proc_Test_Cmd1;
    stEntry1.pPrivData = HI_NULL;
    s32Ret = SVR_PROC_AddEntry(MODULE_ID, &stEntry1);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRINT("SVR_PROC_AddEntry(\"%s\") return %d\n", ENTRYNAME1, s32Ret);
        goto remove_dir;
    }

    /* Will be added at /proc/hisi/${DIRNAME} directory */
    stEntry2.pszDirectory = DIRNAME;
    stEntry2.pszEntryName = ENTRYNAME2;
    stEntry2.pfnShowProc = Proc_Test_Show2;
    stEntry2.pfnCmdProc = Proc_Test_Cmd2;
    stEntry2.pPrivData = HI_NULL;
    s32Ret = SVR_PROC_AddEntry(MODULE_ID, &stEntry2);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRINT("SVR_PROC_AddEntry(\"%s\") return %d\n", ENTRYNAME2, s32Ret);
        goto remove_entry1;
    }

    /* Only support echo, will be added at /proc/hisi/${DIRNAME} directory */
    stEntry3.pszDirectory = DIRNAME;
    stEntry3.pszEntryName = ENTRYNAME3;
    stEntry3.pfnShowProc = HI_NULL;
    stEntry3.pfnCmdProc = Proc_Test_Cmd2;
    stEntry3.pPrivData = HI_NULL;
    s32Ret = SVR_PROC_AddEntry(MODULE_ID, &stEntry3);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRINT("SVR_PROC_AddEntry(\"%s\") return %d\n", ENTRYNAME3, s32Ret);
        goto remove_entry2;
    }

    /* Only support cat, Will be added at /proc/hisi/${DIRNAME} directory */
    stEntry4.pszDirectory = DIRNAME;
    stEntry4.pszEntryName = ENTRYNAME4;
    stEntry4.pfnShowProc = Proc_Test_Show2;
    stEntry4.pfnCmdProc = HI_NULL;
    stEntry4.pPrivData = HI_NULL;
    s32Ret = SVR_PROC_AddEntry(MODULE_ID, &stEntry4);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRINT("SVR_PROC_AddEntry(\"%s\") return %d\n", ENTRYNAME4, s32Ret);
        goto remove_entry3;
    }

    while (1)
    {
        //SAMPLE_GET_INPUTCMD(aszInputCmd);
        if ('q' == aszInputCmd[0])
        {
            break;
        }

        sleep(1);
    }

    SVR_LOG_DOFUNC(SVR_PROC_RemoveEntry(MODULE_ID, &stEntry4));

remove_entry3:
    SVR_LOG_DOFUNC(SVR_PROC_RemoveEntry(MODULE_ID, &stEntry3));

remove_entry2:
    SVR_LOG_DOFUNC(SVR_PROC_RemoveEntry(MODULE_ID, &stEntry2));

remove_entry1:
    SVR_LOG_DOFUNC(SVR_PROC_RemoveEntry(MODULE_ID, &stEntry1));

remove_dir:
    SVR_LOG_DOFUNC(SVR_PROC_RemoveDir(DIRNAME));

sys_deinit:
    SVR_LOG_DOFUNC(SVR_MODULE_UnRegister(MODULE_ID));
    HI_SYS_DeInit();
    return 0;
}
