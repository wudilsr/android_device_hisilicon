package com.hisilicon.dlna.dms;

import android.util.Log;

public final class LogHelper
{
    private static boolean mIsDebugMode = true;// 获取堆栈信息会影响性能，发布应用时记得关闭DebugMode
    private static String mLogTag = "UPNP";
    // private static String mLogTag = "LogHelper";

    private static final String CLASS_METHOD_LINE_FORMAT = "%s.%s()  Line:%d  (%s)";

    public static void trace()
    {
        if (mIsDebugMode)
        {
            StackTraceElement traceElement = Thread.currentThread().getStackTrace()[3];// 从堆栈信息中获取当前被调用的方法信息
            String logText = String.format(CLASS_METHOD_LINE_FORMAT, traceElement.getClassName(),
                    traceElement.getMethodName(), traceElement.getLineNumber(),
                    traceElement.getFileName());
            Log.d(mLogTag, logText);// 打印Log
        }
    }

    public static void trace(String msg)
    {
        if (mIsDebugMode)
        {
            StackTraceElement traceElement = Thread.currentThread().getStackTrace()[3];// 从堆栈信息中获取当前被调用的方法信息
            String logText = String.format(CLASS_METHOD_LINE_FORMAT, traceElement.getClassName(),
                    traceElement.getMethodName(), traceElement.getLineNumber(), msg);
            Log.d(mLogTag, logText);// 打印Log
        }
    }
}
