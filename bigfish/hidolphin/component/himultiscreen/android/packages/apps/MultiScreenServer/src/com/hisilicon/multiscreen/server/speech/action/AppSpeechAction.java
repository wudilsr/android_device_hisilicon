package com.hisilicon.multiscreen.server.speech.action;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ResolveInfo;
import android.os.Handler;

import com.hisilicon.multiscreen.server.speech.SpeechDialog;
import com.hisilicon.multiscreen.server.speech.responsemessage.App;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage.Semantic;
import com.hisilicon.multiscreen.server.R;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * the APP speech action ,used to launch or exit APP.<br>
 * 应用处理类，用于应用启动退出。
 *
 */
public class AppSpeechAction implements ISpeechAction
{

    private Context mContext;
    private Handler mHandler;

    @Override
    public String execute(Context context, Handler handler, SpeechResponseMessage msg)
    {
        if ((null == context) || (null == msg) || (null == handler))
        {
            return context.getString(R.string.fuction_not_support);
        }
        App app = null;
        mContext = context;
        mHandler = handler;
        Semantic sm = msg.getSemantic();
        if (sm != null)
        {
            app = (App) sm.getSlots();
        }
        else
        {
            return mContext.getString(R.string.fuction_not_support);
        }
        if (msg.getOperation().equals("LAUNCH"))
        {
            return launchApp(app.getName());
        }
        else if (msg.getOperation().equals("EXIT"))
        {
            return exitApp(app.getName());
        }
        return mContext.getString(R.string.fuction_not_support);
    }

    private String launchApp(String appName)
    {
        /*
         * List all applications, and find out by package name.<br> CN:列出所有应用，根据包名找出所需启动的应用。
         */
        Intent i = new Intent(Intent.ACTION_MAIN, null);
        i.addCategory(Intent.CATEGORY_LAUNCHER);
        List<ResolveInfo> mAppsList = mContext.getPackageManager().queryIntentActivities(i, 0);

        if (mAppsList == null)
        {
            mAppsList = new ArrayList<ResolveInfo>();
        }

        String pkgName = null;
        String clsName = null;
        for (Iterator<ResolveInfo> it = mAppsList.iterator(); it.hasNext();)
        {
            ResolveInfo app = it.next();

            CharSequence labelSeq = app.loadLabel(mContext.getPackageManager());
            String label = labelSeq != null ? labelSeq.toString() : app.activityInfo.name;

            if (label.equalsIgnoreCase(appName))
            {
                pkgName = app.activityInfo.packageName;
                clsName = app.activityInfo.name;
                break;
            }
        }

        if (null == pkgName)
        {
            LogTool.e("Not found package name by App name:" + appName);
            return mContext.getString(R.string.app_not_installed);
        }
        LogTool.d("Package:" + pkgName);
        Intent intent = new Intent(Intent.ACTION_MAIN);
        intent.addCategory(Intent.CATEGORY_LAUNCHER);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        ComponentName component = new ComponentName(pkgName, clsName);
        intent.setComponent(component);
        mContext.startActivity(intent);
        mHandler.sendEmptyMessage(SpeechDialog.MSG_SPEECH_DIALOG_DISMISS);
        return null;
    }

    private String exitApp(String appName)
    {
        return mContext.getString(R.string.fuction_not_support);
    }

}
