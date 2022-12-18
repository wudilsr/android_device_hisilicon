/***********************************************************
 *                      Copyright    , 2009-2014, Hisilicon Tech. Co., Ltd.
 *                                   ALL RIGHTS RESERVED
 * FileName:  download.h
 * Description: Header file of table parse module
 *
 * History:
 * Version   Date          Author         DefectNum      Description
 * main\1    2009-6-30     y00107738      NULL
 ************************************************************/

/**
 * \file
 * \brief USB upgrade UI
 */

#ifndef __DOWNLOAD_H__
#define __DOWNLOAD_H__

/*include header files*/
#include "hi_type.h"
#include "hi_loader_info.h"

/* C++ support */
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus  */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_9 */
/** @{ */  /** <!-- [USB upgrade data structure] */

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_11 */
/** @{ */  /** <!-- [USB upgrade UI] */

/**
 \brief initialize download mode.
 \attention \n
 \param[in] Para:
 \retval ::HI_SUCCESS : get data success
 \retval ::HI_FAILURE : failed to get data
 */

// OTA
HI_S32 LOADER_DOWNLOAD_Init(HI_LOADER_TYPE_E enType, HI_VOID * Para);

/**
 \brief deinitialize download mode.
 \attention \n
 \retval ::HI_SUCCESS : get data success
 \retval ::HI_FAILURE : failed to get data
 */
HI_S32 LOADER_DOWNLOAD_DeInit(HI_VOID);

/**
 \brief Get upgrade data .
 \attention \n
 \param[in] pbuffer: data buffer, allocate by caller
 \param[in] size: the max expected size, it must be samller than the buffer length
 \param[out] outlen: the really length of data
 \retval ::HI_SUCCESS : get data success
 \retval ::HI_FAILURE : failed to get data
 */
HI_S32 LOADER_DOWNLOAD_Getdata(HI_VOID * pbuffer, HI_U32 size, HI_U32 * outlen);

/** @} */  /** <!-- ==== API declaration end ==== */
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif  /* __cplusplus */
#endif /*__DOWNLOAD_H__*/
