/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_uf.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/11/11
  Description   : 
  History       :
  1.Date        : 2013/11/11
    Author      : c00186004
    Modification: Created file
******************************************************************************/

#ifndef __HI_DRV_UFH__
#define __HI_DRV_UFH__

#include "hi_drv_video.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef HI_S32 (*FN_UF_BufUserSub)(HI_HANDLE hHandle, HI_U32 u32PhysAddr);
typedef HI_S32 (*FN_UF_BufUserAdd)(HI_HANDLE hHandle, HI_U32 u32PhysAddr);

typedef struct hiUF_INIT_ATTR_S
{
    HI_HANDLE        hHandle;
    FN_UF_BufUserSub pfnUfBufUserSub;/* ���ü����� */
    FN_UF_BufUserAdd pfnUfBufUserAdd;/* ���ü����� */    
    HI_U32           u32Depth;    /* �û��ܹ���ȡ�����buf�� */
} UF_INIT_ATTR_S;

/* ��ʼ��,�����û����ռ�õ�ͼ��֡�� */
extern HI_VOID *HI_DRV_UF_Init(UF_INIT_ATTR_S *pstInitAttr);

/* ȥ��ʼ�� */
extern HI_S32 HI_DRV_UF_DeInit(HI_VOID *phUf);

/* �û���ȡ�ɼ�ͼ��֡ */
extern HI_S32 HI_DRV_UF_AcquireFrm(HI_VOID *phUf, HI_DRV_VIDEO_FRAME_S *pstUserFrm);

/* �û��ͷ�ȡ�ɼ�ͼ��֡ */
extern HI_S32 HI_DRV_UF_ReleaseFrm(HI_VOID *phUf, HI_DRV_VIDEO_FRAME_S *pstUserFrm);

/* ��ȡVI�ɼ�ͼ��֡ */
extern HI_S32 HI_DRV_UF_SendFrm(HI_VOID *phUf, HI_DRV_VIDEO_FRAME_S *pstUserFrm);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif/* __HI_DRV_UFH__ */

