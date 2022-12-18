#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/PermissionCache.h>
#include <private/android_filesystem_config.h>
#include <utils/String16.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/types.h>
#include <sys/ioctl.h>
#include <utils/Log.h>
#include <cutils/properties.h>

#include <binder/Parcel.h>

#include "PQService.h"
#include "pqdef.h"

#include "pqsetting.h"

#define BUFLEN PROP_VALUE_MAX
#define LOG_TAG "PQService"


namespace android
{
    const String16 sDump("android.permission.DUMP");


    typedef struct ImageParam{
        int mode;
        int brightness;
        int contrast;
        int hue;
        int saturation;
    }ImageParam_S;
    
    ImageParam_S imageParam[HI_PQ_IMAGE_MODE_BUTT] = { 
                            {HI_PQ_IMAGE_MODE_STANDARD,50,50,50,50}, 
                            {HI_PQ_IMAGE_MODE_COLORFUL,50,55,50,55}, 
                            {HI_PQ_IMAGE_MODE_THEATER,45,45,50,50}, 
                            {HI_PQ_IMAGE_MODE_SPORT,55,55,50,53}, 
                            {HI_PQ_IMAGE_MODE_CUSTOMIZE,50,50,50,50}, 
                            };

    typedef struct ColorParam{
        int colorEnhanceMode;
        int u32Red;
        int u32Blue;
        int u32Green;
        int u32Cyan;
        int u32Magenta;
        int u32Yellow;
    }ColorParam_S;

    ColorParam_S colorParam[HI_PQ_COLOR_ENHANCE_MODE_BUTT] = { 
                            {HI_PQ_COLOR_ENHANCE_MODE_AUTO,50,50,50,50,50,50}, 
                            {HI_PQ_COLOR_ENHANCE_MODE_BLUE,50,65,50,50,50,50}, 
                            {HI_PQ_COLOR_ENHANCE_MODE_GREEN,50,50,65,50,50,50}, 
                            {HI_PQ_COLOR_ENHANCE_MODE_CYAN,50,65,65,50,50,50}, 
                            };

    int currImageMode = 0;

    int currShopMode = 0;

    int currColorEnhanceMode = 0;
    int customizeSixColor[HI_PQ_BASE_COLOR_TYPE_BUTT] = {50,50,50,50,50,50};

    int currDyncContrastMode = 2;
    int currSuperResolutionEnable = 1;
    int currSharpness = 50;


    PQService::PQService()
    {
        int ret = -1;
        char buffer[BUFLEN];
        pq_init();

        //image mode
        property_get("persist.sys.pq.imagemode", buffer, "0"); //default 0 is HI_PQ_IMAGE_MODE_STANDARD
        currImageMode = atoi(buffer);
        //setImageMode(currImageMode); //fastboot set already
        ALOGW("currImageMode = %d\n",currImageMode);

        //shop mode
        memset(buffer, 0, BUFLEN);
        property_get("persist.sys.pq.shopmode", buffer, "2");
        currShopMode = atoi(buffer);
        setShopMode(currShopMode); //0 is on, 1 is splitscreen, 2 is off; default is off

        //customize six color
        char delims[] = ",";
        char *result = NULL;
        int i = 0;
        memset(buffer, 0, BUFLEN);
        property_get("persist.sys.pq.sixcolor", buffer, "50,50,50,50,50,50"); //default 50,50,50,50,50,50
        result = strtok( buffer, delims );
        while( (result != NULL) && (i < 6)) {
            ALOGW( "sixcolor is \"%s\"\n", result );
            customizeSixColor[i++] = atoi(result);
            result = strtok( NULL, delims );
        }

        //color enhance mode
        memset(buffer, 0, BUFLEN);
        property_get("persist.sys.pq.colormode", buffer, "0"); //default 0 is HI_PQ_COLOR_ENHANCE_MODE_AUTO
        currColorEnhanceMode = atoi(buffer);
        setColorEnhanceMode(currColorEnhanceMode);
        ALOGW("currColorEnhanceMode = %d\n",currColorEnhanceMode);

        //dynamic contrast
        memset(buffer, 0, BUFLEN);
        property_get("persist.sys.pq.dynccontrast", buffer, "2"); //default 2 is HI_PQ_DYNAMIC_CONTRAST_MODE_MIDDLE
        currDyncContrastMode = atoi(buffer);
        setDynamicContrast(currDyncContrastMode);
        ALOGW("currDyncContrastMode = %d\n",currDyncContrastMode);

        //sharpness
        memset(buffer, 0, BUFLEN);
        property_get("persist.sys.pq.sharpness", buffer, "50"); //default 50
        currSharpness = atoi(buffer);
        setSharpness(currSharpness);
        ALOGW("currSharpness = %d\n",currSharpness);

        //super resolution
        memset(buffer, 0, BUFLEN);
        property_get("persist.sys.pq.superresolution", buffer, "1"); //default 1 is enable
        currSuperResolutionEnable = atoi(buffer);
        setSuperResolution(currSuperResolutionEnable);
        ALOGW("currSuperResolutionEnable = %d\n",currSuperResolutionEnable);
    }

