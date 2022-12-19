//******************************************************************************
// Copyright     :  Copyright (C) 2014, Hisilicon Technologies Co., Ltd.
// File name     :  c_union_define_vpss.h
// Author        :  x57490
// Version       :  1.0
// Date          :  2014-08-25
// Description   :  Define all registers/tables for S40V200
// Others        :  Generated automatically by nManager V4.0
// History       :  x57490 2014-08-25 Create file
//******************************************************************************

#ifndef __C_UNION_DEFINE_VPSS_H__
#define __C_UNION_DEFINE_VPSS_H__

/* Define the union U_VPSS_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    vsd_en                : 1   ; /* [1]  */
        unsigned int    reserved_1            : 1   ; /* [2]  */
        unsigned int    vhd0_en               : 1   ; /* [3]  */
        unsigned int    reserved_2            : 1   ; /* [4]  */
        unsigned int    vc1_en                : 1   ; /* [5]  */
        unsigned int    chk_sum_en            : 1   ; /* [6]  */
        unsigned int    dei_en                : 1   ; /* [7]  */
        unsigned int    hsp_en                : 1   ; /* [8]  */
        unsigned int    dnr_en                : 1   ; /* [9]  */
        unsigned int    db_en                 : 1   ; /* [10]  */
        unsigned int    dr_en                 : 1   ; /* [11]  */
        unsigned int    two_pix_en            : 1   ; /* [12]  */
        unsigned int    str_det_en            : 1   ; /* [13] , add according to register datasheet. t00273561*/
        unsigned int    reserved_3            : 7   ; /* [20..14]  */
        unsigned int    rotate_angle          : 1   ; /* [21]  */
        unsigned int    rotate_en             : 1   ; /* [22]  */
        unsigned int    prot                  : 2   ; /* [24..23]  */
        unsigned int    ifmd_en               : 1   ; /* [25]  */
        unsigned int    iglb_en               : 1   ; /* [26]  */
        unsigned int    img_pro_mode          : 2   ; /* [28..27]  */
        unsigned int    bfield_first          : 1   ; /* [29]  */
        unsigned int    bfield_mode           : 1   ; /* [30]  */
        unsigned int    bfield                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CTRL;

/* Define the union U_VPSS_CTRL2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    vsd_format            : 4   ; /* [7..4]  */
        unsigned int    reserved_1            : 4   ; /* [11..8]  */
        unsigned int    vhd0_format           : 4   ; /* [15..12]  */
        unsigned int    in_format             : 5   ; /* [20..16]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    in_pix_bitw           : 1   ; /* [24]  */
        unsigned int    uv_invert             : 1   ; /* [25]  */
        unsigned int    reserved_3            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CTRL2;

/* Define the union U_VPSS_CTRL3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    zme_vsd_en            : 1   ; /* [1]  */
        unsigned int    reserved_1            : 1   ; /* [2]  */
        unsigned int    zme_vhd0_en           : 1   ; /* [3]  */
        unsigned int    vhd0_pre_vfir_mode    : 2   ; /* [5..4]  */
        unsigned int    vhd0_pre_vfir_en      : 1   ; /* [6]  */
        unsigned int    vhd0_pre_hfir_mode    : 2   ; /* [8..7]  */
        unsigned int    vhd0_pre_hfir_en      : 1   ; /* [9]  */
        unsigned int    vsd_pre_vfir_mode     : 2   ; /* [11..10]  */
        unsigned int    vsd_pre_vfir_en       : 1   ; /* [12]  */
        unsigned int    vsd_pre_hfir_mode     : 2   ; /* [14..13]  */
        unsigned int    vsd_pre_hfir_en       : 1   ; /* [15]  */
        unsigned int    in_crop_en            : 1   ; /* [16]  */
        unsigned int    vhd0_crop_en          : 1   ; /* [17]  */
        unsigned int    vsd_crop_en           : 1   ; /* [18]  */
        unsigned int    vsd_lba_en            : 1   ; /* [19]  */
        unsigned int    vhd0_lba_en           : 1   ; /* [20]  */
        unsigned int    reserved_2            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CTRL3;

/* Define the union U_VPSS_IMGSIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    imgwidth              : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    imgheight             : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_IMGSIZE;

/* Define the union U_VPSS_INCROP_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    in_crop_x             : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    in_crop_y             : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_INCROP_POS;

/* Define the union U_VPSS_INCROP_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    in_crop_width         : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    in_crop_height        : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_INCROP_SIZE;

/* Define the union U_VPSS_VHD0CROP_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_crop_x           : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_crop_y           : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0CROP_POS;

/* Define the union U_VPSS_VHD0CROP_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_crop_width       : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_crop_height      : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0CROP_SIZE;

/* Define the union U_VPSS_VSDCROP_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vsd_crop_x            : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vsd_crop_y            : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VSDCROP_POS;

/* Define the union U_VPSS_VSDCROP_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vsd_crop_width        : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vsd_crop_height       : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VSDCROP_SIZE;

/* Define the union U_VPSS_VHD0_ZMEORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_zme_ow           : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_zme_oh           : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_ZMEORESO;

/* Define the union U_VPSS_VSD_ZMEORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vsd_zme_ow            : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vsd_zme_oh            : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VSD_ZMEORESO;

/* Define the union U_VPSS_VHD0LBA_DSIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_lba_width        : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_lba_height       : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0LBA_DSIZE;

/* Define the union U_VPSS_VHD0LBA_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_lba_xfpos        : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_lba_yfpos        : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0LBA_VFPOS;

/* Define the union U_VPSS_VSDLBA_DSIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vsd_lba_width         : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vsd_lba_height        : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VSDLBA_DSIZE;

/* Define the union U_VPSS_VSDLBA_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vsd_lba_xfpos         : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vsd_lba_yfpos         : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VSDLBA_VFPOS;

/* Define the union U_VPSS_VHD0LBA_BK */
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

} U_VPSS_VHD0LBA_BK;

/* Define the union U_VPSS_VSDLBA_BK */
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

} U_VPSS_VSDLBA_BK;

/* Define the union U_STR_DET_VIDCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 30  ; /* [29..0]  */
        unsigned int    vid_mode              : 1   ; /* [30]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_STR_DET_VIDCTRL;

/* Define the union U_STR_DET_VIDBLKPOS0_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    blk0_xlpos            : 8   ; /* [7..0]  */
        unsigned int    blk0_ylpos            : 8   ; /* [15..8]  */
        unsigned int    blk1_xlpos            : 8   ; /* [23..16]  */
        unsigned int    blk1_ylpos            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_STR_DET_VIDBLKPOS0_1;

/* Define the union U_STR_DET_VIDBLKPOS2_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    blk2_xlpos            : 8   ; /* [7..0]  */
        unsigned int    blk2_ylpos            : 8   ; /* [15..8]  */
        unsigned int    blk3_xlpos            : 8   ; /* [23..16]  */
        unsigned int    blk3_ylpos            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_STR_DET_VIDBLKPOS2_3;

/* Define the union U_STR_DET_VIDBLKPOS4_5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    blk4_xlpos            : 8   ; /* [7..0]  */
        unsigned int    blk4_ylpos            : 8   ; /* [15..8]  */
        unsigned int    blk5_xlpos            : 8   ; /* [23..16]  */
        unsigned int    blk5_ylpos            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_STR_DET_VIDBLKPOS4_5;

/* Define the union U_VPSS_DR_CFG0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 16  ; /* [15..0]  */
        unsigned int    drthrmaxsimilarpixdiff : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 3   ; /* [23..21]  */
        unsigned int    drthrflat3x3zone      : 5   ; /* [28..24]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DR_CFG0;

/* Define the union U_VPSS_DR_CFG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dralphascale          : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 11  ; /* [15..5]  */
        unsigned int    drbetascale           : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 3   ; /* [23..21]  */
        unsigned int    dr_demo_en            : 1   ; /* [24]  */
        unsigned int    reserved_2            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DR_CFG1;

/* Define the union U_VPSS_DNR_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    thrintlcolcnt         : 4   ; /* [3..0]    */
        unsigned int    thrintlcnt            : 4   ; /* [7..4]    */
        unsigned int    thdmaxgrad            : 8   ; /* [15..8]   */
        unsigned int    thdcntrst8            : 8   ; /* [23..16]  */
        unsigned int    dnr_dither_en         : 1   ; /* [24]      */
        unsigned int    dnr_dither_mode       : 1   ; /* [25]      */
        unsigned int    reserved_0            : 6   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DNR_INFO;

/* Define the union U_VPSS_AXI_RID0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cury_rid              : 4   ; /* [3..0]    */
        unsigned int    curc_rid              : 4   ; /* [7..4]    */
        unsigned int    refy_rid              : 4   ; /* [11..8]   */
        unsigned int    refc_rid              : 4   ; /* [15..12]  */
        unsigned int    nx1y_rid              : 4   ; /* [19..16]  */
        unsigned int    nx1c_rid              : 4   ; /* [23..20]  */
        unsigned int    nx2y_rid              : 4   ; /* [27..24]  */
        unsigned int    nx2c_rid              : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_AXI_RID0;

/* Define the union U_VPSS_AXI_RID1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rst_rid               : 4   ; /* [3..0]  */
        unsigned int    cas_rid               : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_AXI_RID1;

/* Define the union U_VPSS_AXIID */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 20  ; /* [19..0]  */
        unsigned int    awid_cfg0             : 4   ; /* [23..20]  */
        unsigned int    reserved_1            : 4   ; /* [27..24]  */
        unsigned int    arid_cfg0             : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_AXIID;

/* Define the union U_VPSS_INTMASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    eof_mask              : 1   ; /* [0]  */
        unsigned int    timeout_mask          : 1   ; /* [1]  */
        unsigned int    bus_r_err_mask        : 1   ; /* [2]  */
        unsigned int    eof_end_mask          : 1   ; /* [3]  */
        unsigned int    bus_w_err_mask        : 1   ; /* [4]  */
        unsigned int    vhd0_tunl_mask        : 1   ; /* [5]  */
        unsigned int    vsd_tunl_mask         : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_INTMASK;

/* Define the union U_VPSS_CUR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    cur_tile_format       : 1   ; /* [4]  */
        unsigned int    cur_hor_offset        : 13  ; /* [17..5]  */
        unsigned int    cur_ver_offset        : 13  ; /* [30..18]  */
        unsigned int    cur_package422        : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CUR_CTRL;

/* Define the union U_VPSS_CURSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cury_stride           : 16  ; /* [15..0]  */
        unsigned int    curc_stride           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CURSTRIDE;

/* Define the union U_VPSS_CURSTRIDE_LB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cury_stride_lb        : 16  ; /* [15..0]  */
        unsigned int    curc_stride_lb        : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CURSTRIDE_LB;

/* Define the union U_VPSS_REF_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    ref_tile_format       : 1   ; /* [4]  */
        unsigned int    ref_hor_offset        : 13  ; /* [17..5]  */
        unsigned int    ref_ver_offset        : 13  ; /* [30..18]  */
        unsigned int    ref_package422        : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_REF_CTRL;

/* Define the union U_VPSS_REFSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    refy_stride           : 16  ; /* [15..0]  */
        unsigned int    refc_stride           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_REFSTRIDE;

/* Define the union U_VPSS_REFSTRIDE_LB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    refy_stride_lb        : 16  ; /* [15..0]  */
        unsigned int    refc_stride_lb        : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_REFSTRIDE_LB;

/* Define the union U_VPSS_NXT1_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    nxt1_tile_format      : 1   ; /* [4]  */
        unsigned int    nxt1_hor_offset       : 13  ; /* [17..5]  */
        unsigned int    nxt1_ver_offset       : 13  ; /* [30..18]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NXT1_CTRL;

/* Define the union U_VPSS_NXT1STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nxt1y_stride          : 16  ; /* [15..0]  */
        unsigned int    nxt1c_stride          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NXT1STRIDE;

/* Define the union U_VPSS_NXT1STRIDE_LB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nxt1y_stride_lb       : 16  ; /* [15..0]  */
        unsigned int    nxt1c_stride_lb       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NXT1STRIDE_LB;

/* Define the union U_VPSS_NXT2_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    nxt2_tile_format      : 1   ; /* [4]  */
        unsigned int    nxt2_hor_offset       : 13  ; /* [17..5]  */
        unsigned int    nxt2_ver_offset       : 13  ; /* [30..18]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NXT2_CTRL;

/* Define the union U_VPSS_NXT2STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nxt2y_stride          : 16  ; /* [15..0]  */
        unsigned int    nxt2c_stride          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NXT2STRIDE;

/* Define the union U_VPSS_NXT2STRIDE_LB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nxt2y_stride_lb       : 16  ; /* [15..0]  */
        unsigned int    nxt2c_stride_lb       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NXT2STRIDE_LB;

/* Define the union U_VPSS_VHD0CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    vhd0_mirror           : 1   ; /* [4]  */
        unsigned int    vhd0_flip             : 1   ; /* [5]  */
        unsigned int    vhd0_pix_bitw         : 1   ; /* [6]  */
        unsigned int    vhd0_dither_en        : 1   ; /* [7]  */
        unsigned int    vhd0_uv_invert        : 1   ; /* [8]  */
        unsigned int    vhd0_lcmp_en          : 1   ; /* [9]  */
        unsigned int    vhd0_dither_mode      : 1   ; /* [10]  */
        unsigned int    reserved_1            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0CTRL;

/* Define the union U_VPSS_VHD0SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_width            : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_height           : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0SIZE;

/* Define the union U_VPSS_VHD0STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0y_stride          : 16  ; /* [15..0]  */
        unsigned int    vhd0c_stride          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0STRIDE;

/* Define the union U_VPSS_VSDCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    vsd_mirror            : 1   ; /* [4]  */
        unsigned int    vsd_flip              : 1   ; /* [5]  */
        unsigned int    vsd_pix_bitw          : 1   ; /* [6]  */
        unsigned int    vsd_dither_en         : 1   ; /* [7]  */
        unsigned int    vsd_uv_invert         : 1   ; /* [8]  */
        unsigned int    reserved_1            : 1   ; /* [9]  */
        unsigned int    vsd_dither_mode       : 1   ; /* [10]  */
        unsigned int    reserved_2            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VSDCTRL;

/* Define the union U_VPSS_VSDSIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vsd_width             : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vsd_height            : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VSDSIZE;

/* Define the union U_VPSS_VSDSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vsdy_stride           : 16  ; /* [15..0]  */
        unsigned int    vsdc_stride           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VSDSTRIDE;

/* Define the union U_VPSS_STSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    st_stride             : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_STSTRIDE;

/* Define the union U_VPSS_TUNL_CTRL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
		unsigned int    vhd0_tunl_en 		  : 1  ; /* [0]  */
		unsigned int    reserved 		      : 1  ; /* [1]  */
		unsigned int    vsd_tunl_en 		  : 1  ; /* [2]  */
		unsigned int    read_tunl_en 		  : 1  ; /* [3]  */
        unsigned int    read_tunl_sel 		  : 2  ; /* [5..4]  */
        unsigned int    reserved1             : 2  ; /* [7..6]  */
        unsigned int    read_tunl_rd_interval : 8   ; /* [15..8]  */
        unsigned int    vhd0_tunl_finish_line : 13  ; /* [28..16]  */
        unsigned int    vhd0_tunl_mode        : 2   ; /* [30..29]  */
        unsigned int    reserved0             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TUNL_CTRL0;

/* Define the union U_VPSS_TUNL_CTRL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vsd_tunl_finish_line  : 13  ; /* [12..0]  */
        unsigned int    vsd_tunl_mode         : 2   ; /* [14..13]  */
        unsigned int    reserved              : 17   ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TUNL_CTRL1;

/* Define the union U_VPSS_START */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_START;

/* Define the union U_VPSS_INTSTATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    eof_state             : 1   ; /* [0]  */
        unsigned int    timeout_state         : 1   ; /* [1]  */
        unsigned int    bus_r_err             : 1   ; /* [2]  */
        unsigned int    eof_end_state         : 1   ; /* [3]  */
        unsigned int    bus_w_err             : 1   ; /* [4]  */
        unsigned int    vhd0_tunl_state       : 1   ; /* [5]  */
        unsigned int    vsd_tunl_state        : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_INTSTATE;

/* Define the union U_VPSS_INTCLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    eof_clr               : 1   ; /* [0]  */
        unsigned int    timeout_clr           : 1   ; /* [1]  */
        unsigned int    bus_r_err_clr         : 1   ; /* [2]  */
        unsigned int    eof_end_clr           : 1   ; /* [3]  */
        unsigned int    bus_w_err_clr         : 1   ; /* [4]  */
        unsigned int    vhd0_tunl_clr         : 1   ; /* [5]  */
        unsigned int    vsd_tunl_clr          : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_INTCLR;

/* Define the union U_VPSS_RAWINT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    raw_eof               : 1   ; /* [0]  */
        unsigned int    raw_timeout           : 1   ; /* [1]  */
        unsigned int    raw_bus_r_err         : 1   ; /* [2]  */
        unsigned int    raw_eof_end           : 1   ; /* [3]  */
        unsigned int    raw_bus_w_err         : 1   ; /* [4]  */
        unsigned int    raw_vhd0_tunl_state   : 1   ; /* [5]  */
        unsigned int    raw_vsd_tunl_state    : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_RAWINT;

/* Define the union U_VPSS_MISCELLANEOUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    routstanding          : 4   ; /* [3..0]  */
        unsigned int    woutstanding          : 4   ; /* [7..4]  */
        unsigned int    init_timer            : 16  ; /* [23..8]  */
        unsigned int    ck_gt_en              : 1   ; /* [24]  */
        unsigned int    ck_gt_en_calc         : 1   ; /* [25]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MISCELLANEOUS;

/* Define the union U_VPSS_VHD0_LCMP_YINFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    is_lossless           : 1   ; /* [0]  */
        unsigned int    cmp_mode              : 1   ; /* [1]  */
        unsigned int    dw_mode               : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_YINFO;

/* Define the union U_VPSS_VHD0_LCMP_YSIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_width           : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    frame_height          : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_YSIZE;

/* Define the union U_VPSS_VHD0_LCMP_YRCCFG0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mb_bits               : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    ri_bits               : 4   ; /* [19..16]  */
        unsigned int    reserved_1            : 4   ; /* [23..20]  */
        unsigned int    max_rg_comp_bits      : 5   ; /* [28..24]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_YRCCFG0;

/* Define the union U_VPSS_VHD0_LCMP_YRCCFG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_qp                : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 13  ; /* [15..3]  */
        unsigned int    sad_bits_ngain        : 2   ; /* [17..16]  */
        unsigned int    reserved_1            : 6   ; /* [23..18]  */
        unsigned int    rc_smth_ngain         : 2   ; /* [25..24]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_YRCCFG1;

/* Define the union U_VPSS_VHD0_LCMP_YRCCFG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smth_thr              : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    smth_pix_num_thr      : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    pix_diff_thr          : 8   ; /* [23..16]  */
        unsigned int    reserved_2            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_YRCCFG2;

/* Define the union U_VPSS_VHD0_LCMP_YRCCFG3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    adj_sad_thr           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    adj_sad_bit_thr       : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_YRCCFG3;

/* Define the union U_VPSS_VHD0_LCMP_YRCCFG4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    qp_chg1_bits_thr      : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    qp_chg2_bits_thr      : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_YRCCFG4;

/* Define the union U_VPSS_VHD0_LCMP_YRCCFG5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smth_qp0              : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 5   ; /* [7..3]  */
        unsigned int    smth_qp1              : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 5   ; /* [15..11]  */
        unsigned int    smth_lftbits_thr0     : 8   ; /* [23..16]  */
        unsigned int    smth_lftbits_thr1     : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_YRCCFG5;

/* Define the union U_VPSS_VHD0_LCMP_YMAXLEN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_row_len           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_YMAXLEN;

/* Define the union U_VPSS_VHD0_LCMP_CINFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    is_lossless           : 1   ; /* [0]  */
        unsigned int    cmp_mode              : 1   ; /* [1]  */
        unsigned int    dw_mode               : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_CINFO;

/* Define the union U_VPSS_VHD0_LCMP_CSIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_width           : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    frame_height          : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_CSIZE;

/* Define the union U_VPSS_VHD0_LCMP_CRCCFG0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mb_bits               : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    ri_bits               : 4   ; /* [19..16]  */
        unsigned int    reserved_1            : 4   ; /* [23..20]  */
        unsigned int    max_rg_comp_bits      : 5   ; /* [28..24]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_CRCCFG0;

/* Define the union U_VPSS_VHD0_LCMP_CRCCFG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_qp                : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 13  ; /* [15..3]  */
        unsigned int    sad_bits_ngain        : 2   ; /* [17..16]  */
        unsigned int    reserved_1            : 6   ; /* [23..18]  */
        unsigned int    rc_smth_ngain         : 2   ; /* [25..24]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_CRCCFG1;

/* Define the union U_VPSS_VHD0_LCMP_CRCCFG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smth_thr              : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    smth_pix_num_thr      : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    pix_diff_thr          : 8   ; /* [23..16]  */
        unsigned int    reserved_2            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_CRCCFG2;

/* Define the union U_VPSS_VHD0_LCMP_CRCCFG3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    adj_sad_thr           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    adj_sad_bit_thr       : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_CRCCFG3;

/* Define the union U_VPSS_VHD0_LCMP_CRCCFG4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    qp_chg1_bits_thr      : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    qp_chg2_bits_thr      : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_CRCCFG4;

/* Define the union U_VPSS_VHD0_LCMP_CRCCFG5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smth_qp0              : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 5   ; /* [7..3]  */
        unsigned int    smth_qp1              : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 5   ; /* [15..11]  */
        unsigned int    smth_lftbits_thr0     : 8   ; /* [23..16]  */
        unsigned int    smth_lftbits_thr1     : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_CRCCFG5;

/* Define the union U_VPSS_VHD0_LCMP_CMAXLEN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_row_len           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_LCMP_CMAXLEN;

/* Define the union U_VPSS_DIECTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    st_rst_value          : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 1   ; /* [16]  */
        unsigned int    die_rst               : 1   ; /* [17]  */
        unsigned int    reserved_1            : 6   ; /* [23..18]  */
        unsigned int    die_chmmode           : 2   ; /* [25..24]  */
        unsigned int    die_lmmode            : 2   ; /* [27..26]  */
        unsigned int    die_out_sel_c         : 1   ; /* [28]  */
        unsigned int    die_out_sel_l         : 1   ; /* [29]  */
        unsigned int    reserved_2            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIECTRL;

/* Define the union U_VPSS_DIELMA2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    recmode_frmfld_blend_mode : 1   ; /* [0]  */
        unsigned int    frame_motion_smooth_en : 1   ; /* [1]  */
        unsigned int    luma_scesdf_max       : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    motion_iir_en         : 1   ; /* [4]  */
        unsigned int    luma_mf_max           : 1   ; /* [5]  */
        unsigned int    chroma_mf_max         : 1   ; /* [6]  */
        unsigned int    rec_mode_en           : 1   ; /* [7]  */
        unsigned int    reserved_1            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIELMA2;

/* Define the union U_VPSS_DIEINTEN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    dir_inten_ver         : 4   ; /* [11..8]  */
        unsigned int    reserved_1            : 4   ; /* [15..12]  */
        unsigned int    ver_min_inten         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEINTEN;

/* Define the union U_VPSS_DIESCALE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    range_scale           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIESCALE;

/* Define the union U_VPSS_DIECHECK1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ck1_max_range         : 8   ; /* [7..0]  */
        unsigned int    ck1_range_gain        : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    ck1_gain              : 4   ; /* [19..16]  */
        unsigned int    reserved_1            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIECHECK1;

/* Define the union U_VPSS_DIECHECK2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ck2_max_range         : 8   ; /* [7..0]  */
        unsigned int    ck2_range_gain        : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    ck2_gain              : 4   ; /* [19..16]  */
        unsigned int    reserved_1            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIECHECK2;

/* Define the union U_VPSS_DIEDIR0_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir0_mult             : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    dir1_mult             : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    dir2_mult             : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    dir3_mult             : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEDIR0_3;

/* Define the union U_VPSS_DIEDIR4_7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir4_mult             : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    dir5_mult             : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    dir6_mult             : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    dir7_mult             : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEDIR4_7;

/* Define the union U_VPSS_DIEDIR8_11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir8_mult             : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    dir9_mult             : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    dir10_mult            : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    dir11_mult            : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEDIR8_11;

/* Define the union U_VPSS_DIEDIR12_14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir12_mult            : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    dir13_mult            : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    dir14_mult            : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEDIR12_14;

/* Define the union U_VPSS_DIESTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cur_state             : 4   ; /* [3..0]  */
        unsigned int    cur_cstate            : 4   ; /* [7..4]  */
        unsigned int    l_height_cnt          : 12  ; /* [19..8]  */
        unsigned int    c_height_cnt          : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIESTA;

/* Define the union U_VPSS_DIEINTPSCL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intp_scale_ratio_1    : 4   ; /* [3..0]  */
        unsigned int    intp_scale_ratio_2    : 4   ; /* [7..4]  */
        unsigned int    intp_scale_ratio_3    : 4   ; /* [11..8]  */
        unsigned int    intp_scale_ratio_4    : 4   ; /* [15..12]  */
        unsigned int    intp_scale_ratio_5    : 4   ; /* [19..16]  */
        unsigned int    intp_scale_ratio_6    : 4   ; /* [23..20]  */
        unsigned int    intp_scale_ratio_7    : 4   ; /* [27..24]  */
        unsigned int    intp_scale_ratio_8    : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEINTPSCL0;

/* Define the union U_VPSS_DIEINTPSCL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intp_scale_ratio_9    : 4   ; /* [3..0]  */
        unsigned int    intp_scale_ratio_10   : 4   ; /* [7..4]  */
        unsigned int    intp_scale_ratio_11   : 4   ; /* [11..8]  */
        unsigned int    intp_scale_ratio_12   : 4   ; /* [15..12]  */
        unsigned int    intp_scale_ratio_13   : 4   ; /* [19..16]  */
        unsigned int    intp_scale_ratio_14   : 4   ; /* [23..20]  */
        unsigned int    intp_scale_ratio_15   : 4   ; /* [27..24]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEINTPSCL1;

/* Define the union U_VPSS_DIEDIRTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bc_gain               : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    dir_thd               : 4   ; /* [11..8]  */
        unsigned int    edge_mode             : 1   ; /* [12]  */
        unsigned int    hor_edge_en           : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    strength_thd          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEDIRTHD;

/* Define the union U_VPSS_DIEJITMTN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    jitter_gain           : 4   ; /* [3..0]  */
        unsigned int    jitter_coring         : 8   ; /* [11..4]  */
        unsigned int    fld_motion_coring     : 8   ; /* [19..12]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEJITMTN;

/* Define the union U_VPSS_DIEFLDMTN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fld_motion_thd_low    : 8   ; /* [7..0]  */
        unsigned int    fld_motion_thd_high   : 8   ; /* [15..8]  */
        unsigned int    fld_motion_curve_slope : 6   ; /* [21..16]  */
        unsigned int    reserved_0            : 2   ; /* [23..22]  */
        unsigned int    fld_motion_gain       : 4   ; /* [27..24]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFLDMTN;

/* Define the union U_VPSS_DIEMTNDIFFTHD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_diff_thd_0     : 8   ; /* [7..0]  */
        unsigned int    motion_diff_thd_1     : 8   ; /* [15..8]  */
        unsigned int    motion_diff_thd_2     : 8   ; /* [23..16]  */
        unsigned int    motion_diff_thd_3     : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMTNDIFFTHD0;

