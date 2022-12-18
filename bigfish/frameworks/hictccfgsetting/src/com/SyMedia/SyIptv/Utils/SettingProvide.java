package com.SyMedia.SyIptv.Utils;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Calendar;
import java.util.TimeZone;
import com.hisilicon.android.HiAoService;
import com.hisilicon.android.HiDisplayManager;
import android.app.AlarmManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.Rect;
import android.net.LocalSocket;
import android.net.LocalSocketAddress;
import android.provider.Settings;
import android.provider.Settings.SettingNotFoundException;
import android.util.Log;

import com.hisilicon.android.hisysmanager.HiSysManager;
    /**
     *
     * @author 
     */

public class SettingProvide{
    private final String TAG = "SettingProvide";
    private Context mcontext = null;
    private static final String HOURS_12 = "12";
    private static final String HOURS_24 = "24";
    public SettingProvide() {
        mcontext = SettingUtils.context;
    }
    /**
     * TODO set Ip mode : 0  IPv4 1  IPv6
     * @param  flag
     * @return 0:OK -1:fail
     */
    public int setIpMode(int flag){
        int ret = flag;
        Log.d(TAG, "setting c into setIpMode value="+ret);
        return ret;
    }
    /**
     * TODO get ip mode value
     * @return 0:IPv4, 1:IPv6 -1:fail
     */
    public int getIpMode(){
        int ret = 5;
        Log.d(TAG, "setting c into getIpMode return="+ret);
        return ret;
    }
    /**
     * TODO set audio mode include HDMI and SPDIF
     * @param index
     * @return 0:OK,-1:fail
     */
    public int setAudioMode(int index){
        int ret = -1;
        HiAoService audio = new HiAoService();
        if(index>8||index<0)
        return ret;
        switch (index) {
        case 0:
        ret = audio.setAudioOutput(1, 0);
        break;
        case 1:
        ret = audio.setAudioOutput(1, 1);
        break;
        case 2:
        ret = audio.setAudioOutput(1, 2);
        break;
        case 3:
        ret = audio.setAudioOutput(1, 3);
        break;
        case 4:
        ret = audio.setAudioOutput(2, 2);
        break;
        case 5:
        ret = audio.setAudioOutput(2, 3);
        break;
        case 6:
        int curmod0 = audio.getAudioOutput(1);
        if(curmod0==2){
        return ret;
        }
        ret = audio.setBluerayHbr(0);
        break;
        case 7:
        int curmod1 = audio.getAudioOutput(1);
        if(curmod1==2){
        return ret;
        }
        ret = audio.setBluerayHbr(1);
        break;
        case 8:
        int curmod2 = audio.getAudioOutput(1);
        if(curmod2==2){
        return ret;
        }
        ret = audio.setBluerayHbr(2);
        break;
        default:
        break;
        }
        Log.d(TAG, "setting c into setAudioMode value="+ret);
        if(ret==0){
        SettingStore.saveSetting("config_AudioMode", String.valueOf(index));
        }
        return ret;
    }
    /**
    * TODO get current audio mode
    * @return
    */
    public int getAudioMode(){
        int ret = -1;
        String mode = null;
        mode = SettingStore.getSetting("config_AudioMode", "0");
        ret = Integer.parseInt(mode);
        Log.d(TAG, "setting c into getAudioMode return="+ret);
        return ret;
    }
    /**
     * TODO
     * @return -1:fail
        0:
        1:EEPROM
        2:SettingStore
     */
    public int getSaveMode(){
        int ret = -1;
        Log.d(TAG, "setting c into getSaveMode return="+ret);
        return ret;
    }
    /**
     * TODO set outputFormat
     * @param flag 0:PAL 1:NTSC
     * @return 0:OK -1:fail
     */
    public int setOutputFormat(int flag){
        int ret = -1;
        Log.d(TAG, "setting c into setOutputFormat value="+flag);
        HiDisplayManager display = new HiDisplayManager();
        if(flag==0){
        ret = display.setFmt(HiDisplayManager.ENC_FMT_PAL);
        }else if(flag==1){
        ret = display.setFmt(HiDisplayManager.ENC_FMT_NTSC);
        }
        Log.d(TAG, "setting c into setOutputFormat return="+ret);
        return ret>=0?0:-1;
    }
    /**
     * TODO get OutputFormat
     * @return 0:PAL 1:NTSC -1:fail
     */
    public int getOutputFormat(){
        int ret = -1;
        HiDisplayManager display = new HiDisplayManager();
        int format = display.getFmt();
        if(format==HiDisplayManager.ENC_FMT_PAL){
        ret = 0;
        }else if(format==HiDisplayManager.ENC_FMT_NTSC){
        ret = 1;
        }
        Log.d(TAG, "setting c into getOutputFormat return="+ret);
        return ret;
    }
    /**
     * TODO set Position
     * @param  l
     * @param  t
     * @param  w
     * @param  h
     * @param  mode
     * @return 0:OK -1:fail
     */
    public int setPosition(int l, int t, int w, int h ,int mode){
        int ret = -1;
        HiDisplayManager display = new HiDisplayManager();
        ret = display.setOutRange(l, t, w, h);
        Log.d(TAG, "setting c into setPosition return="+ret);
        return ret>=0?0:-1;
    }
    /**
     *
     * TODO get position
     * @return int[]: int[0]:left int[1]:top int[2]:width int[3]:height int[4]:mode
     */
    public int[] getPosition(){
        int[] ret = new int[5];
        HiDisplayManager display = new HiDisplayManager();
        if(display!=null){
        Rect rect = new Rect();
        rect = display.getOutRange();
        if(rect !=null){
        ret[0] = rect.left;
        ret[1] = rect.top;
        ret[2] = rect.width();
        ret[3] = rect.height();
        ret[4] = 0;
        }
        }
        Log.d(TAG, "setting c into getPosition y="+ret[0]+",x="+ret[1]+",w"+ret[2]+
        ",h"+ret[3]+",mode"+ret[4]);
        return ret;
    }
    /**
     *
     * TODO restoreFactory
     * @return 0:OK -1:fail
     */
    public int restoreFactorySettings(){
        int ret = -1;
        HiSysManager hiSysManager = new HiSysManager();
        ret = hiSysManager.reset();
        mcontext.sendBroadcast(new Intent("android.intent.action.MASTER_CLEAR"));
        Log.d(TAG, "setting c into restoreFactorySettings return="+ret);
        return ret;
    }
    /**
     *
     * TODO set date
     * @param  year
     * @param  month
     * @param  day
     * @return
     */
    public int setDate(int year, int month, int day){
        int ret = -1;
        Calendar c = Calendar.getInstance();
        c.set(Calendar.YEAR, year);
        c.set(Calendar.MONTH, month);
        c.set(Calendar.DAY_OF_MONTH, day);
        long when = c.getTimeInMillis();
        if (when / 1000 < Integer.MAX_VALUE) {
            ((AlarmManager) mcontext.getSystemService(Context.ALARM_SERVICE)).setTime(when);
            ret = 0;
        }
        Log.d(TAG, "setting c into setDate valuse="+year+month+day);
        return ret;
    }
    /**
     *
     * TODO set time
     * @param  hourOfDay
     * @param  minute
     * @return 0:OK -1:fail
     */
    public int setTime(int hourOfDay, int minute){
        int ret = -1;
        Calendar c = Calendar.getInstance();
        if(c==null)
        return ret;
        c.set(Calendar.HOUR_OF_DAY, hourOfDay);
        c.set(Calendar.MINUTE, minute);
        c.set(Calendar.SECOND, 0);
        c.set(Calendar.MILLISECOND, 0);
        long when = c.getTimeInMillis();
        if (when / 1000 < Integer.MAX_VALUE) {
            ((AlarmManager) mcontext.getSystemService(Context.ALARM_SERVICE)).setTime(when);
        }else{
        return ret;
        }
        ret = 0;
        Log.d(TAG, "setting c into setTime valuse="+hourOfDay+minute);
        return ret;
    }
    /**
     *
     * TODO setTimeFormat
     * @param  timeFormat 12 24
     * @return 0:OK -1:fail
     */
    public int setTimeFormat(int timeFormat){
        int ret = -1;
        String timestring = null;
        if(timeFormat==12){
        timestring = HOURS_12;
        }else if(timeFormat==24){
        timestring = HOURS_24;
        }else{
        return ret;
        }
        Boolean set = Settings.System.putString(mcontext.getContentResolver(),
                Settings.System.TIME_12_24,timestring);
        if(set){
        ret = 0;
        }
        Log.d(TAG, "setting c into setTimeFormat return="+ret);
        return ret;
    }
    /**
     *
     * TODO getTimeFormat
     * @return 12, 24
     */
    public int getTimeFormat(){
        int ret = -1;
        String format = Settings.System.getString(mcontext.getContentResolver(), Settings.System.TIME_12_24);
        if(format!=null){
        ret = Integer.valueOf(format);
        }
        Log.d(TAG, "setting c into getTimeFormat return="+ret);
        return ret;
    }
    /**
     *
     * TODO setDateFormat
     * @param dateFormat dd/MM/yyyy yyyy/MM/dd MM/dd/yyyy
     * @return 0:OK -1:fail
     */
    public int setDateFormat(String dateFormat){
        int ret = -1;
        Boolean result = Settings.System.putString(mcontext.getContentResolver(),Settings.System.DATE_FORMAT,dateFormat);
        if(result){
        ret = 0;
        }
        Log.d(TAG, "setting c into setDateFormat return="+ret);
        return ret;
    }
    /**
     *
     * TODO getDateFormat
     * @return yyyy/mm/dd, mm/dd/yyyy, dd/mm/yyyy
     */
    public String getDateFormat(){
        String dataformat = null;
        dataformat = Settings.System.getString(mcontext.getContentResolver(),Settings.System.DATE_FORMAT);
        Log.d(TAG, "setting c into getDateFormat return="+dataformat);
        return dataformat;
    }
    /**
     *
     * TODO setAutotime
     * @param Autotime 0: mechanical 1: auto
     * @return 0:OK -1:fail
     */
    public int setAutotime(int Autotime){
        int ret = -1;
        if(Autotime>1||Autotime<0){
        Log.d(TAG, "setAutotime value="+Autotime);
        return ret;
        }
        Boolean result = false;
        Log.d(TAG, "setting c into setAutotime value="+Autotime);
        result = Settings.Global.putString(mcontext.getContentResolver(), Settings.Global.AUTO_TIME,String.valueOf(Autotime));
        if(result){
        ret = 0;
        }
        Log.d(TAG, "setting c into setAutotime return="+ret);
        return ret;
    }
    /**
     *
     * TODO get whether or not auto
     * @return :-1:fail 0:mechanical 1:auto
     */
    public int getAutotime(){
        int ret = -1;
        try {
        ret = Settings.Global.getInt(mcontext.getContentResolver(), Settings.Global.AUTO_TIME);
        } catch (SettingNotFoundException e) {
        return ret;
        }
        Log.d(TAG, "setting c into getAutotime return="+ret);
        return ret;
    }
    /**
     *
     * TODO set AutoTimeZone
     * @param autoTimeZone 0:mechanical 1:auto
     * @return 0:OK -1:fail
     */
    public int setAutoTimeZone(int autoTimeZone){
        int ret = -1;
        if(autoTimeZone>1||autoTimeZone<0){
        return ret;
        }
        Boolean result = Settings.Global.putString(mcontext.getContentResolver(), Settings.Global.AUTO_TIME_ZONE,String.valueOf(autoTimeZone));
        if(result){
        ret = 0;
        }
        Log.d(TAG, "setting c into setAutoTimeZone return="+ret);
        return ret;
    }
    /**
     *
     * TODO get AutoTimeZone
     * @return -1:fail 0:mechanical 1:auto
     */
    public int getAutoTimeZone(){
        int ret = -1;
         try {
         ret = Settings.Global.getInt(mcontext.getContentResolver(), Settings.Global.AUTO_TIME_ZONE);
        } catch (SettingNotFoundException e) {
        return ret;
        }
        Log.d(TAG, "setting c into getAutoTimeZone return="+ret);
        return ret;
    }
    /**
     *
     * TODO set TimeZone
     * @param timeZone Asia/Shanghai Asia/Taipei
     * @return 0:OK -1:fail
     */
    public int setTimeZone(String timeZone){
        int ret = -1;
        TimeZone zone = TimeZone.getTimeZone(timeZone);
        if(zone.getID()==null){
        return ret;
        }else{
        ret = 0;
        }
        final AlarmManager alarm = (AlarmManager) mcontext.getSystemService(Context.ALARM_SERVICE);
        alarm.setTimeZone(zone.getID());
        Log.d(TAG, "setting c into setTimeZone return="+ret);
        return ret;
    }
    /**
     *
     * TODO get TimeZone
     * @return example Asia/Shanghai, Asia/Taipei
     */
    public String getTimeZone(){
        String timezone = null;
        Calendar now = Calendar.getInstance();
        timezone = now.getTimeZone().getID();
        Log.d(TAG, "setting c into getTimeZone return="+timezone);
        return timezone;
    }
    /**
     *
     * TODO set Resolution
     * @param index
     * @return 0:OK -1:fail
     */
    public int setResolution(int index){
        int ret = -1;
        HiDisplayManager display = new HiDisplayManager();
        ret = display.setFmt(index);
        if(ret==0){
        SettingStore.saveSetting("config_Resolutions", String.valueOf(index));
        }
        Log.d(TAG, "setting c into setResolution return="+ret);
        return ret>=0?0:-1;
    }
    /**
     *
     * TODO get Resolution
     * @return
     */
    public int getResolution(){
        int ret = -1;
        String resolution = SettingStore.getSetting("config_Resolutions", "0");
        ret = Integer.parseInt(resolution);
        Log.d(TAG, "setting c into getResolution return="+ret);
        return ret;
    }

}