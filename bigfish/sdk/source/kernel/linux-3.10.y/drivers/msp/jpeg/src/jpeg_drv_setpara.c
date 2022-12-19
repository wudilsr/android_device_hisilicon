/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_drv_setpara.c
Version		    : Initial Draft
Author		    : 
Created		    : 2015/01/25
Description	    :
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2015/01/25		    y00181162  		    Created file      	
******************************************************************************/

/*********************************add include here******************************/

#include "hi_jpeg_reg.h"
#include "jpeg_drv_setpara.h"
#include "jpeg_drv_table.h"
#include "jpeg_drv_parse.h"
#include "jpeg_drv_error.h"
#include "jpeg_drv_mem.h"

#ifdef CONFIG_JPEG_OMX_FUNCTION


/***************************** Macro Definition ******************************/

//#define CONIFG_SETPARA_DEBUG

/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API forward declarations *******************/

/******************************* API realization *****************************/
static HI_S32 jpeg_set_continuebuf(HI_DRV_JPEG_INMSG_S *pstInMsg)
{
    HI_S32 s32Ret = HI_SUCCESS;
    IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)(pstInMsg->u32DecHandle);
    
    s32Ret = jpeg_mem_alloc(pstInMsg->u32DecHandle);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
    
    /** 码流buffer **/
	jpeg_reg_write(JPGD_REG_STADDR, (unsigned long)pstImgInfo->pStreamPhy);
	jpeg_reg_write(JPGD_REG_ENDADDR,(unsigned long)(pstImgInfo->pStreamPhy + JPGD_DRV_STREAM_BUFFER));
    /** 存储码流buffer **/
    jpeg_reg_write(JPGD_REG_STADD, (unsigned long)pstImgInfo->pStreamPhy);
    jpeg_reg_write(JPGD_REG_ENDADD,(unsigned long)(pstImgInfo->pStreamPhy + JPGD_DRV_STREAM_BUFFER));

    return HI_SUCCESS;
    
}
/***************************************************************************************
* func			: jpeg_set_streambuf
* description	: set stream buffer
				  CNcomment: 设置码流buffer CNend\n
* others:		: NA
***************************************************************************************/
static HI_S32 jpeg_set_streambuf(HI_DRV_JPEG_INMSG_S *pstInMsg)
{/** 暂不支持输出内存为虚拟内存 **/

    HI_CHAR *pStartBufPhy   = NULL;
	HI_CHAR *pEndBufPhy     = NULL;
	HI_CHAR *pStartDataPhy  = NULL;
	HI_CHAR *pEndDataPhy    = NULL;
    IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)(pstInMsg->u32DecHandle);
    
    /** 码流buffer **/
    if(0 == pstInMsg->u32SaveLen[1])
    {/** 没有码流回绕 **/
        pStartBufPhy   = pstInMsg->pSavePhy - 128;
        pStartBufPhy   = (HI_CHAR*)(((unsigned long)pStartBufPhy + 64 - 1) & (~(64 - 1)));
        pEndBufPhy     = pstInMsg->pSavePhy + pstInMsg->u32SaveLen[0] + 128;
    }
    else
    {/** 有码流回绕 **/
        pStartBufPhy = pstInMsg->pAllPhy;
	    pEndBufPhy   = pstInMsg->pAllPhy + pstInMsg->u32AllLen;
    }

    /** 数据buffer **/
    if(0 == pstInMsg->u32SaveLen[1])
    {/** 没有码流回绕 **/
        pStartDataPhy  = pstInMsg->pSavePhy + pstImgInfo->u32CurPos[0];
        pEndDataPhy    = pstInMsg->pSavePhy + pstInMsg->u32SaveLen[0];
    }/** 有码流回绕 **/
    else if(pstImgInfo->u32CurPos[0] < pstInMsg->u32SaveLen[0])
    {
        pStartDataPhy  = pstInMsg->pSavePhy + pstImgInfo->u32CurPos[0];
        pEndDataPhy    = pstInMsg->pAllPhy  + pstInMsg->u32SaveLen[1];
    }
    else
    {
        pStartDataPhy  = pstInMsg->pAllPhy  + pstImgInfo->u32CurPos[1];
        pEndDataPhy    = pstInMsg->pAllPhy  + pstInMsg->u32SaveLen[1];
    }
    
	/** 码流buffer **/
	jpeg_reg_write(JPGD_REG_STADDR, (unsigned long)pStartBufPhy);
	jpeg_reg_write(JPGD_REG_ENDADDR,(unsigned long)pEndBufPhy);
    /** 存储码流buffer **/
    jpeg_reg_write(JPGD_REG_STADD,  (unsigned long)pStartDataPhy);
    jpeg_reg_write(JPGD_REG_ENDADD, (unsigned long)pEndDataPhy);

    return HI_SUCCESS;
}

