package com.explorer.activity;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.IBinder;
import android.os.SystemClock;

import com.explorer.R;
import com.explorer.jni.SmbFunction;

public class SambaService extends Service {

    private MyApplication application;
    private boolean isStop = false;

    @Override
    public void onCreate() {
        application = (MyApplication) getApplication();
        super.onCreate();
    }

    @Override
    public IBinder onBind(Intent arg0) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (null == application.getSambaList()) {
            new Thread(new Runnable() {

                @Override
                public void run() {
                    while (!isStop) {
                        if (!checkNetWork()) {
                            SystemClock.sleep(30 * 1000);
                            continue;
                        }
                        List<HashMap<String, Object>> list = getSambaServer();
                        if (null == list) {
                            continue;
                        }
                        application.setSambaList(list);
                        SystemClock.sleep(5 * 60 * 1000);
                    }
                }
            }).start();
        }
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        isStop = true;
        super.onDestroy();
    }

    private List<HashMap<String, Object>> getSambaServer() {
        List<String> domainList = new ArrayList<String>();
        Integer num = Integer.valueOf(-1000000);
        int handle = SmbFunction.Samba_QueryDomainList(num);
        if (handle != 0) {
            for (int i = 0; i < num; i++) {
                String domain = SmbFunction.Samba_GetDomainList(handle, i);
                domainList.add(domain);
            }
            SmbFunction.Samba_freeHandle(handle);
        }

        List<HashMap<String, Object>> sambaList = null;
        for (String domain : domainList) {
            handle = SmbFunction.Samba_QueryServerList(num, domain);
            if (handle != 0) {
                sambaList = new ArrayList<HashMap<String, Object>>();
                for (int i = 0; i < num; i++) {
                    HashMap<String, Object> map = new HashMap<String, Object>();
                    String pcName = SmbFunction.Samba_GetServerList(handle, i);
                    String ip = SmbFunction.Samba_NetBiosName2Ip(pcName);
                    map.put("nick_name", pcName);
                    map.put("ip", ip);
                    map.put("infos", "No Details");
                    map.put("image", R.drawable.mainfile);
                    sambaList.add(map);
                }
            }
        }
        SmbFunction.Samba_freeHandle(handle);
        return sambaList;
    }

    private boolean checkNetWork() {
        ConnectivityManager connectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo info = connectivityManager.getActiveNetworkInfo();
        if (info != null && info.isAvailable())
            return true;
        return false;
    }
}
