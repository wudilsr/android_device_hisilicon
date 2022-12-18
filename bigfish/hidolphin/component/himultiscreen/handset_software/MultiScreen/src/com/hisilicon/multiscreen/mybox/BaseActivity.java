package com.hisilicon.multiscreen.mybox;

import java.lang.ref.SoftReference;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.ProgressDialog;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.os.Vibrator;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Toast;

import com.hisilicon.multiscreen.controller.IAccessListener;
import com.hisilicon.multiscreen.controller.IAccessListener.Caller;
import com.hisilicon.multiscreen.mybox.MultiScreenControlService.ClientState;
import com.hisilicon.multiscreen.protocol.message.KeyInfo;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.remote.RemoteControlCenter;
import com.hisilicon.multiscreen.protocol.remote.RemoteKeyboard;
import com.hisilicon.multiscreen.protocol.remote.RemoteSpeech;
import com.hisilicon.multiscreen.protocol.remote.RemoteTouch;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;
import com.hisilicon.multiscreen.protocol.utils.ServiceUtil;
import com.hisilicon.multiscreen.scene.ISceneListener;
import com.hisilicon.multiscreen.scene.SceneType;
import com.hisilicon.multiscreen.vime.VImeClientControlService;

/**
 * Base activity of MultiScreen, be used at activity of remote control and
 * remote application as the parent class.<br>
 * CN:多屏基础活动类，作为虚拟遥控器和远程应用活动类的父类。
 * @since MultiScreen V1.0.1.0 2012/01/11: first create.
 */
public abstract class BaseActivity extends Activity implements RemotePool
{
    /**
     * Default remote UI status.<br>
     */
    public int DEFAULT_REMOTE_UI_STATUS = MessageDef.REMOTE_TOUCH; // REMOTE_KEY;

    /**
     * Status of remote activity.<br>
     */
    protected int mRemoteUiStatus = DEFAULT_REMOTE_UI_STATUS;

    /**
     * MultiScreen control service.<br>
     * CN:多屏控制服务。
     */
    public MultiScreenControlService mMultiScreenControlService = null;

    /**
     * Instance of remote control center.<br>
     * CN:遥控中心。
     */
    protected RemoteControlCenter mRemoteControlCenter = null;

    /**
     * Remote keyboard controller <br>
     * CN:远端键盘按键事件。
     * @see RemoteControlCenter
     */
    public static RemoteKeyboard mKeyboard = null;

    /**
     * Remote Touch controller <br>
     * CN:远端触摸屏事件响。
     */
    public static RemoteTouch mRemoteTouch = null;

    /**
     * Remote app list <br>
     * CN:远程应用。
     */
    public static RemoteSpeech mRemoteSpeech = null;

    /**
     * CN:振动。
     */
    public static Vibrator mVibrator;

    protected ProgressDialog mProgressDialog = null;

    /**
     * The number of milliseconds to vibrate.<br>
     */
    protected static final long TIME_VIBRATE = 20;

    /**
     * Max loop count of long press.<br>
     */
    protected static final int MAX_LOOP_COUNT = 100;

    /**
     * Long press start time.<br>
     */
    protected long mPressTime = 0;

    /**
     * Long press start time.<br>
     */
    protected long mPressTime2 = 0;

    /**
     * Long press loop count.<br>
     */
    protected int mLoopCount = 0;

    /**
     * Long press loop count.<br>
     */
    protected int mLoopCount2 = 0;

    /**
     * Status of vibrate.<br>
     */
    private static boolean vib_status;

    /**
     * True if home page use remote.<br>
     */
    protected static boolean isHomePageRemote = false;

    /**
     * Access ping listener.<br>
     * CN:网络状态监听回调。
     */
    protected IAccessListener mAccessListener = null;

    /**
     * Scene recognize listener.<br>
     * CN:场景识别监听。
     */
    protected ISceneListener mSceneListener = null;

    /**
     * Handler of access event.
     */
    public AccessEventHandler mAccessEventHandler = null;

    /**
     * Check network failed handler.<br>
     * CN:网络检测失败处理。
     */
    private static class AccessEventHandler extends Handler
    {
        SoftReference<BaseActivity> mActivityReference = null;

        AccessEventHandler(BaseActivity activity)
        {
            mActivityReference = new SoftReference<BaseActivity>(activity);
        }

