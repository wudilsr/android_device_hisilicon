/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : pvr_rec.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
  History       :
  1.Date        : 2010/01/26
    Author      : q46153
    Modification: Created file

******************************************************************************/
#include <stdlib.h>

#include "hi_common.h"

#include "svr_debug.h"


SVR_MODULE_DECLARE("SAMPLE_MOD");

extern HI_VOID Module_Printf(HI_VOID);

/* NOTES:
This test case need the config "HI_LOG_UDISK_SUPPORT" to be set "y", otherwise, meaningless.
*/
HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32 Ret;

    HI_SYS_Init();

    HI_SYS_SetStorePath("/opt/");

    Ret = HI_MODULE_Register(HI_ID_USR_START, "LogPathTest");
    if (Ret != HI_SUCCESS)
    {
        SVR_LOG_ERROR("HI_MODULE_Register LogPathTest failure!\n");

        HI_SYS_DeInit();

        return -1;
    }

    //1. Not to set the log path
    SVR_LOG_ERROR("This log info should been print out from serial...\n");

    //2. Set the path with NULL
    Ret = HI_SYS_SetLogPath(NULL);
    if (Ret != HI_SUCCESS)
    {
        SVR_LOG_ERROR("HI_SYS_SetLogPath failure!, but this case is normal with NULL ...\n");
    }
    SVR_LOG_ERROR("This log info should been print out from serial line:%d...\n", __LINE__);

    //3. Set the path with non-exist path
    Ret = HI_SYS_SetLogPath("/abc");
    if (Ret != HI_SUCCESS)
    {
        SVR_LOG_ERROR("HI_SYS_SetLogPath failure!, but this case is normal with non-exist path:/abc...\n");
    }
    usleep(50000);

    SVR_LOG_ERROR("This log info should been print out from serial:%d...\n", __LINE__);

    usleep(50000);

    //4. Set the path with normal path
    Ret = HI_SYS_SetLogPath("/tmp");
    if (Ret != HI_SUCCESS)
    {
        SVR_LOG_ERROR("HI_SYS_SetLogPath with /tmp failure !....\n");
    }

    usleep(50*10000);

    SVR_LOG_ERROR("This log info should print out to /tmp/stb.log :%d...\n", __LINE__);

    usleep(50*10000);

    //5. Set the path with normal /dev/null
    Ret = HI_SYS_SetLogPath("/dev/null");
    if (Ret != HI_SUCCESS)
    {
        SVR_LOG_ERROR("HI_SYS_SetLogPath with /dev/null failure!....\n");
    }
    SVR_LOG_ERROR("You should see this print from serial:%d...\n", __LINE__);

    usleep(50000);

    //5. Set the only read file
    //Ret = HI_SYS_SetLogPath("./testlog.txt");
    //if (Ret != HI_SUCCESS)
    //{
      //  SVR_LOG_ERROR("HI_SYS_SetLogPath with read-only file:./testlog.txt failure!....\n");
   // }

    while(1)
    {
        SVR_LOG_ERROR("print out come from while, %d...\n", __LINE__);
        sleep(10);
    }

    HI_MODULE_UnRegister(HI_ID_USR_START);

    HI_SYS_DeInit();

    SVR_LOG_INFO("%s exit with 0\n", __func__);

    return 0;
}
