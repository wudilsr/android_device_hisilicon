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

#include "DASHManager.h"

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

using namespace libdash::framework::input;
using namespace libdash::framework::adaptation;
using namespace libdash::framework::buffer;

using namespace dash;
using namespace dash::network;
using namespace dash::mpd;

uint32_t DASHManager::DOWNLOADSIZE = (512 * 1024);
DASHManager::DASHManager        (uint32_t maxcapacity, IAdaptationLogic* logic, void *breakpoint) :
              readSegmentNum  (0),
              maxcapacity       (maxcapacity),
              logic             (logic),
              isDownloading     (false),
              bufferingThread   (NULL),
              mCurlmanager      (NULL),
              state (DASH_MANAGER_STATE_STOPPED),
              downloadSegmentNum(0),
              breakpoint(NULL),
              pausedMedia(NULL),
              buffer(NULL),
              eventBuffer(NULL),
              errcode(0),
              totalDownloadBytes(0),
              totalConsumedUS(0),
              httpHeaders("")
{
    DASHManagerBreakPoint *bk = (DASHManagerBreakPoint *)breakpoint;
    bool resume = false;

    if (breakpoint != NULL)
    {
        if (bk->buffer == NULL)
        {
            dash_log(DASH_LOG_INFO, "[%s, %d] [%p]construct with breakpoint, downloadSegmentNum:%u, buffer is NULL.\n",
                __FUNCTION__, __LINE__, this, bk->downloadSegmentNum);
        }
        else
        {
            dash_log(DASH_LOG_INFO, "[%s, %d] [%p] construct with breakpoint, downloadSegmentNum:%u, buffer[%p] len:%u\n",
                __FUNCTION__, __LINE__, this, bk->downloadSegmentNum, bk->buffer, bk->buffer->Length());
        }
        this->buffer = bk->buffer;
        this->pausedMedia = bk->pausedMedia;
        this->logic->SetPosition(bk->downloadSegmentNum);
        this->readSegmentNum = bk->readSegmentNum;
        resume = true;
        delete bk;
    }

    if (this->buffer == NULL)
    {
        resume = false;
        this->buffer = new MediaObjectBuffer(this->maxcapacity);
        dash_log(DASH_LOG_INFO, "[%s, %d] construct with new MediaObjectBuffer[%p]\n", __FUNCTION__, __LINE__, this->buffer);
    }

    this->eventBuffer = new MediaObjectBuffer(this->maxcapacity);

    if (!resume)
    {
        this->readSegmentNum = this->logic->GetPosition();
    }
    this->downloadSegmentNum = this->logic->GetPosition();//next to download segment
    this->representationStreamType = ((ManualAdaptation *)logic)->GetRepresentationStreamType();

    dash_log(DASH_LOG_INFO, "[%s, %d] [%p] readSegmentNum:%u, downloadSegmentNum:%u\n",
        __FUNCTION__, __LINE__, this, this->readSegmentNum, this->downloadSegmentNum);
}

DASHManager::~DASHManager       ()
{
    this->Stop();

    if (this->buffer != NULL)
    {
        dash_log(DASH_LOG_INFO, "[%s,%d][%p]dash manager delete media buffer...\n", __FUNCTION__, __LINE__, this);
        delete this->buffer;
    }
    if (this->eventBuffer != NULL)
    {
        dash_log(DASH_LOG_INFO, "[%s,%d][%p]dash manager delete event buffer...\n", __FUNCTION__, __LINE__, this);
        delete this->eventBuffer;
    }
}

