/******************************************************************************
 *
 * Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : drv_cipher.c
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2013-12-28
 * Last Modified :
 * Description   : 
 * Function List :
 * History       :
 * ******************************************************************************/
#include "hi_mmz.h"
#include "hi_type.h"
#include "sre_hwi.h"
#include "secure_gic_init.h"
#include "drv_cipher_define.h"
#include "hal_cipher.h"
#include "drv_cipher.h"
#include "drv_cipher_define.h"
#include <boot.h>
#include "sre_sem.h"

//#define CIPHER_HASH_SW

#define CI_BUF_LIST_SetIVFlag(u32Flags)
#define CI_BUF_LIST_SetEndFlag(u32Flags)

typedef struct hiCIPHER_IV_VALUE_S
{
    HI_U32 u32PhyAddr;
    HI_U32 *pu32VirAddr;
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

typedef struct
{
    HI_U32 u32TotalPkg;
    HI_U32 u32CurrentPtr;
    HI_U32 u32BusyCnt;
    HI_U32 u32FreeCnt;
} CIPHER_PKGN_MNG_S;

typedef struct
{
    HI_U32 au32Data[4];
} CIPHER_PKG1_MNG_S;

typedef union
{
    CIPHER_PKGN_MNG_S stPkgNMng;
    CIPHER_PKG1_MNG_S stPkg1Mng;
}CIPHER_DATA_MNG_U;

typedef struct
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

typedef struct
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
    SEM_HANDLE_T          uwSemHandle;
}CIPHER_SOFTCHAN_S;

extern HI_U32 g_u32CipherStartCase;


typedef struct hiCIPHER_COMM_S
{
    MMZ_BUFFER_S        stPhyBuf;
} CIPHER_COMM_S;
extern HI_U32 g_u32CipherEndCase;

static CIPHER_COMM_S g_stCipherComm;
static CIPHER_CHAN_S g_stCipherChans[CIPHER_CHAN_NUM];
CIPHER_SOFTCHAN_S g_stCipherSoftChans[CIPHER_SOFT_CHAN_NUM];

#define sw_memcpy memcpy
#define sw_memset memset

HI_S32 DRV_CipherInitHardWareChn(HI_U32 chnId )
{
    HI_U32        i;

    HAL_Cipher_SetInBufNum(chnId, CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetInBufCnt(chnId, 0);

    HAL_Cipher_SetOutBufNum(chnId, CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetOutBufCnt(chnId, CIPHER_MAX_LIST_NUM);

    HAL_Cipher_SetAGEThreshold(chnId, CIPHER_INT_TYPE_OUT_BUF, 0);
    HAL_Cipher_SetAGEThreshold(chnId, CIPHER_INT_TYPE_IN_BUF, 0);

    HAL_Cipher_DisableInt(chnId, CIPHER_INT_TYPE_OUT_BUF | CIPHER_INT_TYPE_IN_BUF);

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
HI_S32 DRV_Cipher_OpenChn(HI_U32 softChnId)
{
    HI_S32 ret = 0;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    pSoftChan->u32HardWareChn = softChnId;

    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];

    HAL_Cipher_SetIntThreshold(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF, CIPHER_DEFAULT_INT_NUM);
//    ret = HAL_Cipher_EnableInt(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF | CIPHER_INT_TYPE_IN_BUF);
    ret = HAL_Cipher_EnableInt(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF);

    pSoftChan->bOpen = HI_TRUE;
    return ret;
}

/*
flag soft channel closed
*/
HI_S32 DRV_Cipher_CloseChn(HI_U32 softChnId)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];

    pSoftChan->bOpen = HI_FALSE;

    return ret;
}

HI_VOID DRV_CIPHER_UserCommCallBack(HI_U32 arg)
{
    HI_INFO_CIPHER("arg=0x%x.\n", arg);

#ifdef CIPHER_INTERRUPT_ENABLE
    SRE_SemPost(g_stCipherSoftChans[arg].uwSemHandle);
#endif
    return ;
}

