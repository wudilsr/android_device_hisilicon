package com.hisilicon.dlna.dmr;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.SystemClock;
import android.provider.Settings;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Timer;
import java.util.TimerTask;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.lang.reflect.Field;

//import com.hisilicon.dlna.settings.R;
import com.hisilicon.dlna.dmr.IDMRServer;
import com.hisilicon.dlna.dmr.DMRBinder;
import com.hisilicon.dlna.util.CommonDef;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
//import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
//import android.os.IBinder;
import android.os.Message;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.preference.CheckBoxPreference;
import android.preference.PreferenceActivity;
import android.util.Log;
import android.widget.Toast;
import android.provider.Settings.Global;
/**
 * Some processing after received the event of boot completed, such as, network condition, the DMR
 * switch state and so on <br>
 * CN: 收到开机完成事件后要做的处理， 如，网络状态判断，DMR开关状态等 <br>
 * @author t00204177
 *
 */
public class UpnpBootBroadcastServiceDMR extends Service
{
    // Context mConext=null;
    String TAG = "UpnpBootBroadcastServiceDMR";

    String hostNameValue = null;
    String shareDirecoryValue = null;

    String dmrStartFlag = "1";
    String dmsStartFlag = "1";

    String dmsNameValue = "HisiMediaServer";
    String dmrNameValue = "HisiMediaRender";

    Timer restartDLNATimer = null;
    RestartDLNATimeTask restartDLNATimeTask = null;

    final String HOST_NAME = "host_name";
    final String DMR_INIT_START = "dmr_init_start";
    final String DMS_INIT_START = "dms_init_start";
    final String DMS_SHARED_FOLDER = "dms_share_folder";
    final String DMS_NAME = "dms_name";
    final String DMR_NAME = "dmr_name";
    final String DMR_TOAST = "dmr_toast";
    final String Description_path_dmr = "data/data/com.hisilicon.dlna.dmr/files/dmr.xml";
    final String Description_path_dms = "data/data/com.hisilicon.dlna.dmr/files/dms.xml";

    // 锟姐播通知锟斤拷action锟皆硷拷锟斤拷锟酵的改憋拷
    final String ACTION = "com.upnp.SETTING_CHANGE";
    final String BOARDCAST_TYPE = "boardcastType";
    int boardcastType = 0;

    private final int NET_DISCONNECT = 0x10;
    private final int DMS_START_SUCCESS = NET_DISCONNECT + 1;
    private final int RESTART_DMR = NET_DISCONNECT + 2;
    private final int RESTART_DMS = NET_DISCONNECT + 3;
    private SystemSettingReceiverDMR systemSettingReceiver;
    private boolean isFirstMount = true;
    private final static String SYSTEM_AUTOTEST_CHANGE_NAME_ACTION = "com.hisilicon.dlna.devicename.changed";//For auto test,or only change dlna device name;
    private final static String SYSTEM_SETTING_CHANGE_NAME_ACTION = "com.hisi.devicename.changed";
    private final static String SYSTEM_SETTING_STOP_DMR_ACTION = "com.hisilicon.dlna.stop.dmr";
    private final static String SYSTEM_SETTING_START_DMR_ACTION = "com.hisilicon.dlna.start.dmr";
    private final static String SYSTEM_SETTING_TURNOFF_DMR_ACTION = "com.hisilicon.dlna.turnoff.dmr";
    private final static String SYSTEM_SETTING_TURNON_DMR_ACTION = "com.hisilicon.dlna.turnon.dmr";
    private final static String SERVICE_DMR_RESTART_ACTION = "com.hisilicon.service.dmr.restarted";
    private final static String DEFAULT_USE_ADAPTER_WIFI_ETHERNET = "eth"; //wlan

    HandlerThread startServerInActivityInBCThread = null;
    Handler handler2 = null;
    /*DMR start*/
    private IDMRServer.Stub dmrBinder2 = new DMRBinder(this);
    /*DMR end*/

