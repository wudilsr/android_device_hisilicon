/******************************************************************************
Copyright (C), 2009-2019, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_struct.h
Version       : Initial Draft
Author        : Hisilicon
Created       : 2009/12/16
Last Modified :
Description   : Defines the common data type of the system.
                CNcomment: 系统共用的数据类型定义
Function List :
History       :
******************************************************************************/
/**
 * \file
 * \brief Describes the information about basic data types. CNcomment: 提供基本数据类型的相关信息
 */
#ifndef __HI_STRUCT_H__
#define __HI_STRUCT_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */


/*************************** Structure Definition ****************************/
/** \addtogroup      Common */
/** @{ */  /** <!-- 【Common data structure. CNcomment: 通用数据结构】 */

/**System configuration structure*/
/**CNcomment: 系统配置结构体*/
typedef struct hiSYS_CONF_S
{
    HI_U32 u32Reverse;  /**<Not used, reserved for extension*/ /**<CNcomment: 暂时没有使用，留待扩展*/

}HI_SYS_CONF_S;

/**Define the chip type.*/
/**CNcomment: 定义芯片类型枚举 */
typedef enum hiCHIP_TYPE_E
{
    HI_CHIP_TYPE_HI3716M,  /**<HI3716M */
    HI_CHIP_TYPE_HI3716H,  /**<HI3716H */
    HI_CHIP_TYPE_HI3716C,  /**<HI3716C */
    HI_CHIP_TYPE_HI3716L,  /**<HI3716L */

    HI_CHIP_TYPE_HI3720,  /**<HI3720 */

    HI_CHIP_TYPE_BUTT
}HI_CHIP_TYPE_E;

/**Define the chip version.*/
/**CNcomment: 定义芯片版本枚举 */
typedef enum hiCHIP_VERSION_E
{
    HI_CHIP_VERSION_V100 = 0x100,  /**< MPW, for chipset, means B10 */
    HI_CHIP_VERSION_V101 = 0x101,  /**< PILOT */
    HI_CHIP_VERSION_V200 = 0x200,  /**< V200 */
    HI_CHIP_VERSION_V300 = 0x300,  /**< V300 */
    HI_CHIP_VERSION_BUTT
}HI_CHIP_VERSION_E;

/**System version, that is, the version of the software developer's kit (SDK)*/
/**CNcomment:  系统版本号，即整个SDK的版本号*/
typedef struct hiSYS_VERSION_S
{
    HI_CHIP_TYPE_E  enChipTypeSoft;      /**<Chip type corresponding to the SDK*/ /**<CNcomment:  SDK软件对应的芯片类型 */
    HI_CHIP_TYPE_E  enChipTypeHardWare;  /**<Chip type that is detected when the SDK is running*/ /**<CNcomment:  SDK运行时检测到的芯片类型 */
    HI_CHIP_VERSION_E enChipVersion;     /**<Chip version that is detected when the SDK is running*/ /**<CNcomment: SDK运行时检测到芯片版本号 */
    HI_CHAR         aVersion[80];        /**<Version string of the SDK*/ /**<CNcomment:  SDK软件版本号字符串 */
    HI_CHAR         BootVersion[80];     /**<Version string of the Boot*/ /**<CNcomment:  Boot版本号字符串 */
}HI_SYS_VERSION_S;


/*Define the chip attributes*/
typedef struct hiSYS_CHIP_ATTR_S
{
    HI_BOOL bDolbySupport;              /**<Whether this chip support dolby or not*//**<CNcomment:芯片是否支持杜比*/
    HI_BOOL bMacrovisionSupport;     /**<Whether this chip support macrovision or not*//**<CNcomment:芯片是否支持macrovision*/
    HI_BOOL bAdvcaSupport;            /**<Whether this chip support advca or not*//**<CNcomment:芯片是否支持高安*/
}HI_SYS_CHIP_ATTR_S;

/**Maximum bytes of a buffer name*/
/**CNcomment:  buffer命名的最大字节数 */
#define MAX_BUFFER_NAME_SIZE 16

