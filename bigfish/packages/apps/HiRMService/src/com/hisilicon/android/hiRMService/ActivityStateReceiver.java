package com.hisilicon.android.hiRMService;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.view.IWindowManager;
import android.os.ServiceManager;
import android.os.RemoteException;
import android.util.Log;
import com.hisilicon.android.hisysmanager.HiSysManager;
public class ActivityStateReceiver extends BroadcastReceiver {
    HiSysManager hisys = new HiSysManager();
    IWindowManager mWindowManagerService = IWindowManager.Stub.asInterface(ServiceManager.getService("window"));
    String state, currentActivity, currentProcess;
    int ret;

    @Override
    public void onReceive(Context context, Intent intent) {
        String action = intent.getAction();
        if (action != null) {
            if (action.equals("android.ActivityState.CHANGE")) {
                state = intent.getStringExtra("activityState");
                currentActivity = intent.getStringExtra("currentClass");
                currentProcess = intent.getStringExtra("currentProcess");
                ret = hisys.setDynamicPolicy(state, currentActivity, currentProcess);
                try {
                    if (ret == 1) {
                        mWindowManagerService.setRotation(true);
                    } else {
                        mWindowManagerService.setRotation(false);
                    }
                } catch (RemoteException e) {
                    // TODO: handle exception
                }
            }
        }
    }
}
