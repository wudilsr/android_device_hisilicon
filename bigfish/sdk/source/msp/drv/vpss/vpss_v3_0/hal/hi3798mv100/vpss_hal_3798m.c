/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCDadN5jJKSuVyxmmaCmKFU6eJEbB2fyHF9weu4/jer/hxLHb+S1e
E0zVg4C3NiZh4b+GnwjAHj8JYHgZh/mRmQlUl/yvyRM2bdt8FEOq9KEDxoWAhM+suFVQjq7m
HyK2mcDeKLSqkFi+oVjmazvYwNqQ54XDJ8U6iBRI3pzywzm2anQSs5REp40sZPOMc2bFp4IH
iAwDF3dmvpHtgUhBj30v1N1mbm4y5OJtEHSmv0JIg+vmFUjitUXZmX8xInxNMQ==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/








#include "vpss_hal_3798m.h"
#include "linux/kthread.h"
#include "vpss_common.h"

#include <asm/barrier.h>
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#if 1
VPSS_HAL_CTX_S  stHalCtx[VPSS_IP_BUTT] = 
{
    {
        .bInit = HI_FALSE,
        .bClockEn = HI_FALSE,
        .u32LogicVersion = HAL_VERSION_3798M,
        .u32BaseRegPhy   = VPSS0_BASE_ADDR,
        .u32BaseRegVir   = 0,
    },
    
    {
        .bInit = HI_FALSE,
        .bClockEn = HI_FALSE,
        .u32LogicVersion = HAL_VERSION_3798M,
        .u32BaseRegPhy   = VPSS1_BASE_ADDR,
        .u32BaseRegVir   = 0,
    }
};
#endif

VPSS_REG_PORT_E VPSS_HAL_AllocPortId(VPSS_HAL_PORT_INFO_S *pstHalPort,
    HI_BOOL abPortUsed[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER])
{
    if (HI_FALSE == abPortUsed[VPSS_REG_HD])
    {
         abPortUsed[VPSS_REG_HD] = HI_TRUE;
         return VPSS_REG_HD;
    }

    if (HI_FALSE == abPortUsed[VPSS_REG_STR])
    {
         abPortUsed[VPSS_REG_STR] = HI_TRUE;
         return VPSS_REG_STR;
    }
#if 0
    if (HI_FALSE == abPortUsed[VPSS_REG_SD])
    {
         abPortUsed[VPSS_REG_SD] = HI_TRUE;
         return VPSS_REG_SD;
    }
#endif

    return VPSS_REG_BUTT;
}

ZME_FORMAT_E VPSS_HAL_GetZmeFmt(HI_DRV_PIX_FORMAT_E enFormat)
{
    ZME_FORMAT_E enZmeFmt = HI_PQ_ALG_PIX_FORMAT_SP420;
    
    switch(enFormat)
    {
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV21_CMP:
        case HI_DRV_PIX_FMT_NV12_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
            enZmeFmt = HI_PQ_ALG_PIX_FORMAT_SP420;
            break;
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV61_2X1_CMP:
        case HI_DRV_PIX_FMT_NV16_2X1_CMP:
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
        case HI_DRV_PIX_FMT_UYVY:  
        //case HI_DRV_PIX_FMT_ARGB8888:   //sp420->sp422->csc->rgb
        //case HI_DRV_PIX_FMT_ABGR8888:
        //case HI_DRV_PIX_FMT_KBGR8888:
            enZmeFmt = HI_PQ_ALG_PIX_FORMAT_SP422;
            break;
        default:
            VPSS_FATAL("REG ERROR format %d\n",enFormat);
    }

    return enZmeFmt;
}

