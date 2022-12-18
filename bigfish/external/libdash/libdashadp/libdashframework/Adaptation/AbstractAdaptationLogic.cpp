/*
 * AbstractAdaptationLogic.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "AbstractAdaptationLogic.h"

using namespace libdash::framework::adaptation;
using namespace dash::mpd;

AbstractAdaptationLogic::AbstractAdaptationLogic        (dash::mpd::IPeriod *period, dash::mpd::IAdaptationSet *adaptationSet, dash::mpd::IMPD *mpd, uint32_t bufSize) :
                         segmentOffset                  (0),
                         positionOffset                 (0),
                         bufferSize                     (bufSize)
{
}
AbstractAdaptationLogic::~AbstractAdaptationLogic       ()
{
}
uint32_t    AbstractAdaptationLogic::GetPosition        ()
{
    return 0;
}
void        AbstractAdaptationLogic::SetPosition         (uint32_t segmentNumber)
{
}
void        AbstractAdaptationLogic::SetRepresentation   (dash::mpd::IRepresentation *representation,  int index, bool invokeInigSeg)
{
}

int         AbstractAdaptationLogic::GetCurrentRepresentationIndex   ()
{
       return 0;
}

void*      AbstractAdaptationLogic::Pause()
{
    return NULL;
}

bool       AbstractAdaptationLogic::Resume(void *breakpoints)
{
    return true;
}

int         AbstractAdaptationLogic::SetSAPs(dash::mpd::IRepresentation *representation, std::vector<uint64_t> &saps)
{
    return 0;
}
