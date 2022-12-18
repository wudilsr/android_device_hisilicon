/*******************************************************************************
 *             Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: test_loader.c
 * Description:
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 * main1
 ******************************************************************************/

//#include <stdlib.h>
//#include <stdio.h>
//#include <malloc.h>
//#include <string.h>
//#include <unistd.h>
#include <hi_go_bliter.h>
#include "hi_type.h"
#include "upgrd_common.h"
#include "hi_loader_info.h"
#include "hi_go_surface.h"

#include "hi_go_gdev.h"

//#include "hi_go_encoder.h"
#include "hi_flash.h"
#include "upgrd_osd.h"
#include "loaderdb_info.h"
#ifdef HI_LOADER_APPLOADER
 #include "hi_go_text.h"
 #include "hi_unf_common.h"
 #include "hi_adp_osd.h"
#else
 #include "hi_unf_disp.h"
 #include "upgrd_text.h"
#endif

/*******************************************************************************/
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#define WINDOW_START_X 150
#define WINDOW_START_Y 150
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300

/*for history reason, define default width as 720, define default height as 576*/
#define DEFAULT_WIDTH (720)
#define DEFAULT_HEIGTT (576)

#ifdef HI_LOADER_APPLOADER
static const HI_CHAR *pCHN_Str[] =
{
    //0-4
    UPGRD_L_CN_MAN_UPGRD,
    UPGRD_L_CN_PROMPT_UPGRD_PWD1,
    UPGRD_L_CN_PROMPT_UPGRD_PWD2,
    UPGRD_L_CN_INPUT_PWD,
    UPGRD_L_CN_PROMPT_NOT_OP1,

    //5-9
    UPGRD_L_CN_PROMPT_NOT_OP2,
    UPGRD_L_CN_PROMPT_NOT_OP3,
    UPGRD_L_CN_BUTTON_CONFIRM,
    UPGRD_L_CN_BUTTON_CANCLE,
    UPGRD_L_CN_PROMPT_OPRTN,

    //10-14
    UPGRD_L_CN_TITLE_FREQ,
    UPGRD_L_CN_TITLE_SYM_RATE,
    UPGRD_L_CN_TITLE_MODULATE,
    UPGRD_L_CN_TITLE_PID,
    UPGRD_L_CN_TITLE_AUTO,

    //15-19
    UPGRD_L_CN_BUTTON_START,
    UPGRD_L_CN_TRANS_YES,
    UPGRD_L_CN_TRANS_NO,
    UPGRD_L_CN_TRANS_EXIT,
    UPGRD_L_CN_PROMPT_POWER1,

    //20-24
    UPGRD_L_CN_PROMPT_POWER2,
    UPGRD_L_CN_PROMPT_SEARCH,
    UPGRD_L_CN_NT_CUR_PRGRSS,
    UPGRD_L_CN_NT_TTL_PRGRSS,
    UPGRD_L_CN_PT_UPGRADING,

    //25-29
    UPGRD_L_CN_FAIL_SIG_EXPT,
    UPGRD_L_CN_FAIL_FACTORY,
    UPGRD_L_CN_FAIL_HARD_VER,
    UPGRD_L_CN_FAIL_SOFT_VER,
    UPGRD_L_CN_FAIL_SN_DISMATCH,

    //30-34
    UPGRD_L_CN_FAIL_FILE_RNG,
    UPGRD_L_CN_FAIL_CRC,
    UPGRD_L_CN_FAIL_DOWNLOAD_TIMEOUT,
    UPGRD_L_CN_FAIL_DOWNLOAD,
    UPGRD_L_CN_FAIL_DATA,

    //35-39
    UPGRD_L_CN_FAIL_FREQUENCY,
    UPGRD_L_CN_FAIL_SYMBOL,
    UPGRD_L_CN_FAIL_PID,
    UPGRD_L_CN_FAIL_MODUL,
    UPGRD_L_CN_PT_DOWNLOADING,

    //40-44
    UPGRD_L_CN_PT_WRITING,
    UPGRD_L_CN_PT_SUCC,
    UPGRD_L_CN_IP_NOT_FIND_FILE,
    UPGRD_L_CN_SET_IP_ERR,
    UPGRD_L_CN_FAIL_NET_EXPT,

    //45-49
    UPGRD_L_CN_FAIL_NET_TIMEOUT,
    UPGRD_L_CN_FAIL_NO_RESP,
    UPGRD_L_CN_FAIL_FILE_LEN,
    UPGRD_L_CN_DWNLD_WTING,
    UPGRD_L_CN_FAIL_UPGRD,

    //50-54
    UPGRD_L_CN_DWNLD_PROGRESS,
    UPGRD_L_CN_BURN_PROGRESS,
    UPGRD_L_CN_UPGRADING,
    UPGRD_L_CN_NOT_FIND_USB_FILE,
    UPGRD_L_CN_REBOOT,

    //55-60
	UPGRD_L_CN_FACTORY_NOTICE,
	UPGRD_L_CN_FACTORY_SUCCESS,
	UPGRD_L_CN_FACTORY_FAILED,
    UPGRD_L_CN_WARNING,
    UPGRD_L_CN_INFO
};
#endif

