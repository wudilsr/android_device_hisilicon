/******************************************************************************
 *
 * Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : drv_cipher_intf.c
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2013-12-28
 * Last Modified :
 * Description   : 
 * Function List :
 * History       :
 * ******************************************************************************/
//#include "linux/mtd/compat.h"
//#include <task.h>
//#include <sw_debug.h>
//#include <sw_wait.h>
//#include <gic.h>
//#include <libc_sos.h>
//#include <otz_tee_mem_mgmt.h>

#include "hi_type.h"
#include "drv_cipher.h"
#include "drv_cipher_intf.h"
#include "drv_cipher_define.h"
#include "sre_debug.h"
#include "hi_mmz.h"
#include "../mmz/list.h"
#include "sre_securemmu.h"
#include <boot.h>

#define HI_ID_CIPHER 0x4D

#define HI_HANDLE_MAKEHANDLE(mod, privatedata, chnid)  (HI_HANDLE)( (((mod)& 0xffff) << 16) | ((((privatedata)& 0xff) << 8) ) | (((chnid) & 0xff)) )

#define HI_HANDLE_GET_MODID(handle)    (((handle) >> 16) & 0xffff)
#define HI_HANDLE_GET_PriDATA(handle)  (((handle) >> 8) & 0xff)
#define HI_HANDLE_GET_CHNID(handle)    (((handle)) & 0xff)
#define DX_TZ_AES128_BLOCK_SIZE 16

static HI_S32 g_s32CipherInitFlag = -1;

typedef struct hiCIPHER_OSR_CHN_S
{
    HI_BOOL g_bSoftChnOpen; /* mark soft channel open or not*/
    HI_BOOL g_bDataDone;    /* mark the data done or not */
#ifdef  CIPHER_INTERRUPT_ENABLE
 //   struct wait_queue_head cipher_wait_queue; /* mutex method */
#endif
    HI_UNF_CIPHER_DATA_S *pstDataPkg;
    HI_U32                u32DataPkgNum;
}CIPHER_OSR_CHN_S;

static CIPHER_OSR_CHN_S g_stCipherOsrChn[CIPHER_SOFT_CHAN_NUM];
static HI_HANDLE  g_cipherChn = 0;          /* cipher handle */
static HI_U32 g_softChnId = 0;                  /* soft channel ID */

static HI_S32 g_HashDevFd = -1;
CIPHER_HASH_DATA_S g_stCipherHashData;

#define CIPHER_CheckHandle(softChnId) do{\
        if (HI_FALSE == g_stCipherOsrChn[softChnId].g_bSoftChnOpen)\
        {\
            HI_ERR_CIPHER("invalid chn %d, open=%d.\n", softChnId, g_stCipherOsrChn[softChnId].g_bSoftChnOpen);\
            return HI_ERR_CIPHER_INVALID_HANDLE;\
        }\
    }while(0)

#define sw_memcpy memcpy
#define sw_memset memset
#define sw_memcmp memcmp

#ifdef HI_CIPHER_TEST
extern void aes_test (void);
extern void hamc_test(void);
extern void hash_test(void);
extern void rsa_test(void);
extern void des_test(void);
extern void rsa_prim_test(void);
extern void rsa_kg_test(void);
extern void test_rnd(void);
#endif

static HI_U32 s_Cipher_RemapPhyAddr(HI_U32 u32PhyAddr)
{
	struct cpu_section stCpuSection;
    UINT32 *pgd = secure_page_table;
	memset(&stCpuSection, 0, sizeof(stCpuSection));
    stCpuSection.dom = SECURE_ACCESS_DOMAIN;
    stCpuSection.ap  = PRIV_RW_USR_NO;
    stCpuSection.xn  = L1_EXECUTE_NEVER;
    stCpuSection.tex = 0x0;
    stCpuSection.c   = 0x0;
    stCpuSection.b   = 0x1;
    stCpuSection.ns  = 0;
    stCpuSection.ng  = 0;
    stCpuSection.s   = 0;
    stCpuSection.va = u32PhyAddr;
    stCpuSection.pa = u32PhyAddr;
    (HI_VOID)map_section_entry(pgd, &stCpuSection, 0);

	return stCpuSection.va;
}

HI_S32 cipher_drv_modInit(HI_VOID)
{
    HI_U32 i = 0;
    HI_S32 ret = HI_SUCCESS;

    ret = DRV_Cipher_Init();

    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Cipher_Init failed, ret=0x%x.\n", ret);
        return ret;
    }

    for (i = 0; i < CIPHER_SOFT_CHAN_NUM; i++)
    {
        g_stCipherOsrChn[i].g_bSoftChnOpen = HI_FALSE;
        g_stCipherOsrChn[i].g_bDataDone = HI_FALSE;
        g_stCipherOsrChn[i].pstDataPkg = NULL;

#ifdef  CIPHER_INTERRUPT_ENABLE
//        init_waitqueue_head(&(g_stCipherOsrChn[i].cipher_wait_queue));
//        g_stCipherOsrChn[i].cipher_wait_queue.elements_count = 0;
//        INIT_LIST_HEAD(&g_stCipherOsrChn[i].cipher_wait_queue.elements_list);
 //       g_stCipherOsrChn[i].cipher_wait_queue.spin_lock.lock = 0;
#endif
    }
#ifdef  CIPHER_INTERRUPT_ENABLE
//    gic_unmask(0, CIPHER_IRQ_NUMBER);
#endif

    g_s32CipherInitFlag = 1;

    return HI_SUCCESS;
}

HI_VOID CIPHER_DRV_ModDeInit(HI_VOID)
{
    HI_U32 i = 0;

    for (i = 0; i < CIPHER_SOFT_CHAN_NUM; i++)
    {
        DRV_Cipher_CloseChn(i);
        g_stCipherOsrChn[i].g_bSoftChnOpen = HI_FALSE;
		if (g_stCipherOsrChn[i].pstDataPkg)
	    {
		    Cipher_Free(g_stCipherOsrChn[i].pstDataPkg);
		    g_stCipherOsrChn[i].pstDataPkg = NULL;
	    }
    }

    DRV_Cipher_DeInit();
    return ;
}

HI_S32 Cipher_Init(HI_VOID)
{    
	if( -1 == g_s32CipherInitFlag)
	{
	      HI_ERR_CIPHER("Cipher init failed!\n");
          return HI_FAILURE;
	}

	HI_INFO_CIPHER("Cipher init success!\n");

	return HI_SUCCESS;
}

HI_VOID Cipher_DeInit(HI_VOID)
{
	HI_INFO_CIPHER("Do nothing, cipher deinit success!\n");
}

