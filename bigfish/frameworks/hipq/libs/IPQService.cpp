#include <utils/Log.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/Parcel.h>

#include "unistd.h"
#include "string.h"

#include "pqdef.h"
#include "IPQService.h"

namespace android {

    enum {
        SETIMAGEMODE = IBinder::FIRST_CALL_TRANSACTION + 0,
        GETIMAGEMODE,
        SETBRIGHT,
        GETBRIGHT,
        SETCONTRAST,
        GETCONTRAST,
        SETHUE,
        GETHUE,
        SETSATURATION,
        GETSATURATION,
        SAVEPARAM,
        RESET,
        SETSHOPMODE,
        GETSHOPMODE,
        SETCOLORMODE,
        GETCOLORMODE,
        SETCUSTOMIZECOLOR,
        GETCUSTOMIZECOLOR,
        SETDYNAMICCONTRAST,
        GETDYNAMICCONTRAST,
        SETSHARP,
        GETSHARP,
        SETSUPERRESOLUTION,
        GETSUPERRESOLUTION
    };

    class BpPQService : public BpInterface<IPQService>
    {
        public:

            BpPQService(const sp<IBinder>& impl)
                : BpInterface<IPQService>(impl)
            {
            }

            virtual int getImageMode()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(GETIMAGEMODE, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }
            virtual int setImageMode(int  mode)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(mode);
                remote()->transact(SETIMAGEMODE, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int getBrightness()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(GETBRIGHT, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int setBrightness(int  brightness)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(brightness);
                remote()->transact(SETBRIGHT, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int getContrast()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(GETCONTRAST, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int setContrast(int  contrast)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(contrast);
                remote()->transact(SETCONTRAST, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int getSaturation()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(GETSATURATION, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int setSaturation(int  saturation)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(saturation);
                remote()->transact(SETSATURATION, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int getHue()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(GETHUE, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int setHue(int  hue)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(hue);
                remote()->transact(SETHUE, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }


            virtual int saveParam(int savetype)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(savetype);
                remote()->transact(SAVEPARAM, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int reset()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(RESET, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }
            virtual int setShopMode(int  enable)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(enable);
                remote()->transact(SETSHOPMODE, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }
            virtual int getShopMode()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(GETSHOPMODE, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int getColorEnhanceMode()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(GETCOLORMODE, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }
            virtual int setColorEnhanceMode(int  mode)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(mode);
                remote()->transact(GETCOLORMODE, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int getCustomizeColor(int basecolor)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(basecolor);
                remote()->transact(GETCUSTOMIZECOLOR, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;

            }
            virtual int setCustomizeColor(int basecolor, int value)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(basecolor);
                data.writeInt32(value);
                remote()->transact(SETCUSTOMIZECOLOR, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int getSharpness()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(GETSHARP, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int setSharpness(int  sharp)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(sharp);
                remote()->transact(SETSHARP, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }
            virtual int getDynamicContrast()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(GETDYNAMICCONTRAST, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int setDynamicContrast(int  mode)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(mode);
                remote()->transact(SETDYNAMICCONTRAST, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }
            virtual int getSuperResolution()
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                remote()->transact(GETSUPERRESOLUTION, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

            virtual int setSuperResolution(int  enable)
            {
                Parcel data, reply;
                data.writeInterfaceToken(IPQService::getInterfaceDescriptor());
                data.writeInt32(enable);
                remote()->transact(SETSUPERRESOLUTION, data, &reply);
                int32_t ret = reply.readInt32();
                if(ret == 0)
                {
                    ret = reply.readInt32();
                }
                else
                {
                    ret = -1;
                }
                return ret;
            }

    };

    IMPLEMENT_META_INTERFACE(PQService, "com.hisilicon.android.IPQManager");

    status_t BnPQService::onTransact( uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
    {
        int ret = -1;
        int32_t value;
        switch(code)
        {
            case GETIMAGEMODE:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = getImageMode();
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case SETIMAGEMODE:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = setImageMode(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GETBRIGHT:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = getBrightness();
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case SETBRIGHT:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = setBrightness(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GETCONTRAST:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = getContrast();
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case SETCONTRAST:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = setContrast(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GETHUE:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = getHue();
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case SETHUE:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = setHue(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GETSATURATION:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = getSaturation();
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case SETSATURATION:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = setSaturation(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case SAVEPARAM:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = saveParam(value);
                reply->writeInt32(ret);
                return NO_ERROR;
            case RESET:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = reset();
                reply->writeInt32(ret);
                return NO_ERROR;
            case SETSHOPMODE:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = setShopMode(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GETSHOPMODE:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = getShopMode();
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GETCOLORMODE:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = getColorEnhanceMode();
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case SETCOLORMODE:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = setColorEnhanceMode(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;

            case SETCUSTOMIZECOLOR:
                CHECK_INTERFACE(IPQService, data, reply);
                int base;
                base = data.readInt32();
                value = data.readInt32();
                ret = setCustomizeColor(base,value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GETCUSTOMIZECOLOR:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = getCustomizeColor(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;

            case GETDYNAMICCONTRAST:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = getDynamicContrast();
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case SETDYNAMICCONTRAST:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = setDynamicContrast(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GETSHARP:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = getSharpness();
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case SETSHARP:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = setSharpness(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GETSUPERRESOLUTION:
                CHECK_INTERFACE(IPQService, data, reply);
                ret = getSuperResolution();
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;
            case SETSUPERRESOLUTION:
                CHECK_INTERFACE(IPQService, data, reply);
                value = data.readInt32();
                ret = setSuperResolution(value);
                reply->writeInt32(0);
                reply->writeInt32(ret);
                return NO_ERROR;

            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }
};  // namespace android
