/*******************************************************************************
 *              Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: hi_jpg_buf.h
 * Description:
 *
 * History:
 * Version   Date             Author    DefectNum    Description
 * main\1    2008-03-27       d37024    HI_NULL      Create this file.
 ******************************************************************************/
#ifndef _JPG_BUF_H_
#define _JPG_BUF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */



typedef struct hiJPGBUF_DATA_S
{
    HI_VOID*   pAddr[2];
    HI_U32     u32Len[2];
} JPGBUF_DATA_S;

typedef struct hiJPG_CYCLEBUF_S
{
    HI_VOID*  pBase;           
    HI_U32    u32BufLen;      
    HI_U32    u32RsvByte;   
    HI_U32    u32RdHead;      
    HI_U32    u32RdTail;        
    HI_U32    u32WrHead;     
} JPG_CYCLEBUF_S;

/*****************************************************************************/
/*                                 JPG interface                                */
/*****************************************************************************/

/******************************************************************************
* Function:      JPGBUF_Init
* Description: 
* Input:         pVirtBase   buf
                 BufLen      Buf
                 u32RsvByte  
* Output:        ppstCB   Buf
* Return:        HI_SUCCESS:        
* Others:        
                 
******************************************************************************/
HI_S32 JPGBUF_Init(JPG_CYCLEBUF_S* pstCB, HI_VOID* pVirtAddr,
                        HI_U32 u32BufLen, HI_U32 u32RsvByte);

/******************************************************************************
* Function:      JPGBUF_Reset
* Description:   
* Input:         pstCB    buffer
* Return:        
* Others:        
******************************************************************************/
HI_VOID  JPGBUF_Reset(JPG_CYCLEBUF_S* pstCB);

/******************************************************************************
* Function:      JPGBUF_Read
* Description:   
* Input:         pstCB    buf
* Output:        pstRdInfo    Buf
* Return:        
* Others:        
******************************************************************************/
HI_S32 JPGBUF_Read(const JPG_CYCLEBUF_S* pstCB, HI_VOID* pData, HI_U32 u32Len);

/******************************************************************************
* Function:      JPGBUF_Write
* Description:   写数据
* Input:         Handle   Buf句柄
*                pRead    读指针
* Output:        无
* Return:        无
* Others:        无
******************************************************************************/
HI_S32 JPGBUF_Write(JPG_CYCLEBUF_S* pstCB, HI_VOID* pVirtSrc, HI_U32 u32WrLen);

/******************************************************************************
* Function:      JPGBUF_StepRdHead
* Description:   
* Input:         Handle   Buf
*                pRead    
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_VOID   JPGBUF_StepRdHead(JPG_CYCLEBUF_S* pstCB);

/******************************************************************************
* Function:      JPGBUF_StepRdTail
* Description:   
* Input:         Handle   Buf
*                pRead    
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_VOID   JPGBUF_StepRdTail(JPG_CYCLEBUF_S* pstCB);

/******************************************************************************
* Function:      JPGBUF_SetRdHead
* Description:   
* Input:         Handle   Buf
*                Len      
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_VOID  JPGBUF_SetRdHead(JPG_CYCLEBUF_S* pstCB, HI_S32 Len);

/******************************************************************************
* Function:      JPGBUF_SetWrHead
* Description:   
* Input:         pstCB        buf
* Output:        Len    
* Return:        
* Others:        
******************************************************************************/
HI_VOID  JPGBUF_SetWrHead(JPG_CYCLEBUF_S* pCB, HI_U32 Len);

/******************************************************************************
* Function:      JPGBUF_GetFreeLen
* Description:   
* Input:         pstCB    buffer
* Output:        buffer
* Return:        
* Others:        
******************************************************************************/
HI_U32 JPGBUF_GetFreeLen(const JPG_CYCLEBUF_S* pstCB);

/******************************************************************************
* Function:      JPGBUF_GetDataBtwRhRt
* Description:  
* Input:          pstCB        buf
* Output:        pRdInfo    
* Return:        
* Others:        
******************************************************************************/
HI_S32   JPGBUF_GetDataBtwRhRt(const JPG_CYCLEBUF_S* pstCB, JPGBUF_DATA_S *pRdInfo);

/******************************************************************************
* Function:      JPGBUF_GetDataBtwWhRh
* Description:   
* Input:         pstCB        buf
* Output:        pstData    
* Return:        
* Others:        
******************************************************************************/
HI_S32 JPGBUF_GetDataBtwWhRh(const JPG_CYCLEBUF_S* pstCB, JPGBUF_DATA_S *pRdInfo);

/******************************************************************************
* Function:      JPGBUF_GetDataBtwWhRt
* Description:   
* Input:         pstCB        buf
* Output:        pstData    
* Return:        
* Others:        
******************************************************************************/
HI_S32 JPGBUF_GetDataBtwWhRt(const JPG_CYCLEBUF_S* pstCB, JPGBUF_DATA_S *pRdInfo);

/******************************************************************************
* Function:      JPGBUF_GetBufInfo
* Description:   buf
* Input:         pstCB      buf
* Output:        pBase      buf
*                pBufLen    buf
* Return:        
* Others:        
******************************************************************************/
HI_S32 JPGBUF_GetBufInfo(const JPG_CYCLEBUF_S* pstCB, 
                         HI_VOID** pBase, HI_U32* pBufLen);

/******************************************************************************
* Function:      JPGBUF_GetFreeLen
* Description:   buffer
* Input:         pstCB    buffer
* Output:        buffer
* Return:        
* Others:        
******************************************************************************/
HI_S32 JPGBUF_GetFreeInfo(const JPG_CYCLEBUF_S* pstCB, 
                          HI_VOID** pFreeBuf, HI_U32* pFreeLen);

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#endif /*_JPG_BUF_H_*/

