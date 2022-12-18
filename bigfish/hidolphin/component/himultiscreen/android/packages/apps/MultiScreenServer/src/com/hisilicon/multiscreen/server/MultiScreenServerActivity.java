package com.hisilicon.multiscreen.server;

import java.lang.ref.WeakReference;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningServiceInfo;
import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.preference.CheckBoxPreference;
import android.preference.EditTextPreference;
import android.preference.Preference;
import android.preference.Preference.OnPreferenceChangeListener;
import android.preference.PreferenceActivity;
import android.widget.Toast;

import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;

/**
 * MultiScreen service activity on STB.<br>
 * CN:多屏服务端活动。
 * @since HiMultiScrren_V1.0.1.0 2013/01/18 add accessing control function.<br>
 *        CN:增加抢占接入控制功能。
 */
public class MultiScreenServerActivity extends PreferenceActivity
{
    /**
     * Preference name.<br>
     * CN:配置文件名。
     */
    public static final String MULTISCREEN_SETTING_FILE_NAME = "MultiScreenSetting";

    /**
     * Preference key of friendly name.<br>
     * CN:备注名的配置键值。
     */
    public static final String MULTISCREEN_FRIENDLY_KEY_NAME = "FriendlyName";

    public static final String DEFAULT_FRIENDLY_NAME = "HiMultiScreen";

    /**
     * Max length of friendly name.<br>
     * CN:备注名最大长度。
     */
    public static final int MAX_LENGTH_OF_FRIENDLY_NAME = 24;

    /**
     * Switch state manager.<br>
     * CN:服务开关状态管理器。
     */
    private SwitchStateManager stateManager = null;

    private static final String MULTI_SCREEN_SERVICE_NAME =
        "com.hisilicon.multiscreen.server.MultiScreenService";

    private CheckBoxPreference mCheckPrefUpdateSwitch = null;

    private EditTextPreference mEditPrefFriendlyName = null;

    private enum MSG_ACTION
    {
        HIDE_PROGESSBAR, SHOW_PROGESSBAR, FRIENDLY_NAME_TOO_LONG, FRIENDLY_NAME_BLANK, FRIENDLY_NAME_INVALID_CHARACTERS
    }

    private ProgressDialog mProgressDialog = null;

    /**
     * Switch value.<br>
     * CN:开关值。
     */
    private boolean mSwitchValue = true;

    private MyHandler mProgessBarHandle = null;

    private BroadcastReceiver mReceiver = new BroadcastReceiver()
    {
        public void onReceive(Context context, Intent intent)
        {
            String action = intent.getAction();
            if (MultiScreenIntentAction.MULITSCREEN_SERVER_START.equals(action)
                || MultiScreenIntentAction.MULITSCREEN_SERVER_STOP.equals(action))
            {
                Message msg = mProgessBarHandle.obtainMessage();
                msg.obj = MSG_ACTION.HIDE_PROGESSBAR;
                msg.sendToTarget();
                LogTool.d("receive broadcast: " + action);
            }
        }
    };

    private void startStopService(boolean isSwitchOpen)
    {
        if (isSwitchOpen)
        {
            stateManager.open();
            startService();
        }
        else
        {
            stateManager.close();
            stopService();
        }
    }

    /**
     * UI handler.<br>
     */
    private static class MyHandler extends Handler
    {
        WeakReference<MultiScreenServerActivity> mActivity;

        MyHandler(MultiScreenServerActivity activity)
        {
            mActivity = new WeakReference<MultiScreenServerActivity>(activity);
        }

