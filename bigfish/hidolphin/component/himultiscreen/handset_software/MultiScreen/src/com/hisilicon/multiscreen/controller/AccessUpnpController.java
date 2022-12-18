package com.hisilicon.multiscreen.controller;

import org.cybergarage.upnp.Action;
import org.cybergarage.upnp.Argument;
import org.cybergarage.upnp.ArgumentList;
import org.cybergarage.upnp.Device;

import com.hisilicon.multiscreen.controller.IAccessListener.Caller;
import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.mybox.MultiScreenControlService.ClientState;
import com.hisilicon.multiscreen.protocol.ClientInfo;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.upnputils.MultiScreenUpnpControlPoint;
import com.hisilicon.multiscreen.upnputils.UpnpMultiScreenDeviceInfo;

/**
 * Access controller through upnp <br>
 */
public class AccessUpnpController
{
    /**
     * Period of keep alive.
     */
    private static final int KEEP_ALIVE_PERIOD = 2000;

    /**
     * Timeout of stopping thread of keep alive.<br>
     */
    private static final int JOIN_THREAD_KEEP_ALIVE_TIMEOUT = KEEP_ALIVE_PERIOD;

    /**
     * Period of ping.
     */
    private static final int PING_PERIOD = 1500; // 1000;

    /**
     * Timeout of http connection.<br>
     * CN:连接超时。
     */
    private static final int TIMEOUT_PING_CONNECT = 10 * 1000;

    /**
     * Timeout of http reading.<br>
     * CN:读超时。
     */
    private static final int TIMEOUT_PING_READ = 5 * 1000;

    /**
     * Timeout of stopping thread of ping.<br>
     */
    private static final int JOIN_THREAD_PING_TIMEOUT = PING_PERIOD;

    /**
     * Ping timeout.<br>
     */
    private static final int PING_TIME_OUT = 30 * 1000;

    /**
     * Default ping time cost.<br>
     */
    private static final int DEFAULT_PING_TIME = 3000;

    /**
     * Ping remote id - reaved.
     */
    private static final int PING_REMOTE_ID_OTHERS = -1;

    /**
     * Ping remote id - manual off.
     */
    private static final int PING_REMOTE_ID_MANUAL_OFF = PING_REMOTE_ID_OTHERS - 1;

    /**
     * Ping remote id - suspend.
     */
    private static final int PING_REMOTE_ID_SUSPEND = PING_REMOTE_ID_OTHERS - 2;

    /**
     * Ping remote id - can access.
     */
    private static final int PING_REMOTE_ID_CAN_ACCESS = 0;

    /**
     * Ping fail count of warning.<br>
     */
    private static final int PING_FAIL_COUNT_OF_WARNING = 5;

    /**
     * Max ping fail count of keepalive.<br>
     */
    private static final int MAX_PING_FAIL_COUNT = PING_FAIL_COUNT_OF_WARNING * 3;

    /**
     * Period of reAccess.
     */
    private static final int REACCESS_PERIOD = 2000;

    /**
     * Timeout of stopping thread of reAccess.<br>
     */
    private static final int JOIN_THREAD_REACCESS_TIMEOUT = REACCESS_PERIOD;

    /**
     * Timeout of reAccess.<br>
     */
    private static final int TIMEOUT_REACCESS = 5 * 1000;

    /**
     * Ping fail count of reAccess.<br>
     * CN:启动重连的Ping失败计数。<br>
     * CN:路由掉电重启约15s，WiFi开关切换约10s，取最快恢复场景10s，除以保活周期2s，可得reAccess启动时机为Ping失败5次。
     * CN:网络闪断及重命名时间过短，无法和网络抖动区分开，为保证服务正常使用，不能频繁重连。
     */
    private static final int PING_FAIL_COUNT_OF_REACCESS = 5;

    /**
     * Access keep alive thread name.<br>
     */
    private static final String KEEP_ALIVE_THREAD_NAME = "AccessKeepAliveThread";

    /**
     * Access ping thread name.<br>
     */
    private static final String ACCESS_PING_THREAD_NAME = "AccessPingThread";

    /**
     * ReAccess thread name.<br>
     */
    private static final String REACCESS_THREAD_NAME = "ReAccessThread";