static const HI_CHAR*pENG_Str[] =
{
    //0-4
    UPGRD_L_EN_MAN_UPGRD,
    UPGRD_L_EN_PROMPT_UPGRD_PWD1,
    UPGRD_L_EN_PROMPT_UPGRD_PWD2,
    UPGRD_L_EN_INPUT_PWD,
    UPGRD_L_EN_PROMPT_NOT_OP1,

    //5-9
    UPGRD_L_EN_PROMPT_NOT_OP2,
    UPGRD_L_EN_PROMPT_NOT_OP3,
    UPGRD_L_EN_BUTTON_CONFIRM,
    UPGRD_L_EN_BUTTON_CANCLE,
    UPGRD_L_EN_PROMPT_OPRTN,

    //10-14
    UPGRD_L_EN_TITLE_FREQ,
    UPGRD_L_EN_TITLE_SYM_RATE,
    UPGRD_L_EN_TITLE_MODULATE,
    UPGRD_L_EN_TITLE_PID,
    UPGRD_L_EN_TITLE_AUTO,

    //15-19
    UPGRD_L_EN_BUTTON_START,
    UPGRD_L_EN_TRANS_YES,
    UPGRD_L_EN_TRANS_NO,
    UPGRD_L_EN_TRANS_EXIT,
    UPGRD_L_EN_PROMPT_POWER1,

    //20-24
    UPGRD_L_EN_PROMPT_POWER2,
    UPGRD_L_EN_PROMPT_SEARCH,
    UPGRD_L_EN_NT_CUR_PRGRSS,
    UPGRD_L_EN_NT_TTL_PRGRSS,
    UPGRD_L_EN_PT_UPGRADING,

    //25-29
    UPGRD_L_EN_FAIL_SIG_EXPT,
    UPGRD_L_EN_FAIL_FACTORY,
    UPGRD_L_EN_FAIL_HARD_VER,
    UPGRD_L_EN_FAIL_SOFT_VER,
    UPGRD_L_EN_FAIL_SN_DISMATCH,

    //30-34
    UPGRD_L_EN_FAIL_FILE_RNG,
    UPGRD_L_EN_FAIL_CRC,
    UPGRD_L_EN_FAIL_DOWNLOAD_TIMEOUT,
    UPGRD_L_EN_FAIL_DOWNLOAD,
    UPGRD_L_EN_FAIL_DATA,

    //35-39
    UPGRD_L_EN_FAIL_FREQUENCY,
    UPGRD_L_EN_FAIL_SYMBOL,
    UPGRD_L_EN_FAIL_PID,
    UPGRD_L_EN_FAIL_MODUL,
    UPGRD_L_EN_PT_DOWNLOADING,

    //40-44
    UPGRD_L_EN_PT_WRITING,
    UPGRD_L_EN_PT_SUCC,
    UPGRD_L_EN_IP_NOT_FIND_FILE,
    UPGRD_L_EN_SET_IP_ERR,
    UPGRD_L_EN_FAIL_NET_EXPT,

    //45-49
    UPGRD_L_EN_FAIL_NET_TIMEOUT,
    UPGRD_L_EN_FAIL_NO_RESP,
    UPGRD_L_EN_FAIL_FILE_LEN,
    UPGRD_L_EN_DWNLD_WTING,
    UPGRD_L_EN_FAIL_UPGRD,

    //50-54
    UPGRD_L_EN_DWNLD_PROGRESS,
    UPGRD_L_EN_BURN_PROGRESS,
    UPGRD_L_EN_UPGRADING,
    UPGRD_L_EN_NOT_FIND_USB_FILE,
    UPGRD_L_EN_REBOOT,

    //55-60
	UPGRD_L_EN_FACTORY_NOTICE,
	UPGRD_L_EN_FACTORY_SUCCESS,
	UPGRD_L_EN_FACTORY_FAILED,
    UPGRD_L_EN_WARNING,
    UPGRD_L_EN_INFO
};

#ifdef HI_LOADER_BOOTLOADER
extern HI_S32 PRODUCT_DisplayInit(HI_HANDLE *phLayer, HI_HANDLE *phSurface);
#endif

static HI_HANDLE hLayer, hLayerSurface, hFont = 0;
static HI_HANDLE hMemSurface;
static HIGO_PF_E szPixelFormat = HIGO_PF_8888;

static HI_LOADER_UI_LANG_E g_enLanguage = HI_LOADER_UI_LANG_EN;

static HI_U32 g_u32GuageWin = 0;

/*--------------------------------*
*Role: reconstruction of the current window picture window owned by the members of the type and focus of state
*Input: MembHandle - members of the handle
*output: N/A
*return: success(0) or fail(-1)
*--------------------------------*/
static HI_S32        WIN_BuildWindPic(HI_U32 WindHandle);

/* function */

HI_U32 WIN_CreateWind(sPositionXY WindPos, HI_S32 Length, HI_S32 Width, eWindType WindType)
{
	sWindow *pWind = HI_NULL;
	HI_S32 ret;

	/*clear last window*/
	Drv_OSDClear();

	ret = HI_GO_CreateSurface(Length, Width, szPixelFormat, &hMemSurface);
	if (HI_SUCCESS != ret)
	{
		HI_ERR_LOADER("%s->%d\n", __FUNCTION__, __LINE__);
		return HI_INVALID_HANDLE;
	}

	/* mem alloc for window struct and window pic */
	pWind = (sWindow *)malloc(sizeof(sWindow));
	if (HI_NULL == pWind)
	{
		HI_ERR_LOADER("wind create fail!\n");
		return HI_INVALID_HANDLE;
	}

	memset((HI_U8 *)pWind, 0, sizeof(sWindow));

	/* init window struct */
	pWind->hWindHandle = (HI_U32)pWind;
	pWind->WindType    = WindType;
	pWind->WindPos.x   = WindPos.x;
	pWind->WindPos.y   = WindPos.y;
	pWind->WindLength  = Length;
	pWind->WindWidth   = Width;
	pWind->hMemSurface = hMemSurface;
	pWind->FocusPos.x  = 0;
	pWind->FocusPos.y  = 0;
	pWind->pMemberList = HI_NULL;

	/** Draw a rectangle in the memory Surface */
	ret = HI_GO_FillRect(hMemSurface, NULL, BLUE_COLOR, HIGO_COMPOPT_NONE);
	if (HI_SUCCESS != ret)
	{
		free(pWind);
		HI_GO_FreeSurface(hMemSurface);
		return HI_INVALID_HANDLE;
	}

	return (pWind->hWindHandle);
}

