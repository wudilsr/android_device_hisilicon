package com.hisilicon.android.acceleratd.ageing;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.NetworkInfo.State;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.Parcelable;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.MediaController;
import android.widget.TextView;
import android.widget.VideoView;
import android.content.SharedPreferences;
import com.hisilicon.android.flashInfo.FlashInfo;
import com.hisilicon.android.sdkinvoke.HiSdkinvoke;
import com.hisilicon.android.mediaplayer.HiMediaPlayer;
import com.hisilicon.android.mediaplayer.HiMediaPlayer.OnCompletionListener;
import com.hisilicon.android.mediaplayer.HiMediaPlayer.OnErrorListener;
import com.hisilicon.android.mediaplayer.HiVideoView;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.io.InputStream;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.BitSet;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import java.util.regex.Pattern;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.BufferedOutputStream;
import java.text.MessageFormat;
import org.apache.http.conn.util.InetAddressUtils;

public class factorytestActivity extends Activity
{
    TextView CVBSAUDIOinfotext  = null;
    TextView CVBSVIDEOinfotext  = null;
    TextView GUANDQIANGinfotext = null;
    FlashInfo Getflashinfo = null;
    TextView HDMIAUDIOinfotext = null;
    TextView HDMIVIDEOinfotext = null;
    TextView Ledinfotext = null;
    private String TAG = "Factorytest";
    private IntentFilter WifiFilter = null;
    private IntentFilter USBsdcardFilter = null;
    private IntentFilter BootFilter = null;
    private static String BIN_DIR = "/data/local/";
    private static String CMD = "/data/local/memtest";

    private BroadcastReceiver WifiReceiver = new BroadcastReceiver()
    {
        public void onReceive(Context context, Intent intent)
        {
            if (WifiManager.WIFI_STATE_CHANGED_ACTION.equals(intent.getAction()))
            {
                int wifiState = intent.getIntExtra(WifiManager.EXTRA_WIFI_STATE, 0);
                Log.i(TAG, "wifiState:"+wifiState);
                switch (wifiState)
                {
                case WifiManager.WIFI_AP_STATE_ENABLED:
                    Log.i(TAG,"WifiManager.WIFI_STATE_ENABLED");
                    Connect(user, passwd);
                    break;
                case WifiManager.WIFI_STATE_DISABLED:
                    Log.i(TAG,"WifiManager.WIFI_STATE_DISABLED");
                    break;
                case WifiManager.WIFI_STATE_DISABLING:
                    break;
                }
            }
            if (WifiManager.NETWORK_STATE_CHANGED_ACTION.equals(intent.getAction()))
            {
                Parcelable parcelableExtra = intent.getParcelableExtra(WifiManager.EXTRA_NETWORK_INFO);
                if (null != parcelableExtra)
                {
                    NetworkInfo networkInfo = (NetworkInfo) parcelableExtra;
                    State state = networkInfo.getState();
                    boolean isConnected = state == State.CONNECTED;
                    Log.i(TAG, "isConnected:" + isConnected);
                    if (isConnected)
                    {
                        getWifiMacAddr();
                    }
                }
            }
            return;
        }
    };

    private BroadcastReceiver UsbBroadCastReceiver = new BroadcastReceiver()
    {
        public void onReceive(Context paramAnonymousContext, Intent paramAnonymousIntent)
        {
            String str = paramAnonymousIntent.getAction();

            if (str.equals("android.intent.action.MEDIA_MOUNTED"))
            {
                factorytestActivity.this.getusbinfo();
                factorytestActivity.this.isplayingvideo();
            }
            else if (str.equals("android.intent.action.MEDIA_UNMOUNTED"))
            {
                factorytestActivity.this.getusbinfo();
            }

            return;
        }
    };

    TextView YPbPrAUDIOinfotext = null;
    TextView YPbPrVIDEOinfotext = null;
    private int cont = 0;
    int count = 0;
    TextView eXPtext = null;
    private Handler handler = null;
    TextView hiveriontext = null;
    String ipAddress = null;
    private String mEXP = null;
    int mEoData = 1;
    private String mHiverion = null;
    private String mMacaddr = null;
    private String mSN = null;
    private String mSystemVersion = null;
    int mV8Data = 0;
    WifiInfo mWifiInfo = null;
    int m_infonum = 0;
    private static int time = 0;
    private List <String> msglist = new ArrayList();
    byte[] ret;
    String[] testvideoinfo = new String[2];
    String[] usb_numinfo = new String[10];
    private VideoView videoView = null;
    WifiManager wifiManager = null;
    private boolean wifiaddrflage = false;
    Button wifibutton = null;
    private Handler wifihandler = null;
    Button wifisignlebutton = null;
    private TimerTask wifitask = null;
    private Timer wifitimer = null;
    private String user   = null;
    private String passwd = null;
    HiVideoView localHiVideoView = null;

