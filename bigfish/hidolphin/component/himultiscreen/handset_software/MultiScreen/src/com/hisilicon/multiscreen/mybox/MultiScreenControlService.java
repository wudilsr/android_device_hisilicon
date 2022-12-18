package com.hisilicon.multiscreen.mybox;

import org.cybergarage.net.AndoridNetInfoInterface;
import org.cybergarage.upnp.Device;
import org.cybergarage.upnp.ssdp.SSDP;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.DhcpInfo;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiManager.MulticastLock;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.text.format.Formatter;

import com.hisilicon.dlna.dmc.gui.activity.AppPreference;
import com.hisilicon.multiscreen.controller.AccessUpnpController;
import com.hisilicon.multiscreen.controller.DeviceDiscover;
import com.hisilicon.multiscreen.controller.IAccessListener;
import com.hisilicon.multiscreen.controller.IAccessListener.Caller;
import com.hisilicon.multiscreen.controller.MirrorUpnpController;
import com.hisilicon.multiscreen.controller.RemoteAPPUpnpController;
import com.hisilicon.multiscreen.controller.VIMEUpnpController;
import com.hisilicon.multiscreen.controller.VinputUpnpController;
import com.hisilicon.multiscreen.gsensor.AirMouse;
import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.remote.RemoteControlCenter;
import com.hisilicon.multiscreen.protocol.utils.HostNetInterface;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.upnputils.IUpnpControlPointListener;
import com.hisilicon.multiscreen.upnputils.MultiScreenUpnpControlPoint;
import com.hisilicon.multiscreen.upnputils.UpnpMultiScreenDeviceInfo;
import com.hisilicon.multiscreen.vime.VImeClientControlService;

public class MultiScreenControlService extends Service
{
    public enum ClientState
    {
        INIT, DEINIT, RUNNING, NETWORK_LOST, REAVED, STB_LEAVE, STB_SUSPEND
    };

    public enum TopActivity
    {
        discovery, remote, mirror
    };

    /**
     * UUID of device last connected.<br>
     * CN:最后一次接入的设备UUID。
     */
    public static String save_uuid = null;

    public static final int AUDIO_PLAY = 1;

    public static final int AUDIO_PAUSE = 0;

    public static final int VIDEO_PLAY = 1;

    public static final int VIDEO_PAUSE = 0;

    public static boolean mIsVideoPlay = false;

    private static boolean mIsAudioPlay = false;

    public static final String VIDEO_H264_TYPE = "h264";

    public static final String VIDEO_JPEG_TYPE = "jpeg";

    public static String mSupportVideoType = VIDEO_JPEG_TYPE;

    /**
     * State of control service.
     */
    private ClientState mServiceState = ClientState.DEINIT;

    /**
     * Top activity.
     */
    private TopActivity mActivityState = TopActivity.discovery;

    /**
     * Instance of MultiScreen control service.
     */
    private static MultiScreenControlService mMultiScreenControlService = null;

    /**
     * Control point of MultiScreen upnp.
     */
    private static MultiScreenUpnpControlPoint mControlPoint = null;

    /**
     * Simple device.
     */
    private HiDeviceInfo mHiDevice = null;

    /**
     * Remote control center.
     */
    private RemoteControlCenter mRemoteControlCenter = null;

    /**
     * Air mouse.<br>
     */
    private AirMouse mAirMouse = null;

    /**
     * Access upnp controller.
     */
    private AccessUpnpController mAccessUpnpController = null;

    /**
     * VIME upnp controller.<br>
     */
    private VIMEUpnpController mVIMEUpnpController = null;

    /**
     * Mirror upnp controller.<br>
     */
    private MirrorUpnpController mMirrorUpnpController = null;

    /**
     * Remote app upnp controller.<br>
     */
    private RemoteAPPUpnpController mRemoteAppUpnpController = null;

    /**
     * Vinput upnp controller.<br>
     */
    private VinputUpnpController mVinputUpnpController = null;

