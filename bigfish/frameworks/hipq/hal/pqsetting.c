#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <utils/Log.h>

#include <hi_unf_pdm.h>
#include "pqsetting.h"


#define TURN_ON_SD0

#define HI_UNF_DISP_SD0 (HI_UNF_DISPLAY0)
#define HI_UNF_DISP_HD0 (HI_UNF_DISPLAY1)


int pq_init()
{
    HI_S32 ret = HI_SUCCESS;

    ret = HI_UNF_PQ_Init();
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_Init failed, ret = %x!", ret);
    }
    return ret;
}

int pq_deinit()
{
    HI_S32 ret = HI_SUCCESS;

    ret = HI_UNF_PQ_DeInit();
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_DeInit failed, ret = %x!", ret);
    }
    return ret;
}

int pq_get_brightness(int *brightness)
{
    HI_S32 ret = HI_SUCCESS;
    if( NULL == brightness) {
        ALOGE("brightness is NULL");
        return -1;
    }

    ret = HI_UNF_PQ_GetBrightness(HI_UNF_DISP_HD0, (HI_U32 *)brightness);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_GetBrightness failed, ret = %x!", ret);
    }
    return ret;
}

int pq_set_brightness(int brightness)
{
    HI_S32 ret = HI_SUCCESS;

    if((brightness > 100) || (brightness < 0)) {
        ALOGE("set value exceed limits");
        return -1;
    }

    ret = HI_UNF_PQ_SetBrightness(HI_UNF_DISP_HD0, brightness);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HD HI_UNF_PQ_SetBrightness failed, ret = %x!", ret);
    }
#ifdef TURN_ON_SD0
    ret = HI_UNF_PQ_SetBrightness(HI_UNF_DISP_SD0, brightness);
    if (HI_SUCCESS != ret)
    {
        ALOGE("SD HI_UNF_PQ_SetBrightness failed, ret = %x!", ret);
    }
#endif

    return ret;
}

int pq_get_contrast(int *contrast)
{
    HI_S32 ret = HI_SUCCESS;
    if( NULL == contrast) {
        ALOGE("contrast is NULL");
        return -1;
    }

    ret = HI_UNF_PQ_GetContrast(HI_UNF_DISP_HD0, (HI_U32 *)contrast);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_DISP_GetContrast failed!");
    }

    return ret;
}

int pq_set_contrast(int contrast)
{
    HI_S32 ret = HI_SUCCESS;

    if((contrast > 100) || (contrast < 0)) {
        ALOGE("set value exceed limits");
        return -1;
    }

    ret = HI_UNF_PQ_SetContrast(HI_UNF_DISP_HD0, contrast);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HD HI_UNF_PQ_SetContrast failed!");
    }
#ifdef TURN_ON_SD0
    ret = HI_UNF_PQ_SetContrast(HI_UNF_DISP_SD0, contrast);
    if (HI_SUCCESS != ret)
    {
        ALOGE("SD HI_UNF_PQ_SetContrast failed, ret = %x!", ret);
    }
#endif

    return ret;
}

int pq_get_saturation(int *saturation)
{
    HI_S32 ret = HI_SUCCESS;
    if( NULL == saturation) {
        ALOGE("saturation is NULL");
        return -1;
    }

    ret = HI_UNF_PQ_GetSaturation(HI_UNF_DISP_HD0, (HI_U32 *)saturation);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_GetSaturation failed!");
    }

    return ret;
}

int pq_set_saturation(int saturation)
{
    HI_S32 ret = HI_SUCCESS;

    if((saturation > 100) || (saturation < 0)) {
        ALOGE("set value exceed limits");
        return -1;
    }

    ret = HI_UNF_PQ_SetSaturation(HI_UNF_DISP_HD0, saturation);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HD HI_UNF_PQ_SetSaturation failed!");
    }
#ifdef TURN_ON_SD0
    ret = HI_UNF_PQ_SetSaturation(HI_UNF_DISP_SD0, saturation);
    if (HI_SUCCESS != ret)
    {
        ALOGE("SD HI_UNF_PQ_SetSaturation failed, ret = %x!", ret);
    }
#endif

    return ret;
}

