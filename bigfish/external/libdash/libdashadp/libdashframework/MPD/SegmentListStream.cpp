/*
 * SegmentListStream.cpp
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "SegmentListStream.h"
#include <stdio.h>

using namespace dash::mpd;
using namespace libdash::framework::mpd;

SegmentListStream::SegmentListStream            (IMPD *mpd, IPeriod *period, IAdaptationSet *adaptationSet, IRepresentation *representation) :
                   AbstractRepresentationStream (mpd, period, adaptationSet, representation)
{
    this->baseUrls      = BaseUrlResolver::ResolveBaseUrl(mpd, period, adaptationSet, 0, 0, 0);
    this->segmentList   = FindSegmentList();
}
SegmentListStream::~SegmentListStream           ()
{
}
ISegment*                   SegmentListStream::GetInitializationSegment     ()
{
    if (this->segmentList->GetInitialization())
        return this->segmentList->GetInitialization()->ToSegment(this->baseUrls);

    return this->segmentList->ToInitializationSegment(baseUrls, representation->GetId(), representation->GetBandwidth());
}
ISegment*                   SegmentListStream::GetIndexSegment              (size_t segmentNumber)
{
    if (this->segmentList->GetSegmentURLs().size() > segmentNumber)
        return this->segmentList->GetSegmentURLs().at(segmentNumber)->ToIndexSegment(this->baseUrls);

    return NULL;
}
ISegment*                   SegmentListStream::GetMediaSegment              (size_t segmentNumber)
{
    if (this->segmentList->GetSegmentURLs().size() > segmentNumber)
    {
        if (this->segmentList->GetSegmentURLs().at(segmentNumber)->GetMediaURI() == "")
        {
            //Use Representation URL instead
            if (!representation->GetBaseURLs().empty())
            {
                if (representation->GetBaseURLs().at(0)->GetUrl() !=  "")
                    this->segmentList->GetSegmentURLs().at(segmentNumber)->SetMediaURI(representation->GetBaseURLs().at(0)->GetUrl());
            }
        }

        return this->segmentList->GetSegmentURLs().at(segmentNumber)->ToMediaSegment(this->baseUrls);
    }

    return NULL;
}
ISegment*                   SegmentListStream::GetBitstreamSwitchingSegment ()
{
    if (this->segmentList->GetBitstreamSwitching())
        return this->segmentList->GetBitstreamSwitching()->ToSegment(baseUrls);

    return NULL;
}
RepresentationStreamType    SegmentListStream::GetStreamType                ()
{
    return SegmentList;
}
uint32_t                    SegmentListStream::GetSize                      ()
{
    return this->segmentList->GetSegmentURLs().size();
}
ISegmentList*               SegmentListStream::FindSegmentList              ()
{
    if (this->representation->GetSegmentList())
        return this->representation->GetSegmentList();

    if (this->adaptationSet->GetSegmentList())
        return this->adaptationSet->GetSegmentList();

    if (this->period->GetSegmentList())
        return this->period->GetSegmentList();

    return NULL;
}
uint32_t                    SegmentListStream::GetAverageSegmentDuration    ()
{
    /* TODO calculate average segment durations for SegmentTimeline */
    return this->segmentList->GetDuration();
}

uint64_t   SegmentListStream::GetSegmentEndTime  (uint32_t position)
{
    return (GetAverageSegmentDuration() * ( 1 + position));
}

uint64_t   SegmentListStream::GetSegmentStartTime  (uint32_t position)
{
    return (GetAverageSegmentDuration() * (position));
}

uint32_t   SegmentListStream::GetPositionFromTime(int64_t ms, int direct)
{
    uint32_t  avgDuration = GetAverageSegmentDuration();

    if (ms < 0)
        return 0;

    if (avgDuration > 0)
    {
         if (direct > 0)
         {
            return ((ms + avgDuration - 1)/avgDuration);
         }
         else
         {
            return (ms /avgDuration);
         }
    }
    else
        return 0;
}

int          SegmentListStream::SetSAPs  (std::vector<uint64_t> &saps)
{
    return 0;
}
