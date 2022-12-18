package com.hisilicon.dlna.player;

import java.lang.ref.WeakReference;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Toast;

import com.hisilicon.dlna.dmr.Constant;
import com.hisilicon.dlna.dmr.IDMRServer;
import com.hisilicon.dlna.dmr.action.BaseAction;
import com.hisilicon.dlna.dmr.action.Controller;
import com.hisilicon.dlna.util.imagedecode.DecodeUtil;
import com.hisilicon.dlna.file.FileType;

public class MainPlayerActivity extends Activity implements IPlayerMainWnd
{
    private static final String TAG = "MainPlayerActivity";

    /**
     * CN: 延时关闭当前窗口的时间. <br>
     */
    public static final int DELAYFINISH_TIME = 1000 * 3;

    /**
     * CN: 立即关闭当前窗口. <br>
     */
    public static final int MSGID_SUBWND_TO_MAINWND_FINISH = 100;

    public static boolean mIsActivityIsRuning = false;

    public static long mLastStopTime = 0;

    private NetworkReceiver mNetworkReceiver = new NetworkReceiver();
    private PlayerReceiver mPlayerReceiver = new PlayerReceiver();
    private Context mContext = null;

    public Handler mHandler = new MainMsgHandler(this);

    private PlayerSubWnd mIPlayerSubWnd = null;

    private IDMRServer dmrServer = null;
    private Controller mController = null;
    private FileType mFileType = null;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        Log.d(TAG, "onCreate ");

