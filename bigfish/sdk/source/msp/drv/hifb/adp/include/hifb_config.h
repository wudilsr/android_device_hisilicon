/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : hifb_config.h
Version             : Initial Draft
Author              : 
Created             : 2014/09/09
Description         : ������Ϣ�ı仯������һ���ļ������֣������ı��ֲ���
Function List       : 
History             :
Date                       Author                   Modification
2014/09/09                 y00181162                Created file        
******************************************************************************/

#ifndef __HIFB_CONFIG_H__
#define __HIFB_CONFIG_H__


/*********************************add include here******************************/

#include "hi_type.h"

#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
 	#ifndef HI_BUILD_IN_BOOT
		#include "hi_math.h"
	#endif
#endif


/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/
/**
 ** ÿ���Ĵ�����ƫ�Ƶ�ַ
 **/
#define CONFIG_HIFB_CHN_OFFSET     	 0x400
#define CONFIG_HIFB_WBC_OFFSET     	 0x400

#if defined(CHIP_TYPE_hi3796cv100)   || defined(CHIP_TYPE_hi3798cv100)    \
 || defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
	#define CONFIG_HIFB_GFX_OFFSET     0x200
	#define CONFIG_HIFB_GP_OFFSET      0x800
#else
	#define CONFIG_HIFB_GFX_OFFSET     0x800             /** ͼ��   **/
	#define CONFIG_HIFB_GP_OFFSET      0x800 		        /** ͼ��GP **/
#endif


/**
 ** VDP�Ĵ�������ַ
 **/
#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
	#define CONFIG_VDP_REG_BASEADDR	            	  (0xff120000)
	#define CONFIG_HIFB_HD0_REG_BASEADDR               (0xff127000)
	/**
	 ** (CONFIG_HIFB_HD0_REG_BASEADDR + 2 * OPTM_GFX_OFFSET) �����LOGO HD2
	 **/
	#define CONFIG_HIFB_HD_LOGO_REG_BASEADDR           (0xff127400)
	/**
	 ** (CONFIG_HIFB_HD0_REG_BASEADDR + 4 * OPTM_GFX_OFFSET) �����LOGO SD0
	 **/
	#define CONFIG_HIFB_SD_LOGO_REG_BASEADDR            (0xff127800)
	/**
	 ** (CONFIG_HIFB_SD0_REG_BASEADDR + OPTM_GFX_OFFSET) ͬԴ��дʹ�ñ����SD0
	 **/
	#define CONFIG_HIFB_WBC_SLAYER_REG_BASEADDR        (0xff127800)
	/** WBC_GP0ͬԴ��д 0xff129400**/
	#define CONFIG_HIFB_WBC_GP0_REG_BASEADDR            (0xff129400)
#elif defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
	#define CONFIG_VDP_REG_BASEADDR	             	   (0xf8cc0000)
	#define CONFIG_HIFB_HD0_REG_BASEADDR                (0xf8cc7000)
	/**
	 ** (CONFIG_HIFB_HD0_REG_BASEADDR + OPTM_GFX_OFFSET) �����LOGO HD1
	 **/
	#define CONFIG_HIFB_HD_LOGO_REG_BASEADDR            (0xf8cc7200)
	/**
	 ** (CONFIG_HIFB_HD0_REG_BASEADDR + 4 * OPTM_GFX_OFFSET) �����LOGO SD0
	 ** G2��Ȼ���ˣ����ǼĴ���ռ�õĿռ仹��Ԥ����
	 **/
	#define CONFIG_HIFB_SD_LOGO_REG_BASEADDR            (0xf8cc7800)
	/**
	 ** (CONFIG_HIFB_SD0_REG_BASEADDR) ͬԴ��дʹ�ñ����SD0
	 **/
	#define CONFIG_HIFB_WBC_SLAYER_REG_BASEADDR        (0xf8cc7800)
	/** WBC_GP0ͬԴ��д 0xf8cca800**/
	#define CONFIG_HIFB_WBC_GP0_REG_BASEADDR            (0xf8cc9400)
