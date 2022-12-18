package com.hisilicon.android.videoplayer.dao;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import android.app.Activity;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.provider.MediaStore;
import android.provider.MediaStore.Video;
import android.util.Log;

import com.hisilicon.android.videoplayer.activity.VideoModel;
import com.hisilicon.android.videoplayer.util.Common;
import com.hisilicon.android.videoplayer.util.Constants;

public class DBOperateHelper
{
    private static final String TAG = "DBOperateHelper";

    public List <VideoModel> getAllVideoModel(Context con) throws Exception
    {
        List <VideoModel> listVideoMode = queryAllMovie(con);

        return listVideoMode;
    }

    public List <VideoModel> searchByName(Activity act, String name)
    {
        List <VideoModel> videos = new ArrayList <VideoModel>();
        ContentResolver resolver = act.getContentResolver();

        if (name != null)
        {
            if (name.contains("'"))
            {
                name = name.replace("'", "''");
            }
        }

        Cursor cursor = resolver.query(Video.Media.getContentUri("external"), new String[] {"_id",
                                                                                            "_data", "_display_name",
                                                                                            "_size", "duration",
                                                                                            "date_added", "mime_type"},
                                       "_display_name like '%" + name + "%'", null, "_display_name");
        if (cursor == null)
        {
            return videos;
        }

        while (cursor.moveToNext())
        {
            VideoModel video = new VideoModel();
            video.setId(cursor.getInt(0));
            video.setPath(cursor.getString(1));
            video.setTitle(cursor.getString(2));
            video.setSize(cursor.getLong(3));
            video.setDuration(cursor.getInt(4));
            video.setAddedTime(cursor.getInt(5));
            video.setMimeType(cursor.getString(6));
            videos.add(video);
        }

        if (cursor != null)
        {
            cursor.close();
        }

        return videos;
    }

    public List <VideoModel> searchLatestTenVideos(Activity act)
    {
        List <VideoModel> videos = new ArrayList <VideoModel>();
        ContentResolver resolver = act.getContentResolver();
        Cursor cursor = resolver.query(Video.Media.getContentUri("external"), new String[] {"_id",
                                                                                            "_data", "_display_name",
                                                                                            "_size", "duration",
                                                                                            "date_added", "mime_type"},
                                       "last_play_time is not null", null, "last_play_time desc");
        if (cursor == null)
        {
            return videos;
        }

        while (cursor.moveToNext())
        {
            VideoModel video = new VideoModel();
            video.setId(cursor.getInt(0));
            video.setPath(cursor.getString(1));
            video.setTitle(cursor.getString(2));
            video.setSize(cursor.getLong(3));
            video.setDuration(cursor.getInt(4));
            video.setAddedTime(cursor.getInt(5));
            video.setMimeType(cursor.getString(6));
            videos.add(video);
        }

        if (cursor != null)
        {
            cursor.close();
        }

        return videos;
    }

    public List <VideoModel> searchLatestTenVideosByName(Activity act)
    {
        List <VideoModel> videos = new ArrayList <VideoModel>();
        ContentResolver resolver = act.getContentResolver();
        Cursor cursor = resolver.query(Video.Media.getContentUri("external"), new String[] {"_id",
                                                                                            "_data", "_display_name",
                                                                                            "_size", "duration",
                                                                                            "date_added", "mime_type"},
                                       "last_play_time is not null", null, "_display_name");
        if (cursor == null)
        {
            return videos;
        }

        while (cursor.moveToNext())
        {
            VideoModel video = new VideoModel();
            video.setId(cursor.getInt(0));
            video.setPath(cursor.getString(1));
            video.setTitle(cursor.getString(2));
            video.setSize(cursor.getLong(3));
            video.setDuration(cursor.getInt(4));
            video.setAddedTime(cursor.getInt(5));
            video.setMimeType(cursor.getString(6));
            videos.add(video);
        }

        if (cursor != null)
        {
            cursor.close();
        }

        return videos;
    }

    public void updatePlayTime(Activity act, int videoId)
    {
        if (videoId > -1)
        {
            ContentResolver resolver = act.getContentResolver();
            ContentValues values = new ContentValues();
            values.put("last_play_time", new Date().getTime());
            resolver.update(Video.Media.getContentUri("external"), values, "_id=" + videoId, null);
            values   = null;
            resolver = null;
        }
    }

