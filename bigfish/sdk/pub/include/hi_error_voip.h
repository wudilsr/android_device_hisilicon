/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_error_voip.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/11/24
  Description   : error code of VOIP
  History       :
  1.Date        : 2010/11/24
    Author      : f00172091
    Modification: Created file

******************************************************************************/
/**
\file
\brief provide the common error code for VOIP module
*/
/* add include here */
#ifndef __HI_UNF_VOIP_ERRORCODE_H__
#define __HI_UNF_VOIP_ERRORCODE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/***************************** Macro Definition ******************************/
/** \addtogroup      VOIP_ERROR */
/** @{ */  /** <!--  [VOIP_ERROR] */


#define HI_ERR_VOIP_HME_DEV_NOT_EXIST             (HI_S32)(0x80500001)
#define HI_ERR_VOIP_HME_NOT_DEV_FILE              (HI_S32)(0x80500002)
#define HI_ERR_VOIP_HME_DEV_OPEN_ERR              (HI_S32)(0x80500003)
#define HI_ERR_VOIP_HME_DEV_CLOSE_ERR             (HI_S32)(0x80500004)
#define HI_ERR_VOIP_HME_NULL_PTR                  (HI_S32)(0x80500005)
#define HI_ERR_VOIP_HME_NO_INIT                   (HI_S32)(0x80500006)
#define HI_ERR_VOIP_HME_INVALID_PARA              (HI_S32)(0x80500007)
#define HI_ERR_VOIP_HME_CREATE_ERR                (HI_S32)(0x80500008)
#define HI_ERR_VOIP_HME_DESTROY_ERR               (HI_S32)(0x80500009)
#define HI_ERR_VOIP_HME_NOT_EXIST                 (HI_S32)(0x8050000A)
#define HI_ERR_VOIP_HME_INVALID_OPT               (HI_S32)(0x8050000B)

#define HI_ERR_VOIP_HME_UNKNOWN                   (HI_S32)(0x8050000C)
#define HI_ERR_VOIP_HME_INVALCHANNELID            (HI_S32)(0x8050000D)
#define HI_ERR_VOIP_HME_INVALNETPORT              (HI_S32)(0x8050000E)
#define HI_ERR_VOIP_HME_NOT_IMPLEMENTED           (HI_S32)(0x8050000F)
#define HI_ERR_VOIP_HME_NOT_SUPPORTED             (HI_S32)(0x80500010)
#define HI_ERR_VOIP_HME_LOG_INIT                  (HI_S32)(0x80500011)
#define HI_ERR_VOIP_HME_STARTUP_FAIL              (HI_S32)(0x80500012)
#define HI_ERR_VOIP_HME_DELETE_FAIL               (HI_S32)(0x80500013)

/** @} */  /*! <!-- Macro Definition end */



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* End of #ifndef __HI_UNF_VOIP_ERRORCODE_H__ */

