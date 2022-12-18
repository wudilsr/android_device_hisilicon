/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCDadN5jJKSuVyxmmaCmKFU6eJEbB2fyHF9weu4/jer/hxLHb+S1e
E0zVg4C3NiZh4b+GnwjAHj8JYHgZh/mRmQlo+M850KpHPOFhhSeUX482eg9sR1d+VWYFWCe9
s1gR//yjeQJI+pW6xOhVWbi3IQw8CktGpT2z0B+iqomFnFtejzuzsQDWArEQwsIrtslVRj9v
2OIBQR/MD+HCmxpTZLnFa6f/kB+OR1ipp4wuI8rKLzBK4gUnh61GhMKwk3I2Vw==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/










#include "vpss_his.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define HIS_MAD_MAX_WIDTH 1920
#define HIS_MAD_MAX_HEIGHT 1088

HI_S32 VPSS_HIS_FLUSHDATA(MMZ_BUFFER_S* pstMBuf, HI_U32 u32Data)
{
    HI_U32 u32Numb;
    HI_U32 u32Count;
    HI_U32* pu32Pos;
    u32Numb = (pstMBuf->u32Size + 3) / 4;

    pu32Pos = (HI_U32*)pstMBuf->u32StartVirAddr;

    for (u32Count = 0; u32Count < u32Numb; u32Count ++)
    {
        *pu32Pos = u32Data;
        pu32Pos = pu32Pos + 1;
    }

    return HI_SUCCESS;

}
HI_S32 VPSS_HIS_Init(VPSS_HIS_INFO_S *pstHisInfo)
{
    MMZ_BUFFER_S *pstMBuf;
    HI_S32 nRet;
    HI_U32 ii;
    HI_U32 u32InfoSize;

    //128bit align, 4pixels occpy 2bytes.
    u32InfoSize = (((HIS_MAD_MAX_WIDTH + 31) & 0xffffffe0L) /2) * HIS_MAD_MAX_HEIGHT / 2;

    //apply memory for MAD motion-infomation, and get the address.
    pstMBuf = &(pstHisInfo->stMadHisInfo.stMBuf);
    nRet = HI_DRV_MMZ_AllocAndMap("VPSS_MADMotionInfoBuf", HI_NULL, u32InfoSize * 3, 0, pstMBuf);
    if (nRet != HI_SUCCESS)
    {
		VPSS_FATAL("Get VPSS_MADMotionInfoBuf failed.\n");
		return HI_FAILURE;
    }

    VPSS_HIS_FLUSHDATA(pstMBuf, 0x007f007f);

    for (ii = 0; ii < 3; ii++)
    {
        pstHisInfo->stMadHisInfo.u32MadMvAddr[ii] 
                    = pstMBuf->u32StartPhyAddr + (u32InfoSize * ii);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_HIS_DeInit(VPSS_HIS_INFO_S *pstHisInfo)
{
    HIS_MAD_MEM_S *pstMadMem;

    pstMadMem = &(pstHisInfo->stMadHisInfo);
    
    //release MAD motion-infomation memory 
    if (pstMadMem->stMBuf.u32StartVirAddr != 0) 
    {
        HI_DRV_MMZ_UnmapAndRelease(&(pstMadMem->stMBuf));
        pstMadMem->stMBuf.u32StartVirAddr = 0;
        pstMadMem->stMBuf.u32Size = 0;
    }
    else
    {
        VPSS_FATAL("Release MadBuf Error\n");
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_HIS_GetAddr(VPSS_HIS_INFO_S *pstHisInfo,VPSS_HIS_ADDR_S *pstAddr)
{
    HIS_MAD_MEM_S *pstMadMem;
    
    HI_U32 *pu32Addr;
    HI_U32 i;
    
    HI_U32 u32Addrtmp;
    
    pstMadMem = &(pstHisInfo->stMadHisInfo);
    
    pstAddr->u32RPhyAddr = pstMadMem->u32MadMvAddr[2];
    pstAddr->u32WPhyAddr = pstMadMem->u32MadMvAddr[0];
    pstAddr->u32Stride = ((HIS_MAD_MAX_WIDTH + 31) & 0xffffffe0L) /2;

    //motion infor address
    pu32Addr = pstMadMem->u32MadMvAddr;
    
    u32Addrtmp = pu32Addr[2];
    for(i=2;i>0;i--)
    {
        pu32Addr[i] = pu32Addr[i-1];
    }
    pu32Addr[0] = u32Addrtmp;

    return HI_SUCCESS;
}                        
#ifdef __cplusplus
 #if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

