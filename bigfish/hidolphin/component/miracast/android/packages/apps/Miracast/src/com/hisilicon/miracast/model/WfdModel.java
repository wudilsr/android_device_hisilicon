package com.hisilicon.miracast.model;

import java.io.Serializable;

public final class WfdModel implements Serializable
{
    private static final long serialVersionUID = 7425036523931265498L;

    private boolean mIsWifiP2pEnabled = false;
    private boolean mIsWifiP2pConnecting = false;
    private boolean mIsWifiP2pConnected = false;
    private boolean mIsWfdStarted = false;
    private boolean mIsSearching = false;
    private boolean mIsExitingFromMiracast = false;

    private String mDeviceName = "";
    private String mDeviceAddr = "";
    private boolean mIsDeviceGo = false;
    private String mGoIpAddr = "";

    private String mSourceIpAddr = "";

    private int mLostPacket = 0;

    public boolean isWifiP2pEnabled()
    {
        return mIsWifiP2pEnabled;
    }

    public void setWifiP2pEnabled(boolean isWifiP2pEnabled)
    {
        mIsWifiP2pEnabled = isWifiP2pEnabled;
    }

    public boolean isWifiP2pConnecting()
    {
        return mIsWifiP2pConnecting;
    }

    public void setWifiP2pConnecting(boolean isWifiP2pConnecting)
    {
        mIsWifiP2pConnecting = isWifiP2pConnecting;
    }

    public boolean isWifiP2pConnected()
    {
        return mIsWifiP2pConnected;
    }

    public void setWifiP2pConnected(boolean isWifiP2pConnected)
    {
        mIsWifiP2pConnected = isWifiP2pConnected;
    }

    public boolean isExitingFromMiracast()
    {
        return mIsExitingFromMiracast;
    }

    public void setExitingFromMiracast(boolean isExiting)
    {
        mIsExitingFromMiracast = isExiting;
    }

    public boolean isWfdStarted()
    {
        return mIsWfdStarted;
    }

    public void setWfdStarted(boolean isWfdStarted)
    {
        mIsWfdStarted = isWfdStarted;
    }

    public boolean isSearching()
    {
        return mIsSearching;
    }

    public void setSearching(boolean isSearching)
    {
        mIsSearching = isSearching;
    }

    public String getDeviceName()
    {
        return mDeviceName;
    }

    public void setDeviceName(String deviceName)
    {
        mDeviceName = deviceName;
    }

    public String getDeviceAddr()
    {
        return mDeviceAddr;
    }

    public void setDeviceAddr(String deviceAddr)
    {
        mDeviceAddr = deviceAddr;
    }

    public boolean isDeviceGo()
    {
        return mIsDeviceGo;
    }

    public void setDeviceGo(boolean isDeviceGo)
    {
        mIsDeviceGo = isDeviceGo;
    }

    public String getGoIpAddr()
    {
        return mGoIpAddr;
    }

    public void setGoIpAddr(String goIpAddr)
    {
        mGoIpAddr = goIpAddr;
    }

    public String getSourceIpAddr()
    {
        return mSourceIpAddr;
    }

    public void setSourceIpAddr(String sourceIpAddr)
    {
        mSourceIpAddr = sourceIpAddr;
    }

    public int getLostPacket()
    {
        return mLostPacket;
    }

    public void setLostPacket(int lostPacket)
    {
        mLostPacket = lostPacket;
    }
}
