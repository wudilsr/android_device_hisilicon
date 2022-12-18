/*
 *  $Id: content-codes.h,v 1.9 2003/05/29 14:40:13 bootc Exp $
 *  libdaap: content-codes.h
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

#ifndef __DAAP_CONTENT_CODES_H__
#define __DAAP_CONTENT_CODES_H__

#include <inttypes.h>
#include <map>

namespace DAAP {

/*
 *  typedef ChunkType
 *
 *  Discussion:
 *    A unsigned 32-bit value used to contain a chunk's type.  This is a
 *    4-character string packed into a big-endian unsigned long.
 */
typedef uint32_t ChunkType;

// Forward definitions
class ChunkInfo;
class Chunk;
class ContainerChunk;

/*
 *  class ContentCodes
 *
 *  Discussion:
 *    A class containing a set of content codes, as returned from a
 *    /content-codes query to a DAAP server.  It is used to construct chunks
 *    based upon type and to retrieve chunks' full names.
 */
class ContentCodes
{
    public:
        /*
         *  public ContentCodes::DefaultContentCodes()
         *
         *  Discussion:
         *    Returns a built-in set of content codes that should be enough
         *    to decode a /server-info and /content-codes response.  These
         *    built-in types should not be used for more involved requests,
         *    instead a new set of types specific to the server should be
         *    constructed.  See ContentCodes::ContentCodes().
         *
         *  Result:
         *    An shared instance of ContentCodes.  DO NOT deallocate.
         */
        static const ContentCodes *
        DefaultContentCodes();

        /*
         *  public ContentCodes::ContentCodes()
         *
         *  Discussion:
         *    Creates a new set of content codes from a container
         *    representing a dmap.contentcodesresponse, or the top-level
         *    chunk returned from a /content-codes request.
         *
         *  Parameters:
         *
         *    inContainer:
         *      A container whose long name is dmap.contentcodesresponse.
         */
        ContentCodes(const ContainerChunk &inContainer);

        /*
         *  public ContentCodes::~ContentCodes()
         *
         *  Discussion:
         *    Virtual destructor.
         */
        virtual
        ~ContentCodes();

        /*
         *  public ContentCodes::CreateChunk()
         *
         *  Discussion:
         *    Creates a new subclass of Chunk depening on the chunk type
         *    passed to the method, and initializes it with data.
         *
         *  Parameters:
         *
         *    inType:
         *      The type of chunk to create.  Ultimately this decides what
         *      subclass of Chunk to use when creating the chunk.
         *
         *    inLength:
         *      The length of the data to be contained in the chunk.
         *
         *    inData:
         *      The data contained in the chunk.
         *
         *  Result:
         *    An instance of a subclass of Chunk.
         */
        Chunk *
        CreateChunk(
            ChunkType      inType,
            uint32_t       inLength,
            const void *   inData) const;

        /*
         *  public ContentCodes::GetChunkName()
         *
         *  Discussion:
         *    Returns the long name of a chunk according to the chunk type
         *    that it is given.
         *
         *  Parameters:
         *
         *    inType:
         *      The chunk type whose name is to be returned.
         *
         *  Result:
         *    A constant, null-terminated, UTF-8 encoded string.  DO NOT
         *    deallocate this value.
         */
        const char *
        GetChunkName(ChunkType inType) const;

        /*
         *  public ContentCodes::GetChunkType()
         *
         *  Discussion:
         *    Returns the chunk type associated with a chunk's long name.
         *    Throws an exception if the name cannot be found.
         *
         *  Parameters:
         *
         *    inName:
         *      The name of the chunk (e.g. dmap.protocolversion)
         *
         *  Result:
         *    The chunk's type.
         */
        ChunkType
        GetChunkType(const char *inName) const;

        /*
         *  public ContentCodes::operator[]()
         *
         *  Discussion:
         *    Returns the index-th ChunkInfo.
         *
         *  Parameters:
         *
         *    index:
         *      0-based index of ChunkInfo item to return.  Should be less
         *      than count().
         *
         *  Result:
         *    A reference to a ChunkInfo.
         */
        const ChunkInfo &
        operator[](const uint32_t &inIndex) const;

        ChunkInfo &
        operator[](const uint32_t &inIndex);

        /*
         *  public ContentCodes::Count()
         *
         *  Discussion:
         *    Returns the number of content codes in this object.
         */
        uint32_t
        Count() const;

    private:
        ContentCodes();

        ChunkInfo &
        GetChunkInfo(ChunkType inType);

        const ChunkInfo &
        GetChunkInfo(ChunkType inType) const;

        void
        SetChunkInfo(
            ChunkType      inType,
            uint16_t       inBasicType,
            const char *   inName);

        void
        SetChunkInfo(const ContainerChunk &inChunk);

        static ContentCodes *   sDefaultCodes;

        std::map<ChunkType, ChunkInfo>   mTypesMap;
};

} /* namespace DAAP */

#endif /* __DAAP_CONTENT_CODES_H__ */
