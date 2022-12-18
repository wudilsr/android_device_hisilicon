
package com.android.qb;

import android.app.IQbAndroidManager;

import android.app.Service;
import android.app.WallpaperManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.RemoteException;
import android.util.Log;
import android.widget.Toast;

import android.content.ComponentName;
import android.net.Uri;
import android.provider.Settings;
import android.os.Bundle;
import android.content.ContentResolver;
import android.os.UserHandle;
import android.os.Environment;
import android.os.Process;
import android.media.AudioManager;
import android.os.ServiceManager;
import android.os.AsyncTask;
import android.os.SystemProperties;

import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.File;
import java.util.HashMap;
import java.util.Map;

import android.app.WallpaperInfo;
import android.app.WallpaperManager;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlPullParserFactory;

import android.app.QbAndroidManager;
import java.lang.Exception;

import android.util.Slog;

public class QbAndroidManagerService extends IQbAndroidManager.Stub {

	static final String TAG = "QbAndroidManagerService";
	static final boolean DEBUG = false;


	private static enum CHANGE_TYPE {
		NO_CHANGE,
		WALLPAPER_CLASS,
		REFRESH
	};

	private class AppField {
		private String mClassName;
		private String mEntryName;

		public String getClassName() {
			return mClassName;
		}

		public String getEntryName() {
			return mEntryName;
		}

		AppField(String className, String entryName) {
			this.mClassName = className;
			this.mEntryName = entryName;
		}

		@Override
		public boolean equals(Object obj) {
			try {
				AppField pAppField = (AppField)obj;
				return equals(pAppField.getClassName(), pAppField.getEntryName());
			} catch (Exception e) {
				return false;
			}
		}

		public boolean equals(String className, String mEntryName) {
			if (this.mClassName.equals(mClassName)
					&& this.mEntryName.equals(mEntryName)) {
				return true;
			} else {
				return false;
			}
		}

		@Override
		public int hashCode() {
			return mClassName.hashCode()+mEntryName.hashCode();
		}

	}

	private Map<AppField, Boolean> groupWakeUpChecks = new HashMap<AppField, Boolean>();

	private void entryWakeUpWait(String className, String name) {
		if (DEBUG) Slog.v(TAG, "entryWakeUpWait [" +className+ "][" +name+ "]");
		groupWakeUpChecks.put(new AppField(className, name), false);
	}

	private boolean raiseHandWakeUpWait(String className, String name) {
		if (DEBUG) Slog.v(TAG, "raiseHandWakeUpWait [" +className+ "][" +name+ "]");
		for (Map.Entry<AppField, Boolean> entry : groupWakeUpChecks.entrySet()) {
		    AppField key = entry.getKey();
		    Boolean value = entry.getValue();
			if (key.equals(className, name)) {
				if (DEBUG) Slog.v(TAG, "raiseHandWakeUpWait Hit!! [" +className+ "][" +name+ "]");
				groupWakeUpChecks.put(key, true);
				return value;
			}
		}
		if (DEBUG) Slog.v(TAG, "raiseHandWakeUpWait not find... [" +className+ "][" +name+ "]");
		return false;
	}

	private Boolean get(String className, String name) {
		for (Map.Entry<AppField, Boolean> entry : groupWakeUpChecks.entrySet()) {
		    AppField key = entry.getKey();
		    Boolean value = entry.getValue();
			if (key.equals(className, name)) {
				return value;
			}
		}
		return null;
	}

	private boolean checkState() {
		for (Map.Entry<AppField, Boolean> entry : groupWakeUpChecks.entrySet()) {
			if (!entry.getValue()) {
				return false;
			}
		}
		return true;
	}

	private int mQbState = QbAndroidManager.WS_NORMAL_BOOT;

	final Context mContext;

	IntentReceiver mIntentReceiver = new IntentReceiver();

	private AppField findAppField(String className, String filedName) {
		for(Map.Entry<AppField, Boolean> e : groupWakeUpChecks.entrySet()) {
			if (e.getKey().equals(className, filedName)) {
				return e.getKey();
			}
		}
		return null;
	}

	private boolean checkGroupWakeUpCheck() {
		for(Map.Entry<AppField, Boolean> e : groupWakeUpChecks.entrySet()) {
			if (DEBUG) Slog.v(TAG, "["+ e.getValue() +"]:[" +e.getKey().getClassName()+ "][" +e.getKey().getEntryName()+ "]");
			if (!e.getValue()) {
				return false;
			}
		}
		return true;
	}

