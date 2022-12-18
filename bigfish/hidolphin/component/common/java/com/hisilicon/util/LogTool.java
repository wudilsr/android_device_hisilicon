package com.hisilicon.util;

import android.util.Log;

public class LogTool
{
     private static final String MSG_SEPARATOR = ",-";
    private static final String MSG_EMPTY = "Empty Msg";
    private static final int STACK_LEVEL = 5;

    public static final int NOLOG = 0;
    public static final int ERROR = 1;
    public static final int WARNING = 2;
    public static final int INFO = 4;
    public static final int DEBUG = 8;
    public static final int VERBOSE = 16;

   
    private static int mLogLevel = ERROR;

    /**
     * Set the log output level. <br>
     *
     * @param nLevel, Level is : NOLOG,ERROR,WARNING,INFO,DEBUG,VERBOSE
     */
    public static void setLogLevel(int nLevel)
    {
        mLogLevel = NOLOG;
        switch (nLevel)
        {
            case VERBOSE:
                mLogLevel = mLogLevel + VERBOSE;
            case DEBUG:
                mLogLevel = mLogLevel + DEBUG;
            case INFO:
                mLogLevel = mLogLevel + INFO;
            case WARNING:
                mLogLevel = mLogLevel + WARNING;
            case ERROR:
                mLogLevel = mLogLevel + ERROR;
                break;
            default:
                mLogLevel = NOLOG;
                break;
        }
    }

   public static int getLogLevel()
   {
       if (0 != (mLogLevel & VERBOSE) )
       {
           return VERBOSE;
       }

	if (0 != (mLogLevel & DEBUG))
        {
           return DEBUG;
        }

	if (0 != (mLogLevel & INFO))
        {
           return INFO;
        }

	if (0 != (mLogLevel & WARNING))
        {
           return WARNING;
        }

	if (0 != (mLogLevel & ERROR))
        {
           return ERROR;
        }

	return NOLOG;
   }

    public static void v( String pMsg)
    {
        if (0 != (mLogLevel & VERBOSE) )
        {
            Log.v(getFinalTag(), getFinalMsg(pMsg));
        }
    }

    public static void d( String pMsg)
    {
        if (0 != (mLogLevel & DEBUG))
        {
            Log.d(getFinalTag(), getFinalMsg(pMsg));
        }
    }

    public static void i( String pMsg)
    {
        if (0 != (mLogLevel & INFO) )
        {
            Log.i(getFinalTag(), getFinalMsg(pMsg));
        }
    }

    public static void w(String pMsg)
    {
        if (0 != (mLogLevel & WARNING))
        {
            Log.w(getFinalTag(), getFinalMsg(pMsg));
        }
    }

    public static void e( String pMsg)
    {
        if (0 != (mLogLevel & ERROR)) 
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
        _Buf.append(MSG_SEPARATOR);
        _Buf.append(getLineNumber());
        _Buf.append(MSG_SEPARATOR);
        _Buf.append(pMsg);

        return _Buf.toString();
    }

    private static String getFinalTag()
    {
        return getClassName();
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
        String strClassName = Thread.currentThread().getStackTrace()[STACK_LEVEL].getClassName();
        String strRet = strClassName;
        int nLow = strClassName.lastIndexOf('.') + 1;
        if ((nLow > 0) && (nLow < strClassName.length()))
        {
            strRet = strClassName.substring(nLow);
        }
        return strRet;
    }
}