HI_S32 Cipher_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr)
{
    HI_U32 i;
    HI_S32 ret = 0;

    if (NULL == phCipher)
    {
        HI_ERR_CIPHER("para phCipher is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ( HI_UNF_CIPHER_TYPE_NORMAL != pstCipherAttr->enCipherType )
    {
		if( HI_UNF_CIPHER_TYPE_COPY_AVOID != pstCipherAttr->enCipherType )
    	{
            ret = HI_ERR_CIPHER_FAILED_GETHANDLE;
            HI_ERR_CIPHER("Invalid Cipher Type!\n");
            return ret;
        }

        if (0 == g_stCipherOsrChn[0].g_bSoftChnOpen)
        {
            i = 0;
        }
        else
        {
            i = CIPHER_INVALID_CHN;
        }
    }
    else
    {
        for(i = CIPHER_PKGxN_CHAN_MIN; i <= CIPHER_PKGxN_CHAN_MAX; i++)
        {
            if (0 == g_stCipherOsrChn[i].g_bSoftChnOpen)
            {
                break;
            }
        }
    }


    if (i > CIPHER_PKGxN_CHAN_MAX)
    {
        ret = HI_ERR_CIPHER_FAILED_GETHANDLE;
        HI_ERR_CIPHER("No more cipher chan left.\n");
        return HI_FAILURE;
    }
    else /* get a free chn */
    {
        g_stCipherOsrChn[i].pstDataPkg = (HI_UNF_CIPHER_DATA_S *)Cipher_Malloc(sizeof(HI_UNF_CIPHER_DATA_S) * CIPHER_MAX_LIST_NUM);
        if (NULL == g_stCipherOsrChn[i].pstDataPkg)
        {
            ret = HI_ERR_CIPHER_FAILED_GETHANDLE;
            HI_ERR_CIPHER("can NOT malloc memory for cipher.\n");
            return HI_FAILURE;
        }

        g_softChnId = i;
        g_stCipherOsrChn[g_softChnId].g_bSoftChnOpen = HI_TRUE;
    }


    g_cipherChn = HI_HANDLE_MAKEHANDLE(HI_ID_CIPHER, 0, g_softChnId);

    ret = DRV_Cipher_OpenChn(g_softChnId);
    if (HI_SUCCESS != ret)
    {
        Cipher_Free(g_stCipherOsrChn[i].pstDataPkg);
        g_stCipherOsrChn[i].pstDataPkg = NULL;
        return HI_FAILURE;
    }

    *phCipher = g_cipherChn;

    return HI_SUCCESS;
}

HI_S32 Cipher_DestroyHandle(HI_HANDLE hCipher)
{
    HI_S32 ret = 0;

    g_cipherChn = hCipher;

    g_softChnId = HI_HANDLE_GET_CHNID(g_cipherChn);
    if (HI_FALSE == g_stCipherOsrChn[g_softChnId].g_bSoftChnOpen)
    {
        ret = HI_SUCCESS; /* success on re-Destroy */
        return ret;
    }

	if (g_stCipherOsrChn[g_softChnId].pstDataPkg)
	{
		Cipher_Free(g_stCipherOsrChn[g_softChnId].pstDataPkg);
		g_stCipherOsrChn[g_softChnId].pstDataPkg = NULL;
    }

    g_stCipherOsrChn[g_softChnId].g_bSoftChnOpen = HI_FALSE;
    ret = DRV_Cipher_CloseChn(g_softChnId);

    return ret;
}

/*
#ifdef CIPHER_INTERRUPT_ENABLE
HI_VOID DRV_CIPHER_UserCommCallBack(HI_U32 arg)
{
    HI_INFO_CIPHER("arg=%#x.\n", arg);
    g_stCipherOsrChn[arg].g_bDataDone = HI_TRUE;
    return ;
}
#endif
*/

HI_S32 Cipher_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    HI_U32 ret = HI_SUCCESS;
    CIPHER_Config_CTRL configdata;

    if (NULL == pstCtrl)
    {
        HI_ERR_CIPHER("para pstCtrl is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    sw_memcpy(&configdata.CIpstCtrl, pstCtrl, sizeof(HI_UNF_CIPHER_CTRL_S));
    configdata.CIHandle=hCipher;

    if(configdata.CIpstCtrl.enWorkMode>=HI_UNF_CIPHER_WORK_MODE_BUTT)
    {
        HI_ERR_CIPHER("para setCIPHER wokemode is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    g_softChnId = HI_HANDLE_GET_CHNID(configdata.CIHandle);
//    HI_INFO_CIPHER("Cipher_ConfigHandle:g_softChnId=%x\n",g_softChnId);
    CIPHER_CheckHandle(g_softChnId);
    ret = DRV_Cipher_ConfigChn(g_softChnId, &configdata.CIpstCtrl, HI_NULL);

    return ret;

}

HI_S32 Cipher_GetHandleConfig(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    HI_U32 Ret = HI_SUCCESS;
    HI_U32 softChnId = 0;       /* soft channel ID */

    softChnId = HI_HANDLE_GET_CHNID(hCipher);
    CIPHER_CheckHandle(softChnId);

    Ret = DRV_Cipher_GetHandleConfig(softChnId, pstCtrl);
    if(Ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Get handle configuration failed!\n");
    }
    return Ret;
}

HI_S32 Cipher_GetIVOut(HI_HANDLE hCipher, HI_U8 *pu8IVOut)
{
    HI_U32 ret = HI_SUCCESS;
    HI_U32 softChnId = 0;       /* soft channel ID */

    softChnId = HI_HANDLE_GET_CHNID(hCipher);
    CIPHER_CheckHandle(softChnId);

    if(NULL == pu8IVOut)
    {
        HI_ERR_CIPHER("Null pointer!\n");
        return HI_FAILURE;
    }

    ret = DRV_Cipher_GetIVOut(softChnId, pu8IVOut);
    return ret;
}

static void HEX2STR(char buf[2], HI_U8 val)
{
    HI_U8 high, low;

    high = (val >> 4) & 0x0F;
    low =  val & 0x0F;
    
    if(high <= 9)
    {
        buf[0] = high + '0';
    }
    else
    {
        buf[0] = (high - 0x0A) + 'A';
    }

    if(low <= 9)
    {
        buf[1] = low + '0';
    }
    else
    {
        buf[1] = (low - 0x0A) + 'A';
    }
    
}

static void PrintData(const char*pbName, HI_U8 *pbData, HI_U32 u32Size)
{ 
    HI_U32 i;
    char buf[2];

    if (pbName != HI_NULL)
    {
        HI_PRINT("%s ", pbName);
    }
    for (i=0; i<u32Size; i++)
    {
        HEX2STR(buf, pbData[i]);
        HI_PRINT("%c%c ", buf[0], buf[1]);
        if(((i+1) % 16) == 0)
            HI_PRINT("\n   ");  
    }
    if (( i % 16) != 0)
    {
        HI_PRINT("\n");
    }
}
    
HI_S32 Cipher_Test(HI_U32 u32Cmd, HI_U32 *pu32Result, HI_U32 u32Param1, HI_U32 u32Param2)
{
    HI_U32 u32Ret = HI_SUCCESS;
    HI_U32 u32SrcVirAddr = 0;

    switch(u32Cmd)
    {
    case CIPHER_TEST_PRINT_PHY:
        u32SrcVirAddr = s_Cipher_RemapPhyAddr(u32Param1);
        PrintData("TZ-Data", (HI_U8*)u32SrcVirAddr, u32Param2);
        break;
    case CIPHER_TEST_PRINT_VIA:
        u32SrcVirAddr = u32Param1;
        PrintData("TZ-Data", (HI_U8*)u32SrcVirAddr, u32Param2);
        break;
#ifdef HI_CIPHER_TEST
    case CIPHER_TEST_AES:
        aes_test ();
        break;
    case CIPHER_TEST_HMAC:
        hamc_test();
        break;
    case CIPHER_TEST_HASH:
        hash_test();
        break;
    case CIPHER_TEST_RSA:
        rsa_test();
        break;
    case CIPHER_TEST_DES:
        des_test();
        break;
   case CIPHER_TEST_RSA_PRIM:
        rsa_prim_test();
        break;
   case CIPHER_TEST_RSA_KG: 
        rsa_kg_test();
        break;
   case CIPHER_TEST_RND: 
        test_rnd();
        break;
#endif
    default:
        break;
    }

    if (pu32Result != HI_NULL)
    {
        *pu32Result = u32Ret;
    }
    
    return HI_SUCCESS;
}

HI_S32 s_Cipher_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_U32 ret = HI_SUCCESS;
    HI_U32 chnid;
    CIPHER_DATA_S CIdata;
    HI_DRV_CIPHER_TASK_S pCITask;
    HI_UNF_CIPHER_CTRL_S *pstCurrentCipherConfig = NULL;
	if( (0 == u32SrcPhyAddr) || (0 == u32DestPhyAddr) || (0 == u32ByteLength))
	{
		HI_ERR_CIPHER("Invalid data length input\n");
		return HI_ERR_CIPHER_INVALID_PARA;
	}
    chnid = HI_HANDLE_GET_CHNID(hCipher);
    CIPHER_CheckHandle(chnid);

    /*Add by y00201671 for TrustedCore:begin*/
    if (0 == chnid)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    pstCurrentCipherConfig = DRV_Cipher_GetHandleConfig_ptr(chnid);
    if ( (pstCurrentCipherConfig->enAlg == HI_UNF_CIPHER_ALG_AES) 
        && (HI_UNF_CIPHER_WORK_MODE_CTR != pstCurrentCipherConfig->enWorkMode)
        && ((u32ByteLength&0xf) != 0 ))     /* AES */
    {
            return HI_ERR_CIPHER_INVALID_PARA;
    }
	else if((pstCurrentCipherConfig->enAlg != HI_UNF_CIPHER_ALG_AES)
        &&( (u32ByteLength & 0x7) != 0 ))       /* DES/3DES */
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (HI_UNF_CIPHER_WORK_MODE_CTR != pstCurrentCipherConfig->enWorkMode)
    {
        if (u32ByteLength < HI_UNF_CIPHER_MIN_CRYPT_LEN)
            return HI_ERR_CIPHER_INVALID_PARA;
    }
    /*Add by y00201671 for TrustedCore:begin*/
    HI_U32 aligned = 0;
    if (HI_UNF_CIPHER_WORK_MODE_CTR == pstCurrentCipherConfig->enWorkMode)
    {
//        sw_printf("Mode:HI_UNF_CIPHER_WORK_MODE_CTR\n");
        aligned = ((u32ByteLength+DX_TZ_AES128_BLOCK_SIZE-1)/DX_TZ_AES128_BLOCK_SIZE)*DX_TZ_AES128_BLOCK_SIZE - u32ByteLength;
        u32ByteLength = u32ByteLength + aligned;
//        sw_printf("Mode:not HI_UNF_CIPHER_WORK_MODE_CTR\n");
    }
    /*Add by y00201671 for TrustedCore:end*/

    g_softChnId = chnid;

    CIdata.ScrPhyAddr=u32SrcPhyAddr;
    CIdata.DestPhyAddr=u32DestPhyAddr;
    CIdata.u32DataLength=u32ByteLength;
    CIdata.CIHandle=hCipher;

    pCITask.stData2Process.u32src = CIdata.ScrPhyAddr;
    pCITask.stData2Process.u32dest = CIdata.DestPhyAddr;
    pCITask.stData2Process.u32length = CIdata.u32DataLength;
    pCITask.stData2Process.bDecrypt = HI_FALSE;
    pCITask.u32CallBackArg = g_softChnId;
	
    g_stCipherOsrChn[g_softChnId].g_bDataDone = HI_FALSE;
    ret = DRV_Cipher_CreatTask(g_softChnId,&pCITask, NULL, NULL);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

//#ifdef  CIPHER_INTERRUPT_ENABLE
//    sw_wait_event(&g_stCipherOsrChn[g_softChnId].cipher_wait_queue,
 //                   g_stCipherOsrChn[g_softChnId].g_bDataDone == HI_TRUE);

//#else
    ret = DRV_Cipher_waitStat(g_softChnId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Cipher_Encrypt  timeout\n");
        return HI_FAILURE;
    }
//#endif
    /*Add by y00201671 for TrustedCore:begin*/
    if (HI_UNF_CIPHER_WORK_MODE_CTR == pstCurrentCipherConfig->enWorkMode)
    {
        u32ByteLength = u32ByteLength - aligned;
    }
	return HI_SUCCESS;
}

HI_S32 s_Cipher_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_U32 ret = HI_SUCCESS;
    HI_U32 chnid = 0;
    CIPHER_DATA_S CIdata;
    HI_DRV_CIPHER_TASK_S pCITask;
    HI_UNF_CIPHER_CTRL_S *pstCurrentCipherConfig = NULL;

	if( (0 == u32SrcPhyAddr) || (0 == u32DestPhyAddr) || (0 == u32ByteLength))
	{
		return HI_ERR_CIPHER_INVALID_PARA;
	}

    chnid = HI_HANDLE_GET_CHNID(hCipher);

    /*Add by y00201671 for TrustedCore:begin*/
    if (0 == chnid)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    pstCurrentCipherConfig = DRV_Cipher_GetHandleConfig_ptr(chnid);

    if ( (pstCurrentCipherConfig->enAlg == HI_UNF_CIPHER_ALG_AES) 
        && (HI_UNF_CIPHER_WORK_MODE_CTR != pstCurrentCipherConfig->enWorkMode)
        && ((u32ByteLength&0xf) != 0 ))     /* AES */
    {
            return HI_ERR_CIPHER_INVALID_PARA;
    }
	else if((pstCurrentCipherConfig->enAlg != HI_UNF_CIPHER_ALG_AES)
        &&( (u32ByteLength & 0x7) != 0 ))       /* DES/3DES */
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (HI_UNF_CIPHER_WORK_MODE_CTR != pstCurrentCipherConfig->enWorkMode)
    {
        if (u32ByteLength < HI_UNF_CIPHER_MIN_CRYPT_LEN)
            return HI_ERR_CIPHER_INVALID_PARA;
    }
    /*Add by y00201671 for TrustedCore:begin*/
    HI_U32 aligned = 0;
    if (HI_UNF_CIPHER_WORK_MODE_CTR == pstCurrentCipherConfig->enWorkMode)
    {
        aligned = ((u32ByteLength+DX_TZ_AES128_BLOCK_SIZE-1)/DX_TZ_AES128_BLOCK_SIZE)*DX_TZ_AES128_BLOCK_SIZE - u32ByteLength;
        u32ByteLength = u32ByteLength + aligned;
    }

    /*Add by y00201671 for TrustedCore:end*/

    CIdata.ScrPhyAddr=u32SrcPhyAddr;
    CIdata.DestPhyAddr=u32DestPhyAddr;
    CIdata.u32DataLength=u32ByteLength;
    CIdata.CIHandle=hCipher;

    g_softChnId = HI_HANDLE_GET_CHNID(CIdata.CIHandle);



    CIPHER_CheckHandle(g_softChnId);
    pCITask.stData2Process.u32src=CIdata.ScrPhyAddr;
    pCITask.stData2Process.u32dest=CIdata.DestPhyAddr;
    pCITask.stData2Process.u32length=CIdata.u32DataLength;
    pCITask.stData2Process.bDecrypt=HI_TRUE;

    pCITask.u32CallBackArg=g_softChnId;

//    HI_ERR_CA("Start to Decrypt, chnNum = %x!\n", g_softChnId);

    g_stCipherOsrChn[g_softChnId].g_bDataDone = HI_FALSE;

    ret = DRV_Cipher_CreatTask(g_softChnId,&pCITask,NULL,NULL);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

//#ifdef  CIPHER_INTERRUPT_ENABLE
//    HI_INFO_CA("encrypt wait channel %d queue event, spin_lock=%d\n", g_softChnId,
//        g_stCipherOsrChn[g_softChnId].cipher_wait_queue.spin_lock.lock);

/*
    if (0 == wait_event_interruptible_timeout(g_stCipherOsrChn[g_softChnId].cipher_wait_queue,
                g_stCipherOsrChn[g_softChnId].g_bDataDone != HI_FALSE, 200))
    {
        HI_ERR_CIPHER("Encrypt time out! \n");
        return HI_FAILURE;
    }
*/
//    sw_wait_event(&g_stCipherOsrChn[g_softChnId].cipher_wait_queue,
//                    g_stCipherOsrChn[g_softChnId].g_bDataDone == HI_TRUE);

//#else
    ret = DRV_Cipher_waitStat(g_softChnId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Cipher_Decrypt  timeout\n");
        return HI_FAILURE;
    }
//#endif
    /*Add by y00201671 for TrustedCore:begin*/
    if (HI_UNF_CIPHER_WORK_MODE_CTR == pstCurrentCipherConfig->enWorkMode)
    {
        u32ByteLength = u32ByteLength - aligned;
    }
    /*Add by y00201671 for TrustedCore:end*/
    return HI_SUCCESS;
}

static HI_VOID s_Cipher_UnmapPhyAddr(HI_U32 u32PhyAddr)
{
    UINT32 *pgd = secure_page_table;
    (HI_VOID)unmap_ns_section_entry(pgd, u32PhyAddr);
	return;
}

HI_S32 s_Cipher_ConfigHandle_AESCBC(HI_HANDLE hHANDLE, const HI_U8 *pu8IV, const HI_U8 *pu8Key, HI_BOOL bIsKeyByCA)
{
	HI_S32 ret = HI_SUCCESS;
	HI_UNF_CIPHER_CTRL_S stCipherCtrl;
	
	if((HI_TRUE == bIsKeyByCA) && (NULL == pu8Key))
	{
		HI_ERR_CIPHER("Invalid key input, null pointer!\n");
		return HI_FAILURE;
	}

	memset(&stCipherCtrl, 0, sizeof(stCipherCtrl));
	stCipherCtrl.bKeyByCA = bIsKeyByCA;
	stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
	stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
	stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
	stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
	if(NULL == pu8IV)
	{
		memset((HI_U8 *)stCipherCtrl.u32IV, 0, 16);
	}
	else
	{
		stCipherCtrl.stChangeFlags.bit1IV = 1;
		memcpy((HI_U8 *)stCipherCtrl.u32IV, pu8IV, 16);
	}

	if(HI_FALSE == bIsKeyByCA)
	{
		memcpy((HI_U8 *)stCipherCtrl.u32Key, pu8Key, 16);
	}

	ret = Cipher_ConfigHandle(hHANDLE, &stCipherCtrl);
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("Cipher config handle failed!\n");
		return HI_FAILURE;
	}

	return HI_SUCCESS;
}

HI_S32 s_Cipher_Encrypt_AESCBCCTS(HI_HANDLE hCipherHandle, 
								HI_U32 u32SrcPhyAddr, 
								HI_U32 u32DestPhyAddr, 
								HI_U32 u32ByteLength, 
								const HI_U8 au8IV[16],
								const HI_U8 *pu8Key,
								HI_BOOL bIsKeyByCA)
{
	HI_S32 ret = HI_SUCCESS;
	HI_U32 u32TailLen = u32ByteLength % 16;
	HI_U8 au8CN[16] = {0};
	HI_U32 u32SrcVirAddr = 0;
	HI_U32 u32DestVirAddr = 0;
	u32SrcVirAddr = s_Cipher_RemapPhyAddr(u32SrcPhyAddr);
	if(0 == u32SrcVirAddr)
	{
	       
		HI_ERR_CIPHER("Remap src phyaddr failed!");
		return HI_FAILURE;
	}
	
	u32DestVirAddr = s_Cipher_RemapPhyAddr(u32DestPhyAddr);
	if(0 == u32DestVirAddr)
	{
		HI_ERR_CIPHER("Remap dest phyaddr failed!");
		s_Cipher_UnmapPhyAddr(u32SrcPhyAddr);
		return HI_FAILURE;
	}
	
	if (u32ByteLength < 16)
	{
		memcpy((HI_U8 *)u32DestVirAddr, (HI_U8 *)u32SrcVirAddr, u32ByteLength);//just copy without encrypt
    	ret = HI_SUCCESS;
		goto __CIPHER_EXIT__;
	}
	
	if(0 == u32TailLen)
	{
		ret = s_Cipher_ConfigHandle_AESCBC(hCipherHandle, au8IV, pu8Key, bIsKeyByCA);
		ret |= s_Cipher_Encrypt(hCipherHandle, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength);
		if ( HI_SUCCESS != ret )
		{
		    HI_ERR_CIPHER("Cipher decrypt failed, final!\n");
		}
    	return ret;
	}
	memset((HI_U8 *)u32SrcVirAddr + u32ByteLength, 0, 16 - u32TailLen);
	ret	 = s_Cipher_ConfigHandle_AESCBC(hCipherHandle, au8IV, pu8Key, bIsKeyByCA);
	ret |= s_Cipher_Encrypt(hCipherHandle, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength + 16 - u32TailLen);
	if(HI_SUCCESS != ret)
	{
		HI_ERR_CIPHER("Cipher encrypt(CBC) failed!\n");
		goto __CIPHER_EXIT__;
	}
	memcpy(au8CN, (void*)(u32DestVirAddr + u32ByteLength - u32TailLen), 16);	/* backup C[n] */
	memcpy((void*)(u32DestVirAddr + u32ByteLength - u32TailLen), (void*)(u32DestVirAddr + u32ByteLength - u32TailLen - 16), 16);
	memcpy((void*)(u32DestVirAddr + u32ByteLength - u32TailLen - 16), au8CN, 16);
	
__CIPHER_EXIT__:
	s_Cipher_UnmapPhyAddr(u32SrcPhyAddr);
	s_Cipher_UnmapPhyAddr(u32DestPhyAddr);
	return ret;
}

#if 0
//according to widevine L3,  from Android SDK source code:WVCryptoPlugin.cpp
HI_S32 s_Cipher_Decrypt_AESCBCCTS(HI_HANDLE hCipherHandle, 
								HI_U32 u32SrcPhyAddr, 
								HI_U32 u32DestPhyAddr, 
								HI_U32 u32ByteLength, 
								const HI_U8 au8IV[16],
								HI_U8 *pu8Key,
								HI_BOOL bIsKeyByCA)
{
    HI_U32 k, r, i = 0;
    HI_U8 peniv[16] = {0};
	HI_U32 u32SrcVirAddr = 0;
	HI_U32 u32DestVirAddr = 0;
	HI_S32 ret = HI_SUCCESS;

	if ( (NULL == au8IV) || (0 == u32SrcPhyAddr) || (0 == u32DestPhyAddr) || (0 == u32ByteLength))
	{
		HI_ERR_CIPHER("Invalid param input!\n");
	    return HI_FAILURE;
	}

	u32SrcVirAddr = s_Cipher_RemapPhyAddr(u32SrcPhyAddr);
	if(0 == u32SrcVirAddr)
	{
		HI_ERR_CIPHER("Remap src phyaddr failed!");
		return HI_FAILURE;
	}

	u32DestVirAddr = s_Cipher_RemapPhyAddr(u32DestPhyAddr);
	if(0 == u32DestVirAddr)
	{
		HI_ERR_CIPHER("Remap dest phyaddr failed!");
		s_Cipher_UnmapPhyAddr(u32SrcPhyAddr);
		return HI_FAILURE;
	}

	if (u32ByteLength < 16)
	{
		memcpy((HI_U8 *)u32DestVirAddr, (HI_U8 *)u32SrcVirAddr, u32ByteLength);//just copy without decrypt
		ret = HI_SUCCESS;
		goto __CIPHER_EXIT__;
	}

	r = u32ByteLength % 16;

    if (r) {
        k = u32ByteLength - r - 16;
    } else {
        k = u32ByteLength;
    }

//  AES_cbc_encrypt(in, out, k, &mAesKey, iv, 0);
	ret =  s_Cipher_ConfigHandle_AESCBC(hCipherHandle, au8IV, pu8Key, bIsKeyByCA);
	ret |= s_Cipher_Decrypt(hCipherHandle, u32SrcPhyAddr, u32DestPhyAddr, k);
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("Cipher decrypt failed!\n");
	    goto __CIPHER_EXIT__;
	}

    if (r) {
        memcpy(peniv, (HI_U8 *)u32SrcVirAddr + k + 16, r);

//      AES_cbc_encrypt(in + k, out + k, 16, &mAesKey, peniv, 0);
		ret =  s_Cipher_ConfigHandle_AESCBC(hCipherHandle, au8IV, pu8Key, bIsKeyByCA);
		ret |= s_Cipher_Decrypt(hCipherHandle, u32SrcPhyAddr + k, u32DestPhyAddr + k, 16);
		if ( HI_SUCCESS != ret )
		{
		    HI_ERR_CIPHER("Cipher decrypt failed!\n");
		    goto __CIPHER_EXIT__;
		}

        // exchange the final plaintext and ciphertext
        for (i = 0; i < r; i++) {
            *((HI_U8 *)u32DestVirAddr + k + 16 + i) = *((HI_U8 *)u32DestVirAddr + k + i);
            *((HI_U8 *)u32DestVirAddr + k + i) = *((HI_U8 *)u32SrcVirAddr + k + 16 + i);
        }
//        AES_cbc_encrypt(out + k, out + k, 16, &mAesKey, iv, 0);
		ret =  s_Cipher_ConfigHandle_AESCBC(hCipherHandle, au8IV, pu8Key, bIsKeyByCA);
		ret |= s_Cipher_Decrypt(hCipherHandle, u32DestPhyAddr + k, u32DestPhyAddr + k, 16);
		if ( HI_SUCCESS != ret )
		{
		    HI_ERR_CIPHER("Cipher decrypt failed!\n");
		    goto __CIPHER_EXIT__;
		}
    }
    
__CIPHER_EXIT__:
	s_Cipher_UnmapPhyAddr(u32SrcPhyAddr);
	s_Cipher_UnmapPhyAddr(u32DestPhyAddr);
	
	return ret;
}
#else
HI_S32 s_Cipher_Decrypt_AESCBCCTS(HI_HANDLE hCipherHandle, 
								HI_U32 u32SrcPhyAddr, 
								HI_U32 u32DestPhyAddr, 
								HI_U32 u32ByteLength, 
								const HI_U8 au8IV[16],
								HI_U8 *pu8Key,
								HI_BOOL bIsKeyByCA)
{
	HI_S32 ret = HI_SUCCESS;
	HI_U32 u32TailLen = 0;
	HI_U8 au8TempIV[16] = {0};
    HI_U8 au8CN[16] = {0};
    HI_U8 au8CN1[16] = {0};
	HI_U8 au8DN[16] = {0};
	HI_U32 u32SrcVirAddr = 0;
	HI_U32 u32DestVirAddr = 0;

	if ( (NULL == au8IV) || (0 == u32SrcPhyAddr) || (0 == u32DestPhyAddr) || (0 == u32ByteLength))
	{
		HI_ERR_CIPHER("Invalid param input!\n");
	    return HI_FAILURE;
	}

	u32SrcVirAddr = s_Cipher_RemapPhyAddr(u32SrcPhyAddr);
	if(0 == u32SrcVirAddr)
	{
		HI_ERR_CIPHER("Remap src phyaddr failed!");
		return HI_FAILURE;
	}

	u32DestVirAddr = s_Cipher_RemapPhyAddr(u32DestPhyAddr);
	if(0 == u32DestVirAddr)
	{
		HI_ERR_CIPHER("Remap dest phyaddr failed!");
		s_Cipher_UnmapPhyAddr(u32SrcPhyAddr);
		return HI_FAILURE;
	}

	if (u32ByteLength < 16)
	{
		memcpy((HI_U8 *)u32DestVirAddr, (HI_U8 *)u32SrcVirAddr, u32ByteLength);//just copy without decrypt
		ret = HI_SUCCESS;
		goto __CIPHER_EXIT__;
	}

	u32TailLen = u32ByteLength % 16;
	if (0 == u32TailLen)
	{
		ret =  s_Cipher_ConfigHandle_AESCBC(hCipherHandle, au8IV, pu8Key, bIsKeyByCA);
		ret |= s_Cipher_Decrypt(hCipherHandle, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength);
		if ( HI_SUCCESS != ret )
		{
		    HI_ERR_CIPHER("Cipher decrypt failed, final!\n");
		}
		goto __CIPHER_EXIT__;
	}
	
	memset(au8TempIV, 0, sizeof(au8TempIV));
	ret = s_Cipher_ConfigHandle_AESCBC(hCipherHandle, au8TempIV, pu8Key, bIsKeyByCA);
	ret |= s_Cipher_Decrypt(hCipherHandle,
						u32SrcPhyAddr + u32ByteLength - u32TailLen - 16,
						u32DestPhyAddr, 16);
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("Config and decrypt failed!\n");
		goto __CIPHER_EXIT__;
	}
	
	memcpy(au8DN, (void*)u32DestVirAddr, 16);
	memcpy(au8CN, (void*)(u32SrcVirAddr + u32ByteLength - u32TailLen), u32TailLen);
	memcpy(au8CN + u32TailLen, au8DN + u32TailLen, 16 - u32TailLen);
	memcpy(au8CN1, (void*)(u32SrcVirAddr + u32ByteLength - 16 - u32TailLen), 16);	/* backup C[n-1] */
	memcpy((void*)(u32SrcVirAddr + u32ByteLength - 16 - u32TailLen), au8CN, 16);		/* C[n] >> C[n-1] */
	memcpy((void*)(u32SrcVirAddr + u32ByteLength - u32TailLen), au8CN1, 16);			/* C[n-1] >> C[n] */
	memset((void*)u32DestVirAddr, 0, u32ByteLength);
	
	ret =  s_Cipher_ConfigHandle_AESCBC(hCipherHandle, au8IV, pu8Key,bIsKeyByCA);
	ret |= s_Cipher_Decrypt(hCipherHandle,
						u32SrcPhyAddr, 
						u32DestPhyAddr, 
						u32ByteLength + 16 - u32TailLen);
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("Config and decrypt failed!\n");
		goto __CIPHER_EXIT__;
	}
	
