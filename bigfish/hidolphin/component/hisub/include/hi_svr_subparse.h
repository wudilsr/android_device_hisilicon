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
 * \brief Describes the information about the subtitle prase module. CNcomment: 提供字幕解析模块的相关信息 CNend
 */

#ifndef __HI_SVR_SUBPARSE_H__
#define __HI_SVR_SUBPARSE_H__

/* add include here */
#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/

#define MAX_SUB_PARSE_NUM (16)   /**max parase number supported*/ /** CNcomment:最大支持的解析实例 */

/*************************** Structure Definition ****************************/
/** Enum of subtitle types supported*/
/** CNcomment:支持的字幕类型枚举 */
typedef enum hiSVR_SUB_TYPE_E
{
    HI_SVR_SUB_TYPE_TTML = 0, /* TTML subtitle,and this type requires send data by api HI_SVR_SUB_SendData*//**<CNcomment:TTML字幕，该类型要求使用HI_SVR_SUB_SendData主动送数据*/
    HI_SVR_SUB_TYPE_BUTT
} HI_SVR_SUB_TYPE_E;

/** Subtitle data structure*/
/** CNcomment:字幕数据结构 */
typedef struct hiSVR_SUB_DATA_S
{
    HI_S64             s64PTS;/** PTS of the subtitle data*//** CNcomment:字幕数据对应的PTS */
    HI_U32             u32DurationMs;/** Duration of the subtitle data, unit in ms*//** CNcomment:字幕数据持续时间，单位毫秒 */
    HI_U32             u32SubDataLen;/** The subtitle data length*//** CNcomment:字幕数据长度 */
    HI_U32             u32SubBuffLen;/**Do not care*//** CNcomment:内部使用属性，外部不用关注 */
    HI_CHAR*           ps8SubtData;/** The subtitle data pointer*//** CNcomment:字幕数据指针*/
    HI_U32             u32ExtId;/** Exter ID,for further parase*//** CNcomment:外部ID，为进一步解码预留*/
} HI_SVR_SUB_DATA_S;

/** Key value, used for further parase*/
/** CNcomment:字幕键值对，为进一步解码预留 */
typedef struct hiSVR_SUB_KeyVP_S
{
    HI_U32             u32ExtId;/** Exter ID,for further parase*//** CNcomment:外部ID，为进一步解码预留*/
    HI_CHAR*           ps8Name;/** Key name*//** CNcomment:key名*/
    HI_U32             u32NameDatalen;/** Name data length*//** CNcomment:Name数据长度*/
    HI_U32             u32NameBufflen;/**Do not care*//** CNcomment:内部使用属性，外部不用关注 */
    HI_CHAR*           ps8Value;/** Key value*//** CNcomment:Value 数据*/
    HI_U32             u32ValueDatalen;/** Key value data length*//** CNcomment:Value 数据长度*/
    HI_U32             u32ValueBufflen;/**Do not care*//** CNcomment:内部使用属性，外部不用关注 */
} HI_SVR_SUB_KeyVP;

/** Read subtitle raw data callback*/
/** CNcomment:读取字幕原始数据回调 */
typedef  HI_S32 (*HI_SVR_SUB_READ_FN)( HI_HANDLE hSub, HI_U8 *pu8Buf, HI_S32 s32Size);

/** Seek subtitle raw data callback*/
/** CNcomment:读取字幕原始数据时SEEK操作回调 */
typedef  HI_S32 (*HI_SVR_SUB_SEEK_FN)( HI_HANDLE hSub, HI_S64 s64Offsets, HI_S32 s32Whence);

/** Subtitle attribute param structure*/
/** CNcomment:字幕属性参数结构 */
typedef struct hiSVR_SUB_PARAM_S
{
    HI_SVR_SUB_TYPE_E  eSubType;/**< Subtitle type,see declaration of HI_SVR_SUB_TYPE_E */  /**<CNcomment:字幕类型回调，参考类型HI_SVR_SUB_TYPE_E*/
    HI_SVR_SUB_READ_FN pfnReadCb; /**< Callback function of read raw data */  /**<CNcomment:读取原始数据回调函数*/
    HI_SVR_SUB_SEEK_FN pfnSeekCb; /**<Callback function of seek */       /**<CNcomment:seek回调函数*/
    HI_S32             s32PtsAdjustValue;/**<pts adjust value,the value can be positive or negative */ /**<CNcomment:最终算pts的时候会加上该数据,该数值可以为正也可以为负*/
    HI_U32            u32UserData; /**<User data */   /**<CNcomment:用户数据*/
} HI_SVR_SUB_PARAM_S;

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/


