package com.hisilicon.multiscreen.protocol.remote;

import java.io.IOException;
import java.io.UnsupportedEncodingException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerConfigurationException;

import org.xml.sax.SAXException;

import com.hisilicon.multiscreen.http.HiHttpClient;
import com.hisilicon.multiscreen.http.HiHttpRecvMsgListener;
import com.hisilicon.multiscreen.http.HiHttpResponse;
import com.hisilicon.multiscreen.http.HiHttpServer;
import com.hisilicon.multiscreen.protocol.ClientInfo;
import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.message.Action;
import com.hisilicon.multiscreen.protocol.message.Argument;
import com.hisilicon.multiscreen.protocol.message.ArgumentValue;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.SaxXmlUtil;
import com.hisilicon.multiscreen.protocol.utils.VImeStateMachineDriverMessage;
import com.hisilicon.multiscreen.protocol.utils.VImeStatusDefine;
import com.hisilicon.multiscreen.protocol.utils.VImeStatusDefine.VimeStatus;

/**
 * To drive state machine of VIme on client.<br>
 * CN:客户端虚拟输入法状态机驱动者。
 * @since HiMultiScreen V2.0.1.1 2013/01/11: first create
 */
public class VImeClientController
{
    /**
     * HTTP request timeout.<br>
     * CN:HTTP请求超时。<br>
     * Meet the high-delay network environment.<br>
     * CN:满足高延迟网络环境。
     */
    private static final int HTTP_REQUEST_TIMEOUT = 2000;

    /**
     * VIme check period.<br>
     * CN:VIme检查周期。
     */
    public static final long VIME_CHECK_PERIOD = 1000L;

    /**
     * Name of check VIme thread.<br>
     * CN:VIme状态检查线程名称。
     */
    private static final String CHECK_VIME_THREAD_NAME = "CheckVimeThread";

    /**
     * Instance of VIme client controller.<br>
     * CN:虚拟输入法客户端控制类实例。
     */
    private static VImeClientController mVImeClientController = null;

    /**
     * UTIL of SAX XML.
     */
    private SaxXmlUtil mSaxXmlUtil = null;

    /**
     * Instance of VIme client state machine.
     */
    private static VImeClientStateMachine mVImeClientStateMachine = null;

    /**
     * HTTP client.
     */
    private HiHttpClient mHiHttpClient = null;

    /**
     * HTTP server.
     */
    private HiHttpServer mHttpServer = null;

    /**
     * VIme activity handler.
     */
    private IVImeActivityHandler mVImeActivityHandler = null;

    /**
     * Check VIme thread.
     */
    private Thread mCheckVImeThread = null;

    /**
     * VIme check is running.
     */
    private boolean mIsRunning = false;

    /**
     * Get instance of this class
     * @param deviceInfo - device info
     * @return instance of the class
     */
    public static VImeClientController getInstance(HiDeviceInfo deviceInfo)
    {
        if (mVImeClientController == null)
        {
            mVImeClientController = new VImeClientController(deviceInfo);
        }
        else
        {
            mVImeClientController.setHostIp(deviceInfo.getDeviceIP());
            mVImeClientController.setHostPort(mVImeClientController
                .getVimeServerControlPort(deviceInfo));
            mVImeClientStateMachine = VImeClientStateMachine.getInstance();
        }
        return mVImeClientController;
    }

    /**
     * Constructor of this class
     * @param device - device info
     */
    VImeClientController(HiDeviceInfo deviceInfo)
    {
        initHttpClient(deviceInfo);
        mSaxXmlUtil = new SaxXmlUtil();
        mVImeClientStateMachine = VImeClientStateMachine.getInstance();
    }

    /**
     * Set VIme activity handler.
     * @param handler - VIme activity handler
     */
    public void setVimeActivityHandler(IVImeActivityHandler handler)
    {
        mVImeActivityHandler = handler;
    }

    /**
     * VIme is checking on Phone that means VIme is enable.<br>
     * CN:手机端VIme正在check，说明处于开启状态。
     * @return true if VIme is open.
     */
    public boolean isVImeEnable()
    {
        return mIsRunning;
    }

