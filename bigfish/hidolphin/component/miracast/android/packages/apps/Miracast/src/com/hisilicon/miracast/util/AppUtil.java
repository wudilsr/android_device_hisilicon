package com.hisilicon.miracast.util;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;

public class AppUtil
{
    public static String getVersionInfo(Context context)
    {
        StringBuffer versionInfo = new StringBuffer();
        try
        {
            PackageManager pm = context.getPackageManager();
            PackageInfo pi = pm.getPackageInfo(context.getPackageName(), 0);
            if (pi != null)
            {
                versionInfo.append(pi.versionName);
                versionInfo.append("_");
                versionInfo.append(String.valueOf(pi.versionCode));
            }
            else
            {
                versionInfo.append("no version info");
            }
        }
        catch (PackageManager.NameNotFoundException e)
        {
            LogUtil.e(e.toString());
        }
        return versionInfo.toString();
    }

    public static boolean isAudioLibFound()
    {
        boolean ret = false;
        BufferedReader bufReader = null;
        Process proc = null;

        try
        {
            proc = Runtime.getRuntime().exec("busybox find /system/lib -name *AAC*decode*");
            bufReader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
            String line = null;
            while ((line = bufReader.readLine()) != null)
            {
                LogUtil.i(line);
                if (line.contains("AAC") && line.contains("decode"))
                {
                    // find AAC audio decode library
                    ret = true;
                }
            }

        }
        catch (IOException e)
        {
            LogUtil.e(e.toString());
        }
        finally
        {
            if (bufReader != null)
            {
                try
                {
                    bufReader.close();
                    bufReader = null;
                }
                catch (IOException e)
                {
                    LogUtil.e(e.toString());
                }
            }
        }

        return ret;
    }
}
