/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_scrplay.c
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

/**CNcomment:DEMUX ID定义*/  //get from X5HD hi_unf_demux.h
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

static TCsdUnsignedInt16   g_xEmi = DVB_CSA_V2;
static HI_HANDLE   g_hAvplay = 0;

PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;

const HI_U8 *HostKeyTable[12][2] = {
    {scrClearTextHostKeyAesPayload1, scrClearTextHostKeyAesPayload2},       // 1 0x0020
    {scrClearTextHostKeyAesPayload1, scrClearTextHostKeyAesPayload2},       // 2 0x0021
    {scrClearTextHostKeyAesPayload1, scrClearTextHostKeyAesPayload2},       // 3 0x0022
    {scrClearTextHostKeyTdesPayload1, scrClearTextHostKeyTdesPayload2},    // 4 0x0040
    {scrClearTextHostKeyTdesPayload1, scrClearTextHostKeyTdesPayload2},    // 5 0x0041
    {scrClearTextHostKeyAesRaw1, scrClearTextHostKeyAesRaw2},               // 6 0x4020
    {scrClearTextHostKeyAesRaw1, scrClearTextHostKeyAesRaw2},               // 7 0x4021
    {scrClearTextHostKeyAesRaw1, scrClearTextHostKeyAesRaw2},               // 8 0x4022
    {scrClearTextHostKeyAesRaw1, scrClearTextHostKeyAesRaw2},               // 9 0x4023
    {scrClearTextHostKeyAesRaw1, scrClearTextHostKeyAesRaw2},               // 10 0x4024
    {scrClearTextHostKeyTdesRaw1, scrClearTextHostKeyTdesRaw2},             // 11 0x4040
    {scrClearTextHostKeyTdesRaw1, scrClearTextHostKeyTdesRaw2}             // 12 0x4041
};

const HI_U8 *ContentKeyTable[12][2] = {
    {scrCipheredContentKeyAesPayload1, scrCipheredContentKeyAesPayload2},       // 1 0x0020
    {scrCipheredContentKeyAesPayload1, scrCipheredContentKeyAesPayload2},       // 2 0x0021
    {scrCipheredContentKeyAesPayload1, scrCipheredContentKeyAesPayload2},       // 3 0x0022
    {scrCipheredContentKeyTdesPayload1, scrCipheredContentKeyTdesPayload2},    // 4 0x0040
    {scrCipheredContentKeyTdesPayload1, scrCipheredContentKeyTdesPayload2},    // 5 0x0041
    {scrCipheredContentKeyAesRaw1, scrCipheredContentKeyAesRaw2},               // 6 0x4020
    {scrCipheredContentKeyAesRaw1, scrCipheredContentKeyAesRaw2},               // 7 0x4021
    {scrCipheredContentKeyAesRaw1, scrCipheredContentKeyAesRaw2},               // 8 0x4022
    {scrCipheredContentKeyAesRaw1, scrCipheredContentKeyAesRaw2},               // 9 0x4023
    {scrCipheredContentKeyAesRaw1, scrCipheredContentKeyAesRaw2},               // 10 0x4024
    {scrCipheredContentKeyTdesRaw1, scrCipheredContentKeyTdesRaw2},             // 11 0x4040
    {scrCipheredContentKeyTdesRaw1, scrCipheredContentKeyTdesRaw2}             // 12 0x4041
};

const HI_U8 *IVTable[12] = {
    scrInitializationVectorAesCbcPayload,       // 1 0x0020
    NULL,                                       // 2 0x0021
    scrInitializationVectorAesCIplusPayload,    // 3 0x0022
    scrInitializationVectorTdesPayload,         // 4 0x0040
    NULL,                                       // 5 0x0041
    scrInitializationVectorAesRaw,              // 6 0x4020
    NULL,                                       // 7 0x4021
    scrInitializationVectorAesRaw,              // 8 0x4022
    scrInitializationVectorAesRaw,              // 9 0x4023
    scrClearIVAdaptiveStream,                   // 10 0x4024
    scrInitializationVectorTdesRaw,             // 11 0x4040
    NULL,                                       // 12 0x4041
};

HI_U32 IVSizeTable[12] = {
    16,    // 1 0x0020
    0,     // 2 0x0021
    16,    // 3 0x0022
    8,     // 4 0x0040
    0,     // 5 0x0041
    16,    // 6 0x4020
    0,     // 7 0x4021
    16,    // 8 0x4022
    16,    // 9 0x4023
    16,    // 10 0x4024
    8,     // 11 0x4040
    0      // 12 0x4041
};

#define NAGRA_SCR_KEY_SIZE  16
#define NAGRA_TEST_TS_READ_SIZE    (188*128)   // For payload mode, should read not more than 128 ts packets

FILE               *g_pTsFile = HI_NULL;
FILE               *g_pRecFile = HI_NULL;
static pthread_mutex_t g_TsMutex;
static HI_BOOL     g_bStopTsThread = HI_FALSE;
static HI_HANDLE          g_TsBuf;

static HI_U8 *g_pu8HostKey = NULL;
static HI_U8 *g_pu8ContentKey = NULL;
static HI_U8 *g_pu8IV = NULL;
HI_U32 g_u32IVSize = 0;

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
        Result = (Result<<8) |pVector[i];
    }

    return Result;
}