    /**
     * Destroy PushClient.<br>
     * CN:销毁VIme控制类。
     */
    public void destroy()
    {
        stopHttpServer();
        stopCheckThread();

        if (mVImeClientStateMachine != null)
        {
            mVImeClientStateMachine.deInitVimeClient();
        }

        setInstance(null);
    }

    /**
     * Return true if status of VIme is input on client.<br>
     * CN:检查VIme状态机是否为输入状态。
     * @return - true if VIme status is input.
     */
    public boolean isInputStatusOnClient()
    {
        if (mVImeClientStateMachine.getStatus() == VImeStatusDefine.VimeStatus.INPUT_STATUS_VIME_CLIENT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * Enable VIme.<br>
     * The function return true means VIme is opened on STB.<br>
     * CN:使能虚拟输入法，返回 true 表示打开了STB上的VIme。
     * @return - true if VIme is opened on STB.
     */
    public boolean enableVIme()
    {
        boolean isSuccess = false;
        Action responseAction = null;
        Action actionMsg = getEnableVImeAction(new Action());

        responseAction = sendRequestAction(actionMsg);

        if (responseAction == null)
        {
            LogTool.v("enable VIme responseAction is null.");
            isSuccess = false;
        }
        else if (responseAction.getId() == Action.ACTION_ID_VIME_RET_ENABLE)
        {
            VImeStatusDefine.VimeStatus newState =
                handleActionAndUpdateStateMachine(responseAction);

            // CN:当客户端VIME控制服务被异常杀掉后会重启，这种情况下本地状态机不是INIT
            // ，所以下面IF判断条件只要满足当前状态机不是DEINIT状态就可以。
            if (newState != VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT)
            {
                mVImeActivityHandler.openVimeSwitch();
                startCheckThread();
                startHttpServer();

                isSuccess = true;
                LogTool.d("Enable success on phone.");
            }
            else
            {
                // Stop HTTP server and check timer whatever VIme status is.
                stopHttpServer();
                stopCheckThread();

                isSuccess = false;
                LogTool.d("Enable fail on phone.");
            }
        }

        return isSuccess;
    }

    /**
     * Disable VIme.<br>
     * Transform state machine to DiInit status.
     * @return - true if disable success.
     */
    public boolean disableVIme()
    {
        boolean isSuccess = false;
        Action disableAction = getDisableVImeAction(new Action());
        Action responseAction = null;

        // Stop HTTP server and check timer whatever VIme status is.
        stopHttpServer();
        stopCheckThread();

        // Update state machine whatever it gets response.
        // CN:无论是否得到响应，都要更新状态机。
        mVImeClientStateMachine.updateStatus(VImeStateMachineDriverMessage.CLOSE_VIME);

        responseAction = sendRequestAction(disableAction);

        if (responseAction == null)
        {
            LogTool.e("disable VIme responseAction is null.");
            isSuccess = false;
        }
        else if (responseAction.getId() == Action.ACTION_ID_VIME_RET_DISABLE)
        {
            if (mVImeClientStateMachine.getStatus() == VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT)
            {
                LogTool.v("disable VIme success.");
                isSuccess = true;
            }
            else
            {
                LogTool.e("status is not deinit after disable vime!");
                isSuccess = false;
            }
        }

        return isSuccess;
    }

    /**
     * Set instance of VImeClientController.
     * @param control the instance.
     */
    private static void setInstance(VImeClientController control)
    {
        mVImeClientController = control;
    }

    /**
     * Get enable VIme action.<br>
     * CN:获取虚拟输入法使能消息。
     * @param action - object of Action
     * @return action of enable VIme
     */
    private Action getEnableVImeAction(Action action)
    {
        action.setId(Action.ACTION_ID_VIME_ENALBE);
        action.setName("enableVirtualIME");
        action.setResponseFlag("yes");
        action.setResponseId(Action.ACTION_ID_VIME_RET_ENABLE);

        return action;
    }

    /**
     * Get disable VIme action.<br>
     * CN:获取虚拟输入法去使能消息。
     * @param action - object of Action
     * @return action of disable VIme
     */
    private Action getDisableVImeAction(Action action)
    {
        action.setId(Action.ACTION_ID_VIME_DISABLE);
        action.setName("disableVirtualIME");
        action.setResponseFlag("yes");
        action.setResponseId(Action.ACTION_ID_VIME_RET_DISABLE);

        return action;
    }

    /**
     * Initialize http client.
     * @param deviceInfo - device info.
     */
    private void initHttpClient(HiDeviceInfo deviceInfo)
    {
        int port = getVimeServerControlPort(deviceInfo);
        mHiHttpClient = new HiHttpClient(deviceInfo.getDeviceIP(), port, HTTP_REQUEST_TIMEOUT);
        mHiHttpClient.debugOff();
    }

    /**
     * Set host IP.<br>
     * @param ip - host IP for HTTP client.
     */
    private void setHostIp(String ip)
    {
        mHiHttpClient.setHostIp(ip);
    }

    /**
     * Set port.<br>
     * @param port - port for HTTP client.
     */
    private void setHostPort(int port)
    {
        mHiHttpClient.setPort(port);
    }

    /**
     * Get vime server control port.<br>
     * @param deviceInfo - accessed deviceInfo.
     * @return port
     */
    private int getVimeServerControlPort(HiDeviceInfo deviceInfo)
    {
        int port = Integer.parseInt(MessageDef.VIME_CLIENT_CONTROL_PORT);

        if (deviceInfo != null
            && deviceInfo.getService(MessageDef.VIME_SERVER_CONTROL_NAME) != null)
        {
            port = deviceInfo.getService(MessageDef.VIME_SERVER_CONTROL_NAME).getServicePort();
        }
        else
        {
            LogTool
                .e("Vime server control service in deviceInfo is null, and init http client by default port "
                    + port);
        }
        return port;
    }

    /**
     * Start HTTP server for controlling VIme client.<br>
     * CN:启动HTTP服务器,用于控制虚拟输入法客户端。
     */
    private void startHttpServer()
    {
        if (mHttpServer == null)
        {
            LogTool.d("Start http server.");
            mHttpServer = new HiHttpServer();
            mHttpServer.setServerPort(ClientInfo.DEFAULT_VIME_CLIENT_CONTROL_PORT);
            mHttpServer.setHttpRecvMsgListener(mHiHttpMsglistener);
            mHttpServer.startServer();
        }
    }

    /**
     * Stop HTTP server.<br>
     * CN:停止HTTP服务器。
     */
    private void stopHttpServer()
    {
        if (mHttpServer != null)
        {
            mHttpServer.stopServer();
            mHttpServer = null;
        }
    }

    private HiHttpRecvMsgListener mHiHttpMsglistener = new HiHttpRecvMsgListener()
    {
        @Override
        public String onHttpMsgReceived(byte[] arg0, String remoteIP)
        {
            String response = null;
            try
            {
                response = vimeMessageHandle(arg0);
            }
            catch (Exception e)
            {
                LogTool.e("Vime Message parse exception.");
            }

            if (response == null)
            {
                response = "no_response";
            }
            return response;
        }
    };

    /**
     * Handle VIme message.<br>
     * It's the request of VIme on STB.<br>
     * CN:处理STB发送的VIme请求消息。
     * @param vimeMsg - string received.
     * @return response content
     * @throws IOException
     * @throws SAXException
     * @throws ParserConfigurationException
     */
    private String vimeMessageHandle(byte[] msg) throws ParserConfigurationException, SAXException,
        IOException
    {
        String responseString = null;
        Action receiveAction = null;
        Action responseAction = null;
        ArgumentValue argumentValue = null;

        // parse httpReq to action.
        receiveAction = mSaxXmlUtil.parse(msg);

        if (receiveAction == null)
        {
            LogTool.e("receiveAction is null.");
            return null;
        }
        else
        {
            responseAction = new Action();

            switch (receiveAction.getId())
            {
            /* Call input on client */
                case Action.ACTION_ID_VIME_CALL_INPUT:
                {
                    // Update state machine, construct Action of response.
                    // CN:更新状态机，构造 RET_CALL_INPUT_MODULE。

                    Argument argument = new Argument();

                    responseAction.setId(Action.ACTION_ID_VIME_RET_CALL_INPUT);
                    responseAction.setName("retCallInputModule");

                    VimeStatus StatusNow = handleActionAndUpdateStateMachine(receiveAction);
                    if (StatusNow == VImeStatusDefine.VimeStatus.INPUT_STATUS_VIME_CLIENT)
                    {
                        mVImeActivityHandler.callInput(receiveAction);
                        argumentValue = new ArgumentValue("result", 1);
                    }
                    else
                    {
                        argumentValue = new ArgumentValue("result", 0);
                        LogTool.e("callInput failed! status of VIme statemachine is :"
                            + StatusNow.getName());
                    }

                    argument.addArgumentValue(argumentValue);
                    responseAction.addArgument(argument);
                    responseAction.setResponseFlag("no");
                    responseAction.setResponseId(Action.ACTION_ID_NO_RESPONSE);

                    break;
                }
                /* End input on client */
                case Action.ACTION_ID_VIME_ENDINPUT_FROM_STB:
                {
                    Argument argument = new Argument();
                    responseAction.setId(Action.ACTION_ID_VIME_RET_ENDINPUT_FROM_STB);
                    responseAction.setName("retEndInputFromSTB");

                    if (handleActionAndUpdateStateMachine(receiveAction) == VImeStatusDefine.VimeStatus.READY_STATUS_VIME_CLIENT)
                    {
                        // End input from STB, content input activity will not
                        // send endInput request action.
                        mVImeActivityHandler.endInputByServer();
                        argumentValue = new ArgumentValue("result", 1);

                    }
                    else
                    {
                        argumentValue = new ArgumentValue("result", 0);
                    }

                    argument.addArgumentValue(argumentValue);
                    responseAction.addArgument(argument);
                    responseAction.setResponseFlag("no");
                    responseAction.setResponseId(Action.ACTION_ID_NO_RESPONSE);

                    break;
                }
                /* Disable VIme on client */
                case Action.ACTION_ID_VIME_DISABLE:
                {
                    // CN:STB主动切掉VIme。
                    Argument argument = new Argument();
                    responseAction.setId(Action.ACTION_ID_VIME_RET_DISABLE);
                    responseAction.setName("retDisableVirtualIME");

                    if (handleActionAndUpdateStateMachine(receiveAction) == VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT)
                    {
                        mVImeActivityHandler.closeVimeSwitch();
                        stopHttpServer();
                        stopCheckThread();

                        argumentValue = new ArgumentValue("result", 1);

                    }
                    else
                    {
                        LogTool.e("VIme can't be disable on client.");
                        argumentValue = new ArgumentValue("result", 0);
                    }

                    argument.addArgumentValue(argumentValue);
                    responseAction.addArgument(argument);
                    responseAction.setResponseFlag("no");
                    responseAction.setResponseId(Action.ACTION_ID_NO_RESPONSE);

                    break;
                }
                default:
                {
                    /* id of action received is not defined */
                    responseAction.setId(Action.ACTION_ID_NO_RESPONSE);
                    responseAction.setName("defaultResponse");
                    responseAction.setResponseFlag("no");
                    responseAction.setResponseId(Action.ACTION_ID_NO_RESPONSE);
                    break;
                }

            }
        }

        LogTool.v("receive action name is :" + receiveAction.getName());

        // default content of response is null.
        try
        {
            responseString = mSaxXmlUtil.serialize(responseAction);
        }
        catch (TransformerConfigurationException e)
        {
            responseString = null;
            LogTool.e("transformer configuration exception.");
        }

        return responseString;
    }

    /**
     * Start check VIme from client.<br>
     * CN:启动VIme状态检查线程。
     */
    private void startCheckThread()
    {
        mIsRunning = true;

        // CN:客户端启动VIme后手动将INIT状态切换成READY状态，以接收CALL_INPUT指令。
        mVImeClientStateMachine.updateStatus(VImeStateMachineDriverMessage.CHECK_OK);

        if ((mCheckVImeThread == null) || (!mCheckVImeThread.isAlive()))
        {
            mCheckVImeThread = new Thread(new CheckSTBVimeRunnable());
            mCheckVImeThread.setName(CHECK_VIME_THREAD_NAME);
            mCheckVImeThread.setDaemon(true);
            mCheckVImeThread.start();
        }
    }

    /**
     * Stop check VIme from client.<br>
     * CN:停止VIme状态检查线程。
     */
    private void stopCheckThread()
    {
        mIsRunning = false;
        if (mCheckVImeThread != null && mCheckVImeThread.isAlive())
        {
            try
            {
                mCheckVImeThread.join(1000);
            }
            catch (InterruptedException e)
            {
                LogTool.e("InterruptedException when StopCheckVime");
            }
        }
        mCheckVImeThread = null;
    }

    /**
     * Send check VIme and update state machine by response action, it is an
     * runnable class.<br>
     * CN:可运行类，用于发送VIme状态检查消息，并根据响应的Action更新状态机。
     */
    private class CheckSTBVimeRunnable implements Runnable
    {
        /**
         * Max times of check fail.<br>
         * CN:VIme检查最大失败次数。
         */
        private static final short MAX_CHECK_FAIL_TIMES = 6;

        /**
         * Minimize times of check fail.<br>
         * CN:VIme检查最小失败次数。<br>
         * It must be less than MAX_CHECK_FAIL_NUM.<br>
         * CN:必须小于MAX_CHECK_FAIL_NUM。
         */
        private static final short MIN_CHECK_STB_FAIL_TIMES = 3;

        /**
         * Max times of check STB in no_input status.<br>
         * CN:VIme检查到STB非输入状态的最大允许次数。
         */
        private static final short MAX_CHECK_STB_NO_INPUT_TIMES = 6;

        /**
         * Max times of check phone in no_input status.<br>
         * CN:VIme检查到手机非输入状态的最大允许次数。
         */
        private static final short MAX_CHECK_PHONE_NO_INPUT_TIMES = 3;

        /**
         * Check fail times.<br>
         * CN:VIme检查失败次数。
         */
        private short mCheckSTBFailTimes = 0;

        /**
         * Times of check STB in no_input status while phone or state machine of
         * client is not input status.<br>
         * CN:连续检查到STB非输入状态，而状态状态机或手机是输入状态的次数。<br>
         * If it is more than max times, IME on phone will be end input.<br>
         * CN:如果超过最大值，则结束手机输入界面。
         */
        private short mCheckSTBNotInputTimes = 0;

        /**
         * Times of check phone is not input status while state machine of
         * client is input status.<br>
         * CN:连续检查到手机非输入，而客户端状态状态机是input的次数。
         */
        private short mCheckPhoneNotInputTimes = 0;

        /**
         * STB VIme status.<br>
         * CN:STB的VIme状态。
         */
        private VImeStatusDefine.VimeStatus VImeSTBStatus = null;

        @Override
        public void run()
        {

            while (mIsRunning)
            {
                // CN:检查STB状态并得到响应。
                VImeSTBStatus = sendCheckMessage();

                if ((VImeSTBStatus == VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INIT)
                    || (VImeSTBStatus == VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_READY))
                {
                    // CN:服务端为就绪状态，check是OK。
                    // CN:STB短暂的INIT状态也认为检查成功，可以响应来自STB的CALL_INPUT。

                    mCheckSTBFailTimes = 0;
                    mCheckPhoneNotInputTimes = 0;
                    mVImeClientStateMachine.updateStatus(VImeStateMachineDriverMessage.CHECK_OK);

                    if ((mVImeClientStateMachine.getStatus() == VImeStatusDefine.VimeStatus.INPUT_STATUS_VIME_CLIENT)
                        || (mVImeActivityHandler.isInputActivityOnTop() == true))
                    {
                        // Stop input activity on client if check STB is not
                        // input status for continuous MAX_CHECK_NO_INPUT_TIMES
                        // times.
                        // CN:如果手机为Input，但STB检查结果非Input状态，则增加连续次数，超过上限就关闭本地输入框。

                        if (mCheckSTBNotInputTimes < MAX_CHECK_STB_NO_INPUT_TIMES)
                        {
                            mCheckSTBNotInputTimes++;
                        }
                        else
                        {
                            // CN:STB状态与手机不同,则结束本地输入,用endInputByServer()方法是为了不再向STB发送消息。
                            mVImeActivityHandler.endInputByServer();
                            mVImeClientStateMachine
                                .updateStatus(VImeStateMachineDriverMessage.END_INPUT);
                            mCheckSTBNotInputTimes = 0;
                            LogTool
                                .d("End input on client because we find STB is not in input status a few time.");
                        }
                    }
                    else
                    {
                        mCheckSTBNotInputTimes = 0;
                    }
                }
                else if (VImeSTBStatus == VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INPUT)
                {
                    mCheckSTBFailTimes = 0;
                    mCheckSTBNotInputTimes = 0;
                    mVImeClientStateMachine.updateStatus(VImeStateMachineDriverMessage.CHECK_OK);

                    // CN:如果手机输入页面不在顶层，但本地状态机却是input状态，连续若干次，则更新本地状态。
                    if ((mVImeClientStateMachine.getStatus() == VImeStatusDefine.VimeStatus.INPUT_STATUS_VIME_CLIENT)
                        && (mVImeActivityHandler.isInputActivityOnTop() == false))
                    {
                        if (mCheckPhoneNotInputTimes < MAX_CHECK_PHONE_NO_INPUT_TIMES)
                        {
                            mCheckPhoneNotInputTimes++;
                        }
                        else
                        {
                            mVImeActivityHandler.endInputByServer();
                            mVImeClientStateMachine
                                .updateStatus(VImeStateMachineDriverMessage.END_INPUT);
                            mCheckPhoneNotInputTimes = 0;
                        }
                    }
                    else
                    {
                        mCheckPhoneNotInputTimes = 0;
                    }
                }
                else
                {
                    mCheckSTBFailTimes++;

                    if (mCheckSTBFailTimes == MIN_CHECK_STB_FAIL_TIMES)
                    {
                        if (mVImeClientStateMachine.getStatus() == VImeStatusDefine.VimeStatus.INPUT_STATUS_VIME_CLIENT)
                        {
                            // Stop input activity on client if check fail
                            // MIN_CHECK_FAIL_TIMES times.
                            // CN:只要出现 MIN_CHECK_FAIL_TIMES
                            // 次check失败，就结束输入变为setup状态。会出现输入自动关闭的状况，属于正常现象。

                            mVImeActivityHandler.endInputBySelf();
                            LogTool.d("check fail 3 times, activity handler endInput by self.");
                        }

                        /* To setup status */
                        mVImeClientStateMachine
                            .updateStatus(VImeStateMachineDriverMessage.CHECK_FAIL);
                    }
                    else if (mCheckSTBFailTimes > MAX_CHECK_FAIL_TIMES)
                    {
                        // When it checks failed MAX_CHECK_FAIL_NUM times, it
                        // means VIme is down in STB. CN:检查失败
                        // MAX_CHECK_FAIL_NUM 次后，判断STB侧VIme关闭，停止检查，并关闭输入法。

                        mVImeClientStateMachine
                            .updateStatus(VImeStateMachineDriverMessage.CHECK_FAIL);

                        // Check failed MAX_CHECK_FAIL_NUM times, switch VIme on
                        // client and finish check thread.
                        mVImeActivityHandler.closeVimeSwitch();
                        mIsRunning = false;
                        // To stop http server, State machine is deinit.
                        stopHttpServer();
                    }
                }

                if (mIsRunning)
                {
                    try
                    {
                        Thread.sleep(VIME_CHECK_PERIOD);
                    }
                    catch (InterruptedException e)
                    {
                        LogTool.e("Interrupted Exception");
                    }
                }
            }
        }
    }

    /**
     * Send check VIme message to STB.<br>
     * CN:发送状态检查消息。
     * @return - VIme status on STB.
     */
    private VImeStatusDefine.VimeStatus sendCheckMessage()
    {
        ArgumentValue argValueStatus = new ArgumentValue();
        Argument argument = new Argument();
        Action actionMsg = new Action();
        Action responseAction = null;

        argValueStatus.setKey("status");
        argValueStatus.setValue(mVImeClientStateMachine.getStatusIndex());
        argument.addArgumentValue(argValueStatus);

        actionMsg.setId(Action.ACTION_ID_VIME_CHECK);
        actionMsg.setName("checkStatus");
        actionMsg.setResponseFlag("yes");
        actionMsg.setResponseId(Action.ACTION_ID_VIME_RET_CHECK);
        actionMsg.addArgument(argument);

        responseAction = sendRequestAction(actionMsg);

        if (responseAction != null && responseAction.getId() == Action.ACTION_ID_VIME_RET_CHECK)
        {
            int serverState =
                ((Integer) responseAction.getArgument(0).getArgumentValue(1).getVaule()).intValue();
            return VImeStatusDefine.VimeStatus.getStatus(serverState);
        }
        else
        {
            LogTool.d("check response error.");
            return null;
        }
    }

    /**
     * Send action of VIme and get response.<br>
     * CN:发送VIme消息，返回响应消息。
     * @param actionMsg - action be sent
     * @return - action in response
     */
    private Action sendRequestAction(Action actionMsg)
    {
        String str = "";
        Action responseAction = null;
        try
        {
            str = mSaxXmlUtil.serialize(actionMsg);
        }
        catch (Exception e)
        {
            LogTool.e("serialize exception");
            return null;
        }

        /** send HTTP request, which is Action of VIme. */
        HiHttpResponse httpResponse = mHiHttpClient.sendRequest(str);
        String responseContent = httpResponse.getResponseMessage();
        // LogTool.v("receive string in response: " + httpResContent);

        if ((responseContent == null) || (responseContent.length() == 0))
        {
            LogTool.d("action response is null.");
            return null;
        }

        try
        {
            responseAction = mSaxXmlUtil.parse(responseContent.getBytes(SaxXmlUtil.ENCODE_UTF_8));
        }
        catch (UnsupportedEncodingException e)
        {
            responseAction = null;
            LogTool.e("unsupported encoding exception.");
        }
        catch (ParserConfigurationException e)
        {
            responseAction = null;
            LogTool.e("parse configuration exception.");
        }
        catch (SAXException e)
        {
            responseAction = null;
            LogTool.e("SAX exception.");
        }
        catch (IOException e)
        {
            responseAction = null;
            LogTool.e("IO exception.");
        }

        /**
         * only for testing.
         */
        // if (responseAction != null)
        // {
        // LogTool.i("send action:" + actionMsg.getName() + "/" +
        // actionMsg.getId()
        // + ", receive response:" + responseAction.getName() + "/" +
        // responseAction.getId());
        // // responseAction.debugInfor();
        // }

        return responseAction;
    }

    /**
     * Handle received VIme Action, and update state machine.<br>
     * CN:处理收到的虚拟输入法Action，并更新状态机。
     * @param action - received action of VIme.
     * @return - status of state machine after handling action.
     */
    private VImeStatusDefine.VimeStatus handleActionAndUpdateStateMachine(Action action)
    {
        /** Input protection */
        if (action == null)
        {
            return null;
        }
        /*
         * 收到的action，index与状态机驱动消息id并不完全对应
         * 比如EndInput驱动消息可以是手机结束消息，也可以是STB结束消息，Action的id不一样，需要Action到状态机驱动的转换工作
         */
        VImeStateMachineDriverMessage stateDriverMsg = null;
        switch (action.getId())
        {
            case Action.ACTION_ID_VIME_RET_ENABLE:
            {
                stateDriverMsg = VImeStateMachineDriverMessage.OPEN_VIME;
                break;
            }

            case Action.ACTION_ID_VIME_RET_DISABLE:
            {
                // Update state machine without response of
                // STB. CN:客户端关闭VIme后立即更新状态，不用等待response返回。
                stateDriverMsg = VImeStateMachineDriverMessage.CLOSE_VIME;
                LogTool.v("receive action vime ret disable");
                break;
            }

            case Action.ACTION_ID_VIME_DISABLE:
            {
                stateDriverMsg = VImeStateMachineDriverMessage.CLOSE_VIME;
                break;
            }

            case Action.ACTION_ID_VIME_CALL_INPUT:
            {
                stateDriverMsg = VImeStateMachineDriverMessage.CALL_INPUT;
                break;
            }

            case Action.ACTION_ID_VIME_ENDINPUT_FROM_STB:
            {
                stateDriverMsg = VImeStateMachineDriverMessage.END_INPUT;
                break;
            }

            default:
            {
                LogTool.e("Action id is null");
                break;
            }
        }

        return mVImeClientStateMachine.updateStatus(stateDriverMsg);

    }
}
