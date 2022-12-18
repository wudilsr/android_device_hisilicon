package com.hisilicon.multiscreen.mybox;

import java.lang.ref.SoftReference;

import org.cybergarage.upnp.Device;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.os.SystemClock;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.OrientationEventListener;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.multiscreen.controller.AccessUpnpController;
import com.hisilicon.multiscreen.controller.IAccessListener.Caller;
import com.hisilicon.multiscreen.gsensor.IShakeListener;
import com.hisilicon.multiscreen.gsensor.ShakeMe;
import com.hisilicon.multiscreen.mybox.DeviceListShow.ClickCallback;
import com.hisilicon.multiscreen.mybox.MultiScreenControlService.ClientState;
import com.hisilicon.multiscreen.protocol.message.KeyInfo;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.utils.HostNetInterface;
import com.hisilicon.multiscreen.protocol.utils.ISpeechMsgDealer;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.ServiceUtil;
import com.hisilicon.multiscreen.protocol.utils.SpeechRecognizer;
import com.hisilicon.multiscreen.vime.VImeClientControlService;

/**
 * Remote activity.<br>
 * CN：遥控器界面，含REMOTE_KEY、REMOTE_TOUCH、AIRMOUSE。
 */
public class RemoteActivity extends BaseActivity implements OnTouchListener
{
    /**
     * context of this.
     */
    public static Context mContext = null;

    /**
     * CN：返回按键。
     */
    private Button mRemote_head_back;

    /**
     * CN：菜单按键。
     */
    private Button mRemote_head_menu;

    /**
     * CN：菜单按钮的子布局。
     */
    private RemoteParent mPopwin;

    /**
     * Disconnect on UI.<br>
     */
    private Runnable mDisconnectOnUiRunnable;

    /**
     * CN：设备连接的显示信息。
     */
    private static TextView mRemote_head_title;

    /**
     * CN:未连接的提示信息。
     */
    public static String mDisonnectText = null;

    /**
     * CN：设备连接的显示图标。
     */
    public static ImageView mRemote_head_disconnected;

    /**
     * CN:设备名称底部高亮效果。
     */
    private ImageView mRemote_light;

    /**
     * CN：滑动模式界面。
     */
    public static RemoteTouchView mRemoteTouchView;

    /**
     * CN：按键模式界面。
     */
    private RemoteKeyboardView mRemoteKeyboardView;

    private int keyboard_width = 0;

    private int keyboard_height = 0;

    private int x = 0;

    private int y = 0;

    /**
     * CN：数字键盘界面。
     */
    private RemoteNumber mNumberPop;

    /**
     * CN：home按键。
     */
    private Button mRemote_child_home;

    /**
     * CN：menu按键。
     */
    private Button mRemote_child_menu;

    /**
     * CN：静音按键。
     */
    private Button mRemote_child_mute;

    /**
     * CN：音量+按键。
     */
    private Button mRemote_child_volume_max;

    /**
     * CN：音量-按键。
     */
    private Button mRemote_child_volume_min;

    /**
     * CN：遥控器弹出数字键盘界面的按钮。
     */
    private Button mRemote_bottom_number;

    /**
     * CN：遥控器的返回按钮。
     */
    private Button mRemote_bottom_back;

    /**
     * CN：遥控器的声音按钮。
     */
    private Button mRemote_bottom_voice;

    /**
     * CN：未连接机顶盒的动画布局。
     */
    private View mRemote_device_not_found;

    /**
     * Detector of orientation, for auto mirror.<br>
     * CN:方向监听，用于横屏自动Mirror。
     */
    private OrientationDetector mOrientationDetector = null;

    /**
     * Detector of shake phone.<br>
     * CN:摇一摇监控类。
     */
    private ShakeMe mShakeMe = null;

    /**
     * Listener of shake.<br>
     */
    private IShakeListener mShakeListener = null;

    private Handler myHandler = new Handler();

    private static DeviceListShow mDeviceListPop;

    private HandlerThread mHandlerThread = null;

    /**
     * Sync list handler.<br>
     * CN:发送搜索消息、同步搜索结果。
     */
    private SyncListHandler ListHandler = null;

    /**
     * Remote activity handler.<br>
     * CN:遥控器活动消息处理，用于依赖主线程的事件处理。
     */
    private RemoteActivityHandler mRemoteActivityHandler = null;

    private boolean vime_status;

    private boolean isManualConnecting = false;

    private volatile boolean canDestroy = false;

    /**
     * Pop click listener of remote status select.
     */
    private OnClickListener mPopClickListener = null;

    private SpeechRecognizer mSpeechRecognitioner = null;

