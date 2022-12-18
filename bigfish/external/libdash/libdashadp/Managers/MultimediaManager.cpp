/*
 * MultimediaManager.cpp
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/
#include "MultimediaManager.h"

using namespace libdash::framework::adaptation;
using namespace libdash::framework::buffer;
using namespace sampleplayer::managers;
using namespace dash::mpd;
using namespace libdash::framework::mpd;

#define SEGMENTBUFFER_SIZE  3
#define DASH_TIME_UNIT      1000000

MultimediaManager::MultimediaManager            (void *breakpoints) :
                   mpd                          (NULL),
                   period                       (NULL),
                   videoAdaptationSet           (NULL),
                   videoRepresentation          (NULL),
                   videoLogic                   (NULL),
                   videoStream                  (NULL),
                   audioAdaptationSet           (NULL),
                   audioRepresentation          (NULL),
                   audioLogic                   (NULL),
                   audioStream                  (NULL),
                   subtitleAdaptationSet        (NULL),
                   subtitleRepresentation       (NULL),
                   subtitleLogic                (NULL),
                   subtitleStream               (NULL),
                   isStarted                    (false),
                   isLive                       (false),
                   isISOFF                      (false),
                   indexSegmentURL              (""),
                   segmentURL                   (""),
                   videoRating                  (""),
                   framesDisplayed              (0),
                   videoSegmentsDownloaded      (0),
                   videoSegmentsDecodingStarted (0),
                   videoAdaptationSetIndex      (0),
                   audioAdaptationSetIndex      (0),
                   subtitleAdaptationSetIndex   (0),
                   breakpoints(NULL),
                   httpHeaders("")
{
    InitializeCriticalSection (&this->monitorMutex);
    this->manager = CreateDashManager();
    if (breakpoints)
    {
        this->breakpoints = (BreakPoints *)breakpoints;
    }
}

MultimediaManager::~MultimediaManager           ()
{
    this->Destroy();

    delete this->manager;
    this->videoStreams.clear();
    this->audioStreams.clear();
    this->subtitleStreams.clear();
    this->videoLogics.clear();
    this->audioLogics.clear();
    this->subtitleLogics.clear();
    this->videoAdaptationSets.clear();
    this->audioAdaptationSets.clear();
    this->subtitleAdaptationSets.clear();
    this->videoBufferObservers.clear();
    this->videoPosition.clear();
    this->audioPosition.clear();
    this->subtitlePosition.clear();
    this->videoRepresentationIndexes.clear();
    this->audioRepresentationIndexes.clear();
    this->subtitleRepresentationIndexes.clear();
    this->videoForceInvokeInitSeg.clear();
    this->audioForceInvokeInitSeg.clear();
    this->subtitleForceInvokeInitSeg.clear();
    this->videoState.clear();
    this->audioState.clear();
    this->subtitleState.clear();

    delete this->mpd;

    DeleteCriticalSection (&this->monitorMutex);
}

IMPD*   MultimediaManager::GetMPD                           ()
{
    return this->mpd;
}

int       MultimediaManager::InitAdaptionSets()
{
    int i;

    GetVideoAdaptationSetNum();
    this->videoPosition.resize(this->videoAdaptationSets.size());
    for (i = 0; i < this->videoAdaptationSets.size(); i++)
        this->videoPosition.at(i) = 0;

    GetAudioAdaptationSetNum();
    this->audioPosition.resize(this->audioAdaptationSets.size());
    for (i = 0; i < this->audioAdaptationSets.size(); i++)
        this->audioPosition.at(i) = 0;

    GetSubtitleAdaptationSetNum();
    this->subtitlePosition.resize(this->subtitleAdaptationSets.size());
    for (i = 0; i < this->subtitleAdaptationSets.size(); i++)
        this->subtitlePosition.at(i) = 0;

    this->videoRepresentationIndexes.resize(this->videoAdaptationSets.size());
    for (i = 0; i < this->videoAdaptationSets.size(); i++)
        this->videoRepresentationIndexes.at(i) = 0;

    this->audioRepresentationIndexes.resize(this->audioAdaptationSets.size());
    for (i = 0; i < this->audioAdaptationSets.size(); i++)
        this->audioRepresentationIndexes.at(i) = 0;

    this->subtitleRepresentationIndexes.resize(this->subtitleAdaptationSets.size());
    for (i = 0; i < this->subtitleAdaptationSets.size(); i++)
        this->subtitleRepresentationIndexes.at(i) = 0;

    this->videoForceInvokeInitSeg.resize(this->videoAdaptationSets.size());
    for (i = 0; i < this->videoForceInvokeInitSeg.size(); i++)
        this->videoForceInvokeInitSeg.at(i) = false;

    this->audioForceInvokeInitSeg.resize(this->audioAdaptationSets.size());
    for (i = 0; i < this->audioForceInvokeInitSeg.size(); i++)
        this->audioForceInvokeInitSeg.at(i) = false;

    this->subtitleForceInvokeInitSeg.resize(this->subtitleAdaptationSets.size());
    for (i = 0; i < this->subtitleForceInvokeInitSeg.size(); i++)
        this->subtitleForceInvokeInitSeg.at(i) = false;

    this->videoState.resize(this->videoAdaptationSets.size());
    for (i = 0; i < this->videoState.size(); i++)
        this->videoState.at(i) = MANAGER_STATE_IDLE;

    this->audioState.resize(this->audioAdaptationSets.size());
    for (i = 0; i < this->audioState.size(); i++)
        this->audioState.at(i) = MANAGER_STATE_IDLE;

    this->subtitleState.resize(this->subtitleAdaptationSets.size());
    for (i = 0; i < this->subtitleState.size(); i++)
        this->subtitleState.at(i) = MANAGER_STATE_IDLE;

    _IsISOFF();//depend on InitAdaptionSets();

    return 0;
}

bool    MultimediaManager::Init                             (const std::string& url, int *err)
{
    std::string fileUrl = url;
    EnterCriticalSection(&this->monitorMutex);

    if (this->mpd != NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] MultimediaManager have been inited!\n", __FUNCTION__, __LINE__);
        LeaveCriticalSection(&this->monitorMutex);
        return true;
    }

    fileUrl.append(HISIURL_END);
    if (this->httpHeaders.length() > 0)
    {
        fileUrl.append(HISIURL_HTTPHEADERS);
        fileUrl.append(this->httpHeaders);
    }

    this->mpd = this->manager->Open((char *)fileUrl.c_str(), err);
    if(this->mpd == NULL)
    {
        dash_log(DASH_LOG_ERROR, "Open mpd file failed, error %d\n", *err);
        LeaveCriticalSection(&this->monitorMutex);
        return false;
    }

    _SetCurrentPeriod(this->mpd->GetPeriods().at(0));

    IsLive();
    InitAdaptionSets();

    LeaveCriticalSection(&this->monitorMutex);

    return true;
}

bool    MultimediaManager::Create ()
{
    EnterCriticalSection(&this->monitorMutex);

    if ((this->videoState.size() > 0 && this->videoState.at(0) != MANAGER_STATE_IDLE) ||
        (this->audioState.size() > 0 && this->audioState.at(0) != MANAGER_STATE_IDLE) ||
        (this->subtitleState.size() > 0 && this->subtitleState.at(0) != MANAGER_STATE_IDLE))
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] logic and streams have been created, must destroy them first!\n", __FUNCTION__, __LINE__);
        LeaveCriticalSection(&this->monitorMutex);
        return false;
    }

    InitVideoRendering();
    if (this->IsISOFF())
    {
        InitAudioPlayback();
        InitSubtitleParsing();
    }

    //breakpoints should have been used and cleared when create logci/stream.
    if (this->breakpoints)
    {
        if (this->breakpoints->videoBreakPoints.size() ||
            this->breakpoints->audioBreakPoints.size() ||
            this->breakpoints->subtitleBreakPoints.size())
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] fatal error, breakpoints not clear, v:%u, a:%u, s:%u\n",
                __FUNCTION__, __LINE__, this->breakpoints->videoBreakPoints.size(),
                this->breakpoints->audioBreakPoints.size(), this->breakpoints->subtitleBreakPoints.size());
        }

        delete this->breakpoints;
        this->breakpoints = NULL;
    }

    LeaveCriticalSection(&this->monitorMutex);

    return true;
}

void    MultimediaManager::Destroy                             ()
{
    EnterCriticalSection(&this->monitorMutex);

    this->DestroyVideo();
    this->DestroyAudio();
    this->DestroySubtitle();
    LeaveCriticalSection(&this->monitorMutex);
}
void    MultimediaManager::DestroyVideo                        ()
{
    if (this->videoStreams.empty())
        return;

    for (int i = 0; i < this->videoStreams.size(); i ++)
    {
        delete this->videoStreams.at(i);
        delete this->videoLogics.at(i);

        this->videoStreams.at(i) = NULL;
        this->videoLogics.at(i) = NULL;
        this->videoState.at(i) = MANAGER_STATE_IDLE;
    }
    this->videoStreams.clear();
    this->videoLogics.clear();
}
void    MultimediaManager::DestroyAudio                        ()
{
    if (this->audioStreams.empty())
        return;

    for (int i = 0; i < this->audioStreams.size(); i ++)
    {
        delete this->audioStreams.at(i);
        delete this->audioLogics.at(i);

        this->audioStreams.at(i) = NULL;
        this->audioLogics.at(i) = NULL;
        this->audioState.at(i) = MANAGER_STATE_IDLE;
    }
    this->audioStreams.clear();
    this->audioLogics.clear();
}

void    MultimediaManager::DestroySubtitle                     ()
{
    if (this->subtitleStreams.empty())
        return;

    for (int i = 0; i < this->subtitleStreams.size(); i ++)
    {
        delete this->subtitleStreams.at(i);
        delete this->subtitleLogics.at(i);

        this->subtitleStreams.at(i) = NULL;
        this->subtitleLogics.at(i) = NULL;
        this->audioState.at(i) = MANAGER_STATE_IDLE;
    }
    this->subtitleStreams.clear();
    this->subtitleLogics.clear();
}
void    MultimediaManager::Start                            ()
{
    bool started = true;

    EnterCriticalSection(&this->monitorMutex);

    if (!this->videoAdaptationSets.empty())
    {
        for (int i = 0; i < videoStreams.size(); i++)
        {
            if (this->videoState.at(i) == MANAGER_STATE_STOPPED)
            {
                if (this->videoStreams.at(i)->Start())
                {
                    this->videoState.at(i) = MANAGER_STATE_RUNNING;
                }
                else
                {
                    started = false;
                    dash_log(DASH_LOG_ERROR, "[%s,%d] video stream[%d]  start error\n", __FUNCTION__, __LINE__, i);
                }
            }
            else if (this->videoState.at(i) != MANAGER_STATE_RUNNING)
            {
                started = false;
                dash_log(DASH_LOG_ERROR, "[%s,%d] video stream[%d] start error, wrong state %d\n", __FUNCTION__, __LINE__, i, this->videoState.at(i));
            }
        }
    }

    if (!this->audioAdaptationSets.empty() && (true == this->isISOFF))
    {
        for (int i = 0; i < audioStreams.size(); i++)
        {
            if (this->audioState.at(i) == MANAGER_STATE_STOPPED)
            {
                if (this->audioStreams.at(i)->Start())
                {
                    this->audioState.at(i) = MANAGER_STATE_RUNNING;
                }
                else
                {
                    started = false;
                    dash_log(DASH_LOG_ERROR, "[%s,%d] audio stream[%d] start error\n", __FUNCTION__, __LINE__, i);
                }
            }
            else if (this->audioState.at(i) != MANAGER_STATE_RUNNING)
            {
                started = false;
                dash_log(DASH_LOG_ERROR, "[%s,%d] audio stream[%d] start error, wrong state %d\n", __FUNCTION__, __LINE__, i, this->audioState.at(i));
            }
        }
    }

    if (!this->subtitleAdaptationSets.empty() && (true == this->isISOFF))
    {
        for (int i = 0; i < subtitleStreams.size(); i++)
        {
            if (this->subtitleState.at(i) == MANAGER_STATE_STOPPED)
            {
                if (this->subtitleStreams.at(i)->Start())
                {
                    this->subtitleState.at(i) = MANAGER_STATE_RUNNING;
                }
                else
                {
                    started = false;
                    dash_log(DASH_LOG_ERROR, "[%s,%d] subtitle stream[%d] start error\n", __FUNCTION__, __LINE__, i);
                }
            }
            else if (this->subtitleState.at(i) != MANAGER_STATE_RUNNING)
            {
                started = false;
                dash_log(DASH_LOG_ERROR, "[%s,%d] subtitle stream start error, wrong state %d\n", __FUNCTION__, __LINE__, this->subtitleState.at(i));
            }
        }
    }

    this->isStarted = started;

    LeaveCriticalSection(&this->monitorMutex);
}

void    MultimediaManager::Stop                            ()
{
    EnterCriticalSection(&this->monitorMutex);

    if (!this->videoAdaptationSets.empty())
    {
        for (int i = 0; i < videoStreams.size(); i++)
        {
            if (this->videoState.at(i) == MANAGER_STATE_RUNNING)
            {
                this->videoStreams.at(i)->Stop();
                this->videoState.at(i) = MANAGER_STATE_STOPPED;
            }
            else if (this->videoState.at(i) != MANAGER_STATE_STOPPED)
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d] video stream[%d] stop error, wrong state %d\n", __FUNCTION__, __LINE__, i, this->videoState.at(i));
            }
        }
    }

    if (!this->audioAdaptationSets.empty() && (true == this->isISOFF))
    {
        for (int i = 0; i < audioStreams.size(); i++)
        {
            if (this->audioState.at(i) == MANAGER_STATE_RUNNING)
            {
                this->audioStreams.at(i)->Stop();
                this->audioState.at(i) = MANAGER_STATE_STOPPED;
            }
            else if (this->audioState.at(i) != MANAGER_STATE_STOPPED)
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d] audio stream[%d] stop  error, wrong state %d\n", __FUNCTION__, __LINE__, i, this->audioState.at(i));
            }
        }
    }

    if (!this->subtitleAdaptationSets.empty() && (true == this->isISOFF))
    {
        for (int i = 0; i < subtitleStreams.size(); i++)
        {
            if (this->subtitleState.at(i) == MANAGER_STATE_RUNNING)
            {
                this->subtitleStreams.at(i)->Stop();
                this->subtitleState.at(i) = MANAGER_STATE_STOPPED;
            }
            else if (this->subtitleState.at(i) != MANAGER_STATE_RUNNING)
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d] subtitle stream stop error, wrong state %d\n", __FUNCTION__, __LINE__, this->subtitleState.at(i));
            }
        }
    }

    this->isStarted = false;

    LeaveCriticalSection(&this->monitorMutex);
}

bool    MultimediaManager::StartVideo(int adaptationSetIndex)
{
    bool started = false;

    EnterCriticalSection(&this->monitorMutex);

    if (this->videoStreams.size() <= adaptationSetIndex ||
        this->videoAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->videoStreams.size(), this->videoAdaptationSets.size());
        LeaveCriticalSection(&this->monitorMutex);
        return false;
    }

    if (this->videoState.at(adaptationSetIndex) == MANAGER_STATE_STOPPED)
    {
        started = this->videoStreams.at(adaptationSetIndex)->Start();
        if (started)
        {
            this->videoState.at(adaptationSetIndex) = MANAGER_STATE_RUNNING;
        }
    }
    else if (this->videoState.at(adaptationSetIndex) == MANAGER_STATE_RUNNING)
    {
        started = true;
        dash_log(DASH_LOG_WARNING, "[%s,%d] warning, video stream [%d] is already running!\n", __FUNCTION__, __LINE__, adaptationSetIndex);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] warning, video stream [%d] start error, wrong state %d!\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->videoState.at(adaptationSetIndex));
    }
    LeaveCriticalSection(&this->monitorMutex);

    return started;
}

void    MultimediaManager::StopVideo(int adaptationSetIndex)
{
    EnterCriticalSection(&this->monitorMutex);

    if (this->videoStreams.size() <= adaptationSetIndex ||
        this->videoAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->videoStreams.size(), this->videoAdaptationSets.size());
        LeaveCriticalSection(&this->monitorMutex);
        return;
    }

    if (this->videoState.at(adaptationSetIndex) == MANAGER_STATE_RUNNING)
    {
        this->videoStreams.at(adaptationSetIndex)->Stop();
        this->videoState.at(adaptationSetIndex) = MANAGER_STATE_STOPPED;
    }
    else if (this->videoState.at(adaptationSetIndex) == MANAGER_STATE_STOPPED)
    {
        dash_log(DASH_LOG_WARNING, "[%s,%d] warning, video stream [%d] is already stopped!\n", __FUNCTION__, __LINE__, adaptationSetIndex);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] warning, video stream [%d] stop error, wrong state %d!\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->videoState.at(adaptationSetIndex));
    }
    LeaveCriticalSection(&this->monitorMutex);

    return;
}

bool    MultimediaManager::StartAudio(int adaptationSetIndex)
{
    bool started = false;

    EnterCriticalSection(&this->monitorMutex);

    if (this->audioStreams.size() <= adaptationSetIndex ||
        this->audioAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->audioStreams.size(), this->audioAdaptationSets.size());
        LeaveCriticalSection(&this->monitorMutex);
        return false;
    }

    if (this->audioState.at(adaptationSetIndex) == MANAGER_STATE_STOPPED)
    {
        started = this->audioStreams.at(adaptationSetIndex)->Start();
        if (started)
        {
            this->audioState.at(adaptationSetIndex) = MANAGER_STATE_RUNNING;
        }
    }
    else if (this->audioState.at(adaptationSetIndex) == MANAGER_STATE_RUNNING)
    {
        started = true;
        dash_log(DASH_LOG_WARNING, "[%s,%d] warning, audio stream [%d] is already running!\n", __FUNCTION__, __LINE__, adaptationSetIndex);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] warning, audio stream [%d] start error, wrong state %d!\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->audioState.at(adaptationSetIndex));
    }
    LeaveCriticalSection(&this->monitorMutex);

    return started;
}

void    MultimediaManager::StopAudio(int adaptationSetIndex)
{
    EnterCriticalSection(&this->monitorMutex);

    if (this->audioStreams.size() <= adaptationSetIndex ||
        this->audioAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->audioStreams.size(), this->audioAdaptationSets.size());
        LeaveCriticalSection(&this->monitorMutex);
        return;
    }

    if (this->audioState.at(adaptationSetIndex) == MANAGER_STATE_RUNNING)
    {
        this->audioStreams.at(adaptationSetIndex)->Stop();
        this->audioState.at(adaptationSetIndex) = MANAGER_STATE_STOPPED;
    }
    else if (this->audioState.at(adaptationSetIndex) == MANAGER_STATE_STOPPED)
    {
        dash_log(DASH_LOG_WARNING, "[%s,%d] warning, audio stream [%d] is already stopped!\n", __FUNCTION__, __LINE__, adaptationSetIndex);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] warning, audio stream [%d] stop error, wrong state %d!\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->audioState.at(adaptationSetIndex));
    }
    LeaveCriticalSection(&this->monitorMutex);

    return;
}

bool    MultimediaManager::StartSubtitle(int adaptationSetIndex)
{
    bool started = false;

    EnterCriticalSection(&this->monitorMutex);

    if (this->subtitleStreams.size() <= adaptationSetIndex ||
        this->subtitleAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleStreams.size(), this->subtitleAdaptationSets.size());
        LeaveCriticalSection(&this->monitorMutex);
        return false;
    }

    if (this->subtitleState.at(adaptationSetIndex) == MANAGER_STATE_STOPPED)
    {
        started = this->subtitleStreams.at(adaptationSetIndex)->Start();
        if (started)
        {
            this->videoState.at(adaptationSetIndex) = MANAGER_STATE_RUNNING;
        }
    }
    else if (this->subtitleState.at(adaptationSetIndex) == MANAGER_STATE_RUNNING)
    {
        started = true;
        dash_log(DASH_LOG_WARNING, "[%s,%d] warning, subtitle stream [%d] is already running!\n", __FUNCTION__, __LINE__, adaptationSetIndex);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] warning, subtitle stream [%d] start error, wrong state %d!\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleState.at(adaptationSetIndex));
    }
    LeaveCriticalSection(&this->monitorMutex);

    return started;
}

void    MultimediaManager::StopSubtitle(int adaptationSetIndex)
{
    EnterCriticalSection(&this->monitorMutex);

    if (this->subtitleStreams.size() <= adaptationSetIndex ||
        this->subtitleAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleStreams.size(), this->subtitleAdaptationSets.size());
        LeaveCriticalSection(&this->monitorMutex);
        return;
    }

    if (this->subtitleState.at(adaptationSetIndex) == MANAGER_STATE_RUNNING)
    {
        this->subtitleStreams.at(adaptationSetIndex)->Stop();
        this->subtitleState.at(adaptationSetIndex) = MANAGER_STATE_STOPPED;
    }
    else if (this->subtitleState.at(adaptationSetIndex) == MANAGER_STATE_STOPPED)
    {
        dash_log(DASH_LOG_WARNING, "[%s,%d] warning, subtitle stream [%d] is already stopped!\n", __FUNCTION__, __LINE__, adaptationSetIndex);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] warning, subtitle stream [%d] stop error, wrong state %d!\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleState.at(adaptationSetIndex));
    }
    LeaveCriticalSection(&this->monitorMutex);

    return;
}

int  MultimediaManager::Invoke(MANAGER_INVOKE invokeID, void *arg)
{
    if (invokeID == MANAGER_INVOKE_SET_HTTP_HEADERS)
    {
        if (arg != NULL)
        {
            this->httpHeaders.assign((char *)arg);

            return 0;
        }
    }

    return -1;
}

bool    MultimediaManager::SetVideoQuality                  (dash::mpd::IPeriod* period, IAdaptationSet *adaptationSet, dash::mpd::IRepresentation *representation)
{
    EnterCriticalSection(&this->monitorMutex);

    if(this->period != period)
    {
        this->period = period;
    }
/*
    if(this->isStarted)
    {
        this->StopVideo();
        this->InitVideoRendering();
        this->videoStreams.at(this->videoAdaptationSetIndex)->Start();
    }
*/
    LeaveCriticalSection(&this->monitorMutex);
    return true;
}

