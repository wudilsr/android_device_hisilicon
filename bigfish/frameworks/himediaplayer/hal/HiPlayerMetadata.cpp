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

#define LOG_NDEBUG 0
#define LOG_TAG "HisiMetadataRetriever"
#include <utils/Log.h>

#include "HiPlayerMetadata.h"
#include "HiMediaSystem.h"

#include <string.h>
#include <utils/Errors.h>
#include "HiMediaDefine.h"

#include "hi_svr_charset.h"
#include "hi_svr_charset_norm.h"
#include <cutils/properties.h>

namespace android {

    static unsigned int mInstCount = 0;
    static inline unsigned int getSystemTime()
    {
        struct timeval tv;
        gettimeofday(&tv,0);
        return (unsigned int)(tv.tv_sec*1000+tv.tv_usec/1000);
    }

    const int INT_LEN = 30;
    inline void itoa (char *buf, int base, long long d)
    {
        char *p = buf;
        char *p1, *p2;
        //unsigned long ud = d;
        int divisor = 10;

        /* If %d is specified and D is minus, put `-' in the head.  */
        if (base == 'd' && d < 0)
        {
            *p++ = '-';
            buf++;

        }
        else if (base == 'x')
        divisor = 16;

        /* Divide UD by DIVISOR until UD == 0.  */
        do
        {
            int remainder = abs(d) % divisor;
            *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
            d = (abs(d) / divisor);
        }
        while (d);

        /* Terminate BUF.  */
        *p = 0;

        /* Reverse BUF.  */
        p1 = buf;
        p2 = p - 1;
        while (p1 < p2)
        {
            char tmp = *p1;
            *p1 = *p2;
            *p2 = tmp;
            p1++;
            p2--;
        }
    }


    HiPlayerMetadata::HiPlayerMetadata()
        : mUrl(NULL), mHandle((HI_HANDLE)NULL)
    {
        mParsedMetaData = false;
        mpMetadata_Ori = NULL;
        mMetaData.clear();
        mId = mInstCount++;
    }

    HiPlayerMetadata::~HiPlayerMetadata()
    {
        destroyMediaRetriever();
        mHandle = (HI_HANDLE)NULL;
        if (mUrl)
        {
            free(mUrl);
            mUrl = NULL;
        }
        mMetaData.clear();
    }

    status_t HiPlayerMetadata::setDataSource(
                const char *url, const KeyedVector<String8, String8> *headers)
    {
        if (!url)
        {
            return INVALID_OPERATION;
        }

        mUrl = strdup(url);

        if((HI_HANDLE)NULL == mHandle)
        {
            return createMediaRetriever();
        }

        return OK;
    }

    status_t HiPlayerMetadata::setDataSource(int fd,
                                                 int64_t offset, int64_t length)
    {
        char filePath[64];
        char dataSrcPath[HI_FORMAT_MAX_URL_LEN];
        char pathuse[HI_FORMAT_MAX_URL_LEN];
        char value[PROPERTY_VALUE_MAX] = {0};
        memset(filePath, 0, 64);
        memset(dataSrcPath, 0, HI_FORMAT_MAX_URL_LEN);
        memset(pathuse, 0, HI_FORMAT_MAX_URL_LEN);

        snprintf(filePath, 63, "/proc/%d/fd/%d", getpid(), fd);
        readlink(filePath, dataSrcPath, HI_FORMAT_MAX_URL_LEN);

        //set the file name and offset to stMedia
        snprintf(pathuse, HI_FORMAT_MAX_URL_LEN - 1,
            "%s%s%lld%s%lld%s%d",
            dataSrcPath, SEPARATE_SYMBOL_OFFSET, offset, SEPARATE_SYMBOL_LENGTH, length, SEPARATE_SYMBOL_FD, fd);

        mUrl = strdup(pathuse);
        if((HI_HANDLE)NULL == mHandle)
        {
            return createMediaRetriever();
        }

        return OK;
    }

    VideoFrame* HiPlayerMetadata::getFrameAtTime(int64_t timeUs, int option)
    {
        int t1 = getSystemTime();
        int i4KUI = 0;
        HI_CHAR value[PROP_VALUE_MAX];
        HI_FORMAT_THUMBNAIL_PARAM_S thumbParam;
        memset(&thumbParam, 0, sizeof(HI_FORMAT_THUMBNAIL_PARAM_S));
        thumbParam.thumbPixelFormat = HI_FORMAT_PIX_FMT_RGB565LE;
        if (property_get("persist.sys.display.4k2k", value, "0") > 0)
        {
            // 1--4k ui  0---not 4k
            i4KUI = atoi(value);
        }
        if (i4KUI)
        {
            thumbParam.thumbnailSize = 512;
        }
        else
        {
            thumbParam.thumbnailSize = 128;
        }
        thumbParam.thumbnailTimeMs = (timeUs + 500)/1000;

        if (HI_FAILURE == HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_THUMBNAIL, (HI_VOID *)&thumbParam)
            || thumbParam.width == 0
            || thumbParam.height == 0)
        {
            int t2 = getSystemTime();
            LOGE("===inst[%d] getFrameAtTime fail use %dms===", mId, t2-t1);

            return NULL;
        }

