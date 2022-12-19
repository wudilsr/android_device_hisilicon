#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <asm/memory.h>
#include <linux/bootmem.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/memblock.h>

#include "hi_drv_pdm.h"
#include "hi_db.h"
#include "drv_pdm_ext.h"
#include "drv_pdm.h"
#include "hi_drv_sys.h"

#define DRV_PDM_LOCK(pMutex) \
    do { \
        if (down_interruptible(pMutex)) \
        {       \
            HI_ERR_PDM("ERR: pdm lock error!\n");    \
        }   \
    } while (0)

#define DRV_PDM_UNLOCK(pMutex) \
    do { \
        up(pMutex); \
    } while (0)

extern PDM_GLOBAL_S g_PdmGlobal;
extern int pdm_free_reserve_mem(u32 phyaddr, u32 size);

static HI_BOOL g_bVolumeExistInBase = HI_FALSE;

#if 0
static HI_UNF_DISP_TIMING_S g_stDispTiming =
{
    .VFB           =                               27,
    .VBB           =                               23,
    .VACT          =                              768,
    .HFB           =                              210,
    .HBB           =                               46,
    .HACT          =                             1366,
    .VPW           =								4,
    .HPW           =                               24,
    .IDV           =								0,
    .IHS           =								0,
    .IVS           =								0,
    .ClockReversal = HI_FALSE,
    .DataWidth     = HI_UNF_DISP_INTF_DATA_WIDTH24,
    .ItfFormat     = HI_UNF_DISP_INTF_DATA_FMT_RGB888,
    .DitherEnable  = HI_FALSE,
    .ClkPara0      =                       0x912ccccc,
    .ClkPara1      =                       0x006d8157,

    //.InRectWidth = 1366,
    //.InRectHeight = 768,
};
#endif

HI_CHAR *PDM_VmapByPhyaddr(HI_U32 phy_addr, HI_U32 size)
{
    HI_U32 i;
    HI_CHAR *vaddr = NULL;
    struct page **page_array = NULL;
    HI_U32 page_array_size = (size + PAGE_SIZE - 1) / PAGE_SIZE;

    page_array = vmalloc(page_array_size * sizeof(struct page *));
    if (!page_array) {
        HI_ERR_PDM("fail to vmalloc %u bytes\n", page_array_size * sizeof(struct page *));
        goto error_out;
    }

    for (i=0; i < page_array_size; i++) {
        page_array[i] = phys_to_page(phy_addr + i * PAGE_SIZE);
    }

    if (i != page_array_size) {
        HI_ERR_PDM("incorrect page array for vmap, \
                array size is %u, but %u filled\n", page_array_size, i);
        goto error_out;
    }

    vaddr = (unsigned char *)vmap(page_array, page_array_size, VM_MAP, PAGE_KERNEL);
    if (!vaddr) {
        HI_ERR_PDM("fail to vmap %lu at 0x%lX\n", phy_addr, size);
        goto error_out;
    }

    if (page_array)
        vfree(page_array);

    return vaddr;

error_out:
    if (page_array)
        vfree(page_array);
	

    return NULL;
}

