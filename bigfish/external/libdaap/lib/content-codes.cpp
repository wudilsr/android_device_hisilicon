/*
 *  $Id: content-codes.cpp,v 1.13 2003/05/29 14:40:14 bootc Exp $
 *  libdaap: content-codes.cpp
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

#include <libdaap/content-codes.h>
#include "macros.h"
#include <libdaap/chunk-info.h>
#include <libdaap/integer-chunk.h>
#include <libdaap/string-chunk.h>
#include <libdaap/version-chunk.h>
#include <libdaap/container-chunk.h>
#include <libdaap/cxxabi.h>
#include <stdio.h>
#include <stdlib.h>

namespace DAAP {

template<class T>
static Chunk *
CreateChunk(
    ChunkType              inType,
    uint32_t               inLength,
    const void *           inData,
    const ContentCodes *   inContentCodes)
{
    return new T(inType, inLength, inData, inContentCodes);
}

typedef Chunk *(*ChunkCreatorFunc)(
    ChunkType              inType,
    uint32_t               inLength,
    const void *           inData,
    const ContentCodes *   inContentCodes);

struct BasicTypeInfo
{
    uint16_t           basic_type;
    ChunkCreatorFunc   creator;
};

const BasicTypeInfo kBasicTypes[] =
{
    {  1, CreateChunk<Integer8Chunk> },
    {  3, CreateChunk<Integer16Chunk> },
    {  5, CreateChunk<Integer32Chunk> },
    {  7, CreateChunk<Integer64Chunk> },
    {  9, CreateChunk<StringChunk> },
    { 10, CreateChunk<Integer32Chunk> },
    { 11, CreateChunk<VersionChunk> },
    { 12, CreateChunk<ContainerChunk> },
    {  0, NULL }
};

ContentCodes *ContentCodes::sDefaultCodes = NULL;

#pragma mark -
#pragma mark *** STATIC METHODS ***

const ContentCodes *
ContentCodes::DefaultContentCodes()
{
    if (sDefaultCodes == NULL)
        sDefaultCodes = new ContentCodes();

    return sDefaultCodes;
}

#pragma mark -
#pragma mark *** CONSTRUCTORS / DESTRUCTOR ***

ContentCodes::ContentCodes()
{
    // AAAARGH!  Ugly.  I don't like it.
    SetChunkInfo(FOUR_CHAR_CODE('m', 'i', 'i', 'd'),  5, "dmap.itemid");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'i', 'n', 'm'),  9, "dmap.itemname");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'i', 'k', 'd'),  1, "dmap.itemkind");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'p', 'e', 'r'),  7, "dmap.persistentid");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'c', 'o', 'n'), 12, "dmap.container");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'c', 't', 'i'),  5, "dmap.containeritemid");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'p', 'c', 'o'),  5, "dmap.parentcontainerid");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 't', 't'),  5, "dmap.status");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 't', 's'),  9, "dmap.statusstring");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'i', 'm', 'c'),  5, "dmap.itemcount");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'c', 't', 'c'),  5, "dmap.containercount");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'r', 'c', 'o'),  5, "dmap.returnedcount");
    SetChunkInfo(FOUR_CHAR_CODE('m', 't', 'c', 'o'),  5, "dmap.specifiedtotalcount");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'l', 'c', 'l'), 12, "dmap.listing");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'l', 'i', 't'), 12, "dmap.listingitem");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'b', 'c', 'l'), 12, "dmap.bag");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'd', 'c', 'l'), 12, "dmap.dictionary");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'r', 'v'), 12, "dmap.serverinforesponse");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'a', 'u'),  1, "dmap.authenticationmethod");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'l', 'r'),  1, "dmap.loginrequired");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'p', 'r', 'o'), 11, "dmap.protocolversion");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'a', 'l'),  1, "dmap.supportsautologout");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'u', 'p'),  1, "dmap.supportsupdate");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'p', 'i'),  1, "dmap.supportspersistentids");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'e', 'x'),  1, "dmap.supportsextensions");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'b', 'r'),  1, "dmap.supportsbrowse");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'q', 'y'),  1, "dmap.supportsquery");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'i', 'x'),  1, "dmap.supportsindex");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'r', 's'),  1, "dmap.supportsresolve");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 't', 'm'),  5, "dmap.timeoutinterval");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'd', 'c'),  5, "dmap.databasescount");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'l', 'o', 'g'), 12, "dmap.loginresponse");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'l', 'i', 'd'),  5, "dmap.sessionid");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'u', 'p', 'd'), 12, "dmap.updateresponse");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'u', 's', 'r'),  5, "dmap.serverrevision");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'u', 't', 'y'),  1, "dmap.updatetype");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'u', 'd', 'l'), 12, "dmap.deletedidlisting");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'c', 'c', 'r'), 12, "dmap.contentcodesresponse");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'c', 'n', 'm'),  5, "dmap.contentcodesnumber");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'c', 'n', 'a'),  9, "dmap.contentcodesname");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'c', 't', 'y'),  3, "dmap.contentcodestype");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'p', 'r', 'o'), 11, "daap.protocolversion");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'v', 'd', 'b'), 12, "daap.serverdatabases");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'b', 'r', 'o'), 12, "daap.databasebrowse");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'b', 'a', 'l'), 12, "daap.browsealbumlisting");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'b', 'a', 'r'), 12, "daap.browseartistlisting");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'b', 'c', 'p'), 12, "daap.browsecomposerlisting");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'b', 'g', 'n'), 12, "daap.browsegenrelisting");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'd', 'b', 's'), 12, "daap.databasesongs");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'a', 'l'),  9, "daap.songalbum");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'a', 'r'),  9, "daap.songartist");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'b', 't'),  3, "daap.songbeatsperminute");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'b', 'r'),  3, "daap.songbitrate");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'c', 'm'),  9, "daap.songcomment");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'c', 'o'),  1, "daap.songcompilation");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'c', 'p'),  9, "daap.songcomposer");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'd', 'a'), 10, "daap.songdateadded");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'd', 'm'), 10, "daap.songdatemodified");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'd', 'c'),  3, "daap.songdisccount");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'd', 'n'),  3, "daap.songdiscnumber");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'd', 'b'),  1, "daap.songdisabled");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'e', 'q'),  9, "daap.songeqpreset");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'f', 'm'),  9, "daap.songformat");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'g', 'n'),  9, "daap.songgenre");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'd', 't'),  9, "daap.songdescription");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'r', 'v'),  1, "daap.songrelativevolume");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 's', 'r'),  5, "daap.songsamplerate");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 's', 'z'),  5, "daap.songsize");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 's', 't'),  5, "daap.songstarttime");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 's', 'p'),  5, "daap.songstoptime");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 't', 'm'),  5, "daap.songtime");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 't', 'c'),  3, "daap.songtrackcount");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 't', 'n'),  3, "daap.songtracknumber");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'u', 'r'),  1, "daap.songuserrating");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'y', 'r'),  3, "daap.songyear");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'd', 'k'),  1, "daap.songdatakind");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'u', 'l'),  9, "daap.songdataurl");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'p', 'l', 'y'), 12, "daap.databaseplaylists");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'b', 'p', 'l'),  1, "daap.baseplaylist");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'p', 's', 'o'), 12, "daap.playlistsongs");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'r', 's', 'v'), 12, "daap.resolve");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'r', 'i', 'f'), 12, "daap.resolveinfo");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'N', 'V'),  5, "com.apple.itunes.norm-volume");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'S', 'P'),  1, "com.apple.itunes.smart-playlist");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'g', 'r', 'p'), 9, "unknown:agrp");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'c', 'd'), 5, "daap.songcodectype");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'c', 's'), 5, "daap.songcodecsubtype");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'P', 'C'), 1, "com.apple.itunes.is-podcast");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'c', 't'), 9, "daap.songcategory");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'c', 'n'), 9, "daap.songcontentdescription");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'k', 'y'), 9, "daap.songkeywords");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'c', 'r'), 9, "daap.songcr");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'H', 'V'), 1, "com.apple.itunes.has-video");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'M', 'K'), 1, "com.apple.itunes.mediakind");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'S', 'N'), 9, "com.apple.itunes.series-name");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'N', 'N'), 9, "com.apple.itunes.network-name");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'E', 'N'), 9, "com.apple.itunes.episode-num-str");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'E', 'S'), 5, "com.apple.itunes.episode-sort");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'S', 'U'), 5, "com.apple.itunes.season-num");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'G', 'H'), 5, "com.apple.itunes.gapless-heur");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'G', 'D'), 5, "com.apple.itunes.gapless-enc-dr");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'G', 'E'), 5, "com.apple.itunes.gapless-enc-del");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'G', 'R'), 7, "com.apple.itunes.gapless-resy");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'G', 'U'), 7, "com.apple.itunes.gapless-dur");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'a', 'a'), 9, "daap.songalbumartist");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'g', 'p'), 1, "daap.songgapless");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'e', 'd'), 3, "daap.songextradata");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'h', 'p'), 1, "daap.songhasbeenplayed");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 's', 'a'), 9, "daap.sortartist");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 's', 'c'), 9, "daap.sortalbum");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 's', 'l'), 9, "daap.sortalbumartist");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 's', 'n'), 9, "daap.sortname");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 's', 'u'), 9, "daap.sortu");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 's', 's'), 9, "daap.sortseriesname");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'b', 'k'), 1, "daap.songbookmarkable");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'p', 'u'), 9, "daap.songpodcasturl");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'C', 'R'), 9, "com.apple.itunes.content-rating");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'a', 'i'), 7, "daap.songalbumid");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'l', 's'), 7, "daap.songlongsize");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'H', 'D'), 1, "com.apple.itunes.is-hd-video");
    SetChunkInfo(FOUR_CHAR_CODE('c', 'e', 'J', 'V'), 5, "unknown:ceJV");
    SetChunkInfo(FOUR_CHAR_CODE('c', 'e', 'J', 'C'), 9, "unknown:ceJC");
    SetChunkInfo(FOUR_CHAR_CODE('c', 'e', 'J', 'S'), 9, "unknown:ceJS");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'S', 'E'), 9, "unknown:aeSE");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'D', 'V'), 5, "unknown:aeDV");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'D', 'P'), 5, "unknown:aeDP");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'D', 'R'), 9, "unknown:aeDR");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'N', 'D'), 9, "unknown:aeND");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'K', '1'), 9, "unknown:aeK1");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'K', '2'), 9, "unknown:aeK2");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'X', 'D'), 9, "unknown:aeXD");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'M', 'k'), 9, "com.apple.itunes.mediakind1");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'M', 'X'), 9, "unknown:aeMX");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'p', 'c'), 9, "unknown:aspc");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'r', 'i'), 9, "unknown:asri");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'C', 'S'), 9, "unknown:aeCS");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'C', 'S'), 9, "unknown:aeCS");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'p', 'l'), 9, "unknown:aspl");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'k', 'p'), 9, "unknown:askp");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'a', 'c'), 9, "unknown:asac");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'k', 'd'), 9, "unknown:askd");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'd', 's', 't'), 9, "unknown:mdst");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'e', 's'), 9, "unknown:ases");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'C', 'd'), 9, "unknown:aeCd");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'C', 'U'), 9, "unknown:aeCU");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'C', 'M'), 9, "unknown:aeCM");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'r', 's'), 9, "unknown:asrs");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'l', 'r'), 9, "unknown:aslr");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'a', 's'), 9, "unknown:asas");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'l', 'c'), 9, "daap.songlongcontentdescription");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 'a', 's'), 5, "dmap.authenticationschemes");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 't', 'c'), 10, "dmap.utctime");
    SetChunkInfo(FOUR_CHAR_CODE('m', 's', 't', 'o'), 6, "dmap.utcoffset");
    SetChunkInfo(FOUR_CHAR_CODE('c', 'a', 'p', 's'), 9, "unknown:caps");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'p', 's', 'm'), 1, "daap.playlistshufflemode");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'p', 'r', 'm'), 1, "daap.playlistrepeatmode");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'P', 'P'), 1, "com.apple.itunes.is-podcast-playlist");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'P', 'S'), 1, "com.apple.itunes.special-playlist");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'd', 'r'), 10, "daap.songdatereleased");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'd', 'p'), 10, "daap.songdatepurchased");
    SetChunkInfo(FOUR_CHAR_CODE('a', 's', 'b', 'o'), 5, "daap.songbookmark");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'S', 'G'), 1, "com.apple.itunes.saved-genius");
    SetChunkInfo(FOUR_CHAR_CODE('m', 'e', 'd', 's'), 5, "dmap.editcommandssupported");
    SetChunkInfo(FOUR_CHAR_CODE('a', 'e', 'G', 's'), 9, "unknow:aeGs");
}

ContentCodes::ContentCodes(const ContainerChunk &inContainer)
{
    // Make sure we're given a content codes response to work with
    if (strcmp(inContainer.GetName(), "dmap.contentcodesresponse"))
    {
//        throw "must pass content codes response";
        fprintf(stderr, "must pass content codes respomust pass content codes response");
        exit(1);
    }

    // Loop through every child
    for (size_t I = 0; I < inContainer.CountChildren(); I++)
    {
        // Ignore if it's not a dictionary
        if (strcmp(inContainer.GetName(), "dmap.dictionary"))
            continue;

        // Get a reference to the child
        const ContainerChunk &theChild =
            dynamic_cast<const ContainerChunk &>(inContainer[I]);

        // Set the chunk info
        SetChunkInfo(theChild);
    }
}

ContentCodes::~ContentCodes()
{

}

#pragma mark -
#pragma mark *** PUBLIC METHODS ***

Chunk *
ContentCodes::CreateChunk(
    ChunkType      inType,
    uint32_t       inLength,
    const void *   inData) const
{
    // Get the chunk info
    const ChunkInfo &theInfo = GetChunkInfo(inType);

    for (int I = 0; kBasicTypes[I].creator != NULL; I++)
    {
        if (kBasicTypes[I].basic_type != theInfo.GetBasicType())
            continue;

        // Build the chunk
        Chunk *theChunk = kBasicTypes[I].creator(
            inType, inLength, inData, this);

        // Return the chunk
        return theChunk;
    }

    // We don't have a basic type for this chunk
//    throw "don't know basic type";
    fprintf(stderr, "don't know basic type");
    exit(1);
}

const char *
ContentCodes::GetChunkName(ChunkType inType) const
{
    // Get the chunk info
    const ChunkInfo &theInfo = GetChunkInfo(inType);

    // Return the name
    return theInfo.GetName();
}

const ChunkInfo&
ContentCodes::operator[](const uint32_t &inIndex) const
{
    if ( inIndex > Count() )
    {
//        throw "out of range";
        fprintf(stderr, "out of range");
        exit(1);
    }

    uint32_t i=0;

    std::map<ChunkType,ChunkInfo>::const_iterator it = mTypesMap.begin();
    for (;it!=mTypesMap.end() && i!=inIndex;it++,i++ ) {
        if (i==inIndex)
            return it->second;
    }
    if (i==inIndex && it != mTypesMap.end())
        return it->second;

//    throw "map iterator ended sooner than expected";
    fprintf(stderr, "map iterator ended sooner than expected");
    exit(1);
}

ChunkInfo&
ContentCodes::operator[](const uint32_t &inIndex)
{
    if ( inIndex > Count() )
    {
//        throw "out of range";
        fprintf(stderr, "out of range");
        exit(1);
    }

    uint32_t i=0;

    std::map<ChunkType,ChunkInfo>::iterator it = mTypesMap.begin();
    for (;it!=mTypesMap.end() && i!=inIndex;it++,i++ ) {
        if (i==inIndex)
            return it->second;
    }

//    throw "map iterator ended sooner than expected";
    fprintf(stderr, "map iterator ended sooner than expected");
    exit(1);
}

uint32_t
ContentCodes::Count() const
{
    return mTypesMap.size();
}

ChunkType
ContentCodes::GetChunkType(const char *inName) const
{
    std::map<ChunkType, ChunkInfo>::const_iterator theIterator;

    // Start at the first item
    theIterator = mTypesMap.begin();

    // We don't have such an item, throw
    while (theIterator != mTypesMap.end())
    {
        const ChunkInfo &theInfo = theIterator->second;

        // Check if the names match
        if (strcmp(theInfo.GetName(), inName))
        {
            theIterator++;
            continue;
        }

        // Return the chunk type
        return theInfo.GetType();
    }

    // No such chunk name was found
//    throw "chunk name not found";
    fprintf(stderr, "chunk name not found");
    exit(1);
}

#pragma mark -
#pragma mark *** PRIVATE METHODS ***

ChunkInfo &
ContentCodes::GetChunkInfo(ChunkType inType)
{
    std::map<ChunkType, ChunkInfo>::iterator theIterator;

    // Find the item in the map
    theIterator = mTypesMap.find(inType);

    // We don't have such an item, throw
    if (theIterator == mTypesMap.end())
    {
//        throw "unknown type";
        fprintf(stderr, "unknown type: %x\n", inType);
        exit(1);
    }

    // Return the info
    return theIterator->second;
}

const ChunkInfo &
ContentCodes::GetChunkInfo(ChunkType inType) const
{
    std::map<ChunkType, ChunkInfo>::const_iterator theIterator;

    // Find the item in the map
    theIterator = mTypesMap.find(inType);

    // We don't have such an item, throw
    if (theIterator == mTypesMap.end())
    {
//        throw "unknown type";
        fprintf(stderr, "unknown type: %x\n", inType);
        exit(1);
    }

    // Return the info
    return theIterator->second;
}

void
ContentCodes::SetChunkInfo(
    ChunkType      inType,
    uint16_t       inBasicType,
    const char *   inName)
{
    // Create the info object
    ChunkInfo theInfo(inType, inName, inBasicType);

    // Insert it into the map
    mTypesMap.insert(std::pair<ChunkType, ChunkInfo>
        (inType, theInfo));
}

void
ContentCodes::SetChunkInfo(
    const ContainerChunk &inChunk)
{
    // Create the info object
    ChunkInfo theInfo(inChunk);

    // Insert it into the map
    mTypesMap.insert(std::pair<ChunkType, ChunkInfo>
        (theInfo.GetType(), theInfo));
}

} /* namespace DAAP */