        final Window win = getWindow();
        if (null == win)
        {
            Log.e(TAG,"onCreate getWindow = null");
            return;
        }
        win.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.mainlayout);

        mContext = this;
        IntentFilter filter = new IntentFilter();
        filter.addAction("android.net.conn.LINK_STATE_CHANGED");
        filter.addAction("android.net.ethernet.ETHERNET_STATE_CHANGE");
        filter.addAction("android.net.ethernet.STATE_CHANGE");
        registerReceiver(mNetworkReceiver, filter);

        IntentFilter filterPlayer = new IntentFilter();
        filterPlayer.addAction(PlayerBroadcastReceiver.START_AGAIN_BROADCAST_MAIN);
        registerReceiver(mPlayerReceiver, filterPlayer);
        DecodeUtil.HI_ImageDeocde_Init();

        // Check that the activity is using the layout version with
        // the fragment_container FrameLayout
        if (findViewById(R.id.fragment_container) != null)
        {
            if (savedInstanceState == null)
            {
                changeSubWnd(getIntent());
            }
        }
        mIsActivityIsRuning = true;
    }

    private void changeSubWnd(Intent intent)
    {
        BaseAction action = (BaseAction) intent.getSerializableExtra(Constant.FILE_PLAY_PATH);
        FileType type = (FileType) intent.getSerializableExtra(Constant.FILE_PLAY_TYPE);
        String contentType = (String)intent.getSerializableExtra(Constant.FILE_CONTENT_TYPE);
        String contentlength = (String)intent.getSerializableExtra(Constant.FILE_CONTENT_LENGTH);
        mController = action.getController();
        cancelDelayCloseActivity();
        Log.d(TAG, " mController=" + mController + ",filetype= " + type);
        if (mController == Controller.DMR)
        {
            if (ServiceManager.checkService("dmr") == null)
            {
                Log.d(TAG, "dmr service is not exist");
                Toast.makeText(this, "dmr binder is not in ServiceManager", 3);
                this.finish();
            }
            else
            {
                Log.d(TAG, "dmr service is exist");
                dmrServer = IDMRServer.Stub.asInterface(ServiceManager.getService("dmr"));
            }
            openActivityNotify();
        }
        if ((mFileType == type) && (null != mIPlayerSubWnd))
        {
            if(mIPlayerSubWnd.isInited() == true)
            {
                Log.d(TAG, "main receive change,but not need change");
                mIPlayerSubWnd.setBaseAction(action);
                if(contentlength != null)
                            mIPlayerSubWnd.setContentLength(Long.parseLong(contentlength));
                mIPlayerSubWnd.setContentType(contentType);
                Log.d(TAG," content type : " + contentType + "length : " + contentlength);
                return;
            }
        }
        mFileType = type;
        PlayerSubWnd subWnd = null;
        switch (type)
        {
            case VIDEO:
                subWnd = new VideoPlayerSubWnd();
                break;
            case AUDIO:
                subWnd = new MusicPlayerSubWnd();
                break;
            case IMAGE:
                subWnd = new ImagePlayerSubWnd();
            default:
                break;
        }
        if (null == subWnd)
        {
            return;
        }
        this.setIntent(intent);
        // In case this activity was started with special instructions from an Intent,
        // pass the Intent's extras to the fragment as arguments
        subWnd.setArguments(getIntent().getExtras());

        // Add the fragment to the 'fragment_container' FrameLayout
        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        fragmentTransaction.replace(R.id.fragment_container, subWnd).commit();
        mIPlayerSubWnd = subWnd;
        mIPlayerSubWnd.setMainWnd(this);
    }

    @Override
    protected void onPause()
    {
        Log.d(TAG, "onPause send close");
        mIsActivityIsRuning = false;
        closeActivity(false);
        super.onPause();
    }

    protected void onResume()
    {
        super.onResume();
        Log.d(TAG, "onResume()");
        mIsActivityIsRuning = true;
        cancelDelayCloseActivity();
    }

    protected void onStop()
    {
        Log.d(TAG, "onStop()");
        mIsActivityIsRuning = false;
        super.onStop();
    }

    @Override
    protected void onDestroy()
    {
        Log.e(TAG, "onDestroy");
        destroyActivityNotify();
        DecodeUtil.HI_ImageDeocde_DeInit();
        unregisterReceiver(mNetworkReceiver);
        mNetworkReceiver = null;
        unregisterReceiver(mPlayerReceiver);
        mPlayerReceiver = null;
        // ActivityManager activityManager =
        // (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
        // activityManager.killBackgroundProcesses("com.hisilicon.dlna.player");
        super.onDestroy();
    }

    public class PlayerReceiver extends BroadcastReceiver
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            String action = intent.getAction();
            if ((null != action)
                    && (action.equals(PlayerBroadcastReceiver.START_AGAIN_BROADCAST_MAIN)))
            {
                Log.e(TAG, "PlayerReceiver intent=" + intent);
                changeSubWnd(intent);
            }
        }
    }

    public class NetworkReceiver extends BroadcastReceiver
    {
        private static final String TAG = "NetworkReceiver";
        private static final int SUM_OF_WIFI_SIGNAL_LEVELS = 5;

        @Override
        public void onReceive(Context context, Intent intent)
        {
            String action = intent.getAction();
            if (null == action)
            {
                Log.e(TAG, "NetworkReceiver onReceive : get action is null");
            }
            else
            {
                if (action.equals(WifiManager.WIFI_STATE_CHANGED_ACTION))
                {
                    int wifiState = intent.getIntExtra(WifiManager.EXTRA_WIFI_STATE,
                            WifiManager.WIFI_STATE_UNKNOWN);
                    boolean enable = wifiState == WifiManager.WIFI_STATE_ENABLED;
                    // whether wifi is enable?
                    Log.d(TAG, "WIFI_STATE_CHANGED_ACTION enable=" + enable);
                }
                else if (action.equals(WifiManager.NETWORK_STATE_CHANGED_ACTION))
                {
                    NetworkInfo networkInfo = (NetworkInfo) intent
                            .getParcelableExtra(WifiManager.EXTRA_NETWORK_INFO);
                    if (networkInfo != null && networkInfo.isConnected())
                    {
                        // wifi is connected
                        Log.d(TAG, "NETWORK_STATE_CHANGED_ACTION");
                    }
                }
                else if (action.equals(WifiManager.RSSI_CHANGED_ACTION))
                {
                    // which level is wifi signal strength
                    Log.d(TAG, "RSSI_CHANGED_ACTION");
                }
                /*
                 * for android 2.2 ConnectivityManager.ACTION_LINK_STATE_CHANGED =
                 * "android.net.conn.LINK_STATE_CHANGED" public static final String
                 * EXTRA_LINK_CONNECTED = "connected"; for android 4.0
                 * EthernetManager.ETHERNET_STATE_CHANGED_ACTION =
                 * "android.net.ethernet.ETHERNET_STATE_CHANGE"
                 * EthernetManager.NETWORK_STATE_CHANGED_ACTION =
                 * "android.net.ethernet.STATE_CHANGE" String EXTRA_ETHERNET_STATE=
                 * "ethernet_state"; public static final int ETHERNET_STATE_DISABLED = 0; public
                 * static final int ETHERNET_STATE_ENABLED = 1; public static final int
                 * ETHERNET_STATE_UNKNOWN = 2;
                 */
                else if (action.equals("android.net.conn.LINK_STATE_CHANGED"))
                {
                    int linkNum = intent.getIntExtra("connected", 1);
                    if (linkNum > 1)
                    {
                        // network has at least one link
                        Log.d(TAG, "ACTION_LINK_STATE_CHANGED >1");
                    }
                    else if (!isWifiConnected())
                    {
                        // network is dislinked
                        Log.d(TAG, "ACTION_LINK_STATE_CHANGED");
                        if (mContext != null)
                            Toast.makeText(mContext, R.string.network_interruption, 3).show();
                        closeActivity(false);
                    }
                }
                else if (action.equals("android.net.ethernet.ETHERNET_STATE_CHANGE")
                        || action.equals("android.net.ethernet.STATE_CHANGE"))
                {
                    if (action.equals("android.net.ethernet.ETHERNET_STATE_CHANGE"))
                    {
                        int status = intent.getIntExtra("ethernet_state", 2);
                        if (status == 0 || status == 4)
                        {// connected
                        }
                        else if (status == 1 && !isWifiConnected() && !isAPStateOn())
                        {// connect failed
                            Log.d(TAG, "EthernetManager: ethernet connect failed");
                            if (mContext != null)
                                Toast.makeText(mContext, R.string.network_interruption, 3).show();
                            closeActivity(false);
                        }
                        else if ((status == 2 || status == 6) && !isWifiConnected()
                                && !isAPStateOn())
                        {// disconnected
                            Log.d(TAG, "EthernetManager: ethernet disconnected");
                            if (mContext != null)
                                Toast.makeText(mContext, R.string.network_interruption, 3).show();
                            closeActivity(false);
                        }
                        else
                        {// unknown
                        }
                    }
                    else
                    {
                        // nothing to do
                        Log.d(TAG, "EthernetManager.NETWORK_STATE_CHANGED_ACTION");
                    }
                }
            }
        }
    }

    private Boolean isAPStateOn()
    {
        WifiManager wifiManager = (WifiManager) this.getSystemService(Context.WIFI_SERVICE);
        if (wifiManager == null)
        {
            return false;
        }
        if (wifiManager.getWifiApState() == WifiManager.WIFI_AP_STATE_ENABLED)
            return true;
        else
            return false;
    }

    private boolean isWifiConnected()
    {
        ConnectivityManager connectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo wifiInfo = connectivityManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
        return (null != wifiInfo) ? wifiInfo.isConnected() : false;
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if ((null != mIPlayerSubWnd)
                && (PlayerSubWnd.KeyDoResult.DO_OVER == mIPlayerSubWnd.keyDownDispatch(keyCode,
                        event)))
        {
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
        if ((null != mIPlayerSubWnd)
                && (PlayerSubWnd.KeyDoResult.DO_OVER == mIPlayerSubWnd
                        .keyUpDispatch(keyCode, event)))
        {
            return true;
        }
        return super.onKeyUp(keyCode, event);
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event)
    {
        if ((event.getAction() == KeyEvent.ACTION_DOWN)
                && mHandler.hasMessages(MSGID_SUBWND_TO_MAINWND_FINISH))
        {
            closeActivity(true);
        }
        if ((null != mIPlayerSubWnd)
                && (PlayerSubWnd.KeyDoResult.DO_OVER == mIPlayerSubWnd.dispatchKeyEvent(event)))
        {
            return true;
        }
        return super.dispatchKeyEvent(event);
    }

    /**
     * To close the main activity. <br>
     * CN: 关闭主应用. <br>
     */
    public void closeActivity(boolean isDelay)
    {
        cancelDelayCloseActivity();
        Log.d(TAG, "colseActivity isDelay=" + isDelay);
        if (isDelay)
        {
            mHandler.sendEmptyMessageDelayed(MSGID_SUBWND_TO_MAINWND_FINISH, DELAYFINISH_TIME);
        }
        else
        {
            mHandler.sendEmptyMessage(MSGID_SUBWND_TO_MAINWND_FINISH);
        }
    }

    public void cancelDelayCloseActivity()
    {
        while (mHandler.hasMessages(MSGID_SUBWND_TO_MAINWND_FINISH))
        {
            mHandler.removeMessages(MSGID_SUBWND_TO_MAINWND_FINISH);
            Log.d(TAG, "cancelDelayCloseActivity clean");
        }
        Log.d(TAG,"call cancelDelayCloseActivity");
    }

    // ///////////////////////////////////
    private static class MainMsgHandler extends Handler
    {
        WeakReference<MainPlayerActivity> mActivity;

        MainMsgHandler(MainPlayerActivity parent)
        {
            mActivity = new WeakReference<MainPlayerActivity>(parent);
        }

        @Override
        public void handleMessage(Message msg)
        {
            Log.d(TAG, "handleMessage msg = " + msg.what);
            if (null != mActivity)
            {
                MainPlayerActivity parent = mActivity.get();
                if (null != parent)
                {
                    Log.e(TAG, "handleMessage " + ",f=" + mIsActivityIsRuning);
                    if (MSGID_SUBWND_TO_MAINWND_FINISH == msg.what)
                    {
                        mLastStopTime = System.currentTimeMillis();
                        mIsActivityIsRuning = false;
                        parent.destroyActivityNotify();
                        mIsActivityIsRuning = false;
                        parent.finish();
                    }
                }
            }
        }
    }

    private void openActivityNotify()
    {
        if (mController != Controller.DMR)
        {
            return;
        }
        if (dmrServer != null)
        {
            try
            {
                dmrServer.getDMRCallback().openActivityNotify(0);
            }
            catch (RemoteException e)
            {
                Log.e(TAG, "openActivityNotify", e);
            }
        }
    }

    private void destroyActivityNotify()
    {
        Log.e(TAG, "destroyActivityNotify");
        if (dmrServer != null)
        {
            try
            {
                Log.e(TAG, "call dmrServer.getDMRCallback().destroyActivityNotify(0)");
                dmrServer.getDMRCallback().destroyActivityNotify(0);
                dmrServer = null;
            }
            catch (RemoteException e)
            {
                Log.e(TAG, "destroyActivityNotify", e);
            }
        }
    }
}
