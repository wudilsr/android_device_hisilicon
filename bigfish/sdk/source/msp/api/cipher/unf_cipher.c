/******************************************************************************
 
  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.
 
 ******************************************************************************
  File Name     : unf_cipher.c
  Version       : Initial Draft
  Author        : Q46153
  Created       : 2010/3/16
  Last Modified :
  Description   : unf of cipher 
  Function List :
  History       :
  1.Date        : 2010/3/16
    Author      : Q46153
    Modification: Created file
 
******************************************************************************/

#include "hi_mpi_cipher.h"

HI_S32 HI_UNF_CIPHER_Init(HI_VOID)
{
    return HI_MPI_CIPHER_Init();
}

HI_S32 HI_UNF_CIPHER_DeInit(HI_VOID)
{
    return HI_MPI_CIPHER_DeInit();
}

HI_S32 HI_UNF_CIPHER_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr)
{
    return HI_MPI_CIPHER_CreateHandle(phCipher, pstCipherAttr);
}

HI_S32 HI_UNF_CIPHER_DestroyHandle(HI_HANDLE hCipher)
{
    return HI_MPI_CIPHER_DestroyHandle(hCipher);
}

HI_S32 HI_UNF_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    return HI_MPI_CIPHER_ConfigHandle(hCipher, pstCtrl);
}

HI_S32 HI_UNF_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    return HI_MPI_CIPHER_Encrypt(hCipher, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength);
}

HI_S32 HI_UNF_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    return HI_MPI_CIPHER_Decrypt(hCipher, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength);
}

HI_S32 HI_UNF_CIPHER_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    return HI_MPI_CIPHER_EncryptMulti(hCipher, pstDataPkg, u32DataPkgNum);
}

HI_S32 HI_UNF_CIPHER_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    return HI_MPI_CIPHER_DecryptMulti(hCipher, pstDataPkg, u32DataPkgNum);
}

HI_S32 HI_UNF_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber)
{
	return HI_MPI_CIPHER_GetRandomNumber(pu32RandomNumber, -1);
}

HI_S32 HI_UNF_CIPHER_GetHandleConfig(HI_HANDLE hCipherHandle, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    return HI_MPI_CIPHER_GetHandleConfig(hCipherHandle, pstCtrl);
}

HI_S32 HI_UNF_CIPHER_CalcMAC(HI_HANDLE hCipherHandle, HI_U8 *pInputData, HI_U32 u32InputDataLen,
                                        HI_U8 *pOutputMAC, HI_BOOL bIsLastBlock)
{
    return HI_MPI_CIPHER_CalcMAC(hCipherHandle, pInputData, u32InputDataLen, pOutputMAC, bIsLastBlock);
}

HI_S32 HI_UNF_CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    return HI_MPI_CIPHER_HashInit(pstHashAttr, pHashHandle);
}

HI_S32 HI_UNF_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    return HI_MPI_CIPHER_HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);
}

HI_S32 HI_UNF_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    return HI_MPI_CIPHER_HashFinal(hHashHandle, pu8OutputHash);
}