__CIPHER_EXIT__:
	s_Cipher_UnmapPhyAddr(u32SrcPhyAddr);
	s_Cipher_UnmapPhyAddr(u32DestPhyAddr);
	
	return ret;
}
#endif

HI_S32 Cipher_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
	HI_U32 chnid = 0;
	HI_UNF_CIPHER_CTRL_S stCipherCtrl;
	HI_U8 au8IV[16] = {0};
	
	chnid = HI_HANDLE_GET_CHNID(hCipher);
    (HI_VOID)DRV_Cipher_GetHandleConfig(chnid, &stCipherCtrl);
	if (HI_UNF_CIPHER_WORK_MODE_CBC_CTS != stCipherCtrl.enWorkMode)
	{
	    return s_Cipher_Encrypt(hCipher, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength);
	}
	else
	{
		memcpy(au8IV, stCipherCtrl.u32IV, sizeof(au8IV));
	    return s_Cipher_Encrypt_AESCBCCTS(hCipher, 
	    								u32SrcPhyAddr, 
	    								u32DestPhyAddr, 
	    								u32ByteLength, 
	    								au8IV,
	    								(HI_U8*)stCipherCtrl.u32Key,
	    								stCipherCtrl.bKeyByCA);
	}
}
HI_S32 Cipher_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
	HI_U32 chnid = 0;
	HI_UNF_CIPHER_CTRL_S stCipherCtrl;
	HI_U8 au8IV[16] = {0};

	chnid = HI_HANDLE_GET_CHNID(hCipher);
    (HI_VOID)DRV_Cipher_GetHandleConfig(chnid, &stCipherCtrl);

	if (HI_UNF_CIPHER_WORK_MODE_CBC_CTS != stCipherCtrl.enWorkMode)
	{
	    return s_Cipher_Decrypt(hCipher, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength);
	}
	else
	{
		memcpy(au8IV, stCipherCtrl.u32IV, sizeof(au8IV));
	    return s_Cipher_Decrypt_AESCBCCTS(hCipher, 
	    								u32SrcPhyAddr, 
	    								u32DestPhyAddr, 
	    								u32ByteLength, 
	    								au8IV, 
	    								(HI_U8*)stCipherCtrl.u32Key, 
	    								stCipherCtrl.bKeyByCA);
	}
}

