/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : tde_buffer.h
Version             : Initial Draft
Author              : 
Created             : 2014/08/06
Description         : 
Function List       : 
History             :
Date                       Author                   Modification
2014/08/06                 y00181162                Created file        
******************************************************************************/

#ifndef __TDE_BUFFER_H__
#define __TDE_BUFFER_H__


/*********************************add include here******************************/


#include "tde_define.h"

/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/

#define TDE_SCREEN_HEIGHT 720
#define TDE_SCREEM_WIDTH 576

/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/

STATIC HI_U32 s_u32TDEPhyBuff[TDE_BUFFER_USAGE_BUTT] = {0, 0, 0};
STATIC HI_U32 s_u32TDEBuffRef = 0;

/******************************* API declaration *****************************/

static HI_U32  TDE_AllocPhysicBuff(TDE_BUFFER_USAGE_E enBuffUsage)
{
    HI_U32 u32PhyAddr;
    
    if(TDE_BUFFER_USAGE_BUTT == enBuffUsage)
    {
        return 0;
    }

    if (0 == s_u32TDEPhyBuff[TDE_BUFFER_USAGE_BITMAP])
    {
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
#endif /* __cplusplus */

#endif /* __TDE_BUFFER_H__ */
