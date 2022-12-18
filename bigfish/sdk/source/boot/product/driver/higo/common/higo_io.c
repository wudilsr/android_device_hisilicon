/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : higo_io.c
Version             : Initial Draft
Author              : 
Created             : 2015/06/15
Description         : 码流处理
Function List       : 
History             :
Date                       Author                   Modification
2015/06/15                y00181162                Created file        
******************************************************************************/
#include "hi_go_comm.h"
#include "hi_go_decoder.h"
#include "higo_adp_sys.h"
#include "higo_common.h"
#include "higo_io.h"


/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/


/***************************************************************************************
* func          : HIGO_ADP_IOCreate
* description   : CNcomment: 创建码流处理句柄 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IOCreate(IO_INSTANCE_S* const pstStream, HI_CHAR* pStremBuf, HI_U32 u32StreamLen)
{
  
    if(NULL == pStremBuf || u32StreamLen <= 0){
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HI_FAILURE;
    }
    
	pstStream->pAddr       = pStremBuf;
    pstStream->u32Length   = u32StreamLen;
    pstStream->u32Position = 0;

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : HIGO_ADP_IODestroy
* description   : CNcomment: 销毁码流处理句柄 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IODestroy(IO_INSTANCE_S* const pstStream)
{
	if(NULL == pstStream){
		return HI_FAILURE;
	}
    memset(pstStream,0,sizeof(IO_INSTANCE_S));

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : HIGO_ADP_IORead
* description   : CNcomment: 读码流 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IORead(IO_INSTANCE_S* const pstStream, HI_VOID *pBuf, HI_U32 BufLen, HI_U32 *pCopyLen, HI_BOOL *pEndFlag)
{
	HI_U32 Length = 0;

    if( (NULL == pstStream) || (NULL == pBuf) || (0 == BufLen) || (NULL == pCopyLen) || (NULL == pEndFlag)){
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HI_FAILURE;
    }

 	if(pstStream->u32Length < pstStream->u32Position){
        return HI_FAILURE;
    }
 	
	/** 剩余的码流长度 **/
    Length = pstStream->u32Length - pstStream->u32Position;
    if(BufLen < Length){
        *pCopyLen = BufLen;
    }else{
        *pCopyLen = Length;
    }
    if(0 == *pCopyLen){
    /** 没有码流拷贝了 **/
		return HI_FAILURE;
	}
    
	#ifdef HI_MINIBOOT_SUPPORT
   		mmu_cache_enable();
	#else
    	dcache_enable(0);
	#endif

    memcpy(pBuf,(const HI_VOID*)(pstStream->pAddr + pstStream->u32Position), *pCopyLen);

	#ifdef HI_MINIBOOT_SUPPORT
    	mmu_cache_disable();
	#else
    	dcache_disable();
	#endif

    if(*pCopyLen < BufLen){
        *pEndFlag = HI_TRUE;
    }else{
        *pEndFlag = HI_FALSE;
    }

	pstStream->u32Position += *pCopyLen;
	
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : HIGO_ADP_IOSeek
* description   : CNcomment: 码流回退的位置 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IOSeek(IO_INSTANCE_S* const pstStream, IO_POS_E Position, HI_U32 Offset)
{

	HI_U32 StartPos = 0;

    if((NULL == pstStream) || (Position >= IO_POS_BUTT)){
		return HI_FAILURE;
    }

    StartPos = pstStream->u32Position;
    
    switch(Position){
	    case IO_POS_CUR:
	        break;
	    #if 0
	    /** not used **/
	    case IO_POS_END:
	    	pstStream->u32Position = pstStream->u32Length;
	        break;
	    #endif
	    case IO_POS_SET:
	    	pstStream->u32Position = 0;
	        break;
	    default:
	        HIGO_ERROR(HI_FAILURE);
	        break;
    }
	pstStream->u32Position = pstStream->u32Position + Offset;
	
    if(pstStream->u32Position > pstStream->u32Length){
        HIGO_ERROR(HI_FAILURE);
        pstStream->u32Position = StartPos;
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
    
}

/***************************************************************************************
* func          : HIGO_ADP_IOGetLength
* description   : CNcomment: 获取码流长度 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IOGetLength(IO_INSTANCE_S stStream, HI_U32 *pLength)
{

    if(NULL == pLength)
    {
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HI_FAILURE;
    }
    
	*pLength = stStream.u32Length;

	return HI_SUCCESS;
}

/***************************************************************************************
* func          : HIGO_ADP_IOGetPos
* description   : CNcomment: 获取码流位置 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IOGetPos(IO_INSTANCE_S stStream, HI_U32 *pPos)
{

    if(NULL == pPos)
    {
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HI_FAILURE;
    }

	*pPos = stStream.u32Position;
	
    return HI_SUCCESS;
}
