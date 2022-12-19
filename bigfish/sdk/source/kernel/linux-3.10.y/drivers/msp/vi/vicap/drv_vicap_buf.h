/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_vicap_buf.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/11/25
  Description   : 
  History       :
  1.Date        : 2013/11/25
    Author      : c00186004
    Modification: Created file
******************************************************************************/

#ifndef __DRV_VICAP_BUF_H__
#define __DRV_VICAP_BUF_H__

#include <linux/list.h>
#include "hi_drv_mmz.h"
#include "hi_drv_video.h"


typedef enum hiVICAP_FB_BUF_MODE
{
    VICAP_FB_MODE_ALLOC,
    VICAP_FB_MODE_MMAP,
    //VICAP_FB_MODE_VIRTUAL,

    VICAP_FB_MODE_BUTT
} VICAP_FB_BUF_MODE;

typedef struct hiVICAP_BUF_S
{
    struct list_head stList;     

    HI_U32 u32Index;
    HI_DRV_VIDEO_FRAME_S stVideoFrmInfo;        
    HI_S32 s32SumCnt;  /* sum of total user count */
}VICAP_BUF_S;

typedef struct hiVICAP_BUF_ATTR_S
{
    VICAP_FB_BUF_MODE enBufMode;/* MMAPģʽ����Ҫ����size��num */
    HI_U32 u32BufSize;    
    //HI_U32 *pu32PhyAddr;/* ����ָ�� */
    HI_U32 u32BufNum;
} VICAP_BUF_ATTR_S;

typedef struct hiVICAP_BUF_MGR_S
{
    MMZ_BUFFER_S     stMMZBuf;
    VICAP_BUF_ATTR_S stBufAttr;
    VICAP_BUF_S      *pstBuf;
    struct list_head stFree;
    struct list_head stBusy;
    struct list_head stUsed;
    spinlock_t       stBufLock;   /* ��������ֹ�ж���ռ */
} VICAP_BUF_MGR_S;

/* VICAP Buf��ʼ�� */
HI_S32 VICAP_DRV_BufInit(VICAP_BUF_ATTR_S *pstBufAttr, HI_HANDLE *phBuf);
/* VICAP Bufȥʼ�� */
HI_S32 VICAP_DRV_BufDeInit(HI_HANDLE hBuf);
/* VICAP Buf��λΪ��ʼ״̬ */
HI_S32 VICAP_DRV_BufReset(HI_HANDLE hBuf);
/* ����MMAPģʽ���ⲿBuf�ĵ�ַ */
HI_S32 VICAP_DRV_BufSetExt(HI_HANDLE hBuf, HI_U32 u32PhyAddr[], HI_U32 u32BufNum);
/* ��ȡ����Buf */
HI_S32 VICAP_DRV_BufGet(HI_HANDLE hBuf, VICAP_BUF_S *pstBuf);
/* ����ɼ�������Buf */
HI_S32 VICAP_DRV_BufPut(HI_HANDLE hBuf, VICAP_BUF_S *pstBuf);
/* ��ȡ����Buf */
HI_S32 VICAP_DRV_BufAcquire(HI_HANDLE hBuf, VICAP_BUF_S *pstBuf);
/* �ͷ�Buf */
HI_S32 VICAP_DRV_BufRelease(HI_HANDLE hBuf, VICAP_BUF_S *pstBuf);
/* Buf���ü�����1 */
HI_S32 VICAP_DRV_BufAdd(HI_HANDLE hBuf, HI_U32 u32PhyAddr);
/* Buf���ü�����1 */
HI_S32 VICAP_DRV_BufSub(HI_HANDLE hBuf, HI_U32 u32PhyAddr);


#endif //__DRV_VICAP_BUF_H__