    PQService::~PQService()
    {
        pq_deinit();
    }

    void PQService::instantiate()
    {
        defaultServiceManager()->addService(String16("HiPQ"), new PQService());
    }

    int PQService::setImageMode(int mode)
    {
        if ((mode > HI_PQ_IMAGE_MODE_CUSTOMIZE)
                || (mode < HI_PQ_IMAGE_MODE_STANDARD))
        {
            ALOGE("setImageMode, err mode = %d", mode);
            return -1;
        }

        ALOGW("setImageMode, mode = %d\n",mode);
        currImageMode = mode;

        if(mode == HI_PQ_IMAGE_MODE_CUSTOMIZE) {
            //do nothing
        } else {
            pq_set_brightness(imageParam[mode].brightness);
            pq_set_contrast(imageParam[mode].contrast);
            pq_set_hue(imageParam[mode].hue);
            pq_set_saturation(imageParam[mode].saturation);
        }

        return  0;
    }
    int PQService::getImageMode()
    {
        ALOGW("getImageMode, currImageMode = %d", currImageMode);
        return  currImageMode;
    }

    int PQService::setBrightness(int brightness)
    {
        int ret = -1;
        if ((brightness > 100) || (brightness < 0))
        {
            ALOGE("setBrightness, set value exceed limits");
            return -1;
        }
        imageParam[currImageMode].brightness = brightness;
        ret = pq_set_brightness(brightness);
        return  ret;
    }
    int PQService::getBrightness()
    {
        int ret = -1;
        pq_get_brightness(&ret);
        return  ret;
    }
    int PQService::setContrast(int contrast)
    {
        int ret = -1;
        if ((contrast > 100) || (contrast < 0))
        {
            ALOGE("setContrast, set value exceed limits");
            return -1;
        }
        imageParam[currImageMode].contrast = contrast;
        ret = pq_set_contrast(contrast);
        return  ret;
    }
    int PQService::getContrast()
    {
        int ret = -1;
        pq_get_contrast(&ret);
        return  ret;
    }
    int PQService::setSaturation(int saturation)
    {
        int ret = -1;
        if ((saturation > 100) || (saturation < 0))
        {
            ALOGE("setSaturation, set value exceed limits");
            return -1;
        }
        imageParam[currImageMode].saturation = saturation;
        ret = pq_set_saturation(saturation);
        return  ret;
    }
    int PQService::getSaturation()
    {
        int ret = -1;
        pq_get_saturation(&ret);
        return  ret;
    }
    int PQService::setHue(int hue)
    {
        int ret = -1;
        if ((hue > 100) || (hue < 0))
        {
            ALOGE("setHue, set value exceed limits");
            return -1;
        }
        imageParam[currImageMode].hue = hue;
        ret = pq_set_hue(hue);
        return  ret;
    }
    int PQService::getHue()
    {
        int ret = -1;
        pq_get_hue(&ret);
        return  ret;
    }


    int PQService::setShopMode(int enable)
    {
        int ret = -1;
        if ((enable > 2) || (enable < 0))
        {
            ALOGE("setShopMode, err mode = %d", enable);
            return -1;
        }
        ALOGW("setShopMode, enable = %d\n",enable);
        currShopMode = enable;
        ret = pq_set_engine_mode(enable);
        return  ret;
    }
    int PQService::getShopMode()
    {
        ALOGW("getShopMode, currShopMode = %d\n",currShopMode);
        return  currShopMode;
    }

