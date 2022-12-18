package com.hisilicon.dlna.dmc.gui.browse.files;

import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class DeviceAccessBroadcast extends BroadcastReceiver{

	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub
		System.out.println("Come into DeviceAccessBroadcast!!");
		String type = intent.getStringExtra("Type");
		if(type.equals("packetLoss")){
			System.out.println("1Type is:" + type);
		}else if(type.equals("STBClose")){
			System.out.println("2Type is:" + type);
		}else if("Connect".equals(type)){
			System.out.println("2Type is:" + type);
		}
	}

}