static HI_S32 WIN_PasteWind(HI_U32 WindHandle, HI_HANDLE hSurface)
{
    sWindow *pWind = HI_NULL;
    HI_S32 ret;
    HI_RECT rc = {0};
    HIGO_BLTOPT_S stBltOpt;
    HI_S32 s32Width, s32Height;

    if (0 == WindHandle)
    {
        HI_ERR_LOADER("window handle or pRegion invalid!\n");
        return HI_FAILURE;
    }

	memset(&stBltOpt, 0, sizeof(stBltOpt));
    pWind = (sWindow *)WindHandle;
#if 0
    rc.x = pWind->WindPos.x;
    rc.y = pWind->WindPos.y;
    rc.w = pWind->WindLength;
    rc.h = pWind->WindWidth;

#else
    if (HI_SUCCESS != HI_GO_GetSurfaceSize(hSurface, &s32Width, &s32Height))
    {
        s32Width  = 1280;
        s32Height = 720;
    }

    rc.x = pWind->WindPos.x * s32Width / DEFAULT_WIDTH;
    rc.y = pWind->WindPos.y * s32Height / DEFAULT_HEIGTT;
    rc.w = pWind->WindLength * s32Width / DEFAULT_WIDTH;
    rc.h = pWind->WindWidth * s32Height / DEFAULT_HEIGTT;
    stBltOpt.EnableScale = HI_TRUE;
#endif

    ret = HI_GO_Blit(pWind->hMemSurface, NULL, hSurface, &rc, &stBltOpt);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("HI_GO_Blit failure!");
        return ret;
    }