/* Define the union U_VPSS_DIEMTNDIFFTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_diff_thd_4     : 8   ; /* [7..0]  */
        unsigned int    motion_diff_thd_5     : 8   ; /* [15..8]  */
        unsigned int    min_motion_iir_ratio  : 7   ; /* [22..16]  */
        unsigned int    reserved_0            : 1   ; /* [23]  */
        unsigned int    max_motion_iir_ratio  : 7   ; /* [30..24]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMTNDIFFTHD1;

/* Define the union U_VPSS_DIEMTNIIRSLP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_iir_curve_slope_0 : 6   ; /* [5..0]  */
        unsigned int    motion_iir_curve_slope_1 : 6   ; /* [11..6]  */
        unsigned int    motion_iir_curve_slope_2 : 6   ; /* [17..12]  */
        unsigned int    motion_iir_curve_slope_3 : 6   ; /* [23..18]  */
        unsigned int    motion_iir_curve_ratio_0 : 7   ; /* [30..24]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMTNIIRSLP;

/* Define the union U_VPSS_DIEMTNIIRRAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_iir_curve_ratio_1 : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    motion_iir_curve_ratio_2 : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    motion_iir_curve_ratio_3 : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    motion_iir_curve_ratio_4 : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMTNIIRRAT;

/* Define the union U_VPSS_DIEHISMODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rec_mode_fld_motion_step_0 : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    rec_mode_fld_motion_step_1 : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    rec_mode_frm_motion_step_0 : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 2   ; /* [11..10]  */
        unsigned int    rec_mode_frm_motion_step_1 : 2   ; /* [13..12]  */
        unsigned int    reserved_3            : 2   ; /* [15..14]  */
        unsigned int    ppre_info_en          : 1   ; /* [16]  */
        unsigned int    pre_info_en           : 1   ; /* [17]  */
        unsigned int    his_motion_en         : 1   ; /* [18]  */
        unsigned int    his_motion_using_mode : 1   ; /* [19]  */
        unsigned int    his_motion_write_mode : 1   ; /* [20]  */
        unsigned int    his_motion_info_write_mode : 1   ; /* [21]  */
        unsigned int    reserved_4            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEHISMODE;

/* Define the union U_VPSS_DIEMORFLT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mor_flt_thd           : 8   ; /* [7..0]  */
        unsigned int    mor_flt_size          : 2   ; /* [9..8]  */
        unsigned int    reserved_0            : 14  ; /* [23..10]  */
        unsigned int    mor_flt_en            : 1   ; /* [24]  */
        unsigned int    reserved_1            : 1   ; /* [25]  */
        unsigned int    med_blend_en          : 1   ; /* [26]  */
        unsigned int    reserved_2            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMORFLT;

/* Define the union U_VPSS_DIECOMBCHK0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    comb_chk_min_hthd     : 8   ; /* [7..0]  */
        unsigned int    comb_chk_min_vthd     : 8   ; /* [15..8]  */
        unsigned int    comb_chk_lower_limit  : 8   ; /* [23..16]  */
        unsigned int    comb_chk_upper_limit  : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIECOMBCHK0;

/* Define the union U_VPSS_DIECOMBCHK1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    comb_chk_edge_thd     : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    comb_chk_md_thd       : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    comb_chk_en           : 1   ; /* [16]  */
        unsigned int    reserved_2            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIECOMBCHK1;

/* Define the union U_VPSS_DIEFRMMTNSMTHTHD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_motion_smooth_thd0 : 8   ; /* [7..0]  */
        unsigned int    frame_motion_smooth_thd1 : 8   ; /* [15..8]  */
        unsigned int    frame_motion_smooth_thd2 : 8   ; /* [23..16]  */
        unsigned int    frame_motion_smooth_thd3 : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMMTNSMTHTHD0;

/* Define the union U_VPSS_DIEFRMMTNSMTHTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_motion_smooth_thd4 : 8   ; /* [7..0]  */
        unsigned int    frame_motion_smooth_thd5 : 8   ; /* [15..8]  */
        unsigned int    frame_motion_smooth_ratio_min : 7   ; /* [22..16]  */
        unsigned int    reserved_0            : 1   ; /* [23]  */
        unsigned int    frame_motion_smooth_ratio_max : 7   ; /* [30..24]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMMTNSMTHTHD1;

/* Define the union U_VPSS_DIEFRMMTNSMTHSLP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_motion_smooth_slope0 : 6   ; /* [5..0]  */
        unsigned int    frame_motion_smooth_slope1 : 6   ; /* [11..6]  */
        unsigned int    frame_motion_smooth_slope2 : 6   ; /* [17..12]  */
        unsigned int    frame_motion_smooth_slope3 : 6   ; /* [23..18]  */
        unsigned int    frame_motion_smooth_ratio0 : 7   ; /* [30..24]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMMTNSMTHSLP;

/* Define the union U_VPSS_DIEFRMMTNSMTHRAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_motion_smooth_ratio1 : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    frame_motion_smooth_ratio2 : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    frame_motion_smooth_ratio3 : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    frame_motion_smooth_ratio4 : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMMTNSMTHRAT;

/* Define the union U_VPSS_DIEFRMFLDBLENDTHD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_field_blend_thd0 : 8   ; /* [7..0]  */
        unsigned int    frame_field_blend_thd1 : 8   ; /* [15..8]  */
        unsigned int    frame_field_blend_thd2 : 8   ; /* [23..16]  */
        unsigned int    frame_field_blend_thd3 : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMFLDBLENDTHD0;

/* Define the union U_VPSS_DIEFRMFLDBLENDTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_field_blend_thd4 : 8   ; /* [7..0]  */
        unsigned int    frame_field_blend_thd5 : 8   ; /* [15..8]  */
        unsigned int    frame_field_blend_ratio_min : 7   ; /* [22..16]  */
        unsigned int    reserved_0            : 1   ; /* [23]  */
        unsigned int    frame_field_blend_ratio_max : 7   ; /* [30..24]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMFLDBLENDTHD1;

/* Define the union U_VPSS_DIEFRMFLDBLENDSLP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_field_blend_slope0 : 6   ; /* [5..0]  */
        unsigned int    frame_field_blend_slope1 : 6   ; /* [11..6]  */
        unsigned int    frame_field_blend_slope2 : 6   ; /* [17..12]  */
        unsigned int    frame_field_blend_slope3 : 6   ; /* [23..18]  */
        unsigned int    frame_field_blend_ratio0 : 7   ; /* [30..24]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMFLDBLENDSLP;

/* Define the union U_VPSS_DIEFRMFLDBLENDRAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_field_blend_ratio1 : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    frame_field_blend_ratio2 : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    frame_field_blend_ratio3 : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    frame_field_blend_ratio4 : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMFLDBLENDRAT;

/* Define the union U_VPSS_DIEMTNADJ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_adjust_gain    : 8   ; /* [7..0]  */
        unsigned int    motion_adjust_coring  : 6   ; /* [13..8]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    motion_adjust_gain_chr : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMTNADJ;

/* Define the union U_VPSS_DIEGLBMTNTHD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_thd0           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    motion_thd1           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEGLBMTNTHD0;

/* Define the union U_VPSS_DIEGLBMTNTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_thd2           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    motion_thd3           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEGLBMTNTHD1;

/* Define the union U_VPSS_CCRSCLR0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    no_ccr_detect_thd     : 10  ; /* [9..0]  */
        unsigned int    no_ccr_detect_max     : 10  ; /* [19..10]  */
        unsigned int    chroma_ma_offset      : 10  ; /* [29..20]  */
        unsigned int    chroma_ccr_en         : 1   ; /* [30]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CCRSCLR0;

/* Define the union U_VPSS_CCRSCLR1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_xchroma           : 10  ; /* [9..0]  */
        unsigned int    no_ccr_detect_blend   : 4   ; /* [13..10]  */
        unsigned int    similar_thd           : 9   ; /* [22..14]  */
        unsigned int    similar_max           : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CCRSCLR1;

/* Define the union U_VPSS_PDPHISTTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hist_thd0             : 8   ; /* [7..0]  */
        unsigned int    hist_thd1             : 8   ; /* [15..8]  */
        unsigned int    hist_thd2             : 8   ; /* [23..16]  */
        unsigned int    hist_thd3             : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDPHISTTHD1;

/* Define the union U_VPSS_PDPCCMOV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mov_coring_blk        : 8   ; /* [7..0]  */
        unsigned int    mov_coring_tkr        : 8   ; /* [15..8]  */
        unsigned int    mov_coring_norm       : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDPCCMOV;

/* Define the union U_VPSS_PDCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bitsmov2r             : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 16  ; /* [18..3]  */
        unsigned int    lasi_mode             : 1   ; /* [19]  */
        unsigned int    edge_smooth_ratio     : 8   ; /* [27..20]  */
        unsigned int    reserved_1            : 1   ; /* [28]  */
        unsigned int    dir_mch_c             : 1   ; /* [29]  */
        unsigned int    edge_smooth_en        : 1   ; /* [30]  */
        unsigned int    dir_mch_l             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDCTRL;

/* Define the union U_VPSS_PDBLKTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stillblk_thd          : 8   ; /* [7..0]  */
        unsigned int    diff_movblk_thd       : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDBLKTHD;

/* Define the union U_VPSS_PDHISTTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mon_tkr_thr           : 8   ; /* [7..0]  */
        unsigned int    mon_start_idx         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDHISTTHD;

/* Define the union U_VPSS_PDUMTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    um_thd0               : 8   ; /* [7..0]  */
        unsigned int    um_thd1               : 8   ; /* [15..8]  */
        unsigned int    um_thd2               : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDUMTHD;

/* Define the union U_VPSS_PDPCCCORING */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coring_tkr            : 8   ; /* [7..0]  */
        unsigned int    coring_norm           : 8   ; /* [15..8]  */
        unsigned int    coring_blk            : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDPCCCORING;

/* Define the union U_VPSS_PDPCCHTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pcc_hthd              : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDPCCHTHD;

/* Define the union U_VPSS_PDPCCVTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pcc_vthd0             : 8   ; /* [7..0]  */
        unsigned int    pcc_vthd1             : 8   ; /* [15..8]  */
        unsigned int    pcc_vthd2             : 8   ; /* [23..16]  */
        unsigned int    pcc_vthd3             : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDPCCVTHD;

/* Define the union U_VPSS_PDITDIFFVTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    itdiff_vthd0          : 8   ; /* [7..0]  */
        unsigned int    itdiff_vthd1          : 8   ; /* [15..8]  */
        unsigned int    itdiff_vthd2          : 8   ; /* [23..16]  */
        unsigned int    itdiff_vthd3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDITDIFFVTHD;

/* Define the union U_VPSS_PDLASITHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lasi_coring_thd       : 8   ; /* [7..0]  */
        unsigned int    lasi_edge_thd         : 8   ; /* [15..8]  */
        unsigned int    lasi_mov_thd          : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDLASITHD;

/* Define the union U_VPSS_PDLASIMODE0COEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lasi_txt_alpha        : 8   ; /* [7..0]  */
        unsigned int    lasi_txt_coring       : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDLASIMODE0COEF;

/* Define the union U_VPSS_PDLASIMODE1COEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lasi_txt_thd0         : 8   ; /* [7..0]  */
        unsigned int    lasi_txt_thd1         : 8   ; /* [15..8]  */
        unsigned int    lasi_txt_thd2         : 8   ; /* [23..16]  */
        unsigned int    lasi_txt_thd3         : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDLASIMODE1COEF;

/* Define the union U_VPSS_PDREGION */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    region1_y_end         : 12  ; /* [11..0]  */
        unsigned int    region1_y_stt         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDREGION;

/* Define the union U_VPSS_VHD0_HSP */
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

} U_VPSS_VHD0_HSP;

/* Define the union U_VPSS_VHD0_HLOFFSET */
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

} U_VPSS_VHD0_HLOFFSET;

/* Define the union U_VPSS_VHD0_HCOFFSET */
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

} U_VPSS_VHD0_HCOFFSET;

/* Define the union U_VPSS_VHD0_VSP */
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

} U_VPSS_VHD0_VSP;

/* Define the union U_VPSS_VHD0_VSR */
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

} U_VPSS_VHD0_VSR;

/* Define the union U_VPSS_VHD0_VOFFSET */
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

} U_VPSS_VHD0_VOFFSET;

/* Define the union U_VPSS_VSD_HSP */
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

} U_VPSS_VSD_HSP;

/* Define the union U_VPSS_VSD_HLOFFSET */
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

} U_VPSS_VSD_HLOFFSET;

/* Define the union U_VPSS_VSD_HCOFFSET */
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

} U_VPSS_VSD_HCOFFSET;

/* Define the union U_VPSS_VSD_VSP */
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

} U_VPSS_VSD_VSP;

/* Define the union U_VPSS_VSD_VSR */
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

} U_VPSS_VSD_VSR;

/* Define the union U_VPSS_VSD_VOFFSET */
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

} U_VPSS_VSD_VOFFSET;

/* Define the union U_VPSS_HSPCFG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsp_hf0_tmp0          : 8   ; /* [7..0]  */
        unsigned int    hsp_hf0_tmp1          : 8   ; /* [15..8]  */
        unsigned int    hsp_hf0_tmp2          : 8   ; /* [23..16]  */
        unsigned int    hsp_hf0_tmp3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HSPCFG1;

/* Define the union U_VPSS_HSPCFG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsp_hf0_coring        : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HSPCFG2;

/* Define the union U_VPSS_HSPCFG3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsp_hf0_gainpos       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    hsp_hf0_gainneg       : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HSPCFG3;

/* Define the union U_VPSS_HSPCFG4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsp_hf0_overth        : 8   ; /* [7..0]  */
        unsigned int    hsp_hf0_underth       : 8   ; /* [15..8]  */
        unsigned int    hsp_hf0_mixratio      : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 4   ; /* [27..24]  */
        unsigned int    hsp_hf0_winsize       : 3   ; /* [30..28]  */
        unsigned int    hsp_hf0_adpshoot_en   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HSPCFG4;

/* Define the union U_VPSS_HSPCFG5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsp_hf1_tmp0          : 8   ; /* [7..0]  */
        unsigned int    hsp_hf1_tmp1          : 8   ; /* [15..8]  */
        unsigned int    hsp_hf1_tmp2          : 8   ; /* [23..16]  */
        unsigned int    hsp_hf1_tmp3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HSPCFG5;

/* Define the union U_VPSS_HSPCFG6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsp_hf1_coring        : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HSPCFG6;

/* Define the union U_VPSS_HSPCFG7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsp_hf1_gainpos       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    hsp_hf1_gainneg       : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HSPCFG7;

/* Define the union U_VPSS_HSPCFG8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsp_hf1_overth        : 8   ; /* [7..0]  */
        unsigned int    hsp_hf1_underth       : 8   ; /* [15..8]  */
        unsigned int    hsp_hf1_mixratio      : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 4   ; /* [27..24]  */
        unsigned int    hsp_hf1_winsize       : 3   ; /* [30..28]  */
        unsigned int    hsp_hf1_adpshoot_en   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HSPCFG8;

/* Define the union U_VPSS_HSPCFG9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsp_cdti_gain         : 8   ; /* [7..0]  */
        unsigned int    hsp_ldti_gain         : 8   ; /* [15..8]  */
        unsigned int    hsp_lti_ratio         : 8   ; /* [23..16]  */
        unsigned int    hsp_hf_shootdiv       : 3   ; /* [26..24]  */
        unsigned int    reserved_0            : 1   ; /* [27]  */
        unsigned int    hsp_ctih_en           : 1   ; /* [28]  */
        unsigned int    hsp_ltih_en           : 1   ; /* [29]  */
        unsigned int    hsp_h1_en             : 1   ; /* [30]  */
        unsigned int    hsp_h0_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HSPCFG9;

/* Define the union U_VPSS_HSPCFG10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsp_glb_underth       : 9   ; /* [8..0]  */
        unsigned int    hsp_mk_en             : 1   ; /* [9]  */
        unsigned int    hsp_glb_overth        : 9   ; /* [18..10]  */
        unsigned int    hsp_mk_mode           : 1   ; /* [19]  */
        unsigned int    hsp_peak_ratio        : 8   ; /* [27..20]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HSPCFG10;

/* Define the union U_VPSS_DR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    enep                  : 1   ; /* [0]  */
        unsigned int    enovt                 : 4   ; /* [4..1]  */
        unsigned int    enstradjstbylm        : 1   ; /* [5]  */
        unsigned int    enangadjstbylm        : 1   ; /* [6]  */
        unsigned int    clipmode              : 1   ; /* [7]  */
        unsigned int    demo_en               : 1   ; /* [8]  */
        unsigned int    demo_mode             : 1   ; /* [9]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DR_CTRL;

/* Define the union U_VPSS_DR_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regthrmdfangctrst     : 4   ; /* [3..0]  */
        unsigned int    regthrovshtminang     : 4   ; /* [7..4]  */
        unsigned int    regdrstrenth          : 5   ; /* [12..8]  */
        unsigned int    regovtstrenth         : 3   ; /* [15..13]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DR_THR;

/* Define the union U_VPSS_DRLSWSTRLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lswstrlut00           : 5   ; /* [4..0]  */
        unsigned int    lswstrlut10           : 5   ; /* [9..5]  */
        unsigned int    lswstrlut20           : 5   ; /* [14..10]  */
        unsigned int    lswstrlut30           : 5   ; /* [19..15]  */
        unsigned int    lswstrlut40           : 5   ; /* [24..20]  */
        unsigned int    lswstrlut50           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRLUT0;

/* Define the union U_VPSS_DRLSWSTRLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lswstrlut01           : 5   ; /* [4..0]  */
        unsigned int    lswstrlut11           : 5   ; /* [9..5]  */
        unsigned int    lswstrlut21           : 5   ; /* [14..10]  */
        unsigned int    lswstrlut31           : 5   ; /* [19..15]  */
        unsigned int    lswstrlut41           : 5   ; /* [24..20]  */
        unsigned int    lswstrlut51           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRLUT1;

/* Define the union U_VPSS_DRLSWSTRLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lswstrlut02           : 5   ; /* [4..0]  */
        unsigned int    lswstrlut12           : 5   ; /* [9..5]  */
        unsigned int    lswstrlut22           : 5   ; /* [14..10]  */
        unsigned int    lswstrlut32           : 5   ; /* [19..15]  */
        unsigned int    lswstrlut42           : 5   ; /* [24..20]  */
        unsigned int    lswstrlut52           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRLUT2;

/* Define the union U_VPSS_DRLSWSTRLUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lswstrlut03           : 5   ; /* [4..0]  */
        unsigned int    lswstrlut13           : 5   ; /* [9..5]  */
        unsigned int    lswstrlut23           : 5   ; /* [14..10]  */
        unsigned int    lswstrlut33           : 5   ; /* [19..15]  */
        unsigned int    lswstrlut43           : 5   ; /* [24..20]  */
        unsigned int    lswstrlut53           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRLUT3;

/* Define the union U_VPSS_DRLSWSTRLUT4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lswstrlut04           : 5   ; /* [4..0]  */
        unsigned int    lswstrlut14           : 5   ; /* [9..5]  */
        unsigned int    lswstrlut24           : 5   ; /* [14..10]  */
        unsigned int    lswstrlut34           : 5   ; /* [19..15]  */
        unsigned int    lswstrlut44           : 5   ; /* [24..20]  */
        unsigned int    lswstrlut54           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRLUT4;

/* Define the union U_VPSS_DRLSWSTRLUT5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lswstrlut05           : 5   ; /* [4..0]  */
        unsigned int    lswstrlut15           : 5   ; /* [9..5]  */
        unsigned int    lswstrlut25           : 5   ; /* [14..10]  */
        unsigned int    lswstrlut35           : 5   ; /* [19..15]  */
        unsigned int    lswstrlut45           : 5   ; /* [24..20]  */
        unsigned int    lswstrlut55           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRLUT5;

/* Define the union U_VPSS_DRLSWSTRLUT6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lswstrlut06           : 5   ; /* [4..0]  */
        unsigned int    lswstrlut16           : 5   ; /* [9..5]  */
        unsigned int    lswstrlut26           : 5   ; /* [14..10]  */
        unsigned int    lswstrlut36           : 5   ; /* [19..15]  */
        unsigned int    lswstrlut46           : 5   ; /* [24..20]  */
        unsigned int    lswstrlut56           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRLUT6;

/* Define the union U_VPSS_DRLSWSTRLUT7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lswstrlut07           : 5   ; /* [4..0]  */
        unsigned int    lswstrlut17           : 5   ; /* [9..5]  */
        unsigned int    lswstrlut27           : 5   ; /* [14..10]  */
        unsigned int    lswstrlut37           : 5   ; /* [19..15]  */
        unsigned int    lswstrlut47           : 5   ; /* [24..20]  */
        unsigned int    lswstrlut57           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRLUT7;

/* Define the union U_VPSS_DRLSWSTRLUT8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lswstrlut08           : 5   ; /* [4..0]  */
        unsigned int    lswstrlut18           : 5   ; /* [9..5]  */
        unsigned int    lswstrlut28           : 5   ; /* [14..10]  */
        unsigned int    lswstrlut38           : 5   ; /* [19..15]  */
        unsigned int    lswstrlut48           : 5   ; /* [24..20]  */
        unsigned int    lswstrlut58           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRLUT8;

/* Define the union U_VPSS_DRLRWSTRLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lrwstrlut00           : 5   ; /* [4..0]  */
        unsigned int    lrwstrlut10           : 5   ; /* [9..5]  */
        unsigned int    lrwstrlut20           : 5   ; /* [14..10]  */
        unsigned int    lrwstrlut30           : 5   ; /* [19..15]  */
        unsigned int    lrwstrlut40           : 5   ; /* [24..20]  */
        unsigned int    lrwstrlut50           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRLUT0;

/* Define the union U_VPSS_DRLRWSTRLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lrwstrlut01           : 5   ; /* [4..0]  */
        unsigned int    lrwstrlut11           : 5   ; /* [9..5]  */
        unsigned int    lrwstrlut21           : 5   ; /* [14..10]  */
        unsigned int    lrwstrlut31           : 5   ; /* [19..15]  */
        unsigned int    lrwstrlut41           : 5   ; /* [24..20]  */
        unsigned int    lrwstrlut51           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRLUT1;

/* Define the union U_VPSS_DRLRWSTRLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lrwstrlut02           : 5   ; /* [4..0]  */
        unsigned int    lrwstrlut12           : 5   ; /* [9..5]  */
        unsigned int    lrwstrlut22           : 5   ; /* [14..10]  */
        unsigned int    lrwstrlut32           : 5   ; /* [19..15]  */
        unsigned int    lrwstrlut42           : 5   ; /* [24..20]  */
        unsigned int    lrwstrlut52           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRLUT2;

/* Define the union U_VPSS_DRLRWSTRLUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lrwstrlut03           : 5   ; /* [4..0]  */
        unsigned int    lrwstrlut13           : 5   ; /* [9..5]  */
        unsigned int    lrwstrlut23           : 5   ; /* [14..10]  */
        unsigned int    lrwstrlut33           : 5   ; /* [19..15]  */
        unsigned int    lrwstrlut43           : 5   ; /* [24..20]  */
        unsigned int    lrwstrlut53           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRLUT3;

/* Define the union U_VPSS_DRLRWSTRLUT4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lrwstrlut04           : 5   ; /* [4..0]  */
        unsigned int    lrwstrlut14           : 5   ; /* [9..5]  */
        unsigned int    lrwstrlut24           : 5   ; /* [14..10]  */
        unsigned int    lrwstrlut34           : 5   ; /* [19..15]  */
        unsigned int    lrwstrlut44           : 5   ; /* [24..20]  */
        unsigned int    lrwstrlut54           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRLUT4;

/* Define the union U_VPSS_DRLRWSTRLUT5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lrwstrlut05           : 5   ; /* [4..0]  */
        unsigned int    lrwstrlut15           : 5   ; /* [9..5]  */
        unsigned int    lrwstrlut25           : 5   ; /* [14..10]  */
        unsigned int    lrwstrlut35           : 5   ; /* [19..15]  */
        unsigned int    lrwstrlut45           : 5   ; /* [24..20]  */
        unsigned int    lrwstrlut55           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRLUT5;

/* Define the union U_VPSS_DRLRWSTRLUT6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lrwstrlut06           : 5   ; /* [4..0]  */
        unsigned int    lrwstrlut16           : 5   ; /* [9..5]  */
        unsigned int    lrwstrlut26           : 5   ; /* [14..10]  */
        unsigned int    lrwstrlut36           : 5   ; /* [19..15]  */
        unsigned int    lrwstrlut46           : 5   ; /* [24..20]  */
        unsigned int    lrwstrlut56           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRLUT6;

/* Define the union U_VPSS_DRLRWSTRLUT7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lrwstrlut07           : 5   ; /* [4..0]  */
        unsigned int    lrwstrlut17           : 5   ; /* [9..5]  */
        unsigned int    lrwstrlut27           : 5   ; /* [14..10]  */
        unsigned int    lrwstrlut37           : 5   ; /* [19..15]  */
        unsigned int    lrwstrlut47           : 5   ; /* [24..20]  */
        unsigned int    lrwstrlut57           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRLUT7;

/* Define the union U_VPSS_DRLRWSTRLUT8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lrwstrlut08           : 5   ; /* [4..0]  */
        unsigned int    lrwstrlut18           : 5   ; /* [9..5]  */
        unsigned int    lrwstrlut28           : 5   ; /* [14..10]  */
        unsigned int    lrwstrlut38           : 5   ; /* [19..15]  */
        unsigned int    lrwstrlut48           : 5   ; /* [24..20]  */
        unsigned int    lrwstrlut58           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRLUT8;

/* Define the union U_VPSS_DRLSWSTRADJUSTLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_lswadjlut0         : 4   ; /* [3..0]  */
        unsigned int    dr_lswadjlut1         : 4   ; /* [7..4]  */
        unsigned int    dr_lswadjlut2         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRADJUSTLUT0;

/* Define the union U_VPSS_DRLSWSTRADJUSTLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_lswadjlut3         : 4   ; /* [3..0]  */
        unsigned int    dr_lswadjlut4         : 4   ; /* [7..4]  */
        unsigned int    dr_lswadjlut5         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRADJUSTLUT1;

/* Define the union U_VPSS_DRLSWSTRADJUSTLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_lswadjlut6         : 4   ; /* [3..0]  */
        unsigned int    dr_lswadjlut7         : 4   ; /* [7..4]  */
        unsigned int    dr_lswadjlut8         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLSWSTRADJUSTLUT2;

/* Define the union U_VPSS_DRLRWSTRADJUSTLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_lrwadjlut0         : 4   ; /* [3..0]  */
        unsigned int    dr_lrwadjlut1         : 4   ; /* [7..4]  */
        unsigned int    dr_lrwadjlut2         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRADJUSTLUT0;

/* Define the union U_VPSS_DRLRWSTRADJUSTLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_lrwadjlut3         : 4   ; /* [3..0]  */
        unsigned int    dr_lrwadjlut4         : 4   ; /* [7..4]  */
        unsigned int    dr_lrwadjlut5         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRADJUSTLUT1;

/* Define the union U_VPSS_DRLRWSTRADJUSTLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_lrwadjlut6         : 4   ; /* [3..0]  */
        unsigned int    dr_lrwadjlut7         : 4   ; /* [7..4]  */
        unsigned int    dr_lrwadjlut8         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRLRWSTRADJUSTLUT2;

/* Define the union U_VPSS_DRANGADJSUTLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_angadjlut0         : 4   ; /* [3..0]  */
        unsigned int    dr_angadjlut1         : 4   ; /* [7..4]  */
        unsigned int    dr_angadjlut2         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRANGADJSUTLUT0;

/* Define the union U_VPSS_DRANGADJSUTLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_angadjlut3         : 4   ; /* [3..0]  */
        unsigned int    dr_angadjlut4         : 4   ; /* [7..4]  */
        unsigned int    dr_angadjlut5         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRANGADJSUTLUT1;

/* Define the union U_VPSS_DRANGADJSUTLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_angadjlut6         : 4   ; /* [3..0]  */
        unsigned int    dr_angadjlut7         : 4   ; /* [7..4]  */
        unsigned int    dr_angadjlut8         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRANGADJSUTLUT2;

/* Define the union U_VPSS_DRANGLESTRLUT1_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_angdifflut0        : 5   ; /* [4..0]  */
        unsigned int    dr_angdifflut1        : 5   ; /* [9..5]  */
        unsigned int    dr_angdifflut2        : 5   ; /* [14..10]  */
        unsigned int    dr_angdifflut3        : 5   ; /* [19..15]  */
        unsigned int    dr_angdifflut4        : 5   ; /* [24..20]  */
        unsigned int    dr_angdifflut5        : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRANGLESTRLUT1_0;

/* Define the union U_VPSS_DRANGLESTRLUT1_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_angdifflut6        : 5   ; /* [4..0]  */
        unsigned int    dr_angdifflut7        : 5   ; /* [9..5]  */
        unsigned int    dr_angdifflut8        : 5   ; /* [14..10]  */
        unsigned int    dr_angdifflut9        : 5   ; /* [19..15]  */
        unsigned int    dr_angdifflut10       : 5   ; /* [24..20]  */
        unsigned int    dr_angdifflut11       : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRANGLESTRLUT1_1;

