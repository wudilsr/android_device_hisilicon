/*
 *  $Id: integer-chunk.h,v 1.11 2003/05/29 14:24:03 bootc Exp $
 *  libdaap: integer-chunk.h
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

#ifndef __DAAP_INTEGER_CHUNK_H__
#define __DAAP_INTEGER_CHUNK_H__

#include <libdaap/chunk.h>
#include <iostream>

namespace DAAP {

class Integer8Chunk : public Chunk
{
    public:
        Integer8Chunk(
            const char *           inName,
            uint8_t                inValue,
            const ContentCodes *   inContentCodes = NULL);

        Integer8Chunk(
            ChunkType              inType,
            uint32_t               inLength,
            const void *           inData,
            const ContentCodes *   inContentCodes);

        uint8_t
        GetValue() const;

        void
        SetValue(uint8_t inValue);

        /*
         *  public Integer8Chunk::GetLength()
         *
         *  Discussion:
         *    Returns the length of the data contained within this chunk.
         *
         *  Result:
         *    The number of bytes that would be returned by
         *    Chunk::GetData().
         */
        virtual uint32_t
        GetLength() const;

        /*
         *  public Integer8Chunk::GetData()
         *
         *  Discussion:
         *    Copies the data contained in this chunk into a buffer.
         *
         *  Parameters:
         *
         *    inLength:
         *      The length of the buffer.  If the length is smaller than
         *      GetLength(), only inLength bytes will be copied into the
         *      buffer.
         *
         *    outBuffer:
         *      The buffer to copy the data into.
         *
         *  Result:
         *    The number of bytes copied into the buffer which will be equal
         *    to the smaller of inLength and GetLength().
         */
        virtual uint32_t
        GetData(
            uint32_t   inLength,
            void *     outBuffer) const;

        virtual void
        Display(
            std::ostream &   inStream,
            int              inLevel = 0) const;

        virtual const char*
        GetStringValue(const char* key) const;

    private:
        uint8_t   mValue;
};

class Integer16Chunk : public Chunk
{
    public:
        Integer16Chunk(
            const char *           inName,
            uint16_t               inValue,
            const ContentCodes *   inContentCodes = NULL);

        Integer16Chunk(
            ChunkType              inType,
            uint32_t               inLength,
            const void *           inData,
            const ContentCodes *   inContentCodes);

        uint16_t
        GetValue() const;

        void
        SetValue(uint16_t inValue);

        /*
         *  public Integer16Chunk::GetLength()
         *
         *  Discussion:
         *    Returns the length of the data contained within this chunk.
         *
         *  Result:
         *    The number of bytes that would be returned by
         *    Chunk::GetData().
         */
        virtual uint32_t
        GetLength() const;

        /*
         *  public Integer16Chunk::GetData()
         *
         *  Discussion:
         *    Copies the data contained in this chunk into a buffer.
         *
         *  Parameters:
         *
         *    inLength:
         *      The length of the buffer.  If the length is smaller than
         *      GetLength(), only inLength bytes will be copied into the
         *      buffer.
         *
         *    outBuffer:
         *      The buffer to copy the data into.
         *
         *  Result:
         *    The number of bytes copied into the buffer which will be equal
         *    to the smaller of inLength and GetLength().
         */
        virtual uint32_t
        GetData(
            uint32_t   inLength,
            void *     outBuffer) const;

        virtual void
        Display(
            std::ostream &   inStream,
            int              inLevel = 0) const;

        virtual const char*
        GetStringValue(const char* key) const;

    private:
        uint16_t   mValue;
};

class Integer32Chunk : public Chunk
{
    public:
        Integer32Chunk(
            const char *           inName,
            uint32_t               inValue,
            const ContentCodes *   inContentCodes = NULL);

        Integer32Chunk(
            ChunkType              inType,
            uint32_t               inLength,
            const void *           inData,
            const ContentCodes *   inContentCodes);

        uint32_t
        GetValue() const;

        void
        SetValue(uint32_t inValue);

        /*
         *  public Integer32Chunk::GetLength()
         *
         *  Discussion:
         *    Returns the length of the data contained within this chunk.
         *
         *  Result:
         *    The number of bytes that would be returned by
         *    Chunk::GetData().
         */
        virtual uint32_t
        GetLength() const;

        /*
         *  public Integer32Chunk::GetData()
         *
         *  Discussion:
         *    Copies the data contained in this chunk into a buffer.
         *
         *  Parameters:
         *
         *    inLength:
         *      The length of the buffer.  If the length is smaller than
         *      GetLength(), only inLength bytes will be copied into the
         *      buffer.
         *
         *    outBuffer:
         *      The buffer to copy the data into.
         *
         *  Result:
         *    The number of bytes copied into the buffer which will be equal
         *    to the smaller of inLength and GetLength().
         */
        virtual uint32_t
        GetData(
            uint32_t   inLength,
            void *     outBuffer) const;

        virtual void
        Display(
            std::ostream &   inStream,
            int              inLevel = 0) const;

        virtual const char*
        GetStringValue(const char* key) const;

    private:
        uint32_t   mValue;
};

class Integer64Chunk : public Chunk
{
    public:
        Integer64Chunk(
            const char *           inName,
            uint64_t               inValue,
            const ContentCodes *   inContentCodes = NULL);

        Integer64Chunk(
            ChunkType              inType,
            uint32_t               inLength,
            const void *           inData,
            const ContentCodes *   inContentCodes);

        uint64_t
        GetValue() const;

        void
        SetValue(uint64_t inValue);

        /*
         *  public Integer64Chunk::GetLength()
         *
         *  Discussion:
         *    Returns the length of the data contained within this chunk.
         *
         *  Result:
         *    The number of bytes that would be returned by
         *    Chunk::GetData().
         */
        virtual uint32_t
        GetLength() const;

        /*
         *  public Integer64Chunk::GetData()
         *
         *  Discussion:
         *    Copies the data contained in this chunk into a buffer.
         *
         *  Parameters:
         *
         *    inLength:
         *      The length of the buffer.  If the length is smaller than
         *      GetLength(), only inLength bytes will be copied into the
         *      buffer.
         *
         *    outBuffer:
         *      The buffer to copy the data into.
         *
         *  Result:
         *    The number of bytes copied into the buffer which will be equal
         *    to the smaller of inLength and GetLength().
         */
        virtual uint32_t
        GetData(
            uint32_t   inLength,
            void *     outBuffer) const;

        virtual void
        Display(
            std::ostream &   inStream,
            int              inLevel = 0) const;

        virtual const char*
        GetStringValue(const char* key) const;

    private:
        uint64_t   mValue;
};

} /* namespace DAAP */

#endif /* __DAAP_INTEGER_CHUNK_H__ */
