//****************************************************************************** 
// Copyright     :  Copyright (C) 2014, Hisilicon Technologies Co., Ltd.
// File name     :  hi_reg_peri.h
// Author        :  fangqiubin 00179307
// Version       :  1.0 
// Date          :  2014-12-19
// Description   :  Define all registers/tables for PERI_CTRL
// Others        :  Generated automatically by nManager V4.0 
// History       :  fangqiubin 00179307 2014-12-19 Create file
//******************************************************************************

#ifndef __HI_REG_PERI_H__
#define __HI_REG_PERI_H__

/* Define the union U_START_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 9   ; /* [8..0]  */
        unsigned int    boot_sel              : 3   ; /* [11..9]  */
        unsigned int    reserved_1            : 10  ; /* [21..12]  */
        unsigned int    por_sel               : 1   ; /* [22]  */
        unsigned int    jtag_sel_in           : 1   ; /* [23]  */
        unsigned int    usb_boot              : 1   ; /* [24]  */
        unsigned int    sdio_pu_en_in_lock    : 1   ; /* [25]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_START_MODE;

/* Define the union U_PERI_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sdio1_card_det_mode   : 1   ; /* [0]  */
        unsigned int    sdio0_card_det_mode   : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    ssp1_cs_sel           : 1   ; /* [3]  */
        unsigned int    ssp0_cs_sel           : 1   ; /* [4]  */
        unsigned int    sdio0_cwpr_mode       : 1   ; /* [5]  */
        unsigned int    sdio1_cwpr_mode       : 1   ; /* [6]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    net_if0_sel           : 1   ; /* [8]  */
        unsigned int    reserved_2            : 1   ; /* [9]  */
        unsigned int    sata0_pwren           : 1   ; /* [10]  */
        unsigned int    pcie_usb3_sata3_sel_combphy1 : 2   ; /* [12..11]  */
        unsigned int    sata1_pwren           : 1   ; /* [13]  */
        unsigned int    pcie_usb3_sata3_sel_combphy3 : 2   ; /* [15..14]  */
        unsigned int    l2_size               : 2   ; /* [17..16]  */
        unsigned int    reserved_3            : 11  ; /* [28..18]  */
        unsigned int    peri_jtag_sel         : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CTRL;

/* Define the union U_PMU_STAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    PMUPL1                : 4   ; /* [3..0]  */
        unsigned int    PMUPL2                : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMU_STAT;

/* Define the union U_PERI_QOS_GLOB_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddrc_qos_way          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_GLOB_CTRL;

/* Define the union U_PERI_QOS_CFG0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    aiao_arqos            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    aiao_awqos            : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    bpd_arqos             : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    bpd_awqos             : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    cpu_m1_arqos          : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    cpu_m1_awqos          : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 1   ; /* [23]  */
        unsigned int    ddrt_arqos            : 3   ; /* [26..24]  */
        unsigned int    reserved_6            : 1   ; /* [27]  */
        unsigned int    ddrt_awqos            : 3   ; /* [30..28]  */
        unsigned int    reserved_7            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG0;

/* Define the union U_PERI_QOS_CFG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 16  ; /* [15..0]  */
        unsigned int    gpu_arqos             : 3   ; /* [18..16]  */
        unsigned int    reserved_1            : 1   ; /* [19]  */
        unsigned int    gpu_awqos             : 3   ; /* [22..20]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    hwc_arqos             : 3   ; /* [26..24]  */
        unsigned int    reserved_3            : 1   ; /* [27]  */
        unsigned int    hwc_awqos             : 3   ; /* [30..28]  */
        unsigned int    reserved_4            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG1;

/* Define the union U_PERI_QOS_CFG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    jpgd0_arqos           : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    jpgd0_awqos           : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 9   ; /* [15..7]  */
        unsigned int    jpge_arqos            : 3   ; /* [18..16]  */
        unsigned int    reserved_2            : 1   ; /* [19]  */
        unsigned int    jpge_awqos            : 3   ; /* [22..20]  */
        unsigned int    reserved_3            : 1   ; /* [23]  */
        unsigned int    pgd_arqos             : 3   ; /* [26..24]  */
        unsigned int    reserved_4            : 1   ; /* [27]  */
        unsigned int    pgd_awqos             : 3   ; /* [30..28]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG2;

/* Define the union U_PERI_QOS_CFG3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    qtc_awqos             : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    sata3_arqos           : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    sata3_awqos           : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    tde_arqos             : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    tde_awqos             : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    usb3_m_arqos          : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 1   ; /* [23]  */
        unsigned int    usb3_m_awqos          : 3   ; /* [26..24]  */
        unsigned int    reserved_6            : 1   ; /* [27]  */
        unsigned int    vdh_arqos             : 3   ; /* [30..28]  */
        unsigned int    reserved_7            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG3;