#if 0
    rc.x = pWind->WindPos.x - APP_WIND_BWIDTH;
    rc.y = pWind->WindPos.y - APP_WIND_BWIDTH;
    rc.w = pWind->WindLength + APP_WIND_BWIDTH * 2;
    rc.h = APP_WIND_BWIDTH;
    ret = HI_GO_FillRect(hSurface, &rc, APP_WIND_LCOLOR, HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    rc.x = pWind->WindPos.x - APP_WIND_BWIDTH;
    rc.y = pWind->WindPos.y + pWind->WindWidth;
    rc.w = pWind->WindLength + APP_WIND_BWIDTH * 2;
    rc.h = APP_WIND_BWIDTH;
    ret = HI_GO_FillRect(hSurface, &rc, APP_WIND_LCOLOR, HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    rc.x = pWind->WindPos.x - APP_WIND_BWIDTH;
    rc.y = pWind->WindPos.y - APP_WIND_BWIDTH;
    rc.w = APP_WIND_BWIDTH;
    rc.h = pWind->WindWidth;
    ret = HI_GO_FillRect(hSurface, &rc, APP_WIND_LCOLOR, HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    rc.x = pWind->WindPos.x + pWind->WindLength;
    rc.y = pWind->WindPos.y - APP_WIND_BWIDTH;
    rc.w = APP_WIND_BWIDTH;
    rc.h = pWind->WindWidth;

    ret = HI_GO_FillRect(hSurface, &rc, APP_WIND_LCOLOR, HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }
#endif

    return HI_SUCCESS;
}

HI_U32 WIN_CreateWindMember(HI_U32 WindHandle, eWMembType MembType,
                            sPositionXY MembPos, const HI_CHAR *pDefString, HI_U8 MaxLength)
{
    sWindMember *pMemb = HI_NULL;
    sWindMember *pMembTmp = HI_NULL;
    sWindow *pWind = (sWindow *)WindHandle;
    HI_CHAR *pStr = HI_NULL;

    /*params check*/
    if ((0 == WindHandle) || (HI_NULL == pDefString) || (0 == MaxLength))
    {
        HI_ERR_LOADER("input params invalid!\n");
        return (HI_U32)HI_NULL;
    }

    /* member position check */
    if ((MembPos.x > pWind->WindLength) || (MembPos.y > pWind->WindWidth))
    {
        HI_ERR_LOADER("input position params invalid!\n");
        return (HI_U32)HI_NULL;
    }

    /* alloc struct and input string mem */
    pMemb = (sWindMember *)malloc(sizeof(sWindMember));
    if (HI_NULL == pMemb)
    {
        HI_ERR_LOADER("mem alloc fail!\n");
        return (HI_U32)HI_NULL;
    }

    pStr = (HI_CHAR *)malloc(sizeof(HI_U8) * (MaxLength + 1));  // +1 for \0
    if (HI_NULL == pStr)
    {
        free(pMemb);
        HI_ERR_LOADER("mem alloc fail!\n");
        return (HI_U32)HI_NULL;
    }

    memset((HI_U8 *)pMemb, 0, sizeof(sWindMember));
    memset((HI_U8 *)pStr, 0, sizeof(HI_U8) * (MaxLength + 1));

    /* init struct according to member type */
    pMemb->hMembHandle = (HI_U32)pMemb;
    pMemb->MembType = MembType;
    if (HI_NULL == pWind->pMemberList) /* The first control */
    {
        pMemb->IsOnFocus = HI_TRUE;

        /* set window focus to this member */
        pWind->FocusPos.x = MembPos.x;
        pWind->FocusPos.y = MembPos.y;
    }
    else
    {
        pMemb->IsOnFocus = HI_FALSE;
    }

    pMemb->MembPos.x = MembPos.x;
    pMemb->MembPos.y = MembPos.y;
    pMemb->pNext = HI_NULL;

    memcpy(pStr, pDefString, MaxLength);
    pMemb->pDefString = pStr;
    if (APP_WMEMB_BUTTOM == MembType)
    {
        pMemb->TotalLen = MaxLength;
        pMemb->SubFocusIndex = 0;
    }
    else if (APP_WMEMB_PASSWD == MembType)
    {
        pMemb->TotalLen = MaxLength;
        pMemb->SubFocusIndex = 0;
        pMemb->QamNumber = QAM64;
        pMemb->bAuto = HI_FALSE;
        pMemb->IsOnEdit = HI_TRUE;
    }
    else
    {
        pMemb->TotalLen = MaxLength;
        pMemb->SubFocusIndex = (MaxLength - 1);
        pMemb->QamNumber = QAM64;
        pMemb->bAuto = HI_FALSE;
    }

    /* add to window member list */
    pMembTmp = pWind->pMemberList;
    if (HI_NULL == pMembTmp)  /* the first window member */
    {
        pWind->pMemberList = pMemb;
    }
    else
    {
        while (1)
        {
            if (HI_NULL == pMembTmp->pNext)
            {
                pMembTmp->pNext = pMemb;

                break;
            }

            pMembTmp = pMembTmp->pNext;
        }
    }

    return (pMemb->hMembHandle);
}

static HI_S32 WIN_BuildWindPic(HI_U32 WindHandle)
{
    sWindow *pWind = (sWindow *)WindHandle;
    sWindMember *pMembTmp = pWind->pMemberList;
    HI_S32 ret;
    HI_RECT rc = {0};

    if (0 == WindHandle)
    {
        HI_ERR_LOADER("invalid window handle!\n");
        return HI_FAILURE;
    }

    while (HI_NULL != pMembTmp)
    {
        if ((APP_WMEMB_BUTTOM == pMembTmp->MembType)
            || (APP_WMEMB_TRANS == pMembTmp->MembType)
            || (APP_WMEMB_TRANS_2 == pMembTmp->MembType))
        {
            if (HI_TRUE == pMembTmp->IsOnFocus)
            {
                HI_GO_SetTextColor(hFont, APP_TXT_FONTCOLOR_F);
                HI_GO_SetTextBGColor(hFont, APP_TXT_BGCOLOR_F);
            }
            else
            {
                HI_GO_SetTextColor(hFont, APP_TXT_FONTCOLOR);
                HI_GO_SetTextBGColor(hFont, APP_TXT_BGCOLOR);
            }

            rc.x = pMembTmp->MembPos.x;
            rc.y = pMembTmp->MembPos.y;
#if 1
            rc.w = 12 * pMembTmp->TotalLen;
            rc.h = GRPH_FONT_SIZE;

            ret = HI_GO_FillRect(pWind->hMemSurface, &rc, YELLOW_COLOR, HIGO_COMPOPT_NONE);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_LOADER("failed to HI_GO_FillRect\n");
                return HI_FAILURE;
            }
#endif

            ret = HI_GO_GetTextExtent(hFont, pMembTmp->pDefString, &rc.w, &rc.h);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_LOADER("failed to HI_GO_GetTextExtent\n");
                return HI_FAILURE;
            }

            ret = HI_GO_TextOut(hFont, pWind->hMemSurface, pMembTmp->pDefString, &rc);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_LOADER("failed to HI_GO_TextOut\n");
                return HI_FAILURE;
            }
        }

        if (APP_WMEMB_INPUT == pMembTmp->MembType)
        {
            if (HI_TRUE == pMembTmp->IsOnFocus)
            {
                HI_GO_SetTextColor(hFont, APP_TXT_FONTCOLOR_F);
                HI_GO_SetTextBGColor(hFont, APP_TXT_BGCOLOR_F);
            }
            else
            {
                HI_GO_SetTextColor(hFont, APP_TXT_FONTCOLOR);
                HI_GO_SetTextBGColor(hFont, APP_TXT_BGCOLOR);
            }

            rc.x = pMembTmp->MembPos.x;
            rc.y = pMembTmp->MembPos.y;
#if 1
            rc.w = 16 * pMembTmp->TotalLen;
            rc.h = GRPH_FONT_SIZE;

            ret = HI_GO_FillRect(pWind->hMemSurface, &rc, YELLOW_COLOR, HIGO_COMPOPT_NONE);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_LOADER("failed to HI_GO_FillRect\n");
                return HI_FAILURE;
            }
#endif
            ret = HI_GO_GetTextExtent(hFont, pMembTmp->pDefString, &rc.w, &rc.h);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_LOADER("failed to HI_GO_GetTextExtent\n");
                return HI_FAILURE;
            }

            ret = HI_GO_TextOut(hFont, pWind->hMemSurface, pMembTmp->pDefString, &rc);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_LOADER("failed to HI_GO_TextOut\n");
                return HI_FAILURE;
            }

