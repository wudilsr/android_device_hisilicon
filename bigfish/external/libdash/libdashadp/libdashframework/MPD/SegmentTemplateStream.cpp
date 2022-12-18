/*
 * SegmentTemplateStream.cpp
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "SegmentTemplateStream.h"

using namespace dash::mpd;
using namespace libdash::framework::mpd;

SegmentTemplateStream::SegmentTemplateStream            (IMPD *mpd, IPeriod *period, IAdaptationSet *adaptationSet, IRepresentation *representation) :
                       AbstractRepresentationStream     (mpd, period, adaptationSet, representation)
{
    this->baseUrls          = BaseUrlResolver::ResolveBaseUrl(mpd, period, adaptationSet, 0, 0, 0);
    this->timelineTimeScale = 0;
    if (this->representation->GetBaseURLs().size() > 0)
    {
        this->baseUrls.push_back(this->representation->GetBaseURLs().at(0));
    }
    this->segmentTemplate   = FindSegmentTemplate();
    CalculateSegmentStartTimes();
}
SegmentTemplateStream::~SegmentTemplateStream           ()
{
}
ISegment*                   SegmentTemplateStream::GetInitializationSegment     ()
{
    ISegment *seg;
    ISegmentTemplate *segTemplate;
    std::vector<dash::mpd::IBaseUrl *> tempBaseUrls;

    if (this->segmentTemplate->GetInitialization())
        return this->segmentTemplate->GetInitialization()->ToSegment(baseUrls);

    seg = this->segmentTemplate->ToInitializationSegment(baseUrls, representation->GetId(), representation->GetBandwidth());
    if (seg != NULL)
        return  seg;

    segTemplate = this->adaptationSet->GetSegmentTemplate();
    if (segTemplate != NULL)
    {
        tempBaseUrls = BaseUrlResolver::ResolveBaseUrl(mpd, period, adaptationSet, 0, 0, 0);
        seg = segTemplate->ToInitializationSegment(tempBaseUrls, representation->GetId(), representation->GetBandwidth());
        if (seg != NULL)
            return seg;
    }

    segTemplate = this->period->GetSegmentTemplate();
    if (segTemplate != NULL)
    {
        tempBaseUrls = BaseUrlResolver::ResolveBaseUrl(mpd, period, NULL, 0, 0, 0);
        seg = segTemplate->ToInitializationSegment(tempBaseUrls, representation->GetId(), representation->GetBandwidth());
        if (seg != NULL)
            return seg;
    }

    return NULL;
}

ISegment*                   SegmentTemplateStream::GetIndexSegment              (size_t segmentNumber)
{
    /* time-based template */
    if (GetSegmentTimeline())
    {
        if (this->segmentStartTimes.size() > segmentNumber)
            return this->segmentTemplate->GetIndexSegmentFromTime(baseUrls, representation->GetId(), representation->GetBandwidth(), this->segmentStartTimes.at(segmentNumber));

        return NULL;
    }

    /* number-based template */
    return this->segmentTemplate->GetIndexSegmentFromNumber(baseUrls, representation->GetId(), representation->GetBandwidth(),
                                                                this->segmentTemplate->GetStartNumber() + segmentNumber);
}
ISegment*                   SegmentTemplateStream::GetMediaSegment              (size_t segmentNumber)
{
    ISegment*   seg = NULL;
    /* time-based template */
    if (GetSegmentTimeline())
    {
        if (this->segmentStartTimes.size() > segmentNumber)
        {
            seg = this->segmentTemplate->GetMediaSegmentFromTime(baseUrls, representation->GetId(), representation->GetBandwidth(), this->segmentStartTimes.at(segmentNumber));
        }
        else
        {
            return NULL;
        }
    }

    if (seg == NULL)
    {
        /* number-based template */
        seg = this->segmentTemplate->GetMediaSegmentFromNumber(baseUrls, representation->GetId(), representation->GetBandwidth(),
                                                            this->segmentTemplate->GetStartNumber() + segmentNumber);
    }

    return seg;

}
ISegment*                   SegmentTemplateStream::GetBitstreamSwitchingSegment ()
{
    if (this->segmentTemplate->GetBitstreamSwitching())
        return this->segmentTemplate->GetBitstreamSwitching()->ToSegment(baseUrls);

    return this->segmentTemplate->ToBitstreamSwitchingSegment(baseUrls, representation->GetId(), representation->GetBandwidth());
}
RepresentationStreamType    SegmentTemplateStream::GetStreamType                ()
{
    return SegmentList;
}
uint32_t                    SegmentTemplateStream::GetSize                      ()
{
    return this->segmentStartTimes.size() ? this->segmentStartTimes.size() : UINT32_MAX - 1;
}
uint32_t                    SegmentTemplateStream::GetAverageSegmentDuration    ()
{
    uint32_t segDuration = this->segmentTemplate->GetDuration();
    uint32_t timeScale = this->segmentTemplate->GetTimescale();

    /* TODO calculate average segment durations for SegmentTimeline */
    if (timeScale > 0)
    {
        segDuration = this->segmentTemplate->GetDuration() * 1000ULL/timeScale;
    }
  //  dash_log(DASH_LOG_INFO, "[%s,%d] segDuration=%u, timeScale=%u\n",
 //       __FUNCTION__, __LINE__, segDuration, timeScale);

    return segDuration;
}