static HI_S32 NagraTestApp_SCR_CreateDescrambler(HI_U32 u32DemuxID, HI_HANDLE hSCRAvplay, TCsdScrKeyPathHandle* pxScrKeyPathHandle, HI_BOOL bCipheredKey)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_DMX_DESCRAMBLER_ATTR_S stDesAttr;
    HI_HANDLE hDescrambler;

    NAGRA_TEST_CHECK_NULL_PTR(pxScrKeyPathHandle);
    NAGRA_TEST_CHECK_HANDLE(hSCRAvplay);
    
    /*Set descrambler attribute*/
    memset(&stDesAttr, 0, sizeof(HI_UNF_DMX_DESCRAMBLER_ATTR_S));

    if (HI_TRUE == bCipheredKey)
    {
        stDesAttr.enCaType = HI_UNF_DMX_CA_ADVANCE;
    }
    else
    {
        stDesAttr.enCaType = HI_UNF_DMX_CA_NORMAL;
    }
    
    stDesAttr.enEntropyReduction = HI_UNF_DMX_CA_ENTROPY_REDUCTION_CLOSE;
    
    switch (g_xEmi)
    {
        case PAYLOAD_AES_CBC_IDSA:
        {
            stDesAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_IPTV;
            break;
        }
        case PAYLOAD_AES_ECB:
        {
            stDesAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_ECB;
            break;
        }
        case PAYLOAD_AES_CBC_CI:
        {
            stDesAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CI;
            break;
        }
        default:
        {
            NAGRA_TEST_PRINT("not supported EMI type for SCR, EMI= 0x%04x!\n", g_xEmi);
            return HI_FAILURE;
        }
    }

    /*DSC handle are created here*/
    Ret = HI_UNF_DMX_CreateDescramblerExt(u32DemuxID, &stDesAttr, &(pxScrKeyPathHandle->hDescrambler));
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("Create Descrambler ERROR! Ret = 0x%x\n", Ret);
        return HI_FAILURE;
    }

    /*Get video and audio handle*/
    Ret = HI_UNF_AVPLAY_GetDmxVidChnHandle(hSCRAvplay, &pxScrKeyPathHandle->hDmxVidChn);
    Ret |= HI_UNF_AVPLAY_GetDmxAudChnHandle(hSCRAvplay, &pxScrKeyPathHandle->hDmxAudChn); 
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("HI_UNF_AVPLAY_GetDmxChnHandle failed:%x\n", Ret);
        goto _DESTROY_DESCRAMBLER;
    }
    
    /*Attach the descrambler with the video/audio channel*/
    Ret = HI_UNF_DMX_GetDescramblerKeyHandle(pxScrKeyPathHandle->hDmxVidChn, &hDescrambler);
    if (HI_SUCCESS != Ret)
    {
        if (HI_ERR_DMX_NOATTACH_KEY == Ret)
        {
            (HI_VOID)HI_UNF_DMX_AttachDescrambler(pxScrKeyPathHandle->hDescrambler, pxScrKeyPathHandle->hDmxVidChn);
        }
        else
        {
            NAGRA_TEST_PRINT("Get Descrambler Key Handle ERROR! Ret = 0x%x\n", Ret);
            goto _DESTROY_DESCRAMBLER;
        }
    }
    else
    {
        if ((hDescrambler != pxScrKeyPathHandle->hDescrambler))
        {
            (HI_VOID)HI_UNF_DMX_DetachDescrambler(hDescrambler, pxScrKeyPathHandle->hDmxVidChn);
            (HI_VOID)HI_UNF_DMX_AttachDescrambler(pxScrKeyPathHandle->hDescrambler, pxScrKeyPathHandle->hDmxVidChn);
        }
    }
    
    Ret = HI_UNF_DMX_GetDescramblerKeyHandle(pxScrKeyPathHandle->hDmxAudChn, &hDescrambler);
    if (HI_SUCCESS != Ret)
    {
        if (HI_ERR_DMX_NOATTACH_KEY == Ret)
        {
            (HI_VOID)HI_UNF_DMX_AttachDescrambler(pxScrKeyPathHandle->hDescrambler, pxScrKeyPathHandle->hDmxAudChn);
        }
        else
        {
            NAGRA_TEST_PRINT("Get Descrambler Key Handle ERROR! Ret = 0x%x\n", Ret);
            goto _DESTROY_DESCRAMBLER;
        }
    }
    else
    {
        if ((hDescrambler != pxScrKeyPathHandle->hDescrambler))
        {
            (HI_VOID)HI_UNF_DMX_DetachDescrambler(hDescrambler, pxScrKeyPathHandle->hDmxAudChn);
            (HI_VOID)HI_UNF_DMX_AttachDescrambler(pxScrKeyPathHandle->hDescrambler, pxScrKeyPathHandle->hDmxAudChn);
        }
    }
    return HI_SUCCESS;
    
_DESTROY_DESCRAMBLER:
    (HI_VOID)HI_UNF_DMX_DestroyDescrambler(pxScrKeyPathHandle->hDescrambler);
    return Ret;
}

static HI_S32 NagraTestApp_SCR_DestroyDescrambler(TCsdScrKeyPathHandle*    pxScrKeyPathHandle)
{
    HI_S32 ret = HI_SUCCESS;
    NAGRA_TEST_CHECK_NULL_PTR(pxScrKeyPathHandle);
    NAGRA_TEST_CHECK_HANDLE(pxScrKeyPathHandle->hDescrambler);

    ret = HI_UNF_DMX_DetachDescrambler(pxScrKeyPathHandle->hDescrambler, pxScrKeyPathHandle->hDmxVidChn);
    if(HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("Detach video from Descrambler filure.\n");
    }

    ret = HI_UNF_DMX_DetachDescrambler(pxScrKeyPathHandle->hDescrambler, pxScrKeyPathHandle->hDmxAudChn);
    if(HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("Detach audio from Descrambler filure.\n");
    }

    ret = HI_UNF_DMX_DestroyDescrambler(pxScrKeyPathHandle->hDescrambler);
    if(HI_SUCCESS != ret)
    {
        NAGRA_TEST_PRINT("Destroy Descrambler filure.\n");
    }

    memset(pxScrKeyPathHandle, 0, sizeof(TCsdScrKeyPathHandle));
    return HI_SUCCESS;
}

