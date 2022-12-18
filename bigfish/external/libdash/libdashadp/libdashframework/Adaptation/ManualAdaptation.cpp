/*
 * ManualAdaptation.cpp
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "ManualAdaptation.h"
#include <stdio.h>

using namespace dash::mpd;
using namespace libdash::framework::adaptation;
using namespace libdash::framework::input;
using namespace libdash::framework::mpd;
using namespace dash::helpers;

ManualAdaptation::ManualAdaptation          (dash::mpd::IPeriod *period, dash::mpd::IAdaptationSet *adaptationSet, dash::mpd::IMPD *mpd, uint32_t bufferSize, void *breakpoint) :
                  AbstractAdaptationLogic   (period, adaptationSet, mpd, bufferSize),
                  period                    (period),
                  adaptationSet             (adaptationSet),
                  adaptationSetStream       (NULL),
                  representationStream      (NULL),
                  mpd                       (mpd),
                  segmentNumber             (0),
                  invokeInitSegment         (NO_INVOKE),
                  state                          (LOGIC_STATE_RUN),
                  segmentURL                ("")
{
    this->representationIndex = 0;
    this->representation        = this->adaptationSet->GetRepresentation().at(this->representationIndex);
    this->adaptationSetStream   = new AdaptationSetStream(mpd, period, adaptationSet);
    this->representationStream  = adaptationSetStream->GetRepresentationStream(this->representation);
    this->representationStreamType = this->representationStream->GetStreamType();
    if (breakpoint == NULL)
    {
        this->segmentOffset         = CalculateSegmentOffset();
        dash_log(DASH_LOG_INFO, "[%s,%d] ManualAdaptation[%p] construct with segmentOffset:%u\n", __FUNCTION__, __LINE__, this, this->segmentOffset);
    }
    else
    {
        this->segmentOffset         = (uint32_t)breakpoint;
        dash_log(DASH_LOG_INFO, "[%s,%d] ManualAdaptation[%p] construct with breakpoint segmentOffset:%u\n", __FUNCTION__, __LINE__, this, this->segmentOffset);
    }
    InitializeCriticalSection   (&this->monitorMutex);
}
ManualAdaptation::~ManualAdaptation         ()
{
    delete(adaptationSetStream);
    DeleteCriticalSection   (&this->monitorMutex);
}

void *ManualAdaptation::Pause()
{
    dash_log(DASH_LOG_INFO, "[%s,%d] ManualAdaptation[%p]  paused with segmentOffset:%u\n", __FUNCTION__, __LINE__, this, this->segmentOffset);
    return (void *)this->segmentOffset;
}

bool ManualAdaptation::Resume(void * breakpoint)
{
    return true;
}

LogicType       ManualAdaptation::GetType               ()
{
    return adaptation::Manual;
}
MediaObject*    ManualAdaptation::GetSegment            (int type)
{
    ISegment *seg = NULL;
    bool isInitSeg = false;
    MediaObject *media = NULL;
    double durationSeconds;
    uint64_t curSegEndTime, lastSegEndTime;

    EnterCriticalSection(&this->monitorMutex);

    if (this->state == LOGIC_STATE_EOS)
    {
        //dash_log("[%s,%d] ManualAdaptation[%p] is eos!\n", __FUNCTION__, __LINE__, this);
        LeaveCriticalSection(&this->monitorMutex);
        return NULL;
    }

    //if occurred, this event must be reported immediately
    if (TimeResolver::CheckTimeInterval(this->mpd->GetAvailabilityStarttime(),
        this->mpd->GetAvailabilityEndtime()) == false)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] segments not available!\n", __FUNCTION__, __LINE__);
        media = new MediaObject(LOGIC_EVENT_ERROR|LOGIC_ERROR_TYPE_STREAM_NOTAVAILABLE);
        this->state = LOGIC_STATE_EOS;
        LeaveCriticalSection(&this->monitorMutex);
        return media;
    }

    if (type == SEG_TYPE_EVENT)
    {
        LeaveCriticalSection(&this->monitorMutex);
        return NULL;
    }

    if (this->segmentNumber >= this->representationStream->GetSize() + 1)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] segments index beyond the range!\n", __FUNCTION__, __LINE__);
        media = new MediaObject(LOGIC_EVENT_EOS|this->representationIndex);
        this->state = LOGIC_STATE_EOS;
        LeaveCriticalSection(&this->monitorMutex);
        return media;
    }

    if (this->representationStreamType != SingleMediaSegment)
    {
        durationSeconds = dash::helpers::String::timeToSeconds(this->period->GetDuration());
        if (durationSeconds <= 0)
            durationSeconds = dash::helpers::String::timeToSeconds(this->mpd->GetMediaPresentationDuration());
        durationSeconds = 1000 * durationSeconds;

        curSegEndTime = GetSegmentEndTime(this->segmentNumber + segmentOffset);
        if (this->segmentNumber + segmentOffset > 0)
        {
            lastSegEndTime = GetSegmentEndTime(this->segmentNumber + segmentOffset - 1);
        }
        else
        {
            lastSegEndTime = 0;
        }

        if (durationSeconds > 0 &&  curSegEndTime > durationSeconds && lastSegEndTime >= durationSeconds)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] curSegNum %u, curSegEndTime %llu is beyond the period duration %llf!\n", __FUNCTION__, __LINE__, (this->segmentNumber + segmentOffset), curSegEndTime, durationSeconds);
            media = new MediaObject(LOGIC_EVENT_EOS|this->representationIndex);
            this->state = LOGIC_STATE_EOS;
            LeaveCriticalSection(&this->monitorMutex);
            return media;
        }
    }

#if 0
    //just for hbbtv testcase
    if (isLive())
    {
        uint64_t curTimeOffInMS =  GetCurrentTimeOffset() * 1000ULL;
        uint64_t segStartTime    = GetSegmentStartTime(this->segmentNumber + segmentOffset);

        if (segStartTime > curTimeOffInMS && curTimeOffInMS > 0)
        {
            LeaveCriticalSection(&this->monitorMutex);
           // dash_log("[%s,%d] segment not ready, segStartTime:%llu, curTimeOffInMS:%llu\n",
             //   __FUNCTION__, __LINE__, segStartTime, curTimeOffInMS);
            return NULL;
        }
    }
#endif

    if (this->invokeInitSegment == PRE_INVOKE)
    {
         //we return a specify object that declare a init segment will flow this
        //so that in dashadp, we can reopen the avformat.
        media = new MediaObject(LOGIC_EVENT_PRE_INITSEGMENT|this->representationIndex);
        this->invokeInitSegment = DO_INVOKE;
        LeaveCriticalSection(&this->monitorMutex);
        return media;
    }

    //TODO: bssw segment
    if(this->invokeInitSegment == DO_INVOKE)
    {
        switch(this->representationStreamType)
        {
            case SingleMediaSegment:

                seg = this->representationStream->GetInitializationSegment();
                if (seg == NULL)
                {
                    seg = this->representationStream->GetMediaSegment(0);
                    if (this->segmentNumber + segmentOffset != 0)// do not skip current segnumber
                    {
                        isInitSeg = true;
                    }
                }
                else
                {
                    isInitSeg = true;
                }

                this->invokeInitSegment = NO_INVOKE;
#if 0
                //Init-info is in "Initialization-Segment" or "Media-Segment" and can't be NULL
                if (this->positionOffset > 0 && seg != NULL)
                {
                    std::stringstream ss;
                    std::string range;
                    ss << this->positionOffset;
                    ss >> range;
                    seg->HasByteRange(true);
                    seg->Range(range + "-");
                    seg->StartByte(this->positionOffset);
                }
#endif
                break;
            case SegmentList:
            case SegmentTemplate:
                seg = this->representationStream->GetInitializationSegment();
                this->invokeInitSegment = NO_INVOKE;

                if (seg == NULL)
                {
                    //Try to get Init-info from "Initialization sourceURL@SegmentList" from AdaptationSet
                    if (this->adaptationSet->GetSegmentList())
                    {
                        seg = this->adaptationSet->GetSegmentList()->ToInitializationSegment(BaseUrlResolver::ResolveBaseUrl(mpd, period, adaptationSet, 0, 0, 0),
                            representation->GetId(), representation->GetBandwidth());
                    }
                }

                //Try to get Init-info from media segment inside
                if (seg == NULL)
                {
                    seg = this->representationStream->GetMediaSegment(this->segmentNumber + segmentOffset);
                   // this->segmentNumber++;
                }
                else
                {
                     isInitSeg = true;
                }

                if (seg == NULL)
                {
                    dash_log(DASH_LOG_ERROR, "[%s,%d] ManualAdaptation[%p] GetMediaSegment return null, return EOS object.\n", __FUNCTION__, __LINE__, this);
                    media = new MediaObject(LOGIC_EVENT_EOS|this->representationIndex);
                    this->state = LOGIC_STATE_EOS;
                    LeaveCriticalSection(&this->monitorMutex);
                    return NULL;
                }

                break;
            default:
                media = new MediaObject(LOGIC_EVENT_EOS|this->representationIndex);
                this->state = LOGIC_STATE_EOS;
                LeaveCriticalSection(&this->monitorMutex);
                return NULL;
        }
        /*
        else if (this->representationStream->GetBitstreamSwitchingSegment())
        {
            //bssw segment
            seg = this->representationStream->GetBitstreamSwitchingSegment();
            this->segmentNumber--;
        }
        */
    }
    else
    {
            seg = this->representationStream->GetMediaSegment(this->segmentNumber + segmentOffset);//from 1...N
    }

    if (seg != NULL)
    {
        if (!isInitSeg)
        {
            media = new MediaObject(seg, this->representation, MEDIA_SEGMENT_TYPE_NORMAL);
            this->segmentNumber++;
        }
        else
        {
            media = new MediaObject(seg, this->representation, MEDIA_SEGMENT_TYPE_INIT);
        }
        LeaveCriticalSection(&this->monitorMutex);
        return media;
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] ManualAdaptation[%p] GetMediaSegment return null, return EOS object.\n", __FUNCTION__, __LINE__, this);
        media = new MediaObject(LOGIC_EVENT_EOS|this->representationIndex);
        this->state = LOGIC_STATE_EOS;
        LeaveCriticalSection(&this->monitorMutex);
        return media;
    }

}

