package com.hisilicon.android.networkupgrade.activity;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import com.hisilicon.android.hisysmanager.HiSysManager;
import com.hisilicon.android.networkupgrade.R;
import android.app.Activity;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.Preference;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.util.Log;

public class dmesgMainActivity  extends Activity
{
    public static final String TAG = "Dmesg";

    private Button dmesg_start = null;
    private Button dmesg_stop = null;

    private static final String LOGPATH = "/sdcard/dmesg";

    private TextView mTermView;

    private String Result = null;

    byte[] mBuffer = new byte[8 * 1024];

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dmesg);

        dmesg_start = (Button) findViewById(R.id.dmesg_start);
        this.mTermView = ((TextView)findViewById(R.id.command_output));
        dmesg_start.setOnClickListener(new OnClickListener()
                                       {
                                           public void onClick(View v)
                                           {
                                               new dmesg_start_Thread(LOGPATH).start();
                                               while (Result == null)
                                               {
                                                   try
                                                   {
                                                       Thread.sleep(1000);
                                                   } catch (java.lang.InterruptedException e) {
                                                       Log.i(TAG, "IOException:" + e);
                                                   }
                                               }

                                               mTermView.setText(Result);
                                           }
                                       });
    }

    @Override
    protected void onStart()
    {
        super.onStart();
    }

    @Override
    protected void onStop()
    {
        super.onStop();
    }

    public boolean CheckUpdateFile(String path)
    {
        File file = new File(path);

        if (file.exists())
        {
            return true;
        }

        return false;
    }

    class dmesg_start_Thread extends Thread
    {
        public dmesg_start_Thread(String s)
        {
            mstring = s;
        }
        private String mstring = null;
        @Override
        public void run()
        {
            super.run();

            boolean check = false;
            if (mstring != null)
            {
                check = CheckUpdateFile(mstring);
            }

            if (check)
            {
                File file = new File(mstring);
                file.delete();
            }

            if (!CheckUpdateFile(mstring))
            {
                File file = new File(mstring);
                try
                {
                    file.createNewFile();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            HiSysManager hiSysManager = new HiSysManager();
            Log.d(TAG, "dmesgMainActivity: dmesg > " + mstring);
            hiSysManager.readDmesg(mstring);

            try
            {
                FileInputStream in = new FileInputStream(mstring);
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                int count = -1;
                while ((count = in.read(mBuffer, 0, 8 * 1024)) != -1)
                {
                    out.write(mBuffer, 0, count);
                }

                mBuffer = null;

                Result = new String(out.toByteArray(), "ISO-8859-1");
                Log.i(TAG, Result);
                in.close();
            } catch (java.io.IOException e) {
                Log.i(TAG, "IOException:" + e);
            }
        }
    }
}
