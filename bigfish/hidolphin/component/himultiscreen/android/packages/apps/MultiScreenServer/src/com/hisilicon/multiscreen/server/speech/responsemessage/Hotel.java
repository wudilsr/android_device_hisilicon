package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about Hotel .<br>
 * CN:返回的酒店信息
 *
 */
public class Hotel extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private String mName;
    private Location mLocation;
    private DateTime mCheckinDate;
    private DateTime mCheckoutDate;
    private String mPriceMax;
    private String mPriceMin;
    private String mHotelLvl;
    private String mRoomCount;
    private String mRoomType;

    public Hotel(JSONObject jo)
    {
        /* optional */
        try {
            mName = jo.getString("name");
            LogTool.i( "name="+mName);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
        /* must */
        try {
            mLocation = new Location(jo.getJSONObject("location"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mCheckinDate = new DateTime(jo.getJSONObject("checkinDate"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        /* optional */
        try {
            mCheckoutDate = new DateTime(jo.getJSONObject("checkoutDate"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mPriceMax = jo.getString("priceMax");
            LogTool.i( "priceMax="+mPriceMax);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mPriceMin = jo.getString("priceMin");
            LogTool.i( "priceMin="+mPriceMin);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mHotelLvl = jo.getString("hotelLvl");
            LogTool.i( "hotelLvl="+mHotelLvl);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mRoomCount = jo.getString("roomCount");
            LogTool.i( "roomCount="+mRoomCount);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mRoomType = jo.getString("roomType");
            LogTool.i( "roomType="+mRoomType);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public String getName()
    {
        return mName;
    }

    public Location getLocation()
    {
        return mLocation;
    }

    public DateTime getCheckinDate()
    {
        return mCheckinDate;
    }

    public DateTime getCheckoutDate()
    {
        return mCheckoutDate;
    }

    public String getPriceMax()
    {
        return mPriceMax;
    }

    public String getPriceMin()
    {
        return mPriceMin;
    }

    public String getHotelLevel()
    {
        return mHotelLvl;
    }

    public String getRoomCount()
    {
        return mRoomCount;
    }

    public String getRoomType()
    {
        return mRoomType;
    }
}
