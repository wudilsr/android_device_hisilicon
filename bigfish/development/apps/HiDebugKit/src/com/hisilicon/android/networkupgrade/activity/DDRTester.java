package com.hisilicon.android.networkupgrade.activity;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
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
import java.io.IOException;
import java.io.InputStream;
import android.view.KeyEvent;
import com.hisilicon.android.hisysmanager.HiSysManager;
import com.hisilicon.android.networkupgrade.R;

public class DDRTester extends Activity
{

  private static String BIN_DIR = "/data/local/";
  private static String CMD = "/data/local/memtest";
  private static String LOG_FILE = "/mnt/sdcard/memtest_log.txt";
  public static final String TAG = "DDRTester";
  private static Thread mOutput;
  private boolean done = true;
  private Button mBtnStart;
  private EditText mEditLoops;
  private EditText mEditMemSize;
  private Button mExit;
  private Handler mHandler = new Handler()
  {
    public void handleMessage(Message paramAnonymousMessage)
    {
		DDRTester.this.printToScreen();
    }
  };
  private FileOutputStream mLogOut;
  private int mLoops = 1;
  private int mMemSize = 128;
  private ScrollView mScroller;
  private FileInputStream mTermIn;
  private StringBuilder mTermStringBuilder;
  private TextView mTermView;
  int position = 0;

  private void copyToCache(String paramString, InputStream paramInputStream)
  {
    String str = BIN_DIR + paramString;
    BufferedOutputStream localBufferedOutputStream;
      try
      {
          Log.d(TAG, "start copy to cache");
          localBufferedOutputStream = new BufferedOutputStream(new FileOutputStream(str));
          byte arrayOfByte[] = new byte[524288];
          int i = 0;
          int j = paramInputStream.read(arrayOfByte);
          while(j>0)
          {
		  localBufferedOutputStream.write(arrayOfByte,0,j);
		  j = paramInputStream.read(arrayOfByte);
          }

          if (j <= 0)
          {
            paramInputStream.close();
            localBufferedOutputStream.close();
            Log.d(TAG, "finish copy to cache" + i);
          }
      }
      catch (IOException localIOException)
      {
        localIOException.printStackTrace();
      }

  }

  private void printToScreen()
  {
      String showText = this.mTermStringBuilder.toString();
      this.mTermView.setText(showText);
      this.mScroller.fullScroll(130);

      if(showText.contains("Done."))
      {
		  this.done = true;
      }

      if (!this.done)
      {
        this.mBtnStart.setEnabled(false);
        this.mExit.setEnabled(false);
      }
      else
      {
          this.mBtnStart.setEnabled(true);
          this.mExit.setEnabled(true);
      }
      return;
  }

  private void startListening() throws FileNotFoundException
  {
    Runnable local6 = new Runnable()
    {
      public void run()
      {
        while (true)
        {
		try {
		Thread.sleep(500);
		} catch (InterruptedException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
		}
          if (DDRTester.mOutput == null)
            return;
          if(DDRTester.this.mTermIn == null)
		  continue;
          try
          {
		byte[] mBuffer = new byte[4096];
            int i = DDRTester.this.mTermIn.read(mBuffer);
            if(i>0)
            {
		  for(int k=0;k<i;k++)
		  {
		      byte b = mBuffer[k];

		      if (b == 8 && DDRTester.this.mTermStringBuilder.length()>0)
		  DDRTester.this.mTermStringBuilder.deleteCharAt(-1 + DDRTester.this.mTermStringBuilder.length());
		      else if (b == 10)
		  DDRTester.this.mTermStringBuilder.append('\n');
		      else
		  DDRTester.this.mTermStringBuilder.append((char)b);

		  }

		DDRTester.this.mHandler.sendMessage(DDRTester.this.mHandler.obtainMessage(0));
            }
          }
          catch (IOException localIOException)
          {
            localIOException.printStackTrace();
          }
        }
      }
    };
    if (mOutput == null)
    {
      mOutput = new Thread(local6);
      mOutput.start();
      mOutput.setName("Output");
    }
  }

