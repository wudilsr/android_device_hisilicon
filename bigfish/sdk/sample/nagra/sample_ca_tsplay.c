/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_tsplay.c
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "nocs_csd_impl.h"
#include "nocs_csd.h"
#include "cfg_nagra.h"
#include "HA.AUDIO.AC3PASSTHROUGH.decode.h"
#include "HA.AUDIO.DOLBYPLUS.decode.h"
#include "nocs_streams.h"
#include "hi_unf_cipher.h"
#include "hi_unf_descrambler.h"
#include "hi_unf_demux.h"

#include "hi3716c_Test_Vectors_1_x.h"


#define PVR_DMX_ID_LIVE             0
#define PVR_DMX_PORT_ID_IP          HI_UNF_DMX_PORT_RAM_0
#define PVR_DMX_PORT_ID_DVB         HI_UNF_DMX_PORT_TUNER_0
#define PVR_DMX_PORT_ID_PLAYBACK    HI_UNF_DMX_PORT_RAM_1
#define PVR_DMX_ID_REC              1

/**CNcomment:DEMUX ID∂®“Â*/  //get from X5HD hi_unf_demux.h
#define HI_UNF_DMX_ID_0_PLAY            0
#define HI_UNF_DMX_ID_1_REC             1
#define HI_UNF_DMX_ID_2_REC             2
#define HI_UNF_DMX_ID_3_REC             3
#define HI_UNF_DMX_ID_4_PLAY            4


