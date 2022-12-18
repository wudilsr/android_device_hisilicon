package com.hisilicon.multiscreen.protocol.utils;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningServiceInfo;
import android.content.Context;
import android.content.Intent;

import com.hisilicon.dlna.dmc.gui.activity.AppPreference;
import com.hisilicon.dlna.dmc.processor.upnp.CoreUpnpService;
import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.mybox.MyApp;

public class ServiceUtil
{
    public static void checkMultiScreenControlService(Context context)
    {
        if (isServiceRunning(context, MultiScreenControlService.class.getName()) == false)
        {
            startMultiScreenControlService(context);
        }
    }

    /**
     * True if the service is running.<br>
     * @param context
     * @param serviceName
     * @return
     */
    public static boolean isServiceRunning(Context context, String serviceName)
    {
        ActivityManager manager =
            (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        for (RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE))
        {
            if (serviceName.equals(service.service.getClassName()))
            {
                return true;
            }
        }
        return false;
    }

    /**
     * Start service in WelcomeActivity.<br>
     * If the service is not running, do start it again.<br>
     * @param context
     * @see WlecomeActivity.java
     */
    public static void startMultiScreenControlService(Context context)
    {
        LogTool.d("Start MultiScreenControlService");
        Intent intent = new Intent(context, MultiScreenControlService.class);
        context.startService(intent);
    }

    /**
     * CN:关闭多屏控制服务。
     * @param context
     */
    public static void stopMultiScreenControlService(Context context)
    {
        LogTool.d("Stop MultiScreenControlService");
        Intent intent = new Intent(context, MultiScreenControlService.class);
        context.stopService(intent);
    }

    /**
     * Get saved UUID.<br>
     * CN:获取保存的UUID。
     * @return
     */
    public static String getSavedUuid()
    {
        return MultiScreenControlService.save_uuid;
    }

    /**
     * Save UUID.<br>
     * CN:保存UUID。
     * @param uuid
     */
    public static void saveUuid(String uuid)
    {
        MultiScreenControlService.save_uuid = uuid;
        AppPreference.setMultiScreenUDN(uuid);
    }

    /**
     * CN:开启媒体分享服务。
     * @param context
     */
    public static void startMediaSharingService(Context context)
    {
        Intent intent = new Intent(MyApp.getApplication(), CoreUpnpService.class);
        context.startService(intent);
    }

    /**
     * CN:关闭媒体分享服务。
     * @param context
     */
    public static void stopMediaSharingService(Context context)
    {
        Intent intent = new Intent(MyApp.getApplication(), CoreUpnpService.class);
        context.stopService(intent);
    }
}