        public void handleMessage(Message msg)
        {
            super.handleMessage(msg);
            MultiScreenServerActivity multiScreenServerActivity = mActivity.get();

            MSG_ACTION action = (MSG_ACTION) msg.obj;
            switch (action)
            {
                case SHOW_PROGESSBAR:
                {
                    multiScreenServerActivity.showProgressDialog(R.string.dialogTitleLoading,
                        R.string.dialogMessageLoading);
                }
                    break;

                case HIDE_PROGESSBAR:
                {
                    try
                    {
                        Thread.currentThread();
                        Thread.sleep(1000);
                    }
                    catch (InterruptedException e)
                    {
                        LogTool.e("Interrupted Exception.");
                    }

                    multiScreenServerActivity.dismissProgressDialog();

                    if (multiScreenServerActivity.mSwitchValue)
                    {
                        Toast.makeText(multiScreenServerActivity, R.string.start_service,
                            Toast.LENGTH_SHORT).show();
                    }
                    else
                    {
                        Toast.makeText(multiScreenServerActivity, R.string.stop_service,
                            Toast.LENGTH_SHORT).show();
                    }
                }
                    break;

                case FRIENDLY_NAME_TOO_LONG:
                {
                    Toast.makeText(multiScreenServerActivity, R.string.friendly_name_too_long,
                        Toast.LENGTH_SHORT).show();
                }
                    break;

                case FRIENDLY_NAME_BLANK:
                {
                    Toast.makeText(multiScreenServerActivity, R.string.friendly_name_blank,
                        Toast.LENGTH_SHORT).show();
                }
                    break;

                case FRIENDLY_NAME_INVALID_CHARACTERS:
                {
                    Toast.makeText(multiScreenServerActivity,
                        R.string.friendly_name_invalid_characters, Toast.LENGTH_SHORT).show();
                }
                    break;

                default:
                {
                    break;
                }
            }
        }
    };

    /**
     * Friendly name change listener.<br>
     * CN:STB备注名称变更监听者。
     */
    private OnPreferenceChangeListener mFriendlyNameChangeListener =
        new OnPreferenceChangeListener()
        {
            public boolean onPreferenceChange(Preference preference, Object newValue)
            {
                String formatName = getFormatName(newValue.toString());
                resetEditPrefFriendlyName(formatName);

                if (!readFriendlyName().equals(formatName))
                {
                    writeFriendlyNamePreference(formatName);

                    if (MultiScreenService.isStackOpen())
                    {
                        // CN:备注名变更，重启UPNP。
                        startService();
                    }
                    else
                    {
                        LogTool.d("Rename STB when upnp stack is not running.");
                    }
                }

                return false;
            }
        };

    /**
     * Server switch change listener.<br>
     * CN:服务开关变化监听者。
     */
    private OnPreferenceChangeListener mServerSwitchChangeListener =
        new OnPreferenceChangeListener()
        {
            public boolean onPreferenceChange(Preference preference, Object newValue)
            {
                Message msg = mProgessBarHandle.obtainMessage();
                msg.obj = MSG_ACTION.SHOW_PROGESSBAR;
                msg.sendToTarget();
                mSwitchValue = newValue.equals(true);
                startStopService(mSwitchValue);
                return true;
            }
        };

