package com.hisilicon.multiscreen.upnputils;

import org.cybergarage.upnp.Device;

/**
 * Interface of control point listener.
 */
public interface IUpnpControlPointListener
{
    /**
     * Reave callback.
     */
    void reavedNotify();

    /**
     * STB leaved callback.
     */
    void stbLeaveNotify();

    /**
     * Device add.
     */
    void originalListAdd(Device device);

    /**
     * Device remove.
     */
    void originalListRemoved(Device device);

    /**
     * stb suspend.
     */
    void stbSuspendNotify();
}
