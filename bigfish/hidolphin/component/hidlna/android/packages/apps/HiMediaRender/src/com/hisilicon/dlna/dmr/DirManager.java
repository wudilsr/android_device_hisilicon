package com.hisilicon.dlna.dmr;

import java.util.ArrayList;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.view.WindowManager.LayoutParams;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

//import com.hisilicon.dlna.settings.R;

import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;
import android.os.Message;
import android.os.RemoteException;
import android.os.ServiceManager;
import com.hisilicon.dlna.dms.IDMSServer;
import com.hisilicon.dlna.util.CommonDef;

/**
 *
 * Add or remove the Shared Directory List for DMS <br>
 * CN:添加、删除DMS的共享目录列表 <br>
 * @author t00204177
 */
public class DirManager extends Activity
{
    ArrayList<String> text = null;
    ListView list_view = null;
    private ClickDeleteAdapter clickDeleteAdapter = null;
    private IDMSServer dmsBinder;
    private SharedPreferences preference = null;
    final String HOST_NAME = "host_name";
    private String hostNameValue = null;
    final String TAG = "UpnpSettingActivity";
    private Button button = null;

    HandlerThread dmsAddDirThread = null;
    Handler addDirHandler = null;
    HandlerThread dmsDelDirThread = null;
    Handler delDirHandler = null;
    String addPathForHandler = null;
    String delPathForHandler = null;
    private int countOption = 0;
    private final static String SYSTEM_SETTING_REMOVE_SHAREDDIR_ACTION= "com.hisilicon.dlna.remove.shareddir";
    private final static String SYSTEM_SETTING_ADD_SHAREDDIR_ACTION= "com.hisilicon.dlna.add.shareddir";
    //private final int DIR_ADD= 0x10;
    //private final int DIR_REMOVE= DIR_ADD + 1;

    // @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        // requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);// set title bar
        setContentView(R.layout.upnp_dir_manager);