    /**
     * DeviceDiscover upnp controller.<br>
     */
    private DeviceDiscover mDeviceDiscover = null;

    /**
     * Listener of access.<br>
     */
    private IAccessListener mAccessListener = null;

    /**
     * Listener of device update.<br>
     */
    private IOriginalDeviceListListener mIOriginalDeviceListListener = null;

    /**
     * Listener of control point.<br>
     */
    private IUpnpControlPointListener mUpnpControlPointListener = null;

    private MulticastLock mMulticastLock = null;

    private BroadcastReceiver mNetworkChangeReceiver = null;

    /**
     * CN:执行订阅Access服务的线程。
     */
    private Thread mSubscribeAccessServiceThread = null;

    /**
     * CN:连接断开的提示线程。
     */
    private Thread mNoConnectNoticeThread = null;

    /**
     * Lastest IP of phone.<br>
     * CN:手机最后一次IP地址。<br>
     * CN:重连使用AccessHello，其参数可能需要IP。
     */
    private static String prevConIP = null;

    /**
     * Is upnp stack open.<br>
     * CN:upnp协议栈开启。
     */
    private static boolean isUpnpStackOpen = false;

    private MyHandler myHandler = null;

    private static final int MSG_START_SEARCH = 100;

    private static final int MSG_STOP_SEARCH = 200;

    private static final int MSG_SHOW_NO_CONNECT = 300;

    private static Context mContext = null;

    private static final long DELAY_MILLIS = 300;

    private static boolean mIsNetworkAvailable = false;

    /**
     * Interface for get android's net info for cyberlink.
     */
    private AndoridNetInfoInterface mNetInfoInterface = new AndoridNetInfoInterface()
    {
        @Override
        public String getBroadCastAddress()
        {
            return getBroadcastIpAddress();
        }
    };

    @Override
    public void onCreate()
    {
        LogTool.d("onCreate");
        super.onCreate();
        initData();
        allowMulticast();
        initHandler();
        initControlPoint();
        registerConnectReceiver();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        LogTool.d("onStartCommand");
        super.onStartCommand(intent, flags, startId);
        return START_NOT_STICKY;
    }

    @Override
    public void onDestroy()
    {
        LogTool.d("onDestroy");
        super.onDestroy();
        deinitControllers();
        unregisterConnectReceiver();
        deInitControlPoint();
        deInitHandler();
        unlockMulticast();
    }

    @Override
    public IBinder onBind(Intent intent)
    {
        LogTool.d("onBind");
        return null;
    }

    public static MultiScreenControlService getInstance()
    {
        if (mMultiScreenControlService == null)
        {
            mMultiScreenControlService = new MultiScreenControlService();
        }
        return mMultiScreenControlService;
    }

    /**
     * Get Upnp control point.
     * @return Upnp control point of MultiScreen.
     */
    public MultiScreenUpnpControlPoint getControlPoint()
    {
        if (mControlPoint == null)
        {
            mControlPoint = MultiScreenUpnpControlPoint.getInstance();
        }
        return mControlPoint;
    }

    /**
     * Initialize HiDevice and controllers.<br>
     * CN:初始化设备信息和控制者。
     */
    public void init()
    {
        if (mHiDevice == null)
        {
            mHiDevice = new HiDeviceInfo(mControlPoint);
            initAllControllers();
        }
        else
        {
            mHiDevice.resetIp(mControlPoint);
            resetAllControllers();
        }

        setState(ClientState.INIT);
    }

    /**
     * Renew local control service state.<br>
     * CN:重置本地控制服务信息。
     * @return true if success.
     */
    public boolean renewState()
    {
        boolean isOK = mHiDevice.resetServices(mControlPoint);
        if (isOK)
        {
            resetAllControllers();
            renewMirror();
            renewVime();
            subscribeAccessService();
        }
        else
        {
            LogTool.w("Fail to renewState.");
        }

        return isOK;
    }

