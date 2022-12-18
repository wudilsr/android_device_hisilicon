package com.sample.atc.utils;

public class SampleUtils{
    private static final String mLibName = "sampleatc_jni";
    static {
        System.loadLibrary(mLibName);
    }

    public native int hdmiInit();

    public native int hdmiOpen();

    public native int hdmiTestCMD(String str);

    public native int[] hdmiDisplayEdit();

    public native int setHdmiMode(int mode);

    public native int getRGBMode();

    public native int getYCCMode();

    public native int getReverseMode();

}