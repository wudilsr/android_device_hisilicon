package com.hisilicon.android.videoplayer.utility;

import android.util.Log;

public class LogTool
{
    private static final String MSG_SEPARATOR = " ---- ";

    private static final String TAG_PREFIX = "[Hisilicon]";

    private static final String MSG_EMPTY = "Empty Msg";

    private static final int STACK_LEVEL = 5;

    private static boolean mVFlag = true;

    private static boolean mDFlag = true;

    private static boolean mIFlag = true;

    private static boolean mWFlag = true;

    private static boolean mEFlag = true;

    public static final int NOLOG = 0;

    public static final int VERBOSE = 1;

    public static final int DEBUG = 2;

    public static final int INFO = 3;

    public static final int WARNING = 4;

    public static final int ERROR = 5;

    public static void setLogLevel(int pLevel)
    {
        mVFlag = true;
        mDFlag = true;
        mIFlag = true;
        mWFlag = true;
        mEFlag = true;

        switch (pLevel)
        {
            case VERBOSE:
                break;

            case DEBUG:
                mVFlag = false;
                break;

            case INFO:
                mVFlag = false;
                mDFlag = false;
                break;

            case WARNING:
                mVFlag = false;
                mDFlag = false;
                mIFlag = false;
                break;

            case ERROR:
                mVFlag = false;
                mDFlag = false;
                mIFlag = false;
                mWFlag = false;
                break;

            case NOLOG:
                mVFlag = false;
                mDFlag = false;
                mIFlag = false;
                mWFlag = false;
                mEFlag = false;

            default:
                break;
        }
    }

    public static void v(String pMsg)
    {
        if (mVFlag)
        {
            Log.v(getFinalTag(), getFinalMsg(pMsg));
        }
    }

    public static void d(String pMsg)
    {
        if (mDFlag)
        {
            Log.d(getFinalTag(), getFinalMsg(pMsg));
        }
    }

    public static void i(String pMsg)
    {
        if (mIFlag)
        {
            Log.i(getFinalTag(), getFinalMsg(pMsg));
        }
    }

    public static void w(String pMsg)
    {
        if (mEFlag)
        {
            Log.w(getFinalTag(), getFinalMsg(pMsg));
        }
    }

    public static void e(String pMsg)
    {
        if (mWFlag)
        {
            Log.e(getFinalTag(), getFinalMsg(pMsg));
        }
    }

    private static String getFinalMsg(String pMsg)
    {
        if (pMsg.isEmpty())
        {
            pMsg = MSG_EMPTY;
        }

        StringBuffer _Buf = new StringBuffer();
        _Buf.append(getMethodName());
        _Buf.append(" ");
        _Buf.append(getLineNumber());
        _Buf.append(MSG_SEPARATOR);
        _Buf.append(pMsg);
        _Buf.append(MSG_SEPARATOR);

        return _Buf.toString();
    }

    private static String getFinalTag()
    {
        StringBuffer _Buf = new StringBuffer();
        _Buf.append(TAG_PREFIX);
        _Buf.append(getClassName());

        return _Buf.toString();
    }

    private static String getLineNumber()
    {
        StringBuffer _Buf = new StringBuffer();
        _Buf.append("L");
        _Buf.append(Thread.currentThread().getStackTrace()[STACK_LEVEL].getLineNumber());

        return _Buf.toString();
    }

    private static String getMethodName()
    {
        return Thread.currentThread().getStackTrace()[STACK_LEVEL].getMethodName();
    }

    private static String getClassName()
    {
        return Thread.currentThread().getStackTrace()[STACK_LEVEL].getClassName();
    }
}
