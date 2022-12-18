/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_ca_otp_common.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 
  Last Modified :
  Description   : 
  Function List :
  History       :
******************************************************************************/

#ifndef __DRV_CA_OTP_COMMON_H__
#define __DRV_CA_OTP_COMMON_H__

typedef enum
{
    CA_OTP_VERSION_100,
    CA_OTP_VERSION_200,
    CA_OTP_VERSION_BUTT
}CA_OTP_VERSION_E;


/** FLASH device types*/
typedef enum
{
    CA_OTP_FLASH_TYPE_SPI = 0,     /**<SPI flash*/
    CA_OTP_FLASH_TYPE_NAND,        /**<nand flash*/
    CA_OTP_FLASH_TYPE_NOR,         /**<nor flash*/
    CA_OTP_FLASH_TYPE_EMMC,        /**<eMMC*/
    CA_OTP_FLASH_TYPE_SPI_NAND,    /**<spi_nand flash*/
    CA_OTP_FLASH_TYPE_SD,          /**<sd flash*/
    CA_OTP_FLASH_TYPE_BUTT
}CA_OTP_FLASH_TYPE_E;

/** JTAG protect mode*/
typedef enum
{
    CA_OTP_JTAG_MODE_OPEN = 0,     
    CA_OTP_JTAG_MODE_PROTECT,       
    CA_OTP_JTAG_MODE_CLOSED,     

    CA_OTP_JTAG_MODE_BUTT
}CA_OTP_JTAG_MODE_E;

/** JTAG protect mode*/
typedef enum
{
    CA_OTP_KEY_LEV1 = 0,
    CA_OTP_KEY_LEV2,
    CA_OTP_KEY_LEV3,
    CA_OTP_KEY_LEV4,
    CA_OTP_KEY_LEV5,
    CA_OTP_KEY_LEV6,
    CA_OTP_KEY_LEV_BUTT
}CA_OTP_KEY_LEVEL_E;

/** CA vendor type*/
typedef enum
{
    CA_OTP_VENDOR_NONE  = 0x0,
    CA_OTP_VENDOR_NAGRA,
    CA_OTP_VENDOR_IRDETO,
    CA_OTP_VENDOR_CONAX,
    CA_OTP_VENDOR_NDS,
    CA_OTP_VENDOR_SUMA,
    CA_OTP_VENDOR_NOVEL,
    CA_OTP_VENDOR_VERIMATRIX,
    CA_OTP_VENDOR_CTI,
    CA_OTP_VENDOR_SAFEVIEW,
    CA_OTP_VERDOR_LATENSE,
    CA_OTP_VERDOR_SH_TELECOM,
    CA_OTP_VERDOR_VIACCESS,
    CA_OTP_VENDOR_BUTT
}CA_OTP_VENDOR_TYPE_E;

#endif  /* __DRV_CA_OTP_COMMON_H__ */

