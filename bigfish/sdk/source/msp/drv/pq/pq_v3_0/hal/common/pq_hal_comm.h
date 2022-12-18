/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_hal_comm.h
  Version       : Initial Draft
  Author        : l00212594
  Created       : 2013/10/15
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_COMM_H__
#define __PQ_HAL_COMM_H__

#ifndef  __PQ_PLATFORM_BOOT__
#include <linux/fs.h>
#endif
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_module.h"
#include "hi_reg_common.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define VPSS_HANDLE_NUM    16
#define VDP_CHN_MAX        3
#define VDP_VP_MAX         2

#define VID_MAX            5 /* in 98c equal to 8; but equal to 5 in 98m and 98m_a*/


#define VDP_CHN_OFFSET     0x400
#define VDP_VID_OFFSET     0x800
#define VDP_VP_OFFSET      0x800

#define PQ_TRACE(level, range, fmt...) \
    do{\
        if (level <= range)\
        {\
            HI_TRACE(HI_LOG_LEVEL_ERROR, HI_ID_PQ, fmt);\
        }\
    }while(0)

#define PQ_CHECK_NULL_PTR(ptr) \
    do{\
        if (NULL == ptr){\
            HI_TRACE(HI_LOG_LEVEL_ERROR, HI_ID_PQ, "pointer is NULL!\n");\
            return HI_FAILURE;\
        }\
    }while(0)

typedef enum hiPQ_HAL_VDP_CHN_E
{
    VDP_CHN_DHD0    = 0,
    VDP_CHN_DHD1    = 1,
    VDP_CHN_DSD0    = 2,
    VDP_CHN_WBC0    = 3,
    VDP_CHN_WBC1    = 4,
    VDP_CHN_WBC2    = 5,
    VDP_CHN_WBC3    = 6,
    VDP_CHN_NONE    = 7,
    VDP_CHN_BUTT

} PQ_HAL_VDP_CHN_E;

typedef enum tagPQ_HAL_LAYER_VP_E
{
    VDP_LAYER_VP0   = 0,
    VDP_LAYER_VP1   = 1,
    VDP_LAYER_DHD0  = 2,

    VDP_LAYER_VP_BUTT

} PQ_HAL_LAYER_VP_E;


typedef enum tagVDP_LAYER_VID_E
{
    VDP_LAYER_VID0  = 0, /* VDP_LAYER_V0 */
    VDP_LAYER_VID1  = 1, /* VDP_LAYER_V1 */
    VDP_LAYER_VID2  = 2, /* VDP_LAYER_V2 */
    VDP_LAYER_VID3  = 3, /* VDP_LAYER_V3 */
    VDP_LAYER_VID4  = 4, /* VDP_LAYER_V4 */

    VDP_LAYER_VID5  = 5, /* VDP_LAYER_V5 */
    VDP_LAYER_VID6  = 6, /* for FI pixel */ /* using in VDP */
    VDP_LAYER_VID7  = 7, /* for FI info  */ /* using in VDP */

    VDP_LAYER_VID_BUTT

} VDP_LAYER_VID_E;


/* PQ模块开关信息 */
typedef struct hiPQ_HAL_MODULE_S
{
    HI_BOOL                     bFMD;         /*FMD开关*/
    HI_BOOL                     bTNR;         /*NR开关*/
    HI_BOOL                     bCCCL;        /*CCCL开关*/
} PQ_HAL_MODULE_S;

/**
 \brief 初始化HAL模块，申请本地寄存器内存;
 \attention \n
  无

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_Init(HI_VOID);

/**
 \brief 去初始化HAL模块,释放本地寄存器内存;
 \attention \n
  无

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_Deinit(HI_VOID);

/**
 \brief 更新VPSS寄存器;
 \attention \n
  无

 \param[in] u32HandleNo  : VPSS通道号
 \param[in] *pstVPSSReg  : 由驱动传过来的寄存器指针

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_UpdateVpssReg(HI_U32 u32HandleNo, S_CAS_REGS_TYPE* pstVPSSReg, S_VPSSWB_REGS_TYPE* pstVPSSWbcReg);


/**
 \brief 更新VDP寄存器;
 \attention \n
  无

 \param[in] *pstVDPReg  : 由驱动传过来的VPSS寄存器指针

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_UpdateVdpReg(S_VDP_REGS_TYPE* pstVDPReg);

/**
 \brief 更新PQ Module开关参数;
 \attention \n
  无

 \param[in] *pstPQModule

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_UpdatePQModule(PQ_HAL_MODULE_S* pstPQModule);

/**
 \brief 检查VPSS当前u32HandleNo对应虚拟寄存器是否有效;
 \attention \n
  无

 \param[in] u32HandleNo

 \retval ::HI_BOOL

 */
HI_BOOL PQ_HAL_CheckVpssValid(HI_U32 u32HandleNo);