HI_S32 Cipher_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    HI_U32 ret = HI_SUCCESS;
    HI_U32 chnid = 1;
    HI_U32 i = 0;
    HI_UNF_CIPHER_DATA_S *pPkgTmp = NULL;
    static HI_DRV_CIPHER_DATA_INFO_S  tmpData[CIPHER_MAX_LIST_NUM];

    chnid = HI_HANDLE_GET_CHNID(hCipher);
    CIPHER_CheckHandle(chnid);
	if (u32DataPkgNum > CIPHER_MAX_LIST_NUM)
    {
        HI_ERR_CIPHER("Error: you send too many pkg(%d), must < %d.\n", u32DataPkgNum, CIPHER_MAX_LIST_NUM);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    for (i = 0; i < u32DataPkgNum; i++)
    {
        pPkgTmp = pstDataPkg + i;
        if (pPkgTmp->u32ByteLength < HI_UNF_CIPHER_MIN_CRYPT_LEN || pPkgTmp->u32ByteLength > HI_UNF_CIPHER_MAX_CRYPT_LEN)
        {
            HI_ERR_CIPHER("Pkg%d 's length(%d) invalid.\n", i, pPkgTmp->u32ByteLength);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

	memset(tmpData, 0, sizeof(tmpData));

    for (i = 0; i < u32DataPkgNum; i++)
    {
        pPkgTmp = pstDataPkg + i;
        tmpData[i].bDecrypt = HI_FALSE;
        tmpData[i].u32src = pPkgTmp->u32SrcPhyAddr;
        tmpData[i].u32dest = pPkgTmp->u32DestPhyAddr;
        tmpData[i].u32length = pPkgTmp->u32ByteLength;
    }

	memcpy(g_stCipherOsrChn[chnid].pstDataPkg, pstDataPkg, u32DataPkgNum * sizeof(pstDataPkg));

    g_stCipherOsrChn[chnid].g_bDataDone = HI_FALSE;
    ret = DRV_Cipher_CreatMultiPkgTask(chnid, tmpData, u32DataPkgNum, chnid);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }
    //printk("wait channel %d queue event\n", softChnId);
    ret = DRV_Cipher_waitStat(chnid);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Cipher_EncryptMulti  timeout\n");
        return HI_FAILURE;
    }
   // udelay(10000);
    return HI_SUCCESS;
}


