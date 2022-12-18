/******************************************************************************
  Copyright (C), 2004-2015, Hisilicon Tech. Co., Ltd.
******************************************************************************
  File Name     : hi_unf_karaoke.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/1/22
  Last Modified :
  Description   : header file for karaoke
  Function List :
  History       :
  1.Date        :
  Author        : z00234938
  Modification  : Created file
******************************************************************************/

/**
 * \file
 * \brief Describes the information about karaoke module. CNcomment:提供karaoke的相关信息 CNend
 */

#ifndef  __HI_KARAOKE_H__
#define  __HI_KARAOKE_H__

#include "hi_unf_common.h"
#include "hi_unf_aenc.h"
#include "hi_unf_sound.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/********************************Macro Definition********************************/
#define HI_KARAOKE_ALSA_NAME_MAX 128

/*************************** Structure Definition ****************************/
/** \addtogroup      KARAOKE */
/** @{ */  /** <!--  【KARAOKE】 */

/**karaoke attribute */
/**CNcomment:卡拉OK属性*/
typedef struct hiHI_KARAOKE_ATTR_S
{
    HI_CHAR acMicDevName[HI_KARAOKE_ALSA_NAME_MAX];/**<Input, description information about micphone device name. */
    HI_U32         u32MicDevNum; /**<IN the number of Mic dev*/ /**<CNcomment:麦克风数目*/
    HI_U32         u32BitPerSample; /**<IN bitwidth per sample.*/ /**<CNcomment:位宽*/
    HI_U32         u32DesiredSampleRate; /**<IN desired samplerate.*//**<CNcomment:期望采样率*/
    HI_BOOL        bMicDataCaptureEnable;/**<IN Enable or Disable Capture Mic Data.*/ /**<CNcomment:启动或停止获取麦克风数据*/
    HI_BOOL        bMixDataCaptureEnable;/**<IN Enable or Disable Capture Mix Data.*/ /**<CNcomment:启动或停止获取混音后数据*/
} HI_KARAOKE_ATTR_S;

/**Defines  karaoke mix frame attribute */
/**CNcomment:定义卡拉OK混音后帧数据属性*/
typedef struct hiHI_KARAOKE_MIXDATAFRAME_S
{
    HI_UNF_ES_BUF_S stMixBufStream;   /** Es Bitstream: aac: ADTS Frame */

} HI_KARAOKE_MIXDATAFRAME_S;

/**Defines  karaoke mix attribute */
/**CNcomment:定义卡拉OK混音属性*/
typedef struct hiHI_KRAOKE_MIX_ATTR_S
{
    HI_S32          s32SampleRate;    /**< audio file sample rate */
    HI_S32          s32BitRate;       /**< encoder bit rate in bits/sec */
    HI_S16          s16ChannelsIn;    /**< number of channels on input (1,2) */
    HI_S16          s16ChannelsOut;  /**< number of channels on output (1,2) */
} HI_KARAOKE_MIX_ATTR_S;


/**Defines  Audio revervb type */
/**CNcomment:定义音效混响模式*/
typedef enum hiHI_KARAOKE_REVERB_TYPE_E
{
    HI_KARAOKE_REVERB_TYPE_NULL = 0,
    HI_KARAOKE_REVERB_TYPE_KTV,           /**<KTV Mode*/ /**<CNcomment:KTV模式*/
    HI_KARAOKE_REVERB_TYPE_THEATRE,       /**<theatre Mode*/ /**<CNcomment:剧场模式*/
    HI_KARAOKE_REVERB_TYPE_HALL,          /**<hall Mode*/ /**<CNcomment:大厅模式*/
    HI_KARAOKE_REVERB_TYPE_CONCERT,       /**<concert Mode*/ /**<CNcomment:演唱会模式*/
    HI_KARAOKE_REVERB_TYPE_VALLEY,        /**<valley Mode*/ /**<CNcomment:山谷模式*/
    HI_KARAOKE_REVERB_TYPE_BUTT
} HI_KARAOKE_REVERB_TYPE_E;

/**
 \brief Destory Karaoke Handle CNcomment:销毁创建卡拉OK句柄 CNend
 \attention \n
 \param[in] hKaraoke   The handle of the destory Karaoke CNcomment:指针类型，销毁的Karaoke 句柄 CNend
N/A
 */
HI_VOID   HI_KARAOKE_DeInit(HI_HANDLE hKaraoke);

