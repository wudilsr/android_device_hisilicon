/*
 * AbstractChunk.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "AbstractChunk.h"
#include "../portable/MultiThreading.h"

using namespace dash::network;
using namespace dash::helpers;
using namespace dash::metrics;

uint32_t AbstractChunk::BLOCKSIZE = 32768;
//uint64_t AbstractChunk::DOWNLOADSIZE = 1 * 1024 * 1024;

AbstractChunk::AbstractChunk        ()  :
               connection           (NULL),
               dlThread             (NULL),
               bytesDownloaded      (0),
               bytesDownloadedThisTime  (0),
               responseCallBackTotalTime (0)
{
}

AbstractChunk::~AbstractChunk       ()
{
    this->AbortDownload();
//    WaitForSingleObject(this->dlThread, INFINITE);
//    DestroyThreadPortable(this->dlThread);
}

void    AbstractChunk::AbortDownload                ()
{
    this->blockStream.SetEOS(true);
    this->stateManager.CheckAndSet(IN_PROGRESS, REQUEST_ABORT);
    this->stateManager.CheckAndWait(REQUEST_ABORT, ABORTED);

    if (NULL != this->dlThread)
    {
        WaitForSingleObject(this->dlThread, INFINITE);
        DestroyThreadPortable(this->dlThread);
        this->dlThread = NULL;
    }
    this->blockStream.Clear();
}

void    AbstractChunk::PauseDownload                ()
{
  //  this->blockStream.SetEOS(true);

    this->stateManager.CheckAndSet(IN_PROGRESS, REQUEST_PAUSE);
    this->stateManager.CheckAndWait(REQUEST_PAUSE, PAUSED);

    if (NULL != this->dlThread)
    {
        WaitForSingleObject(this->dlThread, INFINITE);
        DestroyThreadPortable(this->dlThread);
        this->dlThread = NULL;
    }

   // this->blockStream.Clear();
}

bool    AbstractChunk::StartDownload          (void * easyHandle,void * multiHandle)
{

    if(this->stateManager.State() != NOT_STARTED &&
       this->stateManager.State() != PAUSED)//
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][%p] start download error state:%d, dlThread:%p\n",
         __FUNCTION__, __LINE__, this, this->stateManager.State(), this->dlThread);
        return false;
    }

    if (NULL != this->dlThread)
    {
        dash_log(DASH_LOG_WARNING, "[%s,%d][%p] thread not exit,state:%d, dlThread:%p\n",
        __FUNCTION__, __LINE__, this, this->stateManager.State(), this->dlThread);
        WaitForSingleObject(this->dlThread, INFINITE);
        DestroyThreadPortable(this->dlThread);
        this->dlThread = NULL;
    }

    this->curl = easyHandle;
    this->curlMulti = multiHandle;

    this->dlThread = CreateThreadPortable (DownloadInternalConnection, this);

    if(this->dlThread == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][%p] start download error ,create thread error!\n",
         __FUNCTION__, __LINE__, this);
        return false;
    }

    this->stateManager.State(IN_PROGRESS);

    return true;
}

bool    AbstractChunk::StartDownload                ()
{
    if(this->stateManager.State() != NOT_STARTED)
        return false;

    curl_global_init(CURL_GLOBAL_ALL);

    this->curl = curl_easy_init();
    curl_easy_setopt(this->curl, CURLOPT_URL, this->AbsoluteURI().c_str());
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, CurlResponseCallback);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, (void *)this);
    /* Debug Callback */
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(this->curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
    curl_easy_setopt(this->curl, CURLOPT_DEBUGDATA, (void *)this);

    if(this->HasByteRange())
        curl_easy_setopt(this->curl, CURLOPT_RANGE, this->Range().c_str());

    if (NULL != this->dlThread)
    {
        WaitForSingleObject(this->dlThread, INFINITE);
        DestroyThreadPortable(this->dlThread);
        this->dlThread = NULL;
    }

    this->dlThread = CreateThreadPortable (DownloadInternalConnection, this);

    if(this->dlThread == NULL)
        return false;

    this->stateManager.State(IN_PROGRESS);

    return true;
}
bool    AbstractChunk::StartDownload                (IConnection *connection)
{
    if(this->stateManager.State() != NOT_STARTED)
        return false;

    if (NULL != this->dlThread)
    {
        WaitForSingleObject(this->dlThread, INFINITE);
        DestroyThreadPortable(this->dlThread);
        this->dlThread = NULL;
    }

    this->dlThread = CreateThreadPortable (DownloadExternalConnection, this);

    if(this->dlThread == NULL)
        return false;

    this->stateManager.State(IN_PROGRESS);
    this->connection = connection;

    return true;
}
int     AbstractChunk::Read                         (uint8_t *data, size_t len)
{
    return this->blockStream.GetBytes(data, len);
}
int     AbstractChunk::Peek                         (uint8_t *data, size_t len)
{
    return this->blockStream.PeekBytes(data, len);
}
void    AbstractChunk::AttachDownloadObserver       (IDownloadObserver *observer)
{
    this->observers.push_back(observer);
    this->stateManager.Attach(observer);
}
void    AbstractChunk::DetachDownloadObserver       (IDownloadObserver *observer)
{
    uint32_t pos = -1;

    for(size_t i = 0; i < this->observers.size(); i++)
        if(this->observers.at(i) == observer)
            pos = i;

    if(pos != -1)
        this->observers.erase(this->observers.begin() + pos);

    this->stateManager.Detach(observer);
}
void*   AbstractChunk::DownloadExternalConnection   (void *abstractchunk)
{
    AbstractChunk   *chunk  = (AbstractChunk *) abstractchunk;
    block_t         *block  = AllocBlock(chunk->BLOCKSIZE);
    int             ret     = 0;

    do
    {
        ret = chunk->connection->Read(block->data, block->len, chunk);
        if(ret > 0)
        {
            block_t *streamblock = AllocBlock(ret);
            memcpy(streamblock->data, block->data, ret);
            chunk->blockStream.PushBack(streamblock);
            chunk->bytesDownloaded += ret;

            //chunk->NotifyDownloadRateChanged();
        }
        if(chunk->stateManager.State() == REQUEST_ABORT)
            ret = 0;

    }while(ret);

    DeleteBlock(block);

    if(chunk->stateManager.State() == REQUEST_ABORT)
        chunk->stateManager.State(ABORTED);
    else
        chunk->stateManager.State(COMPLETED);

    chunk->blockStream.SetEOS(true);

    return NULL;
}

