#define LOG_TAG "EMPTYDRM"

#include <cutils/log.h>
#include "tee_client_api.h"
#include "emptycpy.h"
#include "hi_drm_util.h"

#define WV_MMZ_SIZE (0x200000)

static TEEC_Context context;
static TEEC_Session session;

int initMMZBuffer()
{
    ALOGE("%s >>", __FUNCTION__);
    HI_DRM_UtilInit();
    return 0;
}

int deinitMMZBuffer()
{
    ALOGE("%s >>", __FUNCTION__);
    HI_DRM_UtilDeInit();
    return 0;
}

int emptyca2ta(const unsigned char* inputaddr, unsigned int TEEAddr, int  len)
{
    TEEC_Operation operation;
    TEEC_Result result;
    uint32_t origin;

        ALOGE("%s >>  len11  : %d", __FUNCTION__, len);
    return HI_DRM_UtilCA2TA(inputaddr,TEEAddr,len);
}