    private Handler mainHandler = new Handler()
    {
        public void handleMessage(Message message)
        {
            switch(message.what)
            {
            case 1:
                TextView localTextView = (TextView)findViewById(R.id.time);
                if(localHiVideoView.isPlaying())
                    time++;
                localTextView.setText(MessageFormat.format(
                   "{0,number,00}:{1,number,00}:{2,number,00}",
                   time / 60 / 60, time / 60 % 60, time % 60));
                break;
            case 100:
                factorytestActivity.this.getethernetAddr();
                break;
            }
            super.handleMessage(message);
        }
    };
    private void CVBSinfo()
    {
        this.CVBSVIDEOinfotext = ((TextView)findViewById(R.id.cvbsvideo));
        this.CVBSAUDIOinfotext = ((TextView)findViewById(R.id.cvbsaudio));
    }

    private WifiConfiguration CreateWifiInfo(String paramString1, String paramString2)
    {
        WifiConfiguration localWifiConfiguration = new WifiConfiguration();

        localWifiConfiguration.SSID = ("\"" + paramString1 + "\"");
        localWifiConfiguration.preSharedKey = ("\"" + paramString2 + "\"");
        localWifiConfiguration.hiddenSSID = true;
        localWifiConfiguration.status = 2;
        localWifiConfiguration.allowedGroupCiphers.set(2);
        localWifiConfiguration.allowedGroupCiphers.set(3);
        localWifiConfiguration.allowedKeyManagement.set(1);
        localWifiConfiguration.allowedPairwiseCiphers.set(1);
        localWifiConfiguration.allowedPairwiseCiphers.set(2);
        localWifiConfiguration.allowedProtocols.set(1);
        int i = this.wifiManager.addNetwork(localWifiConfiguration);
        Log.d("WifiPreference", "add Network returned " + i);
        boolean bool = this.wifiManager.enableNetwork(i, true);
        Log.d("WifiPreference", "enableNetwork returned " + bool);
        return localWifiConfiguration;
    }

    private void DisplayHiVersion_EXP()
    {
        /*this.hiveriontext = ((TextView)findViewById(R.id.hiversion));
        this.eXPtext = ((TextView)findViewById(R.id.expand));
        this.hiveriontext.setText(this.mHiverion);
        this.hiveriontext.setTextSize(18.0F);
        this.eXPtext.setText(this.mEXP);
        this.eXPtext.setTextSize(18.0F);*/
    }

    private void GUANDQIANGinfo()
    {}

    private void GetDeviceInfo()
    {
        this.mSystemVersion = Build.DISPLAY;
        this.mMacaddr = GetMacAddr();
        //this.mSN = GetSN();
        //this.mHiverion = GetHiVersion();
        //this.mEXP = GetEXP();
    }

    private void HDMIinfo()
    {
        this.HDMIVIDEOinfotext = ((TextView)findViewById(R.id.hdmivideo));
        ShowAlertDialog(this.HDMIVIDEOinfotext);
        this.HDMIAUDIOinfotext = ((TextView)findViewById(R.id.hdmiaudio));
    }

    private WifiConfiguration IsExsits()
    {
        List localList = this.wifiManager.getConfiguredNetworks();

        Log.v(this.TAG, "existingConfigs=" + localList);
        WifiConfiguration localWifiConfiguration = null;
        if (localList != null)
        {
            Iterator localIterator = localList.iterator();
            do
            {
                if (!localIterator.hasNext())
                {
                    break;
                }

                localWifiConfiguration = (WifiConfiguration)localIterator.next();
            }
            //} while (!localWifiConfiguration.SSID.equals("\"" + paramString + "\""));
            while (localWifiConfiguration.status != WifiConfiguration.Status.CURRENT);
        }
        else
        {
            localWifiConfiguration = null;
        }

        return localWifiConfiguration;
    }

    private boolean OpenWifi()
    {
        boolean bool = true;

        if (!this.wifiManager.isWifiEnabled())
        {
            bool = this.wifiManager.setWifiEnabled(true);
        }

        return bool;
    }