int pq_get_hue(int *hue)
{
    HI_S32 ret = HI_SUCCESS;
    if( NULL == hue) {
        ALOGE("hue is NULL");
        return -1;
    }

    ret = HI_UNF_PQ_GetHue(HI_UNF_DISP_HD0, (HI_U32 *)hue);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_GetHue failed!");
    }

    return ret;
}

int pq_set_hue(int hue)
{
    HI_S32 ret = HI_SUCCESS;

    if((hue > 100) || (hue < 0)) {
        ALOGE("set value exceed limits");
        return -1;
    }

    ret = HI_UNF_PQ_SetHue(HI_UNF_DISP_HD0, hue);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HD HI_UNF_PQ_SetHue failed!");
    }
#ifdef TURN_ON_SD0
    ret = HI_UNF_PQ_SetHue(HI_UNF_DISP_SD0, hue);
    if (HI_SUCCESS != ret)
    {
        ALOGE("SD HI_UNF_PQ_SetHue failed, ret = %x!", ret);
    }
#endif

    return ret;
}

int pq_save_image(int bright, int contrast, int saturation, int hue)
{
    int ret = -1;

    if((bright > 100) || (bright < 0)) {
        ALOGE("bright value exceed limits");
        return -1;
    }
    if((contrast > 100) || (contrast < 0)) {
        ALOGE("contrast value exceed limits");
        return -1;
    }
    if((saturation > 100) || (saturation < 0)) {
        ALOGE("saturation value exceed limits");
        return -1;
    }
    if((hue > 100) || (hue < 0)) {
        ALOGE("hue value exceed limits");
        return -1;
    }

    /*read old config in base param partition*/
    HI_UNF_PDM_DISP_PARAM_S baseParam;
    memset(&baseParam,0,sizeof(HI_UNF_PDM_DISP_PARAM_S));
    ret = HI_UNF_PDM_GetBaseParam(HI_UNF_DISP_HD0, &baseParam);
    if(ret != HI_SUCCESS)
    {
        ALOGE("HD HI_UNF_PDM_GetBaseParam failed,ret = %d", ret);
        return -1;
    } else {
        /*all changes are saved. so we clear the change flag here*/
    }

    /* update value */
    baseParam.u32Brightness = bright;
    baseParam.u32Contrast = contrast;
    baseParam.u32Saturation = saturation;
    baseParam.u32HuePlus = hue;

    /*save to baseparam*/
    ret = HI_UNF_PDM_UpdateBaseParam(HI_UNF_DISP_HD0, &baseParam);
    if(ret != HI_SUCCESS)
    {
        ALOGE("HD HI_UNF_PDM_UpdateBaseParam failed,ret = %d", ret);
    } else {
        /*all changes are saved. so we clear the change flag here*/
    }

#ifdef TURN_ON_SD0
    memset(&baseParam,0,sizeof(HI_UNF_PDM_DISP_PARAM_S));
    ret = HI_UNF_PDM_GetBaseParam(HI_UNF_DISP_SD0, &baseParam);
    if(ret != HI_SUCCESS)
    {
        ALOGE("SD HI_UNF_PDM_GetBaseParam failed,ret = %d", ret);
        return -1;
    }
    baseParam.u32Brightness = bright;
    baseParam.u32Contrast = contrast;
    baseParam.u32Saturation = saturation;
    baseParam.u32HuePlus = hue;
    ret = HI_UNF_PDM_UpdateBaseParam(HI_UNF_DISP_SD0, &baseParam);
    if(ret != HI_SUCCESS)
    {
        ALOGE("SD HI_UNF_PDM_UpdateBaseParam failed,ret = %d", ret);
    }
#endif
    return ret;
}