HI_VOID PDM_GetDefDispParam(HI_UNF_DISP_E enDisp, HI_DISP_PARAM_S *pstDispParam)
{
    HI_S32 i;

    //memset(pstDispParam, 0x0, sizeof(HI_DISP_PARAM_S));
	
    if (enDisp == HI_UNF_DISPLAY0)
    {
        pstDispParam->enSrcDisp         = HI_UNF_DISPLAY1;
        pstDispParam->enFormat          = HI_UNF_ENC_FMT_NTSC;
        pstDispParam->u32Brightness     = 50;
        pstDispParam->u32Contrast       = 50;
        pstDispParam->u32Saturation     = 50;
        pstDispParam->u32HuePlus        = 50;
        pstDispParam->bGammaEnable      = HI_FALSE;
        pstDispParam->u32VirtScreenWidth = 1280;
        pstDispParam->u32VirtScreenHeight = 720;
        
        memset(&(pstDispParam->stOffsetInfo), 0x0, sizeof(HI_UNF_DISP_OFFSET_S));

        memset(&(pstDispParam->stBgColor), 0x0, sizeof(HI_UNF_DISP_BG_COLOR_S));

        pstDispParam->stAspectRatio.enDispAspectRatio = HI_UNF_DISP_ASPECT_RATIO_AUTO;

        pstDispParam->enPixelFormat = HIGO_PF_8888;        
        
        for (i = 0; i < HI_UNF_DISP_INTF_TYPE_BUTT; i++)
        {
            if (i == HI_UNF_DISP_INTF_TYPE_CVBS)
            {
                pstDispParam->stIntf[i].enIntfType = HI_UNF_DISP_INTF_TYPE_CVBS;
                pstDispParam->stIntf[i].unIntf.stCVBS.u8Dac = HI_DAC_CVBS;
            }
            else
            {
                pstDispParam->stIntf[i].enIntfType = HI_UNF_DISP_INTF_TYPE_BUTT;
            }
        }        
    }

    if (enDisp == HI_UNF_DISPLAY1)
    {
        pstDispParam->enSrcDisp         = HI_UNF_DISPLAY1;
        pstDispParam->enFormat          = HI_UNF_ENC_FMT_720P_60;
        pstDispParam->u32Brightness     = 50;
        pstDispParam->u32Contrast       = 50;
        pstDispParam->u32Saturation     = 50;
        pstDispParam->u32HuePlus        = 50;
        pstDispParam->bGammaEnable      = HI_FALSE;
        pstDispParam->u32VirtScreenWidth = 1280;
        pstDispParam->u32VirtScreenHeight = 720;
        
        memset(&(pstDispParam->stOffsetInfo), 0x0, sizeof(HI_UNF_DISP_OFFSET_S));

        memset(&(pstDispParam->stBgColor), 0x0, sizeof(HI_UNF_DISP_BG_COLOR_S));

        pstDispParam->stAspectRatio.enDispAspectRatio = HI_UNF_DISP_ASPECT_RATIO_AUTO;

        pstDispParam->enPixelFormat = HIGO_PF_8888;        
        
        for (i = 0; i < HI_UNF_DISP_INTF_TYPE_BUTT; i++)
        {
            if (i == HI_UNF_DISP_INTF_TYPE_YPBPR)
            {
                pstDispParam->stIntf[i].enIntfType = HI_UNF_DISP_INTF_TYPE_YPBPR;
                pstDispParam->stIntf[i].unIntf.stYPbPr.u8DacY = HI_DAC_YPBPR_Y;
                pstDispParam->stIntf[i].unIntf.stYPbPr.u8DacPb = HI_DAC_YPBPR_PB;
                pstDispParam->stIntf[i].unIntf.stYPbPr.u8DacPr = HI_DAC_YPBPR_PR;
            }
            else if (i == HI_UNF_DISP_INTF_TYPE_HDMI)
            {
                pstDispParam->stIntf[i].enIntfType = HI_UNF_DISP_INTF_TYPE_HDMI;
                pstDispParam->stIntf[i].unIntf.enHdmi = HI_UNF_HDMI_ID_0;
            }
            else
            {
                pstDispParam->stIntf[i].enIntfType = HI_UNF_DISP_INTF_TYPE_BUTT;
            }
        }        
    }

    return;
}

HI_S32 PDM_GetBufByName(const HI_CHAR *BufName, HI_U32 *pu32BasePhyAddr, HI_U32 *pu32Len)
{
    HI_S32 i;

    for (i = 0; i < g_PdmGlobal.u32BufNum; i++)
    {
        if (0 == strncmp(g_PdmGlobal.stBufInfo[i].as8BufName, BufName, strlen(BufName)))
        {
            break;
        }
    }

    if (i >= g_PdmGlobal.u32BufNum)
    {
        return HI_FAILURE;
    }

    *pu32BasePhyAddr = g_PdmGlobal.stBufInfo[i].u32PhyAddr;

    *pu32Len = g_PdmGlobal.stBufInfo[i].u32Lenth;

    return HI_SUCCESS;
}

HI_S32 PDM_SetVirAddrByName(const HI_CHAR *BufName, HI_U32 u32VirAddr)
{
    HI_U32 i;

    DRV_PDM_LOCK(&g_PdmGlobal.PdmMutex);

    for (i = 0; i < g_PdmGlobal.u32BufNum; i++)
    {
        if (0 == strncmp(g_PdmGlobal.stBufInfo[i].as8BufName, BufName, strlen(BufName)))
        {
            break;
        }
    }

    if (i >= g_PdmGlobal.u32BufNum)
    {
        DRV_PDM_UNLOCK(&g_PdmGlobal.PdmMutex);
        HI_INFO_PDM("can not find buffer:%s\n", BufName);
        return HI_FAILURE;
    }

    g_PdmGlobal.stBufInfo[i].u32VirAddr = u32VirAddr;
    DRV_PDM_UNLOCK(&g_PdmGlobal.PdmMutex);
    return HI_SUCCESS;
}

HI_S32 PDM_GetVirAddrByName(const HI_CHAR *BufName, HI_U32 *pu32VirAddr, HI_U32 *pu32Len)
{
    HI_U32 i;

    DRV_PDM_LOCK(&g_PdmGlobal.PdmMutex);
    for (i = 0; i < g_PdmGlobal.u32BufNum; i++)
    {
        if (0 == strncmp(g_PdmGlobal.stBufInfo[i].as8BufName, BufName, strlen(BufName)))
        {
            break;
        }
    }

    if (i >= g_PdmGlobal.u32BufNum)
    {
        DRV_PDM_UNLOCK(&g_PdmGlobal.PdmMutex);
        HI_INFO_PDM("can not find buffer:%s\n", BufName);
        return HI_FAILURE;
    }

    *pu32VirAddr = g_PdmGlobal.stBufInfo[i].u32VirAddr;
    *pu32Len = g_PdmGlobal.stBufInfo[i].u32Lenth;
    DRV_PDM_UNLOCK(&g_PdmGlobal.PdmMutex);
    return HI_SUCCESS;
}

