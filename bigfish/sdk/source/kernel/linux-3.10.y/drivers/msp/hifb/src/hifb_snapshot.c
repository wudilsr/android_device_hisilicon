/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hifb_snapshot.c
  Version       : Initial Draft
  Author        : q00214668
  Created       : 2013/08/07
  Last Modified :
  Description   : snapshot from fb device
  History       :
  1.Date        : 2013/08/07
    Author      : q00214668
    Modification: Created file

******************************************************************************/
#include <linux/string.h>
#include "hifb.h"
#include "hifb_p.h"
#include "hifb_comm.h"
#include "hifb_drv.h"
#include "hi_drv_file.h"

#ifndef HI_ADVCA_FUNCTION_RELEASE
#define CFG_HIFB_PROC_SUPPORT
#endif

#ifdef CFG_HIFB_PROC_SUPPORT
#define HIFB_SNAPSHOT_INFO(fmt...) printk(fmt)
extern HIFB_DRV_OPS_S s_stDrvOps;
extern HIFB_DRV_TDEOPS_S s_stDrvTdeOps;
extern HI_U32 hifb_getbppbyfmt(HIFB_COLOR_FMT_E enColorFmt);
static HIFB_COLOR_FMT_E gSnapshot_ColorFmt = HIFB_FMT_RGB888;
/* to save layer id and layer size */
extern HIFB_LAYER_S s_stLayer[HIFB_MAX_LAYER_NUM];


//λͼͷ�ļ��ṹ��ע���ֽڶ������

typedef struct  tagBITMAPFILEHEADER{
	HI_U16 u16Type;			/*�ļ����ͣ���Ϊ0x4D42*/
	HI_U32 u32Size;			/*�ļ���С���������ݼ���ͷ�ļ���Сsizeof*/
	HI_U16 u16Reserved1;		/*����λ*/
    HI_U16 u16Reserved2;		/*����λ*/
    HI_U32 u32OffBits;			/*�ļ�ͷ��ʵ��λͼ���ݵ�ƫ����*/
}__attribute__((packed)) BMP_BMFHEADER_S;

//λͼ��Ϣͷ�ṹ
typedef  struct tagBITMAPINFOHEADER{
	HI_U32 u32Size;			/*λͼ��Ϣͷ�Ĵ�С,sizeof(BMP_BMIHEADER_S)*/
	HI_U32 u32Width;			/*ͼ����*/
	HI_U32 u32Height;			/*ͼ��߶�*/		
	HI_U16 u32Planes;			/*λͼλ��������Ϊ1*/
	HI_U16 u32PixbitCount;			/*ÿ�����ص�λ������RGB8888����32*/
	HI_U32 u32Compression;	/*λͼ����ѹ�����ͣ���Ϊ0����ʾ����ѹ��*/
	HI_U32 u32SizeImage;		/*λͼ���ݴ�С����Ϊ0 */
	HI_U32 u32XPelsPerMeter;	/*λͼˮƽ�ֱ��ʣ���ͼ������ͬ*/
	HI_U32 u32YPelsPerMeter;	/*λͼ��ֱ�ֱ��ʣ���ͼ��߶���ͬ*/
	HI_U32 u32ClrUsed;		/*˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ����������Ϊ0*/
	HI_U32 u32ClrImportant;	/*��ͼ����ʾ����Ҫ����ɫ����������Ϊ0*/
} BMP_BMIHEADER_S;

