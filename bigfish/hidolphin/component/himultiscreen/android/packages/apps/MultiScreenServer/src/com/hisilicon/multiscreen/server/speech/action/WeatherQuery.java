package com.hisilicon.multiscreen.server.speech.action;

import java.util.HashMap;
import java.util.Map;

public class WeatherQuery
{

    private Map<String, String> mCityCode = new HashMap<String, String>();

    public WeatherQuery()
    {
        mCityCode.put("北京", "101010100");
        mCityCode.put("上海", "101020100");
        mCityCode.put("深圳", "101280601");
        mCityCode.put("广州", "101280101");
        mCityCode.put("东莞", "101281601");
        mCityCode.put("成都", "101270101");
        mCityCode.put("绵阳", "101270401");
        mCityCode.put("重庆", "101040100");
        mCityCode.put("天津", "101030100");
        mCityCode.put("西安", "101110101");
        mCityCode.put("南京", "101190101");
        mCityCode.put("苏州", "101190401");
        mCityCode.put("海南", "101150401");
        mCityCode.put("厦门", "101230201");
        mCityCode.put("合肥", "101220101");
        mCityCode.put("黄山", "101221001");
        mCityCode.put("杭州", "101210101");
        mCityCode.put("金华", "101210901");
        mCityCode.put("大理", "101290201");
        mCityCode.put("丽江", "101291401");
        mCityCode.put("武汉", "101200101");
        mCityCode.put("张家界", "101251101");

    }

    public String getCodeByCity(String cityName)
    {
        return mCityCode.get(cityName);
    }
}
