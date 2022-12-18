/*
 * AbstractAdaptationLogic.h
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LIBDASH_FRAMEWORK_ADAPTATION_ABSTRACTADAPTATIONLOGIC_H_
#define LIBDASH_FRAMEWORK_ADAPTATION_ABSTRACTADAPTATIONLOGIC_H_

#include "MediaObject.h"
#include "IAdaptationLogic.h"

namespace libdash
{
    namespace framework
    {
        namespace adaptation
        {
            class AbstractAdaptationLogic : public IAdaptationLogic
            {
                public:
                    AbstractAdaptationLogic             (dash::mpd::IPeriod* period, dash::mpd::IAdaptationSet *adaptationSet, dash::mpd::IMPD *mpd, uint32_t bufferSize);
                    virtual ~AbstractAdaptationLogic    ();

                    virtual uint32_t        GetPosition         ();
                    virtual void            SetPosition         (uint32_t segmentNumber);
                    virtual void            SetRepresentation   (dash::mpd::IRepresentation *representation,  int index, bool invokeInigSeg);
                    virtual int                         SetSAPs      (dash::mpd::IRepresentation *representation, std::vector<uint64_t> &saps);
                    virtual int              GetCurrentRepresentationIndex   ();
                    virtual void*                  Pause();
                    virtual bool                    Resume(void *breakpoints);
                    virtual input::MediaObject*     GetSegment  (int type)  = 0;
                    virtual bool                       isLive()         =0;
                    virtual LogicType               GetType     ()  = 0;


                protected:
                    uint32_t    positionOffset;
                    uint32_t    segmentOffset;
                    uint32_t    bufferSize;
            };
        }
    }
}
#endif /* LIBDASH_FRAMEWORK_ADAPTATION_ABSTRACTADAPTATIONLOGIC_H_ */
