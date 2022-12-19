/*-----------------------------------------------------------------------*/
/*!!Warning: Hisilicon key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCEm2UPcyllv4D4NOje6cFLSYglw6LvPA978sGAr3yTchgOI0M46H
HZIZCDLcNqR1rYgDnWEYHdqiWpPUq+8h0NIe4CzLQ+vlm8ZeUQMu/J9dlVeH2uOOegCBzanP
+uAaLsrakdoeetWXOhspsrsnb0DJwHxSr0rpKnxwFMZaUE6Z5MDi+2paYG8jihBCu3scz8Ow
p4w8JHN+GEWpMB+Drzl5z3Arjy0x/hawYas4BOHoX+ekSmk+35Lzl+pIA9zizw==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/

















#include    "syntax.h"
#include    "real8.h"
#include    "public.h"
#include    "bitstream.h"
#include    "vfmw.h"

#include    "vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"


#ifdef REAL8_ENABLE



SINT32 REAL8DEC_Init(RV8_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{

    return 0;
}


VOID REAL8DEC_Destroy(RV8_CTX_S *pCtx)
{
    return;
}


SINT32 REAL8DEC_Decode(RV8_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{
    return RV8_VFMW_FALSE;
}


SINT32 REAL8DEC_RecycleImage(RV8_CTX_S *pCtx, UINT32 ImgID)
{
    return RV8_VFMW_FALSE;
}


SINT32 REAL8DEC_GetRemainImg(RV8_CTX_S *pCtx)
{
    return -1;
}


UINT32 REAL8DEC_VDMPostProc(RV8_CTX_S *pCtx, SINT32 ErrRatio, UINT32 Mb0QpInCurrPic)
{
    return RV8_VFMW_FALSE;
}


SINT32 REAL8DEC_GetImageBuffer( RV8_CTX_S *pCtx )
{
    return 0;
}
VOID REAL8DEC_Support(SINT32 *flag)
{
    *flag=0;
    return;
}


#endif //REAL8_VFMW_ENABLE
