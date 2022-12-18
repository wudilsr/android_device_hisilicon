package com.android.hisiliconsetting.net;

import java.net.Inet4Address;
import java.net.InetAddress;
import java.util.Iterator;

import com.android.hisiliconsetting.R;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.location.GpsStatus.NmeaListener;
import android.net.DhcpInfo;
import android.net.RouteInfo;
import android.net.LinkProperties;
import android.net.NetworkUtils;
import android.net.LinkAddress;
import android.net.ConnectivityManager;
import android.net.EthernetDataTracker;
import android.net.ethernet.EthernetManager;
import android.net.pppoe.PppoeManager;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.Toast;

public class EthernetActivity extends Activity{
    private String TAG = "EthernetActivity";
    private IntentFilter mIntentFilter;
    private Button mClose = null;
    private Button mOpen = null;
    private ImageView mSwitch = null;
    private Boolean m_Bauto = false;
    private Boolean m_Manual = false;
    private Boolean m_Enable = false;
    private RelativeLayout mAddressLayout = null;
    private RelativeLayout mMaskLayout = null;
    private RelativeLayout mGatewayLayout = null;
    private RelativeLayout mDnsLayout = null;
    private EditText mAddressEdit = null;
    private EditText mMaskEdit = null;
    private EditText mGatewayEdit = null;
    private EditText mDnsEdit = null;
    private Button mCommit = null;
    private EthernetManager mEthManager = null;
    private WifiManager mWifiManager = null;
    private PppoeManager mPppoeManager;
    private String mip,mMask,mGateway,mDns;
    private ConnectivityManager mConnectivityManager;
    private enum TypeLayout{
        ADDRESS,
        MASK,
        GATEWAY,
        DNS,
    }
    private TypeLayout mType = TypeLayout.ADDRESS;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.ethernet_set_main);
        mWifiManager = (WifiManager)getSystemService(Context.WIFI_SERVICE);
        mConnectivityManager = (ConnectivityManager)getSystemService(Context.CONNECTIVITY_SERVICE);
        mEthManager = (EthernetManager)getSystemService(Context.ETHERNET_SERVICE);
        mPppoeManager = (PppoeManager)getSystemService(Context.PPPOE_SERVICE);
        getEtherMode();
        InitUi();
    }
    private void InitUi(){
        mClose = (Button)findViewById(R.id.ethernet_auto_close);
        mClose.setOnKeyListener(new CloseListener());
        //mClose.setOnClickListener(new AutoClick());
        mOpen = (Button)findViewById(R.id.ethernet_auto_open);
        mOpen.setOnKeyListener(new OpenListener());
        //mOpen.setOnClickListener(new AutoClick());
        mSwitch = (ImageView)findViewById(R.id.ethernet_auto_switch);
        mSwitch.setOnClickListener(new AutoClick());
        mSwitch.requestFocus();
        mAddressLayout = (RelativeLayout)findViewById(R.id.ethernet_set_address);
        mAddressEdit = (EditText)findViewById(R.id.ethernet_set_address_edit);
        mAddressLayout.setOnKeyListener(new LayoutListener());
        mAddressLayout.setOnClickListener(new LayoutClick());
        mMaskLayout = (RelativeLayout)findViewById(R.id.ethernet_set_mask);
        mMaskEdit = (EditText)findViewById(R.id.ethernet_set_mask_edit);
        mMaskLayout.setOnKeyListener(new LayoutListener());

        mGatewayLayout = (RelativeLayout)findViewById(R.id.ethernet_set_gateway);
        mGatewayEdit = (EditText)findViewById(R.id.ethernet_set_gateway_edit);
        mGatewayLayout.setOnKeyListener(new LayoutListener());

        mDnsLayout = (RelativeLayout)findViewById(R.id.ethernet_set_DNS);
        mDnsEdit = (EditText)findViewById(R.id.ethernet_set_dns_edit);
        mDnsLayout.setOnKeyListener(new LayoutListener());

        mCommit = (Button)findViewById(R.id.ethernet_set_commit);
        mCommit.setOnClickListener(new CommitListener());
        //RefreshSwitch(m_Bauto);
        mAddressLayout.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick(View v) {
        mAddressLayout.setBackgroundResource(R.drawable.input_active);
        mAddressEdit.requestFocus();
        mAddressEdit.setSelection(mAddressEdit.getText().length());
        }
        });
        //ClearIP();
    }
    private class CommitListener implements OnClickListener{
        @Override
        public void onClick(View v) {
        mip = mAddressEdit.getText().toString();
        mMask = mMaskEdit.getText().toString();
        mGateway = mGatewayEdit.getText().toString();
        mDns = mDnsEdit.getText().toString();
        if(!WifiUtil.CheckIP(mip)){
        ShowToast(R.string.ethernet_ip_error);
        return;
        }else if(!WifiUtil.CheckIP(mMask)){
        ShowToast(R.string.ethernet_mask_error);
        return;
        }else if(!WifiUtil.CheckIP(mGateway)){
        ShowToast(R.string.ethernet_gateway_error);
        return;
        }else if(!WifiUtil.CheckIP(mDns)){
        ShowToast(R.string.ethernet_dns_error);
        return;
        }
        if(m_Enable){
        startStaticIP();
           m_Manual = true;
        }else{
        ShowToast(R.string.ethernet_commit_faile);
        }
        }
    }
    private class AutoClick implements OnClickListener{
		@Override
		public void onClick(View arg0) {
			m_Bauto=!m_Bauto;
			RefreshSwitch(m_Bauto);
			EnableEdit(m_Bauto);
		}
    }
    private class CloseListener implements OnKeyListener{
        @Override
        public boolean onKey(View arg0, int keycode, KeyEvent event) {
        if(keycode==KeyEvent.KEYCODE_DPAD_RIGHT&&event.getAction()==KeyEvent.ACTION_DOWN){
        m_Bauto = true;
        RefreshSwitch(m_Bauto);
        EnableEdit(m_Bauto);
        }
        return false;
        }
    }
    private class OpenListener implements OnKeyListener{
        @Override
        public boolean onKey(View arg0, int keycode, KeyEvent event) {
        if(keycode==KeyEvent.KEYCODE_DPAD_LEFT&&event.getAction()==KeyEvent.ACTION_DOWN){
        m_Bauto = false;
        RefreshSwitch(m_Bauto);
        EnableEdit(m_Bauto);
        }
        return false;
        }

    }
    private class LayoutClick implements OnClickListener{
		@Override
		public void onClick(View arg0) {
			new LayoutListener().onKey(arg0, KeyEvent.KEYCODE_DPAD_CENTER, new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_CENTER));
		}
    }
    private class LayoutListener implements OnKeyListener{
        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
        if((keyCode==KeyEvent.KEYCODE_ENTER||keyCode==KeyEvent.KEYCODE_DPAD_CENTER)&&event.getAction()==KeyEvent.ACTION_DOWN){
        int id = v.getId();
        switch (id) {
        case R.id.ethernet_set_address:
        mType = TypeLayout.ADDRESS;
        EditLayout(mAddressLayout,mAddressEdit,true);
        break;
        case R.id.ethernet_set_mask:
        mType = TypeLayout.MASK;
        EditLayout(mMaskLayout,mMaskEdit,true);
        break;
        case R.id.ethernet_set_gateway:
        mType = TypeLayout.GATEWAY;
        EditLayout(mGatewayLayout,mGatewayEdit,true);
        break;
        case R.id.ethernet_set_DNS:
        mType = TypeLayout.DNS;
        EditLayout(mDnsLayout,mDnsEdit,true);

        break;
        default:
        break;
        }
        }else if(keyCode==KeyEvent.KEYCODE_DPAD_UP||keyCode==KeyEvent.KEYCODE_DPAD_DOWN){
        Log.d(TAG, "layout get back");
        EnAbleEdit(mType);
        }
        return false;
        }

    }
    private void EnAbleEdit(TypeLayout type){
        Log.d(TAG, " get type="+type);
        switch (type) {
        case ADDRESS:
        EditLayout(mAddressLayout,mAddressEdit,false);
        break;
        case MASK:
        EditLayout(mMaskLayout,mMaskEdit,false);
        break;
        case GATEWAY:
        EditLayout(mGatewayLayout,mGatewayEdit,false);
        break;
        case DNS:
        EditLayout(mDnsLayout,mDnsEdit,false);
        break;

        default:
        break;
        }
    }
    private void EditLayout(RelativeLayout layout,EditText edit,Boolean enable){
        if(enable){
        layout.setBackgroundResource(R.drawable.input_active);
        edit.requestFocus();
        edit.setSelection(edit.getText().length());
        }else{
        if(!layout.hasFocus()){
        layout.setBackgroundResource(R.drawable.input_normal);
        layout.setBackgroundResource(R.drawable.input_edit_selector);
        }

        }

    }
    private void RefreshSwitch(boolean auto){
        if(auto){
        mOpen.requestFocus();
        mSwitch.setBackgroundResource(R.drawable.setting_second_switch_open);
        EnableEdit(m_Bauto);
        if(m_Enable){
        startDhcp();
        }else{
        ShowToast(R.string.ethernet_commit_faile);
        }
        }else{
        getStaticIP();
        mClose.requestFocus();
        mSwitch.setBackgroundResource(R.drawable.setting_second_switch_close);
        }
    }
    private void getEtherMode(){
        String mod = mEthManager.getEthernetMode();
        Log.i(TAG, "getEtherMode = "+mod);
        if (mod.equals(EthernetManager.ETHERNET_CONNECT_MODE_DHCP)){
        m_Bauto = true;
        }else{
        m_Manual = true;
        m_Bauto = false;
        }
        Log.i(TAG, "getEtherMode = "+m_Bauto);
    }
    private void EnableEdit(Boolean auto){
        if(auto){
        mAddressLayout.setEnabled(false);
        mMaskLayout.setEnabled(false);
        mGatewayLayout.setEnabled(false);
        mDnsLayout.setEnabled(false);
        mCommit.setEnabled(false);
        mAddressEdit.setEnabled(false);
        mMaskEdit.setEnabled(false);
        mGatewayEdit.setEnabled(false);
        mDnsEdit.setEnabled(false);
        }else{
        mAddressLayout.setEnabled(true);
        mMaskLayout.setEnabled(true);
        mGatewayLayout.setEnabled(true);
        mDnsLayout.setEnabled(true);
        mCommit.setEnabled(true);
        mAddressEdit.setEnabled(true);
        mMaskEdit.setEnabled(true);
        mGatewayEdit.setEnabled(true);
        mDnsEdit.setEnabled(true);
        }
    }
    private void startDhcp() {
        new Thread(new Runnable()
        {
        public void run()
        {
        String iface = mEthManager.getInterfaceName();
        mPppoeManager.disconnect(iface);
        }
        }).start();
        mEthManager.setEthernetEnabled(false);
        mEthManager.setEthernetMode(EthernetManager.ETHERNET_CONNECT_MODE_DHCP,null);
        mEthManager.setEthernetEnabled(true);
    }
    private void ClearIP(){
        mAddressEdit.setText("0.0.0.0");
        mGatewayEdit.setText("0.0.0.0");
        mMaskEdit.setText("0.0.0.0");
        mDnsEdit.setText("0.0.0.0");
    }
    private void UpdataIP(){
        Log.i(TAG, "startStaticIP ="+mip+" "+mMask+" "+mGateway+" "+mDns);
        if(mip!=null)
        mAddressEdit.setText(mip);
        if(mGateway!=null)
        mGatewayEdit.setText(mGateway);
        if(mMask!=null)
        mMaskEdit.setText(mMask);
        if(mDns!=null)
        mDnsEdit.setText(mDns);
    }
    @Override
    protected void onResume() {
        mIntentFilter = new IntentFilter(EthernetManager.ETHERNET_STATE_CHANGED_ACTION);
        mIntentFilter.addAction(EthernetManager.NETWORK_STATE_CHANGED_ACTION);
        this.registerReceiver(mEthSettingsReceiver, mIntentFilter);
        int state = mEthManager.getEthernetState();
        Log.i(TAG, "EthernetManager state="+state);
        if(state!=EthernetManager.ETHERNET_STATE_ENABLED)
        mEthManager.enableEthernet(true);
        m_Enable = true;
        if(m_Bauto){
            mOpen.requestFocus();
            mSwitch.setBackgroundResource(R.drawable.setting_second_switch_open);
            EnableEdit(m_Bauto);
        }else{
        getStaticIP();
        mClose.requestFocus();
        mSwitch.setBackgroundResource(R.drawable.setting_second_switch_close);
        }
        super.onResume();
    }
    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        super.onDestroy();
        this.unregisterReceiver(mEthSettingsReceiver);
    }
    private BroadcastReceiver mEthSettingsReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
        if (intent.getAction().equals(
        EthernetManager.ETHERNET_STATE_CHANGED_ACTION)) {
        int message = intent.getIntExtra(EthernetManager.EXTRA_ETHERNET_STATE, -1);
        switch (message) {
        case EthernetManager.EVENT_DHCP_CONNECT_SUCCESSED:
        getDhcpIP();
        Log.i(TAG, "DHCP UP OK : " + message);
        ShowToast(R.string.ethernet_commit_ok);
        break;
        case EthernetManager.EVENT_DHCP_CONNECT_FAILED:
        ShowToast(R.string.ethernet_commit_faile);
        Log.i(TAG, "DHCP UP failed : " + message);
        break;
        case EthernetManager.EVENT_DHCP_DISCONNECT_FAILED:
        Log.i(TAG, " DHCP down failed  : " + message);
        break;
        case EthernetManager.EVENT_STATIC_CONNECT_SUCCESSED:
        if(m_Manual){
        getStaticIP();
        ShowToast(R.string.ethernet_commit_ok);
        m_Manual = false;
        }
        Log.i(TAG, " Static UP OK  : " + message);
        break;
        case EthernetManager.EVENT_STATIC_CONNECT_FAILED:
        ShowToast(R.string.ethernet_commit_faile);
        Log.i(TAG, " Static UP failed  : " + message);
        break;
        case EthernetManager.EVENT_STATIC_DISCONNECT_FAILED:
        Log.i(TAG, " Static Down failed  : " + message);
        break;
        case EthernetManager.EVENT_PHY_LINK_UP:
        Log.i(TAG, " EVENT_PHY_LINK_UP  : " + message);
        break;
        case EthernetManager.EVENT_PHY_LINK_DOWN:
        case EthernetManager.EVENT_DHCP_DISCONNECT_SUCCESSED:
        case EthernetManager.EVENT_STATIC_DISCONNECT_SUCCESSED:
        Log.i(TAG, " EVENT_PHY_LINK_DOWN  : " + message);
        if(message==EthernetManager.EVENT_PHY_LINK_DOWN){
            Intent mintent = new Intent();
            mintent.setClass(EthernetActivity.this, WifiActivity.class);
            startActivity(mintent);
            finish();
        }
        break;
        default:
        break;
        }
        }
        }
    };
    public void getDhcpIP() {
        LinkProperties linkProperties = mConnectivityManager.getLinkProperties(ConnectivityManager.TYPE_ETHERNET);
        Iterator<LinkAddress> addrs = linkProperties.getLinkAddresses().iterator();
        if (!addrs.hasNext()) {
        Log.e(TAG, "getDhcpIP:can not get LinkAddress!!");
        return;
        }
        LinkAddress linkAddress = addrs.next();
        int prefixLength = linkAddress.getNetworkPrefixLength();
        int NetmaskInt = NetworkUtils.prefixLengthToNetmaskInt(prefixLength);
        InetAddress Netmask = NetworkUtils.intToInetAddress(NetmaskInt);
        String mNM = Netmask.getHostAddress();
        Log.i(TAG, "netmask:  " + mNM);
        mMask = mNM;
        try {
        String IP = linkAddress.getAddress().getHostAddress();
        Log.i(TAG, "mIP" + IP);
        mip = IP;
        String mGW = "";
        for (RouteInfo route : linkProperties.getRoutes()) {
        if (route.isDefaultRoute()) {
        mGW = route.getGateway().getHostAddress();
        Log.i(TAG, "Gateway:  " + mGW);
        mGateway = mGW;
        break;
        }
        }
        Iterator<InetAddress> dnses = linkProperties.getDnses().iterator();
        if(!dnses.hasNext()) {
        Log.e(TAG, "showDhcpIP:empty dns!!");
        } else {
        String mDns1 = dnses.next().getHostAddress();
        Log.i(TAG, "DNS1: " + mDns1);
        mDns = mDns1;
        if (!dnses.hasNext()) {
        Log.e(TAG, "showDhcpIP:empty dns2!!");
        } else {
        String mDns2 = dnses.next().getHostAddress();
        }
        }
        } catch (NullPointerException e) {
        Log.w(TAG, "can not get IP" + e);
        }
        UpdataIP();
    }
    public void getStaticIP() {
        DhcpInfo dhcpInfo = mEthManager.getSavedEthernetIpInfo();
        String IP = NetworkUtils.intToInetAddress(dhcpInfo.ipAddress).getHostAddress();
        if (null != IP)
        mip = IP;
        String mGW = NetworkUtils.intToInetAddress(dhcpInfo.gateway).getHostAddress();
        if (null != mGW)
        mGateway = mGW;
        String mNM = NetworkUtils.intToInetAddress(dhcpInfo.netmask).getHostAddress();
        if (null != mNM)
        mMask = mNM;
        String dns1 = NetworkUtils.intToInetAddress(dhcpInfo.dns1).getHostAddress();
        if (null != dns1)
        mDns = dns1;
        UpdataIP();
    }
    public void startStaticIP(){
        new Thread(new Runnable()
        {
        public void run()
        {
        String iface = mEthManager.getInterfaceName();
        mPppoeManager.disconnect(iface);
        }
        }).start();
        Log.i(TAG, "startStaticIP ="+mip+" "+mMask+" "+mGateway+" "+mDns);
        mEthManager.setEthernetEnabled(false);
        InetAddress ipaddr = NetworkUtils.numericToInetAddress(mip);
        InetAddress getwayaddr = NetworkUtils.numericToInetAddress(mGateway);
        InetAddress inetmask = NetworkUtils.numericToInetAddress(mMask);
        InetAddress idns1 = NetworkUtils.numericToInetAddress(mDns);

        DhcpInfo dhcpInfo = new DhcpInfo();
        dhcpInfo.ipAddress = NetworkUtils.inetAddressToInt((Inet4Address)ipaddr);
        dhcpInfo.gateway = NetworkUtils.inetAddressToInt((Inet4Address)getwayaddr);
        dhcpInfo.netmask = NetworkUtils.inetAddressToInt((Inet4Address)inetmask);
        dhcpInfo.dns1 = NetworkUtils.inetAddressToInt((Inet4Address)idns1);
        mEthManager.setEthernetMode(EthernetManager.ETHERNET_CONNECT_MODE_MANUAL, dhcpInfo);
        mEthManager.setEthernetEnabled(true);
    }
    public void ShowToast(int stringid){
        Toast toast = Toast.makeText(EthernetActivity.this, getResources().getString(stringid), Toast.LENGTH_SHORT);
        toast.show();

    }

}
