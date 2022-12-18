#include <utils/Log.h>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/Parcel.h>
#include <binder/BpBinder.h>

#include "IInfraredInterface.h"

namespace android {

enum {
    SET_STATE = IBinder::FIRST_CALL_TRANSACTION,
    GET_STATE = IBinder::FIRST_CALL_TRANSACTION + 1
};

// -- Proxy
class BpInfraredInterface: public BpInterface<IInfraredInterface> {

public:
    BpInfraredInterface(const sp<IBinder>& impl) :
        BpInterface<IInfraredInterface>(impl) {}

    virtual void setInfraredState(int32_t s) {
        Parcel data, reply;
        data.writeInterfaceToken(IInfraredInterface::getInterfaceDescriptor());
        data.writeInt32(s);
        remote()->transact(SET_STATE, data, &reply);
    }

    virtual int32_t getInfraredState() {
        Parcel data, reply;
        data.writeInterfaceToken(IInfraredInterface::getInterfaceDescriptor());
        data.writeInt32(0);
        remote()->transact(GET_STATE, data, &reply);
        return reply.readInt32();
    }

};

IMPLEMENT_META_INTERFACE(InfraredInterface, "service.infrared");
// ----------------------------------------------------------------------------

// -- Service
status_t BnInfraredInterface::onTransact(uint32_t code,
                                const Parcel& data,
                                Parcel* reply,
                                uint32_t flags) {

    switch (code) {
        case GET_STATE: {
            CHECK_INTERFACE(IInfraredInterface, data, reply);
            int32_t ret;
            //data.readInt32();
            ret = getInfraredState();
            reply->writeInt32(ret);
            break;
        }
        case SET_STATE: {
            CHECK_INTERFACE(IInfraredInterface, data, reply);
            int32_t ret;
            ret = data.readInt32();
            setInfraredState(ret);
            break;
        }
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }

    return NO_ERROR;
}

};