  public void onCreate(Bundle paramBundle)
  {
    super.onCreate(paramBundle);
    getWindow().setFlags(128, 128);
    setContentView(R.layout.case_memtest);
    BIN_DIR = getCacheDir().getPath() + "/";
    CMD = BIN_DIR + "memtest";

      try {
		copyToCache("memtest", getAssets().open("memtest"));
	} catch (IOException e1) {
		// TODO Auto-generated catch block
		e1.printStackTrace();
	}
      Runtime localRuntime = Runtime.getRuntime();
      try {
		localRuntime.exec("chmod 777 " + BIN_DIR + "memtest");
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}

      File localFile = new File(LOG_FILE);
      if (!localFile.exists())
      {
		try {
		localFile.createNewFile();
		} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
		}
      }
        try {
		this.mLogOut = new FileOutputStream(localFile);
		} catch (FileNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
		}

        this.mEditMemSize = ((EditText)findViewById(R.id.edit_memsize));
        this.mEditLoops = ((EditText)findViewById(R.id.edit_loops));
        this.mEditMemSize.setText(Integer.toString(this.mMemSize));
        this.mEditLoops.setText(Integer.toString(this.mLoops));
        this.mBtnStart = ((Button)findViewById(R.id.restart));
        this.mBtnStart.setOnClickListener(new View.OnClickListener()
        {
          public void onClick(View paramAnonymousView)
          {
            DDRTester.this.mTermStringBuilder = new StringBuilder();
            DDRTester.this.done = false;
            DDRTester.this.position = 0;
		DDRTester.this.mMemSize = Integer.parseInt(DDRTester.this.mEditMemSize.getEditableText().toString());
            DDRTester.this.mLoops = Integer.parseInt(DDRTester.this.mEditLoops.getEditableText().toString());
            String str1 = DDRTester.CMD;
            String str2 = str1 + " " + DDRTester.this.mMemSize + " " + DDRTester.this.mLoops
                    + " >> " + LOG_FILE + " &";
            String str3 = "echo \"" + str2  +"\" > " + LOG_FILE;
            Log.d(TAG, str3);
            HiSysManager hiSysManager = new HiSysManager();
            hiSysManager.adjustDevState(LOG_FILE, str2);

            try {
		DDRTester.this.mTermIn = new FileInputStream(LOG_FILE);
		} catch (FileNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
		}

                String cmd = str1 + " " + DDRTester.this.mMemSize + " " + DDRTester.this.mLoops;
                Log.d(TAG, str2);
                hiSysManager.ddrTest(cmd, LOG_FILE);
          }
        });
        this.mTermView = ((TextView)findViewById(R.id.command_output));
        this.mExit = ((Button)findViewById(R.id.exit));
        this.mExit.setOnClickListener(new View.OnClickListener()
        {
          public void onClick(View paramAnonymousView)
          {
                String str4 = "busybox killall memtest";
                Runtime runtime = Runtime.getRuntime();
                Log.d(TAG, str4);
                try {
                    runtime.exec(str4);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                finish();
          }
        });
        this.mScroller = ((ScrollView)findViewById(R.id.scroll));

        try {
		startListening();
		} catch (FileNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
		}
        this.mTermStringBuilder = new StringBuilder();
  }
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        switch (keyCode) {
        case KeyEvent.KEYCODE_BACK:
            return true;
		}
		return super.onKeyDown(KeyEvent.KEYCODE_ENTER, event);
	}
  protected void onDestroy()
  {
    super.onDestroy();
    if (this.mLogOut != null);
    try
    {
      this.mLogOut.close();
      mOutput = null;
      new File(BIN_DIR + "memtest").delete();
      try
      {
		if(this.mTermIn!=null)
		{
		this.mTermIn.close();
        }
        return;
      }
      catch (IOException localIOException1)
      {
        while (true)
          localIOException1.printStackTrace();
      }
    }
    catch (IOException localIOException2)
    {

    }
  }
}