void*   AbstractChunk::DownloadInternalConnection   (void *abstractchunk)
{
    AbstractChunk *chunk  = (AbstractChunk *) abstractchunk;
    int isRunning = 0;
    long httpCode = 0;
    uint64_t start, end, download_start, download_consume;
    uint64_t will_download_bytes = 0;
    int timeoutCount = 0;
    bool doReconnect = false;
    bool followlocation = true;
    DownloadInfo node;
    char download_url[1024];

   // uint64_t download_time = 0;
   // uint64_t download_size = 0;
   // std::deque<uint64_t>  downloadTime;
   // std::deque<uint64_t> downloadSize;

    chunk->blockStream.SetEOS(false);
    snprintf(download_url, sizeof(download_url), "%s", chunk->AbsoluteURI().c_str());
retry:
    curl_easy_setopt(chunk->curl, CURLOPT_URL, chunk->AbsoluteURI().c_str());
    curl_easy_setopt(chunk->curl, CURLOPT_HEADERFUNCTION, CurlHeaderCallback);
    curl_easy_setopt(chunk->curl, CURLOPT_HEADERDATA, (void *)chunk);
    curl_easy_setopt(chunk->curl, CURLOPT_WRITEFUNCTION, CurlResponseCallback);
    curl_easy_setopt(chunk->curl, CURLOPT_WRITEDATA, (void *)chunk);
    curl_easy_setopt(chunk->curl, CURLOPT_FOLLOWLOCATION, followlocation);

    /*
     * IF 'CURLOPT_NOSIGNAL' is set and libcurl has been built with the standard name resolver.
     * 'timeout' will not occur while the name resolve takes place, but will be safe in multi-thread.
     * Consider building libcurl with c-ares support to enable asynchronous DNS lookups,
     * which enables nice timeouts for name resolves without signals.
     */
    curl_easy_setopt(chunk->curl, CURLOPT_NOSIGNAL, 1L);

    // offset is used to do reconnect
    if (chunk->bytesDownloaded > 0)
    {
        curl_easy_setopt(chunk->curl, CURLOPT_RESUME_FROM_LARGE, chunk->bytesDownloaded);
    }
    else if(chunk->HasByteRange())
    {
        curl_easy_setopt(chunk->curl, CURLOPT_RANGE, chunk->Range().c_str());
        chunk->bytesDownloaded = chunk->StartByte();
        //-1 means there is no end range.such as "0-"
        if (chunk->EndByte() != (size_t)-1)
        {
            will_download_bytes = chunk->EndByte() - chunk->StartByte();
        }
    }

    if (will_download_bytes > 0)
    {
        dash_log(DASH_LOG_INFO, "[%p]download start, offset= %llu(to %llu), url = %s\n", chunk, chunk->bytesDownloaded, (will_download_bytes + chunk->bytesDownloaded),download_url);
    }
    else
    {
        dash_log(DASH_LOG_INFO, "[%p]download start, offset= %llu(to end), url = %s\n", chunk, chunk->bytesDownloaded,download_url);
    }

    curl_multi_add_handle(chunk->curlMulti, chunk->curl);

    doReconnect = false;
    timeoutCount = 0;
    start = dash_gettime();
    download_start = start;

    do
    {
        if (chunk->stateManager.State() == REQUEST_ABORT ||
            chunk->stateManager.State() == REQUEST_PAUSE)
        {
            dash_log(DASH_LOG_WARNING, "[%p]libcurl forced to quit, chunk offset:%llu\n", chunk, chunk->bytesDownloaded );
            break;
        }

        while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(chunk->curlMulti,&isRunning));

        if (chunk->bytesDownloadedThisTime > 0)
        {
            end = dash_gettime();
            node.consumedUS = (end - start);
            node.consumedUS -= chunk->responseCallBackTotalTime;
            node.downloadBytes = chunk->bytesDownloadedThisTime;
            chunk->bytesDownloaded  += chunk->bytesDownloadedThisTime;
            chunk->NotifyDownloadBytes(node);
            start = end;
            chunk->bytesDownloadedThisTime = 0;
        }
        chunk->responseCallBackTotalTime = 0;

        if (isRunning == 0)
            break;

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 100 * 1000;

        int max;
        fd_set fd_read;
        fd_set fd_write;
        fd_set fd_except;

        FD_ZERO(&fd_read);
        FD_ZERO(&fd_write);
        FD_ZERO(&fd_except);

        curl_multi_fdset(chunk->curlMulti, &fd_read, &fd_write, &fd_except,&max);
        int code = select(max + 1, &fd_read, &fd_write, &fd_except, &tv);
        if (-1 == code)
        {
            //TODO:Do smothing here...
            break;
        }
        else if (0 == code)
        {
            timeoutCount++;
            //dash_log("[%p]#####select code = %d timeoutCount=%d isRunning=%d\n", chunk, code, timeoutCount, isRunning);
            if (timeoutCount >= 150)
            {
                dash_log(DASH_LOG_WARNING, "[%s,%d]chunk[%p] download timeout,isRunning=%d, do reconnect.\n", __FUNCTION__, __LINE__, chunk, isRunning);
                doReconnect = true;
                break;
            }

            usleep(100 * 1000);
        }
        else
        {
            timeoutCount = 0;
        }

    }while(isRunning);

    curl_easy_getinfo(chunk->curl, CURLINFO_RESPONSE_CODE ,&httpCode);
    curl_multi_remove_handle(chunk->curlMulti, chunk->curl);
    curl_easy_reset(chunk->curl);//:TODO: this will clear curl settings, such as observers and http headers.
    if (0 == httpCode)
        doReconnect = true;
    //Warning:be careful with the order of the next sentences,used by multithreads.
    //&& mustn't call child class method or curl apis after CheckAndSet ABORTED/COMPLETED.
    if (!doReconnect)
    {
        chunk->stateManager.CheckAndSet(IN_PROGRESS, COMPLETED);
    }
    chunk->stateManager.CheckAndSet(REQUEST_ABORT, ABORTED);
    chunk->stateManager.CheckAndSet(REQUEST_PAUSE, PAUSED);
    if (doReconnect &&
        chunk->stateManager.State() != ABORTED &&
        chunk->stateManager.State() != PAUSED)
    {
        dash_log(DASH_LOG_WARNING, "[%p]doReconnect... offset=%llu\n", chunk, chunk->bytesDownloaded);
        goto retry;
    }

    download_consume = (dash_gettime() - download_start)/1000;

    if (chunk->stateManager.State() == ABORTED)
    {
        chunk->blockStream.SetEOS(true);
        dash_log(DASH_LOG_WARNING, "[%p]download aborted, bytesDownloaded = %lld, httpCode:%ld, url = %s\n", chunk, chunk->bytesDownloaded, httpCode, download_url);
    }
    else if (chunk->stateManager.State() == PAUSED)
    {
        dash_log(DASH_LOG_WARNING, "[%p]download paused, bytesDownloaded = %lld, httpCode:%ld, url = %s\n", chunk, chunk->bytesDownloaded, httpCode, download_url);
    }
    else if (chunk->stateManager.State() == COMPLETED)
    {
        dash_log(DASH_LOG_INFO, "[%p]download finished, consume %llu ms, bytesDownloaded = %lld, httpCode:%ld url = %s\n", chunk, download_consume, chunk->bytesDownloaded, httpCode, download_url);
        //chunk->stateManager.State(COMPLETED);
        chunk->blockStream.SetEOS(true);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%p]fatal, unknown download state %d, consume %llu ms,bytesDownloaded = %lld, httpCode:%ld url = %s\n", chunk, chunk->stateManager.State(), download_consume, chunk->bytesDownloaded, httpCode, download_url);
        chunk->stateManager.State(ABORTED);
        chunk->blockStream.SetEOS(true);
    }

    return NULL;
}

