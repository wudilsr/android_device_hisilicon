/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_vicap.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/11/14
  Description   : 
  History       :
  1.Date        : 2013/11/14
    Author      : w00248302/c00186004
    Modification: Created file
******************************************************************************/
#include <linux/kernel.h>       /* printk */
#include <asm/io.h>
#include <linux/seq_file.h>

#include "hi_debug.h"
#include "vicap_reg.h"
#include "hal_vicap.h"
#include "drv_vicap_coef.h"

volatile VICAP_REGS_TYPE_S *g_pstVicapAllReg = HI_NULL;

/*��֤ע���Ƿ�ɹ�*/
HI_S32 VicapVerifyRegWrite(HI_U32 *RegValue, HI_U32 WriteValue, HI_CHAR *pRegName)
{
    /*WriteValue��ֵΪ0*/
    HI_BOOL bWriteSuccess = HI_FALSE;
    //printk("ViVerifyRegWrite %s: offset:%p value:%x\n",pRegName, RegValue, *RegValue);

    bWriteSuccess = (*RegValue == WriteValue);
    if (!bWriteSuccess)
    {
    }

    return !bWriteSuccess;
}

HI_VOID VicapHalDumpReg(HI_VOID)
{
    HI_U32 i;
    HI_U32 *pu32Reg;

    pu32Reg = (HI_U32 *)(g_pstVicapAllReg);
    
    for(i = 0; i < (64 * 3); i++)
    {
        if(i % (64) == 0)
        {
            printk("\nBASE %x", i * 4);
        } 

        if(i % 4 == 0)
        {
            printk("\n%x0:", (i % 64) / 4);
        }
        
        printk("%.8x  ", *(pu32Reg + i));
    }
    
    printk("\n\n");

    for(i = 1024; i < 1024 + 64 * 11; i++)
    {
        if(i % (64) == 0)
        {
            printk("\nBASE %x", i * 4);
        }

        if(i % 4 == 0)
        {
            printk("\n%x0:", (i % 64) / 4);
        }
        
        printk("%.8x  ", *(pu32Reg + i));
    }

    printk("\n\n");

    for(i = 2048; i < 2048 + 64 * 11; i++)
    {
        if(i % (64) == 0)
        {
            printk("\nBASE %x", i * 4);
        } 

        if(i % 4 == 0)
        {
            printk("\n%x0:", (i % 64) / 4);
        }
        
        printk("%.8x  ", *(pu32Reg + i));
    }

    printk("\n\n");

}
 
 /* CRG����ʱ���ſ� */
HI_VOID VICAP_HAL_SetBusClken(HI_BOOL bEnable)
{
    U_PERI_CRG55 PERI_CRG55;

    PERI_CRG55.u32 = g_pstRegCrg->PERI_CRG55.u32;

    PERI_CRG55.bits.vi_bus_cken = bEnable;

    g_pstRegCrg->PERI_CRG55.u32 = PERI_CRG55.u32;
}

/* CRG PT ʱ���ſ� */
HI_VOID VICAP_HAL_SetPtClken(HI_U32 u32PtIndex, HI_BOOL bEnable)
{
    U_PERI_CRG55 PERI_CRG55;

    PERI_CRG55.u32 = g_pstRegCrg->PERI_CRG55.u32;

    if(VICAP_PHYPT_PT0 == u32PtIndex)
    {
        PERI_CRG55.bits.vi_p0_cken = bEnable;
    }

    if(VICAP_PHYPT_PT1 == u32PtIndex)
    {
        PERI_CRG55.bits.vi_p1_cken = bEnable;
    }

    g_pstRegCrg->PERI_CRG55.u32 = PERI_CRG55.u32;
}

 /* CRG PPC ʱ���ſ� */
HI_VOID VICAP_HAL_SetPpcClken(HI_U32 u32ChnIndex, HI_BOOL bEnable)
{
    U_PERI_CRG55 PERI_CRG55;

    PERI_CRG55.u32 = g_pstRegCrg->PERI_CRG55.u32;

    if(VICAP_PHYCHN_CHN0 == u32ChnIndex)
    {
        PERI_CRG55.bits.vi_ppc0_cken = bEnable;
    }

    if(VICAP_PHYCHN_CHN1 == u32ChnIndex)
    {
        PERI_CRG55.bits.vi_ppc1_cken = bEnable;
    }

    g_pstRegCrg->PERI_CRG55.u32 = PERI_CRG55.u32;
}


  /* CRG���߸�λ */
HI_VOID VICAP_HAL_SetBusReset(HI_BOOL bEnable)
{
     /*оƬ���ƣ����ܸ�λ���߼Ĵ���*/
    U_PERI_CRG55 PERI_CRG55;

    PERI_CRG55.u32 = g_pstRegCrg->PERI_CRG55.u32;

    PERI_CRG55.bits.vi_bus_srst_req = bEnable;

    g_pstRegCrg->PERI_CRG55.u32 = PERI_CRG55.u32;
}

 /* CRG PT ��λ */
HI_VOID VICAP_HAL_SetPtReset(HI_U32 u32PtIndex, HI_BOOL bEnable)
{
    U_PERI_CRG55 PERI_CRG55;

    PERI_CRG55.u32 = g_pstRegCrg->PERI_CRG55.u32;

    if(VICAP_PHYPT_PT0 == u32PtIndex)
    {
        PERI_CRG55.bits.vi_p0_srst_req = bEnable;
    }

    if(VICAP_PHYPT_PT1 == u32PtIndex)
    {
        PERI_CRG55.bits.vi_p1_srst_req = bEnable;
    }

    g_pstRegCrg->PERI_CRG55.u32 = PERI_CRG55.u32;
}
 
  /* CRG PPC ��λ */
HI_VOID VICAP_HAL_SetPpcReset(HI_U32 u32ChnIndex, HI_BOOL bEnable)
{
    U_PERI_CRG55 PERI_CRG55;

    PERI_CRG55.u32 = g_pstRegCrg->PERI_CRG55.u32;

    if(VICAP_PHYCHN_CHN0 == u32ChnIndex)
    {
        PERI_CRG55.bits.vi_ppc0_srst_req = bEnable;
    }

    if(VICAP_PHYCHN_CHN1 == u32ChnIndex)
    {
        PERI_CRG55.bits.vi_ppc1_srst_req = bEnable;
    }

    g_pstRegCrg->PERI_CRG55.u32 = PERI_CRG55.u32;
}

 /* �͹��Ĺ���ģʽ*/
 static HI_VOID VicapHalWorkMode(HI_BOOL bLowPower)
 {
     U_WK_MODE o_wk_mode, *po_wk_mode = NULL;
     po_wk_mode = (U_WK_MODE *)(&g_pstVicapAllReg->stGlobalReg.WK_MODE);
     o_wk_mode.u32 = 1;
     o_wk_mode.bits.power_mode = bLowPower;
     po_wk_mode->u32 = o_wk_mode.u32;
     
     VicapVerifyRegWrite((unsigned int *)&(po_wk_mode->u32), o_wk_mode.u32, "U_WK_MODE");
 }
 
 
 /* AXI OUTSTANDING*/
 static HI_VOID VicapHalSetAxiCfg(VICAP_OUT_STANDING_E enOutStanding)
 {
     U_AXI_CFG o_axi_cfg, *po_axi_cfg = NULL;
     po_axi_cfg = (U_AXI_CFG *)(&g_pstVicapAllReg->stGlobalReg.AXI_CFG);
     o_axi_cfg.u32 = po_axi_cfg->u32;
     o_axi_cfg.bits.outstanding = enOutStanding;
     po_axi_cfg->u32 = o_axi_cfg.u32;
     
     VicapVerifyRegWrite((unsigned int *)&(po_axi_cfg->u32), o_axi_cfg.u32, "U_AXI_CFG");
 }

  /* �͹��Ĺ���ģʽ����ʱû��ʹ��*/
 static HI_VOID VicapHalSetMacCfg(HI_BOOL bLower)
 {
    U_MAC_CFG o_mac_cfg,*po_mac_cfg = NULL;
    po_mac_cfg = (U_MAC_CFG *)(&g_pstVicapAllReg->stGlobalReg.MAC_CFG);
    o_mac_cfg.u32 = 0;
    if(HI_FALSE == bLower)
    {
        o_mac_cfg.bits.req_prio = 0xff;
    }

    if(HI_TRUE == bLower)
    {
        o_mac_cfg.bits.req_prio = 0;
    }
    po_mac_cfg->u32 = o_mac_cfg.u32;
     
    VicapVerifyRegWrite((unsigned int *)&(po_mac_cfg->u32), o_mac_cfg.u32, "U_MAC_CFG");
 }

 /* ��ʼ�� */
