/*
 * SegmentList.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "SegmentList.h"
#include <stdio.h>

using namespace dash::mpd;

SegmentList::SegmentList    () :
                xlinkHref(""),
                xlinkActuate("onRequest")
{
}
SegmentList::~SegmentList   ()
{
    for (size_t i = 0; i < segmentURLs.size(); i++)
        delete(this->segmentURLs.at(i));
}

const std::vector<ISegmentURL*>& SegmentList::GetSegmentURLs    ()  const
{
    return (std::vector<ISegmentURL*> &) this->segmentURLs;
}
void                            SegmentList::AddSegmentURL      (SegmentURL *segmentURL)
{
    this->segmentURLs.push_back(segmentURL);
}
const std::string&              SegmentList::GetXlinkHref       ()  const
{
    return this->xlinkHref;
}
void                            SegmentList::SetXlinkHref       (const std::string& xlinkHref)
{
    this->xlinkHref = xlinkHref;
}
const std::string&              SegmentList::GetXlinkActuate    ()  const
{
    return this->xlinkActuate;
}
void                            SegmentList::SetXlinkActuate    (const std::string& xlinkActuate)
{
    this->xlinkActuate = xlinkActuate;
}

const std::string&  SegmentList::Getinitialization              ()  const
{
    return this->initialization;
}
void                SegmentList::SetInitialization              (const std::string& initialization)
{
    this->initialization = initialization;
}

ISegment*           SegmentList::ToInitializationSegment        (const std::vector<IBaseUrl *>& baseurls, const std::string& representationID, uint32_t bandwidth) const
{
    Segment *seg = new Segment();
    if (seg->Init(baseurls, this->initialization, "", dash::metrics::InitializationSegment))
        return seg;

    delete seg;
    return NULL;
}