HI_VOID PDM_TransFomat(HI_UNF_ENC_FMT_E enSrcFmt, HI_UNF_ENC_FMT_E *penHdFmt, HI_UNF_ENC_FMT_E *penSdFmt)
{
    switch (enSrcFmt)
    {
        /* bellow are tv display formats */
    case HI_UNF_ENC_FMT_1080P_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_1080P_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_1080P_50:
    {
        *penHdFmt = HI_UNF_ENC_FMT_1080P_50;
        *penSdFmt = HI_UNF_ENC_FMT_PAL;
        break;
    }
    case HI_UNF_ENC_FMT_1080i_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_1080i_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_1080i_50:
    {
        *penHdFmt = HI_UNF_ENC_FMT_1080i_50;
        *penSdFmt = HI_UNF_ENC_FMT_PAL;
        break;
    }
    case HI_UNF_ENC_FMT_720P_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_720P_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_720P_50:
    {
        *penHdFmt = HI_UNF_ENC_FMT_720P_50;
        *penSdFmt = HI_UNF_ENC_FMT_PAL;
        break;
    }
    case HI_UNF_ENC_FMT_576P_50:
    {
        *penHdFmt = HI_UNF_ENC_FMT_576P_50;
        *penSdFmt = HI_UNF_ENC_FMT_PAL;
        break;
    }
    case HI_UNF_ENC_FMT_480P_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_480P_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_PAL:
    {
        *penHdFmt = HI_UNF_ENC_FMT_PAL;
        *penSdFmt = HI_UNF_ENC_FMT_PAL;
        break;
    }
    case HI_UNF_ENC_FMT_NTSC:
    {
        *penHdFmt = HI_UNF_ENC_FMT_NTSC;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }

        /* bellow are vga display formats */
    case HI_UNF_ENC_FMT_861D_640X480_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_861D_640X480_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_800X600_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_800X600_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1024X768_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1024X768_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1280X720_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1280X720_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1280X800_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1280X800_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1280X1024_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1280X1024_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1360X768_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1360X768_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1366X768_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1366X768_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1400X1050_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1400X1050_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1440X900_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1440X900_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1440X900_60_RB:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1440X900_60_RB;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1600X900_60_RB:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1600X900_60_RB;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1600X1200_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1600X1200_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1680X1050_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1680X1050_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }

    case HI_UNF_ENC_FMT_VESA_1920X1080_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1920X1080_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_1920X1200_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_1920X1200_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    case HI_UNF_ENC_FMT_VESA_2048X1152_60:
    {
        *penHdFmt = HI_UNF_ENC_FMT_VESA_2048X1152_60;
        *penSdFmt = HI_UNF_ENC_FMT_NTSC;
        break;
    }
    default:
    {
        *penHdFmt = HI_UNF_ENC_FMT_1080i_50;
        *penSdFmt = HI_UNF_ENC_FMT_PAL;
        break;
    }
    }

    return;
}