/**
\brief Initializes the subtitle prase module.CNcomment:字幕解析模块初始化 CNend
\attention \n
Before calling ::HI_SVR_SUB_Parse_Create to create an subtitle praser, you must call this API.
CNcomment 在调用::HI_SVR_SUB_Prase_Create接口创建字幕解析器前之前，调用本接口 CNend
\param  N/A
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failure CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_Init(HI_VOID);


/**
\brief Deinitializes the subtitle prase module.CNcomment:字幕解析模块去初始化 CNend
\attention \n
\param  N/A
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failure CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_DeInit(HI_VOID);


/**
\brief Create an subtitle praser .CNcomment:创建字幕解析器 CNend
\attention \n
\param[int] pstSubParam  Pointer to subtitle praser attributes. For details, see the description of ::HI_SVR_SUB_PARAM_S. CNcomment: 指针类型，字幕解析器属性，请参见::HI_SVR_SUB_PARAM_S CNend
\param[out] phSub    Pointer to the handle of a created subtitle praser.CNcomment:指针类型，创建的字幕解析器句柄 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failure CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_Create(HI_SVR_SUB_PARAM_S *pstSubParam, HI_HANDLE *phSub);


/**
\brief Destroy an subtitle praser .CNcomment:消耗字幕解析器 CNend
\attention \n
\param[in] hSub    Handle of the subtitle praser.CNcomment:字幕解析器句柄 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failure CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_Destroy(HI_HANDLE hSub);


/**
\brief Reset an subtitle praser .CNcomment:复位字幕解析器 CNend
\attention \n
\param[in] hSub    Handle of the subtitle praser.CNcomment:字幕解析器句柄 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failure CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_Reset(HI_HANDLE hSub);


 /**
\brief Read subtitle node data .CNcomment:读取字幕数据 CNend
\attention \n
\param[in] hSub    Handle of the subtitle praser.CNcomment:字幕解析器句柄 CNend
\param[in] s64PtsAdjustTimeMs    PTS adjust value,in ms.CNcomment:PTS调整值，单位ms CNend
\param[out] pstSubNodeBuf    Pointer to subtitle node data.CNcomment:指针类型，执行字幕数据 CNend
\param[out] pu32NodeNum    Subtitle node data number.CNcomment:字幕数据个数 CNend
\param[out] pstSubKeyVpBuf     Pointer to subtitle key value.CNcomment:指针类型，执行字幕键值对数据 CNend
\param[out] pu32KeyVpNum     Number of subtitle key value.CNcomment:指针类型，字幕键值对个数 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failure CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_ReadSubNodes(HI_HANDLE hSub, HI_S64 s64PtsAjustTimeMs, HI_SVR_SUB_DATA_S** pstSubNodeBuf, HI_U32* pu32NodeNum,
                               HI_SVR_SUB_KeyVP** pstSubKeyVpBuf,
                               HI_U32* pu32KeyVpNum);


 /**
\brief Send subtitle raw data .CNcomment:发送字幕原始数据 CNend
\attention \n
Note: use HI_SVR_SUB_Parse_SendData send raw data or read data by call back function internally,is Determined by the type of subtitle.
CNcomment:到底是使用HI_SVR_SUB_Prase_SendData发送原始数据，还是在模块内部通过回调方式读取原始数据，是由字幕类型决定的。 CNend
\param[in] hSub    Handle of the subtitle praser.CNcomment:字幕解析器句柄 CNend
\param[in] pData    Pointer of raw data CNcomment:指针类型，字幕原始数据 CNend
\param[in] u32DataLen    Length of the raw data.CNcomment:原始数据的长度 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failure CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_SendData(HI_HANDLE hSub, HI_U8* pData, HI_U32 u32DataLen);

/*
输入：hSub:字幕handle
返回：HI_SUCCESS-成功， HI_FAILURE-失败。
描述：快速退出请求，字幕解析模块在接收到该接口的调用时，马上退出。防止出现接口长时间不返回的情况。*/
/**
\brief Quick quit requeset,whenever this API is called,the APIS of this module will quit immediately .CNcomment:快速退出请求，一旦调用了该接口，该模块的所有接口都需要马上返回 CNend
\attention \n
\param[in] hSub    Handle of the subtitle praser.CNcomment:字幕解析器句柄 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failure CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_SVR_SUB_Parse_QuickQuitRequest (HI_HANDLE hSub);

#ifdef __cplusplus
}
#endif
#endif /* __HI_SVR_SUBPARSE_H__ */
