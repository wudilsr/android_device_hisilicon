package com.hisilicon.android.networkupgrade.activity;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
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

public class MemInfo extends Activity
{

    public static final String TAG = "MemInfo";

    private TextView mTermView;

    byte[] mBuffer = new byte[8 * 1024];

    
    public void readInfo()
    {
        StrictMode.ThreadPolicy savedPolicy = StrictMode.allowThreadDiskReads();
        try
        {
            FileInputStream in = new FileInputStream("/data/misc/cmdline");
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            int count = -1;
            while((count = in.read(mBuffer,0,8 * 1024)) != -1)
                out.write(mBuffer, 0, count);

            mBuffer = null;

            String Result = new String(out.toByteArray(),"ISO-8859-1");
            Log.i(TAG,"Result:"+Result);
            this.mTermView.setText(Result);
            in.close();
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
        setContentView(R.layout.meminfo);
        this.mTermView = ((TextView)findViewById(R.id.command_output));
        readInfo();
    }

    protected void onDestroy()
    {
        super.onDestroy();
    }
}
