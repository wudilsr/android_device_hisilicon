/*******************************************************************************
 *              Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: jpg_handle.h
 * Description: 
 *
 * History:
 * Version   Date             Author    DefectNum    Description
 * main\1    2008-04-07       d37024    HI_NULL      Create this file.
 ******************************************************************************/
#ifndef _JPG_HANDLE_H_
#define _JPG_HANDLE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */

/*****************************************************************************/
/*                                   */
/*****************************************************************************/

/******************************************************************************
* Function:      JPG_HandleAlloc
* Description:   
* Input:         pInstance 
* Output:        pHandle   
* Return:        HI_SUCCESS:          
*                HI_ERR_JPG_NO_MEM:   
*                HI_FAILURE:             
* Others:        
******************************************************************************/
HI_S32 JPG_Handle_Alloc(JPG_HANDLE *pHandle, HI_VOID *pInstance);

/******************************************************************************
* Function:      JPG_HandleFree
* Description:   
* Input:         Handle    
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_VOID JPG_Handle_Free(JPG_HANDLE Handle);

/******************************************************************************
* Function:      JPG_HandleGetInstance
* Description:   
* Input:             
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_VOID* JPG_Handle_GetInstance(JPG_HANDLE Handle);
HI_VOID JPG_Handle_Clear(HI_VOID);
#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */


#endif /*_JPG_HANDLE_H_*/

