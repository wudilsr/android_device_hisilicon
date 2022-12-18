package com.hisilicon.android.hiRMService;

import java.util.ArrayList;
import java.util.List;
import java.io.File;
import java.io.IOException;
import java.util.Random;
import android.R.bool;
import android.app.ActivityManager;
import android.app.DownloadManager;
import android.app.Instrumentation;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.app.ActivityManager.RunningServiceInfo;
import android.app.ActivityManager.RunningTaskInfo;
import android.bluetooth.BluetoothAdapter;
import android.content.BroadcastReceiver;
import android.content.ContentResolver;
import android.content.Context;
import android.content.ContentResolver;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.FeatureInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.ResolveInfo;
import android.database.Cursor;
import android.database.ContentObserver;
import android.media.AudioManager;
import android.net.wifi.WifiManager;
import android.net.wifi.p2p.WifiP2pManager;
import android.net.ethernet.EthernetManager;
import android.net.EthernetDataTracker;
import android.net.pppoe.PppoeManager;
import android.net.NetworkInfo;
import android.net.NetworkInfo.DetailedState;
import android.os.Binder;
import android.os.Environment;
import android.os.Handler;
import android.os.IBinder;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.os.SystemClock;
import android.os.ServiceManager;
import android.os.SystemProperties;
import android.provider.Settings;
import android.util.Log;
import android.view.KeyEvent;
import android.content.pm.FeatureInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.database.Cursor;
import android.os.SystemProperties;
import com.hisilicon.android.HiAoService;
import com.hisilicon.android.HiDisplayManager;
import com.hisilicon.android.sdkinvoke.HiSdkinvoke;
import android.os.IBinder;
import android.os.StrictMode;
import android.os.INetworkManagementService;
import android.os.ServiceManager;
import com.android.internal.app.IUsageStats;
import java.net.URL;
import java.net.URLConnection;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimeZone;
import com.android.internal.os.PkgUsageStats;
import java.io.FileOutputStream;
import java.io.InputStream;
import com.hisilicon.android.hisysmanager.HiSysManager;

public class HiRMService extends Service {

    private static final String TAG = "HiRMService";
    private static final boolean DEBUG = false;
    static final String SMART_SUSPEND_ENTER = "smart_suspend_broadcast_enter";
    static final String SMART_SUSPEND_QUIT = "smart_suspend_broadcast_quit";
    static final String PACKAGE_SKYPLAY = "com.abc.airplay.player";
    static final String PACKAGE_SUYINGAPK = "com.android.smart.terminal.iptv";
    static final String PACKAGE_SUYINGAIDL = "com.android.smart.terminal.iptv.aidl";
    public final String SIGN_ID = "persist.sys.instructions.id";

    static final String CHIP_98C = "type=HI_CHIP_TYPE_HI3798C;version=HI_CHIP_VERSION_V100";
    static final String CHIP_98M = "type=HI_CHIP_TYPE_HI3798M;version=HI_CHIP_VERSION_V100";

    static final int AOSERVICE_ON = 0;
    static final int AOSERVICE_OFF = 1;

    private static final String DEFAULT_SCREEN_RATIO = "default_screen_ratio";
    private static final String DEFAULT_PLAYER_QUALITY = "default_player_quality";
    private static final String CONTENT_URI = "content://settings/secure";
    private WakeLock wakeLock = null;
    private Handler mHandler;
    private HandlerThread mThread;
    private WifiManager mWifiManager;
    private WifiP2pManager mWifiP2pManager;
    private WifiP2pManager.Channel mWifiP2pChannel;
    private EthernetManager mEthManager;
    private AudioManager mAudioManager;
    private BluetoothAdapter mLocalAdapter;
    private HiAoService mAoService;
    private HiDisplayManager mDisplay;
    private SuspendMode mWifiMode, mEthMode, mBluetoothMode, mWifiapMode;
    private boolean phy_link = true;
    private boolean wifiP2pStatusOn = false;
    private int smartSuspendFlag = -1;
    private IntentFilter intentFilter;

    private ParamObserver mParamObserver;
    private static final int WIFI_DISABLED = 0;
    private static final int WIFI_ENABLED = 1;

	private static final int EVENT_PARAM_CHANGED = 0;

    private static final int SMARTFLAG_AWAKE = 0;
    private static final int SMARTFLAG_SUSPEND = 1;
    private static final int SMARTSUSPEND_DELAY = 2 * 1000;
    private static final int PRIORITY_MAX = 1000;

