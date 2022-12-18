package com.hisilicon.android.networkupgrade.activity;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.DownloadManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.RemoteException;
import android.os.storage.StorageManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;
import android.os.storage.ExtraInfo;
import android.os.storage.IMountService;
import android.os.ServiceManager;
import android.content.ComponentName;
import android.net.WebAddress;
import android.webkit.CookieManager;
import android.os.Environment;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.provider.Settings.System;
import java.io.File;
import java.io.FileNotFoundException;
import android.net.Uri;
import android.os.SystemProperties;
import android.widget.TextView.BufferType;
import android.database.Cursor;
import com.hisilicon.android.networkupgrade.R;
import com.hisilicon.android.hisysmanager.HiSysManager;
public class NetworkUpgradeActivity extends Activity implements android.widget.AdapterView.OnItemClickListener
{
	private static final String TAG = "NetworkUpgrade";
	private StorageManager mStorageManager   = null;
	private DownloadManager mDownloadManager = null;

	private String mSystemUpgrade = "System Upgrade";
    private String mSDKUpgrade = "SDK Upgrade";

	private static final int MSG_SYS_URL_SET = 1;
	private static final int MSG_SYS_STORAGE_SET = 2;
	private static final int MSG_LOGO_DOWNLOAD = 3;

	private Handler mSysUpgradeHandler = null;
	private List <ExtraInfo> mMntInfo = null;
	private AlertDialog mStoragePromptDialog = null;

	private long mDownloadID = -1;
    private String mDownloadPath = "/mnt/sdcard";

	private class NetworkUpgradeURLPromptListener
		implements android.content.DialogInterface.OnClickListener
		{
		View mDialogView = null;
		public NetworkUpgradeURLPromptListener(View inDialogView)
		{
		mDialogView = inDialogView;
		}
		@Override
		public void onClick(DialogInterface dialog, int which)
		{
		if (DialogInterface.BUTTON_POSITIVE == which)
		{
		setNetworkUpgradeURL(getDownloadURL());
		}
		}

		private String getDownloadURL()
		{
		if (null != mDialogView)
		{
		EditText et = (EditText) mDialogView.findViewById(R.id.network_upgrade_url_editor);
		return et.getText().toString();
		}

		return null;
		}
		}

	private class NetworkUpgradeStorageListener
		implements android.widget.AdapterView.OnItemClickListener
		{
		@Override
		public void onItemClick(AdapterView < ? > arg0, View arg1, int arg2,
		long arg3)
		{
		int position   = arg2;
		ExtraInfo elem = mMntInfo.get(position);

		if (null != elem)
		{
		Message m = mSysUpgradeHandler.obtainMessage(MSG_SYS_STORAGE_SET);
		Bundle b = new Bundle();
		b.putString("storage", elem.mMountPoint);
		m.setData(b);
		mSysUpgradeHandler.sendMessage(m);
		}
		}
		}

	private class NetworkUpgradeURLHandler extends Handler
	{
		private static final String tag = "NetworkUpgradeURLHandler";
		private String mDownloadURL = null;

		@Override
		public void handleMessage(Message msg)
		{
		switch (msg.what)
		{
		case MSG_SYS_URL_SET :
		{
		mDownloadURL = msg.getData().getString("url");
		Log.d(tag, "the network upgrade url is " + mDownloadURL);
                            downloadFile(mDownloadURL);
		//showNetworkUpgradeStorageDialog();
		break;
		}
		case MSG_SYS_STORAGE_SET:
		{
		//downloadFile(mDownloadURL, msg.getData().getString("storage"));
		mStoragePromptDialog.dismiss();
		break;
		}
		/*case MSG_LOGO_DOWNLOAD:
		{
		final String strUrl  = msg.getData().getString("url");
		final String strPath = msg.getData().getString("path");
		final String strFile = msg.getData().getString("file");
		/downloadLogo(strUrl, strPath, strFile);
		break;
		}*/
		}
		}
	}

