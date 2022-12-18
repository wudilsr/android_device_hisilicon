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
/** @{ */  /** <!��[CHARSET error code]*/

/** Error code in CHARSET */ /** CNcomment: CHARSET�Ĵ����� */
#define HI_SVR_CHARSET_ERR_BASE              (0x0)
/** Pointer is null */ /** CNcomment:��ָ�� */
#define HI_SVR_CHARSET_ERR_NULL_PTR          (HI_SVR_CHARSET_ERR_BASE+1)
/** Not init */ /** CNcomment:δ��ʼ�� */
#define HI_SVR_CHARSET_ERR_NOT_INIT          (HI_SVR_CHARSET_ERR_BASE+2)
/** Invalid parameter */ /** CNcomment:��Ч���� */
#define HI_SVR_CHARSET_ERR_INVALID_PARAM     (HI_SVR_CHARSET_ERR_BASE+3)
/** No memory */ /** CNcomment:�ڴ治�� */
#define HI_SVR_CHARSET_ERR_NO_MEM            (HI_SVR_CHARSET_ERR_BASE+4)
/** Invalid code type */ /** CNcomment:��Ч�ı������� */
#define HI_SVR_CHARSET_ERR_INVALID_CODETYPE  (HI_SVR_CHARSET_ERR_BASE+5)
/** Open fail */ /** CNcomment:��ʧ�� */
#define HI_SVR_CHARSET_ERR_OPEN_FAIL         (HI_SVR_CHARSET_ERR_BASE+6)


/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      CHARSET */
/** @{*/  /** <!��[CHARSET]*/

/** The charset code type *//** CNcomment:�ַ����������� */
typedef enum hiSVR_CHARSET_CODETYPE_E
{
    HI_SVR_CHARSET_CODETYPE_NONE = 0,        /**<unkonwn type*//**<CNcomment:δʶ������*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_1,       /**<ISO8859-1 *//**<CNcomment:��ŷ��ϵ ��������1*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_2,       /**<ISO8859-2 *//**<CNcomment:��ŷ�Ͷ�ŷ��ϵ��������2*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_3,       /**<ISO8859-3 *//**<CNcomment:ŷ�޶��ϲ���ϵ��������3*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_4,       /**<ISO8859-4 *//**<CNcomment:˹������ά�ǺͲ��޵ĺ���ϵ��������4*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_5,       /**<ISO8859-5 *//**<CNcomment:�����ĺ�˹������*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_6,       /**<ISO8859-6 *//**<CNcomment:�����ĺͰ�������*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_7,       /**<ISO8859-7 *//**<CNcomment:�����ĺ�ϣ����*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_8,       /**<ISO8859-8 *//**<CNcomment:�����ĺ�ϣ������*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_9,       /**<ISO8859-9 *//**<CNcomment:Ϊ�������������������ģ�������5*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_10,      /**<ISO8859_10 *//**<CNcomment:�����ˡ���ŷ�Ͱ�˹��Ħ�˵����֣�������6*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_11,      /**<ISO8859-11 *//**<CNcomment:��������̩��*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_13,      /**<ISO8859-13 *//**<CNcomment:���޵ĺ��ܱ���ϵ��������7*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_14,      /**<ISO8859-14 *//**<CNcomment:�������ģ�������8*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_15,      /**<ISO8859-15 *//**<CNcomment:�Ľ���������1��������9*/
    HI_SVR_CHARSET_CODETYPE_ISO8859_16,      /**<ISO8859-16 *//**<CNcomment:���������ģ�������10*/
    HI_SVR_CHARSET_CODETYPE_UNICODE_16LE,    /**<UNICODE_16LE *//**<CNcomment:16λС�˵�UNICODE*/
    HI_SVR_CHARSET_CODETYPE_UNICODE_16BE,    /**<UNICODE_16BE *//**<CNcomment:16λ��˵�UNICODE*/
    HI_SVR_CHARSET_CODETYPE_GB2312,          /**<GB2312 *//**<CNcomment:��������GB2312*/
    HI_SVR_CHARSET_CODETYPE_GB18030,          /**<GB2312 *//**<CNcomment:��������GB18030*/
    HI_SVR_CHARSET_CODETYPE_BIG5,            /**<BIG5 *//**<CNcomment:��������*/
    HI_SVR_CHARSET_CODETYPE_UTF8,            /**<UTF8 *//**<CNcomment:UTF8*/
    HI_SVR_CHARSET_CODETYPE_CP1250,          /**<CP1250 *//**<CNcomment:��ŷ*/
    HI_SVR_CHARSET_CODETYPE_CP1251,          /**<CP1251 *//**<CNcomment:�������*/
    HI_SVR_CHARSET_CODETYPE_CP1252,          /**<CP1252 *//**<CNcomment:������I*/
    HI_SVR_CHARSET_CODETYPE_CP1253,          /**<CP1253 *//**<CNcomment:ϣ����*/
    HI_SVR_CHARSET_CODETYPE_CP1254,          /**<CP1254 *//**<CNcomment:��������*/
    HI_SVR_CHARSET_CODETYPE_CP1255,          /**<CP1255 *//**<CNcomment:ϣ������*/
    HI_SVR_CHARSET_CODETYPE_CP1256,          /**<CP1256 *//**<CNcomment:��������*/
    HI_SVR_CHARSET_CODETYPE_CP1257,          /**<CP1257 *//**<CNcomment:���޵ĺ���*/
    HI_SVR_CHARSET_CODETYPE_CP1258,          /**<CP1258 *//**<CNcomment:Խ��*/
    HI_SVR_CHARSET_CODETYPE_CP874,           /**<CP874 *//**<CNcomment:̩��*/
    HI_SVR_CHARSET_CODETYPE_UNICODE_32LE,    /**<UNICODE_32LE *//**<CNcomment:32λС�˵�UNICODE*/
    HI_SVR_CHARSET_CODETYPE_UNICODE_32BE,    /**<UNICODE_32BE *//**<CNcomment:32λ��˵�UNICODE*/
    HI_SVR_CHARSET_CODETYPE_ISO6937,         /**<ISO6937 *//**<CNcomment:�����ַ���*/
    HI_SVR_CHARSET_CODETYPE_KSC5601,         /**<Korean Character Set KSC5601-1987,currently not support*//**<CNcomment:KSC5601�����ַ�����Ŀǰ�ݲ�֧��*/
    HI_SVR_CHARSET_CODETYPE_BUTT,
} HI_SVR_CHARSET_CODETYPE_E;


