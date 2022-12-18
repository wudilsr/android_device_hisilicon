/******************************************************************************

Copyright (C), 2012-2020, HiSilicon Technologies Co., Ltd.
******************************************************************************
File Name     : hi_svr_charset.h
Version       : Initial draft
Author        : HiSilicon DTV stack software group
Created Date   : 2012-08-01
Last Modified by: chenguangxian/00212295
Description   : Application programming interfaces (APIs) of charset
Function List :
Change History:
******************************************************************************/

#ifndef __HI_SVR_CHARSET_H__
#define __HI_SVR_CHARSET_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ******************************/
/** \addtogroup      CHARSET */
/** @{ */  /** <!—[CHARSET error code]*/

/** Error code in CHARSET */ /** CNcomment: CHARSET的错误码 */
#define HI_SVR_CHARSET_ERR_BASE              (0x0)
/** Pointer is null */ /** CNcomment:空指针 */
#define HI_SVR_CHARSET_ERR_NULL_PTR          (HI_SVR_CHARSET_ERR_BASE+1)
/** Not init */ /** CNcomment:未初始化 */
#define HI_SVR_CHARSET_ERR_NOT_INIT          (HI_SVR_CHARSET_ERR_BASE+2)
/** Invalid parameter */ /** CNcomment:无效参数 */
#define HI_SVR_CHARSET_ERR_INVALID_PARAM     (HI_SVR_CHARSET_ERR_BASE+3)
/** No memory */ /** CNcomment:内存不足 */
#define HI_SVR_CHARSET_ERR_NO_MEM            (HI_SVR_CHARSET_ERR_BASE+4)
/** Invalid code type */ /** CNcomment:无效的编码类型 */
#define HI_SVR_CHARSET_ERR_INVALID_CODETYPE  (HI_SVR_CHARSET_ERR_BASE+5)
/** Open fail */ /** CNcomment:打开失败 */
#define HI_SVR_CHARSET_ERR_OPEN_FAIL         (HI_SVR_CHARSET_ERR_BASE+6)


/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      CHARSET */
/** @{*/  /** <!—[CHARSET]*/

/** The charset code type *//** CNcomment:字符集编码类型 */
typedef enum hiSVR_CHARSET_CODETYPE_E
{
    HI_SVR_CHARSET_CODETYPE_NONE = 0,        /**<unkonwn type*//**<CNcomment:未识别类型*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_1,       /**<ISO8859-1 *//**<CNcomment:西欧语系 ，拉丁文1*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_2,       /**<ISO8859-2 *//**<CNcomment:中欧和东欧语系，拉丁文2*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_3,       /**<ISO8859-3 *//**<CNcomment:欧洲东南部语系，拉丁文3*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_4,       /**<ISO8859-4 *//**<CNcomment:斯堪的那维亚和波罗的海语系，拉丁文4*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_5,       /**<ISO8859-5 *//**<CNcomment:拉丁文和斯拉夫文*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_6,       /**<ISO8859-6 *//**<CNcomment:拉丁文和阿拉伯文*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_7,       /**<ISO8859-7 *//**<CNcomment:拉丁文和希腊文*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_8,       /**<ISO8859-8 *//**<CNcomment:拉丁文和希伯来文*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_9,       /**<ISO8859-9 *//**<CNcomment:为土耳其文修正的拉丁文，拉丁文5*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_10,      /**<ISO8859_10 *//**<CNcomment:拉普人、北欧和爱斯基摩人的文字，拉丁文6*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_11,      /**<ISO8859-11 *//**<CNcomment:拉丁文与泰文*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_13,      /**<ISO8859-13 *//**<CNcomment:波罗的海周边语系，拉丁文7*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_14,      /**<ISO8859-14 *//**<CNcomment:凯尔特文，拉丁文8*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_15,      /**<ISO8859-15 *//**<CNcomment:改进的拉丁文1，拉丁文9*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_16,      /**<ISO8859-16 *//**<CNcomment:罗马尼亚文，拉丁文10*/
    HI_SVR_CHARSET_CODETYPE_UNICODE_16LE,    /**<UNICODE_16LE *//**<CNcomment:16位小端的UNICODE*/
    HI_SVR_CHARSET_CODETYPE_UNICODE_16BE,    /**<UNICODE_16BE *//**<CNcomment:16位大端的UNICODE*/
    HI_SVR_CHARSET_CODETYPE_GB2312,          /**<GB2312 *//**<CNcomment:简体中文GB2312*/
    HI_SVR_CHARSET_CODETYPE_GB18030,          /**<GB2312 *//**<CNcomment:简体中文GB18030*/
    HI_SVR_CHARSET_CODETYPE_BIG5,            /**<BIG5 *//**<CNcomment:繁体中文*/
    HI_SVR_CHARSET_CODETYPE_UTF8,            /**<UTF8 *//**<CNcomment:UTF8*/
    HI_SVR_CHARSET_CODETYPE_CP1250,          /**<CP1250 *//**<CNcomment:中欧*/
    HI_SVR_CHARSET_CODETYPE_CP1251,          /**<CP1251 *//**<CNcomment:西里尔文*/
    HI_SVR_CHARSET_CODETYPE_CP1252,          /**<CP1252 *//**<CNcomment:拉丁文I*/
    HI_SVR_CHARSET_CODETYPE_CP1253,          /**<CP1253 *//**<CNcomment:希腊文*/
    HI_SVR_CHARSET_CODETYPE_CP1254,          /**<CP1254 *//**<CNcomment:土耳其文*/
    HI_SVR_CHARSET_CODETYPE_CP1255,          /**<CP1255 *//**<CNcomment:希伯来文*/
    HI_SVR_CHARSET_CODETYPE_CP1256,          /**<CP1256 *//**<CNcomment:阿拉伯文*/
    HI_SVR_CHARSET_CODETYPE_CP1257,          /**<CP1257 *//**<CNcomment:波罗的海文*/
    HI_SVR_CHARSET_CODETYPE_CP1258,          /**<CP1258 *//**<CNcomment:越南*/
    HI_SVR_CHARSET_CODETYPE_CP874,           /**<CP874 *//**<CNcomment:泰文*/
    HI_SVR_CHARSET_CODETYPE_UNICODE_32LE,    /**<UNICODE_32LE *//**<CNcomment:32位小端的UNICODE*/
    HI_SVR_CHARSET_CODETYPE_UNICODE_32BE,    /**<UNICODE_32BE *//**<CNcomment:32位大端的UNICODE*/
    HI_SVR_CHARSET_CODETYPE_ISO6937,         /**<ISO6937 *//**<CNcomment:拉丁字符集*/
    HI_SVR_CHARSET_CODETYPE_KSC5601,         /**<Korean Character Set KSC5601-1987,currently not support*//**<CNcomment:KSC5601韩文字符集，目前暂不支持*/
    HI_SVR_CHARSET_CODETYPE_BUTT,
} HI_SVR_CHARSET_CODETYPE_E;