HI_S32 Cipher_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    HI_U32 Ret = HI_SUCCESS;
    HI_U32 chnid= 1;
    HI_U32 i = 0;
    HI_UNF_CIPHER_DATA_S *pPkgTmp = NULL;
    static HI_DRV_CIPHER_DATA_INFO_S  tmpData[CIPHER_MAX_LIST_NUM];

    chnid = HI_HANDLE_GET_CHNID(hCipher);
	CIPHER_CheckHandle(chnid);

    for (i = 0; i < u32DataPkgNum; i++)
    {
        pPkgTmp = pstDataPkg + i;
        if (pPkgTmp->u32ByteLength < HI_UNF_CIPHER_MIN_CRYPT_LEN || pPkgTmp->u32ByteLength > HI_UNF_CIPHER_MAX_CRYPT_LEN)
        {
            HI_ERR_CIPHER("Pkg%d 's length(%d) invalid.\n", i, pPkgTmp->u32ByteLength);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }



    if (u32DataPkgNum > CIPHER_MAX_LIST_NUM)
    {
        HI_ERR_CIPHER("Error: you send too many pkg(%d), must < %d.\n", u32DataPkgNum, CIPHER_MAX_LIST_NUM);
        return  HI_ERR_CIPHER_INVALID_PARA;
    }
    for (i = 0; i < u32DataPkgNum; i++)
    {
        pPkgTmp = pstDataPkg + i;
        tmpData[i].bDecrypt = HI_TRUE;
        tmpData[i].u32src = pPkgTmp->u32SrcPhyAddr;
        tmpData[i].u32dest = pPkgTmp->u32DestPhyAddr;
        tmpData[i].u32length = pPkgTmp->u32ByteLength;
    }

	memcpy(g_stCipherOsrChn[chnid].pstDataPkg, pstDataPkg, u32DataPkgNum * sizeof(HI_UNF_CIPHER_DATA_S));
    g_stCipherOsrChn[chnid].g_bDataDone = HI_FALSE;
    Ret = DRV_Cipher_CreatMultiPkgTask(chnid, tmpData, u32DataPkgNum, chnid);
    if (HI_SUCCESS != Ret)
    {
        return Ret;
    }
    //printk("wait channel %d queue event\n", softChnId);
    Ret = DRV_Cipher_waitStat(chnid);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CIPHER("Cipher_DecryptMulti  timeout\n");
        return HI_FAILURE;
    }
    //udelay(10000);
    return HI_SUCCESS;
}


