package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * the response message about Map .<br>
 * CN:返回的地图信息
 *
 */
public class Map extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    // operation = "POSITION"
    private Location mLocation;

    // operation = "ROUTE"
    private Location mStartLocation;
    private Location mEndLocation;
    private String mType;

    public Map(JSONObject jo)
    {
        try {
            mLocation = new Location(jo.getJSONObject("location"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mStartLocation = new Location(jo.getJSONObject("startLoc"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mEndLocation = new Location(jo.getJSONObject("endLoc"));
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

    public Location getLocation()
    {
        return mLocation;
    }

    public Location getStartLocation()
    {
        return mStartLocation;
    }

    public Location getEndLocation()
    {
        return mEndLocation;
    }

    public String getType()
    {
        return mType;
    }

}
