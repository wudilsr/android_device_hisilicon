package com.hisilicon.multiscreen.server.speech.action;

import java.util.HashMap;
import java.util.Map;

public class WebSearchEngine
{
    private Map<String, String> mSearchEngine = new HashMap<String, String>();

    public WebSearchEngine()
    {
        mSearchEngine.put("baidu", "http://www.baidu.com/s?wd=");
        // mSearchEngine.put("google", "https://www.google.com.hk/search?q=");
        // mSearchEngine.put("taobao", "http://s.taobao.com/search?q=");
    }

    public String getEngineUrlByName(String name)
    {
        if ((name == null) || (mSearchEngine.get(name) == null))
        {
            // default engine baidu
            return mSearchEngine.get("baidu");
        }
        else
        {
            return mSearchEngine.get(name);
        }
    }
}