    /**
     * MultiScreen upnp control point.<br>
     */
    private MultiScreenUpnpControlPoint mControlPoint = null;

    /**
     * Control service.
     */
    private MultiScreenControlService mMultiScreenControlService = null;

    /**
     * Callback listener deal access event<br>
     */
    private IAccessListener mAccessListener = null;

    /**
     * Access ping time cost.
     */
    private PingTime mPingTime = null;

    /**
     * Ping Fail count.<br>
     */
    private int mPingFailCount = 0;

    /**
     * Flag for keep alive thread running.<br>
     */
    private boolean mIsKeepAliveRunning = false;

    /**
     * Thread of access keep alive.<br>
     */
    private Thread mKeepAliveThread = null;

    /**
     * Flag for ping thread running.<br>
     */
    private boolean mIsPingRunning = false;

    /**
     * Thread of access ping.<br>
     */
    private Thread mAccessPingThread = null;

    /**
     * Flag for reAccess thread running.<br>
     */
    private boolean mIsReAccessRunning = false;

    /**
     * Thread of reAccess.<br>
     */
    private Thread mReAccessThread = null;

    /**
     * Access ping time class.<br>
     * CN:AccessPing时间类。
     */
    private class PingTime
    {
        /**
         * Time of starting ping.<br>
         */
        private long mPingStartTime = 0;

        /**
         * Time cost of AccessPing.<br>
         */
        private int mPingTimeCost = DEFAULT_PING_TIME;

        /**
         * PingTimeCost is valid.<br>
         */
        private boolean mIsValid = true;

        public PingTime()
        {
            mPingStartTime = 0;
            mPingTimeCost = DEFAULT_PING_TIME;
            mIsValid = true;
        }

        /**
         * Reset startup time of startPing.<br>
         * CN:重置保活启动时间。
         */
        protected void startup()
        {
            mPingStartTime = System.currentTimeMillis();
        }

        /**
         * Get startup time of startPing.<br>
         * CN:获取保活持续时间。
         * @return
         */
        protected int getStartTime()
        {
            return (int) (System.currentTimeMillis() - mPingStartTime);
        }

        /**
         * Set ping time cost value.<br>
         * CN:设置ping方法耗时。
         * @param timeCost
         */
        protected synchronized void setPingTimeCost(int timeCost)
        {
            mIsValid = true;
            mPingTimeCost = timeCost;
        }

        /**
         * Get ping time cost valid value.<br>
         * CN:获取有效ping方法耗时。<br>
         * Return PING_TIME_OUT if value has been read.<br>
         * CN:如果值被访问过，设为失效，返回超时。
         * @return valid ping time cost.
         */
        protected int getPingTimeCost()
        {
            if (mIsValid == true)
            {
                mIsValid = false;
                return mPingTimeCost;
            }
            else
            {
                // Ping time cost is invalid.
                return PING_TIME_OUT;
            }
        }

        /**
         * Get latest ping time cost value.<br>
         * CN:获取最新ping方法耗时。<br>
         * @return latest ping time cost.
         */
        protected int getLatestPingTimeCost()
        {
            return mPingTimeCost;
        }
    };

    /**
     * Runnable of access ping.<br>
     */
    private class PingRunnable implements Runnable
    {
        /**
         * Current remote id.<br>
         * CN:当前设备ID。
         */
        private String mRemoteID = null;

        /**
         * Return value of accessPing.<br>
         * CN:Ping方法返回值。
         */
        private int mTimeCost = 0;

        /**
         * Construction.<br>
         */
        public PingRunnable()
        {
            if (mPingTime == null)
            {
                mPingTime = new PingTime();
            }
            mPingTime.setPingTimeCost(DEFAULT_PING_TIME);
            mRemoteID = mControlPoint.getRemoteId();
        }

        @Override
        public void run()
        {
            while (mIsPingRunning)
            {
                int sleepTime = 10;
                mTimeCost = accessPing(mRemoteID);
                mPingTime.setPingTimeCost(mTimeCost);

                // Set ping fail count.
                // CN: AccessPing成功，Ping失败计数数立即清零。
                if ((mTimeCost < PING_TIME_OUT) && (mTimeCost > 0))
                {
                    mPingFailCount = 0;
                }

                while( sleepTime > 0 )
                {
                    sleepTime = sleepTime-1;
                    if(mIsPingRunning)
                        ThreadSleep(PING_PERIOD/10);
                    else
                        break;
                }
            }
        }
    }

