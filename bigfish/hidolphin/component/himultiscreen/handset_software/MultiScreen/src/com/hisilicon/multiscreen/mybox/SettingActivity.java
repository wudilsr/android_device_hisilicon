package com.hisilicon.multiscreen.mybox;

import java.lang.ref.SoftReference;
import java.util.Timer;
import java.util.TimerTask;

import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.preference.CheckBoxPreference;
import android.preference.Preference;
import android.preference.Preference.OnPreferenceChangeListener;
import android.preference.PreferenceActivity;
import android.widget.Toast;

import com.hisilicon.multiscreen.controller.IAccessListener;
import com.hisilicon.multiscreen.gsensor.SensorService;
import com.hisilicon.multiscreen.protocol.remote.RemoteControlCenter;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;
import com.hisilicon.multiscreen.vime.VImeClientControlService;

/**
 * MultiScreen service switch activity, include switch for VIME and G-sensor.<br>
 * CN: 客户端多屏服务开关活动类，目前包括虚拟输入法开关、重力感应开关。
 * @deprecated
 * @see MultiSettingActivity.java
 */
public class SettingActivity extends PreferenceActivity
{

    public enum SwitchItem
    {
        VIME_SWITCH, GSENSOR_SWITCH, VIDEO_SWITCH, AUDIO_SWITCH
    };

    /**
     * Multiscreen control service.
     */
    private MultiScreenControlService mMultiScreenControlService = null;

    /**
     * VIme client control Service instance.<br>
     * CN:虚拟输入法客户端控制服务实例。
     */
    // private VImeClientControlService mVImeClientControlService = null;

    /**
     * Remote control center.<br>
     * CN:远程控制中心。<br>
     * To be used for network keep alive.<br>
     * CN:用于网络状态检查。
     */
    private RemoteControlCenter mRemoteControlCenter = null;

    /**
     * Check box preference of VIme.
     */
    private CheckBoxPreference mCheckBoxPreferenceVIme = null;

    /**
     * Check box preference of G-sensor.
     */
    private CheckBoxPreference mCheckBoxPreferenceGsensor = null;

    /**
     * Check box preference of Video.
     */
    private CheckBoxPreference mCheckBoxPreferenceVideo = null;

    /**
     * Check box preference of Audio.
     */
    private CheckBoxPreference mCheckBoxPreferenceAudio = null;

    /**
     * VIME status name in preference.
     */
    public static final String VIME_STATUS_FILE_NAME = "VIme_Status";

    /**
     * Preference key records VIME switch status.
     */
    public static final String VIME_STATUS_KEY = "status";

    /**
     * Preference key records first time to start VIME.
     */
    public static final String VIME_FIRST_USED_KEY = "VIME_first_time";

    /**
     * File name of g-sensor.
     */
    public static final String GSENSOR_STATUS_FILE_NAME = "Gsensor_Status";

    /**
     * Preference key records first time to start Gsensor.
     */
    public static final String GSENSOR_FIRST_USED_KEY = "Gsensor_first_time";

    /**
     * Key of g-sensor status.
     */
    public static final String GSENSOR_STATUS_KEY = "status";

    /**
     * File name of video.
     */
    public static final String VIDEO_STATUS_FILE_NAME = "Video_Status";

    /**
     * Preference key records first time to start Video.
     */
    public static final String VIDEO_FIRST_USED_KEY = "Video_first_time";

    /**
     * Key of video status.
     */
    public static final String VIDEO_STATUS_KEY = "status";

    /**
     * File name of audio.
     */
    public static final String AUDIO_STATUS_FILE_NAME = "Audio_Status";

    /**
     * Preference key records first time to start audio.
     */
    public static final String AUDIO_FIRST_USED_KEY = "Audio_first_time";

    /**
     * Key of audio status.
     */
    public static final String AUDIO_STATUS_KEY = "status";

    /**
     * Dialog of progress.
     */
    private ProgressDialog mProgressDialog = null;

    /**
     * Show dialog time.
     */
    private long mShowDialogTime = 0L;

    /**
     * Dismiss dialog time.
     */
    private long mDismissDialogTime = 0L;

    /**
     * Handle message for showing dialog.<br>
     * CN:显示等待对话框。
     */
    private final static int SHOW_VIME_DIALOG = 50;

