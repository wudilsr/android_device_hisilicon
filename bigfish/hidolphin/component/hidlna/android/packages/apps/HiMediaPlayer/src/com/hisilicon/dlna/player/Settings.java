package com.hisilicon.dlna.player;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
public class Settings
{
    private static final String SETTING_INFOS = "SETTINGS_SAVED";

    private static SharedPreferences setting = null;

    // ==========设置对应项==========
    /* 音乐的播放模式：普通，单曲循环，所有循环 */
    public static final String MUSIC_PLAYMODE = "music_playmode";
    public static final String VIDEO_PLAYMODE = "video_playmode";
    public static final int playmode_normal = 0;
    public static final int playmode_repeat_one = 1;
    public static final int playmode_repeat_all = 2;

    /* 音乐的随机模式：on, off */
    public static final String MUSIC_SHUFFLEMODE = "shuffle_mode";
    public static final int shuffle_off = 0;
    public static final int shuffle_on = 1;

    // ==========设置对应项(完毕)===========

    public static void init(Context ct)
    {
        setting = ct.getSharedPreferences(Settings.SETTING_INFOS, Context.MODE_WORLD_READABLE|Context.MODE_MULTI_PROCESS);
    }

    public static Boolean getParaBoolean(String name)
    {
        Boolean para = setting.getBoolean(name, false);
        return para;
    }

    public static int getParaInt(String name)
    {
        int para = setting.getInt(name, 0);
        return para;
    }

    public static String getParaStr(String name)
    {
        String para = setting.getString(name, "");
        return para;
    }

    public static boolean putParaBoolean(String name, Boolean para)
    {
        return setting.edit().putBoolean(name, para).commit();
    }

    public static boolean putParaInt(String name, int para)
    {
        return setting.edit().putInt(name, para).commit();
    }

    public static boolean putParaStr(String name, String para)
    {
        return setting.edit().putString(name, para).commit();
    }

}