/**Structure of an MMZ buffer*/
/**CNcomment:  MMZ buffer信息结构 */
typedef struct hiMMZ_BUF_S
{
    HI_CHAR bufname[MAX_BUFFER_NAME_SIZE];  /**<Strings of an MMZ buffer name*/ /**<CNcomment:  MMZ buffer名字字符串 */
    HI_U32  phyaddr;                /**<Physical address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer物理地址 */
    HI_U8  *kernel_viraddr;         /**<Kernel-state virtual address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer内核态虚拟地址 */
    HI_U8  *user_viraddr;           /**<User-state virtual address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer用户态虚拟地址 */
    HI_U32  bufsize;                /**<Size of an MMZ buffer*/ /**<CNcomment:  MMZ buffer大小 */
    HI_U32  overflow_threshold;     /**<Overflow threshold of an MMZ buffer, in percentage. For example, the value 100 indicates 100%.*/ /**<CNcomment:  MMZ buffer上溢水线，按百分比设置，例如: 100 indicates 100%.*/
    HI_U32  underflow_threshold;    /**<Underflow threshold of an MMZ buffer, in percentage. For example, the value 0 indicates 0%.*/ /**<CNcomment:  MMZ buffer下溢水线，按百分比设置，例如: 0 indicates 0%.*/
}HI_MMZ_BUF_S;


typedef struct hiRECT_S
{
    HI_S32 s32X;
    HI_S32 s32Y;
    HI_S32 s32Width;
    HI_S32 s32Height;
} HI_RECT_S;

typedef enum hiLAYER_ZORDER_E
{
    HI_LAYER_ZORDER_MOVETOP = 0,  /**<Move to the top*/ /**<CNcomment:  移到最顶部 */
    HI_LAYER_ZORDER_MOVEUP,       /**<Move up*/ /**<CNcomment:  向上移到 */
    HI_LAYER_ZORDER_MOVEBOTTOM,   /**<Move to the bottom*/ /**<CNcomment:  移到最底部 */
    HI_LAYER_ZORDER_MOVEDOWN,     /**<Move down*/ /**<CNcomment:  向下移到 */
    HI_LAYER_ZORDER_BUTT
} HI_LAYER_ZORDER_E;

/**The maximum value is 128 (0x80).*/
/**CNcomment:  最大不可超过128(0x80) */
typedef enum hiMOD_ID_E
{
    HI_ID_INVALID   = 0,

    /* common */
    HI_ID_SYS    = 0x1,
    HI_ID_LOG    = 0x2,
    HI_ID_PROC   = 0x3,
    HI_ID_EVENT  = 0x4,
    HI_ID_MEM    = 0x5,
    HI_ID_STAT   = 0x6,

    /* module */
    HI_ID_DISP   = 0x10,
    HI_ID_VO     = 0x11,
    HI_ID_VDEC   = 0x12,
    HI_ID_AO     = 0x13,
    HI_ID_ADEC   = 0x14,
    HI_ID_DEMUX  = 0x15,
    HI_ID_TDE    = 0x16,
    HI_ID_JPGDEC = 0x17,
    HI_ID_JPGENC = 0x18,
    HI_ID_FB     = 0x19,
    HI_ID_VI     = 0x1A,
    HI_ID_AI     = 0x1B,
    HI_ID_AENC   = 0x1C,
    HI_ID_VENC   = 0x1D,

    HI_ID_SIO_AI = 0x1E,
    HI_ID_SIO_AO = 0x1F,
    HI_ID_SIO    = 0x20,
    HI_ID_HDMI   = 0x21,
    HI_ID_MCE    = 0x22,

    /* app */
    HI_ID_PVR    = 0x30,
    HI_ID_AVPLAY = 0x31,
    HI_ID_SYNC   = 0x32,
    HI_ID_USER   = 0x33,

     /* ecs */
    HI_ID_FLASH  = 0x40,
    HI_ID_IR     = 0x41,
    HI_ID_RTC    = 0x42,
    HI_ID_WDG    = 0x43,
    HI_ID_I2C    = 0x44,
    HI_ID_SCI    = 0x45,
    HI_ID_ETH    = 0x46,
    HI_ID_GPIO   = 0x47,
    HI_ID_DMAC   = 0x48,
    HI_ID_PMOC   = 0x49,
    HI_ID_TUNER  = 0x4A,
    HI_ID_KEYLED = 0x4B,
    HI_ID_E2PROM = 0x4C,
    HI_ID_CIPHER = 0x4D,
    HI_ID_CA 	 = 0x4e,
    HI_ID_C51 	 = 0x4f,

    /*voip*/
    HI_ID_VOIP_HME = 0x50,
    HI_ID_NDPT     = 0x51,
    HI_ID_AUDADP   = 0x52,

    /*vp*/
    HI_ID_VP     = 0x53,

    /*SetHDCP*/
    HI_ID_HDCP   = 0x54,

    /*ci*/
    HI_ID_CI     = 0x55,

    /* subtitle */
    HI_ID_SUBT   = 0x56,

    /* adv7401 */
    HI_ID_ADV7401= 0x57,

    /*cimax+*/
    HI_ID_CIMAXPLUS = 0x58,

    HI_ID_BUTT   = 0x7f
} HI_MOD_ID_E;