HI_S32 HI_Nagra_Payload_Decrypt(HI_HANDLE hCipher, HI_U16 u16EMI, HI_U8 * pu8IV, 
                            HI_U8 *pu8Data, HI_U32 u32PhyAddr, HI_U32 size)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32PLen;
    HI_U32 u32SizeThisTime = 0;
    HI_U8  *buf = pu8Data;
    HI_U32 phyaddr = u32PhyAddr;
    HI_U32 offset = 0;
    HI_UNF_CIPHER_DATA_S cipherData[128];
    HI_U32 u32DataPkgNum = 0;
    
    HI_UNF_CIPHER_DATA_S cipherData1[128];
    HI_U32 u32DataPkgNum1 = 0;
    HI_MMZ_BUF_S stCipherBuf;
    HI_UNF_STREAM_BUF_S   ShortBlockBuf[128];

    memset(&stCipherBuf, 0x0, sizeof(HI_MMZ_BUF_S));
    memset(ShortBlockBuf, 0x0, 128 * sizeof(HI_UNF_STREAM_BUF_S));
    if(PAYLOAD_AES_CBC_IDSA == u16EMI)
    {
        /**allocate the buffer to be used to process the data in tail*/
        /*CNcomment:创建用于尾部数据处理的buffer*/
        strncpy(stCipherBuf.bufname, "IDSA_shortBlock", MAX_BUFFER_NAME_SIZE);
        stCipherBuf.bufsize = 128*16;
        stCipherBuf.overflow_threshold = 100;
        stCipherBuf.underflow_threshold = 0;
        ret = HI_MMZ_Malloc(&stCipherBuf);
        if (HI_SUCCESS != ret)
        {
            NAGRA_TEST_PRINT("HI_MMZ_Malloc failed:%x\n",ret);
            return HI_FAILURE;
        }
    }
    
    if(0 != (g_xEmi & NAGRA_EMI_MASK_TDES))
    {
        u32PLen = 8;
    }
    else
    {
        u32PLen = 16;
    }

    /* Get payload and decrypt */
    while (size > 0)
    {
        if (size > 128*188)
        {
            u32SizeThisTime = 128*188;
        }
        else
        {
            u32SizeThisTime = size;
        }

        /*process up to 128 ts packets each time*/
        /*CNcomment:分组处理,每次处理128个ts*/
        for (buf=pu8Data,phyaddr=u32PhyAddr; buf<pu8Data+u32SizeThisTime; buf+=188,phyaddr+=188)
        {
            HI_U8 adaptation_field_control; 
            HI_U8 adaptation_field_length;
            HI_U32 payloadsize,ShortBlockSize;
            
            if (buf[0] != 0x47 )
            {
                 NAGRA_TEST_PRINT(" Not a TS packet\n");
                 continue;
            }

            /**Get the adaptation_field_control field*/
            /*CNcomment:获取adaptation_field_control位 */
            adaptation_field_control = (buf[3] & 0x30) >> 4; 

            /*analyze the adaptaion field*/
            /* CNcomment:下面分析调整字段 */
            adaptation_field_length = 0; 

            /*00 and 10 is invalid payload*/
            /*CNcomment:00和10视为无有效负载 */
            if ((adaptation_field_control & 0x01) == 0)
            {
                continue;
            }
            
            /*if the adaptation_filed_control is 0x03, there is adaptaion field*/
            /*CNcomment:11后面跟着adaptation域 */
            else if (adaptation_field_control == 0x03)
            {
                /**the length of the adaptation filed*/
                /*CNcomment: adaptation域字节数 */
                adaptation_field_length = buf[4] + 1;
            }

            /*skip the head data*/
            /*CNcomment:跳过头数据(4+调整字段长度)*/
            offset = adaptation_field_length + 4;
            payloadsize = 188-offset;

            /*the length of the tail data*/
            /*CNcomment:尾巴长度*/
            ShortBlockSize = payloadsize % u32PLen;

            /*not encrypt the tail data except PAYLOAD_AES_CBC_IDSA mode*/
            /*CNcomment: PAYLOAD_AES_CBC_IDSA外的其它方式不对尾巴加密 */
            payloadsize -= ShortBlockSize;

            /*set the physical address and length of payload*/
            /*CNcomment:设置payload的物理地址和长度*/
            if( payloadsize > 0 )
            {   
                cipherData[u32DataPkgNum].u32SrcPhyAddr = phyaddr + offset;
                cipherData[u32DataPkgNum].u32DestPhyAddr = phyaddr + offset;
                cipherData[u32DataPkgNum].u32ByteLength = payloadsize;
                u32DataPkgNum++;
            }

            /*need to encrypt the tail data when using PAYLOAD_AES_CBC_IDSA mode*/
            /*CNcomment:PAYLOAD_AES_CBC_IDSA模式需要对尾巴加密 */
            if ((PAYLOAD_AES_CBC_IDSA == u16EMI)&&(ShortBlockSize > 0))
            {

                /*If this is the only short block, using the IV to encrypt*/
                /*CNcomment: 如果是唯一短块，用IV加密 */
                if (0 == payloadsize)
                {
                    memcpy(&stCipherBuf.user_viraddr[16*u32DataPkgNum1], pu8IV, 16);
                }

                /*otherwise using the C(m - 1) to encrypt*/
                /*CNcomment:否则用C(m-1)加密 */
                else
                {
                    /*copy C(m - 1)*/
                    /*CNcomment:把C(m-1)拷进来 */
                    memcpy(&stCipherBuf.user_viraddr[16*u32DataPkgNum1], (buf+offset+payloadsize-16), 16);
                }

                /*set the physical address and length of the tail data*/
                /*CNcomment:设置尾巴加密数据的物理地址和长度*/
                cipherData1[u32DataPkgNum1].u32SrcPhyAddr = stCipherBuf.phyaddr + 16*u32DataPkgNum1;
                cipherData1[u32DataPkgNum1].u32DestPhyAddr = stCipherBuf.phyaddr + 16*u32DataPkgNum1;
                cipherData1[u32DataPkgNum1].u32ByteLength = 16;

                /*set the address and length of the tail data*/
                /*CNcomment:设置尾巴数据的用户态地址和长度*/
                ShortBlockBuf[u32DataPkgNum1].pu8Data = buf + (188-ShortBlockSize);
                ShortBlockBuf[u32DataPkgNum1].u32Size = ShortBlockSize;

                u32DataPkgNum1++;

            }

            /*change the scramble flag to unscramble 00*/
            /*CNcomment:修改加扰标志->未加扰 00 */
            buf[3] &= 0x3f;
        }

        /*decrypt the payload data*/
        /*CNcomment:解密payload数据*/
        if (u32DataPkgNum > 0)
        {
            ret = HI_UNF_CIPHER_DecryptMulti(hCipher, cipherData, u32DataPkgNum);
            if (ret != HI_SUCCESS)
            {
                NAGRA_TEST_PRINT("HI_UNF_CIPHER_DecryptMulti fail: 0x%08x\n", ret);
            }
            u32DataPkgNum = 0;
        }

        /*process the tail data, encrypt C(m - 1) first, then XOR with  the original data*/
        /*CNcomment:处理尾部数据，先加密C(m-1)，结果与原始数据异或*/
        if ((PAYLOAD_AES_CBC_IDSA == u16EMI)&&(u32DataPkgNum1 > 0))
        {
            HI_U32 i,n;
            ret = HI_UNF_CIPHER_EncryptMulti(hCipher, cipherData1, u32DataPkgNum1);
            if (ret != HI_SUCCESS)
            {
                NAGRA_TEST_PRINT("HI_UNF_CIPHER_DecryptMulti fail: 0x%08x\n", ret);
            }

            for(i = 0; i<u32DataPkgNum1; i++)
            {
                /*XOR with the tail data*/
                /*CNcomment:与尾部数据异或 */
                for (n=0; n<ShortBlockBuf[i].u32Size; n++)
                {
                    ShortBlockBuf[i].pu8Data[n] ^= stCipherBuf.user_viraddr[16*i+n];
                }
                
            }
            u32DataPkgNum1 = 0;

        }

        pu8Data += u32SizeThisTime;
        u32PhyAddr += u32SizeThisTime;
        size -= u32SizeThisTime;
    }

    if(PAYLOAD_AES_CBC_IDSA == u16EMI)
    {
        (HI_VOID)HI_MMZ_Free(&stCipherBuf);
    }
    return ret;
}

extern HI_S32 HI_MPI_DMX_GetTSBuffer(HI_HANDLE hTsBuffer, HI_U32 u32ReqLen,
                              HI_UNF_STREAM_BUF_S *pstData, HI_U32 *pu32PhyAddr, HI_U32 u32TimeOutMs);