int pq_set_engine_mode(int mode)
{
    //0 is on, 1 is splitscreen, 2 is off
    ALOGE("pq_set_engine_mode, mode = %d", mode);
    int ret = HI_SUCCESS;
    if(mode == 0) {
        ret = HI_UNF_PQ_SetPQModule(HI_UNF_PQ_MODULE_ALL, 1);
        if (HI_SUCCESS != ret) ALOGE("HD HI_UNF_PQ_SetPQModule failed, ret = %x!", ret);
        ret = HI_UNF_PQ_SetDemo(HI_UNF_PQ_DEMO_ALL, 0);
        if (HI_SUCCESS != ret) ALOGE("HD HI_UNF_PQ_SetDemo failed, ret = %x!", ret);
    } else if(mode == 1) {
        ret = HI_UNF_PQ_SetPQModule(HI_UNF_PQ_MODULE_ALL, 1);
        if (HI_SUCCESS != ret) ALOGE("HD HI_UNF_PQ_SetPQModule failed, ret = %x!", ret);
        ret = HI_UNF_PQ_SetDemo(HI_UNF_PQ_DEMO_ALL, 1);
        if (HI_SUCCESS != ret) ALOGE("HD HI_UNF_PQ_SetDemo failed, ret = %x!", ret);
    } else if(mode == 2) {
        ret = HI_UNF_PQ_SetPQModule(HI_UNF_PQ_MODULE_ALL, 0);
        if (HI_SUCCESS != ret) ALOGE("HD HI_UNF_PQ_SetPQModule failed, ret = %x!", ret);
    } else {
        ALOGE("pq_set_engine_mode, err mode = %d", mode);
    }
    return ret;
}

int pq_set_color_enhance(HI_UNF_PQ_COLOR_ENHANCE_S colorEnhanceParam)
{
    int ret = HI_SUCCESS;

    ret = HI_UNF_PQ_SetColorEnhanceParam(colorEnhanceParam);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_SetColorEnhanceParam failed, ret = %x!", ret);
    }

    return ret;
}

int pq_get_color_enhance(HI_UNF_PQ_COLOR_ENHANCE_S * pColorEnhanceParam)
{
    int ret = HI_SUCCESS;
    if( NULL == pColorEnhanceParam) {
        ALOGE("pColorEnhanceParam is NULL");
        return -1;
    }

    ret = HI_UNF_PQ_GetColorEnhanceParam(pColorEnhanceParam);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_GetColorEnhanceParam failed, ret = %x!", ret);
    }

    return ret;
}

int pq_set_dynamic_contrast(int dcilevel)
{
    int ret = HI_SUCCESS;
    if((dcilevel > 100) || (dcilevel < 0)) {
        ALOGE("set value exceed limits");
        return -1;
    }

    ret = HI_UNF_PQ_SetDynamicContrast(dcilevel);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_SetDynamicContrast failed, ret = %x!", ret);
    }

    return ret;
}

int pq_get_dynamic_contrast(int * pDcilevel)
{
    int ret = HI_SUCCESS;
    if( NULL == pDcilevel ) {
        ALOGE("pDcilevel is NULL");
        return -1;
    }

    ret = HI_UNF_PQ_GetDynamicContrast((HI_U32 *)pDcilevel);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_GetDynamicContrast failed, ret = %x!", ret);
    }

    return ret;
}

int pq_set_sharpness(int sharpness)
{
    int ret = HI_SUCCESS;
    if((sharpness > 100) || (sharpness < 0)) {
        ALOGE("set value exceed limits");
        return -1;
    }

    ret = HI_UNF_PQ_SetSharpness(HI_UNF_DISP_HD0, sharpness);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_SetSharpness failed, ret = %x!", ret);
    }

    return ret;
}


int pq_get_sharpness(int * pSharpness)
{
    int ret = HI_SUCCESS;
    if( NULL == pSharpness ) {
        ALOGE("pSharpness is NULL");
        return -1;
    }

    ret = HI_UNF_PQ_GetSharpness(HI_UNF_DISP_HD0, (HI_U32 *)pSharpness);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_GetSharpness failed, ret = %x!", ret);
    }

    return ret;
}

int pq_set_sr_mode(HI_UNF_PQ_SR_DEMO_E srmode)
{
    int ret = HI_SUCCESS;

    ret = HI_UNF_PQ_SetSRMode(HI_UNF_DISP_HD0, srmode);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_SetSRMode failed, ret = %x!", ret);
    }

    return ret;
}

int pq_get_sr_mode(HI_UNF_PQ_SR_DEMO_E * pSrmode)
{
    int ret = HI_SUCCESS;
    if( NULL == pSrmode ) {
        ALOGE("pSrmode is NULL");
        return -1;
    }

    ret = HI_UNF_PQ_GetSRMode(HI_UNF_DISP_HD0, pSrmode);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_PQ_GetSRMode failed, ret = %x!", ret);
    }

    return ret;
}

