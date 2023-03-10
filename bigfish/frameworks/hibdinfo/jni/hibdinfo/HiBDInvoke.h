#ifndef _ANDROID_HIBDPLAYER_INVOKE_H_
#define _ANDROID_HIBDPLAYER_INVOKE_H_

typedef enum
{
    BD_CMD_OPEN_BLURAY = 1001,
    BD_CMD_CLOSE_BLURAY = 1002,
    BD_CMD_CHECK_DISC_INFO = 1003,
    BD_CMD_GET_TITLE_NUMBER = 1011,
    BD_CMD_GET_CHAPTER_NUMBER = 1012,
    BD_CMD_GET_PLAYLIST = 1013,
    BD_CMD_GET_DEFAULT_PLAYLIST = 1014,
    BD_CMD_GET_CHAPTER_POSITION = 1015,
    BD_CMD_GET_DEFAULT_TITLE = 1016,
    BD_CMD_GET_TITLE = 1017,
    BD_CMD_GET_SUBTITLE_LANGUAGE = 1018,
    BD_CMD_GET_AUDIO_TRACK_LANGUAGE = 1019,
    BD_CMD_GET_CUR_CHAPTER = 1020,
    BD_CMD_GET_DURATION = 1021,
    BD_CMD_CHECK_3D = 1022,
    BD_CMD_GET_POSTER = 1023,
} bd_cmd_type_e;

#endif // !defined(_ANDROID_HIBDPLAYER_INVOKE_H_)