uint64_t   SegmentTemplateStream::GetSegmentEndTime  (uint32_t position)
{
    uint64_t segEndTime = 0;

     if (this->segmentStartTimes.size() > position)
     {
        if (this->segmentDurations.at(position) > 0)
        {
            segEndTime = (this->segmentStartTimes.at(position) + this->segmentDurations.at(position));
        }
        else if (this->segmentStartTimes.size() > position + 1)
        {
            segEndTime = this->segmentStartTimes.at(position + 1);
        }
        else//may be the last segment
        {
            segEndTime = this->segmentStartTimes.at(position) + 3 * this->timelineTimeScale;//""
            dash_log(DASH_LOG_WARNING, "[%s,%d] warning, maybe the last segment %u, end time is estimated.\n", __FUNCTION__, __LINE__, position);
        }
     }
     else
     {
        dash_log(DASH_LOG_ERROR, "[%s,%d] error, position  invalid:%u\n", __FUNCTION__, __LINE__, position);
        return segEndTime;
     }

    if (this->timelineTimeScale > 0)
    {
        segEndTime = segEndTime * 1000ULL/this->timelineTimeScale;
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] error, segmenttemplate timescale invalid:%u\n",
            __FUNCTION__, __LINE__, this->timelineTimeScale);
        segEndTime = 0;
    }

  //  dash_log("[%s,%d] segment %u end time:%llu\n", __FUNCTION__, __LINE__, position, segEndTime);

     return segEndTime;
}

uint64_t   SegmentTemplateStream::GetSegmentStartTime  (uint32_t position)
{
    uint64_t segStartTime = 0;

    if (position == 0)
        return 0;

    if (this->segmentStartTimes.size() > position)
    {
         segStartTime = this->segmentStartTimes.at(position);
    }
    else
    {
       dash_log(DASH_LOG_ERROR, "[%s,%d] error, position  invalid:%u\n", __FUNCTION__, __LINE__, position);
       return segStartTime;
    }

    if (this->timelineTimeScale > 0)
    {
        segStartTime = segStartTime * 1000ULL/this->timelineTimeScale;
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] error, segmenttemplate timescale invalid:%u\n",
            __FUNCTION__, __LINE__, this->timelineTimeScale);
        segStartTime = 0;
    }

  //  dash_log("[%s,%d] segment %u end time:%llu\n", __FUNCTION__, __LINE__, position, segEndTime);

     return segStartTime;
}

uint32_t   SegmentTemplateStream::GetPositionFromTime  (int64_t ms, int direct)
{
    uint32_t position = 0;
    uint64_t startTimeMs;

    if (ms < 0)
        return 0;

    if (this->timelineTimeScale == 0)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] error, segmenttemplate timescale invalid:%u\n",
            __FUNCTION__, __LINE__, this->timelineTimeScale);
        return 0;
    }

    if (direct > 0)
    {
        for (position = 0; position < this->segmentStartTimes.size(); position ++)
        {
            startTimeMs = (uint64_t)(this->segmentStartTimes.at(position)) *1000ULL/this->timelineTimeScale;
            if (startTimeMs >= ms)
                return position;
        }
    }
    else
    {
        for (position = 0; position < this->segmentStartTimes.size(); position ++)
        {
            startTimeMs = (uint64_t)(this->segmentStartTimes.at(position)) *1000ULL/this->timelineTimeScale;
            if (startTimeMs >= ms)
            {
                if (position >= 1)
                    return (position - 1);
                else
                    return 0;
            }
        }
    }

    if (position > 0)
        position --;

    return position;
}

