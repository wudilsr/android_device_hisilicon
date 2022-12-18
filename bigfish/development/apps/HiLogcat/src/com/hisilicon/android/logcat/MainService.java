package com.hisilicon.android.logcat;

import java.io.File;
import java.io.IOException;

import android.app.Service;
import android.os.Binder;
import android.os.IBinder;
import android.os.Handler;
import android.os.Message;
import android.content.Intent;
import android.util.Log;

public class MainService extends Service {

    private static final String TAG = "HiLogcat";
    private IBinder binder = new MyBinder();
    private DumpLogcatHandler mDumpLogcatHandler;
    private static final int MSG_DUMP_LOGCAT = 1;

    private class DumpLogcatHandler extends Handler {
        private void dumpLogcat(){
            File destDir = new File("/tmp/capture/");
            if (!destDir.exists()) {
                Log.e(TAG, "/tmp/capture/ does not exist!");
                return;
            }

            Runtime runtime = Runtime.getRuntime();

            Log.d(TAG, "rm -rf logcat.txt*");
            try {
                runtime.exec("rm -rf logcat.txt*");
            } catch (IOException e) {
                e.printStackTrace();
            }

            Log.d(TAG, "logcat -v threadtime -f /tmp/capture/logcat.txt -r 2048 -n 1 &");
            try {
                runtime.exec("logcat -v threadtime -f /tmp/capture/logcat.txt -r 2048 -n 1 &");
            } catch (IOException e) {
                e.printStackTrace();
            }

            Log.d(TAG, "chmod 644 /tmp/capture/logcat.txt*");
            try {
                runtime.exec("chmod 644 /tmp/capture/logcat.txt*");
            } catch (IOException e) {
                e.printStackTrace();
            }

            Log.d(TAG, "Capture logs finished");
        }
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case MSG_DUMP_LOGCAT:
                    dumpLogcat();
                    break;
                default:
                    Log.d(TAG, "handle error message: " + msg.what);
                    break;
            }
        }
    }

    @Override
    public void onCreate() {
        super.onCreate();
        mDumpLogcatHandler = new DumpLogcatHandler();
        mDumpLogcatHandler.removeMessages(MSG_DUMP_LOGCAT);
        mDumpLogcatHandler.sendMessage(mDumpLogcatHandler.obtainMessage(MSG_DUMP_LOGCAT));
    }

    @Override
    public IBinder onBind(Intent arg0) {
        return binder;
    }

    public class MyBinder extends Binder {
        public MainService getService() {
            return MainService.this;
        }
    }

    @Override
    public void onStart(Intent intent, int startId) {
        super.onStart(intent, startId);
    }
}
