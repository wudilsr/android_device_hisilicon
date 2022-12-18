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
import com.hisilicon.dlna.dms.IDMSServer;
import com.hisilicon.dlna.dms.DMSBinder;
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
 * Some processing after received the event of boot completed, such as, network condition, the DMS
 * switch state and so on <br>
 * CN: 收到开机完成事件后要做的处理， 如，网络状态判断，DMS开关状态等 <br>
 * @author t00204177
 *
 */
public class UpnpBootBroadcastServiceDMS extends Service
{
    // Context mConext=null;
    String TAG = "UpnpBootBroadcastServiceDMS";

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

    final String ACTION = "com.upnp.SETTING_CHANGE";
    final int HOST_NAME_CHANGE = 0x100;
    final int DMR_START_CHANGE = HOST_NAME_CHANGE + 1;
    final int DMS_START_CHANGE = HOST_NAME_CHANGE + 2;
    final int DMS_SHARED_CHANGE = HOST_NAME_CHANGE + 3;
    final String BOARDCAST_TYPE = "boardcastType";
    int boardcastType = 0;

    private final int NET_DISCONNECT = 0x10;
    private final int DMS_START_SUCCESS = NET_DISCONNECT + 1;
    private final int RESTART_DMR = NET_DISCONNECT + 2;
    private final int RESTART_DMS = NET_DISCONNECT + 3;
    private UsbMountEventReceiver usbReceiver;
    private SystemSettingReceiverDMS systemSettingReceiver;
    private boolean isFirstMount = true;
    private boolean isDMSStarted = false;
    private final static String SYSTEM_AUTOTEST_CHANGE_NAME_ACTION = "com.hisilicon.dlna.devicename.changed";//For auto test,or only change dlna device name;
    private final static String SYSTEM_SETTING_CHANGE_NAME_ACTION = "com.hisi.devicename.changed";
    private final static String SYSTEM_SETTING_STOP_DMS_ACTION = "com.hisilicon.dlna.stop.dms";
    private final static String SYSTEM_SETTING_START_DMS_ACTION = "com.hisilicon.dlna.start.dms";
    private final static String SYSTEM_SETTING_TURNOFF_DMS_ACTION= "com.hisilicon.dlna.turnoff.dms";
    private final static String SYSTEM_SETTING_TURNON_DMS_ACTION= "com.hisilicon.dlna.turnon.dms";
    private final static String SYSTEM_SETTING_REMOVE_SHAREDDIR_ACTION= "com.hisilicon.dlna.remove.shareddir";
    private final static String SYSTEM_SETTING_ADD_SHAREDDIR_ACTION= "com.hisilicon.dlna.add.shareddir";
    private final static String SERVICE_DMS_RESTART_ACTION = "com.hisilicon.service.dms.restarted";
    private final int DIR_ADD= 0x10;
    private final int DIR_REMOVE= DIR_ADD + 1;

