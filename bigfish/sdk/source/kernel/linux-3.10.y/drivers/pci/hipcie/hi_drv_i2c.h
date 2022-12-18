/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : priv_i2c.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2007/01/23
  Description   :
  History       :
  1.Date        : 2007/01/23
    Author      : j37987
    Modification: Created file

******************************************************************************/

#ifndef __HI_DRV_I2C_H__
#define __HI_DRV_I2C_H__


#define HI_FATAL_I2C(fmt...) \
    printk("I2C_FATAL " fmt)

#define HI_ERR_I2C(fmt...) \
    printk("I2C_ERR " fmt)

#define HI_WARN_I2C(fmt...) \
    printk("I2C_WARN " fmt)

#define HI_INFO_I2C(fmt...) \
    printk("I2C_INFO " fmt)

#define HI_FAILURE -1
#define HI_ERR_I2C_WRITE_TIMEOUT -2
#define HI_ERR_I2C_READ_TIMEOUT -3


#define HI_STD_I2C_NUM 3


//#define HI_I2C_MAX_NUM_USER      15
//#define HI_STD_I2C_MAX_NUM 5
#define HI_I2C_MAX_NUM_RESERVE 1
#define HI_I2C_MAX_NUM (HI_STD_I2C_NUM)

#define HI_I2C_MAX_LENGTH  1024

static int  HI_DRV_I2C_Init(void);
static void HI_DRV_I2C_DeInit(void);

static int HI_DRV_I2C_WriteConfig(unsigned int I2cNum, unsigned char I2cDevAddr);
static int HI_DRV_I2C_Write(unsigned int I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum, unsigned char * pData,
                        unsigned int DataLen);
static int HI_DRV_I2C_Read(unsigned int I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum, unsigned char * pData,
                       unsigned int DataLen);
static int HI_DRV_I2C_ReadDirectly(unsigned int I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum,
                               unsigned char *pData, unsigned int DataLen);
static int HI_DRV_I2C_Write_NoSTOP(unsigned int I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum,
                               unsigned char *pData, unsigned int DataLen);

#endif
