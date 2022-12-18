/**
**  @file nocs1x_csd_impl.h
**
**  @brief
**    Implementation of Chipset Security Driver API for NOCS 1.x Secure chipset
**
**  @ingroup
**    CSD
**
**  @author
**    Hisilicon hisecurity team
**
**  @version
**    Revision: 1.0
**
** COPYRIGHT:
**   2001-2011, Hisilicon Tech. Co., Ltd.
**
** HISTORY:
*/
#ifndef CSD_IMPL_H
#define CSD_IMPL_H

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

#include "hi_type.h"
#include "hi_debug.h"
#include "asm/ioctl.h"

#define CSD_R2R_NB_OF_PROTECTING_KEYS 1
#define CSD_DSC_NB_OF_PROTECTING_KEYS 1
#define CSD_SCR_NB_OF_PROTECTING_KEYS 1

#define NAGRA_EMI_MASK_RAW  0x4000
#define NAGRA_EMI_MASK_TDES  0x0040
#define NAGRA_EMI_MASK_AES  0x0020

#define NAGRA_CV200_CHIP_REVERSION "V20"

enum ECsdBootMode
{
    CSD_FLASH_TYPE_SPI = 0,     /**<SPI flash*/
    CSD_FLASH_TYPE_NAND,        /**<nand flash*/
    CSD_FLASH_TYPE_UNPROGRAMMED,/**<unprogrammed*/
    LAST_CSD_FLASH_TYPE
};

enum TCsdDscEmi
{
     DVB_CSA_V2         = 0x0000,
     DVB_CSA_V3         = 0x0001,
     AES_CBC_IDSA       = 0x0020,
     AES_ECB            = 0x0021,
     AES_CBC_CI         = 0x0022,
     LAST_CSD_DSC_EMI
};

enum TCsdScrEmi
{
     PAYLOAD_AES_CBC_IDSA       = 0x0020,
     PAYLOAD_AES_ECB            = 0x0021,
     PAYLOAD_AES_CBC_CI         = 0x0022,
     RAW_AES_CBC                = 0x4020,
     RAW_AES_ECB                = 0x4021,
     RAW_AES_CBC_PIFF           = 0x4022,
     RAW_AES_CBC_APPLE          = 0x4023,
     RAW_AES_CTR                = 0x4024,
     RAW_TDES_CBC               = 0x4040,
     RAW_TDES_ECB               = 0x4041,
     LAST_CSD_SCR_EMI
};

struct SCsdR2RKeyPathHandle
{
    HI_HANDLE handle;
};

struct SCsdDscKeyPathHandle
{
    HI_HANDLE hDescrambler;      /* demux hDescrambler */
    HI_HANDLE hDmxVidChn;        /* demux video channel */
    HI_HANDLE hDmxAudChn;        /*demux audio channel */
    HI_U8 dscIVAesCIplusPayload[16];     /*The IV for AES CI+*/
};

struct SCsdScrKeyPathHandle
{
    HI_HANDLE handle;            /* cipher handle for raw*/
    HI_HANDLE hDescrambler;      /* demux hDescrambler for payload */
    HI_HANDLE hDmxVidChn;        /* demux video channel for payload */
    HI_HANDLE hDmxAudChn;        /*demux audio channel for payload */
};

struct SCsdInitParameters
{
};

struct SCsdTerminateParameters 
{
};

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif/* End of #ifndef CSD_IMPL_H */

