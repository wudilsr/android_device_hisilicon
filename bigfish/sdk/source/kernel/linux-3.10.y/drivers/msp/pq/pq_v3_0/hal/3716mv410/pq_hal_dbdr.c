/******************************************************************************

Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
File Name     : pq_hal_dbdr.c
Version       : Initial Draft
Author        : d00241380
Created       : 2014/06/18
Description   : De-blocking and De-Mosquito

******************************************************************************/

#include "pq_hal_comm.h"
#include "pq_hal_dbdr.h"


/* 设置DB软算法api计算出来的参数值 */
HI_S32 PQ_HAL_SetDBApiReg(HI_U32 u32HandleNo, DB_API_REG_S * pstApiPara)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    
    PQ_CHECK_NULL_PTR(pstApiPara);  
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pqprint(PQ_PRN_DB_CALC, "[%s]: LumEn:%d, LumVEn:%d, LumHEn:%d, CbEn:%d, CrEn:%d, CVEn:%d, CHEn:%d\n"
                            "GreyEn:%d, DetHcEn:%d, DetVyEn:%d\n",
            __FUNCTION__,
            pstApiPara->db_lum_en,
            pstApiPara->db_lum_ver_en,
            pstApiPara->db_lum_hor_en,
            pstApiPara->db_cb_en,
            pstApiPara->db_cr_en,
            pstApiPara->db_chr_ver_en,
            pstApiPara->db_chr_hor_en,
            pstApiPara->db_chr_hor_mid_grey_en,
            pstApiPara->det_hc_en,
            pstApiPara->det_vy_en);
    
    //VPSS_DB_CTRL
    pstVpssVirReg->VPSS_DB_CTRL.bits.db_lum_ver_en          = pstApiPara->db_lum_ver_en;
    pstVpssVirReg->VPSS_DB_CTRL.bits.db_lum_hor_en          = pstApiPara->db_lum_hor_en;
    pstVpssVirReg->VPSS_DB_CTRL.bits.db_chr_ver_en          = pstApiPara->db_chr_ver_en;
    pstVpssVirReg->VPSS_DB_CTRL.bits.db_chr_hor_en          = pstApiPara->db_chr_hor_en;
    pstVpssVirReg->VPSS_DB_CTRL.bits.db_chr_hor_mid_grey_en = pstApiPara->db_chr_hor_mid_grey_en;

    /* det_size_en det_hy_en不在此处控制 */
    //pstVpssVirReg->VPSS_DB_CTRL.bits.det_size_en          = pstApiPara->det_size_en;
    //pstVpssVirReg->VPSS_DB_CTRL.bits.det_hy_en            = pstApiPara->det_hy_en;
    pstVpssVirReg->VPSS_DB_CTRL.bits.det_hc_en              = pstApiPara->det_hc_en;
    pstVpssVirReg->VPSS_DB_CTRL.bits.det_vy_en              = pstApiPara->det_vy_en;
    /********************************** Notice: 注意是否需要在软算法中刷新下面寄存器 ***********************/
    //pstVpssVirReg->VPSS_DB_CTRL.bits.dbm_out_mode
    //pstVpssVirReg->VPSS_DB_CTRL.bits.dbm_out_sel_gain

    //VPSS_DBD_TSTBLKNUM
    pstVpssVirReg->VPSS_DBD_TSTBLKNUM.bits.hy_tst_blk_num = pstApiPara->hy_tst_blk_num;
    pstVpssVirReg->VPSS_DBD_TSTBLKNUM.bits.hc_tst_blk_num = pstApiPara->hc_tst_blk_num;
    pstVpssVirReg->VPSS_DBD_TSTBLKNUM.bits.vy_tst_blk_num = pstApiPara->vy_tst_blk_num;

    //VPSS_DBD_BLKSIZE
    pstVpssVirReg->VPSS_DBD_BLKSIZE.bits.min_blk_size    = pstApiPara->min_blk_size;
    pstVpssVirReg->VPSS_DBD_BLKSIZE.bits.hy_max_blk_size = pstApiPara->hy_max_blk_size;
    pstVpssVirReg->VPSS_DBD_BLKSIZE.bits.hc_max_blk_size = pstApiPara->hc_max_blk_size;
    pstVpssVirReg->VPSS_DBD_BLKSIZE.bits.vy_max_blk_size = pstApiPara->vy_max_blk_size;

    {
        int i=0;
        //VPSS_DB_BORD_FLAG 
        for(i = 0; i < 128; ++i)
        {
            pstVpssVirReg->VPSS_DB_BORD_FLAG[i].bits.vpss_db_bord_flag = pstApiPara->vpss_db_bord_flag[i];
        }
    }
    
    //VPSS_DB_DIR
    pstVpssVirReg->VPSS_DB_DIR.bits.grad_sub_ratio = pstApiPara->grad_sub_ratio;

    //VPSS_DB_BLK
    pstVpssVirReg->VPSS_DB_BLK.bits.lum_h_blk_size = pstApiPara->lum_h_blk_size;
    pstVpssVirReg->VPSS_DB_BLK.bits.lum_v_blk_size = pstApiPara->lum_v_blk_size;
    pstVpssVirReg->VPSS_DB_BLK.bits.chr_h_blk_size = pstApiPara->chr_h_blk_size;
    pstVpssVirReg->VPSS_DB_BLK.bits.chr_v_blk_size = pstApiPara->chr_v_blk_size;

    //VPSS_DB_RATIO
    pstVpssVirReg->VPSS_DB_RATIO.bits.lum_hor_scale_ratio  = pstApiPara->lum_hor_scale_ratio;
    pstVpssVirReg->VPSS_DB_RATIO.bits.lum_ver_scale_ratio  = pstApiPara->lum_ver_scale_ratio;
    pstVpssVirReg->VPSS_DB_RATIO.bits.chr_hor_scale_ratio  = pstApiPara->chr_hor_scale_ratio;
    pstVpssVirReg->VPSS_DB_RATIO.bits.lum_hor_filter_sel   = pstApiPara->lum_hor_filter_sel;
    pstVpssVirReg->VPSS_DB_RATIO.bits.chr_hor_filter_sel   = pstApiPara->chr_hor_filter_sel;
    pstVpssVirReg->VPSS_DB_RATIO.bits.lum_hor_txt_win_size = pstApiPara->lum_hor_txt_win_size;

    //VPSS_DB_LHHF
    pstVpssVirReg->VPSS_DB_LHHF.bits.lum_hor_hf_diff_core  = pstApiPara->lum_hor_hf_diff_core;
    pstVpssVirReg->VPSS_DB_LHHF.bits.lum_hor_hf_diff_gain1 = pstApiPara->lum_hor_hf_diff_gain1;
    pstVpssVirReg->VPSS_DB_LHHF.bits.lum_hor_hf_diff_gain2 = pstApiPara->lum_hor_hf_diff_gain2;
    pstVpssVirReg->VPSS_DB_LHHF.bits.lum_hor_hf_var_core   = pstApiPara->lum_hor_hf_var_core;
    pstVpssVirReg->VPSS_DB_LHHF.bits.lum_hor_hf_var_gain1  = pstApiPara->lum_hor_hf_var_gain1;
    pstVpssVirReg->VPSS_DB_LHHF.bits.lum_hor_hf_var_gain2  = pstApiPara->lum_hor_hf_var_gain2;

    //VPSS_DB_LVHF
    pstVpssVirReg->VPSS_DB_LVHF.bits.lum_ver_hf_var_core   = pstApiPara->lum_ver_hf_var_core;
    pstVpssVirReg->VPSS_DB_LVHF.bits.lum_hor_bord_adj_gain = pstApiPara->lum_hor_bord_adj_gain;
    pstVpssVirReg->VPSS_DB_LVHF.bits.lum_ver_bord_adj_gain = pstApiPara->lum_ver_bord_adj_gain;
    pstVpssVirReg->VPSS_DB_LVHF.bits.lum_ver_hf_var_gain1  = pstApiPara->lum_ver_hf_var_gain1;
    pstVpssVirReg->VPSS_DB_LVHF.bits.lum_ver_hf_var_gain2  = pstApiPara->lum_ver_hf_var_gain2;
    pstVpssVirReg->VPSS_DB_LVHF.bits.lum_hor_adj_gain      = pstApiPara->lum_hor_adj_gain;
    pstVpssVirReg->VPSS_DB_LVHF.bits.lum_ver_adj_gain      = pstApiPara->lum_ver_adj_gain;

    //VPSS_DB_CTRS
    pstVpssVirReg->VPSS_DB_CTRS.bits.max_lum_hor_db_dist = pstApiPara->max_lum_hor_db_dist;
    pstVpssVirReg->VPSS_DB_CTRS.bits.max_chr_hor_db_dist = pstApiPara->max_chr_hor_db_dist;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetReg_Lum_Hor_Delta_Lut(HI_U32 u32HandleNo, const HI_U8 u8SrcLut[16])
{   
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    //VPSS_DB_LUT0
    pstVpssVirReg->VPSS_DB_LUT0.bits.lum_hor_delta_lut_p0  = u8SrcLut[0];
    pstVpssVirReg->VPSS_DB_LUT0.bits.lum_hor_delta_lut_p1  = u8SrcLut[1];
    pstVpssVirReg->VPSS_DB_LUT0.bits.lum_hor_delta_lut_p2  = u8SrcLut[2];
    pstVpssVirReg->VPSS_DB_LUT0.bits.lum_hor_delta_lut_p3  = u8SrcLut[3];
    pstVpssVirReg->VPSS_DB_LUT0.bits.lum_hor_delta_lut_p4  = u8SrcLut[4];
    pstVpssVirReg->VPSS_DB_LUT0.bits.lum_hor_delta_lut_p5  = u8SrcLut[5];
    pstVpssVirReg->VPSS_DB_LUT0.bits.lum_hor_delta_lut_p6  = u8SrcLut[6];
    pstVpssVirReg->VPSS_DB_LUT0.bits.lum_hor_delta_lut_p7  = u8SrcLut[7];
    //VPSS_DB_LUT1                                          
    pstVpssVirReg->VPSS_DB_LUT1.bits.lum_hor_delta_lut_p8  = u8SrcLut[8];
    pstVpssVirReg->VPSS_DB_LUT1.bits.lum_hor_delta_lut_p9  = u8SrcLut[9];
    pstVpssVirReg->VPSS_DB_LUT1.bits.lum_hor_delta_lut_p10 = u8SrcLut[10];
    pstVpssVirReg->VPSS_DB_LUT1.bits.lum_hor_delta_lut_p11 = u8SrcLut[11];
    pstVpssVirReg->VPSS_DB_LUT1.bits.lum_hor_delta_lut_p12 = u8SrcLut[12];
    pstVpssVirReg->VPSS_DB_LUT1.bits.lum_hor_delta_lut_p13 = u8SrcLut[13];
    pstVpssVirReg->VPSS_DB_LUT1.bits.lum_hor_delta_lut_p14 = u8SrcLut[14];
    pstVpssVirReg->VPSS_DB_LUT1.bits.lum_hor_delta_lut_p15 = u8SrcLut[15];

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetReg_Lum_Hor_Fade_Lut(HI_U32 u32HandleNo, const HI_U8 u8SrcLut[12])
{   
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    //VPSS_DB_LUT6
    pstVpssVirReg->VPSS_DB_LUT6.bits.lum_h_str_fade_lut_p0  = u8SrcLut[0];
    pstVpssVirReg->VPSS_DB_LUT6.bits.lum_h_str_fade_lut_p1  = u8SrcLut[1];
    pstVpssVirReg->VPSS_DB_LUT6.bits.lum_h_str_fade_lut_p2  = u8SrcLut[2];
    pstVpssVirReg->VPSS_DB_LUT6.bits.lum_h_str_fade_lut_p3  = u8SrcLut[3];
    pstVpssVirReg->VPSS_DB_LUT6.bits.lum_h_str_fade_lut_p4  = u8SrcLut[4];
    pstVpssVirReg->VPSS_DB_LUT6.bits.lum_h_str_fade_lut_p5  = u8SrcLut[5];
    pstVpssVirReg->VPSS_DB_LUT6.bits.lum_h_str_fade_lut_p6  = u8SrcLut[6];
    pstVpssVirReg->VPSS_DB_LUT6.bits.lum_h_str_fade_lut_p7  = u8SrcLut[7];
    pstVpssVirReg->VPSS_DB_LUT6.bits.lum_h_str_fade_lut_p8  = u8SrcLut[8];
    pstVpssVirReg->VPSS_DB_LUT6.bits.lum_h_str_fade_lut_p9  = u8SrcLut[9];
    //VPSS_DB_LUT9
    pstVpssVirReg->VPSS_DB_LUT9.bits.lum_h_str_fade_lut_p10 = u8SrcLut[10];
    pstVpssVirReg->VPSS_DB_LUT9.bits.lum_h_str_fade_lut_p11 = u8SrcLut[11];

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetReg_Chr_Hor_Fade_Lut(HI_U32 u32HandleNo, const HI_U8 u8SrcLut[12])
{   
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    //VPSS_DB_LUT8
    pstVpssVirReg->VPSS_DB_LUT8.bits.chr_h_str_fade_lut_p0  = u8SrcLut[0];
    pstVpssVirReg->VPSS_DB_LUT8.bits.chr_h_str_fade_lut_p1  = u8SrcLut[1];
    pstVpssVirReg->VPSS_DB_LUT8.bits.chr_h_str_fade_lut_p2  = u8SrcLut[2];
    pstVpssVirReg->VPSS_DB_LUT8.bits.chr_h_str_fade_lut_p3  = u8SrcLut[3];
    pstVpssVirReg->VPSS_DB_LUT8.bits.chr_h_str_fade_lut_p4  = u8SrcLut[4];
    pstVpssVirReg->VPSS_DB_LUT8.bits.chr_h_str_fade_lut_p5  = u8SrcLut[5];
    pstVpssVirReg->VPSS_DB_LUT8.bits.chr_h_str_fade_lut_p6  = u8SrcLut[6];
    pstVpssVirReg->VPSS_DB_LUT8.bits.chr_h_str_fade_lut_p7  = u8SrcLut[7];
    pstVpssVirReg->VPSS_DB_LUT8.bits.chr_h_str_fade_lut_p8  = u8SrcLut[8];
    pstVpssVirReg->VPSS_DB_LUT8.bits.chr_h_str_fade_lut_p9  = u8SrcLut[9];
    //VPSS_DB_LUT9
    pstVpssVirReg->VPSS_DB_LUT9.bits.chr_h_str_fade_lut_p10 = u8SrcLut[10];
    pstVpssVirReg->VPSS_DB_LUT9.bits.chr_h_str_fade_lut_p11 = u8SrcLut[11];

    return HI_SUCCESS;
}

/* S5V200 中没有设置 */
HI_S32 PQ_HAL_SetReg_Lum_Ver_Fade_Lut(HI_U32 u32HandleNo, const HI_U8 p_SrcLut[12])
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);
    
    pstVpssVirReg->VPSS_DB_LUT7.bits.lum_v_str_fade_lut_p0  = p_SrcLut[0];
    pstVpssVirReg->VPSS_DB_LUT7.bits.lum_v_str_fade_lut_p1  = p_SrcLut[1];
    pstVpssVirReg->VPSS_DB_LUT7.bits.lum_v_str_fade_lut_p2  = p_SrcLut[2];
    pstVpssVirReg->VPSS_DB_LUT7.bits.lum_v_str_fade_lut_p3  = p_SrcLut[3];
    pstVpssVirReg->VPSS_DB_LUT7.bits.lum_v_str_fade_lut_p4  = p_SrcLut[4];
    pstVpssVirReg->VPSS_DB_LUT7.bits.lum_v_str_fade_lut_p5  = p_SrcLut[5];
    pstVpssVirReg->VPSS_DB_LUT7.bits.lum_v_str_fade_lut_p6  = p_SrcLut[6];
    pstVpssVirReg->VPSS_DB_LUT7.bits.lum_v_str_fade_lut_p7  = p_SrcLut[7];
    pstVpssVirReg->VPSS_DB_LUT7.bits.lum_v_str_fade_lut_p8  = p_SrcLut[8];
    pstVpssVirReg->VPSS_DB_LUT7.bits.lum_v_str_fade_lut_p9  = p_SrcLut[9];
    pstVpssVirReg->VPSS_DB_LUT9.bits.lum_v_str_fade_lut_p10 = p_SrcLut[10];
    pstVpssVirReg->VPSS_DB_LUT9.bits.lum_v_str_fade_lut_p11 = p_SrcLut[11];

    return HI_SUCCESS;
}