#if 1
            if (HI_TRUE == pMembTmp->IsOnEdit)
            {
                /* add cursor */
                rc.x = pMembTmp->MembPos.x + pMembTmp->SubFocusIndex * 11;
                rc.y = pMembTmp->MembPos.y + 22;
                rc.w = 10;
                rc.h = 2;
                ret = HI_GO_FillRect(pWind->hMemSurface, &rc, 0xFF888888, HIGO_COMPOPT_NONE);
                if (HI_SUCCESS != ret)
                {
                    HI_ERR_LOADER("failed to HI_GO_FillRect\n");
                    return HI_FAILURE;
                }
            }
#endif

        }

        if (APP_WMEMB_PASSWD == pMembTmp->MembType)
        {
            if (HI_TRUE == pMembTmp->IsOnFocus)
            {
                HI_GO_SetTextColor(hFont, APP_TXT_FONTCOLOR_F);
                HI_GO_SetTextBGColor(hFont, APP_TXT_BGCOLOR_F);
            }
            else
            {
                HI_GO_SetTextColor(hFont, APP_TXT_FONTCOLOR);
                HI_GO_SetTextBGColor(hFont, APP_TXT_BGCOLOR);
            }

            rc.x = pMembTmp->MembPos.x;
            rc.y = pMembTmp->MembPos.y;
#if 1
            rc.w = 16 * pMembTmp->TotalLen;
            rc.h = GRPH_FONT_SIZE;

            ret = HI_GO_FillRect(pWind->hMemSurface, &rc, YELLOW_COLOR, HIGO_COMPOPT_NONE);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_LOADER("failed to HI_GO_FillRect\n");
                return HI_FAILURE;
            }
#endif


            ret = HI_GO_GetTextExtent(hFont, pMembTmp->pDefString, &rc.w, &rc.h);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_LOADER("failed to HI_GO_GetTextExtent\n");
                return HI_FAILURE;
            }

            ret = HI_GO_TextOut(hFont, pWind->hMemSurface, pMembTmp->pDefString, &rc);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_LOADER("failed to HI_GO_TextOut\n");
                return HI_FAILURE;
            }

#if 1
            if (HI_TRUE == pMembTmp->IsOnEdit)
            {
                /* add cursor */
                rc.x = pMembTmp->MembPos.x + pMembTmp->SubFocusIndex * 11 + pMembTmp->SubFocusIndex / 3;
                rc.y = pMembTmp->MembPos.y + 22;
                rc.w = 10;
                rc.h = 2;
                ret = HI_GO_FillRect(pWind->hMemSurface, &rc, 0xFF888888, HIGO_COMPOPT_NONE);
                if (HI_SUCCESS != ret)
                {
                    HI_ERR_LOADER("failed to HI_GO_FillRect\n");
                    return HI_FAILURE;
                }
            }
#endif

        }

        pMembTmp = pMembTmp->pNext;
    }

    return HI_SUCCESS;
}

HI_S32 WIN_BuildAndPasteWind(HI_U32 WindHandle)
{
    HI_S32 ret = 0;

    ret = WIN_BuildWindPic(WindHandle);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("WIN_BuildWindPic fail!\n");
        return HI_FAILURE;
    }

    ret = WIN_PasteWind(WindHandle, hLayerSurface);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("WIN_PasteWind fail!\n");
        return HI_FAILURE;
    }

    return ret;
}

HI_S32 WIN_ShowWind(HI_U32 WindHandle)
{
    HI_S32 ret = 0;

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("HI_GO_RefreshLayer\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 WIN_DestroyWind(HI_U32 hWind)
{
    sWindow *pWindTemp = HI_NULL;
    sWindMember *pWinMemTemp  = HI_NULL;
    sWindMember *pWinMemTemp2 = HI_NULL;

    if (HI_NULL == hWind)
    {
        HI_ERR_LOADER("Invalid Parameter!");
        return HI_FAILURE;
    }

    pWindTemp   = (sWindow *)hWind;
    pWinMemTemp = pWindTemp->pMemberList;

    while (HI_NULL != pWinMemTemp)
    {
        free(pWinMemTemp->pDefString);
        pWinMemTemp2 = pWinMemTemp;
        pWinMemTemp = pWinMemTemp->pNext;

        free(pWinMemTemp2);
    }

    if (HI_NULL != pWindTemp->hMemSurface)
    {
        if (HI_SUCCESS != HI_GO_FreeSurface(pWindTemp->hMemSurface))
        {
            HI_ERR_LOADER("Free Surface failure!");
        }
    }

    free(pWindTemp);

    return HI_SUCCESS;
}

#ifdef HI_LOADER_APPLOADER
HI_S32 LOADER_OSD_Init(HI_VOID)
{
	HI_S32 ret = HI_FAILURE;

	ret = Disp_Graphic_Init(&hLayer, &hLayerSurface);
	if (HI_SUCCESS != ret)
	{
		HI_ERR_LOADER("Disp_Graphic_Init failed!\n");
		return HI_FAILURE;
	}

	ret = HI_GO_FillRect(hLayerSurface, NULL, BACK_COLOR, HIGO_COMPOPT_NONE);
	if (HI_SUCCESS != ret)
	{
		HI_ERR_LOADER("HI_GO_FillRect failed!\n");
		HI_GO_DestroyLayer(hLayer);
		HI_GO_Deinit();
		return HI_FAILURE;
	}

	ret = HI_GO_RefreshLayer(hLayer, NULL);
	if (HI_SUCCESS != ret)
	{
		HI_ERR_LOADER("++++ HI_GO_RefreshLayer failed! hLayerSurface %d ret 0x%x\n", hLayerSurface, ret);
		HI_GO_DestroyLayer(hLayer);
		HI_GO_Deinit();
		return HI_FAILURE;
	}

	ret = HI_GO_CreateText("./res/DroidSansFallbackLegacy.ttf", NULL,  &hFont);

	if (HI_SUCCESS != ret)
	{
		HI_ERR_LOADER("HI_GO_CreateText failed!ret = 0x%x\n", ret);
		HI_GO_DestroyLayer(hLayer);
		HI_GO_Deinit();
		return HI_FAILURE;
	}

	g_enLanguage = LOADER_GetLanguage();

	return HI_SUCCESS;
}

#else
extern HI_S32 PRODUCT_DisplayInit(HI_HANDLE *phLayer, HI_HANDLE *phSurface);

HI_S32 LOADER_OSD_Init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    HI_DBG_LOADER("LOADER_OSD_Init!\n");

    ret = PRODUCT_DisplayInit(&hLayer, &hLayerSurface);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("PRODUCT_DisplayInit failed!\n");
        return HI_FAILURE;
    }

    ret = HI_GO_FillRect(hLayerSurface, NULL, BACK_COLOR, HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("HI_GO_FillRect failed!\n");

        return HI_FAILURE;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("++++ HI_GO_RefreshLayer failed! hLayerSurface %d ret 0x%x\n", hLayerSurface, ret);

        return HI_FAILURE;
    }

    g_enLanguage = LOADER_GetLanguage();

    return HI_SUCCESS;
}