#define UMAP_NAME    "hi_"

#define HI_MOD_SYS                  "sys"
#define UMAP_DEVNAME_SYS            UMAP_NAME HI_MOD_SYS
#define UMAP_DEV_NUM_SYS            1
#define UMAP_MIN_MINOR_SYS          1
#define UMAP_MAX_MINOR_SYS          (UMAP_MIN_MINOR_SYS + UMAP_DEV_NUM_SYS -1)


#define HI_MOD_LOG                  "log"
#define UMAP_DEVNAME_LOG            UMAP_NAME HI_MOD_LOG
#define UMAP_DEV_NUM_LOG            1
#define UMAP_MIN_MINOR_LOG          (UMAP_MAX_MINOR_SYS + 1)
#define UMAP_MAX_MINOR_LOG          (UMAP_MIN_MINOR_LOG + UMAP_DEV_NUM_LOG -1)


#define HI_MOD_EVENT                "event"
#define UMAP_DEVNAME_EVENT          UMAP_NAME HI_MOD_EVENT
#define UMAP_DEV_NUM_EVENT          1
#define UMAP_MIN_MINOR_EVENT        (UMAP_MAX_MINOR_LOG + 1)
#define UMAP_MAX_MINOR_EVENT        (UMAP_MIN_MINOR_EVENT + UMAP_DEV_NUM_EVENT -1)

#define HI_MOD_STAT                 "stat"
#define UMAP_DEVNAME_STAT           UMAP_NAME HI_MOD_STAT
#define UMAP_DEV_NUM_STAT           1
#define UMAP_MIN_MINOR_STAT         (UMAP_MAX_MINOR_EVENT + 1)
#define UMAP_MAX_MINOR_STAT         (UMAP_MIN_MINOR_STAT + UMAP_DEV_NUM_STAT -1)



#define HI_MOD_MEM      "mem"

#define HI_MOD_PROC     "proc"

/*End of CMPI */

/*Other modules*/
/**CNcomment:  其它模块 */
#define HI_MOD_CIPHER               "cipher"
#define UMAP_DEVNAME_CIPHER         UMAP_NAME HI_MOD_CIPHER
#define UMAP_DEV_NUM_CIPHER         1
#define UMAP_MIN_MINOR_CIPHER       (UMAP_MAX_MINOR_STAT + 1)
#define UMAP_MAX_MINOR_CIPHER       (UMAP_MIN_MINOR_CIPHER + UMAP_DEV_NUM_CIPHER -1)

#define HI_MOD_DISP                 "disp"
#define UMAP_DEVNAME_DISP           UMAP_NAME HI_MOD_DISP
#define UMAP_DEV_NUM_DISP           1
#define UMAP_MIN_MINOR_DISP         (UMAP_MAX_MINOR_CIPHER + 1)
#define UMAP_MAX_MINOR_DISP         (UMAP_MIN_MINOR_DISP + UMAP_DEV_NUM_DISP -1)