bool        DASHManager::Start                          ()
{
    if(this->isDownloading)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][%p] Warning:dash manager already started\n", __FUNCTION__, __LINE__, this);
        return false;
    }

    if (this->state != DASH_MANAGER_STATE_STOPPED)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][%p] Warning:dash manager start error, invalid state %d\n", __FUNCTION__, __LINE__, this, this->state);
        return false;
    }

    if (this->buffer == NULL || this->eventBuffer == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][%p] Warning:dash manager started error, buffer is null.\n", __FUNCTION__, __LINE__, this);
        return false;
    }

    this->mCurlmanager = new CurlManager();
    if (NULL == this->mCurlmanager)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] dash manager[%p] fatal error, create CurlManager error!\n", __FUNCTION__, __LINE__, this);
        return false;
    }

    if (false == this->mCurlmanager->Init())
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] dash manager[%p] fatal error, CurlManager Init error!\n", __FUNCTION__, __LINE__, this);
        this->mCurlmanager->DeInit();
        delete this->mCurlmanager;
        this->mCurlmanager = NULL;
        return false;
    }
    this->mCurlmanager->SetHttpHeaders(this->httpHeaders);

    this->isDownloading     = true;
    this->buffer->SetEOS(false);
    this->eventBuffer->SetEOS(false);
    this->bufferingThread   = CreateThreadPortable (DoBuffering, this);

    if(this->bufferingThread == NULL)
    {
        this->isDownloading = false;
        this->mCurlmanager->DeInit();
        delete this->mCurlmanager;
        dash_log(DASH_LOG_ERROR, "[%s,%d] dash manager[%p] fatal error, create buffering thread error!\n", __FUNCTION__, __LINE__, this);
        return false;
    }

    this->state = DASH_MANAGER_STATE_RUN;
    dash_log(DASH_LOG_INFO, "[%s,%d] dash manager[%p] start success!\n", __FUNCTION__, __LINE__, this);

    return true;
}

void        DASHManager::Stop                           ()
{
    if(!this->isDownloading)
    {
        //dash_log(DASH_LOG_WARNING, "[%s,%d][%p] Warning:dash manager already stopped\n", __FUNCTION__, __LINE__, this);
        return;
    }

    dash_log(DASH_LOG_INFO, "[%s,%d][%p]dash manager stopping...\n", __FUNCTION__, __LINE__, this);
    this->state = DASH_MANAGER_STATE_REQUEST_STOP;
    this->isDownloading = false;

    if (this->bufferingThread != NULL)
    {
        WaitForSingleObject(this->bufferingThread, INFINITE);
        DestroyThreadPortable(this->bufferingThread);
        this->bufferingThread = NULL;
    }

    if (this->pausedMedia != NULL)//avoid blocked
    {
        dash_log(DASH_LOG_INFO, "[%s,%d][%p]dash manager process paused object [%p]\n", __FUNCTION__, __LINE__, this, this->pausedMedia);
        this->pausedMedia->OnDownloadStateChanged(ABORTED);
        this->pausedMedia->SetDownloadFinished(true);
        this->pausedMedia = NULL;
    }

    if (this->buffer != NULL)
    {
        dash_log(DASH_LOG_INFO, "[%s,%d][%p]dash manager clear buffer\n", __FUNCTION__, __LINE__, this);
        this->buffer->SetEOS(true);//warning:this will clear buffer
        this->buffer->Clear();
    }

    if (this->eventBuffer != NULL)
    {
        dash_log(DASH_LOG_INFO, "[%s,%d][%p]dash manager clear eventBuffer\n", __FUNCTION__, __LINE__, this);
        this->eventBuffer->SetEOS(true);//warning:this will clear buffer
        this->eventBuffer->Clear();
    }

    dash_log(DASH_LOG_INFO, "[%s,%d][%p]dash manager delete curlmanager\n", __FUNCTION__, __LINE__, this);
    this->mCurlmanager->DeInit();
    delete this->mCurlmanager;
    this->downloadSegmentNum = 0;
    this->readSegmentNum = 0;
    this->logic->SetPosition(0);
    this->totalConsumedUS = 0;
    this->totalDownloadBytes = 0;
    this->downloadInfoNodes.clear();
    this->state = DASH_MANAGER_STATE_STOPPED;
    dash_log(DASH_LOG_INFO, "[%s,%d][%p]dash manager stopping done.\n", __FUNCTION__, __LINE__, this);
}
void        DASHManager::AttachBufferObserver           (IBufferObserver* observer)
{
    if (this->buffer != NULL)
        this->buffer->AttachObserver(observer);
}
void        DASHManager::AttachDownloadObserver         (IDASHReceiverObserver *observer)
{
    this->observers.push_back(observer);
}

