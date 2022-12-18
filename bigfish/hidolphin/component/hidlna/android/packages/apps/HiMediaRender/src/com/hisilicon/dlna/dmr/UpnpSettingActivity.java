package com.hisilicon.dlna.dmr;

import java.io.File;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.Random;
import java.util.TimerTask;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.RemoteException;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.ProgressDialog;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.BroadcastReceiver;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;
import android.os.Message;
import android.preference.CheckBoxPreference;
import android.preference.EditTextPreference;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceManager;
import android.preference.PreferenceScreen;
import android.preference.Preference.OnPreferenceChangeListener;
import android.preference.Preference.OnPreferenceClickListener;
import android.util.Log;
import android.view.Display;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.ViewDebug.IntToString;
import android.view.Window;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.widget.BaseAdapter;
import android.widget.Toast;

import android.os.ServiceManager;

//import com.hisilicon.dlna.dmr.R;

import com.hisilicon.dlna.dmr.IDMRServer;
import com.hisilicon.dlna.dms.IDMSServer;
import com.hisilicon.dlna.util.CommonDef;

/**
 * The main interface of HiDlnaSetting, Used to changing Name, opening or closeing DMS and DMR，
 * calling DMS Shared Directory Interface. HiDLNASetting <br>
 * CN:的主界面，实现了更改名称，打开关闭DMS和DMR以及调出DMS共享目录界面。 <br>
 * @author t00204177
 */