HI_S32 VPSS_HAL_GetZmeCoef(VPSS_IP_E enIP,VPSS_HAL_ZME_PARAM_S *pstZmeParam, 
    HI_U32 *pu32YH, HI_U32 *pu32CH, HI_U32 *pu32YV, HI_U32 *pu32CV)
{
    HI_U32 i;
    HI_S32 s32Ret;
    HI_PQ_SCALER_S stScalerH, stScalerV;

    /* 找一个可用的系数地址 */
    for (i=0; i<VPSS_ZME_COEF_NUM; i++)
    {
        if (HI_FALSE == stHalCtx[enIP].abUsed[i])
        {
            stHalCtx[enIP].abUsed[i] = HI_TRUE;
            break;
        }
    }

    if(i>=VPSS_ZME_COEF_NUM)
    {
        VPSS_FATAL("No Enough Zme Coef Phy\n");
        return HI_FAILURE;
    }

    stScalerH.bHorizontal = HI_TRUE;
	stScalerH.bYUV        = pstZmeParam->bYUV;
    stScalerH.u32YRatio   = pstZmeParam->u32YHRatio;
    stScalerH.u32CRatio   = pstZmeParam->u32CHRatio;
    stScalerH.enInFmt     = pstZmeParam->enInFmt;
    stScalerH.enOutFmt    = pstZmeParam->enOutFmt;

    s32Ret = DRV_PQ_GetVpssScalerCoef(&stScalerH, 
                (HI_VOID *)stHalCtx[enIP].au32ZmeCoefVir[i][0],
                (HI_VOID*)stHalCtx[enIP].au32ZmeCoefVir[i][1]);
    if(s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("H Coef Get Failed\n");
        return HI_FAILURE;
    }

    stScalerV.bHorizontal = HI_FALSE;
	stScalerV.bYUV        = pstZmeParam->bYUV;
    stScalerV.u32YRatio   = pstZmeParam->u32YVRatio;
    stScalerV.u32CRatio   = pstZmeParam->u32CVRatio;
    stScalerV.enInFmt     = pstZmeParam->enInFmt;
    stScalerV.enOutFmt    = pstZmeParam->enOutFmt;

    s32Ret = DRV_PQ_GetVpssScalerCoef(&stScalerV, 
                (HI_VOID *)stHalCtx[enIP].au32ZmeCoefVir[i][2],
                (HI_VOID*)stHalCtx[enIP].au32ZmeCoefVir[i][3]);
    if(s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("V Coef Get Failed\n");
        return HI_FAILURE;
    }

    *pu32YH = stHalCtx[enIP].au32ZmeCoefPhy[i][0];
    *pu32CH = stHalCtx[enIP].au32ZmeCoefPhy[i][1];
    *pu32YV = stHalCtx[enIP].au32ZmeCoefPhy[i][2];
    *pu32CV = stHalCtx[enIP].au32ZmeCoefPhy[i][3];

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetDnrCfg(VPSS_IP_E enIP,HI_U32 u32AppVir, 
                            VPSS_HAL_INFO_S *pstHalInfo)
{
    VPSS_HAL_FRAME_S *pstInInfo; 
    HI_BOOL bdbEnHort;
    HI_BOOL bdbEnVert;
    HI_BOOL bdrEn;
    HI_BOOL bdbEn;
    
    pstInInfo = &(pstHalInfo->stInInfo);
    
    if(pstInInfo->u32Height <= 576 && pstInInfo->u32Width <= 720)
    {
        if (((pstInInfo->enFormat != HI_DRV_PIX_FMT_NV21)
                && (pstInInfo->enFormat != HI_DRV_PIX_FMT_NV12)
                && (pstInInfo->enFormat != HI_DRV_PIX_FMT_NV21_TILE)
                && (pstInInfo->enFormat != HI_DRV_PIX_FMT_NV12_TILE)
                && (pstInInfo->enFormat != HI_DRV_PIX_FMT_NV12_TILE_CMP)
                && (pstInInfo->enFormat != HI_DRV_PIX_FMT_NV21_TILE_CMP))
            //||pstInst->stProcCtrl.bUseCropRect == HI_TRUE 
            //|| pstAlgCfg->stAuTunnelCfg.stDeiCfg.bDei == HI_FALSE
            //|| ((pstInst->stProcCtrl.bUseCropRect == HI_FALSE)
            //    && (pstInst->stProcCtrl.stInRect.s32Height != 0 
            //        || pstInst->stProcCtrl.stInRect.s32Width != 0
            //        || pstInst->stProcCtrl.stInRect.s32X != 0
            //        || pstInst->stProcCtrl.stInRect.s32Y != 0))
            || ((pstInInfo->u32Height & 0x0000000f) != 0x0)
            || ((pstInInfo->u32Width  & 0x0000000f) != 0x0)
			//|| pstInst->u32Rwzb > 0
			)
        {
            bdbEnHort = 0;
            bdbEnVert = 0;
            bdrEn = 0;
            bdbEn = 0;
        }
        else
        {
            bdbEnHort = 1;
            bdbEnVert = 1;
            bdrEn = 1;
            bdbEn = 1;
        }
    }
    else
    {
        bdbEnHort = 0;
        bdbEnVert = 0;
        bdrEn = 0;
        bdbEn = 0;
    }

    VPSS_REG_SetDREn(u32AppVir, bdrEn);
    VPSS_REG_SetDBEn(u32AppVir,bdbEn);
    
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetHSCLCfg(VPSS_IP_E enIP,HI_U32 u32AppVir, 
                            VPSS_HAL_INFO_S *pstHalInfo)
{
    HI_PQ_ZME_PARA_IN_S stZmeDrvPara;
    HI_PQ_ZME_PARA_IN_S *pstZmeDrvPara;
    VPSS_HAL_FRAME_S *pstInInfo; 

    pstInInfo = &(pstHalInfo->stInInfo);
    
    pstZmeDrvPara  = &(stZmeDrvPara);
    
    memset(pstZmeDrvPara,0,sizeof(HI_PQ_ZME_PARA_IN_S));

    if (pstInInfo->bProgressive != HI_TRUE)
    {
        pstZmeDrvPara->bZmeFrmFmtIn = 1;
    }
    else
    {
        if (pstInInfo->enFieldMode == HI_DRV_FIELD_ALL)
        {
            pstZmeDrvPara->bZmeFrmFmtIn = 1;
        }
        else
        {
            pstZmeDrvPara->bZmeFrmFmtIn = 0;
        }
    }
    pstZmeDrvPara->bZmeFrmFmtOut = 1;

    if (pstInInfo->enFieldMode == HI_DRV_FIELD_TOP)
    {
        pstZmeDrvPara->bZmeBFIn = 0;
    }
    else if (pstInInfo->enFieldMode == HI_DRV_FIELD_BOTTOM)
    {
        pstZmeDrvPara->bZmeBFIn = 1;
    }
    else
    {
        pstZmeDrvPara->bZmeBFIn = 0;
    }
    pstZmeDrvPara->bZmeBFOut = 0;

    if (pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV61
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV16
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_YUV422_1X2
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_YUV420p
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_YUV410p
        )
    {
        pstZmeDrvPara->u8ZmeYCFmtIn = 0;//PQ_ALG_ZME_PIX_FORMAT_SP420;
    }
    else
    {
        pstZmeDrvPara->u8ZmeYCFmtIn = 1;//PQ_ALG_ZME_PIX_FORMAT_SP422;
    }
    
    pstZmeDrvPara->u8ZmeYCFmtOut = 0;//PQ_ALG_ZME_PIX_FORMAT_SP420;
    
    pstZmeDrvPara->u32ZmeFrmHIn = pstInInfo->u32Height;
    pstZmeDrvPara->u32ZmeFrmWIn = pstInInfo->u32Width;
    
    pstZmeDrvPara->u32ZmeFrmHOut = pstInInfo->u32Height;

    if (pstInInfo->u32Width % 4 != 0)
    {
        VPSS_ERROR("Invalid image width %d\n",pstInInfo->u32Width);
    }
    
    //pstZmeDrvPara->u32ZmeFrmWOut = pstInInfo->u32Width/2;
    pstZmeDrvPara->u32ZmeFrmWOut = 1920;
    
    pstZmeDrvPara->stOriRect.s32X = 0;
    pstZmeDrvPara->stOriRect.s32Y = 0;
    pstZmeDrvPara->stOriRect.s32Width = pstInInfo->u32Width;
    pstZmeDrvPara->stOriRect.s32Height = pstInInfo->u32Height;
    pstZmeDrvPara->u32InRate = 25000;     
    pstZmeDrvPara->u32OutRate = 25000;
    pstZmeDrvPara->bDispProgressive = HI_TRUE;
    pstZmeDrvPara->u32Fidelity = 0; 

    DRV_PQ_SetVpssZme(HI_PQ_VPSS_HSCL_LAYER_ZME,
                      (VPSS_REG_S*)u32AppVir,
                      pstZmeDrvPara,
                      HI_TRUE);
                
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetZmeCfg(VPSS_IP_E enIP,HI_U32 u32AppVir, 
                            VPSS_HAL_INFO_S *pstHalInfo,
                            VPSS_REG_PORT_E enPort,
                            HI_U32 u32PortCnt)
{
    VPSS_HAL_PORT_INFO_S *pstHalPort = HI_NULL;
    HI_PQ_ZME_PARA_IN_S stZmeDrvPara;
    HI_PQ_ZME_PARA_IN_S *pstZmeDrvPara;
    VPSS_HAL_FRAME_S *pstInInfo; 
    HI_PQ_VPSS_ZME_LAYER_E enPqPort = HI_PQ_VPSS_LAYER_ZME_BUTT;

	if (VPSS_REG_BUTT <= enPort)
	{
		VPSS_ERROR("Invalid enPort %d\n",enPort);	
		return HI_FAILURE;
	}
    
    pstHalPort = &pstHalInfo->astPortInfo[u32PortCnt];

    pstInInfo = &(pstHalInfo->stInInfo);
    
    pstZmeDrvPara  = &(stZmeDrvPara);
    
    memset(pstZmeDrvPara,0,sizeof(HI_PQ_ZME_PARA_IN_S));

#if 0
    if (pstInInfo->bProgressive != HI_TRUE)
    {
        pstZmeDrvPara->bZmeFrmFmtIn = 1;
    }
    else
    {
        if (pstInInfo->enFieldMode == HI_DRV_FIELD_ALL)
        {
            pstZmeDrvPara->bZmeFrmFmtIn = 1;
        }
        else
        {
            pstZmeDrvPara->bZmeFrmFmtIn = 0;
        }
    }
#else
	pstZmeDrvPara->bZmeFrmFmtIn = 1;
#endif
    pstZmeDrvPara->bZmeFrmFmtOut = 1;

#if 0
    if (pstInInfo->enFieldMode == HI_DRV_FIELD_TOP)
    {
        pstZmeDrvPara->bZmeBFIn = 0;
    }
    else if (pstInInfo->enFieldMode == HI_DRV_FIELD_BOTTOM)
    {
        pstZmeDrvPara->bZmeBFIn = 1;
    }
    else
    {
        pstZmeDrvPara->bZmeBFIn = 0;
    }
#else
	pstZmeDrvPara->bZmeBFIn = 0;
#endif
    pstZmeDrvPara->bZmeBFOut = 0;

    if (pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV61
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV16
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_YUV422_1X2
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_YUV420p
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_YUV410p
        )
    {
        pstZmeDrvPara->u8ZmeYCFmtIn = 0;//PQ_ALG_ZME_PIX_FORMAT_SP420;
    }
    else
    {
        pstZmeDrvPara->u8ZmeYCFmtIn = 1;//PQ_ALG_ZME_PIX_FORMAT_SP422;
    }
    
    if (pstHalPort->stOutInfo.enFormat == HI_DRV_PIX_FMT_NV21
        || pstHalPort->stOutInfo.enFormat == HI_DRV_PIX_FMT_NV12
        || pstHalPort->stOutInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP
        || pstHalPort->stOutInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP)
    {
        pstZmeDrvPara->u8ZmeYCFmtOut = 0;//PQ_ALG_ZME_PIX_FORMAT_SP420;
    }
    else
    {
        pstZmeDrvPara->u8ZmeYCFmtOut = 1;//PQ_ALG_ZME_PIX_FORMAT_SP422;
    }
    
    pstZmeDrvPara->u32ZmeFrmHIn = pstInInfo->u32Height;
    pstZmeDrvPara->u32ZmeFrmWIn = pstInInfo->u32Width;

#if 0
    if (pstInInfo->bProgressive == HI_TRUE)
    {
        if (pstInInfo->enFieldMode != HI_DRV_FIELD_ALL)
        {
            pstZmeDrvPara->u32ZmeFrmHIn = pstZmeDrvPara->u32ZmeFrmHIn*2;
        }
    }
#endif
    
    pstZmeDrvPara->u32ZmeFrmHOut = pstHalPort->stVideoRect.s32Height;
    pstZmeDrvPara->u32ZmeFrmWOut = pstHalPort->stVideoRect.s32Width;
    
	#if 0
    VPSS_ERROR("IN W %d H %d  W %d H %d\n",
        pstZmeDrvPara->u32ZmeFrmWIn,
        pstZmeDrvPara->u32ZmeFrmHIn,
        pstZmeDrvPara->u32ZmeFrmWOut,
        pstZmeDrvPara->u32ZmeFrmHOut);
	#endif
	
    pstZmeDrvPara->stOriRect.s32X = 0;
    pstZmeDrvPara->stOriRect.s32Y = 0;
    pstZmeDrvPara->stOriRect.s32Width = pstInInfo->u32Width;
    pstZmeDrvPara->stOriRect.s32Height = pstInInfo->u32Height;
    pstZmeDrvPara->u32InRate = 25000;     
    pstZmeDrvPara->u32OutRate = 25000;
    pstZmeDrvPara->bDispProgressive = HI_TRUE;
    pstZmeDrvPara->u32Fidelity = 0; 

    switch(enPort)
    {
        case VPSS_REG_HD:
            enPqPort = HI_PQ_VPSS_PORT0_LAYER_ZME;
            break;
        case VPSS_REG_SD:
            enPqPort = HI_PQ_VPSS_PORT1_LAYER_ZME;
            break;
        case VPSS_REG_STR:
            enPqPort = HI_PQ_VPSS_PORT2_LAYER_ZME;
            break;
        default:
            break;
    }
    DRV_PQ_SetVpssZme(enPqPort,
                      (VPSS_REG_S*)u32AppVir,
                      pstZmeDrvPara,
                      HI_TRUE);
                
    return HI_SUCCESS;
}
/* 
*  VPSS_HAL_SetPortCfg函数应该只需要传 VPSS_HAL_PORT_INFO_S数组信息即可，
*  但由于缩放需要源格式 所以传递了VPSS_HAL_INFO_S信息，也同时为后期预缩放场景提供扩展
*/
HI_S32 VPSS_HAL_SetPortCfg(VPSS_IP_E enIP,HI_U32 u32AppVir, 
    VPSS_HAL_INFO_S *pstHalInfo)
{
    HI_U32 u32Count;
	HI_U32 u32PortAvailable = DEF_VPSS_HAL_PORT_NUM;

    HI_BOOL abPortUsed[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER]
        = {HI_FALSE, HI_FALSE, HI_FALSE};
    
    /* 先默认关闭三个硬件输出通道 */
    VPSS_REG_EnPort(u32AppVir, VPSS_REG_HD, HI_FALSE);
    VPSS_REG_EnPort(u32AppVir, VPSS_REG_STR, HI_FALSE);
    //VPSS_REG_EnPort(u32AppVir, VPSS_REG_SD,  HI_FALSE);
    VPSS_REG_SetFidelity(u32AppVir, HI_FALSE);    
    
    for (u32Count = 0; 
			u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER && u32PortAvailable > 0;
			u32Count ++)
    {
        VPSS_HAL_PORT_INFO_S *pstHalPort = HI_NULL;

        pstHalPort = &pstHalInfo->astPortInfo[u32Count];

        if (pstHalPort->bEnable && pstHalPort->bConfig == HI_FALSE)
        {
            VPSS_REG_PORT_E enPort = VPSS_REG_BUTT;
            VPSS_HAL_FRAME_S *pstOutFrm = HI_NULL;
            HI_DRV_VID_FRAME_ADDR_S *pstOutAddr = HI_NULL;
			HI_U32 u32Ow,u32VidX,u32VidY,u32VidW,u32VidH;

			enPort = VPSS_HAL_AllocPortId(pstHalPort, abPortUsed);
			if (enPort == VPSS_REG_BUTT)
			{
				HI_ASSERT(0);
            }
			else
			{
				u32PortAvailable--;
			}

            pstOutFrm = &pstHalPort->stOutInfo;
            pstOutAddr = &pstOutFrm->stAddr;

			if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_L)
			{
				u32Ow = pstOutFrm->u32Width/2;

				pstOutFrm->u32Width = u32Ow;
			}
			else if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_R)
			{
				u32Ow = pstOutFrm->u32Width/2;

				pstOutFrm->u32Width = u32Ow;

				pstOutAddr->u32PhyAddr_Y = pstOutAddr->u32PhyAddr_Y + u32Ow;

				pstOutAddr->u32PhyAddr_C = pstOutAddr->u32PhyAddr_C + u32Ow; 
			}
			else
			{

			}
            /* Flip&Mirro */
            VPSS_REG_SetPortMirrorEn(u32AppVir, enPort,pstHalPort->bNeedMirror);  
            VPSS_REG_SetPortFlipEn(u32AppVir, enPort,pstHalPort->bNeedFlip);    
            
            /* UV反转 */
			VPSS_REG_SetPortUVInvert(u32AppVir,enPort, pstOutFrm->bUVInver);

			/* PreZme */
			//VPSS_REG_SetFrmPreZmeEn(u32AppVir, enPort, HI_FALSE, HI_FALSE);

			//VPSS_REG_SetPortZmeEn(u32AppVir, VPSS_REG_HD, HI_FALSE);

			if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_L)
			{
				u32VidX = pstHalPort->stVideoRect.s32X;
				u32VidY = pstHalPort->stVideoRect.s32Y;
				u32VidW = pstHalPort->stVideoRect.s32Width/2;
				u32VidH = pstHalPort->stVideoRect.s32Height;
			}
			else if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_R)
			{
				u32VidX = 0;
				u32VidY = pstHalPort->stVideoRect.s32Y;
				u32VidW = pstHalPort->stVideoRect.s32Width/2;
				u32VidH = pstHalPort->stVideoRect.s32Height;
			}
			else
			{
				u32VidX = pstHalPort->stVideoRect.s32X;
				u32VidY = pstHalPort->stVideoRect.s32Y;
				u32VidW = pstHalPort->stVideoRect.s32Width;
				u32VidH = pstHalPort->stVideoRect.s32Height;
			}

			pstHalPort->stVideoRect.s32X = (HI_S32)u32VidX;
			pstHalPort->stVideoRect.s32Y = (HI_S32)u32VidY;
			pstHalPort->stVideoRect.s32Width = u32VidW;
			pstHalPort->stVideoRect.s32Height = u32VidH;

			/*ZME*/
			VPSS_HAL_SetZmeCfg(enIP,u32AppVir, 
					pstHalInfo,
					enPort,
					u32Count);

			/* LBX */
			VPSS_REG_SetLBABg(u32AppVir, enPort, 0x108080, 0x7f);
			VPSS_REG_SetLBAVidPos(u32AppVir, enPort, 
					u32VidX,
					u32VidY,
					u32VidH,
					u32VidW);

			VPSS_REG_SetLBADispPos(u32AppVir, enPort, 0, 0, 
					pstOutFrm->u32Height, pstOutFrm->u32Width);
			VPSS_REG_SetLBAEn(u32AppVir, enPort, HI_TRUE);


			/* 输出格式 */
			VPSS_REG_SetFrmSize(u32AppVir,enPort,pstOutFrm->u32Height, pstOutFrm->u32Width);
			VPSS_REG_SetFrmAddr(u32AppVir,enPort,pstOutAddr->u32PhyAddr_Y, pstOutAddr->u32PhyAddr_C);
			VPSS_REG_SetFrmStride(u32AppVir,enPort,pstOutAddr->u32Stride_Y,pstOutAddr->u32Stride_C);
			VPSS_REG_SetFrmFormat(u32AppVir,enPort,pstOutFrm->enFormat);

            VPSS_REG_EnPort(u32AppVir, enPort, HI_TRUE);

			pstHalPort->bConfig = HI_TRUE;
        }    
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetAllAlgCfgAddr(HI_U32 u32AppVir, HI_U32 u32AppPhy)
{
    #if 0
    VPSS_REG_SetVc1StrCfgAddr(u32AppVir, u32AppPhy+0x2400);
    VPSS_REG_SetZmeCfgAddr(u32AppVir, u32AppPhy+0x2000);
    VPSS_REG_SetHspCfgAddr(u32AppVir, u32AppPhy+0x2100);
    VPSS_REG_SetSnrCfgAddr(u32AppVir, u32AppPhy+0x3000);
    VPSS_REG_SetDbCfgAddr(u32AppVir, u32AppPhy+0x2200);
    VPSS_REG_SetDrCfgAddr(u32AppVir, u32AppPhy+0x2300);
    VPSS_REG_SetDeiCfgAddr(u32AppVir, u32AppPhy+0x1000);
    VPSS_REG_SetTnrCfgAddr(u32AppVir, u32AppPhy+0x3800);
    VPSS_REG_SetTnrClutCfgAddr(u32AppVir, u32AppPhy+0x3b00);
    VPSS_REG_SetEsCfgAddr(u32AppVir, u32AppPhy+0x2500);
    #endif
    return HI_SUCCESS;
}
HI_S32 VPSS_HAL_SetRwzbCfg(HI_U32 u32AppAddr,VPSS_RWZB_INFO_S *pstRwzbInfo)
{
    HI_U32 u32Count;

    if( pstRwzbInfo->u32EnRwzb == 0x1)
    {
        for(u32Count = 0; u32Count < 6; u32Count++)
        {
            VPSS_REG_SetDetBlk(u32AppAddr,u32Count,&(pstRwzbInfo->u32Addr[u32Count][0]));
                #if 1
                VPSS_INFO("adddr X %d Y %d\n",pstRwzbInfo->u32Addr[u32Count][0],
                                pstRwzbInfo->u32Addr[u32Count][1]);
                                #endif
        }
        
    }
    VPSS_REG_SetDetEn(u32AppAddr,pstRwzbInfo->u32EnRwzb);
    VPSS_REG_SetDetMode(u32AppAddr,pstRwzbInfo->u32Mode);

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetFieldNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
    HI_U32 u32AppVir)
{
    HI_DRV_VID_FRAME_ADDR_S *pstCur = HI_NULL;
	HI_BOOL bPreZme = HI_FALSE;
    
    VPSS_REG_ResetAppReg(u32AppVir, pstHalInfo->pstPqCfg);

    #if 0
	/*rwzb*/
    VPSS_HAL_SetRwzbCfg(u32AppVir, &(pstHalInfo->stRwzbInfo));
    #endif
    
    /* 输入源信息 */
    VPSS_REG_SetInCropEn(u32AppVir, HI_FALSE);
    //VPSS_REG_SetImgBitWidth(u32AppVir, pstHalInfo->stInInfo.enBitWidth);
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_FALSE);
    }

    VPSS_REG_SetImgFormat(u32AppVir, pstHalInfo->stInInfo.enFormat);

    pstCur = &pstHalInfo->stInInfo.stAddr;

    VPSS_REG_SetImgSize(u32AppVir, 
        pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height,
        pstHalInfo->stInInfo.bProgressive);

    /* 帧信息配置 */

    /* 输入帧信息 */
    VPSS_REG_SetImgAddr(u32AppVir,CUR_FIELD,
                        pstCur->u32PhyAddr_Y,
                        pstCur->u32PhyAddr_C,
                        0);

    VPSS_REG_SetImgStride(u32AppVir,CUR_FIELD, pstCur->u32Stride_Y, pstCur->u32Stride_C);

    if (pstHalInfo->stInInfo.enFieldMode == HI_DRV_FIELD_BOTTOM
			|| pstHalInfo->stInInfo.enFieldMode == HI_DRV_FIELD_TOP)
	{
		if (pstHalInfo->stInInfo.enFieldMode == HI_DRV_FIELD_BOTTOM)
		{
			VPSS_REG_SetPreZme(u32AppVir,PREZME_DISABLE,PREZME_VFIELD);
		}
		else
		{
			VPSS_REG_SetPreZme(u32AppVir,PREZME_DISABLE,PREZME_2X);
		}

		pstHalInfo->stInInfo.u32Height = pstHalInfo->stInInfo.u32Height/2;
		bPreZme = HI_TRUE;
	}

    /*db/dr*/
    VPSS_REG_SetDREn(u32AppVir, HI_FALSE);
    VPSS_REG_SetDBEn(u32AppVir, HI_FALSE);
    
    /* 输出Port信息 */
    VPSS_HAL_SetPortCfg(enIP, u32AppVir, pstHalInfo);

	if (bPreZme)
	{
		pstHalInfo->stInInfo.u32Height = pstHalInfo->stInInfo.u32Height*2;
	}

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetFrameNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
    HI_U32 u32AppVir)
{
    HI_DRV_VID_FRAME_ADDR_S *pstCur = HI_NULL;
    
    VPSS_REG_ResetAppReg(u32AppVir, pstHalInfo->pstPqCfg);

    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        VPSS_REG_SetCurTunlEn(u32AppVir, HI_TRUE);
        VPSS_REG_SetCurTunlAddr(u32AppVir, 
                                CUR_FRAME,
                                pstHalInfo->stInInfo.u32TunnelAddr);
    }
    else
    {
        VPSS_REG_SetCurTunlEn(u32AppVir, HI_FALSE);
    }
    
    #if 0
	/*rwzb*/
    VPSS_HAL_SetRwzbCfg(u32AppVir, &(pstHalInfo->stRwzbInfo));
    #endif
    
    /* 输入源信息 */
    VPSS_REG_SetInCropEn(u32AppVir, HI_FALSE);
    //VPSS_REG_SetImgBitWidth(u32AppVir, pstHalInfo->stInInfo.enBitWidth);
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_FALSE);
    }

    VPSS_REG_SetImgFormat(u32AppVir, pstHalInfo->stInInfo.enFormat);

    pstCur = &pstHalInfo->stInInfo.stAddr;

    VPSS_REG_SetImgSize(u32AppVir, 
        pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height,
        pstHalInfo->stInInfo.bProgressive);

    /* 帧信息配置 */

    /* 输入帧信息 */
    VPSS_REG_SetImgAddr(u32AppVir,CUR_FIELD,
                        pstCur->u32PhyAddr_Y,
                        pstCur->u32PhyAddr_C,
                        0);
    VPSS_REG_SetImgStride(u32AppVir,CUR_FIELD, pstCur->u32Stride_Y, pstCur->u32Stride_C);

    
    /*db/dr*/
    VPSS_HAL_SetDnrCfg(enIP,u32AppVir,pstHalInfo);

	if (pstHalInfo->stInInfo.u32Width > 1920)
	{
		VPSS_HAL_SetHSCLCfg(enIP, u32AppVir, pstHalInfo);
		pstHalInfo->stInInfo.u32Width = pstHalInfo->stInInfo.u32Width/2;
		pstHalInfo->stInInfo.u32Width = 1920;
	}

	/* 输出Port信息 */
    VPSS_HAL_SetPortCfg(enIP, u32AppVir, pstHalInfo);

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_Set5FieldNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, 
    HI_U32 u32AppVir,HI_U32 u32AppPhy)
{
    HI_U32  VPSS_REFYADDR;
    HI_U32  VPSS_REFCADDR;
    HI_U32  VPSS_REFCRADDR;

    HI_U32  VPSS_NEXT1YADDR;
    HI_U32  VPSS_NEXT1CADDR;
    HI_U32  VPSS_NEXT1CRADDR;

    HI_U32  VPSS_NEXT3YADDR;
    HI_U32  VPSS_NEXT3CADDR;
    HI_U32  VPSS_NEXT3CRADDR;
    
    HI_U32  VPSS_DEI_ADDR;

    HI_DRV_VID_FRAME_ADDR_S *pstCur = HI_NULL;

	HI_U32 u32CurFieldYaddr;
	HI_U32 u32CurFieldCaddr;
    
    
    VPSS_REG_ResetAppReg(u32AppVir, pstHalInfo->pstPqCfg);
    
    /* 输入源信息 */
    VPSS_REG_SetInCropEn(u32AppVir, HI_FALSE);
    //VPSS_REG_SetImgBitWidth(u32AppVir, pstHalInfo->stInInfo.enBitWidth);
    VPSS_REG_SetImgFormat(u32AppVir, pstHalInfo->stInInfo.enFormat);
    VPSS_REG_SetImgSize(u32AppVir, 
        pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height,
        pstHalInfo->stInInfo.bProgressive);

    /* 帧信息配置 */
    pstCur = &pstHalInfo->stInInfo.stAddr;

    /* 输入帧信息 */
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_FALSE);
    }
    
    #if 1
    if(pstHalInfo->stInInfo.enFieldMode == HI_DRV_FIELD_BOTTOM)
    {
        if (pstCur->u32Stride_Y >= 256
            && (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
                || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
                || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
                || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP))
        {
			u32CurFieldYaddr = pstCur->u32PhyAddr_Y + 256;
			u32CurFieldCaddr = pstCur->u32PhyAddr_C + 256;
        }
        else
        {
			u32CurFieldYaddr = pstCur->u32PhyAddr_Y + pstCur->u32Stride_Y;
			u32CurFieldCaddr = pstCur->u32PhyAddr_C + pstCur->u32Stride_C;
        }
    }
	else
	{
		u32CurFieldYaddr = pstCur->u32PhyAddr_Y;
		u32CurFieldCaddr = pstCur->u32PhyAddr_C;
	}
    #endif
    VPSS_REG_SetImgAddr(u32AppVir,CUR_FIELD,
                        u32CurFieldYaddr,
                        u32CurFieldCaddr,
                        0);
    VPSS_REG_SetImgStride(u32AppVir,CUR_FIELD, pstCur->u32Stride_Y, pstCur->u32Stride_C);

    
    /*db/dr*/
    VPSS_HAL_SetDnrCfg(enIP,u32AppVir,pstHalInfo);

    /*RWZB*/
    VPSS_HAL_SetRwzbCfg(u32AppVir, &(pstHalInfo->stRwzbInfo));
    
    /*dei*/
    VPSS_REG_SetImgReadMod(u32AppVir, HI_TRUE);
    VPSS_REG_EnDei(u32AppVir, HI_TRUE);
    VPSS_REG_SetDeiTopFirst(u32AppVir, pstHalInfo->stInInfo.bTopFirst);

    switch(pstHalInfo->stInInfo.enFieldMode)
    {
        case HI_DRV_FIELD_BOTTOM:
            VPSS_REG_SetDeiFieldMode(u32AppVir, HI_TRUE);
            break;
        case HI_DRV_FIELD_TOP:
            VPSS_REG_SetDeiFieldMode(u32AppVir, HI_FALSE);
            break;
        default:
            VPSS_FATAL("No spt field Type:%d!\n", pstHalInfo->stInInfo.enFieldMode);
            return HI_FAILURE;
    }
    VPSS_REG_SetModeEn(u32AppVir,REG_DIE_MODE_CHROME,HI_TRUE);
    VPSS_REG_SetModeEn(u32AppVir,REG_DIE_MODE_LUMA,HI_TRUE);

    #if 1
    VPSS_REG_SetStWrAddr(u32AppVir,pstHalInfo->stHisAddr.u32WPhyAddr);
    VPSS_REG_SetStRdAddr(u32AppVir,
                        pstHalInfo->stHisAddr.u32RPhyAddr);
    VPSS_REG_SetStStride(u32AppVir,
                        pstHalInfo->stHisAddr.u32Stride);
    
    //HI_S32 VPSS_REG_SetDeiParaAddr(HI_U32 u32ParaAddr);
    VPSS_DEI_ADDR = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,VPSS_DIECTRL)-sizeof(HI_U32);
    VPSS_REG_SetDeiParaAddr(u32AppVir,
                        VPSS_DEI_ADDR);
    #endif
    VPSS_REG_SetMode(u32AppVir, REG_DIE_MODE_ALL, 1);
    
    VPSS_REFYADDR = pstHalInfo->stFieldAddr[0].u32PhyAddr_Y;
    VPSS_REFCADDR = pstHalInfo->stFieldAddr[0].u32PhyAddr_C;
    VPSS_REFCRADDR = pstHalInfo->stFieldAddr[0].u32PhyAddr_Cr;
    
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,LAST_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,LAST_FIELD,HI_FALSE);
    }
    VPSS_REG_SetDeiAddr(u32AppVir,LAST_FIELD,VPSS_REFYADDR,VPSS_REFCADDR, VPSS_REFCRADDR);
    VPSS_REG_SetDeiStride(u32AppVir,LAST_FIELD,
                            pstHalInfo->stFieldAddr[0].u32Stride_Y,
                            pstHalInfo->stFieldAddr[0].u32Stride_C);

    /*********/

    /*********/
    VPSS_NEXT1YADDR = pstHalInfo->stFieldAddr[3].u32PhyAddr_Y;
    VPSS_NEXT1CADDR = pstHalInfo->stFieldAddr[3].u32PhyAddr_C;
    VPSS_NEXT1CRADDR = pstHalInfo->stFieldAddr[3].u32PhyAddr_Cr;
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,NEXT1_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,NEXT1_FIELD,HI_FALSE);
    }
    VPSS_REG_SetDeiAddr(u32AppVir,NEXT1_FIELD,VPSS_NEXT1YADDR,VPSS_NEXT1CADDR, VPSS_NEXT1CRADDR);
    VPSS_REG_SetDeiStride(u32AppVir,NEXT1_FIELD,
                            pstHalInfo->stFieldAddr[3].u32Stride_Y,
                            pstHalInfo->stFieldAddr[3].u32Stride_C);

    /*********/

    /*********/
    VPSS_NEXT3YADDR = pstHalInfo->stFieldAddr[4].u32PhyAddr_Y;
    VPSS_NEXT3CADDR = pstHalInfo->stFieldAddr[4].u32PhyAddr_C;
    VPSS_NEXT3CRADDR = pstHalInfo->stFieldAddr[4].u32PhyAddr_Cr;
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,NEXT2_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,NEXT2_FIELD,HI_FALSE);
    }
    VPSS_REG_SetDeiAddr(u32AppVir,NEXT2_FIELD,VPSS_NEXT3YADDR,VPSS_NEXT3CADDR, VPSS_NEXT3CRADDR);
    VPSS_REG_SetDeiStride(u32AppVir,NEXT2_FIELD,
                            pstHalInfo->stFieldAddr[4].u32Stride_Y,
                            pstHalInfo->stFieldAddr[4].u32Stride_C);

                                 
    /* 输出Port信息 */
    VPSS_HAL_SetPortCfg(enIP, u32AppVir, pstHalInfo);
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_Set3DFrameNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
    HI_U32 u32AppVir)
{
    HI_U32 u32W, u32H;

    
    (HI_VOID)VPSS_HAL_SetFrameNode(enIP, pstHalInfo, u32AppVir);

    /* 根据输入格式设置偏移 */
    switch(pstHalInfo->stInInfo.eFrmType)
    {
        case HI_DRV_FT_SBS:
            u32W = pstHalInfo->stInInfo.u32Width;
            VPSS_REG_SetImgOffset(u32AppVir,CUR_FIELD,u32W,0);

            break;
            
        case HI_DRV_FT_TAB:
            u32H = pstHalInfo->stInInfo.u32Height;
            VPSS_REG_SetImgOffset(u32AppVir,CUR_FIELD,0,u32H);
            break;
            
        case HI_DRV_FT_FPK:
            break;
        default:
            VPSS_FATAL("eFrmType %d invaild\n", pstHalInfo->stInInfo.eFrmType);
            return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetUHDNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
    HI_U32 u32AppVir)
{
    HI_DRV_VID_FRAME_ADDR_S *pstCur = HI_NULL;
    
    VPSS_REG_ResetAppReg(u32AppVir, pstHalInfo->pstPqCfg);

    /*tunnel*/
    VPSS_REG_SetCurTunlEn(u32AppVir, HI_FALSE);
    
    /* 输入源信息 */
    VPSS_REG_SetInCropEn(u32AppVir, HI_FALSE);
    //VPSS_REG_SetImgBitWidth(u32AppVir, pstHalInfo->stInInfo.enBitWidth);
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_FALSE);
    }
    VPSS_REG_SetImgFormat(u32AppVir, pstHalInfo->stInInfo.enFormat);

    
    pstCur = &pstHalInfo->stInInfo.stAddr;
    VPSS_REG_SetImgSize(u32AppVir, 
        pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height,
        pstHalInfo->stInInfo.bProgressive);

    /* 帧信息配置 */

    /* 输入帧信息 */
    VPSS_REG_SetImgAddr(u32AppVir,CUR_FIELD,
                        pstCur->u32PhyAddr_Y,
                        pstCur->u32PhyAddr_C,
                        0);
    VPSS_REG_SetImgStride(u32AppVir,CUR_FIELD, pstCur->u32Stride_Y, pstCur->u32Stride_C);

    
    /*db/dr*/
    VPSS_REG_SetDREn(u32AppVir, HI_FALSE);
    VPSS_REG_SetDBEn(u32AppVir, HI_FALSE);

    if (pstHalInfo->stInInfo.u32Width > 1920)
    {
        VPSS_HAL_SetHSCLCfg(enIP, u32AppVir, pstHalInfo);
        //pstHalInfo->stInInfo.u32Width = pstHalInfo->stInInfo.u32Width/2;
        pstHalInfo->stInInfo.u32Width = 1920;
    }
    
    /* 输出Port信息 */
    VPSS_HAL_SetPortCfg(enIP, u32AppVir, pstHalInfo);

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetInCrop(HI_U32 u32VirAddr,HI_U32 u32X,HI_U32 u32Y,HI_U32 u32Width,HI_U32 u32Height)
{
	VPSS_REG_SetInCropMode(u32VirAddr,HI_TRUE);
	VPSS_REG_SetInCropEn(u32VirAddr,HI_TRUE);
	VPSS_REG_SetInCropPos(u32VirAddr,u32Y,u32X);
	VPSS_REG_SetInCropSize(u32VirAddr,u32Height,u32Width);

	return HI_SUCCESS;
}
HI_S32 VPSS_HAL_SetUHDSplitNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
    HI_U32 u32AppVir)
{
    HI_DRV_VID_FRAME_ADDR_S *pstCur = HI_NULL;
	HI_U32 u32X,u32Y,u32RdWidth,u32RdHeight;
    
    VPSS_REG_ResetAppReg(u32AppVir, pstHalInfo->pstPqCfg);

    /*tunnel*/
    VPSS_REG_SetCurTunlEn(u32AppVir, HI_FALSE);
   
    /* 输入源信息 */
	if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_L)
	{
		u32X = 0;
		u32Y = 0;
		u32RdWidth = pstHalInfo->stInInfo.u32Width/2;
		u32RdHeight = pstHalInfo->stInInfo.u32Height;
	}
	else
	{
		u32X = pstHalInfo->stInInfo.u32Width/2;
		u32Y = 0;
		u32RdWidth = pstHalInfo->stInInfo.u32Width/2;
		u32RdHeight = pstHalInfo->stInInfo.u32Height;
	}

	if (u32X % 16 == 0)
	{
		VPSS_REG_SetInCropEn(u32AppVir, HI_FALSE);

		pstHalInfo->stInInfo.u32Width = u32RdWidth;
		pstHalInfo->stInInfo.u32Height = u32RdHeight;

		VPSS_REG_SetImgOffset(u32AppVir,CUR_FIELD,u32X,u32Y);
	}
	else
	{
		HI_U32 u32CropX;	
		HI_U32 u32CropY;	
		HI_U32 u32CropWidth;	
		HI_U32 u32CropHeight;	
		HI_U32 u32OffsetX;
		HI_U32 u32OffsetY;

//		VPSS_ERROR("x %d y %d w %d h %d\n",u32X,u32Y,u32RdWidth,u32RdHeight);

		u32CropX = u32X - (u32X / 16 -1)*16;
		u32CropY = 0;
		u32CropWidth = u32RdWidth;
		u32CropHeight = u32RdHeight;

//		VPSS_ERROR("crop x %d y %d w %d h %d\n",u32CropX,u32CropY,u32CropWidth,u32CropHeight);

		(HI_VOID)VPSS_HAL_SetInCrop(u32AppVir,u32CropX,u32CropY,u32CropWidth,u32CropHeight);

		pstHalInfo->stInInfo.u32Width = u32RdWidth + u32CropX;
		pstHalInfo->stInInfo.u32Height = u32RdHeight;

		u32OffsetX = (u32X/16 - 1)*16;
		u32OffsetY = u32Y;

		VPSS_REG_SetImgOffset(u32AppVir,CUR_FIELD,u32OffsetX,u32OffsetY);

#if 0
		VPSS_ERROR("read x %d y %d w %d h %d crop x %d y %d\n",
				u32OffsetX,
				u32OffsetY,
				pstHalInfo->stInInfo.u32Width,
				pstHalInfo->stInInfo.u32Height,
				u32CropX,
				u32CropY);
#endif
	}


    //VPSS_REG_SetImgBitWidth(u32AppVir, pstHalInfo->stInInfo.enBitWidth);
	

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_FALSE);
    }

    VPSS_REG_SetImgFormat(u32AppVir, pstHalInfo->stInInfo.enFormat);

    pstCur = &pstHalInfo->stInInfo.stAddr;
	
    VPSS_REG_SetImgSize(u32AppVir, 
        pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height,
        pstHalInfo->stInInfo.bProgressive);

		pstHalInfo->stInInfo.u32Width = u32RdWidth ;
		pstHalInfo->stInInfo.u32Height = u32RdHeight;



    /* 帧信息配置 */

    /* 输入帧信息 */
    VPSS_REG_SetImgAddr(u32AppVir,CUR_FIELD,
                        pstCur->u32PhyAddr_Y,
                        pstCur->u32PhyAddr_C,
                        0);
    VPSS_REG_SetImgStride(u32AppVir,CUR_FIELD, pstCur->u32Stride_Y, pstCur->u32Stride_C);

    
    /*db/dr*/
    VPSS_REG_SetDREn(u32AppVir, HI_FALSE);
    VPSS_REG_SetDBEn(u32AppVir, HI_FALSE);

    if (pstHalInfo->stInInfo.u32Width > 1920)
    {
        VPSS_HAL_SetHSCLCfg(enIP, u32AppVir, pstHalInfo);
        pstHalInfo->stInInfo.u32Width = 1920;
    }
    
    /* 输出Port信息 */
    VPSS_HAL_SetPortCfg(enIP, u32AppVir, pstHalInfo);

    return HI_SUCCESS;
}
HI_S32 VPSS_HAL_SetRotateNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
    HI_U32 u32AppVir, HI_BOOL bRotateY, HI_U32 u32PortId)
{
    #if 1
    HI_DRV_VPSS_ROTATION_E enRotation;
    HI_DRV_VID_FRAME_ADDR_S *pstCur = HI_NULL;
    VPSS_REG_PORT_E enPort = VPSS_REG_HD;
    VPSS_HAL_FRAME_S *pstOutFrm = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstOutAddr = HI_NULL;
    HI_U32 u32Angle;
    
    VPSS_REG_ResetAppReg(u32AppVir, NULL);

     /* 输入源信息 */
    VPSS_REG_SetInCropEn(u32AppVir, HI_FALSE);
    //VPSS_REG_SetImgBitWidth(u32AppVir, pstHalInfo->stInInfo.enBitWidth);
    VPSS_REG_SetImgFormat(u32AppVir, pstHalInfo->stInInfo.enFormat);
    VPSS_REG_SetImgSize(u32AppVir, 
        pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height,
        pstHalInfo->stInInfo.bProgressive);

    /* 输入帧配置 */
    pstCur = &pstHalInfo->stInInfo.stAddr;

    /* 输入帧信息 */
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_FALSE);
    }
    
    VPSS_REG_SetImgAddr(u32AppVir,CUR_FIELD,
                        pstCur->u32PhyAddr_Y,
                        pstCur->u32PhyAddr_C,
                        0);
    VPSS_REG_SetImgStride(u32AppVir,CUR_FIELD, pstCur->u32Stride_Y, pstCur->u32Stride_C);

    /* 输出配置 */ 
    pstOutFrm = &pstHalInfo->astPortInfo[u32PortId].stOutInfo;
    pstOutAddr = &pstOutFrm->stAddr; 
    VPSS_REG_SetFrmSize(u32AppVir,enPort,pstOutFrm->u32Height, pstOutFrm->u32Width);
    VPSS_REG_SetFrmAddr(u32AppVir,enPort,pstOutAddr->u32PhyAddr_Y, pstOutAddr->u32PhyAddr_C);
    VPSS_REG_SetFrmStride(u32AppVir,enPort,pstOutAddr->u32Stride_Y,pstOutAddr->u32Stride_C);
    VPSS_REG_SetFrmFormat(u32AppVir,enPort,pstOutFrm->enFormat);        
    
    VPSS_REG_EnPort(u32AppVir, enPort, HI_TRUE);

    /* 旋转配置 */ 
    enRotation = pstHalInfo->astPortInfo[u32PortId].enRotation;    
    switch(enRotation)
    {
        case HI_DRV_VPSS_ROTATION_90:
            u32Angle = 0x0;
            break;
        case HI_DRV_VPSS_ROTATION_270:
            u32Angle = 0x1;
            break;
        default:
            u32Angle = 0x1;
            VPSS_FATAL("Ro Error  %d\n",u32Angle);
            break;
    }
    
    if (bRotateY)
    {
        VPSS_REG_SetRotation(u32AppVir,u32Angle,1);
    }
    else
    {
        VPSS_REG_SetRotation(u32AppVir,u32Angle,2);
    }
    #endif
    return HI_SUCCESS;
}

