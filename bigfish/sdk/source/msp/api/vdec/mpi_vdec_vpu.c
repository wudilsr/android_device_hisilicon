/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_vdec_vpu.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/12/30
  Description   : Implement for vdec driver
  History       :
  1.Date        : 2013/12/30
    Author      : l00225186
    Modification: Created file

*******************************************************************************/

/******************************* Include Files *******************************/
/* Sys headers */
#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>
#include <sys/ioctl.h>
#include <pthread.h>

/* Unf headers */
#include "hi_video_codec.h"

/* Mpi headers */
#include "hi_error_mpi.h"
#include "hi_mpi_mem.h"
#include "mpi_vdec_vpu.h"
#include "mpi_vdec_vpu_fmw.h"
#include "mpi_vdec_adapter.h"
#include "hi_math.h"

/*Mpi VPU headers*/
#include "vpuapi.h"
#include "vpuapifunc.h"
#include "hi_video_codec.h"
#include "hi_unf_video.h"

/*Mpi drv headers*/
#include "hi_drv_vdec.h"
#include "mpi_vdec_adapter.h"
#include "hi_common.h"

#include <coda9/coda9_regdefine.h>
#include <coda9/coda9_vpuconfig.h>
#include <wave4/wave4_regdefine.h>
#include <wave4/wave4_vpuconfig.h>
#include <vpuerror.h>

/************************ Static Structure Definition ************************/
#define TEST_SEQUENCE_CHANGE_SUPPORT
//#define OUTPUT_DecInfo
//#define SAVE_Stream
//#define SAVE_YUV
//#define FRM_BUF_STATE
//#define VFMW_BIN_LOAD
//#define VPU_BUF_FULL_AVOID
//#define VPU_ResetTime_Statistics_SUPPORT
#define ALLOC_MEM_FRAME_BY_FRAEM
#define VPU_EVENTS_TEST
HI_U32 g_time[5];

/*****************************************************************************/


/*****************************************************************************
 *                           数据结构                                        *
 *****************************************************************************/
typedef struct hiVPU_DEC_FRM_BUF_INFO_S
{
    vpu_buffer_t  vbFrame;
    vpu_buffer_t  vbWTL;
    vpu_buffer_t  vbFbcYTbl;     /*!<< FBC Luma offset table   */
    vpu_buffer_t  vbFbcCTbl;     /*!<< FBC Chroma offset table */
    FrameBuffer   framebufPool[64];
} VPU_DEC_FRM_BUF_INFO_S;

typedef struct hiVPU_SEQ_CHANGE_PARM_S
{
	HI_BOOL    bSeqChanged;
	HI_BOOL    bAllFrameRevertByVpss;
	HI_BOOL    bAllFramePutToVpss;
	HI_U32     retNum;            /*!<< 发生变分辨率时，记录已解码还未输出的帧   */
	HI_U32     u32FlushedNum;
	VPU_DEC_FRM_BUF_INFO_S PrevFb;
	DecOutputInfo  pDecOutInfo[VPU_MAX_FRAME_NUM];
}VPU_SEQ_CHANGE_PARM_S;


typedef struct hiVPU_PTS_QUEUE_NODE_S
{
	HI_CODEC_STREAM_S RawPacket;
	struct VPU_PTS_QUEUE_NODE_S *next;
}VPU_PTS_QUEUE_NODE_S;

typedef struct tagVPU_PTS_QUEUE_S
{
	HI_U32 u32BufStart ;        /*!<< 码流buf的首地址(物理地址) */
	HI_U32 u32BufEnd ;          /*!<< 码流buf的结束地址(物理地址) */
	HI_U32 u32LastDecReadPtr;   /*!<< 记录上一次解码成功的读指针 */
	HI_U32 u32RawPackOffset;    /*!<< 记录当前读指针所在包的偏移 */
	HI_S64 s64LastDecPts;       /*!<< 记录前一个解码帧的pts值 */
	HI_S64 s64LastValidRawPts;  /*!<< 记录最近一个Raw包的pts值 */
	VPU_PTS_QUEUE_NODE_S *pHead;
	VPU_PTS_QUEUE_NODE_S *pRear;
}VPU_PTS_QUEUE_S;

typedef struct hiVPU_DEC_FRAME_BUF_S
{	
	HI_BOOL bUsed;
	HI_S64  s64pts;
	FrameBuffer stLinearBuf;
}VPU_DEC_FRAME_BUF_S;

typedef struct hiVPU_DISP_FRAME_BUF_S
{	
	HI_BOOL bPutToVpss;
	HI_U32  u32Index;
}VPU_DISP_FRAME_BUF_S;

typedef struct hiVPU_GET_LAST_FRAME_BUF_S
{	
	HI_BOOL bLastEmptyInterruption;
	HI_U32  u32EmptyInterruptionCounts;
}VPU_GET_LAST_FRAME_BUF_S;
#ifdef ALLOC_MEM_FRAME_BY_FRAEM
typedef struct hiVPU_ALLOCED_FRAME_BUF_S
{	
	HI_BOOL       bAllocFromVdh;
	HI_MMZ_BUF_S  stMmzBuf;
}VPU_ALLOCED_FRAME_BUF_S;
#endif

typedef struct hiVPU_CHAN_S
{
    HI_BOOL  bRegFrameBuffer;
    HI_BOOL  bStartDecSeqFlag;
    HI_BOOL  bIsNotSupport;      /*!<< 由于内存资源的限制，目前只支持总帧存(BufSize < 135M, RefNum < 5) */    
    HI_BOOL  bStartDecPicFlag;
    HI_BOOL  bResolutionChanged;  //解码图像宽高发生变化
    HI_BOOL  bWaitEsTimeOut;      //用于DVB直播时，判断积累的码流时间是否超时

    HI_U32   u32ChanId;
    HI_U32   u32hVdec;
    HI_U32   u32frameCount;
    HI_U32   u32MinRefFrameNum;
    HI_U32   u32EosFlag ;        /*!<< 2 Consume stream over*/
    HI_U32   u32ActualFrameNum;
    HI_U32   u32SarWidth;
    HI_U32   u32SarHeight;
    HI_U32   u32SarIndex;
    HI_U32   u32Profile;
    HI_U32   u32LumaBitdepth;
    HI_U32   u32ChromaBitdepth;
    HI_U32   u32TotalMemSize;
    HI_U32   u32IsFromDemux;
    HI_U32   u32BsLastTime;
    HI_U32   u32BsSizeOneSecond;
    HI_U32   u32BsRate;
    HI_U32   u32WaitEsTime;
    HI_S64   s64FirstValidRawPts; /*!<< 记录接收到的第一个有效的raw包pts信息 */
    HI_S64   s64NewDispFramePts; /*!<< 记录前一个显示帧的pts信息 */
    HI_U64   u64RecvPackSize;
    VPU_GET_LAST_FRAME_BUF_S stGetLastFrame;

#ifdef VPU_EVENTS_TEST
    VPU_EVENT_S stVpuEvents;
#endif
    DecHandle        pHandle;
    DecOpenParam       stOpenParam;
    DecOutputInfo        stLastDispOutInfo;
    HI_MMZ_BUF_S     stBitStreamBuf;
#ifdef ALLOC_MEM_FRAME_BY_FRAEM
    VPU_ALLOCED_FRAME_BUF_S stCompressFrmBuf[VPU_MAX_FRAME_NUM];
    VPU_ALLOCED_FRAME_BUF_S stLinearFrmBuf[VPU_MAX_FRAME_NUM];
#else
    HI_MMZ_BUF_S            stCompressFrmBuf[VPU_MAX_FRAME_NUM];
    HI_MMZ_BUF_S            stLinearFrmBuf[VPU_MAX_FRAME_NUM];
#endif

    VPU_PTS_QUEUE_S 		stPtsQueue;
    VPU_DEC_FRAME_BUF_S 	stDecFrmBuf[VPU_MAX_FRAME_NUM];
    VPU_DISP_FRAME_BUF_S    stDispFrmBuf[VPU_MAX_FRAME_NUM];  /*!<< 记录显示帧状态 */
    VPU_SEQ_CHANGE_PARM_S 	stSeqChangeParm;
    HI_U32                  u32SeqChangeCount;

    VPU_CHAN_STATE_E        eChanState;
    VPU_CAP_MODE_E          eCapMode;
    VPU_DEC_MODE_E          eDecMode;
    VPU_SKIP_MODE_E         eSkipMode;
    DecParam                stParam;


    HI_CODEC_OPENPARAM_S    stCodecParam;
    HI_CODEC_ATTR_S         stCodecAttr;

    pthread_mutex_t         stMutex; 

    FILE *fp2DYuv;          /*!<< for 2D YUV storage */
    FILE *fpStream;         /*!<< for stream storage */
}VPU_CHAN_CTX_S;


/*****************************************************************************
 *                         Global Definition                                 *
 *****************************************************************************/
VPU_CHAN_CTX_S g_VPUChanCtx[VPU_MAX_CHAN_NUM];


/*****************************************************************************
 *                         Static Definition                                 *
 *****************************************************************************/
static HI_CODEC_SUPPORT_S s_stCodecSupport = 
{
    .u32Type        = HI_CODEC_TYPE_DEC,
    .enID           = HI_CODEC_ID_VIDEO_HEVC,
    .pstNext        = HI_NULL
};

static HI_CODEC_S hi_codecVPU_entry =
{
    .pszName		= "VPU",
    .unVersion		= {.stVersion = {1, 0, 0, 0}},
    .pszDescription = "Hisilicon H265 codec",

    .GetCap			= HI_VPU_GetCap,
    .Create			= HI_VPU_Create,
    .Destroy		= HI_VPU_Destroy,
    .Start			= HI_VPU_Start,
    .Stop			= HI_VPU_Stop,
    .Reset			= HI_VPU_Reset,
    .SetAttr		= HI_VPU_SetAttr,
    .GetAttr		= HI_VPU_GetAttr,
    .DecodeFrame	= HI_VPU_DecodeFrame,
    .EncodeFrame	= HI_NULL,
    .RegFrameBuffer = HI_VPU_RegFrameBuffer,
    .GetStreamInfo	= HI_VPU_GetStreamInfo,
    .Control		= HI_VPU_Control,
};


/*****************************************************************************
 *                                Function                                   *
 *****************************************************************************/
// add by w00278582
HI_VOID HI_VPU_PROC_STATUS(VPU_CHAN_CTX_S *pChanCtx, DecOutputInfo *pstOutPutInfo);



/******************************************************************************
brief      : CNcomment: 获取VFMW版本号
attention  :
param[in]  : 
retval     : HI_VOID
see        :
******************************************************************************/
HI_VOID VDEC_VPU_CheckFMWVersion(HI_VOID)
{
    HI_U32 version = 0;
    HI_U32 revision = 0;
    HI_U32 productId = 0;
    HI_U32 core_idx = 0;

    VPU_GetVersionInfo(core_idx, &version, &revision, &productId);	

    HI_FATAL_VDEC("VPU coreNum : [%d]\n", core_idx);
    HI_FATAL_VDEC("Firmware Version => projectId : %x | version : %04d.%04d.%08d | revision : r%d\n", 
    	(HI_U32)(version>>16), (HI_U32)((version>>(12))&0x0f), (Uint32)((version>>(8))&0x0f), (Uint32)((version)&0xff), revision);
    HI_FATAL_VDEC("Hardware Version => %04x\n", productId);
    HI_FATAL_VDEC("API Version => %04x\n\n", API_VERSION);	
}

/******************************************************************************
brief      : CNcomment: 获取帧存个数，按分辨率来决策帧存的个数，待完善
attention  :
param[in]  : 
retval     : HI_VOID
see        :
******************************************************************************/
HI_VOID VDEC_VPU_GetActualFrameNum(VPU_CHAN_CTX_S *pChanCtx, DecInitialInfo *pstSeqInfo, HI_U32 *pActualFrmNum)
{
    if ((HI_NULL == pChanCtx) || (HI_NULL == pstSeqInfo) || (HI_NULL == pActualFrmNum))
    {
        HI_ERR_VDEC("FUN:%s,L:%d pChanCtx %p, pstSeqInfo %p, pActualFrmNum %p is NULL\n", __FUNCTION__, __LINE__, 
                          pChanCtx, pstSeqInfo, pActualFrmNum);
        return;
    }

    /** CNcomment: 记录实际的解码帧存个数
    **/
    if (VPU_CAP_ISINGLE == pChanCtx->eCapMode)
    {
        *pActualFrmNum = pstSeqInfo->minFrameBufferCount;
    }
    else
    {
        *pActualFrmNum = pstSeqInfo->minFrameBufferCount + 1; 
        if ((pstSeqInfo->picWidth < VPU_FHD_WIDTH) && (pstSeqInfo->picHeight < VPU_FHD_HEIGHT))
        {
            *pActualFrmNum = pstSeqInfo->minFrameBufferCount + VPU_EXTRA_FRM_NUM; 
        }
    }

    /** CNcomment: 记录实际的解码帧存个数
    **/
    pChanCtx->u32ActualFrameNum = *pActualFrmNum;

    return;
}

/******************************************************************************
brief      : CNcomment: 创建解码参数转换
attention  :
param[in]  : 
retval     : HI_VOID
see        :
******************************************************************************/
HI_VOID HI_VDEC_ConvertFormat(HI_CODEC_COLOR_FORMAT_E enCodecFormat, HI_UNF_VIDEO_FORMAT_E* penUNFFormt)
{
    if (HI_NULL == penUNFFormt)
    {
        HI_ERR_VDEC("FUN:%s,L:%d penUNFFormt is NULL\n", __FUNCTION__, __LINE__);
        return;
    }
    
    switch (enCodecFormat)
    {
    case HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_400:
        *penUNFFormt = HI_UNF_FORMAT_YUV_SEMIPLANAR_400;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_411:
        *penUNFFormt = HI_UNF_FORMAT_YUV_SEMIPLANAR_411;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_420:
        *penUNFFormt = HI_UNF_FORMAT_YUV_SEMIPLANAR_420;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_422_1X2:
        *penUNFFormt = HI_UNF_FORMAT_YUV_SEMIPLANAR_422_1X2;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_422_2X1:
        *penUNFFormt = HI_UNF_FORMAT_YUV_SEMIPLANAR_422;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_444:
        *penUNFFormt = HI_UNF_FORMAT_YUV_SEMIPLANAR_444;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_PLANAR_400:
        *penUNFFormt = HI_UNF_FORMAT_YUV_PLANAR_400;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_PLANAR_411:
        *penUNFFormt = HI_UNF_FORMAT_YUV_PLANAR_411;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_PLANAR_420:
        *penUNFFormt = HI_UNF_FORMAT_YUV_PLANAR_420;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_PLANAR_422_1X2:
        *penUNFFormt = HI_UNF_FORMAT_YUV_PLANAR_422_1X2;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_PLANAR_422_2X1:
        *penUNFFormt = HI_UNF_FORMAT_YUV_PLANAR_422_2X1;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_PLANAR_444:
        *penUNFFormt = HI_UNF_FORMAT_YUV_PLANAR_444;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_PLANAR_410:
        *penUNFFormt = HI_UNF_FORMAT_YUV_PLANAR_410;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_PACKAGE_UYVY422:
        *penUNFFormt = HI_UNF_FORMAT_YUV_PACKAGE_UYVY;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_PACKAGE_YUYV422:
        *penUNFFormt = HI_UNF_FORMAT_YUV_PACKAGE_YUYV;
        break;
    case HI_CODEC_COLOR_FORMAT_YUV_PACKAGE_YVYU422:
        *penUNFFormt = HI_UNF_FORMAT_YUV_PACKAGE_YVYU;
        break;
    default:
        *penUNFFormt = HI_UNF_FORMAT_YUV_SEMIPLANAR_420;
        break;
    }

    return;
}

/******************************************************************************
brief      : CNcomment: DBG调试功能，存收到的码流
attention  :
param[in]  : 
retval     : HI_VOID
see        :
******************************************************************************/
HI_VOID VDEC_VPU_DbgSaveStream(HI_CODEC_STREAM_S *pRawPacket, VPU_CHAN_CTX_S *pChanCtx)
{
    HI_CHAR PathStream[50];
    
    if (HI_NULL == pChanCtx)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pChanCtx is null!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    snprintf(PathStream, sizeof(PathStream), "/mnt/vpu_raw_save_chan%02d.bat", pChanCtx->u32ChanId);
    if ((HI_NULL == pRawPacket) || (HI_NULL == pChanCtx))
    {
        HI_ERR_VDEC("FUN:%s,L:%d pRawPacket or pChanCtx is NULL\n", __FUNCTION__, __LINE__);
        return;
    }

    if (HI_NULL == pChanCtx->fpStream)
    {
        pChanCtx->fpStream = fopen(PathStream, "wb+");
        if (HI_NULL == pChanCtx->fpStream)
        {
            HI_ERR_VDEC("FUN:%s,L:%d  Open file for saving stream failed!\n", __FUNCTION__, __LINE__);
            return;
        }
    }
    
	fwrite(pRawPacket->pu8Addr, 1, pRawPacket->u32Size, pChanCtx->fpStream);
	fflush(pChanCtx->fpStream);

    return;
}

/*****************************************************************************
brief     : HI_VPU_OutPut2DYuv. CNcomment:输出2D yuv文件
attention : 
param[in] : 
param[in] : 
param[out]: FILE *fpYuv
retval    :  
see       :
*****************************************************************************/
HI_VOID VDEC_VPU_DbgSave2DYuv(VPU_CHAN_CTX_S *pChanCtx, DecOutputInfo *pstOutPutInfo, HI_S32 Index)
{
    HI_U32 i,j;
    HI_CHAR PathYuv[50] = "/mnt/vpu_2d_save.yuv";
    HI_U32 chrom_width, chrom_height;
    HI_U32 Width, Height;
    HI_U32 StrideY = 0 ;
    HI_U32 StrideUV = 0 ;
    HI_U8 *TempBufV = NULL;
    HI_U8 *TempBufU = NULL;
    HI_U8 *YAddr = HI_NULL;
    HI_U8 *CbAddr = HI_NULL;
    HI_U8 *CrAddr = HI_NULL;
    FILE  *fpYuv = HI_NULL;

    if (HI_NULL == pChanCtx)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pChanCtx is null!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    snprintf(PathYuv, sizeof(PathYuv), "/mnt/vpu_2d_save_chan%02d.yuv", pChanCtx->u32ChanId);
    if ((HI_NULL == pChanCtx) || (HI_NULL == pstOutPutInfo))
    {
        HI_ERR_VDEC("FUN:%s,L:%d pRawPacket or pstOutPutInfo is NULL\n", __FUNCTION__, __LINE__);
        return;
    }

    if (HI_NULL == pChanCtx->fp2DYuv)
    {
        pChanCtx->fp2DYuv = fopen(PathYuv, "wb+");
        if (HI_NULL == pChanCtx->fp2DYuv)
        {
            HI_ERR_VDEC("FUN:%s,L:%d  Open file for saving YUV failed!\n", __FUNCTION__, __LINE__);
            return;
        }
    }
#ifdef VPU_MEM_MAP
#ifdef ALLOC_MEM_FRAME_BY_FRAEM
    fpYuv  = pChanCtx->fp2DYuv;
    YAddr  = pChanCtx->stLinearFrmBuf[Index].stMmzBuf.user_viraddr;
    CbAddr = pChanCtx->stLinearFrmBuf[Index].stMmzBuf.user_viraddr + (pstOutPutInfo->dispFrame.bufCb - pstOutPutInfo->dispFrame.bufY);
    CrAddr = pChanCtx->stLinearFrmBuf[Index].stMmzBuf.user_viraddr + (pstOutPutInfo->dispFrame.bufCr - pstOutPutInfo->dispFrame.bufY);
#else
    fpYuv  = pChanCtx->fp2DYuv;
    YAddr  = pChanCtx->stLinearFrmBuf[Index].user_viraddr;
    CbAddr = pChanCtx->stLinearFrmBuf[Index].user_viraddr + (pstOutPutInfo->dispFrame.bufCb - pstOutPutInfo->dispFrame.bufY);
    CrAddr = pChanCtx->stLinearFrmBuf[Index].user_viraddr + (pstOutPutInfo->dispFrame.bufCr - pstOutPutInfo->dispFrame.bufY);
#endif

    Width  = pstOutPutInfo->decPicWidth;
    Height = pstOutPutInfo->decPicHeight;
    chrom_width  = Width/2;
    chrom_height = Height/2;
    StrideY  = HI_SYS_GET_STRIDE(Width);
    StrideUV = StrideY /2 ;

    TempBufV = (HI_U8 *)malloc(3*1024*1024);
    TempBufU = (HI_U8 *)malloc(3*1024*1024);

    if ((HI_NULL == YAddr) || (HI_NULL == CbAddr) || (0 == Width) || (0 == Height) 
        || (HI_NULL == TempBufV) || (HI_NULL == TempBufU))
    {
        HI_ERR_VDEC("FUN:%s,L:%d  (%p, %p, %d, %d, %p, %p)Param is not valide!\n", __FUNCTION__, __LINE__,
                      YAddr, CbAddr, Width, Height, TempBufV, TempBufU);
        return;
    }

    //write Y
    for (i = 0;i < Height; i++)
    {
        fwrite(YAddr, 1, Width, fpYuv);
        YAddr += StrideY;
    }

#if 1
	//write Cb
    for (i = 0;i < chrom_height; i++)
    {
        for (j=0; j<chrom_width; j++)
        {
             TempBufV[i*chrom_width+j] = CbAddr[2*j];
             TempBufU[i*chrom_width+j] = CbAddr[2*j+1];
        }

		CbAddr += StrideY;
    }

    fwrite(TempBufU, 1, chrom_width*chrom_height, fpYuv);
    fwrite(TempBufV, 1, chrom_width*chrom_height, fpYuv);

#else
    //write cb
    for (i = 0;i < chrom_height; i++)
    {
        fwrite(CbAddr, 1, chrom_width, fpYuv);
        CbAddr += StrideUV;
    }

    //write cr
    for (i = 0;i < chrom_height; i++)
    {
        fwrite(CrAddr, 1, chrom_width, fpYuv);
        CrAddr += StrideUV;
    }

#endif
    fflush(fpYuv);

    free(TempBufV);
    free(TempBufU);
#else
    return;
#endif

    return;
}

