/*
 * ManualAdaptation.h
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LIBDASH_FRAMEWORK_ADAPTATION_MANUALADAPTATION_H_
#define LIBDASH_FRAMEWORK_ADAPTATION_MANUALADAPTATION_H_

#include "../MPD/RepresentationHelper.h"
#include "AbstractAdaptationLogic.h"
#include "../MPD/AdaptationSetStream.h"
#include "../../../libdash/source/helpers/String.h"

namespace libdash
{
    namespace framework
    {
        namespace adaptation
        {
            enum InvokeInitSegmentState
            {
                NO_INVOKE  = 0,
                PRE_INVOKE = 1,
                DO_INVOKE  = 2
            };

            class ManualAdaptation : public AbstractAdaptationLogic
            {
                public:
                    ManualAdaptation            (dash::mpd::IPeriod *period, dash::mpd::IAdaptationSet *adaptationSet, dash::mpd::IMPD *mpd, uint32_t bufferSize, void *breakpoint);
                    virtual ~ManualAdaptation   ();

                    virtual input::MediaObject*     GetSegment          (int type);
                    virtual uint32_t                GetPosition         ();
                    virtual void                    SetPosition         (uint32_t segmentNumber);
                    virtual void                    SetRepresentation   (dash::mpd::IRepresentation *representation,  int index, bool invokeInigSeg);
                    virtual int                      GetCurrentRepresentationIndex   () ;
                    virtual LogicType               GetType             ();
                    virtual void                    InvokeInitSegment   (bool invoke);
                    uint32_t                        GetSegmentDuration  ();
                    uint64_t                        GetSegmentEndTime(uint32_t position);
                    uint64_t                        GetSegmentStartTime(uint32_t position);
                    uint32_t                        GetPositionFromTime  (int64_t ms, int direct);
                    bool                              isLive();
                    int                                SetSAPs      (dash::mpd::IRepresentation *representation, std::vector<uint64_t> &saps);

                    dash::mpd::ISegment *           GetIndexSegment     ();
                    libdash::framework::mpd::RepresentationStreamType GetRepresentationStreamType();
                    std::string&                    GetSegmentURL       (dash::mpd::IRepresentation *representation, uint32_t position);
                    void *                           Pause();
                    bool                              Resume(void *breakpoint);
                private:
                    uint32_t                        CalculateSegmentOffset ();
                    uint32_t                        GetCurrentTimeOffset   ();

                    dash::mpd::IMPD                                 *mpd;
                    dash::mpd::IPeriod                              *period;
                    dash::mpd::IAdaptationSet                       *adaptationSet;
                    dash::mpd::IRepresentation                      *representation;
                    int                                                         representationIndex;
                    libdash::framework::mpd::AdaptationSetStream    *adaptationSetStream;
                    libdash::framework::mpd::IRepresentationStream  *representationStream;
                    uint32_t                                        segmentNumber;
                    int                                              invokeInitSegment;
                    int                                              state;
                    libdash::framework::mpd::RepresentationStreamType representationStreamType;
                    std::string                     segmentURL;

                    mutable CRITICAL_SECTION    monitorMutex;
            };
        }
    }
}

#endif /* LIBDASH_FRAMEWORK_ADAPTATION_MANUALADAPTATION_H_ */