HI_VOID hifb_captureimage_fillbuffer(HI_U32 u32LayerID, HIFB_BUFFER_S *pstBuffer)
{
    HIFB_PAR_S *par;
	struct fb_info *info;
	
	info = s_stLayer[u32LayerID].pstInfo;
	par  = (HIFB_PAR_S *)(info->par);

	pstBuffer->stCanvas.enFmt      = par->stExtendInfo.enColFmt;
	pstBuffer->stCanvas.u32Width   = par->stExtendInfo.u32DisplayWidth;
	pstBuffer->stCanvas.u32Height  = par->stExtendInfo.u32DisplayHeight;
	pstBuffer->stCanvas.u32PhyAddr = par->stRunInfo.u32ScreenAddr;
	pstBuffer->stCanvas.u32Pitch   = info->fix.line_length;
	
    if (HIFB_LAYER_BUF_NONE == par->stExtendInfo.enBufMode)
	{
	    pstBuffer->stCanvas.enFmt      = par->stDispInfo.stUserBuffer.stCanvas.enFmt;
	    pstBuffer->stCanvas.u32Pitch   = par->stDispInfo.stUserBuffer.stCanvas.u32Pitch;		
	}

	if (par->bSetStereoMode)
	{
	    memcpy(&pstBuffer->stCanvas, &par->st3DInfo.st3DSurface, sizeof(pstBuffer->stCanvas));
	}

	if (par->stProcInfo.bWbcProc)
	{
	    HIFB_SLVLAYER_DATA_S stLayerInfo;
		
	    if (s_stDrvOps.HIFB_DRV_GetSlvLayerInfo(&stLayerInfo))
		{
		    HIFB_ERROR("fail to get layer%d info!\n", par->stBaseInfo.u32LayerID);
			return;
		}

		pstBuffer->stCanvas.enFmt      = HIFB_FMT_ARGB8888;
		pstBuffer->stCanvas.u32Width   = stLayerInfo.stCurWBCBufRect.w;
		pstBuffer->stCanvas.u32Height  = stLayerInfo.stCurWBCBufRect.h;
		pstBuffer->stCanvas.u32PhyAddr = stLayerInfo.u32ReadBufAddr;
		pstBuffer->stCanvas.u32Pitch   = stLayerInfo.u32Stride;
	}

	HIFB_INFO("hifb_snapshot colorfmt %d, width %d, height %d, pitch %d, addr 0x%x\n",
		             pstBuffer->stCanvas.enFmt,pstBuffer->stCanvas.u32Width,pstBuffer->stCanvas.u32Height,
		             pstBuffer->stCanvas.u32Pitch, pstBuffer->stCanvas.u32PhyAddr);

	return;
}