        public void handleMessage(Message msg)
        {
            BaseActivity activity = mActivityReference.get();
            super.handleMessage(msg);
            switch (msg.what)
            {
                case MultiScreenActivity.KEEP_ALIVE_PACKET_LOSS:
                {
                    LogTool.e("keep alive packet loss!");
                    Toast.makeText(activity,
                        activity.getResources().getString(R.string.toast_KeepAlive_packet_loss),
                        Toast.LENGTH_SHORT).show();
                    break;
                }

                case MultiScreenActivity.KEEP_ALIVE_FAILED:
                {
                    // CN:网络断开。
                    Caller caller = (Caller) msg.obj;
                    activity.dealNetfailedStatus(caller);
                    break;
                }
                case MultiScreenActivity.ACCESS_REAVED:
                {
                    // CN:抢占。
                    Caller caller = (Caller) msg.obj;
                    activity.dealAccessByeForReave(caller);
                    break;
                }
                case MultiScreenActivity.STB_LEAVE:
                {
                    Caller caller = (Caller) msg.obj;
                    activity.dealSTBLeave(caller);
                    break;
                }
                case MultiScreenActivity.STB_SUSPEND:
                {
                    Caller caller = (Caller) msg.obj;
                    activity.dealSTBSuppend(caller);
                    break;
                }
                default:
                    break;
            }
        }
    }

    /**
     * Constructor function, to implement KeepAliveCallBack interface.<br>
     * CN:构造函数，实现KeepAliveCallBack接口
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        LogTool.v("On Create.");
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        setStrictMode();
        initData();
        initView();
    }

    /**
     * On restart.<br>
     */
    @Override
    protected void onRestart()
    {
        LogTool.v("on restart.");
        super.onRestart();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig)
    {
        LogTool.d("onConfigurationChanged");
        super.onConfigurationChanged(newConfig);
    }

    /**
     * On resume.<br>
     */
    @Override
    protected void onResume()
    {
        LogTool.v("on resume.");
        super.onResume();
        // checkState();
    }

    /**
     * On pause.<br>
     */
    @Override
    protected void onPause()
    {
        LogTool.v("on pause.");
        super.onPause();
        dismissProgressDialog();
        clearSceneListener();
    }

    /**
     * On stop.<br>
     */
    @Override
    protected void onStop()
    {
        LogTool.v("on stop.");
        super.onStop();
    }

    /**
     * On destory.<br>
     */
    @Override
    protected void onDestroy()
    {
        LogTool.v("on destroy.");
        super.onDestroy();
        if (mVibrator != null)
            mVibrator.cancel();
    }

    /**
     * Deal keeping alive failed.<br>
     * CN:网络断开处理。
     */
    protected void dealNetfailedStatus(Caller caller)
    {
        mMultiScreenControlService.stopPing(caller, ClientState.NETWORK_LOST);
        stopVIME();
        destroyRemoteControl();
        removeInvalidDevice();
    }

    /**
     * Deal Access bye for reave.<br>
     * CN:处理抢占事件。
     */
    protected void dealAccessByeForReave(Caller caller)
    {
        deInitNetworkChecker(caller, ClientState.REAVED);
        stopVIME();
        destroyRemoteControl();
        clearCurrentDevice();
    }

    /**
     * Deal STB leave.<br>
     * CN:处理STB关闭事件。
     */
    protected void dealSTBLeave(Caller caller)
    {
        deInitNetworkChecker(caller, ClientState.STB_LEAVE);
        stopVIME();
        destroyRemoteControl();
        removeInvalidDevice();
    }

    /**
     * Deal STB suppend.<br>
     * CN:处理STB待机事件。
     */
    protected void dealSTBSuppend(Caller caller)
    {
        deInitNetworkChecker(caller, ClientState.STB_SUSPEND);
        stopVIME();
        destroyRemoteControl();
        clearCurrentDevice();
    }

    /**
     * Deal Scene changed.<br>
     * CN:处理场景切换。
     * @param sceneType
     */
    protected void dealSceneChanged(SceneType sceneType)
    {
        switch (sceneType)
        {
            case REMOTE_TOUCH:
            {
                gotoRemoteTouch();
            }
                break;
            case REMOTE_AIRMOUSE:
            {
                gotoAirMouse();
            }
                break;
            case MIRROR:
            {
                gotoMirror();
            }
                break;
            case MIRROR_SENSOR:
            {
                gotoMirrorSensor();
            }
                break;
            default:
            {
                gotoRemoteTouch();
            }
                break;
        }
    }