/**
 \brief 检查VDP寄存器是否有效;
 \attention \n
  无

 \param[in] none

 \retval ::HI_BOOL

 */
HI_BOOL PQ_HAL_CheckVdpValid(HI_VOID);

/**
 \brief 获取VPSS当前寄存器;
 \attention \n
  无

 \param[in] u32HandleNo

 \retval ::VPSS寄存器指针

 */
S_CAS_REGS_TYPE* PQ_HAL_GetVpssReg(HI_U32 u32HandleNo);

/**
 \brief 获取VPSS WBC INFO;
 \attention \n
  无

 \param[in] u32HandleNo

 \retval ::VPSS WBC INFO

 */
S_VPSSWB_REGS_TYPE* PQ_HAL_GetVpssWbcReg(HI_U32 u32HandleNo);

/**
 \brief 获取VDP当前寄存器;
 \attention \n
  无

 \param[in] none

 \retval ::VDP寄存器指针

 */
S_VDP_REGS_TYPE* PQ_HAL_GetVdpReg(HI_VOID);

/**
 \brief 获取PQ Module开关参数;
 \attention \n
  无

 \param[in] none

 \retval ::PQ Module寄存器指针

 */
PQ_HAL_MODULE_S* PQ_HAL_GetPQModule(HI_VOID);

/**
 \brief 写寄存器;
 \attention \n
  无

 \param[in] u32HandleNo
 \param[in] u32RegAddr
 \param[in] u32Value

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_WriteRegister(HI_U32 u32HandleNo, HI_U32 u32RegAddr, HI_U32 u32Value);

/**
 \brief 读寄存器;
 \attention \n
  无

 \param[in] u32HandleNo
 \param[in] u32RegAddr
 \param[out] *pu32Value

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_ReadRegister(HI_U32 u32HandleNo, HI_U32 u32RegAddr, HI_U32* pu32Value);

/**
 \brief 按照起始BIT位复制U32参数;
 \attention \n
  无

 \param[in] u32Src
 \param[in] u32SrcStartBit
 \param[out] *pu32Dst
 \param[in] u32DstStartBit
 \param[in] u32Num

 \retval ::

 */
HI_VOID PQ_HAL_CopyU32ByBit(HI_U32 u32Src, HI_U32 u32SrcStartBit, HI_U32* pu32Dst, HI_U32 u32DstStartBit, HI_U32 u32Num);

/**
 \brief 根据bit位更新U32参数
 \attention \n
  无

 \param[out] pulData,;
 \param[in] ucBitNo

 \retval ::HI_SUCCESS

 */
HI_VOID  PQ_HAL_U32SetBit( HI_U32* pulData, HI_U8 ucBitNo);

/**
 \brief 将U32对应的bit位清零
 \attention \n
  无

 \param[out] pulData,;
 \param[in] ucBitNo

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_U32ClearBit( HI_U32* pulData, HI_U8 ucBitNo);

/**
 \brief 从U32参数根据最高位和最低获取对应的值
 \attention \n
  无

 \param[in]  ulData,  ucMaxBit,  ucMinBit;

 \retval ::HI_SUCCESS

 */
HI_U32 PQ_HAL_GetU32ByBit( HI_U32 ulData, HI_U8 ucMaxBit, HI_U8 ucMinBit);

/**
 \brief 根据最高位和最低位设置U32参数对应的值
 \attention \n
  无

 \param[in] pulData, ucMaxBit, ucMinBit, ulValue;

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_SetU32ByBit( HI_U32* pulData, HI_U8 ucMaxBit, HI_U8 ucMinBit, HI_U32 ulValue);

HI_BOOL PQ_HAL_IsVpssReg(HI_U32 u32RegAddr);

HI_BOOL PQ_HAL_IsVdpReg(HI_U32 u32RegAddr);

HI_BOOL PQ_HAL_IsSpecialReg(HI_U32 u32RegAddr);

HI_U32 PQ_HAL_RegRead(volatile HI_U32 a);

HI_VOID PQ_HAL_RegWrite(volatile HI_U32 a, HI_U32 value);

HI_S32 PQ_REG_RegWrite(volatile HI_U32* a, HI_U32 b);

HI_U32 PQ_REG_RegRead(volatile HI_U32* a);

HI_U32 PQ_HAL_CalCRC32(HI_U32 crc, HI_U8* buf, HI_U32 size);

#if 0
struct file* PQ_HAL_FileOpen(const char* filename, int flags, int mode);
void PQ_HAL_FileClose(struct file* filp);
int PQ_HAL_FileRead(char* buf, unsigned int len, struct file* filp);
int PQ_HAL_FileWrite(char* buf, int len, struct file* filp);
int PQ_HAL_FileSeek(loff_t offset, int origin, struct file* filp);
int PQ_HAL_FileTell(struct file* filp);
HI_U32 PQ_HAL_GetSysTime(HI_VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* End of #ifndef __PQ_HAL_COMM_H__ */