#define HI_MOD_VO                   "vo"
#define UMAP_DEVNAME_VO             UMAP_NAME HI_MOD_VO
#define UMAP_DEV_NUM_VO             1
#define UMAP_MIN_MINOR_VO           (UMAP_MIN_MINOR_DISP + 1)
#define UMAP_MAX_MINOR_VO           (UMAP_MIN_MINOR_VO + UMAP_DEV_NUM_VO -1)

#define HI_MOD_VDEC                 "vdec"
#define UMAP_DEVNAME_VDEC           UMAP_NAME HI_MOD_VDEC
#define UMAP_DEV_NUM_VDEC           2
#define UMAP_MIN_MINOR_VDEC         (UMAP_MAX_MINOR_VO + 1)
#define UMAP_MAX_MINOR_VDEC         (UMAP_MIN_MINOR_VDEC + UMAP_DEV_NUM_VDEC -1)

#define HI_MOD_AO                   "ao"
#define UMAP_DEVNAME_AO             UMAP_NAME HI_MOD_AO
#define UMAP_DEV_NUM_AO             2
#define UMAP_MIN_MINOR_AO           (UMAP_MAX_MINOR_VDEC + 1)
#define UMAP_MAX_MINOR_AO           (UMAP_MIN_MINOR_AO + UMAP_DEV_NUM_AO -1)

#define HI_MOD_AENC                 "aenc"
#define UMAP_DEVNAME_AENC           UMAP_NAME HI_MOD_AENC
#define UMAP_DEV_NUM_AENC           2
#define UMAP_MIN_MINOR_AENC         (UMAP_MAX_MINOR_AO + 1)
#define UMAP_MAX_MINOR_AENC         (UMAP_MIN_MINOR_AENC + UMAP_DEV_NUM_AENC -1)

#define HI_MOD_ADEC                 "adec"
#define UMAP_DEVNAME_ADEC           UMAP_NAME HI_MOD_ADEC
#define UMAP_DEV_NUM_ADEC           2
#define UMAP_MIN_MINOR_ADEC         (UMAP_MAX_MINOR_AENC + 1)
#define UMAP_MAX_MINOR_ADEC         (UMAP_MIN_MINOR_ADEC + UMAP_DEV_NUM_ADEC -1)

#define HI_MOD_DEMUX                "demux"
#define UMAP_DEVNAME_DEMUX          UMAP_NAME HI_MOD_DEMUX
#define UMAP_DEV_NUM_DEMUX          1
#define UMAP_MIN_MINOR_DEMUX        (UMAP_MAX_MINOR_ADEC + 1)
#define UMAP_MAX_MINOR_DEMUX        (UMAP_MIN_MINOR_DEMUX + UMAP_DEV_NUM_DEMUX -1)

#define HI_MOD_JPGD                 "jpgd"
#define UMAP_DEVNAME_JPGD           UMAP_NAME HI_MOD_JPGD
#define UMAP_DEV_NUM_JPGD           1
#define UMAP_MIN_MINOR_JPGD         (UMAP_MAX_MINOR_DEMUX + 1)
#define UMAP_MAX_MINOR_JPGD         (UMAP_MIN_MINOR_JPGD + UMAP_DEV_NUM_JPGD -1)

#define HI_MOD_SYNC                 "sync"
#define UMAP_DEVNAME_SYNC           UMAP_NAME HI_MOD_SYNC
#define UMAP_DEV_NUM_SYNC           1
#define UMAP_MIN_MINOR_SYNC         (UMAP_MAX_MINOR_JPGD + 1)
#define UMAP_MAX_MINOR_SYNC         (UMAP_MIN_MINOR_SYNC + UMAP_DEV_NUM_SYNC -1)