	@Override
	public int getQbState() throws RemoteException {
		if (DEBUG) Slog.v(TAG, "Start getQbState - ret (" +mQbState+ ")");
		return mQbState;
	}

	public void setQbState(int qb_state) throws RemoteException {

		if (DEBUG) Slog.v(TAG, "Start setQbState (" + qb_state + ")");

		if (qb_state > QbAndroidManager.WS_STAND_UP) {
			return;
		} else {
			mQbState = qb_state;
		}
	}

	@Override
	public boolean entryWait(int type, String className, String entryName) {
		if (DEBUG) Slog.v(TAG, "Start entryWait [" + className + "][" + entryName + "]");

		switch(type) {
		case QbAndroidManager.ET_QB_WAKEUP:
			entryWakeUpWait(className, entryName);
			break;
		default:
			return false;
		}
		return true;
	}

	@Override
	public boolean raiseHandWaikUp(String className, String name) {
		if (DEBUG) Slog.v(TAG, "Start raiseHandWaikUp [" + className + "][" + name + "]");
		return raiseHandWakeUpWait(className, name);

	}

	public QbAndroidManagerService(Context context) {
            String buf = "Start QbAndroidManagerService";
            if (DEBUG)
                Slog.v(TAG, buf);
            mContext = context;

            Log.i("Qb", "System.loadLibrary android_qb");
            System.loadLibrary("android_qb");

            IntentFilter filter = new IntentFilter();
            filter.addAction(Intent.ACTION_QB_SNAPSHOT_START);
            //filter.addAction(Intent.ACTION_QB_SNAPSHOT_END);
            //filter.addAction(Intent.ACTION_QB_STAND_UP);
            filter.addAction(Intent.ACTION_QB_WAKE_UP);
            filter.addAction(Intent.ACTION_BOOT_COMPLETED);

            context.registerReceiver(mIntentReceiver, filter);
            // Entry SettingsProvider (SettingsProvider can't use BroadcastReceiver!)
            entryWakeUpWait("SettingsProvider", "settings");

	}

	private class IntentReceiver extends BroadcastReceiver {

            //private QbAndroidManagerService mQbAndroidManagerService;

            private static final String TAG = "QbAndroid - IntentReceiver";
            final boolean DEBUG = true;
            /*
            IntentReceiver(QbAndroidManagerService qb) {
		mQbAndroidManagerService = qb;
            }
            */
            private Context mContext;
            private Intent mIntent;
		private WallpaperInfo mWallpaperInfo;
		private CHANGE_TYPE changeType;
		private WallpaperManager wm;
		private String next;

		private void localSetQbState(int state) {
			try {
				setQbState(state);
			} catch (android.os.RemoteException e) {
			}
		}

		@Override
		public void onReceive(Context context, Intent intent) {

			mContext = context;
			mIntent = intent;

			String action = intent.getAction();
			if (DEBUG) Log.d(TAG, action);

			if (DEBUG) Log.d(TAG, "Start.");


			if (Intent.ACTION_QB_SNAPSHOT_START.equals(action)) {

				return;

			} else if (Intent.ACTION_QB_WAKE_UP.equals(action)) {

				return;

			} else if (Intent.ACTION_BOOT_COMPLETED.equals(action)) {
                if (DEBUG) Log.d(TAG, "AudioManager reloadAudioSettings Start");
                AudioManager mAudioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
                mAudioManager.reloadAudioSettings();
                if (DEBUG) Log.d(TAG, "AudioManager reloadAudioSettings End");
                Log.i(TAG, "Check Load PersistProps");
                Intent reload_intent = new Intent(Intent.ACTION_QB_PROP_RELOAD);
                while(SystemProperties.get("sys.qb.reload").equals("trigger_load_persist_props"))
                {
                    try
                    {
                        Thread.sleep(100);
                    }
                    catch (java.lang.InterruptedException e)
                    {
                    }
                }
                if(SystemProperties.get("sys.qb.reload").equals("load_persist_props"))
                {
                    Log.i("Qb", "Intent.ACTION_QB_PROP_RELOAD");
                    context.sendBroadcast(reload_intent);
                }
			}

			if (DEBUG) Log.d(TAG, "End.");

		}

		private class TaskSnapshotStart extends AsyncTask<Integer, Void, Integer> {
			private Context context;
			public TaskSnapshotStart(Context context){
				if (DEBUG) Log.d(TAG + ":TaskSnapshotStart", "Creat TaskSnapshotStart");
				this.context = context;
			}

