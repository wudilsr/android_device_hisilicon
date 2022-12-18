/******************************************************************************

  Copyright (C), 2008-2018, HiSilicon Technologies Co., Ltd.

 ******************************************************************************
  File Name     : hi_svr_subprase.h
  Version       : Initial draft
  Author        : Device Chipset STB Development Dept
  Created Date  : 2013-09-21
  Description   :
  Change History:
  Date          : 2013-09-21
  Author        : liaokaifu
  Description   : This file is created.

*******************************************************************************/
/**
 * \file
 * \brief Describes the information about the subtitle prase module. CNcomment: �ṩ��Ļ����ģ��������Ϣ CNend
 */

#ifndef __HI_SVR_SUBPARSE_H__
#define __HI_SVR_SUBPARSE_H__

/* add include here */
#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/

#define MAX_SUB_PARSE_NUM (16)   /**max parase number supported*/ /** CNcomment:���֧�ֵĽ���ʵ�� */

/*************************** Structure Definition ****************************/
/** Enum of subtitle types supported*/
/** CNcomment:֧�ֵ���Ļ����ö�� */
typedef enum hiSVR_SUB_TYPE_E
{
    HI_SVR_SUB_TYPE_TTML = 0, /* TTML subtitle,and this type requires send data by api HI_SVR_SUB_SendData*//**<CNcomment:TTML��Ļ��������Ҫ��ʹ��HI_SVR_SUB_SendData����������*/
    HI_SVR_SUB_TYPE_BUTT
} HI_SVR_SUB_TYPE_E;

/** Subtitle data structure*/
/** CNcomment:��Ļ���ݽṹ */
typedef struct hiSVR_SUB_DATA_S
{
    HI_S64             s64PTS;/** PTS of the subtitle data*//** CNcomment:��Ļ���ݶ�Ӧ��PTS */
    HI_U32             u32DurationMs;/** Duration of the subtitle data, unit in ms*//** CNcomment:��Ļ���ݳ���ʱ�䣬��λ���� */
    HI_U32             u32SubDataLen;/** The subtitle data length*//** CNcomment:��Ļ���ݳ��� */
    HI_U32             u32SubBuffLen;/**Do not care*//** CNcomment:�ڲ�ʹ�����ԣ��ⲿ���ù�ע */
    HI_CHAR*           ps8SubtData;/** The subtitle data pointer*//** CNcomment:��Ļ����ָ��*/
    HI_U32             u32ExtId;/** Exter ID,for further parase*//** CNcomment:�ⲿID��Ϊ��һ������Ԥ��*/
} HI_SVR_SUB_DATA_S;

/** Key value, used for further parase*/
/** CNcomment:��Ļ��ֵ�ԣ�Ϊ��һ������Ԥ�� */
typedef struct hiSVR_SUB_KeyVP_S
{
    HI_U32             u32ExtId;/** Exter ID,for further parase*//** CNcomment:�ⲿID��Ϊ��һ������Ԥ��*/
    HI_CHAR*           ps8Name;/** Key name*//** CNcomment:key��*/
    HI_U32             u32NameDatalen;/** Name data length*//** CNcomment:Name���ݳ���*/
    HI_U32             u32NameBufflen;/**Do not care*//** CNcomment:�ڲ�ʹ�����ԣ��ⲿ���ù�ע */
    HI_CHAR*           ps8Value;/** Key value*//** CNcomment:Value ����*/
    HI_U32             u32ValueDatalen;/** Key value data length*//** CNcomment:Value ���ݳ���*/
    HI_U32             u32ValueBufflen;/**Do not care*//** CNcomment:�ڲ�ʹ�����ԣ��ⲿ���ù�ע */
} HI_SVR_SUB_KeyVP;

/** Read subtitle raw data callback*/
/** CNcomment:��ȡ��Ļԭʼ���ݻص� */
typedef  HI_S32 (*HI_SVR_SUB_READ_FN)( HI_HANDLE hSub, HI_U8 *pu8Buf, HI_S32 s32Size);

/** Seek subtitle raw data callback*/
/** CNcomment:��ȡ��Ļԭʼ����ʱSEEK�����ص� */
typedef  HI_S32 (*HI_SVR_SUB_SEEK_FN)( HI_HANDLE hSub, HI_S64 s64Offsets, HI_S32 s32Whence);

/** Subtitle attribute param structure*/
/** CNcomment:��Ļ���Բ����ṹ */
typedef struct hiSVR_SUB_PARAM_S
{
    HI_SVR_SUB_TYPE_E  eSubType;/**< Subtitle type,see declaration of HI_SVR_SUB_TYPE_E */  /**<CNcomment:��Ļ���ͻص����ο�����HI_SVR_SUB_TYPE_E*/
    HI_SVR_SUB_READ_FN pfnReadCb; /**< Callback function of read raw data */  /**<CNcomment:��ȡԭʼ���ݻص�����*/
    HI_SVR_SUB_SEEK_FN pfnSeekCb; /**<Callback function of seek */       /**<CNcomment:seek�ص�����*/
    HI_S32             s32PtsAdjustValue;/**<pts adjust value,the value can be positive or negative */ /**<CNcomment:������pts��ʱ�����ϸ�����,����ֵ����Ϊ��Ҳ����Ϊ��*/
    HI_U32            u32UserData; /**<User data */   /**<CNcomment:�û�����*/
} HI_SVR_SUB_PARAM_S;

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/