/***************************************************************************************
* func			: jpeg_set_outbuf
* description	: set output buffer
				  CNcomment: 设置输出buffer CNend\n
* others:		: NA
***************************************************************************************/
static HI_VOID jpeg_set_outbuf(HI_DRV_JPEG_OUTMSG_S *pstOutMsg)
{/** 暂不支持输出内存为虚拟内存 **/
    jpeg_reg_write(JPGD_REG_YSTADDR, (unsigned long)pstOutMsg->pOutPhy[0]);
	jpeg_reg_write(JPGD_REG_UVSTADDR,(unsigned long)pstOutMsg->pOutPhy[1]);
}

/***************************************************************************************
* func			: jpeg_set_factor
* description	: 设置采样因子
				  CNcomment: 设置采样因子 CNend\n
* others:		: NA
***************************************************************************************/
static HI_VOID jpeg_set_factor(HI_DRV_JPEG_OUTMSG_S *pstOutMsg)
{
    HI_U8 u8YFac = 0,u8UFac = 0,u8VFac = 0;
    IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)(pstOutMsg->u32DecHandle);
    
    u8YFac = (HI_U8)(((pstImgInfo->u8Fac[0][0] << 4) | pstImgInfo->u8Fac[0][1]) & 0xff);
    u8UFac = (HI_U8)(((pstImgInfo->u8Fac[1][0] << 4) | pstImgInfo->u8Fac[1][1]) & 0xff);
    u8VFac = (HI_U8)(((pstImgInfo->u8Fac[2][0] << 4) | pstImgInfo->u8Fac[2][1]) & 0xff);
    jpeg_reg_write(JPGD_REG_SAMPLINGFACTOR,(unsigned long)((u8YFac << 16) |(u8UFac << 8) | u8VFac));
}

/***************************************************************************************
* func			: jpeg_set_yuv420sp
* description	: output yuv420 sp
				  CNcomment: 统一输出yuv420 semi-planer CNend\n
* others:		: NA
***************************************************************************************/
static HI_VOID jpeg_set_yuv420sp(HI_VOID)
{
#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
    jpeg_reg_write(JPGD_REG_OUTTYPE,0x4);
#endif
}

/***************************************************************************************
* func			: jpeg_set_lupixsum
* description	: output lu pixle sum
				  CNcomment: 统一输出亮度和值 CNend\n
* others:		: NA
***************************************************************************************/
static HI_VOID jpeg_set_lupixsum(HI_VOID)
{
#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    jpeg_reg_write(JPGD_REG_LPIXSUM1,(unsigned long)0x80000000);
#endif
}

