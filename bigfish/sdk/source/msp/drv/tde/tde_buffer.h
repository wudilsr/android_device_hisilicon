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


STATIC HI_U32 s_u32TDEPhyBuff = 0;
STATIC HI_U32 s_u32TDEBuffRef = 0;
#ifndef TDE_BOOT
static spinlock_t s_TDEBuffLock;
static HI_SIZE_T s_TDEBuffLockFlags;
#endif
STATIC HI_U32  TDE_AllocPhysicBuff(HI_U32 u32CbCrOffset)
{
    HI_U32 u32PhyAddr;
    HI_U32 u32CscBufferSize;

    #ifdef CFG_HI_TDE_CSCTMPBUFFER_SIZE
    u32CscBufferSize = CFG_HI_TDE_CSCTMPBUFFER_SIZE;
    #else
    u32CscBufferSize = g_u32TdeTmpBuf;
    #endif
    TDE_LOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
    if (0 == s_u32TDEPhyBuff)
    {
        if((u32CbCrOffset*3) > u32CscBufferSize)
        {
            TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
            return 0;
        }

        TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
        
        u32PhyAddr = HI_GFX_AllocMem("TDE_TEMP_BUFFER",NULL,u32CscBufferSize);
        if(0 == u32PhyAddr)
        {
            return 0;
        }
        
        TDE_LOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
        if (0 == s_u32TDEPhyBuff)
        {
            s_u32TDEPhyBuff = u32PhyAddr;
            s_u32TDEBuffRef = 0;
        }
        else
        {
            s_u32TDEBuffRef++;
            TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
            HI_GFX_FreeMem(u32PhyAddr);
            return s_u32TDEPhyBuff + u32CbCrOffset;
        }
        
    }

    s_u32TDEBuffRef++;
    TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);

    return s_u32TDEPhyBuff + u32CbCrOffset;
}

STATIC HI_VOID TDE_FreePhysicBuff(HI_VOID)
{
    TDE_LOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
    if (0 == s_u32TDEBuffRef)
    {
        TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
        return;
    }

    s_u32TDEBuffRef--;
    if (0 == s_u32TDEBuffRef)
    {
        HI_U32 u32PhyBuff = s_u32TDEPhyBuff;
        s_u32TDEPhyBuff = 0;
        TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
        HI_GFX_FreeMem(u32PhyBuff);
        return;
    }
    TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* __HI_HANDLE_MGR_H__ */
