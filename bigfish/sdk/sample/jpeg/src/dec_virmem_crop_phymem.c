/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : sample_dec_virmem_crop_phymem.c
Version		    : Initial Draft
Author		    : 
Created		    : 2013/06/20
Description	    : ������Դ�������ڴ棬�ü������Ϊ�û��������������ڴ�
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2013/06/20		    y00181162  		    Created file      	
******************************************************************************/

/****************************  add include here     ***************************/

#include "sample_api.h"

/***************************** Macro Definition     ***************************/


/***************************** Structure Definition ***************************/

/********************** Global Variable declaration **************************/
DECLARE_SAMPLE_DEC_SETJMP();


/********************** API forward declarations    **************************/

/****************************************************************************
* description	: CNcomment: �������������ת���� CNend\n
* param[in] 	: NA
* retval		: NA
* others:		: NA
******************************************************************************/
DECLARE_SAMPLE_DEC_ERR_FUNC();



/*****************************************************************************
* func		: sample_dec_virmemin_crop_phymemout
* description: CNcomment: �����ڴ����룬�ü��������������ڴ����  CNend\n
* param[in]	: *pFileName		CNcomment:Ҫ������ļ�	          CNend\n
* retval 	: NA
* others:	: NA
*****************************************************************************/
HI_VOID sample_dec_virmemin_crop_phymemout(HI_CHAR *pFileName)
{

		struct jpeg_decompress_struct cinfo;
		JPEG_MYERR_S jerr;

		HI_U32 u32Width    = 0;
		HI_U32 u32Height   = 0;
        HI_U32 u32Stride   = 0;
		HI_U32 u32MemSize  = 0;

		HI_BOOL bHardDec;
		HI_S32 s32Ret       = HI_SUCCESS;
		
		FILE* pInFile = NULL;
		HI_U64 u64FileSize     = 0;
		HI_U64 u64ReadFileSize = 0;
        HI_CHAR *pSrcVirBuf     = NULL;

		HI_JPEG_SURFACE_DESCRIPTION_S stSurfaceDesc;

        SAMPLE_TRACE("\n\n==================================================================================================\n");
		SAMPLE_TRACE("decode jpeg file is %s\n",pFileName);
		SAMPLE_TRACE("==================================================================================================\n");
		
		pInFile = fopen(pFileName,"rb");
		if(NULL == pInFile)
		{
		   SAMPLE_TRACE("open jpeg file failure");
           return;
		}
		
	    sample_get_file_size(pInFile,&u64FileSize);
	    if(0 == u64FileSize)
	    {
	       SAMPLE_TRACE("get jpeg file size failure\n");
		   fclose(pInFile);
	       return;
	    }

		pSrcVirBuf = (HI_CHAR*)malloc(u64FileSize); 
		if(NULL == pSrcVirBuf)
		{
		    SAMPLE_TRACE("malloc failure\n");
		    fclose(pInFile);
	        return;
		}
		u64ReadFileSize = fread(pSrcVirBuf,1,u64FileSize,pInFile);
		if (u64ReadFileSize != u64FileSize)
		{
		    SAMPLE_TRACE("=== %s : %s :%d fread failure \n",__FILE__,__FUNCTION__,__LINE__);
			fclose(pInFile);
			free(pSrcVirBuf);
			pSrcVirBuf = NULL;
	        return;
		}

        memset(&stSurfaceDesc,0,sizeof(HI_JPEG_SURFACE_DESCRIPTION_S));


		/**
		 ** use ourself error manage function
		 **/
		cinfo.err = jpeg_std_error(&jerr.pub);
		jerr.pub.error_exit = SAMPLE_DEC_ERR_FUCNTION;
		
		if (setjmp(SAMPLE_DEC_SETJMP_BUFFER))
		{
			goto DEC_FINISH;
		}

		/**
		 ** create decompress
		 **/
		jpeg_create_decompress(&cinfo);

		/**
		 ** set stream
		 **/
	    jpeg_mem_src(&cinfo,(HI_UCHAR*)pSrcVirBuf,u64FileSize);

		/**
		 ** parse file
		 **/
	    jpeg_read_header(&cinfo, TRUE);
		
		/**
		 ** set scale and output color space
		 **/
		 cinfo.scale_num   = 1 ;
	     cinfo.scale_denom = 2;
         cinfo.out_color_space = JCS_BGR;

		
		stSurfaceDesc.bCrop = HI_TRUE;
	    stSurfaceDesc.stCropRect.x = 0;
	    stSurfaceDesc.stCropRect.y = 0;
	    stSurfaceDesc.stCropRect.w = 100;
	    stSurfaceDesc.stCropRect.h = 100;
	    
	    u32Width = stSurfaceDesc.stCropRect.w;
	    u32Height = stSurfaceDesc.stCropRect.h;

        switch(cinfo.out_color_space)
        {
	   	    case JCS_ARGB_8888:
			case JCS_ABGR_8888:
				 u32Stride  = (stSurfaceDesc.stCropRect.w * 4 + 16 - 1)&(~(16 - 1));
				 break;
			case JCS_RGB:
			case JCS_BGR:
			case JCS_YCbCr:
			case JCS_CrCbY:
				u32Stride  = (stSurfaceDesc.stCropRect.w * 3 + 16 - 1)&(~(16 - 1));
				break;
			case JCS_RGB_565:
			case JCS_BGR_565:
			case JCS_ARGB_1555:
			case JCS_ABGR_1555:
				u32Stride  = (stSurfaceDesc.stCropRect.w * 2 + 16 - 1)&(~(16 - 1));
				break;
			default:
				break;
        }
	    u32MemSize = stSurfaceDesc.stCropRect.h * u32Stride;
			

		if(0 != u32MemSize)
		{
			 stSurfaceDesc.stOutSurface.pOutPhy[0] = (HI_CHAR*)HI_GFX_AllocMem(u32MemSize, 256, (HI_CHAR*)"jpeg", (HI_CHAR*)"JPEG");
			 if(NULL == stSurfaceDesc.stOutSurface.pOutPhy[0])
			 {
				goto DEC_FINISH;
			 }
			 stSurfaceDesc.stOutSurface.pOutVir[0] = (HI_CHAR*)HI_GFX_MapCached((HI_U32)stSurfaceDesc.stOutSurface.pOutPhy[0]); 
			 if(NULL == stSurfaceDesc.stOutSurface.pOutVir[0])
			 {
				goto DEC_FINISH;
			 }
			 memset(stSurfaceDesc.stOutSurface.pOutVir[0],0,u32MemSize);
			 HI_GFX_Flush((HI_U32)stSurfaceDesc.stOutSurface.pOutPhy[0]);
				 
		}
		stSurfaceDesc.stOutSurface.bUserPhyMem = HI_TRUE;
		stSurfaceDesc.stOutSurface.u32OutStride[0] = u32Stride; 
		s32Ret = HI_JPEG_SetOutDesc(&cinfo, &stSurfaceDesc);
		if(HI_SUCCESS != s32Ret)
		{
		   SAMPLE_TRACE("HI_JPEG_SetOutDesc failure\n");
		   goto DEC_FINISH;
		}


		/**
		 ** start decode
		 **/
	    jpeg_start_decompress(&cinfo);

		HI_JPEG_IfHardDec(&cinfo,&bHardDec);
		if(HI_TRUE == bHardDec)
		{
		    SAMPLE_TRACE("=========================\n");
            SAMPLE_TRACE("hard dec success\n");
			SAMPLE_TRACE("=========================\n");
		}
		else
	    {

	        SAMPLE_TRACE("=========================\n");
            SAMPLE_TRACE("soft dec success\n");
			SAMPLE_TRACE("=========================\n");
		}

		/**
		 ** output the decode data
		 **/
		while (cinfo.output_scanline < cinfo.output_height) 
	    {
		    jpeg_read_scanlines(&cinfo, NULL, 1);
		}

        HI_GFX_Flush((HI_U32)stSurfaceDesc.stOutSurface.pOutPhy[0]);

		test_dec_show(u32Width,u32Height,u32Stride,stSurfaceDesc.stOutSurface.pOutVir[0],cinfo.out_color_space);
		
		/**
		 ** finish decode
		 **/
		jpeg_finish_decompress(&cinfo);

		
DEC_FINISH:

		/**
		 ** destory decode
		 **/
      	jpeg_destroy_decompress(&cinfo);
		
		fclose(pInFile);
		pInFile = NULL;
		
		if(NULL != stSurfaceDesc.stOutSurface.pOutPhy[0])
		{
			HI_GFX_Unmap((HI_U32)stSurfaceDesc.stOutSurface.pOutPhy[0]);
	        HI_GFX_FreeMem((HI_U32)stSurfaceDesc.stOutSurface.pOutPhy[0]);
		}

		if(NULL != pSrcVirBuf)
		{
			free(pSrcVirBuf);
			pSrcVirBuf = NULL;
		}

		return;
		
}
int main(int argc,char** argv)
{

		HI_S32 s32Ret = HI_SUCCESS;
		HI_CHAR pFileName[256] = {0};
		DIR *dir = NULL;
		struct dirent *ptr = NULL;
		
		dir = opendir(SAMPLE_DEC_JPEG_FILE_DIR);
		if(NULL==dir)
		{
		 	SAMPLE_TRACE("open jpeg file directory failure \n");
			return HI_FAILURE;
		}

		Display_Init();
		while((ptr = readdir(dir))!=NULL)
        {
             s32Ret = sample_getjpegfilename(ptr->d_name,pFileName);
             if(HI_FAILURE == s32Ret)
			 {
                continue;
             }
			 sample_dec_virmemin_crop_phymemout(pFileName);
		}

		closedir(dir);

		Display_DeInit();
		
		return 0;
}