#define NAGRA_TEST_PRINT(fmt, args...)\
do\
{\
    HI_DEBUG_NAGRA("%s() %d, " fmt, __FUNCTION__, __LINE__, ##args);\
}while(0)

#define NAGRA_TEST_CHECK_NULL_PTR(ptr)\
do{\
    if(NULL == ptr )\
    {\
        HI_DEBUG_NAGRA("%s() %d, null pointer.\n", __FUNCTION__, __LINE__);\
        return HI_FAILURE;\
    }\
}while(0)

#define NAGRA_TEST_CHECK_HANDLE(pHandle)\
do{\
    if((0 == pHandle) || (0xFFFFFFFF == pHandle))\
    {\
        HI_DEBUG_NAGRA("%s() %d, invalid handle.\n", __FUNCTION__, __LINE__);\
        return HI_FAILURE;\
    }\
}while(0)
#define NAGRA_TEST_TS_READ_SIZE    (188*128)   // For payload mode, should read not more than 128 ts packets


static HI_U32 g_Nuid_Index = 0;
static TCsdUnsignedInt16   g_xEmi = PAYLOAD_AES_CBC_IDSA;
static HI_HANDLE   g_hAvplay = 0;

static pthread_mutex_t g_TsMutex;

PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;

FILE               *g_pTsFile = HI_NULL;
static HI_BOOL     g_bStopTsThread = HI_FALSE;
static HI_HANDLE          g_TsBuf;

typedef enum{
    NAGRA_TEST_UNSCRAMBLED,
    NAGRA_TEST_HOSTKEY_SCRAMBLED,
    NAGRA_TEST_CONTENTKEY_SCRAMBLED,
    NAGRA_TEST_SYMMETRICCONTENTKEY_SCRAMBLED,
    NAGRA_TEST_KLT_CONTENTKEY_SCRAMBLED
}NAGRA_TEST_SCRAMBLE_TYPE_E;

static NAGRA_TEST_SCRAMBLE_TYPE_E dscKeyMode = NAGRA_TEST_UNSCRAMBLED;
static TCsdDscKeyPathHandle dscKeyPathHandle;

extern HI_S32 HI_MPI_DMX_GetTSBuffer(HI_HANDLE hTsBuffer, HI_U32 u32ReqLen,
                              HI_UNF_STREAM_BUF_S *pstData, HI_U32 *pu32PhyAddr, HI_U32 u32TimeOutMs);

/*Turn 4Bytes Vector into int*/
/*lint -save -e818 ignored by m00190812*/
HI_U32 convertToInt(TCsd4BytesVector pVector)
{
    HI_U32 Result = 0;
    HI_U32 i = 0;

    if(HI_NULL == pVector)
    {
        return 0x0;
    }

    for ( i = 0 ; i < 4 ; i++ )
    {
        Result = (Result << 8) | pVector[i];
    }

    return Result;
}

static HI_S32 NagraTestApp_CreateDescrambler(HI_U32 u32DemuxID, HI_HANDLE hDSCAvplay, TCsdDscKeyPathHandle* pxDscKeyPathHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_DMX_DESCRAMBLER_ATTR_S stDesAttr;
    HI_HANDLE hDescrambler;

    NAGRA_TEST_CHECK_NULL_PTR(pxDscKeyPathHandle);
    NAGRA_TEST_CHECK_HANDLE(hDSCAvplay);
    
    /*Set descrambler attribute*/
    memset(&stDesAttr, 0, sizeof(HI_UNF_DMX_DESCRAMBLER_ATTR_S));
    if (NAGRA_TEST_UNSCRAMBLED == dscKeyMode)
    {
        NAGRA_TEST_PRINT("unscrambled service, no need to create descrambler.\n");
        return HI_FAILURE;
    }
    else if (NAGRA_TEST_HOSTKEY_SCRAMBLED == dscKeyMode)
    {
        stDesAttr.enCaType = HI_UNF_DMX_CA_NORMAL;
    }
    else if ((NAGRA_TEST_CONTENTKEY_SCRAMBLED == dscKeyMode) || (NAGRA_TEST_KLT_CONTENTKEY_SCRAMBLED == dscKeyMode) || (NAGRA_TEST_SYMMETRICCONTENTKEY_SCRAMBLED == dscKeyMode))
    {
        stDesAttr.enCaType = HI_UNF_DMX_CA_ADVANCE;
    }
    stDesAttr.enEntropyReduction = HI_UNF_DMX_CA_ENTROPY_REDUCTION_CLOSE;
    
    switch (g_xEmi)
    {
        case DVB_CSA_V2 :
        {
            stDesAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2;
            break;
        }
        case DVB_CSA_V3 :
        {
            stDesAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3;
            break;
        }
        case AES_CBC_IDSA:
        {
            stDesAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_IPTV;
            break;
        }
        case AES_ECB:
        {
            stDesAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_ECB;
            break;
        }
        case AES_CBC_CI:
        {
            stDesAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CI;
            break;
        }
        default:
        {
            NAGRA_TEST_PRINT("not supported EMI type for DSC, EMI= 0x%04x!\n", g_xEmi);
            return HI_FAILURE;
        }
    }

    /*DSC handle are created here*/
    Ret = HI_UNF_DMX_CreateDescramblerExt(u32DemuxID, &stDesAttr, &(pxDscKeyPathHandle->hDescrambler));
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("Create Descrambler ERROR! Ret = 0x%x\n", Ret);
        return HI_FAILURE;
    }
     
    /*Get video and audio handle*/
    Ret = HI_UNF_AVPLAY_GetDmxVidChnHandle(hDSCAvplay, &pxDscKeyPathHandle->hDmxVidChn);
    Ret |= HI_UNF_AVPLAY_GetDmxAudChnHandle(hDSCAvplay, &pxDscKeyPathHandle->hDmxAudChn); 
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("HI_UNF_AVPLAY_GetDmxChnHandle failed:%x\n",Ret);
        goto _DESTROY_DESCRAMBLER;
    }
    
    /*Attach the descrambler with the video/audio channel*/
    Ret = HI_UNF_DMX_GetDescramblerKeyHandle(pxDscKeyPathHandle->hDmxVidChn, &hDescrambler);
    if (HI_SUCCESS != Ret)
    {
        if (HI_ERR_DMX_NOATTACH_KEY == Ret)
        {
            (HI_VOID)HI_UNF_DMX_AttachDescrambler(pxDscKeyPathHandle->hDescrambler, pxDscKeyPathHandle->hDmxVidChn);
        }
        else
        {
            NAGRA_TEST_PRINT("Get Descrambler Key Handle ERROR! Ret = 0x%x\n",Ret);
            goto _DESTROY_DESCRAMBLER;
        }
    }
    else
    {
        if ((hDescrambler != pxDscKeyPathHandle->hDescrambler))
        {
            (HI_VOID)HI_UNF_DMX_DetachDescrambler(hDescrambler, pxDscKeyPathHandle->hDmxVidChn);
            (HI_VOID)HI_UNF_DMX_AttachDescrambler(pxDscKeyPathHandle->hDescrambler, pxDscKeyPathHandle->hDmxVidChn);
        }
    }
    
    Ret = HI_UNF_DMX_GetDescramblerKeyHandle(pxDscKeyPathHandle->hDmxAudChn, &hDescrambler);
    if (HI_SUCCESS != Ret)
    {
        if (HI_ERR_DMX_NOATTACH_KEY == Ret)
        {
            (HI_VOID)HI_UNF_DMX_AttachDescrambler(pxDscKeyPathHandle->hDescrambler, pxDscKeyPathHandle->hDmxAudChn);
        }
        else
        {
            NAGRA_TEST_PRINT("Get Descrambler Key Handle ERROR! Ret = 0x%x\n",Ret);
            goto _DESTROY_DESCRAMBLER;
        }
    }
    else
    {
        if ((hDescrambler != pxDscKeyPathHandle->hDescrambler))
        {
            (HI_VOID)HI_UNF_DMX_DetachDescrambler(hDescrambler, pxDscKeyPathHandle->hDmxAudChn);
            (HI_VOID)HI_UNF_DMX_AttachDescrambler(pxDscKeyPathHandle->hDescrambler, pxDscKeyPathHandle->hDmxAudChn);
        }
    }
    return HI_SUCCESS;
    
