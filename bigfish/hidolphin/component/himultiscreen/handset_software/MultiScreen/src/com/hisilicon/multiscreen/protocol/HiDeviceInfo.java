package com.hisilicon.multiscreen.protocol;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

import org.cybergarage.upnp.Device;
import org.cybergarage.upnp.StateVariable;

import android.os.Parcel;
import android.os.Parcelable;

import com.hisilicon.multiscreen.protocol.utils.HostNetInterface;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.upnputils.MultiScreenUpnpControlPoint;
import com.hisilicon.multiscreen.upnputils.UpnpMultiScreenDeviceInfo;

/**
 * Information of HiMultiSceen device.<br>
 * CN:多屏设备信息类。
 */
public class HiDeviceInfo implements Parcelable
{
    /**
     * Default retry times of add services.<br>
     * CN:添加服务的默认重试次数。
     */
    static final int DEFAULT_RETRY_TIMES_ADD_SERVICES = 1;

    /**
     * IP address.<br>
     * CN:IP地址。
     */
    private String mIpAddress = null;

    /**
     * Name of device.<br>
     * CN:设备名称。
     */
    private String mName = null;

    /**
     * List of services on STB.<br>
     * CN:提供多屏服务的列表。
     */
    private HashMap<String, ServiceInfo> mServices = null;

    /**
     * Default constructor.<br>
     * CN:默认构造函数。
     */
    public HiDeviceInfo()
    {
        mIpAddress = "";
        mName = "";
        mServices = new HashMap<String, ServiceInfo>();
    }

    /**
     * Constructor of device info, to initialize IP of device.<br>
     * CN:构造函数，初始化设备IP地址。
     * @param ip - IP of device.<br>
     *        CN:设备IP地址。
     */
    public HiDeviceInfo(String ip)
    {
        mIpAddress = ip;
        mName = "";
        mServices = new HashMap<String, ServiceInfo>();
    }

    /**
     * Constructor of simple device by Upnp device.
     * @param device
     */
    public HiDeviceInfo(MultiScreenUpnpControlPoint controlPoint)
    {
        Device device = controlPoint.getCurrentDevice();
        if (device == null)
        {
            LogTool.e("Current device is null, fail to construct HiDeviceInfo.");
            return;
        }

        // Get STB IP.
        mIpAddress = HostNetInterface.uri2Ip(device.getLocation());

        // Get STB name.
        mName = device.getFriendlyName();

        // FIXME CN:进入主界面后再同步数据，避免进入按钮卡顿。
        // Add all services of upnp.
        // addAllUpnpServices(controlPoint);
    }

    public boolean resetIp(MultiScreenUpnpControlPoint controlPoint)
    {
        boolean isOK = false;
        // Get STB IP.
        String ipAddress = null;
        // Get STB name.
        String name = null;

        Device device = controlPoint.getCurrentDevice();
        if (device == null)
        {
            LogTool.e("Current device is null, fail to reset ipAddress of HiDeviceInfo.");
            return false;
        }

        ipAddress = HostNetInterface.uri2Ip(device.getLocation());
        name = device.getFriendlyName();
        if (ipAddress == null || "".equals(ipAddress))
        {
            isOK = false;
            LogTool.e("Reset ipAddress of HiDeviceInfo failed.");
        }
        else
        {
            isOK = true;
            setDeviceIP(ipAddress);
            setDeviceName(name);
        }
        return isOK;
    }

    /**
     * Reset device info by Upnp device.<br>
     * CN:重置设备信息。
     * @param controlPoint Upnp control point.
     * @return result of reset device info.
     */
    public boolean resetServices(MultiScreenUpnpControlPoint controlPoint)
    {
        final int RETRY_TIMES = 2;
        boolean isOK = false;

        isOK = resetIp(controlPoint);
        if (isOK)
        {
            // Add all services of UPNP.
            // FIXME CN:重连时，本地服务更新失败使用原有服务信息。
            canSyncInfo(controlPoint, RETRY_TIMES);
        }

        return isOK;
    }

