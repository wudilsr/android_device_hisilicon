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
                          AbstractRepresentationStream  (mpd, period, adaptationSet, representation),useSaps(false), mediaSegmentByteRange("")
{
    std::string initializationRange;
    size_t hyphenPos, startByte;
    std::stringstream ss;
    ISegment *initSeg = NULL;
    std::string initSegUrl;
    bool separateInitSeg = false;
    int i;

    this->baseUrls = BaseUrlResolver::ResolveBaseUrl(mpd, period, adaptationSet, 0, 0, 0);

    initSeg = _GetInitializationSegment();
    //if there is not separate initialization segment, we must use byte range to avoid downloading
    //initialization segment repeatedly in GetInitializationSegment() and GetMediaSegment()
    if (initSeg != NULL)
    {
        if (initSeg->AbsoluteURI() != "")
        {
            initSegUrl =  initSeg->AbsoluteURI();
            //find media segment urls in init segment url
            for (i = 0; i < this->representation->GetBaseURLs().size(); i ++)
            {
                if (this->representation->GetBaseURLs().at(i)->GetUrl() != "" &&
                    std::string::npos != initSegUrl.find(this->representation->GetBaseURLs().at(i)->GetUrl()))
                {
                    separateInitSeg = false;
                    break;
                }
            }
            if (i == this->representation->GetBaseURLs().size() &&
                this->representation->GetBaseURLs().size() > 0)
            {
                separateInitSeg = true;
            }
        }
        dash_log(DASH_LOG_INFO, "[%s,%d][%p] init segment='%s', separateInitSeg=%d\n",
            __FUNCTION__, __LINE__, this, initSeg->AbsoluteURI().c_str(), (separateInitSeg?1:0));
        if (!separateInitSeg &&
            this->representation->GetSegmentBase() &&
            this->representation->GetSegmentBase()->GetInitialization())
        {
            initializationRange = this->representation->GetSegmentBase()->GetInitialization()->GetRange();
            hyphenPos = initializationRange.find('-');
            if (hyphenPos != std::string::npos && hyphenPos < initializationRange.size() - 1)
            {
                startByte = strtoul(initializationRange.substr(hyphenPos + 1, std::string::npos).c_str(), NULL, 10) + 1;
                ss << startByte;
                ss >> this->mediaSegmentByteRange;
                this->mediaSegmentByteRange.append("-");
                dash_log(DASH_LOG_INFO, "[%s,%d][%p] initializationRange=%s,  mediaSegmentByteRange=%s\n",
                    __FUNCTION__, __LINE__, this, initializationRange.c_str(), this->mediaSegmentByteRange.c_str());
            }
        }

        delete initSeg;
    }

}
SingleMediaSegmentStream::~SingleMediaSegmentStream     ()
{
    this->saps.clear();
}

ISegment*                   SingleMediaSegmentStream::_GetInitializationSegment      ()
{
    if (this->representation->GetSegmentBase())
    {
        /* TODO: check whether @sourceURL and/or @range is available in SegmentBase.Initialization, see Table 13 */
        if (this->representation->GetSegmentBase()->GetInitialization())
        {
            if (this->representation->GetSegmentBase()->GetInitialization()->GetSourceURL() == "" &&
                !this->representation->GetBaseURLs().empty() &&
                this->representation->GetBaseURLs().at(0)->GetUrl() !=  "")
            {
                dash_log(DASH_LOG_WARNING, "[%s,%d][%p] InitializationSegment sourceURL is null, use base url='%s'  instead!\n",
                    __FUNCTION__, __LINE__, this, representation->GetBaseURLs().at(0)->GetUrl().c_str());
                return this->representation->GetSegmentBase()->GetInitialization()->ToSegment(baseUrls, representation->GetBaseURLs().at(0)->GetUrl());
            }

            /* Check whether Initialization is valid */
            if (this->representation->GetSegmentBase()->GetInitialization()->GetSourceURL() != "")
            {
                return this->representation->GetSegmentBase()->GetInitialization()->ToSegment(baseUrls);
            }
        }

    }

    return NULL;
}

ISegment*                   SingleMediaSegmentStream::_GetPrivateInitializationSegment      ()
{
    if (this->useSaps && this->saps[0] != 0)
    {
        ISegment * seg = NULL;

        seg = this->representation->GetBaseURLs().at(0)->ToMediaSegment(baseUrls);
        if (seg != NULL)
        {
            std::stringstream ss;
            std::stringstream es;
            std::string range;
            std::string endRange;

            ss <<  0;
            ss >> range;
            range.append("-");
            seg->StartByte(0);
            es <<  (this->saps.at(0) - 1);
            es >> endRange;
            range.append(endRange);
            seg->EndByte(this->saps.at(0) - 1);

            seg->HasByteRange(true);
            seg->Range(range);
            dash_log(DASH_LOG_WARNING, "[%s,%d][%p] return private Initialization segment with range '%s'\n", __FUNCTION__, __LINE__, this, range.c_str());

            return seg;
        }
    }

    return NULL;
}

ISegment*                   SingleMediaSegmentStream::GetInitializationSegment      ()
{
    ISegment *initSeg;

    initSeg = _GetInitializationSegment();
    // if no Initialization segment try to alloc a private Initialization segment start from 0 byte.
    if (initSeg != NULL)
    {
        return initSeg;
    }
    {
        return _GetPrivateInitializationSegment();
    }
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

    if (!this->useSaps)
    {
        /* segmentNumber equals the desired BaseUrl */
        if (this->representation->GetBaseURLs().size() > segmentNumber)
        {
            if (this->mediaSegmentByteRange != "" && segmentNumber == 0)
            {
                dash_log(DASH_LOG_WARNING, "[%s,%d][%p] apply byte range  '%s' to first media segment\n",
                    __FUNCTION__, __LINE__,  this, this->mediaSegmentByteRange.c_str());
                return this->representation->GetBaseURLs().at(segmentNumber)->ToMediaSegment(baseUrls, this->mediaSegmentByteRange);
            }
            return this->representation->GetBaseURLs().at(segmentNumber)->ToMediaSegment(baseUrls);
        }
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

    if (this->saps.size() > 0 && this->representation->GetBaseURLs().size() == 1)
    {
        this->useSaps = true;
    }

    dash_log(DASH_LOG_INFO, "[%s,%d][%p] set SingleMediaSegmentStream SAPs OK, size %u, useSaps=%d\n",
        __FUNCTION__, __LINE__, this, this->saps.size(), (this->useSaps?1:0));

    return 0;
}