_DESTROY_DESCRAMBLER:
    (HI_VOID)HI_UNF_DMX_DestroyDescrambler(pxDscKeyPathHandle->hDescrambler);
    return Ret;
}

static HI_S32 NagraTestApp_DestroyDescrambler(TCsdDscKeyPathHandle*    pxDscKeyPathHandle)
{
    HI_S32 ret = HI_SUCCESS;
    NAGRA_TEST_CHECK_NULL_PTR(pxDscKeyPathHandle);
    NAGRA_TEST_CHECK_HANDLE(pxDscKeyPathHandle->hDescrambler);

    ret = HI_UNF_DMX_DetachDescrambler(pxDscKeyPathHandle->hDescrambler, pxDscKeyPathHandle->hDmxVidChn);
    if (HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("Detach video from Descrambler filure.\n");
    }
    
    ret = HI_UNF_DMX_DetachDescrambler(pxDscKeyPathHandle->hDescrambler, pxDscKeyPathHandle->hDmxAudChn);
    if (HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("Detach audio from Descrambler filure.\n");
    }
    
    ret = HI_UNF_DMX_DestroyDescrambler(pxDscKeyPathHandle->hDescrambler);
    if (HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("Destroy Descrambler filure.\n");
    }
    
    memset(pxDscKeyPathHandle, 0, sizeof(TCsdDscKeyPathHandle));
    return HI_SUCCESS;
}

static HI_S32 NagraTestApp_EcmParse(HI_U8 *pu8Data, HI_U32 size)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 u8OddCWIndex,u8EvenCWIndex;
    HI_U8 u8EcmTableId;
    HI_U8 *pu8OddCW = NULL;
    HI_U8 *pu8EvenCW = NULL;
    HI_U8   u8KeySize = 16;
    const TCsdDscCipheredProtectingKeys dscProtectingKeys = {{0}};
    static HI_U8 u8OddCW[16];
    static HI_U8 u8EvenCW[16];

    if (NULL == pu8Data)
    {
        NAGRA_TEST_PRINT("null pointer.\n");
        return HI_FAILURE;
    }
        
    if (0 == size)
    {
        return HI_FAILURE;
    }
    
    switch (g_xEmi)
    {
        case DVB_CSA_V2:
        {
            u8KeySize = 8;
            memcpy(dscProtectingKeys, dsc2CipheredProtectingKeysTable[g_Nuid_Index], sizeof(dsc2CipheredProtectingKeysTable[g_Nuid_Index]));
            break;
        }
        case DVB_CSA_V3:
        {
            u8KeySize = 16;
            memcpy(dscProtectingKeys, dsc3CipheredProtectingKeysTable[g_Nuid_Index], sizeof(dsc3CipheredProtectingKeysTable[g_Nuid_Index]));
            break;
        }
        case AES_CBC_IDSA:
        case AES_ECB:
        case AES_CBC_CI:
        {
            u8KeySize = 16;
            memcpy(dscProtectingKeys, dsc4CipheredProtectingKeysTable[g_Nuid_Index], sizeof(dsc4CipheredProtectingKeysTable[g_Nuid_Index]));
            break;
        }
        default:
            u8KeySize = 16;
            break;
    }
    
    u8EcmTableId = *pu8Data;
    
    if (NAGRA_ODD_TABLE_ID == u8EcmTableId)
    {
        pu8OddCW = pu8Data + 7;

        pu8EvenCW = pu8Data + 7 + u8KeySize;
        
        u8OddCWIndex = *(pu8Data + 7 + u8KeySize * 2);
        
        u8EvenCWIndex = *(pu8Data + 8 + u8KeySize * 2);
    }
    else if (NAGRA_EVEN_TABLE_ID == u8EcmTableId)
    {
        pu8EvenCW = pu8Data + 7;
        
        pu8OddCW = pu8Data + 7 + u8KeySize;
        
        u8EvenCWIndex = *(pu8Data + 7 + u8KeySize * 2);
        
        u8OddCWIndex = *(pu8Data + 8 + u8KeySize * 2);
    }
    else
    {
        NAGRA_TEST_PRINT("invalid ECM table id 0x%x\n",u8EcmTableId);
        return HI_FAILURE;
    }

    if (memcmp(u8OddCW, pu8OddCW, u8KeySize) || memcmp(u8EvenCW, pu8EvenCW, u8KeySize))
    {
        pthread_mutex_lock(&g_TsMutex);
        memcpy(u8OddCW, pu8OddCW, u8KeySize);
        memcpy(u8EvenCW, pu8EvenCW, u8KeySize);
        pthread_mutex_unlock(&g_TsMutex);

        if (AES_CBC_CI == g_xEmi)
        {
            memset(dscKeyPathHandle.dscIVAesCIplusPayload, 0, sizeof(dscKeyPathHandle.dscIVAesCIplusPayload));
            memcpy(dscKeyPathHandle.dscIVAesCIplusPayload, dscInitializationVectorAesCIplusPayload, sizeof(dscInitializationVectorAesCIplusPayload));
        }
        if (AES_CBC_IDSA == g_xEmi)
        {
            memset(dscKeyPathHandle.dscIVAesCIplusPayload, 0, sizeof(dscKeyPathHandle.dscIVAesCIplusPayload));
        }

        if (NAGRA_TEST_HOSTKEY_SCRAMBLED == dscKeyMode)
        {
            ret = csdSetClearTextDscHostKeys(g_xEmi,
                        u8OddCW,
                        u8KeySize,
                        u8EvenCW,
                        u8KeySize,
                        &dscKeyPathHandle);
            if (CSD_NO_ERROR != ret)
            {
                NAGRA_TEST_PRINT("csdSetClearTextDscHostKeys failed! ret = 0x%x\n", ret);
            }
        }
        else if ((NAGRA_TEST_CONTENTKEY_SCRAMBLED == dscKeyMode) ||
            (NAGRA_TEST_SYMMETRICCONTENTKEY_SCRAMBLED == dscKeyMode))
        {
            ret = csdSetProtectedDscContentKeys(g_xEmi,
                        dscProtectingKeys,
                        u8OddCW,
                        u8KeySize,
                        u8EvenCW,
                        u8KeySize,
                        &dscKeyPathHandle);
            if (CSD_NO_ERROR != ret)
            {
                NAGRA_TEST_PRINT("csdSetProtectedDscContentKeys failed! ret = 0x%x\n", ret);
            }
        }
        else if (NAGRA_TEST_KLT_CONTENTKEY_SCRAMBLED == dscKeyMode)
        {
            ret = csdSetProtectedDscContentKeys(g_xEmi,
                        klt2CipheredProtectingKeysTable[g_Nuid_Index],
                        u8OddCW,
                        u8KeySize,
                        u8EvenCW,
                        u8KeySize,
                        &dscKeyPathHandle);
            if (CSD_NO_ERROR != ret)
            {
                printf("%s() %d, csdSetProtectedDscContentKeys failed! ret = 0x%x\n", __FUNCTION__,__LINE__,ret);
            }
        }
    }

    return ret;
}

