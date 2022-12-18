/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : mddrc_reg.h
Version             : Initial Draft
Author              : 
Created             : 2015/05/13
Description         :
Function List       : 

                                          
History             :
Date                            Author                  Modification
2015/05/13                      y00181162               Created file        
******************************************************************************/

/*********************************add include here******************************/


#ifndef __MDDRC_REG__
#define __MDDRC_REG__

/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/

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
        unsigned int    Reserved               : 29  ; // [31..3] 
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
    U_DDR_MODE               ddr_mode;
    U_CLK_CFG                clk_cfg;
	U_DDR_RETENTION_CTRL     ddr_retention_ctrl;
    unsigned int             reserved_1[61];
    U_AWADDR_SRVLNC_START    awaddr_srvlnc_start;   
    U_AWADDR_SRVLNC_END      awaddr_srvlnc_end;
    unsigned int             reserved_2[62];
    unsigned int             awaddr_srvlnc_status;
}OPTM_MDDRC_REGS_S;


/********************** Global Variable declaration **************************/


/******************************* API forward declarations *******************/

/******************************* API realization *****************************/

#endif//__MDDRC_REG__