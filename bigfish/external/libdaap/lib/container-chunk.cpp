/*
 *  $Id: container-chunk.cpp,v 1.12 2003/05/29 14:24:03 bootc Exp $
 *  libdaap: container-chunk.cpp
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

#include <libdaap/container-chunk.h>
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>

namespace DAAP {

ContainerChunk::ContainerChunk(
    const char *           inName,
    const ContentCodes *   inContentCodes)
    : Chunk(inName, inContentCodes)
{

}

ContainerChunk::ContainerChunk(
    ChunkType              inType,
    uint32_t               inLength,
    const void *           inData,
    const ContentCodes *   inContentCodes)
    : Chunk(inType, inContentCodes)
{
    uint32_t theOffset = 0;
    const uint8_t *theData = (const uint8_t *)inData;

    while (theOffset < inLength)
    {
        uint32_t theChildLength = inLength - theOffset;
        const uint8_t *theChildData = theData + theOffset;

        Chunk *theChild = Chunk::ReadChunk(theChildData,
            theChildLength, false, inContentCodes);

        theOffset += (theChild->GetLength() + 8);

        AddChild(theChild);
    }
}

ContainerChunk::~ContainerChunk()
{
    std::vector<Chunk *>::iterator theIterator;

    // Iterate through every child
    theIterator = mChildren.begin();
    while (theIterator != mChildren.end())
    {
        // Get a child
        Chunk *theChunk = *theIterator;

        // Free the memory
        delete theChunk;

        // Increment the iterator
        theIterator++;
    }
}

size_t
ContainerChunk::CountChildren() const
{
    return mChildren.size();
}

const Chunk &
ContainerChunk::operator[](size_t inIndex) const
{
    return *mChildren[inIndex];
}

Chunk &
ContainerChunk::operator[](size_t inIndex)
{
    return *mChildren[inIndex];
}

const Chunk &
ContainerChunk::ChildNamed(const char *inName) const
{
    std::vector<Chunk *>::const_iterator theIterator;

    // Iterate through every child
    theIterator = mChildren.begin();
    while (theIterator != mChildren.end())
    {
        // Get a child
        const Chunk &theChunk = **theIterator;

        if (strcmp(inName, theChunk.GetName()) == 0)
            return theChunk;

        // Increment the iterator
        theIterator++;
    }

    // No such child
//    throw "no such child";
    fprintf(stderr, "no such child");
    exit(1);
}

Chunk &
ContainerChunk::ChildNamed(const char *inName)
{
    std::vector<Chunk *>::iterator theIterator;

    // Iterate through every child
    theIterator = mChildren.begin();
    while (theIterator != mChildren.end())
    {
        // Get a child
        Chunk &theChunk = **theIterator;

        if (strcmp(inName, theChunk.GetName()) == 0)
            return theChunk;

        // Increment the iterator
        theIterator++;
    }

    // No such child
//    throw "no such child";
    fprintf(stderr, "no such child");
    exit(1);
}

void
ContainerChunk::Display(
    std::ostream &   inStream,
    int              inLevel) const
{
    std::vector<Chunk *>::const_iterator theIterator;

    Chunk::Display(inStream, inLevel);

    // Print the list start
    inStream << "{" << std::endl;

    // Iterate through every child
    theIterator = mChildren.begin();
    while (theIterator != mChildren.end())
    {
        // Get a child
        const Chunk &theChunk = **theIterator;

        for (int I = 0; I <= inLevel; I++)
            inStream << "  ";

        // Print it out
        theChunk.Display(inStream, inLevel + 1);
        inStream << std::endl;

        // Increment the iterator
        theIterator++;
    }

    for (int I = 0; I < inLevel; I++)
        inStream << "  ";

    // Print the list end
    inStream << "}";
}

void
ContainerChunk::AddChild(Chunk *inChild)
{
    // Add the child to our list
    if ( inChild )
        mChildren.push_back(inChild);
}

uint32_t
ContainerChunk::GetLength() const
{
    std::vector<Chunk *>::const_iterator theIterator;
    uint32_t theLength = 0;

    // Iterate through every child
    theIterator = mChildren.begin();
    while (theIterator != mChildren.end())
    {
        // Get a child
        const Chunk *theChunk = *theIterator;
        if ( theChunk )
        // Add the child's length
        theLength += theChunk->GetLength() + 8;

        // Increment the iterator
        theIterator++;
    }

    return theLength;
}

uint32_t
ContainerChunk::GetData(
    uint32_t   inLength,
    void *     outBuffer) const
{
    std::vector<Chunk *>::const_iterator theIterator;
    uint8_t *theBuffer = (uint8_t *)outBuffer;
    uint32_t thePosition = 0;

    if (inLength > GetLength())
        inLength = GetLength();

    // Iterate through every child
    theIterator = mChildren.begin();
    while ((theIterator != mChildren.end()) && (thePosition < inLength))
    {
        // Get a child
        const Chunk &theChunk = **theIterator;

        // Copy over the child's data
        thePosition += theChunk.BuildData(
            inLength - thePosition,
            theBuffer + thePosition);

        // Increment the iterator
        theIterator++;
    }

    return inLength;
}

const char*
ContainerChunk::GetStringValue(
        const char* key) const
{
    return NULL;
}

} /* namespace DAAP */
