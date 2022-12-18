package com.hisilicon.dlna.dmc.gui.browse;

import com.hisilicon.multiscreen.mybox.MyApp;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class DMSBroadcastReceive extends BroadcastReceiver{

	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub
		System.out.println("---------Come into DMSBroadcastReceive---------");
		MyApp.setSTBIP(intent.getStringExtra("STBIP"));
	}

}
