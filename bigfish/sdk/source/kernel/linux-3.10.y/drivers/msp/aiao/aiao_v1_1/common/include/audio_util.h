/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : audio_util.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/02/28
  Description   :
  History       :
  1.Date        : 2013/02/28
    Author      : zgjie
    Modification: Created file

 *******************************************************************************/

#ifndef __DSP_UTIL__H__
#define __DSP_UTIL__H__

#include "hi_type.h"
#include "hi_drv_ao.h"
#include "hi_drv_ai.h"
#include "drv_ao_private.h"
#include "hal_aiao_common.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C"
{
 #endif
#endif
#define VOLUME_6dB (0x7f)
#define VOLUME_0dB (0x79)
#define VOLUME_infdB (0x28)
#define VOLUME_MAX_dB (AOE_AIP_VOL_6dB)
#define VOLUME_MIN_dB (AOE_AIP_VOL_infdB)

#define IEC61937_DATATYPE_NULL 0
#define IEC61937_DATATYPE_DOLBY_DIGITAL 1     /* AC3 */
#define IEC61937_DATATYPE_DTS_TYPE_I 11   /* DTS Type 1 */
#define IEC61937_DATATYPE_DTS_TYPE_II 12   /* DTS Type 2 */
#define IEC61937_DATATYPE_DTS_TYPE_III 13   /* DTS Type 3 */
#define IEC61937_DATATYPE_DTS_TYPE_IV 17   /* DTS Type 4 */
#define IEC61937_DATATYPE_DOLBY_DIGITAL_PLUS 21   /* AC3 */
#define IEC61937_DATATYPE_DOLBY_TRUE_HD 22   /* True HD */

#define IEC61937_DATATYPE_71_LPCM 0xf0
#define IEC61937_DATATYPE_20_LPCM 0xf1

#define IEC61937_DATATYPE_DTSCD 0xff         /* DTS CD */
#define IEC61937_DATATYPE_DOLBY_SIMUL 0xfe

////Define IC PLATFORM/////
typedef enum
{
  AUTIL_CHIP_PLATFORM_S40,
  AUTIL_CHIP_TYPE_PLATFORM_S5,
  AUTIL_CHIP_TYPE_PLATFORM_BUTT,
} AUTIL_CHIP_PLATFORM_E;

HI_U32          AUTIL_IEC61937DataType(HI_U16* pu16IecData, HI_U32 u32IecDataSize);
HI_S32          AUTIL_isIEC61937Hbr(HI_U32 u32IEC61937DataType, HI_U32 uSourceRate);
HI_U32          AUTIL_CalcFrameSize(HI_U32 u32Ch, HI_U32 u32BitDepth);
HI_U32          AUTIL_LatencyMs2ByteSize(HI_U32 u32LatencyMs, HI_U32 u32FrameSize, HI_U32 u32SampleRate);
HI_U32          AUTIL_ByteSize2LatencyMs(HI_U32 u32DataBytes, HI_U32 u32FrameSize, HI_U32 u32SampleRate);
HI_U32          AUTIL_VolumeLinear2RegdB(HI_U32 u32Linear);
HI_U32          AUTIL_VolumedB2RegdB(HI_S32 dBVol);
HI_S32          AUTIL_SetBitZeroOrOne(HI_U32* pu32Val, HI_U32 u32Bit, HI_U32 u32ZeroOrOne);
HI_U32          AUTIL_BclkFclkDiv(HI_UNF_I2S_MCLK_SEL_E enMclkSel, HI_UNF_I2S_BCLK_SEL_E enBclkSel);
HI_U32          AUTIL_MclkFclkDiv(HI_UNF_I2S_MCLK_SEL_E enMclkSel);

const HI_CHAR * AUTIL_Port2Name(HI_UNF_SND_OUTPUTPORT_E enPort);
const HI_UNF_SND_OUTPUTPORT_E AUTIL_PortName2Port(HI_CHAR *pcName);
const HI_CHAR * AUTIL_AiPort2Name(HI_UNF_AI_E enAiPort);
const HI_CHAR * AUTIL_TrackMode2Name(HI_UNF_TRACK_MODE_E enMode);
const AIAO_TRACK_MODE_E AUTIL_TrackModeTransform(HI_UNF_TRACK_MODE_E enMode);
const HI_CHAR * AUTIL_HdmiMode2Name(HI_UNF_SND_HDMI_MODE_E enMode);
const HI_CHAR * AUTIL_SpdifMode2Name(HI_UNF_SND_SPDIF_MODE_E enMode);
const HI_CHAR *AUTIL_Track2Name(HI_UNF_SND_TRACK_TYPE_E     enTrackType);
const HI_CHAR * AUTIL_Engine2Name(SND_ENGINE_TYPE_E enEngine);
const HI_CHAR * AUTIL_Format2Name(HI_U32 u32Format);
const HI_CHAR * AUTIL_CategoryCode2Name(HI_UNF_SND_SPDIF_CATEGORYCODE_E enCategory);
const HI_CHAR * AUTIL_ScmsMode2Name(HI_UNF_SND_SPDIF_SCMSMODE_E enScms);

HI_VOID         AUTIL_OS_GetTime(HI_U32* t_ms);
AIAO_I2S_CHNUM_E AUTIL_CHNUM_UNF2AIAO(HI_UNF_I2S_CHNUM_E enChannel);
AIAO_BITDEPTH_E AUTIL_BITDEPTH_UNF2AIAO(HI_UNF_I2S_BITDEPTH_E enBitDepth);
AIAO_I2S_MODE_E AUTIL_I2S_MODE_UNF2AIAO(HI_UNF_I2S_MODE_E enI2sMode);
HI_VOID*        AUTIL_AO_MALLOC(HI_U32 u32ModuleID, HI_U32 u32Size, HI_S32 flag);
HI_VOID         AUTIL_AO_FREE(HI_U32 u32ModuleID, HI_VOID* pMemAddr);
HI_VOID*        AUTIL_AIAO_MALLOC(HI_U32 u32ModuleID, HI_U32 u32Size, HI_S32 flag);
HI_VOID         AUTIL_AIAO_FREE(HI_U32 u32ModuleID, HI_VOID* pMemAddr);

AUTIL_CHIP_PLATFORM_E  AUTIL_GetChipPlatform(HI_VOID);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif
