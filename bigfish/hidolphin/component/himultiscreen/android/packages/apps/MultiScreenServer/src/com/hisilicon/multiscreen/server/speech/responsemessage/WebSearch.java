package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * the response message about Websearch .<br>
 * CN:返回的网页搜索信息
 *
 */
public class WebSearch extends SemanticSlot {

    private static final long serialVersionUID = 1L;
    private String mChannel;
    private String mKeywords;

    public WebSearch(JSONObject jo)
    {
        /* must */
        try {
            mKeywords = jo.getString("keywords");
            LogTool.i( "keywords="+mKeywords);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        /* optional */
        try {
            mChannel = jo.getString("channel");
            LogTool.i( "channel="+mChannel);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public String getChannel()
    {
        return mChannel;
    }

    public String getKeywords()
    {
        return mKeywords;
    }

}