/* Define the union U_PERI_QOS_CFG4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdh_awqos             : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    vdp_arqos             : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    vdp_awqos             : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    vedu_arqos            : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    vedu_awqos            : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    vicap_awqos           : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 1   ; /* [23]  */
        unsigned int    vpss0_m0_arqos        : 3   ; /* [26..24]  */
        unsigned int    reserved_6            : 1   ; /* [27]  */
        unsigned int    vpss0_m0_awqos        : 3   ; /* [30..28]  */
        unsigned int    reserved_7            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG4;

/* Define the union U_PERI_QOS_CFG5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdh1_arqos            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    vdh1_awqos            : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ca_m_qos              : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 9   ; /* [19..11]  */
        unsigned int    spi_nand_m_qos        : 3   ; /* [22..20]  */
        unsigned int    reserved_3            : 1   ; /* [23]  */
        unsigned int    nandc_m_qos           : 3   ; /* [26..24]  */
        unsigned int    reserved_4            : 1   ; /* [27]  */
        unsigned int    pvr_m_qos             : 3   ; /* [30..28]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG5;

/* Define the union U_PERI_QOS_CFG6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    sdio_m_qos            : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 5   ; /* [11..7]  */
        unsigned int    gsf_m_qos             : 3   ; /* [14..12]  */
        unsigned int    reserved_2            : 5   ; /* [19..15]  */
        unsigned int    sfc_qos               : 3   ; /* [22..20]  */
        unsigned int    reserved_3            : 1   ; /* [23]  */
        unsigned int    sha_m_qos             : 3   ; /* [26..24]  */
        unsigned int    reserved_4            : 1   ; /* [27]  */
        unsigned int    usb2_qos              : 3   ; /* [30..28]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG6;

/* Define the union U_PERI_QOS_CFG7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    mcu_qos               : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    pcie_arqos            : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    pcie_awqos            : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG7;

/* Define the union U_PERI_USB_RESUME_INT_MASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb_phy0_suspend_int_mask : 1   ; /* [0]  */
        unsigned int    usb3_utmi_suspend_n   : 1   ; /* [1]  */
        unsigned int    usb_phy2_suspend_int_mask : 1   ; /* [2]  */
        unsigned int    usb_phy3_suspend_int_mask : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB_RESUME_INT_MASK;

/* Define the union U_PERI_USB_RESUME_INT_RAWSTAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb_phy0_suspend_int_rawstat : 1   ; /* [0]  */
        unsigned int    usb3_suspend_int_rawstat : 1   ; /* [1]  */
        unsigned int    usb_phy2_suspend_int_rawstat : 1   ; /* [2]  */
        unsigned int    usb_phy3_suspend_int_rawstat : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB_RESUME_INT_RAWSTAT;

/* Define the union U_PERI_USB_RESUME_INT_STAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb_phy0_suspend_int_stat : 1   ; /* [0]  */
        unsigned int    usb3_suspend_int_stat : 1   ; /* [1]  */
        unsigned int    usb_phy2_suspend_int_stat : 1   ; /* [2]  */
        unsigned int    usb_phy1_suspend_int_stat : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB_RESUME_INT_STAT;

/* Define the union U_PERI_INT_A9TOMCE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_cputomce          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_A9TOMCE;

/* Define the union U_PERI_INT_SWI0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi0              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI0;

/* Define the union U_PERI_INT_SWI1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi1              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI1;

/* Define the union U_PERI_INT_SWI2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi2              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI2;

/* Define the union U_PERI_INT_SWI0_MASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi0_mask_a9      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI0_MASK;

/* Define the union U_PERI_INT_SWI1_MASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi1_mask_a9      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI1_MASK;

/* Define the union U_PERI_INT_SWI2_MASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi2_mask_a9      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI2_MASK;

/* Define the union U_PERI_QAM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    qam_i2c_devaddr       : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QAM;

/* Define the union U_PERI_QAM_ADC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    qamadc_i2c_devaddr    : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    opm                   : 2   ; /* [9..8]  */
        unsigned int    selof                 : 1   ; /* [10]  */
        unsigned int    startcal              : 1   ; /* [11]  */
        unsigned int    envcmout              : 1   ; /* [12]  */
        unsigned int    enaccoupling          : 1   ; /* [13]  */
        unsigned int    reserved_1            : 9   ; /* [22..14]  */
        unsigned int    qamadc_clk_sel        : 1   ; /* [23]  */
        unsigned int    adcrdy                : 1   ; /* [24]  */
        unsigned int    reserved_2            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QAM_ADC0;

/* Define the union U_PERI_TIANLA_ADAC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dacr_vol              : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    dacl_vol              : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 3   ; /* [17..15]  */
        unsigned int    deemphasis_fs         : 2   ; /* [19..18]  */
        unsigned int    dacr_deemph           : 1   ; /* [20]  */
        unsigned int    dacl_deemph           : 1   ; /* [21]  */
        unsigned int    dacr_path             : 1   ; /* [22]  */
        unsigned int    dacl_path             : 1   ; /* [23]  */
        unsigned int    reserved_2            : 4   ; /* [27..24]  */
        unsigned int    mute_dacr             : 1   ; /* [28]  */
        unsigned int    mute_dacl             : 1   ; /* [29]  */
        unsigned int    pd_dacr               : 1   ; /* [30]  */
        unsigned int    pd_dacl               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_TIANLA_ADAC0;

