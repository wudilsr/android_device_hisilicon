package com.hisilicon.android.errorreport;

import com.hisilicon.android.errorreport.util.SystemUiHider;

import android.annotation.TargetApi;
import android.app.Activity;
import android.app.ProgressDialog;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.os.SystemProperties;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.widget.EditText;
import android.util.Log;
import android.content.Context;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.Date;
import com.hisilicon.android.hisysmanager.HiSysManager;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 *
 * @see SystemUiHider
 */
public class FullscreenActivity extends Activity {
  /**
   * Whether or not the system UI should be auto-hidden after
   * {@link #AUTO_HIDE_DELAY_MILLIS} milliseconds.
   */
  private static final boolean AUTO_HIDE = true;

  /**
   * If {@link #AUTO_HIDE} is set, the number of milliseconds to wait after
   * user interaction before hiding the system UI.
   */
  private static final int AUTO_HIDE_DELAY_MILLIS = 1000;

  /**
   * If set, will toggle the system UI visibility upon interaction. Otherwise,
   * will show the system UI visibility upon interaction.
   */
  private static final boolean TOGGLE_ON_CLICK = true;

  /**
   * The flags to pass to {@link SystemUiHider#getInstance}.
   */
  private static final int HIDER_FLAGS = SystemUiHider.FLAG_HIDE_NAVIGATION;

  /**
   * The instance of the {@link SystemUiHider} for this activity.
   */
  private SystemUiHider mSystemUiHider;

       public static final String TAG = "sendEmail";

       private Button sendEmail = null;

       private EditText editTitleView = null;

       private EditText editContentView = null;

       private static ProgressDialog progressBar = null;

       private collectThread mThread = null;

       private String LogFile = null;//getCacheDir().getPath() + "/";

       private String ProcInfoFile = null;

       private String registerInfoFile = null;

       private String CacheDir = null;

       private File tmp = null;

