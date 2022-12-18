package com.hisilicon.android;

//import android.os.Parcel;
//import android.os.Parcelable;

/**
* AudioSetting interface<br>
*/

public class HiAoService
{

    public static final int AUDIO_OUTPUT_PORT_HDMI = 1;
    public static final int AUDIO_OUTPUT_PORT_SPDIF = 2;

    public static final int AUDIO_OUTPUT_MODE_OFF = 0;
    public static final int AUDIO_OUTPUT_MODE_AUTO = 1;
    public static final int AUDIO_OUTPUT_MODE_LPCM = 2;
    public static final int AUDIO_OUTPUT_MODE_RAW = 3;

    public static final int BLUERAY_AUTO = 0;
    public static final int BLUERAY_H2L = 1;
    public static final int BLUERAY_RAW = 2;

    static {
    System.loadLibrary("hiaoservice_jni");
    }

     /**
     * set the audio output mode.
     * @param port 1:HDMI, 2:SPDIF <br>
     * @param mode HDMI 0:close,1:auto,2:LPCM,3:RAW
     *             SPDIF:2:LPCM,3:RAW<br>
     * @return int
     */
    public native int setAudioOutput (int port, int mode);

     /**
     * get the audio output mode.
     * <br>
     * @param port 1.HDMI 2.SPDIF <br>
     * @return mode HDMI 0:close,1:auto,2:LPCM,3:RAW
     *             SPDIF:2:LPCM,3:RAW<br>
     */
    public native int getAudioOutput (int port);

     /*
     * @param status 0:Auto, 1:RAW5.1, 2:RAW7.1
     * @return int
     */
    public native int setBluerayHbr (int status);

	/*
	* @param status 0:FALSE, 1:TRUE
	* @return int
	*/

	public native int setEnterSmartSuspend (int status);
}

