/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_cipher.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
//#include <asm/arch/hardware.h>
#include <asm/setup.h>
#include <asm/barrier.h>    /* mb() */
#include <asm/uaccess.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/fcntl.h>
#include <linux/param.h>
#include <linux/delay.h>

#include <linux/init.h>
#include <asm/io.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/workqueue.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/wait.h>
//#include <asm/semaphore.h>
#include <linux/spinlock.h>
#include <linux/version.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/random.h>

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_common.h"
#include "drv_cipher_define.h"
#include "drv_cipher_ioctl.h"
#include "drv_cipher_ext.h"
#include "drv_advca_ext.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_mem.h"
#include "hi_drv_mmz.h"
#include "hi_drv_module.h"
#include "hi_drv_cipher.h"
#include "hal_cipher.h"
#include "drv_cipher.h"
#include "drv_cipher_sha1.h"
#include "drv_cipher_sha2.h"

HI_DECLARE_MUTEX(g_CipherMutexKernel);
HI_DECLARE_MUTEX(g_HashMutexKernel);

extern HI_VOID HI_DRV_SYS_GetChipVersion(HI_CHIP_TYPE_E *penChipType, HI_CHIP_VERSION_E *penChipID);
HI_S32 DRV_CIPHER_ConfigChn(HI_U32 softChnId,  HI_UNF_CIPHER_CTRL_S *pConfig);
HI_S32 DRV_CIPHER_DestroyHandle(HI_HANDLE hCipherchn);
HI_S32 DRV_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey);


HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S g_stFlashHdcpKey;
HI_BOOL g_bHDCPKeyLoadFlag = HI_FALSE;

#define CI_BUF_LIST_SetIVFlag(u32Flags)
#define CI_BUF_LIST_SetEndFlag(u32Flags)

CIPHER_EXPORT_FUNC_S s_CipherExportFuncs =
{
    .pfnCipherCreateHandle      = HI_DRV_CIPHER_CreateHandle,
    .pfnCipherConfigChn         = HI_DRV_CIPHER_ConfigChn,
    .pfnCipherDestroyHandle     = HI_DRV_CIPHER_DestroyHandle,
    .pfnCipherEncrypt           = HI_DRV_CIPHER_Encrypt,
    .pfnCipherDecrypt           = HI_DRV_CIPHER_Decrypt,
    .pfnCipherEncryptMulti      = HI_DRV_CIPHER_EncryptMulti,
    .pfnCipherDecryptMulti      = HI_DRV_CIPHER_DecryptMulti,
    .pfnCipherGetRandomNumber   = HI_DRV_CIPHER_GetRandomNumber,
    .pfnCipherGetHandleConfig   = HI_DRV_CIPHER_GetHandleConfig,
    .pfnCipherLoadHdcpKey       = HI_DRV_CIPHER_LoadHdcpKey,
    .pfnCipherSoftReset         = HI_DRV_CIPHER_SoftReset,
    .pfnCipherCalcHashInit      = HI_DRV_CIPHER_CalcHashInit,
    .pfnCipherCalcHashUpdate    = HI_DRV_CIPHER_CalcHashUpdate,
    .pfnCipherCalcHashFinal     = HI_DRV_CIPHER_CalcHashFinal,
    .pfnCipherResume            = HI_DRV_CIPHER_Resume,
    .pfnCipherSuspend           = HI_DRV_CIPHER_Suspend,
    .pfnCipherSetHdmiReadClk    = HI_DRV_CIPHER_SetHdmiReadClk,
};

typedef struct hiCIPHER_IV_VALUE_S
{
    HI_U32    u32PhyAddr;
    HI_U32   *pu32VirAddr;
    //HI_U8   au8IVValue[CI_IV_SIZE];
} CIPHER_IV_VALUE_S;


/*
-----------------------------------------------------------
0 | input buf list Node(16Byte) | ...  * CIPHER_MAX_LIST_NUM  | = 16*CIPHER_MAX_LIST_NUM
-----------------------------------------------------------
  | output buf list Node(16Byte)| ...  * CIPHER_MAX_LIST_NUM  |
-----------------------------------------------------------
  | IV (16Byte)                 | ...  * CIPHER_MAX_LIST_NUM  |
-----------------------------------------------------------
... * 7 Channels


*/

typedef struct hiCIPHER_PKGN_MNG_S
{
    HI_U32              u32TotalPkg;  /*  */
    HI_U32              u32CurrentPtr;
    HI_U32              u32BusyCnt;
    HI_U32              u32FreeCnt;
} CIPHER_PKGN_MNG_S;

typedef struct hiCIPHER_PKG1_MNG_S
{
    HI_U32              au32Data[4];
} CIPHER_PKG1_MNG_S;

typedef union hiCIPHER_DATA_MNG_U
{
    CIPHER_PKGN_MNG_S  stPkgNMng;
    CIPHER_PKG1_MNG_S  stPkg1Mng;
}CIPHER_DATA_MNG_U;

typedef struct hiCIPHER_CHAN_S
{
    HI_U32                  chnId;
    CI_BUF_LIST_ENTRY_S     *pstInBuf;
    CI_BUF_LIST_ENTRY_S     *pstOutBuf;
    CIPHER_IV_VALUE_S       astCipherIVValue[CIPHER_MAX_LIST_NUM]; /*  */
    HI_U32                  au32WitchSoftChn[CIPHER_MAX_LIST_NUM];
    HI_U32                  au32CallBackArg[CIPHER_MAX_LIST_NUM];
    HI_BOOL                 bNeedCallback[CIPHER_MAX_LIST_NUM];
    CIPHER_DATA_MNG_U       unInData;
    CIPHER_DATA_MNG_U       unOutData;
} CIPHER_CHAN_S;

typedef struct hiCIPHER_SOFTCHAN_S
{
    HI_BOOL               bOpen;
    HI_U32                u32HardWareChn;

    HI_UNF_CIPHER_CTRL_S  stCtrl;

    HI_BOOL               bIVChange;
    HI_BOOL               bKeyChange;
    HI_U32                u32LastPkg;     /* save which pkg's IV we should use for next pkg */
    HI_BOOL               bDecrypt;       /* hi_false: encrypt */

    HI_U32                u32PrivateData;
    funcCipherCallback    pfnCallBack;

} CIPHER_SOFTCHAN_S;

/********************** Global Variable declaration **************************/
extern HI_U32 g_u32CipherStartCase;


typedef struct hiCIPHER_COMM_S
{
    MMZ_BUFFER_S        stPhyBuf;
} CIPHER_COMM_S;
extern HI_U32 g_u32CipherEndCase;

typedef struct hiCIPHER_OSR_CHN_S
{
    HI_BOOL g_bSoftChnOpen;                 /* mark soft channel open or not*/
    HI_BOOL g_bDataDone;                    /* mark the data done or not */
    wait_queue_head_t cipher_wait_queue;    /* mutex method */
    struct file *pWichFile;                 /* which file need to operate */

    HI_UNF_CIPHER_DATA_S *pstDataPkg;
    HI_U32                u32DataPkgNum;
}CIPHER_OSR_CHN_S;

static CIPHER_COMM_S g_stCipherComm;
static CIPHER_CHAN_S g_stCipherChans[CIPHER_CHAN_NUM];
static CIPHER_SOFTCHAN_S g_stCipherSoftChans[CIPHER_SOFT_CHAN_NUM];
static CIPHER_OSR_CHN_S g_stCipherOsrChn[CIPHER_SOFT_CHAN_NUM];

#define P32 0xEDB88320L
static HI_S32 crc_tab32_init = 0;
static HI_U32 crc_tab32[256];

ADVCA_EXPORT_FUNC_S *s_pAdvcaFunc = HI_NULL;

#define CIPHER_CheckHandle(ChanId)   \
    do \
    { \
        if (ChanId >= CIPHER_SOFT_CHAN_NUM) \
        { \
            HI_ERR_CIPHER("chan %d is too large, max: %d\n", ChanId, CIPHER_SOFT_CHAN_NUM); \
            up(&g_CipherMutexKernel);	\
            return HI_ERR_CIPHER_INVALID_PARA; \
        } \
        if (HI_FALSE == g_stCipherOsrChn[ChanId].g_bSoftChnOpen) \
        { \
            HI_ERR_CIPHER("chan %d is not open\n", ChanId); \
            up(&g_CipherMutexKernel);	\
            return HI_ERR_CIPHER_INVALID_HANDLE; \
        } \
    } while (0)

static HI_VOID init_crc32_tab( HI_VOID )
{
    HI_U32 i,j;
    HI_U32 u32Crc;

    for (i=0; i<256; i++) {
        u32Crc = (HI_U32) i;
        for (j=0; j<8; j++) {
            if (u32Crc & 0x00000001L) {
                u32Crc = (u32Crc >> 1) ^ P32;
            } else {
                u32Crc = u32Crc >> 1;
            }
        }
        crc_tab32[i] = u32Crc;
    }
    crc_tab32_init = 1;
}

static HI_U32 update_crc_32(HI_U32 u32Crc, HI_CHAR s8C)
{
    HI_U32 u32Tmp, u32Long_c;

    u32Long_c = 0x000000ffL & (HI_U32) s8C;
    u32Tmp = u32Crc ^ u32Long_c;
    u32Crc = (u32Crc >> 8) ^ crc_tab32[u32Tmp & 0xff];
    return u32Crc;
}

static HI_S32 Cipher_CRC32( HI_U8* pu8Buff,HI_U32 length, HI_U32 *pu32Crc32Result)
{
    HI_U32 u32Crc32;
    HI_U32 i;
    u32Crc32 = 0xffffffffL;

    if ( (NULL == pu32Crc32Result) || (NULL == pu8Buff) )
    {
        return HI_FAILURE;
    }

    if (!crc_tab32_init) {
        init_crc32_tab();
    }
    for(i=0 ; i < length ; i++) {
        u32Crc32 = update_crc_32(u32Crc32,(char)pu8Buff[i]);
    }
    u32Crc32 ^= 0xffffffffL;

    *pu32Crc32Result = u32Crc32;

    return HI_SUCCESS;
}

HI_VOID DRV_CIPHER_UserCommCallBack(HI_U32 arg)
{
    HI_INFO_CIPHER("arg=%#x.\n", arg);

    g_stCipherOsrChn[arg].g_bDataDone = HI_TRUE;
    wake_up_interruptible(&(g_stCipherOsrChn[arg].cipher_wait_queue));

    return ;
}

static HI_S32 s_DRV_CIPHER_CreateHandleForHDCPKeyInternal(HI_HANDLE *phHandle)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i = 0;
    HI_U32 softChnId = 0;

    if( NULL == phHandle)
    {
        HI_ERR_CIPHER("Invalid params, NULL pointer!\n");
        return HI_FAILURE;
    }

    if (0 == g_stCipherOsrChn[0].g_bSoftChnOpen)
    {
        i = 0;
    }
    else
    {
        i = CIPHER_INVALID_CHN;
    }

    if (i >= CIPHER_SOFT_CHAN_NUM)
    {
        ret = HI_ERR_CIPHER_FAILED_GETHANDLE;
        HI_ERR_CIPHER("No more cipher chan left.\n");
        return HI_FAILURE;
    }
    else
    {
        g_stCipherOsrChn[i].pstDataPkg = HI_VMALLOC(HI_ID_CIPHER, sizeof(HI_UNF_CIPHER_DATA_S) * CIPHER_MAX_LIST_NUM);
        if (NULL == g_stCipherOsrChn[i].pstDataPkg)
        {
            ret = HI_ERR_CIPHER_FAILED_GETHANDLE;
            HI_ERR_CIPHER("can NOT malloc memory for cipher.\n");
            return HI_FAILURE;
        }

        softChnId = i;
        g_stCipherOsrChn[softChnId].g_bSoftChnOpen = HI_TRUE;
    }

    ret = DRV_CIPHER_OpenChn(softChnId);
    if (HI_SUCCESS != ret)
    {
        HI_VFREE(HI_ID_CIPHER, g_stCipherOsrChn[i].pstDataPkg);
        g_stCipherOsrChn[i].pstDataPkg = NULL;
        return HI_FAILURE;
    }

    *phHandle = HI_HANDLE_MAKEHANDLE(HI_ID_CIPHER, 0, softChnId);

    return HI_SUCCESS;
}