    private void renewMirror()
    {
        boolean isMirrorSet = setDefaultMirrorParameter(2);
        TopActivity topActivity = getInstance().getTopActivity();

        if (topActivity == TopActivity.mirror)
        {
            if (isMirrorSet == false)
            {
                isMirrorSet = setDefaultMirrorParameter(1);
            }

            if (isMirrorSet)
            {
                if (startMirror(2) == false)
                {
                    LogTool.e("Fail to start mirror.");
                }
            }
            else
            {
                LogTool.e("Fail to renew mirror parameter.");
            }
        }
        else
        {
            // do not restart mirror.
        }
    }

    private void renewVime()
    {
        TopActivity topActivity = getInstance().getTopActivity();
        if (topActivity != TopActivity.discovery)
        {
            VImeClientControlService vimeService = VImeClientControlService.getInstance();
            if (vimeService != null)
            {
                vimeService.reset();
            }
        }
    }

    /**
     * Get HiDevice.
     * @return HiDevice
     */
    public HiDeviceInfo getHiDevice()
    {
        return mHiDevice;
    }

    /**
     * True if state is running.<br>
     * CN:如果状态为运行状态返回真。
     * @return state of running.
     */
    public boolean isRunning()
    {
        if (getState() == ClientState.RUNNING)
        {
            return true;
        }
        return false;
    }

    public boolean isReaved()
    {
        if (getState() == ClientState.REAVED)
        {
            return true;
        }
        return false;
    }

    public boolean isSuspend()
    {
        if (getState() == ClientState.STB_SUSPEND)
        {
            return true;
        }
        return false;
    }

    /**
     * True if state is ready for auto connect.<br>
     * CN:判断当前状态是否支持自动重连。
     * @return state of ready to auto connect.
     */
    public boolean isReady()
    {
        if (isReaved() || isSuspend())
        {
            return false;
        }
        return true;
    }

    /**
     * Get state of service.
     * @return State of service.
     */
    public ClientState getState()
    {
        return mServiceState;
    }

    /**
     * Set state of service.
     * @param state - state of service.
     */
    public void setState(ClientState state)
    {
        LogTool.d("now state:" + state.name());
        mServiceState = state;
    }

    /**
     * Get top activity name.<br>
     * @return
     */
    public TopActivity getTopActivity()
    {
        return mActivityState;
    }

    /**
     * Set top activity name.<br>
     * @param top
     */
    public void setTopActivity(TopActivity top)
    {
        mActivityState = top;
    }

    /**
     * Get remote control center.<br>
     * @return
     */
    public RemoteControlCenter getRemoteControlCenter()
    {
        if (mRemoteControlCenter == null)
        {
            LogTool.d("Get new remote control center.");
            mRemoteControlCenter = new RemoteControlCenter(mHiDevice);
        }

        return mRemoteControlCenter;
    }

    public AirMouse getAirMouse()
    {
        if (mAirMouse == null)
        {
            mAirMouse = new AirMouse(mContext);
        }
        return mAirMouse;
    }

    public AccessUpnpController getAccessController()
    {
        if (mAccessUpnpController == null)
        {
            LogTool.e("AccessUpnpController is null");
        }
        return mAccessUpnpController;
    }

    public VIMEUpnpController getVIMEUpnpController()
    {
        if (mVIMEUpnpController == null)
        {
            LogTool.e("VIMEUpnpController is null");
        }
        return mVIMEUpnpController;
    }

    public DeviceDiscover getDeviceDiscover()
    {
        if (mDeviceDiscover == null)
        {
            mDeviceDiscover = new DeviceDiscover();
        }
        return mDeviceDiscover;
    }

    /**
     * Start ping.<br>
     */
    public void startPing()
    {
        mAccessUpnpController.startAccessPingTask();
        subscribeAccessService();
        setState(ClientState.RUNNING);
    }

    /**
     * Stop ping.<br>
     * @param caller
     * @param state state of client.
     */
    public void stopPing(Caller caller, ClientState state)
    {
        setState(state);
        unsubscribeAccessService();
        if (mAccessUpnpController != null)
        {
            mAccessUpnpController.stopAccessPingTask(caller);
        }
    }

