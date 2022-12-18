package com.hisilicon.android.sdkinvoke;


public class HiSdkinvoke
{
    static {
        System.loadLibrary("sdkinvoke_jni");
    }

    public native String getCPUInfo();

    public native int hiBitSet(int maddr,int bit,int n,int val);

    public native int hiBitGet(int maddr ,int bit ,int n);

    public native int hiWrite(int maddr ,int val);

    public native int hiRead(int maddr);

    public native int hiGpioBitSet(int maddr,int bit,int val);

    public native int hiGpioBitGet(int maddr,int bit);

    public native String otpGetLotID();

    public native void otpSetLotID(String chipid);

    public native int otpGetLock();

    public static native String getChipVersion();
}
