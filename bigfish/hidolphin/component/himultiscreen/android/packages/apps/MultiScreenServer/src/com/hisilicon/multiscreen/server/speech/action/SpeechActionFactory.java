package com.hisilicon.multiscreen.server.speech.action;

import com.hisilicon.multiscreen.server.speech.responsemessage.App;
import com.hisilicon.multiscreen.server.speech.responsemessage.SemanticSlot;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage;
import com.hisilicon.multiscreen.server.speech.responsemessage.VOD;
import com.hisilicon.multiscreen.server.speech.responsemessage.Weather;
import com.hisilicon.multiscreen.server.speech.responsemessage.WebSearch;
import com.hisilicon.multiscreen.server.speech.responsemessage.WebSite;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage.Semantic;

/**
 * the action factory,used to obtain specfied action.<br>
 * 处理工厂类，用于获取指定的处理类。
 *
 */
public class SpeechActionFactory
{
    public ISpeechAction getSpeechAction(SpeechResponseMessage msg)
    {
        if (null == msg)
        {
            return null;
        }
        SemanticSlot mSs = null;
        Semantic sm = msg.getSemantic();
        if (sm != null)
        {
            mSs = sm.getSlots();
        }
        if (mSs instanceof VOD)
        {
            return new VODSpeechAction();
        }
        else if (mSs instanceof App)
        {
            return new AppSpeechAction();
        }
        else if (mSs instanceof WebSite)
        {
            return new WebsiteSpeechAction();
        }
        else if (mSs instanceof WebSearch)
        {
            return new WebSearchSpeechAction();
        }
        else if (mSs instanceof Weather)
        {
            return new WeatherSpeechAction();
        }
        return null;
    }
}
