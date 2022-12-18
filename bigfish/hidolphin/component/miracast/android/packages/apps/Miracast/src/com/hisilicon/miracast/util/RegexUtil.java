package com.hisilicon.miracast.util;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public final class RegexUtil
{
    public static final String REGEX_IP = "(\\d{1,3}\\.){3}\\d{1,3}";

    public static boolean isIpAddr(String value)
    {
        return value.matches(REGEX_IP);
    }

    public static String findIpAddr(String value)
    {
        String ret = "";
        final Matcher m = Pattern.compile(REGEX_IP).matcher(value);
        if (m.find())
        {
            ret = m.group();
        }

        return ret;
    }
}