    /**
     * Handle message for dismissing dialog and update switch according to the
     * result.<br>
     * CN:隐藏等待对话框并根据结果更新开关。
     */
    private final static int DISMISS_DIALOG_AND_UPDATE_VIME_SWITCH = 60;

    /**
     * Handle message for showing dialog.<br>
     * CN:显示等待对话框。
     */
    private final static int SHOW_VIDEO_DIALOG = 51;

    /**
     * Handle message for dismissing dialog and update switch according to the
     * result.<br>
     * CN:隐藏等待对话框并根据结果更新开关。
     */
    private final static int DISMISS_DIALOG_AND_UPDATE_VIDEO_SWITCH = 61;

    /**
     * Preference key of VIme.<br>
     * CN:虚拟输入法开关设定键值。
     */
    private static final CharSequence PREFERENCES_KEY_VIME = "vimeclient";

    /**
     * Preference key of G-sensor.<br>
     * CN:体感开关设置键值。
     */
    private static final CharSequence PREFERENCES_KEY_GSENSOR = "Gsensorclient";

    /**
     * Preference key of video.<br>
     * CN:虚拟输入法开关设定键值。
     */
    private static final CharSequence PREFERENCES_KEY_VIDEO = "Videoclient";

    /**
     * Preference key of audio.<br>
     * CN:体感开关设置键值。
     */
    private static final CharSequence PREFERENCES_KEY_AUDIO = "Audioclient";

    /**
     * Timeout of showing dialog.<br>
     * CN:对话框显示超时。
     */
    private static final long SHOW_DIALOG_TIMEOUT = 2000;

    /**
     * Handler of VIme dialog.
     */
    private SettingActivityHandler mHandler = null;

    /**
     * Access ping listener.<br>
     * CN:网络状态监听回调。
     */
    private IAccessListener mAccessListener = null;