HI_VOID *NagraTestApp_Thread_TS_Decrypt(HI_VOID *argv)
{
    HI_S32                Ret = HI_SUCCESS;
    HI_UNF_STREAM_BUF_S   StreamBuf;
    HI_U32                u32PhyAddr;
    HI_U32                Readlen;
    HI_U32                u32PLen;
    HI_HANDLE             hCipher = 0;
    TCsdScrKeyPathHandle  stScrKeyPathHandle;
    HI_BOOL bCipheredKey = HI_FALSE;
    TCsd4BytesVector nuid;
    HI_U32 intNuid;
    const TCsdScrCipheredProtectingKeys ProtectingKey = {{0}};
    HI_U32 nuidIndex = 0;

    HI_UNF_CIPHER_ATTS_S  stCipherAttr;
    bCipheredKey = *((HI_BOOL *)argv);

    Ret = csdInitialize(NULL);
    if (CSD_NO_ERROR != Ret)
    {
        NAGRA_TEST_PRINT("call csdInitialize error, Ret=0x%x\n",Ret);
        return NULL;
    }

    if (0 == (g_xEmi & NAGRA_EMI_MASK_RAW))
    {
        Ret = NagraTestApp_SCR_CreateDescrambler(HI_UNF_DMX_ID_0_PLAY, g_hAvplay, &stScrKeyPathHandle, bCipheredKey);
        if (HI_SUCCESS != Ret)
        {
            NAGRA_TEST_PRINT("call NagraTestApp_SCR_CreateDescrambler error, Ret=0x%x\n",Ret);
            goto _CSD_DEINIT;
        }
    }
    else
    {
        Ret = HI_UNF_CIPHER_Init();
        if (HI_SUCCESS != Ret)
        {
            NAGRA_TEST_PRINT("call HI_UNF_CIPHER_Init error, Ret=0x%x\n",Ret);
            goto _CSD_DEINIT;
        }
        memset(&stCipherAttr, 0, sizeof(stCipherAttr));
        stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
        Ret = HI_UNF_CIPHER_CreateHandle(&hCipher, &stCipherAttr);
        if (HI_SUCCESS != Ret)
        {
            NAGRA_TEST_PRINT("call HI_UNF_CIPHER_CreateHandle error, Ret=0x%x\n",Ret);
            goto _CIPHER_DESTROY;
        }
        stScrKeyPathHandle.handle = hCipher;
    }
    
    if (HI_TRUE == bCipheredKey)
    {
        /* Get the NUID in order to retrieve the known ouptut vector computed
        for this specific chipset in the "Chipset_XYZ_Test_Vectors_1_x.h" file*/
        Ret = csdGetNuid(nuid);
        if (CSD_NO_ERROR != Ret)
        {
            NAGRA_TEST_PRINT("CSD Get NUID error, Ret=0x%x\n",Ret);
            goto _CIPHER_DESTROY;
        }
        /* The nuid is a MSBF 4-byte vector therefore it must be converted
        into a integer before it could be used*/
        intNuid = convertToInt(nuid);

        for ( nuidIndex = 0 ; nuidIndex < MAX_NUID_NUMBER ; nuidIndex++ )
        {
            if (intNuid == nagraNUID[nuidIndex])
            {
                break;
            }
        }
        
        if (nuidIndex == MAX_NUID_NUMBER)
        {
            NAGRA_TEST_PRINT("NUID INVALID!\n");
            goto _CIPHER_DESTROY;
        }

        /*lint -save -e605 ignored by m00190812*/
        switch (g_xEmi)
        {
            case PAYLOAD_AES_CBC_IDSA:
            case PAYLOAD_AES_ECB:
            case PAYLOAD_AES_CBC_CI:
                memcpy(ProtectingKey,scrCipheredProtectingKeysTableAesPayload[nuidIndex],16);
                break;
                
            case RAW_AES_CBC:
            case RAW_AES_ECB:
            case RAW_AES_CBC_PIFF:
            case RAW_AES_CBC_APPLE:
            case RAW_AES_CTR:
                memcpy(ProtectingKey,scrCipheredProtectingKeysTableAesRaw[nuidIndex],16);
                break;

            case RAW_TDES_CBC:
            case RAW_TDES_ECB:
                memcpy(ProtectingKey,scrCipheredProtectingKeysTableTdesRaw[nuidIndex],16);
                break;
            default:
                NAGRA_TEST_PRINT("Not support EMI mode 0x%04x\n",g_xEmi);
                goto _CIPHER_DESTROY;
        }
    }

    if (0 != (g_xEmi & NAGRA_EMI_MASK_TDES))
    {
        u32PLen = 8;
    }
    else
    {
        u32PLen = 16;
    }

    if (HI_FALSE == bCipheredKey)
    {
        Ret = csdSetClearTextScrDecryptionKey(g_xEmi, g_pu8HostKey, NAGRA_SCR_KEY_SIZE, g_pu8IV, g_u32IVSize, &stScrKeyPathHandle);
    }
    else
    {
        Ret = csdSetProtectedScrDecryptionKey(g_xEmi, ProtectingKey, g_pu8ContentKey, NAGRA_SCR_KEY_SIZE, g_pu8IV, g_u32IVSize, &stScrKeyPathHandle);
    }
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("Set SCR Decryption key error, Ret=0x%x\n",Ret);
        goto _CIPHER_DESTROY;
    }
    
    while (!g_bStopTsThread)
    {
        pthread_mutex_lock(&g_TsMutex);
        Ret = HI_MPI_DMX_GetTSBuffer(g_TsBuf, NAGRA_TEST_TS_READ_SIZE, &StreamBuf, &u32PhyAddr, 1000);

        if (Ret != HI_SUCCESS )
        {
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), NAGRA_TEST_TS_READ_SIZE, g_pTsFile);
        if (Readlen == 0)
        {
//            HI_DEBUG_NAGRA("read ts file end and rewind!\n");
            if (RAW_AES_CTR == g_xEmi)
            {
                g_pu8IV = (HI_U8 *)scrClearIVAdaptiveStream;
            }

            if (HI_FALSE == bCipheredKey)
            {
                Ret = csdSetClearTextScrDecryptionKey(g_xEmi, g_pu8HostKey, NAGRA_SCR_KEY_SIZE, g_pu8IV, g_u32IVSize, &stScrKeyPathHandle);
            }
            else
            {
                Ret = csdSetProtectedScrDecryptionKey(g_xEmi, ProtectingKey, g_pu8ContentKey, NAGRA_SCR_KEY_SIZE, g_pu8IV, g_u32IVSize, &stScrKeyPathHandle);
            }
            if (HI_SUCCESS != Ret)
            {
                NAGRA_TEST_PRINT("Set SCR Decryption key error, Ret=0x%x\n",Ret);
                goto _CIPHER_DESTROY;
            }
            
            rewind(g_pTsFile);
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }
        
        if (0 != (g_xEmi & NAGRA_EMI_MASK_RAW))
        {
            Ret = HI_UNF_CIPHER_Decrypt(hCipher, u32PhyAddr, u32PhyAddr, (Readlen/u32PLen)*u32PLen);
            if (HI_SUCCESS != Ret)
            {
                NAGRA_TEST_PRINT("Decrypt failure, Ret = 0x%08x\n", Ret); 
            }
        }

        Ret = HI_UNF_DMX_PutTSBuffer(g_TsBuf, Readlen);
        if (Ret != HI_SUCCESS )
        {
            NAGRA_TEST_PRINT("call HI_UNF_DMX_PutTSBuffer failed, Ret = 0x%08x\n", Ret); 
        }
        pthread_mutex_unlock(&g_TsMutex);
    }

    Ret = HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    if (Ret != HI_SUCCESS )
    {
        NAGRA_TEST_PRINT("call HI_UNF_DMX_ResetTSBuffer failed.\n");
    }

