/*
 * IMSPR.h
 *****************************************************************************

 *****************************************************************************/


#ifndef IMSPR_H_
#define IMSPR_H_

#include "config.h"

namespace dash
{
    namespace mpd
    {
        class IMSPR
        {
            public:
                virtual     std::string     GetPRO          ()  const = 0;
                virtual     std::string     GetIsEncrypted  ()  const = 0;
                virtual     std::string     GetIV_size      ()  const = 0;
                virtual     std::string     GetKID          ()  const = 0;
                virtual     ~IMSPR(){};
        };
    }
}

#endif /* IMSPR_H_ */