static HI_S32 DRV_PDM_GetCustomTiming(HI_DB_TABLE_S *pstTable, HI_UNF_DISP_TIMING_S *pstTiming)
{
    HI_S32 Ret;
    HI_DB_KEY_S stKey;

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_VFB, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->VFB = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_VBB, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->VBB = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_VACT, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->VACT = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_HFB, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->HFB = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_HBB, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->HBB = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_HACT, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->HACT = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_VPW, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->VPW = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_HPW, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->HPW = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_IDV, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->IDV = *(HI_BOOL*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_IHS, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->IHS = *(HI_BOOL*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_IVS, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->IVS = *(HI_BOOL*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_CLKR, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->ClockReversal = *(HI_BOOL*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_DW, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->DataWidth = *(HI_UNF_DISP_INTF_DATA_WIDTH_E*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_ITFMT, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->ItfFormat = *(HI_UNF_DISP_INTF_DATA_FMT_E*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_DITE, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->DitherEnable = *(HI_BOOL*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_CLK0, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->ClkPara0 = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_CLK1, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->ClkPara1 = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_INTERL, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->bInterlace = *(HI_BOOL*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_FIXF, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->PixFreq = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_VERTF, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->VertFreq = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_AW, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->AspectRatioW = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_AH, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->AspectRatioH = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_USEGAMMA, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->bUseGamma = *(HI_BOOL*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_RSV0, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->Reserve0 = *(HI_U32*)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(pstTable, MCE_BASE_KEYNAME_TIMING_RSV1, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstTiming->Reserve1 = *(HI_U32*)(stKey.pValue);
    }

    return HI_SUCCESS;
}

HI_S32 DRV_PDM_GetDispParam(HI_UNF_DISP_E enDisp, HI_DISP_PARAM_S *pstDispParam)
{
    HI_S32 Ret;
    HI_DB_S stBaseDB;
    HI_DB_TABLE_S stTable;
    HI_DB_KEY_S stKey;
    HI_U32 u32BasePhyAddr;
    HI_U32 u32BaseVirAddr;
    HI_U32 u32BaseLen;
    HI_SYS_MEM_CONFIG_S     stMemCfg;

    if ((HI_SUCCESS != PDM_GetVirAddrByName(PDM_BASEPARAM_BUFNAME, &u32BaseVirAddr, &u32BaseLen))
        || (HI_NULL == u32BaseVirAddr))
    {
        Ret = PDM_GetBufByName(PDM_BASEPARAM_BUFNAME, &u32BasePhyAddr, &u32BaseLen);
        if (HI_SUCCESS != Ret)
        {
            // if there is no baseparam, use default
            PDM_GetDefDispParam(enDisp, pstDispParam);
            return HI_SUCCESS;
        }

        u32BaseVirAddr = (HI_U32)PDM_VmapByPhyaddr(u32BasePhyAddr, u32BaseLen);
        PDM_SetVirAddrByName(PDM_BASEPARAM_BUFNAME, u32BaseVirAddr);
    }

    PDM_GetDefDispParam(enDisp, pstDispParam);

    Ret = HI_DB_GetDBFromMem((HI_U8 *)u32BaseVirAddr, &stBaseDB);
    if (HI_SUCCESS != Ret)
    {
        HI_INFO_PDM("ERR: HI_DB_GetDBFromMem, use default baseparam!\n");
        return HI_FAILURE;
    }

    if (HI_UNF_DISPLAY0 == enDisp)
    {
        Ret = HI_DB_GetTableByName(&stBaseDB, MCE_BASE_TABLENAME_DISP0, &stTable);
    }
    else
    {
        Ret = HI_DB_GetTableByName(&stBaseDB, MCE_BASE_TABLENAME_DISP1, &stTable);
    }

    if (HI_SUCCESS != Ret)
    {
        HI_INFO_PDM("ERR: HI_DB_GetTableByName, use default baseparam!\n");
        return HI_SUCCESS;
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_FMT, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->enFormat = *(HI_UNF_ENC_FMT_E *)(stKey.pValue);
        if (HI_UNF_ENC_FMT_BUTT == pstDispParam->enFormat)
        {
            Ret = DRV_PDM_GetCustomTiming(&stTable, &(pstDispParam->stDispTiming));
        }
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_INTF_HDMI, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_HDMI] = *(HI_UNF_DISP_INTF_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_INTF_YPBPR, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_YPBPR] = *(HI_UNF_DISP_INTF_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_INTF_CVBS, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_CVBS] = *(HI_UNF_DISP_INTF_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_INTF_RGB, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_RGB] = *(HI_UNF_DISP_INTF_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_INTF_SVIDEO, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_SVIDEO] = *(HI_UNF_DISP_INTF_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_INTF_BT1120, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_BT1120] = *(HI_UNF_DISP_INTF_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_INTF_BT656, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_BT656] = *(HI_UNF_DISP_INTF_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_INTF_LCD, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_LCD] = *(HI_UNF_DISP_INTF_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_INTF_VGA, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_VGA] = *(HI_UNF_DISP_INTF_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_HULEP, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->u32HuePlus = *(HI_U32 *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SATU, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->u32Saturation = *(HI_U32 *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_CONTR, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->u32Contrast = *(HI_U32 *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_BRIG, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->u32Brightness = *(HI_U32 *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_BGCOLOR, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stBgColor = *(HI_UNF_DISP_BG_COLOR_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_GAMA, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->bGammaEnable = *(HI_BOOL *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_ASPECT, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stAspectRatio = *(HI_UNF_DISP_ASPECT_RATIO_S *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SRC_DISP, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->enSrcDisp = *(HI_UNF_DISP_E *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_VIRSCW, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->u32VirtScreenWidth = *(HI_U32 *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_VIRSCH, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->u32VirtScreenHeight = *(HI_U32 *)(stKey.pValue);
    }

    /* if ddr size is 512M, use 720P virtural screen */
    Ret = HI_DRV_SYS_GetMemConfig(&stMemCfg);
    if (HI_SUCCESS == Ret && stMemCfg.u32TotalSize == 512)
    {
        pstDispParam->u32VirtScreenWidth = 1280;
        pstDispParam->u32VirtScreenHeight = 720;
    }

	if ((pstDispParam->u32VirtScreenWidth > 3840)
        || (pstDispParam->u32VirtScreenWidth < 480)
        || (pstDispParam->u32VirtScreenHeight > 3840)
        || (pstDispParam->u32VirtScreenHeight < 480)
    )
    {
		HI_INFO_PDM("Invalid vir screen:W %d, H %d\n", 
			pstDispParam->u32VirtScreenWidth, pstDispParam->u32VirtScreenHeight);

		pstDispParam->u32VirtScreenWidth = 1280;
		pstDispParam->u32VirtScreenHeight = 720;
	}

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_DISP_L, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stOffsetInfo.u32Left = *(HI_U32 *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_DISP_T, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stOffsetInfo.u32Top = *(HI_U32 *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_DISP_R, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stOffsetInfo.u32Right = *(HI_U32 *)(stKey.pValue);
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_DISP_B, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->stOffsetInfo.u32Bottom = *(HI_U32 *)(stKey.pValue);
    }

	if ((pstDispParam->stOffsetInfo.u32Left > 200)
        || (pstDispParam->stOffsetInfo.u32Top > 200)
        || (pstDispParam->stOffsetInfo.u32Right > 200)
        || (pstDispParam->stOffsetInfo.u32Bottom > 200)
    )
    {
    	HI_INFO_PDM("Invalid offset:T %d, B %d, L %d, R %d\n",
			pstDispParam->stOffsetInfo.u32Top,
			pstDispParam->stOffsetInfo.u32Bottom,
			pstDispParam->stOffsetInfo.u32Left,
			pstDispParam->stOffsetInfo.u32Right);
		
		pstDispParam->stOffsetInfo.u32Left = 0;
		pstDispParam->stOffsetInfo.u32Top = 0;
		pstDispParam->stOffsetInfo.u32Right = 0;
		pstDispParam->stOffsetInfo.u32Bottom = 0;
	}

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_PF, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstDispParam->enPixelFormat = *(HIGO_PF_E *)(stKey.pValue);
		if ((pstDispParam->enPixelFormat < HIGO_PF_4444) || (pstDispParam->enPixelFormat > HIGO_PF_0888))
		{
		    HI_INFO_PDM("Invalid enPixelFormat:%d\n", pstDispParam->enPixelFormat);

			pstDispParam->enPixelFormat = HIGO_PF_8888;
		}
    }
    else
    {
        pstDispParam->enPixelFormat = HIGO_PF_8888;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_PDM_GetMceParam(HI_MCE_PARAM_S *pstMceParam)
{
    HI_S32 Ret;
    HI_DB_S stBaseDB;
    HI_DB_TABLE_S stTable;
    HI_DB_KEY_S stKey;
    HI_U32 u32MceParaPhyAddr;
    HI_U32 u32MceParaVirAddr;
    HI_U32 u32MceParaLen;

    if ((HI_SUCCESS != PDM_GetVirAddrByName(PDM_PLAYPARAM_BUFNAME, &u32MceParaVirAddr, &u32MceParaLen))
        || (HI_NULL == u32MceParaVirAddr))
    {
        Ret = PDM_GetBufByName(PDM_PLAYPARAM_BUFNAME, &u32MceParaPhyAddr, &u32MceParaLen);
        if (HI_SUCCESS != Ret)
        {
            return Ret;
        }

        u32MceParaVirAddr = (HI_U32)PDM_VmapByPhyaddr(u32MceParaPhyAddr, u32MceParaLen);
        PDM_SetVirAddrByName(PDM_PLAYPARAM_BUFNAME, u32MceParaVirAddr);
    }

    Ret = HI_DB_GetDBFromMem((HI_U8 *)u32MceParaVirAddr, &stBaseDB);
    if (HI_SUCCESS != Ret)
    {
        HI_INFO_PDM("ERR: HI_DB_GetDBFromMem!\n");
        return HI_FAILURE;
    }

    Ret = HI_DB_GetTableByName(&stBaseDB, MCE_PLAY_TABLENAME, &stTable);
    if (HI_SUCCESS != Ret)
    {
        HI_INFO_PDM("ERR: HI_DB_GetTableByName!\n");
        return HI_FAILURE;
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_PLAY_KEYNAME_FLAG, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstMceParam->u32CheckFlag = *(HI_U32 *)(stKey.pValue);
    }
    else
    {
        pstMceParam->u32CheckFlag = 0;
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_PLAY_KEYNAME_DATALEN, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstMceParam->u32PlayDataLen = *(HI_U32 *)(stKey.pValue);
    }
    else
    {
        pstMceParam->u32PlayDataLen = 0;
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_PLAY_KEYNAME_PARAM, &stKey);
    if (HI_SUCCESS == Ret)
    {
        pstMceParam->stPlayParam = *(HI_UNF_MCE_PLAY_PARAM_S *)(stKey.pValue);
    }
    else
    {
        memset(&(pstMceParam->stPlayParam), 0x00, sizeof(HI_UNF_MCE_PLAY_PARAM_S));
    }

    return HI_SUCCESS;
}

HI_S32 DRV_PDM_GetMceData(HI_U32 u32Size, HI_U32 *pAddr)
{
    HI_S32 Ret;
    HI_U32 u32MceDataPhyAddr;
    HI_U32 u32MceDataLen;
    HI_U32 u32MceDataVirAddr;

    if ((HI_SUCCESS != PDM_GetVirAddrByName(PDM_PLAYDATA_BUFNAME, &u32MceDataVirAddr, &u32MceDataLen))
        || (HI_NULL == u32MceDataVirAddr))
    {
        Ret = PDM_GetBufByName(PDM_PLAYDATA_BUFNAME, &u32MceDataPhyAddr, &u32MceDataLen);
        if (HI_SUCCESS != Ret)
        {
            return Ret;
        }

        u32MceDataVirAddr = (HI_U32)PDM_VmapByPhyaddr(u32MceDataPhyAddr, u32MceDataLen);
        PDM_SetVirAddrByName(PDM_PLAYDATA_BUFNAME, u32MceDataVirAddr);
    }

    *pAddr = u32MceDataVirAddr;

    return HI_SUCCESS;
}

HI_S32 DRV_PDM_GetData(const HI_CHAR *BufName, HI_U32 *pu32DataAddr, HI_U32 *pu32DataLen)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32PhyAddr = 0;

    if ((HI_NULL != BufName)
        && (HI_NULL != pu32DataAddr)
        && (HI_NULL != pu32DataLen))
    {
        if ((HI_SUCCESS != PDM_GetVirAddrByName(BufName, pu32DataAddr, pu32DataLen))
            || (HI_NULL == *pu32DataAddr))
        {
            Ret = PDM_GetBufByName(BufName, &u32PhyAddr, pu32DataLen);
            if (HI_SUCCESS != Ret)
            {
                return Ret;
            }

            *pu32DataAddr = (HI_U32)PDM_VmapByPhyaddr(u32PhyAddr, *pu32DataLen);

            return PDM_SetVirAddrByName(BufName, *pu32DataAddr);
        }
        else
        {
            return HI_SUCCESS;
        }
    }
    else
    {
        return HI_FAILURE;
    }
}

HI_S32 DRV_PDM_GetSoundParam(HI_UNF_SND_E enSound, HI_UNF_PDM_SOUND_PARAM_S *pstSoundParam)
{
    HI_S32 Ret;
    HI_DB_S stBaseDB;
    HI_DB_TABLE_S stTable;
    HI_DB_KEY_S stKey;
    HI_U32 u32BasePhyAddr;
    HI_U32 u32BaseVirAddr;
    HI_U32 u32BaseLen;
    HI_U32 u32Volume;

    if ((enSound >= HI_UNF_SND_BUTT) || (HI_NULL == pstSoundParam))
    {
        return HI_FAILURE;
    }

    if ((HI_SUCCESS != PDM_GetVirAddrByName(PDM_BASEPARAM_BUFNAME, &u32BaseVirAddr, &u32BaseLen))
        || (HI_NULL == u32BaseVirAddr))
    {
        Ret = PDM_GetBufByName(PDM_BASEPARAM_BUFNAME, &u32BasePhyAddr, &u32BaseLen);
        if (HI_SUCCESS != Ret)
        {
            return Ret;
        }

        u32BaseVirAddr = (HI_U32)PDM_VmapByPhyaddr(u32BasePhyAddr, u32BaseLen);
        PDM_SetVirAddrByName(PDM_BASEPARAM_BUFNAME, u32BaseVirAddr);
    }

    Ret = HI_DB_GetDBFromMem((HI_U8 *)u32BaseVirAddr, &stBaseDB);
    if (HI_SUCCESS != Ret)
    {
        HI_INFO_PDM("ERR: HI_DB_GetDBFromMem, use default baseparam!\n");
        return HI_FAILURE;
    }

    if (HI_UNF_SND_0 == enSound)
    {
        Ret = HI_DB_GetTableByName(&stBaseDB, MCE_BASE_TABLENAME_SOUND0, &stTable);
    }
    else if (HI_UNF_SND_1 == enSound)
    {
        Ret = HI_DB_GetTableByName(&stBaseDB, MCE_BASE_TABLENAME_SOUND1, &stTable);
    }
    else
    {
        Ret = HI_DB_GetTableByName(&stBaseDB, MCE_BASE_TABLENAME_SOUND2, &stTable);
    }

    if (HI_SUCCESS != Ret)
    {
        HI_INFO_PDM("ERR: HI_DB_GetTableByName, use default baseparam!\n");
        return HI_FAILURE;
    }

    pstSoundParam->u32PortNum = 0;

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_DAC0, &stKey);
    if ((HI_SUCCESS == Ret) && (*(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue) == HI_UNF_SND_OUTPUTPORT_DAC0))
    {
        pstSoundParam->stOutport[pstSoundParam->u32PortNum].enOutPort = *(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue);

        Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_DAC0_VOLUME, &stKey);
        if (Ret == HI_SUCCESS)
        {
            u32Volume = *(HI_U32 *)(stKey.pValue);
            if (u32Volume > 100)
            {
                u32Volume = 50;
            }
            g_bVolumeExistInBase = HI_TRUE;
        }
        else
        {
            u32Volume = 50;
            g_bVolumeExistInBase = HI_FALSE;
        }

        pstSoundParam->au32Volume[pstSoundParam->u32PortNum] = u32Volume;
        pstSoundParam->u32PortNum++;
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_SPDIF0, &stKey);
    if ((HI_SUCCESS == Ret) && (*(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue) == HI_UNF_SND_OUTPUTPORT_SPDIF0))
    {
        pstSoundParam->stOutport[pstSoundParam->u32PortNum].enOutPort = *(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue);

        Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_SPDIF0_VOLUME, &stKey);
        if (Ret == HI_SUCCESS)
        {
            u32Volume = *(HI_U32 *)(stKey.pValue);
            if (u32Volume > 100)
            {
                u32Volume = 50;
            }
            g_bVolumeExistInBase = HI_TRUE;
        }
        else
        {
            u32Volume = 50;
            g_bVolumeExistInBase = HI_FALSE;
        }

        pstSoundParam->au32Volume[pstSoundParam->u32PortNum] = u32Volume;
        pstSoundParam->u32PortNum++;
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_HDMI0, &stKey);
    if ((HI_SUCCESS == Ret) && (*(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue) == HI_UNF_SND_OUTPUTPORT_HDMI0))
    {
        pstSoundParam->stOutport[pstSoundParam->u32PortNum].enOutPort = *(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue);

        Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_HDMI0_VOLUME, &stKey);
        if (Ret == HI_SUCCESS)
        {
            u32Volume = *(HI_U32 *)(stKey.pValue);
            if (u32Volume > 100)
            {
                u32Volume = 50;
            }
            g_bVolumeExistInBase = HI_TRUE;
        }
        else
        {
            u32Volume = 50;
            g_bVolumeExistInBase = HI_FALSE;
        }

        pstSoundParam->au32Volume[pstSoundParam->u32PortNum] = u32Volume;
        pstSoundParam->u32PortNum++;
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_ARC0, &stKey);
    if ((HI_SUCCESS == Ret) && (*(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue) == HI_UNF_SND_OUTPUTPORT_ARC0))
    {
        pstSoundParam->stOutport[pstSoundParam->u32PortNum].enOutPort = *(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue);

        Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_ARC0_VOLUME, &stKey);
        if (Ret == HI_SUCCESS)
        {
            u32Volume = *(HI_U32 *)(stKey.pValue);
            if (u32Volume > 100)
            {
                u32Volume = 50;
            }
            g_bVolumeExistInBase = HI_TRUE;
        }
        else
        {
            u32Volume = 50;
            g_bVolumeExistInBase = HI_FALSE;
        }

        pstSoundParam->au32Volume[pstSoundParam->u32PortNum] = u32Volume;
        pstSoundParam->u32PortNum++;
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_I2S0, &stKey);
    if ((HI_SUCCESS == Ret) && (*(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue) == HI_UNF_SND_OUTPUTPORT_I2S0))
    {
        pstSoundParam->stOutport[pstSoundParam->u32PortNum].enOutPort = *(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue);
        pstSoundParam->stOutport[pstSoundParam->u32PortNum].unAttr.stI2sAttr = *(HI_UNF_SND_I2S_ATTR_S *)(stKey.pValue + sizeof(HI_UNF_SND_OUTPUTPORT_E));

        Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_I2S0_VOLUME, &stKey);
        if (Ret == HI_SUCCESS)
        {
            u32Volume = *(HI_U32 *)(stKey.pValue);
            if (u32Volume > 100)
            {
                u32Volume = 50;
            }
            g_bVolumeExistInBase = HI_TRUE;
        }
        else
        {
            u32Volume = 50;
            g_bVolumeExistInBase = HI_FALSE;
        }

        pstSoundParam->au32Volume[pstSoundParam->u32PortNum] = u32Volume;
        pstSoundParam->u32PortNum++;
    }

    Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_I2S1, &stKey);
    if ((HI_SUCCESS == Ret) && (*(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue) == HI_UNF_SND_OUTPUTPORT_I2S1))
    {
        pstSoundParam->stOutport[pstSoundParam->u32PortNum].enOutPort = *(HI_UNF_SND_OUTPUTPORT_E *)(stKey.pValue);
        pstSoundParam->stOutport[pstSoundParam->u32PortNum].unAttr.stI2sAttr = *(HI_UNF_SND_I2S_ATTR_S *)(stKey.pValue + sizeof(HI_UNF_SND_OUTPUTPORT_E));

        Ret = HI_DB_GetKeyByName(&stTable, MCE_BASE_KEYNAME_SND_I2S1_VOLUME, &stKey);
        if (Ret == HI_SUCCESS)
        {
            u32Volume = *(HI_U32 *)(stKey.pValue);
            if (u32Volume > 100)
            {
                u32Volume = 50;
            }
            g_bVolumeExistInBase = HI_TRUE;
        }
        else
        {
            u32Volume = 50;
            g_bVolumeExistInBase = HI_FALSE;
        }

        pstSoundParam->au32Volume[pstSoundParam->u32PortNum] = u32Volume;
        pstSoundParam->u32PortNum++;
    }

    return HI_SUCCESS;
}

extern int get_param_data(const char *name, char *buf, unsigned int buflen);
extern int set_param_data(const char *name, char *buf, unsigned int buflen);

static HI_S32 DRV_PDM_TagRemoveBuff(const HI_CHAR *BufName)
{
    HI_CHAR PdmTag[512];
    HI_U32 PdmLen;
    HI_CHAR                 *p, *q;
    HI_U32 ii = 0;

    memset(PdmTag, 0x0, 512);

    PdmLen = get_param_data("pdm_tag", PdmTag, 512);
    if (PdmLen >= 512)
    {
        return HI_FAILURE;
    }

    PdmTag[511] = '\0';

    p = strstr(PdmTag, BufName);

    if (HI_NULL == p)
    {
        return HI_FAILURE;
    }

    q = strstr(p, " ");
    if (HI_NULL == q)
    {
        *p = '\0';
    }
    else
    {
        q++;
        for (ii = 0; ii < (strlen(PdmTag) - (q - PdmTag)); ii++)
        {
            p[ii] = q[ii];
        }

        p[ii] = '\0';
    }

    set_param_data("pdm_tag", PdmTag, strlen(PdmTag) + 1);

    return HI_SUCCESS;
}

HI_S32 DRV_PDM_ReleaseReserveMem(const HI_CHAR *BufName)
{
    HI_U32 i;

    DRV_PDM_LOCK(&g_PdmGlobal.PdmMutex);

    for (i = 0; i < g_PdmGlobal.u32BufNum; i++)
    {
        if (0 == strncmp(g_PdmGlobal.stBufInfo[i].as8BufName, BufName, strlen(BufName)))
        {
            break;
        }
    }

    if (i >= g_PdmGlobal.u32BufNum)
    {
        DRV_PDM_UNLOCK(&g_PdmGlobal.PdmMutex);
        return HI_FAILURE;
    }

    if (g_PdmGlobal.stBufInfo[i].bRelease)
    {
        DRV_PDM_UNLOCK(&g_PdmGlobal.PdmMutex);
        return HI_SUCCESS;
    }

    g_PdmGlobal.stBufInfo[i].bRelease = HI_TRUE;

    if (HI_NULL != g_PdmGlobal.stBufInfo[i].u32VirAddr)
    {
        vunmap((HI_VOID *)(g_PdmGlobal.stBufInfo[i].u32VirAddr));

        g_PdmGlobal.stBufInfo[i].u32VirAddr = HI_NULL;
    }

    DRV_PDM_UNLOCK(&g_PdmGlobal.PdmMutex);

    //this function maybe block, can not lock
    pdm_free_reserve_mem(g_PdmGlobal.stBufInfo[i].u32PhyAddr, g_PdmGlobal.stBufInfo[i].u32Lenth);

    DRV_PDM_TagRemoveBuff(BufName);

    return HI_SUCCESS;
}

HI_S32 HI_DRV_PDM_GetDispParam(HI_UNF_DISP_E enDisp, HI_DISP_PARAM_S *pstDispParam)
{
    return DRV_PDM_GetDispParam(enDisp, pstDispParam);
}

HI_S32 HI_DRV_PDM_GetSoundParam(HI_UNF_SND_E enSound, HI_UNF_PDM_SOUND_PARAM_S * pstSoundParam)
{
    return DRV_PDM_GetSoundParam(enSound, pstSoundParam);
}

HI_S32 HI_DRV_PDM_GetSoundParamEx(HI_UNF_SND_E enSound, HI_UNF_PDM_SOUND_PARAM_S * pstSoundParam, HI_BOOL *pbVolumeExistInBase)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_NULL == pbVolumeExistInBase)
    {
        return HI_ERR_PDM_PTR_NULL;
    }

    s32Ret = DRV_PDM_GetSoundParam(enSound, pstSoundParam);

    *pbVolumeExistInBase = g_bVolumeExistInBase;

    return s32Ret;
}

HI_S32 HI_DRV_PDM_GetMceParam(HI_MCE_PARAM_S *pMceParam)
{
    return DRV_PDM_GetMceParam(pMceParam);
}

HI_S32 HI_DRV_PDM_GetMceData(HI_U32 u32Size, HI_U32 *pAddr)
{
    return DRV_PDM_GetMceData(u32Size, pAddr);
}

HI_S32 HI_DRV_PDM_ReleaseReserveMem(const HI_CHAR *BufName)
{
    return DRV_PDM_ReleaseReserveMem(BufName);
}

HI_S32 HI_DRV_PDM_GetData(const HI_CHAR *BufName, HI_U32 *pu32DataAddr, HI_U32 *pu32DataLen)
{
    return DRV_PDM_GetData(BufName, pu32DataAddr, pu32DataLen);
}
