/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_vicap.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/10/25
  Description   : 
  History       :
  1.Date        : 2013/10/25
    Author      : w00248302/c00186004
    Modification: Created file
******************************************************************************/

#ifndef __DRV_VICAP_H__
#define __DRV_VICAP_H__
#include "hi_osal.h"

#include "drv_vicap_buf.h"
#include "hi_debug.h"
#include "hi_module.h"
#include "hi_drv_vicap.h"
#include "hi_math.h"
#include "hal_vicap.h"
#include "hi_drv_struct.h"
#if    defined(CHIP_TYPE_hi3751v100)   \
    || defined(CHIP_TYPE_hi3751v100b)  
#include "drv_hddec_ext.h"
#endif
#if    defined(CHIP_TYPE_hi3751v100)   \
    || defined(CHIP_TYPE_hi3798cv100)  \
    || defined(CHIP_TYPE_hi3796cv100)  
#include "drv_hdmirx_ext.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define HI_FATAL_VICAP(fmt...) HI_FATAL_PRINT(HI_ID_VICAP, fmt)
#define HI_ERR_VICAP(fmt...) HI_ERR_PRINT(HI_ID_VICAP, fmt)
#define HI_WARN_VICAP(fmt...) HI_WARN_PRINT(HI_ID_VICAP, fmt)
#define HI_INFO_VICAP(fmt...) HI_INFO_PRINT(HI_ID_VICAP, fmt)
#define HI_DEBUG_VICAP(fmt...) HI_DBG_PRINT(HI_ID_VICAP, fmt)

#define VICAP_ALIGN_8BIT_YSTRIDE(w)         HI_SYS_GET_STRIDE(w)
#define VICAP_ALIGN_10BIT_COMP_YSTRIDE(w)   HI_SYS_GET_STRIDE(HICEILING(w*10, 8)) /* l0bit����ģʽ */

#define VICAP_TIME_DIFF_US(a, b) (((a.tv_sec) - (b.tv_sec))*1000000 + ((a.tv_usec) - (b.tv_usec)))

#define VICAP_SKIP_SAMPLE_OFF 0xffffffff  /* ����������skip���� */
#define VICAP_SKIP_SAMPLE_2X  0xaaaaaaaa  /* 2����������skip���� */
#define VICAP_SKIP_SAMPLE_4X  0x11111111  /* 4����������skip���� */
#define VICAP_SKIP_SAMPLE_8X  0x01010101  /* 8����������skip���� */


#define VICAP_MIN_WIDTH  128              /* VICAP��Сͼ���� */
#define VICAP_MIN_HEIGHT 128              /* VICAP��Сͼ��߶� */

#define VICAP_MIN_BUFNUM 2              /* VICAP��Сbuf��Ŀ */

#define VICAP_MAX_HFIR_RATIO  16777216       /* ���ˮƽ��С����Ϊ:16��(65536 =16*1048576) */
#define VICAP_MAX_VFIR_RATIO  16             /*���ֱ���ű���Ϊ16�����ű���Ϊ2-16������*/
#define VICAP_NO_HFIR_RATIO  (1 << 20)       /* �����ű���Ϊ2^20 == 1048576 */
#define VICAP_2X_HFIR_RATIO  ((1 << 20) * 2) /* �����ű���Ϊ2^21 == 1048576 */
#define VICAP_3X_HFIR_RATIO  ((1 << 20) * 3) /* �����ű���Ϊ2^22 == 1048576 */
#define VICAP_4X_HFIR_RATIO  ((1 << 20) * 4) /* �����ű���Ϊ2^23 == 1048576 */

#define VICAP_USEROUT_DEPTH     0xff      

/* ͨ���������� */
#define  VICAP_CHN_DATA_MASK(a)   ((0xffff << (16 - a)) & 0xffff)

/* ͨ���ж�����,����0ʹ�ܳ�/֡��ʼ�жϣ�����1���γ�/֡��ʼ�ж� */                         
#define VICAP_CHN_INT_MASK0 (VICAP_CHN_INT_FRAMESTART|VICAP_CHN_INT_BUFOVF|VICAP_CHN_INT_FIELDTHROW|VICAP_CHN_INT_YBUSERR|VICAP_CHN_INT_CBUSERR)
#define VICAP_CHN_INT_MASK1 (VICAP_CHN_INT_BUFOVF|VICAP_CHN_INT_FIELDTHROW|VICAP_CHN_INT_YBUSERR|VICAP_CHN_INT_CBUSERR)

/*������*/
#define   VICAP_CONTEXT_ID0   0
#define   VICAP_CONTEXT_ID1   1

/*ͨ��ID*/
#define   VICAP_CHNINDEX0   0
#define   VICAP_CHNINDEX1   1
/*CROP*/
#define   VICAP_CROP0 0
#define   VICAP_CROP1 1
/*LEFT AND ROGHT*/
#define   VICAP_EYE_LEFT 0
#define   VICAP_EYE_RIGHT 1

/*��Чֵ*/
#define   INVALID_ID  0xFF