	private static String encodePath(String path)
	{
		char[] chars = path.toCharArray();

		boolean needed = false;
		for (char c : chars)
		{
		if ((c == '[') || (c == ']'))
		{
		needed = true;
		break;
		}
		}

		if (needed == false)
		{
		return path;
		}

		StringBuilder sb = new StringBuilder("");
		for (char c : chars)
		{
		if ((c == '[') || (c == ']'))
		{
		sb.append('%');
		sb.append(Integer.toHexString(c));
		}
		else
		{
		sb.append(c);
		}
		}

		return sb.toString();
	}

	private String getUUIDByPath(String path)
	{
		IMountService mountService = getMountService();
		String mPathUUID = null;

		try
		{
		List <ExtraInfo> mntList = getMountService().getAllExtraInfos();
		if (null != mntList)
		{
		int iSize = mntList.size();
		if (iSize > 0)
		{
		for (int i = 0; i < iSize; i++)
		{
		ExtraInfo elem = mntList.get(i);
		if (null != elem)
		{
		if (path.startsWith(elem.mMountPoint))
		{
		mPathUUID = elem.mUUID;
		return mPathUUID;
		}
		}
		}
		}
		}
		} catch (RemoteException e) {
		Log.e("downloadFile", "uuid = -1:" + e);
		return "-1";
		}
		return "-1";
	}

