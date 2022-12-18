/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : advca_priv.h
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/
#ifndef __ADVCA_PRIV_H__
#define __ADVCA_PRIV_H__

#include "hi_unf_advca.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

#define CMD_CA_SETMARKETID                      _IOW(HI_ID_CA, 0x06, HI_U32)
#define CMD_CA_GETMARKETID                      _IOR(HI_ID_CA, 0x07, HI_U32)
#define CMD_CA_SETSTBSN                         _IOW(HI_ID_CA, 0x0A, HI_U32)
#define CMD_CA_GETSTBSN                         _IOR(HI_ID_CA, 0x0B, HI_U32)
#define CMD_CA_DISABLESELFBOOT                  _IO(HI_ID_CA, 0x18)

#define CMD_CA_SETBOOTMODE                      _IOW(HI_ID_CA, 0x36, HI_UNF_ADVCA_FLASH_TYPE_E)
#define CMD_CA_GETBOOTMODE                      _IOR(HI_ID_CA, 0x37, HI_UNF_ADVCA_FLASH_TYPE_E)
#define CMD_CA_SETSCSACTIVE                     _IO(HI_ID_CA, 0x3C)
#define CMD_CA_GETSCSACTIVE                     _IOR(HI_ID_CA, 0x3D, HI_U32)
#define CMD_CA_SETJTAGPRTMODE                   _IOW(HI_ID_CA, 0x3E, HI_UNF_ADVCA_JTAG_MODE_E)
#define CMD_CA_GETJTAGPRTMODE                   _IOR(HI_ID_CA, 0x3F, HI_UNF_ADVCA_JTAG_MODE_E)

#define CMD_CA_GET_SELFBOOT                     _IOR(HI_ID_CA, 0x77, HI_U32)

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __ADVCA_PRIV_H__ */