    /**
     * Runnable of reAccess.<br>
     */
    private class ReAccessRunnable implements Runnable
    {
        /**
         * Current remote id.<br>
         * CN:当前设备ID。
         */
        private String mRemoteID = null;

        public ReAccessRunnable()
        {
            mRemoteID = mControlPoint.getRemoteId();
        }

        @Override
        public void run()
        {
            while (mIsReAccessRunning)
            {
                int sleepTime = 10;
                if (isKeepAliveStateOK() == false)
                {
                    // CN:保活状态异常，进行重连。
                    if (mIsReAccessRunning == true
                        && reAccess(mRemoteID, TIMEOUT_REACCESS, TIMEOUT_REACCESS) == true)
                    {
                        setKeepAliveStateOK();
                        renewState();
                    }

                    // CN:如果重连失败，发送M-SEARCH。
                    if (mIsReAccessRunning == true && isKeepAliveStateOK() == false)
                    {
                        mMultiScreenControlService.getDeviceDiscover().msearch();
                    }
                }

                while( sleepTime > 0 )
                {
                    sleepTime = sleepTime-1;
                    if(mIsReAccessRunning)
                        ThreadSleep(REACCESS_PERIOD/10);
                    else
                        break;
                }
            }
        }
    }

    /**
     * Runnable of access keep alive.<br>
     */
    private class KeepAliveRunnable implements Runnable
    {
        private int mTempPingTimeCost;

        public KeepAliveRunnable()
        {
            mTempPingTimeCost = DEFAULT_PING_TIME;
            mPingFailCount = 0;
        }

        @Override
        public void run()
        {
            while (mIsKeepAliveRunning)
            {
                int sleepTime = 10;
                mTempPingTimeCost = mPingTime.getPingTimeCost();

                if (isPingException(mTempPingTimeCost))
                {
                    LogTool.d("Ping time exception is being dealt.");
                    mIsPingRunning = false;
                    mIsReAccessRunning = false;
                    mIsKeepAliveRunning = false;
                    break;
                }

                // Count times of ping failed
                if ((mTempPingTimeCost < PING_TIME_OUT) && (mTempPingTimeCost > 0))
                {
                    mPingFailCount = 0;
                }
                else
                {
                    mPingFailCount++;
                    // LogTool.d("Ping fail count:" + mPingFailCount);
                }

                if (isNetworkLost(mPingFailCount))
                {
                    // Ping failed too much times: MAX_PING_FAIL_COUNT.
                    mIsPingRunning = false;
                    mIsReAccessRunning = false;
                    mIsKeepAliveRunning = false;
                    break;
                }

                while( sleepTime > 0 )
                {
                    sleepTime = sleepTime-1;
                    if(mIsKeepAliveRunning)
                        ThreadSleep(KEEP_ALIVE_PERIOD/10);
                    else
                        break;
                }
            }
        }

        /**
         * Check exception of ping time cost.<br>
         * Like: STB_REAVED, STB_MANUAL_OFF, STB_SUSPEND.
         * @param pingTime
         * @return true if it's a exception.
         */
        private boolean isPingException(int pingTime)
        {
            boolean isException = true;
            switch (pingTime)
            {
                case PING_REMOTE_ID_OTHERS:
                {
                    mMultiScreenControlService.setState(ClientState.REAVED);
                    dealReaved(Caller.KeepAlive);
                }
                    break;

                case PING_REMOTE_ID_MANUAL_OFF:
                {
                    mMultiScreenControlService.setState(ClientState.STB_LEAVE);
                    dealSTBLeave(Caller.KeepAlive);
                }
                    break;

                case PING_REMOTE_ID_SUSPEND:
                {
                    // RemoteID is suspend, be suspend.
                    mMultiScreenControlService.setState(ClientState.STB_SUSPEND);
                    dealSTBSuspend(Caller.KeepAlive);
                }
                    break;

                default:
                {
                    isException = false;
                }
                    break;
            }

            return isException;
        }

