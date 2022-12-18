/*
 * AbstractRepresentationStream.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "AbstractRepresentationStream.h"

using namespace libdash::framework::mpd;
using namespace dash::mpd;

AbstractRepresentationStream::AbstractRepresentationStream  (IMPD *mpd, IPeriod *period, IAdaptationSet *adaptationSet, IRepresentation *representation) :
                              mpd                           (mpd),
                              period                        (period),
                              adaptationSet                 (adaptationSet),
                              representation                (representation)
{
}
AbstractRepresentationStream::~AbstractRepresentationStream ()
{
}

void        AbstractRepresentationStream::SetBaseUrls               (const std::vector<dash::mpd::IBaseUrl *> baseurls)
{
    this->baseUrls.clear();

    for (size_t i = 0; i < baseurls.size(); i++)
        this->baseUrls.push_back(baseurls.at(i));
}
uint32_t    AbstractRepresentationStream::GetSize                   ()
{
    return UINT32_MAX - 1;
}
uint32_t    AbstractRepresentationStream::GetFirstSegmentNumber     ()
{
    if (this->mpd->GetType() == "dynamic")
    {
        uint32_t currTime   = TimeResolver::GetCurrentTimeInSec();
        uint32_t availStT   = TimeResolver::GetUTCDateTimeInSec(this->mpd->GetAvailabilityStarttime());
        uint32_t duration   = this->GetAverageSegmentDuration()/1000;
        uint32_t timeshift  = TimeResolver::GetDurationInSec(this->mpd->GetTimeShiftBufferDepth());

        dash_log(DASH_LOG_INFO, "[%s,%d] currTime:%u, availStT:%u, duration:%u, timeshift:%u\n", __FUNCTION__, __LINE__, currTime, availStT, duration, timeshift);
        dash_log(DASH_LOG_INFO, "[%s,%d] AvailabilityStarttime %s\n", __FUNCTION__, __LINE__, this->mpd->GetAvailabilityStarttime().c_str());
        if ((currTime > duration + availStT + timeshift) && duration != 0)
            return (currTime - duration - availStT - timeshift ) / duration;
    }

    return 0;
}
uint32_t    AbstractRepresentationStream::GetCurrentSegmentNumber   ()
{
    if (this->mpd->GetType() == "dynamic")
    {
        uint32_t currTime = TimeResolver::GetCurrentTimeInSec();
        uint32_t duration = this->GetAverageSegmentDuration()/1000;
        uint32_t availStT = TimeResolver::GetUTCDateTimeInSec(this->mpd->GetAvailabilityStarttime());

        if ((currTime > duration + availStT) && duration != 0)
            return (currTime - duration - availStT) / duration;
    }

    return 0;
}
uint32_t    AbstractRepresentationStream::GetLastSegmentNumber      ()
{
    if (this->mpd->GetType() == "dynamic")
    {
        uint32_t currTime   = TimeResolver::GetCurrentTimeInSec();
        uint32_t duration = this->GetAverageSegmentDuration()/1000;
        uint32_t availStT   = TimeResolver::GetUTCDateTimeInSec(this->mpd->GetAvailabilityStarttime());
        uint32_t checkTime  = mpd->GetFetchTime() +
                              TimeResolver::GetDurationInSec(this->mpd->GetMinimumUpdatePeriod());

        return ( ((checkTime > currTime) ? currTime : checkTime) - duration - availStT) / duration;
    }

    return 0;
}

uint32_t    AbstractRepresentationStream::GetAverageSegmentDuration ()
{
    return 1;
}

uint64_t   AbstractRepresentationStream::GetSegmentEndTime  (uint32_t position)
{
    return 0;
}

uint64_t   AbstractRepresentationStream::GetSegmentStartTime  (uint32_t position)
{
    return 0;
}

uint32_t  AbstractRepresentationStream::GetPositionFromTime  (int64_t ms, int direct)
{
    return 0;
}

