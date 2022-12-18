package com.hisilicon.miracast.model;

import java.io.Serializable;

public final class Hdcp implements Serializable
{
    private String mHdcpName = "";
    private int mHdcpMode = 0;

    public Hdcp()
    {
    }

    public Hdcp(String hdcpName, int hdcpMode)
    {
        this.mHdcpName = hdcpName;
        this.mHdcpMode = hdcpMode;
    }

    public String getHdcpName()
    {
        return mHdcpName;
    }

    public void setHdcpName(String hdcpName)
    {
        this.mHdcpName = hdcpName;
    }

    public int getHdcpMode()
    {
        return mHdcpMode;
    }

    public void setHdcpMode(int hdcpMode)
    {
        this.mHdcpMode = hdcpMode;
    }

    public String toString()
    {
        return "hdcp: mHdcpName= " + mHdcpName + " mHdcpMode= " + mHdcpMode;
    }
}