HI_VOID VPSS_HAL_DumpReg(VPSS_IP_E enIP, VPSS_HAL_TASK_NODE_E enTaskNodeId)
{
    HI_U32 i;
    HI_U32 *pu32Reg;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    pstHalCtx = &stHalCtx[enIP];

    pu32Reg = (HI_U32 *)(pstHalCtx->au32AppVir[enTaskNodeId]);
    
    printk("\n\nPhyAddr %8x   enTaskNodeId = %d\n\n", 
        pstHalCtx->au32AppPhy[enTaskNodeId], enTaskNodeId);
    
    for(i=0; i<(64*4); i++)
    {
        if(i%(64) == 0)
        {
            printk("\nBASE %x", i*4);
        }

        if(i%4 == 0)
        {
            printk("\n%x0:", (i%64)/4);
        }
        
        printk("%.8x  ", *(pu32Reg+i));
    }
    
    printk("\n\n");

    for(i=1024; i<1024+64; i++)
    {
        if(i%(64) == 0)
        {
            printk("\nBASE %x", i*4);
        }

        if(i%4 == 0)
        {
            printk("\n%x0:", (i%64)/4);
        }
        
        printk("%.8x  ", *(pu32Reg+i));
    }

    printk("\n\n");

    for(i=2048; i<2048+64; i++)
    {
        if(i%(64) == 0)
        {
            printk("\nBASE %x", i*4);
        }

        if(i%4 == 0)
        {
            printk("\n%x0:", (i%64)/4);
        }
        
        printk("%.8x  ", *(pu32Reg+i));
    }

    printk("\n\n");

}

