#ifndef _INFRARED_SERVICE_HEADER_
#define _INFRARED_SERVICE_HEADER_

#include "IInfraredInterface.h"

namespace android {

class InfraredService : public BnInfraredInterface {

public:
    static void start();
    virtual void setInfraredState(int32_t s);
    virtual int32_t getInfraredState() {
        //XLOGD("InfraredService", "getInfraredState -- %d...", static_cast<int>(infrared_state));
        return infrared_state;
    }
    static int infraredState() {
       // XLOGD("InfraredService", "::infraredState -- %d...", static_cast<int>(infrared_state));
        return static_cast<int>(infrared_state);
    }

private:
    static int32_t infrared_state;
};

}
#endif