/* Define the union U_VPSS_DRANGLESTRLUT1_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_angdifflut12       : 5   ; /* [4..0]  */
        unsigned int    dr_angdifflut13       : 5   ; /* [9..5]  */
        unsigned int    dr_angdifflut14       : 5   ; /* [14..10]  */
        unsigned int    dr_angdifflut15       : 5   ; /* [19..15]  */
        unsigned int    dr_angdifflut16       : 5   ; /* [24..20]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRANGLESTRLUT1_2;

/* Define the union U_VPSS_DRANGLESTRLUT2_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_angminlut0         : 5   ; /* [4..0]  */
        unsigned int    dr_angminlut1         : 5   ; /* [9..5]  */
        unsigned int    dr_angminlut2         : 5   ; /* [14..10]  */
        unsigned int    dr_angminlut3         : 5   ; /* [19..15]  */
        unsigned int    dr_angminlut4         : 5   ; /* [24..20]  */
        unsigned int    dr_angminlut5         : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRANGLESTRLUT2_0;

/* Define the union U_VPSS_DRANGLESTRLUT2_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_angminlut6         : 5   ; /* [4..0]  */
        unsigned int    dr_angminlut7         : 5   ; /* [9..5]  */
        unsigned int    dr_angminlut8         : 5   ; /* [14..10]  */
        unsigned int    dr_angminlut9         : 5   ; /* [19..15]  */
        unsigned int    dr_angminlut10        : 5   ; /* [24..20]  */
        unsigned int    dr_angminlut11        : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRANGLESTRLUT2_1;

/* Define the union U_VPSS_DRANGLESTRLUT2_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_angminlut12        : 5   ; /* [4..0]  */
        unsigned int    dr_angminlut13        : 5   ; /* [9..5]  */
        unsigned int    dr_angminlut14        : 5   ; /* [14..10]  */
        unsigned int    dr_angminlut15        : 5   ; /* [19..15]  */
        unsigned int    dr_angminlut16        : 5   ; /* [24..20]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DRANGLESTRLUT2_2;

/* Define the union U_VPSS_DROVTSTRADJUSTLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_ovadjlut0          : 4   ; /* [3..0]  */
        unsigned int    dr_ovadjlut1          : 4   ; /* [7..4]  */
        unsigned int    dr_ovadjlut2          : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DROVTSTRADJUSTLUT0;

/* Define the union U_VPSS_DROVTSTRADJUSTLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_ovadjlut3          : 4   ; /* [3..0]  */
        unsigned int    dr_ovadjlut4          : 4   ; /* [7..4]  */
        unsigned int    dr_ovadjlut5          : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DROVTSTRADJUSTLUT1;

/* Define the union U_VPSS_DROVTSTRADJUSTLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_ovadjlut6          : 4   ; /* [3..0]  */
        unsigned int    dr_ovadjlut7          : 4   ; /* [7..4]  */
        unsigned int    dr_ovadjlut8          : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DROVTSTRADJUSTLUT2;

/* Define the union U_VPSS_DROVTSTRLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_ovstrlut0          : 4   ; /* [3..0]  */
        unsigned int    dr_ovstrlut1          : 4   ; /* [7..4]  */
        unsigned int    dr_ovstrlut2          : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DROVTSTRLUT0;

/* Define the union U_VPSS_DROVTSTRLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_ovstrlut3          : 4   ; /* [3..0]  */
        unsigned int    dr_ovstrlut4          : 4   ; /* [7..4]  */
        unsigned int    dr_ovstrlut5          : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DROVTSTRLUT1;

/* Define the union U_VPSS_DROVTSTRLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dr_ovstrlut6          : 4   ; /* [3..0]  */
        unsigned int    dr_ovstrlut7          : 4   ; /* [7..4]  */
        unsigned int    dr_ovstrlut8          : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DROVTSTRLUT2;

/* Define the union U_VPSS_VC1_CTRL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fr0_vc1_profile       : 2   ; /* [1..0]  */
        unsigned int    fr0_vc1_rangedfrm     : 1   ; /* [2]  */
        unsigned int    fr0_vc1_mapyflg       : 1   ; /* [3]  */
        unsigned int    fr0_vc1_mapcflg       : 1   ; /* [4]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    fr0_vc1_mapy          : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    fr0_vc1_mapc          : 3   ; /* [14..12]  */
        unsigned int    reserved_2            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VC1_CTRL0;

/* Define the union U_VPSS_VC1_CTRL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fr1_vc1_profile       : 2   ; /* [1..0]  */
        unsigned int    fr1_vc1_rangedfrm     : 1   ; /* [2]  */
        unsigned int    fr1_vc1_mapyflg       : 1   ; /* [3]  */
        unsigned int    fr1_vc1_mapcflg       : 1   ; /* [4]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    fr1_vc1_mapy          : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    fr1_vc1_mapc          : 3   ; /* [14..12]  */
        unsigned int    reserved_2            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VC1_CTRL1;

/* Define the union U_VPSS_VC1_CTRL2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fr2_vc1_profile       : 2   ; /* [1..0]  */
        unsigned int    fr2_vc1_rangedfrm     : 1   ; /* [2]  */
        unsigned int    fr2_vc1_mapyflg       : 1   ; /* [3]  */
        unsigned int    fr2_vc1_mapcflg       : 1   ; /* [4]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    fr2_vc1_mapy          : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    fr2_vc1_mapc          : 3   ; /* [14..12]  */
        unsigned int    reserved_2            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VC1_CTRL2;

/* Define the union U_VPSS_VC1_CTRL3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fr3_vc1_profile       : 2   ; /* [1..0]  */
        unsigned int    fr3_vc1_rangedfrm     : 1   ; /* [2]  */
        unsigned int    fr3_vc1_mapyflg       : 1   ; /* [3]  */
        unsigned int    fr3_vc1_mapcflg       : 1   ; /* [4]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    fr3_vc1_mapy          : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    fr3_vc1_mapc          : 3   ; /* [14..12]  */
        unsigned int    reserved_2            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VC1_CTRL3;

/* Define the union U_VPSS_DB_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_lum_en             : 1   ; /* [0]  */
        unsigned int    db_lum_ver_en         : 1   ; /* [1]  */
        unsigned int    db_lum_hor_en         : 1   ; /* [2]  */
        unsigned int    db_cb_en              : 1   ; /* [3]  */
        unsigned int    db_cr_en              : 1   ; /* [4]  */
        unsigned int    db_chr_ver_en         : 1   ; /* [5]  */
        unsigned int    db_chr_hor_en         : 1   ; /* [6]  */
        unsigned int    db_chr_hor_mid_grey_en : 1   ; /* [7]  */
        unsigned int    reserved_0            : 2   ; /* [9..8]  */
        unsigned int    db_demo_en            : 1   ; /* [10]  */
        unsigned int    db_demo_mode          : 1   ; /* [11]  */
        unsigned int    det_size_en           : 1   ; /* [12]  */
        unsigned int    det_hy_en             : 1   ; /* [13]  */
        unsigned int    det_hc_en             : 1   ; /* [14]  */
        unsigned int    det_vy_en             : 1   ; /* [15]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_CTRL;

/* Define the union U_VPSS_DB_DIR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    grad_sub_ratio        : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    ctrst_thresh          : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_DIR;

/* Define the union U_VPSS_DB_BLK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_h_blk_size        : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    lum_v_blk_size        : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    chr_h_blk_size        : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    chr_v_blk_size        : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_BLK;

/* Define the union U_VPSS_DB_RATIO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_hor_scale_ratio   : 2   ; /* [1..0]  */
        unsigned int    lum_ver_scale_ratio   : 2   ; /* [3..2]  */
        unsigned int    chr_hor_scale_ratio   : 2   ; /* [5..4]  */
        unsigned int    chr_ver_scale_ratio   : 2   ; /* [7..6]  */
        unsigned int    lum_hor_filter_sel    : 2   ; /* [9..8]  */
        unsigned int    chr_hor_filter_sel    : 2   ; /* [11..10]  */
        unsigned int    glabal_db_strenth_lum : 4   ; /* [15..12]  */
        unsigned int    glabal_db_strenth_chr : 4   ; /* [19..16]  */
        unsigned int    lum_hor_txt_win_size  : 2   ; /* [21..20]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_RATIO;

/* Define the union U_VPSS_DB_LHHF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_hor_hf_diff_core  : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    lum_hor_hf_diff_gain1 : 4   ; /* [11..8]  */
        unsigned int    lum_hor_hf_diff_gain2 : 4   ; /* [15..12]  */
        unsigned int    lum_hor_hf_var_core   : 5   ; /* [20..16]  */
        unsigned int    lum_hor_bord_adj_gain : 3   ; /* [23..21]  */
        unsigned int    lum_hor_hf_var_gain1  : 4   ; /* [27..24]  */
        unsigned int    lum_hor_hf_var_gain2  : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LHHF;

/* Define the union U_VPSS_DB_LVHF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_ver_hf_var_core   : 5   ; /* [4..0]  */
        unsigned int    lum_ver_bord_adj_gain : 3   ; /* [7..5]  */
        unsigned int    lum_ver_hf_var_gain1  : 4   ; /* [11..8]  */
        unsigned int    lum_ver_hf_var_gain2  : 4   ; /* [15..12]  */
        unsigned int    lum_hor_adj_gain      : 5   ; /* [20..16]  */
        unsigned int    reserved_0            : 3   ; /* [23..21]  */
        unsigned int    lum_ver_adj_gain      : 5   ; /* [28..24]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LVHF;

/* Define the union U_VPSS_DB_CTRS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ctrst_adj_core        : 5   ; /* [4..0]  */
        unsigned int    dir_smooth_mode       : 2   ; /* [6..5]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    ctrst_adj_gain1       : 4   ; /* [11..8]  */
        unsigned int    ctrst_adj_gain2       : 4   ; /* [15..12]  */
        unsigned int    max_lum_hor_db_dist   : 4   ; /* [19..16]  */
        unsigned int    max_chr_hor_db_dist   : 4   ; /* [23..20]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_CTRS;

/* Define the union U_VPSS_DB_LUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_hor_delta_lut_p0  : 4   ; /* [3..0]  */
        unsigned int    lum_hor_delta_lut_p1  : 4   ; /* [7..4]  */
        unsigned int    lum_hor_delta_lut_p2  : 4   ; /* [11..8]  */
        unsigned int    lum_hor_delta_lut_p3  : 4   ; /* [15..12]  */
        unsigned int    lum_hor_delta_lut_p4  : 4   ; /* [19..16]  */
        unsigned int    lum_hor_delta_lut_p5  : 4   ; /* [23..20]  */
        unsigned int    lum_hor_delta_lut_p6  : 4   ; /* [27..24]  */
        unsigned int    lum_hor_delta_lut_p7  : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT0;

/* Define the union U_VPSS_DB_LUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_hor_delta_lut_p8  : 4   ; /* [3..0]  */
        unsigned int    lum_hor_delta_lut_p9  : 4   ; /* [7..4]  */
        unsigned int    lum_hor_delta_lut_p10 : 4   ; /* [11..8]  */
        unsigned int    lum_hor_delta_lut_p11 : 4   ; /* [15..12]  */
        unsigned int    lum_hor_delta_lut_p12 : 4   ; /* [19..16]  */
        unsigned int    lum_hor_delta_lut_p13 : 4   ; /* [23..20]  */
        unsigned int    lum_hor_delta_lut_p14 : 4   ; /* [27..24]  */
        unsigned int    lum_hor_delta_lut_p15 : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT1;

/* Define the union U_VPSS_DB_LUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_ver_delta_lut_p0  : 4   ; /* [3..0]  */
        unsigned int    lum_ver_delta_lut_p1  : 4   ; /* [7..4]  */
        unsigned int    lum_ver_delta_lut_p2  : 4   ; /* [11..8]  */
        unsigned int    lum_ver_delta_lut_p3  : 4   ; /* [15..12]  */
        unsigned int    lum_ver_delta_lut_p4  : 4   ; /* [19..16]  */
        unsigned int    lum_ver_delta_lut_p5  : 4   ; /* [23..20]  */
        unsigned int    lum_ver_delta_lut_p6  : 4   ; /* [27..24]  */
        unsigned int    lum_ver_delta_lut_p7  : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT2;

/* Define the union U_VPSS_DB_LUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_ver_delta_lut_p8  : 4   ; /* [3..0]  */
        unsigned int    lum_ver_delta_lut_p9  : 4   ; /* [7..4]  */
        unsigned int    lum_ver_delta_lut_p10 : 4   ; /* [11..8]  */
        unsigned int    lum_ver_delta_lut_p11 : 4   ; /* [15..12]  */
        unsigned int    lum_ver_delta_lut_p12 : 4   ; /* [19..16]  */
        unsigned int    lum_ver_delta_lut_p13 : 4   ; /* [23..20]  */
        unsigned int    lum_ver_delta_lut_p14 : 4   ; /* [27..24]  */
        unsigned int    lum_ver_delta_lut_p15 : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT3;

/* Define the union U_VPSS_DB_LUT4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    chr_hor_delta_lut_p0  : 4   ; /* [3..0]  */
        unsigned int    chr_hor_delta_lut_p1  : 4   ; /* [7..4]  */
        unsigned int    chr_hor_delta_lut_p2  : 4   ; /* [11..8]  */
        unsigned int    chr_hor_delta_lut_p3  : 4   ; /* [15..12]  */
        unsigned int    chr_hor_delta_lut_p4  : 4   ; /* [19..16]  */
        unsigned int    chr_hor_delta_lut_p5  : 4   ; /* [23..20]  */
        unsigned int    chr_hor_delta_lut_p6  : 4   ; /* [27..24]  */
        unsigned int    chr_hor_delta_lut_p7  : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT4;

/* Define the union U_VPSS_DB_LUT5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    chr_hor_delta_lut_p8  : 4   ; /* [3..0]  */
        unsigned int    chr_hor_delta_lut_p9  : 4   ; /* [7..4]  */
        unsigned int    chr_hor_delta_lut_p10 : 4   ; /* [11..8]  */
        unsigned int    chr_hor_delta_lut_p11 : 4   ; /* [15..12]  */
        unsigned int    chr_hor_delta_lut_p12 : 4   ; /* [19..16]  */
        unsigned int    chr_hor_delta_lut_p13 : 4   ; /* [23..20]  */
        unsigned int    chr_hor_delta_lut_p14 : 4   ; /* [27..24]  */
        unsigned int    chr_hor_delta_lut_p15 : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT5;

/* Define the union U_VPSS_DB_LUT6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_h_str_fade_lut_p0 : 3   ; /* [2..0]  */
        unsigned int    lum_h_str_fade_lut_p1 : 3   ; /* [5..3]  */
        unsigned int    lum_h_str_fade_lut_p2 : 3   ; /* [8..6]  */
        unsigned int    lum_h_str_fade_lut_p3 : 3   ; /* [11..9]  */
        unsigned int    lum_h_str_fade_lut_p4 : 3   ; /* [14..12]  */
        unsigned int    lum_h_str_fade_lut_p5 : 3   ; /* [17..15]  */
        unsigned int    lum_h_str_fade_lut_p6 : 3   ; /* [20..18]  */
        unsigned int    lum_h_str_fade_lut_p7 : 3   ; /* [23..21]  */
        unsigned int    lum_h_str_fade_lut_p8 : 3   ; /* [26..24]  */
        unsigned int    lum_h_str_fade_lut_p9 : 3   ; /* [29..27]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT6;

/* Define the union U_VPSS_DB_LUT7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_v_str_fade_lut_p0 : 3   ; /* [2..0]  */
        unsigned int    lum_v_str_fade_lut_p1 : 3   ; /* [5..3]  */
        unsigned int    lum_v_str_fade_lut_p2 : 3   ; /* [8..6]  */
        unsigned int    lum_v_str_fade_lut_p3 : 3   ; /* [11..9]  */
        unsigned int    lum_v_str_fade_lut_p4 : 3   ; /* [14..12]  */
        unsigned int    lum_v_str_fade_lut_p5 : 3   ; /* [17..15]  */
        unsigned int    lum_v_str_fade_lut_p6 : 3   ; /* [20..18]  */
        unsigned int    lum_v_str_fade_lut_p7 : 3   ; /* [23..21]  */
        unsigned int    lum_v_str_fade_lut_p8 : 3   ; /* [26..24]  */
        unsigned int    lum_v_str_fade_lut_p9 : 3   ; /* [29..27]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT7;

/* Define the union U_VPSS_DB_LUT8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    chr_h_str_fade_lut_p0 : 3   ; /* [2..0]  */
        unsigned int    chr_h_str_fade_lut_p1 : 3   ; /* [5..3]  */
        unsigned int    chr_h_str_fade_lut_p2 : 3   ; /* [8..6]  */
        unsigned int    chr_h_str_fade_lut_p3 : 3   ; /* [11..9]  */
        unsigned int    chr_h_str_fade_lut_p4 : 3   ; /* [14..12]  */
        unsigned int    chr_h_str_fade_lut_p5 : 3   ; /* [17..15]  */
        unsigned int    chr_h_str_fade_lut_p6 : 3   ; /* [20..18]  */
        unsigned int    chr_h_str_fade_lut_p7 : 3   ; /* [23..21]  */
        unsigned int    chr_h_str_fade_lut_p8 : 3   ; /* [26..24]  */
        unsigned int    chr_h_str_fade_lut_p9 : 3   ; /* [29..27]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT8;

/* Define the union U_VPSS_DB_LUT9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lum_h_str_fade_lut_p10 : 3   ; /* [2..0]  */
        unsigned int    lum_h_str_fade_lut_p11 : 3   ; /* [5..3]  */
        unsigned int    lum_v_str_fade_lut_p10 : 3   ; /* [8..6]  */
        unsigned int    lum_v_str_fade_lut_p11 : 3   ; /* [11..9]  */
        unsigned int    chr_h_str_fade_lut_p10 : 3   ; /* [14..12]  */
        unsigned int    chr_h_str_fade_lut_p11 : 3   ; /* [17..15]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT9;

/* Define the union U_VPSS_DB_LUT10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir_str_gain_lut_p0   : 4   ; /* [3..0]  */
        unsigned int    dir_str_gain_lut_p1   : 4   ; /* [7..4]  */
        unsigned int    dir_str_gain_lut_p2   : 4   ; /* [11..8]  */
        unsigned int    dir_str_gain_lut_p3   : 4   ; /* [15..12]  */
        unsigned int    dir_str_gain_lut_p4   : 4   ; /* [19..16]  */
        unsigned int    dir_str_gain_lut_p5   : 4   ; /* [23..20]  */
        unsigned int    dir_str_gain_lut_p6   : 4   ; /* [27..24]  */
        unsigned int    dir_str_gain_lut_p7   : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT10;

/* Define the union U_VPSS_DBD_THDEDGE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hy_thd_edge           : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    hc_thd_edge           : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    vy_thd_edge           : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_THDEDGE;

/* Define the union U_VPSS_DBD_THDTXT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hy_thd_txt            : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    hc_thd_txt            : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    vy_thd_txt            : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_THDTXT;

/* Define the union U_VPSS_DBD_LUTWGT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    det_lut_wgt0          : 4   ; /* [3..0]  */
        unsigned int    det_lut_wgt1          : 4   ; /* [7..4]  */
        unsigned int    det_lut_wgt2          : 4   ; /* [11..8]  */
        unsigned int    det_lut_wgt3          : 4   ; /* [15..12]  */
        unsigned int    det_lut_wgt4          : 4   ; /* [19..16]  */
        unsigned int    det_lut_wgt5          : 4   ; /* [23..20]  */
        unsigned int    det_lut_wgt6          : 4   ; /* [27..24]  */
        unsigned int    det_lut_wgt7          : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_LUTWGT0;

/* Define the union U_VPSS_DBD_LUTWGT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    det_lut_wgt8          : 4   ; /* [3..0]  */
        unsigned int    det_lut_wgt9          : 4   ; /* [7..4]  */
        unsigned int    det_lut_wgt10         : 4   ; /* [11..8]  */
        unsigned int    det_lut_wgt11         : 4   ; /* [15..12]  */
        unsigned int    det_lut_wgt12         : 4   ; /* [19..16]  */
        unsigned int    det_lut_wgt13         : 4   ; /* [23..20]  */
        unsigned int    det_lut_wgt14         : 4   ; /* [27..24]  */
        unsigned int    det_lut_wgt15         : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_LUTWGT1;

/* Define the union U_VPSS_DBD_RTNBDTXT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hy_rtn_bd_txt         : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    hc_rtn_bd_txt         : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    vy_rtn_bd_txt         : 5   ; /* [20..16]  */
        unsigned int    reserved_2            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_RTNBDTXT;

