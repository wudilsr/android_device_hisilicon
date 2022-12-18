#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <cutils/log.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <utils/String16.h>

#include "InfraredService.h"

namespace android {

int32_t InfraredService::infrared_state = 0;

void InfraredService::start() {
    XLOGD("InfraredService", "start...");
    defaultServiceManager()->addService(
                        String16("service.infrared"), new InfraredService());
}

void InfraredService::setInfraredState(int32_t s) {
    //XLOGD("InfraredService", "setInfraredState -- %d...", static_cast<int>(s));
    infrared_state = s;
}

}
