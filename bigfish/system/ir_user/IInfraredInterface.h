#ifndef _IINFRARED_INTERFACE_HEADER_
#define _IINFRARED_INTERFACE_HEADER_

#include <utils/RefBase.h>
#include <utils/Log.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android {

#define XLOGD(TAG,...) android_printLog(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define XLOGE(TAG,...) android_printLog(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define XLOGW(TAG,...) android_printLog(ANDROID_LOG_WARNING, TAG, __VA_ARGS__)

#ifndef CHECK_INTERFACE
#define CHECK_INTERFACE(interface, data, reply) \
            do { if (!data.enforceInterface(interface::getInterfaceDescriptor())) { \
                     XLOGE("InfraredInterface", "Incorrectly call routed to " #interface);\
                     return PERMISSION_DENIED; \
                 }\
            } while (0)
#endif

class IInfraredInterface: public IInterface {

public:
    DECLARE_META_INTERFACE(InfraredInterface);
    virtual void setInfraredState(int32_t s) = 0;
    virtual int32_t getInfraredState() = 0;
};

class BnInfraredInterface: public BnInterface<IInfraredInterface> {

public:
    virtual status_t onTransact(uint32_t code,
                                const Parcel& data,
                                Parcel* reply,
                                uint32_t flags = 0);
};

};

#endif
