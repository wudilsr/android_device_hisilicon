package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about Schedule .<br>
 * CN:返回的提醒信息
 *
 */
public class Schedule extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private String mName;
    private DateTime mDateTime;
    private String mRepeat;
    private String mContent;

    public Schedule(JSONObject jo)
    {
        try {
            mName = jo.getString("name");
            LogTool.i( "name="+mName);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mDateTime = new DateTime(jo.getJSONObject("datetime"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mRepeat = jo.getString("repeat");
            LogTool.i( "repeat="+mRepeat);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mContent = jo.getString("content");
            LogTool.i( "content="+mContent);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public String getName()
    {
        return mName;
    }

    public DateTime getDateTime()
    {
        return mDateTime;
    }

    public String getRepeat()
    {
        return mRepeat;
    }

    public String getContent()
    {
        return mContent;
    }

}
