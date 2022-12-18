package com.hisilicon.testlog;

import android.app.Activity;
import android.os.Bundle;
import com.hisilicon.util.LogTool;

public class Sample_logActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        int level =  LogTool.getLogLevel();
        System.out.println("loglevel is "+ level);
        LogTool.e("test log, log level is error");
        LogTool.w("test log, log level is warn, but it will not show");
        LogTool.setLogLevel(LogTool.DEBUG);
        LogTool.w("test log, log level is  warn.");
        LogTool.i("test log, log level is info");
        LogTool.d("test log, log level is debug, but it will  show");

    }

    protected void onPause()
    {
        LogTool.d("test log,insert the function named onPause");
        finish();
        super.onPause();
        System.exit(0);

    }
}