/*Handle*/
#define GETVICAPID(a) ((a >> 24) & 0xff)
#define GETCONTEXTID(a) ((a >> 16) & 0xff)
#define GETPHYPT(b) ((b >> 8) & 0xff)
#define GETPHYCHN(c) (c & 0xff) 


#define VICAP_IS_ODD_NUM(a) (a & 0x1)
#define PERI_CRG55_OFFSET     0x00DC


/*FHD*/
#define VICAP_FHD_WIDTH 1920
#define VICAP_FHD_HEIGHT 1080

/*UHD*/
#define VICAP_UHD_WIDTH 3840
#define VICAP_UHD_HEIGHT 2160

/*720*/
#define VICAP_720_WIDTH 1280
#define VICAP_720_HEIGHT 720


#define VICAP_FRMRATE_24HZ  24  
#define VICAP_FRMRATE_25HZ  25   
#define VICAP_FRMRATE_30HZ  30
#define VICAP_FRMRATE_50HZ  50
#define VICAP_FRMRATE_60HZ  60
#define VICAP_FRMRATE_85HZ  85
#define VICAP_FRMRATE_120HZ 120

#define VICAP_COUNT_NONE 0

typedef enum hiSYS_VICAP_CLK_SEL_E
{
    SYS_VICAP_CLK_TVD = 0,
    SYS_VICAP_CLK_HDDEC,
    SYS_VICAP_CLK_HDMI_CTRL0 ,
    SYS_VICAP_CLK_HDMI_CTRL1,
    SYS_VICAP_CLK_HDMI_CTRL0_CTRL1,    
    SYS_VICAP_CLK_EXTERN,
    
    SYS_VICAP_CLK_BUTT,
} SYS_VICAP_CLK_SEL_E;

/* ͨ��״̬ */
typedef enum hiVICAP_STATUS_E
{
    VICAP_STATUS_STOP = 0,     /* ͨ�� stopped */
    VICAP_STATUS_START,       /* ͨ�� start stop */
    VICAP_STATUS_STOPPING,    /* ͨ�� stopping */
    
    VICAP_WAIT_STOP_BUTT,
} VICAP_STATUS_E;

/* VICAP����ʱ�� */
typedef enum hiSYS_VICAP_WORKHZ_E
{
    VICAP_WORKHZ_300HZ = 0,     /* VICAP����ʱ�� 300MHZ*/
    VICAP_WORKHZ_200HZ,       /* VICAP����ʱ�� 200MHZ*/
    VICAP_WORKHZ_100HZ,    /* VICAP����ʱ�� 100MHZ*/
    
    VICAP_WORKHZ_BUTT,
} VICAP_WORKHZ_E;

/* HDMIʱ�� */
typedef enum hiSYS_VICAP_HDMIRX_WORKHZ_E
{
    VICAP_HDMIRX_WORKHZ_PPC = 0,     /* clk_vi_ppc_com */
    VICAP_HDMIRX_WORKHZ_HDMIRX,       /* clk_hdmi_rx */
    
    VICAP_HDMIRX_WORKHZ_BUTT,
} VICAP_HDMIRX_WORKHZ_E;

/* Source Timing Info */
typedef struct hiVICAP_SOURCETIMING_INFO_S
{
    HI_DRV_SOURCE_E             enSource;
    HI_U32                      u32SrcWidth;
    HI_U32                      u32SrcHeight;
    HI_U32                      u32SrcFrmRate;
    HI_DRV_FRAME_TYPE_E         en3dType;
    HI_DRV_COLOR_SPACE_E        enSrcColorSpace;
    HI_DRV_COLOR_SYS_E          enSrcColorSys;
    HI_BOOL                     bGraphicMode;
    HI_BOOL                     bInterlace;    
}VICAP_SOURCETIMING_INFO_S;


typedef struct hiVICAP_FRAME_STATUS_S
{
    HI_HANDLE                 hBufHandle;       /*BufHandle*/ 
    HI_U32                    u32DstWidth;      /* ͨ����� */
    HI_U32                    u32DstHeight;     /* ͨ���߶� */
    HI_DRV_PIXEL_BITWIDTH_E   enDstBitWidth;    /* ���֡��λ�� */
    HI_DRV_PIX_FORMAT_E       enVideoFormat;    /* ����洢��ʽ */
    HI_U32                    u32DstFrameRate;   /* ֡�� */
    HI_U32                    u32YStride;       /* ͨ��Y����ƫ��*/
    HI_U32                    u32CStride;       /* ͨ��C����ƫ�� */     
    HI_U32                    u32BufSize;       /* ֡buffer��С */
    HI_BOOL                   b3D;              /*�Ƿ�3D���룬3D����*/
    HI_BOOL                   bCsc;              /*�Ƿ���CSCת��*/
    HI_DRV_COLOR_SPACE_E      eCscColorSpace;   /*RGBתYUV�Ժ��ɫ�ʿռ�*/
    VICAP_SOURCETIMING_INFO_S stSourceTimingInfo; /**/
} VICAP_FRAME_STATUS_S;

/* VICAP ͼ�񻺴���Ϣ */
typedef struct hiVICAP_BUF_BLK_S
{
    volatile HI_BOOL bValid;
    HI_DRV_VIDEO_FRAME_S stVicapFrameInfo;
} VICAP_BUF_BLK_S;

