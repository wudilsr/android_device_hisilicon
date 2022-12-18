package com.hisilicon.android.videoplayer.utility;

public class TimeTool
{
    public static String mill2String(int pMillisec)
    {
        long _TotalSec = (pMillisec / 1000);
        int _Hour = (int) (_TotalSec / 3600);
        int _Min = (int) (_TotalSec / 60 % 60);
        int _Sec = (int) (_TotalSec % 60);

        String _StrHour = (_Hour < 10) ? "0" + _Hour : String.valueOf(_Hour);
        String _StrMin = (_Min < 10) ? "0" + _Min : String.valueOf(_Min);
        String _StrSec = (_Sec < 10) ? "0" + _Sec : String.valueOf(_Sec);

        StringBuffer _Buf = new StringBuffer();
        _Buf.append(_StrHour);
        _Buf.append(":");
        _Buf.append(_StrMin);
        _Buf.append(":");
        _Buf.append(_StrSec);
        String _StrTime = _Buf.toString();

        return _StrTime;
    }

    public static int string2Mill(String pHour, String pMinute, String pSecond)
    {
        int _Hour = 0;
        if(!pHour.equals(""))
            _Hour = Integer.parseInt(pHour);
        int _Minute = 0;
        if(!pMinute.equals(""))
            _Minute = Integer.parseInt(pMinute);
        int _Second = 0;
        if(!pSecond.equals(""))
            _Second = Integer.parseInt(pSecond);
        return (_Hour * 3600 + _Minute * 60 + _Second) * 1000;
    }
}