    /**
     * CN:滑动遥控器。<br>
     */
    protected void gotoRemoteTouch()
    {
        LogTool.d("");
        // Handle it in sub class.
    }

    /**
     * CN:空鼠遥控器。<br>
     */
    protected void gotoAirMouse()
    {
        LogTool.d("");
        // Handle it in sub class.
    }

    /**
     * CN:跳转按键遥控器。<br>
     */
    protected void gotoRemoteKey()
    {
        LogTool.d("");
        // Handle it in sub class.
    }

    /**
     * CN:跳转游戏遥控器。<br>
     */
    protected void gotoGamePage()
    {
        LogTool.d("");
        // Handle it in sub class.
    }

    /**
     * CN:镜像。<br>
     */
    protected void gotoMirror()
    {
        LogTool.d("");
        // Handle it in sub class.
    }

    /**
     * CN:镜像，并开启体感。<br>
     */
    protected void gotoMirrorSensor()
    {
        LogTool.d("");
        // Handle it in sub class.
    }

    /**
     * CN:跳转首页设备发现。<br>
     */
    protected void gotoDeviceDiscovery()
    {
        LogTool.d("");
        // Handle it in sub class.
    }

    /**
     * @deprecated Destroy remote control center.<br>
     */
    protected void destroyRemoteControl()
    {
        // FIXME CN:不销毁，让遥控器抢占时可用。
        // mRemoteControlCenter.destroy();
        // BaseActivity.this.finish();
    }