#if 0
/* 以上为内部调用函数 */
/* 以下为外部调用函数 */
#endif

HI_S32 VPSS_HAL_Init(VPSS_IP_E enIP)
{
    HI_U32 i, j;
    HI_S32 s32Ret = HI_SUCCESS;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;

    VPSS_HAL_CHECK_IP_VAILD(enIP);

    pstHalCtx = &stHalCtx[enIP];

    if (pstHalCtx->bInit)
    {
        VPSS_INFO("VPSS IP%d, Already Init\n", enIP);
        return HI_SUCCESS;
    }

    /* 申请和分配NODE节点 */
    s32Ret = HI_DRV_MMZ_AllocAndMap("VPSS_RegBuf", HI_NULL,
        VPSS_REG_SIZE*VPSS_HAL_TASK_NODE_BUTT, 0, &pstHalCtx->stRegBuf);
    if (s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("Alloc VPSS_RegBuf Failed\n");
        return HI_FAILURE;
    }

    for (i=0; i<VPSS_HAL_TASK_NODE_BUTT; i++)
    {
        pstHalCtx->au32AppPhy[i] = pstHalCtx->stRegBuf.u32StartPhyAddr
                                 + VPSS_REG_SIZE*i;
        
        pstHalCtx->au32AppVir[i] = pstHalCtx->stRegBuf.u32StartVirAddr
                                 + VPSS_REG_SIZE*i;
    }

    /* 申请和分配缩放系数 */
    s32Ret = HI_DRV_MMZ_AllocAndMap("VPSS_ZmeCoefBuf", HI_NULL,
        VPSS_ZME_COEF_SIZE*4*VPSS_ZME_COEF_NUM, 0, &pstHalCtx->stZmeCoefBuf);
    if (s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("Alloc VPSS_ZmeCoefBuf Failed\n");
        return HI_FAILURE;
    }

    for (i = 0; i < VPSS_ZME_COEF_NUM; i++)
    {
        pstHalCtx->abUsed[i] = HI_FALSE;
        
        for(j=0; j<4; j++)
        {
            pstHalCtx->au32ZmeCoefPhy[i][j] = 
                pstHalCtx->stZmeCoefBuf.u32StartPhyAddr + VPSS_ZME_COEF_SIZE * (4*i+j) ;
            
            pstHalCtx->au32ZmeCoefVir[i][j] =
                pstHalCtx->stZmeCoefBuf.u32StartVirAddr + VPSS_ZME_COEF_SIZE * (4*i+j);
        }
    }

    /* 映射寄存器地址 */
    pstHalCtx->u32BaseRegVir
        = (HI_U32)IO_ADDRESS(pstHalCtx->u32BaseRegPhy);
    if (0 == pstHalCtx->u32BaseRegVir)
    {
        VPSS_FATAL("io_address VPSS_REG(%#x) Failed\n", pstHalCtx->u32BaseRegPhy);
        HI_DRV_MMZ_UnmapAndRelease(&pstHalCtx->stRegBuf);
        return HI_FAILURE;
    }

    pstHalCtx->bInit = HI_TRUE;

    VPSS_HAL_SetClockEn(enIP, HI_FALSE);
    
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_DelInit(VPSS_IP_E enIP)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);

    pstHalCtx = &stHalCtx[enIP];

    if (!pstHalCtx->bInit)
    {
        VPSS_INFO("VPSS IP%d, Already DeInit\n", enIP);
        return HI_SUCCESS;
    }

    VPSS_HAL_SetClockEn(enIP, HI_FALSE);

    HI_ASSERT(pstHalCtx->u32BaseRegVir != 0);
    if (pstHalCtx->u32BaseRegVir != 0)
    {
        pstHalCtx->u32BaseRegVir = 0;
    }

    HI_DRV_MMZ_UnmapAndRelease(&pstHalCtx->stRegBuf);
    memset(&pstHalCtx->stRegBuf, 0, sizeof(MMZ_BUFFER_S));

    HI_DRV_MMZ_UnmapAndRelease(&pstHalCtx->stZmeCoefBuf);
    memset(&pstHalCtx->stZmeCoefBuf, 0, sizeof(MMZ_BUFFER_S));

    pstHalCtx->bInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetClockEn(VPSS_IP_E enIP, HI_BOOL bClockEn)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);
    
    pstHalCtx = &stHalCtx[enIP];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    if(pstHalCtx->bClockEn == bClockEn)
    {
        return HI_SUCCESS;
    }

    if (bClockEn)
    {
        VPSS_REG_SetClockEn(enIP, HI_TRUE);

        VPSS_REG_ResetAppReg(pstHalCtx->u32BaseRegVir, HI_NULL);
        VPSS_REG_SetTimeOut(pstHalCtx->u32BaseRegVir, DEF_LOGIC_TIMEOUT);
        VPSS_REG_SetIntMask(pstHalCtx->u32BaseRegVir, 0xfe);
    }
    else
    {
        VPSS_REG_SetClockEn(enIP, HI_FALSE);
    }

    pstHalCtx->bClockEn = bClockEn;

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_GetClockEn(VPSS_IP_E enIP, HI_BOOL *pbClockEn)
{
    //:TODO:后续加入CRG和时钟控制
    return HI_SUCCESS;   
}