#endif

static HI_S32 Drv_OSDFillRect(HI_U32 window, HI_S32 StartX, HI_S32 StartY,
                              HI_S32 height, HI_S32 width, HI_U32 color)
{
    HI_S32 ret;
    HI_RECT rect = {0};

    sWindow *pWind = HI_NULL;

    if (0 == window)
    {
        HI_ERR_LOADER("window handle or pRegion invalid!\n");
        return HI_FAILURE;
    }

    pWind = (sWindow *)window;

    if ((StartX > APPOSD_MAX_WIDTH_PAL)
        || (StartY > APPOSD_MAX_HEIGHT_PAL)
        || ((StartY + height) > APPOSD_MAX_HEIGHT_PAL)
        || ((StartX + width) > APPOSD_MAX_WIDTH_PAL))
    {
        HI_ERR_LOADER("[DRV]OSD input Rect params invalid!\n");
        return HI_FAILURE;
    }

    rect.x = StartX;
    rect.y = StartY;
    rect.h = height;
    rect.w = width;
    ret = HI_GO_FillRect(pWind->hMemSurface, &rect, color, HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("Drv_OSDFillRect:HI_GO_FillRect failed! rect (%d %d %d %d)\n", rect.x, rect.y, rect.w, rect.h);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_VOID Drv_RectShowText(HI_U32 window, const HI_CHAR *CharBuffer, HI_S32 StartX, HI_S32 StartY)
{
    HI_S32 ret = 0;
    HI_U32 u32len = 0;
    HI_RECT rc = {0};
    sWindow *pWind = HI_NULL;

    if (0 == window)
    {
        HI_ERR_LOADER("window handle or pRegion invalid!\n");
        return;
    }

    pWind = (sWindow *)window;

    rc.x = StartX;
    rc.y = StartY;

    ret = HI_GO_GetTextExtent(hFont, CharBuffer, &rc.w, &rc.h);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("failed to HI_GO_GetTextExtent line %d \n", __LINE__);
        return;
    }

#if 1
    u32len = strlen(CharBuffer);
    if (u32len < 5)
    {
        rc.w = 16 * 5;
    }
    else
    {
        rc.w = 16 * 15;
    }

    ret = HI_GO_FillRect(pWind->hMemSurface, &rc, BLUE_COLOR, HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("failed to HI_GO_FillRect\n");
        return;
    }
#endif


    ret = HI_GO_TextOut(hFont, pWind->hMemSurface, CharBuffer, &rc);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("failed to HI_GO_TextOut line %d  ret=%x\n", __LINE__, ret);
        return;
    }
	
    return;
}

HI_VOID Drv_UpdateIndictorText(LOADER_Content_E enContent)
{
	const HI_CHAR *pCharBuffer = NULL;

#ifdef HI_ADVCA_FUNCTION_RELEASE
	if (LOADER_CONTENT_PT_SUCC != enContent)
	{
		return;
	}
#endif

	pCharBuffer = LoaderOSDGetText(enContent);

	if (HI_NULL != pCharBuffer)
	{
		Drv_RectShowText(g_u32GuageWin, pCharBuffer, 70, 70);
		if (HI_SUCCESS != WIN_PasteWind(g_u32GuageWin, hLayerSurface))
		{
			HI_ERR_LOADER("paste window failed. \n");
		}
		
		if( HI_SUCCESS != HI_GO_RefreshLayer(hLayer, NULL))
		{
			HI_ERR_LOADER("fresh layer failed.\n");
		}
	}

	return;
}

