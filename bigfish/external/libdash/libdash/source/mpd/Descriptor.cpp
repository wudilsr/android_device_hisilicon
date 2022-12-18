/* 
 * Descriptor.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "Descriptor.h"

using namespace dash::mpd;

Descriptor::Descriptor  () :
            schemeIdUri (""),
            value       (""),
            mspr        (NULL)
{
}
Descriptor::~Descriptor ()
{
     for(size_t i = 0; i < this->mspr.size(); i++)
        delete(this->mspr.at(i));
}
const std::string&  Descriptor::GetSchemeIdUri  ()  const
{
    return this->schemeIdUri;
}
void                Descriptor::SetSchemeIdUri  (const std::string& schemeIdUri) 
{
    this->schemeIdUri = schemeIdUri;
}
const std::string&  Descriptor::GetValue        ()  const
{
    return this->value;
}
void                Descriptor::SetValue        (const std::string& value) 
{
    this->value = value;
}

const std::vector<IMSPR *>& Descriptor::GetMSPR         ()  const
{
    return (std::vector<IMSPR*> &)this->mspr;
}

void                Descriptor::AddMSPR         (MSPR * mspr)
{
    this->mspr.push_back(mspr);
}