/***************************************************************************************
* func			: jpeg_set_sofn
* description	: set sof message
				  CNcomment: 配置图像基本信息 CNend\n
* others:		: NA
***************************************************************************************/
static HI_VOID  jpeg_set_sofn(HI_DRV_JPEG_OUTMSG_S *pstOutMsg)
{
    
    HI_S32 s32Scale      = 0;
    HI_S32 s32TmpScale   = 0;
    HI_S32 s32Stride     = 0;
    HI_S32 s32YInWidth   = 0;
    HI_S32 s32YInHeight  = 0;
    HI_S32 s32PicSize    = 0;
    HI_S32 s32DefaultScale  = 0;
    IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)(pstOutMsg->u32DecHandle);

    switch(pstOutMsg->s32Scale)
    {
		case 1:
			s32TmpScale = 0;
			break;
		case 2:
			s32TmpScale = 1;
			break;
		case 4:
			s32TmpScale = 2;
			break;
		default:
			s32TmpScale = 3;
			break;
    }
    
    s32DefaultScale = (HI_S32)0x34;
    s32YInWidth     = (1 == pstImgInfo->u8Fac[0][0]) ? ((pstImgInfo->s32InWidth  + JPEG_DRV_MCU_8ALIGN - 1)>>3) : ((pstImgInfo->s32InWidth  + JPEG_DRV_MCU_16ALIGN - 1)>>4);
    s32YInHeight    = (1 == pstImgInfo->u8Fac[0][1]) ? ((pstImgInfo->s32InHeight + JPEG_DRV_MCU_8ALIGN - 1)>>3) : ((pstImgInfo->s32InHeight + JPEG_DRV_MCU_16ALIGN - 1)>>4);
    s32PicSize      = (s32YInWidth| (s32YInHeight << 16));
    s32Stride       = (HI_S32)((pstOutMsg->u32OutStride[1] << 16 ) | pstOutMsg->u32OutStride[0]);
    s32Scale        =  ((HI_U32)s32DefaultScale & 0xfffffffc) | s32TmpScale | 0x8;
    
    jpeg_reg_write(JPGD_REG_PICTYPE,  (unsigned long)pstImgInfo->eImgFmt);
    jpeg_reg_write(JPGD_REG_SCALE,    (unsigned long)s32Scale);
    jpeg_reg_write(JPGD_REG_PICSIZE,  (unsigned long)s32PicSize);
    jpeg_reg_write(JPGD_REG_STRIDE,   (unsigned long)s32Stride);
    
}
/*****************************************************************************
* func			: jpeg_set_dri
* description	: set the dri
                  CNcomment:  设置dri得值         CNend\n
* param[in] 	:
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID	jpeg_set_dri(HI_DRV_JPEG_OUTMSG_S *pstOutMsg)
{
    IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)(pstOutMsg->u32DecHandle);
    jpeg_reg_write(JPGD_REG_DRI,  (unsigned long)pstImgInfo->s32RestartInterval);
}

/*****************************************************************************
* func			: jpeg_set_memmask
* description	: set the memory mask
                  CNcomment:  设置mem信息         CNend\n
* param[in] 	:
* retval		: NA
* others:		: NA
*****************************************************************************/
static HI_VOID jpeg_set_memmask(HI_DRV_JPEG_OUTMSG_S *pstOutMsg)
{

#ifdef CONFIG_JPEG_MMU_SUPPORT
	IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)(pstOutMsg->u32DecHandle);
#endif

	HI_U32 u32Mask =   JPEG_DRV_STREAM_MEM_MMU_TYPE            \
		             | JPEG_DRV_YOUTPUT_MEM_MMU_TYPE           \
		             | JPEG_DRV_UVOUTPUT_MEM_MMU_TYPE          \
		             | JPEG_DRV_XRGBSAMPLE0_READ_MEM_MMU_TYPE  \
		             | JPEG_DRV_XRGBSAMPLE1_READ_MEM_MMU_TYPE  \
		             | JPEG_DRV_XRGBSAMPLE0_WRITE_MEM_MMU_TYPE \
		             | JPEG_DRV_XRGBSAMPLE1_WRITE_MEM_MMU_TYPE \
					 | JPEG_DRV_XRGBOUTPUT_MEM_MMU_TYPE;

