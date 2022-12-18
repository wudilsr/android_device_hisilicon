package com.SyMedia.SyIptv.Utils;

import android.content.Context;

public class SettingUtils{
    private static final String mLibName = "CTCCfgSetting";
    public static Context context = null;
    static {
        System.loadLibrary(mLibName);
    }
    public SettingUtils(Context context) {
        SettingUtils.context = context;
    }
    /**
     * TODO set Ip mode : 0  IPv4 1  IPv6
     * @param  flag
     * @return 0:OK -1:fail
     */
    public native int setIpMode(int flag);
    /**
     * TODO get ip mode value
     * @return 0:IPv4, 1:IPv6 -1:fail
     */
    public native int getIpMode();
    /**
     * TODO set audio mode include HDMI and SPDIF
     * @param index
     * AUDIO_OUTPUT_PORT_HDMI&&AUDIO_OUTPUT_MODE_OFF     0
     * AUDIO_OUTPUT_PORT_HDMI&& AUDIO_OUTPUT_MODE_AUTO   1
     * AUDIO_OUTPUT_PORT_HDMI&&AUDIO_OUTPUT_MODE_LPCM    2
     * AUDIO_OUTPUT_PORT_HDMI&&AUDIO_OUTPUT_MODE_RAW     3
     * AUDIO_OUTPUT_PORT_SPDIF&& AUDIO_OUTPUT_MODE_LPCM  4
     * AUDIO_OUTPUT_PORT_SPDIF&& AUDIO_OUTPUT_MODE_RAW   5
     * BLUERAY_AUTO 6
     * BLUERAY_H2L  7
     * BLUERAY_RAW  8
     * @return 0:OK -1:fail
     */
    public native int setAudioMode(int index);
    /**
     * TODO get current audio mode
     * @return
     */
    public native int getAudioMode();
    /**
     * TODO
     * @return -1:fail
        0:
        1:EEPROM
        2:SettingStore
     */
    public native int getSaveMode();
    /**
     * TODO set outputFormat
     * @param flag 0:PAL 1:NTSC
     * @return 0:OK -1:fail
     */
    public native int setOutputFormat(int flag);
    /**
     * TODO get OutputFormat
     * @return 0:PAL 1:NTSC -1:fail
     */
    public native int getOutputFormat();
    /**
     * TODO set Position
     * @param  l
     * @param  t
     * @param  w
     * @param  h
     * @param  mode
     * @return 0:OK -1:fail
     */
    public native int[] getPosition();
    /**
     *
     * TODO get position
     * @return int[]: int[0]:left int[1]:top int[2]:width int[3]:height int[4]:mode
     */
    public native int setPosition(int l, int t, int w, int h ,int mode);
    /**
     *
     * TODO restoreFactory
     * @return 0:OK -1:fail
     */
    public native int restoreFactorySettings();
    /**
     *
     * TODO set date
     * @param  year
     * @param  month
     * @param  day
     * @return
     */
    public native int setDate(int year, int month, int day);
    /**
     *
     * TODO set time
     * @param  hourOfDay
     * @param  minute
     * @return 0:OK -1:fail
     */
    public native int setTime(int hourOfDay, int minute);
    /**
     * TODO setTimeFormat
     * @param  timeFormat 12 24
     * @return 0:OK -1:fail
     */
    public native int setTimeFormat(int timeFormat );
    /**
     * TODO getTimeFormat
     * @return 12, 24
     */
    public native int getTimeFormat();
    /**
     * TODO setDateFormat
     * @param dateFormat dd/MM/yyyy yyyy/MM/dd MM/dd/yyyy
     * @return 0:OK -1:fail
     */
    public native int setDateFormat(String dateFormat);
    /**
     *
     * TODO getDateFormat
     * @return yyyy/mm/dd, mm/dd/yyyy, dd/mm/yyyy
     */
    public native String getDateFormat();
    /**
     * TODO setAutotime
     * @param Autotime 0: mechanical 1: auto
     * @return 0:OK -1:fail
     */
    public native int setAutotime(int Autotime);
    /**
     *
     * TODO get whether or not auto
     * @return :-1:fail 0:mechanical 1:auto
     */
    public native int getAutotime();
    /**
     *
     * TODO set AutoTimeZone
     * @param autoTimeZone 0:mechanical 1:auto
     * @return 0:OK -1:fail
     */
    public native int setAutoTimeZone(int autoTimeZone);
    /**
     *
     * TODO get AutoTimeZone
     * @return -1:fail 0:mechanical 1:auto
     */
    public native int getAutoTimeZone();
    /**
     *
     * TODO set TimeZone
     * @param timeZone Asia/Shanghai Asia/Taipei
     * @return 0:OK -1:fail
     */
    public native int setTimeZone(String timeZone);
    /**
     *
     * TODO get TimeZone
     * @return example Asia/Shanghai, Asia/Taipei
     */
    public native String getTimeZone();
    /**
     * TODO set Resolution
     * @param index
     * TV 1080P 60Hz            0
     * TV 1080P 50Hz            1
     * TV 1080i 60Hz            5
     * TV 1080i 50Hz            6
     * TV 720P 60Hz             7
     * TV 720P 50Hz             8
     * PAL                      11
     * NTSC                     14
     * @return 0:OK -1:fail
     */
    public native int setResolution(int index);
    /**
     *
     * TODO get Resolution
     * @return
     */
    public native int getResolution();
}
