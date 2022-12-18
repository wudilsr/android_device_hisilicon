package com.hisilicon.android.videoplayer.model;

public class ModelSubtitleInfo
{
    private String mSubtitleConfigPath;

    private int mSubtitleFontSize = 25;

    private String mSubtitleFontColor = "0x00";

    private int mSubtitleFontPosition = 0;

    private int mSubtitleFontStyle = -1;

    private int mSubtitleFontSpace = -1;

    private int mSubtitleFontLineSpace = -1;

    private int mSubtitleTimeSync = -1;

    private int mSubtitleDisable = -1;

    public String getSubtitleConfigPath()
    {
        return mSubtitleConfigPath;
    }

    public void setSubtitleConfigPath(String pSubtitleConfigPath)
    {
        mSubtitleConfigPath = pSubtitleConfigPath;
    }

    public int getSubtitleFontSize()
    {
        return mSubtitleFontSize;
    }

    public void setSubtitleFontSize(int pSubtitleFontSize)
    {
        mSubtitleFontSize = pSubtitleFontSize;
    }

    public String getSubtitleFontColor()
    {
        return mSubtitleFontColor;
    }

    public void setSubtitleFontColor(String pSubtitleFontColor)
    {
        mSubtitleFontColor = pSubtitleFontColor;
    }

    public int getSubtitleFontPosition()
    {
        return mSubtitleFontPosition;
    }

    public void setSubtitleFontPosition(int pSubtitleFontPosition)
    {
        mSubtitleFontPosition = pSubtitleFontPosition;
    }

    public int getSubtitleFontStyle()
    {
        return mSubtitleFontStyle;
    }

    public void setSubtitleFontStyle(int pSubtitleFontStyle)
    {
        mSubtitleFontStyle = pSubtitleFontStyle;
    }

    public int getSubtitleFontSpace()
    {
        return mSubtitleFontSpace;
    }

    public void setSubtitleFontSpace(int pSubtitleFontSpace)
    {
        mSubtitleFontSpace = pSubtitleFontSpace;
    }

    public int getSubtitleFontLineSpace()
    {
        return mSubtitleFontLineSpace;
    }

    public void setSubtitleFontLineSpace(int pSubtitleFontLineSpace)
    {
        mSubtitleFontLineSpace = pSubtitleFontLineSpace;
    }

    public int getSubtitleTimeSync()
    {
        return mSubtitleTimeSync;
    }

    public void setSubtitleTimeSync(int pSubtitleTimeSync)
    {
        mSubtitleTimeSync = pSubtitleTimeSync;
    }

    public int getSubtitleDisable()
    {
        return mSubtitleDisable;
    }

    public void setSubtitleDisable(int pSubtitleDisable)
    {
        mSubtitleDisable = pSubtitleDisable;
    }
}