/******************************************************************************
brief      : CNcomment: 获取解码通道能力级相关参数 
attention  :
param[in]  : 
retval     : HI_VOID
see        :
******************************************************************************/
HI_VOID VDEC_VPU_SetOpenOpt(HI_UNF_AVPLAY_OPEN_OPT_S *pstOpenParam, VPU_CHAN_CTX_S *pChanCtx)
{
    if ((HI_NULL == pstOpenParam) || (HI_NULL == pChanCtx))
    {
        HI_ERR_VDEC("FUN:%s,L:%d pstOpenParam or pChanCtx is NULL\n", __FUNCTION__, __LINE__);
        return;
    }

    switch (pstOpenParam->enDecType)
    {
        case HI_UNF_VCODEC_DEC_TYPE_NORMAL:
            pChanCtx->eCapMode = VPU_CAP_NORMAL;
            break;
        case HI_UNF_VCODEC_DEC_TYPE_ISINGLE:
            pChanCtx->eCapMode = VPU_CAP_ISINGLE;
            break;
        case HI_UNF_VCODEC_DEC_TYPE_BUTT:
        default:
            pChanCtx->eCapMode = VPU_DEC_BUTT;
            break;
    }

    return;
}


/******************************************************************************
brief      : CNcomment: 获取解码通道配置相关参数 
attention  :
param[in]  : 
retval     : HI_VOID
see        :
******************************************************************************/
HI_VOID VDEC_VPU_SetAttrOpt(HI_UNF_VCODEC_ATTR_S* pstAttr, VPU_CHAN_CTX_S *pChanCtx)
{
    if ((HI_NULL == pstAttr) || (HI_NULL == pChanCtx))
    {
        HI_ERR_VDEC("FUN:%s,L:%d pstOpenParam or pChanCtx is NULL\n", __FUNCTION__, __LINE__);
        return;
    }

    switch (pstAttr->enMode)
    {
        case HI_UNF_VCODEC_MODE_NORMAL:
            pChanCtx->eDecMode = VPU_DEC_IPB;
            pChanCtx->stParam.skipframeMode = 0;
            pChanCtx->eSkipMode = VPU_SKIP_NOTHING;
            break;
        case HI_UNF_VCODEC_MODE_IP:
            pChanCtx->eDecMode = VPU_DEC_IP;
            pChanCtx->stParam.skipframeMode = 2;
            pChanCtx->eSkipMode = VPU_SKIP_B;
            break;
        case HI_UNF_VCODEC_MODE_I:
            pChanCtx->eDecMode = VPU_DEC_I;
            pChanCtx->stParam.skipframeMode = 1;
            pChanCtx->eSkipMode = VPU_SKIP_P_B;
            break;
            
        case HI_UNF_VCODEC_MODE_DROP_INVALID_B:
        case HI_UNF_VCODEC_MODE_BUTT:
        default:
            pChanCtx->eDecMode = VPU_DEC_BUTT;
            pChanCtx->stParam.skipframeMode = 0;
            pChanCtx->eSkipMode = VPU_SKIP_NOTHING;
            break;
    }

    return;
}


/******************************************************************************
brief      : initial the ptsQueue . CNcomment:初始化pts管理队列
attention  :
param[in]  : 
retval     : HI_S32
see        :
******************************************************************************/
HI_S32 VDEC_VPU_InitPTSQueue(VPU_CHAN_CTX_S *pChanCtx)
{ 
    VPU_PTS_QUEUE_S *pstQueue = HI_NULL;

	if (HI_NULL == pChanCtx)
	{
        HI_ERR_VDEC("FUN:%s,L:%d pChanCtx is NULL\n", __FUNCTION__, __LINE__);
		return HI_FAILURE;
	}
    
	pstQueue = &(pChanCtx->stPtsQueue);
	memset(pstQueue, 0, sizeof(VPU_PTS_QUEUE_S));
	
    /** CNcomment: 生成头结点
    **/
	pstQueue->pHead = pstQueue->pRear = (VPU_PTS_QUEUE_NODE_S*)malloc(sizeof(VPU_PTS_QUEUE_NODE_S));
	if (HI_NULL == (pstQueue->pHead))
	{
        HI_ERR_VDEC("FUN:%s,L:%d pstQueue->pHead is NULL\n", __FUNCTION__, __LINE__);
	 	return HI_FAILURE;
	}

	memset(pstQueue->pHead, 0, sizeof(VPU_PTS_QUEUE_NODE_S));
   	pstQueue->pHead->next       = HI_NULL;
	pstQueue->u32BufStart       = pChanCtx->stBitStreamBuf.phyaddr ;
	pstQueue->u32BufEnd         = pChanCtx->stBitStreamBuf.phyaddr + pChanCtx->stBitStreamBuf.bufsize;
	pstQueue->u32LastDecReadPtr = pstQueue->u32BufStart;
	pstQueue->s64LastDecPts     = -1;
	
	return HI_SUCCESS;
}


/*****************************************************************************
brief      : push one Node into ptsQueue. CNcomment:将raw包节点插入到pts管理队
             列尾部，同时更新相关参数
attention  :
param[in]  : 
retval     : HI_S32
see        :
*****************************************************************************/
HI_S32 VDEC_VPU_CreatPTSQueue(VPU_CHAN_CTX_S *pChanCtx, HI_CODEC_STREAM_S *pRawPacket)
{
	VPU_PTS_QUEUE_NODE_S  *pNode = HI_NULL;

	if ((HI_NULL == pRawPacket) || (HI_NULL == pChanCtx)) 
	{
   		HI_ERR_VDEC("FUN: %s, L:%d pRawPacket or pChanCtx is null!! \n",__FUNCTION__, __LINE__);
		return HI_FAILURE;
	}
		
	pNode = (VPU_PTS_QUEUE_NODE_S*)malloc(sizeof(VPU_PTS_QUEUE_NODE_S));
	if ( HI_NULL == pNode ) 
	{
   		HI_ERR_VDEC("FUN: %s, L:%d pNode is null!! \n",__FUNCTION__, __LINE__);
		return HI_FAILURE;
	}

	memcpy(&(pNode->RawPacket), pRawPacket, sizeof(HI_CODEC_STREAM_S));
	pNode->next = HI_NULL;
	pChanCtx->stPtsQueue.pRear->next = (struct VPU_PTS_QUEUE_NODE_S *)pNode;
	pChanCtx->stPtsQueue.pRear = pNode;
	
	return HI_SUCCESS;
}

/*****************************************************************************
brief      : delete one Node from ptsQueue. CNcomment:将raw包节点从pts管理队列
             头部删除，同时更新相关参数并从pts队列中找到当前解码帧所在的包的
             pts，作为该解码帧的pts。
attention  :
param[in]  : 
retval     : HI_S32
see        :
*****************************************************************************/
HI_S32 VDEC_VPU_GetPTS(VPU_CHAN_CTX_S *pChanCtx, HI_S32 rdPtr, HI_S64 *ps64PtsMs)
{
	HI_U32 u32CurrentDecFrameSize = 0;
	HI_U32 u32PackpetSize = 0 ;
	VPU_PTS_QUEUE_NODE_S *pNode = HI_NULL;
	HI_CODEC_STREAM_S RawPacket;
	VPU_PTS_QUEUE_S *pstQueue = HI_NULL;

	if (HI_NULL == pChanCtx)
	{
        HI_ERR_VDEC("FUN:%s,L:%d pChanCtx is NULL\n", __FUNCTION__, __LINE__);
		return HI_FAILURE;
	}

	pstQueue = &(pChanCtx->stPtsQueue);
	if (pstQueue->pHead == pstQueue->pRear)
	{
        HI_WARN_VDEC("FUN:%s,L:%d pstQueue for PTS is empty!!\n", __FUNCTION__, __LINE__);
		return HI_SUCCESS;
	}

    /**CNcomment:获取解码当前帧的字节数,区分卷绕与非卷绕情况
    **/
    if (pstQueue->u32LastDecReadPtr <= ((HI_U32)rdPtr) )
	{
		u32CurrentDecFrameSize = (HI_U32)rdPtr - pstQueue->u32LastDecReadPtr ;
	}
	else
	{
	  	u32CurrentDecFrameSize = (pstQueue->u32BufEnd - pstQueue->u32LastDecReadPtr) + ((HI_U32)rdPtr - pstQueue->u32BufStart);
	}
    
    /**CNcomment:记录上一次解码成功的读指针
    **/
    pstQueue->u32LastDecReadPtr = (HI_U32)rdPtr; 
    if (1 == pChanCtx->u32IsFromDemux)
    {
        pstQueue->s64LastValidRawPts = -1;
    }

    do
    {
        if (pstQueue->pHead == pstQueue->pRear)
        {
            break;
        }

        pNode = (VPU_PTS_QUEUE_NODE_S *)(pstQueue->pHead->next);
        memcpy(&RawPacket, &(pNode->RawPacket), sizeof(HI_CODEC_STREAM_S));
        u32PackpetSize += RawPacket.u32Size ; 

        if (1 == pChanCtx->u32IsFromDemux)
        {
            if ((RawPacket.s64PtsMs >= 0) && (0xffffffff != RawPacket.s64PtsMs) && (-1 == pstQueue->s64LastValidRawPts))
            {
                pstQueue->s64LastValidRawPts = RawPacket.s64PtsMs ; //记录最近一个有效的pts
            }
        }
        else
        {
            if ((RawPacket.s64PtsMs >= 0)  && (0xffffffff != RawPacket.s64PtsMs))
            {
                pstQueue->s64LastValidRawPts = RawPacket.s64PtsMs ; //记录最近一个有效的pts
            }
        } 
        if ((u32PackpetSize - pstQueue->u32RawPackOffset ) >= u32CurrentDecFrameSize)                               
        {
            if ((pstQueue->s64LastDecPts == RawPacket.s64PtsMs) && (0xffffffff != RawPacket.s64PtsMs))
            {
                *ps64PtsMs = -1;
            }
            else 
            {
                pstQueue->s64LastDecPts = RawPacket.s64PtsMs;   //更新前一帧的pts，针对一包多帧
                if ((RawPacket.s64PtsMs >= 0) && (0xffffffff != RawPacket.s64PtsMs))
                {
                    if (1 == pChanCtx->u32IsFromDemux)
                    {
                        *ps64PtsMs = pstQueue->s64LastValidRawPts;  //RawPacket.s64PtsMs;
                    }
                    else
                    {
                        *ps64PtsMs = RawPacket.s64PtsMs;
                    }
                }
                else
                {
                    *ps64PtsMs = pstQueue->s64LastValidRawPts; //针对多包一帧，当前包pts出错
                }
            }
            //	HI_ERR_VDEC("#HI_VPU_GetPTS : u32CurrentDecFrameSize =%d || s64LastDecPts = %lld || Packet.s64PtsMs = %lld || s64pts = %lld\n",u32CurrentDecFrameSize,pstQueue->s64LastDecPts,RawPacket.s64PtsMs,*ps64PtsMs);
            pstQueue->u32RawPackOffset = RawPacket.u32Size - (u32PackpetSize - pstQueue->u32RawPackOffset -u32CurrentDecFrameSize);
            break;
            }
            else 
            {
                pstQueue->pHead->next = pNode->next; // 头结点指向下一个结点

                if( pstQueue->pRear == pNode ) // 删除的是队尾结点
                {
                    pstQueue->pRear = pstQueue->pHead ; // 修改队尾指针指向头结点(空队列)
                }

                free(pNode); // 释放队头结点
                pNode = HI_NULL;
            }
    } while (1); 

return HI_SUCCESS;
}

/*****************************************************************************
brief      : destroy the ptsQueue . CNcomment:销毁pts管理队列
attention  :
param[in]  : 
retval     : HI_S32
see        :
*****************************************************************************/
HI_S32 VDEC_VPU_DeinitPTSQueue(VPU_PTS_QUEUE_S *pstQueue)
{ 
    if (HI_NULL == pstQueue)
	{
        HI_ERR_VDEC("FUN:%s,L:%d pstQueue is NULL\n", __FUNCTION__, __LINE__);
		return HI_FAILURE;
	}
		
    while (HI_NULL != pstQueue->pHead)
    {
        pstQueue->pRear = (VPU_PTS_QUEUE_NODE_S *)(pstQueue->pHead->next); // pRear指向pHead的下一个结点
        free(pstQueue->pHead);             // 释放pHead所指结点
        pstQueue->pHead = pstQueue->pRear; // pHead指向pHead的下一个结点
    }
	 
	return HI_SUCCESS;
}

/*****************************************************************************
brief      : set PTS for decoded frame  . CNcomment:为解码帧打上pts
attention  :
param[in]  : 
retval     : HI_S32
see        :
******************************************************************************/
HI_S32 VDEC_VPU_SetPtsForDecFrmBuf( VPU_CHAN_CTX_S *pChanCtx, HI_S32 frameIdx, HI_S64 s64Pts)
{ 
	HI_U32 i = 0;
	RetCode ret;
	DecHandle pHandle = HI_NULL;
	FrameBuffer frameBuf ;

    if (HI_NULL == pChanCtx)
	{
        HI_ERR_VDEC("FUN:%s,L:%d pChanCtx is NULL\n", __FUNCTION__, __LINE__);
		return HI_FAILURE;
	}

    pHandle  = pChanCtx->pHandle;
	
	ret = VPU_DecGetFrameBuffer(pHandle, (frameIdx + pChanCtx->u32ActualFrameNum), &frameBuf);
	VPU_ASSERT_EQ(RETCODE_SUCCESS, ret);

    for (i = 0; i < VPU_MAX_FRAME_NUM; i++)
	{
		if (HI_FALSE == pChanCtx->stDecFrmBuf[i].bUsed )
		{
 			memcpy(&(pChanCtx->stDecFrmBuf[i].stLinearBuf), &frameBuf, sizeof(FrameBuffer)); 
			pChanCtx->stDecFrmBuf[i].s64pts = s64Pts;
			pChanCtx->stDecFrmBuf[i].bUsed  = HI_TRUE;
			ret = HI_SUCCESS;
            break;
		}
	}	
 
    if (i >= VPU_MAX_FRAME_NUM)
    {
        HI_ERR_VDEC("FUN:%s,L:%d Can not find a not used frame buffer\n", __FUNCTION__, __LINE__);
        ret = HI_FAILURE;
    }

	return ret;
}


/*****************************************************************************
brief      : get PTS from display frame  . CNcomment:从显示帧存中获取pts
attention  :
param[in]  : 
retval     : HI_S32
see        :
*****************************************************************************/
HI_S32 VDEC_VPU_GetPtsForDispFrmBuf( VPU_CHAN_CTX_S *pChanCtx, DecOutputInfo stOutPutInfo, HI_S64 *s64Pts)
{ 
	HI_U32  i = 0;
	RetCode ret;

    for (i = 0; i < VPU_MAX_FRAME_NUM; i++)
	{
		if ( stOutPutInfo.dispFrame.bufY == pChanCtx->stDecFrmBuf[i].stLinearBuf.bufY &&
			 stOutPutInfo.dispFrame.bufCb == pChanCtx->stDecFrmBuf[i].stLinearBuf.bufCb &&
 			 stOutPutInfo.dispFrame.bufCr == pChanCtx->stDecFrmBuf[i].stLinearBuf.bufCr)
		{
 			*s64Pts = pChanCtx->stDecFrmBuf[i].s64pts ;
			pChanCtx->stDecFrmBuf[i].bUsed = HI_FALSE;
			pChanCtx->s64NewDispFramePts = pChanCtx->stDecFrmBuf[i].s64pts;
			ret = HI_SUCCESS;
            break;
		}
	}	

    if (i >= VPU_MAX_FRAME_NUM)
    {
        HI_WARN_VDEC("FUN:%s,L:%d Can not find a valide buffer\n", __FUNCTION__, __LINE__);
        ret = HI_FAILURE;
    }

	return ret;
}




/*****************************************************************************
 * \brief                   Print out decoded information such like RD_PTR, WR_PTR, PIC_TYPE, ..
 * \param   decodedInfo     If this parameter is not NULL then print out decoded informations
 *                          otherwise print out header.
******************************************************************************/
static void VDEC_VPU_DisplayDecodedInformation(DecHandle handle, HI_U32 frameNo, DecOutputInfo* decodedInfo)
{
    HI_S32 logLevel;
     if (decodedInfo == NULL) {
         // Print header
         HI_ERR_VDEC( "I  NO    T   DECO   DISP DISPFLAG   RD_PTR   WR_PTR FRM_START FRM_END WxH  \n");
         HI_ERR_VDEC( "---------------------------------------------------------------------------\n");
     }
     else {
         logLevel = (decodedInfo->decodingSuccess&0x01) == 0 ? ERR : TRACE;
         // Print informations
         HI_ERR_VDEC( "%02d %5d %d %2d(%2d) %2d(%2d) %08x %08x %08x %08x %08x %dx%d\n",
             handle->instIndex, frameNo, decodedInfo->picType, 
             decodedInfo->indexFrameDecoded, decodedInfo->indexFrameDecodedForTiled,
             decodedInfo->indexFrameDisplay, decodedInfo->indexFrameDisplayForTiled,
             decodedInfo->frameDisplayFlag,decodedInfo->rdPtr, decodedInfo->wrPtr, 
             decodedInfo->bytePosFrameStart, decodedInfo->bytePosFrameEnd,
             decodedInfo->dispPicWidth, decodedInfo->dispPicHeight);
         if (logLevel == ERR)
             HI_ERR_VDEC( "\t>>ERROR REASON: 0x%08x(0x%08x)\n", decodedInfo->errorReason, decodedInfo->errorReasonExt);
         if (decodedInfo->numOfErrMBs)
             HI_ERR_VDEC( "\t>> ErrorBlock: %d, TotalBlock: %d\n", decodedInfo->numOfErrMBs, decodedInfo->numOfTotMBs);
     }

#if 0
    if (decodedInfo == HI_NULL) {
        // Print header
        HI_INFO_VDEC("I  NO    T   DECO   DISP DISPFLAG   RD_PTR   WR_PTR FRM_START FRM_END WxH  \n");
        HI_INFO_VDEC("TRACE---------------------------------------------------------------------------\n");
    }
    else {
        logLevel = (decodedInfo->decodingSuccess&0x01) == 0 ? ERR : TRACE;
        // Print informations
        HI_INFO_VDEC( "\nlogLevel =%d:  %02d %5d (Type %d) %2d(%2d) %2d(%2d) %08x %08x %08x %08x %08x %08x %dx%d\n",
            logLevel,handle->instIndex, frameNo, decodedInfo->picType, 
            decodedInfo->indexFrameDecoded, decodedInfo->indexFrameDecodedForTiled,
            decodedInfo->indexFrameDisplay, decodedInfo->indexFrameDisplayForTiled,
            decodedInfo->frameDisplayFlag,decodedInfo->dispFrame.bufY,
            decodedInfo->rdPtr, decodedInfo->wrPtr, 
            decodedInfo->bytePosFrameStart, decodedInfo->bytePosFrameEnd,
            decodedInfo->dispPicWidth, decodedInfo->dispPicHeight);
        if (logLevel == ERR)
            HI_INFO_VDEC( "\t ERR,>>ERROR REASON: 0x%08x(0x%08x)\n", decodedInfo->errorReason, decodedInfo->errorReasonExt);
        if (decodedInfo->numOfErrMBs)
            HI_INFO_VDEC("\t WARN,>>ErrorBlock: %d\n", decodedInfo->numOfErrMBs);
    }
#endif    
}


