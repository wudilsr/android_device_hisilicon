package com.hisilicon.multiscreen.server.speech.action;

import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Handler;

import com.hisilicon.multiscreen.server.R;
import com.hisilicon.multiscreen.server.speech.SpeechDialog;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage.Semantic;
import com.hisilicon.multiscreen.server.speech.responsemessage.WebSearch;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * the Web Search speech action ,used to launch web search.<br>
 * 网页搜索类，用于启动网页搜索。
 *
 */
public class WebSearchSpeechAction implements ISpeechAction
{
    @Override
    public String execute(Context context, Handler handler, SpeechResponseMessage msg)
    {
        if ((null == context) || (null == msg) || (null == handler))
        {
            return context.getString(R.string.fuction_not_support);
        }
        WebSearch webSearch = null;
        String url = null;

        Semantic sm = msg.getSemantic();
        if (sm != null)
        {
            webSearch = (WebSearch) sm.getSlots();
        }
        else
        {
            return context.getString(R.string.fuction_not_support);
        }

        // Intent i = new Intent(Intent.ACTION_WEB_SEARCH);
        // i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        // i.putExtra(SearchManager.QUERY, webSearch.getKeywords());
        WebSearchEngine webSearchEngine = new WebSearchEngine();
        String urlhead = webSearchEngine.getEngineUrlByName(webSearch.getChannel());

        StringBuffer urlBuffer = new StringBuffer();
        urlBuffer.append(urlhead);
        urlBuffer.append(webSearch.getKeywords());

        Intent i = new Intent(Intent.ACTION_VIEW);
        i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        i.setData(Uri.parse(urlBuffer.toString()));

        try
        {
            context.startActivity(i);
        }
        catch (ActivityNotFoundException e)
        {
            LogTool.w(e.getMessage());
            return context.getString(R.string.browser_not_installed);
        }
        handler.sendEmptyMessage(SpeechDialog.MSG_SPEECH_DIALOG_DISMISS);
        return null;
    }
}
