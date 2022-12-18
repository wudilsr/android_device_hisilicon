package com.hisilicon.multiscreen.server;

import java.io.IOException;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.provider.Settings;
import android.view.inputmethod.InputMethodInfo;
import android.view.inputmethod.InputMethodManager;

import com.hisilicon.multiscreen.http.HiHttpRecvMsgListener;
import com.hisilicon.multiscreen.http.HiHttpServer;
import com.hisilicon.multiscreen.protocol.message.Action;
import com.hisilicon.multiscreen.protocol.message.Argument;
import com.hisilicon.multiscreen.protocol.message.ArgumentValue;
import com.hisilicon.multiscreen.protocol.server.VImeServerControl;
import com.hisilicon.multiscreen.protocol.server.VImeStatusObserver;
import com.hisilicon.multiscreen.protocol.utils.HostNetInterface;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;
import com.hisilicon.multiscreen.protocol.utils.SaxXmlUtil;
import com.hisilicon.multiscreen.protocol.utils.VImeStatusDefine;

/**
 * Control and observe state of Virtual IME.<br>
 * CN:控制和监控虚拟输入法的状态。
 * @since MultiScreen V2.0.1.1
 */
public class VImeControl
{
    /**
     * Virtual IME’s string Id.<br>
     * CN:虚拟输入法的字符串ID。
     */
    private static final String VIRTUAL_IME_NAME = "com.hisilicon.multiscreen.vime/.VirtualIME";

    /**
     * Index of first argument in message.<br>
     * CN:消息中第一个参数的索引。
     * */
    private static final int FIRST_ARGUMENT_INDEX = 0;

    /**
     * The upper limit continued count, when the server at input status, however
     * client at other status .<br>
     * CN:服务端处于input状态，而客户端持续处于其他状态的计数的上限。
     * */
    private static final int CLIENT_READY_UPPER_LIMIT = 4;

    /**
     * Default VIme check timeout.<br>
     * CN:默认VIme状态检查超时。
     */
    private static final long MAX_CHECK_TIMEOUT = 21000L;

    /**
     * Default interval between close keyboard and close VIme<br>
     * CN:关闭键盘和关闭输入法的默认的时间间隔。
     */
    private static final long CLOSE_VIME_TIME_INTERVAL = 1000L;

    /**
     * Default close VIme timeout tolerance<br>
     * CN:默认的关闭VIme的超时容差。
     */
    private static final long CHECK_TIMEOUT_TOLERANCE = 60000L;

    /**
     * The context that the VImeControl rely on.<br>
     * CN: VImeControl依赖的context。
     */
    private Context mContext = null;

    /**
     * Save the VIme's status.<br>
     * CN：保存VIme的状态。
     */
    private VImeStatusObserver mStatusObserver = null;

    /**
     * System's Input method Manager parameter.<br>
     * CN：系统输入法管理参数。
     */
    private InputMethodManager mInputManager = null;

    /**
     * System's default IME ID. <br>
     * CN：系统默认输入法id。
     */
    private String mDefaultIMEId = null;

    /**
     * VIme control message constructor. <br>
     * CN：VIme 控制消息构造器。
     */
    private VImeServerControl mVImeControlMsg = null;

    /**
     * VIme server's net status. <br>
     * CN：VIme 服务端网络状态。
     */
    private int mNetStat = Action.ACTION_ID_VIME_SUCCESS_FLAG;

    /**
     * The last time that client check status. <br>
     * CN：客户端上次检查状态时间。
     */
    private long mLastCheckTime = 0;

    /**
     * The timeout not receive client's check. <br>
     * CN：check 消息无响应timeout。
     */
    private long mCheckTimeOut = MAX_CHECK_TIMEOUT;

    /**
     * The check message check cycle. <br>
     * CN：check 消息检查周期。
     */
    private long mCheckCycle = 1000;

    /**
     * The Connected client's IP. <br>
     * CN：接入的客户端IP。
     */
    private String mRemoteIP = null;

