/******************************************************************
*
*    CyberUPnP for Java
*
*    Copyright (C) Satoshi Konno 2002
*
*    File: DeviceList.java
*
*    Revision;
*
*    12/04/02
*        - first revision.
*
******************************************************************/

package org.cybergarage.upnp;

import java.util.Vector;

import org.cybergarage.util.Mutex;

public class DeviceList extends Vector
{
    ////////////////////////////////////////////////
    //    Constants
    ////////////////////////////////////////////////

    public final static String ELEM_NAME = "deviceList";

    ////////////////////////////////////////////////
    //    Constructor
    ////////////////////////////////////////////////

    public DeviceList()
    {
    }

    ////////////////////////////////////////////////
    //    Methods
    ////////////////////////////////////////////////

    public Device getDevice(int n)
    {
        if (n < size())
        {
            return (Device) get(n);
        }
        else
        {
            return null;
        }
    }

    // Begin modify for MultiScreen.
    private Mutex mutex = new Mutex();

    public void lock()
    {
        mutex.lock();
    }

    public void unlock()
    {
        mutex.unlock();
    }
    // End modify for MultiScreen.
}
