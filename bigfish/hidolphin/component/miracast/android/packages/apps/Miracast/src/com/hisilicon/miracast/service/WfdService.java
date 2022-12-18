package com.hisilicon.miracast.service;

import java.lang.ref.WeakReference;
import java.lang.reflect.Field;
import java.net.InetAddress;
import java.util.TimerTask;
import java.util.Timer;
import java.io.InputStream;
import java.util.List;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.p2p.WifiP2pDevice;
import android.net.wifi.p2p.WifiP2pInfo;
import android.net.wifi.p2p.WifiP2pManager;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.os.Messenger;

import com.hisilicon.miracast.R;
import com.hisilicon.miracast.activity.DisplayActivity;
import com.hisilicon.miracast.bean.LoopThread;
import com.hisilicon.miracast.business.WfdBusiness;
import com.hisilicon.miracast.business.WifiBusiness;
import com.hisilicon.miracast.constant.IntentConst;
import com.hisilicon.miracast.constant.MsgConst;
import com.hisilicon.miracast.model.WfdModel;
import com.hisilicon.miracast.model.Hdcp;
import com.hisilicon.miracast.ndk.SinkNative;
import com.hisilicon.miracast.util.DialogUtil;
import com.hisilicon.miracast.util.LogUtil;
import com.hisilicon.miracast.util.RegexUtil;
import com.hisilicon.miracast.util.ToastUtil;
import com.hisilicon.miracast.util.BroadcastUtil;
import com.hisilicon.miracast.util.XmlUtil;
import com.hisilicon.miracast.model.Hdcp;


public final class WfdService extends Service
{
    /* dialog */
    private ProgressDialog mPdWaiting;

    /* wfd */
    private WfdBusiness mWfdBusiness;
    private WfdModel mWfdModel;
    private SinkNative mSinkNative;
    private BroadcastReceiver mWfdReceiver;

    /* wifi */
    private WifiBusiness mWifiBusiness;
    private BroadcastReceiver mWifiReceiver;
    private boolean mWasWifiEnabled = false;
    private boolean mIsWifiApEnabled = false;
    private boolean mIsDisconnectAp = false;

    private LoopThread mWorkThread;
    private Handler mWorkHandler;

    /** when sink is go, start a thread to get source ip address */
    private Thread mSinkGoThread;
    private static final int CONNECT_RTSP_DURATION = 500;

    private Messenger mMessenger;

    /** RTSP connection count */
    private int mConnectCount = 0;
    private static final int MAX_CONNECT_COUNT = 30;

    /**
     * true means SettingActivity is started
     * false means SettingActivity wants to stop
     */
    private boolean mIsSettingStarted = true;

    /**
     * true means DisplayActivity is started
     * false means DisplayActivity is stopped
     */
    private boolean mIsDisplayStarted = false;

    /**when sink connected AP, start a thread to delay 1 second then disconnect AP*/
    private static final int AP_CONNECTED_DELAY_TIME = 1000;
    private Thread mApConnectedThread;

    /**
    *true means rtsp setup success
    *false means rtsp does not setup success
    */
    private boolean mIsRtspSuccess = false;

    /**
    *true means enter enableWfd function
    *false means does not enter enableWfd function
    */
    private boolean mIsEnterEnableWfd =  false;

    /**
    *true means exit from SettingActivity
    *false means does not exit from SettingActivity
    */
    private boolean mIsExitFromSetting = false;

    /**
    *true means finish enter SettingActivity
    *false means does not finish enter SettingActivity
    */
    private boolean mIsFinishEnterSetting = false;

    /**
     *true means sink connecting ap
     *false means isnot connecting ap
     */
    private boolean mIsApConnected = false;

    /**
     *true means STB is restarting wifi before exit from miracast
     *false means STB is not restarting wifi
     */
    private boolean mIsRestartWifiBeforeExit = false;
    private boolean mIsHomeBack = false;
    /*keep sink alive*/
    private Timer mkeepAliveTimer = null;
    private TimerTask mkeepAliveTimerTask = null;

    private static final int SINK_KEEPALIVE_TIME = 60 * 60 * 1000 + 10 * 1000;

    /*add timer and timerTask to statistic mExitMiracastTime before exit*/
    private Timer mExitMiracastTimer = null;
    private TimerTask mExitMiracastTimerTask = null;
    private int mExitMiracastTime = 0;
    private static final int EXIT_PERIOD_TIME = 1000;
    private static final int MAX_EXIT_TIME = 10;
    private final Object mLock = new Object();

    private BroadcastUtil mBroadcast = null;

    /**wifi p2p listen channel, operater channel*/
    private int[] mWifiP2pChannels = new int[2];