    private SystemUpgrade mSystemUpgrade;
    private LogoUpgrade mLogoUpgrade;
    private FastplayUpgrade mFastplayUpgrade;
    private AnimationUpgrade mAnimationUpgrade;
    private DownloadManager mDownloadManager;

    private String launchName = null;

    private static final String RUNTIME = "persist.sys.instructions.time";
    private DBAdapter adapter;
    private boolean stopService;
    private IUsageStats mUsageStatsService;
    private List<AppEntity> nowStats;
    private List<AppEntity> lastStats;
    private List<AppEntity> changeStats;
    private HiSysManager mhisys;
    private final BroadcastReceiver mPowerReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Intent home = new Intent(Intent.ACTION_MAIN);
            home.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            home.addCategory(Intent.CATEGORY_HOME);
            String message;
            if (intent.getAction().equals(Intent.ACTION_SCREEN_OFF)) {
                if(DEBUG) {
                    Log.w(TAG, "ACTION_SCREEN_OFF");
                }
                if(smartSuspendFlag == SMARTFLAG_SUSPEND)
                    return;
                startActivity(home);
                acquireWakeLock();
                mhisys.adjustDevState("/proc/msp/hdmi0","oe 0");
                mhisys.adjustDevState("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor","userspace");
                removeUpgrade();
                killApp();
//                message = "system busybox killall cp";
//                writeSocket(message);
                if(DEBUG) {
                    Log.d(TAG, "after forceStopPackage");
                }
                if(SystemProperties.get("ro.thirdparty.dhcp").equals("true")) {
                    releaseLock();
                } else {
                    prepareSuspend();

                    if (!mWifiMode.getEnableFlag() && !mEthMode.getEnableFlag()
                            && !mBluetoothMode.getEnableFlag() && !mWifiapMode.getEnableFlag()) {
                            releaseLock();
                    }
                    abortBroadcast();
                }
            } else if (intent.getAction().equals(Intent.ACTION_SCREEN_ON)) {
		if(smartSuspendFlag == SMARTFLAG_AWAKE)
                   return ;
                refreshTimeThread t = new refreshTimeThread();
                t.start();
                downloadUpgrade();
                ActivityManager am = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
                if (launchName != null) {
                    am.forceStopPackage(launchName);
                }
                if(SystemProperties.get("ro.thirdparty.dhcp").equals("false")) {
                    prepareResume();
                }
                if(CHIP_98C.equals(HiSdkinvoke.getChipVersion())){
                    mhisys.doInitSh(0);
                } else {
                    mhisys.doInitSh(0);
                }
                if(SystemProperties.get("ro.thirdparty.dhcp").equals("false")) {
                    registerReceiver(mNetReceiver, intentFilter);
                    abortBroadcast();
                }
            } else if (intent.getAction().equals(SMART_SUSPEND_ENTER)) {
                //startActivity(home);
                if (smartSuspendFlag !=SMARTFLAG_SUSPEND) {
                    smartSuspendFlag = SMARTFLAG_SUSPEND;
                    //killApp();
                    int audiotype = mAudioManager.getMode();
                    mAudioManager.setStreamMute(audiotype, true);
                    mAoService.setEnterSmartSuspend(AOSERVICE_OFF);
                    if (wifiP2pStatusOn && mWifiP2pChannel != null) {
                        mWifiP2pManager
                                .removeGroup(
                                        mWifiP2pChannel,
                                        new wifiActionListener(
                                                wifiActionListener.ACTION_ID_DISCONNECT_P2P));
                    } else {
                        //SystemClock.sleep(SMARTSUSPEND_DELAY);
                       mhisys.enterSmartStandby();
                    }
                    Intent Fintent = new Intent(Intent.ACTION_SCREEN_OFF);
                    context.sendBroadcast(Fintent);
                    Log.d(TAG, "sendBroadcast  ACTION_SCREEN_OFF");
                } else {
                    smartSuspendFlag = SMARTFLAG_AWAKE;
                    mhisys.quitSmartStandby();
                    int audiotype = mAudioManager.getMode();
                    mAudioManager.setStreamMute(audiotype, false);
                    mAoService.setEnterSmartSuspend(AOSERVICE_ON);
                    Intent Fintent = new Intent(Intent.ACTION_SCREEN_ON);
                    context.sendBroadcast(Fintent);
                    Log.d(TAG, "sendBroadcast  ACTION_SCREEN_ON");
                }
            } else if (intent.getAction().equals(SMART_SUSPEND_QUIT)
                    && smartSuspendFlag == SMARTFLAG_SUSPEND) {
                mhisys.quitSmartStandby();
                int audiotype = mAudioManager.getMode();
                    mAudioManager.setStreamMute(audiotype, false);
                Intent Fintent = new Intent(Intent.ACTION_SCREEN_ON);
                context.sendBroadcast(Fintent);
                mAoService.setEnterSmartSuspend(AOSERVICE_ON);
            }
        }
    };

    private final BroadcastReceiver mNetReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent.getAction()
                    .equals(WifiManager.WIFI_STATE_CHANGED_ACTION)) {
                if (mWifiMode.getEnableFlag()
                        && (mWifiManager.getWifiState() == WifiManager.WIFI_STATE_DISABLED)) {
                    mWifiMode.setLockFlag(false);
                        final ContentResolver cr = getContentResolver();
                        Settings.Global.putInt(cr, Settings.Global.WIFI_ON,
                                WIFI_ENABLED);
                        releaseLock();
                    }
                return;
            }
            if (intent.getAction().equals(
                    WifiManager.WIFI_AP_STATE_CHANGED_ACTION)) {
                if (mWifiapMode.getEnableFlag()
                        && (mWifiManager.getWifiApState() == WifiManager.WIFI_AP_STATE_DISABLED)) {
                    mWifiapMode.setLockFlag(false);
                        final ContentResolver cr = getContentResolver();
                        Settings.Global.putInt(cr, Settings.Global.WIFIAP_ON,
                                WIFI_ENABLED);
                        releaseLock();
                    }
                return;
            }
            if (intent.getAction().equals(
                    WifiP2pManager.WIFI_P2P_CONNECTION_CHANGED_ACTION)) {
                NetworkInfo info = (NetworkInfo) intent
                        .getParcelableExtra(WifiP2pManager.EXTRA_NETWORK_INFO);
                if (DetailedState.CONNECTED == info.getDetailedState()) {
                    wifiP2pStatusOn = true;
                } else {
                    wifiP2pStatusOn = false;
                }
                return;
            }
            if (intent.getAction().equals(
                    EthernetManager.ETHERNET_STATE_CHANGED_ACTION)) {
                int message = intent.getIntExtra(
                        EthernetManager.EXTRA_ETHERNET_STATE, -1);
                if (message == EthernetManager.EVENT_PHY_LINK_DOWN) {
                    phy_link = false;
                } else if (message == EthernetManager.EVENT_PHY_LINK_UP) {
                    phy_link = true;
                }
                if (mEthMode.getEnableFlag()
                        && (mEthManager.getEthernetState() == EthernetManager.ETHERNET_STATE_DISABLED)) {
                    mEthMode.setLockFlag(false);
                        releaseLock();
                    }
                return;
            }

            if (intent.getAction().equals(
                    PppoeManager.PPPOE_STATE_CHANGED_ACTION)) {
                if (mEthMode.getEnableFlag()
                        && (mEthManager.getEthernetState() == EthernetManager.ETHERNET_STATE_DISABLED)) {
                    mEthMode.setLockFlag(false);
                        releaseLock();
                    }
                return;
            }

            if (intent.getAction()
                    .equals(BluetoothAdapter.ACTION_STATE_CHANGED)) {
                int state = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE,
                        BluetoothAdapter.ERROR);
                if (mBluetoothMode.getEnableFlag() && state == BluetoothAdapter.STATE_OFF) {
                    mBluetoothMode.setLockFlag(false);
                        releaseLock();
                }
            }
        }
    };

    private final BroadcastReceiver mUpdateReceiver = new BroadcastReceiver() {

        @Override
        public void onReceive(Context context, Intent intent) {

            long completeDownloadId = intent.getLongExtra(
                    DownloadManager.EXTRA_DOWNLOAD_ID, -1);
            DownloadManager.Query query = new DownloadManager.Query();
            query.setFilterById(completeDownloadId);
            Cursor c = mDownloadManager.query(query);
            if (c.moveToFirst()) {
                int status = c.getInt(c
                        .getColumnIndex(DownloadManager.COLUMN_STATUS));
                switch (status) {
                case DownloadManager.STATUS_SUCCESSFUL:
                    try {
                        if(DEBUG) {
                            Log.d(TAG, "DownloadManager.STATUS_SUCCESSFUL");
                        }
                        String message;
                        if (completeDownloadId == mSystemUpgrade
                                .getDownloadID_zip()) {
                            Intent upgrade = new Intent(HiRMService.this,
                                    UpgradeActivity.class);
                            upgrade.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                            upgrade.putExtra("info", mSystemUpgrade.getInfo());
                            upgrade.putExtra("path",
                                    mSystemUpgrade.getSdcardPath());
                            startActivity(upgrade);
                        } else if (completeDownloadId == mLogoUpgrade
                                .getDownloadID()) {
                            mhisys.writeRaw("logo","/mnt/sdcard/logo.img");
                            writeAndRemove(mLogoUpgrade);
                        } else if (completeDownloadId == mFastplayUpgrade
                                .getDownloadID()) {
                            mhisys.writeRaw("fastplay","/mnt/sdcard/fastplay.img");
                            writeAndRemove(mFastplayUpgrade);
                        } else if (completeDownloadId == mAnimationUpgrade
                                .getDownloadID()) {
                            try{
                               Runtime.getRuntime().exec("cp /mnt/sdcard/bootanimation.zip /data/local/bootanimation.zip");
                            }catch (IOException e) {
                            }
                            writeAndRemove(mAnimationUpgrade);
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    break;
                case DownloadManager.STATUS_FAILED:
                case DownloadManager.STATUS_PAUSED:
                case DownloadManager.STATUS_PENDING:
                    if (completeDownloadId == mSystemUpgrade
                            .getDownloadID_zip()) {
                        mDownloadManager.remove(mSystemUpgrade
                                .getDownloadID_zip());
                    } else if (completeDownloadId == mLogoUpgrade
                            .getDownloadID()) {
                        mDownloadManager.remove(mLogoUpgrade.getDownloadID());
                    }
                    break;
                case DownloadManager.STATUS_RUNNING:
                default:
                    break;
                }
            }
            c.close();
        }
    };

    private void writeAndRemove(Upgrade upgrade) {
            upgrade.setVersion(upgrade.getReleaseTime());
            mDownloadManager.remove(upgrade.getDownloadID());
        }

    public void onCreate() {
        mhisys= new HiSysManager();
        refreshTimeThread t = new refreshTimeThread();
        t.start();
        PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
        mDownloadManager = (DownloadManager) getSystemService(DOWNLOAD_SERVICE);
        wakeLock = pm.newWakeLock(PowerManager.SUSPEND_WAKE_LOCK, this
                .getClass().getCanonicalName());
        mWifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
        mWifiP2pManager = (WifiP2pManager) getSystemService(Context.WIFI_P2P_SERVICE);
        if (mWifiP2pManager != null) {
            mWifiP2pChannel = mWifiP2pManager.initialize(this,
                    this.getMainLooper(), new WfdChannelListener());
        }
        mEthManager = (EthernetManager) getSystemService(Context.ETHERNET_SERVICE);
        mAudioManager = (AudioManager) getSystemService(AUDIO_SERVICE);
        mLocalAdapter = BluetoothAdapter.getDefaultAdapter();
        mAoService = new HiAoService();
        mDisplay = new HiDisplayManager();

        mSystemUpgrade = new SystemUpgrade(getApplicationContext(),
                mDownloadManager);
        mLogoUpgrade = new LogoUpgrade(getApplicationContext(),
                mDownloadManager);
        mFastplayUpgrade = new FastplayUpgrade(getApplicationContext(),
                mDownloadManager);
        mAnimationUpgrade = new AnimationUpgrade(getApplicationContext(),
                mDownloadManager);
        mWifiMode = new SuspendMode();
        mEthMode = new SuspendMode();
        mWifiapMode = new SuspendMode();
        mBluetoothMode = new SuspendMode();

        if("shcmcc".equals(SystemProperties.get("ro.product.target"))){
            mThread = new HandlerThread(TAG);
            mThread.start();
            mHandler = new MyHandler(mThread.getLooper());
        }

        IntentFilter powerIntentFilter = new IntentFilter();
        powerIntentFilter.addAction(Intent.ACTION_SCREEN_ON);
        powerIntentFilter.addAction(Intent.ACTION_SCREEN_OFF);
        powerIntentFilter.addAction(SMART_SUSPEND_ENTER);
        powerIntentFilter.addAction(SMART_SUSPEND_QUIT);
        powerIntentFilter.setPriority(PRIORITY_MAX);
        registerReceiver(mPowerReceiver, powerIntentFilter);

        intentFilter = new IntentFilter();
        intentFilter.addAction(WifiManager.NETWORK_STATE_CHANGED_ACTION);
        intentFilter.addAction(WifiManager.WIFI_STATE_CHANGED_ACTION);
        intentFilter.addAction(WifiManager.WIFI_AP_STATE_CHANGED_ACTION);
        intentFilter
                .addAction(WifiP2pManager.WIFI_P2P_CONNECTION_CHANGED_ACTION);
        intentFilter.addAction(PppoeManager.PPPOE_STATE_CHANGED_ACTION);
        intentFilter.addAction(EthernetManager.ETHERNET_STATE_CHANGED_ACTION);
        intentFilter.addAction(BluetoothAdapter.ACTION_STATE_CHANGED);
        if(SystemProperties.get("ro.thirdparty.dhcp").equals("false")) {
            registerReceiver(mNetReceiver, intentFilter);
        }

        registerReceiver(mUpdateReceiver, new IntentFilter(
                DownloadManager.ACTION_DOWNLOAD_COMPLETE));
		doInitSh();
		adapter = new DBAdapter(this);

        mUsageStatsService = IUsageStats.Stub.asInterface(ServiceManager.getService("usagestats"));
        HiSdkinvoke sdkInvoke = new HiSdkinvoke();

        String SIGN_ID = "persist.sys.instructions.id";
        String NET_MAC="persist.sys.net.mac";
        String mSn=null;
        //mSn = SystemProperties.get(SIGN_ID);
        /*if(mSn==null||"".equals(mSn))
        {
			int lock = sdkInvoke.otpGetLock();
			if(lock==1)
			{
				mSn = sdkInvoke.otpGetLotID();//19λ
			}
			else
			{
                Random r = new Random();
                mSn = "" + r.nextLong();
                int length = mSn.length();
                if (length > 9) {
                    mSn = mSn.substring(length - 10, length - 1);
                }
                sdkInvoke.otpSetLotID(mSn);//9λ
				mSn = sdkInvoke.otpGetLotID();//19λ
            }
            SystemProperties.set(SIGN_ID,mSn);
        }*/
		mSn = sdkInvoke.otpGetLotID();//19λ
		SystemProperties.set(SIGN_ID,mSn);
        SystemProperties.set(NET_MAC,getLocalMacAddress());

        if("shcmcc".equals(SystemProperties.get("ro.product.target"))){
            mParamObserver = new ParamObserver(mHandler, EVENT_PARAM_CHANGED);
            mParamObserver.observe(this);
        }

        super.onCreate();
    }
    class refreshTimeThread extends Thread{
        public void run(){
               getNetTime();
           }
        }
    public void getNetTime(){
        int count = 1;
        while(count < 13)
        {
           try
            {
              URL url = new URL("http://www.baidu.com/");
              URLConnection uc = url.openConnection();
              uc.connect();
              long time = uc.getDate();
              Date date = new Date(time);
              SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
              dateFormat.setTimeZone(TimeZone.getTimeZone("GMT"));
              String settime = dateFormat.format(date);
              mhisys.getNetTime(settime);
              break;
            }catch (Exception e) {
                e.printStackTrace();
                count++;
                try{
                Thread.sleep(10000);
                }catch (Exception ee) {}
            }
         }
    }

    public String getLocalMacAddress() {
        IBinder b = ServiceManager
                .getService(Context.NETWORKMANAGEMENT_SERVICE);
        INetworkManagementService mNwService;
        mNwService = INetworkManagementService.Stub.asInterface(b);
        String ethMac = "";
        try {
            ethMac = mNwService.getInterfaceConfig("eth0").getHardwareAddress()
                    .toString();
        } catch (Exception e) {
        }
        return ethMac;
    }
    private int downloadThreadRun = 0;

    private void removeUpgrade() {
        mDownloadManager.remove(mSystemUpgrade.getDownloadID_zip());
        mDownloadManager.remove(mLogoUpgrade.getDownloadID());
        mDownloadManager.remove(mFastplayUpgrade.getDownloadID());
        mDownloadManager.remove(mAnimationUpgrade.getDownloadID());
    }

    private void downloadUpgrade() {
        if(DEBUG) {
            Log.d(TAG, "downloadUpgrade:" + downloadThreadRun);
        }
        if (Environment.MEDIA_MOUNTED.equals(Environment
                .getExternalStorageState()) && downloadThreadRun == 0) {
            new Thread() {
                public void run() {
                    downloadThreadRun = 1;
                    removeUpgrade();
                    mSystemUpgrade.downloadXML(true);
                    mLogoUpgrade.downloadXML(true);
                    mFastplayUpgrade.downloadXML(true);
                    mAnimationUpgrade.downloadXML(true);
                    downloadThreadRun = 0;
                }
            }.start();
        }
    }

    public int onStartCommand(Intent intent, int flags, int startId) {
        startStats();
        downloadUpgrade();
        return super.onStartCommand(intent, flags, startId);
    }

    public IBinder onBind(Intent intent) {
        return null;
    }

    public void onDestroy() {
        try {
            unregisterReceiver(mPowerReceiver);
            unregisterReceiver(mUpdateReceiver);
        } catch (Exception e) {
            Log.v("Exception", "Exception " + e);
        }
        stopService = true;
        wakeLock.release();
        super.onDestroy();
    }

    private void startStats() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (!stopService) {
                    try {
                        getStats();
                        Log.i(TAG, " ***** changeStats = " + changeStats.size());
                        saveStats();
                        Thread.sleep(1000 * 10);
                        String runtime = SystemProperties.get(RUNTIME);
                        if (runtime == null || runtime.equals("")) {
                            runtime = "0";
                        }
                        Long l = Long.parseLong(runtime);
                        l++;
                        SystemProperties.set(RUNTIME, "" + l);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }

    private void saveStats() {
        adapter.open();
        adapter.saveStats(changeStats);
        adapter.close();
    }
    private void getStats() {
        try {
            PkgUsageStats[] pkgStats = mUsageStatsService.getAllPkgUsageStats();
            if (null != pkgStats) {
                nowStats = changeToMyPkgStats(pkgStats);
                if (null == lastStats)
                    changeStats = lastStats = nowStats;
                else
                    compareStats();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private AppEntity getStats(AppEntity nowStats, AppEntity lastStats) {
        AppEntity mStats = null;
        if (null != nowStats) {
            mStats = new AppEntity();
            mStats.packageName = nowStats.packageName;
            if (null == lastStats) {
                mStats.launchCount = nowStats.launchCount;
                mStats.usageTime = nowStats.usageTime;
            } else {
                mStats.launchCount = nowStats.launchCount - lastStats.launchCount;
                mStats.usageTime = nowStats.usageTime - lastStats.usageTime;
            }
        }
        return mStats;
    }
    private void compareStats() {
        ArrayList<AppEntity> tmpStats = new ArrayList<AppEntity>();
        for (AppEntity now : nowStats) {
            AppEntity stats = null;
            boolean flag = false;
            for (AppEntity last : lastStats) {
                if (now.packageName.equals(last.packageName)) {
                    stats = getStats(now, last);
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                stats = getStats(now, null);
            }
            tmpStats.add(stats);
        }
        changeStats = new ArrayList<AppEntity>();
        for (AppEntity tmp : tmpStats) {
            if (null != tmp) {
                if (tmp.launchCount != 0 || tmp.usageTime != 0)
                    changeStats.add(tmp);
            }
        }
        lastStats = nowStats;
    }
    private ArrayList<AppEntity> changeToMyPkgStats(PkgUsageStats[] pkgStats) {
        ArrayList<AppEntity> stats = new ArrayList<AppEntity>();
        for (PkgUsageStats pkg : pkgStats) {
            AppEntity mStats = new AppEntity();
            mStats.packageName = pkg.packageName;
            mStats.launchCount = pkg.launchCount;
            mStats.usageTime = pkg.usageTime;
            stats.add(mStats);
        }
        return stats;
    }

    private void prepareSuspend() {
        if (mWifiManager.getWifiState() == WifiManager.WIFI_STATE_ENABLING
                || mWifiManager.getWifiState() == WifiManager.WIFI_STATE_ENABLED) {
            mWifiMode.setEnableFlag(true);
            mWifiMode.setLockFlag(true);
            mWifiManager.setWifiEnabled(false);
        }

        if (mWifiManager.getWifiApState() == WifiManager.WIFI_AP_STATE_ENABLING
                || mWifiManager.getWifiApState() == WifiManager.WIFI_AP_STATE_ENABLED) {
            mWifiapMode.setEnableFlag(true);
            mWifiapMode.setLockFlag(true);
            mWifiManager.setWifiApEnabled(null, false);
        }

        if (mEthManager.getEthernetState() == EthernetManager.ETHERNET_STATE_ENABLED
                && phy_link) {
            mEthMode.setEnableFlag(true);
            mEthMode.setLockFlag(true);
            mEthManager.setEthernetEnabled(false);
        }

        if (mLocalAdapter != null
                && mLocalAdapter.getState() == BluetoothAdapter.STATE_ON) {
            mBluetoothMode.setEnableFlag(true);
            mBluetoothMode.setLockFlag(true);
            mLocalAdapter.disable();
        }
    }

    private void prepareResume() {
        if (mEthMode.getEnableFlag()) {
            mEthMode.setEnableFlag(false);
            mEthManager.setEthernetEnabled(true);
        }
        if (mWifiMode.getEnableFlag()) {
            mWifiMode.setEnableFlag(false);
            mWifiManager.setWifiEnabled(true);
        }
        if (mWifiapMode.getEnableFlag()) {
            mWifiapMode.setEnableFlag(false);
            mWifiManager.setWifiApEnabled(null, true);
        }
        if (mBluetoothMode.getEnableFlag()) {
            mBluetoothMode.setEnableFlag(false);
            mLocalAdapter.enable();
        }
    }
    private void acquireWakeLock() {
        synchronized (wakeLock) {
            try {
                wakeLock.acquire();
            } catch (Exception e) {
                Log.e(TAG, "exception in acquireWakeLock()", e);
            }
        }
    }

    private boolean isLiveWallPaper(String packageName) {
        PackageManager packageManager = getPackageManager();
        try {
            PackageInfo info = packageManager.getPackageInfo(packageName,
                    PackageManager.GET_CONFIGURATIONS);
            if (info.reqFeatures != null) {
                for (int i = 0; i < info.reqFeatures.length; i++) {
                    FeatureInfo reqFeatures = info.reqFeatures[i];
                    if ("android.software.live_wallpaper"
                            .equals(reqFeatures.name)) {
                        return true;
                    }
                }
            }
        } catch (NameNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            return false;
        }
        return false;
    }

    private void killApp() {
        PackageManager packageManager = getPackageManager();
        Intent mainIntent = new Intent(Intent.ACTION_MAIN, null);
        mainIntent.addCategory(Intent.CATEGORY_HOME);
        final List<ResolveInfo> apps = packageManager.queryIntentActivities(
                mainIntent, 0);

        ActivityManager am = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        List<ActivityManager.RunningAppProcessInfo> processes = am
                .getRunningAppProcesses();
        for (int j = 0; j < processes.size(); j++) {
            ActivityManager.RunningAppProcessInfo actRSI = processes.get(j);
            if(SystemProperties.get("ro.thirdparty.dhcp").equals("true")) {
                if (actRSI.flags != ActivityManager.RunningAppProcessInfo.FLAG_PERSISTENT
                        && actRSI.flags != ActivityManager.RunningAppProcessInfo.FLAG_HAS_ACTIVITIES
                        && !PACKAGE_SKYPLAY.equals(actRSI.processName)
                        && !PACKAGE_SUYINGAIDL.equals(actRSI.processName)
                        && !PACKAGE_SUYINGAPK.equals(actRSI.processName)
                        && !isLiveWallPaper(actRSI.processName)) {
                    Log.d(TAG, "apk:  " + actRSI.processName);
                    am.forceStopPackage(actRSI.processName);
                } else if (actRSI.flags == ActivityManager.RunningAppProcessInfo.FLAG_HAS_ACTIVITIES) {
                    int flag = 0;
                    for (int s = 0; s < apps.size(); s++) {
                        if (actRSI.processName
                                .equals(apps.get(s).activityInfo.applicationInfo.packageName)) {
                            flag = 1;
                            launchName = actRSI.processName;
                            break;
                        }
                    }
                    if (flag == 0 && !isLiveWallPaper(actRSI.processName)
                        && !PACKAGE_SUYINGAPK.equals(actRSI.processName)) {
                        Log.d(TAG, "launcher:  " + actRSI.processName);
                        am.forceStopPackage(actRSI.processName);
                    }
                }
            }else {
                if (actRSI.flags != ActivityManager.RunningAppProcessInfo.FLAG_PERSISTENT
                        && actRSI.flags != ActivityManager.RunningAppProcessInfo.FLAG_HAS_ACTIVITIES
                        && !PACKAGE_SKYPLAY.equals(actRSI.processName)
                        && !isLiveWallPaper(actRSI.processName)) {
                    Log.d(TAG, "apk:  " + actRSI.processName);
                    am.forceStopPackage(actRSI.processName);
                } else if (actRSI.flags == ActivityManager.RunningAppProcessInfo.FLAG_HAS_ACTIVITIES) {
                    int flag = 0;
                    for (int s = 0; s < apps.size(); s++) {
                        if (actRSI.processName
                                .equals(apps.get(s).activityInfo.applicationInfo.packageName)) {
                            flag = 1;
                            launchName = actRSI.processName;
                            break;
                        }
                    }
                    if (flag == 0 && !isLiveWallPaper(actRSI.processName)) {
                        Log.d(TAG, "launcher:  " + actRSI.processName);
                        am.forceStopPackage(actRSI.processName);
                    }
                }
            }
        }
    }

    private void releaseLock() {
        if (!mEthMode.getLockFlag() && !mWifiMode.getLockFlag()
                && !mWifiapMode.getLockFlag() && !mBluetoothMode.getLockFlag()) {
            if(SystemProperties.get("ro.thirdparty.dhcp").equals("false")) {
                unregisterReceiver(mNetReceiver);
            }
            wakeLock.release();
        }
    }

    private void doInitSh() {
        if(CHIP_98M.equals(HiSdkinvoke.getChipVersion()))
        {
           mhisys.doInitSh(1);
        }
        else if(CHIP_98C.equals(HiSdkinvoke.getChipVersion()))
        {
            mhisys.doInitSh(2);
        }
        else
        {
            mhisys.doInitSh(0);
        }
    }

    class WfdChannelListener implements WifiP2pManager.ChannelListener {
        @Override
        public void onChannelDisconnected() {
            mWifiP2pChannel = null;
        }
    }

    class wifiActionListener implements WifiP2pManager.ActionListener {
        public static final int ACTION_ID_DISCONNECT_P2P = 1001;

        private int mActionId;
        private String mAction = "";

        public wifiActionListener(int actionId) {
            mActionId = actionId;

            switch (mActionId) {
            case ACTION_ID_DISCONNECT_P2P:
                mAction = "DISCONNECT_P2P";
                break;
            default:
                break;
            }
        }

        @Override
        public void onSuccess() {
            SystemClock.sleep(SMARTSUSPEND_DELAY);
            mhisys.enterSmartStandby();
        }

        @Override
        public void onFailure(int reason) {
            String reasonDescription = "";

            switch (reason) {
            case WifiP2pManager.ERROR:
                reasonDescription = "ERROR";
                break;
            case WifiP2pManager.P2P_UNSUPPORTED:
                reasonDescription = "P2P_UNSUPPORTED";
                break;
            case WifiP2pManager.BUSY:
                reasonDescription = "BUSY";
                break;

            default:
                break;
            }

            Log.e(TAG, mAction + " reason: " + reasonDescription);
        }
    }

    private class MyHandler extends Handler {

        public MyHandler(Looper l) {
            super(l);
        }

        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case EVENT_PARAM_CHANGED:
                    setSystemProtity();
                    break;
                default:
                    break;
            }
        }
    }

    private void setSystemProtity(){
        int screen_ratio, player_quality;

        ContentResolver resolver = getContentResolver();
        screen_ratio = Settings.Secure.getInt(resolver, DEFAULT_SCREEN_RATIO, 0);
        player_quality = Settings.Secure.getInt(resolver, DEFAULT_PLAYER_QUALITY, 0);

        SystemProperties.set("persist.sys.video.cvrs", String.valueOf(1 - screen_ratio));
        SystemProperties.set("persist.sys.video.quality", String.valueOf(player_quality));
    }

    private static class ParamObserver extends ContentObserver {

        private int mMsg;
        private Handler mHandler;

        ParamObserver(Handler handler, int msg) {
            super(handler);
            mHandler = handler;
            mMsg = msg;
        }

        void observe(Context context) {
            ContentResolver resolver = context.getContentResolver();
            resolver.registerContentObserver(Settings.Secure.getUriFor(DEFAULT_SCREEN_RATIO),
                    true, this);
            resolver.registerContentObserver(Settings.Secure.getUriFor(DEFAULT_PLAYER_QUALITY),
                    true, this);
        }

        @Override
        public void onChange(boolean selfChange) {
            mHandler.obtainMessage(mMsg).sendToTarget();
        }
    }

}
