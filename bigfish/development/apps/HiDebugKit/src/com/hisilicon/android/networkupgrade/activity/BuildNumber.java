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

public class BuildNumber extends Activity
{

    public static final String TAG = "BuildNumber";

    private TextView mTermView1;
    private TextView mTermView2;
    private TextView mTermView3;
    private TextView mTermView4;
    private TextView mTermView5;

    byte[] mBuffer = new byte[8 * 1024];

    /*static
    {
        try
        {
            System.loadLibrary("SDKVersion");
        }
        catch(Exception e)
        {
            Log.e(TAG, "loadLibrary failed");
        }
    }*/

    public void readKernelVersion()
    {
        StrictMode.ThreadPolicy savedPolicy = StrictMode.allowThreadDiskReads();
        try
        {
            FileInputStream in = new FileInputStream("/proc/version");
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            int count = -1;
            while((count = in.read(mBuffer,0,8 * 1024)) != -1)
                out.write(mBuffer, 0, count);

            mBuffer = null;

            String Result2 = new String(out.toByteArray(),"ISO-8859-1");
            Log.d(TAG, "/proc/version:\n" + Result2);
            this.mTermView2.setText(Result2);
            in.close();
        }
        catch (java.io.FileNotFoundException e)
        {
            Log.e(TAG, "FileNotFoundException: " + e);
        }
        catch (java.io.IOException e)
        {
            Log.e(TAG, "IOException: " + e);
        }
        finally {
            StrictMode.setThreadPolicy(savedPolicy);
        }
    }
    public void onCreate(Bundle paramBundle)
    {
        super.onCreate(paramBundle);
        getWindow().setFlags(128, 128);
        setContentView(R.layout.buildnumber);
        String Result1 = SystemProperties.get("ro.build.version.release");
        this.mTermView1 = ((TextView)findViewById(R.id.command_output1));
        this.mTermView1.setText(Result1 + "\n");
        this.mTermView2 = ((TextView)findViewById(R.id.command_output2));
        readKernelVersion();
        /*String Result3 = GetSDKVersion();
        Log.i(TAG,"Result3:"+Result3);
        this.mTermView3 = ((TextView)findViewById(R.id.command_output3));
        this.mTermView3.setText(Result3 + "\n");*/
        this.mTermView4 = ((TextView)findViewById(R.id.command_output4));
        String Result4 = SystemProperties.get("ro.opengles.version");
        if (Result4.equals("65536")) {
            this.mTermView4.setText("OpenGL ES-CM 1.0\n");
        } else if (Result4.equals("65537")) {
            this.mTermView4.setText("OpenGL ES-CM 1.1\n");
        } else if (Result4.equals("131072")) {
            this.mTermView4.setText("OpenGL ES 2.0\n");
        } else if (Result4.equals("196608")) {
            this.mTermView4.setText("OpenGL ES 3.0\n");
        } else if (Result4.equals("196609")) {
            this.mTermView4.setText("OpenGL ES 3.1\n");
        } else {
            this.mTermView4.setText("Unknown\n");
        }
        String Result5 = SystemProperties.get("ro.build.display.id");
        this.mTermView5 = ((TextView)findViewById(R.id.command_output5));
        this.mTermView5.setText(Result5 + "\n");
    }

    protected void onDestroy()
    {
        super.onDestroy();
    }

    //native String GetSDKVersion();
}