/**
 \brief Create Karaoke Handle CNcomment:创建卡拉OK句柄 CNend
 \attention \n
 \param[out] phKaraoke   Pointer to the handle of the created Karaoke CNcomment:指针类型，创建的Karaoke 句柄 CNend
 \retval ::HI_SUCCESS Success CNcomment:成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \see \n
N/A
 */
HI_S32   HI_KARAOKE_Init(HI_HANDLE* phKaraoke);

/**
 \brief Obtains the default configured parameters of Karaoke. CNcomment:获取KARAOKE默认设置参数 CNend
 \attention \n
 \param[out] pstAttr     Audio attributes CNcomment:音频属性 CNend
 \retval ::HI_SUCCESS Success CNcomment:成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR  The pointer is null. CNcomment:指针参数为空 CNend
 \see \n
N/A
 */
HI_S32   HI_KARAOKE_GetDefaultKaraokeAttr(HI_KARAOKE_ATTR_S*  pstAttr);

/**
 \brief Create Karaoke CNcomment:创建卡拉OK CNend
 \attention \n
 \param[in] enSound     ID of an AO device CNcomment:音频输出设备号 CNend
 \param[in] pKaraokeAttr Karaoke attributes CNcomment:指针类型，Karaoke 属性 CNend
 \param[out] phKaraoke   Pointer to the handle of the created Karaoke CNcomment:指针类型，创建的Karaoke 句柄 CNend
 \retval ::HI_SUCCESS Success CNcomment:成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR           The pointer is null. CNcomment:指针参数为空 CNend
 \see \n
N/A
 */
HI_S32   HI_KARAOKE_Create(HI_UNF_SND_E enSound, HI_KARAOKE_ATTR_S*  pKaraokeAttr, HI_HANDLE hKaraoke);

/**
 \brief Destroy Karaoke. CNcomment:销毁Karaoke CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment:Karaoke 句柄 CNend
 \retval ::HI_SUCCESS Success CNcomment:成功 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
N/A
 */
HI_S32   HI_KARAOKE_Destroy(HI_HANDLE hKaraoke);

/**
 \brief enable or Disable Karaoke. CNcomment: 使能或者停止Karaoke通道 CNend
 \attention \n
 \param[in] hKaraoke  the handle of the Karaoke CNcomment: Karaoke句柄 CNend
 \param[in] bEnable      enable  .CNcomment:使能控制 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
N/A CNcomment: 无 CNend
*/

HI_S32   HI_KARAOKE_SetEnable(HI_HANDLE hKaraoke, HI_BOOL bEnable);

/**
 \brief Obtains enable/disable status of Karaoke. CNcomment: 获取Karaoke通道时能状态 CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke句柄 CNend
 \param[out] pbEnable enable/disable status Karaoke CNcomment:Karaoke时能状态 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */

HI_S32   HI_KARAOKE_GetEnable(HI_HANDLE hKaraoke, HI_BOOL* pbEnable);

/**
 \brief Sets the L/R channel weight of karaoke. CNcomment:设置卡拉OK左右声道权重 CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke句柄 CNend
 \param[in] pstMicWeightGain   the channel Weight Gain CNcomment:权重 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */

HI_S32   HI_KARAOKE_SetMicWeight(HI_HANDLE hKaraoke, const HI_UNF_SND_ABSGAIN_ATTR_S* pstMicWeightGain);

/**
 \brief Obtains the L/R channel weight of karaoke. CNcomment:获取卡拉OK左右声道权重 CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke句柄 CNend
 \param[in] pstMicWeightGain     Pointer to the ChannelWeight Gain CNcomment:指针类型，权重属性 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */

HI_S32   HI_KARAOKE_GetMicWeight(HI_HANDLE hKaraoke, HI_UNF_SND_ABSGAIN_ATTR_S* pstMicWeightGain);

/**
 \brief Sets mute or unmute of karaoke. CNcomment:设置卡拉OK静音功能 CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke句柄 CNend
 \param[in] bMute    mute or not CNcomment:静音与否 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */


HI_S32   HI_KARAOKE_SetMute(HI_HANDLE hKaraoke, HI_BOOL bMute);

/**
 \brief Gets mute status of karaoke. CNcomment:获取卡拉OK的静音状态 CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke句柄 CNend
 \param[out] pbMute               mute status CNcomment:静音状态 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */

HI_S32   HI_KARAOKE_GetMute(HI_HANDLE hKaraoke, HI_BOOL* pbMute);

/**
 \brief set the attribute of karaoke, reversed. CNcomment:设置卡拉OK属性， 预留 CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke句柄 CNend
 \param[in] pstKaraokeAttr   the attribute of the karaoke CNcomment:卡拉OK 属性 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */


HI_S32   HI_KARAOKE_SetAttr(HI_HANDLE hKaraoke, const HI_KARAOKE_ATTR_S*  pstKaraokeAttr);

/**
 \brief get the attribute of  a karaoke, reversed. CNcomment:获取卡拉OK的属性， 预留 CNend
 \attention \n
 \param[in] hKaraoke   the handle of the Karaoke CNcomment:Karaoke 句柄 CNend
 \param[out] pstTrackAttr   the attribute of the Karaoke CNcomment:Karaoke 属性 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */

HI_S32   HI_KARAOKE_GetAttr(HI_HANDLE hKaraoke, HI_KARAOKE_ATTR_S*  pstTrackAttr);


/**
 \brief enable or Disable capture mic frame. CNcomment: 使能或者停止获取麦克风数据 CNend
 \attention \n
 \param[in] hKaraoke   the handle of the Karaoke CNcomment:Karaoke 句柄 CNend
 \param[in] bEnable      enable  .CNcomment:使能控制 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */

HI_S32   HI_KARAOKE_SetAcquireMicFrameEnable(HI_HANDLE hKaraoke, HI_BOOL bEnable);

/**
 \brief Obtains enable/disable status of capture mic frame. CNcomment: 获取Karaoke获取麦克风数据 状态 CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke句柄 CNend
 \param[out] pbEnable enable/disable status Karaoke CNcomment:Karaoke时能状态 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */
HI_S32   HI_KARAOKE_GetAcquireMicFrameEnable(HI_HANDLE hKaraoke, HI_BOOL* pbEnable);

/**
 \brief Acquire the audio frame from mic. CNcomment:获取麦克风的音频帧 CNend
 \attention \n
 \param[in] hKaraoke   the handle of the Track CNcomment:Track 句柄 CNend
 \param[in] u32TimeoutMs         acquire timeout.CNcomment:获取超时 CNend
 \param[out] pstAOFrame the audio frame  CNcomment:Track 音频帧 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */


HI_S32   HI_KARAOKE_AcquireMicFrame(HI_HANDLE hKaraoke, HI_UNF_AO_FRAMEINFO_S* pstAOFrame, HI_U32 u32TimeoutMs);

/**
 \brief Release the audio frame . CNcomment:释放麦克风 音频帧 CNend
 \attention \n
 \param[in] hKaraoke   the handle of the Track CNcomment:Track 句柄 CNend
 \param[in] pstAOFrame the audio frame  CNcomment:Track 音频帧 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
*/

HI_S32   HI_KARAOKE_ReleaseMicFrame(HI_HANDLE hKaraoke, HI_UNF_AO_FRAMEINFO_S* pstAOFrame);

/**
\brief set the attribute of MixFrame, reversed. CNcomment:设置声音共享帧信息属性， 预留 CNend
\attention \n
\param[in] hKaraoke the handle of the Track CNcomment:hKaraoke 句柄 CNend
\param[in] pstAencAttr the attribute of the MixFrame CNcomment:hKaraoke 属性 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_ERR_KARAOKE_INVALPARAM        The parameter is invalid. CNcomment:无效的参数 CNend
\retval ::HI_ERR_KARAOKE_NULL_PTR            The pointer is null. CNcomment:指针为空 CNend
\see \n
N/A
*/
HI_S32   HI_KARAOKE_SetMixFrameAttr(HI_HANDLE hKaraoke, HI_KARAOKE_MIX_ATTR_S* pstMixAttr);

/**
 \brief enable or Disable capture mix frame. CNcomment: 使能或者停止获取混音后的数据 CNend
 \attention \n
 \param[in] hKaraoke   the handle of the Karaoke Ncomment:Karaoke 句柄 CNend
 \param[in] bEnable      enable  .CNcomment:使能控制 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */

HI_S32   HI_KARAOKE_SetAcquireMixFrameEnable(HI_HANDLE hKaraoke, HI_BOOL bEnable);

/**
 \brief Obtains enable/disable status of capture mix frame. CNcomment: 获取音频帧数据 状态 CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke句柄 CNend
 \param[out] pbEnable enable/disable status Karaoke CNcomment:Karaoke时能状态 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
*/