    /**
     * 活动建立时调用，根据设置启动服务。 Called when the activity is first created. start
     * service according to setting.
     * */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        LogTool.d("onCreate");
        super.onCreate(savedInstanceState);
        initView();
        initData();
    }

    @Override
    public void onResume()
    {
        LogTool.d("onResume");
        super.onResume();
        initService();
    }

    @Override
    public void onDestroy()
    {
        LogTool.d("onDestroy");
        super.onDestroy();

        unregisterReceiver(mReceiver);
        stateManager.deinit();
    }

    private void initView()
    {
        addPreferencesFromResource(R.xml.preferences);
        mCheckPrefUpdateSwitch = (CheckBoxPreference) findPreference("mutiserver");
        mEditPrefFriendlyName = (EditTextPreference) findPreference("FriendlyName");
        resetEditPrefFriendlyName(readFriendlyName());
    }

    private void initData()
    {
        mProgessBarHandle = new MyHandler(this);
        IntentFilter filter = new IntentFilter();
        filter.addAction(MultiScreenIntentAction.MULITSCREEN_SERVER_START);
        filter.addAction(MultiScreenIntentAction.MULITSCREEN_SERVER_STOP);
        registerReceiver(mReceiver, filter);

        stateManager = SwitchStateManager.getInstance(this);
        stateManager.init();

        // Add preference change listener. CN:添加设置变化监听。
        mEditPrefFriendlyName.setOnPreferenceChangeListener(mFriendlyNameChangeListener);
        mCheckPrefUpdateSwitch.setOnPreferenceChangeListener(mServerSwitchChangeListener);
    }

    /**
     * Start MultiScreen service.<br>
     * CN:启动服务。
     */
    private void startService()
    {
        Intent intent = new Intent(MultiScreenIntentAction.MULITSCREEN_SWITCH_OPEN);
        sendBroadcast(intent);
    }

    /**
     * Stop MultiScreen service.<br>
     * CN:停止服务。
     */
    private void stopService()
    {
        Intent intent = new Intent(MultiScreenIntentAction.MULITSCREEN_SWITCH_CLOSE);
        sendBroadcast(intent);
    }

    /**
     * Init service if it's not running.<br>
     * CN:若服务没有启动则启动服务。
     */
    private void initService()
    {
        if (isServiceRunning() == false)
        {
            LogTool.d("Find MultiScreenService is not running, so start it.");
            startService(new Intent(this, MultiScreenService.class));
        }

        // CN:当状态值与界面开关状态冲突，以界面值为准启停服务。
        boolean isSwitchOpen = mCheckPrefUpdateSwitch.isChecked();
        if (isSwitchOpen != stateManager.isOpen())
        {
            stateManager.setState(isSwitchOpen);
            startStopService(isSwitchOpen);
            LogTool.d("Switch open: " + isSwitchOpen);
        }
    }

    /**
     * Check service status of running.<br>
     * CN:检查服务是否正在运行。
     * @return - Status of running.<br>
     *         CN:运行状态。
     */
    private boolean isServiceRunning()
    {
        ActivityManager manager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
        List<RunningServiceInfo> serviceLists = manager.getRunningServices(Integer.MAX_VALUE);
        if (null == serviceLists)
        {
            LogTool.e("RunningServiceInfo is null");
            return false;
        }
        for (RunningServiceInfo service : serviceLists)
        {
            if (MULTI_SCREEN_SERVICE_NAME.equalsIgnoreCase(service.service.getClassName()))
            {
                return true;
            }
        }
        return false;
    }

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

    private void dismissProgressDialog()
    {
        if (mProgressDialog != null)
        {
            mProgressDialog.dismiss();
            mProgressDialog = null;
        }
    }

    private void resetEditPrefFriendlyName(String name)
    {
        mEditPrefFriendlyName.setSummary(name);
        mEditPrefFriendlyName.setText(name);
        Editor fridendlyEditor = mEditPrefFriendlyName.getEditor();
        if (fridendlyEditor != null)
        {
            fridendlyEditor.commit();
        }
    }

    private String readFriendlyName()
    {
        SharedPreferences prefrence =
            getSharedPreferences(MultiScreenServerActivity.MULTISCREEN_SETTING_FILE_NAME,
                Context.MODE_PRIVATE);
        return prefrence.getString(MultiScreenServerActivity.MULTISCREEN_FRIENDLY_KEY_NAME,
            DEFAULT_FRIENDLY_NAME);
    }

    private void writeFriendlyNamePreference(String friendlyName)
    {
        SharedPreferences.Editor editor =
            getSharedPreferences(MULTISCREEN_SETTING_FILE_NAME, MODE_PRIVATE).edit();
        editor.putString(MULTISCREEN_FRIENDLY_KEY_NAME, friendlyName);
        editor.commit();
    }

    private String replaceBlank(String str)
    {
        String dest = "";
        if (str != null)
        {
            Pattern p = Pattern.compile("\\t|\r|\n");
            Matcher m = p.matcher(str);
            dest = m.replaceAll("");
        }
        return dest;
    }

    private String getFormatName(String inputName)
    {
        String name = replaceBlank(inputName).trim();

        // Warning: nothing changes.
        if (name.length() <= 0)
        {
            // Blank.
            Message msg = mProgessBarHandle.obtainMessage();
            msg.obj = MSG_ACTION.FRIENDLY_NAME_BLANK;
            msg.sendToTarget();
            name = readFriendlyName();
        }
        else if (name.getBytes().length > MAX_LENGTH_OF_FRIENDLY_NAME)
        {
            // Too long.
            Message msg = mProgessBarHandle.obtainMessage();
            msg.obj = MSG_ACTION.FRIENDLY_NAME_TOO_LONG;
            msg.sendToTarget();
            name = readFriendlyName();
        }
        else if (readFriendlyName().equals(name) && !inputName.equals(name))
        {
            // Invalid characters.
            Message msg = mProgessBarHandle.obtainMessage();
            msg.obj = MSG_ACTION.FRIENDLY_NAME_INVALID_CHARACTERS;
            msg.sendToTarget();
        }

        return name;
    }
}
