/*
 * AbstractSetHelper.cpp
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "AdaptationSetHelper.h"

using namespace libdash::framework::mpd;
using namespace dash::mpd;

std::vector<IAdaptationSet *>   AdaptationSetHelper::GetAudioAdaptationSets (dash::mpd::IPeriod *period)
{
    std::vector<IAdaptationSet *> audioAdaptationSets;
    std::vector<IAdaptationSet *> adaptationSets = period->GetAdaptationSets();

    for (size_t i = 0; i < adaptationSets.size(); i++)
        if (AdaptationSetHelper::IsAudioAdaptationSet(adaptationSets.at(i)))
            audioAdaptationSets.push_back(adaptationSets.at(i));

    return audioAdaptationSets;
}
std::vector<IAdaptationSet *>   AdaptationSetHelper::GetVideoAdaptationSets (dash::mpd::IPeriod *period)
{
    std::vector<IAdaptationSet *> videoAdaptationSets;
    std::vector<IAdaptationSet *> adaptationSets = period->GetAdaptationSets();

    for (size_t i = 0; i < adaptationSets.size(); i++)
        if (AdaptationSetHelper::IsVideoAdaptationSet(adaptationSets.at(i)))
            videoAdaptationSets.push_back(adaptationSets.at(i));

    return videoAdaptationSets;
}

std::vector<IAdaptationSet *>   AdaptationSetHelper::GetSubtitleAdaptationSets (dash::mpd::IPeriod *period)
{
    std::vector<IAdaptationSet *> subtitleAdaptationSets;
    std::vector<IAdaptationSet *> adaptationSets = period->GetAdaptationSets();

    for (size_t i = 0; i < adaptationSets.size(); i++)
        if (AdaptationSetHelper::IsSubTitleAdaptationSet(adaptationSets.at(i)))
            subtitleAdaptationSets.push_back(adaptationSets.at(i));

    return subtitleAdaptationSets;
}

bool                            AdaptationSetHelper::IsAudioAdaptationSet   (dash::mpd::IAdaptationSet *adaptationSet)
{
    bool isAudioAdaptationSet = false;

    if (adaptationSet->GetMimeType() != "")
        if (adaptationSet->GetMimeType().find("audio") != std::string::npos)
            return true;

    if (adaptationSet->GetContentType() != "")
        if (adaptationSet->GetContentType().find("audio") != std::string::npos)
            return true;

    std::vector<IContentComponent *> contentComponents = adaptationSet->GetContentComponent();
    for(size_t i = 0;i < contentComponents.size();i++)
    {
        IContentComponent * contentComponent = contentComponents.at(i);
        if (contentComponent->GetContentType() != "")
        {
            if (contentComponent->GetContentType().find("video") != std::string::npos)
                return false;

            if (contentComponent->GetContentType().find("audio") != std::string::npos)
                isAudioAdaptationSet = true;
        }
    }

    if (isAudioAdaptationSet)
        return true;

    return false;
}
bool                            AdaptationSetHelper::IsVideoAdaptationSet   (dash::mpd::IAdaptationSet *adaptationSet)
{
    if (adaptationSet->GetMimeType() != "")
        if (adaptationSet->GetMimeType().find("video") != std::string::npos)
            return true;

    if (adaptationSet->GetContentType() != "")
        if (adaptationSet->GetContentType().find("video") != std::string::npos)
            return true;

    std::vector<IContentComponent *> contentComponents = adaptationSet->GetContentComponent();
    for(size_t i = 0;i < contentComponents.size();i++)
    {
        IContentComponent * contentComponent = contentComponents.at(i);
        if (contentComponent->GetContentType() != "")
            if (contentComponent->GetContentType().find("video") != std::string::npos)
                return true;
    }
    return false;
}

bool                        AdaptationSetHelper::IsSubTitleAdaptationSet     (dash::mpd::IAdaptationSet *adaptationSet)
{
    if (adaptationSet->GetMimeType() != "")
           if (adaptationSet->GetMimeType().find("text") != std::string::npos)

    if (adaptationSet->GetContentType() != "")
        if (adaptationSet->GetContentType().find("text") != std::string::npos)
               return true;

    std::vector<IContentComponent *> contentComponents = adaptationSet->GetContentComponent();
    for(size_t i = 0;i < contentComponents.size();i++)
    {
        IContentComponent * contentComponent = contentComponents.at(i);
        if (contentComponent->GetContentType() != "")
            if (contentComponent->GetContentType().find("text") != std::string::npos)
                return true;
    }

    for (size_t i = 0; i < adaptationSet->GetRepresentation().size(); i++)
    {
       IRepresentation *subtitleRepresentation = adaptationSet->GetRepresentation().at(i);
       std::vector<std::string> codecs = subtitleRepresentation->GetCodecs();
       if (!codecs.empty())
       {
           if (codecs.at(0).find("tx3g") != std::string::npos || codecs.at(0).find("stpp") != std::string::npos)
           {
               return true;
           }
       }
    }

    if (adaptationSet->GetMimeType() != "")
        if (adaptationSet->GetMimeType().find("application/ttml+xml") != std::string::npos)
            return true;

    return false;
}