/**
\brief user identify call back function. CNcomment: �û��ַ�ʶ��ص���������
\attention \n
none. it will be called when charset inner identify faile��CNcomment: ��chaset �ڲ�ʶ��ʧ�ܵ�����£����øýӿڡ�
it used to identify charset code type in non-standard string according to DVB SI�� CNcomment:����ʶ��DVB SIЭ���зǱ�׼�ַ����ı������͡�
\param[in]  pu8InBuf      The input string buffer. CNcomment: �����ַ�����
\param[in]  s32InLen      The length of input string buffer. CNcomment:�����������ĳ��ȡ�
\param[in]  pvUserData   The user private data from HI_SVR_CHARSET_Init() function. CNcomment:�û���HI_SVR_CHARSET_Init ע���˽������pvUserData��
\param[out]  penCodeType   The charset code type of input string buffer. CNcomment: �����ַ������ַ��������͡�
\param[in]  au8LangCode     The language code of input string buffer, maybe null(e.g. Service Name in SDT).CNcomment:�����ַ�����Ӧ������������,����Ϊ��( ��SDT  ���е�ҵ������)��
\retval   ::HI_SUCCESS  success. CNcomment:�ɹ���
\retval   ::HI_FAILURE  failure. CNcomment:ʧ�ܡ�
\see \n
none
*/
typedef HI_S32 (*HI_SVR_CHARSET_IDENTIFY_CB_FN)(const HI_U8* pu8InBuf, HI_S32 s32InLen, HI_VOID* pvUserData, HI_SVR_CHARSET_CODETYPE_E* penCodeType, const HI_U8 au8LangCode[3]);




