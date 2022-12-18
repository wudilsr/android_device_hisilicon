package com.android.smart.terminal.iptv.aidl;
import com.android.smart.terminal.iptv.aidl.EthernetDevInfo;
interface ServiceSettingsInfoAidl {
	int getAudioMode();
	int getResoultion();
	boolean setAudioMode(int flag);
	boolean setResoultion(int flag);
	boolean setEthernetDevInfo(in EthernetDevInfo eth);
	EthernetDevInfo getEthernetDevInfo();
	boolean setValue(in String key,in String value);
	String getValue(in String key,in String value);
	EthernetDevInfo getEthernetIPv6DevInfo();
}