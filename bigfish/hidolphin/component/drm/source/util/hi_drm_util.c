#include <cutils/log.h>
#include "hi_type.h"
#include "hi_common.h"
#include "tee_client_api.h"

#define WV_MMZ_SIZE (0x200000)

typedef enum
{
    CMD_TZ_OEMCrypto_Initialize = 20,
    CMD_TZ_OEMCrypto_Terminate,
    CMD_TZ_OEMCrypto_OpenSession,
    CMD_TZ_OEMCrypto_CloseSession,
    CMD_TZ_OEMCrypto_GenerateDerivedKeys,
    CMD_TZ_OEMCrypto_GenerateNonce,
    CMD_TZ_OEMCrypto_GenerateSignature,
    CMD_TZ_OEMCrypto_LoadKeys,
    CMD_TZ_OEMCrypto_RefreshKeys,
    CMD_TZ_OEMCrypto_SelectKey,
    CMD_TZ_OEMCrypto_DecryptCTR,
    CMD_TZ_OEMCrypto_WrapKeybox,
    CMD_TZ_OEMCrypto_InstallKeybox,
    CMD_TZ_OEMCrypto_IsKeyboxValid,
    CMD_TZ_OEMCrypto_GetDeviceID,
    CMD_TZ_OEMCrypto_GetKeyData,
    CMD_TZ_OEMCrypto_GetRandom,
    CMD_TZ_OEMCrypto_RewrapDeviceRSAKey,
    CMD_TZ_OEMCrypto_LoadDeviceRSAKey,
    CMD_TZ_OEMCrypto_GenerateRSASignature,
    CMD_TZ_OEMCrypto_DeriveKeysFromSessionKey,
    CMD_TZ_OEMCrypto_APIVersion,
    CMD_TZ_OEMCrypto_SecurityLevel,
    CMD_TZ_OEMCrypto_Generic_Encrypt,
    CMD_TZ_OEMCrypto_Generic_Decrypt,
    CMD_TZ_OEMCrypto_Generic_Sign,
    CMD_TZ_OEMCrypto_Generic_Verify,
#if 0
    CMD_TZ_OEMCrypto_GetHDCPCapability,
    CMD_TZ_OEMCrypto_SupportsUsageTable,
    CMD_TZ_OEMCrypto_UpdateUsageTable,
    CMD_TZ_OEMCrypto_DeactivateUsageEntry,
    CMD_TZ_OEMCrypto_ReportUsage,
    CMD_TZ_OEMCrypto_DeleteUsageEntry,
    CMD_TZ_OEMCrypto_DeleteUsageTable,
    CMD_TZ_OEMCrypto_LoadKeys,
    CMD_TZ_OEMCrypto_GenerateRSASignature,
    CMD_TZ_OEMCrypto_GetMaxNumberOfSessions,
    CMD_TZ_OEMCrypto_GetNumberOfOpenSessions,
    CMD_TZ_OEMCrypto_IsAntiRollbackHwPresent,
    CMD_TZ_OEMCrypto_CopyBuffer,
    CMD_TZ_OEMCrypto_ForceDeleteUsageEntry,
    CMD_TZ_OEMCrypto_Security_Patch_Level,
    CMD_TZ_OEMCrypto_DecryptCENC,
    CMD_TZ_OEMCrypto_QueryKeyControl,
    CMD_TZ_OEMCrypto_LoadTestKeybox,
    CMD_TZ_OEMCrypto_LoadTestRSAKey,
#endif
    CMD_TZ_CIPHER_AESCBC_ENCRYPT = 100,
    CMD_TZ_CIPHER_AESCBC_DECRYPT,
    CMD_TZ_CIPHER_AESCTR_ENCRYPT,
    CMD_TZ_CIPHER_SHA1,
    CMD_TZ_CIPHER_SHA256,
    CMD_TZ_CIPHER_HMAC_SHA1,
    CMD_TZ_CIPHER_HMAC_SHA256,
    CMD_TZ_CIPHER_RANG,
    CMD_TZ_DRM_CP_VIRCA2MMZTA,
    CMD_TZ_DRM_CP_MMZCA2VIRTA,
    CMD_TZ_DRM_CP_MMUCA2VIRTA,
//basic test
    CMD_TZ_INPUT_VALUE_TEST = 150,
    CMD_TZ_INOUT_VALUE_TEST,
    CMD_TZ_INPUT_BUFFER_TEST,
    CMD_TZ_INOUT_BUFFER_TEST,
    CMD_TZ_OEMCrypto_BUTT
}Hi_TzWidevineCommandId_E;