HI_S32 DRV_Cipher_ConfigChn(HI_U32 softChnId,  HI_UNF_CIPHER_CTRL_S *pConfig, funcCipherCallback fnCallBack)
{
    HI_S32 ret = HI_SUCCESS;
    HI_BOOL bDecrypt = HI_FALSE;
    HI_BOOL bIVSet = HI_FALSE;
    CIPHER_CHAN_S *pChan = NULL;
    CIPHER_SOFTCHAN_S *pSoftChan = NULL;
    HI_U32 hardWareChn = 0;
	if ( NULL == pConfig )
	{
        HI_ERR_CIPHER("Error, null pointer!\n");
	    return HI_FAILURE;
	}
    pSoftChan = &g_stCipherSoftChans[softChnId];
	hardWareChn = pSoftChan->u32HardWareChn;
    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];
    pSoftChan->pfnCallBack = (fnCallBack != HI_NULL ? fnCallBack : DRV_CIPHER_UserCommCallBack);
    bIVSet = (pConfig->stChangeFlags.bit1IV & 0x1) ? HI_TRUE : HI_FALSE;
    
    ret = HAL_Cipher_Config(pChan->chnId, bDecrypt, bIVSet, pConfig);

    pSoftChan->bIVChange = bIVSet;
    pSoftChan->bKeyChange = HI_TRUE;

    sw_memcpy(&(pSoftChan->stCtrl), pConfig, sizeof(HI_UNF_CIPHER_CTRL_S));
    if((pSoftChan->bKeyChange) && (HI_TRUE == pConfig->bKeyByCA))
    {
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

HI_S32 DRV_Cipher_GetHandleConfig(HI_U32 u32SoftChanId, HI_UNF_CIPHER_CTRL_S *pCipherCtrl)
{
    CIPHER_SOFTCHAN_S *pSoftChan;

    if(pCipherCtrl == NULL)
    {
        HI_ERR_CIPHER("Error! NULL pointer!\n");
        return HI_FAILURE;
    }

    pSoftChan = &g_stCipherSoftChans[u32SoftChanId];

    sw_memcpy(pCipherCtrl, &(pSoftChan->stCtrl), sizeof(HI_UNF_CIPHER_CTRL_S));
    
    return HI_SUCCESS;
}

static HI_VOID DRV_Cipher_SetHdcpModeEn(HI_DRV_CIPHER_HDCP_KEY_MODE_E enMode)
{
    HAL_Cipher_SetHdcpModeEn(enMode);
    return;
}

HI_S32 DRV_Cipher_GetHdcpModeEn(HI_DRV_CIPHER_HDCP_KEY_MODE_E *penMode)
{
    return HAL_Cipher_GetHdcpModeEn(penMode);    
}

static HI_VOID DRV_Cipher_SetHdcpKeyRamMode(HI_DRV_CIPHER_HDCP_KEY_RAM_MODE_E enMode)
{
    HAL_Cipher_SetHdcpKeyRamMode(enMode);
    return;
}

static HI_S32 DRV_Cipher_SetHdcpKeySelectMode(HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enHdcpKeySelectMode)
{
    return HAL_Cipher_SetHdcpKeySelectMode(enHdcpKeySelectMode);
}

HI_S32 DRV_Cipher_GetHdcpKeySelectMode(HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E *penHdcpKeySelectMode)
{
    return HAL_Cipher_GetHdcpKeySelectMode(penHdcpKeySelectMode);
}

HI_S32 DRV_Cipher_HdcpParamConfig(HI_DRV_CIPHER_HDCP_KEY_MODE_E enHdcpEnMode, HI_DRV_CIPHER_HDCP_KEY_RAM_MODE_E enRamMode, HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enKeyType)
{ 
    DRV_Cipher_SetHdcpModeEn(enHdcpEnMode);    
    DRV_Cipher_SetHdcpKeyRamMode(enRamMode);
    return DRV_Cipher_SetHdcpKeySelectMode(enKeyType);
}

static HI_VOID DRV_Cipher_ClearHdcpConfig(HI_VOID)
{    
    HAL_Cipher_ClearHdcpCtrlReg();
    return;
}
HI_UNF_CIPHER_CTRL_S* DRV_Cipher_GetHandleConfig_ptr(HI_U32 u32SoftChanId)
{
    return &(g_stCipherSoftChans[u32SoftChanId].stCtrl);
}

HI_S32 DRV_Cipher_GetIVOut(HI_U32 u32SoftChanId, HI_U8 *pu8IVOut)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    
    if(pu8IVOut == NULL)
    {
        HI_ERR_CIPHER("Error! NULL pointer!\n");
        return HI_FAILURE;
    }

    sw_memset(&stCipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    ret = HAL_Cipher_GetOutIV(u32SoftChanId, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Get out IV failure!\n");
        return HI_FAILURE;
    }
    sw_memcpy(pu8IVOut, stCipherCtrl.u32IV, CI_IV_SIZE);
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

    HAL_Cipher_SetInIV(0, &(pSoftChan->stCtrl));

    HAL_Cipher_SetKey(0, &(pSoftChan->stCtrl));
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
    HI_U32 BusyCnt;
    HI_U32 currentPtr;
    CI_BUF_LIST_ENTRY_S *pInBuf;
    CI_BUF_LIST_ENTRY_S *pOutBuf;

    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    hardWareChn = pSoftChan->u32HardWareChn;
    pChan = &g_stCipherChans[hardWareChn];
    HAL_Cipher_GetInBufCnt(hardWareChn, &BusyCnt);
//    HI_INFO_CIPHER("ibuf_cnt, reg 0x%08x is 0x%x\n", CIPHER_REG_CHANn_IBUF_CNT(hardWareChn), BusyCnt);
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
            sw_memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
                pSoftChan->stCtrl.u32IV, CI_IV_SIZE);

            pInBuf->u32IVStartAddr
                = pChan->astCipherIVValue[currentPtr].u32PhyAddr;

            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_IVSET_BIT);
        }
        else
        {
#if 1       /* for 1 pkg task,  save IV for next pkg unless user config the handle again */
            pInBuf->u32Flags &= ~(1 << CI_BUF_LIST_FLAG_IVSET_BIT); 
#else
			sw_memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
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

//        HI_INFO_CIPHER("obuf_cnt, reg 0x%08x is 0x%x\n", CIPHER_REG_CHANn_OBUF_CNT(hardWareChn), BusyCnt);
        
#if 0
        HI_ERR_CA("%s %x->%x, LEN:%x\n", pBuf2Process->bDecrypt ? "Dec" : "ENC",
                pBuf2Process->u32src, pBuf2Process->u32dest,
                pBuf2Process->u32length );
#endif

        HAL_Cipher_SetInBufCnt(hardWareChn, 1); /* +1 */


    }
    else
    {
        return HI_FAILURE;
    }

    return ret;
}


HI_S32 DRV_Cipher_CreatMultiPkgTask(HI_U32 softChnId, HI_DRV_CIPHER_DATA_INFO_S *pBuf2Process, HI_U32 pkgNum, HI_U32 callBackArg)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 hardWareChn;
    HI_U32 BusyCnt, i;
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
        HAL_Cipher_SetKey(hardWareChn, &(pSoftChan->stCtrl));
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
            sw_memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
                pSoftChan->stCtrl.u32IV, CI_IV_SIZE);

            pInBuf->u32IVStartAddr
                = pChan->astCipherIVValue[currentPtr].u32PhyAddr;

            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_IVSET_BIT);
        }
        else
        {
#if 0       
			pInBuf->u32Flags &= ~(1 << CI_BUF_LIST_FLAG_IVSET_BIT); 
#else  /* for multi pkg task, reset IV(use the user configed IV ) each time. */
			sw_memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
				pSoftChan->stCtrl.u32IV, CI_IV_SIZE);

			pInBuf->u32IVStartAddr
				= pChan->astCipherIVValue[currentPtr].u32PhyAddr;

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

    return ret;
}

/*
*/
HI_S32 DRV_Cipher_CreatTask(HI_U32 softChnId, HI_DRV_CIPHER_TASK_S *pTask, HI_U32 *pKey, HI_U32 *pIV)
{
    HI_S32 ret;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;
    pSoftChan = &g_stCipherSoftChans[softChnId];
    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];

    if (pKey)
    {
        pSoftChan->bKeyChange = HI_TRUE;
        sw_memcpy(pSoftChan->stCtrl.u32Key, pKey, CI_KEY_SIZE);
    }
    if (pIV)
    {
        pSoftChan->bIVChange = HI_TRUE;
        sw_memcpy(pSoftChan->stCtrl.u32IV, pIV, CI_IV_SIZE);
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
        HI_ERR_CIPHER("can't create task, ERR=%x.\n", ret);
        return ret;
    }

    CIPHER_MSLEEP(1);
    return HI_SUCCESS;
}

HI_S32 DRV_CipherDataDoneSinglePkg(HI_U32 chnId)
{
    CIPHER_SOFTCHAN_S *pSoftChan;

    HI_ERR_CIPHER("Data DONE, hwChn:%d\n", chnId);
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
    HI_U32 currentPtr;
    HI_U32 softChnId;
    HI_U32 fullCnt;
    HI_U32 i, idx;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;
    CI_BUF_LIST_ENTRY_S *pInBuf;
    CI_BUF_LIST_ENTRY_S *pOutBuf;

    pChan = &g_stCipherChans[chnId];
//    HI_ERR_CA("Data DONE, hwChn:%d\n", chnId);

    currentPtr = pChan->unOutData.stPkgNMng.u32CurrentPtr;

//    HI_ERR_CA("Data DONE, hwChn:%u, currentPtr=%u\n", chnId, currentPtr);

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
    }