    int PQService::setColorEnhanceMode(int mode)
    {
        ALOGW("setColorEnhanceMode, mode = %d\n",mode);
        HI_UNF_PQ_COLOR_ENHANCE_S stColorEnhanceParam;
        if ((mode > HI_PQ_COLOR_ENHANCE_MODE_CUSTOMIZE)
                || (mode < HI_PQ_COLOR_ENHANCE_MODE_AUTO))
        {
            ALOGE("setColorEnhanceMode, err mode = %d", mode);
            return -1;
        }

        if (mode == HI_PQ_COLOR_ENHANCE_MODE_CUSTOMIZE) {
            stColorEnhanceParam.enColorEnhanceType = HI_UNF_PQ_COLOR_ENHANCE_SIX_BASE;
            stColorEnhanceParam.unColorGain.stSixBase.u32Red = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_RED];
            stColorEnhanceParam.unColorGain.stSixBase.u32Blue = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_BLUE];
            stColorEnhanceParam.unColorGain.stSixBase.u32Green = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_GREEN];
            stColorEnhanceParam.unColorGain.stSixBase.u32Cyan = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_CYAN];
            stColorEnhanceParam.unColorGain.stSixBase.u32Magenta = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_MAGENTA];
            stColorEnhanceParam.unColorGain.stSixBase.u32Yellow = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_YELLOW];
        } else if(mode == HI_PQ_COLOR_ENHANCE_MODE_SKIN) {
            stColorEnhanceParam.enColorEnhanceType = HI_UNF_PQ_COLOR_ENHANCE_FLESHTONE;
            stColorEnhanceParam.unColorGain.enFleshtone =  HI_UNF_PQ_FLESHTONE_GAIN_MID;
        } else if(mode == HI_PQ_COLOR_ENHANCE_MODE_BLUE) {
            stColorEnhanceParam.enColorEnhanceType = HI_UNF_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE;
            stColorEnhanceParam.unColorGain.enColorMode = HI_UNF_PQ_COLOR_MODE_BLUE;
        } else if(mode == HI_PQ_COLOR_ENHANCE_MODE_GREEN) {
            stColorEnhanceParam.enColorEnhanceType = HI_UNF_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE;
            stColorEnhanceParam.unColorGain.enColorMode = HI_UNF_PQ_COLOR_MODE_GREEN;
        } else if(mode == HI_PQ_COLOR_ENHANCE_MODE_CYAN) {
            stColorEnhanceParam.enColorEnhanceType = HI_UNF_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE;
            stColorEnhanceParam.unColorGain.enColorMode = HI_UNF_PQ_COLOR_MODE_BG;
        } else if(mode == HI_PQ_COLOR_ENHANCE_MODE_AUTO) {
            stColorEnhanceParam.enColorEnhanceType = HI_UNF_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE;
            stColorEnhanceParam.unColorGain.enColorMode = HI_UNF_PQ_COLOR_MODE_RECOMMEND;
        }
        pq_set_color_enhance(stColorEnhanceParam);
        currColorEnhanceMode = mode;

        return  0;
    }
    int PQService::getColorEnhanceMode()
    {
        ALOGW("getColorEnhanceMode, currColorEnhanceMode = %d", currColorEnhanceMode);
        return  currColorEnhanceMode;
    }

    int PQService::setCustomizeColor(int basecolor, int value)
    {
        HI_UNF_PQ_COLOR_ENHANCE_S stColorEnhanceParam;
        if ((basecolor > HI_PQ_BASE_COLOR_TYPE_YELLOW)
                || (basecolor < HI_PQ_BASE_COLOR_TYPE_RED))
        {
            ALOGE("setCustomizeColor, err basecolor = %d", basecolor);
            return -1;
        }
        if ((value > 100) || (value < 0))
        {
            ALOGE("setCustomizeColor, set value exceed limits");
            return -1;
        }
        customizeSixColor[basecolor] = value;
        ALOGW("setCustomizeColor, basecolor = %d, value = %d\n",basecolor,value);

        stColorEnhanceParam.enColorEnhanceType = HI_UNF_PQ_COLOR_ENHANCE_SIX_BASE;
        stColorEnhanceParam.unColorGain.stSixBase.u32Red = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_RED];
        stColorEnhanceParam.unColorGain.stSixBase.u32Blue = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_BLUE];
        stColorEnhanceParam.unColorGain.stSixBase.u32Green = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_GREEN];
        stColorEnhanceParam.unColorGain.stSixBase.u32Cyan = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_CYAN];
        stColorEnhanceParam.unColorGain.stSixBase.u32Magenta = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_MAGENTA];
        stColorEnhanceParam.unColorGain.stSixBase.u32Yellow = customizeSixColor[HI_PQ_BASE_COLOR_TYPE_YELLOW];

        pq_set_color_enhance(stColorEnhanceParam);

        return  0;
    }

    int PQService::getCustomizeColor(int basecolor)
    {
        if(basecolor > HI_PQ_BASE_COLOR_TYPE_YELLOW)
            return -1;
        ALOGW("getCustomizeColor, basecolor = %d, value = %d\n", basecolor,customizeSixColor[basecolor]);
         return customizeSixColor[basecolor];
    }

    int PQService::setDynamicContrast(int mode)
    {
        int ret = -1;
        int level = 50;
        
        if ((mode > HI_PQ_DYNAMIC_CONTRAST_MODE_HIGH)
                || (mode < HI_PQ_DYNAMIC_CONTRAST_MODE_OFF))
        {
            ALOGE("setDynamicContrast, err mode = %d", mode);
            return ret;
        }
        currDyncContrastMode = mode;
        ALOGW("setDynamicContrast, mode = %d\n",mode);
        if(mode == HI_PQ_DYNAMIC_CONTRAST_MODE_OFF)
            level = 0;
        else if(mode == HI_PQ_DYNAMIC_CONTRAST_MODE_LOW)
            level = 10;
        else if(mode == HI_PQ_DYNAMIC_CONTRAST_MODE_HIGH)
            level = 100;
        else
            level = 50;

        ret = pq_set_dynamic_contrast(level);
        return  ret;
    }
    int PQService::getDynamicContrast()
    {
        ALOGW("getDynamicContrast, currDyncContrastMode = %d", currDyncContrastMode);
        return  currDyncContrastMode;
    }

    int PQService::setSharpness(int sharp)
    {
        int ret = -1;
        if ((sharp > 100) || (sharp < 0))
        {
            ALOGE("setSharpness, set value exceed limits");
            return -1;
        }
        currSharpness = sharp;
        ALOGW("setSharpness, sharp = %d", sharp);
        ret = pq_set_sharpness(sharp);
        return  ret;
    }
    int PQService::getSharpness()
    {
        ALOGW("getSharpness, sharp = %d", currSharpness);
        return  currSharpness;
    }

    int PQService::setSuperResolution(int enable)
    {
        int ret = -1;
        HI_UNF_PQ_SR_DEMO_E mode;
        if ((enable > HI_UNF_PQ_SR_ENABLE_A)
                || (enable < HI_UNF_PQ_SR_DISABLE))
        {
            ALOGE("setSuperResolution, err sr mode = %d", enable);
            return ret;
        }
        currSuperResolutionEnable = enable;
        ALOGW("setSuperResolution, enable = %d\n",enable);
        if(enable == 0)
            mode = HI_UNF_PQ_SR_DISABLE;
        else 
            mode = HI_UNF_PQ_SR_ENABLE_A;
        ret = pq_set_sr_mode(mode);
        return  ret;
    }
    int PQService::getSuperResolution()
    {
        ALOGW("getSuperResolution, currSuperResolutionEnable = %d", currSuperResolutionEnable);
        return  currSuperResolutionEnable;
    }


    int PQService::saveParam(int savetype)
    {
        int ret = -1;
        char  buffer[BUFLEN];
        ALOGW("saveParam, savetype = %d\n",savetype);

        if(savetype == HI_PQ_SAVE_TYPE_IMAGE) {
            sprintf(buffer,"%d", currImageMode);
            ret = property_set("persist.sys.pq.imagemode", buffer);
            ret = pq_save_image(imageParam[currImageMode].brightness,
                                imageParam[currImageMode].contrast,
                                imageParam[currImageMode].saturation,
                                imageParam[currImageMode].hue
                            );
        } else if(savetype == HI_PQ_SAVE_TYPE_COLOR) {
            sprintf(buffer,"%d", currColorEnhanceMode);
            ret = property_set("persist.sys.pq.colormode", buffer);

            sprintf(buffer,"%d,%d,%d,%d,%d,%d", 
                        customizeSixColor[HI_PQ_BASE_COLOR_TYPE_RED],
                        customizeSixColor[HI_PQ_BASE_COLOR_TYPE_BLUE],
                        customizeSixColor[HI_PQ_BASE_COLOR_TYPE_GREEN],
                        customizeSixColor[HI_PQ_BASE_COLOR_TYPE_CYAN],
                        customizeSixColor[HI_PQ_BASE_COLOR_TYPE_MAGENTA],
                        customizeSixColor[HI_PQ_BASE_COLOR_TYPE_YELLOW]
                    );
            ret = property_set("persist.sys.pq.sixcolor", buffer);
        } else if(savetype == HI_PQ_SAVE_TYPE_SHARPNESS) {
            sprintf(buffer,"%d", currSharpness);
            ret = property_set("persist.sys.pq.sharpness", buffer);
        } else if(savetype == HI_PQ_SAVE_TYPE_DYNCCONTRAST) {
            sprintf(buffer,"%d", currDyncContrastMode);
            ret = property_set("persist.sys.pq.dynccontrast", buffer);
        } else if(savetype == HI_PQ_SAVE_TYPE_SHOPMODE) {
            sprintf(buffer,"%d", currShopMode);
            ret = property_set("persist.sys.pq.shopmode", buffer);
        } else if(savetype == HI_PQ_SAVE_TYPE_SUPERRESOLUTION) {
            sprintf(buffer,"%d", currSuperResolutionEnable);
            ret = property_set("persist.sys.pq.superresolution", buffer);
        } else {
        }
        return ret;
    }

    int PQService::reset()
    {
        ALOGW("pq reset\n");
        //image mode
        setImageMode(0);
        property_set("persist.sys.pq.imagemode", "0"); //default 0 is HI_PQ_IMAGE_MODE_STANDARD

        //shop mode
        setShopMode(0);
        property_set("persist.sys.pq.shopmode", "2"); //default is off

        //color enhance mode
        setColorEnhanceMode(0);
        property_set("persist.sys.pq.colormode", "0"); //default 0 is HI_PQ_COLOR_ENHANCE_MODE_AUTO

        //customize six color
        property_set("persist.sys.pq.sixcolor", "50,50,50,50,50,50"); //default 50,50,50,50,50,50

        //dynamic contrast
        setDynamicContrast(2);
        property_set("persist.sys.pq.dynccontrast", "2"); //default 2 is HI_PQ_DYNAMIC_CONTRAST_MODE_MIDDLE

        //sharpness
        setSharpness(50);
        property_set("persist.sys.pq.sharpness", "50"); //default 50

        //super resolution
        setSuperResolution(1);
        property_set("persist.sys.pq.superresolution", "1"); //default 1 is enable

        return 0;
    }

    void PQService::binderDied(const wp<IBinder>& who) {
        /* client is force close */
    }

    status_t PQService::dump(int fd, const Vector<String16>& args)
    {
        String8  result;
        IPCThreadState* ipc = IPCThreadState::self();
        const int pid = ipc->getCallingPid();
        const int uid = ipc->getCallingUid();
        if ((uid != AID_SHELL) &&
             !PermissionCache::checkPermission(sDump, pid, uid)) {
             result.appendFormat("Permission Denial: "
                            "can't dump HiPQ from pid=%d, uid=%d\n", pid, uid);
        } else {
            const int BUFF = 2048;
            char output[BUFF] = {0};
            char *tmp = output;
            int length = 0;
            sprintf(output,
                "---currImageMode--- Brightness--- Contrast ---Saturation---   Hue   --- \n"
                "---%10d---%10d---%10d---%10d---%10d---\n",
                currImageMode, getBrightness(), getContrast(), getSaturation(), getHue()
            );
            result.append(output);
        }

        write(fd, result.string(), result.size());
        return NO_ERROR;
    }

};
