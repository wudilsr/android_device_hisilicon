package com.hisilicon.multiscreen.protocol.message;

import java.io.Serializable;

/**
 * Application information of device.
 * CN:设备的安卓应用程序信息类。
 */
public class AppInfo implements Serializable
{
    private static final long serialVersionUID = 2225651111100652973L;

    private String mAppName = "";

    private String mPackageName = "";

    private int mIndex = 0;

    private byte[] mIcon = null;

    /**
     * Set Package Name.<br>
     * CN:设置应用程序包名.
     * @param name - Application Package Name.<br>
     * CN:应用程序包名.
     */
    public void setPackageName(String name)
    {
        mPackageName = name;
    }

    /**
     * Get Package Name.<br>
     * CN:获取应用程序包名.
     * @return - Application Package Name.<br>
     * CN:应用程序包名.
     */
    public String getPackageName()
    {
        return mPackageName;
    }

    /**
     * Set application name.<br>
     * CN:设置应用程序名.
     * @param name - application name.<br>
     * CN:应用程序名
     */
    public void setAppName(String name)
    {
        mAppName = name;
    }

    /**
     * Get application name.<br>
     * CN:获取应用程序名.
     * @return - application name.<br>
     * CN:应用程序名
     */
    public String getAppName()
    {
        return mAppName;
    }

    /**
     * Set Package Icon.<br>
     * CN:设置应用程序图标.
     * @param icon - byte array of Icon.<br>
     * CN:图标的字节数组.
     */
    public void setPackageIcon(byte[] icon)
    {
        this.mIcon = new byte[icon.length];
        this.mIcon = icon;
    }

    /**
     * 获取应用程序图标
     * @return - 图标的字节数组
     */
    public byte[] getPackageIcon()
    {
        return mIcon;
    }

    /**
     * Set application Index.<br>
     * CN:设置应用程序编号.
     * @param index - application Index.<br>
     * CN:应用程序编号
     */
    public void setPackageIndex(int index)
    {
        this.mIndex = index;
    }

    /**
     * Get application Index.<br>
     * CN:获取应用程序编号.
     * @return - application Index.<br>
     * CN:应用程序编号.
     */
    public int getPackageIndex()
    {
        return mIndex;
    }
}
