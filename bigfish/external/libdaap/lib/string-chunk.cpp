/*
 *  $Id: string-chunk.cpp,v 1.11 2003/05/29 14:24:04 bootc Exp $
 *  libdaap: string-chunk.cpp
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

#include <libdaap/string-chunk.h>
#include "macros.h"
#include <cstring>
#include <cstdlib>

namespace DAAP {

StringChunk::StringChunk(
    const char *           inName,
    const char *           inValue,
    uint32_t               inLength,
    const ContentCodes *   inContentCodes)
    : Chunk(inName, inContentCodes)
{
    if (inLength == 0)
        inLength = strlen(inValue);

    mLength = inLength;

    mValue = new char[inLength + 1];
    memcpy(mValue, inValue, inLength);
    mValue[inLength] = 0;
}

StringChunk::StringChunk(
    ChunkType              inType,
    uint32_t               inLength,
    const void *           inData,
    const ContentCodes *   inContentCodes)
    : Chunk(inType, inContentCodes)
{
    mLength = inLength;

    mValue = new char[inLength + 1];
    memcpy(mValue, inData, inLength);
    mValue[inLength] = 0;
}

StringChunk::~StringChunk()
{
    // Clean up
    delete mValue;
    mValue = NULL;
}

const char *
StringChunk::GetValue() const
{
    return mValue;
}

void
StringChunk::SetValue(
    const char *   inValue,
    uint32_t       inLength)
{
    if (inLength == 0)
        inLength = strlen(inValue);

    mLength = inLength;

    if (mValue)
        delete mValue;

    mValue = new char[inLength + 1];

    memcpy(mValue, inValue, inLength);
    mValue[inLength] = 0;
}

uint32_t
StringChunk::GetLength() const
{
    return mLength;
}

uint32_t
StringChunk::GetData(
    uint32_t   inLength,
    void *     outBuffer) const
{
    if (inLength > mLength)
        inLength = mLength;

    memcpy(outBuffer, mValue, inLength);

    return inLength;
}

void
StringChunk::Display(
    std::ostream &   inStream,
    int              inLevel) const
{
    // Display the name and stuff
    Chunk::Display(inStream, inLevel);

    // Output the value between quotes
    inStream << "\"" << GetValue() << "\"";
}

const char*
StringChunk::GetStringValue(
        const char* key) const
{
    const char* value = GetValue();
    int len = strlen(value)+1;
    char *result = new char[len];
    memset(result, '\0', len);
    strncpy(result, value, len);
    return result;
}

} /* namespace DAAP */