/* Define the union U_PERI_TIANLA_ADAC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pop_direct_r          : 1   ; /* [0]  */
        unsigned int    pop_adj_res           : 2   ; /* [2..1]  */
        unsigned int    pop_direct_l          : 1   ; /* [3]  */
        unsigned int    pop_adj_clk           : 2   ; /* [5..4]  */
        unsigned int    reserved_0            : 1   ; /* [6]  */
        unsigned int    verf_extmod           : 1   ; /* [7]  */
        unsigned int    reserved_1            : 11  ; /* [18..8]  */
        unsigned int    clksel                : 3   ; /* [21..19]  */
        unsigned int    data_bits             : 2   ; /* [23..22]  */
        unsigned int    reserved_2            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_TIANLA_ADAC1;

/* Define the union U_PERI_FEPHY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fephy_phy_addr        : 5   ; /* [4..0]  */
        unsigned int    mask_fephy_wol        : 1   ; /* [5]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    fephy_tclk_enable     : 1   ; /* [8]  */
        unsigned int    afe_tclk_test_en      : 1   ; /* [9]  */
        unsigned int    fephy_patch_enable    : 1   ; /* [10]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    soft_fephy_mdio_mdc   : 1   ; /* [12]  */
        unsigned int    reserved_2            : 1   ; /* [13]  */
        unsigned int    soft_fephy_mdio_i     : 1   ; /* [14]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    soft_fephy_gp_i       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_FEPHY;

/* Define the union U_PERI_SD_LDO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fuse                  : 4   ; /* [3..0]  */
        unsigned int    vset                  : 1   ; /* [4]  */
        unsigned int    en                    : 1   ; /* [5]  */
        unsigned int    bypass                : 1   ; /* [6]  */
        unsigned int    reserved_0            : 9   ; /* [15..7]  */
        unsigned int    fuse1                 : 4   ; /* [19..16]  */
        unsigned int    vset1                 : 1   ; /* [20]  */
        unsigned int    en1                   : 1   ; /* [21]  */
        unsigned int    bypass1               : 1   ; /* [22]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_SD_LDO;

/* Define the union U_PERI_USB0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    test_wrdata           : 8   ; /* [7..0]  */
        unsigned int    test_addr             : 5   ; /* [12..8]  */
        unsigned int    test_wren             : 1   ; /* [13]  */
        unsigned int    test_clk              : 1   ; /* [14]  */
        unsigned int    test_rstn             : 1   ; /* [15]  */
        unsigned int    test_rddata           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB0;

/* Define the union U_PERI_USB1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    test_wrdata           : 8   ; /* [7..0]  */
        unsigned int    test_addr             : 5   ; /* [12..8]  */
        unsigned int    test_wren             : 1   ; /* [13]  */
        unsigned int    test_clk              : 1   ; /* [14]  */
        unsigned int    test_rstn             : 1   ; /* [15]  */
        unsigned int    test_rddata           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB1;

/* Define the union U_PERI_USB2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    test_wrdata           : 8   ; /* [7..0]  */
        unsigned int    test_addr             : 5   ; /* [12..8]  */
        unsigned int    test_wren             : 1   ; /* [13]  */
        unsigned int    test_clk              : 1   ; /* [14]  */
        unsigned int    test_rstn             : 1   ; /* [15]  */
        unsigned int    test_rddata           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB2;

/* Define the union U_PERI_USB3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ss_word_if_i          : 1   ; /* [0]  */
        unsigned int    ohci_susp_lgcy_i      : 1   ; /* [1]  */
        unsigned int    app_start_clk_i       : 1   ; /* [2]  */
        unsigned int    ulpi_bypass_en_i      : 1   ; /* [3]  */
        unsigned int    reserved_0            : 1   ; /* [4]  */
        unsigned int    ss_autoppd_on_overcur_en_i : 1   ; /* [5]  */
        unsigned int    ss_ena_incr_align_i   : 1   ; /* [6]  */
        unsigned int    ss_ena_incr4_i        : 1   ; /* [7]  */
        unsigned int    ss_ena_incr8_i        : 1   ; /* [8]  */
        unsigned int    ss_ena_incr16_i       : 1   ; /* [9]  */
        unsigned int    reserved_1            : 12  ; /* [21..10]  */
        unsigned int    ss_hubsetup_min_i     : 1   ; /* [22]  */
        unsigned int    reserved_2            : 5   ; /* [27..23]  */
        unsigned int    chipid                : 1   ; /* [28]  */
        unsigned int    ss_scaledown_mode     : 2   ; /* [30..29]  */
        unsigned int    ohci_0_cntsel_i_n     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB3;

