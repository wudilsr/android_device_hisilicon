package com.android.factorytest;

import java.io.File;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class BootReceiver extends BroadcastReceiver {
    private String path1 = "/mnt/sda/sda1/mac_info.xml";
    private String path2 = "/mnt/sdb/sdb1/mac_info.xml";

    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent.getAction().equals("android.intent.action.BOOT_COMPLETED")) {
            File file1 = new File(path1);
            File file2 = new File(path2);
            if (!file1.exists() && !file2.exists()) {
                return;
            }
            Intent newintent = new Intent(context, factorytestActivity.class);
            newintent.addCategory("android.intent.category.LAUNCHER");
            newintent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(newintent);
        }
    }

}