#ifdef CONFIG_JPEG_MMU_SUPPORT
	if(pstImgInfo->u32MemTypeMask & JPEG_DRV_STREAM_MEM_MMU_TYPE){
       u32Mask &= ~JPEG_DRV_STREAM_MEM_MMU_TYPE;
    }
	if(pstImgInfo->u32MemTypeMask & JPEG_DRV_YOUTPUT_MEM_MMU_TYPE){
       u32Mask &= ~JPEG_DRV_YOUTPUT_MEM_MMU_TYPE;
    }
	if(pstImgInfo->u32MemTypeMask & JPEG_DRV_UVOUTPUT_MEM_MMU_TYPE){
       u32Mask &= ~JPEG_DRV_UVOUTPUT_MEM_MMU_TYPE;
    }
	if(pstImgInfo->u32MemTypeMask & JPEG_DRV_XRGBSAMPLE0_READ_MEM_MMU_TYPE){
       u32Mask &= ~JPEG_DRV_XRGBSAMPLE0_READ_MEM_MMU_TYPE;
    }
	if(pstImgInfo->u32MemTypeMask & JPEG_DRV_XRGBSAMPLE1_READ_MEM_MMU_TYPE){
       u32Mask &= ~JPEG_DRV_XRGBSAMPLE1_READ_MEM_MMU_TYPE;
    }
	if(pstImgInfo->u32MemTypeMask & JPEG_DRV_XRGBSAMPLE0_WRITE_MEM_MMU_TYPE){
       u32Mask &= ~JPEG_DRV_XRGBSAMPLE0_WRITE_MEM_MMU_TYPE;
    }
	if(pstImgInfo->u32MemTypeMask & JPEG_DRV_XRGBSAMPLE1_WRITE_MEM_MMU_TYPE){
       u32Mask &= ~JPEG_DRV_XRGBSAMPLE1_WRITE_MEM_MMU_TYPE;
    }
	if(pstImgInfo->u32MemTypeMask & JPEG_DRV_XRGBOUTPUT_MEM_MMU_TYPE){
       u32Mask &= ~JPEG_DRV_XRGBOUTPUT_MEM_MMU_TYPE;
    }
	jpeg_reg_write(JPGD_REG_MMU_BYPASS,(unsigned long)u32Mask);
#else
	/** 非mmu，都bypass **/
	jpeg_reg_write(JPGD_REG_MMU_BYPASS,(unsigned long)u32Mask);
#endif

}