static HI_U32 u32EcmThreadRunFlag = 0;

static HI_VOID *NagraTestApp_Thread_EcmGet(HI_VOID *arg)
{
    HI_S32 ret;
    HI_U32 i;
    HI_U32 u32AcquireNum = 1;
    HI_U32 pu32AcquiredNum = 0;
    HI_UNF_DMX_DATA_S pstBuf[10];
    HI_HANDLE hEcmChannel = 0;

    hEcmChannel = *((HI_U32 *)arg);
    HI_DEBUG_NAGRA("NagraTestApp_Thread_EcmGet start, ECM channel handle is 0x%x!\n", hEcmChannel);

    while (0 != u32EcmThreadRunFlag)
    {
        ret = HI_UNF_DMX_AcquireBuf(hEcmChannel, u32AcquireNum, &pu32AcquiredNum, pstBuf, 5000);
        if (HI_SUCCESS != ret)
        {
            NAGRA_TEST_PRINT("call HI_UNF_DMX_AcquireBuf failed, ret=0x%x!\n",ret);
            usleep(10 * 1000);
            continue;
        }
        
        for (i = 0; i < pu32AcquiredNum; i++)
        {
            ret = NagraTestApp_EcmParse(pstBuf[i].pu8Data, pstBuf[i].u32Size);
            if (HI_SUCCESS != ret)
            {
                break;
            }
        }
        
        ret = HI_UNF_DMX_ReleaseBuf(hEcmChannel, pu32AcquiredNum, pstBuf);
        if (HI_SUCCESS != ret)
        {
            NAGRA_TEST_PRINT("call HI_UNF_DMX_ReleaseBuf failed, ret=0x%x!\n", ret);
        }
    }
    
    HI_DEBUG_NAGRA("NagraTestApp_Thread_EcmGet over!\n");
    return NULL;
}