/**
\brief user charset convert call back function. CNcomment: �û��ַ�ת��ص���������
\attention \n
none. it will be called when charset inner convert faile��CNcomment: ��chaset �ڲ�ת��ʧ�ܵ�����£����øýӿڡ�
\param[in]  pu8InBuf      The input string buffer(not include the byte of Charset code type ). CNcomment:�����ַ���(�������ַ����������ֽ�)��
\param[in/out]  ps32InLenLeft The left length of input buffer. CNcomment:�����������ĳ��ȣ����δת������������ȡ�
\param[out] pu8OutBuf   The output buffer. CNcomment:�����������
\param[in/out] ps32OutLenLeft The left length of output buffer. CNcomment:����洢����������Ŀռ䳤�ȣ����δʹ�õ�ʣ��ռ䳤�ȡ�
\param[in]  penCodeType   The charset code type of input string buffer. CNcomment: �����ַ������ַ��������͡�
\retval   ::HI_SUCCESS  success. CNcomment:�ɹ���
\retval   ::HI_FAILURE  failure. CNcomment:ʧ�ܡ�
\see \n
none
*/
typedef HI_S32 (*HI_SVR_CHARSET_CONV_CB_FN)(const HI_U8* pu8InBuf, HI_S32* ps32InLenLeft, HI_U8* pu8OutBuf, HI_S32* ps32OutLenLeft, HI_SVR_CHARSET_CODETYPE_E enCodeType);



/** The attribute of charset *//** CNcomment:�ַ���ת��ģ������� */
typedef struct hiSVR_CHARSET_ATTR_S
{
    HI_SVR_CHARSET_CODETYPE_E     enToCodeType; /**<The target Charset code type, it will just do copy when enToCodeType is HI_SVR_CHARSET_CODETYPE_NONE*/ /**<CNcomment:Ŀ��������ͣ����ΪHI_SVR_CHARSET_CODETYPE_NONE��ֱ�ӿ���͸��*/
    HI_SVR_CHARSET_IDENTIFY_CB_FN pfnIdentify;  /**<The callback function to identify charset code type*//**<CNcomment:����ַ�����Ļص�����*/
    HI_SVR_CHARSET_CONV_CB_FN     pfnConvert;   /**<The callback function to convert string*//**<CNcomment:�ַ�ת��ص�����*/
    HI_VOID* pvUserData;  /**<User data which used in callback function*//**<CNcomment:�û����ݣ����ڻص�����pfnIdentify*/
} HI_SVR_CHARSET_ATTR_S;

/** @}*/  /** <!-- ==== Structure Definition End ====*/



/******************************* API Declaration *****************************/
/** \addtogroup      CHARSET*/
/** @{*/  /** <!-- -CHARSET=*/

/**
\brief Init. CNcomment:ģ���ʼ����
\attention \n
none.
\param[in]  pstAttr     The attribute of charset. CNcomment:�ַ���ת�����ԡ�
\retval   ::HI_SUCCESS  success. CNcomment:�ɹ���
\retval   ::HI_FAILURE  failure. CNcomment:ʧ�ܡ�
\see \n
none
*/
HI_S32 HI_SVR_CHARSET_Init(HI_SVR_CHARSET_ATTR_S* pstAttr);

/**
\brief DeInit. CNcomment:ģ��ȥ��ʼ����
\attention \n
none.
\param[in]  pVoid       Reserved. CNcomment:Ԥ��������Ϊ��ָ�롣
\retval   ::HI_SUCCESS  success. CNcomment:�ɹ���
\retval   ::HI_FAILURE  failure. CNcomment:ʧ�ܡ�
\see \n
none
*/
HI_S32 HI_SVR_CHARSET_DeInit(HI_VOID* pVoid);

/**
\brief Charset convert. CNcomment:�ַ���ת�롣
\attention \n
Charset code type of source according to Annex A of ETSI EN 300 468 V1.5.1  from the first byte of pu8InBuf.CNcomment:�������ַ�����һ�ֽ�ָ�����������Ϳɲ鿴ETSI EN 300 468 V1.5.1 Э���еĸ�¼A��
Charset code type of dest used the 'enToCodeType' from  HI_SVR_CHARSET_Init () function.CNcomment:�û���HI_SVR_CHARSET_Init() �ӿ���ע���Ŀ���������enToCodeType��
\param[in]  pu8InBuf    The input buffer. CNcomment:������������
\param[in/out]  ps32InLenLeft The left length of input buffer. CNcomment:�����������ĳ��ȣ����δת������������ȡ�
\param[out] pu8OutBuf   The output buffer. CNcomment:�����������
\param[in/out] ps32OutLenLeft The left length of output buffer. CNcomment:����洢����������Ŀռ䳤�ȣ����δʹ�õ�ʣ��ռ䳤�ȡ�
\param[in] au8LangCode the laguage code (ISO 639-2) of pu8InBuf, can be NULL. CNcomment:������������Ӧ��������ISO 639-2����Ϊ�ա�
\retval   ::HI_SUCCESS  success. CNcomment:�ɹ���
\retval   ::HI_FAILURE  failure. CNcomment:ʧ�ܡ�
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
