#include "hi_type.h"
#include "tee_drv_pvr.h"

#ifndef __TE_DRV_PVR_PRIV_H__
#define __TE_DRV_PVR_PRIV_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

struct mutex {
    HI_VOID *rlock;
};

typedef struct tagTEE_DRV_PVR_REC_CHAN_S
{
    TEE_DRV_PVR_BUFFER_INFO_S stCbBuf;
    TEE_DRV_PVR_BUFFER_INFO_S stTsBuf;
    TEE_DRV_PVR_TS_ADJUST_INFO_S stTsAdjustInfo;
}TEE_DRV_PVR_REC_CHAN_S;
typedef struct tagTEE_DRV_PVR_PLAY_CHAN_S
{
    HI_U32 u32Dummy;
}TEE_DRV_PVR_PLAY_CHAN_S;
typedef union
{
    TEE_DRV_PVR_REC_CHAN_S stRecInfo;
    TEE_DRV_PVR_PLAY_CHAN_S stPlayInfo;
}TEE_DRV_PVR_CHAN_INFO_S;

typedef struct tagTEE_DRV_PVR_INST_S
{
    TEE_PVR_TYPE_E enType;
    TEE_DRV_PVR_CHAN_INFO_S stChnInfo;
}TEE_DRV_PVR_INST_S;
typedef struct tagTEE_DRV_PVR_INST_CTRL_S
{
    struct mutex PvrMutex;
    HI_BOOL bUsed[TEE_PVR_MAX_INSTANCE];
    TEE_DRV_PVR_INST_S stInstInfo[TEE_PVR_MAX_INSTANCE];
}TEE_DRV_PVR_INST_CTRL_S;



/**********************************************************************************/
HI_S32 DRV_PVR_REC_TS_DATA_AdjustTsDataMore(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo,
                                                            TEE_DRV_PVR_INDEX_INFO_S *pstIndexInfo);

HI_S32 DRV_PVR_REC_TS_DATA_AdjustNoIndex(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo, TEE_DRV_PVR_INDEX_INFO_S *pstIndexInfo);
/**********************************************************************************/
HI_S32 DRV_PVR_RecOpenChannel(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo, HI_S32 s32BufLen);
HI_S32 DRV_PVR_RecCloseChannel(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo);
HI_S32 DRV_PVR_RecProcTsData(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo, TEE_DRV_PVR_INDEX_INFO_S *pstRecIdxBuf);
HI_S32 DRV_PVR_RecCopyToRee(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo, HI_VOID *pDstBuf, HI_U32 *pu32BufLen);
HI_S32 DRV_PVR_RecGetBufInfo(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo, HI_U32 *pu32Addr, HI_U32 *pu32BufLen);
HI_S32 DRV_PVR_RecGetStatus(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo, TEE_DRV_PVR_REC_STATUS_S *pstTeeState);
/**********************************************************************************/
HI_S32 DRV_PVR_PlayCopyReeDataToTee(HI_VOID *pDst, HI_VOID *pSrc, HI_U32 u32DataLen);
/**********************************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