HI_S32 VICAP_HAL_BoardInit(HI_VOID)
{
    g_pstVicapAllReg  = (VICAP_REGS_TYPE_S*)ioremap_nocache(VICAP_REGS_ADDR, VICAP_REGS_SIZE);

    if (NULL == g_pstVicapAllReg)
    {
        printk("ioremap_nocache failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/* ȥ��ʼ���Ĵ��� */
HI_VOID VICAP_HAL_BoardDeInit(HI_VOID)
{    
    if (g_pstVicapAllReg != NULL)
    {
        iounmap(g_pstVicapAllReg);
        g_pstVicapAllReg = NULL;
    }    
}

/*�˿�ʱ��ѡ��*/
HI_VOID VICAP_HAL_SetPtClk(HI_U32 u32PtIndex)
{
    U_PT_SEL  o_pt_sel,*po_pt_sel = NULL;
   
    po_pt_sel = (U_PT_SEL *)(&g_pstVicapAllReg->stGlobalReg.PT_SEL);
    o_pt_sel.u32 = po_pt_sel->u32;
    if(VICAP_PHYPT_PT0 == u32PtIndex)
    {
        o_pt_sel.bits.pt0_sel = 0;
    }
    if(VICAP_PHYPT_PT1 == u32PtIndex)
    {
        o_pt_sel.bits.pt1_sel = 0;
    }

    po_pt_sel->u32 = o_pt_sel.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_pt_sel->u32), o_pt_sel.u32, "U_PT_SEL");
}

/*ͨ��ʱ��ѡ��*/
HI_VOID VICAP_HAL_SetChnClk(HI_U32 u32PtIndex,HI_U32 u32ChnIndex)
{
    U_CH_SEL  o_ch_sel,*po_ch_sel = NULL;
   
    po_ch_sel = (U_CH_SEL *)(&g_pstVicapAllReg->stGlobalReg.CH_SEL);
    o_ch_sel.u32 = po_ch_sel->u32;    
    if(VICAP_PHYCHN_CHN0 == (1 << u32ChnIndex))
    {
      o_ch_sel.bits.ch0_sel = u32PtIndex;  
    }
    
    if(VICAP_PHYCHN_CHN1 == (1 << u32ChnIndex))
    {
      o_ch_sel.bits.ch1_sel = u32PtIndex;  
    }   

    po_ch_sel->u32 = o_ch_sel.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_ch_sel->u32), o_ch_sel.u32, "U_CH_SEL");
}


/*����ж�*/
HI_VOID VICAP_HAL_ClrChnIntStatus(HI_U32 s32ChnIndex, HI_U32 u32ClrInt)
{
    U_CH_INT *po_ch_int = NULL;
    /*�����Ĵ���*/
    po_ch_int = (U_CH_INT *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_INT);
    po_ch_int->u32 = u32ClrInt;
    
    VicapVerifyRegWrite((unsigned int *)&(po_ch_int->u32), u32ClrInt, "U_CH_INT");
}


/*��ȡ�ж�״̬*/
HI_S32 VICAP_HAL_GetChnIntStatus(HI_U32 s32ChnIndex)
{
    U_CH_INT *po_ch_int = NULL;
    
    po_ch_int = (U_CH_INT *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_INT);
    return po_ch_int->u32;
}

/* ʹ��/����ͨ�� */
HI_VOID VICAP_HAL_SetChnEn(HI_U32 s32ChnIndex, HI_BOOL bEn)
{
    U_CH_CTRL o_ch_ctrl, *po_ch_ctrl = NULL;
  
    po_ch_ctrl = (U_CH_CTRL *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CTRL);
    o_ch_ctrl.u32 = 0;
    o_ch_ctrl.bits.enable = bEn;
    po_ch_ctrl->u32 = o_ch_ctrl.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_ch_ctrl->u32), o_ch_ctrl.u32, "U_CH_CTRL");
}


/* ��ȡͨ��ʹ��״̬ */
HI_S32 VICAP_HAL_GetChnEnStatus(HI_U32 s32ChnIndex)
{
    U_CH_CTRL  *po_ch_ctrl = NULL;
   
    po_ch_ctrl = (U_CH_CTRL *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CTRL);
    return po_ch_ctrl->u32;

}

/* ��ȡ��ǰ���Ƿ�Ϊ����(�泡)�������ź���Ч */
VICAP_FRAME_FILED_E VICAP_HAL_IsTopField(HI_U32 u32PtIndex)
{
    VICAP_FRAME_FILED_E enFrameFiled;
    if(!(g_pstVicapAllReg->stPortReg[u32PtIndex].PT_STATUS.bits.field))
    {
        enFrameFiled = VICAP_FRAME_FILED_BOTTOM;
    }
    else
    {
        enFrameFiled = VICAP_FRAME_FILED_TOP;
    }
    return enFrameFiled;
}

/*��ȡ�˿��Ƿ�ʹ��*/
HI_S32  VICAP_HAL_GetPtIntfMode(HI_U32 s32PtIndex)
{
    U_PT_INTF_MOD *po_pt_intf_mod = NULL;
    
    po_pt_intf_mod = (U_PT_INTF_MOD *)(&g_pstVicapAllReg->stPortReg[s32PtIndex].PT_INTF_MOD);
    return po_pt_intf_mod->u32;
    
}

/* VIȫ���ж�CHN mask */
HI_VOID VICAP_HAL_SetVicapIntChnMask(HI_U32 u32ChnIndex,HI_BOOL bValid)
{
    U_VICAP_INT_MASK o_vicap_int_mask, *po_vicap_int_mask = NULL;

    po_vicap_int_mask = (U_VICAP_INT_MASK *)(&g_pstVicapAllReg->stGlobalReg.VICAP_INT_MASK);
    o_vicap_int_mask.u32 = po_vicap_int_mask->u32;
    if(0 == u32ChnIndex)
    {
       o_vicap_int_mask.bits.int_ch0 = bValid; 
    }

    if(1 == u32ChnIndex)
    {
       o_vicap_int_mask.bits.int_ch1 = bValid; 
    }

    po_vicap_int_mask->u32 = o_vicap_int_mask.u32;
    VicapVerifyRegWrite((unsigned int *)&(po_vicap_int_mask->u32), o_vicap_int_mask.u32, "U_VICAP_INT_MASK");
}
/* VIȫ���ж� PT mask */
HI_VOID VICAP_HAL_SetVicapIntPtMask(HI_U32 u32PtIndex,HI_BOOL bValid)
{
    U_VICAP_INT_MASK o_vicap_int_mask, *po_vicap_int_mask = NULL;

    po_vicap_int_mask = (U_VICAP_INT_MASK *)(&g_pstVicapAllReg->stGlobalReg.VICAP_INT_MASK);
    o_vicap_int_mask.u32 = po_vicap_int_mask->u32;
    if(0 == u32PtIndex)
    {
       o_vicap_int_mask.bits.int_pt0 = bValid; 
    }

    if(1 == u32PtIndex)
    {
       o_vicap_int_mask.bits.int_pt1 = bValid; 
    }

    po_vicap_int_mask->u32 = o_vicap_int_mask.u32;
    VicapVerifyRegWrite((unsigned int *)&(po_vicap_int_mask->u32), o_vicap_int_mask.u32, "U_VICAP_INT_MASK");
}

/*ͨ���ж�mask*/
HI_VOID VICAP_HAL_SetChnIntMask(HI_U32 s32ChnIndex, HI_U32 u32IntMask)
{
    U_CH_INT_MASK *po_ch_int_mask = NULL;

    po_ch_int_mask = (U_CH_INT_MASK *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_INT_MASK);
    po_ch_int_mask->u32 = u32IntMask;

    VicapVerifyRegWrite((unsigned int *)&(po_ch_int_mask->u32), u32IntMask, "U_CH_INT_MASK");
}

/* ���ýӿ��Ƿ��ϲ�����YUV444 */
HI_VOID VICAP_HAL_SetPortUpToYuv444(HI_U32 u32PtIndex,HI_BOOL bUptoYuv444)
{
    U_PT_YUV444_CFG o_pt_yuv444_cfg, *po_pt_yuv444_cfg = NULL;
    
    po_pt_yuv444_cfg = (U_PT_YUV444_CFG *)(&g_pstVicapAllReg->stPortReg[u32PtIndex].PT_YUV444_CFG);
    o_pt_yuv444_cfg.u32 = po_pt_yuv444_cfg->u32;
    o_pt_yuv444_cfg.bits.enable = bUptoYuv444;
    po_pt_yuv444_cfg->u32 = o_pt_yuv444_cfg.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_pt_yuv444_cfg->u32), o_pt_yuv444_cfg.u32, "U_PT_YUV444_CFG");
}


