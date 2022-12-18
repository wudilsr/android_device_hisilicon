package com.android.hisiliconsetting;

import com.android.hisiliconsetting.display.DisplaySetActivity;
import com.android.hisiliconsetting.net.EthernetActivity;
import com.android.hisiliconsetting.net.NetSetActivity;
import com.android.hisiliconsetting.net.WifiActivity;
import com.android.hisiliconsetting.normal.NormalSetActivity;
import com.android.hisiliconsetting.play.PlaySetActivity;
import com.android.hisiliconsetting.secure.SecureActivity;
import com.android.hisiliconsetting.upgrade.UpgradeMainActivity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.wifi.WifiManager;
import android.net.ConnectivityManager;
import android.net.ethernet.EthernetManager;
import android.net.NetworkInfo;
import android.os.SystemProperties;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageView;
import android.widget.RelativeLayout;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 *
 * @see SystemUiHider
 */
public class MainActivity extends Activity {
    private String TAG = "MainActivity";
    private RelativeLayout mNetSetLayout = null;
    private RelativeLayout mSecureLayout = null;
    private RelativeLayout mDisplayLayout = null;
    private RelativeLayout mNormalLayout = null;
    private RelativeLayout mPalyLayout = null;
    private RelativeLayout mUpgradeLayout = null;
    private WifiManager mwifi = null;
    private EthernetManager mEthManager = null;
    private ImageView mNetImage = null;
    private IntentFilter mIntentFilter = null;
    private ConnectivityManager mConnectivityManager;
    private boolean isWifi = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (isPortrait()) {
            setContentView(R.layout.activity_main_portrait);
        } else {
            setContentView(R.layout.activity_main);
        }
        mwifi = (WifiManager)getSystemService(Context.WIFI_SERVICE);
        mEthManager = (EthernetManager)getSystemService(Context.ETHERNET_SERVICE);
        mConnectivityManager = (ConnectivityManager)getSystemService(Context.CONNECTIVITY_SERVICE);
        mNetSetLayout = (RelativeLayout)findViewById(R.id.main_net_set);
        mNetImage = (ImageView)findViewById(R.id.main_net_image);
        mSecureLayout = (RelativeLayout)findViewById(R.id.main_secure_set);
        mDisplayLayout = (RelativeLayout)findViewById(R.id.main_display_set);
        mNormalLayout = (RelativeLayout)findViewById(R.id.main_normal_set);
        mPalyLayout = (RelativeLayout)findViewById(R.id.main_play_set);
        mUpgradeLayout = (RelativeLayout) findViewById(R.id.main_updata_set);
        mNetSetLayout.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick(View arg0) {
        Log.d(TAG, "onClick");
        Intent intent = new Intent();
        if(isWifi){
            intent.setClass(MainActivity.this, WifiActivity.class);
        }else{
            intent.setClass(MainActivity.this, EthernetActivity.class);
        }
        //intent.setClass(MainActivity.this, NetSetActivity.class);
        startActivity(intent);
        }
        });
        mSecureLayout.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick(View arg0) {
        Log.d(TAG, "onClick");
        Intent intent = new Intent();
        intent.setClass(MainActivity.this, SecureActivity.class);
        startActivity(intent);
        }
        });
        mDisplayLayout.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick(View arg0) {
        Log.d(TAG, "onClick");
        Intent intent = new Intent();
        intent.setClass(MainActivity.this, DisplaySetActivity.class);
        startActivity(intent);
        }
        });
        mNormalLayout.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick(View arg0) {
        Log.d(TAG, "onClick");
        Intent intent = new Intent();
        intent.setClass(MainActivity.this, NormalSetActivity.class);
        startActivity(intent);
        }
        });
        mPalyLayout.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick(View arg0) {
        Log.d(TAG, "onClick");
        Intent intent = new Intent();
        intent.setClass(MainActivity.this, PlaySetActivity.class);
        startActivity(intent);
        }
        });
        mUpgradeLayout.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick(View arg0) {
        Log.d(TAG, "onClick");
        Intent intent = new Intent();
        intent.setClass(MainActivity.this, UpgradeMainActivity.class);
        startActivity(intent);
        }
        });
    }
    protected void onDestroy() {
        // TODO Auto-generated method stub
        super.onDestroy();
        this.unregisterReceiver(mEthSettingsReceiver);
    }
    @Override
    protected void onResume() {
        super.onResume();
        int state = mEthManager.getEthernetState();
        Log.i(TAG, "EthernetManager state="+state);
        if(state!=EthernetManager.ETHERNET_STATE_ENABLED){
            mEthManager.enableEthernet(true);
        }
        if(!mwifi.isWifiEnabled()){
            mwifi.setWifiEnabled(true);
        }
        if(mIntentFilter==null){
            mIntentFilter = new IntentFilter(EthernetManager.ETHERNET_STATE_CHANGED_ACTION);
            mIntentFilter.addAction(EthernetManager.NETWORK_STATE_CHANGED_ACTION);
            this.registerReceiver(mEthSettingsReceiver, mIntentFilter);
        }
        NetworkInfo info =  mConnectivityManager.getNetworkInfo(ConnectivityManager.TYPE_ETHERNET);
        if(!info.isAvailable()){
            if(mwifi.isWifiEnabled()){
               isWifi = true;
               mNetImage.setBackgroundResource(R.drawable.icon_settings_wifi_normal_4);
            }else{
                isWifi = false;
                mNetImage.setBackgroundResource(R.drawable.icon_settings_wlan_normal_4);
            }
        }else{
        mNetImage.setBackgroundResource(R.drawable.icon_settings_wlan_normal_4);
        }

    }
    private BroadcastReceiver mEthSettingsReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
        if (intent.getAction().equals(
        EthernetManager.ETHERNET_STATE_CHANGED_ACTION)) {
        int message = intent.getIntExtra(EthernetManager.EXTRA_ETHERNET_STATE, -1);
        switch (message) {
        case EthernetManager.EVENT_PHY_LINK_UP:
        case EthernetManager.EVENT_DHCP_CONNECT_SUCCESSED:
        case EthernetManager.EVENT_STATIC_CONNECT_SUCCESSED:
        Log.i(TAG, "EthernetManager EVENT_PHY_LINK_UP");
         isWifi = false;
         mNetImage.setBackgroundResource(R.drawable.icon_settings_wlan_normal_4);
        break;
        case EthernetManager.EVENT_PHY_LINK_DOWN:
        case EthernetManager.EVENT_DHCP_DISCONNECT_SUCCESSED:
        case EthernetManager.EVENT_STATIC_DISCONNECT_SUCCESSED:
        Log.i(TAG, "EthernetManager EVENT_PHY_LINK_DOWN=");
        if(mwifi.isWifiEnabled()){
            isWifi = true;
            mNetImage.setBackgroundResource(R.drawable.icon_settings_wifi_normal_4);
        }else{
            isWifi = false;
            mNetImage.setBackgroundResource(R.drawable.icon_settings_wlan_normal_4);
        }
        break;
        default:
        break;
        }
        }
        }
    };

    private boolean isPortrait() {
        String screenOrientation = SystemProperties.get("persist.sys.screenorientation");
        if (screenOrientation != null) {
            if ("portrait".equals(screenOrientation)) {
                return true;
            }
        }
        return false;
    }

}