_CIPHER_DESTROY:
    if (0 == (g_xEmi & NAGRA_EMI_MASK_RAW))
    {
        (HI_VOID)NagraTestApp_SCR_DestroyDescrambler(&stScrKeyPathHandle);
    }
    else
    {
        if (0 != hCipher)
        {
            (HI_VOID)HI_UNF_CIPHER_DestroyHandle(hCipher);
        }
        (HI_VOID)HI_UNF_CIPHER_DeInit();
    }
    
_CSD_DEINIT:
    (HI_VOID)csdTerminate(NULL);
    return NULL;
}

HI_S32 NagraTestApp_SCR_Encrypt(HI_BOOL bCipheredKey)
{
    HI_S32                Ret = HI_SUCCESS;
    HI_U32                Readlen;
    HI_U32                u32PLen;
    HI_HANDLE             hCipher;
    TCsdScrKeyPathHandle  stScrKeyPathHandle;
    HI_MMZ_BUF_S stTmpBuf;
    TCsd4BytesVector nuid;
    HI_U32 intNuid;
    const TCsdScrCipheredProtectingKeys ProtectingKey = {{0}};
    HI_U32 nuidIndex = 0;
    HI_UNF_CIPHER_ATTS_S  stCipherAttr;

    strncpy(stTmpBuf.bufname, "NagraTsEncrypt", MAX_BUFFER_NAME_SIZE);
    stTmpBuf.bufsize = 0x100000;
    stTmpBuf.overflow_threshold = 100;
    stTmpBuf.underflow_threshold = 0;
    Ret = HI_MMZ_Malloc(&stTmpBuf);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("HI_MMZ_Malloc failed:%x\n",Ret);
        return HI_FAILURE;
    }
    
    Ret = csdInitialize(NULL);
    if (CSD_NO_ERROR != Ret)
    {
        NAGRA_TEST_PRINT("call csdInitialize error, Ret=0x%x\n",Ret);
        goto _FREE_BUFFER;
    }
    
    Ret = HI_UNF_CIPHER_Init();
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_CIPHER_Init error, Ret=0x%x\n", Ret);
        goto _CSD_DEINIT;
    }

	memset(&stCipherAttr, 0, sizeof(stCipherAttr));
	stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&hCipher, &stCipherAttr);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_CIPHER_CreateHandle error, Ret=0x%x\n", Ret);
        goto _CIPHER_CLOSE;
    }
    stScrKeyPathHandle.handle = hCipher;

    if (HI_TRUE == bCipheredKey)
    {
        /* Get the NUID in order to retrieve the known ouptut vector computed
        for this specific chipset in the "Chipset_XYZ_Test_Vectors_1_x.h" file*/
        Ret = csdGetNuid(nuid);
        if(CSD_NO_ERROR != Ret)
        {
            NAGRA_TEST_PRINT("CSD Get NUID error, Ret=0x%x\n", Ret);
            goto _CIPHER_DESTROY;
        }
        /* The nuid is a MSBF 4-byte vector therefore it must be converted
        into a integer before it could be used*/
        intNuid = convertToInt(nuid);

        for ( nuidIndex = 0 ; nuidIndex < MAX_NUID_NUMBER ; nuidIndex++ )
        {
            if (intNuid == nagraNUID[nuidIndex])
            {
                break;
            }
        }
        
        if (nuidIndex == MAX_NUID_NUMBER)
        {
            NAGRA_TEST_PRINT("NUID INVALID!\n");
            Ret = HI_FAILURE;
            goto _CIPHER_DESTROY;
        }

        switch (g_xEmi)
        {
            case PAYLOAD_AES_CBC_IDSA:
            case PAYLOAD_AES_ECB:
            case PAYLOAD_AES_CBC_CI:
                memcpy(ProtectingKey,scrCipheredProtectingKeysTableAesPayload[nuidIndex],16);
                break;
                
            case RAW_AES_CBC:
            case RAW_AES_ECB:
            case RAW_AES_CBC_PIFF:
            case RAW_AES_CBC_APPLE:
            case RAW_AES_CTR:
                memcpy(ProtectingKey,scrCipheredProtectingKeysTableAesRaw[nuidIndex],16);
                break;

            case RAW_TDES_CBC:
            case RAW_TDES_ECB:
                memcpy(ProtectingKey,scrCipheredProtectingKeysTableTdesRaw[nuidIndex],16);
                break;
            default:
                NAGRA_TEST_PRINT("Not support EMI mode 0x%04x\n",g_xEmi);
                goto _CIPHER_DESTROY;
        }
    }

    if (0 != (g_xEmi & NAGRA_EMI_MASK_TDES))
    {
        u32PLen = 8;
    }
    else
    {
        u32PLen = 16;
    }

    if (HI_FALSE == bCipheredKey)
    {
        Ret = csdSetClearTextScrEncryptionKey(g_xEmi, g_pu8HostKey, NAGRA_SCR_KEY_SIZE, g_pu8IV, g_u32IVSize, &stScrKeyPathHandle);
    }
    else
    {
        Ret = csdSetProtectedScrEncryptionKey(g_xEmi, ProtectingKey, g_pu8ContentKey, NAGRA_SCR_KEY_SIZE, g_pu8IV, g_u32IVSize, &stScrKeyPathHandle);
    }
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("Set SCR Encrypt key error, Ret=0x%x\n",Ret);
        goto _CIPHER_DESTROY;
    }

    /*lint -save -e716 ignored by m00190812*/
    while (1)
    {
        Readlen = fread(stTmpBuf.user_viraddr, sizeof(HI_S8), NAGRA_TEST_TS_READ_SIZE, g_pTsFile);
        if (Readlen == 0)
        {
            NAGRA_TEST_PRINT("read ts file end!\n");
            break;
        }

        if (0 != (g_xEmi & NAGRA_EMI_MASK_RAW))
        {
            Ret = HI_UNF_CIPHER_Encrypt(hCipher, stTmpBuf.phyaddr, stTmpBuf.phyaddr, (Readlen/u32PLen)*u32PLen);
        }
        else
        {
            //do not support playload encrypt
        }
            
        if (HI_SUCCESS != Ret)
        {
            NAGRA_TEST_PRINT("Encrypt failure, Ret = 0x%08x\n", Ret); 
            break;
        }
        
        fwrite(stTmpBuf.user_viraddr, sizeof(HI_S8), Readlen, g_pRecFile);
    }

_CIPHER_DESTROY:
    if (0 != hCipher)
    {
        (HI_VOID)HI_UNF_CIPHER_DestroyHandle(hCipher);
    }
    
_CIPHER_CLOSE:    
    (HI_VOID)HI_UNF_CIPHER_DeInit();
    
_CSD_DEINIT:
    (HI_VOID)csdTerminate(NULL);

_FREE_BUFFER:
    (HI_VOID)HI_MMZ_Free(&stTmpBuf);
    
    return Ret;
}

HI_S32 NagraTestApp_StopScrService(HI_HANDLE   hSCRAvplay)
{
    HI_S32                  Ret;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;

    NAGRA_TEST_CHECK_HANDLE(hSCRAvplay);
    
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    Ret = HI_UNF_AVPLAY_Stop(hSCRAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &Stop);
    Ret |= HI_UNF_AVPLAY_Stop(hSCRAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_AVPLAY_Stop failed.\n");
        return Ret;
    }
    return HI_SUCCESS;
}