HI_S32 VPSS_HAL_GetIntState(VPSS_IP_E enIP, HI_U32* pu32IntState)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(pu32IntState);

    pstHalCtx = &stHalCtx[enIP];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    return VPSS_REG_GetIntState(pstHalCtx->u32BaseRegVir, pu32IntState);
}

HI_S32 VPSS_HAL_ClearIntState(VPSS_IP_E enIP, HI_U32 u32IntState)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);
    
    pstHalCtx = &stHalCtx[enIP];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    return VPSS_REG_ClearIntState(pstHalCtx->u32BaseRegVir, u32IntState);
}

HI_S32 VPSS_HAL_SetNodeInfo(VPSS_IP_E enIP,
     VPSS_HAL_INFO_S *pstHalInfo,  VPSS_HAL_TASK_NODE_E enTaskNodeId)
{
    HI_U32 u32PortId = 0;    
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    HI_U32 u32AppVir, u32AppPhy;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(pstHalInfo);
    VPSS_HAL_CHECK_NODE_ID_VAILD(enTaskNodeId);

    pstHalCtx = &stHalCtx[enIP];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    u32AppVir = pstHalCtx->au32AppVir[enTaskNodeId];
    u32AppPhy = pstHalCtx->au32AppPhy[enTaskNodeId];

    switch(pstHalInfo->enNodeType)
    {
        case VPSS_HAL_NODE_2D_Field:
            s32Ret = VPSS_HAL_SetFieldNode(enIP, pstHalInfo, u32AppVir);
            break;
        case VPSS_HAL_NODE_2D_FRAME:
            s32Ret = VPSS_HAL_SetFrameNode(enIP, pstHalInfo, u32AppVir);
            break;
        case VPSS_HAL_NODE_2D_5Field:
            s32Ret = VPSS_HAL_Set5FieldNode(enIP, pstHalInfo, u32AppVir,
                                            u32AppPhy);
            break;
        case VPSS_HAL_NODE_3D_FRAME_R:
            s32Ret = VPSS_HAL_Set3DFrameNode(enIP, pstHalInfo, u32AppVir);
            break;
        case VPSS_HAL_NODE_UHD:
            s32Ret = VPSS_HAL_SetUHDNode(enIP, pstHalInfo, u32AppVir);
        case VPSS_HAL_NODE_UHD_SPLIT_L:
        case VPSS_HAL_NODE_UHD_SPLIT_R:
            s32Ret = VPSS_HAL_SetUHDSplitNode(enIP, pstHalInfo, u32AppVir);
            break;
#if 0
        case VPSS_HAL_NODE_2D_3Field:
            //VPSS_HAL_SetFrameNode(pstHalInfo, u32AppVir);
            break;
        case VPSS_HAL_NODE_PZME:
            //VPSS_HAL_SetFrameNode(pstHalInfo, u32AppVir);
            break;
        
        case VPSS_HAL_NODE_3DDET:
            //VPSS_HAL_SetFrameNode(pstHalInfo, u32AppVir);
            break;
        case VPSS_HAL_NODE_ZME_2L:
            //VPSS_HAL_SetFrameNode(pstHalInfo, u32AppVir);
            break;
        case VPSS_HAL_NODE_ROTATION_Y:
            //VPSS_HAL_SetFrameNode(pstHalInfo, u32AppVir);
            break;
        case VPSS_HAL_NODE_ROTATION_C:
            //VPSS_HAL_SetFrameNode(pstHalInfo, u32AppVir);
            break;
#endif
        case VPSS_HAL_NODE_ROTATION_Y:
            u32PortId = (enTaskNodeId - VPSS_HAL_TASK_NODE_P0_RO_Y) / 2;//:TODO:优化
            s32Ret = VPSS_HAL_SetRotateNode(enIP, pstHalInfo, u32AppVir, HI_TRUE,u32PortId);
            break;
        case VPSS_HAL_NODE_ROTATION_C:
            u32PortId = (enTaskNodeId - VPSS_HAL_TASK_NODE_P0_RO_Y) / 2;            
            s32Ret = VPSS_HAL_SetRotateNode(enIP, pstHalInfo, u32AppVir, HI_FALSE,u32PortId);
            break;
        default:
            VPSS_FATAL("No this Node Type:%d!\n", pstHalInfo->enNodeType);
            return HI_FAILURE;
            
    }

    (HI_VOID)VPSS_HAL_SetAllAlgCfgAddr(u32AppVir, u32AppPhy);

    //VPSS_FATAL("enTaskNodeId = %d, this Node Type:%d!\n", enTaskNodeId, pstHalInfo->enNodeType);
    //VPSS_HAL_DumpReg(enIP,enTaskNodeId);
    
    return s32Ret;
}

