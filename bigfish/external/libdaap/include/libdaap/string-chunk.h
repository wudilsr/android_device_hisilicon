/*
 *  $Id: string-chunk.h,v 1.9 2003/05/29 14:24:03 bootc Exp $
 *  libdaap: string-chunk.h
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

#ifndef __DAAP_STRING_CHUNK_H__
#define __DAAP_STRING_CHUNK_H__

#include <libdaap/chunk.h>
#include <iostream>

namespace DAAP {

class StringChunk : public Chunk
{
    public:
        StringChunk(
            const char *           inName,
            const char *           inValue,
            uint32_t               inLength = 0,
            const ContentCodes *   inContentCodes = NULL);

        StringChunk(
            ChunkType              inType,
            uint32_t               inLength,
            const void *           inData,
            const ContentCodes *   inContentCodes);

        virtual
        ~StringChunk();

        const char *
        GetValue() const;

        // If length is 0, uses strlen(inValue)
        void
        SetValue(
            const char *   inValue,
            uint32_t       inLength = 0);

        virtual uint32_t
        GetLength() const;

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
        char *     mValue;
        uint32_t   mLength;
};

} /* namespace DAAP */

#endif /* __DAAP_STRING_CHUNK_H__ */
