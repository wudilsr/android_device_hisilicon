package com.hisilicon.android.netshare;

/**
 * JNI
*/
public class Jni
{
	static {
		System.loadLibrary("netshare_jni");
        sambaInit();
	}
	public native int UImount(String address, String workpath,String mountpoint,String user,String password);
	public native int myUmount(String path);
	public native String getMountPoint(String path);
	public native String getPcName(String ip);
	public native int umountlist();
    private static native final int sambaInit();
}