HI_S32 Cipher_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 Ret = HI_SUCCESS;

    if( (NULL== pstHashAttr) || (NULL == pHashHandle) )
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_FAILURE;
    }

    if(pstHashAttr->eShaType >= HI_UNF_CIPHER_HASH_TYPE_BUTT)
    {
        HI_ERR_CIPHER("Invalid hash type input!\n");
        return HI_FAILURE;
    }

    if(g_HashDevFd > 0)
    {
        HI_ERR_CIPHER("Hash module is busy!\n");
        return HI_FAILURE;
    }

    g_HashDevFd = 1;

    sw_memset((HI_U8 *)&g_stCipherHashData, 0, sizeof(g_stCipherHashData));
    g_stCipherHashData.enShaType = pstHashAttr->eShaType;
    if( ( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashAttr->eShaType) || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstHashAttr->eShaType ))
    {
    	if(NULL != pstHashAttr->pu8HMACKey)
    	{
	        sw_memcpy(g_stCipherHashData.u8HMACKey, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen);
//			g_stCipherHashData.u32HMACKeyLen = pstHashAttr->u32HMACKeyLen;
        g_stCipherHashData.enHMACKeyFrom = HI_CIPHER_HMAC_KEY_FROM_CPU;
    }
		else
		{
		    return HI_FAILURE;
		}
    }

    /*MMZ malloc hash buffer*/

    Ret = DRV_Cipher_CalcHashInit(&g_stCipherHashData);
    if(Ret != HI_SUCCESS)
    {
        g_HashDevFd = -1;
        return Ret;
    }

    *pHashHandle = (HI_U32)&g_stCipherHashData;

    return HI_SUCCESS;
}

