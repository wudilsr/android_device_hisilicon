/*
 *  $Id: chunk-info.h,v 1.4 2003/05/16 12:27:28 bootc Exp $
 *  libdaap: chunk-info.h
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

#ifndef __DAAP_CHUNK_INFO_H__
#define __DAAP_CHUNK_INFO_H__

#include <libdaap/content-codes.h>

namespace DAAP {

// Forward definitions
class ContainerChunk;

/*
 *  class ChunkInfo
 *
 *  Discussion:
 *    Holds information about a particular chunk type, such as its type
 *    number, name and the type of value it contains (integer, string,
 *    container, etc...).
 */
class ChunkInfo
{
    public:
        /*
         *  public ChunkInfo::ChunkInfo()
         *
         *  Discussion:
         *    Creates a new piece of chunk info.
         *
         *  Parameters:
         *
         *    inType:
         *      The chunk's type code.
         *
         *    inName:
         *      The chunk's long name.
         *
         *    inBasicType:
         *      The chunk's basic type.
         */
        ChunkInfo(
            ChunkType      inType,
            const char *   inName,
            uint16_t       inBasicType);

        /*
         *  public ChunkInfo::ChunkInfo()
         *
         *  Discussion:
         *    Creates a new piece of chunk info.
         *
         *  Parameters:
         *
         *    inChunk:
         *      The dmap.dictionary chunk to look at to get the chunk info
         *      from.  It must contain dmap.contentcodesnumber,
         *      dmap.contentcodesname, and dmap.contentcodestype fields.
         */
        ChunkInfo(const ContainerChunk &inChunk);

        /*
         *  public ChunkInfo::ChunkInfo()
         *
         *  Discussion:
         *    Copy constructor
         *
         *  Parameters:
         *
         *    inInfo:
         *      The chunk info to copy from.
         */
        ChunkInfo(const ChunkInfo &inInfo);

        /*
         *  public ChunkInfo::~ChunkInfo()
         *
         *  Discussion:
         *    Virtual destructor.
         */
        virtual
        ~ChunkInfo();

        /*
         *  public ChunkInfo::GetType()
         *
         *  Discussion:
         *    Returns the type associated with this piece of chunk info.
         *
         *  Result:
         *    The type.
         */
        ChunkType
        GetType() const;

        /*
         *  public ChunkInfo::GetName()
         *
         *  Discussion:
         *    Returns the name associated with this piece of chunk info.
         *
         *  Result:
         *    A constant, null-terminated, UTF-8 encoded string.  DO NOT
         *    deallocate this value.
         */
        const char *
        GetName() const;

        /*
         *  public ChunkInfo::GetBasicType()
         *
         *  Discussion:
         *    Returns the basic type associated with this piece of chunk
         *    info.
         *
         *  Result:
         *    The basic type.
         */
        uint16_t
        GetBasicType() const;

    private:
        ChunkType      mType;
        const char *   mName;
        uint16_t       mBasicType;
};

} /* namespace DAAP */

#endif /* __DAAP_CHUNK_INFO_H__ */
