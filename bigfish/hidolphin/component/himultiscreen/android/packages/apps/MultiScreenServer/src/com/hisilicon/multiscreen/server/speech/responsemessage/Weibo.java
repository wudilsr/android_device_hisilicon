package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about Weibo .<br>
 * CN:返回的微博信息
 *
 */
public class Weibo extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private String mChannel;
    private String mContent;

    public Weibo(JSONObject jo)
    {
        try {
            mChannel = jo.getString("channel");
            LogTool.i( "channel="+mChannel);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mContent = jo.getString("content");
            LogTool.i( "content="+mContent);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public String getChannel()
    {
        return mChannel;
    }

    public String getContent()
    {
        return mContent;
    }
}