HI_S32 NagraTestApp_PlayScrService(HI_HANDLE   hSCRAvplay)
{
    HI_S32                  Ret;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_U32                  VidPid;
    HI_U32                  AudPid;
    HI_U32                  PcrPid;
    HI_UNF_VCODEC_TYPE_E    enVidType;
    HI_U32                  u32AudType;

    NAGRA_TEST_CHECK_HANDLE(hSCRAvplay);

    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    Ret = HI_UNF_AVPLAY_Stop(hSCRAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &Stop);
    Ret |= HI_UNF_AVPLAY_Stop(hSCRAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_AVPLAY_Stop failed.\n");
        return Ret;
    }

    /*lint -save -e648 ignored by m00190812*/
    /*lint -save -e778 ignored by m00190812*/
    /*lint -save -e834 ignored by m00190812*/
    VidPid = scrServiceVideoPid;
    enVidType = HI_UNF_VCODEC_TYPE_MPEG2;
    AudPid = scrServiceAudioPid;
    u32AudType = HA_AUDIO_ID_AC3PASSTHROUGH;
    PcrPid = scrServicePCRPid;
    

    Ret = HI_UNF_AVPLAY_SetAttr(hSCRAvplay, HI_UNF_AVPLAY_ATTR_ID_PCR_PID, &PcrPid);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("call HI_UNF_AVPLAY_SetAttr failed.\n");
        return Ret;
    }

    Ret = HIADP_AVPlay_SetVdecAttr(hSCRAvplay,enVidType,HI_UNF_VCODEC_MODE_NORMAL);
    Ret |= HI_UNF_AVPLAY_SetAttr(hSCRAvplay, HI_UNF_AVPLAY_ATTR_ID_VID_PID,&VidPid);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HIADP_AVPlay_SetVdecAttr failed.\n");
        return Ret;
    }

    Ret = HI_UNF_AVPLAY_Start(hSCRAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HI_UNF_AVPLAY_Start failed.\n");
        return Ret;
    }

    Ret  = HIADP_AVPlay_SetAdecAttr(hSCRAvplay, u32AudType, HD_DEC_MODE_RAWPCM, 1);
	
    Ret |= HI_UNF_AVPLAY_SetAttr(hSCRAvplay, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &AudPid);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("HIADP_AVPlay_SetAdecAttr failed:%#x\n",Ret);
        return Ret;
    }

    Ret = HI_UNF_AVPLAY_Start(hSCRAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HI_UNF_AVPLAY_Start failed.\n");
    }

    return HI_SUCCESS;
}

