package com.hisilicon.multiscreen.server.speech.responsemessage;

import java.io.Serializable;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;



/**
 * the response message about Location .<br>
 * CN:返回的位置信息
 *
 */
public class Location implements Serializable {


    private static final long serialVersionUID = 1L;
    private String mType;
    private String mCountry;
    private String mProvince;
    private String mProvinceAddr;
    private String mCity;
    private String mCityAddr;
    private String mArea;
    private String mAreaAddr;

    public Location(JSONObject jo)
    {
        try {
            mType = jo.getString("type");
            LogTool.i( "type="+mType);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mCountry = jo.getString("country");
            LogTool.i( "country="+mCountry);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mProvince = jo.getString("province");
            LogTool.i( "province="+mProvince);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mProvinceAddr = jo.getString("provinceAddr");
            LogTool.i( "provinceAddr="+mProvinceAddr);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mCity = jo.getString("city");
            LogTool.i( "city="+mCity);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mCityAddr = jo.getString("cityAddr");
            LogTool.i( "cityAddr="+mCityAddr);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mArea = jo.getString("area");
            LogTool.i( "area="+mArea);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mAreaAddr = jo.getString("areaAddr");
            LogTool.i( "areaAddr="+mAreaAddr);
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

    public String getCountry()
    {
        return mCountry;
    }

    public String getProvince()
    {
        return mProvince;
    }

    public String getProvinceAddr()
    {
        return mProvinceAddr;
    }

    public String getCity()
    {
        return mCity;
    }

    public String getCityAddr()
    {
        return mCityAddr;
    }

    public String getArea()
    {
        return mArea;
    }

    public String getAreaAddr()
    {
        return mAreaAddr;
    }

}