    HandlerThread startServerInActivityInBCThread = null;
    Handler handler2 = null;
    Handler handleDMSInit = null;
    /*DMS start*/
    private IDMSServer.Stub dmsBinder2 = new DMSBinder(this);;
    /*DMS end*/

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
        Log.d(TAG, "UpnpBootBroadcastServiceDMS onDestroy");
        super.onDestroy();
        stopForeground(true);
        unregisterSystemSettingReceiver();
        unregisterReceiver(netStateChangeReceiver);
        unregisterUsbMountEventReceiver();
        /**
         * If it binded dms Server,free it . <br>
         * CN: 如果绑定了dms Server，在此服务销毁时释放<br>
         */
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
        writeDescriptionFile("dms.xml", getString(R.string.dmsdescription));
        //writeDescriptionFile("dms.xml", getResources().getString(R.string.dmsdescription));
    }

    /**
     * Judge whether DMS is checked, Start the one which was checked.
     * 判断DMS是否是选中状态，是就自动启动它们
     */
    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        if(null == intent)
        {
            Log.e(TAG, "UpnpBootBroadcastServiceDMS intent is null");
            intent = new Intent("com.hisilicon.dlna.dmr.UPNP_BOOT_BROADCAST_SERVICE_DMS");
        }
        Log.d(TAG, "UpnpBootBroadcastServiceDMS onStartCommand : " + intent.getAction());
        // mConext =context;//problem
        register();
        registerSystemSettingReceiver();
        registerUsbMountEventReceiver();

        if( isNetworkEnable()) {
            netOldState = "on";
        } else {
            netOldState = "off";
        }
        oldIPValue = getHostIpAddress();

        readConfig();
        pirntConfig();

        /**
         * If dms was set to on, notify HiMediaShare to start DMS Service, and start DMS in
         * handleDMSInitRun. 如果dms标记为启动，通知HiMediaShare启动DMS Service，并在handleDMSInitRun中启动DMS
         */
        if (dmsStartFlag.equals("1"))
        {
            handleDMSInit = new Handler();
            handleDMSInit.post(handleDMSInitRun);
        }
        flags = START_STICKY;
        return super.onStartCommand(intent, flags, startId);
    }

    Runnable handleDMSInitRun = new Runnable()
    {

        public void run()
        {
            Log.e(TAG, "will start dms");
            LogHelper.trace();
            Log.d(TAG, "will run startDmsafterBroadCast");
            LogHelper.trace();
            // start Thread
            startServerInActivityInBCThread = new HandlerThread("startServerInActivityInBC_Thread");
            startServerInActivityInBCThread.start();
            handler2 = new Handler(startServerInActivityInBCThread.getLooper());
            handler2.post(startDMSServerInBR);
        }
    };

    Runnable startDMSServerInBR = new Runnable()
    {

        public void run()
        {
            // TODO Auto-generated method stub
            Log.d(TAG, "The Thread Name = " + Thread.currentThread().getName() + "The Thread ID = "
                    + Thread.currentThread().getId());
            LogHelper.trace();
            startDMS2();
        }

    };

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

    private void restartDMS()
    {
        boolean networkstatus = isNetworkEnable();
        if (networkstatus != true)
        {
            LogHelper.trace("return restartDMS()");
            return;
        }
        readConfig();

        /**
         * If dms was set to on, restart DMS Service. 如果dms标记为启动，重启DMS Service
         */
        if (dmsStartFlag.equals("1"))
        {
            LogHelper.trace("restart dms");
            // netExpireHandler.sendEmptyMessage(RESTART_DMS);
            new Thread(new DMSRestartThread()).start();
        }
    }
    private void restartDLNAServer()
    {
        LogHelper.trace("restartDLNAServer");
        restartDMS();
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
                    {// network IP
                     // Changed
                     // Toast.makeText( context, "Mobile Network Type :" +
                     // oldIPValue,
                     // Toast.LENGTH_SHORT ).show();
                        if (newIPValue != null && !newIPValue.equals(oldIPValue))
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

    private class DMSRestartThread implements Runnable
    {

        public void run()
        {
            stopDMS2();
            startDMS2();
            // netExpireHandler.sendEmptyMessage(DMS_START_SUCCESS);
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
        dmsStartFlag = preference.getString(DMS_INIT_START, "1");
        shareDirecoryValue = preference.getString(DMS_SHARED_FOLDER, "");
        dmsNameValue = preference.getString(DMS_NAME, "HiMediaServer");
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
        // tianjia
        edit.putString(DMS_INIT_START, dmsStartFlag);
        edit.putString(DMS_NAME, dmsNameValue);
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


    private Handler dirAddRemoveHandler = new Handler()
    {

        @Override
        public void handleMessage(Message msg)
        {
            // TODO Auto-generated method stub
            switch (msg.what)
            {
                case DIR_ADD:
                    break;
                case DIR_REMOVE:
                    break;
                default:
                    break;
            }
        }

    };
    private Handler netExpireHandler = new Handler()
    {

        @Override
        public void handleMessage(Message msg)
        {
            // TODO Auto-generated method stub
            switch (msg.what)
            {
                case NET_DISCONNECT:
                    readConfig();
                    dmsStartFlag = "0";
                    writeConfig();
                    CommonDef.toastEx(getApplicationContext(), R.string.netDisconnected, Toast.LENGTH_SHORT);
                    //Toast.makeText(getApplicationContext(), R.string.netDisconnected,
                    //        Toast.LENGTH_SHORT).show();

                    break;
                case DMS_START_SUCCESS:
                    CommonDef.toastEx(getBaseContext(), R.string.dmsStartSucess, Toast.LENGTH_SHORT);
                    break;
                case RESTART_DMS:
                    CommonDef.toastEx(getBaseContext(), R.string.restartDMS, Toast.LENGTH_SHORT);
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
                                // Toast.makeText( getBaseContext(),ipaddress ,
                                // Toast.LENGTH_SHORT ).show();
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

    public ArrayList<String> getDirDataList(String text)
    {
        ArrayList<String> dataList = new ArrayList<String>();
        if (null != text)
        {
            String[] sArray = text.split(":");
            for (int i = 0; i < sArray.length; i++)
            {
                dataList.add(sArray[i]);
            }
        }
        return dataList;
    }

    private class UsbMountEventReceiver extends BroadcastReceiver
    {
        public void onReceive(Context context, Intent intent)
        {
            String action = intent.getAction();
            if (null != action)
            {
                if (action.equals(Intent.ACTION_MEDIA_MOUNTED))
                {
                    Log.d(TAG, "receive mount event");
                    if (isDMSStarted && isFirstMount)
                    {
                        isFirstMount = false;
                        reAddShareDir();
                        CommonDef.toastEx(UpnpBootBroadcastServiceDMS.this, R.string.readd_dir, Toast.LENGTH_SHORT);
                    }
                }
                else if (action.equals(Intent.ACTION_MEDIA_UNMOUNTED))
                {
                    // TODO unmounted
                    Log.d(TAG, "receive unmount event");
                }
                else if (action.equals(Intent.ACTION_MEDIA_EJECT))
                {
                    // TODO eject
                    Log.d(TAG, "receive eject event");
                }
            }else
            {
                Log.e(TAG,"UsbMountEventReceiver get Action is null");
            }
        }
    }

    private void registerUsbMountEventReceiver()
    {
        usbReceiver = new UsbMountEventReceiver();
        IntentFilter usbFilter = new IntentFilter();
        usbFilter.addAction(Intent.ACTION_MEDIA_MOUNTED);
        usbFilter.addAction(Intent.ACTION_MEDIA_UNMOUNTED);
        usbFilter.addAction(Intent.ACTION_MEDIA_EJECT);
        usbFilter.addDataScheme("file");
        registerReceiver(usbReceiver, usbFilter);
    }

    private void unregisterUsbMountEventReceiver()
    {
        if (usbReceiver != null)
        {
            unregisterReceiver(usbReceiver);
        }
    }

    private void reAddShareDir()
    {
        SharedPreferences preference = getSharedPreferences("UPNPSettings", Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);

        String text = preference.getString("dirPath", "");
        Log.d(TAG, "dirlist:" + text);
        ArrayList<String> textlist = getDirDataList(text);
        for (int i = 0; i < textlist.size(); i++)
        {
            try
            {
                if (dmsBinder2.delShareDir(dmsNameValue, textlist.get(i)))
                {
                    Log.d(TAG, new StringBuffer("dms delShareDir+").append(dmsNameValue)
                            .append("+").append(textlist.get(i)).append(" successfully").toString());
                }
                else
                {
                    Log.d(TAG, new StringBuffer("dms delShareDir+").append(dmsNameValue)
                            .append("+").append(textlist.get(i)).append(" fail").toString());
                }
                if (dmsBinder2.addShareDir(dmsNameValue, textlist.get(i)))
                {
                    Log.d(TAG, new StringBuffer("dms addShareDir+").append(dmsNameValue)
                            .append("+").append(textlist.get(i)).append(" successfully").toString());
                }
                else
                {
                    Log.d(TAG, new StringBuffer("dms addShareDir+").append(dmsNameValue)
                            .append("+").append(textlist.get(i)).append(" fail").toString());
                }
            }
            catch (RemoteException e)
            {
                Log.e(TAG, "add or del shareDir", e);
            }
            LogHelper.trace();
        }
    }

    private void registerSystemSettingReceiver()
    {
        IntentFilter systemSettingFilter = new IntentFilter();
        systemSettingFilter.addAction(SYSTEM_SETTING_CHANGE_NAME_ACTION);
        systemSettingFilter.addAction(SYSTEM_AUTOTEST_CHANGE_NAME_ACTION);
        systemSettingFilter.addAction(SYSTEM_SETTING_STOP_DMS_ACTION);
        systemSettingFilter.addAction(SYSTEM_SETTING_START_DMS_ACTION);
        systemSettingFilter.addAction(SYSTEM_SETTING_TURNOFF_DMS_ACTION);
        systemSettingFilter.addAction(SYSTEM_SETTING_TURNON_DMS_ACTION);
        systemSettingFilter.addAction(SYSTEM_SETTING_REMOVE_SHAREDDIR_ACTION);
        systemSettingFilter.addAction(SYSTEM_SETTING_ADD_SHAREDDIR_ACTION);
        systemSettingFilter.addAction(SERVICE_DMS_RESTART_ACTION);

        systemSettingReceiver = new SystemSettingReceiverDMS();
        registerReceiver(systemSettingReceiver, systemSettingFilter);
    }
    private void unregisterSystemSettingReceiver()
    {
        if (systemSettingReceiver != null)
        {
            unregisterReceiver(systemSettingReceiver);
        }
    }
    class SystemSettingReceiverDMS extends BroadcastReceiver
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
            else if(SYSTEM_SETTING_STOP_DMS_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.stop.dms*/
                Log.d(TAG, "receive stop dms bc");
                stopDMS2();
            }
            else if(SYSTEM_SETTING_START_DMS_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.start.dms*/
                Log.d(TAG, "receive start dms bc");
                startDMS2();
            }
            else if(SYSTEM_SETTING_TURNOFF_DMS_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.turnoff.dms*/
                Log.d(TAG, "receive turnoff dms bc");
                readConfig();
                dmsStartFlag = "0";
                writeConfig();
                stopDMS2();
            }
            else if(SYSTEM_SETTING_TURNON_DMS_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.turnon.dms*/
                Log.d(TAG, "receive turnon dmr bc");
                readConfig();
                dmsStartFlag = "1";
                writeConfig();
                startDMS2();
            }
            else if(SYSTEM_SETTING_REMOVE_SHAREDDIR_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.remove.shareddir*/
                Log.d(TAG, "receive dms remove shareddir bc");
                String rmDir = intent.getStringExtra("rmDir");
                Log.d(TAG, "remove :" + rmDir);
                rmOneDirByStack(rmDir);
            }
            else if(SYSTEM_SETTING_ADD_SHAREDDIR_ACTION.equalsIgnoreCase(strAction))
            {
                /*adb shell am broadcast -a com.hisilicon.dlna.add.shareddir*/
                Log.d(TAG, "receive dms add shareddir bc");
                String addDir = intent.getStringExtra("addDir");
                Log.d(TAG, "add :" + addDir);
                addOneDirByStack(addDir);
            }
            else if(SERVICE_DMS_RESTART_ACTION.equalsIgnoreCase(strAction))
            {   //only dmsStartFlag is set to '1',it can work.
                /*adb shell am broadcast -a com.hisilicon.service.dms.restarted*/
                Log.d(TAG, "receive dms service restart bc");
                restartDMS();
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
         * calling the protocol API for DMS. 分别调用DMS和DMR的协议栈API
         */
        if (dmsStartFlag.equals("1"))
        {
            //new Thread(new RestartDMSThread()).start();
            setDMSNameByStack();
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

    /*DMS cutMem start*/
    private boolean startDMSStack()
    {
        boolean result = false;
        try
        {
            dmsBinder2.setDescriptionPath(Description_path_dms);
            result = dmsBinder2.create(dmsNameValue + "(" + hostNameValue + ")", "");
            isDMSStarted = true;
            return true;
        }
        catch (RemoteException e)
        {
            Log.e(TAG, "dmsBinder2.create failed in BroadCast", e);
            LogHelper.trace();
        }
        return result;
    }
    private boolean stopDMSStack()
    {
        boolean result = false;
        try
        {
            result = dmsBinder2.destroy();
        }
        catch (RemoteException e)
        {
            LogHelper.trace();
        }
        return result;
    }
    private boolean setDMSNameByStack()
    {
        boolean result = false;
         try
         {
             String newhostName = dmsNameValue + "(" + hostNameValue + ")";
             Log.d(TAG, "new hostNameValue = " + newhostName);
             result = dmsBinder2.setDeviceName(newhostName, newhostName);
         }
         catch (RemoteException e)
         {
             Log.e(TAG, "dmsBinder2.setDeviceName failed");
         }
         return result;
    }
    private boolean addOneDirByStack(String dirPath)
    {
        boolean r = false;
        try
        {
            r = dmsBinder2.addShareDir(hostNameValue, dirPath);
        }
        catch (RemoteException e)
        {
            Log.e(TAG, "dmsBinder2.addShareDir failed in BroadCast", e);
            LogHelper.trace();
        }
        return r;
    }
    private boolean rmOneDirByStack(String dirPath)
    {
        boolean r = false;
        try
        {
            r = dmsBinder2.delShareDir(hostNameValue, dirPath);
        }
        catch (RemoteException e)
        {
            Log.e(TAG, "dmsBinder2.delShareDir failed in BroadCast", e);
            LogHelper.trace();
        }
        return r;
    }
    private void addDMSSharedDirByStack()
    {
        SharedPreferences preference = getSharedPreferences("UPNPSettings", Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
        String text = preference.getString("dirPath", "");
        try
        {
            ArrayList<String> textlist = getDirDataList(text);
            for (int i = 0; i < textlist.size(); i++)
            {
                if (dmsBinder2.addShareDir(dmsNameValue, textlist.get(i)))
                {
                    Log.d(TAG, new StringBuffer("dms addShareDir+").append(dmsNameValue)
                            .append("+").append(textlist.get(i)).append(" successfully")
                            .toString());
                }
                else
                {
                    Log.d(TAG, new StringBuffer("dms addShareDir+").append(dmsNameValue)
                            .append("+").append(textlist.get(i)).append(" fail").toString());
                }
                LogHelper.trace();
            }
            netExpireHandler.sendEmptyMessage(DMS_START_SUCCESS);
            Log.e(TAG, "dmsBinder2.create success in BroadCast");
            LogHelper.trace();
        }
        catch (RemoteException e)
        {
            Log.e(TAG, "dmsBinder2.create failed in BroadCast", e);
            LogHelper.trace();
        }
    }
    private boolean startDMS2()
    {
        boolean result = false;
        if (loopCheckNetUsableNew() == false)
        {
            Log.e(TAG, "BR Net loop false");
            //netExpireHandler.sendEmptyMessage(NET_DISCONNECT);
            return false;
        }
        result = startDMSStack();
        addDMSSharedDirByStack();
        return result;
    }
    private boolean stopDMS2()
    {
        boolean result = stopDMSStack();
        return result;
    }
    /*DMS cutMem end*/
}
