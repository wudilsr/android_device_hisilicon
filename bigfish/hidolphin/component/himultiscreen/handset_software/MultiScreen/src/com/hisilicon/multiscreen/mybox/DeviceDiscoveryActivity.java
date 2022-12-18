package com.hisilicon.multiscreen.mybox;

import java.lang.ref.SoftReference;
import java.util.HashMap;

import org.cybergarage.upnp.Device;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.os.StrictMode;
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.gui.activity.DMSBrowseActivity;
import com.hisilicon.dlna.dmc.gui.activity.LiveTVActivity;
import com.hisilicon.multiscreen.controller.AccessUpnpController;
import com.hisilicon.multiscreen.controller.IAccessListener;
import com.hisilicon.multiscreen.controller.IAccessListener.Caller;
import com.hisilicon.multiscreen.mybox.DeviceListShow.ClickCallback;
import com.hisilicon.multiscreen.mybox.MultiScreenControlService.ClientState;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.utils.HostNetInterface;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.ServiceUtil;
import com.hisilicon.multiscreen.scene.SceneType;
import com.hisilicon.multiscreen.upnputils.MultiScreenDeviceList;
import com.hisilicon.multiscreen.upnputils.UpnpDeviceListHandler;

/**
 * Activity activity of device discovery.<br>
 * CN:设备发现。
 */
public class DeviceDiscoveryActivity extends Activity
{
    /**
     * Handle message for showing packet loss toast.<br>
     * CN:网络存在丢包。
     */
    public static final int KEEP_ALIVE_PACKET_LOSS = 10;

    /**
     * Handle message for showing failed dialog.<br>
     * CN:网络断开。
     */
    public static final int KEEP_ALIVE_FAILED = 20;

    /**
     * Access reaved.<br>
     * CN:抢占消息。
     */
    public static final int ACCESS_REAVED = 30;

    /**
     * STB leave.<br>
     * CN:STB离开消息。
     */
    public static final int STB_LEAVE = 40;

    /**
     * STB suspend.<br>
     * CN:STB待机消息。
     */
    public static final int STB_SUSPEND = 80;

    /**
     * MultiScreen control service.<br>
     * CN:多屏控制服务。
     */
    private MultiScreenControlService mMultiScreenControlService = null;

    /**
     * Access UPNP controller.<br>
     * CN:接入控制者。
     */
    private AccessUpnpController mAccessController = null;

    /**
     * Handler of access event.
     */
    private AccessEventHandler mAccessEventHandler = null;

    /**
     * Access ping listener.<br>
     * CN:网络状态监听回调。
     */
    private IAccessListener mAccessListener = null;

    /**
     * CN:未连接的提示信息。
     */
    public static String mDisonnectText = null;

    public static final int MSG_SHOWLIST_DELAY = 100;

    public static final int MSG_MSEARCH_DELAY = 200;

    public static final int MSG_MESARCH = 300;

    /**
     * Delay time of showing list.<br>
     */
    public static final long SHOWLIST_DELAY_MILLIS = 50;

    /**
     * Retry times of sending M-SEARCH.<br>
     */
    public static final int MSEARCH_RETRY_TIMES = 3;

    /**
     * Delay time of re-sending M-SEARCH.<br>
     */
    public static final long RE_SEARCH_DELAY_MILLIS = 2000;

    /**
     * Delay time of search.<br>
     */
    public static final long SEARCH_DELAY_MILLIS = 50;

    /**
     * Delay time of connect device.<br>
     */
    public static final long CONNECT_DELAY_MILLIS = 50;

    /**
     * Message data key of M-Search retry times.<br>
     */
    private static final String MSG_DATA_KEY_RETRY_TIMES = "MSEARCH_RETRY_TIMES";

    /**
     * Message data key of M-Search delay time.<br>
     */
    private static final String MSG_DATA_KEY_DELAY_TIME = "MSEARCH_DELAY_TIME";

    private HandlerThread mHandlerThread = null;

    private Handler ListHandler = null;

    /**
     * CN:设备选择布局。
     */
    private RelativeLayout mDevice_title_select;

    /**
     * CN:设备连接信息。
     */
    private TextView mDevice_title_info;

    /**
     * CN:设备连接图标。
     */
    private ImageView mDeVice_title_disconnected;

    /**
     * CN:设备连接的子界面。
     */
    private DeviceChildView mDevice_child;

    /**
     * CN:设置按钮。
     */
    private Button mDevice_setting;

    /**
     * Display width of screen.
     */
    private int displayWidth = 0;

    /**
     * Context of this <br>
     * .
     */
    private static Context mContext = null;

    /**
     * CN:已连接的设备ip
     */
    public static String save_ip = null;

    /**
     * CN:设备列表。
     */
    private MultiScreenDeviceList devList = null;

    /**
     * Device list handler.<br>
     */
    private DeviceListHandler mShowDeviceListHandler = null;

    /**
     * Connect timeout of AccessHello.<br>
     */
    public static final int ACCESS_CONNECT_TIMEOUT = 3000;

    /**
     * Read timeout of AccessHello.<br>
     */
    public static final int READ_TIMEOUT = 3000;

    /**
     * DeviceListShow click callback.
     */
    private ClickCallback mPopClickCallback;

    /**
     * CN:设备列表的显示，通过集成popwindow实现。
     */
    private DeviceListShow mDeviceListPop;

    private Runnable mDisconnectOnUiRunnable;

    private volatile boolean canDestroy = false;

    private boolean isManualConnecting = false;

    // public static final String DEVICE_CONNECT =
    // "com.hisilicon.multiscreen.mybox.DeviceListener.DEVICE_CONNECT";
    // public static final String DEVICE_DISCONNECT =
    // "com.hisilicon.multiscreen.mybox.DeviceListener.DEVICE_DISCONNECT";

    /**
     * Device list update handler.<br>
     * CN:设备列表更新处理者。
     */
    public UpnpDeviceListHandler mDeviceListHandler = new UpnpDeviceListHandler()
    {
        @Override
        public void updateDeviceList()
        {
            synchronized (mSyncDevList)
            {
                devList = mMultiScreenControlService.getDeviceDiscover().getDeviceList();
            }
            mShowDeviceListHandler.sendEmptyMessage(MessageDef.MSG_DEVICE_IP_LIST_UPDATE);
        }
    };