bool    MultimediaManager::SetAudioQuality                  (dash::mpd::IPeriod* period, IAdaptationSet *adaptationSet, dash::mpd::IRepresentation *representation)
{
    EnterCriticalSection(&this->monitorMutex);

    this->period                = period;
/*
    if (this->isStarted)
    {
        this->StopAudio();
        this->InitAudioPlayback();
        this->audioStreams.at(this->audioAdaptationSetIndex)->Start();
    }
*/
    LeaveCriticalSection(&this->monitorMutex);
    return true;
}

bool MultimediaManager::SetSubtitleQuality                  (dash::mpd::IPeriod * period, IAdaptationSet *adaptationSet, dash::mpd::IRepresentation *representation)
{
    EnterCriticalSection(&this->monitorMutex);

    this->period                 = period;
    this->subtitleAdaptationSet  = adaptationSet;
    this->subtitleRepresentation = representation;
/*
    if (this->isStarted)
    {
        this->StopSubtitle();
        this->InitSubtitleParsing();
        this->subtitleStreams.at(this->subtitleAdaptationSetIndex)->Start();
    }
*/
    LeaveCriticalSection(&this->monitorMutex);
    return true;
}

bool    MultimediaManager::SetVideoAdaptationLogic          (libdash::framework::adaptation::LogicType type)
{
    //Currently unused, always using ManualAdaptation.
    return true;
}
bool    MultimediaManager::SetAudioAdaptationLogic          (libdash::framework::adaptation::LogicType type)
{
    //Currently unused, always using ManualAdaptation.
    return true;
}
void    MultimediaManager::NotifyVideoObservers             ()
{
    /* Notify DASHPLayer onVideoDataAvailable which does the scaling and forwards the frame to the renderer */
}
void    MultimediaManager::NotifyAudioObservers             ()
{
    /* MUST NOT BE IMPLEMENTED YET */
}
void    MultimediaManager::AttachVideoBufferObserver        (IBufferObserver *videoBufferObserver)
{
    this->videoBufferObservers.push_back(videoBufferObserver);
}
void    MultimediaManager::AttachAudioBufferObserver        (IBufferObserver *audioBufferObserver)
{
}
void    MultimediaManager::NotifyVideoBufferObservers       ()
{
}
void    MultimediaManager::NotifyAudioBufferObservers       ()
{
}

