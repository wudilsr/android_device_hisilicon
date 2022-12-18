package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about Translation .<br>
 * CN:返回的翻译信息
 *
 */
public class Translation extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private String mContent;
    private String mSource;
    private String mTarget;

    public Translation(JSONObject jo)
    {
        try {
            mContent = jo.getString("content");
            LogTool.i( "content="+mContent);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mSource = jo.getString("source");
            LogTool.i( "source="+mSource);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            mTarget = jo.getString("target");
            LogTool.i( "target="+mTarget);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }

    }

    public String getContent()
    {
        return mContent;
    }

    public String getSource()
    {
        return mSource;
    }

    public String getTarget()
    {
        return mTarget;
    }

}