/* Define the union U_PERI_USB4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ss_word_if_i          : 1   ; /* [0]  */
        unsigned int    ohci_susp_lgcy_i      : 1   ; /* [1]  */
        unsigned int    app_start_clk_i       : 1   ; /* [2]  */
        unsigned int    ulpi_bypass_en_i      : 1   ; /* [3]  */
        unsigned int    reserved_0            : 1   ; /* [4]  */
        unsigned int    ss_autoppd_on_overcur_en_i : 1   ; /* [5]  */
        unsigned int    ss_ena_incr_align_i   : 1   ; /* [6]  */
        unsigned int    ss_ena_incr4_i        : 1   ; /* [7]  */
        unsigned int    ss_ena_incr8_i        : 1   ; /* [8]  */
        unsigned int    ss_ena_incr16_i       : 1   ; /* [9]  */
        unsigned int    reserved_1            : 12  ; /* [21..10]  */
        unsigned int    ss_hubsetup_min_i     : 1   ; /* [22]  */
        unsigned int    reserved_2            : 8   ; /* [30..23]  */
        unsigned int    ohci_0_cntsel_i_n     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB4;

/* Define the union U_PERI_USB5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    hub_port_perm_attach  : 2   ; /* [3..2]  */
        unsigned int    hub_u2_port_disable   : 1   ; /* [4]  */
        unsigned int    hub_u3_port_disable   : 1   ; /* [5]  */
        unsigned int    host_port_power_control_present : 1   ; /* [6]  */
        unsigned int    host_msi_enable       : 1   ; /* [7]  */
        unsigned int    fladj_30mhz_reg       : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    bus_filter_bypass     : 4   ; /* [19..16]  */
        unsigned int    host_current_belt     : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB5;

/* Define the union U_PERI_USB6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb_pwr_ctrl          : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB6;

/* Define the union U_PERI_USB7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    hub_port_perm_attach  : 2   ; /* [3..2]  */
        unsigned int    hub_u2_port_disable   : 1   ; /* [4]  */
        unsigned int    hub_u3_port_disable   : 1   ; /* [5]  */
        unsigned int    host_port_power_control_present : 1   ; /* [6]  */
        unsigned int    host_msi_enable       : 1   ; /* [7]  */
        unsigned int    fladj_30mhz_reg       : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    bus_filter_bypass     : 4   ; /* [19..16]  */
        unsigned int    host_current_belt     : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB7;

/* Define the union U_PERI_USB8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb_pwr_ctrl          : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB8;

/* Define the union U_PERI_TIANLA_ADAC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ctrl_dffr             : 1   ; /* [0]  */
        unsigned int    ctrl_dffl             : 1   ; /* [1]  */
        unsigned int    pd_vref               : 1   ; /* [2]  */
        unsigned int    Pd_ctcm_ibias         : 1   ; /* [3]  */
        unsigned int    pd_ibias              : 1   ; /* [4]  */
        unsigned int    pd_dacr               : 1   ; /* [5]  */
        unsigned int    pd_dacl               : 1   ; /* [6]  */
        unsigned int    pd_ctcm               : 1   ; /* [7]  */
        unsigned int    adj_refbf             : 2   ; /* [9..8]  */
        unsigned int    adj_dac               : 2   ; /* [11..10]  */
        unsigned int    adj_ctcm              : 1   ; /* [12]  */
        unsigned int    RST                   : 1   ; /* [13]  */
        unsigned int    mute_dacr             : 1   ; /* [14]  */
        unsigned int    mute_dacl             : 1   ; /* [15]  */
        unsigned int    Td_sel                : 5   ; /* [20..16]  */
        unsigned int    fs                    : 1   ; /* [21]  */
        unsigned int    popfreer              : 1   ; /* [22]  */
        unsigned int    popfreel              : 1   ; /* [23]  */
        unsigned int    clkdgesel             : 1   ; /* [24]  */
        unsigned int    clksel                : 1   ; /* [25]  */
        unsigned int    Chop_dacvref_sel      : 2   ; /* [27..26]  */
        unsigned int    Chop_ctcm_sel         : 2   ; /* [29..28]  */
        unsigned int    Chop_bps_dacvref      : 1   ; /* [30]  */
        unsigned int    Chop_bps_ctcm         : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_TIANLA_ADAC2;

/* Define the union U_PERI_FEPHY_GP_I */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    peri_fephy_gp_i       : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_FEPHY_GP_I;

/* Define the union U_PERI_DDRPHY_TEST0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddrphy0_iotst_iotest  : 12  ; /* [11..0]  */
        unsigned int    ddrphy0_hs_dgbmux_sel : 15  ; /* [26..12]  */
        unsigned int    ddrphy0_ls_dgbmux_sel : 3   ; /* [29..27]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_DDRPHY_TEST0;

/* Define the union U_PERI_DDRPHY_TEST1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddrphy1_iotst_iotest  : 12  ; /* [11..0]  */
        unsigned int    ddrphy1_hs_dgbmux_sel : 15  ; /* [26..12]  */
        unsigned int    ddrphy1_ls_dgbmux_sel : 3   ; /* [29..27]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_DDRPHY_TEST1;

/* Define the union U_CHIPSET_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dolby_flag            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 1   ; /* [1]  */
        unsigned int    dts_flag              : 1   ; /* [2]  */
        unsigned int    peri_chipset_info     : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHIPSET_INFO;

