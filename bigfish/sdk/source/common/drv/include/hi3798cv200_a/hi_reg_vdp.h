//******************************************************************************
// Copyright     :  Copyright (C) 2014, Hisilicon Technologies Co., Ltd.
// File name     :  c_union_define.h
// Author        :  xxx
// Version       :  1.0
// Date          :  2014-06-26
// Description   :  Define all registers/tables for vdp
// Others        :  Generated automatically by nManager V4.0
// History       :  xxx 2014-06-26 Create file
//******************************************************************************

#ifndef __C_UNION_DEFINE_H__
#define __C_UNION_DEFINE_H__

/* Define the union U_VOCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    m0_arb_mode           : 4   ; /* [3..0]  */
        unsigned int    m1_arb_mode           : 4   ; /* [7..4]  */
        unsigned int    m2_arb_mode           : 4   ; /* [11..8]  */
        unsigned int    m3_arb_mode           : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 8   ; /* [23..16]  */
        unsigned int    twochn_en             : 1   ; /* [24]  */
        unsigned int    twochn_mode           : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    g3_sel                : 1   ; /* [29]  */
        unsigned int    chk_sum_en            : 1   ; /* [30]  */
        unsigned int    vo_ck_gt_en           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOCTRL;

/* Define the union U_VOINTSTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd0vtthd1_int        : 1   ; /* [0]  */
        unsigned int    dhd0vtthd2_int        : 1   ; /* [1]  */
        unsigned int    dhd0vtthd3_int        : 1   ; /* [2]  */
        unsigned int    dhd0uf_int            : 1   ; /* [3]  */
        unsigned int    dhd1vtthd1_int        : 1   ; /* [4]  */
        unsigned int    dhd1vtthd2_int        : 1   ; /* [5]  */
        unsigned int    dhd1vtthd3_int        : 1   ; /* [6]  */
        unsigned int    dhd1uf_int            : 1   ; /* [7]  */
        unsigned int    gwbc0_vte_int         : 1   ; /* [8]  */
        unsigned int    dwbc0_vte_int         : 1   ; /* [9]  */
        unsigned int    g0wbc_vte_int         : 1   ; /* [10]  */
        unsigned int    g4wbc_vte_int         : 1   ; /* [11]  */
        unsigned int    reserved_0            : 3   ; /* [14..12]  */
        unsigned int    v0rr_int              : 1   ; /* [15]  */
        unsigned int    v1rr_int              : 1   ; /* [16]  */
        unsigned int    v3rr_int              : 1   ; /* [17]  */
        unsigned int    v4rr_int              : 1   ; /* [18]  */
        unsigned int    fi_int                : 1   ; /* [19]  */
        unsigned int    vdac0_load_int        : 1   ; /* [20]  */
        unsigned int    vdac1_load_int        : 1   ; /* [21]  */
        unsigned int    vdac2_load_int        : 1   ; /* [22]  */
        unsigned int    vdac3_load_int        : 1   ; /* [23]  */
        unsigned int    g0rr_int              : 1   ; /* [24]  */
        unsigned int    g1rr_int              : 1   ; /* [25]  */
        unsigned int    g2rr_int              : 1   ; /* [26]  */
        unsigned int    g3rr_int              : 1   ; /* [27]  */
        unsigned int    g4rr_int              : 1   ; /* [28]  */
        unsigned int    wbcdhd_partfns_int    : 1   ; /* [29]  */
        unsigned int    m0_be_int             : 1   ; /* [30]  */
        unsigned int    m1_be_int             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOINTSTA;

/* Define the union U_VOMSKINTSTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd0vtthd1_clr        : 1   ; /* [0]  */
        unsigned int    dhd0vtthd2_clr        : 1   ; /* [1]  */
        unsigned int    dhd0vtthd3_clr        : 1   ; /* [2]  */
        unsigned int    dhd0uf_clr            : 1   ; /* [3]  */
        unsigned int    dhd1vtthd1_clr        : 1   ; /* [4]  */
        unsigned int    dhd1vtthd2_clr        : 1   ; /* [5]  */
        unsigned int    dhd1vtthd3_clr        : 1   ; /* [6]  */
        unsigned int    dhd1uf_clr            : 1   ; /* [7]  */
        unsigned int    gwbc0_vte_clr         : 1   ; /* [8]  */
        unsigned int    dwbc0_vte_clr         : 1   ; /* [9]  */
        unsigned int    g0wbc_vte_clr         : 1   ; /* [10]  */
        unsigned int    g4wbc_vte_clr         : 1   ; /* [11]  */
        unsigned int    reserved_0            : 3   ; /* [14..12]  */
        unsigned int    v0rr_clr              : 1   ; /* [15]  */
        unsigned int    v1rr_clr              : 1   ; /* [16]  */
        unsigned int    v3rr_clr              : 1   ; /* [17]  */
        unsigned int    v4rr_clr              : 1   ; /* [18]  */
        unsigned int    fi_sta                : 1   ; /* [19]  */
        unsigned int    vdac0_load_clr        : 1   ; /* [20]  */
        unsigned int    vdac1_load_clr        : 1   ; /* [21]  */
        unsigned int    vdac2_load_clr        : 1   ; /* [22]  */
        unsigned int    vdac3_load_clr        : 1   ; /* [23]  */
        unsigned int    g0rr_clr              : 1   ; /* [24]  */
        unsigned int    g1rr_clr              : 1   ; /* [25]  */
        unsigned int    g2rr_clr              : 1   ; /* [26]  */
        unsigned int    g3rr_clr              : 1   ; /* [27]  */
        unsigned int    g4rr_clr              : 1   ; /* [28]  */
        unsigned int    wbcdhd_partfns_clr    : 1   ; /* [29]  */
        unsigned int    m0_be_clr             : 1   ; /* [30]  */
        unsigned int    m1_be_clr             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOMSKINTSTA;

/* Define the union U_VOINTMSK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd0vtthd1_intmsk     : 1   ; /* [0]  */
        unsigned int    dhd0vtthd2_intmsk     : 1   ; /* [1]  */
        unsigned int    dhd0vtthd3_intmsk     : 1   ; /* [2]  */
        unsigned int    dhd0uf_intmsk         : 1   ; /* [3]  */
        unsigned int    dhd1vtthd1_intmsk     : 1   ; /* [4]  */
        unsigned int    dhd1vtthd2_intmsk     : 1   ; /* [5]  */
        unsigned int    dhd1vtthd3_intmsk     : 1   ; /* [6]  */
        unsigned int    dhd1uf_intmsk         : 1   ; /* [7]  */
        unsigned int    gwbc0_vte_intmsk      : 1   ; /* [8]  */
        unsigned int    dwbc0_vte_intmsk      : 1   ; /* [9]  */
        unsigned int    g0wbc_vte_intmsk      : 1   ; /* [10]  */
        unsigned int    g4wbc_vte_intmsk      : 1   ; /* [11]  */
        unsigned int    reserved_0            : 3   ; /* [14..12]  */
        unsigned int    v0rr_intmsk           : 1   ; /* [15]  */
        unsigned int    v1rr_intmsk           : 1   ; /* [16]  */
        unsigned int    v3rr_intmsk           : 1   ; /* [17]  */
        unsigned int    v4rr_intmsk           : 1   ; /* [18]  */
        unsigned int    fi_intmsk             : 1   ; /* [19]  */
        unsigned int    vdac0_load_intmsk     : 1   ; /* [20]  */
        unsigned int    vdac1_load_intmsk     : 1   ; /* [21]  */
        unsigned int    vdac2_load_intmsk     : 1   ; /* [22]  */
        unsigned int    vdac3_load_intmsk     : 1   ; /* [23]  */
        unsigned int    g0rr_intmsk           : 1   ; /* [24]  */
        unsigned int    g1rr_intmsk           : 1   ; /* [25]  */
        unsigned int    g2rr_intmsk           : 1   ; /* [26]  */
        unsigned int    g3rr_intmsk           : 1   ; /* [27]  */
        unsigned int    g4rr_intmsk           : 1   ; /* [28]  */
        unsigned int    wbcdhd_partfns_intmsk : 1   ; /* [29]  */
        unsigned int    m0_be_intmsk          : 1   ; /* [30]  */
        unsigned int    m1_be_intmsk          : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOINTMSK;

/* Define the union U_VODEBUG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rm_en_chn             : 4   ; /* [3..0]  */
        unsigned int    dhd0_ff_info          : 2   ; /* [5..4]  */
        unsigned int    dhd1_ff_info          : 2   ; /* [7..6]  */
        unsigned int    dsd0_ff_info          : 2   ; /* [9..8]  */
        unsigned int    bfm_vga_en            : 1   ; /* [10]  */
        unsigned int    bfm_cvbs_en           : 1   ; /* [11]  */
        unsigned int    bfm_lcd_en            : 1   ; /* [12]  */
        unsigned int    bfm_bt1120_en         : 1   ; /* [13]  */
        unsigned int    wbc2_ff_info          : 2   ; /* [15..14]  */
        unsigned int    wbc_mode              : 4   ; /* [19..16]  */
        unsigned int    node_num              : 4   ; /* [23..20]  */
        unsigned int    wbc_cmp_mode          : 2   ; /* [25..24]  */
        unsigned int    bfm_mode              : 3   ; /* [28..26]  */
        unsigned int    bfm_clk_sel           : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VODEBUG;

/* Define the union U_VOINTSTA_OFL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 7   ; /* [6..0]  */
        unsigned int    ofl_vte_int           : 1   ; /* [7]  */
        unsigned int    gwbc0_vte_int         : 1   ; /* [8]  */
        unsigned int    dwbc0_vte_int         : 1   ; /* [9]  */
        unsigned int    g0wbc_vte_int         : 1   ; /* [10]  */
        unsigned int    g4wbc_vte_int         : 1   ; /* [11]  */
        unsigned int    wbcme_vte_int         : 1   ; /* [12]  */
        unsigned int    wbcfi_vte_int         : 1   ; /* [13]  */
        unsigned int    wbcbmp_vte_int        : 1   ; /* [14]  */
        unsigned int    v0rr_int              : 1   ; /* [15]  */
        unsigned int    v1rr_int              : 1   ; /* [16]  */
        unsigned int    reserved_1            : 7   ; /* [23..17]  */
        unsigned int    g0rr_int              : 1   ; /* [24]  */
        unsigned int    g1rr_int              : 1   ; /* [25]  */
        unsigned int    g2rr_int              : 1   ; /* [26]  */
        unsigned int    g3rr_int              : 1   ; /* [27]  */
        unsigned int    reserved_2            : 1   ; /* [28]  */
        unsigned int    wbcdhd_partfns_int    : 1   ; /* [29]  */
        unsigned int    m2_be_int             : 1   ; /* [30]  */
        unsigned int    m3_be_int             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOINTSTA_OFL;

/* Define the union U_VOMSKINTSTA_OFL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 7   ; /* [6..0]  */
        unsigned int    ofl_vte_clr           : 1   ; /* [7]  */
        unsigned int    gwbc0_vte_clr         : 1   ; /* [8]  */
        unsigned int    dwbc0_vte_clr         : 1   ; /* [9]  */
        unsigned int    g0wbc_vte_clr         : 1   ; /* [10]  */
        unsigned int    g4wbc_vte_clr         : 1   ; /* [11]  */
        unsigned int    wbcme_vte_clr         : 1   ; /* [12]  */
        unsigned int    wbcfi_vte_clr         : 1   ; /* [13]  */
        unsigned int    wbcbmp_vte_clr        : 1   ; /* [14]  */
        unsigned int    v0rr_clr              : 1   ; /* [15]  */
        unsigned int    v1rr_clr              : 1   ; /* [16]  */
        unsigned int    reserved_1            : 7   ; /* [23..17]  */
        unsigned int    g0rr_clr              : 1   ; /* [24]  */
        unsigned int    g1rr_clr              : 1   ; /* [25]  */
        unsigned int    g2rr_clr              : 1   ; /* [26]  */
        unsigned int    g3rr_clr              : 1   ; /* [27]  */
        unsigned int    reserved_2            : 1   ; /* [28]  */
        unsigned int    wbcdhd_partfns_clr    : 1   ; /* [29]  */
        unsigned int    m2_be_clr             : 1   ; /* [30]  */
        unsigned int    m3_be_clr             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOMSKINTSTA_OFL;

/* Define the union U_VOINTMSK_OFL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 7   ; /* [6..0]  */
        unsigned int    ofl_vte_intmsk        : 1   ; /* [7]  */
        unsigned int    gwbc0_vte_intmsk      : 1   ; /* [8]  */
        unsigned int    dwbc0_vte_intmsk      : 1   ; /* [9]  */
        unsigned int    g0wbc_vte_intmsk      : 1   ; /* [10]  */
        unsigned int    g4wbc_vte_intmsk      : 1   ; /* [11]  */
        unsigned int    wbcme_vte_intmsk      : 1   ; /* [12]  */
        unsigned int    wbcfi_vte_intmsk      : 1   ; /* [13]  */
        unsigned int    wbcbmp_vte_intmsk     : 1   ; /* [14]  */
        unsigned int    v0rr_intmsk           : 1   ; /* [15]  */
        unsigned int    v1rr_intmsk           : 1   ; /* [16]  */
        unsigned int    reserved_1            : 7   ; /* [23..17]  */
        unsigned int    g0rr_intmsk           : 1   ; /* [24]  */
        unsigned int    g1rr_intmsk           : 1   ; /* [25]  */
        unsigned int    g2rr_intmsk           : 1   ; /* [26]  */
        unsigned int    g3rr_intmsk           : 1   ; /* [27]  */
        unsigned int    reserved_2            : 1   ; /* [28]  */
        unsigned int    wbcdhd_partfns_intmsk : 1   ; /* [29]  */
        unsigned int    m2_be_intmsk          : 1   ; /* [30]  */
        unsigned int    m3_be_intmsk          : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOINTMSK_OFL;

/* Define the union U_VDPVERSION1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vdpversion1            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VDPVERSION1;
/* Define the union U_VDPVERSION2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vdpversion2            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VDPVERSION2;
/* Define the union U_VOAXICTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    m0_outstd_rid0        : 4   ; /* [3..0]  */
        unsigned int    m0_outstd_rid1        : 4   ; /* [7..4]  */
        unsigned int    m0_wr_ostd            : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 3   ; /* [14..12]  */
        unsigned int    m0_mutli_id_o         : 1   ; /* [15]  */
        unsigned int    m1_outstd_rid0        : 4   ; /* [19..16]  */
        unsigned int    m1_outstd_rid1        : 4   ; /* [23..20]  */
        unsigned int    m1_wr_ostd            : 4   ; /* [27..24]  */
        unsigned int    reserved_1            : 3   ; /* [30..28]  */
        unsigned int    m1_mutli_id_o         : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOAXICTRL;

/* Define the union U_VOAXICTRL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    m2_outstd_rid0        : 4   ; /* [3..0]  */
        unsigned int    m2_outstd_rid1        : 4   ; /* [7..4]  */
        unsigned int    m2_wr_ostd            : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    m3_outstd_rid0        : 4   ; /* [19..16]  */
        unsigned int    m3_outstd_rid1        : 4   ; /* [23..20]  */
        unsigned int    m3_wr_ostd            : 4   ; /* [27..24]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOAXICTRL1;

/* Define the union U_VOMASTERSEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_master_sel         : 1   ; /* [0]  */
        unsigned int    v1_master_sel         : 1   ; /* [1]  */
        unsigned int    v2_master_sel         : 1   ; /* [2]  */
        unsigned int    v3_master_sel         : 1   ; /* [3]  */
        unsigned int    v4_master_sel         : 1   ; /* [4]  */
        unsigned int    v5_master_sel         : 1   ; /* [5]  */
        unsigned int    v6_master_sel         : 1   ; /* [6]  */
        unsigned int    v7_master_sel         : 1   ; /* [7]  */
        unsigned int    v8_master_sel         : 1   ; /* [8]  */
        unsigned int    v9_master_sel         : 1   ; /* [9]  */
        unsigned int    vhd_str_master_sel    : 1   ; /* [10]  */
        unsigned int    vhd_stw_master_sel    : 1   ; /* [11]  */
        unsigned int    vad_str_master_sel    : 1   ; /* [12]  */
        unsigned int    vad_stw_master_sel    : 1   ; /* [13]  */
        unsigned int    g0_master_sel         : 1   ; /* [14]  */
        unsigned int    g1_master_sel         : 1   ; /* [15]  */
        unsigned int    g2_master_sel         : 1   ; /* [16]  */
        unsigned int    g3_master_sel         : 1   ; /* [17]  */
        unsigned int    g4_master_sel         : 1   ; /* [18]  */
        unsigned int    g5_master_sel         : 1   ; /* [19]  */
        unsigned int    g6_master_sel         : 1   ; /* [20]  */
        unsigned int    g7_master_sel         : 1   ; /* [21]  */
        unsigned int    wbc0_master_sel       : 1   ; /* [22]  */
        unsigned int    wbc1_master_sel       : 1   ; /* [23]  */
        unsigned int    wbc2_master_sel       : 1   ; /* [24]  */
        unsigned int    wbc3_master_sel       : 1   ; /* [25]  */
        unsigned int    wbc4_master_sel       : 1   ; /* [26]  */
        unsigned int    wbc5_master_sel       : 1   ; /* [27]  */
        unsigned int    wbc6_master_sel       : 1   ; /* [28]  */
        unsigned int    wbc7_master_sel       : 1   ; /* [29]  */
        unsigned int    para_master_sel       : 1   ; /* [30]  */
        unsigned int    sddate_master_sel     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOMASTERSEL;

/* Define the union U_VOMASTERSEL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_master_sel         : 1   ; /* [0]  */
        unsigned int    v1_master_sel         : 1   ; /* [1]  */
        unsigned int    v2_master_sel         : 1   ; /* [2]  */
        unsigned int    v3_master_sel         : 1   ; /* [3]  */
        unsigned int    v4_master_sel         : 1   ; /* [4]  */
        unsigned int    v5_master_sel         : 1   ; /* [5]  */
        unsigned int    v6_master_sel         : 1   ; /* [6]  */
        unsigned int    v7_master_sel         : 1   ; /* [7]  */
        unsigned int    v8_master_sel         : 1   ; /* [8]  */
        unsigned int    v9_master_sel         : 1   ; /* [9]  */
        unsigned int    vhd_str_master_sel    : 1   ; /* [10]  */
        unsigned int    vhd_stw_master_sel    : 1   ; /* [11]  */
        unsigned int    vad_str_master_sel    : 1   ; /* [12]  */
        unsigned int    vad_stw_master_sel    : 1   ; /* [13]  */
        unsigned int    g0_master_sel         : 1   ; /* [14]  */
        unsigned int    g1_master_sel         : 1   ; /* [15]  */
        unsigned int    g2_master_sel         : 1   ; /* [16]  */
        unsigned int    g3_master_sel         : 1   ; /* [17]  */
        unsigned int    g4_master_sel         : 1   ; /* [18]  */
        unsigned int    g5_master_sel         : 1   ; /* [19]  */
        unsigned int    g6_master_sel         : 1   ; /* [20]  */
        unsigned int    g7_master_sel         : 1   ; /* [21]  */
        unsigned int    wbc0_master_sel       : 1   ; /* [22]  */
        unsigned int    wbc1_master_sel       : 1   ; /* [23]  */
        unsigned int    wbc2_master_sel       : 1   ; /* [24]  */
        unsigned int    wbc3_master_sel       : 1   ; /* [25]  */
        unsigned int    wbc4_master_sel       : 1   ; /* [26]  */
        unsigned int    wbc5_master_sel       : 1   ; /* [27]  */
        unsigned int    wbc6_master_sel       : 1   ; /* [28]  */
        unsigned int    wbc7_master_sel       : 1   ; /* [29]  */
        unsigned int    para_master_sel       : 1   ; /* [30]  */
        unsigned int    sddate_master_sel     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOMASTERSEL1;

/* Define the union U_VOWBCARB0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    prio0                 : 3   ; /* [2..0]  */
        unsigned int    prio1                 : 3   ; /* [5..3]  */
        unsigned int    prio2                 : 3   ; /* [8..6]  */
        unsigned int    prio3                 : 3   ; /* [11..9]  */
        unsigned int    prio4                 : 3   ; /* [14..12]  */
        unsigned int    prio5                 : 3   ; /* [17..15]  */
        unsigned int    prio6                 : 3   ; /* [20..18]  */
        unsigned int    reserved_0            : 7   ; /* [27..21]  */
        unsigned int    w_arb_mode            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOWBCARB0;

/* Define the union U_VOWBCARB1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    prio0                 : 3   ; /* [2..0]  */
        unsigned int    prio1                 : 3   ; /* [5..3]  */
        unsigned int    prio2                 : 3   ; /* [8..6]  */
        unsigned int    prio3                 : 3   ; /* [11..9]  */
        unsigned int    prio4                 : 3   ; /* [14..12]  */
        unsigned int    prio5                 : 3   ; /* [17..15]  */
        unsigned int    prio6                 : 3   ; /* [20..18]  */
        unsigned int    reserved_0            : 7   ; /* [27..21]  */
        unsigned int    w_arb_mode            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOWBCARB1;

/* Define the union U_VOWBCARB2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    prio0                 : 3   ; /* [2..0]  */
        unsigned int    prio1                 : 3   ; /* [5..3]  */
        unsigned int    prio2                 : 3   ; /* [8..6]  */
        unsigned int    prio3                 : 3   ; /* [11..9]  */
        unsigned int    prio4                 : 3   ; /* [14..12]  */
        unsigned int    prio5                 : 3   ; /* [17..15]  */
        unsigned int    prio6                 : 3   ; /* [20..18]  */
        unsigned int    reserved_0            : 7   ; /* [27..21]  */
        unsigned int    w_arb_mode            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOWBCARB2;

/* Define the union U_VOWBCARB3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    prio0                 : 3   ; /* [2..0]  */
        unsigned int    prio1                 : 3   ; /* [5..3]  */
        unsigned int    prio2                 : 3   ; /* [8..6]  */
        unsigned int    prio3                 : 3   ; /* [11..9]  */
        unsigned int    prio4                 : 3   ; /* [14..12]  */
        unsigned int    prio5                 : 3   ; /* [17..15]  */
        unsigned int    prio6                 : 3   ; /* [20..18]  */
        unsigned int    reserved_0            : 7   ; /* [27..21]  */
        unsigned int    w_arb_mode            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOWBCARB3;

/* Define the union U_VOUFSTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_uf_sta             : 1   ; /* [0]  */
        unsigned int    v1_uf_sta             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    v3_uf_sta             : 1   ; /* [3]  */
        unsigned int    reserved_1            : 4   ; /* [7..4]  */
        unsigned int    g0_uf_sta             : 1   ; /* [8]  */
        unsigned int    g1_uf_sta             : 1   ; /* [9]  */
        unsigned int    g2_uf_sta             : 1   ; /* [10]  */
        unsigned int    g3_uf_sta             : 1   ; /* [11]  */
        unsigned int    g4_uf_sta             : 1   ; /* [12]  */
        unsigned int    reserved_2            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOUFSTA;

/* Define the union U_VOUFCLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_uf_clr             : 1   ; /* [0]  */
        unsigned int    v1_uf_clr             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    v3_uf_clr             : 1   ; /* [3]  */
        unsigned int    reserved_1            : 4   ; /* [7..4]  */
        unsigned int    g0_uf_clr             : 1   ; /* [8]  */
        unsigned int    g1_uf_clr             : 1   ; /* [9]  */
        unsigned int    g2_uf_clr             : 1   ; /* [10]  */
        unsigned int    g3_uf_clr             : 1   ; /* [11]  */
        unsigned int    g4_uf_clr             : 1   ; /* [12]  */
        unsigned int    reserved_2            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOUFCLR;

/* Define the union U_VOULTCSTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    latency_aver          : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    latency_max           : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOULTCSTA;

/* Define the union U_VOULTCCLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    latency_clr           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 30  ; /* [30..1]  */
        unsigned int    latency_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOULTCCLR;

/* Define the union U_VOINTPROC_TIM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vointproc_time        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOINTPROC_TIM;

/* Define the union U_VO_MUX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sddate_sel            : 1   ; /* [0]  */
        unsigned int    hddate_sel            : 1   ; /* [1]  */
        unsigned int    vga_sel               : 1   ; /* [2]  */
        unsigned int    hdmi_sel              : 1   ; /* [3]  */
        unsigned int    digital_sel           : 2   ; /* [5..4]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_MUX;

/* Define the union U_VO_MUX_DAC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac0_sel              : 4   ; /* [3..0]  */
        unsigned int    dac1_sel              : 4   ; /* [7..4]  */
        unsigned int    dac2_sel              : 4   ; /* [11..8]  */
        unsigned int    dac3_sel              : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_MUX_DAC;

/* Define the union U_VO_DAC_CTRL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 16  ; /* [15..0]  */
        unsigned int    trim_vcml             : 3   ; /* [18..16]  */
        unsigned int    reserved_1            : 11  ; /* [29..19]  */
        unsigned int    mode_bg               : 1   ; /* [30]  */
        unsigned int    en_bg                 : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_CTRL0;

/* Define the union U_VO_DAC_C_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 15  ; /* [14..0]  */
        unsigned int    ct_c                  : 6   ; /* [20..15]  */
        unsigned int    reserved_1            : 10  ; /* [30..21]  */
        unsigned int    en_c                  : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_C_CTRL;

/* Define the union U_VO_DAC_R_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 15  ; /* [14..0]  */
        unsigned int    ct_r                  : 6   ; /* [20..15]  */
        unsigned int    reserved_1            : 10  ; /* [30..21]  */
        unsigned int    en_r                  : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_R_CTRL;

/* Define the union U_VO_DAC_G_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 15  ; /* [14..0]  */
        unsigned int    ct_g                  : 6   ; /* [20..15]  */
        unsigned int    reserved_1            : 10  ; /* [30..21]  */
        unsigned int    en_g                  : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_G_CTRL;

/* Define the union U_VO_DAC_B_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 15  ; /* [14..0]  */
        unsigned int    ct_b                  : 6   ; /* [20..15]  */
        unsigned int    reserved_1            : 10  ; /* [30..21]  */
        unsigned int    en_b                  : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_B_CTRL;

/* Define the union U_VO_DAC_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdac_finetuning       : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 23  ; /* [28..6]  */
        unsigned int    vdac_gain             : 2   ; /* [30..29]  */
        unsigned int    vdac_pd               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_CTRL;

/* Define the union U_WBC_DHD_LOCATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_dhd_locate        : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD_LOCATE;

/* Define the union U_WBC_OFL_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_ofl_en            : 1   ; /* [0]  */
        unsigned int    wbc_ofl_pro           : 1   ; /* [1]  */
        unsigned int    reserved_0            : 25  ; /* [26..2]  */
        unsigned int    ofl_rst               : 1   ; /* [27]  */
        unsigned int    ofl_start             : 1   ; /* [28]  */
        unsigned int    ofl_disp_mode         : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_OFL_EN;

/* Define the union U_WBC_OFL_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    h                     : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_OFL_RESO;

/* Define the union U_IPTIMING */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsync_bp_wide         : 6   ; /* [5..0]  */
        unsigned int    hsync_fp_wide         : 6   ; /* [11..6]  */
        unsigned int    hsync_cp_wide         : 6   ; /* [17..12]  */
        unsigned int    vsync_bp_wide         : 5   ; /* [22..18]  */
        unsigned int    vsync_fp_wide         : 5   ; /* [27..23]  */
        unsigned int    vsync_cp_wide         : 2   ; /* [29..28]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IPTIMING;

/* Define the union U_IPSEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ip_2dto3d_sel         : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IPSEL;

/* Define the union U_COEF_DATA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_data              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_COEF_DATA;
/* Define the union U_V0_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_hlcoef_rd          : 1   ; /* [0]  */
        unsigned int    v0_hccoef_rd          : 1   ; /* [1]  */
        unsigned int    v0_vlcoef_rd          : 1   ; /* [2]  */
        unsigned int    v0_vccoef_rd          : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_PARARD;

/* Define the union U_V1_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v1_hlcoef_rd          : 1   ; /* [0]  */
        unsigned int    v1_hccoef_rd          : 1   ; /* [1]  */
        unsigned int    v1_vlcoef_rd          : 1   ; /* [2]  */
        unsigned int    v1_vccoef_rd          : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_PARARD;

/* Define the union U_V3_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v3_hlcoef_rd          : 1   ; /* [0]  */
        unsigned int    v3_hccoef_rd          : 1   ; /* [1]  */
        unsigned int    v3_vlcoef_rd          : 1   ; /* [2]  */
        unsigned int    v3_vccoef_rd          : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V3_PARARD;

/* Define the union U_V4_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v4_hlcoef_rd          : 1   ; /* [0]  */
        unsigned int    v4_hccoef_rd          : 1   ; /* [1]  */
        unsigned int    v4_vlcoef_rd          : 1   ; /* [2]  */
        unsigned int    v4_vccoef_rd          : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V4_PARARD;

/* Define the union U_VP0_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vp0_acmlut_rd         : 1   ; /* [0]  */
        unsigned int    vp0_dcihbw_rd         : 1   ; /* [1]  */
        unsigned int    vp0_dcidiv_rd         : 1   ; /* [2]  */
        unsigned int    vp0_dcilut_rd         : 1   ; /* [3]  */
        unsigned int    vp0_sharplut_rd       : 1   ; /* [4]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_PARARD;

/* Define the union U_GP0_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gp0_hlcoef_rd         : 1   ; /* [0]  */
        unsigned int    gp0_hccoef_rd         : 1   ; /* [1]  */
        unsigned int    gp0_vlcoef_rd         : 1   ; /* [2]  */
        unsigned int    gp0_vccoef_rd         : 1   ; /* [3]  */
        unsigned int    gp0_gti_hlcoef_rd     : 1   ; /* [4]  */
        unsigned int    gp0_gti_hccoef_rd     : 1   ; /* [5]  */
        unsigned int    gp0_gti_vlcoef_rd     : 1   ; /* [6]  */
        unsigned int    gp0_gti_vccoef_rd     : 1   ; /* [7]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_PARARD;

/* Define the union U_GP1_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gp1_hlcoef_rd         : 1   ; /* [0]  */
        unsigned int    gp1_hccoef_rd         : 1   ; /* [1]  */
        unsigned int    gp1_vlcoef_rd         : 1   ; /* [2]  */
        unsigned int    gp1_vccoef_rd         : 1   ; /* [3]  */
        unsigned int    gp1_gti_hlcoef_rd     : 1   ; /* [4]  */
        unsigned int    gp1_gti_hccoef_rd     : 1   ; /* [5]  */
        unsigned int    gp1_gti_vlcoef_rd     : 1   ; /* [6]  */
        unsigned int    gp1_gti_vccoef_rd     : 1   ; /* [7]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP1_PARARD;

/* Define the union U_WBC_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbcdhd_hlcoef_rd      : 1   ; /* [0]  */
        unsigned int    wbcdhd_hccoef_rd      : 1   ; /* [1]  */
        unsigned int    wbcdhd_vlcoef_rd      : 1   ; /* [2]  */
        unsigned int    wbcdhd_vccoef_rd      : 1   ; /* [3]  */
        unsigned int    wbcme_hlcoef_rd       : 1   ; /* [4]  */
        unsigned int    reserved_0            : 1   ; /* [5]  */
        unsigned int    wbcme_vlcoef_rd       : 1   ; /* [6]  */
        unsigned int    reserved_1            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_PARARD;

/* Define the union U_DHD0_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd0_gmm_rd           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    dhd_hlcoef_rd         : 1   ; /* [4]  */
        unsigned int    dhd_hccoef_rd         : 1   ; /* [5]  */
        unsigned int    dhd_vlcoef_rd         : 1   ; /* [6]  */
        unsigned int    dhd_vccoef_rd         : 1   ; /* [7]  */
        unsigned int    dhd_dimhcoef_rd       : 1   ; /* [8]  */
        unsigned int    dhd_dimvcoef_rd       : 1   ; /* [9]  */
        unsigned int    dhd_dimcoef_rd        : 1   ; /* [10]  */
        unsigned int    reserved_1            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_PARARD;

/* Define the union U_DHD1_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd1_gmm_rd           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD1_PARARD;

/* Define the union U_V0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ifmt                  : 4   ; /* [3..0]  */
        unsigned int    vicap_abnm_en         : 1   ; /* [4]  */
        unsigned int    req_ctrl              : 3   ; /* [7..5]  */
        unsigned int    dcmp_en               : 1   ; /* [8]  */
        unsigned int    reserved_0            : 1   ; /* [9]  */
        unsigned int    nosec_flag            : 1   ; /* [10]  */
        unsigned int    uv_order              : 1   ; /* [11]  */
        unsigned int    chm_rmode             : 2   ; /* [13..12]  */
        unsigned int    lm_rmode              : 2   ; /* [15..14]  */
        unsigned int    reserved_1            : 1   ; /* [16]  */
        unsigned int    vup_mode              : 1   ; /* [17]  */
        unsigned int    ifir_mode             : 2   ; /* [19..18]  */
        unsigned int    ofl_master            : 1   ; /* [20]  */
        unsigned int    es_en                 : 1   ; /* [21]  */
        unsigned int    fi_vscale             : 1   ; /* [22]  */
        unsigned int    chroma_copy           : 1   ; /* [23]  */
        unsigned int    twodt3d_en            : 1   ; /* [24]  */
        unsigned int    reserved_2            : 1   ; /* [25]  */
        unsigned int    flip_en               : 1   ; /* [26]  */
        unsigned int    mute_en               : 1   ; /* [27]  */
        unsigned int    data_width            : 2   ; /* [29..28]  */
        unsigned int    surface_c_en          : 1   ; /* [30]  */
        unsigned int    surface_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CTRL;

/* Define the union U_V0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_UPD;

/* Define the union U_V0_PRERD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 31  ; /* [30..0]  */
        unsigned int    pre_rd_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_PRERD;

/* Define the union U_V0_FI_IRESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    iw                    : 12  ; /* [11..0]  */
        unsigned int    ih                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_FI_IRESO;

/* Define the union U_V0_IRESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    iw                    : 12  ; /* [11..0]  */
        unsigned int    ih                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_IRESO;

/* Define the union U_V0_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 12  ; /* [11..0]  */
        unsigned int    oh                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ORESO;

/* Define the union U_V0_FI_REQW_0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fi_reqw_0              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_FI_REQW_0;
/* Define the union U_V0_FI_REQW_1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fi_reqw_1              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_FI_REQW_1;
/* Define the union U_V0_CBMPARA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    galpha                : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CBMPARA;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                : 12   ; /* [11..0]  */
        unsigned int    oh                : 12   ; /* [23..12]  */
        unsigned int    reserved_0_0      : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_SRORESO;


/* Define the union U_V0_PARAUP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_hlcoef_upd         : 1   ; /* [0]  */
        unsigned int    v0_hccoef_upd         : 1   ; /* [1]  */
        unsigned int    v0_vlcoef_upd         : 1   ; /* [2]  */
        unsigned int    v0_vccoef_upd         : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_PARAUP;

/* Define the union U_V0_CPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_xfpos             : 12  ; /* [11..0]  */
        unsigned int    src_xlpos             : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CPOS;

/* Define the union U_V0_DRAWMODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    draw_mode             : 2   ; /* [1..0]  */
        unsigned int    draw_mode_c           : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DRAWMODE;

/* Define the union U_V0_HLCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_HLCOEFAD;
/* Define the union U_V0_HCCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_HCCOEFAD;
/* Define the union U_V0_VLCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_VLCOEFAD;
/* Define the union U_V0_VCCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_VCCOEFAD;
/* Define the union U_V0_DFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xfpos            : 12  ; /* [11..0]  */
        unsigned int    disp_yfpos            : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DFPOS;

/* Define the union U_V0_DLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xlpos            : 12  ; /* [11..0]  */
        unsigned int    disp_ylpos            : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DLPOS;

/* Define the union U_V0_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VFPOS;

/* Define the union U_V0_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VLPOS;

/* Define the union U_V0_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_cr                : 10  ; /* [9..0]  */
        unsigned int    vbk_cb                : 10  ; /* [19..10]  */
        unsigned int    vbk_y                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_BK;

/* Define the union U_V0_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_alpha             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ALPHA;

/* Define the union U_V0_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_MUTE_BK;

/* Define the union U_V0_CSC_IDC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc0               : 11  ; /* [10..0]  */
        unsigned int    cscidc1               : 11  ; /* [21..11]  */
        unsigned int    csc_en                : 1   ; /* [22]  */
        unsigned int    csc_mode              : 3   ; /* [25..23]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CSC_IDC;

/* Define the union U_V0_CSC_ODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscodc0               : 11  ; /* [10..0]  */
        unsigned int    cscodc1               : 11  ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CSC_ODC;

/* Define the union U_V0_CSC_IODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc2               : 11  ; /* [10..0]  */
        unsigned int    cscodc2               : 11  ; /* [21..11]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CSC_IODC;

/* Define the union U_V0_CSC_P0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp00                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp01                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CSC_P0;

/* Define the union U_V0_CSC_P1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp02                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp10                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CSC_P1;

/* Define the union U_V0_CSC_P2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp11                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp12                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CSC_P2;

/* Define the union U_V0_CSC_P3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp20                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp21                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CSC_P3;

/* Define the union U_V0_CSC_P4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp22                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CSC_P4;

/* Define the union U_V0_HSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hratio                : 24  ; /* [23..0]  */
        unsigned int    hfir_order            : 1   ; /* [24]  */
        unsigned int    hchfir_en             : 1   ; /* [25]  */
        unsigned int    hlfir_en              : 1   ; /* [26]  */
        unsigned int    non_lnr_en            : 1   ; /* [27]  */
        unsigned int    hchmid_en             : 1   ; /* [28]  */
        unsigned int    hlmid_en              : 1   ; /* [29]  */
        unsigned int    hchmsc_en             : 1   ; /* [30]  */
        unsigned int    hlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HSP;

/* Define the union U_V0_HLOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_loffset           : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HLOFFSET;

/* Define the union U_V0_HCOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_coffset           : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HCOFFSET;

/* Define the union U_V0_HZONE0DELTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zone0_delta           : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HZONE0DELTA;

/* Define the union U_V0_HZONE2DELTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zone2_delta           : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HZONE2DELTA;

/* Define the union U_V0_HZONEEND */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zone0_end             : 12  ; /* [11..0]  */
        unsigned int    zone1_end             : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HZONEEND;

/* Define the union U_V0_VSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    zme_in_fmt            : 2   ; /* [20..19]  */
        unsigned int    zme_out_fmt           : 2   ; /* [22..21]  */
        unsigned int    vchfir_en             : 1   ; /* [23]  */
        unsigned int    vlfir_en              : 1   ; /* [24]  */
        unsigned int    vfir_1tap_en          : 1   ; /* [25]  */
        unsigned int    reserved_1            : 2   ; /* [27..26]  */
        unsigned int    vchmid_en             : 1   ; /* [28]  */
        unsigned int    vlmid_en              : 1   ; /* [29]  */
        unsigned int    vchmsc_en             : 1   ; /* [30]  */
        unsigned int    vlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VSP;

/* Define the union U_V0_VSR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vratio                : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VSR;

/* Define the union U_V0_VOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vchroma_offset        : 16  ; /* [15..0]  */
        unsigned int    vluma_offset          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VOFFSET;

/* Define the union U_V0_VBOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbchroma_offset       : 16  ; /* [15..0]  */
        unsigned int    vbluma_offset         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VBOFFSET;

/* Define the union U_V0_ZMECOEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_vhd_vf_cren       : 1   ; /* [0]  */
        unsigned int    apb_vhd_vf_lren       : 1   ; /* [1]  */
        unsigned int    apb_vhd_hf_cren_b     : 1   ; /* [2]  */
        unsigned int    apb_vhd_hf_cren_a     : 1   ; /* [3]  */
        unsigned int    apb_vhd_hf_lren_b     : 1   ; /* [4]  */
        unsigned int    apb_vhd_hf_lren_a     : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZMECOEF;

/* Define the union U_V0_ZMECOEFAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_vhd_coef_raddr    : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZMECOEFAD;

/* Define the union U_V0_IFIRCOEF01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef0                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef1                 : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_IFIRCOEF01;

/* Define the union U_V0_IFIRCOEF23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef2                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef3                 : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_IFIRCOEF23;

/* Define the union U_V0_IFIRCOEF45 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef4                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef5                 : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_IFIRCOEF45;

/* Define the union U_V0_IFIRCOEF67 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef6                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef7                 : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_IFIRCOEF67;

/* Define the union U_V0_P0RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P0RESO;

/* Define the union U_V0_P0LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P0LADDR;
/* Define the union U_V0_P0CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P0CADDR;
/* Define the union U_V0_P0STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P0STRIDE;

/* Define the union U_V0_P0VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P0VFPOS;

/* Define the union U_V0_P0VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P0VLPOS;

/* Define the union U_V0_P1RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P1RESO;

/* Define the union U_V0_P1LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P1LADDR;
/* Define the union U_V0_P1CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P1CADDR;
/* Define the union U_V0_P1STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P1STRIDE;

/* Define the union U_V0_P1VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P1VFPOS;

/* Define the union U_V0_P1VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P1VLPOS;

/* Define the union U_V0_P2RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P2RESO;

/* Define the union U_V0_P2LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P2LADDR;
/* Define the union U_V0_P2CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P2CADDR;
/* Define the union U_V0_P2STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P2STRIDE;

/* Define the union U_V0_P2VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P2VFPOS;

/* Define the union U_V0_P2VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P2VLPOS;

/* Define the union U_V0_P3RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P3RESO;

/* Define the union U_V0_P3LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P3LADDR;
/* Define the union U_V0_P3CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P3CADDR;
/* Define the union U_V0_P3STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P3STRIDE;

/* Define the union U_V0_P3VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P3VFPOS;

/* Define the union U_V0_P3VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P3VLPOS;

/* Define the union U_V0_P4RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P4RESO;

/* Define the union U_V0_P4LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P4LADDR;
/* Define the union U_V0_P4CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P4CADDR;
/* Define the union U_V0_P4STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P4STRIDE;

/* Define the union U_V0_P4VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P4VFPOS;

/* Define the union U_V0_P4VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P4VLPOS;

/* Define the union U_V0_P5RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P5RESO;

/* Define the union U_V0_P5LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P5LADDR;
/* Define the union U_V0_P5CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P5CADDR;
/* Define the union U_V0_P5STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P5STRIDE;

/* Define the union U_V0_P5VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P5VFPOS;

/* Define the union U_V0_P5VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P5VLPOS;

/* Define the union U_V0_P6RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P6RESO;

/* Define the union U_V0_P6LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P6LADDR;
/* Define the union U_V0_P6CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P6CADDR;
/* Define the union U_V0_P6STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P6STRIDE;

/* Define the union U_V0_P6VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P6VFPOS;

/* Define the union U_V0_P6VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P6VLPOS;

/* Define the union U_V0_P7RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P7RESO;

/* Define the union U_V0_P7LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P7LADDR;
/* Define the union U_V0_P7CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P7CADDR;
/* Define the union U_V0_P7STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P7STRIDE;

/* Define the union U_V0_P7VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P7VFPOS;

/* Define the union U_V0_P7VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P7VLPOS;

/* Define the union U_V0_P8RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P8RESO;

/* Define the union U_V0_P8LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P8LADDR;
/* Define the union U_V0_P8CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P8CADDR;
/* Define the union U_V0_P8STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P8STRIDE;

/* Define the union U_V0_P8VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P8VFPOS;

/* Define the union U_V0_P8VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P8VLPOS;

/* Define the union U_V0_P9RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P9RESO;

/* Define the union U_V0_P9LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P9LADDR;
/* Define the union U_V0_P9CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P9CADDR;
/* Define the union U_V0_P9STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P9STRIDE;

/* Define the union U_V0_P9VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P9VFPOS;

/* Define the union U_V0_P9VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P9VLPOS;

/* Define the union U_V0_P10RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P10RESO;

/* Define the union U_V0_P10LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P10LADDR;
/* Define the union U_V0_P10CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P10CADDR;
/* Define the union U_V0_P10STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P10STRIDE;

/* Define the union U_V0_P10VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P10VFPOS;

/* Define the union U_V0_P10VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P10VLPOS;

/* Define the union U_V0_P11RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P11RESO;

/* Define the union U_V0_P11LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P11LADDR;
/* Define the union U_V0_P11CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P11CADDR;
/* Define the union U_V0_P11STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P11STRIDE;

/* Define the union U_V0_P11VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P11VFPOS;

/* Define the union U_V0_P11VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P11VLPOS;

/* Define the union U_V0_P12RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P12RESO;

/* Define the union U_V0_P12LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P12LADDR;
/* Define the union U_V0_P12CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P12CADDR;
/* Define the union U_V0_P12STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P12STRIDE;

/* Define the union U_V0_P12VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P12VFPOS;

/* Define the union U_V0_P12VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P12VLPOS;

/* Define the union U_V0_P13RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P13RESO;

/* Define the union U_V0_P13LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P13LADDR;
/* Define the union U_V0_P13CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P13CADDR;
/* Define the union U_V0_P13STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P13STRIDE;

/* Define the union U_V0_P13VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P13VFPOS;

/* Define the union U_V0_P13VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P13VLPOS;

/* Define the union U_V0_P14RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P14RESO;

/* Define the union U_V0_P14LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P14LADDR;
/* Define the union U_V0_P14CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P14CADDR;
/* Define the union U_V0_P14STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P14STRIDE;

/* Define the union U_V0_P14VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P14VFPOS;

/* Define the union U_V0_P14VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P14VLPOS;

/* Define the union U_V0_P15RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    w                     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P15RESO;

/* Define the union U_V0_P15LADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P15LADDR;
/* Define the union U_V0_P15CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_P15CADDR;
/* Define the union U_V0_P15STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    surface_cstride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P15STRIDE;

/* Define the union U_V0_P15VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P15VFPOS;

/* Define the union U_V0_P15VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P15VLPOS;

/* Define the union U_V0_NADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_naddr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_NADDR;
/* Define the union U_V0_NCADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_ncaddr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_NCADDR;
/* Define the union U_V0_TILE_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tile_stride           : 16  ; /* [15..0]  */
        unsigned int    tile_cstride          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_TILE_STRIDE;

/* Define the union U_V0_MULTI_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_mode              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_MULTI_MODE;

/* Define the union U_V0_LADDROFFSET */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int laddr_offset           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_LADDROFFSET;
/* Define the union U_V0_CADDROFFSET */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int caddr_offset           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_CADDROFFSET;
/* Define the union U_V0_TILE_LOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    l_x_offset            : 8   ; /* [7..0]  */
        unsigned int    l_y_offset            : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_TILE_LOFFSET;

/* Define the union U_V0_TILE_COFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    c_x_offset            : 8   ; /* [7..0]  */
        unsigned int    c_y_offset            : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_TILE_COFFSET;

/* Define the union U_V0_16REGIONENL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p0_en                 : 1   ; /* [0]  */
        unsigned int    p1_en                 : 1   ; /* [1]  */
        unsigned int    p2_en                 : 1   ; /* [2]  */
        unsigned int    p3_en                 : 1   ; /* [3]  */
        unsigned int    p4_en                 : 1   ; /* [4]  */
        unsigned int    p5_en                 : 1   ; /* [5]  */
        unsigned int    p6_en                 : 1   ; /* [6]  */
        unsigned int    p7_en                 : 1   ; /* [7]  */
        unsigned int    p8_en                 : 1   ; /* [8]  */
        unsigned int    p9_en                 : 1   ; /* [9]  */
        unsigned int    p10_en                : 1   ; /* [10]  */
        unsigned int    p11_en                : 1   ; /* [11]  */
        unsigned int    p12_en                : 1   ; /* [12]  */
        unsigned int    p13_en                : 1   ; /* [13]  */
        unsigned int    p14_en                : 1   ; /* [14]  */
        unsigned int    p15_en                : 1   ; /* [15]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_16REGIONENL;

/* Define the union U_V0_16MUTE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p0_mute_en            : 1   ; /* [0]  */
        unsigned int    p1_mute_en            : 1   ; /* [1]  */
        unsigned int    p2_mute_en            : 1   ; /* [2]  */
        unsigned int    p3_mute_en            : 1   ; /* [3]  */
        unsigned int    p4_mute_en            : 1   ; /* [4]  */
        unsigned int    p5_mute_en            : 1   ; /* [5]  */
        unsigned int    p6_mute_en            : 1   ; /* [6]  */
        unsigned int    p7_mute_en            : 1   ; /* [7]  */
        unsigned int    p8_mute_en            : 1   ; /* [8]  */
        unsigned int    p9_mute_en            : 1   ; /* [9]  */
        unsigned int    p10_mute_en           : 1   ; /* [10]  */
        unsigned int    p11_mute_en           : 1   ; /* [11]  */
        unsigned int    p12_mute_en           : 1   ; /* [12]  */
        unsigned int    p13_mute_en           : 1   ; /* [13]  */
        unsigned int    p14_mute_en           : 1   ; /* [14]  */
        unsigned int    p15_mute_en           : 1   ; /* [15]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_16MUTE;

/* Define the union U_V0_DCMP_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    is_lossless_c         : 1   ; /* [0]  */
        unsigned int    is_lossless_l         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DCMP_CTRL;

/* Define the union U_V0_DCMP_LSTATE0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_l_state0          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_DCMP_LSTATE0;
/* Define the union U_V0_DCMP_LSTATE1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_l_state1          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_DCMP_LSTATE1;
/* Define the union U_V0_DCMP_CSTATE0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_c_state0          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_DCMP_CSTATE0;
/* Define the union U_V0_DCMP_CSTATE1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_c_state1          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_DCMP_CSTATE1;
/* Define the union U_V0_DCMPERRCLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dcmp_l_errclr         : 1   ; /* [0]  */
        unsigned int    dcmp_c_errclr         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DCMPERRCLR;

/* Define the union U_V0_DCMP_ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dcmp_l_wrong          : 1   ; /* [0]  */
        unsigned int    dcmp_c_wrong          : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DCMP_ERR;

/* Define the union U_ES_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mk_en                 : 1   ; /* [0]  */
        unsigned int    mk_mode               : 1   ; /* [1]  */
        unsigned int    reserved_0            : 22  ; /* [23..2]  */
        unsigned int    blend_mode            : 1   ; /* [24]  */
        unsigned int    edge_strength_mode    : 1   ; /* [25]  */
        unsigned int    alter_dir_en          : 1   ; /* [26]  */
        unsigned int    check2_en             : 1   ; /* [27]  */
        unsigned int    check1_en             : 1   ; /* [28]  */
        unsigned int    dir_mode              : 1   ; /* [29]  */
        unsigned int    interlaced_proc       : 1   ; /* [30]  */
        unsigned int    edge_smooth_en        : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_MODE;

/* Define the union U_ES_DIR_RATIO_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir_ratio_0           : 4   ; /* [3..0]  */
        unsigned int    dir_ratio_1           : 4   ; /* [7..4]  */
        unsigned int    dir_ratio_2           : 4   ; /* [11..8]  */
        unsigned int    dir_ratio_3           : 4   ; /* [15..12]  */
        unsigned int    dir_ratio_4           : 4   ; /* [19..16]  */
        unsigned int    dir_ratio_5           : 4   ; /* [23..20]  */
        unsigned int    dir_ratio_6           : 4   ; /* [27..24]  */
        unsigned int    dir_ratio_7           : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_DIR_RATIO_0;

/* Define the union U_ES_DIR_RATIO_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir_ratio_8           : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_DIR_RATIO_1;

/* Define the union U_ES_NORMALIZED_SCALE_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    normalized_scale_0    : 6   ; /* [5..0]  */
        unsigned int    normalized_scale_1    : 6   ; /* [11..6]  */
        unsigned int    normalized_scale_2    : 6   ; /* [17..12]  */
        unsigned int    normalized_scale_3    : 6   ; /* [23..18]  */
        unsigned int    normalized_scale_4    : 6   ; /* [29..24]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_NORMALIZED_SCALE_0;

/* Define the union U_ES_NORMALIZED_SCALE_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    normalized_scale_5    : 6   ; /* [5..0]  */
        unsigned int    normalized_scale_6    : 6   ; /* [11..6]  */
        unsigned int    normalized_scale_7    : 6   ; /* [17..12]  */
        unsigned int    normalized_scale_8    : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_NORMALIZED_SCALE_1;

/* Define the union U_ES_BC1_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    check1_deadzone       : 6   ; /* [5..0]  */
        unsigned int    check1_autodz_gain    : 6   ; /* [11..6]  */
        unsigned int    check1_gain           : 6   ; /* [17..12]  */
        unsigned int    chech1_dir_diff_gain  : 8   ; /* [25..18]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_BC1_CFG;

/* Define the union U_ES_BC2_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    check2_deadzone       : 6   ; /* [5..0]  */
        unsigned int    check2_autodz_gain    : 6   ; /* [11..6]  */
        unsigned int    check2_gain           : 6   ; /* [17..12]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_BC2_CFG;

/* Define the union U_ES_BC_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    check_gain            : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_BC_CFG;

/* Define the union U_ES_RATIO_LIMIT_SCALE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ratio_limit_scale     : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_RATIO_LIMIT_SCALE;

/* Define the union U_ES_VER_MIN_STRENGTH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ver_min_strength      : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_VER_MIN_STRENGTH;

/* Define the union U_ES_EDGE_SMOOTH_GAIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_smooth_gain      : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_EDGE_SMOOTH_GAIN;

/* Define the union U_ES_EDGE_THD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_thd_0            : 8   ; /* [7..0]  */
        unsigned int    edge_thd_1            : 8   ; /* [15..8]  */
        unsigned int    edge_thd_2            : 8   ; /* [23..16]  */
        unsigned int    edge_thd_3            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_EDGE_THD;

/* Define the union U_ES_EDGE_SMOOTH_RATIO_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_smooth_ratio_0   : 8   ; /* [7..0]  */
        unsigned int    edge_smooth_ratio_1   : 8   ; /* [15..8]  */
        unsigned int    edge_smooth_ratio_2   : 8   ; /* [23..16]  */
        unsigned int    edge_smooth_ratio_3   : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_EDGE_SMOOTH_RATIO_0;

/* Define the union U_ES_EDGE_SMOOTH_RATIO_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_smooth_ratio_4   : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_EDGE_SMOOTH_RATIO_1;

/* Define the union U_ES_EDGE_SLOPE_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_slope_0          : 11  ; /* [10..0]  */
        unsigned int    edge_slope_1          : 11  ; /* [21..11]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_EDGE_SLOPE_0;

/* Define the union U_ES_EDGE_SLOPE_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_slope_2          : 11  ; /* [10..0]  */
        unsigned int    edge_slope_3          : 11  ; /* [21..11]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_EDGE_SLOPE_1;

/* Define the union U_ES_EDGE_SLOPE_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_slope_4          : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ES_EDGE_SLOPE_2;

/* Define the union U_ES_STATUS_0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int status                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_ES_STATUS_0;
/* Define the union U_ES_STATUS_1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int status                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_ES_STATUS_1;
/* Define the union U_ES_STATUS_2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int status                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_ES_STATUS_2;
/* Define the union U_VP0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    mute_en               : 1   ; /* [8]  */
        unsigned int    vp_sel                : 1   ; /* [9]  */
        unsigned int    odd_data_mute         : 1   ; /* [10]  */
        unsigned int    even_data_mute        : 1   ; /* [11]  */
        unsigned int    reserved_1            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CTRL;

/* Define the union U_VP0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_UPD;

/* Define the union U_VP0_IRESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    iw                    : 12  ; /* [11..0]  */
        unsigned int    ih                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_IRESO;

/* Define the union U_VP0_DCI_CAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VP0_DCI_CAD;
/* Define the union U_VP0_ACM_CAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VP0_ACM_CAD;
/* Define the union U_VP0_SHARP_CAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VP0_SHARP_CAD;
/* Define the union U_VP0_PARAUP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vp0_acmcoef_upd       : 1   ; /* [0]  */
        unsigned int    vp0_acccoef_upd       : 1   ; /* [1]  */
        unsigned int    vp0_sharpcoef_upd     : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_PARAUP;

/* Define the union U_VP0_GALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    galpha                : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_GALPHA;

/* Define the union U_VP0_DFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xfpos            : 12  ; /* [11..0]  */
        unsigned int    disp_yfpos            : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DFPOS;

/* Define the union U_VP0_DLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xlpos            : 12  ; /* [11..0]  */
        unsigned int    disp_ylpos            : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DLPOS;

/* Define the union U_VP0_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_VFPOS;

/* Define the union U_VP0_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_VLPOS;

/* Define the union U_VP0_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_cr                : 10  ; /* [9..0]  */
        unsigned int    vbk_cb                : 10  ; /* [19..10]  */
        unsigned int    vbk_y                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_BK;

/* Define the union U_VP0_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_alpha             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_ALPHA;

/* Define the union U_VP0_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_MUTE_BK;

/* Define the union U_VP0_DOF_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 31  ; /* [30..0]  */
        unsigned int    dof_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DOF_CTRL;

/* Define the union U_VP0_DOF_STEP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    left_step             : 8   ; /* [7..0]  */
        unsigned int    right_step            : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DOF_STEP;

/* Define the union U_VP0_DOF_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dof_bk_cr             : 10  ; /* [9..0]  */
        unsigned int    dof_bk_cb             : 10  ; /* [19..10]  */
        unsigned int    dof_bk_y              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DOF_BKG;

/* Define the union U_VP0_CSC_IDC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc0               : 11  ; /* [10..0]  */
        unsigned int    cscidc1               : 11  ; /* [21..11]  */
        unsigned int    csc_en                : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC_IDC;

/* Define the union U_VP0_CSC_ODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscodc0               : 11  ; /* [10..0]  */
        unsigned int    cscodc1               : 11  ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC_ODC;

/* Define the union U_VP0_CSC_IODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc2               : 11  ; /* [10..0]  */
        unsigned int    cscodc2               : 11  ; /* [21..11]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC_IODC;

/* Define the union U_VP0_CSC_P0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp00                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp01                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC_P0;

/* Define the union U_VP0_CSC_P1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp02                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp10                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC_P1;

/* Define the union U_VP0_CSC_P2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp11                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp12                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC_P2;

/* Define the union U_VP0_CSC_P3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp20                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp21                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC_P3;

/* Define the union U_VP0_CSC_P4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp22                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC_P4;

/* Define the union U_VPWCG_NON2LCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    gma_lin_thre_0        : 8   ; /* [9..2]  */
        unsigned int    gma_lin_thre_1        : 10  ; /* [19..10]  */
        unsigned int    gma_lin_thre_2        : 10  ; /* [29..20]  */
        unsigned int    gma_lin_init_slp      : 1   ; /* [30]  */
        unsigned int    gma_lin_neg_scl       : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_NON2LCTRL;

/* Define the union U_VPWCG_NON2LCOEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gma_lin_coef_a_0      : 10  ; /* [9..0]  */
        unsigned int    gma_lin_coef_b_0      : 12  ; /* [21..10]  */
        unsigned int    gma_lin_coef_c_0      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_NON2LCOEF0;

/* Define the union U_VPWCG_NON2LCOEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gma_lin_coef_a_1      : 10  ; /* [9..0]  */
        unsigned int    gma_lin_coef_b_1      : 12  ; /* [21..10]  */
        unsigned int    gma_lin_coef_c_1      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_NON2LCOEF1;

/* Define the union U_VPWCG_NON2LCOEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gma_lin_coef_a_2      : 10  ; /* [9..0]  */
        unsigned int    gma_lin_coef_b_2      : 12  ; /* [21..10]  */
        unsigned int    gma_lin_coef_c_2      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_NON2LCOEF2;

/* Define the union U_VPWCG_CSC2CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_r_r_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_r_g_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 5   ; /* [28..24]  */
        unsigned int    csc2_scale_sel        : 2   ; /* [30..29]  */
        unsigned int    csc2_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_CSC2CTRL;

/* Define the union U_VPWCG_CSC2COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_r_b_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_g_r_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_CSC2COEF0;

/* Define the union U_VPWCG_CSC2COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_g_g_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_g_b_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_CSC2COEF1;

/* Define the union U_VPWCG_CSC2COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_b_r_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_b_g_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_CSC2COEF2;

/* Define the union U_VPWCG_CSC2COEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_b_b_coef         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_CSC2COEF3;

/* Define the union U_VPWCG_L2NONTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_thre_0        : 8   ; /* [7..0]  */
        unsigned int    lin_gma_thre_1        : 11  ; /* [18..8]  */
        unsigned int    lin_gma_thre_2        : 11  ; /* [29..19]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_L2NONTHD;

/* Define the union U_VPWCG_L2NONCOEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_coef_a_0      : 11  ; /* [10..0]  */
        unsigned int    lin_gma_coef_b_0      : 10  ; /* [20..11]  */
        unsigned int    lin_gma_coef_c_0      : 9   ; /* [29..21]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_L2NONCOEF0;

/* Define the union U_VPWCG_L2NONCOEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_coef_a_1      : 11  ; /* [10..0]  */
        unsigned int    lin_gma_coef_b_1      : 10  ; /* [20..11]  */
        unsigned int    lin_gma_coef_c_1      : 9   ; /* [29..21]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_L2NONCOEF1;

/* Define the union U_VPWCG_L2NONCOEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_coef_a_2      : 11  ; /* [10..0]  */
        unsigned int    lin_gma_coef_b_2      : 10  ; /* [20..11]  */
        unsigned int    lin_gma_coef_c_2      : 9   ; /* [29..21]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPWCG_L2NONCOEF2;

/* Define the union U_VP0_DCICTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 3   ; /* [2..0]  */
        unsigned int    dci_y_linear          : 11  ; /* [13..3]  */
        unsigned int    dci_stat_ctrl         : 2   ; /* [15..14]  */
        unsigned int    dci_hist_state        : 1   ; /* [16]  */
        unsigned int    dci_swcfg_en          : 1   ; /* [17]  */
        unsigned int    dci_histlpf_en        : 1   ; /* [18]  */
        unsigned int    dci_shift_ctrl        : 2   ; /* [20..19]  */
        unsigned int    dci_out_range         : 1   ; /* [21]  */
        unsigned int    dci_in_range          : 1   ; /* [22]  */
        unsigned int    dci_cbcrsta_en        : 1   ; /* [23]  */
        unsigned int    dci_cbcrcmp_en        : 1   ; /* [24]  */
        unsigned int    dci_man_adj2          : 1   ; /* [25]  */
        unsigned int    dci_man_adj1          : 1   ; /* [26]  */
        unsigned int    dci_man_adj0          : 1   ; /* [27]  */
        unsigned int    dci_scene_flg         : 1   ; /* [28]  */
        unsigned int    dci_dbg_mode          : 1   ; /* [29]  */
        unsigned int    dci_dbg_en            : 1   ; /* [30]  */
        unsigned int    dci_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCICTRL;

/* Define the union U_VP0_DCIHPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    dci_hend              : 12  ; /* [19..8]  */
        unsigned int    dci_hstart            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIHPOS;

/* Define the union U_VP0_DCIVPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    dci_vend              : 12  ; /* [19..8]  */
        unsigned int    dci_vstart            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIVPOS;

/* Define the union U_VP0_DCIHISBLD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    dci_cbcrsta_cr        : 8   ; /* [15..8]  */
        unsigned int    dci_cbcrsta_cb        : 8   ; /* [23..16]  */
        unsigned int    dci_cbcrsta_y         : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIHISBLD;

/* Define the union U_VP0_DCIHISOFT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 23  ; /* [22..0]  */
        unsigned int    dci_cbcrsta_oft       : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIHISOFT;

/* Define the union U_VP0_DCIHISCOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    dci_histcor_thr2      : 8   ; /* [15..8]  */
        unsigned int    dci_histcor_thr1      : 8   ; /* [23..16]  */
        unsigned int    dci_histcor_thr0      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIHISCOR;

/* Define the union U_VP0_DCIMERBLD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_org_abld          : 6   ; /* [7..2]  */
        unsigned int    dci_hist_abld         : 6   ; /* [13..8]  */
        unsigned int    dci_metrc_abld2       : 6   ; /* [19..14]  */
        unsigned int    dci_metrc_abld1       : 6   ; /* [25..20]  */
        unsigned int    dci_metrc_abld0       : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIMERBLD;

/* Define the union U_VP0_DCIADJWGT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    dci_man_adjwgt2       : 8   ; /* [15..8]  */
        unsigned int    dci_man_adjwgt1       : 8   ; /* [23..16]  */
        unsigned int    dci_man_adjwgt0       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJWGT;

/* Define the union U_VP0_DCICLIP0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 16  ; /* [15..0]  */
        unsigned int    dci_wgt_cliphigh0     : 8   ; /* [23..16]  */
        unsigned int    dci_wgt_cliplow0      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCICLIP0;

/* Define the union U_VP0_DCICLIP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 16  ; /* [15..0]  */
        unsigned int    dci_wgt_cliphigh1     : 8   ; /* [23..16]  */
        unsigned int    dci_wgt_cliplow1      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCICLIP1;

/* Define the union U_VP0_DCICLIP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 16  ; /* [15..0]  */
        unsigned int    dci_wgt_cliphigh2     : 8   ; /* [23..16]  */
        unsigned int    dci_wgt_cliplow2      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCICLIP2;

/* Define the union U_VP0_DCIGLBGAIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 14  ; /* [13..0]  */
        unsigned int    dci_glb_gain2         : 6   ; /* [19..14]  */
        unsigned int    dci_glb_gain1         : 6   ; /* [25..20]  */
        unsigned int    dci_glb_gain0         : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIGLBGAIN;

/* Define the union U_VP0_DCIPOSTHR0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dci_gainpos_thr4      : 8   ; /* [7..0]  */
        unsigned int    dci_gainpos_thr3      : 8   ; /* [15..8]  */
        unsigned int    dci_gainpos_thr2      : 8   ; /* [23..16]  */
        unsigned int    dci_gainpos_thr1      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIPOSTHR0;

/* Define the union U_VP0_DCIPOSTHR1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    dci_gainpos_thr7      : 8   ; /* [15..8]  */
        unsigned int    dci_gainpos_thr6      : 8   ; /* [23..16]  */
        unsigned int    dci_gainpos_thr5      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIPOSTHR1;

/* Define the union U_VP0_DCIPOSGAIN0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dci_gainpos_cbcr7     : 4   ; /* [3..0]  */
        unsigned int    dci_gainpos_cbcr6     : 4   ; /* [7..4]  */
        unsigned int    dci_gainpos_cbcr5     : 4   ; /* [11..8]  */
        unsigned int    dci_gainpos_cbcr4     : 4   ; /* [15..12]  */
        unsigned int    dci_gainpos_cbcr3     : 4   ; /* [19..16]  */
        unsigned int    dci_gainpos_cbcr2     : 4   ; /* [23..20]  */
        unsigned int    dci_gainpos_cbcr1     : 4   ; /* [27..24]  */
        unsigned int    dci_gainpos_cbcr0     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIPOSGAIN0;

/* Define the union U_VP0_DCIPOSGAIN1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 28  ; /* [27..0]  */
        unsigned int    dci_gainpos_cbcr8     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIPOSGAIN1;

/* Define the union U_VP0_DCIPOSSLP0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_gainpos_slp2      : 10  ; /* [11..2]  */
        unsigned int    dci_gainpos_slp1      : 10  ; /* [21..12]  */
        unsigned int    dci_gainpos_slp0      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIPOSSLP0;

/* Define the union U_VP0_DCIPOSSLP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_gainpos_slp5      : 10  ; /* [11..2]  */
        unsigned int    dci_gainpos_slp4      : 10  ; /* [21..12]  */
        unsigned int    dci_gainpos_slp3      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIPOSSLP1;

/* Define the union U_VP0_DCIPOSSLP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 12  ; /* [11..0]  */
        unsigned int    dci_gainpos_slp7      : 10  ; /* [21..12]  */
        unsigned int    dci_gainpos_slp6      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIPOSSLP2;

/* Define the union U_VP0_DCINEGTHR0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dci_gainneg_thr4      : 8   ; /* [7..0]  */
        unsigned int    dci_gainneg_thr3      : 8   ; /* [15..8]  */
        unsigned int    dci_gainneg_thr2      : 8   ; /* [23..16]  */
        unsigned int    dci_gainneg_thr1      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCINEGTHR0;

/* Define the union U_VP0_DCINEGTHR1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    dci_gainneg_thr7      : 8   ; /* [15..8]  */
        unsigned int    dci_gainneg_thr6      : 8   ; /* [23..16]  */
        unsigned int    dci_gainneg_thr5      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCINEGTHR1;

/* Define the union U_VP0_DCINEGGAIN0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dci_gainneg_cbcr7     : 4   ; /* [3..0]  */
        unsigned int    dci_gainneg_cbcr6     : 4   ; /* [7..4]  */
        unsigned int    dci_gainneg_cbcr5     : 4   ; /* [11..8]  */
        unsigned int    dci_gainneg_cbcr4     : 4   ; /* [15..12]  */
        unsigned int    dci_gainneg_cbcr3     : 4   ; /* [19..16]  */
        unsigned int    dci_gainneg_cbcr2     : 4   ; /* [23..20]  */
        unsigned int    dci_gainneg_cbcr1     : 4   ; /* [27..24]  */
        unsigned int    dci_gainneg_cbcr0     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCINEGGAIN0;

/* Define the union U_VP0_DCINEGGAIN1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 28  ; /* [27..0]  */
        unsigned int    dci_gainneg_cbcr8     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCINEGGAIN1;

/* Define the union U_VP0_DCINEGSLP0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_gainneg_slp2      : 10  ; /* [11..2]  */
        unsigned int    dci_gainneg_slp1      : 10  ; /* [21..12]  */
        unsigned int    dci_gainneg_slp0      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCINEGSLP0;

/* Define the union U_VP0_DCINEGSLP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_gainneg_slp5      : 10  ; /* [11..2]  */
        unsigned int    dci_gainneg_slp4      : 10  ; /* [21..12]  */
        unsigned int    dci_gainneg_slp3      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCINEGSLP1;

/* Define the union U_VP0_DCINEGSLP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 12  ; /* [11..0]  */
        unsigned int    dci_gainneg_slp7      : 10  ; /* [21..12]  */
        unsigned int    dci_gainneg_slp6      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCINEGSLP2;

/* Define the union U_VP0_DCIADJSW0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw2           : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw1           : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw0           : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW0;

/* Define the union U_VP0_DCIADJSW1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw5           : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw4           : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw3           : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW1;

/* Define the union U_VP0_DCIADJSW2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw8           : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw7           : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw6           : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW2;

/* Define the union U_VP0_DCIADJSW3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw11          : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw10          : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw9           : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW3;

/* Define the union U_VP0_DCIADJSW4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw14          : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw13          : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw12          : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW4;

/* Define the union U_VP0_DCIADJSW5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw17          : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw16          : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw15          : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW5;

/* Define the union U_VP0_DCIADJSW6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw20          : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw19          : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw18          : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW6;

/* Define the union U_VP0_DCIADJSW7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw23          : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw22          : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw21          : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW7;

/* Define the union U_VP0_DCIADJSW8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw26          : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw25          : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw24          : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW8;

/* Define the union U_VP0_DCIADJSW9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw29          : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw28          : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw27          : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW9;

/* Define the union U_VP0_DCIADJSW10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    dci_adj_sw32          : 10  ; /* [11..2]  */
        unsigned int    dci_adj_sw31          : 10  ; /* [21..12]  */
        unsigned int    dci_adj_sw30          : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIADJSW10;

/* Define the union U_VP0_DCIWGTRD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    dci_cal_adjwgt2       : 8   ; /* [15..8]  */
        unsigned int    dci_cal_adjwgt1       : 8   ; /* [23..16]  */
        unsigned int    dci_cal_adjwgt0       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCIWGTRD;

/* Define the union U_VP0_DCI_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dcihbw_rd_en          : 1   ; /* [0]  */
        unsigned int    dcidiv_rd_en          : 1   ; /* [1]  */
        unsigned int    dcilut_rd_en          : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DCI_PARARD;

/* Define the union U_VP0_DCI_PARA_DATA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_data              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VP0_DCI_PARA_DATA;
/* Define the union U_VP0_ACM_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_cbcrthr           : 9   ; /* [8..0]  */
        unsigned int    acm_dbg_mode          : 1   ; /* [9]  */
        unsigned int    reserved_0            : 17  ; /* [26..10]  */
        unsigned int    acm_cliporwrap        : 1   ; /* [27]  */
        unsigned int    acm_cliprange         : 1   ; /* [28]  */
        unsigned int    acm_stretch           : 1   ; /* [29]  */
        unsigned int    acm_dbg_en            : 1   ; /* [30]  */
        unsigned int    acm_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_ACM_CTRL;

/* Define the union U_VP0_ACM_ADJ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_gain2             : 10  ; /* [9..0]  */
        unsigned int    acm_gain1             : 10  ; /* [19..10]  */
        unsigned int    acm_gain0             : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_ACM_ADJ;

/* Define the union U_VP0_ACM_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_lut_rd_en         : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_ACM_PARARD;

/* Define the union U_VP0_ACM_PARA_DATA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_data              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VP0_ACM_PARA_DATA;
/* Define the union U_VP0_CSC1_IDC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc0               : 11  ; /* [10..0]  */
        unsigned int    cscidc1               : 11  ; /* [21..11]  */
        unsigned int    csc_en                : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC1_IDC;

/* Define the union U_VP0_CSC1_ODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscodc0               : 11  ; /* [10..0]  */
        unsigned int    cscodc1               : 11  ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC1_ODC;

/* Define the union U_VP0_CSC1_IODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc2               : 11  ; /* [10..0]  */
        unsigned int    cscodc2               : 11  ; /* [21..11]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC1_IODC;

/* Define the union U_VP0_CSC1_P0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp00                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp01                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC1_P0;

/* Define the union U_VP0_CSC1_P1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp02                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp10                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC1_P1;

/* Define the union U_VP0_CSC1_P2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp11                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp12                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC1_P2;

/* Define the union U_VP0_CSC1_P3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp20                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp21                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC1_P3;

/* Define the union U_VP0_CSC1_P4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp22                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CSC1_P4;

/* Define the union U_SPCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    debug_en              : 1   ; /* [0]  */
        unsigned int    sharpen_en            : 1   ; /* [1]  */
        unsigned int    merge_mode            : 1   ; /* [2]  */
        unsigned int    glb_oversh_thd        : 9   ; /* [11..3]  */
        unsigned int    glb_undersh_thd       : 9   ; /* [20..12]  */
        unsigned int    disp_mode             : 2   ; /* [22..21]  */
        unsigned int    demo_mode             : 2   ; /* [24..23]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTRL;

/* Define the union U_SPDETAILADJ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    detail_adj_thd        : 8   ; /* [7..0]  */
        unsigned int    detail_adj_en         : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPDETAILADJ;

/* Define the union U_SPRATIO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    color_adj_div         : 3   ; /* [2..0]  */
        unsigned int    adp_shoot_div         : 3   ; /* [5..3]  */
        unsigned int    lti_ratio             : 8   ; /* [13..6]  */
        unsigned int    peak_ratio            : 8   ; /* [21..14]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPRATIO;

/* Define the union U_SPCOLORADJ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    color_adj_high        : 10  ; /* [9..0]  */
        unsigned int    color_adj_low         : 10  ; /* [19..10]  */
        unsigned int    color_adj_en          : 1   ; /* [20]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCOLORADJ;

/* Define the union U_SPRATIOH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixratio_h1           : 8   ; /* [7..0]  */
        unsigned int    mixratio_h2           : 8   ; /* [15..8]  */
        unsigned int    mixratio_h3           : 8   ; /* [23..16]  */
        unsigned int    mixratio_h4           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPRATIOH;

/* Define the union U_SPRATIOV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixratio_v1           : 8   ; /* [7..0]  */
        unsigned int    mixratio_v2           : 8   ; /* [15..8]  */
        unsigned int    mixratio_v3           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPRATIOV;

/* Define the union U_SPRATIOD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixratio_d1           : 8   ; /* [7..0]  */
        unsigned int    mixratio_d2           : 8   ; /* [15..8]  */
        unsigned int    mixratio_d3           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPRATIOD;

/* Define the union U_SPCORINGH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coring_h1             : 8   ; /* [7..0]  */
        unsigned int    coring_h2             : 8   ; /* [15..8]  */
        unsigned int    coring_h3             : 8   ; /* [23..16]  */
        unsigned int    coring_h4             : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCORINGH;

/* Define the union U_SPCORINGV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coring_v1             : 8   ; /* [7..0]  */
        unsigned int    coring_v2             : 8   ; /* [15..8]  */
        unsigned int    coring_v3             : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCORINGV;

/* Define the union U_SPCORINGD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coring_d1             : 8   ; /* [7..0]  */
        unsigned int    coring_d2             : 8   ; /* [15..8]  */
        unsigned int    coring_d3             : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCORINGD;

/* Define the union U_SPWINSIZEHV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    winsize_v3            : 3   ; /* [2..0]  */
        unsigned int    winsize_v2            : 3   ; /* [5..3]  */
        unsigned int    winsize_v1            : 3   ; /* [8..6]  */
        unsigned int    winsize_h4            : 3   ; /* [11..9]  */
        unsigned int    winsize_h3            : 3   ; /* [14..12]  */
        unsigned int    winsize_h2            : 3   ; /* [17..15]  */
        unsigned int    winsize_h1            : 3   ; /* [20..18]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPWINSIZEHV;

/* Define the union U_SPWINSIZED */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    winsize_d3            : 3   ; /* [2..0]  */
        unsigned int    winsize_d2            : 3   ; /* [5..3]  */
        unsigned int    winsize_d1            : 3   ; /* [8..6]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPWINSIZED;

/* Define the union U_SPGRDH11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd1_h1               : 10  ; /* [9..0]  */
        unsigned int    grd0_h1               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDH11;

/* Define the union U_SPGRDH12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd3_h1               : 10  ; /* [9..0]  */
        unsigned int    grd2_h1               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDH12;

/* Define the union U_SPGRDH21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd1_h2               : 10  ; /* [9..0]  */
        unsigned int    grd0_h2               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDH21;

/* Define the union U_SPGRDH22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd3_h2               : 10  ; /* [9..0]  */
        unsigned int    grd2_h2               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDH22;

/* Define the union U_SPGRDH31 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd1_h3               : 10  ; /* [9..0]  */
        unsigned int    grd0_h3               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDH31;

/* Define the union U_SPGRDH32 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd3_h3               : 10  ; /* [9..0]  */
        unsigned int    grd2_h3               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDH32;

/* Define the union U_SPGRDH41 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd1_h4               : 10  ; /* [9..0]  */
        unsigned int    grd0_h4               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDH41;

/* Define the union U_SPGRDH42 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd3_h4               : 10  ; /* [9..0]  */
        unsigned int    grd2_h4               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDH42;

/* Define the union U_SPGRDV0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd0_v3               : 10  ; /* [9..0]  */
        unsigned int    grd0_v2               : 10  ; /* [19..10]  */
        unsigned int    grd0_v1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDV0;

/* Define the union U_SPGRDV1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd1_v3               : 10  ; /* [9..0]  */
        unsigned int    grd1_v2               : 10  ; /* [19..10]  */
        unsigned int    grd1_v1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDV1;

/* Define the union U_SPGRDV2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd2_v3               : 10  ; /* [9..0]  */
        unsigned int    grd2_v2               : 10  ; /* [19..10]  */
        unsigned int    grd2_v1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDV2;

/* Define the union U_SPGRDV3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd3_v3               : 10  ; /* [9..0]  */
        unsigned int    grd3_v2               : 10  ; /* [19..10]  */
        unsigned int    grd3_v1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDV3;

/* Define the union U_SPGRDD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd0_d3               : 10  ; /* [9..0]  */
        unsigned int    grd0_d2               : 10  ; /* [19..10]  */
        unsigned int    grd0_d1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDD0;

/* Define the union U_SPGRDD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd1_d3               : 10  ; /* [9..0]  */
        unsigned int    grd1_d2               : 10  ; /* [19..10]  */
        unsigned int    grd1_d1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDD1;

/* Define the union U_SPGRDD2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd2_d3               : 10  ; /* [9..0]  */
        unsigned int    grd2_d2               : 10  ; /* [19..10]  */
        unsigned int    grd2_d1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDD2;

/* Define the union U_SPGRDD3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd3_d3               : 10  ; /* [9..0]  */
        unsigned int    grd3_d2               : 10  ; /* [19..10]  */
        unsigned int    grd3_d1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRDD3;

/* Define the union U_SPGAINEN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    d3_enable             : 1   ; /* [0]  */
        unsigned int    d2_enable             : 1   ; /* [1]  */
        unsigned int    d1_enable             : 1   ; /* [2]  */
        unsigned int    v3_enable             : 1   ; /* [3]  */
        unsigned int    v2_enable             : 1   ; /* [4]  */
        unsigned int    v1_enable             : 1   ; /* [5]  */
        unsigned int    h4_enable             : 1   ; /* [6]  */
        unsigned int    h3_enable             : 1   ; /* [7]  */
        unsigned int    h2_enable             : 1   ; /* [8]  */
        unsigned int    h1_enable             : 1   ; /* [9]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINEN;

/* Define the union U_SPSLPH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slp2_h1               : 10  ; /* [9..0]  */
        unsigned int    slp1_h1               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPSLPH1;

/* Define the union U_SPSLPH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slp2_h2               : 10  ; /* [9..0]  */
        unsigned int    slp1_h2               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPSLPH2;

/* Define the union U_SPSLPH3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slp2_h3               : 10  ; /* [9..0]  */
        unsigned int    slp1_h3               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPSLPH3;

/* Define the union U_SPSLPH4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slp2_h4               : 10  ; /* [9..0]  */
        unsigned int    slp1_h4               : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPSLPH4;

/* Define the union U_SPSLPV1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slp1_v3               : 10  ; /* [9..0]  */
        unsigned int    slp1_v2               : 10  ; /* [19..10]  */
        unsigned int    slp1_v1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPSLPV1;

/* Define the union U_SPSLPV2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slp2_v3               : 10  ; /* [9..0]  */
        unsigned int    slp2_v2               : 10  ; /* [19..10]  */
        unsigned int    slp2_v1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPSLPV2;

/* Define the union U_SPSLPD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slp1_d3               : 10  ; /* [9..0]  */
        unsigned int    slp1_d2               : 10  ; /* [19..10]  */
        unsigned int    slp1_d1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPSLPD1;

/* Define the union U_SPSLPD2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slp2_d3               : 10  ; /* [9..0]  */
        unsigned int    slp2_d2               : 10  ; /* [19..10]  */
        unsigned int    slp2_d1               : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPSLPD2;

/* Define the union U_SPGAINMINLH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_minl_h2          : 10  ; /* [9..0]  */
        unsigned int    gain_minl_h3          : 10  ; /* [19..10]  */
        unsigned int    gain_minl_h4          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMINLH1;

/* Define the union U_SPGAINMINLH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_minl_h1          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMINLH2;

/* Define the union U_SPGAINMINLV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_minl_v1          : 10  ; /* [9..0]  */
        unsigned int    gain_minl_v2          : 10  ; /* [19..10]  */
        unsigned int    gain_minl_v3          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMINLV;

/* Define the union U_SPGAINMINLD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_minl_d1          : 10  ; /* [9..0]  */
        unsigned int    gain_minl_d2          : 10  ; /* [19..10]  */
        unsigned int    gain_minl_d3          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMINLD;

/* Define the union U_SPGAINMINHH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_minh_h2          : 10  ; /* [9..0]  */
        unsigned int    gain_minh_h3          : 10  ; /* [19..10]  */
        unsigned int    gain_minh_h4          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMINHH1;

/* Define the union U_SPGAINMINHH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_minh_h1          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMINHH2;

/* Define the union U_SPGAINMINHV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_minh_v1          : 10  ; /* [9..0]  */
        unsigned int    gain_minh_v2          : 10  ; /* [19..10]  */
        unsigned int    gain_minh_v3          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMINHV;

/* Define the union U_SPGAINMINHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_minh_d1          : 10  ; /* [9..0]  */
        unsigned int    gain_minh_d2          : 10  ; /* [19..10]  */
        unsigned int    gain_minh_d3          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMINHD;

/* Define the union U_SPGAINMAXH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_max_h2           : 10  ; /* [9..0]  */
        unsigned int    gain_max_h3           : 10  ; /* [19..10]  */
        unsigned int    gain_max_h4           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMAXH1;

/* Define the union U_SPGAINMAXH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_max_h1           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMAXH2;

/* Define the union U_SPGAINMAXV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_max_v1           : 10  ; /* [9..0]  */
        unsigned int    gain_max_v2           : 10  ; /* [19..10]  */
        unsigned int    gain_max_v3           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMAXV;

/* Define the union U_SPGAINMAXD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_max_d1           : 10  ; /* [9..0]  */
        unsigned int    gain_max_d2           : 10  ; /* [19..10]  */
        unsigned int    gain_max_d3           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINMAXD;

/* Define the union U_SPGAINPOSH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_pos_h2           : 10  ; /* [9..0]  */
        unsigned int    gain_pos_h3           : 10  ; /* [19..10]  */
        unsigned int    gain_pos_h4           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINPOSH1;

/* Define the union U_SPGAINPOSH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_pos_h1           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINPOSH2;

/* Define the union U_SPGAINPOSV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_pos_v1           : 10  ; /* [9..0]  */
        unsigned int    gain_pos_v2           : 10  ; /* [19..10]  */
        unsigned int    gain_pos_v3           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINPOSV;

/* Define the union U_SPGAINPOSD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_pos_d1           : 10  ; /* [9..0]  */
        unsigned int    gain_pos_d2           : 10  ; /* [19..10]  */
        unsigned int    gain_pos_d3           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINPOSD;

/* Define the union U_SPGAINNEGH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_neg_h2           : 10  ; /* [9..0]  */
        unsigned int    gain_neg_h3           : 10  ; /* [19..10]  */
        unsigned int    gain_neg_h4           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINNEGH1;

/* Define the union U_SPGAINNEGH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_neg_h1           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINNEGH2;

/* Define the union U_SPGAINNEGV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_neg_v1           : 10  ; /* [9..0]  */
        unsigned int    gain_neg_v2           : 10  ; /* [19..10]  */
        unsigned int    gain_neg_v3           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINNEGV;

/* Define the union U_SPGAINNEGD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_neg_d1           : 10  ; /* [9..0]  */
        unsigned int    gain_neg_d2           : 10  ; /* [19..10]  */
        unsigned int    gain_neg_d3           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINNEGD;

/* Define the union U_SPOVERTHDH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    over_thd_h1           : 8   ; /* [7..0]  */
        unsigned int    over_thd_h2           : 8   ; /* [15..8]  */
        unsigned int    over_thd_h3           : 8   ; /* [23..16]  */
        unsigned int    over_thd_h4           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPOVERTHDH;

/* Define the union U_SPOVERTHDV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    over_thd_v1           : 8   ; /* [7..0]  */
        unsigned int    over_thd_v2           : 8   ; /* [15..8]  */
        unsigned int    over_thd_v3           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPOVERTHDV;

/* Define the union U_SPOVERTHDD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    over_thd_d1           : 8   ; /* [7..0]  */
        unsigned int    over_thd_d2           : 8   ; /* [15..8]  */
        unsigned int    over_thd_d3           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPOVERTHDD;

/* Define the union U_SPUNDERTHDH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    under_thd_h1          : 8   ; /* [7..0]  */
        unsigned int    under_thd_h2          : 8   ; /* [15..8]  */
        unsigned int    under_thd_h3          : 8   ; /* [23..16]  */
        unsigned int    under_thd_h4          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPUNDERTHDH;

/* Define the union U_SPUNDERTHDV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    under_thd_v1          : 8   ; /* [7..0]  */
        unsigned int    under_thd_v2          : 8   ; /* [15..8]  */
        unsigned int    under_thd_v3          : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPUNDERTHDV;

/* Define the union U_SPUNDERTHDD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    under_thd_d1          : 8   ; /* [7..0]  */
        unsigned int    under_thd_d2          : 8   ; /* [15..8]  */
        unsigned int    under_thd_d3          : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPUNDERTHDD;

/* Define the union U_SPTMPH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmp0_h1               : 8   ; /* [7..0]  */
        unsigned int    tmp1_h1               : 8   ; /* [15..8]  */
        unsigned int    tmp2_h1               : 8   ; /* [23..16]  */
        unsigned int    tmp3_h1               : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTMPH1;

/* Define the union U_SPTMPH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmp0_h2               : 8   ; /* [7..0]  */
        unsigned int    tmp1_h2               : 8   ; /* [15..8]  */
        unsigned int    tmp2_h2               : 8   ; /* [23..16]  */
        unsigned int    tmp3_h2               : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTMPH2;

/* Define the union U_SPTMPH3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmp0_h3               : 8   ; /* [7..0]  */
        unsigned int    tmp1_h3               : 8   ; /* [15..8]  */
        unsigned int    tmp2_h3               : 8   ; /* [23..16]  */
        unsigned int    tmp3_h3               : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTMPH3;

/* Define the union U_SPTMPH4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmp0_h4               : 8   ; /* [7..0]  */
        unsigned int    tmp1_h4               : 8   ; /* [15..8]  */
        unsigned int    tmp2_h4               : 8   ; /* [23..16]  */
        unsigned int    tmp3_h4               : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTMPH4;

/* Define the union U_SPTMPV1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmp0_v1               : 8   ; /* [7..0]  */
        unsigned int    tmp1_v1               : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTMPV1;

/* Define the union U_SPTMPV2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmp0_v2               : 8   ; /* [7..0]  */
        unsigned int    tmp1_v2               : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTMPV2;

/* Define the union U_SPTMPV3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmp0_v3               : 8   ; /* [7..0]  */
        unsigned int    tmp1_v3               : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTMPV3;

/* Define the union U_SPTMPD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmp0_d1               : 8   ; /* [7..0]  */
        unsigned int    tmp1_d1               : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTMPD1;

/* Define the union U_SPTMPD2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmp0_d2               : 8   ; /* [7..0]  */
        unsigned int    tmp1_d2               : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTMPD2;

/* Define the union U_SPTMPD3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmp0_d3               : 8   ; /* [7..0]  */
        unsigned int    tmp1_d3               : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTMPD3;

/* Define the union U_SPTIGAIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_gain_h            : 8   ; /* [7..0]  */
        unsigned int    cti_gain_v            : 8   ; /* [15..8]  */
        unsigned int    lti_gain_h            : 8   ; /* [23..16]  */
        unsigned int    lti_gain_v            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPTIGAIN;

/* Define the union U_SPENABLE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_en_v              : 1   ; /* [0]  */
        unsigned int    cti_en_h              : 1   ; /* [1]  */
        unsigned int    lti_en_v              : 1   ; /* [2]  */
        unsigned int    lti_en_h              : 1   ; /* [3]  */
        unsigned int    hfreq_en_d3           : 1   ; /* [4]  */
        unsigned int    hfreq_en_d2           : 1   ; /* [5]  */
        unsigned int    hfreq_en_d1           : 1   ; /* [6]  */
        unsigned int    hfreq_en_v3           : 1   ; /* [7]  */
        unsigned int    hfreq_en_v2           : 1   ; /* [8]  */
        unsigned int    hfreq_en_v1           : 1   ; /* [9]  */
        unsigned int    hfreq_en_h4           : 1   ; /* [10]  */
        unsigned int    hfreq_en_h3           : 1   ; /* [11]  */
        unsigned int    hfreq_en_h2           : 1   ; /* [12]  */
        unsigned int    hfreq_en_h1           : 1   ; /* [13]  */
        unsigned int    yvalue_en             : 1   ; /* [14]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPENABLE;

/* Define the union U_SPSHOOTEN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    shoot_en_d3           : 1   ; /* [0]  */
        unsigned int    shoot_en_d2           : 1   ; /* [1]  */
        unsigned int    shoot_en_d1           : 1   ; /* [2]  */
        unsigned int    shoot_en_v3           : 1   ; /* [3]  */
        unsigned int    shoot_en_v2           : 1   ; /* [4]  */
        unsigned int    shoot_en_v1           : 1   ; /* [5]  */
        unsigned int    shoot_en_h4           : 1   ; /* [6]  */
        unsigned int    shoot_en_h3           : 1   ; /* [7]  */
        unsigned int    shoot_en_h2           : 1   ; /* [8]  */
        unsigned int    shoot_en_h1           : 1   ; /* [9]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPSHOOTEN;

/* Define the union U_SPLTICOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lti_cor               : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPLTICOR;

/* Define the union U_SPYVALUETH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yvalue_th0            : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    yvalue_th1            : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPYVALUETH1;

/* Define the union U_SPYVALUESLP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yvalue_slp1           : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPYVALUESLP1;

/* Define the union U_SPYVALUETH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yvalue_th2            : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    yvalue_th3            : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPYVALUETH2;

/* Define the union U_SPYVALUESLP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yvalue_slp2           : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPYVALUESLP2;

/* Define the union U_SPCTIA1TH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_a1_th0            : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    cti_a1_th1            : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTIA1TH;

/* Define the union U_SPCTIA2TH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_a2_th0            : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    cti_a2_th1            : 10  ; /* [25..16]  */
        unsigned int    cti_a2_win            : 4   ; /* [29..26]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTIA2TH;

/* Define the union U_SPCTIA3TH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_a3_th0            : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    cti_a3_th1            : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTIA3TH;

/* Define the union U_SPCTIA4GAIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_a4_cor            : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    cti_a4_gain           : 6   ; /* [21..16]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTIA4GAIN;

/* Define the union U_SPCTIA1SLP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_a1_slp            : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTIA1SLP;

/* Define the union U_SPCTIA2SLP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_a2_slp            : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTIA2SLP;

/* Define the union U_SPCTIA3SLP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_a3_slp            : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTIA3SLP;

/* Define the union U_SPCTIA4TH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_a4_th0            : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    cti_a4_th1            : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTIA4TH;

/* Define the union U_SPCTIA4SLP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cti_a4_slp            : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTIA4SLP;

/* Define the union U_SPFLATSATUR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    saturation            : 8   ; /* [7..0]  */
        unsigned int    yflat_num             : 5   ; /* [12..8]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPFLATSATUR;

/* Define the union U_SPGRADSUMTH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cgrad_sum_low         : 10  ; /* [9..0]  */
        unsigned int    cgrad_sum_high        : 10  ; /* [19..10]  */
        unsigned int    ygrad_sum_thr         : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRADSUMTH;

/* Define the union U_SPCGRADTHR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cgrad_thr0            : 10  ; /* [9..0]  */
        unsigned int    cgrad_thr1            : 10  ; /* [19..10]  */
        unsigned int    cgrad_dec_thr0        : 5   ; /* [24..20]  */
        unsigned int    cgrad_dec_thr1        : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCGRADTHR;

/* Define the union U_SPCGRADDIFFTHR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cgrad_diff_thr0       : 10  ; /* [9..0]  */
        unsigned int    cgrad_diff_thr1       : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCGRADDIFFTHR;

/* Define the union U_SP_PARARD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sharplut_rd           : 1   ; /* [0]  */
        unsigned int    sharplut_rd_id        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SP_PARARD;

/* Define the union U_SP_PARA_DATA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int sharp_para_data        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SP_PARA_DATA;
/* Define the union U_DHD0_BSCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 31  ; /* [30..0]  */
        unsigned int    bs_en                 : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_BSCTRL;

/* Define the union U_DHD0_BSRDELTA0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g0_r_be               : 8   ; /* [7..0]  */
        unsigned int    k0_r_be               : 8   ; /* [15..8]  */
        unsigned int    x0_r_be               : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_BSRDELTA0;

/* Define the union U_DHD0_BSRDELTA1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g1_r_be               : 8   ; /* [7..0]  */
        unsigned int    k1_r_be               : 8   ; /* [15..8]  */
        unsigned int    x1_r_be               : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_BSRDELTA1;

/* Define the union U_DHD0_BSGDELTA0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g0_g_be               : 8   ; /* [7..0]  */
        unsigned int    k0_g_be               : 8   ; /* [15..8]  */
        unsigned int    x0_g_be               : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_BSGDELTA0;

/* Define the union U_DHD0_BSGDELTA1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g1_g_be               : 8   ; /* [7..0]  */
        unsigned int    k1_g_be               : 8   ; /* [15..8]  */
        unsigned int    x1_g_be               : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_BSGDELTA1;

/* Define the union U_G0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ifmt                  : 8   ; /* [7..0]  */
        unsigned int    bitext                : 2   ; /* [9..8]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    odd_data_mute         : 1   ; /* [12]  */
        unsigned int    even_data_mute        : 1   ; /* [13]  */
        unsigned int    req_ctrl              : 2   ; /* [15..14]  */
        unsigned int    reserved_1            : 8   ; /* [23..16]  */
        unsigned int    flip_en               : 1   ; /* [24]  */
        unsigned int    dcmp_en               : 1   ; /* [25]  */
        unsigned int    read_mode             : 1   ; /* [26]  */
        unsigned int    upd_mode              : 1   ; /* [27]  */
        unsigned int    mute_en               : 1   ; /* [28]  */
        unsigned int    ofl_master            : 1   ; /* [29]  */
        unsigned int    nosec_flag            : 1   ; /* [30]  */
        unsigned int    surface_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CTRL;

/* Define the union U_G0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_UPD;

/* Define the union U_G0_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G0_ADDR;
/* Define the union U_G0_NADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G0_NADDR;
/* Define the union U_G0_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_STRIDE;

/* Define the union U_G0_IRESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    iw                    : 12  ; /* [11..0]  */
        unsigned int    ih                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_IRESO;

/* Define the union U_G0_SFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_xfpos             : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_SFPOS;

/* Define the union U_G0_CBMPARA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    galpha                : 8   ; /* [7..0]  */
        unsigned int    palpha_range          : 1   ; /* [8]  */
        unsigned int    reserved_0            : 1   ; /* [9]  */
        unsigned int    vedge_p               : 1   ; /* [10]  */
        unsigned int    hedge_p               : 1   ; /* [11]  */
        unsigned int    palpha_en             : 1   ; /* [12]  */
        unsigned int    premult_en            : 1   ; /* [13]  */
        unsigned int    key_en                : 1   ; /* [14]  */
        unsigned int    key_mode              : 1   ; /* [15]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CBMPARA;

/* Define the union U_G0_CKEYMAX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    keyb_max              : 8   ; /* [7..0]  */
        unsigned int    keyg_max              : 8   ; /* [15..8]  */
        unsigned int    keyr_max              : 8   ; /* [23..16]  */
        unsigned int    va0                   : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CKEYMAX;

/* Define the union U_G0_CKEYMIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    keyb_min              : 8   ; /* [7..0]  */
        unsigned int    keyg_min              : 8   ; /* [15..8]  */
        unsigned int    keyr_min              : 8   ; /* [23..16]  */
        unsigned int    va1                   : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CKEYMIN;

/* Define the union U_G0_CMASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    kmsk_b                : 8   ; /* [7..0]  */
        unsigned int    kmsk_g                : 8   ; /* [15..8]  */
        unsigned int    kmsk_r                : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CMASK;

/* Define the union U_G0_PARAADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G0_PARAADDR;
/* Define the union U_G0_PARAUP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gdc_paraup            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_PARAUP;

/* Define the union U_G0_DCMP_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G0_DCMP_ADDR;
/* Define the union U_G0_DCMP_NADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int surface_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G0_DCMP_NADDR;
/* Define the union U_G0_DCMP_OFFSET */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int offset                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G0_DCMP_OFFSET;
/* Define the union U_G0_DFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xfpos            : 12  ; /* [11..0]  */
        unsigned int    disp_yfpos            : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DFPOS;

/* Define the union U_G0_DLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xlpos            : 12  ; /* [11..0]  */
        unsigned int    disp_ylpos            : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DLPOS;

/* Define the union U_G0_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_VFPOS;

/* Define the union U_G0_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_VLPOS;

/* Define the union U_G0_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_cr                : 10  ; /* [9..0]  */
        unsigned int    vbk_cb                : 10  ; /* [19..10]  */
        unsigned int    vbk_y                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_BK;

/* Define the union U_G0_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_alpha             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_ALPHA;

/* Define the union U_G0_DOF_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 31  ; /* [30..0]  */
        unsigned int    dof_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DOF_CTRL;

/* Define the union U_G0_DOF_STEP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    left_step             : 8   ; /* [7..0]  */
        unsigned int    right_step            : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DOF_STEP;

/* Define the union U_G0_DOF_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dof_bk_cr             : 10  ; /* [9..0]  */
        unsigned int    dof_bk_cb             : 10  ; /* [19..10]  */
        unsigned int    dof_bk_y              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DOF_BKG;

/* Define the union U_G0_DOF_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dof_bk_alpha          : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DOF_ALPHA;

/* Define the union U_G0_CSC_IDC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc0               : 11  ; /* [10..0]  */
        unsigned int    cscidc1               : 11  ; /* [21..11]  */
        unsigned int    csc_en                : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CSC_IDC;

/* Define the union U_G0_CSC_ODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscodc0               : 11  ; /* [10..0]  */
        unsigned int    cscodc1               : 11  ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CSC_ODC;

/* Define the union U_G0_CSC_IODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc2               : 11  ; /* [10..0]  */
        unsigned int    cscodc2               : 11  ; /* [21..11]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CSC_IODC;

/* Define the union U_G0_CSC_P0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp00                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp01                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CSC_P0;

/* Define the union U_G0_CSC_P1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp02                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp10                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CSC_P1;

/* Define the union U_G0_CSC_P2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp11                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp12                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CSC_P2;

/* Define the union U_G0_CSC_P3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp20                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp21                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CSC_P3;

/* Define the union U_G0_CSC_P4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp22                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CSC_P4;

/* Define the union U_GP0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mux1_sel              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    mux2_sel              : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    aout_sel              : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 2   ; /* [11..10]  */
        unsigned int    bout_sel              : 2   ; /* [13..12]  */
        unsigned int    reserved_3            : 12  ; /* [25..14]  */
        unsigned int    ffc_sel               : 1   ; /* [26]  */
        unsigned int    reserved_4            : 3   ; /* [29..27]  */
        unsigned int    mute_en               : 1   ; /* [30]  */
        unsigned int    read_mode             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_CTRL;

/* Define the union U_GP0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_UPD;

/* Define the union U_GP0_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 12  ; /* [11..0]  */
        unsigned int    oh                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ORESO;

/* Define the union U_GP0_IRESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    iw                    : 12  ; /* [11..0]  */
        unsigned int    ih                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_IRESO;

/* Define the union U_GP0_HCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GP0_HCOEFAD;
/* Define the union U_GP0_VCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GP0_VCOEFAD;
/* Define the union U_GP0_PARAUP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gp0_hcoef_upd         : 1   ; /* [0]  */
        unsigned int    gp0_vcoef_upd         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_PARAUP;

/* Define the union U_GP0_GALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    galpha                : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_GALPHA;

/* Define the union U_GP0_DFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xfpos            : 12  ; /* [11..0]  */
        unsigned int    disp_yfpos            : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_DFPOS;

/* Define the union U_GP0_DLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xlpos            : 12  ; /* [11..0]  */
        unsigned int    disp_ylpos            : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_DLPOS;

/* Define the union U_GP0_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_VFPOS;

/* Define the union U_GP0_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_VLPOS;

/* Define the union U_GP0_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_cr                : 10  ; /* [9..0]  */
        unsigned int    vbk_cb                : 10  ; /* [19..10]  */
        unsigned int    vbk_y                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_BK;

/* Define the union U_GP0_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_alpha             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ALPHA;

/* Define the union U_GP0_CSC_IDC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc0               : 11  ; /* [10..0]  */
        unsigned int    cscidc1               : 11  ; /* [21..11]  */
        unsigned int    csc_en                : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_CSC_IDC;

/* Define the union U_GP0_CSC_ODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscodc0               : 11  ; /* [10..0]  */
        unsigned int    cscodc1               : 11  ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_CSC_ODC;

/* Define the union U_GP0_CSC_IODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc2               : 11  ; /* [10..0]  */
        unsigned int    cscodc2               : 11  ; /* [21..11]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_CSC_IODC;

/* Define the union U_GP0_CSC_P0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp00                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp01                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_CSC_P0;

/* Define the union U_GP0_CSC_P1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp02                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp10                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_CSC_P1;

/* Define the union U_GP0_CSC_P2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp11                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp12                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_CSC_P2;

/* Define the union U_GP0_CSC_P3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp20                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp21                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_CSC_P3;

/* Define the union U_GP0_CSC_P4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp22                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_CSC_P4;

/* Define the union U_GP0_ZME_HSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hratio                : 24  ; /* [23..0]  */
        unsigned int    hfir_order            : 1   ; /* [24]  */
        unsigned int    hafir_en              : 1   ; /* [25]  */
        unsigned int    hfir_en               : 1   ; /* [26]  */
        unsigned int    reserved_0            : 1   ; /* [27]  */
        unsigned int    hchmid_en             : 1   ; /* [28]  */
        unsigned int    hlmid_en              : 1   ; /* [29]  */
        unsigned int    hamid_en              : 1   ; /* [30]  */
        unsigned int    hsc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_HSP;

/* Define the union U_GP0_ZME_HLOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_loffset           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_HLOFFSET;

/* Define the union U_GP0_ZME_HCOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_coffset           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_HCOFFSET;

/* Define the union U_GP0_ZME_VSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 23  ; /* [22..0]  */
        unsigned int    vafir_en              : 1   ; /* [23]  */
        unsigned int    vfir_en               : 1   ; /* [24]  */
        unsigned int    vfir_1tap_en          : 1   ; /* [25]  */
        unsigned int    vfir_2tap_en          : 1   ; /* [26]  */
        unsigned int    reserved_1            : 1   ; /* [27]  */
        unsigned int    vchmid_en             : 1   ; /* [28]  */
        unsigned int    vlmid_en              : 1   ; /* [29]  */
        unsigned int    vamid_en              : 1   ; /* [30]  */
        unsigned int    vsc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_VSP;

/* Define the union U_GP0_ZME_VSR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vratio                : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_VSR;

/* Define the union U_GP0_ZME_VOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbtm_offset           : 16  ; /* [15..0]  */
        unsigned int    vtp_offset            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_VOFFSET;

/* Define the union U_GP0_ZME_LTICTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lhpass_coef4          : 8   ; /* [7..0]  */
        unsigned int    lmixing_ratio         : 8   ; /* [15..8]  */
        unsigned int    lgain_ratio           : 12  ; /* [27..16]  */
        unsigned int    reserved_0            : 3   ; /* [30..28]  */
        unsigned int    lti_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_LTICTRL;

/* Define the union U_GP0_ZME_LHPASSCOEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lhpass_coef0          : 8   ; /* [7..0]  */
        unsigned int    lhpass_coef1          : 8   ; /* [15..8]  */
        unsigned int    lhpass_coef2          : 8   ; /* [23..16]  */
        unsigned int    lhpass_coef3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_LHPASSCOEF;

/* Define the union U_GP0_ZME_LTITHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lover_swing           : 10  ; /* [9..0]  */
        unsigned int    lunder_swing          : 10  ; /* [19..10]  */
        unsigned int    lcoring_thd           : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_LTITHD;

/* Define the union U_GP0_ZME_LHFREQTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lhfreq_thd0           : 16  ; /* [15..0]  */
        unsigned int    lhfreq_thd1           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_LHFREQTHD;

/* Define the union U_GP0_ZME_LGAINCOEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lgain_coef0           : 8   ; /* [7..0]  */
        unsigned int    lgain_coef1           : 8   ; /* [15..8]  */
        unsigned int    lgain_coef2           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_LGAINCOEF;

/* Define the union U_GP0_ZME_CTICTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    cmixing_ratio         : 8   ; /* [15..8]  */
        unsigned int    cgain_ratio           : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 3   ; /* [30..28]  */
        unsigned int    cti_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_CTICTRL;

/* Define the union U_GP0_ZME_CHPASSCOEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    chpass_coef0          : 8   ; /* [7..0]  */
        unsigned int    chpass_coef1          : 8   ; /* [15..8]  */
        unsigned int    chpass_coef2          : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_CHPASSCOEF;

/* Define the union U_GP0_ZME_CTITHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cover_swing           : 10  ; /* [9..0]  */
        unsigned int    cunder_swing          : 10  ; /* [19..10]  */
        unsigned int    ccoring_thd           : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_CTITHD;

/* Define the union U_GP0_ZMECOEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_g0_lcti_vc_ren    : 1   ; /* [0]  */
        unsigned int    apb_g0_lcti_vl_ren    : 1   ; /* [1]  */
        unsigned int    apb_g0_lcti_hc_ren    : 1   ; /* [2]  */
        unsigned int    apb_g0_lcti_hl_ren    : 1   ; /* [3]  */
        unsigned int    apb_g0_vf_ren         : 1   ; /* [4]  */
        unsigned int    apb_g0_hf_ren_b       : 1   ; /* [5]  */
        unsigned int    apb_g0_hf_ren_a       : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZMECOEF;

/* Define the union U_GP0_ZMECOEFAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_g0_coef_raddr     : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZMECOEFAD;

/* Define the union U_GP0_WCG_NON2LCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    gma_lin_thre_0        : 8   ; /* [9..2]  */
        unsigned int    gma_lin_thre_1        : 10  ; /* [19..10]  */
        unsigned int    gma_lin_thre_2        : 10  ; /* [29..20]  */
        unsigned int    gma_lin_init_slp      : 1   ; /* [30]  */
        unsigned int    gma_lin_neg_scl       : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_NON2LCTRL;

/* Define the union U_GP0_WCG_NON2LCOEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gma_lin_coef_a_0      : 10  ; /* [9..0]  */
        unsigned int    gma_lin_coef_b_0      : 12  ; /* [21..10]  */
        unsigned int    gma_lin_coef_c_0      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_NON2LCOEF0;

/* Define the union U_GP0_WCG_NON2LCOEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gma_lin_coef_a_1      : 10  ; /* [9..0]  */
        unsigned int    gma_lin_coef_b_1      : 12  ; /* [21..10]  */
        unsigned int    gma_lin_coef_c_1      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_NON2LCOEF1;

/* Define the union U_GP0_WCG_NON2LCOEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gma_lin_coef_a_2      : 10  ; /* [9..0]  */
        unsigned int    gma_lin_coef_b_2      : 12  ; /* [21..10]  */
        unsigned int    gma_lin_coef_c_2      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_NON2LCOEF2;

/* Define the union U_GP0_WCG_CSC2CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_r_r_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_r_g_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 5   ; /* [28..24]  */
        unsigned int    csc2_scale_sel        : 2   ; /* [30..29]  */
        unsigned int    csc2_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_CSC2CTRL;

/* Define the union U_GP0_WCG_CSC2COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_r_b_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_g_r_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_CSC2COEF0;

/* Define the union U_GP0_WCG_CSC2COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_g_g_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_g_b_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_CSC2COEF1;

/* Define the union U_GP0_WCG_CSC2COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_b_r_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_b_g_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_CSC2COEF2;

/* Define the union U_GP0_WCG_CSC2COEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_b_b_coef         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_CSC2COEF3;

/* Define the union U_GP0_WCG_L2NONTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_thre_0        : 8   ; /* [7..0]  */
        unsigned int    lin_gma_thre_1        : 11  ; /* [18..8]  */
        unsigned int    lin_gma_thre_2        : 11  ; /* [29..19]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_L2NONTHD;

/* Define the union U_GP0_WCG_L2NONCOEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_coef_a_0      : 11  ; /* [10..0]  */
        unsigned int    lin_gma_coef_b_0      : 10  ; /* [20..11]  */
        unsigned int    lin_gma_coef_c_0      : 9   ; /* [29..21]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_L2NONCOEF0;

/* Define the union U_GP0_WCG_L2NONCOEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_coef_a_1      : 11  ; /* [10..0]  */
        unsigned int    lin_gma_coef_b_1      : 10  ; /* [20..11]  */
        unsigned int    lin_gma_coef_c_1      : 9   ; /* [29..21]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_L2NONCOEF1;

/* Define the union U_GP0_WCG_L2NONCOEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_coef_a_2      : 11  ; /* [10..0]  */
        unsigned int    lin_gma_coef_b_2      : 10  ; /* [20..11]  */
        unsigned int    lin_gma_coef_c_2      : 9   ; /* [29..21]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_WCG_L2NONCOEF2;

/* Define the union U_WBC_DHD0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_interval          : 10  ; /* [9..0]  */
        unsigned int    auto_stop_en          : 1   ; /* [10]  */
        unsigned int    histogam_en           : 1   ; /* [11]  */
        unsigned int    wbc_vtthd_mode        : 1   ; /* [12]  */
        unsigned int    reserved_0            : 5   ; /* [17..13]  */
        unsigned int    three_d_mode          : 2   ; /* [19..18]  */
        unsigned int    ofl_master            : 1   ; /* [20]  */
        unsigned int    data_width            : 1   ; /* [21]  */
        unsigned int    uv_order              : 1   ; /* [22]  */
        unsigned int    flip_en               : 1   ; /* [23]  */
        unsigned int    format_out            : 4   ; /* [27..24]  */
        unsigned int    mode_out              : 2   ; /* [29..28]  */
        unsigned int    reserved_1            : 1   ; /* [30]  */
        unsigned int    wbc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CTRL;

/* Define the union U_WBC_DHD0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_UPD;

/* Define the union U_WBC_DHD0_YADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbcaddr                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_YADDR;
/* Define the union U_WBC_DHD0_CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbccaddr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_CADDR;
/* Define the union U_WBC_DHD0_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbclstride            : 16  ; /* [15..0]  */
        unsigned int    wbccstride            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_STRIDE;

/* Define the union U_WBC_DHD0_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 12  ; /* [11..0]  */
        unsigned int    oh                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ORESO;

/* Define the union U_WBC_DHD0_FCROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wfcrop                : 12  ; /* [11..0]  */
        unsigned int    hfcrop                : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_FCROP;

/* Define the union U_WBC_DHD0_LCROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wlcrop                : 12  ; /* [11..0]  */
        unsigned int    hlcrop                : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_LCROP;

/* Define the union U_WBC_DHD0_LOWDLYCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wb_per_line_num       : 12  ; /* [11..0]  */
        unsigned int    partfns_line_num      : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 6   ; /* [29..24]  */
        unsigned int    lowdly_test           : 1   ; /* [30]  */
        unsigned int    lowdly_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_LOWDLYCTRL;

/* Define the union U_WBC_DHD0_TUNLADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tunl_cell_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_TUNLADDR;
/* Define the union U_WBC_DHD0_LOWDLYSTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 31  ; /* [30..0]  */
        unsigned int    part_finish           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_LOWDLYSTA;

/* Define the union U_WBC_DHD0_PARAUP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_hlcoef_upd        : 1   ; /* [0]  */
        unsigned int    wbc_hccoef_upd        : 1   ; /* [1]  */
        unsigned int    wbc_vlcoef_upd        : 1   ; /* [2]  */
        unsigned int    wbc_vccoef_upd        : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_PARAUP;

/* Define the union U_WBC_DHD0_HLCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_HLCOEFAD;
/* Define the union U_WBC_DHD0_HCCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_HCCOEFAD;
/* Define the union U_WBC_DHD0_VLCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_VLCOEFAD;
/* Define the union U_WBC_DHD0_VCCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_VCCOEFAD;
/* Define the union U_WBC_DHD0_HISTOGRAM0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt0            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM0;

/* Define the union U_WBC_DHD0_HISTOGRAM1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt1            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM1;

/* Define the union U_WBC_DHD0_HISTOGRAM2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt2            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM2;

/* Define the union U_WBC_DHD0_HISTOGRAM3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt3            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM3;

/* Define the union U_WBC_DHD0_HISTOGRAM4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt4            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM4;

/* Define the union U_WBC_DHD0_HISTOGRAM5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt5            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM5;

/* Define the union U_WBC_DHD0_HISTOGRAM6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt6            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM6;

/* Define the union U_WBC_DHD0_HISTOGRAM7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt7            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM7;

/* Define the union U_WBC_DHD0_HISTOGRAM8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt8            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM8;

/* Define the union U_WBC_DHD0_HISTOGRAM9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt9            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM9;

/* Define the union U_WBC_DHD0_HISTOGRAM10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt10           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM10;

/* Define the union U_WBC_DHD0_HISTOGRAM11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt11           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM11;

/* Define the union U_WBC_DHD0_HISTOGRAM12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt12           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM12;

/* Define the union U_WBC_DHD0_HISTOGRAM13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt13           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM13;

/* Define the union U_WBC_DHD0_HISTOGRAM14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt14           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM14;

/* Define the union U_WBC_DHD0_HISTOGRAM15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hgram_cnt15           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HISTOGRAM15;

/* Define the union U_WBC_DHD0_DBG_WBC_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_sta_l             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 15  ; /* [15..1]  */
        unsigned int    wbc_sta_c             : 1   ; /* [16]  */
        unsigned int    reserved_1            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_DBG_WBC_STA;

/* Define the union U_WBC_DHD0_DBG_WBC_LINE_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    line_num_l            : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    line_num_c            : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_DBG_WBC_LINE_CNT;

/* Define the union U_WBC_DHD0_CHECKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_CHECKSUM_Y;
/* Define the union U_WBC_DHD0_CHECKSUM_C */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_CHECKSUM_C;
/* Define the union U_WBC_DHD0_DITHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    dither_round          : 1   ; /* [29]  */
        unsigned int    dither_mode           : 1   ; /* [30]  */
        unsigned int    dither_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_DITHER_CTRL;

/* Define the union U_WBC_DHD0_DITHER_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef0          : 8   ; /* [7..0]  */
        unsigned int    dither_coef1          : 8   ; /* [15..8]  */
        unsigned int    dither_coef2          : 8   ; /* [23..16]  */
        unsigned int    dither_coef3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_DITHER_COEF0;

/* Define the union U_WBC_DHD0_DITHER_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef4          : 8   ; /* [7..0]  */
        unsigned int    dither_coef5          : 8   ; /* [15..8]  */
        unsigned int    dither_coef6          : 8   ; /* [23..16]  */
        unsigned int    dither_coef7          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_DITHER_COEF1;

/* Define the union U_WBC_DHD0_HCDS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    hchfir_en             : 1   ; /* [29]  */
        unsigned int    hchmid_en             : 1   ; /* [30]  */
        unsigned int    hcds_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HCDS;

/* Define the union U_WBC_DHD0_HCDS_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef0                 : 10  ; /* [9..0]  */
        unsigned int    coef1                 : 10  ; /* [19..10]  */
        unsigned int    coef2                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HCDS_COEF0;

/* Define the union U_WBC_DHD0_HCDS_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef3                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HCDS_COEF1;

/* Define the union U_WBC_DHD0_HPZME */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    hpzme_mode            : 1   ; /* [29]  */
        unsigned int    hpzme_mid_en          : 1   ; /* [30]  */
        unsigned int    hpzme_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HPZME;

/* Define the union U_WBC_DHD0_ZME_HSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hratio                : 24  ; /* [23..0]  */
        unsigned int    hfir_order            : 1   ; /* [24]  */
        unsigned int    hchfir_en             : 1   ; /* [25]  */
        unsigned int    hlfir_en              : 1   ; /* [26]  */
        unsigned int    reserved_0            : 1   ; /* [27]  */
        unsigned int    hchmid_en             : 1   ; /* [28]  */
        unsigned int    hlmid_en              : 1   ; /* [29]  */
        unsigned int    hchmsc_en             : 1   ; /* [30]  */
        unsigned int    hlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_HSP;

/* Define the union U_WBC_DHD0_ZME_HLOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_loffset           : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_HLOFFSET;

/* Define the union U_WBC_DHD0_ZME_HCOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_coffset           : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_HCOFFSET;

/* Define the union U_WBC_DHD0_ZME_VSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    zme_in_fmt            : 2   ; /* [20..19]  */
        unsigned int    zme_out_fmt           : 2   ; /* [22..21]  */
        unsigned int    vchfir_en             : 1   ; /* [23]  */
        unsigned int    vlfir_en              : 1   ; /* [24]  */
        unsigned int    reserved_1            : 3   ; /* [27..25]  */
        unsigned int    vchmid_en             : 1   ; /* [28]  */
        unsigned int    vlmid_en              : 1   ; /* [29]  */
        unsigned int    vchmsc_en             : 1   ; /* [30]  */
        unsigned int    vlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_VSP;

/* Define the union U_WBC_DHD0_ZME_VSR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vratio                : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_VSR;

/* Define the union U_WBC_DHD0_ZME_VOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vchroma_offset        : 16  ; /* [15..0]  */
        unsigned int    vluma_offset          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_VOFFSET;

/* Define the union U_WBC_DHD0_ZME_VBOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbchroma_offset       : 16  ; /* [15..0]  */
        unsigned int    vbluma_offset         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_VBOFFSET;

/* Define the union U_WBC_DHD0_CSCIDC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc0               : 9   ; /* [8..0]  */
        unsigned int    cscidc1               : 9   ; /* [17..9]  */
        unsigned int    cscidc2               : 9   ; /* [26..18]  */
        unsigned int    csc_en                : 1   ; /* [27]  */
        unsigned int    csc_mode              : 3   ; /* [30..28]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCIDC;

/* Define the union U_WBC_DHD0_CSCODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscodc0               : 9   ; /* [8..0]  */
        unsigned int    cscodc1               : 9   ; /* [17..9]  */
        unsigned int    cscodc2               : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCODC;

/* Define the union U_WBC_DHD0_CSCP0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp00                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp01                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCP0;

/* Define the union U_WBC_DHD0_CSCP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp02                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp10                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCP1;

/* Define the union U_WBC_DHD0_CSCP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp11                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp12                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCP2;

/* Define the union U_WBC_DHD0_CSCP3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp20                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp21                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCP3;

/* Define the union U_WBC_DHD0_CSCP4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp22                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCP4;

/* Define the union U_WBC_GP0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_interval          : 10  ; /* [9..0]  */
        unsigned int    auto_stop_en          : 1   ; /* [10]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    wbc_vtthd_mode        : 1   ; /* [12]  */
        unsigned int    reserved_1            : 5   ; /* [17..13]  */
        unsigned int    three_d_mode          : 2   ; /* [19..18]  */
        unsigned int    reserved_2            : 3   ; /* [22..20]  */
        unsigned int    flip_en               : 1   ; /* [23]  */
        unsigned int    format_out            : 4   ; /* [27..24]  */
        unsigned int    mode_out              : 2   ; /* [29..28]  */
        unsigned int    reserved_3            : 1   ; /* [30]  */
        unsigned int    wbc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_GP0_CTRL;

/* Define the union U_WBC_GP0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_GP0_UPD;

/* Define the union U_WBC_GP0_YADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbcaddr                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_GP0_YADDR;
/* Define the union U_WBC_GP0_CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbccaddr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_GP0_CADDR;
/* Define the union U_WBC_GP0_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbclstride            : 16  ; /* [15..0]  */
        unsigned int    wbccstride            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_GP0_STRIDE;

/* Define the union U_WBC_GP0_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 12  ; /* [11..0]  */
        unsigned int    oh                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_GP0_ORESO;

/* Define the union U_WBC_GP0_FCROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wfcrop                : 12  ; /* [11..0]  */
        unsigned int    hfcrop                : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_GP0_FCROP;

/* Define the union U_WBC_GP0_LCROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wlcrop                : 12  ; /* [11..0]  */
        unsigned int    hlcrop                : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_GP0_LCROP;

/* Define the union U_WBC_GP0_DITHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    dither_round          : 1   ; /* [29]  */
        unsigned int    dither_mode           : 1   ; /* [30]  */
        unsigned int    dither_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_GP0_DITHER_CTRL;

/* Define the union U_WBC_GP0_DITHER_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef0          : 8   ; /* [7..0]  */
        unsigned int    dither_coef1          : 8   ; /* [15..8]  */
        unsigned int    dither_coef2          : 8   ; /* [23..16]  */
        unsigned int    dither_coef3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_GP0_DITHER_COEF0;

/* Define the union U_WBC_GP0_DITHER_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef4          : 8   ; /* [7..0]  */
        unsigned int    dither_coef5          : 8   ; /* [15..8]  */
        unsigned int    dither_coef6          : 8   ; /* [23..16]  */
        unsigned int    dither_coef7          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_GP0_DITHER_COEF1;

/* Define the union U_WBC_GP0_HPZME */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    hpzme_mode            : 1   ; /* [29]  */
        unsigned int    hpzme_mid_en          : 1   ; /* [30]  */
        unsigned int    hpzme_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_GP0_HPZME;

/* Define the union U_WBC_G0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_interval          : 10  ; /* [9..0]  */
        unsigned int    auto_stop_en          : 1   ; /* [10]  */
        unsigned int    reserved_0            : 15  ; /* [25..11]  */
        unsigned int    format_out            : 2   ; /* [27..26]  */
        unsigned int    reserved_1            : 3   ; /* [30..28]  */
        unsigned int    wbc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_G0_CTRL;

/* Define the union U_WBC_G0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_G0_UPD;

/* Define the union U_WBC_G0_CMP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cmp_lossy_en          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    cmp_drr               : 4   ; /* [7..4]  */
        unsigned int    reserved_1            : 23  ; /* [30..8]  */
        unsigned int    cmp_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_G0_CMP;

/* Define the union U_WBC_G0_AR_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbcaddr                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_G0_AR_ADDR;
/* Define the union U_WBC_G0_GB_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbccaddr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_G0_GB_ADDR;
/* Define the union U_WBC_G0_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbcstride             : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_G0_STRIDE;

/* Define the union U_WBC_G0_OFFSET */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbcoffset              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_G0_OFFSET;
/* Define the union U_WBC_G0_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 12  ; /* [11..0]  */
        unsigned int    oh                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_G0_ORESO;

/* Define the union U_WBC_G0_FCROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wfcrop                : 12  ; /* [11..0]  */
        unsigned int    hfcrop                : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_G0_FCROP;

/* Define the union U_WBC_G0_LCROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wlcrop                : 12  ; /* [11..0]  */
        unsigned int    hlcrop                : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_G0_LCROP;

/* Define the union U_WBC_ME_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_interval          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 10  ; /* [19..10]  */
        unsigned int    ofl_master            : 1   ; /* [20]  */
        unsigned int    reserved_1            : 3   ; /* [23..21]  */
        unsigned int    format_out            : 4   ; /* [27..24]  */
        unsigned int    reserved_2            : 3   ; /* [30..28]  */
        unsigned int    wbc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_CTRL;

/* Define the union U_WBC_ME_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_UPD;

/* Define the union U_WBC_ME_YADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbcaddr                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_ME_YADDR;
/* Define the union U_WBC_ME_CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbccaddr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_ME_CADDR;
/* Define the union U_WBC_ME_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbclstride            : 16  ; /* [15..0]  */
        unsigned int    wbccstride            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_STRIDE;

/* Define the union U_WBC_ME_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 12  ; /* [11..0]  */
        unsigned int    oh                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_ORESO;

/* Define the union U_WBC_ME_PARAUP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_hlcoef_upd        : 1   ; /* [0]  */
        unsigned int    wbc_hccoef_upd        : 1   ; /* [1]  */
        unsigned int    wbc_vlcoef_upd        : 1   ; /* [2]  */
        unsigned int    wbc_vccoef_upd        : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_PARAUP;

/* Define the union U_WBC_ME_HLCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_ME_HLCOEFAD;
/* Define the union U_WBC_ME_HCCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_ME_HCCOEFAD;
/* Define the union U_WBC_ME_VLCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_ME_VLCOEFAD;
/* Define the union U_WBC_ME_VCCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_ME_VCCOEFAD;
/* Define the union U_WBC_ME_CHECKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_ME_CHECKSUM_Y;
/* Define the union U_WBC_ME_CHECKSUM_C */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_ME_CHECKSUM_C;
/* Define the union U_WBC_ME_DITHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    dither_round          : 1   ; /* [29]  */
        unsigned int    dither_mode           : 1   ; /* [30]  */
        unsigned int    dither_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_DITHER_CTRL;

/* Define the union U_WBC_ME_DITHER_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef0          : 8   ; /* [7..0]  */
        unsigned int    dither_coef1          : 8   ; /* [15..8]  */
        unsigned int    dither_coef2          : 8   ; /* [23..16]  */
        unsigned int    dither_coef3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_DITHER_COEF0;

/* Define the union U_WBC_ME_DITHER_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef4          : 8   ; /* [7..0]  */
        unsigned int    dither_coef5          : 8   ; /* [15..8]  */
        unsigned int    dither_coef6          : 8   ; /* [23..16]  */
        unsigned int    dither_coef7          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_DITHER_COEF1;

/* Define the union U_WBC_ME_ZME_HSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hratio                : 24  ; /* [23..0]  */
        unsigned int    hfir_order            : 1   ; /* [24]  */
        unsigned int    hchfir_en             : 1   ; /* [25]  */
        unsigned int    hlfir_en              : 1   ; /* [26]  */
        unsigned int    reserved_0            : 1   ; /* [27]  */
        unsigned int    hchmid_en             : 1   ; /* [28]  */
        unsigned int    hlmid_en              : 1   ; /* [29]  */
        unsigned int    hchmsc_en             : 1   ; /* [30]  */
        unsigned int    hlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_ZME_HSP;

/* Define the union U_WBC_ME_ZME_HLOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_loffset           : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_ZME_HLOFFSET;

/* Define the union U_WBC_ME_ZME_HCOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_coffset           : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_ZME_HCOFFSET;

/* Define the union U_WBC_ME_ZME_VSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    zme_in_fmt            : 2   ; /* [20..19]  */
        unsigned int    zme_out_fmt           : 2   ; /* [22..21]  */
        unsigned int    vchfir_en             : 1   ; /* [23]  */
        unsigned int    vlfir_en              : 1   ; /* [24]  */
        unsigned int    reserved_1            : 3   ; /* [27..25]  */
        unsigned int    vchmid_en             : 1   ; /* [28]  */
        unsigned int    vlmid_en              : 1   ; /* [29]  */
        unsigned int    vchmsc_en             : 1   ; /* [30]  */
        unsigned int    vlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_ZME_VSP;

/* Define the union U_WBC_ME_ZME_VSR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vratio                : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_ZME_VSR;

/* Define the union U_WBC_ME_ZME_VOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vchroma_offset        : 16  ; /* [15..0]  */
        unsigned int    vluma_offset          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_ZME_VOFFSET;

/* Define the union U_WBC_ME_ZME_VBOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbchroma_offset       : 16  ; /* [15..0]  */
        unsigned int    vbluma_offset         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_ME_ZME_VBOFFSET;

/* Define the union U_WBC_FI_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_interval          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 10  ; /* [19..10]  */
        unsigned int    ofl_master            : 1   ; /* [20]  */
        unsigned int    data_width            : 1   ; /* [21]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    format_out            : 4   ; /* [27..24]  */
        unsigned int    reserved_2            : 2   ; /* [29..28]  */
        unsigned int    cmp_en                : 1   ; /* [30]  */
        unsigned int    wbc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_CTRL;

/* Define the union U_WBC_FI_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_UPD;

/* Define the union U_WBC_FI_YADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbcaddr                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_FI_YADDR;
/* Define the union U_WBC_FI_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 12  ; /* [11..0]  */
        unsigned int    oh                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_ORESO;

/* Define the union U_WBC_FI_CHECKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_FI_CHECKSUM_Y;
/* Define the union U_WBC_FI_CHECKSUM_C */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_FI_CHECKSUM_C;
/* Define the union U_WBC_FI_HCDS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    hchfir_en             : 1   ; /* [29]  */
        unsigned int    hchmid_en             : 1   ; /* [30]  */
        unsigned int    hcds_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_HCDS;

/* Define the union U_WBC_FI_HCDS_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef0                 : 10  ; /* [9..0]  */
        unsigned int    coef1                 : 10  ; /* [19..10]  */
        unsigned int    coef2                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_HCDS_COEF0;

/* Define the union U_WBC_FI_HCDS_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef3                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_HCDS_COEF1;

/* Define the union U_WBC_FI_CMP_MB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mb_bits               : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_CMP_MB;

/* Define the union U_WBC_FI_CMP_MAX_MIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    min_bits_cnt          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    max_bits_cnt          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_CMP_MAX_MIN;

/* Define the union U_WBC_FI_CMP_ADJ_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    adj_sad_thr           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    adj_sad_bit_thr       : 8   ; /* [23..16]  */
        unsigned int    adj_spec_bit_thr      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_CMP_ADJ_THR;

/* Define the union U_WBC_FI_CMP_BIG_GRAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    big_grad_thr          : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    big_grad_num_thr      : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_CMP_BIG_GRAD;

/* Define the union U_WBC_FI_CMP_BLK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smth_thr              : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    blk_comp_thr          : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_CMP_BLK;

/* Define the union U_WBC_FI_CMP_GRAPHIC_JUDGE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    graphic_en            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 15  ; /* [15..1]  */
        unsigned int    video_sad_thr         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_CMP_GRAPHIC_JUDGE;

/* Define the union U_WBC_FI_CMP_RC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sadbits_ngain         : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 5   ; /* [7..3]  */
        unsigned int    rc_smth_gain          : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 5   ; /* [15..11]  */
        unsigned int    max_trow_bits         : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_CMP_RC;

/* Define the union U_WBC_FI_CMP_FRAME_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_size            : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_FI_CMP_FRAME_SIZE;

/* Define the union U_WBC_BMP_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_interval          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 10  ; /* [19..10]  */
        unsigned int    ofl_master            : 1   ; /* [20]  */
        unsigned int    data_width            : 1   ; /* [21]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    format_out            : 4   ; /* [27..24]  */
        unsigned int    reserved_2            : 3   ; /* [30..28]  */
        unsigned int    wbc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_BMP_CTRL;

/* Define the union U_WBC_BMP_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_BMP_UPD;

/* Define the union U_WBC_BMP_YADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbcaddr                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_BMP_YADDR;
/* Define the union U_WBC_BMP_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 12  ; /* [11..0]  */
        unsigned int    oh                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_BMP_ORESO;

/* Define the union U_WBC_BMP_SUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bmp_sum               : 25  ; /* [24..0]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_BMP_SUM;

/* Define the union U_WBC_BMP_CHECKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_BMP_CHECKSUM_Y;
/* Define the union U_WBC_BMP_CHECKSUM_C */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_BMP_CHECKSUM_C;
/* Define the union U_MIXV0_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_bkgcr           : 10  ; /* [9..0]  */
        unsigned int    mixer_bkgcb           : 10  ; /* [19..10]  */
        unsigned int    mixer_bkgy            : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXV0_BKG;

/* Define the union U_MIXV0_MIX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXV0_MIX;

/* Define the union U_MIXG0_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_bkgcr           : 10  ; /* [9..0]  */
        unsigned int    mixer_bkgcb           : 10  ; /* [19..10]  */
        unsigned int    mixer_bkgy            : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXG0_BKG;

/* Define the union U_MIXG0_BKALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_alpha           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXG0_BKALPHA;

/* Define the union U_MIXG0_MIX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    mixer_prio2           : 4   ; /* [11..8]  */
        unsigned int    mixer_prio3           : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXG0_MIX;

/* Define the union U_CBM_BKG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cbm_bkgcr1            : 10  ; /* [9..0]  */
        unsigned int    cbm_bkgcb1            : 10  ; /* [19..10]  */
        unsigned int    cbm_bkgy1             : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_BKG1;

/* Define the union U_CBM_MIX1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_MIX1;

/* Define the union U_WBC_BMP_THD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_bmp_thd           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_BMP_THD;

/* Define the union U_CBM_BKG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cbm_bkgcr2            : 10  ; /* [9..0]  */
        unsigned int    cbm_bkgcb2            : 10  ; /* [19..10]  */
        unsigned int    cbm_bkgy2             : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_BKG2;

/* Define the union U_CBM_MIX2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_MIX2;

/* Define the union U_HC_BMP_THD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hc_bmp_thd            : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HC_BMP_THD;

/* Define the union U_CBM_BKG3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cbm_bkgcr3            : 10  ; /* [9..0]  */
        unsigned int    cbm_bkgcb3            : 10  ; /* [19..10]  */
        unsigned int    cbm_bkgy3             : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_BKG3;

/* Define the union U_CBM_MIX3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    mixer_prio2           : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_MIX3;

/* Define the union U_SR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    sr_mode               : 2   ; /* [30..29]  */
        unsigned int    sr_en                 : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CTRL;

/* Define the union U_SR_LDIR_RATIO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd_sub_ratio         : 6   ; /* [5..0]  */
        unsigned int    grd_hv_near           : 6   ; /* [11..6]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_LDIR_RATIO;

/* Define the union U_SR_LTEX_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd_thrl              : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    grd_thrh              : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_LTEX_THR;

/* Define the union U_SR_LTEX_ADD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grd_add_ctrl          : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    grd_thrh_subl         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_LTEX_ADD;

/* Define the union U_SR_DIPL_DETAIL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disc_detail_gain      : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_DIPL_DETAIL;

/* Define the union U_SR_SHARP_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    resvered              : 31  ; /* [30..0]  */
        unsigned int    sharp_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_SHARP_EN;

/* Define the union U_SR_SHARP_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sharp_gain            : 11  ; /* [10..0]  */
        unsigned int    resvered              : 17  ; /* [27..11]  */
        unsigned int    sharp_coring          : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_SHARP_THR;

/* Define the union U_SR_SMOOTH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    plus_ctrl             : 10  ; /* [9..0]  */
        unsigned int    resvered              : 20  ; /* [29..10]  */
        unsigned int    plus_en               : 1   ; /* [30]  */
        unsigned int    smooth_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_SMOOTH;

/* Define the union U_SR_HSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hratio                : 24  ; /* [23..0]  */
        unsigned int    hfir_order            : 1   ; /* [24]  */
        unsigned int    hchfir_en             : 1   ; /* [25]  */
        unsigned int    hlfir_en              : 1   ; /* [26]  */
        unsigned int    reserved_0            : 1   ; /* [27]  */
        unsigned int    hchmid_en             : 1   ; /* [28]  */
        unsigned int    hlmid_en              : 1   ; /* [29]  */
        unsigned int    hchmsc_en             : 1   ; /* [30]  */
        unsigned int    hlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HSP;

/* Define the union U_SR_HLOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_loffset           : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HLOFFSET;

/* Define the union U_SR_HCOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_coffset           : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOFFSET;

/* Define the union U_SR_VSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    zme_in_fmt            : 2   ; /* [20..19]  */
        unsigned int    zme_out_fmt           : 2   ; /* [22..21]  */
        unsigned int    vchfir_en             : 1   ; /* [23]  */
        unsigned int    vlfir_en              : 1   ; /* [24]  */
        unsigned int    avfir_mode            : 1   ; /* [25]  */
        unsigned int    reserved_1            : 1   ; /* [26]  */
        unsigned int    ahfir_mode            : 1   ; /* [27]  */
        unsigned int    vchmid_en             : 1   ; /* [28]  */
        unsigned int    vlmid_en              : 1   ; /* [29]  */
        unsigned int    vchmsc_en             : 1   ; /* [30]  */
        unsigned int    vlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VSP;

/* Define the union U_SR_VSR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vratio                : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VSR;

/* Define the union U_SR_VOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vchroma_offset        : 16  ; /* [15..0]  */
        unsigned int    vluma_offset          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VOFFSET;

/* Define the union U_SR_VBOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbchroma_offset       : 16  ; /* [15..0]  */
        unsigned int    vbluma_offset         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VBOFFSET;

/* Define the union U_SR_RINGDT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grad_thres_h          : 10  ; /* [9..0]  */
        unsigned int    grad_thres_l          : 10  ; /* [19..10]  */
        unsigned int    grad_flat_thr         : 10  ; /* [29..20]  */
        unsigned int    ringdt_en             : 1   ; /* [30]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_RINGDT0;

/* Define the union U_SR_RINGDT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grad_flat_thr2        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    grad_slop             : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_RINGDT1;

/* Define the union U_SR_SKINDT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_data             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 23  ; /* [30..8]  */
        unsigned int    skindt_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_SKINDT_CTRL;

/* Define the union U_SR_SKINDT_EXP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    y_expect_value        : 10  ; /* [9..0]  */
        unsigned int    u_expect_value        : 10  ; /* [19..10]  */
        unsigned int    v_expect_value        : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_SKINDT_EXP;

/* Define the union U_SR_SKINDT_YTHR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    y_thres_h             : 10  ; /* [9..0]  */
        unsigned int    y_thres_l             : 10  ; /* [19..10]  */
        unsigned int    y_slop                : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_SKINDT_YTHR;

/* Define the union U_SR_SKINDT_UTHR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    u_thres_h             : 10  ; /* [9..0]  */
        unsigned int    u_thres_l             : 10  ; /* [19..10]  */
        unsigned int    u_slop                : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_SKINDT_UTHR;

/* Define the union U_SR_SKINDT_VTHR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_thres_h             : 10  ; /* [9..0]  */
        unsigned int    v_thres_l             : 10  ; /* [19..10]  */
        unsigned int    v_slop                : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_SKINDT_VTHR;

/* Define the union U_SR_HANCE_SLOP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sharp_high_slop       : 16  ; /* [15..0]  */
        unsigned int    sharp_low_slop        : 12  ; /* [27..16]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HANCE_SLOP;

/* Define the union U_SR_HANCE_SHARP_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sharp_thres_h         : 10  ; /* [9..0]  */
        unsigned int    sharp_thres_l         : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HANCE_SHARP_THR;

/* Define the union U_SR_HANCE_LOW_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sharp_low_ctrl_h      : 10  ; /* [9..0]  */
        unsigned int    sharp_low_ctrl_l      : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HANCE_LOW_CTRL;

/* Define the union U_SR_HANCE_HIGH_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sharp_high_ctrl_h     : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 1   ; /* [9]  */
        unsigned int    sharp_high_ctrl_l     : 9   ; /* [18..10]  */
        unsigned int    reserved_1            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HANCE_HIGH_CTRL;

/* Define the union U_SR_HANCE_THR0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sharp_low_start       : 5   ; /* [4..0]  */
        unsigned int    sharp_high_start      : 8   ; /* [12..5]  */
        unsigned int    strengh               : 5   ; /* [17..13]  */
        unsigned int    edge_factor_ctrl      : 5   ; /* [22..18]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HANCE_THR0;

/* Define the union U_SR_HANCE_THR1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    skin_thres_h          : 5   ; /* [4..0]  */
        unsigned int    skin_thres_l          : 5   ; /* [9..5]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    ring_thres_h          : 8   ; /* [23..16]  */
        unsigned int    ring_thres_l          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HANCE_THR1;

/* Define the union U_SR_HANCE_THR2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sharp_high_ctrl       : 10  ; /* [9..0]  */
        unsigned int    nolinear_ctrl         : 10  ; /* [19..10]  */
        unsigned int    shoot_thrsh           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HANCE_THR2;

/* Define the union U_SR_DIR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir_hv_ctrl           : 10  ; /* [9..0]  */
        unsigned int    dir_dg_ctrl           : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_DIR_CTRL;

/* Define the union U_SR_HCOEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hlcoef02              : 10  ; /* [9..0]  */
        unsigned int    hlcoef01              : 10  ; /* [19..10]  */
        unsigned int    hlcoef00              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF0;

/* Define the union U_SR_HCOEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hlcoef05              : 10  ; /* [9..0]  */
        unsigned int    hlcoef04              : 10  ; /* [19..10]  */
        unsigned int    hlcoef03              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF1;

/* Define the union U_SR_HCOEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hlcoef10              : 10  ; /* [9..0]  */
        unsigned int    hlcoef07              : 10  ; /* [19..10]  */
        unsigned int    hlcoef06              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF2;

/* Define the union U_SR_HCOEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hlcoef13              : 10  ; /* [9..0]  */
        unsigned int    hlcoef12              : 10  ; /* [19..10]  */
        unsigned int    hlcoef11              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF3;

/* Define the union U_SR_HCOEF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hlcoef16              : 10  ; /* [9..0]  */
        unsigned int    hlcoef15              : 10  ; /* [19..10]  */
        unsigned int    hlcoef14              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF4;

/* Define the union U_SR_HCOEF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hlcoef17              : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF5;

/* Define the union U_SR_HCOEF6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hccoef02              : 10  ; /* [9..0]  */
        unsigned int    hccoef01              : 10  ; /* [19..10]  */
        unsigned int    hccoef00              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF6;

/* Define the union U_SR_HCOEF7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hccoef05              : 10  ; /* [9..0]  */
        unsigned int    hccoef04              : 10  ; /* [19..10]  */
        unsigned int    hccoef03              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF7;

/* Define the union U_SR_HCOEF8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hccoef10              : 10  ; /* [9..0]  */
        unsigned int    hccoef07              : 10  ; /* [19..10]  */
        unsigned int    hccoef06              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF8;

/* Define the union U_SR_HCOEF9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hccoef13              : 10  ; /* [9..0]  */
        unsigned int    hccoef12              : 10  ; /* [19..10]  */
        unsigned int    hccoef11              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF9;

/* Define the union U_SR_HCOEF10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hccoef16              : 10  ; /* [9..0]  */
        unsigned int    hccoef15              : 10  ; /* [19..10]  */
        unsigned int    hccoef14              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF10;

/* Define the union U_SR_HCOEF11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hccoef17              : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_HCOEF11;

/* Define the union U_SR_VCOEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vlcoef02              : 10  ; /* [9..0]  */
        unsigned int    vlcoef01              : 10  ; /* [19..10]  */
        unsigned int    vlcoef00              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VCOEF0;

/* Define the union U_SR_VCOEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vlcoef05              : 10  ; /* [9..0]  */
        unsigned int    vlcoef04              : 10  ; /* [19..10]  */
        unsigned int    vlcoef03              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VCOEF1;

/* Define the union U_SR_VCOEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vlcoef12              : 10  ; /* [9..0]  */
        unsigned int    vlcoef11              : 10  ; /* [19..10]  */
        unsigned int    vlcoef10              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VCOEF2;

/* Define the union U_SR_VCOEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vlcoef15              : 10  ; /* [9..0]  */
        unsigned int    vlcoef14              : 10  ; /* [19..10]  */
        unsigned int    vlcoef13              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VCOEF3;

/* Define the union U_SR_VCOEF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vccoef02              : 10  ; /* [9..0]  */
        unsigned int    vccoef01              : 10  ; /* [19..10]  */
        unsigned int    vccoef00              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VCOEF4;

/* Define the union U_SR_VCOEF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vccoef05              : 10  ; /* [9..0]  */
        unsigned int    vccoef04              : 10  ; /* [19..10]  */
        unsigned int    vccoef03              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VCOEF5;

/* Define the union U_SR_VCOEF6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vccoef12              : 10  ; /* [9..0]  */
        unsigned int    vccoef11              : 10  ; /* [19..10]  */
        unsigned int    vccoef10              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VCOEF6;

/* Define the union U_SR_VCOEF7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vccoef15              : 10  ; /* [9..0]  */
        unsigned int    vccoef14              : 10  ; /* [19..10]  */
        unsigned int    vccoef13              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_VCOEF7;

/* Define the union U_DHD0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    disp_mode             : 3   ; /* [3..1]  */
        unsigned int    iop                   : 1   ; /* [4]  */
        unsigned int    intf_ivs              : 1   ; /* [5]  */
        unsigned int    intf_ihs              : 1   ; /* [6]  */
        unsigned int    intf_idv              : 1   ; /* [7]  */
        unsigned int    reserved_0            : 1   ; /* [8]  */
        unsigned int    hdmi420c_sel          : 1   ; /* [9]  */
        unsigned int    hdmi420_en            : 1   ; /* [10]  */
        unsigned int    uf_offline_en         : 1   ; /* [11]  */
        unsigned int    gmm_mode              : 1   ; /* [12]  */
        unsigned int    gmm_en                : 1   ; /* [13]  */
        unsigned int    hdmi_mode             : 1   ; /* [14]  */
        unsigned int    twochn_debug          : 1   ; /* [15]  */
        unsigned int    reserved_1            : 1   ; /* [16]  */
        unsigned int    mirror_en             : 1   ; /* [17]  */
        unsigned int    sin_en                : 1   ; /* [18]  */
        unsigned int    reserved_2            : 1   ; /* [19]  */
        unsigned int    fpga_lmt_width        : 7   ; /* [26..20]  */
        unsigned int    fpga_lmt_en           : 1   ; /* [27]  */
        unsigned int    p2i_en                : 1   ; /* [28]  */
        unsigned int    cbar_sel              : 1   ; /* [29]  */
        unsigned int    cbar_en               : 1   ; /* [30]  */
        unsigned int    intf_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CTRL;

/* Define the union U_DHD0_VSYNC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vact                  : 12  ; /* [11..0]  */
        unsigned int    vbb                   : 10  ; /* [21..12]  */
        unsigned int    vfb                   : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VSYNC;

/* Define the union U_DHD0_HSYNC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hact                  : 16  ; /* [15..0]  */
        unsigned int    hbb                   : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_HSYNC1;

/* Define the union U_DHD0_HSYNC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hfb                   : 16  ; /* [15..0]  */
        unsigned int    hmid                  : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_HSYNC2;

/* Define the union U_DHD0_VPLUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bvact                 : 12  ; /* [11..0]  */
        unsigned int    bvbb                  : 10  ; /* [21..12]  */
        unsigned int    bvfb                  : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VPLUS;

/* Define the union U_DHD0_PWR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpw                   : 16  ; /* [15..0]  */
        unsigned int    vpw                   : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_PWR;

/* Define the union U_DHD0_VTTHD3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vtmgthd3              : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 2   ; /* [14..13]  */
        unsigned int    thd3_mode             : 1   ; /* [15]  */
        unsigned int    vtmgthd4              : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 2   ; /* [30..29]  */
        unsigned int    thd4_mode             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VTTHD3;

/* Define the union U_DHD0_VTTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vtmgthd1              : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 2   ; /* [14..13]  */
        unsigned int    thd1_mode             : 1   ; /* [15]  */
        unsigned int    vtmgthd2              : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 2   ; /* [30..29]  */
        unsigned int    thd2_mode             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VTTHD;

/* Define the union U_DHD0_SYNC_INV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcd_dv_inv            : 1   ; /* [0]  */
        unsigned int    lcd_hs_inv            : 1   ; /* [1]  */
        unsigned int    lcd_vs_inv            : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    vga_dv_inv            : 1   ; /* [4]  */
        unsigned int    vga_hs_inv            : 1   ; /* [5]  */
        unsigned int    vga_vs_inv            : 1   ; /* [6]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    hdmi_dv_inv           : 1   ; /* [8]  */
        unsigned int    hdmi_hs_inv           : 1   ; /* [9]  */
        unsigned int    hdmi_vs_inv           : 1   ; /* [10]  */
        unsigned int    hdmi_f_inv            : 1   ; /* [11]  */
        unsigned int    date_dv_inv           : 1   ; /* [12]  */
        unsigned int    date_hs_inv           : 1   ; /* [13]  */
        unsigned int    date_vs_inv           : 1   ; /* [14]  */
        unsigned int    date_f_inv            : 1   ; /* [15]  */
        unsigned int    reserved_2            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_SYNC_INV;

/* Define the union U_DHD0_SRIRESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sr_iw                 : 12  ; /* [11..0]  */
        unsigned int    sr_ih                 : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_SRIRESO;

/* Define the union U_DHD0_SRSEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sr_sel                : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_SRSEL;

/* Define the union U_DHD0_DATA_SEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    date_data_sel         : 1   ; /* [0]  */
        unsigned int    vga_data_sel          : 1   ; /* [1]  */
        unsigned int    lcd_data_sel          : 1   ; /* [2]  */
        unsigned int    hdmi_data_sel         : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_DATA_SEL;

/* Define the union U_DHD0_CSC_IDC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc0               : 11  ; /* [10..0]  */
        unsigned int    cscidc1               : 11  ; /* [21..11]  */
        unsigned int    csc_en                : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CSC_IDC;

/* Define the union U_DHD0_CSC_ODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscodc0               : 11  ; /* [10..0]  */
        unsigned int    cscodc1               : 11  ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CSC_ODC;

/* Define the union U_DHD0_CSC_IODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc2               : 11  ; /* [10..0]  */
        unsigned int    cscodc2               : 11  ; /* [21..11]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CSC_IODC;

/* Define the union U_DHD0_CSC_P0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp00                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp01                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CSC_P0;

/* Define the union U_DHD0_CSC_P1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp02                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp10                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CSC_P1;

/* Define the union U_DHD0_CSC_P2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp11                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp12                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CSC_P2;

/* Define the union U_DHD0_CSC_P3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp20                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp21                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CSC_P3;

/* Define the union U_DHD0_CSC_P4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp22                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CSC_P4;

/* Define the union U_DHD0_DITHER0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    dither_round          : 1   ; /* [29]  */
        unsigned int    dither_mode           : 1   ; /* [30]  */
        unsigned int    dither_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_DITHER0_CTRL;

/* Define the union U_DHD0_DITHER0_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef0          : 8   ; /* [7..0]  */
        unsigned int    dither_coef1          : 8   ; /* [15..8]  */
        unsigned int    dither_coef2          : 8   ; /* [23..16]  */
        unsigned int    dither_coef3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_DITHER0_COEF0;

/* Define the union U_DHD0_DITHER0_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef4          : 8   ; /* [7..0]  */
        unsigned int    dither_coef5          : 8   ; /* [15..8]  */
        unsigned int    dither_coef6          : 8   ; /* [23..16]  */
        unsigned int    dither_coef7          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_DITHER0_COEF1;

/* Define the union U_DHD0_DITHER1_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    dither_round          : 1   ; /* [29]  */
        unsigned int    dither_mode           : 1   ; /* [30]  */
        unsigned int    dither_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_DITHER1_CTRL;

/* Define the union U_DHD0_DITHER1_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef0          : 8   ; /* [7..0]  */
        unsigned int    dither_coef1          : 8   ; /* [15..8]  */
        unsigned int    dither_coef2          : 8   ; /* [23..16]  */
        unsigned int    dither_coef3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_DITHER1_COEF0;

/* Define the union U_DHD0_DITHER1_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef4          : 8   ; /* [7..0]  */
        unsigned int    dither_coef5          : 8   ; /* [15..8]  */
        unsigned int    dither_coef6          : 8   ; /* [23..16]  */
        unsigned int    dither_coef7          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_DITHER1_COEF1;

/* Define the union U_DHD0_CLIP0_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_cl0              : 10  ; /* [9..0]  */
        unsigned int    clip_cl1              : 10  ; /* [19..10]  */
        unsigned int    clip_cl2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLIP0_L;

/* Define the union U_DHD0_CLIP0_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_ch0              : 10  ; /* [9..0]  */
        unsigned int    clip_ch1              : 10  ; /* [19..10]  */
        unsigned int    clip_ch2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLIP0_H;

/* Define the union U_DHD0_CLIP1_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_cl0              : 10  ; /* [9..0]  */
        unsigned int    clip_cl1              : 10  ; /* [19..10]  */
        unsigned int    clip_cl2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLIP1_L;

/* Define the union U_DHD0_CLIP1_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_ch0              : 10  ; /* [9..0]  */
        unsigned int    clip_ch1              : 10  ; /* [19..10]  */
        unsigned int    clip_ch2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLIP1_H;

/* Define the union U_DHD0_CLIP2_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_cl0              : 10  ; /* [9..0]  */
        unsigned int    clip_cl1              : 10  ; /* [19..10]  */
        unsigned int    clip_cl2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLIP2_L;

/* Define the union U_DHD0_CLIP2_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_ch0              : 10  ; /* [9..0]  */
        unsigned int    clip_ch1              : 10  ; /* [19..10]  */
        unsigned int    clip_ch2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLIP2_H;

/* Define the union U_DHD0_CLIP3_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_cl0              : 10  ; /* [9..0]  */
        unsigned int    clip_cl1              : 10  ; /* [19..10]  */
        unsigned int    clip_cl2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLIP3_L;

/* Define the union U_DHD0_CLIP3_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_ch0              : 10  ; /* [9..0]  */
        unsigned int    clip_ch1              : 10  ; /* [19..10]  */
        unsigned int    clip_ch2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLIP3_H;

/* Define the union U_DHD0_CLIP4_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_cl0              : 10  ; /* [9..0]  */
        unsigned int    clip_cl1              : 10  ; /* [19..10]  */
        unsigned int    clip_cl2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLIP4_L;

/* Define the union U_DHD0_CLIP4_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_ch0              : 10  ; /* [9..0]  */
        unsigned int    clip_ch1              : 10  ; /* [19..10]  */
        unsigned int    clip_ch2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLIP4_H;

/* Define the union U_DHD0_PARATHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    para_thd              : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 23  ; /* [30..8]  */
        unsigned int    dfs_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_PARATHD;

/* Define the union U_DHD0_VBI */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbi_data              : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 8   ; /* [23..16]  */
        unsigned int    vbi_addr              : 4   ; /* [27..24]  */
        unsigned int    reserved_1            : 3   ; /* [30..28]  */
        unsigned int    vbi_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VBI;

/* Define the union U_DHD0_HBI */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bitmap_frm_hc_lcnt    : 16  ; /* [15..0]  */
        unsigned int    bitmap_frm_gp0_lcnt   : 8   ; /* [23..16]  */
        unsigned int    bitmap_hc_uf_sta      : 1   ; /* [24]  */
        unsigned int    bitmap_gp0_uf_sta     : 1   ; /* [25]  */
        unsigned int    bitmap_hc_of_sta      : 1   ; /* [26]  */
        unsigned int    bitmap_gp0_of_sta     : 1   ; /* [27]  */
        unsigned int    bitmap_sync_en        : 1   ; /* [28]  */
        unsigned int    reserved_0            : 1   ; /* [29]  */
        unsigned int    hbi_hc_en             : 1   ; /* [30]  */
        unsigned int    hbi_gp0_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_HBI;

/* Define the union U_DHD0_START_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start_pos             : 8   ; /* [7..0]  */
        unsigned int    timing_start_pos      : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_START_POS;

/* Define the union U_DHD0_LOCKCFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    measure_en            : 1   ; /* [0]  */
        unsigned int    lock_cnt_en           : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_LOCKCFG;

/* Define the union U_DHD0_CAP_FRM_CNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cap_frm_cnt            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_CAP_FRM_CNT;
/* Define the union U_DHD0_VSYNC_CAP_VDP_CNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vsync_cap_vdp_cnt      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_VSYNC_CAP_VDP_CNT;
/* Define the union U_DHD0_GMM_COEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_GMM_COEFAD;
/* Define the union U_DHD0_PARAUP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd0_gmm_upd          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    sr_hlparaup           : 1   ; /* [4]  */
        unsigned int    sr_hcparaup           : 1   ; /* [5]  */
        unsigned int    sr_vlparaup           : 1   ; /* [6]  */
        unsigned int    sr_vcparaup           : 1   ; /* [7]  */
        unsigned int    dim_lut_paraup        : 1   ; /* [8]  */
        unsigned int    dim_hf_paraup         : 1   ; /* [9]  */
        unsigned int    dim_vf_paraup         : 1   ; /* [10]  */
        unsigned int    reserved_1            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_PARAUP;

/* Define the union U_DHD0_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vback_blank           : 1   ; /* [0]  */
        unsigned int    vblank                : 1   ; /* [1]  */
        unsigned int    bottom_field          : 1   ; /* [2]  */
        unsigned int    vcnt                  : 13  ; /* [15..3]  */
        unsigned int    count_int             : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_STATE;

/* Define the union U_DHDWCG_NON2LCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    gma_lin_thre_0        : 8   ; /* [9..2]  */
        unsigned int    gma_lin_thre_1        : 10  ; /* [19..10]  */
        unsigned int    gma_lin_thre_2        : 10  ; /* [29..20]  */
        unsigned int    gma_lin_init_slp      : 1   ; /* [30]  */
        unsigned int    gma_lin_neg_scl       : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_NON2LCTRL;

/* Define the union U_DHDWCG_NON2LCOEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gma_lin_coef_a_0      : 10  ; /* [9..0]  */
        unsigned int    gma_lin_coef_b_0      : 12  ; /* [21..10]  */
        unsigned int    gma_lin_coef_c_0      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_NON2LCOEF0;

/* Define the union U_DHDWCG_NON2LCOEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gma_lin_coef_a_1      : 10  ; /* [9..0]  */
        unsigned int    gma_lin_coef_b_1      : 12  ; /* [21..10]  */
        unsigned int    gma_lin_coef_c_1      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_NON2LCOEF1;

/* Define the union U_DHDWCG_NON2LCOEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gma_lin_coef_a_2      : 10  ; /* [9..0]  */
        unsigned int    gma_lin_coef_b_2      : 12  ; /* [21..10]  */
        unsigned int    gma_lin_coef_c_2      : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_NON2LCOEF2;

/* Define the union U_DHDWCG_CSC2CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_r_r_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_r_g_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 5   ; /* [28..24]  */
        unsigned int    csc2_scale_sel        : 2   ; /* [30..29]  */
        unsigned int    csc2_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_CSC2CTRL;

/* Define the union U_DHDWCG_CSC2COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_r_b_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_g_r_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_CSC2COEF0;

/* Define the union U_DHDWCG_CSC2COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_g_g_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_g_b_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_CSC2COEF1;

/* Define the union U_DHDWCG_CSC2COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_b_r_coef         : 12  ; /* [11..0]  */
        unsigned int    csc2_b_g_coef         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_CSC2COEF2;

/* Define the union U_DHDWCG_CSC2COEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc2_b_b_coef         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_CSC2COEF3;

/* Define the union U_DHDWCG_L2NONTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_thre_0        : 8   ; /* [7..0]  */
        unsigned int    lin_gma_thre_1        : 11  ; /* [18..8]  */
        unsigned int    lin_gma_thre_2        : 11  ; /* [29..19]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_L2NONTHD;

/* Define the union U_DHDWCG_L2NONCOEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_coef_a_0      : 11  ; /* [10..0]  */
        unsigned int    lin_gma_coef_b_0      : 10  ; /* [20..11]  */
        unsigned int    lin_gma_coef_c_0      : 9   ; /* [29..21]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_L2NONCOEF0;

/* Define the union U_DHDWCG_L2NONCOEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_coef_a_1      : 11  ; /* [10..0]  */
        unsigned int    lin_gma_coef_b_1      : 10  ; /* [20..11]  */
        unsigned int    lin_gma_coef_c_1      : 9   ; /* [29..21]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_L2NONCOEF1;

/* Define the union U_DHDWCG_L2NONCOEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lin_gma_coef_a_2      : 11  ; /* [10..0]  */
        unsigned int    lin_gma_coef_b_2      : 10  ; /* [20..11]  */
        unsigned int    lin_gma_coef_c_2      : 9   ; /* [29..21]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHDWCG_L2NONCOEF2;

/* Define the union U_DHD0_DITHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    dither_round          : 1   ; /* [29]  */
        unsigned int    dither_mode           : 1   ; /* [30]  */
        unsigned int    dither_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_DITHER_CTRL;

/* Define the union U_DHD0_DITHER_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef0          : 8   ; /* [7..0]  */
        unsigned int    dither_coef1          : 8   ; /* [15..8]  */
        unsigned int    dither_coef2          : 8   ; /* [23..16]  */
        unsigned int    dither_coef3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_DITHER_COEF0;

/* Define the union U_DHD0_DITHER_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef4          : 8   ; /* [7..0]  */
        unsigned int    dither_coef5          : 8   ; /* [15..8]  */
        unsigned int    dither_coef6          : 8   ; /* [23..16]  */
        unsigned int    dither_coef7          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_DITHER_COEF1;

/* Define the union U_SR_CSC0_IDC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc0               : 11  ; /* [10..0]  */
        unsigned int    cscidc1               : 11  ; /* [21..11]  */
        unsigned int    csc_en                : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC0_IDC;

/* Define the union U_SR_CSC0_ODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscodc0               : 11  ; /* [10..0]  */
        unsigned int    cscodc1               : 11  ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC0_ODC;

/* Define the union U_SR_CSC0_IODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc2               : 11  ; /* [10..0]  */
        unsigned int    cscodc2               : 11  ; /* [21..11]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC0_IODC;

/* Define the union U_SR_CSC0_P0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp00                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp01                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC0_P0;

/* Define the union U_SR_CSC0_P1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp02                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp10                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC0_P1;

/* Define the union U_SR_CSC0_P2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp11                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp12                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC0_P2;

/* Define the union U_SR_CSC0_P3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp20                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp21                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC0_P3;

/* Define the union U_SR_CSC0_P4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp22                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC0_P4;

/* Define the union U_DHDHLCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dhdhlcoefad            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHDHLCOEFAD;
/* Define the union U_DHDHCCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dhdhccoefad            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHDHCCOEFAD;
/* Define the union U_DHDVLCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dhdvlcoefad            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHDVLCOEFAD;
/* Define the union U_DHDVCCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dhdvccoefad            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHDVCCOEFAD;
/* Define the union U_DHDDIMLUTAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dhddimlutad            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHDDIMLUTAD;
/* Define the union U_DHDDIMHFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dhddimhfad             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHDDIMHFAD;
/* Define the union U_DHDDIMVFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dhddimvfad             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHDDIMVFAD;
/* Define the union U_SR_CSC1_IDC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc0               : 11  ; /* [10..0]  */
        unsigned int    cscidc1               : 11  ; /* [21..11]  */
        unsigned int    csc_en                : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC1_IDC;

/* Define the union U_SR_CSC1_ODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscodc0               : 11  ; /* [10..0]  */
        unsigned int    cscodc1               : 11  ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC1_ODC;

/* Define the union U_SR_CSC1_IODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc2               : 11  ; /* [10..0]  */
        unsigned int    cscodc2               : 11  ; /* [21..11]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC1_IODC;

/* Define the union U_SR_CSC1_P0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp00                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp01                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC1_P0;

/* Define the union U_SR_CSC1_P1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp02                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp10                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC1_P1;

/* Define the union U_SR_CSC1_P2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp11                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp12                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC1_P2;

/* Define the union U_SR_CSC1_P3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp20                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp21                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC1_P3;

/* Define the union U_SR_CSC1_P4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp22                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SR_CSC1_P4;

/* Define the union U_DIM_GLB_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode_init_led         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 3   ; /* [14..12]  */
        unsigned int    disable_2d            : 1   ; /* [15]  */
        unsigned int    bypass_led            : 1   ; /* [16]  */
        unsigned int    sel_uhd               : 1   ; /* [17]  */
        unsigned int    reserved_1            : 6   ; /* [23..18]  */
        unsigned int    bypass_lcd            : 1   ; /* [24]  */
        unsigned int    diming_en             : 1   ; /* [25]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_GLB_CTRL;

/* Define the union U_DIM_LED_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    led_numv              : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    led_numh              : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED_NUM;

/* Define the union U_DIM_SEG_METIRCS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    seg_height            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    seg_width             : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_SEG_METIRCS;

/* Define the union U_DIM_START_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcnt_init             : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    hcnt_init             : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_START_POS;

/* Define the union U_DIM_STAT_METRICS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stat_height           : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    stat_width            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_STAT_METRICS;

/* Define the union U_DIM_GLB_NORM_UNIT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    glb_norm_unit         : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_GLB_NORM_UNIT;

/* Define the union U_DIM_SEG_NORM_UNIT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    seg_norm_unit         : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_SEG_NORM_UNIT;

/* Define the union U_DIM_HIST_STAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    thresh_md2            : 8   ; /* [7..0]  */
        unsigned int    thresh_md0            : 8   ; /* [15..8]  */
        unsigned int    bits_w_hist           : 3   ; /* [18..16]  */
        unsigned int    reserved_0            : 5   ; /* [23..19]  */
        unsigned int    bits_b_hist           : 3   ; /* [26..24]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_HIST_STAT;

/* Define the union U_DIM_ADJ0D_CORE0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_mid_0d           : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    core_low_0d           : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_ADJ0D_CORE0;

/* Define the union U_DIM_ADJ0D_CORE1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_high_0d          : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_ADJ0D_CORE1;

/* Define the union U_DIM_LED0D_LOW_THRESH0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x1_low_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    x0_low_0d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_LOW_THRESH0;

/* Define the union U_DIM_LED0D_LOW_THRESH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x2_low_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_LOW_THRESH1;

/* Define the union U_DIM_LED0D_LOW_OFFSET0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g1_low_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g0_low_0d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_LOW_OFFSET0;

/* Define the union U_DIM_LED0D_LOW_OFFSET1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g3_low_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g2_low_0d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_LOW_OFFSET1;

/* Define the union U_DIM_LED0D_LOW_GAIN0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k1_low_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k0_low_0d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_LOW_GAIN0;

/* Define the union U_DIM_LED0D_LOW_GAIN1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k3_low_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k2_low_0d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_LOW_GAIN1;

/* Define the union U_DIM_LED0D_MID_THRESH0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x1_mid_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    x0_mid_0d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_MID_THRESH0;

/* Define the union U_DIM_LED0D_MID_THRESH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x2_mid_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_MID_THRESH1;

/* Define the union U_DIM_LED0D_MID_OFFSET0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g1_mid_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g0_mid_0d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_MID_OFFSET0;

/* Define the union U_DIM_LED0D_MID_OFFSET1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g3_mid_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g2_mid_0d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_MID_OFFSET1;

/* Define the union U_DIM_LED0D_MID_GAIN0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k1_mid_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k0_mid_0d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_MID_GAIN0;

/* Define the union U_DIM_LED0D_MID_GAIN1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k3_mid_0d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k2_mid_0d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_MID_GAIN1;

/* Define the union U_DIM_LED0D_HIGH_THRESH0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x1_high_0d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    x0_high_0d            : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_HIGH_THRESH0;

/* Define the union U_DIM_LED0D_HIGH_THRESH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x2_high_0d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_HIGH_THRESH1;

/* Define the union U_DIM_LED0D_HIGH_OFFSET0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g1_high_0d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g0_high_0d            : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_HIGH_OFFSET0;

/* Define the union U_DIM_LED0D_HIGH_OFFSET1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g3_high_0d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g2_high_0d            : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_HIGH_OFFSET1;

/* Define the union U_DIM_LED0D_HIGH_GAIN0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k1_high_0d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k0_high_0d            : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_HIGH_GAIN0;

/* Define the union U_DIM_LED0D_HIGH_GAIN1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k3_high_0d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k2_high_0d            : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_HIGH_GAIN1;

/* Define the union U_DIM_ADJ2D_CORE0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_mid_2d           : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    core_low_2d           : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_ADJ2D_CORE0;

/* Define the union U_DIM_ADJ2D_CORE1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_high_2d          : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_ADJ2D_CORE1;

/* Define the union U_DIM_LED2D_LOW_THRESH0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x1_low_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    x0_low_2d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_LOW_THRESH0;

/* Define the union U_DIM_LED2D_LOW_THRESH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x2_low_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_LOW_THRESH1;

/* Define the union U_DIM_LED2D_LOW_OFFSET0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g1_low_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g0_low_2d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_LOW_OFFSET0;

/* Define the union U_DIM_LED2D_LOW_OFFSET1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g3_low_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g2_low_2d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_LOW_OFFSET1;

/* Define the union U_DIM_LED2D_LOW_GAIN0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k1_low_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k0_low_2d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_LOW_GAIN0;

/* Define the union U_DIM_LED2D_LOW_GAIN1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k3_low_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k2_low_2d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_LOW_GAIN1;

/* Define the union U_DIM_LED2D_MID_THRESH0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x1_mid_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    x0_mid_2d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_MID_THRESH0;

/* Define the union U_DIM_LED2D_MID_THRESH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x2_mid_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_MID_THRESH1;

/* Define the union U_DIM_LED2D_MID_OFFSET0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g1_mid_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g0_mid_2d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_MID_OFFSET0;

/* Define the union U_DIM_LED2D_MID_OFFSET1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g3_mid_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g2_mid_2d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_MID_OFFSET1;

/* Define the union U_DIM_LED2D_MID_GAIN0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k1_mid_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k0_mid_2d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_MID_GAIN0;

/* Define the union U_DIM_LED2D_MID_GAIN1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k3_mid_2d             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k2_mid_2d             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_MID_GAIN1;

/* Define the union U_DIM_LED2D_HIGH_THRESH0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x1_high_2d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    x0_high_2d            : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_HIGH_THRESH0;

/* Define the union U_DIM_LED2D_HIGH_THRESH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x2_high_2d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_HIGH_THRESH1;

/* Define the union U_DIM_LED2D_HIGH_OFFSET0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g1_high_2d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g0_high_2d            : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_HIGH_OFFSET0;

/* Define the union U_DIM_LED2D_HIGH_OFFSET1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g3_high_2d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    g2_high_2d            : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_HIGH_OFFSET1;

/* Define the union U_DIM_LED2D_HIGH_GAIN0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k1_high_2d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k0_high_2d            : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_HIGH_GAIN0;

/* Define the union U_DIM_LED2D_HIGH_GAIN1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k3_high_2d            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k2_high_2d            : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_HIGH_GAIN1;

/* Define the union U_DIM_LED0D_CORE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_dstat_high       : 8   ; /* [7..0]  */
        unsigned int    core_dstat_mid        : 8   ; /* [15..8]  */
        unsigned int    core_dstat_low        : 8   ; /* [23..16]  */
        unsigned int    k_dstat_0d            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_CORE;

/* Define the union U_DIM_LED0D_GAIN_MISC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_led0d            : 8   ; /* [7..0]  */
        unsigned int    gain_led0d_tf         : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_GAIN_MISC;

/* Define the union U_DIM_LED2D_GAIN_MISC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_led2d            : 8   ; /* [7..0]  */
        unsigned int    gain_bldmax2d         : 8   ; /* [15..8]  */
        unsigned int    gain_bld_0d2d         : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED2D_GAIN_MISC;

/* Define the union U_DIM_PRE_0D2D_BLD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_led0d            : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    k_led0d               : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_PRE_0D2D_BLD;

/* Define the union U_DIM_FINAL_GAIN_0D */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_final_0d         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    offset_final_0d       : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_FINAL_GAIN_0D;

/* Define the union U_DIM_FINAL_CLIP_0D */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_btm_final_0d     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    clip_up_final_0d      : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_FINAL_CLIP_0D;

/* Define the union U_DIM_FINAL_GAIN_2D */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_final_2d         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    offset_final_2d       : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_FINAL_GAIN_2D;

/* Define the union U_DIM_FINAL_CLIP_2D */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_btm_final_2d     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    clip_up_final_2d      : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_FINAL_CLIP_2D;

/* Define the union U_DIM_LED0D_STATUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    led0d_sw              : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    sc_0d_sw              : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D_STATUS;

/* Define the union U_DIM_VFIR_COEF_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vfir_tap3             : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    vfir_tap2             : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    vfir_tap1             : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    vfir_tap0             : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_VFIR_COEF_0;

/* Define the union U_DIM_VFIR_COEF_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vfir_tap4             : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_VFIR_COEF_1;

/* Define the union U_DIM_HFIR_COEF_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hfir_tap3             : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    hfir_tap2             : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    hfir_tap1             : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    hfir_tap0             : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_HFIR_COEF_0;

/* Define the union U_DIM_HFIR_COEF_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hfir_tap4             : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_HFIR_COEF_1;

/* Define the union U_DIM_POST_FIR_BLD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_vfir             : 8   ; /* [7..0]  */
        unsigned int    gain_hfir             : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_POST_FIR_BLD;

/* Define the union U_DIM_POST_FIR_GAIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_led2d               : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    core_led2d            : 6   ; /* [21..16]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    gain_tf               : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_POST_FIR_GAIN;

/* Define the union U_DIM_LCD_COMP_0D */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcd_k_led0d           : 8   ; /* [7..0]  */
        unsigned int    lcd_core_led0d        : 9   ; /* [16..8]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LCD_COMP_0D;

/* Define the union U_DIM_LCD_COMP_2D */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcd_k_led2d           : 8   ; /* [7..0]  */
        unsigned int    lcd_core_led2d        : 9   ; /* [16..8]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LCD_COMP_2D;

/* Define the union U_DIM_LCD_COMPGAIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcd_compgain_2d       : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LCD_COMPGAIN;

/* Define the union U_DIM_LED_PANEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_led_panel         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    k_led_panel           : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED_PANEL;

/* Define the union U_DIM_LED0D2D */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    led2d_final           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    led0d_final           : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_LED0D2D;

/* Define the union U_DIM_SCL_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 26  ; /* [25..0]  */
        unsigned int    lhfir_mode            : 1   ; /* [26]  */
        unsigned int    lhfir_mid_en          : 1   ; /* [27]  */
        unsigned int    lhfir_en              : 1   ; /* [28]  */
        unsigned int    lvfir_mode            : 1   ; /* [29]  */
        unsigned int    lvfir_mid_en          : 1   ; /* [30]  */
        unsigned int    lvfir_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_SCL_CTRL;

/* Define the union U_DIM_SCL_OFFSET_V */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lvfir_offset          : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_SCL_OFFSET_V;

/* Define the union U_DIM_SCL_OFFSET_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lhfir_offset          : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_SCL_OFFSET_H;

/* Define the union U_DIM_SCL_RATIO_V */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lvfir_scl_dec         : 16  ; /* [15..0]  */
        unsigned int    lvfir_scl_int         : 4   ; /* [19..16]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_SCL_RATIO_V;

/* Define the union U_DIM_SCL_RATIO_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lhfir_scl_dec         : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 4   ; /* [23..20]  */
        unsigned int    lhfir_scl_int         : 4   ; /* [27..24]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_SCL_RATIO_H;

/* Define the union U_DIM_PARA_REN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    local2d_stat_rd_en    : 1   ; /* [0]  */
        unsigned int    dimlut_rd_en          : 1   ; /* [1]  */
        unsigned int    dim_scl_coef_rd_en    : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_PARA_REN;

/* Define the union U_DIM_PARA_DATA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    para_data             : 31  ; /* [30..0]  */
        unsigned int    rd_error_flag         : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIM_PARA_DATA;

/* Define the union U_INTF_CHKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_INTF_CHKSUM_Y;
/* Define the union U_INTF_CHKSUM_U */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_INTF_CHKSUM_U;
/* Define the union U_INTF_CHKSUM_V */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_INTF_CHKSUM_V;
/* Define the union U_INTF1_CHKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_INTF1_CHKSUM_Y;
/* Define the union U_INTF1_CHKSUM_U */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_INTF1_CHKSUM_U;
/* Define the union U_INTF1_CHKSUM_V */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_INTF1_CHKSUM_V;
/* Define the union U_HDATE_VERSION */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int hdate_version          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HDATE_VERSION;
/* Define the union U_HDATE_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hd_en                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_EN;

/* Define the union U_HDATE_POLA_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsync_in_pola         : 1   ; /* [0]  */
        unsigned int    vsync_in_pola         : 1   ; /* [1]  */
        unsigned int    fid_in_pola           : 1   ; /* [2]  */
        unsigned int    hsync_out_pola        : 1   ; /* [3]  */
        unsigned int    vsync_out_pola        : 1   ; /* [4]  */
        unsigned int    fid_out_pola          : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_POLA_CTRL;

/* Define the union U_HDATE_VIDEO_FORMAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_ft              : 4   ; /* [3..0]  */
        unsigned int    sync_add_ctrl         : 3   ; /* [6..4]  */
        unsigned int    video_out_ctrl        : 2   ; /* [8..7]  */
        unsigned int    csc_ctrl              : 3   ; /* [11..9]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_VIDEO_FORMAT;

/* Define the union U_HDATE_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    line_len              : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    frame_len             : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 1   ; /* [27]  */
        unsigned int    mv_en_pin             : 1   ; /* [28]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_STATE;

/* Define the union U_HDATE_OUT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vsync_sel             : 2   ; /* [1..0]  */
        unsigned int    hsync_sel             : 2   ; /* [3..2]  */
        unsigned int    video3_sel            : 2   ; /* [5..4]  */
        unsigned int    video2_sel            : 2   ; /* [7..6]  */
        unsigned int    video1_sel            : 2   ; /* [9..8]  */
        unsigned int    src_ctrl              : 2   ; /* [11..10]  */
        unsigned int    sync_lpf_en           : 1   ; /* [12]  */
        unsigned int    sd_sel                : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_OUT_CTRL;

/* Define the union U_HDATE_SRC_13_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap1_1           : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 11  ; /* [15..5]  */
        unsigned int    coef_tap1_3           : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF1;

/* Define the union U_HDATE_SRC_13_COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap2_1           : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 10  ; /* [15..6]  */
        unsigned int    coef_tap2_3           : 6   ; /* [21..16]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF2;

/* Define the union U_HDATE_SRC_13_COEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap3_1           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 9   ; /* [15..7]  */
        unsigned int    coef_tap3_3           : 7   ; /* [22..16]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF3;

/* Define the union U_HDATE_SRC_13_COEF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap4_1           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    coef_tap4_3           : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF4;

/* Define the union U_HDATE_SRC_13_COEF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap5_1           : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    coef_tap5_3           : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF5;

/* Define the union U_HDATE_SRC_13_COEF6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap6_1           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef_tap6_3           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF6;

/* Define the union U_HDATE_SRC_13_COEF7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap7_1           : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    coef_tap7_3           : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF7;

/* Define the union U_HDATE_SRC_13_COEF8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap8_1           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef_tap8_3           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF8;

/* Define the union U_HDATE_SRC_13_COEF9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap9_1           : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    coef_tap9_3           : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF9;

/* Define the union U_HDATE_SRC_13_COEF10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap10_1          : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    coef_tap10_3          : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF10;

/* Define the union U_HDATE_SRC_13_COEF11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap11_1          : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 9   ; /* [15..7]  */
        unsigned int    coef_tap11_3          : 7   ; /* [22..16]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF11;

/* Define the union U_HDATE_SRC_13_COEF12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap12_1          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 10  ; /* [15..6]  */
        unsigned int    coef_tap12_3          : 6   ; /* [21..16]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF12;

/* Define the union U_HDATE_SRC_13_COEF13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap13_1          : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 11  ; /* [15..5]  */
        unsigned int    coef_tap13_3          : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_13_COEF13;

/* Define the union U_HDATE_SRC_24_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap1_2           : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 11  ; /* [15..5]  */
        unsigned int    coef_tap1_4           : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF1;

/* Define the union U_HDATE_SRC_24_COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap2_2           : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 10  ; /* [15..6]  */
        unsigned int    coef_tap2_4           : 6   ; /* [21..16]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF2;

/* Define the union U_HDATE_SRC_24_COEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap3_2           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 9   ; /* [15..7]  */
        unsigned int    coef_tap3_4           : 7   ; /* [22..16]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF3;

/* Define the union U_HDATE_SRC_24_COEF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap4_2           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    coef_tap4_4           : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF4;

/* Define the union U_HDATE_SRC_24_COEF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap5_2           : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    coef_tap5_4           : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF5;

/* Define the union U_HDATE_SRC_24_COEF6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap6_2           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef_tap6_4           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF6;

/* Define the union U_HDATE_SRC_24_COEF7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap7_2           : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    coef_tap7_4           : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF7;

/* Define the union U_HDATE_SRC_24_COEF8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap8_2           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef_tap8_4           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF8;

/* Define the union U_HDATE_SRC_24_COEF9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap9_1           : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    coef_tap9_2           : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF9;

/* Define the union U_HDATE_SRC_24_COEF10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap10_2          : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    coef_tap10_4          : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF10;

/* Define the union U_HDATE_SRC_24_COEF11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap11_1          : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 9   ; /* [15..7]  */
        unsigned int    coef_tap11_2          : 7   ; /* [22..16]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF11;

/* Define the union U_HDATE_SRC_24_COEF12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap12_2          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 10  ; /* [15..6]  */
        unsigned int    coef_tap12_4          : 6   ; /* [21..16]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF12;

/* Define the union U_HDATE_SRC_24_COEF13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef_tap13_2          : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 11  ; /* [15..5]  */
        unsigned int    coef_tap13_4          : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_SRC_24_COEF13;

/* Define the union U_HDATE_CSC_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_coef_r_y          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    csc_coef_r_cb         : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_CSC_COEF1;

/* Define the union U_HDATE_CSC_COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_coef_r_cr         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    csc_coef_g_y          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_CSC_COEF2;

/* Define the union U_HDATE_CSC_COEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_coef_g_cb         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    csc_coef_g_cr         : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_CSC_COEF3;

/* Define the union U_HDATE_CSC_COEF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_coef_b_y          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    csc_coef_b_cb         : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_CSC_COEF4;

/* Define the union U_HDATE_CSC_COEF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_coef_b_cr         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_CSC_COEF5;

/* Define the union U_HDATE_TEST */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    test_data             : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_TEST;

/* Define the union U_HDATE_VBI_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cgmsb_add_en          : 1   ; /* [0]  */
        unsigned int    cgmsa_add_en          : 1   ; /* [1]  */
        unsigned int    mv_en                 : 1   ; /* [2]  */
        unsigned int    vbi_lpf_en            : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_VBI_CTRL;

/* Define the union U_HDATE_CGMSA_DATA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cgmsa_data            : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_CGMSA_DATA;

/* Define the union U_HDATE_CGMSB_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdate_cgmsb_h         : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_CGMSB_H;

/* Define the union U_HDATE_CGMSB_DATA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cgmsb_data1            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HDATE_CGMSB_DATA1;
/* Define the union U_HDATE_CGMSB_DATA2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cgmsb_data2            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HDATE_CGMSB_DATA2;
/* Define the union U_HDATE_CGMSB_DATA3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cgmsb_data3            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HDATE_CGMSB_DATA3;
/* Define the union U_HDATE_CGMSB_DATA4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cgmsb_data4            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HDATE_CGMSB_DATA4;
/* Define the union U_DATE_COEFF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_seq                : 1   ; /* [0]  */
        unsigned int    chgain_en             : 1   ; /* [1]  */
        unsigned int    sylp_en               : 1   ; /* [2]  */
        unsigned int    chlp_en               : 1   ; /* [3]  */
        unsigned int    oversam2_en           : 1   ; /* [4]  */
        unsigned int    lunt_en               : 1   ; /* [5]  */
        unsigned int    oversam_en            : 2   ; /* [7..6]  */
        unsigned int    reserved_0            : 1   ; /* [8]  */
        unsigned int    luma_dl               : 4   ; /* [12..9]  */
        unsigned int    agc_amp_sel           : 1   ; /* [13]  */
        unsigned int    length_sel            : 1   ; /* [14]  */
        unsigned int    sync_mode_scart       : 1   ; /* [15]  */
        unsigned int    sync_mode_sel         : 2   ; /* [17..16]  */
        unsigned int    style_sel             : 4   ; /* [21..18]  */
        unsigned int    fm_sel                : 1   ; /* [22]  */
        unsigned int    vbi_lpf_en            : 1   ; /* [23]  */
        unsigned int    rgb_en                : 1   ; /* [24]  */
        unsigned int    scanline              : 1   ; /* [25]  */
        unsigned int    pbpr_lpf_en           : 1   ; /* [26]  */
        unsigned int    pal_half_en           : 1   ; /* [27]  */
        unsigned int    reserved_1            : 1   ; /* [28]  */
        unsigned int    dis_ire               : 1   ; /* [29]  */
        unsigned int    clpf_sel              : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF0;

/* Define the union U_DATE_COEFF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac_test              : 10  ; /* [9..0]  */
        unsigned int    date_test_mode        : 2   ; /* [11..10]  */
        unsigned int    date_test_en          : 1   ; /* [12]  */
        unsigned int    amp_outside           : 10  ; /* [22..13]  */
        unsigned int    c_limit_en            : 1   ; /* [23]  */
        unsigned int    cc_seq                : 1   ; /* [24]  */
        unsigned int    cgms_seq              : 1   ; /* [25]  */
        unsigned int    vps_seq               : 1   ; /* [26]  */
        unsigned int    wss_seq               : 1   ; /* [27]  */
        unsigned int    cvbs_limit_en         : 1   ; /* [28]  */
        unsigned int    c_gain                : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF1;

/* Define the union U_DATE_COEFF2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef02                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF2;
/* Define the union U_DATE_COEFF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef03                : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF3;

/* Define the union U_DATE_COEFF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef04                : 30  ; /* [29..0]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF4;

/* Define the union U_DATE_COEFF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef05                : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF5;

/* Define the union U_DATE_COEFF6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef06_1              : 23  ; /* [22..0]  */
        unsigned int    reserved_0            : 8   ; /* [30..23]  */
        unsigned int    coef06_0              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF6;

/* Define the union U_DATE_COEFF7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt07_enf2             : 1   ; /* [0]  */
        unsigned int    tt08_enf2             : 1   ; /* [1]  */
        unsigned int    tt09_enf2             : 1   ; /* [2]  */
        unsigned int    tt10_enf2             : 1   ; /* [3]  */
        unsigned int    tt11_enf2             : 1   ; /* [4]  */
        unsigned int    tt12_enf2             : 1   ; /* [5]  */
        unsigned int    tt13_enf2             : 1   ; /* [6]  */
        unsigned int    tt14_enf2             : 1   ; /* [7]  */
        unsigned int    tt15_enf2             : 1   ; /* [8]  */
        unsigned int    tt16_enf2             : 1   ; /* [9]  */
        unsigned int    tt17_enf2             : 1   ; /* [10]  */
        unsigned int    tt18_enf2             : 1   ; /* [11]  */
        unsigned int    tt19_enf2             : 1   ; /* [12]  */
        unsigned int    tt20_enf2             : 1   ; /* [13]  */
        unsigned int    tt21_enf2             : 1   ; /* [14]  */
        unsigned int    tt22_enf2             : 1   ; /* [15]  */
        unsigned int    tt07_enf1             : 1   ; /* [16]  */
        unsigned int    tt08_enf1             : 1   ; /* [17]  */
        unsigned int    tt09_enf1             : 1   ; /* [18]  */
        unsigned int    tt10_enf1             : 1   ; /* [19]  */
        unsigned int    tt11_enf1             : 1   ; /* [20]  */
        unsigned int    tt12_enf1             : 1   ; /* [21]  */
        unsigned int    tt13_enf1             : 1   ; /* [22]  */
        unsigned int    tt14_enf1             : 1   ; /* [23]  */
        unsigned int    tt15_enf1             : 1   ; /* [24]  */
        unsigned int    tt16_enf1             : 1   ; /* [25]  */
        unsigned int    tt17_enf1             : 1   ; /* [26]  */
        unsigned int    tt18_enf1             : 1   ; /* [27]  */
        unsigned int    tt19_enf1             : 1   ; /* [28]  */
        unsigned int    tt20_enf1             : 1   ; /* [29]  */
        unsigned int    tt21_enf1             : 1   ; /* [30]  */
        unsigned int    tt22_enf1             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF7;

/* Define the union U_DATE_COEFF8 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tt_staddr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF8;
/* Define the union U_DATE_COEFF9 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tt_edaddr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF9;
/* Define the union U_DATE_COEFF10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_pktoff             : 8   ; /* [7..0]  */
        unsigned int    tt_mode               : 2   ; /* [9..8]  */
        unsigned int    tt_highest            : 1   ; /* [10]  */
        unsigned int    full_page             : 1   ; /* [11]  */
        unsigned int    nabts_100ire          : 1   ; /* [12]  */
        unsigned int    reserved_0            : 18  ; /* [30..13]  */
        unsigned int    tt_ready              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF10;

/* Define the union U_DATE_COEFF11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    date_clf2             : 10  ; /* [9..0]  */
        unsigned int    date_clf1             : 10  ; /* [19..10]  */
        unsigned int    cc_enf2               : 1   ; /* [20]  */
        unsigned int    cc_enf1               : 1   ; /* [21]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF11;

/* Define the union U_DATE_COEFF12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cc_f2data             : 16  ; /* [15..0]  */
        unsigned int    cc_f1data             : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF12;

/* Define the union U_DATE_COEFF13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cg_f1data             : 20  ; /* [19..0]  */
        unsigned int    cg_enf2               : 1   ; /* [20]  */
        unsigned int    cg_enf1               : 1   ; /* [21]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF13;

/* Define the union U_DATE_COEFF14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cg_f2data             : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF14;

/* Define the union U_DATE_COEFF15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wss_data              : 14  ; /* [13..0]  */
        unsigned int    wss_en                : 1   ; /* [14]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF15;

/* Define the union U_DATE_COEFF16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vps_data              : 24  ; /* [23..0]  */
        unsigned int    vps_en                : 1   ; /* [24]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF16;

/* Define the union U_DATE_COEFF17 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vps_data               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF17;
/* Define the union U_DATE_COEFF18 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vps_data               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF18;
/* Define the union U_DATE_COEFF19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vps_data              : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF19;

/* Define the union U_DATE_COEFF20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt05_enf2             : 1   ; /* [0]  */
        unsigned int    tt06_enf2             : 1   ; /* [1]  */
        unsigned int    tt06_enf1             : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF20;

/* Define the union U_DATE_COEFF21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac0_in_sel           : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    dac1_in_sel           : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    dac2_in_sel           : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    dac3_in_sel           : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    dac4_in_sel           : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    dac5_in_sel           : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF21;

/* Define the union U_DATE_COEFF22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_phase_delta     : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF22;

/* Define the union U_DATE_COEFF23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac0_out_dly          : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    dac1_out_dly          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    dac2_out_dly          : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    dac3_out_dly          : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    dac4_out_dly          : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    dac5_out_dly          : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF23;

/* Define the union U_DATE_COEFF24 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int burst_start            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF24;
/* Define the union U_DATE_COEFF25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x_n_coef              : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    x_n_1_coef            : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF25;

/* Define the union U_DATE_COEFF26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x_n_1_coef            : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF26;

/* Define the union U_DATE_COEFF27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    y_n_coef              : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    y_n_1_coef            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF27;

/* Define the union U_DATE_COEFF28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pixel_begin1          : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    pixel_begin2          : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF28;

/* Define the union U_DATE_COEFF29 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pixel_end             : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF29;

/* Define the union U_DATE_COEFF30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_secam               : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF30;

/* Define the union U_DATE_ISRMASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_mask               : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_ISRMASK;

/* Define the union U_DATE_ISRSTATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_status             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_ISRSTATE;

/* Define the union U_DATE_ISR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_int                : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_ISR;

/* Define the union U_DATE_VERSION */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_VERSION;
/* Define the union U_DATE_COEFF37 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_y1_coeff0         : 8   ; /* [7..0]  */
        unsigned int    fir_y1_coeff1         : 8   ; /* [15..8]  */
        unsigned int    fir_y1_coeff2         : 8   ; /* [23..16]  */
        unsigned int    fir_y1_coeff3         : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF37;

/* Define the union U_DATE_COEFF38 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_y2_coeff0         : 16  ; /* [15..0]  */
        unsigned int    fir_y2_coeff1         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF38;

/* Define the union U_DATE_COEFF39 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_y2_coeff2         : 16  ; /* [15..0]  */
        unsigned int    fir_y2_coeff3         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF39;

/* Define the union U_DATE_COEFF40 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_c1_coeff0         : 8   ; /* [7..0]  */
        unsigned int    fir_c1_coeff1         : 8   ; /* [15..8]  */
        unsigned int    fir_c1_coeff2         : 8   ; /* [23..16]  */
        unsigned int    fir_c1_coeff3         : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF40;

/* Define the union U_DATE_COEFF41 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_c2_coeff0         : 16  ; /* [15..0]  */
        unsigned int    fir_c2_coeff1         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF41;

/* Define the union U_DATE_COEFF42 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_c2_coeff2         : 16  ; /* [15..0]  */
        unsigned int    fir_c2_coeff3         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF42;

/* Define the union U_DATE_DACDET1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdac_det_high         : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    det_line              : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_DACDET1;

/* Define the union U_DATE_DACDET2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    det_pixel_sta         : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    det_pixel_wid         : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 4   ; /* [30..27]  */
        unsigned int    vdac_det_en           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_DACDET2;

/* Define the union U_DATE_COEFF50 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF50;

/* Define the union U_DATE_COEFF51 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF51;

/* Define the union U_DATE_COEFF52 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF52;

/* Define the union U_DATE_COEFF53 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF53;

/* Define the union U_DATE_COEFF54 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF54;

/* Define the union U_DATE_COEFF55 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF55;


// Define the union U_DATE_COEFF56
typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    oversam2_round_en     : 1   ; // [0] 
        unsigned int    Reserved_700          : 31  ; // [31..1] 
    } bits;

    // Define an unsigned member
    unsigned int    u32;

} U_DATE_COEFF56;

// Define the union U_DATE_COEFF57
typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    v_gain                : 8   ; // [7..0] 
        unsigned int    u_gain                : 8   ; // [15..8] 
        unsigned int    ycvbs_gain            : 8   ; // [23..16] 
        unsigned int    Reserved_701          : 7   ; // [30..24] 
        unsigned int    cvbs_gain_en          : 1   ; // [31] 
    } bits;

    // Define an unsigned member
    unsigned int    u32;

} U_DATE_COEFF57;

// Define the union U_DATE_COEFF58
typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    pr_gain               : 8   ; // [7..0] 
        unsigned int    pb_gain               : 8   ; // [15..8] 
        unsigned int    ycomp_gain            : 8   ; // [23..16] 
        unsigned int    Reserved_702          : 7   ; // [30..24] 
        unsigned int    comp_gain_en          : 1   ; // [31] 
    } bits;

    // Define an unsigned member
    unsigned int    u32;

} U_DATE_COEFF58;

// Define the union U_DATE_COEFF59
typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    ynotch_clip_fullrange  : 1   ; // [0] 
        unsigned int    clpf_clip_fullrange   : 1   ; // [1] 
        unsigned int    Reserved_707          : 2   ; // [3..2] 
        unsigned int    y_os_clip_fullrange   : 1   ; // [4] 
        unsigned int    Reserved_706          : 3   ; // [7..5] 
        unsigned int    u_os_clip_fullrange   : 1   ; // [8] 
        unsigned int    v_os_clip_fullrange   : 1   ; // [9] 
        unsigned int    Reserved_705          : 2   ; // [11..10] 
        unsigned int    cb_os_clip_fullrange  : 1   ; // [12] 
        unsigned int    cr_os_clip_fullrange  : 1   ; // [13] 
        unsigned int    Reserved_704          : 2   ; // [15..14] 
        unsigned int    cb_gain_polar         : 1   ; // [16] 
        unsigned int    Reserved_703          : 15  ; // [31..17] 
    } bits;

    // Define an unsigned member
    unsigned int    u32;

} U_DATE_COEFF59;

/* Define the union U_LVDS_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 17  ; /* [16..0]  */
        unsigned int    resv_inv              : 1   ; /* [17]  */
        unsigned int    de_inv                : 1   ; /* [18]  */
        unsigned int    vsync_inv             : 1   ; /* [19]  */
        unsigned int    hsync_inv             : 1   ; /* [20]  */
        unsigned int    data_inv              : 1   ; /* [21]  */
        unsigned int    sync_out              : 1   ; /* [22]  */
        unsigned int    bit_sel               : 1   ; /* [23]  */
        unsigned int    lvds_map              : 2   ; /* [25..24]  */
        unsigned int    test_mode             : 3   ; /* [28..26]  */
        unsigned int    mode                  : 2   ; /* [30..29]  */
        unsigned int    lvds_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LVDS_CTRL;

/* Define the union U_LVDS_SWAP0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    comp_swap             : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 5   ; /* [7..3]  */
        unsigned int    ch0_swap              : 3   ; /* [10..8]  */
        unsigned int    ch1_swap              : 3   ; /* [13..11]  */
        unsigned int    ch2_swap              : 3   ; /* [16..14]  */
        unsigned int    ch3_swap              : 3   ; /* [19..17]  */
        unsigned int    ch4_swap              : 3   ; /* [22..20]  */
        unsigned int    reserved_1            : 1   ; /* [23]  */
        unsigned int    linka_swap            : 2   ; /* [25..24]  */
        unsigned int    linkb_swap            : 2   ; /* [27..26]  */
        unsigned int    linkc_swap            : 2   ; /* [29..28]  */
        unsigned int    linkd_swap            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LVDS_SWAP0;

/* Define the union U_LVDS_SWAP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bit2_swap             : 4   ; /* [3..0]  */
        unsigned int    bit3_swap             : 4   ; /* [7..4]  */
        unsigned int    bit4_swap             : 4   ; /* [11..8]  */
        unsigned int    bit5_swap             : 4   ; /* [15..12]  */
        unsigned int    bit6_swap             : 4   ; /* [19..16]  */
        unsigned int    bit7_swap             : 4   ; /* [23..20]  */
        unsigned int    bit8_swap             : 4   ; /* [27..24]  */
        unsigned int    bit9_swap             : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LVDS_SWAP1;

/* Define the union U_LVDS_SWAP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    bit0_swap             : 4   ; /* [27..24]  */
        unsigned int    bit1_swap             : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LVDS_SWAP2;

/* Define the union U_LVDS_PHYCTRL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 23  ; /* [22..0]  */
        unsigned int    emp                   : 2   ; /* [24..23]  */
        unsigned int    dual_single           : 1   ; /* [25]  */
        unsigned int    r_fb                  : 1   ; /* [26]  */
        unsigned int    sel8_10               : 1   ; /* [27]  */
        unsigned int    pon                   : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LVDS_PHYCTRL0;

/* Define the union U_LVDS_PHYCTRL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clkds4                : 3   ; /* [2..0]  */
        unsigned int    clkds3                : 3   ; /* [5..3]  */
        unsigned int    clkds2                : 3   ; /* [8..6]  */
        unsigned int    clkds1                : 3   ; /* [11..9]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    swing_ctl             : 3   ; /* [18..16]  */
        unsigned int    reserved_1            : 5   ; /* [23..19]  */
        unsigned int    offset_ctl            : 3   ; /* [26..24]  */
        unsigned int    reserved_2            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LVDS_PHYCTRL1;

/* Define the union U_LVDS_PHYCTRL2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_LVDS_PHYCTRL2;
/* Define the union U_LVDS_SPHYSTAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pll_lock              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LVDS_SPHYSTAT;

/* Define the union U_VBO_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 12  ; /* [11..0]  */
        unsigned int    vbo_bit_sel           : 1   ; /* [12]  */
        unsigned int    vbo_aln_mode          : 1   ; /* [13]  */
        unsigned int    vbo_test_mode         : 3   ; /* [16..14]  */
        unsigned int    vbo_test_en           : 1   ; /* [17]  */
        unsigned int    vbo_inter_swap1       : 1   ; /* [18]  */
        unsigned int    vbo_inter_swap0       : 1   ; /* [19]  */
        unsigned int    vbo_intra_swap        : 1   ; /* [20]  */
        unsigned int    vbo_byte_num          : 3   ; /* [23..21]  */
        unsigned int    vbo_lane_num          : 4   ; /* [27..24]  */
        unsigned int    vbo_data_mode         : 3   ; /* [30..28]  */
        unsigned int    vbo_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VBO_CTRL;

/* Define the union U_VBO_PHYCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 11  ; /* [10..0]  */
        unsigned int    vbo_test_pll_clk      : 1   ; /* [11]  */
        unsigned int    vbo_div_trim          : 1   ; /* [12]  */
        unsigned int    vbo_lpf_r_trim        : 2   ; /* [14..13]  */
        unsigned int    vbo_rt                : 2   ; /* [16..15]  */
        unsigned int    vbo_cp_trim           : 2   ; /* [18..17]  */
        unsigned int    vbo_dcc_ctl           : 4   ; /* [22..19]  */
        unsigned int    vbo_rfb               : 1   ; /* [23]  */
        unsigned int    vbo_emp               : 2   ; /* [25..24]  */
        unsigned int    vbo_swing_ctl         : 3   ; /* [28..26]  */
        unsigned int    vbo_pon               : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VBO_PHYCTRL;

/* Define the union U_VBO_PHYSTAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbo_pll_lock          : 1   ; /* [0]  */
        unsigned int    vbo_lockn             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VBO_PHYSTAT;

/* Define the union U_PWM_CONTROL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dimming_pwm_en        : 1   ; /* [0]  */
        unsigned int    dimming_vsync_rise    : 1   ; /* [1]  */
        unsigned int    dimming_3d_sg         : 1   ; /* [2]  */
        unsigned int    dimming_pwm_inv       : 1   ; /* [3]  */
        unsigned int    dimming_duty_sel      : 1   ; /* [4]  */
        unsigned int    sync_vsync            : 1   ; /* [5]  */
        unsigned int    sync_whole            : 1   ; /* [6]  */
        unsigned int    reserved_0            : 17  ; /* [23..7]  */
        unsigned int    refresh_cmd           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_CONTROL;

/* Define the union U_DIMMING_PWM_DUTY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dimming_pwm_duty      : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIMMING_PWM_DUTY;

/* Define the union U_PWM_FREQ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pwm_freq              : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_FREQ;

/* Define the union U_PWM_M */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pwm_m                 : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_M;

/* Define the union U_PWM_P */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pwm_p                 : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_P;

/* Define the union U_PWM_Q */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pwm_q                 : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_Q;

/* Define the union U_LR_SYNC_CONTROL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lr_sync_en            : 1   ; /* [0]  */
        unsigned int    lr_sync_rise          : 1   ; /* [1]  */
        unsigned int    lr_sync_int           : 1   ; /* [2]  */
        unsigned int    lr_sync_inv           : 1   ; /* [3]  */
        unsigned int    reserved_0            : 20  ; /* [23..4]  */
        unsigned int    refresh_cmd           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LR_SYNC_CONTROL;

/* Define the union U_LR_SYNC_M */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lr_sync_m             : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LR_SYNC_M;

/* Define the union U_LR_GLASS_CONTROL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lr_glass_en           : 1   ; /* [0]  */
        unsigned int    lr_glass_sel          : 1   ; /* [1]  */
        unsigned int    lr_glass_int          : 1   ; /* [2]  */
        unsigned int    lr_glass_inv          : 1   ; /* [3]  */
        unsigned int    reserved_0            : 20  ; /* [23..4]  */
        unsigned int    refresh_cmd           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LR_GLASS_CONTROL;

/* Define the union U_LR_GLASS_M */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lr_glass_m            : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LR_GLASS_M;

/* Define the union U_PWM_1D1CONTROL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dimming_pwm_1d1_en    : 1   ; /* [0]  */
        unsigned int    dimming_vsync_rise    : 1   ; /* [1]  */
        unsigned int    dimming_3d_sg         : 1   ; /* [2]  */
        unsigned int    dimming_pwm_1d1_inv   : 1   ; /* [3]  */
        unsigned int    dimming_duty_sel      : 1   ; /* [4]  */
        unsigned int    sync_vsync            : 1   ; /* [5]  */
        unsigned int    sync_whole            : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_1D1CONTROL;

/* Define the union U_DIMMING_PWM_1D1_DUTY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dimming_pwm_1d1_duty  : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIMMING_PWM_1D1_DUTY;

/* Define the union U_PWM_1D1_FREQ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pwm_1d1_freq          : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_1D1_FREQ;

/* Define the union U_PWM_1D2CONTROL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dimming_pwm_1d2_en    : 1   ; /* [0]  */
        unsigned int    dimming_vsync_rise    : 1   ; /* [1]  */
        unsigned int    dimming_3d_sg         : 1   ; /* [2]  */
        unsigned int    dimming_pwm_1d2_inv   : 1   ; /* [3]  */
        unsigned int    dimming_duty_sel      : 1   ; /* [4]  */
        unsigned int    sync_vsync            : 1   ; /* [5]  */
        unsigned int    sync_whole            : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_1D2CONTROL;

/* Define the union U_DIMMING_PWM_1D2_DUTY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dimming_pwm_1d2_duty  : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIMMING_PWM_1D2_DUTY;

/* Define the union U_PWM_1D2_FREQ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pwm_1d2_freq          : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_1D2_FREQ;

/* Define the union U_PWM_1D3CONTROL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dimming_pwm_1d3_en    : 1   ; /* [0]  */
        unsigned int    dimming_vsync_rise    : 1   ; /* [1]  */
        unsigned int    dimming_3d_sg         : 1   ; /* [2]  */
        unsigned int    dimming_pwm_1d3_inv   : 1   ; /* [3]  */
        unsigned int    dimming_duty_sel      : 1   ; /* [4]  */
        unsigned int    sync_vsync            : 1   ; /* [5]  */
        unsigned int    sync_whole            : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_1D3CONTROL;

/* Define the union U_DIMMING_PWM_1D3_DUTY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dimming_pwm_1d3_duty  : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DIMMING_PWM_1D3_DUTY;

/* Define the union U_PWM_1D3_FREQ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pwm_1d3_freq          : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PWM_1D3_FREQ;

//==============================================================================
/* Define the global struct */
typedef struct
{
    U_VOCTRL               VOCTRL                            ; /* 0x0 */
    U_VOINTSTA             VOINTSTA                          ; /* 0x4 */
    U_VOMSKINTSTA          VOMSKINTSTA                       ; /* 0x8 */
    U_VOINTMSK             VOINTMSK                          ; /* 0xc */
    U_VODEBUG              VODEBUG                           ; /* 0x10 */
    U_VOINTSTA_OFL         VOINTSTA_OFL                      ; /* 0x14 */
    U_VOMSKINTSTA_OFL      VOMSKINTSTA_OFL                   ; /* 0x18 */
    U_VOINTMSK_OFL         VOINTMSK_OFL                      ; /* 0x1c */
    U_VDPVERSION1          VDPVERSION1                       ; /* 0x20 */
    U_VDPVERSION2          VDPVERSION2                       ; /* 0x24 */
    unsigned int           reserved_0[2]                     ; /* 0x28~0x2c */
    U_VOAXICTRL            VOAXICTRL                         ; /* 0x30 */
    U_VOAXICTRL1           VOAXICTRL1                        ; /* 0x34 */
    U_VOMASTERSEL          VOMASTERSEL                       ; /* 0x38 */
    U_VOMASTERSEL1         VOMASTERSEL1                      ; /* 0x3c */
    U_VOWBCARB0            VOWBCARB0                         ; /* 0x40 */
    U_VOWBCARB1            VOWBCARB1                         ; /* 0x44 */
    U_VOWBCARB2            VOWBCARB2                         ; /* 0x48 */
    U_VOWBCARB3            VOWBCARB3                         ; /* 0x4c */
    U_VOUFSTA              VOUFSTA                           ; /* 0x50 */
    U_VOUFCLR              VOUFCLR                           ; /* 0x54 */
    U_VOULTCSTA            VOULTCSTA                         ; /* 0x58 */
    U_VOULTCCLR            VOULTCCLR                         ; /* 0x5c */
    U_VOINTPROC_TIM        VOINTPROC_TIM                     ; /* 0x60 */
    unsigned int           reserved_1[39]                     ; /* 0x64~0xfc */
    U_VO_MUX               VO_MUX                            ; /* 0x100 */
    U_VO_MUX_DAC           VO_MUX_DAC                        ; /* 0x104 */
    unsigned int           reserved_2[6]                     ; /* 0x108~0x11c */
    U_VO_DAC_CTRL0         VO_DAC_CTRL0                      ; /* 0x120 */
    unsigned int           reserved_3[3]                     ; /* 0x124~0x12c */
    U_VO_DAC_C_CTRL        VO_DAC_C_CTRL                     ; /* 0x130 */
    U_VO_DAC_R_CTRL        VO_DAC_R_CTRL                     ; /* 0x134 */
    U_VO_DAC_G_CTRL        VO_DAC_G_CTRL                     ; /* 0x138 */
    U_VO_DAC_B_CTRL        VO_DAC_B_CTRL                     ; /* 0x13c */
    unsigned int           reserved_4[4]                     ; /* 0x140~0x14c */
    U_VO_DAC_CTRL          VO_DAC_CTRL                       ; /* 0x150 */
    unsigned int           reserved_5[107]                     ; /* 0x154~0x2fc */
    U_WBC_DHD_LOCATE       WBC_DHD_LOCATE                    ; /* 0x300 */
    U_WBC_OFL_EN           WBC_OFL_EN                        ; /* 0x304 */
    U_WBC_OFL_RESO         WBC_OFL_RESO                      ; /* 0x308 */
    unsigned int           reserved_6[13]                     ; /* 0x30c~0x33c */
    U_IPTIMING             IPTIMING                          ; /* 0x340 */
    U_IPSEL                IPSEL                             ; /* 0x344 */
    unsigned int           reserved_7[46]                     ; /* 0x348~0x3fc */
    U_COEF_DATA            COEF_DATA                         ; /* 0x400 */
    unsigned int           reserved_8[3]                     ; /* 0x404~0x40c */
    U_V0_PARARD            V0_PARARD                         ; /* 0x410 */
    U_V1_PARARD            V1_PARARD                         ; /* 0x414 */
    unsigned int           reserved_9                     ; /* 0x418 */
    U_V3_PARARD            V3_PARARD                         ; /* 0x41c */
    U_V4_PARARD            V4_PARARD                         ; /* 0x420 */
    unsigned int           reserved_10[7]                     ; /* 0x424~0x43c */
    U_VP0_PARARD           VP0_PARARD                        ; /* 0x440 */
    unsigned int           reserved_11[19]                     ; /* 0x444~0x48c */
    U_GP0_PARARD           GP0_PARARD                        ; /* 0x490 */
    U_GP1_PARARD           GP1_PARARD                        ; /* 0x494 */
    unsigned int           reserved_12[10]                     ; /* 0x498~0x4bc */
    U_WBC_PARARD           WBC_PARARD                        ; /* 0x4c0 */
    unsigned int           reserved_13[11]                     ; /* 0x4c4~0x4ec */
    U_DHD0_PARARD          DHD0_PARARD                       ; /* 0x4f0 */
    U_DHD1_PARARD          DHD1_PARARD                       ; /* 0x4f4 */
    unsigned int           reserved_14[194]                     ; /* 0x4f8~0x7fc */
    U_V0_CTRL              V0_CTRL                           ; /* 0x800 */
    U_V0_UPD               V0_UPD                            ; /* 0x804 */
    unsigned int           reserved_15[6]                     ; /* 0x808~0x81c */
    U_V0_PRERD             V0_PRERD                          ; /* 0x820 */
    U_V0_FI_IRESO          V0_FI_IRESO                       ; /* 0x824 */
    U_V0_IRESO             V0_IRESO                          ; /* 0x828 */
    U_V0_ORESO             V0_ORESO                          ; /* 0x82c */
    U_V0_FI_REQW_0         V0_FI_REQW_0                      ; /* 0x830 */
    U_V0_FI_REQW_1         V0_FI_REQW_1                      ; /* 0x834 */
    U_V0_CBMPARA           V0_CBMPARA                        ; /* 0x838 */
    U_V0_SRORESO           V0_SRORESO                        ; /* 0x83c */
    U_V0_PARAUP            V0_PARAUP                         ; /* 0x840 */
    U_V0_CPOS              V0_CPOS                           ; /* 0x844 */
    U_V0_DRAWMODE          V0_DRAWMODE                       ; /* 0x848 */
    unsigned int           reserved_16                     ; /* 0x84c */
    U_V0_HLCOEFAD          V0_HLCOEFAD                       ; /* 0x850 */
    U_V0_HCCOEFAD          V0_HCCOEFAD                       ; /* 0x854 */
    U_V0_VLCOEFAD          V0_VLCOEFAD                       ; /* 0x858 */
    U_V0_VCCOEFAD          V0_VCCOEFAD                       ; /* 0x85c */
    U_V0_DFPOS             V0_DFPOS                          ; /* 0x860 */
    U_V0_DLPOS             V0_DLPOS                          ; /* 0x864 */
    U_V0_VFPOS             V0_VFPOS                          ; /* 0x868 */
    U_V0_VLPOS             V0_VLPOS                          ; /* 0x86c */
    U_V0_BK                V0_BK                             ; /* 0x870 */
    U_V0_ALPHA             V0_ALPHA                          ; /* 0x874 */
    U_V0_MUTE_BK           V0_MUTE_BK                        ; /* 0x878 */
    unsigned int           reserved_17                     ; /* 0x87c */
    U_V0_CSC_IDC           V0_CSC_IDC                        ; /* 0x880 */
    U_V0_CSC_ODC           V0_CSC_ODC                        ; /* 0x884 */
    U_V0_CSC_IODC          V0_CSC_IODC                       ; /* 0x888 */
    U_V0_CSC_P0            V0_CSC_P0                         ; /* 0x88c */
    U_V0_CSC_P1            V0_CSC_P1                         ; /* 0x890 */
    U_V0_CSC_P2            V0_CSC_P2                         ; /* 0x894 */
    U_V0_CSC_P3            V0_CSC_P3                         ; /* 0x898 */
    U_V0_CSC_P4            V0_CSC_P4                         ; /* 0x89c */
    unsigned int           reserved_18[8]                     ; /* 0x8a0~0x8bc */
    U_V0_HSP               V0_HSP                            ; /* 0x8c0 */
    U_V0_HLOFFSET          V0_HLOFFSET                       ; /* 0x8c4 */
    U_V0_HCOFFSET          V0_HCOFFSET                       ; /* 0x8c8 */
    U_V0_HZONE0DELTA       V0_HZONE0DELTA                    ; /* 0x8cc */
    U_V0_HZONE2DELTA       V0_HZONE2DELTA                    ; /* 0x8d0 */
    U_V0_HZONEEND          V0_HZONEEND                       ; /* 0x8d4 */
    U_V0_VSP               V0_VSP                            ; /* 0x8d8 */
    U_V0_VSR               V0_VSR                            ; /* 0x8dc */
    U_V0_VOFFSET           V0_VOFFSET                        ; /* 0x8e0 */
    U_V0_VBOFFSET          V0_VBOFFSET                       ; /* 0x8e4 */
    unsigned int           reserved_19[2]                     ; /* 0x8e8~0x8ec */
    U_V0_ZMECOEF           V0_ZMECOEF                        ; /* 0x8f0 */
    U_V0_ZMECOEFAD         V0_ZMECOEFAD                      ; /* 0x8f4 */
    unsigned int           reserved_20[34]                     ; /* 0x8f8~0x97c */
    U_V0_IFIRCOEF01        V0_IFIRCOEF01                     ; /* 0x980 */
    U_V0_IFIRCOEF23        V0_IFIRCOEF23                     ; /* 0x984 */
    U_V0_IFIRCOEF45        V0_IFIRCOEF45                     ; /* 0x988 */
    U_V0_IFIRCOEF67        V0_IFIRCOEF67                     ; /* 0x98c */
    unsigned int           reserved_21[28]                     ; /* 0x990~0x9fc */
    U_V0_P0RESO            V0_P0RESO                         ; /* 0xa00 */
    U_V0_P0LADDR           V0_P0LADDR                        ; /* 0xa04 */
    U_V0_P0CADDR           V0_P0CADDR                        ; /* 0xa08 */
    U_V0_P0STRIDE          V0_P0STRIDE                       ; /* 0xa0c */
    U_V0_P0VFPOS           V0_P0VFPOS                        ; /* 0xa10 */
    U_V0_P0VLPOS           V0_P0VLPOS                        ; /* 0xa14 */
    unsigned int           reserved_22[2]                     ; /* 0xa18~0xa1c */
    U_V0_P1RESO            V0_P1RESO                         ; /* 0xa20 */
    U_V0_P1LADDR           V0_P1LADDR                        ; /* 0xa24 */
    U_V0_P1CADDR           V0_P1CADDR                        ; /* 0xa28 */
    U_V0_P1STRIDE          V0_P1STRIDE                       ; /* 0xa2c */
    U_V0_P1VFPOS           V0_P1VFPOS                        ; /* 0xa30 */
    U_V0_P1VLPOS           V0_P1VLPOS                        ; /* 0xa34 */
    unsigned int           reserved_23[2]                     ; /* 0xa38~0xa3c */
    U_V0_P2RESO            V0_P2RESO                         ; /* 0xa40 */
    U_V0_P2LADDR           V0_P2LADDR                        ; /* 0xa44 */
    U_V0_P2CADDR           V0_P2CADDR                        ; /* 0xa48 */
    U_V0_P2STRIDE          V0_P2STRIDE                       ; /* 0xa4c */
    U_V0_P2VFPOS           V0_P2VFPOS                        ; /* 0xa50 */
    U_V0_P2VLPOS           V0_P2VLPOS                        ; /* 0xa54 */
    unsigned int           reserved_24[2]                     ; /* 0xa58~0xa5c */
    U_V0_P3RESO            V0_P3RESO                         ; /* 0xa60 */
    U_V0_P3LADDR           V0_P3LADDR                        ; /* 0xa64 */
    U_V0_P3CADDR           V0_P3CADDR                        ; /* 0xa68 */
    U_V0_P3STRIDE          V0_P3STRIDE                       ; /* 0xa6c */
    U_V0_P3VFPOS           V0_P3VFPOS                        ; /* 0xa70 */
    U_V0_P3VLPOS           V0_P3VLPOS                        ; /* 0xa74 */
    unsigned int           reserved_25[2]                     ; /* 0xa78~0xa7c */
    U_V0_P4RESO            V0_P4RESO                         ; /* 0xa80 */
    U_V0_P4LADDR           V0_P4LADDR                        ; /* 0xa84 */
    U_V0_P4CADDR           V0_P4CADDR                        ; /* 0xa88 */
    U_V0_P4STRIDE          V0_P4STRIDE                       ; /* 0xa8c */
    U_V0_P4VFPOS           V0_P4VFPOS                        ; /* 0xa90 */
    U_V0_P4VLPOS           V0_P4VLPOS                        ; /* 0xa94 */
    unsigned int           reserved_26[2]                     ; /* 0xa98~0xa9c */
    U_V0_P5RESO            V0_P5RESO                         ; /* 0xaa0 */
    U_V0_P5LADDR           V0_P5LADDR                        ; /* 0xaa4 */
    U_V0_P5CADDR           V0_P5CADDR                        ; /* 0xaa8 */
    U_V0_P5STRIDE          V0_P5STRIDE                       ; /* 0xaac */
    U_V0_P5VFPOS           V0_P5VFPOS                        ; /* 0xab0 */
    U_V0_P5VLPOS           V0_P5VLPOS                        ; /* 0xab4 */
    unsigned int           reserved_27[2]                     ; /* 0xab8~0xabc */
    U_V0_P6RESO            V0_P6RESO                         ; /* 0xac0 */
    U_V0_P6LADDR           V0_P6LADDR                        ; /* 0xac4 */
    U_V0_P6CADDR           V0_P6CADDR                        ; /* 0xac8 */
    U_V0_P6STRIDE          V0_P6STRIDE                       ; /* 0xacc */
    U_V0_P6VFPOS           V0_P6VFPOS                        ; /* 0xad0 */
    U_V0_P6VLPOS           V0_P6VLPOS                        ; /* 0xad4 */
    unsigned int           reserved_28[2]                     ; /* 0xad8~0xadc */
    U_V0_P7RESO            V0_P7RESO                         ; /* 0xae0 */
    U_V0_P7LADDR           V0_P7LADDR                        ; /* 0xae4 */
    U_V0_P7CADDR           V0_P7CADDR                        ; /* 0xae8 */
    U_V0_P7STRIDE          V0_P7STRIDE                       ; /* 0xaec */
    U_V0_P7VFPOS           V0_P7VFPOS                        ; /* 0xaf0 */
    U_V0_P7VLPOS           V0_P7VLPOS                        ; /* 0xaf4 */
    unsigned int           reserved_29[2]                     ; /* 0xaf8~0xafc */
    U_V0_P8RESO            V0_P8RESO                         ; /* 0xb00 */
    U_V0_P8LADDR           V0_P8LADDR                        ; /* 0xb04 */
    U_V0_P8CADDR           V0_P8CADDR                        ; /* 0xb08 */
    U_V0_P8STRIDE          V0_P8STRIDE                       ; /* 0xb0c */
    U_V0_P8VFPOS           V0_P8VFPOS                        ; /* 0xb10 */
    U_V0_P8VLPOS           V0_P8VLPOS                        ; /* 0xb14 */
    unsigned int           reserved_30[2]                     ; /* 0xb18~0xb1c */
    U_V0_P9RESO            V0_P9RESO                         ; /* 0xb20 */
    U_V0_P9LADDR           V0_P9LADDR                        ; /* 0xb24 */
    U_V0_P9CADDR           V0_P9CADDR                        ; /* 0xb28 */
    U_V0_P9STRIDE          V0_P9STRIDE                       ; /* 0xb2c */
    U_V0_P9VFPOS           V0_P9VFPOS                        ; /* 0xb30 */
    U_V0_P9VLPOS           V0_P9VLPOS                        ; /* 0xb34 */
    unsigned int           reserved_31[2]                     ; /* 0xb38~0xb3c */
    U_V0_P10RESO           V0_P10RESO                        ; /* 0xb40 */
    U_V0_P10LADDR          V0_P10LADDR                       ; /* 0xb44 */
    U_V0_P10CADDR          V0_P10CADDR                       ; /* 0xb48 */
    U_V0_P10STRIDE         V0_P10STRIDE                      ; /* 0xb4c */
    U_V0_P10VFPOS          V0_P10VFPOS                       ; /* 0xb50 */
    U_V0_P10VLPOS          V0_P10VLPOS                       ; /* 0xb54 */
    unsigned int           reserved_32[2]                     ; /* 0xb58~0xb5c */
    U_V0_P11RESO           V0_P11RESO                        ; /* 0xb60 */
    U_V0_P11LADDR          V0_P11LADDR                       ; /* 0xb64 */
    U_V0_P11CADDR          V0_P11CADDR                       ; /* 0xb68 */
    U_V0_P11STRIDE         V0_P11STRIDE                      ; /* 0xb6c */
    U_V0_P11VFPOS          V0_P11VFPOS                       ; /* 0xb70 */
    U_V0_P11VLPOS          V0_P11VLPOS                       ; /* 0xb74 */
    unsigned int           reserved_33[2]                     ; /* 0xb78~0xb7c */
    U_V0_P12RESO           V0_P12RESO                        ; /* 0xb80 */
    U_V0_P12LADDR          V0_P12LADDR                       ; /* 0xb84 */
    U_V0_P12CADDR          V0_P12CADDR                       ; /* 0xb88 */
    U_V0_P12STRIDE         V0_P12STRIDE                      ; /* 0xb8c */
    U_V0_P12VFPOS          V0_P12VFPOS                       ; /* 0xb90 */
    U_V0_P12VLPOS          V0_P12VLPOS                       ; /* 0xb94 */
    unsigned int           reserved_34[2]                     ; /* 0xb98~0xb9c */
    U_V0_P13RESO           V0_P13RESO                        ; /* 0xba0 */
    U_V0_P13LADDR          V0_P13LADDR                       ; /* 0xba4 */
    U_V0_P13CADDR          V0_P13CADDR                       ; /* 0xba8 */
    U_V0_P13STRIDE         V0_P13STRIDE                      ; /* 0xbac */
    U_V0_P13VFPOS          V0_P13VFPOS                       ; /* 0xbb0 */
    U_V0_P13VLPOS          V0_P13VLPOS                       ; /* 0xbb4 */
    unsigned int           reserved_35[2]                     ; /* 0xbb8~0xbbc */
    U_V0_P14RESO           V0_P14RESO                        ; /* 0xbc0 */
    U_V0_P14LADDR          V0_P14LADDR                       ; /* 0xbc4 */
    U_V0_P14CADDR          V0_P14CADDR                       ; /* 0xbc8 */
    U_V0_P14STRIDE         V0_P14STRIDE                      ; /* 0xbcc */
    U_V0_P14VFPOS          V0_P14VFPOS                       ; /* 0xbd0 */
    U_V0_P14VLPOS          V0_P14VLPOS                       ; /* 0xbd4 */
    unsigned int           reserved_36[2]                     ; /* 0xbd8~0xbdc */
    U_V0_P15RESO           V0_P15RESO                        ; /* 0xbe0 */
    U_V0_P15LADDR          V0_P15LADDR                       ; /* 0xbe4 */
    U_V0_P15CADDR          V0_P15CADDR                       ; /* 0xbe8 */
    U_V0_P15STRIDE         V0_P15STRIDE                      ; /* 0xbec */
    U_V0_P15VFPOS          V0_P15VFPOS                       ; /* 0xbf0 */
    U_V0_P15VLPOS          V0_P15VLPOS                       ; /* 0xbf4 */
    unsigned int           reserved_37[130]                     ; /* 0xbf8~0xdfc */
    U_V0_NADDR             V0_NADDR                          ; /* 0xe00 */
    U_V0_NCADDR            V0_NCADDR                         ; /* 0xe04 */
    U_V0_TILE_STRIDE       V0_TILE_STRIDE                    ; /* 0xe08 */
    unsigned int           reserved_38[9]                     ; /* 0xe0c~0xe2c */
    U_V0_MULTI_MODE        V0_MULTI_MODE                     ; /* 0xe30 */
    unsigned int           reserved_39[3]                     ; /* 0xe34~0xe3c */
    U_V0_LADDROFFSET       V0_LADDROFFSET                    ; /* 0xe40 */
    U_V0_CADDROFFSET       V0_CADDROFFSET                    ; /* 0xe44 */
    U_V0_TILE_LOFFSET      V0_TILE_LOFFSET                   ; /* 0xe48 */
    U_V0_TILE_COFFSET      V0_TILE_COFFSET                   ; /* 0xe4c */
    unsigned int           reserved_40[44]                     ; /* 0xe50~0xefc */
    U_V0_16REGIONENL       V0_16REGIONENL                    ; /* 0xf00 */
    unsigned int           reserved_41                     ; /* 0xf04 */
    U_V0_16MUTE            V0_16MUTE                         ; /* 0xf08 */
    unsigned int           reserved_42                     ; /* 0xf0c */
    U_V0_DCMP_CTRL         V0_DCMP_CTRL                      ; /* 0xf10 */
    unsigned int           reserved_43[3]                     ; /* 0xf14~0xf1c */
    U_V0_DCMP_LSTATE0      V0_DCMP_LSTATE0                   ; /* 0xf20 */
    U_V0_DCMP_LSTATE1      V0_DCMP_LSTATE1                   ; /* 0xf24 */
    U_V0_DCMP_CSTATE0      V0_DCMP_CSTATE0                   ; /* 0xf28 */
    U_V0_DCMP_CSTATE1      V0_DCMP_CSTATE1                   ; /* 0xf2c */
    U_V0_DCMPERRCLR        V0_DCMPERRCLR                     ; /* 0xf30 */
    U_V0_DCMP_ERR          V0_DCMP_ERR                       ; /* 0xf34 */
    unsigned int           reserved_44[2]                     ; /* 0xf38~0xf3c */
    U_ES_MODE              ES_MODE                           ; /* 0xf40 */
    U_ES_DIR_RATIO_0       ES_DIR_RATIO_0                    ; /* 0xf44 */
    U_ES_DIR_RATIO_1       ES_DIR_RATIO_1                    ; /* 0xf48 */
    U_ES_NORMALIZED_SCALE_0   ES_NORMALIZED_SCALE_0          ; /* 0xf4c */
    U_ES_NORMALIZED_SCALE_1   ES_NORMALIZED_SCALE_1          ; /* 0xf50 */
    U_ES_BC1_CFG           ES_BC1_CFG                        ; /* 0xf54 */
    U_ES_BC2_CFG           ES_BC2_CFG                        ; /* 0xf58 */
    U_ES_BC_CFG            ES_BC_CFG                         ; /* 0xf5c */
    U_ES_RATIO_LIMIT_SCALE   ES_RATIO_LIMIT_SCALE            ; /* 0xf60 */
    U_ES_VER_MIN_STRENGTH   ES_VER_MIN_STRENGTH              ; /* 0xf64 */
    U_ES_EDGE_SMOOTH_GAIN   ES_EDGE_SMOOTH_GAIN              ; /* 0xf68 */
    U_ES_EDGE_THD          ES_EDGE_THD                       ; /* 0xf6c */
    U_ES_EDGE_SMOOTH_RATIO_0   ES_EDGE_SMOOTH_RATIO_0        ; /* 0xf70 */
    U_ES_EDGE_SMOOTH_RATIO_1   ES_EDGE_SMOOTH_RATIO_1        ; /* 0xf74 */
    U_ES_EDGE_SLOPE_0      ES_EDGE_SLOPE_0                   ; /* 0xf78 */
    U_ES_EDGE_SLOPE_1      ES_EDGE_SLOPE_1                   ; /* 0xf7c */
    U_ES_EDGE_SLOPE_2      ES_EDGE_SLOPE_2                   ; /* 0xf80 */
    U_ES_STATUS_0          ES_STATUS_0                       ; /* 0xf84 */
    U_ES_STATUS_1          ES_STATUS_1                       ; /* 0xf88 */
    U_ES_STATUS_2          ES_STATUS_2                       ; /* 0xf8c */
    unsigned int           reserved_45[5148]                     ; /* 0xf90~0x5ffc */
    U_VP0_CTRL             VP0_CTRL                          ; /* 0x6000 */
    U_VP0_UPD              VP0_UPD                           ; /* 0x6004 */
    U_VP0_IRESO            VP0_IRESO                         ; /* 0x6008 */
    unsigned int           reserved_46                     ; /* 0x600c */
    U_VP0_DCI_CAD          VP0_DCI_CAD                       ; /* 0x6010 */
    U_VP0_ACM_CAD          VP0_ACM_CAD                       ; /* 0x6014 */
    U_VP0_SHARP_CAD        VP0_SHARP_CAD                     ; /* 0x6018 */
    U_VP0_PARAUP           VP0_PARAUP                        ; /* 0x601c */
    U_VP0_GALPHA           VP0_GALPHA                        ; /* 0x6020 */
    unsigned int           reserved_47[7]                     ; /* 0x6024~0x603c */
    U_VP0_DFPOS            VP0_DFPOS                         ; /* 0x6040 */
    U_VP0_DLPOS            VP0_DLPOS                         ; /* 0x6044 */
    U_VP0_VFPOS            VP0_VFPOS                         ; /* 0x6048 */
    U_VP0_VLPOS            VP0_VLPOS                         ; /* 0x604c */
    U_VP0_BK               VP0_BK                            ; /* 0x6050 */
    U_VP0_ALPHA            VP0_ALPHA                         ; /* 0x6054 */
    U_VP0_MUTE_BK          VP0_MUTE_BK                       ; /* 0x6058 */
    unsigned int           reserved_48[9]                     ; /* 0x605c~0x607c */
    U_VP0_DOF_CTRL         VP0_DOF_CTRL                      ; /* 0x6080 */
    U_VP0_DOF_STEP         VP0_DOF_STEP                      ; /* 0x6084 */
    U_VP0_DOF_BKG          VP0_DOF_BKG                       ; /* 0x6088 */
    unsigned int           reserved_49[5]                     ; /* 0x608c~0x609c */
    U_VP0_CSC_IDC          VP0_CSC_IDC                       ; /* 0x60a0 */
    U_VP0_CSC_ODC          VP0_CSC_ODC                       ; /* 0x60a4 */
    U_VP0_CSC_IODC         VP0_CSC_IODC                      ; /* 0x60a8 */
    U_VP0_CSC_P0           VP0_CSC_P0                        ; /* 0x60ac */
    U_VP0_CSC_P1           VP0_CSC_P1                        ; /* 0x60b0 */
    U_VP0_CSC_P2           VP0_CSC_P2                        ; /* 0x60b4 */
    U_VP0_CSC_P3           VP0_CSC_P3                        ; /* 0x60b8 */
    U_VP0_CSC_P4           VP0_CSC_P4                        ; /* 0x60bc */
    U_VPWCG_NON2LCTRL      VPWCG_NON2LCTRL                   ; /* 0x60c0 */
    U_VPWCG_NON2LCOEF0     VPWCG_NON2LCOEF0                  ; /* 0x60c4 */
    U_VPWCG_NON2LCOEF1     VPWCG_NON2LCOEF1                  ; /* 0x60c8 */
    U_VPWCG_NON2LCOEF2     VPWCG_NON2LCOEF2                  ; /* 0x60cc */
    U_VPWCG_CSC2CTRL       VPWCG_CSC2CTRL                    ; /* 0x60d0 */
    U_VPWCG_CSC2COEF0      VPWCG_CSC2COEF0                   ; /* 0x60d4 */
    U_VPWCG_CSC2COEF1      VPWCG_CSC2COEF1                   ; /* 0x60d8 */
    U_VPWCG_CSC2COEF2      VPWCG_CSC2COEF2                   ; /* 0x60dc */
    U_VPWCG_CSC2COEF3      VPWCG_CSC2COEF3                   ; /* 0x60e0 */
    U_VPWCG_L2NONTHD       VPWCG_L2NONTHD                    ; /* 0x60e4 */
    U_VPWCG_L2NONCOEF0     VPWCG_L2NONCOEF0                  ; /* 0x60e8 */
    U_VPWCG_L2NONCOEF1     VPWCG_L2NONCOEF1                  ; /* 0x60ec */
    U_VPWCG_L2NONCOEF2     VPWCG_L2NONCOEF2                  ; /* 0x60f0 */
    unsigned int           reserved_50[3]                     ; /* 0x60f4~0x60fc */
    U_VP0_DCICTRL          VP0_DCICTRL                       ; /* 0x6100 */
    U_VP0_DCIHPOS          VP0_DCIHPOS                       ; /* 0x6104 */
    U_VP0_DCIVPOS          VP0_DCIVPOS                       ; /* 0x6108 */
    U_VP0_DCIHISBLD        VP0_DCIHISBLD                     ; /* 0x610c */
    U_VP0_DCIHISOFT        VP0_DCIHISOFT                     ; /* 0x6110 */
    U_VP0_DCIHISCOR        VP0_DCIHISCOR                     ; /* 0x6114 */
    U_VP0_DCIMERBLD        VP0_DCIMERBLD                     ; /* 0x6118 */
    U_VP0_DCIADJWGT        VP0_DCIADJWGT                     ; /* 0x611c */
    U_VP0_DCICLIP0         VP0_DCICLIP0                      ; /* 0x6120 */
    U_VP0_DCICLIP1         VP0_DCICLIP1                      ; /* 0x6124 */
    U_VP0_DCICLIP2         VP0_DCICLIP2                      ; /* 0x6128 */
    U_VP0_DCIGLBGAIN       VP0_DCIGLBGAIN                    ; /* 0x612c */
    U_VP0_DCIPOSTHR0       VP0_DCIPOSTHR0                    ; /* 0x6130 */
    U_VP0_DCIPOSTHR1       VP0_DCIPOSTHR1                    ; /* 0x6134 */
    U_VP0_DCIPOSGAIN0      VP0_DCIPOSGAIN0                   ; /* 0x6138 */
    U_VP0_DCIPOSGAIN1      VP0_DCIPOSGAIN1                   ; /* 0x613c */
    U_VP0_DCIPOSSLP0       VP0_DCIPOSSLP0                    ; /* 0x6140 */
    U_VP0_DCIPOSSLP1       VP0_DCIPOSSLP1                    ; /* 0x6144 */
    U_VP0_DCIPOSSLP2       VP0_DCIPOSSLP2                    ; /* 0x6148 */
    U_VP0_DCINEGTHR0       VP0_DCINEGTHR0                    ; /* 0x614c */
    U_VP0_DCINEGTHR1       VP0_DCINEGTHR1                    ; /* 0x6150 */
    U_VP0_DCINEGGAIN0      VP0_DCINEGGAIN0                   ; /* 0x6154 */
    U_VP0_DCINEGGAIN1      VP0_DCINEGGAIN1                   ; /* 0x6158 */
    U_VP0_DCINEGSLP0       VP0_DCINEGSLP0                    ; /* 0x615c */
    U_VP0_DCINEGSLP1       VP0_DCINEGSLP1                    ; /* 0x6160 */
    U_VP0_DCINEGSLP2       VP0_DCINEGSLP2                    ; /* 0x6164 */
    U_VP0_DCIADJSW0        VP0_DCIADJSW0                     ; /* 0x6168 */
    U_VP0_DCIADJSW1        VP0_DCIADJSW1                     ; /* 0x616c */
    U_VP0_DCIADJSW2        VP0_DCIADJSW2                     ; /* 0x6170 */
    U_VP0_DCIADJSW3        VP0_DCIADJSW3                     ; /* 0x6174 */
    U_VP0_DCIADJSW4        VP0_DCIADJSW4                     ; /* 0x6178 */
    U_VP0_DCIADJSW5        VP0_DCIADJSW5                     ; /* 0x617c */
    U_VP0_DCIADJSW6        VP0_DCIADJSW6                     ; /* 0x6180 */
    U_VP0_DCIADJSW7        VP0_DCIADJSW7                     ; /* 0x6184 */
    U_VP0_DCIADJSW8        VP0_DCIADJSW8                     ; /* 0x6188 */
    U_VP0_DCIADJSW9        VP0_DCIADJSW9                     ; /* 0x618c */
    U_VP0_DCIADJSW10       VP0_DCIADJSW10                    ; /* 0x6190 */
    U_VP0_DCIWGTRD         VP0_DCIWGTRD                      ; /* 0x6194 */
    U_VP0_DCI_PARARD       VP0_DCI_PARARD                    ; /* 0x6198 */
    U_VP0_DCI_PARA_DATA    VP0_DCI_PARA_DATA                 ; /* 0x619c */
    U_VP0_ACM_CTRL         VP0_ACM_CTRL                      ; /* 0x61a0 */
    U_VP0_ACM_ADJ          VP0_ACM_ADJ                       ; /* 0x61a4 */
    U_VP0_ACM_PARARD       VP0_ACM_PARARD                    ; /* 0x61a8 */
    U_VP0_ACM_PARA_DATA    VP0_ACM_PARA_DATA                 ; /* 0x61ac */
    unsigned int           reserved_51[4]                     ; /* 0x61b0~0x61bc */
    U_VP0_CSC1_IDC         VP0_CSC1_IDC                      ; /* 0x61c0 */
    U_VP0_CSC1_ODC         VP0_CSC1_ODC                      ; /* 0x61c4 */
    U_VP0_CSC1_IODC        VP0_CSC1_IODC                     ; /* 0x61c8 */
    U_VP0_CSC1_P0          VP0_CSC1_P0                       ; /* 0x61cc */
    U_VP0_CSC1_P1          VP0_CSC1_P1                       ; /* 0x61d0 */
    U_VP0_CSC1_P2          VP0_CSC1_P2                       ; /* 0x61d4 */
    U_VP0_CSC1_P3          VP0_CSC1_P3                       ; /* 0x61d8 */
    U_VP0_CSC1_P4          VP0_CSC1_P4                       ; /* 0x61dc */
    unsigned int           reserved_52[8]                     ; /* 0x61e0~0x61fc */
    U_SPCTRL               SPCTRL                            ; /* 0x6200 */
    U_SPDETAILADJ          SPDETAILADJ                       ; /* 0x6204 */
    U_SPRATIO              SPRATIO                           ; /* 0x6208 */
    U_SPCOLORADJ           SPCOLORADJ                        ; /* 0x620c */
    U_SPRATIOH             SPRATIOH                          ; /* 0x6210 */
    U_SPRATIOV             SPRATIOV                          ; /* 0x6214 */
    U_SPRATIOD             SPRATIOD                          ; /* 0x6218 */
    U_SPCORINGH            SPCORINGH                         ; /* 0x621c */
    U_SPCORINGV            SPCORINGV                         ; /* 0x6220 */
    U_SPCORINGD            SPCORINGD                         ; /* 0x6224 */
    U_SPWINSIZEHV          SPWINSIZEHV                       ; /* 0x6228 */
    U_SPWINSIZED           SPWINSIZED                        ; /* 0x622c */
    U_SPGRDH11             SPGRDH11                          ; /* 0x6230 */
    U_SPGRDH12             SPGRDH12                          ; /* 0x6234 */
    U_SPGRDH21             SPGRDH21                          ; /* 0x6238 */
    U_SPGRDH22             SPGRDH22                          ; /* 0x623c */
    U_SPGRDH31             SPGRDH31                          ; /* 0x6240 */
    U_SPGRDH32             SPGRDH32                          ; /* 0x6244 */
    U_SPGRDH41             SPGRDH41                          ; /* 0x6248 */
    U_SPGRDH42             SPGRDH42                          ; /* 0x624c */
    U_SPGRDV0              SPGRDV0                           ; /* 0x6250 */
    U_SPGRDV1              SPGRDV1                           ; /* 0x6254 */
    U_SPGRDV2              SPGRDV2                           ; /* 0x6258 */
    U_SPGRDV3              SPGRDV3                           ; /* 0x625c */
    U_SPGRDD0              SPGRDD0                           ; /* 0x6260 */
    U_SPGRDD1              SPGRDD1                           ; /* 0x6264 */
    U_SPGRDD2              SPGRDD2                           ; /* 0x6268 */
    U_SPGRDD3              SPGRDD3                           ; /* 0x626c */
    U_SPGAINEN             SPGAINEN                          ; /* 0x6270 */
    U_SPSLPH1              SPSLPH1                           ; /* 0x6274 */
    U_SPSLPH2              SPSLPH2                           ; /* 0x6278 */
    U_SPSLPH3              SPSLPH3                           ; /* 0x627c */
    U_SPSLPH4              SPSLPH4                           ; /* 0x6280 */
    U_SPSLPV1              SPSLPV1                           ; /* 0x6284 */
    U_SPSLPV2              SPSLPV2                           ; /* 0x6288 */
    U_SPSLPD1              SPSLPD1                           ; /* 0x628c */
    U_SPSLPD2              SPSLPD2                           ; /* 0x6290 */
    U_SPGAINMINLH1         SPGAINMINLH1                      ; /* 0x6294 */
    U_SPGAINMINLH2         SPGAINMINLH2                      ; /* 0x6298 */
    U_SPGAINMINLV          SPGAINMINLV                       ; /* 0x629c */
    U_SPGAINMINLD          SPGAINMINLD                       ; /* 0x62a0 */
    U_SPGAINMINHH1         SPGAINMINHH1                      ; /* 0x62a4 */
    U_SPGAINMINHH2         SPGAINMINHH2                      ; /* 0x62a8 */
    U_SPGAINMINHV          SPGAINMINHV                       ; /* 0x62ac */
    U_SPGAINMINHD          SPGAINMINHD                       ; /* 0x62b0 */
    U_SPGAINMAXH1          SPGAINMAXH1                       ; /* 0x62b4 */
    U_SPGAINMAXH2          SPGAINMAXH2                       ; /* 0x62b8 */
    U_SPGAINMAXV           SPGAINMAXV                        ; /* 0x62bc */
    U_SPGAINMAXD           SPGAINMAXD                        ; /* 0x62c0 */
    U_SPGAINPOSH1          SPGAINPOSH1                       ; /* 0x62c4 */
    U_SPGAINPOSH2          SPGAINPOSH2                       ; /* 0x62c8 */
    U_SPGAINPOSV           SPGAINPOSV                        ; /* 0x62cc */
    U_SPGAINPOSD           SPGAINPOSD                        ; /* 0x62d0 */
    U_SPGAINNEGH1          SPGAINNEGH1                       ; /* 0x62d4 */
    U_SPGAINNEGH2          SPGAINNEGH2                       ; /* 0x62d8 */
    U_SPGAINNEGV           SPGAINNEGV                        ; /* 0x62dc */
    U_SPGAINNEGD           SPGAINNEGD                        ; /* 0x62e0 */
    U_SPOVERTHDH           SPOVERTHDH                        ; /* 0x62e4 */
    U_SPOVERTHDV           SPOVERTHDV                        ; /* 0x62e8 */
    U_SPOVERTHDD           SPOVERTHDD                        ; /* 0x62ec */
    U_SPUNDERTHDH          SPUNDERTHDH                       ; /* 0x62f0 */
    U_SPUNDERTHDV          SPUNDERTHDV                       ; /* 0x62f4 */
    U_SPUNDERTHDD          SPUNDERTHDD                       ; /* 0x62f8 */
    U_SPTMPH1              SPTMPH1                           ; /* 0x62fc */
    U_SPTMPH2              SPTMPH2                           ; /* 0x6300 */
    U_SPTMPH3              SPTMPH3                           ; /* 0x6304 */
    U_SPTMPH4              SPTMPH4                           ; /* 0x6308 */
    U_SPTMPV1              SPTMPV1                           ; /* 0x630c */
    U_SPTMPV2              SPTMPV2                           ; /* 0x6310 */
    U_SPTMPV3              SPTMPV3                           ; /* 0x6314 */
    U_SPTMPD1              SPTMPD1                           ; /* 0x6318 */
    U_SPTMPD2              SPTMPD2                           ; /* 0x631c */
    U_SPTMPD3              SPTMPD3                           ; /* 0x6320 */
    U_SPTIGAIN             SPTIGAIN                          ; /* 0x6324 */
    U_SPENABLE             SPENABLE                          ; /* 0x6328 */
    U_SPSHOOTEN            SPSHOOTEN                         ; /* 0x632c */
    U_SPLTICOR             SPLTICOR                          ; /* 0x6330 */
    U_SPYVALUETH1          SPYVALUETH1                       ; /* 0x6334 */
    U_SPYVALUESLP1         SPYVALUESLP1                      ; /* 0x6338 */
    U_SPYVALUETH2          SPYVALUETH2                       ; /* 0x633c */
    U_SPYVALUESLP2         SPYVALUESLP2                      ; /* 0x6340 */
    U_SPCTIA1TH            SPCTIA1TH                         ; /* 0x6344 */
    U_SPCTIA2TH            SPCTIA2TH                         ; /* 0x6348 */
    U_SPCTIA3TH            SPCTIA3TH                         ; /* 0x634c */
    U_SPCTIA4GAIN          SPCTIA4GAIN                       ; /* 0x6350 */
    U_SPCTIA1SLP           SPCTIA1SLP                        ; /* 0x6354 */
    U_SPCTIA2SLP           SPCTIA2SLP                        ; /* 0x6358 */
    U_SPCTIA3SLP           SPCTIA3SLP                        ; /* 0x635c */
    U_SPCTIA4TH            SPCTIA4TH                         ; /* 0x6360 */
    U_SPCTIA4SLP           SPCTIA4SLP                        ; /* 0x6364 */
    U_SPFLATSATUR          SPFLATSATUR                       ; /* 0x6368 */
    U_SPGRADSUMTH          SPGRADSUMTH                       ; /* 0x636c */
    U_SPCGRADTHR           SPCGRADTHR                        ; /* 0x6370 */
    U_SPCGRADDIFFTHR       SPCGRADDIFFTHR                    ; /* 0x6374 */
    U_SP_PARARD            SP_PARARD                         ; /* 0x6378 */
    U_SP_PARA_DATA         SP_PARA_DATA                      ; /* 0x637c */
    unsigned int           reserved_53[32]                     ; /* 0x6380~0x63fc */
    U_DHD0_BSCTRL          DHD0_BSCTRL                       ; /* 0x6400 */
    unsigned int           reserved_54[3]                     ; /* 0x6404~0x640c */
    U_DHD0_BSRDELTA0       DHD0_BSRDELTA0                    ; /* 0x6410 */
    U_DHD0_BSRDELTA1       DHD0_BSRDELTA1                    ; /* 0x6414 */
    U_DHD0_BSGDELTA0       DHD0_BSGDELTA0                    ; /* 0x6418 */
    U_DHD0_BSGDELTA1       DHD0_BSGDELTA1                    ; /* 0x641c */
    unsigned int           reserved_55[760]                     ; /* 0x6420~0x6ffc */
    U_G0_CTRL              G0_CTRL                           ; /* 0x7000 */
    U_G0_UPD               G0_UPD                            ; /* 0x7004 */
    unsigned int           reserved_56[2]                     ; /* 0x7008~0x700c */
    U_G0_ADDR              G0_ADDR                           ; /* 0x7010 */
    unsigned int           reserved_57                     ; /* 0x7014 */
    U_G0_NADDR             G0_NADDR                          ; /* 0x7018 */
    U_G0_STRIDE            G0_STRIDE                         ; /* 0x701c */
    U_G0_IRESO             G0_IRESO                          ; /* 0x7020 */
    U_G0_SFPOS             G0_SFPOS                          ; /* 0x7024 */
    unsigned int           reserved_58[2]                     ; /* 0x7028~0x702c */
    U_G0_CBMPARA           G0_CBMPARA                        ; /* 0x7030 */
    U_G0_CKEYMAX           G0_CKEYMAX                        ; /* 0x7034 */
    U_G0_CKEYMIN           G0_CKEYMIN                        ; /* 0x7038 */
    U_G0_CMASK             G0_CMASK                          ; /* 0x703c */
    U_G0_PARAADDR          G0_PARAADDR                       ; /* 0x7040 */
    U_G0_PARAUP            G0_PARAUP                         ; /* 0x7044 */
    unsigned int           reserved_59[2]                     ; /* 0x7048~0x704c */
    U_G0_DCMP_ADDR         G0_DCMP_ADDR                      ; /* 0x7050 */
    U_G0_DCMP_NADDR        G0_DCMP_NADDR                     ; /* 0x7054 */
    U_G0_DCMP_OFFSET       G0_DCMP_OFFSET                    ; /* 0x7058 */
    unsigned int           reserved_60[9]                     ; /* 0x705c~0x707c */
    U_G0_DFPOS             G0_DFPOS                          ; /* 0x7080 */
    U_G0_DLPOS             G0_DLPOS                          ; /* 0x7084 */
    U_G0_VFPOS             G0_VFPOS                          ; /* 0x7088 */
    U_G0_VLPOS             G0_VLPOS                          ; /* 0x708c */
    U_G0_BK                G0_BK                             ; /* 0x7090 */
    U_G0_ALPHA             G0_ALPHA                          ; /* 0x7094 */
    unsigned int           reserved_61[2]                     ; /* 0x7098~0x709c */
    U_G0_DOF_CTRL          G0_DOF_CTRL                       ; /* 0x70a0 */
    U_G0_DOF_STEP          G0_DOF_STEP                       ; /* 0x70a4 */
    U_G0_DOF_BKG           G0_DOF_BKG                        ; /* 0x70a8 */
    U_G0_DOF_ALPHA         G0_DOF_ALPHA                      ; /* 0x70ac */
    unsigned int           reserved_62[4]                     ; /* 0x70b0~0x70bc */
    U_G0_CSC_IDC           G0_CSC_IDC                        ; /* 0x70c0 */
    U_G0_CSC_ODC           G0_CSC_ODC                        ; /* 0x70c4 */
    U_G0_CSC_IODC          G0_CSC_IODC                       ; /* 0x70c8 */
    U_G0_CSC_P0            G0_CSC_P0                         ; /* 0x70cc */
    U_G0_CSC_P1            G0_CSC_P1                         ; /* 0x70d0 */
    U_G0_CSC_P2            G0_CSC_P2                         ; /* 0x70d4 */
    U_G0_CSC_P3            G0_CSC_P3                         ; /* 0x70d8 */
    U_G0_CSC_P4            G0_CSC_P4                         ; /* 0x70dc */
    unsigned int           reserved_63[968]                     ; /* 0x70e0~0x7ffc */
    U_GP0_CTRL             GP0_CTRL                          ; /* 0x8000 */
    U_GP0_UPD              GP0_UPD                           ; /* 0x8004 */
    U_GP0_ORESO            GP0_ORESO                         ; /* 0x8008 */
    U_GP0_IRESO            GP0_IRESO                         ; /* 0x800c */
    U_GP0_HCOEFAD          GP0_HCOEFAD                       ; /* 0x8010 */
    U_GP0_VCOEFAD          GP0_VCOEFAD                       ; /* 0x8014 */
    U_GP0_PARAUP           GP0_PARAUP                        ; /* 0x8018 */
    unsigned int           reserved_64                     ; /* 0x801c */
    U_GP0_GALPHA           GP0_GALPHA                        ; /* 0x8020 */
    unsigned int           reserved_65[55]                     ; /* 0x8024~0x80fc */
    U_GP0_DFPOS            GP0_DFPOS                         ; /* 0x8100 */
    U_GP0_DLPOS            GP0_DLPOS                         ; /* 0x8104 */
    U_GP0_VFPOS            GP0_VFPOS                         ; /* 0x8108 */
    U_GP0_VLPOS            GP0_VLPOS                         ; /* 0x810c */
    U_GP0_BK               GP0_BK                            ; /* 0x8110 */
    U_GP0_ALPHA            GP0_ALPHA                         ; /* 0x8114 */
    unsigned int           reserved_66[2]                     ; /* 0x8118~0x811c */
    U_GP0_CSC_IDC          GP0_CSC_IDC                       ; /* 0x8120 */
    U_GP0_CSC_ODC          GP0_CSC_ODC                       ; /* 0x8124 */
    U_GP0_CSC_IODC         GP0_CSC_IODC                      ; /* 0x8128 */
    U_GP0_CSC_P0           GP0_CSC_P0                        ; /* 0x812c */
    U_GP0_CSC_P1           GP0_CSC_P1                        ; /* 0x8130 */
    U_GP0_CSC_P2           GP0_CSC_P2                        ; /* 0x8134 */
    U_GP0_CSC_P3           GP0_CSC_P3                        ; /* 0x8138 */
    U_GP0_CSC_P4           GP0_CSC_P4                        ; /* 0x813c */
    U_GP0_ZME_HSP          GP0_ZME_HSP                       ; /* 0x8140 */
    U_GP0_ZME_HLOFFSET     GP0_ZME_HLOFFSET                  ; /* 0x8144 */
    U_GP0_ZME_HCOFFSET     GP0_ZME_HCOFFSET                  ; /* 0x8148 */
    U_GP0_ZME_VSP          GP0_ZME_VSP                       ; /* 0x814c */
    U_GP0_ZME_VSR          GP0_ZME_VSR                       ; /* 0x8150 */
    U_GP0_ZME_VOFFSET      GP0_ZME_VOFFSET                   ; /* 0x8154 */
    unsigned int           reserved_67[2]                     ; /* 0x8158~0x815c */
    U_GP0_ZME_LTICTRL      GP0_ZME_LTICTRL                   ; /* 0x8160 */
    U_GP0_ZME_LHPASSCOEF   GP0_ZME_LHPASSCOEF                ; /* 0x8164 */
    U_GP0_ZME_LTITHD       GP0_ZME_LTITHD                    ; /* 0x8168 */
    unsigned int           reserved_68                     ; /* 0x816c */
    U_GP0_ZME_LHFREQTHD    GP0_ZME_LHFREQTHD                 ; /* 0x8170 */
    U_GP0_ZME_LGAINCOEF    GP0_ZME_LGAINCOEF                 ; /* 0x8174 */
    unsigned int           reserved_69[2]                     ; /* 0x8178~0x817c */
    U_GP0_ZME_CTICTRL      GP0_ZME_CTICTRL                   ; /* 0x8180 */
    U_GP0_ZME_CHPASSCOEF   GP0_ZME_CHPASSCOEF                ; /* 0x8184 */
    U_GP0_ZME_CTITHD       GP0_ZME_CTITHD                    ; /* 0x8188 */
    unsigned int           reserved_70                     ; /* 0x818c */
    U_GP0_ZMECOEF          GP0_ZMECOEF                       ; /* 0x8190 */
    U_GP0_ZMECOEFAD        GP0_ZMECOEFAD                     ; /* 0x8194 */
    unsigned int           reserved_71[10]                     ; /* 0x8198~0x81bc */
    U_GP0_WCG_NON2LCTRL    GP0_WCG_NON2LCTRL                 ; /* 0x81c0 */
    U_GP0_WCG_NON2LCOEF0   GP0_WCG_NON2LCOEF0                ; /* 0x81c4 */
    U_GP0_WCG_NON2LCOEF1   GP0_WCG_NON2LCOEF1                ; /* 0x81c8 */
    U_GP0_WCG_NON2LCOEF2   GP0_WCG_NON2LCOEF2                ; /* 0x81cc */
    U_GP0_WCG_CSC2CTRL     GP0_WCG_CSC2CTRL                  ; /* 0x81d0 */
    U_GP0_WCG_CSC2COEF0    GP0_WCG_CSC2COEF0                 ; /* 0x81d4 */
    U_GP0_WCG_CSC2COEF1    GP0_WCG_CSC2COEF1                 ; /* 0x81d8 */
    U_GP0_WCG_CSC2COEF2    GP0_WCG_CSC2COEF2                 ; /* 0x81dc */
    U_GP0_WCG_CSC2COEF3    GP0_WCG_CSC2COEF3                 ; /* 0x81e0 */
    U_GP0_WCG_L2NONTHD     GP0_WCG_L2NONTHD                  ; /* 0x81e4 */
    U_GP0_WCG_L2NONCOEF0   GP0_WCG_L2NONCOEF0                ; /* 0x81e8 */
    U_GP0_WCG_L2NONCOEF1   GP0_WCG_L2NONCOEF1                ; /* 0x81ec */
    U_GP0_WCG_L2NONCOEF2   GP0_WCG_L2NONCOEF2                ; /* 0x81f0 */
    unsigned int           reserved_72[899]                     ; /* 0x81f4~0x8ffc */
    U_WBC_DHD0_CTRL        WBC_DHD0_CTRL                     ; /* 0x9000 */
    U_WBC_DHD0_UPD         WBC_DHD0_UPD                      ; /* 0x9004 */
    unsigned int           reserved_73[2]                     ; /* 0x9008~0x900c */
    U_WBC_DHD0_YADDR       WBC_DHD0_YADDR                    ; /* 0x9010 */
    U_WBC_DHD0_CADDR       WBC_DHD0_CADDR                    ; /* 0x9014 */
    U_WBC_DHD0_STRIDE      WBC_DHD0_STRIDE                   ; /* 0x9018 */
    unsigned int           reserved_74                     ; /* 0x901c */
    U_WBC_DHD0_ORESO       WBC_DHD0_ORESO                    ; /* 0x9020 */
    U_WBC_DHD0_FCROP       WBC_DHD0_FCROP                    ; /* 0x9024 */
    U_WBC_DHD0_LCROP       WBC_DHD0_LCROP                    ; /* 0x9028 */
    unsigned int           reserved_75                     ; /* 0x902c */
    U_WBC_DHD0_LOWDLYCTRL   WBC_DHD0_LOWDLYCTRL              ; /* 0x9030 */
    U_WBC_DHD0_TUNLADDR    WBC_DHD0_TUNLADDR                 ; /* 0x9034 */
    U_WBC_DHD0_LOWDLYSTA   WBC_DHD0_LOWDLYSTA                ; /* 0x9038 */
    unsigned int           reserved_76                     ; /* 0x903c */
    U_WBC_DHD0_PARAUP      WBC_DHD0_PARAUP                   ; /* 0x9040 */
    unsigned int           reserved_77[3]                     ; /* 0x9044~0x904c */
    U_WBC_DHD0_HLCOEFAD    WBC_DHD0_HLCOEFAD                 ; /* 0x9050 */
    U_WBC_DHD0_HCCOEFAD    WBC_DHD0_HCCOEFAD                 ; /* 0x9054 */
    U_WBC_DHD0_VLCOEFAD    WBC_DHD0_VLCOEFAD                 ; /* 0x9058 */
    U_WBC_DHD0_VCCOEFAD    WBC_DHD0_VCCOEFAD                 ; /* 0x905c */
    unsigned int           reserved_78[16]                     ; /* 0x9060~0x909c */
    U_WBC_DHD0_HISTOGRAM0   WBC_DHD0_HISTOGRAM0              ; /* 0x90a0 */
    U_WBC_DHD0_HISTOGRAM1   WBC_DHD0_HISTOGRAM1              ; /* 0x90a4 */
    U_WBC_DHD0_HISTOGRAM2   WBC_DHD0_HISTOGRAM2              ; /* 0x90a8 */
    U_WBC_DHD0_HISTOGRAM3   WBC_DHD0_HISTOGRAM3              ; /* 0x90ac */
    U_WBC_DHD0_HISTOGRAM4   WBC_DHD0_HISTOGRAM4              ; /* 0x90b0 */
    U_WBC_DHD0_HISTOGRAM5   WBC_DHD0_HISTOGRAM5              ; /* 0x90b4 */
    U_WBC_DHD0_HISTOGRAM6   WBC_DHD0_HISTOGRAM6              ; /* 0x90b8 */
    U_WBC_DHD0_HISTOGRAM7   WBC_DHD0_HISTOGRAM7              ; /* 0x90bc */
    U_WBC_DHD0_HISTOGRAM8   WBC_DHD0_HISTOGRAM8              ; /* 0x90c0 */
    U_WBC_DHD0_HISTOGRAM9   WBC_DHD0_HISTOGRAM9              ; /* 0x90c4 */
    U_WBC_DHD0_HISTOGRAM10   WBC_DHD0_HISTOGRAM10            ; /* 0x90c8 */
    U_WBC_DHD0_HISTOGRAM11   WBC_DHD0_HISTOGRAM11            ; /* 0x90cc */
    U_WBC_DHD0_HISTOGRAM12   WBC_DHD0_HISTOGRAM12            ; /* 0x90d0 */
    U_WBC_DHD0_HISTOGRAM13   WBC_DHD0_HISTOGRAM13            ; /* 0x90d4 */
    U_WBC_DHD0_HISTOGRAM14   WBC_DHD0_HISTOGRAM14            ; /* 0x90d8 */
    U_WBC_DHD0_HISTOGRAM15   WBC_DHD0_HISTOGRAM15            ; /* 0x90dc */
    U_WBC_DHD0_DBG_WBC_STA   WBC_DHD0_DBG_WBC_STA            ; /* 0x90e0 */
    U_WBC_DHD0_DBG_WBC_LINE_CNT   WBC_DHD0_DBG_WBC_LINE_CNT  ; /* 0x90e4 */
    unsigned int           reserved_79[2]                     ; /* 0x90e8~0x90ec */
    U_WBC_DHD0_CHECKSUM_Y   WBC_DHD0_CHECKSUM_Y              ; /* 0x90f0 */
    U_WBC_DHD0_CHECKSUM_C   WBC_DHD0_CHECKSUM_C              ; /* 0x90f4 */
    unsigned int           reserved_80[2]                     ; /* 0x90f8~0x90fc */
    U_WBC_DHD0_DITHER_CTRL   WBC_DHD0_DITHER_CTRL            ; /* 0x9100 */
    U_WBC_DHD0_DITHER_COEF0   WBC_DHD0_DITHER_COEF0          ; /* 0x9104 */
    U_WBC_DHD0_DITHER_COEF1   WBC_DHD0_DITHER_COEF1          ; /* 0x9108 */
    unsigned int           reserved_81                     ; /* 0x910c */
    U_WBC_DHD0_HCDS        WBC_DHD0_HCDS                     ; /* 0x9110 */
    U_WBC_DHD0_HCDS_COEF0   WBC_DHD0_HCDS_COEF0              ; /* 0x9114 */
    U_WBC_DHD0_HCDS_COEF1   WBC_DHD0_HCDS_COEF1              ; /* 0x9118 */
    unsigned int           reserved_82[13]                     ; /* 0x911c~0x914c */
    U_WBC_DHD0_HPZME       WBC_DHD0_HPZME                    ; /* 0x9150 */
    unsigned int           reserved_83[91]                     ; /* 0x9154~0x92bc */
    U_WBC_DHD0_ZME_HSP     WBC_DHD0_ZME_HSP                  ; /* 0x92c0 */
    U_WBC_DHD0_ZME_HLOFFSET   WBC_DHD0_ZME_HLOFFSET          ; /* 0x92c4 */
    U_WBC_DHD0_ZME_HCOFFSET   WBC_DHD0_ZME_HCOFFSET          ; /* 0x92c8 */
    unsigned int           reserved_84[3]                     ; /* 0x92cc~0x92d4 */
    U_WBC_DHD0_ZME_VSP     WBC_DHD0_ZME_VSP                  ; /* 0x92d8 */
    U_WBC_DHD0_ZME_VSR     WBC_DHD0_ZME_VSR                  ; /* 0x92dc */
    U_WBC_DHD0_ZME_VOFFSET   WBC_DHD0_ZME_VOFFSET            ; /* 0x92e0 */
    U_WBC_DHD0_ZME_VBOFFSET   WBC_DHD0_ZME_VBOFFSET          ; /* 0x92e4 */
    unsigned int           reserved_85[6]                     ; /* 0x92e8~0x92fc */
    U_WBC_DHD0_CSCIDC      WBC_DHD0_CSCIDC                   ; /* 0x9300 */
    U_WBC_DHD0_CSCODC      WBC_DHD0_CSCODC                   ; /* 0x9304 */
    U_WBC_DHD0_CSCP0       WBC_DHD0_CSCP0                    ; /* 0x9308 */
    U_WBC_DHD0_CSCP1       WBC_DHD0_CSCP1                    ; /* 0x930c */
    U_WBC_DHD0_CSCP2       WBC_DHD0_CSCP2                    ; /* 0x9310 */
    U_WBC_DHD0_CSCP3       WBC_DHD0_CSCP3                    ; /* 0x9314 */
    U_WBC_DHD0_CSCP4       WBC_DHD0_CSCP4                    ; /* 0x9318 */
    unsigned int           reserved_86[57]                     ; /* 0x931c~0x93fc */
    U_WBC_GP0_CTRL         WBC_GP0_CTRL                      ; /* 0x9400 */
    U_WBC_GP0_UPD          WBC_GP0_UPD                       ; /* 0x9404 */
    unsigned int           reserved_87[2]                     ; /* 0x9408~0x940c */
    U_WBC_GP0_YADDR        WBC_GP0_YADDR                     ; /* 0x9410 */
    U_WBC_GP0_CADDR        WBC_GP0_CADDR                     ; /* 0x9414 */
    U_WBC_GP0_STRIDE       WBC_GP0_STRIDE                    ; /* 0x9418 */
    unsigned int           reserved_88                     ; /* 0x941c */
    U_WBC_GP0_ORESO        WBC_GP0_ORESO                     ; /* 0x9420 */
    U_WBC_GP0_FCROP        WBC_GP0_FCROP                     ; /* 0x9424 */
    U_WBC_GP0_LCROP        WBC_GP0_LCROP                     ; /* 0x9428 */
    unsigned int           reserved_89[53]                     ; /* 0x942c~0x94fc */
    U_WBC_GP0_DITHER_CTRL   WBC_GP0_DITHER_CTRL              ; /* 0x9500 */
    U_WBC_GP0_DITHER_COEF0   WBC_GP0_DITHER_COEF0            ; /* 0x9504 */
    U_WBC_GP0_DITHER_COEF1   WBC_GP0_DITHER_COEF1            ; /* 0x9508 */
    unsigned int           reserved_90[17]                     ; /* 0x950c~0x954c */
    U_WBC_GP0_HPZME        WBC_GP0_HPZME                     ; /* 0x9550 */
    unsigned int           reserved_91[171]                     ; /* 0x9554~0x97fc */
    U_WBC_G0_CTRL          WBC_G0_CTRL                       ; /* 0x9800 */
    U_WBC_G0_UPD           WBC_G0_UPD                        ; /* 0x9804 */
    U_WBC_G0_CMP           WBC_G0_CMP                        ; /* 0x9808 */
    unsigned int           reserved_92                     ; /* 0x980c */
    U_WBC_G0_AR_ADDR       WBC_G0_AR_ADDR                    ; /* 0x9810 */
    U_WBC_G0_GB_ADDR       WBC_G0_GB_ADDR                    ; /* 0x9814 */
    U_WBC_G0_STRIDE        WBC_G0_STRIDE                     ; /* 0x9818 */
    U_WBC_G0_OFFSET        WBC_G0_OFFSET                     ; /* 0x981c */
    U_WBC_G0_ORESO         WBC_G0_ORESO                      ; /* 0x9820 */
    U_WBC_G0_FCROP         WBC_G0_FCROP                      ; /* 0x9824 */
    U_WBC_G0_LCROP         WBC_G0_LCROP                      ; /* 0x9828 */
    unsigned int           reserved_93[501]                     ; /* 0x982c~0x9ffc */
    U_WBC_ME_CTRL          WBC_ME_CTRL                       ; /* 0xa000 */
    U_WBC_ME_UPD           WBC_ME_UPD                        ; /* 0xa004 */
    unsigned int           reserved_94[2]                     ; /* 0xa008~0xa00c */
    U_WBC_ME_YADDR         WBC_ME_YADDR                      ; /* 0xa010 */
    U_WBC_ME_CADDR         WBC_ME_CADDR                      ; /* 0xa014 */
    U_WBC_ME_STRIDE        WBC_ME_STRIDE                     ; /* 0xa018 */
    unsigned int           reserved_95                     ; /* 0xa01c */
    U_WBC_ME_ORESO         WBC_ME_ORESO                      ; /* 0xa020 */
    unsigned int           reserved_96[7]                     ; /* 0xa024~0xa03c */
    U_WBC_ME_PARAUP        WBC_ME_PARAUP                     ; /* 0xa040 */
    unsigned int           reserved_97[3]                     ; /* 0xa044~0xa04c */
    U_WBC_ME_HLCOEFAD      WBC_ME_HLCOEFAD                   ; /* 0xa050 */
    U_WBC_ME_HCCOEFAD      WBC_ME_HCCOEFAD                   ; /* 0xa054 */
    U_WBC_ME_VLCOEFAD      WBC_ME_VLCOEFAD                   ; /* 0xa058 */
    U_WBC_ME_VCCOEFAD      WBC_ME_VCCOEFAD                   ; /* 0xa05c */
    unsigned int           reserved_98[36]                     ; /* 0xa060~0xa0ec */
    U_WBC_ME_CHECKSUM_Y    WBC_ME_CHECKSUM_Y                 ; /* 0xa0f0 */
    U_WBC_ME_CHECKSUM_C    WBC_ME_CHECKSUM_C                 ; /* 0xa0f4 */
    unsigned int           reserved_99[2]                     ; /* 0xa0f8~0xa0fc */
    U_WBC_ME_DITHER_CTRL   WBC_ME_DITHER_CTRL                ; /* 0xa100 */
    U_WBC_ME_DITHER_COEF0   WBC_ME_DITHER_COEF0              ; /* 0xa104 */
    U_WBC_ME_DITHER_COEF1   WBC_ME_DITHER_COEF1              ; /* 0xa108 */
    unsigned int           reserved_100[109]                     ; /* 0xa10c~0xa2bc */
    U_WBC_ME_ZME_HSP       WBC_ME_ZME_HSP                    ; /* 0xa2c0 */
    U_WBC_ME_ZME_HLOFFSET   WBC_ME_ZME_HLOFFSET              ; /* 0xa2c4 */
    U_WBC_ME_ZME_HCOFFSET   WBC_ME_ZME_HCOFFSET              ; /* 0xa2c8 */
    unsigned int           reserved_101[3]                     ; /* 0xa2cc~0xa2d4 */
    U_WBC_ME_ZME_VSP       WBC_ME_ZME_VSP                    ; /* 0xa2d8 */
    U_WBC_ME_ZME_VSR       WBC_ME_ZME_VSR                    ; /* 0xa2dc */
    U_WBC_ME_ZME_VOFFSET   WBC_ME_ZME_VOFFSET                ; /* 0xa2e0 */
    U_WBC_ME_ZME_VBOFFSET   WBC_ME_ZME_VBOFFSET              ; /* 0xa2e4 */
    unsigned int           reserved_102[70]                     ; /* 0xa2e8~0xa3fc */
    U_WBC_FI_CTRL          WBC_FI_CTRL                       ; /* 0xa400 */
    U_WBC_FI_UPD           WBC_FI_UPD                        ; /* 0xa404 */
    unsigned int           reserved_103[2]                     ; /* 0xa408~0xa40c */
    U_WBC_FI_YADDR         WBC_FI_YADDR                      ; /* 0xa410 */
    unsigned int           reserved_104[3]                     ; /* 0xa414~0xa41c */
    U_WBC_FI_ORESO         WBC_FI_ORESO                      ; /* 0xa420 */
    unsigned int           reserved_105[51]                     ; /* 0xa424~0xa4ec */
    U_WBC_FI_CHECKSUM_Y    WBC_FI_CHECKSUM_Y                 ; /* 0xa4f0 */
    U_WBC_FI_CHECKSUM_C    WBC_FI_CHECKSUM_C                 ; /* 0xa4f4 */
    unsigned int           reserved_106[6]                     ; /* 0xa4f8~0xa50c */
    U_WBC_FI_HCDS          WBC_FI_HCDS                       ; /* 0xa510 */
    U_WBC_FI_HCDS_COEF0    WBC_FI_HCDS_COEF0                 ; /* 0xa514 */
    U_WBC_FI_HCDS_COEF1    WBC_FI_HCDS_COEF1                 ; /* 0xa518 */
    unsigned int           reserved_107                     ; /* 0xa51c */
    U_WBC_FI_CMP_MB        WBC_FI_CMP_MB                     ; /* 0xa520 */
    U_WBC_FI_CMP_MAX_MIN   WBC_FI_CMP_MAX_MIN                ; /* 0xa524 */
    U_WBC_FI_CMP_ADJ_THR   WBC_FI_CMP_ADJ_THR                ; /* 0xa528 */
    U_WBC_FI_CMP_BIG_GRAD   WBC_FI_CMP_BIG_GRAD              ; /* 0xa52c */
    U_WBC_FI_CMP_BLK       WBC_FI_CMP_BLK                    ; /* 0xa530 */
    U_WBC_FI_CMP_GRAPHIC_JUDGE   WBC_FI_CMP_GRAPHIC_JUDGE    ; /* 0xa534 */
    U_WBC_FI_CMP_RC        WBC_FI_CMP_RC                     ; /* 0xa538 */
    U_WBC_FI_CMP_FRAME_SIZE   WBC_FI_CMP_FRAME_SIZE          ; /* 0xa53c */
    unsigned int           reserved_108[176]                     ; /* 0xa540~0xa7fc */
    U_WBC_BMP_CTRL         WBC_BMP_CTRL                      ; /* 0xa800 */
    U_WBC_BMP_UPD          WBC_BMP_UPD                       ; /* 0xa804 */
    unsigned int           reserved_109[2]                     ; /* 0xa808~0xa80c */
    U_WBC_BMP_YADDR        WBC_BMP_YADDR                     ; /* 0xa810 */
    unsigned int           reserved_110[3]                     ; /* 0xa814~0xa81c */
    U_WBC_BMP_ORESO        WBC_BMP_ORESO                     ; /* 0xa820 */
    unsigned int           reserved_111[8]                     ; /* 0xa824~0xa840 */
    U_WBC_BMP_SUM          WBC_BMP_SUM                       ; /* 0xa844 */
    unsigned int           reserved_112[42]                     ; /* 0xa848~0xa8ec */
    U_WBC_BMP_CHECKSUM_Y   WBC_BMP_CHECKSUM_Y                ; /* 0xa8f0 */
    U_WBC_BMP_CHECKSUM_C   WBC_BMP_CHECKSUM_C                ; /* 0xa8f4 */
    unsigned int           reserved_113[450]                     ; /* 0xa8f8~0xaffc */
    U_MIXV0_BKG            MIXV0_BKG                         ; /* 0xb000 */
    unsigned int           reserved_114                     ; /* 0xb004 */
    U_MIXV0_MIX            MIXV0_MIX                         ; /* 0xb008 */
    unsigned int           reserved_115[125]                     ; /* 0xb00c~0xb1fc */
    U_MIXG0_BKG            MIXG0_BKG                         ; /* 0xb200 */
    U_MIXG0_BKALPHA        MIXG0_BKALPHA                     ; /* 0xb204 */
    U_MIXG0_MIX            MIXG0_MIX                         ; /* 0xb208 */
    unsigned int           reserved_116[125]                     ; /* 0xb20c~0xb3fc */
    U_CBM_BKG1             CBM_BKG1                          ; /* 0xb400 */
    unsigned int           reserved_117                     ; /* 0xb404 */
    U_CBM_MIX1             CBM_MIX1                          ; /* 0xb408 */
    unsigned int           reserved_118[14]                     ; /* 0xb40c~0xb440 */
    U_WBC_BMP_THD          WBC_BMP_THD                       ; /* 0xb444 */
    unsigned int           reserved_119[46]                     ; /* 0xb448~0xb4fc */
    U_CBM_BKG2             CBM_BKG2                          ; /* 0xb500 */
    unsigned int           reserved_120                     ; /* 0xb504 */
    U_CBM_MIX2             CBM_MIX2                          ; /* 0xb508 */
    unsigned int           reserved_121[14]                     ; /* 0xb50c~0xb540 */
    U_HC_BMP_THD           HC_BMP_THD                        ; /* 0xb544 */
    unsigned int           reserved_122[46]                     ; /* 0xb548~0xb5fc */
    U_CBM_BKG3             CBM_BKG3                          ; /* 0xb600 */
    unsigned int           reserved_123                     ; /* 0xb604 */
    U_CBM_MIX3             CBM_MIX3                          ; /* 0xb608 */
    unsigned int           reserved_124[157]                     ; /* 0xb60c~0xb87c */
    U_SR_CTRL              SR_CTRL                           ; /* 0xb880 */
    U_SR_LDIR_RATIO        SR_LDIR_RATIO                     ; /* 0xb884 */
    U_SR_LTEX_THR          SR_LTEX_THR                       ; /* 0xb888 */
    U_SR_LTEX_ADD          SR_LTEX_ADD                       ; /* 0xb88c */
    U_SR_DIPL_DETAIL       SR_DIPL_DETAIL                    ; /* 0xb890 */
    U_SR_SHARP_EN          SR_SHARP_EN                       ; /* 0xb894 */
    U_SR_SHARP_THR         SR_SHARP_THR                      ; /* 0xb898 */
    U_SR_SMOOTH            SR_SMOOTH                         ; /* 0xb89c */
    unsigned int           reserved_125[8]                     ; /* 0xb8a0~0xb8bc */
    U_SR_HSP               SR_HSP                            ; /* 0xb8c0 */
    U_SR_HLOFFSET          SR_HLOFFSET                       ; /* 0xb8c4 */
    U_SR_HCOFFSET          SR_HCOFFSET                       ; /* 0xb8c8 */
    unsigned int           reserved_126[3]                     ; /* 0xb8cc~0xb8d4 */
    U_SR_VSP               SR_VSP                            ; /* 0xb8d8 */
    U_SR_VSR               SR_VSR                            ; /* 0xb8dc */
    U_SR_VOFFSET           SR_VOFFSET                        ; /* 0xb8e0 */
    U_SR_VBOFFSET          SR_VBOFFSET                       ; /* 0xb8e4 */
    unsigned int           reserved_127[6]                     ; /* 0xb8e8~0xb8fc */
    U_SR_RINGDT0           SR_RINGDT0                        ; /* 0xb900 */
    U_SR_RINGDT1           SR_RINGDT1                        ; /* 0xb904 */
    U_SR_SKINDT_CTRL       SR_SKINDT_CTRL                    ; /* 0xb908 */
    U_SR_SKINDT_EXP        SR_SKINDT_EXP                     ; /* 0xb90c */
    U_SR_SKINDT_YTHR       SR_SKINDT_YTHR                    ; /* 0xb910 */
    U_SR_SKINDT_UTHR       SR_SKINDT_UTHR                    ; /* 0xb914 */
    U_SR_SKINDT_VTHR       SR_SKINDT_VTHR                    ; /* 0xb918 */
    U_SR_HANCE_SLOP        SR_HANCE_SLOP                     ; /* 0xb91c */
    U_SR_HANCE_SHARP_THR   SR_HANCE_SHARP_THR                ; /* 0xb920 */
    U_SR_HANCE_LOW_CTRL    SR_HANCE_LOW_CTRL                 ; /* 0xb924 */
    U_SR_HANCE_HIGH_CTRL   SR_HANCE_HIGH_CTRL                ; /* 0xb928 */
    U_SR_HANCE_THR0        SR_HANCE_THR0                     ; /* 0xb92c */
    U_SR_HANCE_THR1        SR_HANCE_THR1                     ; /* 0xb930 */
    U_SR_HANCE_THR2        SR_HANCE_THR2                     ; /* 0xb934 */
    U_SR_DIR_CTRL          SR_DIR_CTRL                       ; /* 0xb938 */
    unsigned int           reserved_128                     ; /* 0xb93c */
    U_SR_HCOEF0            SR_HCOEF0                         ; /* 0xb940 */
    U_SR_HCOEF1            SR_HCOEF1                         ; /* 0xb944 */
    U_SR_HCOEF2            SR_HCOEF2                         ; /* 0xb948 */
    U_SR_HCOEF3            SR_HCOEF3                         ; /* 0xb94c */
    U_SR_HCOEF4            SR_HCOEF4                         ; /* 0xb950 */
    U_SR_HCOEF5            SR_HCOEF5                         ; /* 0xb954 */
    U_SR_HCOEF6            SR_HCOEF6                         ; /* 0xb958 */
    U_SR_HCOEF7            SR_HCOEF7                         ; /* 0xb95c */
    U_SR_HCOEF8            SR_HCOEF8                         ; /* 0xb960 */
    U_SR_HCOEF9            SR_HCOEF9                         ; /* 0xb964 */
    U_SR_HCOEF10           SR_HCOEF10                        ; /* 0xb968 */
    U_SR_HCOEF11           SR_HCOEF11                        ; /* 0xb96c */
    U_SR_VCOEF0            SR_VCOEF0                         ; /* 0xb970 */
    U_SR_VCOEF1            SR_VCOEF1                         ; /* 0xb974 */
    U_SR_VCOEF2            SR_VCOEF2                         ; /* 0xb978 */
    U_SR_VCOEF3            SR_VCOEF3                         ; /* 0xb97c */
    U_SR_VCOEF4            SR_VCOEF4                         ; /* 0xb980 */
    U_SR_VCOEF5            SR_VCOEF5                         ; /* 0xb984 */
    U_SR_VCOEF6            SR_VCOEF6                         ; /* 0xb988 */
    U_SR_VCOEF7            SR_VCOEF7                         ; /* 0xb98c */
    unsigned int           reserved_129[412]                     ; /* 0xb990~0xbffc */
    U_DHD0_CTRL            DHD0_CTRL                         ; /* 0xc000 */
    U_DHD0_VSYNC           DHD0_VSYNC                        ; /* 0xc004 */
    U_DHD0_HSYNC1          DHD0_HSYNC1                       ; /* 0xc008 */
    U_DHD0_HSYNC2          DHD0_HSYNC2                       ; /* 0xc00c */
    U_DHD0_VPLUS           DHD0_VPLUS                        ; /* 0xc010 */
    U_DHD0_PWR             DHD0_PWR                          ; /* 0xc014 */
    U_DHD0_VTTHD3          DHD0_VTTHD3                       ; /* 0xc018 */
    U_DHD0_VTTHD           DHD0_VTTHD                        ; /* 0xc01c */
    U_DHD0_SYNC_INV        DHD0_SYNC_INV                     ; /* 0xc020 */
    U_DHD0_SRIRESO         DHD0_SRIRESO                      ; /* 0xc024 */
    U_DHD0_SRSEL           DHD0_SRSEL                        ; /* 0xc028 */
    U_DHD0_DATA_SEL        DHD0_DATA_SEL                     ; /* 0xc02c */
    unsigned int           reserved_130[4]                     ; /* 0xc030~0xc03c */
    U_DHD0_CSC_IDC         DHD0_CSC_IDC                      ; /* 0xc040 */
    U_DHD0_CSC_ODC         DHD0_CSC_ODC                      ; /* 0xc044 */
    U_DHD0_CSC_IODC        DHD0_CSC_IODC                     ; /* 0xc048 */
    U_DHD0_CSC_P0          DHD0_CSC_P0                       ; /* 0xc04c */
    U_DHD0_CSC_P1          DHD0_CSC_P1                       ; /* 0xc050 */
    U_DHD0_CSC_P2          DHD0_CSC_P2                       ; /* 0xc054 */
    U_DHD0_CSC_P3          DHD0_CSC_P3                       ; /* 0xc058 */
    U_DHD0_CSC_P4          DHD0_CSC_P4                       ; /* 0xc05c */
    U_DHD0_DITHER0_CTRL    DHD0_DITHER0_CTRL                 ; /* 0xc060 */
    U_DHD0_DITHER0_COEF0   DHD0_DITHER0_COEF0                ; /* 0xc064 */
    U_DHD0_DITHER0_COEF1   DHD0_DITHER0_COEF1                ; /* 0xc068 */
    unsigned int           reserved_131                     ; /* 0xc06c */
    U_DHD0_DITHER1_CTRL    DHD0_DITHER1_CTRL                 ; /* 0xc070 */
    U_DHD0_DITHER1_COEF0   DHD0_DITHER1_COEF0                ; /* 0xc074 */
    U_DHD0_DITHER1_COEF1   DHD0_DITHER1_COEF1                ; /* 0xc078 */
    unsigned int           reserved_132                     ; /* 0xc07c */
    U_DHD0_CLIP0_L         DHD0_CLIP0_L                      ; /* 0xc080 */
    U_DHD0_CLIP0_H         DHD0_CLIP0_H                      ; /* 0xc084 */
    U_DHD0_CLIP1_L         DHD0_CLIP1_L                      ; /* 0xc088 */
    U_DHD0_CLIP1_H         DHD0_CLIP1_H                      ; /* 0xc08c */
    U_DHD0_CLIP2_L         DHD0_CLIP2_L                      ; /* 0xc090 */
    U_DHD0_CLIP2_H         DHD0_CLIP2_H                      ; /* 0xc094 */
    U_DHD0_CLIP3_L         DHD0_CLIP3_L                      ; /* 0xc098 */
    U_DHD0_CLIP3_H         DHD0_CLIP3_H                      ; /* 0xc09c */
    U_DHD0_CLIP4_L         DHD0_CLIP4_L                      ; /* 0xc0a0 */
    U_DHD0_CLIP4_H         DHD0_CLIP4_H                      ; /* 0xc0a4 */
    unsigned int           reserved_133[2]                     ; /* 0xc0a8~0xc0ac */
    U_DHD0_PARATHD         DHD0_PARATHD                      ; /* 0xc0b0 */
    U_DHD0_VBI             DHD0_VBI                          ; /* 0xc0b4 */
    U_DHD0_HBI             DHD0_HBI                          ; /* 0xc0b8 */
    unsigned int           reserved_134                     ; /* 0xc0bc */
    U_DHD0_START_POS       DHD0_START_POS                    ; /* 0xc0c0 */
    unsigned int           reserved_135[3]                     ; /* 0xc0c4~0xc0cc */
    U_DHD0_LOCKCFG         DHD0_LOCKCFG                      ; /* 0xc0d0 */
    U_DHD0_CAP_FRM_CNT     DHD0_CAP_FRM_CNT                  ; /* 0xc0d4 */
    unsigned int           reserved_136                     ; /* 0xc0d8 */
    U_DHD0_VSYNC_CAP_VDP_CNT   DHD0_VSYNC_CAP_VDP_CNT        ; /* 0xc0dc */
    U_DHD0_GMM_COEFAD      DHD0_GMM_COEFAD                   ; /* 0xc0e0 */
    unsigned int           reserved_137[2]                     ; /* 0xc0e4~0xc0e8 */
    U_DHD0_PARAUP          DHD0_PARAUP                       ; /* 0xc0ec */
    U_DHD0_STATE           DHD0_STATE                        ; /* 0xc0f0 */
    unsigned int           reserved_138[3]                     ; /* 0xc0f4~0xc0fc */
    U_DHDWCG_NON2LCTRL     DHDWCG_NON2LCTRL                  ; /* 0xc100 */
    U_DHDWCG_NON2LCOEF0    DHDWCG_NON2LCOEF0                 ; /* 0xc104 */
    U_DHDWCG_NON2LCOEF1    DHDWCG_NON2LCOEF1                 ; /* 0xc108 */
    U_DHDWCG_NON2LCOEF2    DHDWCG_NON2LCOEF2                 ; /* 0xc10c */
    U_DHDWCG_CSC2CTRL      DHDWCG_CSC2CTRL                   ; /* 0xc110 */
    U_DHDWCG_CSC2COEF0     DHDWCG_CSC2COEF0                  ; /* 0xc114 */
    U_DHDWCG_CSC2COEF1     DHDWCG_CSC2COEF1                  ; /* 0xc118 */
    U_DHDWCG_CSC2COEF2     DHDWCG_CSC2COEF2                  ; /* 0xc11c */
    U_DHDWCG_CSC2COEF3     DHDWCG_CSC2COEF3                  ; /* 0xc120 */
    U_DHDWCG_L2NONTHD      DHDWCG_L2NONTHD                   ; /* 0xc124 */
    U_DHDWCG_L2NONCOEF0    DHDWCG_L2NONCOEF0                 ; /* 0xc128 */
    U_DHDWCG_L2NONCOEF1    DHDWCG_L2NONCOEF1                 ; /* 0xc12c */
    U_DHDWCG_L2NONCOEF2    DHDWCG_L2NONCOEF2                 ; /* 0xc130 */
    unsigned int           reserved_139[7]                     ; /* 0xc134~0xc14c */
    U_DHD0_DITHER_CTRL     DHD0_DITHER_CTRL                  ; /* 0xc150 */
    U_DHD0_DITHER_COEF0    DHD0_DITHER_COEF0                 ; /* 0xc154 */
    U_DHD0_DITHER_COEF1    DHD0_DITHER_COEF1                 ; /* 0xc158 */
    unsigned int           reserved_140                     ; /* 0xc15c */
    U_SR_CSC0_IDC          SR_CSC0_IDC                       ; /* 0xc160 */
    U_SR_CSC0_ODC          SR_CSC0_ODC                       ; /* 0xc164 */
    U_SR_CSC0_IODC         SR_CSC0_IODC                      ; /* 0xc168 */
    U_SR_CSC0_P0           SR_CSC0_P0                        ; /* 0xc16c */
    U_SR_CSC0_P1           SR_CSC0_P1                        ; /* 0xc170 */
    U_SR_CSC0_P2           SR_CSC0_P2                        ; /* 0xc174 */
    U_SR_CSC0_P3           SR_CSC0_P3                        ; /* 0xc178 */
    U_SR_CSC0_P4           SR_CSC0_P4                        ; /* 0xc17c */
    U_DHDHLCOEFAD          DHDHLCOEFAD                       ; /* 0xc180 */
    U_DHDHCCOEFAD          DHDHCCOEFAD                       ; /* 0xc184 */
    U_DHDVLCOEFAD          DHDVLCOEFAD                       ; /* 0xc188 */
    U_DHDVCCOEFAD          DHDVCCOEFAD                       ; /* 0xc18c */
    U_DHDDIMLUTAD          DHDDIMLUTAD                       ; /* 0xc190 */
    U_DHDDIMHFAD           DHDDIMHFAD                        ; /* 0xc194 */
    U_DHDDIMVFAD           DHDDIMVFAD                        ; /* 0xc198 */
    unsigned int           reserved_141[9]                     ; /* 0xc19c~0xc1bc */
    U_SR_CSC1_IDC          SR_CSC1_IDC                       ; /* 0xc1c0 */
    U_SR_CSC1_ODC          SR_CSC1_ODC                       ; /* 0xc1c4 */
    U_SR_CSC1_IODC         SR_CSC1_IODC                      ; /* 0xc1c8 */
    U_SR_CSC1_P0           SR_CSC1_P0                        ; /* 0xc1cc */
    U_SR_CSC1_P1           SR_CSC1_P1                        ; /* 0xc1d0 */
    U_SR_CSC1_P2           SR_CSC1_P2                        ; /* 0xc1d4 */
    U_SR_CSC1_P3           SR_CSC1_P3                        ; /* 0xc1d8 */
    U_SR_CSC1_P4           SR_CSC1_P4                        ; /* 0xc1dc */
    unsigned int           reserved_142[8]                     ; /* 0xc1e0~0xc1fc */
    U_DIM_GLB_CTRL         DIM_GLB_CTRL                      ; /* 0xc200 */
    U_DIM_LED_NUM          DIM_LED_NUM                       ; /* 0xc204 */
    U_DIM_SEG_METIRCS      DIM_SEG_METIRCS                   ; /* 0xc208 */
    U_DIM_START_POS        DIM_START_POS                     ; /* 0xc20c */
    U_DIM_STAT_METRICS     DIM_STAT_METRICS                  ; /* 0xc210 */
    U_DIM_GLB_NORM_UNIT    DIM_GLB_NORM_UNIT                 ; /* 0xc214 */
    U_DIM_SEG_NORM_UNIT    DIM_SEG_NORM_UNIT                 ; /* 0xc218 */
    U_DIM_HIST_STAT        DIM_HIST_STAT                     ; /* 0xc21c */
    U_DIM_ADJ0D_CORE0      DIM_ADJ0D_CORE0                   ; /* 0xc220 */
    U_DIM_ADJ0D_CORE1      DIM_ADJ0D_CORE1                   ; /* 0xc224 */
    U_DIM_LED0D_LOW_THRESH0   DIM_LED0D_LOW_THRESH0          ; /* 0xc228 */
    U_DIM_LED0D_LOW_THRESH1   DIM_LED0D_LOW_THRESH1          ; /* 0xc22c */
    U_DIM_LED0D_LOW_OFFSET0   DIM_LED0D_LOW_OFFSET0          ; /* 0xc230 */
    U_DIM_LED0D_LOW_OFFSET1   DIM_LED0D_LOW_OFFSET1          ; /* 0xc234 */
    U_DIM_LED0D_LOW_GAIN0   DIM_LED0D_LOW_GAIN0              ; /* 0xc238 */
    U_DIM_LED0D_LOW_GAIN1   DIM_LED0D_LOW_GAIN1              ; /* 0xc23c */
    U_DIM_LED0D_MID_THRESH0   DIM_LED0D_MID_THRESH0          ; /* 0xc240 */
    U_DIM_LED0D_MID_THRESH1   DIM_LED0D_MID_THRESH1          ; /* 0xc244 */
    U_DIM_LED0D_MID_OFFSET0   DIM_LED0D_MID_OFFSET0          ; /* 0xc248 */
    U_DIM_LED0D_MID_OFFSET1   DIM_LED0D_MID_OFFSET1          ; /* 0xc24c */
    U_DIM_LED0D_MID_GAIN0   DIM_LED0D_MID_GAIN0              ; /* 0xc250 */
    U_DIM_LED0D_MID_GAIN1   DIM_LED0D_MID_GAIN1              ; /* 0xc254 */
    U_DIM_LED0D_HIGH_THRESH0   DIM_LED0D_HIGH_THRESH0        ; /* 0xc258 */
    U_DIM_LED0D_HIGH_THRESH1   DIM_LED0D_HIGH_THRESH1        ; /* 0xc25c */
    U_DIM_LED0D_HIGH_OFFSET0   DIM_LED0D_HIGH_OFFSET0        ; /* 0xc260 */
    U_DIM_LED0D_HIGH_OFFSET1   DIM_LED0D_HIGH_OFFSET1        ; /* 0xc264 */
    U_DIM_LED0D_HIGH_GAIN0   DIM_LED0D_HIGH_GAIN0            ; /* 0xc268 */
    U_DIM_LED0D_HIGH_GAIN1   DIM_LED0D_HIGH_GAIN1            ; /* 0xc26c */
    U_DIM_ADJ2D_CORE0      DIM_ADJ2D_CORE0                   ; /* 0xc270 */
    U_DIM_ADJ2D_CORE1      DIM_ADJ2D_CORE1                   ; /* 0xc274 */
    U_DIM_LED2D_LOW_THRESH0   DIM_LED2D_LOW_THRESH0          ; /* 0xc278 */
    U_DIM_LED2D_LOW_THRESH1   DIM_LED2D_LOW_THRESH1          ; /* 0xc27c */
    U_DIM_LED2D_LOW_OFFSET0   DIM_LED2D_LOW_OFFSET0          ; /* 0xc280 */
    U_DIM_LED2D_LOW_OFFSET1   DIM_LED2D_LOW_OFFSET1          ; /* 0xc284 */
    U_DIM_LED2D_LOW_GAIN0   DIM_LED2D_LOW_GAIN0              ; /* 0xc288 */
    U_DIM_LED2D_LOW_GAIN1   DIM_LED2D_LOW_GAIN1              ; /* 0xc28c */
    U_DIM_LED2D_MID_THRESH0   DIM_LED2D_MID_THRESH0          ; /* 0xc290 */
    U_DIM_LED2D_MID_THRESH1   DIM_LED2D_MID_THRESH1          ; /* 0xc294 */
    U_DIM_LED2D_MID_OFFSET0   DIM_LED2D_MID_OFFSET0          ; /* 0xc298 */
    U_DIM_LED2D_MID_OFFSET1   DIM_LED2D_MID_OFFSET1          ; /* 0xc29c */
    U_DIM_LED2D_MID_GAIN0   DIM_LED2D_MID_GAIN0              ; /* 0xc2a0 */
    U_DIM_LED2D_MID_GAIN1   DIM_LED2D_MID_GAIN1              ; /* 0xc2a4 */
    U_DIM_LED2D_HIGH_THRESH0   DIM_LED2D_HIGH_THRESH0        ; /* 0xc2a8 */
    U_DIM_LED2D_HIGH_THRESH1   DIM_LED2D_HIGH_THRESH1        ; /* 0xc2ac */
    U_DIM_LED2D_HIGH_OFFSET0   DIM_LED2D_HIGH_OFFSET0        ; /* 0xc2b0 */
    U_DIM_LED2D_HIGH_OFFSET1   DIM_LED2D_HIGH_OFFSET1        ; /* 0xc2b4 */
    U_DIM_LED2D_HIGH_GAIN0   DIM_LED2D_HIGH_GAIN0            ; /* 0xc2b8 */
    U_DIM_LED2D_HIGH_GAIN1   DIM_LED2D_HIGH_GAIN1            ; /* 0xc2bc */
    U_DIM_LED0D_CORE       DIM_LED0D_CORE                    ; /* 0xc2c0 */
    U_DIM_LED0D_GAIN_MISC   DIM_LED0D_GAIN_MISC              ; /* 0xc2c4 */
    U_DIM_LED2D_GAIN_MISC   DIM_LED2D_GAIN_MISC              ; /* 0xc2c8 */
    U_DIM_PRE_0D2D_BLD     DIM_PRE_0D2D_BLD                  ; /* 0xc2cc */
    U_DIM_FINAL_GAIN_0D    DIM_FINAL_GAIN_0D                 ; /* 0xc2d0 */
    U_DIM_FINAL_CLIP_0D    DIM_FINAL_CLIP_0D                 ; /* 0xc2d4 */
    U_DIM_FINAL_GAIN_2D    DIM_FINAL_GAIN_2D                 ; /* 0xc2d8 */
    U_DIM_FINAL_CLIP_2D    DIM_FINAL_CLIP_2D                 ; /* 0xc2dc */
    U_DIM_LED0D_STATUS     DIM_LED0D_STATUS                  ; /* 0xc2e0 */
    U_DIM_VFIR_COEF_0      DIM_VFIR_COEF_0                   ; /* 0xc2e4 */
    U_DIM_VFIR_COEF_1      DIM_VFIR_COEF_1                   ; /* 0xc2e8 */
    U_DIM_HFIR_COEF_0      DIM_HFIR_COEF_0                   ; /* 0xc2ec */
    U_DIM_HFIR_COEF_1      DIM_HFIR_COEF_1                   ; /* 0xc2f0 */
    U_DIM_POST_FIR_BLD     DIM_POST_FIR_BLD                  ; /* 0xc2f4 */
    U_DIM_POST_FIR_GAIN    DIM_POST_FIR_GAIN                 ; /* 0xc2f8 */
    U_DIM_LCD_COMP_0D      DIM_LCD_COMP_0D                   ; /* 0xc2fc */
    U_DIM_LCD_COMP_2D      DIM_LCD_COMP_2D                   ; /* 0xc300 */
    U_DIM_LCD_COMPGAIN     DIM_LCD_COMPGAIN                  ; /* 0xc304 */
    U_DIM_LED_PANEL        DIM_LED_PANEL                     ; /* 0xc308 */
    U_DIM_LED0D2D          DIM_LED0D2D                       ; /* 0xc30c */
    U_DIM_SCL_CTRL         DIM_SCL_CTRL                      ; /* 0xc310 */
    U_DIM_SCL_OFFSET_V     DIM_SCL_OFFSET_V                  ; /* 0xc314 */
    U_DIM_SCL_OFFSET_H     DIM_SCL_OFFSET_H                  ; /* 0xc318 */
    U_DIM_SCL_RATIO_V      DIM_SCL_RATIO_V                   ; /* 0xc31c */
    U_DIM_SCL_RATIO_H      DIM_SCL_RATIO_H                   ; /* 0xc320 */
    U_DIM_PARA_REN         DIM_PARA_REN                      ; /* 0xc324 */
    U_DIM_PARA_DATA        DIM_PARA_DATA                     ; /* 0xc328 */
    unsigned int           reserved_143[15]                     ; /* 0xc32c~0xc364 */
    U_INTF_CHKSUM_Y        INTF_CHKSUM_Y                     ; /* 0xc368 */
    U_INTF_CHKSUM_U        INTF_CHKSUM_U                     ; /* 0xc36c */
    U_INTF_CHKSUM_V        INTF_CHKSUM_V                     ; /* 0xc370 */
    U_INTF1_CHKSUM_Y       INTF1_CHKSUM_Y                    ; /* 0xc374 */
    U_INTF1_CHKSUM_U       INTF1_CHKSUM_U                    ; /* 0xc378 */
    U_INTF1_CHKSUM_V       INTF1_CHKSUM_V                    ; /* 0xc37c */
    unsigned int           reserved_144[544]                     ; /* 0xc380~0xcbfc */
    U_HDATE_VERSION        HDATE_VERSION                     ; /* 0xcc00 */
    U_HDATE_EN             HDATE_EN                          ; /* 0xcc04 */
    U_HDATE_POLA_CTRL      HDATE_POLA_CTRL                   ; /* 0xcc08 */
    U_HDATE_VIDEO_FORMAT   HDATE_VIDEO_FORMAT                ; /* 0xcc0c */
    U_HDATE_STATE          HDATE_STATE                       ; /* 0xcc10 */
    U_HDATE_OUT_CTRL       HDATE_OUT_CTRL                    ; /* 0xcc14 */
    U_HDATE_SRC_13_COEF1   HDATE_SRC_13_COEF1                ; /* 0xcc18 */
    U_HDATE_SRC_13_COEF2   HDATE_SRC_13_COEF2                ; /* 0xcc1c */
    U_HDATE_SRC_13_COEF3   HDATE_SRC_13_COEF3                ; /* 0xcc20 */
    U_HDATE_SRC_13_COEF4   HDATE_SRC_13_COEF4                ; /* 0xcc24 */
    U_HDATE_SRC_13_COEF5   HDATE_SRC_13_COEF5                ; /* 0xcc28 */
    U_HDATE_SRC_13_COEF6   HDATE_SRC_13_COEF6                ; /* 0xcc2c */
    U_HDATE_SRC_13_COEF7   HDATE_SRC_13_COEF7                ; /* 0xcc30 */
    U_HDATE_SRC_13_COEF8   HDATE_SRC_13_COEF8                ; /* 0xcc34 */
    U_HDATE_SRC_13_COEF9   HDATE_SRC_13_COEF9                ; /* 0xcc38 */
    U_HDATE_SRC_13_COEF10   HDATE_SRC_13_COEF10              ; /* 0xcc3c */
    U_HDATE_SRC_13_COEF11   HDATE_SRC_13_COEF11              ; /* 0xcc40 */
    U_HDATE_SRC_13_COEF12   HDATE_SRC_13_COEF12              ; /* 0xcc44 */
    U_HDATE_SRC_13_COEF13   HDATE_SRC_13_COEF13              ; /* 0xcc48 */
    U_HDATE_SRC_24_COEF1   HDATE_SRC_24_COEF1                ; /* 0xcc4c */
    U_HDATE_SRC_24_COEF2   HDATE_SRC_24_COEF2                ; /* 0xcc50 */
    U_HDATE_SRC_24_COEF3   HDATE_SRC_24_COEF3                ; /* 0xcc54 */
    U_HDATE_SRC_24_COEF4   HDATE_SRC_24_COEF4                ; /* 0xcc58 */
    U_HDATE_SRC_24_COEF5   HDATE_SRC_24_COEF5                ; /* 0xcc5c */
    U_HDATE_SRC_24_COEF6   HDATE_SRC_24_COEF6                ; /* 0xcc60 */
    U_HDATE_SRC_24_COEF7   HDATE_SRC_24_COEF7                ; /* 0xcc64 */
    U_HDATE_SRC_24_COEF8   HDATE_SRC_24_COEF8                ; /* 0xcc68 */
    U_HDATE_SRC_24_COEF9   HDATE_SRC_24_COEF9                ; /* 0xcc6c */
    U_HDATE_SRC_24_COEF10   HDATE_SRC_24_COEF10              ; /* 0xcc70 */
    U_HDATE_SRC_24_COEF11   HDATE_SRC_24_COEF11              ; /* 0xcc74 */
    U_HDATE_SRC_24_COEF12   HDATE_SRC_24_COEF12              ; /* 0xcc78 */
    U_HDATE_SRC_24_COEF13   HDATE_SRC_24_COEF13              ; /* 0xcc7c */
    U_HDATE_CSC_COEF1      HDATE_CSC_COEF1                   ; /* 0xcc80 */
    U_HDATE_CSC_COEF2      HDATE_CSC_COEF2                   ; /* 0xcc84 */
    U_HDATE_CSC_COEF3      HDATE_CSC_COEF3                   ; /* 0xcc88 */
    U_HDATE_CSC_COEF4      HDATE_CSC_COEF4                   ; /* 0xcc8c */
    U_HDATE_CSC_COEF5      HDATE_CSC_COEF5                   ; /* 0xcc90 */
    unsigned int           reserved_145[3]                     ; /* 0xcc94~0xcc9c */
    U_HDATE_TEST           HDATE_TEST                        ; /* 0xcca0 */
    U_HDATE_VBI_CTRL       HDATE_VBI_CTRL                    ; /* 0xcca4 */
    U_HDATE_CGMSA_DATA     HDATE_CGMSA_DATA                  ; /* 0xcca8 */
    U_HDATE_CGMSB_H        HDATE_CGMSB_H                     ; /* 0xccac */
    U_HDATE_CGMSB_DATA1    HDATE_CGMSB_DATA1                 ; /* 0xccb0 */
    U_HDATE_CGMSB_DATA2    HDATE_CGMSB_DATA2                 ; /* 0xccb4 */
    U_HDATE_CGMSB_DATA3    HDATE_CGMSB_DATA3                 ; /* 0xccb8 */
    U_HDATE_CGMSB_DATA4    HDATE_CGMSB_DATA4                 ; /* 0xccbc */
    unsigned int           reserved_146[80]                     ; /* 0xccc0~0xcdfc */
    U_DATE_COEFF0          DATE_COEFF0                       ; /* 0xce00 */
    U_DATE_COEFF1          DATE_COEFF1                       ; /* 0xce04 */
    U_DATE_COEFF2          DATE_COEFF2                       ; /* 0xce08 */
    U_DATE_COEFF3          DATE_COEFF3                       ; /* 0xce0c */
    U_DATE_COEFF4          DATE_COEFF4                       ; /* 0xce10 */
    U_DATE_COEFF5          DATE_COEFF5                       ; /* 0xce14 */
    U_DATE_COEFF6          DATE_COEFF6                       ; /* 0xce18 */
    U_DATE_COEFF7          DATE_COEFF7                       ; /* 0xce1c */
    U_DATE_COEFF8          DATE_COEFF8                       ; /* 0xce20 */
    U_DATE_COEFF9          DATE_COEFF9                       ; /* 0xce24 */
    U_DATE_COEFF10         DATE_COEFF10                      ; /* 0xce28 */
    U_DATE_COEFF11         DATE_COEFF11                      ; /* 0xce2c */
    U_DATE_COEFF12         DATE_COEFF12                      ; /* 0xce30 */
    U_DATE_COEFF13         DATE_COEFF13                      ; /* 0xce34 */
    U_DATE_COEFF14         DATE_COEFF14                      ; /* 0xce38 */
    U_DATE_COEFF15         DATE_COEFF15                      ; /* 0xce3c */
    U_DATE_COEFF16         DATE_COEFF16                      ; /* 0xce40 */
    U_DATE_COEFF17         DATE_COEFF17                      ; /* 0xce44 */
    U_DATE_COEFF18         DATE_COEFF18                      ; /* 0xce48 */
    U_DATE_COEFF19         DATE_COEFF19                      ; /* 0xce4c */
    U_DATE_COEFF20         DATE_COEFF20                      ; /* 0xce50 */
    U_DATE_COEFF21         DATE_COEFF21                      ; /* 0xce54 */
    U_DATE_COEFF22         DATE_COEFF22                      ; /* 0xce58 */
    U_DATE_COEFF23         DATE_COEFF23                      ; /* 0xce5c */
    U_DATE_COEFF24         DATE_COEFF24                      ; /* 0xce60 */
    U_DATE_COEFF25         DATE_COEFF25                      ; /* 0xce64 */
    U_DATE_COEFF26         DATE_COEFF26                      ; /* 0xce68 */
    U_DATE_COEFF27         DATE_COEFF27                      ; /* 0xce6c */
    U_DATE_COEFF28         DATE_COEFF28                      ; /* 0xce70 */
    U_DATE_COEFF29         DATE_COEFF29                      ; /* 0xce74 */
    U_DATE_COEFF30         DATE_COEFF30                      ; /* 0xce78 */
    unsigned int           reserved_147                     ; /* 0xce7c */
    U_DATE_ISRMASK         DATE_ISRMASK                      ; /* 0xce80 */
    U_DATE_ISRSTATE        DATE_ISRSTATE                     ; /* 0xce84 */
    U_DATE_ISR             DATE_ISR                          ; /* 0xce88 */
    unsigned int           reserved_148                     ; /* 0xce8c */
    U_DATE_VERSION         DATE_VERSION                      ; /* 0xce90 */
    U_DATE_COEFF37         DATE_COEFF37                      ; /* 0xce94 */
    U_DATE_COEFF38         DATE_COEFF38                      ; /* 0xce98 */
    U_DATE_COEFF39         DATE_COEFF39                      ; /* 0xce9c */
    U_DATE_COEFF40         DATE_COEFF40                      ; /* 0xcea0 */
    U_DATE_COEFF41         DATE_COEFF41                      ; /* 0xcea4 */
    U_DATE_COEFF42         DATE_COEFF42                      ; /* 0xcea8 */
    unsigned int           reserved_149[5]                     ; /* 0xceac~0xcebc */
    U_DATE_DACDET1         DATE_DACDET1                      ; /* 0xcec0 */
    U_DATE_DACDET2         DATE_DACDET2                      ; /* 0xcec4 */
    U_DATE_COEFF50         DATE_COEFF50                      ; /* 0xcec8 */
    U_DATE_COEFF51         DATE_COEFF51                      ; /* 0xcecc */
    U_DATE_COEFF52         DATE_COEFF52                      ; /* 0xced0 */
    U_DATE_COEFF53         DATE_COEFF53                      ; /* 0xced4 */
    U_DATE_COEFF54         DATE_COEFF54                      ; /* 0xced8 */
    U_DATE_COEFF55         DATE_COEFF55                      ; /* 0xcedc */
    U_DATE_COEFF56         DATE_COEFF56                      ; /* 0xcee0 */
    U_DATE_COEFF57         DATE_COEFF57                      ; /* 0xcee4 */
    U_DATE_COEFF58         DATE_COEFF58                      ; /* 0xcee8 */
    U_DATE_COEFF59         DATE_COEFF59                      ; /* 0xceec */
    unsigned int           reserved_150[324]                     ; /* 0xcee0~0xd3fc */
    U_LVDS_CTRL            LVDS_CTRL                         ; /* 0xd400 */
    U_LVDS_SWAP0           LVDS_SWAP0                        ; /* 0xd404 */
    U_LVDS_SWAP1           LVDS_SWAP1                        ; /* 0xd408 */
    U_LVDS_SWAP2           LVDS_SWAP2                        ; /* 0xd40c */
    U_LVDS_PHYCTRL0        LVDS_PHYCTRL0                     ; /* 0xd410 */
    U_LVDS_PHYCTRL1        LVDS_PHYCTRL1                     ; /* 0xd414 */
    U_LVDS_PHYCTRL2        LVDS_PHYCTRL2                     ; /* 0xd418 */
    U_LVDS_SPHYSTAT        LVDS_SPHYSTAT                     ; /* 0xd41c */
    unsigned int           reserved_152[56]                     ; /* 0xd420~0xd4fc */
    U_VBO_CTRL             VBO_CTRL                          ; /* 0xd500 */
    U_VBO_PHYCTRL          VBO_PHYCTRL                       ; /* 0xd504 */
    U_VBO_PHYSTAT          VBO_PHYSTAT                       ; /* 0xd508 */
    unsigned int           reserved_153[61]                     ; /* 0xd50c~0xd5fc */
    U_PWM_CONTROL          PWM_CONTROL                       ; /* 0xd600 */
    U_DIMMING_PWM_DUTY     DIMMING_PWM_DUTY                  ; /* 0xd604 */
    U_PWM_FREQ             PWM_FREQ                          ; /* 0xd608 */
    U_PWM_M                PWM_M                             ; /* 0xd60c */
    U_PWM_P                PWM_P                             ; /* 0xd610 */
    U_PWM_Q                PWM_Q                             ; /* 0xd614 */
    unsigned int           reserved_154[2]                     ; /* 0xd618~0xd61c */
    U_LR_SYNC_CONTROL      LR_SYNC_CONTROL                   ; /* 0xd620 */
    U_LR_SYNC_M            LR_SYNC_M                         ; /* 0xd624 */
    unsigned int           reserved_155[6]                     ; /* 0xd628~0xd63c */
    U_LR_GLASS_CONTROL     LR_GLASS_CONTROL                  ; /* 0xd640 */
    U_LR_GLASS_M           LR_GLASS_M                        ; /* 0xd644 */
    unsigned int           reserved_156[6]                     ; /* 0xd648~0xd65c */
    U_PWM_1D1CONTROL       PWM_1D1CONTROL                    ; /* 0xd660 */
    U_DIMMING_PWM_1D1_DUTY   DIMMING_PWM_1D1_DUTY            ; /* 0xd664 */
    U_PWM_1D1_FREQ         PWM_1D1_FREQ                      ; /* 0xd668 */
    unsigned int           reserved_157[5]                     ; /* 0xd66c~0xd67c */
    U_PWM_1D2CONTROL       PWM_1D2CONTROL                    ; /* 0xd680 */
    U_DIMMING_PWM_1D2_DUTY   DIMMING_PWM_1D2_DUTY            ; /* 0xd684 */
    U_PWM_1D2_FREQ         PWM_1D2_FREQ                      ; /* 0xd688 */
    unsigned int           reserved_158[5]                     ; /* 0xd68c~0xd69c */
    U_PWM_1D3CONTROL       PWM_1D3CONTROL                    ; /* 0xd6a0 */
    U_DIMMING_PWM_1D3_DUTY   DIMMING_PWM_1D3_DUTY            ; /* 0xd6a4 */
    U_PWM_1D3_FREQ         PWM_1D3_FREQ                      ; /* 0xd6a8 */

} S_VDP_REGS_TYPE;

/* Declare the struct pointor of the module VDP */
extern S_VDP_REGS_TYPE *gopVDPAllReg;


#endif /* __C_UNION_DEFINE_H__ */
