package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about VOD .<br>
 * CN:返回的视频点播信息
 *
 */
public class VOD extends SemanticSlot{


    private static final long serialVersionUID = 1L;
    /* must area if Operation=="PLAY", optional if Operation=="QUERY" */
    private String mQueryField;
    /* optional area */
    private String mChannel;
    private String mKeywords;
    private String mActor;
    private String mDirector;
    private String mCountry;
    private String mVideoCategory;
    private String mVideoTag;
    private String mSeason;
    private String mEpisode;
    private DateTime mDateTime;
    private String mTVChannel;
    private String mPopularity;

    public VOD(JSONObject jo)
    {
        LogTool.i( "video slots:"+jo.toString());
        /* must */
        try {
            mQueryField = jo.getString("queryField");
            LogTool.i( "queryField="+mQueryField);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        /* optional */
        try {
            mChannel = jo.getString("channel");
            LogTool.i("channel="+mChannel);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mKeywords = jo.getString("keywords");
            LogTool.i("keywords="+mKeywords);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mActor = jo.getString("actor");
            LogTool.i("actor="+mActor);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mDirector = jo.getString("director");
            LogTool.i("director="+mDirector);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mCountry = jo.getString("country");
            LogTool.i("country="+mCountry);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mVideoCategory = jo.getString("videoCategory");
            LogTool.i("videoCategory="+mVideoCategory);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mVideoTag = jo.getString("videoTag");
            LogTool.i("videoTag="+mVideoTag);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mSeason = jo.getString("season");
            LogTool.i("season="+mSeason);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mEpisode = jo.getString("episode");
            LogTool.i("episode="+mEpisode);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            JSONObject joDateTime = jo.getJSONObject("datetime");
            mDateTime = new DateTime(joDateTime);
            LogTool.i("datetime="+jo.toString());
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mTVChannel = jo.getString("tvchannel");
            LogTool.i("tvchannel="+mTVChannel);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mPopularity = jo.getString("popularity");
            LogTool.i("popularity="+mPopularity);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public String getQueryField()
    {
        return mQueryField;
    }

    public String getChannel()
    {
        return mChannel;
    }

    public String getKeywords()
    {
        return mKeywords;
    }

    public String getActor()
    {
        return mActor;
    }

    public String getDirector()
    {
        return mDirector;
    }

    public String getCountry()
    {
        return mCountry;
    }

    public String getVideoCategory()
    {
        return mVideoCategory;
    }

    public String getVideoTag()
    {
        return mVideoTag;
    }

    public String getSeason()
    {
        return mSeason;
    }

    public DateTime getDateTime()
    {
        return mDateTime;
    }

    public String getTVChannel()
    {
        return mTVChannel;
    }

    public String getPopularity()
    {
        return mPopularity;
    }
}
