
/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_ua.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef PQ_MNG_UA_H__
#define PQ_MNG_UA_H__

#include "hi_type.h"
#include "drv_pq_ext.h"
#include "pq_mng_zme.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_S32 PQ_MNG_InitUA(HI_VOID);
HI_S32 PQ_MNG_DeInitUA(HI_VOID);

HI_VOID PQ_MNG_SetVdpZme(HI_U32 u32LayerId,
                         ALG_VZME_DRV_PARA_S* pstZmeDrvPara,
                         HI_BOOL  bFirEnable);

HI_VOID PQ_MNG_SetVpssZme(HI_U32 u32LayerId,
                          S_CAS_REGS_TYPE* pstReg,
                          ALG_VZME_DRV_PARA_S* pstZmeDrvPara,
                          HI_BOOL  bFirEnable);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*  __DRV_DISP_UA_H__  */