bool    ManualAdaptation::isLive   ()
{
    if (this->mpd->GetType() == "dynamic")
        return true;

    return false;
}

uint32_t        ManualAdaptation::GetPosition           ()
{
    return (this->segmentNumber + segmentOffset);
}
void            ManualAdaptation::SetPosition           (uint32_t segmentNumber)
{
    switch(this->representationStreamType)
    {
        case SingleMediaSegment:
        case SegmentList:
        case SegmentTemplate:
            EnterCriticalSection(&this->monitorMutex);
            //do not use offset when segment number is setted to other than 0xffffffff
            if (segmentNumber != 0xffffffff)
            {
                this->segmentNumber = segmentNumber;
                segmentOffset = 0;
            }
            else
            {
                this->segmentNumber = 0;
            }
            this->state = LOGIC_STATE_RUN;
            LeaveCriticalSection(&this->monitorMutex);
            dash_log(DASH_LOG_INFO, "[%s,%d] ManualAdaptation[%p] set segmentNumber=%u, this->segmentNumber =%u,segmentOffset=%u\n",
                __FUNCTION__, __LINE__, this, segmentNumber, this->segmentNumber, segmentOffset);
            break;
        default:
            break;
    }
}

void            ManualAdaptation::SetRepresentation     (dash::mpd::IRepresentation *representation, int index, bool invokeInitSeg)
{
    EnterCriticalSection(&this->monitorMutex);
    this->representation        = representation;
    this->representationIndex = index;
    this->representationStream  = adaptationSetStream->GetRepresentationStream(representation);
    if (this->invokeInitSegment == NO_INVOKE && invokeInitSeg)
        this->invokeInitSegment = PRE_INVOKE;
    else if (this->invokeInitSegment == PRE_INVOKE && !invokeInitSeg)
        this->invokeInitSegment = NO_INVOKE;

    LeaveCriticalSection(&this->monitorMutex);
    dash_log(DASH_LOG_INFO, "[%s,%d] ManualAdaptation[%p]presentation changed to @id=%s, @bandwidth=%u, invokeInitSeg:%d, invokeInitSeg state:%d\n",
        __FUNCTION__, __LINE__, this, representation->GetId().c_str(), representation->GetBandwidth(), invokeInitSeg, this->invokeInitSegment);
}

