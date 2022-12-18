#ifndef _PQ_CLIENT_H_
#define _PQ_CLIENT_H_

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <binder/IMemory.h>
#include <binder/Parcel.h>

#include "IPQService.h"


namespace android
{
    class PQClient: public RefBase
    {
        public:
            int setImageMode(int mode);
            int getImageMode();
            int setBrightness(int brightness);
            int getBrightness();
            int setContrast(int contrast);
            int getContrast();
            int setSaturation(int saturation);
            int getSaturation();
            int setHue(int hue);
            int getHue();

            
            int setShopMode(int enable);
            int getShopMode();

            int setColorEnhanceMode(int mode);
            int getColorEnhanceMode();
            int setCustomizeColor(int basecolor, int value);
            int getCustomizeColor(int basecolor);

            int setDynamicContrast(int mode);
            int getDynamicContrast();

            int setSharpness(int sharp);
            int getSharpness();

            int setSuperResolution(int enable);
            int getSuperResolution();

            int saveParam(int savetype);
            int reset();

        private:
            const sp<IPQService> & getPQService();
            static sp<IPQService> mPQService;
    };
};
#endif
