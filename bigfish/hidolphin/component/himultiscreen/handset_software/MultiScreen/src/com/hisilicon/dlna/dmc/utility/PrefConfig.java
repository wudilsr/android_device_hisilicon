package com.hisilicon.dlna.dmc.utility;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.preference.PreferenceManager;

import com.hisilicon.multiscreen.mybox.MyApp;

public class PrefConfig {

	public static void setIntPreferences(String sharedPreferences, String key, int value){
		SharedPreferences pref = getSharedPreferences(sharedPreferences);
		Editor editor = pref.edit();
		editor.putInt(key, value);
		editor.commit();
	}
	
	public static int getIntPreferences(String sharedPreferences, String key){
		SharedPreferences pref = getSharedPreferences(sharedPreferences);
		return pref.getInt(key, 0);
	}
	
	public static SharedPreferences getSharedPreferences(String sharedPreferences){
		return MyApp.getApplication().getSharedPreferences(sharedPreferences, Context.MODE_PRIVATE);
	}

	public static SharedPreferences getDefaultSharedPreferences(){
		return PreferenceManager.getDefaultSharedPreferences(MyApp.getApplication());
	}

	public static void setStringPreferences(String key, String value){
		SharedPreferences pref = getDefaultSharedPreferences();
		Editor editor = pref.edit();
		editor.putString(key, value);
		editor.commit();
	}

	public static String getStringPreferences(String key){
		return getStringPreferences(key, "");
	}

	public static String getStringPreferences(String key, String defaultValue){
		SharedPreferences pref = getDefaultSharedPreferences();
		return pref.getString(key, defaultValue);
	}

	public static void setBooleanPreferences(String key, boolean value){
		SharedPreferences pref = getDefaultSharedPreferences();
		Editor editor = pref.edit();
		editor.putBoolean(key, value);
		editor.commit();
	}

	public static boolean getBooleanPreferences(String key){
		return getBooleanPreferences(key, false);
	}

	public static boolean getBooleanPreferences(String key, boolean defValue){
		SharedPreferences pref = getDefaultSharedPreferences();
		return pref.getBoolean(key, defValue);
	}

	public static void setFloatPreferences(String key, float value)
	{
		SharedPreferences pref = getDefaultSharedPreferences();
		Editor editor = pref.edit();
		editor.putFloat(key, value);
		editor.commit();
	}

	public static float getFloatPreferences(String key)
	{
		return getFloatPreferences(key, 0.0f);
	}

	public static float getFloatPreferences(String key, float defValue)
	{
		SharedPreferences pref = getDefaultSharedPreferences();
		return pref.getFloat(key, defValue);
	}

	public static void setIntPreferences(String key, int value){
		SharedPreferences pref = getDefaultSharedPreferences();
		Editor editor = pref.edit();
		editor.putInt(key, value);
		editor.commit();
	}

	public static int getIntPreferences(String key){
		return getIntPreferences(key, 0);
	}

	public static int getIntPreferences(String key, int defalutValue){
		SharedPreferences pref = getDefaultSharedPreferences();
		return pref.getInt(key, defalutValue);
	}
}