void    MultimediaManager::InitVideoRendering               ()

{
    //if (!this->isStarted)
    {
        BreakPoints *bks = this->breakpoints;
        for (int i = 0; i < videoAdaptationSets.size(); i++)
        {
            IAdaptationLogic *videoLogic = NULL;
            IRepresentation *videoRepresentation = NULL;
            int representationIndex;
            uint32_t offset = this->videoPosition.at(i);
            void *logicBK = NULL, *streamBK = NULL;

            IAdaptationSet *adaptationSet = this->videoAdaptationSets.at(i);

            representationIndex = this->videoRepresentationIndexes.at(i);
            videoRepresentation = adaptationSet->GetRepresentation().at(representationIndex);

            if (bks)
            {
                logicBK    =  bks->videoBreakPoints.at(i).logicBreakPoint;
                streamBK =  bks->videoBreakPoints.at(i).streamBreakPoint;
            }
            videoLogic = AdaptationLogicFactory::Create(libdash::framework::adaptation::Manual, this->period, adaptationSet, this->mpd, SEGMENTBUFFER_SIZE, logicBK);
            if (bks == NULL)
                videoLogic->SetPosition(offset);
            if (bks == NULL || this->videoForceInvokeInitSeg.at(i))
            {
                 //if representation changed ,need to do this,
                 //but parse initial segment one more time, will get one more stream in avformat
                this->videoForceInvokeInitSeg.at(i) = false;
                videoLogic->SetRepresentation(videoRepresentation, representationIndex, true);
            }
            else
            {
                videoLogic->SetRepresentation(videoRepresentation, representationIndex, false);
            }

            MultimediaStream *videoStream = NULL;
            videoStream = new MultimediaStream(adaptationSet, videoLogic, SEGMENTBUFFER_SIZE, streamBK);
            videoStream->AttachStreamObserver(this);
            videoStream->SetHttpHeaders(this->httpHeaders);

            for(int j = 0; j < this->videoBufferObservers.size(); j++)
            {
                videoStream->AttachBufferObserver(this->videoBufferObservers.at(j));
            }

            if (0 == this->videoLogics.size())
                this->videoLogics.resize(this->videoAdaptationSets.size());

            if (0 == this->videoStreams.size())
                this->videoStreams.resize(this->videoAdaptationSets.size());

            this->videoLogics.at(i) = videoLogic;
            this->videoStreams.at(i) = videoStream;
            this->videoState.at(i) = MANAGER_STATE_STOPPED;
        }
        if (bks)
            bks->videoBreakPoints.clear();
    }
#if 0
    else
    {
        IAdaptationLogic *videoLogic = NULL;
        uint32_t offset = this->videoPosition.at(videoAdaptationSetIndex);
        int representationIndex = this->videoRepresentationIndexes.at(videoAdaptationSetIndex);
        IAdaptationSet *adaptationSet = this->videoAdaptationSets.at(videoAdaptationSetIndex);
        IRepresentation *videoRepresentation = adaptationSet->GetRepresentation().at(representationIndex);
        videoLogic = AdaptationLogicFactory::Create(libdash::framework::adaptation::Manual, this->period, adaptationSet, this->mpd, SEGMENTBUFFER_SIZE, NULL);
        videoLogic->SetPosition(offset);
        if (this->videoForceInvokeInitSeg.at(videoAdaptationSetIndex))
        {
            this->videoForceInvokeInitSeg.at(videoAdaptationSetIndex) = false;
            videoLogic->SetRepresentation(videoRepresentation, representationIndex, true);
        }
        else
        {
            videoLogic->SetRepresentation(videoRepresentation, representationIndex, false);
        }

        MultimediaStream *videoStream = NULL;
        videoStream = new MultimediaStream(adaptationSet, videoLogic, SEGMENTBUFFER_SIZE, NULL);
        videoStream->AttachStreamObserver(this);

        videoStreams.at(this->videoAdaptationSetIndex) = videoStream;
        videoLogics.at(this->videoAdaptationSetIndex) = videoLogic;

        for(int i = 0; i < this->videoBufferObservers.size(); i++)
        {
            videoStream->AttachBufferObserver(this->videoBufferObservers.at(i));
        }
    }
#endif
}

void    MultimediaManager::InitAudioPlayback                ()

{
//    if (!isStarted)
    {
        BreakPoints *bks = this->breakpoints;
        for (int i = 0; i < audioAdaptationSets.size(); i++)
        {
            IAdaptationLogic *audioLogic = NULL;
            IRepresentation *audioRepresentation = NULL;
            int representationIndex;
            uint32_t offset = this->audioPosition.at(i);
            void *logicBK = NULL, *streamBK = NULL;

            IAdaptationSet *adaptationSet = this->audioAdaptationSets.at(i);

            representationIndex = this->audioRepresentationIndexes.at(i);
            audioRepresentation = adaptationSet->GetRepresentation().at(representationIndex);;

            if (bks)
            {
                logicBK    =  bks->audioBreakPoints.at(i).logicBreakPoint;
                streamBK =  bks->audioBreakPoints.at(i).streamBreakPoint;
            }
            audioLogic = AdaptationLogicFactory::Create(libdash::framework::adaptation::Manual, this->period, adaptationSet, this->mpd, SEGMENTBUFFER_SIZE, logicBK);
            if (bks == NULL)
                audioLogic->SetPosition(offset);
            if (bks == NULL || this->audioForceInvokeInitSeg.at(i))
            {
                this->audioForceInvokeInitSeg.at(i) = false;
                audioLogic->SetRepresentation(audioRepresentation, representationIndex, true);
            }
            else
            {
                audioLogic->SetRepresentation(audioRepresentation, representationIndex, false);
            }

            MultimediaStream *audioStream = NULL;
            audioStream = new MultimediaStream(adaptationSet, audioLogic, SEGMENTBUFFER_SIZE, streamBK);
            audioStream->AttachStreamObserver(this);
            audioStream->SetHttpHeaders(this->httpHeaders);

            if (0 == this->audioLogics.size())
                this->audioLogics.resize(this->audioAdaptationSets.size());

            if (0 == this->audioStreams.size())
                this->audioStreams.resize(this->audioAdaptationSets.size());

            this->audioLogics.at(i) = audioLogic;
            this->audioStreams.at(i) = audioStream;
            this->audioState.at(i) = MANAGER_STATE_STOPPED;
        }
        if (bks)
            bks->audioBreakPoints.clear();
    }
 #if 0
    else
    {
        IAdaptationLogic *audioLogic = NULL;
        uint32_t offset = this->audioPosition.at(audioAdaptationSetIndex);
        int representationIndex = this->audioRepresentationIndexes.at(audioAdaptationSetIndex);
        IAdaptationSet *adaptationSet = this->audioAdaptationSets.at(audioAdaptationSetIndex);
        IRepresentation *audioRepresentation = adaptationSet->GetRepresentation().at(representationIndex);
        audioLogic = AdaptationLogicFactory::Create(libdash::framework::adaptation::Manual, this->period, adaptationSet, this->mpd, SEGMENTBUFFER_SIZE, NULL);
        audioLogic->SetPosition(offset);
        if (this->audioForceInvokeInitSeg.at(audioAdaptationSetIndex))
        {
            this->audioForceInvokeInitSeg.at(audioAdaptationSetIndex) = false;
            audioLogic->SetRepresentation(audioRepresentation, representationIndex, true);
            //audioLogic->InvokeInitSegment(true);
        }
        else
        {
            audioLogic->SetRepresentation(audioRepresentation, representationIndex, false);
        }

        MultimediaStream *audioStream = NULL;
        audioStream = new MultimediaStream(adaptationSet, audioLogic, SEGMENTBUFFER_SIZE, NULL);
        audioStream->AttachStreamObserver(this);

        audioStreams.at(this->audioAdaptationSetIndex) = audioStream;
        audioLogics.at(this->audioAdaptationSetIndex) = audioLogic;
    }
#endif

}

