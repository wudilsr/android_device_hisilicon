package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;


/**
 * the response message about Weather .<br>
 * CN:返回的天气信息
 *
 */
public class Weather extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private Location mLocation;
    private DateTime mDateTime;

    public Weather(JSONObject jo)
    {
        /* must */
        try {
            mLocation = new Location(jo.getJSONObject("location"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        /* optional */
        try {
            mDateTime = new DateTime(jo.getJSONObject("datetime"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public Location getLocation()
    {
        return mLocation;
    }

    public DateTime getDateTime()
    {
        return mDateTime;
    }
}
