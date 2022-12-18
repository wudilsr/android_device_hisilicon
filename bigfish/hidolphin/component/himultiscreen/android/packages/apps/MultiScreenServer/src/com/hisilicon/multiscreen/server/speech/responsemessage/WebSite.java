package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about WebSite .<br>
 * CN:返回的网址信息
 *
 */
public class WebSite extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private String mName;
    private String mUrl;

    public WebSite(JSONObject jo)
    {
        try {
            mName = jo.getString("name");
            LogTool.i( "name ="+mName);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mUrl = jo.getString("url");
            LogTool.i( "url ="+mUrl);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public String getName()
    {
        return mName;
    }

    public String getUrl()
    {
        return mUrl;
    }

}
