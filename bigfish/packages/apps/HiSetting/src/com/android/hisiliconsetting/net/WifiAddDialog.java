package com.android.hisiliconsetting.net;

import com.android.hisiliconsetting.R;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiConfiguration.AuthAlgorithm;
import android.net.wifi.WifiConfiguration.KeyMgmt;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnFocusChangeListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
//import android.net.ProxyProperties;
//import android.net.wifi.WifiConfiguration.IpAssignment;
//import android.net.wifi.WifiConfiguration.ProxySettings;
public class WifiAddDialog extends Dialog{
	private String TAG = "WifiAddDialog";
    private OnCallback mCall = null;
    private Button mConfirmButton = null;
    private RelativeLayout mSSID_layout = null;
    private RelativeLayout mSecure_layout = null;
    private RelativeLayout mPassword_layout = null;
    private EditText mSSID_ed = null;
    private EditText mPassword_ed = null;
    private TextView mSecure_info = null;
    private ImageView mSecure_r,mSecure_l;
    private String[] mSecure_arry = null;
    private int FRESH_LEFT_ARROW = 1;
    private int FRESH_RIGHT_ARROW = 2;
    private final int mDelayTime = 300;
    private int mSecure_index = 0;
    private WifiConfiguration config = null;

    public static interface OnCallback {
        public void OkcallBack(WifiConfiguration config);
    }
    private Handler mhandler = new Handler(){
    	public void handleMessage(android.os.Message msg) {
    		if(msg.what==FRESH_LEFT_ARROW){
    			mSecure_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
    		}else if(msg.what==FRESH_RIGHT_ARROW){
    			mSecure_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
    		}
    	}
    };
    public WifiAddDialog(Context context,int theme,OnCallback call) {
        super(context, theme);
        mCall = call;
        mSecure_arry = context.getResources().getStringArray(R.array.wifi_add_secure_value);
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.wifi_add_net_view);
         
        mSSID_layout = (RelativeLayout)findViewById(R.id.wifi_add_ssid);
        mSSID_layout.setOnFocusChangeListener(new layoutFocus());
        mSSID_ed = (EditText)findViewById(R.id.wifi_add_ssid_edit);
        mSSID_ed.setOnFocusChangeListener(new layoutFocus());
        
        mSecure_layout = (RelativeLayout)findViewById(R.id.wifi_add_secure);
        mSecure_info = (TextView)findViewById(R.id.wifi_add_secure_info);
        mSecure_info.setText(mSecure_arry[mSecure_index]);
        mSecure_r = (ImageView)findViewById(R.id.wifi_add_right);
        mSecure_l = (ImageView)findViewById(R.id.wifi_add_left);
        mSecure_layout.setOnKeyListener(new LayoutListener());
        mSecure_layout.setOnClickListener(new SecureOnlick());
        
        mPassword_layout = (RelativeLayout)findViewById(R.id.wifi_add_password);
        mPassword_layout.setOnFocusChangeListener(new layoutFocus());
        mPassword_ed = (EditText)findViewById(R.id.wifi_add_password_edit);
        mPassword_ed.setOnFocusChangeListener(new layoutFocus());
        