int         DASHManager::Read                           (uint8_t *buf, int buf_size)
{
    int ret = 0;
    MediaObject *media;
    MediaSegmentType segType;

    /* FFMpeg callback that consumes data from the buffer for decoding */
    if (this->state == DASH_MANAGER_STATE_PAUSED ||
        this->state == DASH_MANAGER_STATE_REQUEST_PAUSE ||
        this->state == DASH_MANAGER_STATE_STOPPED ||
        this->state == DASH_MANAGER_STATE_REQUEST_STOP)
    {
      //  dash_log("[%s,%d] dash manager[%p] was paused ,can't Read\n", __FUNCTION__, __LINE__, this);
        return 0;
    }

    //check urgent event first
    media = this->eventBuffer->Front();
    if (media != NULL)
    {
        if (!media->CheckDownloadFinished())
            return 0;
        ret = media->Read(buf, buf_size);
        dash_log(DASH_LOG_INFO, "[%s,%d] this is a urgent event(%#x) segment\n", __FUNCTION__, __LINE__, ret);
        this->eventBuffer->PopFront();
        return ret;
    }

    media = this->buffer->Front();
    if(media == NULL)
    {
        if (this->state == DASH_MANAGER_STATE_EOS)
        {
            dash_log(DASH_LOG_INFO, "[%s,%d] no object left return EOS\n", __FUNCTION__, __LINE__);
            if (this->errcode != 0)
                return this->errcode;
            else
                return (LOGIC_EVENT_EOS);
        }
        dash_log(DASH_LOG_INFO, "[%s,%d] no object left return 0\n", __FUNCTION__, __LINE__);
        return 0;
    }

    ret = media->Read(buf, buf_size);
    if(ret == 0)
    {
        if (!media->CheckDownloadFinished())
            return 0;
        segType = media->GetSegmentType();
        this->buffer->PopFront();
    }
    //event wrapped in media object
    else if ((ret & LOGIC_EVENT_MASK) != 0)
    {
        if (!media->CheckDownloadFinished())
            return 0;
        dash_log(DASH_LOG_INFO, "[%s,%d] this is a event(%#x) segment\n", __FUNCTION__, __LINE__, ret);
        this->buffer->PopFront();
        return ret;
    }
    else
    {
        return ret;
    }

    if (segType != MEDIA_SEGMENT_TYPE_INIT &&
        segType != MEDIA_SEGMENT_TYPE_EVENT)
    {
        this->readSegmentNum++;
    }
    else
    {
        dash_log(DASH_LOG_INFO, "[%s,%d] this is a init or event segment %d\n", __FUNCTION__, __LINE__, segType);
    }

    this->NotifySegmentDecodingStarted();

    return this->Read(buf, buf_size);
}
void        DASHManager::Clear                          ()
{
    this->pausedMedia = NULL;
    if (this->buffer != NULL)
        this->buffer->ClearTail();
}
uint32_t    DASHManager::GetPosition                    ()
{
        return this->readSegmentNum;
}

void *    DASHManager::Pause                  ()
{
    if (this->breakpoint != NULL)
    {
        return this->breakpoint;
    }

    this->state = DASH_MANAGER_STATE_REQUEST_PAUSE;

    dash_log(DASH_LOG_INFO, "[%s,%d][%p] waiting for dash manager to be paused...\n", __FUNCTION__, __LINE__, this);
    while(this->state != DASH_MANAGER_STATE_PAUSED && this->isDownloading)
    {
        usleep(10000);
    }

    this->breakpoint = new DASHManagerBreakPoint();
    this->breakpoint->downloadSegmentNum = this->downloadSegmentNum;
    this->breakpoint->readSegmentNum = this->readSegmentNum;
    this->breakpoint->buffer = this->buffer;
    this->breakpoint->pausedMedia = this->pausedMedia;
    if (this->isDownloading)
    {
        dash_log(DASH_LOG_INFO, "[%s,%d][%p] dash manager paused, downloadSegmentNum:%u,readSegmentNum:%u, buffer[%p] len:%u\n",
            __FUNCTION__, __LINE__, this, this->breakpoint->downloadSegmentNum,
            this->readSegmentNum, this->buffer, this->buffer->Length());
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][%p] warning, dash manager stopped?downloadSegmentNum:%u, readSegmentNum:%u, buffer len:%u\n",
            __FUNCTION__, __LINE__, this, this->breakpoint->downloadSegmentNum,
            this->readSegmentNum, this->buffer, this->buffer->Length());
    }
    this->buffer = NULL;
    this->pausedMedia = NULL;

    return this->breakpoint;
}