/* Define the union U_PERI_SIM_OD_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    sim0_pwren_od_sel     : 1   ; /* [1]  */
        unsigned int    sim0_rst_od_sel       : 1   ; /* [2]  */
        unsigned int    reserved_1            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_SIM_OD_CTRL;

/* Define the union U_PERI_SOC_FUSE_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    otp_control_cpu       : 1   ; /* [0]  */
        unsigned int    reserved_0            : 2   ; /* [2..1]  */
        unsigned int    otp_control_gpu       : 2   ; /* [4..3]  */
        unsigned int    otp_ddr_st            : 2   ; /* [6..5]  */
        unsigned int    otp_vd_st             : 1   ; /* [7]  */
        unsigned int    otp_control_qam       : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    otp_ctrl_vdac         : 4   ; /* [15..12]  */
        unsigned int    chip_id               : 5   ; /* [20..16]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    mven                  : 1   ; /* [24]  */
        unsigned int    vedu_chip_id          : 2   ; /* [26..25]  */
        unsigned int    reserved_3            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_SOC_FUSE_0;

/* Define the union U_PERI_FEPHY_LDO_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fephy_ldo_vset        : 4   ; /* [3..0]  */
        unsigned int    fephy_ldo_en          : 1   ; /* [4]  */
        unsigned int    fephy_ldo_enz         : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_FEPHY_LDO_CTRL;

/* Define the union U_PERI_COMBPHY0_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    nano_tx_pattern       : 2   ; /* [3..2]  */
        unsigned int    reserved_1            : 7   ; /* [10..4]  */
        unsigned int    nano_rx_standby       : 1   ; /* [11]  */
        unsigned int    nano_test_addr        : 5   ; /* [16..12]  */
        unsigned int    reserved_2            : 3   ; /* [19..17]  */
        unsigned int    nano_test_data        : 4   ; /* [23..20]  */
        unsigned int    nano_test_write       : 1   ; /* [24]  */
        unsigned int    reserved_3            : 3   ; /* [27..25]  */
        unsigned int    nano_buffer_mode      : 1   ; /* [28]  */
        unsigned int    reserved_4            : 2   ; /* [30..29]  */
        unsigned int    nano_bypass_codec     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY0_CFG;

/* Define the union U_PERI_COMBPHY0_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nano_align_detect     : 1   ; /* [0]  */
        unsigned int    nano_rx_standby_status : 1   ; /* [1]  */
        unsigned int    nano_rx_data_valid    : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    nano_data_bus_width   : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    nano_test_o           : 4   ; /* [11..8]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY0_STATE;

/* Define the union U_PERI_COMBPHY1_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clkref_out_oe         : 1   ; /* [0]  */
        unsigned int    clkref_out_ie         : 1   ; /* [1]  */
        unsigned int    nano_tx_pattern       : 2   ; /* [3..2]  */
        unsigned int    nano_tx_swing         : 1   ; /* [4]  */
        unsigned int    nano_tx_deemp         : 2   ; /* [6..5]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    nano_tx_margin        : 3   ; /* [10..8]  */
        unsigned int    nano_rx_standby       : 1   ; /* [11]  */
        unsigned int    nano_test_addr        : 5   ; /* [16..12]  */
        unsigned int    reserved_1            : 3   ; /* [19..17]  */
        unsigned int    nano_test_data        : 4   ; /* [23..20]  */
        unsigned int    nano_test_write       : 1   ; /* [24]  */
        unsigned int    reserved_2            : 3   ; /* [27..25]  */
        unsigned int    nano_buffer_mode      : 1   ; /* [28]  */
        unsigned int    reserved_3            : 1   ; /* [29]  */
        unsigned int    bypass_pciectrl_analog : 1   ; /* [30]  */
        unsigned int    nano_bypass_codec     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY1_CFG;

/* Define the union U_PERI_COMBPHY1_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nano_align_detect     : 1   ; /* [0]  */
        unsigned int    nano_rx_standby_status : 1   ; /* [1]  */
        unsigned int    nano_rx_data_valid    : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    nano_data_bus_width   : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    nano_test_o           : 4   ; /* [11..8]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY1_STATE;

/* Define the union U_PERI_COMBPHY2_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    nano_tx_pattern       : 2   ; /* [3..2]  */
        unsigned int    reserved_1            : 7   ; /* [10..4]  */
        unsigned int    nano_rx_standby       : 1   ; /* [11]  */
        unsigned int    nano_test_addr        : 5   ; /* [16..12]  */
        unsigned int    reserved_2            : 3   ; /* [19..17]  */
        unsigned int    nano_test_data        : 4   ; /* [23..20]  */
        unsigned int    nano_test_write       : 1   ; /* [24]  */
        unsigned int    reserved_3            : 3   ; /* [27..25]  */
        unsigned int    nano_buffer_mode      : 1   ; /* [28]  */
        unsigned int    reserved_4            : 2   ; /* [30..29]  */
        unsigned int    nano_bypass_codec     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY2_CFG;