void    MultimediaManager::InitSubtitleParsing              ()
{
   // if (!isStarted)
    {
        BreakPoints *bks = this->breakpoints;
        for (int i = 0; i < subtitleAdaptationSets.size(); i++)
        {
            IAdaptationLogic *subtitleLogic = NULL;
            IRepresentation *subtitleRepresentation = NULL;
            int representationIndex;
            uint32_t offset = this->subtitlePosition.at(i);
            IAdaptationSet *adaptationSet = this->subtitleAdaptationSets.at(i);
            void *logicBK = NULL, *streamBK = NULL;

            representationIndex = this->subtitleRepresentationIndexes.at(i);
            subtitleRepresentation = adaptationSet->GetRepresentation().at(representationIndex);

            if (bks)
            {
                logicBK    =  bks->subtitleBreakPoints.at(i).logicBreakPoint;
                streamBK =  bks->subtitleBreakPoints.at(i).streamBreakPoint;
            }

            subtitleLogic = AdaptationLogicFactory::Create(libdash::framework::adaptation::Manual, this->period, adaptationSet, this->mpd, SEGMENTBUFFER_SIZE, logicBK);
            if (bks == NULL)
            {
                subtitleLogic->SetPosition(offset);
              //  subtitleLogic->InvokeInitSegment(true);
            }
            if (bks == NULL || this->subtitleForceInvokeInitSeg.at(i))
            {
                this->subtitleForceInvokeInitSeg.at(i) = false;
                subtitleLogic->SetRepresentation(subtitleRepresentation, representationIndex, true);
            }
            else
            {
                subtitleLogic->SetRepresentation(subtitleRepresentation, representationIndex, false);
            }

            MultimediaStream *subtitleStream = NULL;
            subtitleStream = new MultimediaStream(adaptationSet, subtitleLogic, SEGMENTBUFFER_SIZE, streamBK);
            subtitleStream->AttachStreamObserver(this);
            subtitleStream->SetHttpHeaders(this->httpHeaders);

            if (0 == this->subtitleLogics.size())
                this->subtitleLogics.resize(this->subtitleAdaptationSets.size());

            if (0 == this->subtitleStreams.size())
                this->subtitleStreams.resize(this->subtitleAdaptationSets.size());

            this->subtitleLogics.at(i) = subtitleLogic;
            this->subtitleStreams.at(i) = subtitleStream;
            this->subtitleState.at(i) = MANAGER_STATE_STOPPED;
        }
        if (bks)
         bks->subtitleBreakPoints.clear();
    }
 #if 0
    else
    {
        IAdaptationLogic *subtitleLogic = NULL;
        uint32_t offset = this->subtitlePosition.at(subtitleAdaptationSetIndex);
        int representationIndex = this->subtitleRepresentationIndexes.at(subtitleAdaptationSetIndex);
        IAdaptationSet *adaptationSet = this->subtitleAdaptationSets.at(subtitleAdaptationSetIndex);
        IRepresentation *subtitleRepresentation = adaptationSet->GetRepresentation().at(representationIndex);
        subtitleLogic = AdaptationLogicFactory::Create(libdash::framework::adaptation::Manual, this->period, adaptationSet, this->mpd, SEGMENTBUFFER_SIZE, NULL);
        subtitleLogic->SetPosition(offset);
        if (this->subtitleForceInvokeInitSeg.at(subtitleAdaptationSetIndex))
        {
            this->subtitleForceInvokeInitSeg.at(subtitleAdaptationSetIndex) = false;
            subtitleLogic->SetRepresentation(subtitleRepresentation, representationIndex, true);
        }
        else
        {
            subtitleLogic->SetRepresentation(subtitleRepresentation, representationIndex, false);
        }
       // subtitleLogic->SetRepresentation(subtitleRepresentation);
       // subtitleLogic->InvokeInitSegment(true);

        MultimediaStream *subtitleStream = NULL;
        subtitleStream = new MultimediaStream(adaptationSet, subtitleLogic, SEGMENTBUFFER_SIZE, NULL);
        subtitleStream->AttachStreamObserver(this);

        subtitleStreams.at(this->subtitleAdaptationSetIndex) = subtitleStream;
        subtitleLogics.at(this->subtitleAdaptationSetIndex) = subtitleLogic;
    }
#endif
}

void    MultimediaManager::OnVideoSegmentDecodingStarted    ()
{
    this->videoSegmentsDecodingStarted++;
}
void    MultimediaManager::OnVideoSegmentDownloaded         ()
{
    //this->bandWidth = bandWidth;
    this->videoSegmentsDownloaded++;
}

uint32_t    MultimediaManager::GetBandWidth()
{
    return this->bandWidth;
}

uint32_t    MultimediaManager::GetVideoBandWidth            ()
{
    if (!this->videoStreams.empty())
        return this->videoStreams.at(videoAdaptationSetIndex)->GetBandWidth();

    return 0;
}

uint32_t    MultimediaManager::GetAudioBandWidth             ()
{
    if (!this->audioStreams.empty())
        return this->audioStreams.at(audioAdaptationSetIndex)->GetBandWidth();

    return 0;
}

uint32_t    MultimediaManager::GetSubtitleBandWidth          ()
{
    if (!this->subtitleStreams.empty())
        return this->subtitleStreams.at(subtitleAdaptationSetIndex)->GetBandWidth();

    return 0;
}

int     MultimediaManager::_GetPresentationFromBandWidth(std::vector<IRepresentation *> represenations, uint32_t bandWidth)
{
    int index = 0, i;
    int32_t minBWDiff = (int32_t)0x80000000, bwDiff;
    uint32_t rBandWidth;

    for(int i = 0; i < represenations.size(); i++)
    {
        rBandWidth =  represenations.at(i)->GetBandwidth();
        bwDiff = bandWidth - rBandWidth;
        if (bwDiff == 0)
            return i;
        if ((minBWDiff < 0 && bwDiff > minBWDiff) ||
            (minBWDiff >= 0 && bwDiff >= 0 && bwDiff < minBWDiff))
        {
            minBWDiff = bwDiff;
            index = i;
        }
    }

    return index;
}

int     MultimediaManager::CheckVideoCurrentIndex(uint32_t bandWidth)
{
    if (mpd->GetPeriods().size() > 0)
    {
        IPeriod *period = GetCurrentPeriod();

        if (!AdaptationSetHelper::GetVideoAdaptationSets(period).empty())
        {
            IAdaptationSet *adaptationSet = AdaptationSetHelper::GetVideoAdaptationSets(period).at(videoAdaptationSetIndex);

            return _GetPresentationFromBandWidth(adaptationSet->GetRepresentation(), bandWidth);
        }
    }
    return -1;
}

int      MultimediaManager::CheckAudioCurrentIndex(uint32_t bandWidth)
{
    if (mpd->GetPeriods().size() > 0)
    {
        IPeriod *period = GetCurrentPeriod();

        if (!AdaptationSetHelper::GetAudioAdaptationSets(period).empty())
        {
            IAdaptationSet *adaptationSet = AdaptationSetHelper::GetAudioAdaptationSets(period).at(audioAdaptationSetIndex);

            return _GetPresentationFromBandWidth(adaptationSet->GetRepresentation(), bandWidth);
        }
    }
    return -1;
}

int     MultimediaManager::CheckSubtitleCurrentIndex(uint32_t bandWidth)
{
    if (mpd->GetPeriods().size() > 0)
    {
        IPeriod *period = GetCurrentPeriod();

        if (!AdaptationSetHelper::GetSubtitleAdaptationSets(period).empty())
        {
            IAdaptationSet *adaptationSet = AdaptationSetHelper::GetSubtitleAdaptationSets(period).at(subtitleAdaptationSetIndex);

            return _GetPresentationFromBandWidth(adaptationSet->GetRepresentation(), bandWidth);
        }
    }
    return -1;
}

bool MultimediaManager::IsStarted()
{
    return this->isStarted;
}

//getFileInfo
int64_t MultimediaManager::GetDuration()
{
    std::string duration = mpd->GetMediaPresentationDuration();
    if (duration != "")
        return TimeResolver::GetDurationInSec(mpd->GetMediaPresentationDuration()) * DASH_TIME_UNIT;

    return -1;
}

bool MultimediaManager::IsLive()
{
    if (mpd->GetType() == "static")
        this->isLive = false;

    if (mpd->GetType() == "dynamic")
        this->isLive = true;

    return this->isLive;
}

void * MultimediaManager::GetVideoAVIOContext(int adaptationSetIndex)
{
    if (!this->videoStreams.empty())
        return (void *)this->videoStreams.at(adaptationSetIndex)->GetDecodingThread()->GetDecoder()->GetAVIOContextPtr();

    return NULL;
}

void * MultimediaManager::GetAudioAVIOContext(int adaptationSetIndex)
{
    if (!this->audioStreams.empty())
        return (void *)this->audioStreams.at(adaptationSetIndex)->GetDecodingThread()->GetDecoder()->GetAVIOContextPtr();

    return NULL;
}

void * MultimediaManager::GetSubtitleAVIOContext(int adaptationSetIndex)
{
    if (!this->subtitleStreams.empty())
        return (void *)this->subtitleStreams.at(adaptationSetIndex)->GetDecodingThread()->GetDecoder()->GetAVIOContextPtr();

    return NULL;
}

uint32_t    MultimediaManager::GetFetchTime()
{
    return mpd->GetFetchTime();
}

uint32_t    MultimediaManager::GetCheckTime()
{
    return (mpd->GetFetchTime() + TimeResolver::GetDurationInSec(this->mpd->GetMinimumUpdatePeriod()));//+1 for deviation, verfied by org.hbbtv_DA540650, failed sometimes
}

uint32_t    MultimediaManager::GetCurrentTime()
{
    return TimeResolver::GetCurrentTimeInSec();
}

uint32_t    MultimediaManager::GetVideoPosition()
{
    if (!this->videoStreams.empty())
        return this->videoStreams.at(this->videoAdaptationSetIndex)->GetPosition();

    return 0;
}

uint32_t    MultimediaManager::GetAudioPosition()
{
    if (!this->audioStreams.empty())
        return this->audioStreams.at(this->audioAdaptationSetIndex)->GetPosition();

    return 0;
}

uint32_t    MultimediaManager::GetSubtitlePosition()
{
    if (!this->subtitleStreams.empty())
        return this->subtitleStreams.at(this->subtitleAdaptationSetIndex)->GetPosition();

    return 0;
}

uint32_t    MultimediaManager::GetVideoPosition(int adaptationSetIndex)
{
    if (this->videoStreams.size() > adaptationSetIndex && adaptationSetIndex >= 0)
        return this->videoStreams.at(adaptationSetIndex)->GetPosition();
    else
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get position, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->videoStreams.size());

    return 0;
}

uint32_t    MultimediaManager::GetAudioPosition(int adaptationSetIndex)
{
    if (this->audioStreams.size() > adaptationSetIndex && adaptationSetIndex >= 0)
        return this->audioStreams.at(this->audioAdaptationSetIndex)->GetPosition();
    else
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get position, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->audioStreams.size());

    return 0;
}

uint32_t    MultimediaManager::GetSubtitlePosition(int adaptationSetIndex)
{
    if (this->subtitleStreams.size() > adaptationSetIndex && adaptationSetIndex >= 0)
        return this->subtitleStreams.at(this->subtitleAdaptationSetIndex)->GetPosition();
    else
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get position, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleStreams.size());

    return 0;
}

void        MultimediaManager::SetVideoPosition(int videoAdaptationSetIndex, uint32_t position)
{
    if (0 == this->videoPosition.size())
        this->videoPosition.resize(this->videoAdaptationSets.size());

    this->videoPosition.at(videoAdaptationSetIndex) = position;
    if (this->videoState.at(videoAdaptationSetIndex) == MANAGER_STATE_STOPPED)
    {
        this->videoLogics.at(videoAdaptationSetIndex)->SetPosition(position);
    }
}