int              ManualAdaptation::GetCurrentRepresentationIndex()
{
    return this->representationIndex;
}

void            ManualAdaptation::InvokeInitSegment     (bool invoke)
{
    EnterCriticalSection(&this->monitorMutex);
    if (this->invokeInitSegment == NO_INVOKE && invoke)
        this->invokeInitSegment = PRE_INVOKE;
    else if (this->invokeInitSegment == PRE_INVOKE && !invoke)
        this->invokeInitSegment = NO_INVOKE;
    LeaveCriticalSection(&this->monitorMutex);
}

uint32_t        ManualAdaptation::CalculateSegmentOffset()
{
    if (mpd->GetType() == "static")
        return 0;

    uint32_t firstSegNum = this->representationStream->GetFirstSegmentNumber();
    uint32_t currSegNum  = this->representationStream->GetCurrentSegmentNumber();
    uint32_t startSegNum  = 0;//currSegNum - 2*bufferSize;
    uint32_t u32Offset;

    if (currSegNum > 2*bufferSize)
        startSegNum = currSegNum - 2*bufferSize;

    u32Offset = (startSegNum > firstSegNum) ? startSegNum : firstSegNum;
    dash_log(DASH_LOG_INFO, "[%s,%d] ManualAdaptation[%p] firstSegNum:%u, currSegNum:%u, startSegNum:%u, u32Offset:%u\n",
        __FUNCTION__, __LINE__, this, firstSegNum, currSegNum, startSegNum, u32Offset);

    return u32Offset;
}