    /**
     * The Connected client's http Port. <br>
     * CN：接入的客户端的http端口。
     */
    private int mRemotePort = 2016;

    /**
     * The VIme control http server's Port. <br>
     * CN：VIme 控制的http服务器的端口。
     */
    private int mVImeControlPort = 2015;

    /**
     * The flag indicates whether switch VIme. <br>
     * CN：是否要切换VIme的标志量。
     */
    private boolean mIsNeedSwitchIME = false;

    /**
     * The timer for check client’s net. <br>
     * CN：检查客户端网络的计时器。
     */
    private Timer mCheckTimer = null;

    /**
     * The http server receive the client's request. <br>
     * CN：接受客户端请求的http服务器
     */
    private HiHttpServer mVImeHttpServer = null;

    /**
     * The continued count, when the server at input status, however client at
     * other status .<br>
     * CN:服务端处于input状态，而客户端持续处于其他状态的计数。
     */
    private int mClientNoInputCount = 0;

    /**
     * Flag for enable VIME from client <br>
     * CN:使能VIME的操作来自客户端的标示
     */
    private boolean mIsEnableFromClient = false;

    /**
     * Listener of VIME status. <br>
     * CN: 虚拟输入法状态监听。
     */
    private BroadcastReceiver mStatusReceiver = new BroadcastReceiver()
    {
        public void onReceive(Context context, Intent intent)
        {
            String action = intent.getAction();
            LogTool.d("Receiver the BroadCastID" + action);
            VImeStatusDefine.VimeStatus currentStatus;

            if (MultiScreenIntentAction.VIME_SWITCH_TO_READY.equals(action))
            {
                currentStatus = VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_READY;
                mIsNeedSwitchIME = true;
                if (!mIsEnableFromClient)
                {
                    sendVImeAbnormalStart();
                }
            }
            else if (MultiScreenIntentAction.VIME_SWITCH_TO_INPUT.equals(action))
            {
                currentStatus = VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INPUT;
            }
            else if (MultiScreenIntentAction.VIME_SWITCH_TO_DEINIT.equals(action))
            {
                currentStatus = VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_DEINIT;
                mIsNeedSwitchIME = false;
                mIsEnableFromClient = false;
            }
            else
            {
                currentStatus = VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INIT;
            }

            if (null != mStatusObserver)
            {
                mStatusObserver.setVImeStatus(currentStatus);
            }
            else
            {
                LogTool.e("mStatusObserver is null");
                mStatusObserver = new VImeStatusObserver();
                mStatusObserver.setVImeStatus(currentStatus);
            }

        }

    };