    private ISpeechMsgDealer mSpeechMsgDealer = new ISpeechMsgDealer()
    {
        @Override
        public void pushSpeechInfo(String result, int type)
        {
            if ((null != result) && (mRemoteSpeech != null))
            {
                // send first
                LogTool.d("send speech info" + result);
                mRemoteSpeech.sendSpeechInfo(result, type);
            }
        }

        @Override
        public void startSpeaking()
        {
            if (mRemoteSpeech != null)
            {
                mRemoteSpeech.startSpeak();
            }
        }

        @Override
        public void stopSpeaking()
        {
            if (mRemoteSpeech != null)
            {
                mRemoteSpeech.stopSpeak();
            }
        }

        @Override
        public void pushAudioData(byte[] audiodate, int seq)
        {
            if (mRemoteSpeech != null)
            {
                mRemoteSpeech.sendAudioDate(audiodate, seq);
            }
        }

        @Override
        public void speakError(String error)
        {
            if ((mRemoteSpeech != null))
            {
                mRemoteSpeech.sendErrorInfo(error);
            }
        }
    };

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
                // CN:必须延迟显示或提前删除副本中设备，因为cyberlink remove
                // listener回调时，原始设备还存在，不能直接显示原始列表。
                showListDelay();
            }
        };

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mybox_remote);
        initView();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        resumeActivity();
    }

    @Override
    protected void onPause()
    {
        super.onPause();
        disableOrientationDetector();
        // CN:暂停摇一摇。
        mShakeMe.disable();
        // CN:暂停空鼠。
        mRemoteTouchView.disableAirMouse();
    }

    @Override
    protected void onStop()
    {
        super.onStop();
    }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        mContext = null;
        stopVIME();
        deInitHandler();
        unbindDrawables(findViewById(R.layout.mybox_remote));
    }

    @Override
    public void onBackPressed()
    {
        super.onBackPressed();
        gotoDeviceDiscovery();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        // if (keyCode == KeyEvent.KEYCODE_BACK)
        // {
        // if (isHomePageRemote)
        // {
        // // CN:若首页为遥控器，则采用双击退出，并销毁服务。
        // if (canDestroy)
        // {
        // destroy();
        // }
        // else
        // {
        // canDestroy = true;
        // mRemoteActivityHandler.sendEmptyMessageDelayed(MessageDef.EXIT_APP,
        // MessageDef.BACK_PRESSED_MILLIS);
        // Toast.makeText(this, R.string.one_more_exit,
        // Toast.LENGTH_SHORT).show();
        // }
        // return true;
        // }
        // }

        return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onTouch(View v, MotionEvent event)
    {
        handleTouch(v, event);
        return true;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    protected void initData()
    {
        super.initData();
        mContext = this;
        mRemoteUiStatus = DEFAULT_REMOTE_UI_STATUS;
        vime_status = readStatusPreference(MultiSettingActivity.VIME_STATUS_KEY);
        mRemoteActivityHandler = new RemoteActivityHandler(this);
        mPopClickListener = new PopwinClickEvent();
        mPopwin = new RemoteParent(this, mPopClickListener);
        initOrientationDetector();
        mDisconnectOnUiRunnable = new Runnable()
        {
            @Override
            public void run()
            {
                if (mRemote_head_title != null)
                {
                    mRemote_head_title.setText(mDisonnectText);
                    mRemote_head_disconnected
                        .setImageResource(R.drawable.device_disconnected_normal);
                }
                // warnLayoutFlash();
            }
        };
        initShakeMe();
        initHandler();
        initSpeechModule();
    }

    /**
     * CN:手机方向监听。<br>
     * CN:横屏切换到传屏，竖屏切换遥控器。
     */
    private void initOrientationDetector()
    {
        // FIXME CN:横竖屏切换暂不使用，与体感冲突。
        // mOrientationDetector = new MyOrientationDetector(this);
    }

    private void enableOrientationDetector()
    {
        if (mOrientationDetector != null)
        {
            mOrientationDetector.enable();
        }
    }

    private void disableOrientationDetector()
    {
        if (mOrientationDetector != null)
        {
            mOrientationDetector.disable();
        }
    }

    private void initSpeechModule()
    {
        SpeechRecognizer.loginServer(mContext);
        mSpeechRecognitioner = new SpeechRecognizer();
        mSpeechRecognitioner.setSpeechDeal(mSpeechMsgDealer);
    }

    private void initShakeMe()
    {
        mShakeListener = new IShakeListener()
        {
            @Override
            public void shake(int times, int level)
            {
                if (mRemoteTouchView.isAirMouseOpen() == false)
                {
                    updateAirMouseView();
                    mShakeMe.doVibrate();
                }
            }
        };
        mShakeMe = new ShakeMe(this, mShakeListener);
    }

    /**
     * Initialize view of activity.<br>
     * CN:初始化活动界面。
     */

    private void initView()
    {
        LogTool.d("initView");

        mRemote_head_title = (TextView) findViewById(R.id.remote_head_title);
        mDisonnectText = getResources().getString(R.string.device_select_no_connect);
        mRemote_head_disconnected = (ImageView) findViewById(R.id.remote_head_disconnected);
        mRemote_light = (ImageView) findViewById(R.id.mybox_remote_light);
        mRemote_device_not_found = findViewById(R.id.remote_not_found_layout);

        // touch
        mRemoteTouchView = (RemoteTouchView) findViewById(R.id.mybox_remote_touchs);
        // mRemoteTouchView.setVisibility(View.VISIBLE);

        // keyboard
        mRemoteKeyboardView = (RemoteKeyboardView) findViewById(R.id.mybox_remote_keyboards);
        mRemoteKeyboardView.setVisibility(View.VISIBLE);

        mRemoteKeyboardView.mRemote_keyboard_btn.setOnTouchListener(this);

        mRemote_head_back = (Button) findViewById(R.id.remote_head_back);
        mRemote_head_back.setOnTouchListener(this);

        mRemote_head_menu = (Button) findViewById(R.id.remote_head_menu);
        mRemote_head_menu.setOnTouchListener(this);

        mRemote_child_home = (Button) findViewById(R.id.remote_child_homes);
        mRemote_child_home.setOnTouchListener(this);

        mRemote_child_menu = (Button) findViewById(R.id.remote_child_menus);
        mRemote_child_menu.setOnTouchListener(this);

        mRemote_child_mute = (Button) findViewById(R.id.remote_child_mutes);
        mRemote_child_mute.setOnTouchListener(this);

        mRemote_child_volume_max = (Button) findViewById(R.id.remote_child_volume_maxs);
        mRemote_child_volume_max.setOnTouchListener(this);

        mRemote_child_volume_min = (Button) findViewById(R.id.remote_child_volume_mins);
        mRemote_child_volume_min.setOnTouchListener(this);

        // FIXME CN:数字键不常用，后续换到其他页面，放大返回键图标。
         mRemote_bottom_number = (Button)
         findViewById(R.id.remote_bottom_number);
         mRemote_bottom_number.setOnTouchListener(this);

        mRemote_bottom_back = (Button) findViewById(R.id.remote_bottom_back);
        mRemote_bottom_back.setOnTouchListener(this);

        mRemote_bottom_voice = (Button) findViewById(R.id.remote_bottom_voice);
        mRemote_bottom_voice.setOnTouchListener(this);
        mRemote_bottom_voice.setVisibility(View.INVISIBLE);

        mDeviceListPop = new DeviceListShow(RemoteActivity.this, new ClickCallback()
        {
            @Override
            public void clickItem(Device device)
            {
                manualConnectDevice(device);
            }
        });

        mRemote_head_title.setOnClickListener(new OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                mDeviceListPop.showAtLocation(mRemote_head_title, Gravity.BOTTOM, 0, 0);
                searchDelay();
            }
        });
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
            updateDeviceName(currentDevice.getFriendlyName());
            initModules();
        }
        else
        {
            LogTool.e("Control state is running but current device is null.");
            disconnectOnUi();
        }
    }

    /**
     * Read enable/disable record.<br>
     * CN:开启/关闭记录读取。
     * @param statusKey - CN:键值
     */
    private boolean readStatusPreference(String statusKey)
    {
        SharedPreferences prefrence =
            getSharedPreferences(MultiSettingActivity.SETTING_STATUS_FILE_NAME, MODE_PRIVATE);
        return prefrence.getBoolean(statusKey, true);
    }

    private void connectDelay(String uuid)
    {
        if (isTarget(uuid))
        {
            clearConnectMessage();
            Message msg =
                mRemoteActivityHandler.obtainMessage(MessageDef.MSG_AUTO_CONNECT_DEVICE, uuid);
            mRemoteActivityHandler.sendMessageDelayed(msg,
                DeviceDiscoveryActivity.CONNECT_DELAY_MILLIS);
        }
    }

    private void clearConnectMessage()
    {
        if (mRemoteActivityHandler.hasMessages(MessageDef.MSG_AUTO_CONNECT_DEVICE))
        {
            mRemoteActivityHandler.removeMessages(MessageDef.MSG_AUTO_CONNECT_DEVICE);
        }
    }

    /**
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
            LogTool.d("Auto connect to save device:" + uuid);
            connectDevcie(device);
        }
        else if (mMultiScreenControlService.isRunning())
        {
            // CN:当设备更新，但UUID没变化，仍需要更新设备名称。
            updateDeviceName(device.getFriendlyName());
        }
    }

    /**
     * Go into MultiScreen Activity.<br>
     * CN:进入多屏主活动界面.
     */
    private synchronized void manualConnectDevice(Device device)
    {
        beginManualConnect(device);
        if (device == null)
        {
            // device info can not be null
            LogTool.e("device info is null!");
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

    private void searchDelay()
    {
        clearSearchMessage();
        Message msg = ListHandler.obtainMessage(DeviceDiscoveryActivity.MSG_MESARCH);
        ListHandler.sendMessageDelayed(msg, DeviceDiscoveryActivity.SEARCH_DELAY_MILLIS);
    }

    private void clearSearchMessage()
    {
        if (ListHandler.hasMessages(DeviceDiscoveryActivity.MSG_MESARCH))
        {
            ListHandler.removeMessages(DeviceDiscoveryActivity.MSG_MESARCH);
        }
    }

    /**
     * Show device list on view.
     */
    private void showListView()
    {
        if (mDeviceListPop != null)
            mDeviceListPop.updateAdapter();
    }

    /**
     * CN：UI更新设备名称。
     */
    public void updateDeviceName(final String name)
    {
        clearUpdateDeviceName();
        Message msg = mRemoteActivityHandler.obtainMessage(MessageDef.DEVICE_INFO, name);
        mRemoteActivityHandler.sendMessageDelayed(msg,
            DeviceDiscoveryActivity.SHOWLIST_DELAY_MILLIS);
    }

    private void clearUpdateDeviceName()
    {
        if (mRemoteActivityHandler.hasMessages(MessageDef.DEVICE_INFO))
        {
            mRemoteActivityHandler.removeMessages(MessageDef.DEVICE_INFO);
        }
    }

    /**
     * Resume activity.<br>
     * CN:恢复活动。
     */
    private void resumeActivity()
    {
        mMultiScreenControlService.setTopActivity(MultiScreenControlService.TopActivity.remote);

        enableOrientationDetector();
        checkCurrentDevice();
        updateView();

        mMultiScreenControlService.setOriginalDeviceListListener(mIOriginalDeviceListListener);
        resetAccessListener();
        resetSceneListener();
        searchDelay();
        showListDelay();
    }

    /**
     * Update view of remote UI.<br>
     * CN:更新遥控器界面。
     */
    private void updateView()
    {
        int selectStatus =
            getIntent().getIntExtra(MessageDef.INTENT_REMOTE_STATUS, DEFAULT_REMOTE_UI_STATUS);

        switch (selectStatus)
        {
            case MessageDef.REMOTE_TOUCH:
            {
                updateTouchView();
            }
                break;

            case MessageDef.REMOTE_AIRMOUSE:
            {
                updateAirMouseView();
            }
                break;

            case MessageDef.REMOTE_KEY:
            {
                updateKeyboardView();
            }
                break;

            default:
            {
                updateTouchView();
            }
                break;
        }

        if (mPopwin != null)
        {
            mPopwin.updateBackground(mRemoteUiStatus);
        }
    }

    /**
     * Deal keeping alive failed.<br>
     * CN:网络断开处理。
     */
    @Override
    protected void dealNetfailedStatus(Caller caller)
    {
        super.dealNetfailedStatus(caller);
        disconnectOnUi();
    }

    /**
     * Deal Access bye for reave.<br>
     * CN:处理抢占事件。
     */
    @Override
    protected void dealAccessByeForReave(Caller caller)
    {
        super.dealAccessByeForReave(caller);
        reavedOnUi();
    }

    /**
     * Deal STB leave.<br>
     * CN:处理STB服务关闭事件。
     */
    @Override
    protected void dealSTBLeave(Caller caller)
    {
        super.dealSTBLeave(caller);
        disconnectOnUi();
    }

    @Override
    protected void dealSTBSuppend(Caller caller)
    {
        super.dealSTBSuppend(caller);
        disconnectOnUi();
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
            clearCurrentDevice();
            mMultiScreenControlService.getDeviceDiscover().removeCannotAccessDevice(device);
            isAccess = false;
        }
        return isAccess;
    }

    /**
     * Judge whether the phone can access the STB.<br>
     * CN：判断是否可以接入STB。
     * @param device upnp device.<br>
     *        CN:UPnP设备 。<br>
     * @return true the phone can access the STB, false the phone can't access
     *         the STB.<br>
     *         CN:true 代表可以接入，false 代表不可以接入。<br>
     */
    protected boolean canAccess(Device device)
    {
        LogTool.d("Try to access device.");
        boolean retCanAccess = false;
        String remoteId = getRemoteId();

        String localIP = getWifiIpAddress();

        mMultiScreenControlService.getControlPoint().setCurrentDevice(device);
        mMultiScreenControlService.getControlPoint().setRemoteId(remoteId);

        AccessUpnpController accessController = new AccessUpnpController();
        retCanAccess =
            accessController.accessHello(remoteId, localIP,
                DeviceDiscoveryActivity.ACCESS_CONNECT_TIMEOUT,
                DeviceDiscoveryActivity.READ_TIMEOUT);
        LogTool.i("Access STB is " + retCanAccess);

        return retCanAccess;
    }

    /**
     * Initialize local state.
     */
    private void initLocalState()
    {
        mMultiScreenControlService.init();
        syncInfo();
    }

    private void connectSuccess(Device device)
    {
        ServiceUtil.saveUuid(device.getUDN());
        DeviceDiscoveryActivity.save_ip = HostNetInterface.uri2Ip(device.getLocation());
        updateDeviceName(device.getFriendlyName());
    }

    /**
     * Get remote id by server ip.<br>
     * CN:通过服务端IP获取手机上同一网段的IP。
     * @param serverIp - ip of server.
     * @return remote id.
     */
    private String getRemoteId()
    {
        String mac = getMacAddress();
        return mac;

    }

    /**
     * Get local MAC address.<br>
     * CN: 获取手机MAC地址。
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
     * @see initData() save_udn = AppPreference.getMultiScreenUDN().<br>
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
     * Show list delay.<br>
     * CN:延迟显示列表。
     */
    private void showListDelay()
    {
        clearMessage();
        Message msg = ListHandler.obtainMessage(DeviceDiscoveryActivity.MSG_SHOWLIST_DELAY);
        ListHandler.sendMessageDelayed(msg, DeviceDiscoveryActivity.SHOWLIST_DELAY_MILLIS);
    }

    /**
     * Show list in order.<br>
     */
    private void showList()
    {
        mMultiScreenControlService.getDeviceDiscover().syncOrderingList();
        mRemoteActivityHandler.sendEmptyMessage(MessageDef.MSG_DEVICE_IP_LIST_UPDATE);
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
     * Clear message in handler.<br>
     */
    private void clearMessage()
    {
        if (ListHandler.hasMessages(DeviceDiscoveryActivity.MSG_SHOWLIST_DELAY))
        {
            ListHandler.removeMessages(DeviceDiscoveryActivity.MSG_SHOWLIST_DELAY);
        }
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
                case DeviceDiscoveryActivity.MSG_SHOWLIST_DELAY:
                {
                    showList();
                }
                    break;

                case DeviceDiscoveryActivity.MSG_MESARCH:
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
        mHandlerThread = new HandlerThread("RemoteActivityHandlerThread");
        mHandlerThread.start();
        ListHandler = new SyncListHandler(mHandlerThread.getLooper());
    }

    /**
     * DeInit handler.<br>
     */
    private void deInitHandler()
    {
        if (mHandlerThread != null)
        {
            mHandlerThread.getLooper().quit();
        }
    }

    /**
     * Handler of device list.<br>
     */
    private static class RemoteActivityHandler extends Handler
    {
        SoftReference<RemoteActivity> mActivityReference = null;

        RemoteActivityHandler(RemoteActivity activity)
        {
            mActivityReference = new SoftReference<RemoteActivity>(activity);
        }

        public void handleMessage(Message msg)
        {
            RemoteActivity thisActivity = mActivityReference.get();
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

                case MessageDef.MSG_AUTO_CONNECT_DEVICE:
                {
                    // CN:连接上次设备
                    String uuid = (String) msg.obj;
                    thisActivity.autoConnectDevice(uuid);
                }
                    break;

                case MessageDef.DEVICE_INFO:
                {
                    String friendlyname = (String) msg.obj;
                    if (friendlyname == null)
                    {
                        friendlyname = "";
                    }
                    mRemote_head_title.setText(friendlyname);
                    mRemote_head_disconnected.setImageResource(R.drawable.device_connected_normal);
                }
                    break;

                case MessageDef.EXIT_APP:
                {
                    thisActivity.canDestroy = false;
                }
                    break;

                case MessageDef.MSG_GOTO_REMOTE_TOUCH:
                {
                    if (thisActivity.mRemoteUiStatus != MessageDef.REMOTE_TOUCH)
                    {
                        thisActivity.updateTouchView();
                    }
                }
                    break;

                case MessageDef.MSG_GOTO_AIRMOUSE:
                {
                    if (thisActivity.mRemoteUiStatus != MessageDef.REMOTE_AIRMOUSE)
                    {
                        thisActivity.updateAirMouseView();
                    }
                }
                    break;

                case MessageDef.MSG_GOTO_REMOTE_KEY:
                {
                    if (thisActivity.mRemoteUiStatus != MessageDef.REMOTE_KEY)
                    {
                        thisActivity.updateKeyboardView();
                    }
                }
                    break;

                case MessageDef.MSG_GOTO_MIRROR_SENSOR:
                {
                    thisActivity.startActivity(new Intent(thisActivity, MultiScreenActivity.class));
                }
                    break;

                default:
                    break;
            }
        }
    }

    /**
     * Detector of phone orientation.<br>
     */
    public class OrientationDetector extends OrientationEventListener
    {
        public OrientationDetector(Context context)
        {
            super(context);
        }

        @Override
        public void onOrientationChanged(int orientation)
        {
            if (orientation == OrientationEventListener.ORIENTATION_UNKNOWN)
            {
                // CN:手机平放时，检测不到有效的角度
            }
            else if (orientation > 260 && orientation < 280)
            { // 270度，开启mirror
              // CN:调试空鼠，关闭横屏mirror
              // gotoMirror();
            }
            // else if (orientation > 350 || orientation < 10)
            // { // 0度
            // }
            // else if (orientation > 80 && orientation < 100)
            // { // 90度
            // }
            // else if (orientation > 170 && orientation < 190)
            // { // 180度
            // }
        }
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
    public void disconnectOnUi()
    {
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
     * CN：显示设备未连接的显示动画。
     * @deprecated
     */
    private void showWarnLayout()
    {
        if (mRemote_device_not_found == null)
            return;
        Animation animation = AnimationUtils.loadAnimation(mContext, R.anim.up_slidein);
        animation.setAnimationListener(new AnimationListener()
        {
            @Override
            public void onAnimationStart(Animation animation)
            {
            }

            @Override
            public void onAnimationRepeat(Animation animation)
            {
            }

            @Override
            public void onAnimationEnd(Animation animation)
            {
                mRemote_device_not_found.clearAnimation();
                mRemote_device_not_found.setVisibility(View.VISIBLE);
            }
        });
        mRemote_device_not_found.startAnimation(animation);
    }

    /**
     * CN：隐藏设备未连接的显示动画。
     * @deprecated
     */
    private void hideWarnLayout()
    {
        if (mRemote_device_not_found == null)
            return;
        Animation animation = AnimationUtils.loadAnimation(mContext, R.anim.up_slideout);
        animation.setAnimationListener(new AnimationListener()
        {
            @Override
            public void onAnimationStart(Animation animation)
            {
            }

            @Override
            public void onAnimationRepeat(Animation animation)
            {
            }

            @Override
            public void onAnimationEnd(Animation animation)
            {
                mRemote_device_not_found.clearAnimation();
                mRemote_device_not_found.setVisibility(View.GONE);
            }
        });
        mRemote_device_not_found.startAnimation(animation);
    }

    /**
     * CN:自定义首页不需要该动画。<br>
     * CN:显示1000ms警告：未检测到机顶盒。
     * @deprecated
     */
    private void warnLayoutFlash()
    {
        if (mRemote_device_not_found == null)
            return;
        myHandler.removeCallbacks(hideRunnable);
        showWarnLayout();
        myHandler.postDelayed(hideRunnable, 1000);
    }

    /**
     * @deprecated
     */
    private Runnable hideRunnable = new Runnable()
    {
        @Override
        public void run()
        {
            hideWarnLayout();
        }
    };

    /**
     * Sync info of STB.<br>
     * CN:同步STB信息。
     */
    private void syncInfo()
    {
        if (mMultiScreenControlService.isRunning() == false)
        {
            if (mMultiScreenControlService.canSyncInfo())
            {
                // CN:启动网络状态检查时，重置服务状态为RUNNING。
                mMultiScreenControlService.startPing();
                initModules();
            }
            else
            {
                // CN:两次同步STB数据失败提示网络异常。
                LogTool.e("sync STB info failed!");
            }
        }
        else
        {
            // CN:从HOME恢复主活动。
            LogTool.d("Resume RemoteActivity from HOME.");
            initModules();
        }
    }

    /**
     * Init modules.<br>
     * CN:初始化各模块。
     */
    private void initModules()
    {
        LogTool.d("initModules");
        // Start checking network before other modules.
        resetAccessListener();
        initRemoteCenter();
        initVIME();
        initAirMouse();
    }

    /**
     * Init remote center.<br>
     * CN:初始化远程控制中心。
     */
    private void initRemoteCenter()
    {
        LogTool.d("initRemoteCenter");

        mRemoteControlCenter = MultiScreenControlService.getInstance().getRemoteControlCenter();
        // Virtual keyboard object.
        // CN:虚拟键盘对象。
        mKeyboard = mRemoteControlCenter.getRemoteKeyboard();
        mRemoteSpeech = mRemoteControlCenter.getRemoteSpeechControl();
    }

    /**
     * Start vime control service.<br>
     * CN:启动虚拟输入法控制服务。
     */
    private void initVIME()
    {
        LogTool.d("initVIME");
        // Start VIME client control service.
        if (vime_status == true)
            startService(new Intent(this, VImeClientControlService.class));
        else
            stopService(new Intent(this, VImeClientControlService.class));
    }

    private void initAirMouse()
    {
        mRemoteTouchView.initAirMouse();
        if (mRemoteUiStatus != MessageDef.REMOTE_AIRMOUSE)
        {
            mRemoteTouchView.disableAirMouse();
        }
    }

    /**
     * CN:切换到滑动界面。
     */
    private void updateTouchView()
    {
        mRemoteUiStatus = MessageDef.REMOTE_TOUCH;
        getIntent().putExtra(MessageDef.INTENT_REMOTE_STATUS, mRemoteUiStatus);
        mShakeMe.enable();
        mRemote_head_menu.setBackgroundResource(R.drawable.remote_head_switch_touch);
        mRemoteTouchView.setVisibility(View.VISIBLE);
        mRemoteTouchView.disableAirMouse();
        mRemoteKeyboardView.setVisibility(View.INVISIBLE);
    }

    private void updateAirMouseView()
    {
        mRemoteUiStatus = MessageDef.REMOTE_AIRMOUSE;
        getIntent().putExtra(MessageDef.INTENT_REMOTE_STATUS, mRemoteUiStatus);
        mShakeMe.enable();
        mRemote_head_menu.setBackgroundResource(R.drawable.remote_head_switch_touch);
        mRemoteTouchView.setVisibility(View.VISIBLE);
        mRemoteTouchView.enableAirMouse();
        mRemoteKeyboardView.setVisibility(View.INVISIBLE);
    }

    /**
     * CN:切换到按键界面。
     */
    private void updateKeyboardView()
    {
        mRemoteUiStatus = MessageDef.REMOTE_KEY;
        getIntent().putExtra(MessageDef.INTENT_REMOTE_STATUS, mRemoteUiStatus);
        mRemote_head_menu.setBackgroundResource(R.drawable.remote_head_switch_keyboard);
        mRemoteKeyboardView.setVisibility(View.VISIBLE);
        mRemoteTouchView.setVisibility(View.INVISIBLE);
        mRemote_light.setVisibility(View.VISIBLE);
        mRemoteTouchView.disableAirMouse();
        mShakeMe.enable();
        new Handler().postDelayed(new Runnable()
        {
            @Override
            public void run()
            {
                mRemote_light.setVisibility(View.INVISIBLE);
            }
        }, 2000);
    }

    /**
     * CN:菜单按键子布局的控件监听者。
     */
    private class PopwinClickEvent implements OnClickListener
    {
        @Override
        public void onClick(View v)
        {
            if (mPopwin != null)
            {
                mPopwin.dismiss();
            }

            switch (v.getId())
            {
                case R.id.remote_parent_touchs:
                    gotoRemoteTouch();
                    break;

                case R.id.remote_parent_keyboards:
                    gotoRemoteKey();
                    break;

                case R.id.remote_parent_games:
                    gotoGamePage();
                    break;

                default:
                    break;
            }
            mPopwin.updateBackground(mRemoteUiStatus);
        }
    }

    /**
     * CN:获取按键界面布局的宽和高。
     */
    private void getKeyboardXY(MotionEvent event)
    {
        keyboard_width = mRemoteKeyboardView.mRemote_keyboard_layout.getWidth();
        keyboard_height = mRemoteKeyboardView.mRemote_keyboard_layout.getHeight();
    }

    /**
     * CN:遥控器首页时，双击销毁。
     */
    private void destroy()
    {
        try
        {
            mMultiScreenControlService.stopPing(Caller.Others, ClientState.NETWORK_LOST);
            stopVIME();
            stopMultiScreenControlService();
            finish();
        }
        finally
        {
            android.os.Process.killProcess(android.os.Process.myPid());
        }
    }

    private void stopMultiScreenControlService()
    {
        Intent intent = new Intent(this, MultiScreenControlService.class);
        stopService(intent);
    }

    /**
     * Handle touch event.<br>
     * @param v
     * @param event
     */
    private void handleTouch(View v, MotionEvent event)
    {
        x = (int) event.getX();
        y = (int) event.getY();

        switch (v.getId())
        {
            case R.id.remote_head_back:
            {
                gotoDeviceDiscovery();
            }
                break;

            case R.id.remote_head_menu:
            {
                if (mPopwin != null)
                {
                    mPopwin.dismiss();
                }
                mPopwin.updateBackground(mRemoteUiStatus);
                mPopwin.showAtLocation(this.findViewById(R.id.remote_head_menu),
                    Gravity.CLIP_VERTICAL, 0, 0);
            }
                break;

            case R.id.remote_keyboard_btn:
            {// FIXME remote keyboard.
                getKeyboardXY(event);

                if (x > keyboard_width / 3 && x < 2 * keyboard_width / 3 && y > keyboard_height / 3
                    && y < 2 * keyboard_height / 3)
                {
                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        mRemoteKeyboardView.mRemote_keyboard_btn
                            .setBackgroundResource(R.drawable.remote_keyboard_ok_foucs);
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP
                        || event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        mRemoteKeyboardView.mRemote_keyboard_btn.setBackgroundResource(000000);
                        doKeyboard(REMOTE_OK);
                    }
                }
                else if (y > 0 && y < keyboard_height / 3
                    && (x >= y * keyboard_width / keyboard_height)
                    && (x + y * keyboard_width / keyboard_height) <= keyboard_width)
                {// REMOTE_UP
                 // CN:方向键需要支持长按。
                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        toVibrate();
                        mRemoteKeyboardView.mRemote_keyboard_btn
                            .setBackgroundResource(R.drawable.remote_keyboard_edge_up);
                        mLoopCount = 0;
                        mPressTime = SystemClock.elapsedRealtime();
                        if (mPressTime != 0)
                        {
                            sendLongPress(KeyInfo.KEYCODE_DPAD_UP, KeyInfo.KEY_EVENT_DOWN);
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_MOVE)
                    {
                        if (mPressTime != 0)
                        {
                            if (mLoopCount < MAX_LOOP_COUNT)
                            {
                                mLoopCount++;
                            }
                            else
                            {
                                sendLongPress(KeyInfo.KEYCODE_DPAD_UP, KeyInfo.KEY_EVENT_DOWN);
                                mLoopCount = 0;
                            }
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP
                        || event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        mRemoteKeyboardView.mRemote_keyboard_btn.setBackgroundResource(000000);
                        // doKeyboard(REMOTE_UP);
                        sendLongPress(KeyInfo.KEYCODE_DPAD_UP, KeyInfo.KEY_EVENT_UP);
                    }
                }
                else if (x > 0 && x < keyboard_width / 3
                    && (x < y * keyboard_width / keyboard_height)
                    && (x + y * keyboard_width / keyboard_height) <= keyboard_width)
                {// REMOTE_LEFT
                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        toVibrate();
                        mRemoteKeyboardView.mRemote_keyboard_btn
                            .setBackgroundResource(R.drawable.remote_keyboard_edge_left);
                        mLoopCount = 0;
                        mPressTime = SystemClock.elapsedRealtime();
                        if (mPressTime != 0)
                        {
                            sendLongPress(KeyInfo.KEYCODE_DPAD_LEFT, KeyInfo.KEY_EVENT_DOWN);
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_MOVE)
                    {
                        if (mPressTime != 0)
                        {
                            if (mLoopCount < MAX_LOOP_COUNT)
                            {
                                mLoopCount++;
                            }
                            else
                            {
                                sendLongPress(KeyInfo.KEYCODE_DPAD_LEFT, KeyInfo.KEY_EVENT_DOWN);
                                mLoopCount = 0;
                            }
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP
                        || event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        mRemoteKeyboardView.mRemote_keyboard_btn.setBackgroundResource(000000);
                        // doKeyboard(REMOTE_LEFT);
                        sendLongPress(KeyInfo.KEYCODE_DPAD_LEFT, KeyInfo.KEY_EVENT_UP);
                    }
                }
                else if (x > 2 * keyboard_width / 3 && x < keyboard_width
                    && (x >= y * keyboard_width / keyboard_height)
                    && (x + y * keyboard_width / keyboard_height) > keyboard_width)
                {// REMOTE_RIGHT
                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        toVibrate();
                        mRemoteKeyboardView.mRemote_keyboard_btn
                            .setBackgroundResource(R.drawable.remote_keyboard_edge_right);
                        mLoopCount = 0;
                        mPressTime = SystemClock.elapsedRealtime();
                        if (mPressTime != 0)
                        {
                            sendLongPress(KeyInfo.KEYCODE_DPAD_RIGHT, KeyInfo.KEY_EVENT_DOWN);
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_MOVE)
                    {
                        if (mPressTime != 0)
                        {
                            if (mLoopCount < MAX_LOOP_COUNT)
                            {
                                mLoopCount++;
                            }
                            else
                            {
                                sendLongPress(KeyInfo.KEYCODE_DPAD_RIGHT, KeyInfo.KEY_EVENT_DOWN);
                                mLoopCount = 0;
                            }
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP
                        || event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        mRemoteKeyboardView.mRemote_keyboard_btn.setBackgroundResource(000000);
                        // doKeyboard(REMOTE_RIGHT);
                        sendLongPress(KeyInfo.KEYCODE_DPAD_RIGHT, KeyInfo.KEY_EVENT_UP);
                    }
                }
                else if (y > 2 * keyboard_height / 3 && y < keyboard_height
                    && (x < y * keyboard_width / keyboard_height)
                    && (x + y * keyboard_width / keyboard_height) > keyboard_width)
                {// REMOTE_DOWN
                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        toVibrate();
                        mRemoteKeyboardView.mRemote_keyboard_btn
                            .setBackgroundResource(R.drawable.remote_keyboard_edge_down);
                        mLoopCount = 0;
                        mPressTime = SystemClock.elapsedRealtime();
                        if (mPressTime != 0)
                        {
                            sendLongPress(KeyInfo.KEYCODE_DPAD_DOWN, KeyInfo.KEY_EVENT_DOWN);
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_MOVE)
                    {
                        if (mPressTime != 0)
                        {
                            if (mLoopCount < MAX_LOOP_COUNT)
                            {
                                mLoopCount++;
                            }
                            else
                            {
                                sendLongPress(KeyInfo.KEYCODE_DPAD_DOWN, KeyInfo.KEY_EVENT_DOWN);
                                mLoopCount = 0;
                            }
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP
                        || event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        mRemoteKeyboardView.mRemote_keyboard_btn.setBackgroundResource(000000);
                        // doKeyboard(REMOTE_DOWN);
                        sendLongPress(KeyInfo.KEYCODE_DPAD_DOWN, KeyInfo.KEY_EVENT_UP);
                    }
                }
                else
                {
                    // Out of range.
                    mRemoteKeyboardView.mRemote_keyboard_btn.setBackgroundResource(000000);
                    sendLongPress(KeyInfo.KEYCODE_DPAD_UP, KeyInfo.KEY_EVENT_UP);
                    sendLongPress(KeyInfo.KEYCODE_DPAD_LEFT, KeyInfo.KEY_EVENT_UP);
                    sendLongPress(KeyInfo.KEYCODE_DPAD_RIGHT, KeyInfo.KEY_EVENT_UP);
                    sendLongPress(KeyInfo.KEYCODE_DPAD_DOWN, KeyInfo.KEY_EVENT_UP);
                }

            }
                break;
            case R.id.remote_child_homes:
            {
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mRemote_child_home.setBackgroundResource(R.drawable.remote_child_home_foucs);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mRemote_child_home.setBackgroundResource(R.drawable.remote_child_home);
                    doKeyboard(REMOTE_PARENT_HOME);
                }
            }
                break;

            case R.id.remote_child_menus:
            {
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mRemote_child_menu.setBackgroundResource(R.drawable.remote_child_menu_foucs);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mRemote_child_menu.setBackgroundResource(R.drawable.remote_child_menu);
                    doKeyboard(REMOTE_PARENT_MENU);
                }
            }
                break;

            case R.id.remote_child_mutes:
            {
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mRemote_child_mute.setBackgroundResource(R.drawable.remote_child_mute_foucs);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mRemote_child_mute.setBackgroundResource(R.drawable.remote_child_mute);
                    doKeyboard(REMOTE_PARENT_MUTE);
                }
            }
                break;

            case R.id.remote_child_volume_maxs:
            {
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mRemote_child_volume_max
                        .setBackgroundResource(R.drawable.remote_child_volume_max_foucs);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mRemote_child_volume_max
                        .setBackgroundResource(R.drawable.remote_child_volume_max);
                    doKeyboard(REMOTE_PARENT_VOLUME_UP);
                }
            }
                break;
            case R.id.remote_child_volume_mins:
            {
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mRemote_child_volume_min
                        .setBackgroundResource(R.drawable.remote_child_volume_min_foucs);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mRemote_child_volume_min
                        .setBackgroundResource(R.drawable.remote_child_volume_min);
                    doKeyboard(REMOTE_PARENT_VOLUME_DOWN);
                }
            }
                break;
            case R.id.remote_bottom_back:
            {
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mRemote_bottom_back.setBackgroundResource(R.drawable.remote_back_foucs);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mRemote_bottom_back.setBackgroundResource(R.drawable.remote_back);
                    doKeyboard(REMOTE_BACK);
                }
            }
                break;

             case R.id.remote_bottom_number:
             {
             //CN:数字键
             if (event.getAction() == MotionEvent.ACTION_DOWN)
             {
             mRemote_bottom_number.setBackgroundResource(R.drawable.remote_mode_foucs);
            
             }
             else if (event.getAction() == MotionEvent.ACTION_UP
             || event.getAction() == MotionEvent.ACTION_CANCEL)
             {
             mRemote_bottom_number.setBackgroundResource(R.drawable.remote_mode);
            
             if (mNumberPop != null)
             {
             mNumberPop.dismiss();
             }
             mNumberPop = new RemoteNumber(RemoteActivity.this);
             mNumberPop.showAtLocation(mRemote_bottom_number, Gravity.CENTER,
             0, 0);
            
             }
             }
             break;
            case R.id.remote_bottom_voice:
            {
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mRemote_bottom_voice.setBackgroundResource(R.drawable.remote_voice_foucs);
                    if (MultiScreenControlService.getInstance().isRunning())
                    {
                        mSpeechRecognitioner.run(this);
                    }
                    else
                    {
                        if ((mContext != null) && (mContext.getResources() != null))
                        {
                            Toast.makeText(mContext,
                                mContext.getResources().getString(R.string.DeviceConnect_box),
                                Toast.LENGTH_SHORT).show();
                        }
                    }
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mRemote_bottom_voice.setBackgroundResource(R.drawable.remote_voice);
                }
            }
                break;

            default:
            {
                // The view we don't handle touch on it.
            }
                break;
        }
    }

    private void clearGotoActivity()
    {
        if (mRemoteActivityHandler.hasMessages(MessageDef.MSG_GOTO_REMOTE_TOUCH))
        {
            mRemoteActivityHandler.removeMessages(MessageDef.MSG_GOTO_REMOTE_TOUCH);
        }

        if (mRemoteActivityHandler.hasMessages(MessageDef.MSG_GOTO_AIRMOUSE))
        {
            mRemoteActivityHandler.removeMessages(MessageDef.MSG_GOTO_AIRMOUSE);
        }

        if (mRemoteActivityHandler.hasMessages(MessageDef.MSG_GOTO_REMOTE_KEY))
        {
            mRemoteActivityHandler.removeMessages(MessageDef.MSG_GOTO_REMOTE_KEY);
        }
    }

    @Override
    protected void gotoRemoteTouch()
    {
        super.gotoRemoteTouch();
        clearGotoActivity();
        Message msg = mRemoteActivityHandler.obtainMessage(MessageDef.MSG_GOTO_REMOTE_TOUCH);
        mRemoteActivityHandler.sendMessageDelayed(msg, MessageDef.DELAY_MILLIS);
    }

    @Override
    protected void gotoAirMouse()
    {
        super.gotoAirMouse();
        clearGotoActivity();
        Message msg = mRemoteActivityHandler.obtainMessage(MessageDef.MSG_GOTO_AIRMOUSE);
        mRemoteActivityHandler.sendMessageDelayed(msg, MessageDef.DELAY_MILLIS);
    }

    @Override
    protected void gotoRemoteKey()
    {
        super.gotoRemoteKey();
        clearGotoActivity();
        Message msg = mRemoteActivityHandler.obtainMessage(MessageDef.MSG_GOTO_REMOTE_KEY);
        mRemoteActivityHandler.sendMessageDelayed(msg, MessageDef.DELAY_MILLIS);
    }

    @Override
    protected void gotoGamePage()
    {
        super.gotoGamePage();
        clearGotoActivity();
        Intent intent = new Intent(this, RemoteGameActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, mRemoteUiStatus);
        startActivity(intent);
        finish();
    }

    @Override
    protected void gotoMirror()
    {
        super.gotoMirror();
        clearGotoActivity();
        Intent intent = new Intent(this, MultiScreenActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, mRemoteUiStatus);
        intent.putExtra(MessageDef.INTENT_MIRROR_STATUS, MessageDef.MIRROR_STATUS_DEFAULT);
        startActivity(intent);
        // Do finish when goto another activity.
        finish();
    }

    @Override
    protected void gotoMirrorSensor()
    {
        super.gotoMirrorSensor();
        clearGotoActivity();
        Intent intent = new Intent(this, MultiScreenActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, mRemoteUiStatus);
        intent.putExtra(MessageDef.INTENT_MIRROR_STATUS, MessageDef.MIRROR_STATUS_SENSOR);
        startActivity(intent);
        finish();
    }

    @Override
    protected void gotoDeviceDiscovery()
    {
        clearGotoActivity();
        Intent intent = new Intent(this, DeviceDiscoveryActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(intent);
        finish();
    }
}
