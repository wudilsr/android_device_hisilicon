/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_mng_dci.h
  Version       : Initial Draft
  Author        : l00212594
  Created       : 2013/10/15
  Description   :

******************************************************************************/

#ifndef __PQ_MNG_DCI_H__
#define __PQ_MNG_DCI_H__

#include "hi_type.h"
#include "pq_hal_dci.h"
#include "drv_pq_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*
 *DCI文件结构
 */
typedef struct  hiDCI_INFO_HEADER_S
{
    HI_U8             au8MagicNumber[8];
    HI_U16            u16DCITblNum;
    HI_U16            u16DCITblSize;
    HI_U32            u32CRC;
} DCI_INFO_HEADER_S;

typedef struct  hiDCI_TABLE_DATA_S
{
    HI_CHAR cIndexName[8];
    DCI_WGT_S    stDCITable;
} DCI_TABLE_DATA_S;

typedef struct  hiDCI_INFO
{
    DCI_INFO_HEADER_S stDCIHeader;
    HI_U8*    pstDCIData;
} DCI_INFO_S;

/*DCI 增益类型*/
typedef enum hiDCI_LEVEL_E
{
    DCI_LEVEL_LOW = 0,
    DCI_LEVEL_MID,
    DCI_LEVEL_HIGH,

    DCI_LEVEL_BUTT
} DCI_LEVEL_E;

/*DCI统计窗口*/
typedef struct  hiDCI_WIN_S
{
    HI_U16      u16HStar;
    HI_U16      u16HEnd;
    HI_U16      u16VStar;
    HI_U16      u16VEnd;
} DCI_WIN_S;


/**
 \brief 初始化DCI模块
 \attention \n
无

 \param[in] *pszPath:外部文件路径

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_InitDCI(PQ_PARAM_S* pstPqParam, HI_BOOL bDefault);


/**
 \brief 去初始化DCI模块
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_DeinitDCI(HI_VOID);


/**
 \brief 获取DCI模块开关状态
 \attention \n
无

 \param[out] *pu32OnOff;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetDCIEnable(HI_U32* pu32OnOff);

/**
 \brief 使能DCI模块
 \attention \n
无

 \param[in] bOnOff;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_EnableDCI(HI_BOOL bOnOff);


/**
 \brief 设置DCI强度增益等级
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_SetDCILevelGain(HI_U32 u32DCILevelGain, HI_U32 u32SourceMode);

/**
 \brief 设置DCI强度增益等级
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetDCILevelGain(HI_U32* pu32DCILevelGain);



/**
 \brief DCI开关卖场模式;
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_DCIDemoMode(HI_BOOL bOnOff);


/**
 \brief 更新DCI直方图统计窗口
 \attention \n
无

 \param[in] *pstWin;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_UpdateDCIWin(DCI_WIN_S* pstWin);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