        /**
     *true means sink disable networks
     *false means not disable networks
     */
    private boolean mIsDisableNetworks = false;
    @Override
    public void onCreate()
    {
        LogUtil.v("");
        super.onCreate();

        initVariable();
        initReceiver();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        LogUtil.v("");
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public IBinder onBind(Intent intent)
    {
        LogUtil.v("");
        sendBroadcastWfdChanged();
        return mMessenger.getBinder();
    }

    @Override
    public void onRebind(Intent intent)
    {
        LogUtil.v("");
        super.onRebind(intent);
    }

    @Override
    public boolean onUnbind(Intent intent)
    {
        LogUtil.v("");
        return super.onUnbind(intent);
    }

    @Override
    public void onDestroy()
    {
        LogUtil.v("");
        super.onDestroy();
        //press home key back, mIsExitFromSetting is false
        if (!mIsExitFromSetting)
        {
            clearWifiP2pInfo();

            if (!mWasWifiEnabled)
            {
                //at the beginning wifi is disabled
                LogUtil.d("disableWifi");
                mWifiBusiness.disableWifi();
            }
            else if (mIsDisconnectAp)
            {
                //at the beginning wifi AP is connected
                enableNetworks();
                LogUtil.d("connect AP");
                mWifiBusiness.connect();
            }
            if (mIsWifiApEnabled)
            {
                mWifiBusiness.enableWifiAp();
                mIsWifiApEnabled = false;
            }
        }
        destroyReceiver();
        doCleanup();
    }

    private void showWifiNotAvailableDialog()
    {
        LogUtil.d("");
        AlertDialog.Builder builder =
            DialogUtil.getCommonDialogBuilder(this, R.string.DialogTitleWifiNotAvailable,
                                              R.string.DialogMessageWifiNotAvailable);
        builder.setPositiveButton(R.string.TextYes, new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
                sendBroadcastFinishSetting();
            }
        });
        builder.setCancelable(false);

