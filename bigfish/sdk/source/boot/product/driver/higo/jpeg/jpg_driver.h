/***********************************************************************************
 *             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: jpg_driver.h
 * Description: JPEG����������ͷ�ļ�
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
 * Description:     �ͷ�JPGӲ�������豸
 * Data Accessed:   
 * Data Updated:  
 * Input:           ��
 * Output:          ��
 * Return:          HI_SUCCESS             �ɹ�
 *                  HI_ERR_JPG_DEV_NOOPEN  �豸δ����
 *                  HI_FAILURE             ϵͳ����
 * Others:       
*******************************************************************************/
HI_S32 JPGDRV_ReleaseDevice(HI_VOID);

/*******************************************************************************
 * Function:        JPGDRV_GetRegisterAddr
 * Description:     ��ȡ�Ĵ����û�̬��ַ
 * Data Accessed:   
 * Data Updated:  
 * Input:           ��
 * Output:          pRegPtr �Ĵ���ӳ�䵽�û�̬�ĵ�ַָ��
 * Return:          HI_SUCCESS             �ɹ�
 *                  HI_ERR_JPG_DEV_NOOPEN  �豸δ����
 *                  HI_FAILURE             ϵͳ����
 * Others:       
*******************************************************************************/
HI_VOID JPGDRV_GetRegisterAddr(HI_VOID **pRegPtr, HI_VOID **pRstRegPtr, HI_VOID **pVhbRegPtr);

/*******************************************************************************
 * Function:        JPGDRV_GetIntStatus
 * Description:     ��ȡ�ж�״̬
 * Data Accessed:   
 * Data Updated:  
 * Input:           TimeOut       ��ʱֵ
 * Output:          pu32IntStatus �ж�״̬
 * Return:          HI_SUCCESS             �ɹ�
 *                  HI_ERR_JPG_DEV_NOOPEN  �豸δ����
 *                  HI_ERR_JPG_TIME_OUT    ��ʱ����
 *                  HI_FAILURE             ϵͳ����
 * Others:       
*******************************************************************************/
HI_VOID JPGDRV_GetIntStatus(JPG_INTTYPE_E *pIntType, HI_U32 TimeOut);

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#endif /* _JPG_DRIVER_H_*/



