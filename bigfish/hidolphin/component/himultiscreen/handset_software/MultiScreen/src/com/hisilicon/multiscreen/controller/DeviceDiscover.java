package com.hisilicon.multiscreen.controller;

import java.net.InetAddress;
import java.util.Collections;
import java.util.Comparator;

import org.cybergarage.upnp.Device;
import org.cybergarage.upnp.DeviceList;
import org.cybergarage.upnp.device.ST;

import android.os.Process;

import com.hisilicon.multiscreen.protocol.utils.HostNetInterface;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.upnputils.MultiScreenDeviceList;
import com.hisilicon.multiscreen.upnputils.MultiScreenUpnpControlPoint;
import com.hisilicon.multiscreen.upnputils.UpnpMultiScreenDeviceInfo;

public class DeviceDiscover
{
    /**
     * Control point.<br>
     */
    private MultiScreenUpnpControlPoint mControlPoint = null;

    /**
     * MultiScreen Device list<br>
     */
    private MultiScreenDeviceList mDeviceList = null;

    private DeviceList mOriginalList = null;

    private Runnable mStartControlPointRunnable = null;

    /**
     * DeviceDiscover's construct method <br>
     */
    public DeviceDiscover()
    {
        super();
        mControlPoint = MultiScreenUpnpControlPoint.getInstance();
        mDeviceList = new MultiScreenDeviceList();
        mStartControlPointRunnable = new Runnable()
        {
            public void run()
            {
                mControlPoint.startControl();
            }
        };
    }

    public void initSearch()
    {
        if (mControlPoint != null)
        {
            Thread localThread = new Thread(mStartControlPointRunnable);
            localThread.setPriority(Process.THREAD_PRIORITY_LESS_FAVORABLE);
            localThread.setName("initSearchThread");
            localThread.start();
        }
        else
        {
            LogTool.e("mControlPoint is null.");
        }
    }

    public void finalizeSearch()
    {
        if (mControlPoint != null)
        {
            mControlPoint.stopControl();
        }
        else
        {
            LogTool.e("mControlPoint is null.");
        }
    }

    /**
     * Send M_SEARCH.<br>
     * CN:发送搜索消息。
     */
    public void msearch()
    {
        mControlPoint.search(ST.MULTISCREEN_DEVICE);
    }

    /**
     * Clear list and search.<br>
     * CN:清空列表并搜索。
     */
    public void reSearch()
    {
        clearOriginalList();
        msearch();
    }

    public void removeDevice(Device device)
    {
        mDeviceList.lock();
        for (int i = 0; i < mDeviceList.size(); i++)
        {
            if (mDeviceList.getDevice(i).getUDN().equals(device.getUDN()))
            {
                // LogTool.e("device.getUDN() = " + device.getUDN());
                mDeviceList.remove(i);
            }
        }
        mDeviceList.unlock();
    }

    /**
     * Clear original device list.<br>
     * CN:清空原始列表信息。
     */
    public void clearOriginalList()
    {
        mControlPoint.removeAlldevice();
    }

    /**
     * Returns if the original list has no device, a size of zero.<br>
     * CN:返回原始设备列表是否为空。
     * @return true if the original list has no device, false otherwise.
     */
    public boolean isOriginalListEmpty()
    {
        mOriginalList = mControlPoint.getDeviceList();
        return mOriginalList.isEmpty();
    }

    /**
     * Clear all device list.<br>
     * CN:清空列表信息。
     * @deprecated CN:DeviceList清空，用户界面上的列表就失效了。
     * @see clearOriginalList()
     */
    public void clearAllList()
    {
        mControlPoint.removeAlldevice();
        mDeviceList.clear();
    }

    /**
     * Get ordering device list.<br>
     */
    public void syncOrderingList()
    {
        filterMultiScreenList();
        sortMultiScreenDeviceList(mDeviceList);
    }

    public void removeCannotAccessDevice(Device device)
    {
        mControlPoint.removeCannotAccessDevice(device);
        msearch();
    }

    public MultiScreenDeviceList getDeviceList()
    {
        return mDeviceList;
    }

    /**
     * Get device by uuid.<br>
     * CN:通过uuid获取设备。
     * @param uuid
     * @return true if it get device successfully.
     */
    public Device getDeviceByUUID(String uuid)
    {
        mOriginalList = mControlPoint.getDeviceList();
        mOriginalList.lock();

        for (int i = 0; i < mOriginalList.size(); i++)
        {
            if (mOriginalList.getDevice(i).isDevice(uuid))
            {
                if (mOriginalList.getDevice(i).getDeviceType()
                    .startsWith(UpnpMultiScreenDeviceInfo.MULTISCREEN_DEVICE_TYPE))
                {
                    mOriginalList.unlock();
                    return mOriginalList.getDevice(i);
                }
            }
        }

        mOriginalList.unlock();
        return null;
    }

    /**
     * Get device by IP.<br>
     * CN:通过IP获取设备。
     * @param inetAddress
     * @return true if it get device successfully.
     */
    public Device getDeviceByIP(InetAddress inetAddress)
    {
        String ipAddress = inetAddress.getHostAddress();
        mOriginalList = mControlPoint.getDeviceList();
        mOriginalList.lock();

        for (int i = 0; i < mOriginalList.size(); i++)
        {
            if (ipAddress.equals(HostNetInterface.uri2Ip(mOriginalList.getDevice(i).getLocation())))
            {
                if (mOriginalList.getDevice(i).getDeviceType()
                    .startsWith(UpnpMultiScreenDeviceInfo.MULTISCREEN_DEVICE_TYPE))
                {
                    mOriginalList.unlock();
                    return mOriginalList.getDevice(i);
                }
            }
        }

        mOriginalList.unlock();
        return null;
    }

    /**
     * Get HiMultiScreen device list.<br>
     */
    @SuppressWarnings("unchecked")
    private void filterMultiScreenList()
    {
        mDeviceList.lock();
        mDeviceList.clear();
        mOriginalList = mControlPoint.getDeviceList();

        for (int i = 0; i < mOriginalList.size(); i++)
        {
            if (mOriginalList.getDevice(i).getDeviceType()
                .startsWith(UpnpMultiScreenDeviceInfo.MULTISCREEN_DEVICE_TYPE))
            {
                mDeviceList.add(mOriginalList.getDevice(i));
            }
        }
        mDeviceList.unlock();
    }

    /**
     * Class for implement the comparator.<br>
     */
    class DeviceListComparator implements Comparator<Device>
    {

        @Override
        public int compare(Device lDevice, Device rDevice)
        {
            if (lDevice.getLocation().compareTo(rDevice.getLocation()) > 0)
            {
                return 1;
            }
            else if (lDevice.getLocation().compareTo(rDevice.getLocation()) < 0)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
    }

    /**
     * Sort the multiScreen device List.<br>
     * @param deviceList
     */
    @SuppressWarnings("unchecked")
    private void sortMultiScreenDeviceList(MultiScreenDeviceList deviceList)
    {
        DeviceListComparator devComparator = new DeviceListComparator();
        deviceList.lock();
        Collections.sort(deviceList, devComparator);
        deviceList.unlock();
    }
}
