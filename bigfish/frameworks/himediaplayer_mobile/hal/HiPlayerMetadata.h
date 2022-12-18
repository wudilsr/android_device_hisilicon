/*
**
** Copyright 2009, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef ANDROID_HIPLAYERMETADATA_H
#define ANDROID_HIPLAYERMETADATA_H


#include "hi_svr_player.h"
#include "hi_svr_metadata.h"
#include <utils/KeyedVector.h>
#include <utils/String8.h>
#include <private/media/VideoFrame.h>
#include <media/mediametadataretriever.h>

namespace android {
#define HiKeyMIMEType "mime"
#define HiKeyAlbum "album"
#define HiKeyArtist "artist"
#define HiKeyAlbumArtist "album_artist"
#define HiKeyAuthor "author"
#define HiKeyComposer "composer"
#define HiKeyGenre "genre"
#define HiKeyTitle "title"
#define HiKeyYear "year"
#define HiKeyDate "date"
#define HiKeyDuration "duration"
#define HiKeyID3Pic "APIC" /*"id3pic"*/
//#define HiKeyAuthor "author"
//#define HiKeyDate "date"
//#define HiKeyTrackNum "tracknum"
#define HiKeyWidth "videowidth"
#define HiKeyHeight "videoheight"
#define HiKeyBitrate "track-info/audio/bit-rate"
#define HiKeyTrackNum       "tracknumber"
#define HiKeyDiscNumber     "discnumber"
#define HiKeyCompliation    "compliation"
#define HiKeyHasAudio       "hasaudio"
#define HiKeyHasVideo       "hasvideo"
#define HiKeyLanguage       "language"
#define HiKeyIsDRM          "isdrm"
#define HiKeyLocation       "location"
#define HiKeyRotation       "rotation"
#define HiKeyCDTrackNumber  "cdtracknumber"

class HiPlayerMetadata {
public:
    HiPlayerMetadata();
    virtual ~HiPlayerMetadata();

    virtual status_t setDataSource(
                const char *url, const KeyedVector<String8, String8> *headers);
    virtual status_t setDataSource(int fd, int64_t offset, int64_t length);

    virtual VideoFrame* getFrameAtTime(int64_t timeUs, int option);
    virtual const char* extractMetadata(int keyCode);
    virtual MediaAlbumArt* extractAlbumArt();
private:
    char*     mUrl;
    HI_HANDLE mHandle;
    bool      mParsedMetaData;
    KeyedVector<int, String8> mMetaData;
    HI_SVR_PLAYER_METADATA_S* mpMetadata_Ori;
    status_t createMediaRetriever();
    status_t destroyMediaRetriever();
    void     convertMetadata();
    unsigned int mId;
};

}; // namespace android

#endif // ANDROID_HIPLAYERMETADATA_H