static HI_S32 NagraTestApp_Get_ECM(HI_BOOL bEnable, HI_U32 u32DemuxID, HI_U32 u32EcmPID)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_DMX_CHAN_ATTR_S stChnAttr;
    HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;
    static HI_HANDLE hChannel = 0;
    static HI_HANDLE hFilter1 = 0;
    static pthread_t   tEcmThread = 0;
    HI_U8 u8Match[DMX_FILTER_MAX_DEPTH];
    HI_U8 u8Mask[DMX_FILTER_MAX_DEPTH];
    HI_U8 u8Negate[DMX_FILTER_MAX_DEPTH];
    
    if (!bEnable)
    {
        goto THREAD_DESTROY;
    }

    if (INVALID_TSPID == u32EcmPID)
    {
        NAGRA_TEST_PRINT("Invalid pid!\n");
        return HI_FAILURE;
    }

    if (0 != hChannel)
    {
        NAGRA_TEST_PRINT("ECM channel has been created!\n");
        return HI_FAILURE;
    }

    /*Creat ECM Filter*/    
    ret = HI_UNF_DMX_GetChannelDefaultAttr(&stChnAttr);
    if (HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_DMX_GetChannelDefaultAttr failed, ret=0x%x!\n", ret);
        return ret;
    }

    stChnAttr.enChannelType = HI_UNF_DMX_CHAN_TYPE_SEC;
    stChnAttr.enCRCMode = HI_UNF_DMX_CHAN_CRC_MODE_FORBID;
    stChnAttr.u32BufSize = 16 * 1024;
    ret = HI_UNF_DMX_CreateChannel(u32DemuxID, &stChnAttr, &hChannel);
    if (HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_DMX_CreateChannel failed, ret=0x%x!\n", ret);
        return ret;
    }

    /* set filter attr */
    memset(u8Mask, 0, DMX_FILTER_MAX_DEPTH);
    memset(u8Match, 0, DMX_FILTER_MAX_DEPTH);
    memset(u8Negate, 0, DMX_FILTER_MAX_DEPTH);
    stFilterAttr.u32FilterDepth = 1;
    u8Match[0] = 0x80;
    u8Mask[0] = 0x01;
    memcpy(stFilterAttr.au8Mask, u8Mask, DMX_FILTER_MAX_DEPTH);
    memcpy(stFilterAttr.au8Match, u8Match, DMX_FILTER_MAX_DEPTH);
    memcpy(stFilterAttr.au8Negate, u8Negate, DMX_FILTER_MAX_DEPTH);
    
    ret = HI_UNF_DMX_CreateFilter(0, &stFilterAttr, &hFilter1);
    if (HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_DMX_CreateFilter failed, ret=0x%x!\n",ret);
        goto CHN_DESTROY;
    }

    ret = HI_UNF_DMX_AttachFilter(hFilter1, hChannel);
    if (HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_DMX_AttachFilter failed, ret=0x%x!\n",ret);
        (HI_VOID)HI_UNF_DMX_DestroyFilter(hFilter1);
        goto CHN_DESTROY;
    }

    ret = HI_UNF_DMX_SetChannelPID(hChannel, u32EcmPID);
    ret |= HI_UNF_DMX_OpenChannel(hChannel);
    if (HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_DMX_OpenChannel failed, ret=0x%x!\n",ret);
        goto FILTER_DESTROY;
    }

    u32EcmThreadRunFlag = 1;
    ret = pthread_create(&tEcmThread, HI_NULL, NagraTestApp_Thread_EcmGet, &hChannel);
    if (ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("create ECM process thread err.\n");
        goto CHANNEL_CLOSE;
    }

    return HI_SUCCESS;
    
THREAD_DESTROY:
    if (0 != tEcmThread)
    {
        u32EcmThreadRunFlag = 0;
        (HI_VOID)pthread_join(tEcmThread, NULL);
        tEcmThread = 0;
    }

CHANNEL_CLOSE:
    if (0 != hChannel)
    {
        (HI_VOID)HI_UNF_DMX_CloseChannel(hChannel);
    }

FILTER_DESTROY:
    if ((0 != hChannel) && (0 != hFilter1))
    {
        (HI_VOID)HI_UNF_DMX_DetachFilter(hFilter1, hChannel);
        (HI_VOID)HI_UNF_DMX_DestroyFilter(hFilter1);
        hFilter1 = 0;
    }
CHN_DESTROY:
    if (0 != hChannel)
    {
        (HI_VOID)HI_UNF_DMX_DestroyChannel(hChannel);
        hChannel = 0;
    }
    
    return ret;
}



HI_S32 NagaTestApp_SwitchService(HI_U32 u32ProgNum)
{
    HI_S32 Ret = HI_SUCCESS;
    
    if (0 != dscKeyPathHandle.hDescrambler)
    {
        (HI_VOID)NagraTestApp_Get_ECM(HI_FALSE, HI_UNF_DMX_ID_0_PLAY, INVALID_TSPID);
        (HI_VOID)NagraTestApp_DestroyDescrambler(&dscKeyPathHandle);
        memset(&dscKeyPathHandle, 0, sizeof(TCsdDscKeyPathHandle));
    }

    Ret = HIADP_AVPlay_PlayProg(g_hAvplay, g_pProgTbl, u32ProgNum, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call PlayProg failed.\n");
        return HI_FAILURE;
    }

    if (NAGRA_TEST_UNSCRAMBLED == dscKeyMode)
    {
        return HI_SUCCESS;
    }
    
    Ret = NagraTestApp_CreateDescrambler(HI_UNF_DMX_ID_0_PLAY, g_hAvplay, &dscKeyPathHandle);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("NagraTestApp_CreateDescrambler failure, Ret = 0x%x\n",Ret);
        return HI_SUCCESS;
    }

    HI_DEBUG_NAGRA("\nprogram id : %d\n",g_pProgTbl->proginfo[u32ProgNum].ProgID);
