package com.hisilicon.multiscreen.controller;

import org.cybergarage.upnp.Action;

import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.upnputils.MultiScreenUpnpControlPoint;
import com.hisilicon.multiscreen.upnputils.UpnpMultiScreenDeviceInfo;

/**
 * Class for control Mirror through upnp <br>
 */
public class MirrorUpnpController
{
    /**
     * MultiScreen upnp control point.<br>
     */
    private MultiScreenUpnpControlPoint mControlPoint = null;

    /**
     * MirrorUpnpController's construct method <br>
     */
    public MirrorUpnpController()
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
     * Try to set mirror parameter in some times.<br>
     * @param times
     * @return
     */
    public boolean setMirrorParameter(String MirrorParameter, int times)
    {
        boolean isOK = false;
        if (times <= 0)
        {
            times = 1;
        }

        do
        {
            times--;
            isOK = setMirrorParameter(MirrorParameter);
        }
        while ((isOK == false) && (times > 0));

        return isOK;
    }

    /**
     * Try to start mirror in some times.<br>
     * @param times
     * @return
     */
    public boolean startMirror(int times)
    {
        boolean isOK = false;
        if (times <= 0)
        {
            times = 1;
        }

        do
        {
            times--;
            isOK = startMirror();
        }
        while ((isOK == false) && (times > 0));

        return isOK;
    }

    /**
     * Try to stop mirror in some times.<br>
     * @param times
     * @return
     */
    public boolean stopMirror(int times)
    {
        boolean isOK = false;
        if (times <= 0)
        {
            times = 1;
        }

        do
        {
            times--;
            isOK = stopMirror();
        }
        while ((isOK == false) && (times > 0));

        return isOK;
    }

    private boolean setMirrorParameter(String MirrorParameter)
    {
        Action setMirrorParameterAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_MIRROR_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_MIRROR_SET_PARAMETER);
        if (setMirrorParameterAct == null)
        {
            LogTool.e("setMirrorParameterAct not found");
            return false;
        }
        setMirrorParameterAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_REMOTE_ID,
            mControlPoint.getRemoteId());
        setMirrorParameterAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_MIRROR_PARAMETER,
            MirrorParameter);
        if (setMirrorParameterAct.postControlAction() == false)
            return false;
        return true;
    }

    private boolean startMirror()
    {
        Action startMirrorAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_MIRROR_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_MIRROR_START);
        if (startMirrorAct == null)
        {
            LogTool.e("StartMirrorAct not found");
            return false;
        }
        return mControlPoint.postAction(startMirrorAct);
    }

    private boolean stopMirror()
    {
        Action stopMirrorAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_MIRROR_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_MIRROR_STOP);
        if (stopMirrorAct == null)
        {
            LogTool.e("StopMirrorAct not found");
            return false;
        }
        return mControlPoint.postAction(stopMirrorAct);
    }
}
