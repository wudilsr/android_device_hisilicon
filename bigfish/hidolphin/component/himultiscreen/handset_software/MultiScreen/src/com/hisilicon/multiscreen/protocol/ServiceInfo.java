package com.hisilicon.multiscreen.protocol;

import android.os.Parcel;
import android.os.Parcelable;

/**
 * Device service information class, used for creating a map between service
 * name and port.<br>
 * CN:设备服务信息类，用于服务名称与端口的映射.
 */
public class ServiceInfo implements Parcelable
{

    /**
     * Service name.<br>
     * CN:服务名称.
     */
    private String mServiceName;

    /**
     * Service port.<br>
     * CN:服务端口.
     */
    private int mServicePort;

    /**
     * Realize the CREATOR, deserialize objects.<br>
     * CN:实现CREATOR,反序列化对象。
     */
    public static final Parcelable.Creator<ServiceInfo> CREATOR =
        new Parcelable.Creator<ServiceInfo>()
        {
            @Override
            public ServiceInfo createFromParcel(Parcel source)
            {
                ServiceInfo p = new ServiceInfo();
                p.setServiceName(source.readString());
                p.setServicePort(source.readInt());
                return p;
            }

            @Override
            public ServiceInfo[] newArray(int size)
            {
                return new ServiceInfo[size];
            }
        };

    @Override
    public int describeContents()
    {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags)
    {
        dest.writeString(mServiceName);
        dest.writeInt(mServicePort);
    }

    /**
     * Set service name.<br>
     * CN:设置服务名称.
     * @param name - service name.<br>
     *        CN:服务名称.
     */
    public void setServiceName(String name)
    {
        mServiceName = name;
    }

    /**
     * Set service port.<br>
     * CN:设置服务端口号.
     * @param port - service port.<br>
     *        CN:服务端口号.
     */
    public void setServicePort(int port)
    {
        mServicePort = port;
    }

    /**
     * Get service name.<br>
     * CN:获取服务名称.
     * @return - service name.<br>
     *         CN:服务名称.
     */
    public String getServiceName()
    {
        return mServiceName;
    }

    /**
     * Get service port.<br>
     * CN:获取服务端口号.
     * @return - service port.<br>
     *         CN:服务端口号.
     */
    public int getServicePort()
    {
        return mServicePort;
    }
}
