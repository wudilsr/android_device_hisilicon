/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_pvprogram_product.c
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
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>

#include "nocs_csd_impl.h"
#include "nocs_csd.h"
#include "cfg_nagra.h"
#include "hi_drv_struct.h"

#define CSD_MAX_CMDLINE_LEN  1280
#define CSD_MAX_ARGS_COUNT   20
#define CSD_MAX_ARGS_LEN     128
#define PV_MAX_NUM           5

static HI_CHAR g_CSDCmdLine[CSD_MAX_CMDLINE_LEN];
static HI_S32 g_CSDArgc;
static HI_CHAR g_CSDArgv[CSD_MAX_ARGS_COUNT][CSD_MAX_ARGS_LEN];
static HI_BOOL g_mainRun = HI_TRUE;

static HI_BOOL g_isValueSet = HI_FALSE;

/** PV index*/
typedef enum hiPV_INDEX_E
{
    HI_PV_INDEX_BOOT_MODE = 0,
    HI_PV_INDEX_SCS,
    HI_PV_INDEX_JTAG_PRT_MODE,
    HI_PV_INDEX_MSID,
    HI_PV_INDEX_STBSN
}HI_PV_INDEX_E;

HI_CHAR g_PVName[PV_MAX_NUM][32] = {
    "boot_mode_sel", "SCS_activation","jtag_prt_mode", "MSID", "STB_SN"};

HI_U32 g_PVLength[PV_MAX_NUM] = {2, 1, 2, 32, 32};

/*lint -save -e785 ignored by m00190812*/
TCsdUnsignedInt8 g_PVMeaning[PV_MAX_NUM][5][16] = 
    {{"SPI", "NAND", "UNKNOWN"}, {"DEACTIVE", "ACTIVE", "UNKNOWN"},
     {"OPEN", "PROTECTED", "CLOSED", "CLOSED", "UNKNOWN"}, {{}}, {{}}};

TCsdStatus getValueFromCfgFile(HI_U32 bitFieldNumber, TCsdUnsignedInt8 *pBitFieldValue)
{
    TCsdStatus csdRet = CSD_NO_ERROR;
    FILE *cfgFile = NULL;
    HI_CHAR u8Value[512] = {0};
    HI_U32 tempFlag = 0;
    HI_CHAR tempName[32] = {0};
    HI_U32 u32Value = 0;
    HI_U32 i = 0;
    
    if (NULL == (cfgFile = fopen("pvprogram.cfg", "rb")))
    {
        HI_DEBUG_NAGRA("Open config file ERROR!\n");
        return CSD_ERROR;
    }

    while (1)
    {
        if (g_PVLength[bitFieldNumber] > 8)
        {
            /*lint -save -e732 ignored by m00190812*/
            tempFlag = fscanf(cfgFile, "%32s = 0x%08x\n", tempName, &u32Value);
            
            for ( i = 0 ; i < 4 ; i++ )
            {
                u8Value[i] = (HI_CHAR)(u32Value >> ((3 - i) * 8) & 0xff);
            }
        }
        else
        {
            tempFlag = fscanf(cfgFile, "%32s = %1024d\n", tempName, (HI_U32*)&u8Value[0]);
        }
        
        if ((tempFlag > 0) && (0 == strncmp(tempName, g_PVName[bitFieldNumber], strlen(g_PVName[bitFieldNumber]))))
        {
            break;
        }
    }

    memcpy(pBitFieldValue, u8Value, (g_PVLength[bitFieldNumber] + 7) / 8);

    fclose(cfgFile);
    
    return csdRet;
    
}

TCsdStatus parse_CSDcmdline(HI_CHAR*pCmdLine,HI_S32*pArgc,HI_CHAR pArgv[CSD_MAX_ARGS_COUNT][CSD_MAX_ARGS_LEN])
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

    for (i = 0; i < CSD_MAX_ARGS_COUNT; i++)
    {
        int j = 0;
        while ((*ptr == ' ') && (*(++ptr) != '\0'))
        {
            ;
        }

        while ((*ptr != ' ') && (*ptr != '\0') && (j < CSD_MAX_ARGS_LEN))
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

    return CSD_NO_ERROR;
}

TCsdStatus getUserChoice(TCsdUnsignedInt8 *pUserChoice)
{
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_CHAR *pCSDCmdLine;
    
    pCSDCmdLine = fgets(g_CSDCmdLine,CSD_MAX_CMDLINE_LEN,stdin);
    if (HI_NULL == pCSDCmdLine)
    {
        return CSD_ERROR;
    }

    csdRet = parse_CSDcmdline(pCSDCmdLine, &g_CSDArgc,g_CSDArgv);
    if (CSD_NO_ERROR != csdRet || 1 != g_CSDArgc)
    {
        return CSD_ERROR;
    }

    if (!strncmp(g_CSDArgv[0], "yes", 3))
    {
        *pUserChoice = 1;
    }
    else if (!strncmp(g_CSDArgv[0], "no", 2))
    {
        *pUserChoice = 0;
    }
    else
    {
        csdRet = CSD_ERROR;
    }

    return csdRet;
}