    /**
     * Sync object.<br>
     * CN:同步对象。
     */
    private Object mSyncDevList = new Object();

    /**
     * Original device list listener.<br>
     * CN:原始设备列表监听者。
     */
    private IOriginalDeviceListListener mIOriginalDeviceListListener =
        new IOriginalDeviceListListener()
        {
            @Override
            public void deviceAdd(Device device)
            {
                // CN:自动连接
                connectDelay(device.getUDN());
                // CN:延迟显示排序列表。
                showListDelay();
            }

            @Override
            public void deviceRemoved(Device device)
            {
                // FIXME CN: 1.设备下线可能是闪断后服务重启，主动断开连接。
                // 2.必须延迟同步并显示列表，因为该接口回调时，原始设备还存在。
                showListDelay();
            }
        };

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        LogTool.v("onCreate");
        super.onCreate(savedInstanceState);

        initView();
        setStrictMode();
        initData();
        initHandler();
        // startMediaSharingService();
        // sendBroadcast();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig)
    {
        LogTool.d("onConfigurationChanged");
        super.onConfigurationChanged(newConfig);
    }

    /**
     * To start time task of discovering devices when the activity resumes.
     * Schedule the time task for repeated 6000 milliseconds fixed-delay.<br>
     * CN:搜索设备，结果停留6000毫秒重新搜索。
     */
    protected void onResume()
    {
        LogTool.v("onResume");
        super.onResume();
        resumeActivity();
    }

    /**
     * On pause.<br>
     * The access event should be handled whatever screen-off. So do not set
     * access listener null when the activity is on pause.
     */
    protected void onPause()
    {
        LogTool.v("onPause");
        super.onPause();
    }

    /**
     * On stop.<br>
     */
    protected void onStop()
    {
        LogTool.v("onStop");
        super.onStop();
    }

    /**
     * On destroy.<br>
     */
    protected void onDestroy()
    {
        LogTool.v("onDestroy");
        super.onDestroy();
    }

    /**
     * Do handling key down even.<br>
     * CN:处理按键事件。
     */
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if (keyCode == KeyEvent.KEYCODE_BACK)
        {
            // FIXME ztest for get device by locationURL.
            // ControlPoint controlPoint =
            // mMultiScreenControlService.getControlPoint();
            // if (controlPoint != null)
            // {
            // // something like this: http://192.168.0.3:49154/description.xml
            // // http://192.168.0.6:49152/description.xml
            // String locationURL = "http://192.168.0.3:49152/description.xml";
            // String uuid = "cc6g32df-aaaa-22c3-e029-0AAC26386B77";
            // String localAddress = getWifiIpAddress();
            // controlPoint.searchByUrl(locationURL, uuid, localAddress);
            // }
            // end ztest

            if (canDestroy)
            {
                destroy();
            }
            else
            {
                canDestroy = true;
                myHandler.sendEmptyMessageDelayed(MessageDef.EXIT_APP,
                    MessageDef.BACK_PRESSED_MILLIS);
                Toast.makeText(this, R.string.one_more_exit, Toast.LENGTH_SHORT).show();
            }

            return true;
        }
        else if (keyCode == KeyEvent.KEYCODE_HOME)
        {
            // TODO CN:HOME退出，服务重置为INIT，停止保活？
            // deInitNetworkChecker(Caller.Others, ClientState.INIT);
        }

