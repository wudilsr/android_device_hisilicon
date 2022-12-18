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
 * \brief Describes the information about karaoke module. CNcomment:�ṩkaraoke�������Ϣ CNend
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
/** @{ */  /** <!--  ��KARAOKE�� */

/**karaoke attribute */
/**CNcomment:����OK����*/
typedef struct hiHI_KARAOKE_ATTR_S
{
    HI_CHAR acMicDevName[HI_KARAOKE_ALSA_NAME_MAX];/**<Input, description information about micphone device name. */
    HI_U32         u32MicDevNum; /**<IN the number of Mic dev*/ /**<CNcomment:��˷���Ŀ*/
    HI_U32         u32BitPerSample; /**<IN bitwidth per sample.*/ /**<CNcomment:λ��*/
    HI_U32         u32DesiredSampleRate; /**<IN desired samplerate.*//**<CNcomment:����������*/
    HI_BOOL        bMicDataCaptureEnable;/**<IN Enable or Disable Capture Mic Data.*/ /**<CNcomment:������ֹͣ��ȡ��˷�����*/
    HI_BOOL        bMixDataCaptureEnable;/**<IN Enable or Disable Capture Mix Data.*/ /**<CNcomment:������ֹͣ��ȡ����������*/
} HI_KARAOKE_ATTR_S;

/**Defines  karaoke mix frame attribute */
/**CNcomment:���忨��OK������֡��������*/
typedef struct hiHI_KARAOKE_MIXDATAFRAME_S
{
    HI_UNF_ES_BUF_S stMixBufStream;   /** Es Bitstream: aac: ADTS Frame */

} HI_KARAOKE_MIXDATAFRAME_S;

/**Defines  karaoke mix attribute */
/**CNcomment:���忨��OK��������*/
typedef struct hiHI_KRAOKE_MIX_ATTR_S
{
    HI_S32          s32SampleRate;    /**< audio file sample rate */
    HI_S32          s32BitRate;       /**< encoder bit rate in bits/sec */
    HI_S16          s16ChannelsIn;    /**< number of channels on input (1,2) */
    HI_S16          s16ChannelsOut;  /**< number of channels on output (1,2) */
} HI_KARAOKE_MIX_ATTR_S;


/**Defines  Audio revervb type */
/**CNcomment:������Ч����ģʽ*/
typedef enum hiHI_KARAOKE_REVERB_TYPE_E
{
    HI_KARAOKE_REVERB_TYPE_NULL = 0,
    HI_KARAOKE_REVERB_TYPE_KTV,           /**<KTV Mode*/ /**<CNcomment:KTVģʽ*/
    HI_KARAOKE_REVERB_TYPE_THEATRE,       /**<theatre Mode*/ /**<CNcomment:�糡ģʽ*/
    HI_KARAOKE_REVERB_TYPE_HALL,          /**<hall Mode*/ /**<CNcomment:����ģʽ*/
    HI_KARAOKE_REVERB_TYPE_CONCERT,       /**<concert Mode*/ /**<CNcomment:�ݳ���ģʽ*/
    HI_KARAOKE_REVERB_TYPE_VALLEY,        /**<valley Mode*/ /**<CNcomment:ɽ��ģʽ*/
    HI_KARAOKE_REVERB_TYPE_BUTT
} HI_KARAOKE_REVERB_TYPE_E;

/**
 \brief Destory Karaoke Handle CNcomment:���ٴ�������OK��� CNend
 \attention \n
 \param[in] hKaraoke   The handle of the destory Karaoke CNcomment:ָ�����ͣ����ٵ�Karaoke ��� CNend
N/A
 */
HI_VOID   HI_KARAOKE_DeInit(HI_HANDLE hKaraoke);

/**
 \brief Create Karaoke Handle CNcomment:��������OK��� CNend
 \attention \n
 \param[out] phKaraoke   Pointer to the handle of the created Karaoke CNcomment:ָ�����ͣ�������Karaoke ��� CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \see \n
N/A
 */
HI_S32   HI_KARAOKE_Init(HI_HANDLE* phKaraoke);

/**
 \brief Obtains the default configured parameters of Karaoke. CNcomment:��ȡKARAOKEĬ�����ò��� CNend
 \attention \n
 \param[out] pstAttr     Audio attributes CNcomment:��Ƶ���� CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR  The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \see \n
N/A
 */
