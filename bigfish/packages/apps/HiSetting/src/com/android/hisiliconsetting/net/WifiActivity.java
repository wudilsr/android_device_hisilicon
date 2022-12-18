package com.android.hisiliconsetting.net;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.NetworkInfo;
import android.net.NetworkInfo.DetailedState;
import android.net.wifi.ScanResult;
import android.net.wifi.SupplicantState;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnFocusChangeListener;
import android.view.View.OnKeyListener;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;
import java.util.Timer;
import java.util.TimerTask;

import com.android.hisiliconsetting.CommonDialog;
import com.android.hisiliconsetting.ProDialog;
import com.android.hisiliconsetting.R;
import com.android.hisiliconsetting.net.WifiAdapter.ViewHolder;
import com.android.hisiliconsetting.net.WifiAddDialog.OnCallback;
import android.net.ethernet.EthernetManager;
import static android.net.wifi.WifiConfiguration.INVALID_NETWORK_ID;

public class WifiActivity extends Activity{
    private String TAG = "WifiActivity";
    public static final int ERROR_NOACCOUNT = 2;
    public static final int ERROR_NOOPEN = 1;
    public static final int ERROR_NORESPONSE = -1;
    public static final int SUCCESS = 0;
    private static final int REFRESH_ITEM = 0;
    private static final int CONNECT_ERROR = 1;
    private static final int FRESH_LIST = 2;
    private static final int CONNECT_TIME_OUT = 3;
    private static final int REFRESH_ITEM_VIEW = 4;
    private static final int SCAN_TIME_OUT = 5;
    private static final int WAITING_TIME = 25000;
    private static final int WIFI_RESCAN_INTERVAL_MS = 10 * 1000;
    private IntentFilter mFilter;
    private WifiInfo mCurInfo;
    private List<WifiConfiguration> mConfigList = new ArrayList<WifiConfiguration>();
    private BroadcastReceiver mReceiver;
    private WifiAdapter mWifiListAdapter;
    private WifiManager mWifiManager;
    private List<WifiAp> mDataLists = new ArrayList<WifiAp>();
    private ListView mWifilist;
    private TextView mWifiError = null;
    private RelativeLayout mEditLayout = null;
    private RelativeLayout mPasswordLayout = null;
    private LinearLayout mWifiInfoLayout = null;
    private TextView mCurInfo_tx = null;
    private ImageView mCurInfo_signal = null;
    private EditText mPassword_ed = null;
    private Button mConnect_bn = null;
    private WifiAp mCurWifi = null;
    public static boolean mIsConnectting = false;
    private boolean mWifiEnable = false;
    private IntentFilter mIntentFilter;
    private int mWifiState = WifiManager.WIFI_STATE_UNKNOWN;
    private Timer mtimer = null;
    private ViewHolder mCurItemview = null;
    private int index = -1;
    private ProDialog mProdialog = null;
    private Scanner mscanner = null;
    private void handleEvent(Context paramContext, Intent paramIntent){
        String str = paramIntent.getAction();
        //Log.i(TAG, str);
        if (str.equals("android.net.wifi.SCAN_RESULTS"))
        {
        //Log.i(TAG, "android.net.wifi.SCAN_RESULTS = "+mIsConnectting);
        if(mIsConnectting){
        return;
        }else{
        mhander.sendEmptyMessage(FRESH_LIST);
        }
        }
        if (str.equals("android.net.wifi.STATE_CHANGE")){
        if(mDataLists.size()>0){
        Message msg = new Message();
        msg.what = REFRESH_ITEM;
        msg.obj = paramIntent;
        mhander.sendMessage(msg);
        }

        }
        if(str.equals("android.net.wifi.supplicant.STATE_CHANGE")){
        if(mDataLists.size()>0){
        Message msg = new Message();
        msg.what = CONNECT_ERROR;
        msg.obj = paramIntent;
        mhander.sendMessage(msg);
        }
        }

    }
    private Handler mhander = new Handler(){
      public void handleMessage(Message msg) {
        switch (msg.what) {
        case REFRESH_ITEM:
        Log.i(TAG, "handleMessage--REFRESH_ITEM");
        Intent intent = (Intent) msg.obj;
        NetworkInfo.DetailedState localDetailedState = ((NetworkInfo)intent.getParcelableExtra("networkInfo")).getDetailedState();
        Log.i(TAG, "localDetailedState--="+localDetailedState);
        if(localDetailedState==DetailedState.CONNECTED){
        mIsConnectting = false;
        cancelTimer();
        updateWifiState(localDetailedState);
        mscanner.resume();
        }else if(localDetailedState==DetailedState.DISCONNECTED){
        }
        break;
        case CONNECT_ERROR:

        break;
        case FRESH_LIST:
         refreshWifiList();
        break;
        case CONNECT_TIME_OUT:
        Log.i(TAG, "connect time out");
          mscanner.resume();
          mIsConnectting = false;
          cancelTimer();
          if(mCurInfo!=null)
          mWifiManager.disableNetwork(mCurInfo.getNetworkId());
          updateWifiState(NetworkInfo.DetailedState.DISCONNECTED);
        break;
        case SCAN_TIME_OUT:
        if(mProdialog!=null){
        //mWifiManager.setWifiEnabled(false);
        mProdialog.Dismiss();
        if(mDataLists.size()==0){
            mWifiError.setVisibility(View.VISIBLE);
            mscanner.stopScan();
        }
        }
        break;
        case REFRESH_ITEM_VIEW:
        DetailedState state = (DetailedState)msg.obj;
        Log.i(TAG, "REFRESH_ITEM_VIEW="+state);
        if(mCurItemview!=null)
        mCurItemview.isConnect.setText("");
        if(index<0){
        mCurInfo = mWifiManager.getConnectionInfo();
           Log.i(TAG, "REFRESH_ITEM_VIEW mCurInfo="+mCurInfo.getSSID());
           if(mDataLists.size()>0){
         for (int i = 0; i < mDataLists.size(); i++) {
        String ssid = WifiAp.removeDoubleQuotes(mCurInfo.getSSID());
        if(ssid.equals(mDataLists.get(i).getSsid())){
        index = i;
        break;
        }
        }
       }
       }
        if(mWifilist.getChildAt(index)==null)
            return;
        mCurItemview = (ViewHolder)mWifilist.getChildAt(index).getTag();
            if(state==DetailedState.CONNECTED){
            mCurItemview.isConnect.setText(R.string.wifi_connected);
            }else if(state==DetailedState.DISCONNECTED){
            mCurItemview.isConnect.setText(R.string.wifi_connect_fail);
            }else if(state==DetailedState.CONNECTING){
            mCurItemview.isConnect.setText(R.string.wifi_connecting);
            }
        break;
        default:
        break;
        }
      }
    };
    private void refreshWifiList()
    {
        if(mWifiManager.getScanResults()!=null&&mWifiManager.getScanResults().size()>0){
            mProdialog.Dismiss();
            cancelTimer();
            mWifiError.setVisibility(View.INVISIBLE);
        }
        ScanFiltrate(mWifiManager.getScanResults());
        if(mDataLists.size()>0){
        mWifiListAdapter = new WifiAdapter(this,mDataLists, mWifiManager);
        mWifilist.setAdapter(mWifiListAdapter);
        mWifiListAdapter.notifyDataSetChanged();
        mWifiError.setVisibility(View.INVISIBLE);
        }else{
            if(mWifiListAdapter!=null){
                mWifiListAdapter.notifyDataSetChanged();
            }
        }
    }
    private void ScanFiltrate(List<ScanResult> list){
            mDataLists.clear();
            /** Lookup table to more quickly update AccessPoints by only considering objects with the
             * correct SSID.  Maps SSID -> List of AccessPoints with the given SSID.  */
            HashMap<String, WifiAp> apMap = new HashMap<String, WifiAp>();
            final List<WifiConfiguration> configs = mWifiManager.getConfiguredNetworks();
            if (configs != null) {
                for (WifiConfiguration config : configs) {
                    config.SSID = WifiAp.removeDoubleQuotes(config.SSID);
                   if(!apMap.containsKey(config.SSID)) {
                         WifiAp accessPoint = new WifiAp(config);
                         mDataLists.add(accessPoint);
                         apMap.put(accessPoint.ssid, accessPoint);
                    }
                }
            }
            final List<ScanResult> results = mWifiManager.getScanResults();
            if (results != null) {
                for (ScanResult result : results) {
                    if (result.SSID == null || result.SSID.length() == 0 ||
                            result.capabilities.contains("[IBSS]")) {
                        continue;
                    }
                    boolean found = false;
                    if (apMap.containsKey(result.SSID)) {
                        WifiAp tem = apMap.get(result.SSID);
                        apMap.remove(result.SSID);
                        apMap.put(result.SSID, UpdateApState(tem, result));
                        found = true;
                    }
                    if (!found) {
                        WifiAp accessPoint = new WifiAp(result);
                        mDataLists.add(accessPoint);
                        apMap.put(accessPoint.ssid, accessPoint);
                    }
                }
            }
            MoveToTop();
    }
    private WifiAp UpdateApState(WifiAp oldap,ScanResult newap){
        WifiAp temap = oldap;
        temap.mRssi = newap.level;
        return temap;
    }
    private void scanWifi()
    {
        mscanner.startScan();
        startTimer();

    }
    private void wifiMessage()
    {
        mFilter = new IntentFilter();
        mFilter.addAction("android.net.wifi.WIFI_STATE_CHANGED");
        mFilter.addAction("android.net.wifi.SCAN_RESULTS");
        mFilter.addAction("android.net.wifi.NETWORK_IDS_CHANGED");
        mFilter.addAction("android.net.wifi.supplicant.STATE_CHANGE");
        mFilter.addAction("android.net.wifi.STATE_CHANGE");
        mFilter.addAction("android.net.wifi.RSSI_CHANGED");
        mReceiver = new BroadcastReceiver()
        {
        public void onReceive(Context paramContext, Intent paramIntent)
        {
        handleEvent(paramContext, paramIntent);
        }
        };
    }
    protected void onCreate(Bundle paramBundle)
    {
        super.onCreate(paramBundle);
        setContentView(R.layout.wifi_set_main);
        mWifiManager = ((WifiManager)getSystemService(Context.WIFI_SERVICE));
        mWifiEnable = mWifiManager.isWifiEnabled();
        mWifiState = mWifiManager.getWifiState();
        mWifiError = (TextView)findViewById(R.id.wifi_unenable);
        mProdialog = new ProDialog(this,android.R.style.Theme_Translucent_NoTitleBar_Fullscreen);
        mProdialog.SetShowMsg(getResources().getString(R.string.wifi_progress));
        mProdialog.Dismiss();
        Log.i(TAG, "mWifiState=" +mWifiState);
        Log.i(TAG, "mWifiEnable=" +mWifiEnable);
        if(!mWifiEnable){
        mWifiManager.setWifiEnabled(true);
        }
        mscanner = new Scanner();
        setView();

    }
    private void ShowForgetDialog(final WifiAp AccessPoint,final Boolean isconnect){
        Log.i(TAG, "ShowForgetDialog AccessPoint netid=" +AccessPoint.networkId);
        CommonDialog dialog = new CommonDialog(this,android.R.style.Theme_Translucent_NoTitleBar_Fullscreen, new CommonDialog.OnCallback() {
			@Override
			public void OkcallBack() {
				// TODO Auto-generated method stub
				if(isconnect){
					Forget(AccessPoint);
				}else{
					ReConnect(AccessPoint);
				}
			}
			@Override
			public void CancelcallBack() {
				// TODO Auto-generated method stub
			}
			@Override
			public void MidcallBack() {
				// TODO Auto-generated method stub
				Forget(AccessPoint);
			}
		});
        dialog.show();
        dialog.SetTitle(AccessPoint.getSsid());
        dialog.SetText(getResources().getString(R.string.wifi_forget_text));
        dialog.SetCancleText(getResources().getString(R.string.wifi_forget_cancel));
        if(!isconnect){
            dialog.SetMidText(getResources().getString(R.string.wifi_forget_ok));
            dialog.SetPositiveText(getResources().getString(R.string.wifi_connect));
        }else{
            dialog.SetPositiveText(getResources().getString(R.string.wifi_forget_ok));
        }
    }
    private void Forget(WifiAp AccessPoint){
         if (AccessPoint.networkId == INVALID_NETWORK_ID) {
             return;
         }
         mWifiManager.forget(AccessPoint.networkId,null);
         refreshWifiList();
    }
    private void ReConnect(WifiAp AccessPoint){
      mscanner.stopScan();
      mIsConnectting = true;
      mWifiManager.disableNetwork(mCurInfo.getNetworkId());
      mWifiManager.enableNetwork(AccessPoint.networkId, true);
      MoveToTop();
      mWifiListAdapter.notifyDataSetChanged();
      mWifilist.setSelection(0);
      updateWifiState(DetailedState.CONNECTING);
      startTimer();
    }
    private AdapterView.OnItemClickListener listItemListener = new AdapterView.OnItemClickListener()
    {
        public void onItemClick(AdapterView<?> paramAdapterView, View paramView, int paramInt, long paramLong)
        {
            if(paramInt==mWifiListAdapter.getCount()){
                  showAddDialog();
            }else{
                index = paramInt;
                mCurWifi = (WifiAp)mWifiListAdapter.getItem(paramInt);
                mCurInfo = mWifiManager.getConnectionInfo();
                Log.i(TAG, "OnItemClickListener mCurInfo="+mCurInfo.getSSID());
                Log.i(TAG, "mCurWifi_id="+mCurWifi.ssid);
                String infoid = WifiUtil.ChangeSSID(mCurInfo.getSSID());
                if(mCurWifi.ssid.equals(infoid)){
                Log.i(TAG, "same wifi info");
                ShowForgetDialog(mCurWifi,true);
                }else{
                goConnect();
                }
            }
        }
    };
    private void showAddDialog(){
        WifiAddDialog dialog = new WifiAddDialog(this,android.R.style.Theme_Translucent_NoTitleBar_Fullscreen,new OnCallback(){
        @Override
        public void OkcallBack(WifiConfiguration config) {
        if(config!=null){
        Log.i(TAG, "showAddDialog to add");
        mscanner.stopScan();
        int net_id = mWifiManager.addNetwork(config);
        mWifiManager.enableNetwork(net_id, true);
        WifiAp ap = new WifiAp(config);
        mDataLists.add(ap);
        mWifiListAdapter.notifyDataSetChanged();
        index = mWifiListAdapter.getCount()-1;
        updateWifiState(DetailedState.CONNECTING);
        mIsConnectting = true;
        startTimer();
        }
        }
        });
        dialog.show();
    }
    private void ShowPasswordView(Boolean show,WifiAp result){
        if(show){
        mWifilist.setVisibility(View.INVISIBLE);
        mWifiInfoLayout.setVisibility(View.VISIBLE);
        mCurInfo_tx.setText(result.ssid);
        mCurInfo_signal.setBackgroundResource(WifiUtil.changeStregthtoDrawid(result.mRssi));
        mEditLayout.setVisibility(View.VISIBLE);
        mPasswordLayout.setBackgroundResource(R.drawable.input_focus_wide);
        mPassword_ed.requestFocus();
        mEditLayout.setOnKeyListener(new OnKeyListener() {
        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
        if(keyCode==KeyEvent.KEYCODE_BACK&&event.getAction()==KeyEvent.ACTION_DOWN){
        Log.i(TAG, "mEditLayout get back-key");
        mWifilist.setVisibility(View.VISIBLE);
        mWifiInfoLayout.setVisibility(View.INVISIBLE);
        mEditLayout.setVisibility(View.INVISIBLE);
        mPassword_ed.setText("");
        mPasswordLayout.setBackgroundResource(R.drawable.input_edit_selector);
        return true;
        }
        return false;
        }
        });
        }else{
        mWifilist.setVisibility(View.VISIBLE);
        mWifiInfoLayout.setVisibility(View.INVISIBLE);
        mEditLayout.setVisibility(View.INVISIBLE);
        mPassword_ed.setText("");
        mPasswordLayout.setBackgroundResource(R.drawable.input_edit_selector);
        }

    }
    @Override
    protected void onPause() {
        super.onPause();
        mscanner.stopScan();
    }
    @Override
    public void onBackPressed() {
      Log.i(TAG, "onBackPressed");
      if(mEditLayout.isShown()){
        mWifilist.setVisibility(View.VISIBLE);
          mWifiInfoLayout.setVisibility(View.INVISIBLE);
          mEditLayout.setVisibility(View.INVISIBLE);
          mPassword_ed.setText("");
          mPasswordLayout.setBackgroundResource(R.drawable.input_edit_selector);
      }else{
          if(mReceiver!=null){
              unregisterReceiver(mReceiver);
              mReceiver = null;
              finish();
          }
      }
    }

    protected void onResume()
    {
        super.onResume();
        Log.i(TAG, "onResume");
        final List<WifiConfiguration> configs = mWifiManager.getConfiguredNetworks();
        if(configs!=null&&configs.size()>0&&mDataLists.size()==0){
            for (WifiConfiguration config : configs) {
                  WifiAp accessPoint = new WifiAp(config);
                  mDataLists.add(accessPoint);
            }
            if(mDataLists.size()>0){
                MoveToTop();
                mWifiListAdapter = new WifiAdapter(this,mDataLists, mWifiManager);
                mWifilist.setAdapter(mWifiListAdapter);
                mWifiListAdapter.notifyDataSetChanged();
                mWifilist.setSelection(0);
                mWifiError.setVisibility(View.INVISIBLE);
           }
        }else{
            if(mDataLists.size()==0)
            mProdialog.Show();
        }
        scanWifi();
        index = -1;
        if(mReceiver==null){
             wifiMessage();
             registerReceiver(mReceiver, mFilter);
        }
        mIntentFilter = new IntentFilter(EthernetManager.ETHERNET_STATE_CHANGED_ACTION);
        mIntentFilter.addAction(EthernetManager.NETWORK_STATE_CHANGED_ACTION);
        this.registerReceiver(mEthSettingsReceiver, mIntentFilter);
    }
    protected void onStart()
    {
        super.onStart();
    }

    public void setView()
    {
        mWifiInfoLayout = (LinearLayout)findViewById(R.id.wifi_info_layout);
        mCurInfo_tx = (TextView)findViewById(R.id.wifi_info_title);
        mCurInfo_signal = (ImageView)findViewById(R.id.wifi_info_signal);
        mEditLayout = (RelativeLayout)findViewById(R.id.wifi_password_layout);
        mPasswordLayout = (RelativeLayout)findViewById(R.id.wifi_edit_layout);
        mPassword_ed = (EditText)findViewById(R.id.wifi_password_edit);
        mConnect_bn = (Button)findViewById(R.id.wifi_connect_btn);
        mConnect_bn.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick(View v) {
        // to connect wifi
        mscanner.stopScan();
        String password = mPassword_ed.getText().toString();
        int netid = 0;
        Log.i(TAG, "connectg has password="+password);
        mIsConnectting = true;
        WifiConfiguration config = WifiUtil.CreateWifiInfo(mCurWifi.ssid, password,mCurWifi.security);
        netid = mWifiManager.addNetwork(config);
        mDataLists.get(index).networkId = netid;
        Log.i(TAG, "connectg has netid="+netid);
        mWifiManager.enableNetwork(netid, true);
        mWifiManager.saveConfiguration();
        ShowPasswordView(false, null);
        startTimer();
        MoveToTop();
        mWifiListAdapter.notifyDataSetChanged();
        mWifilist.setSelection(0);
        updateWifiState(DetailedState.CONNECTING);
        }
        });
        mConnect_bn.setOnFocusChangeListener(new OnFocusChangeListener() {
        @Override
        public void onFocusChange(View v, boolean hasFocus) {
        if(hasFocus){
        mPasswordLayout.setBackgroundResource(R.drawable.input_normal_wide);
        }else{
        mPasswordLayout.setBackgroundResource(R.drawable.input_focus_wide);
        mPassword_ed.requestFocus();
        }
        }
        });
        mWifilist = (ListView)findViewById(R.id.wifi_info_list);
        mWifilist.setOnItemClickListener(listItemListener);
        addFootView();
    }
    private void addFootView(){
        View foot = LinearLayout.inflate(this, R.layout.wifi_info_item, null);
        ImageView add = (ImageView)foot.findViewById(R.id.wifi_item_lock);
        add.setBackgroundResource(R.drawable.icon_add_active);
        ImageView signal =(ImageView)foot.findViewById(R.id.wifi_item_signal);
        signal.setBackgroundResource(R.color.transparent);
        TextView add_tx = (TextView)foot.findViewById(R.id.wifi_item_title);
        add_tx.setText(R.string.wifi_add);
        mWifilist.addFooterView(foot);
    }
    private void goConnect(){
        mCurInfo = mWifiManager.getConnectionInfo();
        if(mCurWifi.security==0){
        //no password go to connect
        Log.i(TAG, "goConnect no pass");
        int netid = 0;
        mIsConnectting = true;
        mWifiManager.disableNetwork(mCurInfo.getNetworkId());
        WifiConfiguration config = WifiUtil.CreateWifiInfo(mCurWifi.ssid, null, mCurWifi.security);
        netid = mWifiManager.addNetwork(config);
        mDataLists.get(index).networkId = netid;
        Log.i(TAG, "connectg has netid="+netid);
        mWifiManager.enableNetwork(netid, true);
        MoveToTop();
        mWifiListAdapter.notifyDataSetChanged();
        mWifilist.setSelection(0);
        updateWifiState(DetailedState.CONNECTING);
        startTimer();
        mscanner.stopScan();
        }else{
        mConfigList = mWifiManager.getConfiguredNetworks();
        final WifiConfiguration config = WifiUtil.IsExsits(mCurWifi, mConfigList);
        if(config!=null){
        //Log.i(TAG, "goConnect has save");
        ShowForgetDialog(mCurWifi,false);
        }else{
        ShowPasswordView(true,mCurWifi);
        }
        }
    }
    private void startTimer(){
        if(mtimer==null){
        mtimer = new Timer();
        mtimer.schedule(new TimerTask() {
        @Override
        public void run() {
        if(mIsConnectting){
        mhander.sendEmptyMessage(CONNECT_TIME_OUT);
        }else{
        mhander.sendEmptyMessage(SCAN_TIME_OUT);
        }

        }
        }, WAITING_TIME);
        }
    }
    private void cancelTimer(){
        if(mtimer!=null){
        mtimer.cancel();
        mtimer = null;
        }
    }
    private class Scanner extends Handler {
        void resume() {
              removeMessages(0);
              sendEmptyMessageDelayed(0, WIFI_RESCAN_INTERVAL_MS);
        }
        void stopScan() {
            removeMessages(0);
        }
        void startScan() {
            removeMessages(0);
            sendEmptyMessage(0);
        }
        @Override
        public void handleMessage(Message message) {
            if (mWifiManager.startScan()){
                 sendEmptyMessageDelayed(0, WIFI_RESCAN_INTERVAL_MS);
            }
        }
    }
    public void updateWifiState(DetailedState paramDetailedState)
    {
        //Log.i(TAG, "updateWifiState ="+paramDetailedState);
        //Log.i(TAG, "mWifiListAdapter.OldIndex ="+mWifiListAdapter.OldIndex);
        if(mWifiListAdapter.OldIndex>=0){
        ViewHolder view = (ViewHolder)mWifilist.getChildAt(mWifiListAdapter.OldIndex).getTag();
        view.isConnect.setText("");
        mWifiListAdapter.OldIndex = -1;
        }
        Message msg = new Message();
        msg.what = REFRESH_ITEM_VIEW;
        msg.obj = paramDetailedState;
        mhander.sendMessage(msg);
        mscanner.resume();
    }
    private void MoveToTop(){
        String topap = "";
        int tem_index = 0;
        WifiAp tem_ap = null;
        WifiInfo mtemp = mWifiManager.getConnectionInfo();
        if(null != mtemp&&!mtemp.getSSID().equals("0x")){//has ap connected
            topap = WifiAp.removeDoubleQuotes(mtemp.getSSID());
            Log.i(TAG, "get top ap ssid is curinfo="+mtemp.getSSID());
        }else{
            if(mCurWifi!=null){
                topap = mCurWifi.ssid;
                Log.i(TAG, "get top ap ssid is curap="+topap);
            }
        }
        if(mDataLists.size()>0){
            for (int i = 0; i < mDataLists.size(); i++) {
				if(mDataLists.get(i).ssid.equals(topap)){
					tem_index = i;
					tem_ap = mDataLists.get(i);
					break;
				}
			}
            if(tem_index>0){
                index = 0;
                mDataLists.remove(tem_ap);
                mDataLists.add(0, tem_ap);
            }
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
        Log.i(TAG, " EVENT_PHY_LINK_UP  : " + message);
        Intent mintent = new Intent();
        mintent.setClass(WifiActivity.this, EthernetActivity.class);
        startActivity(mintent);
        finish();
        break;
        case EthernetManager.EVENT_PHY_LINK_DOWN:
        case EthernetManager.EVENT_DHCP_DISCONNECT_SUCCESSED:
        case EthernetManager.EVENT_STATIC_DISCONNECT_SUCCESSED:
        Log.i(TAG, " EVENT_PHY_LINK_DOWN  : " + message);
        break;
        default:
        break;
        }
        }
        }
    };
}
