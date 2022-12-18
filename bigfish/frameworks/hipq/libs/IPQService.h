#ifndef _IPQ_SERVICE_H_
#define _IPQ_SERVICE_H_

#include <stdint.h>
#include <sys/types.h>
#include <utils/Errors.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>

namespace android {

    class IPQService : public IInterface
    {
        public:
            DECLARE_META_INTERFACE(PQService);
            virtual int setImageMode(int  mode) = 0;
            virtual int getImageMode() = 0;
            virtual int setBrightness(int  brightness) = 0;
            virtual int getBrightness() = 0;
            virtual int setContrast(int  contrast) = 0;
            virtual int getContrast() = 0;
            virtual int setSaturation(int  saturation) = 0;
            virtual int getSaturation() = 0;
            virtual int setHue(int  hue) = 0;
            virtual int getHue() = 0;

            virtual int saveParam(int savetype) = 0;
            virtual int reset() = 0;

            virtual int setShopMode(int enable) = 0;
            virtual int getShopMode() = 0;

            virtual int setColorEnhanceMode(int  mode) = 0;
            virtual int getColorEnhanceMode() = 0;
            virtual int setCustomizeColor(int basecolor, int value) = 0;
            virtual int getCustomizeColor(int basecolor) = 0;

            virtual int setDynamicContrast(int mode) = 0;
            virtual int getDynamicContrast() = 0;
            virtual int setSharpness(int sharp) = 0;
            virtual int getSharpness() = 0;
            virtual int setSuperResolution(int enable) = 0;
            virtual int getSuperResolution() = 0;
    };

    class BnPQService : public BnInterface<IPQService>
    {
        public:
            virtual status_t onTransact( uint32_t code,
                    const Parcel& data,
                    Parcel* reply,
                    uint32_t flags = 0);

    };

};
#endif