#define HI_MOD_AVPLAY               "avplay"
#define UMAP_DEVNAME_AVPLAY         UMAP_NAME HI_MOD_AVPLAY
#define UMAP_DEV_NUM_AVPLAY         1
#define UMAP_MIN_MINOR_AVPLAY       (UMAP_MAX_MINOR_SYNC + 1)
#define UMAP_MAX_MINOR_AVPLAY       (UMAP_MIN_MINOR_AVPLAY + UMAP_DEV_NUM_AVPLAY -1)

#define HI_MOD_PVR               "pvr"
#define UMAP_DEVNAME_PVR         UMAP_NAME HI_MOD_PVR
#define UMAP_DEV_NUM_PVR         1
#define UMAP_MIN_MINOR_PVR       (UMAP_MAX_MINOR_AVPLAY + 1)
#define UMAP_MAX_MINOR_PVR       (UMAP_MIN_MINOR_PVR + UMAP_DEV_NUM_PVR -1)

#define HI_MOD_HDMI                  "hdmi"
#define UMAP_DEVNAME_HDMI            UMAP_NAME HI_MOD_HDMI
#define UMAP_DEV_NUM_HDMI            1
#define UMAP_MIN_MINOR_HDMI          (UMAP_MAX_MINOR_PVR + 1)
#define UMAP_MAX_MINOR_HDMI          (UMAP_MIN_MINOR_HDMI + UMAP_DEV_NUM_HDMI -1)


#define HI_MOD_VI                   "vi"
#define UMAP_DEVNAME_VI             UMAP_NAME HI_MOD_VI
#define UMAP_DEV_NUM_VI             1
#define UMAP_MIN_MINOR_VI           (UMAP_MAX_MINOR_HDMI + 1)
#define UMAP_MAX_MINOR_VI           (UMAP_MIN_MINOR_VI + UMAP_DEV_NUM_VI -1)

#define HI_MOD_VENC             "venc"
#define UMAP_DEVNAME_VENC       UMAP_NAME HI_MOD_VENC
#define UMAP_DEV_NUM_VENC       2
#define UMAP_MIN_MINOR_VENC     (UMAP_MAX_MINOR_VI+1)
#define UMAP_MAX_MINOR_VENC     (UMAP_MIN_MINOR_VENC+UMAP_DEV_NUM_VENC-1)

#define HI_MOD_SIO_AI             "sio_ai"
#define UMAP_DEVNAME_SIO_AI       UMAP_NAME HI_MOD_SIO_AI
#define UMAP_DEV_NUM_SIO_AI       2
#define UMAP_MIN_MINOR_SIO_AI     (UMAP_MAX_MINOR_VENC+1)
#define UMAP_MAX_MINOR_SIO_AI     (UMAP_MIN_MINOR_SIO_AI+UMAP_DEV_NUM_SIO_AI-1)

#define HI_MOD_SIO_AO             "sio_ao"
#define UMAP_DEVNAME_SIO_AO       UMAP_NAME HI_MOD_SIO_AO
#define UMAP_DEV_NUM_SIO_AO       2
#define UMAP_MIN_MINOR_SIO_AO     (UMAP_MAX_MINOR_SIO_AI+1)
#define UMAP_MAX_MINOR_SIO_AO     (UMAP_MIN_MINOR_SIO_AO+UMAP_DEV_NUM_SIO_AO-1)

#define HI_MOD_DMA               "dma"
#define UMAP_DEVNAME_DMA       UMAP_NAME HI_MOD_DMA
#define UMAP_DEV_NUM_DMA       1
#define UMAP_MIN_MINOR_DMA     (UMAP_MAX_MINOR_SIO_AO+1)
#define UMAP_MAX_MINOR_DMA     (UMAP_MIN_MINOR_DMA+UMAP_DEV_NUM_DMA-1)

#define HI_MOD_AUDADP               "audadp"
#define UMAP_DEVNAME_AUDADP        UMAP_NAME HI_MOD_AUDADP
#define UMAP_DEV_NUM_AUDADP        1
#define UMAP_MIN_MINOR_AUDADP      (UMAP_MAX_MINOR_DMA+1)
#define UMAP_MAX_MINOR_AUDADP      (UMAP_MIN_MINOR_AUDADP +UMAP_DEV_NUM_AUDADP -1)

