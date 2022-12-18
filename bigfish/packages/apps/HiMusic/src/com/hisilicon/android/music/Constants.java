package com.hisilicon.android.music;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

/**
 * The class of app costants.
 */
public class Constants {
    /* List mode */
    public static final int LIST_MODE = 0;
    /* Poster mode */
    public static final int POSTER_MODE = 2;
    /* Thumbnail mode */
    public static final int THUMBNAIL_MODE = 1;
    /* Preview mode */
    public static final int PRE_SCAN_MODE = 3;
    /* Sort by name */
    public static final int ORDER_BY_NAME = 0;
    /* Sort by size */
    public static final int ORDER_BY_SIZE = 1;
    /* Sort by clickrate */
    public static final int ORDER_BY_CLICKRATE = 2;
    /* Sort by added time */
    public static final int ORDER_BY_ADDTIME = 3;
    /* Sort by play time */
    public static final int ORDER_BY_PLAYEDTIME = 4;
    /* Full screen */
    public final static int SCREEN_FULL = 0;
    /* default screen */
    public final static int SCREEN_DEFAULT = 1;
    /* Display interval of The control bar */
    public final static int CTRLBAR_HIDE_TIME = 5000;
    /* Display duration of Dialog */
    public final static int DIALOG_SHOW = 5000;
    /* Display duration of Views */
    public final static int VIEW_SHOW = 5000;
    /* Display duration of vedio name and size */
    public final static int NAME_SIZE_HIDE_TIME = 5000;
    /* the minimal length of seek */
    public final static int MIN_SEEK = 1;
    /* Sort by name */
    public final static int SORT_NAME = 0;
    /* Sort by size */
    public final static int SORT_SIZE = 1;
    /* Sort by time */
    public final static int SORT_TIME = 2;
    /* the name of database */
    public static String MARK_DB_NAME = "hisi_media.db";
    /* the version of database */
    public static int VERSION = 1;

    public static final String TABLE_VIDEO = "video";
    public static final String VIDEO_BOOKMARK = "video_bookmark";
    public static final String VIDEO_PLAYLISTS = "video_playlists";
    public static final String VIDEO_MAP = "video_playlists_map";
    public static final String TRIGGER_VIDEO_CLEANUP = "video_playlists_cleanup";

    public static Object objLock = new Object();
    private static SQLiteDatabase _db;

    public static void setDB(SQLiteDatabase vdb) {
        synchronized (Constants.objLock) {
            Constants._db = vdb;
        }
    }

    /* key value of TV INFO */
    public static final int TV_INFO = 165;
    /* key value of TV Subtitle */
    public static final int TV_SUB = 1179;
    /* key value of TV F1 */
    public static final int TV_F1 = 131;
    /* key value of TV F2 */
    public static final int TV_F2 = 132;
    /* key value of TV F3 */
    public static final int TV_F3 = 133;
    /* key value of TV F4 */
    public static final int TV_F4 = 134;
    /* key value of TV FAV */
    public static final int TV_FAV = 1177;
    /* key value of TV SEEK */
    public static final int TV_SEEK = 1180;
    /* key value of TV PLAY */
    public static final int TV_PLAY = 85;
    /* key value of TV FORWARD */
    public static final int TV_FORWARD = 90;
    /* key value of TV REWIND */
    public static final int TV_REWIND = 89;
    /* key value of TV STOP */
    public static final int TV_STOP = 86;
    /* key value of TV DEL */
    public static final int TV_DEL = 67;
    /* key value of TV PageUp */
    public static final int TV_PAGEUP = 92;
    /* key value of TV PageDown */
    public static final int TV_PAGEDOWN = 93;
    /* key value of TV Search */
    public static final int TV_SEARCH = 84;
    /* key value of TV REPEAT */
    public static final int TV_REPEAT = 67;
    /* all repeat */
    public static final int ALLNOCYCLE = 0;
    /* order */
    public static final int ALLCYCLE = 1;
    /* Single repetition */
    public static final int ONECYCLE = 2;
    /* once */
    public static final int ONENOCYCLE = 3;
    /* shuffle */
    public static final int RANDOM = 4;
    public static String CONTENT_URI = "content://com.android.mysetting/item";
    /* Resume broken play */
    public static int CONTINUE_PLAYER_FLAG = 1;
    public static final String VALUE = "VALUE";

    public static final int showMediaController = 1;
    public static final int hideMediaController = 2;
    /* the max value of time adjustment */
    public static final int timeMax = 1000;
    /* temp file name */
    public static final String SHARED = "shared";
    /* Fast Forward */
    public static final int FORWARD = 200;
    /* Rewind */
    public static final int REWIND = 201;
    /* Mute */
    public static final int MUTE = 4;
    /* set audio track */
    public static final int SET_TRACK = 12;
    /* get all the audio track */
    public static final int GET_TRACK = 205;
    /* set audio channel */
    public static final int SET_CHANNAL = 6;
    /* get program */
    public static final int GET_PROGRAM = 206;
    /* set cur subtitle ID */
    public static final int SET_SUB_ID = 101;
    /* get cur subtitle ID */
    public static final int GET_SUB_ID = 102;
    /* get subtile info */
    public static final int SUB_INFO = 103;
    /* subtile type */
    public static final int SUB_TYPE = 139;
    /* subtile front size */
    public static final int SUB_FONT_SIZE = 104;
    /* subtile front horizontal position */
    public static final int SUB_FONT_POSITION = 106;
    /* subtile front vertical position */
    public static final int SUB_FONT_VERTICAL = 110;
    /* subtile front color */
    public static final int SUB_FONT_COLOR = 114;
    /* subtile front backcolor */
    public static final int SUB_FONT_BACKCOLOR = 116;
    /* subtile front alignment.(0(Center),1(Left),2(Right) */
    public static final int SUB_FONT_ALIGNMENT = 112;
    /* Shadow effects */
    public static final int SUB_FONT_SHADOW = 118;
    /* Hollow effects */
    public static final int SUB_FONT_HOLLOW = 120;
    /* subtile front spacing */
    public static final int SUB_FONT_SPACE = 122;
    /* subtitle front line space */
    public static final int SUB_FONT_LINESPACE = 124;
    /* set subtitle front encode */
    public static final int SET_SUB_FONT_ENCODE = 128;
    /* get subtitle front encode */
    public static final int GET_SUB_FONT_ENCODE = 129;
    /* adjust the subtile Time stamp */
    public static final int SUB_TIME_SYNC = 130;
    /* set subtitle style */
    public static final int SUB_FONT_STYLE = 133;
    /* set subtile file */
    public static final int SUB_FILE = 132;
    /* disenble subtile */
    public static final int SUB_DISABLE = 135;
    public static final String STARTVIDEO = "com.hisilicon.video";
    public static final String ISVIDEOPLAYING = "SHOW_HIDE_FLAG";
    /* Called by playlist */
    public static final int FROMPLAYLIST = 0;
    /* Called by filemanage */
    public static final int FROMFILEM = 1;
    /* media files server */
    public static final String ACTION = "com.hisilicon.android.music.listservice";
}
