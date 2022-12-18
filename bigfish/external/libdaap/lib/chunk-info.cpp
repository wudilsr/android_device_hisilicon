/*
 *  $Id: chunk-info.cpp,v 1.5 2003/05/16 12:27:29 bootc Exp $
 *  libdaap: chunk-info.cpp
 *
 *  Created by Chris Boot on Wed May 07 2003.
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

#include <libdaap/chunk-info.h>
#include "macros.h"
#include <libdaap/integer-chunk.h>
#include <libdaap/string-chunk.h>
#include <libdaap/container-chunk.h>

namespace DAAP {

ChunkInfo::ChunkInfo(
    ChunkType      inType,
    const char *   inName,
    uint16_t       inBasicType)
{
    mType = inType;
    mName = inName;
    mBasicType = inBasicType;
}

ChunkInfo::ChunkInfo(
    const ContainerChunk &inChunk)
{
    // Get the chunk type
    mType = dynamic_cast<const Integer32Chunk &>(
        inChunk.ChildNamed("dmap.contentcodesnumber")).GetValue();

    // Get the chunk name
    mName = dynamic_cast<const StringChunk &>(
        inChunk.ChildNamed("dmap.contentcodesname")).GetValue();

    // Get the chunk basic type
    mBasicType = dynamic_cast<const Integer16Chunk &>(
        inChunk.ChildNamed("dmap.contentcodestype")).GetValue();
}

ChunkInfo::ChunkInfo(
    const ChunkInfo &inInfo)
{
    mType = inInfo.mType;
    mName = inInfo.mName;
    mBasicType = inInfo.mBasicType;
}

ChunkInfo::~ChunkInfo()
{

}

ChunkType
ChunkInfo::GetType() const
{
    return mType;
}

const char *
ChunkInfo::GetName() const
{
    return mName;
}

uint16_t
ChunkInfo::GetBasicType() const
{
    return mBasicType;
}

} /* namespace DAAP */