    /**
     * Stop network check.<br>
     * CN:停止网络状态检查。
     * @param caller CN:调用者。
     * @param clientState CN:客户端状态。
     */
    protected void deInitNetworkChecker(Caller caller, ClientState clientState)
    {
        // CN:停止网络状态检查。
        mMultiScreenControlService.stopPing(caller, clientState);
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

    protected void clearCurrentDevice()
    {
        mMultiScreenControlService.getControlPoint().setCurrentDevice(null);
    }

    /**
     * Release view object.<br>
     * CN:释放View对象。
     * 
     * @param view - View object to be released.<br>
     *        CN:需要释放的View对象。
     */
    protected void unbindDrawables(View view)
    {
        if (view != null)
        {
            if (view.getBackground() != null)
            {
                view.getBackground().setCallback(null);
            }
            if (view instanceof ViewGroup)
            {
                for (int i = 0; i < ((ViewGroup) view).getChildCount(); i++)
                {
                    unbindDrawables(((ViewGroup) view).getChildAt(i));
                }
                ((ViewGroup) view).removeAllViews();
            }
        }
        view = null;
    }

    /**
     * Show progress dialog.<br>
     * 
     * @param titleId - title of dialog
     * @param msgId - message of dialog
     */
    protected void showProgressDialog(int titleId, int msgId)
    {
        if (mProgressDialog == null)
        {
            mProgressDialog = new ProgressDialog(this);
        }

        mProgressDialog.setTitle(titleId);
        mProgressDialog.setMessage(getString(msgId));
        mProgressDialog.setCancelable(false);
        mProgressDialog.show();
    }

    /**
     * Dismiss progress dialog.<br>
     */
    protected void dismissProgressDialog()
    {
        if (mProgressDialog != null)
        {
            mProgressDialog.dismiss();
            mProgressDialog = null;
        }
    }

    /**
     * Register receiver of broadcast.<br>
     * CN: 注册Base的广播接收者。
     * 
     * @param receiver - broadcast receiver.
     */
    protected void registerBroadcastReceiver(BroadcastReceiver receiver, IntentFilter filter)
    {
        registerReceiver(receiver, filter);
    }

    /**
     * Unregister receiver of broadcast.<br>
     * CN:反注册Base的广播接收者。
     * 
     * @param receiver - broadcast receiver.
     */
    protected void unregisterBroadcastReceiver(BroadcastReceiver receiver)
    {
        try
        {
            unregisterReceiver(receiver);
        }
        catch (IllegalArgumentException e)
        {
            LogTool.d("the receiver was already unregistered or was not registered.");
        }
    }

    /**
     * Reset callback of keep alive for remote control.<br>
     * CN:重置保活的回调。
     */
    protected void resetAccessListener()
    {
        if (mAccessListener == null)
        {
            mAccessListener = new IAccessListener()
            {
                @Override
                public void dealNetWorkNotWellEvent()
                {
                    // keep alive packet loss.
                    mAccessEventHandler
                        .sendEmptyMessage(MultiScreenActivity.KEEP_ALIVE_PACKET_LOSS);
                }

                @Override
                public void dealNetWorkLostEvent(Caller caller)
                {
                    // Keep alive fail.
                    LogTool.d("Keep alive fail.");
                    sendAccessStatusMessage(caller, MultiScreenActivity.KEEP_ALIVE_FAILED);
                }

                @Override
                public void dealReaveEvent(Caller caller)
                {
                    // Be reaved.
                    LogTool.d("Be reaved.");
                    sendAccessStatusMessage(caller, MultiScreenActivity.ACCESS_REAVED);
                }

                @Override
                public void dealSTBLeaveEvent(Caller caller)
                {
                    // STB leave.
                    LogTool.d("STB leave.");
                    sendAccessStatusMessage(caller, MultiScreenActivity.STB_LEAVE);
                }

                @Override
                public void dealSTBSuspendEvent(Caller caller)
                {
                    // STB suspend
                    LogTool.d("STB suspend.");
                    sendAccessStatusMessage(caller, MultiScreenActivity.STB_SUSPEND);
                }
            };
        }
        mMultiScreenControlService.setAllAccessListener(mAccessListener);
    }

    /**
     * CN:重置场景识别观察者。
     */
    protected void resetSceneListener()
    {
        if (mSceneListener == null)
        {
            mSceneListener = new ISceneListener()
            {
                @Override
                public void sceneChanged(SceneType sceneType)
                {
                    dealSceneChanged(sceneType);
                }
            };
        }
        mMultiScreenControlService.setSceneListener(mSceneListener);
    }

    private void clearSceneListener()
    {
        mMultiScreenControlService.setSceneListener(null);
    }

    private void sendAccessStatusMessage(Caller caller, int what)
    {
        Message msg = mAccessEventHandler.obtainMessage();
        msg.obj = caller;
        msg.what = what;
        msg.sendToTarget();
    }

    /**
     * To vibrate.<br>
     * CN:振动手机。
     */
    protected static void toVibrate()
    {
        if (isVibrate())
        {
            mVibrator.vibrate(TIME_VIBRATE);
            // mVibrator.vibrate(new long[]
            // { 100, 2, 100, 200 }, -1);
        }
    }

    /**
     * Is status of vibrate. CN:客户端按键振动开关状态。
     * @return
     */
    protected static boolean isVibrate()
    {
        return vib_status;
    }

    /**
     * Init view.
     */
    private void initView()
    {
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        vib_status = readStatusPreference(MultiSettingActivity.VIBRATOR_STATUS_KEY);
        mVibrator = (Vibrator) getApplication().getSystemService(Service.VIBRATOR_SERVICE);

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

    /**
     * Set strict mode.
     */
    @SuppressLint("NewApi")
    private void setStrictMode()
    {
        StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder().detectDiskReads()
            .detectDiskWrites().detectNetwork().penaltyLog().build());
        StrictMode.setVmPolicy(new StrictMode.VmPolicy.Builder().detectLeakedSqlLiteObjects()
            .penaltyLog().penaltyDeath().build());
    }

    /**
     * @deprecated do checkState in subclass.<br>
     * @see RemoteActivity.java checkCurrentDevice().<br>
     *      Check state of client on resume.
     */
    private void checkState()
    {
        switch (mMultiScreenControlService.getState())
        {
            case RUNNING:
            {
                LogTool.d("check state RUNNING.");
                resetAccessListener();
                break;
            }
            case REAVED:
            {
                LogTool.d("check state REAVED.");
                sendAccessStatusMessage(Caller.AccessPing, MultiScreenActivity.ACCESS_REAVED);
                break;
            }
            case STB_LEAVE:
            {
                LogTool.d("check state STB_LEAVE.");
                sendAccessStatusMessage(Caller.AccessPing, MultiScreenActivity.STB_LEAVE);
                break;
            }
            case NETWORK_LOST:
            {
                LogTool.d("check state NETWORK_LOST.");
                sendAccessStatusMessage(Caller.KeepAlive, MultiScreenActivity.KEEP_ALIVE_FAILED);
                break;
            }
            case STB_SUSPEND:
            {
                LogTool.d("check state STB_SUSPEND.");
                sendAccessStatusMessage(Caller.AccessPing, MultiScreenActivity.STB_SUSPEND);
                break;
            }
            default:
            {
                LogTool.e("check state error: " + mMultiScreenControlService.getState().toString());
                sendAccessStatusMessage(Caller.Others, MultiScreenActivity.KEEP_ALIVE_FAILED);
                break;
            }
        }
    }

    /**
     * Initialize service and controller.
     */
    protected void initData()
    {
        ServiceUtil.checkMultiScreenControlService(this);
        mMultiScreenControlService = MultiScreenControlService.getInstance();
        // Get instance of remote control center.
        mRemoteControlCenter = mMultiScreenControlService.getRemoteControlCenter();
        mAccessEventHandler = new AccessEventHandler(this);
        // isHomePageRemote =
        // readStatusPreference(MultiSettingActivity.HOMEPAGE_REMOTE_KEY);
    }

    /**
     * Stop VIME control service.<br>
     * CN:销毁虚拟输入法控制服务。
     */
    protected void stopVIME()
    {
        LogTool.d("stop vime.");
        sendBroadcast(new Intent(MultiScreenIntentAction.END_INPUT_BY_STB));
        stopService(new Intent(this, VImeClientControlService.class));
    }

    /**
     * CN:客户端键盘键值，触发远端键盘按键事件响应。
     */
    public static void doKeyboard(int result)
    {
        toVibrate();

        if (mKeyboard != null)
        {
            switch (result)
            {
                case REMOTE_BACK:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_BACK);
                    break;
                case REMOTE_PARENT_HOME:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_HOME);
                    break;

                case REMOTE_PARENT_MENU:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_MENU);
                    break;

                case REMOTE_PARENT_MUTE:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_MUTE);
                    break;

