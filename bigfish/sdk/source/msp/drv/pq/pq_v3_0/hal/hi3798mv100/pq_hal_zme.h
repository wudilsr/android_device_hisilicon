#ifndef __VDP_DRIVER_WBC_H__
#define __VDP_DRIVER_WBC_H__

#include "hi_type.h"
#include "pq_hal_comm.h"
#include "pq_mng_zme.h"

#include "hi_drv_video.h"

#define VID_OFFSET     0x800
#define WBC_OFFSET     0x400

typedef enum tagVDP_LAYER_WBC_E
{
    VDP_LAYER_WBC_HD0  = 0,
    VDP_LAYER_WBC_GP0  = 1,
    VDP_LAYER_WBC_G0   = 2,
    VDP_LAYER_WBC_G4   = 3,
    VDP_LAYER_WBC_ME   = 4,
    VDP_LAYER_WBC_FI   = 5,
    VDP_LAYER_WBC_BMP  = 6,

    VDP_LAYER_WBC_BUTT
} VDP_LAYER_WBC_E;

typedef enum
{
    VDP_ZME_MODE_HOR = 0,
    VDP_ZME_MODE_VER    ,

    VDP_ZME_MODE_HORL   ,
    VDP_ZME_MODE_HORC   ,
    VDP_ZME_MODE_VERL   ,
    VDP_ZME_MODE_VERC   ,

    VDP_ZME_MODE_ALPHA  ,
    VDP_ZME_MODE_ALPHAV ,
    VDP_ZME_MODE_VERT   ,
    VDP_ZME_MODE_VERB   ,

    VDP_ZME_MODE_ALL    ,
    VDP_ZME_MODE_NONL   ,
    
    VDP_ZME_MODE_BUTT
} VDP_ZME_MODE_E;

typedef enum tagVDP_WBC_PARA_E
{
    VDP_WBC_PARA_ZME_HORL = 0  ,
    VDP_WBC_PARA_ZME_HORC      ,
    VDP_WBC_PARA_ZME_VERL      ,
    VDP_WBC_PARA_ZME_VERC      ,

    VDP_WBC_GTI_PARA_ZME_HORL  ,
    VDP_WBC_GTI_PARA_ZME_HORC  ,
    VDP_WBC_GTI_PARA_ZME_VERL  ,
    VDP_WBC_GTI_PARA_ZME_VERC  ,

    VDP_WBC_PARA_ZME_HOR       ,
    VDP_WBC_PARA_ZME_VER       ,

    VDP_WBC_PARA_BUTT
} VDP_WBC_PARA_E;

typedef enum
{
    VDP_SR_ZME_MODE_HOR = 0,
    VDP_SR_ZME_MODE_VER    ,

    VDP_SR_ZME_MODE_HORL   ,
    VDP_SR_ZME_MODE_HORC   ,
    VDP_SR_ZME_MODE_VERL   ,
    VDP_SR_ZME_MODE_VERC   ,

    VDP_SR_ZME_MODE_BUTT
} VDP_SR_ZME_MODE_E;




typedef enum tagVDP_PROC_FMT_E
{
    VDP_PROC_FMT_SP_422      = 0x0,
    VDP_PROC_FMT_SP_420      = 0x1,
    VDP_PROC_FMT_SP_444      = 0x2,//plannar,in YUV color domain
    VDP_PROC_FMT_RGB_888     = 0x3,//package,in RGB color domain
    VDP_PROC_FMT_RGB_444     = 0x4,//plannar,in RGB color domain

    VDP_PROC_FMT_BUTT
} VDP_PROC_FMT_E;

typedef enum tagVDP_VID_PARA_E
{
    VDP_VID_PARA_ZME_HORL = 0,
    VDP_VID_PARA_ZME_HORC    ,
    VDP_VID_PARA_ZME_VERL    ,
    VDP_VID_PARA_ZME_VERC    ,

    VDP_VID_PARA_ZME_HOR     ,
    VDP_VID_PARA_ZME_VER     ,

    VDP_VID_PARA_BUTT
} VDP_VID_PARA_E;