HI_S32 Cipher_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 Ret = HI_SUCCESS;
    CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S *)hHashHandle;
    HI_U32 u32TmpLen = 0;

    if(hHashHandle == 0 || pu8InputData == NULL || u32InputDataLen == 0)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        g_HashDevFd = -1;
        return HI_FAILURE;
    }

    while(u32InputDataLen > 0)
    {
        if(u32InputDataLen > SECURE_MEM_CIPHER_MAX_SIZE)
        {
            u32TmpLen = SECURE_MEM_CIPHER_MAX_SIZE;
        }
        else
        {
            u32TmpLen = u32InputDataLen;
        }

        pstCipherHashData->u32InputDataLen = u32TmpLen;
        pstCipherHashData->pu8InputData = pu8InputData;
        u32InputDataLen -= u32TmpLen;
        pu8InputData += u32TmpLen;

        Ret = DRV_Cipher_CalcHashUpdate(pstCipherHashData);
        if(Ret != HI_SUCCESS)
        {
            g_HashDevFd = -1;
            return Ret;
        }
    }
    return HI_SUCCESS;
}

HI_S32 Cipher_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 Ret = HI_SUCCESS;
    CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S *)hHashHandle;;

    if(pu8OutputHash == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        g_HashDevFd = -1;
        return HI_FAILURE;
    }

    pstCipherHashData->pu8Output= pu8OutputHash;
    Ret = DRV_Cipher_CalcHashFinal(pstCipherHashData);
    if(Ret != HI_SUCCESS)
    {
        g_HashDevFd = -1;
        return Ret;
    }
    g_HashDevFd = -1;
    
    return HI_SUCCESS;
}