    /**
     * Set device IP.<br>
     * CN:设置设备IP地址。
     * @param ip - IP of device.<br>
     *        CN:设备IP地址。
     */
    public void setDeviceIP(String ip)
    {
        mIpAddress = ip;
    }

    /**
     * Get device IP.<br>
     * CN:返回设备IP地址。
     * @return - IP address.<br>
     *         CN:设备IP地址。
     */
    public String getDeviceIP()
    {
        return mIpAddress;
    }

    /**
     * Set device name.<br>
     * CN:设置设备名称。
     * @param name - name of device.<br>
     *        CN:设备名称。
     */
    public void setDeviceName(String name)
    {
        mName = name;
    }

    /**
     * Get name of device.<br>
     * CN:获取设备名称。
     * @return - device name.<br>
     *         CN:设备名称。
     */
    public String getDeviceName()
    {
        return mName;
    }

    /**
     * Add service of device.<br>
     * CN:新增设备可用服务。
     * @param name - name of service.<br>
     *        CN:服务名称。
     * @param service - service info.<br>
     *        CN:服务信息对象。
     */
    public void addService(String name, ServiceInfo service)
    {
        if (mServices.get(name) != null)
        {
            mServices.get(name).setServiceName(service.getServiceName());
            mServices.get(name).setServicePort(service.getServicePort());
        }
        else
        {
            mServices.put(name, service);
        }
    }

    /**
     * Remove service of device.<br>
     * CN:删除设备可用服务。
     * @param name - name of service.<br>
     *        CN:设备服务名称。
     */
    public void removeService(String name)
    {
        mServices.remove(name);
    }

    /**
     * Get service info by name.<br>
     * CN:获取设备可用服务信息。
     * @param name - name of service.<br>
     *        CN:设备服务名称。
     * @return - service info.<br>
     *         CN:服务信息对象。
     */
    public ServiceInfo getService(String name)
    {
        if (mServices.containsKey(name))
        {
            return mServices.get(name);
        }
        else
        {
            return null;
        }
    }

    /**
     * Get list of services.<br>
     * CN:返回可用服务列表。
     * @return - list of services.<br>
     *         CN:设备服务列表。
     */
    public Collection<ServiceInfo> getServiceList()
    {
        return mServices.values();
    }

    @Override
    public int describeContents()
    {
        return mServices != null ? mServices.size() : 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags)
    {
        dest.writeString(mIpAddress);
        dest.writeString(mName);
        dest.writeInt(mServices.size());
        for (String s : (Set<String>) mServices.keySet())
        {
            dest.writeString(s);
            dest.writeParcelable((Parcelable) mServices.get(s), 0);
        }
    }

    public static final Parcelable.Creator<HiDeviceInfo> CREATOR =
        new Parcelable.Creator<HiDeviceInfo>()
        {
            public HiDeviceInfo createFromParcel(Parcel in)
            {
                return new HiDeviceInfo(in);
            }

            public HiDeviceInfo[] newArray(int size)
            {
                return new HiDeviceInfo[size];
            }
        };

    public void readFromParcel(Parcel in)
    {
        mIpAddress = in.readString();
        mName = in.readString();
        int count = in.readInt();
        for (int i = 0; i < count; i++)
        {
            mServices.put(in.readString(),
                (ServiceInfo) in.readParcelable(ServiceInfo.class.getClassLoader()));
        }
    }

    private HiDeviceInfo(Parcel in)
    {
        mServices = new HashMap<String, ServiceInfo>();
        readFromParcel(in);
    }

    public ServiceInfo get(String key)
    {
        return mServices.get(key);
    }

    public void put(String key, ServiceInfo value)
    {
        mServices.put(key, (ServiceInfo) value);
    }

    public boolean canSyncInfo(MultiScreenUpnpControlPoint controlPoint)
    {
        return addAllUpnpServices(controlPoint);
    }

    public boolean canSyncInfo(MultiScreenUpnpControlPoint controlPoint, int retryTimes)
    {
        return addAllUpnpServices(controlPoint, retryTimes);
    }