void        MultimediaManager::SetAudioPosition(int audioAdaptationSetIndex, uint32_t position)
{
    if (0 == this->audioPosition.size())
        this->audioPosition.resize(this->audioAdaptationSets.size());

    this->audioPosition.at(audioAdaptationSetIndex) = position;

    if (this->audioState.at(audioAdaptationSetIndex) == MANAGER_STATE_STOPPED)
    {
        this->audioLogics.at(audioAdaptationSetIndex)->SetPosition(position);
    }
}

void        MultimediaManager::SetSubtitlePosition(int subtitleAdaptationSetIndex, uint32_t position)
{
    if (0 == this->subtitlePosition.size())
        this->subtitlePosition.resize(this->subtitleAdaptationSets.size());

    this->subtitlePosition.at(subtitleAdaptationSetIndex) = position;

    if (this->subtitleState.at(subtitleAdaptationSetIndex) == MANAGER_STATE_STOPPED)
    {
        this->subtitleLogics.at(subtitleAdaptationSetIndex)->SetPosition(position);
    }
}

void        MultimediaManager::SetVideoRepresentation(int adaptationSetIndex,
                                                 int representationIndex, bool invokeInitSegment)
{
    if (this->videoLogics.size() <= adaptationSetIndex ||
        this->videoAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->videoLogics.size(), this->videoAdaptationSets.size());
        return;
    }

    if (this->videoAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size() \
        <= representationIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] representationIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, representationIndex,
            this->videoAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size());
        return;
    }

    IRepresentation *representation = this->videoAdaptationSets.at(adaptationSetIndex)->GetRepresentation().at(representationIndex);

    this->videoLogics.at(adaptationSetIndex)->SetRepresentation(representation, representationIndex, invokeInitSegment);
    this->videoRepresentationIndexes.at(adaptationSetIndex) = representationIndex;

    dash_log(DASH_LOG_INFO, "[%s,%d] video adaptionset %d's representation changed to %d, invokeInitSegment:%d\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, representationIndex, invokeInitSegment);
}

void        MultimediaManager::SetAudioRepresentation(int adaptationSetIndex,
                                                 int representationIndex, bool invokeInitSegment)
{
    if (this->audioLogics.size() <= adaptationSetIndex ||
        this->audioAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->audioLogics.size(), this->audioAdaptationSets.size());
        return;
    }

    if (this->audioAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size() \
        <= representationIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] representationIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, representationIndex,
            this->audioAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size());
        return;
    }

    IRepresentation *representation = this->audioAdaptationSets.at(adaptationSetIndex)->GetRepresentation().at(representationIndex);

    this->audioLogics.at(adaptationSetIndex)->SetRepresentation(representation, representationIndex, invokeInitSegment);
    this->audioRepresentationIndexes.at(adaptationSetIndex) = representationIndex;

    dash_log(DASH_LOG_INFO, "[%s,%d] audio adaptionset %d's representation changed to %d, invokeInitSegment:%d\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, representationIndex, invokeInitSegment);
}

void        MultimediaManager::SetSubtitleRepresentation(int adaptationSetIndex,
                                                 int representationIndex, bool invokeInitSegment)
{
    if (this->subtitleLogics.size() <= adaptationSetIndex ||
        this->subtitleAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleLogics.size(), this->subtitleAdaptationSets.size());
        return;
    }

    if (this->subtitleAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size() \
        <= representationIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] representationIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, representationIndex,
            this->subtitleAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size());
        return;
    }

    IRepresentation *representation = this->subtitleAdaptationSets.at(adaptationSetIndex)->GetRepresentation().at(representationIndex);

    this->subtitleLogics.at(adaptationSetIndex)->SetRepresentation(representation, representationIndex, invokeInitSegment);
    this->subtitleRepresentationIndexes.at(adaptationSetIndex) = representationIndex;

    dash_log(DASH_LOG_INFO, "[%s,%d] subtitle adaptionset changed to %d, representation changed to %d, invokeInitSegment:%d\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, representationIndex, invokeInitSegment);
}

void        MultimediaManager::SetVideoIndex(int adaptationSetIndex,
                                                 int representationIndex, bool invokeInitSegment)
{
    if (this->videoLogics.size() <= adaptationSetIndex ||
        this->videoAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->videoLogics.size(), this->videoAdaptationSets.size());
        return;
    }

    if (this->videoAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size() \
        <= representationIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] representationIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, representationIndex,
            this->videoAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size());
        return;
    }

    SetVideoRepresentation(adaptationSetIndex, representationIndex, invokeInitSegment);
    if (this->videoAdaptationSetIndex != adaptationSetIndex)
    {
        this->videoAdaptationSetIndex = adaptationSetIndex;
        dash_log(DASH_LOG_INFO, "[%s,%d] video adaptionset changed to %d\n", __FUNCTION__, __LINE__, adaptationSetIndex);
    }
}

void        MultimediaManager::SetAudioIndex(int adaptationSetIndex,
                                                 int representationIndex, bool invokeInitSegment)
{
    if (this->audioLogics.size() <= adaptationSetIndex ||
        this->audioAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->audioLogics.size(), this->audioAdaptationSets.size());
        return;
    }

    if (this->audioAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size() \
        <= representationIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] representationIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, representationIndex,
            this->audioAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size());
        return;
    }

    SetAudioRepresentation(adaptationSetIndex, representationIndex, invokeInitSegment);
    if (this->audioAdaptationSetIndex != adaptationSetIndex)
    {
        this->audioAdaptationSetIndex = adaptationSetIndex;
        dash_log(DASH_LOG_INFO, "[%s,%d] audio adaptionset changed to %d\n", __FUNCTION__, __LINE__, adaptationSetIndex);
    }
}

void        MultimediaManager::SetSubtitleIndex(int adaptationSetIndex,
                                                 int representationIndex, bool invokeInitSegment)
{
    if (this->subtitleLogics.size() <= adaptationSetIndex ||
        this->subtitleAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleLogics.size(), this->subtitleAdaptationSets.size());
        return;
    }

    if (this->subtitleAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size() \
        <= representationIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] representationIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, representationIndex,
            this->subtitleAdaptationSets.at(adaptationSetIndex)->GetRepresentation().size());
        return;
    }

    SetSubtitleRepresentation(adaptationSetIndex, representationIndex, invokeInitSegment);
    if (this->subtitleAdaptationSetIndex != adaptationSetIndex)
    {
        this->subtitleAdaptationSetIndex = adaptationSetIndex;
        dash_log(DASH_LOG_INFO, "[%s,%d] subtitle adaptionset changed to %d\n", __FUNCTION__, __LINE__, adaptationSetIndex);
    }
}

int          MultimediaManager::GetVideoCurrentPresentationIndex(int adaptationSetIndex)
{
    if (this->videoAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->videoAdaptationSets.size());
        return -1;
    }

    if (this->isStarted)
    {
        if (this->videoLogics.size() <= adaptationSetIndex)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u)\n",
                __FUNCTION__, __LINE__, adaptationSetIndex, this->videoLogics.size());
            return -1;
        }

        return this->videoLogics.at(adaptationSetIndex)->GetCurrentRepresentationIndex();
    }
    else
    {
        return this->videoRepresentationIndexes.at(adaptationSetIndex);
    }
}

int          MultimediaManager::GetAudioCurrentPresentationIndex(int adaptationSetIndex)
{
    if (this->audioAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->audioAdaptationSets.size());
        return -1;
    }

    if (this->isStarted)
    {
        if (this->audioLogics.size() <= adaptationSetIndex)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u)\n",
                __FUNCTION__, __LINE__, adaptationSetIndex, this->audioLogics.size());
            return -1;
        }

        return this->audioLogics.at(adaptationSetIndex)->GetCurrentRepresentationIndex();
    }
    else
    {
        return this->audioRepresentationIndexes.at(adaptationSetIndex);
    }
}

int          MultimediaManager::GetSubtitleCurrentPresentationIndex(int adaptationSetIndex)
{
    if (this->subtitleAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleAdaptationSets.size());
        return -1;
    }

    if (this->isStarted)
    {
        if (this->subtitleLogics.size() <= adaptationSetIndex)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] adaptationSetIndex %d invalid, scope [0, %u)\n",
                __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleLogics.size());
            return -1;
        }

        return this->subtitleLogics.at(adaptationSetIndex)->GetCurrentRepresentationIndex();
    }
    else
    {
        return this->subtitleRepresentationIndexes.at(adaptationSetIndex);
    }
}

bool        MultimediaManager::_SetCurrentPeriod(dash::mpd::IPeriod *period)
{
    if (this->videoStreams.size() > 0 ||
        this->videoLogics.size() > 0 ||
        this->audioStreams.size() > 0 ||
        this->audioLogics.size() > 0 ||
        this->subtitleStreams.size() > 0 ||
        this->subtitleLogics.size() > 0 ||
        period == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] MultimediaManager::destroy() must be called before set period!\n", __FUNCTION__, __LINE__);
        return false;
    }

    this->period = period;

    return true;
}

bool        MultimediaManager::SetCurrentPeriod(dash::mpd::IPeriod *period)
{
        bool ret;

        EnterCriticalSection(&this->monitorMutex);
        ret = _SetCurrentPeriod(period);
        if (ret)
        {
            InitAdaptionSets();
        }
        LeaveCriticalSection(&this->monitorMutex);

        return ret;
}

IPeriod *MultimediaManager::GetCurrentPeriod()
{
        return this->period;
}

