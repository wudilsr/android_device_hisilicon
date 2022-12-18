package com.hisilicon.android.videoplayer.utility;

import java.util.ArrayList;
import java.util.List;

public class CommonTool
{
    public static List<String> stringsToList(String[] pStrings)
    {
        List<String> _List = new ArrayList<String>();

        for (int i = 0; i < pStrings.length; i++)
        {
            _List.add(pStrings[i]);
        }

        return _List;
    }
}