#else
	#define CONFIG_VDP_REG_BASEADDR	             	   (0xf8cc0000)
	#define CONFIG_HIFB_HD0_REG_BASEADDR                (0xf8cc6000)
	/**
	 ** (CONFIG_HIFB_HD0_REG_BASEADDR + OPTM_GFX_OFFSET) �����LOGO HD1
	 **/
	#define CONFIG_HIFB_HD_LOGO_REG_BASEADDR            (0xf8cc6800)
	/**
	 ** (CONFIG_HIFB_HD0_REG_BASEADDR + 3 * OPTM_GFX_OFFSET) �����LOGO SD1(˫�Թ���G3->G5)
	 **/
	#define CONFIG_HIFB_SD_LOGO_REG_BASEADDR            (0xf8cc7800)
	/**
	 ** (CONFIG_HIFB_SD0_REG_BASEADDR + 4*OPTM_GFX_OFFSET) ͬԴ��дʹ�ñ����SD0(G4)
	 **/
	#define CONFIG_HIFB_WBC_SLAYER_REG_BASEADDR        (0xf8cc8000)
	/** WBC_GP0ͬԴ��д 0xf8cca800**/
	#define CONFIG_HIFB_WBC_GP0_REG_BASEADDR            (0xf8cca800)
#endif


#define CONFIG_HIFB_MDDRC_REG_BASEADDR  (0xF8A35000)
#define CONFIG_HIFB_MDDRC_OFFSET         0x8
#define CONFIG_HIFB_MDDRC_MAX_ZONE       32


/**
 **�Ƿ�֧�ֽ�����ͨ��ͼ��3���ص�����ͨ�����ͼ��5
 **/
#if defined(CHIP_TYPE_hi3716cv200)
	/** ֧��˫�Թ���TC **/
	#define CONFIG_HIFB_GFX3_TO_GFX5
#endif

/**
 ** ZME COEF
 ** ����ˮƽ���Ȳ�ѯ
 ** 98MV100/HIFONE-STB: ˮƽ���Ȳ�ѯ�ǰ���20bit
 ** ����: ˮƽ���Ȳ�ѯ�ǰ���12bit
 ** �����ǰ���12bit����ģ���������ٽ���ƫ��
 **/
#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3798cv200_a) \
    || defined(CHIP_TYPE_hi3798cv200)
	#define CONFIG_HIFB_PRECISION_ZMERATIONH_12BITOFFSET          8
#else
	#define CONFIG_HIFB_PRECISION_ZMERATIONH_12BITOFFSET          0
#endif
/**
 ** ˮƽ����ͬʱ�����к�������
 **/
#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3798cv200_a) \
    || defined(CHIP_TYPE_hi3798cv200)
	#define CONFIG_GP0_ZME_HLC_OFFSET_ENABLE
#endif
/**
 **
 **/
#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3798cv200_a) \
    || defined(CHIP_TYPE_hi3798cv200)
	#define CONFIG_HIFB_ALG_G_HZME_PRECISION      1048576
	#define CONFIG_HIFB_ALG_G_VZME_PRECISION      4096
#else
	#define CONFIG_HIFB_ALG_G_HZME_PRECISION      4096
	#define CONFIG_HIFB_ALG_G_VZME_PRECISION      4096
#endif


/**
 ** GP֧�ֵ�ͼ�β���� 
 **/

#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
	#define CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT          4 /** (G0 G1 G2 G3) **/
	#define CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT          1 /** (G4)          **/
#elif defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
	#define CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT          2 /** (G0 G1) **/
	#define CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT          1 /** (G4)    **/
#elif defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
	#define CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT          3 /** (G0 G1 G3) **//** G2��֧�� **/
	#define CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT          1 /** (G4) **/