        VideoFrame *frame     = new VideoFrame;
        if(NULL == frame)
        {
            return NULL;
        }

        frame->mWidth         = thumbParam.width;
        frame->mHeight        = thumbParam.height;
        frame->mDisplayWidth  = thumbParam.width;
        frame->mDisplayHeight = thumbParam.height;
        frame->mSize          = thumbParam.lineSize[0] * thumbParam.height;
        frame->mRotationAngle = 0;

        frame->mData          = new uint8_t[frame->mSize];
        if(NULL == frame->mData)
        {
            delete frame;
            return NULL;
        }

        memcpy(frame->mData, thumbParam.frameData[0], frame->mSize);

        for (int i = 0; i < 4; i++)
        {
            if (NULL != thumbParam.frameData[i])
            {
                free(thumbParam.frameData[i]);
                thumbParam.frameData[i] = NULL;
            }
        }

        int t2 = getSystemTime();
        LOGI("===inst[%d] getFrameAtTime success use %dms===", mId, t2-t1);
        return frame;
    }

    MediaAlbumArt* HiPlayerMetadata::extractAlbumArt()
    {
        int t1 = getSystemTime();
        MediaAlbumArt *AlbumArt = NULL;
        HI_SVR_PLAYER_METADATA_S *pMetadata_Ori = HI_SVR_META_Create();
        if(NULL == pMetadata_Ori)
        {
            return NULL;
        }

        if (HI_FAILURE == HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_METADATA, (HI_VOID*)(pMetadata_Ori)))
        {
            int t2 = getSystemTime();
            LOGE("===inst[%d] extractAlbumArt fail use %dms===", mId, t2-t1);

            HI_SVR_META_Free(&pMetadata_Ori);
            return NULL;
        }

        for (size_t i= 0; i < pMetadata_Ori->u32KvpUsedNum; i++) {
            HI_U32 ValLen = pMetadata_Ori->pstKvp[i].u32ValueNum;
            HI_CHAR *Key = pMetadata_Ori->pstKvp[i].pszKey;
            if (HI_SVR_PLAYER_VALUE_CHARP == pMetadata_Ori->pstKvp[i].eValueType) {
                int KeySize = strlen(Key);
                int KeyPreLen = strlen(HiKeyID3Pic);
                int n = 0;
                for (;n < KeySize; n++)
                {
                    if ('/' == Key[n])
                    {
                        break;
                    }
                }

                if (n != KeySize && KeySize > KeyPreLen) {
                    //find the pic metadata
                    if (!strncmp(HiKeyID3Pic, Key, KeyPreLen)) {
                        AlbumArt = new MediaAlbumArt;
                        if(NULL == AlbumArt)
                        {
                            HI_SVR_META_Free(&pMetadata_Ori);
                            return NULL;
                        }

                        AlbumArt->mSize = ValLen;
                        AlbumArt->mData = new uint8_t[ValLen];
                        if(NULL == AlbumArt->mData)
                        {
                            HI_SVR_META_Free(&pMetadata_Ori);
                            delete AlbumArt;
                            return NULL;
                        }

                        memcpy(AlbumArt->mData, pMetadata_Ori->pstKvp[i].unValue.pszValue, ValLen);
                        break;
                    }
                }
            }
        }

        HI_SVR_META_Free(&pMetadata_Ori);

        int t2 = getSystemTime();
        LOGI("===inst[%d] extractAlbumArt success use %dms===", mId, t2-t1);

        return AlbumArt;
    }

    const char* HiPlayerMetadata::extractMetadata(int keyCode)
    {
        if (!mParsedMetaData)
        {
            mpMetadata_Ori = HI_SVR_META_Create();
            if(NULL == mpMetadata_Ori)
            {
                return NULL;
            }

            HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_METADATA, (HI_VOID*)(mpMetadata_Ori));
            mParsedMetaData = true;
            convertMetadata();
            HI_SVR_META_Free(&mpMetadata_Ori);
        }

        ssize_t index = mMetaData.indexOfKey(keyCode);
        if (index < 0)
        {
            return NULL;
        }

        return strdup(mMetaData.valueAt(index).string());
    }

    void HiPlayerMetadata::convertMetadata()
    {
        struct KeyMap {
            const char* from;
            int         to;
        };

        static const KeyMap kMap[] = {
            { HiKeyMIMEType,      METADATA_KEY_MIMETYPE },
            { HiKeyCDTrackNumber, METADATA_KEY_CD_TRACK_NUMBER },//0
            { HiKeyAlbum,         METADATA_KEY_ALBUM },
            { HiKeyArtist,        METADATA_KEY_ARTIST },
            { HiKeyAlbumArtist,   METADATA_KEY_ALBUMARTIST },
            { HiKeyAuthor,        METADATA_KEY_AUTHOR },
            { HiKeyComposer,      METADATA_KEY_COMPOSER },

            { HiKeyGenre,         METADATA_KEY_GENRE },//6
            { HiKeyTitle,         METADATA_KEY_TITLE },
            { HiKeyYear,          METADATA_KEY_YEAR },
            { HiKeyDate,          METADATA_KEY_YEAR },
            { HiKeyDuration,      METADATA_KEY_DURATION },
            { HiKeyTrackNum,      METADATA_KEY_NUM_TRACKS},

            { HiKeyAuthor,        METADATA_KEY_WRITER},//11
            { HiKeyMIMEType,      METADATA_KEY_MIMETYPE },
            { HiKeyAlbumArtist,   METADATA_KEY_ALBUMARTIST },
            { HiKeyDiscNumber,    METADATA_KEY_DISC_NUMBER},
            { HiKeyCompliation,   METADATA_KEY_COMPILATION},

            { HiKeyHasAudio,      METADATA_KEY_HAS_AUDIO},//16
            { HiKeyHasVideo,      METADATA_KEY_HAS_VIDEO},
            { HiKeyWidth,         METADATA_KEY_VIDEO_WIDTH},
            { HiKeyHeight,        METADATA_KEY_VIDEO_HEIGHT},
            { HiKeyBitrate,       METADATA_KEY_BITRATE},

            { HiKeyLanguage,      METADATA_KEY_TIMED_TEXT_LANGUAGES},//21
            { HiKeyIsDRM,         METADATA_KEY_IS_DRM},
            { HiKeyLocation,      METADATA_KEY_LOCATION},
            { HiKeyRotation,      METADATA_KEY_VIDEO_ROTATION}
        };

        static const size_t kNumMapEntries = sizeof(kMap) / sizeof(kMap[0]);


        HI_HANDLE _CharsetMgrHandler = (HI_HANDLE)NULL;
        HI_CHAR * ps8Out = NULL;
        HI_S32 s32CodeType = 0;//SVR_SUB_CODETYPE_UNKNOW;
        HI_S32 usedlen = 0;
        HI_S32 outlen = 0;
        HI_S32 ret = 0;
        HI_CHARSET_FUN_S * pstCharsetMgr = &g_stCharsetMgr_s;
        bool bCharsetMgrHdl = false;

        if(NULL != pstCharsetMgr &&
           NULL != pstCharsetMgr->Create &&
           NULL != pstCharsetMgr->Destroy)
        {
            ret = pstCharsetMgr->Create(&_CharsetMgrHandler, 0);
            if(ret != HI_SUCCESS)
                LOGV("fail to create charset mgr handler");
            else
                bCharsetMgrHdl = true;
        }

        for (size_t n = 0; n < kNumMapEntries; ++n)
        {
            for (size_t i= 0; i < mpMetadata_Ori->u32KvpUsedNum; i++)
            {
                const char *KeyCompare = kMap[n].from;
                char *Key = mpMetadata_Ori->pstKvp[i].pszKey;

                int KeyConvert = kMap[n].to;
                if (!strcmp(KeyCompare, Key))
                {
                    switch (mpMetadata_Ori->pstKvp[i].eValueType)
                    {
                        case HI_SVR_PLAYER_VALUE_CHARP:
                        {
                            if(bCharsetMgrHdl == true)
                            {
                                 ret = pstCharsetMgr->IdentStream(_CharsetMgrHandler, (HI_U8 *)mpMetadata_Ori->pstKvp[i].unValue.pszValue,
                                        strlen(mpMetadata_Ori->pstKvp[i].unValue.pszValue), 0, &s32CodeType);
                                 if(ret == HI_SUCCESS)
                                 {
                                      LOGV("charset CodeType : %d", s32CodeType);

                                      ps8Out = (HI_CHAR*)malloc(strlen(mpMetadata_Ori->pstKvp[i].unValue.pszValue) * 4 + 2);

                                      outlen = strlen(mpMetadata_Ori->pstKvp[i].unValue.pszValue)*4 + 2;

                                      ret = pstCharsetMgr->ConvStream(_CharsetMgrHandler, (HI_U8 *)ps8Out, &outlen,
                                                             (HI_U8 *)mpMetadata_Ori->pstKvp[i].unValue.pszValue,
                                                             strlen(mpMetadata_Ori->pstKvp[i].unValue.pszValue),
                                                             s32CodeType, 2, &usedlen);
                                      if(ret == HI_SUCCESS)
                                          mMetaData.add(KeyConvert, String8(ps8Out));
                                      else
                                      {
                                          LOGV("fail to convstream");
                                          mMetaData.add(KeyConvert, String8(mpMetadata_Ori->pstKvp[i].unValue.pszValue));
                                      }
                                 }
                                 else
                                 {
                                      LOGV("fail to ident stream");
                                      mMetaData.add(KeyConvert, String8(mpMetadata_Ori->pstKvp[i].unValue.pszValue));
                                 }
                            }
                            else
                            {
                                 LOGV("fail to create charset manager handler");
                                 mMetaData.add(KeyConvert, String8(mpMetadata_Ori->pstKvp[i].unValue.pszValue));
                            }

                            if(ps8Out != NULL)
                            {
                                free(ps8Out);
                                ps8Out = NULL;
                            }
                            break;
                        }
                        case HI_SVR_PLAYER_VALUE_S32:
                        {
                            int ValueInt = mpMetadata_Ori->pstKvp[i].unValue.s32Value;
                            char ConvIntBuf[INT_LEN];
                            memset(ConvIntBuf, 0, INT_LEN);
                            itoa(ConvIntBuf, 'd', ValueInt);
                            mMetaData.add(KeyConvert, String8(ConvIntBuf));
                            break;
                        }
                        case HI_SVR_PLAYER_VALUE_S64:
                        {
                            HI_S64 ValueLongLong = mpMetadata_Ori->pstKvp[i].unValue.s64Value;
                            char ConvIntBuf[INT_LEN];
                            memset(ConvIntBuf, 0, INT_LEN);
                            itoa(ConvIntBuf, 'd', ValueLongLong);
                            mMetaData.add(KeyConvert, String8(ConvIntBuf));
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
        if(bCharsetMgrHdl == true)
        {
            if(_CharsetMgrHandler != (HI_HANDLE)NULL)
            {
                pstCharsetMgr->Destroy(_CharsetMgrHandler);
                _CharsetMgrHandler = (HI_HANDLE)NULL;
            }
            bCharsetMgrHdl = false;
        }
    }

    status_t HiPlayerMetadata::createMediaRetriever()
    {
        int t1 = getSystemTime();
        HI_HANDLE hPlayer = (HI_HANDLE)NULL;
        HI_SVR_PLAYER_PARAM_S s_stParam = {
            0,
            3,
            0,
            0,
            1920,
            1080,
            100,
            0,
            0,
        };

        if (HI_FAILURE == HiMediaSystem::initDevice())
        {
            LOGE("Init device failed");
            return UNKNOWN_ERROR;
        }

        if (HI_FAILURE == HiMediaSystem::initPlayer())
        {
            LOGE("Init Player failed");
            return UNKNOWN_ERROR;
        }

        if (HI_FAILURE == HiMediaSystem::initCharset())
        {
            LOGE("Init char set failed");
            return UNKNOWN_ERROR;
        }

        HI_SVR_PLAYER_MEDIA_S stMedia;
        memset(&stMedia, 0, sizeof(stMedia));
        snprintf(stMedia.aszUrl, sizeof(stMedia.aszUrl), "%s", mUrl);

        if (HI_FAILURE == HI_SVR_PLAYER_CreateMetaRetriever(&s_stParam, &stMedia, &hPlayer))
        {
            int t2 = getSystemTime();
            LOGE("===inst[%d] createMediaRetriever fail use %dms url [%s]===", mId, t2-t1, mUrl);
#ifndef HIMEDIA_NOT_DEINIT_RESOURCE
            HiMediaSystem::deInitCharset();
            HiMediaSystem::deInitPlayer();
            HiMediaSystem::deInitDevice();
#endif
            return UNKNOWN_ERROR;
        }

        mHandle = hPlayer;

        int t2 = getSystemTime();
        LOGI("===inst[%d] createMediaRetriever use %dms url[%s]===", mId, t2-t1, mUrl);
        return NO_ERROR;
    }

    status_t HiPlayerMetadata::destroyMediaRetriever()
    {
        int t1 = getSystemTime();

        if(mHandle)
        {
            HI_SVR_PLAYER_DestroyMetaRetriever(mHandle);
#ifndef HIMEDIA_NOT_DEINIT_RESOURCE
            HiMediaSystem::deInitCharset();
            HiMediaSystem::deInitPlayer();
            HiMediaSystem::deInitDevice();
#endif
            mHandle = NULL;
        }

        int t2 = getSystemTime();
        LOGI("===inst[%d] destroyMediaRetriever use %dms===", mId, t2-t1);
        return NO_ERROR;
    }
};