/**
\brief user identify call back function. CNcomment: 用户字符识别回调处理函数。
\attention \n
none. it will be called when charset inner identify faile。CNcomment: 在chaset 内部识别失败的情况下，调用该接口。
it used to identify charset code type in non-standard string according to DVB SI。 CNcomment:用于识别DVB SI协议中非标准字符串的编码类型。
\param[in]  pu8InBuf      The input string buffer. CNcomment: 输入字符串。
\param[in]  s32InLen      The length of input string buffer. CNcomment:输入数据流的长度。
\param[in]  pvUserData   The user private data from HI_SVR_CHARSET_Init() function. CNcomment:用户在HI_SVR_CHARSET_Init 注册的私有数据pvUserData。
\param[out]  penCodeType   The charset code type of input string buffer. CNcomment: 输入字符串的字符编码类型。
\param[in]  au8LangCode     The language code of input string buffer, maybe null(e.g. Service Name in SDT).CNcomment:输入字符串对应的语言码类型,可能为空( 如SDT  表中的业务名称)。
\retval   ::HI_SUCCESS  success. CNcomment:成功。
\retval   ::HI_FAILURE  failure. CNcomment:失败。
\see \n
none
*/
typedef HI_S32 (*HI_SVR_CHARSET_IDENTIFY_CB_FN)(const HI_U8* pu8InBuf, HI_S32 s32InLen, HI_VOID* pvUserData, HI_SVR_CHARSET_CODETYPE_E* penCodeType, const HI_U8 au8LangCode[3]);