/***************************************************************************************
* func			: jpg_dec_setpara
* description	: set para that hard dec needed.
				  CNcomment: 配置硬件解码需要的参数信息 CNend\n
* param[in] 	: pstDecInfo
* retval		: HI_SUCCESS 成功
* retval		: HI_FAILURE 失败
* others:		: NA
***************************************************************************************/
HI_S32 jpg_dec_setpara(HI_JPEG_DECINFO_S *pstDecInfo)
{

    HI_S32 s32Ret = HI_SUCCESS;
    
#ifdef CONIFG_SETPARA_DEBUG
    mdelay(100);
    JPEG_TRACE("\n===============================================%s %d\n",__func__,__LINE__);
    JPEG_TRACE("begin jpeg_set_dqt\n");
#endif

    /** set dqt **/
	jpeg_set_dqt(&(pstDecInfo->stOutMsg));

     /**set dri value **/
	jpeg_set_dri(&(pstDecInfo->stOutMsg));

    jpeg_set_memmask(&(pstDecInfo->stOutMsg));
    
#ifdef CONIFG_SETPARA_DEBUG
    JPEG_TRACE("end jpeg_set_dqt\n");
    JPEG_TRACE("===============================================%s %d\n",__func__,__LINE__);
    mdelay(100);
    JPEG_TRACE("begin jpeg_set_dht\n");
#endif

    /** set dht **/
	s32Ret = jpeg_set_dht(&(pstDecInfo->stOutMsg));
    if(HI_SUCCESS != s32Ret)
    {
        JPEG_TRACE("set huff table failure\n");
        return HI_ERR_JPEG_SERPARA;
    }

#ifdef CONIFG_SETPARA_DEBUG
    JPEG_TRACE("end jpeg_set_dht\n");
    JPEG_TRACE("===============================================%s %d\n",__func__,__LINE__);
    mdelay(100);
    JPEG_TRACE("begin jpeg_set_sofn\n");
#endif

    s32Ret = jpeg_get_sofn(&(pstDecInfo->stOutMsg));
    if(HI_SUCCESS != s32Ret)
    {
        JPEG_TRACE("jpeg_get_sofn failure\n");
        return HI_ERR_JPEG_SERPARA;
    }
    jpeg_set_sofn(&(pstDecInfo->stOutMsg));

#ifdef CONIFG_SETPARA_DEBUG
    JPEG_TRACE("end jpeg_set_sofn\n");
    JPEG_TRACE("===============================================%s %d\n",__func__,__LINE__);
    mdelay(100);
    JPEG_TRACE("begin jpeg_set_factor\n");
#endif

    jpeg_set_factor(&(pstDecInfo->stOutMsg));

#ifdef CONIFG_SETPARA_DEBUG
    JPEG_TRACE("end jpeg_set_factor\n");
    JPEG_TRACE("===============================================%s %d\n",__func__,__LINE__);
    mdelay(100);
    JPEG_TRACE("begin jpeg_set_yuv420sp\n");
#endif

    if(HI_TRUE == pstDecInfo->stOutMsg.bOutYuvSp420)
	{
	   if(8 == pstDecInfo->stOutMsg.s32Scale)
	   {/** 缩放8倍不支持 **/
	   	   return HI_ERR_JPEG_SERPARA;
	   }
	   jpeg_set_yuv420sp();
	}

#ifdef CONIFG_SETPARA_DEBUG
    JPEG_TRACE("end jpeg_set_yuv420sp\n");
    JPEG_TRACE("===============================================%s %d\n",__func__,__LINE__);
    mdelay(100);
    JPEG_TRACE("begin jpeg_set_lupixsum\n");
#endif

    if(HI_TRUE == pstDecInfo->stOutMsg.bLuPixSum)
    {
        jpeg_set_lupixsum();
    }

#ifdef CONIFG_SETPARA_DEBUG
    JPEG_TRACE("end jpeg_set_lupixsum\n");
    JPEG_TRACE("===============================================%s %d\n",__func__,__LINE__);
    mdelay(100);
    JPEG_TRACE("begin jpeg_set_streambuf\n");
#endif

    if(HI_TRUE == pstDecInfo->stInMsg.bUserPhyMem)
    {
        s32Ret = jpeg_set_streambuf(&(pstDecInfo->stInMsg));
    }
    else
    {
        s32Ret = jpeg_set_continuebuf(&(pstDecInfo->stInMsg));
    }
    if(HI_SUCCESS != s32Ret)
    {
        JPEG_TRACE("set buffer para failure\n");
        return HI_ERR_JPEG_SERPARA;
    }
    
#ifdef CONIFG_SETPARA_DEBUG
    JPEG_TRACE("end jpeg_set_streambuf\n");
    JPEG_TRACE("===============================================%s %d\n",__func__,__LINE__);
    mdelay(100);
    JPEG_TRACE("begin jpeg_set_outbuf\n");
#endif

    jpeg_set_outbuf(&(pstDecInfo->stOutMsg));

#ifdef CONIFG_SETPARA_DEBUG
    JPEG_TRACE("end jpeg_set_outbuf\n");
    JPEG_TRACE("===============================================%s %d\n",__func__,__LINE__);
    mdelay(100);
#endif

    return HI_SUCCESS;
    
}