    private void ShowAlertDialog(TextView paramTextView)
    {}

    private void ShowFailedMeseage(TextView paramTextView)
    {
        paramTextView.setTextColor(-65536);
        paramTextView.setText(R.string.str_failed);
    }

    private void ShowPassMeseage(TextView paramTextView)
    {
        paramTextView.setTextColor(-1);
        paramTextView.setText(R.string.srt_pass);
    }

    private void Sninfo()
    {
        /*TextView localTextView = (TextView)findViewById(R.id.sn);

        localTextView.setTextSize(18.0F);
        localTextView.setText(this.mSN);*/
    }

    private void Systemversioninfo()
    {
        TextView localTextView = (TextView)findViewById(R.id.version);

        localTextView.setTextSize(16);
        this.mSystemVersion = Build.DISPLAY;
        localTextView.setText(this.mSystemVersion);
    }

    private void Traversalfile(File paramFile)
    {
        if (paramFile != null)
        {
            if (paramFile.isDirectory())
            {
                File[] arrayOfFile = paramFile.listFiles();
                if (arrayOfFile != null)
                {
                    for (int i = 0; i < arrayOfFile.length; i++)
                    {
                        Traversalfile(arrayOfFile[i]);
                    }
                }
            }
            else
            {
                searchfilefordevice(paramFile);
            }
        }
    }

    private void Traversaltestvideo(File paramFile)
    {
        if ((paramFile != null) && (!this.testvideoinfo[1].equals("1.avi")))
        {
            if (paramFile.isDirectory())
            {
                File[] arrayOfFile = paramFile.listFiles();
                if (arrayOfFile != null)
                {
                    for (int i = 0; i < arrayOfFile.length; i++)
                    {
                        Log.i(TAG, "arrayOfFile[i]:" + arrayOfFile[i]);
                        Traversaltestvideo(arrayOfFile[i]);
                    }
                }
            }
            else if ((1 != 0) && (paramFile.getName().equals("1.avi")))
            {
                this.testvideoinfo[0] = paramFile.getPath();
                this.testvideoinfo[1] = paramFile.getName();
                Log.v(TAG, "testvideoinfo testvideoinfo ok " + this.testvideoinfo[0]);
                System.out.println(paramFile.getPath());
            }
        }
    }

    private void YPbPrinfo()
    {
        this.YPbPrVIDEOinfotext = ((TextView)findViewById(R.id.ypbprvideo));
        this.YPbPrAUDIOinfotext = ((TextView)findViewById(R.id.ypbpraudio));
    }

    private void bootverioninfo()
    {
        TextView localTextView = (TextView)findViewById(R.id.model);

        localTextView.setTextSize(16);
        localTextView.setText(getProductAndBootVer());
        localTextView.requestFocus();
    }

    private boolean checkNet()
    {
        //((TextView)findViewById(2131034128));
        ConnectivityManager localConnectivityManager = (ConnectivityManager)getSystemService("connectivity");
        int i;

        if (localConnectivityManager != null)
        {
            NetworkInfo[] arrayOfNetworkInfo = localConnectivityManager.getAllNetworkInfo();
            if (arrayOfNetworkInfo != null)
            {
                i = 0;
                for (i = 0; i < arrayOfNetworkInfo.length; i++)
                {
                    if (arrayOfNetworkInfo[i].getState().equals(NetworkInfo.State.CONNECTED))
                    {
                        return true;
                    }
                }

                return false;
            }
        }

        return false;
    }

    private void closewifitimer(int paramInt, boolean paramBoolean)
    {
        if (paramBoolean)
        {
            this.wifitimer.cancel();
        }
        else if (paramInt > 20)
        {
            this.wifitimer.cancel();
            TextView localTextView = (TextView)findViewById(R.id.wifiip);
            localTextView.setTextColor(-65536);
            localTextView.setText("FAILED");
        }
    }

