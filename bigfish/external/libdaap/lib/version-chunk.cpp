/*
 *  $Id: version-chunk.cpp,v 1.9 2003/05/29 14:24:04 bootc Exp $
 *  libdaap: version-chunk.cpp
 *
 *  Created by Chris Boot on Mon May 05 2003.
 *  Copyright (C) 2003 Chris Boot
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <libdaap/version-chunk.h>
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>

namespace DAAP {

// Max size: (5 + 1 + 3 + 1 + 3 + NUL) = 14
#define VERS_MAX_SIZE 14

VersionChunk::VersionChunk(
    const char *           inName,
    const VersionInfo &    inValue,
    const ContentCodes *   inContentCodes)
    : Chunk(inName, inContentCodes)
{
    mInfo = inValue;

    // Initialize the buffer
    mVersion = new char[VERS_MAX_SIZE];

    // Format the version string
    snprintf(mVersion, VERS_MAX_SIZE, "%d.%d.%d", mInfo.major,
        mInfo.minor, mInfo.micro);
}

VersionChunk::VersionChunk(
    ChunkType              inType,
    uint32_t               inLength,
    const void *           inData,
    const ContentCodes *   inContentCodes)
    : Chunk(inType, inContentCodes)
{
    // Check that the length matches
    if (inLength != sizeof(VersionInfo))
    {
//        throw "version length incorrect";
        fprintf(stderr, "version length incorrect");
        exit(1);
    }

    // Copy over the info
    memcpy(&mInfo, inData, sizeof(VersionInfo));
    mInfo.major = UINT16_SWAB(mInfo.major);

    // Initialize the buffer
    mVersion = new char[VERS_MAX_SIZE];

    // Format the version string
    snprintf(mVersion, VERS_MAX_SIZE, "%d.%d.%d", mInfo.major,
        mInfo.minor, mInfo.micro);
}

VersionChunk::~VersionChunk()
{
    // Clean up
    delete mVersion;
    mVersion = NULL;
}

VersionInfo
VersionChunk::GetValue() const
{
    return mInfo;
}

const char *
VersionChunk::GetVersion() const
{
    return mVersion;
}

uint32_t
VersionChunk::GetLength() const
{
    return sizeof(VersionInfo);
}

uint32_t
VersionChunk::GetData(
    uint32_t   inLength,
    void *     outBuffer) const
{
    if (inLength > 4)
        inLength = 4;

    VersionInfo theInfo = mInfo;
    theInfo.major = UINT16_SWAB(theInfo.major);

    memcpy(outBuffer, &theInfo, inLength);

    return inLength;
}

void
VersionChunk::Display(
    std::ostream &   inStream,
    int              inLevel) const
{
    Chunk::Display(inStream, inLevel);
    inStream << GetVersion();
}

const char*
VersionChunk::GetStringValue(
        const char* key) const
{
    return NULL;
}

} /* namespace DAAP */
