/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_advca.h
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2014-09-16
Last Modified :
Description   :  
Function List :
History       :
******************************************************************************/
#include "ca_common.h"

/**Defines the attribute of the TA keyladder type ID.*/
/**CNcomment: 定义TA keyladder属性类型ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_TA_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_ENABLE = 0, /**<Use TA keyladder or not. Before using the TA keyladder, should set this attribute to HI_TRUE,
                                                                     and after using, should set it to HI_FALSE.*/
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_ALG,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_LOAD_TRANDATA,   /**<Transformation data protection and loading*/    
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_TA_ATTR_E;

/**Defines the attribute of the CSA3 keyladder type ID.*/
/**CNcomment: 定义CSA3 keyladder属性类型ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_CSA3_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_ALG = 0,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_E;

/**Defines the attribute of the CSA3 keyladder.*/
/**CNcomment: 定义CSA3 keyladder属性结构体.*/
typedef struct hiUNF_ADVCA_KEYLADDER_CSA3_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_E  enCsa3KlAttr; /**<CSA3 keyladder attribute ID*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;          /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;   /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                                    /**<Session key*/  
}HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_S;


/**Defines the attribute of the CSA2 keyladder type ID.*/
/**CNcomment: 定义CSA2 keyladder属性类型ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_CSA2_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_ALG = 0,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_E;

/**Defines the attribute of the R2R keyladder type ID.*/
/**CNcomment: 定义R2R keyladder属性类型ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_R2R_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_ALG = 0,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_E;

/**Defines the attribute of the SP keyladder type ID.*/
/**CNcomment: 定义SP keyladder属性类型ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_SP_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ENABLE = 0,       /**<Use SPE keyladder or not for specal CA system */
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ALG ,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_DSC_MODE,   /**<Descrambling mode*/        
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_SP_ATTR_E;

/**Defines the attribute of the MISC keyladder type ID.*/
/**CNcomment: 定义MISC keyladder属性类型ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_MISC_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ENABLE = 0, /**<Use MISC keyladder or not. Before using the MISC keyladder, should set this attribute to HI_TRUE,
                                                                     and after using, should set it to HI_FALSE.*/
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ALG,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_DSC_MODE,   /**<Descrambling mode*/ 
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_SESSION_KEY,   /**<Keyladder session key*/    
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_E;

/**Defines the attribute of the LP keyladder type ID.*/
/**CNcomment: 定义LP keyladder属性类型ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_LP_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_LP_ATTR_LOAD_LPK = 0,            /**<Load Link protection key*/
    HI_UNF_ADVCA_KEYLADDER_LP_ATTR_DECRYPT_PROTECTED_DATA,   /**<Decrypt Link protected data*/
    HI_UNF_ADVCA_KEYLADDER_LP_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_LP_ATTR_E;

/**Defines the attribute of the CSA2 keyladder.*/
/**CNcomment: 定义CSA2 keyladder属性结构体.*/
typedef struct hiUNF_ADVCA_KEYLADDER_CSA2_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_E  enCsa2KlAttr; /**<CSA2 keyladder attribute ID*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;          /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;   /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                                   /**<Session key*/  
}HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_S;


/**Defines the attribute of the R2R keyladder.*/
/**CNcomment: 定义R2R keyladder属性结构体.*/
typedef struct hiUNF_ADVCA_KEYLADDER_R2R_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_E  enR2RKlAttr; /**<R2R keyladder attribute  ID*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;          /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;   /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                                   /**<Session key*/
}HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_S;

/**Defines the attribute of the SP keyladder.*/
/**CNcomment: 定义SP keyladder属性结构体.*/
typedef struct hiUNF_ADVCA_KEYLADDER_SP_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_E  enSPKlAttr; /**<SP keyladder attribute ID*/
    HI_BOOL bEnable;    /**<Use SP keyladder or not. Before using the SP keyladder*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;               /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_SP_DSC_MODE_E enDscMode;    /**<Descramblig mode*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;         /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                                         /**<Session key*/
}HI_UNF_ADVCA_KEYLADDER_SP_ATTR_S;

/**Defines the attribute of the LP keyladder.*/
/**CNcomment: 定义LP keyladder属性结构体.*/
typedef struct hiUNF_ADVCA_KEYLADDER_LP_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_LP_ATTR_E  enLPKlAttr; /**<LP keyladder attribute ID*/
    HI_U8 u8Lpk[16];                                /**<Link protection key to be loaded*/
    HI_U8 *pu8ProtectedData;                /**<Input link protected data to be decrypted*/
    HI_U32 u32ProtectedDataLen;          /**<Input link protected data length*/   
    HI_U8 *pu8OutputProtectedData;   /**<Output link protected data after decryption*/
}HI_UNF_ADVCA_KEYLADDER_LP_ATTR_S;

