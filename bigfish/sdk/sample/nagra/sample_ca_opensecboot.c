/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_opensecboot.c
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
#include <string.h>

#include "nocs_csd_impl.h"
#include "nocs_csd.h"
#include "cfg_nagra.h"

/*lint -save -e818 ignored by m00190812*/
HI_S32 main(HI_S32 argc,HI_CHAR**argv)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdBootMode enFlashType;

    if (argc < 2)
    {
        HI_TRACE_LOG("usage:opensecboot flashtype[spi|nand]\n");
        return HI_FAILURE;
    }

    if(0 == strncmp(argv[1],"spi", 3))
    {
        enFlashType = CSD_FLASH_TYPE_SPI;
    }
    else if(0 == strncmp(argv[1],"nand", 4))
    {
        enFlashType = CSD_FLASH_TYPE_NAND;
    }
    else
    {
        HI_TRACE_LOG("usage:opensecboot flashtype[spi|nand]\n");
        return HI_FAILURE;
    }


    Ret = csdInitialize(HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_NAGRA("csdInitialize failed! Ret = %x\n", Ret);
        return HI_FAILURE;
    }

    Ret = csdSetBootMode(enFlashType);
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_NAGRA("Set boot mode failed! Ret = %x\n", Ret);
        goto _TERMINATE;
    }
    
    Ret = csdEnableScs();
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_NAGRA("Enable Secure Boot failed! Ret = %x\n", Ret);
    }
    else
    {
        HI_TRACE_LOG("Open Secure Boot success!\n");
    }

_TERMINATE:
    (HI_VOID)csdTerminate(HI_NULL);   

    return Ret;
}

