#include "sre_config.h"
#include <stdarg.h>
#include "sre_base.h"
#if (OS_HARDWARE_PLATFORM == OS_C64XPLUS)
#include "v_dspPatchTypdef.h"
#include "v_dspPatchConfig.h"
#include "v_dspPatch.h"
#endif

extern void fpga_secure_test(void);

extern UINT32 osTestInit(void);

#if (OS_HARDWARE_PLATFORM != OS_SC3400)
UINT32 SRE_HardDrvInit(VOID)
{
    return SRE_OK;
}
#endif

VOID SRE_HardBootInit()
{
}



UINT32 SRE_AppInit()
{
    UINT32 uwRet;

    uart_printf("osTestInit MemInit start2\n");
    uwRet = osTestInit();
    if(uwRet != SRE_OK)
    {
        return uwRet;
    }

    return SRE_OK;
}