/* ���ýӿ�ģʽ */
HI_VOID VICAP_HAL_SetPortIntfMode(HI_U32 u32PtIndex,VICAP_INTF_MODE_E enIntfMode)
{
    U_PT_INTF_MOD o_pt_intf_mod, *po_pt_intf_mod = NULL;
    
    po_pt_intf_mod = (U_PT_INTF_MOD *)(&g_pstVicapAllReg->stPortReg[u32PtIndex].PT_INTF_MOD);
    o_pt_intf_mod.u32 = po_pt_intf_mod->u32;
    o_pt_intf_mod.bits.mode = enIntfMode;
    po_pt_intf_mod->u32 = o_pt_intf_mod.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_pt_intf_mod->u32), o_pt_intf_mod.u32, "U_INTF_MOD");
}

/* ���ö˿ڵķ���ģʽ */
HI_VOID VICAP_HAL_SetPortCompMode(HI_U32 u32PtIndex,VICAP_COMP_MODE_E enCompMode)
{
    U_PT_UNIFY_DATA_CFG o_pt_unify_data_cfg, *po_pt_unify_data_cfg = NULL;
    
    po_pt_unify_data_cfg = (U_PT_UNIFY_DATA_CFG *)(&g_pstVicapAllReg->stPortReg[u32PtIndex].PT_UNIFY_DATA_CFG);
    o_pt_unify_data_cfg.u32 = 0;
    o_pt_unify_data_cfg.bits.comp_num = enCompMode;
    if (VICAP_COMP_MODE_SINGLE == enCompMode)
    {
        o_pt_unify_data_cfg.bits.enable = HI_FALSE;
    }
    else
    {
        o_pt_unify_data_cfg.bits.enable = HI_TRUE;
    }
    po_pt_unify_data_cfg->u32 = o_pt_unify_data_cfg.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_pt_unify_data_cfg->u32), o_pt_unify_data_cfg.u32, "U_PT_UNIFY_DATA_CFG");
}


/* ���ö˿���������ƫ��/���� */
HI_VOID VICAP_HAL_SetPortDataLayout(HI_U32 u32PtIndex,HI_U32 au32Offset[3], HI_U32 au32CompMask[3])
{
    U_PT_OFFSET0 o_pt_offset0, *po_pt_offset0 = NULL;
    U_PT_OFFSET1 o_pt_offset1, *po_pt_offset1 = NULL;
    U_PT_OFFSET2 o_pt_offset2, *po_pt_offset2 = NULL;
    
    po_pt_offset0 = (U_PT_OFFSET0 *)(&g_pstVicapAllReg->stPortReg[u32PtIndex].PT_OFFSET0);
    o_pt_offset0.u32 = 0;
    o_pt_offset0.bits.offset = au32Offset[0];
    o_pt_offset0.bits.mask = au32CompMask[0];
    po_pt_offset0->u32 = o_pt_offset0.u32;
    
    po_pt_offset1 = (U_PT_OFFSET1 *)(&g_pstVicapAllReg->stPortReg[u32PtIndex].PT_OFFSET1);
    o_pt_offset1.u32 = 0;
    o_pt_offset1.bits.offset = au32Offset[1];
    o_pt_offset1.bits.mask = au32CompMask[1];
    po_pt_offset1->u32 = o_pt_offset1.u32;
    
    po_pt_offset2 = (U_PT_OFFSET2 *)(&g_pstVicapAllReg->stPortReg[u32PtIndex].PT_OFFSET2);
    o_pt_offset2.u32 = 0;    
    o_pt_offset2.bits.offset = au32Offset[2];
    o_pt_offset2.bits.mask = au32CompMask[2];    
    po_pt_offset2->u32 = o_pt_offset2.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_pt_offset0->u32), o_pt_offset0.u32, "U_PT_OFFSET0");
    VicapVerifyRegWrite((unsigned int *)&(po_pt_offset1->u32), o_pt_offset1.u32, "U_PT_OFFSET1");
    VicapVerifyRegWrite((unsigned int *)&(po_pt_offset2->u32), o_pt_offset2.u32, "U_PT_OFFSET2");
}


/* ���ö˿�FVHDEͬ���źŵ����� */
HI_VOID VICAP_HAL_SetPortSyncCfg(HI_U32 u32PtIndex,VICAP_SYNC_CFG_S *pstSyncCfg)
{
    U_PT_UNIFY_TIMING_CFG o_pt_unify_timing_cfg, *po_pt_unify_timing_cfg = NULL;
    
    po_pt_unify_timing_cfg = (U_PT_UNIFY_TIMING_CFG *)(&g_pstVicapAllReg->stPortReg[u32PtIndex].PT_UNIFY_TIMING_CFG);
    o_pt_unify_timing_cfg.u32 = 0;
    
    o_pt_unify_timing_cfg.bits.field_inv = pstSyncCfg->bFieldInv;
    o_pt_unify_timing_cfg.bits.field_sel = pstSyncCfg->enFieldSel;
    o_pt_unify_timing_cfg.bits.vsync_mode = pstSyncCfg->enVsyncMode;
    o_pt_unify_timing_cfg.bits.vsync_inv = pstSyncCfg->bVsyncInv;
    o_pt_unify_timing_cfg.bits.vsync_sel = pstSyncCfg->enVsyncSel;
    o_pt_unify_timing_cfg.bits.hsync_mode = pstSyncCfg->enHsyncMode;
    o_pt_unify_timing_cfg.bits.hsync_and = pstSyncCfg->enHsyncAnd;
    o_pt_unify_timing_cfg.bits.hsync_inv = pstSyncCfg->bHsyncInv;
    o_pt_unify_timing_cfg.bits.hsync_sel = pstSyncCfg->enHsyncSel;
    o_pt_unify_timing_cfg.bits.de_inv = pstSyncCfg->bDeInv;
    o_pt_unify_timing_cfg.bits.de_sel = pstSyncCfg->enDeSel;
    
    po_pt_unify_timing_cfg->u32 = o_pt_unify_timing_cfg.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_pt_unify_timing_cfg->u32), o_pt_unify_timing_cfg.u32, "U_PT_UNIFY_TIMING_CFG");
}

/* ���ö˿��ж�mask */
HI_VOID VICAP_HAL_SetPortIntMask(HI_U32 u32PtIndex,HI_U32 u32IntMask)
{
    U_PT_INT_MASK *po_pt_int_mask = NULL;
    
    po_pt_int_mask = (U_PT_INT_MASK *)(&g_pstVicapAllReg->stPortReg[u32PtIndex].PT_INT_MASK);
    po_pt_int_mask->u32 = u32IntMask;    
    VicapVerifyRegWrite((unsigned int *)&(po_pt_int_mask->u32), u32IntMask, "U_PT_INT_MASK");
}


/* ����/ʹ�ܶ˿� */
HI_VOID VICAP_HAL_SetPortEn(HI_U32 u32PtIndex,HI_BOOL bEnalbe)
{
    U_PT_INTF_MOD o_pt_intf_mod, *po_pt_intf_mod = NULL;

    po_pt_intf_mod = (U_PT_INTF_MOD *)(&g_pstVicapAllReg->stPortReg[u32PtIndex].PT_INTF_MOD);
    o_pt_intf_mod.u32 = po_pt_intf_mod->u32;
    o_pt_intf_mod.bits.enable = bEnalbe;
    po_pt_intf_mod->u32 = o_pt_intf_mod.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_pt_intf_mod->u32), o_pt_intf_mod.u32, "U_INTF_MOD");
}

/*Y�������*/
HI_VOID VICAP_HAL_SetWchYStride(HI_U32 s32ChnIndex, HI_U32 u32YStride)
{
    U_CH_WCH_Y_STRIDE o_ch_wch_y_stride, *po_ch_wch_y_stride = NULL;

    po_ch_wch_y_stride = (U_CH_WCH_Y_STRIDE *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_WCH_Y_STRIDE);
    o_ch_wch_y_stride.u32 = 0;
    o_ch_wch_y_stride.bits.stride = u32YStride;
    po_ch_wch_y_stride->u32 = o_ch_wch_y_stride.u32;

    VicapVerifyRegWrite((unsigned int *)&(po_ch_wch_y_stride->u32), o_ch_wch_y_stride.u32, "U_CH_WCH_Y_STRIDE");    
}  

/*C�������*/
HI_VOID VICAP_HAL_SetWchCStride(HI_U32 s32ChnIndex, HI_U32 u32CStride)
{
    U_CH_WCH_C_STRIDE o_ch_wch_c_stride, *po_ch_wch_c_stride = NULL;
  
    po_ch_wch_c_stride = (U_CH_WCH_C_STRIDE *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_WCH_C_STRIDE); 
    o_ch_wch_c_stride.u32 = 0;    
    o_ch_wch_c_stride.bits.stride = u32CStride;    
    po_ch_wch_c_stride->u32 = o_ch_wch_c_stride.u32;

  
    VicapVerifyRegWrite((unsigned int *)&(po_ch_wch_c_stride->u32), o_ch_wch_c_stride.u32, "U_CH_WCH_C_STRIDE");
}