//    HI_INFO_CA("chnId=%d, idx=%d, fullCnt=%d \n", chnId, idx, fullCnt);

    if (fullCnt > 0) /* have list entry */
    {
        for (i = 0; i < fullCnt; i++)
        {
//            idx = currentPtr;

            softChnId = pChan->au32WitchSoftChn[idx];
            pChan->au32WitchSoftChn[idx] = CIPHER_INVALID_CHN;

            pSoftChan = &g_stCipherSoftChans[softChnId];
            pSoftChan->u32LastPkg = idx;
//            HI_INFO_CA("softChnId=%d, idx=%u, needCallback:%d\n", softChnId, idx, pChan->bNeedCallback[idx]);
            if (pSoftChan->pfnCallBack && pChan->bNeedCallback[idx])
            {
//                HI_INFO_CA("CallBack function\n");
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

//        HI_U32 value;
//        CIPHER_READ_REG(REG_CI_CHANn_OBUF_CNT(chnId),value);
//        HI_INFO_CA("obuf_cnt, reg 0x%08x is 0x%x\n", REG_CI_CHANn_OBUF_CNT(chnId), value);

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
        HI_ERR_CIPHER("INTSt:%x\n", regValue);

        HAL_Cipher_GetIntEnState(&regValue);
        HI_ERR_CIPHER("INTEnSt:%x\n", regValue);

        HAL_Cipher_GetRawIntState(&regValue);
        HI_ERR_CIPHER("INTRawSt:%x\n", regValue);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_Cipher_Stat(HI_U32 chnId, HI_U32 *pCipherStat)
{
    if (NULL == pCipherStat)
    {
        HI_ERR_CIPHER("Parameters Error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HAL_Cipher_Stat(chnId, pCipherStat);
}

#ifdef CIPHER_INTERRUPT_ENABLE


/* interrupt routine, callback */
HI_VOID DRV_Cipher_ISR(HWI_ARG_T arg)
{
    HI_U32 i;
    HI_U32 INTValue = 0;

    HI_PRINT("DRV_Cipher_ISR...\n");

    HAL_Cipher_GetIntState(&INTValue);
    HAL_Cipher_ClrIntState(INTValue);

//    HI_PRINT("in the isr INTValue=0x%x!\n", INTValue);
    
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
}
#endif

HI_S32 DRV_Cipher_Init(HI_VOID)
{
    HI_U32 i,j, hwChnId, ChnIdx;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 bufSizeChn = 0; /* all the buffer list size, included data buffer size and IV buffer size */
    HI_U32 databufSizeChn = 0; /* max list number data buffer size */
    HI_U32 ivbufSizeChn = 0; /* all the list IV size */
    HI_U32 bufSizeTotal = 0; /* all the channel buffer size */
    HI_U32 u32ClrAllInt;
    MMZ_BUFFER_S   cipherListBuf;
    CIPHER_CHAN_S *pChan;

    sw_memset(&g_stCipherComm, 0, sizeof(g_stCipherComm));
    sw_memset(&g_stCipherChans, 0, sizeof(g_stCipherChans));
    sw_memset(&g_stCipherSoftChans, 0, sizeof(g_stCipherSoftChans));

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
    sw_memset((void*)&cipherListBuf, 0, sizeof(MMZ_BUFFER_S));
    cipherListBuf.u32Size = bufSizeTotal;

    cipherListBuf.u32StartPhyAddr = new_mmb("CIPHER_DRV", bufSizeTotal, SECURE_MEM, "SEC-MMZ");
    if(cipherListBuf.u32StartPhyAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_NEW() for cipher failed\n");
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    cipherListBuf.u32StartVirAddr = (unsigned int)remap_mmb(cipherListBuf.u32StartPhyAddr);
    if(cipherListBuf.u32StartVirAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_MAP() for cipher failed, PhyAddr=0x%x\n", cipherListBuf.u32StartPhyAddr);
        (HI_VOID)delete_mmb(cipherListBuf.u32StartPhyAddr);
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    sw_memset((void*)(cipherListBuf.u32StartVirAddr), 0, cipherListBuf.u32Size);

    /* save the whole memory info, included physical address, virtual address and their size */
    sw_memcpy(&(g_stCipherComm.stPhyBuf), &(cipherListBuf), sizeof(g_stCipherComm.stPhyBuf));

    /* assign hardware channel ID from 0 to 7 */
    for (i = 0; i < CIPHER_CHAN_NUM; i++)
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
    for (i = CIPHER_PKGxN_CHAN_MIN; i <= CIPHER_PKGxN_CHAN_MAX; i++)
    {
        /* config channel from 1 to 7 */
        hwChnId = i;
        ChnIdx = i - CIPHER_PKGxN_CHAN_MIN; 
        pChan = &g_stCipherChans[hwChnId];

        pChan->astCipherIVValue[0].u32PhyAddr
            = cipherListBuf.u32StartPhyAddr + (ChnIdx * bufSizeChn);
        pChan->astCipherIVValue[0].pu32VirAddr
            = (HI_U32*)(cipherListBuf.u32StartVirAddr + (ChnIdx * bufSizeChn));

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

    u32ClrAllInt = 0x00;
    for (i = CIPHER_PKGxN_CHAN_MIN; i <= CIPHER_PKGxN_CHAN_MAX; i++)
    {
        u32ClrAllInt |= 0x01 << i;
        u32ClrAllInt |= 0x01 << (i+8);
    }
    u32ClrAllInt |= 0x01 << 16;
    HAL_Cipher_ClrIntState(u32ClrAllInt);

#ifdef CIPHER_INTERRUPT_ENABLE
    ret  = SRE_HwiCreate(CIPHER_IRQ_NUMBER, 0xa0, INT_SECURE, DRV_Cipher_ISR, HI_NULL);
    if(SRE_OK != ret)
    {
        HI_ERR_CIPHER("HW int create failure, ret=0x%x.", ret);
        HAL_Cipher_DisableAllInt();
        (void)unmap_mmb((void*)g_stCipherComm.stPhyBuf.u32StartVirAddr);
        (void)delete_mmb(g_stCipherComm.stPhyBuf.u32StartPhyAddr);
        return HI_FAILURE;
    }
    ret = SRE_HwiEnable(CIPHER_IRQ_NUMBER);
    if(SRE_OK != ret)
    {
        HI_ERR_CIPHER("HW int enable failure, ret=0x%x.", ret);
        HAL_Cipher_DisableAllInt();
        (void)unmap_mmb((void*)g_stCipherComm.stPhyBuf.u32StartVirAddr);
        (void)delete_mmb(g_stCipherComm.stPhyBuf.u32StartPhyAddr);
        return HI_FAILURE;
    }
    for (i = CIPHER_PKGxN_CHAN_MIN; i <= CIPHER_PKGxN_CHAN_MAX; i++)
    {
        SRE_SemCreate(0, &g_stCipherSoftChans[i].uwSemHandle);;
    }
#endif

    HAL_Cipher_EnableAllSecChn();
    
    return ret;
}

HI_VOID DRV_Cipher_DeInit(HI_VOID)
{
    HI_U32 i, hwChnId;
    HI_U32 u32ClrAllInt;
//  HI_U32  REG_SYS_BASE_ADDR_VIRT = 0;

    u32ClrAllInt = 0x00;
    for (i = CIPHER_PKGxN_CHAN_MIN; i <= CIPHER_PKGxN_CHAN_MAX; i++)
    {
        u32ClrAllInt |= 0x01 << i;
        u32ClrAllInt |= 0x01 << (i+8);
    }
    u32ClrAllInt |= 0x01 << 16;

    HAL_Cipher_DisableAllInt();
    HAL_Cipher_ClrIntState(u32ClrAllInt);

    for (i = CIPHER_PKGxN_CHAN_MIN; i <= CIPHER_PKGxN_CHAN_MAX; i++)
    {
        hwChnId = i;
        DRV_CipherDeInitHardWareChn(hwChnId);
#ifdef CIPHER_INTERRUPT_ENABLE
        SRE_SemDelete(g_stCipherSoftChans[i].uwSemHandle);
#endif
    }

    if(g_stCipherComm.stPhyBuf.u32StartVirAddr != 0)
    {
        (void)unmap_mmb((void*)g_stCipherComm.stPhyBuf.u32StartVirAddr);
    }
    if(g_stCipherComm.stPhyBuf.u32StartPhyAddr != 0)
    {
        (void)delete_mmb(g_stCipherComm.stPhyBuf.u32StartPhyAddr);
    }
    sw_memset(&g_stCipherComm.stPhyBuf, 0, sizeof(MMZ_BUFFER_S));

    HAL_Cipher_DeInit();

    return;
}

HI_S32 DRV_Cipher_waitStat(HI_U32 chnId)
{
#ifdef CIPHER_INTERRUPT_ENABLE
    HI_S32 ret;
    
    ret = SRE_SemPend(g_stCipherSoftChans[chnId].uwSemHandle, OS_WAIT_FOREVER);
    if (ret != SRE_OK)
    {
        HI_ERR_CIPHER("DRV_Cipher_waitStat handle too long \n");
        return HI_FAILURE;      /* overtime */
    }

#else
    HI_U32 cnt;
    HI_U32 cipherStat;
    cnt = 0;
    while (cnt < 1000000)
    {
        DRV_Cipher_Stat(chnId, &cipherStat);
        if (CIPHER_PKGx1_CHAN == chnId)
        {
            if (cipherStat == 0)
            {
                break;
            }
        }
        else
        {
            if (cipherStat == 1)
            {
                break;
            }
        }
        CIPHER_MSLEEP(1);
        cnt++;
    }
    if (cnt >= 1000000)
    {
        HI_ERR_CIPHER("DRV_Cipher_waitStat handle too long \n");
        return HI_FAILURE;      /* overtime */
    }
    DRV_CipherDataDoneMultiPkg(chnId);
#endif
    return HI_SUCCESS;        /* success */
}
#if 0
// support powerdown step 0
HI_VOID  DRV_Cipher_Suspend(HI_VOID)
{
    return;
}
// support powerdown step 0
//reset cipher module!
HI_VOID DRV_Cipher_Resume(HI_VOID)
{
    HI_U32 i; 
    HI_U32 ret;
    HI_U32 hwChnId;
    //HI_U32 bufSizeChn;
    HI_U32 ivbufSizeChn;
    HI_U32 databufSizeChn;
    //HI_U32 bufSizeTotal;
    CIPHER_CHAN_S *pChan;
    // 0
    databufSizeChn = sizeof(CI_BUF_LIST_ENTRY_S) * CI_MAX_LIST_NUM;
    ivbufSizeChn = CI_IV_SIZE * CI_MAX_LIST_NUM;
    //bufSizeChn = (databufSizeChn * 2) + ivbufSizeChn;/* inBuf + outBuf + keyBuf */
    //bufSizeTotal = bufSizeChn * (CI_PKGxN_CHAN_MAX - CI_PKGxN_CHAN_MIN + 1) ; /* only 7 channels need buf */
    // 2
    HAL_Cipher_Init();
    HAL_Cipher_DisableAllInt();
    for (i = 0; i < CI_PKGxN_CHAN_MAX; i++)
    {
        hwChnId = i+CI_PKGxN_CHAN_MIN;
        pChan = &g_stCipherChans[hwChnId];

        pChan->pstInBuf = (CI_BUF_LIST_ENTRY_S*)((HI_U32)(pChan->astCipherIVValue[0].pu32VirAddr) + ivbufSizeChn);
        pChan->pstOutBuf = (CI_BUF_LIST_ENTRY_S*)((HI_U32)(pChan->pstInBuf) + databufSizeChn);

        HAL_Cipher_SetBufAddr(hwChnId, CIPHER_BUF_TYPE_IN, pChan->astCipherIVValue[0].u32PhyAddr + ivbufSizeChn);
        HAL_Cipher_SetBufAddr(hwChnId, CIPHER_BUF_TYPE_OUT, pChan->astCipherIVValue[0].u32PhyAddr + ivbufSizeChn + databufSizeChn);

        DRV_CipherInitHardWareChn(hwChnId);
    }
    
    HAL_Cipher_GetIntState(&ret);
    HAL_Cipher_DisableAllInt();

    
    HAL_Cipher_ClrIntState(0xffffffff);
    
    return;
}
#endif

static HI_U32 g_u32HashHandleSeed = 0xa0000000;
static HI_HANDLE g_hashHandle = -1;

#ifdef CIPHER_HASH_SW

static sha1_context g_sha1Context;
static sha2_context g_sha2Context;
static HI_BOOL g_is224 = HI_FALSE;

HI_S32 DRV_Cipher_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;


    (HI_VOID)Cipher_GetRandomNumber(&g_hashHandle);
    
    /* 56 = 64 - 8, 120 = 56 + 64 */
    /* add 8 bytes fix data length */

    /* Format(binary): {data|1000...00| fix_data_len(bits)} */
    switch(pCipherHashData->enShaType)
    /* write 8 bytes fix data length */

    {
	    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
        {
	        (HI_VOID)sha1_starts(&g_sha1Context);
	        pCipherHashData->hHandle = g_hashHandle;
	        break;
	    }
	    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
		{
	        g_is224 = HI_FALSE;
	        (HI_VOID)sha2_starts(&g_sha2Context, g_is224);
	        pCipherHashData->hHandle = g_hashHandle;
	        break;
	    }
	    default:
	    {
	       HI_ERR_CIPHER("Invalid hash type!\n");
	       pCipherHashData->hHandle = -1;
	       ret = HI_FAILURE;
	       break;
	    }
	}
    return ret;
}

#else

static MMZ_BUFFER_S  s_mmzHashBuf;

HI_S32 DRV_Cipher_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;

    g_hashHandle = g_u32HashHandleSeed++;
    pCipherHashData->hHandle = g_hashHandle;

    s_mmzHashBuf.u32StartPhyAddr = new_mmb("HASH_DRV", SECURE_MEM_CIPHER_MAX_SIZE+HASH_PAD_MAX_LEN, NON_SECURE_MEM, "NONSEC-MMZ");
    if(s_mmzHashBuf.u32StartPhyAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_NEW() for hash failed\n");
        return HI_ERR_CIPHER_FAILED_INIT;
    }
    s_mmzHashBuf.u32StartVirAddr = (unsigned int)remap_mmb(s_mmzHashBuf.u32StartPhyAddr);
    if(s_mmzHashBuf.u32StartVirAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_MAP() for hash failed, PhyAddr=0x%x\n", s_mmzHashBuf.u32StartPhyAddr);
        (HI_VOID)delete_mmb(s_mmzHashBuf.u32StartPhyAddr);
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    sw_memset((void*)(s_mmzHashBuf.u32StartVirAddr), 0, s_mmzHashBuf.u32Size);
    s_mmzHashBuf.u32Size = 0;
        
    ret = HAL_Cipher_CalcHashInit(pCipherHashData);
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("Cipher hash init failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}
#endif

#ifdef CIPHER_HASH_SW
HI_S32 DRV_Cipher_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;

    if ( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Invalid Param, null poiner!\n");
        return HI_FAILURE;
    }

    if(pCipherHashData->hHandle != g_hashHandle)
    {
        HI_ERR_CIPHER("Invalid hash handle!\n");
        return HI_FAILURE;
    }
    
    switch(pCipherHashData->enShaType)
    {
        case HI_UNF_CIPHER_HASH_TYPE_SHA1:
		{
            (HI_VOID)sha1_update(&g_sha1Context, pCipherHashData->pu8InputData, pCipherHashData->u32InputDataLen);
            break;
        }
        case HI_UNF_CIPHER_HASH_TYPE_SHA256:
		{
            (HI_VOID)sha2_update(&g_sha2Context, pCipherHashData->pu8InputData, pCipherHashData->u32InputDataLen);
            break;
        }
        default:
		{
            HI_ERR_CIPHER("Invalid hash type!\n");
            ret = HI_FAILURE;
            break;
        }
    }

    return ret;
}

#else 

HI_S32 DRV_Cipher_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 *pu8InputData;
    HI_U32 u32InputDataLen;
    HI_U32 u32BlockCnt, u32BlockLeft;

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

    sw_memcpy((HI_U8*)s_mmzHashBuf.u32StartVirAddr+s_mmzHashBuf.u32Size, pCipherHashData->pu8InputData, pCipherHashData->u32InputDataLen);

    u32InputDataLen = pCipherHashData->u32InputDataLen;
    pu8InputData = pCipherHashData->pu8InputData;
    pCipherHashData->u32TotalDataLen += pCipherHashData->u32InputDataLen;
    pCipherHashData->pu8InputData = (HI_U8*)s_mmzHashBuf.u32StartPhyAddr;
    u32BlockCnt = (pCipherHashData->u32InputDataLen + s_mmzHashBuf.u32Size) / HASH_BLOCK_SIZE;
    u32BlockLeft = (pCipherHashData->u32InputDataLen + s_mmzHashBuf.u32Size) % HASH_BLOCK_SIZE;
    if (u32BlockCnt > 0)
    {
        pCipherHashData->u32InputDataLen = u32BlockCnt * HASH_BLOCK_SIZE;
        ret = HAL_Cipher_CalcHashUpdate(pCipherHashData);
        if(HI_FAILURE == ret)
        {
            HI_ERR_CIPHER("Cipher hash update failed!\n");
            return HI_FAILURE;
        }
        sw_memcpy((HI_U8*)s_mmzHashBuf.u32StartVirAddr, pu8InputData + u32InputDataLen - u32BlockLeft, u32BlockLeft);
        s_mmzHashBuf.u32Size = u32BlockLeft;
    }
    else
    {
        sw_memcpy((HI_U8*)s_mmzHashBuf.u32StartVirAddr + s_mmzHashBuf.u32Size, pu8InputData, u32InputDataLen);
        s_mmzHashBuf.u32Size += u32InputDataLen;
    }
    return HI_SUCCESS;
}
#endif

#ifdef CIPHER_HASH_SW
HI_S32 DRV_Cipher_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;

    if ( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Invalid Param, null poiner!\n");
        return HI_FAILURE;
    }

    if(pCipherHashData->hHandle != g_hashHandle)
    {
        HI_ERR_CIPHER("Invalid hash handle!\n");
        return HI_FAILURE;
    }

    (HI_VOID)Cipher_GetRandomNumber(&g_hashHandle);

    switch(pCipherHashData->enShaType)
    {
	    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
	    {
	        (HI_VOID)sha1_finish(&g_sha1Context, pCipherHashData->pu8Output);
	        break;
	    }
	    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
		{
	        (HI_VOID)sha2_finish(&g_sha2Context, pCipherHashData->pu8Output);
	        break;
	    }
	    default:
		{
	       HI_ERR_CIPHER("Invalid hash type!\n");
	       ret = HI_FAILURE;
	       break;
	    }
	}

	return ret;
}

#else

static HI_S32 Cipher_HashMsgPadding(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_U32 u32Tmp = 0;
    HI_U32 i = 0;
    HI_U8 *pu8PadLen;

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error! Null pointer input!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }
    sw_memset(pCipherHashData->u8Padding, 0, sizeof(pCipherHashData->u8Padding));
    u32Tmp = pCipherHashData->u32TotalDataLen % HASH_PAD_MAX_LEN;
    /* 56 = 64 - 8, 120 = 56 + 64 */
    pCipherHashData->u32PaddingLen = (u32Tmp < 56) ? (56 - u32Tmp) : (120 - u32Tmp);
    /* add 8 bytes fix data length */
    pCipherHashData->u32PaddingLen += 8;
    /* Format(binary): {data|1000...00| fix_data_len(bits)} */
    sw_memset(pCipherHashData->u8Padding, 0x80, 1);
    sw_memset(pCipherHashData->u8Padding + 1, 0, pCipherHashData->u32PaddingLen - 1 - 8);
    /* write 8 bytes fix data length */
    u32Tmp = pCipherHashData->u32TotalDataLen;
    pu8PadLen = pCipherHashData->u8Padding + pCipherHashData->u32PaddingLen - 8;
#if 0
    if( (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pCipherHashData->enShaType)
     || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pCipherHashData->enShaType) )
    {
        for (i = 0; i < 8; i++)
        {
            u8PadLen[i] = ((u32Tmp * 8 + 512) >> (7 - i) * 8) & 0xff;
        }
    }
    else
#endif
    {
        for (i = 0; i < 8; i++)
        {
            pu8PadLen[i] = ((u32Tmp * 8) >> ((7 - i) * 8)) & 0xff;
        }
    }

    return HI_SUCCESS;
}

HI_S32 DRV_Cipher_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Tmp;
    HI_U8 *pu8InputData;

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
    
    ret = Cipher_HashMsgPadding(pCipherHashData);
	if ( HI_SUCCESS != ret )
	{
        HI_ERR_CIPHER("Error, hash message padding failed!\n");
	    return ret;
	}

	/* the remained data length must be 64 bytes aligned */
	u32Tmp = (s_mmzHashBuf.u32Size + pCipherHashData->u32PaddingLen) % HASH_BLOCK_SIZE;
	if ( 0 != u32Tmp)
	{
	    HI_ERR_CIPHER("Error, invalid length for hash final!\n");
		return HI_FAILURE;
	}

	sw_memcpy((HI_U8 *)s_mmzHashBuf.u32StartVirAddr + s_mmzHashBuf.u32Size,
				pCipherHashData->u8Padding,
				pCipherHashData->u32PaddingLen);
    pu8InputData = pCipherHashData->pu8InputData;
    pCipherHashData->pu8InputData = (HI_U8*)s_mmzHashBuf.u32StartPhyAddr;
	pCipherHashData->u32InputDataLen = s_mmzHashBuf.u32Size + pCipherHashData->u32PaddingLen;

    ret = HAL_Cipher_CalcHashFinal(pCipherHashData);
    if(HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("Cipher hash final failed!\n");
        return HI_FAILURE;
    }

    if(s_mmzHashBuf.u32StartVirAddr != 0)
    {
        (void)unmap_mmb((void*)s_mmzHashBuf.u32StartVirAddr);
    }
    if(s_mmzHashBuf.u32StartPhyAddr != 0)
    {
        (void)delete_mmb(s_mmzHashBuf.u32StartPhyAddr);
    }
    s_mmzHashBuf.u32Size = 0;
    
    pCipherHashData->pu8InputData = pu8InputData;

    return HI_SUCCESS;
}
#endif

#define P32 0xEDB88320L
static HI_S32 crc_tab32_init = 0;
static HI_U32 crc_tab32[256];
static HI_VOID init_crc32_tab( HI_VOID ) 
{
    HI_U32 i,j;
    HI_U32 u32Crc = 0;
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

HI_S32 DRV_CIPHER_CalcHDCPKeyCRC32( HI_U8* pu8Buff,HI_U32 length, HI_U32 *pu32Crc32Result)
{
    HI_U32 u32Crc32 = 0xffffffffL;
    HI_U32 i = 0;

    if ( (NULL == pu32Crc32Result) || (NULL == pu8Buff) )
    {
        return HI_FAILURE;
    }
    
    if (!crc_tab32_init)
	{
		init_crc32_tab();
    }

    for(i=0 ; i < length ; i++)
	{
        u32Crc32 = update_crc_32(u32Crc32,(char)pu8Buff[i]);
    }

    u32Crc32 ^= 0xffffffffL;

    *pu32Crc32Result = u32Crc32;
    
    return HI_SUCCESS;
}

HI_VOID DRV_Cipher_FormatHDCPKey(HI_UNF_HDCP_DECRYPT_S *pSrcKey, OTP_HDCPKEY_S *pDstKey)
{
	HI_S32        i;
	HI_U8         TailBytes[31] = {0x14, 0xf7, 0x61, 0x03, 0xb7, 0x59, 0x45, 0xe3,
		                           0x0c, 0x7d, 0xb4, 0x45, 0x19, 0xea, 0x8f, 0xd2, 
                                   0x89, 0xee, 0xbd, 0x90, 0x21, 0x8b, 0x05, 0xe0,
                                   0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	HI_U32        CheckSum = 0xa3c5;
    HI_U32        XorValue,Temp;

	memset(pDstKey->HdcpKey, 0, 320);

	/* Byte 0*/
    pDstKey->HdcpKey[0] = 0x00;
    /* Byte 1 ~ 5 KSV */
    for (i = 0; i < 5; i ++)
    {
        pDstKey->HdcpKey[1 + i] = pSrcKey->u8KSV[i];
    }
	/* Byte 8 */
    pDstKey->HdcpKey[8] = 0xa8;
    /* Byte 9 ~ 288 Device Private Key */
    for (i = 0; i < 280; i ++)
    {
        pDstKey->HdcpKey[9 + i] = pSrcKey->u8PrivateKey[i];
    }
    /* Byte 289 ~ 319 */
    for (i = 0; i < 31; i ++)
    {
        pDstKey->HdcpKey[289 + i] = TailBytes[i];
    }

    /* Count CRC value */
    for(i=0; i<320; i++)
    {
        if((i>=6) && (i<=8)) 
        {
	        continue;        	
        }
        XorValue = CheckSum ^ pDstKey->HdcpKey[i];
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
    pDstKey->HdcpKey[6] = CheckSum & 0xff;
    pDstKey->HdcpKey[7] = (CheckSum >> 8) & 0xff;

	return;
}

HI_S32 DRV_Cipher_CryptoFormatedHDCPKey(HI_U8 *pu8Input,
                                    HI_U32 u32InputLen, 
                                    HI_DRV_CIPHER_HDCP_KEY_MODE_E enHdcpEnMode, 
                                    HI_DRV_CIPHER_HDCP_KEY_RAM_MODE_E enRamMode,
                                    HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enKeyType,
                                    HI_BOOL bIsDecryption, 
                                    HI_U8 *pu8Output)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 softChnId = 0;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_DRV_CIPHER_TASK_S pCITask;
    HI_U32 i = 0;

    if ( NULL == pu8Input )
    {
        HI_ERR_CIPHER("Invalid param , null pointer input!\n");
        return HI_FAILURE;
    }

    if ((NULL == pu8Output ) && (HI_FALSE == bIsDecryption))
    {
        HI_ERR_CIPHER("Invalid param , null pointer!\n");
        return HI_FAILURE;
    }

    if ( CIPHER_HDCP_MODE_HDCP_KEY != enHdcpEnMode)
    {
        HI_ERR_CIPHER("Invalid HDCP mode!\n");
        return HI_FAILURE;
    }

    if ( 320 != u32InputLen)
    {
        HI_ERR_CIPHER("Invalid keylength input!\n");
        return HI_FAILURE;
    }

    ret = DRV_Cipher_OpenChn(softChnId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("(g_pCIPHERExportFunctionList_forhdcp->DRV_Cipher_OpenChn) failed\n");
        (HI_VOID)DRV_Cipher_ClearHdcpConfig();
        return HI_FAILURE;
    }

    for(i = 0;i < 20; i++)
    {
	    /* config hdcp param */
        ret = DRV_Cipher_HdcpParamConfig(enHdcpEnMode, enRamMode, enKeyType);
        if ( HI_FAILURE == ret)
        {
	        (HI_VOID)DRV_Cipher_ClearHdcpConfig();
            return HI_FAILURE;
        } 

	    memset(&CipherCtrl, 0, sizeof(CipherCtrl));
        CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
        CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
        CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;        
        memset(CipherCtrl.u32IV, 0 , sizeof(CipherCtrl.u32IV));
        CipherCtrl.stChangeFlags.bit1IV = (0 == i) ? 1 : 0;            

        ret = DRV_Cipher_ConfigChn(softChnId, &CipherCtrl, HI_NULL);
		if ( HI_SUCCESS != ret )
		{
            DRV_Cipher_ClearHdcpConfig();
            DRV_Cipher_CloseChn(softChnId);
		    HI_ERR_CIPHER("Cipher config chn failed!\n");
			return HI_FAILURE;
		}

		memset(&pCITask, 0, sizeof(pCITask));
        memcpy((HI_U8 *)(pCITask.stData2Process.u32DataPkg), pu8Input + (i * 16), 16);
        pCITask.stData2Process.u32length = 16;
        pCITask.stData2Process.bDecrypt = bIsDecryption;
        pCITask.u32CallBackArg = softChnId;
        
        ret = DRV_Cipher_CreatTask(softChnId, &pCITask, NULL, NULL);
        if (HI_SUCCESS != ret)
        {
            DRV_Cipher_ClearHdcpConfig();
            DRV_Cipher_CloseChn(softChnId);
            HI_ERR_CIPHER("DRV_Cipher_CreatTask call failed\n");
            return HI_FAILURE;
        }

        if ( NULL != pu8Output )
        {
            memcpy(pu8Output + ( i * 16), (HI_U8 *)(pCITask.stData2Process.u32DataPkg), 16);
        }
    }

    DRV_Cipher_ClearHdcpConfig();
    DRV_Cipher_CloseChn(softChnId);
    
    return HI_SUCCESS;
}

HI_S32 DRV_Cipher_DecryptHDCPKey(HI_UNF_HDCP_HDCPKEY_S *pSrcKey,  HI_UNF_HDCP_DECRYPT_S *pDstkey)
{
	HI_U32 softChnId = 7;
	HI_U8 key[16];
	HI_U8 ResultBuf[320];
	HI_S32 ret = HI_SUCCESS;
	HI_U8 VersionBuf[8];
	HI_BOOL ValidFlag = HI_TRUE;
	HI_U32 i = 0;
	HI_UNF_HDCP_ENCRYPT_S stEncryptKey;
	HI_UNF_CIPHER_CTRL_S CipherCtrl;
	MMZ_BUFFER_S encrypt_buf, decrypt_buf;
	HI_DRV_CIPHER_TASK_S stCITask;

	if(!pSrcKey->EncryptionFlag)
	{
		HI_ERR_CIPHER("EncryptionFlag Error!\n");
		return HI_FAILURE;
	}

    memset(&stEncryptKey, 0, sizeof(stEncryptKey));
	memcpy(&stEncryptKey, &pSrcKey->key, sizeof(HI_UNF_HDCP_ENCRYPT_S));
	
	softChnId = 7;
	ret = DRV_Cipher_OpenChn(softChnId);
	if (HI_SUCCESS != ret)
	{
		HI_ERR_CIPHER("Cipher open chn failed\n");
		return HI_FAILURE;
	}

    memset(&CipherCtrl, 0, sizeof(CipherCtrl));
	CipherCtrl.bKeyByCA = HI_FALSE;
	CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
	CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
	CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_8BIT;
	CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
	CipherCtrl.stChangeFlags.bit1IV = 1;

    memset(VersionBuf, 0, sizeof(VersionBuf));
	memcpy(VersionBuf, &stEncryptKey.u8EncryptKey[8], 8);
	
	for(i = 0; i < 8; ++i)
	{
		if(VersionBuf[i] != "V0000001"[i])
		{
			ValidFlag = HI_FALSE;
			i = 8;
		}
	}

	if(!ValidFlag)
	{
		HI_ERR_CIPHER("EncryptKey check version failed\n");
		(HI_VOID)DRV_Cipher_CloseChn(softChnId);
		return HI_FAILURE;
	}

	memset(key, 0, sizeof(key)); 
	key[0] = 'z';
	key[1] = 'h';
	key[2] = 'o';
	key[3] = 'n';
	key[4] = 'g'; 
	memcpy((HI_U8 *)CipherCtrl.u32Key, key, sizeof(key));
	memset(CipherCtrl.u32IV, 0, sizeof(CipherCtrl.u32IV));
	ret = DRV_Cipher_ConfigChn(softChnId, &CipherCtrl, HI_NULL);
	if ( HI_SUCCESS !=ret )
	{
	    HI_ERR_CIPHER("Cipher Config chn faliled.\n");
		(HI_VOID)DRV_Cipher_CloseChn(softChnId);
		return HI_FAILURE;
	}

#if 0
    memset(&encrypt_buf, 0, sizeof(encrypt_buf));
	if (HI_SUCCESS != HI_DRV_MMZ_AllocAndMap("EncryptBuf", MMZ_OTHERS, 320, 32, &encrypt_buf))
	{					
		HI_ERR_CIPHER("CMPI_MEM_AllocAndMapMem EncryptBuf failed\n");
		return HI_FAILURE;
	}

	memset((HI_U8 *)(encrypt_buf.u32StartVirAddr), 0x0, 320);

    memset(&decrypt_buf, 0, sizeof(decrypt_buf));
	if (HI_SUCCESS != HI_DRV_MMZ_AllocAndMap("DecryptBuf", MMZ_OTHERS, 320, 32, &decrypt_buf))
	{
		HI_DRV_MMZ_UnmapAndRelease(&encrypt_buf);
		HI_ERR_CIPHER("CMPI_MEM_AllocAndMapMem EncryptBuf failed\n");
		return HI_FAILURE;
	}
#else
    memset(&encrypt_buf, 0, sizeof(encrypt_buf));
    encrypt_buf.u32Size = 320;
    encrypt_buf.u32StartPhyAddr = new_mmb("HDCP_EncryptBuf", 320, SECURE_MEM, "test");
    if(encrypt_buf.u32StartPhyAddr == 0)
    {
        HI_ERR_CIPHER("new_mmb() for cipher failed\n");
		(HI_VOID)DRV_Cipher_CloseChn(softChnId);
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    encrypt_buf.u32StartVirAddr = (unsigned int)remap_mmb(encrypt_buf.u32StartPhyAddr);
    if(encrypt_buf.u32StartVirAddr == 0)
    {
        HI_ERR_CIPHER("new_mmb() for cipher failed, PhyAddr=0x%x\n", encrypt_buf.u32StartPhyAddr);
		(HI_VOID)delete_mmb(encrypt_buf.u32StartPhyAddr);
		(HI_VOID)DRV_Cipher_CloseChn(softChnId);
        return HI_ERR_CIPHER_FAILED_INIT;
    }
	
    memset(&decrypt_buf, 0, sizeof(decrypt_buf));
    decrypt_buf.u32Size = 320;
    decrypt_buf.u32StartPhyAddr = new_mmb("HDCP_DecryptBuf", 320, SECURE_MEM, "test");
    if(decrypt_buf.u32StartPhyAddr == 0)
    {
        HI_ERR_CIPHER("new_mmb() for cipher failed\n");
		(HI_VOID)delete_mmb(encrypt_buf.u32StartPhyAddr);
		(HI_VOID)unmap_mmb((void *)encrypt_buf.u32StartVirAddr);
		(HI_VOID)DRV_Cipher_CloseChn(softChnId);
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    decrypt_buf.u32StartVirAddr = (unsigned int)remap_mmb(decrypt_buf.u32StartPhyAddr);
    if(decrypt_buf.u32StartVirAddr == 0)
    {
        HI_ERR_CIPHER("new_mmb() for cipher failed, PhyAddr=0x%x\n", decrypt_buf.u32StartPhyAddr);
		(HI_VOID)delete_mmb(encrypt_buf.u32StartPhyAddr);
		(HI_VOID)unmap_mmb((void *)encrypt_buf.u32StartVirAddr);
		(HI_VOID)delete_mmb(decrypt_buf.u32StartPhyAddr);
		(HI_VOID)DRV_Cipher_CloseChn(softChnId);
        return HI_ERR_CIPHER_FAILED_INIT;
    }
#endif

	memset((HI_U8 *)(decrypt_buf.u32StartVirAddr), 0x0, 320);
	memcpy((HI_U8 *)encrypt_buf.u32StartVirAddr, (HI_U8 *)stEncryptKey.u8EncryptKey + 48, 320);

    memset(&stCITask, 0, sizeof(stCITask));
	stCITask.stData2Process.u32src = encrypt_buf.u32StartPhyAddr;
	stCITask.stData2Process.u32dest = decrypt_buf.u32StartPhyAddr;
	stCITask.stData2Process.u32length = 320;
	stCITask.stData2Process.bDecrypt = HI_TRUE;
	stCITask.u32CallBackArg = softChnId;
   
	ret = DRV_Cipher_CreatTask(softChnId, &stCITask, NULL, NULL);
	if (HI_SUCCESS != ret)
	{
		HI_ERR_CIPHER("(g_pCIPHERExportFunctionList_forhdcp->DRV_Cipher_CreatTask) call failed\n");
		goto __HDCP_EXIT__;
	}

    ret = DRV_Cipher_waitStat(softChnId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Cipher Decrypt hdcpkey timeout\n");
		goto __HDCP_EXIT__;
    }

    memset(&ResultBuf, 0, sizeof(ResultBuf));
	memcpy(ResultBuf, (HI_U8 *)decrypt_buf.u32StartVirAddr, 320);
	if(ResultBuf[5] || ResultBuf[6] || ResultBuf[7])
	{
		HI_ERR_CIPHER("Check bit[5:7] failed after decrypt!\n");
		ret = HI_FAILURE;
		goto __HDCP_EXIT__;
	}
	memcpy(pDstkey->u8KSV, ResultBuf, sizeof(pDstkey->u8KSV));
	memcpy(pDstkey->u8PrivateKey, ResultBuf + 8, sizeof(pDstkey->u8PrivateKey));

	HI_INFO_CIPHER("In Drv_burnhdcp:Decrypt OK, chnNum = %#x!\n", softChnId);

__HDCP_EXIT__:
	(HI_VOID)delete_mmb(encrypt_buf.u32StartPhyAddr);
	(HI_VOID)unmap_mmb((void *)encrypt_buf.u32StartVirAddr);
	(HI_VOID)delete_mmb(decrypt_buf.u32StartPhyAddr);
	(HI_VOID)unmap_mmb((void *)decrypt_buf.u32StartVirAddr);
	(HI_VOID)DRV_Cipher_CloseChn(softChnId);

	return HI_SUCCESS;
}

HI_S32 DRV_Cipher_DecryptAndFormatHDCPKey(HI_UNF_HDCP_HDCPKEY_S *pSrcKey, OTP_HDCPKEY_S *pstOtpHdcpKey)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_HDCP_DECRYPT_S DstKey;
//	int i = 0;

    if ( NULL == pstOtpHdcpKey)
    {
        HI_ERR_CIPHER("Invalid param, null pointer!\n");
        return HI_FAILURE;
    }

    memset(&DstKey, 0, sizeof(DstKey));

    if(pSrcKey->EncryptionFlag)
    {
        ret = DRV_Cipher_DecryptHDCPKey(pSrcKey, &DstKey);
        if(ret != HI_SUCCESS)
        {
        	HI_ERR_CIPHER("DRV_Cipher_DecryptHDCPKey failed!\n");
        	return HI_FAILURE;
        }
		else
		{
		    HI_INFO_CIPHER("++++++++decrypt hdcp key success+++++++++++++++\n");
		}
    }
    else
    {
        memcpy(&DstKey, &pSrcKey->key, sizeof(HI_UNF_HDCP_DECRYPT_S));
    }
#if 0
    if(pSrcKey->Reserved == 0xabcd1234)
    {
        int i;

        HI_INFO_HDCP("\n***** Debug HDCP Key, just debug HDCP key, Do not really write key *****\n");
        HI_INFO_HDCP("u8KSV:\n");
        for(i = 0; i < 5; ++i)
        {
        	HI_INFO_HDCP("%02X ", DstKey.u8KSV[i]);
        }

        HI_INFO_HDCP("\n u8PrivateKey:\n");
        for(i = 0; i < 280; ++i)
        {
        	HI_INFO_HDCP("%02X ", DstKey.u8PrivateKey[i]);
        	if(((i+1)%16) == 0)
        		HI_INFO_HDCP("\n");
        }
        HI_INFO_HDCP("\n\n");

        return HI_SUCCESS;
    }
#endif
 
    //transform HDCP key to Chip's requirement!
#if 0
    HI_INFO_CIPHER("++aksv:\n");
    HI_INFO_CIPHER("++aksv:\n");
    HI_INFO_CIPHER("++aksv:\n");
    for ( i = 0 ; i < 5 ; i++ )
    {
        HI_INFO_CIPHER("%x ", DstKey.u8KSV[i]);
    }
    HI_INFO_CIPHER("\n");
#endif
	
    DRV_Cipher_FormatHDCPKey(&DstKey, pstOtpHdcpKey);

    return HI_SUCCESS;
}

HI_VOID DRV_Cipher_HDCPTxReadEnable(HI_VOID)
{
	(HI_VOID)HAL_Cipher_HDCPTxReadEnable();
	return;
}