/*****************************************************************************
brief      : fill rawpacket for vpu Codec. CNcomment:给VPU送码流
attention  :
param[in]  : 
retval     : HI_S32
see        :
*****************************************************************************/
HI_S32 VDEC_VPU_FillRawPacket(VPU_CHAN_CTX_S *pChanCtx, HI_CODEC_STREAM_S *pRawPacket)
{
    HI_U8 *CurVir 		= HI_NULL;
    HI_U8 *StreamVir 	= HI_NULL;
    HI_U8 *StartVir 	= HI_NULL;
    DecHandle   pHandle = HI_NULL;

    HI_U32 ReadPtr, WritePtr, Size, TempSize;
    HI_U32 BufEnd, BufStart;
    HI_S32 s32Ret;
    HI_U32 u32Time = 0;

    if (HI_NULL == pChanCtx)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pChanCtx is null\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    pHandle  = pChanCtx->pHandle;
    BufStart = pChanCtx->stBitStreamBuf.phyaddr;
    BufEnd   = pChanCtx->stBitStreamBuf.phyaddr + pChanCtx->stBitStreamBuf.bufsize;
    StartVir = CurVir = pChanCtx->stBitStreamBuf.user_viraddr;

    if (HI_NULL == pRawPacket)
    {

        return HI_FAILURE;
    }
	
    /**CNcomment: 查看 Bitstream buffer 还有多少空闲
    **/
    s32Ret = VPU_DecGetBitstreamBuffer(pHandle, &ReadPtr, &WritePtr, &Size);
    VPU_ASSERT_EQ(RETCODE_SUCCESS, s32Ret);

    /**CNcomment: 这两种情况下，均只是记录RAW包信息，不标记为可释放
    **/
    if ((Size <= 0) || (pRawPacket->u32Size > Size))
    {
        return VPU_STR_BUF_INSUFFICIENT;
    }

    /**CNcomment: 区分卷绕和非卷绕的情况
    **/
    if ((WritePtr + pRawPacket->u32Size) > BufEnd)
    {
        TempSize =  BufEnd - WritePtr;
		CurVir = StartVir + (WritePtr - BufStart);
        memcpy(CurVir, pRawPacket->pu8Addr, TempSize);  
        StreamVir = pRawPacket->pu8Addr + TempSize;
		TempSize = pRawPacket->u32Size - TempSize;
        memcpy(StartVir, StreamVir, TempSize);  
    }
    else
    {
        TempSize = pRawPacket->u32Size;
		CurVir = StartVir + (WritePtr - BufStart);
        memcpy(CurVir, pRawPacket->pu8Addr, TempSize);  
    }

    /**CNcomment: 更新 Bitstream buffer 状态
    **/
    s32Ret = VPU_DecUpdateBitstreamBuffer(pHandle, pRawPacket->u32Size);
    VPU_ASSERT_EQ(RETCODE_SUCCESS, s32Ret);

#ifdef SAVE_Stream
    VDEC_VPU_DbgSaveStream(pRawPacket, pChanCtx);
#endif	

    /**CNcomment: 每次送入码流到buff成功时，更新pts管理队列
    **/
    s32Ret = VDEC_VPU_CreatPTSQueue( pChanCtx, pRawPacket);
    VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);

    pChanCtx->u64RecvPackSize += pRawPacket->u32Size;
    pChanCtx->u32BsSizeOneSecond += pRawPacket->u32Size;

    if ( 0 == pChanCtx->s64FirstValidRawPts  && 0xffffffff != pRawPacket->s64PtsMs )
    {
        pChanCtx->s64FirstValidRawPts = pRawPacket->s64PtsMs;
    }
    if (0 == pChanCtx->u32BsLastTime)
    {
        HI_SYS_GetTimeStampMs(&(pChanCtx->u32BsLastTime));
    }
    else
    {
        HI_SYS_GetTimeStampMs(&u32Time);
        if (u32Time - pChanCtx->u32BsLastTime > 1000)
        {
            pChanCtx->u32BsRate = (pChanCtx->u32BsSizeOneSecond*8)/(u32Time - pChanCtx->u32BsLastTime);
            pChanCtx->u32BsSizeOneSecond = 0;
            pChanCtx->u32BsLastTime = u32Time;
            HI_VPU_PROC_STATUS(pChanCtx, HI_NULL);
        }
    }

    return HI_SUCCESS;
}


/*****************************************************************************
brief      : get the vpu Codec. CNcomment:获取VPU解码器描述 CNend
attention  :
param[in]  : 
retval     : HI_CODEC_S
see        :
*****************************************************************************/
HI_VOID VDEC_VPU_CtxReset(HI_HANDLE hInst)
{
    if (hInst >= VPU_MAX_CHAN_NUM)
    {
         HI_ERR_VDEC("FUN:%s,L:%d hInst %d is not valid!\n", __FUNCTION__, __LINE__, hInst);
         return;
    }

    memset(&(g_VPUChanCtx[hInst]), 0x0, sizeof(VPU_CHAN_CTX_S));

    /**CNcomment: 对需要特殊初始化的值，在这里需要进行重新赋值
    **/
    g_VPUChanCtx[hInst].eChanState = VPU_STATE_OPEN;
    g_VPUChanCtx[hInst].u32hVdec   = HI_INVALID_HANDLE;
    g_VPUChanCtx[hInst].u32ChanId  = HI_INVALID_HANDLE;
    g_VPUChanCtx[hInst].s64NewDispFramePts = -1;
    
    return;
}

/*****************************************************************************
brief     : Load binary firmware file
attention :
param[in] : HI_CODEC_OPENPARAM_S * 
retval    : Int32 productId     
            Uint8** retFirmware : firmware address
            Uint32* retSizeInWord : firmware size
            const char* path : firmware file path
see       :
******************************************************************************/
HI_VOID VDEC_VPU_LoadFirmware(HI_S32 productId, HI_U16* pusBitCode, HI_U32* retSizeInWord)
{
#ifdef VFMW_BIN_LOAD
    HI_U32 totalRead, readSize;
    HI_CHAR *path = "/mnt/michelangel.bin";
    FILE *fp = NULL;  

    if ((fp = fopen(path, "rb")) == NULL)
    {
        VLOG(ERR, "Failed to open %s\n", path);
        return ;
    }

   
	fseek(fp,0L,SEEK_END); 
	readSize = ftell(fp);
	fseek(fp,0L,SEEK_SET); 
	
    if (NULL != fp && readSize > 0)
    {
	    //  endian 0
        totalRead = fread((HI_U8*)pusBitCode, 1, readSize, fp);
	}
    fclose(fp);

    *retSizeInWord = (totalRead+1)/2;

#else
	HI_U32  readSize = 0;

	readSize = (sizeof(g_vpu_firmware) + 3)/(sizeof(g_vpu_firmware[0]));
	memcpy((HI_U8*)pusBitCode, (HI_U8*)g_vpu_firmware, sizeof(g_vpu_firmware));
	*retSizeInWord = (sizeof(g_vpu_firmware)+1)/2 ;
#endif
	return;
}

