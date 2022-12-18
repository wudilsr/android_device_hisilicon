package com.SyMedia.SyIptv.Utils;

public class SettingStore {
    private static final String mLibName = "CTCCfgSetting";
    static {
             System.loadLibrary(mLibName);
        }
    public static native String getSetting(String key, String defaultval) ;
    public static native int saveSetting(String key, String val);
}
