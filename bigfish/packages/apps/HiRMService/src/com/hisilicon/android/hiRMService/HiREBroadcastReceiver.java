package com.hisilicon.android.hiRMService;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.SystemProperties;
import android.util.Log;

import com.hisilicon.android.HiAoService;
import com.hisilicon.android.HiDisplayManager;

public class HiREBroadcastReceiver extends BroadcastReceiver {

    private static final String ACTION_WAKEUP = Intent.ACTION_QB_WAKE_UP;

    private static final String ACTION_RELOAD = Intent.ACTION_QB_PROP_RELOAD;

    private static final String ACTION_BOOT = Intent.ACTION_BOOT_COMPLETED;

    @Override
    public void onReceive(Context context, Intent intent) {
        if(SystemProperties.get("persist.sys.qb.enable","false").equals("true"))
        {
            Log.i("Qb","HiREBroadcastReceiver:"+intent);
            if (intent.getAction().equals(ACTION_BOOT)) {
                reloadDisplaySetting();
            }
            else if (intent.getAction().equals(ACTION_RELOAD)) {
                reloadAudioSetting();
            }
        }
    }

    public void reloadDisplaySetting()
    {
        Log.i("Qb","reloadDisplaySetting");
        HiDisplayManager reloadDisplayManager = new HiDisplayManager();

        reloadDisplayManager.reload();
    }
    public void reloadAudioSetting()
    {
        Log.i("Qb","reloadAudioSetting");
        HiAoService reloadAoService = new HiAoService();

        String HDMI = SystemProperties.get("persist.sys.audio.hdmi.output");
        String SPDIF = SystemProperties.get("persist.sys.audio.spdif.output");
        String BLUERAY = SystemProperties.get("persist.sys.audio.blueray");
        reloadAoService.setAudioOutput(1, Integer.parseInt(HDMI));
        reloadAoService.setAudioOutput(2, Integer.parseInt(SPDIF));
        reloadAoService.setBluerayHbr(Integer.parseInt(BLUERAY));
    }
}
