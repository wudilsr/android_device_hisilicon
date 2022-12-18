package com.android.hisiliconsetting.secure;
import com.android.hisiliconsetting.R;

import android.R.animator;
import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.UserManager;
import android.provider.Settings;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class SecureActivity extends Activity{
    private String TAG = "SecureActivity";
    private TextView mInstallTx = null,mAdbTx = null;
    private ImageView mInstall_Bn_r = null,mInstall_Bn_l = null;
    private ImageView mAdb_Bn_r = null,mAdb_Bn_l = null;
    private RelativeLayout mInstall_layout = null,mAdb_layout = null;
    private Boolean mInstall_b = false;
    private Boolean mAdb_b = false;

    private final int FRESH_BUTTON_RIGHT = 1;
    private final int FRESH_BUTTON_LEFT = 2;
    private final int SET_ADB_DATA = 3;
    private final int SET_INSTALL_DATA = 4;
    private final int mDelayTime = 300;
    private enum SecureType{
        INSTALL,
        ADB,
    }
    private SecureType mType = SecureType.INSTALL;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.secure_set_main);
        InitUI();
    }
    @Override
    protected void onResume() {
        super.onResume();
        mInstall_b = isNonMarketAppsAllowed();
        Log.i(TAG, "mInstall_b="+mInstall_b);
        RefreshText(SecureType.INSTALL,mInstall_b,0);
        mAdb_b = getAdbEnable();
        Log.i(TAG, "mAdb_b="+mAdb_b);
        RefreshText(SecureType.ADB, mAdb_b, 0);
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
    private Handler mhandler = new Handler(){
        public void handleMessage(Message msg) {
        switch (msg.what) {
        case FRESH_BUTTON_RIGHT:
        if(mType==SecureType.INSTALL){
        mInstall_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }else{
        mAdb_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }
        break;
        case FRESH_BUTTON_LEFT:
                if(mType==SecureType.INSTALL){
        mInstall_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }else{
        mAdb_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }
        break;
        case SET_INSTALL_DATA:
        setNonMarketAppsAllowed(mInstall_b);
        break;
        case SET_ADB_DATA:
        setAdbEnable(mAdb_b);
        break;
        default:
        break;
        }
        }
    };
    private void InitUI(){
        mInstall_layout = (RelativeLayout)findViewById(R.id.secure_set_install);
        mInstall_layout.setOnKeyListener(new LayoutListener());
        mInstall_layout.setOnClickListener(new LayoutClick());
        mAdb_layout = (RelativeLayout)findViewById(R.id.secure_set_adb);
        mAdb_layout.setOnKeyListener(new LayoutListener());
        mInstall_Bn_r = (ImageView)findViewById(R.id.secure_install_right);
        mInstall_Bn_l = (ImageView)findViewById(R.id.secure_install_left);
        mAdb_Bn_r = (ImageView)findViewById(R.id.secure_adb_right);
        mAdb_Bn_l = (ImageView)findViewById(R.id.secure_adb_left);
        mInstallTx = (TextView)findViewById(R.id.secure_set_install_info);
        mAdbTx = (TextView)findViewById(R.id.secure_set_adb_info);
    }
    private class LayoutClick implements OnClickListener{
		@Override
		public void onClick(View v) {
			int id = v.getId();
	        switch (id) {
	        case R.id.secure_set_install:
	        mInstall_b = !mInstall_b;
	        mType = SecureType.INSTALL;
	        RefreshText(mType,mInstall_b,0);
	        mhandler.sendEmptyMessage(SET_INSTALL_DATA);
	        break;
	        case R.id.secure_set_adb:
	        mAdb_b = !mAdb_b;
	        mType = SecureType.ADB;
	        RefreshText(mType,mAdb_b,0);
	        mhandler.sendEmptyMessage(SET_ADB_DATA);
	        break;
	        default:
	        break;
	       }
		}
    }
    private class LayoutListener implements OnKeyListener{
        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
        if((keyCode==KeyEvent.KEYCODE_DPAD_LEFT||keyCode==KeyEvent.KEYCODE_DPAD_RIGHT)
        &&event.getAction()==KeyEvent.ACTION_DOWN){
        int id = v.getId();
        switch (id) {
        case R.id.secure_set_install:
        mInstall_b = !mInstall_b;
        mType = SecureType.INSTALL;
        RefreshText(mType,mInstall_b,keyCode);
        mhandler.sendEmptyMessage(SET_INSTALL_DATA);
        break;
        case R.id.secure_set_adb:
        mAdb_b = !mAdb_b;
        mType = SecureType.ADB;
        RefreshText(mType,mAdb_b,keyCode);
        mhandler.sendEmptyMessage(SET_ADB_DATA);
        break;
        default:
        break;
        }
        }
        return false;
        }

    }
    private void RefreshText(SecureType type,Boolean enable,int keycode){
        switch (type) {
        case INSTALL:
        if(enable){
        mInstallTx.setText(R.string.secure_allow);
        }else{
        mInstallTx.setText(R.string.secure_refuse);
        }
        if(keycode==KeyEvent.KEYCODE_DPAD_LEFT){
        mInstall_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_LEFT, mDelayTime);
        }else if(keycode==KeyEvent.KEYCODE_DPAD_RIGHT){
        mInstall_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_RIGHT, mDelayTime);
        }
        break;
        case ADB:
            if(enable){
        mAdbTx.setText(R.string.secure_allow);
        }else{
        mAdbTx.setText(R.string.secure_refuse);
        }
        if(keycode==KeyEvent.KEYCODE_DPAD_LEFT){
        mAdb_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_LEFT, mDelayTime);
        }else if(keycode==KeyEvent.KEYCODE_DPAD_RIGHT){
        mAdb_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_RIGHT, mDelayTime);
        }
        break;
        default:
        break;
        }
    }
    private boolean isNonMarketAppsAllowed() {
        return Settings.Global.getInt(getContentResolver(),Settings.Global.INSTALL_NON_MARKET_APPS, 0) > 0;
    }
    private void setNonMarketAppsAllowed(boolean enabled) {
        final UserManager um = (UserManager) SecureActivity.this.getSystemService(Context.USER_SERVICE);
        if (um.hasUserRestriction(UserManager.DISALLOW_INSTALL_UNKNOWN_SOURCES)) {
            return;
        }
        Settings.Global.putInt(getContentResolver(), Settings.Global.INSTALL_NON_MARKET_APPS,enabled ? 1 : 0);
    }
    private Boolean getAdbEnable(){
        Boolean enable = false;
        int ret = -1;
        ret = Settings.Global.getInt(getContentResolver(), Settings.Global.ADB_ENABLED, 0);
        if(ret==1)
        enable = true;
        return enable;
    }
    private void setAdbEnable(Boolean enable){
        if(enable){
        Settings.Global.putInt(getContentResolver(),Settings.Global.ADB_ENABLED, 1);
        }else{
        Settings.Global.putInt(getContentResolver(),Settings.Global.ADB_ENABLED, 0);
        }
    }
}