    /**
     * Access byebye.
     * @return result.
     */
    public boolean accessByebye()
    {
        if (mAccessUpnpController != null)
        {
            return mAccessUpnpController.accessByebye();
        }
        return false;
    }

    /**
     * Set listener to AccessController and ControlPoint.<br>
     * Event callback of access state.
     * @param listener - Access listener.
     */
    public void setAllAccessListener(IAccessListener listener)
    {
        setAccessControllerListener(listener);
        setControlPointListener(listener);
    }

    /**
     * Set listener to AccessController.<br>
     * @param listener
     */
    public void setAccessControllerListener(IAccessListener listener)
    {
        if (mAccessUpnpController == null)
        {
            LogTool.d("AccessUpnpController is null, and it will init after device connected.");
        }
        else
        {
            mAccessUpnpController.setListener(listener);
        }
    }

    public void setOriginalDeviceListListener(IOriginalDeviceListListener listener)
    {
        mIOriginalDeviceListListener = listener;
    }

    /**
     * Subscribe access service.<br>
     * CN:订阅接入控制服务。
     * @return result
     */
    public boolean subscribeAccessService()
    {
        boolean isOK = subscribeService();
        if (isOK == false)
        {
            LogTool.d("Fail to subscribe AccessService, and start subscribe thread.");
            startSubscribeThread();
        }
        return isOK;
    }

    /**
     * Unsubscribe access service.<br>
     * CN:解订阅接入控制服务。
     * @return result
     */
    public boolean unsubscribeAccessService()
    {
        boolean retValue = unsubscribeService();
        stopSubscribeThread();
        return retValue;
    }

    public boolean isVideoPlay()
    {
        return mIsVideoPlay;
    }

    public void setVideoPlay(boolean isPlay)
    {
        mIsVideoPlay = isPlay;
    }

    public boolean isAudioPlay()
    {
        return mIsAudioPlay;
    }

    public void setAudioPlay(boolean isPlay)
    {
        mIsAudioPlay = isPlay;
    }

    public String getSupportVideoType()
    {
        return mSupportVideoType;
    }

    public void setSupportVideoType(String type)
    {
        mSupportVideoType = type;
    }

    /**
     * Set parameter of mirror.
     * @param arg
     * @param times
     * @return
     */
    public boolean setMirrorParameter(String arg, int times)
    {
        return mMirrorUpnpController.setMirrorParameter(arg, times);
    }

    public boolean setDefaultMirrorParameter(int times)
    {
        StringBuffer paramBuff = new StringBuffer();
        paramBuff.append("fps=15,resend=0,cip=");
        paramBuff.append(getLastestIP());
        paramBuff.append(",cport=8888");

        // append vide play flag
        paramBuff.append(",video_play=");
        if (isVideoPlay())
        {
            paramBuff.append(VIDEO_PLAY);
        }
        else
        {
            paramBuff.append(VIDEO_PAUSE);
        }
        LogTool.d("param " + paramBuff.toString());

        // append video support type
        paramBuff.append(",source=");
        paramBuff.append(mSupportVideoType);

        return setMirrorParameter(paramBuff.toString(), times);
    }

    /**
     * Start Mirror controller <br>
     * @param times
     * @return true if success
     */
    public boolean startMirror(int times)
    {
        if (mMirrorUpnpController != null)
        {
            return mMirrorUpnpController.startMirror(times);
        }
        return false;
    }

    /**
     * Stop Mirror controller <br>
     * @param times
     * @return true if success
     */
    public boolean stopMirror(int times)
    {
        if (mMirrorUpnpController != null)
        {
            return mMirrorUpnpController.stopMirror(times);
        }
        return false;
    }

    /**
     * Try to sync info with STB.<br>
     * @return result of sync.
     */
    public boolean canSyncInfo()
    {
        boolean result = false;

        if (mHiDevice == null)
        {
            // CN:待机Activity销毁。
            LogTool.e("HiDevice is null.");
        }
        else
        {
            result = mHiDevice.canSyncInfo(mControlPoint);
        }

        return result;
    }

