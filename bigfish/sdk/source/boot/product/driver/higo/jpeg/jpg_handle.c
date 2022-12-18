/*******************************************************************************
 *              Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: jpg_handle.c
 * Description: handle
 *
 * History:
 * Version   Date             Author    DefectNum    Description
 * main\1    2008-04-07       d37024    HI_NULL      Create this file.
 ******************************************************************************/

#include "jpg_common.h"
#include "higo_common.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */

 
 typedef struct hiJPG_HANDLEITEM_S
 {    
     HI_BOOL       UsedFlag;          
     HI_U32        Handle;             
     HI_VOID       *pInstance;        
 }JPG_HANDLEITEM_S;
 
 typedef struct hiJPG_HANDLEINFO_S
 {    
     HI_U32           Count;     
     HI_U32           HandleMax;  
     JPG_HANDLEITEM_S *pItemHead; 
 }JPG_HANDLEINFO_S;

#define HANDLE_START   0x1000      /*Handle min*/
#define HANDLE_END     0x7FFFFFF0  /*Handle max*/


#ifndef HIGO_CODE_CUT
#define HANDLE_EVERYMALLOC_NUM 10
static JPG_HANDLEITEM_S s_HdlMem[3*HANDLE_EVERYMALLOC_NUM]; //= {0, 0, HI_NULL, 0};
static JPG_HANDLEINFO_S s_struHandleInfo = {3*HANDLE_EVERYMALLOC_NUM, HANDLE_START, s_HdlMem};
#else
#define HANDLE_EVERYMALLOC_NUM 1
static JPG_HANDLEITEM_S s_HdlMem[3*HANDLE_EVERYMALLOC_NUM]; //= {0, 0, HI_NULL, 0};
static JPG_HANDLEINFO_S s_struHandleInfo = {3*HANDLE_EVERYMALLOC_NUM, HANDLE_START, s_HdlMem};
#endif



/*****************************************************************************/
/*                                   */
/*****************************************************************************/

