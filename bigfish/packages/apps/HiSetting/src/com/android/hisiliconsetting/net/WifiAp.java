package com.android.hisiliconsetting.net;

import android.content.Context;
import android.net.NetworkInfo;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiConfiguration.KeyMgmt;
import android.net.wifi.WifiSsid;
public class WifiAp implements Comparable<WifiAp>{

	@Override
	public int compareTo(WifiAp o) {
		// TODO Auto-generated method stub
		return 0;
	}
	private static final int SECURITY_EAP = 3;
	private static final int SECURITY_NONE = 0;
	private static final int SECURITY_PSK = 2;
	private static final int SECURITY_WEP = 1;
	public WifiConfiguration mConfig;
	public WifiInfo mInfo;
	public int mRssi;
	public int networkId;
	public int security;
	public String ssid;

	public WifiAp(ScanResult paramScanResult)
	{
		this.ssid = paramScanResult.SSID;
		this.security = getSecurity(paramScanResult);
		this.networkId = -1;
		this.mRssi = paramScanResult.level;
	}

	public WifiAp(WifiConfiguration paramWifiConfiguration)
	{
		this.ssid = (paramWifiConfiguration.SSID == null ? "" : removeDoubleQuotes(paramWifiConfiguration.SSID));
		this.security = getSecurity(paramWifiConfiguration);
		this.networkId = paramWifiConfiguration.networkId;
		this.mConfig = paramWifiConfiguration;
		this.mRssi = Integer.MAX_VALUE;
	}

	static String convertToQuotedString(String paramString)
	{
		return "\"" + paramString + "\"";
	}

	private int getSecurity(ScanResult result)
	{
		if (result.capabilities.contains("WEP")) {
			return SECURITY_WEP;
		} else if (result.capabilities.contains("PSK")) {
			return SECURITY_PSK;
		} else if (result.capabilities.contains("EAP")) {
			return SECURITY_EAP;
		}
		return SECURITY_NONE;
	}

	private int getSecurity(WifiConfiguration config)
	{
		if (config.allowedKeyManagement.get(KeyMgmt.WPA_PSK)) {
			return SECURITY_PSK;
		}
		if (config.allowedKeyManagement.get(KeyMgmt.WPA_EAP) ||
				config.allowedKeyManagement.get(KeyMgmt.IEEE8021X)) {
			return SECURITY_EAP;
		}
		return (config.wepKeys[0] != null) ? SECURITY_WEP : SECURITY_NONE;
	}

	static String removeDoubleQuotes(String paramString)
	{
	    if(paramString==null)
	        return WifiSsid.NONE;
		int i = paramString.length();
		if ((i > 1) && (paramString.charAt(0) == '"') && (paramString.charAt(i - 1) == '"'))
			paramString = paramString.substring(1, i - 1);
		return paramString;
	}


	protected void generateOpenNetworkConfig()
	{
		if (this.security != 0)
			throw new IllegalStateException();
		if (this.mConfig != null)
			return;
		this.mConfig = new WifiConfiguration();
		this.mConfig.SSID = convertToQuotedString(this.ssid);
		this.mConfig.allowedKeyManagement.set(0);
	}

	WifiConfiguration getConfig()
	{
		return this.mConfig;
	}
	public int getSecurity()
	{
		return this.security;
	}

	public String getSsid()
	{
		return this.ssid;
	}
	public int getRssi()
	{
		if(mRssi==Integer.MAX_VALUE)
		return -1;
		return this.mRssi;
	}
	public int getNetworkId()
	{
		return this.networkId;
	}
}
