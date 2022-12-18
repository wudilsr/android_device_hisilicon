/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name             :   tde_buffer.h
  Version               :   Initial Draft
  Author                :   Hisilicon multimedia software group
  Created               :   2008/03/05
  Last Modified         :
  Description           :
  Function List         :
  History               :
  1.Date                :   2008/03/24
    Author              :   w54130
Modification            :   Created file
******************************************************************************/
#ifndef  __HI_TDE_BUFFER_H__
#define  __HI_TDE_BUFFER_H__

#include "tde_define.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

#define TDE_SCREEN_HEIGHT 720
#define TDE_SCREEM_WIDTH 576


STATIC HI_U32 s_u32TDEPhyBuff[TDE_BUFFER_USAGE_BUTT] = {0, 0, 0};
STATIC HI_U32 s_u32TDEBuffRef = 0;

static HI_U32  TDE_AllocPhysicBuff(TDE_BUFFER_USAGE_E enBuffUsage)
{
    HI_U32 u32PhyAddr;
    
    if(TDE_BUFFER_USAGE_BUTT == enBuffUsage)
    {
        return 0;
    }

    if (0 == s_u32TDEPhyBuff[TDE_BUFFER_USAGE_BITMAP])
    {
        //u32PhyAddr = TDE_MEM_NEW(TDE_MEMPOOL_SIZE, 4, "TDE_TEMP_BUFFER", "ddr") + 0x100000;
        TDE_MEM_NEW(u32PhyAddr,TDE_SCREEN_HEIGHT * TDE_SCREEM_WIDTH * 4, 4, "TDE_TEMP_BUFFER", "ddr");
        if (u32PhyAddr == 0)
        {
            return 0;
        }
        
        s_u32TDEPhyBuff[TDE_BUFFER_USAGE_BITMAP] = u32PhyAddr;
        s_u32TDEPhyBuff[TDE_BUFFER_USAGE_Y] = s_u32TDEPhyBuff[TDE_BUFFER_USAGE_BITMAP];
        s_u32TDEPhyBuff[TDE_BUFFER_USAGE_CbCr] = s_u32TDEPhyBuff[TDE_BUFFER_USAGE_BITMAP] + TDE_SCREEN_HEIGHT * TDE_SCREEM_WIDTH * 2;
        s_u32TDEBuffRef = 0;
    }

    s_u32TDEBuffRef++;
    
    return s_u32TDEPhyBuff[enBuffUsage];
}

static HI_VOID TDE_FreePhysicBuff(HI_VOID)
{
    if (0 == s_u32TDEBuffRef)
    {
        return;
    }
    
    s_u32TDEBuffRef--;
    if (0 == s_u32TDEBuffRef)
    {
        TDE_MEM_FREE(s_u32TDEPhyBuff[TDE_BUFFER_USAGE_BITMAP]);
        s_u32TDEPhyBuff[TDE_BUFFER_USAGE_BITMAP] = 0;
    }

    return;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* __HI_HANDLE_MGR_H__ */
