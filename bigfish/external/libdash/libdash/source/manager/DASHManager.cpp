/*
 * DASHManager.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "DASHManager.h"
#include <stdio.h>

using namespace dash;
using namespace dash::xml;
using namespace dash::mpd;
using namespace dash::network;
using namespace dash::helpers;

DASHManager::DASHManager            ()
{
}
DASHManager::~DASHManager           ()
{
}
IMPD*           DASHManager::Open           (char *path, int *err)
{
    DOMParser parser(path);

    uint32_t fetchTime = Time::GetCurrentUTCTimeInSec();

    if (!parser.Parse(err))
        return NULL;

    MPD* mpd = parser.GetRootNode()->ToMPD();

    if (mpd)
        mpd->SetFetchTime(fetchTime);
    else
    *err = DashError_Unknown;

    return mpd;
}