/**
\brief user charset convert call back function. CNcomment: 用户字符转码回调处理函数。
\attention \n
none. it will be called when charset inner convert faile。CNcomment: 在chaset 内部转码失败的情况下，调用该接口。
\param[in]  pu8InBuf      The input string buffer(not include the byte of Charset code type ). CNcomment:输入字符串(不包含字符编码类型字节)。
\param[in/out]  ps32InLenLeft The left length of input buffer. CNcomment:输入数据流的长度，输出未转码的数据流长度。
\param[out] pu8OutBuf   The output buffer. CNcomment:输出数据流。
\param[in/out] ps32OutLenLeft The left length of output buffer. CNcomment:输入存储输出数据流的空间长度，输出未使用的剩余空间长度。
\param[in]  penCodeType   The charset code type of input string buffer. CNcomment: 输入字符串的字符编码类型。
\retval   ::HI_SUCCESS  success. CNcomment:成功。
\retval   ::HI_FAILURE  failure. CNcomment:失败。
\see \n
none
*/
typedef HI_S32 (*HI_SVR_CHARSET_CONV_CB_FN)(const HI_U8* pu8InBuf, HI_S32* ps32InLenLeft, HI_U8* pu8OutBuf, HI_S32* ps32OutLenLeft, HI_SVR_CHARSET_CODETYPE_E enCodeType);



/** The attribute of charset *//** CNcomment:字符集转码模块的属性 */
typedef struct hiSVR_CHARSET_ATTR_S
{
    HI_SVR_CHARSET_CODETYPE_E     enToCodeType; /**<The target Charset code type, it will just do copy when enToCodeType is HI_SVR_CHARSET_CODETYPE_NONE*/ /**<CNcomment:目标编码类型，如果为HI_SVR_CHARSET_CODETYPE_NONE，直接拷贝透传*/
    HI_SVR_CHARSET_IDENTIFY_CB_FN pfnIdentify;  /**<The callback function to identify charset code type*//**<CNcomment:检测字符编码的回调函数*/
    HI_SVR_CHARSET_CONV_CB_FN     pfnConvert;   /**<The callback function to convert string*//**<CNcomment:字符转码回调函数*/
    HI_VOID* pvUserData;  /**<User data which used in callback function*//**<CNcomment:用户数据，用在回调函数pfnIdentify*/
} HI_SVR_CHARSET_ATTR_S;

/** @}*/  /** <!-- ==== Structure Definition End ====*/



/******************************* API Declaration *****************************/
/** \addtogroup      CHARSET*/
/** @{*/  /** <!-- -CHARSET=*/

/**
\brief Init. CNcomment:模块初始化。
\attention \n
none.
\param[in]  pstAttr     The attribute of charset. CNcomment:字符集转码属性。
\retval   ::HI_SUCCESS  success. CNcomment:成功。
\retval   ::HI_FAILURE  failure. CNcomment:失败。
\see \n
none
*/
HI_S32 HI_SVR_CHARSET_Init(HI_SVR_CHARSET_ATTR_S* pstAttr);

/**
\brief DeInit. CNcomment:模块去初始化。
\attention \n
none.
\param[in]  pVoid       Reserved. CNcomment:预留，可以为空指针。
\retval   ::HI_SUCCESS  success. CNcomment:成功。
\retval   ::HI_FAILURE  failure. CNcomment:失败。
\see \n
none
*/
HI_S32 HI_SVR_CHARSET_DeInit(HI_VOID* pVoid);

/**
\brief Charset convert. CNcomment:字符集转码。
\attention \n
Charset code type of source according to Annex A of ETSI EN 300 468 V1.5.1  from the first byte of pu8InBuf.CNcomment:由输入字符串第一字节指出，具体类型可查看ETSI EN 300 468 V1.5.1 协议中的附录A。
Charset code type of dest used the 'enToCodeType' from  HI_SVR_CHARSET_Init () function.CNcomment:用户在HI_SVR_CHARSET_Init() 接口中注册的目标编码类型enToCodeType。
\param[in]  pu8InBuf    The input buffer. CNcomment:输入数据流。
\param[in/out]  ps32InLenLeft The left length of input buffer. CNcomment:输入数据流的长度，输出未转码的数据流长度。
\param[out] pu8OutBuf   The output buffer. CNcomment:输出数据流。
\param[in/out] ps32OutLenLeft The left length of output buffer. CNcomment:输入存储输出数据流的空间长度，输出未使用的剩余空间长度。
\param[in] au8LangCode the laguage code (ISO 639-2) of pu8InBuf, can be NULL. CNcomment:输入数据流对应的语言码ISO 639-2，可为空。
\retval   ::HI_SUCCESS  success. CNcomment:成功。
\retval   ::HI_FAILURE  failure. CNcomment:失败。
\see \n
none
*/
HI_S32 HI_SVR_CHARSET_Conv(const HI_U8* pu8InBuf, HI_S32* ps32InLenLeft, HI_U8* pu8OutBuf, HI_S32* ps32OutLenLeft, const HI_U8 au8LangCode[3]);



/** @}*/  /** <!-- ==== API Declaration End ====*/

/*define*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */
#endif /*__HI_SVR_CHARSET_H__*/