        return super.onKeyDown(keyCode, event);
    }

    /**
     * CN:退出应用。
     */
    private void destroy()
    {
        try
        {
            // stopMediaSharingService();// 放到第一位，确保首先kill掉爱分享服务进程
            ServiceUtil.stopMultiScreenControlService(this);
            deInitHandler();
            finish();
        }
        finally
        {
            android.os.Process.killProcess(android.os.Process.myPid());
        }
    }

    /**
     * init view.
     */
    private void initView()
    {
        mContext = this;
        setContentView(R.layout.device_dis);

        DisplayMetrics dm = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm);
        displayWidth = dm.widthPixels;
        // displayHeight= dm.heightPixels;

        mDisonnectText = mContext.getResources().getString(R.string.device_select_no_connect);

        mDevice_title_select = (RelativeLayout) findViewById(R.id.device_title_select);
        mDevice_title_select.setOnClickListener(mOnClickListener);
        mDevice_title_info = (TextView) findViewById(R.id.device_title_info);
        mDeVice_title_disconnected = (ImageView) findViewById(R.id.device_title_disconnected);

        mDevice_child = (DeviceChildView) findViewById(R.id.device_child);

        mDevice_setting = (Button) findViewById(R.id.device_setting);
        mDevice_setting.setOnClickListener(mOnClickListener);
        mDevice_child.mDevice_gridview.setAdapter(new GridViewAdapter(mDevice_child.mImageIds,
            mDevice_child.mtags, mDevice_child.mtags_info, mContext));
    }

    /**
     * Init service and controller.<br>
     * CN:初始化服务和控制者。
     */
    private void initData()
    {
        LogTool.d("initData");
        ServiceUtil.checkMultiScreenControlService(this);
        mMultiScreenControlService = MultiScreenControlService.getInstance();
        mPopClickCallback = new ClickCallback()
        {
            public void clickItem(Device device)
            {
                manualConnectDevice(device);
            }
        };
        mDeviceListPop = new DeviceListShow(DeviceDiscoveryActivity.this, mPopClickCallback);

        mDisconnectOnUiRunnable = new Runnable()
        {
            @Override
            public void run()
            {
                if (mDevice_title_info != null)
                {
                    mDevice_title_info.setText(mDisonnectText);
                    mDeVice_title_disconnected
                        .setImageResource(R.drawable.device_disconnected_normal);
                    mDevice_child.mDevice_no_connect.setVisibility(View.VISIBLE);
                    mDevice_child.mDevice_connect.setVisibility(View.INVISIBLE);
                }
            }
        };

        mAccessController = new AccessUpnpController();

        mAccessEventHandler = new AccessEventHandler(this);

        mAccessListener = new IAccessListener()
        {
            @Override
            public void dealNetWorkNotWellEvent()
            {
                // Keep alive packet loss.
                mAccessEventHandler.sendEmptyMessage(KEEP_ALIVE_PACKET_LOSS);
            }

            @Override
            public void dealNetWorkLostEvent(Caller caller)
            {
                // Keep alive fail.
                LogTool.d("Keep alive fail.");
                sendAccessStatusMessage(caller, KEEP_ALIVE_FAILED);
            }

            @Override
            public void dealReaveEvent(Caller caller)
            {
                // Be reaved.
                LogTool.d("Be reaved.");
                sendAccessStatusMessage(caller, ACCESS_REAVED);
            }

            @Override
            public void dealSTBLeaveEvent(Caller caller)
            {
                // STB leave.
                LogTool.d("STB leave.");
                sendAccessStatusMessage(caller, STB_LEAVE);
            }

            @Override
            public void dealSTBSuspendEvent(Caller caller)
            {
                // STB suspend
                LogTool.d("STB suspend.");
                sendAccessStatusMessage(caller, STB_SUSPEND);
            }

            private void sendAccessStatusMessage(Caller caller, int what)
            {
                Message msg = mAccessEventHandler.obtainMessage();
                msg.obj = caller;
                msg.what = what;
                msg.sendToTarget();
            }
        };
    }

    /**
     * Is target device.<br>
     * @param uuid
     * @return
     */
    private boolean isTarget(String uuid)
    {
        boolean isTarget = false;
        if (isFirst())
        {
            isTarget = true;
        }
        else
        {
            isTarget = isSaved(uuid);
        }

        return isTarget;
    }

    /**
     * Is first time to connect device.<br>
     * @return
     */
    private boolean isFirst()
    {
        boolean isFirst = false;
        if (ServiceUtil.getSavedUuid() == null || "".equals(ServiceUtil.getSavedUuid()))
        {
            isFirst = true;
        }
        return isFirst;
    }

    /**
     * Device UDN(UUID) is saved.<br>
     * @param uuid
     * @return
     */
    private boolean isSaved(String uuid)
    {
        boolean isSaved = false;
        if (uuid.equals(ServiceUtil.getSavedUuid()))
        {
            isSaved = true;
        }
        return isSaved;
    }

    /**
     * Check current device and update UI on resume.<br>
     */
    private void checkCurrentDevice()
    {
        if (mMultiScreenControlService != null && mMultiScreenControlService.isReaved())
        {
            reavedOnUi();
            return;
        }
        else if ((mMultiScreenControlService == null)
            || (mMultiScreenControlService.isRunning() == false))
        {
            disconnectOnUi();
            return;
        }

        Device currentDevice = mMultiScreenControlService.getControlPoint().getCurrentDevice();
        if (currentDevice != null)
        {
            // MyApp.setSTBIP(HostNetInterface.uri2Ip(currentDevice.getLocation()));
            updateDeviceName(currentDevice.getFriendlyName());
        }
        else
        {
            disconnectOnUi();
        }
    }

    /**
     * Show dialog if access event notify.<br>
     * CN:接入控制事件处理者。
     */
    private static class AccessEventHandler extends Handler
    {
        SoftReference<DeviceDiscoveryActivity> mActivityReference = null;

        AccessEventHandler(DeviceDiscoveryActivity activity)
        {
            mActivityReference = new SoftReference<DeviceDiscoveryActivity>(activity);
        }

        public void handleMessage(Message msg)
        {
            DeviceDiscoveryActivity activity = mActivityReference.get();
            super.handleMessage(msg);

            if (activity == null)
            {
                return;
            }

            switch (msg.what)
            {
                case KEEP_ALIVE_PACKET_LOSS:
                {
                    // CN:网络存在丢包。
                    LogTool.e("keep alive packet loss!");
                    activity.dealPacketLoss();
                    break;
                }

                case KEEP_ALIVE_FAILED:
                {
                    // CN:网络断开。
                    Caller caller = (Caller) msg.obj;
                    activity.dealNetfailedStatus(caller);
                    break;
                }

                case ACCESS_REAVED:
                {
                    // CN:抢占。
                    Caller caller = (Caller) msg.obj;
                    activity.dealAccessByeForReave(caller);
                    break;
                }

                case STB_LEAVE:
                {
                    // CN:STB关闭。
                    // sendBroadcast("STBClose");
                    Caller caller = (Caller) msg.obj;
                    activity.dealSTBLeave(caller);
                    break;
                }
                case STB_SUSPEND:
                {
                    // CN:STB浅待机
                    Caller caller = (Caller) msg.obj;
                    activity.dealSTBSuspend(caller);
                }
                    break;
                default:
                    break;
            }
        }
    }

    /**
     * Deal packet loss.<br>
     * CN:网络存在丢包。
     */
    private void dealPacketLoss()
    {
        Toast.makeText(this, getResources().getString(R.string.toast_KeepAlive_packet_loss),
            Toast.LENGTH_SHORT).show();
    }

    /**
     * Deal keeping alive failed.<br>
     * CN:网络断开处理。
     */
    private void dealNetfailedStatus(Caller caller)
    {
        // CN:从设备列表中删除失效的设备。
        deInitNetworkChecker(caller, ClientState.NETWORK_LOST);
        sendByeToSTB(ClientState.NETWORK_LOST);
        removeInvalidDevice();
        // 设备下线处理
        disconnectOnUi();
    }

    /**
     * Deal Access bye for reave.<br>
     * CN:处理抢占事件。
     */
    private void dealAccessByeForReave(Caller caller)
    {
        // CN:停止状态检查，更新UI，允许手动再次接入。
        deInitNetworkChecker(caller, ClientState.REAVED);
        clearCurrentDevice();
        reavedOnUi();
    }

    /**
     * Deal STB leave.<br>
     * CN:处理STB关闭事件。
     */
    private void dealSTBLeave(Caller caller)
    {
        deInitNetworkChecker(caller, ClientState.STB_LEAVE);
        sendByeToSTB(ClientState.STB_LEAVE);
        removeInvalidDevice();
        disconnectOnUi();
    }

    /**
     * Deal STB suspend.<br>
     * @param caller
     */
    private void dealSTBSuspend(Caller caller)
    {
        deInitNetworkChecker(caller, ClientState.STB_SUSPEND);
        clearCurrentDevice();
        disconnectOnUi();
    }

    /**
     * Remove invalid device in original list.<br>
     * CN:删除原始列表中的失效设备。
     */
    private void removeInvalidDevice()
    {
        mMultiScreenControlService.getControlPoint().removeCannotAccessDevice(
            mMultiScreenControlService.getControlPoint().getCurrentDevice());
        clearCurrentDevice();
    }

    private void clearCurrentDevice()
    {
        mMultiScreenControlService.getControlPoint().setCurrentDevice(null);
    }

    /**
     * Stop network check.<br>
     * CN:停止网络状态检查。
     * @param caller CN:调用者。
     * @param clientState CN:客户端状态。
     */
    private void deInitNetworkChecker(Caller caller, ClientState clientState)
    {
        // CN:停止网络状态检查。
        mMultiScreenControlService.stopPing(caller, clientState);
    }

    /**
     * Send byebye to STB.<br>
     * CN:向STB发送byebye消息。
     * @param clientState
     */
    private void sendByeToSTB(ClientState clientState)
    {
        // CN:当客户端不被抢占状态时，发送byebye消息。
        if (clientState != ClientState.REAVED)
        {
            new Thread()
            {
                public void run()
                {
                    boolean isByebye = MultiScreenControlService.getInstance().accessByebye();
                    if (!isByebye)
                    {
                        LogTool.d("AccessByebye failed and try again!");
                        MultiScreenControlService.getInstance().accessByebye();
                    }
                }
            }.start();
        }
    }

    /**
     * View click listener.<br>
     * CN:控件监听者。
     */
    public OnClickListener mOnClickListener = new OnClickListener()
    {
        @Override
        public void onClick(View view)
        {
            switch (view.getId())
            {
                case R.id.device_title_select:
                {
                    mDeviceListPop.showAtLocation(mDevice_title_info, Gravity.BOTTOM, 0, 0);
                    retrySearchDelay(MSEARCH_RETRY_TIMES, RE_SEARCH_DELAY_MILLIS);
                }
                    break;

                case R.id.device_setting:
                {
                    Intent intent =
                        new Intent(DeviceDiscoveryActivity.this, MultiSettingActivity.class);
                    intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                    startActivity(intent);
                }
                    break;

                default:
                    break;
            }
        };

    };

    /**
     * Resume activity.<br>
     * CN:恢复活动。
     */
    private void resumeActivity()
    {
        mMultiScreenControlService.setTopActivity(MultiScreenControlService.TopActivity.discovery);

        resetAccessListener();
        clearSceneListener();
        checkCurrentDevice();
        searchDelay();
        showListDelay();
    }

    /**
     * Reset access listener.
     */
    private void resetAccessListener()
    {
        mMultiScreenControlService.setOriginalDeviceListListener(mIOriginalDeviceListListener);
        mMultiScreenControlService.setAllAccessListener(mAccessListener);
    }

    /**
     * Clear scene listener.<br>
     * CN:设备发现页面清空场景监听。
     */
    private void clearSceneListener()
    {
        mMultiScreenControlService.setSceneListener(null);
    }

    /**
     * Handler of message.<br>
     * CN:消息处理者。
     */
    private class SyncListHandler extends Handler
    {
        public SyncListHandler(Looper looper)
        {
            super(looper);
        }

        @Override
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case MSG_SHOWLIST_DELAY:
                {
                    showList();
                }
                    break;
                case MSG_MSEARCH_DELAY:
                {
                    int retryTimes = msg.getData().getInt(MSG_DATA_KEY_RETRY_TIMES);
                    long delayTime = msg.getData().getLong(MSG_DATA_KEY_DELAY_TIME);
                    mMultiScreenControlService.getDeviceDiscover().msearch();
                    LogTool.d("Do msearch " + (MSEARCH_RETRY_TIMES - retryTimes + 1) + " times");

                    retryTimes--;
                    if (retryTimes > 0)
                    {
                        delayTime += RE_SEARCH_DELAY_MILLIS;
                        retrySearchDelay(retryTimes, delayTime);
                    }
                }
                    break;
                case MSG_MESARCH:
                {
                    mMultiScreenControlService.getDeviceDiscover().msearch();
                }
                    break;
                default:
                    break;
            }
        }
    }

    /**
     * Initialize handler.<br>
     */
    private void initHandler()
    {
        mHandlerThread = new HandlerThread("DiscoveryHandlerThread");
        mHandlerThread.start();
        ListHandler = new SyncListHandler(mHandlerThread.getLooper());
        mShowDeviceListHandler = new DeviceListHandler(this);
    }

    /**
     * DeInit handler.<br>
     */
    private void deInitHandler()
    {
        if (mHandlerThread != null)
        {
            clearShowListMessage();
            clearSearchMessage();
            mHandlerThread.getLooper().quit();
        }
    }

    /**
     * Clear showlist message in handler.<br>
     */
    private void clearShowListMessage()
    {
        if (ListHandler.hasMessages(MSG_SHOWLIST_DELAY))
        {
            ListHandler.removeMessages(MSG_SHOWLIST_DELAY);
        }
    }

    /**
     * Show list delay.<br>
     * CN:延迟显示列表。
     */
    private void showListDelay()
    {
        clearShowListMessage();
        Message msg = ListHandler.obtainMessage(MSG_SHOWLIST_DELAY);
        ListHandler.sendMessageDelayed(msg, SHOWLIST_DELAY_MILLIS);
    }

    /**
     * Show list in order.<br>
     */
    private void showList()
    {
        mMultiScreenControlService.getDeviceDiscover().syncOrderingList();
        mDeviceListHandler.updateDeviceList();
    }

    /**
     * Hide list of device list.<br>
     * CN:隐藏设备列表。
     */
    private void hideList()
    {
        if (mDeviceListPop != null)
        {
            mDeviceListPop.dismiss();
        }
    }

    /**
     * Clear M-SEARCH message.<br>
     * CN:清楚搜索消息。
     */
    private void clearSearchMessage()
    {
        if (ListHandler.hasMessages(MSG_MSEARCH_DELAY))
        {
            ListHandler.removeMessages(MSG_MSEARCH_DELAY);
        }

        if (ListHandler.hasMessages(MSG_MESARCH))
        {
            ListHandler.removeMessages(MSG_MESARCH);
        }
    }

    /**
     * Retry M-SEARCH if device list is empty after delay time.<br>
     * CN:延迟时间过后，列表仍然为空则重新发送搜索消息。
     * @param retryTimes - CN:重试次数。
     * @param delayTime - CN:延迟时间。
     */
    private void retrySearchDelay(int retryTimes, long delayTime)
    {
        if (mMultiScreenControlService.isRunning() && retryTimes < MSEARCH_RETRY_TIMES)
        {
            // CN:如果已接入，并且不是第一次调用，则停止搜索。
            return;
        }

        if ((retryTimes <= 0) || (delayTime <= 0))
        {
            LogTool.e("Arguments are error!");
            return;
        }

        clearSearchMessage();

        Message msg = ListHandler.obtainMessage(MSG_MSEARCH_DELAY);
        Bundle data = new Bundle();
        data.putInt(MSG_DATA_KEY_RETRY_TIMES, retryTimes);
        data.putLong(MSG_DATA_KEY_DELAY_TIME, delayTime);
        msg.setData(data);
        ListHandler.sendMessageDelayed(msg, delayTime);
    }

    private void searchDelay()
    {
        clearSearchMessage();
        Message msg = ListHandler.obtainMessage(MSG_MESARCH);
        ListHandler.sendMessageDelayed(msg, SEARCH_DELAY_MILLIS);
    }

    /**
     * Show device list on view.
     */
    private void showListView()
    {
        if (mDeviceListPop != null)
        {
            mDeviceListPop.updateAdapter();
        }
    }

    /**
     * Handler of device list.
     */
    private static class DeviceListHandler extends Handler
    {
        SoftReference<DeviceDiscoveryActivity> mActivityReference = null;

        DeviceListHandler(DeviceDiscoveryActivity activity)
        {
            mActivityReference = new SoftReference<DeviceDiscoveryActivity>(activity);
        }

        public void handleMessage(Message msg)
        {

            DeviceDiscoveryActivity thisActivity = mActivityReference.get();
            if (thisActivity == null)
            {
                LogTool.e("get activity fail.");
                return;
            }

            switch (msg.what)
            {
                case MessageDef.MSG_DEVICE_IP_LIST_UPDATE:
                {
                    // Show device list. CN:显示设备列
                    thisActivity.showListView();
                }
                    break;

                case MessageDef.MSG_CANNOT_VISIT_DEVICE:
                {
                    // device info can not be null
                    LogTool.e("device info is null!");
                    Toast.makeText(thisActivity,
                        thisActivity.getResources().getString(R.string.device_refuse_access),
                        Toast.LENGTH_SHORT).show();
                }
                    break;

                case MessageDef.MSG_IP_ADDRESS_INVALID:
                {
                    LogTool.e("Ip address is invalid!");
                    Toast.makeText(thisActivity,
                        thisActivity.getResources().getString(R.string.access_address_invalid),
                        Toast.LENGTH_SHORT).show();
                    break;
                }

                case MessageDef.MSG_AUTO_CONNECT_DEVICE:
                {
                    // CN:连接上次设备
                    String uuid = (String) msg.obj;
                    thisActivity.autoConnectDevice(uuid);
                }
                    break;

                default:
                    break;
            }
        }
    }

    /**
     * CN:UI更新设备名称。
     */
    private void updateDeviceName(final String name)
    {
        Message msg = myHandler.obtainMessage(MessageDef.DEVICE_INFO, name);
        myHandler.sendMessage(msg);
    }

    private Handler myHandler = new Handler()
    {
        @Override
        public void handleMessage(Message msg)
        {// 设备连上界面状态修改
            switch (msg.what)
            {
                case MessageDef.DEVICE_INFO:
                {
                    String friendlyname = (String) msg.obj;
                    if (friendlyname == null)
                    {
                        friendlyname = "";
                    }
                    mDevice_title_info.setText(friendlyname);
                    mDeVice_title_disconnected.setImageResource(R.drawable.device_connected_normal);
                    mDevice_child.mDevice_no_connect.setVisibility(View.INVISIBLE);
                    mDevice_child.mDevice_connect.setVisibility(View.VISIBLE);
                    mDevice_title_info.invalidate();
                }
                    break;
                case MessageDef.EXIT_APP:
                {
                    canDestroy = false;
                }
                    break;
                default:
                    break;
            }
            super.handleMessage(msg);
        }
    };

    private void connectDelay(String uuid)
    {
        if (isTarget(uuid))
        {
            clearConnectMessage();
            Message msg =
                mShowDeviceListHandler.obtainMessage(MessageDef.MSG_AUTO_CONNECT_DEVICE, uuid);
            mShowDeviceListHandler.sendMessageDelayed(msg, CONNECT_DELAY_MILLIS);
        }
    }

    /**
     * Clear auto connect message.<br>
     */
    private void clearConnectMessage()
    {
        if (mShowDeviceListHandler.hasMessages(MessageDef.MSG_AUTO_CONNECT_DEVICE))
        {
            mShowDeviceListHandler.removeMessages(MessageDef.MSG_AUTO_CONNECT_DEVICE);
        }
    }

    /**
     * Auto connect device.<br>
     * CN:自动连接。
     */
    private void autoConnectDevice(String uuid)
    {
        if (isReadyForAutoConnect() == false)
        {
            LogTool.d("It is not ready for auto connect, try manual connect.");
            return;
        }
        else if (isTarget(uuid) == false)
        {
            return;
        }

        Device device = mMultiScreenControlService.getDeviceDiscover().getDeviceByUUID(uuid);
        String currUuid = "";
        if (device == null)
        {
            LogTool.e("Device is null!");
            return;
        }

        Device currentDevice = mMultiScreenControlService.getControlPoint().getCurrentDevice();
        if (currentDevice != null)
        {
            currUuid = currentDevice.getUDN();
        }

        if (!uuid.equals(currUuid))
        {
            connectDevcie(device);
        }
        else if (mMultiScreenControlService.isRunning())
        {
            // CN:当设备更新，但UUID没变化，仍需要更新设备名称。
            updateDeviceName(device.getFriendlyName());
        }
    }

    /**
     * Select device.<br>
     * CN:选择设备。
     */
    private synchronized void manualConnectDevice(Device device)
    {
        beginManualConnect(device);
        if (device == null)
        {
            // device info can not be null
            LogTool.e("device info is null!");
            mShowDeviceListHandler.sendEmptyMessage(MessageDef.MSG_CANNOT_VISIT_DEVICE);
            endManualConnect();
            return;
        }
        else if (device.getServiceList().isEmpty())
        {
            // device service is null
            String title = getResources().getString(R.string.networkConnectTitle);
            String tips = "Device Service is null";
            DialogUtils.showDialog(this, title, tips, new DialogInterface.OnClickListener()
            {
                public void onClick(DialogInterface arg0, int arg1)
                {
                }
            });
            endManualConnect();
            return;
        }
        else
        {
            Device currentDevice = mMultiScreenControlService.getControlPoint().getCurrentDevice();
            if (currentDevice != null)
            {
                // CN:当前设备不为空。
                String currentUuid = currentDevice.getUDN();
                if (mMultiScreenControlService.isRunning())
                {
                    // CN:当前已经连入一个设备。
                    if (currentUuid.equals(device.getUDN()))
                    {
                        // CN:相同设备，不连接
                        updateDeviceName(device.getFriendlyName());
                        endManualConnect();
                        return;
                    }
                    else
                    {
                        // CN:设备切换，断开前一个保活
                        // CN:未进入mirror，不需要向上一设备发送byebye
                        deInitNetworkChecker(Caller.Others, ClientState.DEINIT);
                        clearCurrentDevice();
                    }
                }
                else
                {
                    mMultiScreenControlService.getControlPoint().setCurrentDevice(null);
                }
            }

            // CN:接入新设备。
            if (connectDevcie(device) == false)
            {
                // Fail: can not access STB.
                String title = this.getResources().getString(R.string.networkConnectTitle);
                DialogUtils.showDialog(this, title,
                    this.getResources().getString(R.string.AccessController_refuse_access_tips),
                    new DialogInterface.OnClickListener()
                    {
                        public void onClick(DialogInterface arg0, int arg1)
                        {
                        }
                    });
            }
        }
        endManualConnect();
    }

    private void beginManualConnect(Device device)
    {
        ServiceUtil.saveUuid(device.getUDN());
        isManualConnecting = true;
        clearConnectMessage();
    }

    private void endManualConnect()
    {
        isManualConnecting = false;
        hideList();
    }

    private boolean isReadyForAutoConnect()
    {
        if (isManualConnecting || mMultiScreenControlService.isReady() == false)
        {
            return false;
        }
        return true;
    }

    private void gotoRemote()
    {
        Intent intent = new Intent(this, RemoteActivity.class);
        SceneType scene = SceneType.REMOTE_TOUCH;

        if (MultiScreenControlService.isSceneOpen())
        {
            scene = MultiScreenControlService.getScene();
        }

        switch (scene)
        {
            case REMOTE_TOUCH:
            {
                intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, MessageDef.REMOTE_TOUCH);
            }
                break;

            case REMOTE_AIRMOUSE:
            {
                intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, MessageDef.REMOTE_AIRMOUSE);
            }
                break;

            default:
            {
                intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, MessageDef.REMOTE_TOUCH);
            }
                break;
        }

        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        startActivity(intent);
    }

    /**
     * CN:进入镜像界面，如果设备只有一个，连接成功直接进入镜像界面，如果多个，请手动选择设备连接。
     */
    private void gotoMirror()
    {
        if (mMultiScreenControlService.isRunning())
        {
            startMultiScreen();
            return;
        }

        if (isFirst())
        {
            if (devList == null)
            {
                DialogUtils.showToast(
                    mContext.getResources().getString(R.string.DeviceConnect_box), mContext);
            }
            else if (devList.size() == 1)
            {
                Device mDevice = devList.getDevice(0);
                connectDevcie(mDevice);
                if (mMultiScreenControlService.isRunning())
                {
                    startMultiScreen();
                }
            }
            else
            {
                DialogUtils.showToast(
                    mContext.getResources().getString(R.string.DeviceConnect_box), mContext);
            }
        }
        else
        {
            Device currentDevice = mMultiScreenControlService.getControlPoint().getCurrentDevice();
            if ((mMultiScreenControlService.isRunning() == false) && (currentDevice != null))
            {
                connectDevcie(currentDevice);
                if (mMultiScreenControlService.isRunning())
                {
                    startMultiScreen();
                }
            }
            else
            {
                DialogUtils.showToast(
                    mContext.getResources().getString(R.string.DeviceConnect_box), mContext);
            }
        }
    }

    /**
     * CN:设备连接。
     */
    private boolean connectDevcie(Device device)
    {
        boolean isAccess = false;
        if (device == null)
        {
            LogTool.e("device is null!");
            isAccess = false;
        }
        else if (canAccess(device))
        {
            initLocalState();
            connectSuccess(device);
            isAccess = true;
        }
        else
        {
            LogTool.d("Access failed: remove device.");
            clearCurrentDevice();
            mMultiScreenControlService.getDeviceDiscover().removeCannotAccessDevice(device);
            isAccess = false;
        }
        return isAccess;
    }

    /**
     * Judge whether the phone can access the STB.<br>
     * CN：判断是否可以接入STB。<br>
     * 
     * @param device upnp device.<br>
     *        CN:UPnP设备 。<br>
     * @return true the phone can access the STB, false the phone can't access
     *         the STB.<br>
     *         CN:true 代表可以接入，false 代表不可以接入。<br>
     */
    private boolean canAccess(Device device)
    {
        LogTool.d("Try to access device.");
        boolean retCanAccess = false;
        String remoteId = getRemoteId();

        String localIP = getWifiIpAddress();

        mMultiScreenControlService.getControlPoint().setCurrentDevice(device);
        mMultiScreenControlService.getControlPoint().setRemoteId(remoteId);

        retCanAccess =
            mAccessController.accessHello(remoteId, localIP, ACCESS_CONNECT_TIMEOUT, READ_TIMEOUT);
        LogTool.i("Access STB is " + retCanAccess);

        return retCanAccess;
    }

    /**
     * Initialize local state.
     */
    private void initLocalState()
    {
        mMultiScreenControlService.init();
        mMultiScreenControlService.setAccessControllerListener(mAccessListener);
        syncInfo();
    }

    private void connectSuccess(Device device)
    {
        ServiceUtil.saveUuid(device.getUDN());
        save_ip = HostNetInterface.uri2Ip(device.getLocation());
        updateDeviceName(device.getFriendlyName());
        // sendBroadcast("Connect");
    }

    /**
     * Sync info of STB.<br>
     * CN:同步STB信息。
     */
    private void syncInfo()
    {
        if (mMultiScreenControlService.isRunning())
        {
            // CN:从HOME恢复主活动。
            LogTool.d("Resume Activity from HOME.");
            // CN:不需要重启网络监听
        }
        else
        {
            if (mMultiScreenControlService.canSyncInfo())
            {
                // CN:启动网络状态检查时，重置服务状态为RUNNING。
                // TODO CN:设备连续上线，可能重复触发保活。
                initNetworkChecker();
            }
            else
            {
                // CN:同步STB数据失败。
                LogTool.e("sync STB info failed!");
                mMultiScreenControlService.setState(ClientState.NETWORK_LOST);
            }
        }
    }

    /**
     * Start network check for all activities.<br>
     * CN:为所有活动启动网络状态检查。
     */
    private void initNetworkChecker()
    {
        LogTool.d("initNetworkChecker");
        mMultiScreenControlService.startPing();
    }

    /**
     * CN:界面处理：可设置顶部提示文字。
     * @param titleText
     */
    private void disconnectOnUi(String titleText)
    {
        mDisonnectText = titleText;
        runOnUiThread(mDisconnectOnUiRunnable);
    }

    /**
     * CN:界面处理：未连接。
     */
    private void disconnectOnUi()
    {
        // sendConnectionStateBroadcast(getConnectionState());
        String titleText = mContext.getResources().getString(R.string.device_select_no_connect);
        disconnectOnUi(titleText);
    }

    /**
     * CN:界面处理：抢占。
     */
    private void reavedOnUi()
    {
        String titleText = getResources().getString(R.string.device_select_be_reaved);
        disconnectOnUi(titleText);
    }

    /**
     * Set strict mode.<br>
     */
    @SuppressLint("NewApi")
    private void setStrictMode()
    {
        StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder().detectDiskReads()
            .detectDiskWrites().detectNetwork().penaltyLog().build());
    }

    /**
     * Get remote id by server ip. CN:通过服务端IP获取手机上同一网段的IP。
     * 
     * @param serverIp - ip of server.
     * @return remote id.
     */
    private String getRemoteId()
    {
        String mac = getMacAddress();
        return mac;

    }

    /**
     * Get local MAC address. CN: 获取手机MAC地址。
     * 
     * @return - MAC address
     */
    private String getMacAddress()
    {
        String macAddress = null;
        WifiManager wifiMgr = (WifiManager) getSystemService(Context.WIFI_SERVICE);
        WifiInfo info = (null == wifiMgr ? null : wifiMgr.getConnectionInfo());
        if (null != info)
        {
            macAddress = info.getMacAddress();
            // ip = info.getIpAddress();
        }

        return macAddress;
    }

    /**
     * Get local IP address.<br>
     * CN: 获取手机IP地址。
     * @return - IP address
     */
    private String getWifiIpAddress()
    {
        String ipAddress = null;
        WifiManager wifiMgr = (WifiManager) getSystemService(Context.WIFI_SERVICE);
        WifiInfo info = (null == wifiMgr ? null : wifiMgr.getConnectionInfo());
        if (null != info)
        {
            ipAddress = HostNetInterface.int2Ip(info.getIpAddress());
        }

        return ipAddress;
    }

    /**
     * CN:广电直播，媒体分享，遥控器，镜像的模块显示，及相应点击的处理。
     */
    class GridViewAdapter extends BaseAdapter
    {

        private LayoutInflater inflater;

        private Integer[] mImageId;

        private String[] mtag;

        private String[] mtags_info;

        private HashMap<String, SoftReference<Bitmap> > map = new HashMap<String, SoftReference<Bitmap>>();

        public GridViewAdapter(Integer[] mImageIds, String[] mtags, String[] mtags_info,
            Context context)
        {
            super();
            map.clear();

            this.mImageId = mImageIds;
            this.mtag = mtags;
            this.mtags_info = mtags_info;

            inflater = LayoutInflater.from(context);
            for (int i = 0; i < mImageIds.length; i++)
            {

                BitmapFactory.Options opts = new BitmapFactory.Options();
                opts.inSampleSize = 1;
                SoftReference<Bitmap> bmp = new SoftReference<Bitmap>(
                    BitmapFactory.decodeResource(context.getResources(), mImageIds[i], opts));
                map.put(mImageIds[i] + "", bmp);
            }

        }

        @Override
        public int getCount()
        {

            return map.size();
        }

        @Override
        public Object getItem(int position)
        {

            return null;
        }

        @Override
        public long getItemId(int position)
        {

            return 0;
        }

        @Override
        public View getView(final int position, View convertView, ViewGroup parent)
        {

            final ViewHolder viewHolder;
            if (convertView == null)
            {
                convertView = inflater.inflate(R.layout.device_item_view, null);
                viewHolder = new ViewHolder();

                viewHolder.mDevice_image =
                    (ImageView) convertView.findViewById(R.id.device_imageview);
                viewHolder.mDevice_tag = (TextView) convertView.findViewById(R.id.device_tag);
                viewHolder.mDevice_tag_info =
                    (TextView) convertView.findViewById(R.id.device_tag_info);
                viewHolder.mDevice_layer = (ImageView) convertView.findViewById(R.id.device_layer);
                convertView.setTag(viewHolder);
            }
            else
            {
                viewHolder = (ViewHolder) convertView.getTag();
            }

            viewHolder.mDevice_image.setAdjustViewBounds(true);
            viewHolder.mDevice_image.setScaleType(ImageView.ScaleType.FIT_XY);
            viewHolder.mDevice_layer.setScaleType(ImageView.ScaleType.FIT_XY);
            SoftReference<Bitmap> bit1 = map.get(mImageId[position] + "");
            SoftReference<Bitmap> bit = null ;
            Bitmap bitmap = null;
            if(bit1 != null)
            {
                bit = preScaleBitmap(bit1.get());
                if(bit != null)
                    bitmap = bit.get();
            }

            if (bitmap != null)
            {
                viewHolder.mDevice_image.setImageBitmap(bitmap);
            }
            else
            {
                BitmapFactory.Options opts = new BitmapFactory.Options();
                opts.inSampleSize = 1;
                SoftReference<Bitmap> bmp = new SoftReference<Bitmap>(
                    BitmapFactory.decodeResource(convertView.getResources(), mImageId[position],
                        opts));
                map.put(mImageId[position] + "", bmp);
                viewHolder.mDevice_image.setImageBitmap(bmp.get());
            }
            viewHolder.mDevice_tag.setText(mtag[position]);
            viewHolder.mDevice_tag_info.setText(mtags_info[position]);
            viewHolder.mDevice_image.setOnTouchListener(new View.OnTouchListener()
            {

                @Override
                public boolean onTouch(View v, MotionEvent event)
                {
                    Intent intent;
                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        viewHolder.mDevice_layer.setVisibility(View.VISIBLE);
                    }
                    else if (event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        viewHolder.mDevice_layer.setVisibility(View.INVISIBLE);
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP)
                    {
                        viewHolder.mDevice_layer.setVisibility(View.INVISIBLE);
                        switch (mImageId[position])
                        {
                            case R.drawable.device_live_tv:// 需将STB的IP传过去
                                intent =
                                    new Intent(DeviceDiscoveryActivity.this, LiveTVActivity.class);
                                Device dev =
                                    mMultiScreenControlService.getControlPoint().getCurrentDevice();
                                intent.putExtra("STBIP",
                                    dev != null ? HostNetInterface.uri2Ip(dev.getLocation())
                                        : "STBIP");
                                startActivity(intent);
                                break;

                            case R.drawable.device_airsharing:// 需将STB的IP传过去
                                intent =
                                    new Intent(DeviceDiscoveryActivity.this,
                                        DMSBrowseActivity.class);
                                Device device =
                                    mMultiScreenControlService.getControlPoint().getCurrentDevice();
                                intent.putExtra("STBIP",
                                    device != null ? HostNetInterface.uri2Ip(device.getLocation())
                                        : "STBIP");
                                intent.putExtra("ConnectStatue", MultiScreenControlService
                                    .getInstance().isRunning());
                                startActivity(intent);
                                break;

                            case R.drawable.device_telecontroller:
                            {
                                gotoRemote();
                            }
                                break;

                            case R.drawable.device_image_control:
                            {
                                gotoMirror();
                            }
                                break;
                            default:
                                break;
                        }
                    }
                    return true;
                }
            });

            return convertView;
        }

        /**
         * CN:按比例放大缩小图片。
         */
        public SoftReference<Bitmap> preScaleBitmap(Bitmap temp)
        {
            if(temp == null)
                return null;
            float scaleWidth = displayWidth - 35 * 2;
            float scale = scaleWidth / temp.getWidth();
            Matrix matrix = new Matrix();
            matrix.postScale(scale, scale);
            SoftReference<Bitmap> temp2 =new SoftReference<Bitmap>(
                Bitmap.createBitmap(temp, 0, 0, temp.getWidth(), temp.getHeight(), matrix, true));
            return temp2;
        }

        class ViewHolder
        {

            public ImageView mDevice_image;

            public TextView mDevice_tag;

            public TextView mDevice_tag_info;

            public ImageView mDevice_layer;

        }
    }

    private void startMultiScreen()
    {
        Intent intent = new Intent(this, MultiScreenActivity.class);
        SceneType scene = SceneType.MIRROR;

        if (MultiScreenControlService.isSceneOpen())
        {
            scene = MultiScreenControlService.getScene();
        }

        switch (scene)
        {
            case MIRROR_SENSOR:
            {
                intent.putExtra(MessageDef.INTENT_MIRROR_STATUS, MessageDef.MIRROR_STATUS_SENSOR);
            }
                break;

            case MIRROR:
            {
                intent.putExtra(MessageDef.INTENT_MIRROR_STATUS, MessageDef.MIRROR_STATUS_DEFAULT);
            }
                break;

            default:
            {
                intent.putExtra(MessageDef.INTENT_MIRROR_STATUS, MessageDef.MIRROR_STATUS_DEFAULT);
            }
                break;
        }

        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        startActivity(intent);
    }

    /**
     * @deprecated
     * @param state
     */
    private void sendConnectionStateBroadcast(boolean state)
    {
        // if (state)
        // {
        // sendBroadcast(new Intent(DEVICE_CONNECT));
        // }
        // else
        // {
        // sendBroadcast(new Intent(DEVICE_DISCONNECT));
        // }
    }

    /**
     * @deprecated
     * @param type
     */
    private void sendBroadcast(String type)
    {
        System.out.println("come into send broadcast!" + type);
        Intent intent = new Intent();
        intent.setAction("com.device.access");
        intent.putExtra("Type", type);
        // sendBroadcast(intent);
    }
}
