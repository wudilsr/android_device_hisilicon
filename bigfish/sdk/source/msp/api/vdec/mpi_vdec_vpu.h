/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_vdec_vpu.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/12/30
  Description   : Definitions for vdec driver
  History       :
  1.Date        : 2013/12/30
    Author      : l00225186
    Modification: Created file

*******************************************************************************/

#ifndef __HI_MPI_VDEC_VPU_H__
#define __HI_MPI_VDEC_VPU_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/******************************* Include Files *******************************/
#include "hi_drv_vdec.h"



#define  VPU_VERSION_NUM       2015011000  // VPU�İ汾��


/****************************** Macro Definition *****************************/
#define VPU_MAX_CHAN_NUM      4
#define VPU_ENC_TIMEOUT       5000 
#define VDEC_VPU_DEC_TIMEOUT  300
#define VPU_WAIT_TIME_OUT     10
#define VPU_MAX_FRAME_NUM     31
#define VPU_FMW_BIN_SIZE      (1024*1024)
#define VPU_ALIGN_LEN         (256) 
#define VPU_FBUF_MMZ_MAX      (180*1024*1024)
#define VPU_STREAM_BUF_SIZE   (10*1024*1024)
#define VPU_FHD_WIDTH         1920
#define VPU_FHD_HEIGHT        1080
#define VPU_EXTRA_FRM_NUM     5
#define VPU_MAIN_PROFILE_8BIT 8
#define VPU_EMPTY_COUNT       5
#define VPU_HEVC              1
#define VPU_PERCENTAGE        100  // add by w00278582

#define VPU_STR_BUF_INSUFFICIENT          0x2222  /*!<<  ����BUFF������ */
#define VPU_STR_BUF_INSUFFICIENT_SUCESS   0x2223  /*!<<  ����BUFF�����㣬����ɹ� */ 
#define VPU_STR_BUF_INSUFFICIENT_FAILURE  0x2224  /*!<<  ����BUFF�����㣬����ʧ�� */

#define VPU_LOCK(Mutex)        pthread_mutex_lock(&Mutex)
#define VPU_UNLOCK(Mutex)      pthread_mutex_unlock(&Mutex)

#define VPU_CHAN_CHECK(hInst) \
do { \
       if (hInst >= VPU_MAX_CHAN_NUM)  \
       {\
            HI_ERR_VDEC("%s ->:line:%d hInst %d is not valid\n", __FUNCTION__,__LINE__,hInst);\
            return HI_FAILURE;\
       }\
}while(0)

#define VPU_ASSERT_EQ(value, ret) \
do { \
      if (value != ret)  \
      {\
           HI_ERR_VDEC("%s ->:line:%d value %d != ret %d\n", __FUNCTION__,__LINE__,value,ret);\
           return HI_FAILURE;\
      }\
}while(0)

#define VPU_DECODE_ASSERT(value, ret, flag) \
do { \
      if (value != ret)  \
      {\
           HI_ERR_VDEC("%s ->:line:%d value %d != ret %d\n", __FUNCTION__,__LINE__,value,ret);\
           if (flag) {\
                return VPU_STR_BUF_INSUFFICIENT_FAILURE;\
           	}\
           	else { \
                return HI_FAILURE;\
      		}\
      }\
}while(0)

#define VPU_RET_CHECK(value, ret, flag) \
do { \
      if (HI_SUCCESS == value)  \
      {\
           ret = flag? VPU_STR_BUF_INSUFFICIENT_SUCESS: HI_SUCCESS;\
      }\
      else \
      {\
           ret = flag? VPU_STR_BUF_INSUFFICIENT_FAILURE: HI_FAILURE;\
      }\
}while(0)


/*************************** Structure Definition ****************************/
/**  VPU interrupt reason
**/
typedef enum
{
  VPU_INT_INIT_VPU          = 0,
  VPU_INT_DEC_PIC_HDR       = 1,
  VPU_INT_FINI_SEQ          = 2,
  VPU_INT_DEC_PIC           = 3,
  VPU_INT_SET_FRAMEBUF      = 4,
  VPU_INT_FLUSH_DEC         = 5,
  VPU_INT_GET_FW_VERSION    = 9,
  VPU_INT_QUERY_DEC         = 10,
  VPU_INT_SLEEP_VPU         = 11,
  VPU_INT_WAKEUP_VPU        = 12,
  VPU_INT_CHANGE_INT        = 13,       
  VPU_INT_BSBUF_EMPTY       = 14,   /*!<< Bitstream buffer empty */
  VPU_INT_CREATE_INSTANCE   = 15, 
}VPU_INT_REASON_E;

