/*****************************************************************************
*             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tde_adp.c
* Description:TDE hal interface define
*
* History:
* Version   Date          Author        DefectNum       Description
*
*****************************************************************************/
#include "tde_hal.h"
#include "tde_define.h"
#include "tde_adp.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

static HI_U32 gs_u32Capability = ROP|ALPHABLEND|COLORIZE|CLUT|COLORKEY|CLIP|DEFLICKER|RESIZE|MIRROR|CSCCOVERT|QUICKFILL|QUICKCOPY|\
PATTERFILL;
HI_S32 TdeHalGetCapability(HI_U32 *pstCapability)
{
    *pstCapability = gs_u32Capability;
    return HI_SUCCESS;
}
#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

