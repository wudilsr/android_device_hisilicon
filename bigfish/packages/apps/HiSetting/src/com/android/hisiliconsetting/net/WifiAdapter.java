package com.android.hisiliconsetting.net;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.NetworkInfo.State;
import android.net.NetworkInfo.DetailedState;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.WpsInfo;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import java.util.HashMap;
import java.util.List;

import com.android.hisiliconsetting.R;

public class WifiAdapter extends BaseAdapter
{
    private String TAG = "WifiAdapter";
    private Context ctx;
    private ConnectivityManager mConnectivityManager;
    private LayoutInflater mInflater;
    private List<WifiAp> mLists;
    private WifiManager mWifiManager;
    public int OldIndex = -1;
    private WifiInfo localWifiInfo = null;
    public WifiAdapter(Context paramContext, List<WifiAp> paramList, WifiManager paramWifiManager)
    {
        this.mInflater = LayoutInflater.from(paramContext);
        this.ctx = paramContext;
        this.mLists = paramList;
        this.mWifiManager = paramWifiManager;
        mConnectivityManager = ((ConnectivityManager)this.ctx.getSystemService(Context.CONNECTIVITY_SERVICE));
        localWifiInfo = this.mWifiManager.getConnectionInfo();
    }

    public int getCount()
    {
        if (this.mLists == null)
        return 0;
        return this.mLists.size();
    }

    public List<WifiAp> getData()
    {
        return this.mLists;
    }

    public Object getItem(int paramInt)
    {
        return this.mLists.get(paramInt);
    }

    public long getItemId(int paramInt)
    {
        return 0L;
    }

    public View getView(int paramInt, View paramView, ViewGroup paramViewGroup)
    {
        ViewHolder localViewHolder;
        WifiAp localScanResult = null;
        localScanResult = (WifiAp)this.mLists.get(paramInt);
        if (paramView == null)
        {
        localWifiInfo = this.mWifiManager.getConnectionInfo();
        localViewHolder = new ViewHolder();
        paramView = this.mInflater.inflate(R.layout.wifi_info_item, null);
        localViewHolder.ssidname = ((TextView)paramView.findViewById(R.id.wifi_item_title));
        localViewHolder.imgLock = ((ImageView)paramView.findViewById(R.id.wifi_item_lock));
        localViewHolder.imgSign = ((ImageView)paramView.findViewById(R.id.wifi_item_signal));
        localViewHolder.isConnect = ((TextView)paramView.findViewById(R.id.wifi_item_connect));
        paramView.setTag(localViewHolder);
        }else{
        localViewHolder = (ViewHolder)paramView.getTag();
        }
        localViewHolder.ssidname.setText(localScanResult.getSsid());
        if(localScanResult.getRssi()==-1){
             localViewHolder.imgSign.setBackgroundResource(R.drawable.icon_settings_wifi_normal_0);
        }else{
             localViewHolder.imgSign.setBackgroundResource(WifiUtil.changeStregthtoDrawid(localScanResult.getRssi()));
        }
        localViewHolder.isConnect.setVisibility(View.VISIBLE);
        localViewHolder.isConnect.setText("");
        int securi = localScanResult.getSecurity();
        if (securi == 0){
        localViewHolder.imgLock.setBackgroundResource(R.color.transparent);
        }else{
        localViewHolder.imgLock.setBackgroundResource(R.drawable.setting_wifi_lock_normal);
        }
        if(WifiActivity.mIsConnectting&&paramInt==0
            &&WifiAp.removeDoubleQuotes(localWifiInfo.getSSID()).equals(localScanResult.getSsid())){
            localViewHolder.isConnect.setText(R.string.wifi_connecting);
            return paramView;
        }
        NetworkInfo info = mConnectivityManager.getActiveNetworkInfo();
        if(localWifiInfo!=null&&localWifiInfo.getSSID()!=null&&localWifiInfo.getNetworkId()!=WifiConfiguration.INVALID_NETWORK_ID){
        String wifiinfo_ssid = WifiAp.removeDoubleQuotes(localWifiInfo.getSSID());
        //Log.i(TAG, "localWifiInfo SSID = " + wifiinfo_ssid);
        if(wifiinfo_ssid.equals(localScanResult.getSsid())){
        //Log.i(TAG, "localWifiInfo equals SSID = " + wifiinfo_ssid);
        OldIndex = paramInt;
        //int network = mConnectivityManager.getActiveDefaultNetwork();
        //Log.i(TAG, "localScanResult index= " + OldIndex);
        if (info!=null&&info.getTypeName().equals("WIFI")&&info.isAvailable())
        {
        localViewHolder.isConnect.setText(R.string.wifi_connected);
        }
        }else{
        }
        }else{
        //Log.i(TAG, "localWifiInfo = null");
        }
        return paramView;
    }
    public class ViewHolder
    {
        public ImageView imgLock;
        public ImageView imgSign;
        public TextView isConnect;
        public TextView ssidname;
    }
}