static HI_S32 s_DRV_Cipher_CryptoHdcpKey(HI_U8 *pu8Input,
                                    HI_U32 u32InputLen,
                                    HI_DRV_HDCPKEY_TYPE_E enHdcpKeyType,
                                    HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enRootKeyType,
                                    HI_U8 *pu8Output)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 softChnId = 0;
    HI_U32 u32KeyBlock = 0;
    HI_HANDLE hCipherHandle = 0xFFFFFFFF;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_DRV_CIPHER_TASK_S stCITask;
    HI_U32 i = 0;

    HI_DECLARE_MUTEX(CipherMutexKernel);

    if (NULL == pu8Input)
    {
        HI_ERR_CIPHER("Invalid param!\n");
        return HI_FAILURE;
    }

    (HI_VOID)DRV_CIPHER_SetHdcpModeEn(CIPHER_HDCP_MODE_HDCP_KEY);

    ret = s_DRV_CIPHER_CreateHandleForHDCPKeyInternal(&hCipherHandle);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("DRV_CIPHER_OpenChn failed\n");
        (HI_VOID)DRV_CIPHER_ClearHdcpConfig();
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(hCipherHandle);

    if(down_interruptible(&CipherMutexKernel))
    {
        return -ERESTARTSYS;
    }

    u32KeyBlock = u32InputLen / 16;
    for (i = 0;i < u32KeyBlock; i++)
    {
        ret = DRV_CIPHER_HdcpParamConfig(CIPHER_HDCP_MODE_HDCP_KEY, enRootKeyType, enHdcpKeyType);
        if ( HI_FAILURE == ret)
        {
            goto __EXIT_HDCP__;
        }

        memset(&CipherCtrl, 0, sizeof(CipherCtrl));
        CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
        CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
        CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
        CipherCtrl.stChangeFlags.bit1IV = (0 == i) ? 1 : 0;

        ret = DRV_CIPHER_ConfigChn(softChnId, &CipherCtrl);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("HI_DRV_CIPHER_ConfigChn failed\n");
            goto __EXIT_HDCP__;
        }

        memset(&stCITask, 0, sizeof(stCITask));
        memcpy((HI_U8 *)(stCITask.stData2Process.u32DataPkg), pu8Input + (i * 16), 16);
        stCITask.stData2Process.u32length = 16;
        stCITask.stData2Process.bDecrypt = HI_TRUE;
        stCITask.u32CallBackArg = softChnId;

        ret = DRV_CIPHER_CreatTask(softChnId, &stCITask, NULL, NULL);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("DRV_CIPHER_CreatTask call failed\n");
            goto __EXIT_HDCP__;
        }

        if ( NULL != pu8Output )
        {
            memcpy(pu8Output + ( i * 16), (HI_U8 *)(stCITask.stData2Process.u32DataPkg), 16);
        }
    }

    if (HI_DRV_HDCPKEY_RX0 == enHdcpKeyType || HI_DRV_HDCPKEY_RX1 == enHdcpKeyType)
    {
        (HI_VOID)DRV_CIPHER_SetHdcpkeyRxRead(CIPHER_HDCP_KEY_RD_RX_RAM);
    }
    else
    {
        (HI_VOID)DRV_CIPHER_SetHdcpKeyTxRead(CIPHER_HDCP_KEY_RAM_MODE_READ);
    }

__EXIT_HDCP__:
    up(&CipherMutexKernel);
    if(HI_SUCCESS != ret)
    {
        (HI_VOID)DRV_CIPHER_ClearHdcpConfig();
    }
    (HI_VOID)DRV_CIPHER_DestroyHandle(hCipherHandle);

    return ret;
}

HI_S32 DRV_CIPHER_ReadReg(HI_U32 addr, HI_U32 *pVal)
{
    if ( NULL == pVal )
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    (HI_VOID)HAL_CIPHER_ReadReg(addr, pVal);

    return HI_SUCCESS;;
}

HI_S32 DRV_CIPHER_WriteReg(HI_U32 addr, HI_U32 Val)
{
    (HI_VOID)HAL_CIPHER_WriteReg(addr, Val);
    return HI_SUCCESS;
}

HI_S32 DRV_CipherInitHardWareChn(HI_U32 chnId )
{
    HI_U32        i;
    CIPHER_CHAN_S *pChan;

    pChan = &g_stCipherChans[chnId];

    HAL_Cipher_SetInBufNum(chnId, CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetInBufCnt(chnId, 0);
//    HAL_Cipher_SetInBufEmpty(chnId, CIPHER_MAX_LIST_NUM);

    HAL_Cipher_SetOutBufNum(chnId, CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetOutBufCnt(chnId, CIPHER_MAX_LIST_NUM);
//    HAL_Cipher_SetOutBufFull(chnId, 0);

    HAL_Cipher_SetAGEThreshold(chnId, CIPHER_INT_TYPE_OUT_BUF, 0);
    HAL_Cipher_SetAGEThreshold(chnId, CIPHER_INT_TYPE_IN_BUF, 0);

    HAL_Cipher_DisableInt(chnId, CIPHER_INT_TYPE_OUT_BUF | CIPHER_INT_TYPE_IN_BUF);

    //HAL_Cipher_Config(chnId, 0);

    for (i = 0; i < CIPHER_MAX_LIST_NUM; i++)
    {
        ;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_CipherDeInitHardWareChn(HI_U32 chnId)
{
/*
    HAL_Cipher_SetInBufNum(CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetInBufCnt(0);
    HAL_Cipher_SetInBufEmpty(CIPHER_MAX_LIST_NUM);

    HAL_Cipher_SetOutBufNum(CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetOutBufCnt(CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetOutBufFull(0);
*/

    HAL_Cipher_DisableInt(chnId, CIPHER_INT_TYPE_OUT_BUF | CIPHER_INT_TYPE_IN_BUF);
    return HI_SUCCESS;
}
/*
set interrupt threshold level and enable it, and flag soft channel opened
*/
HI_S32 DRV_CIPHER_OpenChn(HI_U32 softChnId)
{
    HI_S32 ret = 0;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    pSoftChan->u32HardWareChn = softChnId;

    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];

    HAL_Cipher_SetIntThreshold(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF, CIPHER_DEFAULT_INT_NUM);
    //ret = HAL_Cipher_EnableInt(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF | CIPHER_INT_TYPE_IN_BUF);
    ret = HAL_Cipher_EnableInt(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF);

    pSoftChan->bOpen = HI_TRUE;
    return ret;
}

HI_S32 DRV_CIPHER_CloseChn(HI_U32 softChnId)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];

    pSoftChan->bOpen = HI_FALSE;

    HAL_Cipher_ClearCbcVerifyFlag(); //clear the irdeto CBC verify flag anyway
    //ret = HAL_Cipher_DisableInt(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF);
    return ret;
}

HI_S32 DRV_CIPHER_ConfigChn(HI_U32 softChnId,  HI_UNF_CIPHER_CTRL_S *pConfig)
{
    HI_S32 ret = HI_SUCCESS;
    HI_BOOL bDecrypt = HI_FALSE;
    HI_U32 hardWareChn;
    HI_BOOL bIVSet;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    CIPHER_CheckHandle(softChnId);

    pSoftChan = &g_stCipherSoftChans[softChnId];
    hardWareChn = pSoftChan->u32HardWareChn;
    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];
    pSoftChan->pfnCallBack = DRV_CIPHER_UserCommCallBack;
    bIVSet = (pConfig->stChangeFlags.bit1IV & 0x1) ? HI_TRUE : HI_FALSE;

    ret = HAL_Cipher_Config(pChan->chnId, bDecrypt, bIVSet, pConfig);

    pSoftChan->bIVChange = bIVSet;
    pSoftChan->bKeyChange = HI_TRUE;

    memcpy(&(pSoftChan->stCtrl), pConfig, sizeof(HI_UNF_CIPHER_CTRL_S));

    /* set Key */
    if (pSoftChan->bKeyChange &&  (HI_TRUE == pConfig->bKeyByCA))
    {
        /* Used for copy protection mode */
        if( 0 == hardWareChn)
        {
            ret = HAL_CIPHER_LoadSTBRootKey(0);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_CIPHER("Load STB root key failed!\n");
                return ret;
            }
        }
        else if(pConfig->enCaType == HI_UNF_CIPHER_CA_TYPE_STBROOTKEY)
        {
            ret = HAL_CIPHER_LoadSTBRootKey(hardWareChn);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_CIPHER("Load STB root key failed!\n");
                return ret;
            }
        }
        else
        {
            ret = HAL_Cipher_SetKey(hardWareChn, &(pSoftChan->stCtrl));
            if (HI_SUCCESS != ret)
            {
                return ret;
            }
        }
        pSoftChan->bKeyChange = HI_FALSE;
    }

    return ret;
}


HI_S32 HI_DRV_CIPHER_ConfigChn(HI_U32 softChnId,  HI_UNF_CIPHER_CTRL_S *pConfig)
{
    HI_S32 ret = HI_SUCCESS;

    if(down_interruptible(&g_CipherMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

	ret = DRV_CIPHER_ConfigChn(softChnId, pConfig);

	up(&g_CipherMutexKernel);

	return ret;
}

/*
*/
HI_S32 DRV_CipherStartSinglePkgChn(HI_U32 softChnId, HI_DRV_CIPHER_DATA_INFO_S *pBuf2Process)
{
    HI_U32 ret;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];

    HAL_Cipher_Config(0, pBuf2Process->bDecrypt, pSoftChan->bIVChange, &(pSoftChan->stCtrl));

#if 0
    HAL_Cipher_SetInIV(0, &(pSoftChan->stCtrl));
    HAL_Cipher_SetKey(0, &(pSoftChan->stCtrl));
#else
    pSoftChan->bIVChange = HI_FALSE;
#endif

    HAL_Cipher_SetDataSinglePkg(pBuf2Process);

    HAL_Cipher_StartSinglePkg(pChan->chnId);
    ret = HAL_Cipher_WaitIdle();
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }
    HAL_Cipher_ReadDataSinglePkg(pBuf2Process->u32DataPkg);

    return HI_SUCCESS;
}

/*
*/
HI_S32 DRV_CipherStartMultiPkgChn(HI_U32 softChnId, HI_DRV_CIPHER_DATA_INFO_S *pBuf2Process, HI_U32 callBackArg)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 hardWareChn;
    HI_U32 BusyCnt = 0;
    HI_U32 currentPtr;
    CI_BUF_LIST_ENTRY_S *pInBuf;
    CI_BUF_LIST_ENTRY_S *pOutBuf;

    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    hardWareChn = pSoftChan->u32HardWareChn;
    pChan = &g_stCipherChans[hardWareChn];

    HAL_Cipher_GetInBufCnt(hardWareChn, &BusyCnt);

    pChan->unInData.stPkgNMng.u32BusyCnt = BusyCnt;
    currentPtr = pChan->unInData.stPkgNMng.u32CurrentPtr;

    pInBuf = pChan->pstInBuf + currentPtr;
    pOutBuf = pChan->pstOutBuf + currentPtr;

    if (BusyCnt < CIPHER_MAX_LIST_NUM) /* */
    {
        /* set addr */
        pInBuf->u32DataAddr = pBuf2Process->u32src;
        pInBuf->U32DataLen = pBuf2Process->u32length;

        pOutBuf->u32DataAddr = pBuf2Process->u32dest;
        pOutBuf->U32DataLen = pBuf2Process->u32length;

        /* set IV */
        if (pSoftChan->bIVChange)
        {
            memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr, pSoftChan->stCtrl.u32IV, CI_IV_SIZE);
            mb();
            pInBuf->u32IVStartAddr = pChan->astCipherIVValue[currentPtr].u32PhyAddr;

            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_IVSET_BIT);
        }
        else
        {
#if 1       /* for 1 pkg task,  save IV for next pkg unless user config the handle again */
            pInBuf->u32Flags &= ~(1 << CI_BUF_LIST_FLAG_IVSET_BIT);
#else
            memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
                pChan->astCipherIVValue[pSoftChan->u32LastPkg].pu32VirAddr, CI_IV_SIZE);

            pInBuf->u32IVStartAddr
                = pChan->astCipherIVValue[currentPtr].u32PhyAddr;

            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_IVSET_BIT);
#endif
        }

        /* set Key */
        if (pSoftChan->bKeyChange)
        {
            ret = HAL_Cipher_SetKey(hardWareChn, &(pSoftChan->stCtrl));
            if (HI_SUCCESS != ret)
            {
                return ret;
            }

            pSoftChan->bKeyChange = HI_FALSE;
        }
        else
        {
            ;
        }

        /* just set each node to End_of_list <--- changed by q46153, 20111108, no need,  we think the task is NOT over */
        //pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_EOL_BIT);
        //pOutBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_EOL_BIT);

        //ret = HAL_Cipher_Config(hardWareChn, pSoftChan->bDecrypt, pSoftChan->bIVChange, &(pSoftChan->stCtrl));
        ret = HAL_Cipher_Config(hardWareChn, pBuf2Process->bDecrypt, pSoftChan->bIVChange, &(pSoftChan->stCtrl));
        pSoftChan->bIVChange = HI_FALSE;

        pChan->au32WitchSoftChn[currentPtr] = softChnId;
        pChan->au32CallBackArg[currentPtr] = callBackArg;
        pSoftChan->u32PrivateData = callBackArg;
        pChan->bNeedCallback[currentPtr] = HI_TRUE;
        HI_INFO_CIPHER("pkg %d set ok.\n", currentPtr);

        currentPtr++;
        if (currentPtr >=  CIPHER_MAX_LIST_NUM)
        {
            currentPtr = 0;
        }

        /* save list Node */
        pChan->unInData.stPkgNMng.u32CurrentPtr = currentPtr;
        pChan->unInData.stPkgNMng.u32TotalPkg++;
        pChan->unOutData.stPkgNMng.u32TotalPkg++;

        HAL_Cipher_GetOutBufCnt(hardWareChn, &BusyCnt);
        HI_INFO_CIPHER("%s %#x->%#x, LEN:%#x\n", pBuf2Process->bDecrypt ? "Dec" : "ENC",
                pBuf2Process->u32src, pBuf2Process->u32dest,
                pBuf2Process->u32length );
        HAL_Cipher_SetInBufCnt(hardWareChn, 1); /* +1 */

    }
    else
    {
        return HI_FAILURE;
    }

    return ret;
}