HI_S32   HI_KARAOKE_GetDefaultKaraokeAttr(HI_KARAOKE_ATTR_S*  pstAttr);

/**
 \brief Create Karaoke CNcomment:��������OK CNend
 \attention \n
 \param[in] enSound     ID of an AO device CNcomment:��Ƶ����豸�� CNend
 \param[in] pKaraokeAttr Karaoke attributes CNcomment:ָ�����ͣ�Karaoke ���� CNend
 \param[out] phKaraoke   Pointer to the handle of the created Karaoke CNcomment:ָ�����ͣ�������Karaoke ��� CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \see \n
N/A
 */
HI_S32   HI_KARAOKE_Create(HI_UNF_SND_E enSound, HI_KARAOKE_ATTR_S*  pKaraokeAttr, HI_HANDLE hKaraoke);

/**
 \brief Destroy Karaoke. CNcomment:����Karaoke CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment:Karaoke ��� CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
N/A
 */
HI_S32   HI_KARAOKE_Destroy(HI_HANDLE hKaraoke);

/**
 \brief enable or Disable Karaoke. CNcomment: ʹ�ܻ���ֹͣKaraokeͨ�� CNend
 \attention \n
 \param[in] hKaraoke  the handle of the Karaoke CNcomment: Karaoke��� CNend
 \param[in] bEnable      enable  .CNcomment:ʹ�ܿ��� CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
N/A CNcomment: �� CNend
*/

HI_S32   HI_KARAOKE_SetEnable(HI_HANDLE hKaraoke, HI_BOOL bEnable);

/**
 \brief Obtains enable/disable status of Karaoke. CNcomment: ��ȡKaraokeͨ��ʱ��״̬ CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke��� CNend
 \param[out] pbEnable enable/disable status Karaoke CNcomment:Karaokeʱ��״̬ CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */

HI_S32   HI_KARAOKE_GetEnable(HI_HANDLE hKaraoke, HI_BOOL* pbEnable);

/**
 \brief Sets the L/R channel weight of karaoke. CNcomment:���ÿ���OK��������Ȩ�� CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke��� CNend
 \param[in] pstMicWeightGain   the channel Weight Gain CNcomment:Ȩ�� CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */

HI_S32   HI_KARAOKE_SetMicWeight(HI_HANDLE hKaraoke, const HI_UNF_SND_ABSGAIN_ATTR_S* pstMicWeightGain);

/**
 \brief Obtains the L/R channel weight of karaoke. CNcomment:��ȡ����OK��������Ȩ�� CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke��� CNend
 \param[in] pstMicWeightGain     Pointer to the ChannelWeight Gain CNcomment:ָ�����ͣ�Ȩ������ CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */

HI_S32   HI_KARAOKE_GetMicWeight(HI_HANDLE hKaraoke, HI_UNF_SND_ABSGAIN_ATTR_S* pstMicWeightGain);

/**
 \brief Sets mute or unmute of karaoke. CNcomment:���ÿ���OK�������� CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke��� CNend
 \param[in] bMute    mute or not CNcomment:������� CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */


HI_S32   HI_KARAOKE_SetMute(HI_HANDLE hKaraoke, HI_BOOL bMute);

/**
 \brief Gets mute status of karaoke. CNcomment:��ȡ����OK�ľ���״̬ CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke��� CNend
 \param[out] pbMute               mute status CNcomment:����״̬ CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */

HI_S32   HI_KARAOKE_GetMute(HI_HANDLE hKaraoke, HI_BOOL* pbMute);

/**
 \brief set the attribute of karaoke, reversed. CNcomment:���ÿ���OK���ԣ� Ԥ�� CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke��� CNend
 \param[in] pstKaraokeAttr   the attribute of the karaoke CNcomment:����OK ���� CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */


HI_S32   HI_KARAOKE_SetAttr(HI_HANDLE hKaraoke, const HI_KARAOKE_ATTR_S*  pstKaraokeAttr);