	        protected Integer doInBackground(Integer... params){
				if (DEBUG) Log.d(TAG + ":TaskSnapshotStart", "Call doInBackground");

				if (DEBUG) Log.d(TAG, "***");
				if (DEBUG) Log.d(TAG, "***");
				if (DEBUG) Log.d(TAG, "* Intent.ACTION_QB_SNAPSHOT_START");
				if (DEBUG) Log.d(TAG, "***");
				if (DEBUG) Log.d(TAG, "***");

				localSetQbState(QbAndroidManager.WS_SNAPSHOT_START);
				stopSettingsProvider();
				if (DEBUG) Log.d(TAG + ":TaskSnapshotStart", "Return.");
		             return 0;
		    }

			protected void onPostExecute(Integer result) {
				if (DEBUG) Log.d(TAG + ":TaskSnapshotStart", "Exit TaskSnapshotStart");
		    }
		}


		private class TaskWakeUp extends AsyncTask<String, Integer, Integer> {
			private Context context;
			public TaskWakeUp(Context context){
				this.context = context;
			}

	        protected Integer doInBackground(String... params){

				if (DEBUG) Log.d(TAG + ":TaskWakeUp", "Call doInBackground params:" + params[0]);
				String mode = params[0];

				if (DEBUG) Log.d(TAG, "***");
				if (DEBUG) Log.d(TAG, "***");
				if (DEBUG) Log.d(TAG, "* Intent.ACTION_QB_WAKE_UP");


				if (mode.equals("3")) {
					next = Intent.ACTION_QB_SNAPSHOT_END;
				} else if (mode.equals("4")) {
					next = Intent.ACTION_QB_STAND_UP;
				} else {
					next = null;
				}

				if (DEBUG) Log.d(TAG, "* next " + next);
				if (DEBUG) Log.d(TAG, "***");
				if (DEBUG) Log.d(TAG, "***");

				localSetQbState(QbAndroidManager.WS_WAKE_UP);

				refreshSettingsProvider();

				if (DEBUG) Log.d(TAG, "Qb Wake Up Wait ....");
				while (!checkGroupWakeUpCheck()) {
					if (DEBUG) Log.d(TAG, "Sleeping  ....");
					try {
						Thread.sleep(500);
					} catch (java.lang.InterruptedException e) {
					}
				}
				if (DEBUG) Log.d(TAG, "raise Hand! all class ");

				if (DEBUG) Log.d(TAG, "***");
				if (DEBUG) Log.d(TAG, "***");
				if (DEBUG) Log.d(TAG, "* " + next);
				if (DEBUG) Log.d(TAG, "***");
				if (DEBUG) Log.d(TAG, "***");

				if (mode.equals("3")) {
					localSetQbState(QbAndroidManager.WS_SNAPSHOT_END);
				} else if (mode.equals("4")) {
					localSetQbState(QbAndroidManager.WS_STAND_UP);
				} else {
					localSetQbState(QbAndroidManager.WS_NORMAL_BOOT);
				}

				if (DEBUG) Log.d(TAG, "AudioManager reloadAudioSettings Start");
				AudioManager mAudioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
				mAudioManager.reloadAudioSettings();
				if (DEBUG) Log.d(TAG, "AudioManager reloadAudioSettings End");

				if(next != null) {
					Intent next_intent = new Intent(next);
		                    context.sendBroadcast(next_intent);
				}

                           /*---do not reload wallpaper for moke---*/
				/*wm = (WallpaperManager) mContext.getSystemService(Service.WALLPAPER_SERVICE);
				mWallpaperInfo = wm.getWallpaperInfo();
				checkWallpaperXML();*/
				//onPostExecute()
		             return 0;
		    }

			protected void onPostExecute(Integer result) {
				if (DEBUG) Log.d(TAG + ":TaskWakeUp", "Exit onPostExecute");
		    }
		}

