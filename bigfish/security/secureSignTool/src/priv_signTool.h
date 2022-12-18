#ifndef _PRIV_SIGNTOOL_H
#define _PRIV_SIGNTOOL_H

//#include <windows.h>
#include "type.h"

extern unsigned long g_ulHeadAreaLength;

typedef enum tagChipsetType
{
    Hi3716CV100,
    Hi3716CV200,
    Hi3716MV200,
    Hi3716MV300,
    Hi3110EV300,
    Hi3719CV100,
    Hi3719MV100,
}HI_CHIPSET_TYPE_EN;


//#define CFGFILE _T("\\config.ini")

//extern CString g_strCurDir;

struct ConfigInfor {
    CString strManuID;
    CString strManuName;
    CString strCntName;
    CString strCntEmal;
    CString strCntKeyID;
    CString strChipType;
};

/************************************************************************/
/* memory map on board                                                  */
/************************************************************************/
#define SECTION_P_ROM       0              /*onchip rom and ram*/
#define SECTION_P_CA        0x10000000     /*ca reg*/
#define SECTION_P_SYS       0x10100000     /*sys ctrl reg and otp reg*/
#define SECTION_P_PERI      0x10200000     /*peri ctrl reg*/
#define SECTION_P_CSSYS     0x10300000     /*cssys reg*/
#define SECTION_P_DNR       0x10400000     /*dnr reg*/
#define SECTION_P_L2        0x16800000     /*l2 cache reg*/
#define SECTION_P_NAND      0x24000000     /*nand flash*/
#define SECTION_P_SPI       0x26000000     /*spi flash*/
#define SECTION_P_NOR       0x34000000     /*nor flash*/
#define SECTION_P_NANDC     0x60000000     /*nandc and cipher reg*/
#define SECTION_P_MMC       0x60100000     /*mmc reg*/
#define SECTION_P_DDR_1     0x80000000     /*DDR*/
#define SECTION_P_DDR_2     0x80100000     /*DDR*/
#define SECTION_P_DDR_3     0x80200000     /*DDR*/
#define SECTION_P_DDR_4     0x80300000     /*DDR*/
#define SECTION_P_DDR_5     0x80400000     /*DDR*/
#define SECTION_P_DDR_6     0x80500000     /*DDR*/
#define SECTION_P_DDR_7     0x80600000     /*DDR*/

#define SECTION_V_ROM       0              /*onchip rom and ram*/
#define SECTION_V_CA        0x100000       /*ca reg*/
#define SECTION_V_SYS       0x200000       /*sys ctrl reg and otp reg*/
#define SECTION_V_PERI      0x300000       /*peri ctrl reg*/
#define SECTION_V_CSSYS     0x400000       /*cssys reg*/
#define SECTION_V_DNR       0x500000       /*dnr reg*/
#define SECTION_V_L2        0x600000       /*l2 cache reg*/
#define SECTION_V_NAND      0x700000       /*nand flash*/
#define SECTION_V_SPI       0x800000       /*spi flash*/
#define SECTION_V_NOR       0x900000       /*nor flash*/
#define SECTION_V_NANDC     0xA00000       /*nandc and cipher reg*/
#define SECTION_V_MMC       0xB00000       /*mmc reg*/
#define SECTION_V_DDR_1     0xC00000       /*DDR*/
#define SECTION_V_DDR_2     0xD00000       /*DDR*/
#define SECTION_V_DDR_3     0xE00000       /*DDR*/
#define SECTION_V_DDR_4     0xF00000       /*DDR*/
#define SECTION_V_DDR_5    0x1000000       /*DDR*/
#define SECTION_V_DDR_6    0x1100000       /*DDR*/
#define SECTION_V_DDR_7    0x1200000       /*DDR*/

/************************************************************************/
/* param area struct on flash, little endian                            */
/************************************************************************/
#define KEY_AREA_OFFSET        0x0
#define PARA_AREA_OFFSET    0x304
#define BOOT_AREA_OFFSET_MV200        0x800

#define BOOT_AREA_OFFSET_MV300  0x1800

#define RSA_2048_LEN         0x100
#define KEY_AREA_LEN        PARA_AREA_OFFSET
#define PARA_AREA_LEN    (g_ulHeadAreaLength - PARA_AREA_OFFSET)

#define RSA_SIGNATURE_LEN   0x100

#define CFG_TYPE_INIT       1
#define CFG_TYPE_WAKEUP     2
#define CFG_TYPE_NULL       0xff

#define CFG_CMD_END         0xf
#define CFG_CMD_REG         0
#define CFG_CMD_DELAY       1
#define CFG_CMD_WAIT        2
#define CFG_CMD_REG_MSK     3
#define CFG_CMD_WAIT_MSK    4

#define CFG_BIT_8           0x0
#define CFG_BIT_16          0x1
#define CFG_BIT_32          0x2

#define BOOT_AREA_NUM       2

typedef struct {
    UINT32   check_area_off[BOOT_AREA_NUM];
    UINT32   check_area_len[BOOT_AREA_NUM];
    UINT32   boot_area_len;
    UINT32   clear_flag    :1;    /*0:encrypted, 1: clear*/
    UINT32   alg           :1;    /*0:AES, 1: TDES*/
    UINT32   mode          :1;    /*0:CBC, 1: ECB*/
    UINT32   reserved      :29;
}boot_area_info;

typedef union {
    struct
    {
        UINT32     ecc_type    :3;
        UINT32     block_size  :2;
        UINT32     page_size   :2;
        UINT32     bus_with    :1;
        UINT32     addr_num    :1;
        UINT32     disable     :1;
        UINT32     reserved    :22;
    }bits;
    UINT32 all;
}nand_param;

typedef struct {
    UCHAR  type;
    UCHAR  reserved;
    UCHAR  len[2];
    UCHAR  reg_base[4];
}cfg_param_head;


#define RSV_PARAM_LEN (32 - sizeof(boot_area_info) - sizeof (nand_param))
#define CFG_PARAM_LEN (PARA_AREA_LEN - RSA_2048_LEN - 32)

#define MAX_CFG_PARAM_LEN (BOOT_AREA_OFFSET_MV300 - PARA_AREA_OFFSET - RSA_2048_LEN - 32)
/*parameter area*/
typedef struct {
    boot_area_info boot_area;  //PARA_AREA_OFFSET
    nand_param nand;
    UCHAR    reserved[RSV_PARAM_LEN];
    UCHAR    cfg_param[MAX_CFG_PARAM_LEN];
}param_area;

#define SWPK_LEN 0x20

#define UNCHECKED_AREA_LEN  0x800

#endif