/* Define the union U_VPSS_DBD_TSTBLKNUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hy_tst_blk_num        : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 1   ; /* [9]  */
        unsigned int    hc_tst_blk_num        : 9   ; /* [18..10]  */
        unsigned int    reserved_1            : 1   ; /* [19]  */
        unsigned int    vy_tst_blk_num        : 9   ; /* [28..20]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_TSTBLKNUM;

/* Define the union U_VPSS_DBD_HYRDX8BINLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hy_rdx8bin_lut0       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    hy_rdx8bin_lut1       : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HYRDX8BINLUT0;

/* Define the union U_VPSS_DBD_HYRDX8BINLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hy_rdx8bin_lut2       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    hy_rdx8bin_lut3       : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HYRDX8BINLUT1;

/* Define the union U_VPSS_DBD_HYRDX8BINLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hy_rdx8bin_lut4       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    hy_rdx8bin_lut5       : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HYRDX8BINLUT2;

/* Define the union U_VPSS_DBD_HYRDX8BINLUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hy_rdx8bin_lut6       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HYRDX8BINLUT3;

/* Define the union U_VPSS_DBD_HCRDX8BINLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hc_rdx8bin_lut0       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    hc_rdx8bin_lut1       : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HCRDX8BINLUT0;

/* Define the union U_VPSS_DBD_HCRDX8BINLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hc_rdx8bin_lut2       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    hc_rdx8bin_lut3       : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HCRDX8BINLUT1;

/* Define the union U_VPSS_DBD_HCRDX8BINLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hc_rdx8bin_lut4       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    hc_rdx8bin_lut5       : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HCRDX8BINLUT2;

/* Define the union U_VPSS_DBD_HCRDX8BINLUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hc_rdx8bin_lut6       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HCRDX8BINLUT3;

/* Define the union U_VPSS_DBD_VYRDX8BINLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vy_rdx8bin_lut0       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    vy_rdx8bin_lut1       : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_VYRDX8BINLUT0;

/* Define the union U_VPSS_DBD_VYRDX8BINLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vy_rdx8bin_lut2       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    vy_rdx8bin_lut3       : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_VYRDX8BINLUT1;

/* Define the union U_VPSS_DBD_VYRDX8BINLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vy_rdx8bin_lut4       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    vy_rdx8bin_lut5       : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_VYRDX8BINLUT2;

/* Define the union U_VPSS_DBD_VYRDX8BINLUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vy_rdx8bin_lut6       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_VYRDX8BINLUT3;

/* Define the union U_VPSS_DBD_BLKSIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    min_blk_size          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    hy_max_blk_size       : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    hc_max_blk_size       : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    vy_max_blk_size       : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_BLKSIZE;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_VPSS_CTRL            VPSS_CTRL                ; /* 0x0 */
    volatile U_VPSS_CTRL2           VPSS_CTRL2               ; /* 0x4 */
    volatile U_VPSS_CTRL3           VPSS_CTRL3               ; /* 0x8 */
    volatile unsigned int           reserved_0                     ; /* 0xc */
    volatile U_VPSS_IMGSIZE         VPSS_IMGSIZE             ; /* 0x10 */
    volatile U_VPSS_INCROP_POS      VPSS_INCROP_POS          ; /* 0x14 */
    volatile U_VPSS_INCROP_SIZE     VPSS_INCROP_SIZE         ; /* 0x18 */
    volatile U_VPSS_VHD0CROP_POS    VPSS_VHD0CROP_POS        ; /* 0x1c */
    volatile U_VPSS_VHD0CROP_SIZE   VPSS_VHD0CROP_SIZE       ; /* 0x20 */
    volatile U_VPSS_VSDCROP_POS     VPSS_VSDCROP_POS         ; /* 0x24 */
    volatile U_VPSS_VSDCROP_SIZE    VPSS_VSDCROP_SIZE        ; /* 0x28 */
    volatile U_VPSS_VHD0_ZMEORESO   VPSS_VHD0_ZMEORESO       ; /* 0x2c */
    volatile U_VPSS_VSD_ZMEORESO    VPSS_VSD_ZMEORESO        ; /* 0x30 */
    volatile U_VPSS_VHD0LBA_DSIZE   VPSS_VHD0LBA_DSIZE       ; /* 0x34 */
    volatile U_VPSS_VHD0LBA_VFPOS   VPSS_VHD0LBA_VFPOS       ; /* 0x38 */
    volatile U_VPSS_VSDLBA_DSIZE    VPSS_VSDLBA_DSIZE        ; /* 0x3c */
    volatile U_VPSS_VSDLBA_VFPOS    VPSS_VSDLBA_VFPOS        ; /* 0x40 */
    volatile unsigned int           reserved_1[3]                     ; /* 0x44~0x4c */
    volatile U_VPSS_VHD0LBA_BK      VPSS_VHD0LBA_BK          ; /* 0x50 */
    volatile U_VPSS_VSDLBA_BK       VPSS_VSDLBA_BK           ; /* 0x54 */
    volatile unsigned int           reserved_2[2]                     ; /* 0x58~0x5c */
    volatile U_STR_DET_VIDCTRL      STR_DET_VIDCTRL          ; /* 0x60 */
    volatile U_STR_DET_VIDBLKPOS0_1   STR_DET_VIDBLKPOS0_1   ; /* 0x64 */
    volatile U_STR_DET_VIDBLKPOS2_3   STR_DET_VIDBLKPOS2_3   ; /* 0x68 */
    volatile U_STR_DET_VIDBLKPOS4_5   STR_DET_VIDBLKPOS4_5   ; /* 0x6c */
    volatile U_VPSS_DR_CFG0         VPSS_DR_CFG0             ; /* 0x70 */
    volatile U_VPSS_DR_CFG1         VPSS_DR_CFG1             ; /* 0x74 */
    volatile U_VPSS_DNR_INFO        VPSS_DNR_INFO            ; /* 0x78 */
    volatile unsigned int           reserved_3[25]                     ; /* 0x7c~0xdc */
    volatile U_VPSS_AXI_RID0        VPSS_AXI_RID0            ; /* 0xe0 */
    volatile U_VPSS_AXI_RID1        VPSS_AXI_RID1            ; /* 0xe4 */
    volatile unsigned int           VPSS_NODEID              ; /* 0xe8 */
    volatile U_VPSS_AXIID           VPSS_AXIID               ; /* 0xec */
    volatile U_VPSS_INTMASK         VPSS_INTMASK             ; /* 0xf0 */
    volatile unsigned int           reserved_4[3]                     ; /* 0xf4~0xfc */
    volatile U_VPSS_CUR_CTRL        VPSS_CUR_CTRL            ; /* 0x100 */
    volatile unsigned int           VPSS_CURYADDR            ; /* 0x104 */
    volatile unsigned int           VPSS_CURCADDR            ; /* 0x108 */
    volatile unsigned int           VPSS_CURCRADDR           ; /* 0x10c */
    volatile U_VPSS_CURSTRIDE       VPSS_CURSTRIDE           ; /* 0x110 */
    volatile unsigned int           VPSS_CURYADDR_LB         ; /* 0x114 */
    volatile unsigned int           VPSS_CURCADDR_LB         ; /* 0x118 */
    volatile U_VPSS_CURSTRIDE_LB    VPSS_CURSTRIDE_LB        ; /* 0x11c */
    volatile U_VPSS_REF_CTRL        VPSS_REF_CTRL            ; /* 0x120 */
    volatile unsigned int           VPSS_REFYADDR            ; /* 0x124 */
    volatile unsigned int           VPSS_REFCADDR            ; /* 0x128 */
    volatile unsigned int           VPSS_REFCRADDR           ; /* 0x12c */
    volatile U_VPSS_REFSTRIDE       VPSS_REFSTRIDE           ; /* 0x130 */
    volatile unsigned int           VPSS_REFYADDR_LB         ; /* 0x134 */
    volatile unsigned int           VPSS_REFCADDR_LB         ; /* 0x138 */
    volatile U_VPSS_REFSTRIDE_LB    VPSS_REFSTRIDE_LB        ; /* 0x13c */
    volatile U_VPSS_NXT1_CTRL       VPSS_NXT1_CTRL           ; /* 0x140 */
    volatile unsigned int           VPSS_NXT1YADDR           ; /* 0x144 */
    volatile unsigned int           VPSS_NXT1CADDR           ; /* 0x148 */
    volatile unsigned int           VPSS_NXT1CRADDR          ; /* 0x14c */
    volatile U_VPSS_NXT1STRIDE      VPSS_NXT1STRIDE          ; /* 0x150 */
    volatile unsigned int           VPSS_NXT1YADDR_LB        ; /* 0x154 */
    volatile unsigned int           VPSS_NXT1CADDR_LB        ; /* 0x158 */
    volatile U_VPSS_NXT1STRIDE_LB   VPSS_NXT1STRIDE_LB       ; /* 0x15c */
    volatile U_VPSS_NXT2_CTRL       VPSS_NXT2_CTRL           ; /* 0x160 */
    volatile unsigned int           VPSS_NXT2YADDR           ; /* 0x164 */
    volatile unsigned int           VPSS_NXT2CADDR           ; /* 0x168 */
    volatile unsigned int           VPSS_NXT2CRADDR          ; /* 0x16c */
    volatile U_VPSS_NXT2STRIDE      VPSS_NXT2STRIDE          ; /* 0x170 */
    volatile unsigned int           VPSS_NXT2YADDR_LB        ; /* 0x174 */
    volatile unsigned int           VPSS_NXT2CADDR_LB        ; /* 0x178 */
    volatile U_VPSS_NXT2STRIDE_LB   VPSS_NXT2STRIDE_LB       ; /* 0x17c */
    volatile U_VPSS_VHD0CTRL        VPSS_VHD0CTRL            ; /* 0x180 */
    volatile U_VPSS_VHD0SIZE        VPSS_VHD0SIZE            ; /* 0x184 */
    volatile unsigned int           VPSS_VHD0YADDR           ; /* 0x188 */
    volatile unsigned int           VPSS_VHD0CADDR           ; /* 0x18c */
    volatile U_VPSS_VHD0STRIDE      VPSS_VHD0STRIDE          ; /* 0x190 */
    volatile U_VPSS_VSDCTRL         VPSS_VSDCTRL             ; /* 0x194 */
    volatile U_VPSS_VSDSIZE         VPSS_VSDSIZE             ; /* 0x198 */
    volatile unsigned int           VPSS_VSDYADDR            ; /* 0x19c */
    volatile unsigned int           VPSS_VSDCADDR            ; /* 0x1a0 */
    volatile U_VPSS_VSDSTRIDE       VPSS_VSDSTRIDE           ; /* 0x1a4 */
    volatile unsigned int           VPSS_STRADDR             ; /* 0x1a8 */
    volatile unsigned int           VPSS_STWADDR             ; /* 0x1ac */
    volatile U_VPSS_STSTRIDE        VPSS_STSTRIDE            ; /* 0x1b0 */
    volatile unsigned int           VPSS_STT_W_ADDR          ; /* 0x1b4 */
    volatile U_VPSS_TUNL_CTRL0      VPSS_TUNL_CTRL0          ; /* 0x1b8 */
    volatile U_VPSS_TUNL_CTRL1      VPSS_TUNL_CTRL1          ; /* 0x1bc */
    volatile unsigned int           VPSS_VHD0_TUNL_ADDR      ; /* 0x1c0 */
    volatile unsigned int           VPSS_VSD_TUNL_ADDR       ; /* 0x1c4 */
    volatile unsigned int           VPSS_CUR_TUNL_ADDR       ; /* 0x1c8 */
    volatile unsigned int           reserved_5[13]                     ; /* 0x1cc~0x1fc */
    volatile unsigned int           VPSS_VHD0_ZME_LHADDR     ; /* 0x200 */
    volatile unsigned int           VPSS_VHD0_ZME_LVADDR     ; /* 0x204 */
    volatile unsigned int           VPSS_VHD0_ZME_CHADDR     ; /* 0x208 */
    volatile unsigned int           VPSS_VHD0_ZME_CVADDR     ; /* 0x20c */
    volatile unsigned int           VPSS_VSD_ZME_LHADDR      ; /* 0x210 */
    volatile unsigned int           VPSS_VSD_ZME_LVADDR      ; /* 0x214 */
    volatile unsigned int           VPSS_VSD_ZME_CHADDR      ; /* 0x218 */
    volatile unsigned int           VPSS_VSD_ZME_CVADDR      ; /* 0x21c */
    volatile unsigned int           VPSS_VC1_STR_ADDR        ; /* 0x220 */
    volatile unsigned int           VPSS_ZME_ADDR            ; /* 0x224 */
    volatile unsigned int           VPSS_HSP_ADDR            ; /* 0x228 */
    volatile unsigned int           VPSS_DB_ADDR             ; /* 0x22c */
    volatile unsigned int           VPSS_DR_ADDR             ; /* 0x230 */
    volatile unsigned int           VPSS_DEI_ADDR            ; /* 0x234 */
    volatile unsigned int           VPSS_CHK_SUM_W_ADDR      ; /* 0x238 */
    volatile unsigned int           VPSS_VHD0_LCMP_ADDR      ; /* 0x23c */
    volatile unsigned int           reserved_6[47]                     ; /* 0x240~0x2f8 */
    volatile unsigned int           VPSS_PNEXT               ; /* 0x2fc */
    volatile U_VPSS_START           VPSS_START               ; /* 0x300 */
    volatile U_VPSS_INTSTATE        VPSS_INTSTATE            ; /* 0x304 */
    volatile U_VPSS_INTCLR          VPSS_INTCLR              ; /* 0x308 */
    volatile U_VPSS_RAWINT          VPSS_RAWINT              ; /* 0x30c */
    volatile unsigned int           VPSS_PFCNT               ; /* 0x310 */
    volatile U_VPSS_MISCELLANEOUS   VPSS_MISCELLANEOUS       ; /* 0x314 */
    volatile unsigned int           VPSS_MACCFG              ; /* 0x318 */
    volatile unsigned int           VPSS_TIMEOUT             ; /* 0x31c */
    volatile unsigned int           VPSS_EOFCNT              ; /* 0x320 */
    volatile unsigned int           reserved_7[3]                     ; /* 0x324~0x32c */
    volatile unsigned int           VPSS_VERSION             ; /* 0x330 */
    volatile unsigned int           reserved_8[51]                     ; /* 0x334~0x3fc */
    volatile U_VPSS_VHD0_LCMP_YINFO     VPSS_VHD0_LCMP_YINFO   ; /* 0x400 */
    volatile U_VPSS_VHD0_LCMP_YSIZE     VPSS_VHD0_LCMP_YSIZE   ; /* 0x404 */
    volatile U_VPSS_VHD0_LCMP_YRCCFG0   VPSS_VHD0_LCMP_YRCCFG0 ; /* 0x408 */
    volatile U_VPSS_VHD0_LCMP_YRCCFG1   VPSS_VHD0_LCMP_YRCCFG1 ; /* 0x40c */
    volatile U_VPSS_VHD0_LCMP_YRCCFG2   VPSS_VHD0_LCMP_YRCCFG2 ; /* 0x410 */
    volatile U_VPSS_VHD0_LCMP_YRCCFG3   VPSS_VHD0_LCMP_YRCCFG3 ; /* 0x414 */
    volatile U_VPSS_VHD0_LCMP_YRCCFG4   VPSS_VHD0_LCMP_YRCCFG4 ; /* 0x418 */
    volatile U_VPSS_VHD0_LCMP_YRCCFG5   VPSS_VHD0_LCMP_YRCCFG5 ; /* 0x41c */
    volatile U_VPSS_VHD0_LCMP_YMAXLEN   VPSS_VHD0_LCMP_YMAXLEN ; /* 0x420 */
    volatile unsigned int               reserved_9[7]                     ; /* 0x424~0x43c */
    volatile U_VPSS_VHD0_LCMP_CINFO     VPSS_VHD0_LCMP_CINFO   ; /* 0x440 */
    volatile U_VPSS_VHD0_LCMP_CSIZE     VPSS_VHD0_LCMP_CSIZE   ; /* 0x444 */
    volatile U_VPSS_VHD0_LCMP_CRCCFG0   VPSS_VHD0_LCMP_CRCCFG0 ; /* 0x448 */
    volatile U_VPSS_VHD0_LCMP_CRCCFG1   VPSS_VHD0_LCMP_CRCCFG1 ; /* 0x44c */
    volatile U_VPSS_VHD0_LCMP_CRCCFG2   VPSS_VHD0_LCMP_CRCCFG2 ; /* 0x450 */
    volatile U_VPSS_VHD0_LCMP_CRCCFG3   VPSS_VHD0_LCMP_CRCCFG3 ; /* 0x454 */
    volatile U_VPSS_VHD0_LCMP_CRCCFG4   VPSS_VHD0_LCMP_CRCCFG4 ; /* 0x458 */
    volatile U_VPSS_VHD0_LCMP_CRCCFG5   VPSS_VHD0_LCMP_CRCCFG5 ; /* 0x45c */
    volatile U_VPSS_VHD0_LCMP_CMAXLEN   VPSS_VHD0_LCMP_CMAXLEN ; /* 0x460 */
    volatile unsigned int           reserved_10[743]                     ; /* 0x464~0xffc */
    volatile U_VPSS_DIECTRL         VPSS_DIECTRL             ; /* 0x1000 */
    volatile U_VPSS_DIELMA2         VPSS_DIELMA2             ; /* 0x1004 */
    volatile U_VPSS_DIEINTEN        VPSS_DIEINTEN            ; /* 0x1008 */
    volatile U_VPSS_DIESCALE        VPSS_DIESCALE            ; /* 0x100c */
    volatile U_VPSS_DIECHECK1       VPSS_DIECHECK1           ; /* 0x1010 */
    volatile U_VPSS_DIECHECK2       VPSS_DIECHECK2           ; /* 0x1014 */
    volatile U_VPSS_DIEDIR0_3       VPSS_DIEDIR0_3           ; /* 0x1018 */
    volatile U_VPSS_DIEDIR4_7       VPSS_DIEDIR4_7           ; /* 0x101c */
    volatile U_VPSS_DIEDIR8_11      VPSS_DIEDIR8_11          ; /* 0x1020 */
    volatile U_VPSS_DIEDIR12_14     VPSS_DIEDIR12_14         ; /* 0x1024 */
    volatile U_VPSS_DIESTA          VPSS_DIESTA              ; /* 0x1028 */
    volatile unsigned int           VPSS_DIESTPPREADDR       ; /* 0x102c */
    volatile unsigned int           VPSS_DIESTPREADDR        ; /* 0x1030 */
    volatile U_VPSS_DIEINTPSCL0     VPSS_DIEINTPSCL0         ; /* 0x1034 */
    volatile U_VPSS_DIEINTPSCL1     VPSS_DIEINTPSCL1         ; /* 0x1038 */
    volatile U_VPSS_DIEDIRTHD       VPSS_DIEDIRTHD           ; /* 0x103c */
    volatile U_VPSS_DIEJITMTN       VPSS_DIEJITMTN           ; /* 0x1040 */
    volatile U_VPSS_DIEFLDMTN       VPSS_DIEFLDMTN           ; /* 0x1044 */
    volatile U_VPSS_DIEMTNDIFFTHD0  VPSS_DIEMTNDIFFTHD0     ; /* 0x1048 */
    volatile U_VPSS_DIEMTNDIFFTHD1  VPSS_DIEMTNDIFFTHD1     ; /* 0x104c */
    volatile U_VPSS_DIEMTNIIRSLP    VPSS_DIEMTNIIRSLP        ; /* 0x1050 */
    volatile U_VPSS_DIEMTNIIRRAT    VPSS_DIEMTNIIRRAT        ; /* 0x1054 */
    volatile U_VPSS_DIEHISMODE      VPSS_DIEHISMODE          ; /* 0x1058 */
    volatile U_VPSS_DIEMORFLT       VPSS_DIEMORFLT           ; /* 0x105c */
    volatile U_VPSS_DIECOMBCHK0     VPSS_DIECOMBCHK0         ; /* 0x1060 */
    volatile U_VPSS_DIECOMBCHK1     VPSS_DIECOMBCHK1         ; /* 0x1064 */
    volatile U_VPSS_DIEFRMMTNSMTHTHD0   VPSS_DIEFRMMTNSMTHTHD0 ; /* 0x1068 */
    volatile U_VPSS_DIEFRMMTNSMTHTHD1   VPSS_DIEFRMMTNSMTHTHD1 ; /* 0x106c */
    volatile U_VPSS_DIEFRMMTNSMTHSLP    VPSS_DIEFRMMTNSMTHSLP ; /* 0x1070 */
    volatile U_VPSS_DIEFRMMTNSMTHRAT    VPSS_DIEFRMMTNSMTHRAT ; /* 0x1074 */
    volatile U_VPSS_DIEFRMFLDBLENDTHD0  VPSS_DIEFRMFLDBLENDTHD0 ; /* 0x1078 */
    volatile U_VPSS_DIEFRMFLDBLENDTHD1  VPSS_DIEFRMFLDBLENDTHD1 ; /* 0x107c */
    volatile U_VPSS_DIEFRMFLDBLENDSLP   VPSS_DIEFRMFLDBLENDSLP ; /* 0x1080 */
    volatile U_VPSS_DIEFRMFLDBLENDRAT   VPSS_DIEFRMFLDBLENDRAT ; /* 0x1084 */
    volatile U_VPSS_DIEMTNADJ       VPSS_DIEMTNADJ           ; /* 0x1088 */
    volatile U_VPSS_DIEGLBMTNTHD0   VPSS_DIEGLBMTNTHD0       ; /* 0x108c */
    volatile U_VPSS_DIEGLBMTNTHD1   VPSS_DIEGLBMTNTHD1       ; /* 0x1090 */
    volatile U_VPSS_CCRSCLR0        VPSS_CCRSCLR0            ; /* 0x1094 */
    volatile U_VPSS_CCRSCLR1        VPSS_CCRSCLR1            ; /* 0x1098 */
    volatile unsigned int           reserved_11[42]                     ; /* 0x109c~0x1140 */
    volatile U_VPSS_PDPHISTTHD1     VPSS_PDPHISTTHD1         ; /* 0x1144 */
    volatile U_VPSS_PDPCCMOV        VPSS_PDPCCMOV            ; /* 0x1148 */
    volatile unsigned int           VPSS_PDICHD              ; /* 0x114c */
    volatile U_VPSS_PDCTRL          VPSS_PDCTRL              ; /* 0x1150 */
    volatile U_VPSS_PDBLKTHD        VPSS_PDBLKTHD            ; /* 0x1154 */
    volatile U_VPSS_PDHISTTHD       VPSS_PDHISTTHD           ; /* 0x1158 */
    volatile U_VPSS_PDUMTHD         VPSS_PDUMTHD             ; /* 0x115c */
    volatile U_VPSS_PDPCCCORING     VPSS_PDPCCCORING         ; /* 0x1160 */
    volatile U_VPSS_PDPCCHTHD       VPSS_PDPCCHTHD           ; /* 0x1164 */
    volatile U_VPSS_PDPCCVTHD       VPSS_PDPCCVTHD           ; /* 0x1168 */
    volatile U_VPSS_PDITDIFFVTHD    VPSS_PDITDIFFVTHD        ; /* 0x116c */
    volatile U_VPSS_PDLASITHD       VPSS_PDLASITHD           ; /* 0x1170 */
    volatile U_VPSS_PDLASIMODE0COEF   VPSS_PDLASIMODE0COEF   ; /* 0x1174 */
    volatile U_VPSS_PDLASIMODE1COEF   VPSS_PDLASIMODE1COEF   ; /* 0x1178 */
    volatile U_VPSS_PDREGION        VPSS_PDREGION            ; /* 0x117c */
    volatile unsigned int           reserved_12[928]                     ; /* 0x1180~0x1ffc */
    volatile U_VPSS_VHD0_HSP        VPSS_VHD0_HSP            ; /* 0x2000 */
    volatile U_VPSS_VHD0_HLOFFSET   VPSS_VHD0_HLOFFSET       ; /* 0x2004 */
    volatile U_VPSS_VHD0_HCOFFSET   VPSS_VHD0_HCOFFSET       ; /* 0x2008 */
    volatile U_VPSS_VHD0_VSP        VPSS_VHD0_VSP            ; /* 0x200c */
    volatile U_VPSS_VHD0_VSR        VPSS_VHD0_VSR            ; /* 0x2010 */
    volatile U_VPSS_VHD0_VOFFSET    VPSS_VHD0_VOFFSET        ; /* 0x2014 */
    volatile unsigned int           reserved_13[26]                     ; /* 0x2018~0x207c */
    volatile U_VPSS_VSD_HSP         VPSS_VSD_HSP             ; /* 0x2080 */
    volatile U_VPSS_VSD_HLOFFSET    VPSS_VSD_HLOFFSET        ; /* 0x2084 */
    volatile U_VPSS_VSD_HCOFFSET    VPSS_VSD_HCOFFSET        ; /* 0x2088 */
    volatile U_VPSS_VSD_VSP         VPSS_VSD_VSP             ; /* 0x208c */
    volatile U_VPSS_VSD_VSR         VPSS_VSD_VSR             ; /* 0x2090 */
    volatile U_VPSS_VSD_VOFFSET     VPSS_VSD_VOFFSET         ; /* 0x2094 */
    volatile unsigned int           reserved_14[26]          ; /* 0x2098~0x20fc */
    volatile U_VPSS_HSPCFG1         VPSS_HSPCFG1             ; /* 0x2100 */
    volatile U_VPSS_HSPCFG2         VPSS_HSPCFG2             ; /* 0x2104 */
    volatile unsigned int           reserved_15[3]           ; /* 0x2108~0x2110 */
    volatile U_VPSS_HSPCFG3         VPSS_HSPCFG3             ; /* 0x2114 */
    volatile U_VPSS_HSPCFG4         VPSS_HSPCFG4             ; /* 0x2118 */
    volatile U_VPSS_HSPCFG5         VPSS_HSPCFG5             ; /* 0x211c */
    volatile U_VPSS_HSPCFG6         VPSS_HSPCFG6             ; /* 0x2120 */
    volatile unsigned int           reserved_16[3]           ; /* 0x2124~0x212c */
    volatile U_VPSS_HSPCFG7         VPSS_HSPCFG7             ; /* 0x2130 */
    volatile U_VPSS_HSPCFG8         VPSS_HSPCFG8             ; /* 0x2134 */
    volatile U_VPSS_HSPCFG9         VPSS_HSPCFG9             ; /* 0x2138 */
    volatile U_VPSS_HSPCFG10        VPSS_HSPCFG10            ; /* 0x213c */
    volatile unsigned int           reserved_17[112]         ; /* 0x2140~0x22fc */
    volatile U_VPSS_DR_CTRL         VPSS_DR_CTRL             ; /* 0x2300 */
    volatile U_VPSS_DR_THR          VPSS_DR_THR              ; /* 0x2304 */
    volatile U_VPSS_DRLSWSTRLUT0    VPSS_DRLSWSTRLUT0        ; /* 0x2308 */
    volatile U_VPSS_DRLSWSTRLUT1    VPSS_DRLSWSTRLUT1        ; /* 0x230c */
    volatile U_VPSS_DRLSWSTRLUT2    VPSS_DRLSWSTRLUT2        ; /* 0x2310 */
    volatile U_VPSS_DRLSWSTRLUT3    VPSS_DRLSWSTRLUT3        ; /* 0x2314 */
    volatile U_VPSS_DRLSWSTRLUT4    VPSS_DRLSWSTRLUT4        ; /* 0x2318 */
    volatile U_VPSS_DRLSWSTRLUT5    VPSS_DRLSWSTRLUT5        ; /* 0x231c */
    volatile U_VPSS_DRLSWSTRLUT6    VPSS_DRLSWSTRLUT6        ; /* 0x2320 */
    volatile U_VPSS_DRLSWSTRLUT7    VPSS_DRLSWSTRLUT7        ; /* 0x2324 */
    volatile U_VPSS_DRLSWSTRLUT8    VPSS_DRLSWSTRLUT8        ; /* 0x2328 */
    volatile U_VPSS_DRLRWSTRLUT0    VPSS_DRLRWSTRLUT0        ; /* 0x232c */
    volatile U_VPSS_DRLRWSTRLUT1    VPSS_DRLRWSTRLUT1        ; /* 0x2330 */
    volatile U_VPSS_DRLRWSTRLUT2    VPSS_DRLRWSTRLUT2        ; /* 0x2334 */
    volatile U_VPSS_DRLRWSTRLUT3    VPSS_DRLRWSTRLUT3        ; /* 0x2338 */
    volatile U_VPSS_DRLRWSTRLUT4    VPSS_DRLRWSTRLUT4        ; /* 0x233c */
    volatile U_VPSS_DRLRWSTRLUT5    VPSS_DRLRWSTRLUT5        ; /* 0x2340 */
    volatile U_VPSS_DRLRWSTRLUT6    VPSS_DRLRWSTRLUT6        ; /* 0x2344 */
    volatile U_VPSS_DRLRWSTRLUT7    VPSS_DRLRWSTRLUT7        ; /* 0x2348 */
    volatile U_VPSS_DRLRWSTRLUT8    VPSS_DRLRWSTRLUT8        ; /* 0x234c */
    volatile U_VPSS_DRLSWSTRADJUSTLUT0   VPSS_DRLSWSTRADJUSTLUT0 ; /* 0x2350 */
    volatile U_VPSS_DRLSWSTRADJUSTLUT1   VPSS_DRLSWSTRADJUSTLUT1 ; /* 0x2354 */
    volatile U_VPSS_DRLSWSTRADJUSTLUT2   VPSS_DRLSWSTRADJUSTLUT2 ; /* 0x2358 */
    volatile U_VPSS_DRLRWSTRADJUSTLUT0   VPSS_DRLRWSTRADJUSTLUT0 ; /* 0x235c */
    volatile U_VPSS_DRLRWSTRADJUSTLUT1   VPSS_DRLRWSTRADJUSTLUT1 ; /* 0x2360 */
    volatile U_VPSS_DRLRWSTRADJUSTLUT2   VPSS_DRLRWSTRADJUSTLUT2 ; /* 0x2364 */
    volatile U_VPSS_DRANGADJSUTLUT0   VPSS_DRANGADJSUTLUT0   ; /* 0x2368 */
    volatile U_VPSS_DRANGADJSUTLUT1   VPSS_DRANGADJSUTLUT1   ; /* 0x236c */
    volatile U_VPSS_DRANGADJSUTLUT2   VPSS_DRANGADJSUTLUT2   ; /* 0x2370 */
    volatile U_VPSS_DRANGLESTRLUT1_0   VPSS_DRANGLESTRLUT1_0 ; /* 0x2374 */
    volatile U_VPSS_DRANGLESTRLUT1_1   VPSS_DRANGLESTRLUT1_1 ; /* 0x2378 */
    volatile U_VPSS_DRANGLESTRLUT1_2   VPSS_DRANGLESTRLUT1_2 ; /* 0x237c */
    volatile U_VPSS_DRANGLESTRLUT2_0   VPSS_DRANGLESTRLUT2_0 ; /* 0x2380 */
    volatile U_VPSS_DRANGLESTRLUT2_1   VPSS_DRANGLESTRLUT2_1 ; /* 0x2384 */
    volatile U_VPSS_DRANGLESTRLUT2_2   VPSS_DRANGLESTRLUT2_2 ; /* 0x2388 */
    volatile U_VPSS_DROVTSTRADJUSTLUT0   VPSS_DROVTSTRADJUSTLUT0 ; /* 0x238c */
    volatile U_VPSS_DROVTSTRADJUSTLUT1   VPSS_DROVTSTRADJUSTLUT1 ; /* 0x2390 */
    volatile U_VPSS_DROVTSTRADJUSTLUT2   VPSS_DROVTSTRADJUSTLUT2 ; /* 0x2394 */
    volatile U_VPSS_DROVTSTRLUT0    VPSS_DROVTSTRLUT0        ; /* 0x2398 */
    volatile U_VPSS_DROVTSTRLUT1    VPSS_DROVTSTRLUT1        ; /* 0x239c */
    volatile U_VPSS_DROVTSTRLUT2    VPSS_DROVTSTRLUT2        ; /* 0x23a0 */
    volatile unsigned int           reserved_18[23]          ; /* 0x23a4~0x23fc */
    volatile U_VPSS_VC1_CTRL0       VPSS_VC1_CTRL0           ; /* 0x2400 */
    volatile U_VPSS_VC1_CTRL1       VPSS_VC1_CTRL1           ; /* 0x2404 */
    volatile U_VPSS_VC1_CTRL2       VPSS_VC1_CTRL2           ; /* 0x2408 */
    volatile U_VPSS_VC1_CTRL3       VPSS_VC1_CTRL3           ; /* 0x240c */
    volatile unsigned int           reserved_19[60]          ; /* 0x2410~0x24fc */
#if 0
    volatile U_VPSS_VC1_CTRL3       VPSS_VC1_CTRL3           ; /* 0x2408 */
    volatile unsigned int           reserved_19[61]          ; /* 0x240c~0x24fc */