/*
void    AbstractChunk::NotifyDownloadRateChanged    ()
{
    for(size_t i = 0; i < this->observers.size(); i++)
        this->observers.at(i)->OnDownloadRateChanged(this->bandWidth, this->bytesDownloaded);
}
*/
void AbstractChunk::NotifyDownloadBytes(DownloadInfo &info)
{
    for(size_t i = 0; i < this->observers.size(); i++)
        this->observers.at(i)->OnBytesDownloaded(info);
}

void    AbstractChunk::NotifyErrorHappened          ()
{
    for(size_t i = 0; i < this->observers.size(); i++)
        this->observers.at(i)->OnErrorHappened(true);
}
size_t  AbstractChunk::CurlHeaderCallback(void * headerData,size_t size,size_t nmemb,void * userdata)
{
    size_t realsize = size * nmemb;
    //dash_log("\n%s\n", (char *)headerData);
    AbstractChunk *chunk = (AbstractChunk *)userdata;
    long httpCode = 0;

    curl_easy_getinfo(chunk->curl, CURLINFO_RESPONSE_CODE ,&httpCode);

    if (404 == httpCode)
        chunk->NotifyErrorHappened();
    if (httpCode == 0 || httpCode >= 400)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] chunk [%p] url='%s', download return http error code=%ld\n",
             __FUNCTION__, __LINE__, chunk, chunk->AbsoluteURI().c_str(), httpCode);
    }

    return realsize;
}