HI_VOID VICAP_HAL_SetChnWchSize(HI_U32 s32ChnIndex,HI_U32 u32Width, HI_U32 u32Height,VICAP_WCH_MODE_E enWchMode)
{
    U_CH_WCH_Y_SIZE o_ch_wch_y_size,*po_ch_wch_y_size = NULL;
    U_CH_WCH_C_SIZE o_ch_wch_c_size,*po_ch_wch_c_size = NULL;

    if(VICAP_WCH_MODE_Y == enWchMode)
    {
        po_ch_wch_y_size = (U_CH_WCH_Y_SIZE *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_WCH_Y_SIZE);
        o_ch_wch_y_size.u32 = 0;
        o_ch_wch_y_size.bits.width = u32Width - 1;
        o_ch_wch_y_size.bits.height = u32Height - 1;
        po_ch_wch_y_size->u32 = o_ch_wch_y_size.u32;
        
        VicapVerifyRegWrite((unsigned int *)&(po_ch_wch_y_size->u32), o_ch_wch_y_size.u32, "U_CH_WCH_Y_SIZE");
    }

    if(VICAP_WCH_MODE_C== enWchMode)
    {
        po_ch_wch_c_size = (U_CH_WCH_C_SIZE *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_WCH_C_SIZE);
        o_ch_wch_c_size.u32 = 0;
        o_ch_wch_c_size.bits.width = u32Width -1 ;
        o_ch_wch_c_size.bits.height = u32Height - 1;
        po_ch_wch_c_size->u32 = o_ch_wch_c_size.u32;
        
        VicapVerifyRegWrite((unsigned int *)&(po_ch_wch_c_size->u32), o_ch_wch_c_size.u32, "U_CH_WCH_C_SIZE");
    }
}
HI_VOID VICAP_HAL_SetChnWchCfg(HI_U32 s32ChnIndex,VICAP_CHN_WCH_CFG_S *stWchCfg,VICAP_WCH_MODE_E enWchMode)
{
    U_CH_WCH_Y_CFG  o_ch_wch_y_cfg,*po_ch_wch_y_cfg = NULL;
    U_CH_WCH_C_CFG  o_ch_wch_c_cfg,*po_ch_wch_c_cfg = NULL;

    if(VICAP_WCH_MODE_Y == enWchMode)
    {
        po_ch_wch_y_cfg = (U_CH_WCH_Y_CFG *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_WCH_Y_CFG);
        o_ch_wch_y_cfg.u32 = 0;
        o_ch_wch_y_cfg.bits.cmp_en = 0;
        o_ch_wch_y_cfg.bits.bit_width = stWchCfg->enDstBitWidth;
        o_ch_wch_y_cfg.bits.bfield = stWchCfg->enField;
        o_ch_wch_y_cfg.bits.interleave = stWchCfg->bInterlace;
        po_ch_wch_y_cfg->u32 = o_ch_wch_y_cfg.u32;
        
        VicapVerifyRegWrite((unsigned int *)&(po_ch_wch_y_cfg->u32), o_ch_wch_y_cfg.u32, "U_CH_WCH_Y_CFG");
    }

    if(VICAP_WCH_MODE_C== enWchMode)
    {
        po_ch_wch_c_cfg = (U_CH_WCH_C_CFG *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_WCH_C_CFG);
        o_ch_wch_c_cfg.u32 = 0;
        o_ch_wch_c_cfg.bits.cmp_en = 0;
        o_ch_wch_c_cfg.bits.bit_width = stWchCfg->enDstBitWidth;
        o_ch_wch_c_cfg.bits.bfield = stWchCfg->enField;
        o_ch_wch_c_cfg.bits.interleave = stWchCfg->bInterlace;
        po_ch_wch_c_cfg->u32 = o_ch_wch_c_cfg.u32;
        
        VicapVerifyRegWrite((unsigned int *)&(po_ch_wch_c_cfg->u32), o_ch_wch_c_cfg.u32, "U_CH_WCH_C_CFG");

    }
}
HI_VOID VICAP_HAL_SetChnWchAddr(HI_U32 s32ChnIndex,VICAP_ADDR_S *stVicapAddr,VICAP_WCH_MODE_E enWchMode)
{
    U_CH_WCH_Y_FADDR o_ch_wch_y_faddr, *po_ch_wch_y_faddr = NULL;
    U_CH_WCH_C_FADDR o_ch_wch_c_faddr, *po_ch_wch_c_faddr = NULL;

    if(VICAP_WCH_MODE_Y == enWchMode)
    {
        po_ch_wch_y_faddr = (U_CH_WCH_Y_FADDR *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_WCH_Y_FADDR);
        o_ch_wch_y_faddr.u32 = 0;
        o_ch_wch_y_faddr.bits.faddr = stVicapAddr->u32YAddr;
        po_ch_wch_y_faddr->u32 = o_ch_wch_y_faddr.u32;
        
        VicapVerifyRegWrite((unsigned int *)&(po_ch_wch_y_faddr->u32), o_ch_wch_y_faddr.u32, "U_CH_WCH_Y_FADDR");
    }

    if(VICAP_WCH_MODE_C== enWchMode)
    {
        po_ch_wch_c_faddr = (U_CH_WCH_C_FADDR *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_WCH_C_FADDR);
        o_ch_wch_c_faddr.u32 = 0;
        o_ch_wch_c_faddr.bits.faddr = stVicapAddr->u32CAddr;
        po_ch_wch_c_faddr->u32 = o_ch_wch_c_faddr.u32;
        
        VicapVerifyRegWrite((unsigned int *)&(po_ch_wch_c_faddr->u32), o_ch_wch_c_faddr.u32, "U_CH_WCH_C_FADDR");

    }
}

/* 
 * ����ͨ���ü�����
 * ͼ��һ�еĿ��(������Ϊ��λ)������ֵΪʵ��ֵ��1 
 * ��ȡͼ��ĸ߶�(����Ϊ��λ)������ֵΪʵ��ֵ��1
 */
HI_VOID VICAP_HAL_SetChnCrop(HI_U32 s32ChnIndex, VICAP_CROP_CFG_S *pstCropCfg)
{
    U_CH_CROP_CFG o_ch_crop_cfg, *po_ch_crop_cfg = NULL;
    U_CH_CROP0_START o_ch_crop0_start, *po_ch_crop0_start = NULL;
    U_CH_CROP0_SIZE o_ch_crop0_size, *po_ch_crop0_size = NULL;
    U_CH_CROP1_START o_ch_crop1_start, *po_ch_crop1_start = NULL;
    U_CH_CROP1_SIZE o_ch_crop1_size, *po_ch_crop1_size = NULL;  
    
    if (pstCropCfg->bCropEn[0])
    {
        po_ch_crop0_start = (U_CH_CROP0_START *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CROP0_START);
        o_ch_crop0_start.u32 = 0;
        o_ch_crop0_start.bits.x_start = pstCropCfg->stCropRect[0].s32X;
        o_ch_crop0_start.bits.y_start = pstCropCfg->stCropRect[0].s32Y;
        po_ch_crop0_start->u32 = o_ch_crop0_start.u32;
        
        po_ch_crop0_size = (U_CH_CROP0_SIZE *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CROP0_SIZE);     
        o_ch_crop0_size.u32 = 0;       
        o_ch_crop0_size.bits.width = pstCropCfg->stCropRect[0].s32Width - 1;
        o_ch_crop0_size.bits.height = pstCropCfg->stCropRect[0].s32Height - 1;        
        po_ch_crop0_size->u32 = o_ch_crop0_size.u32;

        VicapVerifyRegWrite((unsigned int *)&(po_ch_crop0_start->u32), o_ch_crop0_start.u32, "U_CH_CROP0_START");
        VicapVerifyRegWrite((unsigned int *)&(po_ch_crop0_size->u32), o_ch_crop0_size.u32, "U_CH_CROP0_SIZE");
    }
    
    if (pstCropCfg->bCropEn[1])
    {
        po_ch_crop1_start = (U_CH_CROP1_START *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CROP1_START);
        o_ch_crop1_start.u32 = 0;
        o_ch_crop1_start.bits.x_start = pstCropCfg->stCropRect[1].s32X;
        o_ch_crop1_start.bits.y_start = pstCropCfg->stCropRect[1].s32Y;
        po_ch_crop1_start->u32 = o_ch_crop1_start.u32;

        po_ch_crop1_size = (U_CH_CROP1_SIZE *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CROP1_SIZE);
        o_ch_crop1_size.u32 = 0;
        o_ch_crop1_size.bits.width = pstCropCfg->stCropRect[1].s32Width - 1;
        o_ch_crop1_size.bits.height = pstCropCfg->stCropRect[1].s32Height - 1;
        po_ch_crop1_size->u32 = o_ch_crop1_size.u32;

        VicapVerifyRegWrite((unsigned int *)&(po_ch_crop1_start->u32), o_ch_crop1_start.u32, "U_CH_CROP1_START");
        VicapVerifyRegWrite((unsigned int *)&(po_ch_crop1_size->u32), o_ch_crop1_size.u32, "U_CH_CROP1_SIZE");
    }

    po_ch_crop_cfg = (U_CH_CROP_CFG *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CROP_CFG);
    o_ch_crop_cfg.u32 = 0;
    o_ch_crop_cfg.bits.n0_en = pstCropCfg->bCropEn[0];
    o_ch_crop_cfg.bits.n1_en = pstCropCfg->bCropEn[1];
    po_ch_crop_cfg->u32 = o_ch_crop_cfg.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_ch_crop_cfg->u32), o_ch_crop_cfg.u32, "U_CH_CROP_CFG");    
}