HI_S32 VPSS_HAL_StartLogic(VPSS_IP_E enIP, 
    HI_BOOL abNodeVaild[VPSS_HAL_TASK_NODE_BUTT])
{
    HI_U32 i = 0;
    VPSS_HAL_TASK_NODE_E enId, enLastVaild = VPSS_HAL_TASK_NODE_BUTT;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(abNodeVaild);
    
    pstHalCtx = &stHalCtx[enIP];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    /* 从后向前链接所有节点 */
    enLastVaild = VPSS_HAL_TASK_NODE_BUTT;
    for(i=0;i<VPSS_HAL_TASK_NODE_BUTT;i++)
    {
        enId = VPSS_HAL_TASK_NODE_BUTT - 1 - i;
        
        if(HI_TRUE == abNodeVaild[enId])
        {
            if(VPSS_HAL_TASK_NODE_BUTT == enLastVaild)
            {
                VPSS_REG_StartLogic(0, pstHalCtx->au32AppVir[enId]);
            }
            else
            {
                VPSS_REG_StartLogic(pstHalCtx->au32AppPhy[enLastVaild], 
                    pstHalCtx->au32AppVir[enId]);
            }

            enLastVaild = enId;
        }
    }

    /* 清空所有ZME系数使用 */
    for(i=0; i<VPSS_ZME_COEF_NUM; i++)
    {
        pstHalCtx->abUsed[i] = HI_FALSE;
    }

    HI_ASSERT(enLastVaild != VPSS_HAL_TASK_NODE_BUTT);
    if (enLastVaild == VPSS_HAL_TASK_NODE_BUTT)
    {
        VPSS_FATAL("No Node Needs Start\n");
        return HI_FAILURE;
    }
    else
    {
        /* 启动硬件 */
        return VPSS_REG_StartLogic(pstHalCtx->au32AppPhy[enLastVaild], 
                            pstHalCtx->u32BaseRegVir);
    }
}