        Dialog dialog = builder.create();
        DialogUtil.showServiceDialog(dialog);
    }

    private void showSinkKeepAliveFailedDialog()
    {
        LogUtil.d("");
        AlertDialog.Builder builder =
            DialogUtil.getCommonDialogBuilder(this, R.string.DialogTitleAboutMiracast,
                                              R.string.DialogMessageKeepAliveFailed);
        builder.setPositiveButton(R.string.TextYes, null);

        Dialog dialog = builder.create();
        DialogUtil.showServiceDialog(dialog);
    }

    private void disconnectAp()
    {
        mWifiBusiness.disconnect();
        mIsDisconnectAp = true;
    }

    private void setHdcpMode()
    {
        LogUtil.d("");

        Hdcp hdcp = null;
        int hdcpMode = 0;
        String hdcpName = "";
        InputStream inputStream = getResources().openRawResource(R.raw.hdcp);

        try
        {
        hdcp = XmlUtil.getHdcpInfo(inputStream);
        hdcpMode = hdcp.getHdcpMode();
        hdcpName = hdcp.getHdcpName();
        LogUtil.d("hdcpName: " + hdcpName + "hdcpMode: " + hdcpMode);
        }
        catch(Exception e)
        {
        e.printStackTrace();
        }

        if (hdcpMode < 0 || hdcpMode > 3)
        {
        hdcpMode = 0;
        }

        if (mSinkNative != null)
        {
           mSinkNative.setHdcpMode(hdcpMode);
        }
    }

    private int[] getBestWifiP2pChannel()
    {
        int[] channels = new int[2];

        channels = mWifiBusiness.getWifiP2pChannel();


        return channels;
    }

    private void setWifiP2pChannels()
    {
        if (mWifiP2pChannels[0] == 0 || mWifiP2pChannels[1] == 0 || mWfdBusiness == null)
        {
            return;
        }

        mWfdBusiness.setWifiP2pChannels(mWifiP2pChannels[0], mWifiP2pChannels[1]);
    }

    private void initVariable()
    {
        mWifiBusiness = new WifiBusiness(this);
        mWasWifiEnabled = mWifiBusiness.isWifiEnabled();
        mIsWifiApEnabled = mWifiBusiness.isWifiApEnabled();

        mWfdModel = new WfdModel();
        mWfdBusiness = new WfdBusiness(this);

        mWorkThread = new LoopThread(getClass().getSimpleName() + "WorkThread");
        mWorkHandler = new WorkHandler(this, mWorkThread.getLooper());
        mMessenger = new Messenger(mWorkHandler);

        mSinkNative = SinkNative.getInstance();
        mSinkNative.setListener(new SinkListener());
        mBroadcast = new BroadcastUtil(this);

        mWifiP2pChannels = getBestWifiP2pChannel();
    }

    private void initReceiver()
    {
        LogUtil.d("");

        final IntentFilter wifiFilter = new IntentFilter();
        wifiFilter.addAction(WifiManager.NETWORK_STATE_CHANGED_ACTION);
        wifiFilter.addAction(WifiManager.WIFI_STATE_CHANGED_ACTION);
        wifiFilter.addAction(WifiManager.RSSI_CHANGED_ACTION);
        mWifiReceiver = new WifiReceiver();
        registerReceiver(mWifiReceiver, wifiFilter);

        final IntentFilter wfdFilter = new IntentFilter();
        wfdFilter.addAction(WifiP2pManager.WIFI_P2P_STATE_CHANGED_ACTION);
        wfdFilter.addAction(WifiP2pManager.WIFI_P2P_CONNECTION_CHANGED_ACTION);
        wfdFilter.addAction(WifiP2pManager.WIFI_P2P_PEERS_CHANGED_ACTION);
        wfdFilter.addAction(WifiP2pManager.WIFI_P2P_THIS_DEVICE_CHANGED_ACTION);
        wfdFilter.addAction(WifiP2pManager.WIFI_P2P_DISCOVERY_CHANGED_ACTION);
        wfdFilter.addAction(WifiP2pManager.WIFI_P2P_PERSISTENT_GROUPS_CHANGED_ACTION);
        wfdFilter.addAction(getWifiP2pConnectingAction());
        wfdFilter.addAction(getWifiP2pConnectFailAction());
        mWfdReceiver = new WfdReceiver();
        registerReceiver(mWfdReceiver, wfdFilter);
    }

    private void destroyReceiver()
    {
        LogUtil.d("");
        if (mWifiReceiver != null)
        {
            unregisterReceiver(mWifiReceiver);
            mWifiReceiver = null;
        }

        if (mWfdReceiver != null)
        {
            unregisterReceiver(mWfdReceiver);
            mWfdReceiver = null;
        }
    }

    private void doCleanup()
    {
        stopKeepAliveTimer();

        mSinkNative.removeListener();

        mWorkThread.quit();

        try
        {
            if (mWorkThread.isAlive())
            {
                mWorkThread.join();
                mWorkThread = null;
            }

            if ((mSinkGoThread != null) && (mSinkGoThread.isAlive()))
            {
                mSinkGoThread.join();
                mSinkGoThread = null;
            }

            if ((mApConnectedThread != null) && (mApConnectedThread.isAlive()))
            {
                mApConnectedThread.join();
                mApConnectedThread = null;
            }
        }
        catch (InterruptedException e)
        {
            LogUtil.e(e.toString());
        }
    }

    private void exitAfterRestartWifi()
    {
        LogUtil.d("");

        if (mIsWifiApEnabled)
        {
            mWifiBusiness.enableWifiAp();
            mIsWifiApEnabled = false;
        }

        if (mWfdModel.isExitingFromMiracast())
        {
            mWfdModel.setExitingFromMiracast(false);
            stopExitMiracastTimer();
            sendBroadcastFinishSetting();
        }
    }

    private void enableWfd()
    {
        LogUtil.d("");

        if (!mWasWifiEnabled)
        {
            sendBroadcastShowTurnOnDialog();
            mIsEnterEnableWfd = true;
            mWifiBusiness.enableWifi();
        }

        mIsFinishEnterSetting = true;
    }

    private void clearWifiP2pInfo()
    {
        LogUtil.d("");
        if (mWfdModel.isWifiP2pEnabled())
        {
            mWfdBusiness.clearWfdInfo();

            if (mWfdModel.isWifiP2pConnected())
            {
                releaseWfd();
                mWfdBusiness.disconnectP2p();
            }
        }
    }

    private void disableWfd()
    {
        LogUtil.d("");

        mIsExitFromSetting = true;

        clearWifiP2pInfo();

        if (mWifiBusiness.isWifiAvailable())
        {
            if (mWasWifiEnabled)
            {
                //if wifi is enabled at the beginning, restart wifi
                if (!mIsRestartWifiBeforeExit)
                {
                    mIsRestartWifiBeforeExit = true;
                    mWfdModel.setExitingFromMiracast(true);
                    startExitMiracastTimer();
                    mWifiBusiness.disableWifi();
                }
            }
            else
            {
                mWifiBusiness.disableWifi();
                sendBroadcastShowTurnOffDialog();
                if (mIsWifiApEnabled)
                {
                    mWifiBusiness.enableWifiAp();
                    mIsWifiApEnabled = false;
                }
            }
        }
    }

    private synchronized void onWifiP2pConnectionChanged()
    {
        LogUtil.d("");

        if (mWfdModel.isWifiP2pConnected())
        {
            if (mWfdBusiness.isSourceWfd())
            {
                if (mWfdModel.isDeviceGo())
                {
                    // sink go
                    mSinkGoThread = new Thread(new SinkGoThread());
                    mSinkGoThread.start();
                }
                else
                {
                    // source go
                    mWfdModel.setSourceIpAddr(mWfdModel.getGoIpAddr());
                    startWfd();
                }
            }
            else
            {
                LogUtil.w("source is not a Wi-Fi Display device");
            }
        }
        else
        {
            if (mWfdModel.isWifiP2pEnabled())
            {
                mConnectCount = 0;
            }

            onStopWfdFinished(MsgConst.MSG_NATIVE_ARG_NONE);
        }
    }

    private void sendBroadcastWfdChanged()
    {
        final Intent intent = new Intent(IntentConst.ACTION_WFD_CHANGED);
        intent.putExtra(IntentConst.EXTRA_WFD_MODEL, mWfdModel);
        sendBroadcast(intent);
    }

    private void sendBroadcastShowToast()
    {
        LogUtil.d("");
        final Intent intent = new Intent(IntentConst.ACTION_SHOW_TOAST);
        sendBroadcast(intent);
    }

    private void sendBroadcastShowTurnOnDialog()
    {
        LogUtil.d("");
        final Intent intent = new Intent(IntentConst.ACTION_SHOW_TURN_ON_DIALOG);
        sendBroadcast(intent);
    }

    private void sendBroadcastShowTurnOffDialog()
    {
        LogUtil.d("");
        final Intent intent = new Intent(IntentConst.ACTION_SHOW_TURN_OFF_DIALOG);
        sendBroadcast(intent);
    }

    private void sendBroadcastHideDialog()
    {
        LogUtil.d("");
        final Intent intent = new Intent(IntentConst.ACTION_HIDE_DIALOG);
        sendBroadcast(intent);
    }

    private synchronized void startWfd()
    {
        final String sourceIp = mWfdModel.getSourceIpAddr();
        LogUtil.d("source ip address: " + sourceIp);

        if (mWfdModel.isWifiP2pEnabled())
        {
            if (RegexUtil.isIpAddr(sourceIp))
            {
                if (!mWfdModel.isWfdStarted())
                {
                    setHdcpMode();
                    mSinkNative.initSink(sourceIp, mWfdBusiness.getSourcePort());
                    mSinkNative.startSink();
                }
                else
                {
                    LogUtil.e("wfd is started");
                }
            }
            else
            {
                LogUtil.e("ip addr error");
            }
        }
        else
        {
            LogUtil.w("wfd is not enabled");
        }
    }

    private synchronized void stopWfd()
    {
        LogUtil.d("");
        if (mWfdModel.isWfdStarted())
        {
            mSinkNative.stopSink();
        }
    }

    private synchronized void releaseWfd()
    {
        LogUtil.d("");
        mSinkNative.releaseSink();
    }

    private void onUpdateLostPacket(int lostPacket)
    {
        mWfdModel.setLostPacket(lostPacket);
    }

    private void onSettingStart()
    {
        mIsSettingStarted = true;
        enableWfd();
    }

    private void onSettingStop()
    {
        mIsSettingStarted = false;
        disableWfd();
    }

    private void onDisplayStart()
    {
        LogUtil.d("");
        mIsDisplayStarted = true;
        initPlayer();
        sendBroadcastWfdState(MsgConst.MSG_WFD_PLAYING);
    }

    private synchronized void initPlayer()
    {
        LogUtil.d("");
        mSinkNative.initPlayer();
    }

    private void onDisplayStop()
    {
        LogUtil.d("");
        mIsDisplayStarted = false;
        stopWfd();
    }

    private synchronized void onStartWfdFinished()
    {
        LogUtil.d("");
        if (!mWfdModel.isWfdStarted())
        {
            mWfdModel.setWfdStarted(true);
            sendBroadcastWfdFinishInit();
            mIsRtspSuccess = true;
        }
    }

    private void sendBroadcastWfdFinishInit()
    {
        LogUtil.d("");
        sendBroadcast(new Intent(IntentConst.ACTION_FINISH_WFD_INIT));
    }

    private synchronized void onStopWfdFinished(int arg)
    {
        LogUtil.d("");

        releaseWfd();

        mWfdModel.setWfdStarted(false);

        if ((arg == MsgConst.MSG_NATIVE_ARG_CONNECTION_FAILED)
            && (mConnectCount < MAX_CONNECT_COUNT) && !mIsRtspSuccess)
        {
            LogUtil.w("RTSP connection failed");
            mConnectCount++;
            LogUtil.i("connect count: " + mConnectCount);

            if (mWfdModel.isWifiP2pConnected())
            {
                try
                {
                    Thread.sleep(CONNECT_RTSP_DURATION);
                }
                catch (InterruptedException e)
                {
                    LogUtil.e(e.toString());
                }
                startWfd();
            }
        }
        else
        {
            if (mWfdModel.isWifiP2pConnected())
            {
                mWfdBusiness.disconnectP2p();
            }

            if (mIsDisplayStarted)
            {
                sendBroadcastFinishDisplay();
            }

            if (mWfdModel.isWifiP2pConnecting())
            {
                mWfdModel.setWifiP2pConnecting(false);
                sendBroadcastWfdChanged();
            }

            mIsRtspSuccess = false;
        }
    }

    private void startDisplayActivity()
    {
        LogUtil.d("");
        final Intent intent = new Intent(getApplicationContext(), DisplayActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }

    private void sendBroadcastFinishSetting()
    {
        LogUtil.d("");
        sendBroadcast(new Intent(IntentConst.ACTION_FINISH_SETTING));
    }

    private void sendBroadcastHomeFinishSetting()
    {
        LogUtil.d("");
        mIsHomeBack = true;
        sendBroadcast(new Intent(IntentConst.ACTION_HOME_FINISH_SETTING));
    }

    private void platformNoSupported()
    {
        LogUtil.d("");
        ToastUtil.showToast(this, R.string.ToastPlatformNoSupport);
    }

    private void sendBroadcastFinishDisplay()
    {
        LogUtil.d("");
        sendBroadcast(new Intent(IntentConst.ACTION_FINISH_DISPLAY));
    }

    private void startKeepAliveTimer()
    {
        LogUtil.d("");

        mkeepAliveTimer = new Timer();
        mkeepAliveTimerTask = new KeepAliveTimerTask();

        if (mkeepAliveTimer != null && mkeepAliveTimerTask != null)
        {
            mkeepAliveTimer.schedule(mkeepAliveTimerTask, SINK_KEEPALIVE_TIME, SINK_KEEPALIVE_TIME);
        }
    }

    private void stopKeepAliveTimer()
    {
        LogUtil.d("");

        if (mkeepAliveTimerTask != null)
        {
            mkeepAliveTimerTask.cancel();
            mkeepAliveTimerTask = null;
        }

        if (mkeepAliveTimer != null)
        {
            mkeepAliveTimer.cancel();
            mkeepAliveTimer = null;
        }
    }

    private void keepSinkAlive()
    {
        LogUtil.d("");

        stopKeepAliveTimer();

        startKeepAliveTimer();
    }

    /*when exit, the max mExitMiracastTime is 10s*/
    private void startExitMiracastTimer()
    {
        LogUtil.d("");

        mExitMiracastTimer = new Timer();
        TimerTask mExitMiracastTimerTask = new TimerTask()
        {
            public void run()
            {
                synchronized (mLock)
                {
                    mExitMiracastTime++;
                    LogUtil.d("mExitMiracastTime = " + mExitMiracastTime);
                    if (mExitMiracastTime >= MAX_EXIT_TIME)
                    {
                        exitAfterRestartWifi();
                    }
                }
            }
        };

        if (mExitMiracastTimer != null)
        {
            mExitMiracastTimer.schedule(mExitMiracastTimerTask, EXIT_PERIOD_TIME, EXIT_PERIOD_TIME);
        }
        else
        {
            LogUtil.d("mExitMiracastTimer equals to null");
        }
    }

    private void stopExitMiracastTimer()
    {
        LogUtil.d("");
        if (mExitMiracastTimerTask != null)
        {
            mExitMiracastTimerTask.cancel();
            mExitMiracastTimerTask = null;
        }

        if (mExitMiracastTimer != null)
        {
            mExitMiracastTimer.cancel();
            mExitMiracastTimer = null;
        }
        synchronized (mLock)
        {
            mExitMiracastTime = 0;
        }
    }

    private void sendBroadcastWfdState(int stateId)
    {
        LogUtil.d("");

        if (mBroadcast != null)
        {
            mBroadcast.sendWfdBroadCast(stateId);
        }
    }

    private String getWifiP2pConnectingAction()
    {
        String action = "android.net.wifi.p2p.WIFI_MIRACAST_IS_CONNECTING_ACTION";

        try
        {
            Field connectingField = WifiP2pManager.class.getField(" WIFI_MIRACAST_IS_CONNECTING_ACTION");
            action = (String)connectingField.get(null);
        }
        catch (NoSuchFieldException e)
        {
            LogUtil.e(e.toString());
        }
        catch (SecurityException e)
        {
            LogUtil.e(e.toString());
        }
        catch (IllegalArgumentException e)
        {
            LogUtil.e(e.toString());
        }
        catch (IllegalAccessException e)
        {
            LogUtil.e(e.toString());
        }

        return action;
    }

    private String getWifiP2pConnectFailAction()
    {
        String action = "android.net.wifi.p2p.WIFI_MIRACAST_CONNECT_FAIL_ACTION";

        try
        {
            Field connectFailField = WifiP2pManager.class.getField("WIFI_MIRACAST_CONNECT_FAIL_ACTION");
            action = (String)connectFailField.get(null);
        }
        catch (NoSuchFieldException e)
        {
            LogUtil.e(e.toString());
        }
        catch (SecurityException e)
        {
            LogUtil.e(e.toString());
        }
        catch (IllegalArgumentException e)
        {
            LogUtil.e(e.toString());
        }
        catch (IllegalAccessException e)
        {
            LogUtil.e(e.toString());
        }

        return action;
    }

    private String getSourceInfo()
    {
        String info = "miracastSourceInfo";

        try
        {
            Field sourceInfoField = WifiP2pManager.class.getField("EXTRA_MIRACAST_SOURCE_INFO");
            info = (String)sourceInfoField.get(null);
        }
        catch (NoSuchFieldException e)
        {
            LogUtil.e(e.toString());
        }
        catch (SecurityException e)
        {
            LogUtil.e(e.toString());
        }
        catch (IllegalArgumentException e)
        {
            LogUtil.e(e.toString());
        }
        catch (IllegalAccessException e)
        {
            LogUtil.e(e.toString());
        }

        return info;
    }

    private void disableNetworks()
    {
        if (mWifiBusiness != null)
        {
            mWifiBusiness.disableNetworks();
        }
    }

    private void enableNetworks()
    {
        if (mWifiBusiness != null)
        {
             mWifiBusiness.enableNetworks();
        }
    }

    class SinkListener implements SinkNative.ISinkListener
    {
        @Override
        public void onMessageReceived(Message msg)
        {
            LogUtil.d("what: " + msg.what);
            mWorkHandler.sendMessage(msg);
        }
    }

    class SinkGoThread implements Runnable
    {
        @Override
        public void run()
        {
            try
            {
                mWfdModel.setSourceIpAddr(mWfdBusiness.getSourceIp());
                startWfd();
            }
            catch (Exception e)
            {
                LogUtil.e(e.toString());
            }
        }
    }

    class ApConnectedThread implements Runnable
    {
        @Override
        public void run()
        {
            try
            {
                Thread.sleep(AP_CONNECTED_DELAY_TIME);
                final Message msg = Message.obtain();
                msg.what = MsgConst.MSG_SERVICE_DISCONNECT_AP;
                mWorkHandler.sendMessage(msg);
            }
            catch (Exception e)
            {
                LogUtil.e(e.toString());
            }
        }
    }

    class KeepAliveTimerTask extends TimerTask
    {
        @Override
        public void run()
        {
            LogUtil.d("keeplive setwfdinfo");

            if (mWfdBusiness != null)
            {
                mWfdBusiness.setWfdInfo();
            }
        }
    }

    class WifiReceiver extends BroadcastReceiver
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            final String action = intent.getAction();
            LogUtil.i(action);
            final Message msg = Message.obtain();
            if (WifiManager.NETWORK_STATE_CHANGED_ACTION.equals(action))
            {
                final NetworkInfo info =
                    (NetworkInfo) intent.getParcelableExtra(WifiManager.EXTRA_NETWORK_INFO);
                if (info == null)
                {
                    LogUtil.i("WifiManager NetworkInfo info is null!");
                    return;
                }

                if (info.isConnected())
                {
                    LogUtil.i("wifi connected");
                    final WifiInfo wifiInfo =
                        (WifiInfo) intent.getParcelableExtra(WifiManager.EXTRA_WIFI_INFO);
                    mIsApConnected = true;
                    if (wifiInfo != null)
                    {
                        LogUtil.i("ssid: " + wifiInfo.getSSID());
                    }



                    if (mIsSettingStarted)
                    {
                        mApConnectedThread = new Thread(new ApConnectedThread());
                        mApConnectedThread.start();
                    }
                    else
                    {
                       // the case: at the beginning AP is connected
                        if (mIsRestartWifiBeforeExit && mIsDisconnectAp)
                        {
                            exitAfterRestartWifi();
                            mIsDisconnectAp = false;
                        }
                    }
                }
                else
                {
                    LogUtil.i("wifi disconnected");
                    // when restart wifi, need not setWfdInfo
                    if ((!mIsRestartWifiBeforeExit) && mIsApConnected  && (!mIsHomeBack))
                    {
                        LogUtil.i("wifi disconnected setWfdInfo");
                        mIsApConnected = false;
                        mWfdBusiness.setWfdInfo();
                        keepSinkAlive();
                    }
                }

                if (!mIsDisableNetworks)
                {
                    disableNetworks();
                    mIsDisableNetworks = true;
                }
            }
            else if (WifiManager.WIFI_STATE_CHANGED_ACTION.equals(action))
            {
                final int state =
                    intent.getIntExtra(WifiManager.EXTRA_WIFI_STATE,
                                       WifiManager.WIFI_STATE_DISABLED);

                if (WifiManager.WIFI_STATE_DISABLED == state)
                {
                    LogUtil.i("WIFI_STATE_DISABLED");

                    if (!mIsSettingStarted && !mWasWifiEnabled)
                    {
                        LogUtil.i("sendBroadcastHideDialog");
                        sendBroadcastHideDialog();
                        sendBroadcastFinishSetting();
                    }
                    // disable wifi is OK, now enable wifi
                    if (!mIsSettingStarted && mWasWifiEnabled)
                    {
                        LogUtil.i("Now enableWifi");
                        mWifiBusiness.enableWifi();
                    }
                    if (!mIsExitFromSetting && mIsFinishEnterSetting)
                    {
                        showWifiNotAvailableDialog();
                        mIsFinishEnterSetting = false;
                    }
                }
                else if (WifiManager.WIFI_STATE_DISABLING == state)
                {
                    LogUtil.i("WIFI_STATE_DISABLING");
                }
                else if (WifiManager.WIFI_STATE_ENABLED == state)
                {
                    LogUtil.i("WIFI_STATE_ENABLED");
                    // the case: at the beginning wifi is enabled, but AP is not connected
                    if ((!mIsDisconnectAp) && mIsRestartWifiBeforeExit)
                    {
                        exitAfterRestartWifi();
                    }
                }
                else if (WifiManager.WIFI_STATE_ENABLING == state)
                {
                    LogUtil.i("WIFI_STATE_ENABLING");
                }
                else if (WifiManager.WIFI_STATE_UNKNOWN == state)
                {
                    LogUtil.w("WIFI_STATE_UNKNOWN");

                    if (mIsEnterEnableWfd)
                    {
                        sendBroadcastHideDialog();
                        showWifiNotAvailableDialog();
                        mIsEnterEnableWfd = false;
                    }
                }
            }
            else if (WifiManager.RSSI_CHANGED_ACTION.equals(action))
            {
                final int rssi = intent.getIntExtra(WifiManager.EXTRA_NEW_RSSI, -1);
                final int signalLevel = WifiBusiness.getSignalLevel(rssi);
                LogUtil.i("signal level: " + signalLevel);
            }
        }
    }

    class WfdReceiver extends BroadcastReceiver
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            final String action = intent.getAction();
            LogUtil.i(action);

            final Message msg = Message.obtain();

            if (WifiP2pManager.WIFI_P2P_STATE_CHANGED_ACTION.equals(action))
            {
                final int state =
                    intent.getIntExtra(WifiP2pManager.EXTRA_WIFI_STATE,
                                       WifiP2pManager.WIFI_P2P_STATE_DISABLED);
                boolean isEnabled = (WifiP2pManager.WIFI_P2P_STATE_ENABLED == state);

                if (isEnabled)
                {
                    LogUtil.i("WIFI_P2P_STATE_ENABLED");
                    sendBroadcastHideDialog();
                    setWifiP2pChannels();
                }
                else
                {
                    LogUtil.i("WIFI_P2P_STATE_DISABLED");
                }

                mWfdModel.setWifiP2pEnabled(isEnabled);

                msg.what = MsgConst.MSG_SERVICE_WIFI_P2P_STATE_CHANGED;
            }
            else if (WifiP2pManager.WIFI_P2P_CONNECTION_CHANGED_ACTION.equals(action))
            {
                if (mWfdModel.isWifiP2pEnabled())
                {
                    NetworkInfo info =
                        (NetworkInfo) intent.getParcelableExtra(WifiP2pManager.EXTRA_NETWORK_INFO);
                if (info == null)
                {
                    LogUtil.i("WifiP2pManager NetworkInfo info is null!");
                    return;
                }
                    mWfdModel.setWifiP2pConnected(info.isConnected());

                    mWfdBusiness.updateGroup();
                    mWfdBusiness.updatePeers();

                    if (info.isConnected())
                    {
                        LogUtil.i("Wi-Fi Direct connected");
                        final WifiP2pInfo p2pInfo =
                            (WifiP2pInfo) intent
                            .getParcelableExtra(WifiP2pManager.EXTRA_WIFI_P2P_INFO);
                        if (p2pInfo != null)
                        {
                            mWfdModel.setDeviceGo(p2pInfo.isGroupOwner);
                            final InetAddress inetAddr = p2pInfo.groupOwnerAddress;
                            final String hostAddr = inetAddr.getHostAddress();
                            LogUtil.i("go ip address: " + hostAddr);
                            mWfdModel.setGoIpAddr(hostAddr);

                            if (mWfdModel.isDeviceGo())
                            {
                                LogUtil.i("sink is go");
                            }
                            else
                            {
                                LogUtil.i("source is go");
                            }
                        }

                        sendBroadcastWfdState(MsgConst.MSG_WFD_CONNECTED);
                    }
                    else
                    {
                        LogUtil.i("Wi-Fi Direct disconnected");
                        // when restart wifi, need not setWfdInfo
                        if ((!mIsRestartWifiBeforeExit) && (!mIsApConnected) && (!mIsHomeBack))
                        {
                            LogUtil.i("Wi-Fi Direct disconnected setWfdInfo");
                            mWfdBusiness.setWfdInfo();
                            keepSinkAlive();
                        }
                    }

                    msg.what = MsgConst.MSG_SERVICE_WIFI_P2P_CONNECTION_CHANGED;
                }
            }
            else if (WifiP2pManager.WIFI_P2P_PEERS_CHANGED_ACTION.equals(action))
            {
            }
            else if (WifiP2pManager.WIFI_P2P_THIS_DEVICE_CHANGED_ACTION.equals(action))
            {
                WifiP2pDevice device =
                    (WifiP2pDevice) intent.getParcelableExtra(WifiP2pManager.EXTRA_WIFI_P2P_DEVICE);
                if (device == null)
                {
                    LogUtil.i("device is null!");
                    return;
                }
                mWfdModel.setDeviceName(device.deviceName);
                mWfdModel.setDeviceAddr(device.deviceAddress);

                msg.what = MsgConst.MSG_SERVICE_WIFI_P2P_THIS_DEVICE_CHANGED;
            }
            else if (WifiP2pManager.WIFI_P2P_DISCOVERY_CHANGED_ACTION.equals(action))
            {
                final int state =
                    intent.getIntExtra(WifiP2pManager.EXTRA_DISCOVERY_STATE,
                                       WifiP2pManager.WIFI_P2P_DISCOVERY_STOPPED);
                boolean isSearching = (WifiP2pManager.WIFI_P2P_DISCOVERY_STARTED == state);
                mWfdModel.setSearching(isSearching);

                if (isSearching)
                {
                    LogUtil.i("searching started");
                }
                else
                {
                    LogUtil.i("searching stopped");
                }
            }
            else if (WifiP2pManager.WIFI_P2P_PERSISTENT_GROUPS_CHANGED_ACTION.equals(action))
            {
                if (mWfdModel.isWifiP2pEnabled())
                {
                    mWfdBusiness.updatePersistentGroup();
                }
            }
            else if (getWifiP2pConnectingAction().equals(action))
            {
                WifiP2pDevice device =
                (WifiP2pDevice) intent.getParcelableExtra(getSourceInfo());

                mWfdModel.setWifiP2pConnecting(true);

                sendBroadcastWfdState(MsgConst.MSG_WFD_CONNECTING);

                if (device != null)
                {
                    LogUtil.i("device name:" + device.deviceName);
                    LogUtil.i("device address:" + device.deviceAddress);
                }

                msg.what = MsgConst.MSG_SERVICE_WIFI_P2P_CONNECTING;
            }
            else if (getWifiP2pConnectFailAction().equals(action))
            {
                 LogUtil.d("wifi p2p connect failed");
            }

            mWorkHandler.sendMessage(msg);
        }
    }

    static class WorkHandler extends Handler
    {
        final WeakReference<WfdService> mRef;

        public WorkHandler(WfdService ori, Looper looper)
        {
            super(looper);
            mRef = new WeakReference<WfdService>(ori);
        }

        @Override
        public void handleMessage(Message msg)
        {
            final WfdService ori = mRef.get();

            switch (msg.what)
            {
                case MsgConst.MSG_SERVICE_WIFI_P2P_STATE_CHANGED:
                    ori.sendBroadcastWfdChanged();
                    break;

                case MsgConst.MSG_SERVICE_WIFI_P2P_CONNECTION_CHANGED:
                    ori.onWifiP2pConnectionChanged();
                    ori.sendBroadcastWfdChanged();
                    break;

                case MsgConst.MSG_SERVICE_WIFI_P2P_CONNECTING:
                    ori.sendBroadcastWfdChanged();
                    break;

                case MsgConst.MSG_SERVICE_WIFI_P2P_THIS_DEVICE_CHANGED:
                    ori.sendBroadcastWfdChanged();
                    break;

                case MsgConst.MSG_SERVICE_DISCONNECT_AP:
                    ori.disconnectAp();
                    ori.sendBroadcastShowToast();
                    break;

                case MsgConst.MSG_SETTING_START:
                    ori.onSettingStart();
                    break;

                case MsgConst.MSG_SETTING_DISPLAYSTART:
                    ori.startDisplayActivity();
                    break;

                case MsgConst.MSG_SETTING_STOP:
                    ori.onSettingStop();
                    ori.sendBroadcastWfdChanged();
                    break;

                case MsgConst.MSG_DISPLAY_START:
                    ori.onDisplayStart();
                    break;

                case MsgConst.MSG_DISPLAY_STOP:
                    ori.onDisplayStop();
                    break;

                case MsgConst.MSG_DISPLAY_HOME_STOP:
                    ori.sendBroadcastHomeFinishSetting();
                    break;

                case MsgConst.MSG_NATIVE_WHAT_START_WFD_FINISHED:
                    ori.onStartWfdFinished();
                    ori.sendBroadcastWfdChanged();
                    break;

                case MsgConst.MSG_NATIVE_WHAT_STOP_WFD_FINISHED:
                case MsgConst.MSG_NATIVE_WHAT_NETWORK_INTERRUPT:
                case MsgConst.MSG_NATIVE_WHAT_TVP_INIT_ERROR:
                case MsgConst.MSG_NATIVE_WHAT_HDCP_INIT_ERROR:
                    ori.onStopWfdFinished(msg.arg1);
                    ori.sendBroadcastWfdState(MsgConst.MSG_WFD_DISCONNECTED);
                    break;

                case MsgConst.MSG_NATIVE_WHAT_SINK_KEEPALIVE_FAILED:
                    ori.onStopWfdFinished(msg.arg1);
                    ori.showSinkKeepAliveFailedDialog();
                    ori.sendBroadcastWfdState(MsgConst.MSG_WFD_DISCONNECTED);
                    break;

                case MsgConst.MSG_NATIVE_WHAT_PLATFORM_NO_SUPPORTED:
                    ori.platformNoSupported();
                    ori.onStopWfdFinished(msg.arg1);
                    ori.sendBroadcastWfdState(MsgConst.MSG_WFD_DISCONNECTED);
                    break;

                case MsgConst.MSG_NATIVE_WHAT_UPDATE_LOST_PACKET:
                    ori.onUpdateLostPacket(msg.arg1);
                    ori.sendBroadcastWfdChanged();
                    break;

                default:
                    break;
            }
        }
    }
}
