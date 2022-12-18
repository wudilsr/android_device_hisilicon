/*
 * MediaObjectBuffer.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "MediaObjectBuffer.h"
#include <stdio.h>

using namespace libdash::framework::buffer;
using namespace libdash::framework::input;

using namespace dash::mpd;
using namespace dash::network;

#define BUFFER_MAX_SIZE     (4 * 1024 * 1024)

MediaObjectBuffer::MediaObjectBuffer    (uint32_t maxcapacity) :
                   eos                  (false),
                   maxcapacity          (maxcapacity),
                   bufferSize           (0)
{
    InitializeConditionVariable (&this->full);
    InitializeConditionVariable (&this->empty);
    InitializeCriticalSection   (&this->monitorMutex);
}
MediaObjectBuffer::~MediaObjectBuffer   ()
{
    this->Clear();

    DeleteConditionVariable (&this->full);
    DeleteConditionVariable (&this->empty);
    DeleteCriticalSection   (&this->monitorMutex);
}

bool            MediaObjectBuffer::PushBack         (MediaObject *media)
{
    EnterCriticalSection(&this->monitorMutex);

    while((this->mediaobjects.size() >= this->maxcapacity) && !this->eos)
        SleepConditionVariableCS(&this->empty, &this->monitorMutex, INFINITE);

    if(this->mediaobjects.size() >= this->maxcapacity)
    {
        LeaveCriticalSection(&this->monitorMutex);
        return false;
    }

    this->mediaobjects.push_back(media);
    //this->bufferSize += media->GetBytesDownloaded();

    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
    this->Notify();
    return true;
}

bool            MediaObjectBuffer::PushBack         (MediaObject *media, bool force)
{
    EnterCriticalSection(&this->monitorMutex);

    if (!force)
    {
        while((this->mediaobjects.size() >= this->maxcapacity) && !this->eos)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d][%p]MediaObjectBuffer full.....\n", __FUNCTION__, __LINE__, this);
            SleepConditionVariableCS(&this->empty, &this->monitorMutex, INFINITE);
        }

        if(this->mediaobjects.size() >= this->maxcapacity)
        {
            LeaveCriticalSection(&this->monitorMutex);
            return false;
        }
    }

    this->mediaobjects.push_back(media);
    //this->bufferSize += media->GetBytesDownloaded();

    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
    this->Notify();
    return true;
}

MediaObject*    MediaObjectBuffer::Front            ()
{
    EnterCriticalSection(&this->monitorMutex);

  //  while(this->mediaobjects.size() == 0 && !this->eos)
  ///      SleepConditionVariableCS(&this->full, &this->monitorMutex, INFINITE);

    if(this->mediaobjects.size() == 0)
    {
        LeaveCriticalSection(&this->monitorMutex);
        return NULL;
    }

    MediaObject *object = this->mediaobjects.front();
    LeaveCriticalSection(&this->monitorMutex);
    return object;
}
MediaObject*    MediaObjectBuffer::GetFront         ()
{
    EnterCriticalSection(&this->monitorMutex);

    while(this->mediaobjects.size() == 0 && !this->eos)
        SleepConditionVariableCS(&this->full, &this->monitorMutex, INFINITE);

    if(this->mediaobjects.size() == 0)
    {
        LeaveCriticalSection(&this->monitorMutex);
        return NULL;
    }

    MediaObject *object = this->mediaobjects.front();
    this->mediaobjects.pop_front();

    LeaveCriticalSection(&this->monitorMutex);

    return object;
}
uint32_t        MediaObjectBuffer::Length           ()
{
    EnterCriticalSection(&this->monitorMutex);

    uint32_t ret = this->mediaobjects.size();

    LeaveCriticalSection(&this->monitorMutex);

    return ret;
}
void            MediaObjectBuffer::PopFront         ()
{
    EnterCriticalSection(&this->monitorMutex);

    MediaObject * media = this->mediaobjects.front();
    delete media;
    this->mediaobjects.pop_front();

    WakeAllConditionVariable(&this->empty);
    LeaveCriticalSection(&this->monitorMutex);
    this->Notify();
}

MediaObject*    MediaObjectBuffer::Back            ()
{
    EnterCriticalSection(&this->monitorMutex);

 //   while(this->mediaobjects.size() == 0 && !this->eos)
 //       SleepConditionVariableCS(&this->full, &this->monitorMutex, INFINITE);

    if(this->mediaobjects.size() == 0)
    {
        LeaveCriticalSection(&this->monitorMutex);
        return NULL;
    }

    MediaObject *object = this->mediaobjects.back();
    LeaveCriticalSection(&this->monitorMutex);
    return object;
}

MediaObject*    MediaObjectBuffer::GetBack         ()
{
    EnterCriticalSection(&this->monitorMutex);

    while(this->mediaobjects.size() == 0 && !this->eos)
        SleepConditionVariableCS(&this->full, &this->monitorMutex, INFINITE);

    if(this->mediaobjects.size() == 0)
    {
        LeaveCriticalSection(&this->monitorMutex);
        return NULL;
    }

    MediaObject *object = this->mediaobjects.back();
    this->mediaobjects.pop_back();

    LeaveCriticalSection(&this->monitorMutex);

    return object;
}

void            MediaObjectBuffer::PopBack        ()
{
    EnterCriticalSection(&this->monitorMutex);

    MediaObject * media = this->mediaobjects.back();
    delete media;
    this->mediaobjects.pop_back();

    WakeAllConditionVariable(&this->empty);
    LeaveCriticalSection(&this->monitorMutex);
    this->Notify();
}

void            MediaObjectBuffer::SetEOS           (bool value)
{
    EnterCriticalSection(&this->monitorMutex);

    if (value)
    {
        for (size_t i = 0; i < this->mediaobjects.size(); i++)
            this->mediaobjects.at(i)->AbortDownload();
    }

    this->eos = value;

    WakeAllConditionVariable(&this->empty);
    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
}

void            MediaObjectBuffer::SetEOS           ()
{
    EnterCriticalSection(&this->monitorMutex);

    this->eos = true;

    WakeAllConditionVariable(&this->empty);
    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
}


void            MediaObjectBuffer::AttachObserver   (IBufferObserver *observer)
{
    this->observer.push_back(observer);
}
void            MediaObjectBuffer::Notify           ()
{
    for(size_t i = 0; i < this->observer.size(); i++)
        this->observer.at(i)->OnBufferStateChanged((int)((double)this->mediaobjects.size()/(double)this->maxcapacity*100.0));
}
void            MediaObjectBuffer::ClearTail        ()
{
    EnterCriticalSection(&this->monitorMutex);

    int size = this->mediaobjects.size() - 1;

    MediaObject* object = this->mediaobjects.front();
    this->mediaobjects.pop_front();
    for(int i=0; i < size; i++)
    {
        delete this->mediaobjects.front();
        this->mediaobjects.pop_front();
    }

    this->mediaobjects.push_back(object);
    WakeAllConditionVariable(&this->empty);
    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
}
void            MediaObjectBuffer::Clear            ()
{
    EnterCriticalSection(&this->monitorMutex);
    int len = this->mediaobjects.size();

    for(int i=0; i < len; i++)
    {
        this->mediaobjects.front()->AbortDownload();
        delete this->mediaobjects.front();
        this->mediaobjects.pop_front();
    }

    WakeAllConditionVariable(&this->empty);
    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
}
uint32_t        MediaObjectBuffer::Capacity         ()
{
    return this->maxcapacity;
}