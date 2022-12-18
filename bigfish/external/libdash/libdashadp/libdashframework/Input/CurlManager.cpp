/*
 * DASHManager.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "CurlManager.h"

using namespace libdash::framework::input;

CurlManager::CurlManager()
{
    this->httpHeaders = NULL;
}

CurlManager::~CurlManager()
{
    if (this->httpHeaders != NULL)
    {
       // dash_log("[%s,%d] free curl httpHeaders\n", __FUNCTION__, __LINE__);
        curl_slist_free_all(this->httpHeaders);
        this->httpHeaders = NULL;
    }
}

bool CurlManager::Init()
{
    if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d]CurlManager[%p] curl_global_init error\n", __FUNCTION__, __LINE__, this);
        return false;
    }

    this->curl = curl_easy_init();
    if (this->curl == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d]CurlManager[%p] curl_easy_init error\n", __FUNCTION__, __LINE__, this);
        curl_global_cleanup();
        return false;
    }

    this->curlMulti = curl_multi_init();
    if (this->curlMulti == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d]CurlManager[%p] curl_multi_init error\n", __FUNCTION__, __LINE__, this);
        curl_easy_cleanup(this->curl);
        this->curl = NULL;
        curl_global_cleanup();
        return false;
    }

    return true;
}

bool CurlManager::DeInit()
{
    if (this->curl != NULL)
    {
        curl_easy_cleanup(this->curl);
        this->curl = NULL;
    }

    if (this->curlMulti != NULL)
    {
        curl_multi_cleanup(this->curlMulti);
        this->curlMulti = NULL;
    }
    curl_global_cleanup();

    return true;
}

CURL*   CurlManager::GetCurlHandle()
{
    return this->curl;
}

CURLM*  CurlManager::GetCurlMultiHandle()
{
    return this->curlMulti;
}

bool CurlManager::SetHttpHeaders(std::string &headers)
{
    int start = 0, end = 0;
    struct curl_slist *slist=NULL;

    if (headers.length() <= 0)
        return false;

    do
    {
        end = headers.find("\r\n", start);
        if (end == std::string::npos)
        {
            if (headers.substr(start).length() > 0)
            {
                slist = curl_slist_append(slist, headers.substr(start).c_str());
                //dash_log("apend11:%s\n", headers.substr(start).c_str());
            }
            break;
        }
        else
        {
            if (headers.substr(start, (end - start)).length() > 0)
            {
                slist = curl_slist_append(slist, headers.substr(start, (end - start)).c_str());
                //dash_log("apend:%s\n", headers.substr(start, (end - start)).c_str());
            }
            start = end + 2;
            if (start >= headers.length())
                break;
        }
    } while (end  != std::string::npos);

    if (slist != NULL)
    {
        if (this->httpHeaders != NULL)
        {
            curl_slist_free_all(this->httpHeaders);
            this->httpHeaders = NULL;
        }
        this->httpHeaders = slist;
      //  curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, slist);
       // curl_slist_free_all(slist); /* free the list again */
    }

    return true;
}

bool CurlManager::ResetUserSettings(void)
{
    if (this->httpHeaders != NULL)
    {
        curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->httpHeaders);
    }

    return true;
}


