#ifndef _PQ_SERVICE_H_
#define _PQ_SERVICE_H_

#include <cutils/memory.h>
#include <utils/Log.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include "IPQService.h"
//#include "hidisplay.h"

namespace android
{
    class PQService: public BnPQService
    {
        public:
            PQService();
            ~PQService();
            static void instantiate();

            virtual int setImageMode(int  mode);
            virtual int getImageMode();

            virtual int setBrightness(int  brightness);
            virtual int getBrightness();
            virtual int setContrast(int  contrast);
            virtual int getContrast();
            virtual int setSaturation(int  saturation);
            virtual int getSaturation();
            virtual int setHue(int  hue);
            virtual int getHue();

            virtual int setShopMode(int  enable);
            virtual int getShopMode();

            virtual int setColorEnhanceMode(int mode);
            virtual int getColorEnhanceMode();
            virtual int setCustomizeColor(int basecolor, int value);
            virtual int getCustomizeColor(int basecolor);

            virtual int setDynamicContrast(int mode);
            virtual int getDynamicContrast();

            virtual int setSharpness(int  sharp);
            virtual int getSharpness();

            virtual int setSuperResolution(int enable);
            virtual int getSuperResolution();

            virtual int saveParam(int savetype);
            virtual int reset();

            virtual void binderDied(const wp<IBinder>& who);
            status_t dump(int fd, const Vector<String16>& args);
    };
};
#endif /*DISPLAYSERVICE_H*/
