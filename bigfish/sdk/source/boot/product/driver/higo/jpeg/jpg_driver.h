/***********************************************************************************
 *             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: jpg_driver.h
 * Description: JPEG解码驱动层头文件
 *
 * History:
 * Version   Date             Author     DefectNum    Description
 * main\1    2008-03-27       d37024                  Create this file.
 ***********************************************************************************/

#ifndef  _JPG_DRIVER_H_
#define  _JPG_DRIVER_H_
#include "jpg_type.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */


/*******************************************************************************
 * Function:        JPGDRV_ReleaseDevice
 * Description:     释放JPG硬件解码设备
 * Data Accessed:   
 * Data Updated:  
 * Input:           无
 * Output:          无
 * Return:          HI_SUCCESS             成功
 *                  HI_ERR_JPG_DEV_NOOPEN  设备未开启
 *                  HI_FAILURE             系统错误
 * Others:       
*******************************************************************************/
HI_S32 JPGDRV_ReleaseDevice(HI_VOID);

/*******************************************************************************
 * Function:        JPGDRV_GetRegisterAddr
 * Description:     获取寄存器用户态地址
 * Data Accessed:   
 * Data Updated:  
 * Input:           无
 * Output:          pRegPtr 寄存器映射到用户态的地址指针
 * Return:          HI_SUCCESS             成功
 *                  HI_ERR_JPG_DEV_NOOPEN  设备未开启
 *                  HI_FAILURE             系统错误
 * Others:       
*******************************************************************************/
HI_VOID JPGDRV_GetRegisterAddr(HI_VOID **pRegPtr, HI_VOID **pRstRegPtr, HI_VOID **pVhbRegPtr);

/*******************************************************************************
 * Function:        JPGDRV_GetIntStatus
 * Description:     获取中断状态
 * Data Accessed:   
 * Data Updated:  
 * Input:           TimeOut       超时值
 * Output:          pu32IntStatus 中断状态
 * Return:          HI_SUCCESS             成功
 *                  HI_ERR_JPG_DEV_NOOPEN  设备未开启
 *                  HI_ERR_JPG_TIME_OUT    超时错误
 *                  HI_FAILURE             系统错误
 * Others:       
*******************************************************************************/
HI_VOID JPGDRV_GetIntStatus(JPG_INTTYPE_E *pIntType, HI_U32 TimeOut);

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#endif /* _JPG_DRIVER_H_*/



