package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about TV .<br>
 * CN:返回的电视节目预告信息
 *
 */
public class TV extends SemanticSlot {

    private static final long serialVersionUID = 1L;
    private DateTime mStartTime;
    private String mTVName;
    private String mProgramType;
    private String mProgramName;

    public TV(JSONObject jo)
    {
        try {
            mStartTime = new DateTime(jo.getJSONObject("startTime"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mTVName = jo.getString("tvName");
            LogTool.i( "tvName="+mTVName);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mProgramType = jo.getString("programType");
            LogTool.i( "programType="+mProgramType);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mProgramName = jo.getString("programName");
            LogTool.i( "programName="+mProgramName);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public DateTime getStartTime()
    {
        return mStartTime;
    }

    public String getTVName()
    {
        return mTVName;
    }

    public String getProgramType()
    {
        return mProgramType;
    }

    public String getProgramName()
    {
        return mProgramName;
    }

}