/* S5V200 中没有设置 */
HI_S32 PQ_HAL_SetReg_Lum_Ver_Delta_Lut(HI_U32 u32HandleNo, const HI_U8 p_SrcLut[16])
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);
    
    pstVpssVirReg->VPSS_DB_LUT2.bits.lum_ver_delta_lut_p0 = p_SrcLut[0]; 
    pstVpssVirReg->VPSS_DB_LUT2.bits.lum_ver_delta_lut_p1 = p_SrcLut[1];
    pstVpssVirReg->VPSS_DB_LUT2.bits.lum_ver_delta_lut_p2 = p_SrcLut[2];
    pstVpssVirReg->VPSS_DB_LUT2.bits.lum_ver_delta_lut_p3 = p_SrcLut[3];
    pstVpssVirReg->VPSS_DB_LUT2.bits.lum_ver_delta_lut_p4 = p_SrcLut[4];
    pstVpssVirReg->VPSS_DB_LUT2.bits.lum_ver_delta_lut_p5 = p_SrcLut[5];
    pstVpssVirReg->VPSS_DB_LUT2.bits.lum_ver_delta_lut_p6 = p_SrcLut[6];
    pstVpssVirReg->VPSS_DB_LUT2.bits.lum_ver_delta_lut_p7 = p_SrcLut[7];

    pstVpssVirReg->VPSS_DB_LUT3.bits.lum_ver_delta_lut_p8  = p_SrcLut[8];
    pstVpssVirReg->VPSS_DB_LUT3.bits.lum_ver_delta_lut_p9  = p_SrcLut[9];
    pstVpssVirReg->VPSS_DB_LUT3.bits.lum_ver_delta_lut_p10 = p_SrcLut[10];
    pstVpssVirReg->VPSS_DB_LUT3.bits.lum_ver_delta_lut_p11 = p_SrcLut[11];
    pstVpssVirReg->VPSS_DB_LUT3.bits.lum_ver_delta_lut_p12 = p_SrcLut[12];
    pstVpssVirReg->VPSS_DB_LUT3.bits.lum_ver_delta_lut_p13 = p_SrcLut[13];
    pstVpssVirReg->VPSS_DB_LUT3.bits.lum_ver_delta_lut_p14 = p_SrcLut[14];
    pstVpssVirReg->VPSS_DB_LUT3.bits.lum_ver_delta_lut_p15 = p_SrcLut[15];

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetDBDetEnReg(HI_U32 u32HandleNo, HI_S32 *pDet_size_en,
                                      HI_S32 *pDet_hy_en, HI_S32 *pDet_hc_en, HI_S32 *pDet_vy_en)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    *pDet_size_en = pstVpssVirReg->VPSS_DB_CTRL.bits.det_size_en;
    *pDet_hy_en   = pstVpssVirReg->VPSS_DB_CTRL.bits.det_hy_en;
    *pDet_hc_en   = pstVpssVirReg->VPSS_DB_CTRL.bits.det_hc_en;
    *pDet_vy_en   = pstVpssVirReg->VPSS_DB_CTRL.bits.det_vy_en;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetDBEnReg(HI_U32 u32HandleNo, HI_BOOL* pbOnOff)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    *pbOnOff = pstVpssVirReg->VPSS_CTRL.bits.dbm_en;

    return HI_SUCCESS;
}

