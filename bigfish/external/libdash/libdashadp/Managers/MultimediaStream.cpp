/*
 * MultimediaStream.cpp
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "MultimediaStream.h"

#include <stdio.h>

using namespace sampleplayer::managers;
using namespace sampleplayer::decoder;
using namespace libdash::framework::adaptation;
using namespace libdash::framework::input;
using namespace dash::mpd;

MultimediaStream::MultimediaStream  (IAdaptationSet *adaptationSet, IAdaptationLogic *logic, uint32_t bufferSize, void* breakpoint) :
                  adaptationSet     (adaptationSet),
                  logic             (logic),
                  bufferSize        (bufferSize),
                  eos               (false),
                  receiver          (NULL),
                  decodingThread    (NULL),
                  bandWidth         (0)
{
    this->Init(breakpoint);
}
MultimediaStream::~MultimediaStream ()
{
    this->Stop();
    delete(this->decodingThread);
    delete(this->receiver);
}

uint32_t    MultimediaStream::GetPosition               ()
{
    return this->receiver->GetPosition();
}
void        MultimediaStream::Init                      (void* breakpoint)
{
    this->receiver          = new DASHManager(this->bufferSize, this->logic, breakpoint);
    this->decodingThread    = new DecodingThread(this->receiver, this, this);

    this->receiver->AttachDownloadObserver(this);
}
bool        MultimediaStream::Start                     ()
{
    if(!this->StartDownload())
        return false;

    if(!this->StartDecoding())
        return false;

    return true;
}
bool        MultimediaStream::StartDecoding             ()
{
    if(!this->decodingThread->Start())
        return false;

    return true;
}
bool        MultimediaStream::StartDownload             ()
{
    if(!receiver->Start())
        return false;

    return true;
}
void        MultimediaStream::Stop                      ()
{
    this->StopDownload();
}
void        MultimediaStream::StopDownload              ()
{
    this->receiver->Stop();
}
void        MultimediaStream::Clear                     ()
{
    this->receiver->Clear();
}

void*      MultimediaStream::Pause                     ()
{
    return this->receiver->Pause();
}

bool      MultimediaStream::Resume                     (void *breakpoint)
{
    return this->receiver->Resume(breakpoint);
}

void        MultimediaStream::OnVideoDataAvailable      (const uint8_t **data, videoFrameProperties *props)
{
    //do nothing
}

void        MultimediaStream::OnAudioDataAvailable      (const uint8_t **data, audioFrameProperties *props)
{
    //do nothing
}

DecodingThread* MultimediaStream::GetDecodingThread()
{
    return this->decodingThread;
}

void        MultimediaStream::AttachStreamObserver      (IStreamObserver *observer)
{
    this->observers.push_back(observer);
}
void        MultimediaStream::AttachBufferObserver      (libdash::framework::buffer::IBufferObserver *observer)
{
    this->receiver->AttachBufferObserver(observer);
}
void        MultimediaStream::OnSegmentDecodingStarted  ()
{
    for(size_t i = 0; i < this->observers.size(); i++)
        this->observers.at(i)->OnVideoSegmentDecodingStarted();
}

void        MultimediaStream::OnSegmentDownloaded       ()
{
    for(size_t i = 0; i < this->observers.size(); i++)
        this->observers.at(i)->OnVideoSegmentDownloaded();
}

void        MultimediaStream::OnBandWidthChanged       (uint32_t bandWidth)
{
    this->bandWidth = bandWidth;
}

void        MultimediaStream::OnEosReached              ()
{
    this->eos = true;
}

bool        MultimediaStream::CheckEosReached           ()
{
    return this->eos;
}

uint32_t    MultimediaStream::GetBandWidth              ()
{
    return this->bandWidth;
}

DASHManager* MultimediaStream::GetReceiver              ()
{
    return this->receiver;
}

bool        MultimediaStream::SetHttpHeaders(std::string &headers)
{
    if (this->receiver != NULL)
        return this->receiver->SetHttpHeaders(headers);

    return false;
}