public class UpnpSettingActivity extends PreferenceActivity implements OnPreferenceChangeListener,
        OnPreferenceClickListener
{
    /** Called when the activity is first created. */

    SharedPreferences sharedPreferences;
    private boolean isShow = false;

    EditTextPreference hostName = null;
    PreferenceScreen shareDirectoryName = null;// tianjia

    CheckBoxPreference dmrStartList = null;// tianjia
    CheckBoxPreference dmsStartLsit = null;// tianjia
    ArrayList<String> textlist = null;//
    private IDMSServer dmsBinder = null;
    private IDMRServer dmrBinder = null;

    String hostNameValue = null;
    String shareDirecoryValue = null;

    String dmrStartFlag = "0";
    String dmsStartFlag = "0";

    String dmsNameValue = "HiMediaServer";
    String dmrNameValue = "HiMediaRender";

    final String HOST_NAME_KEY = "curHostName";
    final String SHARE_DIRECORY_KEY = "dms_direcory";
    final String DMR_START_KEY = "dmr_key";
    final String DMS_START_KEY = "dms_key";

    final String HOST_NAME = "host_name";
    final String DMR_INIT_START = "dmr_init_start";
    final String DMS_INIT_START = "dms_init_start";
    final String DMS_SHARED_FOLDER = "dms_share_folder";
    final String DMS_NAME = "dms_name";
    final String DMR_NAME = "dmr_name";
    final String Description_path_dmr = "data/data/com.hisilicon.dlna.dmr/files/dmr.xml";
    final String Description_path_dms = "data/data/com.hisilicon.dlna.dmr/files/dms.xml";
    final int HOST_NAME_CHANGE = 0x100;
    final int DMR_START_CHANGE = HOST_NAME_CHANGE + 1;
    final int DMS_START_CHANGE = HOST_NAME_CHANGE + 2;
    final int DMS_SHARED_CHANGE = HOST_NAME_CHANGE + 3;
    final int DMR_START_SERVICE = HOST_NAME_CHANGE + 4;
    final String BOARDCAST_TYPE = "boardcastType";
    int boardcastType = 0;

    private Boolean dmrStatusFlag = false;
    private String checkBoxFlag = null;
    ProgressDialog mypDialog = null;
    Handler loopCheckDmsStartupStatusHdl = null;
    Handler loopCheckDmrStartupStatusHdl = null;

    Context mContext = null;

    private final static String SYSTEM_AUTOTEST_CHANGE_NAME_ACTION = "com.hisilicon.dlna.devicename.changed";
    private final static String SYSTEM_SETTING_TURNOFF_DMR_ACTION = "com.hisilicon.dlna.turnoff.dmr";
    private final static String SYSTEM_SETTING_TURNON_DMR_ACTION = "com.hisilicon.dlna.turnon.dmr";
    private final static String SYSTEM_SETTING_TURNOFF_DMS_ACTION= "com.hisilicon.dlna.turnoff.dms";
    private final static String SYSTEM_SETTING_TURNON_DMS_ACTION= "com.hisilicon.dlna.turnon.dms";
    final String TAG = "UpnpSettingActivity";

    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        WindowManager m = getWindowManager();
        Display d = m.getDefaultDisplay();
        Window window = getWindow();
        if ((null != window) && (null != d))
        {
            LayoutParams p = window.getAttributes();
            p.height = (int) (d.getHeight() * 0.7);
            p.width = (int) (d.getWidth() * 0.7);

            //不需要标题<br>
            window.setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.upnp_titlebar);
            window.setAttributes(p);
        }

        readConfig();// tianjia
        Log.d(TAG, "before addPreferences");
        addPreferencesFromResource(R.xml.upnp_preference);
        setContentView(R.layout.upnp_titlebar);
        Log.d(TAG, "addPreferences");
        initUI();// tianjia
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        registerInitStatusNotifyBC();
        judgeIfDisable();

    }

    @Override
    protected void onPause()
    {
        Log.d(TAG, "onPause");
        setQuitNormal(1);
        unregisterInitStatusNotifyBC();
        super.onPause();
    }

    @Override
    public void onDestroy()
    {
        Log.d(TAG, "onDestroy");
        super.onDestroy();
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
        // TODO Auto-generated method stub
        if (keyCode == KeyEvent.KEYCODE_BACK)
        {
            if(dmsStartLsit.isEnabled() == false)
            {
                Log.d(TAG, "onKeyUp,dialog");
                return true;
            }

        }
        return super.onKeyUp(keyCode, event);
    }

    void initUI()
    {
        hostName = (EditTextPreference) findPreference(HOST_NAME_KEY);
        hostName.setOnPreferenceChangeListener(this);
        hostName.setOnPreferenceClickListener(this);
        hostName.setSummary(hostNameValue);

        shareDirectoryName = (PreferenceScreen) findPreference(SHARE_DIRECORY_KEY);
        shareDirectoryName.setOnPreferenceChangeListener(this);
        shareDirectoryName.setOnPreferenceClickListener(this);

        dmrStartList = (CheckBoxPreference) findPreference(DMR_START_KEY);
        dmrStartList.setOnPreferenceChangeListener(this);

        // tianjia
        dmsStartLsit = (CheckBoxPreference) findPreference(DMS_START_KEY);
        dmsStartLsit.setOnPreferenceChangeListener(this);

        Log.d(TAG, "dmsInitAndAddDir:" + getQuitNormal());
        setQuitNormal(0);

        judgeIfDisable();
    }

    /**
     * If DMS is initialing in BroadCast. Stop the function of DMS Checkbox until it finished.
     * 若在广播中正在启动DMS，暂时禁止CheckBox，直至启动完成
     */
    void judgeIfDisable()
    {
        readConfig();
        if (dmsStartFlag.equals("0"))
        {
            dmsStartLsit.setChecked(false);
        }
        else
        {
            dmsStartLsit.setChecked(true);
        }
        if (dmrStartFlag.equals("0"))
        {
            dmrStartList.setChecked(false);
        }
        else
        {
            dmrStartList.setChecked(true);
        }
    }


    /**
     * Calling the dialog of Shared Directory Manager. 调用共享目录管理的对话框
     */
    public boolean onPreferenceClick(Preference preference)
    {
        if (preference.getKey().equals(shareDirectoryName.getKey()))
        {// tianjia
            startActivity(new Intent(getApplicationContext(), DirManager.class));
        }
        return true;
    }

    public boolean onPreferenceChange(Preference preference, Object newValue)
    {
        Log.d(TAG, "onPreferenceChange newValue=" + newValue.toString());
        if (preference.getKey().equals(HOST_NAME_KEY))
        {
            if (hostName.getSummary().equals(newValue.toString()))
            {
                return true;
            }
            else if (newValue.toString().length() < 1)
            {
                Toast.makeText(getBaseContext(), R.string.inputNothing, Toast.LENGTH_SHORT).show();
                return false;
            }
            else
            {
                /**
                 * The name must be an alphanumeric string or underline.
                 * 命名规则为字母、数字和下划线，长度不大于MAXLENGTH
                 */
                int MAXLENGTH = 48;
                String regEx = "[^a-zA-Z0-9_]";
                Pattern p = Pattern.compile(regEx);
                Matcher m = p.matcher(newValue.toString());
                // judge the name is legal
                if ((m.find()) || (newValue.toString().length() > MAXLENGTH))
                {
                    String tmpstr = getString(R.string.ruleOfHostName) + MAXLENGTH;
                    new AlertDialog.Builder(UpnpSettingActivity.this).setTitle(R.string.error)
                            .setMessage(tmpstr).show();
                    return false;
                }
                else
                {
                    String newHostName = newValue.toString();
                    hostName.setSummary(newHostName);
                    hostNameValue = newHostName;
                }

                /**
                 * calling the protocol API respectively for DMS or DMR. 分别调用DMS和DMR的协议栈API
                 */
                Intent renameintent = new Intent();
                renameintent.setAction(SYSTEM_AUTOTEST_CHANGE_NAME_ACTION);
                renameintent.putExtra(HOST_NAME, hostNameValue);
                CommonDef.sendBroadcastEx(this, renameintent);
            }

        }
        else if (preference.getKey().equals(dmrStartList.getKey()))
        {
            dmrStartList.setEnabled(false);
            messageHandler.sendEmptyMessageDelayed(5,1500);
            if ((Boolean) newValue == true)
            {
                /**
                 * Broadcast for notify DMR Service to close DMR 广播通知DMR Service关闭DMR
                 */
                Intent intent = new Intent();
                intent.setAction(SYSTEM_SETTING_TURNON_DMR_ACTION);
                CommonDef.sendBroadcastEx(this, intent);
            }
            else
            {
                Intent intent = new Intent();
                intent.setAction(SYSTEM_SETTING_TURNOFF_DMR_ACTION);
                CommonDef.sendBroadcastEx(this, intent);
            }
        }

        // tianjia
        else if (preference.getKey().equals(dmsStartLsit.getKey()))
        {
            dmsStartLsit.setEnabled(false);
            messageHandler.sendEmptyMessageDelayed(6,1500);
            if ((Boolean) newValue == true)
            {
                Log.v("SystemSetting", "checkbox preference is clicked...true");
                Intent intent = new Intent();
                intent.setAction(SYSTEM_SETTING_TURNON_DMS_ACTION);
                CommonDef.sendBroadcastEx(this, intent);
            }
            else
            {
                Log.v("SystemSetting", "checkbox preference is clicked...false");
                Intent intent = new Intent();
                intent.setAction(SYSTEM_SETTING_TURNOFF_DMS_ACTION);
                CommonDef.sendBroadcastEx(this, intent);
            }
        }

        return true;
    }

    /**
     * Save the configure of DLNA 保存DLNA的配置
     */
    public void writeConfig()
    {

        SharedPreferences preference = getSharedPreferences("UPNPSettings",
                Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);

        Editor edit = preference.edit();
        edit.putString(HOST_NAME, hostNameValue);
        edit.putString(DMR_INIT_START, dmrStartFlag);
        // tianjia
        edit.putString(DMS_INIT_START, dmsStartFlag);
        edit.putString(DMS_NAME, dmsNameValue);
        edit.putString(DMR_NAME, dmrNameValue);
        edit.commit();
        pirntConfig();

    }

    void pirntConfig()
    {
        Log.d(TAG, "hostNameValue=" + hostNameValue);
        Log.d(TAG, "dmrStartFlag=" + dmrStartFlag);
        // tianjia
        Log.d(TAG, "dmsStartFlag=" + dmsStartFlag);
        Log.d(TAG, "dmsNameValue=" + dmsNameValue);
        Log.d(TAG, "dmrNameValue=" + dmrNameValue);

    }

    /**
     * Read the configure of DLNA 读取DLNA的配置
     */
    void readConfig()
    {
        Log.d(TAG, "readConfig");
        SharedPreferences preference = getSharedPreferences("UPNPSettings",
                Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
        hostNameValue = preference.getString(HOST_NAME, "Living Room 1");
        dmrStartFlag = preference.getString(DMR_INIT_START, "1");
        dmsStartFlag = preference.getString(DMS_INIT_START, "1");
    }


    private InitStatusNotifyReceiver dlnaSettingReceiver = null;
    private static final String DMR_START_SUCCESS_BC = "com.hisilicon.dlna.setting.DMR_SUCCESS";
    private static final String DMR_START_FAIL_BC = "com.hisilicon.dlna.setting.DMR_FAIL";
    private static final String DMS_START_SUCCESS_BC = "com.hisilicon.dlna.setting.DMS_SUCCESS";
    private static final String DMS_START_FAIL_BC = "com.hisilicon.dlna.setting.DMS_FAIL";

    private enum SettingResult
    {
        DMRSUCCESS,
        DMRFAIL,
        DMSSUCCESS,
        DMSFAIL
    }

    private enum ServiceStart
    {
        DMRSTART,
        DMRSTOP,
        DMSSTART,
        DMSSTOP
    }

    private void registerInitStatusNotifyBC()
    {
        IntentFilter filter = new IntentFilter();
        filter.addAction(DMR_START_SUCCESS_BC);
        filter.addAction(DMR_START_FAIL_BC);
        filter.addAction(DMS_START_SUCCESS_BC);
        filter.addAction(DMS_START_FAIL_BC);

        dlnaSettingReceiver = new InitStatusNotifyReceiver();
        registerReceiver(dlnaSettingReceiver, filter);
    }

    /**
     * @see #register()
     */
    private void unregisterInitStatusNotifyBC()
    {
        unregisterReceiver(dlnaSettingReceiver);
    }

    private void sendSettingBC(SettingResult r)
    {
        Intent sintent = new Intent();

        switch (r)
        {
            case DMRSUCCESS:
                sintent.setAction(DMR_START_SUCCESS_BC);
                break;
            case DMRFAIL:
                sintent.setAction(DMR_START_FAIL_BC);
                break;
            case DMSSUCCESS:
                sintent.setAction(DMS_START_SUCCESS_BC);
                break;
            case DMSFAIL:
                sintent.setAction(DMS_START_FAIL_BC);
                break;
        }

        CommonDef.sendBroadcastEx(this,sintent);
    }

    class InitStatusNotifyReceiver extends BroadcastReceiver
    {
        public void onReceive(Context context, Intent intent)
        {
            String strAction = intent.getAction();
            if (null != strAction)
            {
                Log.d(TAG, "intent.getAction():" + strAction);
                if (strAction.equalsIgnoreCase(DMR_START_SUCCESS_BC))
                {
                    dmrStartList.setChecked(true);
                    dmrStartList.setEnabled(true);
                }
                else if (strAction.equalsIgnoreCase(DMR_START_FAIL_BC))
                {
                    Log.e(TAG,"DMR start fail");
                }
                else if (strAction.equalsIgnoreCase(DMS_START_SUCCESS_BC))
                {
                    dmsStartLsit.setChecked(true);
                    dmsStartLsit.setEnabled(true);
                }
                else if (strAction.equalsIgnoreCase(DMS_START_FAIL_BC))
                {
                    Log.e(TAG,"DMS start fail");
                }
            }
            else
            {
                Log.e(TAG, "get intent.getAction is null");
            }
        }
    }

    private Handler messageHandler = new Handler()
    {

        @Override
        public void handleMessage(Message msg)
        {
            // TODO Auto-generated method stub
            switch (msg.what)
            {
                case 0:
                    dmsStartLsit.setChecked(false);
                    Toast.makeText(getBaseContext(), R.string.netDisconnected, Toast.LENGTH_SHORT)
                            .show();
                    break;
                case 1:
                    sendSettingBC(SettingResult.DMRSUCCESS);
                    dmrStartFlag = "1";
                    writeConfig();
                    CommonDef.toastEx(getBaseContext(), R.string.dmr_start_suc, Toast.LENGTH_SHORT);
                    break;
                case 2:
                    if (dmrStartList.isChecked() == true)
                    {
                        dmrStartList.setChecked(false);
                    }
                    dmrStartList.setEnabled(true);
                    dmrStartFlag = "0";
                    writeConfig();
                    CommonDef.toastEx(getBaseContext(), R.string.dmr_start_fail, Toast.LENGTH_SHORT);
                    break;
                case 3:
                    dmsStartLsit.setChecked(false);
                    CommonDef.toastEx(getBaseContext(), getString(R.string.dmsStartFail), Toast.LENGTH_LONG);
                    break;
                case 4:
                    sendSettingBC(SettingResult.DMSSUCCESS);
                    CommonDef.toastEx(getBaseContext(), getString(R.string.dmsStartSucess), Toast.LENGTH_LONG);
                    dmsStartFlag = "1";
                    writeConfig();
                    break;
                case 5:
                    dmrStartList.setEnabled(true);
                    break;
                case 6:
                    dmsStartLsit.setEnabled(true);
                    break;
                default:
                    break;
            }
        }

    };
    private int timerExpire = 0;
    private static int timerExpireSecond = 15;

    /**
     * Return whether the network is up.<br>
     * 判断网络是否连通.<br>
     */
    private boolean isNetworkEnable()
    {
        if (isAPStateOn())
        {// AP is on, can start DLNA
            return true;
        }
        ConnectivityManager networkManager = (ConnectivityManager) this
                .getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo info = networkManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
        if (info != null && info.isConnected())
        {
            return true;
        }
        info = networkManager.getNetworkInfo(ConnectivityManager.TYPE_WIMAX);
        if (info == null)
        {
            // FIXME there is no defination for TYPE_ETHERNET, so use number 9
            info = networkManager.getNetworkInfo(9); // TYPE_ETHERNET = 9 for
                                                     // ics
        }
        if (info != null && info.isConnected())
        {
            return true;
        }
        return false;
    }

    /**
     * If havn't found the network during timerExpireSecond, return false, or else return true.
     * 如果在timerExpireSecond给定的时间内没有发现网络，返回false，否则返回true。
     *
     * @return
     */
    private Boolean loopCheckNetUsableNew()
    {
        while (true)
        {
            if (isNetworkEnable() == true)
            {
                break;
            }
            try
            {
                Log.d(TAG, "sleep 1000 for net check");
                Thread.sleep(1000);
            }
            catch (Exception e)
            {
                Log.e(TAG, "sleep", e);
            }
            timerExpire++;
            Log.e(TAG, "timerExpire ==" + timerExpire++);
            if (timerExpire > timerExpireSecond)
                break;
        }
        if (timerExpire > timerExpireSecond)
        {
            timerExpire = 0;
            return false;// no netlink untile now
        }
        else
        {
            timerExpire = 0;
            try
            {
                Thread.sleep(3000);
            }
            catch (Exception e)
            {
                Log.e(TAG, "sleep", e);
            }
            return true;// get netlink
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

    public void setQuitNormal(int num)
    { // 1,normal; 0,abnormal
        SharedPreferences settings = getSharedPreferences("UPNPSettings",
                Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
        SharedPreferences.Editor editor = settings.edit();
        editor.putInt("quitNormal", num);
        editor.commit();
    }

    public boolean getQuitNormal()
    {
        SharedPreferences settings = getSharedPreferences("UPNPSettings",
                Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
        int num = settings.getInt("quitNormal", 0);
        if (num == 1)
            return true;
        else
            return false;
    }
}
