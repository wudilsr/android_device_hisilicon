package com.android.hisiliconsetting.normal;

import java.util.List;
import java.util.Locale;
import java.util.Random;

import com.android.hisiliconsetting.CommonDialog;
import com.android.hisiliconsetting.CommonDialog.OnCallback;
import com.android.hisiliconsetting.net.EthernetActivity;
import com.android.hisiliconsetting.R;
import com.hisilicon.android.netshare.NativeSamba;
import com.hisilicon.android.HiDisplayManager;
import android.app.Activity;
import android.app.ActivityManagerNative;
import android.app.IActivityManager;
import android.app.backup.BackupManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.provider.Settings;
import android.provider.Settings.Global;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnFocusChangeListener;
import android.view.View.OnKeyListener;
import android.view.inputmethod.InputMethodInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.os.SystemProperties;
import com.hisilicon.android.sdkinvoke.HiSdkinvoke;
import com.hisilicon.android.hisysmanager.HiSysManager;
public class NormalSetActivity extends Activity{
    private String TAG = "NormalSetActivity";
    public final static String SETRING = "hisetting";
    private final String DEFAULT_DEVICE_NAME = "Living Room 1";
    private final String KEY_DEVICE_NAME = "device_name";
    private TextView mLanguageTx = null,mSambaTx = null,mDevicesTx;
    private MarqueeText mInputTx = null;
    private ImageView mInput_Bn_r = null,mInput_Bn_l = null;
    private ImageView mLanguage_Bn_r = null,mLanguage_Bn_l = null;
    private ImageView mSamba_Bn_r = null,mSamba_Bn_l = null;
    private ImageView mDevices_Bn_r = null,mDevices_Bn_l = null;
    private RelativeLayout mInput_layout = null,mLanguge_layout = null,mSamba_layout = null,
                       mRecovery_layout = null,mSet_layout = null,mDevices_layout = null;
    private Boolean mChian_b = false;
    private Boolean mSamba_b = false;
    private final int FRESH_BUTTON_RIGHT = 1;
    private final int FRESH_BUTTON_LEFT = 2;
    private final int SET_INPUTMOTHE_DATA = 3;
    private final int SET_LANGUAGE_DATA = 4;
    private final int SET_SAMBA_DATA = 5;
    private final int SET_DEVICE_DATA = 6;
    private final int mDelayTime = 200;
    private List<InputMethodInfo> mInputMethods = null;
    private String[] mDeviceList = null;
    private InputMethodManager mInputManager = null;
    private int mInputIndex = 0;
    private int mInputCount = 0;
    private int mDeviceIndex = 0;
    private int mDeviceCount = 0;
    private String mNewInput = null;
    private String mOldInput = null;
    private final String EN = "en_US";
    private final String ZH = "zh";
    private NativeSamba mSamba = null;
    private HiDisplayManager mDisplay = null;
    private static final String DEIVCE_NAME_CHANGE_BROADCAST = "com.hisi.devicename.changed";
    private static final String dmrNameValue = "HiMediaRender";
    private static final String dmsNameValue = "HiMediaServer";
    private static final int default_bind_time = 4;
    public static final String BUTTON_CHANGE_PASS_KEY = "button_change_pass_key";
    public static final String KEY_ENABLE_PASSWORD = "password_enabled";
    public static final String BUTTON_GROUP_KEY = "group_edittext";
    public static final String KEY_SERVER_USER_MODE = "server_user_mode";
    public static final String KEY_WRITEABLE = "chkbox_writeable";
    static final String BLANK = "";
	static final String SPACE = " ";
	static final String ENTER = "\n";
	static final String SERVER_SHARE_MODE = "share";
	static final String SERVER_USER_MODE = "user";
	static final String SHARED_DIRECTORY = "/mnt";
	static final String SHARED_FILE_NAME = "share";
	static final String NET_BIOS_NAME = BLANK;
	static final String CAN_WRITE = "yes";
	static final String CAN_NOT_WRITE = "no";
	/*server user*/
	static final String SERVER_USER = "administrator";
	private static final String DEFAULT_WORK = "WORKGROUP";
    private static final String SAMBA_STATUS = "samba_status";
	/*default log row*/
	public static final int LOG_NUM = 225;
	/*hostname*/
	private String netBiosName = BLANK;
	/*shared file permissions*/
	private static final String FILE_PERMISSION = "0777";
	/*shared directory permissions*/
	private static final String DIRECTORY_PERMISSION = "0777";
	/*Available*/
	private static final String AVAIL = "yes";
	/*to browse*/
	private static final String BROWSE = "yes";
	/*can write*/
	private String nCanWrite = CAN_WRITE;
    private enum NormalType{
        INPUT,
        LANGUAGE,
        SAMBA,
        DEVICES,
        RECOVERY,
        SET,
    }
    private NormalType mType = NormalType.INPUT;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.normal_set_main);
        mInputManager = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
        mSamba = new NativeSamba();
        mDisplay = new HiDisplayManager();
        InitUI();
    }
    @Override
    protected void onResume() {
        super.onResume();
        mChian_b = isChianes();
        if(mChian_b){
        mLanguageTx.setText(R.string.normal_language_CN);
        }else{
        mLanguageTx.setText(R.string.normal_language_EN);
        }
        Log.i(TAG, "getSambaProcessState="+mSamba.getSambaProcessState());
        if(SystemProperties.get("persist.sys.samba.status","true").equals("false")){
            mSamba_b = false;
            mSambaTx.setText(R.string.normal_samba_off);
        }else{
            mSamba_b = true;
            mSambaTx.setText(R.string.normal_samba_on);
        }
        InitInput();
        InitDevices();
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
    private void InitDevices(){
        mDeviceList = getResources().getStringArray(R.array.device_name_entries_value);
        mDeviceCount = mDeviceList.length;
        String device = Settings.Global.getString(getContentResolver(), Global.DEVICE_NAME);
        if(device==null){
        StringBuffer sb = new StringBuffer();
        sb.append(DEFAULT_DEVICE_NAME).append("_").append(getEquipmentId().substring(8,12));
        device = sb.toString();

        }else{

        }
        for (int i = 0; i < mDeviceCount; i++) {
        StringBuffer sb = new StringBuffer();
        sb.append(mDeviceList[i]).append("_").append(getEquipmentId().substring(8,12));
        mDeviceList[i] = sb.toString();
        if(device.equals(mDeviceList[i])){
        mDeviceIndex = i;
        }
        }
        mDevicesTx.setText(device);
    }
    private void InitInput(){
        mInputMethods = mInputManager.getEnabledInputMethodList();
        mOldInput = Settings.Secure.getString(NormalSetActivity.this
        .getContentResolver(), Settings.Secure.DEFAULT_INPUT_METHOD);
        Log.i(TAG, "mOldInput ="+mOldInput);
        if(mInputMethods.size()>0){
        mInputCount = mInputMethods.size();
        for (int i = 0; i < mInputMethods.size(); i++) {
        Log.i(TAG, "mInputMethods="+i+" "+mInputMethods.get(i).getId()+" "+mInputMethods.get(i).getPackageName()+
        " "+mInputMethods.get(i).loadLabel(getPackageManager()));
        if(mOldInput.equals(mInputMethods.get(i).getId())){
        mInputIndex = i;
        }
        }
        }
        mInputTx.setText(mInputMethods.get(mInputIndex).loadLabel(getPackageManager()));

    }
    private void InitUI(){
        mInput_layout = (RelativeLayout)findViewById(R.id.normal_set_input);
        mInput_layout.setOnKeyListener(new LayoutListener());
        mInput_layout.setOnClickListener(new LayoutClick());

        mLanguge_layout = (RelativeLayout)findViewById(R.id.normal_language);
        mLanguge_layout.setOnKeyListener(new LayoutListener());
        mLanguge_layout.setOnClickListener(new LayoutClick());
        mSamba_layout = (RelativeLayout)findViewById(R.id.normal_samba);
        mSamba_layout.setOnKeyListener(new LayoutListener());
        mSamba_layout.setOnClickListener(new LayoutClick());
        mDevices_layout = (RelativeLayout)findViewById(R.id.normal_devices);
        mDevices_layout.setOnKeyListener(new LayoutListener());
        mDevices_layout.setOnClickListener(new LayoutClick());
        mRecovery_layout = (RelativeLayout)findViewById(R.id.normal_recovery);
        mRecovery_layout.setOnKeyListener(new LayoutListener());
        mRecovery_layout.setOnClickListener(new LayoutClick());

        mSet_layout = (RelativeLayout)findViewById(R.id.normal_set);
        mSet_layout.setOnKeyListener(new LayoutListener());
        mSet_layout.setOnClickListener(new LayoutClick());

        mInput_Bn_r = (ImageView)findViewById(R.id.normal_input_right);
        mInput_Bn_l = (ImageView)findViewById(R.id.normal_input_left);
        mLanguage_Bn_r = (ImageView)findViewById(R.id.normal_language_right);
        mLanguage_Bn_l = (ImageView)findViewById(R.id.normal_language_left);
        mSamba_Bn_r = (ImageView)findViewById(R.id.normal_samba_right);
        mSamba_Bn_l = (ImageView)findViewById(R.id.normal_samba_left);
        mDevices_Bn_r = (ImageView)findViewById(R.id.normal_devices_right);
        mDevices_Bn_l = (ImageView)findViewById(R.id.normal_devices_left);
        mInputTx = (MarqueeText)findViewById(R.id.normal_input_info);
        mLanguageTx = (TextView)findViewById(R.id.normal_language_info);
        mSambaTx = (TextView)findViewById(R.id.normal_samba_info);
        mDevicesTx = (TextView)findViewById(R.id.normal_devices_info);
        mInput_layout.setOnFocusChangeListener(new OnFocusChangeListener() {
			@Override
			public void onFocusChange(View arg0, boolean hasfocus) {
				// TODO Auto-generated method stub
				if(hasfocus){
					mInputTx.setMaquee(true);
					mInputTx.setText(mInputMethods.get(mInputIndex).loadLabel(getPackageManager()));
				}else{
					mInputTx.setMaquee(false);
					mInputTx.setText(mInputMethods.get(mInputIndex).loadLabel(getPackageManager()));
				}
			}
		});
    }
    private Handler mhandler = new Handler(){
        public void handleMessage(Message msg) {
        switch (msg.what) {
        case FRESH_BUTTON_RIGHT:
        if(mType==NormalType.INPUT){
        mInput_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }else if(mType==NormalType.LANGUAGE){
        mLanguage_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }else if(mType==NormalType.SAMBA){
        mSamba_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }else if(mType==NormalType.DEVICES){
        mDevices_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }
        break;
        case FRESH_BUTTON_LEFT:
        if(mType==NormalType.INPUT){
        mInput_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }else if(mType==NormalType.LANGUAGE){
        mLanguage_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }else if(mType==NormalType.SAMBA){
        mSamba_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }else if(mType==NormalType.DEVICES){
        mDevices_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }
        break;
        case SET_LANGUAGE_DATA:
        updateLocale(mChian_b);
        break;
        case SET_SAMBA_DATA:
        openSamba(mSamba_b);
        break;
        case SET_INPUTMOTHE_DATA:
        setInput(mInputIndex);
        break;
        case SET_DEVICE_DATA:
        setDevicesName(mDeviceList[mDeviceIndex]);
        break;
        default:
        break;
        }
        }
    };
    private class LayoutClick implements OnClickListener{
		@Override
		public void onClick(View arg0) {
			int id = arg0.getId();
			Log.i(TAG, "get onclick id = "+id);
	        switch (id) {
	        case R.id.normal_set_input:
	        mType = NormalType.INPUT;
	        OnClickRefreshText(mType);
	        break;
	        case R.id.normal_language:
	        mChian_b = !mChian_b;
	        mType = NormalType.LANGUAGE;
	        OnClickRefreshText(mType);
	        mhandler.sendEmptyMessage(SET_LANGUAGE_DATA);
	        break;
	        case R.id.normal_samba:
	        mSamba_b = !mSamba_b;
	        mType = NormalType.SAMBA;
	        OnClickRefreshText(mType);
	        mhandler.sendEmptyMessage(SET_SAMBA_DATA);
	        break;
	        case R.id.normal_devices:
	        mType = NormalType.DEVICES;
	        OnClickRefreshText(mType);
	        break;
	        case R.id.normal_recovery:
	        Log.i(TAG, "get onclick id = normal_recovery");
	        Intent resetIntent = new Intent(NormalSetActivity.this, ResetSetActivity.class);
		    startActivity(resetIntent);
	        break;
	        case R.id.normal_set:
	        Log.i(TAG, "get onclick id = normal_set");
	        PackageManager pm = getPackageManager();
            Intent settingIntent = pm.getLaunchIntentForPackage("com.android.settings");
            String name = settingIntent.getComponent().getClassName();
            Log.i(TAG, "setting--------"  + name);
            startActivity(settingIntent);
	        break;
	        default:
	        break;
	        }
		}
    }
    private class LayoutListener implements OnKeyListener{
        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
        if(event.getAction()==KeyEvent.ACTION_UP)
        return false;
        int id = v.getId();
        if(keyCode==KeyEvent.KEYCODE_DPAD_LEFT||keyCode==KeyEvent.KEYCODE_DPAD_RIGHT){
        switch (id) {
        case R.id.normal_set_input:
        mType = NormalType.INPUT;
        RefreshText(mType,keyCode);
        break;
        case R.id.normal_language:
        mChian_b = !mChian_b;
        mType = NormalType.LANGUAGE;
        RefreshText(mType,keyCode);
        mhandler.sendEmptyMessage(SET_LANGUAGE_DATA);
        break;
        case R.id.normal_samba:
        mSamba_b = !mSamba_b;
        mType = NormalType.SAMBA;
        RefreshText(mType,keyCode);
        mhandler.sendEmptyMessage(SET_SAMBA_DATA);
        break;
        case R.id.normal_devices:
        mType = NormalType.DEVICES;
        RefreshText(mType,keyCode);
        break;
        default:
        break;
        }
        }else if(keyCode==KeyEvent.KEYCODE_DPAD_CENTER||keyCode==KeyEvent.KEYCODE_ENTER){
        if(id==R.id.normal_recovery){
        Intent resetIntent = new Intent(NormalSetActivity.this, ResetSetActivity.class);
        startActivity(resetIntent);
        }else if(id==R.id.normal_set){
                    PackageManager pm = getPackageManager();
                    Intent settingIntent = pm.getLaunchIntentForPackage("com.android.settings");
                    String name = settingIntent.getComponent().getClassName();
                    Log.i(TAG, "setting--------"  + name);
                    startActivity(settingIntent);
        }
        }
        return false;
        }

    }

    private void RefreshText(NormalType type,int keycode){
        switch (keycode) {
        case KeyEvent.KEYCODE_DPAD_LEFT:
        switch (type) {
        case INPUT:
        if(mInputIndex>0){
        mInputIndex--;
        }else{
        mInputIndex = mInputCount -1;
        }
        mInputTx.setText(mInputMethods.get(mInputIndex).loadLabel(getPackageManager()));
        mInput_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        mhandler.sendEmptyMessage(SET_INPUTMOTHE_DATA);
        break;
        case LANGUAGE:
        if(mChian_b){
        mLanguageTx.setText(R.string.normal_language_CN);
        }else{
        mLanguageTx.setText(R.string.normal_language_EN);
        }
        mLanguage_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        break;
        case SAMBA:
        if(mSamba_b){
        mSambaTx.setText(R.string.normal_samba_on);
        }else{
        mSambaTx.setText(R.string.normal_samba_off);
        }
        mSamba_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        break;
        case DEVICES:
        if(mDeviceIndex>0){
        mDeviceIndex--;
        }else{
        mDeviceIndex = mDeviceCount -1;
        }
        mDevicesTx.setText(mDeviceList[mDeviceIndex]);
        mDevices_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        mhandler.sendEmptyMessage(SET_DEVICE_DATA);
        break;
        default:
        break;
        }
        mhandler.removeMessages(FRESH_BUTTON_LEFT);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_LEFT, mDelayTime);
        break;
        case KeyEvent.KEYCODE_DPAD_RIGHT:
        switch (type) {
        case INPUT:
        if(mInputIndex<mInputCount-1){
        mInputIndex++;
        }else{
        mInputIndex = 0;
        }
        mInputTx.setText(mInputMethods.get(mInputIndex).loadLabel(getPackageManager()));
        mInput_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        mhandler.sendEmptyMessage(SET_INPUTMOTHE_DATA);
        break;
        case LANGUAGE:
        if(mChian_b){
        mLanguageTx.setText(R.string.normal_language_CN);
        }else{
        mLanguageTx.setText(R.string.normal_language_EN);
        }
        mLanguage_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        break;
        case SAMBA:
        if(mSamba_b){
        mSambaTx.setText(R.string.normal_samba_on);
        }else{
        mSambaTx.setText(R.string.normal_samba_off);
        }
        mSamba_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        break;
        case DEVICES:
        if(mDeviceIndex<mDeviceCount-1){
        mDeviceIndex++;
        }else{
        mDeviceIndex = 0;
        }
        mDevicesTx.setText(mDeviceList[mDeviceIndex]);
        mDevices_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        mhandler.sendEmptyMessage(SET_DEVICE_DATA);
        break;
        default:
        break;
        }
        mhandler.removeMessages(FRESH_BUTTON_RIGHT);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_RIGHT, mDelayTime);
        break;
        default:
        break;
        }
    }
    private void OnClickRefreshText(NormalType type){
        switch (type) {
        case INPUT:
        if(mInputIndex>0){
        mInputIndex--;
        }else{
        mInputIndex = mInputCount -1;
        }
        mInputTx.setText(mInputMethods.get(mInputIndex).loadLabel(getPackageManager()));
        mhandler.sendEmptyMessage(SET_INPUTMOTHE_DATA);
        break;
        case LANGUAGE:
        if(mChian_b){
        mLanguageTx.setText(R.string.normal_language_CN);
        }else{
        mLanguageTx.setText(R.string.normal_language_EN);
        }
        break;
        case SAMBA:
        if(mSamba_b){
        mSambaTx.setText(R.string.normal_samba_on);
        }else{
        mSambaTx.setText(R.string.normal_samba_off);
        }
        break;
        case DEVICES:
        if(mDeviceIndex>0){
        mDeviceIndex--;
        }else{
        mDeviceIndex = mDeviceCount -1;
        }
        mDevicesTx.setText(mDeviceList[mDeviceIndex]);
        mhandler.sendEmptyMessage(SET_DEVICE_DATA);
        break;
        default:
        break;
        }
    }
    private void ShowRecoverDialog(){
        CommonDialog dialog = new CommonDialog(this, android.R.style.Theme_Translucent_NoTitleBar_Fullscreen, new OnCallback() {
        @Override
        public void OkcallBack() {
        // TODO Auto-generated method stub
                HiSysManager hisys = new HiSysManager();
                hisys.reset();
            NormalSetActivity.this.sendBroadcast(new Intent("android.intent.action.MASTER_CLEAR"));
        }

        @Override
        public void CancelcallBack() {
        // TODO Auto-generated method stub
        }

		@Override
		public void MidcallBack() {
			// TODO Auto-generated method stub
		}
        });
        dialog.show();
        dialog.SetText(getResources().getString(R.string.normal_recovery_hint));
    }
    private void setDevicesName(String hostName){

        Settings.Global.putString(this.getContentResolver(), Global.DEVICE_NAME, hostName);
        Intent intent = new Intent(DEIVCE_NAME_CHANGE_BROADCAST);
        this.sendBroadcast(intent);
    }

    public void updateLocale(Boolean chinese) {
        try {
        IActivityManager am = ActivityManagerNative.getDefault();
        Configuration config = am.getConfiguration();
        Locale locale = null;
        if(chinese){
        locale = new Locale(ZH);
        config.locale = Locale.SIMPLIFIED_CHINESE;
        }else{
        locale = new Locale(EN);
        config.locale = Locale.US;
        }
        Locale.setDefault(locale);
        am.updateConfiguration(config);
        BackupManager.dataChanged("com.android.providers.settings");
        } catch (RemoteException e) {
        // Intentionally left blank
        }
    }
  public Boolean isChianes(){
      Boolean ret = false;
      try {
          IActivityManager am = ActivityManagerNative.getDefault();
          Configuration config = am.getConfiguration();
          Log.i(TAG, "local="+config.locale.toString());
          if(config.locale.toString().equals("zh_CN"))
          ret= true;
      } catch (RemoteException e) {
      }
      return ret;
  }
  public void openSamba(Boolean open){
      if(open){
          if(mSamba.getSambaProcessState()==0){
              SharedPreferences p = NormalSetActivity.this.getSharedPreferences("com.android.settings_preferences", 0);
              String is_enable = p.getString("player", "1");
              SystemProperties.set("service.media.hiplayer", is_enable.equals("1") ? "true" : "false");
                  String password = p.getString(BUTTON_CHANGE_PASS_KEY, BLANK);
                  boolean check = p.getBoolean(KEY_ENABLE_PASSWORD, false);
                  mSamba.setUser(SERVER_USER);
                  if (check) {
                      mSamba.setPasswd(password);
                  }
                  String group = p.getString(BUTTON_GROUP_KEY, DEFAULT_WORK);
                  String server_info = p.getString(KEY_SERVER_USER_MODE, SERVER_SHARE_MODE);
                  mSamba.setGlobal(group, BLANK, server_info, LOG_NUM, BLANK);

                  boolean isWriteable = p.getBoolean(KEY_WRITEABLE, false);
                  if (isWriteable) {
                      nCanWrite = CAN_NOT_WRITE;
                  } else {
                      nCanWrite = CAN_WRITE;
                  }
                  /*Get all the configuration information*/
                  String heads = mSamba.getProperty();
                  /*Not share information,Increase,Have share information,read and write edit*/
                  if (null == heads) {
                      int fg1 = mSamba.addProperty(SHARED_FILE_NAME, SHARED_DIRECTORY,
                          FILE_PERMISSION, DIRECTORY_PERMISSION, AVAIL, BROWSE,
                          nCanWrite, SERVER_USER);
                  } else {
                      int fg2 = mSamba.editShare(SHARED_FILE_NAME, SHARED_DIRECTORY,
                          FILE_PERMISSION, DIRECTORY_PERMISSION, AVAIL, BROWSE,
                          nCanWrite, SERVER_USER);
                  }
          int ret = mSamba.startSambaServer();
          if(ret==0){
              ShowToast(R.string.normal_samba_start);
              SystemProperties.set("persist.sys.samba.status","true");
          }
          }

      }else{
          if(mSamba.getSambaProcessState()==1){
              int ret = mSamba.stopSambaServer();
              if(ret==0){
                  ShowToast(R.string.normal_samba_stop);
                  SystemProperties.set("persist.sys.samba.status","false");
              }
          }
      }
  }

  public void setInput(int index){
      mNewInput = mInputMethods.get(index).getId();
      if(!mNewInput.equals(mOldInput)){
          Settings.Secure.putString(NormalSetActivity.this.getContentResolver(),Settings.Secure.DEFAULT_INPUT_METHOD, mNewInput);
      }
  }
    public void ShowToast(int stringid){
        Toast toast = Toast.makeText(NormalSetActivity.this, getResources().getString(stringid), Toast.LENGTH_SHORT);
        toast.show();

    }
    private String getEquipmentId(){
        String equipmentId = SystemProperties.get("persist.sys.instructions.id");
		if(equipmentId==null||"".equals(equipmentId))
		{
			equipmentId="null";
		}
        return equipmentId;
    }
}