        WindowManager m = getWindowManager();
        Display d = m.getDefaultDisplay();
        Window window = getWindow();
        if ((null != window) && (null != d))
        {
            LayoutParams p = window.getAttributes(); // 获取对话框当前的参数
            p.height = (int) (d.getHeight() * 0.7); // 高度设置为屏幕的1.0
            p.width = (int) (d.getWidth() * 0.7); // 宽度设置为屏幕的0.8
            // p.x = 110;
            // p.y = -30;
            // p.alpha = 1.0f; //设置本身透明
            // p.dimAmount = 0.0f; //设置黑暗
            window.setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.upnp_titlebar);
            window.setAttributes(p); // 设置生效
        }

        list_view = (ListView) findViewById(R.id.list_view);
        text = getDirDataList();
        //
        clickDeleteAdapter = new ClickDeleteAdapter(this, text);
        list_view.setAdapter(clickDeleteAdapter);
        countOption = 0;

        button = (Button) findViewById(R.id.addButton);
        button.setOnClickListener(new OnClickListener()
        {
            // @Override
            public void onClick(View v)
            {
                clickDeleteAdapter.notifyDataSetChanged();

                /**
                 * Calling Directory explorer。 <br>
                 * CN:  调用目录浏览器<br>
                 */
                Intent intent = new Intent(DirManager.this, DirExplorDialog.class);
                startActivityForResult(intent, 1);

            }
        });

        /**
         * click to remove the line of directory name。 <br>
         * CN:  单击删除光标所在的目录行<br>
         */
        list_view.setOnItemClickListener(new OnItemClickListener()
        {

            // @Override
            public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3)
            {
                // TODO Auto-generated method stub
                String sdir = text.get(arg2);
                String rmsdir = getString(R.string.remove) + " " + sdir;
                Toast.makeText(getBaseContext(), rmsdir, Toast.LENGTH_SHORT).show();
                removeDirDataFromList(sdir);
                text.remove(arg2);
                ((BaseAdapter) list_view.getAdapter()).notifyDataSetChanged();
                // >>>>>>>>dms rm dir
                //dirAddRemoveHandler.sendEmptyMessage(DIR_REMOVE);
                Intent rmintent = new Intent();
                rmintent.setAction(SYSTEM_SETTING_REMOVE_SHAREDDIR_ACTION);
                rmintent.putExtra("rmDir", sdir);
                CommonDef.sendBroadcastEx(getBaseContext(), rmintent);
                //delPathForHandler = sdir;
                //dmsDelDirThread = new HandlerThread("dmsDelDir_Thread");
                //dmsDelDirThread.start();
                //delDirHandler = new Handler(dmsDelDirThread.getLooper());
                //delDirHandler.post(delDirRun);

            }

        });
    }

    private Handler handler = new Handler()
    {

        @Override
        public void handleMessage(Message msg)
        {
            // TODO Auto-generated method stub
            switch (msg.what)
            {
                case 0:
                    ((BaseAdapter) list_view.getAdapter()).notifyDataSetChanged();
                    break;
                default:
                    break;
            }
        }

    };

    @Override
    protected void onDestroy()
    {
        // TODO Auto-generated method stub
        super.onDestroy();
        if (dmsBinder != null)
            unbindService(serviceConnection);

    }

    /**
     * Get the Shared Directory name from DirExplorDialog.class，and add to DMS <br>
     * CN: 从DirExplorDialog.class中获得需要共享的目录名，并添加到DMS<br>
     */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent intent)
    {
        // super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == 1 && resultCode == 1)
        {
            Bundle data = intent.getExtras();
            if (null != data)
            {
                String value = data.getString("dirPath");
                if (!dirCheckRepeat(value))
                {
                    text.add(value);
                    ((BaseAdapter) list_view.getAdapter()).notifyDataSetChanged();

                    addDirDataToList(value);
                    // >>>>>>>>>>>>>>>dms add dir
                    //dirAddRemoveHandler.sendEmptyMessage(DIR_ADD);
                    Intent addintent = new Intent();
                    addintent.setAction(SYSTEM_SETTING_ADD_SHAREDDIR_ACTION);
                    addintent.putExtra("addDir", value);
                    CommonDef.sendBroadcastEx(getBaseContext(), addintent);
                    //addPathForHandler = value;
                    //dmsAddDirThread = new HandlerThread("dmsAddDir_Thread");
                    //dmsAddDirThread.start();
                    //addDirHandler = new Handler(dmsAddDirThread.getLooper());
                    //addDirHandler.post(addDirRun);
                    //String addsdir = getString(R.string.add) + " " + value;
                    //Toast.makeText(getBaseContext(), addsdir, Toast.LENGTH_SHORT).show();
                }
                else
                {
                    String tmp = value + getString(R.string.alreadyExist);
                    Toast.makeText(getBaseContext(), tmp, Toast.LENGTH_SHORT).show();
                }
            }
        }
    }

