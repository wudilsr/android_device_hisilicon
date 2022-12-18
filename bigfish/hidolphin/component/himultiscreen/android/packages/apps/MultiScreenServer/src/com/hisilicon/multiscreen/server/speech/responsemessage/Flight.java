package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;



/**
 * the response message about Flight .<br>
 * CN:返回的航班信息
 *
 */
public class Flight extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    public String mFlightNo;
    public Location mStartLocation;
    public Location mEndLocation;
    public DateTime mStartDate;
    public DateTime mEndDate;
    public String mAirline;
    public String mSeat;
    public String mType;

    public Flight(JSONObject jo)
    {
        /* optional */
        try {
            mFlightNo = jo.getString("flightNo");
            LogTool.i( "flightNo = "+mFlightNo);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mStartLocation = new Location(jo.getJSONObject("startLoc"));
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mEndLocation = new Location(jo.getJSONObject("endLoc"));
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mStartDate = new DateTime(jo.getJSONObject("startDate"));
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mEndDate = new DateTime(jo.getJSONObject("endDate"));
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mAirline = jo.getString("airline");
            LogTool.i( "airline = "+mAirline);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mSeat = jo.getString("seat");
            LogTool.i( "seat = "+mSeat);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mType = jo.getString("type");
            LogTool.i( "type = "+mType);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public String getFlightNo()
    {
        return mFlightNo;
    }

    public Location getStartLocation()
    {
        return mStartLocation;
    }

    public Location getEndLocation()
    {
        return mEndLocation;
    }

    public DateTime getStartDate()
    {
        return mStartDate;
    }

    public DateTime getEndDate()
    {
        return mEndDate;
    }

    public String getAirline()
    {
        return mAirline;
    }

    public String getSeat()
    {
        return mSeat;
    }

    public String getType()
    {
        return mType;
    }
}
