
/******************************************************************************
  Copyright (C), 2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : pq_mng_ua.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2014/4/1
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "pq_mng_ua.h"
#include "pq_mng_zme.h"
#include "pq_hal_zme.h"
#include "hi_type.h"
#include "hi_drv_video.h"
#include "hi_drv_disp.h"
#include "pq_hal_comm.h"
#include "hi_drv_mmz.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_BOOL g_bUAInitFlag     = HI_FALSE;
HI_BOOL g_bUAVdpInitFlag  = HI_FALSE;
HI_BOOL g_bUAVpssInitFlag = HI_FALSE;
ALG_VZME_MEM_S g_stVZMEVdpInstance;
ALG_VZME_MEM_S g_stVZMEVpssInstance;

static HI_U32 PQ_TRACE_RANGE = HI_LOG_LEVEL_ERROR;
static HI_S32 PQ_MNG_InitVdpUA(HI_VOID);
static HI_S32 PQ_MNG_DeInitVdpUA(HI_VOID);
static HI_S32 PQ_MNG_InitVpssUA(HI_VOID);
static HI_S32 PQ_MNG_DeInitVpssUA(HI_VOID);


typedef  HI_VOID (*FN_Zme_CoefCalculate)(ALG_VZME_MEM_S* pstMem, ALG_VZME_DRV_PARA_S* pstZmeDrvPara, ALG_VZME_RTL_PARA_S* pstZmeRtlPara);
typedef  HI_VOID (*FN_Zme_VdpRegCfg)(HI_U32 u32LayerId, ALG_VZME_RTL_PARA_S* pstZmeRtlPara, HI_BOOL bFirEnable);
typedef  HI_VOID (*FN_Zme_VpssRegCfg)(HI_U32 u32LayerId, S_CAS_REGS_TYPE* pstReg, ALG_VZME_RTL_PARA_S* pstZmeRtlPara, HI_BOOL  bFirEnable);

typedef struct
{
    FN_Zme_CoefCalculate   pfnZme_CoefCalculate;
    FN_Zme_VdpRegCfg       pfnZme_VdpRegCfg;
} ZME_VDP_FUNC_S;

typedef struct
{
    FN_Zme_CoefCalculate   pfnZme_CoefCalculate;
    FN_Zme_VpssRegCfg      pfnZme_VpssRegCfg;
} ZME_VPSS_FUNC_S;

typedef struct hiPQ_MMZ_BUF_S
{
    HI_U32 u32StartVirAddr;
    HI_U32 u32StartPhyAddr;
    HI_U32 u32Size;
} PQ_MMZ_BUF_S;

static HI_S32 PQ_OS_MMZ_AllocAndMap(const char* bufname, char* zone_name, HI_U32 size, int align, PQ_MMZ_BUF_S* pstMBuf)
{
    MMZ_BUFFER_S stMMZ;
    HI_S32 nRet;

    nRet = HI_DRV_MMZ_AllocAndMap(bufname, zone_name, size, align, &stMMZ);
    if (!nRet)
    {
        pstMBuf->u32StartPhyAddr = stMMZ.u32StartPhyAddr;
        pstMBuf->u32StartVirAddr = stMMZ.u32StartVirAddr;
        pstMBuf->u32Size = stMMZ.u32Size;
    }

    return nRet;
}

static HI_VOID PQ_OS_MMZ_UnmapAndRelease(PQ_MMZ_BUF_S* pstMBuf)
{
    MMZ_BUFFER_S stMMZ;

    stMMZ.u32StartPhyAddr = pstMBuf->u32StartPhyAddr;
    stMMZ.u32StartVirAddr = pstMBuf->u32StartVirAddr;
    stMMZ.u32Size = pstMBuf->u32Size;

    HI_DRV_MMZ_UnmapAndRelease(&stMMZ);

    return;
}

HI_S32 PQ_MNG_InitUA(HI_VOID)
{
    if (g_bUAInitFlag)
    {
        PQ_TRACE(HI_LOG_LEVEL_INFO, PQ_TRACE_RANGE, "FUNC(%s) inited!\n", __FUNCTION__);
        return HI_SUCCESS;
    }

    (HI_VOID)PQ_MNG_InitVpssUA();
    (HI_VOID)PQ_MNG_InitVdpUA();

    g_bUAInitFlag = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_InitVdpUA(HI_VOID)
{
    HI_S32 nRet;

    if (g_bUAVdpInitFlag)
    {
        PQ_TRACE(HI_LOG_LEVEL_INFO, PQ_TRACE_RANGE, "FUNC(%s) inited!\n", __FUNCTION__);
        return HI_SUCCESS;
    }

    nRet = PQ_OS_MMZ_AllocAndMap("PQ_VDPZmeCoef", HI_NULL, (288 + 240 + 192) * 7, 16, (PQ_MMZ_BUF_S*)&g_stVZMEVdpInstance.stMBuf);
    if (nRet != 0)
    {
        HI_PRINT("Get PQ_Zme failed\n");
        return HI_FAILURE;
    }

    /*load Vdp zme coef.*/
    nRet = ALG_VZmeVdpComnInit(&g_stVZMEVdpInstance);
    if (nRet)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "ALG_VZmeVdpComnInit failed!\n");
        PQ_OS_MMZ_UnmapAndRelease((PQ_MMZ_BUF_S*)&g_stVZMEVdpInstance.stMBuf);
        g_stVZMEVdpInstance.stMBuf.u32StartVirAddr = 0;
        return HI_FAILURE;
    }

    g_bUAVdpInitFlag = HI_TRUE;

    return HI_SUCCESS;
}


