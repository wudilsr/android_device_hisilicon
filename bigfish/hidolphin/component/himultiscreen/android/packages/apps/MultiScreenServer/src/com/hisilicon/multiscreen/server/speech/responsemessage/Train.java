package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about Train .<br>
 * CN:返回的火车信息
 *
 */
public class Train extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private Location mStartLocation;
    private Location mEndLoccation;
    private DateTime mStartDate;
    private String mSeat;
    private String mCode;
    private String mCategory;
    private String mType;

    public Train(JSONObject jo)
    {
        /* must */
        try {
            mStartLocation = new Location(jo.getJSONObject("startLoc"));
            mStartDate = new DateTime(jo.getJSONObject("startDate"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        /* optional */
        try {
            mEndLoccation = new Location(jo.getJSONObject("endLoc"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mSeat = jo.getString("seat");
            LogTool.i( "seat="+mSeat);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mCode = jo.getString("code");
            LogTool.i( "code="+mCode);
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

        try {
            mType = jo.getString("type");
            LogTool.i( "type="+mType);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public Location getStartLocation()
    {
        return mStartLocation;
    }

    public Location getEndLocation()
    {
        return mEndLoccation;
    }

    public DateTime getStartDate()
    {
        return mStartDate;
    }

    public String getSeat()
    {
        return mSeat;
    }

    public String getCode()
    {
        return mCode;
    }

    public String getCategory()
    {
        return mCategory;
    }

    public String getType()
    {
        return mType;
    }
}
