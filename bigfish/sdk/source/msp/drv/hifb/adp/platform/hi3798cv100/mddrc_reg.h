//******************************************************************************
//  Copyright (C), 2008-2014, Hisilicon Technologies Co., Ltd.
//
//******************************************************************************
// File name     : mddrc_reg.h
// Version       : 1.0
// Author        : xxx
// Created       : 2013-12-12
// Last Modified : 
// Description   :  The register definition file for the module mddrc
// Function List : 
// History       : 
// 1 Date        : 
// Author        : xxx
// Modification  : Create file
//******************************************************************************

#ifndef __MDDRC_REG__
#define __MDDRC_REG__

/********defeine MDDRC register***********/
#define MDDRC_BASE_ADDR 0xF8A35000
#define OPTM_MDDRC_OFFSET 0x8
#define OPTM_MDDRC_MAX_ZONE 32

typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    mem_mode              : 1   ; // [0] 
        unsigned int    mem_comb              : 2   ; // [2..1] 
        unsigned int    Reserved              : 29  ; // [31..3] 
    } bits;

    // Define an unsigned member
    unsigned int    u32;
}U_DDR_MODE;

typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    apg_gt_en              : 1   ; // [0] 
        unsigned int    muxcmd_gt_en           : 1   ; // [1] 
        unsigned int    detaddr_gt_en          : 1   ; // [2] 
        unsigned int    Reserved              : 29   ; // [31..3] 
    } bits;

    // Define an unsigned member
    unsigned int    u32;
}U_CLK_CFG;

typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    ddr_retention_ctrl    : 1   ; // [0] 
        unsigned int    Reserved              : 31  ; // [31..1] 
    } bits;

    // Define an unsigned member
    unsigned int    u32;
}U_DDR_RETENTION_CTRL;


// Define the union U_AWADDR_SRVLNC_START
typedef union
{
    // Define the struct bits 
    struct
    {
        unsigned int awaddr_srvlnc_start                 : 32  ; // [31..0] 
    } bits;
 
    // Define an unsigned member
        unsigned int    u32;
 
} U_AWADDR_SRVLNC_START;

// Define the union U_AWADDR_SRVLNC_END
typedef union
{
    // Define the struct bits 
    struct
    {
        unsigned int awaddr_srvlnc_end                 : 32  ; // [31..0] 
    } bits;
 
    // Define an unsigned member
        unsigned int    u32;
 
} U_AWADDR_SRVLNC_END;


typedef struct
{
    U_DDR_MODE ddr_mode;
    U_CLK_CFG  clk_cfg;
	U_DDR_RETENTION_CTRL ddr_retention_ctrl;
    unsigned int reserved_1[61];
    U_AWADDR_SRVLNC_START awaddr_srvlnc_start;   
    U_AWADDR_SRVLNC_END awaddr_srvlnc_end;
    unsigned int reserved_2[62];
    unsigned int awaddr_srvlnc_status;
}OPTM_MDDRC_REGS_S;

#endif//__MDDRC_REG__