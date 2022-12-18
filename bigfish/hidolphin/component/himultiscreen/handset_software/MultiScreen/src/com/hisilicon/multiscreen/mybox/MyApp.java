package com.hisilicon.multiscreen.mybox;

import android.app.Application;
import android.content.ContentResolver;

public class MyApp extends Application
{
    private static MyApp instance;

    private static String STBIP = "";

    @Override
    public void onCreate()
    {
        super.onCreate();
        instance = this;
    }

    public static Application getApplication()
    {
        if (instance == null)
            initialize();
        return instance;
    }

    private static void initialize()
    {
        instance = new MyApp();
        instance.onCreate();
    }

    public static ContentResolver getResolver()
    {
        return getApplication().getContentResolver();
    }

    public static String getSTBIP()
    {
        return STBIP;
    }

    public static void setSTBIP(String nowSTBIP)
    {
        STBIP = nowSTBIP;
    }
}
