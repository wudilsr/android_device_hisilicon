package com.android.smart.terminal.iptv.aidl;

import android.os.Parcel;
import android.os.Parcelable;

public class EthernetDevInfo implements Parcelable{
	
	public static final String ETH_CONN_MODE_DHCP = "dhcp";
	public static final String ETH_CONN_MODE_STATIC = "static";
	public static final String ETH_CONN_MODE_DHCPPLUS = "dhcp+";
	public static final String ETH_CONN_MODE_PPPOE = "pppoe";
	
	public String dev_name;
	public String username;
	public String password;
	public String ipmode;
	public String ipaddr;
	public String netmask;
	public String route;
	public String dns;
	public String dns2;
	public String mode;
	
	public static final Parcelable.Creator<EthernetDevInfo> CREATOR = new Parcelable.Creator<EthernetDevInfo>() {
		public EthernetDevInfo createFromParcel(Parcel in) {
			return new EthernetDevInfo(in);
		}


		public EthernetDevInfo[] newArray(int size) {
			return new EthernetDevInfo[size];
		}
	};
	
	public EthernetDevInfo() {
	}


	private EthernetDevInfo(Parcel in) {
		readFromParcel(in);
	}
	
	public void readFromParcel(Parcel in) {
		dev_name = in.readString();
		username = in.readString();
		password = in.readString();
		ipmode = in.readString();
		ipaddr = in.readString();
		netmask = in.readString();
		route = in.readString();
		dns = in.readString();
		dns2 = in.readString();
		mode = in.readString();
	}
	@Override
	public int describeContents() {
		// TODO Auto-generated method stub
		return 0;
	}
	@Override
	public void writeToParcel(Parcel out, int flags) {
		// TODO Auto-generated method stub
		out.writeString(dev_name);
		out.writeString(username);
		out.writeString(password);
		out.writeString(ipmode);
		out.writeString(ipaddr);
		out.writeString(netmask);
		out.writeString(route);
		out.writeString(dns);
		out.writeString(dns2);
		out.writeString(mode);
	}
	
	
}