RepresentationStreamType ManualAdaptation::GetRepresentationStreamType()
{
    return this->representationStreamType;
}

uint32_t    ManualAdaptation::GetSegmentDuration()
{
    return this->representationStream->GetAverageSegmentDuration();
}

uint64_t   ManualAdaptation::GetSegmentEndTime(uint32_t position)
{
   // dash_log("[%s,%d] segment %d dur:%u\n", __FUNCTION__, __LINE__, position, GetSegmentDuration());
    if (GetSegmentDuration() > 0)
    {
        return ((uint64_t)(position + 1) * GetSegmentDuration());
    }
    else
        return this->representationStream->GetSegmentEndTime(position);
}

uint64_t   ManualAdaptation::GetSegmentStartTime(uint32_t position)
{
   // dash_log("[%s,%d] segment %d dur:%u\n", __FUNCTION__, __LINE__, position, GetSegmentDuration());
    if (GetSegmentDuration() > 0)
    {
        return ((uint64_t)(position) * GetSegmentDuration());
    }
    else
        return this->representationStream->GetSegmentStartTime(position);
}

uint32_t   ManualAdaptation::GetPositionFromTime(int64_t ms, int direct)
{
    uint32_t segDur = GetSegmentDuration();
   // dash_log("[%s,%d] segment %d dur:%u\n", __FUNCTION__, __LINE__, position, GetSegmentDuration());
    if (ms < 0)
        return 0;

    if (segDur > 0)
    {
        if (direct > 0)
        {
            return ((ms + segDur - 1)/segDur);
        }
        else
        {
            return (ms /segDur);
        }
    }
    else
        return this->representationStream->GetPositionFromTime(ms, direct);
}

ISegment*   ManualAdaptation::GetIndexSegment()
{
    if (SingleMediaSegment == this->representationStreamType)
        return this->representationStream->GetIndexSegment(0);

    return NULL;
}

std::string&     ManualAdaptation::GetSegmentURL(IRepresentation * representation ,uint32_t position)
{
    ISegment *seg = NULL;
    IRepresentationStream * representationStream = adaptationSetStream->GetRepresentationStream(representation);

    if (SingleMediaSegment == this->representationStreamType)
    {
        seg = representationStream->GetInitializationSegment();
    }
    else
    {
        seg = representationStream->GetMediaSegment(position - 1 + segmentOffset);
    }

    this->segmentURL = seg->AbsoluteURI();

    delete seg;
    return this->segmentURL;
}

uint32_t    ManualAdaptation::GetCurrentTimeOffset   ()
{
    if (this->mpd->GetType() == "dynamic")
    {
        uint32_t currTime = TimeResolver::GetCurrentTimeInSec();
        uint32_t availStT  = TimeResolver::GetUTCDateTimeInSec(this->mpd->GetAvailabilityStarttime());
        uint32_t periodStT = TimeResolver::GetDurationInSec(this->period->GetStart());
        uint32_t offset;

        if (currTime > availStT + periodStT)
        {
            offset = currTime - availStT - periodStT;
            return offset;
        }

        dash_log(DASH_LOG_INFO, "[%s,%d] currTime:%u, availStT:%u, periodStT:%u, offset:%u\n", __FUNCTION__, __LINE__, currTime, availStT, periodStT, offset);
    }

    return 0;
}

int         ManualAdaptation::SetSAPs      (dash::mpd::IRepresentation *representation, std::vector<uint64_t> &saps)
{
    if (representation != NULL && saps.size() > 0)
    {
        libdash::framework::mpd::IRepresentationStream *stream = adaptationSetStream->GetRepresentationStream(representation);
        libdash::framework::mpd::SingleMediaSegmentStream *single;
        if (stream != NULL && stream->GetStreamType() == libdash::framework::mpd::SingleMediaSegment)
        {
            single = (libdash::framework::mpd::SingleMediaSegmentStream *)stream;
            return single->SetSAPs(saps);
        }
    }

    return -1;
}

