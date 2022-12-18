/*
 *  $Id: chunk.h,v 1.8 2003/05/18 02:07:50 wcc2987 Exp $
 *  libdaap: chunk.h
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

#ifndef __DAAP_CHUNK_H__
#define __DAAP_CHUNK_H__

#include <libdaap/content-codes.h>
#include <sys/types.h>
#include <iostream>

namespace DAAP {

/*
 *  class Chunk
 *
 *  Discussion:
 *    The root class that represents a chunk of data originating from a DAAP
 *    server.  All chunks will be subclasses of this class, and will present
 *    specialized methods to access the data in a more natural manner.
 */
class Chunk
{
    public:
        /*
         *  public Chunk::ReadChunk()
         *
         *  Discussion:
         *    Reads a chunk from a block of data.  Throws if there was not
         *    enough data passed to the method or if the chunk could not be
         *    created.  See ContentCodes::CreateChunk().
         *
         *  Parameters:
         *
         *    inData:
         *      A pointer to the data to create the chunk from.
         *
         *    inDataLength:
         *      The length of the data block.  If this length is longer than
         *      necessary, extra data will be ignored.
         *
         *    inTopLevel:
         *      Pass true for this parameter if the data being passed is
         *      directly from an HTTP request to the DAAP server.  This will
         *      cause the length embedded in the data to be ingored and a
         *      length will be inferred from inDataLength.
         *
         *    inContentCodes:
         *      If content codes have been downloaded for the particular
         *      server that this data comes from, pass an pointer to the
         *      object here.  If this parameter is NULL the method will use
         *      the built-in types as returned by
         *      ContentCodes::DefaultContentCodes().
         *
         *  Result:
         *    An instance of a subclass of Chunk.
         */
        static Chunk *
        ReadChunk(
            const void *           inData,
            uint32_t               inDataLength,
            bool                   inTopLevel = false,
            const ContentCodes *   inContentCodes = NULL);

        /*
         *  public Chunk::~Chunk()
         *
         *  Discussion:
         *    Virtual destructor.
         */
        virtual
        ~Chunk();

        /*
         *  public Chunk::GetType()
         *
         *  Discussion:
         *    Returns the chunk type of this chunk.  This is an unsigned
         *    32-bit value that contains a 4-character constant that is the
         *    short name of this chunk.  This value is used to return the
         *    chunk's long name (see Chunk::GetName()) and its
         *    underlying type (integer, string, container, etc...).
         *
         *  Result:
         *    A ChunkType.
         */
        ChunkType
        GetType() const;

        /*
         *  public Chunk::GetName()
         *
         *  Discussion:
         *    Returns this chunk's long name, as returned by
         *    ContentCodes::GetChunkName().
         *
         *  Result:
         *    A constant, null-terminated, UTF-8 encoded string.  DO NOT
         *    deallocate this value.
         */
        const char *
        GetName() const;

        /*
         *  public Chunk::GetLength()
         *
         *  Discussion:
         *    Returns the length of the data contained within this chunk.
         *
         *  Result:
         *    The number of bytes that would be returned by
         *    Chunk::GetData().
         */
        virtual uint32_t
        GetLength() const = 0;

        /*
         *  public Chunk::GetData()
         *
         *  Discussion:
         *    Copies the data contained in this chunk into a buffer.
         *
         *  Parameters:
         *
         *    inLength:
         *      The length of the buffer.  If the length is smaller than
         *      GetLength(), only inLength bytes or less will be copied into
         *      the buffer.
         *
         *    outBuffer:
         *      The buffer to copy the data into.
         *
         *  Result:
         *    The number of bytes copied into the buffer.
         */
        virtual uint32_t
        GetData(
            uint32_t   inLength,
            void *     outBuffer) const = 0;

        /*
         *  public Chunk::Display()
         *
         *  Discussion:
         *    Dumps this chunk in human-readable form to the provided output
         *    stream.  This method is intended to be used when debugging,
         *    and is not for use in a production environment.
         *
         *  Parameters:
         *
         *    inStream:
         *      The stream to output to.
         *
         *    inLevel:
         *      The indentation level to use.  Each level is equivalent to
         *      2 spaces.  This is only used by ContainerChunk::Display
         *      and is otherwise ignored.
         */
        virtual void
        Display(
            std::ostream &   inStream,
            int              inLevel = 0) const;

        /*
         *  public Chunk::BuildData()
         *
         *  Discussion:
         *    Prepares a chunk for transmission over the network.  Copies
         *    the chunk's data, including type and length, into the provided
         *    buffer if it is non-null, otherwise it simply returns the
         *    number of bytes required to get a copy of the chunk.
         *
         *  Parameters:
         *
         *    inLength:
         *      The length of the buffer pointed to by outBuffer.  Ignored
         *      if outBuffer is null.
         *
         *    outBuffer:
         *      The buffer to copy the serialized chunk into.
         *
         *  Result:
         *    If outBuffer was non-null, the number of bytes that were
         *    copied into the buffer.  If outBuffer was null, the number of
         *    bytes required to copy the whole chunk into.
         */
        uint32_t
        BuildData(
            uint32_t   inLength = 0,
            void *     outBuffer = NULL) const;

        static const char *GetValueOf(Chunk *containner, const char* key);

        virtual const char*
        GetStringValue(const char* key) const;

    protected:
        /*
         *  protected Chunk::Chunk()
         *
         *  Discussion:
         *    Creates a new Chunk instance.
         *
         *  Parameters:
         *
         *    inType:
         *      The type of the container.  This is a 4-letter character
         *      constant that is used to discover the basic data type that
         *      this chunk can contain as well as its name.
         *
         *    inContentCodes:
         *      The content codes to use to decode child chunks.
         */
        Chunk(
            ChunkType              inType,
            const ContentCodes *   inContentCodes);

        /*
         * protected Chunk::Chunk()
         *
         * Discussion:
         *   Constructor intended for server-side use.  Creates an empty
         *   Chunk so that the server can then fill it with data.
         *
         *  Parameters:
         *
         *    inName:
         *      The long name of the chunk.  This is used to then get the
         *      short name, or chunk type.
         *
         *    inContentCodes:
         *      Set of content codes to use when creating the chunk.  If the
         *      default value of NULL is used, the codes returned by
         *      ContentCodes::DefaultContentCodes() shall be used.
         */
        Chunk(
            const char *           inName,
            const ContentCodes *   inContentCodes = NULL);

        /*
         *  protected Chunk::GetContentCodes()
         *
         *  Discussion:
         *    Returns the content codes that this chunk was created from.
         *    This is used to return the chunk's long name
         *    (see Chunk::GetName()) and to create child chunks in the
         *    case of a container chunk.
         *
         *  Result:
         *    An instance of the ContentCodes class.
         */
        const ContentCodes *
        GetContentCodes() const;

    private:
        ChunkType              mType;
        const ContentCodes *   mContentCodes;
};

/*
 *  ::operator<<()
 *
 *  Discussion:
 *    Allows the use of the standard ostream mechanism to display debugging
 *    information about chunks.  Calls through to the Chunk::Display()
 *    method to actually display the chunk.
 *
 *  Parameters:
 *
 *    inStream:
 *      The stream to display the chunk in.
 *
 *    inChunk:
 *      The chunk to display in the stream.
 *
 *  Result:
 *    The same as inStream.  This allows chaining several statements
 *    together.
 */
std::ostream &
operator << (
    std::ostream &   inStream,
    const Chunk &    inChunk);

} /* namespace DAAP */

#endif /* __DAAP_CHUNK_H__ */