HI_S32 Cipher_GetRandomNumber(HI_U32 *pu32Rnd)
{
    HI_U32 u32RngStat = 0;
    HI_U32 u32RngCtrl = 0;
    HI_U32 u32RngRandomNumber = 0;

	if(NULL == pu32Rnd)
	{
		return HI_FAILURE;
	}
    u32RngCtrl = 0;
    CIPHER_READ_REG(REG_RNG_BASE_ADDR, u32RngCtrl);
    if ((0x01 == (u32RngCtrl & 0x03)) || (0x0 == (u32RngCtrl & 0x03)))
    {
        u32RngCtrl &= 0xfffffffc;
        u32RngCtrl |= 0x03;

        CIPHER_WRITE_REG(REG_RNG_BASE_ADDR, u32RngCtrl);
        CIPHER_MSLEEP(2);
    }

    while(1)
    {
        u32RngStat = 0;
        CIPHER_READ_REG(REG_RNG_STAT_ADDR, u32RngStat);
        if((u32RngStat & 0xFF) > 0)
        {
            break;
        }
        CIPHER_MSLEEP(1);
    }

    u32RngRandomNumber = 0;
    CIPHER_READ_REG(REG_RNG_NUMBER_ADDR, u32RngRandomNumber);
    *pu32Rnd = u32RngRandomNumber;
    return HI_SUCCESS;
}

HI_S32 Cipher_EncryptHDCPKey(OTP_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer)
{
    HI_S32 ret = HI_SUCCESS;
    OTP_HDCPKEY_S stOtpHdcpKey;
    HI_U8 u8KeyBuf[320] = {0};
    HI_U32 u32CRC_0 = 0;
	HI_U32 u32CRC_1 = 0;
    HI_U8 u8WriteFlagChar[2] = {'H', 'I'};

    if ( NULL== pstHdcpKeyTransfer)
    {
        HI_ERR_CIPHER("Invalid param, null pointer!\n");
        return HI_FAILURE;
    }
	
    memset(&stOtpHdcpKey, 0, sizeof(stOtpHdcpKey));

    if ( HI_TRUE ==  pstHdcpKeyTransfer->bIsUseOTPRootKey)
    {    
        memset(&(pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey[0]), 0x00, 1);
    }
    else
    {
        memset(&(pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey[0]), 0x80, 1);
    }
	
    memset(&(pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey[1]), 0x00, 1);
    memcpy(&(pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey[2]), u8WriteFlagChar, 2);
    if ( HI_TRUE == pstHdcpKeyTransfer->stHdcpKey.EncryptionFlag)
    {
        ret = DRV_Cipher_DecryptAndFormatHDCPKey(&(pstHdcpKeyTransfer->stHdcpKey), &stOtpHdcpKey);
        if ( HI_FAILURE == ret)
        {
            HI_ERR_CIPHER("HDCPKey decytion and format failed!\n");
            return HI_FAILURE;
        }
    }
    else
    {
        (HI_VOID)DRV_Cipher_FormatHDCPKey((HI_UNF_HDCP_DECRYPT_S *)&pstHdcpKeyTransfer->stHdcpKey.key, &stOtpHdcpKey);
    }

    if ( HI_TRUE == pstHdcpKeyTransfer->bIsUseOTPRootKey)
    {
        ret = DRV_Cipher_CryptoFormatedHDCPKey(stOtpHdcpKey.HdcpKey, 
                                    320, 
                                    CIPHER_HDCP_MODE_HDCP_KEY,
                                    CIPHER_HDCP_KEY_RAM_MODE_WRITE,
                                    CIPHER_HDCP_KEY_TYPE_OTP_ROOT_KEY,
                                    HI_FALSE,
                                    u8KeyBuf );
        if ( HI_FAILURE == ret)
        {
            HI_ERR_CIPHER("Encrypt HDCP Key using rootkey in otp failed!\n");
            return HI_FAILURE;
        }            
    }
    else
    {
        ret = DRV_Cipher_CryptoFormatedHDCPKey(stOtpHdcpKey.HdcpKey, 
                                    320, 
                                    CIPHER_HDCP_MODE_HDCP_KEY,
                                    CIPHER_HDCP_KEY_RAM_MODE_WRITE,
                                    CIPHER_HDCP_KEY_TYPE_HISI_DEFINED,
                                    HI_FALSE,
                                    u8KeyBuf );
        if ( HI_FAILURE == ret)
        {
            HI_ERR_CIPHER("Encrypt HDCP Key using rootkey in otp failed!\n");
            return HI_FAILURE;
        }            
    }

    memcpy(&(pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey[4]), u8KeyBuf, 320);
	
    ret = DRV_CIPHER_CalcHDCPKeyCRC32(stOtpHdcpKey.HdcpKey, 320, &u32CRC_0);
    if ( HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("CRC32_0 calc failed!\n");
        return HI_FAILURE;
    }
	
    memcpy(&(pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey[324]), &u32CRC_0, 4);
    ret = DRV_CIPHER_CalcHDCPKeyCRC32(pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey, (332-4), &u32CRC_1);
    if ( HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("CRC32_1 calc failed!\n");
        return HI_FAILURE;
    }
	
    memcpy(&(pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey[328]), &u32CRC_1, 4);
	
    return HI_SUCCESS;
}

HI_S32 Cipher_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Crc32Result = 0;
    HI_U32 u32CRC32_1;
    HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enKeyType;
    HI_U32 u32Tmp = 0;

    if( NULL == pstFlashHdcpKey)
    {
        HI_ERR_CIPHER("NULL Pointer, Invalid param input!\n");
        return  HI_FAILURE;
    }

    u32Tmp = pstFlashHdcpKey->u8Key[0] & 0xc0;
    if ( 0x00 == u32Tmp)
    {
        enKeyType = CIPHER_HDCP_KEY_TYPE_OTP_ROOT_KEY;
    }
    else if( 0x80 == u32Tmp)
    {
        enKeyType = CIPHER_HDCP_KEY_TYPE_HISI_DEFINED;
    }
    else
    {
        HI_ERR_CIPHER("Invalid keySelect mode input!\n");
        return  HI_FAILURE;
    }
	
    ret = DRV_CIPHER_CalcHDCPKeyCRC32(pstFlashHdcpKey->u8Key, (332-4), &u32Crc32Result);
    if ( HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("HDCP KEY CRC32_1 calc failed!\n");
        return HI_FAILURE;
    }
	
    memcpy((HI_U8 *)&u32CRC32_1, &pstFlashHdcpKey->u8Key[328], 4);
    if ( u32Crc32Result != u32CRC32_1 )
    {
        HI_ERR_CIPHER("HDCP KEY CRC32_1 compare failed!");
        return HI_FAILURE;
    }
	
    ret = DRV_Cipher_CryptoFormatedHDCPKey(pstFlashHdcpKey->u8Key+4,
                                     320,
                                     CIPHER_HDCP_MODE_HDCP_KEY,
                                     CIPHER_HDCP_KEY_RAM_MODE_WRITE,
                                     enKeyType,
                                     HI_TRUE,
                                     NULL);
    if ( HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("HDCP key decrypt final failed!\n");
        return HI_FAILURE;
    }

	(HI_VOID)DRV_Cipher_HDCPTxReadEnable();

    return HI_SUCCESS;
}

