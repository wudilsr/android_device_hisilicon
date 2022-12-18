package com.hisilicon.multiscreen.server;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Broadcast receiver of BOOT_COMPLETED.<br>
 * CN:系统启动广播接收者。
 */
public class BootReceiver extends BroadcastReceiver
{
    @Override
    public void onReceive(Context context, Intent intent)
    {
        if (Intent.ACTION_BOOT_COMPLETED.equals(intent.getAction()))
        {
            LogTool.d("boot complete");
            context.startService(new Intent(context, MultiScreenService.class));
        }
    }
}