/*CSCʹ��*/
HI_VOID VICAP_HAL_SetChnCscEn(HI_U32 s32ChnIndex, HI_BOOL bEnableCsc)
{
    U_CH_CSC_CFG o_ch_csc_cfg, *po_ch_csc_cfg = HI_NULL;
    
    po_ch_csc_cfg = (U_CH_CSC_CFG *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CSC_CFG);
    o_ch_csc_cfg.u32 = po_ch_csc_cfg->u32;
    o_ch_csc_cfg.bits.enable = bEnableCsc;
    po_ch_csc_cfg->u32 = o_ch_csc_cfg.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_ch_csc_cfg->u32), o_ch_csc_cfg.u32, "U_CH_CSC_CFG"); 
}

/*����CSC����*/
HI_VOID VICAP_HAL_SetChnCsc(HI_U32 s32ChnIndex, VICAP_CSC_COEF_S *pstVicapCSCCoef, VICAP_CSC_DCCOEF_S *pstVicapCSCDCCoef)
{    
    U_CH_CSC_COEF0   o_ch_csc_coef0,   *po_ch_csc_coef0;
    U_CH_CSC_COEF1   o_ch_csc_coef1,   *po_ch_csc_coef1;
    U_CH_CSC_COEF2   o_ch_csc_coef2,   *po_ch_csc_coef2;
    U_CH_CSC_COEF3   o_ch_csc_coef3,   *po_ch_csc_coef3;
    U_CH_CSC_COEF4   o_ch_csc_coef4,   *po_ch_csc_coef4;
    U_CH_CSC_IN_DC0  o_ch_csc_in_dc0,  *po_ch_csc_in_dc0;
    U_CH_CSC_IN_DC1  o_ch_csc_in_dc1,  *po_ch_csc_in_dc1;
    U_CH_CSC_OUT_DC0 o_ch_csc_out_dc0, *po_ch_csc_out_dc0;
    U_CH_CSC_OUT_DC1 o_ch_csc_out_dc1, *po_ch_csc_out_dc1;

    po_ch_csc_coef0 = (U_CH_CSC_COEF0 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CSC_COEF0);
    po_ch_csc_coef1 = (U_CH_CSC_COEF1 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CSC_COEF1);
    po_ch_csc_coef2 = (U_CH_CSC_COEF2 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CSC_COEF2);
    po_ch_csc_coef3 = (U_CH_CSC_COEF3 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CSC_COEF3);
    po_ch_csc_coef4 = (U_CH_CSC_COEF4 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CSC_COEF4);
    po_ch_csc_in_dc0 = (U_CH_CSC_IN_DC0 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CSC_IN_DC0);
    po_ch_csc_in_dc1 = (U_CH_CSC_IN_DC1 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CSC_IN_DC1);
    po_ch_csc_out_dc0 = (U_CH_CSC_OUT_DC0 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CSC_OUT_DC0);
    po_ch_csc_out_dc1 = (U_CH_CSC_OUT_DC1 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CSC_OUT_DC1);

    o_ch_csc_coef0.u32 = po_ch_csc_coef0->u32;
    o_ch_csc_coef1.u32 = po_ch_csc_coef1->u32;
    o_ch_csc_coef2.u32 = po_ch_csc_coef2->u32;
    o_ch_csc_coef3.u32 = po_ch_csc_coef3->u32;
    o_ch_csc_coef4.u32 = po_ch_csc_coef4->u32;
    o_ch_csc_in_dc0.u32 = po_ch_csc_in_dc0->u32;
    o_ch_csc_in_dc1.u32 = po_ch_csc_in_dc1->u32;
    o_ch_csc_out_dc0.u32 = po_ch_csc_out_dc0->u32;
    o_ch_csc_out_dc1.u32 = po_ch_csc_out_dc1->u32;

    o_ch_csc_coef0.bits.coef00 = pstVicapCSCCoef->csc_coef00;
    o_ch_csc_coef0.bits.coef01 = pstVicapCSCCoef->csc_coef01;
    o_ch_csc_coef1.bits.coef02 = pstVicapCSCCoef->csc_coef02;
    o_ch_csc_coef1.bits.coef10 = pstVicapCSCCoef->csc_coef10;
    o_ch_csc_coef2.bits.coef11 = pstVicapCSCCoef->csc_coef11;
    o_ch_csc_coef2.bits.coef12 = pstVicapCSCCoef->csc_coef12;
    o_ch_csc_coef3.bits.coef20 = pstVicapCSCCoef->csc_coef20;
    o_ch_csc_coef3.bits.coef21 = pstVicapCSCCoef->csc_coef21;
    o_ch_csc_coef4.bits.coef22 = pstVicapCSCCoef->csc_coef22;
    o_ch_csc_in_dc0.bits.in_dc0 = pstVicapCSCDCCoef->csc_in_dc0;
    o_ch_csc_in_dc0.bits.in_dc1 = pstVicapCSCDCCoef->csc_in_dc1;
    o_ch_csc_in_dc1.bits.in_dc2 = pstVicapCSCDCCoef->csc_in_dc2;
    o_ch_csc_out_dc0.bits.out_dc0 = pstVicapCSCDCCoef->csc_out_dc0;
    o_ch_csc_out_dc0.bits.out_dc1 = pstVicapCSCDCCoef->csc_out_dc1;
    o_ch_csc_out_dc1.bits.out_dc2 = pstVicapCSCDCCoef->csc_out_dc2;

    po_ch_csc_coef0->u32 = o_ch_csc_coef0.u32;
    po_ch_csc_coef1->u32 = o_ch_csc_coef1.u32;
    po_ch_csc_coef2->u32 = o_ch_csc_coef2.u32;
    po_ch_csc_coef3->u32 = o_ch_csc_coef3.u32;
    po_ch_csc_coef4->u32 = o_ch_csc_coef4.u32;
    po_ch_csc_in_dc0->u32 = o_ch_csc_in_dc0.u32;
    po_ch_csc_in_dc1->u32 = o_ch_csc_in_dc1.u32;
    po_ch_csc_out_dc0->u32 = o_ch_csc_out_dc0.u32;
    po_ch_csc_out_dc1->u32 = o_ch_csc_out_dc1.u32;

    VicapVerifyRegWrite((unsigned int *)&(po_ch_csc_coef0->u32), o_ch_csc_coef0.u32, "U_CH_CSC_COEF0"); 
    VicapVerifyRegWrite((unsigned int *)&(po_ch_csc_coef1->u32), o_ch_csc_coef1.u32, "U_CH_CSC_COEF1"); 
    VicapVerifyRegWrite((unsigned int *)&(po_ch_csc_coef2->u32), o_ch_csc_coef2.u32, "U_CH_CSC_COEF2"); 
    VicapVerifyRegWrite((unsigned int *)&(po_ch_csc_coef3->u32), o_ch_csc_coef3.u32, "U_CH_CSC_COEF3"); 
    VicapVerifyRegWrite((unsigned int *)&(po_ch_csc_coef4->u32), o_ch_csc_coef4.u32, "U_CH_CSC_COEF4"); 
    VicapVerifyRegWrite((unsigned int *)&(po_ch_csc_in_dc0->u32), o_ch_csc_in_dc0.u32, "U_CH_CSC_IN_DC0"); 
    VicapVerifyRegWrite((unsigned int *)&(po_ch_csc_in_dc1->u32), o_ch_csc_in_dc1.u32, "U_CH_CSC_IN_DC1"); 
    VicapVerifyRegWrite((unsigned int *)&(po_ch_csc_out_dc0->u32), o_ch_csc_out_dc0.u32, "U_CH_CSC_OUT_DC0"); 
    VicapVerifyRegWrite((unsigned int *)&(po_ch_csc_out_dc1->u32), o_ch_csc_out_dc1.u32, "U_CH_CSC_OUT_DC1");    
}