/*****************************************************************************
brief      : CNcomment:对VPU进行全局初始化，主要完成VPU初始化和加载FMW的工作
attention  :
param[in]  : HI_VOID
retval     : HI_S32
see        :
*****************************************************************************/
HI_S32 VDEC_VPU_GlobaleInit(HI_VOID)
{
	HI_S32  s32CoreIndex = 0; 
	HI_S32  productId 	 = 0; 
    HI_S32  s32Ret       = HI_FAILURE;
    HI_U32  sizeInWord 	 = 0;
    HI_U16* pusBitCode 	 = HI_NULL ;

    VPU_HWReset(s32CoreIndex);
//	VPU_SWReset(s32CoreIndex, SW_RESET_SAFETY, NULL);  // TO DO

    /**CNcomment: 调用VPU_Init完成模块初始化工作,创建多通道实例时,只允许加载一次
    **/
    productId  = VPU_GetProductId(s32CoreIndex);
    pusBitCode = (HI_U16*)malloc(VPU_FMW_BIN_SIZE);
    if (HI_NULL == pusBitCode)
    {
        HI_ERR_VDEC("FUN:%s,L:%d malloc for vfmw bin failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
    else
    {
        memset(pusBitCode, 0x0, VPU_FMW_BIN_SIZE);
        VDEC_VPU_LoadFirmware(productId, pusBitCode, &sizeInWord);
        s32Ret = VPU_InitWithBitcode(s32CoreIndex, pusBitCode, sizeInWord);

        free(pusBitCode); 
        pusBitCode = HI_NULL;
    }

    if ((RETCODE_SUCCESS != s32Ret) && (RETCODE_CALLED_BEFORE != s32Ret))
    {
        HI_ERR_VDEC("FUN:%s,L:%d Failed to boot up VPU!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


/*****************************************************************************
brief      : Init vpu Codec. CNcomment:初始化VPU解码器
attention  :
param[in]  : 
retval     : HI_CODEC_S
see        :
*****************************************************************************/
HI_U32 VDEC_VPU_Init(HI_VOID)
{
    HI_S32 i = 0;
    HI_S32 s32Ret = 0;

    /**CNcomment: 暂时先放到在这里，继续输里多实例时，将不能放到这里 TODO
    **/
    s32Ret = VDEC_VPU_GlobaleInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("FUN:%s,L:%d  VDEC_VPU_GlobaleInit for VPU failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    for(i = 0; i < VPU_MAX_CHAN_NUM; i++)
	{
        VDEC_VPU_CtxReset(i);
	}
 
    return HI_SUCCESS;
}


/*****************************************************************************
brief      : get the vpu Codec. CNcomment:获取VPU解码器描述 CNend
attention  :
param[in]  : 
retval     : HI_CODEC_S
see        :
*****************************************************************************/
HI_CODEC_S* VDEC_VPU_Codec(HI_VOID)
{
    return &hi_codecVPU_entry;
}

/*****************************************************************************
brief     : get the vpu Codec Capability. CNcomment:获取VPU解码器解码能力 CNend
attention :
param[in] : HI_CODEC_CAP_S *
param[out]: HI_CODEC_CAP_S
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_GetCap(HI_CODEC_CAP_S *pstCodecCap)
{
    if (HI_NULL == pstCodecCap)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pstCodecCap is null\n", __FUNCTION__, __LINE__);
        return HI_ERR_CODEC_INVALIDPARAM;
    }

    pstCodecCap->u32CapNumber = HI_CODEC_CAP_DRIVENOUTSIDE | HI_CODEC_CAP_OUTPUT2SPECADDR;
    pstCodecCap->pstSupport   = &s_stCodecSupport;

    return HI_SUCCESS;
}

/*****************************************************************************
brief     : creat stream buffer
attention :
param[in] : HI_MMZ_BUF_S *
retval    : HI_S32
see       :
*****************************************************************************/
HI_S32 VDEC_VPU_CreateStreamBuffer(HI_MMZ_BUF_S *pStreamBuf)
{
    HI_S32 s32Ret = HI_FAILURE;
	HI_CHAR BufName[16] = "VPU_STR_BUF";

    if (HI_NULL == pStreamBuf)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pStreamBuf is null\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    pStreamBuf->bufsize = VPU_STREAM_BUF_SIZE;
	strncpy(pStreamBuf->bufname, BufName, sizeof(HI_CHAR)*16);
    s32Ret = HI_MMZ_Malloc(pStreamBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("FUN:%s,L:%d HI_MMZ_Malloc for stream buffer failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

	return s32Ret;
}

/*****************************************************************************
brief     : free buffer
attention :
param[in] : HI_MMZ_BUF_S *
retval    : HI_S32
see       :
*****************************************************************************/
HI_S32 VDEC_VPU_FreeBuffer(HI_MMZ_BUF_S *pBuf)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_NULL == pBuf)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pBuf is null!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    s32Ret = HI_MMZ_Free(pBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("FUN:%s,L:%d HI_MMZ_Free for pBuf failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }


	return HI_SUCCESS;
}


/*****************************************************************************
brief     : Create frame buffer
attention :
param[in] : HI_MMZ_BUF_S *
retval    : HI_S32
see       :
******************************************************************************/
#ifdef ALLOC_MEM_FRAME_BY_FRAEM
HI_S32 HI_VPU_CreateFrameBuf(HI_U32 u32Size, HI_U32 u32Num, VPU_ALLOCED_FRAME_BUF_S *pFrameBuf)
{
   //@f00241306  20140504
	HI_U32 i 			   = 0 ;
    HI_S32 s32Ret 		   = HI_FAILURE;
    HI_CHAR BufName[16]    = "VPU_FRM_BUF";
	HI_BOOL  bAllocFromVdh = HI_TRUE; //默认优先从VDH预分的内存中申请帧存
	HI_MMZ_BUF_S  stFrameBuf;

    /**CNcomment: 函数输入的参数合法性检查
    **/
    if ((HI_NULL == pFrameBuf) || (0 == u32Size) || (0 == u32Num))
    {
        HI_ERR_VDEC("FUN:%s,L:%d pFrameBuf(%p), u32Size(%d), u32Num(%d) is valid!\n", 
                     __FUNCTION__, __LINE__, pFrameBuf, u32Size, u32Num);
        return HI_FAILURE;
    }

    /**CNcomment: 对帧存空间进行分割
    **/
	for (i = 0; i < u32Num; i++)
	{
	    /**CNcomment: 申请帧存BUFFER
    	**/
        bAllocFromVdh = HI_TRUE;
		memset(&stFrameBuf, 0, sizeof(HI_MMZ_BUF_S));
		stFrameBuf.bufsize = u32Size;
		strncpy(stFrameBuf.bufname, BufName, sizeof(HI_CHAR)*16);

		s32Ret = VDEC_VPU_CreateFrameBuf(&stFrameBuf);
		/**CNcomment: 如果从预分的帧存中分不到，那么从系统中申请
       	**/
    	if (HI_SUCCESS != s32Ret)
    	{
    	    s32Ret = HI_MMZ_Malloc(&stFrameBuf);
    	    if (HI_SUCCESS != s32Ret)
    		{
        		HI_ERR_VDEC("FUN:%s,L:%d HI_MMZ_Malloc for frame buffer failed!\n", __FUNCTION__, __LINE__);
        		return HI_FAILURE;
    		}
			bAllocFromVdh = HI_FALSE;
    	}
		
        memcpy(&(pFrameBuf[i].stMmzBuf), &stFrameBuf, sizeof(HI_MMZ_BUF_S));
		pFrameBuf[i].bAllocFromVdh = bAllocFromVdh;
	}

	return HI_SUCCESS;
}
#else
HI_S32 HI_VPU_CreateFrameBuf(HI_U32 u32Size, HI_U32 u32Num, HI_MMZ_BUF_S *pFrameBuf)
{
	HI_U32 i 			= 0 ;
    HI_S32 s32Ret 		= HI_FAILURE;
    HI_CHAR BufName[16] = "VPU_FRM_BUF";
	HI_MMZ_BUF_S stFrameBuf;

    /**CNcomment: 函数输入的参数合法性检查
    **/
    if ((HI_NULL == pFrameBuf) || (0 == u32Size) || (0 == u32Num))
    {
        HI_ERR_VDEC("FUN:%s,L:%d pFrameBuf(%p), u32Size(%d), u32Num(%d) is valid!\n", 
                     __FUNCTION__, __LINE__, pFrameBuf, u32Size, u32Num);
        return HI_FAILURE;
    }

    memset(&stFrameBuf, 0, sizeof(HI_MMZ_BUF_S));

    /**CNcomment: 申请帧存BUFFER
    **/
    stFrameBuf.bufsize = u32Size*u32Num + 3*1024 ;
    strncpy(stFrameBuf.bufname, BufName, sizeof(HI_CHAR)*16);
    s32Ret = VDEC_VPU_CreateFrameBuf(&stFrameBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("FUN:%s,L:%d VDEC_VPU_CreateFrameBuf failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    /**CNcomment: 对帧存空间进行分割
    **/
	for (i = 0; i < u32Num; i++)
	{
        memcpy(&(pFrameBuf[i]), &stFrameBuf, sizeof(HI_MMZ_BUF_S));
	    pFrameBuf[i].bufsize        = u32Size;
		pFrameBuf[i].phyaddr        = stFrameBuf.phyaddr        + i*u32Size;
		pFrameBuf[i].user_viraddr   = stFrameBuf.user_viraddr   + i*u32Size;
		pFrameBuf[i].kernel_viraddr = stFrameBuf.kernel_viraddr + i*u32Size;
	}

	return HI_SUCCESS;	
}
#endif

/*****************************************************************************
brief     : fill Decode open parameter
attention :
param[in] : DecOpenParam  *
retval    : 
see       :
*****************************************************************************/
HI_S32 VDEC_VPU_FillDecOpenParm(DecOpenParam *decOP, HI_MMZ_BUF_S *pstBitstreamBuf)
{

    /**CNcomment: 函数输入的参数合法性检查
    **/
    if ((HI_NULL == decOP) || (HI_NULL == pstBitstreamBuf))
	{
        HI_ERR_VDEC("FUN:%s,L:%d  decOP or pstBitstreamBuf is null!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
	}

	decOP->bitstreamFormat     = 12; // 12(H.265)
    decOP->coreIdx             = 0;  //only supported one core
    decOP->bitstreamBuffer     = pstBitstreamBuf->phyaddr;
    decOP->bitstreamBufferSize = pstBitstreamBuf->bufsize;
    decOP->mp4DeblkEnable      = 0;
    decOP->tiled2LinearEnable  = (COMPRESSED_FRAME_MAP >> 4) & 0x1; // COMPRESSED_FRAME_MAP=10
	
    decOP->tiled2LinearMode    = FF_NONE;	
    decOP->bitstreamMode       = 0;
	decOP->wtlEnable           = 1;
    decOP->wtlMode             = FF_FRAME;

	decOP->mp4DeblkEnable      = 0;
    decOP->tiled2LinearEnable  = 0;	
    decOP->cbcrInterleave      = CBCR_INTERLEAVE;	
    decOP->bwbEnable           = 0;
    decOP->nv21                = 1;

    decOP->streamEndian        = VPU_STREAM_ENDIAN;
    decOP->frameEndian         = VPU_FRAME_ENDIAN;

	return HI_SUCCESS;
}

/*****************************************************************************
brief     : Create frame list
attention :
param[in] : HI_HANDLE
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_CreateFrameList(HI_HANDLE hVdec)
{
    HI_S32 s32Ret;

	s32Ret = VDEC_VPU_CreateFrameList(hVdec);

    return s32Ret;
}

/*****************************************************************************
brief     : Destroy frame list
attention :
param[in] : HI_HANDLE
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_ReleaseFrameList(HI_HANDLE hVdec)
{
    HI_S32 s32Ret;

	s32Ret = VDEC_VPU_ReleaseFrameList(hVdec);

    return s32Ret;
}

/*****************************************************************************
brief     : Create vpu Codec. CNcomment:创建VPU解码器 CNend
attention :
param[in] : HI_CODEC_OPENPARAM_S * 
retval    : HI_HANDLE*
see       :
*****************************************************************************/
HI_S32 HI_VPU_Create(HI_HANDLE* phInst, const HI_CODEC_OPENPARAM_S *pstParam)
{
	HI_S32  s32Ret = HI_FAILURE, i  = 0; 
    HI_U32  u32hVdec		   	    = *phInst;
	VPU_CHAN_CTX_S *pChanCtx 		= HI_NULL;
 	DecHandle *handle 				= HI_NULL;
	HI_MMZ_BUF_S *pstBitstreamBuf 	= HI_NULL;
	DecOpenParam  *pDecOP	  	 	= HI_NULL;
    HI_UNF_AVPLAY_OPEN_OPT_S*   pstOpenParam = NULL;
    HI_S32 s32Value = 100;

    /**CNcomment: 需要检查参数是否合法：h265解码器中只支持h265
    **/
    if (NULL == pstParam || HI_CODEC_ID_VIDEO_HEVC != pstParam->enID)
    {
        HI_ERR_VDEC("FUN:%s,L:%d  Not support any other video type but H265!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
    else
    {  
        pstOpenParam = (HI_UNF_AVPLAY_OPEN_OPT_S*)pstParam->unParam.stVdec.pPlatformPriv;
    }

#if 0
    /**CNcomment: 暂时先放到在这里，继续输里多实例时，将不能放到这里 TODO
    **/
    s32Ret = VDEC_VPU_GlobaleInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("FUN:%s,L:%d  VDEC_VPU_GlobaleInit for VPU failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
#endif
//    VDEC_VPU_CheckFMWVersion();

    /**CNcomment: 找一个空闲的通道
    **/
    for (i = 0; i < VPU_MAX_CHAN_NUM; i++ )
    {
		if (HI_NULL == g_VPUChanCtx[i].pHandle)
		{
            *phInst  = i;
		    pDecOP   = &(g_VPUChanCtx[i].stOpenParam);
			pChanCtx = &(g_VPUChanCtx[i]);
			break;
		}
	}

    if (i >= VPU_MAX_CHAN_NUM)
    {
        HI_ERR_VDEC("FUN:%s,L:%d  can not find a valide instance for VPU!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
	}
    
    handle = &(pChanCtx->pHandle);

    pChanCtx->u32ChanId        = i;
	pChanCtx->u32hVdec         = u32hVdec;
	pChanCtx->bRegFrameBuffer  = HI_FALSE;
	pChanCtx->bStartDecPicFlag = HI_FALSE;
    pChanCtx->bIsNotSupport    = HI_FALSE;
	pChanCtx->bStartDecSeqFlag = HI_FALSE;
	pChanCtx->u32frameCount    = 0;
    VDEC_VPU_SetOpenOpt(pstOpenParam, pChanCtx);
    memcpy(&(pChanCtx->stCodecParam), pstParam, sizeof(HI_CODEC_OPENPARAM_S));
		
    pstBitstreamBuf = &(g_VPUChanCtx[i].stBitStreamBuf);

    /**CNcomment: 申请Stream buffer 
    **/
    s32Ret = VDEC_VPU_CreateStreamBuffer(pstBitstreamBuf);
    if (RETCODE_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("FUN:%s,L:%d Allocate bitstream buffer for VPU failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    /**CNcomment: 设置解码参数
    **/
	VDEC_VPU_FillDecOpenParm(pDecOP, pstBitstreamBuf);

    /**CNcomment: 创建一个解码实例
    **/
    s32Ret = VPU_DecOpen(handle, pDecOP);	
    if(RETCODE_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("FUN:%s,L:%d VPU_DecOpen for VPU failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }


    /** Empty interrupt occurrs every s32Value(ms) of the application didn't fill bitstream
    **/
//    VPU_DecGiveCommand(handle, DEC_SET_REPEAT_EMPTY_INTERRUPT, &s32Value);  
//    VPU_DecGiveCommand(pChanCtx->pHandle, ENABLE_LOGGING, 0);  


    /**CNcomment: 创建VDEC 帧存列表
    **/
	s32Ret = HI_VPU_CreateFrameList(pChanCtx->u32hVdec);
	if (HI_SUCCESS != s32Ret)
	{
        HI_ERR_VDEC("FUN:%s,L:%d VPU_DecOpen for VPU failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
	}

    /**CNcomment: 创建VDEC PTS 列表
    **/
    s32Ret = VDEC_VPU_PtsAlloc(pChanCtx->u32hVdec, pChanCtx->u32ChanId);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VDEC("FUN:%s,L:%d VDEC_VPU_PtsAlloc for VPU failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
	
    /**CNcomment: 初始化PTS 队列
    **/
	s32Ret = VDEC_VPU_InitPTSQueue( pChanCtx );
	if (HI_SUCCESS != s32Ret)
	{
        HI_ERR_VDEC("FUN:%s,L:%d VDEC_VPU_InitPTSQueue for VPU failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
	}

    /**CNcomment: 配通道相关信息
    **/
    if (VPU_CAP_ISINGLE == pChanCtx->eCapMode)
    {
        s32Ret = VPU_DecGiveCommand(pChanCtx->pHandle, ENABLE_DEC_THUMBNAIL_MODE, NULL);    
        if(RETCODE_SUCCESS != s32Ret)
        {
            HI_ERR_VDEC("FUN:%s,L:%d set VPU_DEC_ISINGLE for VPU failed!\n", __FUNCTION__, __LINE__);
            return HI_FAILURE;
        }
    }

	return HI_SUCCESS;
}

//该函数属在开发过种中的多余代码，后续优化将其删除
/*****************************************************************************
brief     : Create vpu Codec. CNcomment:创建VPU解码器 CNend
attention :
param[in] : HI_CODEC_OPENPARAM_S * 
retval    : HI_HANDLE*
see       :
*****************************************************************************/
HI_S32 VPU_CreatForReset(VPU_CHAN_CTX_S *pChanCtx, const HI_CODEC_OPENPARAM_S * pstParam)
{
	HI_S32 s32Ret 					= 0; 
	DecHandle *handle 				= HI_NULL;
	HI_MMZ_BUF_S *pstBitstreamBuf 	= HI_NULL;
	DecOpenParam    *pDecOP	   		= {0};
    
    if(HI_NULL == pChanCtx || HI_NULL == pstParam)
    { 
        HI_ERR_VDEC("VPU_CreatForReset ERROR Param\n");
        return HI_FAILURE;
    }
    //1.需要检查参数是否合法：h265解码器中只支持h265；
    if ( HI_CODEC_ID_VIDEO_HEVC != pstParam->enID )
    { 
        HI_ERR_VDEC("Not supported standard!\n");
        return HI_FAILURE;
    }
 
    if ( HI_NULL != pChanCtx)
    {
        handle = &(pChanCtx->pHandle);
        pDecOP = &(pChanCtx->stOpenParam);
        pChanCtx->bRegFrameBuffer = HI_FALSE ;
        pChanCtx->bStartDecPicFlag = HI_FALSE ;
        pChanCtx->bStartDecSeqFlag = HI_FALSE;
        pChanCtx->u32frameCount = 0 ;
    }

    pstBitstreamBuf = &(pChanCtx->stBitStreamBuf);
		
    s32Ret = VDEC_VPU_CreateStreamBuffer(pstBitstreamBuf);
    if ( s32Ret != RETCODE_SUCCESS )
    {
		HI_ERR_VDEC("fail to allocate bitstream buffer!\n");
        return HI_FAILURE;
    } 

	VDEC_VPU_FillDecOpenParm(pDecOP, pstBitstreamBuf);

    s32Ret = VPU_DecOpen(handle, pDecOP);	
    if( s32Ret != RETCODE_SUCCESS )
    {
		HI_ERR_VDEC("VPU_DecOpen failed Error!\n");
        return HI_FAILURE;
    }

	s32Ret = HI_VPU_CreateFrameList(pChanCtx->u32hVdec);
	if (HI_SUCCESS != s32Ret)
	{
		HI_ERR_VDEC("HI_VPU_CreateFrameList fialed:%d.\n",s32Ret);
	}

    s32Ret = VDEC_VPU_PtsAlloc(pChanCtx->u32hVdec, -1);
    if ( s32Ret != HI_SUCCESS )
    {
		HI_ERR_VDEC("fail to allocate PTS buffer!\n");
        return HI_FAILURE;
    }
	
	s32Ret = VDEC_VPU_InitPTSQueue( pChanCtx );
	if (HI_SUCCESS != s32Ret)
	{
		HI_ERR_VDEC("VDEC_VPU_InitPTSQueue fialed:%d.\n",s32Ret);
	}

	return HI_SUCCESS;
}

#ifdef ALLOC_MEM_FRAME_BY_FRAEM
/*****************************************************************************
brief     : destroy vpu Codec. CNcomment:销毁VPU解码器 CNend
attention :
param[in] : HI_HANDLE* 
retval    : 
see       :
*****************************************************************************/
HI_VOID HI_VPU_DestroyFrmBuffer(VPU_ALLOCED_FRAME_BUF_S *pFrmBuf)
{
	HI_S32 s32Ret       = HI_SUCCESS;
	HI_MMZ_BUF_S *pBuf  = HI_NULL;

	pBuf = &(pFrmBuf->stMmzBuf) ;
	if (0 == pBuf->phyaddr)
	{
		return;
	}

	if ( HI_TRUE == pFrmBuf->bAllocFromVdh)
	{
		s32Ret = VDEC_VPU_RevertFrameBuf(pBuf->phyaddr);
        #ifdef VPU_MEM_MAP
 		HI_MEM_Unmap(pBuf->user_viraddr);
        #endif
		if (HI_SUCCESS != s32Ret)
		{
			HI_ERR_VDEC("FUN:%s,L:%d  pBuf is null!\n", __FUNCTION__, __LINE__);
		}
	}
	else
	{
		s32Ret = VDEC_VPU_FreeBuffer(pBuf);
		if (HI_SUCCESS != s32Ret)
		{
			HI_ERR_VDEC("FUN:%s,L:%d  pBuf is null!\n", __FUNCTION__, __LINE__);
		}
	}

	memset(pBuf, 0, sizeof(HI_MMZ_BUF_S));
	
	return;
}
#endif
/*****************************************************************************
brief     : destroy vpu Codec. CNcomment:销毁VPU解码器 CNend
attention :
param[in] : HI_HANDLE* 
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_Destroy(HI_HANDLE hInst)
{
 	HI_S32 s32Ret    = HI_SUCCESS, i = 0;
	DecHandle handle = HI_NULL;
	HI_MMZ_BUF_S *pBuf = HI_NULL;
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;

	DecOutputInfo stOutPutInfo	= {0};

    VPU_CHAN_CHECK(hInst);
    pChanCtx = &g_VPUChanCtx[hInst];
	
    //get VPU instance and coreIdx
    handle = g_VPUChanCtx[hInst].pHandle;

 	VPU_DecUpdateBitstreamBuffer(handle, STREAM_END_SIZE);
	VPU_DecGetOutputInfo(handle, &stOutPutInfo);

    /** CNcomment: 关闭VPU解码通道
    **/
    s32Ret = VPU_DecClose(handle);
    if (s32Ret != RETCODE_SUCCESS)
    {
        HI_ERR_VDEC("FUN:%s,L:%d close vpu failed!\n", __FUNCTION__, __LINE__);
    }
	g_VPUChanCtx[hInst].pHandle = HI_NULL ;
 
    /** CNcomment: 释放PTS相关资源
    **/
    s32Ret = VDEC_VPU_PtsFree(pChanCtx->u32hVdec, pChanCtx->u32ChanId);
    if ( s32Ret != HI_SUCCESS )
    {
        HI_ERR_VDEC("FUN:%s,L:%d free PTS buffer failed!\n", __FUNCTION__, __LINE__);
    }
	
	s32Ret = VDEC_VPU_DeinitPTSQueue( &(pChanCtx->stPtsQueue));
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VDEC("FUN:%s,L:%d Deniit failed!\n", __FUNCTION__, __LINE__);
    }

    /** CNcomment: 释放码流BUF
    **/
	pBuf = &(g_VPUChanCtx[hInst].stBitStreamBuf);
	if( HI_NULL != pBuf )
	{
	    s32Ret = VDEC_VPU_FreeBuffer(pBuf);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_VDEC("FUN:%s,L:%d free vdec vpu stream buf failed!\n", __FUNCTION__, __LINE__);
        }
	}
#ifndef ALLOC_MEM_FRAME_BY_FRAEM

    /** CNcomment: 释放1D帧存
    **/
	pBuf = &(g_VPUChanCtx[hInst].stCompressFrmBuf[0]);
	if( HI_NULL != pBuf )
	{
    	s32Ret = VDEC_VPU_RevertFrameBuf(pBuf->phyaddr);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_VDEC("FUN:%s,L:%d free vdec vpu 1d frame buf failed!\n", __FUNCTION__, __LINE__);
        }
	}

    /** CNcomment: 释放2D帧存
    **/
	pBuf = &(g_VPUChanCtx[hInst].stLinearFrmBuf[0]);
	if( HI_NULL != pBuf )
	{
    	s32Ret = VDEC_VPU_RevertFrameBuf(pBuf->phyaddr);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_VDEC("FUN:%s,L:%d free vdec vpu 2d frame buf failed!\n", __FUNCTION__, __LINE__);
        }
	}
#else   
    /** CNcomment: 释放1D帧存
    **/
    for ( i = 0; i < pChanCtx->u32ActualFrameNum; i++)
	{
		HI_VPU_DestroyFrmBuffer( &(g_VPUChanCtx[hInst].stCompressFrmBuf[i]) );
	}


    /** CNcomment: 释放2D帧存
    **/
	for ( i = 0; i < pChanCtx->u32ActualFrameNum; i++)
	{
		HI_VPU_DestroyFrmBuffer( &(g_VPUChanCtx[hInst].stLinearFrmBuf[i]) );
	}
#endif

    /** CNcomment: 释放帧存节点
    **/
	s32Ret = HI_VPU_ReleaseFrameList(g_VPUChanCtx[hInst].u32hVdec);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VDEC("FUN:%s,L:%d release frame list failed!\n", __FUNCTION__, __LINE__);
    }

    /** CNcomment: 释放文件资源
    **/
    if (HI_NULL != g_VPUChanCtx[hInst].fp2DYuv)
    {
        fclose(g_VPUChanCtx[hInst].fp2DYuv);
        g_VPUChanCtx[hInst].fp2DYuv = HI_NULL;
    }

    if (HI_NULL != g_VPUChanCtx[hInst].fpStream)
    {
        fclose(g_VPUChanCtx[hInst].fpStream);
        g_VPUChanCtx[hInst].fpStream = HI_NULL;
    }

    /** CNcomment: 这个地方得细考虑下，有些变量初始化不能直接赋零的值
    **/
    VDEC_VPU_CtxReset(hInst);
	
    return HI_SUCCESS ;
}

/*****************************************************************************
brief     : start vpu Codec. CNcomment:启动VPU解码器 CNend
attention :
param[in] : HI_HANDLE* 
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_Start(HI_HANDLE phInst)
{
	HI_S32 s32Ret = 0;
	VPU_CHAN_CTX_S *pChanCtx = HI_NULL;

    VPU_CHAN_CHECK(phInst);
    pChanCtx = &g_VPUChanCtx[phInst];

	s32Ret = VDEC_VPU_Start(phInst);
    VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);

	s32Ret = VDEC_VPU_PtsStart(pChanCtx->u32hVdec);
    VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);
	
    pChanCtx->eChanState = VPU_STATE_RUN;

    return s32Ret;
}

/*****************************************************************************
brief     : stop vpu Codec. CNcomment:停止VPU解码器 CNend
attention :
param[in] : HI_HANDLE* 
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_Stop(HI_HANDLE phInst)
{
	HI_S32 s32Ret = 0;
	VPU_CHAN_CTX_S *pChanCtx = HI_NULL;

    VPU_CHAN_CHECK(phInst);
    pChanCtx = &g_VPUChanCtx[phInst];
	
	s32Ret = VDEC_VPU_Stop(phInst);
    VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);

	s32Ret = VDEC_VPU_PtsStop(pChanCtx->u32hVdec);
    VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);

    pChanCtx->eChanState = VPU_STATE_STOP;
	
    return s32Ret;
}

/*****************************************************************************
brief     : CNcomment: SEEK 功能
attention :
param[in] : VPU_CHAN_CTX_S *
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_Seek(VPU_CHAN_CTX_S *pChanCtx)
{
    HI_S32 s32Ret = 0;
    HI_U32 i = 0;
    HI_U32 u32RegFrmBufCount = 0;
    
    if (HI_NULL == pChanCtx)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pChanCtx is null!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    u32RegFrmBufCount = pChanCtx->u32ActualFrameNum;
    

    /** CNcomment: 释放PTS相关资源
    **/
    s32Ret = VDEC_VPU_PtsFree(pChanCtx->u32hVdec, -1);
    if ( s32Ret != HI_SUCCESS )
    {
        HI_ERR_VDEC("FUN:%s,L:%d free PTS buffer failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
    memset(pChanCtx->stDecFrmBuf, 0x0, sizeof(VPU_DEC_FRAME_BUF_S)*VPU_MAX_FRAME_NUM);

    /** CNcomment: 释放帧队列相关资源
    **/
    s32Ret = HI_VPU_ReleaseFrameList(pChanCtx->u32hVdec);
	VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);
    memset(pChanCtx->stDispFrmBuf, 0x0, sizeof(VPU_DISP_FRAME_BUF_S)*VPU_MAX_FRAME_NUM);

    
    for(i = 0; i < u32RegFrmBufCount; i++)
    {
        // clear the display buffers except putTOVpss
        if (HI_TRUE == pChanCtx->stDispFrmBuf[i].bPutToVpss)
        {
            VPU_DecClrDispFlag(pChanCtx->pHandle, i);
        }
        pChanCtx->stDispFrmBuf[i].bPutToVpss = HI_FALSE;
    }

    /** can clear all display buffer before Bitstream buffer flush
        if HOST wants clearing all remained frame in buffer.
    **/ 
    s32Ret = VPU_DecFrameBufferFlush(pChanCtx->pHandle, HI_NULL, HI_NULL);
    if(RETCODE_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("FUN:%s,L:%d VPU_DecGetBitstreamBuffer failed Error code is 0x%x\n",__FUNCTION__, __LINE__, s32Ret);
        return HI_FAILURE;
    }


#if 0
    /** clear all frame buffer except current frame
    **/
    for(i = 0; i < u32RegFrmBufCount; i++)
    {
        // clear the display buffers except putTOVpss
        if (HI_TRUE == pChanCtx->stDispFrmBuf[i].bPutToVpss)
        {
            VPU_DecGiveCommand(pChanCtx->pHandle, DEC_SET_DISPLAY_FLAG, &i);
            printf("%d ",i);
        }
        printf("\n");
    }

    printf("----------seek start --------\n");
#ifdef FRM_BUF_STATE
        {
            printf("Satus: ");
            for (i = 0; i < pChanCtx->u32ActualFrameNum; i++)
            {
                printf("%d ",pChanCtx->stDispFrmBuf[i].bPutToVpss);
            }
            printf("\n");
        }
#endif
#endif

    /** clear bitstream buffer
    **/ 
    s32Ret = VPU_DecSetRdPtr(pChanCtx->pHandle, pChanCtx->stOpenParam.bitstreamBuffer, 1);
    if(RETCODE_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("FUN:%s,L:%d VPU_DecSetRdPtr failed Error code is 0x%x\n", __FUNCTION__, __LINE__, s32Ret);
        return HI_FAILURE;
    }

    /** to find I(IDR) frame
    **/ 
    pChanCtx->stParam.skipframeMode = 1;

    /**CNcomment: 创建VDEC 帧存列表
    **/
    s32Ret = HI_VPU_CreateFrameList(pChanCtx->u32hVdec);
	if (HI_SUCCESS != s32Ret)
	{
        HI_ERR_VDEC("FUN:%s,L:%d HI_VPU_Seek for VPU failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
	}

    
    /**CNcomment: 创建VDEC PTS 列表
    **/
    s32Ret = VDEC_VPU_PtsAlloc(pChanCtx->u32hVdec, -1);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VDEC("FUN:%s,L:%d VDEC_VPU_PtsAlloc for VPU failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
	
    /**CNcomment: 初始化PTS 队列
    **/
	s32Ret = VDEC_VPU_InitPTSQueue(pChanCtx);
	if (HI_SUCCESS != s32Ret)
	{
        HI_ERR_VDEC("FUN:%s,L:%d VDEC_VPU_InitPTSQueue for VPU failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
	}
    

    return HI_SUCCESS;

}



/*****************************************************************************
brief     : reset vpu Codec. CNcomment:复位VPU解码器 CNend
attention :
param[in] : HI_HANDLE* 
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_Reset(HI_HANDLE hInst)
{
	HI_S32 s32Ret = 0;
	HI_CODEC_OPENPARAM_S  stCodecParam;
    HI_CODEC_ATTR_S       stCodecAttr;
	VPU_CHAN_CTX_S *pChanCtx = HI_NULL;

    VPU_CHAN_CHECK(hInst);
    pChanCtx = &g_VPUChanCtx[hInst];
    memcpy(&stCodecParam, &(pChanCtx->stCodecParam), sizeof(HI_CODEC_OPENPARAM_S));
    memcpy(&stCodecAttr, &(pChanCtx->stCodecAttr), sizeof(HI_CODEC_ATTR_S));

	s32Ret = VDEC_VPU_PtsReset(pChanCtx->u32hVdec);
    VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);
	
#ifdef VPU_ResetTime_Statistics_SUPPORT
   	s32Ret = HI_SYS_GetTimeStampMs(&g_time[0]);
#endif		

    /**CNcomment: 目前VPU无法知道上层是RESET 直接播下一条还是SEEK,所以暂时不修改，沿用
       原来创建销毁的方案，后续考虑
    **/
//  HI_VPU_Seek(pChanCtx);
 
    /**CNcomment: SEEK 相关不能与RESET强行绑定，这样会导致接口的混乱，应用出错
       要求，上层传入SEEK标志，在VDEC上HEVC走分支，实现创建和销毁动作 TODO
    **/
    s32Ret = HI_VPU_Destroy(hInst);
    VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);

//	s32Ret = VPU_CreatForReset(pChanCtx, &stParam);
	s32Ret = HI_VPU_Create(&hInst, &stCodecParam);
	VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);
 
    return s32Ret;
}

/*****************************************************************************
brief     : set vpu Codec attribute. CNcomment:设置VPU解码器属性 CNend
attention :
param[in] : HI_HANDLE
param[in] : HI_CODEC_ATTR_S*
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_SetAttr(HI_HANDLE hInst, const HI_CODEC_ATTR_S* pstAttr)
{
    HI_S32 s32Ret = 0;
	HI_HANDLE hVdec = 0;
	VDEC_VPU_ATTR_S stVPUAttr = {0};
	DecHandle phandle 			= HI_NULL;
    VPU_CHAN_CTX_S *pChanCtx 	= HI_NULL;
    HI_UNF_VCODEC_ATTR_S* pstPrivAttr = HI_NULL;

    if (HI_NULL == pstAttr)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pstAttr is null!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
			
    VPU_CHAN_CHECK(hInst);
    pChanCtx = &g_VPUChanCtx[hInst];
    phandle  = pChanCtx->pHandle;
	
	if(HI_CODEC_ID_VIDEO_HEVC != pstAttr->enID)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pstAttr->enID is not HEVC!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

	hVdec = g_VPUChanCtx[hInst].u32hVdec;
	stVPUAttr.bVPU = 1;

	s32Ret = VDEC_VPU_SetAttr(hVdec, &stVPUAttr);
    VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);

    pstPrivAttr = (HI_UNF_VCODEC_ATTR_S *)pstAttr->unAttr.stVdec.pPlatformPriv;
    VDEC_VPU_SetAttrOpt(pstPrivAttr, pChanCtx);

    memcpy(&(pChanCtx->stCodecAttr), pstAttr, sizeof(HI_CODEC_ATTR_S));
	
    return HI_SUCCESS;
}

/*****************************************************************************
brief     : get vpu Codec attribute. CNcomment:获取VPU解码器属性 CNend
attention :
param[in] : HI_HANDLE
param[out]: HI_CODEC_ATTR_S*
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_GetAttr(HI_HANDLE hInst, HI_CODEC_ATTR_S* pstAttr)
{
    VPU_CHAN_CTX_S *pChanCtx 	= HI_NULL;

    VPU_CHAN_CHECK(hInst);
    pChanCtx = &g_VPUChanCtx[hInst];

    memcpy(pstAttr, &(pChanCtx->stCodecAttr), sizeof(HI_CODEC_ATTR_S));

    return HI_SUCCESS;
}


/*****************************************************************************
brief     : register frame buffer to  vpu Codec. CNcomment:向VPU解码器注册帧存CNend
attention : H265 only
param[in] : HI_HANDLE
param[in] : HI_CODEC_FRAME_BUF_S * 
param[in] : HI_U32
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_RegFrameBuffer(HI_HANDLE hInst, HI_CODEC_STREAM_S *pstRawPacket)
{
	HI_U32 u32FrameNum = 0;
	HI_U32 u32StrBufInsufficientFlag = 0;
    HI_S32 s32IntReason = 0;
    HI_S32 fbSize = 0, mvcolSize = 0,stride = 0 ,height = 0, fbOffsetSizeY = 0, fbOffsetSizeC= 0;
	HI_S32 CompressedfbSize = 0 , LinearfbSize = 0 ;
	HI_S32 s32Ret = 0,i = 0, timeout_count = 0;
    VPU_CHAN_CTX_S *pChanCtx = NULL;
    DecHandle phandle = NULL;
    DecInitialInfo stSeqInfo;
    FrameBufferAllocInfo stAllocInfo;
    FrameBuffer stFbArray[VPU_MAX_FRAME_NUM*2];
	HI_DRV_VDEC_FRAME_BUF_S pstBuf[VPU_MAX_FRAME_NUM];

    /** 对局部变量进行初始化
    **/
    VPU_CHAN_CHECK(hInst);
    pChanCtx = &g_VPUChanCtx[hInst];
    phandle = pChanCtx->pHandle;
    memset(&stSeqInfo, 0, sizeof(DecInitialInfo));
    memset(&stAllocInfo, 0, sizeof(FrameBufferAllocInfo));
	memset(&stFbArray, 0, sizeof(FrameBuffer)*VPU_MAX_FRAME_NUM*2);
	memset(&pstBuf, 0, sizeof(HI_DRV_VDEC_FRAME_BUF_S)*VPU_MAX_FRAME_NUM);

    if ((HI_TRUE == pChanCtx->bRegFrameBuffer) || (HI_TRUE == pChanCtx->bIsNotSupport))
	{
		return HI_SUCCESS;
	}

    /** 为了避免码流不足导致解头信息不成功，如果收到的码流小于1K时，就
        不进行解头信息动作
    **/
    if ((HI_NULL == pstRawPacket) && (pChanCtx->u64RecvPackSize < 1024))
    {
        return HI_FAILURE;
    }

    /** 送码流,码流的大小是否足够解头信息，可在这里做一个经验值判断
    **/
    s32Ret = VDEC_VPU_FillRawPacket(pChanCtx, pstRawPacket);
	if (VPU_STR_BUF_INSUFFICIENT == s32Ret)
	{
		u32StrBufInsufficientFlag = 1;
	}
	
    /** 启动解头信息
    **/
    if (HI_FALSE == pChanCtx->bStartDecSeqFlag)
	{
		s32Ret = VPU_DecIssueSeqInit(phandle);
		pChanCtx->bStartDecSeqFlag = HI_TRUE ;
		VPU_ASSERT_EQ(RETCODE_SUCCESS, s32Ret);
	}


    /** 等待解头信息中断
    **/
    do
    {
    	s32IntReason = VPU_WaitInterrupt(phandle->coreIdx, VPU_WAIT_TIME_OUT);

        if (s32IntReason == -1) // timeout
        {
            if (timeout_count * VPU_WAIT_TIME_OUT > VPU_DEC_TIMEOUT)
            {
                HI_ERR_VDEC("VPU interrupt wait timeout instIdx=%d, PC=0x%08x\n", phandle->coreIdx, VpuReadReg(phandle->coreIdx, 0x04));
                VPU_SWReset(phandle->coreIdx, SW_RESET_SAFETY, phandle);
                break;
            }
            timeout_count++;
            s32IntReason = 0;
        }

		if (s32IntReason > 0)
        {
            VPU_ClearInterrupt(phandle->coreIdx);
			
            if (s32IntReason & (1<<VPU_INT_DEC_PIC_HDR))
            {
				pChanCtx->bStartDecSeqFlag = HI_FALSE ;
                break;
            }
            else if (s32IntReason & (1<<INT_WAVE_BIT_BUF_EMPTY))
            {
                pChanCtx->bStartDecSeqFlag = HI_TRUE;
			    s32Ret = u32StrBufInsufficientFlag ? VPU_STR_BUF_INSUFFICIENT_FAILURE : HI_FAILURE;
				return s32Ret;
            }
            else
            {
            }
        }
    } while (1);

    /** 获取头信息
    **/
    s32Ret = VPU_DecCompleteSeqInit(phandle, &stSeqInfo);
    if (RETCODE_FAILURE == s32Ret && 
        stSeqInfo.seqInitErrReason == WAVE4_SPSERR_NOT_FOUND) 
    {
        pChanCtx->bStartDecSeqFlag = HI_FALSE;
        return (u32StrBufInsufficientFlag ? VPU_STR_BUF_INSUFFICIENT_FAILURE : HI_FAILURE);
    }

    pChanCtx->u32Profile        = stSeqInfo.profile;
	pChanCtx->u32LumaBitdepth   = stSeqInfo.lumaBitdepth;
	pChanCtx->u32ChromaBitdepth = stSeqInfo.chromaBitdepth;
    HI_VPU_PROC_STATUS(pChanCtx, HI_NULL);
    
    if (VPU_MAIN_PROFILE_8BIT != stSeqInfo.lumaBitdepth || 
        VPU_MAIN_PROFILE_8BIT != stSeqInfo.chromaBitdepth)
    {
    #ifdef VPU_EVENTS_TEST
        pChanCtx->stVpuEvents.bDecErr          = HI_TRUE ; 
        pChanCtx->stVpuEvents.VpuDecFailReason = VPU_MAIN_PROFILE_NOT_8BIT ; 
    #endif      

        pChanCtx->bStartDecSeqFlag = HI_FALSE;
        return (u32StrBufInsufficientFlag ? VPU_STR_BUF_INSUFFICIENT_FAILURE : HI_FAILURE);
    }
    VPU_ASSERT_EQ(RETCODE_SUCCESS, s32Ret);

#ifdef OUTPUT_DecInfo
	HI_ERR_VDEC("*HI_VPU_RegFrameBuffer: Dec InitialInfo =>\n instance #%d, \n minframeBuffercount: %u\n ", phandle->coreIdx, stSeqInfo.minFrameBufferCount);
    HI_ERR_VDEC("picWidth: %u\n picHeight: %u\n ",stSeqInfo.picWidth, stSeqInfo.picHeight); 
    if (stSeqInfo.fRateDenominator)
        HI_ERR_VDEC("frameRate: %.2f\n ",(double)(stSeqInfo.fRateNumerator/(stSeqInfo.fRateDenominator)) );
    HI_ERR_VDEC("frRes: %u\n frDiv: %u\n",stSeqInfo.fRateNumerator, stSeqInfo.fRateDenominator);
#endif	

    /**CNcomment: 获取显示宽高比
    **/
    if (stSeqInfo.isExtSAR)
    {
        pChanCtx->u32SarWidth  = (stSeqInfo.aspectRateInfo&0xffff0000) >> 16;
        pChanCtx->u32SarHeight = (stSeqInfo.aspectRateInfo&0xffff);
    }
    else
    {
        pChanCtx->u32SarIndex  = stSeqInfo.aspectRateInfo;
    }

	stride = HI_SYS_GET_STRIDE(stSeqInfo.picWidth);
	height = VPU_ALIGN16(stSeqInfo.picHeight);

    /** 计算 Frame buffer 大小
    **/
    fbSize    = VPU_GetFrameBufSize(phandle->coreIdx, stride, height, COMPRESSED_FRAME_MAP, FORMAT_420, 0, NULL);
    mvcolSize = VPU_GetMvColBufSize(STD_HEVC, stride, height, 1);
    VPU_GetFBCOffsetTableSize(STD_HEVC, stride, height, &fbOffsetSizeY, &fbOffsetSizeC);

    VDEC_VPU_GetActualFrameNum(pChanCtx, &stSeqInfo, &u32FrameNum);
	pChanCtx->u32MinRefFrameNum = stSeqInfo.minFrameBufferCount; //记录最小帧存个数

    /** 申请帧存 for compress frame buffer，调用VDEC的帧存申请函数
    **/
    CompressedfbSize = fbSize + mvcolSize + fbOffsetSizeY + fbOffsetSizeC;
    CompressedfbSize = (CompressedfbSize + VPU_ALIGN_LEN - 1) & (~(VPU_ALIGN_LEN -1));
	pChanCtx->u32TotalMemSize = ((CompressedfbSize+ fbSize)*u32FrameNum)/(1024*1024);

#ifndef ALLOC_MEM_FRAME_BY_FRAEM
    /** 由于内存限制，对参考帧个数大于5的，约180M，上报不支持
    **/
    if (((CompressedfbSize + fbSize)*u32FrameNum  > VPU_FBUF_MMZ_MAX)&&(stSeqInfo.minFrameBufferCount > 7))
    {
        HI_ERR_VDEC("WARN!!!: MMZ_SIZE(%dM > 180M), RefNum(%d) > 7 is not support!!!\n",((CompressedfbSize+ fbSize)*u32FrameNum)/(1024*1024), stSeqInfo.minFrameBufferCount);
        pChanCtx->bIsNotSupport = HI_TRUE;
        return HI_FAILURE;
    }
    pChanCtx->bIsNotSupport = HI_FALSE;
#endif

    s32Ret = HI_VPU_CreateFrameBuf(CompressedfbSize, u32FrameNum, pChanCtx->stCompressFrmBuf);

	/** 如果申请的Compress内存不够，则将已经申请到的内存释放掉
    **/
#ifdef ALLOC_MEM_FRAME_BY_FRAEM
	if ( HI_SUCCESS != s32Ret)
	{
		for ( i = 0 ; i < u32FrameNum; i++)
		{
			HI_VPU_DestroyFrmBuffer( &(g_VPUChanCtx[hInst].stCompressFrmBuf[i]) );
		}

	#ifdef VPU_EVENTS_TEST
		pChanCtx->stVpuEvents.bDecErr				= HI_TRUE ; 
		pChanCtx->stVpuEvents.VpuDecFailReason 		= VPU_MEMORY_INSUFFICIENT ; 
	#endif 		
	    if (CompressedfbSize > 0 && u32FrameNum > 0)
    	{
			pChanCtx->bIsNotSupport = HI_TRUE;
    	}
		return HI_FAILURE;
	}
#endif

	for (i=0; i<u32FrameNum; i++) 
    {
    #ifdef ALLOC_MEM_FRAME_BY_FRAEM
        stFbArray[i].bufY  = pChanCtx->stCompressFrmBuf[i].stMmzBuf.phyaddr ; //for compress BUF
    #else
        stFbArray[i].bufY  = pChanCtx->stCompressFrmBuf[i].phyaddr ; //for compress BUF
	#endif
        stFbArray[i].bufCb = -1;
        stFbArray[i].bufCr = -1;
    }
	
    stAllocInfo.format         = FORMAT_420;
    stAllocInfo.cbcrInterleave = 0;
    stAllocInfo.mapType        = COMPRESSED_FRAME_MAP;
    stAllocInfo.stride         = stride;
    stAllocInfo.height         = stSeqInfo.picHeight;
    stAllocInfo.num            = u32FrameNum;//stSeqInfo.minFrameBufferCount;
    stAllocInfo.endian         = pChanCtx->stOpenParam.frameEndian;
    stAllocInfo.type           = FB_TYPE_CODEC;
    s32Ret = VPU_DecAllocateFrameBuffer(phandle, stAllocInfo, stFbArray);
    VPU_ASSERT_EQ(RETCODE_SUCCESS, s32Ret); 

    /** 申请帧存 for for linear frame buffer,调用VDEC的帧存申请函数
    **/
    LinearfbSize = fbSize;
    LinearfbSize = (LinearfbSize + VPU_ALIGN_LEN - 1) & (~(VPU_ALIGN_LEN -1));
#ifdef OUTPUT_DecInfo
	HI_ERR_VDEC("HI_VPU_RegFrameBuffer:CompressedfbSize = %d || LinearfbSize = %d\n",CompressedfbSize, LinearfbSize);
#endif			
    s32Ret = HI_VPU_CreateFrameBuf(LinearfbSize, u32FrameNum, pChanCtx->stLinearFrmBuf);
	/** 如果申请的Linear内存不够，则将已经申请到的所有内存释放掉
    **/
#ifdef ALLOC_MEM_FRAME_BY_FRAEM
	if ( HI_SUCCESS != s32Ret)
	{
		for ( i = 0 ; i < u32FrameNum; i++)
		{
			HI_VPU_DestroyFrmBuffer( &(g_VPUChanCtx[hInst].stCompressFrmBuf[i]) );
			HI_VPU_DestroyFrmBuffer( &(g_VPUChanCtx[hInst].stLinearFrmBuf[i]) );
		}

	#ifdef VPU_EVENTS_TEST
		pChanCtx->stVpuEvents.bDecErr				= HI_TRUE ; 
		pChanCtx->stVpuEvents.VpuDecFailReason 		= VPU_MEMORY_INSUFFICIENT ; 
	#endif 		
	
		if (CompressedfbSize > 0 && u32FrameNum > 0)
		{
			pChanCtx->bIsNotSupport = HI_TRUE;
		}
		
		return HI_FAILURE;
	}
#endif
    for (i = 0; i < u32FrameNum; i++) 
    {
    #ifdef ALLOC_MEM_FRAME_BY_FRAEM
        stFbArray[i + u32FrameNum].bufY  = pChanCtx->stLinearFrmBuf[i].stMmzBuf.phyaddr; //for linear BUF
    #else
		stFbArray[i + u32FrameNum].bufY  = pChanCtx->stLinearFrmBuf[i].phyaddr; //for linear BUF
	#endif
        stFbArray[i + u32FrameNum].bufCb = -1;
        stFbArray[i + u32FrameNum].bufCr = -1;
    }

    stAllocInfo.format         = FORMAT_420;
    stAllocInfo.cbcrInterleave = 1;
    stAllocInfo.mapType        = LINEAR_FRAME_MAP;
    stAllocInfo.stride         = stride;

    stAllocInfo.height         = stSeqInfo.picHeight;
    stAllocInfo.num            = u32FrameNum;//stSeqInfo.minFrameBufferCount;
    stAllocInfo.endian         = pChanCtx->stOpenParam.frameEndian;
    stAllocInfo.type           = FB_TYPE_CODEC;
    s32Ret = VPU_DecAllocateFrameBuffer(phandle, stAllocInfo, &(stFbArray[u32FrameNum]));
    VPU_ASSERT_EQ(RETCODE_SUCCESS, s32Ret);

    /** 注册帧存,一次性注册即可
    **/
#if 0
    s32Ret = VPU_DecRegisterFrameBuffer(phandle, stFbArray, u32FrameNum, stride, height, COMPRESSED_FRAME_MAP);
    VPU_ASSERT_EQ(RETCODE_SUCCESS, s32Ret);
#else
    s32Ret = VPU_DecRegisterFrameBuffer(phandle, stFbArray, u32FrameNum, stride, height, COMPRESSED_FRAME_MAP);
    if ( RETCODE_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("*******************free frame buff******************\n");
        for ( i = 0 ; i < u32FrameNum; i++)
        {
            HI_VPU_DestroyFrmBuffer( &(g_VPUChanCtx[hInst].stCompressFrmBuf[i]) );
            HI_VPU_DestroyFrmBuffer( &(g_VPUChanCtx[hInst].stLinearFrmBuf[i]) );
        }
        return HI_FAILURE;
    }
#endif
#ifdef VPU_ResetTime_Statistics_SUPPORT
	s32Ret = HI_SYS_GetTimeStampMs(&g_time[1]);
//	HI_ERR_VDEC("HI_VPU_RegFrameBuffer: finished time =%d\n",g_time[1]);
#endif
	
    pChanCtx->bRegFrameBuffer = HI_TRUE;
    return HI_SUCCESS;
}



/*****************************************************************************
brief     : RegFrameBufferWithoutWaitInterrupt: 根据保持的头信息直接注册帧存
attention : H265 only
param[in] : HI_HANDLE
param[in] : HI_CODEC_FRAME_BUF_S * 
param[in] : HI_U32
retval    : 
see       :
*****************************************************************************/
HI_S32 RegFrameBufferWithoutWaitInterrupt(VPU_CHAN_CTX_S *pChanCtx)
{
	HI_U32 u32FrameNum = 0;
    HI_S32 fbSize = 0, mvcolSize = 0,stride = 0;
    HI_S32 height = 0, fbOffsetSizeY = 0, fbOffsetSizeC= 0;
	HI_S32 CompressedfbSize = 0, LinearfbSize = 0 ;
	HI_S32 s32Ret = 0, i = 0;
	
    DecHandle phandle = NULL;
    DecInitialInfo stSeqInfo;
    FrameBufferAllocInfo stAllocInfo;
    FrameBuffer stFbArray[VPU_MAX_FRAME_NUM*2];
	HI_DRV_VDEC_FRAME_BUF_S pstBuf[VPU_MAX_FRAME_NUM];

    phandle = pChanCtx->pHandle;
    memset(&stSeqInfo, 0x0, sizeof(DecInitialInfo));
    memset(&stAllocInfo, 0x0, sizeof(FrameBufferAllocInfo));
	memset(&stFbArray, 0x0, sizeof(FrameBuffer)*VPU_MAX_FRAME_NUM*2);
	memset(&pstBuf, 0x0, sizeof(HI_DRV_VDEC_FRAME_BUF_S)*VPU_MAX_FRAME_NUM);

	stSeqInfo = pChanCtx->pHandle->CodecInfo.decInfo.initialInfo;

#ifdef OUTPUT_DecInfo
	HI_ERR_VDEC("* RegFrameBufferWithoutWaitInterrupt:Dec InitialInfo =>\n instance #%d, \n minframeBuffercount: %u\n ", phandle->coreIdx, stSeqInfo.minFrameBufferCount);
    HI_ERR_VDEC("picWidth: %u\n picHeight: %u\n ",stSeqInfo.picWidth, stSeqInfo.picHeight); 
    if (stSeqInfo.fRateDenominator)
        HI_ERR_VDEC("frameRate: %.2f\n ",(double)(stSeqInfo.fRateNumerator/(stSeqInfo.fRateDenominator)) );
    HI_ERR_VDEC("frRes: %u\n frDiv: %u\n",stSeqInfo.fRateNumerator, stSeqInfo.fRateDenominator);
#endif	

	stride = HI_SYS_GET_STRIDE(stSeqInfo.picWidth);;
	height = VPU_ALIGN16(stSeqInfo.picHeight);

    fbSize    = VPU_GetFrameBufSize(phandle->coreIdx, stride, height, COMPRESSED_FRAME_MAP, FORMAT_420, 0, NULL);
    mvcolSize = VPU_GetMvColBufSize(STD_HEVC, stride, height, 1);
    VPU_GetFBCOffsetTableSize(STD_HEVC, stride, height, &fbOffsetSizeY, &fbOffsetSizeC);

    VDEC_VPU_GetActualFrameNum(pChanCtx, &stSeqInfo, &u32FrameNum);
	pChanCtx->u32MinRefFrameNum = stSeqInfo.minFrameBufferCount; //记录最小帧存个数

    /**CNcomment: 申请帧存 for compress frame buffer
    **/
    CompressedfbSize = fbSize + mvcolSize + fbOffsetSizeY + fbOffsetSizeC;
    CompressedfbSize = (CompressedfbSize + VPU_ALIGN_LEN - 1) & (~(VPU_ALIGN_LEN -1));

#ifndef ALLOC_MEM_FRAME_BY_FRAEM

    /** 由于内存限制，对参考帧个数大于5的，约135M，上报不支持
    **/
    if (((CompressedfbSize+ fbSize)*u32FrameNum  > VPU_FBUF_MMZ_MAX)&&(stSeqInfo.minFrameBufferCount > 5))
    {
        HI_ERR_VDEC("WARN!!!: MMZ_SIZE(%dM > 130M), RefNum(%d) > 5 is not support!!!\n",((CompressedfbSize+ fbSize)*u32FrameNum)/(1024*1024), stSeqInfo.minFrameBufferCount);
        pChanCtx->bIsNotSupport = HI_TRUE;
        return HI_FAILURE;
    }
    pChanCtx->bIsNotSupport = HI_FALSE;
#endif

    s32Ret = HI_VPU_CreateFrameBuf(CompressedfbSize, u32FrameNum, pChanCtx->stCompressFrmBuf);
#ifdef ALLOC_MEM_FRAME_BY_FRAEM
	if ( HI_SUCCESS != s32Ret)
	{
		pChanCtx->bIsNotSupport = HI_TRUE;	
		
		for ( i = 0 ; i < u32FrameNum; i++)
		{
			HI_VPU_DestroyFrmBuffer( &(pChanCtx->stCompressFrmBuf[i]) );
		}

	#ifdef VPU_EVENTS_TEST
		pChanCtx->stVpuEvents.bDecErr				= HI_TRUE ; 
		pChanCtx->stVpuEvents.VpuDecFailReason	 	= VPU_MEMORY_INSUFFICIENT ; 
	#endif 		
		
		return HI_FAILURE;
	}
#endif 
	for (i=0; i<u32FrameNum; i++) 
    {
    #ifdef ALLOC_MEM_FRAME_BY_FRAEM
        stFbArray[i].bufY  = pChanCtx->stCompressFrmBuf[i].stMmzBuf.phyaddr ; //for compress BUF
    #else
        stFbArray[i].bufY  = pChanCtx->stCompressFrmBuf[i].phyaddr ; //for compress BUF
    #endif
        stFbArray[i].bufCb = -1;
        stFbArray[i].bufCr = -1;
    }
	
    stAllocInfo.format         = FORMAT_420;
    stAllocInfo.cbcrInterleave = 0;
    stAllocInfo.mapType        = COMPRESSED_FRAME_MAP;
    stAllocInfo.stride         = stride;
    stAllocInfo.height         = stSeqInfo.picHeight;
    stAllocInfo.num            = u32FrameNum;//stSeqInfo.minFrameBufferCount;
    stAllocInfo.endian         = pChanCtx->stOpenParam.frameEndian;
    stAllocInfo.type           = FB_TYPE_CODEC;
    s32Ret = VPU_DecAllocateFrameBuffer(phandle, stAllocInfo, stFbArray);
    VPU_ASSERT_EQ(RETCODE_SUCCESS, s32Ret); 

    /**CNcomment: 申请帧存 for for linear frame buffer
    **/
    LinearfbSize = fbSize;
    LinearfbSize = (LinearfbSize + VPU_ALIGN_LEN - 1) & (~(VPU_ALIGN_LEN -1));
#ifdef OUTPUT_DecInfo
	HI_ERR_VDEC("RegFrameBufferWithoutWaitInterrupt: CompressedfbSize = %d || LinearfbSize = %d\n",CompressedfbSize, LinearfbSize);
#endif			
    s32Ret = HI_VPU_CreateFrameBuf(LinearfbSize, u32FrameNum, pChanCtx->stLinearFrmBuf);
#ifdef ALLOC_MEM_FRAME_BY_FRAEM
		if ( HI_SUCCESS != s32Ret)
		{
			pChanCtx->bIsNotSupport = HI_TRUE;	
			
			for ( i = 0 ; i < u32FrameNum; i++)
			{
				HI_VPU_DestroyFrmBuffer( &(pChanCtx->stCompressFrmBuf[i]) );
				HI_VPU_DestroyFrmBuffer( &(pChanCtx->stLinearFrmBuf[i]) );
			}

	#ifdef VPU_EVENTS_TEST
		pChanCtx->stVpuEvents.bDecErr				= HI_TRUE ; 
		pChanCtx->stVpuEvents.VpuDecFailReason	 	= VPU_MEMORY_INSUFFICIENT ; 
	#endif 		
			
			return HI_FAILURE;
		}
#endif

    for (i = 0; i < u32FrameNum; i++) 
    {
    #ifdef ALLOC_MEM_FRAME_BY_FRAEM
        stFbArray[i + u32FrameNum].bufY  = pChanCtx->stLinearFrmBuf[i].stMmzBuf.phyaddr; //for linear BUF
    #else
        stFbArray[i + u32FrameNum].bufY  = pChanCtx->stLinearFrmBuf[i].phyaddr; //for linear BUF
    #endif
        stFbArray[i + u32FrameNum].bufCb = -1;
        stFbArray[i + u32FrameNum].bufCr = -1;
    }

    stAllocInfo.format         = FORMAT_420;
    stAllocInfo.cbcrInterleave = 1;
    stAllocInfo.mapType        = LINEAR_FRAME_MAP;
    stAllocInfo.stride         = stride;

    stAllocInfo.height         = stSeqInfo.picHeight;
    stAllocInfo.num            = u32FrameNum;//stSeqInfo.minFrameBufferCount;
    stAllocInfo.endian         = pChanCtx->stOpenParam.frameEndian;
    stAllocInfo.type           = FB_TYPE_CODEC;
    s32Ret = VPU_DecAllocateFrameBuffer(phandle, stAllocInfo, &(stFbArray[u32FrameNum]));
    VPU_ASSERT_EQ(RETCODE_SUCCESS, s32Ret);

    /**CNcomment: 注册帧存,一次性注册即可
    **/
    s32Ret = VPU_DecRegisterFrameBuffer(phandle, stFbArray, u32FrameNum, stride, height, COMPRESSED_FRAME_MAP);
    VPU_ASSERT_EQ(RETCODE_SUCCESS, s32Ret);

	pChanCtx->bRegFrameBuffer = HI_TRUE;
    return HI_SUCCESS;
}

/*****************************************************************************
brief     : HI_VDEC_PutFrame: 将解码出来的帧信息送给VDEC队列
attention : 
param[in] : HI_HANDLE
param[in] : HI_DRV_VDEC_USR_FRAME_S * 
param[in] : HI_S32
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VDEC_PutFrame(HI_HANDLE hVdec,HI_DRV_VDEC_USR_FRAME_S *pstBuf)
{
    HI_S32 s32Ret;

	if(HI_NULL == pstBuf)
	{
        HI_ERR_VDEC("FUN:%s,L:%d pstBuf is null!\n", __FUNCTION__, __LINE__);
		return HI_FAILURE;
	}
	s32Ret = VDEC_VPU_PutFrame(hVdec,pstBuf);

    return s32Ret;
}

/*****************************************************************************
brief     : HI_VDEC_PutFrame: 将VPU解码出来的帧信息送给VDEC队列
attention : 
param[in] : 
param[in] : 
param[in] : HI_S32
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_PutFrame( VPU_CHAN_CTX_S *pChanCtx,HI_CODEC_FRAME_S * pstOut,DecOutputInfo stOutPutInfo, HI_S64 s64Pts)
{
	HI_U32  i = 0, u32Index = 0;
	HI_S32 s32Ret = HI_SUCCESS;
	HI_DRV_VDEC_USR_FRAME_S pstBuf ={0};

	pstOut->s64PtsMs = s64Pts;
	pstOut->s64SrcPtsMs = s64Pts;
	pstOut->unInfo.stVideo.u32Width 	  = stOutPutInfo.dispPicWidth;
	pstOut->unInfo.stVideo.u32Height	  = stOutPutInfo.dispPicHeight;
	pstOut->unInfo.stVideo.u32AspectWidth = stOutPutInfo.dispPicWidth;
	pstOut->unInfo.stVideo.u32AspectHeight= stOutPutInfo.dispPicHeight;
	pstOut->unInfo.stVideo.u32YAddr    = stOutPutInfo.dispFrame.bufY;
	pstOut->unInfo.stVideo.u32UAddr    = stOutPutInfo.dispFrame.bufCb;
	pstOut->unInfo.stVideo.u32VAddr    = stOutPutInfo.dispFrame.bufCr;
	pstOut->unInfo.stVideo.u32YStride  = stOutPutInfo.dispFrame.stride;
	pstOut->unInfo.stVideo.u32UStride  = stOutPutInfo.dispFrame.stride/2;
	pstOut->unInfo.stVideo.u32VStride  = stOutPutInfo.dispFrame.stride/2;

    /**CNcomment: 检查上报的帧存地址是否合法
    **/
	for (i = 0; i < VPU_MAX_FRAME_NUM; i++)
	{
    #ifdef ALLOC_MEM_FRAME_BY_FRAEM
		if (stOutPutInfo.dispFrame.bufY == pChanCtx->stLinearFrmBuf[i].stMmzBuf.phyaddr)
	#else
		if (stOutPutInfo.dispFrame.bufY == pChanCtx->stLinearFrmBuf[i].phyaddr)
	#endif
		{
            break;
		}
	}

    if (i >= VPU_MAX_FRAME_NUM)
    {
        HI_ERR_VDEC("FUN:%s,L:%d bufY=%x is not valide!\n", __FUNCTION__, __LINE__, stOutPutInfo.dispFrame.bufY);
        return HI_FAILURE;
    }

#ifdef SAVE_YUV
    VDEC_VPU_DbgSave2DYuv(pChanCtx, &stOutPutInfo, i);
    VPU_DecClrDispFlag(pChanCtx->pHandle, stOutPutInfo.indexFrameDisplay);
    return;
#endif

	pstBuf.bFrameValid      = HI_TRUE;
	HI_VDEC_ConvertFormat(pstOut->unInfo.stVideo.enColorFormat, &(pstBuf.enFormat));
	pstBuf.u32Pts           = (HI_U32)(pstOut->s64PtsMs);
	pstBuf.s32YWidth        = (HI_S32)(pstOut->unInfo.stVideo.u32Width);
	pstBuf.s32YHeight       = (HI_S32)(pstOut->unInfo.stVideo.u32Height);
	pstBuf.s32LumaPhyAddr   = (HI_S32)(pstOut->unInfo.stVideo.u32YAddr);
	pstBuf.s32CbPhyAddr     = (HI_S32)(pstOut->unInfo.stVideo.u32UAddr);
	pstBuf.s32CrPhyAddr     = (HI_S32)(pstOut->unInfo.stVideo.u32VAddr);
	pstBuf.s32LumaStride    = (HI_S32)(pstOut->unInfo.stVideo.u32YStride);
	pstBuf.s32ChromStride   = (HI_S32)(pstOut->unInfo.stVideo.u32YStride);
	pstBuf.s32ChromCrStride = (HI_S32)(pstOut->unInfo.stVideo.u32YStride);
	pstBuf.bEndOfStream     = HI_FALSE;
	pstBuf.s32FrameID       = stOutPutInfo.indexFrameDisplay ;
	s32Ret = HI_VDEC_PutFrame(pChanCtx->u32hVdec, &pstBuf);
	VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);

    u32Index = stOutPutInfo.indexFrameDisplay;
    if (HI_FALSE == pChanCtx->stDispFrmBuf[u32Index].bPutToVpss)
    {
        pChanCtx->stDispFrmBuf[u32Index].bPutToVpss = HI_TRUE ;
        pChanCtx->stDispFrmBuf[u32Index].u32Index   = u32Index;
    }
    else
    {
        HI_ERR_VDEC("FUN:%s,L:%d bufY=%x u32Index=%d is set to VPSS again!\n", __FUNCTION__, __LINE__, 
                     stOutPutInfo.dispFrame.bufY, u32Index);
    }

#ifdef FRM_BUF_STATE
    {
        printf("Put %d \n",u32Index);
        printf("Satus: ");
        for (i = 0; i < pChanCtx->u32ActualFrameNum; i++)
        {
            printf("%d ",pChanCtx->stDispFrmBuf[i].bPutToVpss);
        }
        printf("\n");
    }
#endif
 
	return HI_SUCCESS;
}


/*****************************************************************************
brief     : VpuFreePreviousFramebuffer: 释放之前的帧BUFFER信息
attention : 
param[in] : 
param[in] : 
param[in] : void
retval    : 
see       :
*****************************************************************************/
static void VpuFreePreviousFramebuffer(Uint32 coreIdx, VPU_DEC_FRM_BUF_INFO_S* fb)
{
    if (HI_NULL == fb)
    {
        return;
    }
    
    if (fb->vbFrame.size > 0) {
        vdi_free_dma_memory(coreIdx, &fb->vbFrame);
        osal_memset((void*)&fb->vbFrame, 0x00, sizeof(vpu_buffer_t));
    }
    if (fb->vbWTL.size > 0) {
        vdi_free_dma_memory(coreIdx, &fb->vbWTL);
        osal_memset((void*)&fb->vbWTL, 0x00, sizeof(vpu_buffer_t));
    }
    if (fb->vbFbcYTbl.size > 0) {
        vdi_free_dma_memory(coreIdx, &fb->vbFbcYTbl);
        osal_memset((void*)&fb->vbFbcYTbl, 0x00, sizeof(vpu_buffer_t));
    }
    if (fb->vbFbcCTbl.size > 0) {
        vdi_free_dma_memory(coreIdx, &fb->vbFbcCTbl);
        osal_memset((void*)&fb->vbFbcCTbl, 0x00, sizeof(vpu_buffer_t));
    }

    
    return;
}

/*****************************************************************************
brief     : UpdateDispFrameStatus: 更新显示帧存的状态
attention : 
param[in] : 
param[in] : 
param[in] : HI_VOID
retval    : 
see       :
*****************************************************************************/
HI_VOID UpdateDispFrameStatus( VPU_CHAN_CTX_S *pChanCtx, HI_S32 *FrmList, HI_S32 FrmRleaseNum)
{
	HI_S32 i = 0;
    HI_U32 u32Index = 0;

	for (i = 0; i < FrmRleaseNum; i++)
	{
        u32Index = FrmList[i];
        if ((u32Index == pChanCtx->stDispFrmBuf[u32Index].u32Index) && 
            (HI_TRUE == pChanCtx->stDispFrmBuf[u32Index].bPutToVpss))
        {
            pChanCtx->stDispFrmBuf[u32Index].bPutToVpss = HI_FALSE;
            pChanCtx->stDispFrmBuf[u32Index].u32Index   = 0;
        }
	}

#ifdef FRM_BUF_STATE
    {
        printf("Clear: ");
        for (i = 0; i < FrmRleaseNum; i++)
        {
            u32Index = FrmList[i];
            printf("%d ", u32Index);
        }
        printf("\n");

        printf("Satus: ",u32Index);
        for (i = 0; i < pChanCtx->u32ActualFrameNum; i++)
        {
            printf("%d ",pChanCtx->stDispFrmBuf[i].bPutToVpss);
        }
        printf("\n");
    }
#endif

	if (HI_TRUE == pChanCtx->stSeqChangeParm.bSeqChanged)
	{
		pChanCtx->stSeqChangeParm.bAllFrameRevertByVpss = HI_TRUE ;
		for (i = 0; i < VPU_MAX_FRAME_NUM; i++)
		{
		    if (HI_TRUE == pChanCtx->stDispFrmBuf[i].bPutToVpss)
			{	
				pChanCtx->stSeqChangeParm.bAllFrameRevertByVpss = HI_FALSE ;
				break;
			}				
		}
	}

    return;
}


/*****************************************************************************
brief     : Flush remaining framebuffers.
attention :
param[in] : HI_HANDLE
param[out]: DecGetFramebufInfo* return remaining framebuffers when squence changed.
retval    : HI_S32
see       :
*****************************************************************************/
static HI_S32 Re_registerFrameBuffer(VPU_CHAN_CTX_S *pChanCtx)
{
	HI_S32 s32Ret = 0, i = 0;

	pChanCtx->bRegFrameBuffer = HI_FALSE;  

#ifdef ALLOC_MEM_FRAME_BY_FRAEM
    /** CNcomment: 释放1D帧存
    **/
    for ( i = 0; i < pChanCtx->u32ActualFrameNum; i++)
	{
		HI_VPU_DestroyFrmBuffer( &(pChanCtx->stCompressFrmBuf[i]) );
	}


    /** CNcomment: 释放2D帧存
    **/
	for ( i = 0; i < pChanCtx->u32ActualFrameNum; i++)
	{
		HI_VPU_DestroyFrmBuffer( &(pChanCtx->stLinearFrmBuf[i]) );
	}
#else

    /**CNcomment: 释放压缩帧存
    **/
	pBuf = &(g_VPUChanCtx[pChanCtx->pHandle->coreIdx].stCompressFrmBuf[0]);
	if( HI_NULL != pBuf )
	{
		s32Ret = VDEC_VPU_RevertFrameBuf(pBuf->phyaddr);
		VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);
	}

    /**CNcomment: 释放线性帧存
    **/
	pBuf = &(g_VPUChanCtx[pChanCtx->pHandle->coreIdx].stLinearFrmBuf[0]);
	if( HI_NULL != pBuf )
	{
		s32Ret = VDEC_VPU_RevertFrameBuf(pBuf->phyaddr);
		VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);
	}
#endif	

	s32Ret = RegFrameBufferWithoutWaitInterrupt(pChanCtx);
	VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);

	VpuFreePreviousFramebuffer(pChanCtx->pHandle->coreIdx, &(pChanCtx->stSeqChangeParm.PrevFb));
	memset(&(pChanCtx->stSeqChangeParm), 0, sizeof(VPU_SEQ_CHANGE_PARM_S));
	memset(&(pChanCtx->stDecFrmBuf), 0, sizeof(VPU_DEC_FRAME_BUF_S)* VPU_MAX_FRAME_NUM);

	return s32Ret;
}




/*****************************************************************************
brief     : Flush remaining framebuffers.
attention :
param[in] : HI_HANDLE
param[out]: DecGetFramebufInfo* return remaining framebuffers when squence changed.
retval    : HI_S32
see       :
*****************************************************************************/
static HI_S32 HI_VPU_FlushRemainingFrames(VPU_CHAN_CTX_S *pChanCtx, HI_CODEC_FRAME_S * pstOut, HI_U32 *frameCount)
{
	HI_S32     s32Ret = 0;
	HI_S64     s64PtsMs = 0;
	
	DecOutputInfo  *pDecOutInfo = HI_NULL; 

    /**CNcomment: 变分辨时，有未输出的帧
    **/
	if (0 < pChanCtx->stSeqChangeParm.retNum)
	{
		if (  HI_FALSE == pChanCtx->stSeqChangeParm.bAllFramePutToVpss)
		{
			pDecOutInfo = &(pChanCtx->stSeqChangeParm.pDecOutInfo[pChanCtx->stSeqChangeParm.u32FlushedNum]);
			pChanCtx->stSeqChangeParm.u32FlushedNum++;

		#ifdef OUTPUT_DecInfo
		    VDEC_VPU_DisplayDecodedInformation( pChanCtx->pHandle, *frameCount, pDecOutInfo);
		#endif

            /**CNcomment: 解码一帧成功，从pts管理队列中找到对应的码流包的pts
            **/
			if (pDecOutInfo->indexFrameDecoded >= 0)
			{
				s32Ret = VDEC_VPU_GetPTS( pChanCtx, pDecOutInfo->rdPtr, &s64PtsMs);
				VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);	
		
				s32Ret = VDEC_VPU_SetPtsForDecFrmBuf(pChanCtx,pDecOutInfo->indexFrameDecoded,s64PtsMs);
				VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);
			}

			if (pDecOutInfo->indexFrameDisplay >= 0)
		    {
    	        memcpy(&(pChanCtx->stLastDispOutInfo), pDecOutInfo, sizeof(DecOutputInfo));
				s32Ret = VDEC_VPU_GetPtsForDispFrmBuf (pChanCtx, *pDecOutInfo, &s64PtsMs );
				VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);

				s32Ret = HI_VPU_PutFrame(pChanCtx, pstOut, *pDecOutInfo, s64PtsMs);
				VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);
		       
		        (*frameCount)++;
		    }

			if ( pChanCtx->stSeqChangeParm.retNum == pChanCtx->stSeqChangeParm.u32FlushedNum)
			{
				pChanCtx->stSeqChangeParm.bAllFramePutToVpss = HI_TRUE ;
				return HI_SUCCESS;
			}
		}		
	}

    /**CNcomment: 注意；有可能变分辨发生时，之前的帧都已经输出
    **/
	if ( HI_TRUE == pChanCtx->stSeqChangeParm.bAllFrameRevertByVpss)
	{
		s32Ret = Re_registerFrameBuffer(pChanCtx);
		VPU_ASSERT_EQ(HI_SUCCESS, s32Ret);
	}

	return s32Ret;

}

/*****************************************************************************
brief     : prepare for sequence changed.
attention :
param[in] : HI_HANDLE
param[out]: DecGetFramebufInfo* return remaining framebuffers when squence changed.
retval    : HI_BOOL
see       :
*****************************************************************************/
static HI_BOOL HI_VPU_PrepareChangingSequence(VPU_CHAN_CTX_S *pChanCtx, DecOutputInfo* outInfo)
{
	HI_BOOL    changed = HI_FALSE;
	HI_BOOL    profileChanged = HI_FALSE, resolutionChanged= HI_FALSE, numDpbChanged = HI_FALSE;
    HI_CHAR*   profileName[4] = {"None", "Main", "Main10", "StillPicture" };
    HI_U32     i = 0 ;
	DecHandle  handle = pChanCtx->pHandle;
	DecInitialInfo* pDecSeqInfo = &handle->CodecInfo.decInfo.initialInfo;
	
	DecGetFramebufInfo *prevFbInfo = (DecGetFramebufInfo*)(&(pChanCtx->stSeqChangeParm.PrevFb));
	DecOutputInfo*  pDecOutInfo = &(pChanCtx->stSeqChangeParm.pDecOutInfo[0]);

    profileChanged    = (outInfo->sequenceChanged>>5)&0x01 ? HI_TRUE : HI_FALSE;
    resolutionChanged = (outInfo->sequenceChanged>>16)&0x01 ? HI_TRUE : HI_FALSE;
    numDpbChanged     = (outInfo->sequenceChanged>>19)&0x01 ? HI_TRUE : HI_FALSE;

	pChanCtx->bResolutionChanged = resolutionChanged ;

//	HI_ERR_VDEC("profileChanged=%d || resolutionChanged=%d || numDpbChanged=%d \n",profileChanged,resolutionChanged,numDpbChanged); 

    if (HI_TRUE == profileChanged) 
	{
        if (pDecSeqInfo->profile != HEVC_PROFILE_MAIN) 
            HI_WARN_VDEC("Not supported profile: %s\n", profileName[pDecSeqInfo->profile]);
    }
	
    if (resolutionChanged || numDpbChanged) 
	{
        VPU_DecGiveCommand(handle, DEC_GET_FRAMEBUF_INFO, prevFbInfo);
        VPU_DecFrameBufferFlush(handle, pDecOutInfo, &(pChanCtx->stSeqChangeParm.retNum));

        /* Changed resolution or number of DPB */     
        VPU_DecGiveCommand(handle, DEC_RESET_FRAMEBUF_INFO, NULL);
        VPU_DecGiveCommand(handle, DEC_FREE_FRAME_BUFFER, NULL);
        changed = HI_TRUE;
    }

	if (0 < pChanCtx->stSeqChangeParm.retNum)
	{
		for (i = 0; i < pChanCtx->stSeqChangeParm.retNum; i++)
		{
		    VDEC_VPU_DisplayDecodedInformation(handle, i, &(pDecOutInfo[i]));
		}
	}

    return changed;
}

/*****************************************************************************
brief     : use vpu Codec decode frame. CNcomment:使用VPU解码器解码 CNend
attention : H265 only
param[in] : HI_HANDLE
param[in] : HI_CODEC_STREAM_S * 
param[out]: HI_CODEC_FRAME_S *
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_DecodeFrame(HI_HANDLE hInst, HI_CODEC_STREAM_S * pstIn, HI_CODEC_FRAME_S * pstOut)
{
	HI_U32 u32StrBufInsufficientFlag           = 0;
		
    HI_S32 i = 0, s32Ret = 0;
    HI_S32 s32IntReason                        = 0;
	HI_S32 FrmList[HI_VDEC_MAX_VPU_FRAME_NUM]  = {0};
	HI_S32 FrmRleaseNum 					   = 0;
	HI_S32 timeout_count 					   = 0 ;
	HI_S64 s64PtsMs 						   = 0 ;
    DecParam *pstParam 						   = HI_NULL;
    DecOutputInfo stOutPutInfo				   = {0};
    DecHandle phandle 						   = HI_NULL;
    VPU_CHAN_CTX_S *pChanCtx 				   = HI_NULL;

    HI_S32 temp = 30;
    HI_U32 ReadPtr, WritePtr, Size;
    HI_S32 val =0;
	
    VPU_CHAN_CHECK(hInst);
    pChanCtx = &g_VPUChanCtx[hInst];
    phandle = pChanCtx->pHandle;

    /**CNcomment: 填充码流 VDEC ----> VPU, 如果VPU 码流BUF处于满的状态时，需要将
        标志u32StrBufInsufficientFlag置为 1
    **/
    s32Ret = VDEC_VPU_FillRawPacket(pChanCtx, pstIn); 
	if (VPU_STR_BUF_INSUFFICIENT == s32Ret)
	{
		u32StrBufInsufficientFlag = 1;
	}

    /**CNcomment: 检查解码通过是否为运行状态
    **/
    if ((VPU_STATE_RUN != pChanCtx->eChanState) || (HI_FALSE == pChanCtx->bRegFrameBuffer) ||
        (HI_TRUE == pChanCtx->bIsNotSupport))
    {
        VPU_RET_CHECK(HI_FAILURE, s32Ret, u32StrBufInsufficientFlag);
        return s32Ret;
    }

    /**CNcomment: 检测是否有可释放的帧存 VPSS ---> VDEC ----> VPU
    **/
    s32Ret = VDEC_VPU_CheckRlsFrameID(pChanCtx->u32hVdec,FrmList, &FrmRleaseNum);
    if (HI_SUCCESS == s32Ret)
    {
        for (i = 0 ; i < FrmRleaseNum; i++)
        {
            VPU_DecClrDispFlag(phandle, FrmList[i]);
        }
    }

	UpdateDispFrameStatus(pChanCtx, FrmList, FrmRleaseNum);

    /**CNcomment: 暂时做规避用，因为VPU显示帧存反压后，会导致VPU混乱
    **/
#ifdef VPU_BUF_FULL_AVOID
    for (i = 0; i < pChanCtx->u32ActualFrameNum; i++)
    {
        if (HI_TRUE == pChanCtx->stDispFrmBuf[i].bPutToVpss)
        {
            FrameBufToVDECCount++;
        }
        if ((pChanCtx->u32ActualFrameNum > 2)&&(FrameBufToVDECCount >= (pChanCtx->u32ActualFrameNum-2)))
        {
            VPU_RET_CHECK(HI_FAILURE, s32Ret, u32StrBufInsufficientFlag);
            return s32Ret;
        }
    }
#endif

    /**CNcomment: 变分辨率的处理
    **/
#ifdef TEST_SEQUENCE_CHANGE_SUPPORT  //@f00241306 20140320
	if (HI_TRUE == pChanCtx->stSeqChangeParm.bSeqChanged)
	{
		s32Ret = HI_VPU_FlushRemainingFrames(pChanCtx, pstOut, &(pChanCtx->u32frameCount));
        VPU_RET_CHECK(s32Ret, s32Ret, u32StrBufInsufficientFlag);
		return s32Ret;
	}
#endif

    /**CNcomment: 参数配置
    **/
    pstParam = &(pChanCtx->stParam);
	
#ifdef TEST_SEQUENCE_CHANGE_SUPPORT  //@f00241306 20140317
	val = SEQ_CHANGE_ENABLE_ALL;
   	VPU_DecGiveCommand(phandle, DEC_SET_SEQ_CHANGE_MASK, (void*)&val);    
#endif	
		
    /**CNcomment: 启动解码
    **/
    if (HI_FALSE == pChanCtx->bStartDecPicFlag)
    {
	#ifdef VPU_ResetTime_Statistics_SUPPORT
		s32Ret = HI_SYS_GetTimeStampMs(&g_time[2]);
	#endif
      
        /**CNcomment: 上报空中断需每次解码前先调用下这个函数
        **/
        VPU_DecGiveCommand(phandle, DEC_SET_REPEAT_EMPTY_INTERRUPT, &temp);      
        s32Ret = VPU_DecStartOneFrame(phandle, pstParam);
		if (RETCODE_SUCCESS != s32Ret)
		{
            VPU_RET_CHECK(HI_FAILURE, s32Ret, u32StrBufInsufficientFlag);
			return s32Ret;
		}
    }

    /**CNcomment: 等待解码完成
    **/
    do
    {
        s32IntReason = VPU_WaitInterrupt(phandle->coreIdx, VDEC_VPU_DEC_TIMEOUT);
        if (s32IntReason == -1) // timeout
        {
            if (timeout_count * VPU_WAIT_TIME_OUT > VDEC_VPU_DEC_TIMEOUT)
            {
	            VPU_DecGetBitstreamBuffer(phandle, &ReadPtr, &WritePtr, &Size);
	            HI_ERR_VDEC("Time out: RD_PTR:0x%08x, WR_PTR:0x%08x\n", ReadPtr, WritePtr);
                VPU_SWReset(phandle->coreIdx, SW_RESET_SAFETY, phandle);
                VPU_DecUpdateBitstreamBuffer(phandle, 1024);
                break;
            }
        #ifdef VPU_EVENTS_TEST
            pChanCtx->stVpuEvents.bDecErr               = HI_TRUE ; 
            pChanCtx->stVpuEvents.VpuDecFailReason      = VPU_ERR_INTERRPUTION ; 
        #endif 
		
            timeout_count++;
            s32IntReason = 0;
        }

		if (s32IntReason > 0)
        {
            VPU_ClearInterrupt(phandle->coreIdx);
            if (s32IntReason & (1<<INT_WAVE_DEC_PIC))
            {
                pChanCtx->bStartDecPicFlag = HI_FALSE;
				pChanCtx->stGetLastFrame.bLastEmptyInterruption     = HI_FALSE;
				pChanCtx->stGetLastFrame.u32EmptyInterruptionCounts = 0;
                break;
            }
            else if (s32IntReason & (1<<INT_WAVE_BIT_BUF_EMPTY))
            {
                if ( HI_TRUE == pChanCtx->stGetLastFrame.bLastEmptyInterruption )
            	{
					pChanCtx->stGetLastFrame.u32EmptyInterruptionCounts++;
            	}
				pChanCtx->stGetLastFrame.bLastEmptyInterruption = HI_TRUE;

	    		if ( 2 == pChanCtx->u32EosFlag && pChanCtx->stGetLastFrame.u32EmptyInterruptionCounts > VPU_EMPTY_COUNT)
				{
					VPU_DecUpdateBitstreamBuffer(phandle, STREAM_END_SIZE);
					pChanCtx->u32EosFlag = 0 ;
				}
                pChanCtx->bStartDecPicFlag = HI_TRUE;
                VPU_RET_CHECK(HI_FAILURE, s32Ret, u32StrBufInsufficientFlag);
				return s32Ret;
            }
            else
            {
            }
        }
    } while (1);

    /**CNcomment: 读取解码帧信息
    **/
    s32Ret = VPU_DecGetOutputInfo(phandle, &stOutPutInfo);
    VPU_DECODE_ASSERT(RETCODE_SUCCESS, s32Ret, u32StrBufInsufficientFlag);

#ifdef TEST_SEQUENCE_CHANGE_SUPPORT  //@f00241306 20140317
	if (stOutPutInfo.sequenceChanged)  
	{	
		pChanCtx->stSeqChangeParm.bSeqChanged = HI_VPU_PrepareChangingSequence(pChanCtx, &stOutPutInfo);
        pChanCtx->u32SeqChangeCount++;
		if (HI_TRUE == pChanCtx->stSeqChangeParm.bSeqChanged)
		{
    	#ifdef VPU_EVENTS_TEST
			pChanCtx->stVpuEvents.bResolutionChanged 	= pChanCtx->bResolutionChanged ; 
		    if ( HI_TRUE == pChanCtx->stVpuEvents.bResolutionChanged)
	    	{
				pChanCtx->stVpuEvents.u32Height 			= stOutPutInfo.decPicHeight ;
				pChanCtx->stVpuEvents.u32Width  			= stOutPutInfo.decPicWidth ;
	    	}
		#endif 
            VPU_RET_CHECK(HI_FAILURE, s32Ret, u32StrBufInsufficientFlag);
			return s32Ret;
		}
	}
#endif


#ifdef VPU_ResetTime_Statistics_SUPPORT
	if (stOutPutInfo.indexFrameDecoded >= 0)
	{
		s32Ret = HI_SYS_GetTimeStampMs(&g_time[3]);
//		HI_ERR_VDEC("HI_VPU_DecodeFrame: Decoded finished time =%d\n",g_time[3]);
	}
#endif

#ifdef OUTPUT_DecInfo
    VDEC_VPU_DisplayDecodedInformation( phandle, pChanCtx->u32frameCount, &stOutPutInfo);
#endif

    /**CNcomment: 解码一帧成功，从pts管理队列中找到对应的码流包的pts
    **/
	if (stOutPutInfo.indexFrameDecoded >= 0)
	{
        pChanCtx->stParam.skipframeMode = pChanCtx->eSkipMode;
		s32Ret = VDEC_VPU_GetPTS(pChanCtx, stOutPutInfo.rdPtr, &s64PtsMs);
        if (HI_SUCCESS != s32Ret)
        {
			HI_WARN_VDEC("FUN:%s, L:%d Get Pts for indexFrameDecoded(%d) failed!\n", __FUNCTION__, __LINE__, stOutPutInfo.indexFrameDecoded);
        }
	
		s32Ret = VDEC_VPU_SetPtsForDecFrmBuf(pChanCtx,stOutPutInfo.indexFrameDecoded,s64PtsMs);
        if (HI_SUCCESS != s32Ret)
        {
			HI_WARN_VDEC("FUN:%s, L:%d Set Pts for indexFrameDecoded(%d) failed!\n", __FUNCTION__, __LINE__, stOutPutInfo.indexFrameDecoded);
        }
	}

    // add by w00278582
    HI_VPU_PROC_STATUS(pChanCtx, &stOutPutInfo);

    if (stOutPutInfo.indexFrameDisplay == -1)
    {
        VPU_RET_CHECK(HI_FAILURE, s32Ret, u32StrBufInsufficientFlag);
    }
    else if (stOutPutInfo.indexFrameDisplay >= 0)
    {
#ifdef VPU_EVENTS_TEST
		pChanCtx->stVpuEvents.u32ErrRatio	= 0;//stOutPutInfo.numOfErrMBs ; //这里返回的个数如何转换成比率呢
#endif 
        memcpy(&(pChanCtx->stLastDispOutInfo), &stOutPutInfo, sizeof(DecOutputInfo));
#ifdef VPU_ResetTime_Statistics_SUPPORT
		s32Ret = HI_SYS_GetTimeStampMs(&g_time[4]);
//		HI_ERR_VDEC("HI_VPU_DecodeFrame: Display finished time =%d\n",g_time[4]);
#endif

		s32Ret = VDEC_VPU_GetPtsForDispFrmBuf (pChanCtx, stOutPutInfo, &s64PtsMs );
        if (HI_SUCCESS != s32Ret)
        {
			HI_WARN_VDEC("FUN:%s, L:%d Get Pts for indexFrameDisplay(%d) failed!\n", __FUNCTION__, __LINE__, stOutPutInfo.indexFrameDisplay);
            s64PtsMs = -1;
        }

		s32Ret = HI_VPU_PutFrame(pChanCtx, pstOut, stOutPutInfo, s64PtsMs);
        if (HI_SUCCESS != s32Ret)
        {
			HI_WARN_VDEC("FUN:%s, L:%d Get Pts for indexFrameDisplay(%d) failed!\n", __FUNCTION__, __LINE__, stOutPutInfo.indexFrameDisplay);
        }

        (pChanCtx->u32frameCount)++;

        VPU_RET_CHECK(HI_SUCCESS, s32Ret, u32StrBufInsufficientFlag);
    }
    else
    {
        VPU_RET_CHECK(HI_FAILURE, s32Ret, u32StrBufInsufficientFlag);
    }


    return s32Ret;
}



/*****************************************************************************
brief     : get stream information . CNcomment:获取码流信息 CNend
attention : H265 only
param[in] : HI_HANDLE
param[out]: HI_CODEC_STREAMINFO_S *
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_GetStreamInfo(HI_HANDLE hInst, HI_CODEC_STREAMINFO_S * pstAttr)
{
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;
			
    VPU_CHAN_CHECK(hInst);
    if (HI_NULL == pstAttr)
    {
        HI_ERR_VDEC("FUN:%s, L:%d pstAttr is null!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
    pChanCtx = &g_VPUChanCtx[hInst];

    /**CNcomment: 各信息还待完善和一一确认
    **/
    pstAttr->stVideo.enCodecID         = HI_CODEC_ID_VIDEO_HEVC;
    pstAttr->stVideo.enSubStandard     = HI_CODEC_VIDEO_SUB_STANDARD_UNKNOWN;
    pstAttr->stVideo.u32SubVersion     = 0;
    pstAttr->stVideo.u32Profile        = 0;
    pstAttr->stVideo.u32Level          = 0;
    pstAttr->stVideo.enDisplayNorm     = HI_CODEC_ENC_FMT_BUTT;
    pstAttr->stVideo.bProgressive      = HI_TRUE;
    pstAttr->stVideo.u32AspectWidth    = 0;
    pstAttr->stVideo.u32AspectHeight   = 2;
    pstAttr->stVideo.u32bps            = 0;
    pstAttr->stVideo.u32FrameRateInt   = 0;
    pstAttr->stVideo.u32FrameRateDec   = 0;    
    pstAttr->stVideo.u32Width          = pChanCtx->stLastDispOutInfo.decPicWidth;
    pstAttr->stVideo.u32Height         = pChanCtx->stLastDispOutInfo.decPicHeight;
    pstAttr->stVideo.u32DisplayWidth   = pChanCtx->stLastDispOutInfo.dispPicWidth;
    pstAttr->stVideo.u32DisplayHeight  = pChanCtx->stLastDispOutInfo.dispPicHeight;
    pstAttr->stVideo.u32DisplayCenterX = pChanCtx->stLastDispOutInfo.dispPicWidth / 2;
    pstAttr->stVideo.u32DisplayCenterY = pChanCtx->stLastDispOutInfo.dispPicHeight / 2;
    
    return HI_SUCCESS;
}

/*****************************************************************************
brief     : close vpu dev . CNcomment:关闭VPU设备 CNend
attention : H265 only
retval    : 
see       :
*****************************************************************************/
HI_S32 VDEC_CloseVPU()
{
    HI_S32 s32Ret;
    HI_U32 u32CoreIndexID = 0;

	s32Ret = VPU_IsInit(u32CoreIndexID);
    if(s32Ret)
    {
        s32Ret = VPU_DeInit(u32CoreIndexID);
		if(RETCODE_SUCCESS != s32Ret)
		{
            HI_ERR_VDEC("FUN:%s,L:%d Call function of VPU_DecInit failed!\n", __FUNCTION__, __LINE__);
		    return HI_FAILURE;
		}
    }
	
	return HI_SUCCESS;
}

/*****************************************************************************
brief     : VPU_SetStreamEndFlag . CNcomment :从vdec获取码流结束标志
attention : H265 only
retval    : 
see       :
*****************************************************************************/
static HI_S32 VPU_SetStreamEndFlag( HI_HANDLE hVpuInst, HI_U32  *u32EosFlag)
{
    HI_S32 s32Ret = HI_SUCCESS;
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;

    VPU_CHAN_CHECK(hVpuInst);
    pChanCtx = &g_VPUChanCtx[hVpuInst];

	pChanCtx->u32EosFlag = *u32EosFlag ;

    return s32Ret;
}


/*****************************************************************************
brief     : VPU_CheckEvt . CNcomment:获取VPU上报的事件
attention : H265 only
retval    : 
see       :
*****************************************************************************/
static HI_S32 VPU_CheckEvt(HI_HANDLE hVpuInst, VDEC_EVENT_S *pstNewEvent)
{
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;
			
    VPU_CHAN_CHECK(hVpuInst);
    pChanCtx = &g_VPUChanCtx[hVpuInst];

    if (HI_NULL == pstNewEvent|| HI_NULL == pChanCtx)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pstNewEvent is null!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
#ifdef VPU_EVENTS_TEST
    pstNewEvent->bNormChange							= pChanCtx->stVpuEvents.bResolutionChanged ;
	if (HI_TRUE == pstNewEvent->bNormChange)
	{
		pstNewEvent->stNormChangeParam.u32ImageHeight 	= pChanCtx->stVpuEvents.u32Height ;
		pstNewEvent->stNormChangeParam.u32ImageWidth  	= pChanCtx->stVpuEvents.u32Width;
	}
	pstNewEvent->bDecErr 								= pChanCtx->stVpuEvents.bDecErr;
	pstNewEvent->u32ErrRatio 							= pChanCtx->stVpuEvents.u32ErrRatio ;
#endif
		
	return HI_SUCCESS;
}


/*****************************************************************************
brief     : VPU_GetChanStatusInfo . CNcomment:获取通道上状态
attention : H265 only
retval    : 
see       :
*****************************************************************************/
static HI_S32 VPU_GetChanStatusInfo(HI_HANDLE hVdec, HI_HANDLE hVpuInst, HI_DRV_VDEC_FRAMEBUF_STATUS_S *pstStatusInfo)
{
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;
	HI_BOOL         bAllPortCompleteFrm = 0;
			
    VPU_CHAN_CHECK(hVpuInst);
    pChanCtx = &g_VPUChanCtx[hVpuInst];

    if (HI_SUCCESS != VPU_GetVpssStatusInfo(hVdec, &bAllPortCompleteFrm))
    {
        HI_ERR_VDEC("FUN:%s,L:%d Call funtion of VPU_GetVpssStatusInfo failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    pstStatusInfo->bAllPortCompleteFrm  = bAllPortCompleteFrm ;
	pstStatusInfo->u32TotalDecFrameNum  = pChanCtx->u32frameCount;
    pstStatusInfo->u32FrameBufNum       = pChanCtx->u32ActualFrameNum;
		
	return HI_SUCCESS;
}


/*****************************************************************************
brief     : VPU_ReadNewFrame . CNcomment:获取新帧信息
attention : H265 only
retval    : 
see       :
*****************************************************************************/
static HI_S32 VPU_ReadNewFrame( HI_HANDLE hVdec, HI_HANDLE hVpuInst, HI_DRV_VIDEO_FRAME_S *pstNewFrame)
{
    HI_S32 s32Ret = HI_SUCCESS;
	HI_U32 u32FrameRate = 0 ;
    DecOutputInfo *pstOutPutInfo	= HI_NULL;
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;
	DecInitialInfo stSeqInfo;
	HI_DRV_VIDEO_PRIVATE_S* pstVideoPriv = NULL;

    VPU_CHAN_CHECK(hVpuInst);
    pChanCtx = &g_VPUChanCtx[hVpuInst];
	pstOutPutInfo = &(pChanCtx->stLastDispOutInfo);
	memset(&stSeqInfo, 0, sizeof(DecInitialInfo));
    if (NULL == pChanCtx->pHandle)
    {
        HI_ERR_VDEC("FUN:%s,L:%d pChanCtx->pHandle is null!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
	stSeqInfo = pChanCtx->pHandle->CodecInfo.decInfo.initialInfo;
    pstVideoPriv = (HI_DRV_VIDEO_PRIVATE_S*)(pstNewFrame->u32Priv);
	
	pstNewFrame->u32FrameIndex                        = pChanCtx->u32frameCount;	
	pstNewFrame->stBufAddr[0].u32PhyAddr_YHead        = pstOutPutInfo->dispFrame.bufY;
	pstNewFrame->stBufAddr[0].u32PhyAddr_Y            = pstOutPutInfo->dispFrame.bufY;
	pstNewFrame->stBufAddr[0].u32Stride_Y             = pstOutPutInfo->dispFrame.stride;
	pstNewFrame->stBufAddr[0].u32PhyAddr_CHead        = pstOutPutInfo->dispFrame.bufCb;
	pstNewFrame->stBufAddr[0].u32PhyAddr_C            = pstOutPutInfo->dispFrame.bufCb;
	pstNewFrame->stBufAddr[0].u32Stride_C             = pstOutPutInfo->dispFrame.stride/2;
	pstNewFrame->stBufAddr[0].u32PhyAddr_CrHead       = pstOutPutInfo->dispFrame.bufCr;
	pstNewFrame->stBufAddr[0].u32PhyAddr_Cr           = pstOutPutInfo->dispFrame.bufCr;
	pstNewFrame->stBufAddr[0].u32Stride_Cr            = pstOutPutInfo->dispFrame.stride/2;
	
    pstNewFrame->u32Width                             = pstOutPutInfo->dispPicWidth;
	pstNewFrame->u32Height                            = pstOutPutInfo->dispPicHeight;
	pstNewFrame->u32SrcPts                            = pChanCtx->s64NewDispFramePts;
	pstNewFrame->u32Pts                               = pChanCtx->s64NewDispFramePts;

	pstNewFrame->u32AspectHeight                      = pstOutPutInfo->dispPicHeight ;
	pstNewFrame->u32AspectWidth                       = pstOutPutInfo->dispPicWidth ;

	if (stSeqInfo.isExtSAR == TRUE) 
	{
		pstNewFrame->u32AspectWidth  = (stSeqInfo.aspectRateInfo&0xffff0000) >> 16;
		pstNewFrame->u32AspectHeight = (stSeqInfo.aspectRateInfo&0xffff);
	} 
	
	s32Ret = VDEC_VPU_GetFrameRateForNewFrm(hVdec, &u32FrameRate);
	pstNewFrame->u32FrameRate                         = u32FrameRate ;
	
	pstNewFrame->ePixFormat                           = HI_DRV_PIX_FMT_NV21 ;
	pstNewFrame->enFieldMode 						  = HI_DRV_FIELD_ALL;
	pstNewFrame->bCompressd                           = HI_FALSE ;
	pstNewFrame->bProgressive                         = HI_FALSE ;
	pstNewFrame->enBitWidth                           = HI_DRV_PIXEL_BITWIDTH_8BIT;

    pstVideoPriv->eColorSpace                  	   	  = HI_DRV_CS_BT601_YUV_LIMITED;
	pstVideoPriv->stVideoOriginalInfo.enSource 	   	  = HI_DRV_SOURCE_DTV;
	pstVideoPriv->stVideoOriginalInfo.u32Width 	   	  = pstNewFrame->u32Width  ;
	pstVideoPriv->stVideoOriginalInfo.u32Height    	  = pstNewFrame->u32Height;
    pstVideoPriv->stVideoOriginalInfo.u32FrmRate   	  = 25;
	pstVideoPriv->stVideoOriginalInfo.en3dType     	  = HI_DRV_FT_NOT_STEREO;
	pstVideoPriv->stVideoOriginalInfo.enSrcColorSpace = HI_DRV_CS_BT601_YUV_LIMITED;
	pstVideoPriv->stVideoOriginalInfo.enColorSys 	  = HI_DRV_COLOR_SYS_AUTO;
	pstVideoPriv->stVideoOriginalInfo.bGraphicMode 	  = HI_FALSE;
	pstVideoPriv->stVideoOriginalInfo.bInterlace	  = 0;

	return s32Ret;
}

/*****************************************************************************
brief     : VPU_SetFrameRate . CNcomment:设置帧率
attention : H265 only
retval    : 
see       :
*****************************************************************************/
static HI_S32 VPU_SetFrameRate(HI_HANDLE hVdec, HI_UNF_AVPLAY_FRMRATE_PARAM_S *pstFrmRate)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = VPU_SetFrmRate(hVdec, pstFrmRate);
    
    return s32Ret;
}

/*****************************************************************************
brief     : VPU_GetFrameRate . CNcomment:获取帧率
attention : H265 only
retval    : 
see       :
*****************************************************************************/
static HI_S32 VPU_GetFrameRate(HI_HANDLE hVdec, HI_UNF_AVPLAY_FRMRATE_PARAM_S *pstFrmRate)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = VPU_GetFrmRate(hVdec, pstFrmRate);

    return s32Ret;
}

/*****************************************************************************
brief     : VPU_FillStream . CNcomment:填充码流到VPU的码流buff
attention : H265 only
retval    : 
see       :
*****************************************************************************/
static HI_S32 VPU_FillStream(HI_HANDLE hVpuInst, HI_CODEC_STREAM_S* pstCodecStrm)
{
    HI_S32 s32Ret = HI_SUCCESS;
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;
    VPU_CHAN_CHECK(hVpuInst);

    pChanCtx = &g_VPUChanCtx[hVpuInst];

    s32Ret = VDEC_VPU_FillRawPacket(pChanCtx,pstCodecStrm);

    if ( pstCodecStrm->s64PtsMs != 0xffffffff)
    {
        pChanCtx->bWaitEsTimeOut = ((pstCodecStrm->s64PtsMs - pChanCtx->s64FirstValidRawPts) > pChanCtx->u32WaitEsTime) ? HI_TRUE : HI_FALSE;
    }
    return s32Ret;
}

/*****************************************************************************
brief     : VPU_FillStream . CNcomment:填充码流到VPU的码流buff
attention : H265 only
retval    : 
see       :
*****************************************************************************/
static HI_S32 VPU_SetStreamMode(HI_HANDLE hVpuInst, HI_U32 u32DemuxFlag)
{
    HI_S32 s32Ret = HI_SUCCESS;
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;
    VPU_CHAN_CHECK(hVpuInst);

    pChanCtx = &g_VPUChanCtx[hVpuInst];

    pChanCtx->u32IsFromDemux = u32DemuxFlag;

    return HI_SUCCESS;
}


/*****************************************************************************
brief     : VPU_GetStreamBuf_Status . CNcomment:获取码流buff状态
attention : H265 only
retval    : 
see       :
*****************************************************************************/
static HI_VOID VPU_GetStreamBuf_Status(HI_HANDLE hVpuInst, VPU_STREAM_BUF_STATUS_S* pstStreamBufStatus)
{
    HI_U32 u32BsPercentage = 0;
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;
    VPU_CHAN_CHECK(hVpuInst);

    pChanCtx = &g_VPUChanCtx[hVpuInst];

    u32BsPercentage = 9;
    pstStreamBufStatus->bStreamBufSuccfient = ((pChanCtx->u64RecvPackSize > ((HI_U32)VPU_STREAM_BUF_SIZE*u32BsPercentage/10)) ? 1 : 0 ) || pChanCtx->bWaitEsTimeOut;
}

/*****************************************************************************
brief     : VPU_Set_WaitEsTime . CNcomment: 提供用户设置攥码流时间(ms)
attention : H265 only
retval    : 
see       :
*****************************************************************************/
static HI_VOID VPU_Set_WaitEsTime(HI_HANDLE hVpuInst, HI_U32 *u32WaitEsTime)
{
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;
    VPU_CHAN_CHECK(hVpuInst);

    pChanCtx 				= &g_VPUChanCtx[hVpuInst];
    pChanCtx->u32WaitEsTime = *u32WaitEsTime;
}

/*****************************************************************************
brief     : HI_VPU_Control . CNcomment: VPU Control 扩展接口
attention : H265 only
retval    : 
see       :
*****************************************************************************/
HI_S32 HI_VPU_Control(HI_HANDLE hVpuInst, HI_U32 u32CMD, HI_VOID * pParam)
{
    VPU_CHAN_CTX_S *pChanCtx = HI_NULL;
    HI_HANDLE hVdec;
			
    VPU_CHAN_CHECK(hVpuInst);
    pChanCtx = &g_VPUChanCtx[hVpuInst];
    hVdec    = pChanCtx->u32hVdec;

    if ((HI_INVALID_HANDLE == hVdec) || (NULL == pParam))
    {
	    HI_ERR_VDEC("FUN:%s L:%d hVdec(%d) and pParam(%p) is not valide value\n",__FUNCTION__,__LINE__,hVdec,pParam);
	    return HI_ERR_VDEC_INVALID_PARA;
    } 
    if((u32CMD!=VPU_CMD_SETFRAMERATE)&&(u32CMD!=VPU_CMD_GETFRAMERATE)) 
    {
        if(VPU_STATE_RUN != pChanCtx->eChanState)
        {
            HI_WARN_VDEC("FUN:%s,L:%d hVdec(%d) and pParam(%p) is not valide value or VPU not run!!\n",
                      __FUNCTION__, __LINE__, hVdec, pParam);
            return HI_FAILURE;
	}
    }

    switch (u32CMD)
    {
        case VPU_CMD_CHECKEVT:
            return VPU_CheckEvt(hVpuInst, (VDEC_EVENT_S *)pParam);
        case VPU_CMD_GETCHANSTATUSINFO:
            return VPU_GetChanStatusInfo(hVdec, hVpuInst, (HI_DRV_VDEC_FRAMEBUF_STATUS_S *)pParam);
        case VPU_CMD_READNEWFRAME:
            return VPU_ReadNewFrame(hVdec, hVpuInst, (HI_DRV_VIDEO_FRAME_S*)pParam);
        case VPU_CMD_SETFRAMERATE:
            return VPU_SetFrameRate(hVdec, (HI_UNF_AVPLAY_FRMRATE_PARAM_S*)pParam);
        case VPU_CMD_GETFRAMERATE:
            return VPU_GetFrameRate(hVdec, (HI_UNF_AVPLAY_FRMRATE_PARAM_S*)pParam);
        case VPU_CMD_SETSTREAMENDFLAG:
            return VPU_SetStreamEndFlag(hVpuInst, (HI_U32*)pParam);
        case VPU_CMD_FIllRAWPACKAGE:
            return VPU_FillStream(hVpuInst, (HI_CODEC_STREAM_S*)pParam);
        case VPU_CMD_SETBITSTREAMMODE:
            //return VPU_SetStreamMode(hVpuInst, *((HI_U32*)pParam));
            return HI_ERR_CODEC_UNSUPPORT;
        case VPU_CMD_GETSTREAMBUFSTATUS:
            VPU_GetStreamBuf_Status(hVpuInst, (VPU_STREAM_BUF_STATUS_S*)pParam);
            return HI_SUCCESS;
        case VPU_CMD_SETWAITESTIME:
            VPU_Set_WaitEsTime(hVpuInst, (HI_U32*)pParam);
        return HI_SUCCESS;
    default:
        HI_ERR_VDEC("FUN:%s,L:%d CMD %d is not support\n", __FUNCTION__, __LINE__, u32CMD);
        return HI_ERR_CODEC_UNSUPPORT;
    }

    return HI_ERR_CODEC_UNSUPPORT;
}


/*****************************************************************************
brief     : HI_VPU_PROC_STATUS
attention : H265 only
retval    : 
see       :
 *****************************************************************************/
HI_VOID HI_VPU_PROC_STATUS(VPU_CHAN_CTX_S *pChanCtx, DecOutputInfo *pstOutPutInfo)
{
    int i;
    HI_HANDLE hHandle;
    HI_U32 size;
    HI_DRV_VDEC_VPU_STATUS_S stVPUStatus;
    HI_U32 u32ReadPtr, u32WritePtr;

    if (HI_NULL == pChanCtx)
    {
        return;
    }

    memset(&stVPUStatus, 0, sizeof(HI_DRV_VDEC_VPU_STATUS_S));

    stVPUStatus.u32Version       = VPU_VERSION_NUM;
    stVPUStatus.u32VedioStandard = VPU_HEVC;

    hHandle                      = pChanCtx->u32hVdec;
    stVPUStatus.u32DecodeStatus  = pChanCtx->eChanState;
    
    stVPUStatus.u32DecodeMode    = pChanCtx->eDecMode;
    stVPUStatus.u32InstanceMode  = pChanCtx->eCapMode;
    stVPUStatus.u32PhyAddr       = pChanCtx->stOpenParam.bitstreamBuffer;
    stVPUStatus.u32BsBufSize     = pChanCtx->stOpenParam.bitstreamBufferSize;
    stVPUStatus.u32BsRate        = pChanCtx->u32BsRate;

    VPU_DecGetBitstreamBuffer(pChanCtx->pHandle, &u32ReadPtr, &u32WritePtr, &size);
    stVPUStatus.u32BsBufReadPtr  = u32ReadPtr;
    stVPUStatus.u32BsBufWritePtr = u32WritePtr;  

    if (stVPUStatus.u32BsBufSize > 0)
    {
        stVPUStatus.u32BsBuFUsedSize = (u32WritePtr - u32ReadPtr + stVPUStatus.u32BsBufSize) % stVPUStatus.u32BsBufSize;
        stVPUStatus.u32BsBufPercent  = VPU_PERCENTAGE * stVPUStatus.u32BsBuFUsedSize / stVPUStatus.u32BsBufSize;
    }
    else
    {
        stVPUStatus.u32BsBuFUsedSize = 0;
        stVPUStatus.u32BsBufPercent  = 0;
    }

    stVPUStatus.u32Profile           = pChanCtx->u32Profile;
    stVPUStatus.u32LumaBitdepth      = pChanCtx->u32LumaBitdepth;
    stVPUStatus.u32ChromaBitdepth    = pChanCtx->u32ChromaBitdepth;

    stVPUStatus.u32SeqChangeCount    = pChanCtx->u32SeqChangeCount;
    stVPUStatus.u32ActualFrmBufNum   = pChanCtx->u32ActualFrameNum;

    for (i = 0; i < stVPUStatus.u32ActualFrmBufNum; i++)
    {
    #ifdef ALLOC_MEM_FRAME_BY_FRAEM
        stVPUStatus.stFrmStatus[i].u32FrmPhyAddr       = pChanCtx->stLinearFrmBuf[i].stMmzBuf.phyaddr;
        stVPUStatus.stFrmStatus[i].u32IsPutVdecQueue   = pChanCtx->stDispFrmBuf[i].bPutToVpss;
    #else
        stVPUStatus.stFrmStatus[i].u32FrmPhyAddr       = pChanCtx->stLinearFrmBuf[i].phyaddr;
        stVPUStatus.stFrmStatus[i].u32IsPutVdecQueue   = pChanCtx->stDispFrmBuf[i].bPutToVpss;
    #endif
    }

    if (NULL != pstOutPutInfo)
    {
        stVPUStatus.u32DecWidth          = pstOutPutInfo->decPicWidth;
        stVPUStatus.u32DecHeight         = pstOutPutInfo->decPicHeight; 
        stVPUStatus.u32DispWidth         = pstOutPutInfo->dispPicWidth;
        stVPUStatus.u32DispHeight        = pstOutPutInfo->dispPicHeight; 
        stVPUStatus.u32NumOfErrMBs       = pstOutPutInfo->numOfErrMBs;
        stVPUStatus.s32indexFrameDisplay = pstOutPutInfo->indexFrameDisplay;
        stVPUStatus.s32indexFrameDecoded = pstOutPutInfo->indexFrameDecoded;
    }

    stVPUStatus.u32ErrRatio              = 0;    
    stVPUStatus.u32OldWidth[0]           = 0;    
    stVPUStatus.u32OldHeight[0]          = 0;    
    stVPUStatus.u32OldFrmBufNum          = 0;  

    VDEC_VPU_ProcStatus(hHandle, &stVPUStatus);

    return;
}