    /**
     * Callback listener for dealing control message of virtual IME. <br>
     * CN:处理虚拟输入法控制消息的监听回调。
     */
    private HiHttpRecvMsgListener mVImeMsgListener = new HiHttpRecvMsgListener()
    {

        @Override
        public String onHttpMsgReceived(byte[] msg, String remoteIP)
        {
            String retStr;
            Action recvAction = parseVImeControlMsg(msg);
            if (null == recvAction)
            {
                LogTool.e("recvAction is null");
                retStr = mVImeControlMsg.retDefaultMsgResponse();
            }
            else
            {
                switch (recvAction.getId())
                {
                    case Action.ACTION_ID_VIME_CHECK:
                    {
                        // LogTool.d("receive check status msg");
                        // mRemoteIP = remoteIP;
                        mIsNeedSwitchIME = true;
                        mLastCheckTime = System.currentTimeMillis();
                        if (null == mStatusObserver)
                        {
                            LogTool.e("statusObserver is null");
                            mStatusObserver = new VImeStatusObserver();
                        }
                        if (null == mStatusObserver.getVImeStatus())
                        {
                            LogTool.e("VImeStatus is null,reset status");
                            mStatusObserver
                                .setVImeStatus(VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INIT);
                        }
                        retStr =
                            mVImeControlMsg.retCheckStatus(mNetStat, mStatusObserver
                                .getVImeStatus().getIndex());
                        Argument statusArg = recvAction.getArgument(FIRST_ARGUMENT_INDEX);
                        if (null == statusArg)
                        {
                            LogTool.e("status arg is null");
                            break;
                        }

                        ArgumentValue statusVal = statusArg.getArgumentValue(FIRST_ARGUMENT_INDEX);
                        if (null == statusVal)
                        {
                            LogTool.e("status value is null");
                            break;
                        }
                        int status = (Integer) statusVal.getVaule();
                        // LogTool.v("vime client status : " + status);
                        // LogTool.v("vime server status : "
                        // + mStatusObserver.getVImeStatus().getIndex());
                        VImeStatusDefine.VimeStatus clientStatus =
                            VImeStatusDefine.VimeStatus.getStatus(status);
                        if (clientStatus != null)
                        {
                            defineVImeCloseTipKeyboard(clientStatus);
                        }

                        break;
                    }

                    case Action.ACTION_ID_VIME_ENALBE:
                    {
                        LogTool.d("receive enable msg");
                        mIsEnableFromClient = true;
                        mRemoteIP = remoteIP;
                        String currentIMEId =
                            Settings.Secure.getString(mContext.getContentResolver(),
                                Settings.Secure.DEFAULT_INPUT_METHOD);
                        boolean changeFlag = false;
                        if (VIRTUAL_IME_NAME.equals(currentIMEId))
                        {
                            changeFlag = true;
                        }
                        else
                        {
                            mInputManager.setInputMethod(null, VIRTUAL_IME_NAME);
                            mStatusObserver
                                .setVImeStatus(VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_READY);
                        }
                        sendClientDeviceInfo();
                        // return enable result
                        retStr = mVImeControlMsg.retEnableIME(changeFlag);
                        break;
                    }

                    case Action.ACTION_ID_VIME_DISABLE:
                    {
                        LogTool.d("receive disable msg");
                        if ((mRemoteIP != null) && (mRemoteIP.equalsIgnoreCase(remoteIP)))
                        {
                            closeVIme();
                        }
                        retStr = mVImeControlMsg.retDisableIME(true);
                        break;
                    }

                    default:
                    {
                        LogTool.e("receive other msg");
                        retStr = mVImeControlMsg.retDefaultMsgResponse();
                        break;
                    }

                }
            }

            // LogTool.v("response string:" + retStr);
            return retStr;
        }
    };

    /**
     * Construct the VImeControl use mContext and InputManager
     * @param context MultiScreen service context.<br>
     *        CN:多屏服务上下文环境。
     * @param inputManager input method manager of system.<br>
     *        CN：系统输入法管理类的对象。
     */
    public VImeControl(Context context, InputMethodManager inputManager)
    {
        super();
        this.mContext = context;
        this.mInputManager = inputManager;
        String currentIMEId =
            Settings.Secure.getString(mContext.getContentResolver(),
                Settings.Secure.DEFAULT_INPUT_METHOD);
        mDefaultIMEId = currentIMEId;

    }

    /**
     * Start control virtual IME module. <br>
     * CN:开始虚拟输入法控制。
     */
    public void startControl()
    {
        initObserver();
        mVImeControlMsg = new VImeServerControl();
        mVImeHttpServer = new HiHttpServer(mVImeControlPort, mVImeMsgListener);
        mVImeHttpServer.startServer();
        startCheckConnect();
        LogTool.d("VImeControl start");
    }

    /**
     * Stop control virtual IME module. <br>
     * CN:停止虚拟输入法控制模块。
     */
    public void stopControl()
    {
        mVImeHttpServer.stopServer();
        closeVIme();
        stopCheckConnect();
        unregisterBroadcastReceiver(mStatusReceiver);
        LogTool.d("VImeControl stop");
    }

    /**
     * Get the check status's timeout. <br>
     * CN: 获得检查状态的timeout。 <br>
     * @return mCheckTimeOut a positive number in millisecond CN:一个以毫秒为单位的正的数字
     */
    public long getCheckTimeOut()
    {
        return mCheckTimeOut;
    }