/**
 \brief get the attribute of  a karaoke, reversed. CNcomment:��ȡ����OK�����ԣ� Ԥ�� CNend
 \attention \n
 \param[in] hKaraoke   the handle of the Karaoke CNcomment:Karaoke ��� CNend
 \param[out] pstTrackAttr   the attribute of the Karaoke CNcomment:Karaoke ���� CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */

HI_S32   HI_KARAOKE_GetAttr(HI_HANDLE hKaraoke, HI_KARAOKE_ATTR_S*  pstTrackAttr);


/**
 \brief enable or Disable capture mic frame. CNcomment: ʹ�ܻ���ֹͣ��ȡ��˷����� CNend
 \attention \n
 \param[in] hKaraoke   the handle of the Karaoke CNcomment:Karaoke ��� CNend
 \param[in] bEnable      enable  .CNcomment:ʹ�ܿ��� CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */

HI_S32   HI_KARAOKE_SetAcquireMicFrameEnable(HI_HANDLE hKaraoke, HI_BOOL bEnable);

/**
 \brief Obtains enable/disable status of capture mic frame. CNcomment: ��ȡKaraoke��ȡ��˷����� ״̬ CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke��� CNend
 \param[out] pbEnable enable/disable status Karaoke CNcomment:Karaokeʱ��״̬ CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */
HI_S32   HI_KARAOKE_GetAcquireMicFrameEnable(HI_HANDLE hKaraoke, HI_BOOL* pbEnable);

/**
 \brief Acquire the audio frame from mic. CNcomment:��ȡ��˷����Ƶ֡ CNend
 \attention \n
 \param[in] hKaraoke   the handle of the Track CNcomment:Track ��� CNend
 \param[in] u32TimeoutMs         acquire timeout.CNcomment:��ȡ��ʱ CNend
 \param[out] pstAOFrame the audio frame  CNcomment:Track ��Ƶ֡ CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */


HI_S32   HI_KARAOKE_AcquireMicFrame(HI_HANDLE hKaraoke, HI_UNF_AO_FRAMEINFO_S* pstAOFrame, HI_U32 u32TimeoutMs);

/**
 \brief Release the audio frame . CNcomment:�ͷ���˷� ��Ƶ֡ CNend
 \attention \n
 \param[in] hKaraoke   the handle of the Track CNcomment:Track ��� CNend
 \param[in] pstAOFrame the audio frame  CNcomment:Track ��Ƶ֡ CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
*/

HI_S32   HI_KARAOKE_ReleaseMicFrame(HI_HANDLE hKaraoke, HI_UNF_AO_FRAMEINFO_S* pstAOFrame);

/**
\brief set the attribute of MixFrame, reversed. CNcomment:������������֡��Ϣ���ԣ� Ԥ�� CNend
\attention \n
\param[in] hKaraoke the handle of the Track CNcomment:hKaraoke ��� CNend
\param[in] pstAencAttr the attribute of the MixFrame CNcomment:hKaraoke ���� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_KARAOKE_INVALPARAM        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_KARAOKE_NULL_PTR            The pointer is null. CNcomment:ָ��Ϊ�� CNend
\see \n
N/A
*/
HI_S32   HI_KARAOKE_SetMixFrameAttr(HI_HANDLE hKaraoke, HI_KARAOKE_MIX_ATTR_S* pstMixAttr);

/**
 \brief enable or Disable capture mix frame. CNcomment: ʹ�ܻ���ֹͣ��ȡ����������� CNend
 \attention \n
 \param[in] hKaraoke   the handle of the Karaoke Ncomment:Karaoke ��� CNend
 \param[in] bEnable      enable  .CNcomment:ʹ�ܿ��� CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */

HI_S32   HI_KARAOKE_SetAcquireMixFrameEnable(HI_HANDLE hKaraoke, HI_BOOL bEnable);

/**
 \brief Obtains enable/disable status of capture mix frame. CNcomment: ��ȡ��Ƶ֡���� ״̬ CNend
 \attention \n
 \param[in] hKaraoke the handle of the Karaoke CNcomment: Karaoke��� CNend
 \param[out] pbEnable enable/disable status Karaoke CNcomment:Karaokeʱ��״̬ CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
*/

HI_S32   HI_KARAOKE_GetAcquireMixFrameEnable(HI_HANDLE hKaraoke, HI_BOOL* pbEnable);