ISegmentTemplate*           SegmentTemplateStream::FindSegmentTemplate          ()
{
    if (this->representation->GetSegmentTemplate() &&
        this->representation->GetSegmentTemplate()->Getmedia().length() > 0)
        return this->representation->GetSegmentTemplate();

    if (this->adaptationSet->GetSegmentTemplate() &&
        this->adaptationSet->GetSegmentTemplate()->Getmedia().length() > 0)
        return this->adaptationSet->GetSegmentTemplate();

    if (this->period->GetSegmentTemplate() &&
        this->period->GetSegmentTemplate()->Getmedia().length() > 0)
        return this->period->GetSegmentTemplate();

    dash_log(DASH_LOG_ERROR, "[%s,%d] error, SegmentTemplate not found.\n", __FUNCTION__, __LINE__);

    return NULL;
}

void                        SegmentTemplateStream::CalculateSegmentStartTimes   ()
{
    if (!GetSegmentTimeline())
        return;

    size_t   numOfTimelines = 0;
    uint32_t segStartTime   = 0;
    uint32_t segDuration    = 0;
    size_t   repeatCount    = 0;
    uint32_t startTimeOffset = 0;

    numOfTimelines      = GetSegmentTimeline()->GetTimelines().size();

    for (size_t i = 0; i < numOfTimelines; i++)
    {
        repeatCount     = GetSegmentTimeline()->GetTimelines().at(i)->GetRepeatCount();
        segStartTime    = GetSegmentTimeline()->GetTimelines().at(i)->GetStartTime();
        segDuration     = GetSegmentTimeline()->GetTimelines().at(i)->GetDuration();

        if (repeatCount > 0)
        {
            for (size_t j = 0; j <= repeatCount; j++)
            {
                if (segStartTime != 0xffffffff)
                {
                    this->segmentStartTimes.push_back(segStartTime + segDuration * j);
                    this->segmentDurations.push_back(segDuration);

                    startTimeOffset = segStartTime;
                }
                else
                {
                    /* TODO: implement if SegmentTemplate.SegmentTimeline.S@t is not specified */
                    this->segmentStartTimes.push_back(startTimeOffset);
                    this->segmentDurations.push_back(segDuration);
                }

                startTimeOffset += segDuration;
            }
        }
        else
        {
            if (segStartTime != 0xffffffff)
            {
                this->segmentStartTimes.push_back(segStartTime);
                this->segmentDurations.push_back(segDuration);

                startTimeOffset = segStartTime;
            }
            else
            {
                this->segmentStartTimes.push_back(startTimeOffset);
                this->segmentDurations.push_back(segDuration);
            }

            startTimeOffset += segDuration;
        }
    }
}

const ISegmentTimeline *SegmentTemplateStream::GetSegmentTimeline   ()
{
    const ISegmentTimeline *segmentTimeline;
    ISegmentTemplate *segmentTemplate = this->representation->GetSegmentTemplate();

    /*get from representation*/
    if (segmentTemplate)
    {
        segmentTimeline = segmentTemplate->GetSegmentTimeline();
        if (segmentTimeline)
        {
            this->timelineTimeScale = segmentTemplate->GetTimescale();
            return segmentTimeline;
        }
    }

    /*get from AdaptionSet*/
    segmentTemplate = this->adaptationSet->GetSegmentTemplate();
    if (segmentTemplate)
    {
        segmentTimeline = segmentTemplate->GetSegmentTimeline();
        if (segmentTimeline)
        {
            this->timelineTimeScale = segmentTemplate->GetTimescale();
            return segmentTimeline;
        }
    }

   /*get from Period*/
    segmentTemplate = this->period->GetSegmentTemplate();
    if (segmentTemplate)
    {
        segmentTimeline = segmentTemplate->GetSegmentTimeline();
        if (segmentTimeline)
        {
            this->timelineTimeScale = segmentTemplate->GetTimescale();
            return segmentTimeline;
        }
    }

    return NULL;
}

int          SegmentTemplateStream::SetSAPs  (std::vector<uint64_t> &saps)
{
    return 0;
}