    /**
     * Set the check status's timeout <br>
     * @param timeout a positive number in millisecond <br>
     *        CN:一个以毫秒为单位的正的数字
     */
    public void setCheckTimeOut(long timeout)
    {
        this.mCheckTimeOut = timeout;
    }

    /**
     * Set the check status cycle <br>
     * CN: 设置状态检查的周期
     * @param mCheckCycle a positive number in millisecond <br>
     *        CN:一个以毫秒为单位的正的数字
     */
    public long getCheckCycle()
    {
        return mCheckCycle;
    }

    /**
     * Set the check status cycle <br>
     * CN: 设置状态检查的周期
     * @param mCheckCycle a positive number in millisecond <br>
     *        CN:一个以毫秒为单位的正的数字
     */
    public void setCheckCycle(long mCheckCycle)
    {
        this.mCheckCycle = mCheckCycle;
    }

    /**
     * Set the status of net. <br>
     * CN:设置网络状态的周期。
     * @param mNetStat 0 means fail connection; 1 means success connection <br>
     *        CN: 0 表示网络失去连接，1 表示网络连接成功
     */
    public void setNetStat(int mNetStat)
    {
        this.mNetStat = mNetStat;
    }

    /**
     * Get the status of net. <br>
     * CN:获得网络状态。
     * @return net status CN：网络状态
     */
    public int getNetStat()
    {
        return mNetStat;
    }

    /**
     * Get the accepted client's IP. <br>
     * CN:获得接受的客户端的IP。
     * @return mRemoteIP null or IP address <br>
     *         CN: null或者IP地址
     */
    public String getRemoteIP()
    {
        return mRemoteIP;
    }

    /**
     * Set the accepted client's IP. <br>
     * CN:设置远程IP。
     * @param remoteIP the connected client's ip address <br>
     *        CN:连接的客户端IP地址
     */
    public void setRemoteIP(String remoteIP)
    {
        LogTool.d("setRemoteIP");
        this.mRemoteIP = remoteIP;
    }

    /**
     * Set the accepted client's url and convert it to ip and port.<br>
     * CN:设置接收到的客户端的url，并转化为ip和端口。
     * @param url 客户端监听服务端的url。
     */
    public void setClientURL(String url)
    {
        mRemoteIP = HostNetInterface.uri2Ip(url);
        mRemotePort = HostNetInterface.uri2port(url);
    }

    /**
     * Register virtual IME observer. <br>
     * CN:初始状态检查。
     */
    private void initObserver()
    {
        mStatusObserver = new VImeStatusObserver();
        mStatusObserver.setVImeStatus(VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INIT);
        IntentFilter filter = new IntentFilter();
        filter.addAction(MultiScreenIntentAction.VIME_SWITCH_TO_INIT);
        filter.addAction(MultiScreenIntentAction.VIME_SWITCH_TO_READY);
        filter.addAction(MultiScreenIntentAction.VIME_SWITCH_TO_INPUT);
        filter.addAction(MultiScreenIntentAction.VIME_SWITCH_TO_DEINIT);
        mContext.registerReceiver(mStatusReceiver, filter);
        queryVImeStatus();
    }

    /**
     * Start check client connection task. <br>
     * CN:开始检查客户端连接。
     */
    private void startCheckConnect()
    {
        mLastCheckTime = System.currentTimeMillis();
        TimerTask checkTask = new TimerTask()
        {
            long curTime = 0;

            @Override
            public void run()
            {
                curTime = System.currentTimeMillis();

                // when reset system time stop current check circle
                if (((curTime - mLastCheckTime) < 0)
                    || ((curTime - mLastCheckTime) > (mCheckTimeOut + CHECK_TIMEOUT_TOLERANCE)))
                {
                    LogTool.e("reset system time");
                    mLastCheckTime = curTime;
                    return;
                }

                if ((curTime - mLastCheckTime) > mCheckTimeOut)
                {
                    closeVIme();
                    mLastCheckTime = curTime;
                }

                if (!mIsNeedSwitchIME)
                {
                    mLastCheckTime = curTime;
                }
            }
        };

        if (null != mCheckTimer)
        {
            mCheckTimer.cancel();
            mCheckTimer = null;
        }
        mCheckTimer = new Timer();
        mCheckTimer.schedule(checkTask, 0, mCheckCycle);
    }