    /**
     * Get lastest IP of phone.<br>
     * @return IP of phone.
     */
    public String getLastestIP()
    {
        LogTool.d("Get local prevConIP:" + prevConIP);
        return prevConIP;
    }

    /**
     * Start VIME Upnp controller <br>
     */
    public boolean startVIMEUpnpControl()
    {
        return mVIMEUpnpController.startVIMEControlServer();
    }

    /**
     * Stop VIME Upnp controller <br>
     */
    public boolean stopVIMEUpnpControl()
    {
        return mVIMEUpnpController.stopVIMEControlServer();
    }

    /**
     * Start Vinput Upnp controller <br>
     */
    public boolean startVInputUpnpControl()
    {
        return mVinputUpnpController.startVinput();
    }

    /**
     * Stop Vinput Upnp controller <br>
     */
    public boolean stopVInputUpnpControl()
    {
        return mVinputUpnpController.stopVinput();
    }

    /**
     * Start Remote app Upnp controller <br>
     */
    public boolean startRemoteAppUpnpControl()
    {
        return mRemoteAppUpnpController.startRemoteApp();
    }

    /**
     * Stop Vinput Upnp controller <br>
     */
    public boolean stopRemoteAppControl()
    {
        return mRemoteAppUpnpController.stopRemoteApp();
    }

    public static boolean isNetworkAvailable()
    {
        return mIsNetworkAvailable;
    }

    public static void readSaveUuid()
    {
        save_uuid = AppPreference.getMultiScreenUDN();
    }

    private void initData()
    {
        mContext = this;
        readSaveUuid();
        initMirrorSetting();
    }

    /**
     * Allow multicast.
     */
    private void allowMulticast()
    {
        WifiManager wifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
        mMulticastLock = wifiManager.createMulticastLock("multicast.upnp");
        mMulticastLock.setReferenceCounted(true);
        mMulticastLock.acquire();

        // LogTool.d("Multicast mMulticastLock.isHeld() = " +
        // mMulticastLock.isHeld());
        // LogTool.d("Multicast mMulticastLock.toString() = " +
        // mMulticastLock.toString());
    }

    /**
     * Release multicast.
     */
    private void unlockMulticast()
    {
        mMulticastLock.release();
    }

    /**
     * Init Upnp control point.<br>
     * CN:初始化Upnp控制点。
     */
    private void initControlPoint()
    {
        SSDP.setNetInterfaceUtil(mNetInfoInterface);
        mControlPoint = MultiScreenUpnpControlPoint.getInstance();
    }

    private void initAllControllers()
    {
        mRemoteControlCenter = new RemoteControlCenter(mHiDevice);
        mAirMouse = new AirMouse(mContext);
        mAccessUpnpController = new AccessUpnpController();
        mMirrorUpnpController = new MirrorUpnpController();
        mVIMEUpnpController = new VIMEUpnpController();
        mRemoteAppUpnpController = new RemoteAPPUpnpController();
        mVinputUpnpController = new VinputUpnpController();
    }

    private void resetAllControllers()
    {
        mRemoteControlCenter.reset(mHiDevice);
        mAirMouse.reset(mContext);
        mAccessUpnpController.reset();
        mMirrorUpnpController.reset();
        mVIMEUpnpController.reset();
        mRemoteAppUpnpController.reset();
        mVinputUpnpController.reset();
    }

    private void deinitControllers()
    {
        mAirMouse.deinit();
    }

    /**
     * CN:初始化传屏开启关闭状态。
     */
    private void initMirrorSetting()
    {
        setVideoPlay(readVideoPreference());
        setAudioPlay(readAudioPreference());
    }

    /**
     * Stop upnp control point <br>
     */
    private void deInitControlPoint()
    {
        if (mControlPoint != null)
        {
            mControlPoint.destroy();
            mControlPoint = null;
        }
        setState(ClientState.DEINIT);
        mUpnpControlPointListener = null;
    }