		private void checkWallpaperXML() {


			Log.d(TAG, "Process.myUid: " + Process.myUid());
			Log.d(TAG, "UserHandle.USER_OWNER: " + UserHandle.USER_OWNER);
			final String base =
				Environment.getDataDirectory()
				+ "/system/users"
				+ "/" + UserHandle.USER_OWNER + "/"
				+ "wallpaper_info.xml";
			GetWallpaperXML mGetWallpaperXML = new GetWallpaperXML(base);
			changeType = checkWallpaper(mGetWallpaperXML, mWallpaperInfo);


			switch (changeType) {
			case REFRESH:
				if (DEBUG) Log.d(TAG, "CHANGE_REFRESH.");
				updateWallpaper2();
				break;
			case WALLPAPER_CLASS:
				if (DEBUG) Log.d(TAG, "GetWallpaperXML:Changing the wallpaper !!");

				String component = mGetWallpaperXML.getComponent();
				ComponentName mComponentName;

				if (component == null || component.isEmpty() ) {
					mComponentName = new ComponentName("com.android.systemui", "com.android.systemui.ImageWallpaper");
				} else {
					mComponentName = android.content.ComponentName.unflattenFromString(component);
				}

				if (DEBUG) Log.d(TAG, "GetWallpaperXML"+ "\n" +
					"  getClassName():" + mComponentName.getClassName() + "\n" +
					"  getPackageName():" + mComponentName.getPackageName() + "\n" +
					"  getShortClassName():" + mComponentName.getShortClassName());

				changeWallPaper2(mComponentName);
				break;
			default:
				break;
			}
		}

		private void refreshSettingsProvider() {

			if (DEBUG) Log.d(TAG, "SettingsProvider refresh.");
			ContentResolver cr = mContext.getContentResolver();

			String request = null;
			Bundle args = null;

			if (DEBUG) Log.d(TAG, "mes(1):" + Settings.CALL_METHOD_REFRESH);

			String mes = Settings.System.getString(cr, Settings.CALL_METHOD_REFRESH);

			if (DEBUG) Log.d(TAG, "mes:" + mes);

			if (mes == null) {
				mes = Settings.CALL_METHOD_REFRESH;
			}

			if (DEBUG) Log.d(TAG, "mes:" + mes);

			Uri mUri = Uri.parse("content://settings");

			cr.call(mUri, mes, request, args);
                    //getContentResolver().refresh(CONTENT_URI);
                    //Intent intent = new Intent(Intent.ACTION_QB_SETTINGS_REFRESH);
                    //intent.putExtra("broadcastTest", "ブロードキャスト！！");
                    //mContext.sendBroadcast(intent);

		}

		private void stopSettingsProvider() {

			if (DEBUG) Log.d(TAG, "SettingsProvider stop.");

			ContentResolver cr = mContext.getContentResolver();

			String request = null;
			Bundle args = null;

			if (DEBUG) Log.d(TAG, "mes(1):" + Settings.CALL_METHOD_STOP);

			String mes = Settings.System.getString(cr, Settings.CALL_METHOD_STOP);

			if (DEBUG) Log.d(TAG, "mes:" + mes);

			if (mes == null) {
				mes = Settings.CALL_METHOD_STOP;
			}

			if (DEBUG) Log.d(TAG, "mes:" + mes);

			Uri mUri = Uri.parse("content://settings");

			cr.call(mUri, mes, request, args);

		}


		private CHANGE_TYPE checkWallpaper(GetWallpaperXML mGetWallpaperXML, WallpaperInfo info) {

			if (DEBUG) Log.d(TAG, "checkWallpaper:checkWallpaper");

			String buf = "";

			String wallManager;
			String component = mGetWallpaperXML.getComponent();
			String name = mGetWallpaperXML.getName();

			if (DEBUG) {
				buf = "checkWallpaper:component:" + component + "\n";
				buf += "checkWallpaper:name:" + name;
				Log.d(TAG, buf);
			}

			if (info == null) {

				if (DEBUG) Log.d(TAG, "checkWallpaper:WallpaperManager is Null.");

				wallManager = "res:com.android.launcher:drawable/wallpaper_outofthebox";

				if (component == null || component.isEmpty())
                           {
					return CHANGE_TYPE.REFRESH;
				}
                           else
				{
					return CHANGE_TYPE.WALLPAPER_CLASS;
				}

			} else {

				ComponentName mComponentName = info.getComponent();
				wallManager = mComponentName.getPackageName() + "/" + mComponentName.getShortClassName();

				if (DEBUG) {
					buf = "checkWallpaper:getPackageName:" + info.getPackageName() + "\n";
					buf += "checkWallpaper:getServiceName:" + info.getServiceName() + "\n";
					buf += "checkWallpaper:getSettingsActivity:" + info.getSettingsActivity() + "\n";
					buf += "checkWallpaper:getComponent:" + info.getComponent() + "\n";
					buf += "checkWallpaper:getServiceInfo:" + info.getServiceInfo() + "\n";
					buf += "checkWallpaper:ComponentName#getClassName:" + mComponentName.getClassName() + "\n";
					buf += "checkWallpaper:ComponentName#getPackageName:" + mComponentName.getPackageName() + "\n";
					buf += "checkWallpaper:ComponentName#getShortClassName:" + mComponentName.getShortClassName() + "\n";
					buf += "checkWallpaper:wallManager:" + wallManager + "\n";
					buf += "checkWallpaper:wallXML:" + component;
					Log.d(TAG, buf);
				}

				if (wallManager.equals(component)) {
					return CHANGE_TYPE.NO_CHANGE;
				} else {
					return CHANGE_TYPE.WALLPAPER_CLASS;
				}

			}
		}

