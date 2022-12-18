/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : hi_jpeg_drv_api.h
Version		    : Initial Draft
Author		    : 
Created		    : 2015/03/01
Description	    : the jpeg api use the hal information get from this file
                  CNcomment: jpegӦ�ò�ʹ�õ������Ϣ�Ӹ��ļ��л�ȡ CNend\n
Function List 	:
History       	:
Date				Author        		Modification
2015/03/01		    y00181162  		    Created file      	
******************************************************************************/


#ifndef __HI_JPEG_HAL_API_H__
#define __HI_JPEG_HAL_API_H__


/*********************************add include here******************************/
#include "hi_type.h"


/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" 
{
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ******************************/
	#define VID_CMD_MAGIC     'j' 

	#define CMD_JPG_GETDEVICE                _IO(VID_CMD_MAGIC,    0x0)
	#define CMD_JPG_OPEN_RESET_CLOCK         _IO(VID_CMD_MAGIC,    0x1)
	
	#define CMD_JPG_SUSPEND                  _IO(VID_CMD_MAGIC,   0x3)
	#define CMD_JPG_RESUME                   _IO(VID_CMD_MAGIC,   0x4)
	#define CMD_JPG_GETSUSPEND               _IO(VID_CMD_MAGIC,   0x5)
	#define CMD_JPG_GETRESUME                _IO(VID_CMD_MAGIC,   0x6)

	#define CMD_JPG_RESET                    _IO(VID_CMD_MAGIC,   0x7)
	#define CMD_JPG_CANCEL_RESET             _IO(VID_CMD_MAGIC,   0x8)
	
#ifdef CHIP_TYPE_X5HD_hi3716m
	#define CMD_JPG_GETSIGNAL_ID             _IOWR(VID_CMD_MAGIC, 0x9, int)
	#define CMD_JPG_GETINTSTATUS             _IOWR(VID_CMD_MAGIC, 0x2,  JPG_GETINTTYPE_S*)
#else
	#define CMD_JPG_GETSIGNAL_ID             _IOWR(VID_CMD_MAGIC, 0x2, int)
	#define CMD_JPG_GETINTSTATUS             _IOWR(VID_CMD_MAGIC, 0x9,  JPG_GETINTTYPE_S)
#endif
	#define CMD_JPG_GETRESUMEVALUE           _IOWR(VID_CMD_MAGIC, 0x10, unsigned int)
	
	#define CMD_JPG_READPROC                 _IOWR(VID_CMD_MAGIC, 0x11,  HI_JPEG_PROC_INFO_S)

    #define CMD_JPG_CREATEDEC                _IOWR(VID_CMD_MAGIC, 0x12,  HI_S32)
    #define CMD_JPG_DECINFO                  _IOWR(VID_CMD_MAGIC, 0x13,  HI_DRV_JPEG_INMSG_S)
    #define CMD_JPG_DECOUTINFO               _IOWR(VID_CMD_MAGIC, 0x14,  HI_DRV_JPEG_OUTMSG_S)
    #define CMD_JPG_DECODE                   _IOWR(VID_CMD_MAGIC, 0x15,  HI_JPEG_DECINFO_S)
    #define CMD_JPG_DESTORYDEC               _IOWR(VID_CMD_MAGIC, 0x16,  HI_S32)
    #define CMD_JPG_GETLUPIXSUM              _IOWR(VID_CMD_MAGIC, 0x17,  HI_DRV_JPEG_OUTMSG_S)
    #define CMD_JPG_SETMEMTYPE               _IOWR(VID_CMD_MAGIC, 0x18,  HI_DRV_JPEG_INMSG_S)
    
    #define MAX_COMPONENT_NUM                3
    
    /*************************** Structure Definition ****************************/
	/** halt state types **/
	typedef enum hiJPG_INTTYPE_E
	{
	
		JPG_INTTYPE_NONE       = 0,	       /** none halt happen	    **/
		JPG_INTTYPE_CONTINUE,	               /** continue stream halt **/
		JPG_INTTYPE_FINISH, 	               /** finish halt		    **/
		JPG_INTTYPE_ERROR,		               /** error halt 		    **/
		JPG_INTTYPE_BUTT
	}JPG_INTTYPE_E;

    typedef enum hiJPG_FMT_E
	{
		JPG_FMT_YUV400	       = 0,   /**< yuv400     */
		JPG_FMT_YUV420	       = 1,   /**< yuv420     */
		JPG_FMT_YUV422_21    = 2,   /**< yuv422_21  */
		JPG_FMT_YUV422_12    = 3,   /**< yuv422_12  */
		JPG_FMT_YUV444	       = 4,   /**< yuv444     */
		JPG_FMT_YCCK   	   = 5,   /**< YCCK       */
		JPG_FMT_CMYK   	   = 6,   /**< CMYK       */
		JPG_FMT_BUTT	
	}JPG_FMT_E;
    
	/** get halt state struct **/
	typedef struct hiJPG_GETINTTYPE_S
	{
	
		JPG_INTTYPE_E IntType;	  /** halt type **/
		unsigned int TimeOut; 	  /** overtime	**/
		
	}JPG_GETINTTYPE_S;

	
 	/** structure of jpeg decode state */
    /** CNcomment:jpeg����״̬         */
	typedef enum hiJPEG_DEC_STATE_E
    {
        JPEG_DEC_FINISH_CREATE_DECOMPRESS  = 0, /**< create decompress finish   *//**<CNcomment:��������������  */
        JPEG_DEC_FINISH_STDIC               = 1, /**< stdio the stream  finish   *//**<CNcomment:������������    */
        JPEG_DEC_FINISH_READ_HEADER        = 2,  /**< read header file finish   *//**<CNcomment:�����ļ�����    */
        JPEG_DEC_FINISH_START_DECOMPRESS   = 3, /**< start decompress finish    *//**<CNcomment:�������        */
        JPEG_DEC_FINISH_READ_SCANLINES     = 4, /**< read scanlines   finish    *//**<CNcomment:�������        */
        JPEG_DEC_FINISH_FINISH_DECOMPRESS  = 5, /**< finish decompress finish   *//**<CNcomment:��ɽ���        */
        JPEG_DEC_FINISH_DESTORY_DECOMPRESS = 6, /**< destory decompress finish  *//**<CNcomment:���ٽ���������  */
        JPEG_DEC_SUCCESS                     = 7, /**< decode success             *//**<CNcomment:����ɹ�        */
        JPEG_DEC_STATE_BUTT
    }HI_JPEG_DEC_STATE_E;

 	/** structure of jpeg decode type                  */
    /** CNcomment:jpeg�������ͣ���Ӳ�����뻹��������� */
	typedef enum hiJPEG_DEC_TYPE_E
    {
    
        JPEG_DEC_HW = 0,    /**< hard decode   *//**<CNcomment:Ӳ������  */
        JPEG_DEC_SW = 1,    /**< soft decode   *//**<CNcomment:�������  */
        JPEG_DEC_BUTT
    }HI_JPEG_DEC_TYPE_E;

	
	typedef struct hiJPG_SAVEINFO_S
	{
		HI_U32	 u32ResumeData0;
		HI_U32	 u32ResumeData1;
		HI_U32	 u32ResBitRemain;
		HI_U32	 u32ResByteConsu;
		HI_U32	 u32ResMcuy;
		HI_U32	 u32Pdy;
		HI_U32	 u32Pdcbcr;
        HI_U32   u32DriCnt;
	}HI_JPG_SAVEINFO_S;

	/** structure of the proc information��the user need proc, 
	 ** echo proc on and we need echo proc on and then echo trace on **/
    /** CNcomment:proc��Ϣ�ṹ�壬ֻ���û��ṩ��ֻ��Ҫecho proc on��Ҫ��
     ** Ҫ���Լ�����ֻҪ��echo proc on Ȼ�� echo trace on **/
    typedef struct hiJPEG_PROC_INFO_S
    {
         /** our need proc information */
		 /** CNcomment:�Լ��ĵ�����Ϣ  */
		 HI_U32  u32YWidth;         /**< the lu width       *//**<CNcomment:���ȿ��� */
		 HI_U32  u32YHeight;        /**< the lu height      *//**<CNcomment:���ȸ߶�   */
		 HI_U32  u32YSize;          /**< the lu size        *//**<CNcomment:���ȴ�С   */
		 HI_U32  u32CWidth;         /**< the ch width       *//**<CNcomment:ɫ�ȿ��   */
		 HI_U32  u32CHeight;        /**< the ch height      *//**<CNcomment:ɫ�ȸ߶�   */
		 HI_U32  u32CSize;          /**< the ch size        *//**<CNcomment:ɫ�ȴ�С   */
		 HI_U32  u32YStride;        /**< the lu stride      *//**<CNcomment:�����м�� */
		 HI_U32  u32CbCrStride;     /**< the ch stride      *//**<CNcomment:ɫ���м�� */
		 HI_U32  u32DisplayW;       /**< the display width  *//**<CNcomment:��ʾ���   */
		 HI_U32  u32DisplayH;       /**< the display height *//**<CNcomment:��ʾ�߶�   */
         HI_U32  u32DisplayStride;  /**< the display stride *//**<CNcomment:��ʾ�м��  */
		 HI_U32  u32DecW;           /**< the dec width      *//**<CNcomment:������    */
		 HI_U32  u32DecH;           /**< the dec height     *//**<CNcomment:����߶�    */
		 HI_U32  u32DecStride;      /**< the dec stride     *//**<CNcomment:�����м��  */
		 HI_U32  u32DataStartAddr;  /**< the stream start address     *//**<CNcomment:����buffer��ʼ��ַ��Ҫ64�ֽڶ���      */
		 HI_U32  u32DataEndAddr;    /**< the stream end address       *//**<CNcomment:����buffer������ַ��Ҫ64�ֽڶ���      */
		 HI_U32  u32SaveStartAddr;  /**< the save data start address  *//**<CNcomment:�洢��������ʼ��ַ(��������ַ������)  */
		 HI_U32  u32SaveEndAddr;    /**< the save data end address    *//**<CNcomment:�洢�����Ľ�����ַ(��������ַ������)  */
         /** user need proc information */
		 /** CNcomment:�û��뿴������Ϣ */
		 HI_U32 u32InWidth;             /**< the input widht             *//**<CNcomment:������      */
         HI_U32 u32InHeight;            /**< the input height            *//**<CNcomment:����߶�      */
         HI_U32 u32OutWidth;            /**< the output width            *//**<CNcomment:������      */
         HI_U32 u32OutHeight;           /**< the output height           *//**<CNcomment:����߶�      */
		 HI_U32 u32OutStride;           /**< the output stride           *//**<CNcomment:����м��    */
         HI_U32 u32InFmt;               /**< the input format            *//**<CNcomment:�������ظ�ʽ  */
		 HI_U32 u32OutFmt;              /**< the output format           *//**<CNcomment:������ظ�ʽ  */
         HI_U32 u32OutPhyBuf;           /**< the output physics address  *//**<CNcomment:��������ַ  */
		 HI_U32 u32Scale;               /**< the decode scale            *//**<CNcomment:�������ű���  */
		 HI_JPEG_DEC_STATE_E eDecState; /**< the decode state            *//**<CNcomment:����״̬      */
         HI_JPEG_DEC_TYPE_E eDecodeType;/**< the decode type             *//**<CNcomment:��������      */
		 
    }HI_JPEG_PROC_INFO_S;

    
    typedef struct tagJPEG_INMSG_S
	{/** ����ṹ��Ҫ���û�̬hi_jpeg_api.h�еĽṹ�屣��һ�� **/
		 HI_CHAR* pAllPhy;           /** ��������buffer����ʼ�����ַ **/
         HI_CHAR* pSavePhy;          /** ��һ��������������ַ       **/
		 HI_CHAR* pSaveVir[2];       /** �������������ַ���ڶ��������ַ����������buffer�������ַ��Ӧ **/
         HI_U32   u32AllLen;         /** ��������buffer�ĳ���         **/
         HI_U32   u32SaveLen[2];     /** ������������buffer�Ĵ�С     **/
         HI_U32   s32InWidth;        /** ����ͼ���                   **/
		 HI_U32   s32InHeight;       /** ����ͼ���                   **/
         HI_U32   u32DecHandle;      /** ������                       **/
         HI_U32   u32MemMask;		 /** ʹ�õ��ڴ�����               **/
         HI_BOOL  bUserPhyMem;       /** �Ƿ����Ϊ�����ַ         **/
         JPG_FMT_E enInFmt;          /** ����ͼ�����ظ�ʽ             **/
	}HI_DRV_JPEG_INMSG_S;

    typedef struct tagJPEG_OUTMSG_S
	{/** ����ṹ��Ҫ���û�̬hi_jpeg_api.h�еĽṹ�屣��һ�� **/
		 HI_CHAR* pOutPhy[MAX_COMPONENT_NUM];
         HI_U32   u32OutWidth[MAX_COMPONENT_NUM];
		 HI_U32   u32OutHeight[MAX_COMPONENT_NUM];
         HI_U32   u32OutStride[MAX_COMPONENT_NUM];
         HI_U32   u32OutSize[MAX_COMPONENT_NUM];   /** �ڴ�����uv��ַƫ��ʹ�����ֵ **/
         HI_S32   s32Scale;                        /** only support 1-2-4-8 **/
         HI_U32   u32DecHandle;                    /** ������               **/
         HI_U64   u64LuPixValue;
         HI_BOOL  bOutYuvSp420;
         HI_BOOL  bLuPixSum;
         JPG_FMT_E enOutFmt;
	}HI_DRV_JPEG_OUTMSG_S;
    
    typedef struct hiJPEG_DECINFO_S
	{
		 HI_DRV_JPEG_INMSG_S  stInMsg;
         HI_DRV_JPEG_OUTMSG_S stOutMsg;
	}HI_JPEG_DECINFO_S;
    
    /********************** Global Variable declaration **************************/
 
    /******************************* API declaration *****************************/

	/***************************************************************************
    * func          : HI_DRV_JPEG_Open
    * description   : open jpeg dev.
                      CNcomment: ��jpeg�豸 CNend\n
    * retval        : HI_SUCCESS �ɹ�
    * retval        : HI_FAILURE ʧ��
    * others:       : NA
    ****************************************************************************/
    HI_S32 HI_DRV_JPEG_Open(HI_VOID);

    /***************************************************************************
    * func          : HI_DRV_JPEG_Close
    * description   : close jpeg dev.
                      CNcomment: �ر�jpeg�豸 CNend\n
    * others:       : NA
    ****************************************************************************/
    HI_VOID HI_DRV_JPEG_Close(HI_VOID);

    /***************************************************************************
    * func          : HI_DRV_JPEG_CreateDec
    * description   : ctreate jpeg decoder.
                      CNcomment: ���������� CNend\n
    * param[in]     : *pu32Handle
    * retval        : HI_SUCCESS �ɹ�
    * retval        : HI_FAILURE ʧ��
    * others:       : NA
    ****************************************************************************/
    HI_S32 HI_DRV_JPEG_CreateDec(HI_U32 *pu32Handle);

	/***************************************************************************
    * func          : HI_DRV_JPEG_SetDecMemType
    * description   : ���ý������ڴ�ʹ������.
                      CNcomment: ���������� CNend\n
    * param[in]     : u32Handle
    * param[in]     : u32MemTypeMask
    * retval        : HI_SUCCESS �ɹ�
    * retval        : HI_FAILURE ʧ��
    * others:       : NA
    ****************************************************************************/
    HI_S32 HI_DRV_JPEG_SetDecMemType(HI_U32 u32Handle,HI_U32 u32MemTypeMask);
	
    
    /***************************************************************************
    * func          : HI_DRV_JPEG_DecInfo
    * description   : get jpeg input infomation.
                      CNcomment: ��ȡͼƬ������Ϣ CNend\n
    * param[in]     : u32Handle
    * param[in]     : *stInMsg
    * retval        : HI_SUCCESS �ɹ�
    * retval        : HI_FAILURE ʧ��
    * others:       : NA
    ****************************************************************************/
    HI_S32 HI_DRV_JPEG_DecInfo(HI_U32 u32Handle,HI_DRV_JPEG_INMSG_S *stInMsg);
    
    /***************************************************************************
    * func          : HI_DRV_JPEG_DecOutInfo
    * description   : get jpeg output infomation.
                      CNcomment: ��ȡͼƬ�����Ϣ CNend\n
    * param[in]     : u32Handle
    * param[in]     : *stOutMsg
    * retval        : HI_SUCCESS �ɹ�
    * retval        : HI_FAILURE ʧ��
    * others:       : NA
    ****************************************************************************/
    HI_S32 HI_DRV_JPEG_DecOutInfo(HI_U32 u32Handle,HI_DRV_JPEG_OUTMSG_S *stOutMsg);

    /***************************************************************************
    * func          : HI_DRV_JPEG_DecFrame
    * description   : dec one frame.
                     CNcomment: ����һ֡ͼƬ CNend\n
    * param[in]     : u32Handle
    * param[in]     : *stInMsg
    * param[in]     : *stOutMsg
    * retval        : HI_SUCCESS �ɹ�
    * retval        : HI_FAILURE ʧ��
    * others:       : NA
    ****************************************************************************/
    HI_S32 HI_DRV_JPEG_DecFrame(HI_U32 u32Handle,HI_DRV_JPEG_INMSG_S *stInMsg,HI_DRV_JPEG_OUTMSG_S *stOutMsg);

    /***************************************************************************
    * func          : HI_DRV_JPEG_DestoryDec
    * description   : destory decode.
                      CNcomment: ���ٽ����� CNend\n
    * param[in]     : u32Handle
    * retval        : HI_SUCCESS �ɹ�
    * retval        : HI_FAILURE ʧ��
    * others:       : NA
    ****************************************************************************/
    HI_S32 HI_DRV_JPEG_DestoryDec(HI_U32 u32Handle);

	/***************************************************************************************
	* func			: HI_DRV_JPEG_GetLuPixSum
	* description	: get lu pix sum
					  CNcomment: ��ȡ����ֵ�� CNend\n
	* param[in] 	: u32Handle
	* retval		:
	* retval		:
	* others:		: NA
	***************************************************************************************/
	HI_VOID HI_DRV_JPEG_GetLuPixSum(HI_U32 u32Handle,HI_U64* pu64LuPixValue);
	
    /****************************************************************************/



#ifdef __cplusplus
    
#if __cplusplus
   
}
#endif
#endif /* __cplusplus */

#endif /* __HI_JPEG_HAL_API_H__*/