static HI_S32 PQ_MNG_InitVpssUA(HI_VOID)
{
    ALG_MMZ_BUF_S* pstMBuf;
    HI_S32 s32Ret;

    if (g_bUAVpssInitFlag)
    {
        PQ_TRACE(HI_LOG_LEVEL_INFO, PQ_TRACE_RANGE, "FUNC(%s) inited!\n", __FUNCTION__);
        return HI_SUCCESS;
    }

    //apply memory for zme coefficient, and get the address.
    pstMBuf = &(g_stVZMEVpssInstance.stMBuf);

    s32Ret = PQ_OS_MMZ_AllocAndMap("PQ_VpssZmeCoef", HI_NULL, (464 + 400 + 336 + 336) * 7, 0, (PQ_MMZ_BUF_S*)pstMBuf);
    if (s32Ret != HI_SUCCESS)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "PQ_OS_MMZ_AllocAndMap failed!\n");
        return HI_FAILURE;
    }
    /*load Vpss zme coef.*/
    s32Ret = ALG_VZmeVpssComnInit(&g_stVZMEVpssInstance);
    if (s32Ret)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "ALG_VZmeVPssComnInit failed!\n");
        PQ_OS_MMZ_UnmapAndRelease((PQ_MMZ_BUF_S*)pstMBuf);
        //g_stVZMEVpssInstance.stMBuf.u32StartVirAddr = 0;
        return HI_FAILURE;
    }

    g_bUAVpssInitFlag = HI_TRUE;
    return HI_SUCCESS;
}


