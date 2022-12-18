#ifndef _INFRARED_CLIENT_HEADER_
#define _INFRARED_CLIENT_HEADER_

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <binder/IMemory.h>
#include <binder/Parcel.h>
#include "IInfraredInterface.h"

namespace android {

class InfraredClient: public RefBase {

public:
    int32_t getInfraredState();
    void setInfraredState(int32_t);

private:
    sp<IInfraredInterface> getInfraredService();
    static sp<IInfraredInterface> infrared_service;
};

}

#endif