    /**
     * Stop check client's connect. <br>
     * 停止检查客户端网络连接。
     */
    private void stopCheckConnect()
    {
        if (null != mCheckTimer)
        {
            mCheckTimer.cancel();
            mCheckTimer = null;
        }
    }

    /**
     * Query current status of virtual IME. <br>
     * CN: 查询虚拟输入法状态。
     */

    private void queryVImeStatus()
    {
        Intent initCheckIntent = new Intent();
        initCheckIntent.setAction(MultiScreenIntentAction.CHECK_VIME_STATUS);
        mContext.sendBroadcast(initCheckIntent);
    }

    /**
     * Check virtual IME is current default IME. <br>
     * CN:检查当前默认输入法是否是虚拟输入法。
     * @return true indicates that current default IME is virtual IME; false
     *         means current default IME is other IME. CN:true
     *         表示当前默认输入法是虚拟输入法，false表示当前输入法是其他输入法
     */
    private boolean isVImeDefault()
    {
        String currentIMEId =
            Settings.Secure.getString(mContext.getContentResolver(),
                Settings.Secure.DEFAULT_INPUT_METHOD);
        boolean result = false;
        if (VIRTUAL_IME_NAME.equals(currentIMEId))
        {
            result = true;
        }

        return result;
    }

    /**
     * Switch virtual IME to other IME. <br>
     * CN :将虚拟输入法切换为其他输入法。
     * @return true means switch success,false means switch failure <br>
     *         CN: true 表示切换成功，false 表示切换失败
     */
    private boolean closeVIme()
    {
        if (!mIsNeedSwitchIME)
        {
            return true;
        }

        if ((null == mContext) || (null == mInputManager))
        {
            LogTool.e("Context or InputManager is null");
            throw new RuntimeException("Context or InputManager is null");
        }

        if (isVImeDefault())
        {
            LogTool.d("check status msg receive  timeout");

            notifyCloseTipKeyboard();
            try
            {
                Thread.sleep(CLOSE_VIME_TIME_INTERVAL);
            }
            catch (InterruptedException e)
            {
                LogTool.e(e.getMessage());
            }
            mIsEnableFromClient = false;
            if ((!mDefaultIMEId.equals(VIRTUAL_IME_NAME)) && isIMEAlive(mDefaultIMEId))
            {
                // Settings.Secure.putString(mContext.getContentResolver(),
                // Settings.Secure.DEFAULT_INPUT_METHOD, mDefaultIMEId);
                mInputManager.setInputMethod(null, mDefaultIMEId);
                return true;

            }
            else
            {
                List<InputMethodInfo> imeList = mInputManager.getInputMethodList();
                for (int i = 0; i < imeList.size(); i++)
                {
                    InputMethodInfo imeInfo = imeList.get(i);
                    if (null == imeInfo)
                    {
                        LogTool.e("ime Info is null");
                        return false;
                    }
                    if (imeInfo.getId().equals(VIRTUAL_IME_NAME))
                    {
                        continue;
                    }
                    else
                    {
                        // Settings.Secure.putString(mContext.getContentResolver(),
                        // Settings.Secure.DEFAULT_INPUT_METHOD,
                        // imeInfo.getId());
                        mInputManager.setInputMethod(null, imeInfo.getId());
                        mDefaultIMEId = imeInfo.getId();
                        return true;
                    }
                }
            }
        }
        return true;
    }