                case REMOTE_PARENT_VOLUME_UP:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_VOLUME_UP);
                    break;

                case REMOTE_PARENT_VOLUME_DOWN:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_VOLUME_DOWN);
                    break;

                case REMOTE_OK:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_ENTER);
                    break;

                case REMOTE_UP:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_DPAD_UP);
                    break;

                case REMOTE_LEFT:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_DPAD_LEFT);
                    break;

                case REMOTE_RIGHT:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_DPAD_RIGHT);
                    break;

                case REMOTE_DOWN:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_DPAD_DOWN);
                    break;

                case REMOTE_NUMEBR_F1:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_GREEN);
                    break;

                case REMOTE_NUMEBR_F2:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_RED);
                    break;

                case REMOTE_NUMEBR_F3:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_YELLOW);
                    break;

                case REMOTE_NUMEBR_F4:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_BLUE);
                    break;

                case REMOTE_NUMEBR_ONE:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_1);
                    break;

                case REMOTE_NUMEBR_TWO:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_2);
                    break;

                case REMOTE_NUMEBR_THREE:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_3);
                    break;

                case REMOTE_NUMEBR_FOUR:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_4);
                    break;

                case REMOTE_NUMEBR_FIVE:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_5);
                    break;

                case REMOTE_NUMEBR_SIX:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_6);
                    break;

                case REMOTE_NUMEBR_SEVEN:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_7);
                    break;

                case REMOTE_NUMEBR_EIGHT:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_8);
                    break;

                case REMOTE_NUMEBR_NINE:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_9);
                    break;

                case REMOTE_NUMEBR_EMPTY:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_SPACE);
                    break;

                case REMOTE_NUMEBR_ZERO:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_0);
                    break;

                case REMOTE_NUMEBR_DEL:
                    mKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_DEL);
                    break;

                default:
                    break;
            }
        }
    }

    /**
     * Send long press key.
     * @param key_value
     * @param event_type
     */
    public void sendLongPress(int key_value, short event_type)
    {
        if (mKeyboard != null)
        {
            mKeyboard.sendDownOrUpKeyCode(key_value, event_type);
        }
    }
}
