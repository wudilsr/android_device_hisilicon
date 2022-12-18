package com.hisilicon.android.karaokesetting;

import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.ServiceManager;
import android.os.SystemProperties;
import android.util.Log;

public class HiKaraokeReceiver extends BroadcastReceiver {

    private static final String ACTION = Intent.ACTION_SCREEN_OFF;
    private static final String ACTIONBootCompleted = "android.intent.action.BOOT_COMPLETED";
		private WakeLock wakeLock = null;
    @Override
    public void onReceive(Context context, Intent intent) {

        if (intent.getAction().equals(ACTION)) {
           // Intent intent2 = new Intent();
           // intent2.setAction("com.hisilicon.sendPowerService");
           // context.sendBroadcast(intent2);
           // Log.i("liangguofu", "*************HiKaraokeReceiver*******接收到广播********");

		PowerManager pm = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
		wakeLock = pm.newWakeLock(PowerManager.SUSPEND_WAKE_LOCK, this.getClass().getCanonicalName());
            acquireWakeLock();
            String status = SystemProperties.get("persist.sys.karaoke.onoff");
            if(status.equals("ON"))
            {
		Common.micphone.stop();
                Common.micphone.release();
                SystemProperties.set("persist.sys.karaoke.onoff","OFF");
            }

            //wakeLock.release();
        }
        else if (intent.getAction().equals(ACTIONBootCompleted)) {
            MainService.initMICDate();
            if(Common.MIC_ONOFF.equals("ON"))
            {
                Common.KaraokOnOff = false;
                MainService.startMIC();
            }
        }
    }

    private void acquireWakeLock() {
        synchronized (wakeLock) {
            try {
                wakeLock.acquire();
            } catch (Exception e) {
                //Log.e(TAG, "exception in acquireWakeLock()", e);
            }
        }
    }

}