    public boolean addVinputService(MultiScreenUpnpControlPoint controlPoint)
    {
        // vinput service.
        boolean retValue =
            addOneUpnpService(controlPoint,
                UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_VINPUT_TYPE,
                UpnpMultiScreenDeviceInfo.VAR_VINPUT_SERVER_URI);
        return retValue;
    }

    public boolean addGsensorService(MultiScreenUpnpControlPoint controlPoint)
    {
        // gsensor service.
        boolean retValue =
            addOneUpnpService(controlPoint,
                UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_GSENSOR_TYPE,
                UpnpMultiScreenDeviceInfo.VAR_GSENSOR_SERVER_URI);
        return retValue;
    }

    public boolean addVIMEService(MultiScreenUpnpControlPoint controlPoint)
    {
        boolean retValue = false;
        // vime control service.
        boolean controlReslut =
            addOneUpnpService(controlPoint,
                UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_VIME_TYPE,
                UpnpMultiScreenDeviceInfo.VAR_VIME_CONTROL_SERVER_URI);

        // vime data service.
        boolean transferReslut =
            addOneUpnpService(controlPoint,
                UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_VIME_TYPE,
                UpnpMultiScreenDeviceInfo.VAR_VIME_DATA_SERVER_URI);
        retValue = controlReslut & transferReslut;
        return retValue;
    }

    /**
     * Add all services from upnp service info with default retry times.<br>
     * @param controlPoint - upnp control point.
     * @return result of add services.
     */
    private boolean addAllUpnpServices(MultiScreenUpnpControlPoint controlPoint)
    {
        return addAllUpnpServices(controlPoint, DEFAULT_RETRY_TIMES_ADD_SERVICES);
    }

    /**
     * Add all services from upnp service info.
     * @param controlPoint - upnp control point.
     * @param retryTimes - max count of retry add services, and range is [1, 4].
     * @return result of add services.
     */
    private boolean addAllUpnpServices(MultiScreenUpnpControlPoint controlPoint, int retryTimes)
    {
        boolean isOK = false;
        boolean vinputOK = false;
        boolean gsensorOK = false;
        boolean vimeOK = false;

        if (retryTimes < 1 || retryTimes > 4)
        {
            // Value range: [1, 4].
            retryTimes = DEFAULT_RETRY_TIMES_ADD_SERVICES;
        }

        if (mServices == null)
        {
            mServices = new HashMap<String, ServiceInfo>();
        }
        else
        {
            // CN:对已存在服务信息不要清空，在原始HashMap上修改。
        }

        // TODO CN:分别获取服务启动结果。
        do
        {
            // vinput service.
            if (!vinputOK)
            {
                vinputOK = addVinputService(controlPoint);
            }

            // gsensor service.
            if (!gsensorOK)
            {
                gsensorOK = addGsensorService(controlPoint);
            }

            // vime service.
            if (!vimeOK)
            {
                vimeOK = addVIMEService(controlPoint);
            }

            isOK = vinputOK & gsensorOK & vimeOK;
            if (isOK)
            {
                break;
            }

            retryTimes--;
        }
        while (retryTimes > -1);

        return isOK;
    }

    /**
     * Add one upnp service by service name and variable.<br>
     * @param device
     * @param serviceName
     * @param VarName
     */
    private boolean addOneUpnpService(MultiScreenUpnpControlPoint controlPoint, String serviceName,
        String VarName)
    {
        StateVariable var = controlPoint.getStateVariable(serviceName, VarName);
        if (var == null)
        {
            LogTool.e("Add service fail: state variable not exist " + VarName);
            return false;
        }
        ServiceInfo sInfo = new ServiceInfo();
        LogTool.d(var.getName() + " = " + var.getValue());
        sInfo.setServiceName(var.getName());
        sInfo.setServicePort(HostNetInterface.uri2port(var.getValue()));
        addService(var.getName(), sInfo);
        return true;
    }
}