bool        MultimediaManager::SetQuality()
{
    if (mpd->GetPeriods().size() > 0)
    {
        IPeriod * period = GetCurrentPeriod();

        if (!isStarted)
        {
            if (!AdaptationSetHelper::GetVideoAdaptationSets(period).empty())
            {
                for (int i = 0; i < AdaptationSetHelper::GetVideoAdaptationSets(period).size(); i++)
                {
                    IAdaptationSet *adaptationSet = AdaptationSetHelper::GetVideoAdaptationSets(period).at(i);
                    IRepresentation *videoRepresentation = adaptationSet->GetRepresentation().at(0);
                    this->SetVideoQuality(period, adaptationSet, videoRepresentation);
                }
            }

            if (!AdaptationSetHelper::GetAudioAdaptationSets(period).empty() && (true == this->isISOFF))
            {
                for (int i = 0; i < AdaptationSetHelper::GetAudioAdaptationSets(period).size(); i++)
                {
                    IAdaptationSet *adaptationSet = AdaptationSetHelper::GetAudioAdaptationSets(period).at(i);
                    IRepresentation *audioRepresentation = adaptationSet->GetRepresentation().at(0);
                    this->SetAudioQuality(period, adaptationSet, audioRepresentation);
                }
            }

            if (!AdaptationSetHelper::GetSubtitleAdaptationSets(period).empty() && (true == this->isISOFF))
            {
                for (int i = 0; i< AdaptationSetHelper::GetSubtitleAdaptationSets(period).size(); i++)
                {
                    IAdaptationSet *adaptationSet = AdaptationSetHelper::GetSubtitleAdaptationSets(period).at(i);
                    IRepresentation *subtitleRepresentation = adaptationSet->GetRepresentation().at(0);
                    this->SetSubtitleQuality(period, adaptationSet, subtitleRepresentation);
                }
            }
        }
        /*
        else
        {
            if (!videoAdaptationSets.empty() && videoRepresentationIndex >= 0)
            {
                IAdaptationSet *adaptationSet = videoAdaptationSets.at(videoAdaptationSetIndex);
                IRepresentation *videoRepresentation = adaptationSet->GetRepresentation().at(videoRepresentationIndex);
                this->SetVideoQuality(period, adaptationSet, videoRepresentation);
            }

            if (!audioAdaptationSets.empty() && audioRepresentationIndex >= 0 && (true == this->isISOFF))
            {
                IAdaptationSet *adaptationSet = audioAdaptationSets.at(audioAdaptationSetIndex);
                IRepresentation *audioRepresentation = adaptationSet->GetRepresentation().at(audioRepresentationIndex);
                this->SetAudioQuality(period, adaptationSet, audioRepresentation);
            }

            if (!subtitleAdaptationSets.empty() && subtitleRepresentationIndex >= 0 && (true == this->isISOFF))
            {
                IAdaptationSet *adaptationSet = subtitleAdaptationSets.at(subtitleAdaptationSetIndex);
                IRepresentation *subtitleRepresentation = adaptationSet->GetRepresentation().at(subtitleRepresentationIndex);
                this->SetSubtitleQuality(period, adaptationSet, subtitleRepresentation);
            }
        }
        */
    }
    return true;
}

void *    MultimediaManager::Pause()
{
    int i ;
    BreakPoints  *bks;
    void  *bk;

    if (this->breakpoints)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] already have breakpoints\n", __FUNCTION__, __LINE__);
        return breakpoints;
    }

    dash_log(DASH_LOG_ERROR, "[%s,%d] begin to pause...\n", __FUNCTION__, __LINE__);

    EnterCriticalSection(&this->monitorMutex);

    this->breakpoints = new BreakPoints();
    bks = this->breakpoints;

    if (this->videoStreams.size() > 0)
    {
        bks->videoBreakPoints.resize(this->videoStreams.size());
        for (i = 0; i < this->videoStreams.size(); i++)
        {
            bk = this->videoStreams.at(i)->Pause();
            bks->videoBreakPoints.at(i).streamBreakPoint = bk;
            bk = this->videoLogics.at(i)->Pause();
            bks->videoBreakPoints.at(i).logicBreakPoint = bk;
        }
    }

    if (this->audioStreams.size() > 0)
    {
        bks->audioBreakPoints.resize(this->audioStreams.size());
        for (i = 0; i < this->audioStreams.size(); i++)
        {
            bk = this->audioStreams.at(i)->Pause();
            bks->audioBreakPoints.at(i).streamBreakPoint = bk;
            bk = this->audioLogics.at(i)->Pause();
            bks->audioBreakPoints.at(i).logicBreakPoint = bk;
        }
    }

    if (this->subtitleStreams.size() > 0)
    {
        bks->subtitleBreakPoints.resize(this->subtitleStreams.size());
        for (i = 0; i < this->subtitleStreams.size(); i++)
        {
            bk = this->subtitleStreams.at(i)->Pause();
            bks->subtitleBreakPoints.at(i).streamBreakPoint = bk;
            bk = this->subtitleLogics.at(i)->Pause();
            bks->subtitleBreakPoints.at(i).logicBreakPoint = bk;
        }
    }
    LeaveCriticalSection(&this->monitorMutex);

    dash_log(DASH_LOG_ERROR, "[%s,%d] pause done, return %p...\n", __FUNCTION__, __LINE__, bks);

    return bks;
}

bool    MultimediaManager::Resume(void *breakpoint)
{
    int i;
    BreakPoints  *bks = this->breakpoints;

    if (breakpoint != this->breakpoints && breakpoint != NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] error, breakpoint not correct!\n", __FUNCTION__, __LINE__);
        return false;
    }

    dash_log(DASH_LOG_ERROR, "[%s,%d] begin to resume...\n", __FUNCTION__, __LINE__);

    EnterCriticalSection(&this->monitorMutex);
    if (this->videoStreams.size() > 0)
    {
        //bks->videoBreakPoints.resize(this->videoStreams.size());
        for (i = 0; i < this->videoStreams.size(); i++)
        {
            this->videoStreams.at(i)->Resume(bks->videoBreakPoints.at(i).streamBreakPoint);
            this->videoLogics.at(i)->Resume(bks->videoBreakPoints.at(i).logicBreakPoint);
        }
    }

    if (this->audioStreams.size() > 0)
    {
        //bks->audioBreakPoints.resize(this->audioStreams.size());
        for (i = 0; i < this->audioStreams.size(); i++)
        {
            this->audioStreams.at(i)->Resume(bks->audioBreakPoints.at(i).streamBreakPoint);
            this->audioLogics.at(i)->Resume(bks->audioBreakPoints.at(i).logicBreakPoint);
        }
    }

    if (this->subtitleStreams.size() > 0)
    {
        //bks->subtitleBreakPoints.resize(this->subtitleStreams.size());
        for (i = 0; i < this->subtitleStreams.size(); i++)
        {
            this->subtitleStreams.at(i)->Resume(bks->subtitleBreakPoints.at(i).streamBreakPoint);
            this->subtitleLogics.at(i)->Resume(bks->subtitleBreakPoints.at(i).logicBreakPoint);
        }
    }

    delete this->breakpoints;
    this->breakpoints = NULL;
    LeaveCriticalSection(&this->monitorMutex);

    dash_log(DASH_LOG_ERROR, "[%s,%d] resume done\n", __FUNCTION__, __LINE__);

    return true;
}

uint32_t    MultimediaManager::GetVideoAdaptationSetNum()
{
    if (mpd->GetPeriods().size() <= 0)
        return 0;

    IPeriod * period = GetCurrentPeriod();
    if (!AdaptationSetHelper::GetVideoAdaptationSets(period).empty())
    {
        this->videoAdaptationSets = AdaptationSetHelper::GetVideoAdaptationSets(period);
        return this->videoAdaptationSets.size();
    }

    return 0;
}

uint32_t    MultimediaManager::GetAudioAdaptationSetNum()
{
    if (mpd->GetPeriods().size() <= 0 )//|| (false == this->isISOFF)// do not depend on isISOFF, it is inited behind
        return 0;

    IPeriod * period = GetCurrentPeriod();
    if (!AdaptationSetHelper::GetAudioAdaptationSets(period).empty())
    {
        this->audioAdaptationSets = AdaptationSetHelper::GetAudioAdaptationSets(period);
        return this->audioAdaptationSets.size();
    }

    return 0;
}

uint32_t    MultimediaManager::GetSubtitleAdaptationSetNum()
{
    if (mpd->GetPeriods().size() <= 0)//|| (false == this->isISOFF)// do not depend on isISOFF, it is inited behind
        return 0;

    IPeriod * period = GetCurrentPeriod();
    if (!AdaptationSetHelper::GetSubtitleAdaptationSets(period).empty())
    {
        this->subtitleAdaptationSets = AdaptationSetHelper::GetSubtitleAdaptationSets(period);
        return this->subtitleAdaptationSets.size();
    }

    return 0;
}

IAdaptationSet  *MultimediaManager::GetVideoAdaptionSet(int adaptationSetIndex)
{
    if (this->videoAdaptationSets.size() <= adaptationSetIndex || adaptationSetIndex < 0)
        return NULL;

    return this->videoAdaptationSets.at(adaptationSetIndex);
}

IAdaptationSet  *MultimediaManager::GetAudioAdaptionSet(int adaptationSetIndex)
{
    if (this->audioAdaptationSets.size() <= adaptationSetIndex || adaptationSetIndex < 0)
        return NULL;

    return this->audioAdaptationSets.at(adaptationSetIndex);
}

IAdaptationSet  *MultimediaManager::GetSubtitleAdaptionSet(int adaptationSetIndex)
{
    if (this->subtitleAdaptationSets.size() <= adaptationSetIndex || adaptationSetIndex < 0)
        return NULL;

    return this->subtitleAdaptationSets.at(adaptationSetIndex);
}

RepresentationStreamType MultimediaManager::GetRepresentationStreamType()
{
    //TODO: different type?
    if (!this->videoLogics.empty())
    {
        ManualAdaptation * videoLogic = (ManualAdaptation *)this->videoLogics.at(0);
        return videoLogic->GetRepresentationStreamType();
    }

    if (!this->audioLogics.empty())
    {
        ManualAdaptation * audioLogic = (ManualAdaptation *)this->audioLogics.at(0);
        return audioLogic->GetRepresentationStreamType();
    }

    if (!this->subtitleLogics.empty())
    {
        ManualAdaptation * subtitleLogic = (ManualAdaptation *)this->subtitleLogics.at(0);
        return subtitleLogic->GetRepresentationStreamType();
    }

    return  UNDEFINED;
}

uint32_t    MultimediaManager::GetVideoSegmentDuration()
{
    if (!this->videoLogics.empty())
    {
        ManualAdaptation * videoLogic = (ManualAdaptation *)this->videoLogics.at(this->videoAdaptationSetIndex);
        return videoLogic->GetSegmentDuration();
    }

    return 0;
}

uint32_t    MultimediaManager::GetAudioSegmentDuration()
{
    if (!this->audioLogics.empty())
    {
        ManualAdaptation * audioLogic = (ManualAdaptation *)this->audioLogics.at(this->audioAdaptationSetIndex);
        return audioLogic->GetSegmentDuration();
    }

    return 0;
}

uint32_t    MultimediaManager::GetSubtitleSegmentDuration()
{
    if (!this->subtitleLogics.empty())
    {
        ManualAdaptation * subtitleLogic = (ManualAdaptation *)this->subtitleLogics.at(this->subtitleAdaptationSetIndex);
        return subtitleLogic->GetSegmentDuration();
    }

    return 0;
}

uint32_t    MultimediaManager::GetVideoSegmentDuration(int adaptationSetIndex)
{
    if (this->videoLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * videoLogic = (ManualAdaptation *)this->videoLogics.at(adaptationSetIndex);
        return videoLogic->GetSegmentDuration();
    }
    else
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get segment duration, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->videoLogics.size());

    return 0;
}

uint32_t    MultimediaManager::GetAudioSegmentDuration(int adaptationSetIndex)
{
    if (this->audioLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * audioLogic = (ManualAdaptation *)this->audioLogics.at(adaptationSetIndex);
        return audioLogic->GetSegmentDuration();
    }
    else
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get segment duration, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->audioLogics.size());

    return 0;
}

uint32_t    MultimediaManager::GetSubtitleSegmentDuration(int adaptationSetIndex)
{
    if (this->subtitleLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * subtitleLogic = (ManualAdaptation *)this->subtitleLogics.at(adaptationSetIndex);
        return subtitleLogic->GetSegmentDuration();
    }
    else
         dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get segment duration, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleLogics.size());

    return 0;
}

