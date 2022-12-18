package com.hisilicon.multiscreen.server.speech.action;

import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Handler;

import com.hisilicon.multiscreen.server.speech.SpeechDialog;
import com.hisilicon.multiscreen.server.speech.responsemessage.App;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage.Semantic;
import com.hisilicon.multiscreen.server.speech.responsemessage.WebSite;
import com.hisilicon.multiscreen.server.R;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * the Website speech action ,used to launch brower for the spefied url.<br>
 * 网页处理类，用于打开浏览器并打开网页。
 *
 */
public class WebsiteSpeechAction implements ISpeechAction
{

    @Override
    public String execute(Context context, Handler handler, SpeechResponseMessage msg)
    {
        if ((null == context) || (null == msg) || (null == handler))
        {
            return context.getString(R.string.fuction_not_support);
        }
        WebSite site = null;
        String url = null;
        Semantic sm = msg.getSemantic();
        if (sm != null)
        {
            site = (WebSite) sm.getSlots();
            url = site.getUrl();
        }
        else
        {
            return context.getString(R.string.fuction_not_support);
        }
        if (url == null)
        {
            return context.getString(R.string.fuction_not_support);
        }
        Intent i = new Intent(Intent.ACTION_VIEW);
        i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        i.setData(Uri.parse(url));
        try
        {
            context.startActivity(i);
        }
        catch (ActivityNotFoundException e)
        {
            e.printStackTrace();
            return context.getString(R.string.browser_not_installed);
        }
        handler.sendEmptyMessage(SpeechDialog.MSG_SPEECH_DIALOG_DISMISS);
        return null;
    }
}
