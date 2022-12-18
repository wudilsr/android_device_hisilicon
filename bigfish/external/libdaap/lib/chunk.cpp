/*
 *  $Id: chunk.cpp,v 1.10 2003/05/18 02:07:50 wcc2987 Exp $
 *  libdaap: chunk.cpp
 *
 *  Created by Chris Boot on Sun May 04 2003.
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

#include <libdaap/chunk.h>
#include "macros.h"
#include "libdaap/libdaap.h"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

namespace DAAP {

#pragma mark *** STATIC METHODS ***

Chunk *
Chunk::ReadChunk(
    const void *           inData,
    uint32_t               inDataLength,
    bool                   inTopLevel,
    const ContentCodes *   inContentCodes)
{
    ChunkType theType;
    uint32_t theLength;
    uint8_t *theData = (uint8_t *)inData;

    // Check that there is enough data to actually have chunk
    if (inDataLength < 8)
    {
//        throw "data length must be at least 8";
        fprintf(stderr, "data length must be at least 8");
        exit(1);
    }

    // Read the chunk type from the first 4 bytes
    memcpy(&theType, theData, sizeof(ChunkType));

    // If we're the top level chunk, we ignore our built-in length
    if (inTopLevel)
    {
        // Calculate the chunk length from the full data length
        theLength = inDataLength - 8;
    }
    else
    {
        // Read the length from the data
        memcpy(&theLength, theData + 4, sizeof(uint32_t));
        theLength = UINT32_SWAB(theLength);

        // Not enough data
        if (theLength > inDataLength)
        {
//            throw "not enough data";
            fprintf(stderr, "not enough data");
            exit(1);
        }
    }

    // Get the default codes if we need to
    if (inContentCodes == NULL)
        inContentCodes = ContentCodes::DefaultContentCodes();

    // Create the chunk
    Chunk *theChunk = inContentCodes->CreateChunk(
        theType, theLength, theData + 8);

    return theChunk;
}

#pragma mark -
#pragma mark *** CONSTRUCTORS / DESTRUCTOR ***

Chunk::Chunk(
    ChunkType              inType,
    const ContentCodes *   inContentCodes)
{
    mType = inType;
    mContentCodes = inContentCodes;
}

Chunk::Chunk(
    const char *           inName,
    const ContentCodes *   inContentCodes)
{
    if (inContentCodes == NULL)
        inContentCodes = ContentCodes::DefaultContentCodes();

    mType = inContentCodes->GetChunkType(inName);
    mContentCodes = inContentCodes;
}

Chunk::~Chunk()
{

}

#pragma mark -
#pragma mark *** PUBLIC METHODS ***

ChunkType
Chunk::GetType() const
{
    return mType;
}

const char *
Chunk::GetName() const
{
    // Return our name
    return mContentCodes->GetChunkName(mType);
}

void
Chunk::Display(
    std::ostream &   inStream,
    int              inLevel) const
{
    inStream << GetName() << " = ";
}

const char*
Chunk::GetStringValue(
        const char* key) const
{
    return NULL;
}

uint32_t
Chunk::BuildData(
    uint32_t   inLength,
    void *     outBuffer) const
{
    uint8_t *theBuffer = (uint8_t *)outBuffer;

    // If the buffer was NULL, return the ideal length of the chunk
    if (!outBuffer)
        return GetLength() + 8;

    // If there's not enough space for the code, return
    if (inLength < 4)
        return 0;

    // Copy over the chunk type
    uint32_t theType = GetType();
    memcpy(theBuffer, &theType, 4);

    // If there's not enough space for the length, return
    if (inLength < 8)
        return 4;

    // Prepare the chunk length for transmission
    uint32_t theLength = GetLength();
    theLength = UINT32_SWAB(theLength);
    memcpy(theBuffer + 4, &theLength, 4);

    // Copy over the child's data
    return GetData(inLength - 8, theBuffer + 8) + 8;
}

#pragma mark -
#pragma mark *** PROTECTED METHODS ***

const ContentCodes *
Chunk::GetContentCodes() const
{
    return mContentCodes;
}

#pragma mark -
#pragma mark *** OTHER STUFF ***

std::ostream &
operator << (
    std::ostream &   inStream,
    const Chunk &    inChunk)
{
    inChunk.Display(inStream);
    return inStream;
}

const char* Chunk::GetValueOf(Chunk *containerChunk, const char* key)
{
    ContainerChunk *container = dynamic_cast<ContainerChunk*>(containerChunk);
    if (container == NULL)
    {
        return NULL;
    }
    int numOfChildren = container->CountChildren();
    for (int i = 0; i < numOfChildren; i++)
    {
        const Chunk &tmpChunk = (*container)[i];
        const char* tmpName = tmpChunk.GetName();
        if (!strcmp(tmpName, key))
        {
            return tmpChunk.GetStringValue(tmpName);
        }
    }
    return NULL;
}

} /* namespace DAAP */