uint64_t    MultimediaManager::GetVideoSegmentEndTime(int adaptationSetIndex, uint32_t position)
{
    if (this->videoLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * videoLogic = (ManualAdaptation *)this->videoLogics.at(adaptationSetIndex);
        return videoLogic->GetSegmentEndTime(position);
    }
    else
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get segment end time, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->videoLogics.size());

    return 0;
}

uint64_t    MultimediaManager::GetAudioSegmentEndTime(int adaptationSetIndex, uint32_t position)
{
    if (this->audioLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * audioLogic = (ManualAdaptation *)this->audioLogics.at(adaptationSetIndex);
        return audioLogic->GetSegmentEndTime(position);
    }
    else
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get segment end time, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->audioLogics.size());

    return 0;
}

uint64_t    MultimediaManager::GetSubtitleSegmentEndTime(int adaptationSetIndex, uint32_t position)
{
    if (this->subtitleLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * subtitleLogic = (ManualAdaptation *)this->subtitleLogics.at(adaptationSetIndex);
        return subtitleLogic->GetSegmentEndTime(position);
    }
    else
         dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get segment end time, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleLogics.size());

    return 0;
}

uint64_t    MultimediaManager::GetVideoSegmentStartTime(int adaptationSetIndex, uint32_t position)
{
    if (this->videoLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * logic = (ManualAdaptation *)this->videoLogics.at(adaptationSetIndex);
        return logic->GetSegmentStartTime(position);
    }
    else
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get segment start time, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->videoLogics.size());

    return 0;
}

uint64_t    MultimediaManager::GetAudioSegmentStartTime(int adaptationSetIndex, uint32_t position)
{
    if (this->audioLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * logic = (ManualAdaptation *)this->audioLogics.at(adaptationSetIndex);
        return logic->GetSegmentStartTime(position);
    }
    else
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get segment start time, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->audioLogics.size());

    return 0;
}

uint64_t    MultimediaManager::GetSubtitleSegmentStartTime(int adaptationSetIndex, uint32_t position)
{
    if (this->subtitleLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * logic = (ManualAdaptation *)this->subtitleLogics.at(adaptationSetIndex);
        return logic->GetSegmentStartTime(position);
    }
    else
         dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get segment start time, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleLogics.size());

    return 0;
}

uint32_t    MultimediaManager::GetVideoPositionFromTime(int adaptationSetIndex, int64_t ms, int direct)
{
    if (this->videoLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * logic = (ManualAdaptation *)this->videoLogics.at(adaptationSetIndex);
        return logic->GetPositionFromTime(ms, direct);
    }
    else
         dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get position, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->videoLogics.size());

    return 0;
}

uint32_t    MultimediaManager::GetAudioPositionFromTime(int adaptationSetIndex, int64_t ms, int direct)
{
    if (this->audioLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * logic = (ManualAdaptation *)this->audioLogics.at(adaptationSetIndex);
        return logic->GetPositionFromTime(ms, direct);
    }
    else
         dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get position, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->audioLogics.size());

    return 0;
}

uint32_t    MultimediaManager::GetSubtitlePositionFromTime(int adaptationSetIndex, int64_t ms, int direct)
{
    if (this->subtitleLogics.size() > adaptationSetIndex && adaptationSetIndex >= 0)
    {
        ManualAdaptation * logic = (ManualAdaptation *)this->subtitleLogics.at(adaptationSetIndex);
        return logic->GetPositionFromTime(ms, direct);
    }
    else
         dash_log(DASH_LOG_ERROR, "[%s,%d] fail to get position, invalid adaptationSetIndex %d, scope [0, %u)\n",
        __FUNCTION__, __LINE__, adaptationSetIndex, this->subtitleLogics.size());

    return 0;
}

bool        MultimediaManager::_findFFSignInAdaptationSet(dash::mpd::IAdaptationSet * adaptationSet)
{
    int j, repCount;

    if (adaptationSet == NULL)
        return false;

    if (adaptationSet->GetMimeType().find("mp4") != std::string::npos)
    {
        this->isISOFF = true;
        return true;
    }
    else if (adaptationSet->GetMimeType().find("mp2t") != std::string::npos)
    {
        this->isISOFF = false;
        return true;
    }

    repCount = adaptationSet->GetRepresentation().size();
    for (j = 0; j < repCount; j++)
    {
        if (adaptationSet->GetRepresentation().at(j)->GetMimeType().find("mp4") != std::string::npos)
        {
            this->isISOFF = true;
            return true;
        }
        else if (adaptationSet->GetRepresentation().at(j)->GetMimeType().find("mp2t") != std::string::npos)
        {
            this->isISOFF = false;
            return true;
         }
    }

    return false;
}

bool        MultimediaManager::_IsISOFF()
{
    int i, adaptCount;
    bool bFileFormatFound = false;
    std::vector<dash::mpd::IAdaptationSet *> *adaptationSet = NULL;

    if (!mpd->GetProfiles().empty())
    {
        std::string profile = mpd->GetProfiles().at(0);
        /*
        if (profile.find("isoff") != std::string::npos)
            this->isISOFF = true;
        else if (profile.find("mp2t") != std::string::npos)
            this->isISOFF = false;
            */
         if (profile.find("mp2t") != std::string::npos)
         {
            this->isISOFF = false;
            bFileFormatFound = true;
         }
         else
         {
            if (profile.find("isoff") != std::string::npos)
            {
                this->isISOFF = true;
                bFileFormatFound = true;
            }
            else
            {
                if (this->videoAdaptationSets.size() > 0)
                {
                    adaptationSet = &(this->videoAdaptationSets);
                    adaptCount = this->videoAdaptationSets.size();
                }
                else if (this->audioAdaptationSets.size() > 0)
                {
                    adaptationSet = &(this->audioAdaptationSets);
                    adaptCount = this->audioAdaptationSets.size();
                }

                if (adaptationSet != NULL && adaptCount > 0)
                {
                    for (i = 0; i < adaptCount; i ++)
                    {
                        if(_findFFSignInAdaptationSet(adaptationSet->at(i)))
                        {
                            bFileFormatFound = true;
                            break;
                        }
                    }
                }
            }
         }

         if (bFileFormatFound == false)
         {
            dash_log(DASH_LOG_ERROR, "[%s,%d] dash segment file format is unknown, isISOFF default to %d...\n",
                __FUNCTION__, __LINE__, this->isISOFF);
         }

        return this->isISOFF;
    }

    return false;
}

bool        MultimediaManager::IsISOFF()
{
    if (this->mpd == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] MultimediaManager not inited, the result is not trusty!\n", __FUNCTION__, __LINE__);
    }

    return this->isISOFF;
}

std::string&    MultimediaManager::GetVideoIndexSegment()
{
    if (!this->videoAdaptationSets.empty())
    {
        int representationIndex = this->videoRepresentationIndexes.at(videoAdaptationSetIndex);
        IAdaptationSet * adaptationSet = this->videoAdaptationSets.at(videoAdaptationSetIndex);
        IRepresentation * videoRepresentation = adaptationSet->GetRepresentation().at(representationIndex);

        std::string indexurl = "";
        std::string baseurl = "";

        if (videoRepresentation->GetSegmentBase() && videoRepresentation->GetSegmentBase()->GetRepresentationIndex())
            indexurl = videoRepresentation->GetSegmentBase()->GetRepresentationIndex()->GetSourceURL();

        baseurl = BaseUrlResolver::ResolveBaseUrl(mpd, period, adaptationSet, 0, 0, 0).at(0)->GetUrl();

        indexSegmentURL = baseurl + "/" + indexurl;
    }

    return indexSegmentURL;
}

std::string&    MultimediaManager::GetAudioIndexSegment()
{
   //Currently unused
    return indexSegmentURL;
}

std::string&    MultimediaManager::GetSubtitleIndexSegment()
{
    //Currently unused
    return indexSegmentURL;
}

std::string&    MultimediaManager::GetVideoRating()
{
    if (!videoAdaptationSets.empty())
    {
        //TODO:: how to use Rating Info?
        IAdaptationSet *adaptationSet = videoAdaptationSets.at(videoAdaptationSetIndex);
        if (adaptationSet->GetRating().size() > 0)
        {
            this->videoRating = adaptationSet->GetRating().at(0)->GetSchemeIdUri();
        }
        else if (adaptationSet->GetContentComponent().size() > 0)
        {
            IContentComponent * contentComponent = adaptationSet->GetContentComponent().at(0);
            if (contentComponent->GetRating().size() > 0)
                this->videoRating = contentComponent->GetRating().at(0)->GetSchemeIdUri();
        }

        return this->videoRating;
    }

    return this->videoRating;
}

std::string&    MultimediaManager::GetAudioRating()
{
    if (!audioAdaptationSets.empty())
    {
        //TODO:: how to use Rating Info?
        IAdaptationSet *adaptationSet = audioAdaptationSets.at(audioAdaptationSetIndex);
        if (adaptationSet->GetRating().size() > 0)
        {
            this->audioRating = adaptationSet->GetRating().at(0)->GetSchemeIdUri();
        }
        else if (adaptationSet->GetContentComponent().size() > 0)
        {
            IContentComponent * contentComponent = adaptationSet->GetContentComponent().at(0);
            if (contentComponent->GetRating().size() > 0)
                this->audioRating = contentComponent->GetRating().at(0)->GetSchemeIdUri();
        }

        return this->audioRating;
    }

    return this->audioRating;
}

std::string&    MultimediaManager::GetSubtitleRating()
{
    if (!subtitleAdaptationSets.empty())
    {
        //TODO:: how to use Rating Info?
        IAdaptationSet *adaptationSet = subtitleAdaptationSets.at(subtitleAdaptationSetIndex);
        if (adaptationSet->GetRating().size() > 0)
        {
            this->subtitleRating = adaptationSet->GetRating().at(0)->GetSchemeIdUri();
        }
        else if (adaptationSet->GetContentComponent().size() > 0)
        {
            IContentComponent * contentComponent = adaptationSet->GetContentComponent().at(0);
            if (contentComponent->GetRating().size() > 0)
                this->subtitleRating = contentComponent->GetRating().at(0)->GetSchemeIdUri();
        }

        return this->subtitleRating;
    }

    return this->subtitleRating;
}

bool            MultimediaManager::VideoEosReached()
{
    if (!videoStreams.empty())
        return videoStreams.at(videoAdaptationSetIndex)->CheckEosReached();

    return false;
}

bool            MultimediaManager::AudioEosReached()
{
    if (!audioStreams.empty())
        return audioStreams.at(audioAdaptationSetIndex)->CheckEosReached();

    return false;
}

bool            MultimediaManager::SubtitleEosReached()
{
    if (!subtitleStreams.empty())
        return subtitleStreams.at(subtitleAdaptationSetIndex)->CheckEosReached();

    return false;
}