       private String curDateStr;
  private HiSysManager mhisys;
       final Handler mHandler = new Handler() {
       public void handleMessage(Message msg) {
            switch (msg.what) {
            case 0:
                {
                    String path = (String)msg.obj;
                    Context mContext = FullscreenActivity.this;
                    progressBar = new ProgressDialog(mContext);
                    progressBar.setTitle(mContext.getString(R.string.app_name));
                    progressBar.setMessage(mContext.getString(R.string.collect));
                    progressBar.setCancelable(true);
                    progressBar.show();
                    mThread = new collectThread();
                    mThread.start();
                    break;
                }
            case 1:
                {
                    Context mContext = FullscreenActivity.this;
                    progressBar.setMessage(mContext.getString(R.string.send));
                    break;
                }
              case 2:
                {
                    int result = (int)msg.arg1;
                    Log.i(TAG,"send email result: "+result);
                    Context mContext = FullscreenActivity.this;
                    progressBar.dismiss();
                    if(result == 1)
                    {
                        Toast tmpToast = Toast.makeText(mContext, R.string.sendsuccess,Toast.LENGTH_SHORT);
                        tmpToast.show();
                    }
                    else if(result == 0)
                    {
                        Toast tmpToast = Toast.makeText(mContext, R.string.sendfailed,Toast.LENGTH_SHORT);
                        tmpToast.show();
                    }
                    break;
                }
            }
        }
       };
  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.activity_fullscreen);

    //final View controlsView = findViewById(R.id.fullscreen_content_controls);
    final View contentView = findViewById(R.id.fullscreen_content);

             //editTitleView = (EditText) findViewById(R.id.editTitleView);
             editContentView = (EditText) findViewById(R.id.editContentView);
             sendEmail = (Button) findViewById(R.id.emailButton);
             mhisys = new HiSysManager();
    // Set up an instance of SystemUiHider to control the system UI for
    // this activity.
    /*mSystemUiHider = SystemUiHider.getInstance(this, contentView,
        HIDER_FLAGS);
    mSystemUiHider.setup();
    mSystemUiHider
        .setOnVisibilityChangeListener(new SystemUiHider.OnVisibilityChangeListener() {
          // Cached values.
          int mControlsHeight;
          int mShortAnimTime;

          @Override
          @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
          public void onVisibilityChange(boolean visible) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
              // If the ViewPropertyAnimator API is available
              // (Honeycomb MR2 and later), use it to animate the
              // in-layout UI controls at the bottom of the
              // screen.
              if (mControlsHeight == 0) {
                mControlsHeight = controlsView.getHeight();
              }
              if (mShortAnimTime == 0) {
                mShortAnimTime = getResources().getInteger(
                    android.R.integer.config_shortAnimTime);
              }
              controlsView
                  .animate()
                  .translationY(visible ? 0 : mControlsHeight)
                  .setDuration(mShortAnimTime);
            } else {
              // If the ViewPropertyAnimator APIs aren't
              // available, simply show or hide the in-layout UI
              // controls.
              controlsView.setVisibility(visible ? View.VISIBLE
                  : View.GONE);
            }

            if (visible && AUTO_HIDE) {
              // Schedule a hide().
              delayedHide(AUTO_HIDE_DELAY_MILLIS);
            }
          }
        });*/

    // Set up the user interaction to manually show or hide the system UI.
    contentView.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View view) {
        /*if (TOGGLE_ON_CLICK) {
          mSystemUiHider.toggle();
        } else {
          mSystemUiHider.show();
        }*/
      }
    });

             sendEmail.setOnClickListener(new View.OnClickListener() {
                    @Override
      public void onClick(View view) {
             Log.i(TAG,"sendEmail");
                           Message msg = mHandler.obtainMessage(0);
                           mHandler.sendMessage(msg);
      }
             });
             sendEmail.setEnabled(true);
             sendEmail.requestFocus();

             CacheDir = getCacheDir().getPath() + "/";
    // Upon interacting with UI controls, delay any scheduled hide()
    // operations to prevent the jarring behavior of controls going away
    // while interacting with the UI.
    /*findViewById(R.id.dummy_button).setOnTouchListener(
        mDelayHideTouchListener);*/
  }

  @Override
  protected void onPostCreate(Bundle savedInstanceState) {
    super.onPostCreate(savedInstanceState);

    // Trigger the initial hide() shortly after the activity has been
    // created, to briefly hint to the user that UI controls
    // are available.
    delayedHide(100);
  }

       //final View controlsView = findViewById(R.id.fullscreen_content_controls);
  /**
   * Touch listener to use for in-layout UI controls to delay hiding the
   * system UI. This is to prevent the jarring behavior of controls going away
   * while interacting with activity UI.
   */
  View.OnTouchListener mDelayHideTouchListener = new View.OnTouchListener() {
    @Override
    public boolean onTouch(View view, MotionEvent motionEvent) {
      if (AUTO_HIDE) {
        delayedHide(AUTO_HIDE_DELAY_MILLIS);
      }
      return false;
    }
  };

  Handler mHideHandler = new Handler();
  Runnable mHideRunnable = new Runnable() {
    @Override
    public void run() {
      //mSystemUiHider.hide();
    }
  };

  /**
   * Schedules a call to hide() in [delay] milliseconds, canceling any
   * previously scheduled calls.
   */
  private void delayedHide(int delayMillis) {
    mHideHandler.removeCallbacks(mHideRunnable);
    mHideHandler.postDelayed(mHideRunnable, delayMillis);
  }

       private class collectThread extends Thread
       {
             public void run()
             {
                Log.i(TAG,"collectThread!");
                tmp = new File(getCacheDir().getPath()+ "/" + "loginfo");
                if(tmp.exists())
                {
                  tmp.delete();
                }
                tmp.mkdir();
                LogFile = tmp.getPath() + "/";
                ProcInfoFile = tmp.getPath() + "/";
                registerInfoFile = tmp.getPath() + "/";
                SimpleDateFormat   formatter   =   new   SimpleDateFormat   ("yyyy-MM-dd hh:mm:ss");
                Date curDate = new Date(System.currentTimeMillis());
                curDateStr = formatter.format(curDate);
                Log.i(TAG,"curDateStr: "+curDateStr);
                curDateStr = curDateStr.replace(" ", "_");
                LogFile += curDateStr+"_logcat.txt";
                ProcInfoFile += curDateStr+ "_procinfo.txt";
                registerInfoFile +=curDateStr+"_hdmi_register_info.txt";
                readAndroidVersion();
                readKernelVersion();
                readBootargsInfo();
                readMemInfo();
                readMediaMem();
                readGPUInfo();
                readDmesg();

                getProc();
                getHdmi();
                getHdmiSink();
                getDisp0();
                getDisp1();


                getAdec();
                getSound();
                mySleep();

                getAdec();
                getSound();
                mySleep();

                getAdec();
                getSound();
                mySleep();
                mhisys.registerInfo(registerInfoFile);
                readLogcat();
                Message msg = mHandler.obtainMessage(1);
                mHandler.sendMessage(msg);
                boolean result = sendEmail();
                if(result)
                    msg.arg1 = 1;
                else
                    msg.arg1 = 0;
                msg = mHandler.obtainMessage(2);
                mHandler.sendMessage(msg);
             }
       }

       public void readAndroidVersion()
       {
             try
             {
                    String Result = SystemProperties.get("ro.build.version.release");
                    Log.i(TAG,"AndroidVersion:" + Result);
                    FileWriter fw = new FileWriter(LogFile,true);
                    fw.write("AndroidVersion :\r\n"+Result+"\r\n\r\n");
                    fw.flush();
                    fw.close();
             }
             catch (java.io.FileNotFoundException e)
             {
                 Log.e(TAG,"FileNotFoundException:"+e);
             }
             catch (java.io.IOException e)
             {
                 Log.e(TAG,"IOException:"+e);
             }
       }

       public void readKernelVersion()
       {
             byte[] mBuffer = new byte[8 * 1024];

             StrictMode.ThreadPolicy savedPolicy = StrictMode.allowThreadDiskReads();
             try
             {
                 FileInputStream in = new FileInputStream("/proc/version");
                 ByteArrayOutputStream out = new ByteArrayOutputStream();
                 int count = -1;
                 while((count = in.read(mBuffer,0,8 * 1024)) != -1)
                        out.write(mBuffer, 0, count);

                 mBuffer = null;

                 String Result = new String(out.toByteArray(),"ISO-8859-1");
                 Log.i(TAG,"KernelVersion:" + Result);
                 in.close();
                 FileWriter fw = new FileWriter(LogFile,true);
                 fw.write("KernelVersion :\r\n"+Result+"\r\n\r\n");
                 fw.flush();
                 fw.close();
             }
             catch (java.io.FileNotFoundException e)
             {
                 Log.e(TAG,"FileNotFoundException:"+e);
             }
             catch (java.io.IOException e)
             {
                 Log.e(TAG,"IOException:"+e);
             }
             finally {
                 StrictMode.setThreadPolicy(savedPolicy);
             }
        }

        public void readBootargsInfo()
        {
             try
             {
                 Thread.sleep(1000);
             }
             catch (java.lang.InterruptedException e)
             {
                 Log.i(TAG,"IOException:"+e);
             }

             byte[] mBuffer = new byte[8 * 1024];

             StrictMode.ThreadPolicy savedPolicy = StrictMode.allowThreadDiskReads();
             try
             {
                 FileInputStream in = new FileInputStream("/data/misc/cmdline");
                 ByteArrayOutputStream out = new ByteArrayOutputStream();
                 int count = -1;
                 while((count = in.read(mBuffer,0,4 * 1024)) != -1)
                     out.write(mBuffer, 0, count);

                 mBuffer = null;

                 String Result = new String(out.toByteArray(),"ISO-8859-1");
                 Log.i(TAG,"BootargsInfo:"+Result);
                 in.close();
                 FileWriter fw = new FileWriter(LogFile,true);
                 fw.write("BootargsInfo :\r\n"+Result+"\r\n\r\n");
                 fw.flush();
                 fw.close();
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

        public void readMemInfo()
        {
            byte[] mBuffer = new byte[8 * 1024];

            StrictMode.ThreadPolicy savedPolicy = StrictMode.allowThreadDiskReads();
            try
            {
                FileInputStream in = new FileInputStream("/proc/meminfo");
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                int count = -1;
                while((count = in.read(mBuffer,0,8 * 1024)) != -1)
                    out.write(mBuffer, 0, count);

                mBuffer = null;

                String Result = new String(out.toByteArray(),"ISO-8859-1");
                Result = Result.replaceAll("\n","\r\n");
                Log.i(TAG,"MemInfo:"+Result);
                in.close();
                FileWriter fw = new FileWriter(LogFile,true);
                fw.write("MemInfo :\r\n"+Result+"\r\n\r\n");
                fw.flush();
                fw.close();
            }
            catch (java.io.FileNotFoundException e)
            {
                Log.e(TAG,"FileNotFoundException:"+e);
            }
            catch (java.io.IOException e)
            {
                Log.e(TAG,"IOException:"+e);
            }
            finally {
                StrictMode.setThreadPolicy(savedPolicy);
            }
        }

        public void readMediaMem()
        {
            byte[] mBuffer = new byte[8 * 1024];

            StrictMode.ThreadPolicy savedPolicy = StrictMode.allowThreadDiskReads();
            try
            {
                FileInputStream in = new FileInputStream("/proc/media-mem");
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                int count = -1;
                while((count = in.read(mBuffer,0,8 * 1024)) != -1)
                    out.write(mBuffer, 0, count);

                mBuffer = null;

                String Result = new String(out.toByteArray(),"ISO-8859-1");
                Result = Result.replaceAll("\n","\r\n");
                Log.i(TAG,"MediaMem:"+Result);
                in.close();
                FileWriter fw = new FileWriter(LogFile,true);
                fw.write("MediaMem :\r\n"+Result+"\r\n\r\n");
                fw.flush();
                fw.close();
            }
            catch (java.io.FileNotFoundException e)
            {
                Log.e(TAG,"FileNotFoundException:"+e);
            }
            catch (java.io.IOException e)
            {
                Log.e(TAG,"IOException:"+e);
            }
            finally {
                StrictMode.setThreadPolicy(savedPolicy);
            }
        }

        public void readGPUInfo()
        {
            Runtime runtime = Runtime.getRuntime();
            Log.d(TAG, "readGPUInfo(): mount -t debugfs debugfs /sys/kernel/debug");
            try {
                runtime.exec("mount -t debugfs debugfs /sys/kernel/debug");
            } catch (IOException e) {
                e.printStackTrace();
            }

            try
            {
                Thread.sleep(1000);
            }
            catch (java.lang.InterruptedException e)
            {
                Log.e(TAG,"IOException:"+e);
            }

            byte[] mBuffer = new byte[8 * 1024];

            StrictMode.ThreadPolicy savedPolicy = StrictMode.allowThreadDiskReads();
            try
            {
                FileInputStream in = new FileInputStream("/sys/kernel/debug/ion/ddr");
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                int count = -1;
                while((count = in.read(mBuffer,0,8 * 1024)) != -1)
                    out.write(mBuffer, 0, count);

                mBuffer = null;

                String Result = new String(out.toByteArray(),"ISO-8859-1");
                Result = Result.replaceAll("\n","\r\n");
                Log.i(TAG,"GPUInfo:"+Result);
                in.close();
                FileWriter fw = new FileWriter(LogFile,true);
                fw.write("GPUInfo :\r\n"+Result+"\r\n\r\n");
                fw.flush();
                fw.close();
            }
            catch (java.io.FileNotFoundException e)
            {
                Log.e(TAG,"FileNotFoundException:"+e);
            }
            catch (java.io.IOException e)
            {
                Log.e(TAG,"IOException:"+e);
            }
            finally {
                StrictMode.setThreadPolicy(savedPolicy);
            }
        }

        public void readMemLeak()
        {
            Runtime runtime = Runtime.getRuntime();
            Log.d(TAG, "readMemLeak(): mount -t debugfs debugfs /sys/kernel/debug");
            try {
                runtime.exec("mount -t debugfs debugfs /sys/kernel/debug");
            } catch (IOException e) {
                e.printStackTrace();
            }

            try
            {
                Thread.sleep(1000);
            }
            catch (java.lang.InterruptedException e)
            {
                Log.e(TAG,"IOException:"+e);
            }

            byte[] mBuffer = new byte[8 * 1024];

            StrictMode.ThreadPolicy savedPolicy = StrictMode.allowThreadDiskReads();
            try
            {
                FileInputStream in = new FileInputStream("/sys/kernel/debug/kmemleak");
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                int count = -1;
                while((count = in.read(mBuffer,0,8 * 1024)) != -1)
                    out.write(mBuffer, 0, count);

                mBuffer = null;

                String Result = new String(out.toByteArray(),"ISO-8859-1");
                Result = Result.replaceAll("\n","\r\n");
                Log.i(TAG,"MemLeak:"+Result);
                in.close();
                FileWriter fw = new FileWriter(LogFile,true);
                fw.write("MemLeak :\r\n"+Result+"\r\n\r\n");
                fw.flush();
                fw.close();
            }
            catch (java.io.FileNotFoundException e)
            {
                Log.e(TAG,"FileNotFoundException:"+e);
            }
            catch (java.io.IOException e)
            {
                Log.e(TAG,"IOException:"+e);
            }
            finally {
                StrictMode.setThreadPolicy(savedPolicy);
            }
        }

        public void readDmesg()
        {
            String dmesgFile = tmp.getPath() + "/dmesg";
            File file = new File(dmesgFile);
            if(file.exists())
                file.delete();

            Log.d(TAG, "readDmesg(): dmesg > " + dmesgFile);
            mhisys.readDmesg(dmesgFile);

            byte[] mBuffer = new byte[8 * 1024];

            try
            {
                FileInputStream in = new FileInputStream(dmesgFile);
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                int count = -1;
                while ((count = in.read(mBuffer, 0, 8 * 1024)) != -1)
                {
                    out.write(mBuffer, 0, count);
                }

                mBuffer = null;

                String Result = new String(out.toByteArray(), "ISO-8859-1");
                Result = Result.replaceAll("\n","\r\n");
                Log.i(TAG,"Dmesg:"+Result);
                in.close();
                FileWriter fw = new FileWriter(LogFile,true);
                fw.write("Dmesg :\r\n"+Result+"\r\n\r\n");
                fw.flush();
                fw.close();
            } catch (java.io.IOException e) {
                Log.i(TAG, "IOException:" + e);
            }
        }

        public void readLogcat()
        {
            String logcatFile ="/mnt/sdcard/logcat";
            File file = new File(logcatFile);
            if(file.exists())
                file.delete();
            Runtime runtime = Runtime.getRuntime();
            Log.d(TAG, "readLogcat(): logcat -f " + logcatFile + " &");
            try {
                runtime.exec("logcat -f " + logcatFile + " &");
            } catch (IOException e) {
                e.printStackTrace();
            }

            try
            {
                Thread.sleep(2000);
            }
            catch (java.lang.InterruptedException e)
            {
                Log.i(TAG,"IOException:"+e);
            }
            byte[] mBuffer = new byte[8 * 1024];

            try
            {
                FileInputStream in = new FileInputStream(logcatFile);
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                int count = -1;
                while ((count = in.read(mBuffer, 0, 8 * 1024)) != -1)
                {
                    out.write(mBuffer, 0, count);
                }

                mBuffer = null;

                String Result = new String(out.toByteArray(), "ISO-8859-1");
                Result = Result.replaceAll("\n","\r\n");
                //Log.i(TAG,"Logcat:"+Result);
                in.close();
                FileWriter fw = new FileWriter(LogFile,true);
                fw.write("Logcat :\r\n"+Result+"\r\n\r\n");
                fw.flush();
                fw.close();
            } catch (java.io.IOException e) {
                Log.i(TAG, "IOException:" + e);
            }

            Log.d(TAG, "readLogcat(): busybox killall logcat");
            try {
                runtime.exec("busybox killall logcat");
            } catch (IOException e) {
                e.printStackTrace();
            }

            try
            {
                Thread.sleep(2000);
            }
            catch (java.lang.InterruptedException e)
            {
                Log.i(TAG,"IOException:"+e);
            }
        }

        public boolean sendEmail()
        {
            //String mTitle = editTitleView.getText().toString();
            /*if(title != null && title.equals(""))
            {
                Toast tmpToast = Toast.makeText(FullscreenActivity.this, R.string.nulltitle,Toast.LENGTH_SHORT);
                tmpToast.show();
                return false;
            }*/
          String dest = tmp.getPath()+"/"+curDateStr+"_log.zip";
          ZipUtil.addFoldToZip(tmp.getPath(), dest);
            String mContent = editContentView.getText().toString();
            SendEmailClient sendEmailClient = new SendEmailClient();
       return sendEmailClient.sendEmailWithPart(dest,mContent);
        }

        public void getProc()
        {
            getInfo("/proc/msp/sys", ProcInfoFile, false);
        }

        public void getHdmi(){
            getInfo("/proc/msp/hdmi0", ProcInfoFile, true);
        }

        public void getHdmiSink(){
            getInfo("/proc/msp/hdmi0_sink", ProcInfoFile, true);
        }

        public void getDisp0(){
            getInfo("/proc/msp/disp0", ProcInfoFile, true);
        }

        public void getDisp1(){
            getInfo("/proc/msp/disp1", ProcInfoFile, true);
        }
        public void getAdec(){
            getInfo("/proc/msp/adec00", ProcInfoFile, true);
        }

        public void getSound(){
            getInfo("/proc/msp/sound0", ProcInfoFile, true);
        }

        private void getInfo(String procFilePath, String outFilePath, boolean append) {
            byte[] mBuffer = new byte[8 * 1024];

            StrictMode.ThreadPolicy savedPolicy = StrictMode.allowThreadDiskReads();
            try {
                FileInputStream in = new FileInputStream(procFilePath);
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                int count = -1;
                while((count = in.read(mBuffer, 0, 8 * 1024)) != -1)
                    out.write(mBuffer, 0, count);

                mBuffer = null;

                String Result = new String(out.toByteArray(), "ISO-8859-1");
                Result = Result.replaceAll("\n", "\r\n");
                Log.d(TAG, procFilePath + ": ");
                Log.d(TAG, Result);
                in.close();
                FileWriter fw = new FileWriter(outFilePath, append);
                fw.write(procFilePath + ":\r\n" + Result + "\r\n\r\n");
                fw.flush();
                fw.close();
            } catch (java.io.FileNotFoundException e) {
                Log.e(TAG, "FileNotFoundException:" + e);
            } catch (java.io.IOException e) {
                Log.e(TAG, "IOException:" + e);
            } finally {
                StrictMode.setThreadPolicy(savedPolicy);
            }
        }

        public void mySleep(){
            Runtime runtime = Runtime.getRuntime();
            Log.d(TAG, "mySleep(): sleep 0.5");
            try {
                runtime.exec("sleep 0.5");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }





}