    /**
     * Set control point listener.<br>
     */
    private void setControlPointListener(IAccessListener listener)
    {
        mAccessListener = listener;

        if (mUpnpControlPointListener == null)
        {
            mUpnpControlPointListener = new IUpnpControlPointListener()
            {
                @Override
                public void reavedNotify()
                {
                    setState(ClientState.REAVED);
                    if (mAccessListener == null)
                    {
                        LogTool.d("Access listener is null.");
                    }
                    else
                    {
                        mAccessListener.dealReaveEvent(Caller.Others);
                        LogTool.d("Reaved Notify callback.");
                    }
                }

                @Override
                public void stbLeaveNotify()
                {
                    setState(ClientState.STB_LEAVE);
                    if (mAccessListener == null)
                    {
                        LogTool.d("Access listener is null.");
                    }
                    else
                    {
                        mAccessListener.dealSTBLeaveEvent(Caller.Others);
                        LogTool.d("STB Leave Notify callback.");
                    }
                }

                @Override
                public void originalListAdd(Device device)
                {
                    if (mIOriginalDeviceListListener != null)
                    {
                        // LogTool.d("Add device.");
                        mIOriginalDeviceListListener.deviceAdd(device);
                    }
                    else
                    {
                        LogTool.d("mIOriginalDeviceListListener is null.");
                    }
                }

                @Override
                public void originalListRemoved(Device device)
                {
                    // CN:为了支持断网重连，不能立刻退出。
                    if (mIOriginalDeviceListListener != null)
                    {
                        // CN:当前页面为设备发现页面，则删除副本设备。
                        mIOriginalDeviceListListener.deviceRemoved(device);
                    }
                    else
                    {
                        LogTool.d("mIOriginalDeviceListListener is null.");
                    }
                }

                @Override
                public void stbSuspendNotify()
                {
                    setState(ClientState.STB_SUSPEND);
                    if (mAccessListener == null)
                    {
                        LogTool.d("Access listener is null.");
                    }
                    else
                    {
                        mAccessListener.dealSTBSuspendEvent(Caller.Others);
                        LogTool.d("Suspend Notify callback.");
                    }
                }
            };
        }

        if (mControlPoint == null)
        {
            initControlPoint();
        }
        mControlPoint.setControlPointListener(mUpnpControlPointListener);
    }

    /**
     * Restart or stop discovery server when network status change.<br>
     * CN:监视网络状态，启动或关闭设备发现服务。
     */
    private void registerConnectReceiver()
    {
        IntentFilter filter = new IntentFilter();
        filter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);

        mNetworkChangeReceiver = new BroadcastReceiver()
        {
            boolean isNoConnection = false;

            public void onReceive(Context context, Intent intent)
            {
                // LogTool.e("receive network connectivity broadcast");
                String action = intent.getAction();

                if (action.equals(ConnectivityManager.CONNECTIVITY_ACTION))
                {
                    isNoConnection =
                        intent.getBooleanExtra(ConnectivityManager.EXTRA_NO_CONNECTIVITY, false);

                    if (isNoConnection)
                    {
                        // There is no network. CN:没有可用网络，清空设备列表。
                        LogTool.e("Network error.");
                        setNetworkAvailable(false);
                        // DialogUtils.showToastLong(R.string.toast_network_error,
                        // mContext);
                        startNoConnectNoticeThread();
                        stopDiscovery();
                    }
                    else
                    {
                        // Restart device discovery if there is a new
                        // connectivity network. CN:网络变更后可用，清空设备列表，则重新发送搜索消息。
                        ConnectivityManager connec =
                            (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
                        NetworkInfo info = connec.getActiveNetworkInfo();

                        if ((info != null) && (info.isAvailable()))
                        {
                            setNetworkAvailable(true);
                            restartDiscovery();
                        }
                        else
                        {
                            setNetworkAvailable(false);
                        }
                    }
                }
            }
        };

        registerReceiver(mNetworkChangeReceiver, filter);
    }

