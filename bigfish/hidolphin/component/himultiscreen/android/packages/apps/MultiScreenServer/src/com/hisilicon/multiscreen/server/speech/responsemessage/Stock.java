package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * the response message about Stock .<br>
 * CN:返回的股票信息
 *
 */
public class Stock extends SemanticSlot {

    private static final long serialVersionUID = 1L;
    private String mName;
    private String mCode;
    private String mCategory;
    private String mChartType;

    public Stock(JSONObject jo)
    {
        try {
            mName = jo.getString("name");
            LogTool.i( "name="+mName);
        }
        catch (JSONException e) {
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
            mChartType = jo.getString("chartType");
            LogTool.i( "chartType="+mChartType);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public String getName()
    {
        return mName;
    }

    public String getCode()
    {
        return mCode;
    }

    public String getCategory()
    {
        return mCategory;
    }

    public String getChartType()
    {
        return mChartType;
    }
}