/**  VPU extended command
**/
typedef enum 
{
    VPU_CMD_CHECKEVT = 0,       /**< The param is VDEC_EVENT_S* */
    VPU_CMD_GETCHANSTATUSINFO,  /**< The param is VDEC_STATUSINFO_S* */
    VPU_CMD_READNEWFRAME,       /**< The param is HI_DRV_VIDEO_FRAME_S* */
    VPU_CMD_SETFRAMERATE,       /**< The param is HI_UNF_AVPLAY_FRMRATE_PARAM_S* */
    VPU_CMD_GETFRAMERATE,       /**< The param is HI_UNF_AVPLAY_FRMRATE_PARAM_S* */
    VPU_CMD_SETSTREAMENDFLAG,   /**< The param is HI_U32* */
    VPU_CMD_FIllRAWPACKAGE,     /**< The param is HI_U32* */
    VPU_CMD_SETBITSTREAMMODE,     /**< The param is HI_U32* */
    VPU_CMD_GETSTREAMBUFSTATUS, /**< The param is HI_U32* */
    VPU_CMD_SETWAITESTIME,        /**< The param is HI_U32* */
}VPU_CMD_E;


/**  VPU error type
**/
typedef enum hiVPU_PLAYFAIL_S
{    
    VPU_MEMORY_INSUFFICIENT 	= 1, 
	VPU_ERR_INTERRPUTION 		= 2,   
    VPU_MAIN_PROFILE_NOT_8BIT   = 3,   
} VPU_PLAY_FAIL_REASEN_S;

/**  VPU event 
**/
typedef struct hiVPU_EVENT_S
{    
    HI_BOOL  				bResolutionChanged;
	HI_U32                  u32Width;
	HI_U32                  u32Height;
	HI_BOOL					bDecErr;
	VPU_PLAY_FAIL_REASEN_S 	VpuDecFailReason;
    HI_U32    				u32ErrRatio;    //��¼����һ֡�д���ĺ����� 0~100
} VPU_EVENT_S;
/**  VPU instance status
**/
typedef enum 
{
    VPU_STATE_OPEN = 0, 
    VPU_STATE_RUN, 
    VPU_STATE_STOP, 
    VPU_STATE_CLOSE, 
    VPU_STATE_BUTT
}VPU_CHAN_STATE_E;


/**  VPU capability mode
**/
typedef enum 
{
    VPU_CAP_NORMAL = 0, 
    VPU_CAP_ISINGLE, 
    VPU_CAP_BUTT
}VPU_CAP_MODE_E;


/**  VPU decode mode
**/
typedef enum 
{
    VPU_DEC_IPB = 0, 
    VPU_DEC_IP, 
    VPU_DEC_I, 
    VPU_DEC_DSICARD, 
    VPU_DEC_BUTT
}VPU_DEC_MODE_E;

/**  VPU skip mode
**/
typedef enum 
{
    VPU_SKIP_NOTHING = 0, 
    VPU_SKIP_P_B, 
    VPU_SKIP_B, 
    VPU_SKIP_ALL, 
    VPU_SKIP_BUTT
}VPU_SKIP_MODE_E;

typedef struct hiVPU_STREAM_BUF_STATUS_S
{	
	HI_BOOL bStreamBufSuccfient;
}VPU_STREAM_BUF_STATUS_S;


/***************************** Function Definition ***************************/
/**
brief      : get the vpu Codec. CNcomment:��ȡVPU���������� CNend
attention  :
param[in]  : 
retval     : HI_CODEC_S
see        :
*/
HI_CODEC_S* VDEC_VPU_Codec(HI_VOID);

/**
brief     : get the vpu Codec Capability. CNcomment:��ȡVPU�������������� CNend
attention :
param[in] : HI_CODEC_CAP_S *
param[out]: HI_CODEC_CAP_S
retval    : 
see       :
*/
HI_S32 HI_VPU_GetCap(HI_CODEC_CAP_S *pstCodecCap);

