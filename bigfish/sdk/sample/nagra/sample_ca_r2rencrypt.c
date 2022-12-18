/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_r2rencrypt.c
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
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include "nocs_csd_impl.h"
#include "nocs_csd.h"
#include "cfg_nagra.h"
#include "hi_unf_cipher.h"

#define MAX_LEN (60*1024*1024)

#define NAGRA_TEST_PRINT(fmt,args...)\
do\
{\
    HI_DEBUG_NAGRA("%s() %d, " fmt,__FUNCTION__,__LINE__,##args);\
}while(0)

TCsdBoolean checkEnd(const char *pFileName, const char *pMask)
{
    if (NULL != strstr(pFileName, pMask))
    {
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }
}

static int IsHex(char ptr)
{
    if((ptr >= '0') && (ptr<='9'))
    {
    }
    else if ((ptr >= 'a') && (ptr<='f'))
    {
    }
    else if((ptr >= 'A') && (ptr<='F'))
    {
    }
    else
    {
        return 0;
    }

    return 1;
}

int convertToHex(char ptr)
{
    int u8Value = 0;

    if ((ptr >= '0') && (ptr<='9'))
    {
        u8Value += ptr - '0';
    }
    else if ((ptr >= 'a') && (ptr<='f'))
    {
        u8Value += (ptr - 'a') + 0x0a;
    }
    else if ((ptr >= 'A') && (ptr<='F'))
    {
        u8Value += (ptr - 'A') + 0x0a;
    }

    return u8Value;
}

TCsdStatus secEncryptData(TCsdUnsignedInt8* pxDst,const TCsdUnsignedInt8* pxSrc,TCsdSize xDataLength)
{
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_S32 Ret = HI_SUCCESS;
    TCsdR2RKeyPathHandle stR2RKeyPathHandle;
    HI_HANDLE hCipher = 0;
    const TCsdR2RCipheredProtectingKeys g_R2RCipheredProtectingKeys =
        {{0xe4, 0x21, 0x13, 0xa7, 0x99, 0xca, 0xf4, 0xc7,
        0x05, 0xff, 0x14, 0x32, 0x23, 0x32, 0x91, 0xcb}};
    const TCsdUnsignedInt8 g_CipheredContentKey[16] =
        {0xe4, 0x21, 0x13, 0xa7, 0x99, 0xca, 0xf4, 0xc7,
        0x05, 0xff, 0x14, 0x32, 0x23, 0x32, 0x91, 0xcb};

    HI_UNF_CIPHER_ATTS_S  stCipherAttr;
    
    if ((NULL == pxDst) || (NULL == pxSrc) || (0 != (xDataLength % 8)))
    {
        NAGRA_TEST_PRINT("Parameter ERROR!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    /* Initialize the CSD driver if this is not already done */
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
    
    memset(&stCipherAttr, 0, sizeof(stCipherAttr));
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&hCipher, &stCipherAttr);
    if(HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_CIPHER_CreateHandle error, Ret=0x%x\n",Ret);
        csdRet = CSD_ERROR;
        goto _CIPHER_CLOSE;
    }
    
    stR2RKeyPathHandle.handle= hCipher;
    /* Encrypt Block of Data */
    csdRet = csdEncryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
                CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
                g_R2RCipheredProtectingKeys,
                g_CipheredContentKey,
                16,
                NULL, 0, FALSE,
                &stR2RKeyPathHandle,
                pxSrc,
                pxDst,
                xDataLength);
    if (CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Encrypt ERROR, csdRet = 0x%x\n", csdRet);
    }

    if(0 != hCipher)
    {
        (HI_VOID)HI_UNF_CIPHER_DestroyHandle(hCipher);
        hCipher = 0;
    }
    
_CIPHER_CLOSE:    
    (HI_VOID)HI_UNF_CIPHER_DeInit();
    
_CSD_DEINIT:
    (HI_VOID)csdTerminate(NULL);

    return csdRet;
}

TCsdStatus secDecryptData(TCsdUnsignedInt8* pxDst,const TCsdUnsignedInt8* pxSrc,TCsdSize xDataLength)
{
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_S32 Ret = HI_SUCCESS;
    TCsdR2RKeyPathHandle stR2RKeyPathHandle;
    HI_HANDLE hCipher = 0;
    const TCsdR2RCipheredProtectingKeys g_R2RCipheredProtectingKeys =
        {{0xe4, 0x21, 0x13, 0xa7, 0x99, 0xca, 0xf4, 0xc7,
        0x05, 0xff, 0x14, 0x32, 0x23, 0x32, 0x91, 0xcb}};
    const TCsdUnsignedInt8 g_CipheredContentKey[16] =
        {0xe4, 0x21, 0x13, 0xa7, 0x99, 0xca, 0xf4, 0xc7,
        0x05, 0xff, 0x14, 0x32, 0x23, 0x32, 0x91, 0xcb};

    HI_UNF_CIPHER_ATTS_S  stCipherAttr;
    
    if ((NULL == pxDst) || (NULL == pxSrc) || (0 != (xDataLength % 8)))
    {
        NAGRA_TEST_PRINT("Parameter ERROR!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    /* Initialize the CSD driver if this is not already done */
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
    
    memset(&stCipherAttr, 0, sizeof(stCipherAttr));
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&hCipher, &stCipherAttr);
    if(HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_CIPHER_CreateHandle error, Ret=0x%x\n",Ret);
        csdRet = CSD_NO_ERROR;
        goto _CIPHER_CLOSE;
    }
    
    stR2RKeyPathHandle.handle= hCipher;
    /* Encrypt Block of Data */
    csdRet = csdDecryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
                CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
                g_R2RCipheredProtectingKeys,
                g_CipheredContentKey,
                16,
                NULL, 0, FALSE,
                &stR2RKeyPathHandle,
                pxSrc,
                pxDst,
                xDataLength);
    if (CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Encrypt ERROR, csdRet = 0x%x\n", csdRet);
    }

    if(0 != hCipher)
    {
        (HI_VOID)HI_UNF_CIPHER_DestroyHandle(hCipher);
        hCipher = 0;
    }
    
_CIPHER_CLOSE:    
    (HI_VOID)HI_UNF_CIPHER_DeInit();
    
_CSD_DEINIT:
    (HI_VOID)csdTerminate(NULL);

    return csdRet;
}

/*lint -save -e818 ignored by m00190812*/
int main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32 Ret = HI_FAILURE;
    TCsdStatus csdRet = CSD_NO_ERROR;
    FILE *inputTxtFd = NULL;
    int inputBinFd = -1;
    FILE *outputTxtFd = NULL;
    int outputBinFd = -1;
    HI_U32 len = 0;
    HI_U32 totalLength = 0;
    char tempBuf[2048];
    TCsdUnsignedInt8 *ptrInput = NULL;
    TCsdUnsignedInt8 *ptrOutput = NULL;
    TCsdUnsignedInt16 writeLength = 0;
    HI_U32 i = 0;
    int tempValue = 0;
    HI_U32 tempLength = 0;

    if (3 != argc)
    {
        HI_TRACE_LOG("Usage: r2rencrypt input output\n");
        return Ret;
    }

    ptrInput = (TCsdUnsignedInt8 *)malloc(MAX_LEN);
    if (NULL == ptrInput)
    {
        HI_DEBUG_NAGRA("malloc ERROR!\n");
        return Ret;
    }
    ptrOutput = (TCsdUnsignedInt8 *)malloc(MAX_LEN);
    if (NULL == ptrOutput)
    {
        HI_DEBUG_NAGRA("malloc ERROR!\n");
        goto _FREE_INPUT;
    }

    memset(ptrInput, 0xFF, sizeof(ptrInput));
    memset(ptrOutput, 0xFF, sizeof(ptrOutput));
    memset(tempBuf, 0xFF, sizeof(tempBuf));
    
    if (checkEnd(argv[1], ".txt"))
    {
        inputTxtFd = fopen (argv[1], "r");
        if (NULL == inputTxtFd) 
        {
            HI_DEBUG_NAGRA("open input file ERROR!\n");
        	goto _FREE_OUTPUT;
        }
        
        while ((len = fread(tempBuf, 1L, sizeof(tempBuf), inputTxtFd)) > 0)
        {
            for (i = 0; i < len; i++)
            {
                if (1 != IsHex(tempBuf[i]))
                {
                    continue;
                }
                            
                if (0 == (tempLength % 2))
                {
                    tempValue = convertToHex(tempBuf[i]);
                }
                else
                {
                    tempValue = (tempValue << 4) + convertToHex(tempBuf[i]);
                    *(ptrInput + totalLength + (tempLength / 2)) = (HI_U8)tempValue;
                }
                
                tempLength++;
            }

            totalLength += len;
        }

        fclose(inputTxtFd);
        totalLength = (totalLength + 1) / 2;
    }
    else if (checkEnd(argv[1], ".bin"))
    {
        inputBinFd = open (argv[1], O_RDONLY);
        if (inputBinFd < 0) 
        {
            HI_DEBUG_NAGRA("open input file ERROR!\n");
        	goto _FREE_OUTPUT;
        }

        while ((len = (HI_U32)read(inputBinFd, tempBuf, sizeof(tempBuf))) > 0)
        {
            memcpy(ptrInput + totalLength, tempBuf, len);
            totalLength += len;
        }

        close(inputBinFd);
    }
    else
    {
        HI_TRACE_LOG("Input file format ERROR, only support \".txt\" or \".bin\"\n");
        goto _FREE_OUTPUT;
    }

    HI_TRACE_LOG("totalLength = %d, input file is:\n", totalLength);
    for ( i = 0 ; i < totalLength ; i++ )
    {
        if (0 == (i % 16))
        {
            HI_TRACE_LOG("\n");
        }

        HI_TRACE_LOG("%02x, ", *(ptrInput + i));
    }
    HI_TRACE_LOG("\n");
    
    /*Align with 8 byte*/
    tempLength = totalLength - (totalLength % 8);
    if (totalLength % 8)
    {
        memcpy((ptrOutput + tempLength), (ptrInput + tempLength), (totalLength % 8));
    }

    csdRet = secEncryptData(ptrOutput, ptrInput, tempLength);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("Encrypt Data ERROR! csdRet = 0x%x\n", csdRet);
        Ret = csdRet;
        goto _FREE_OUTPUT;
    }

    HI_TRACE_LOG("output file is:\n");
    for ( i = 0 ; i < totalLength ; i++ )
    {
        if (0 == (i % 16))
        {
            HI_TRACE_LOG("\n");
        }

        HI_TRACE_LOG("%02x, ", *(ptrOutput + i));
    }
    HI_TRACE_LOG("\n");
  
    writeLength = 0;
    memset(tempBuf, 0xFF, sizeof(tempBuf));
    
    if (checkEnd(argv[2], ".txt"))
    {
        outputTxtFd = fopen (argv[2], "w+");
        if (NULL == outputTxtFd) 
        {
            HI_DEBUG_NAGRA("open output file ERROR!\n");
        	goto _FREE_OUTPUT;
        }

        while (writeLength < totalLength)
        {
            if (totalLength < sizeof(tempBuf))
            {
                memcpy(tempBuf, ptrOutput + writeLength, totalLength);
                tempLength = totalLength;
            }
            else
            {
                memcpy(tempBuf, ptrOutput + writeLength, sizeof(tempBuf));
                tempLength = sizeof(tempBuf);
            }

            for ( i = 0 ; i < tempLength ; i++ )
            {
                fprintf(outputTxtFd, "%02x", tempBuf[i]);
            }

            writeLength += (TCsdUnsignedInt16)tempLength;
        }

        fclose(outputTxtFd);
    }
    else if (checkEnd(argv[2], ".bin"))
    {
        outputBinFd = open (argv[2], O_RDWR | O_CREAT, 0777);
        if (outputBinFd < 0) 
        {
            HI_DEBUG_NAGRA("open output file ERROR!\n");
        	goto _FREE_OUTPUT;
        }

        while (writeLength < totalLength)
        {
            if (totalLength < sizeof(tempBuf))
            {
                memcpy(tempBuf, ptrOutput + writeLength, totalLength);
                tempLength = totalLength;
            }
            else
            {
                memcpy(tempBuf, ptrOutput + writeLength, sizeof(tempBuf));
                tempLength = sizeof(tempBuf);
            }

            if ((len = (HI_U32)write(outputBinFd, tempBuf, tempLength))> 0)
            {
                if (len == sizeof(tempBuf))
                {
                    writeLength += (TCsdUnsignedInt16)len;
                }
                else if (len == totalLength)
                {
                    writeLength = (TCsdUnsignedInt16)totalLength;
                }
            }
        }

        close(outputBinFd);
    }
    else
    {
        HI_TRACE_LOG("Output file format ERROR, only support \".txt\" or \".bin\"\n");
        goto _FREE_OUTPUT;
    }

    HI_TRACE_LOG("encrypt SUCCESS!\n");
    Ret = HI_SUCCESS;
    
_FREE_OUTPUT:
    free(ptrOutput);

_FREE_INPUT:
    free(ptrInput);

    return Ret;
}


