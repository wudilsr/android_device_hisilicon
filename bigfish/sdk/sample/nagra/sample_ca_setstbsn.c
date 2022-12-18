/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_setstbsn.c
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

/********************** Global Variable declaration **************************/
#define MAX_CMDLINE_LEN  1280
#define MAX_ARGS_COUNT   20
#define MAX_ARGS_LEN     128

static HI_CHAR g_CmdLine[MAX_CMDLINE_LEN];
static HI_S32 g_Argc;
static HI_CHAR g_Argv[MAX_ARGS_COUNT][MAX_ARGS_LEN];

/******************************* API declaration *****************************/
HI_S32 parse_cmdline(HI_CHAR *pCmdLine, HI_S32 *pArgc, HI_CHAR pArgv[MAX_ARGS_COUNT][MAX_ARGS_LEN])
{
    HI_CHAR *ptr = pCmdLine;
    int i;

    while ((*ptr == ' ') && (*ptr++ != '\0'))
    {
        ;
    }

    for (i = (int)strlen(ptr); i > 0; i--)
    {
        if ((*(ptr + i - 1) == 0x0a) || (*(ptr + i - 1) == ' '))
        {
            *(ptr + i - 1) = '\0';
        }
        else
        {
            break;
        }
    }

    for (i = 0; i < MAX_ARGS_COUNT; i++)
    {
        int j = 0;
        while ((*ptr == ' ') && (*(++ptr) != '\0'))
        {
            ;
        }

        while ((*ptr != ' ') && (*ptr != '\0') && (j < MAX_ARGS_LEN))
        {
            pArgv[i][j++] = *ptr++;
        }

        pArgv[i][j] = '\0';
        if ('\0' == *ptr)
        {
            i++;
            break;
        }
    }
    *pArgc = i;

    return HI_SUCCESS;
}

HI_S32 getUserChoice(HI_U8 *pUserChoice)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CHAR *pCmdLine;
    
    pCmdLine = fgets(g_CmdLine,MAX_CMDLINE_LEN,stdin);
    if (HI_NULL == pCmdLine)
    {
        return HI_FAILURE;
    }

    s32Ret = parse_cmdline(pCmdLine, &g_Argc,g_Argv);
    if (HI_SUCCESS != s32Ret || 1 != g_Argc)
    {
        return HI_FAILURE;
    }

    if (!strncmp(g_Argv[0], "yes", 3))
    {
        *pUserChoice = 1;
    }
    else if (!strncmp(g_Argv[0], "no", 2))
    {
        *pUserChoice = 0;
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

/*lint -save -e818 ignored by m00190812*/
static HI_BOOL IsHex(HI_CHAR *ptr)
{
    int i, strlength;
    strlength = (int)strlen(ptr);

    if(strlength > 2)
    {
        return HI_FALSE;
    }

    for (i = 0; i < strlength ; i++)
    {
        if((ptr[i] >= '0') && (ptr[i]<='9'))
        {
        }
        else if ((ptr[i] >= 'a') && (ptr[i]<='f'))
        {
        }
        else if((ptr[i] >= 'A') && (ptr[i]<='F'))
        {
        }
        else
        {
            return HI_FALSE;
        }
    }
    return HI_TRUE;
}

/*Turn the user's input into HEX*/
HI_U8 convertToHex(HI_CHAR* ptr)
{
    int i, strlength;
    HI_U8 u8Value = 0;

    strlength = (int)strlen(ptr);

    for (i = 0; i < strlength; i++)
    {
        if ((ptr[i] >= '0') && (ptr[i]<='9'))
        {
            u8Value += (HI_U8)(ptr[i] - '0');
        }
        else if ((ptr[i] >= 'a') && (ptr[i]<='f'))
        {
            u8Value += (HI_U8)(ptr[i] - 'a') + 0x0a;
        }
        else if ((ptr[i] >= 'A') && (ptr[i]<='F'))
        {
            u8Value += (HI_U8)(ptr[i] - 'A') + 0x0a;
        }

        if ((0 == i) && (2 == strlength))
        {
            u8Value <<= 4;
        }
    }

    return u8Value;
}

HI_S32 getInputValue(HI_U32 length, HI_U8 *pxValue)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_CHAR *pCmdLine;
    HI_U32 i;
    
    pCmdLine = fgets(g_CmdLine,MAX_CMDLINE_LEN,stdin);
    if (HI_NULL == pCmdLine)
    {
        return HI_FAILURE;
    }
    
    Ret = parse_cmdline(pCmdLine, &g_Argc,g_Argv);
    if (HI_SUCCESS != Ret || length != (HI_U32)g_Argc)
    {
        return HI_FAILURE;
    }

    for ( i = 0  ; i < length ; i++ )
    {
        if (!IsHex(g_Argv[i]))
        {
            return HI_FAILURE;
        }
        
        pxValue[i] = convertToHex(g_Argv[i]);
    }

    return Ret;
}

HI_S32 main(HI_S32 argc,HI_CHAR**argv)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U8 userChoice = 0;
    TCsd4BytesVector stbsn = {0};

    Ret = csdInitialize(HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_NAGRA("csdInitialize failed! Ret = %x\n", Ret);
        return HI_FAILURE;
    }
    
    HI_TRACE_LOG("\033[0;32m""Please Input the value you want to set:(STBCASN is 4 Bytes long. Note that every byte should be seperated by space)\n0x""\033[0m");
    
    Ret = getInputValue(4, stbsn);
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_NAGRA("Input Value ERROR!Ret = 0x%x\n", Ret);
        goto TERMINATE;
    }
    
    HI_TRACE_LOG("You want to set STBSN to 0x%02x%02x%02x%02x, Confirm?[yes/no]\n", stbsn[0], stbsn[1], stbsn[2], stbsn[3]);
    
    Ret = getUserChoice(&userChoice);
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_NAGRA("Invalid value!\n");
        goto TERMINATE;
    }

    if (1 == userChoice)
    {
        Ret = csdSetStbCaSn(stbsn);
        if (HI_SUCCESS != Ret)
        {
            HI_TRACE_LOG("Set STBSN failed! Ret = %x\n", Ret);
        }
        else
        {
            HI_TRACE_LOG("Set STBSN success!\n");
        }
    }

TERMINATE:
    (HI_VOID)csdTerminate(HI_NULL);

    return Ret;
}

