package com.hisilicon.multiscreen.controller;

import org.cybergarage.upnp.Action;

import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.upnputils.MultiScreenUpnpControlPoint;
import com.hisilicon.multiscreen.upnputils.UpnpMultiScreenDeviceInfo;

public class RemoteAPPUpnpController
{
    /**
     * Control point.<br>
     */
    private MultiScreenUpnpControlPoint mControlPoint = null;

    /**
     * RemoteAPPUpnpController's construct method <br>
     */
    public RemoteAPPUpnpController()
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
     * Start remote app server. <br>
     * @return
     */
    public boolean startRemoteApp()
    {
        boolean result = false;
        Action startRemoteAppAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_REMOTE_APP_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_REMOTE_APP_START);

        if (startRemoteAppAct == null)
        {
            LogTool.e("startRemoteAppAct is null");
            return false;
        }

        result = mControlPoint.postAction(startRemoteAppAct);
        return result;
    }

    /**
     * Stop remote app server. <br>
     * @return
     */
    public boolean stopRemoteApp()
    {
        boolean result = false;
        Action stopRemoteAppAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_VIME_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_REMOTE_APP_STOP);

        if (stopRemoteAppAct == null)
        {
            LogTool.e("stopRemoteAppAct is null");
            return false;
        }

        result = mControlPoint.postAction(stopRemoteAppAct);
        return result;
    }

}
