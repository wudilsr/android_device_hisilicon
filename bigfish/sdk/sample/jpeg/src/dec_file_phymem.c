/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : sample_dec_file_phymem.c
Version		    : Initial Draft
Author		    : 
Created		    : 2013/06/20
Description	    : ������Դ���ļ������Ϊ�û��������������ڴ�
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
* func		: sample_dec_filein_phymemout
* description: CNcomment: �ļ��������������ڴ����  CNend\n
* param[in]	: *pFileName		CNcomment:Ҫ������ļ�	  CNend\n
* retval 	: NA
* others:	: NA
*****************************************************************************/
HI_VOID sample_dec_filein_phymemout(HI_CHAR *pFileName)
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
        HI_JPEG_INFO_S stJpegInfo;
	
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
	    jpeg_stdio_src(&cinfo, pInFile);

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

		
        stJpegInfo.bOutInfo = HI_TRUE;
		s32Ret = HI_JPEG_GetJpegInfo(&cinfo,&stJpegInfo);

        u32Width   = stJpegInfo.u32Width[0];
		u32Height  = stJpegInfo.u32Height[0];
		u32Stride  = stJpegInfo.u32OutStride[0];
        u32MemSize = stJpegInfo.u32OutSize[0];
			

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

		/**
		 **����ط�����������������ڴ棬���û������Ƿ�ˢcach,�ڲ�
		 **TDEת��ֱ��ת�������ڴ棬û�ж������ڴ�������
		 **/
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
			 sample_dec_filein_phymemout(pFileName);
		}

		closedir(dir);

		Display_DeInit();

		return 0;
}
