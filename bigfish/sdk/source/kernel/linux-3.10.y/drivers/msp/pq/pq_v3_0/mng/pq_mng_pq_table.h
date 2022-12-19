/******************************************************************************

  Copyright (C), 2014-2015, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_mng_pq_table.h
  Version       : Initial Draft
  Author        : p00203646
  Created       : 2013/10/15
  Description   :

******************************************************************************/

#ifndef __PQ_MNG_PQ_TABLE_H__
#define __PQ_MNG_PQ_TABLE_H__

#include "hi_drv_pq.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*soft table pq bin define*/
#define PQ_SOFT_IP_DETECT    0xfffe0001


/*PQ Bin Module¿‡–Õ*/
typedef enum hiPQ_BIN_MODULE_E
{
    PQ_BIN_MODULE_DEI      = 0x1,
    PQ_BIN_MODULE_FMD      = 0x2,
    PQ_BIN_MODULE_SHARPEN  = 0x4,
    PQ_BIN_MODULE_DNR      = 0x8,
    PQ_BIN_MODULE_DCI      = 0x10,
    PQ_BIN_MODULE_ACM      = 0x20,
    PQ_BIN_MODULE_HSHARPEN = 0x40,
    PQ_BIN_MODULE_SR       = 0x100,
    PQ_BIN_MODULE_DB       = 0x200,
    PQ_BIN_MODULE_DM       = 0x400,
    PQ_BIN_MODULE_TNR      = 0x800,
    PQ_BIN_MODULE_DS       = 0x1000,
    PQ_BIN_MODULE_ALL      = 0xffff,
} PQ_BIN_MODULE_E;

/*PQ Source Mode*/
typedef enum hiPQ_SOURCE_MODE_E
{
    SOURCE_MODE_NO = 0,
    SOURCE_MODE_SD,
    SOURCE_MODE_HD,
    SOURCE_MODE_UHD,
    SOURCE_MODE_ALL,
} PQ_SOURCE_MODE_E;

/*PQ Output Mode*/
typedef enum hiPQ_OUTPUT_MODE_E
{
    OUTPUT_MODE_NO = 0,
    OUTPUT_MODE_SD,
    OUTPUT_MODE_HD,
    OUTPUT_MODE_UHD,
    OUTPUT_MODE_ALL,
} PQ_OUTPUT_MODE_E;


/*PQ Reg Type*/
typedef enum hiPQ_REG_TYPE_E
{
    REG_TYPE_VPSS = 0,
    REG_TYPE_VDP,
    REG_TYPE_ALL,
} PQ_REG_TYPE_E;


/* check Timing Source Mode*/
PQ_SOURCE_MODE_E PQ_MNG_CheckSourceMode(HI_U32 u32Width, HI_U32 u32Height);
/* check Timing Output Mode*/
PQ_OUTPUT_MODE_E PQ_MNG_CheckOutputMode(HI_BOOL bSRState);

HI_S32 PQ_MNG_DeInitPQTable(HI_VOID);

HI_S32 PQ_MNG_InitPQTable(PQ_PARAM_S* pstPqParam, HI_BOOL bDefault);

HI_S32 PQ_MNG_UpdatePhyList(HI_U32 u32Addr, HI_U8 u8Lsb, HI_U8 u8Msb, HI_U8 u8SourceMode, HI_U8 u8OutputMode, HI_U32 u32Value);

HI_S32 PQ_MNG_SetVdpReg(HI_U32 u32Addr, HI_U8 u8Lsb, HI_U8 u8Msb, HI_U32 u32Value);

HI_S32 PQ_MNG_SetVpssReg(HI_U32 u32Addr, HI_U8 u8Lsb, HI_U8 u8Msb, HI_U32 u32Value);

HI_S32 PQ_MNG_LoadPhyList(PQ_REG_TYPE_E enRegType, PQ_SOURCE_MODE_E enSourceMode, PQ_OUTPUT_MODE_E enOutputMode, PQ_BIN_MODULE_E enModule);

HI_S32 PQ_MNG_InitPhyList(HI_U32 u32ID, PQ_REG_TYPE_E enRegType, PQ_SOURCE_MODE_E enSourceMode, PQ_OUTPUT_MODE_E enOutputMode, PQ_BIN_MODULE_E enModule);

HI_U32 PQ_MNG_GetSoftTable(HI_U32 u32Lut, PQ_SOURCE_MODE_E enSourceMode, PQ_OUTPUT_MODE_E enOutputMode, HI_U32 u32DefaultValue);

HI_S32 PQ_MNG_SetSoftTable(HI_U32 u32Lut, PQ_SOURCE_MODE_E enSourceMode, PQ_OUTPUT_MODE_E enOutputMode, HI_U32 u32Value);

HI_S32 PQ_MNG_SetReg(HI_PQ_REGISTER_S* pstAttr, PQ_SOURCE_MODE_E enSourceMode, PQ_OUTPUT_MODE_E enOutputMode);

HI_S32 PQ_MNG_GetReg(HI_PQ_REGISTER_S* pstAttr);

HI_VOID PQ_MNG_PrintTable( HI_BOOL bIsAll, HI_U32 u32PriAddr);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