TCsdStatus setBitFieldValue(HI_U32 bitFieldNumber)
{
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_U32 bitFieldLength = 0;
    TCsdUnsignedInt8 bitFieldValue[512] = {0};
    TCsdUnsignedInt8 meaningIndex = 0;
    HI_U32 numberOfBytes = 0;
    TCsdUnsignedInt8 userChoice = 0;
    HI_U32 i = 0;
    TCsdBootMode bootMode = LAST_CSD_FLASH_TYPE;
    TCsdDebugInterfaceAccessMode jtagMode = LAST_CSD_DEBUG_INTERFACE_ACCESS_MODE;
    TCsd4BytesVector csdVector = {0};
    
    bitFieldLength = g_PVLength[bitFieldNumber];
    numberOfBytes = (bitFieldLength + 7) / 8;

    if (1 == bitFieldLength)
    {
        bitFieldValue[0] = 1;
        meaningIndex = bitFieldValue[0];
        
        HI_TRACE_LOG("You want to set %s to %s. Confirm? [yes/no]\n", g_PVName[bitFieldNumber], g_PVMeaning[bitFieldNumber][meaningIndex]);
    }
    else if (2 == bitFieldLength)
    {
        csdRet = getValueFromCfgFile(bitFieldNumber, bitFieldValue);
        if (CSD_NO_ERROR != csdRet)
        {
            HI_DEBUG_NAGRA("\033[0;32m""Get Value from \"pvprogram.cfg\" ERROR!csdRet = 0x%x\n""\033[0m", csdRet);
            return csdRet;
        }

        meaningIndex = bitFieldValue[0];

        HI_TRACE_LOG("You want to set %s to %s. Confirm? [yes/no]\n", g_PVName[bitFieldNumber], g_PVMeaning[bitFieldNumber][meaningIndex]);
    }
    else
    {
        csdRet = getValueFromCfgFile(bitFieldNumber, bitFieldValue);
        if (CSD_NO_ERROR != csdRet)
        {
            HI_DEBUG_NAGRA("\033[0;32m""Get Value from \"pvprogram.cfg\" ERROR!csdRet = 0x%x\n""\033[0m", csdRet);
            return csdRet;
        }
        
        HI_TRACE_LOG("You want to set %s to: 0x", g_PVName[bitFieldNumber]);
        for ( i = 0 ; i < numberOfBytes - 1; i++ )
        {
            HI_TRACE_LOG("%02x ", bitFieldValue[i]);
        }
        HI_TRACE_LOG("%02x\n", bitFieldValue[numberOfBytes - 1]);
        
        HI_TRACE_LOG("Confirm? [yes/no]\n");
    }

    csdRet = getUserChoice(&userChoice);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("\033[0;32m""Input ERROR! csdRet = 0x%x\n""\033[0m", csdRet);
        return csdRet;
    }

    if (1 == userChoice)
    {
        switch (bitFieldNumber)
        {
            case HI_PV_INDEX_BOOT_MODE :
                bootMode = (TCsdBootMode)bitFieldValue[0];
                csdRet = csdSetBootMode(bootMode);
                break;
            case HI_PV_INDEX_SCS :
                csdRet = csdEnableScs();
                break;
            case HI_PV_INDEX_JTAG_PRT_MODE :
                jtagMode = (TCsdDebugInterfaceAccessMode)bitFieldValue[0];
                csdRet = csdSelectDebugInterfaceProtectionLevel(jtagMode);
                break;
            case HI_PV_INDEX_MSID :
                memcpy(csdVector, bitFieldValue, 4);
                csdRet = csdSetMarketSegmentId(csdVector);
                break;
            case HI_PV_INDEX_STBSN :
                memcpy(csdVector, bitFieldValue, 4);
                csdRet = csdSetStbCaSn(csdVector);
                break;
            default:
                HI_DEBUG_NAGRA("\033[0;32m""Invalid choice!\n""\033[0m");
                break;
        }
    }
    else
    {
        return CSD_NO_ERROR;
    }

    return csdRet;
}

TCsdStatus isValueSet(HI_BOOL *pbSet)
{
    TCsdStatus csdRet = CSD_NO_ERROR;
    TCsd4BytesVector msidVector = {0};
    TCsd4BytesVector stbcasnVector = {0};
    HI_U32 i = 0;

    csdRet = csdGetMarketSegmentId(msidVector);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("\033[0;32m""Get MSID and STBCASN status ERROR!\n""\033[0m");
        return csdRet;
    }
    
    csdRet = csdGetStbCaSn(stbcasnVector);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("\033[0;32m""Get MSID and STBCASN status ERROR!\n""\033[0m");
        return csdRet;
    }

    for ( i = 0 ; i < 4 ; i++ )
    {
        if (msidVector[i] != 0)
        {
            break;
        }

        if (stbcasnVector[i] != 0)
        {
            break;
        }
    }

    if ((i == 4) && (!g_isValueSet))
    {
        *pbSet = HI_FALSE;
    }
    else
    {
        *pbSet = HI_TRUE;
    }

    return csdRet;
}

