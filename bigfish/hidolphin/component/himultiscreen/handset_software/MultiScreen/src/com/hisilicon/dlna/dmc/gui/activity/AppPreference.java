package com.hisilicon.dlna.dmc.gui.activity;

import com.hisilicon.dlna.dmc.utility.PrefConfig;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.R;

public class AppPreference {

	/**
	 * 
	 * 根据Preferences 值判断应用程序是否第一次使用
	 */
	public static boolean isAppFirstUse() {
		return PrefConfig.getIntPreferences(Utility.getString(R.string.Pref_IS_APP_FIRST_USE)) == 0;
	}

	public static void setAppAlreadyUse() {
		PrefConfig.setIntPreferences(Utility.getString(R.string.Pref_IS_APP_FIRST_USE), 1);
	}
	
	
	/**
	 * 
	 * 根据Preferences 值判断应用程序是否第一次使用
	 */
	public static boolean isMirrorFirstUse() {
		return PrefConfig.getIntPreferences(Utility.getString(R.string.Pref_IS_MIRROR)) == 0;
	}

	public static void setMirrrorUse() {
		PrefConfig.setIntPreferences(Utility.getString(R.string.Pref_IS_MIRROR), 1);
	}
	
	/**
	 * 
	 * DMS 每次加载的最大个数
	 */
	public static int getMaxItemPerLoad() {
		return PrefConfig.getIntPreferences(Utility.getString(R.string.Pref_MAX_RESULT), 60);
	}

	public static boolean getAutoNext() {
		return PrefConfig.getBooleanPreferences(Utility.getString(R.string.Pref_AUTO_NEXT), true);
	}

	public static boolean getShuffle() {
		return PrefConfig.getBooleanPreferences(Utility.getString(R.string.Pref_RANDOM_TRACK));
	}
	
	public static void setShuffle(boolean shuffle) {
		PrefConfig.setBooleanPreferences(Utility.getString(R.string.Pref_RANDOM_TRACK), shuffle);
	}

	public static String getFriendlyName() {
		return PrefConfig.getStringPreferences(Utility.getString(R.string.Pref_DLNA_FRIENDLY_NAME), Utility.getString(R.string.friendly_name));
	}
	
	/**
	 * 
	 * 获取上次保存的MultiScreen的UDN
	 */
	public static String getMultiScreenUDN() {
		return PrefConfig.getStringPreferences(Utility.getString(R.string.Pref_DLNA_MUTISCREEN_UDN));
	}
	
	/**
	 * 
	 * 保存MultiScreen的UDN
	 */
	public static void setMultiScreenUDN(String udn) {
		PrefConfig.setStringPreferences(Utility.getString(R.string.Pref_DLNA_MUTISCREEN_UDN), udn);
	}

	public static String getManufacturer() {
		return PrefConfig.getStringPreferences(Utility.getString(R.string.Pref_DLNA_MANUFACTURER), Utility.getString(R.string.manufacturer));
	}
	
	public static String getDLNACreater() {
		return PrefConfig.getStringPreferences(Utility.getString(R.string.Pref_DLNA_CREATER), Utility.getString(R.string.dlna_creater));
	}
	
	public static String getCameraCachePath() {
		return PrefConfig.getStringPreferences(Utility.getString(R.string.Pref_DLNA_CAMERA_CACHE_PATH));
	}
	
	public static void setCameraCachePath(String path) {
		PrefConfig.setStringPreferences(Utility.getString(R.string.Pref_DLNA_CAMERA_CACHE_PATH), path);
	}
	
	public static int getPlayPosition() {
		return PrefConfig.getIntPreferences(Utility.getString(R.string.Pref_PLAY_POSITION));
	}

	public static void setPlayPosition(int playPosition) {
		PrefConfig.setIntPreferences(Utility.getString(R.string.Pref_PLAY_POSITION), playPosition);
	}
}