/* 设置DB Det Size功能开关 */
HI_S32 PQ_HAL_SetDBDetSizeEn(HI_U32 u32HandleNo, HI_BOOL bOnOff)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_DB_CTRL.bits.det_size_en = bOnOff;

    return HI_SUCCESS;
}

/* DB卖场模式的开关 */
HI_S32 PQ_HAL_EnableDBDemo(HI_U32 u32HandleNo, HI_BOOL bDBDemoEn)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_DB_CTRL.bits.dbm_demo_en = bDBDemoEn;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetDbmDemoMode(HI_U32 u32HandleNo, DBM_DEMO_MODE_E enMode)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_DB_CTRL.bits.dbm_demo_mode = enMode;

    return HI_SUCCESS;
}

/* 设置DR功能开关 */
HI_S32 PQ_HAL_EnableDM(HI_U32 u32HandleNo, HI_BOOL bOnOff)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    /* DM的单独使能 */
    pstVpssVirReg->VPSS_DB_CTRL.bits.dm_en = bOnOff;

    return HI_SUCCESS;
}

/* 设置DR卖场模式的功能开关 */
HI_S32 PQ_HAL_EnableDMDemo(HI_U32 u32HandleNo, HI_BOOL bOnOff)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_DB_CTRL.bits.dbm_demo_en = bOnOff;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetDMApiReg(HI_U32 u32HandleNo, DM_API_REG_S* pstDmApiReg)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;

    PQ_CHECK_NULL_PTR(pstDmApiReg);
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    //VPSS_DM_EDGE
    pstVpssVirReg->VPSS_DM_EDGE.bits.dm_edge_thr     = pstDmApiReg->u8Dm_edge_thr;
    pstVpssVirReg->VPSS_DM_EDGE.bits.dm_asymtrc_gain = pstDmApiReg->u8Dm_asymtrc_gain;
    pstVpssVirReg->VPSS_DM_EDGE.bits.dm_edge_gain1   = pstDmApiReg->u8Dm_edge_gain1;
    pstVpssVirReg->VPSS_DM_EDGE.bits.dm_edge_gain2   = pstDmApiReg->u8Dm_edge_gain2;
    pstVpssVirReg->VPSS_DM_EDGE.bits.dm_sw_thr_gain  = pstDmApiReg->u8Dm_sw_thr_gain;
    pstVpssVirReg->VPSS_DM_EDGE.bits.dm_global_str   = pstDmApiReg->u8Dm_global_str;
    pstVpssVirReg->VPSS_DM_EDGE.bits.dm_str_idx      = pstDmApiReg->u8Dm_str_idx;

    return HI_SUCCESS;
}

