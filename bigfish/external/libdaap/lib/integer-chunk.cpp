/*
 *  $Id: integer-chunk.cpp,v 1.8 2003/05/29 14:24:04 bootc Exp $
 *  libdaap: integer-chunk.cpp
 *
 *  Created by Chris Boot on Thu May 08 2003.
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

#include <libdaap/integer-chunk.h>
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>

namespace DAAP {

Integer8Chunk::Integer8Chunk(
    const char *           inName,
    uint8_t                inValue,
    const ContentCodes *   inContentCodes)
    : Chunk(inName, inContentCodes)
{
    mValue = inValue;
}

Integer8Chunk::Integer8Chunk(
    ChunkType              inType,
    uint32_t               inLength,
    const void *           inData,
    const ContentCodes *   inContentCodes)
    : Chunk(inType, inContentCodes)
{
    // Check size
    if (inLength != sizeof(uint8_t))
    {
//        throw "integer length incorrect";
        fprintf(stderr, "integer length incorrect");
        exit(1);
    }

    // Get the value
    memcpy(&mValue, inData, 1);
}

uint8_t
Integer8Chunk::GetValue() const
{
    return mValue;
}

void
Integer8Chunk::SetValue(uint8_t inValue)
{
    mValue = inValue;
}

uint32_t
Integer8Chunk::GetLength() const
{
    return sizeof(mValue);
}

uint32_t
Integer8Chunk::GetData(
    uint32_t   inLength,
    void *     outBuffer) const
{
    if (inLength > 1)
        inLength = 1;

    memcpy(outBuffer, &mValue, inLength);

    return inLength;
}

void
Integer8Chunk::Display(
    std::ostream &   inStream,
    int              inLevel) const
{
    Chunk::Display(inStream, inLevel);
    inStream << (long)mValue;
}

const char*
Integer8Chunk::GetStringValue(
        const char* key) const
{
    uint8_t value = GetValue();
    char *result = new char[16];
    memset(result, '\0', 16);
    snprintf(result, 16, "%d", value);
    return result;
}

#pragma mark -

Integer16Chunk::Integer16Chunk(
    const char *           inName,
    uint16_t               inValue,
    const ContentCodes *   inContentCodes)
    : Chunk(inName, inContentCodes)
{
    mValue = inValue;
}

Integer16Chunk::Integer16Chunk(
    ChunkType              inType,
    uint32_t               inLength,
    const void *           inData,
    const ContentCodes *   inContentCodes)
    : Chunk(inType, inContentCodes)
{
    // Check size
    if (inLength != sizeof(uint16_t))
    {
//        throw "integer length incorrect";
        fprintf(stderr, "integer length incorrect");
        exit(1);
    }

    // Get the value
    memcpy(&mValue, inData, sizeof(mValue));
    mValue = UINT16_SWAB(mValue);
}

uint16_t
Integer16Chunk::GetValue() const
{
    return mValue;
}

void
Integer16Chunk::SetValue(uint16_t inValue)
{
    mValue = inValue;
}

uint32_t
Integer16Chunk::GetLength() const
{
    return sizeof(mValue);
}

uint32_t
Integer16Chunk::GetData(
    uint32_t   inLength,
    void *     outBuffer) const
{
    if (inLength > 2)
        inLength = 2;

    uint16_t theValue = UINT16_SWAB(mValue);
    memcpy(outBuffer, &theValue, inLength);

    return inLength;
}

void
Integer16Chunk::Display(
    std::ostream &   inStream,
    int              inLevel) const
{
    Chunk::Display(inStream, inLevel);
    inStream << mValue;
}

const char*
Integer16Chunk::GetStringValue(
        const char* key) const
{
    uint16_t value = GetValue();
    char* result = new char[16];
    memset(result, '\0', 16);
    snprintf(result, 16, "%d", value);
    return result;
}

#pragma mark -

Integer32Chunk::Integer32Chunk(
    const char *           inName,
    uint32_t               inValue,
    const ContentCodes *   inContentCodes)
    : Chunk(inName, inContentCodes)
{
    mValue = inValue;
}

Integer32Chunk::Integer32Chunk(
    ChunkType              inType,
    uint32_t               inLength,
    const void *           inData,
    const ContentCodes *   inContentCodes)
    : Chunk(inType, inContentCodes)
{
    // Check size
    if (inLength != sizeof(uint32_t))
    {
//        throw "integer length incorrect";
        fprintf(stderr, "integer length incorrect");
        exit(1);
    }

    // Get the value
    memcpy(&mValue, inData, sizeof(mValue));
    mValue = UINT32_SWAB(mValue);
}

uint32_t
Integer32Chunk::GetValue() const
{
    return mValue;
}

void
Integer32Chunk::SetValue(uint32_t inValue)
{
    mValue = inValue;
}

uint32_t
Integer32Chunk::GetLength() const
{
    return sizeof(mValue);
}

uint32_t
Integer32Chunk::GetData(
    uint32_t   inLength,
    void *     outBuffer) const
{
    if (inLength > 4)
        inLength = 4;

    uint32_t theValue = UINT32_SWAB(mValue);
    memcpy(outBuffer, &theValue, inLength);

    return inLength;
}

void
Integer32Chunk::Display(
    std::ostream &   inStream,
    int              inLevel) const
{
    Chunk::Display(inStream, inLevel);
    inStream << mValue;
}

const char*
Integer32Chunk::GetStringValue(
        const char* key) const
{
    uint32_t value = GetValue();
    char* result = new char[16];
    memset(result, '\0', 16);
    snprintf(result, 16, "%d", value);
    return result;
}

#pragma mark -

Integer64Chunk::Integer64Chunk(
    const char *           inName,
    uint64_t               inValue,
    const ContentCodes *   inContentCodes)
    : Chunk(inName, inContentCodes)
{
    mValue = inValue;
}

Integer64Chunk::Integer64Chunk(
    ChunkType              inType,
    uint32_t               inLength,
    const void *           inData,
    const ContentCodes *   inContentCodes)
    : Chunk(inType, inContentCodes)
{
    // Check size
    if (inLength != sizeof(uint64_t))
    {
//        throw "integer length incorrect";
        fprintf(stderr, "integer length incorrect");
        exit(1);
    }

    // Get the value
    memcpy(&mValue, inData, sizeof(mValue));
    mValue = UINT64_SWAB(mValue);
}

uint64_t
Integer64Chunk::GetValue() const
{
    return mValue;
}

void
Integer64Chunk::SetValue(uint64_t inValue)
{
    mValue = inValue;
}

uint32_t
Integer64Chunk::GetLength() const
{
    return sizeof(mValue);
}

uint32_t
Integer64Chunk::GetData(
    uint32_t   inLength,
    void *     outBuffer) const
{
    if (inLength > 8)
        inLength = 8;

    uint64_t theValue = UINT64_SWAB(mValue);
    memcpy(outBuffer, &theValue, inLength);

    return inLength;
}

void
Integer64Chunk::Display(
    std::ostream &   inStream,
    int              inLevel) const
{
    Chunk::Display(inStream, inLevel);
    inStream << mValue;
}

const char*
Integer64Chunk::GetStringValue(
        const char* key) const
{
    int64_t value = GetValue();
    char *result = new char[16];
    memset(result, '\0', 16);
    snprintf(result, 16, "%lld", value);
    return result;
}

} /* namespace DAAP */
