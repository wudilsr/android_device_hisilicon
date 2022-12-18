package com.HiMediaSample;

public class GlobalDef
{
    static final String     LOG_TAG = "HiMediaTest";
    static final int        MAX_MESSAGE_LEN = 200;
    static final int        MEDIA_INFO_NOT_SUPPORT = 1004;
    static final int        MEDIA_INFO_FIRST_FRAME_TIME = 1010;
    static final int        MEDIA_INFO_BUFFER_DOWNLOAD_FIN = 1009;
    static final int        MEDIA_INFO_AUDIO_FAIL = 1000;
    static final int        MEDIA_INFO_VIDEO_FAIL = 1001;
    static final int        MEDIA_INFO_NETWORK = 1002;
    static final int        NETWORK_STATUS_CONNECT_FAIL = 1;
    static final int        NETWORK_STATUS_CONNECT_TIMEOUT = 2;
    static final int        NETWORK_STATUS_CONNECT_NOTFOUND = 4;
    static final int        NETWORK_STATUS_CONNECT_DISCONNECT = 3;
    static final int        INVOKE_SET_HLS_STREAM = 305;
    static final int        INVOKE_SET_VIDEO_ZORDER = 314;
    static final int        INVOKE_GET_HLS_STREAM_NUM = 300;
    static final int        INVOKE_GET_HLS_STREAM_INFO = 302;
    static final int        INVOKE_GET_HLS_SEG_INFO = 303;
    static final int        INVOKE_GET_HLS_DETAIL_INFO = 304;
    static final int        INVOKE_GET_M3U9_INFO = 320;
    static final int        INVOKE_SET_USER_AGENT = 315;
    static final int        HIMEDIA_TEST_SUCCESS = 0;
    static final int        HIMEDIA_TEST_FAIL = 1;
    static final int        WINDOW_MODE_FREEZE = 0;
    static final int        WINDOW_MODE_BLACK = 1;
    static final int        WINDOW_MODE_INVALID = 2;
}

class HlsNumObject
{
        public int HlsNum;
}
