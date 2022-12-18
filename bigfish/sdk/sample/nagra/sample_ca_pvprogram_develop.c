/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_pvprogram_develop.c
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
#include <sys/ioctl.h>

#include "nocs_csd_impl.h"
#include "nocs_csd.h"
#include "hi_unf_advca.h"
#include "advca_priv.h"
#include "cfg_nagra.h"
#include "hi_drv_struct.h"

#define CSD_MAX_CMDLINE_LEN  1280
#define CSD_MAX_ARGS_COUNT   20
#define CSD_MAX_ARGS_LEN     128
#define PV_MAX_NUM           6

static HI_CHAR g_CSDCmdLine[CSD_MAX_CMDLINE_LEN];
static HI_S32 g_CSDArgc;
static HI_CHAR g_CSDArgv[CSD_MAX_ARGS_COUNT][CSD_MAX_ARGS_LEN];
static TCsdBoolean g_csdMainRun = TRUE;                     /*the running flag of main menu*/

/** PV index*/
typedef enum hiPV_INDEX_E
{
    HI_PV_INDEX_BOOT_MODE = 0,
    HI_PV_INDEX_SCS,
    HI_PV_INDEX_JTAG_PRT_MODE,
    HI_PV_INDEX_SELF_BOOT,
    HI_PV_INDEX_MSID,
    HI_PV_INDEX_STBSN
}HI_PV_INDEX_E;
    
HI_CHAR g_PVName[PV_MAX_NUM][32] = {
    "boot_mode_sel", "SCS_activation", "jtag_prt_mode", "self_boot_disable", "MSID", "STB_SN"};

HI_U32 g_PVLength[PV_MAX_NUM] = {2, 1, 2, 1, 32, 32};

/*lint -save -e785 ignored by m00190812*/
TCsdUnsignedInt8 g_PVMeaning[PV_MAX_NUM][5][16] = {
    {"SPI", "NAND", "UNKNOWN"}, {"DEACTIVE", "ACTIVE", "UNKNOWN"},
    {"OPEN", "PROTECTED", "CLOSED", "CLOSED", "UNKNOWN"}, {"ENABLE", "DISABLE", "UNKNOWN"}, {{}}, {{}}};

HI_S32 g_CAFd = -1;

HI_S32 parse_CSDcmdline(HI_CHAR*pCmdLine,HI_S32*pArgc,HI_CHAR pArgv[CSD_MAX_ARGS_COUNT][CSD_MAX_ARGS_LEN])
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

    return HI_SUCCESS;
}

void printMainMenu()
{
    int i;
    HI_TRACE_LOG("Please select an item to continue:\n");
    for ( i = 0 ; i < PV_MAX_NUM ; i++ )
    {
        HI_TRACE_LOG("[%d] %s\n", i, g_PVName[i]);
    }
    HI_TRACE_LOG("[q] Quit application\n");
}

HI_S32 getValueFromCfgFile(HI_U32 bitFieldNumber, TCsdUnsignedInt8 *pBitFieldValue)
{
    FILE *cfgFile = NULL;
    HI_CHAR u8Value[512] = {0};
    HI_U32 tempFlag = 0;
    HI_CHAR tempName[32] = {0};
    HI_U32 u32Value = 0;
    HI_U32 i = 0;
    
    if (NULL == (cfgFile = fopen("pvprogram.cfg", "rb")))
    {
        HI_DEBUG_NAGRA("Open config file ERROR!\n");
        return HI_FAILURE;
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
    
    return HI_SUCCESS;
}

HI_S32 getUserChoice(TCsdUnsignedInt8 *pUserChoice)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_CHAR *pCSDCmdLine;
    
    pCSDCmdLine = fgets(g_CSDCmdLine,CSD_MAX_CMDLINE_LEN,stdin);
    if (HI_NULL == pCSDCmdLine)
    {
        return HI_FAILURE;
    }

    Ret = parse_CSDcmdline(pCSDCmdLine, &g_CSDArgc,g_CSDArgv);
    if ((HI_SUCCESS != Ret) || (1 != g_CSDArgc))
    {
        return HI_FAILURE;
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
        Ret = HI_FAILURE;
    }

    return Ret;
}