#endif
    volatile U_VPSS_DB_CTRL         VPSS_DB_CTRL             ; /* 0x2500 */
    volatile U_VPSS_DB_DIR          VPSS_DB_DIR              ; /* 0x2504 */
    volatile U_VPSS_DB_BLK          VPSS_DB_BLK              ; /* 0x2508 */
    volatile U_VPSS_DB_RATIO        VPSS_DB_RATIO            ; /* 0x250c */
    volatile U_VPSS_DB_LHHF         VPSS_DB_LHHF             ; /* 0x2510 */
    volatile U_VPSS_DB_LVHF         VPSS_DB_LVHF             ; /* 0x2514 */
    volatile U_VPSS_DB_CTRS         VPSS_DB_CTRS             ; /* 0x2518 */
    volatile U_VPSS_DB_LUT0         VPSS_DB_LUT0             ; /* 0x251c */
    volatile U_VPSS_DB_LUT1         VPSS_DB_LUT1             ; /* 0x2520 */
    volatile U_VPSS_DB_LUT2         VPSS_DB_LUT2             ; /* 0x2524 */
    volatile U_VPSS_DB_LUT3         VPSS_DB_LUT3             ; /* 0x2528 */
    volatile U_VPSS_DB_LUT4         VPSS_DB_LUT4             ; /* 0x252c */
    volatile U_VPSS_DB_LUT5         VPSS_DB_LUT5             ; /* 0x2530 */
    volatile U_VPSS_DB_LUT6         VPSS_DB_LUT6             ; /* 0x2534 */
    volatile U_VPSS_DB_LUT7         VPSS_DB_LUT7             ; /* 0x2538 */
    volatile U_VPSS_DB_LUT8         VPSS_DB_LUT8             ; /* 0x253c */
    volatile U_VPSS_DB_LUT9         VPSS_DB_LUT9             ; /* 0x2540 */
    volatile U_VPSS_DB_LUT10        VPSS_DB_LUT10            ; /* 0x2544 */
    volatile unsigned int           reserved_20[2]           ; /* 0x2548~0x254c */
    volatile U_VPSS_DBD_THDEDGE     VPSS_DBD_THDEDGE         ; /* 0x2550 */
    volatile U_VPSS_DBD_THDTXT      VPSS_DBD_THDTXT          ; /* 0x2554 */
    volatile U_VPSS_DBD_LUTWGT0     VPSS_DBD_LUTWGT0         ; /* 0x2558 */
    volatile U_VPSS_DBD_LUTWGT1     VPSS_DBD_LUTWGT1         ; /* 0x255c */
    volatile U_VPSS_DBD_RTNBDTXT    VPSS_DBD_RTNBDTXT        ; /* 0x2560 */
    volatile U_VPSS_DBD_TSTBLKNUM   VPSS_DBD_TSTBLKNUM       ; /* 0x2564 */
    volatile U_VPSS_DBD_HYRDX8BINLUT0   VPSS_DBD_HYRDX8BINLUT0 ; /* 0x2568 */
    volatile U_VPSS_DBD_HYRDX8BINLUT1   VPSS_DBD_HYRDX8BINLUT1 ; /* 0x256c */
    volatile U_VPSS_DBD_HYRDX8BINLUT2   VPSS_DBD_HYRDX8BINLUT2 ; /* 0x2570 */
    volatile U_VPSS_DBD_HYRDX8BINLUT3   VPSS_DBD_HYRDX8BINLUT3 ; /* 0x2574 */
    volatile U_VPSS_DBD_HCRDX8BINLUT0   VPSS_DBD_HCRDX8BINLUT0 ; /* 0x2578 */
    volatile U_VPSS_DBD_HCRDX8BINLUT1   VPSS_DBD_HCRDX8BINLUT1 ; /* 0x257c */
    volatile U_VPSS_DBD_HCRDX8BINLUT2   VPSS_DBD_HCRDX8BINLUT2 ; /* 0x2580 */
    volatile U_VPSS_DBD_HCRDX8BINLUT3   VPSS_DBD_HCRDX8BINLUT3 ; /* 0x2584 */
    volatile U_VPSS_DBD_VYRDX8BINLUT0   VPSS_DBD_VYRDX8BINLUT0 ; /* 0x2588 */
    volatile U_VPSS_DBD_VYRDX8BINLUT1   VPSS_DBD_VYRDX8BINLUT1 ; /* 0x258c */
    volatile U_VPSS_DBD_VYRDX8BINLUT2   VPSS_DBD_VYRDX8BINLUT2 ; /* 0x2590 */
    volatile U_VPSS_DBD_VYRDX8BINLUT3   VPSS_DBD_VYRDX8BINLUT3 ; /* 0x2594 */
    volatile U_VPSS_DBD_BLKSIZE     VPSS_DBD_BLKSIZE         ; /* 0x2598 */
    volatile unsigned int           reserved_21[25]          ; /* 0x259c~0x25fc */
    volatile unsigned int           VPSS_DB_BORD_FLAG[128]   ; /* 0x2600~0x27fc */
    volatile unsigned int           reserved_22[1536]        ; /* 0x2800~0x3ffc */
    volatile unsigned int           VPSS_DEBUG0              ; /* 0x4000 */
    volatile unsigned int           VPSS_DEBUG1              ; /* 0x4004 */
    volatile unsigned int           VPSS_DEBUG2              ; /* 0x4008 */
    volatile unsigned int           VPSS_DEBUG3              ; /* 0x400c */
    volatile unsigned int           VPSS_DEBUG4              ; /* 0x4010 */
    volatile unsigned int           VPSS_DEBUG5              ; /* 0x4014 */
    volatile unsigned int           VPSS_DEBUG6              ; /* 0x4018 */
    volatile unsigned int           VPSS_DEBUG7              ; /* 0x401c */
    volatile unsigned int           VPSS_DEBUG8              ; /* 0x4020 */
    volatile unsigned int           VPSS_DEBUG9              ; /* 0x4024 */
    volatile unsigned int           VPSS_DEBUG10             ; /* 0x4028 */
    volatile unsigned int           VPSS_DEBUG11             ; /* 0x402c */
    volatile unsigned int           VPSS_DEBUG12             ; /* 0x4030 */
    volatile unsigned int           VPSS_DEBUG13             ; /* 0x4034 */
    volatile unsigned int           VPSS_DEBUG14             ; /* 0x4038 */
    volatile unsigned int           VPSS_DEBUG15             ; /* 0x403c */
    volatile unsigned int           VPSS_DEBUG16             ; /* 0x4040 */
    volatile unsigned int           VPSS_DEBUG17             ; /* 0x4044 */
    volatile unsigned int           VPSS_DEBUG18             ; /* 0x4048 */
    volatile unsigned int           VPSS_DEBUG19             ; /* 0x404c */
    volatile unsigned int           VPSS_DEBUG20             ; /* 0x4050 */
    volatile unsigned int           VPSS_DEBUG21             ; /* 0x4054 */
    volatile unsigned int           VPSS_DEBUG22             ; /* 0x4058 */
    volatile unsigned int           VPSS_DEBUG23             ; /* 0x405c */
    volatile unsigned int           VPSS_DEBUG24             ; /* 0x4060 */
    volatile unsigned int           VPSS_DEBUG25             ; /* 0x4064 */
    volatile unsigned int           VPSS_DEBUG26             ; /* 0x4068 */
    volatile unsigned int           VPSS_DEBUG27             ; /* 0x406c */
    volatile unsigned int           VPSS_DEBUG28             ; /* 0x4070 */
    volatile unsigned int           VPSS_DEBUG29             ; /* 0x4074 */
    volatile unsigned int           VPSS_DEBUG30             ; /* 0x4078 */
    volatile unsigned int           VPSS_DEBUG31             ; /* 0x407c */
    volatile unsigned int           VPSS_DEBUG32             ; /* 0x4080 */
    volatile unsigned int           VPSS_DEBUG33             ; /* 0x4084 */
    volatile unsigned int           VPSS_DEBUG34             ; /* 0x4088 */
    volatile unsigned int           VPSS_DEBUG35             ; /* 0x408c */
    volatile unsigned int           VPSS_DEBUG36             ; /* 0x4090 */
    volatile unsigned int           VPSS_DEBUG37             ; /* 0x4094 */
    volatile unsigned int           VPSS_DEBUG38             ; /* 0x4098 */
    volatile unsigned int           VPSS_DEBUG39             ; /* 0x409c */
    volatile unsigned int           VPSS_DEBUG40             ; /* 0x40a0 */
    volatile unsigned int           VPSS_DEBUG41             ; /* 0x40a4 */
    volatile unsigned int           VPSS_DEBUG42             ; /* 0x40a8 */
    volatile unsigned int           VPSS_DEBUG43             ; /* 0x40ac */

} VPSS_REG_S, S_CAS_REGS_TYPE;

/*In hifoneB2, It exists S_VPSSWB_REGS_TYPE in hi_reg_vpss_wbc.h*/
/*
typedef struct
{
} S_VPSSWB_REGS_TYPE;
*/
/* Declare the struct pointor of the module CAS */
//extern volatile S_CAS_REGS_TYPE *gopCASAllReg;