/* Define the union U_PERI_COMBPHY2_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nano_align_detect     : 1   ; /* [0]  */
        unsigned int    nano_rx_standby_status : 1   ; /* [1]  */
        unsigned int    nano_rx_data_valid    : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    nano_data_bus_width   : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    nano_test_o           : 4   ; /* [11..8]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY2_STATE;

/* Define the union U_PERI_COMBPHY3_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    nano_tx_pattern       : 2   ; /* [3..2]  */
        unsigned int    nano_tx_swing         : 1   ; /* [4]  */
        unsigned int    nano_tx_deemp         : 2   ; /* [6..5]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    nano_tx_margin        : 3   ; /* [10..8]  */
        unsigned int    nano_rx_standby       : 1   ; /* [11]  */
        unsigned int    nano_test_addr        : 5   ; /* [16..12]  */
        unsigned int    reserved_2            : 3   ; /* [19..17]  */
        unsigned int    nano_test_data        : 4   ; /* [23..20]  */
        unsigned int    nano_test_write       : 1   ; /* [24]  */
        unsigned int    reserved_3            : 3   ; /* [27..25]  */
        unsigned int    nano_buffer_mode      : 2   ; /* [29..28]  */
        unsigned int    bypass_pciectrl_analog : 1   ; /* [30]  */
        unsigned int    nano_bypass_codec     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY3_CFG;

/* Define the union U_PERI_COMBPHY3_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nano_align_detect     : 1   ; /* [0]  */
        unsigned int    nano_rx_standby_status : 1   ; /* [1]  */
        unsigned int    nano_rx_data_valid    : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    nano_data_bus_width   : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    nano_test_o           : 4   ; /* [11..8]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY3_STATE;

/* Define the union U_PERI_SOC_FUSE_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    otp_control0_usb3     : 1   ; /* [2]  */
        unsigned int    reserved_1            : 1   ; /* [3]  */
        unsigned int    otp_ctrl_uart_core    : 1   ; /* [4]  */
        unsigned int    otp_ctrl_uart_mcu     : 1   ; /* [5]  */
        unsigned int    reserved_2            : 2   ; /* [7..6]  */
        unsigned int    romboot_sel_lock      : 1   ; /* [8]  */
        unsigned int    otp_vdh_real          : 1   ; /* [9]  */
        unsigned int    otp_vdh_divx3         : 1   ; /* [10]  */
        unsigned int    otp_vdh_vc1           : 1   ; /* [11]  */
        unsigned int    otp_vdh_vp6           : 1   ; /* [12]  */
        unsigned int    otp_vdh_vp8           : 1   ; /* [13]  */
        unsigned int    otp_vdh_h264          : 1   ; /* [14]  */
        unsigned int    otp_vdh_mpeg4         : 1   ; /* [15]  */
        unsigned int    otp_vdh_avs           : 1   ; /* [16]  */
        unsigned int    reserved_3            : 2   ; /* [18..17]  */
        unsigned int    otp_ctrl_usb_1p       : 1   ; /* [19]  */
        unsigned int    otp_ctrl_tsi          : 1   ; /* [20]  */
        unsigned int    reserved_4            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_SOC_FUSE_1;

/* Define the union U_PERI_SOC_FUSE_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    otp_vdh_mpg2          : 1   ; /* [0]  */
        unsigned int    otp_vdh_h265          : 1   ; /* [1]  */
        unsigned int    otp_vdh_4k_2k         : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_SOC_FUSE_2;

/* Define the union U_PERI_SPINAND_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ctrl_bus              : 6   ; /* [5..0]  */
        unsigned int    dev_internal_ecc      : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_SPINAND_CTRL;