    public String[] allTitles(Activity act)
    {
        String[] titles = {};
        ContentResolver resolver = act.getContentResolver();
        Cursor cursor = resolver.query(Video.Media.getContentUri("external"),
                                       new String[] {"_display_name"}, null, null, null);
        if (cursor != null)
        {
            titles = new String[cursor.getCount()];
            int i = 0;
            while (cursor.moveToNext())
            {
                titles[i] = cursor.getString(0);
                i++;
            }

            cursor.close();
        }

        return titles;
    }

    public List <VideoModel> searchVideosByPlayList(Activity act, int listId)
    {
        List <VideoModel> videos = new ArrayList <VideoModel>();
        ContentResolver resolver = act.getContentResolver();
        Uri uri = Uri.parse("content://media/external/video/playlists/" + listId + "/members");
        Cursor cursor = resolver.query(uri, new String[] {"video_id"}, null, null, null);
        String idZone = "";
        List <Integer> ids = new       ArrayList <Integer>();
        if (cursor != null)
        {
            while (cursor.moveToNext())
            {
                ids.add(cursor.getInt(0));
            }

            cursor.close();
        }

        for (int i = 0; i < ids.size(); i++)
        {
            if (i == 0)
            {
                idZone = idZone + ids.get(i);
            }
            else
            {
                idZone = idZone + "," + ids.get(i);
            }
        }

        Cursor c = resolver.query(Video.Media.getContentUri("external"), new String[] {"_id",
                                                                                       "_data", "_display_name",
                                                                                       "_size", "duration",
                                                                                       "date_added", "mime_type"},
                                  "_id in (" + idZone + ")", null, "_display_name");
        if (c != null)
        {
            while (c.moveToNext())
            {
                VideoModel video = new VideoModel();
                video.setId(c.getInt(0));
                video.setPath(c.getString(1));
                video.setTitle(c.getString(2));
                video.setSize(c.getLong(3));
                video.setDuration(c.getInt(4));
                video.setAddedTime(c.getInt(5));
                video.setMimeType(c.getString(6));
                videos.add(video);
            }

            c.close();
        }

        return videos;
    }