/* ����ͨ��������SKIP��Ϣ */
HI_VOID VICAP_HAL_SetSkipYCfg(HI_U32 s32ChnIndex, HI_U32 u32SkipCfg)
{
    HI_U32 *po_skip_y_cfg = NULL;

    po_skip_y_cfg = (HI_U32 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_SKIP_Y_CFG);
    *po_skip_y_cfg = u32SkipCfg;
    VicapVerifyRegWrite((unsigned int *)po_skip_y_cfg, u32SkipCfg, "CH_SKIP_Y_CFG");
}

/* ����ͨ����ɫ��SKIP��Ϣ*/
HI_VOID VICAP_HAL_SetSkipCCfg(HI_U32 s32ChnIndex, HI_U32 u32SkipCfg)
{
    HI_U32 *po_skip_c_cfg = NULL;

    po_skip_c_cfg = (HI_U32 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_SKIP_C_CFG);
    *po_skip_c_cfg = u32SkipCfg;
    VicapVerifyRegWrite((unsigned int *)po_skip_c_cfg, u32SkipCfg, "CH_SKIP_C_CFG");
}



/* ����ͨ�����¼Ĵ��� */
HI_VOID VICAP_HAL_SetRegNewer(HI_S32 s32ChnIndex)
{
    U_CH_REG_NEWER o_ch_reg_newer, *po_ch_reg_newer = NULL;
    
    po_ch_reg_newer = (U_CH_REG_NEWER *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_REG_NEWER);
    o_ch_reg_newer.u32 = 0;
    o_ch_reg_newer.bits.reg_newer = HI_TRUE;
    po_ch_reg_newer->u32 = o_ch_reg_newer.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_ch_reg_newer->u32), o_ch_reg_newer.u32, "U_CH_REG_NEWER");
}

/* ����ͨ��DITHERģʽ��Ϣ */
HI_VOID VICAP_HAL_SetDitherCfg(HI_U32 s32ChnIndex, VICAP_DITHER_CFG_E enDitherCfg)
{
    U_CH_DITHER_CFG o_ch_dither_cfg, *po_ch_dither_cfg = NULL;

    po_ch_dither_cfg = (U_CH_DITHER_CFG *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_DITHER_CFG);
    o_ch_dither_cfg.u32 = 0;
    o_ch_dither_cfg.bits.mode = enDitherCfg;
    o_ch_dither_cfg.bits.enable = HI_TRUE;
    po_ch_dither_cfg->u32 = o_ch_dither_cfg.u32;
    
    VicapVerifyRegWrite((unsigned int *)&(po_ch_dither_cfg->u32), o_ch_dither_cfg.u32, "U_CH_DITHER_CFG");
}

/*����ˮƽ����*/
HI_S32 VICAP_HAL_SetHScale(HI_U32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, HI_U32 u32Ratio, 
                               VICAP_CHN_SCALE_MODE_E enMode, HI_BOOL bMidEn, HI_BOOL bScaleEn)
{
    HI_S32 s32Ret = 0;
    U_CH_LHFIR_CFG o_ch_lhfir_cfg, *po_ch_lhfir_cfg = NULL;
    U_CH_CHFIR_CFG o_ch_chfir_cfg, *po_ch_chfir_cfg = NULL;

    if (VICAP_CHN_SCALE_OBJ_YH == enObj)
    {
        po_ch_lhfir_cfg = (U_CH_LHFIR_CFG*)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_LHFIR_CFG);
        o_ch_lhfir_cfg.u32 = po_ch_lhfir_cfg->u32;
        o_ch_lhfir_cfg.bits.ratio = u32Ratio;
        o_ch_lhfir_cfg.bits.fir_en = enMode;
        o_ch_lhfir_cfg.bits.mid_en = bMidEn;
        o_ch_lhfir_cfg.bits.enable = bScaleEn;
        po_ch_lhfir_cfg->u32 = o_ch_lhfir_cfg.u32;
        
        s32Ret = VicapVerifyRegWrite((unsigned int *)&(po_ch_lhfir_cfg->u32), o_ch_lhfir_cfg.u32, "U_CH_LHFIR_CFG");
    }
    else if (VICAP_CHN_SCALE_OBJ_CH == enObj)
    {
        po_ch_chfir_cfg = (U_CH_CHFIR_CFG*)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CHFIR_CFG);
        o_ch_chfir_cfg.u32 = po_ch_chfir_cfg->u32;
        o_ch_chfir_cfg.bits.ratio = u32Ratio;
        o_ch_chfir_cfg.bits.fir_en = enMode;
        o_ch_chfir_cfg.bits.mid_en = bMidEn;
        o_ch_chfir_cfg.bits.enable = bScaleEn;
        po_ch_chfir_cfg->u32 = o_ch_chfir_cfg.u32;
        
        s32Ret = VicapVerifyRegWrite((unsigned int *)&(po_ch_chfir_cfg->u32), o_ch_chfir_cfg.u32, "U_CH_CHFIR_CFG");
    }
    else
    {
        HI_ASSERT(0);
    }    

    return s32Ret;
}

/*���ô�ֱ����*/
HI_S32 VICAP_HAL_SetVScale(HI_U32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, HI_U32 u32Ratio,HI_BOOL bScaleEn)
{
    HI_S32 s32Ret = 0;
    U_CH_LVFIR_CFG o_ch_lvfir_cfg, *po_ch_lvfir_cfg = NULL;
    U_CH_CVFIR_CFG o_ch_cvfir_cfg, *po_ch_cvfir_cfg = NULL;

    if (VICAP_CHN_SCALE_OBJ_YH == enObj)
    {
        po_ch_lvfir_cfg = (U_CH_LVFIR_CFG*)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_LVFIR_CFG);
        o_ch_lvfir_cfg.u32 = po_ch_lvfir_cfg->u32;
        o_ch_lvfir_cfg.bits.ratio = u32Ratio;
        o_ch_lvfir_cfg.bits.enable = bScaleEn;
        po_ch_lvfir_cfg->u32 = o_ch_lvfir_cfg.u32;
        
        s32Ret = VicapVerifyRegWrite((unsigned int *)&(po_ch_lvfir_cfg->u32), o_ch_lvfir_cfg.u32, "U_CH_LVFIR_CFG");
    }
    else if (VICAP_CHN_SCALE_OBJ_CH == enObj)
    {
        po_ch_cvfir_cfg = (U_CH_CVFIR_CFG*)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CVFIR_CFG);
        o_ch_cvfir_cfg.u32 = po_ch_cvfir_cfg->u32;
        o_ch_cvfir_cfg.bits.ratio = u32Ratio;
        o_ch_cvfir_cfg.bits.enable = bScaleEn;
        po_ch_cvfir_cfg->u32 = o_ch_cvfir_cfg.u32;
        
        s32Ret = VicapVerifyRegWrite((unsigned int *)&(po_ch_cvfir_cfg->u32), o_ch_cvfir_cfg.u32, "U_CH_CVFIR_CFG");
    }
    else
    {
        HI_ASSERT(0);
    }    

    return s32Ret;
}


/* ˮƽ����ʹ�� */
HI_S32 VICAP_HAL_HScaleEn(HI_U32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, HI_BOOL bEn)
{
    HI_S32 s32Ret = 0;
    U_CH_LHFIR_CFG o_ch_lhfir_cfg, *po_ch_lhfir_cfg = NULL;
    U_CH_CHFIR_CFG o_ch_chfir_cfg, *po_ch_chfir_cfg = NULL;

    if (VICAP_CHN_SCALE_OBJ_YH == enObj)
    {
        po_ch_lhfir_cfg= (U_CH_LHFIR_CFG*)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_LHFIR_CFG);
        o_ch_lhfir_cfg.u32 = po_ch_lhfir_cfg->u32;
        o_ch_lhfir_cfg.bits.enable = bEn;
        po_ch_lhfir_cfg->u32 = o_ch_lhfir_cfg.u32;
        
        s32Ret = VicapVerifyRegWrite((unsigned int *)&(po_ch_lhfir_cfg->u32), o_ch_lhfir_cfg.u32, "U_CH_LHFIR_CFG");
    }
    else if (VICAP_CHN_SCALE_OBJ_CH == enObj)
    {
        po_ch_chfir_cfg= (U_CH_CHFIR_CFG*)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CHFIR_CFG);
        o_ch_chfir_cfg.u32 = po_ch_chfir_cfg->u32;
        o_ch_chfir_cfg.bits.enable = bEn;
        po_ch_chfir_cfg->u32 = o_ch_chfir_cfg.u32;
        
        s32Ret = VicapVerifyRegWrite((unsigned int *)&(po_ch_chfir_cfg->u32), o_ch_chfir_cfg.u32, "U_CH_CHFIR_CFG");
    }
    else
    {
        HI_ASSERT(0);
    }    

    return s32Ret;
}

