// HiBDInfo.cpp: implementation of the HiBDInfo class.
//
//////////////////////////////////////////////////////////////////////
#define LOG_NDEBUG 1
#define LOG_TAG "HiBDInfo"
#include <utils/Log.h>
#include <utils/String8.h>
#include <sys/times.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "HiBDInfo.h"
#include "HiBDInvoke.h"

#define BUFFSIZE_PATH           2048
#define PLAYLIST_MIN_LENGTH     30
#define TIME_SYSTEM             60
#define TIME_CONVERSION_S       90000
#define TIME_CONVERSION_MS      90
#define DEFAULT_ANGLE           0
#define BD_INIT_PREFIX_LENGTH   11

#define LOGE ALOGE
#define LOGV ALOGV
#define LOGW ALOGW
#define LOGI ALOGI
#define LOGD ALOGD

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HiBDInfo::HiBDInfo():
    titleNumber(0)
{
    LOGV("%s", __FUNCTION__);
}

HiBDInfo::~HiBDInfo()
{
    LOGV("%s", __FUNCTION__);
    closeBluray();
}

int HiBDInfo::invoke(const Parcel & p_request, Parcel * p_reply)
{
    LOGV("%s", __FUNCTION__);

    status_t _ret = OK;
    int _s32Ret = 0;

    Parcel * _request = (Parcel *)&p_request;
    Parcel * _reply   = p_reply;

    if (NULL == _request || NULL == _reply)
    {
        return -1;
    }

    String16 * _pstr16;

    bd_cmd_type_e _cmdType = (bd_cmd_type_e)_request->readInt32();

    LOGV("invoke cmd [%d]", _cmdType);

    switch (_cmdType)
    {
        case BD_CMD_OPEN_BLURAY:
            {
                String16 _requestArg = _request->readString16();
                char _bdPath[BUFFSIZE_PATH] = {0};
                if (_requestArg.size() > 0)
                {
#ifdef ANDROID_VERSION_4_0
                    utf16_to_utf8(_requestArg.string(), _requestArg.size(), _bdPath);
#else
                    int _size = utf8_length_from_utf16(_requestArg.string(), _requestArg.size()) + 1;
                    utf16_to_utf8(_requestArg.string(), _requestArg.size(), _bdPath, _size);
#endif
                }
                int _replyArg = openBluray(_bdPath);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_CLOSE_BLURAY:
            {
                int _replyArg = closeBluray();
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_CHECK_DISC_INFO:
            {
                int _replyArg = checkDiscInfo();
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_GET_TITLE_NUMBER:
            {
                int _replyArg = getTitleNumber();
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_GET_CHAPTER_NUMBER:
            {
                int _requestArg = _request->readInt32();
                int _replyArg = getChapterNumberByTitleId(_requestArg);
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_GET_PLAYLIST:
            {
                int _requestArg = _request->readInt32();
                int _replyArg = getPlaylistByTitleId(_requestArg);
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_GET_TITLE:
            {
                int _requestArg = _request->readInt32();
                int _replyArg = getTitleIdByPlaylist(_requestArg);
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_CHECK_3D:
            {
                int _replyArg = checkBluray3D();
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_GET_POSTER:
            {
                char *post_buff = NULL;
                int  post_size = 0;
                int _replyArg = getPoster(&post_buff, &post_size);

                _reply->writeInt32(_replyArg);

                if (!_replyArg)
                {
                    _reply->writeInt32(post_size);
                    //note: this is not a mistake, rewrite for matching java Parcel::readByteArray
                    _reply->writeInt32(post_size);
                    _reply->write(post_buff, post_size);
                }

                freePoster();
            }
            break;

        case BD_CMD_GET_DEFAULT_PLAYLIST:
            {
                int _replyArg = getDefaultPlaylist();
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_GET_DEFAULT_TITLE:
            {
                int _replyArg = getDefaultTitleId();
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_GET_CHAPTER_POSITION:
            {
                int _requestArg1 = _request->readInt32();
                int _requestArg2 = _request->readInt32();
                int _replyArg = getChapterPosition(_requestArg1, _requestArg2);
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_GET_CUR_CHAPTER:
            {
                int _requestArg1 = _request->readInt32();
                int _requestArg2 = _request->readInt32();
                int _replyArg = getCurChapterId(_requestArg1, _requestArg2);
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_GET_DURATION:
            {
                int _requestArg = _request->readInt32();
                int _replyArg = getDurationByTitleId(_requestArg);
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_replyArg);
            }
            break;

        case BD_CMD_GET_SUBTITLE_LANGUAGE:
            {
                String16 * _pstr16;
                char _lang[4];
                int _titleId = getDefaultTitleId();
                BLURAY_TITLE_INFO * _titleInfo = bd_get_title_info(m_bd, _titleId, DEFAULT_ANGLE);
                int _subtitleNum = _titleInfo->clips[0].pg_stream_count;
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_subtitleNum);
                for (int i = 0; i < _subtitleNum; i++)
                {
                    memcpy(_lang, _titleInfo->clips[0].pg_streams[i].lang, sizeof(_titleInfo->clips[0].pg_streams[i].lang));
                    _pstr16 = new String16(_lang, strlen(_lang));
                    _reply->writeString16(*_pstr16);
                }
            }
            break;

        case BD_CMD_GET_AUDIO_TRACK_LANGUAGE:
            {
                String16 * _pstr16;
                char _lang[4];
                int _titleId = getDefaultTitleId();
                BLURAY_TITLE_INFO * _titleInfo = bd_get_title_info(m_bd, _titleId, DEFAULT_ANGLE);
                int _audioTrackNum = _titleInfo->clips[0].audio_stream_count;
                _reply->writeInt32(_s32Ret);
                _reply->writeInt32(_audioTrackNum);
                for (int i = 0; i < _audioTrackNum; i++)
                {
                    memcpy(_lang, _titleInfo->clips[0].audio_streams[i].lang, sizeof(_titleInfo->clips[0].audio_streams[i].lang));
                    _pstr16 = new String16(_lang, strlen(_lang));
                    _reply->writeString16(*_pstr16);
                }
            }
            break;

        default:
            break;
    }
    return 0;
}

int HiBDInfo::openBluray(const char * p_bdPath)
{
    LOGV("%s", __FUNCTION__);

    if (p_bdPath == NULL)
    {
        LOGV("bd Path is null");
        return -1;
    }

    LOGV("bd Path is %s", p_bdPath);

    if (m_bd != NULL)
    {
        LOGV("bd is already opened, close first");
        closeBluray();
    }

    mLock.lock();

    m_bd = bd_open(p_bdPath, NULL);
    if (NULL == m_bd)
    {
        LOGE("bd_open failed");
        mLock.unlock();
        return -1;
    }
    else
    {
        LOGV("bd_open successed");
    }

    return 0;
}

int HiBDInfo::closeBluray()
{
    LOGV("%s", __FUNCTION__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    bd_close(m_bd);
    m_bd = NULL;
    mLock.unlock();

    return 0;
}

int HiBDInfo::checkDiscInfo()
{
    LOGV("%s", __FUNCTION__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    const BLURAY_DISC_INFO * _discInfo;
    _discInfo = bd_get_disc_info(m_bd);

    if (!_discInfo)
    {
        LOGE("bd_get_disc_info failed");
        return -1;
    }

    if (!_discInfo->bluray_detected)
    {
        LOGE("bluRay not detected");
        return -1;
    }

    /* AACS */
    /*if (_discInfo->aacs_detected && !_discInfo->aacs_handled)
    {
        if (!_discInfo->libaacs_detected)
        {
            LOGE("Media stream encrypted with AACS, install and configure libaacs");
        }
        else
        {
            LOGE("Your libaacs can't decrypt this media");
        }
        return -1;
    }*/

    /* BD+ */
    /*if (_discInfo->bdplus_detected && !_discInfo->bdplus_handled)
    {
        LOGE("Unable to decrypt BD+ encrypted media");
        return -1;
    }*/

    return 0;
}

int HiBDInfo::getTitleNumber()
{
    LOGV("%s", __FUNCTION__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    int _titleNumber = bd_get_titles(m_bd, TITLES_RELEVANT, PLAYLIST_MIN_LENGTH);

    LOGV("title number is %d", _titleNumber);

    if (_titleNumber < 1)
    {
        LOGE("bd_get_titles failed");
        titleNumber = 0;
        return -1;
    }
    else
    {
        LOGV("bd_get_titles successed");
        titleNumber = _titleNumber;
    }

    return _titleNumber;
}

int HiBDInfo::getChapterNumberByTitleId(int p_titleId)
{
    LOGV("%s", __FUNCTION__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    if (titleNumber == 0 || p_titleId >= titleNumber)
    {
        LOGE("param p_titleId not legal");
        return -1;
    }

    int _chapterNumber = 0;

    BLURAY_TITLE_INFO * _titleInfo = bd_get_title_info(m_bd, p_titleId, DEFAULT_ANGLE);
    if(_titleInfo == NULL)
    {
        LOGE("_titleInfo is NULL");
        return -1;
    }
    _chapterNumber = _titleInfo->chapter_count;
    bd_free_title_info(_titleInfo);

    LOGV("chapter number is %d", _chapterNumber);

    return _chapterNumber;
}

int HiBDInfo::getPlaylistByTitleId(int p_titleId)
{
    LOGV("%s", __FUNCTION__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    if (titleNumber == 0 || p_titleId >= titleNumber)
    {
        LOGE("param p_titleId not legal");
        return -1;
    }

    int _playlist = -1;

    BLURAY_TITLE_INFO * _titleInfo = bd_get_title_info(m_bd, p_titleId, DEFAULT_ANGLE);
    if(_titleInfo == NULL)
    {
        LOGE("_titleInfo is NULL");
        return -1;
    }
    _playlist = _titleInfo->playlist;
    bd_free_title_info(_titleInfo);

    LOGV("playlist is %05d", _playlist);

    return _playlist;
}

int HiBDInfo::getTitleIdByPlaylist(int p_playlist)
{
    LOGV("%s", __FUNCTION__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    int _titleId = -1;

    int _titleNumber = getTitleNumber();

    for (int i = 0; i < _titleNumber; i++)
    {
        BLURAY_TITLE_INFO * _titleInfo = bd_get_title_info(m_bd, i, 0);
        if(_titleInfo == NULL)
        {
            LOGE("_titleInfo is NULL");
            return -1;
        }
        if ((int)_titleInfo->playlist == p_playlist)
        {
            _titleId = _titleInfo->idx;
        }

        bd_free_title_info(_titleInfo);
    }

    return _titleId;
}


int HiBDInfo::checkBluray3D()
{
    LOGV("%s", __FUNCTION__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    int _result = 0;

    CLPI_CL* cl = NULL;
    cl = bd_get_ext_clpi(m_bd, 0, 0);
    if(cl)
    {
        _result = 1;
        bd_free_clpi(cl);
    }

    return _result;
}

int HiBDInfo::getDefaultPlaylist()
{
    LOGV("%s", __FUNCTION__);

    return getPlaylistByTitleId(getDefaultTitleId());
}

int HiBDInfo::getPoster(char** pBuffer, int* pSize)
{
    int ret = 0;

    LOGV("%s, Line: %d", __FUNCTION__, __LINE__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    BLURAY_POSTER_INFO *pPosterInfo = NULL;

    ret = bd_get_poster(m_bd, &pPosterInfo);

    if (ret)
    {
        LOGE("get poster is fail");
        return -1;
    }

    *pBuffer = pPosterInfo->buffer;
    *pSize = pPosterInfo->size;
    return 0;
}

int HiBDInfo::freePoster()
{
    int ret = 0;

    LOGV("%s, Line: %d", __FUNCTION__, __LINE__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    ret = bd_free_poster(m_bd);

    if (ret)
    {
        LOGE("free poster fail");
        return -1;
    }

    return 0;
}

int HiBDInfo::getDefaultTitleId()
{
    LOGV("%s", __FUNCTION__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    int _defaultTitleId = -1;
    int _defaultTitle3DId = -1;
    int _titleNumber = getTitleNumber();

    /* get longest titleId */
    uint64_t _duration = 0;
    for (int i = 0; i < _titleNumber; i++)
    {
        BLURAY_TITLE_INFO * _titleInfo = bd_get_title_info(m_bd, i, 0);
        if(_titleInfo == NULL)
        {
            LOGE("_titleInfo is NULL");
            return -1;
        }
        if (_titleInfo->duration >= _duration)
        {
            _defaultTitleId = _titleInfo->idx;
            _duration = _titleInfo->duration;
            bd_select_title(m_bd,_defaultTitleId);
            char *sub_ts = bd_get_sub_ts_path(m_bd, 0, 0);
            if(sub_ts != NULL)
            {
                _defaultTitle3DId = _defaultTitleId;
                free(sub_ts);
            }
        }

        bd_free_title_info(_titleInfo);
    }
    if(_defaultTitle3DId != -1)
        return _defaultTitle3DId;
    return _defaultTitleId;
}

int HiBDInfo::getChapterPosition(int p_titleId, int p_chapterId)
{
    LOGV("%s", __FUNCTION__);
    int _position = -1;

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    if (titleNumber == 0 || p_titleId >= titleNumber)
    {
        LOGE("param p_titleId not legal");
        return -1;
    }

    // ¼ì²échapterId

    BLURAY_TITLE_INFO * _titleInfo = bd_get_title_info(m_bd, p_titleId, DEFAULT_ANGLE);
    if(_titleInfo == NULL)
    {
        LOGE("_titleInfo is NULL");
        return -1;
    }

    if (p_chapterId < _titleInfo->chapter_count)
    {
        _position = _titleInfo->chapters[p_chapterId].start / TIME_CONVERSION_MS;
    }

    return _position;
}

int HiBDInfo::getCurChapterId(int p_titleId, int p_position)
{
    LOGV("%s", __FUNCTION__);
    int i = 0;
    int _chapterId = 0;

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    if (titleNumber == 0 || p_titleId >= titleNumber)
    {
        LOGE("param p_titleId not legal");
        return -1;
    }

    BLURAY_TITLE_INFO * _titleInfo = bd_get_title_info(m_bd, p_titleId, DEFAULT_ANGLE);
    if(_titleInfo == NULL)
    {
        LOGE("_titleInfo is NULL");
        return -1;
    }
    for (i = 0; i < (int)_titleInfo->chapter_count; i++)
    {
        if (p_position >= (int)_titleInfo->chapters[i].duration / TIME_CONVERSION_MS)
        {
            _chapterId++;
            p_position -= (int)_titleInfo->chapters[i].duration / TIME_CONVERSION_MS;
        }
        else
        {
            break;
        }
    }

    return _chapterId;
}

int HiBDInfo::getDurationByTitleId(int p_titleId)
{
    LOGV("%s", __FUNCTION__);

    if (NULL == m_bd)
    {
        LOGE("bd not open");
        return -1;
    }

    if (titleNumber == 0 || p_titleId >= titleNumber)
    {
        LOGE("param p_titleId not legal");
        return -1;
    }

    BLURAY_TITLE_INFO * _titleInfo = bd_get_title_info(m_bd, p_titleId, 0);
    if(_titleInfo == NULL)
    {
        LOGE("_titleInfo is NULL");
        return -1;
    }
    int _duration = _titleInfo->duration / TIME_CONVERSION_MS;
    bd_free_title_info(_titleInfo);

    return _duration;
}

int HiBDInfo::checkDiscInfo(const char * p_bdPath)
{
    LOGV("%s", __FUNCTION__);

    if (p_bdPath == NULL)
    {
        LOGV("bd Path is null");
        return -1;
    }

    BLURAY * _bd = bd_open(p_bdPath, NULL);
    if (NULL == _bd)
    {
        LOGE("bd_open failed");
        return -1;
    }
    else
    {
        LOGV("bd_open successed");
    }

    const BLURAY_DISC_INFO * _discInfo;
    _discInfo = bd_get_disc_info(_bd);

    if (!_discInfo)
    {
        LOGE("bd_get_disc_info failed");
        bd_close(_bd);
        return -1;
    }

    if (!_discInfo->bluray_detected)
    {
        LOGE("bluRay not detected");
        bd_close(_bd);
        return -1;
    }

    /* AACS */
    /*if (_discInfo->aacs_detected && !_discInfo->aacs_handled)
    {
        if (!_discInfo->libaacs_detected)
        {
            LOGE("Media stream encrypted with AACS, install and configure libaacs");
        }
        else
        {
            LOGE("Your libaacs can't decrypt this media");
        }
        bd_close(_bd);
        return -1;
    }*/

    /* BD+ */
    /*if (_discInfo->bdplus_detected && !_discInfo->bdplus_handled)
    {
        LOGE("Unable to decrypt BD+ encrypted media");
        bd_close(_bd);
        return -1;
    }*/

    return 0;
}
