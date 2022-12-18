/******************************************************************************
                              Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : test_loader.h
Version       : Initial Draft
Author        : Hisilicon multimedia Hardware group l50549
Created       : 2007/08/20
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __OTA_COMMON_H__
#define __OTA_COMMON_H__

#include "hi_loader_info.h"
#include "hi_unf_demux.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of__cplusplus */

#define FILTERDEPTH 12

/*QAM modulation mode */
typedef enum hiCABLE_MOD_E
{
    QAM16  = 0x00,      //16QAM
    QAM32  = 0x01,      // 32QAM
    QAM64  = 0x02,      // 64QAM
    QAM128 = 0x03,      // 128QAM
    QAM256 = 0x04       //256QAM
} CABLE_MOD_E;

typedef struct DBTunerSwitch16_S
{
    HI_U32 u32Level;          /**<DiSEqC device level*/
    HI_U32 u32Port;           /**<DiSEqC switch port*/
} DB_TUNER_SWITCH16_S;

typedef struct DBTunerSwitch4_S
{
    HI_U32 u32Level;  /**<DiSEqC device level*/
    HI_U32 u32Port;   /**<DiSEqC switch port*/
    HI_U32 u32Polar;  /**<Polarization type */
    HI_U32 u32LNB22K; /**<22K status*/
} DB_TUNER_SWITCH4_S;

typedef struct hiDOWNLOAD_OTA_PARAMETER_S
{
    HI_U32              u32SignalType; /* signal type*/
    HI_U32              u32Frequency; /* frequency range: 45000KHz ~ 900000KHz */
    HI_U32              u32SymbolRate; /* symbol rate, unit:  KS/s */
    CABLE_MOD_E         enModulation; /* qam size */
    HI_U32              u32Polar; /* Polarization type*/
    HI_U32              u32LowLO; /**< Low Local Oscillator Frequency, MHz */
    HI_U32              u32HighLO;/**< High Local Oscillator Frequency, MHz*/
    HI_U32              u32Switch22K;     /** 22KHz switch */
    HI_U32              u32Switch0_12V;   /** 0/12V switch */
    HI_U32              u32ToneBurst;     /* Tone burst switch*/
    DB_TUNER_SWITCH16_S stSwitch16;
    DB_TUNER_SWITCH4_S  stSwitch4;
    HI_U16              u16TsPID; /* download ts pid  */
    HI_U8               u8TableID;/* download talbe id */
    HI_U8               ota_type; /* download type */
    HI_U16              u16Reserved; /* reserved for future use */
    HI_VOID*            pReserved;  /*  reserved for future use  */
} DOWNLOAD_OTA_PARAMETER_S;

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_1*/
/** @{ */  /** <!?a[Forced upgrade data structure] */

/**Definition of button types for infrared response*/

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_1 */
/** @{ */  /** <! [Forced upgrade API] */

// OTA
HI_S32	LOADER_GetTunerAttr(HI_UNF_TUNER_ATTR_S *pstTunerAttr);

#ifdef HI_LOADER_TUNER_SAT
HI_S32	LOADER_GetSatAttr(HI_UNF_TUNER_SAT_ATTR_S *pstSatAttr);
#endif

HI_S32 LOADER_DOWNLOAD_OTA_Init(HI_VOID * Para);

/**
 \brief deinitialize OTA download mode.
 \attention \n
 \retval ::HI_SUCCESS : get data success
 \retval ::HI_FAILURE : failed to get data
 */
HI_S32 LOADER_DOWNLOAD_OTA_DeInit(HI_VOID);

/**
 \brief Get upgrade data through OTA, usually section data.
 \attention \n
 \param[in] pbuffer: data buffer, allocate by caller
 \param[in] size: the max expected size, it must be samller than the buffer length
 \param[out] outlen: the really length of data
 \retval ::HI_SUCCESS : get data success
 \retval ::HI_FAILURE : failed to get data
 */
HI_S32 LOADER_DOWNLOAD_OTA_getdata(HI_VOID * pbuffer, HI_U32 size, HI_U32 * outlen);

/**
 \brief Set fillter attributes to acquire data through OTA.
 \attention \n
 \param[in] u16Pid:
 \param[in] pstFilterAttr: filter attributs
 \retval ::HI_SUCCESS : set fillter success
 \retval ::HI_FAILURE : set fillter failed
 */
HI_S32 LOADER_DOWNLOAD_OTA_setfilter(HI_U16 u16Pid, HI_UNF_DMX_FILTER_ATTR_S *pstFilterAttr);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__OTA_COMMON_H__*/
