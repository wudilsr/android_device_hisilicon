/*
 * SingleMediaSegmentStream.cpp
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "SingleMediaSegmentStream.h"
#include <stdio.h>

using namespace dash::mpd;
using namespace libdash::framework::mpd;

SingleMediaSegmentStream::SingleMediaSegmentStream      (IMPD *mpd, IPeriod *period, IAdaptationSet *adaptationSet, IRepresentation *representation) :
                          AbstractRepresentationStream  (mpd, period, adaptationSet, representation)
{
    this->baseUrls = BaseUrlResolver::ResolveBaseUrl(mpd, period, adaptationSet, 0, 0, 0);
}
SingleMediaSegmentStream::~SingleMediaSegmentStream     ()
{
    this->saps.clear();
}
ISegment*                   SingleMediaSegmentStream::GetInitializationSegment      ()
{
    if (this->representation->GetSegmentBase())
    {
        /* TODO: check whether @sourceURL and/or @range is available in SegmentBase.Initialization, see Table 13 */

        if (this->representation->GetSegmentBase()->GetInitialization())
        {
            /* Check whether Initialization is valid */
            if (this->representation->GetSegmentBase()->GetInitialization()->GetSourceURL() != "")
                return this->representation->GetSegmentBase()->GetInitialization()->ToSegment(baseUrls);
        }
    }

    return NULL;
  //  return GetMediaSegment(0);
}
ISegment*                   SingleMediaSegmentStream::GetIndexSegment               (size_t segmentNumber)
{
    /* segmentNumber is not used in this case */
    if (this->representation->GetSegmentBase())
    {
        if (this->representation->GetSegmentBase()->GetRepresentationIndex())
            return this->representation->GetSegmentBase()->GetRepresentationIndex()->ToSegment(baseUrls);
    }

    return NULL;
}
ISegment*                   SingleMediaSegmentStream::GetMediaSegment               (size_t segmentNumber)
{
    ISegment * seg = NULL;

    if (this->saps.size() <= 0 || this->representation->GetBaseURLs().size() > 1)
    {
        /* segmentNumber equals the desired BaseUrl */
        if (this->representation->GetBaseURLs().size() > segmentNumber)
            return this->representation->GetBaseURLs().at(segmentNumber)->ToMediaSegment(baseUrls);
    }
    /*now sap download only support the case of exactly 1 base url*/
    else if (this->representation->GetBaseURLs().size() == 1 &&
               this->saps.size() > segmentNumber)
    {
      //  dash_log("[SEGNUM] segmentNumber:%u, this->saps.size():%u\n", segmentNumber, this->saps.size());
        seg = this->representation->GetBaseURLs().at(0)->ToMediaSegment(baseUrls);
        if (seg != NULL)
        {
            std::stringstream ss;
            std::stringstream es;
            std::string range;
            std::string endRange;

            ss <<  this->saps.at(segmentNumber);
            ss >> range;
            range.append("-");
            seg->StartByte(this->saps.at(segmentNumber));
            if (this->saps.size() > segmentNumber + 1)
            {
                es <<  (this->saps.at(segmentNumber + 1) - 1);
                es >> endRange;
                range.append(endRange);
                seg->EndByte(this->saps.at(segmentNumber + 1) - 1);
            }
            seg->HasByteRange(true);
            seg->Range(range);
            return seg;
        }
    }

    return NULL;
   // return this->representation->GetBaseURLs().at(0)->ToMediaSegment(baseUrls);
}
ISegment*                   SingleMediaSegmentStream::GetBitstreamSwitchingSegment  ()
{
    /* not possible */
    return NULL;
}
RepresentationStreamType    SingleMediaSegmentStream::GetStreamType                 ()
{
    return SingleMediaSegment;
}
uint32_t                    SingleMediaSegmentStream::GetFirstSegmentNumber           ()
{
    return 0;
}
uint32_t                    SingleMediaSegmentStream::GetCurrentSegmentNumber         ()
{
    return 0;
}
uint32_t                    SingleMediaSegmentStream::GetLastSegmentNumber            ()
{
    return 0;
}
int                          SingleMediaSegmentStream::SetSAPs            (std::vector<uint64_t> &saps)
{
    this->saps = saps;
    dash_log(DASH_LOG_INFO, "[%s,%d] set SingleMediaSegmentStream SAPs OK, size %u\n", __FUNCTION__, __LINE__, this->saps.size());

    return 0;
}

