/******************************************************************************

  Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_tee_otp.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2013-12-28
  Description   :
  History       :
  1.Date        : 2016/06/23
    Author      : z00277608
    Modification: format file

*******************************************************************************/
/**
 * \file
 * \brief Describes the API about the otp.
          CNcomment:�ṩotp API CNend
 */

#ifndef __HI_TEE_OTP_H__
#define __HI_TEE_OTP_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      OTP */
/** @{ */  /** <!-- [OTP] */

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      OTP */
/** @{ */  /** <!-- [OTP] */

/**
\brief Init an otp device.
\brief CNcomment:��ʼ��OTP�豸�� CNend
\attention \n
N/A
\param N/A                                          CNcomment:�ޡ� CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_Init(HI_VOID);

/**
\brief Deinit an otp device.
\brief CNcomment:ȥ��ʼ��OTP�豸�� CNend
\attention \n
N/A
\param N/A                                          CNcomment:�ޡ� CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_DeInit(HI_VOID);

/**
\brief reset the otp device.
\brief CNcomment:��λOTP�豸�� CNend
\attention \n
N/A
\param N/A                                          CNcomment:�ޡ� CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_Reset(HI_VOID);

/**
\brief Get the device chip ID.
\brief CNcomment:��ȡ�豸оƬ��ʶ�� CNend
\attention \n
N/A
\param[out] pKey:  Buffer to store the chip ID.     CNcomment:�洢��ȡоƬ��ʶ�Ļ�����ָ�롣 CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_GetChipID(HI_U8 *pu8ChipID);

/**
\brief Read otp value by word.
\brief CNcomment���ֶ�ȡOTP��ֵ�� CNend
\attention \n
N/A
\param[in] u32Addr:  OTP address.                           CNcomment:OTP ��ַ�� CNend
\param[out] pu32Value:  Buffer to store the otp by word.    CNcomment:�洢���ֻ�ȡOTPֵ�Ļ�����ָ�롣 CNend
\retval ::HI_SUCCESS  Call this API successful.             CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                  CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_ReadWord(HI_U32 u32Addr, HI_U32 *pu32Value);

/**
\brief Read otp value by byte.
\brief CNcomment���ֽڶ�ȡOTP��ֵ�� CNend
\attention \n
N/A
\param[in] u32Addr:  OTP address.                           CNcomment:OTP ��ַ�� CNend
\param[out] pu32Value:  Buffer to store the otp by word.    CNcomment:�洢���ֽڻ�ȡOTPֵ�Ļ�����ָ�롣 CNend
\retval ::HI_SUCCESS  Call this API successful.             CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                  CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_ReadByte(HI_U32 u32Addr, HI_U8 *pu8Value);

/**
\brief Write otp value by word.
\brief CNcomment����дOTP��ֵ�� CNend
\attention \n
N/A
\param[in] u32Addr:  OTP address.                       CNcomment:OTP ��ַ�� CNend
\param[] u32Value:   value to be write.                 CNcomment:��д��OTP��ֵ�� CNend
\retval ::HI_SUCCESS  Call this API successful.         CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.              CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_WriteWord(HI_U32 u32Addr, HI_U32 u32Value);

/**
\brief Write otp value by byte.
\brief CNcomment���ֽ�дOTP��ֵ�� CNend
\attention \n
N/A
\param[in] u32Addr:  OTP address.                       CNcomment:OTP ��ַ�� CNend
\param[] u32Value:   value to be write.                 CNcomment:��д��OTP��ֵ�� CNend
\retval ::HI_SUCCESS  Call this API successful.         CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.              CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_WriteByte(HI_U32 u32Addr, HI_U8 u8Value);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif

