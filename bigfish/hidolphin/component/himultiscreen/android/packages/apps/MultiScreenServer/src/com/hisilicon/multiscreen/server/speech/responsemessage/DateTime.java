package com.hisilicon.multiscreen.server.speech.responsemessage;

import java.io.Serializable;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * the response message about DateTime .<br>
 * CN:返回的日期信息
 *
 */
public class DateTime implements Serializable {
    /**
     *
     */
    private static final long serialVersionUID = 1L;
    private static final String Tag = "DateTime";
    public String mType;
    private String mDate;
    private String mDateOrig;
    private String mTime;
    private String mTimeOrig;
    private String mEndDate;
    private String mEndDateOrig;
    private String mEndTime;
    private String mEndTimeOrig;

    public DateTime(JSONObject jo)
    {
        /* must */
        try {
            mType = jo.getString("type");
            mDate = jo.getString("date");
            LogTool.i("type="+mType+", date="+mDate);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        /* optional */
        try {
            mDateOrig = jo.getString("dateOrig");
            LogTool.i("dateOrig is "+mDateOrig);
            mTime = jo.getString("time");
            LogTool.i( "time is "+mTime);
            mTimeOrig = jo.getString("timeOrig");
            LogTool.i( "timeOrig is "+mTimeOrig);
            mEndDate = jo.getString("endDate");
            LogTool.i( "endDate is "+mEndDate);
            mEndDateOrig = jo.getString("endDateOrig");
            LogTool.i( "endDateOrig is "+mEndDateOrig);
            mEndTime = jo.getString("endTime");
            LogTool.i( "endTime is "+mEndTime);
            mEndTimeOrig = jo.getString("endTimeOrig");
            LogTool.i( "endTimeOrig is "+mEndTimeOrig);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public String getType()
    {
        return mType;
    }

    public String getDate()
    {
        return mDate;
    }

    public String getDateOrig()
    {
        return mDateOrig;
    }

    public String getTime()
    {
        return mTime;
    }

    public String getTimeOrig()
    {
        return mTimeOrig;
    }

    public String getEndDate()
    {
        return mEndDate;
    }

    public String getEndDateOrig()
    {
        return mEndDateOrig;
    }

    public String getEndTime()
    {
        return mEndTime;
    }

    public String getEndTimeOrig()
    {
        return mEndTimeOrig;
    }
}
