/*
 * MediaObject.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "MediaObject.h"

using namespace libdash::framework::input;

using namespace dash::mpd;
using namespace dash::network;

MediaObject::MediaObject    (ISegment *segment, IRepresentation *rep) :
             segment        (segment),
             rep            (rep),
             bandWidth      (0),
             bytesDownloaded(0),
             errorHappened  (false),
             downloadFinished(false),
             event(0),
             segType(MEDIA_SEGMENT_TYPE_NORMAL)
{
    InitializeConditionVariable (&this->stateChanged);
    InitializeCriticalSection   (&this->stateLock);
}

MediaObject::MediaObject    (ISegment *segment, IRepresentation *rep, MediaSegmentType segmentType) :
             segment        (segment),
             rep            (rep),
             bandWidth      (0),
             bytesDownloaded(0),
             errorHappened  (false),
             downloadFinished(false),
             event(0),
             segType(segmentType)
{
    InitializeConditionVariable (&this->stateChanged);
    InitializeCriticalSection   (&this->stateLock);
}

MediaObject::MediaObject    (int event) :
             segment        (NULL),
             rep            (NULL),
             bandWidth      (0),
             bytesDownloaded(0),
             errorHappened  (false),
             downloadFinished(false),
             segType(MEDIA_SEGMENT_TYPE_EVENT)
{
   // dash_log("[%s,%d] [%p] contruct with segment[%p]\n", __FUNCTION__, __LINE__, this, segment);
    InitializeConditionVariable (&this->stateChanged);
    InitializeCriticalSection   (&this->stateLock);
    this->event = event;
}

MediaObject::~MediaObject   ()
{
    if(this->state == IN_PROGRESS && this->segment != NULL)
    {
        this->segment->AbortDownload();
    }

    this->WaitFinished();

    if (this->segment != NULL)
    {
        this->segment->DetachDownloadObserver(this);
        delete this->segment;
    }

    DeleteConditionVariable (&this->stateChanged);
    DeleteCriticalSection   (&this->stateLock);
}

void    MediaObject::AbortDownload          ()
{
    if (this->segment != NULL)
        this->segment->AbortDownload();
    else
        this->state = ABORTED;
    //this->OnDownloadStateChanged(ABORTED);
}

void    MediaObject::PauseDownload          ()
{
    if (this->segment != NULL)
        this->segment->PauseDownload();
}

bool    MediaObject::StartDownload          ()
{
    if (this->segment == NULL)
    {
        EnterCriticalSection(&this->stateLock);
        //this->downloadFinished = true;
        this->state = COMPLETED;
        WakeAllConditionVariable(&this->stateChanged);
        LeaveCriticalSection(&this->stateLock);
        dash_log(DASH_LOG_INFO, "[%s,%d] [%p] event object download COMPLETED.\n", __FUNCTION__, __LINE__, this);
        return true;
    }

    this->segment->AttachDownloadObserver(this);
    return this->segment->StartDownload();
}

bool    MediaObject::StartDownload(void * easyHandle, void* multiHandle)
{
    bool ret;

    if (this->segment == NULL)
    {
        EnterCriticalSection(&this->stateLock);
       // this->downloadFinished = true;
        this->state = COMPLETED;
        WakeAllConditionVariable(&this->stateChanged);
        LeaveCriticalSection(&this->stateLock);
        dash_log(DASH_LOG_INFO, "[%s,%d] [%p] event object download COMPLETED.\n", __FUNCTION__, __LINE__, this);
        return true;
    }

    this->segment->AttachDownloadObserver(this);
    ret = this->segment->StartDownload(easyHandle, multiHandle);
    return ret;
}

void    MediaObject::AttachDownloadObserver  (IDownloadObserver *observer)
{
    if (this->segment != NULL && observer != NULL)
    {
        this->segment->AttachDownloadObserver(observer);
    }
}

void    MediaObject::DetachDownloadObserver  (IDownloadObserver *observer)
{
    if (this->segment != NULL && observer != NULL)
    {
        this->segment->DetachDownloadObserver(observer);
    }
}

void    MediaObject::WaitFinished           ()
{
    //dash_log("LOCK:%s %d\n", __FILE__, __LINE__);
    EnterCriticalSection(&this->stateLock);

    /*
     * 'state'            is internal state. Used for check segment state, changed by segment callback
     * 'downloadFinished' is external state. Used for tell media current download state, associated with 'state'
     *  Only when 'state' is COMPLETED or ABORTED and 'downloadFinished' is set true,
     *  we can free the resource that the media is used
     */
    while((!this->downloadFinished) || (this->state != COMPLETED && this->state != ABORTED))
        SleepConditionVariableCS(&this->stateChanged, &this->stateLock, INFINITE);

    LeaveCriticalSection(&this->stateLock);
    //dash_log("UNLOCK:%s %d this->state = %d\n", __FILE__, __LINE__, this->state);
}

bool    MediaObject::WaitDownloadFinished   ()
{
    //dash_log("LOCK:%s %d\n", __FILE__, __LINE__);
    EnterCriticalSection(&this->stateLock);

    if (this->state == COMPLETED || this->state == ABORTED)
        this->downloadFinished = true;

    LeaveCriticalSection(&this->stateLock);
    //dash_log("UNLOCK:%s %d this->state = %d\n", __FILE__, __LINE__, this->state);
    return this->downloadFinished;
}

void    MediaObject::OnDownloadStateChanged (DownloadState state)
{
    EnterCriticalSection(&this->stateLock);

    this->state = state;

    WakeAllConditionVariable(&this->stateChanged);
    LeaveCriticalSection(&this->stateLock);
}

void    MediaObject::OnDownloadRateChanged  (uint32_t bandWidth, uint64_t bytesDownloaded)
{
    this->bandWidth = bandWidth;
    this->bytesDownloaded = bytesDownloaded;
}

void MediaObject::OnBytesDownloaded(DownloadInfo &info)
{
}
void    MediaObject::OnErrorHappened        (bool errorHappened)
{
    this->errorHappened = errorHappened;
}

uint32_t    MediaObject::GetDownloadBandWidth()
{
    return this->bandWidth;
}

bool        MediaObject::ErrorHappened      ()
{
    return this->errorHappened;
}

int     MediaObject::Read                   (uint8_t *data, size_t len)
{
    if (this->segment == NULL)
        return this->event;

    return this->segment->Read(data, len);
}
int     MediaObject::Peek                   (uint8_t *data, size_t len)
{
    if (this->segment == NULL)
        return 0;

    return this->segment->Peek(data, len);
}

bool    MediaObject::CheckDownloadFinished()
{
    bool finished;

    EnterCriticalSection(&this->stateLock);
    finished = this->downloadFinished;
    LeaveCriticalSection(&this->stateLock);

    return finished;
}

void    MediaObject::SetDownloadFinished(bool value)
{
    EnterCriticalSection(&this->stateLock);

    this->downloadFinished = value;
    WakeAllConditionVariable(&this->stateChanged);

    LeaveCriticalSection(&this->stateLock);
}

dash::network::DownloadState MediaObject::GetDownloadState()
{
    return this->state;
}

int    MediaObject::PeekEvent()
{
    return this->event;
}

MediaSegmentType    MediaObject::GetSegmentType()
{
    return this->segType;
}