HI_VOID hifb_captureimage_fromdevice(HI_U32 u32LayerID, HI_BOOL bAlphaEnable)
{
	HI_S32 s32Ret;
	HI_U32 u32Row;
	HI_CHAR name[HIFB_FILE_NAME_MAX_LEN];
	HI_S8 *pData, *pTemp;
	HI_U32 u32BufSize, u32Bpp, u32Stride;
	HIFB_BUFFER_S   stSrcBuffer, stDstBuffer;
	HIFB_BLIT_OPT_S stBlitOpt;
	BMP_BMFHEADER_S sBmpHeader;
	BMP_BMIHEADER_S sBmpInfoHeader;
	HI_CHAR filepath[HIFB_FILE_PATH_MAX_LEN-HIFB_FILE_NAME_MAX_LEN]={0};
	HI_CHAR filename[HIFB_FILE_PATH_MAX_LEN]={0};
	struct file* fp;

	memset(&stBlitOpt, 0, sizeof(HIFB_BLIT_OPT_S));

	hifb_captureimage_fillbuffer(u32LayerID, &stSrcBuffer);

	stSrcBuffer.UpdateRect.x = 0;
	stSrcBuffer.UpdateRect.y = 0;
	stSrcBuffer.UpdateRect.w = stSrcBuffer.stCanvas.u32Width;
	stSrcBuffer.UpdateRect.h = stSrcBuffer.stCanvas.u32Height;

	memcpy(&stDstBuffer, &stSrcBuffer, sizeof(HIFB_BUFFER_S));
	stDstBuffer.stCanvas.enFmt = gSnapshot_ColorFmt;

	/*alloc dst buffer*/
	u32Bpp = hifb_getbppbyfmt(stDstBuffer.stCanvas.enFmt);
	u32Stride = ((stSrcBuffer.stCanvas.u32Width * u32Bpp>>3) + 0xf)&0xfffffff0;
	u32BufSize = stSrcBuffer.stCanvas.u32Height * u32Stride; 

	stDstBuffer.stCanvas.u32Pitch = u32Stride;

	snprintf(name, sizeof(name),"HIFB_SnapShot%d", u32LayerID);
	stDstBuffer.stCanvas.u32PhyAddr = hifb_buf_allocmem(name, u32BufSize);
	if (0 == stDstBuffer.stCanvas.u32PhyAddr)
    {
        HIFB_ERROR("failed to malloc the snapshot memory, size: %d KBtyes!\n", u32BufSize/1024);
        return ;
    }
    else
    {
        /* initialize the virtual address and clear memory */
        pData = (HI_S8*)hifb_buf_map(stDstBuffer.stCanvas.u32PhyAddr);
        if (HI_NULL == pData)
        {
            HIFB_ERROR("Failed to map snapshot memory.\n");
			return;
        }
        else
        {
            memset(pData, 0x00, u32BufSize);
        }
    }

	HIFB_INFO("hifb_snapshot srcbuf info:\n\
			   phyadd 0x%x, width %d, height %d, stride %d\n",stSrcBuffer.stCanvas.u32PhyAddr,stSrcBuffer.stCanvas.u32Width,
			   stSrcBuffer.stCanvas.u32Height, stSrcBuffer.stCanvas.u32Pitch);
	HIFB_INFO("hifb_snapshot dstbuf info:\n\
			   phyadd 0x%x, width %d, height %d, stride %d\n",stDstBuffer.stCanvas.u32PhyAddr,stDstBuffer.stCanvas.u32Width,
			   stDstBuffer.stCanvas.u32Height, stDstBuffer.stCanvas.u32Pitch);

	if (bAlphaEnable)
	{
	    stBlitOpt.stAlpha.bAlphaEnable = HI_TRUE;
	    stBlitOpt.stAlpha.u8GlobalAlpha=0xff;
	}

	stBlitOpt.bBlock = HI_TRUE;
	s32Ret = s_stDrvTdeOps.HIFB_DRV_Blit(&stSrcBuffer, &stDstBuffer, &stBlitOpt, HI_TRUE);
	if (s32Ret < 0)
	{
	    HIFB_ERROR("tde blit error!\n");
	    return;
	}

	/*��ÿһ�������ֵ*/
    sBmpHeader.u16Type = 0x4D42;
    sBmpHeader.u32Size = u32BufSize + sizeof(BMP_BMFHEADER_S) + sizeof(BMP_BMIHEADER_S);
    sBmpHeader.u16Reserved1 = 0;
    sBmpHeader.u16Reserved2 = 0;
    sBmpHeader.u32OffBits = sizeof(BMP_BMFHEADER_S) + sizeof(BMP_BMIHEADER_S); //+ 2;//

	sBmpInfoHeader.u32Size = sizeof(BMP_BMIHEADER_S);
    sBmpInfoHeader.u32Width = stDstBuffer.stCanvas.u32Width;
    sBmpInfoHeader.u32Height = stDstBuffer.stCanvas.u32Height;
    sBmpInfoHeader.u32Planes = 1;
    sBmpInfoHeader.u32PixbitCount = 24;
    sBmpInfoHeader.u32Compression = 0;
    sBmpInfoHeader.u32SizeImage = 0;
    sBmpInfoHeader.u32XPelsPerMeter = stDstBuffer.stCanvas.u32Width;
    sBmpInfoHeader.u32YPelsPerMeter = stDstBuffer.stCanvas.u32Height;
    sBmpInfoHeader.u32ClrUsed = 0;
    sBmpInfoHeader.u32ClrImportant = 0;

	HI_DRV_FILE_GetStorePath(filepath, HIFB_FILE_PATH_MAX_LEN-HIFB_FILE_NAME_MAX_LEN);
	snprintf(filename, sizeof(filename),"%s/hifb_snapshot%d.bmp", filepath,u32LayerID);
	//fp = HI_DRV_FILE_Open(filename, 1);
	fp = HI_NULL;
	fp = filp_open(filename, O_WRONLY | O_CREAT | O_LARGEFILE, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (IS_ERR(fp))
	{
		HIFB_ERROR("fail to open file %s.\n",filename);
		return;
	}

	HIFB_INFO("success to create file %s.\n",filename);
	
	if (sizeof(BMP_BMFHEADER_S) != 
			HI_DRV_FILE_Write(fp, (HI_S8*)&sBmpHeader, sizeof(BMP_BMFHEADER_S)))
	{
		HIFB_ERROR("Write data to file %s failure.\n",filename);
		return;
	}

	if (sizeof(BMP_BMIHEADER_S) != 
			HI_DRV_FILE_Write(fp, (HI_S8*)&sBmpInfoHeader, sizeof(BMP_BMIHEADER_S)))
	{
		HIFB_ERROR("Write data to file %s failure.\n",filename);
		return;
	}

	u32Row = stSrcBuffer.stCanvas.u32Height;
	pTemp  = pData;
	pTemp += (u32Stride * (stSrcBuffer.stCanvas.u32Height - 1));
	
	while(u32Row)
	{
		if (u32Stride != HI_DRV_FILE_Write(fp, (HI_S8*)pTemp, u32Stride))
		{
			HIFB_ERROR("Write data to file %s failure.\n",filename);
			return;
		}

		pTemp -= u32Stride;
		u32Row--;
	}	

	HI_DRV_FILE_Close(fp);
	
	hifb_buf_ummap((HI_VOID *)pData);
	hifb_buf_freemem(stDstBuffer.stCanvas.u32PhyAddr);
	
	HI_PRINT("success to capture fb%d, store in file %s.\n", u32LayerID, filename);
		
	return;
}
#endif