//    HI_DEBUG_NAGRA("Descrambler  : 0x%x\n",dscKeyPathHandle.hDescrambler);
//    HI_DEBUG_NAGRA("VidCh handle : 0x%x\n",dscKeyPathHandle.hDmxVidChn);
//    HI_DEBUG_NAGRA("AudCh handle : 0x%x\n",dscKeyPathHandle.hDmxAudChn);

    if (NAGRA_TEST_HOSTKEY_SCRAMBLED == dscKeyMode)
    {
        Ret = NagraTestApp_Get_ECM(HI_TRUE, HI_UNF_DMX_ID_0_PLAY, hostKeyScrambledServiceECMPid);
    }
    else if ((NAGRA_TEST_CONTENTKEY_SCRAMBLED == dscKeyMode))
    {
        Ret = NagraTestApp_Get_ECM(HI_TRUE, HI_UNF_DMX_ID_0_PLAY, contentKeyScrambledServiceECMPid);
    }
    else if ((NAGRA_TEST_SYMMETRICCONTENTKEY_SCRAMBLED == dscKeyMode) || (NAGRA_TEST_KLT_CONTENTKEY_SCRAMBLED == dscKeyMode))
    {
        Ret = NagraTestApp_Get_ECM(HI_TRUE, HI_UNF_DMX_ID_0_PLAY, symmetricalContentKeyScrambledServiceECMPid);
    }
    
    return Ret;
}

HI_VOID *NagraTestApp_Thread_DSC_TS_Decrypt(HI_VOID *argv)
{
    HI_S32                Ret = HI_SUCCESS;
    HI_UNF_STREAM_BUF_S   StreamBuf;
    HI_U32                Readlen;

    while (!g_bStopTsThread)
    {
        pthread_mutex_lock(&g_TsMutex);
        Ret = HI_UNF_DMX_GetTSBuffer(g_TsBuf, NAGRA_TEST_TS_READ_SIZE, &StreamBuf, 1000);

        if (Ret != HI_SUCCESS)
        {
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), NAGRA_TEST_TS_READ_SIZE, g_pTsFile);
        if(Readlen == 0)
        {
//            HI_DEBUG_NAGRA("read ts file end and rewind!\n");
            rewind(g_pTsFile);
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }
        
        Ret = HI_UNF_DMX_PutTSBuffer(g_TsBuf, Readlen);
        if (Ret != HI_SUCCESS )
        {
            NAGRA_TEST_PRINT("call HI_UNF_DMX_PutTSBuffer failed, Ret = 0x%08x\n", Ret); 
        }
        pthread_mutex_unlock(&g_TsMutex);
        usleep(1*1000);
    }

    Ret = HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    if (Ret != HI_SUCCESS )
    {
        NAGRA_TEST_PRINT("call HI_UNF_DMX_ResetTSBuffer failed.\n");
    }

    return NULL;
}

