#include <utils/Log.h>
#include <binder/IServiceManager.h>
#include <utils/threads.h>
#include <binder/IMemory.h>
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IInterface.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <binder/Parcel.h>

#include "PQClient.h"

namespace android
{
    sp<IPQService> PQClient::mPQService;

    const sp<IPQService>& PQClient::getPQService()
    {
        if(mPQService.get() == 0)
        {
            sp<IServiceManager> sm = defaultServiceManager();
            sp<IBinder> binder ;
            do
            {
                binder = sm->getService(String16("HiPQ"));
                if (binder != 0)
                {
                    break;
                }
                usleep(500000);
            } while(true);
            mPQService = interface_cast<IPQService>(binder);
        }
        return mPQService;
    }

    int PQClient::setImageMode(int mode)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->setImageMode(mode);
        }
        return ret;
    }
    int PQClient::getImageMode()
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->getImageMode();
        }
        return ret;
    }

    int PQClient::setBrightness(int brightness)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->setBrightness(brightness);
        }
        return ret;
    }
    int PQClient::getBrightness(void)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->getBrightness();
        }
        return ret;
    }

    int PQClient::setContrast(int contrast)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->setContrast(contrast);
        }
        return ret;
    }
    int PQClient::getContrast(void)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->getContrast();
        }
        return ret;
    }

    int PQClient::setSaturation(int saturation)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();
        if(ps != 0)
        {
            ret = ps->setSaturation(saturation);
        }
        return ret;
    }
    int PQClient::getSaturation(void)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->getSaturation();
        }
        return ret;
    }

    int PQClient::setHue(int hue)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();
        if(ps != 0)
        {
            ret = ps->setHue(hue);
        }
        return ret;
    }
    int PQClient::getHue(void)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->getHue();
        }
        return ret;
    }

    int PQClient::saveParam(int savetype)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->saveParam(savetype);
        }
        return ret;
    }


    int PQClient::setShopMode(int enable)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->setShopMode(enable);
        }
        return ret;
    }
    int PQClient::getShopMode()
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->getShopMode();
        }
        return ret;
    }

    int PQClient::setColorEnhanceMode(int mode)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->setColorEnhanceMode(mode);
        }
        return ret;
    }
    int PQClient::getColorEnhanceMode()
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->getColorEnhanceMode();
        }
        return ret;
    }
    int PQClient::setCustomizeColor(int basecolor, int value)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();
    
        if(ps != 0)
        {
            ret = ps->setCustomizeColor(basecolor, value);
        }
        return ret;
    }
    int PQClient::getCustomizeColor(int basecolor)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();
    
        if(ps != 0)
        {
             ret = ps->getCustomizeColor(basecolor);
        }

        return ret;
    }

    int PQClient::setDynamicContrast(int mode)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->setDynamicContrast(mode);
        }
        return ret;
    }
    int PQClient::getDynamicContrast()
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->getDynamicContrast();
        }
        return ret;
    }

    int PQClient::setSharpness(int sharp)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->setSharpness(sharp);
        }
        return ret;
    }
    int PQClient::getSharpness(void)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->getSharpness();
        }
        return ret;
    }

    int PQClient::setSuperResolution(int enable)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->setSuperResolution(enable);
        }
        return ret;
    }
    int PQClient::getSuperResolution(void)
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->getSuperResolution();
        }
        return ret;
    }

    int PQClient::reset()
    {
        int ret = -1;
        const sp<IPQService>& ps = getPQService();

        if(ps != 0)
        {
            ret = ps->reset();
        }
        return ret;
    }

};
//end namespace