HI_S32 VPSS_HAL_GetSCDInfo(HI_U32 u32AppAddr,HI_S32 s32SCDInfo[32])
{
	//return VPSS_REG_GetSCDInfo(u32AppAddr,s32SCDInfo);
	return HI_SUCCESS;
}

HI_VOID VPSS_HAL_GetDetPixel(VPSS_IP_E enIP,HI_U32 BlkNum, HI_U8* pstData)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    HI_U32 u32AppAddr;
    
    pstHalCtx = &stHalCtx[enIP];

    u32AppAddr = pstHalCtx->u32BaseRegVir;
    
    VPSS_REG_GetDetPixel(u32AppAddr,BlkNum,pstData);
}

HI_S32 VPSS_HAL_GetBaseRegAddr(VPSS_IP_E enIP,
                                 HI_U32 *pu32PhyAddr,
                                 HI_U32 *pu32VirAddr)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    pstHalCtx = &stHalCtx[enIP];

    *pu32PhyAddr = pstHalCtx->u32BaseRegPhy;
    *pu32VirAddr = pstHalCtx->u32BaseRegVir;
    
    return HI_SUCCESS;
}                                 

HI_S32 VPSS_HAL_GetCycleCnt(VPSS_IP_E enIP,HI_U32 *pu32Cycle)
{
	HI_U32 u32VirAddr;

    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    pstHalCtx = &stHalCtx[enIP];

    u32VirAddr = pstHalCtx->u32BaseRegVir;

	VPSS_REG_GetReg(u32VirAddr,pu32Cycle);

	return HI_SUCCESS;
}
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif  /* __cplusplus */