bool    DASHManager::Resume                  (void *breakpoint)
{
    DASHManagerBreakPoint *bk = (DASHManagerBreakPoint *)breakpoint;

    if (breakpoint == NULL && this->breakpoint == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][%p] error, no breakpoint, failed to resume.\n", __FUNCTION__, __LINE__, this);
        return false;
    }

    if (!this->isDownloading || this->state != DASH_MANAGER_STATE_PAUSED || this->buffer != NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][%p] warning, wrong state when resume,isDownloading:%d, state:%d, buffer:%p.\n",
            __FUNCTION__, __LINE__, this, this->isDownloading, this->state, this->buffer);
        if (breakpoint)
            delete bk;

        if (this->breakpoint && this->breakpoint != breakpoint)
            delete this->breakpoint;
        this->breakpoint = NULL;

        return false;
    }

    if (breakpoint == NULL)
        bk= this->breakpoint;

    this->buffer = bk->buffer;
    this->pausedMedia = this->breakpoint->pausedMedia;
    this->downloadSegmentNum = bk->downloadSegmentNum;
    this->readSegmentNum = bk->readSegmentNum;
    this->logic->SetPosition(this->downloadSegmentNum);
    this->state = DASH_MANAGER_STATE_RUN;
    if (breakpoint)
        delete bk;

    if (this->breakpoint && this->breakpoint != breakpoint)
        delete this->breakpoint;
    this->breakpoint = NULL;

    dash_log(DASH_LOG_INFO, "[%s,%d][%p] resume with downloadSegmentNum:%u, readSegmentNum %u, buffer[%p] len %u success\n",
        __FUNCTION__, __LINE__, this, this->downloadSegmentNum, this->readSegmentNum, this->buffer, this->buffer->Length());

    return true;
}

void        DASHManager::NotifySegmentDownloaded        ()
{
    for(size_t i = 0; i < this->observers.size(); i++)
        this->observers.at(i)->OnSegmentDownloaded();
}
void        DASHManager::NotifySegmentDecodingStarted   ()
{
    for(size_t i = 0; i < this->observers.size(); i++)
        this->observers.at(i)->OnSegmentDecodingStarted();
}

void        DASHManager::NotifyBandwidth        (uint32_t bandWidth)
{
    for(size_t i = 0; i < this->observers.size(); i++)
        this->observers.at(i)->OnBandWidthChanged(bandWidth);
}
void        DASHManager::NotifyEos                      ()
{
    for(size_t i = 0; i < this->observers.size(); i++)
        this->observers.at(i)->OnEosReached();
}

bool DASHManager::DispatchMediaObject(MediaObject *media, bool force)
{
    int event;

    if (media == NULL)
        return false;

    event = media->PeekEvent();
    //some urgent event, we insert it int the eventBuffer.
    if ((event & (LOGIC_EVENT_MASK|LOGIC_ERROR_TYPE_MASK) ) \
        == (LOGIC_EVENT_ERROR|LOGIC_ERROR_TYPE_STREAM_NOTAVAILABLE))
    {
        dash_log(DASH_LOG_INFO, "[%p][%s,%d] pushback urgent event object[%p] to queue \n", this, __FUNCTION__, __LINE__, media);
        return this->eventBuffer->PushBack(media, true);
    }
    else
    {
        //avoid blocking
        if (!force && this->buffer->Length() >= this->buffer->Capacity())
        {
            return false;
        }

        return this->buffer->PushBack(media, force);
    }
}