static HI_S32 NagraTestApp_DSC_TS_Play(HI_BOOL bEnable)
{
    HI_S32                  Ret = HI_SUCCESS;
    static HI_HANDLE               hWin = 0;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    static pthread_t   g_TsThd;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;

    HI_HANDLE hTrack;       //++
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;       //++

    if(!bEnable)
    {
        goto AVPLAY_STOP;
    }

    if(0 != g_hAvplay)
    {
        NAGRA_TEST_PRINT("AV player has been created.\n");
        return HI_FAILURE;
    }
    
    Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HIADP_Snd_Init failed.\n");
        return HI_FAILURE;
    }

    Ret = HIADP_Disp_Init(DSC_ENC_FMT);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HIADP_Disp_DeInit failed.\n");
        goto SND_DEINIT;
    }

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    Ret |= HIADP_VO_CreatWin(HI_NULL,&hWin);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HIADP_VO_Init failed.\n");
        (HI_VOID)HIADP_VO_DeInit();
        goto DISP_DEINIT;
    }

    Ret = HI_UNF_DMX_Init();
    Ret |= HI_UNF_DMX_AttachTSPort(HI_UNF_DMX_ID_0_PLAY,/*HI_UNF_DMX_PORT_3_RAM*/HI_UNF_DMX_PORT_RAM_0);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_DMX_Init failed.\n");
        goto VO_DEINIT;
    }

    Ret = HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_RAM_0, 0x200000, &g_TsBuf);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HI_UNF_DMX_CreateTSBuffer failed.\n");
        goto DMX_DEINIT;
    }

    Ret = HIADP_AVPlay_RegADecLib();
    Ret |= HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HI_UNF_AVPLAY_Init failed.\n");
        goto DESTROY_TS_BUFFER;
    }

    Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    AvplayAttr.u32DemuxId = HI_UNF_DMX_ID_0_PLAY;
    Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &g_hAvplay);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    Ret |= HI_UNF_AVPLAY_ChnOpen(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto CHN_CLOSE;
    }

    Ret = HI_UNF_VO_AttachWindow(hWin, g_hAvplay);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_VO_AttachWindow failed.\n");
        goto CHN_CLOSE;
    }
    Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr,&hTrack);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HI_UNF_SND_CreateTrack failed.\n");
        goto WIN_DETACH;
    }

    //Ret = HI_UNF_SND_Attach(HI_UNF_SND_0, g_hAvplay, HI_UNF_SND_MIX_TYPE_MASTER, 100);
    Ret = HI_UNF_SND_Attach(hTrack, g_hAvplay);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HI_SND_Attach failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_AVPLAY_GetAttr(g_hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_NONE;
    Ret |= HI_UNF_AVPLAY_SetAttr(g_hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    (HI_VOID)pthread_mutex_init(&g_TsMutex,NULL);
    g_bStopTsThread = HI_FALSE;

    (HI_VOID)pthread_create(&g_TsThd, HI_NULL, NagraTestApp_Thread_DSC_TS_Decrypt, NULL);
    HIADP_Search_Init();
    (HI_VOID)HIADP_Search_GetAllPmt(HI_UNF_DMX_ID_0_PLAY, &g_pProgTbl);

    return HI_SUCCESS;

AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    (HI_VOID)HI_UNF_AVPLAY_Stop(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &Stop);
    (HI_VOID)HI_UNF_AVPLAY_Stop(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

    HIADP_Search_DeInit();

    g_bStopTsThread = HI_TRUE;
    (HI_VOID)pthread_join(g_TsThd, HI_NULL);
    (HI_VOID)pthread_mutex_destroy(&g_TsMutex);
    
SND_DETACH:
    if (g_hAvplay != 0)
    {
        (HI_VOID)HI_UNF_SND_Detach(hTrack, g_hAvplay);
    }
WIN_DETACH:
    if ((g_hAvplay != 0) && (hWin != 0))
    {
        (HI_VOID)HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
        (HI_VOID)HI_UNF_VO_DetachWindow(hWin, g_hAvplay);
    }
CHN_CLOSE:
    if (g_hAvplay != 0)
    {
        (HI_VOID)HI_UNF_AVPLAY_ChnClose(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        (HI_VOID)HI_UNF_AVPLAY_ChnClose(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

        (HI_VOID)HI_UNF_AVPLAY_Destroy(g_hAvplay);
        g_hAvplay = 0;
    }
AVPLAY_DEINIT:
    (HI_VOID)HI_UNF_AVPLAY_DeInit();

DESTROY_TS_BUFFER:
    if (0 != g_TsBuf)
    {
        (HI_VOID)HI_UNF_DMX_DestroyTSBuffer(g_TsBuf);
        g_TsBuf = 0;
    }

DMX_DEINIT:
    (HI_VOID)HI_UNF_DMX_DetachTSPort(HI_UNF_DMX_ID_0_PLAY);
    (HI_VOID)HI_UNF_DMX_DeInit();

VO_DEINIT:
    if (hWin != 0)
    {
        (HI_VOID)HI_UNF_VO_DestroyWindow(hWin);
        (HI_VOID)HIADP_VO_DeInit();
        hWin = 0;
    }
DISP_DEINIT:
    (HI_VOID)HIADP_Disp_DeInit();

SND_DEINIT:
    (HI_VOID)HIADP_Snd_DeInit();
    
    return Ret;
}


HI_S32 main()
{
    HI_S32                  Ret = HI_SUCCESS;
    HI_CHAR                 InputCmd[32];
    HI_CHAR *szFileName = HI_NULL;
    HI_CHAR streamFileName[64] = {0};
    TCsdStatus            csdRet;
    TCsd4BytesVector nuid;
    HI_U32 intNuid = 0;
    
    Ret = HI_SYS_Init();
//    Ret |= HI_SYS_PreAV(NULL);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("Initialize ERROR!!!!Ret = 0x%x\n", Ret);
        return Ret;
    }
    
    csdRet = csdInitialize(NULL);
    if (CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("Initialize ERROR!!!!csdRet = 0x%x\n", csdRet);
        return csdRet;
    }

    HI_TRACE_LOG("[DSC_4] Select the EMI?\n");
    HI_TRACE_LOG("[1]: EMI 0x0020 \n");
    HI_TRACE_LOG("[2]: EMI 0x0021 \n");
    HI_TRACE_LOG("[3]: EMI 0x0022 \n");
    HI_TRACE_LOG("[4]: EMI 0x0000 \n");
    HI_TRACE_LOG("[5]: EMI 0x0001 \n");
    (HI_VOID)fgets(InputCmd, 30, stdin);

    if ('1' == InputCmd[0])
    {
        g_xEmi = AES_CBC_IDSA;
    }
    else if ('2' == InputCmd[0])
    {
        g_xEmi = AES_ECB;
    }
    else if ('3' == InputCmd[0])
    {
        g_xEmi = AES_CBC_CI;
    }
    else if ('4' == InputCmd[0])
    {
        g_xEmi = DVB_CSA_V2;
    }
    else if ('5' == InputCmd[0])
    {
        g_xEmi = DVB_CSA_V3;
    }
    else
    {
        HI_TRACE_LOG("Invalid choice. Shall be only 1, 2 or 3.\n");
        goto TERMINATE;
    }

    /*lint -emacro(303, NOCS_STREAM_NAME_PARSER)    ignore by m00190812  */ 
    NOCS_STREAM_NAME_PARSER("DSC", "Cable", g_xEmi, szFileName, 64);
    (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/%s", SCR_STREAM_PATH, szFileName);

    g_pTsFile = NULL;
    g_pTsFile = fopen(streamFileName, "rb");
    if (!g_pTsFile)
    {
        NAGRA_TEST_PRINT("open file %s error!\n", streamFileName);
        Ret = HI_FAILURE;
        goto TERMINATE;
    }

    Ret = NagraTestApp_DSC_TS_Play(HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        goto CLOSEFILE;
    }
    
    dscKeyMode = NAGRA_TEST_UNSCRAMBLED;

    Ret = HIADP_AVPlay_PlayProg(g_hAvplay, g_pProgTbl, 0, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("Play DSC service failed.\n");
        goto STOP;
    }

    csdRet = csdGetNuid(nuid);
    if (CSD_NO_ERROR != csdRet)
    {
        NAGRA_TEST_PRINT("csdGetNuid failed! csdRet = 0x%x\n", csdRet);
        goto STOP;
    }
    
    intNuid = convertToInt(nuid);
    
    for ( g_Nuid_Index = 0 ; g_Nuid_Index < MAX_NUID_NUMBER ; g_Nuid_Index++ )
    {
        if (intNuid == nagraNUID[g_Nuid_Index])
        {
            break;
        }
    }
    
    if (g_Nuid_Index == MAX_NUID_NUMBER)
    {
        NAGRA_TEST_PRINT("NUID invalid!\n");
        //Ret = HI_FAILURE;
        //goto STOP;
        g_Nuid_Index = 0;
    }

    while (1)
    {
        HI_TRACE_LOG("0 -- Unscrambled_Service\n");
        HI_TRACE_LOG("1 -- HostKey_Scrambled_Service\n");
        HI_TRACE_LOG("2 -- ContentKey_Scrambled_Service\n");
        HI_TRACE_LOG("3 -- Symmetrical_Key_Scrambled_Service\n");
        HI_TRACE_LOG("q -- quit\n");
        (HI_VOID)fgets(InputCmd, 30, stdin);
        if ('0' == InputCmd[0])
        {
            dscKeyMode = NAGRA_TEST_UNSCRAMBLED;
            (HI_VOID)NagaTestApp_SwitchService(0);
        }
        else if ('1' == InputCmd[0])
        {
            dscKeyMode = NAGRA_TEST_HOSTKEY_SCRAMBLED;
            (HI_VOID)NagaTestApp_SwitchService(1);
        }
        else if ('2' == InputCmd[0])
        {
            dscKeyMode = NAGRA_TEST_CONTENTKEY_SCRAMBLED;
            (HI_VOID)NagaTestApp_SwitchService(2);
        }
        else if (('3' == InputCmd[0]))
        {
            dscKeyMode = NAGRA_TEST_SYMMETRICCONTENTKEY_SCRAMBLED;
            (HI_VOID)NagaTestApp_SwitchService(3);
        }
        else if ('q' == InputCmd[0])
        {
            HI_TRACE_LOG("prepare to quit!\n");
            (HI_VOID)NagraTestApp_Get_ECM(HI_FALSE, HI_UNF_DMX_ID_0_PLAY, INVALID_TSPID);
            (HI_VOID)NagraTestApp_DestroyDescrambler(&dscKeyPathHandle);
            break;
        }
        else
        {
            HI_TRACE_LOG("Invalid choice. Shall be only 0, 1, 2 or 3.\n");
        }
    }

STOP:
    (HI_VOID)NagraTestApp_DSC_TS_Play(HI_FALSE);

CLOSEFILE:
    if (NULL != g_pTsFile)
    {
        (HI_VOID)fclose(g_pTsFile);
        g_pTsFile = NULL;
    }

TERMINATE:
    (HI_VOID)csdTerminate(NULL);
    (HI_VOID)HI_SYS_DeInit();

    return Ret;
}
