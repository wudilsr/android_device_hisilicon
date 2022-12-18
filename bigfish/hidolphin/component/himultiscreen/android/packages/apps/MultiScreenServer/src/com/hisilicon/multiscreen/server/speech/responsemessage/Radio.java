package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * the response message about Radio .<br>
 * CN:返回的广播信息
 *
 */
public class Radio extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private String mName;
    private String mCode;
    private String mWaveband;

    public Radio(JSONObject jo)
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
            mWaveband = jo.getString("waveband");
            LogTool.i( "waveband="+mWaveband);
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

    public String getWaveband()
    {
        return mWaveband;
    }
}