        /**
         * Deal if times of failures is more than the threshold value.<br>
         * PING_FAIL_COUNT_OF_WARNING, MAX_PING_FAIL_COUNT.
         * @param failedCount
         * @return true if network lost.
         */
        private boolean isNetworkLost(int failedCount)
        {
            boolean isLost = false;

            if (failedCount == 2 * PING_FAIL_COUNT_OF_WARNING)
            {
                isLost = false;
                dealNetworkNotWell();
            }
            else if (failedCount >= MAX_PING_FAIL_COUNT)
            {
                isLost = true;
                mMultiScreenControlService.setState(ClientState.NETWORK_LOST);
                dealNetworkLost(Caller.KeepAlive);
            }

            return isLost;
        }
    }

    /**
     * Access controller constructor.<br>
     */
    public AccessUpnpController()
    {
        mMultiScreenControlService = MultiScreenControlService.getInstance();
        mControlPoint = mMultiScreenControlService.getControlPoint();
        mPingTime = new PingTime();

    }

    /**
     * Reset AccessUpnpController.<br>
     */
    public void reset()
    {
        mMultiScreenControlService = MultiScreenControlService.getInstance();
        mControlPoint = mMultiScreenControlService.getControlPoint();
        if (mPingTime == null)
        {
            mPingTime = new PingTime();
        }
    }

    /**
     * Set listener of access.
     * @param accessMsgListener
     */
    public void setListener(IAccessListener accessMsgListener)
    {
        mAccessListener = accessMsgListener;
    }

    /**
     * Access hello.<br>
     * @param remoteID
     * @param localIP
     * @param timeoutConnect
     * @param timeoutRead
     * @return true if it success.
     */
    public boolean accessHello(String remoteID, String localIP, int timeoutConnect, int timeoutRead)
    {
        boolean isSuccess = false;
        Action helloAct = initHello(remoteID, localIP);

        if (helloAct == null)
        {
            LogTool.e("Init Hello action failed!");
        }
        else
        {
            ArgumentList outArgList = sendHello(helloAct, timeoutConnect, timeoutRead);
            isSuccess = checkHello(remoteID, outArgList);
            if (isSuccess)
            {
                setVideoType(outArgList);
            }
        }

        return isSuccess;
    }

