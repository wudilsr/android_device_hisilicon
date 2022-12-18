package com.hisilicon.multiscreen.upnputils;

import org.cybergarage.upnp.DeviceList;
import org.cybergarage.util.Mutex;

/**
 * MultiScreen Device list <br>
 */
public class MultiScreenDeviceList extends DeviceList
{

    /**
     *
     */
    private static final long serialVersionUID = 2739688970776699423L;

    private Mutex mutex = new Mutex();

    public void lock()
    {
        mutex.lock();
    }

    public void unlock()
    {
        mutex.unlock();
    }

}