/* ֡�ʿ�����Ϣ */
typedef struct hiVICAP_FRM_RATE_CTRL_S
{
    HI_U32 u32DstFrmRate;   /* VIĿ��֡��*/
    HI_U32 u32SrcFrmRate;/* ����Դ��֡��(PAL:25,NTSC:30,DC: )*/
    HI_S32 s32LostFrmKey;/* ��֡���Թؼ�ֵ*/
} VICAP_FRM_RATE_CTRL_S;

/* VICAP������Ϣ */
typedef struct hiVIAP_CHN_DBG_INFO_S
{
    HI_U32 u32IntCnt;         /* ͨ���ж�����������*/
    HI_U32 u32IntTime;        /* �ж�ռ��ʱ�䣬������*/
    HI_U32 u32IntTimeMax;     /* ����ж�ռ��ʱ�䣬������*/
    struct timeval stLastIntTime;/* �ϴ��ж�ʱ�䣬������*/
    HI_U32 u32IntvTime;       /* �����жϼ��ʱ�䣬������*/
    HI_U32 u32BufCnt;         /* ռ��buf����������*/
    HI_BOOL bStartCnt;        /* �Ƿ�ʼ������ʧ�жϡ����׳��� */
    HI_U32 u32LostInt;        /* �ж϶�������������*/
    HI_U32 u32TopLost;        /* �����ж϶�������������*/
    HI_U32 u32BotLost;        /* �׳��ж϶�������������*/
    HI_U32 u32GetVbFail;      /* ��ȡ��Ƶ֡����ʧ�ܴ���*/
    HI_U32 u32Sequence;       /* ֡���� */
    struct timeval stLastSendTime; /* �ϴη���֡ʱ�䣬������*/
    HI_U32 u32SendvTime;      /* ���ڷ���֡���ʱ�䣬������*/
    HI_U32 u32SendFrmTime;    /* ����֡ռ��ʱ�䣬������*/
    HI_U32 u32SendCnt;        /* ����֡�� ������*/
    HI_U32 u32UpdateCnt;      /* ������Ը��¼���*/
} VICAP_CHN_DBG_INFO_S;

/* VICAP���������ݽṹ*/
typedef struct hiVICAP_DRV_CTX_S
{
    HI_HANDLE                   	  hViCap;          /*��·VICAP��handle��*/
    VICAP_STATUS_E                    enStatus;        /*����ͨ��״̬*/
    HI_DRV_VICAP_ATTR_S               stVicapAttr;     /*VICAP�豸����*/
    volatile HI_BOOL            	  bUpdateCfg;      /* �ȴ�����VI������� */   
    HI_DRV_VICAP_OUTPUT_ATTR_S        stOutAttrtmp;    /* ��ǰVICAP�������,��̬�������� */
    VICAP_FRAME_STATUS_S              stFrmStatus;     /*��ǰ֡״̬��Ϣ*/
    VICAP_BUF_BLK_S                   stThisFrm;       /*this frame buffer*/
    VICAP_BUF_BLK_S                   stNextFrm;       /*this frame buffer*/
    VICAP_FRM_RATE_CTRL_S        	  stFrmRateCtrl;   /* ֡�ʿ��� */
    HI_BOOL                 		  bTopFrmLost;     /* ���ڶ����ж϶�ʧʱ���쳣���� */
    HI_VOID                      	  *pUfHandle;      /* �û���ȡUF֡���ݵľ�� */
    HI_HANDLE                         hBufHandle ;    /*��ȡVI Bufģ��֡���ݵľ��*/  
    VICAP_CHN_DBG_INFO_S           	  stChnDbg;        /* debug info for chn*/
    wait_queue_head_t                 stWaitQueue;     /* VICAP Disable �ȴ����� */
    HI_HANDLE                         hDst;            /* �ص������͸��������ȷ������һ·VI */
    PFN_VICAP_CALLBACK                pfUserCallBack;  /* �ص����� */
} VICAP_DRV_CTX_S;

typedef struct hiVICAP_USED_EXT_FUN_S
{
#if    defined(CHIP_TYPE_hi3751v100)   \
    || defined(CHIP_TYPE_hi3751v100b)  
    HDDEC_EXPORT_FUNC_S *pHddecExtFunc;
#endif
#if    defined(CHIP_TYPE_hi3751v100)   \
    || defined(CHIP_TYPE_hi3798cv100)  \
    || defined(CHIP_TYPE_hi3796cv100)    
    HDMIRX_EXPORT_FUNC_S *pHdmirxExtFunc;
#endif 
} VICAP_USED_EXT_FUNC_S;

HI_S32 VICAP_DRV_GetVicapCtx(HI_U32 u32VicapContextId, VICAP_DRV_CTX_S **pstVicapDrvCtx);

HI_S32 VICAP_DRV_ProcAdd(HI_HANDLE hVicap);

HI_S32 VICAP_DRV_ProcDel(HI_HANDLE hVicap);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif/* __DRV_VICAP_H__ */