HI_S32 printBitFieldValue(HI_U32 pBitFieldNumber)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 i;
    HI_U32 bitFieldLength;
    HI_U32 numberOfBytes;
    TCsdUnsignedInt8 meaningIndex = 0;
    HI_UNF_ADVCA_JTAG_MODE_E jtagPrtMode = HI_UNF_ADVCA_JTAG_MODE_BUTT;
    HI_UNF_ADVCA_FLASH_TYPE_E flashType = HI_UNF_ADVCA_FLASH_TYPE_BUTT;
    HI_U32 u32BitFieldValue = 0;
    TCsdUnsignedInt8 u8BitFieldValue[512] = {0};

    bitFieldLength = g_PVLength[pBitFieldNumber];
    numberOfBytes = (bitFieldLength + 7) / 8;

    switch (pBitFieldNumber)
    {
        case HI_PV_INDEX_BOOT_MODE:
            Ret = ioctl(g_CAFd, CMD_CA_GETBOOTMODE, &flashType);
            u32BitFieldValue = (HI_U32)flashType;
            break;
        case HI_PV_INDEX_SCS:
            Ret = ioctl(g_CAFd, CMD_CA_GETSCSACTIVE, &u32BitFieldValue);
            break;
        case HI_PV_INDEX_JTAG_PRT_MODE:
            Ret = ioctl(g_CAFd, CMD_CA_GETJTAGPRTMODE, &jtagPrtMode);
            u32BitFieldValue = (HI_U32)jtagPrtMode;
            break;
        case HI_PV_INDEX_SELF_BOOT:
            Ret = ioctl(g_CAFd, CMD_CA_GET_SELFBOOT, &u32BitFieldValue);
            break;
        case HI_PV_INDEX_MSID:
            Ret = ioctl(g_CAFd, CMD_CA_GETMARKETID, &u32BitFieldValue);
            for ( i = 0 ; i < 4 ; i++ )
            {
                u8BitFieldValue[i] = u32BitFieldValue >> ((3 - i) * 8) & 0xff;
            }
            break;
        case HI_PV_INDEX_STBSN:
            Ret = ioctl(g_CAFd, CMD_CA_GETSTBSN, &u32BitFieldValue);
            for ( i = 0 ; i < 4 ; i++ )
            {
                u8BitFieldValue[i] = u32BitFieldValue >> ((3 - i) * 8) & 0xff;
            }
            break;
        default:
            HI_TRACE_LOG("\033[0;32m""Invalid choice!\n""\033[0m");
    }

    if (HI_SUCCESS != Ret)
    {
        HI_TRACE_LOG("\033[0;32m""Get bit field value failure!\n""\033[0m");
        return Ret;
    }

    if (1 != numberOfBytes)
    {
        HI_TRACE_LOG("\033[0;32m""The current value of %s is: ""\033[0m", g_PVName[pBitFieldNumber]);
    
        for ( i = 0 ; i <  numberOfBytes - 1; i++ )
        {
            if ((numberOfBytes > 16) && ((i % 16) == 0))
            {
                HI_TRACE_LOG("\n");
            }

            HI_TRACE_LOG("0x%02x, ", u8BitFieldValue[i]);
        }
        HI_TRACE_LOG("0x%02x\n", u8BitFieldValue[numberOfBytes - 1]);
    }
    else
    {
        meaningIndex = (TCsdUnsignedInt8)u32BitFieldValue;
        
        HI_TRACE_LOG("\033[0;32m""Title: %s\n""\033[0m", g_PVName[pBitFieldNumber]);
        
        HI_TRACE_LOG("\033[0;32m""Value: ""\033[0m");
        HI_TRACE_LOG("\033[0;32m""0x%02x\n""\033[0m", u32BitFieldValue);

        if ((HI_PV_INDEX_JTAG_PRT_MODE != pBitFieldNumber) && (meaningIndex > 2))
        {
            meaningIndex = 2;
        }
        if ((HI_PV_INDEX_JTAG_PRT_MODE == pBitFieldNumber) && (meaningIndex > 4))
        {
            meaningIndex = 4;
        }

        HI_TRACE_LOG("\033[0;32m""Meaning: %s\n""\033[0m", g_PVMeaning[pBitFieldNumber][meaningIndex]);
    }

    return Ret;
}