HI_S32 Drv_CreatGuageWin(HI_VOID)
{
    HI_U32 testWind = 0;
    HI_S32 ret = HI_FAILURE;
    sPositionXY Pos = {0};

    Pos.x = WINDOW_START_X; //150;//
    Pos.y = WINDOW_START_Y; //150;//

    testWind = WIN_CreateWind(Pos, WINDOW_WIDTH, WINDOW_HEIGHT, APP_WIND_NOTES);
    g_u32GuageWin = testWind;
    ret = Drv_ShowText(testWind, LOADER_CONTENT_PROMPT_POWER1, 10, 5, APP_WIN_TXT_COLOR);
    ret = Drv_ShowText(testWind, LOADER_CONTENT_PROMPT_POWER2, 10, 30, APP_WIN_TXT_COLOR);

#ifndef HI_ADVCA_FUNCTION_RELEASE
    ret += Drv_ShowText(testWind, LOADER_CONTENT_DWNLD_PROGRESS, 20, 180, APP_WIN_TXT_COLOR);
    ret += Drv_ShowText(testWind, LOADER_CONTENT_BURN_PROGRESS, 20, 260, APP_WIN_TXT_COLOR);
#endif

    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("Win fill rect fail!\n");
        return HI_FAILURE;
    }

    ret = WIN_BuildWindPic(testWind);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("WIN_BuildWindPic fail!\n");
        return HI_FAILURE;
    }

    ret = WIN_PasteWind(testWind, hLayerSurface);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("WIN_PasteWind fail! ret = %d\n", ret);
        return HI_FAILURE;
    }

    ret = WIN_ShowWind(testWind);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("WIN_ShowWind fail!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 Drv_DestroyGuageWin(HI_VOID)
{
    return WIN_DestroyWind(g_u32GuageWin);
}

HI_S32 Drv_ShowDoubleGuage(HI_U32 u32Percent1, HI_U32 u32Percent2)
{
#ifndef HI_ADVCA_FUNCTION_RELEASE
	HI_S32 ret = HI_FAILURE;
	HI_CHAR CharBuffer1[10] = {0};
	HI_CHAR CharBuffer2[10] = {0};

	if ((u32Percent1 > 100) || (u32Percent2 > 100))
		return HI_FAILURE;

	if (0 == u32Percent1)
	{
		ret = Drv_OSDFillRect(g_u32GuageWin, 20, 150, 20, 300, APP_PROGREE_BGCOLOR);
		if (HI_SUCCESS != ret)
		{
			HI_ERR_LOADER("u32Percent1 : Drv_OSDFillRect fail!\n");
			return HI_FAILURE;
		}
	}

	if (0 == u32Percent2)
	{
		ret = Drv_OSDFillRect(g_u32GuageWin, 20, 230, 20, 300, APP_PROGREE_BGCOLOR);
		if (HI_SUCCESS != ret)
		{
			HI_ERR_LOADER("u32Percent2 : Drv_OSDFillRect fail!\n");
			return HI_FAILURE;
		}
	}

	if (u32Percent1 != 0)
	{
		ret = Drv_OSDFillRect(g_u32GuageWin, 20, 150, 20, u32Percent1 * 3, 0xFFFFFF00);
		if (HI_SUCCESS != ret)
		{
			HI_ERR_LOADER("u32Percent1*3 : Drv_WinFillRect fail! ret 0x%x\n", ret);
			return HI_FAILURE;
		}
	}

	if (u32Percent2 != 0)
	{
		ret = Drv_OSDFillRect(g_u32GuageWin, 20, 230, 20, u32Percent2 * 3, 0xFFFFFF00);
		if (HI_SUCCESS != ret)
		{
			HI_ERR_LOADER("u32Percent2*3 : Drv_WinFillRect fail!\n");
			return HI_FAILURE;
		}
	}

	HI_OSAL_Snprintf(CharBuffer1, sizeof(CharBuffer1), "%3d%%", u32Percent1);
	HI_OSAL_Snprintf(CharBuffer2, sizeof(CharBuffer2), "%3d%%", u32Percent2);

	Drv_RectShowText(g_u32GuageWin, CharBuffer1, 330, 150);
	Drv_RectShowText(g_u32GuageWin, CharBuffer2, 330, 230);

	ret = WIN_PasteWind(g_u32GuageWin, hLayerSurface);
	if (HI_SUCCESS != ret)
	{
		HI_ERR_LOADER("WIN_PasteWind fail\n");
		return HI_FAILURE;
	}

	ret = HI_GO_RefreshLayer(hLayer, NULL);
	if (HI_SUCCESS != ret)
	{
		HI_ERR_LOADER("HI_GO_RefreshLayer\n");
		return HI_FAILURE;
	}
#endif
	return HI_SUCCESS;
}

HI_VOID Drv_OSDClear(HI_VOID)
{
	if (HI_SUCCESS != HI_GO_FillRect(hLayerSurface, NULL, BACK_COLOR, HIGO_COMPOPT_NONE))
	{
		HI_ERR_LOADER("higo fill rect failed.\n");
	}
}

HI_S32 Drv_ShowText(HI_U32 WindHandle, LOADER_Content_E enContent, HI_S32 StartX, HI_S32 StartY, HI_U32 FontColor)
{
    HI_S32 ret = HI_FAILURE;
    HI_RECT rc = {0};
    sWindow *pWind = (sWindow *)WindHandle;
    const HI_CHAR *pCharBuffer = HI_NULL;

    pCharBuffer = LoaderOSDGetText(enContent);

    if ((0 == WindHandle) || (HI_NULL == pCharBuffer))
    {
        HI_ERR_LOADER("input parameter invalid!\n");
        return HI_FAILURE;
    }

    ret = HI_GO_SetTextColor(hFont, FontColor);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("failed to HI_GO_SetTextColor\n");
        return HI_FAILURE;
    }

    rc.x = StartX;
    rc.y = StartY;
    ret = HI_GO_GetTextExtent(hFont, pCharBuffer, &rc.w, &rc.h);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("failed to HI_GO_GetTextExtent\n");
        return HI_FAILURE;
    }

    ret = HI_GO_TextOut(hFont, pWind->hMemSurface, pCharBuffer, &rc);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("failed to HI_GO_TextOut\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 Drv_ShowTextEx(HI_U32 WindHandle, const HI_CHAR *pCharBuffer, HI_S32 StartX, HI_S32 StartY, HI_U32 FontColor)
{
    HI_S32 ret = HI_FAILURE;
    HI_RECT rc = {0};
    sWindow *pWind = (sWindow *)WindHandle;

    if ((0 == WindHandle) || (HI_NULL == pCharBuffer))
    {
        HI_ERR_LOADER("input parameter invalid!\n");
        return HI_FAILURE;
    }

    ret = HI_GO_SetTextColor(hFont, FontColor);

    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("failed to HI_GO_SetTextColor\n");
        return HI_FAILURE;
    }

    rc.x = StartX;
    rc.y = StartY;
    ret = HI_GO_GetTextExtent(hFont, pCharBuffer, &rc.w, &rc.h);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("failed to HI_GO_GetTextExtent\n");
        return HI_FAILURE;
    }

    ret = HI_GO_TextOut(hFont, pWind->hMemSurface, pCharBuffer, &rc);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("failed to HI_GO_TextOut\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 Drv_DownLoadFail(LOADER_Content_E enContent)
{
    HI_U32 testWind = 0;
    HI_S32 ret = HI_FAILURE;
    sPositionXY Pos = {0};

    Pos.x = WINDOW_START_X; //150;
    Pos.y = WINDOW_START_Y;

    Drv_OSDClear();
    testWind = WIN_CreateWind(Pos, WINDOW_WIDTH, WINDOW_HEIGHT, APP_WIND_NOTES);

#ifdef HI_ADVCA_FUNCTION_RELEASE
    switch (enContent)
    {
    case LOADER_CONTENT_DWNLD_WTING:
    case LOADER_CONTENT_PT_UPGRADING:
    case LOADER_CONTENT_FAIL_UPGRD:
        break;

    default:
        enContent = LOADER_CONTENT_FAIL_UPGRD;
        break;
    }
#endif


    ret = Drv_ShowText(testWind, enContent, 5, 110, APP_WIN_TXT_COLOR);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("Win fill rect fail!\n");
        return HI_FAILURE;
    }

    ret = WIN_BuildWindPic(testWind);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("WIN_BuildWindPic fail!\n");
        return HI_FAILURE;
    }

    ret = WIN_PasteWind(testWind, hLayerSurface);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("WIN_PasteWind fail!\n");
        return HI_FAILURE;
    }

    ret = WIN_ShowWind(testWind);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("WIN_ShowWind fail!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

const HI_CHAR * LoaderOSDGetText(LOADER_Content_E enContent)
{
	if (enContent >= LOADER_CONTENT_MAX)
	{
		return HI_NULL;
	}
	else
	{
		UNUSED(g_enLanguage);// for pc-lint
#ifdef HI_LOADER_APPLOADER
		if (HI_LOADER_UI_LANG_EN == g_enLanguage)
		{
			return pENG_Str[enContent];
		}
		else
		{
			return pCHN_Str[enContent];
		}

#else
		return pENG_Str[enContent];
#endif
	}
}

HI_S32 LOADER_NotifyInfo(HI_HANDLE *hWin, HI_U32 u32InfoNum, NOTIFY_INFO_S *pstInfo)
{
	HI_HANDLE window;
	HI_S32 Length;
	HI_S32 Width;
	HI_S32 TextWidth;
	HI_S32 TextHeight;
	HI_S32 s32StartX = 0;
	sPositionXY Pos;
	HI_U8 ii = 0;

	if ((0 == u32InfoNum) || (HI_NULL == pstInfo))
	{
		HI_ERR_LOADER("Invalid Parameter!\n");
		return HI_FAILURE;
	}

	if (u32InfoNum > 8)
	{
		Length = 720;
		Width = 576;
		Pos.x = 0;
		Pos.y = 0;
	}
	else
	{
		Length = WINDOW_WIDTH;
		Width = WINDOW_HEIGHT;
		Pos.x = WINDOW_START_X;
		Pos.y = WINDOW_START_Y;
	}

	window = WIN_CreateWind(Pos, Length, Width, APP_WIND_NOTES);

	for (ii = 0; ii < u32InfoNum; ii++)
	{
		if (HI_SUCCESS != HI_GO_GetTextExtent(hFont, pstInfo[ii].acInfo, &TextWidth, &TextHeight))
		{
			HI_ERR_LOADER("get text extent failed.\n");
			return HI_FAILURE;
		}

		if (TextWidth > Length)
		{
			s32StartX = 0;
		}
		else
		{
			s32StartX = (Length - TextWidth) / 2;
		}

		(HI_VOID)Drv_ShowTextEx(window, pstInfo[ii].acInfo,
				s32StartX, pstInfo[ii].s32StartY,
				APP_WIN_TXT_COLOR);
	}

	//add for window display
	WIN_BuildAndPasteWind(window);

	/* update window */
	(HI_VOID)WIN_ShowWind(window);

	if (hWin)
	{
		*hWin = window;
	}

	return HI_SUCCESS;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