typedef enum tagVDP_ZME_LAYER_E
{
    VDP_ZME_LAYER_V0 = 0,
    VDP_ZME_LAYER_V1    ,
    VDP_ZME_LAYER_V2    ,
    VDP_ZME_LAYER_V3    ,
    VDP_ZME_LAYER_V4    ,
    VDP_ZME_LAYER_WBC0  ,
    VDP_ZME_LAYER_SR    ,

    VDP_ZME_LAYER_BUTT
} VDP_ZME_LAYER_E;


typedef enum hiVPSS_REG_PORT_E
{
    VPSS_REG_HD = 0 , /* HD */
    VPSS_REG_SD     , /* SD */
    VPSS_REG_STR    , /* STR */
    VPSS_REG_HSC    , /* HScaler */
    
    VPSS_REG_BUTT
} VPSS_REG_PORT_E;

typedef enum
{
    REG_ZME_MODE_HOR = 0 ,
    REG_ZME_MODE_VER     ,

    REG_ZME_MODE_HORL    ,
    REG_ZME_MODE_HORC    ,
    REG_ZME_MODE_VERL    ,
    REG_ZME_MODE_VERC    ,

    REG_ZME_MODE_ALL     ,
    REG_ZME_MODE_NONL    ,
    
    REG_ZME_MODE_BUTT
} REG_ZME_MODE_E;

#if 0
HI_VOID VDP_VID_SetZmeEnable2(HI_U32 u32Data, HI_U32 u32bEnable);
HI_VOID VDP_VID_SetZmePhaseH(HI_U32 u32Data, HI_S32 s32PhaseL, HI_S32 s32PhaseC);
HI_VOID VDP_VID_SetZmePhaseV(HI_U32 u32Data, HI_S32 s32PhaseL, HI_S32 s32PhaseC);
HI_VOID VDP_VID_SetZmePhaseVB(HI_U32 u32Data, HI_S32 s32PhaseL, HI_S32 s32PhaseC);
HI_VOID VDP_VID_SetZmeFirEnable2(HI_U32 u32Data, HI_U32 u32bEnableHl, HI_U32 u32bEnableHc, HI_U32 u32bEnableVl, HI_U32 u32bEnableVc);
HI_VOID VDP_VID_SetZmeMidEnable2(HI_U32 u32Data, HI_U32 u32bEnable);
HI_VOID VDP_VID_SetZmeVchTap(HI_U32 u32Data, HI_U32 u32VscTap);
HI_VOID VDP_VID_SetZmeHorRatio(HI_U32 u32Data, HI_U32 u32Ratio);
HI_VOID VDP_VID_SetZmeVerRatio(HI_U32 u32Data, HI_U32 u32Ratio);
HI_VOID VDP_VID_SetZmeHfirOrder(HI_U32 u32Data, HI_U32 u32HfirOrder);
HI_VOID VDP_VID_SetZmeCoefAddr(HI_U32 u32Data, HI_U32 u32Mode, HI_U32 u32LAddr, HI_U32 u32CAddr);
HI_VOID VDP_VID_SetParaUpd       (HI_U32 u32Data, VDP_VID_PARA_E enMode);
HI_VOID VDP_VID_SetZmeInFmt(HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt);
HI_VOID VDP_VID_SetZmeOutFmt(HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt);

HI_VOID VDP_WBC_SetZmePhaseH(VDP_LAYER_WBC_E enLayer, HI_S32 s32PhaseL, HI_S32 s32PhaseC);
HI_VOID VDP_WBC_SetZmePhaseV(VDP_LAYER_WBC_E enLayer, HI_S32 s32PhaseL, HI_S32 s32PhaseC);
HI_VOID VDP_WBC_SetZmePhaseV(VDP_LAYER_WBC_E enLayer, HI_S32 s32PhaseL, HI_S32 s32PhaseC);
HI_VOID VDP_WBC_SetZmeHorRatio(VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio);
HI_VOID VDP_WBC_SetZmeVerRatio(VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio);
HI_VOID VDP_WBC_SetZmeEnable(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable, HI_U32 u32firMode);
HI_VOID VDP_WBC_SetMidEnable(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 bEnable);
HI_VOID VDP_WBC_SetZmeHfirOrder(VDP_LAYER_WBC_E enLayer, HI_U32 u32HfirOrder);
HI_VOID VDP_WBC_SetZmeVerTap(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 u32VerTap);
HI_VOID VDP_WBC_SetZmeCoefAddr(VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E u32Mode, HI_U32 u32Addr, HI_U32 u32CAddr);
HI_VOID VDP_WBC_SetParaUpd (VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E enMode);
HI_VOID VDP_WBC_SetZmeInFmt(VDP_LAYER_WBC_E enLayer, VDP_PROC_FMT_E u32Fmt);

