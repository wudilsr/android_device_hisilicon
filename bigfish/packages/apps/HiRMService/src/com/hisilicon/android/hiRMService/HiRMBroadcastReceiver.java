package com.hisilicon.android.hiRMService;

import java.net.URL;
import java.net.URLConnection;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimeZone;
import android.os.SystemProperties;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;
import com.hisilicon.android.HiDisplayManager;
import com.hisilicon.android.hisysmanager.HiSysManager;

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
        }else if(intent.getAction().equals(ConnectivityManager.CONNECTIVITY_ACTION_IMMEDIATE)){
              Log.i(TAG, "getreceive CONNECTIVITY_ACTION_IMMEDIATE");
              NetworkInfo info = (NetworkInfo) intent.getExtras().get(ConnectivityManager.EXTRA_NETWORK_INFO);
                if(null!=info&&info.isConnected()){
                     Log.i(TAG, "getreceive CONNECTIVITY_ACTION_IMMEDIATE and net ok");
                     refreshTimeThread t = new refreshTimeThread();
                     t.start();
                }
        }
    }
    class refreshTimeThread extends Thread{
        public void run(){
               getNetTime();
           }
        }
    public void getNetTime(){
        Log.i(TAG, "getreceive CONNECTIVITY_ACTION_IMMEDIATE and getnettime");
        int count = 1;
        HiSysManager hisys = new HiSysManager();
        while(count < 13)
        {
           try
            {
              URL url = new URL("http://www.baidu.com/");
              URLConnection uc = url.openConnection();
              uc.connect();
              long time = uc.getDate();
              Date date = new Date(time);
              SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
              dateFormat.setTimeZone(TimeZone.getTimeZone("GMT"));
              String settime = dateFormat.format(date);
              hisys.getNetTime(settime);
              break;
            }catch (Exception e) {
                e.printStackTrace();
                count++;
                try{
                Thread.sleep(10000);
                }catch (Exception ee) {}
            }
         }
    }
}