#define HI_MOD_HME               "hme"
#define UMAP_DEVNAME_HME       UMAP_NAME HI_MOD_HME
#define UMAP_DEV_NUM_HME       1
#define UMAP_MIN_MINOR_HME     (UMAP_MAX_MINOR_AUDADP +1)
#define UMAP_MAX_MINOR_HME     (UMAP_MIN_MINOR_HME+UMAP_DEV_NUM_HME-1)

#define HI_MOD_NDPT               "ndpt"
#define UMAP_DEVNAME_NDPT       UMAP_NAME HI_MOD_NDPT
#define UMAP_DEV_NUM_NDPT       1
#define UMAP_MIN_MINOR_NDPT     (UMAP_MAX_MINOR_HME +1)
#define UMAP_MAX_MINOR_NDPT     (UMAP_MIN_MINOR_NDPT+UMAP_DEV_NUM_NDPT-1)

#define HI_MOD_VP                   "vp"
#define UMAP_DEVNAME_VP             UMAP_NAME HI_MOD_VP
#define UMAP_DEV_NUM_VP             1
#define UMAP_MIN_MINOR_VP           (UMAP_MAX_MINOR_NDPT + 1)
#define UMAP_MAX_MINOR_VP           (UMAP_MIN_MINOR_VP + UMAP_DEV_NUM_VP -1)

/*                 ECS                */
#define HI_MOD_IR                   "ir"
#define UMAP_DEVNAME_IR             UMAP_NAME HI_MOD_IR
#define UMAP_DEV_NUM_IR             1
#define UMAP_MIN_MINOR_IR           (UMAP_MAX_MINOR_VP + 1)
#define UMAP_MAX_MINOR_IR           (UMAP_MIN_MINOR_IR + UMAP_DEV_NUM_IR -1)

#define HI_MOD_KEYLED               "keyled"
#define UMAP_DEVNAME_KEYLED         UMAP_NAME HI_MOD_KEYLED
#define UMAP_DEV_NUM_KEYLED         1
#define UMAP_MIN_MINOR_KEYLED       (UMAP_MAX_MINOR_IR + 1)
#define UMAP_MAX_MINOR_KEYLED       (UMAP_MIN_MINOR_KEYLED + UMAP_DEV_NUM_KEYLED -1)

#define HI_MOD_I2C                  "i2c"
#define UMAP_DEVNAME_I2C            UMAP_NAME HI_MOD_I2C
#define UMAP_DEV_NUM_I2C            1
#define UMAP_MIN_MINOR_I2C          (UMAP_MAX_MINOR_KEYLED + 1)
#define UMAP_MAX_MINOR_I2C          (UMAP_MIN_MINOR_I2C + UMAP_DEV_NUM_I2C -1)

#define HI_MOD_E2PROM               "e2prom"
#define UMAP_DEVNAME_E2PROM         UMAP_NAME HI_MOD_E2PROM
#define UMAP_DEV_NUM_E2PROM         1
#define UMAP_MIN_MINOR_E2PROM       (UMAP_MAX_MINOR_I2C + 1)
#define UMAP_MAX_MINOR_E2PROM       (UMAP_MIN_MINOR_E2PROM + UMAP_DEV_NUM_E2PROM -1)

#define HI_MOD_TUNER                "tuner"
#define UMAP_DEVNAME_TUNER          UMAP_NAME HI_MOD_TUNER
#define UMAP_DEV_NUM_TUNER          1
#define UMAP_MIN_MINOR_TUNER        (UMAP_MAX_MINOR_E2PROM + 1)
#define UMAP_MAX_MINOR_TUNER        (UMAP_MIN_MINOR_TUNER + UMAP_DEV_NUM_TUNER -1)

