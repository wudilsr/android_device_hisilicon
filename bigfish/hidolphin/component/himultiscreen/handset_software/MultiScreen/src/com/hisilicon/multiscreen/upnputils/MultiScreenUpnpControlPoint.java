package com.hisilicon.multiscreen.upnputils;

import java.util.Timer;
import java.util.TimerTask;

import org.cybergarage.upnp.Action;
import org.cybergarage.upnp.ControlPoint;
import org.cybergarage.upnp.Device;
import org.cybergarage.upnp.DeviceList;
import org.cybergarage.upnp.Service;
import org.cybergarage.upnp.StateVariable;
import org.cybergarage.upnp.UPnP;
import org.cybergarage.upnp.device.DeviceChangeListener;
import org.cybergarage.upnp.device.NotifyListener;
import org.cybergarage.upnp.device.ST;
import org.cybergarage.upnp.device.SearchResponseListener;
import org.cybergarage.upnp.event.EventListener;
import org.cybergarage.upnp.event.Subscription;
import org.cybergarage.upnp.ssdp.SSDPPacket;
import org.cybergarage.util.Debug;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

public class MultiScreenUpnpControlPoint extends ControlPoint implements NotifyListener,
    EventListener, SearchResponseListener, DeviceChangeListener
{
    /**
     * Default remote id.<br>
     * CN:STB没有客户端接入时，控制点ID值，表示服务端处于可以接入状态。
     */
    public static final String REMOTE_ID_CAN_ACCESS = "0.0.0.0";

    /**
     * Suspend remote id.<br>
     * The client will exit.<br>
     * CN:STB处于浅待机状态时，控制点ID值，客户端检测到该变量值则立刻退出。
     */
    public static final String REMOTE_ID_DEVICE_SUSPEND = "0.0.0.1";

    /**
     * The remote id means STB is manual off.<br>
     * The client will exit.<br>
     * CN:STB多屏服务手动关闭时，控制点ID值，客户端检测到该变量值则立刻退出。
     */
    public static final String REMOTE_ID_STB_MANUAL_OFF = "REMOTE_ID_STB_MANUAL_OFF";

    /**
     * True if UPNP control point is started.<br>
     */
    public static boolean mIsStarted = false;

    /**
     * Local control point's id.<br>
     */
    private String mRemoteID = null;

    /**
     * Current connect device.<br>
     */
    private Device mCurrentDevice = null;

    /**
     * Instance of MultiScreen ControlPoint.
     */
    private static MultiScreenUpnpControlPoint mMultiScreenControlPoint = null;

    /**
     * Original device list of control point.<br>
     */
    private DeviceList mOriginalList = null;

    /**
     * Listener of control point events.<br>
     */
    private IUpnpControlPointListener mUpnpControlPointListener = null;

    /**
     * Timer of renew subscriber.<br>
     * CN:重置Access事件订阅的计时器。
     */
    private Timer mRenewSubscriberTimer = null;

    private class RenewSubscriberTask extends TimerTask
    {
        public void run()
        {
            renewSubscriber();
        }
    }

    private static final int SSDP_PORT_FOR_MULTISCREEN = 8009;

    private static final int HTTP_PORT_FOR_MULTISCREEN = 8060;

    /**
     * Constructor.
     */
    public MultiScreenUpnpControlPoint()
    {
        UPnP.setEnable(UPnP.USE_ONLY_IPV4_ADDR);
        UPnP.setDisable(UPnP.USE_LOOPBACK_ADDR);
        UPnP.setDisable(UPnP.USE_ONLY_IPV6_ADDR);
        Debug.off();
        this.setSSDPPort(SSDP_PORT_FOR_MULTISCREEN);
        this.setHTTPPort(HTTP_PORT_FOR_MULTISCREEN);
    }

    @Override
    public void deviceSearchResponseReceived(SSDPPacket ssdpPacket)
    {
        // LogTool.d("deviceSearchResponseReceived");
    }

    @Override
    public void eventNotifyReceived(String uuid, long seq, String name, String value)
    {
        if (name.equals(UpnpMultiScreenDeviceInfo.VAR_ACCESS_REMOTE_LIST))
        {
            if (!value.equals(mRemoteID))
            {
                LogTool.e("RemoteID notify received");
                LogTool.d("My RemoteID is " + mRemoteID + ", STB RemoteID is " + value);

                if (mUpnpControlPointListener == null)
                {
                    LogTool.e("UpnpControlPointListener has been set null.");
                }
                else if (value.equals(REMOTE_ID_CAN_ACCESS))
                {
                    LogTool.d("STB can access");
                }
                else if (value.equals(REMOTE_ID_STB_MANUAL_OFF))
                {
                    LogTool.d("STB manual off.");
                    mUpnpControlPointListener.stbLeaveNotify();
                }
                else if (value.equals(REMOTE_ID_DEVICE_SUSPEND))
                {
                    LogTool.d("STB suspend.");
                    mUpnpControlPointListener.stbSuspendNotify();
                }
                else
                {
                    LogTool.e("STB is reaved");
                    mUpnpControlPointListener.reavedNotify();
                }
            }
        }
    }

    @Override
    public void deviceNotifyReceived(SSDPPacket ssdpPacket)
    {
        // TODO Auto-generated method stub
        // LogTool.d("deviceNotifyReceived");
        // LogTool.d("NT:  "+ssdpPacket.getNT());
        // LogTool.d("nts:  "+ssdpPacket.getNTS());
        // LogTool.d("st: " +ssdpPacket.getST());
        // LogTool.d("usn:  "+ssdpPacket.getUSN());
        // LogTool.d("location: " + ssdpPacket.getLocation());
        // if ( ssdpPacket.getST().equalsIgnoreCase(MULTISCREEN_DEVICE_TYPE) &&
        // ssdpPacket.isAlive() )
        // {
        // LogTool.e("alive notify add");
        // addMultiScreenDevice(ssdpPacket.getUSN());
        // return;
        // }
        //
        // if (ssdpPacket.isByeBye())
        // {
        // LogTool.d("byebye notify remove");
        // removeMultiScreenDevice(ssdpPacket.getUSN());
        // return;
        // }
    }

    @Override
    public void deviceAdded(Device dev)
    {
        // LogTool.d("add device" + HostNetInterface.uri2Ip(dev.getLocation()));
        if (mUpnpControlPointListener != null)
        {
            // LogTool.d("add DeviceType =" + dev.getDeviceType());
            if (dev.getDeviceType().equals(UpnpMultiScreenDeviceInfo.MULTISCREEN_DEVICE_TYPE))
            {
                mUpnpControlPointListener.originalListAdd(dev);
            }
        }
    }

    @Override
    public void deviceRemoved(Device dev)
    {
        // LogTool.d("remove device " +
        // HostNetInterface.uri2Ip(dev.getLocation()));
        if (mUpnpControlPointListener != null)
        {
            // LogTool.d("remove DeviceType =" + dev.getDeviceType());
            if (dev.getDeviceType().equals(UpnpMultiScreenDeviceInfo.MULTISCREEN_DEVICE_TYPE))
            {
                mUpnpControlPointListener.originalListRemoved(dev);
            }
        }
    }

    @Override
    public void deviceRefreshed(Device dev)
    {
        if (mUpnpControlPointListener != null)
        {
            if (dev.getDeviceType().equals(UpnpMultiScreenDeviceInfo.MULTISCREEN_DEVICE_TYPE))
            {
                mUpnpControlPointListener.originalListAdd(dev);
            }
        }
    }

    /**
     * Set control point listener.
     * @param listener IUpnpControlPointListener.
     */
    public void setControlPointListener(IUpnpControlPointListener listener)
    {
        mUpnpControlPointListener = listener;
    }

    public boolean startGsensor()
    {
        Action StartGsensorAct =
            getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_GSENSOR_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_GSENSOR_START);
        return postAction(StartGsensorAct);
    }

    public boolean stopGsensor()
    {
        Action StopGsensorAct =
            getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_GSENSOR_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_GSENSOR_STOP);
        return postAction(StopGsensorAct);
    }

    public Action getAction(String ServiceTypeName, String ActionName)
    {
        Action mAction = null;
        if (mCurrentDevice == null)
        {
            LogTool.e("Current device is null, fail to get action.");
            return mAction;
        }
        Service mService = mCurrentDevice.getService(ServiceTypeName);
        if (mService == null)
        {
            LogTool.e("Service not found");
            return mAction;
        }
        mAction = mService.getAction(ActionName);
        return mAction;
    }

    public boolean postAction(Action mAction)
    {
        if (mAction == null)
        {
            LogTool.e("Action not found");
            return false;
        }
        mAction.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_REMOTE_ID, mRemoteID);
        return mAction.postControlAction();
    }

    /**
     * Get value of state variable.
     * @param ServiceType - name of service
     * @param StateVariableName - name of state variable.
     * @return state variable
     */
    public StateVariable getStateVariable(String ServiceType, String StateVariableName)
    {
        if (mCurrentDevice == null)
        {
            LogTool.e("Current device is null, fail to get state variable.");
            return null;
        }

        StateVariable stateVar = mCurrentDevice.getStateVariable(ServiceType, StateVariableName);
        if (stateVar == null)
        {
            LogTool.e("Can not get state varibale: " + StateVariableName);
            return null;
        }

        if (stateVar.postQuerylAction() == true)
        {
            String Value = stateVar.getValue();
            StringBuffer stateValue = new StringBuffer("value of ");
            stateValue.append(StateVariableName);
            stateValue.append(" = ");
            stateValue.append(Value);
            LogTool.i(stateValue.toString());

            return stateVar;
        }
        else
        {
            LogTool.e(StateVariableName + ": postQuerylAction fail.");
            return null;
        }
    }

    /**
     * Subscribe service.<br>
     * CN:订阅服务。
     * @param serviceName
     * @return
     */
    public boolean subscribeService(String serviceName)
    {
        LogTool.d("Subscribe");
        if (mCurrentDevice == null)
        {
            LogTool.e("Current device is null, fail to subscribe service.");
            return false;
        }
        Service service = mCurrentDevice.getService(serviceName);

        boolean isSuccess = subscribe(service);
        if (isSuccess)
        {
            LogTool.d("Success.");
            beginRenewSubscribeTask();
        }
        else
        {
            LogTool.d("Fail.");
        }
        return isSuccess;
    }

    /**
     * Unsubscribe service.<br>
     * CN:解订阅服务。
     * @param serviceName
     * @return
     */
    public boolean unsubscribeService(String serviceName)
    {
        LogTool.d("Unsubscribe");
        if (mCurrentDevice == null)
        {
            LogTool.e("Current device is null, fail to unsubscribe service.");
            return false;
        }
        endRenewSubscribeTask();
        Service service = mCurrentDevice.getService(serviceName);
        return unsubscribe(service);
    }

    /**
     * Get single instance of MultiScreenControlPoint <br>
     * @return instance of MultiScreenControlPoint
     */
    public static MultiScreenUpnpControlPoint getInstance()
    {
        if (mMultiScreenControlPoint == null)
        {
            LogTool.d("Create ctrpoint");
            mMultiScreenControlPoint = new MultiScreenUpnpControlPoint();
        }
        // CN:服务销毁时，会清空监听，要重新注册。
        mMultiScreenControlPoint.registerListener();
        return mMultiScreenControlPoint;
    }

    /**
     * Destroy control point.<br>
     * CN:销毁Upnp控制点。
     */
    public void destroy()
    {
        stopControl();
        unregisterListener();
    }

    public boolean isStarted()
    {
        return mIsStarted;
    }

    public void startControl()
    {
        if (!isStarted())
        {
            removeAlldevice();
            mMultiScreenControlPoint.start(ST.MULTISCREEN_DEVICE);
            // mMultiScreenControlPoint.search(ST.MULTISCREEN_DEVICE);
        }
        mIsStarted = true;
    }

    public void stopControl()
    {
        if (isStarted())
        {
            removeAlldevice();
            mMultiScreenControlPoint.finalize();
        }
        mIsStarted = false;
    }

    public void removeAlldevice()
    {
        lock();
        mOriginalList = getDeviceList();
        for (int i = 0; i < mOriginalList.size(); i++)
        {
            removeDevice(mOriginalList.getDevice(i));
        }
        unlock();
    }

    public void removeCannotAccessDevice(Device device)
    {
        removeDevice(device);
    }

    public Device getCurrentDevice()
    {
        return mCurrentDevice;
    }

    public void setCurrentDevice(Device currentDevice)
    {
        mCurrentDevice = currentDevice;
    }

    /**
     * Set current device by histroy uuid.<br>
     * CN:通过历史uuid设置当前设备。
     * @param uuid
     * @return true if set current device successfully.
     */
    public boolean setCurrentDeviceByHistroy(String uuid)
    {
        boolean retValue = false;

        for (int i = 0; i < mOriginalList.size(); i++)
        {
            if (mOriginalList.getDevice(i).isDevice(uuid))
            {
                mCurrentDevice = mOriginalList.getDevice(i);
                retValue = true;
                break;
            }
        }

        return retValue;
    }

    public String getRemoteId()
    {
        return mRemoteID;
    }

    public void setRemoteId(String localId)
    {
        mRemoteID = localId;
    }

    private void registerListener()
    {
        addNotifyListener(this);
        addSearchResponseListener(this);
        addEventListener(this);
        addDeviceChangeListener(this);
    }

    private void unregisterListener()
    {
        removeNotifyListener(this);
        removeSearchResponseListener(this);
        removeEventListener(this);
        removeDeviceChangeListener(this);
    }

    /**
     * Time task of renew subscribe services.<br>
     * CN:定期重订阅服务，超时为300s，故在280s内重置两次。
     */
    private void beginRenewSubscribeTask()
    {
        LogTool.d("Begin");
        final long delay = 140 * 1000, period = 140 * 1000;
        if (mRenewSubscriberTimer == null)
        {
            mRenewSubscriberTimer = new Timer();
            mRenewSubscriberTimer.schedule(new RenewSubscriberTask(), delay, period);
        }
    }

    private void endRenewSubscribeTask()
    {
        LogTool.d("End");
        if (mRenewSubscriberTimer != null)
        {
            mRenewSubscriberTimer.cancel();
            mRenewSubscriberTimer = null;
        }
    }

    /**
     * Run it in time task.<br>
     */
    private void renewSubscriber()
    {
        if (mCurrentDevice != null)
        {
            LogTool.d("renew subscriber service");
            renewSubscriberService(mCurrentDevice, Subscription.INFINITE_VALUE);
        }
    }
}
