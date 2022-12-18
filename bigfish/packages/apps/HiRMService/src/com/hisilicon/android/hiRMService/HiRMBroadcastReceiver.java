package com.hisilicon.android.hiRMService;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import com.hisilicon.android.HiDisplayManager;

public class HiRMBroadcastReceiver extends BroadcastReceiver {
    private static final String TAG = "HiRMBroadcastReceiver";

    private static final String ACTION_BOOT_COMPLETED = "android.intent.action.BOOT_COMPLETED";
    private static final String ACTION_RESET_BASE = "com.hisilicon.intent.action.RESET_BASEPARAM";

    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent.getAction().equals(ACTION_BOOT_COMPLETED)) {
            Intent i = new Intent(Intent.ACTION_RUN);
            i.setClass(context, HiRMService.class);
            i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startService(i);
        } else if (intent.getAction().equals(ACTION_RESET_BASE)) {
            // Reset display params
            HiDisplayManager displayManager = new HiDisplayManager();
            if (displayManager != null) {
                Log.d(TAG, "Reset display parameters.");
                displayManager.reset();
            }
        }
    }
}
