package com.hisilicon.android.videoplayer.control.base;

public class Constant
{
    public static final String BD_PREFIX = "bluray:";

    public static final String DVD_PREFIX = "dvd:";

    public static final String SPF_FILENAME = "MovieProgress";

    public static final String INDEX_BDMV = "/BDMV/index.bdmv";

    public static final class Timer
    {
        public static final int TIMER_ID_UPDATE = 1;

        public static final int TIMER_ID_HIDE_CONTROLLER = 2;

        public static final int TIMER_ID_LOAD_TIMEOUT = 3;

        public static final int TIMER_ID_HIDE_DIALOG = 4;

        public static final int TIMER_DELAY_UPDATE = 1000;

        public static final int TIMER_DELAY_HIDE_CONTROLLER = 5000;

        public static final int TIMER_DELAY_LOAD_TIMEOUT = 10000;

        public static final int TIMER_DELAY_HIDE_DIALOG = 5000;

        public static final int TIMER_PERIOD_UPDATE = 1000;
    }

    public static final class KeyCode
    {
        public static final int KEYCODE_MEDIA_SUBTITLE = 1179;

        public static final int KEYCODE_MEDIA_AUDIO = 1185;

        public static final int KEYCODE_MEDIA_PREV = 92;

        public static final int KEYCODE_MEDIA_NEXT = 93;

        public static final int KEYCODE_MEDIA_INFO = 165;

        public static final int KEYCODE_MEDIA_MUTE = 164;

        public static final int KEYCODE_MEDIA_SEEK = 1180;
    }

    public static final class Time
    {
        public static final int TIME_REWIND_FORWARD = 30000;

        public static final int TIME_PREV = 1000;
    }

    public static final class SubtitleSetting
    {
        public static final int SUBTITLE_DISABLE = 0;

        public static final int SUBTITLE_SELECT = 1;

        public static final int SUBTITLE_TIME_SYNC = 2;

        public static final int SUBTITLE_FONT_SIZE = 3;

        public static final int SUBTITLE_FONT_POSITION = 4;

        public static final int MAX_VALUE_TIME_SYNC = 1000;

        public static final int MAX_VALUE_FONT_SIZE = 50;
    }

    public static final class Button
    {
        public static final int YES = -1;

        public static final int NO = -2;
    }
}