/**
brief     : Create vpu Codec. CNcomment:����VPU������ CNend
attention :
param[in] : HI_CODEC_OPENPARAM_S * 
retval    : HI_HANDLE*
see       :
*/
HI_S32 HI_VPU_Create(HI_HANDLE *phInst, const HI_CODEC_OPENPARAM_S * pstParam);

/**
brief     : destroy vpu Codec. CNcomment:����VPU������ CNend
attention :
param[in] : HI_HANDLE* 
retval    : 
see       :
*/
HI_S32 HI_VPU_Destroy(HI_HANDLE hInst);

/**
brief     : start vpu Codec. CNcomment:����VPU������ CNend
attention :
param[in] : HI_HANDLE 
retval    : 
see       :
*/
HI_S32 HI_VPU_Start(HI_HANDLE phInst);

/**
brief     : stop vpu Codec. CNcomment:ֹͣVPU������ CNend
attention :
param[in] : HI_HANDLE* 
retval    : 
see       :
*/
HI_S32 HI_VPU_Stop(HI_HANDLE phInst);

/**
brief     : reset vpu Codec. CNcomment:��λVPU������ CNend
attention :
param[in] : HI_HANDLE* 
retval    : 
see       :
*/
HI_S32 HI_VPU_Reset(HI_HANDLE phInst);

/**
brief     : set vpu Codec attribute. CNcomment:����VPU���������� CNend
attention :
param[in] : HI_HANDLE
param[in] : HI_CODEC_ATTR_S*
retval    : 
see       :
*/
HI_S32 HI_VPU_SetAttr(HI_HANDLE hInst, const HI_CODEC_ATTR_S* pstAttr);
/**
brief     : get vpu Codec attribute. CNcomment:��ȡVPU���������� CNend
attention :
param[in] : HI_HANDLE
param[out]: HI_CODEC_ATTR_S*
retval    : 
see       :
*/
HI_S32 HI_VPU_GetAttr(HI_HANDLE hInst, HI_CODEC_ATTR_S* pstAttr);

/**
brief     : use vpu Codec decode frame. CNcomment:ʹ��VPU���������� CNend
attention : H265 only
param[in] : HI_HANDLE
retval    : 
see       :
*/
HI_S32 HI_VPU_DecodeFrame(HI_HANDLE hInst, HI_CODEC_STREAM_S * pstIn, HI_CODEC_FRAME_S * pstOut);

/**
brief     : register frame buffer to  vpu Codec. CNcomment:��VPU������ע��֡��CNend
attention : H265 only
param[in] : HI_HANDLE
param[in] : HI_CODEC_FRAME_BUF_S * 
param[in] : HI_U32
retval    : 
see       :
*/
HI_S32 HI_VPU_RegFrameBuffer(HI_HANDLE hInst, HI_CODEC_STREAM_S *pstRawPacket);

/**
brief     : get stream information . CNcomment:��ȡ������Ϣ CNend
attention : H265 only
param[in] : HI_HANDLE
param[out]: HI_CODEC_STREAMINFO_S *
retval    : 
see       :
*/
HI_S32 HI_VPU_GetStreamInfo(HI_HANDLE hInst, HI_CODEC_STREAMINFO_S * pstAttr);

/**
brief     : close vpu dev . CNcomment:�ر�VPU�豸 CNend
attention : H265 only
retval    : 
see       :
*/
HI_S32 VDEC_CloseVPU();


/**
brief     : create frame list . CNcomment:����������֡������� CNend
attention : 
retval    : 
see       :
*/
HI_S32 HI_VDEC_PutFrame(HI_HANDLE hVdec,HI_DRV_VDEC_USR_FRAME_S *pstBuf);

HI_S32 HI_VDEC_CheckFreeFrameBufferId(HI_HANDLE hVdec,HI_S32 *s32FrameIdArray);

HI_S32 HI_VDEC_DestroyFrameList(HI_HANDLE hVdec);

HI_S32 HI_VPU_Control(HI_HANDLE hVpuInst, HI_U32 u32CMD, HI_VOID * pParam);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MPI_VDEC_VPU_H__ */