	private void downloadFile(final String downloadUrl)
	{
		if (null != downloadUrl)
		{
		Log.d(TAG, "the url is " + downloadUrl);
		final DownloadManager.Request dmReq = new DownloadManager.Request(Uri.parse(downloadUrl));

		dmReq.setMimeType("application/zip");

		File file = new File("/mnt/sdcard/update.zip");
		if (file.exists())
		{
		file.delete();
		}

		Log.i("downloadFile", "file:" + file.getAbsolutePath());

		dmReq.setDestinationInExternalPublicDir("", "update.zip");
		WebAddress webAddress;
		try
		{
		webAddress = new WebAddress(downloadUrl);
		webAddress.setPath(encodePath(webAddress.getPath()));
		} catch (Exception e) {
		Log.e("downloadFile", "Exception trying to parse url:" + downloadUrl);
		return;
		}
		dmReq.setDescription(webAddress.getHost());
		dmReq.addRequestHeader("cookie", null);
		dmReq.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED);

		new Thread("update download")
		{
		public void run()
		{
		mDownloadID = mDownloadManager.enqueue(dmReq);
		}
		}.start();
		}
	}

	private BroadcastReceiver mDownloadReciver = new BroadcastReceiver()
	{
		@Override
		public void onReceive(Context context, Intent intent)
		{
		if (intent.getAction().equals(DownloadManager.ACTION_DOWNLOAD_COMPLETE))
		{
		Bundle extras = intent.getExtras();
		if (mDownloadID == extras.getLong(DownloadManager.EXTRA_DOWNLOAD_ID))
		{
		Log.d(TAG, "the update.zip donwloaded");
		Toast tmpToast = Toast.makeText(NetworkUpgradeActivity.this, R.string.network_upgrade_download_success, Toast.LENGTH_SHORT);
		            tmpToast.show();
		    HiSysManager hisys = new HiSysManager();
		                 hisys.upgrade(mDownloadPath);
                        Intent newIntent = new Intent("android.intent.action.MASTER_CLEAR");
                        newIntent.putExtra("mount_point", mDownloadPath);
                        sendBroadcast(newIntent);
		}
		}
		}
	};

	/** Called when the activity is first created. */
	@Override
		public void onCreate(Bundle savedInstanceState)
		{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		ListView lv = (ListView)findViewById(R.id.network_upgrade_type_list);

		String strSysUp  = this.getString(R.string.network_system_upgrade);
		String strSdkUp = this.getString(R.string.network_sdk_upgrade);
		String strMemTest = this.getString(R.string.application_terminal);
        String strBootargsInfo = this.getString(R.string.bootargs_info);
        String strLogcat = this.getString(R.string.logcat);
        String strMediaMem = this.getString(R.string.media_mem);
        String strMemInfo = this.getString(R.string.meminfo);
        String strBuildNumber = this.getString(R.string.build_number);
        String strGPU = this.getString(R.string.gpu);
        String strMemLeak = this.getString(R.string.memleak);
        String strHDMI = this.getString(R.string.hdmi);
        String strDmesg = this.getString(R.string.dmesg);

		ArrayAdapter <String> adpt = new ArrayAdapter <String>(this, android.R.layout.simple_expandable_list_item_1,
		new String[] {strSysUp,strMemTest,strBuildNumber,strBootargsInfo,strMemInfo,strMediaMem,strGPU,strMemLeak,strHDMI,strDmesg,strLogcat});
		lv.setAdapter(adpt);
		lv.setOnItemClickListener(this);

		mSysUpgradeHandler = new NetworkUpgradeURLHandler();
		mDownloadManager = (DownloadManager)getSystemService(DOWNLOAD_SERVICE);

		IntentFilter filter = new IntentFilter(DownloadManager.ACTION_DOWNLOAD_COMPLETE);
		registerReceiver(mDownloadReciver, filter);
		}

	private void showNetworkUpgradeUrlDialog()
	{
		LayoutInflater li = LayoutInflater.from(this);
		View view = li.inflate(R.layout.net_upgrade_url_prompt, null);

		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setTitle(R.string.network_upgrade_url_title);
		builder.setView(view);
		String downloadUrl;
		try
		{
		downloadUrl = System.getString(getContentResolver(), "download_url");
		} catch (Exception ex) {
		downloadUrl = null;
		}
		if ((downloadUrl != null) && !downloadUrl.equals(""))
		{
		EditText editText = (EditText)view.findViewById(R.id.network_upgrade_url_editor);
		editText.setText(downloadUrl, BufferType.EDITABLE);
		}

		NetworkUpgradeURLPromptListener urlListener = new NetworkUpgradeURLPromptListener(view);
		builder.setPositiveButton(R.string.network_upgrade_prompt_okay, urlListener);
		builder.setNegativeButton(R.string.network_upgrade_prompt_cancel, urlListener);

		AlertDialog ad = builder.create();
		ad.show();
	}

	@Override
		protected void onResume()
		{
		super.onResume();
		}

	@Override
		protected void onPause()
		{
		super.onPause();
		}

	@Override
		public void onDestroy()
		{
		if (mDownloadReciver != null)
		{
		unregisterReceiver(mDownloadReciver);
		}

		super.onDestroy();
		}

	@Override
		public void onItemClick(AdapterView < ? > arg0, View arg1, int arg2, long arg3)
		{
		// TODO Auto-generated method stub
		int position = arg2;

		if (position == 0)
		{
		    String SysUpUrl  = this.getString(R.string.network_upgrade_default_url);
            Intent intent = new Intent();
            intent.setClassName("com.hisilicon.android.networkupgrade",
		        "com.hisilicon.android.networkupgrade.activity.WebActivity");
		    startActivity(intent);
        }
		else if(position == 1)
		{
		    Intent localIntent=new Intent(this,DDRTester.class);
		    startActivity(localIntent);
		}
        else if(position == 2)
		{
		    Intent localIntent=new Intent(this,BuildNumber.class);
		    startActivity(localIntent);
		}
        else if(position == 3)
        {
		    Intent localIntent=new Intent(this,BootargsInfo.class);
		    startActivity(localIntent);
        }
        else if(position == 4)
        {
		    Intent localIntent=new Intent(this,MemInfo.class);
		    startActivity(localIntent);
        }
        else if(position == 5)
        {
		    Intent localIntent=new Intent(this,MediaMem.class);
		    startActivity(localIntent);
        }
        else if(position == 6)
        {
		    Intent localIntent=new Intent(this,GPU.class);
		    startActivity(localIntent);
        }
        else if(position == 7)
        {
		    Intent localIntent=new Intent(this,MemLeak.class);
		    startActivity(localIntent);
        }
        else if(position == 8)
        {
		    Intent localIntent=new Intent(this,HDMI.class);
		    startActivity(localIntent);
        }
        else if(position == 9)
        {
		    Intent localIntent=new Intent(this,dmesgMainActivity.class);
		    startActivity(localIntent);
        }
        else if(position == 10)
        {
		    Intent localIntent=new Intent(this,logcatMainActivity.class);
		    startActivity(localIntent);
        }
	}

	private List <String> getMountInfo()
	{
		List <String> data = new ArrayList <String>();
		int iSize = mMntInfo.size();
		for (int i = 0; i < iSize; i++)
		{
		ExtraInfo elem = mMntInfo.get(i);
		if (null != elem)
		{
		int start = elem.mMountPoint.lastIndexOf("/");
		data.add(elem.mMountPoint.substring(start + 1));
		}
		}

		return data;
	}

	private void showNetworkUpgradeStorageDialog()
	{
		try
		{
		mMntInfo = getMountService().getAllExtraInfos();
		if (null != mMntInfo)
		{
		int iSize = mMntInfo.size();
		if (iSize > 0)
		{
		for (int i = 0; i < iSize; i++)
		{
		ExtraInfo elem = mMntInfo.get(i);
		if (null != elem)
		{
		Log.d(TAG, "the mountPoint is " + elem.mMountPoint + " , UUID is " + elem.mUUID);
		}
		}
		}
		else
		{
		Toast tmpToast = Toast.makeText(this, R.string.network_upgrade_no_sdcard, Toast.LENGTH_SHORT);
		tmpToast.show();
		return;
		}
		}
		} catch (RemoteException e) {}

		//show dialog
		LayoutInflater li = LayoutInflater.from(this);
		View view = li.inflate(R.layout.net_upgrade_storage_medium, null);

		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setTitle(R.string.network_upgrade_storage_tiltle);
		builder.setView(view);
		builder.setNegativeButton(R.string.network_upgrade_prompt_cancel, null);

		ListView lv = (ListView)view.findViewById(R.id.network_upgrade_storage_list);
		lv.setAdapter(new ArrayAdapter <String>(this, android.R.layout.simple_expandable_list_item_1, getMountInfo()));
		lv.setOnItemClickListener(new NetworkUpgradeStorageListener());

		mStoragePromptDialog = builder.create();
		mStoragePromptDialog.show();
	}

	public void setNetworkUpgradeURL(String url)
	{
		if (null != url)
		{
		Message m = mSysUpgradeHandler.obtainMessage(MSG_SYS_URL_SET);
		Bundle b = new Bundle();
		b.putString("url", url);
		m.setData(b);
		mSysUpgradeHandler.sendMessage(m);
		}
	}

	private static IMountService getMountService()
	{
		IBinder service = ServiceManager.getService("mount");

		if (service != null)
		{
		return IMountService.Stub.asInterface(service);
		}
		else
		{
		Log.e(TAG, "Can't get mount service");
		}

		return null;
	}

    private boolean checkDownloadSuccess()
    {
        boolean bRet = false;

        DownloadManager mgr = (DownloadManager)getSystemService(DOWNLOAD_SERVICE);

        Log.i("checkDownloadSuccess", "mDownloadID:" + mDownloadID);
        try
        {
            Cursor c = mgr.query(new DownloadManager.Query().setFilterById(mDownloadID));
            if (null != c)
            {
                c.moveToFirst();
                int iStatus = c.getInt(c.getColumnIndex(DownloadManager.COLUMN_STATUS));
                if (DownloadManager.STATUS_SUCCESSFUL == iStatus)
                {
                    bRet = true;
                }

                c.close();
            }
        } catch (Exception ex) {
            Log.i("checkDownloadSuccess", "");
        }

        return bRet;
    }
}
