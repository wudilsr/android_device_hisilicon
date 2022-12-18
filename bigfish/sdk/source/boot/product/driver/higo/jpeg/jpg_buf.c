/*******************************************************************************
 *              Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: hi_jpg_buf.c
 * Description:
 *
 * History:
 * Version   Date             Author    DefectNum    Description
 * main\1    2008-04-09       z53517    HI_NULL      Create this file.
 ******************************************************************************/

#include "jpg_common.h"
#include "jpg_buf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */

/*
*/
#define JPGBUF_ASSERT(Wh, Rh, Rt, u32BufLen)\
do{\
    assert (   ((Wh >= Rh) && (Rh >= Rt))\
                 ||((Rh  >= Rt)  && (Rt >= Wh))\
                 ||((Rt  >= Wh) && (Wh >= Rh))   );\
    assert(  (Wh >= 0) && (Wh < u32BufLen)\
                    && (Rh >= 0) && (Rh  < u32BufLen)\
                    && (Rt  >= 0) && (Rt  < u32BufLen)  );\
}while(0)

/******************************************************************************
******************************************************************************/
HI_S32 JPGBUF_Init(JPG_CYCLEBUF_S* pstCB, HI_VOID* pVirtAddr,
                        HI_U32 u32BufLen, HI_U32 u32RsvByte)
{
    JPG_ASSERT_NULLPTR(pstCB);
    JPG_ASSERT_NULLPTR(pVirtAddr);
    assert(u32RsvByte > 0);
    assert(u32BufLen > u32RsvByte);

   // BM_TRACE("JPGBUF_init pstCB 0x%x Base 0x%x BufLen 0x%x RsvByte 0x%x\n",pstCB,pVirtAddr,u32BufLen,u32RsvByte);
    pstCB->pBase      = pVirtAddr;
    pstCB->u32BufLen  = u32BufLen;
    pstCB->u32RsvByte = u32RsvByte;

    pstCB->u32RdHead = 0;
    pstCB->u32RdTail = 0;
    pstCB->u32WrHead = 0;

    return HI_SUCCESS;

}


/******************************************************************************
* Function:      JPGBUF_Reset
* Description:   flush BUF
* Input:         pstCB Buf 
* Return:        
* Others:        
******************************************************************************/
HI_VOID  JPGBUF_Reset(JPG_CYCLEBUF_S* pstCB)
{
    JPG_ASSERT_NULLPTR(pstCB);

    pstCB->u32RdHead = 0;
    pstCB->u32RdTail = 0;
    pstCB->u32WrHead = 0;

    return;
}

/******************************************************************************
* Function:      JPGBUF_Read
* Description:   
* Input:         pstCB    buf
                 pVirtDst 
                 u32RdLen 
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_S32   JPGBUF_Read(const JPG_CYCLEBUF_S* pstCB, HI_VOID* pVirtDst, HI_U32 u32RdLen)
{
    JPGBUF_DATA_S stData;
    
    JPG_ASSERT_NULLPTR(pstCB);
    JPG_ASSERT_NULLPTR(pVirtDst);

    assert(u32RdLen >= 2);

    JPGBUF_ASSERT(pstCB->u32WrHead, pstCB->u32RdHead, 
                  pstCB->u32RdTail, pstCB->u32BufLen);

    (HI_VOID)JPGBUF_GetDataBtwWhRh(pstCB, &stData);
    if((stData.u32Len[0] + stData.u32Len[1]) < u32RdLen)
    {
        return HI_FAILURE;
    }
    
    if(u32RdLen > 2)
    {
        if(u32RdLen <= stData.u32Len[0])
        {
            
            VCOS_memcpy(pVirtDst, stData.pAddr[0], u32RdLen);
        }
        else  /*(u32RdLen > stData.u32Len[0])*/
        {
            VCOS_memcpy(pVirtDst, stData.pAddr[0], stData.u32Len[0]);
            VCOS_memcpy((HI_U8*)pVirtDst + stData.u32Len[0],
                        stData.pAddr[1], u32RdLen - stData.u32Len[0]);
        }   
    }
#if 0
	/** deal with codecc **/
    else  /*(u32RdLen == 2) */
    {
        HI_U8*  pu8Src = (HI_U8*)stData.pAddr[0];
        HI_U8*  pu8Dst = (HI_U8*)pVirtDst;
        
        *pu8Dst++  = *pu8Src;       
        if(pu8Src == (HI_U8*)pstCB->pBase + (pstCB->u32BufLen - 1))  
        {
            pu8Src = (HI_U8*)pstCB->pBase;
        }
        else
        {
            pu8Src++;
        }
        
        *pu8Dst = *pu8Src;
    }
