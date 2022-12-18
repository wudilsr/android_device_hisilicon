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
#endif /* __cplusplus */

#pragma pack(1)


/*PQ Bin Module类型*/
typedef enum hiPQ_BIN_MODULE_E
{
    PQ_MODULE_DEI = 0x1,
    PQ_MODULE_FMD = 0x2,
    PQ_MODULE_HSHARPEN = 0x4,
    PQ_MODULE_DNR = 0x8,
    PQ_MODULE_DCI = 0x10,
    PQ_MODULE_ACM = 0x20,
    PQ_MODULE_SHARPEN_CTRL = 0x40,
    PQ_MODULE_SHARPEN_COMM = 0x80,
    PQ_MODULE_SR = 0x100,
    PQ_MODULE_DB = 0x200,
    PQ_MODULE_DR_HD = 0x400,
    PQ_MODULE_ALL = 0xffff,
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


/**
 \brief 去初始化pq table;
 \attention \n
无

 \param[in]

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DeInitPQTable(HI_VOID);

/**
 \brief 加载解析PQTable;
 \attention \n
  无

 \param[in];

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_InitPQTable(PQ_PARAM_S* pstPqParam, HI_BOOL bDefault);

HI_S32 PQ_MNG_UpdatePhyList(HI_U32 u32Addr, HI_U8 u8Lsb, HI_U8 u8Msb, HI_U8 u8SourceMode, HI_U8 u8OutputMode, HI_U32 u32Value);

HI_S32 PQ_MNG_SetVdpReg(HI_U32 u32Addr, HI_U8 u8Lsb, HI_U8 u8Msb, HI_U32 u32Value);

HI_S32 PQ_MNG_SetVpssReg(HI_U32 u32Addr, HI_U8 u8Lsb, HI_U8 u8Msb, HI_U32 u32Value);

HI_S32 PQ_MNG_LoadPhyList(PQ_REG_TYPE_E enRegType, PQ_SOURCE_MODE_E enSourceMode, PQ_OUTPUT_MODE_E enOutputMode, PQ_BIN_MODULE_E enModule);

PQ_SOURCE_MODE_E PQ_MNG_CheckSourceMode(HI_U32 u32Width, HI_U32 u32Height);/* check Timing Source Mode*/

PQ_OUTPUT_MODE_E PQ_MNG_CheckOutputMode(HI_BOOL bSRState);/* check Timing Output Mode*/




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