/*  Get DR Enable Reg */
HI_S32 PQ_HAL_GetDREnReg(HI_U32 u32HandleNo, HI_BOOL* pbOnOff)
{
    return HI_SUCCESS;
}

/*  Set DR Demo Mode Enable */
HI_S32 PQ_HAL_EnableDRDemo(HI_U32 u32HandleNo, HI_BOOL bOnOff)
{
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetVpssDemoPos(HI_U32 u32HandleNo, HI_U32 u32DemoPos)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_CTRL2.bits.market_coordinate = u32DemoPos;

    return HI_SUCCESS;
}

#if 0
/* 设置DB功能开关 */
HI_S32 PQ_HAL_EnableDB(HI_U32 u32HandleNo, HI_BOOL bOnOff)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    /* db_en and det_size_en open and close together */
    pstVpssVirReg->VPSS_CTRL.bits.dbm_en         = bOnOff;
    pstVpssVirReg->VPSS_DB_CTRL.bits.det_size_en = bOnOff;

    return HI_SUCCESS;
}

/* 设置DB卖场模式的Pos */
HI_S32 PQ_HAL_SetDBDemoPos(HI_U32 u32HandleNo, HI_U32 u32DBDemoPos)
{
    S_CAS_REGS_TYPE* pstVpssVirReg = HI_NULL;
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_DBM_DEMO.bits.dbm_demo_xpos = u32DBDemoPos;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetDBStrength(HI_U32 u32HandleNo, HI_S32 s32DBStr)
{
    return HI_SUCCESS;
}

/* DM 强度中间值 */
static HI_S32 sg_s32DmMStr[VPSS_HANDLE_NUM];

/* 设置DM强度中间值 */
HI_S32 PQ_HAL_SetDMMidStr(HI_U32 u32HandleNo)
{
    return HI_SUCCESS;
}

/* 设置DM强度等级 */
HI_S32 PQ_HAL_SetDMStrength(HI_U32 u32HandleNo, HI_S32 s32DMStr)
{
    return HI_SUCCESS;
}
#endif

