package com.hisilicon.android.acceleratd.ageing;

import android.content.BroadcastReceiver;
import android.content.SharedPreferences;
import android.content.Intent;
import android.content.Context;
import android.util.Log;

public class BootReceiver extends BroadcastReceiver
{
    private String TAG = "Factorytest";
    @Override
    public void onReceive(Context context, Intent intent)
    {
        if (intent.getAction().equals("android.intent.action.BOOT_COMPLETED"))
        {
            int boot = context.getSharedPreferences("shared", Context.MODE_PRIVATE).getInt("boot", 1);
            if(boot == 1)
            {
                Intent newintent = new Intent(context, factorytestActivity.class );
                newintent.setAction("android.intent.action.MAIN");
                newintent.addCategory("android.intent.category.LAUNCHER");
                newintent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                context.startActivity(newintent);
            }
        }
    }
}