/* Declare the functions that set the member value */
int iSetVPSS_CTRLvsd_en(unsigned int uvsd_en);
int iSetVPSS_CTRLvhd0_en(unsigned int uvhd0_en);
int iSetVPSS_CTRLvc1_en(unsigned int uvc1_en);
int iSetVPSS_CTRLchk_sum_en(unsigned int uchk_sum_en);
int iSetVPSS_CTRLdei_en(unsigned int udei_en);
int iSetVPSS_CTRLhsp_en(unsigned int uhsp_en);
int iSetVPSS_CTRLdnr_en(unsigned int udnr_en);
int iSetVPSS_CTRLdb_en(unsigned int udb_en);
int iSetVPSS_CTRLdr_en(unsigned int udr_en);
int iSetVPSS_CTRLtwo_pix_en(unsigned int utwo_pix_en);
int iSetVPSS_CTRLrotate_angle(unsigned int urotate_angle);
int iSetVPSS_CTRLrotate_en(unsigned int urotate_en);
int iSetVPSS_CTRLprot(unsigned int uprot);
int iSetVPSS_CTRLifmd_en(unsigned int uifmd_en);
int iSetVPSS_CTRLiglb_en(unsigned int uiglb_en);
int iSetVPSS_CTRLimg_pro_mode(unsigned int uimg_pro_mode);
int iSetVPSS_CTRLbfield_first(unsigned int ubfield_first);
int iSetVPSS_CTRLbfield_mode(unsigned int ubfield_mode);
int iSetVPSS_CTRLbfield(unsigned int ubfield);
int iSetVPSS_CTRL2vsd_format(unsigned int uvsd_format);
int iSetVPSS_CTRL2vhd0_format(unsigned int uvhd0_format);
int iSetVPSS_CTRL2in_format(unsigned int uin_format);
int iSetVPSS_CTRL2in_pix_bitw(unsigned int uin_pix_bitw);
int iSetVPSS_CTRL2uv_invert(unsigned int uuv_invert);
int iSetVPSS_CTRL3zme_vsd_en(unsigned int uzme_vsd_en);
int iSetVPSS_CTRL3zme_vhd0_en(unsigned int uzme_vhd0_en);
int iSetVPSS_CTRL3vhd0_pre_vfir_mode(unsigned int uvhd0_pre_vfir_mode);
int iSetVPSS_CTRL3vhd0_pre_vfir_en(unsigned int uvhd0_pre_vfir_en);
int iSetVPSS_CTRL3vhd0_pre_hfir_mode(unsigned int uvhd0_pre_hfir_mode);
int iSetVPSS_CTRL3vhd0_pre_hfir_en(unsigned int uvhd0_pre_hfir_en);
int iSetVPSS_CTRL3vsd_pre_vfir_mode(unsigned int uvsd_pre_vfir_mode);
int iSetVPSS_CTRL3vsd_pre_vfir_en(unsigned int uvsd_pre_vfir_en);
int iSetVPSS_CTRL3vsd_pre_hfir_mode(unsigned int uvsd_pre_hfir_mode);
int iSetVPSS_CTRL3vsd_pre_hfir_en(unsigned int uvsd_pre_hfir_en);
int iSetVPSS_CTRL3in_crop_en(unsigned int uin_crop_en);
int iSetVPSS_CTRL3vhd0_crop_en(unsigned int uvhd0_crop_en);
int iSetVPSS_CTRL3vsd_crop_en(unsigned int uvsd_crop_en);
int iSetVPSS_CTRL3vsd_lba_en(unsigned int uvsd_lba_en);
int iSetVPSS_CTRL3vhd0_lba_en(unsigned int uvhd0_lba_en);
int iSetVPSS_IMGSIZEimgwidth(unsigned int uimgwidth);
int iSetVPSS_IMGSIZEimgheight(unsigned int uimgheight);
int iSetVPSS_INCROP_POSin_crop_x(unsigned int uin_crop_x);
int iSetVPSS_INCROP_POSin_crop_y(unsigned int uin_crop_y);
int iSetVPSS_INCROP_SIZEin_crop_width(unsigned int uin_crop_width);
int iSetVPSS_INCROP_SIZEin_crop_height(unsigned int uin_crop_height);
int iSetVPSS_VHD0CROP_POSvhd0_crop_x(unsigned int uvhd0_crop_x);
int iSetVPSS_VHD0CROP_POSvhd0_crop_y(unsigned int uvhd0_crop_y);
int iSetVPSS_VHD0CROP_SIZEvhd0_crop_width(unsigned int uvhd0_crop_width);
int iSetVPSS_VHD0CROP_SIZEvhd0_crop_height(unsigned int uvhd0_crop_height);
int iSetVPSS_VSDCROP_POSvsd_crop_x(unsigned int uvsd_crop_x);
int iSetVPSS_VSDCROP_POSvsd_crop_y(unsigned int uvsd_crop_y);
int iSetVPSS_VSDCROP_SIZEvsd_crop_width(unsigned int uvsd_crop_width);
int iSetVPSS_VSDCROP_SIZEvsd_crop_height(unsigned int uvsd_crop_height);
int iSetVPSS_VHD0_ZMEORESOvhd0_zme_ow(unsigned int uvhd0_zme_ow);
int iSetVPSS_VHD0_ZMEORESOvhd0_zme_oh(unsigned int uvhd0_zme_oh);
int iSetVPSS_VSD_ZMEORESOvsd_zme_ow(unsigned int uvsd_zme_ow);
int iSetVPSS_VSD_ZMEORESOvsd_zme_oh(unsigned int uvsd_zme_oh);
int iSetVPSS_VHD0LBA_DSIZEvhd0_lba_width(unsigned int uvhd0_lba_width);
int iSetVPSS_VHD0LBA_DSIZEvhd0_lba_height(unsigned int uvhd0_lba_height);
int iSetVPSS_VHD0LBA_VFPOSvhd0_lba_xfpos(unsigned int uvhd0_lba_xfpos);
int iSetVPSS_VHD0LBA_VFPOSvhd0_lba_yfpos(unsigned int uvhd0_lba_yfpos);
int iSetVPSS_VSDLBA_DSIZEvsd_lba_width(unsigned int uvsd_lba_width);
int iSetVPSS_VSDLBA_DSIZEvsd_lba_height(unsigned int uvsd_lba_height);
int iSetVPSS_VSDLBA_VFPOSvsd_lba_xfpos(unsigned int uvsd_lba_xfpos);
int iSetVPSS_VSDLBA_VFPOSvsd_lba_yfpos(unsigned int uvsd_lba_yfpos);
int iSetVPSS_VHD0LBA_BKvbk_cr(unsigned int uvbk_cr);
int iSetVPSS_VHD0LBA_BKvbk_cb(unsigned int uvbk_cb);
int iSetVPSS_VHD0LBA_BKvbk_y(unsigned int uvbk_y);
int iSetVPSS_VSDLBA_BKvbk_cr(unsigned int uvbk_cr);
int iSetVPSS_VSDLBA_BKvbk_cb(unsigned int uvbk_cb);
int iSetVPSS_VSDLBA_BKvbk_y(unsigned int uvbk_y);
int iSetSTR_DET_VIDCTRLvid_mode(unsigned int uvid_mode);
int iSetSTR_DET_VIDBLKPOS0_1blk0_xlpos(unsigned int ublk0_xlpos);
int iSetSTR_DET_VIDBLKPOS0_1blk0_ylpos(unsigned int ublk0_ylpos);
int iSetSTR_DET_VIDBLKPOS0_1blk1_xlpos(unsigned int ublk1_xlpos);
int iSetSTR_DET_VIDBLKPOS0_1blk1_ylpos(unsigned int ublk1_ylpos);
int iSetSTR_DET_VIDBLKPOS2_3blk2_xlpos(unsigned int ublk2_xlpos);
int iSetSTR_DET_VIDBLKPOS2_3blk2_ylpos(unsigned int ublk2_ylpos);
int iSetSTR_DET_VIDBLKPOS2_3blk3_xlpos(unsigned int ublk3_xlpos);
int iSetSTR_DET_VIDBLKPOS2_3blk3_ylpos(unsigned int ublk3_ylpos);
int iSetSTR_DET_VIDBLKPOS4_5blk4_xlpos(unsigned int ublk4_xlpos);
int iSetSTR_DET_VIDBLKPOS4_5blk4_ylpos(unsigned int ublk4_ylpos);
int iSetSTR_DET_VIDBLKPOS4_5blk5_xlpos(unsigned int ublk5_xlpos);
int iSetSTR_DET_VIDBLKPOS4_5blk5_ylpos(unsigned int ublk5_ylpos);
int iSetVPSS_DR_CFG0drthrmaxsimilarpixdiff(unsigned int udrthrmaxsimilarpixdiff);
int iSetVPSS_DR_CFG0drthrflat3x3zone(unsigned int udrthrflat3x3zone);
int iSetVPSS_DR_CFG1dralphascale(unsigned int udralphascale);
int iSetVPSS_DR_CFG1drbetascale(unsigned int udrbetascale);
int iSetVPSS_DNR_INFOthrintlcolcnt(unsigned int uthrintlcolcnt);
int iSetVPSS_DNR_INFOthrintlcnt(unsigned int uthrintlcnt);
int iSetVPSS_DNR_INFOthdmaxgrad(unsigned int uthdmaxgrad);
int iSetVPSS_DNR_INFOthdcntrst8(unsigned int uthdcntrst8);
int iSetVPSS_AXI_RID0cury_rid(unsigned int ucury_rid);
int iSetVPSS_AXI_RID0curc_rid(unsigned int ucurc_rid);
int iSetVPSS_AXI_RID0refy_rid(unsigned int urefy_rid);
int iSetVPSS_AXI_RID0refc_rid(unsigned int urefc_rid);
int iSetVPSS_AXI_RID0nx1y_rid(unsigned int unx1y_rid);
int iSetVPSS_AXI_RID0nx1c_rid(unsigned int unx1c_rid);
int iSetVPSS_AXI_RID0nx2y_rid(unsigned int unx2y_rid);
int iSetVPSS_AXI_RID0nx2c_rid(unsigned int unx2c_rid);
int iSetVPSS_AXI_RID1rst_rid(unsigned int urst_rid);
int iSetVPSS_AXI_RID1cas_rid(unsigned int ucas_rid);
int iSetVPSS_NODEIDnodeid(unsigned int unodeid);
int iSetVPSS_AXIIDawid_cfg0(unsigned int uawid_cfg0);
int iSetVPSS_AXIIDarid_cfg0(unsigned int uarid_cfg0);
int iSetVPSS_INTMASKeof_mask(unsigned int ueof_mask);
int iSetVPSS_INTMASKtimeout_mask(unsigned int utimeout_mask);
int iSetVPSS_INTMASKbus_r_err_mask(unsigned int ubus_r_err_mask);
int iSetVPSS_INTMASKeof_end_mask(unsigned int ueof_end_mask);
int iSetVPSS_INTMASKbus_w_err_mask(unsigned int ubus_w_err_mask);
int iSetVPSS_INTMASKvhd0_tunl_mask(unsigned int uvhd0_tunl_mask);
int iSetVPSS_INTMASKvsd_tunl_mask(unsigned int uvsd_tunl_mask);
int iSetVPSS_CUR_CTRLcur_tile_format(unsigned int ucur_tile_format);
int iSetVPSS_CUR_CTRLcur_hor_offset(unsigned int ucur_hor_offset);
int iSetVPSS_CUR_CTRLcur_ver_offset(unsigned int ucur_ver_offset);
int iSetVPSS_CUR_CTRLcur_package422(unsigned int ucur_package422);
int iSetVPSS_CURYADDRcury_addr(unsigned int ucury_addr);
int iSetVPSS_CURCADDRcurc_addr(unsigned int ucurc_addr);
int iSetVPSS_CURCRADDRcurcr_addr(unsigned int ucurcr_addr);
int iSetVPSS_CURSTRIDEcury_stride(unsigned int ucury_stride);
int iSetVPSS_CURSTRIDEcurc_stride(unsigned int ucurc_stride);
int iSetVPSS_CURYADDR_LBcury_addrlb(unsigned int ucury_addrlb);
int iSetVPSS_CURCADDR_LBcurc_addr_lb(unsigned int ucurc_addr_lb);
int iSetVPSS_CURSTRIDE_LBcury_stride_lb(unsigned int ucury_stride_lb);
int iSetVPSS_CURSTRIDE_LBcurc_stride_lb(unsigned int ucurc_stride_lb);
int iSetVPSS_REF_CTRLref_tile_format(unsigned int uref_tile_format);
int iSetVPSS_REF_CTRLref_hor_offset(unsigned int uref_hor_offset);
int iSetVPSS_REF_CTRLref_ver_offset(unsigned int uref_ver_offset);
int iSetVPSS_REF_CTRLref_package422(unsigned int uref_package422);
int iSetVPSS_REFYADDRrefy_addr(unsigned int urefy_addr);
int iSetVPSS_REFCADDRrefc_addr(unsigned int urefc_addr);
int iSetVPSS_REFCRADDRrefcr_addr(unsigned int urefcr_addr);
int iSetVPSS_REFSTRIDErefy_stride(unsigned int urefy_stride);
int iSetVPSS_REFSTRIDErefc_stride(unsigned int urefc_stride);
int iSetVPSS_REFYADDR_LBrefy_addr_lb(unsigned int urefy_addr_lb);
int iSetVPSS_REFCADDR_LBrefc_addr_lb(unsigned int urefc_addr_lb);
int iSetVPSS_REFSTRIDE_LBrefy_stride_lb(unsigned int urefy_stride_lb);
int iSetVPSS_REFSTRIDE_LBrefc_stride_lb(unsigned int urefc_stride_lb);
int iSetVPSS_NXT1_CTRLnxt1_tile_format(unsigned int unxt1_tile_format);
int iSetVPSS_NXT1_CTRLnxt1_hor_offset(unsigned int unxt1_hor_offset);
int iSetVPSS_NXT1_CTRLnxt1_ver_offset(unsigned int unxt1_ver_offset);
int iSetVPSS_NXT1YADDRnxt1y_addr(unsigned int unxt1y_addr);
int iSetVPSS_NXT1CADDRnxt1c_addr(unsigned int unxt1c_addr);
int iSetVPSS_NXT1CRADDRnxt1cr_addr(unsigned int unxt1cr_addr);
int iSetVPSS_NXT1STRIDEnxt1y_stride(unsigned int unxt1y_stride);
int iSetVPSS_NXT1STRIDEnxt1c_stride(unsigned int unxt1c_stride);
int iSetVPSS_NXT1YADDR_LBnxt1y_addr_lb(unsigned int unxt1y_addr_lb);
int iSetVPSS_NXT1CADDR_LBnxt1c_addr_lb(unsigned int unxt1c_addr_lb);
int iSetVPSS_NXT1STRIDE_LBnxt1y_stride_lb(unsigned int unxt1y_stride_lb);
int iSetVPSS_NXT1STRIDE_LBnxt1c_stride_lb(unsigned int unxt1c_stride_lb);
int iSetVPSS_NXT2_CTRLnxt2_tile_format(unsigned int unxt2_tile_format);
int iSetVPSS_NXT2_CTRLnxt2_hor_offset(unsigned int unxt2_hor_offset);
int iSetVPSS_NXT2_CTRLnxt2_ver_offset(unsigned int unxt2_ver_offset);
int iSetVPSS_NXT2YADDRnxt2y_addr(unsigned int unxt2y_addr);
int iSetVPSS_NXT2CADDRnxt2c_addr(unsigned int unxt2c_addr);
int iSetVPSS_NXT2CRADDRnxt2cr_addr(unsigned int unxt2cr_addr);
int iSetVPSS_NXT2STRIDEnxt2y_stride(unsigned int unxt2y_stride);
int iSetVPSS_NXT2STRIDEnxt2c_stride(unsigned int unxt2c_stride);
int iSetVPSS_NXT2YADDR_LBnxt2y_addr_lb(unsigned int unxt2y_addr_lb);
int iSetVPSS_NXT2CADDR_LBnxt2c_addr_lb(unsigned int unxt2c_addr_lb);
int iSetVPSS_NXT2STRIDE_LBnxt2y_stride_lb(unsigned int unxt2y_stride_lb);
int iSetVPSS_NXT2STRIDE_LBnxt2c_stride_lb(unsigned int unxt2c_stride_lb);
int iSetVPSS_VHD0CTRLvhd0_mirror(unsigned int uvhd0_mirror);
int iSetVPSS_VHD0CTRLvhd0_flip(unsigned int uvhd0_flip);
int iSetVPSS_VHD0CTRLvhd0_pix_bitw(unsigned int uvhd0_pix_bitw);
int iSetVPSS_VHD0CTRLvhd0_dither_en(unsigned int uvhd0_dither_en);
int iSetVPSS_VHD0CTRLvhd0_uv_invert(unsigned int uvhd0_uv_invert);
int iSetVPSS_VHD0CTRLvhd0_lcmp_en(unsigned int uvhd0_lcmp_en);
int iSetVPSS_VHD0CTRLvhd0_dither_mode(unsigned int uvhd0_dither_mode);
int iSetVPSS_VHD0SIZEvhd0_width(unsigned int uvhd0_width);
int iSetVPSS_VHD0SIZEvhd0_height(unsigned int uvhd0_height);
int iSetVPSS_VHD0YADDRvhd0y_addr(unsigned int uvhd0y_addr);
int iSetVPSS_VHD0CADDRvhd0c_addr(unsigned int uvhd0c_addr);
int iSetVPSS_VHD0STRIDEvhd0y_stride(unsigned int uvhd0y_stride);
int iSetVPSS_VHD0STRIDEvhd0c_stride(unsigned int uvhd0c_stride);
int iSetVPSS_VSDCTRLvsd_mirror(unsigned int uvsd_mirror);
int iSetVPSS_VSDCTRLvsd_flip(unsigned int uvsd_flip);
int iSetVPSS_VSDCTRLvsd_pix_bitw(unsigned int uvsd_pix_bitw);
int iSetVPSS_VSDCTRLvsd_dither_en(unsigned int uvsd_dither_en);
int iSetVPSS_VSDCTRLvsd_uv_invert(unsigned int uvsd_uv_invert);
int iSetVPSS_VSDCTRLvsd_dither_mode(unsigned int uvsd_dither_mode);
int iSetVPSS_VSDSIZEvsd_width(unsigned int uvsd_width);
int iSetVPSS_VSDSIZEvsd_height(unsigned int uvsd_height);
int iSetVPSS_VSDYADDRvsdy_addr(unsigned int uvsdy_addr);
int iSetVPSS_VSDCADDRvsdc_addr(unsigned int uvsdc_addr);
int iSetVPSS_VSDSTRIDEvsdy_stride(unsigned int uvsdy_stride);
int iSetVPSS_VSDSTRIDEvsdc_stride(unsigned int uvsdc_stride);
int iSetVPSS_STRADDRst_raddr(unsigned int ust_raddr);
int iSetVPSS_STWADDRst_waddr(unsigned int ust_waddr);
int iSetVPSS_STSTRIDEst_stride(unsigned int ust_stride);
int iSetVPSS_STT_W_ADDRstt_w_addr(unsigned int ustt_w_addr);
int iSetVPSS_TUNL_CTRL0vhd0_tunl_finish_line(unsigned int uvhd0_tunl_finish_line);
int iSetVPSS_TUNL_CTRL0vhd0_tunl_en(unsigned int uvhd0_tunl_en);
int iSetVPSS_TUNL_CTRL0vsd_tunl_en(unsigned int uvsd_tunl_en);
int iSetVPSS_TUNL_CTRL0cur_tunl_en(unsigned int ucur_tunl_en);
int iSetVPSS_TUNL_CTRL1vsd_tunl_finish_line(unsigned int uvsd_tunl_finish_line);
int iSetVPSS_TUNL_CTRL1cur_tunl_rd_interval(unsigned int ucur_tunl_rd_interval);
int iSetVPSS_TUNL_CTRL1vhd0_tunl_mode(unsigned int uvhd0_tunl_mode);
int iSetVPSS_TUNL_CTRL1vsd_tunl_mode(unsigned int uvsd_tunl_mode);
int iSetVPSS_VHD0_TUNL_ADDRvhd0_tunl_addr(unsigned int uvhd0_tunl_addr);
int iSetVPSS_VSD_TUNL_ADDRvsd_tunl_addr(unsigned int uvsd_tunl_addr);
int iSetVPSS_CUR_TUNL_ADDRcur_tunl_addr(unsigned int ucur_tunl_addr);
int iSetVPSS_VHD0_ZME_LHADDRvhd0_scl_lh(unsigned int uvhd0_scl_lh);
int iSetVPSS_VHD0_ZME_LVADDRvhd0_scl_lv(unsigned int uvhd0_scl_lv);
int iSetVPSS_VHD0_ZME_CHADDRvhd0_scl_ch(unsigned int uvhd0_scl_ch);
int iSetVPSS_VHD0_ZME_CVADDRvhd0_scl_cv(unsigned int uvhd0_scl_cv);
int iSetVPSS_VSD_ZME_LHADDRvsd_scl_lh(unsigned int uvsd_scl_lh);
int iSetVPSS_VSD_ZME_LVADDRvsd_scl_lv(unsigned int uvsd_scl_lv);
int iSetVPSS_VSD_ZME_CHADDRvsd_scl_ch(unsigned int uvsd_scl_ch);
int iSetVPSS_VSD_ZME_CVADDRvsd_scl_cv(unsigned int uvsd_scl_cv);
int iSetVPSS_VC1_STR_ADDRvc1_str_cfg_addr(unsigned int uvc1_str_cfg_addr);
int iSetVPSS_ZME_ADDRzme_cfg_addr(unsigned int uzme_cfg_addr);
int iSetVPSS_HSP_ADDRhsp_cfg_addr(unsigned int uhsp_cfg_addr);
int iSetVPSS_DB_ADDRdb_cfg_addr(unsigned int udb_cfg_addr);
int iSetVPSS_DR_ADDRdr_cfg_addr(unsigned int udr_cfg_addr);
int iSetVPSS_DEI_ADDRdei_cfg_addr(unsigned int udei_cfg_addr);
int iSetVPSS_CHK_SUM_W_ADDRchk_sum_w_addr(unsigned int uchk_sum_w_addr);
int iSetVPSS_VHD0_LCMP_ADDRvhd0_lcmp_cfg_addr(unsigned int uvhd0_lcmp_cfg_addr);
int iSetVPSS_PNEXTp_next(unsigned int up_next);
int iSetVPSS_MISCELLANEOUSroutstanding(unsigned int uroutstanding);
int iSetVPSS_MISCELLANEOUSwoutstanding(unsigned int uwoutstanding);
int iSetVPSS_MISCELLANEOUSinit_timer(unsigned int uinit_timer);
int iSetVPSS_MISCELLANEOUSck_gt_en(unsigned int uck_gt_en);
int iSetVPSS_MISCELLANEOUSck_gt_en_calc(unsigned int uck_gt_en_calc);
int iSetVPSS_MACCFGmac_ch_prio(unsigned int umac_ch_prio);
int iSetVPSS_TIMEOUTtimeout(unsigned int utimeout);
int iSetVPSS_VHD0_LCMP_YINFOis_lossless(unsigned int uis_lossless);
int iSetVPSS_VHD0_LCMP_YINFOcmp_mode(unsigned int ucmp_mode);
int iSetVPSS_VHD0_LCMP_YINFOdw_mode(unsigned int udw_mode);
int iSetVPSS_VHD0_LCMP_YSIZEframe_width(unsigned int uframe_width);
int iSetVPSS_VHD0_LCMP_YSIZEframe_height(unsigned int uframe_height);
int iSetVPSS_VHD0_LCMP_YRCCFG0mb_bits(unsigned int umb_bits);
int iSetVPSS_VHD0_LCMP_YRCCFG0ri_bits(unsigned int uri_bits);
int iSetVPSS_VHD0_LCMP_YRCCFG0max_rg_comp_bits(unsigned int umax_rg_comp_bits);
int iSetVPSS_VHD0_LCMP_YRCCFG1max_qp(unsigned int umax_qp);
int iSetVPSS_VHD0_LCMP_YRCCFG1sad_bits_ngain(unsigned int usad_bits_ngain);
int iSetVPSS_VHD0_LCMP_YRCCFG1rc_smth_ngain(unsigned int urc_smth_ngain);
int iSetVPSS_VHD0_LCMP_YRCCFG2smth_thr(unsigned int usmth_thr);
int iSetVPSS_VHD0_LCMP_YRCCFG2smth_pix_num_thr(unsigned int usmth_pix_num_thr);
int iSetVPSS_VHD0_LCMP_YRCCFG2pix_diff_thr(unsigned int upix_diff_thr);
int iSetVPSS_VHD0_LCMP_YRCCFG3adj_sad_thr(unsigned int uadj_sad_thr);
int iSetVPSS_VHD0_LCMP_YRCCFG3adj_sad_bit_thr(unsigned int uadj_sad_bit_thr);
int iSetVPSS_VHD0_LCMP_YRCCFG4qp_chg1_bits_thr(unsigned int uqp_chg1_bits_thr);
int iSetVPSS_VHD0_LCMP_YRCCFG4qp_chg2_bits_thr(unsigned int uqp_chg2_bits_thr);
int iSetVPSS_VHD0_LCMP_YRCCFG5smth_qp0(unsigned int usmth_qp0);
int iSetVPSS_VHD0_LCMP_YRCCFG5smth_qp1(unsigned int usmth_qp1);
int iSetVPSS_VHD0_LCMP_YRCCFG5smth_lftbits_thr0(unsigned int usmth_lftbits_thr0);
int iSetVPSS_VHD0_LCMP_YRCCFG5smth_lftbits_thr1(unsigned int usmth_lftbits_thr1);
int iSetVPSS_VHD0_LCMP_CINFOis_lossless(unsigned int uis_lossless);
int iSetVPSS_VHD0_LCMP_CINFOcmp_mode(unsigned int ucmp_mode);
int iSetVPSS_VHD0_LCMP_CINFOdw_mode(unsigned int udw_mode);
int iSetVPSS_VHD0_LCMP_CSIZEframe_width(unsigned int uframe_width);
int iSetVPSS_VHD0_LCMP_CSIZEframe_height(unsigned int uframe_height);
int iSetVPSS_VHD0_LCMP_CRCCFG0mb_bits(unsigned int umb_bits);
int iSetVPSS_VHD0_LCMP_CRCCFG0ri_bits(unsigned int uri_bits);
int iSetVPSS_VHD0_LCMP_CRCCFG0max_rg_comp_bits(unsigned int umax_rg_comp_bits);
int iSetVPSS_VHD0_LCMP_CRCCFG1max_qp(unsigned int umax_qp);
int iSetVPSS_VHD0_LCMP_CRCCFG1sad_bits_ngain(unsigned int usad_bits_ngain);
int iSetVPSS_VHD0_LCMP_CRCCFG1rc_smth_ngain(unsigned int urc_smth_ngain);
int iSetVPSS_VHD0_LCMP_CRCCFG2smth_thr(unsigned int usmth_thr);
int iSetVPSS_VHD0_LCMP_CRCCFG2smth_pix_num_thr(unsigned int usmth_pix_num_thr);
int iSetVPSS_VHD0_LCMP_CRCCFG2pix_diff_thr(unsigned int upix_diff_thr);
int iSetVPSS_VHD0_LCMP_CRCCFG3adj_sad_thr(unsigned int uadj_sad_thr);
int iSetVPSS_VHD0_LCMP_CRCCFG3adj_sad_bit_thr(unsigned int uadj_sad_bit_thr);
int iSetVPSS_VHD0_LCMP_CRCCFG4qp_chg1_bits_thr(unsigned int uqp_chg1_bits_thr);
int iSetVPSS_VHD0_LCMP_CRCCFG4qp_chg2_bits_thr(unsigned int uqp_chg2_bits_thr);
int iSetVPSS_VHD0_LCMP_CRCCFG5smth_qp0(unsigned int usmth_qp0);
int iSetVPSS_VHD0_LCMP_CRCCFG5smth_qp1(unsigned int usmth_qp1);
int iSetVPSS_VHD0_LCMP_CRCCFG5smth_lftbits_thr0(unsigned int usmth_lftbits_thr0);
int iSetVPSS_VHD0_LCMP_CRCCFG5smth_lftbits_thr1(unsigned int usmth_lftbits_thr1);
int iSetVPSS_DIECTRLdie_rst(unsigned int udie_rst);
int iSetVPSS_DIECTRLdie_chmmode(unsigned int udie_chmmode);
int iSetVPSS_DIECTRLdie_lmmode(unsigned int udie_lmmode);
int iSetVPSS_DIECTRLdie_out_sel_c(unsigned int udie_out_sel_c);
int iSetVPSS_DIECTRLdie_out_sel_l(unsigned int udie_out_sel_l);
int iSetVPSS_DIELMA2recmode_frmfld_blend_mode(unsigned int urecmode_frmfld_blend_mode);
int iSetVPSS_DIELMA2frame_motion_smooth_en(unsigned int uframe_motion_smooth_en);
int iSetVPSS_DIELMA2luma_scesdf_max(unsigned int uluma_scesdf_max);
int iSetVPSS_DIELMA2motion_iir_en(unsigned int umotion_iir_en);
int iSetVPSS_DIELMA2luma_mf_max(unsigned int uluma_mf_max);
int iSetVPSS_DIELMA2chroma_mf_max(unsigned int uchroma_mf_max);
int iSetVPSS_DIELMA2rec_mode_en(unsigned int urec_mode_en);
int iSetVPSS_DIEINTENdir_inten_ver(unsigned int udir_inten_ver);
int iSetVPSS_DIEINTENver_min_inten(unsigned int uver_min_inten);
int iSetVPSS_DIESCALErange_scale(unsigned int urange_scale);
int iSetVPSS_DIECHECK1ck1_max_range(unsigned int uck1_max_range);
int iSetVPSS_DIECHECK1ck1_range_gain(unsigned int uck1_range_gain);
int iSetVPSS_DIECHECK1ck1_gain(unsigned int uck1_gain);
int iSetVPSS_DIECHECK2ck2_max_range(unsigned int uck2_max_range);
int iSetVPSS_DIECHECK2ck2_range_gain(unsigned int uck2_range_gain);
int iSetVPSS_DIECHECK2ck2_gain(unsigned int uck2_gain);
int iSetVPSS_DIEDIR0_3dir0_mult(unsigned int udir0_mult);
int iSetVPSS_DIEDIR0_3dir1_mult(unsigned int udir1_mult);
int iSetVPSS_DIEDIR0_3dir2_mult(unsigned int udir2_mult);
int iSetVPSS_DIEDIR0_3dir3_mult(unsigned int udir3_mult);
int iSetVPSS_DIEDIR4_7dir4_mult(unsigned int udir4_mult);
int iSetVPSS_DIEDIR4_7dir5_mult(unsigned int udir5_mult);
int iSetVPSS_DIEDIR4_7dir6_mult(unsigned int udir6_mult);
int iSetVPSS_DIEDIR4_7dir7_mult(unsigned int udir7_mult);
int iSetVPSS_DIEDIR8_11dir8_mult(unsigned int udir8_mult);
int iSetVPSS_DIEDIR8_11dir9_mult(unsigned int udir9_mult);
int iSetVPSS_DIEDIR8_11dir10_mult(unsigned int udir10_mult);
int iSetVPSS_DIEDIR8_11dir11_mult(unsigned int udir11_mult);
int iSetVPSS_DIEDIR12_14dir12_mult(unsigned int udir12_mult);
int iSetVPSS_DIEDIR12_14dir13_mult(unsigned int udir13_mult);
int iSetVPSS_DIEDIR12_14dir14_mult(unsigned int udir14_mult);
int iSetVPSS_DIESTPPREADDRdie_ppre_addr(unsigned int udie_ppre_addr);
int iSetVPSS_DIESTPREADDRdie_pre_addr(unsigned int udie_pre_addr);
int iSetVPSS_DIEINTPSCL0intp_scale_ratio_1(unsigned int uintp_scale_ratio_1);
int iSetVPSS_DIEINTPSCL0intp_scale_ratio_2(unsigned int uintp_scale_ratio_2);
int iSetVPSS_DIEINTPSCL0intp_scale_ratio_3(unsigned int uintp_scale_ratio_3);
int iSetVPSS_DIEINTPSCL0intp_scale_ratio_4(unsigned int uintp_scale_ratio_4);
int iSetVPSS_DIEINTPSCL0intp_scale_ratio_5(unsigned int uintp_scale_ratio_5);
int iSetVPSS_DIEINTPSCL0intp_scale_ratio_6(unsigned int uintp_scale_ratio_6);
int iSetVPSS_DIEINTPSCL0intp_scale_ratio_7(unsigned int uintp_scale_ratio_7);
int iSetVPSS_DIEINTPSCL0intp_scale_ratio_8(unsigned int uintp_scale_ratio_8);
int iSetVPSS_DIEINTPSCL1intp_scale_ratio_9(unsigned int uintp_scale_ratio_9);
int iSetVPSS_DIEINTPSCL1intp_scale_ratio_10(unsigned int uintp_scale_ratio_10);
int iSetVPSS_DIEINTPSCL1intp_scale_ratio_11(unsigned int uintp_scale_ratio_11);
int iSetVPSS_DIEINTPSCL1intp_scale_ratio_12(unsigned int uintp_scale_ratio_12);
int iSetVPSS_DIEINTPSCL1intp_scale_ratio_13(unsigned int uintp_scale_ratio_13);
int iSetVPSS_DIEINTPSCL1intp_scale_ratio_14(unsigned int uintp_scale_ratio_14);
int iSetVPSS_DIEINTPSCL1intp_scale_ratio_15(unsigned int uintp_scale_ratio_15);
int iSetVPSS_DIEDIRTHDbc_gain(unsigned int ubc_gain);
int iSetVPSS_DIEDIRTHDdir_thd(unsigned int udir_thd);
int iSetVPSS_DIEDIRTHDedge_mode(unsigned int uedge_mode);
int iSetVPSS_DIEDIRTHDhor_edge_en(unsigned int uhor_edge_en);
int iSetVPSS_DIEDIRTHDstrength_thd(unsigned int ustrength_thd);
int iSetVPSS_DIEJITMTNjitter_gain(unsigned int ujitter_gain);
int iSetVPSS_DIEJITMTNjitter_coring(unsigned int ujitter_coring);
int iSetVPSS_DIEJITMTNfld_motion_coring(unsigned int ufld_motion_coring);
int iSetVPSS_DIEFLDMTNfld_motion_thd_low(unsigned int ufld_motion_thd_low);
int iSetVPSS_DIEFLDMTNfld_motion_thd_high(unsigned int ufld_motion_thd_high);
int iSetVPSS_DIEFLDMTNfld_motion_curve_slope(unsigned int ufld_motion_curve_slope);
int iSetVPSS_DIEFLDMTNfld_motion_gain(unsigned int ufld_motion_gain);
int iSetVPSS_DIEMTNDIFFTHD0motion_diff_thd_0(unsigned int umotion_diff_thd_0);
int iSetVPSS_DIEMTNDIFFTHD0motion_diff_thd_1(unsigned int umotion_diff_thd_1);
int iSetVPSS_DIEMTNDIFFTHD0motion_diff_thd_2(unsigned int umotion_diff_thd_2);
int iSetVPSS_DIEMTNDIFFTHD0motion_diff_thd_3(unsigned int umotion_diff_thd_3);
int iSetVPSS_DIEMTNDIFFTHD1motion_diff_thd_4(unsigned int umotion_diff_thd_4);
int iSetVPSS_DIEMTNDIFFTHD1motion_diff_thd_5(unsigned int umotion_diff_thd_5);
int iSetVPSS_DIEMTNDIFFTHD1min_motion_iir_ratio(unsigned int umin_motion_iir_ratio);
int iSetVPSS_DIEMTNDIFFTHD1max_motion_iir_ratio(unsigned int umax_motion_iir_ratio);
int iSetVPSS_DIEMTNIIRSLPmotion_iir_curve_slope_0(unsigned int umotion_iir_curve_slope_0);
int iSetVPSS_DIEMTNIIRSLPmotion_iir_curve_slope_1(unsigned int umotion_iir_curve_slope_1);
int iSetVPSS_DIEMTNIIRSLPmotion_iir_curve_slope_2(unsigned int umotion_iir_curve_slope_2);
int iSetVPSS_DIEMTNIIRSLPmotion_iir_curve_slope_3(unsigned int umotion_iir_curve_slope_3);
int iSetVPSS_DIEMTNIIRSLPmotion_iir_curve_ratio_0(unsigned int umotion_iir_curve_ratio_0);
int iSetVPSS_DIEMTNIIRRATmotion_iir_curve_ratio_1(unsigned int umotion_iir_curve_ratio_1);
int iSetVPSS_DIEMTNIIRRATmotion_iir_curve_ratio_2(unsigned int umotion_iir_curve_ratio_2);
int iSetVPSS_DIEMTNIIRRATmotion_iir_curve_ratio_3(unsigned int umotion_iir_curve_ratio_3);
int iSetVPSS_DIEMTNIIRRATmotion_iir_curve_ratio_4(unsigned int umotion_iir_curve_ratio_4);
int iSetVPSS_DIEHISMODErec_mode_fld_motion_step_0(unsigned int urec_mode_fld_motion_step_0);
int iSetVPSS_DIEHISMODErec_mode_fld_motion_step_1(unsigned int urec_mode_fld_motion_step_1);
int iSetVPSS_DIEHISMODErec_mode_frm_motion_step_0(unsigned int urec_mode_frm_motion_step_0);
int iSetVPSS_DIEHISMODErec_mode_frm_motion_step_1(unsigned int urec_mode_frm_motion_step_1);
int iSetVPSS_DIEHISMODEppre_info_en(unsigned int uppre_info_en);
int iSetVPSS_DIEHISMODEpre_info_en(unsigned int upre_info_en);
int iSetVPSS_DIEHISMODEhis_motion_en(unsigned int uhis_motion_en);
int iSetVPSS_DIEHISMODEhis_motion_using_mode(unsigned int uhis_motion_using_mode);
int iSetVPSS_DIEHISMODEhis_motion_write_mode(unsigned int uhis_motion_write_mode);
int iSetVPSS_DIEHISMODEhis_motion_info_write_mode(unsigned int uhis_motion_info_write_mode);
int iSetVPSS_DIEMORFLTmor_flt_thd(unsigned int umor_flt_thd);
int iSetVPSS_DIEMORFLTmor_flt_size(unsigned int umor_flt_size);
int iSetVPSS_DIEMORFLTmor_flt_en(unsigned int umor_flt_en);
int iSetVPSS_DIEMORFLTmed_blend_en(unsigned int umed_blend_en);
int iSetVPSS_DIECOMBCHK0comb_chk_min_hthd(unsigned int ucomb_chk_min_hthd);
int iSetVPSS_DIECOMBCHK0comb_chk_min_vthd(unsigned int ucomb_chk_min_vthd);
int iSetVPSS_DIECOMBCHK0comb_chk_lower_limit(unsigned int ucomb_chk_lower_limit);
int iSetVPSS_DIECOMBCHK0comb_chk_upper_limit(unsigned int ucomb_chk_upper_limit);
int iSetVPSS_DIECOMBCHK1comb_chk_edge_thd(unsigned int ucomb_chk_edge_thd);
int iSetVPSS_DIECOMBCHK1comb_chk_md_thd(unsigned int ucomb_chk_md_thd);
int iSetVPSS_DIECOMBCHK1comb_chk_en(unsigned int ucomb_chk_en);
int iSetVPSS_DIEFRMMTNSMTHTHD0frame_motion_smooth_thd0(unsigned int uframe_motion_smooth_thd0);
int iSetVPSS_DIEFRMMTNSMTHTHD0frame_motion_smooth_thd1(unsigned int uframe_motion_smooth_thd1);
int iSetVPSS_DIEFRMMTNSMTHTHD0frame_motion_smooth_thd2(unsigned int uframe_motion_smooth_thd2);
int iSetVPSS_DIEFRMMTNSMTHTHD0frame_motion_smooth_thd3(unsigned int uframe_motion_smooth_thd3);
int iSetVPSS_DIEFRMMTNSMTHTHD1frame_motion_smooth_thd4(unsigned int uframe_motion_smooth_thd4);
int iSetVPSS_DIEFRMMTNSMTHTHD1frame_motion_smooth_thd5(unsigned int uframe_motion_smooth_thd5);
int iSetVPSS_DIEFRMMTNSMTHTHD1frame_motion_smooth_ratio_min(unsigned int uframe_motion_smooth_ratio_min);
int iSetVPSS_DIEFRMMTNSMTHTHD1frame_motion_smooth_ratio_max(unsigned int uframe_motion_smooth_ratio_max);
int iSetVPSS_DIEFRMMTNSMTHSLPframe_motion_smooth_slope0(unsigned int uframe_motion_smooth_slope0);
int iSetVPSS_DIEFRMMTNSMTHSLPframe_motion_smooth_slope1(unsigned int uframe_motion_smooth_slope1);
int iSetVPSS_DIEFRMMTNSMTHSLPframe_motion_smooth_slope2(unsigned int uframe_motion_smooth_slope2);
int iSetVPSS_DIEFRMMTNSMTHSLPframe_motion_smooth_slope3(unsigned int uframe_motion_smooth_slope3);
int iSetVPSS_DIEFRMMTNSMTHSLPframe_motion_smooth_ratio0(unsigned int uframe_motion_smooth_ratio0);
int iSetVPSS_DIEFRMMTNSMTHRATframe_motion_smooth_ratio1(unsigned int uframe_motion_smooth_ratio1);
int iSetVPSS_DIEFRMMTNSMTHRATframe_motion_smooth_ratio2(unsigned int uframe_motion_smooth_ratio2);
int iSetVPSS_DIEFRMMTNSMTHRATframe_motion_smooth_ratio3(unsigned int uframe_motion_smooth_ratio3);
int iSetVPSS_DIEFRMMTNSMTHRATframe_motion_smooth_ratio4(unsigned int uframe_motion_smooth_ratio4);
int iSetVPSS_DIEFRMFLDBLENDTHD0frame_field_blend_thd0(unsigned int uframe_field_blend_thd0);
int iSetVPSS_DIEFRMFLDBLENDTHD0frame_field_blend_thd1(unsigned int uframe_field_blend_thd1);
int iSetVPSS_DIEFRMFLDBLENDTHD0frame_field_blend_thd2(unsigned int uframe_field_blend_thd2);
int iSetVPSS_DIEFRMFLDBLENDTHD0frame_field_blend_thd3(unsigned int uframe_field_blend_thd3);
int iSetVPSS_DIEFRMFLDBLENDTHD1frame_field_blend_thd4(unsigned int uframe_field_blend_thd4);
int iSetVPSS_DIEFRMFLDBLENDTHD1frame_field_blend_thd5(unsigned int uframe_field_blend_thd5);
int iSetVPSS_DIEFRMFLDBLENDTHD1frame_field_blend_ratio_min(unsigned int uframe_field_blend_ratio_min);
int iSetVPSS_DIEFRMFLDBLENDTHD1frame_field_blend_ratio_max(unsigned int uframe_field_blend_ratio_max);
int iSetVPSS_DIEFRMFLDBLENDSLPframe_field_blend_slope0(unsigned int uframe_field_blend_slope0);
int iSetVPSS_DIEFRMFLDBLENDSLPframe_field_blend_slope1(unsigned int uframe_field_blend_slope1);
int iSetVPSS_DIEFRMFLDBLENDSLPframe_field_blend_slope2(unsigned int uframe_field_blend_slope2);
int iSetVPSS_DIEFRMFLDBLENDSLPframe_field_blend_slope3(unsigned int uframe_field_blend_slope3);
int iSetVPSS_DIEFRMFLDBLENDSLPframe_field_blend_ratio0(unsigned int uframe_field_blend_ratio0);
int iSetVPSS_DIEFRMFLDBLENDRATframe_field_blend_ratio1(unsigned int uframe_field_blend_ratio1);
int iSetVPSS_DIEFRMFLDBLENDRATframe_field_blend_ratio2(unsigned int uframe_field_blend_ratio2);
int iSetVPSS_DIEFRMFLDBLENDRATframe_field_blend_ratio3(unsigned int uframe_field_blend_ratio3);
int iSetVPSS_DIEFRMFLDBLENDRATframe_field_blend_ratio4(unsigned int uframe_field_blend_ratio4);
int iSetVPSS_DIEMTNADJmotion_adjust_gain(unsigned int umotion_adjust_gain);
int iSetVPSS_DIEMTNADJmotion_adjust_coring(unsigned int umotion_adjust_coring);
int iSetVPSS_DIEMTNADJmotion_adjust_gain_chr(unsigned int umotion_adjust_gain_chr);
int iSetVPSS_DIEGLBMTNTHD0motion_thd0(unsigned int umotion_thd0);
int iSetVPSS_DIEGLBMTNTHD0motion_thd1(unsigned int umotion_thd1);
int iSetVPSS_DIEGLBMTNTHD1motion_thd2(unsigned int umotion_thd2);
int iSetVPSS_DIEGLBMTNTHD1motion_thd3(unsigned int umotion_thd3);
int iSetVPSS_CCRSCLR0no_ccr_detect_thd(unsigned int uno_ccr_detect_thd);
int iSetVPSS_CCRSCLR0no_ccr_detect_max(unsigned int uno_ccr_detect_max);
int iSetVPSS_CCRSCLR0chroma_ma_offset(unsigned int uchroma_ma_offset);
int iSetVPSS_CCRSCLR0chroma_ccr_en(unsigned int uchroma_ccr_en);
int iSetVPSS_CCRSCLR1max_xchroma(unsigned int umax_xchroma);
int iSetVPSS_CCRSCLR1no_ccr_detect_blend(unsigned int uno_ccr_detect_blend);
int iSetVPSS_CCRSCLR1similar_thd(unsigned int usimilar_thd);
int iSetVPSS_CCRSCLR1similar_max(unsigned int usimilar_max);
int iSetVPSS_PDPHISTTHD1hist_thd0(unsigned int uhist_thd0);
int iSetVPSS_PDPHISTTHD1hist_thd1(unsigned int uhist_thd1);
int iSetVPSS_PDPHISTTHD1hist_thd2(unsigned int uhist_thd2);
int iSetVPSS_PDPHISTTHD1hist_thd3(unsigned int uhist_thd3);
int iSetVPSS_PDPCCMOVmov_coring_blk(unsigned int umov_coring_blk);
int iSetVPSS_PDPCCMOVmov_coring_tkr(unsigned int umov_coring_tkr);
int iSetVPSS_PDPCCMOVmov_coring_norm(unsigned int umov_coring_norm);
int iSetVPSS_PDCTRLbitsmov2r(unsigned int ubitsmov2r);
int iSetVPSS_PDCTRLlasi_mode(unsigned int ulasi_mode);
int iSetVPSS_PDCTRLedge_smooth_ratio(unsigned int uedge_smooth_ratio);
int iSetVPSS_PDCTRLdir_mch_c(unsigned int udir_mch_c);
int iSetVPSS_PDCTRLedge_smooth_en(unsigned int uedge_smooth_en);
int iSetVPSS_PDCTRLdir_mch_l(unsigned int udir_mch_l);
int iSetVPSS_PDBLKTHDstillblk_thd(unsigned int ustillblk_thd);
int iSetVPSS_PDBLKTHDdiff_movblk_thd(unsigned int udiff_movblk_thd);
int iSetVPSS_PDHISTTHDmon_tkr_thr(unsigned int umon_tkr_thr);
int iSetVPSS_PDHISTTHDmon_start_idx(unsigned int umon_start_idx);
int iSetVPSS_PDUMTHDum_thd0(unsigned int uum_thd0);
int iSetVPSS_PDUMTHDum_thd1(unsigned int uum_thd1);
int iSetVPSS_PDUMTHDum_thd2(unsigned int uum_thd2);
int iSetVPSS_PDPCCCORINGcoring_tkr(unsigned int ucoring_tkr);
int iSetVPSS_PDPCCCORINGcoring_norm(unsigned int ucoring_norm);
int iSetVPSS_PDPCCCORINGcoring_blk(unsigned int ucoring_blk);
int iSetVPSS_PDPCCHTHDpcc_hthd(unsigned int upcc_hthd);
int iSetVPSS_PDPCCVTHDpcc_vthd0(unsigned int upcc_vthd0);
int iSetVPSS_PDPCCVTHDpcc_vthd1(unsigned int upcc_vthd1);
int iSetVPSS_PDPCCVTHDpcc_vthd2(unsigned int upcc_vthd2);
int iSetVPSS_PDPCCVTHDpcc_vthd3(unsigned int upcc_vthd3);
int iSetVPSS_PDITDIFFVTHDitdiff_vthd0(unsigned int uitdiff_vthd0);
int iSetVPSS_PDITDIFFVTHDitdiff_vthd1(unsigned int uitdiff_vthd1);
int iSetVPSS_PDITDIFFVTHDitdiff_vthd2(unsigned int uitdiff_vthd2);
int iSetVPSS_PDITDIFFVTHDitdiff_vthd3(unsigned int uitdiff_vthd3);
int iSetVPSS_PDLASITHDlasi_coring_thd(unsigned int ulasi_coring_thd);
int iSetVPSS_PDLASITHDlasi_edge_thd(unsigned int ulasi_edge_thd);
int iSetVPSS_PDLASITHDlasi_mov_thd(unsigned int ulasi_mov_thd);
int iSetVPSS_PDLASIMODE0COEFlasi_txt_alpha(unsigned int ulasi_txt_alpha);
int iSetVPSS_PDLASIMODE0COEFlasi_txt_coring(unsigned int ulasi_txt_coring);
int iSetVPSS_PDLASIMODE1COEFlasi_txt_thd0(unsigned int ulasi_txt_thd0);
int iSetVPSS_PDLASIMODE1COEFlasi_txt_thd1(unsigned int ulasi_txt_thd1);
int iSetVPSS_PDLASIMODE1COEFlasi_txt_thd2(unsigned int ulasi_txt_thd2);
int iSetVPSS_PDLASIMODE1COEFlasi_txt_thd3(unsigned int ulasi_txt_thd3);
int iSetVPSS_PDREGIONregion1_y_end(unsigned int uregion1_y_end);
int iSetVPSS_PDREGIONregion1_y_stt(unsigned int uregion1_y_stt);
int iSetVPSS_VHD0_HSPhratio(unsigned int uhratio);
int iSetVPSS_VHD0_HSPhfir_order(unsigned int uhfir_order);
int iSetVPSS_VHD0_HSPhchfir_en(unsigned int uhchfir_en);
int iSetVPSS_VHD0_HSPhlfir_en(unsigned int uhlfir_en);
int iSetVPSS_VHD0_HSPhchmid_en(unsigned int uhchmid_en);
int iSetVPSS_VHD0_HSPhlmid_en(unsigned int uhlmid_en);
int iSetVPSS_VHD0_HSPhchmsc_en(unsigned int uhchmsc_en);
int iSetVPSS_VHD0_HSPhlmsc_en(unsigned int uhlmsc_en);
int iSetVPSS_VHD0_HLOFFSEThor_loffset(unsigned int uhor_loffset);
int iSetVPSS_VHD0_HCOFFSEThor_coffset(unsigned int uhor_coffset);
int iSetVPSS_VHD0_VSPzme_in_fmt(unsigned int uzme_in_fmt);
int iSetVPSS_VHD0_VSPzme_out_fmt(unsigned int uzme_out_fmt);
int iSetVPSS_VHD0_VSPvchfir_en(unsigned int uvchfir_en);
int iSetVPSS_VHD0_VSPvlfir_en(unsigned int uvlfir_en);
int iSetVPSS_VHD0_VSPvchmid_en(unsigned int uvchmid_en);
int iSetVPSS_VHD0_VSPvlmid_en(unsigned int uvlmid_en);
int iSetVPSS_VHD0_VSPvchmsc_en(unsigned int uvchmsc_en);
int iSetVPSS_VHD0_VSPvlmsc_en(unsigned int uvlmsc_en);
int iSetVPSS_VHD0_VSRvratio(unsigned int uvratio);
int iSetVPSS_VHD0_VOFFSETvchroma_offset(unsigned int uvchroma_offset);
int iSetVPSS_VHD0_VOFFSETvluma_offset(unsigned int uvluma_offset);
int iSetVPSS_VSD_HSPhratio(unsigned int uhratio);
int iSetVPSS_VSD_HSPhfir_order(unsigned int uhfir_order);
int iSetVPSS_VSD_HSPhchfir_en(unsigned int uhchfir_en);
int iSetVPSS_VSD_HSPhlfir_en(unsigned int uhlfir_en);
int iSetVPSS_VSD_HSPhchmid_en(unsigned int uhchmid_en);
int iSetVPSS_VSD_HSPhlmid_en(unsigned int uhlmid_en);
int iSetVPSS_VSD_HSPhchmsc_en(unsigned int uhchmsc_en);
int iSetVPSS_VSD_HSPhlmsc_en(unsigned int uhlmsc_en);
int iSetVPSS_VSD_HLOFFSEThor_loffset(unsigned int uhor_loffset);
int iSetVPSS_VSD_HCOFFSEThor_coffset(unsigned int uhor_coffset);
int iSetVPSS_VSD_VSPzme_in_fmt(unsigned int uzme_in_fmt);
int iSetVPSS_VSD_VSPzme_out_fmt(unsigned int uzme_out_fmt);
int iSetVPSS_VSD_VSPvchfir_en(unsigned int uvchfir_en);
int iSetVPSS_VSD_VSPvlfir_en(unsigned int uvlfir_en);
int iSetVPSS_VSD_VSPvchmid_en(unsigned int uvchmid_en);
int iSetVPSS_VSD_VSPvlmid_en(unsigned int uvlmid_en);
int iSetVPSS_VSD_VSPvchmsc_en(unsigned int uvchmsc_en);
int iSetVPSS_VSD_VSPvlmsc_en(unsigned int uvlmsc_en);
int iSetVPSS_VSD_VSRvratio(unsigned int uvratio);
int iSetVPSS_VSD_VOFFSETvchroma_offset(unsigned int uvchroma_offset);
int iSetVPSS_VSD_VOFFSETvluma_offset(unsigned int uvluma_offset);
int iSetVPSS_HSPCFG1hsp_hf0_tmp0(unsigned int uhsp_hf0_tmp0);
int iSetVPSS_HSPCFG1hsp_hf0_tmp1(unsigned int uhsp_hf0_tmp1);
int iSetVPSS_HSPCFG1hsp_hf0_tmp2(unsigned int uhsp_hf0_tmp2);
int iSetVPSS_HSPCFG1hsp_hf0_tmp3(unsigned int uhsp_hf0_tmp3);
int iSetVPSS_HSPCFG2hsp_hf0_coring(unsigned int uhsp_hf0_coring);
int iSetVPSS_HSPCFG3hsp_hf0_gainpos(unsigned int uhsp_hf0_gainpos);
int iSetVPSS_HSPCFG3hsp_hf0_gainneg(unsigned int uhsp_hf0_gainneg);
int iSetVPSS_HSPCFG4hsp_hf0_overth(unsigned int uhsp_hf0_overth);
int iSetVPSS_HSPCFG4hsp_hf0_underth(unsigned int uhsp_hf0_underth);
int iSetVPSS_HSPCFG4hsp_hf0_mixratio(unsigned int uhsp_hf0_mixratio);
int iSetVPSS_HSPCFG4hsp_hf0_winsize(unsigned int uhsp_hf0_winsize);
int iSetVPSS_HSPCFG4hsp_hf0_adpshoot_en(unsigned int uhsp_hf0_adpshoot_en);
int iSetVPSS_HSPCFG5hsp_hf1_tmp0(unsigned int uhsp_hf1_tmp0);
int iSetVPSS_HSPCFG5hsp_hf1_tmp1(unsigned int uhsp_hf1_tmp1);
int iSetVPSS_HSPCFG5hsp_hf1_tmp2(unsigned int uhsp_hf1_tmp2);
int iSetVPSS_HSPCFG5hsp_hf1_tmp3(unsigned int uhsp_hf1_tmp3);
int iSetVPSS_HSPCFG6hsp_hf1_coring(unsigned int uhsp_hf1_coring);
int iSetVPSS_HSPCFG7hsp_hf1_gainpos(unsigned int uhsp_hf1_gainpos);
int iSetVPSS_HSPCFG7hsp_hf1_gainneg(unsigned int uhsp_hf1_gainneg);
int iSetVPSS_HSPCFG8hsp_hf1_overth(unsigned int uhsp_hf1_overth);
int iSetVPSS_HSPCFG8hsp_hf1_underth(unsigned int uhsp_hf1_underth);
int iSetVPSS_HSPCFG8hsp_hf1_mixratio(unsigned int uhsp_hf1_mixratio);
int iSetVPSS_HSPCFG8hsp_hf1_winsize(unsigned int uhsp_hf1_winsize);
int iSetVPSS_HSPCFG8hsp_hf1_adpshoot_en(unsigned int uhsp_hf1_adpshoot_en);
int iSetVPSS_HSPCFG9hsp_cdti_gain(unsigned int uhsp_cdti_gain);
int iSetVPSS_HSPCFG9hsp_ldti_gain(unsigned int uhsp_ldti_gain);
int iSetVPSS_HSPCFG9hsp_lti_ratio(unsigned int uhsp_lti_ratio);
int iSetVPSS_HSPCFG9hsp_hf_shootdiv(unsigned int uhsp_hf_shootdiv);
int iSetVPSS_HSPCFG9hsp_ctih_en(unsigned int uhsp_ctih_en);
int iSetVPSS_HSPCFG9hsp_ltih_en(unsigned int uhsp_ltih_en);
int iSetVPSS_HSPCFG9hsp_h1_en(unsigned int uhsp_h1_en);
int iSetVPSS_HSPCFG9hsp_h0_en(unsigned int uhsp_h0_en);
int iSetVPSS_HSPCFG10hsp_glb_underth(unsigned int uhsp_glb_underth);
int iSetVPSS_HSPCFG10hsp_mk_en(unsigned int uhsp_mk_en);
int iSetVPSS_HSPCFG10hsp_glb_overth(unsigned int uhsp_glb_overth);
int iSetVPSS_HSPCFG10hsp_mk_mode(unsigned int uhsp_mk_mode);
int iSetVPSS_HSPCFG10hsp_peak_ratio(unsigned int uhsp_peak_ratio);
int iSetVPSS_DR_CTRLenep(unsigned int uenep);
int iSetVPSS_DR_CTRLenovt(unsigned int uenovt);
int iSetVPSS_DR_CTRLenstradjstbylm(unsigned int uenstradjstbylm);
int iSetVPSS_DR_CTRLenangadjstbylm(unsigned int uenangadjstbylm);
int iSetVPSS_DR_CTRLclipmode(unsigned int uclipmode);
int iSetVPSS_DR_CTRLdemo_en(unsigned int udemo_en);
int iSetVPSS_DR_CTRLdemo_mode(unsigned int udemo_mode);
int iSetVPSS_DR_THRregthrmdfangctrst(unsigned int uregthrmdfangctrst);
int iSetVPSS_DR_THRregthrovshtminang(unsigned int uregthrovshtminang);
int iSetVPSS_DR_THRregdrstrenth(unsigned int uregdrstrenth);
int iSetVPSS_DR_THRregovtstrenth(unsigned int uregovtstrenth);
int iSetVPSS_DRLSWSTRLUT0lswstrlut00(unsigned int ulswstrlut00);
int iSetVPSS_DRLSWSTRLUT0lswstrlut10(unsigned int ulswstrlut10);
int iSetVPSS_DRLSWSTRLUT0lswstrlut20(unsigned int ulswstrlut20);
int iSetVPSS_DRLSWSTRLUT0lswstrlut30(unsigned int ulswstrlut30);
int iSetVPSS_DRLSWSTRLUT0lswstrlut40(unsigned int ulswstrlut40);
int iSetVPSS_DRLSWSTRLUT0lswstrlut50(unsigned int ulswstrlut50);
int iSetVPSS_DRLSWSTRLUT1lswstrlut01(unsigned int ulswstrlut01);
int iSetVPSS_DRLSWSTRLUT1lswstrlut11(unsigned int ulswstrlut11);
int iSetVPSS_DRLSWSTRLUT1lswstrlut21(unsigned int ulswstrlut21);
int iSetVPSS_DRLSWSTRLUT1lswstrlut31(unsigned int ulswstrlut31);
int iSetVPSS_DRLSWSTRLUT1lswstrlut41(unsigned int ulswstrlut41);
int iSetVPSS_DRLSWSTRLUT1lswstrlut51(unsigned int ulswstrlut51);
int iSetVPSS_DRLSWSTRLUT2lswstrlut02(unsigned int ulswstrlut02);
int iSetVPSS_DRLSWSTRLUT2lswstrlut12(unsigned int ulswstrlut12);
int iSetVPSS_DRLSWSTRLUT2lswstrlut22(unsigned int ulswstrlut22);
int iSetVPSS_DRLSWSTRLUT2lswstrlut32(unsigned int ulswstrlut32);
int iSetVPSS_DRLSWSTRLUT2lswstrlut42(unsigned int ulswstrlut42);
int iSetVPSS_DRLSWSTRLUT2lswstrlut52(unsigned int ulswstrlut52);
int iSetVPSS_DRLSWSTRLUT3lswstrlut03(unsigned int ulswstrlut03);
int iSetVPSS_DRLSWSTRLUT3lswstrlut13(unsigned int ulswstrlut13);
int iSetVPSS_DRLSWSTRLUT3lswstrlut23(unsigned int ulswstrlut23);
int iSetVPSS_DRLSWSTRLUT3lswstrlut33(unsigned int ulswstrlut33);
int iSetVPSS_DRLSWSTRLUT3lswstrlut43(unsigned int ulswstrlut43);
int iSetVPSS_DRLSWSTRLUT3lswstrlut53(unsigned int ulswstrlut53);
int iSetVPSS_DRLSWSTRLUT4lswstrlut04(unsigned int ulswstrlut04);
int iSetVPSS_DRLSWSTRLUT4lswstrlut14(unsigned int ulswstrlut14);
int iSetVPSS_DRLSWSTRLUT4lswstrlut24(unsigned int ulswstrlut24);
int iSetVPSS_DRLSWSTRLUT4lswstrlut34(unsigned int ulswstrlut34);
int iSetVPSS_DRLSWSTRLUT4lswstrlut44(unsigned int ulswstrlut44);
int iSetVPSS_DRLSWSTRLUT4lswstrlut54(unsigned int ulswstrlut54);
int iSetVPSS_DRLSWSTRLUT5lswstrlut05(unsigned int ulswstrlut05);
int iSetVPSS_DRLSWSTRLUT5lswstrlut15(unsigned int ulswstrlut15);
int iSetVPSS_DRLSWSTRLUT5lswstrlut25(unsigned int ulswstrlut25);
int iSetVPSS_DRLSWSTRLUT5lswstrlut35(unsigned int ulswstrlut35);
int iSetVPSS_DRLSWSTRLUT5lswstrlut45(unsigned int ulswstrlut45);
int iSetVPSS_DRLSWSTRLUT5lswstrlut55(unsigned int ulswstrlut55);
int iSetVPSS_DRLSWSTRLUT6lswstrlut06(unsigned int ulswstrlut06);
int iSetVPSS_DRLSWSTRLUT6lswstrlut16(unsigned int ulswstrlut16);
int iSetVPSS_DRLSWSTRLUT6lswstrlut26(unsigned int ulswstrlut26);
int iSetVPSS_DRLSWSTRLUT6lswstrlut36(unsigned int ulswstrlut36);
int iSetVPSS_DRLSWSTRLUT6lswstrlut46(unsigned int ulswstrlut46);
int iSetVPSS_DRLSWSTRLUT6lswstrlut56(unsigned int ulswstrlut56);
int iSetVPSS_DRLSWSTRLUT7lswstrlut07(unsigned int ulswstrlut07);
int iSetVPSS_DRLSWSTRLUT7lswstrlut17(unsigned int ulswstrlut17);
int iSetVPSS_DRLSWSTRLUT7lswstrlut27(unsigned int ulswstrlut27);
int iSetVPSS_DRLSWSTRLUT7lswstrlut37(unsigned int ulswstrlut37);
int iSetVPSS_DRLSWSTRLUT7lswstrlut47(unsigned int ulswstrlut47);
int iSetVPSS_DRLSWSTRLUT7lswstrlut57(unsigned int ulswstrlut57);
int iSetVPSS_DRLSWSTRLUT8lswstrlut08(unsigned int ulswstrlut08);
int iSetVPSS_DRLSWSTRLUT8lswstrlut18(unsigned int ulswstrlut18);
int iSetVPSS_DRLSWSTRLUT8lswstrlut28(unsigned int ulswstrlut28);
int iSetVPSS_DRLSWSTRLUT8lswstrlut38(unsigned int ulswstrlut38);
int iSetVPSS_DRLSWSTRLUT8lswstrlut48(unsigned int ulswstrlut48);
int iSetVPSS_DRLSWSTRLUT8lswstrlut58(unsigned int ulswstrlut58);
int iSetVPSS_DRLRWSTRLUT0lrwstrlut00(unsigned int ulrwstrlut00);
int iSetVPSS_DRLRWSTRLUT0lrwstrlut10(unsigned int ulrwstrlut10);
int iSetVPSS_DRLRWSTRLUT0lrwstrlut20(unsigned int ulrwstrlut20);
int iSetVPSS_DRLRWSTRLUT0lrwstrlut30(unsigned int ulrwstrlut30);
int iSetVPSS_DRLRWSTRLUT0lrwstrlut40(unsigned int ulrwstrlut40);
int iSetVPSS_DRLRWSTRLUT0lrwstrlut50(unsigned int ulrwstrlut50);
int iSetVPSS_DRLRWSTRLUT1lrwstrlut01(unsigned int ulrwstrlut01);
int iSetVPSS_DRLRWSTRLUT1lrwstrlut11(unsigned int ulrwstrlut11);
int iSetVPSS_DRLRWSTRLUT1lrwstrlut21(unsigned int ulrwstrlut21);
int iSetVPSS_DRLRWSTRLUT1lrwstrlut31(unsigned int ulrwstrlut31);
int iSetVPSS_DRLRWSTRLUT1lrwstrlut41(unsigned int ulrwstrlut41);
int iSetVPSS_DRLRWSTRLUT1lrwstrlut51(unsigned int ulrwstrlut51);
int iSetVPSS_DRLRWSTRLUT2lrwstrlut02(unsigned int ulrwstrlut02);
int iSetVPSS_DRLRWSTRLUT2lrwstrlut12(unsigned int ulrwstrlut12);
int iSetVPSS_DRLRWSTRLUT2lrwstrlut22(unsigned int ulrwstrlut22);
int iSetVPSS_DRLRWSTRLUT2lrwstrlut32(unsigned int ulrwstrlut32);
int iSetVPSS_DRLRWSTRLUT2lrwstrlut42(unsigned int ulrwstrlut42);
int iSetVPSS_DRLRWSTRLUT2lrwstrlut52(unsigned int ulrwstrlut52);
int iSetVPSS_DRLRWSTRLUT3lrwstrlut03(unsigned int ulrwstrlut03);
int iSetVPSS_DRLRWSTRLUT3lrwstrlut13(unsigned int ulrwstrlut13);
int iSetVPSS_DRLRWSTRLUT3lrwstrlut23(unsigned int ulrwstrlut23);
int iSetVPSS_DRLRWSTRLUT3lrwstrlut33(unsigned int ulrwstrlut33);
int iSetVPSS_DRLRWSTRLUT3lrwstrlut43(unsigned int ulrwstrlut43);
int iSetVPSS_DRLRWSTRLUT3lrwstrlut53(unsigned int ulrwstrlut53);
int iSetVPSS_DRLRWSTRLUT4lrwstrlut04(unsigned int ulrwstrlut04);
int iSetVPSS_DRLRWSTRLUT4lrwstrlut14(unsigned int ulrwstrlut14);
int iSetVPSS_DRLRWSTRLUT4lrwstrlut24(unsigned int ulrwstrlut24);
int iSetVPSS_DRLRWSTRLUT4lrwstrlut34(unsigned int ulrwstrlut34);
int iSetVPSS_DRLRWSTRLUT4lrwstrlut44(unsigned int ulrwstrlut44);
int iSetVPSS_DRLRWSTRLUT4lrwstrlut54(unsigned int ulrwstrlut54);
int iSetVPSS_DRLRWSTRLUT5lrwstrlut05(unsigned int ulrwstrlut05);
int iSetVPSS_DRLRWSTRLUT5lrwstrlut15(unsigned int ulrwstrlut15);
int iSetVPSS_DRLRWSTRLUT5lrwstrlut25(unsigned int ulrwstrlut25);
int iSetVPSS_DRLRWSTRLUT5lrwstrlut35(unsigned int ulrwstrlut35);
int iSetVPSS_DRLRWSTRLUT5lrwstrlut45(unsigned int ulrwstrlut45);
int iSetVPSS_DRLRWSTRLUT5lrwstrlut55(unsigned int ulrwstrlut55);
int iSetVPSS_DRLRWSTRLUT6lrwstrlut06(unsigned int ulrwstrlut06);
int iSetVPSS_DRLRWSTRLUT6lrwstrlut16(unsigned int ulrwstrlut16);
int iSetVPSS_DRLRWSTRLUT6lrwstrlut26(unsigned int ulrwstrlut26);
int iSetVPSS_DRLRWSTRLUT6lrwstrlut36(unsigned int ulrwstrlut36);
int iSetVPSS_DRLRWSTRLUT6lrwstrlut46(unsigned int ulrwstrlut46);
int iSetVPSS_DRLRWSTRLUT6lrwstrlut56(unsigned int ulrwstrlut56);
int iSetVPSS_DRLRWSTRLUT7lrwstrlut07(unsigned int ulrwstrlut07);
int iSetVPSS_DRLRWSTRLUT7lrwstrlut17(unsigned int ulrwstrlut17);
int iSetVPSS_DRLRWSTRLUT7lrwstrlut27(unsigned int ulrwstrlut27);
int iSetVPSS_DRLRWSTRLUT7lrwstrlut37(unsigned int ulrwstrlut37);
int iSetVPSS_DRLRWSTRLUT7lrwstrlut47(unsigned int ulrwstrlut47);
int iSetVPSS_DRLRWSTRLUT7lrwstrlut57(unsigned int ulrwstrlut57);
int iSetVPSS_DRLRWSTRLUT8lrwstrlut08(unsigned int ulrwstrlut08);
int iSetVPSS_DRLRWSTRLUT8lrwstrlut18(unsigned int ulrwstrlut18);
int iSetVPSS_DRLRWSTRLUT8lrwstrlut28(unsigned int ulrwstrlut28);
int iSetVPSS_DRLRWSTRLUT8lrwstrlut38(unsigned int ulrwstrlut38);
int iSetVPSS_DRLRWSTRLUT8lrwstrlut48(unsigned int ulrwstrlut48);
int iSetVPSS_DRLRWSTRLUT8lrwstrlut58(unsigned int ulrwstrlut58);
int iSetVPSS_DRLSWSTRADJUSTLUT0dr_lswadjlut0(unsigned int udr_lswadjlut0);
int iSetVPSS_DRLSWSTRADJUSTLUT0dr_lswadjlut1(unsigned int udr_lswadjlut1);
int iSetVPSS_DRLSWSTRADJUSTLUT0dr_lswadjlut2(unsigned int udr_lswadjlut2);
int iSetVPSS_DRLSWSTRADJUSTLUT1dr_lswadjlut3(unsigned int udr_lswadjlut3);
int iSetVPSS_DRLSWSTRADJUSTLUT1dr_lswadjlut4(unsigned int udr_lswadjlut4);
int iSetVPSS_DRLSWSTRADJUSTLUT1dr_lswadjlut5(unsigned int udr_lswadjlut5);
int iSetVPSS_DRLSWSTRADJUSTLUT2dr_lswadjlut6(unsigned int udr_lswadjlut6);
int iSetVPSS_DRLSWSTRADJUSTLUT2dr_lswadjlut7(unsigned int udr_lswadjlut7);
int iSetVPSS_DRLSWSTRADJUSTLUT2dr_lswadjlut8(unsigned int udr_lswadjlut8);
int iSetVPSS_DRLRWSTRADJUSTLUT0dr_lrwadjlut0(unsigned int udr_lrwadjlut0);
int iSetVPSS_DRLRWSTRADJUSTLUT0dr_lrwadjlut1(unsigned int udr_lrwadjlut1);
int iSetVPSS_DRLRWSTRADJUSTLUT0dr_lrwadjlut2(unsigned int udr_lrwadjlut2);
int iSetVPSS_DRLRWSTRADJUSTLUT1dr_lrwadjlut3(unsigned int udr_lrwadjlut3);
int iSetVPSS_DRLRWSTRADJUSTLUT1dr_lrwadjlut4(unsigned int udr_lrwadjlut4);
int iSetVPSS_DRLRWSTRADJUSTLUT1dr_lrwadjlut5(unsigned int udr_lrwadjlut5);
int iSetVPSS_DRLRWSTRADJUSTLUT2dr_lrwadjlut6(unsigned int udr_lrwadjlut6);
int iSetVPSS_DRLRWSTRADJUSTLUT2dr_lrwadjlut7(unsigned int udr_lrwadjlut7);
int iSetVPSS_DRLRWSTRADJUSTLUT2dr_lrwadjlut8(unsigned int udr_lrwadjlut8);
int iSetVPSS_DRANGADJSUTLUT0dr_angadjlut0(unsigned int udr_angadjlut0);
int iSetVPSS_DRANGADJSUTLUT0dr_angadjlut1(unsigned int udr_angadjlut1);
int iSetVPSS_DRANGADJSUTLUT0dr_angadjlut2(unsigned int udr_angadjlut2);
int iSetVPSS_DRANGADJSUTLUT1dr_angadjlut3(unsigned int udr_angadjlut3);
int iSetVPSS_DRANGADJSUTLUT1dr_angadjlut4(unsigned int udr_angadjlut4);
int iSetVPSS_DRANGADJSUTLUT1dr_angadjlut5(unsigned int udr_angadjlut5);
int iSetVPSS_DRANGADJSUTLUT2dr_angadjlut6(unsigned int udr_angadjlut6);
int iSetVPSS_DRANGADJSUTLUT2dr_angadjlut7(unsigned int udr_angadjlut7);
int iSetVPSS_DRANGADJSUTLUT2dr_angadjlut8(unsigned int udr_angadjlut8);
int iSetVPSS_DRANGLESTRLUT1_0dr_angdifflut0(unsigned int udr_angdifflut0);
int iSetVPSS_DRANGLESTRLUT1_0dr_angdifflut1(unsigned int udr_angdifflut1);
int iSetVPSS_DRANGLESTRLUT1_0dr_angdifflut2(unsigned int udr_angdifflut2);
int iSetVPSS_DRANGLESTRLUT1_0dr_angdifflut3(unsigned int udr_angdifflut3);
int iSetVPSS_DRANGLESTRLUT1_0dr_angdifflut4(unsigned int udr_angdifflut4);
int iSetVPSS_DRANGLESTRLUT1_0dr_angdifflut5(unsigned int udr_angdifflut5);
int iSetVPSS_DRANGLESTRLUT1_1dr_angdifflut6(unsigned int udr_angdifflut6);
int iSetVPSS_DRANGLESTRLUT1_1dr_angdifflut7(unsigned int udr_angdifflut7);
int iSetVPSS_DRANGLESTRLUT1_1dr_angdifflut8(unsigned int udr_angdifflut8);
int iSetVPSS_DRANGLESTRLUT1_1dr_angdifflut9(unsigned int udr_angdifflut9);
int iSetVPSS_DRANGLESTRLUT1_1dr_angdifflut10(unsigned int udr_angdifflut10);
int iSetVPSS_DRANGLESTRLUT1_1dr_angdifflut11(unsigned int udr_angdifflut11);
int iSetVPSS_DRANGLESTRLUT1_2dr_angdifflut12(unsigned int udr_angdifflut12);
int iSetVPSS_DRANGLESTRLUT1_2dr_angdifflut13(unsigned int udr_angdifflut13);
int iSetVPSS_DRANGLESTRLUT1_2dr_angdifflut14(unsigned int udr_angdifflut14);
int iSetVPSS_DRANGLESTRLUT1_2dr_angdifflut15(unsigned int udr_angdifflut15);
int iSetVPSS_DRANGLESTRLUT1_2dr_angdifflut16(unsigned int udr_angdifflut16);
int iSetVPSS_DRANGLESTRLUT2_0dr_angminlut0(unsigned int udr_angminlut0);
int iSetVPSS_DRANGLESTRLUT2_0dr_angminlut1(unsigned int udr_angminlut1);
int iSetVPSS_DRANGLESTRLUT2_0dr_angminlut2(unsigned int udr_angminlut2);
int iSetVPSS_DRANGLESTRLUT2_0dr_angminlut3(unsigned int udr_angminlut3);
int iSetVPSS_DRANGLESTRLUT2_0dr_angminlut4(unsigned int udr_angminlut4);
int iSetVPSS_DRANGLESTRLUT2_0dr_angminlut5(unsigned int udr_angminlut5);
int iSetVPSS_DRANGLESTRLUT2_1dr_angminlut6(unsigned int udr_angminlut6);
int iSetVPSS_DRANGLESTRLUT2_1dr_angminlut7(unsigned int udr_angminlut7);
int iSetVPSS_DRANGLESTRLUT2_1dr_angminlut8(unsigned int udr_angminlut8);
int iSetVPSS_DRANGLESTRLUT2_1dr_angminlut9(unsigned int udr_angminlut9);
int iSetVPSS_DRANGLESTRLUT2_1dr_angminlut10(unsigned int udr_angminlut10);
int iSetVPSS_DRANGLESTRLUT2_1dr_angminlut11(unsigned int udr_angminlut11);
int iSetVPSS_DRANGLESTRLUT2_2dr_angminlut12(unsigned int udr_angminlut12);
int iSetVPSS_DRANGLESTRLUT2_2dr_angminlut13(unsigned int udr_angminlut13);
int iSetVPSS_DRANGLESTRLUT2_2dr_angminlut14(unsigned int udr_angminlut14);
int iSetVPSS_DRANGLESTRLUT2_2dr_angminlut15(unsigned int udr_angminlut15);
int iSetVPSS_DRANGLESTRLUT2_2dr_angminlut16(unsigned int udr_angminlut16);
int iSetVPSS_DROVTSTRADJUSTLUT0dr_ovadjlut0(unsigned int udr_ovadjlut0);
int iSetVPSS_DROVTSTRADJUSTLUT0dr_ovadjlut1(unsigned int udr_ovadjlut1);
int iSetVPSS_DROVTSTRADJUSTLUT0dr_ovadjlut2(unsigned int udr_ovadjlut2);
int iSetVPSS_DROVTSTRADJUSTLUT1dr_ovadjlut3(unsigned int udr_ovadjlut3);
int iSetVPSS_DROVTSTRADJUSTLUT1dr_ovadjlut4(unsigned int udr_ovadjlut4);
int iSetVPSS_DROVTSTRADJUSTLUT1dr_ovadjlut5(unsigned int udr_ovadjlut5);
int iSetVPSS_DROVTSTRADJUSTLUT2dr_ovadjlut6(unsigned int udr_ovadjlut6);
int iSetVPSS_DROVTSTRADJUSTLUT2dr_ovadjlut7(unsigned int udr_ovadjlut7);
int iSetVPSS_DROVTSTRADJUSTLUT2dr_ovadjlut8(unsigned int udr_ovadjlut8);
int iSetVPSS_DROVTSTRLUT0dr_ovstrlut0(unsigned int udr_ovstrlut0);
int iSetVPSS_DROVTSTRLUT0dr_ovstrlut1(unsigned int udr_ovstrlut1);
int iSetVPSS_DROVTSTRLUT0dr_ovstrlut2(unsigned int udr_ovstrlut2);
int iSetVPSS_DROVTSTRLUT1dr_ovstrlut3(unsigned int udr_ovstrlut3);
int iSetVPSS_DROVTSTRLUT1dr_ovstrlut4(unsigned int udr_ovstrlut4);
int iSetVPSS_DROVTSTRLUT1dr_ovstrlut5(unsigned int udr_ovstrlut5);
int iSetVPSS_DROVTSTRLUT2dr_ovstrlut6(unsigned int udr_ovstrlut6);
int iSetVPSS_DROVTSTRLUT2dr_ovstrlut7(unsigned int udr_ovstrlut7);
int iSetVPSS_DROVTSTRLUT2dr_ovstrlut8(unsigned int udr_ovstrlut8);
int iSetVPSS_VC1_CTRL0fr0_vc1_profile(unsigned int ufr0_vc1_profile);
int iSetVPSS_VC1_CTRL0fr0_vc1_rangedfrm(unsigned int ufr0_vc1_rangedfrm);
int iSetVPSS_VC1_CTRL0fr0_vc1_mapyflg(unsigned int ufr0_vc1_mapyflg);
int iSetVPSS_VC1_CTRL0fr0_vc1_mapcflg(unsigned int ufr0_vc1_mapcflg);
int iSetVPSS_VC1_CTRL0fr0_vc1_mapy(unsigned int ufr0_vc1_mapy);
int iSetVPSS_VC1_CTRL0fr0_vc1_mapc(unsigned int ufr0_vc1_mapc);
int iSetVPSS_VC1_CTRL1fr1_vc1_profile(unsigned int ufr1_vc1_profile);
int iSetVPSS_VC1_CTRL1fr1_vc1_rangedfrm(unsigned int ufr1_vc1_rangedfrm);
int iSetVPSS_VC1_CTRL1fr1_vc1_mapyflg(unsigned int ufr1_vc1_mapyflg);
int iSetVPSS_VC1_CTRL1fr1_vc1_mapcflg(unsigned int ufr1_vc1_mapcflg);
int iSetVPSS_VC1_CTRL1fr1_vc1_mapy(unsigned int ufr1_vc1_mapy);
int iSetVPSS_VC1_CTRL1fr1_vc1_mapc(unsigned int ufr1_vc1_mapc);
int iSetVPSS_VC1_CTRL2fr2_vc1_profile(unsigned int ufr2_vc1_profile);
int iSetVPSS_VC1_CTRL2fr2_vc1_rangedfrm(unsigned int ufr2_vc1_rangedfrm);
int iSetVPSS_VC1_CTRL2fr2_vc1_mapyflg(unsigned int ufr2_vc1_mapyflg);
int iSetVPSS_VC1_CTRL2fr2_vc1_mapcflg(unsigned int ufr2_vc1_mapcflg);
int iSetVPSS_VC1_CTRL2fr2_vc1_mapy(unsigned int ufr2_vc1_mapy);
int iSetVPSS_VC1_CTRL2fr2_vc1_mapc(unsigned int ufr2_vc1_mapc);
int iSetVPSS_VC1_CTRL3fr3_vc1_profile(unsigned int ufr3_vc1_profile);
int iSetVPSS_VC1_CTRL3fr3_vc1_rangedfrm(unsigned int ufr3_vc1_rangedfrm);
int iSetVPSS_VC1_CTRL3fr3_vc1_mapyflg(unsigned int ufr3_vc1_mapyflg);
int iSetVPSS_VC1_CTRL3fr3_vc1_mapcflg(unsigned int ufr3_vc1_mapcflg);
int iSetVPSS_VC1_CTRL3fr3_vc1_mapy(unsigned int ufr3_vc1_mapy);
int iSetVPSS_VC1_CTRL3fr3_vc1_mapc(unsigned int ufr3_vc1_mapc);
int iSetVPSS_DB_CTRLdb_lum_en(unsigned int udb_lum_en);
int iSetVPSS_DB_CTRLdb_lum_ver_en(unsigned int udb_lum_ver_en);
int iSetVPSS_DB_CTRLdb_lum_hor_en(unsigned int udb_lum_hor_en);
int iSetVPSS_DB_CTRLdb_cb_en(unsigned int udb_cb_en);
int iSetVPSS_DB_CTRLdb_cr_en(unsigned int udb_cr_en);
int iSetVPSS_DB_CTRLdb_chr_ver_en(unsigned int udb_chr_ver_en);
int iSetVPSS_DB_CTRLdb_chr_hor_en(unsigned int udb_chr_hor_en);
int iSetVPSS_DB_CTRLdb_chr_hor_mid_grey_en(unsigned int udb_chr_hor_mid_grey_en);
int iSetVPSS_DB_CTRLdb_demo_en(unsigned int udb_demo_en);
int iSetVPSS_DB_CTRLdb_demo_mode(unsigned int udb_demo_mode);
int iSetVPSS_DB_CTRLdet_size_en(unsigned int udet_size_en);
int iSetVPSS_DB_CTRLdet_hy_en(unsigned int udet_hy_en);
int iSetVPSS_DB_CTRLdet_hc_en(unsigned int udet_hc_en);
int iSetVPSS_DB_CTRLdet_vy_en(unsigned int udet_vy_en);
int iSetVPSS_DB_DIRgrad_sub_ratio(unsigned int ugrad_sub_ratio);
int iSetVPSS_DB_DIRctrst_thresh(unsigned int uctrst_thresh);
int iSetVPSS_DB_BLKlum_h_blk_size(unsigned int ulum_h_blk_size);
int iSetVPSS_DB_BLKlum_v_blk_size(unsigned int ulum_v_blk_size);
int iSetVPSS_DB_BLKchr_h_blk_size(unsigned int uchr_h_blk_size);
int iSetVPSS_DB_BLKchr_v_blk_size(unsigned int uchr_v_blk_size);
int iSetVPSS_DB_RATIOlum_hor_scale_ratio(unsigned int ulum_hor_scale_ratio);
int iSetVPSS_DB_RATIOlum_ver_scale_ratio(unsigned int ulum_ver_scale_ratio);
int iSetVPSS_DB_RATIOchr_hor_scale_ratio(unsigned int uchr_hor_scale_ratio);
int iSetVPSS_DB_RATIOchr_ver_scale_ratio(unsigned int uchr_ver_scale_ratio);
int iSetVPSS_DB_RATIOlum_hor_filter_sel(unsigned int ulum_hor_filter_sel);
int iSetVPSS_DB_RATIOchr_hor_filter_sel(unsigned int uchr_hor_filter_sel);
int iSetVPSS_DB_RATIOglabal_db_strenth_lum(unsigned int uglabal_db_strenth_lum);
int iSetVPSS_DB_RATIOglabal_db_strenth_chr(unsigned int uglabal_db_strenth_chr);
int iSetVPSS_DB_RATIOlum_hor_txt_win_size(unsigned int ulum_hor_txt_win_size);
int iSetVPSS_DB_LHHFlum_hor_hf_diff_core(unsigned int ulum_hor_hf_diff_core);
int iSetVPSS_DB_LHHFlum_hor_hf_diff_gain1(unsigned int ulum_hor_hf_diff_gain1);
int iSetVPSS_DB_LHHFlum_hor_hf_diff_gain2(unsigned int ulum_hor_hf_diff_gain2);
int iSetVPSS_DB_LHHFlum_hor_hf_var_core(unsigned int ulum_hor_hf_var_core);
int iSetVPSS_DB_LHHFlum_hor_bord_adj_gain(unsigned int ulum_hor_bord_adj_gain);
int iSetVPSS_DB_LHHFlum_hor_hf_var_gain1(unsigned int ulum_hor_hf_var_gain1);
int iSetVPSS_DB_LHHFlum_hor_hf_var_gain2(unsigned int ulum_hor_hf_var_gain2);
int iSetVPSS_DB_LVHFlum_ver_hf_var_core(unsigned int ulum_ver_hf_var_core);
int iSetVPSS_DB_LVHFlum_ver_bord_adj_gain(unsigned int ulum_ver_bord_adj_gain);
int iSetVPSS_DB_LVHFlum_ver_hf_var_gain1(unsigned int ulum_ver_hf_var_gain1);
int iSetVPSS_DB_LVHFlum_ver_hf_var_gain2(unsigned int ulum_ver_hf_var_gain2);
int iSetVPSS_DB_LVHFlum_hor_adj_gain(unsigned int ulum_hor_adj_gain);
int iSetVPSS_DB_LVHFlum_ver_adj_gain(unsigned int ulum_ver_adj_gain);
int iSetVPSS_DB_CTRSctrst_adj_core(unsigned int uctrst_adj_core);
int iSetVPSS_DB_CTRSdir_smooth_mode(unsigned int udir_smooth_mode);
int iSetVPSS_DB_CTRSctrst_adj_gain1(unsigned int uctrst_adj_gain1);
int iSetVPSS_DB_CTRSctrst_adj_gain2(unsigned int uctrst_adj_gain2);
int iSetVPSS_DB_CTRSmax_lum_hor_db_dist(unsigned int umax_lum_hor_db_dist);
int iSetVPSS_DB_CTRSmax_chr_hor_db_dist(unsigned int umax_chr_hor_db_dist);
int iSetVPSS_DB_LUT0lum_hor_delta_lut_p0(unsigned int ulum_hor_delta_lut_p0);
int iSetVPSS_DB_LUT0lum_hor_delta_lut_p1(unsigned int ulum_hor_delta_lut_p1);
int iSetVPSS_DB_LUT0lum_hor_delta_lut_p2(unsigned int ulum_hor_delta_lut_p2);
int iSetVPSS_DB_LUT0lum_hor_delta_lut_p3(unsigned int ulum_hor_delta_lut_p3);
int iSetVPSS_DB_LUT0lum_hor_delta_lut_p4(unsigned int ulum_hor_delta_lut_p4);
int iSetVPSS_DB_LUT0lum_hor_delta_lut_p5(unsigned int ulum_hor_delta_lut_p5);
int iSetVPSS_DB_LUT0lum_hor_delta_lut_p6(unsigned int ulum_hor_delta_lut_p6);
int iSetVPSS_DB_LUT0lum_hor_delta_lut_p7(unsigned int ulum_hor_delta_lut_p7);
int iSetVPSS_DB_LUT1lum_hor_delta_lut_p8(unsigned int ulum_hor_delta_lut_p8);
int iSetVPSS_DB_LUT1lum_hor_delta_lut_p9(unsigned int ulum_hor_delta_lut_p9);
int iSetVPSS_DB_LUT1lum_hor_delta_lut_p10(unsigned int ulum_hor_delta_lut_p10);
int iSetVPSS_DB_LUT1lum_hor_delta_lut_p11(unsigned int ulum_hor_delta_lut_p11);
int iSetVPSS_DB_LUT1lum_hor_delta_lut_p12(unsigned int ulum_hor_delta_lut_p12);
int iSetVPSS_DB_LUT1lum_hor_delta_lut_p13(unsigned int ulum_hor_delta_lut_p13);
int iSetVPSS_DB_LUT1lum_hor_delta_lut_p14(unsigned int ulum_hor_delta_lut_p14);
int iSetVPSS_DB_LUT1lum_hor_delta_lut_p15(unsigned int ulum_hor_delta_lut_p15);
int iSetVPSS_DB_LUT2lum_ver_delta_lut_p0(unsigned int ulum_ver_delta_lut_p0);
int iSetVPSS_DB_LUT2lum_ver_delta_lut_p1(unsigned int ulum_ver_delta_lut_p1);
int iSetVPSS_DB_LUT2lum_ver_delta_lut_p2(unsigned int ulum_ver_delta_lut_p2);
int iSetVPSS_DB_LUT2lum_ver_delta_lut_p3(unsigned int ulum_ver_delta_lut_p3);
int iSetVPSS_DB_LUT2lum_ver_delta_lut_p4(unsigned int ulum_ver_delta_lut_p4);
int iSetVPSS_DB_LUT2lum_ver_delta_lut_p5(unsigned int ulum_ver_delta_lut_p5);
int iSetVPSS_DB_LUT2lum_ver_delta_lut_p6(unsigned int ulum_ver_delta_lut_p6);
int iSetVPSS_DB_LUT2lum_ver_delta_lut_p7(unsigned int ulum_ver_delta_lut_p7);
int iSetVPSS_DB_LUT3lum_ver_delta_lut_p8(unsigned int ulum_ver_delta_lut_p8);
int iSetVPSS_DB_LUT3lum_ver_delta_lut_p9(unsigned int ulum_ver_delta_lut_p9);
int iSetVPSS_DB_LUT3lum_ver_delta_lut_p10(unsigned int ulum_ver_delta_lut_p10);
int iSetVPSS_DB_LUT3lum_ver_delta_lut_p11(unsigned int ulum_ver_delta_lut_p11);
int iSetVPSS_DB_LUT3lum_ver_delta_lut_p12(unsigned int ulum_ver_delta_lut_p12);
int iSetVPSS_DB_LUT3lum_ver_delta_lut_p13(unsigned int ulum_ver_delta_lut_p13);
int iSetVPSS_DB_LUT3lum_ver_delta_lut_p14(unsigned int ulum_ver_delta_lut_p14);
int iSetVPSS_DB_LUT3lum_ver_delta_lut_p15(unsigned int ulum_ver_delta_lut_p15);
int iSetVPSS_DB_LUT4chr_hor_delta_lut_p0(unsigned int uchr_hor_delta_lut_p0);
int iSetVPSS_DB_LUT4chr_hor_delta_lut_p1(unsigned int uchr_hor_delta_lut_p1);
int iSetVPSS_DB_LUT4chr_hor_delta_lut_p2(unsigned int uchr_hor_delta_lut_p2);
int iSetVPSS_DB_LUT4chr_hor_delta_lut_p3(unsigned int uchr_hor_delta_lut_p3);
int iSetVPSS_DB_LUT4chr_hor_delta_lut_p4(unsigned int uchr_hor_delta_lut_p4);
int iSetVPSS_DB_LUT4chr_hor_delta_lut_p5(unsigned int uchr_hor_delta_lut_p5);
int iSetVPSS_DB_LUT4chr_hor_delta_lut_p6(unsigned int uchr_hor_delta_lut_p6);
int iSetVPSS_DB_LUT4chr_hor_delta_lut_p7(unsigned int uchr_hor_delta_lut_p7);
int iSetVPSS_DB_LUT5chr_hor_delta_lut_p8(unsigned int uchr_hor_delta_lut_p8);
int iSetVPSS_DB_LUT5chr_hor_delta_lut_p9(unsigned int uchr_hor_delta_lut_p9);
int iSetVPSS_DB_LUT5chr_hor_delta_lut_p10(unsigned int uchr_hor_delta_lut_p10);
int iSetVPSS_DB_LUT5chr_hor_delta_lut_p11(unsigned int uchr_hor_delta_lut_p11);
int iSetVPSS_DB_LUT5chr_hor_delta_lut_p12(unsigned int uchr_hor_delta_lut_p12);
int iSetVPSS_DB_LUT5chr_hor_delta_lut_p13(unsigned int uchr_hor_delta_lut_p13);
int iSetVPSS_DB_LUT5chr_hor_delta_lut_p14(unsigned int uchr_hor_delta_lut_p14);
int iSetVPSS_DB_LUT5chr_hor_delta_lut_p15(unsigned int uchr_hor_delta_lut_p15);
int iSetVPSS_DB_LUT6lum_h_str_fade_lut_p0(unsigned int ulum_h_str_fade_lut_p0);
int iSetVPSS_DB_LUT6lum_h_str_fade_lut_p1(unsigned int ulum_h_str_fade_lut_p1);
int iSetVPSS_DB_LUT6lum_h_str_fade_lut_p2(unsigned int ulum_h_str_fade_lut_p2);
int iSetVPSS_DB_LUT6lum_h_str_fade_lut_p3(unsigned int ulum_h_str_fade_lut_p3);
int iSetVPSS_DB_LUT6lum_h_str_fade_lut_p4(unsigned int ulum_h_str_fade_lut_p4);
int iSetVPSS_DB_LUT6lum_h_str_fade_lut_p5(unsigned int ulum_h_str_fade_lut_p5);
int iSetVPSS_DB_LUT6lum_h_str_fade_lut_p6(unsigned int ulum_h_str_fade_lut_p6);
int iSetVPSS_DB_LUT6lum_h_str_fade_lut_p7(unsigned int ulum_h_str_fade_lut_p7);
int iSetVPSS_DB_LUT6lum_h_str_fade_lut_p8(unsigned int ulum_h_str_fade_lut_p8);
int iSetVPSS_DB_LUT6lum_h_str_fade_lut_p9(unsigned int ulum_h_str_fade_lut_p9);
int iSetVPSS_DB_LUT7lum_v_str_fade_lut_p0(unsigned int ulum_v_str_fade_lut_p0);
int iSetVPSS_DB_LUT7lum_v_str_fade_lut_p1(unsigned int ulum_v_str_fade_lut_p1);
int iSetVPSS_DB_LUT7lum_v_str_fade_lut_p2(unsigned int ulum_v_str_fade_lut_p2);
int iSetVPSS_DB_LUT7lum_v_str_fade_lut_p3(unsigned int ulum_v_str_fade_lut_p3);
int iSetVPSS_DB_LUT7lum_v_str_fade_lut_p4(unsigned int ulum_v_str_fade_lut_p4);
int iSetVPSS_DB_LUT7lum_v_str_fade_lut_p5(unsigned int ulum_v_str_fade_lut_p5);
int iSetVPSS_DB_LUT7lum_v_str_fade_lut_p6(unsigned int ulum_v_str_fade_lut_p6);
int iSetVPSS_DB_LUT7lum_v_str_fade_lut_p7(unsigned int ulum_v_str_fade_lut_p7);
int iSetVPSS_DB_LUT7lum_v_str_fade_lut_p8(unsigned int ulum_v_str_fade_lut_p8);
int iSetVPSS_DB_LUT7lum_v_str_fade_lut_p9(unsigned int ulum_v_str_fade_lut_p9);
int iSetVPSS_DB_LUT8chr_h_str_fade_lut_p0(unsigned int uchr_h_str_fade_lut_p0);
int iSetVPSS_DB_LUT8chr_h_str_fade_lut_p1(unsigned int uchr_h_str_fade_lut_p1);
int iSetVPSS_DB_LUT8chr_h_str_fade_lut_p2(unsigned int uchr_h_str_fade_lut_p2);
int iSetVPSS_DB_LUT8chr_h_str_fade_lut_p3(unsigned int uchr_h_str_fade_lut_p3);
int iSetVPSS_DB_LUT8chr_h_str_fade_lut_p4(unsigned int uchr_h_str_fade_lut_p4);
int iSetVPSS_DB_LUT8chr_h_str_fade_lut_p5(unsigned int uchr_h_str_fade_lut_p5);
int iSetVPSS_DB_LUT8chr_h_str_fade_lut_p6(unsigned int uchr_h_str_fade_lut_p6);
int iSetVPSS_DB_LUT8chr_h_str_fade_lut_p7(unsigned int uchr_h_str_fade_lut_p7);
int iSetVPSS_DB_LUT8chr_h_str_fade_lut_p8(unsigned int uchr_h_str_fade_lut_p8);
int iSetVPSS_DB_LUT8chr_h_str_fade_lut_p9(unsigned int uchr_h_str_fade_lut_p9);
int iSetVPSS_DB_LUT9lum_h_str_fade_lut_p10(unsigned int ulum_h_str_fade_lut_p10);
int iSetVPSS_DB_LUT9lum_h_str_fade_lut_p11(unsigned int ulum_h_str_fade_lut_p11);
int iSetVPSS_DB_LUT9lum_v_str_fade_lut_p10(unsigned int ulum_v_str_fade_lut_p10);
int iSetVPSS_DB_LUT9lum_v_str_fade_lut_p11(unsigned int ulum_v_str_fade_lut_p11);
int iSetVPSS_DB_LUT9chr_h_str_fade_lut_p10(unsigned int uchr_h_str_fade_lut_p10);
int iSetVPSS_DB_LUT9chr_h_str_fade_lut_p11(unsigned int uchr_h_str_fade_lut_p11);
int iSetVPSS_DB_LUT10dir_str_gain_lut_p0(unsigned int udir_str_gain_lut_p0);
int iSetVPSS_DB_LUT10dir_str_gain_lut_p1(unsigned int udir_str_gain_lut_p1);
int iSetVPSS_DB_LUT10dir_str_gain_lut_p2(unsigned int udir_str_gain_lut_p2);
int iSetVPSS_DB_LUT10dir_str_gain_lut_p3(unsigned int udir_str_gain_lut_p3);
int iSetVPSS_DB_LUT10dir_str_gain_lut_p4(unsigned int udir_str_gain_lut_p4);
int iSetVPSS_DB_LUT10dir_str_gain_lut_p5(unsigned int udir_str_gain_lut_p5);
int iSetVPSS_DB_LUT10dir_str_gain_lut_p6(unsigned int udir_str_gain_lut_p6);
int iSetVPSS_DB_LUT10dir_str_gain_lut_p7(unsigned int udir_str_gain_lut_p7);
int iSetVPSS_DBD_THDEDGEhy_thd_edge(unsigned int uhy_thd_edge);
int iSetVPSS_DBD_THDEDGEhc_thd_edge(unsigned int uhc_thd_edge);
int iSetVPSS_DBD_THDEDGEvy_thd_edge(unsigned int uvy_thd_edge);
int iSetVPSS_DBD_THDTXThy_thd_txt(unsigned int uhy_thd_txt);
int iSetVPSS_DBD_THDTXThc_thd_txt(unsigned int uhc_thd_txt);
int iSetVPSS_DBD_THDTXTvy_thd_txt(unsigned int uvy_thd_txt);
int iSetVPSS_DBD_LUTWGT0det_lut_wgt0(unsigned int udet_lut_wgt0);
int iSetVPSS_DBD_LUTWGT0det_lut_wgt1(unsigned int udet_lut_wgt1);
int iSetVPSS_DBD_LUTWGT0det_lut_wgt2(unsigned int udet_lut_wgt2);
int iSetVPSS_DBD_LUTWGT0det_lut_wgt3(unsigned int udet_lut_wgt3);
int iSetVPSS_DBD_LUTWGT0det_lut_wgt4(unsigned int udet_lut_wgt4);
int iSetVPSS_DBD_LUTWGT0det_lut_wgt5(unsigned int udet_lut_wgt5);
int iSetVPSS_DBD_LUTWGT0det_lut_wgt6(unsigned int udet_lut_wgt6);
int iSetVPSS_DBD_LUTWGT0det_lut_wgt7(unsigned int udet_lut_wgt7);
int iSetVPSS_DBD_LUTWGT1det_lut_wgt8(unsigned int udet_lut_wgt8);
int iSetVPSS_DBD_LUTWGT1det_lut_wgt9(unsigned int udet_lut_wgt9);
int iSetVPSS_DBD_LUTWGT1det_lut_wgt10(unsigned int udet_lut_wgt10);
int iSetVPSS_DBD_LUTWGT1det_lut_wgt11(unsigned int udet_lut_wgt11);
int iSetVPSS_DBD_LUTWGT1det_lut_wgt12(unsigned int udet_lut_wgt12);
int iSetVPSS_DBD_LUTWGT1det_lut_wgt13(unsigned int udet_lut_wgt13);
int iSetVPSS_DBD_LUTWGT1det_lut_wgt14(unsigned int udet_lut_wgt14);
int iSetVPSS_DBD_LUTWGT1det_lut_wgt15(unsigned int udet_lut_wgt15);
int iSetVPSS_DBD_RTNBDTXThy_rtn_bd_txt(unsigned int uhy_rtn_bd_txt);
int iSetVPSS_DBD_RTNBDTXThc_rtn_bd_txt(unsigned int uhc_rtn_bd_txt);
int iSetVPSS_DBD_RTNBDTXTvy_rtn_bd_txt(unsigned int uvy_rtn_bd_txt);
int iSetVPSS_DBD_TSTBLKNUMhy_tst_blk_num(unsigned int uhy_tst_blk_num);
int iSetVPSS_DBD_TSTBLKNUMhc_tst_blk_num(unsigned int uhc_tst_blk_num);
int iSetVPSS_DBD_TSTBLKNUMvy_tst_blk_num(unsigned int uvy_tst_blk_num);
int iSetVPSS_DBD_HYRDX8BINLUT0hy_rdx8bin_lut0(unsigned int uhy_rdx8bin_lut0);
int iSetVPSS_DBD_HYRDX8BINLUT0hy_rdx8bin_lut1(unsigned int uhy_rdx8bin_lut1);
int iSetVPSS_DBD_HYRDX8BINLUT1hy_rdx8bin_lut2(unsigned int uhy_rdx8bin_lut2);
int iSetVPSS_DBD_HYRDX8BINLUT1hy_rdx8bin_lut3(unsigned int uhy_rdx8bin_lut3);
int iSetVPSS_DBD_HYRDX8BINLUT2hy_rdx8bin_lut4(unsigned int uhy_rdx8bin_lut4);
int iSetVPSS_DBD_HYRDX8BINLUT2hy_rdx8bin_lut5(unsigned int uhy_rdx8bin_lut5);
int iSetVPSS_DBD_HYRDX8BINLUT3hy_rdx8bin_lut6(unsigned int uhy_rdx8bin_lut6);
int iSetVPSS_DBD_HCRDX8BINLUT0hc_rdx8bin_lut0(unsigned int uhc_rdx8bin_lut0);
int iSetVPSS_DBD_HCRDX8BINLUT0hc_rdx8bin_lut1(unsigned int uhc_rdx8bin_lut1);
int iSetVPSS_DBD_HCRDX8BINLUT1hc_rdx8bin_lut2(unsigned int uhc_rdx8bin_lut2);
int iSetVPSS_DBD_HCRDX8BINLUT1hc_rdx8bin_lut3(unsigned int uhc_rdx8bin_lut3);
int iSetVPSS_DBD_HCRDX8BINLUT2hc_rdx8bin_lut4(unsigned int uhc_rdx8bin_lut4);
int iSetVPSS_DBD_HCRDX8BINLUT2hc_rdx8bin_lut5(unsigned int uhc_rdx8bin_lut5);
int iSetVPSS_DBD_HCRDX8BINLUT3hc_rdx8bin_lut6(unsigned int uhc_rdx8bin_lut6);
int iSetVPSS_DBD_VYRDX8BINLUT0vy_rdx8bin_lut0(unsigned int uvy_rdx8bin_lut0);
int iSetVPSS_DBD_VYRDX8BINLUT0vy_rdx8bin_lut1(unsigned int uvy_rdx8bin_lut1);
int iSetVPSS_DBD_VYRDX8BINLUT1vy_rdx8bin_lut2(unsigned int uvy_rdx8bin_lut2);
int iSetVPSS_DBD_VYRDX8BINLUT1vy_rdx8bin_lut3(unsigned int uvy_rdx8bin_lut3);
int iSetVPSS_DBD_VYRDX8BINLUT2vy_rdx8bin_lut4(unsigned int uvy_rdx8bin_lut4);
int iSetVPSS_DBD_VYRDX8BINLUT2vy_rdx8bin_lut5(unsigned int uvy_rdx8bin_lut5);
int iSetVPSS_DBD_VYRDX8BINLUT3vy_rdx8bin_lut6(unsigned int uvy_rdx8bin_lut6);
int iSetVPSS_DBD_BLKSIZEmin_blk_size(unsigned int umin_blk_size);
int iSetVPSS_DBD_BLKSIZEhy_max_blk_size(unsigned int uhy_max_blk_size);
int iSetVPSS_DBD_BLKSIZEhc_max_blk_size(unsigned int uhc_max_blk_size);
int iSetVPSS_DBD_BLKSIZEvy_max_blk_size(unsigned int uvy_max_blk_size);
int iSetVPSS_DB_BORD_FLAGvpss_db_bord_flag(unsigned int* upvpss_db_bord_flag);


#endif /* __C_UNION_DEFINE_VPSS_H__ */