    /**
     * Obtain the flag for whether the imeId exists in the system's IME list.<br>
     * 获得id为imeId输入法是否存在于系统输入法列表中的标示。
     * @param imeId - 输入法id
     * @return -输入法存在标示
     */
    private boolean isIMEAlive(String imeId)
    {
        if (null == mInputManager)
        {
            LogTool.e("InputManager is null");
            throw new RuntimeException("InputManager is null");
        }
        List<InputMethodInfo> imeList = mInputManager.getInputMethodList();
        for (int i = 0; i < imeList.size(); i++)
        {
            InputMethodInfo imeInfo = imeList.get(i);
            if (null == imeInfo)
            {
                return false;
            }
            if (imeInfo.getId().equals(imeId))
            {
                return true;
            }
        }
        return false;
    }

    /**
     * Send the connected client's device Info. <br>
     * CN:发送连接的客户端设备信息。
     */
    private void sendClientDeviceInfo()
    {
        Intent intent = new Intent();
        intent.setAction(MultiScreenIntentAction.SEND_REMOTE_DEVICE_INFO);
        intent.putExtra("remoteIP", mRemoteIP);
        intent.putExtra("remotePort", mRemotePort);
        intent.putExtra("enableFromclient", mIsEnableFromClient);
        mContext.sendStickyBroadcast(intent);
    }

    /**
     * Notify VIme close tip keyboard. <br>
     * CN:通知虚拟输入法关闭提示键盘。
     */
    private void notifyCloseTipKeyboard()
    {
        Intent intent = new Intent();
        intent.setAction(MultiScreenIntentAction.VIME_SERVER_CLOSE_KEYBOARD);
        mContext.sendBroadcast(intent);
    }

    /**
     * Notify VIme irregular start. <br>
     * CN:通知虚拟输入法非正常启动。
     */
    private void sendVImeAbnormalStart()
    {
        Intent intent = new Intent();
        intent.setAction(MultiScreenIntentAction.VIME_ABNORMAL_START);
        mContext.sendBroadcast(intent);
    }

    /**
     * Parse byte message into Action. <br>
     * CN:将byte类型的消息解析为Action。
     * @param msg the received message. <br>
     *        CN:接收到的消息。
     * @return the parsed action. <br>
     *         CN:解析后的Action。
     */
    private Action parseVImeControlMsg(byte[] msg)
    {
        SaxXmlUtil saxTool = new SaxXmlUtil();
        Action recvAction = null;

        try
        {
            recvAction = saxTool.parse(msg);
        }
        catch (ParserConfigurationException e)
        {
            LogTool.e("ParserConfigurationException");
            e.printStackTrace();
        }
        catch (SAXException e)
        {
            // TODO Auto-generated catch block
            LogTool.e("SAXException");
            e.printStackTrace();
        }
        catch (IOException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
            LogTool.e("IOException");
        }

        return recvAction;
    }

    /**
     * Declare whether to notify VIme close tip keyboard. <br>
     * CN: 判断是否通知VIme关闭提示键盘
     * @param status client's current status. <br>
     *        CN:客户端当前的状态
     */
    private void defineVImeCloseTipKeyboard(VImeStatusDefine.VimeStatus status)
    {

        switch (status)
        {
            case INPUT_STATUS_VIME_CLIENT:
            {
                mClientNoInputCount = 0;
                break;
            }

            default:
            {
                if (mStatusObserver.getVImeStatus() == VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INPUT)
                {
                    if (mClientNoInputCount < CLIENT_READY_UPPER_LIMIT)
                    {
                        mClientNoInputCount++;
                    }

                    if (mClientNoInputCount == CLIENT_READY_UPPER_LIMIT)
                    {
                        LogTool.v("notify close tip keyboard");
                        notifyCloseTipKeyboard();
                    }
                }
                else
                {
                    mClientNoInputCount = 0;
                }

                break;
            }
        }

    }

    /**
     * Unregister receiver of broadcast.<br>
     * CN:反注册广播接收者。
     * @param receiver broadcast receiver.
     */
    private void unregisterBroadcastReceiver(BroadcastReceiver receiver)
    {
        try
        {
            mContext.unregisterReceiver(receiver);
        }
        catch (IllegalArgumentException e)
        {
            LogTool.d("the receiver was already unregistered or was not registered.");
        }
    }

}