int             MultimediaManager::GetSubtitleType(int subtitleAdaptationSetIndex)
{
    if (!subtitleAdaptationSets.empty())
    {
        IAdaptationSet *adaptationSet = subtitleAdaptationSets.at(subtitleAdaptationSetIndex);
        if (adaptationSet->GetMimeType().find("application/ttml+xml") != std::string::npos)
            return Subtitle_TTML;

        for (size_t i = 0; i < adaptationSet->GetRepresentation().size(); i++)
        {
           IRepresentation *subtitleRepresentation = adaptationSet->GetRepresentation().at(i);
           std::vector<std::string> codecs = subtitleRepresentation->GetCodecs();
           if (!codecs.empty())
           {
                if (codecs.at(0).find("tx3g") != std::string::npos)
                {
                    return Subtitle_TX3G | Subtitle_ISO_Mask;
                }
                else if (codecs.at(0).find("stpp") != std::string::npos)
                {
                    return Subtitle_TTML | Subtitle_ISO_Mask;
                }
           }
        }

    }

    return Subtitle_UNSUPPROTED;
}

void             MultimediaManager::Interrupt()
{
    size_t i = 0;

    if (!this->videoStreams.empty())
    {
        for (i = 0; i < videoStreams.size(); i++)
        {
           videoStreams.at(i)->GetReceiver()->Interrupt();
        }
    }

    if (!this->audioStreams.empty())
    {
        for (i = 0; i < audioStreams.size(); i++)
        {
           audioStreams.at(i)->GetReceiver()->Interrupt();
        }
    }

    if (!this->subtitleStreams.empty())
    {
        for (i = 0; i < subtitleStreams.size(); i++)
        {
           subtitleStreams.at(i)->GetReceiver()->Interrupt();
        }
    }

    return;
}

//Get target Segment URL by specifying the 'Adaptation Index','Representation Index' and 'position'
std::string&    MultimediaManager::GetVideoSegmentURL(int videoAdaptationSetIndex, int videoRepresentationIndex, uint32_t position)
{
    if (!this->videoLogics.empty() && videoAdaptationSetIndex < videoLogics.size())
    {
        ManualAdaptation * videoLogic = (ManualAdaptation *)this->videoLogics.at(this->videoAdaptationSetIndex);
        if (!this->videoAdaptationSets.empty())
        {
            IAdaptationSet * adaptationSet = this->videoAdaptationSets.at(videoAdaptationSetIndex);
            IRepresentation * videoRepresentation = adaptationSet->GetRepresentation().at(videoRepresentationIndex);
            this->segmentURL = videoLogic->GetSegmentURL(videoRepresentation, position);
        }
    }

    return this->segmentURL;
}

std::string&    MultimediaManager::GetAudioSegmentURL(int audioAdaptationSetIndex, int audioRepresentationIndex, uint32_t position)
{
    if (!this->audioLogics.empty() && audioAdaptationSetIndex < audioLogics.size())
    {
        ManualAdaptation * audioLogic = (ManualAdaptation *)this->audioLogics.at(this->audioAdaptationSetIndex);
        if (!this->audioAdaptationSets.empty())
        {
            IAdaptationSet * adaptationSet = this->audioAdaptationSets.at(audioAdaptationSetIndex);
            IRepresentation * audioRepresentation = adaptationSet->GetRepresentation().at(audioRepresentationIndex);
            this->segmentURL = audioLogic->GetSegmentURL(audioRepresentation, position);
        }
    }

    return this->segmentURL;
}

std::string&    MultimediaManager::GetSubtitleSegmentURL(int subtitleAdaptationSetIndex, int subtitleRepresentationIndex, uint32_t position)
{
    if (!this->subtitleLogics.empty() && subtitleAdaptationSetIndex < subtitleLogics.size())
    {
        ManualAdaptation * subtitleLogic = (ManualAdaptation *)this->subtitleLogics.at(this->subtitleAdaptationSetIndex);
        if (!this->subtitleAdaptationSets.empty())
        {
            IAdaptationSet * adaptationSet = this->subtitleAdaptationSets.at(subtitleAdaptationSetIndex);
            IRepresentation * subtitleRepresentation = adaptationSet->GetRepresentation().at(subtitleRepresentationIndex);
            this->segmentURL = subtitleLogic->GetSegmentURL(subtitleRepresentation, position);
        }
    }

    return this->segmentURL;
}

int           MultimediaManager::SetVideoRepresentationSAPs(int adaptationSetIndex, int representationIndex, std::vector<uint64_t>& saps)
{
    IAdaptationSet * adaptationSet;
    IRepresentation *representation;

    if (this->videoLogics.size() <= adaptationSetIndex || this->videoAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] AdaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->videoLogics.size(), this->videoAdaptationSets.size());
        return -1;
    }

    if (this->videoState.at(adaptationSetIndex) == MANAGER_STATE_RUNNING)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] AdaptationSetIndex %d is running, must set saps in stop state! \n",
            __FUNCTION__, __LINE__, adaptationSetIndex);
        return -1;
    }

    adaptationSet = this->videoAdaptationSets.at(adaptationSetIndex);

    if (adaptationSet->GetRepresentation().size() <= representationIndex)
    {
         dash_log(DASH_LOG_ERROR, "[%s,%d] AdaptationSet %d , representationIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, adaptationSet->GetRepresentation().size());
        return -1;
    }
    representation  = adaptationSet->GetRepresentation().at(representationIndex);

    return this->videoLogics.at(adaptationSetIndex)->SetSAPs(representation, saps);
}

int           MultimediaManager::SetAudioRepresentationSAPs(int adaptationSetIndex, int representationIndex, std::vector<uint64_t>& saps)
{
    IAdaptationSet * adaptationSet;
    IRepresentation *representation;

    if (this->audioLogics.size() <= adaptationSetIndex || this->audioAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] AdaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->audioLogics.size(), this->audioAdaptationSets.size());
        return -1;
    }

    if (this->audioState.at(adaptationSetIndex) == MANAGER_STATE_RUNNING)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] AdaptationSetIndex %d is running, must set saps in stop state! \n",
            __FUNCTION__, __LINE__, adaptationSetIndex);
        return -1;
    }

    adaptationSet = this->audioAdaptationSets.at(adaptationSetIndex);
    if (adaptationSet->GetRepresentation().size() <= representationIndex)
    {
         dash_log(DASH_LOG_ERROR, "[%s,%d] AdaptationSet %d , representationIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, adaptationSet->GetRepresentation().size());
        return -1;
    }
    representation  = adaptationSet->GetRepresentation().at(representationIndex);

    return this->audioLogics.at(adaptationSetIndex)->SetSAPs(representation, saps);
}

int           MultimediaManager::SetSubtitleRepresentationSAPs(int adaptationSetIndex, int representationIndex, std::vector<uint64_t>& saps)
{
    IAdaptationSet * adaptationSet;
    IRepresentation *representation;

    if (this->subtitleLogics.size() <= adaptationSetIndex || this->subtitleAdaptationSets.size() <= adaptationSetIndex)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] AdaptationSetIndex %d invalid, scope [0, %u(%u))\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, this->audioLogics.size(), this->audioAdaptationSets.size());
        return -1;
    }

    if (this->subtitleState.at(adaptationSetIndex) == MANAGER_STATE_RUNNING)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] AdaptationSetIndex %d is running, must set saps in stop state! \n",
            __FUNCTION__, __LINE__, adaptationSetIndex);
        return -1;
    }

    adaptationSet = this->subtitleAdaptationSets.at(adaptationSetIndex);
    if (adaptationSet->GetRepresentation().size() <= representationIndex)
    {
         dash_log(DASH_LOG_ERROR, "[%s,%d] AdaptationSet %d , representationIndex %d invalid, scope [0, %u)\n",
            __FUNCTION__, __LINE__, adaptationSetIndex, adaptationSet->GetRepresentation().size());
        return -1;
    }
    representation  = adaptationSet->GetRepresentation().at(representationIndex);

    return this->subtitleLogics.at(adaptationSetIndex)->SetSAPs(representation, saps);
}

/*
 *  MPEG DASH Content Protection using PlayReady 1.1
 *  Chapter 2 PLAYREADY DASH CONTENT PROTECTION SCHEME:

 *  The four scenarios which are the focus of this specification are VOD or live presentations of media:
 *  1.encrypted with a single key
 *    ...

 *  so we just retun the first Content & pro info
 */

bool     MultimediaManager::CheckUUID      (std::string &uuid)
{
    if (this->mpd == NULL)
        return false;

    dash_log(DASH_LOG_INFO, "%s %d\n",  __FILE__, __LINE__);
    if (!this->videoAdaptationSets.empty())
    {
        dash_log(DASH_LOG_INFO, "%s %d\n",  __FILE__, __LINE__);
        IAdaptationSet * adaptationSet = this->videoAdaptationSets.at(0);
        for (size_t i = 0; i < adaptationSet->GetContentProtection().size(); i++)
        {
            dash_log(DASH_LOG_INFO, "%s %d\n",  __FILE__, __LINE__);
            std::string schemeIdUri = adaptationSet->GetContentProtection().at(i)->GetSchemeIdUri();
            if (schemeIdUri != "" && schemeIdUri.find(uuid) != std::string::npos)
            {
                dash_log(DASH_LOG_INFO, "return uuid:%s\n", schemeIdUri.c_str());
                return true;
            }
        }
    }

    if (!this->audioAdaptationSets.empty())
    {
        IAdaptationSet * adaptationSet = this->audioAdaptationSets.at(0);
        for (size_t i = 0; i < adaptationSet->GetContentProtection().size(); i++)
        {
            std::string schemeIdUri = adaptationSet->GetContentProtection().at(i)->GetSchemeIdUri();
            if (schemeIdUri != "" && schemeIdUri.find(uuid) != std::string::npos)
                return true;
        }
    }

    return false;
}

std::string     MultimediaManager::GetPRO       ()
{
    if (this->mpd == NULL)
        return "";

    if (!this->videoAdaptationSets.empty())
    {
        dash_log(DASH_LOG_INFO, "%s %d\n",  __FILE__, __LINE__);
        IAdaptationSet * adaptationSet = this->videoAdaptationSets.at(0);
        for (size_t i = 0; i < adaptationSet->GetContentProtection().size(); i++)
        {
            for (size_t j = 0; j < adaptationSet->GetContentProtection().at(i)->GetMSPR().size(); j++)
            {
                IMSPR * mspr = adaptationSet->GetContentProtection().at(i)->GetMSPR().at(j);
                if (mspr->GetPRO() != "")
                {
                    dash_log(DASH_LOG_INFO, "Get Video PRO data!\n");
                    return mspr->GetPRO();
                }
            }
        }
    }

    if (!this->audioAdaptationSets.empty())
    {
        dash_log(DASH_LOG_INFO, "%s %d\n",  __FILE__, __LINE__);
        IAdaptationSet * adaptationSet = this->audioAdaptationSets.at(0);
        for (size_t i = 0; i < adaptationSet->GetContentProtection().size(); i++)
        {
            for (size_t j = 0; j < adaptationSet->GetContentProtection().at(i)->GetMSPR().size(); j++)
            {
                IMSPR * mspr = adaptationSet->GetContentProtection().at(i)->GetMSPR().at(j);
                if (mspr->GetPRO() != "")
                {
                    dash_log(DASH_LOG_INFO, "Get Audio PRO data\n");
                    return mspr->GetPRO();
                }
            }
        }
    }

    return "";
}
