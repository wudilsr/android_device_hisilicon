/**
 \file
 \brief subtitle transcode
 \copyright Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author l00167705
 \date 2013-9-16
 */
#include "hi_unf_version.h"
#if (UNF_VERSION_CODE == UNF_VERSION(3,0))
#include "hi_charset.h"
#include "hi_charset_common.h"
#include "hi_charset_norm.h"
#else
#include "hi_svr_charset.h"
#include "hi_svr_charset_common.h"
#include "hi_svr_charset_norm.h"
#endif

#include "subparse.h"

/***************************** Macro Definition ******************************/

#define INVALID_HANDLE (0xffffffff)

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/
static HI_HANDLE hTransCode = INVALID_HANDLE;

/******************************* API declaration *****************************/
HI_S32 sub_transcode_init()
{
    HI_S32 ret = HI_SUCCESS;

    if (hTransCode != INVALID_HANDLE) //already inited
    {
        return ret;
    }

    ret = HI_CHARSET_Init();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SUB("call HI_CHARSET_Init failed:%x\n", ret);
        return ret;
    }

    ret = HI_CHARSET_RegisterDynamic("libcharset.so");
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SUB("call HI_CHARSET_RegisterDynamic failed:%x\n", ret);
        HI_CHARSET_Deinit();
        return ret;
    }

    ret = g_stCharsetMgr_s.Create(&hTransCode, 0);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_SUB("call g_stCharsetMgr_s.Create failed:%x\n", ret);
        HI_CHARSET_Deinit();
        hTransCode = INVALID_HANDLE;
        return ret;
    }

    return ret;
}

HI_S32 sub_transcode_deinit()
{
    HI_S32 ret = HI_SUCCESS;

    ret = g_stCharsetMgr_s.Destroy(hTransCode);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SUB("call g_stCharsetMgr_s.Destroy failed:%x\n", ret);
    }

    ret = HI_CHARSET_Deinit();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SUB("call HI_CHARSET_Deinit failed:%x\n", ret);
    }

    hTransCode = INVALID_HANDLE;
    return ret;
}

HI_S32 sub_transcode_data(HI_U8* pu8DataIn, HI_U32 u32DataInLen, HI_U8* pu8Utf8DataOut,
                         HI_U32 u32DataOutBufferLen, HI_S32* ps32DataOutLen)
{
    HI_S32 ret;
    HI_S32 codetype;
    HI_S32 usedlen;

    if (hTransCode == INVALID_HANDLE)
    {
        HI_ERR_SUB("%s:init first.\n", __FUNCTION__);
        return HI_FAILURE;
    }

    if (!pu8DataIn || (u32DataInLen == 0) || !pu8Utf8DataOut || (u32DataOutBufferLen == 0) || !ps32DataOutLen)
    {
        HI_ERR_SUB("%s:invalid param check it.\n", __FUNCTION__);
        return HI_FAILURE;
    }

    ret = g_stCharsetMgr_s.IdentStream(hTransCode, pu8DataIn, u32DataInLen, 0, &codetype);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_SUB("%s:g_stCharsetMgr_s.IdentStream failed:%x.\n", __FUNCTION__, ret);
        return ret;
    }

    ret = g_stCharsetMgr_s.ConvStream(hTransCode, pu8Utf8DataOut, ps32DataOutLen, pu8DataIn, u32DataInLen, codetype,
                                      HI_CHARSET_CODETYPE_UTF8, &usedlen);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_SUB("%s:g_stCharsetMgr_s.IdentStream failed:%x.\n", __FUNCTION__, ret);
        return ret;
    }

    return HI_SUCCESS;
}