/******************************************************************************
* Function:      JPG_Handle_Alloc
* Description:   
* Input:         pInstance 
* Output:        pHandle   
* Return:        HI_SUCCESS:          
*                HI_ERR_JPG_NO_MEM:   
*                HI_FAILURE:             
* Others:        
******************************************************************************/
HI_S32 JPG_Handle_Alloc(JPG_HANDLE *pHandle, HI_VOID *pInstance)
{
    HI_U32  Cnt;
#ifndef HIGO_CODE_CUT
	HI_U32 MallocLen;
    /*如果s_struHandleInfo对应的pItemHead为空*/
    if (HI_NULL == s_struHandleInfo.pItemHead)
    {    

        MallocLen = HANDLE_EVERYMALLOC_NUM * sizeof(JPG_HANDLEITEM_S);
        
       // s_struHandleInfo.pItemHead = (JPG_HANDLEITEM_S *)VCOS_malloc(MallocLen);
        s_struHandleInfo.pItemHead = s_HdlMem;
        if (HI_NULL == s_struHandleInfo.pItemHead)
        {
            HIGO_ERROR(HI_ERR_JPG_NO_MEM);
            return HI_ERR_JPG_NO_MEM;
        }
        VCOS_memset(s_struHandleInfo.pItemHead, 0x0, MallocLen);

        s_struHandleInfo.Count = HANDLE_EVERYMALLOC_NUM;
        s_struHandleInfo.HandleMax = HANDLE_START;
    }

#endif
    Cnt = 0;
    while ((Cnt < s_struHandleInfo.Count) 
           && (HI_FALSE != s_struHandleInfo.pItemHead[Cnt].UsedFlag))
    {
        Cnt++; 
    }

    if (Cnt == s_struHandleInfo.Count)
    {
#ifndef HIGO_CODE_CUT
        HI_VOID *pTmp = HI_NULL;
        MallocLen = (s_struHandleInfo.Count + HANDLE_EVERYMALLOC_NUM) 
                    * sizeof(JPG_HANDLEITEM_S);
       // pTmp = (JPG_HANDLEITEM_S *)VCOS_malloc(MallocLen);
        pTmp = s_HdlMem + 10;
        if (HI_NULL == pTmp)
        {
            HIGO_ERROR(HI_ERR_JPG_NO_MEM);
            return HI_ERR_JPG_NO_MEM;
        }
		
        VCOS_memset(pTmp, 0x0, MallocLen);
        VCOS_memcpy(pTmp, s_struHandleInfo.pItemHead, 
                    s_struHandleInfo.Count * sizeof(JPG_HANDLEITEM_S));
        //VCOS_free((HI_VOID *)s_struHandleInfo.pItemHead);
        VCOS_memset(s_struHandleInfo.pItemHead, 0, 
                              HANDLE_EVERYMALLOC_NUM * sizeof(JPG_HANDLEITEM_S));
        s_struHandleInfo.pItemHead = pTmp;
        s_struHandleInfo.Count += HANDLE_EVERYMALLOC_NUM;
    #else
        return HI_FAILURE;
#endif
    }
    
    
    s_struHandleInfo.pItemHead[Cnt].UsedFlag = HI_TRUE;
    s_struHandleInfo.pItemHead[Cnt].pInstance = pInstance;

    if (HANDLE_END == s_struHandleInfo.HandleMax)
    {
        s_struHandleInfo.HandleMax = HANDLE_START;
    }
    s_struHandleInfo.pItemHead[Cnt].Handle = s_struHandleInfo.HandleMax++;
    *pHandle = s_struHandleInfo.pItemHead[Cnt].Handle;
    
    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPG_Handle_Free
* Description:   
* Input:         Handle    
* Output:        
* Return:        
* Others:        
******************************************************************************/
HI_VOID JPG_Handle_Free(JPG_HANDLE Handle)
{
   
#ifndef HIGO_CODE_CUT
    HI_U32 Cnt;
    Cnt = 0;
    while (Cnt < s_struHandleInfo.Count) 
    {
        if ((Handle == s_struHandleInfo.pItemHead[Cnt].Handle)
            && (HI_TRUE == s_struHandleInfo.pItemHead[Cnt].UsedFlag))
        {
            break;
        }
        Cnt++;
    }

    if (Cnt != s_struHandleInfo.Count)
    {
        s_struHandleInfo.pItemHead[Cnt].Handle = 0;
        s_struHandleInfo.pItemHead[Cnt].UsedFlag = HI_FALSE;
    }

#endif    
    return;    
}

/******************************************************************************
* Function:      JPG_Handle_GetInstance
* Description:   Handle
* Input:         Handle    
* Output:        无
* Return:      
* Others:        
******************************************************************************/
HI_VOID* JPG_Handle_GetInstance(JPG_HANDLE Handle)
{
    HI_U32 Cnt;

    Cnt = 0;
    while ((Cnt < s_struHandleInfo.Count) 
           && ((Handle != s_struHandleInfo.pItemHead[Cnt].Handle)
           || ((Handle == s_struHandleInfo.pItemHead[Cnt].Handle) 
           && (HI_FALSE == s_struHandleInfo.pItemHead[Cnt].UsedFlag))))
    {
        Cnt++; 
    }
    if (Cnt == s_struHandleInfo.Count)
    {
        return HI_NULL;
    }
    //BM_TRACE("Cnt %d Addr 0x%x handle %d struHandle %d \n",Cnt,s_struHandleInfo.pItemHead[Cnt].pInstance,Handle,s_struHandleInfo.pItemHead[Cnt].Handle);
    return s_struHandleInfo.pItemHead[Cnt].pInstance;
}

HI_VOID JPG_Handle_Clear(HI_VOID)
{
    VCOS_memset(&s_struHandleInfo, 0, sizeof(JPG_HANDLEINFO_S));
}

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

