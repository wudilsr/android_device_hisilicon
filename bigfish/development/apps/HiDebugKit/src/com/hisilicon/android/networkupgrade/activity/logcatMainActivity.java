package com.hisilicon.android.networkupgrade.activity;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Map;
import com.hisilicon.android.networkupgrade.R;
import android.app.Activity;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.Preference;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class logcatMainActivity  extends Activity {
    public static final String TAG = "logcatMainActivity";

    private Button logcat_start = null ;
    private Button logcat_stop =null;

    Preference update_Local ;
    EditTextPreference update_Network;
    List<Map<String, String>> childList;
    private static final String LOGPATH = "/sdcard/logcat";
    String uuid = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // TODO Auto-generated method stub
        super.onCreate(savedInstanceState);
         setContentView(R.layout.logcat);

         logcat_start = (Button) findViewById(R.id.logcat_start);
         logcat_stop = (Button)findViewById(R.id.logcat_stop);
         logcat_start.setOnClickListener(new OnClickListener() {


        public void onClick(View v) {
        // TODO Auto-generated method stub
        new logcat_start_Thread(LOGPATH).start();
        logcat_start.setEnabled(false);
        }
        });
         logcat_stop.setOnClickListener(new OnClickListener() {
        public void onClick(View v) {
            Runtime runtime = Runtime.getRuntime();
            Log.d(TAG, "busybox killall logcat");
            try {
                runtime.exec("busybox killall logcat");
            } catch (IOException e) {
                e.printStackTrace();
            }

        new logcatclearThread().start();
        logcat_start.setEnabled(true);
        }
        });
    }

    @Override
    protected void onStart() {
        // TODO Auto-generated method stub
        super.onStart();
        SharedPreferences prf = getPreferences(MODE_PRIVATE);
        boolean b = prf.getBoolean("start_logcat_satus", true);
        logcat_start.setEnabled(b);
    }

    @Override
    protected void onStop() {
        // TODO Auto-generated method stub
        super.onStop();
        SharedPreferences prf = getPreferences(MODE_PRIVATE);
         Editor  e  = prf.edit();
         e.putString("filename",LOGPATH);
         e.putBoolean("start_logcat_satus", logcat_start.isEnabled());
         e.commit();
    }

    public boolean CheckUpdateFile(String path)
    {
        File file = new File(path);
        if(file.exists())
        {
        return true;
        }
        return false;
    }

    class logcat_start_Thread extends Thread{
        public logcat_start_Thread(String s){
        mstring = s;
        }
        private String mstring = null;
        @Override
        public void run() {
        // TODO Auto-generated method stub
        super.run();

        boolean  check = false;
        if(mstring != null)
        {
           check = CheckUpdateFile(mstring);
        }
        if(check){
        File file = new File(mstring);
        file.delete();
        }
        if(!CheckUpdateFile(mstring)){
        File file = new File(mstring);
        try{
        file.createNewFile();
        }catch (IOException e) {
        // TODO: handle exception
        e.printStackTrace();
        }
        }

            if(mstring != null){
                Runtime runtime = Runtime.getRuntime();
                Log.d(TAG, "logcat -f " + mstring + " &");
                try {
                    runtime.exec("logcat -f " + mstring + " &");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    class logcatclearThread extends Thread{
        @Override
        public void run() {
        // TODO Auto-generated method stub
        super.run();

            Runtime runtime = Runtime.getRuntime();
            Log.d(TAG, "logcat -c");
            try {
                runtime.exec("logcat -c");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

}
