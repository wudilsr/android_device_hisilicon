#include <uboot.h>
#include "hi_boot_logo.h"

HI_S32 HI_LOGO_DecImg(HI_LOGO_PARAM_S stLogoParam, HI_U32 u32LogoDataAddr, HI_HANDLE *phSurface)
{
    HI_S32                      Ret;
    HIGO_DEC_ATTR_S             stDecAttr;
    HI_HANDLE                   hDec;

    memset(&stDecAttr, 0x00, sizeof(HIGO_DEC_ATTR_S));
    stDecAttr.SrcInfo.MemInfo.pAddr = (HI_CHAR*)(u32LogoDataAddr);
    stDecAttr.SrcInfo.MemInfo.Length = stLogoParam.u32LogoLen;
    Ret = HI_GO_CreateDecoder(&stDecAttr, &hDec);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_GO_CreateDecoder err! Ret = %x\n", Ret);
        return Ret;
    }

    Ret = HI_GO_DecImgData(hDec, 0, NULL, phSurface);

    Ret |= HI_GO_DestroyDecoder(hDec);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_GO_DestroyDecoder err! Ret = %x\n", Ret);
        return Ret;
    }    

    return HI_SUCCESS;
}




