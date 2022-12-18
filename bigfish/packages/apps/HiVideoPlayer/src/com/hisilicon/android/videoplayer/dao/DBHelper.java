package com.hisilicon.android.videoplayer.dao;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteDatabase.CursorFactory;

import com.hisilicon.android.videoplayer.util.Constants;

public class DBHelper extends SQLiteOpenHelper
{
    public DBHelper(Context context, String name, CursorFactory factory,
                    int version)
    {
        super(context, name, factory, version);
    }

    public void onCreate(SQLiteDatabase db)
    {
        db.execSQL("create table " + Constants.TABLE_VIDEO
                   + "(_id integer primary key,_data text not null,display_name text,"
                   + "_size integer,mime_type text,data_added integer,date_modified integer,title text,"
                   + "duration integer,artist text,album text,resolution text,description text,"
                   + "isprivate integer,tags text,category text,language text,mini_thumb_data text,"
                   + "latitude double,longitude double,datetaken integer,mini_thumb_magic integer,"
                   + "bucket_id text,bucket_display_name text,bookmark integer,recommended integer,"
                   + "style text,director text,video_region text,start_screen integer,mark_score integer,"
                   + "play_times char,last_play_postion integer)");
        db.execSQL("create index idx_data on video(_data)" );
        db.execSQL("create index idx_displayname on video(display_name)");

        db.execSQL("create table " + Constants.VIDEO_BOOKMARK + "(_id integer primary key,_data text not null,"
                   + "bookmark_name text,bookmark integer,date_added integer)");
        db.execSQL("create index idx_v_bkm_data on " + Constants.VIDEO_BOOKMARK + "(_data)");

        db.execSQL("create table " + Constants.VIDEO_PLAYLISTS
                   + "(_id integer primary key,_data text,name text not null,"
                   + "date_added integer,date_modified integer)");
        db.execSQL("create unique index idx_vpll_name on " + Constants.VIDEO_PLAYLISTS + "(name)");
        db.execSQL("create index idx_vpll_data on " + Constants.VIDEO_PLAYLISTS + "(_data)");

        db.execSQL("create table " + Constants.VIDEO_MAP + "(_id integer primary key,video_id integer not null,"
                   + "playlist_id integer not null,play_order integer not null)");
        db.execSQL("create index playlists_video_id on " + Constants.VIDEO_MAP + "(playlist_id)");

        db.execSQL("create index idx_video_id on " + Constants.VIDEO_MAP + "(video_id)");
    }

    public static void createContactsTriggers(SQLiteDatabase db)
    {
        db.execSQL("DROP TRIGGER IF EXISTS " + Constants.TRIGGER_VIDEO_CLEANUP + "_deleted;");
        db.execSQL("CREATE TRIGGER " + Constants.TRIGGER_VIDEO_CLEANUP + " DELETE ON " + Constants.VIDEO_PLAYLISTS
                   + " BEGIN "
                   + "   DELETE FROM " + Constants.VIDEO_MAP
                   + "     WHERE playlist_id"
                   + "=OLD." + "_id" + ";"
                   + "   SELECT _DELETE_FILE("
                   + "=OLD." + "_data);"
                   + " END");
    }

    public void onUpgrade(SQLiteDatabase db, int arg1, int arg2)
    {
        String sql = "drop table if EXISTS mymark;";

        db.execSQL(sql);
        db.execSQL("drop table if EXISTS videoinfos;");
        db.execSQL("drop table if EXISTS " + Constants.TABLE_VIDEO + ";");
        db.execSQL("drop table if EXISTS " + Constants.VIDEO_BOOKMARK + ";");
        db.execSQL("drop table if EXISTS  " + Constants.VIDEO_PLAYLISTS + ";");
        db.execSQL("drop table if EXISTS  " + Constants.VIDEO_MAP + ";");
        onCreate(db);
    }
}