HI_S32 DRV_CIPHER_CreatMultiPkgTask(HI_U32 softChnId, HI_DRV_CIPHER_DATA_INFO_S *pBuf2Process, HI_U32 pkgNum, HI_U32 callBackArg)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 hardWareChn;
    HI_U32 BusyCnt = 0, i;
    HI_U32 currentPtr;
    CI_BUF_LIST_ENTRY_S *pInBuf;
    CI_BUF_LIST_ENTRY_S *pOutBuf;

    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;
    HI_DRV_CIPHER_DATA_INFO_S *pTmpDataPkg = pBuf2Process;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    hardWareChn = pSoftChan->u32HardWareChn;
    pChan = &g_stCipherChans[hardWareChn];

    HAL_Cipher_GetInBufCnt(hardWareChn, &BusyCnt);
    HI_DEBUG_CIPHER("HAL_Cipher_GetInBufCnt, BusyCnt=%d.\n", BusyCnt);

    pChan->unInData.stPkgNMng.u32BusyCnt = BusyCnt;

    if (BusyCnt + pkgNum > CIPHER_MAX_LIST_NUM) /* */
    {
         HI_ERR_CIPHER("%s: pkg want to do: %u, free pkg num:%u.\n", pBuf2Process->bDecrypt ? "Dec" : "ENC",
                pkgNum, CIPHER_MAX_LIST_NUM - BusyCnt);
         return HI_ERR_CIPHER_BUSY;
    }


    /* set Key */
    if (pSoftChan->bKeyChange)
    {
        ret = HAL_Cipher_SetKey(hardWareChn, &(pSoftChan->stCtrl));
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
        pSoftChan->bKeyChange = HI_FALSE;
    }
    else
    {
        ;
    }


    currentPtr = pChan->unInData.stPkgNMng.u32CurrentPtr;

    for (i = 0; i < pkgNum; i++)
    {
        pTmpDataPkg = pBuf2Process + i;
        pInBuf = pChan->pstInBuf + currentPtr;
        pOutBuf = pChan->pstOutBuf + currentPtr;


        /* set addr */
        pInBuf->u32DataAddr = pTmpDataPkg->u32src;
        pInBuf->U32DataLen = pTmpDataPkg->u32length;

        pOutBuf->u32DataAddr = pTmpDataPkg->u32dest;
        pOutBuf->U32DataLen = pTmpDataPkg->u32length;

        /* set IV */
        if (pSoftChan->bIVChange)
        {
            memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
                pSoftChan->stCtrl.u32IV, CI_IV_SIZE);
            mb();
            pInBuf->u32IVStartAddr
                = pChan->astCipherIVValue[currentPtr].u32PhyAddr;

            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_IVSET_BIT);
        }
        else
        {
#if 0
            pInBuf->u32Flags &= ~(1 << CI_BUF_LIST_FLAG_IVSET_BIT);
#else  /* for multi pkg task, reset IV(use the user configed IV ) each time. */
            memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
                pSoftChan->stCtrl.u32IV, CI_IV_SIZE);
            mb();
            pInBuf->u32IVStartAddr = pChan->astCipherIVValue[currentPtr].u32PhyAddr;

            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_IVSET_BIT);
#endif

        }


        pChan->au32WitchSoftChn[currentPtr] = softChnId;
        pChan->au32CallBackArg[currentPtr] = callBackArg;
        pSoftChan->u32PrivateData = callBackArg;
        if ((i + 1) == pkgNum)
        {
            pChan->bNeedCallback[currentPtr] = HI_TRUE ;

            /* just set each node to End_of_list, <--- changed by q46153, 20111108, only the last pkg need this. */
            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_EOL_BIT);
            pOutBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_EOL_BIT);
        }
        else
        {
            pChan->bNeedCallback[currentPtr] = HI_FALSE ;
        }


        currentPtr++;
        if (currentPtr >=  CIPHER_MAX_LIST_NUM)
        {
            currentPtr = 0;
        }

        /* save list Node */
        pChan->unInData.stPkgNMng.u32CurrentPtr = currentPtr;
        pChan->unInData.stPkgNMng.u32TotalPkg++;
        pChan->unOutData.stPkgNMng.u32TotalPkg++;
    }


    ret = HAL_Cipher_Config(hardWareChn, pTmpDataPkg->bDecrypt,
                            pSoftChan->bIVChange, &(pSoftChan->stCtrl));
    pSoftChan->bIVChange = HI_FALSE;

    HAL_Cipher_SetIntThreshold(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF, pkgNum);

    HAL_Cipher_GetOutBufCnt(hardWareChn, &BusyCnt);
    HAL_Cipher_SetInBufCnt(hardWareChn, pkgNum); /* commit task */
    HI_INFO_CIPHER("%s: pkg:%#x.\n", pTmpDataPkg->bDecrypt ? "Dec" : "ENC",   pkgNum);
    return HI_SUCCESS;
}

