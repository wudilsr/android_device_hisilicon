package com.hisilicon.android.videoplayer.util;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

public class Constants
{
    public static final int LIST_MODE = 0;

    public static final int POSTER_MODE = 2;

    public static final int THUMBNAIL_MODE = 1;

    public static final int PRE_SCAN_MODE = 3;

    public static final int ORDER_BY_NAME = 0;

    public static final int ORDER_BY_SIZE = 1;

    public static final int ORDER_BY_CLICKRATE = 2;

    public static final int ORDER_BY_ADDTIME = 3;

    public static final int ORDER_BY_PLAYEDTIME = 4;

    public final static int SCREEN_FULL = 0;

    public final static int SCREEN_DEFAULT = 1;

    public final static int CTRLBAR_HIDE_TIME = 5000;

    public final static int DIALOG_SHOW = 5000;

    public final static int VIEW_SHOW = 5000;

    public final static int NAME_SIZE_HIDE_TIME = 5000;

    public final static int MIN_SEEK = 1;

    public final static int SORT_NAME = 0;

    public final static int SORT_SIZE = 1;

    public final static int SORT_TIME = 2;

    public static String MARK_DB_NAME = "videoplayer.db";

    public static int VERSION = 1;

    public static final String TABLE_VIDEO = "video";
    public static final String VIDEO_BOOKMARK  = "video_bookmark";
    public static final String VIDEO_PLAYLISTS = "video_playlists";
    public static final String VIDEO_MAP = "video_playlists_map";
    public static final String TRIGGER_VIDEO_CLEANUP = "video_playlists_cleanup";

    public static Object objLock = new Object();
    private static SQLiteDatabase _db;

    public static SQLiteDatabase getDB(Context context)
    {
        SQLiteDatabase r = null;

        synchronized (Constants.objLock){
            if ((Constants._db == null) || !Constants._db.isOpen())
            {
                try
                {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                Constants._db = Common.getDataBase(context);
                if ((Constants._db == null) || !Constants._db.isOpen())
                {}
            }

            r = Constants._db;
        }

        return r;
    }

    public static void setDB(SQLiteDatabase vdb)
    {
        synchronized (Constants.objLock){
            Constants._db = vdb;
        }
    }

    public static final int TV_INFO = 165;

    public static final int TV_SUB = 1179;

    public static final int TV_F1 = 131;

    public static final int TV_F2 = 132;

    public static final int TV_F3 = 133;

    public static final int TV_F4 = 134;

    public static final int TV_FAV = 1177;

    public static final int TV_SEEK = 1180;

    public static final int TV_PLAY = 85;

    public static final int TV_FORWARD = 90;

    public static final int TV_REWIND = 89;

    public static final int TV_STOP = 86;

    public static final int TV_DEL = 67;

    public static final int TV_PAGEUP = 92;

    public static final int TV_PAGEDOWN = 93;

    public static final int TV_SEARCH = 84;

    public static final int TV_REPEAT = 67;

    public static final int ALLNOCYCLE = 0;

    public static final int ALLCYCLE = 1;

    public static final int ONECYCLE = 2;

    public static final int ONENOCYCLE = 3;

    public static final int RANDOM = 4;

    public static String CONTENT_URI = "content://com.android.mysetting/item";

    public static int CONTINUE_PLAYER_FLAG = 1;

    public static final String VALUE = "VALUE";

    public static final int showMediaController = 1;

    public static final int hideMediaController = 2;

    public static final int switchSubtitle = 3;

    public static final int switchAudioTrack = 4;

    public static final int doSeek = 5;

    public static final int timeMax = 1000;

    public static final String SHARED = "shared";

    public static final int FORWARD = 200;

    public static final int REWIND = 201;

    public static final int MUTE = 4;

    public static final int SET_TRACK = 12;

    public static final int GET_TRACK = 205;

    public static final int SET_CHANNAL = 6;

    public static final int GET_PROGRAM = 206;

    public static final int SET_SUB_ID = 101;

    public static final int GET_SUB_ID = 102;

    public static final int SUB_INFO = 103;

    public static final int SUB_TYPE = 139;

    public static final int SUB_FONT_SIZE = 104;

    public static final int SUB_FONT_POSITION = 106;

    public static final int SUB_FONT_VERTICAL = 110;

    public static final int SUB_FONT_COLOR = 114;

    public static final int SUB_FONT_BACKCOLOR = 116;

    public static final int SUB_FONT_ALIGNMENT = 112;

    public static final int SUB_FONT_SHADOW = 118;

    public static final int SUB_FONT_HOLLOW = 120;

    public static final int SUB_FONT_SPACE = 122;

    public static final int SUB_FONT_LINESPACE = 124;

    public static final int SET_SUB_FONT_ENCODE = 128;

    public static final int GET_SUB_FONT_ENCODE = 129;

    public static final int SUB_TIME_SYNC = 130;

    public static final int SUB_FONT_STYLE = 133;

    public static final int SUB_FILE = 132;

    public static final int SUB_DISABLE = 135;

    public static final String STARTVIDEO = "com.hisilicon.android.videoplayer.video";

    public static final String ISVIDEOPLAYING = "SHOW_HIDE_FLAG";

    public static final int FROMPLAYLIST = 0;

    public static final int FROMFILEM = 1;

    public static final String ACTION = "com.hisilicon.android.videoplayer.listservice";
}
