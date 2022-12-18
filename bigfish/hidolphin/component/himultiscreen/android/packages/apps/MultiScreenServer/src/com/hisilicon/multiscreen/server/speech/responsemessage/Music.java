package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about Music .<br>
 * CN:返回的音乐信息
 *
 */
public class Music extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private String mSong;
    private String mArtist;
    private String mAlbum;
    private String mCategory;

    public Music(JSONObject jo)
    {
        try {
            mSong = jo.getString("song");
            LogTool.i( "song="+mSong);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mArtist = jo.getString("artist");
            LogTool.i( "artist="+mArtist);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mAlbum = jo.getString("album");
            LogTool.i( "album="+mAlbum);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mCategory = jo.getString("category");
            LogTool.i( "category="+mCategory);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

    }

    public String getSong()
    {
        return mSong;
    }

    public String getArtist()
    {
        return mArtist;
    }

    public String getAlbum()
    {
        return mAlbum;
    }

    public String getCategory()
    {
        return mCategory;
    }

}
