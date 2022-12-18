/*
 * SegmentTemplateStream.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LIBDASH_FRAMEWORK_MPD_SEGMENTTEMPLATESTREAM_H_
#define LIBDASH_FRAMEWORK_MPD_SEGMENTTEMPLATESTREAM_H_

#include "IMPD.h"
#include "AbstractRepresentationStream.h"
#include "ISegment.h"
#include "ISegmentTemplate.h"
#include "ISegmentTimeline.h"

namespace libdash
{
    namespace framework
    {
        namespace mpd
        {
            class SegmentTemplateStream: public AbstractRepresentationStream
            {
                public:
                    SegmentTemplateStream           (dash::mpd::IMPD *mpd, dash::mpd::IPeriod *period, dash::mpd::IAdaptationSet *adaptationSet, dash::mpd::IRepresentation *representation);
                    virtual ~SegmentTemplateStream  ();

                    virtual dash::mpd::ISegment*        GetInitializationSegment        ();
                    virtual dash::mpd::ISegment*        GetIndexSegment                 (size_t segmentNumber);
                    virtual dash::mpd::ISegment*        GetMediaSegment                 (size_t segmentNumber);
                    virtual dash::mpd::ISegment*        GetBitstreamSwitchingSegment    ();
                    virtual RepresentationStreamType    GetStreamType                   ();
                    virtual uint32_t                    GetSize                         ();

                    virtual uint32_t                    GetAverageSegmentDuration       ();
                    virtual uint64_t                    GetSegmentEndTime  (uint32_t position);
                    virtual uint64_t                    GetSegmentStartTime  (uint32_t position);
                    virtual uint32_t                    GetPositionFromTime  (int64_t ms, int direct);
                    virtual int                           SetSAPs  (std::vector<uint64_t> &saps);

                private:
                    dash::mpd::ISegmentTemplate*        FindSegmentTemplate             ();
                    void                                CalculateSegmentStartTimes      ();
                    const dash::mpd::ISegmentTimeline *GetSegmentTimeline   ();

                    dash::mpd::ISegmentTemplate *segmentTemplate;
                    std::vector<uint32_t>       segmentStartTimes;
                    std::vector<uint8_t>         segmentDurations;
                    uint32_t timelineTimeScale;
            };
        }
    }
}

#endif /* LIBDASH_FRAMEWORK_MPD_SEGMENTTEMPLATESTREAM_H_ */