#else
	#define CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT		  3 /** (G0 G1 G2)       **/
	#define CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT		  2 /** (G3(��G5) G4 G5) **/
#endif

/**
 ** �����ʹ�õ�LOGOͼ�㣬����Ҫ��"\"����Ȼ�ᶨ�����
 **/
#if defined(CHIP_TYPE_hi3796cv100)  || defined(CHIP_TYPE_hi3798cv100)   \
 || defined(CHIP_TYPE_hi3798mv100)  || defined(CHIP_TYPE_hi3796mv100)   \
 || defined(CHIP_TYPE_hi3798cv200_a)|| defined(CHIP_TYPE_hi3798cv200)
	#define CONFIG_HIFB_SD_LOGO_LAYER_ID      HIFB_LAYER_SD_0
	/** �ȴ�ֱ��ˮƽ **/
	#define CONFIG_HIFB_ZME_ORDER_VH
#else 
	#define CONFIG_HIFB_SD_LOGO_LAYER_ID      HIFB_LAYER_SD_1
	/** ��ˮƽ��ֱ **/
	#define CONFIG_HIFB_ZME_ORDER_HV
#endif

/**
 ** �����ʹ�õ�LOGOͼ�㣬����Ҫ��"\"����Ȼ�ᶨ�����
 **/
#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100) \
 || defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) 
	/**
	 ** �Ƿ���Ҫ���д���ֻ�������йأ��͹���û�й�ϵ���߼����Ŷ�֧��
	 ** ���ܲ������ó���
	 **/
	#define CONFIG_HIFB_EXTRACE_DISABLE
#endif

/**
 ** ʹ�ù����Ĵ���ͷ�ļ�
 **/
#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3798cv200_a) \
    || defined(CHIP_TYPE_hi3798cv200)
	#define CONFIG_HIFB_USE_COMM_REGH
#endif

/**
 **�ж�ͼ���Ƿ�֧��
 **/
#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
    #define CONFIG_HIFB_HD0_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_HD1_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_HD2_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_HD3_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_SD0_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_SD2_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_SD3_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD0_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD1_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD2_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD3_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_CURSOR_LAYER_SUPPORT         	  HI_FALSE
#elif defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
    #define CONFIG_HIFB_HD0_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_HD1_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_HD2_LAYER_SUPPORT                  HI_TRUE/**G3**/
	#define CONFIG_HIFB_HD3_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_SD0_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_SD2_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_SD3_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD0_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD1_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD2_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD3_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_CURSOR_LAYER_SUPPORT         	  HI_FALSE	
#else
	#define CONFIG_HIFB_HD0_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_HD1_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_HD2_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_HD3_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_SD0_LAYER_SUPPORT                  HI_TRUE
	#define CONFIG_HIFB_SD2_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_SD3_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD0_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD1_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD2_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_AD3_LAYER_SUPPORT                  HI_FALSE
	#define CONFIG_HIFB_CURSOR_LAYER_SUPPORT         	  HI_FALSE
#endif
#if defined(CHIP_TYPE_hi3719mv100)  || defined(CHIP_TYPE_hi3718mv100)  \
 || defined(CHIP_TYPE_hi3798mv100)  || defined(CHIP_TYPE_hi3796mv100)  \
 || defined(CHIP_TYPE_hi3798cv200_a)|| defined(CHIP_TYPE_hi3798cv200)
    #define CONFIG_HIFB_SD1_LAYER_SUPPORT                  HI_FALSE
#else
	#ifndef HI_BUILD_IN_BOOT
		#ifdef CFG_HIFB_CURSOR_SUPPORT
        	#define CONFIG_HIFB_SD1_LAYER_SUPPORT          HI_TRUE
		#else
       	    #define CONFIG_HIFB_SD1_LAYER_SUPPORT          HI_FALSE
		#endif
	#else
        	#define CONFIG_HIFB_SD1_LAYER_SUPPORT          HI_TRUE
	#endif
