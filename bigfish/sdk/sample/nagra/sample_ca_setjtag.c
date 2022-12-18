/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_setjtag.c
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "nocs_csd_impl.h"
#include "nocs_csd.h"
#include "cfg_nagra.h"

/*lint -save -e818 ignored by m00190812*/
HI_S32 main(HI_S32 argc,HI_CHAR**argv)
{
    HI_S32 JtagMode = 0;
    HI_S32 Ret = HI_SUCCESS;
    TCsdDebugInterfaceAccessMode enJtagMode;

    if (argc < 2)
    {
        HI_TRACE_LOG("usage:%s mode\n"
               "      mode 0-Opened 1-Password Protected 2-Closed\n",argv[0]);
        return HI_FAILURE;
    }

    JtagMode = atoi(argv[1]);
    switch (JtagMode)
    {
        case 0 :
            enJtagMode = CSD_DEBUG_INTERFACE_ACCESS_MODE_OPEN;
            break;
        case 1 :
            enJtagMode = CSD_DEBUG_INTERFACE_ACCESS_MODE_PASSWORD_PROTECTED;
            break;
        case 2 :
            enJtagMode = CSD_DEBUG_INTERFACE_ACCESS_MODE_CLOSED;
            break;
        default:
            HI_TRACE_LOG("the mode value is invalid\n");
            return HI_FAILURE;
    }


    Ret = csdInitialize(HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_NAGRA("csdInitialize failed! Ret = %x\n", Ret);
        return HI_FAILURE;
    }

    Ret = csdSelectDebugInterfaceProtectionLevel(enJtagMode);
    if (HI_SUCCESS != Ret)
    {
        HI_TRACE_LOG("Set jtag protection mode failed! Ret = %x\n", Ret);
    }
    else
    {
        HI_TRACE_LOG("Set jtag protection mode success!\n");
    }

    (HI_VOID)csdTerminate(HI_NULL);

    return Ret;
}