/*lint -save -e818 ignored by m00190812*/
HI_S32 setBitFieldValue(HI_U32 pBitFieldNumber, TCsdUnsignedInt8 *pBitFieldValue)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 i = 0;
    HI_UNF_ADVCA_JTAG_MODE_E jtagPrtMode = HI_UNF_ADVCA_JTAG_MODE_BUTT;
    HI_UNF_ADVCA_FLASH_TYPE_E flashType = HI_UNF_ADVCA_FLASH_TYPE_BUTT;
    HI_U32 u32MarketID = 0;
    HI_U32 u32STBCASN = 0;
    
    switch (pBitFieldNumber)
    {
        case HI_PV_INDEX_BOOT_MODE:
            flashType = (HI_UNF_ADVCA_FLASH_TYPE_E)*pBitFieldValue;
            Ret = ioctl(g_CAFd, CMD_CA_SETBOOTMODE, &flashType);
            break;
        case HI_PV_INDEX_SCS:
            if (1 == (*pBitFieldValue))
            {
                Ret = ioctl(g_CAFd, CMD_CA_SETSCSACTIVE, HI_NULL);
            }
            break;
        case HI_PV_INDEX_JTAG_PRT_MODE:
            jtagPrtMode = (HI_UNF_ADVCA_JTAG_MODE_E)*pBitFieldValue;
            Ret = ioctl(g_CAFd, CMD_CA_SETJTAGPRTMODE, &jtagPrtMode);
            break;
        case HI_PV_INDEX_SELF_BOOT:
            if (1 == (*pBitFieldValue))
            {
                Ret = ioctl(g_CAFd, CMD_CA_DISABLESELFBOOT, HI_NULL);
            }
            break;
        case HI_PV_INDEX_MSID:
            for ( i = 0 ; i < 4 ; i++ )
            {
                u32MarketID += *(pBitFieldValue + i) << ((3 - i) * 8);
            }
            
            Ret = ioctl(g_CAFd, CMD_CA_SETMARKETID, &u32MarketID);
            break;
        case HI_PV_INDEX_STBSN:
            for ( i = 0 ; i < 4 ; i++ )
            {
                u32STBCASN += *(pBitFieldValue + i) << ((3 - i) * 8);
            }
            
            Ret = ioctl(g_CAFd, CMD_CA_SETSTBSN, &u32STBCASN);
            break;
        default:
            HI_TRACE_LOG("\033[0;32m""Invalid choice!\n""\033[0m");
    }
    
    return Ret;
}

HI_S32 handleBitField(HI_U32 pBitFieldNumber)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 bitFieldLength;
    TCsdUnsignedInt8 bitFieldValue[512] = {0};
    TCsdUnsignedInt8 userChoice = 0;
    HI_U32 numberOfBytes;
    HI_U32 i;
    TCsdUnsignedInt8 meaningIndex = 0;

    bitFieldLength = g_PVLength[pBitFieldNumber];
    numberOfBytes = (bitFieldLength + 7) / 8;

    Ret = printBitFieldValue(pBitFieldNumber);
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_NAGRA("\033[0;32m""CSD Get PV Value ERROR! Ret = 0x%x\n""\033[0m", Ret);
        return Ret;
    }
    
    HI_TRACE_LOG("Would you like to set %s to a new value? [yes/no]\n", g_PVName[pBitFieldNumber]);

    Ret = getUserChoice(&userChoice);
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_NAGRA("\033[0;32m""Input ERROR! Ret = 0x%x\n""\033[0m", Ret);
        return Ret;
    }
    
    if (1 == userChoice)
    {
        if (1 == bitFieldLength)
        {
            bitFieldValue[0] = 1;
            meaningIndex = bitFieldValue[0];
            
            HI_TRACE_LOG("You want to set %s to %s. Confirm? [yes/no]\n", g_PVName[pBitFieldNumber], g_PVMeaning[pBitFieldNumber][meaningIndex]);
        }
        else if (2 == bitFieldLength)
        {
            Ret = getValueFromCfgFile(pBitFieldNumber, bitFieldValue);
            if (HI_SUCCESS != Ret)
            {
                HI_DEBUG_NAGRA("\033[0;32m""Get Value from \"pvprogram.cfg\" ERROR!Ret = 0x%x\n""\033[0m", Ret);
                return Ret;
            }

            meaningIndex = bitFieldValue[0];

            HI_TRACE_LOG("You want to set %s to %s. Confirm? [yes/no]\n", g_PVName[pBitFieldNumber], g_PVMeaning[pBitFieldNumber][meaningIndex]);
        }
        else
        {
            Ret = getValueFromCfgFile(pBitFieldNumber, bitFieldValue);
            if (HI_SUCCESS != Ret)
            {
                HI_DEBUG_NAGRA("\033[0;32m""Get Value from \"pvprogram.cfg\" ERROR!Ret = 0x%x\n""\033[0m", Ret);
                return Ret;
            }
            
            HI_TRACE_LOG("The value you want to set is: ");
            for ( i = 0 ; i < numberOfBytes - 1; i++ )
            {
                HI_TRACE_LOG("0x%02x ", bitFieldValue[i]);
            }
            HI_TRACE_LOG("0x%02x\n", bitFieldValue[numberOfBytes - 1]);
            
            HI_TRACE_LOG("Confirm? [yes/no]\n");
        }

        Ret = getUserChoice(&userChoice);
        if (HI_SUCCESS != Ret)
        {
            HI_DEBUG_NAGRA("\033[0;32m""Input ERROR! Ret = 0x%x\n""\033[0m", Ret);
            return Ret;
        }

        if (1 == userChoice)
        {
            Ret = setBitFieldValue(pBitFieldNumber, bitFieldValue);
            if (HI_SUCCESS != Ret)
            {
                HI_DEBUG_NAGRA("\033[0;32m""Set PV ERROR! Ret = 0x%x\n""\033[0m", Ret);
                return Ret;
            }
        }
        else
        {
            return HI_SUCCESS;
        }
    }
    else if (0 == userChoice)
    {
        return HI_SUCCESS;
    }
    else
    {
        HI_TRACE_LOG("Invalid Command!\n");
        return HI_FAILURE;
    }

    Ret = printBitFieldValue(pBitFieldNumber);

    return Ret;
}