/**
 \brief get frame info of mix. CNcomment: ��ȡ��������֡��Ϣ CNend
 \attention \n
  aac data format define in HI_KARAOKE_MIX_ATTR_S.
 \param[in] hKaraoke      handle of screen share .CNcomment:���������� CNend
 \param[out] pstMixFrame        frame info.CNcomment:֡��Ϣ CNend
 \param[in] u32TimeoutMs         acquire timeout.CNcomment:��ȡ��ʱ CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
 */

HI_S32   HI_KARAOKE_AcquireMixFrame(HI_HANDLE hKaraoke, HI_KARAOKE_MIXDATAFRAME_S* pstMixFrame,
                                    HI_U32 u32TimeoutMs);
/**
 \brief release frame info of mix. CNcomment: �ͷ���������֡��Ϣ CNend
 \attention \n
none. CNcomment:�� CNend
 \param[in] hKaraoke     handle of karaoke .CNcomment:���������� CNend
 \param[in] pstMixFrame     frame info.CNcomment:֡��Ϣ CNend
 \param[in] u32TimeoutMs    release timeout.CNcomment:�ͷų�ʱ CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
*/

HI_S32   HI_KARAOKE_ReleaseMixFrame(HI_HANDLE hKaraoke, HI_KARAOKE_MIXDATAFRAME_S* pstMixFrame);

/**
 \brief Set audio reverb effect config. CNcomment: ������Ч��̬���� CNend
 \attention \n
none. CNcomment:�� CNend
 \param[in] hKaraoke  audio effect handle .CNcomment:��Ч��� CNend
 \param[in] enCfgRevrbType   config type .CNcomment:�������� CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
*/
HI_S32   HI_KARAOKE_SetREVERBConfig(HI_HANDLE hKaraoke, HI_KARAOKE_REVERB_TYPE_E enCfgRevrbType);

/**
 \brief Get audio reverb effect config. CNcomment: ��ȡ��Ч��̬���� CNend
 \attention \n
none. CNcomment:�� CNend
 \param[in] phAef   audio effect handle .CNcomment:��Ч��� CNend
 \param[out] penCfgRevrbType   point of config .CNcomment:����ָ�� CNend
 \retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_KARAOKE_NULL_PTR   The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \retval ::HI_ERR_KARAOKE_NOT_OPEN    Sound device is not opened. CNcomment:Karaoke �豸δ�� CNend
 \see \n
 N/A CNcomment: �� CNend
*/

HI_S32   HI_KARAOKE_GetREVERBConfig(HI_HANDLE hKaraoke, HI_KARAOKE_REVERB_TYPE_E* penCfgRevrbType);

HI_S32 HI_KARAOKE_SetEnableKde(HI_HANDLE hKaraoke, HI_S32 s32Comp, HI_BOOL bEnable);

/** @} */  /** <!-- ==== API declaration end ==== */

/*returned value section definition according to component*/ /*CNcomment:����ֵ������ֶζ���*/
            
#define KARAOKE_ERR_BASE                     (0x80001001)           


/*define error number*/ /*CNcomment:��ش����붨��*/
#define HI_ERR_KARAOKE_UNKNOWN                     (KARAOKE_ERR_BASE + 1)  /*unknow error*/ /*CNcomment:δ֪����*/
#define HI_ERR_KARAOKE_INVALPARAM                  (KARAOKE_ERR_BASE + 2)  /*invalid parameter*/ /*CNcomment:��Ч�Ĳ���*/
#define HI_ERR_KARAOKE_NULL_PTR                    (KARAOKE_ERR_BASE + 3)  /*NULL pointer*/ /*CNcomment:��ָ��*/
#define HI_ERR_KARAOKE_NOT_OPEN                    (KARAOKE_ERR_BASE + 4)  /*not open*/ /*CNcomment:δopen*/
#define HI_ERR_KARAOKE_BUFFER_EMPTY                (KARAOKE_ERR_BASE + 5)  /*buffer empty*/ /*CNcomment:�ڴ�����Ϊ��*/
#define HI_ERR_KARAOKE_NOT_INIT                    (KARAOKE_ERR_BASE + 5)  /*not init*/ /*CNcomment:δ��ʼ��*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /*__HI_KARAOKE_H__*/