void DASHManager::CheckEvent()
{
    bool ret;
    MediaObject *media = this->logic->GetSegment(SEG_TYPE_EVENT);

    if (media != NULL)
    {
        ret = this->DispatchMediaObject(media, true);
        if (true == ret)
        {
            //needn't to wait for event object to be download finished
            media->AttachDownloadObserver(this);
            media->StartDownload((void *)this->mCurlmanager->GetCurlHandle(), (void*)this->mCurlmanager->GetCurlMultiHandle());
            media->WaitDownloadFinished();
        }
        else
        {
            dash_log(DASH_LOG_ERROR, "[%p][%s,%d] pushback object[%p] to queue error\n", this, __FUNCTION__, __LINE__, media);
            media->AbortDownload();
            media->SetDownloadFinished(true);
            delete media;
            media = NULL;
        }
    }
}

/* Thread that does the buffering of segments */
void*   DASHManager::DoBuffering   (void *receiver)
{
    DASHManager *dashmanager = (DASHManager *) receiver;
    CurlManager *curlmanager = dashmanager->mCurlmanager;

    MediaObject *media = NULL;
    bool downloadPaused = false;
    bool bPausedSeg;
    int event;

    while (dashmanager->isDownloading)
    {
        dashmanager->CheckEvent();

        if (dashmanager->state == DASH_MANAGER_STATE_REQUEST_PAUSE ||
            dashmanager->state == DASH_MANAGER_STATE_PAUSED)
        {
            dashmanager->state = DASH_MANAGER_STATE_PAUSED;
            usleep(10000);
            continue;
        }
        else if (dashmanager->state == DASH_MANAGER_STATE_STOPPED ||
            dashmanager->state == DASH_MANAGER_STATE_REQUEST_STOP)
        {
            usleep(20000);
            continue;
        }

        bPausedSeg = false;
        //resume paused segment first
        if (dashmanager->pausedMedia != NULL)
        {
            media = dashmanager->pausedMedia;
            dashmanager->pausedMedia = NULL;
            bPausedSeg = true;
            dash_log(DASH_LOG_ERROR, "[%p][%s,%d] this object [%p] download resume from last time\n",
                dashmanager, __FUNCTION__, __LINE__, media);
        }
        else
        {
            //avoid blocked
            if (dashmanager->buffer->Length() >= dashmanager->buffer->Capacity())
            {
                usleep(10000);
                continue;
            }

            media = dashmanager->logic->GetSegment(SEG_TYPE_ALL);
            if (NULL == media)
            {
                usleep(20000);
                continue;
            }
        }

        media->AttachDownloadObserver(dashmanager);
        curlmanager->ResetUserSettings();
        if (!media->StartDownload((void *)curlmanager->GetCurlHandle(), (void*)curlmanager->GetCurlMultiHandle()))
        {
            dash_log(DASH_LOG_ERROR, "[%p][%s,%d] download object [%p] failed\n", dashmanager, __FUNCTION__, __LINE__, media);
        }

        if (!bPausedSeg)
        {
            if (true != dashmanager->DispatchMediaObject(media, false))
            {
                dash_log(DASH_LOG_ERROR, "[%p][%s,%d] dispatch object[%p] to queue error\n", dashmanager, __FUNCTION__, __LINE__, media);
                media->AbortDownload();
                media->SetDownloadFinished(true);
                delete media;
                media = NULL;
                break;
            }
        }

        while (!media->WaitDownloadFinished())
        {
            if (!dashmanager->isDownloading || dashmanager->state == DASH_MANAGER_STATE_REQUEST_PAUSE)
            {
                if (dashmanager->state != DASH_MANAGER_STATE_REQUEST_PAUSE)
                {
                 /*
                 * 'isDownloading' is used for fast quit
                 * We set finished here, so the reading-thread can break out
                 */
                    media->AbortDownload();
                    media->SetDownloadFinished(true);
                }
                else
                {
                    media->PauseDownload();
                    if (media->GetDownloadState() == PAUSED)
                    {
                        downloadPaused = true;
                        dashmanager->downloadSegmentNum = dashmanager->logic->GetPosition();
                        dash_log(DASH_LOG_ERROR, "[%p][%s,%d] object [%p] download paused\n", dashmanager, __FUNCTION__, __LINE__, media);
                    }
                }
                break;
            }

            usleep(SLEEP_TIME);
        }

        if (downloadPaused)
        {
            media->DetachDownloadObserver(dashmanager);
            dashmanager->pausedMedia = media;
            downloadPaused = false;
            continue;
        }
        else
        {
            //mustn't access media any more after download finished.
            media = NULL;
        }

        if (dashmanager->errcode != 0)
        {
            dash_log(DASH_LOG_ERROR, "[%p][%s,%d]dash manager break thread.\n", dashmanager, __FUNCTION__, __LINE__);
            break;
        }
        else
        {
            dashmanager->downloadSegmentNum = dashmanager->logic->GetPosition();
            dashmanager->NotifySegmentDownloaded();
        }
    }

    dash_log(DASH_LOG_INFO, "[%p][%s,%d] dash manager thread exit!\n", dashmanager, __FUNCTION__, __LINE__);
    dashmanager->state = DASH_MANAGER_STATE_EOS;
    dashmanager->isDownloading = false;
    if (dashmanager->buffer != NULL)
        dashmanager->buffer->SetEOS();
    if (dashmanager->eventBuffer != NULL)
        dashmanager->eventBuffer->SetEOS();
    //DestroyThreadPortable(dashmanager->bufferingThread);
    //dashmanager->bufferingThread = NULL;

    return NULL;
}