HI_S32   HI_KARAOKE_GetAcquireMixFrameEnable(HI_HANDLE hKaraoke, HI_BOOL* pbEnable);

/**
 \brief get frame info of mix. CNcomment: 获取声音共享帧信息 CNend
 \attention \n
  aac data format define in HI_KARAOKE_MIX_ATTR_S.
 \param[in] hKaraoke      handle of screen share .CNcomment:声音共享句柄 CNend
 \param[out] pstMixFrame        frame info.CNcomment:帧信息 CNend
 \param[in] u32TimeoutMs         acquire timeout.CNcomment:获取超时 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
 */

HI_S32   HI_KARAOKE_AcquireMixFrame(HI_HANDLE hKaraoke, HI_KARAOKE_MIXDATAFRAME_S* pstMixFrame,
                                    HI_U32 u32TimeoutMs);
/**
 \brief release frame info of mix. CNcomment: 释放声音共享帧信息 CNend
 \attention \n
none. CNcomment:无 CNend
 \param[in] hKaraoke     handle of karaoke .CNcomment:声音共享句柄 CNend
 \param[in] pstMixFrame     frame info.CNcomment:帧信息 CNend
 \param[in] u32TimeoutMs    release timeout.CNcomment:释放超时 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
*/

HI_S32   HI_KARAOKE_ReleaseMixFrame(HI_HANDLE hKaraoke, HI_KARAOKE_MIXDATAFRAME_S* pstMixFrame);

/**
 \brief Set audio reverb effect config. CNcomment: 设置音效动态配置 CNend
 \attention \n
none. CNcomment:无 CNend
 \param[in] hKaraoke  audio effect handle .CNcomment:音效句柄 CNend
 \param[in] enCfgRevrbType   config type .CNcomment:配置类型 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
*/
HI_S32   HI_KARAOKE_SetREVERBConfig(HI_HANDLE hKaraoke, HI_KARAOKE_REVERB_TYPE_E enCfgRevrbType);

/**
 \brief Get audio reverb effect config. CNcomment: 获取音效动态配置 CNend
 \attention \n
none. CNcomment:无 CNend
 \param[in] phAef   audio effect handle .CNcomment:音效句柄 CNend
 \param[out] penCfgRevrbType   point of config .CNcomment:配置指针 CNend
 \retval ::HI_SUCCESS CNcomment: success.成功 CNend
 \retval ::HI_FAILURE  Failure  CNcomment:失败 CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:指针参数为空 CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke 设备未打开 CNend
 \see \n
 N/A CNcomment: 无 CNend
*/

HI_S32   HI_KARAOKE_GetREVERBConfig(HI_HANDLE hKaraoke, HI_KARAOKE_REVERB_TYPE_E* penCfgRevrbType);

HI_S32 HI_KARAOKE_SetEnableKde(HI_HANDLE hKaraoke, HI_S32 s32Comp, HI_BOOL bEnable);

/** @} */  /** <!-- ==== API declaration end ==== */

/*returned value section definition according to component*/ /*CNcomment:返回值按组件分段定义*/
            
#define KARAOKE_ERR_BASE                     (0x80001001)           


/*define error number*/ /*CNcomment:相关错误码定义*/
#define HI_ERR_KARAOKE_UNKNOWN                     (KARAOKE_ERR_BASE + 1)  /*unknow error*/ /*CNcomment:未知错误*/
#define HI_ERR_KARAOKE_INVALPARAM                  (KARAOKE_ERR_BASE + 2)  /*invalid parameter*/ /*CNcomment:无效的参数*/
#define HI_ERR_KARAOKE_NULL_PTR                    (KARAOKE_ERR_BASE + 3)  /*NULL pointer*/ /*CNcomment:空指针*/
#define HI_ERR_KARAOKE_NOT_OPEN                    (KARAOKE_ERR_BASE + 4)  /*not open*/ /*CNcomment:未open*/
#define HI_ERR_KARAOKE_BUFFER_EMPTY                (KARAOKE_ERR_BASE + 5)  /*buffer empty*/ /*CNcomment:内存数据为空*/
#define HI_ERR_KARAOKE_NOT_INIT                    (KARAOKE_ERR_BASE + 5)  /*not init*/ /*CNcomment:未初始化*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /*__HI_KARAOKE_H__*/