    private void unregisterConnectReceiver()
    {
        if (mNetworkChangeReceiver != null)
        {
            unregisterReceiver(mNetworkChangeReceiver);
            mNetworkChangeReceiver = null;
        }
    }

    private void initHandler()
    {
        myHandler = new MyHandler();
    }

    private void deInitHandler()
    {
        if (myHandler != null)
        {
            clearMessages();
            myHandler = null;
        }
    }

    /**
     * Stop discovery.<br>
     * CN:停止设备发现。
     */
    private void stopDiscovery()
    {
        clearMessages();

        Message msg = myHandler.obtainMessage(MSG_STOP_SEARCH);
        myHandler.sendMessageDelayed(msg, DELAY_MILLIS);
    }

    /**
     * Restart discovery.<br>
     * CN:重启设备发现。
     */
    private void restartDiscovery()
    {
        clearMessages();
        clearNoticeMessage();

        Message msg = myHandler.obtainMessage(MSG_STOP_SEARCH);
        myHandler.sendMessageDelayed(msg, DELAY_MILLIS);

        msg = myHandler.obtainMessage(MSG_START_SEARCH);
        myHandler.sendMessageDelayed(msg, DELAY_MILLIS);
    }

    private void clearMessages()
    {
        if (myHandler.hasMessages(MSG_START_SEARCH))
            myHandler.removeMessages(MSG_START_SEARCH);

        if (myHandler.hasMessages(MSG_STOP_SEARCH))
            myHandler.removeMessages(MSG_STOP_SEARCH);
    }

    private void showNoConnect()
    {
        clearNoticeMessage();

        Message msg = myHandler.obtainMessage(MSG_SHOW_NO_CONNECT);
        myHandler.sendMessageDelayed(msg, DELAY_MILLIS);
    }

    private void clearNoticeMessage()
    {
        if (myHandler.hasMessages(MSG_SHOW_NO_CONNECT))
            myHandler.removeMessages(MSG_SHOW_NO_CONNECT);
    }

    private class MyHandler extends Handler
    {
        @Override
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case MSG_START_SEARCH:
                {
                    startUpnpStack();
                    checkState();
                }
                    break;

                case MSG_STOP_SEARCH:
                {
                    stopUpnpStack();
                }
                    break;