    private void copyToCache(String paramString, InputStream paramInputStream)
    {
        String BIN_DIR = getCacheDir().getPath() + "/";
        String str = BIN_DIR + paramString;
        File outFile = new File(str);
        if(outFile.exists())
        {
            Log.i(TAG, "copyToCache exists!");
            return;
        }
        BufferedOutputStream localBufferedOutputStream;
        try
        {
            Log.v(TAG, "start copy to cache");
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
                Log.v(TAG, "finish copy to cache" + i);
            }
        }
        catch (IOException localIOException)
        {
            localIOException.printStackTrace();
        }
    }

    private void factorytest()
    {
        try
        {
            copyToCache("10m.m2ts", getAssets().open("10m.m2ts"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        videoinfo();
        ledtestinfo();
        playtimer();
    }

    private String getEthernetMacAddr_extern()
    {
        TextView localTextView = (TextView)findViewById(R.id.netmacid);

        localTextView.setTextSize(16);
        localTextView.setText(this.mMacaddr);
        return null;
    }

    private String getProductAndBootVer()
    {
        Log.i(TAG, "getProductAndBootVer!");
        byte[] mBuffer = new byte[4 * 1024];
        try
        {
            FileInputStream in = new FileInputStream("/data/misc/cmdline");
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            int count = -1;
            while ((count = in.read(mBuffer, 0, 4 * 1024)) != -1)
            {
                out.write(mBuffer, 0, count);
            }

            mBuffer = null;

            String Result = new String(out.toByteArray(), "ISO-8859-1");
            Log.i(TAG, "Result:" + Result);
            in.close();
            return Result;
        } catch (java.io.FileNotFoundException e) {
            Log.i(TAG, "FileNotFoundException:" + e);
        } catch (java.io.IOException e) {
            Log.i(TAG, "IOException:" + e);
        }
        return null;
    }

    private void getWifiMacAddr()
    {
        TextView localTextView = (TextView)findViewById(R.id.wifimac);
        WifiInfo localWifiInfo = ((WifiManager)getSystemService("wifi")).getConnectionInfo();

        localTextView.setTextSize(16);
        localTextView.setText(localWifiInfo.getMacAddress());
    }

    private void getethernetAddr()
    {
        TextView localTextView = (TextView)findViewById(R.id.netip);

        localTextView.setTextSize(16);
        Thread.currentThread();
        String str = getLocalIpAddress();
        if ((str == null) && (this.count < 20))
        {
            Message localMessage = new Message();
            localMessage.what = 100;
            this.mainHandler.sendMessageDelayed(localMessage, 100L);
        }
        else
        {
            this.count = (1 + this.count);
            localTextView.setText(str);
            user   = getSharedPreferences("shared", Context.MODE_PRIVATE).getString("user", "HiABC");
            passwd = getSharedPreferences("shared", Context.MODE_PRIVATE).getString("passwd", "9988776655");
            Log.i(TAG, "user:" + user);
            Log.i(TAG, "passwd:" + passwd);
            if (user.equals("HiABC") && passwd.equals("9988776655"))
            {
                SharedPreferences.Editor editor = getSharedPreferences("shared", Context.MODE_PRIVATE).edit();
                editor.putString("user", "HiABC");
                editor.putString("passwd", "9988776655");
                editor.commit();
            }
            OpenWifi();
            Connect(user, passwd);
            //getWifiMacAddr();
        }
    }

    private void playtimer()
    {
        TimerTask task = new TimerTask()
        {
            public void run()
            {
                Message message = new Message();
                message.what = 1;
                mainHandler.sendMessage(message);
            }
        };
        Timer timer = new Timer(true);
        timer.schedule(task,1000, 1000);
    }
    private void getusbinfo()
    {
        TextView localTextView1 = (TextView)findViewById(R.id.usb1);
        TextView localTextView2 = (TextView)findViewById(R.id.usb2);
        TextView localTextView3 = (TextView)findViewById(R.id.usb3);
        TextView localTextView4 = (TextView)findViewById(R.id.sata);
        TextView localTextView5 = (TextView)findViewById(R.id.sdcard);
        TextView localTextView6 = (TextView)findViewById(R.id.network);
        File localFile = new File("/mnt" + File.separator);

        for (int i = 0; i < 10; i++)
        {
            this.usb_numinfo[i] = "0";
        }

        Traversalfile(localFile);
        this.m_infonum = 0;
        if (this.usb_numinfo[0].equals("usb1"))
        {
            this.m_infonum = (1 + this.m_infonum);
            localTextView1.setTextSize(20);
            localTextView1.setText("usb1");
            Log.v(TAG, "usb_numinfo usb1 ok " + this.usb_numinfo[0]);
            if (!this.usb_numinfo[1].equals("usb2"))
            {
                localTextView2.setText(" ");
                Log.v(TAG, "usb_numinfo usb2 fialed " + this.usb_numinfo[1]);
            }

            this.m_infonum = (1 + this.m_infonum);
            localTextView2.setText("usb2");
            localTextView2.setTextSize(20);
            Log.v(TAG, "usb_numinfo usb2 ok " + this.usb_numinfo[1]);
            if (!this.usb_numinfo[2].equals("usb3"))
            {
                localTextView3.setText(" ");
                Log.v(TAG, "usb_numinfo usb3 fialed " + this.usb_numinfo[2]);
            }

            this.m_infonum = (1 + this.m_infonum);
            localTextView3.setTextSize(20);
            localTextView3.setText("usb3");
            Log.v(TAG, "usb_numinfo usb3 ok " + this.usb_numinfo[2]);
            if (!this.usb_numinfo[3].equals("sata"))
            {
                localTextView4.setText(" ");
                Log.v(TAG, "usb_numinfo sata fialed " + this.usb_numinfo[3]);
            }

            this.m_infonum = (1 + this.m_infonum);
            localTextView4.setTextSize(20);
            localTextView4.setText("sata");
            Log.v(TAG, "usb_numinfo sata ok " + this.usb_numinfo[3]);
            if (!this.usb_numinfo[4].equals("sdcard"))
            {
                localTextView5.setText(" ");
                Log.v(TAG, "usb_numinfo sdcard fialed " + this.usb_numinfo[4]);
            }

            this.m_infonum = (1 + this.m_infonum);
            localTextView5.setText("sdcard");
            localTextView5.setTextSize(20);
            Log.v(TAG, "usb_numinfo sdcard ok " + this.usb_numinfo[4]);
            localTextView6.setTextSize(20);
            localTextView6.setText(Integer.toString(this.m_infonum));
            return;
        }
    }

    private boolean getwifiaddress()
    {
        this.mWifiInfo = this.wifiManager.getConnectionInfo();
        if (!longToIP(this.mWifiInfo.getIpAddress()).equals("0.0.0.0"))
        {
            TextView localTextView = (TextView)findViewById(R.id.wifiip);
            localTextView.setTextSize(16);
            localTextView.setText(longToIP(this.mWifiInfo.getIpAddress()));

            //((WifiManager)getSystemService("wifi"));
            int i = WifiManager.calculateSignalLevel(this.mWifiInfo.getRssi(), 5);
            Log.v(this.TAG, "wifi signle is:" + i);
            int j = this.mWifiInfo.getLinkSpeed();
            Log.v(this.TAG, "wifi speed is:" + j);
        }

        for (boolean bool = true;; bool = false)
        {
            return bool;
        }
    }

    private void gotowifiInit()
    {
        this.wifibutton.setOnClickListener(new View.OnClickListener()
                                           {
                                               public void onClick(View paramAnonymousView)
                                               {
                                                   factorytestActivity.this.OpenWifi();
                                                   factorytestActivity.this.startActivity(new Intent("android.settings.WIFI_SETTINGS"));
                                               }
                                           });
        this.wifisignlebutton.setOnClickListener(new View.OnClickListener()
                                                 {
                                                     public void onClick(View paramAnonymousView)
                                                     {
                                                         Intent localIntent = new Intent();

                                                         localIntent.setClassName("com.farproc.wifi.analyzer",
                                                                                  "com.farproc.wifi.analyzer.MainScreen");
                                                         factorytestActivity.this.startActivity(localIntent);
                                                     }
                                                 });
    }

    private void handlersendMessage(int paramInt)
    {
        Message localMessage = this.handler.obtainMessage();

        localMessage.arg1 = paramInt;
        this.handler.sendMessageDelayed(localMessage, paramInt);
    }

    private void isplayingvideo()
    {
        VideoView localVideoView = (VideoView)findViewById(R.id.VideoView01);

        System.out.println("CG LOG isplayingvideo.....\n");
        if (localVideoView.isPlaying())
        {
            System.out.println("CG LOG is playing video .....\n");
        }
        else
        {
            System.out.println("CG LOG is not playing video .....\n");
            videoinfo();
        }
    }

    private void ledtestinfo()
    {
        LEDThread.start = true;
        new LEDThread().start();
    }

    public static String longToIP(long paramLong)
    {
        StringBuffer localStringBuffer = new StringBuffer("");

        localStringBuffer.append(String.valueOf(paramLong & 0xFF));
        localStringBuffer.append(".");
        localStringBuffer.append(String.valueOf(0xFF & paramLong >> 8));
        localStringBuffer.append(".");
        localStringBuffer.append(String.valueOf(0xFF & paramLong >> 16));
        localStringBuffer.append(".");
        localStringBuffer.append(String.valueOf(0xFF & paramLong >> 24));
        return localStringBuffer.toString();
    }

    private String readFromFile(String paramString)
    throws IOException
    {
        BufferedReader localBufferedReader = new BufferedReader(new FileReader(paramString), 1024);

        try
        {
            String str = localBufferedReader.readLine();
            return str;
        }
        finally
        {
            localBufferedReader.close();
        }
    }

    private void searchfilefordevice(File paramFile)
    {
        if (paramFile.getName().equals("usb1.mpg"))
        {
            this.usb_numinfo[0] = "usb1";
        }

        if (paramFile.getName().equals("usb2.mpg"))
        {
            this.usb_numinfo[1] = "usb2";
        }

        if (paramFile.getName().equals("usb3.mpg"))
        {
            this.usb_numinfo[2] = "usb3";
        }

        if (paramFile.getName().equals("sata.mpg"))
        {
            this.usb_numinfo[3] = "sata";
        }

        if (paramFile.getName().equals("sdcard.mpg"))
        {
            this.usb_numinfo[4] = "sdcard";
        }
    }

    private void strlistinit()
    {
        this.msglist.add("0");
        this.msglist.add("HDMI��Ƶ���");
        this.msglist.add("HDMI��Ƶ���");
        this.msglist.add("YPbPr��Ƶ���");
        this.msglist.add("YPbPr��Ƶ���");
        this.msglist.add("CVBS��Ƶ���");
        this.msglist.add("CVBS��Ƶ���");
        this.msglist.add("������Ƶ���");
        this.msglist.add("LED��");
    }

    private void videoinfo()
    {
        localHiVideoView = (HiVideoView)findViewById(R.id.VideoView01);
        File localFile = new File("/mnt" + File.separator);

        for (int i = 0; i < 2; i++)
        {
            this.testvideoinfo[i] = "0";
        }

        Log.i(TAG, "localFile:" + localFile);

        //Traversaltestvideo(localFile);

        this.testvideoinfo[0] = getCacheDir().getPath()+"/10m.m2ts";
        if (!this.testvideoinfo[0].equals(getCacheDir().getPath()+"/10m.m2ts"))
        {
            System.out.println("CG LOG call is not 10m.m2ts .....\n");
        }
        else
        {
            Log.i(TAG, "begin play!");
            localHiVideoView.setVideoPath(this.testvideoinfo[0]);
            new MediaController(this);
            localHiVideoView.start();
            localHiVideoView.setOnCompletionListener(new HiMediaPlayer.OnCompletionListener()
                                                     {
                                                         public void onCompletion(HiMediaPlayer paramAnonymousHiMediaPlayer)
                                                         {
                                                             localHiVideoView.start();
                                                             System.out.println("CG LOG call restart testvideo .....\n");
                                                         }
                                                     });
            localHiVideoView.setOnErrorListener(new HiMediaPlayer.OnErrorListener()
                                                     {
                                                         public boolean onError(HiMediaPlayer mp, int what, int extra)
                                                         {
                                                             LEDThread.start = false;
                                                             HiSdkinvoke mSDKInvoke = new HiSdkinvoke();
                                                             mSDKInvoke.hiBitSet(0xF8000044,4,3,0x00);
                                                             mSDKInvoke.hiGpioBitSet(0xF8004000,3,1);
                                                             System.out.println("CG LOG call stop testvideo .....\n");
                                                             return true;
                                                         }
                                                     });
        }
    }

    public void CloseWifi()
    {
        this.mWifiInfo = this.wifiManager.getConnectionInfo();
        if (longToIP(this.mWifiInfo.getIpAddress()).equals("0.0.0.0"))
        {
            System.out.println("=====================wifi  return===============");
        }
        else
        {
            if (this.wifiManager.isWifiEnabled())
            {
                this.wifiManager.setWifiEnabled(false);
            }
        }
    }

    public boolean Connect(String paramString1, String paramString2)
    {
        /*boolean bool1 = OpenWifi();
        boolean bool2 = false;

        if (!bool1)
        {
            ;
        }
        else
        {*/
            WifiConfiguration localWifiConfiguration1 = CreateWifiInfo(paramString1, paramString2);
            boolean bool2 = false;
            if (localWifiConfiguration1 != null)
            {
                WifiConfiguration localWifiConfiguration2 = IsExsits();
                if (localWifiConfiguration2 != null)
                {
                    this.wifiManager.removeNetwork(localWifiConfiguration2.networkId);
                }

                int i = this.wifiManager.addNetwork(localWifiConfiguration1);
                bool2 = this.wifiManager.enableNetwork(i, true);
            }
        //}

        return bool2;
    }

    public void DisconnectWifi(int paramInt)
    {
        this.wifiManager.disableNetwork(paramInt);
        this.wifiManager.disconnect();
    }

    public String GetEXP()
    {
        String str = this.Getflashinfo.getFlashInfo(8192, 30);

        if (str == null)
        {
            str = "";
        }
        else
        {
            if (str.substring(0, 5).equals("�����"))
            {
                str = "";
            }
        }

        return str;
    }

    public String GetHiVersion()
    {
        String str = this.Getflashinfo.getFlashInfo(4096, 10);

        Log.i(TAG, "GetHiVersion:" + str);
        if (str == null)
        {
            str = "";
        }
        else
        {
            if (str.substring(0, 5).equals("�����"))
            {
                str = "";
            }
        }

        return str;
    }

    public String GetMacAddr()
    {
        String str = this.Getflashinfo.getFlashInfo(0, 18);

        Log.i(TAG, "GetMacAddr:" + str);
        if (str == null)
        {
            str = "";
        }

        return str;
    }

    public String GetSN()
    {
        String str = this.Getflashinfo.getFlashInfo(18, 25);

        Log.i(TAG, "GetSN:" + str);
        if (str == null)
        {
            str = "";
        }
        else
        {
            if (str.substring(0, 5).equals("�����"))
            {
                str = "";
            }
        }

        return str;
    }

    public String getLocalIpAddress()
    {
        try
        {
            for (Enumeration en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();)
            {
                NetworkInterface intf = (NetworkInterface)en.nextElement();
                for (Enumeration enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();)
                {
                    InetAddress inetAddress = (InetAddress)enumIpAddr.nextElement();
                    if (!inetAddress.isLoopbackAddress() && !inetAddress.isLinkLocalAddress())
                    {
                        return inetAddress.getHostAddress().toString();
                    }
                }
            }
        } catch (SocketException ex) {
            Log.e("IpAddress", ex.toString());
        }
        return null;
    }

    public void onCreate(Bundle paramBundle)
    {
        super.onCreate(paramBundle);
        getIntent().getExtras();
        requestWindowFeature(1);
        getWindowManager().getDefaultDisplay();
        getWindow().setFlags(1024, 1024);
        setContentView(R.layout.main);
        String chipVersion = HiSdkinvoke.getChipVersion();
        Log.i(TAG,"chipVersion:"+chipVersion);
        if(chipVersion.equals("Unknown chip ID"))
            finish();
    }

    protected void onPause()
    {
        super.onPause();

        if (this.videoView != null)
        {
            this.videoView.stopPlayback();
        }

        if (this.wifitimer != null)
        {
            this.wifitimer.cancel();
        }

        SharedPreferences.Editor editor = getSharedPreferences("shared", Context.MODE_PRIVATE).edit();
        editor.putInt("boot", 0);
        editor.commit();
    }

    protected void onDestroy()
    {
        super.onDestroy();
        /*if (this.UsbBroadCastReceiver != null)
        {
            unregisterReceiver(this.UsbBroadCastReceiver);
        }*/

        new SendledThread((byte)0).start();
        if (this.videoView != null)
        {
            this.videoView.stopPlayback();
        }

        if (this.wifitimer != null)
        {
            this.wifitimer.cancel();
        }
    }

    public boolean onKeyDown(int paramInt, KeyEvent paramKeyEvent)
    {
        if (paramInt == 4)
        {
            new SendledThread((byte)0).start();
            if (this.videoView != null)
            {
                this.videoView.stopPlayback();
            }

            if (this.wifitimer != null)
            {
                this.wifitimer.cancel();
            }

            finish();
        }

        return super.onKeyDown(paramInt, paramKeyEvent);
    }

    protected void onResume()
    {
        super.onResume();
        factorytest();
    }

    protected void onStop()
    {
        new SendledThread((byte)0).start();
        if (this.videoView != null)
        {
            this.videoView.stopPlayback();
        }

        super.onStop();
    }
}