HI_S32 PQ_MNG_DeInitUA(HI_VOID)
{
    if (g_bUAInitFlag)
    {
        (HI_VOID)PQ_MNG_DeInitVpssUA();
        (HI_VOID)PQ_MNG_DeInitVdpUA();
        
        g_bUAInitFlag = HI_FALSE;
    }

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_DeInitVdpUA(HI_VOID)
{
    if (g_bUAVdpInitFlag)
    {
        ALG_VZmeVdpComnDeInit(&g_stVZMEVdpInstance);
        //release zme coefficient memory
        if (g_stVZMEVdpInstance.stMBuf.u32StartVirAddr != 0)
        {
            PQ_OS_MMZ_UnmapAndRelease((PQ_MMZ_BUF_S*)&g_stVZMEVdpInstance.stMBuf);
            g_stVZMEVdpInstance.stMBuf.u32StartVirAddr = 0;
        }

        g_bUAVdpInitFlag = HI_FALSE;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_MNG_DeInitVpssUA(HI_VOID)
{
    if (g_bUAVpssInitFlag)
    {
        ALG_VZmeVpssComnDeInit(&g_stVZMEVpssInstance);
        //release zme coefficient memory
        if (g_stVZMEVpssInstance.stMBuf.u32StartVirAddr != 0)
        {
            PQ_OS_MMZ_UnmapAndRelease((PQ_MMZ_BUF_S*)&g_stVZMEVpssInstance.stMBuf);
            g_stVZMEVpssInstance.stMBuf.u32StartVirAddr = 0;
        }

        g_bUAVpssInitFlag = HI_FALSE;
    }
    return HI_SUCCESS;
}

ZME_VDP_FUNC_S stZmeVdpFunc[HI_PQ_DISP_LAYER_ZME_BUTT]  =
{
#if defined(CHIP_TYPE_hi3719mv100) || defined(CHIP_TYPE_hi3718mv100) || defined(CHIP_TYPE_hi3716cv200) || defined(CHIP_TYPE_hi3716mv400) || defined(CHIP_TYPE_hi3719cv100) || defined(CHIP_TYPE_hi3718cv100) || defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
    {ALG_VZmeVdpSQSetSptAddr, ALG_VZmeVdpRegCfg},    //V0
    {ALG_VZmeVdpSQSetSptAddr, ALG_VZmeVdpRegCfg},    //V1
    {ALG_VZmeVdpSQSetSptAddr, ALG_VZmeVdpRegCfg},    //V2
    {ALG_VZmeVdpSQSetSptAddr, ALG_VZmeVdpRegCfg},    //V3
    {ALG_VZmeVdpSQSetSptAddr, ALG_VZmeVdpRegCfg},    //V4
    {ALG_VZmeVdpSQSetSptAddr, ALG_VZmeVdpWbcRegCfg}, //WBC0
  //{ALG_VZmeVdpHQSetSptAddr, ALG_VZmeVdpSRRegCfg},  //SR
    {ALG_VZmeSRSetAddr, ALG_VZmeVdpSRRegCfg},        //SR
    
#endif


#if defined(CHIP_TYPE_hi3798cv100) || defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv200_a)
    {ALG_VZmeVdpHQSetSptAddr, ALG_VZmeVdpRegCfg},   //V0
    {ALG_VZmeVdpHQSetSptAddr, ALG_VZmeVdpRegCfg},   //V1
    {ALG_VZmeVdpHQSetSptAddr, ALG_VZmeVdpRegCfg},   //V2
    {ALG_VZmeVdpHQSetSptAddr, ALG_VZmeVdpRegCfg},   //V3
    {ALG_VZmeVdpHQSetSptAddr, ALG_VZmeVdpRegCfg},   //V4
    {ALG_VZmeVdpHQSet, ALG_VZmeVdpWbcRegCfg},       //WBC0
  //{ALG_VZmeVdpHQSetSptAddr, ALG_VZmeVdpSRRegCfg}, //SR
    {ALG_VZmeSRSetAddr, ALG_VZmeVdpSRRegCfg},       //SR
#endif

};

ZME_VPSS_FUNC_S stZmeVpssFunc[HI_PQ_VPSS_LAYER_ZME_BUTT]  =
{
#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
    {ALG_VZmeVpssHQSetSptAddr, ALG_VZmeVpssRegCfg}, //PORT0
    {ALG_VZmeVpssHQSetSptAddr, ALG_VZmeVpssRegCfg}, //PORT1
    {ALG_VZmeVpssHQSetSptAddr, ALG_VZmeVpssRegCfg}, //PORT2
    {ALG_VZmeVpssHQSetSptAddr, ALG_VZmeVpssRegCfg}, //HSCL

#elif defined(CHIP_TYPE_hi3798cv200_a)
    {ALG_VZmeVpssSetSptAddr, ALG_VZmeVpssRegCfg}, //PORT0
    {ALG_VZmeVpssSetSptAddr, ALG_VZmeVpssRegCfg}, //PORT1
    {ALG_VZmeVpssSetSptAddr, ALG_VZmeVpssRegCfg}, //PORT2
    {HI_NULL, HI_NULL},                           //HSCL

#else
    {HI_NULL, HI_NULL},          //PORT0
    {HI_NULL, HI_NULL},          //PORT1
    {HI_NULL, HI_NULL},          //PORT2
    {HI_NULL, HI_NULL},          //HSCL
#endif

};

HI_VOID PQ_MNG_SetVdpZme(HI_U32 u32LayerId,
                         ALG_VZME_DRV_PARA_S* pstZmeDrvPara,
                         HI_BOOL  bFirEnable)
{
    ALG_VZME_RTL_PARA_S stZmeRtlParam;

    memset((void*)&stZmeRtlParam, 0, sizeof(ALG_VZME_RTL_PARA_S));
    stZmeVdpFunc[u32LayerId].pfnZme_CoefCalculate(&g_stVZMEVdpInstance, pstZmeDrvPara, &stZmeRtlParam);
    stZmeVdpFunc[u32LayerId].pfnZme_VdpRegCfg(u32LayerId, &stZmeRtlParam, bFirEnable);

    return;
}

HI_VOID PQ_MNG_SetVpssZme(HI_U32 u32LayerId,
                          S_CAS_REGS_TYPE* pstReg,
                          ALG_VZME_DRV_PARA_S* pstZmeDrvPara,
                          HI_BOOL  bFirEnable)
{
    ALG_VZME_RTL_PARA_S stZmeRtlParam;

    memset((void*)&stZmeRtlParam, 0, sizeof(ALG_VZME_RTL_PARA_S));
    stZmeVpssFunc[u32LayerId].pfnZme_CoefCalculate(&g_stVZMEVpssInstance, pstZmeDrvPara, &stZmeRtlParam);
    stZmeVpssFunc[u32LayerId].pfnZme_VpssRegCfg(u32LayerId, pstReg, &stZmeRtlParam, bFirEnable);

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