/**
\brief Initializes the subtitle prase module.CNcomment:��Ļ����ģ���ʼ�� CNend
\attention \n
Before calling ::HI_SVR_SUB_Parse_Create to create an subtitle praser, you must call this API.
CNcomment �ڵ���::HI_SVR_SUB_Prase_Create�ӿڴ�����Ļ������ǰ֮ǰ�����ñ��ӿ� CNend
\param  N/A
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_Init(HI_VOID);


/**
\brief Deinitializes the subtitle prase module.CNcomment:��Ļ����ģ��ȥ��ʼ�� CNend
\attention \n
\param  N/A
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_DeInit(HI_VOID);


/**
\brief Create an subtitle praser .CNcomment:������Ļ������ CNend
\attention \n
\param[int] pstSubParam  Pointer to subtitle praser attributes. For details, see the description of ::HI_SVR_SUB_PARAM_S. CNcomment: ָ�����ͣ���Ļ���������ԣ���μ�::HI_SVR_SUB_PARAM_S CNend
\param[out] phSub    Pointer to the handle of a created subtitle praser.CNcomment:ָ�����ͣ���������Ļ��������� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_Create(HI_SVR_SUB_PARAM_S *pstSubParam, HI_HANDLE *phSub);


/**
\brief Destroy an subtitle praser .CNcomment:������Ļ������ CNend
\attention \n
\param[in] hSub    Handle of the subtitle praser.CNcomment:��Ļ��������� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_Destroy(HI_HANDLE hSub);


/**
\brief Reset an subtitle praser .CNcomment:��λ��Ļ������ CNend
\attention \n
\param[in] hSub    Handle of the subtitle praser.CNcomment:��Ļ��������� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_Reset(HI_HANDLE hSub);


 /**
\brief Read subtitle node data .CNcomment:��ȡ��Ļ���� CNend
\attention \n
\param[in] hSub    Handle of the subtitle praser.CNcomment:��Ļ��������� CNend
\param[in] s64PtsAdjustTimeMs    PTS adjust value,in ms.CNcomment:PTS����ֵ����λms CNend
\param[out] pstSubNodeBuf    Pointer to subtitle node data.CNcomment:ָ�����ͣ�ִ����Ļ���� CNend
\param[out] pu32NodeNum    Subtitle node data number.CNcomment:��Ļ���ݸ��� CNend
\param[out] pstSubKeyVpBuf     Pointer to subtitle key value.CNcomment:ָ�����ͣ�ִ����Ļ��ֵ������ CNend
\param[out] pu32KeyVpNum     Number of subtitle key value.CNcomment:ָ�����ͣ���Ļ��ֵ�Ը��� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_ReadSubNodes(HI_HANDLE hSub, HI_S64 s64PtsAjustTimeMs, HI_SVR_SUB_DATA_S** pstSubNodeBuf, HI_U32* pu32NodeNum,
                               HI_SVR_SUB_KeyVP** pstSubKeyVpBuf,
                               HI_U32* pu32KeyVpNum);


 /**
\brief Send subtitle raw data .CNcomment:������Ļԭʼ���� CNend
\attention \n
Note: use HI_SVR_SUB_Parse_SendData send raw data or read data by call back function internally,is Determined by the type of subtitle.
CNcomment:������ʹ��HI_SVR_SUB_Prase_SendData����ԭʼ���ݣ�������ģ���ڲ�ͨ���ص���ʽ��ȡԭʼ���ݣ�������Ļ���;����ġ� CNend
\param[in] hSub    Handle of the subtitle praser.CNcomment:��Ļ��������� CNend
\param[in] pData    Pointer of raw data CNcomment:ָ�����ͣ���Ļԭʼ���� CNend
\param[in] u32DataLen    Length of the raw data.CNcomment:ԭʼ���ݵĳ��� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_SendData(HI_HANDLE hSub, HI_U8* pData, HI_U32 u32DataLen);

/*
���룺hSub:��Ļhandle
���أ�HI_SUCCESS-�ɹ��� HI_FAILURE-ʧ�ܡ�
�����������˳�������Ļ����ģ���ڽ��յ��ýӿڵĵ���ʱ�������˳�����ֹ���ֽӿڳ�ʱ�䲻���ص������*/
/**
\brief Quick quit requeset,whenever this API is called,the APIS of this module will quit immediately .CNcomment:�����˳�����һ�������˸ýӿڣ���ģ������нӿڶ���Ҫ���Ϸ��� CNend
\attention \n
\param[in] hSub    Handle of the subtitle praser.CNcomment:��Ļ��������� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_QuickQuitRequest (HI_HANDLE hSub);

#ifdef __cplusplus
}
#endif
#endif /* __HI_SVR_SUBPARSE_H__ */