#define HI_MOD_SCI                  "sci"
#define UMAP_DEVNAME_SCI            UMAP_NAME HI_MOD_SCI
#define UMAP_DEV_NUM_SCI            1
#define UMAP_MIN_MINOR_SCI          (UMAP_MAX_MINOR_TUNER+ 1)
#define UMAP_MAX_MINOR_SCI          (UMAP_MIN_MINOR_SCI + UMAP_DEV_NUM_SCI -1)


#define HI_MOD_CA                   "ca"
#define UMAP_DEVNAME_CA             UMAP_NAME HI_MOD_CA
#define UMAP_DEV_NUM_CA             1
#define UMAP_MIN_MINOR_CA           (UMAP_MAX_MINOR_SCI+ 1)
#define UMAP_MAX_MINOR_CA           (UMAP_MIN_MINOR_CA + UMAP_DEV_NUM_CA -1)

#define HI_MOD_OTP                  "otp"
#define UMAP_DEVNAME_OTP            UMAP_NAME HI_MOD_OTP
#define UMAP_DEV_NUM_OTP            1
#define UMAP_MIN_MINOR_OTP          (UMAP_MAX_MINOR_CA + 1)
#define UMAP_MAX_MINOR_OTP          (UMAP_MIN_MINOR_OTP + UMAP_DEV_NUM_OTP -1)

#define HI_MOD_SVDEC                 "svdec"
#define UMAP_DEVNAME_SVDEC          UMAP_NAME HI_MOD_SVDEC
#define UMAP_DEV_NUM_SVDEC          1
#define UMAP_MIN_MINOR_SVDEC        (UMAP_MAX_MINOR_OTP + 1)
#define UMAP_MAX_MINOR_SVDEC        (UMAP_MIN_MINOR_SVDEC + UMAP_DEV_NUM_SVDEC -1)

#define HI_MOD_SETHDCP             "sethdcp"
#define UMAP_DEVNAME_SETHDCP       UMAP_NAME HI_MOD_SETHDCP
#define UMAP_DEV_NUM_SETHDCP       1
#define UMAP_MIN_MINOR_SETHDCP     (UMAP_MIN_MINOR_SVDEC+ 1)
#define UMAP_MAX_MINOR_SETHDCP     (UMAP_MIN_MINOR_SETHDCP + UMAP_DEV_NUM_SETHDCP -1)


#define HI_MOD_CI                   "ci"
#define UMAP_DEVNAME_CI             UMAP_NAME HI_MOD_CI
#define UMAP_DEV_NUM_CI             1
#define UMAP_MIN_MINOR_CI           (UMAP_MAX_MINOR_SETHDCP+ 1)
#define UMAP_MAX_MINOR_CI           (UMAP_MIN_MINOR_CI + UMAP_DEV_NUM_CI -1)

#define HI_MOD_SUBT                   "subt"
#define UMAP_DEVNAME_SUBT             UMAP_NAME HI_MOD_SUBT
#define UMAP_DEV_NUM_SUBT             1
#define UMAP_MIN_MINOR_SUBT           (UMAP_MAX_MINOR_CI+ 1)
#define UMAP_MAX_MINOR_SUBT           (UMAP_MIN_MINOR_SUBT + UMAP_DEV_NUM_SUBT - 1)


#define UMAP_DEV_NUM_TOTAL   	    UMAP_MAX_MINOR_SUBT
/** @} */  /** <!-- ==== Structure Definition End ==== */

#define IOC_TYPE_DEMUX          'I'
#define IOC_TYPE_MEM            'J'
#define IOC_TYPE_RELEASE        'K'
#define IOC_TYPE_EVENT          'L'
#define IOC_TYPE_SYS            'M'
#define IOC_TYPE_STAT           'N'
#define IOC_TYPE_MCC            'O'
#define IOC_TYPE_TDE            'P'

#define IOC_TYPE_CIPHER         'Q'
#define IOC_TYPE_AVPLAY         'R'

#define IOC_TYPE_VI             'S'
#define IOC_TYPE_VENC           'T'
#define IOC_TYPE_CA             'U'
#define IOC_TYPE_OTP            'V'

#define IOC_TYPE_VP             'W'


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __HI_STRUCT_H__ */
