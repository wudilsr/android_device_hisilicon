#include "tee_common.h"
#include "tee_internal_api.h"
#include "tee_mem_mgmt_api.h"
#define TA_DEBUG
#include "tee_log.h"
#include "tee_fs.h"
#include "tee_trusted_storage_api.h"
#include "tee_time_api.h"
#include "hi_tee_mem.h"
#include "sre_syscalls_ext.h"
#include "tee_pvr.h"

HI_S32 TEE_PVR_DeInit(HI_VOID)
{
    return __TEE_PVR_DeInit();
}
HI_S32 TEE_PVR_RecOpenChannel(TEE_Param stParams[4])
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RecChnId = -1;
    HI_S32 s32BufferLen = 0;

    s32BufferLen = stParams[0].value.b;
    
    s32BufferLen = s32BufferLen/TEE_PVR_DATA_ALIGN * TEE_PVR_DATA_ALIGN + TEE_PVR_DATA_ALIGN;
    TEE_DEBUG_PVR("(stParams[0].value.b, s32BufferLen) = (%d, %d)\n", stParams[0].value.b, s32BufferLen);
    s32Ret = __TEE_PVR_OpenChannel(&u32RecChnId,s32BufferLen,TEE_PVR_RECORD);
    if (HI_SUCCESS != s32Ret)
    {
        TEE_ERR_PVR("open tee record channel failed, ret = 0x%x\n", s32Ret);
    }
    stParams[0].value.a = u32RecChnId;
    return s32Ret;
}
HI_S32 TEE_PVR_RecCloseChannel(TEE_Param stParams[4])
{
    HI_S32 s32Ret = HI_SUCCESS;
    s32Ret = __TEE_PVR_CloseChannel(stParams[0].value.a);
    if (HI_SUCCESS != s32Ret)
    {
        TEE_ERR_PVR("close tee record channel(%d) failed, ret = 0x%x\n", stParams[0].value.a, s32Ret);
    }
    return s32Ret;
}
HI_S32 TEE_PVR_RecProcTsData(TEE_Param stParams[4])
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RecChnId = stParams[1].value.a;
    HI_U32 u32NSSmmuAddr = stParams[0].value.a;
    
    s32Ret = __TEE_PVR_RecProcTsData(u32RecChnId, u32NSSmmuAddr);
    if (HI_SUCCESS != s32Ret)
    {
        TEE_ERR_PVR("process ts data failed, ret = 0x%x\n", s32Ret);
    }
    return s32Ret;
}
HI_S32 TEE_PVR_RecCopyToRee(TEE_Param stParams[4])
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RecChnId = stParams[0].value.a;
    HI_U32 u32NSSmmuAddr = stParams[1].value.a;
    HI_U32 u32BufLen = stParams[1].value.b;
    
    s32Ret = __TEE_PVR_RecCopyToRee(u32RecChnId, u32NSSmmuAddr,&u32BufLen);
    if (HI_SUCCESS != s32Ret)
    {
        TEE_ERR_PVR("channel(%d) copy ts data to ree failed, ret = 0x%x\n", u32RecChnId, s32Ret);
    }
    return s32Ret;
}
HI_S32 TEE_PVR_PlayCopyFromRee(TEE_Param stParams[4])
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ReeAddr = stParams[0].value.a;
    HI_U32 u32TeeAddr = stParams[0].value.b;
    HI_U32 u32DataLen = stParams[1].value.a;
    
    s32Ret = __TEE_PVR_PlayCopyFromRee(u32ReeAddr, u32TeeAddr, u32DataLen);
    if (HI_SUCCESS != s32Ret)
    {
        TEE_ERR_PVR("copy ts data from ree failed, ret = 0x%x\n", s32Ret);
    }
    return s32Ret;
}

HI_S32 TEE_PVR_RecGetOutputBufInfo(TEE_Param stParams[4])
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RecChnId = stParams[0].value.a;
    HI_U32 u32SmmuAddr = 0;
    HI_U32 u32ValidLen = stParams[0].value.b;
    
    s32Ret = __TEE_PVR_RecGetOutputBufInfo(u32RecChnId, &u32SmmuAddr, &u32ValidLen);
    if (HI_SUCCESS != s32Ret)
    {
        TEE_ERR_PVR("channel(%d) get tee output buffer info failed, ret = 0x%x\n", u32RecChnId, s32Ret);
    }
    stParams[1].value.a = u32SmmuAddr;
    stParams[1].value.b = u32ValidLen;
    return s32Ret;
}

HI_S32 TEE_PVR_RecGetStatus(TEE_Param stParams[4])
{
    return __TEE_PVR_RecGetStatus(stParams[0].value.a, stParams[1].value.a);
}