		private void changeWallPaper2(ComponentName mComponentName) {
			if (DEBUG) Log.d(TAG, "changeWallPaper2:Start methoad.");
			try {
				wm.getIWallpaperManager().setWallpaperComponent(mComponentName);
			} catch (RemoteException e) {
				Toast.makeText(mContext, "RemoteException", Toast.LENGTH_SHORT).show();
				e.printStackTrace();
			} catch (RuntimeException e) {
				Toast.makeText(mContext, "RuntimeException", Toast.LENGTH_SHORT).show();
				e.printStackTrace();
			}
		}

		private void updateWallpaper2() {
			if (DEBUG) Log.d(TAG, "Call startWatching2");
			try {
				wm.getIWallpaperManager().refleshWallpaper();
			} catch (RemoteException e) {
				if (DEBUG) Log.d(TAG, e.toString());
				e.printStackTrace();
			} catch (RuntimeException e) {
				if (DEBUG) Log.d(TAG, e.toString());
				e.printStackTrace();
			}
		}

	}

	private class GetWallpaperXML {

		private static final String TAG = "QbAndroid - GetWallpaperXML";
		static final boolean DEBUG = false;
		private String xmlFilename;

		private Map<String, String> info = new HashMap<String, String>();

		private final String[] list = { "width", "height", "name", "component"} ;

		public GetWallpaperXML(String filename) {
			xmlFilename = filename;
			getXMLInfo();
		}

		public String getName() {
			return info.get("name");
		}


		public String getComponent() {
			return info.get("component");
		}

		private void getXMLInfo() {
			info.clear();
			XmlPullParserFactory factory;
			if (DEBUG) Log.d(TAG, "Start!");
			try {
				factory = XmlPullParserFactory.newInstance();
				factory.setNamespaceAware(true);
				XmlPullParser xpp = factory.newPullParser();
				File mFile = new File(xmlFilename);
				if (mFile.exists()) {
					InputStream inputStream = new FileInputStream(mFile);
					try {
						xpp.setInput(inputStream ,"UTF-8");

						int eventType = xpp.getEventType();

						while (eventType != XmlPullParser.END_DOCUMENT) {
							if(eventType == XmlPullParser.START_TAG) {
								if (xpp.getName().equals("wp")) {
									for (String a: list) {
										String b = xpp.getAttributeValue(null, a);
										if (DEBUG) Log.d(TAG, "key:" + a + " value:" + b);
										info.put(a, b);
									}
								}
							}
							eventType = xpp.next();
						}
					} finally {
						if (inputStream != null) {
							inputStream.close();
						}
					}
				} else {
					throw new FileNotFoundException(xmlFilename);
				}
				if (DEBUG) Log.d(TAG, "End document");

			} catch (XmlPullParserException e) {
				e.printStackTrace();
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}
    @Override
    public boolean checkFlag()
    {
        return checkFlagWait();
    }

    private native boolean checkFlagWait();

    @Override
    public boolean checkBoot()
    {
        return checkBootWait();
    }

    private native boolean checkBootWait();

    @Override
    public void setFlag(boolean flag)
    {
        setFlagWait(flag);
    }

    private native void setFlagWait(boolean flag);

    @Override
    public void setBoot(boolean flag)
    {
        setBootWait(flag);
    }

    private native void setBootWait(boolean flag);

    @Override
    public void doQb()
    {
        doQbWait();
    }

    private native int doQbWait();

    @Override
    public void doBoot()
    {
        doBootWait();
    }

    private native int doBootWait();

    @Override
    public void doReload(boolean flag)
    {
        doReloadWait(flag);
    }

    private native void doReloadWait(boolean flag);

    @Override
    public void setQbEnable(boolean flag)
    {
        setQbEnableWait(flag);
    }

    private native void setQbEnableWait(boolean flag);
}
