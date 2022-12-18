#include "hi_type.h"
#include "tee_pvr.h"

#ifndef __TEE_DRV_PVR_H__
#define __TEE_DRV_PVR_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define TEE_PVR_TS_PACKET_LEN        (188)
#define TEE_PVR_TS_PD_SIZE_POS       4         
#define TEE_PVR_TS_PD_FLAG_POS       5         
#define TEE_PVR_TS_MIN_PD_SIZE       2
#define TEE_PVR_TS_HEAD_LEN          (4)    
#define PVR_TEE_TS_ADAPT_RESERVED    0x0
#define PVR_TEE_TS_ADAPT_PLD_ONLY    0x1
#define PVR_TEE_TS_ADAPT_ADAPT_ONLY  0x2
#define PVR_TEE_TS_ADAPT_BOTH        0x3
#define REE_PVR_MAX_INDEX_NUM       (256)

#define PVR_TEE_TS_ADAPT_HAVE_ADAPT(flag) (flag & PVR_TEE_TS_ADAPT_ADAPT_ONLY)
#define PVR_TEE_GET_TS_HEAD_ADAPTION(pTsHead)           ((((pTsHead)[3]) >> 4) & 0x3)
#define PVR_TEE_SET_TS_HEAD_ADAPTION(pTsHead, flag)     ((((pTsHead)[3])&0xCF)|(((flag)&0x3)<<4))  
#define PVR_TEE_DISORDER_CNT_NUM(pTsHead, u8RandNum)    (((((pTsHead)[3] & 0xF) + (u8RandNum)) &0xF) | ((pTsHead)[3] & 0xF0))

typedef struct tagTEE_DRV_PVR_TS_ADJUST_INFO_S
{
    HI_U64  u64DataGlobalOffset;/*TEE收到的总数据，每次处理完刷新*/
    HI_U64  u64BaseGlobalOffset;/*考虑demux缓存溢出*/
    HI_U64  u64NextOldOffset;/*下一帧的原始偏移计算值, 基于demux上报的数据*/
    HI_U64  u64NextAdjustOffset;/*下一帧调整后的偏移*/
    HI_S32  s32InsertTsPacketNum;/*累计插入的ts包个数*/
    HI_BOOL bUsedNext;/*u64LastAdjustOffset u64LastOldOffset是否已经使用*/
    HI_CHAR chTsPacket[TEE_PVR_TS_PACKET_LEN];
}TEE_DRV_PVR_TS_ADJUST_INFO_S;

typedef struct tagTEE_DRV_PVR_REC_STATUS_S
{
    HI_U32 u32TeeBufAddr;
    HI_U32 u32TeeBufLen;
    HI_U32 u32ReeBufAddr;
    HI_U32 u32ReeBufLen;
    HI_U32 u32TeeReadPos;
    HI_U32 u32TeeWritePos;
    HI_U64 u64DataGlobalOffset;
    HI_U64 u64BaseGlobalOffset;
    HI_U64 u64NextOldOffset;
    HI_U64 u64NextAdjustOffset;
    HI_S32 s32InsertTsPacketNum;
    HI_BOOL bUsedNext;
}TEE_DRV_PVR_REC_STATUS_S;

typedef struct tagTEE_DRV_PVR_SMMU_BUF_S
{
    HI_ULONG  phyaddr;                /**<Physical address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer物理地址 */
    HI_U8  *user_viraddr;           /**<User-state virtual address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer用户态虚拟地址 */
    HI_U32  bufsize;                /**<Size of an MMZ buffer*/ /**<CNcomment:  MMZ buffer大小 */
}TEE_DRV_PVR_SMMU_BUF_S;
typedef struct tagTEE_DRV_PVR_BUFFER_INFO_S
{
    TEE_DRV_PVR_SMMU_BUF_S stSmmucBuf;
    HI_S32 s32Length;
    HI_S32 s32Read;
    HI_S32 s32Write;
}TEE_DRV_PVR_BUFFER_INFO_S;    

typedef struct tagTEE_DRV_PVR_REC_DATA_S
{
    HI_U8  *pDataAddr;      
    HI_U32  u32Reserved;
    HI_U32  u32Len;         
}TEE_DRV_PVR_REC_DATA_S;  

typedef struct tagTEE_DRV_PVR_INDEX_INFO_S
{
    HI_S32 s32IndexNum;
    HI_S32 s32TsDataNum;
    HI_U64 u64DropLength;
    HI_U64 u64GlobalOffset[REE_PVR_MAX_INDEX_NUM];
    HI_U32 u32FrameSize[REE_PVR_MAX_INDEX_NUM];
    TEE_DRV_PVR_REC_DATA_S stRecData[2]; 
}TEE_DRV_PVR_INDEX_INFO_S;

HI_S32 TEE_DRV_PVR_DeInit();

HI_S32 TEE_DRV_PVR_OpenChannel(HI_U32 *pu32ChnId, HI_S32 s32BufLen, TEE_PVR_TYPE_E enType);
HI_S32 TEE_DRV_PVR_CloseChannel(HI_U32 u32ChnId);
HI_S32 TEE_DRV_PVR_RecProcTsData(HI_U32 u32ChnId, HI_U32 u32NoSecureSmmuAddr);
HI_S32 TEE_DRV_PVR_RecCopyToRee(HI_U32 u32ChnId, HI_U32 u32NoSecureSmmuAddr, HI_U32 *pu32DataLen);
HI_S32 TEE_DRV_PVR_RecGetOutputBufInfo(HI_U32 u32ChnId, HI_U32 *pu32SecureSmmuAddr, HI_U32 *pu32DataLen);
HI_S32 TEE_DRV_PVR_RecGetStatus(HI_U32 u32ChnId, HI_U32 u32SecureSmmuAddr);
HI_S32 TEE_DRV_PVR_PlayCopyToTee(HI_U32 u32ReeAddr, HI_U32 u32TeeAddr, HI_U32 u32DataLen);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
