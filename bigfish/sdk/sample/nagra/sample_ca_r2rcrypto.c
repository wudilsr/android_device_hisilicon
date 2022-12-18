/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_r2rcrypt.c
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
#include "cfg_nagra.h"
#include "hi_unf_cipher.h"

#define TEXT_LEN 16

#define NAGRA_TEST_PRINT(fmt,args...)\
do\
{\
    HI_DEBUG_NAGRA("%s() %d, " fmt,__FUNCTION__,__LINE__,##args);\
}while(0)

const TCsdUnsignedInt8 g_R2RInput[TEXT_LEN] =
                               {0xa0, 0x26, 0x00, 0xec, 0xb8, 0xea, 0x77, 0x62,
                                0x5b, 0xba, 0x66, 0x41, 0xed, 0x5f, 0x59, 0x20};

const TCsdR2RCipheredProtectingKeys g_R2RCipheredProtectingKey =
        {{0xe4, 0x21, 0x13, 0xa7, 0x99, 0xca, 0xf4, 0xc7,
          0x05, 0xff, 0x14, 0x32, 0x23, 0x32, 0x91, 0xcb}};

const TCsdUnsignedInt8 g_R2RCipheredContentKey[16] = 
        {0xe4, 0x21, 0x13, 0xa7, 0x99, 0xca, 0xf4, 0xc7,
          0x05, 0xff, 0x14, 0x32, 0x23, 0x32, 0x91, 0xcb};

/*lint -save -e818 ignored by m00190812*/
HI_S32 main(HI_S32 argc,HI_CHAR** argv)
{
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_S32 Ret = HI_SUCCESS;
    HI_HANDLE hCipher = 0;
    TCsdR2RKeyPathHandle stR2RKeyPathHandle;
    TCsdUnsignedInt8 dataIn[TEXT_LEN];
    TCsdUnsignedInt8 dataOut[TEXT_LEN];
    TCsdUnsignedInt16 i;
    HI_UNF_CIPHER_ATTS_S  stCipherAttr;

    Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_CIPHER_Init error, Ret=0x%x\n",Ret);
        return CSD_ERROR;
    }
    
    /* Initialize the CSD driver if this is not already done */
    csdRet = csdInitialize(NULL);
    if (CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Initialize ERROR!!!!csdRet = 0x%x\n", csdRet);
        goto _CIPHER_CLOSE;
    }    
    
    memset(&stCipherAttr, 0, sizeof(stCipherAttr));
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&hCipher, &stCipherAttr);
    if(HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_CIPHER_CreateHandle error, Ret=0x%x\n",Ret);
        csdRet = CSD_ERROR;
        goto _CSD_DEINIT;
    }
    stR2RKeyPathHandle.handle = hCipher;

    HI_TRACE_LOG("contents of plain buf is: \n");
    for(i = 0;i < TEXT_LEN; i++)
    {
        HI_TRACE_LOG("0x%02x ",g_R2RInput[i]);
    }
    HI_TRACE_LOG("\n");
    
    memcpy(dataIn, g_R2RInput, sizeof(g_R2RInput));

    (HI_VOID)csdEncryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
                                CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
                                g_R2RCipheredProtectingKey,
                                g_R2RCipheredContentKey,
                                16,
                                NULL, 0, FALSE,
                                &stR2RKeyPathHandle,
                                dataIn,
                                dataOut,
                                TEXT_LEN);
    
    HI_TRACE_LOG("after encrypt the plain buf ,contents of encrypted buf is: \n");
    for(i = 0;i < TEXT_LEN; i++)
    {
        HI_TRACE_LOG("0x%02x ",dataOut[i]);
    }
    HI_TRACE_LOG("\n");
    
    memcpy(dataIn, dataOut, sizeof(dataOut));

    (HI_VOID)csdDecryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
                                CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
                                g_R2RCipheredProtectingKey,
                                g_R2RCipheredContentKey,
                                16,
                                NULL, 0, FALSE,
                                &stR2RKeyPathHandle,
                                dataIn,
                                dataOut,
                                TEXT_LEN);

    HI_TRACE_LOG("after decrypt the encrypted buf ,contents of result buf is: \n");
    for(i = 0;i < TEXT_LEN; i++)
    {
        HI_TRACE_LOG("0x%02x ",dataOut[i]);
    }
    HI_TRACE_LOG("\n");
    
    if(!memcmp(g_R2RInput, dataOut, TEXT_LEN))
    {
        HI_TRACE_LOG("contents of plain buf and result buf is the same ,test successful!\n");
    }
    else
    {
        HI_TRACE_LOG("contents of plain buf and result buf is different ,test failed!\n");
    }

    if(0 != hCipher)
    {
        (HI_VOID)HI_UNF_CIPHER_DestroyHandle(hCipher);
        hCipher = 0;
    }
    
_CSD_DEINIT:
    (HI_VOID)csdTerminate(NULL);

_CIPHER_CLOSE:
    (HI_VOID)HI_UNF_CIPHER_DeInit();
    
    return csdRet;
}

