/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : ca_authenticate.h
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __CA_AUTHENTICATE_H__
#define __CA_AUTHENTICATE_H__

#include "ca_flash.h"
#include "ca_common.h"

#define SPECIAL_MODE    0
#define COMMON_MODE     1

/* compatible for old interfaces */
#define CA_FlashAuthenticateByName(format, arg...) \
        HI_CA_FlashAuthenticateByName(format, ## arg)

#define CA_FlashAuthenticateByAddr(format, arg...) \
        HI_CA_FlashAuthenticateByAddr(format, ## arg)

#define CA_AuthenticateBootPara(format, arg...) \
        HI_CA_AuthenticateBootPara(format, ## arg)

#define CA_AuthenticateBootParaBak(format, arg...) \
        HI_CA_AuthenticateBootParaBak(format, ## arg)

#define CIPHER_CalcMAC(format, arg...) \
        HI_CA_CalcMAC(format, ## arg)

#ifndef HI_ADVCA_TYPE_VERIMATRIX
#define CA_getExternRsaKey(format, arg...) \
        CA_GetExternRsaKey(format, ## arg)
#endif

#define CA_auth(format, arg...) \
        HI_Android_Authenticate(format, ## arg)

#define CA_CommonVerify_BootPara(format, arg...) \
        HI_CA_CommonVerify_BootPara(format, ## arg)

#define CA_CommonVerify_EncryptImage(format, arg...) \
        HI_CA_CommonVerify_EncryptImage(format, ## arg)

#define CA_Common_VerifyParseSignCommand(format, arg...) \
        CA_Common_VerifyParseSignCommand(format, ## arg)

#define CA_CommonVerify_Section_Signature(format, arg...) \
        HI_CA_CommonVerify_Section_Signature(format, ## arg)

#define CA_CommonVerify_Signature(format, arg...) \
        HI_CA_CommonVerify_Signature(format, ## arg)

#define CA_CheckSoftware(format, arg...) \
        HI_CA_AuthenticateEntry(format, ## arg)

#define CA_DecryptFlashImage2DDR(format, arg...) \
        HI_CA_DecryptFlashImage2DDR(format, ## arg)

#define CA_EncryptDDRImageAndBurnFlashNameByLen(format, arg...) \
        HI_CA_EncryptDDRImageAndBurnFlashNameByLen(format, ## arg)

#define CA_EncryptDDRImageAndBurnFlashName(format, arg...) \
        HI_CA_EncryptDDRImageAndBurnFlashName(format, ## arg)

#define CA_EncryptDDRImageAndBurnFlashAddr(format, arg...) \
        HI_CA_EncryptDDRImageAndBurnFlashAddr(format, ## arg)

#define CA_GetFlashImgInfoByAddr(format, arg...) \
        HI_CA_GetFlashImgInfoByAddr(format, ## arg)

#define CA_GetFlashImgInfoByName(format, arg...) \
        HI_CA_GetFlashImgInfoByName(format, ## arg)

#define CA_ImgAuthenticate(format, arg...) \
        HI_CA_ImgAuthenticate(format, ## arg)



/**
\brief  Authenticate flash contents by partion name
CNcomment:根据flash分区名校验flash内容
\attention \n
如果是加密存储在flash的镜像，会被先解密，然后校验签名；如果是明文镜像，直接校验签名。
如果是明文镜像而且需要被加密回烧，则校验完成后会使用配置好的加密方式加密镜像回烧flash。
然后再解密DDR中的镜像（此时此镜像可能会被直接执行）。
\param[in] pPartionName Flash partion name CNcomment:pPartionName  flash 分区名
\param[out] ImgInDDRAddress After Authenticate finished ,image address in DDR CNcomment:ImgInDDRAddress 校验完成后，可用镜像处于DDR中的位置
\retval ::0 Success CNcomment:0                  成功
\retval ::-1 Faliure CNcomment:-1                失败
\see \n
None CNcomment:无
*/
HI_S32 HI_CA_FlashAuthenticateByName(HI_U8* pPartionName,HI_U32 *ImgInDDRAddress);

/**
\brief  Authenticate flash contents by flash address
CNcomment:根据flash地址校验flash内容
\attention \n
对于同时存在多种flash的STB,此接口只能操作boot所在的flash
\param[in] PartionAddr Flash partion address CNcomment:PartionAddr  flash 地址
\param[in] bisBootargsArea is for auth the bootargs area CNcomment:bisBootargsArea  校验bootargs 分区
\param[out] ImgInDDRAddress After Authenticate finished ,image address in DDR CNcomment:ImgInDDRAddress 校验完成后，可用镜像处于DDR中的位置
\retval ::0 Success CNcomment:0                  成功
\retval ::-1 Faliure CNcomment:-1                失败
\see \n
None CNcomment:无
*/
HI_S32 HI_CA_FlashAuthenticateByAddr(HI_U32 PartionAddr,HI_BOOL bisBootargsArea,HI_U32 *ImgInDDRAddress);

/**
\brief  Authenticate boot parrmeter
CNcomment:校验Boot参数区
\attention \n
此接口视具体需求而被调用，如果需要校验boot参数区，请首先调用此接口；对于不需要校验boot参数区的客户请不要调用此接口。
\param 无
\retval ::0 success CNcomment:0                  成功
\retval ::-1 Faliure CNcomment:-1                失败
\see \n
None CNcomment:无
*/
HI_S32 HI_CA_AuthenticateBootPara(HI_VOID);

/**
\brief  Authenticate boot backup parrmeter
CNcomment:校验Boot参数备份区
\attention \n
\param 无
\retval ::0 success CNcomment:0                  成功
\retval ::-1 Faliure CNcomment:-1                失败
\see \n
None CNcomment:无
*/
HI_S32 HI_CA_AuthenticateBootParaBak(HI_VOID);

/**
\brief  Calculate the AES CBC MAC
CNcomment:计算AES CBC MAC值
\attention \n
\param [in] pu8Key: Key for AES CBC MAC
\param [in] pInputData: input data to calculate the AES CBC MAC
\param [in] u32InputDataLen: input data length
\param [out] pOutputMAC: the output MAC
\param [in] bIsLastBlock: if the data is last block
\retval ::0 success CNcomment:0                  成功
\retval ::-1 Faliure CNcomment:-1                失败
\see \n
None CNcomment:无
*/
HI_S32 HI_CA_CalcMAC(HI_U8 *pu8Key, HI_U8 *pInputData, HI_U32 u32InputDataLen, HI_U8 *pOutputMAC, HI_BOOL bIsLastBlock);

/**
\brief  Authenticate by a given buffer and signature
CNcomment:根据指定的buffer地址和长度，以及对应的签名，校验此buffer数据的签名是否和指定签名一致。
\attention \n

\param 无
\retval ::0 success CNcomment:0                  成功
\retval ::-1 Faliure CNcomment:-1                失败
\see \n
None CNcomment:无
*/
HI_U32 HI_CA_ImgAuthenticate(HI_U32 StartAddr,HI_U32 length,HI_U8 u8Signature[RSA_2048_LEN]);

/*
    Get Auth Mode by partition name
*/
#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
HI_U32 HI_CA_GetAuthMode(HI_U8* pPartionName);

/*
    Authenticate non-boot images when enter recovery
*/
HI_S32 HI_Android_Auth_Recovery(HI_VOID);
#endif

/*
    Get header structure of image by partition name
*/
HI_S32 HI_CA_GetFlashImgInfoByName(HI_U8* pPartionName,HI_CAImgHead_S* pstImgInfo, HI_BOOL *pIsEncrypt);

/*
    Get header structure of image by partition address
*/
HI_S32 HI_CA_GetFlashImgInfoByAddr(HI_U32 PartionAddr,HI_CAImgHead_S* pstImgInfo, HI_BOOL *pIsEncrypt);

/*
    Encrypt image from DDR address, and burn the encrypted image to the given partition address
*/
HI_S32 HI_CA_EncryptDDRImageAndBurnFlashAddr(HI_U8* pImageDDRAddress, HI_U32 PartionAddr);

/*
    Encrypt image from DDR address, and burn the encrypted image to the given partition name
*/
HI_S32 HI_CA_EncryptDDRImageAndBurnFlashName(HI_U8* pImageDDRAddress, HI_CHAR* pPartionName);

/*
    Encrypt image from DDR address and length, and burn the encrypted image to the given partition name
*/
HI_S32 HI_CA_EncryptDDRImageAndBurnFlashNameByLen(HI_U8* pImageDDRAddress, HI_U32 u32Len,HI_CHAR* pPartionName);

/*
    Decrypt flash image by a given partition name to a fixed DDR address
*/
HI_S32 HI_CA_DecryptFlashImage2DDR(HI_CHAR* pPartionName);

/*

*/
HI_S32 HI_CA_AuthenticateEntry(HI_VOID);


/*
    Verify partition signature by partitionname, signature partitionname and its offset
*/
HI_S32 HI_CA_CommonVerify_Signature(HI_U8 *PartitionImagenName, HI_U8 *PartitionSignName, HI_U32 offset);

/*
    Verify partition signature by partitionname, signature partitionname and its offset
*/
HI_S32 HI_CA_CommonVerify_Section_Signature(HI_U8 *PartitionImagenName, HI_U8 *PartitionSignName, HI_U32 offset);


/*
    Verify partition, and encrypt it if needed.
*/
HI_S32 HI_CA_CommonVerify_EncryptImage(HI_U8 *PartitionImagenName, HI_U8 *PartitionSignName, HI_U32 offset);

/*
    Verify bootargs signature.
*/
HI_S32 HI_CA_CommonVerify_BootPara(HI_U32 u32ParaPartionAddr, HI_U32 u32ParaParitonSize);

#if !defined HI_ADVCA_TYPE_VERIMATRIX && !defined HI_MINIBOOT_SUPPORT
/*
    Copy external RSA pub key in boot image to the running global array.
*/
HI_S32 CA_GetExternRsaKey(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[]);
#endif

/*
    Authenticate non-boot images, such as recovory, kernel..., currently only used for Android
*/
HI_S32 HI_Android_Authenticate(HI_VOID);


#endif /*__CA_AUTHENTICATE_H__*/

