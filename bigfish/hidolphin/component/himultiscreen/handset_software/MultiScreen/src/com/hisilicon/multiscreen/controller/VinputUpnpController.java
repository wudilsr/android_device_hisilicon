package com.hisilicon.multiscreen.controller;

import org.cybergarage.upnp.Action;

import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.upnputils.MultiScreenUpnpControlPoint;
import com.hisilicon.multiscreen.upnputils.UpnpMultiScreenDeviceInfo;

public class VinputUpnpController
{
    /**
     * Control point.<br>
     */
    private MultiScreenUpnpControlPoint mControlPoint = null;

    /**
     * VinputUpnpController's construct method <br>
     */
    public VinputUpnpController()
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
     * Start vinput server.<br>
     * @return
     */
    public boolean startVinput()
    {
        Action startVinputAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_VINPUT_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_VINPUT_START);
        if (startVinputAct == null)
        {
            LogTool.e("StartVinputAct is null");
            return false;
        }
        return mControlPoint.postAction(startVinputAct);
    }

    /**
     * Stop vinput server.<br>
     * @return
     */
    public boolean stopVinput()
    {
        Action stopVinputAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_VINPUT_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_VINPUT_STOP);
        if (stopVinputAct == null)
        {
            LogTool.e("stopVinputAct is null");
            return false;
        }
        return mControlPoint.postAction(stopVinputAct);
    }

}