/*
    private Handler dirAddRemoveHandler = new Handler()
    {

        @Override
        public void handleMessage(Message msg)
        {
            // TODO Auto-generated method stub
            switch (msg.what)
            {
                case DIR_ADD:
                    Intent addintent = new Intent();
                    addintent.setAction(SYSTEM_SETTING_ADD_SHAREDDIR_ACTION);
                    CommonDef.sendBroadcastEx(getBaseContext(), addintent);
                    break;
                case DIR_REMOVE:
                    Intent rmintent = new Intent();
                    rmintent.setAction(SYSTEM_SETTING_REMOVE_SHAREDDIR_ACTION);
                    CommonDef.sendBroadcastEx(getBaseContext(), rmintent);
                    break;
                default:
                    break;
            }
        }

    };
*/

    Runnable delDirRun = new Runnable()
    {

        // @Override
        public void run()
        {
            // TODO Auto-generated method stub
            Log.d(TAG, "The Thread Name = " + Thread.currentThread().getName() + "The Thread ID = "
                    + Thread.currentThread().getId() + "start");
            dms_rm_dir(delPathForHandler);
            Log.d(TAG, "The Thread Name = " + Thread.currentThread().getName() + "The Thread ID = "
                    + Thread.currentThread().getId() + "finish");
        }
    };

    private ServiceConnection serviceConnection = new ServiceConnection()
    {

        public void onServiceDisconnected(ComponentName arg0)
        {
            // TODO Auto-generated method stub

        }

        public void onServiceConnected(ComponentName name, IBinder service)
        {
            // TODO Auto-generated method stub
            LogHelper.trace();
            dmsBinder = IDMSServer.Stub.asInterface(service);
        }
    };

    // synchronized void dms_rm_dir(String folderName){
    /**
     * Remove the directory from DMS. If failed to bind service， rebind in 5 seconds
     * 将选择目录删除，如果绑定服务失败5秒后重新绑定
     *
     * @param folderName
     */
    void dms_rm_dir(String folderName)
    {
        CommonDef.bindServiceEx(this, new Intent("com.hisilicon.dlna.dms.IDMSServer"), serviceConnection,
                Context.BIND_AUTO_CREATE);
        if (dmsBinder != null)
        {
            Log.d(TAG, "dms get service success");
            // dmsBinder =
            // IDMSServer.Stub.asInterface(ServiceManager.getService("dms"));
            preference = getSharedPreferences("UPNPSettings", Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
            hostNameValue = preference.getString(HOST_NAME, "Living Room 1");
            try
            {
                showSyncNotify();// send notify
                // synchronized (this) {
                setCountOption();
                Log.d(TAG, "The Thread Name = " + Thread.currentThread().getName()
                        + "The Thread ID = " + Thread.currentThread().getId() + " start"
                        + " dms_rm_dir");
                dmsBinder.delShareDir(hostNameValue, folderName);
                cutCountOption();
                // }
                if (getCountOption() == 0)
                {
                    showreadyNotify();// send notify
                }
            }
            catch (RemoteException e)
            {
                Log.e(TAG, "dmsBinder.delShareDir", e);
            }
            // Toast.makeText(getApplicationContext(),"remove dir" + folderName,
            // Toast.LENGTH_SHORT).show();
        }
        else
        {
            // TODO
            Log.d(TAG, "dmsBinder failed init");
            delDirHandler.postDelayed(delDirRun, 5000);
        }
    }

    Runnable addDirRun = new Runnable()
    {

        // @Override
        public void run()
        {

            Log.d(TAG, "The Thread Name = " + Thread.currentThread().getName() + "The Thread ID = "
                    + Thread.currentThread().getId() + "start");
            // TODO Auto-generated method stub
            dms_add_dir(addPathForHandler);
            Log.d(TAG, "The Thread Name = " + Thread.currentThread().getName() + "The Thread ID = "
                    + Thread.currentThread().getId() + "finish");
        }
    };

    /**
     * Add the directory to DMS. If failed to bind service, rebind in 5 seconds.
     * 将选择目录添加到DMS，如果绑定服务失败5秒后重新绑定
     *
     * @param folderName
     */
    // synchronized void dms_add_dir(String folderName){
    void dms_add_dir(String folderName)
    {

        CommonDef.bindServiceEx(this, new Intent("com.hisilicon.dlna.dms.IDMSServer"), serviceConnection,
                Context.BIND_AUTO_CREATE);
        //
        if (dmsBinder != null)
        {
            Log.d(TAG, "dms get service success");
            // dmsBinder =
            // IDMSServer.Stub.asInterface(ServiceManager.getService("dms"));
            preference = getSharedPreferences("UPNPSettings", Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
            hostNameValue = preference.getString(HOST_NAME, "Living Room 1");
            try
            {
                showSyncNotify();// send notify
                // synchronized (this) {
                setCountOption();
                Log.d(TAG, "The Thread Name = " + Thread.currentThread().getName()
                        + "The Thread ID = " + Thread.currentThread().getId() + " start"
                        + " dms_add_dir");
                boolean r = dmsBinder.addShareDir(hostNameValue, folderName);
                if (r == false)
                {
                    Toast.makeText(getApplicationContext(), getString(R.string.noPermissionAccess),
                            Toast.LENGTH_SHORT).show();
                    removeDirDataFromList(folderName);
                    text.remove(folderName);
                    handler.sendEmptyMessage(0);
                }
                cutCountOption();
                // }
                if (getCountOption() == 0)
                {
                    showreadyNotify();// send notify
                }
            }
            catch (RemoteException e)
            {
                Log.e(TAG, "dmsBinder.addShareDir", e);
            }
            // Toast.makeText(getApplicationContext(),"add dir" + folderName,
            // Toast.LENGTH_SHORT).show();
            // Toast.makeText(getApplicationContext(), text, duration)
        }
        else
        {
            // TODO
            Log.d(TAG, "dmsBinder failed init");
            addDirHandler.postDelayed(addDirRun, 5000);
        }

    }

    private byte[] lock = new byte[0];

    private void setCountOption()
    {
        synchronized (lock)
        {
            countOption++;
        }
    }

    private void cutCountOption()
    {
        synchronized (lock)
        {
            countOption--;
        }
    }

    private int getCountOption()
    {
        return countOption;
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////
    // @Override
    /**
     * Focus on button though the remote control left arrow keys <br>
     * CN:  通过遥控器的左方向键，将光标定位到button上<br>
     */
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        Log.e(TAG, "stop after finish" + getCountOption());

        //
        if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT)
        {
            // Toast.makeText(this.context,"aaaaa", Toast.LENGTH_SHORT).show();
            // System.out.println("left pressed");
            button.requestFocus();
            return true;
        }
        else
        {
            return super.onKeyDown(keyCode, event);
        }
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////
    static final int notifyDMS_ID = 0x1124;

    void showSyncNotify()
    {
        PendingIntent pi = PendingIntent.getActivity(this, 0, new Intent(this,
                UpnpSettingActivity.class), 0);
        Notification syncNotify = new Notification();
        syncNotify.icon = R.drawable.sync;
        syncNotify.tickerText = getString(R.string.mediaSync);
        syncNotify.when = System.currentTimeMillis();
        syncNotify.setLatestEventInfo(DirManager.this, getString(R.string.dmsSync),
                getString(R.string.clicknotify), pi);
        NotificationManager notificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
        notificationManager.notify(notifyDMS_ID, syncNotify);
    }

    void showreadyNotify()
    {
        PendingIntent pi = PendingIntent.getActivity(this, 0, new Intent(this,
                UpnpSettingActivity.class), 0);
        Notification readyNotify = new Notification();
        readyNotify.icon = R.drawable.ready;
        readyNotify.tickerText = getString(R.string.mediaReady);
        readyNotify.when = System.currentTimeMillis();
        readyNotify.setLatestEventInfo(DirManager.this, getString(R.string.dmsReady),
                getString(R.string.clicknotify), pi);
        NotificationManager notificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
        notificationManager.notify(notifyDMS_ID, readyNotify);
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * Check whether the directory have been added 检查是否已经添加了此目录
     *
     * @param str
     * @return
     */
    public boolean dirCheckRepeat(String str)
    {
        ArrayList<String> dirList = getDirDataList();
        return dirList.contains(str);
    }

    /**
     * add dir and update sharedpreference configure file <br>
     * CN:  添加目录，并更新sharedpreference配置文件 <br>
     *
     * @param dirPath
     * @return
     */
    public boolean addDirDataToList(String dirPath)
    {
        String text = readPrefString();
        // System.out.println(text);
        if (dirPath == null)
            return false;

        if (text == null)
            text = dirPath;
        else
            text = text + ":" + dirPath;

        writePrefString(text);
        return true;
    }

    /**
     * remove dir and update sharedpreference configure file  <br>
     * CN: 删除目录，并更新sharedpreference配置文件<br>
     *
     * @param dirPath
     * @return
     */
    public boolean removeDirDataFromList(String dirPath)
    {
        if (dirPath == null)
            return false;
        ArrayList<String> sList = getDirDataList();
        sList.remove(dirPath);
        StringBuffer text = null;

        for (int i = 0; i < sList.size(); i++)
        {
            if (null == text)
                text = new StringBuffer(sList.get(i));
            else
            {
                text.append(":");
                text.append(sList.get(i));
            }
        }
        if (null != text)
        {
            writePrefString(text.toString());
        }
        else
        {
            writePrefString(null);
        }
        return true;
    }

    /**
     * Assign the shared directory name to ArrayList  <br>
     * CN: 将已添加的共享目录名分配到ArrayList中，便于处理 <br>
     *
     * @return
     */
    public ArrayList<String> getDirDataList()
    {
        ArrayList<String> dataList = new ArrayList<String>();
        String text = readPrefString();
        if (text != null)
        {
            String[] sArray = text.split(":");
            for (int i = 0; i < sArray.length; i++)
            {
                dataList.add(sArray[i]);
            }
        }
        return dataList;
    }

    public boolean writePrefString(String str)
    {
        SharedPreferences settings = getSharedPreferences("UPNPSettings",
                Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
        SharedPreferences.Editor editor = settings.edit();
        editor.putString("dirPath", str);
        editor.commit();
        return true;
    }

    public String readPrefString()
    {
        SharedPreferences settings = getSharedPreferences("UPNPSettings",
                Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
        String text = settings.getString("dirPath", null);
        return text;
    }

}