#endif
    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPGBUF_Write
* Description:   
* Input:         pstCB    buf
*                pVirtSrc 
                 u32WrLen 
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_S32 JPGBUF_Write(JPG_CYCLEBUF_S* pstCB, HI_VOID* pVirtSrc, HI_U32 u32WrLen)
{
    JPGBUF_DATA_S   stWrInfo;
    HI_U32          freeLen;
    HI_U8*          pu8Addr;
    
    JPG_ASSERT_NULLPTR(pstCB);
    JPG_ASSERT_NULLPTR(pVirtSrc);
    assert(u32WrLen >= 0);
    JPGBUF_ASSERT(pstCB->u32WrHead, pstCB->u32RdHead, 
                  pstCB->u32RdTail, pstCB->u32BufLen);
    
    freeLen = JPGBUF_GetFreeLen(pstCB);
    
    if (freeLen < u32WrLen)
    {
        return HI_FAILURE;
    }
    if ((pstCB->u32WrHead + u32WrLen) >= pstCB->u32BufLen)
    {
        stWrInfo.pAddr[0] = (HI_U8*)pstCB->pBase + pstCB->u32WrHead;
        stWrInfo.u32Len[0] = pstCB->u32BufLen - pstCB->u32WrHead;
        stWrInfo.pAddr[1] = pstCB->pBase;
        stWrInfo.u32Len[1] = u32WrLen - stWrInfo.u32Len[0];
        pstCB->u32WrHead = stWrInfo.u32Len[1];  
    }
    else
    {
        stWrInfo.pAddr[0] = (HI_U8*)pstCB->pBase + pstCB->u32WrHead;
        stWrInfo.u32Len[0] = u32WrLen;
        stWrInfo.pAddr[1] = (HI_U8*)stWrInfo.pAddr[0] + u32WrLen;
        stWrInfo.u32Len[1] = 0;       
        pstCB->u32WrHead += u32WrLen;  
        if (pstCB->u32WrHead >= pstCB->u32BufLen)
        {
            pstCB->u32WrHead = 0;
        }
    }
    pu8Addr = (HI_U8*)pVirtSrc;
#ifdef HI_MINIBOOT_SUPPORT
    mmu_cache_enable();
#else
    dcache_enable(0);
#endif
    //BM_TRACE("write0 addr 0x%x size 0x%x fm Addr 0x%x\n",stWrInfo.pAddr[0],stWrInfo.u32Len[0],pu8Addr);
    VCOS_memcpy((char*)stWrInfo.pAddr[0], (char*)pu8Addr, stWrInfo.u32Len[0]);
    if(0 != stWrInfo.u32Len[1])
    {
        pu8Addr += stWrInfo.u32Len[0];
    //BM_TRACE("write1 addr 0x%x size 0x%x fm Addr 0x%x\n",stWrInfo.pAddr[1],stWrInfo.u32Len[1],pu8Addr);
        VCOS_memcpy(stWrInfo.pAddr[1], pu8Addr, stWrInfo.u32Len[1]);
    } 
#ifdef HI_MINIBOOT_SUPPORT
    mmu_cache_disable();
#else
    dcache_disable();
#endif
    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPGBUF_StepRdHead
* Description:   
* Input:         pstCB    buf
                 u32AlignLen buf
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_VOID   JPGBUF_StepRdHead(JPG_CYCLEBUF_S* pstCB)
{
    JPG_ASSERT_NULLPTR(pstCB);
    
    pstCB->u32RdHead = pstCB->u32WrHead;
    
    return;
}

/******************************************************************************
* Function:      JPGBUF_StepRdTail
* Description:   
* Input:         pstCB    buf
*                pRead    
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_VOID   JPGBUF_StepRdTail(JPG_CYCLEBUF_S* pstCB)
{
    JPG_ASSERT_NULLPTR(pstCB);
    pstCB->u32RdTail = pstCB->u32RdHead;
    
    return;
}

/******************************************************************************
* Function:      JPGBUF_SetRdHead
* Description:   
* Input:         pstCB    buf
*                u32Len   
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_VOID  JPGBUF_SetRdHead(JPG_CYCLEBUF_S* pCB, HI_S32 Len)
{
    HI_S32 s32RdHead;
    JPG_ASSERT_NULLPTR(pCB);

    s32RdHead = (HI_S32)pCB->u32RdHead + Len;
    //pCB->u32RdHead += Len;
    
    if(s32RdHead >= (HI_S32)pCB->u32BufLen)
    {
        s32RdHead -= (HI_S32)pCB->u32BufLen;
    }
    
    if(s32RdHead < 0)
    {
        s32RdHead += (HI_S32)pCB->u32BufLen;
    }
    
    pCB->u32RdHead = (HI_U32)s32RdHead;
    return;
}

/******************************************************************************
* Function:      JPGBUF_SetWrHead
* Description:   
* Input:         pstCB        buf
* Output:        Len    
* Return:        
* Others:        
******************************************************************************/
HI_VOID  JPGBUF_SetWrHead(JPG_CYCLEBUF_S* pCB, HI_U32 Len)
{
    HI_U32 u32WrHead;
    JPG_ASSERT_NULLPTR(pCB);
    u32WrHead = pCB->u32WrHead + Len;
    //BM_TRACE("pCB->u32WrHead 0x%x Len 0x%x buflen 0x%x\n",pCB->u32WrHead,Len,pCB->u32BufLen);
    if(u32WrHead >= pCB->u32BufLen)
    {
        u32WrHead -= pCB->u32BufLen;
    }
     
    pCB->u32WrHead = u32WrHead;
    return;
}


/******************************************************************************
* Function:      JPGBUF_GetFreeLen
* Description:   
* Input:         pstCB    
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_U32 JPGBUF_GetFreeLen(const JPG_CYCLEBUF_S* pstCB)
{
    HI_U32 u32FreeLen;
    JPG_ASSERT_NULLPTR(pstCB);

    if (pstCB->u32WrHead >= pstCB->u32RdTail)
    {
        u32FreeLen = (pstCB->u32BufLen - pstCB->u32RsvByte)
                   - (pstCB->u32WrHead - pstCB->u32RdTail);     
    }
    else
    {
        u32FreeLen = (pstCB->u32RdTail - pstCB->u32WrHead) - pstCB->u32RsvByte;
    }

    return u32FreeLen;
}

/******************************************************************************
* Function:      JPGBUF_GetDataBtwRhRt
* Description:  
* Input:          pstCB        buf
* Output:        pRdInfo    
* Return:        
* Others:        
******************************************************************************/
HI_S32   JPGBUF_GetDataBtwRhRt(const JPG_CYCLEBUF_S* pstCB, JPGBUF_DATA_S *pRdInfo)
{
    JPG_ASSERT_NULLPTR(pstCB);
    JPG_ASSERT_NULLPTR(pRdInfo);

    JPGBUF_ASSERT(pstCB->u32WrHead, pstCB->u32RdHead, 
                  pstCB->u32RdTail, pstCB->u32BufLen);
    
    if(pstCB->u32RdHead >= pstCB->u32RdTail)
    {
        pRdInfo->pAddr[0]  = (HI_U8*)pstCB->pBase + pstCB->u32RdTail;
        pRdInfo->u32Len[0] = pstCB->u32RdHead - pstCB->u32RdTail;
        pRdInfo->pAddr[1]  = (HI_U8*)pRdInfo->pAddr[0] + pRdInfo->u32Len[0];
        pRdInfo->u32Len[1] = 0;
    }
    else   
    {
        pRdInfo->pAddr[0]  = (HI_U8*)pstCB->pBase + pstCB->u32RdTail;
        pRdInfo->u32Len[0] = pstCB->u32BufLen - pstCB->u32RdTail;
        pRdInfo->pAddr[1]  = pstCB->pBase;
        pRdInfo->u32Len[1] = pstCB->u32RdHead;
    }

    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPGBUF_GetDataBtwWhRh
* Description:   
* Input:         pstCB        buf
* Output:        pstData    
* Return:        
* Others:        
******************************************************************************/
HI_S32   JPGBUF_GetDataBtwWhRh(const JPG_CYCLEBUF_S* pstCB, JPGBUF_DATA_S *pstData)
{
    JPG_ASSERT_NULLPTR(pstCB);
    JPG_ASSERT_NULLPTR(pstData);

    JPGBUF_ASSERT(pstCB->u32WrHead, pstCB->u32RdHead, 
                  pstCB->u32RdTail, pstCB->u32BufLen);
    
    
    if(pstCB->u32WrHead >= pstCB->u32RdHead)
    {
        pstData->pAddr[0]  = (HI_U8*)pstCB->pBase + pstCB->u32RdHead;
        pstData->u32Len[0] = pstCB->u32WrHead - pstCB->u32RdHead;
        pstData->pAddr[1]  = (HI_U8*)pstData->pAddr[0] + pstData->u32Len[0];
        pstData->u32Len[1] = 0;
        //BM_TRACE("Base1 0x%x u32RdHead 0x%x u32WrHead 0x%x pAddr 0x%x u32Len 0x%x\n", 
        //    pstCB->pBase,pstCB->u32RdHead,pstCB->u32WrHead,pstData->pAddr[0],pstData->u32Len[0]);
           
        assert(pstData->u32Len[0] < pstCB->u32BufLen);
    }
    else   
    {
        pstData->pAddr[0]  = (HI_U8*)pstCB->pBase + pstCB->u32RdHead;
        pstData->u32Len[0] = pstCB->u32BufLen - pstCB->u32RdHead;
        pstData->pAddr[1]  = pstCB->pBase;
        pstData->u32Len[1] = pstCB->u32WrHead;
       // BM_TRACE("Base2 0x%x u32RdHead 0x%x u32WrHead 0x%x pAddr 0x%x u32Len 0x%x bufLen 0x%x\n", 
         //   pstCB->pBase,pstCB->u32RdHead,pstCB->u32WrHead,pstData->pAddr[0],pstData->u32Len[0],pstCB->u32BufLen);
           
    }

    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPGBUF_GetDataBtwWhRt
* Description:   
* Input:         pstCB        buf
* Output:        pstData    
* Return:        
* Others:        
******************************************************************************/
HI_S32   JPGBUF_GetDataBtwWhRt(const JPG_CYCLEBUF_S* pstCB, JPGBUF_DATA_S *pstData)
{
    JPG_ASSERT_NULLPTR(pstCB);
    JPG_ASSERT_NULLPTR(pstData);

    JPGBUF_ASSERT(pstCB->u32WrHead, pstCB->u32RdHead,
                  pstCB->u32RdTail, pstCB->u32BufLen);

    
    if(pstCB->u32WrHead >= pstCB->u32RdTail)
    {
        pstData->pAddr[0]  = (HI_U8*)pstCB->pBase + pstCB->u32RdTail;
        pstData->u32Len[0] = pstCB->u32WrHead - pstCB->u32RdTail;
        pstData->pAddr[1]  = (HI_U8*)pstData->pAddr[0] + pstData->u32Len[0];
        pstData->u32Len[1] = 0;
        assert(pstData->u32Len[0] < pstCB->u32BufLen);
    }
    else   
    {
        pstData->pAddr[0]  = (HI_U8*)pstCB->pBase + pstCB->u32RdTail;
        pstData->u32Len[0] = pstCB->u32BufLen - pstCB->u32RdTail;
        pstData->pAddr[1]  = pstCB->pBase;
        pstData->u32Len[1] = pstCB->u32WrHead;
    }

    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPGBUF_GetBufInfo
* Description:  
* Input:        
* Output:      
*              
* Others:        
******************************************************************************/
HI_S32 JPGBUF_GetBufInfo(const JPG_CYCLEBUF_S* pstCB, HI_VOID** pBase, 
                                                    HI_U32* pBufLen)
{
    *pBufLen = pstCB->u32BufLen;
    *pBase    = pstCB->pBase;
    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPGBUF_GetFreeInfo
* Description:   
* Input:               
* Output:      
*                
* Return:    
* Others:        
******************************************************************************/
HI_S32 JPGBUF_GetFreeInfo(const JPG_CYCLEBUF_S* pstCB, HI_VOID** pFreeBuf, 
                                                    HI_U32* pFreeLen)
{
    HI_U32 u32FreeLen;
    JPG_ASSERT_NULLPTR(pstCB);
    if (pstCB->u32WrHead >= pstCB->u32RdTail)
    {
        u32FreeLen = pstCB->u32BufLen - pstCB->u32WrHead;
        if(pstCB->u32RdTail == 0)
        {
            u32FreeLen -= pstCB->u32RsvByte;
        }
    }
    else
    {
        u32FreeLen = (pstCB->u32RdTail - pstCB->u32WrHead) - pstCB->u32RsvByte;
    }

    *pFreeBuf = (HI_U8*)pstCB->pBase + pstCB->u32WrHead;
   //  printf(" Base 0x%x WrHead 0x%x Buf 0x%x \n",pstCB->pBase ,pstCB->u32WrHead,*pFreeBuf);
    *pFreeLen = u32FreeLen;
    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */


