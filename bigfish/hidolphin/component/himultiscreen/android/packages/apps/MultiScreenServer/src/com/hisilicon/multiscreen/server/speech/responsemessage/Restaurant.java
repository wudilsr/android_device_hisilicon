package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about Restaurant .<br>
 * CN:返回的餐馆信息
 *
 */
public class Restaurant extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private Location mLocation;
    private String mName;
    private String mCategory;
    private String mSpecial;
    private String mPrice;
    private String mKeyword;
    private int mHasCoupon;
    private int mRadius;
    private int mHasDeal;

    public Restaurant(JSONObject jo)
    {
        try {
            mLocation = new Location(jo.getJSONObject("location"));
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mName = jo.getString("name");
            LogTool.i( "name="+mName);
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
            mSpecial = jo.getString("special");
            LogTool.i( "special="+mSpecial);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mPrice = jo.getString("price");
            LogTool.i( "price="+mPrice);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mKeyword = jo.getString("keyword");
            LogTool.i( "keyword="+mKeyword);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mHasCoupon = jo.getInt("hasCoupon");
            LogTool.i( "hasCoupon="+mHasCoupon);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mRadius = jo.getInt("radius");
            LogTool.i( "radius="+mRadius);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mHasDeal = jo.getInt("hasDeal");
            LogTool.i( "hasDeal="+mHasDeal);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public Location getLocation()
    {
        return mLocation;
    }

    public String getName()
    {
        return mName;
    }

    public String getCategory()
    {
        return mCategory;
    }

    public String getSpecial()
    {
        return mSpecial;
    }

    public String getPrice()
    {
        return mPrice;
    }

    public String getKeyword()
    {
        return mKeyword;
    }

    public int getHasCoupon()
    {
        return mHasCoupon;
    }

    public int getRadius()
    {
        return mRadius;
    }

    public int getHasDeal()
    {
        return mHasDeal;
    }

}
