package com.hisilicon.multiscreen.protocol.remote;

import com.hisilicon.multiscreen.http.HiHttpClient;
import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.message.Action;
import com.hisilicon.multiscreen.protocol.message.Argument;
import com.hisilicon.multiscreen.protocol.message.ArgumentValue;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.message.VImeTextInfo;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.SaxXmlUtil;
import com.hisilicon.multiscreen.protocol.utils.VImeStateMachineDriverMessage;

/**
 * Transfer of text and cursor index in VIme client.<br>
 * CN:虚拟输入法客户端传送文字、光标位置。
 */
public class VImeClientTransfer
{
    /**
     * HTTP request timeout.<br>
     */
    private static final int HTTP_REQUEST_TIMEOUT = 2000;

    /**
     * Interface of HTTP client.<br>
     */
    private HiHttpClient mHiHttpClient = null;

    /**
     * VIME message parse.<br>
     */
    private SaxXmlUtil mSaxVirtualIMEClient = null;

    /**
     * VIme client state machine.
     */
    private static VImeClientStateMachine mVImeClientStateMachine = null;

    /**
     * Instance of VIME.<br>
     */
    private static VImeClientTransfer mVImeClientTransfer = null;

    /**
     * Get instance of this class.<br>
     * CN: 获得该类的单实例。
     * @param deviceInfo - device info of STB.
     * @return instance of the class
     */
    public static VImeClientTransfer getInstance(HiDeviceInfo deviceInfo)
    {
        if (mVImeClientTransfer == null)
        {
            mVImeClientTransfer = new VImeClientTransfer(deviceInfo);
        }
        else
        {
            mVImeClientTransfer.resetHttpClient(deviceInfo.getDeviceIP(),
                deviceInfo.getService(MessageDef.VIME_SERVER_TRANSFER).getServicePort());
            mVImeClientStateMachine = VImeClientStateMachine.getInstance();
        }

        return mVImeClientTransfer;
    }

    /**
     * Constructor of class.<br>
     * 构造方法
     */
    private VImeClientTransfer(HiDeviceInfo deviceInfo)
    {
        mHiHttpClient =
            new HiHttpClient(deviceInfo.getDeviceIP(), deviceInfo.getService(
                MessageDef.VIME_SERVER_TRANSFER).getServicePort(), HTTP_REQUEST_TIMEOUT);
        mSaxVirtualIMEClient = new SaxXmlUtil();
        mVImeClientStateMachine = VImeClientStateMachine.getInstance();
    }

    /**
     * Reset host IP and port of HTTP client.
     * @param ip - host IP for HTTP client.
     * @param port - port for HTTP client.
     */
    private void resetHttpClient(String ip, int port)
    {
        mHiHttpClient.setHostIp(ip);
        mHiHttpClient.setPort(port);
    }

    /**
     * Send text and cursor index to STB.<br>
     * CN:发送文字和光标信息给机顶盒
     * @param curText - 当前输入框中的文字内容
     * @param cursorIndex - 当前输入框中的光标位置
     */
    public Action sendText(int seq, String curText, int startSelection, int endSelection)
    {
        String str = null;
        Argument argument = new Argument();
        // Action responseAction = null;
        Action textMessage = new Action();

        ArgumentValue argSeq = new ArgumentValue();
        argSeq.setKey(VImeTextInfo.TEXT_SEQUENCE);
        argSeq.setValue(seq);
        argument.addArgumentValue(argSeq);

        ArgumentValue argText = new ArgumentValue();
        argText.setKey(VImeTextInfo.SRC_TEXT); // FIXME 原来是Text,按照协议改成小写
        argText.setValue(curText);
        argument.addArgumentValue(argText);

        ArgumentValue argStartSelection = new ArgumentValue();
        argStartSelection.setKey(VImeTextInfo.SRC_START_SELECTION);
        argStartSelection.setValue(startSelection);
        argument.addArgumentValue(argStartSelection);

        ArgumentValue argEndSelection = new ArgumentValue();
        argEndSelection.setKey(VImeTextInfo.SRC_END_SELECTION);
        argEndSelection.setValue(endSelection);
        argument.addArgumentValue(argEndSelection);

        textMessage.setId(Action.ACTION_ID_VIME_SEND_TEXT);
        textMessage.setName("sendText");
        textMessage.setResponseFlag("yes");
        textMessage.setResponseId(Action.ACTION_ID_VIME_RET_SEND_TEXT);
        textMessage.addArgument(argument);

        try
        {
            str = mSaxVirtualIMEClient.serialize(textMessage);
        }
        catch (Exception e)
        {
            LogTool.e("parse string error in sending text.");
            return null;
        }

        // Send HTTP request, which is Action of VIME.
        // FIXME we don't care about response in this function.
        mHiHttpClient.sendRequest(str);

        return null;
    }

    /**
     * Send end input request.<br>
     * CN:发送输入完成请求。
     * @param imeOptionIndex - index of VIME option.
     * @return action of response.
     */
    public Action endInput(int imeOptionIndex)
    {
        String str = null;
        // Action responseAction = null;
        Action endInput_message = getEndInputAction(imeOptionIndex);

        mVImeClientStateMachine.updateStatus(VImeStateMachineDriverMessage.END_INPUT);

        try
        {
            str = mSaxVirtualIMEClient.serialize(endInput_message);
        }
        catch (Exception e)
        {
            LogTool.e("parse input stream error");
            return null;
        }

        // send HTTP request, which is Action of VIME.
        // FIXME we don't care about response in this function.
        mHiHttpClient.sendRequest(str);

        return null;
    }

    /**
     * Get action of end input.<br>
     * CN:获取输入结束的Action.
     * @param imeOption - option of VIME
     * @return action of end input
     */
    private Action getEndInputAction(int imeOption)
    {
        Action endInput_message = new Action();
        Argument argument = new Argument();

        endInput_message.setId(Action.ACTION_ID_VIME_ENDINPUT_FROM_PHONE);
        endInput_message.setName("endInputFromPhone");
        ArgumentValue argumentValue = new ArgumentValue();
        argumentValue.setKey(VImeTextInfo.INPUT_OPTION);
        argumentValue.setValue(Integer.valueOf(imeOption));
        argument.addArgumentValue(argumentValue);

        endInput_message.addArgument(argument);
        endInput_message.setResponseFlag("yes");
        endInput_message.setResponseId(Action.ACTION_ID_VIME_RET_ENDINPUT_FROM_PHONE);

        return endInput_message;
    }
}