/* Define the union U_PERI_HDMITX_CTRL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdmitx_aud_id         : 5   ; /* [4..0]  */
        unsigned int    hdmitx_avcttpt        : 6   ; /* [10..5]  */
        unsigned int    reserved_0            : 2   ; /* [12..11]  */
        unsigned int    hdmitx_hdcp2tx_cupd_done : 1   ; /* [13]  */
        unsigned int    hdmitx_hdcp2tx_cupd_hw : 1   ; /* [14]  */
        unsigned int    hdmitx_hdcp2tx_cupd_strart : 1   ; /* [15]  */
        unsigned int    hdmitx_idck2pclk_ratio : 2   ; /* [17..16]  */
        unsigned int    hdmitx_pclknx2pclk_ratio : 2   ; /* [19..18]  */
        unsigned int    hdmitx_tclk2pclknx_ratio : 2   ; /* [21..20]  */
        unsigned int    reserved_1            : 3   ; /* [24..22]  */
        unsigned int    hdmitx_hdcp2tx_cchk_done : 1   ; /* [25]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_HDMITX_CTRL0;

/* Define the union U_PERI_HDMIRX_CTRL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdmirx_5v_det_mux     : 1   ; /* [0]  */
        unsigned int    hdmirx_5v_det_reg     : 1   ; /* [1]  */
        unsigned int    hdmirx_hpd_pctrl      : 1   ; /* [2]  */
        unsigned int    hdmirx_pwr_pctrl      : 1   ; /* [3]  */
        unsigned int    hdmirx_2p0_rx_spi_spi_boot_start : 1   ; /* [4]  */
        unsigned int    hdmirx_pram_switch_spi2apb : 1   ; /* [5]  */
        unsigned int    reserved_0            : 20  ; /* [25..6]  */
        unsigned int    hdmirx_hdmin_mode     : 1   ; /* [26]  */
        unsigned int    hdmirx_mhl3_mode      : 1   ; /* [27]  */
        unsigned int    hdmirx_phy_mhl3_mode  : 1   ; /* [28]  */
        unsigned int    hdmirx_mhl_cd_sense   : 1   ; /* [29]  */
        unsigned int    hdmirx_mhl1x_mode     : 1   ; /* [30]  */
        unsigned int    hdmirx_mhlpp_mode     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_HDMIRX_CTRL0;