/*
*/
HI_S32 DRV_CIPHER_CreatTask(HI_U32 softChnId, HI_DRV_CIPHER_TASK_S *pTask, HI_U32 *pKey, HI_U32 *pIV)
{
    HI_S32 ret;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];

    if (pKey)
    {
        pSoftChan->bKeyChange = HI_TRUE;
        memcpy(pSoftChan->stCtrl.u32Key, pKey, CI_KEY_SIZE);
    }

    if (pIV)
    {
        pSoftChan->bIVChange = HI_TRUE;
        memcpy(pSoftChan->stCtrl.u32IV, pIV, CI_IV_SIZE);
    }

    HAL_Cipher_SetIntThreshold(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF, 1);

    if (CIPHER_PKGx1_CHAN == pSoftChan->u32HardWareChn)
    {
        ret = DRV_CipherStartSinglePkgChn(softChnId, &(pTask->stData2Process));
    }
    else
    {
        ret = DRV_CipherStartMultiPkgChn(softChnId, &(pTask->stData2Process), pTask->u32CallBackArg);
    }

    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("can't create task, ERR=%#x.\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_CipherDataDoneSinglePkg(HI_U32 chnId)
{
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pChan = &g_stCipherChans[chnId];
    HI_DEBUG_CIPHER("Data DONE, hwChn:%d\n", chnId);
    pSoftChan = &g_stCipherSoftChans[chnId];

    if (pSoftChan->pfnCallBack)
    {
        pSoftChan->pfnCallBack(pSoftChan->u32PrivateData);
    }
    return HI_SUCCESS;
}

HI_S32 DRV_CipherDataDoneMultiPkg(HI_U32 chnId)
{
    HI_S32 ret;
    HI_U32 currentPtr = 0;
    HI_U32 softChnId = 0;
    HI_U32 fullCnt = 0;
    HI_U32 i, idx = 0;
    CIPHER_CHAN_S *pChan = NULL;
    CIPHER_SOFTCHAN_S *pSoftChan = NULL;
    CI_BUF_LIST_ENTRY_S *pInBuf = NULL;
    CI_BUF_LIST_ENTRY_S *pOutBuf = NULL;

    pChan = &g_stCipherChans[chnId];
    HI_DEBUG_CIPHER("Data DONE, hwChn:%d\n", chnId);

    currentPtr = pChan->unOutData.stPkgNMng.u32CurrentPtr;

    HI_DEBUG_CIPHER("Data DONE, hwChn:%u, currentPtr=%u\n", chnId, currentPtr);

    /* get the finished output data buffer count */
    ret = HAL_Cipher_GetOutBufFull(chnId, &fullCnt);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }
    idx = currentPtr;

    if(idx >= CIPHER_MAX_LIST_NUM)
    {
        HI_ERR_CIPHER("idx error: idx=%u, chnId=%d \n", idx, chnId);
        return HI_FAILURE;
    }

    if (fullCnt > 0) /* have list entry */
    {
        for (i = 0; i < fullCnt; i++)
        {
//            idx = currentPtr;

            softChnId = pChan->au32WitchSoftChn[idx];
            pChan->au32WitchSoftChn[idx] = CIPHER_INVALID_CHN;

            pSoftChan = &g_stCipherSoftChans[softChnId];
            pSoftChan->u32LastPkg = idx;
            HI_DEBUG_CIPHER("softChnId=%d, idx=%u, needCallback:%d\n", softChnId, idx, pChan->bNeedCallback[idx]);
            if (pSoftChan->pfnCallBack && pChan->bNeedCallback[idx])
            {
                HI_DEBUG_CIPHER("CallBack function\n");
                pSoftChan->pfnCallBack(pSoftChan->u32PrivateData);
            }

            pInBuf = pChan->pstInBuf + idx;  /* reset the flag of each pkg */
            pInBuf->u32Flags = 0;

            pOutBuf = pChan->pstOutBuf + idx; /* reset the flag of each pkg */
            pOutBuf->u32Flags = 0;

            idx++;
            if (idx >= CIPHER_MAX_LIST_NUM)
            {
                idx = 0;
            }
        }

        pChan->unOutData.stPkgNMng.u32CurrentPtr = idx;
        HAL_Cipher_SetInBufEmpty(chnId, fullCnt);  /* -  */
        HAL_Cipher_SetOutBufFull(chnId, fullCnt);  /* -  */
        HAL_Cipher_SetOutBufCnt(chnId, fullCnt);   /* +  */
    }
    else
    {
        HI_U32 regValue = 0xabcd;

        HI_ERR_CIPHER("Data done, but fullCnt=0, chn%d\n", chnId);

        HAL_Cipher_GetIntState(&regValue);
        HI_ERR_CIPHER("INTSt:%#x\n", regValue);

        HAL_Cipher_GetIntEnState(&regValue);
        HI_ERR_CIPHER("INTEnSt:%#x\n", regValue);

        HAL_Cipher_GetRawIntState(&regValue);
        HI_ERR_CIPHER("INTRawSt:%#x\n", regValue);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/* interrupt routine, callback */
irqreturn_t DRV_Cipher_ISR(HI_S32 irq, HI_VOID *devId)
{
    HI_U32 i;
    HI_U32 INTValue = 0;

    HAL_Cipher_GetIntState(&INTValue);
    HAL_Cipher_ClrIntState(INTValue);

    HI_DEBUG_CIPHER(" in the isr INTValue=%#x!\n", INTValue);

    if (INTValue >> 8 & 0x1) /* single pkg */
    {
        DRV_CipherDataDoneSinglePkg(0);
    }

    for(i = 1; i < CIPHER_CHAN_NUM; i++)
    {
        if ((INTValue >> (i+8)) & 0x1)
        {
            DRV_CipherDataDoneMultiPkg(i);
        }
    }
//    HAL_Cipher_ClrIntState();
    return IRQ_HANDLED;
}


HI_S32 DRV_CIPHER_Init(HI_VOID)
{
    HI_U32 i,j, hwChnId;
    HI_S32 ret;
    HI_U32 bufSizeChn = 0; /* all the buffer list size, included data buffer size and IV buffer size */
    HI_U32 databufSizeChn = 0; /* max list number data buffer size */
    HI_U32 ivbufSizeChn = 0; /* all the list IV size */
    HI_U32 bufSizeTotal = 0; /* all the channel buffer size */
    MMZ_BUFFER_S   cipherListBuf;
    CIPHER_CHAN_S *pChan;

    memset(&g_stCipherComm, 0, sizeof(g_stCipherComm));
    memset(&g_stCipherChans, 0, sizeof(g_stCipherChans));
    memset(&g_stCipherSoftChans, 0, sizeof(g_stCipherSoftChans));

    for (i = 0; i < CIPHER_SOFT_CHAN_NUM; i++)
    {
        g_stCipherOsrChn[i].g_bSoftChnOpen = HI_FALSE;
        g_stCipherOsrChn[i].g_bDataDone = HI_FALSE;
        g_stCipherOsrChn[i].pWichFile = NULL;
        init_waitqueue_head(&(g_stCipherOsrChn[i].cipher_wait_queue));
        g_stCipherOsrChn[i].pstDataPkg = NULL;
    }

/*
==========================channel-1=============================
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |inBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |outBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |keyBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
=============================================================
...
...
...
==========================channel-7=============================
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |inBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |outBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |keyBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
=============================================================
*/

    databufSizeChn = sizeof(CI_BUF_LIST_ENTRY_S) * CIPHER_MAX_LIST_NUM;
    ivbufSizeChn = CI_IV_SIZE * CIPHER_MAX_LIST_NUM;
    bufSizeChn = (databufSizeChn * 2) + ivbufSizeChn;/* inBuf + outBuf + keyBuf */
    bufSizeTotal = bufSizeChn * (CIPHER_PKGxN_CHAN_MAX - CIPHER_PKGxN_CHAN_MIN + 1) ; /* only 7 channels need buf */

    HAL_Cipher_Init();
    HAL_Cipher_DisableAllInt();

    /* allocate 7 channels size */
    ret = HI_DRV_MMZ_AllocAndMap("CIPHER_ChnBuf",NULL, bufSizeTotal, 0, &(cipherListBuf));
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Can NOT get mem for cipher, init failed, exit...\n");
        return HI_FAILURE;
    }
    else
    {
        memset((void*)(cipherListBuf.u32StartVirAddr), 0, cipherListBuf.u32Size);

        /* save the whole memory info, included physical address, virtual address and their size */
        memcpy(&(g_stCipherComm.stPhyBuf), &(cipherListBuf), sizeof(g_stCipherComm.stPhyBuf));
    }

    HI_DEBUG_CIPHER("TOTAL BUF: %#x/%#x", cipherListBuf.u32StartPhyAddr, cipherListBuf.u32StartVirAddr);

    /* assign hardware channel ID from 0 to 7 */
    for (i = 0; i <= CIPHER_PKGxN_CHAN_MAX; i++)
    {
        pChan = &g_stCipherChans[i];
        pChan->chnId = i;
    }

/*
channel layout
==============================================================
|
|
==============================================================
/\                                     /\                                      /\
 |              IV buf                  |             IN buf                    |             OUT buf
startPhyAddr
==============================================================
|
|
==============================================================
/\                                     /\                                      /\
 |              IV buf                  |             IN buf                    |             OUT buf
 startVirAddr
*/
    for (i = 0; i < CIPHER_PKGxN_CHAN_MAX; i++)
    {
        /* config channel from 1 to 7 */
        hwChnId = i+CIPHER_PKGxN_CHAN_MIN;
        pChan = &g_stCipherChans[hwChnId];

        pChan->astCipherIVValue[0].u32PhyAddr = cipherListBuf.u32StartPhyAddr + (i * bufSizeChn);
        pChan->astCipherIVValue[0].pu32VirAddr = (HI_U32 *)(cipherListBuf.u32StartVirAddr + (i * bufSizeChn));

        for (j = 1; j < CIPHER_MAX_LIST_NUM; j++)
        {
            pChan->astCipherIVValue[j].u32PhyAddr = pChan->astCipherIVValue[0].u32PhyAddr + (CI_IV_SIZE * j);
            pChan->astCipherIVValue[j].pu32VirAddr = (HI_U32*)(((HI_U32)pChan->astCipherIVValue[0].pu32VirAddr) + (CI_IV_SIZE * j));

            pChan->bNeedCallback[j] = HI_FALSE;
        }

        pChan->pstInBuf = (CI_BUF_LIST_ENTRY_S*)((HI_U32)(pChan->astCipherIVValue[0].pu32VirAddr) + ivbufSizeChn);
        pChan->pstOutBuf = (CI_BUF_LIST_ENTRY_S*)((HI_U32)(pChan->pstInBuf) + databufSizeChn);

        HAL_Cipher_SetBufAddr(hwChnId, CIPHER_BUF_TYPE_IN, pChan->astCipherIVValue[0].u32PhyAddr + ivbufSizeChn);
        HAL_Cipher_SetBufAddr(hwChnId, CIPHER_BUF_TYPE_OUT, pChan->astCipherIVValue[0].u32PhyAddr + ivbufSizeChn + databufSizeChn);

        DRV_CipherInitHardWareChn(hwChnId);


    }

    /* debug info */
    for (i = 0; i < CIPHER_PKGxN_CHAN_MAX; i++)
    {
        hwChnId = i+CIPHER_PKGxN_CHAN_MIN;
        pChan = &g_stCipherChans[hwChnId];

        HI_INFO_CIPHER("Chn%02x, IV:%#x/%p In:%#x/%p, Out:%#x/%p.\n", i,
            pChan->astCipherIVValue[0].u32PhyAddr,
            pChan->astCipherIVValue[0].pu32VirAddr,
            pChan->astCipherIVValue[0].u32PhyAddr + ivbufSizeChn, pChan->pstInBuf,
            pChan->astCipherIVValue[0].u32PhyAddr + ivbufSizeChn + databufSizeChn, pChan->pstOutBuf );
    }

    HAL_Cipher_ClrIntState(0xffffffff);

    /* request irq */
    ret = request_irq(CIPHER_IRQ_NUMBER, DRV_Cipher_ISR, IRQF_DISABLED, "hi_cipher_irq", &g_stCipherComm);
    if(HI_SUCCESS != ret)
    {
        HAL_Cipher_DisableAllInt();
        HAL_Cipher_ClrIntState(0xffffffff);

        HI_ERR_CIPHER("Irq request failure, ret=%#x.", ret);
        HI_DRV_MMZ_UnmapAndRelease(&(g_stCipherComm.stPhyBuf));
        return HI_FAILURE;
    }

#if    defined(CHIP_TYPE_hi3719mv100)   \
    || defined(CHIP_TYPE_hi3718mv100)   \
    || defined(CHIP_TYPE_hi3751v100)    \
    || defined(CHIP_TYPE_hi3751v100b)   \
    || defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
	|| defined (CHIP_TYPE_hi3798cv200_a)
	
    HAL_Cipher_EnableAllSecChn();
#endif
    return HI_SUCCESS;
}

HI_VOID DRV_CIPHER_DeInit(HI_VOID)
{
    HI_U32 i, hwChnId;

    HAL_Cipher_DisableAllInt();
    HAL_Cipher_ClrIntState(0xffffffff);

    for (i = 0; i < CIPHER_PKGxN_CHAN_MAX; i++)
    {
        hwChnId = i+CIPHER_PKGxN_CHAN_MIN;
        DRV_CipherDeInitHardWareChn(hwChnId);
    }

    /* free irq */
    free_irq(CIPHER_IRQ_NUMBER, &g_stCipherComm);

    HI_DRV_MMZ_UnmapAndRelease(&(g_stCipherComm.stPhyBuf));

    HAL_Cipher_DeInit();

    return;
}

HI_VOID HI_DRV_CIPHER_Suspend(HI_VOID)
{
    DRV_CIPHER_DeInit();

    return;
}

HI_S32 HI_DRV_CIPHER_Resume(HI_VOID)
{
    HI_U32 i, j, hwChnId;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 bufSizeChn = 0;      /* all the buffer list size, included data buffer size and IV buffer size */
    HI_U32 databufSizeChn = 0;  /* max list number data buffer size */
    HI_U32 ivbufSizeChn = 0;    /* all the list IV size */
    HI_U32 bufSizeTotal = 0;    /* all the channel buffer size */
    MMZ_BUFFER_S   cipherListBuf;
    CIPHER_CHAN_S *pChan;

    memset(&g_stCipherComm, 0, sizeof(g_stCipherComm));
    memset(&g_stCipherChans, 0, sizeof(g_stCipherChans));

    databufSizeChn = sizeof(CI_BUF_LIST_ENTRY_S) * CIPHER_MAX_LIST_NUM;
    ivbufSizeChn = CI_IV_SIZE * CIPHER_MAX_LIST_NUM;
    bufSizeChn = (databufSizeChn * 2) + ivbufSizeChn;/* inBuf + outBuf + keyBuf */
    bufSizeTotal = bufSizeChn * (CIPHER_PKGxN_CHAN_MAX - CIPHER_PKGxN_CHAN_MIN + 1) ; /* only 7 channels need buf */

    HAL_Cipher_Init();
    HAL_Cipher_HashSoftReset();
    HAL_Cipher_DisableAllInt();

    /* allocate 7 channels size */
    ret = HI_DRV_MMZ_AllocAndMap("CIPHER_ChnBuf", NULL, bufSizeTotal, 0, &(cipherListBuf));
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Can NOT get mem for cipher, init failed, exit...\n");
        return ret;
    }
    else
    {
        memset((void*)(cipherListBuf.u32StartVirAddr), 0, cipherListBuf.u32Size);

        /* save the whole memory info, included physical address, virtual address and their size */
        memcpy(&(g_stCipherComm.stPhyBuf), &(cipherListBuf), sizeof(g_stCipherComm.stPhyBuf));
    }

    /* assign hardware channel ID from 0 to 7 */
    for (i = 0; i <= CIPHER_PKGxN_CHAN_MAX; i++)
    {
        pChan = &g_stCipherChans[i];
        pChan->chnId = i;
    }

    for (i = 0; i < CIPHER_PKGxN_CHAN_MAX; i++)
    {
        /* config channel from 1 to 7 */
        hwChnId = i + CIPHER_PKGxN_CHAN_MIN;
        pChan = &g_stCipherChans[hwChnId];

        pChan->astCipherIVValue[0].u32PhyAddr
            = cipherListBuf.u32StartPhyAddr + (i * bufSizeChn);
        pChan->astCipherIVValue[0].pu32VirAddr
            = (HI_U32*)(cipherListBuf.u32StartVirAddr + (i * bufSizeChn));

        for (j = 1; j < CIPHER_MAX_LIST_NUM; j++)
        {
            pChan->astCipherIVValue[j].u32PhyAddr
                = pChan->astCipherIVValue[0].u32PhyAddr + (CI_IV_SIZE * j);
            pChan->astCipherIVValue[j].pu32VirAddr
                = (HI_U32*)(((HI_U32)pChan->astCipherIVValue[0].pu32VirAddr) + (CI_IV_SIZE * j));

            pChan->bNeedCallback[j] = HI_FALSE;
        }

        pChan->pstInBuf = (CI_BUF_LIST_ENTRY_S*)((HI_U32)(pChan->astCipherIVValue[0].pu32VirAddr) + ivbufSizeChn);
        pChan->pstOutBuf = (CI_BUF_LIST_ENTRY_S*)((HI_U32)(pChan->pstInBuf) + databufSizeChn);

        HAL_Cipher_SetBufAddr(hwChnId, CIPHER_BUF_TYPE_IN,
            pChan->astCipherIVValue[0].u32PhyAddr + ivbufSizeChn);
        HAL_Cipher_SetBufAddr(hwChnId, CIPHER_BUF_TYPE_OUT,
            pChan->astCipherIVValue[0].u32PhyAddr + ivbufSizeChn + databufSizeChn);

        DRV_CipherInitHardWareChn(hwChnId);
    }

    HAL_Cipher_ClrIntState(0xffffffff);

    /* request irq */
    ret = request_irq(CIPHER_IRQ_NUMBER, DRV_Cipher_ISR, IRQF_DISABLED, "hi_cipher_irq", &g_stCipherComm);
    if(HI_SUCCESS != ret)
    {
        HAL_Cipher_DisableAllInt();
        HAL_Cipher_ClrIntState(0xffffffff);

        HI_ERR_CIPHER("Irq request failure, ret=%#x.", ret);
        HI_DRV_MMZ_UnmapAndRelease(&(g_stCipherComm.stPhyBuf));
        return ret;
    }

    for(i = 0; i < CIPHER_CHAN_NUM; i++)
    {
        if (g_stCipherSoftChans[i].bOpen)
        {
            DRV_CIPHER_OpenChn(i);
            DRV_CIPHER_ConfigChn(i, &g_stCipherSoftChans[i].stCtrl);
        }
    }

#if    defined(CHIP_TYPE_hi3719mv100)   \
    || defined(CHIP_TYPE_hi3718mv100)   \
    || defined(CHIP_TYPE_hi3751v100)    \
    || defined(CHIP_TYPE_hi3751v100b)   \
    || defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
	|| defined(CHIP_TYPE_hi3798cv200_a)
    HAL_Cipher_EnableAllSecChn();
#endif

	if(HI_TRUE == g_bHDCPKeyLoadFlag)
	{
		ret = DRV_CIPHER_LoadHdcpKey(&g_stFlashHdcpKey);
		if(HI_SUCCESS != ret)
		{
			HI_ERR_CIPHER("Load hdcp key failed!\n");
		}
		else
		{
			HI_INFO_CIPHER("Load hdcp key success!\n");
			//g_bHDCPKeyLoadFlag = HI_FALSE;
		}
	}

    return HI_SUCCESS;
}

HI_VOID HI_DRV_CIPHER_SetHdmiReadClk(HI_DRV_HDCPKEY_TYPE_E enHDCPKeyType)
{
    switch(enHDCPKeyType)
    {
    case HI_DRV_HDCPKEY_TX0:
    case HI_DRV_HDCPKEY_TX1:  
        DRV_CIPHER_SetHdcpKeyTxRead(CIPHER_HDCP_KEY_RAM_MODE_READ);
        break;
     case HI_DRV_HDCPKEY_RX0:
     case HI_DRV_HDCPKEY_RX1:
        DRV_CIPHER_SetHdcpkeyRxRead(CIPHER_HDCP_KEY_RAM_MODE_READ);
        break;
    default:
        HI_ERR_CIPHER("Set Hdmi Read Clk failed! unknow key type: 0x%x\n", enHDCPKeyType);
        break;
    }
}

