package com.hisilicon.multiscreen.protocol.remote;

import java.io.IOException;
import java.io.UnsupportedEncodingException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerConfigurationException;

import org.xml.sax.SAXException;

import com.hisilicon.multiscreen.http.HiHttpClient;
import com.hisilicon.multiscreen.http.HiHttpResponse;
import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.message.Action;
import com.hisilicon.multiscreen.protocol.message.Argument;
import com.hisilicon.multiscreen.protocol.message.ArgumentValue;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.SaxXmlUtil;

/**
 * Class speech control.<br>
 * CN:推送语音控制消息类。
 */
public class RemoteSpeech
{
    /**
     * Port of push server on STB.
     */
    private static final int STB_PUSH_SERVER_PORT = 8867;

    /**
     * Timeout of HTTP request.
     */
    private static final int HTTP_REQUEST_TIMEOUT = 3000;

    /**
     * Encoding char set.
     */
    private static final String ENCODE_CHARSET = SaxXmlUtil.ENCODE_UTF_8;

    /**
     * HTTP client for sending push server message.
     */
    private HiHttpClient mHiHttpClient = null;

    /**
     * IP of STB.
     */
    private String mHostIp = "";

    /**
     * Sax XML util.
     */
    private SaxXmlUtil mSaxXmlUtil = null;

    /**
     * Constructor of remote application list.<br>
     * CN:远程应用构造函数。
     * @param deviceInfo - device info
     */
    public RemoteSpeech(HiDeviceInfo deviceInfo)
    {
        if (deviceInfo == null)
        {
            LogTool.e("device info is null in remote app list.");
        }
        else
        {
            mHostIp = deviceInfo.getDeviceIP();
            mHiHttpClient = new HiHttpClient(mHostIp, STB_PUSH_SERVER_PORT, HTTP_REQUEST_TIMEOUT);
            mSaxXmlUtil = new SaxXmlUtil();
        }
    }

    /**
     * Destroy remote speech.<br>
     * CN:远程语音控制去初始化。
     */
    public void destroy()
    {

    }

    /**
     * Reset HiDevice info. CN:重置多屏设备信息。
     * @param deviceInfo HiDevice
     */
    protected void resetDevice(HiDeviceInfo deviceInfo)
    {
        mHostIp = deviceInfo.getDeviceIP();
        mHiHttpClient.setHostIp(mHostIp);
    }

    /**
     * Send speech recognize result.<br>
     * CN:发送语音识别结果。
     */
    public void sendSpeechInfo(String speechInfo, int type)
    {
        Action sendSpeechAction = getSendSpeechInfoAction(new Action(), speechInfo, type);
        sendRequestAction(sendSpeechAction);
    }

    /**
     * Send audio data.<br>
     * CN:发送语音数据。
     */
    public void sendAudioDate(byte[] audiodate, int seq)
    {
        Action sendAudioAction = getRecordAudioDataAction(new Action(), audiodate, seq);
        sendRequestAction(sendAudioAction);
    }

    public void sendErrorInfo(String error)
    {
        Action sendErrorAction = getSendErrorInfoAction(new Action(), error);
        sendRequestAction(sendErrorAction);
    }

    /**
     * Start speaking.<br>
     * CN:开始说话。
     */
    public void startSpeak()
    {
        Action startSpeak = getStartSpeakAction(new Action());
        sendRequestAction(startSpeak);
    }

    /**
     * Stop speaking.<br>
     * CN:停止说话。
     */
    public void stopSpeak()
    {
        Action stopSpeak = getStopSpeakAction(new Action());
        sendRequestAction(stopSpeak);
    }

    private Action getSendSpeechInfoAction(Action action, String speechInfo, int type)
    {
        Argument argument = new Argument();

        ArgumentValue argumentValue = new ArgumentValue("SpeechInfo", speechInfo);
        argument.addArgumentValue(argumentValue);

        ArgumentValue typeArgValue = new ArgumentValue("ResultType", type);
        argument.addArgumentValue(typeArgValue);

        action.setId(Action.ACTION_ID_SPEECH_TEXT_SEND);
        action.setName("sendSpeechInfo");
        action.setResponseFlag("yes");
        action.setResponseId(Action.ACTION_ID_SPEECH_TEXT_RET_SEND);
        action.addArgument(argument);
        return action;
    }

    private Action getSendErrorInfoAction(Action action, String error)
    {
        Argument argument = new Argument();
        ArgumentValue argumentValue = null;
        argumentValue = new ArgumentValue("SpeechErrorInfo", error);
        argument.addArgumentValue(argumentValue);

        action.setId(Action.ACTION_ID_SPEECH_ERROR);
        action.setName("sendSpeechErrorInfo");
        action.setResponseFlag("yes");
        action.setResponseId(Action.ACTION_ID_SPEECH_ERROR_RET_SEND);
        action.addArgument(argument);
        return action;
    }

    private Action getRecordAudioDataAction(Action action, byte[] audiodate, int seq)
    {
        Argument argument = new Argument();
        ArgumentValue argumentValue = null;
        argumentValue = new ArgumentValue("Audio", audiodate);
        argument.addArgumentValue(argumentValue);

        ArgumentValue SeqArgValue = null;
        SeqArgValue = new ArgumentValue("Seq", seq);
        argument.addArgumentValue(SeqArgValue);

        action.setId(Action.ACTION_ID_SPEECH_TEXT_SEND);
        action.setName("sendAudioData");
        action.setResponseFlag("yes");
        action.setResponseId(Action.ACTION_ID_SPEECH_TEXT_RET_SEND);
        action.addArgument(argument);
        return action;
    }

    private Action getStartSpeakAction(Action action)
    {
        action.setId(Action.ACTION_ID_START_SPEAKING);
        action.setName("StartSpeaking");
        action.setResponseFlag("yes");
        action.setResponseId(Action.ACTION_ID_RET_START_SPEAKING);
        return action;
    }

    private Action getStopSpeakAction(Action action)
    {
        action.setId(Action.ACTION_ID_STOP_SPEAKING);
        action.setName("StopSpeaking");
        action.setResponseFlag("yes");
        action.setResponseId(Action.ACTION_ID_RET_STOP_SPEAKING);
        return action;
    }

    /**
     * Send action of request and get response.<br>
     * @param actionMsg - action be sent
     * @return - action in response
     */
    private Action sendRequestAction(Action actionMsg)
    {
        String str = null;
        Action responseAction = null;
        String responseContent = null;

        try
        {
            str = mSaxXmlUtil.serialize(actionMsg);
        }
        catch (TransformerConfigurationException e)
        {
            LogTool.e(e.getMessage());
            return null;
        }
        catch (SAXException e)
        {
            LogTool.e(e.getMessage());
        }

        // Send HTTP request, which is Action of push server.
        HiHttpResponse httpResponse = mHiHttpClient.sendRequest(str);

        try
        {
            responseContent = new String(httpResponse.getMessage(), ENCODE_CHARSET);
        }
        catch (UnsupportedEncodingException e1)
        {
            LogTool.e("Unsupported Encoding Exception.");
        }

        if ((responseContent == null) || (responseContent.length() == 0))
        {
            LogTool.e("action response is null.");
            return null;
        }

        try
        {
            responseAction = mSaxXmlUtil.parse(responseContent.getBytes(ENCODE_CHARSET));
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

        return responseAction;
    }

}
