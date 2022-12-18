/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_getchipinfo.c
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

#include "nocs_csd_impl.h"
#include "nocs_csd.h"
#include "hi3716c_Test_Vectors_1_x.h"
#include "hi_unf_cipher.h"
#include "cfg_nagra.h"

#define CHIPSET_MANUFACTURER "HSI"
#define CHIPSET_NAME_C "Hi3716CV2"

#define NAGRA_TEST_PRINT(fmt,args...)\
do\
{\
    HI_DEBUG_NAGRA("%s() %d, " fmt,__FUNCTION__,__LINE__,##args);\
}while(0)

static TCsdUnsignedInt8 g_BootMode_Type[3][20] = {{"SPI FLASH\0"}, {"NAND FLASH\0"}, {"UNKNOWN\0"}};
static TCsdUnsignedInt8 g_Activation_Flag[3][20] = {{"SET\0"}, {"NOT SET\0"}, {"UNKNOWN\0"}};
static TCsdUnsignedInt8 g_TotalArea_Size[8][20] = {{"16K Bytes\0"}, {"32K Bytes\0"}, {"64K Bytes\0"}, 
               {"128K Bytes\0"}, {"256K Bytes\0"}, {"UNPROGRAMMED\0"}, {"NOT SUPPORTED\0"}, {"UNKNOWN\0"}};
static TCsdUnsignedInt8 g_DebugPrt_Level[5][20] = {{"OPEN\0"}, {"PROTECTED\0"}, {"CLOSED\0"}, 
               {"INCONSISTENT STATE\0"}, {"UNKNOWN\0"}};

int main()
{
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_S32 Ret = HI_SUCCESS;
    TCsd20CharsString softwareVersion;
    TCsd20CharsString chipRevision;
    TCsd20CharsString ChipExtension;
    TCsd4BytesVector nuid;
    TCsd4BytesVector nuidCheckNumber;
    TCsd4BytesVector marketSegmentId;
    TCsdBootMode bootMode;
    TCsdScsActivationFlag scsActivationFlag;
    TCsdScsTotalAreaSize totalAreaSize;
    TCsd4BytesVector stbCaSn;
    TCsdDebugInterfaceAccessMode debugPrtLevel;
    TCsdKeyLadderDeactivationFlag keyLadderDeactivationFlag;
    TCsdUnsignedInt8 dvrKey[16];
    TCsdUnsignedInt16 i;

    csdRet = csdInitialize(NULL);
    if (CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Initialize ERROR!!!!csdRet = 0x%x\n", csdRet);
        return csdRet;
    }

    Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_CIPHER_Init error, Ret=0x%x\n",Ret);
        csdRet = CSD_ERROR;
        goto _CSD_DEINIT;
    }
    
    csdRet = csdGetSoftwareVersion(softwareVersion);
    if(CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Get Chip Info ERROR!!!! csdRet = 0x%x\n", csdRet);
        goto _CIPHER_CLOSE;
    }

    csdRet = csdGetChipRevision(chipRevision);
    if(CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Get Chip Info ERROR!!!! csdRet = 0x%x\n", csdRet);
        goto _CIPHER_CLOSE;
    }

    csdRet = csdGetChipExtension(ChipExtension);
    if(CSD_NO_ERROR != csdRet)
    {
        snprintf((HI_CHAR *)ChipExtension, sizeof(ChipExtension), "NULL");
    }
    
    csdRet = csdGetNuid(nuid);
    if(CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Get Chip Info ERROR!!!! csdRet = 0x%x\n", csdRet);
        goto _CIPHER_CLOSE;
    }
    
    csdRet = csdGetMarketSegmentId(marketSegmentId);
    if(CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Get Chip Info ERROR!!!! csdRet = 0x%x\n", csdRet);
        goto _CIPHER_CLOSE;
    }
    
    csdRet = csdGetBootMode(&bootMode);
    if(CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Get Chip Info ERROR!!!! csdRet = 0x%x\n", csdRet);
        goto _CIPHER_CLOSE;
    }
    
    csdRet = csdGetScsActivationFlag(&scsActivationFlag);
    if(CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Get Chip Info ERROR!!!! csdRet = 0x%x\n", csdRet);
        goto _CIPHER_CLOSE;
    }
    
    csdRet = csdGetScsTotalAreaSize(&totalAreaSize);
    if(CSD_NO_ERROR != csdRet)
    {
        totalAreaSize = CSD_SCS_TOTAL_AREA_SIZE_NOT_SUPPORTED;
    }
    
    csdRet = csdGetStbCaSn(stbCaSn);
    if(CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Get Chip Info ERROR!!!! csdRet = 0x%x\n", csdRet);
        goto _CIPHER_CLOSE;
    }
    
    csdRet = csdGetDebugInterfaceProtectionLevel(&debugPrtLevel);
    if(CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Get Chip Info ERROR!!!! csdRet = 0x%x\n", csdRet);
        goto _CIPHER_CLOSE;
    }
    
    csdRet = csdGetKeyLadderDeactivationFlag(&keyLadderDeactivationFlag);
    if(CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Get Chip Info ERROR!!!! csdRet = 0x%x\n", csdRet);
        goto _CIPHER_CLOSE;
    }

    csdRet = csdGetNUIDCheckNumber(nuidCheckNumber);
    if (CSD_NO_ERROR != csdRet)
    {
        memset(nuidCheckNumber, 0, 4);
        csdRet = CSD_NO_ERROR;
    }
    
    csdRet = csdGetDvrKey(dvrKey);
    if (CSD_NO_ERROR != csdRet)
    {
        memset(dvrKey, 0, 16);
        csdRet = CSD_NO_ERROR;
    }

    HI_TRACE_LOG("Chipset Manufacturer: %s\n", CHIPSET_MANUFACTURER);
    
    HI_TRACE_LOG("Chipset Name: %s\n", CHIPSET_NAME_C);
    
    HI_TRACE_LOG("CSD Software Version: %s\n", softwareVersion);
    HI_TRACE_LOG("Chip Revision: %s\n", chipRevision);
    HI_TRACE_LOG("Chip Extension: %s\n", ChipExtension);
    HI_TRACE_LOG("NUID: 0x%02x%02x%02x%02x\n", nuid[0], nuid[1], nuid[2], nuid[3]);
    HI_TRACE_LOG("NUID Check Number: 0x%02x%02x%02x%02x\n", nuidCheckNumber[0], nuidCheckNumber[1], nuidCheckNumber[2], nuidCheckNumber[3]);
    HI_TRACE_LOG("Market Segment ID: 0x%02x%02x%02x%02x\n", marketSegmentId[0], marketSegmentId[1], marketSegmentId[2], marketSegmentId[3]);

    if ((bootMode >= CSD_FLASH_TYPE_SPI) && (bootMode < LAST_CSD_FLASH_TYPE))
    {
        HI_TRACE_LOG("Boot Mode: %s\n", g_BootMode_Type[bootMode]);
    }
    else
    {
        HI_TRACE_LOG("Boot Mode: %s\n", g_BootMode_Type[LAST_CSD_FLASH_TYPE]);
    }

    if ((scsActivationFlag >= CSD_ACTIVATION_FLAG_SET) && (scsActivationFlag < LAST_CSD_ACTIVATION_FLAG))
    {
        HI_TRACE_LOG("SCS Activation Flag: %s\n", g_Activation_Flag[scsActivationFlag]);
    }
    else
    {
        HI_TRACE_LOG("SCS Activation Flag: %s\n", g_Activation_Flag[LAST_CSD_ACTIVATION_FLAG]);
    }

    if ((totalAreaSize >= CSD_SCS_TOTAL_AREA_SIZE_16K) && (totalAreaSize < LAST_CSD_SCS_TOTAL_AREA_SIZE))
    {
        HI_TRACE_LOG("SCS Total Area Size: %s\n", g_TotalArea_Size[totalAreaSize]);
    }
    else
    {
        HI_TRACE_LOG("SCS Total Area Size: %s\n", g_TotalArea_Size[LAST_CSD_SCS_TOTAL_AREA_SIZE]);
    }

    HI_TRACE_LOG("STB CA Serial Number: 0x%02x%02x%02x%02x\n", stbCaSn[0], stbCaSn[1], stbCaSn[2], stbCaSn[3]);

    if ((debugPrtLevel >= CSD_DEBUG_INTERFACE_ACCESS_MODE_OPEN) && (debugPrtLevel < LAST_CSD_DEBUG_INTERFACE_ACCESS_MODE))
    {
        HI_TRACE_LOG("Debug Interface Protection Level: %s\n", g_DebugPrt_Level[debugPrtLevel]);
    }
    else
    {
        HI_TRACE_LOG("Debug Interface Protection Level: %s\n", g_DebugPrt_Level[LAST_CSD_DEBUG_INTERFACE_ACCESS_MODE]);
    }

    if (keyLadderDeactivationFlag < LAST_CSD_ACTIVATION_FLAG)
    {
        HI_TRACE_LOG("Key Ladder Deactivation Flag: %s\n", g_Activation_Flag[keyLadderDeactivationFlag]);
    }
    else
    {
        HI_TRACE_LOG("Key Ladder Deactivation Flag: %s\n", g_Activation_Flag[LAST_CSD_ACTIVATION_FLAG]);
    }

    HI_TRACE_LOG("DVR Key:");
    for ( i = 0 ; i < 15 ; i++ )
    {
        HI_TRACE_LOG("0x%02x, ", dvrKey[i]);
    }
    HI_TRACE_LOG("0x%02x\n\n", dvrKey[15]);

_CIPHER_CLOSE:
    (HI_VOID)HI_UNF_CIPHER_DeInit();
 
_CSD_DEINIT:
    (HI_VOID)csdTerminate(NULL);


    return csdRet;
}