    public boolean delVideoMapValue(Activity act, int listId, int videoId)
    {
        boolean result = false;

        try
        {
            ContentResolver resolver = act.getContentResolver();
            Uri uri = Uri.parse("content://media/external/video/playlists/" + listId + "/members/"
                                + videoId);
            result = resolver.delete(uri, null, null) >= 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return result;
    }

    public boolean modifyPlayListName(Activity act, int listId, String name)
    {
        try
        {
            ContentResolver resolver = act.getContentResolver();
            Uri uri = Uri.parse("content://media/external/video/playlists/" + listId);
            ContentValues cv = new ContentValues();
            cv.put("name", name);
            resolver.update(uri, cv, null, null);
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    public void addVideoToPlayList(Activity act, int listId, int videoId)
    {
        ContentResolver resolver = act.getContentResolver();
        ContentValues values = new ContentValues();

        values.put("playlist_id", listId);
        values.put("video_id", videoId);
        values.put("play_order", 0);
        Uri uri = Uri.parse("content://media/external/video/playlists/" + listId);
        resolver.insert(uri, values);
        values   = null;
        resolver = null;
    }

    public List <VideoModel> queryRecommand(SQLiteDatabase db, Activity act) throws Exception
    {
        List <VideoModel> videos = new ArrayList <VideoModel>();
        VideoModel videoModel = null;
        if ((db == null) || !(db.isOpen()))
        {
            return videos;
        }

        Cursor cursor = db.query(Constants.TABLE_VIDEO, new String[] {"_id", "_data",
                                                                      "display_name", "_size", "duration", "data_added",
                                                                      "mime_type"}, "recommended = 1",
                                 null, null, null, null);
        if ((cursor != null) && (cursor.getCount() > 0))
        {
            while (cursor.moveToNext())
            {
                videoModel = new VideoModel();
                videoModel.setId(cursor.getInt(0));
                videoModel.setPath(cursor.getString(1));
                videoModel.setTitle(cursor.getString(2));
                videoModel.setSize(cursor.getLong(3));
                videoModel.setDuration(cursor.getInt(4));
                videoModel.setAddedTime(cursor.getInt(5));
                videoModel.setMimeType(cursor.getString(6));
                videos.add(videoModel);
            }
        }

        if (cursor != null)
        {
            cursor.close();
        }

        return videos;
    }

    public VideoModel searchByData(Activity act, String data)
    {
        VideoModel video = new VideoModel();
        ContentResolver resolver = act.getContentResolver();

        Cursor cursor = resolver.query(Video.Media.getContentUri("external"), new String[] {"_id",
                                                                                            "_data", "_display_name",
                                                                                            "_size", "duration",
                                                                                            "date_added", "mime_type"},
                                       "_data = '" + data + "'", null, null);

        if ((cursor != null) && (cursor.getCount() > 0))
        {
            while (cursor.moveToNext())
            {
                video.setId(cursor.getInt(0));
                video.setPath(cursor.getString(1));
                video.setTitle(cursor.getString(2));
                video.setSize(cursor.getLong(3));
                video.setDuration(cursor.getInt(4));
                video.setAddedTime(cursor.getInt(5));
                video.setMimeType(cursor.getString(6));
            }
        }

        if (cursor != null)
        {
            cursor.close();
        }

        return video;
    }

    public List <VideoModel> queryAllMovie(Context act) throws Exception
    {
        ContentResolver resolver = act.getContentResolver();

        Cursor cursor = resolver.query(Video.Media.getContentUri("external"), new String[] {"_id",
                                                                                            "_data", "_display_name",
                                                                                            "_size", "duration",
                                                                                            "date_added",
                                                                                            "mime_type"}, null,
                                       null, "_display_name");
        List <VideoModel> videos = new ArrayList <VideoModel>();

        if (cursor == null)
        {
            Log.v("songjn", "therr is no media!");
            return videos;
        }

        while (cursor.moveToNext())
        {
            VideoModel video = new VideoModel();
            video.setId(cursor.getInt(0));
            video.setPath(cursor.getString(1));
            video.setTitle(cursor.getString(2));
            video.setSize(cursor.getLong(3));
            video.setDuration(cursor.getInt(4));
            video.setAddedTime(cursor.getInt(5));
            video.setMimeType(cursor.getString(6));
            videos.add(video);
        }

        if (cursor != null)
        {
            cursor.close();
        }

        return videos;
    }

    public boolean delVideoModeItem(SQLiteDatabase db, Context act, VideoModel videoModel, int state)
    {
        Cursor cursor  = queryByData(db, videoModel);
        boolean result = false;

        if (state != 1)
        {
            Common.getData().remove(videoModel);
            ContentResolver cr = act.getContentResolver();
            String videoID = "content://media/external/video/media/" + videoModel.getId();
            cr.delete(Uri.parse(videoID), "_id=" + videoModel.getId(), null);
        }

        if ((cursor != null) && (cursor.getCount() >= 0))
        {
            result = db
                     .delete(Constants.TABLE_VIDEO, "_data=?", new String[] {videoModel.getPath()}) >= 0;
        }

        if (cursor != null)
        {
            cursor.close();
        }

        return result;
    }

    public Cursor queryByData(SQLiteDatabase db, VideoModel videoModel)
    {
        Cursor cursor = db
                        .query(Constants.TABLE_VIDEO, new String[] {"_id,_data"},
                               "recommended = 1 and _data=?", new String[] {videoModel.getPath()}, null,
                               null, null);

        return cursor;
    }

    public boolean deleteRecommend(SQLiteDatabase db) throws Exception
    {
        if ((db == null) || !(db.isOpen()))
        {
            return false;
        }

        boolean result = db.delete(Constants.TABLE_VIDEO, "recommended = 1", null) >= 0;
        return result;
    }

    public boolean insertVideo(Context con, VideoModel videomode)
    {
        Cursor cursor = Constants.getDB(con).query(Constants.TABLE_VIDEO, new String[] {"_id"},
                                                   " _data = ? ", new String[] {videomode.getPath()}, null, null, null);

        if ((cursor != null) && (cursor.getCount() > 0))
        {
            cursor.close();
            return false;
        }

        ContentValues value = new ContentValues();
        value.put("_data", videomode.getPath());
        value.put("recommended", 0);
        value.put("display_name", videomode.getTitle());
        value.put("_size", videomode.getSize());
        value.put("duration", videomode.getDuration());
        value.put("data_added", videomode.getAddedTime());
        Constants.getDB(con).insert(Constants.TABLE_VIDEO, null, value);
        if (cursor != null)
        {
            cursor.close();
        }

        return true;
    }

    public List <VideoModel> queryByMode(Context con, String cateory, String values)
    {
        VideoModel videoModel = null;

        List <VideoModel> videos = new ArrayList <VideoModel>();
        String str = null;
        if ("director".equals(cateory))
        {
            str = "where director='" + values + "'";
        }
        else if ("style".equals(cateory))
        {
            str = "where style='" + values + "'";
        }
        else if ("".equals(cateory))
        {
            str = "where style='" + values + "'";
        }
        else if ("".equals(cateory))
        {
            str = "where style='" + values + "'";
        }

        Cursor cursor = Constants.getDB(con).query(
            Constants.TABLE_VIDEO,
            new String[] {"_id", "_data", "display_name", "_size", "duration", "data_added",
                          "mime_type", "director", "style"}, str, null, null, null, null);

        if ((cursor != null) && (cursor.getCount() > 0))
        {
            while (cursor.moveToNext())
            {
                videoModel = new VideoModel();
                videoModel.setId(cursor.getInt(0));
                videoModel.setPath(cursor.getString(1));
                videoModel.setTitle(cursor.getString(2));
                videoModel.setSize(cursor.getLong(3));
                videoModel.setDuration(cursor.getInt(4));
                videoModel.setAddedTime(cursor.getInt(5));
                videoModel.setMimeType(cursor.getString(6));
                videos.add(videoModel);
            }
        }

        if (cursor != null)
        {
            cursor.close();
        }

        return videos;
    }

    public boolean checkMarkPoint(SQLiteDatabase db, String currentPath, String mark,
                                  String markName)
    {
        boolean isRepeat = false;
        Cursor cursor = null;

        try
        {
            cursor = db.query(Constants.VIDEO_BOOKMARK, new String[] {"_data", "bookmark_name",
                                                                      "bookmark"}, null, null, null, null, null);
            while (cursor.moveToNext())
            {
                if (cursor.getString(cursor.getColumnIndex("_data")).equals(currentPath)
                    && Common.getTimeFormatValue(
                        cursor.getInt(cursor.getColumnIndex("bookmark"))).equals(mark)
                    && cursor.getString(cursor.getColumnIndex("bookmark_name")).trim()
                    .equals(markName))
                {
                    isRepeat = true;
                    break;
                }
                else
                {
                    isRepeat = false;
                }

                Log.i(cursor.getString(cursor.getColumnIndex("_data")), currentPath);
                Log.i(Common.getTimeFormatValue(cursor.getInt(cursor.getColumnIndex("bookmark"))),
                      mark);
                Log.i(cursor.getString(cursor.getColumnIndex("bookmark_name")).trim(), markName);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        finally
        {
            if (cursor != null)
            {
                cursor.close();
                cursor = null;
            }
        }
        return isRepeat;
    }

    public void insertBookMark(SQLiteDatabase db, String currentPath, int mark, String markName)
    {
        String sql = "insert into " + Constants.VIDEO_BOOKMARK
                     + "(_data,bookmark,bookmark_name,date_added) values ('" + currentPath + "','"
                     + mark + "','" + markName + "','"
                     + Common.getFormatDate(System.currentTimeMillis()) + "')";

        db.execSQL(sql);
    }

    public void thumbnailSetter(Activity context, List <VideoModel> videos)
    {
        ContentResolver resolver = context.getContentResolver();
        Cursor thumbCursor = resolver.query(MediaStore.Video.Thumbnails.EXTERNAL_CONTENT_URI,
                                            new String[] {"video_id", "_data"}, null, null, null);

        if (thumbCursor != null)
        {
            while (thumbCursor.moveToNext())
            {
                int id = thumbCursor.getInt(0);
                Log.i(TAG, "id=" + thumbCursor.getInt(0));
                for (VideoModel vm : videos)
                {
                    if (id == vm.getId())
                    {
                        vm.setThumbnailPath(thumbCursor.getString(1));
                        break;
                    }
                }
            }
        }

        if (thumbCursor != null)
        {
            thumbCursor.close();
        }
    }

    public void updateDuratin(Context context, int id, long duration)
    {
        ContentResolver resolver = context.getContentResolver();
        ContentValues values = new ContentValues();

        values.put("duration", duration);
        resolver.update(Video.Media.getContentUri("external"), values, "_id=" + id, null);
    }
}
