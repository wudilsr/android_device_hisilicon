/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCDadN5jJKSuVyxmmaCmKFU6eJEbB2fyHF9weu4/jer/hxLHb+S1e
E0zVg4C3NiZh4b+GnwjAHj8JYHgZh/mRmQk1AoCXflQhLCU0MfX7LvuRdShBnU/54DqgO+TQ
uIsf7OojXgyyB44+/r8oyrLdYtYglocQ7uCoPPkgM2+sS1JlfR5EC9rXVBUyAE7rw9R4U9KT
xYrJpRFWSAAdAMCk/zlyHFDoJNh/jFAKmFm2hcPXNpIQ9F9l1tSddJycuz9m+A==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/



#include    "syntax.h"
#include    "real9.h"
#include    "public.h"
#include    "bitstream.h"
#include    "vfmw.h"

#include    "vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"
#ifdef VFMW_DNR_SUPPORT
#include    "dnr_hal.h"
#endif
SINT32 REAL9DEC_Init(RV9_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{
    return 0;
}
VOID REAL9DEC_Destroy(RV9_CTX_S *pCtx)
{
    return;
}
SINT32 REAL9DEC_Decode(RV9_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{
    return RV9_VFMW_TRUE;
}



SINT32 REAL9DEC_RecycleImage(RV9_CTX_S *pCtx, UINT32 ImgID)
{
    return RV9_VFMW_TRUE;
}
SINT32 REAL9DEC_GetRemainImg(RV9_CTX_S *pCtx)
{
    return 0;
}
UINT32 REAL9DEC_VDMPostProc(RV9_CTX_S *pCtx, SINT32 ErrRatio, UINT32 Mb0QpInCurrPic)
{
    return RV9_VFMW_TRUE;
}


SINT32 REAL9DEC_GetImageBuffer( RV9_CTX_S *pCtx )
{
    return 0;
}
VOID REAL9DEC_Support(SINT32 *flag)
{
    *flag=0;
    return;
}