/**Defines the attribute of the MISC keyladder.*/
/**CNcomment: 定义MISC keyladder属性结构体.*/
typedef struct hiUNF_ADVCA_KEYLADDER_MISC_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_E  enMiscKlAttr; /**<MISC keyladder attribute ID*/
    HI_BOOL bEnable;    /**<Use MISC keyladder or not. Before using the MISC keyladder, should be set to HI_TRUE,
                            and after using, should be set to HI_FALSE.*/   
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;               /**<Keyladder algorithm, TDES/AES*/  
    HI_UNF_ADVCA_SP_DSC_MODE_E enDscMode;    /**<Descramblig mode*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;         /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                                         /**<Session key*/
}HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_S;

/**Defines the attribute of the TA keyladder.*/
/**CNcomment: 定义TA keyladder属性结构体.*/
typedef struct hiUNF_ADVCA_KEYLADDER_TA_ATTR_S
{  
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_E  enTAKlAttr; /**<TA keyladder attribute ID*/
    HI_BOOL bEnable;    /**<Use TA keyladder or not. Before using the TA keyladder, should be set to HI_TRUE,
                            and after using, should be set to HI_FALSE.*/     
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;          /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;   /**<Keyladder stage of the session key to be set*/
    HI_U8 au8SessionKey[16];                                   /**<Session key*/
    HI_U8 *pu8TranData;                                         /**<Transformation data*/
    HI_U32 u32TranDataLen;                                  /**<Transformation data length*/
}HI_UNF_ADVCA_KEYLADDER_TA_ATTR_S;

/**Defines the attribute of all of the keyladder.*/
/**CNcomment: 定义所有 keyladder属性结构体.*/
typedef struct hiUNF_ADVCA_KEYLADDER_ATTR_S
{
    union
    {
        HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_S 	stCSA2KlAttr;   /**<CSA2 keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_S 	stCSA3KlAttr;   /**<CSA3 keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_S          stR2RKlAttr;     /**<R2R keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_SP_ATTR_S 	        stSPKlAttr;       /**<SP keyladder attribute*/   
        HI_UNF_ADVCA_KEYLADDER_LP_ATTR_S             stLpKlAttr;       /**<LP keyladder attribute*/  
        HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_S        stMiscKlAttr;    /**<MISC keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_TA_ATTR_S            stTAKlAttr;     /**<TA keyladder attribute, only for Irdeto MSR2.2*/
    }unKlAttr;
}HI_UNF_ADVCA_KEYLADDER_ATTR_S;

typedef enum hiUNF_ADVCA_KEYLADDER_TYPE_E
{
    HI_UNF_ADVCA_KEYLADDER_CSA2 = 0,    /**<CSA2 keyladder*/
    HI_UNF_ADVCA_KEYLADDER_CSA3,          /**<CSA3 keyladder*/
    HI_UNF_ADVCA_KEYLADDER_R2R,             /**<R2R keyladder*/
    HI_UNF_ADVCA_KEYLADDER_SP,              /**<SP keyladder*/
    HI_UNF_ADVCA_KEYLADDER_MISC,        /**<MISC keyladder*/
    HI_UNF_ADVCA_KEYLADDER_LP,              /**<LP keyladder*/
    HI_UNF_ADVCA_KEYLADDER_TA,            /**<TA keyladder, only for Irdeto MSR2.2*/ 
    HI_UNF_ADVCA_KEYLADDER_TYPE_BUTT
}HI_UNF_ADVCA_KEYLADDER_TYPE_E;

typedef struct
{
    HI_UNF_ADVCA_KEYLADDER_TYPE_E enKeyLadderType;
    HI_UNF_ADVCA_KEYLADDER_ATTR_S stKeyladderAttr;
}CA_KEYLADDER_ATTR_S;



HI_S32 HI_UNF_ADVCA_Init(HI_VOID);

HI_S32 HI_UNF_ADVCA_DeInit(HI_VOID);

HI_S32 HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);

HI_S32 HI_UNF_ADVCA_SetRSAKey(HI_U8 *pkey);

HI_S32 HI_UNF_ADVCA_GetRSAKey(HI_U8 *pkey);

HI_S32 HI_UNF_ADVCA_EnableSecBoot(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType);

HI_S32 HI_UNF_ADVCA_GetSecBootStat(HI_BOOL *pbEnable,HI_UNF_ADVCA_FLASH_TYPE_E *penFlashType);

HI_S32 HI_UNF_ADVCA_SetOtpFuse(HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse, HI_UNF_ADVCA_OTP_ATTR_S *pstOtpFuseAttr);

HI_S32 HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse, HI_UNF_ADVCA_OTP_ATTR_S *pstOtpFuseAttr);

HI_S32 HI_UNF_ADVCA_CaVendorOperation(HI_UNF_ADVCA_VENDORID_E enCaVendor, HI_UNF_ADVCA_CA_VENDOR_OPT_S *pstCaVendorOpt);

HI_S32 HI_UNF_ADVCA_GetVendorID(HI_U32 *pu32VendorID);

HI_S32 HI_UNF_ADVCA_GetChipId(HI_U32 *pu32ChipId);

HI_S32 HI_UNF_ADVCA_GetStbSn(HI_U8 au8StbSn[4]);

HI_S32 HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_TYPE_E enKeyLadderType, HI_UNF_ADVCA_KEYLADDER_ATTR_S *pstKeyladderAttr);






