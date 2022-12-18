#include "hi_tde_type.h"
#include "tde_osictl.h"
#include "tde_osilist.h"
#include "tde_hal.h"
#include "wmalloc.h"

/* version */
#define TDE_V_VERSION 1   /* main version */
#define TDE_R_VERSION 0   /* minor version */
#define TDE_C_VERSION 0   /* */
#define TDE_B_VERSION 0   /* */
#if defined(CHIP_TYPE_hi3796cv100_a) || defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100_a) || defined(CHIP_TYPE_hi3798cv100)
#define TDE_REG_BASEADDR 0xff420000
#else
#define TDE_REG_BASEADDR 0xf8c10000
#endif
/* define for proc */
#ifdef TDE_PROC_ENABLE
TDE_HWNode_S *g_pstTdeHwNode = HI_NULL; /*节点配置信息*/
HI_U32 g_u32TdeAqCurProcNum = 0;
HI_U32 g_u32TdeSqCurProcNum = 0;
HI_U32 g_u32TdeNdCurProcNum = 0;
HI_U32 g_u32TdeMallocCnt = 0;
#endif

#define MKSTR(exp) # exp
#define MKMARCOTOSTR(exp) MKSTR(exp)
#if 0
static void tde_version(void)
{
    /* Use "strings tde.ko | grep "TDE_MAIN_VERSION"" to get the version */
    HI_CHAR TDEMainVersion[80] = "TDE_MAIN_VERSION["\
        MKMARCOTOSTR(TDE_MAIN_VERSION)"] Build Time["\
        __DATE__", "__TIME__"]";
    
    /* Use "strings tde.ko | grep "TDE_ADP_VERSION"" to get the version */
    HI_CHAR TDEAdpVersion[80] ="TDE_ADP_VERSION["\
        MKMARCOTOSTR(TDE_ADP_VERSION)"] Build Time["\
        __DATE__", "__TIME__"]";

   // printf("%s\n", TDEMainVersion);
   // printf("%s\n", TDEAdpVersion);
}
#endif

int  tde_osr_init(void)
{


  //  tde_version();

    /* 初始化hal层 */
    if (TdeHalInit(TDE_REG_BASEADDR) < 0)
    {
        return -1;
    }

    TdeOsiListInit();

    TDE_TRACE(TDE_KERN_DEBUG, "init tde successful!\n");
    return 0;
}


void tde_osr_deinit(void)
{
    /* 去初始化list层 */
    TdeOsiListTerm();

    TdeHalRelease();

 
    return;
}