HI_S32 NagraTestApp_TS_Play(HI_BOOL bCipheredKey)
{
    HI_S32                  Ret = HI_SUCCESS;
    static HI_HANDLE               hWin = 0;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    static pthread_t   g_TsThd;
    HI_CHAR InputCmd[32];

    HI_HANDLE hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;

    if (0 != g_hAvplay)
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

    Ret = HI_UNF_DMX_CreateTSBuffer(/*HI_UNF_DMX_PORT_3_RAM*/HI_UNF_DMX_PORT_RAM_0, 0x200000, &g_TsBuf);
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
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    Ret |= HI_UNF_AVPLAY_SetAttr(g_hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    (HI_VOID)pthread_mutex_init(&g_TsMutex,NULL);
    g_bStopTsThread = HI_FALSE;
    (HI_VOID)pthread_create(&g_TsThd, HI_NULL, NagraTestApp_Thread_TS_Decrypt, &bCipheredKey);

    Ret = NagraTestApp_PlayScrService(g_hAvplay);
    if (Ret != HI_SUCCESS)
    {
        NAGRA_TEST_PRINT("call NagraTestApp_PlayScrService failed.\n");
        goto AVPLAY_STOP;
    }

    while (1)
    {
        HI_TRACE_LOG("\nplease input \"q\" to quit!\n");
        memset(InputCmd, 0, sizeof(InputCmd));
        (HI_VOID)fgets(InputCmd, sizeof(InputCmd)-1, stdin);
        if ('q' == InputCmd[0])
        {
            HI_TRACE_LOG("\nprepare to quit!\n");
            break;
        }
    }

AVPLAY_STOP:
    if (g_hAvplay != 0)
    {
        (HI_VOID)NagraTestApp_StopScrService(g_hAvplay);
    }

    g_bStopTsThread = HI_TRUE;
    (HI_VOID)pthread_join(g_TsThd, HI_NULL);
    (HI_VOID)pthread_mutex_destroy(&g_TsMutex);
    
SND_DETACH:
    if (g_hAvplay != 0)
    {
        (HI_VOID)HI_UNF_SND_Detach(HI_UNF_SND_0, g_hAvplay);
    }

WIN_DETACH:
    if ((g_hAvplay != 0) && (hWin != 0))
    {
        (HI_VOID)HI_UNF_VO_SetWindowEnable(hWin,HI_FALSE);
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
    (HI_VOID)HI_UNF_DMX_DetachTSPort(/*HI_UNF_DMX_PORT_3_RAM*/HI_UNF_DMX_PORT_RAM_0);
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

TCsdStatus scr_1_Decrypt_HostKey(TCsdUnsignedInt16 pEMINum)
{
    HI_U32 sel;
    HI_CHAR input[32];
    HI_CHAR *szFileName = HI_NULL;
    HI_CHAR streamFileName[64] = {0};
    HI_CHAR szKey[64];

    memset(szKey, 0, sizeof(szKey));
    (HI_VOID)snprintf(szKey, sizeof(szKey), "scrClearTextHostKey%s%s",
        (g_xEmi & NAGRA_EMI_MASK_TDES) ? "Tdes" : "Aes",
        (g_xEmi & NAGRA_EMI_MASK_RAW) ? "Raw" : "Payload");

    HI_TRACE_LOG("\n\nPlease select the host key:\n");
    HI_TRACE_LOG("[SCR_%d_1][1]: %s1\n", pEMINum, szKey);
    HI_TRACE_LOG("[SCR_%d_1][2]: %s2\n\n", pEMINum, szKey);

    while (1)
    {
        memset(input, 0, sizeof(input));
        (HI_VOID)fgets(input, 30, stdin);
        if (('1' == input[0]) || ('2' == input[0]))
        {
            /*lint -save -e732 ignored by m00190812*/
            sel = input[0] - '0';
            break;
        }
        else
        {
            HI_TRACE_LOG("Invalid choice. Shall be only 1 or 2.\n");
        }
    }
    g_pu8HostKey = (HI_U8 *)HostKeyTable[pEMINum-1][sel-1];
    g_pu8IV = (HI_U8 *)IVTable[pEMINum-1];
    g_u32IVSize = IVSizeTable[pEMINum-1];
    

    if ((PAYLOAD_AES_CBC_IDSA != g_xEmi) && (PAYLOAD_AES_ECB != g_xEmi) && (PAYLOAD_AES_CBC_CI != g_xEmi))
    {
        HI_TRACE_LOG("\n\nPlease select the MPEG Transport Stream:\n");
        HI_TRACE_LOG("[SCR_%d_1][1]: scrEmi0x%04x.ts\n", pEMINum, g_xEmi);
        HI_TRACE_LOG("[SCR_%d_1][2]: scrEmi0x%04xRecorded.ts\n", pEMINum, g_xEmi);
    
        while(1)
        {
            memset(input,0,sizeof(input));
            (HI_VOID)fgets(input, 30, stdin);
            if(('1' == input[0])||('2' == input[0]))
            {
                sel = input[0] - '0';
                break;
            }
            else
            {
                HI_TRACE_LOG("Invalid choice. Shall be only 1 or 2.\n");
            }
        }
        
        if(1 == sel)
        {
            NOCS_STREAM_NAME_PARSER("SCR", "None", g_xEmi, szFileName, 64);
            (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/%s", SCR_STREAM_PATH, szFileName);
        }
        else if(2 == sel)
        {
            (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/scrEmi0x%04xRecorded.ts", SCR_STREAM_PATH, g_xEmi);
        }
    }
    else
    {
        NOCS_STREAM_NAME_PARSER("SCR", "None", g_xEmi, szFileName, 64);
        (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/%s", SCR_STREAM_PATH, szFileName);
    }
    
    g_pTsFile = fopen(streamFileName, "rb");
    if (!g_pTsFile)
	{
        NAGRA_TEST_PRINT("open file %s error!\n", streamFileName);
		return CSD_ERROR;
	}

    (HI_VOID)NagraTestApp_TS_Play(HI_FALSE);
    
    if (NULL != g_pTsFile)
    {
        fclose(g_pTsFile);
        g_pTsFile = NULL;
    }

    return CSD_NO_ERROR;
}

TCsdStatus scr_2_Encrypt_HostKey(TCsdUnsignedInt16 pEMINum)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 sel;
    HI_CHAR input[32];
    HI_CHAR *szFileName = HI_NULL;
    HI_CHAR streamFileName[64] = {0};
    HI_CHAR szKey[64];
    TCsdUnsignedInt16 clearEmi = 0x0;

    memset(szKey, 0, sizeof(szKey));
    (HI_VOID)snprintf(szKey, sizeof(szKey), "scrClearTextHostKey%s%s",
        (g_xEmi & NAGRA_EMI_MASK_TDES) ? "Tdes" : "Aes",
        (g_xEmi & NAGRA_EMI_MASK_RAW) ? "Raw" : "Payload");
    
    HI_TRACE_LOG("\n\nPlease select the host key:\n");
    HI_TRACE_LOG("[SCR_%d_2][1]: %s1\n", pEMINum, szKey);
    HI_TRACE_LOG("[SCR_%d_2][2]: %s2\n\n", pEMINum, szKey);

    while (1)
    {
        memset(input, 0, sizeof(input));
        (HI_VOID)fgets(input, 30, stdin);
        if (('1' == input[0]) || ('2' == input[0]))
        {
            sel = input[0] - '0';
            break;
        }
        else
        {
            HI_TRACE_LOG("Invalid choice. Shall be only 1 or 2.\n");
        }
    }
    g_pu8HostKey = (HI_U8 *)HostKeyTable[pEMINum-1][sel-1];
    g_pu8IV = (HI_U8 *)IVTable[pEMINum-1];
    g_u32IVSize = IVSizeTable[pEMINum-1];

    
    HI_TRACE_LOG("[SCR_%d_2]: Open the stream file scrClear.ts to encrypt\n", pEMINum);

    /*lint -save -e774 ignored by m00190812*/
    NOCS_STREAM_NAME_PARSER("SCR", "None", clearEmi, szFileName, 64);
    (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/%s", SCR_STREAM_PATH, szFileName);

    g_pTsFile = fopen(streamFileName, "rb");
    if (!g_pTsFile)
	{
        NAGRA_TEST_PRINT("open file %s error!\n", streamFileName);
		return CSD_ERROR;
	}

    memset(streamFileName, 0, sizeof(streamFileName));
    (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/scrEmi0x%04xRecorded.ts", SCR_STREAM_PATH, g_xEmi);

    g_pRecFile = fopen(streamFileName, "wb");
    if (!g_pRecFile)
	{
        NAGRA_TEST_PRINT("open file %s error!\n", streamFileName);
		goto _CLOSE_SRC_FILE;
	}

    HI_TRACE_LOG("\n[SCR_%d_2]: Please wait, Encrypting......\n\n", pEMINum);

    Ret = NagraTestApp_SCR_Encrypt(HI_FALSE);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("Encrypt ts error!\n");
    }

_CLOSE_SRC_FILE:
    if (NULL != g_pTsFile)
    {
        fclose(g_pTsFile);
        g_pTsFile = NULL;
    }
    return CSD_NO_ERROR;
}

TCsdStatus scr_3_Decrypt_ContentKey(TCsdUnsignedInt16 pEMINum)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 sel;
    HI_CHAR input[32];
    HI_CHAR *szFileName = HI_NULL;
    HI_CHAR streamFileName[64] = {0};
    HI_CHAR szKey[64];

    memset(szKey, 0, sizeof(szKey));
    (HI_VOID)snprintf(szKey, sizeof(szKey), "scrCipheredContentKey%s%s",
        (g_xEmi & NAGRA_EMI_MASK_TDES) ? "Tdes" : "Aes",
        (g_xEmi & NAGRA_EMI_MASK_RAW) ? "Raw" : "Payload");

    HI_TRACE_LOG("\n\nPlease select the content key:\n");
    HI_TRACE_LOG("[SCR_%d_3][1]: %s1\n", pEMINum, szKey);
    HI_TRACE_LOG("[SCR_%d_3][2]: %s2\n\n", pEMINum, szKey);

    while (1)
    {
        memset(input,0,sizeof(input));
        (HI_VOID)fgets(input, 30, stdin);
        if (('1' == input[0]) || ('2' == input[0]))
        {
            sel = input[0] - '0';
            break;
        }
        else
        {
            HI_TRACE_LOG("Invalid choice. Shall be only 1 or 2.\n");
        }
    }

    g_pu8ContentKey = (HI_U8 *)ContentKeyTable[pEMINum-1][sel-1];
    g_pu8IV = (HI_U8 *)IVTable[pEMINum-1];
    g_u32IVSize = IVSizeTable[pEMINum-1];
    
    if ((PAYLOAD_AES_CBC_IDSA != g_xEmi) && (PAYLOAD_AES_ECB != g_xEmi) && (PAYLOAD_AES_CBC_CI != g_xEmi))
    {
        HI_TRACE_LOG("\n\nPlease select the MPEG Transport Stream:\n");
        HI_TRACE_LOG("[SCR_%d_3][1]: scrEmi0x%04x.ts\n",pEMINum,g_xEmi);
        HI_TRACE_LOG("[SCR_%d_3][2]: scrEmi0x%04xRecorded.ts\n",pEMINum,g_xEmi);

        while(1)
        {
            memset(input,0,sizeof(input));
            (HI_VOID)fgets(input, 30, stdin);
            if(('1' == input[0])||('2' == input[0]))
            {
                sel = input[0]-'0';
                break;
            }
            else
            {
                HI_TRACE_LOG("Invalid choice. Shall be only 1 or 2.\n");
            }
        }
        
        if(1 == sel)
        {
            NOCS_STREAM_NAME_PARSER("SCR", "None", g_xEmi, szFileName, 64);
            (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/%s", SCR_STREAM_PATH, szFileName);
        }
        else if(2 == sel)
        {
            (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/scrEmi0x%04xRecorded.ts", SCR_STREAM_PATH, g_xEmi);
        }
    }
    else
    {
        NOCS_STREAM_NAME_PARSER("SCR", "None", g_xEmi, szFileName, 64);
        (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/%s", SCR_STREAM_PATH, szFileName);
    }
    
    g_pTsFile = fopen(streamFileName, "rb");
    if (!g_pTsFile)
	{
        NAGRA_TEST_PRINT("open file %s error!\n", streamFileName);
		return CSD_ERROR;
	}

    Ret = NagraTestApp_TS_Play(HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("Play ts error!\n");
    }

    if(NULL != g_pTsFile)
    {
        fclose(g_pTsFile);
        g_pTsFile = NULL;
    }
    return CSD_NO_ERROR;
}

TCsdStatus scr_4_Encrypt_ContentKey(TCsdUnsignedInt16 pEMINum)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 sel;
    HI_CHAR input[32];
    HI_CHAR *szFileName = HI_NULL;
    HI_CHAR streamFileName[64] = {0};
    HI_CHAR szKey[64];
    TCsdUnsignedInt16 clearEmi = 0x0;

    memset(szKey, 0, sizeof(szKey));
    (HI_VOID)snprintf(szKey, sizeof(szKey), "scrCipheredContentKey%s%s",
        (g_xEmi & NAGRA_EMI_MASK_TDES) ? "Tdes" : "Aes",
        (g_xEmi & NAGRA_EMI_MASK_RAW) ? "Raw" : "Payload");

    HI_TRACE_LOG("\n\nPlease select the content key:\n");
    HI_TRACE_LOG("[SCR_%d_4][1]: %s1\n", pEMINum, szKey);
    HI_TRACE_LOG("[SCR_%d_4][2]: %s2\n\n", pEMINum, szKey);

    while (1)
    {
        memset(input, 0, sizeof(input));
        (HI_VOID)fgets(input, 30, stdin);
        if (('1' == input[0]) || ('2' == input[0]))
        {
            sel = input[0] - '0';
            break;
        }
        else
        {
            HI_TRACE_LOG("Invalid choice. Shall be only 1 or 2.\n");
        }
    }

    g_pu8ContentKey = (HI_U8 *)ContentKeyTable[pEMINum-1][sel-1];
    g_pu8IV = (HI_U8 *)IVTable[pEMINum-1];
    g_u32IVSize = IVSizeTable[pEMINum-1];
    
    HI_TRACE_LOG("[SCR_%d_4]: Open the stream file scrClear.ts to encrypt\n", pEMINum);

    NOCS_STREAM_NAME_PARSER("SCR", "None", clearEmi, szFileName, 64);
    (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/%s", SCR_STREAM_PATH, szFileName);

    g_pTsFile = fopen(streamFileName, "rb");
    if (!g_pTsFile)
	{
        NAGRA_TEST_PRINT("open file %s error!\n", streamFileName);
		return CSD_ERROR;
	}

    memset(streamFileName, 0, sizeof(streamFileName));
    (HI_VOID)snprintf(streamFileName, sizeof(streamFileName), "%s/scrEmi0x%04xRecorded.ts", SCR_STREAM_PATH, g_xEmi);

    g_pRecFile = fopen(streamFileName, "wb");
    if (!g_pRecFile)
	{
        NAGRA_TEST_PRINT("open file %s error!\n", streamFileName);
		goto _CLOSE_SRC_FILE;
	}

    HI_TRACE_LOG("\n[SCR_%d_4]: Please wait, Encrypting......\n\n", pEMINum);

    Ret = NagraTestApp_SCR_Encrypt(HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        NAGRA_TEST_PRINT("Encrypt ts error!\n");
    }

    if (NULL != g_pRecFile)
    {
        fclose(g_pRecFile);
        g_pRecFile = NULL;
    }

_CLOSE_SRC_FILE:
    if (NULL != g_pTsFile)
    {
        fclose(g_pTsFile);
        g_pTsFile = NULL;
    }
    return CSD_NO_ERROR;
}

HI_S32 main()
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdRet = CSD_NO_ERROR;
    TCsdUnsignedInt16 number  = 1;
    g_xEmi = 0x0020;
    
    (HI_VOID)HI_SYS_Init();
	//(HI_VOID)HI_SYS_PreAV(NULL);

    HI_TRACE_LOG("\033[0;32m""Testing the decrypt by hostkey of stream: %04x\n""\033[0m", g_xEmi);
    csdRet = scr_1_Decrypt_HostKey(number);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("play host key scramblered stream %04x ERROR!\n", g_xEmi);
        return HI_FAILURE;
    }

    HI_TRACE_LOG("\033[0;32m""Testing the decrypt by contentkey of stream: %04x\n""\033[0m", g_xEmi);
    csdRet = scr_3_Decrypt_ContentKey(number);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("play content key scramblered stream %04x ERROR!\n", g_xEmi);
        return HI_FAILURE;
    }

    g_xEmi = 0x4020;
    number = 6;
    HI_TRACE_LOG("\033[0;32m""Testing the encrypt by hostkey of stream: %04x\n""\033[0m", g_xEmi);
    csdRet = scr_2_Encrypt_HostKey(number);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("encrypt host key scramblered stream %04x ERROR!\n", g_xEmi);
        return HI_FAILURE;
    }

    HI_TRACE_LOG("\033[0;32m""Testing the decrypt by hostkey of stream: %04x\n""\033[0m", g_xEmi);
    csdRet = scr_1_Decrypt_HostKey(number);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("play host key scramblered stream %04x ERROR!\n", g_xEmi);
        return HI_FAILURE;
    }

    HI_TRACE_LOG("\033[0;32m""Testing the encrypt by contentkey of stream: %04x\n""\033[0m", g_xEmi);
    csdRet = scr_4_Encrypt_ContentKey(number);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("encrypt content key scramblered stream %04x ERROR!\n", g_xEmi);
        return HI_FAILURE;
    }

    HI_TRACE_LOG("\033[0;32m""Testing the decrypt by contentkey of stream: %04x\n""\033[0m", g_xEmi);
    csdRet = scr_3_Decrypt_ContentKey(number);
    if (CSD_NO_ERROR != csdRet)
    {
        HI_DEBUG_NAGRA("play content key scramblered stream %04x ERROR!\n", g_xEmi);
        return HI_FAILURE;
    }
    
    (HI_VOID)HI_SYS_DeInit();

    return Ret;
}