HI_S32 HI_DRV_CIPHER_GetHandleConfig(CIPHER_Config_CTRL *pstCipherConfig)
{
    CIPHER_SOFTCHAN_S *pSoftChan = NULL;
    HI_U32 u32SoftChanId = 0;

    if(pstCipherConfig == NULL)
    {
        HI_ERR_CIPHER("Error! NULL pointer!\n");
        return HI_FAILURE;
    }

    if(down_interruptible(&g_CipherMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    u32SoftChanId = HI_HANDLE_GET_CHNID(pstCipherConfig->CIHandle);
    CIPHER_CheckHandle(u32SoftChanId);

    pSoftChan = &g_stCipherSoftChans[u32SoftChanId];
    memcpy(&pstCipherConfig->CIpstCtrl, &(pSoftChan->stCtrl), sizeof(HI_UNF_CIPHER_CTRL_S));

	up(&g_CipherMutexKernel);
    return HI_SUCCESS;
}

HI_S32 DRV_CIPHER_CreateHandle(CIPHER_HANDLE_S *pstCIHandle)
{
	HI_S32 ret = HI_SUCCESS;
	HI_U32 i = 0;
	HI_HANDLE hCipherchn = 0;
	HI_U32 softChnId = 0;

	if ( NULL == pstCIHandle)
	{
	    HI_ERR_CIPHER("Invalid params!\n");
	    return HI_FAILURE;
	}

	if ( HI_UNF_CIPHER_TYPE_NORMAL != pstCIHandle->stCipherAtts.enCipherType )
	{
	    if(HI_UNF_CIPHER_TYPE_BUTT <= pstCIHandle->stCipherAtts.enCipherType)
	    {
	        HI_ERR_CIPHER("Invalid cipher type!\n");
	        return HI_FAILURE;
	    }
	    if (0 == g_stCipherOsrChn[0].g_bSoftChnOpen)
	    {
	        i = 0;
	        if (HI_UNF_CIPHER_TYPE_COPY_AVOID == pstCIHandle->stCipherAtts.enCipherType)
	        {
	            (HI_VOID)DRV_CIPHER_SetHdcpModeEn(CIPHER_HDCP_MODE_NO_HDCP_KEY);
	        }
	    }
	    else
	    {
	        i = CIPHER_INVALID_CHN;
	    }
	}
	else
	{
	    for(i = CIPHER_PKGxN_CHAN_MIN; i < CIPHER_SOFT_CHAN_NUM; i++)
	    {
	        if (0 == g_stCipherOsrChn[i].g_bSoftChnOpen)
	        {
	            break;
	        }
	    }
	}

	if (i >= CIPHER_SOFT_CHAN_NUM)
	{
	    ret = HI_ERR_CIPHER_FAILED_GETHANDLE;
	    HI_ERR_CIPHER("No more cipher chan left.\n");
	    return HI_FAILURE;
	}
	else
	{
	    g_stCipherOsrChn[i].pstDataPkg = HI_VMALLOC(HI_ID_CIPHER, sizeof(HI_UNF_CIPHER_DATA_S) * CIPHER_MAX_LIST_NUM);
	    if (NULL == g_stCipherOsrChn[i].pstDataPkg)
	    {
	        ret = HI_ERR_CIPHER_FAILED_GETHANDLE;
	        HI_ERR_CIPHER("can NOT malloc memory for cipher.\n");
	        return HI_FAILURE;
	    }

	    softChnId = i;
	    g_stCipherOsrChn[softChnId].g_bSoftChnOpen = HI_TRUE;
	}

	hCipherchn = HI_HANDLE_MAKEHANDLE(HI_ID_CIPHER, 0, softChnId);

	ret = DRV_CIPHER_OpenChn(softChnId);
	if (HI_SUCCESS != ret)
	{
	    HI_VFREE(HI_ID_CIPHER, g_stCipherOsrChn[i].pstDataPkg);
	    g_stCipherOsrChn[i].pstDataPkg = NULL;
	    return HI_FAILURE;
	}

	pstCIHandle->hCIHandle = hCipherchn;

	return HI_SUCCESS;
}

HI_S32 HI_DRV_CIPHER_CreateHandle(CIPHER_HANDLE_S *pstCIHandle)
{
	HI_S32 ret = HI_SUCCESS;

	if(down_interruptible(&g_CipherMutexKernel))
	{
		HI_ERR_CIPHER("down_interruptible failed!\n");
	    return HI_FAILURE;
	}

	ret = DRV_CIPHER_CreateHandle(pstCIHandle);

	up(&g_CipherMutexKernel);

	return ret;
}


HI_S32 DRV_CIPHER_DestroyHandle(HI_HANDLE hCipherchn)
{
    HI_U32 softChnId = 0;

    softChnId = HI_HANDLE_GET_CHNID(hCipherchn);
    if (HI_FALSE == g_stCipherOsrChn[softChnId].g_bSoftChnOpen)
    {
        return HI_SUCCESS;
    }

    if (g_stCipherOsrChn[softChnId].pstDataPkg)
    {
        HI_VFREE(HI_ID_CIPHER, g_stCipherOsrChn[softChnId].pstDataPkg);
        g_stCipherOsrChn[softChnId].pstDataPkg = NULL;
    }

    g_stCipherOsrChn[softChnId].g_bSoftChnOpen = HI_FALSE;
    g_stCipherOsrChn[softChnId].pWichFile = NULL;

    return DRV_CIPHER_CloseChn(softChnId);
}

HI_S32 HI_DRV_CIPHER_DestroyHandle(HI_HANDLE hCipherchn)
{
    HI_S32 ret = HI_SUCCESS;

    if(down_interruptible(&g_CipherMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

	ret = DRV_CIPHER_DestroyHandle(hCipherchn);

	up(&g_CipherMutexKernel);

	return ret;
}

HI_S32 DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 softChnId = 0;
    HI_DRV_CIPHER_TASK_S stCITask;

    memset(&stCITask, 0, sizeof(stCITask));
    softChnId = HI_HANDLE_GET_CHNID(pstCIData->CIHandle);
    CIPHER_CheckHandle(softChnId);

    if ( 0 != softChnId )
    {
        stCITask.stData2Process.u32src = pstCIData->ScrPhyAddr;
        stCITask.stData2Process.u32dest = pstCIData->DestPhyAddr;
        stCITask.stData2Process.u32length = pstCIData->u32DataLength;
        stCITask.stData2Process.bDecrypt = HI_FALSE;
        stCITask.u32CallBackArg = softChnId;

        HI_INFO_CIPHER("Start to Encrypt, chnNum = %#x!\n", softChnId);

        g_stCipherOsrChn[softChnId].g_bDataDone = HI_FALSE;

        ret = DRV_CIPHER_CreatTask(softChnId,&stCITask, NULL, NULL);
        if (HI_SUCCESS != ret)
        {
            return ret;
        }

        if (0 == wait_event_interruptible_timeout(g_stCipherOsrChn[softChnId].cipher_wait_queue,
                    g_stCipherOsrChn[softChnId].g_bDataDone != HI_FALSE, 200))
        {
            HI_ERR_CIPHER("Encrypt time out! \n");
            return HI_FAILURE;
        }

        HI_INFO_CIPHER("Encrypt OK, chnNum = %#x!\n", softChnId);
        return HI_SUCCESS;
    }
    else
    {
        MMZ_BUFFER_S stSrcMmzBuf;
        MMZ_BUFFER_S stDestMmzBuf;
        HI_U32 u32Offset = 0;

        if ( pstCIData->u32DataLength % 16 != 0)
        {
            HI_ERR_CIPHER("Invalid encrypt length, must be multiple of 16 bytes!\n");
            return HI_FAILURE;
        }

        stSrcMmzBuf.u32Size = pstCIData->u32DataLength;
        stSrcMmzBuf.u32StartPhyAddr = pstCIData->ScrPhyAddr;
        ret = HI_DRV_MMZ_Map(&stSrcMmzBuf);
        if ( HI_FAILURE == ret)
        {
            HI_ERR_CIPHER("DRV SRC MMZ MAP ERROR!\n");
            return ret;
        }

        stDestMmzBuf.u32Size = pstCIData->u32DataLength;
        stDestMmzBuf.u32StartPhyAddr = pstCIData->DestPhyAddr;
        ret = HI_DRV_MMZ_Map(&stDestMmzBuf);
        if ( HI_FAILURE == ret)
        {
            HI_ERR_CIPHER("DRV DEST MMZ MAP ERROR!\n");
            HI_DRV_MMZ_Unmap(&stSrcMmzBuf);

            return ret;
        }
#if 0
        memcpy((HI_U8 *)(stCITask.stData2Process.u32DataPkg), (HI_U8 *)stSrcMmzBuf.u32StartVirAddr, pstCIData->u32DataLength);
        stCITask.stData2Process.u32length = pstCIData->u32DataLength;
        stCITask.stData2Process.bDecrypt = HI_FALSE;
        stCITask.u32CallBackArg = softChnId;

        ret = DRV_CIPHER_CreatTask(softChnId, &stCITask, NULL, NULL);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("Cipher create task failed!\n");
            HI_DRV_MMZ_Unmap(&stSrcMmzBuf);
            HI_DRV_MMZ_Unmap(&stDestMmzBuf);

            return HI_FAILURE;
        }

        memcpy((HI_U8 *)stDestMmzBuf.u32StartVirAddr, (HI_U8 *)(stCITask.stData2Process.u32DataPkg), pstCIData->u32DataLength);
#else
		while(u32Offset < pstCIData->u32DataLength)
		{
		    memcpy((HI_U8 *)(stCITask.stData2Process.u32DataPkg), (HI_U8 *)stSrcMmzBuf.u32StartVirAddr + u32Offset, 16);
		    stCITask.stData2Process.u32length = 16;
		    stCITask.stData2Process.bDecrypt = HI_FALSE;
		    stCITask.u32CallBackArg = softChnId;

		    ret = DRV_CIPHER_CreatTask(softChnId, &stCITask, NULL, NULL);
		    if (HI_SUCCESS != ret)
		    {
	            HI_ERR_CIPHER("Cipher create task failed!\n");
	            HI_DRV_MMZ_Unmap(&stSrcMmzBuf);
	            HI_DRV_MMZ_Unmap(&stDestMmzBuf);
	            return HI_FAILURE;
		    }

		    memcpy((HI_U8 *)stDestMmzBuf.u32StartVirAddr + u32Offset, (HI_U8 *)(stCITask.stData2Process.u32DataPkg), 16);
		    u32Offset += 16;
		}
#endif

        HI_DRV_MMZ_Unmap(&stSrcMmzBuf);
        HI_DRV_MMZ_Unmap(&stDestMmzBuf);
        return HI_SUCCESS;
    }

}

HI_S32 HI_DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData)
{
    HI_S32 ret = HI_SUCCESS;

    if(down_interruptible(&g_CipherMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

	ret = DRV_CIPHER_Encrypt(pstCIData);

	up(&g_CipherMutexKernel);

	return ret;
}

HI_S32 DRV_CIPHER_Decrypt(CIPHER_DATA_S *pstCIData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 softChnId = 0;
    HI_DRV_CIPHER_TASK_S pCITask;

    if(NULL == pstCIData)
    {
        HI_ERR_CIPHER("Invalid param!\n");
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(pstCIData->CIHandle);
    CIPHER_CheckHandle(softChnId);

    if ( 0 != softChnId)
    {
        pCITask.stData2Process.u32src = pstCIData->ScrPhyAddr;
        pCITask.stData2Process.u32dest = pstCIData->DestPhyAddr;
        pCITask.stData2Process.u32length = pstCIData->u32DataLength;
        pCITask.stData2Process.bDecrypt = HI_TRUE;

        pCITask.u32CallBackArg=softChnId;

        HI_INFO_CIPHER("Start to Decrypt, chnNum = %#x!\n", softChnId);

        g_stCipherOsrChn[softChnId].g_bDataDone = HI_FALSE;

        ret = DRV_CIPHER_CreatTask(softChnId,&pCITask,NULL,NULL);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("Cipher create task failed!\n");
            return ret;
        }

        if (0== wait_event_interruptible_timeout(g_stCipherOsrChn[softChnId].cipher_wait_queue,
                    g_stCipherOsrChn[softChnId].g_bDataDone != HI_FALSE, 200))
        {
            HI_ERR_CIPHER("Decrypt time out \n");
            return HI_FAILURE;
        }

        HI_INFO_CIPHER("Decrypt OK, chnNum = %#x!\n", softChnId);
        return HI_SUCCESS;
    }
    else
    {
        MMZ_BUFFER_S stSrcMmzBuf;
        MMZ_BUFFER_S stDestMmzBuf;
        HI_U32 u32Offset = 0;

        if ( pstCIData->u32DataLength % 16 != 0)
        {
            HI_ERR_CIPHER("Invalid decrypt length, must be multiple of 16 bytes!\n");
            return HI_FAILURE;
        }

        stSrcMmzBuf.u32Size = pstCIData->u32DataLength;
        stSrcMmzBuf.u32StartPhyAddr = pstCIData->ScrPhyAddr;
        ret = HI_DRV_MMZ_Map(&stSrcMmzBuf);
        if ( HI_FAILURE == ret)
        {
            HI_ERR_CIPHER("DRV SRC MMZ MAP ERROR!\n");
            return HI_FAILURE;
        }

        stDestMmzBuf.u32Size = pstCIData->u32DataLength;
        stDestMmzBuf.u32StartPhyAddr = pstCIData->DestPhyAddr;
        ret = HI_DRV_MMZ_Map(&stDestMmzBuf);
        if ( HI_FAILURE == ret)
        {
            HI_ERR_CIPHER("DRV DEST MMZ MAP ERROR!\n");
            HI_DRV_MMZ_Unmap(&stSrcMmzBuf);
            return HI_FAILURE;
        }

#if 0
        memcpy((HI_U8 *)(pCITask.stData2Process.u32DataPkg), (HI_U8 *)stSrcMmzBuf.u32StartVirAddr, pstCIData->u32DataLength);
        pCITask.stData2Process.u32length = pstCIData->u32DataLength;
        pCITask.stData2Process.bDecrypt = HI_TRUE;
        pCITask.u32CallBackArg = softChnId;

        ret = DRV_CIPHER_CreatTask(softChnId, &pCITask, NULL, NULL);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("Cipher create task failed!\n");
            HI_DRV_MMZ_Unmap(&stSrcMmzBuf);
            HI_DRV_MMZ_Unmap(&stDestMmzBuf);
            return HI_FAILURE;
        }

        memcpy((HI_U8 *)stDestMmzBuf.u32StartVirAddr, (HI_U8 *)(pCITask.stData2Process.u32DataPkg), pstCIData->u32DataLength);
#else
		while(u32Offset < pstCIData->u32DataLength)
		{
		    memcpy((HI_U8 *)(pCITask.stData2Process.u32DataPkg), (HI_U8 *)stSrcMmzBuf.u32StartVirAddr + u32Offset, 16);
		    pCITask.stData2Process.u32length = 16;
		    pCITask.stData2Process.bDecrypt = HI_TRUE;
		    pCITask.u32CallBackArg = softChnId;

		    ret = DRV_CIPHER_CreatTask(softChnId, &pCITask, NULL, NULL);
		    if (HI_SUCCESS != ret)
		    {
	            HI_ERR_CIPHER("Cipher create task failed!\n");
	            HI_DRV_MMZ_Unmap(&stSrcMmzBuf);
	            HI_DRV_MMZ_Unmap(&stDestMmzBuf);
	            return HI_FAILURE;
		    }

		    memcpy((HI_U8 *)stDestMmzBuf.u32StartVirAddr + u32Offset, (HI_U8 *)(pCITask.stData2Process.u32DataPkg), 16);
		    u32Offset += 16;
		}
#endif

        HI_DRV_MMZ_Unmap(&stSrcMmzBuf);
        HI_DRV_MMZ_Unmap(&stDestMmzBuf);
        return HI_SUCCESS;
    }
}

HI_S32 HI_DRV_CIPHER_Decrypt(CIPHER_DATA_S *pstCIData)
{
	HI_S32 ret = HI_SUCCESS;

	if(down_interruptible(&g_CipherMutexKernel))
	{
		HI_ERR_CIPHER("down_interruptible failed!\n");
		return HI_FAILURE;
	}

	ret = DRV_CIPHER_Decrypt(pstCIData);

	up(&g_CipherMutexKernel);

	return ret;
}


HI_S32 HI_DRV_CIPHER_EncryptMulti(CIPHER_DATA_S *pstCIData)
{
    HI_U32 i = 0;
    HI_U32 softChnId = 0;
    static HI_DRV_CIPHER_DATA_INFO_S  tmpData[CIPHER_MAX_LIST_NUM];
    HI_UNF_CIPHER_DATA_S *pTmp = NULL;
    HI_U32 pkgNum = 0;
    HI_S32 ret = HI_SUCCESS;

    if(NULL == pstCIData)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    if(down_interruptible(&g_CipherMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(pstCIData->CIHandle);
    CIPHER_CheckHandle(softChnId);

    pkgNum = pstCIData->u32DataLength;
    if (pkgNum > CIPHER_MAX_LIST_NUM)
    {
        HI_ERR_CIPHER("Error: you send too many pkg(%d), must < %d.\n",pkgNum, CIPHER_MAX_LIST_NUM);
		up(&g_CipherMutexKernel);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (copy_from_user(g_stCipherOsrChn[softChnId].pstDataPkg, (void*)pstCIData->ScrPhyAddr,
                       pkgNum * sizeof(HI_UNF_CIPHER_DATA_S)))
    {
        HI_ERR_CIPHER("copy data from user fail!\n");
		up(&g_CipherMutexKernel);
        return HI_FAILURE;
    }

    for (i = 0; i < pstCIData->u32DataLength; i++)
    {
        pTmp = g_stCipherOsrChn[softChnId].pstDataPkg + i;
        tmpData[i].bDecrypt = HI_FALSE;
        tmpData[i].u32src = pTmp->u32SrcPhyAddr;
        tmpData[i].u32dest = pTmp->u32DestPhyAddr;
        tmpData[i].u32length = pTmp->u32ByteLength;
    }

    HI_INFO_CIPHER("Start to DecryptMultiPkg, chnNum = %#x, pkgNum=%d!\n", softChnId, pkgNum);

    g_stCipherOsrChn[softChnId].g_bDataDone = HI_FALSE;

    ret = DRV_CIPHER_CreatMultiPkgTask(softChnId, tmpData, pkgNum, softChnId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Cipher create multi task failed!\n");
		up(&g_CipherMutexKernel);
        return ret;
    }

    if (0== wait_event_interruptible_timeout(g_stCipherOsrChn[softChnId].cipher_wait_queue,
                g_stCipherOsrChn[softChnId].g_bDataDone != HI_FALSE, 200))
    {
        HI_ERR_CIPHER("Decrypt time out \n");
		up(&g_CipherMutexKernel);
        return HI_FAILURE;
    }

    HI_INFO_CIPHER("Decrypt OK, chnNum = %#x!\n", softChnId);
	up(&g_CipherMutexKernel);
    return HI_SUCCESS;
}

HI_S32 HI_DRV_CIPHER_DecryptMulti(CIPHER_DATA_S *pstCIData)
{
    HI_U32 i;
    HI_U32 softChnId = 0;
    static HI_DRV_CIPHER_DATA_INFO_S  tmpData[CIPHER_MAX_LIST_NUM];
    HI_UNF_CIPHER_DATA_S *pTmp = NULL;
    HI_U32 pkgNum = 0;
    HI_S32 ret = HI_SUCCESS;

    if(NULL == pstCIData)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(down_interruptible(&g_CipherMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(pstCIData->CIHandle);
    CIPHER_CheckHandle(softChnId);

    pkgNum = pstCIData->u32DataLength;
    if (pkgNum > CIPHER_MAX_LIST_NUM)
    {
        HI_ERR_CIPHER("Error: you send too many pkg(%d), must < %d.\n",pkgNum, CIPHER_MAX_LIST_NUM);
		up(&g_CipherMutexKernel);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (copy_from_user(g_stCipherOsrChn[softChnId].pstDataPkg, (void*)pstCIData->ScrPhyAddr,
                       pkgNum * sizeof(HI_UNF_CIPHER_DATA_S)))
    {
        HI_ERR_CIPHER("copy data from user fail!\n");
		up(&g_CipherMutexKernel);
        return HI_FAILURE;
    }

    for (i = 0; i < pstCIData->u32DataLength; i++)
    {
        pTmp = g_stCipherOsrChn[softChnId].pstDataPkg + i;
        tmpData[i].bDecrypt = HI_TRUE;
        tmpData[i].u32src = pTmp->u32SrcPhyAddr;
        tmpData[i].u32dest = pTmp->u32DestPhyAddr;
        tmpData[i].u32length = pTmp->u32ByteLength;
    }

    HI_INFO_CIPHER("Start to DecryptMultiPkg, chnNum = %#x, pkgNum=%d!\n", softChnId, pkgNum);

    g_stCipherOsrChn[softChnId].g_bDataDone = HI_FALSE;

    ret = DRV_CIPHER_CreatMultiPkgTask(softChnId, tmpData, pkgNum, softChnId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Cipher create multi task failed!\n");
		up(&g_CipherMutexKernel);
        return ret;
    }

    if (0== wait_event_interruptible_timeout(g_stCipherOsrChn[softChnId].cipher_wait_queue,
                g_stCipherOsrChn[softChnId].g_bDataDone != HI_FALSE, 200))
    {
        HI_ERR_CIPHER("Decrypt time out \n");
		up(&g_CipherMutexKernel);
        return HI_FAILURE;
    }

    HI_INFO_CIPHER("Decrypt OK, chnNum = %#x!\n", softChnId);
	up(&g_CipherMutexKernel);
    return HI_SUCCESS;
}

HI_S32 HI_DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG)
{
	HI_S32 ret = HI_SUCCESS;

    if(NULL == pstRNG)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    if(down_interruptible(&g_CipherMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    ret = HAL_Cipher_GetRandomNumber(pstRNG);

	up(&g_CipherMutexKernel);
	return ret;
}

HI_S32 DRV_CIPHER_Open(struct inode * inode, struct file * file)
{
#ifdef HI_ADVCA_SUPPORT
    HI_S32 ret = HI_SUCCESS;

    ret = HI_DRV_MODULE_GetFunction(HI_ID_CA, (HI_VOID**)&s_pAdvcaFunc);
    if ( (HI_SUCCESS != ret) || (NULL == s_pAdvcaFunc) )
    {
        HI_ERR_CIPHER("Get advca function failed.\n");
        return -1;
    }
#endif

    return 0;
}

HI_S32 DRV_CIPHER_Release(struct inode * inode, struct file * file)
{
    HI_U32 i;

    for (i = 0; i < CIPHER_SOFT_CHAN_NUM; i++)
    {
            DRV_CIPHER_CloseChn(i);
            g_stCipherOsrChn[i].g_bSoftChnOpen = HI_FALSE;
            g_stCipherOsrChn[i].pWichFile = NULL;
            if (g_stCipherOsrChn[i].pstDataPkg)
            {
                HI_VFREE(HI_ID_CIPHER, g_stCipherOsrChn[i].pstDataPkg);
                g_stCipherOsrChn[i].pstDataPkg = NULL;
        }
    }

    return 0;
}

HI_VOID DRV_CIPHER_SetHdcpModeEn(HI_DRV_CIPHER_HDCP_KEY_MODE_E enMode)
{
    HAL_Cipher_SetHdcpModeEn(enMode);
    return;
}

HI_S32 DRV_CIPHER_GetHdcpModeEn(HI_DRV_CIPHER_HDCP_KEY_MODE_E *penMode)
{
    return HAL_Cipher_GetHdcpModeEn(penMode);
}

HI_VOID DRV_CIPHER_SetHdcpKeyTxRead(HI_DRV_CIPHER_HDCP_KEY_RAM_MODE_E enMode)
{
    HAL_Cipher_SetHdcpKeyTxRead(enMode);
    return;
}
HI_VOID DRV_CIPHER_SetHdcpkeyRxRead(HI_DRV_CIPHER_HDCP_KEY_RX_READ_E enRxReadMode)
{
    HAL_CIPHER_SetRxRead(enRxReadMode);
}
HI_S32 DRV_CIPHER_SetHdcpkeyRxSelect(HI_DRV_CIPHER_HDCP_KEY_RX_SELECT_E enRxSelect)
{
    return HAL_Cipher_SetRxSelect(enRxSelect);
}

HI_S32 DRV_CIPHER_SetHdcpKeySelectMode(HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enHdcpKeySelectMode)
{
    return HAL_Cipher_SetHdcpKeySelectMode(enHdcpKeySelectMode);
}

HI_S32 DRV_CIPHER_GetHdcpKeySelectMode(HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E *penHdcpKeySelectMode)
{
    return HAL_Cipher_GetHdcpKeySelectMode(penHdcpKeySelectMode);
}

HI_S32 DRV_CIPHER_HdcpParamConfig(HI_DRV_CIPHER_HDCP_KEY_MODE_E enHdcpEnMode,
                                  HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enRootKeyType,
                                  HI_DRV_HDCPKEY_TYPE_E enHDCPKeyType)
{
    HI_S32 ret = HI_SUCCESS;

    (HI_VOID)DRV_CIPHER_SetHdcpModeEn(enHdcpEnMode);

    if (HI_DRV_HDCPKEY_RX0 == enHDCPKeyType  || HI_DRV_HDCPKEY_RX1 == enHDCPKeyType)
    {
        (HI_VOID)DRV_CIPHER_SetHdcpkeyRxRead(CIPHER_HDCP_KEY_WR_RX_RAM);

        ret = DRV_CIPHER_SetHdcpkeyRxSelect(CIPHER_HDCP_KEY_SELECT_RX);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("DRV_CIPHER_SetHdcpkeyRxSelect error.\n");
            return HI_FAILURE;
        }
    }
    else
    {
#if defined(CHIP_TYPE_hi3796cv100_a) || defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100_a) || defined(CHIP_TYPE_hi3798cv100)
        (HI_VOID)HAL_Cipher_SetHDMITxRxOtpSelReg();
#endif
        DRV_CIPHER_SetHdcpKeyTxRead(CIPHER_HDCP_KEY_RAM_MODE_WRITE);
        ret = DRV_CIPHER_SetHdcpkeyRxSelect(CIPHER_HDCP_KEY_SELECT_TX);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("DRV_CIPHER_SetHdcpkeyRxSelect error.\n");
            return HI_FAILURE;
        }
    }

    return DRV_CIPHER_SetHdcpKeySelectMode(enRootKeyType);
}

HI_S32 DRV_CIPHER_ClearHdcpConfig(HI_VOID)
{
    HAL_Cipher_ClearHdcpCtrlReg();
    return HI_SUCCESS;
}

HI_S32 HI_DRV_CIPHER_SoftReset()
{
    HI_S32 ret = HI_SUCCESS;

    (HI_VOID)HI_DRV_CIPHER_Suspend();

    ret = HI_DRV_CIPHER_Resume();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("Cipher Soft Reset failed in cipher resume!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_U32 g_u32HashHandleSeed = 0xa0000000;
static HI_HANDLE g_hashHandle = -1;
static sha1_context g_sha1Context;
static sha2_context g_sha2Context;
static HI_BOOL g_is224 = HI_FALSE;

static HI_S32 Cipher_CalcHashInit_Sw(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 ticks;
    struct timeval tv;

    do_gettimeofday(&tv);
    ticks = tv.tv_sec + tv.tv_usec;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
    srandom32 (ticks);  //set the seed of random data
    g_hashHandle = random32();
#else
    g_hashHandle = (HI_HANDLE)ticks;
#endif

    switch(pCipherHashData->enShaType)
    {
        case HI_UNF_CIPHER_HASH_TYPE_SHA1:
            sha1_starts(&g_sha1Context);
            pCipherHashData->hHandle = g_hashHandle;
            break;

        case HI_UNF_CIPHER_HASH_TYPE_SHA256:
            g_is224 = HI_FALSE;
            sha2_starts(&g_sha2Context, g_is224);
            pCipherHashData->hHandle = g_hashHandle;
            break;

        default:
           HI_ERR_CIPHER("Invalid hash type!\n");
           pCipherHashData->hHandle = -1;
           Ret = HI_FAILURE;
           break;
    }

    return Ret;
}

HI_S32 Cipher_CalcHashInit_Hw(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;

    g_hashHandle = g_u32HashHandleSeed++;
    pCipherHashData->hHandle = g_hashHandle;

    ret = HAL_Cipher_CalcHashInit(pCipherHashData);
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("Cipher hash init failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 Cipher_CalcHashUpdate_Sw(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 Ret = HI_SUCCESS;

    if(pCipherHashData->hHandle != g_hashHandle)
    {
        HI_ERR_CIPHER("Invalid hash handle!\n");
        return HI_FAILURE;
    }

    switch(pCipherHashData->enShaType)
    {
        case HI_UNF_CIPHER_HASH_TYPE_SHA1:
            sha1_update(&g_sha1Context, pCipherHashData->pu8InputData, pCipherHashData->u32InputDataLen);
            break;

        case HI_UNF_CIPHER_HASH_TYPE_SHA256:
            sha2_update(&g_sha2Context, pCipherHashData->pu8InputData, pCipherHashData->u32InputDataLen);
            break;

        default:
            HI_ERR_CIPHER("Invalid hash type!\n");
            Ret = HI_FAILURE;
            break;
    }

    return Ret;
}

static HI_S32 Cipher_CalcHashUpdate_Hw(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error, Null pointer input!\n");
        return HI_FAILURE;
    }

    if(pCipherHashData->hHandle != g_hashHandle)
    {
        HI_ERR_CIPHER("Invalid hash handle!\n");
        return HI_FAILURE;
    }

    ret = HAL_Cipher_CalcHashUpdate(pCipherHashData);
    if(HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("Cipher hash update failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 Cipher_CalcHashFinal_Sw(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 ticks;
    struct timeval tv;

    if(pCipherHashData->hHandle != g_hashHandle)
    {
        HI_ERR_CIPHER("Invalid hash handle!\n");
        return HI_FAILURE;
    }

    /* reset the handle */
    do_gettimeofday(&tv);
    ticks = tv.tv_sec + tv.tv_usec;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
    srandom32 (ticks);  /* set the seed of random data */
    g_hashHandle = random32();
#else
    g_hashHandle = (HI_HANDLE)ticks;
#endif

    switch(pCipherHashData->enShaType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:

        sha1_finish(&g_sha1Context, pCipherHashData->pu8Output);
        break;

    case HI_UNF_CIPHER_HASH_TYPE_SHA256:

        sha2_finish(&g_sha2Context, pCipherHashData->pu8Output);
        break;

    default:
       HI_ERR_CIPHER("Invalid hash type!\n");
       Ret = HI_FAILURE;
       break;
    }

    return Ret;
}

HI_S32 Cipher_CalcHashFinal_Hw(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error, Null pointer input!\n");
        return HI_FAILURE;
    }

    if(pCipherHashData->hHandle != g_hashHandle)
    {
        HI_ERR_CIPHER("Invalid hash handle!\n");
        return HI_FAILURE;
    }

    ret = HAL_Cipher_CalcHashFinal(pCipherHashData);
    if(HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("Cipher hash final failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_CIPHER_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_CHIP_TYPE_E enchipType = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E enchipVersion = HI_CHIP_VERSION_BUTT;

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error, Null pointer input!\n");
        return HI_FAILURE;
    }

    if(down_interruptible(&g_HashMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    HI_DRV_SYS_GetChipVersion(&enchipType, &enchipVersion);
    if( (HI_CHIP_VERSION_V300 == enchipVersion) && (HI_CHIP_TYPE_HI3716M == enchipType) )
    {
        ret = Cipher_CalcHashInit_Sw(pCipherHashData);
    }
    else
    {
        ret = Cipher_CalcHashInit_Hw(pCipherHashData);
    }

    if(HI_FAILURE ==  ret)
    {
        HI_ERR_CIPHER("CIPHER hash init failed!\n");
		up(&g_HashMutexKernel);
        return HI_FAILURE;
    }

	up(&g_HashMutexKernel);
    return ret;
}


HI_S32 HI_DRV_CIPHER_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CHIP_TYPE_E enchipType = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E enchipVersion = HI_CHIP_VERSION_BUTT;

    if(down_interruptible(&g_HashMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    HI_DRV_SYS_GetChipVersion(&enchipType, &enchipVersion);
    if( (HI_CHIP_VERSION_V300 == enchipVersion) && (HI_CHIP_TYPE_HI3716M == enchipType) )
    {
        s32Ret = Cipher_CalcHashUpdate_Sw(pCipherHashData);
    }
    else
    {
        s32Ret = Cipher_CalcHashUpdate_Hw(pCipherHashData);
    }

    if(HI_FAILURE ==  s32Ret)
    {
        HI_ERR_CIPHER("Cipher hash update failed!\n");
		up(&g_HashMutexKernel);
        return HI_FAILURE;
    }

	up(&g_HashMutexKernel);
    return s32Ret;
}

HI_S32 HI_DRV_CIPHER_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CHIP_TYPE_E enchipType = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E enchipVersion = HI_CHIP_VERSION_BUTT;

    if(down_interruptible(&g_HashMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    HI_DRV_SYS_GetChipVersion(&enchipType, &enchipVersion);
    if( (HI_CHIP_VERSION_V300 == enchipVersion) && (HI_CHIP_TYPE_HI3716M == enchipType) )
    {
        s32Ret = Cipher_CalcHashFinal_Sw(pCipherHashData);
    }
    else
    {
        s32Ret = Cipher_CalcHashFinal_Hw(pCipherHashData);
    }

	up(&g_HashMutexKernel);
    return s32Ret;
}

/*
        head              HDMIIP_HDCPKey                 CRC32_0 CRC32_1
      |-------|-----------------------------------------|------|------|
      |4bytes-|-----------------Encrypt(320bytes)-------|-4byte|-4byte|
*/
HI_S32 HI_DRV_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey)
{
    HI_S32 ret = HI_SUCCESS;
    if(down_interruptible(&g_CipherMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
	ret = DRV_CIPHER_LoadHdcpKey(pstFlashHdcpKey);
	up(&g_CipherMutexKernel);
	return ret;
}
HI_S32 DRV_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Crc32Result = 0;
    HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enRootKeyType;
    HI_U32 u32Tmp = 0;

    if( NULL == pstFlashHdcpKey)
    {
        HI_ERR_CIPHER("NULL Pointer, Invalid param input!\n");
        return HI_FAILURE;
    }

    if(pstFlashHdcpKey->u32KeyLen != HDCP_KEY_CHIP_FILE_SIZE)
    {
        HI_ERR_CIPHER("Invalid key len: 0x%x!\n", pstFlashHdcpKey->u32KeyLen);
        return HI_FAILURE;
    }

    // HDCP1.x Tx/Rx
    if (HI_DRV_HDCP_VERIOSN_1x == pstFlashHdcpKey->enHDCPVersion)
    {
        u32Tmp = pstFlashHdcpKey->u8Key[0] & 0xc0;
        if ( 0x00 == u32Tmp)
        {
            enRootKeyType = CIPHER_HDCP_KEY_TYPE_OTP_ROOT_KEY;
        }
        else if( 0x80 == u32Tmp)
        {
            enRootKeyType = CIPHER_HDCP_KEY_TYPE_HISI_DEFINED;
        }
        else
        {
            HI_ERR_CIPHER("Invalid keySelect mode input!\n");
            return  HI_FAILURE;
        }

        /* verify crc32_1 */
        s32Ret = Cipher_CRC32(pstFlashHdcpKey->u8Key, (HDCP_KEY_CHIP_FILE_SIZE - 4), &u32Crc32Result);
        if ( HI_FAILURE == s32Ret)
        {
            HI_ERR_CIPHER("HDCP KEY CRC32_1 calc failed!\n");
            return HI_FAILURE;
        }
        if ( memcmp(&u32Crc32Result, &pstFlashHdcpKey->u8Key[HDCP_KEY_CHIP_FILE_SIZE - 4], 4) != 0 )
        {
            HI_ERR_CIPHER("HDCP KEY CRC32_1 compare failed!");
            return HI_FAILURE;
        }

        s32Ret = s_DRV_Cipher_CryptoHdcpKey(pstFlashHdcpKey->u8Key + 4,
                                         HDCP_KEY_RAM_SIZE,
                                         pstFlashHdcpKey->enHDCPKeyType,
                                         enRootKeyType,
                                         HI_NULL);
        if ( HI_FAILURE == s32Ret)
        {
            HI_ERR_CIPHER("HDCP key decrypt final failed!\n");
            return HI_FAILURE;
        }

        memcpy(&g_stFlashHdcpKey, pstFlashHdcpKey, sizeof(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S));
        g_bHDCPKeyLoadFlag = HI_TRUE;

    }
    else   // HDCP2.x Rx/Tx or other
    {
        HI_ERR_CIPHER("Please set correct HDCP verison!");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_VOID s_DRV_CIPHER_FormatHDCPKey(HI_UNF_HDCP_DECRYPT_S *pSrcKey, HI_U8 u8DstKey[HDCP_KEY_RAM_SIZE])
{
    HI_S32 i;
    HI_U8 TailBytes[31] = {0x14, 0xf7, 0x61, 0x03, 0xb7, 0x59, 0x45, 0xe3,
                           0x0c, 0x7d, 0xb4, 0x45, 0x19, 0xea, 0x8f, 0xd2,
                           0x89, 0xee, 0xbd, 0x90, 0x21, 0x8b, 0x05, 0xe0,
                           0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    HI_U32 CheckSum = 0xa3c5;
    HI_U32 XorValue, Temp;

    memset(u8DstKey, 0, HDCP_KEY_RAM_SIZE);

    /* Byte 0*/
    u8DstKey[0] = 0x00;
    /* Byte 1 ~ 5 KSV */
    for (i = 0; i < 5; i ++)
    {
        u8DstKey[1 + i] = pSrcKey->u8KSV[i];
    }
    /* Byte 8 */
    u8DstKey[8] = 0xa8;
    /* Byte 9 ~ 288 Device Private Key */
    for (i = 0; i < 280; i ++)
    {
        u8DstKey[9 + i] = pSrcKey->u8PrivateKey[i];
    }
    /* Byte 289 ~ 319 */
    for (i = 0; i < 31; i ++)
    {
        u8DstKey[289 + i] = TailBytes[i];
    }

    /* Count CRC value */
    for(i=0; i<320; i++)
    {
        if((i>=6) && (i<=8))
        {
            continue;
        }
        XorValue = CheckSum ^ u8DstKey[i];
        Temp = ~((XorValue >> 7) ^ (XorValue >> 16));
        XorValue = XorValue << 1;
        XorValue = (XorValue & 0x1fffe) | (Temp & 1);
        CheckSum = XorValue;
    }

    for(i=0; i<8; i++)
    {
        XorValue = CheckSum;
        Temp = ~((XorValue >> 7) ^ (XorValue >> 16));
        XorValue = XorValue << 1;
        XorValue = (XorValue & 0x1fffe) | (Temp & 1);
        CheckSum = XorValue;
    }

    /* Byte 6 && 7  CRC Value */
    u8DstKey[6] = CheckSum & 0xff;
    u8DstKey[7] = (CheckSum >> 8) & 0xff;

#if defined (CHIP_TYPE_hi3798cv200_a)
    u8DstKey[HDCP_KEY_RAM_SIZE - 2] = 0x00; //AV Content Protection
    u8DstKey[HDCP_KEY_RAM_SIZE - 1] = 0xFF; //OTP Locked
#endif
    
    return;
}

/**********************************************************************  
    DCP申请的独立的HDCP key原始格式，共308Bytes：
    0~4	KSV  固定为 "02000000"	Key Selection Vector use to communicate between HDMI Transmitter and Receiver.
    5~7	     固定为 "000000"
    8~287	 Device Private Key	Secret data
    288~307	Reserved	No use

    HISI HDCP Key工具将申请到的Key重新封装，生成新的key文件大小为384个字节，各字段意义如下：
	第0~7(8)字节      ：海思标记位：HISI_xxx
	第8~15(8)字节     ：工具版本号：V0000001
	第16~47(32)字节   ：客户的ID号：xxxxxxxx
	第48~367(320)字节 ：加密后的320bytes HDCP key(16字节对齐)。
	第368~384(16)字节 ：后续使用，暂定为随机数。

    芯片上加密存放到文件中的HDCP Key格式
    head              HDMIIP_HDCPKey                 CRC32_0 CRC32_1
    |-------|-----------------------------------------|------|------|
    |4bytes-|-----------------Encrypt(320bytes)-------|-4byte|-4byte|

    total: 332

    Head格式：4 byte
    B0[7..6] key type, 00: otp root key, 01: hisi defined 10: host root key
    B1:      固定为0x00;
    B2~B3:   固定为"HI"

    HDCPKey 格式：320 byte
    B0:      固定为0x00;
    B1~B5:   KSV (DCP组织申请的HDCP Key中提取）
    B6~B7:   HDCPKey的CRC16，不包括B6~B8.
    B8：     固定为0xa8;
    B9~B288: Device Private Key (DCP组织申请的HDCP Key中提取）
    B289~B319: 填充为 0x14, 0xf7, 0x61, 0x03, 0xb7, 0x59, 0x45, 0xe3, 0x0c, 0x7d, 0xb4, 0x45, 0x19, 0xea, 0x8f, 0xd2,0x89, 0xee, 0xbd, 0x90, 0x21, 0x8b, 0x05, 0xe0,0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

    CRC32_0：  加密前HDCPKey的CRC32
    CRC32_1：  Head+HDCPKey+CRC32_0的CRC32
*/
static HI_S32 s_DRV_CIPHER_DecryptHDCPKeyBeforeFormat(HI_UNF_HDCP_HDCPKEY_S *pSrcKey,  HI_UNF_HDCP_DECRYPT_S *pDstkey)
{
    HI_U32 softChnId = 0;
    HI_U8 key[16];
    HI_S32 ret = HI_SUCCESS;
    HI_U8 *pu8EncryptKey = HI_NULL;
    HI_U8 *pu8ClearKey = HI_NULL;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    MMZ_BUFFER_S stInputBuffer, stOutputBuffer;
    HI_DRV_CIPHER_TASK_S stCITask;
    CIPHER_HANDLE_S stCIHandle;
    CIPHER_DATA_S stCIData;

    if(!pSrcKey->EncryptionFlag)
    {
        HI_ERR_CIPHER("EncryptionFlag Error!\n");
        return HI_FAILURE;
    }

    memset(&CipherCtrl, 0, sizeof(CipherCtrl));
    memset(&stInputBuffer, 0, sizeof(stInputBuffer));
    memset(&stOutputBuffer, 0, sizeof(stOutputBuffer));
    memset(&stCITask, 0, sizeof(stCITask));
    memset(&stCIData, 0, sizeof(stCIData));
    pu8EncryptKey = pSrcKey->key.EncryptData.u8EncryptKey;

    stCIHandle.hCIHandle = 0;
    stCIHandle.stCipherAtts.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    ret = DRV_CIPHER_CreateHandle(&stCIHandle);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("Cipher create handle failed\n");
        return HI_FAILURE;
    }

    if( memcmp("V0000001", &pu8EncryptKey[8], 8) != 0 )
    {
        HI_ERR_CIPHER("EncryptKey check version failed\n");
        return HI_FAILURE;
    }

    memset(key, 0, sizeof(key));
    key[0] = 'z';
    key[1] = 'h';
    key[2] = 'o';
    key[3] = 'n';
    key[4] = 'g';

    CipherCtrl.bKeyByCA = HI_FALSE;
    CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
    CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_8BIT;
    CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    CipherCtrl.stChangeFlags.bit1IV = 1;
    memcpy((HI_U8 *)CipherCtrl.u32Key, key, sizeof(key));
    memset(CipherCtrl.u32IV, 0, sizeof(CipherCtrl.u32IV));

    softChnId = HI_HANDLE_GET_CHNID(stCIHandle.hCIHandle);
    ret = DRV_CIPHER_ConfigChn(softChnId, &CipherCtrl);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Cipher config handle failed\n");
        return HI_FAILURE;
    }

    ret = HI_DRV_MMZ_AllocAndMap("Cipher_EncryptBuf", MMZ_OTHERS, HDCP_KEY_PRIME_SIZE, 32, &stInputBuffer);
    ret |= HI_DRV_MMZ_AllocAndMap("Cipher_DecryptBuf", MMZ_OTHERS, HDCP_KEY_PRIME_SIZE, 32, &stOutputBuffer);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_MMZ_UnmapAndRelease(&stInputBuffer);
        HI_ERR_CIPHER("HI_DRV_MMZ_AllocAndMap failed\n");
        return HI_FAILURE;
    }

    memcpy((HI_U8 *)stInputBuffer.u32StartVirAddr, &pu8EncryptKey[48], HDCP_KEY_PRIME_SIZE);
    stCIData.CIHandle = stCIHandle.hCIHandle;
    stCIData.ScrPhyAddr = stInputBuffer.u32StartPhyAddr;
    stCIData.DestPhyAddr = stOutputBuffer.u32StartPhyAddr;
    stCIData.u32DataLength = HDCP_KEY_PRIME_SIZE;
    ret = DRV_CIPHER_Decrypt(&stCIData);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("DRV CIPHER Decrypt failed!\n");
        goto __EXIT_CIPHER__;
    }
    pu8ClearKey = (HI_U8*)stOutputBuffer.u32StartVirAddr;
    if(pu8ClearKey[5] || pu8ClearKey[6] || pu8ClearKey[7])
    {
        HI_ERR_CIPHER("Check bit[5:7] failed after decrypt!\n");
        goto __EXIT_CIPHER__;
    }

    memcpy(pDstkey->u8KSV, pu8ClearKey, sizeof(pDstkey->u8KSV));
    memcpy(pDstkey->u8PrivateKey, pu8ClearKey + 8, sizeof(pDstkey->u8PrivateKey));

__EXIT_CIPHER__:
    HI_DRV_MMZ_UnmapAndRelease(&stInputBuffer);
    HI_DRV_MMZ_UnmapAndRelease(&stOutputBuffer);

    (HI_VOID)DRV_CIPHER_DestroyHandle(stCIHandle.hCIHandle);

    return ret;
}

static HI_S32 s_DRV_CIPHER_CryptoFormattedHDCPKey(HI_U8 *pu8Input,
                                    HI_U32 u32InputLen,
                                    HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enRootKeyType,
                                    HI_U8 *pu8Output)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 softChnId = 0;
    HI_U32 u32KeyBlock = 0;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_DRV_CIPHER_TASK_S pCITask;
    HI_U32 i = 0;
    CIPHER_HANDLE_S stCIHandle;

    if ( NULL == pu8Input )
    {
        HI_ERR_CIPHER("Invalid param , null pointer input!\n");
        return HI_FAILURE;
    }

    if (NULL == pu8Output ) 
    {
        HI_ERR_CIPHER("Invalid param , null pointer!\n");
        return HI_FAILURE;
    }

    if ( HDCP_KEY_RAM_SIZE != u32InputLen)
    {
        HI_ERR_CIPHER("Invalid keylength input!\n");
        return HI_FAILURE;
    }

    (HI_VOID)DRV_CIPHER_SetHdcpModeEn(CIPHER_HDCP_MODE_HDCP_KEY);

    memset(&pCITask, 0, sizeof(pCITask));
    memset(&CipherCtrl, 0, sizeof(CipherCtrl));

    ret = s_DRV_CIPHER_CreateHandleForHDCPKeyInternal(&stCIHandle.hCIHandle);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("(DRV_CIPHER_OpenChn failed\n");
        (HI_VOID)DRV_CIPHER_ClearHdcpConfig();
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(stCIHandle.hCIHandle);

    u32KeyBlock = u32InputLen / 16;
    for(i = 0;i < u32KeyBlock; i++)
    {   
        ret = DRV_CIPHER_HdcpParamConfig(CIPHER_HDCP_MODE_HDCP_KEY, enRootKeyType, HI_DRV_HDCPKEY_RX0);
        if ( HI_FAILURE == ret)
        {
            goto __EXIT_HDCP__;
        }
        CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
        CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
        CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
        memset(CipherCtrl.u32IV, 0, sizeof(CipherCtrl.u32IV));
        CipherCtrl.stChangeFlags.bit1IV = (0 == i) ? 1 : 0;

        ret = DRV_CIPHER_ConfigChn(softChnId, &CipherCtrl);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("DRV cipher config handle failed!\n");
            goto __EXIT_HDCP__;
        }

        memcpy((HI_U8 *)(pCITask.stData2Process.u32DataPkg), pu8Input + (i * 16), 16);
        pCITask.stData2Process.u32length = 16;
        pCITask.stData2Process.bDecrypt = HI_FALSE;
        pCITask.u32CallBackArg = softChnId;

        ret = DRV_CIPHER_CreatTask(softChnId, &pCITask, NULL, NULL);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("(DRV_CIPHER_CreatTask call failed\n");
            goto __EXIT_HDCP__;
        }

        if ( NULL != pu8Output )
        {
            memcpy(pu8Output + ( i * 16), (HI_U8 *)(pCITask.stData2Process.u32DataPkg), 16);
        }
    }

__EXIT_HDCP__:
    (HI_VOID)DRV_CIPHER_ClearHdcpConfig();
    (HI_VOID)DRV_CIPHER_DestroyHandle(stCIHandle.hCIHandle);

    return ret;
}

HI_S32 HI_DRV_CIPHER_EncryptHDCPKey(CIPHER_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer)
{
    HI_S32 ret = HI_SUCCESS;
	if(down_interruptible(&g_CipherMutexKernel))
	{
		HI_ERR_CIPHER("down_interruptible failed!\n");
		return HI_FAILURE;
	}
	ret = DRV_CIPHER_EncryptHDCPKey(pstHdcpKeyTransfer);
	up(&g_CipherMutexKernel);
	return ret;
}

HI_S32 DRV_CIPHER_EncryptHDCPKey(CIPHER_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8  *pu8OutKey = HI_NULL;
    HI_U32 u32KeyLen = 0;
    HI_U32 u32CRC_0 = 0;
    HI_U32 u32CRC_1 = 0;
    HI_UNF_HDCP_DECRYPT_S stDstKey;
    HI_DRV_HDCPKEY_TYPE_E enHDCPKeyType = CIPHER_HDCP_KEY_TYPE_HISI_DEFINED;

    if ( NULL == pstHdcpKeyTransfer)
    {
        HI_ERR_CIPHER("Invalid param, null pointer!\n");
        return HI_FAILURE;
    }

    memset(&stDstKey, 0, sizeof(stDstKey));
    pu8OutKey = pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey;

    /* header config */
    pu8OutKey[u32KeyLen++] = (pstHdcpKeyTransfer->bIsUseOTPRootKey ? 0x00 : 0x80);
    pu8OutKey[u32KeyLen++] = 0x00;
    /* 'H' 'I' display that the Encrypted Hdpcp Key Exists */
    pu8OutKey[u32KeyLen++] = 'H';
    pu8OutKey[u32KeyLen++] = 'I';
    
    /* format clear text*/
    if ( HI_TRUE == pstHdcpKeyTransfer->stHdcpKey.EncryptionFlag)
    {
        ret = s_DRV_CIPHER_DecryptHDCPKeyBeforeFormat(&pstHdcpKeyTransfer->stHdcpKey, &stDstKey);
        if(ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("s_DRV_CIPHER_DecryptHDCPKeyBeforeFormat failed!\n");
            return HI_FAILURE;
        }
        (HI_VOID)s_DRV_CIPHER_FormatHDCPKey(&stDstKey, &pu8OutKey[u32KeyLen]);
    }
    else
    {
        (HI_VOID)s_DRV_CIPHER_FormatHDCPKey(&pstHdcpKeyTransfer->stHdcpKey.key.DecryptData, &pu8OutKey[u32KeyLen]);
    }
    /* crc32_0 calculate */
    ret = Cipher_CRC32(&pu8OutKey[u32KeyLen], HDCP_KEY_RAM_SIZE, &u32CRC_0);
    if ( HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("CRC32_0 calc failed!\n");
        return HI_FAILURE;
    }
#if 0
        if(pstHdcpKeyTransfer->stHdcpKey.Reserved == 0xabcd1234)
        {
            int i;

            HI_INFO_HDCP("\n***** Debug HDCP Key, just debug HDCP key, Do not really write key *****\n");
            HI_INFO_HDCP("u8KSV:\n");
            for(i = 0; i < 5; ++i)
            {
                HI_INFO_HDCP("%02X ", stDstKey.u8KSV[i]);
            }

            HI_INFO_HDCP("\n u8PrivateKey:\n");
            for(i = 0; i < 280; ++i)
            {
                HI_INFO_HDCP("%02X ", stDstKey.u8PrivateKey[i]);
                if(((i+1)%16) == 0)
                    HI_INFO_HDCP("\n");
            }
            HI_INFO_HDCP("\n\n");

            return HI_SUCCESS;
        }
#endif


    /* encrypt formated text*/
    if (pstHdcpKeyTransfer->bIsUseOTPRootKey)
    {
        enHDCPKeyType = CIPHER_HDCP_KEY_TYPE_OTP_ROOT_KEY;
    }
    ret = s_DRV_CIPHER_CryptoFormattedHDCPKey(&pu8OutKey[u32KeyLen],
                                            HDCP_KEY_RAM_SIZE,
                                            enHDCPKeyType,
                                            &pu8OutKey[u32KeyLen]);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Encrypt HDCP Key using rootkey in otp failed!\n");
        return HI_FAILURE;
    }
    u32KeyLen+=HDCP_KEY_RAM_SIZE;
    memcpy(&pu8OutKey[u32KeyLen], &u32CRC_0, 4);
    u32KeyLen+=4;
    
    /* crc32_1  calculate */
    ret = Cipher_CRC32(pu8OutKey, u32KeyLen, &u32CRC_1);
    if ( HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("CRC32_1 calc failed!\n");
        return HI_FAILURE;
    }
    memcpy(&pu8OutKey[u32KeyLen], &u32CRC_1, 4);
    u32KeyLen+=4;

    return HI_SUCCESS;
}

HI_S32 DRV_CIPHER_ProcGetStatus(CIPHER_CHN_STATUS_S *pstCipherStatus)
{
    HI_U32 i = 0;

    for (i = 0; i < 8; i++)
    {
        if (HI_TRUE == g_stCipherSoftChans[i].bOpen)
        {
            pstCipherStatus[i].ps8Openstatus = "open ";
        }
        else
        {
            pstCipherStatus[i].ps8Openstatus = "close";
        }
    }
    return HAL_CIPHER_ProcGetStatus(pstCipherStatus);
}

HI_S32 DRV_CIPHER_CbcMacAuth(CIPHER_CBCMAC_DATA_S *pstParam)
{
    return HAL_Cipher_CbcMacAuth(pstParam);
}

HI_S32 HI_DRV_CIPHER_CbcMacAuth(CIPHER_CBCMAC_DATA_S *pstParam)
{
    HI_S32 ret = 0;

    if(down_interruptible(&g_CipherMutexKernel))
    {
    	HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    ret = DRV_CIPHER_CbcMacAuth(pstParam);
	up(&g_CipherMutexKernel);
    return ret;
}

EXPORT_SYMBOL(HI_DRV_CIPHER_CreateHandle);
EXPORT_SYMBOL(HI_DRV_CIPHER_ConfigChn);
EXPORT_SYMBOL(HI_DRV_CIPHER_DestroyHandle);
EXPORT_SYMBOL(HI_DRV_CIPHER_Encrypt);
EXPORT_SYMBOL(HI_DRV_CIPHER_Decrypt);
EXPORT_SYMBOL(HI_DRV_CIPHER_EncryptMulti);
EXPORT_SYMBOL(HI_DRV_CIPHER_DecryptMulti);
EXPORT_SYMBOL(HI_DRV_CIPHER_GetRandomNumber);
EXPORT_SYMBOL(HI_DRV_CIPHER_GetHandleConfig);
EXPORT_SYMBOL(HI_DRV_CIPHER_SoftReset);
EXPORT_SYMBOL(HI_DRV_CIPHER_CalcHashInit);
EXPORT_SYMBOL(HI_DRV_CIPHER_CalcHashUpdate);
EXPORT_SYMBOL(HI_DRV_CIPHER_CalcHashFinal);
EXPORT_SYMBOL(HI_DRV_CIPHER_LoadHdcpKey);
EXPORT_SYMBOL(HI_DRV_CIPHER_Resume);
EXPORT_SYMBOL(HI_DRV_CIPHER_Suspend);