/*��ֱ����ʹ��*/
HI_S32 VICAP_HAL_VScaleEn(HI_U32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj,HI_BOOL bScaleEn)
{
    HI_S32 s32Ret = 0;
    U_CH_LVFIR_CFG o_ch_lvfir_cfg, *po_ch_lvfir_cfg = NULL;
    U_CH_CVFIR_CFG o_ch_cvfir_cfg, *po_ch_cvfir_cfg = NULL;

    if (VICAP_CHN_SCALE_OBJ_YH == enObj)
    {
        po_ch_lvfir_cfg = (U_CH_LVFIR_CFG*)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_LVFIR_CFG);
        o_ch_lvfir_cfg.u32 = po_ch_lvfir_cfg->u32;
        o_ch_lvfir_cfg.bits.enable = bScaleEn;
        po_ch_lvfir_cfg->u32 = o_ch_lvfir_cfg.u32;
        
        s32Ret = VicapVerifyRegWrite((unsigned int *)&(po_ch_lvfir_cfg->u32), o_ch_lvfir_cfg.u32, "U_CH_LVFIR_CFG");
    }
    else if (VICAP_CHN_SCALE_OBJ_CH == enObj)
    {
        po_ch_cvfir_cfg = (U_CH_CVFIR_CFG*)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CVFIR_CFG);
        o_ch_cvfir_cfg.u32 = po_ch_cvfir_cfg->u32;
        o_ch_cvfir_cfg.bits.enable = bScaleEn;
        po_ch_cvfir_cfg->u32 = o_ch_cvfir_cfg.u32;
        
        s32Ret = VicapVerifyRegWrite((unsigned int *)&(po_ch_cvfir_cfg->u32), o_ch_cvfir_cfg.u32, "U_CH_CVFIR_CFG");
    }
    else
    {
        HI_ASSERT(0);
    }    

    return s32Ret;
}

#if 0
#endif

/* �������Ų������� */
HI_S32 VICAP_HAL_SetCoefUpdate(HI_S32 s32ChnIndex, VICAP_CHN_COEF_UPDATE_E enMod)
{
    U_CH_COEF_UPDATE o_ch_coef_update, *po_ch_coef_update = NULL;

    po_ch_coef_update = (U_CH_COEF_UPDATE*)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_COEF_UPDATE);
    o_ch_coef_update.u32 = po_ch_coef_update->u32;
    if (VICAP_CHN_LHCOEF_UPDATE == enMod)
    {
        o_ch_coef_update.bits.lhcoef_update = HI_TRUE;
    }
    else if (VICAP_CHN_CHCOEF_UPDATE == enMod)
    {
        o_ch_coef_update.bits.chcoef_update = HI_TRUE;
    }
    else
    {
        HI_ASSERT(0);
    }
    po_ch_coef_update->u32 = o_ch_coef_update.u32;
    
    return VicapVerifyRegWrite((unsigned int *)&(po_ch_coef_update->u32),o_ch_coef_update.u32, "U_CH_COEF_UPDATE"); 
}

/* ������������ϵ�� */
static HI_S32 VicapHalSetScaleLhfirCoef(HI_S32 s32ChnIndex,HI_U32 u32Phase, CH_LHFIR_COEF_S stLhfirCoef)
{
    HI_S32 s32Ret = 0;
    U_CH_LHFIR_COEF0 *po_ch_lhfir_coef0 = HI_NULL;
    U_CH_LHFIR_COEF1 *po_ch_lhfir_coef1 = HI_NULL;
    U_CH_LHFIR_COEF2 *po_ch_lhfir_coef2 = HI_NULL;

    po_ch_lhfir_coef0 = (U_CH_LHFIR_COEF0 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_LHFIR_COEF[u32Phase].uChLhfirCoef0);
    po_ch_lhfir_coef1 = (U_CH_LHFIR_COEF1 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_LHFIR_COEF[u32Phase].uChLhfirCoef1);
    po_ch_lhfir_coef2 = (U_CH_LHFIR_COEF2 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_LHFIR_COEF[u32Phase].uChLhfirCoef2);

    po_ch_lhfir_coef0->u32 = stLhfirCoef.uChLhfirCoef0.u32;
    po_ch_lhfir_coef1->u32 = stLhfirCoef.uChLhfirCoef1.u32;
    po_ch_lhfir_coef2->u32 = stLhfirCoef.uChLhfirCoef2.u32;

    s32Ret = VicapVerifyRegWrite((unsigned int *)&(po_ch_lhfir_coef0->u32), stLhfirCoef.uChLhfirCoef0.u32, "U_CH_LHFIR_COEF0");
    s32Ret |= VicapVerifyRegWrite((unsigned int *)&(po_ch_lhfir_coef1->u32), stLhfirCoef.uChLhfirCoef1.u32, "U_CH_LHFIR_COEF1");
    s32Ret |= VicapVerifyRegWrite((unsigned int *)&(po_ch_lhfir_coef2->u32), stLhfirCoef.uChLhfirCoef2.u32, "U_CH_LHFIR_COEF2");


   return s32Ret;
}

/* ����ɫ������ϵ�� */
static HI_S32 VicapHalSetScaleChfirCoef(HI_S32 s32ChnIndex,HI_U32 u32Phase, CH_CHFIR_COEF_S stChfirCoef)
{
    HI_S32 s32Ret = 0;
    U_CH_CHFIR_COEF0  *po_ch_chfir_coef0 = HI_NULL;
    U_CH_CHFIR_COEF1  *po_ch_chfir_coef1 = HI_NULL;
    U_CH_CHFIR_COEF2  *po_ch_chfir_coef2 = HI_NULL;


    po_ch_chfir_coef0 = (U_CH_CHFIR_COEF0 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CHFIR_COEF[u32Phase].uChChfirCoef0);
    po_ch_chfir_coef1 = (U_CH_CHFIR_COEF1 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CHFIR_COEF[u32Phase].uChChfirCoef1);
    po_ch_chfir_coef2 = (U_CH_CHFIR_COEF2 *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CHFIR_COEF[u32Phase].uChChfirCoef2);

    po_ch_chfir_coef0->u32 = stChfirCoef.uChChfirCoef0.u32;
    po_ch_chfir_coef1->u32 = stChfirCoef.uChChfirCoef1.u32;
    po_ch_chfir_coef2->u32 = stChfirCoef.uChChfirCoef2.u32;

    s32Ret = VicapVerifyRegWrite((unsigned int *)&(po_ch_chfir_coef0->u32), stChfirCoef.uChChfirCoef0.u32, "U_CH_CHFIR_COEF0");
    s32Ret |= VicapVerifyRegWrite((unsigned int *)&(po_ch_chfir_coef1->u32), stChfirCoef.uChChfirCoef1.u32, "U_CH_CHFIR_COEF1");
    s32Ret |= VicapVerifyRegWrite((unsigned int *)&(po_ch_chfir_coef2->u32), stChfirCoef.uChChfirCoef2.u32, "U_CH_CHFIR_COEF2");

   return s32Ret;
}


/* ��������ϵ����ȡѡ�� */
static HI_S32 VicapHalSetCoefSelect(HI_S32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, HI_U32 uValue)
{
    U_CH_COEF_RSEL o_ch_coef_rsel, *po_ch_coef_rsel = NULL;
    
    po_ch_coef_rsel = (U_CH_COEF_RSEL*)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_COEF_RSEL);
    
    o_ch_coef_rsel.u32 = po_ch_coef_rsel->u32;
    if (VICAP_CHN_SCALE_OBJ_YH == enObj)
    {
        o_ch_coef_rsel.bits.lhcoef_read_sel = uValue;
    }
    else if (VICAP_CHN_SCALE_OBJ_CH == enObj)
    {
        o_ch_coef_rsel.bits.chcoef_read_sel = uValue;
    }
    else
    {
        HI_ASSERT(0);
    }
        
    po_ch_coef_rsel->u32 = o_ch_coef_rsel.u32;

    return VicapVerifyRegWrite((unsigned int *)&(po_ch_coef_rsel->u32), o_ch_coef_rsel.u32, "U_CH_COEF_RSEL");
}