#endif
/**
 **�ж�ѹ����ѹ�Ƿ�֧��
 **/
#if    defined(CHIP_TYPE_hi3798mv100)   \
	|| defined(CHIP_TYPE_hi3796mv100)   \
 	|| defined(CHIP_TYPE_hi3798cv200_a) \
 	|| defined(CHIP_TYPE_hi3798cv200)
	#define CONFIG_HIFB_HD0_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_HD1_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_HD2_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_HD3_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_SD0_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_SD1_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_SD2_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_SD3_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_AD0_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_AD1_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_AD2_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_AD3_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_CURSOR_COMPRESSION_SUPPORT         HI_FALSE
#else
	#define CONFIG_HIFB_HD0_COMPRESSION_SUPPORT            HI_TRUE
	#define CONFIG_HIFB_HD1_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_HD2_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_HD3_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_SD0_COMPRESSION_SUPPORT            HI_TRUE
	#define CONFIG_HIFB_SD1_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_SD2_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_SD3_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_AD0_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_AD1_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_AD2_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_AD3_COMPRESSION_SUPPORT            HI_FALSE
	#define CONFIG_HIFB_CURSOR_COMPRESSION_SUPPORT         HI_FALSE
#endif


#if defined(CHIP_TYPE_hi3796cv100)   || defined(CHIP_TYPE_hi3798cv100) \
 || defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
/** ֧��4K*2K**/
	#define CONFIG_HIFB_HD_LAYER_MAXWIDTH         3840
	#define CONFIG_HIFB_HD_LAYER_MAXHEIGHT        2160
	#define CONFIG_HIFB_SD_LAYER_MAXWIDTH         2560
	#define CONFIG_HIFB_SD_LAYER_MAXHEIGHT        1600
	#define CONFIG_HIFB_AD_LAYER_MAXWIDTH         1920
    #define CONFIG_HIFB_AD_LAYER_MAXHEIGHT        1080
	#define CONFIG_HIFB_CURSOR_LAYER_MAXWIDTH     1920
    #define CONFIG_HIFB_CURSOR_LAYER_MAXHEIGHT    1080
#else
	#define CONFIG_HIFB_HD_LAYER_MAXWIDTH         2560
    #define CONFIG_HIFB_HD_LAYER_MAXHEIGHT        1600
	#define CONFIG_HIFB_SD_LAYER_MAXWIDTH         2560
    #define CONFIG_HIFB_SD_LAYER_MAXHEIGHT        1600
	#define CONFIG_HIFB_AD_LAYER_MAXWIDTH         1920
    #define CONFIG_HIFB_AD_LAYER_MAXHEIGHT        1080
	#define CONFIG_HIFB_CURSOR_LAYER_MAXWIDTH     1920
    #define CONFIG_HIFB_CURSOR_LAYER_MAXHEIGHT    1080
#endif

#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
	/** ���֧�ָ����괦�� **/
	#define CONFIG_HIFB_CURSOR_LAYER_NEGATIVE_SUPPORT
#endif

#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
	/** ѹ���������Ѿ�ɾ�� **/
	#ifdef CFG_HIFB_COMPRESSION_SUPPORT
		#undef CFG_HIFB_COMPRESSION_SUPPORT
	#endif
	#define GFX_CONFIG_GP0_MZE_VSP_2TAB_EN
#endif


#define CONFIG_HIFB_STRIDE_16ALIGN                         16

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/
static inline HI_VOID HI_HIFB_GetStride(HI_U32 u32SrcSize, HI_U32 *pu32Stride,HI_U32 u32Align)
{
    #if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
            *pu32Stride = HI_SYS_GET_STRIDE(u32SrcSize);
    #else
            *pu32Stride = (u32SrcSize + u32Align - 1) & (~(u32Align - 1));
    #endif
}


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __HIFB_CONFIG_H__ */
