package com.android.hisiliconsetting.net;

import java.util.List;

import com.android.hisiliconsetting.R;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiSsid;
import android.net.wifi.WifiConfiguration.AuthAlgorithm;
import android.net.wifi.WifiConfiguration.KeyMgmt;
import android.util.Log;

public class WifiUtil
{
  private static String TAG="WifiUtil";
  public static final int SECURITY_EAP = 3;
  public static final int SECURITY_NONE = 0;
  public static final int SECURITY_PSK = 2;
  public static final int SECURITY_WEP = 1;

  public static int changeStregthtoDrawid(int paramInt)
  {
		  switch (WifiManager.calculateSignalLevel(paramInt, 5))
		    {
		    case 0:
		      return R.drawable.setting_wifi_signal_connected01_normal;
		    case 1:
		      return R.drawable.setting_wifi_signal_connected02_normal;
		    case 2:
		      return R.drawable.setting_wifi_signal_connected03_normal;
		    case 3:
		    case 4:
		      return R.drawable.setting_wifi_signal_connected04_normal;
		    }
    return R.drawable.icon_settings_wifi_normal_0;
  }

  public static PskType getPskType(ScanResult result)
  {
      boolean wpa = result.capabilities.contains("WPA-PSK");
      boolean wpa2 = result.capabilities.contains("WPA2-PSK");
      if (wpa2 && wpa) {
          return PskType.WPA_WPA2;
      } else if (wpa2) {
          return PskType.WPA2;
      } else if (wpa) {
          return PskType.WPA;
      } else {
          Log.w(TAG, "Received abnormal flag string: " + result.capabilities);
          return PskType.UNKNOWN;
      }
  }
  public static int getSecurity(WifiConfiguration config) {
      if (config.allowedKeyManagement.get(KeyMgmt.WPA_PSK)) {
          return SECURITY_PSK;
      }
      if (config.allowedKeyManagement.get(KeyMgmt.WPA_EAP) ||
              config.allowedKeyManagement.get(KeyMgmt.IEEE8021X)) {
          return SECURITY_EAP;
      }
      return (config.wepKeys[0] != null) ? SECURITY_WEP : SECURITY_NONE;
  }
  public static int getSecurity(ScanResult paramScanResult)
  {
    if (paramScanResult.capabilities.contains("WEP"))
      return SECURITY_WEP;
    if (paramScanResult.capabilities.contains("PSK"))
      return SECURITY_PSK;
    if (paramScanResult.capabilities.contains("EAP"))
      return SECURITY_EAP;
    return SECURITY_NONE;
  }
  public static enum PskType {
      UNKNOWN,
      WPA,
      WPA2,
      WPA_WPA2,
  };
  public static WifiConfiguration IsExsits(WifiAp paramScanResult,List<WifiConfiguration> list)
       {
           List<WifiConfiguration> existingConfigs = list;
              for (WifiConfiguration existingConfig : existingConfigs)
             {
                if (existingConfig.SSID.equals("\""+paramScanResult.ssid+"\""))
                {
                    return existingConfig;
                }
             }
           return null;
      }
  public static WifiConfiguration CreateWifiInfo(String SSID, String Password, int Type)
     {
        WifiConfiguration config = new WifiConfiguration();
         config.allowedAuthAlgorithms.clear();
         config.allowedGroupCiphers.clear();
         config.allowedKeyManagement.clear();
         config.allowedPairwiseCiphers.clear();
         config.allowedProtocols.clear();
         config.SSID = "\"" + SSID + "\"";
         config.hiddenSSID = true;
        if(Type == SECURITY_NONE)
        {
            // config.wepKeys[0] = "";
             config.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.NONE);
            // config.wepTxKeyIndex = 0;
        }
        if(Type == SECURITY_WEP)
        {
        config.allowedKeyManagement.set(KeyMgmt.NONE);
            config.allowedAuthAlgorithms.set(AuthAlgorithm.OPEN);
            config.allowedAuthAlgorithms.set(AuthAlgorithm.SHARED);
        // WEP-40, WEP-104, and 256-bit WEP (WEP-232?)
            int length = Password.length();
            if ((length == 10 || length == 26 || length == 58) &&
        Password.matches("[0-9A-Fa-f]*")) {
                config.wepKeys[0] = Password;
            } else {
                config.wepKeys[0] = '"' + Password + '"';
            }
        }
        if(Type==SECURITY_PSK)
        {
        config.allowedKeyManagement.set(KeyMgmt.WPA_PSK);
            if (Password.length() != 0) {
                if (Password.matches("[0-9A-Fa-f]{64}")) {
                    config.preSharedKey = Password;
                } else {
                    config.preSharedKey = '"' + Password + '"';
                }
            }
        }
        if(Type==SECURITY_EAP){
         config.allowedKeyManagement.set(KeyMgmt.WPA_EAP);
             config.allowedKeyManagement.set(KeyMgmt.IEEE8021X);
        }
        return config;
        }
  public static String ChangeSSID(String infossid){
        String id = null;
        if(infossid==null)
           return WifiSsid.NONE;
        int end = infossid.length();
        id = infossid.substring(1, end-1);
        return id;
    }
  public static Boolean CheckIP(String ip){
      Boolean enable = false;
      String regex = "^(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|[1-9])\\."
              + "(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)\\."
              + "(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)\\."
              + "(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)$";
      if(ip!=null){
          if(ip.matches(regex)){
          enable = true;
          }
      }
      return enable;
  }

}