HI_S32 main_Run_Cmdline(HI_S32 argc,HI_CHAR argv[CSD_MAX_ARGS_COUNT][CSD_MAX_ARGS_LEN])
{
    HI_S32 Ret = HI_FAILURE;
    HI_U32 bitFieldNumber = 0;
    
    if ((argv[0][0] >= '0') && (argv[0][0] <= '9'))
    {
        if ((argv[0][1] >= '0') && (argv[0][1] <= '9'))
        {
            bitFieldNumber = strtol(argv[0], NULL, 0);
        }
        else if (argv[0][1] == '\0')
        {
            bitFieldNumber = strtol(argv[0], NULL, 0);
        }
        else 
        {
            HI_TRACE_LOG("\033[0;32m""Invalid Choice!\n""\033[0m");
            return HI_FAILURE;
        }
        
        if (bitFieldNumber > PV_MAX_NUM)
        {
            HI_TRACE_LOG("\033[0;32m""Invalid Choice!\n""\033[0m");
            return HI_FAILURE;
        }
        Ret = handleBitField(bitFieldNumber);
    }
    else if (!strncmp(argv[0], "q", 1))
    {
        g_csdMainRun = FALSE;
    }
    else 
    {
        HI_TRACE_LOG("Invalid Command\n");
    }

    return Ret;    
}

#ifndef UMAP_DEVNAME_CA
#define UMAP_NAME    "hi_"
#define HI_MOD_CA                   "ca"
#define UMAP_DEVNAME_CA             UMAP_NAME HI_MOD_CA
#endif

int main()
{
    HI_S32 Ret = HI_SUCCESS;
    HI_CHAR *pCSDCmdLine;
    
    g_CAFd = open("/dev/" UMAP_DEVNAME_CA, O_RDWR , 0);
    if (g_CAFd < 0)
    {
        HI_DEBUG_NAGRA("\033[0;32m""CA open ERROR!\n""\033[0m");
        return HI_FAILURE;
    }
    
    HI_TRACE_LOG("\033[0;32m""Please change the values in the \"pvprogram.cfg\" file before using this sample!\n""\033[0m");
    
    while(g_csdMainRun)
    {
        printMainMenu();
        pCSDCmdLine = fgets(g_CSDCmdLine,CSD_MAX_CMDLINE_LEN,stdin);
        if (HI_NULL == pCSDCmdLine)
        {
            continue;
        }

        Ret = parse_CSDcmdline(pCSDCmdLine, &g_CSDArgc,g_CSDArgv);
        if (HI_SUCCESS != Ret || 0 == g_CSDArgc)
        {
            continue;
        }

        Ret |= main_Run_Cmdline(g_CSDArgc,g_CSDArgv);
    }

    close(g_CAFd);
    return Ret;
}

