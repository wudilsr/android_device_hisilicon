/******************************************************************************

Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : ca_ssd.h
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/
#ifndef __CA_API_SSD_H__
#define __CA_API_SSD_H__

#ifdef HI_LOADER_APPLOADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif  /*HI_LOADER_APPLOADER*/

#include "hi_type.h"
#include "hi_flash.h"

#if defined(HI_ADVCA_SUPPORT) && !defined(HI_ADVCA_TYPE_NAGRA)
#include "cx_ssd.h"
#endif

#define HI_FATAL_CA_SSD(fmt...)  \
	        HI_TRACE(HI_LOG_LEVEL_FATAL, HI_ID_CA, fmt) 
#define HI_ERR_CA_SSD(fmt...) \
            HI_TRACE(HI_LOG_LEVEL_ERROR, HI_ID_CA, fmt)
#define HI_WARN_CA_SSD(fmt...) \
            HI_TRACE(HI_LOG_LEVEL_WARNING, HI_ID_CA, fmt)
#define HI_INFO_CA_SSD(fmt...) \
            HI_TRACE(HI_LOG_LEVEL_INFO, HI_ID_CA, fmt)

#define SSD_Free( p ) \
    do {\
        if (p){\
            free(p); p = NULL;} \
    } while (0)

#define SSD_Malloc( p, len ) \
    do {\
        if(len){ \
            p = malloc(len);} \
    } while (0)

/* Error info returns */
#define HI_ERR_CA_SSD_BASE              (0xFF000000U)
#define HI_ERR_CA_SSD_INVALID_PARAM     (HI_ERR_CA_SSD_BASE + 0x0)
#define HI_ERR_CA_SSD_INIT_FAILED       (HI_ERR_CA_SSD_BASE + 0x1)
#define HI_ERR_CA_SSD_DEINIT_FAILED     (HI_ERR_CA_SSD_BASE + 0x2)
#define HI_ERR_CA_SSD_AUTH_FAILED       (HI_ERR_CA_SSD_BASE + 0x3)
#define HI_ERR_CA_SSD_ENC_FAILED        (HI_ERR_CA_SSD_BASE + 0x4)
#define HI_ERR_CA_SSD_DEC_FAILED        (HI_ERR_CA_SSD_BASE + 0x5)
#define HI_ERR_CA_SSD_BURN_FAILED       (HI_ERR_CA_SSD_BASE + 0x6)

/* macro definitions */
typedef enum CA_SSD_UPGRD_TYPE
{
    CA_SSD_UPGRD_TYPE_USB,
    CA_SSD_UPGRD_TYPE_IP,
    CA_SSD_UPGRD_TYPE_OTA,
    CA_SSD_UPGRD_TYPE_BUTT,
}CA_SSD_UPGRD_TYPE;

/* macro definitions */
typedef enum CA_SSD_IMAGE_TYPE
{
    CA_SSD_IMAGE_TYPE_BOOT,
    CA_SSD_IMAGE_TYPE_LOADER,
    CA_SSD_IMAGE_TYPE_STBINFO,
    CA_SSD_IMAGE_TYPE_LOADERDB,
    CA_SSD_IMAGE_TYPE_BUTT,
}CA_SSD_IMAGE_TYPE;

/* crypto key type */
typedef enum CA_SSD_KEY_TYPE
{
    CA_SSD_KEY_GROUP1,
    CA_SSD_KEY_GROUP2,
    CA_SSD_KEY_BUTT,
}CA_SSD_KEY_TYPE;


#ifdef HI_ADVCA_SUPPORT

/* 
 Descryption�� ��ȡFlash����ʱ����������б����ܴ洢�����ȡ����ʹ�ô˽ӿڽ��ܡ�
 param pu8StartVirAddr [in/out]�� ����ܵľ���Buffer��ʼ��ַ��
 param u32Len [in]�� ����ܵľ����Buffer���ȡ�
 param enImageType [in]�� ����ܵķ������ơ���conax�������жϽ��ܵľ����Ƿ�ΪLoaderDB�������Ӷ�ѡ��ͬ��key group��
 */
HI_S32 CA_SSD_DecryptImage(HI_U8 *pu8Buffer, HI_U32 u32Len, CA_SSD_KEY_TYPE enImageType);


/* 
 Descryption�� ��������дFlash����ǰ����������豻���ܴ洢������ʹ�ô˽ӿڼ��ܡ�
 param pu8StartVirAddr [in/out]�� ����ܵľ���Buffer��ʼ��ַ��
 param u32Len [in]�� ����ܵľ����Buffer���ȡ�
 param enImageType [in]�� ����ܵķ������ơ���conax�������жϼ��ܵľ����Ƿ�ΪLoaderDB�������Ӷ�ѡ��ͬ��key group��
 */
HI_S32 CA_SSD_EncryptImage(HI_U8 *pu8Buffer, HI_U32 u32Len, CA_SSD_KEY_TYPE enImageType);

/* 
 Descryption�� У��Loader���������Magic number��
 param pu8StartVirAddr [in]:��ҪУ���Buffer��ʼ��ַ��
 param u32Len [in]�� ��ҪУ���Buffer�ĳ��ȡ�
 return��HI_SUCCESSΪ�ɹ���
         HI_FAILUREΪʧ�ܡ�
*/
HI_S32 CA_SSD_AuthenticateEx(HI_U8 *ppu8Buffer, HI_U32 *pu32Len);

#else           /*#ifdef HI_ADVCA_SUPPORT*/

static inline HI_S32 CA_SSD_DecryptImage(HI_U8 *pu8StartVirAddr, HI_U32 u32Len, CA_SSD_KEY_TYPE enKeyType) { return HI_SUCCESS;}

static inline HI_S32 CA_SSD_EncryptImage(HI_U8 *pu8StartVirAddr, HI_U32 u32Len, CA_SSD_KEY_TYPE enKeyType) { return HI_SUCCESS;}

static inline HI_S32 CA_SSD_AuthenticateEx(HI_U8 *ppu8Buffer, HI_U32 *pu32Len) { return HI_SUCCESS;}

#endif  /*HI_ADVCA_SUPPORT*/

#endif  /*__CA_API_SSD_H__*/