    /**
     * Broadcast receiver for setting activity.<br>
     * CN:设置页面广播接收者。
     */
    private BroadcastReceiver mBroadcastReceiver = new BroadcastReceiver()
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            String action = intent.getAction();
            if (action.equals(MultiScreenIntentAction.SWITCH_VIME_SETTING))
            {
                LogTool.d("receive the vime switch read");
                mDismissDialogTime = System.currentTimeMillis();
                if ((mDismissDialogTime - mShowDialogTime) > SHOW_DIALOG_TIMEOUT)
                {
                    mHandler.sendEmptyMessage(DISMISS_DIALOG_AND_UPDATE_VIME_SWITCH);
                }
            }
        }
    };

    /**
     * Preference change listener.<br>
     * CN:设置改变监听者。
     */
    private OnPreferenceChangeListener mOnPreferenceChangeListener =
        new OnPreferenceChangeListener()
        {
            @Override
            public boolean onPreferenceChange(Preference preference, Object newValue)
            {
                /*
                 * if (preference.getKey().equals(PREFERENCES_KEY_VIME)) { //
                 * VIme preference. if (newValue.equals(true)) {
                 * mHandler.sendEmptyMessage(SHOW_VIME_DIALOG);
                 * 
                 * startVimeService();
                 * 
                 * Timer showTimer = new Timer(); showTimer.schedule(new
                 * TimerTask() {
                 * 
                 * @Override public void run() {
                 * mHandler.sendEmptyMessage(DISMISS_DIALOG_AND_UPDATE_VIME_SWITCH
                 * ); } }, SHOW_DIALOG_TIMEOUT); } else { stopVimeService(); } }
                 * else
                 */if (preference.getKey().equals(PREFERENCES_KEY_GSENSOR))
                {
                    // G-sensor preference.
                    if (newValue.equals(true))
                    {
                        startGsensor();
                        LogTool.d("Gsensor start.");
                    }
                    else
                    {
                        stopGsensor();
                        LogTool.d("Gsensor stop.");
                    }
                }
                else if (preference.getKey().equals(PREFERENCES_KEY_VIDEO))
                {
                    mHandler.sendEmptyMessage(SHOW_VIDEO_DIALOG);

                    if (newValue.equals(true))
                    {
                        boolean result = resumeVideo();
                        mMultiScreenControlService.setVideoPlay(result);
                    }
                    else
                    {
                        boolean result = pauseVideo();
                        mMultiScreenControlService.setVideoPlay(!result);
                    }

                    Timer showTimer = new Timer();
                    showTimer.schedule(new TimerTask()
                    {
                        @Override
                        public void run()
                        {
                            mHandler.sendEmptyMessage(DISMISS_DIALOG_AND_UPDATE_VIDEO_SWITCH);
                        }
                    }, SHOW_DIALOG_TIMEOUT);

                }
                else if (preference.getKey().equals(PREFERENCES_KEY_AUDIO))
                {
                    if (newValue.equals(true))
                    {
                        resumeAudio();
                    }
                    else
                    {
                        pauseAudio();
                    }
                }
                return true;
            }
        };

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        LogTool.v("onCreate.");
        super.onCreate(savedInstanceState);

        setStrictMode();
        initData();
        initView();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig)
    {
        LogTool.d("onConfigurationChanged");
        super.onConfigurationChanged(newConfig);
    }

    @Override
    public void onResume()
    {
        LogTool.v("onResume.");
        super.onResume();
        checkState();
    }

    @Override
    public void onBackPressed()
    {
        LogTool.v("onBackPressed.");
        super.onBackPressed();
    }

    @Override
    public void onPause()
    {
        super.onPause();
        unregisterBroadcastReceiver(mBroadcastReceiver);
    }

    @Override
    public void onStop()
    {
        LogTool.v("onStop.");
        super.onStop();
    }

    @Override
    public void onDestroy()
    {
        LogTool.v("onDestroy.");
        super.onDestroy();

        dismissProgressDialog();
        unregisterBroadcastReceiver(mBroadcastReceiver);

        if (mCheckBoxPreferenceVIme.isChecked())
        {
            writeStatusPreference(VIME_STATUS_FILE_NAME, VIME_STATUS_KEY, true);
        }
        else
        {
            writeStatusPreference(VIME_STATUS_FILE_NAME, VIME_STATUS_KEY, false);
        }

        if (mCheckBoxPreferenceGsensor.isChecked())
        {
            writeStatusPreference(GSENSOR_STATUS_FILE_NAME, GSENSOR_STATUS_KEY, true);
        }
        else
        {
            writeStatusPreference(GSENSOR_STATUS_FILE_NAME, GSENSOR_STATUS_KEY, false);
        }

        if (mCheckBoxPreferenceVideo.isChecked())
        {
            writeStatusPreference(VIDEO_STATUS_FILE_NAME, VIDEO_STATUS_KEY, true);
        }
        else
        {
            writeStatusPreference(VIDEO_STATUS_FILE_NAME, VIDEO_STATUS_KEY, false);
        }

        if (mCheckBoxPreferenceAudio.isChecked())
        {
            writeStatusPreference(AUDIO_STATUS_FILE_NAME, AUDIO_STATUS_KEY, true);
        }
        else
        {
            writeStatusPreference(AUDIO_STATUS_FILE_NAME, AUDIO_STATUS_KEY, false);
        }
    }

    /* *//**
     * Enable VIme.<br>
     * CN:使能虚拟输入法。
     */
    /*
     * private void startVimeService() { mVImeClientControlService.enableVIme();
     * }
     *//**
     * Enable VIme.<br>
     * CN:禁用虚拟输入法。
     */
    /*
     * private void stopVimeService() { if
     * (mVImeClientControlService.disableVIme()) {
     * writeStatusPreference(VIME_STATUS_FILE_NAME, VIME_STATUS_KEY, false); } }
     */

    /**
     * Start G-sensor.<br>
     * CN:开启重力感应。
     */
    private void startGsensor()
    {
        LogTool.d("start Gsensor");
        Intent intent = new Intent(SettingActivity.this, SensorService.class);
        SettingActivity.this.startService(intent);
    }

    /**
     * Stop G-sensor.<br>
     * CN:关闭重力感应。
     */
    private void stopGsensor()
    {
        LogTool.d("stop Gsensor");
        Intent mIntent = new Intent(SettingActivity.this, SensorService.class);
        SettingActivity.this.stopService(mIntent);
    }

    /**
     * Resume audio play. CN:恢复audio播放。
     */
    private void resumeAudio()
    {
        writeStatusPreference(AUDIO_STATUS_FILE_NAME, AUDIO_STATUS_KEY, true);
    }

    /**
     * Pause audio. CN:暂停audio播放。
     */
    private void pauseAudio()
    {
        writeStatusPreference(AUDIO_STATUS_FILE_NAME, AUDIO_STATUS_KEY, false);
    }

    /**
     * Resume video play. CN:恢复video播放。
     */
    private boolean resumeVideo()
    {
        return true;
    }

    /**
     * Pause video. CN:暂停video播放。
     */
    private boolean pauseVideo()
    {
        return true;
    }

    /**
     * Read enable/disable record of Gsensor.<br>
     * CN:读取体感开启/关闭记录。
     * @return - Status of Gsensor.<br>
     *         CN:Gsensor开关状态。
     */
    private boolean readGsensorStatusPreference()
    {
        boolean isOpen = false;
        boolean isFirstTime = true;

        SharedPreferences prefrence = getSharedPreferences(GSENSOR_STATUS_FILE_NAME, MODE_PRIVATE);
        isFirstTime = prefrence.getBoolean(GSENSOR_FIRST_USED_KEY, true);

        if (isFirstTime)
        {
            // CN:体感默认不开启。
            isOpen = false;
            SharedPreferences.Editor editor =
                getSharedPreferences(GSENSOR_STATUS_FILE_NAME, MODE_PRIVATE).edit();
            editor.putBoolean(GSENSOR_FIRST_USED_KEY, false);
            editor.putBoolean(GSENSOR_STATUS_KEY, false);
            editor.commit();
        }
        else
        {
            // CN:不是第一次。
            isOpen = prefrence.getBoolean(GSENSOR_STATUS_KEY, false);
        }

        return isOpen;
    }

    /**
     * Read enable/disable record of Audio.<br>
     * CN:读取Audio开启/关闭记录。
     * @return - Status of Audio.<br>
     *         CN:Audio开关状态。
     */
    private boolean readAudioStatusPreference()
    {
        boolean isOpen = false;
        boolean isFirstTime = true;

        SharedPreferences prefrence = getSharedPreferences(AUDIO_STATUS_FILE_NAME, MODE_PRIVATE);
        isFirstTime = prefrence.getBoolean(AUDIO_FIRST_USED_KEY, true);

        if (isFirstTime)
        {
            // CN:audio默认开启。
            isOpen = true;
            SharedPreferences.Editor editor =
                getSharedPreferences(AUDIO_STATUS_FILE_NAME, MODE_PRIVATE).edit();
            editor.putBoolean(AUDIO_FIRST_USED_KEY, false);
            editor.putBoolean(AUDIO_STATUS_KEY, true);
            editor.commit();
        }
        else
        {
            // CN:不是第一次。
            isOpen = prefrence.getBoolean(AUDIO_STATUS_KEY, true);
        }

        return isOpen;
    }

    public boolean readVideoStatusPreference()
    {
        boolean isOpen = false;
        boolean isFirstTime = true;
        SharedPreferences prefrence =
            getSharedPreferences(SettingActivity.VIDEO_STATUS_FILE_NAME, MODE_PRIVATE);
        isFirstTime = prefrence.getBoolean(SettingActivity.VIDEO_FIRST_USED_KEY, true);

        if (isFirstTime)
        {
            // CN:video默认开启。
            isOpen = true;
            SharedPreferences.Editor editor =
                getSharedPreferences(SettingActivity.VIDEO_STATUS_FILE_NAME, MODE_PRIVATE).edit();
            editor.putBoolean(SettingActivity.VIDEO_FIRST_USED_KEY, false);
            editor.putBoolean(SettingActivity.VIDEO_STATUS_KEY, true);
            editor.commit();
        }
        else
        {
            // CN:不是第一次。
            isOpen = prefrence.getBoolean(SettingActivity.VIDEO_STATUS_KEY, true);
        }
        return isOpen;
    }

    /**
     * Write enable/disable record of VIme.<br>
     * CN:虚拟输入法开启/关闭记录写入。
     * @param filename - CN:文件名
     * @param statusKey - CN:键值
     * @param isOpened - CN:开关状态
     */
    private void writeStatusPreference(String filename, String statusKey, boolean isOpened)
    {
        SharedPreferences.Editor editor = getSharedPreferences(filename, MODE_PRIVATE).edit();
        editor.putBoolean(statusKey, isOpened);
        editor.commit();
    }

    /**
     * Register receiver of broadcast.<br>
     * CN:注册广播接收者。
     * @param receiver - broadcast receiver.
     */
    private void registerBroadcastReceiver(BroadcastReceiver receiver)
    {
        IntentFilter filter = new IntentFilter();
        filter.addAction(MultiScreenIntentAction.SWITCH_VIME_SETTING);
        registerReceiver(receiver, filter);
    }

    /**
     * Unregister receiver of broadcast.<br>
     * CN:解注册广播接收者。
     * @param receiver - broadcast receiver.
     */
    private void unregisterBroadcastReceiver(BroadcastReceiver receiver)
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
     * Show progress dialog.<br>
     * CN:显示加载对话框。
     * @param titleId - string ID of title.<br>
     *        CN:对话框标题资源ID。
     * @param msgId - string ID of message.<br>
     *        CN:提示消息资源ID。
     */
    private void showProgressDialog(int titleId, int msgId)
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
     * CN:隐藏加载对话框。
     */
    private void dismissProgressDialog()
    {
        if (mProgressDialog != null)
        {
            mProgressDialog.dismiss();
            mProgressDialog = null;
        }
    }

    /**
     * Show dialog when VIme is opening.
     */
    private void showDialog()
    {
        mShowDialogTime = System.currentTimeMillis();
        showProgressDialog(R.string.dialogTitleLoading, R.string.dialogMessageLoading);
    }

    /**
     * Dismiss dialog and update switch.
     */
    private void dismissDialogAndUpdateChecked(SwitchItem item)
    {
        dismissProgressDialog();
        switch (item)
        {
            case VIME_SWITCH:
            {
                mDismissDialogTime = System.currentTimeMillis();
                // mCheckBoxPreferenceVIme.setChecked(mVImeClientControlService.readVIMEStatusPreference());
                break;
            }
            case VIDEO_SWITCH:
            {
                mCheckBoxPreferenceVideo.setChecked(mMultiScreenControlService.isVideoPlay());
                break;
            }
            default:
                break;
        }
    }

    /**
     * Handler of setting activity.
     */
    private static class SettingActivityHandler extends Handler
    {
        SoftReference<SettingActivity> mActivityReference = null;

        SettingActivityHandler(SettingActivity activity)
        {
            mActivityReference = new SoftReference<SettingActivity>(activity);
        }

        public void handleMessage(Message msg)
        {
            super.handleMessage(msg);
            SettingActivity activity = mActivityReference.get();

            switch (msg.what)
            {
                case SHOW_VIME_DIALOG:
                {
                    activity.showDialog();
                    break;
                }

                case DISMISS_DIALOG_AND_UPDATE_VIME_SWITCH:
                {
                    activity.dismissDialogAndUpdateChecked(SwitchItem.VIME_SWITCH);
                    break;
                }

                case SHOW_VIDEO_DIALOG:
                {
                    activity.showDialog();
                    break;
                }

                case DISMISS_DIALOG_AND_UPDATE_VIDEO_SWITCH:
                {
                    activity.dismissDialogAndUpdateChecked(SwitchItem.VIDEO_SWITCH);
                    break;
                }

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
                    activity.destroyRemoteControl();
                    break;
                }

                case MultiScreenActivity.ACCESS_REAVED:
                {
                    activity.destroyRemoteControl();
                    break;
                }

                case MultiScreenActivity.STB_LEAVE:
                {
                    activity.destroyRemoteControl();
                    break;
                }

                case MultiScreenActivity.STB_SUSPEND:
                {
                    activity.destroyRemoteControl();
                    break;
                }
                default:
                    break;
            }
        }
    }

    /**
     * Reset callback of keep alive for remote control.<br>
     * CN:重置保活的回调。
     */
    private void resetAccessListener()
    {
        if (mAccessListener == null)
        {
            mAccessListener = new IAccessListener()
            {

                @Override
                public void dealNetWorkNotWellEvent()
                {
                    // keep alive packet loss.
                    mHandler.sendEmptyMessage(MultiScreenActivity.KEEP_ALIVE_PACKET_LOSS);
                }

                @Override
                public void dealNetWorkLostEvent(Caller caller)
                {
                    // keep alive fail.
                    mHandler.sendEmptyMessage(MultiScreenActivity.KEEP_ALIVE_FAILED);
                }

                @Override
                public void dealReaveEvent(Caller caller)
                {
                    // be reaved.
                    mHandler.sendEmptyMessage(MultiScreenActivity.ACCESS_REAVED);
                }

                @Override
                public void dealSTBLeaveEvent(Caller caller)
                {
                    // be reaved.
                    mHandler.sendEmptyMessage(MultiScreenActivity.STB_LEAVE);
                }

                @Override
                public void dealSTBSuspendEvent(Caller caller)
                {
                    // be suspend
                    mHandler.sendEmptyMessage(MultiScreenActivity.STB_SUSPEND);
                }
            };
        }
        mMultiScreenControlService.setAllAccessListener(mAccessListener);
    }

    /**
     * Destroy remote control center.<br>
     */
    private void destroyRemoteControl()
    {
        mRemoteControlCenter.destroy();
        SettingActivity.this.finish();
    }

    /**
     * Set strivt mode.
     */
    private void setStrictMode()
    {
        StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder().detectDiskReads()
            .detectDiskWrites().detectNetwork().penaltyLog().build());
        StrictMode.setVmPolicy(new StrictMode.VmPolicy.Builder().detectLeakedSqlLiteObjects()
            .penaltyLog().penaltyDeath().build());
    }

    /**
     * Init service and controller.
     */
    private void initData()
    {
        mMultiScreenControlService = MultiScreenControlService.getInstance();
        mRemoteControlCenter = mMultiScreenControlService.getRemoteControlCenter();
        // mVImeClientControlService = VImeClientControlService.getInstance();
        mHandler = new SettingActivityHandler(this);
    }

    /**
     * Start vime control service.<br>
     * CN:启动虚拟输入法控制服务。
     */
    private void initVIME()
    {
        LogTool.d("initVIME");
        // Start VIME client control service.
        startService(new Intent(this, VImeClientControlService.class));
    }

    /**
     * Stop vime control service.<br>
     * CN:销毁虚拟输入法控制服务。
     */
    private void deInitVIMEService()
    {
        LogTool.v("stopService VImeClientControlService.");
        stopService(new Intent(this, VImeClientControlService.class));
    }

    /**
     * Init view of activity.
     */
    private void initView()
    {
        // registerBroadcastReceiver(mBroadcastReceiver);
        addPreferencesFromResource(R.xml.preferences);

        // CN:虚拟输入法开关。
        mCheckBoxPreferenceVIme = (CheckBoxPreference) findPreference(PREFERENCES_KEY_VIME);
        // mCheckBoxPreferenceVIme.setChecked(mVImeClientControlService.readVIMEStatusPreference());
        // mCheckBoxPreferenceVIme.setOnPreferenceChangeListener(mOnPreferenceChangeListener);

        // CN:重力感应开关。
        mCheckBoxPreferenceGsensor = (CheckBoxPreference) findPreference(PREFERENCES_KEY_GSENSOR);
        mCheckBoxPreferenceGsensor.setChecked(readGsensorStatusPreference());
        mCheckBoxPreferenceGsensor.setOnPreferenceChangeListener(mOnPreferenceChangeListener);

        // CN:video开关。
        mCheckBoxPreferenceVideo = (CheckBoxPreference) findPreference(PREFERENCES_KEY_VIDEO);
        mCheckBoxPreferenceVideo.setChecked(readVideoStatusPreference());
        mCheckBoxPreferenceVideo.setOnPreferenceChangeListener(mOnPreferenceChangeListener);

        // CN:audio开关。
        mCheckBoxPreferenceAudio = (CheckBoxPreference) findPreference(PREFERENCES_KEY_AUDIO);
        mCheckBoxPreferenceAudio.setChecked(readAudioStatusPreference());
        mCheckBoxPreferenceAudio.setOnPreferenceChangeListener(mOnPreferenceChangeListener);
    }

    /**
     * Check state of client on resume.
     */
    private void checkState()
    {
        switch (mMultiScreenControlService.getState())
        {
            case RUNNING:
            {
                resetAccessListener();
                registerBroadcastReceiver(mBroadcastReceiver);
                sendBroadcast(new Intent(MultiScreenIntentAction.SWITCH_VIME_SETTING));
                break;
            }
            default:
            {
                mHandler.sendEmptyMessage(MultiScreenActivity.KEEP_ALIVE_FAILED);
                break;
            }
        }
    }
}