/***************************************************************************
* func          : jpeg_send_stream
* description   : send the continue stream.
                 CNcomment: 送续码流 CNend\n
* param[in]     : u32DecHandle
* param[in] 	: ps32Offset
* param[in] 	: pbReachEOF
* retval        : HI_SUCCESS 成功
* retval        : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
HI_S32 jpeg_send_stream(HI_U32 u32DecHandle,HI_S32 *ps32Offset,HI_BOOL *pbReachEOF)
{/** 暂不支持输出内存为虚拟内存 **/

    IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)u32DecHandle;
    HI_S32 s32CpyLen    = 0;
    HI_S32 s32LeaveLen0 = 0;
    HI_S32 s32LeaveLen1 = 0;

    *ps32Offset  = 0;
    s32LeaveLen0 = pstImgInfo->u32DataLen[0] - pstImgInfo->u32CurPos[0];
    s32LeaveLen1 = pstImgInfo->u32DataLen[1] - pstImgInfo->u32CurPos[1];
    
    /** 没有码流回绕 **/
    if(0 == pstImgInfo->u32DataLen[1])
    {
        if(s32LeaveLen0 > JPGD_DRV_STREAM_BUFFER)
        {
            s32CpyLen   = JPGD_DRV_STREAM_BUFFER;
            *pbReachEOF = HI_FALSE;
        }
        else
        {
            s32CpyLen = s32LeaveLen0;
            *pbReachEOF = HI_TRUE;
        }
                
        memcpy(pstImgInfo->pStreamVir,pstImgInfo->pDataVir[0] + pstImgInfo->u32CurPos[0],s32CpyLen);

        *ps32Offset = s32CpyLen;
        pstImgInfo->u32CurPos[0] += s32CpyLen;
        
        return HI_SUCCESS;
    }
    
    /** 有码流回绕 **/
    if(s32LeaveLen0 >= JPGD_DRV_STREAM_BUFFER)
    {/** 只需要拷贝第一块buffer **/
        s32CpyLen    = JPGD_DRV_STREAM_BUFFER;
        *pbReachEOF  = HI_FALSE;
        
        memcpy(pstImgInfo->pStreamVir,pstImgInfo->pDataVir[0] + pstImgInfo->u32CurPos[0],s32CpyLen);

        *ps32Offset  = JPGD_DRV_STREAM_BUFFER;
        pstImgInfo->u32CurPos[0] += s32CpyLen;
        
        return HI_SUCCESS;
    }
    else
    {
        s32CpyLen = s32LeaveLen0;
        pstImgInfo->u32CurPos[0] += s32CpyLen;
        
        memcpy(pstImgInfo->pStreamVir,pstImgInfo->pDataVir[0] + pstImgInfo->u32CurPos[0],s32CpyLen);

        *ps32Offset  = s32CpyLen;
        pstImgInfo->u32CurPos[0] += s32CpyLen;
    }
    
    /** 需要从第二块buffer补充数据 **/
    if(s32LeaveLen1 < (JPGD_DRV_STREAM_BUFFER - s32CpyLen))
    {/** 只可以补充一次 **/
        s32CpyLen    = s32LeaveLen1;
        *pbReachEOF  = HI_TRUE;
        
        memcpy(pstImgInfo->pStreamVir + *ps32Offset,pstImgInfo->pDataVir[1] + pstImgInfo->u32CurPos[1],s32CpyLen);

        *ps32Offset += s32CpyLen;
        pstImgInfo->u32CurPos[1] += s32CpyLen;
        
    }
    else
    {
        s32CpyLen    = JPGD_DRV_STREAM_BUFFER - s32CpyLen;
        *pbReachEOF  = HI_FALSE;
        
        memcpy(pstImgInfo->pStreamVir + *ps32Offset,pstImgInfo->pDataVir[1] + pstImgInfo->u32CurPos[1],s32CpyLen);

        *ps32Offset  = JPGD_DRV_STREAM_BUFFER;
        pstImgInfo->u32CurPos[1] += s32CpyLen;
        
    }
    
    return HI_SUCCESS;
}

#endif
