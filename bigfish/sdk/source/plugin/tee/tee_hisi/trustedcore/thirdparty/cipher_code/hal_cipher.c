/******************************************************************************
 *
 * Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : hal_cipher.c
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2013-12-28
 * Last Modified :
 * Description   : 
 * Function List :
 * History       :
 * ******************************************************************************/
//#include <sw_debug.h>
//#include <libc_sos.h>
//#include <sw_mem_functions.h>

#include "hi_type.h"
#include "drv_cipher_define.h"
#include "drv_cipher_reg.h"
#include "hi_drv_cipher.h"
#include "hal_cipher.h"

#include <sre_mem.h>
//#include "asm/atomic.h"
//#include "ca_authdefine.h"
//#include "ca_common.h"
#include <boot.h>

#define sw_memcpy memcpy
#define sw_memset memset
#define sw_memcmp memcmp

#define HASH_MAX_DURATION (500000)

/***************************** Macro Definition ******************************/

/*process of bit*/
#define HAL_SET_BIT(src, bit)        ((src) |= (1<<bit))
#define HAL_CLEAR_BIT(src,bit)       ((src) &= ~(1<<bit))

#define HI_ASSERT(expr)                                     \
    do{                                                     \
        if (!(expr)) {                                      \
            HI_ERR_CIPHER("ASSERT failed, Condition: %s\n", #expr);    \
        }                                                   \
    }while(0)

/*************************** Structure Definition ****************************/
typedef enum
{
    HASH_READY,
    REC_READY,
    DMA_READY,
}HASH_WAIT_TYPE;
        
/******************************* API declaration *****************************/

// Allocates memory bloc
HI_VOID *Cipher_Malloc(HI_U32 size)
{   
    return SRE_MemAlloc(OS_MID_SYS, OS_MEM_DEFAULT_FSC_PT, size);
    //return sw_malloc(size);
}

// Deallocates or frees a memory block
HI_VOID Cipher_Free(HI_VOID *memblock)
{
    SRE_MemFree(OS_MID_SYS, memblock);
    //sw_free(memblock);


    /* wait for hash_rdy */

//    CIPHER_MSLEEP(1);

/* check if hash module is idle or not */



    /* set bit 6 */

    /* check if set bit 6 valid or not */
            /* clear bit 6*/



}

inline HI_S32 HASH_WaitReady( HASH_WAIT_TYPE enType)
{
    CIPHER_SHA_STATUS_U unCipherSHAstatus;
    HI_SIZE_T ulDuraTime = 0;

    /* wait for hash_rdy */
    ulDuraTime = 0;
    while(1)
    {
        unCipherSHAstatus.u32 = 0;
        (HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_STATUS_ADDR, unCipherSHAstatus.u32);
        if(HASH_READY == enType)
        {
            if(1 == unCipherSHAstatus.bits.hash_rdy)
            {
                break;
            }
        }
        else if (REC_READY == enType)
        {
            if(1 == unCipherSHAstatus.bits.rec_rdy)
            {
                break;
            }
        }
        else if (DMA_READY == enType)
        {
            if(1 == unCipherSHAstatus.bits.dma_rdy)
            {
                break;
            }
        }
        else
        {
            HI_ERR_CIPHER("Error! Invalid wait type!\n");
            return HI_FAILURE;
        }

        ulDuraTime ++;
        if (ulDuraTime >= HASH_MAX_DURATION )
        { 
            HI_ERR_CIPHER("Error! Hash time out!\n");
            return HI_FAILURE;
        }

		CIPHER_MSLEEP(1);
    }

    return HI_SUCCESS;
}

/* check if hash module is idle or not */
static HI_S32 HAL_CIPHER_WaitHashIdle(HI_VOID)
{
    CIPHER_SHA_CTRL_U unCipherSHACtrl;
    HI_SIZE_T ulDuraTime = 0;

__HASH_WAIT__:
    ulDuraTime = 0;
    unCipherSHACtrl.u32 = 0;
    (HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);
    while(0 != (unCipherSHACtrl.bits.usedbyarm | unCipherSHACtrl.bits.usedbyc51))
    {
        ulDuraTime++;
        if (ulDuraTime >= HASH_MAX_DURATION)
        { 
            HI_ERR_CIPHER("Error! Hash module is busy now!\n");
            return HI_FAILURE;
        }
        else
        {
            CIPHER_MSLEEP(1);
            unCipherSHACtrl.u32 = 0;
            (HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);
            continue;
        }
    }

    /* set bit 6 */
    (HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);
    unCipherSHACtrl.bits.usedbyarm = 0x1;
    (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);

    /* check if set bit 6 valid or not */
    unCipherSHACtrl.u32 = 0;
    (HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);
    unCipherSHACtrl.u32 = (unCipherSHACtrl.u32 >> 6) & 0x3;
    switch(unCipherSHACtrl.u32)
    {
        case 0x1:
        {
            return HI_SUCCESS;
        }
        case 0x3:
        {
            /* clear bit 6*/
            (HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);
            unCipherSHACtrl.bits.usedbyarm = 0;
            (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);
            goto __HASH_WAIT__;
        }
        case 0x0:
        case 0x2:
        {
            return HI_FAILURE;
        }
        default:
        {
            return HI_FAILURE;
        }
    }
}

static HI_VOID HAL_CIPHER_MarkHashIdle(HI_VOID)
{
    CIPHER_SHA_CTRL_U unCipherSHACtrl;

    unCipherSHACtrl.u32 = 0;
    (HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);
    unCipherSHACtrl.bits.usedbyarm = 0x0;
    (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);

    return;
}

#if defined(CHIP_TYPE_hi3751v100) || defined(CHIP_TYPE_hi3751v100b) 
static HI_VOID HAL_Cipher_HashOpenClock(HI_VOID)
{
#if defined(CHIP_TYPE_hi3751v100) || defined(CHIP_TYPE_hi3751v100b) 
    U_PERI_CRG49 unShaCrg;

    /* enable hash hardware clock */
    CIPHER_READ_REG(CIPHER_REG_SYS_CLK_SHA_ADDR, unShaCrg.u32);
    unShaCrg.bits.sha_cken = 1;
    unShaCrg.bits.sha_srst_req = 0;
    CIPHER_WRITE_REG(CIPHER_REG_SYS_CLK_SHA_ADDR, unShaCrg.u32);
#endif
}

static HI_VOID HAL_Cipher_HashCloseClock(HI_VOID)
{
#if defined(CHIP_TYPE_hi3751v100) || defined(CHIP_TYPE_hi3751v100b)
    U_PERI_CRG49 unShaCrg;

    /* disable hash hardware clock */
    CIPHER_READ_REG(CIPHER_REG_SYS_CLK_SHA_ADDR, unShaCrg.u32);
    unShaCrg.bits.sha_cken = 0;
    unShaCrg.bits.sha_srst_req = 0;
    CIPHER_WRITE_REG(CIPHER_REG_SYS_CLK_SHA_ADDR, unShaCrg.u32);
#endif
}
#endif

HI_S32 HAL_Cipher_SetInBufNum(HI_U32 chnId, HI_U32 num)
{
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* register0~15 bit is valid, others bits reserved */
    regAddr = CIPHER_REG_CHANn_IBUF_NUM(chnId);

    if (num > 0xffff)
    {
        HI_ERR_CIPHER("value err:%x, set to 0xffff\n", num);
        num = 0xffff;
    }

    CIPHER_WRITE_REG(regAddr, num);

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_GetInBufNum(HI_U32 chnId, HI_U32 *pNum)
{
    HI_U32 regAddr  = 0;
    HI_U32 regValue = 0;

    if (CIPHER_PKGx1_CHAN == chnId || HI_NULL == pNum)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_IBUF_NUM(chnId);
    CIPHER_READ_REG(regAddr, regValue);
    
    *pNum = regValue;

    return HI_SUCCESS;
}


HI_S32 HAL_Cipher_SetInBufCnt(HI_U32 chnId, HI_U32 num)
{
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_IBUF_CNT(chnId);

    if (num > 0xffff)
    {
        HI_ERR_CIPHER("value err:%x, set to 0xffff\n", num);
        num = 0xffff;
    }

    CIPHER_WRITE_REG(regAddr, num);

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_GetInBufCnt(HI_U32 chnId, HI_U32 *pNum)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    if ( (CIPHER_PKGx1_CHAN == chnId) || (HI_NULL == pNum) )
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_IBUF_CNT(chnId);
    CIPHER_READ_REG(regAddr, regValue);
    *pNum = regValue;

    return HI_SUCCESS;
}


HI_S32 HAL_Cipher_SetInBufEmpty(HI_U32 chnId, HI_U32 num)
{
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_IEMPTY_CNT(chnId);

    if (num > 0xffff)
    {
        HI_ERR_CIPHER("value err:%x, set to 0xffff\n", num);
        num = 0xffff;
    }

    CIPHER_WRITE_REG(regAddr, num);

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_GetInBufEmpty(HI_U32 chnId, HI_U32 *pNum)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    if ( (CIPHER_PKGx1_CHAN == chnId) || (HI_NULL == pNum) )
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_IEMPTY_CNT(chnId);
    CIPHER_READ_REG(regAddr, regValue);
    
    *pNum = regValue;

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_SetOutBufNum(HI_U32 chnId, HI_U32 num)
{
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_OBUF_NUM(chnId);

    if (num > 0xffff)
    {
        HI_ERR_CIPHER("value err:%x, set to 0xffff\n", num);
        num = 0xffff;
    }

    CIPHER_WRITE_REG(regAddr, num);

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_GetOutBufNum(HI_U32 chnId, HI_U32 *pNum)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    if ( (CIPHER_PKGx1_CHAN == chnId) || (HI_NULL == pNum) )
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_OBUF_NUM(chnId);
    CIPHER_READ_REG(regAddr, regValue);

    *pNum = regValue;

    return HI_SUCCESS;
}


HI_S32 HAL_Cipher_SetOutBufCnt(HI_U32 chnId, HI_U32 num)
{
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_OBUF_CNT(chnId);

    if (num > 0xffff)
    {
        HI_ERR_CIPHER("value err:%x, set to 0xffff\n", num);
        num = 0xffff;
    }

    CIPHER_WRITE_REG(regAddr, num);
        
    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_GetOutBufCnt(HI_U32 chnId, HI_U32 *pNum)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    if ( (CIPHER_PKGx1_CHAN == chnId) || (HI_NULL == pNum) )
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_OBUF_CNT(chnId);
    CIPHER_READ_REG(regAddr, regValue);

    *pNum = regValue;

    return HI_SUCCESS;
}


HI_S32 HAL_Cipher_SetOutBufFull(HI_U32 chnId, HI_U32 num)
{
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_OFULL_CNT(chnId);

    if (num > 0xffff)
    {
        HI_ERR_CIPHER("value err:%x, set to 0xffff\n", num);
        num = 0xffff;
    }

    CIPHER_WRITE_REG(regAddr, num);
    
    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_GetOutBufFull(HI_U32 chnId, HI_U32 *pNum)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    if ( (CIPHER_PKGx1_CHAN == chnId) || (HI_NULL == pNum) )
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHANn_OFULL_CNT(chnId);
    CIPHER_READ_REG(regAddr, regValue);

    *pNum = regValue;

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_WaitIdle(HI_VOID)
{
    HI_S32 i = 0;
    HI_U32 u32RegAddr = 0;
    HI_U32 u32RegValue = 0;

    /* channel 0 configuration register [31-2]:reserved, [1]:ch0_busy, [0]:ch0_start 
         * [1]:channel 0 status signal, [0]:channel 0 encrypt/decrypt start signal
         */

    u32RegAddr = CIPHER_REG_CHAN0_CFG;
    for (i = 0; i < CIPHER_WAIT_IDLE_TIMES; i++)
    {
        CIPHER_READ_REG(u32RegAddr, u32RegValue);
        if (0x0 == ((u32RegValue >> 1) & 0x01))
        {
            return HI_SUCCESS;
        }
        else
        {
            CIPHER_MSLEEP(1);
        }
    }

    return HI_FAILURE;
}
/*
just only check for channel 0
 */
HI_BOOL HAL_Cipher_IsIdle(HI_U32 chn)
{
    HI_U32 u32RegValue = 0;

    HI_ASSERT(CIPHER_PKGx1_CHAN == chn);

    CIPHER_READ_REG(CIPHER_REG_CHAN0_CFG, u32RegValue);
    if (0x0 == ((u32RegValue >> 1) & 0x01))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

HI_S32 HAL_Cipher_SetDataSinglePkg(HI_DRV_CIPHER_DATA_INFO_S * info)
{
    HI_U32 regAddr = 0;
    HI_U32 i = 0;

    regAddr = CIPHER_REG_CHAN0_CIPHER_DIN(0);
    
    /***/
    for (i = 0; i < (16/sizeof(HI_U32)); i++)
    {
        CIPHER_WRITE_REG(regAddr + (i * sizeof(HI_U32)), (*(info->u32DataPkg + i)) );
    }
    
    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_ReadDataSinglePkg(HI_U32 *pData)
{
    HI_U32 regAddr = 0;
    HI_U32 i = 0;

    regAddr = CIPHER_REG_CHAN0_CIPHER_DOUT(0);

    /***/
    for (i = 0; i < (16/sizeof(HI_U32)); i++)
    {
        CIPHER_READ_REG(regAddr + (i * sizeof(HI_U32)), (*(pData+ i)) );
    }
    
    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_StartSinglePkg(HI_U32 chnId)
{
    HI_U32 u32RegAddr = 0;
    HI_U32 u32RegValue = 0;

    HI_ASSERT(CIPHER_PKGx1_CHAN == chnId);

    u32RegAddr = CIPHER_REG_CHAN0_CFG;
    CIPHER_READ_REG(u32RegAddr, u32RegValue);
    
    u32RegValue |= 0x1;
    CIPHER_WRITE_REG(u32RegAddr, u32RegValue); /* start work */
    
    return HI_SUCCESS;
}


HI_S32 HAL_Cipher_SetBufAddr(HI_U32 chnId, CIPHER_BUF_TYPE_E bufType, HI_U32 addr)
{
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (CIPHER_BUF_TYPE_IN == bufType)
    {
        regAddr = CIPHER_REG_CHANn_SRC_LST_SADDR(chnId);
    }
    else if (CIPHER_BUF_TYPE_OUT == bufType)
    {
        regAddr = CIPHER_REG_CHANn_DEST_LST_SADDR(chnId);
    }
    else
    {
        HI_ERR_CIPHER("SetBufAddr type err:%x.\n", bufType);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CIPHER_WRITE_REG(regAddr, addr);

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_Stat(HI_U32 chnId, HI_U32 *pCipherStat)
{
    HI_U32 u32RegAddr;
    HI_U32 u32RegValue;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
    //    HI_ASSERT(CIPHER_PKGx1_CHAN == chnId);

        u32RegAddr = CIPHER_REG_CHAN0_CIPHER_CTRL;
        CIPHER_READ_REG(u32RegAddr, u32RegValue);

        *pCipherStat = u32RegValue & 0x02;
    }
    else
    {
        u32RegAddr = CIPHER_REG_INT_STATUS;
        CIPHER_READ_REG(u32RegAddr, u32RegValue);
        HAL_Cipher_ClrIntState(u32RegValue);

        *pCipherStat = (u32RegValue >> (chnId + 8)) & 0x01;
    }

    return HI_SUCCESS;
}

HI_VOID HAL_Cipher_Reset(HI_VOID)
{

    //CIPHER_WRITE_REG(CIPHER_SOFT_RESET_ADDR, 1);
    return;
}

HI_S32 HAL_Cipher_GetOutIV(HI_U32 chnId, HI_UNF_CIPHER_CTRL_S* pCtrl)
{
    HI_U32 i = 0;
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN != chnId)
    {
        regAddr = CIPHER_REG_CHAN0_CIPHER_IVIN(0);
    }
    else
    {
        regAddr = CIPHER_REG_CHAN_CIPHER_IVOUT(chnId);
    }


    /***/
    for (i = 0; i < (CI_IV_SIZE/sizeof(HI_U32)); i++)
    {
        CIPHER_READ_REG(regAddr + (i * sizeof(HI_U32)), pCtrl->u32IV[i]);
    }

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_SetInIV(HI_U32 chnId, HI_UNF_CIPHER_CTRL_S* pCtrl)
{
    HI_U32 i = 0;
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN != chnId)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    regAddr = CIPHER_REG_CHAN0_CIPHER_IVIN(0);

    /***/
    for (i = 0; i < (CI_IV_SIZE/sizeof(HI_U32)); i++)
    {
        CIPHER_WRITE_REG(regAddr + (i * sizeof(HI_U32)), pCtrl->u32IV[i]);
    }

    return HI_SUCCESS;
}

//extern HI_S32 CA_DecryptCipher(HI_U32 AddrID, HI_U32 *pDataIn);

HI_S32 HAL_Cipher_SetKey(HI_U32 chnId, HI_UNF_CIPHER_CTRL_S* pCtrl)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i = 0;
    HI_U32 regAddr = 0;

    regAddr = CIPHER_REG_CIPHER_KEY(chnId);

    if(NULL == pCtrl)
    {
        HI_ERR_CIPHER("Error, null pointer!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (HI_FALSE == pCtrl->bKeyByCA)
    {
        for (i = 0; i < (CI_KEY_SIZE/sizeof(HI_U32)); i++)
        {
            CIPHER_WRITE_REG(regAddr + (i * sizeof(HI_U32)), pCtrl->u32Key[i]);
        }
    }
    else
    {
//        HI_ERR_CIPHER("Not support crypto by keyladder, return HI_SUCCESS!\n");
        return HI_SUCCESS;		//Modified by z00213260
    }
    
    return ret;
}

static HI_VOID HAL_Cipher_Delay(HI_U32 u32Count)
{
	HI_U32 i = 0;

	for ( i = 0 ; i < u32Count ; i++ )
	{
	    for ( i = 0 ; i < u32Count ; i++ )
	    {
	        ;
	    }
	}

	return;
}

static HI_S32 HAL_CIPHER_IsCABusy(HI_VOID)
{
    HI_U32 cnt = 0;
    HI_U32 u32CAState = 0;

    while (cnt < 500000)
    {
        u32CAState = 0;
        CIPHER_READ_REG(CIPHER_REG_CA_STATE, u32CAState);

        if( ((u32CAState >> 31) & 0x1) == 0)
        {
            break;
        }

//      mdelay(10);
		HAL_Cipher_Delay(1000);
        cnt++;
    }

    if (cnt >= 500000)
    {
        HI_ERR_CIPHER("Error Time out! u32CAState(0x%x) = 0x%x\n", CIPHER_REG_CA_STATE, u32CAState);
        return HI_FAILURE;
    }
/*
    for(cnt=0; cnt<256; cnt+=4)
    {
        CIPHER_READ_REG(0xF8A90000+cnt, u32CAState);
        HI_PRINT("0x%x\n", u32CAState);
    }*/
    return HI_SUCCESS;
}

HI_S32 HAL_CIPHER_LoadSTBRootKey(HI_U32 u32ChID)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_CA_STB_KEY_CTRL_U unSTBKeyCtrl;
    CIPHER_CA_CONFIG_STATE_U unConfigState;

    unConfigState.u32 = 0;
    CIPHER_READ_REG(CIPHER_REG_CA_CONFIG_STATE, unConfigState.u32);
    if(unConfigState.bits.st_vld != 1)
    {
        HI_ERR_CIPHER("Error: ca unStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    ret = HAL_CIPHER_IsCABusy();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("CA time out!\n");
        return HI_FAILURE;
    }

    unSTBKeyCtrl.u32 = 0;
    CIPHER_READ_REG(CIPHER_REG_STB_KEY_CTRL, unSTBKeyCtrl.u32);
    unSTBKeyCtrl.bits.key_addr = u32ChID;
    CIPHER_WRITE_REG(CIPHER_REG_STB_KEY_CTRL, unSTBKeyCtrl.u32);

    ret = HAL_CIPHER_IsCABusy();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("CA time out!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#if 0
static HI_S32 HAL_CIPHER_IsCABusy(HI_VOID)
{
    HI_U32 cnt = 0;
    HI_U32 u32CAState = 0;

    while (cnt < 50)
    {
        u32CAState = 0;
        CIPHER_READ_REG(CIPHER_REG_CA_STATE, u32CAState);
        if( ((u32CAState >> 31) & 0x1) == 0)
        {
            break;
        }
        CIPHER_MSLEEP(10);
        cnt++;
    }

    if (cnt >= 50)
    {
        HI_ERR_CIPHER("Error Time out! \n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#endif
/*
=========channel n control register==========
[31:22]             weight [in 64bytes, just only for multi-packet channel encrypt or decrypt, otherwise reserved.]
[21:17]             reserved
[16:14]     RW    key_adder [current key sequence number]
[13]          RW    key_sel [key select control, 0-CPU keys, 1-keys from key Ladder]
[12:11]             reserved
[10:9]      RW      key_length[key length control
                                            (1).AES, 00-128 bits key, 01-192bits 10-256bits, 11-128bits
                                            (2).DES, 00-3 keys, 01-3keys, 10-3keys, 11-2keys]
[8]                     reserved
[7:6]       RW      width[bits width control
                                 (1).for DES/3DES, 00-64bits, 01-8bits, 10-1bit, 11-64bits
                                 (2).for AES, 00-128bits, 01-8bits, 10-1bit, 11-128bits]
[5:4]       RW      alg_sel[algorithm type, 00-DES, 01-3DES, 10-AES, 11-DES]
[3:1]       RW      mode[mode control, 
                                  (1).for AES, 000-ECB, 001-CBC, 010-CFB, 011-OFB, 100-CTR, others-ECB
                                  (2).for DES, 000-ECB, 001-CBC, 010-CFB, 011-OFB, others-ECB]
[0]         RW      decrypt[encrypt or decrypt control, 0 stands for encrypt, 1 stands for decrypt]
*/
HI_S32 HAL_Cipher_Config(HI_U32 chnId, HI_BOOL bDecrypt, HI_BOOL bIVChange, HI_UNF_CIPHER_CTRL_S* pCtrl)
{
    HI_U32 keyId = 0;
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;
	HI_UNF_CIPHER_WORK_MODE_E enWorkMode;

    HI_BOOL bKeyByCA = pCtrl->bKeyByCA;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        /* channel 0, single packet encrypt or decrypt channel */
        regAddr = CIPHER_REG_CHAN0_CIPHER_CTRL;
    }
    else
    {
        regAddr = CIPHER_REG_CHANn_CIPHER_CTRL(chnId);
    }

    CIPHER_READ_REG(regAddr, regValue);

    if (HI_FALSE == bDecrypt)/* encrypt */
    {
        regValue &= ~(1 << 0);
    }
    else /* decrypt */
    {
        regValue |= 1;
    }

    /* set mode */
	enWorkMode = pCtrl->enWorkMode;
	if ( HI_UNF_CIPHER_WORK_MODE_CBC_CTS == enWorkMode)
	{
	    enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
	}
    regValue &= ~(0x07 << 1);/* clear bit1~bit3 */
    regValue |= ((enWorkMode & 0x7) << 1);

    /* set algorithm bits */
    regValue &= ~(0x03 << 4); /* clear algorithm bits*/
    regValue |= ((pCtrl->enAlg & 0x3) << 4);

    /* set bits width */
    regValue &= ~(0x03 << 6);
    regValue |= ((pCtrl->enBitWidth & 0x3) << 6);

    regValue &= ~(0x01 << 8);
    regValue |= ((bIVChange & 0x1) << 8);
    if (bIVChange) ///?
    {
        HAL_Cipher_SetInIV(chnId, pCtrl);
    }

    regValue &= ~(0x03 << 9);
    regValue |= ((pCtrl->enKeyLen & 0x3) << 9);

    regValue &= ~(0x01 << 13);
    regValue |= ((bKeyByCA & 0x1) << 13);

//    if (HI_FALSE == bKeyByCA) /* By User */
//    {
        keyId = chnId;/**/

        //HAL_Cipher_SetKey(chnId, pCtrl->u32Key);

        regValue &= ~(0x07 << 14);
        regValue |= ((keyId & 0x7) << 14);
//    }

    CIPHER_WRITE_REG(regAddr, regValue);

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_SetAGEThreshold(HI_U32 chnId, CIPHER_INT_TYPE_E intType, HI_U32 value)
{
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (CIPHER_INT_TYPE_IN_BUF == intType)
    {
        regAddr = CIPHER_REG_CHANn_IAGE_CNT(chnId);
    }
    else if (CIPHER_INT_TYPE_OUT_BUF == intType)
    {
        regAddr = CIPHER_REG_CHANn_OAGE_CNT(chnId);
    }
    else
    {
        HI_ERR_CIPHER("SetAGEThreshold type err:%x.\n", intType);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (value > 0xffff)
    {
        HI_ERR_CIPHER("SetAGEThreshold value err:%x, set to 0xffff\n", value);
        value = 0xffff;
    }

    CIPHER_WRITE_REG(regAddr, value);

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_SetIntThreshold(HI_U32 chnId, CIPHER_INT_TYPE_E intType, HI_U32 value)
{
    HI_U32 regAddr = 0;

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (CIPHER_INT_TYPE_IN_BUF == intType)
    {
        regAddr = CIPHER_REG_CHANn_INT_ICNTCFG(chnId);
    }
    else if (CIPHER_INT_TYPE_OUT_BUF == intType)
    {
        regAddr = CIPHER_REG_CHANn_INT_OCNTCFG(chnId);
    }
    else
    {
        HI_ERR_CIPHER("SetIntThreshold type err:%x.\n", intType);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (value > 0xffff)
    {
        HI_ERR_CIPHER("SetIntThreshold value err:%x, set to 0xffff\n", value);
        value = 0xffff;
    }

    CIPHER_WRITE_REG(regAddr, value);

    return HI_SUCCESS;
}

/*
interrupt enable
[31]-----cipher module unitary interrupt enable
[30:16]--reserved
[15] channel 7 output queue data interrupt enable
[14] channel 6 output queue data interrupt enable
[... ] channel ... output queue data interrupt enable
[9]   channel 1 output queue data interrupt enable
[8]   channel 0 data dispose finished interrupt enble
[7] channel 7 input queue data interrupt enable
[6] channel 6 input queue data interrupt enable
...
[1] channel 1 input queue data interrupt enable
[0] reserved
*/
HI_S32 HAL_Cipher_EnableInt(HI_U32 chnId, int intType)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    regAddr = CIPHER_REG_INT_EN;
    CIPHER_READ_REG(regAddr, regValue);

    regValue |= (1 << 31); /* sum switch int_en */
    regValue |= (1 << 30); /* sec_int_en*/

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        regValue |= (1 << 8);
    }
    else
    {
        if (CIPHER_INT_TYPE_OUT_BUF == (CIPHER_INT_TYPE_OUT_BUF & intType))
        {
            regValue |= (1 << (8 + chnId));
        }

        /* NOT else if */
        if (CIPHER_INT_TYPE_IN_BUF == (CIPHER_INT_TYPE_IN_BUF & intType))
        {
            regValue |= (1 << (0 + chnId));
        }
    }

    CIPHER_WRITE_REG(regAddr, regValue);
/*
    CIPHER_READ_REG(regAddr, regValue);
    HI_ERR_CIPHER("CIPHER_REG_INT_EN(0x%x):set to 0x%x \n", regAddr, regValue);
*/
    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_DisableInt(HI_U32 chnId, int intType)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    regAddr = CIPHER_REG_INT_EN;
    CIPHER_READ_REG(regAddr, regValue);

    if (CIPHER_PKGx1_CHAN == chnId)
    {
        regValue &= ~(1 << 8);
    }
    else
    {
        if (CIPHER_INT_TYPE_OUT_BUF == (CIPHER_INT_TYPE_OUT_BUF & intType))
        {
            regValue &= ~(1 << (8 + chnId));
        }

        /* NOT else if */
        if (CIPHER_INT_TYPE_IN_BUF == (CIPHER_INT_TYPE_IN_BUF & intType))
        {
            regValue &= ~(1 << (0 + chnId));
        }
    }

    if (0 == (regValue & 0x7fffffff))
    {
        regValue &= ~(1 << 31); /* regValue = 0; sum switch int_en */
    }

    CIPHER_WRITE_REG(regAddr, regValue);

    return HI_SUCCESS;
}

HI_VOID HAL_Cipher_DisableAllInt(HI_VOID)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    regAddr = CIPHER_REG_INT_EN;
    regValue = 0;

    CIPHER_WRITE_REG(regAddr, regValue);
}
/*
interrupt status register
[31:16]--reserved
[15] channel 7 output queue data interrupt enable
[14] channel 6 output queue data interrupt enable
[... ] channel ... output queue data interrupt enable
[9]   channel 1 output queue data interrupt enable
[8]   channel 0 data dispose finished interrupt enble
[7] channel 7 input queue data interrupt enable
[6] channel 6 input queue data interrupt enable
...
[1] channel 1 input queue data interrupt enable
[0] reserved
*/

HI_VOID HAL_Cipher_GetIntState(HI_U32 *pState)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    regAddr = CIPHER_REG_INT_STATUS;
    CIPHER_READ_REG(regAddr, regValue);

    if (pState)
    {
        *pState = regValue;
    }
}

HI_VOID HAL_Cipher_GetIntEnState(HI_U32 *pState)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    regAddr = CIPHER_REG_INT_EN;
    
    CIPHER_READ_REG(regAddr, regValue);

    if (pState)
    {
        *pState = regValue;
    }
}

HI_VOID HAL_Cipher_GetRawIntState(HI_U32 *pState)
{
    HI_U32 regAddr = 0;
    HI_U32 regValue = 0;

    regAddr = CIPHER_REG_INT_RAW;
    
    CIPHER_READ_REG(regAddr, regValue);

    if (pState)
    {
        *pState = regValue;
    }
}

HI_VOID HAL_Cipher_ClrIntState(HI_U32 intStatus)
{
    HI_U32 regAddr;
    HI_U32 regValue;

    regAddr = CIPHER_REG_INT_RAW;
    regValue = intStatus;
    CIPHER_WRITE_REG(regAddr, regValue);
}

HI_VOID HAL_Cipher_EnableAllSecChn(HI_VOID)
{
	HI_U32 regAddr = CIPHER_REG_SEC_CHN_CFG;
	HI_U32 regValue = 0;
    HI_U32 i;

    for(i=CIPHER_PKGxN_CHAN_MIN; i<=CIPHER_PKGxN_CHAN_MAX; i++)
	{
	    regValue |= 0x01 << i;
    }

    CIPHER_WRITE_REG(regAddr, regValue);
    
	return;
}

HI_VOID HAL_Cipher_SetHdcpModeEn(HI_DRV_CIPHER_HDCP_KEY_MODE_E enMode)
{
    HI_U32 u32RegAddr = 0;
    CIPHER_HDCP_MODE_CTRL_U stHDCPModeCtrl;
    memset((HI_VOID *)&stHDCPModeCtrl, 0, sizeof(stHDCPModeCtrl.u32));
    u32RegAddr = CIPHER_REG_HDCP_MODE_CTRL;
    CIPHER_READ_REG(u32RegAddr, stHDCPModeCtrl.u32);
    if ( CIPHER_HDCP_MODE_NO_HDCP_KEY == enMode)
    {
        stHDCPModeCtrl.bits.hdcp_mode_en = 0;
    }
    else
    {
        stHDCPModeCtrl.bits.hdcp_mode_en = 1;
    }
    CIPHER_WRITE_REG(u32RegAddr, stHDCPModeCtrl.u32);
    
    return;
}
HI_S32 HAL_Cipher_GetHdcpModeEn(HI_DRV_CIPHER_HDCP_KEY_MODE_E *penMode)
{
    HI_U32 u32RegAddr = 0;
    CIPHER_HDCP_MODE_CTRL_U stHDCPModeCtrl;
    if ( NULL == penMode )
    {
        HI_ERR_CIPHER("Invald param, null pointer!\n");
        return HI_FAILURE;
    }
    memset((HI_VOID *)&stHDCPModeCtrl, 0, sizeof(CIPHER_HDCP_MODE_CTRL_U));
    u32RegAddr = CIPHER_REG_HDCP_MODE_CTRL;
    CIPHER_READ_REG(u32RegAddr, stHDCPModeCtrl.u32);
    if ( 0 == stHDCPModeCtrl.bits.hdcp_mode_en)
    {
        *penMode = CIPHER_HDCP_MODE_NO_HDCP_KEY;
    }
    else
    {
        *penMode = CIPHER_HDCP_MODE_HDCP_KEY;
    }
    return HI_SUCCESS;
}

HI_VOID HAL_Cipher_SetHdcpKeyRamMode(HI_DRV_CIPHER_HDCP_KEY_RAM_MODE_E enMode)
{
    HI_U32 u32RegAddr = 0;
    CIPHER_HDCP_MODE_CTRL_U unHDCPModeCtrl;
    memset((HI_VOID *)&unHDCPModeCtrl, 0, sizeof(CIPHER_HDCP_MODE_CTRL_U));
    u32RegAddr = CIPHER_REG_HDCP_MODE_CTRL;
    CIPHER_READ_REG(u32RegAddr, unHDCPModeCtrl.u32);
    if ( CIPHER_HDCP_KEY_RAM_MODE_READ == enMode)
    {
        unHDCPModeCtrl.bits.tx_read = 0x1;      //hdmi read mode
    }
    else
    {
        unHDCPModeCtrl.bits.tx_read = 0x0;      //cpu write mode
    }    
    CIPHER_WRITE_REG(u32RegAddr, unHDCPModeCtrl.u32);
    return;
}

HI_S32 HAL_Cipher_GetHdcpKeyRamMode(HI_DRV_CIPHER_HDCP_KEY_RAM_MODE_E *penMode)
{
    HI_U32 u32RegAddr = 0;
    CIPHER_HDCP_MODE_CTRL_U unHDCPModeCtrl;
    if ( NULL == penMode )
    {
        return HI_FAILURE;
    }
    memset((HI_VOID *)&unHDCPModeCtrl, 0, sizeof(CIPHER_HDCP_MODE_CTRL_U));
    u32RegAddr = CIPHER_REG_HDCP_MODE_CTRL;
    CIPHER_READ_REG(u32RegAddr, unHDCPModeCtrl.u32);
    if ( 0 == unHDCPModeCtrl.bits.tx_read )
    {
        *penMode = CIPHER_HDCP_KEY_RAM_MODE_WRITE;      //cpu write mode
    }
    else
    {
        *penMode = CIPHER_HDCP_KEY_RAM_MODE_READ;       //hdmi read mode
    }    
    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_SetHdcpKeySelectMode(HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enHdcpKeySelectMode)
{
    HI_U32 u32RegAddr = 0;
    CIPHER_HDCP_MODE_CTRL_U unHDCPModeCtrl;
    memset((HI_VOID *)&unHDCPModeCtrl, 0, sizeof(CIPHER_HDCP_MODE_CTRL_U));
    u32RegAddr = CIPHER_REG_HDCP_MODE_CTRL;
    CIPHER_READ_REG(u32RegAddr, unHDCPModeCtrl.u32);       
    if ( CIPHER_HDCP_KEY_TYPE_OTP_ROOT_KEY == enHdcpKeySelectMode )
    {
        unHDCPModeCtrl.bits.hdcp_rootkey_sel = 0x00;
    }
    else if ( CIPHER_HDCP_KEY_TYPE_HISI_DEFINED == enHdcpKeySelectMode )
    {
        unHDCPModeCtrl.bits.hdcp_rootkey_sel = 0x01;
    }
    else if ( CIPHER_HDCP_KEY_TYPE_HOST_ROOT_KEY == enHdcpKeySelectMode)
    {
        unHDCPModeCtrl.bits.hdcp_rootkey_sel = 0x2;
    }
    else
    {
        unHDCPModeCtrl.bits.hdcp_rootkey_sel = 0x3;
        CIPHER_WRITE_REG(u32RegAddr, unHDCPModeCtrl.u32);
        HI_ERR_CIPHER("Unexpected hdcp key type selected!\n");
        return HI_FAILURE;
    }
    CIPHER_WRITE_REG(u32RegAddr, unHDCPModeCtrl.u32);
    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_GetHdcpKeySelectMode(HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E *penHdcpKeySelectMode)
{
    HI_U32 u32RegAddr = 0;
    CIPHER_HDCP_MODE_CTRL_U unHDCPModeCtrl;
    if ( NULL == penHdcpKeySelectMode )
    {
        HI_ERR_CIPHER("Invalid param, NULL pointer!\n");
        return HI_FAILURE;
    }
    memset((HI_VOID *)&unHDCPModeCtrl, 0, sizeof(CIPHER_HDCP_MODE_CTRL_U));
    u32RegAddr = CIPHER_REG_HDCP_MODE_CTRL;
    CIPHER_READ_REG(u32RegAddr, unHDCPModeCtrl.u32);
    if ( 0x00 == unHDCPModeCtrl.bits.hdcp_rootkey_sel )
    {
        *penHdcpKeySelectMode = CIPHER_HDCP_KEY_TYPE_OTP_ROOT_KEY;
    }
    else if ( 0x01 == unHDCPModeCtrl.bits.hdcp_rootkey_sel)
    {
        *penHdcpKeySelectMode = CIPHER_HDCP_KEY_TYPE_HISI_DEFINED;
    }
    else if (  0x02 == unHDCPModeCtrl.bits.hdcp_rootkey_sel )
    {
        *penHdcpKeySelectMode = CIPHER_HDCP_KEY_TYPE_HOST_ROOT_KEY;
    }
    else
    {
        *penHdcpKeySelectMode = CIPHER_HDCP_KEY_TYPE_BUTT;
    }
    return HI_SUCCESS;
}

HI_VOID HAL_Cipher_ClearHdcpCtrlReg(HI_VOID)
{
    CIPHER_WRITE_REG(CIPHER_REG_HDCP_MODE_CTRL, 0);
    return;
}

static void sleep_for_round(int A, int B)
{
	int i= 0;
	
	for(i = 0; i < A; i++)
	{
		for(i = 0; i < B; i++)
		{
			;
		}
	}
}

HI_S32 HAL_Cipher_HashSoftReset(HI_VOID)
{
    U_PERI_CRG49 unShaCrg;

/* reset request */
    CIPHER_READ_REG(CIPHER_REG_SYS_CLK_SHA_ADDR, unShaCrg.u32);
    unShaCrg.bits.sha_cken = 1;
    unShaCrg.bits.sha_srst_req = 1;
    CIPHER_WRITE_REG(CIPHER_REG_SYS_CLK_SHA_ADDR, unShaCrg.u32);

    CIPHER_MSLEEP(10);

/* cancel reset */
    CIPHER_READ_REG(CIPHER_REG_SYS_CLK_SHA_ADDR, unShaCrg.u32);
    unShaCrg.bits.sha_cken = 1;
    unShaCrg.bits.sha_srst_req = 0;
    CIPHER_WRITE_REG(CIPHER_REG_SYS_CLK_SHA_ADDR, unShaCrg.u32);

    (HI_VOID)HAL_CIPHER_MarkHashIdle();
    return HI_SUCCESS;
}

HI_VOID HAL_Cipher_Init(void)
{
    CIPHER_CA_SYS_CLK_U unCRG;

    unCRG.u32 = 0;

#ifdef CHIP_TYPE_hi3716cv200es
    CIPHER_READ_REG(CIPHER_REG_SYS_CLK_CA_ADDR, unCRG.u32);
    unCRG.bits.ca_kl_srst_req = 1;
    unCRG.bits.ca_ci_srst_req = 1;
    unCRG.bits.otp_srst_req = 1;
    /* clock open */
    unCRG.bits.ca_kl_bus_cken = 1;    
    unCRG.bits.ca_ci_bus_cken = 1;
    unCRG.bits.ca_ci_cken = 1;

    /* ca clock select : 200M */
    unCRG.bits.ca_clk_sel = 0;
    CIPHER_WRITE_REG(CIPHER_REG_SYS_CLK_CA_ADDR, unCRG.u32);

//    CIPHER_MSLEEP(1);
	sleep_for_round(100, 100);
    
    unCRG.u32 = 0;
    CIPHER_READ_REG(CIPHER_REG_SYS_CLK_CA_ADDR, unCRG.u32);
    unCRG.bits.ca_kl_srst_req = 0;
    unCRG.bits.ca_ci_srst_req = 0;
    unCRG.bits.otp_srst_req = 0;

    /* make sure clock opened */
    unCRG.bits.ca_kl_bus_cken = 1;    
    unCRG.bits.ca_ci_bus_cken = 1;
    unCRG.bits.ca_ci_cken = 1;
    /* make sure ca clock select : 200M */
    unCRG.bits.ca_clk_sel = 0;
    CIPHER_WRITE_REG(CIPHER_REG_SYS_CLK_CA_ADDR, unCRG.u32);
#else

    CIPHER_READ_REG(CIPHER_REG_SYS_CLK_CA_ADDR, unCRG.u32);
    unCRG.bits.ca_kl_srst_req = 1;
    unCRG.bits.ca_ci_srst_req = 1;
    unCRG.bits.otp_srst_req = 1;

    /* ca clock select : 200M */
    unCRG.bits.ca_ci_clk_sel = 0;
    CIPHER_WRITE_REG(CIPHER_REG_SYS_CLK_CA_ADDR, unCRG.u32);

//    CIPHER_MSLEEP(1);
	sleep_for_round(100, 100);

    unCRG.u32 = 0;
    CIPHER_READ_REG(CIPHER_REG_SYS_CLK_CA_ADDR, unCRG.u32);
    unCRG.bits.ca_kl_srst_req = 0;
    unCRG.bits.ca_ci_srst_req = 0;
    unCRG.bits.otp_srst_req = 0;

    /* make sure ca clock select : 200M */
    unCRG.bits.ca_ci_clk_sel = 0;
    CIPHER_WRITE_REG(CIPHER_REG_SYS_CLK_CA_ADDR, unCRG.u32);

#endif

#if defined(CHIP_TYPE_hi3798cv200_a)
    HAL_Cipher_SetHdcpKeyTxRead(CIPHER_HDCP_KEY_RAM_MODE_READ);
#endif

    return;
}

HI_VOID HAL_Cipher_HDCPTxReadEnable(HI_VOID)
{
    CIPHER_HDCP_MODE_CTRL_U unCRG;

    unCRG.u32 = 0;
    CIPHER_READ_REG(CIPHER_REG_HDCP_MODE_CTRL, unCRG.u32);
	unCRG.bits.tx_read = 1;
	CIPHER_WRITE_REG(CIPHER_REG_HDCP_MODE_CTRL, unCRG.u32);
//
	CIPHER_MSLEEP(5000);

	unCRG.u32 = 0;
    CIPHER_READ_REG(CIPHER_REG_HDCP_MODE_CTRL, unCRG.u32);
	HI_INFO_CIPHER("tx_read = %d\n", unCRG.bits.tx_read);

	return;
}

HI_U32 g_u32HashCount = 0;
HI_U32 g_u32RecLen = 0;
HI_S32 HAL_Cipher_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_SHA_CTRL_U unCipherSHACtrl;
    CIPHER_SHA_START_U unCipherSHAStart;

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error! Null pointer input!\n");
        return HI_FAILURE;
    }

    ret = HAL_CIPHER_WaitHashIdle();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Time out!Hash is busy now!\n");
        return HI_FAILURE;
    }

    g_u32HashCount = 0;
    g_u32RecLen = 0;

    /* wait for hash_rdy */
    ret = HASH_WaitReady(HASH_READY);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Hash wait ready failed! g_u32HashCount = 0x%08x\n", g_u32HashCount);
        (HI_VOID)HAL_Cipher_HashSoftReset();
        return HI_FAILURE;
    }

    /* write total len low and high */
    (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_TOTALLEN_LOW_ADDR, 0xFFFFFFFF);
    (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_TOTALLEN_HIGH_ADDR, 0);

    /* config sha_ctrl : read by dma first, and by cpu in the hash final function */
    unCipherSHACtrl.u32 = 0;
    (HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);
    unCipherSHACtrl.bits.read_ctrl = 0;
    if( HI_UNF_CIPHER_HASH_TYPE_SHA1 == pCipherHashData->enShaType )
    {
        unCipherSHACtrl.bits.hardkey_hmac_flag = 0;
        unCipherSHACtrl.bits.sha_sel= 0x0;
    }
    else if( HI_UNF_CIPHER_HASH_TYPE_SHA256 == pCipherHashData->enShaType )
    {
        unCipherSHACtrl.bits.hardkey_hmac_flag = 0;
        unCipherSHACtrl.bits.sha_sel= 0x1;
    }
    else if( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pCipherHashData->enShaType )
    {
		/* unCipherSHACtrl.bits.hardkey_hmac_flag = 1; */
        unCipherSHACtrl.bits.hardkey_hmac_flag = 0;
        unCipherSHACtrl.bits.sha_sel= 0x0;
		/* unCipherSHACtrl.bits.hardkey_sel = pCipherHashData->enHMACKeyFrom; */
    }
    else if( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pCipherHashData->enShaType )
    {
        unCipherSHACtrl.bits.hardkey_hmac_flag = 0;
        unCipherSHACtrl.bits.sha_sel= 0x1;
		/* unCipherSHACtrl.bits.hardkey_sel = pCipherHashData->enHMACKeyFrom; */
    }
    else
    {
        HI_ERR_CIPHER("Invalid hash type input!\n");
        (HI_VOID)HAL_Cipher_HashSoftReset();
        return HI_FAILURE;
    }

    (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_CTRL_ADDR, unCipherSHACtrl.u32);    
    
    /* config sha_start */
    unCipherSHAStart.u32 = 0;
    unCipherSHAStart.bits.sha_start = 1;
    (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_START_ADDR, unCipherSHAStart.u32);

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error, Null pointer input!\n");
        (HI_VOID)HAL_Cipher_HashSoftReset();
        return HI_FAILURE;
    }

    ret= HASH_WaitReady(REC_READY);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Hash wait ready failed! g_u32HashCount = 0x%08x\n", g_u32HashCount);
        (HI_VOID)HAL_Cipher_HashSoftReset();
        return HI_FAILURE;
    }

//  (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_DMA_START_ADDR, pCipherHashData->stMMZBuffer.u32StartPhyAddr);
    (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_DMA_START_ADDR, (HI_U32)pCipherHashData->pu8InputData);
    (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_DMA_LEN, pCipherHashData->u32InputDataLen);
    g_u32HashCount += pCipherHashData->u32InputDataLen;
    g_u32RecLen += pCipherHashData->u32InputDataLen;

    ret  = HASH_WaitReady(REC_READY);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Hash wait ready failed! g_u32HashCount = 0x%08x\n", g_u32HashCount);
        (HI_VOID)HAL_Cipher_HashSoftReset();
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_Cipher_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_SHA_STATUS_U unCipherSHAStatus;
	HI_U32 sha_out[8];
    HI_U32 i = 0;

    if( (NULL == pCipherHashData) || (NULL == pCipherHashData->pu8Output) )
    {
        HI_ERR_CIPHER("Error, Null pointer input!\n");
        (HI_VOID)HAL_Cipher_HashSoftReset();
        return HI_FAILURE;
    }

//  (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_DMA_START_ADDR, pCipherHashData->stMMZBuffer.u32StartPhyAddr);
    (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_DMA_START_ADDR, (HI_U32)pCipherHashData->pu8InputData);
    (HI_VOID)CIPHER_WRITE_REG(CIPHER_HASH_REG_DMA_LEN, pCipherHashData->u32InputDataLen);
    g_u32HashCount += pCipherHashData->u32InputDataLen;
    g_u32RecLen += pCipherHashData->u32InputDataLen;

    /* wait for rec_ready instead of hash_ready */
    ret= HASH_WaitReady(REC_READY);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Hash wait ready failed, u32HashCount_g = 0x%08x\n", g_u32HashCount);
        (HI_VOID)HAL_Cipher_HashSoftReset();
        return HI_FAILURE;
    }

    HI_INFO_CIPHER("***********  u32TotalDataLen=%d, u32Rec_len=%d ********\n", pCipherHashData->u32TotalDataLen, g_u32RecLen);

    /* read digest */
    unCipherSHAStatus.u32 = 0;
    (HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_STATUS_ADDR, unCipherSHAStatus.u32);

    if( 0x00 == unCipherSHAStatus.bits.error_state )
    {
        memset(sha_out, 0x0, sizeof(sha_out));
        if( (HI_UNF_CIPHER_HASH_TYPE_SHA1 == pCipherHashData->enShaType)
         || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pCipherHashData->enShaType))
        {
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT1, (sha_out[0]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT2, (sha_out[1]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT3, (sha_out[2]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT4, (sha_out[3]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT5, (sha_out[4]));

    		for(i = 0; i < 5; i++)
    		{
    		    /* small endian */
    			pCipherHashData->pu8Output[i * 4 + 3] = sha_out[i] >> 24;
    			pCipherHashData->pu8Output[i * 4 + 2] = sha_out[i] >> 16;
    			pCipherHashData->pu8Output[i * 4 + 1] = sha_out[i] >> 8;
    			pCipherHashData->pu8Output[i * 4]     = sha_out[i];
    		}
        }
        else if( (HI_UNF_CIPHER_HASH_TYPE_SHA256 == pCipherHashData->enShaType )
              || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pCipherHashData->enShaType))
        {
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT1, (sha_out[0]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT2, (sha_out[1]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT3, (sha_out[2]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT4, (sha_out[3]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT5, (sha_out[4]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT6, (sha_out[5]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT7, (sha_out[6]));
    		(HI_VOID)CIPHER_READ_REG(CIPHER_HASH_REG_SHA_OUT8, (sha_out[7]));

    		for(i = 0; i < 8; i++)
    		{
    		    /* small endian */
    			pCipherHashData->pu8Output[i * 4 + 3] = sha_out[i] >> 24;
    			pCipherHashData->pu8Output[i * 4 + 2] = sha_out[i] >> 16;
    			pCipherHashData->pu8Output[i * 4 + 1] = sha_out[i] >> 8;
    			pCipherHashData->pu8Output[i * 4]     = sha_out[i];
    		}
        }
        else
        {
            HI_ERR_CIPHER("Invalid hash type : %d!\n", pCipherHashData->enShaType);
            (HI_VOID)HAL_Cipher_HashSoftReset();
            return HI_FAILURE;
        }
    }
    else
    {
        HI_ERR_CIPHER("Error! SHA Status Reg: error_state = %d!\n", unCipherSHAStatus.bits.error_state);
        (HI_VOID)HAL_Cipher_HashSoftReset();
        return HI_FAILURE;
    }

    (HI_VOID)HAL_Cipher_HashSoftReset();
    (HI_VOID)HAL_CIPHER_MarkHashIdle();

    return HI_SUCCESS;
}

HI_VOID HAL_Cipher_DeInit(void)
{
    /* use the same clock of CA */
    //CIPHER_WRITE_REG(IO_ADDRESS(CIPHER_REG_SYS_CLK_CA_ADDR), 0x0103); 
    //CIPHER_WRITE_REG(IO_ADDRESS(CIPHER_REG_SYS_CLK_CA_ADDR), 0x3); /* close cipher's clock */
}