void printMainMenu()
{
    HI_TRACE_LOG("Please select an item to continue:\n");
    HI_TRACE_LOG("[1] Set MSID and STBSN\n");
    HI_TRACE_LOG("[2] Set other PVs\n");
    HI_TRACE_LOG("[q] Quit application\n");
}

/*lint -save -e818 ignored by m00190812*/
TCsdStatus main_Run_Cmdline(HI_S32 argc,HI_CHAR argv[CSD_MAX_ARGS_COUNT][CSD_MAX_ARGS_LEN])
{
    TCsdStatus csdRet = CSD_ERROR;
    HI_U32 userChoice = 0;
    HI_BOOL bIsValueSet = HI_FALSE;
    
    if ((argv[0][0] >= '0') && (argv[0][0] <= '9'))
    {
        userChoice = strtol(argv[0], NULL, 0);

        if (1 == userChoice)
        {
            /*set and lock MSID*/
            csdRet = setBitFieldValue(HI_PV_INDEX_MSID);
            if (CSD_NO_ERROR != csdRet)
            {
                HI_DEBUG_NAGRA("\033[0;32m""Set MSID ERROR!ret = 0x%x\n""\033[0m", csdRet);
                return csdRet;
            }
            
            /*set and lock STBSN*/
            csdRet = setBitFieldValue(HI_PV_INDEX_STBSN);
            if (CSD_NO_ERROR != csdRet)
            {
                HI_DEBUG_NAGRA("\033[0;32m""Set STBSN ERROR!ret = 0x%x\n""\033[0m", csdRet);
                return csdRet;
            }
            g_isValueSet = HI_TRUE;
        }
        else if (2 == userChoice)
        {
            /*check if MSID and STBSN are set*/
            csdRet = isValueSet(&bIsValueSet);
            if (CSD_NO_ERROR != csdRet)
            {
                return csdRet;
            }

            if (HI_FALSE == bIsValueSet)
            {
                HI_TRACE_LOG("\033[0;32m""Please set MSID and STBSN first!\n""\033[0m");
                return CSD_ERROR;
            }
            
            /*set and lock bootmode, disable selfboot*/
            csdRet = setBitFieldValue(HI_PV_INDEX_BOOT_MODE);
            if (CSD_NO_ERROR != csdRet)
            {
                HI_DEBUG_NAGRA("\033[0;32m""Set bootmode ERROR!ret = 0x%x\n""\033[0m", csdRet);
                return csdRet;
            }

            /*set jtag protection mode*/
            csdRet = setBitFieldValue(HI_PV_INDEX_JTAG_PRT_MODE);
            if (CSD_NO_ERROR != csdRet)
            {
                HI_DEBUG_NAGRA("\033[0;32m""Set jtag protection mode ERROR!ret = 0x%x\n""\033[0m", csdRet);
                return csdRet;
            }

            /*set SCS Activation*/
            csdRet = setBitFieldValue(HI_PV_INDEX_SCS);
            if (CSD_NO_ERROR != csdRet)
            {
                HI_DEBUG_NAGRA("\033[0;32m""Set SCS Activation ERROR!ret = 0x%x\n""\033[0m", csdRet);
                return csdRet;
            }
        }
        else
        {
            HI_TRACE_LOG("\033[0;32m""Invalid Choice!\n""\033[0m");
            return CSD_ERROR;
        }
    }
    else if (!strncmp(argv[0], "q", 1))
    {
        g_mainRun = HI_FALSE;
    }
    else 
    {
        HI_TRACE_LOG("Invalid Command\n");
    }

    return CSD_NO_ERROR;    
}

int main()
{
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_CHAR *pCSDCmdLine;

    csdRet = csdInitialize(NULL);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("\033[0;32m""CSD Initialize ERROR!csdRet = 0x%x\n""\033[0m", csdRet);
        return CSD_ERROR;
    }
    
    HI_TRACE_LOG("\033[0;32m""Please change the values in the \"pvprogram.cfg\" file before using this sample!\n""\033[0m");

    while(g_mainRun)
    {
        printMainMenu();
        pCSDCmdLine = fgets(g_CSDCmdLine,CSD_MAX_CMDLINE_LEN,stdin);
        if (HI_NULL == pCSDCmdLine)
        {
            continue;
        }

        csdRet = parse_CSDcmdline(pCSDCmdLine, &g_CSDArgc,g_CSDArgv);
        if (CSD_NO_ERROR != csdRet || 0 == g_CSDArgc)
        {
            continue;
        }

        csdRet = main_Run_Cmdline(g_CSDArgc,g_CSDArgv);
        if (CSD_NO_ERROR != csdRet)
        {
            break;
        }
    }

    if (CSD_NO_ERROR != csdRet)
    {
        HI_TRACE_LOG("\033[0;32m""Set All PVs FAILURE!\n""\033[0m");
    }
    else
    {
        HI_TRACE_LOG("\033[0;32m""Set All PVs SUCCESSFULLY!\n""\033[0m");
    }

    (HI_VOID)csdTerminate(NULL);
    return csdRet;
}
