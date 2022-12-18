package com.hisilicon.dlna.dmc.utility;

import android.util.Log;

public class LogUtil {
	private static long time;
	
	public static void log(String str){
		Log.d("shichang",str);
	}
	
	public static void logErr(String str){
		Log.e("shichang",str);
	}
	
	public static void startTiming(){
		time = System.currentTimeMillis();
	}
	
	public static void endTiming(){
		long tmp = System.currentTimeMillis() - time;
		log("used " + tmp);
	}
}