HI_VOID VDP_SR_SetZmeHorRatio (HI_U32 u32Data, HI_U32 u32Ratio);
HI_VOID VDP_SR_SetZmeVerRatio (HI_U32 u32Data, HI_U32 u32Ratio);
HI_VOID VDP_SR_SetZmeEnable(HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable, HI_U32 u32firMode);
HI_VOID VDP_SR_SetZmePhase (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_S32 s32Phase);

HI_VOID VDP_SR_SetZmeFirEnable (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID VDP_SR_SetZmeMidEnable (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID VDP_SR_SetZmeInFmt (HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt);
HI_VOID VDP_SR_SetZmeOutFmt (HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt);
HI_VOID VDP_SR_SetHfirOrder(HI_U32 u32Data, HI_U32 u32HfirOrder);
HI_VOID VDP_SR_SetZmeVerTap(HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32VerTap);
HI_VOID VDP_SR_SetZmeCoefAddr (HI_U32 u32Data, VDP_SR_ZME_MODE_E enMode, HI_U32 u32Addr);
HI_VOID VDP_SR_SetParaUpd (HI_U32 u32Data, VDP_SR_ZME_MODE_E enMode);
HI_VOID VDP_SR_SetZmeCoef (HI_U32 u32Data, VDP_SR_ZME_MODE_E enMode, VDP_SR_ZME_COEF_S* pstVdpSrZmeCoef);


HI_S32 VPSS_REG_SetZmeEnable(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_BOOL bEnable);
HI_S32 VPSS_REG_SetZmeInSize(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_U32 u32Height, HI_U32 u32Width);
HI_S32 VPSS_REG_SetZmeOutSize(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_U32 u32Height, HI_U32 u32Width);
HI_S32 VPSS_REG_SetZmeFirEnable(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort,S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_BOOL bEnable);
HI_S32 VPSS_REG_SetZmeMidEnable(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort,S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_BOOL bEnable);
HI_S32 VPSS_REG_SetZmePhase(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort,S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_S32 s32Phase);
HI_S32 VPSS_REG_SetZmeRatio(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort,S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_U32 u32Ratio);
HI_S32 VPSS_REG_SetZmeHfirOrder(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort,S_CAS_REGS_TYPE *pstReg, HI_BOOL bVfirst);
HI_S32 VPSS_REG_SetZmeInFmt(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort,S_CAS_REGS_TYPE *pstReg, HI_DRV_PIX_FORMAT_E eFormat);
HI_S32 VPSS_REG_SetZmeOutFmt(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort,S_CAS_REGS_TYPE *pstReg, HI_DRV_PIX_FORMAT_E eFormat);
HI_S32 VPSS_REG_SetZmeCoefAddr(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort,S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_U32 u32Addr);
#endif

HI_VOID ALG_VZmeVdpRegCfg(HI_U32 u32LayerId, ALG_VZME_RTL_PARA_S* pstZmeRtlPara, HI_BOOL bFirEnable);
HI_VOID ALG_VZmeVdpWbcRegCfg(HI_U32 u32LayerId, ALG_VZME_RTL_PARA_S* pstZmeRtlPara, HI_BOOL bFirEnable);
HI_VOID ALG_VZmeVdpSRRegCfg(HI_U32 u32LayerId, ALG_VZME_RTL_PARA_S* pstZmeRtlPara, HI_BOOL bFirEnable);
HI_VOID ALG_VZmeVpssRegCfg(HI_U32 u32LayerId, S_CAS_REGS_TYPE *pstReg, ALG_VZME_RTL_PARA_S* pstZmeRtlPara, HI_BOOL bFirEnable);


#endif