size_t  AbstractChunk::CurlResponseCallback         (void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    AbstractChunk *chunk = (AbstractChunk *)userp;
    uint64_t start, end;
    long httpCode = 0;

    if (chunk == NULL || chunk->curl == NULL)
        return 0;

    start = dash_gettime();
    if (chunk->stateManager.State() == REQUEST_ABORT ||
        chunk->stateManager.State() == REQUEST_PAUSE)
    {
        chunk->responseCallBackTotalTime = 0;
        return 0;
    }

    curl_easy_getinfo(chunk->curl, CURLINFO_RESPONSE_CODE ,&httpCode);
    //refer to rfc2616, httpCode Successful 2xx, Redirection 3xx ,Client Error 4xx, Server Error 5xx
    if (realsize <= 0 || (httpCode < 200 || httpCode >= 300) )
    {
        end = dash_gettime();
        chunk->responseCallBackTotalTime = (end - start);
        return realsize;
    }
    block_t *block = AllocBlock(realsize);
    if (block == NULL)
        return 0;

    memcpy(block->data, contents, realsize);
    chunk->blockStream.PushBack(block);

    end = dash_gettime();

    chunk->responseCallBackTotalTime = (end - start);
    chunk->bytesDownloadedThisTime = realsize;
    return realsize;
}

size_t  AbstractChunk::CurlDebugCallback            (CURL *url, curl_infotype infoType, char * data, size_t length, void *userdata)
{
    AbstractChunk   *chunk      = (AbstractChunk *)userdata;

    switch (infoType) {
        case CURLINFO_TEXT:
            break;
        case CURLINFO_HEADER_OUT:
            chunk->HandleHeaderOutCallback();
            break;
        case CURLINFO_HEADER_IN:
            chunk->HandleHeaderInCallback(std::string(data));
            break;
        case CURLINFO_DATA_IN:
            break;
        default:
            return 0;
    }
    return 0;
}
void    AbstractChunk::HandleHeaderOutCallback      ()
{
    HTTPTransaction *httpTransaction = new HTTPTransaction();

    httpTransaction->SetOriginalUrl(this->AbsoluteURI());
    httpTransaction->SetRange(this->Range());
    httpTransaction->SetType(this->GetType());
    httpTransaction->SetRequestSentTime(Time::GetCurrentUTCTimeStr());

    this->httpTransactions.push_back(httpTransaction);
}
void    AbstractChunk::HandleHeaderInCallback       (std::string data)
{
    if (data.substr(0,4) != "HTTP")
        return;

    HTTPTransaction *httpTransaction = this->httpTransactions.at(this->httpTransactions.size()-1);

    httpTransaction->SetResponseReceivedTime(Time::GetCurrentUTCTimeStr());
    httpTransaction->SetResponseCode(strtoul(data.substr(9,3).c_str(), NULL, 10));
}
const std::vector<ITCPConnection *>&    AbstractChunk::GetTCPConnectionList    () const
{
    return (std::vector<ITCPConnection *> &) this->tcpConnections;
}
const std::vector<IHTTPTransaction *>&  AbstractChunk::GetHTTPTransactionList  () const
{
    return (std::vector<IHTTPTransaction *> &) this->httpTransactions;
}