void    DASHManager::Interrupt()
{
    if (NULL == this->buffer)
        return;

    //this->buffer->SetEOS(true);
   // this->Stop();

    return;
}
bool    DASHManager::isLive()
{
    if (this->logic != NULL)
        return this->logic->isLive();

    dash_log(DASH_LOG_ERROR, "[%s,%d] error, logic is invalid, result of  isLive is not believeable.\n", __FUNCTION__, __LINE__);
    return false;
}

void    DASHManager::OnDownloadStateChanged (DownloadState state)
{
    //implmented in MediaObject
}

void  DASHManager::OnBytesDownloaded(DownloadInfo &info)
{
    DownloadInfo node;
    uint32_t bw;

    if (info.consumedUS > 0 && info.downloadBytes > 0)
    {
        this->totalDownloadBytes += info.downloadBytes;
        this->totalConsumedUS += info.consumedUS;
        this->downloadInfoNodes.push_back(info);
    }

    if (this->totalDownloadBytes > 0 && this->totalConsumedUS > 0)
    {
        bw = (this->totalDownloadBytes * 8ULL * 1000000ULL / this->totalConsumedUS);
        this->NotifyBandwidth(bw);
    //    dash_log("[%s,%d][%p][BW] bw changed to %u, total(%u, %u),cur(%u,%u)\n",
    //        __FUNCTION__, __LINE__, this, bw, this->totalDownloadBytes, this->totalConsumedUS , info.downloadBytes, info.consumedUS);
    }

    while(this->totalDownloadBytes >= this->DOWNLOADSIZE)
    {
       node = this->downloadInfoNodes.front();
       this->totalConsumedUS -= node.consumedUS;
       this->totalDownloadBytes -= node.downloadBytes;
       this->downloadInfoNodes.pop_front();
    }

}

void    DASHManager::OnErrorHappened        (bool errorHappened)
{
    //also implmented in MediaObject
    this->errcode = (LOGIC_EVENT_ERROR | LOGIC_ERROR_TYPE_HTTP | (404 & LOGIC_ERROR_CODE_MASK));
    dash_log(DASH_LOG_ERROR, "[%p][%s,%d] dash manager error happened!\n", this, __FUNCTION__, __LINE__);
}

bool    DASHManager::SetHttpHeaders(std::string &headers)
{
    this->httpHeaders = headers;

    return true;
}