        mConfirmButton = (Button)findViewById(R.id.wifi_add_confirm);
        mConfirmButton.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
        // TODO Auto-generated method stub
        	if(addAp()){
        		Log.i(TAG, "add is true");
        		if(mCall!=null)
        		mCall.OkcallBack(config);
        		dismiss();
        	}else{
        		Log.i(TAG, "add is false");
        	}
        }
        });
        HidePasswordLayout(true);
    }
    private class layoutFocus implements OnFocusChangeListener{
    	@Override
    	public void onFocusChange(View v, boolean hasFocus) {
    		if(hasFocus){
    			if(v.getId()==R.id.wifi_add_ssid){
    				Log.i(TAG, "mSSID_layout getfocuse");
    				mSSID_ed.requestFocus();
    				mSSID_layout.setBackgroundResource(R.drawable.input_focus_wide);
    				
    			}else if(v.getId()==R.id.wifi_add_password){
    				mPassword_layout.setBackgroundResource(R.drawable.input_focus_wide);
    				mPassword_ed.requestFocus();
    			}
    		}else{
    			if(v.getId()==R.id.wifi_add_ssid){
    				Log.i(TAG, "mSSID_layout lost focuse ");
    				
    			}else if(v.getId()==R.id.wifi_add_password){
    				
    			}else if(v.getId()==R.id.wifi_add_ssid_edit){
    				mSSID_layout.setBackgroundResource(R.drawable.input_normal_wide);
    				mSSID_layout.setBackgroundResource(R.drawable.input_wide_selector);
    			}else if(v.getId()==R.id.wifi_add_password_edit){
    				mPassword_layout.setBackgroundResource(R.drawable.input_normal_wide);
    				mPassword_layout.setBackgroundResource(R.drawable.input_wide_selector);
    			}
    		}
    	}
    }
    private class SecureOnlick implements android.view.View.OnClickListener{
		@Override
		public void onClick(View arg0) {
           if(mSecure_index<mSecure_arry.length-1){
                mSecure_index++;
           }else{
                mSecure_index=0;
            }
            if(mSecure_index==0){
                HidePasswordLayout(true);
            }else{
                HidePasswordLayout(false);
            }
            mSecure_info.setText(mSecure_arry[mSecure_index]);
		}
    }
    private class LayoutListener implements android.view.View.OnKeyListener{
        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
        if(event.getAction()==KeyEvent.ACTION_UP)
        return false;
        int id = v.getId();
        if(keyCode==KeyEvent.KEYCODE_DPAD_LEFT){
        	if(id==R.id.wifi_add_secure){
        		if(mSecure_index>0){
        			mSecure_index--;
        		}else{
        			mSecure_index=mSecure_arry.length-1;
        		}
        		if(mSecure_index==0){
            		HidePasswordLayout(true);
            	}else{
            		HidePasswordLayout(false);
            	}
        		mSecure_info.setText(mSecure_arry[mSecure_index]);
        		mSecure_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        		mhandler.removeMessages(FRESH_LEFT_ARROW);
        		mhandler.sendEmptyMessageDelayed(FRESH_LEFT_ARROW,mDelayTime);
        	}
        }
        if(keyCode==KeyEvent.KEYCODE_DPAD_RIGHT){
            if(id==R.id.wifi_add_secure){
            	if(mSecure_index<mSecure_arry.length-1){
        			mSecure_index++;
        		}else{
        			mSecure_index=0;
        		}
            	if(mSecure_index==0){
            		HidePasswordLayout(true);
            	}else{
            		HidePasswordLayout(false);
            	}
        		mSecure_info.setText(mSecure_arry[mSecure_index]);
        		mSecure_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        		mhandler.removeMessages(FRESH_RIGHT_ARROW);
        		mhandler.sendEmptyMessageDelayed(FRESH_RIGHT_ARROW,mDelayTime);
        	}
        }
        return false;
        }
    } 
    private void HidePasswordLayout(Boolean hide){
    	if(hide){
    		mSecure_layout.setNextFocusDownId(R.id.wifi_add_confirm);
    		mConfirmButton.setNextFocusUpId(R.id.wifi_add_secure);
    	}else{
    		mSecure_layout.setNextFocusDownId(R.id.wifi_add_password);
    		mConfirmButton.setNextFocusUpId(R.id.wifi_add_password);
    	}
    }
    private boolean addAp(){
    	
    	String SSID = mSSID_ed.getEditableText().toString();
    	String password = mPassword_ed.getEditableText().toString();
    	if(SSID.length()==0){
    		//toast 
    		return false;
    	}
    	config = new WifiConfiguration();
    	config.SSID = "\"" + SSID + "\"";
    	config.hiddenSSID = true;
    	switch (mSecure_index) {
    	case 0://no password
    		config.allowedKeyManagement.set(KeyMgmt.NONE);
    		return true;
    	case 1://WEP
    		config.allowedKeyManagement.set(KeyMgmt.NONE);
    		config.allowedAuthAlgorithms.set(AuthAlgorithm.OPEN);
    		config.allowedAuthAlgorithms.set(AuthAlgorithm.SHARED);
    		if (password.length() != 0) {
    			int length = password.length();
    			// WEP-40, WEP-104, and 256-bit WEP (WEP-232?)
    			if ((length == 10 || length == 26 || length == 58) &&
    					password.matches("[0-9A-Fa-f]*")) {
    				config.wepKeys[0] = password;
    			} else {
    				config.wepKeys[0] = '"' + password + '"';
    			}
    			return true;
    		}
    		break;
    	case 2:
    		config.allowedKeyManagement.set(KeyMgmt.WPA_PSK);
    		if (password.length() != 0) {
    			if (password.matches("[0-9A-Fa-f]{64}")) {
    				config.preSharedKey = password;
    			} else {
    				config.preSharedKey = '"' + password + '"';
    			}
    			return true;
    		}
    		break;
    	default:
    		break;
    	}
    	return false;
    }
}
