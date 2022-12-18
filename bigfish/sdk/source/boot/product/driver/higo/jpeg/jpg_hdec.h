/***********************************************************************************
 *             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: jpg_hal.h
 * Description: JPEGhal
 *
 * History:
 * Version   Date             Author     DefectNum    Description
 * main\1    2008-03-27       d37024                  Create this file.
 ***********************************************************************************/

#ifndef  _JPG_HAL_H_
#define  _JPG_HAL_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */

/*******************************************************************************
 * Function:        JPGHDEC_CreateInstance
 * Description:     JPEG
 * Data Accessed:
 * Data Updated:
 * Input:           u32FileLen 
 * Output:          
 * Return:          HI_SUCCESS:          
 *                  HI_ERR_JPG_NO_MEM:   
 *                  HI_ERR_JPG_DEC_BUSY: 
 *                  HI_FAILURE:          
 * Others:          
*******************************************************************************/
HI_S32 JPGHDEC_CreateInstance(JPG_HANDLE *pHandle, HI_U32 u32FileLen);

/*******************************************************************************
 * Function:        JPGHDEC_DestroyInstance
 * Description:     JPEG
 * Data Accessed:
 * Data Updated:
 * Input:           
 * Output:          
 * Return:          
 * Others:
*******************************************************************************/
HI_VOID JPGHDEC_DestroyInstance(JPG_HANDLE Handle);

/*******************************************************************************
 * Function:        JPGHDEC_FlushBuf
 * Description:     
 * Data Accessed:
 * Data Updated:
 * Input:           
 * Output:          
 * Return:          
 * Others:
*******************************************************************************/
HI_VOID JPGHDEC_FlushBuf(JPG_HANDLE Handle);

/*******************************************************************************
 * Function:        JPGHDEC_Reset
 * Description:     
 * Data Accessed:
 * Data Updated:
 * Input:           
 * Output:          
 * Return:          
 * Others:
*******************************************************************************/
HI_VOID JPGHDEC_Reset(JPG_HANDLE Handle);

/*******************************************************************************
 * Function:        JPGHDEC_Check
 * Description:     
 * Data Accessed:
 * Data Updated:
 * Input:           pstruCheckInfo 
 * Output:          
 * Return:          HI_SUCCESS    
 *                  HI_FAILURE    
 * Others:
*******************************************************************************/
HI_S32 JPGHDEC_Check(JPG_HANDLE Handle, const JPGDEC_CHECKINFO_S *pCheckInfo);

/*******************************************************************************
 * Function:        JPGHDEC_SetDecodeInfo
 * Description:     
 * Data Accessed:
 * Data Updated:
 * Input:           pstruDecodeAttr 
 * Output:          
 * Return:          
 * Others:
*******************************************************************************/
HI_S32 JPGHDEC_SetDecodeInfo(JPG_HANDLE Handle,
                                         JPGDEC_DECODEATTR_S *pstruDecodeAttr);

/*******************************************************************************
 * Function:        JPGHDEC_SendStream
 * Description:     
 * Data Accessed:
 * Data Updated:
 * Input:           pstruStreamInfo 
 * Output:          
 * Return:          
 * Others:
*******************************************************************************/
HI_VOID JPGHDEC_SendStream(JPG_HANDLE Handle, JPGDEC_WRITESTREAM_S* pStreamInfo);

/*******************************************************************************
 * Function:        JPGHDEC_Start
 * Description:     
 * Data Accessed:
 * Data Updated:
 * Input:           
 * Output:          
 * Return:          HI_SUCCESS   
 *
 * Others:
*******************************************************************************/
HI_S32 JPGHDEC_Start(JPG_HANDLE Handle);


/*******************************************************************************
 * Function:        JPGHDEC_GetDecodeInfo
 * Description:     
 * Data Accessed:
 * Data Updated:
 * Input:           TimeOut      
 * Output:          pDecodeState 
 *                  pSize        
 * Return:          
 * Others:
*******************************************************************************/
HI_VOID JPGHDEC_GetDecodeInfo(JPGDEC_DECODESTATE_E *pDecodeState,
                              HI_U32 *pSize,
                              HI_U32 TimeOut);

/******************************************************************************
* Function:      JPGHDEC_Status

******************************************************************************/
HI_S32  JPGHDEC_Status(JPG_HANDLE Handle, HI_VOID **pBuf, HI_U32 *pBufLen,
                       JPG_HDSTATE_E* pHdState);

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#endif /* _JPG_HAL_H_*/