                case MSG_SHOW_NO_CONNECT:
                {
                    showNoConnect();
                }
                    break;
            }
        }

        private void startUpnpStack()
        {
            String curConIP = getWifiIpAddress();
            // FIXME CN:有消息清空机制，不先stop的话，需注意开启状态isUpnpStackOpen。
            if (isUpnpStackOpen == false)
            {
                if (curConIP != null)
                {
                    LogTool.d("Network available: NowIP:" + curConIP + " PreIP:" + prevConIP);
                    getDeviceDiscover().initSearch();
                    isUpnpStackOpen = true;
                }
            }
            prevConIP = curConIP;
        }

        private void stopUpnpStack()
        {
            getDeviceDiscover().finalizeSearch();
            isUpnpStackOpen = false;
        }

        private void showNoConnect()
        {
            DialogUtils.showToastLong(R.string.toast_network_error, mContext);
        }

        private void checkState()
        {
            if (getInstance().isRunning())
            {
                getInstance().renewState();
            }
        }
    }

    private Runnable mNoConnectNoticeRunnable = new Runnable()
    {
        private int mTimes;

        @Override
        public void run()
        {
            // CN:WiFi断开：提示三次，间隔8s，小于保活提示的20s。
            mTimes = 3;
            do
            {
                if (isNetworkAvailable())
                {
                    break;
                }
                mTimes--;
                showNoConnect();
                threadSleep(8000);
            }
            while (mTimes > 0);
        }

        private void threadSleep(long time)
        {
            try
            {
                Thread.sleep(time);
            }
            catch (InterruptedException e)
            {
                // LogTool.w(e.getMessage());
            }
        }
    };

    private void startNoConnectNoticeThread()
    {
        mNoConnectNoticeThread = new Thread(mNoConnectNoticeRunnable);
        mNoConnectNoticeThread.setName("NoConnectNoticeThread");
        mNoConnectNoticeThread.start();
    }

    private void startSubscribeThread()
    {
        if (mSubscribeAccessServiceThread == null)
        {
            mSubscribeAccessServiceThread = new Thread(new SubscribeServiceRunnable());
            mSubscribeAccessServiceThread.setName("SubscribeAccessServiceThread");
            mSubscribeAccessServiceThread.start();
        }
    }

    private void stopSubscribeThread()
    {
        if (mSubscribeAccessServiceThread != null)
        {
            try
            {
                mSubscribeAccessServiceThread.join(500);
            }
            catch (InterruptedException e)
            {
                LogTool.e(e.getMessage());
            }
            mSubscribeAccessServiceThread = null;
        }
    }

    private class SubscribeServiceRunnable implements Runnable
    {
        private boolean isOK = false;

        /**
         * CN:尝试订阅服务的次数。
         */
        private int subscribeTime = 10;

        public SubscribeServiceRunnable()
        {
            isOK = false;
            subscribeTime = 10;
        }

        @Override
        public void run()
        {
            do
            {
                isOK = subscribeService();
                subscribeTime--;
                if (isOK || subscribeTime <= 0)
                {
                    break;
                }
                threadSleep();
            }
            while (isOK == false);

            LogTool.d("End of SubscribeServiceRunnable, result:" + isOK);
        }

        private void threadSleep()
        {
            try
            {
                Thread.sleep(500);
            }
            catch (InterruptedException e)
            {
            }
        }
    };

    private boolean subscribeService()
    {
        boolean retValue = false;
        if (mControlPoint != null)
        {
            retValue =
                mControlPoint
                    .subscribeService(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_ACCESS_TYPE);
        }
        return retValue;
    }

    private boolean unsubscribeService()
    {
        boolean retValue = false;
        if (mControlPoint != null)
        {
            retValue =
                mControlPoint
                    .unsubscribeService(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_ACCESS_TYPE);
        }
        return retValue;
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
            // ip = info.getIpAddress();
        }

        return ipAddress;
    }

    private String getBroadcastIpAddress()
    {
        WifiManager wifiMgr = (WifiManager) getSystemService(Context.WIFI_SERVICE);
        if (wifiMgr == null)
        {
            LogTool.e("wifi manager is null");
            return null;
        }
        DhcpInfo dhcpInfo = wifiMgr.getDhcpInfo();
        if (dhcpInfo == null)
        {
            LogTool.e("dhcpInfo is null");
            return null;
        }
        int broadcast = (dhcpInfo.ipAddress & dhcpInfo.netmask) | ~dhcpInfo.netmask;
        return Formatter.formatIpAddress(broadcast);
    }

    private void setNetworkAvailable(boolean isAvailable)
    {
        mIsNetworkAvailable = isAvailable;
    }

    /**
     * Read video status.<br>
     * CN:读取视频开关状态。
     * @return true if video plays.
     */
    private boolean readVideoPreference()
    {
        return readStatusPreference(MultiSettingActivity.VIDEO_STATUS_KEY, true);
    }

    /**
     * Read audio status.<br>
     * CN:读取音频开关状态。
     * @return true if audio plays.
     */
    private boolean readAudioPreference()
    {
        return readStatusPreference(MultiSettingActivity.AUDIO_STATUS_KEY, true);
    }

    /**
     * Read preference.<br>
     * @param statusKey
     * @param defValue
     * @return
     */
    private boolean readStatusPreference(String statusKey, boolean defValue)
    {
        SharedPreferences prefrence =
            getSharedPreferences(MultiSettingActivity.SETTING_STATUS_FILE_NAME, MODE_PRIVATE);
        return prefrence.getBoolean(statusKey, defValue);
    }
}