    @Override
    public IBinder onBind(Intent arg0)
    {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public void onCreate()
    {
        // TODO Auto-generated method stub
        Notification notification = new Notification(R.drawable.icon,
                getText(R.string.dlnasetting_is_running), System.currentTimeMillis());
        notification.setLatestEventInfo(this, getText(R.string.dlnasetting_title),
                getText(R.string.dlnasetting_is_running), null);
        startForeground(R.string.dlnasetting_is_running, notification);
        super.onCreate();
        writeDeviceDescriptionFile();
    }

    @Override
    public void onDestroy()
    {
        // TODO Auto-generated method stub
        Log.d(TAG, "UpnpBootBroadcastService onDestroy");
        super.onDestroy();
        stopForeground(true);
        unregisterSystemSettingReceiver();
        unregisterReceiver(netStateChangeReceiver);
    }

    public int writeDescriptionFile(String pathname, String value)
    {
        FileOutputStream fout = null;
        try
        {
            fout = openFileOutput(pathname, android.content.Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
            fout.write(value.getBytes());
            fout.close();
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        if (null != fout)
        {
            try
            {
                fout.close();
            }
            catch (Exception ex)
            {
                ex.printStackTrace();
            }
        }

        return 1;
    }

    private void writeDeviceDescriptionFile()
    {
        Log.e(TAG, "Save description");
        writeDescriptionFile("dmr.xml", getString(R.string.dmrdescription));
    }

    /**
     * Judge whether DMR is checked, Start the one which was checked.
     * 判断DMR是否是选中状态，是就自动启动它们
     */
    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        if(null == intent)
        {
            Log.e(TAG, "UpnpBootBroadcastService intent is null");
            intent = new Intent("com.hisilicon.dlna.dmr.UPNP_BOOT_BROADCAST_SERVICE_DMR");
        }
        Log.d(TAG, "UpnpBootBroadcastService onStartCommand : " + intent.getAction());
        // mConext =context;//problem
        register();
        registerSystemSettingReceiver();

        if( isNetworkEnable()) {
            netOldState = "on";
        } else {
            netOldState = "off";
        }
        oldIPValue = getHostIpAddress();

        readConfig();
        pirntConfig();

        /**
         * If dmr was set to on, notify DMR Service to start DMR. <br>
         * CN: 如果dmr标记为启动，通知DMR Service 去启动DMR
         */
        if (dmrStartFlag.equals("1"))
        {
            LogHelper.trace();
            new StartDMRThread().start();
        }
        flags = START_STICKY;
        return super.onStartCommand(intent, flags, startId);
    }

    private NetStateChangeReceiver netStateChangeReceiver;
    private String netOldState = "off";//check the first time netstatechange after boot up
    //private String netOldState = "on";//don't check the first time netstatechange after boot up
    // private currentIpValue;

    private void register()
    {
        IntentFilter netStateChangeFilter = new IntentFilter();
        netStateChangeFilter.addAction("android.net.conn.CONNECTIVITY_CHANGE");
        netStateChangeFilter.addAction(WifiManager.WIFI_AP_STATE_CHANGED_ACTION);// t00204177
                                                                                 // for
                                                                                 // AP
                                                                                 // State
        netStateChangeReceiver = new NetStateChangeReceiver();
        registerReceiver(netStateChangeReceiver, netStateChangeFilter);
    }

    private void restartDMR()
    {
        boolean networkstatus = isNetworkEnable();
        if (networkstatus != true)
        {
            LogHelper.trace("return restartDMR()");
            return;
        }
        readConfig();

        /**
         * If dmr was set to on, notify DMR Service to restart DMR. <br>
         * CN: 如果dmr标记为启动，通知DMR Service去重新启动DMR<br>
         */
        if (dmrStartFlag.equals("1"))
        {
            // netExpireHandler.sendEmptyMessage(RESTART_DMR);
            LogHelper.trace("restart dmr");
            new Thread(new DMRRestartThread()).start();
        }
    }

    private void restartDLNAServer()
    {
        LogHelper.trace("restartDLNAServer");
        restartDMR();
        Log.e(TAG, "getLocalIpAddress:" + getLocalIpAddress());
    }

    private class RestartDLNATimeTask extends TimerTask
    {
        @Override
        public void run()
        {
            restartDLNAServer();
        }

    }

    private synchronized void restartDLNATimer()
    {
        if (restartDLNATimer != null)
        {
            restartDLNATimer.cancel();
            restartDLNATimer = null;
        }
        if (restartDLNATimeTask != null)
        {
            restartDLNATimeTask.cancel();
            restartDLNATimeTask = null;
        }

        if (restartDLNATimer == null)
        {
            restartDLNATimer = new Timer();
        }

        if (restartDLNATimeTask == null)
        {
            restartDLNATimeTask = new RestartDLNATimeTask();
        }

        if (restartDLNATimer != null && restartDLNATimeTask != null)
            restartDLNATimer.schedule(restartDLNATimeTask, 2000);
    }

    private String oldIPValue = null;
    private String newIPValue = null;
    private long oldTimeMillis = 0;

    class NetStateChangeReceiver extends BroadcastReceiver
    { // DTS2012102300526
      // 无线有线互切没有重启DLNA服务

        @Override
        public void onReceive(Context context, Intent intent)
        {
            String strAction = intent.getAction();
            if ((null != strAction) && (strAction.equalsIgnoreCase("android.net.conn.CONNECTIVITY_CHANGE")
                    || strAction.equals(WifiManager.WIFI_AP_STATE_CHANGED_ACTION)))
            {
                LogHelper.trace("CONNECTIVITY_CHANGE,IFI_AP_STATE_CHANGED:" + strAction);
                boolean networkstatus = isNetworkEnable();
                if (networkstatus == true)
                {
                    newIPValue = getHostIpAddress();
                    LogHelper.trace("newIPValue " + newIPValue);
                    LogHelper.trace("oldIPValue " + oldIPValue);
                    if (netOldState.equals("off"))
                    { // network restarted
                        LogHelper.trace("reconnect Network,restartDLNATimer");
                        restartDLNATimer();
                    }
                    else
                    {// network IP Changed
                     // Toast.makeText( context, "Mobile Network Type :" +
                     // oldIPValue,
                     // Toast.LENGTH_SHORT ).show();
                        //if (newIPValue != null && !newIPValue.equals(oldIPValue))
                        {
                            LogHelper.trace("IP Change,restartDLNATimer");
                            restartDLNATimer();
                        }
                    }
                    netOldState = "on";
                }
                else
                {
                    // Toast.makeText(context, "no net connect...",
                    // Toast.LENGTH_SHORT).show();
                    LogHelper.trace("netOldState set to off");
                    oldTimeMillis = System.currentTimeMillis();
                    netOldState = "off";
                }
                oldIPValue = getHostIpAddress();
            }
        }

    }

    private String getLocalIpAddress()
    {
        try
        {
            Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces();
            if (en == null)
            {
                return null;
            }
            while (en.hasMoreElements())
            {
                NetworkInterface intf = en.nextElement();
                for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr
                        .hasMoreElements();)
                {
                    InetAddress inetAddress = enumIpAddr.nextElement();
                    if (!inetAddress.isLoopbackAddress())
                    {
                        return String.format("%s", inetAddress.getHostAddress());
                    }
                    LogHelper.trace(String.format("%s", inetAddress.getHostAddress()));
                }
            }
        }
        catch (SocketException ex)
        {
            LogHelper.trace(ex.toString());
        }
        catch (Exception ex)
        {
            LogHelper.trace(ex.toString());
        }
        return null;
    }

    private class DMRRestartThread implements Runnable
    {

        public void run()
        {
            // TODO Auto-generated method stub
            stopDMR2 ();
            startDMR2();
        }

    }

    private class StartDMRThread extends Thread
    {
        StartDMRThread()
        {
        }

        public void run()
        {
            Log.e(TAG, "will start dmr");
            startDMR2();
        }
    }

    /**
     * Read the configure of DLNA 读取DLNA的配置
     */
    private void readConfig()
    {
        Log.d(TAG, "readConfig");
        LogHelper.trace();
        SharedPreferences preference = getSharedPreferences("UPNPSettings", Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
        hostNameValue = preference.getString(HOST_NAME, getBootUpSystemSettingDeviceNameKey());
        dmrStartFlag = preference.getString(DMR_INIT_START, "1");
        dmrNameValue = preference.getString(DMR_NAME, "HiMediaRender");

    }

    /**
     * Save the configure of DLNA 保存DLNA的配置
     */
    private void writeConfig()
    {

        SharedPreferences preference = getSharedPreferences("UPNPSettings", Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);

        Editor edit = preference.edit();
        edit.putString(HOST_NAME, hostNameValue);
        edit.putString(DMR_INIT_START, dmrStartFlag);
        edit.putString(DMR_NAME, dmrNameValue);
        edit.commit();
        pirntConfig();

    }

    /**
     * use broadcast to notify HiMediaShare or HiMediaplayer. They will do corresponding setting.
     * 用广播通知HiMediaShare或HiMediaplayer做相应设置
     *
     * @param type
     */
    private void setSettingChang(int type)
    {

        Intent mIntent = new Intent();
        Bundle bd = new Bundle();
        bd.putInt(BOARDCAST_TYPE, type);
        bd.putString(HOST_NAME, hostNameValue);
        bd.putString(DMR_INIT_START, dmrStartFlag);
        bd.putString(DMS_INIT_START, dmsStartFlag);
        bd.putString(DMS_SHARED_FOLDER, shareDirecoryValue);
        bd.putString(DMS_NAME, dmsNameValue);
        bd.putString(DMR_NAME, dmrNameValue);

        mIntent.setAction(ACTION);
        mIntent.putExtra("bd", bd);
        CommonDef.sendBroadcastEx(this,mIntent);
        // mConext.sendBroadcast(mIntent);
    }

    /**
     * print out the configure of DLNA. Used for debug 输出DLNA配置参数，调试用
     */
    private void pirntConfig()
    {
        LogHelper.trace();
        Log.d(TAG, "hostNameValue=" + hostNameValue);
        Log.d(TAG, "dmrStartFlag=" + dmrStartFlag);
        Log.d(TAG, "dmsStartFlag=" + dmsStartFlag);
        Log.d(TAG, "shareDirecoryValue=" + shareDirecoryValue);
        Log.d(TAG, "dmsNameValue=" + dmsNameValue);
        Log.d(TAG, "dmrNameValue=" + dmrNameValue);

    }

    private Handler netExpireHandler = new Handler()
    {

        @Override
        public void handleMessage(Message msg)
        {
            // TODO Auto-generated method stub
            switch (msg.what)
            {
                case NET_DISCONNECT:
                    CommonDef.toastEx(getApplicationContext(), R.string.netDisconnected, Toast.LENGTH_SHORT);
                    break;
                case RESTART_DMR:
                    CommonDef.toastEx(getBaseContext(), R.string.restartDMR, Toast.LENGTH_SHORT);
                    break;
                default:
                    break;
            }
        }

    };
    private int timerExpire = 0;
    private static int timerExpireSecond = 60;

    /**
     * Return whether the network is up.  <br>
     * CN: 判断网络是否连通. <br>
     */
    private boolean isNetworkEnable()
    {
        if (isAPStateOn())
        {// AP is on, can start DLNA
            return true;
        }
        ConnectivityManager networkManager = (ConnectivityManager) this
                .getSystemService(CONNECTIVITY_SERVICE);
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
     * 判断是否为合法IP
     *
     * @return the ip
     */
    private boolean isIPAddress(String ip)
    {
        Pattern p = Pattern
                .compile("([0-9]|[0-9]\\d|1\\d{2}|2[0-1]\\d|25[0-5])(\\.(\\d|[0-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])){3}");
        Matcher m = p.matcher(ip);
        boolean match = m.matches();
        if (!match)
        {
            return false;
        }
        return true;
    }

    private String getHostIpAddress()
    {
        try
        {
            Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces();
            if (en != null)
            {
                while (en.hasMoreElements())
                {
                    NetworkInterface intf = en.nextElement();
                    for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr
                            .hasMoreElements();)
                    {
                        InetAddress inetAddress = enumIpAddr.nextElement();
                        if (!inetAddress.isLoopbackAddress())
                        {
                            String ipaddress = String.format("%s", inetAddress.getHostAddress());
                            if (isIPAddress(ipaddress))
                            {
                                return ipaddress;
                            }
                        }
                    }
                }
            }
        }
        catch (SocketException ex)
        {
            Log.e(TAG, "getHostIpAddress()", ex);
        }
        catch (Exception ex)
        {
            Log.e(TAG, "getHostIpAddress()", ex);
        }
        return null;
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
            return false;// no netlink until now
        }
        else
        {
            timerExpire = 0;
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

    private void registerSystemSettingReceiver()
    {
        IntentFilter systemSettingFilter = new IntentFilter();
        systemSettingFilter.addAction(SYSTEM_SETTING_CHANGE_NAME_ACTION);
        systemSettingFilter.addAction(SYSTEM_AUTOTEST_CHANGE_NAME_ACTION);
        systemSettingFilter.addAction(SYSTEM_SETTING_STOP_DMR_ACTION);
        systemSettingFilter.addAction(SYSTEM_SETTING_START_DMR_ACTION);
        systemSettingFilter.addAction(SYSTEM_SETTING_TURNOFF_DMR_ACTION);
        systemSettingFilter.addAction(SYSTEM_SETTING_TURNON_DMR_ACTION);
        systemSettingFilter.addAction(SERVICE_DMR_RESTART_ACTION);

        systemSettingReceiver = new SystemSettingReceiverDMR();
        registerReceiver(systemSettingReceiver, systemSettingFilter);
    }
    private void unregisterSystemSettingReceiver()
    {
        if (systemSettingReceiver != null)
        {
            unregisterReceiver(systemSettingReceiver);
        }
    }
    class SystemSettingReceiverDMR extends BroadcastReceiver
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            String strAction = intent.getAction();
            if ((null != strAction) && (strAction.equalsIgnoreCase(SYSTEM_SETTING_CHANGE_NAME_ACTION))
                || SYSTEM_AUTOTEST_CHANGE_NAME_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.devicename.changed -e host_name "xxx" */
                String hostNameBC = intent.getStringExtra(HOST_NAME);
                Log.d(TAG, "receive change name bc,name = " + hostNameBC);
                systemSettingChangeName(hostNameBC);
            }
            else if(SYSTEM_SETTING_STOP_DMR_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.stop.dmr*/
                Log.d(TAG, "receive stop dmr bc");
                readConfig();
                dmrStartFlag = "0";
                writeConfig();
                stopDMR2();
            }
            else if(SYSTEM_SETTING_START_DMR_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.start.dmr*/
                Log.d(TAG, "receive start dmr bc");
                readConfig();
                dmrStartFlag = "1";
                writeConfig();
                startDMR2();
            }
            else if(SYSTEM_SETTING_TURNOFF_DMR_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.turnoff.dmr*/
                Log.d(TAG, "receive turnoff dmr bc");
                readConfig();
                dmrStartFlag = "0";
                writeConfig();
                stopDMR2();
            }
            else if(SYSTEM_SETTING_TURNON_DMR_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.turnon.dmr*/
                Log.d(TAG, "receive turnon dmr bc");
                readConfig();
                dmrStartFlag = "1";
                writeConfig();
                startDMR2();
            }
            else if(SERVICE_DMR_RESTART_ACTION.equalsIgnoreCase(strAction))
            {   //only dmrStartFlag is set to '1',it can work.
                /*adb shell am broadcast -a com.hisilicon.service.dmr.restarted*/
                Log.d(TAG, "receive dmr service restart bc");
                restartDMR();
            }
        }
    }

    private void systemSettingChangeName(String hostNameBC)
    {
        String hostName = null;
        readConfig();
        hostName = Settings.Global.getString(getContentResolver(), getSystemSettingDeviceNameKey());
        if(hostName != null)
        {
            hostNameValue = hostName;
        }
        if(hostNameBC != null)
        {
            hostNameValue = hostNameBC;
        }
        writeConfig();
        /**
         * calling the protocol API for DMR. 调用DMR的协议栈API
         */
        if (dmrStartFlag.equals("1"))
        {
            setDMRNameByStack();
        }
    }

    private String getBootUpSystemSettingDeviceNameKey() {
        String hostName = Settings.Global.getString(getContentResolver(), getSystemSettingDeviceNameKey());
        if(hostName == null)
        {
            hostName = "HiDLNA";
        }

        return hostName;
    }

    private String getSystemSettingDeviceNameKey() {
        String key = "device_name";
        try {
            Field deviceNameField = Settings.Global.class.getField("DEVICE_NAME");
            key = (String)deviceNameField.get(null);
        } catch(NoSuchFieldException e) {
            Log.e(TAG, "no class field Settings.Global.DEVICE_NAME found", e);
        } catch(SecurityException e) {
            Log.e(TAG, "getField fail", e);
        } catch(IllegalArgumentException e) {
            Log.e(TAG, "Field.get fail", e);
        } catch(IllegalAccessException e) {
            Log.e(TAG, "Field.get fail", e);
        }
        return key;
    }

    /*DMR cutMem start*/
    private boolean startDMRStack()
    {
        boolean isStart = false;
        try
        {
            dmrBinder2.setDescriptionPath(Description_path_dmr);
            //isStart = dmrBinder2.create(dmrNameValue + "(" + hostNameValue + ")");
            CommonDef.setDefaultAdapterName(DEFAULT_USE_ADAPTER_WIFI_ETHERNET);
            isStart = dmrBinder2.create(hostNameValue + "(" + dmrNameValue + ")");
            if (isStart)
            {
                ServiceManager.addService("dmr", dmrBinder2);
                CommonDef.toastEx(getBaseContext(), R.string.dmr_start_suc, Toast.LENGTH_SHORT);
            }
            else
            {
                CommonDef.toastEx(getBaseContext(), R.string.dmr_start_fail, Toast.LENGTH_SHORT);
            }
        }
        catch (RemoteException e)
        {
            Log.e(TAG, "dmr create", e);
        }
        return isStart;
    }

    private boolean stopDMRStack()
    {
        boolean result = false;
        try
        {
            result = dmrBinder2.destroy();
        }
        catch (RemoteException e)
        {
            Log.e(TAG, "dmr destroy", e);
        }
        return result;
    }

    private boolean setDMRNameByStack()
    {
        boolean result = false;
        try
        {
            //String newhostName = dmrNameValue + "(" + hostNameValue + ")";
            String newhostName = hostNameValue + "(" + dmrNameValue + ")";
            Log.d(TAG, "new hostNameValue = " + newhostName);
            result = dmrBinder2.setDeviceName(newhostName, newhostName);
        }
        catch (RemoteException e)
        {
            Log.e(TAG, "dmrBinder2.setDeviceName failed");
        }
        return result;
    }
    private boolean startDMR2()
    {
        if (loopCheckNetUsableNew() == false)
        {
            Log.e(TAG, "BR Net loop false");
            //netExpireHandler.sendEmptyMessage(NET_DISCONNECT);
            return false;
        }
        boolean isStart = startDMRStack();
        return isStart;
    }
    private boolean stopDMR2()
    {
        boolean result = stopDMRStack();
        return result;
    }
    /*DMR cutMem end*/
}
