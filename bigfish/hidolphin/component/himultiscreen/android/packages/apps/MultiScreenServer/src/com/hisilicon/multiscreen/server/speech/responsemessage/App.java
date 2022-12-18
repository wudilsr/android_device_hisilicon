package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


public class App extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private String mName;

    public App(JSONObject jo)
    {
        try {
            mName = jo.getString("name");
            LogTool.i("name is "+mName);
        }
        catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public String getName()
    {
        return mName;
    }
}
