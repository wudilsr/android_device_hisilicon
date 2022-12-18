package com.hisilicon.miracast.util;

import android.util.Log;

public class LogUtil
{
    public static boolean sIsDebugMode = true;

    public static final String DELIMITERS = " ---- ";
    public static final String SPACE = " ";

    public static final int STACK_INDEX = 5;

    public static void v(String msg)
    {
        if (sIsDebugMode)
        {
            Log.v(getFinalTag(), getFinalMsg(msg));
        }
    }

    public static void d(String msg)
    {
        if (sIsDebugMode)
        {
            Log.d(getFinalTag(), getFinalMsg(msg));
        }
    }

    public static void i(String msg)
    {
        Log.i(getFinalTag(), getFinalMsg(msg));
    }

    public static void w(String msg)
    {
        Log.w(getFinalTag(), getFinalMsg(msg));
    }

    public static void e(String msg)
    {
        Log.e(getFinalTag(), getFinalMsg(msg));
    }

    private static String getFinalTag()
    {
        return getClassName();
    }

    private static String getFinalMsg(String msg)
    {
        final StringBuffer strBuf = new StringBuffer();
        strBuf.append(getMethodName());
        strBuf.append(SPACE);
        strBuf.append(getLineNumber());
        if (msg != null)
        {
            if (!msg.isEmpty())
            {
                strBuf.append(DELIMITERS);
                strBuf.append(msg);
                strBuf.append(DELIMITERS);
            }
        }

        return strBuf.toString();
    }

    private static String getClassName()
    {
        return Thread.currentThread().getStackTrace()[STACK_INDEX].getClassName();
    }

    private static String getMethodName()
    {
        return Thread.currentThread().getStackTrace()[STACK_INDEX].getMethodName();
    }

    private static String getLineNumber()
    {
        final StringBuffer strBuf = new StringBuffer();
        strBuf.append("L");
        strBuf.append(Thread.currentThread().getStackTrace()[STACK_INDEX].getLineNumber());

        return strBuf.toString();
    }
}