    /**
     * Access byebye.<br>
     * @return byebye result.
     */
    public boolean accessByebye()
    {
        Action byebyeAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_ACCESS_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_ACCESS_BYEBYE);
        if (byebyeAct == null)
        {
            LogTool.e("Action not found");
            return false;
        }
        byebyeAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_REMOTE_ID,
            mControlPoint.getRemoteId());
        if (byebyeAct.postControlAction() == false)
        {
            return false;
        }
        return true;
    }

    /**
     * Start Access ping task. <br>
     */
    public void startAccessPingTask()
    {
        if (mIsPingRunning || mIsReAccessRunning || mIsKeepAliveRunning)
        {
            stopAccessPingTask();
            LogTool.d("restart AccessPingTask");
        }

        startPing();
        startReAccessThread();
        startKeepAlive();
    }

    /**
     * Stop Access ping task.<br>
     * @param caller caller of this function.
     */
    public void stopAccessPingTask(Caller caller)
    {
        mIsPingRunning = false;
        mIsReAccessRunning = false;
        mIsKeepAliveRunning = false;

        if (caller == null)
        {
            caller = Caller.Others;
            LogTool.d("Caller of IAccessListener is null, you should check it.");
        }

        switch (caller)
        {
            case AccessPing:
            {
                stopReAccessThread();
                stopKeepAlive();
            }
                break;
            case ReAccess:
            {
                stopPing();
                stopKeepAlive();
            }
                break;
            case KeepAlive:
            {
                stopPing();
                stopReAccessThread();
            }
                break;
            case Others:
            default:
            {
                stopPing();
                stopReAccessThread();
                stopKeepAlive();
            }
                break;
        }
    }

    /**
     * Initialize Hello action.<br>
     * @param remoteID remoteID of client.
     * @param localIP IP address of client.
     * @return Hello action.
     */
    private Action initHello(String remoteID, String localIP)
    {
        Action helloAct;
        if (remoteID != null && localIP != null)
        {
            helloAct =
                mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_ACCESS_TYPE,
                    UpnpMultiScreenDeviceInfo.ACTION_ACCESS_HELLO);
            if (helloAct != null)
            {
                helloAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_REMOTE_ID, remoteID);
                helloAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_REMOTE_IP, localIP);
                helloAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_CLIENT_VERSION,
                    ClientInfo.CLIENT_VERSION);
                helloAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_HANDSET_DEVICEINFO,
                    android.os.Build.MODEL);
                helloAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_HANDSET_SDK_VERSION,
                    android.os.Build.VERSION.SDK_INT);

                LogTool.d("handset info：" + android.os.Build.MODEL + ", sdk version:"
                    + android.os.Build.VERSION.SDK_INT);
                LogTool.d("Access hello input remote id = " + remoteID);
                LogTool.d("Access hello input remote IP = " + localIP);
            }
        }
        else
        {
            LogTool.e("remoteID or localIP is null and hello action initialize failed.");
            helloAct = null;
        }
        return helloAct;
    }

    /**
     * Send Hello action.<br>
     * @param helloAct
     * @param timeoutConnect
     * @param timeoutRead
     * @return outArgList of Hello action.
     */
    private ArgumentList sendHello(Action helloAct, int timeoutConnect, int timeoutRead)
    {
        ArgumentList outArgList = null;
        if ((helloAct != null) && (helloAct.postControlAction(timeoutConnect, timeoutRead) == true))
        {
            outArgList = helloAct.getOutputArgumentList();
        }
        else
        {
            LogTool.e("Send Hello action fail.");
        }
        return outArgList;
    }

    /**
     * Check Hello action result.<br>
     * @param remoteID
     * @param outArgList
     * @return true if access hello is successful.
     */
    private boolean checkHello(String remoteID, ArgumentList outArgList)
    {
        boolean isOK = false;
        if (outArgList == null)
        {
            LogTool.e("outArgList of Hello action is null.");
        }
        else
        {
            Argument argRemoteID =
                outArgList.getArgument(UpnpMultiScreenDeviceInfo.ARG_CURRENT_REMOTE_ID);
            if (argRemoteID != null)
            {
                String currentID = argRemoteID.getValue();
                if (remoteID.equals(currentID))
                {
                    isOK = true;
                }
                LogTool.d("Access hello return = " + currentID);
            }
        }
        return isOK;
    }

    /**
     * Set the type of video supported.
     * @param outArgList
     */
    private void setVideoType(ArgumentList outArgList)
    {
        String videoType = MultiScreenControlService.VIDEO_JPEG_TYPE;

        if (outArgList != null)
        {
            Argument ArgVideoType =
                outArgList.getArgument(UpnpMultiScreenDeviceInfo.ARG_SUPPORT_VIDEO);
            if (ArgVideoType == null)
            {
                LogTool.i("Hello action does not return the type of video supported in server.");
            }
            else
            {
                videoType = ArgVideoType.getValue();
            }
        }

        LogTool.i("Set the type of video supported: " + videoType);
        mMultiScreenControlService.setSupportVideoType(videoType);
    }

    /**
     * Stop Access ping task.<br>
     */
    private void stopAccessPingTask()
    {
        stopAccessPingTask(Caller.Others);
    }

    /**
     * Start ping.<br>
     */
    private void startPing()
    {
        mIsPingRunning = true;
        mPingTime.startup();
        mAccessPingThread = new Thread(new PingRunnable());
        mAccessPingThread.setName(ACCESS_PING_THREAD_NAME);
        mAccessPingThread.setDaemon(true);
        mAccessPingThread.start();
    }

    /**
     * Stop ping.<br>
     */
    private void stopPing()
    {
        mIsPingRunning = false;
        if (mAccessPingThread != null && mAccessPingThread.isAlive())
        {
            try
            {
                mAccessPingThread.join(JOIN_THREAD_PING_TIMEOUT);
            }
            catch (InterruptedException e)
            {
                LogTool.e(e.getMessage());
            }
        }
        mAccessPingThread = null;
    }

    /**
     * Start keep alive.<br>
     */
    private void startKeepAlive()
    {
        mIsKeepAliveRunning = true;
        mKeepAliveThread = new Thread(new KeepAliveRunnable());
        mKeepAliveThread.setName(KEEP_ALIVE_THREAD_NAME);
        mKeepAliveThread.setDaemon(true);
        mKeepAliveThread.start();
    }

    /**
     * Stop keep alive.<br>
     */
    private void stopKeepAlive()
    {
        mIsKeepAliveRunning = false;
        if (mKeepAliveThread != null && mKeepAliveThread.isAlive())
        {
            try
            {
                mKeepAliveThread.join(JOIN_THREAD_KEEP_ALIVE_TIMEOUT);
            }
            catch (InterruptedException e)
            {
                LogTool.e(e.getMessage());
            }
        }
        mKeepAliveThread = null;
    }

    /**
     * Start ReAccess thread.<br>
     */
    private void startReAccessThread()
    {
        mIsReAccessRunning = true;
        mReAccessThread = new Thread(new ReAccessRunnable());
        mReAccessThread.setName(REACCESS_THREAD_NAME);
        mReAccessThread.setDaemon(true);
        mReAccessThread.start();
    }

    /**
     * Stop ReAccess thread.<br>
     */
    private void stopReAccessThread()
    {
        mIsReAccessRunning = false;
        if (mReAccessThread != null && mReAccessThread.isAlive())
        {
            try
            {
                mReAccessThread.join(JOIN_THREAD_REACCESS_TIMEOUT);
            }
            catch (InterruptedException e)
            {
                LogTool.e(e.getMessage());
            }
        }
        mReAccessThread = null;
    }

    /**
     * Access ping.<br>
     * @param RemoteID
     * @return
     */
    private int accessPing(String RemoteID)
    {
        int timeCost = PING_TIME_OUT;
        Action pingAct =
            mControlPoint.getAction(UpnpMultiScreenDeviceInfo.MULTISCREEN_SERVICE_ACCESS_TYPE,
                UpnpMultiScreenDeviceInfo.ACTION_ACCESS_PING);
        if (pingAct == null)
        {
            LogTool.e("Action not found");
            return timeCost;
        }

        pingAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_REMOTE_ID, RemoteID);
        pingAct.setArgumentValue(UpnpMultiScreenDeviceInfo.ARG_PING_TIME, mPingTime.getStartTime());

        if (pingAct.postControlAction(TIMEOUT_PING_CONNECT, TIMEOUT_PING_READ) == false)
        {
            LogTool.e("Post ping action fail");
        }
        else
        {
            ArgumentList outArgList = pingAct.getOutputArgumentList();
            String remoteIdSTB = outArgList.getArgument(0).getValue();
            if (RemoteID.equals(remoteIdSTB))
            {
                timeCost =
                    mPingTime.getStartTime()
                        - Integer.parseInt(outArgList.getArgument(1).getValue());
            }
            else if (MultiScreenUpnpControlPoint.REMOTE_ID_CAN_ACCESS.equals(remoteIdSTB))
            {
                // CN:RemoteID为0.0.0.0，说明STB服务重置，需要重新接入。
                LogTool.d("remote_id of STB is can_access.");
                timeCost = PING_REMOTE_ID_CAN_ACCESS;
            }
            else if (MultiScreenUpnpControlPoint.REMOTE_ID_STB_MANUAL_OFF.equals(remoteIdSTB))
            {
                LogTool.d("STB is manual off.");
                mMultiScreenControlService.setState(ClientState.STB_LEAVE);
                mIsPingRunning = false;
                dealSTBLeave(Caller.AccessPing);
                timeCost = PING_REMOTE_ID_MANUAL_OFF;
            }
            else if (MultiScreenUpnpControlPoint.REMOTE_ID_DEVICE_SUSPEND.equals(remoteIdSTB))
            {
                mMultiScreenControlService.setState(ClientState.STB_SUSPEND);
                mIsPingRunning = false;
                dealSTBSuspend(Caller.AccessPing);
                timeCost = PING_REMOTE_ID_SUSPEND;
            }
            else
            {
                // CN:被其他RemoteID抢占。
                LogTool.e("Be reaved by " + outArgList.getArgument(0).getValue());
                mMultiScreenControlService.setState(ClientState.REAVED);
                mIsPingRunning = false;
                dealReaved(Caller.AccessPing);
                timeCost = PING_REMOTE_ID_OTHERS;
            }
        }

        return timeCost;
    }

    /**
     * Re-Access current device.<br>
     * @param remoteID
     * @param timeoutConnect
     * @param timeoutRead
     * @return result of reAccess.
     */
    private boolean reAccess(String remoteID, int timeoutConnect, int timeoutRead)
    {
        // CN:需要重连的场景：1.STB网络恢复；2.STB服务开关重启；3.客户端网络重置；4.手动重置STB服务接入RemoteID；
        boolean isOK = false;
        String localIP = mMultiScreenControlService.getLastestIP();
        Device currentDevice = mControlPoint.getCurrentDevice();

        if (currentDevice == null)
        {
            LogTool.e("Current device is null, fail to reAccessSTB.");
            return false;
        }

        // CN:通过UUID从设备列表中获得设备信息。
        Device newDevice =
            mMultiScreenControlService.getDeviceDiscover().getDeviceByUUID(currentDevice.getUDN());
        if (newDevice == null)
        {
            LogTool.e("ReAccess device is not exist:" + currentDevice.getUDN());
            return false;
        }

        LogTool.d("ReAccess device name: " + newDevice.getFriendlyName());
        // CN:重置设备信息。
        mMultiScreenControlService.getControlPoint().setCurrentDevice(newDevice);
        // CN:尝试接入。
        isOK = accessHello(remoteID, localIP, timeoutConnect, timeoutRead);
        if (isOK)
        {
            LogTool.d("ReAccess successfully.");
            // FIXME CN:查询重置服务信息较慢，reAccess成功后应该先返回通知保活。
            // isOK = mMultiScreenControlService.renewState();
        }
        else
        {
            LogTool.e("Fail to reAccess.");
        }

        return isOK;
    }

    /**
     * Renew state after reAccess successfully.<br>
     * @return true means successful.
     */
    private boolean renewState()
    {
        return mMultiScreenControlService.renewState();
    }

    private boolean isKeepAliveStateOK()
    {
        boolean isOK = false;
        int tempPingTimeCost = mPingTime.getLatestPingTimeCost();

        if ((0 < tempPingTimeCost && tempPingTimeCost < PING_TIME_OUT)
            || (mPingFailCount < PING_FAIL_COUNT_OF_REACCESS))
        {
            // CN:1.ping成功；2.ping失败计数小于重连阈值。
            isOK = true;
        }
        else
        {
            isOK = false;
        }

        return isOK;
    }

    private void setKeepAliveStateOK()
    {
        mPingFailCount = 0;
        mPingTime.setPingTimeCost(DEFAULT_PING_TIME);
    }

    /**
     * CN:处理抢占。
     * @param caller
     */
    private void dealReaved(Caller caller)
    {
        if (mAccessListener == null)
        {
            LogTool.e("Access listener is null, cannot deal event: Reaved.");
        }
        else
        {
            mAccessListener.dealReaveEvent(caller);
        }
    }

    /**
     * CN:处理服务关闭。
     * @param caller
     */
    private void dealSTBLeave(Caller caller)
    {
        if (mAccessListener == null)
        {
            LogTool.e("Access listener is null, cannot deal event: STBLeave.");
        }
        else
        {
            mAccessListener.dealSTBLeaveEvent(caller);
        }
    }

    /**
     * CN:处理抢占。
     * @param caller
     */
    private void dealSTBSuspend(Caller caller)
    {
        if (mAccessListener == null)
        {
            LogTool.e("Access listener is null, cannot deal event: STBSuspend.");
        }
        else
        {
            mAccessListener.dealSTBSuspendEvent(caller);
        }
    }

    /**
     * CN:处理网络状态不佳。
     */
    private void dealNetworkNotWell()
    {
        if (mAccessListener == null)
        {
            LogTool.e("Access listener is null, cannot deal event: NetWorkNotWell.");
        }
        else
        {
            mAccessListener.dealNetWorkNotWellEvent();
        }
    }

    /**
     * CN:处理断网。
     * @param caller
     */
    private void dealNetworkLost(Caller caller)
    {
        if (mAccessListener == null)
        {
            LogTool.e("Access listener is null, cannot deal event: NetWorkLost.");
        }
        else
        {
            mAccessListener.dealNetWorkLostEvent(caller);
        }
    }

    private void ThreadSleep(long time)
    {
        try
        {
            Thread.sleep(time);
        }
        catch (InterruptedException e)
        {
            LogTool.e("Interrupted Exception" + e.getMessage());
        }
    }
}
