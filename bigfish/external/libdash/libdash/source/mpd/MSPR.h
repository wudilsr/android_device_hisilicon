/*
 * Descriptor.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef MSPR_H_
#define MSPR_H_

#include "IMSPR.h"
#include "config.h"

namespace dash
{
    namespace mpd
    {
        class MSPR : IMSPR
        {
            public:
                ~MSPR           ();
                MSPR            ();

                void    SetPRO          (const std::string& pro);
                void    SetIsEncrypted  (const std::string& isEncrypted);
                void    SetIV_size      (const std::string& iv_size);
                void    SetKID          (const std::string& kid);

                std::string     GetPRO          ()  const;
                std::string     GetIsEncrypted  ()  const;
                std::string     GetIV_size      ()  const;
                std::string     GetKID          ()  const;

            private:
                std::string  pro;
                std::string  isEncrypted;
                std::string  iv_size;
                std::string  kid;
        };
    }
}

#endif /* MSPR_H_ */
