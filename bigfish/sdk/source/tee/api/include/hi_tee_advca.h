/******************************************************************************

  Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_tee_advca.h
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
 * \brief Describes the API about advca.
          CNcomment:�ṩ�߰�API CNend
 */
#ifndef __HI_TEE_ADVCA_H__
#define __HI_TEE_ADVCA_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      ADVCA */
/** @{ */  /** <!-- [ADVCA] */

/** DCAS KeyLadder use mode */
/**CNcomment:DCAS ģʽ */
typedef enum hiTEE_ADVCA_DCAS_KEYLADDER_LEV_E
{
    HI_TEE_ADVCA_DCAS_KEYLADDER_EK2         = 0,    /**<session EK2*/
    HI_TEE_ADVCA_DCAS_KEYLADDER_EK1         = 1,    /**<session EK1*/
    HI_TEE_ADVCA_DCAS_KEYLADDER_VENDORSYSID = 8,    /**<session Vendor_SysID*/
    HI_TEE_ADVCA_DCAS_KEYLADDER_NONCE       = 9,    /**<session nonce*/
    HI_TEE_ADVCA_DCAS_KEYLADDER_BUTT
}HI_TEE_ADVCA_DCAS_KEYLADDER_LEV_E;


/**Defines the attribute ID of the OTP fuse. Please be kindly noted that the OTP fuse is set permanently.
After setting the OTP fuse, please power off and then power on the STB to make the OTP fuse function effective */
/**CNcomment: ����OTPλIDö������. ��ע��OTPλ���ú󲻿ɸı�.
���ú���ϵ�����ʹOTPλ������Ч.*/
typedef enum hiTEE_ADVCA_OTP_FUSE_E
{
    HI_TEE_ADVCA_OTP_NULL = 0,
    HI_TEE_ADVCA_OTP_R2R_KL_LEVEL_SEL,      /**<R2R keyladder stage, HI_TEE_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*/
    HI_TEE_ADVCA_OTP_CHIP_ID,               /**<Chip ID, HI_TEE_ADVCA_CHIPID_ATTR_S*/
    HI_TEE_ADVCA_OTP_TZ_AREA_DATA,          /**<Trust zone area data*/
    HI_TEE_ADVCA_OTP_ANTIROLLBACK_VERSION,  /**<the version of ANTIROLLBACK, HI_TEE_ADVCA_ANTIROLLBACK_VERSION_S*/
    HI_TEE_ADVCA_OTP_TZ_AREA_LOCK_FLAG,     /**< Get the lock flag of OTP trust area, when otp_tz_area_enable is set, these lock flags can only be accessed by secure cpu , HI_TEE_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_TEE_ADVCA_OTP_FUSE_BUTT
}HI_TEE_ADVCA_OTP_FUSE_E;

/**Defines the attribute of the keyladder type ID.*/
/**CNcomment: ����keyladder����ID.*/
typedef enum hiTEE_ADVCA_KEYLADDER_TYPE_E
{
    HI_TEE_ADVCA_KEYLADDER_R2R,             /**<R2R keyladder*/
    HI_TEE_ADVCA_KEYLADDER_SP,              /**<SP keyladder*/
    HI_TEE_ADVCA_KEYLADDER_MISC,            /**<MISC keyladder*/
    HI_TEE_ADVCA_KEYLADDER_GDRM,            /**<Google DRM key ladder*/
    HI_TEE_ADVCA_KEYLADDER_STB_TA,          /**<STB TA key ladder*/
    HI_TEE_ADVCA_KEYLADDER_CA_TA,           /**<Ca TA key ladder*/
    HI_TEE_ADVCA_KEYLADDER_SEC_STORE,       /**<SEC STORE key ladder*/
    HI_TEE_ADVCA_KEYLADDER_TYPE_BUTT
}HI_TEE_ADVCA_KEYLADDER_TYPE_E;


/**Defines the attribute of the CA vendor type ID.*/
/**CNcomment: ����CA vendor��������ID.*/
typedef enum hiTEE_ADVCA_VENDORID_E
{
    HI_TEE_ADVCA_NULL       = 0x00,     /**<No-Advcance CA chipset, Marked with 0*/
    HI_TEE_ADVCA_NAGRA      = 0x01,     /**<NAGRA  Chipse, Marked with R*/
    HI_TEE_ADVCA_IRDETO     = 0x02,     /**<IRDETO Chipset, Marked with I*/
    HI_TEE_ADVCA_CONAX      = 0x03,     /**<CONAX Chipset, Marked with C*/
    HI_TEE_ADVCA_SUMA       = 0x05,     /**<SUMA Chipset, Marked with S*/
    HI_TEE_ADVCA_NOVEL      = 0x06,     /**<NOVEL Chipset, Marked with Y*/
    HI_TEE_ADVCA_VERIMATRIX = 0x07,     /**<VERIMATRIX Chipset, Marked with M*/
    HI_TEE_ADVCA_CTI        = 0x08,     /**<CTI Chipset, Marked with T*/
    HI_TEE_ADVCA_COMMONCA   = 0x0b,     /**<COMMONCA Chipset, Marked with H*/
    HI_TEE_ADVCA_DCAS       = 0x0c,     /**<DCAS CA Chipset*/
    HI_TEE_ADVCA_PANACCESS  = 0x0e,     /**<PANACCESS CA Chipset*/
    HI_TEE_ADVCA_VENDORIDE_BUTT
}HI_TEE_ADVCA_VENDORID_E;

/**Defines the operation of the CA vendor.*/
/**CNcomment: ����CA vendor�����������ID.*/
typedef enum hiTEE_ADVCA_CA_VENDOR_OPT_E
{
    HI_TEE_ADVCA_CA_VENDOR_OPT_VMX_SET_KWMCWC,
    HI_TEE_ADVCA_CA_VENDOR_OPT_BUTT
}HI_TEE_ADVCA_CA_VENDOR_OPT_E;

/**Defines the struct of VMX KWMCWC.*/
/**CNcomment: ����VMX ˮӡ�����ֽṹ��.*/
typedef struct hiTEE_ADVCA_VMX_KWMCWC_S
{
    HI_TEE_ADVCA_KEYLADDER_TYPE_E enKeyladderType;
    HI_U8 u8KWMCWC[16];
}HI_TEE_ADVCA_VMX_KWMCWC_S;

/**Defines the attribute of the CA vendor private function.*/
/**CNcomment: ����CA����˽�й������Խṹ��.*/
typedef struct hiADVCA_CA_VENDOR_OPT_S
{
    HI_TEE_ADVCA_CA_VENDOR_OPT_E enCaVendorOpt;
    union
    {
        HI_TEE_ADVCA_VMX_KWMCWC_S       stKWMCWC;
    }unCaVendorOpt;
}HI_TEE_ADVCA_CA_VENDOR_OPT_S;

/**Defines the attribute of the R2R keyladder type ID.*/
/**CNcomment: ����R2R keyladder��������ID.*/
typedef enum hiTEE_ADVCA_KEYLADDER_R2R_ATTR_E
{
    HI_TEE_ADVCA_KEYLADDER_R2R_ATTR_ALG = 0,            /**<Keyladder algorithm, TDES/AES*/
    HI_TEE_ADVCA_KEYLADDER_R2R_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_TEE_ADVCA_KEYLADDER_R2R_ATTR_BUTT
}HI_TEE_ADVCA_KEYLADDER_R2R_ATTR_E;

/**Defines the advanced CA Encrypt algorithm.*/
/**CNcomment: ����߰������㷨.*/
typedef enum hiTEE_ADVCA_ALG_TYPE_E
{
    HI_TEE_ADVCA_ALG_TYPE_TDES      = 0,    /**<Encrypt algorithm : 3DES*/
    HI_TEE_ADVCA_ALG_TYPE_AES,              /**<Encrypt algorithm : AES*/
    HI_TEE_ADVCA_ALG_TYPE_BUTT
}HI_TEE_ADVCA_ALG_TYPE_E;

/**Defines the session serect key class.*/
/**CNcomment: ����Ự��Կ����.*/
typedef enum hiTEE_ADVCA_KEYLADDER_LEV_E
{
    HI_TEE_ADVCA_KEYLADDER_LEV1     = 0,    /**<session serect key level 1*/
    HI_TEE_ADVCA_KEYLADDER_LEV2,            /**<session serect key level 2*/
    HI_TEE_ADVCA_KEYLADDER_LEV3,            /**<session serect key level 3*/
    HI_TEE_ADVCA_KEYLADDER_LEV4,            /**<session serect key level 4*/
    HI_TEE_ADVCA_KEYLADDER_LEV5,            /**<session serect key level 5*/
    HI_TEE_ADVCA_KEYLADDER_LEV6,            /**<session serect key level 6*/
    HI_TEE_ADVCA_KEYLADDER_BUTT
}HI_TEE_ADVCA_KEYLADDER_LEV_E;

/**Defines the attribute of the R2R keyladder.*/
/**CNcomment: ����R2R keyladder���Խṹ��.*/
typedef struct hiTEE_ADVCA_KEYLADDER_R2R_ATTR_S
{
    HI_TEE_ADVCA_KEYLADDER_R2R_ATTR_E  enR2RKlAttr; /**<R2R keyladder attribute  ID*/
    HI_TEE_ADVCA_ALG_TYPE_E enAlgType;              /**<Keyladder algorithm, TDES/AES*/
    HI_TEE_ADVCA_KEYLADDER_LEV_E enStage;           /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                         /**<Session key*/
}HI_TEE_ADVCA_KEYLADDER_R2R_ATTR_S;

/**Defines the attribute of the SP keyladder type ID.*/
/**CNcomment: ����SP keyladder��������ID.*/
typedef enum hiTEE_ADVCA_KEYLADDER_SP_ATTR_E
{
    HI_TEE_ADVCA_KEYLADDER_SP_ATTR_ENABLE = 0,  /**<Use SPE keyladder or not for specal CA system */
    HI_TEE_ADVCA_KEYLADDER_SP_ATTR_ALG,         /**<Keyladder algorithm, TDES/AES*/
    HI_TEE_ADVCA_KEYLADDER_SP_ATTR_DSC_MODE,    /**<Descrambling mode*/
    HI_TEE_ADVCA_KEYLADDER_SP_ATTR_SESSION_KEY, /**<Keyladder session key*/
    HI_TEE_ADVCA_KEYLADDER_SP_ATTR_BUTT
}HI_TEE_ADVCA_KEYLADDER_SP_ATTR_E;


/**Defines the mode of demux descrambling.*/
/**CNcomment: �������������ģʽ.*/
typedef enum hiTEE_ADVCA_SP_DSC_MODE_E
{
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_CSA2              = 0x0000,   /**<Demux PAYLOAD CSA2 */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_CSA3              = 0x0010,   /**<Demux PAYLOAD CSA3 */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_IDSA      = 0x0020,   /**<Demux PAYLOAD AES  IPTV Mode */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_AES_ECB           = 0x0021,   /**<Demux PAYLOAD AES  ECB Mode */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_CI        = 0x0022,   /**<Demux PAYLOAD AES  CIPLUS */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_DES_IPTV          = 0x0030,   /**<Demux PAYLOAD DES  CIPLUS */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_DES_CIPLUS        = 0x0032,   /**<Demux PAYLOAD DES  CIPLUS */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_DES_CBC           = 0x0033,   /**<Demux PAYLOAD DES  CBC */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_AES_NOVEL         = 0x0040,   /**<Demux PAYLOAD AES  NOVEL */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_SMS4_NOVEL        = 0x0041,   /**<Demux PAYLOAD SMS4 NOVEL */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_SMS4_IPTV         = 0x0050,   /**<Demux PAYLOAD SMS4 IPTV */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_SMS4_ECB          = 0x0051,   /**<Demux PAYLOAD SMS4 ECB */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_SMS4_CBC          = 0x0053,   /**<Demux PAYLOAD SMS4 CBC */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC           = 0x0063,   /**<Demux PAYLOAD AES  CBC */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_TDES_IPTV         = 0x0070,   /**<Demux PAYLOAD TDES IPTV */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_TDES_ECB          = 0x0071,   /**<Demux PAYLOAD TDES ECB */
     HI_TEE_ADVCA_SP_DSC_MODE_PAYLOAD_TDES_CBC          = 0x0073,   /**<Demux PAYLOAD TDES CBC */
     HI_TEE_ADVCA_SP_DSC_MODE_RAW_AES_CBC               = 0x4020,   /**<MultiCipher AES CBC */
     HI_TEE_ADVCA_SP_DSC_MODE_RAW_AES_ECB               = 0x4021,   /**<MultiCipher AES ECB */
     HI_TEE_ADVCA_SP_DSC_MODE_RAW_AES_CBC_PIFF          = 0x4022,   /**<MultiCipher AES CBC PIFF */
     HI_TEE_ADVCA_SP_DSC_MODE_RAW_AES_CBC_APPLE         = 0x4023,   /**<MultiCipher AES CBC APPLE */
     HI_TEE_ADVCA_SP_DSC_MODE_RAW_AES_CTR               = 0x4024,   /**<MultiCipher AES CTR */
     HI_TEE_ADVCA_SP_DSC_MODE_RAW_TDES_CBC              = 0x4040,   /**<MultiCipher AES CBC */
     HI_TEE_ADVCA_SP_DSC_MODE_RAW_TDES_ECB              = 0x4041,   /**<MultiCipher AES ECB */
     HI_TEE_ADVCA_SP_DSC_MODE_BUTT
}HI_TEE_ADVCA_SP_DSC_MODE_E;


/**Defines the attribute of the SP keyladder.*/
/**CNcomment: ����SP keyladder���Խṹ��.*/
typedef struct hiTEE_ADVCA_KEYLADDER_SP_ATTR_S
{
    HI_TEE_ADVCA_KEYLADDER_SP_ATTR_E  enSPKlAttr;   /**<SP keyladder attribute ID*/
    HI_BOOL bEnable;                                /**<Use SP keyladder or not. Before using the SP keyladder*/
    HI_TEE_ADVCA_ALG_TYPE_E enAlgType;              /**<Keyladder algorithm, TDES/AES*/
    HI_TEE_ADVCA_SP_DSC_MODE_E enDscMode;           /**<Descramblig mode*/
    HI_TEE_ADVCA_KEYLADDER_LEV_E enStage;           /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                         /**<Session key*/
}HI_TEE_ADVCA_KEYLADDER_SP_ATTR_S;


/**Defines the attribute of the MISC keyladder type ID.*/
/**CNcomment: ����MISC keyladder��������ID.*/
typedef enum hiTEE_ADVCA_KEYLADDER_MISC_ATTR_E
{
    HI_TEE_ADVCA_KEYLADDER_MISC_ATTR_ENABLE = 0,    /**<Use MISC keyladder or not. Before using the MISC keyladder, should set this attribute to HI_TRUE,
                                                        and after using, should set it to HI_FALSE.*/
    HI_TEE_ADVCA_KEYLADDER_MISC_ATTR_ALG,           /**<Keyladder algorithm, TDES/AES*/
    HI_TEE_ADVCA_KEYLADDER_MISC_ATTR_DSC_MODE,      /**<Descrambling mode*/
    HI_TEE_ADVCA_KEYLADDER_MISC_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_TEE_ADVCA_KEYLADDER_MISC_ATTR_BUTT
}HI_TEE_ADVCA_KEYLADDER_MISC_ATTR_E;

/**Defines the attribute of the MISC keyladder.*/
/**CNcomment: ����MISC keyladder���Խṹ��.*/
typedef struct hiTEE_ADVCA_KEYLADDER_MISC_ATTR_S
{
    HI_TEE_ADVCA_KEYLADDER_MISC_ATTR_E  enMiscKlAttr;   /**<MISC keyladder attribute ID*/
    HI_BOOL bEnable;                                    /**<Use MISC keyladder or not. Before using the MISC keyladder, should be set to HI_TRUE,
                                                            and after using, should be set to HI_FALSE.*/
    HI_TEE_ADVCA_ALG_TYPE_E enAlgType;      /**<Keyladder algorithm, TDES/AES*/
    HI_TEE_ADVCA_SP_DSC_MODE_E enDscMode;   /**<Descramblig mode*/
    HI_TEE_ADVCA_KEYLADDER_LEV_E enStage;   /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                 /**<Session key*/
}HI_TEE_ADVCA_KEYLADDER_MISC_ATTR_S;


/**Defines the attribute of the Google DRM keyladder type ID.*/
/**CNcomment: ����Google DRM keyladder��������ID.*/
typedef enum hiTEE_ADVCA_KEYLADDER_GDRM_ATTR_E
{
    HI_TEE_ADVCA_KEYLADDER_GDRM_ATTR_ENABLE = 0,    /**<Use GDRM keyladder or not. Before using the GDRM keyladder, should set this attribute to HI_TRUE, and after using, should set it to HI_FALSE.*/
    HI_TEE_ADVCA_KEYLADDER_GDRM_ATTR_ENCRYPT,       /**<Encrypt clear device key*/
    HI_TEE_ADVCA_KEYLADDER_GDRM_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_TEE_ADVCA_KEYLADDER_GDRM_ATTR_GETFLAG,       /**<Get flag*/
    HI_TEE_ADVCA_KEYLADDER_GDRM_ATTR_BUTT
}HI_TEE_ADVCA_KEYLADDER_GDRM_ATTR_E;

/**Defines the attribute of Google DRM keyladder.*/
/**CNcomment: ����Google DRM keyladder���Խṹ��.*/
typedef struct hiTEE_ADVCA_KEYLADDER_GDRM_ATTR_S
{
    HI_TEE_ADVCA_KEYLADDER_GDRM_ATTR_E  enGDRMKlAttr;
    HI_BOOL bEnable;                        /**<Use GDRM keyladder or not. Before using the GDRM keyladder, should be set to HI_TRUE, and after using, should set it to HI_FALSE.*/
    HI_TEE_ADVCA_KEYLADDER_LEV_E enStage;   /**<Keyladder stage of the session key to be set*/
    HI_HANDLE hCipherHandle;                /**<cipher handle, if enStage is HI_UNF_ADVCA_KEYLADDER_LEV3, hCipherHandle should be set*/
    HI_U8 au8SessionKey[32];                /**<if select HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENCRYPT it is clear device key, if select HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_SESSION_KEY, it is session key*/
    HI_U8 au8Output[16];                    /**<if HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENCRYPT is set, it is encrypted device key, if HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_GETFLAG is set, it is flag*/
}HI_TEE_ADVCA_KEYLADDER_GDRM_ATTR_S;


/**Defines the attribute of all of the keyladder.*/
/**CNcomment: �������� keyladder���Խṹ��.*/
typedef struct hiTEE_ADVCA_KEYLADDER_ATTR_S
{
    union
    {
        HI_TEE_ADVCA_KEYLADDER_R2R_ATTR_S       stR2RKlAttr;    /**<R2R keyladder attribute*/
        HI_TEE_ADVCA_KEYLADDER_SP_ATTR_S        stSPKlAttr;     /**<SP keyladder attribute*/
        HI_TEE_ADVCA_KEYLADDER_MISC_ATTR_S      stMiscKlAttr;   /**<MISC keyladder attribute*/
        HI_TEE_ADVCA_KEYLADDER_GDRM_ATTR_S      stGDRMAttr;     /**<Google DRM keyladder attribute*/
    }unKlAttr;
}HI_TEE_ADVCA_KEYLADDER_ATTR_S;

/**Defines the attribute of CA key target.*/
/**CNcomment: ����߰�keyʹ��Ŀ�Ľṹ��.*/
typedef enum hiTEE_ADVCA_CA_TARGET_E
{
    HI_TEE_ADVCA_CA_TARGET_DEMUX = 0,       /**<demux*/
    HI_TEE_ADVCA_CA_TARGET_MULTICIPHER,     /**<multicipher*/
    HI_TEE_ADVCA_CA_TARGET_BUTT
}HI_TEE_ADVCA_CA_TARGET_E;

/**Defines the default attribute of OTP fuse. If one OTP fuse can ONLY be "Enable" or "Disable",
then we will use this attribute.*/
/**CNcomment: ����OTPλĬ�����Խṹ��. ������һ��OTPλ�Ĺ���
ֻ�ǿ�����رյ����*/
typedef struct hiTEE_ADVCA_OTP_DEFAULT_ATTR_S
{
    HI_BOOL bEnable;    /**<Is the feature enable or not*/
}HI_TEE_ADVCA_OTP_DEFAULT_ATTR_S;

/**Defines the attribute of the keyladder level.*/
/**CNcomment: ����keyladder�������Խṹ��.*/
typedef struct hiTEE_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S
{
    HI_TEE_ADVCA_KEYLADDER_LEV_E enKeyladderLevel;   /**<Keyladder level*/
}HI_TEE_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S;

/**Defines the attribute of the version number.*/
/**CNcomment: ������ع��汾�����Խṹ��.*/
typedef struct hiTEE_ADVCA_VERSION_NUMBER_S
{
    HI_U32 u32OTPAddr;
    HI_U32 u32OTPLength;
    HI_U32 u32VersionNumber;
}HI_TEE_ADVCA_ANTIROLLBACK_VERSION_S;

/**Defines the attribute of the OTP fuse.*/
/**CNcomment: ����OTP fuse���Խṹ��.*/
typedef struct hiTEE_ADVCA_OTP_ATTR_S
{
    union
    {
        HI_TEE_ADVCA_OTP_DEFAULT_ATTR_S          stDefaultAttr;         /**<Default attribute, if one fuse can ONLY be "Enable" or "Disable", then we can use this attribute*/
        HI_TEE_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S  stKeyladderLevSel;     /**<Keyladder level attribute*/
        HI_TEE_ADVCA_ANTIROLLBACK_VERSION_S      stVersionNumber;       /**<for ree and tee version number*/
    }unOtpFuseAttr;
}HI_TEE_ADVCA_OTP_ATTR_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      advca */
/** @{ */  /** <!-- [advca] */


/**
\brief Initializes the advanced CA module CNcomment:��ʼ��advance CAģ�� CNend
\attention \n
Call this application programming interface (API) before using the advanced CA module.
The code HI_SUCCESS is returned if this API is called repeatedly.
CNcomment:�ڽ���advance CA��ز���ǰӦ�����ȵ��ñ��ӿ�\n
�ظ����ñ��ӿڣ��᷵�سɹ� CNend
\param N/A CNcomment:�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_OPEN_ERR The CA device fails to start CNcomment:HI_ERR_CA_OPEN_ERR ��CA�豸ʧ�� CNend
\see \n
::HI_TEE_ADVCA_DeInit
*/
HI_S32 HI_TEE_ADVCA_Init(HI_VOID);

/**
\brief Deinitializes the advanced CA module CNcomment:ȥ��ʼ��advance CAģ�� CNend
\attention \n
None CNcomment:�� CNend
\param N/A CNcomment:�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_DeInit(HI_VOID);

/**
  \brief This function is used to get the OTP fuse. CNcomment:���ڻ�ȡOTPλ CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enOtpFuse: the OTP fuse ID CNcomment:enOtpFuse ����ȡ��OTPλID CNend
  \param[in]  pstOtpFuseAttr: the OTP fuse attribute CNcomment:pstOtpFuseAttr ��ȡ��OTPλ���� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_GetOtpFuse(HI_TEE_ADVCA_OTP_FUSE_E enOtpFuse, HI_TEE_ADVCA_OTP_ATTR_S *pstOtpFuseAttr);

/**
  \brief This function is used to set the OTP fuse. CNcomment:��������OTPλ CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enOtpFuse: the OTP fuse ID CNcomment:enOtpFuse �����õ�OTPλID CNend
  \param[in]  pstOtpFuseAttr: the OTP fuse attribute CNcomment:pstOtpFuseAttr �����õ�OTPλ���� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_SetOtpFuse(HI_TEE_ADVCA_OTP_FUSE_E enOtpFuse, HI_TEE_ADVCA_OTP_ATTR_S *pstOtpFuseAttr);

/**
  \brief This function is used to set the keyladder attribute. CNcomment:��������keyladder���� CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enKeyLadderType: The keyladder type ID CNcomment:enKeyLadderType Keyladder����ID CNend
  \param[in]  pstKeyladderAttr: The keyladder attribute CNcomment:pstKeyladderAttr �����õ�keyladder����CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_SetKeyLadderAttr(HI_TEE_ADVCA_KEYLADDER_TYPE_E enKeyLadderType, HI_TEE_ADVCA_KEYLADDER_ATTR_S *pstKeyladderAttr);

/**
  \brief This function is used to close the DCAS keyladder CNcomment:���ڹر�DCAS CNend
  \attention \n
  None  CNcomment:�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_DCASClose(HI_VOID);

/**
  \brief This function is used to open the DCAS CNcomment:���ڴ�DCAS CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enAlg: DCAS keyladder algorithm CNcomment:enAlg DCAS keyladder�㷨 CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_DCASOpen(HI_TEE_ADVCA_ALG_TYPE_E enAlg);

/**
  \brief This function is used to get the DCAS CHIPID CNcomment:���ڻ�ȡDCAS CHIPID
  \attention \n
  None  CNcomment:�� CNend
  \param[out]  pu32MSBID: First 4 bytes of DCAS CHIPID CNcomment:DCAS CHIPIDǰ4���ֽ� CNend
  \param[out]  pu32LSBID: last 4 bytes of DCAS CHIPID CNcomment:DCAS CHIPID��4���ֽ� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/

HI_S32 HI_TEE_ADVCA_GetDCASChipId(HI_U32 *pu32MSBID, HI_U32 *pu32LSBID);

/**
  \brief This function is used to set the session key CNcomment:��������DCAS session��Կ CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enDCASLevel: the DCAS keyladder level CNcomment:enAlg DCAS keyladder���� CNend
  \param[in]  pu8Key: the DCAS keyladder session key CNcomment:enAlg DCAS keyladder��Կ CNend
  \param[in]  pu8Output: the output of the DCAS keyladder CNcomment:pu8Output DCAS keyladder��� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_SetDCASSessionKey(HI_TEE_ADVCA_DCAS_KEYLADDER_LEV_E enDCASLevel, HI_U8 au8Key[16], HI_U8 au8Output[16]);

/**
\brief  Calculte the AES_CMAC value of data
CNcomment: �������ݵ�AES_CMAC ֵ CNend
\attention \n
None CNcomment:�� CNend

\param[in]  buffer  pointer of data buffer .        CNcomment:����buffer ָ�� CNend
\param[in]  Length  The length  of data .   CNcomment:���ݳ��� CNend
\param[in]  Key   The key used in Calculte the AES_CMAC of data           CNcomment: AES_CMAC ������ʹ�õ�key  CNend
\param[out]  MAC   The AES_CMAC value          CNcomment:AES_CMAC ֵ CNend

\retval ::HI_SUCCESS  Success                 CNcomment:�ɹ� CNend
\retval ::HI_FAILURE    Failure                     CNcomment:ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_CalculteAES_CMAC(HI_U8 *buffer, HI_U32 Length, HI_U8 Key[16], HI_U8 MAC[16]);

/**
  \brief This function is used to achieve the CA vendor privated function. CNcomment:�������CA�������еĲ��� CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enCaVendor: The CA vendor type ID CNcomment:enCaVendor CA vendor����ID CNend
  \param[in]  pstCavendorOpt: The parameter to achieve the CA vendor private function CNcomment:pstCavendorOpt ���CA�������й�����Ҫ�Ĳ���CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_CaVendorOperation(HI_TEE_ADVCA_VENDORID_E enCaVendor, HI_TEE_ADVCA_CA_VENDOR_OPT_S *pstCaVendorOpt);

/**
  \brief This function is used to set open Misc keyladder. CNcomment:���ڴ�Misc keyladder CNend
  \attention \n
  None  CNcomment:�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_VMXMiscOpen();

/**
  \brief This function is used to close Misc keyladder. CNcomment:���ڹر�Misc keyladder CNend
  \attention \n
  None  CNcomment:�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_VMXMiscClose();

/**
  \brief This function is used to set Misc keyladder session key. CNcomment:���� CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enStage: The keyladder level CNcomment:keyladder ���� CNend
  \param[in]  pu8Key: The parameter to achieve session key CNcomment:pu8Key �Ự��Կ CNend
  \param[in]  u32KeyLen: The length of the session key CNcomment:�Ự��Կ���� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_SetVMXMiscSessionKey(HI_TEE_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key, HI_U32 u32KeyLen);

/**
  \brief This function is used to set Misc keyladder algorithms. CNcomment:��������Misc keyladder �㷨 CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enType: The keyladder level CNcomment:Misc keyladder �㷨 CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_SetVMXMiscAlg(HI_TEE_ADVCA_ALG_TYPE_E enType);

/**
  \brief This function is used to set Misc keyladder descrambler mode. CNcomment:��������Misc keyladder ����ģʽ CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enDscMode: The keyladder level CNcomment:Misc keyladder ����ģʽ CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_SetVMXMiscDscMode(HI_TEE_ADVCA_SP_DSC_MODE_E enDscMode);

/**
  \brief This function is used to get Misc keyladder level. CNcomment:���ڻ�ȡMisc keyladder ���� CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[out]  penLevel: The point to get Misc keyladder level CNcomment:��ȡMisc keyladder ���� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_GetVMXMiscKlLevel(HI_TEE_ADVCA_KEYLADDER_LEV_E *penLevel);
/**
  \brief This function is used to set open SP keyladder. CNcomment:���ڴ�SP keyladder CNend
  \attention \n
  None  CNcomment:�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_VMXSPOpen();

/**
  \brief This function is used to close SP keyladder. CNcomment:���ڹر�SP keyladder CNend
  \attention \n
  None  CNcomment:�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_VMXSPClose();



/**
  \brief This function is used to set SP keyladder session key. CNcomment:���� CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enStage: The keyladder level CNcomment:keyladder ���� CNend
  \param[in]  pu8Key: The parameter to achieve session key CNcomment:pu8Key �Ự��Կ CNend
  \param[in]  u32KeyLen: The length of the session key CNcomment:�Ự��Կ���� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_SetVMXSPSessionKey(HI_TEE_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key, HI_U32 u32KeyLen);

/**
  \brief This function is used to set SP keyladder algorithms. CNcomment:��������SP keyladder �㷨 CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enType: The keyladder level CNcomment:SP keyladder �㷨 CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_SetVMXSPAlg(HI_TEE_ADVCA_ALG_TYPE_E enType);

/**
  \brief This function is used to set SP keyladder descrambler mode. CNcomment:��������SP keyladder ����ģʽ CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enDscMode: The keyladder level CNcomment:SP keyladder ����ģʽ CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_SetVMXSPDscMode(HI_TEE_ADVCA_SP_DSC_MODE_E enDscMode);

/**
  \brief This function is used to get SP keyladder level. CNcomment:���ڻ�ȡSP keyladder ���� CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[out]  penLevel: The point to get SP keyladder level CNcomment:��ȡSP keyladder ���� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_TEE_ADVCA_GetVMXSPKlLevel(HI_TEE_ADVCA_KEYLADDER_LEV_E *penLevel);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif /* __HI_TEE_ADVCA_H__ */
