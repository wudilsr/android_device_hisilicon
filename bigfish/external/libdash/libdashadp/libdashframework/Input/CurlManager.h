/*
 * DASHManager.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LIBDASH_FRAMEWORK_INPUT_CURLMANAGER_H_
#define LIBDASH_FRAMEWORK_INPUT_CURLMANAGER_H_

#include "config.h"

#include "curl/curl.h"

namespace libdash
{
    namespace framework
    {
        namespace input
        {
            class CurlManager
            {
                public:
                    CurlManager();
                    ~CurlManager();
                    bool    Init();
                    CURL*   GetCurlHandle();
                    CURLM*  GetCurlMultiHandle();
                    bool    DeInit();
                    bool    SetHttpHeaders(std::string &headers);
                    bool    ResetUserSettings();
                private:
                    CURL        *curl;
                    CURLM       *curlMulti;
                    curl_slist   *httpHeaders;
            };
        }
    }
}

#endif /* LIBDASH_FRAMEWORK_INPUT_DASHMANAGER_H_ */
