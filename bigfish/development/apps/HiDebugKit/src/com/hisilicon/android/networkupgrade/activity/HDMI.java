package com.hisilicon.android.networkupgrade.activity;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.os.SystemProperties;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import android.view.KeyEvent;
import com.hisilicon.android.networkupgrade.R;
import com.hisilicon.android.hisysmanager.HiSysManager;

public class HDMI extends Activity
{
	
    public static final String TAG = "HDMI";

    private TextView mTermView;
    private HiSysManager mhisys;
    byte[] mBuffer = new byte[8 * 1024];

    public void readInfo()
    {
        StrictMode.ThreadPolicy savedPolicy = StrictMode.allowThreadDiskReads();
        try
        {
            FileInputStream in1 = new FileInputStream("/proc/msp/hdmi0_sink");
            FileInputStream in2 = new FileInputStream("/proc/msp/hdmi0");

            ByteArrayOutputStream out1 = new ByteArrayOutputStream();
            ByteArrayOutputStream out2 = new ByteArrayOutputStream();

            int count = -1;
            while((count = in1.read(mBuffer,0,8 * 1024)) != -1)
                out1.write(mBuffer, 0, count);

            while((count = in2.read(mBuffer,0,8 * 1024)) != -1)
                out2.write(mBuffer, 0, count);

            String Result1 = new String(out1.toByteArray(),"ISO-8859-1");
            Log.i(TAG,"Result1:"+Result1);
            String Result2 = new String(out2.toByteArray(),"ISO-8859-1");
            Log.i(TAG,"Result2:"+Result2);

            in1.close();
            in2.close();

            mhisys.readDebugInfo();
            FileInputStream in3 = new FileInputStream("/sdcard/tmp");
            ByteArrayOutputStream out3 = new ByteArrayOutputStream();
            while((count = in3.read(mBuffer,0,8 * 1024)) != -1)
                out3.write(mBuffer, 0, count);
            String Result3 = new String(out3.toByteArray(),"ISO-8859-1");
            Log.i(TAG, "Result3:" + Result3);
            in3.close();

            this.mTermView.setText(Result1 + Result2 + Result3);
        }
        catch (java.io.FileNotFoundException e)
        {
            Log.i(TAG,"FileNotFoundException:"+e);
        }
        catch (java.io.IOException e)
        {
            Log.i(TAG,"IOException:"+e);
        }
        finally {
            StrictMode.setThreadPolicy(savedPolicy);
        }
    }
    public void onCreate(Bundle paramBundle)
    {
        super.onCreate(paramBundle);
        getWindow().setFlags(128, 128);
        setContentView(R.layout.hdmi);
        mhisys = new HiSysManager();
        this.mTermView = ((TextView)findViewById(R.id.command_output));
        readInfo();
    }

    protected void onDestroy()
    {
        super.onDestroy();
    }
}
