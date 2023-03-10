/*
 * SingleMediaSegmentStream.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LIBDASH_FRAMEWORK_MPD_SINGLEMEDIASEGMENTSTREAM_H_
#define LIBDASH_FRAMEWORK_MPD_SINGLEMEDIASEGMENTSTREAM_H_

#include "IMPD.h"
#include "AbstractRepresentationStream.h"
#include "ISegment.h"

namespace libdash
{
    namespace framework
    {
        namespace mpd
        {
            class SingleMediaSegmentStream: public AbstractRepresentationStream
            {
                public:
                    SingleMediaSegmentStream           (dash::mpd::IMPD *mpd, dash::mpd::IPeriod *period, dash::mpd::IAdaptationSet *adaptationSet, dash::mpd::IRepresentation *representation);
                    virtual ~SingleMediaSegmentStream  ();

                    virtual dash::mpd::ISegment*        GetInitializationSegment        ();
                    virtual dash::mpd::ISegment*        GetIndexSegment                 (size_t segmentNumber);
                    virtual dash::mpd::ISegment*        GetMediaSegment                 (size_t segmentNumber);
                    virtual dash::mpd::ISegment*        GetBitstreamSwitchingSegment    ();
                    virtual RepresentationStreamType    GetStreamType                   ();

                    virtual uint32_t                    GetFirstSegmentNumber           ();
                    virtual uint32_t                    GetCurrentSegmentNumber         ();
                    virtual uint32_t                    GetLastSegmentNumber            ();
                    virtual int                            SetSAPs            (std::vector<uint64_t> &saps);

                 private:
                    std::vector<uint64_t>           saps;
                    bool                            useSaps; //use saps to create media segment
                    std::string                     mediaSegmentByteRange;//if the Initialization && media data are in the same single segment, use this range to avoid  repeat downloading the Initialization data

                    dash::mpd::ISegment*         _GetInitializationSegment        ();
                    dash::mpd::ISegment*         _GetPrivateInitializationSegment        ();
            };
        }
    }
}

#endif /* LIBDASH_FRAMEWORK_MPD_SINGLEMEDIASEGMENTSTREAM_H_ */