/* ��������8��ϵ�� */
HI_S32 VICAP_HAL_SetHScaleCoef8Phase(HI_S32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, VICAP_SCALE_COEFPARA_E eYCoefPara)
{
    HI_S32 i = 0, s32Ret = 0;
    CH_LHFIR_COEF_S astLhfirCoef[COEFF_GRPNUM];
    CH_CHFIR_COEF_S astChfirCoef[COEFF_GRPNUM];  
    HI_S32 (*asCoefPara)[8] = HI_NULL;
    
    memset(astLhfirCoef, 0, sizeof(CH_LHFIR_COEF_S));
    memset(astChfirCoef, 0, sizeof(CH_CHFIR_COEF_S));

    if(VICAP_SCALE_COEFPARA_NO == eYCoefPara)
    {
        asCoefPara = coef8_noScale;
    }else if(VICAP_SCALE_COEFPARA_2X == eYCoefPara)
    {
        asCoefPara = coef8_2xScale;
    }else if(VICAP_SCALE_COEFPARA_3X == eYCoefPara)
    {
        asCoefPara = coef8_3xScale;
    }else if(VICAP_SCALE_COEFPARA_4X == eYCoefPara)
    {
        asCoefPara = coef8_4xScale;
    }else 
    {
        asCoefPara = coef8_OtherScale;
    }
    
    for(i = 0; i < COEFF_GRPNUM; i++)
    {

            if(VICAP_CHN_SCALE_OBJ_YH== enObj)
            {
                astLhfirCoef[i].uChLhfirCoef0.bits.coef0 = asCoefPara[i][0];
                astLhfirCoef[i].uChLhfirCoef0.bits.coef1 = asCoefPara[i][1];
                astLhfirCoef[i].uChLhfirCoef0.bits.coef2 = asCoefPara[i][2];
                astLhfirCoef[i].uChLhfirCoef1.bits.coef3 = asCoefPara[i][3];
                astLhfirCoef[i].uChLhfirCoef1.bits.coef4 = asCoefPara[i][4];
                astLhfirCoef[i].uChLhfirCoef1.bits.coef5 = asCoefPara[i][5];
                astLhfirCoef[i].uChLhfirCoef2.bits.coef6 = asCoefPara[i][6];
                astLhfirCoef[i].uChLhfirCoef2.bits.coef7 = asCoefPara[i][7];
                VicapHalSetScaleLhfirCoef(s32ChnIndex, i, astLhfirCoef[i]);

            }

            if(VICAP_CHN_SCALE_OBJ_CH== enObj)
            {
                astChfirCoef[i].uChChfirCoef0.bits.coef0 = asCoefPara[i][0];
                astChfirCoef[i].uChChfirCoef0.bits.coef1 = asCoefPara[i][1];
                astChfirCoef[i].uChChfirCoef0.bits.coef2 = asCoefPara[i][2];
                astChfirCoef[i].uChChfirCoef1.bits.coef3 = asCoefPara[i][3];
                astChfirCoef[i].uChChfirCoef1.bits.coef4 = asCoefPara[i][4];
                astChfirCoef[i].uChChfirCoef1.bits.coef5 = asCoefPara[i][5];
                astChfirCoef[i].uChChfirCoef2.bits.coef6 = asCoefPara[i][6];
                astChfirCoef[i].uChChfirCoef2.bits.coef7 = asCoefPara[i][7];
                VicapHalSetScaleChfirCoef(s32ChnIndex, i, astChfirCoef[i]);
            }
        
        /*ѡ����ʾ��������coef�Ĵ���*/
        s32Ret |= VicapHalSetCoefSelect(s32ChnIndex, enObj, HI_TRUE);
        if (s32Ret != HI_SUCCESS)
        {
            return s32Ret;
        }
    }

    return HI_SUCCESS;
}

/* ������������������ */
HI_S32 VICAP_HAL_SetScaleSize(HI_S32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, VICAP_SCALE_SIZE_S *pstScaleSize)
{   
    HI_S32 s32Ret = 0;
    U_CH_LFIR_IN_SIZE o_ch_lfir_in_size, *po_ch_lfir_in_size = NULL;
    U_CH_LFIR_OUT_SIZE o_ch_lfir_out_size, *po_ch_hfir_out_size = NULL;
    U_CH_CFIR_IN_SIZE o_ch_cfir_in_size, *po_ch_cfir_in_size = NULL;
    U_CH_CFIR_OUT_SIZE o_ch_cfir_out_size, *po_ch_cfir_out_size = NULL;

    if (VICAP_CHN_SCALE_OBJ_YH == enObj) 
    {
        po_ch_lfir_in_size = (U_CH_LFIR_IN_SIZE *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_LFIR_IN_SIZE);
        o_ch_lfir_in_size.u32 = 0;
        o_ch_lfir_in_size.bits.width = pstScaleSize->u32YInPixel - 1;
        o_ch_lfir_in_size.bits.height = pstScaleSize->u32YInLine - 1;
        po_ch_lfir_in_size->u32 = o_ch_lfir_in_size.u32;

        po_ch_hfir_out_size = (U_CH_LFIR_OUT_SIZE *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_LFIR_OUT_SIZE);
        o_ch_lfir_out_size.u32 = 0;        
        o_ch_lfir_out_size.bits.width = pstScaleSize->u32YOutPixel - 1; 
        o_ch_lfir_out_size.bits.height = pstScaleSize->u32YOutLine - 1; 
        po_ch_hfir_out_size->u32 = o_ch_lfir_out_size.u32;

        VicapVerifyRegWrite((unsigned int *)&(po_ch_lfir_in_size->u32), o_ch_lfir_in_size.u32, "U_CH_LFIR_IN_SIZE");
        VicapVerifyRegWrite((unsigned int *)&(po_ch_hfir_out_size->u32), o_ch_lfir_out_size.u32, "U_CH_LFIR_OUT_SIZE");
    }
    else if (VICAP_CHN_SCALE_OBJ_CH == enObj)
    {
        po_ch_cfir_in_size = (U_CH_CFIR_IN_SIZE *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CFIR_IN_SIZE);
        o_ch_cfir_in_size.u32 = 0;
        o_ch_cfir_in_size.bits.width = pstScaleSize->u32CInPixel - 1;
        o_ch_cfir_in_size.bits.height = pstScaleSize->u32CInLine - 1;
        po_ch_cfir_in_size->u32 = o_ch_cfir_in_size.u32;

        po_ch_cfir_out_size = (U_CH_CFIR_OUT_SIZE *)(&g_pstVicapAllReg->stChnReg[s32ChnIndex].CH_CFIR_OUT_SIZE);
        o_ch_cfir_out_size.u32 = 0;        
        o_ch_cfir_out_size.bits.width = pstScaleSize->u32COutPixel - 1; 
        o_ch_cfir_out_size.bits.height = pstScaleSize->u32COutLine - 1;       
        po_ch_cfir_out_size->u32 = o_ch_cfir_out_size.u32; 
        
        VicapVerifyRegWrite((unsigned int *)&(po_ch_cfir_in_size->u32), o_ch_cfir_in_size.u32, "U_CH_CFIR_IN_SIZE");
        VicapVerifyRegWrite((unsigned int *)&(po_ch_cfir_out_size->u32), o_ch_cfir_out_size.u32, "U_CH_CFIR_OUT_SIZE");
    }
    else
    {
        HI_ASSERT(0);
    }
    
   return s32Ret;
}

#if 0
#endif 

static HI_VOID VicapHalDisablePtAll(HI_VOID)
{   
    HI_U32 i;
    
    /*���ö˿�*/
    for (i = 0; i < MAXPT; i++)
    {
       VICAP_HAL_SetPortEn(i,HI_FALSE);
    }
    
}

static HI_VOID  VicapHalDisableChnAll(HI_VOID)
{
    HI_U32 i;
    
    /*ͨ��ѭ���ر�*/
    for (i = 0; i < MAXCHN; i++)
    {
        /*�ر�YH��CH������*/
        VICAP_HAL_HScaleEn(i, VICAP_CHN_SCALE_OBJ_YH, HI_FALSE);
        VICAP_HAL_HScaleEn(i, VICAP_CHN_SCALE_OBJ_CH, HI_FALSE);
        /*�ر�YV��CV������*/
        VICAP_HAL_VScaleEn(i, VICAP_CHN_SCALE_OBJ_YH, HI_FALSE);
        VICAP_HAL_VScaleEn(i, VICAP_CHN_SCALE_OBJ_CH, HI_FALSE);
        /*����ͨ��*/
        VICAP_HAL_SetChnEn(i, HI_FALSE);
    }

}

/* ��ʼ��Ӳ�� */
HI_VOID VICAP_HAL_Init(HI_VOID)
{
    VicapHalWorkMode(HI_TRUE);
    VicapHalSetAxiCfg(VICAP_OUT_EIGHT);
    VicapHalSetMacCfg(HI_TRUE);
    VicapHalDisableChnAll();
    VicapHalDisablePtAll();
}