static TEEC_Context context;
static TEEC_Session session;
static const TEEC_UUID st_uuid_widevine = {
    0x79b77788, 0x9789, 0x4a7a,
    {0xa2, 0xbe, 0xb6, 0x1, 0x55, 0xee, 0xf5, 0xf8}
};

HI_U32 g_u32UsedNum = 0;

HI_S32 HI_DRM_UtilInit()
{
    HI_U32 origin = 0;
    TEEC_Result result;
    TEEC_Operation session_operation;

    if (g_u32UsedNum > 0)
    {
        //ALOGD("g_u32UsedNum = %d", g_u32UsedNum);
        return 0;
    }

    result = TEEC_InitializeContext(NULL, &context);
    if(result != TEEC_SUCCESS) {
        ALOGE("InitializeContext failed, ReturnCode=0x%x\n", result);
        return -1;
    } else {
        ALOGD("InitializeContext success\n");
    }

    memset(&session_operation, 0, sizeof(TEEC_Operation));
    session_operation.started = 1;
    session_operation.paramTypes = TEEC_PARAM_TYPES(
                            TEEC_NONE,
                            TEEC_NONE,
                            TEEC_MEMREF_TEMP_INPUT,
                            TEEC_MEMREF_TEMP_INPUT);

    result = TEEC_OpenSession(&context, &session, &st_uuid_widevine,
            TEEC_LOGIN_IDENTIFY, NULL, &session_operation, &origin);
    if(result != TEEC_SUCCESS) {
        ALOGE("OpenSession failed, ReturnCode=0x%x, ReturnOrigin=0x%x\n", result, origin);
        TEEC_FinalizeContext(&context);
        return -1;
    } else {
        ALOGD("OpenSession success\n");
    }

    g_u32UsedNum = 1;
    return 0;
}

HI_S32 HI_DRM_UtilCA2TA(const HI_U8* inputaddr, HI_U32 TAAddr, HI_S32 len)
{
    TEEC_Operation operation;
    TEEC_Result result;
    HI_U32 origin = 0;

    if(-1 == HI_DRM_UtilInit())
    {
        return -1;
    }

    if(len > WV_MMZ_SIZE)
    {
        ALOGE("%s >>  copy too big len   : %d", __FUNCTION__, len);
        TEEC_CloseSession(&session);
        TEEC_FinalizeContext(&context);
        return -1;
    }

    //ALOGD("%s >>  copy address:0x%08x, len:0x%08x, out:0x%08x", __FUNCTION__, (HI_U32)(inputaddr), len,(HI_U32)(TAAddr));
    memset(&operation, 0x0, sizeof(TEEC_Operation));
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT, TEEC_VALUE_INPUT, TEEC_NONE, TEEC_NONE);
    operation.params[0].tmpref.buffer = (HI_U8*)inputaddr;
    operation.params[0].tmpref.size = len;
    operation.params[1].value.a = (HI_U32)(TAAddr);

    result = TEEC_InvokeCommand( &session, CMD_TZ_DRM_CP_VIRCA2MMZTA, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        ALOGE("CMD_TZ_DRM_CP_VIRCA2MMZTA:InvokeCommand failed, ReturnCode=0x%x, ReturnOrigin=0x%x\n", result, origin);
        TEEC_CloseSession(&session);
        TEEC_FinalizeContext(&context);
        return -1;
    }
    return 0;
}

int HI_DRM_UtilDeInit()
{
    TEEC_CloseSession(&session);
    TEEC_FinalizeContext(&context);
    g_u32UsedNum = 0;
    return 0;
}

