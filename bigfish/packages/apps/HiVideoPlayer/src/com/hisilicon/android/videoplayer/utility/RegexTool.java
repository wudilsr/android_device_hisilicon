package com.hisilicon.android.videoplayer.utility;

public final class RegexTool
{
    public final static String NUM = "[0-9]+";

    public final static String MONEY = "[\\d]+|[\\d]+[.]{1}[1-9]{1,2}|[\\d]+[.]{1}[0-9]{1}[1-9]{1}";

    public static boolean isNum(String pValue)
    {
        return pValue.matches(NUM);
    }

    public static boolean isMoney(String pValue)
    {
        return pValue.matches(MONEY);
    }

    public static boolean isNull(Object pObject)
    {
        if (pObject == null)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    public static boolean isZero(int pObject)
    {
        if (pObject == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
