package com.hisilicon.multiscreen.controller;

import org.cybergarage.upnp.Action;
import org.cybergarage.upnp.Device;

import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.protocol.ClientInfo;
import com.hisilicon.multiscreen.protocol.utils.HostNetInterface;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.upnputils.MultiScreenUpnpControlPoint;
import com.hisilicon.multiscreen.upnputils.UpnpMultiScreenDeviceInfo;

/**
 * VIME UPNP controller class.
 */
public class VIMEUpnpController
{
    /**
     * Control point.<br>
     */
    private MultiScreenUpnpControlPoint mControlPoint = null;

    /**
     * VIMEUpnpController's construct method <br>
     */
    public VIMEUpnpController()
    {
        super();
        mControlPoint = MultiScreenControlService.getInstance().getControlPoint();
    }

    /**
     * Reset control point.
     */
    public void reset()
    {
        mControlPoint = MultiScreenControlService.getInstance().getControlPoint();
    }

    /**
     * Start VIME upnp controller <br>
     */
    public void start()
    {
        setVIMEParameter(ClientInfo.DEFAULT_VIME_CLIENT_CONTROL_PORT);
        startVIMEControlServer();
    }

    /**
     * Stop VIME upnp controller <br>
     */
    public void stop()
    {
        stopVIMEControlServer();
    }

    /**
     * Set VIME's parameter through upnp.<br>
     * @param port - VIME's control port.<br>
     * @return
     */
    public boolean setVIMEParameter(int port)
    {
        boolean result = false;
        Action setVIMEParameterAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_VIME_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_VIME_SET_PARAMETER);
        if (setVIMEParameterAct == null)
        {
            LogTool.e("setVIMEParameterAct is null");
            return false;
        }

        Device device = mControlPoint.getCurrentDevice();
        if (device == null)
        {
            LogTool.e("Current device is null, fail to set VIME parameter.");
            return false;
        }
        String clientIP =
            HostNetInterface.getSameSegmentIp(HostNetInterface.uri2Ip(device.getLocation()));
        String parameter =
            HostNetInterface.ipAndPort2Uri(ClientInfo.MODULE_VIME_HEAD, clientIP, port);
        setVIMEParameterAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_VIME_PARAMETER,
            parameter);
        result = mControlPoint.postAction(setVIMEParameterAct);
        return result;
    }

    /**
     * Start VIME UPNP control server. <br>
     * @return
     */
    public boolean startVIMEControlServer()
    {
        boolean result = false;
        Action startVIMEControlServerAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_VIME_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_VIME_START);
        if (startVIMEControlServerAct == null)
        {
            LogTool.e("startVIMEControlServerAct is null");
            return false;
        }
        result = mControlPoint.postAction(startVIMEControlServerAct);
        return result;
    }

    /**
     * Stop VIME UPNP control server. <br>
     * @return
     */
    public boolean stopVIMEControlServer()
    {
        boolean result = false;
        Action stopVIMEControlServerAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_VIME_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_VIME_STOP);

        if (stopVIMEControlServerAct == null)
        {
            LogTool.e("stopVIMEControlServerAct is null");
            return result;
        }

        result = mControlPoint.postAction(stopVIMEControlServerAct);
        return result;
    }

}