/* Define the union U_PERI_HDMIRX_CTRL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdmirx_2p0_config_dummy : 30  ; /* [29..0]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_HDMIRX_CTRL1;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_START_MODE           START_MODE               ; /* 0x0 */
    volatile unsigned int           reserved_0                     ; /* 0x4 */
    volatile U_PERI_CTRL            PERI_CTRL                ; /* 0x8 */
    volatile U_PMU_STAT             PMU_STAT                 ; /* 0xc */
    volatile unsigned int           reserved_1[12]                     ; /* 0x10~0x3c */
    volatile U_PERI_QOS_GLOB_CTRL   PERI_QOS_GLOB_CTRL       ; /* 0x40 */
    volatile U_PERI_QOS_CFG0        PERI_QOS_CFG0            ; /* 0x44 */
    volatile U_PERI_QOS_CFG1        PERI_QOS_CFG1            ; /* 0x48 */
    volatile U_PERI_QOS_CFG2        PERI_QOS_CFG2            ; /* 0x4c */
    volatile U_PERI_QOS_CFG3        PERI_QOS_CFG3            ; /* 0x50 */
    volatile U_PERI_QOS_CFG4        PERI_QOS_CFG4            ; /* 0x54 */
    volatile U_PERI_QOS_CFG5        PERI_QOS_CFG5            ; /* 0x58 */
    volatile U_PERI_QOS_CFG6        PERI_QOS_CFG6            ; /* 0x5c */
    volatile U_PERI_QOS_CFG7        PERI_QOS_CFG7            ; /* 0x60 */
    volatile unsigned int           reserved_2[20]                     ; /* 0x64~0xb0 */
    volatile U_PERI_USB_RESUME_INT_MASK   PERI_USB_RESUME_INT_MASK ; /* 0xb4 */
    volatile U_PERI_USB_RESUME_INT_RAWSTAT   PERI_USB_RESUME_INT_RAWSTAT ; /* 0xb8 */
    volatile U_PERI_USB_RESUME_INT_STAT   PERI_USB_RESUME_INT_STAT ; /* 0xbc */
    volatile U_PERI_INT_A9TOMCE     PERI_INT_A9TOMCE         ; /* 0xc0 */
    volatile unsigned int           reserved_3[8]                     ; /* 0xc4~0xe0 */
    volatile U_PERI_INT_SWI0        PERI_INT_SWI0            ; /* 0xe4 */
    volatile U_PERI_INT_SWI1        PERI_INT_SWI1            ; /* 0xe8 */
    volatile U_PERI_INT_SWI2        PERI_INT_SWI2            ; /* 0xec */
    volatile U_PERI_INT_SWI0_MASK   PERI_INT_SWI0_MASK       ; /* 0xf0 */
    volatile U_PERI_INT_SWI1_MASK   PERI_INT_SWI1_MASK       ; /* 0xf4 */
    volatile U_PERI_INT_SWI2_MASK   PERI_INT_SWI2_MASK       ; /* 0xf8 */
    volatile unsigned int           reserved_4                     ; /* 0xfc */
    volatile U_PERI_QAM             PERI_QAM                 ; /* 0x100 */
    volatile U_PERI_QAM_ADC0        PERI_QAM_ADC0            ; /* 0x104 */
    volatile unsigned int           reserved_5[2]                     ; /* 0x108~0x10c */
    volatile U_PERI_TIANLA_ADAC0    PERI_TIANLA_ADAC0        ; /* 0x110 */
    volatile U_PERI_TIANLA_ADAC1    PERI_TIANLA_ADAC1        ; /* 0x114 */
    volatile U_PERI_FEPHY           PERI_FEPHY               ; /* 0x118 */
    volatile U_PERI_SD_LDO          PERI_SD_LDO              ; /* 0x11c */
    volatile U_PERI_USB0            PERI_USB0                ; /* 0x120 */
    volatile U_PERI_USB1            PERI_USB1                ; /* 0x124 */
    volatile U_PERI_USB2            PERI_USB2                ; /* 0x128 */
    volatile U_PERI_USB3            PERI_USB3                ; /* 0x12c */
    volatile U_PERI_USB4            PERI_USB4                ; /* 0x130 */
    volatile U_PERI_USB5            PERI_USB5                ; /* 0x134 */
    volatile U_PERI_USB6            PERI_USB6                ; /* 0x138 */
    volatile U_PERI_USB7            PERI_USB7                ; /* 0x13c */
    volatile U_PERI_USB8            PERI_USB8                ; /* 0x140 */
    volatile unsigned int           reserved_6[7]                     ; /* 0x144~0x15c */
    volatile U_PERI_TIANLA_ADAC2    PERI_TIANLA_ADAC2        ; /* 0x160 */
    volatile unsigned int           reserved_7                     ; /* 0x164 */
    volatile U_PERI_FEPHY_GP_I      PERI_FEPHY_GP_I          ; /* 0x168 */
    volatile unsigned int           reserved_8[18]                     ; /* 0x16c~0x1b0 */
    volatile U_PERI_DDRPHY_TEST0    PERI_DDRPHY_TEST0        ; /* 0x1b4 */
    volatile U_PERI_DDRPHY_TEST1    PERI_DDRPHY_TEST1        ; /* 0x1b8 */
    volatile unsigned int           reserved_9[9]                     ; /* 0x1bc~0x1dc */
    volatile U_CHIPSET_INFO         CHIPSET_INFO             ; /* 0x1e0 */
    volatile unsigned int           reserved_10[3]                     ; /* 0x1e4~0x1ec */
    volatile unsigned int           PERI_SW_SET              ; /* 0x1f0 */
    volatile unsigned int           reserved_11[402]                     ; /* 0x1f4~0x838 */
    volatile U_PERI_SIM_OD_CTRL     PERI_SIM_OD_CTRL         ; /* 0x83c */
    volatile U_PERI_SOC_FUSE_0      PERI_SOC_FUSE_0          ; /* 0x840 */
    volatile U_PERI_FEPHY_LDO_CTRL   PERI_FEPHY_LDO_CTRL     ; /* 0x844 */
    volatile unsigned int           reserved_12[2]                     ; /* 0x848~0x84c */
    volatile U_PERI_COMBPHY0_CFG    PERI_COMBPHY0_CFG        ; /* 0x850 */
    volatile U_PERI_COMBPHY0_STATE   PERI_COMBPHY0_STATE     ; /* 0x854 */
    volatile U_PERI_COMBPHY1_CFG    PERI_COMBPHY1_CFG        ; /* 0x858 */
    volatile U_PERI_COMBPHY1_STATE   PERI_COMBPHY1_STATE     ; /* 0x85c */
    volatile U_PERI_COMBPHY2_CFG    PERI_COMBPHY2_CFG        ; /* 0x860 */
    volatile U_PERI_COMBPHY2_STATE   PERI_COMBPHY2_STATE     ; /* 0x864 */
    volatile U_PERI_COMBPHY3_CFG    PERI_COMBPHY3_CFG        ; /* 0x868 */
    volatile U_PERI_COMBPHY3_STATE   PERI_COMBPHY3_STATE     ; /* 0x86c */
    volatile U_PERI_SOC_FUSE_1      PERI_SOC_FUSE_1          ; /* 0x870 */
    volatile U_PERI_SOC_FUSE_2      PERI_SOC_FUSE_2          ; /* 0x874 */
    volatile unsigned int           reserved_13[9]                     ; /* 0x878~0x898 */
    volatile U_PERI_SPINAND_CTRL    PERI_SPINAND_CTRL        ; /* 0x89c */
    volatile unsigned int           reserved_14[4]                     ; /* 0x8a0~0x8ac */
    volatile U_PERI_HDMITX_CTRL0    PERI_HDMITX_CTRL0        ; /* 0x8b0 */
    volatile unsigned int           PERI_HDMITX_CTRL1        ; /* 0x8b4 */
    volatile U_PERI_HDMIRX_CTRL0    PERI_HDMIRX_CTRL0        ; /* 0x8b8 */
    volatile U_PERI_HDMIRX_CTRL1    PERI_HDMIRX_CTRL1        ; /* 0x8bc */

} S_PERICTRL_REGS_TYPE;

#endif /* __HI_REG_PERI_H__ */
