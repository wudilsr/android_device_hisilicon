package com.hisilicon.multiscreen.protocol.message;

import java.util.ArrayList;

/**
 * The class is used to describe the interaction of the VIME messages.and it
 * describes the accessing control message.<br>
 * CN:该类描述虚拟输入法的交互消息。<br>
 * 同时描述了接入控制的消息，允许后来者抢占。<br>
 * @since HiMultiScreen_V2.0.1.0<br>
 *        2013/1/14, add description of the access control message,mainly
 *        message type and add final to message type.<br>
 *        CN:2013/1/14，增加接入控制的消息描述，主要是增加消息类型，同时将以前的消息类型前面增加final修饰符。<br>
 *        2013/1/30,add new define of the VIME messages.<br>
 *        CN:2013/1/14，增加虚拟输入法新消息定义。<br>
 *        2013/2/6, add new define of the remote application messages.<br>
 *        CN:2013/2/6，增加远程应用新消息定义。<br>
 */
public class Action
{

    // FIXME 公共消息定义

    /**
     * No response.<br>
     * CN:无回应消息。
     */
    public static final int ACTION_ID_NO_RESPONSE = 0;

    public static final int ACTION_ID_XML_PARSE_ERROR_RESPONSE = 0x001;

    // FIXME 接入控制消息定义

    /**
     * Mobile connecting notify message ID.<br>
     * CN:手持设备接入通知消息。
     */
    public static final int ACTION_ID_ACCESS_CONTROLLER_ACCESS_NOTIFY = 0x1200;

    /**
     * "retAccessNotify" message ID.<br>
     * CN:手持设备接入通知消息的返回消息类型。
     */
    public static final int ACTION_ID_ACCESS_CONTROLLER_RET_ACCESS_NOTIFY = 0x1201;

    /**
     * "byeForReave" message ID.<br>
     * CN:通知前一个接入设备连接被抢占。
     */
    public static final int ACTION_ID_ACCESS_CONTROLLER_BYE_FOR_REAVE = 0x1210;

    /**
     * "retByeForReave" message ID.<br>
     * CN:通知前一个接入设备连接被抢占的返回消息。
     */
    public static final int ACTION_ID_ACCESS_CONTROLLER_RET_BYE_FOR_REAVE = 0x1211;

    /**
     * "leaveNotifyByPhone" message ID.<br>
     * CN:手持设备离开时发出的离开消息。
     */
    public static final int ACTION_ID_ACCESS_CONTROLLER_LEAVE_NOTIFY_BY_PHONE = 0x1220;

    /**
     * "retLeaveNotifyByPhone" message ID.<br>
     * CN:手持设备离开时发出的离开消息。
     */
    public static final int ACTION_ID_ACCESS_CONTROLLER_RET_LEAVE_NOTIFY_BY_PHONE = 0x1221;

    /**
     * "leaveNotifyBySTB" message ID.<br>
     * CN:机顶盒的多屏服务关闭时发送leaveNotifyBySTB消息。
     */
    public static final int ACTION_ID_ACCESS_CONTROLLER_LEAVE_NOTIFY_BY_STB = 0x1230;

    /**
     * "retLeaveNotifyBySTB" message ID.<br>
     * CN:机顶盒的多屏服务关闭时发送leaveNotifyBySTB消息的返回消息。
     */
    public static final int ACTION_ID_ACCESS_CONTROLLER_RET_LEAVE_NOTIFY_BY_STB = 0x1231;

    // FIXME 虚拟输入法消息定义

    /**
     * Flag of return success message.<br>
     * CN:返回成功消息的标示。
     */
    public static final int ACTION_ID_VIME_SUCCESS_FLAG = 1;

    /**
     * Flag of return fail message.<br>
     * CN:返回失败消息的标示。
     */
    public static final int ACTION_ID_VIME_FAIL_FLAG = 0;

    /**
     * Enable virtual IME message id.<br>
     * CN:虚拟输入法使能消息id。
     */
    public static final int ACTION_ID_VIME_ENALBE = 0x1101;

    /**
     * Enable virtual IME response message id.<br>
     * CN:虚拟输入法使能回应消息id。
     */
    public static final int ACTION_ID_VIME_RET_ENABLE = 0x1102;

    /**
     * Disable virtual IME message id.<br>
     * CN:虚拟输入法去使能消息id。
     */
    public static final int ACTION_ID_VIME_DISABLE = 0x1111;

    /**
     * Disable virtual IME response message id.<br>
     * CN:虚拟输入法去使能回应消息id。
     */
    public static final int ACTION_ID_VIME_RET_DISABLE = 0x1112;

    /**
     * Check status message id.<br>
     * CN:虚拟输入法去检查消息id。
     */
    public static final int ACTION_ID_VIME_CHECK = 0x1121;

    /**
     * Check status response message id.<br>
     * CN:状态检查回应消息id。
     */
    public static final int ACTION_ID_VIME_RET_CHECK = 0x1122;

    /**
     * Call input module message id.<br>
     * CN:调出输入模块消息id。
     */
    public static final int ACTION_ID_VIME_CALL_INPUT = 0x5001;

    /**
     * Call input module response message id.<br>
     * CN:调出输入模块回应消息id。
     */
    public static final int ACTION_ID_VIME_RET_CALL_INPUT = 0x5002;

    /**
     * Send text message id.<br>
     * CN:文本发送消息id。
     */
    public static final int ACTION_ID_VIME_SEND_TEXT = 0x5011;

    /**
     * Send text response message id.<br>
     * CN:文本发送回应消息id。
     */
    public static final int ACTION_ID_VIME_RET_SEND_TEXT = 0x5012;

    /**
     * End input message from phone id.<br>
     * CN:手机侧结束输入消息id。
     */
    public static final int ACTION_ID_VIME_ENDINPUT_FROM_PHONE = 0x5021;

    /**
     * End input response message from phone id.<br>
     * CN:手机侧结束输入消息回应消息id。
     */
    public static final int ACTION_ID_VIME_RET_ENDINPUT_FROM_PHONE = 0x5022;

    /**
     * End input message from STB id.<br>
     * CN:机顶盒侧结束输入消息id。
     */
    public static final int ACTION_ID_VIME_ENDINPUT_FROM_STB = 0x5031;

    /**
     * End input response message from STB id.<br>
     * CN:机顶盒侧结束输入回应消息id。
     */
    public static final int ACTION_ID_VIME_RET_ENDINPUT_FROM_STB = 0x5032;

    // FIXME 远程应用消息定义

    /**
     * Id of remote application update list.<br>
     * CN:远程应用更新应用列表消息id。
     */
    public static final int ACTION_ID_REMOTE_APP_UPDATE_LIST = 0x3001;

    /**
     * Id response of remote application update list.<br>
     * CN:更新应用列表的回应消息id。
     */
    public static final int ACTION_ID_REMOTE_APP_RET_UPDATE_LIST = 0x3002;

    /**
     * Id of launch remote application.<br>
     * CN:启动远程应用的消息id。
     */
    public static final int ACTION_ID_REMOTE_APP_LAUNCH = 0x3011;

    /**
     * Id of response of launch remote application.<br>
     * CN:启动远程应用的回应消息id。
     */
    public static final int ACTION_ID_REMOTE_APP_RET_LAUNCH = 0x3012;

    /**
     * Id of send speech recognize result info.<br>
     * CN:语音识别结果消息id。
     */
    public static final int ACTION_ID_SPEECH_TEXT_SEND = 0x4001;

    /**
     * Id of response of send speech text info.<br>
     * CN:语音识别结果回应消息id。
     */
    public static final int ACTION_ID_SPEECH_TEXT_RET_SEND = 0x4002;

    /**
     * Id of start speaking.<br>
     * CN:启动语音id。
     */
    public static final int ACTION_ID_START_SPEAKING = 0x4011;

    /**
     * Id of response of send speech text info.<br>
     * CN:启动语音回应消息id。
     */
    public static final int ACTION_ID_RET_START_SPEAKING = 0x4012;

    /**
     * Id of stop speaking.<br>
     * CN:停止语音消息id。
     */
    public static final int ACTION_ID_STOP_SPEAKING = 0x4021;

    /**
     * Id of response of send speech text info.<br>
     * CN:停止语音的回应消息id。
     */
    public static final int ACTION_ID_RET_STOP_SPEAKING = 0x4022;

    /**
     * Id of send audio data.<br>
     * CN:语音发送消息id。
     */
    public static final int ACTION_ID_AUDIO_DATA_SEND = 0x4031;

    /**
     * Id of response of send audio data.<br>
     * CN:语音发送的回应消息id。
     */
    public static final int ACTION_ID_RET_AUDIO_DATA_SEND = 0x4032;

    /**
     * Id of speech error info.<br>
     * CN:语音错误消息id。
     */
    public static final int ACTION_ID_SPEECH_ERROR = 0x4041;

    /**
     * Id of response of send speech error info.<br>
     * CN:语音错误回应消息id。
     */
    public static final int ACTION_ID_SPEECH_ERROR_RET_SEND = 0x4042;

    // FIXME 其他成员变量

    protected ArrayList<Argument> mArgumentList = new ArrayList<Argument>();

    protected int mId = 0;

    protected String mName = null;

    protected int mResponseId = 0;

    protected String mResponseFlag = null;

    /**
     * 构造方法
     */
    public Action()
    {

    }

    /**
     * 构造方法
     * @param id 对应信息的ID
     * @param name 虚拟输入法消息名称
     */
    public Action(int id, String name)
    {
        this.mId = id;
        this.mName = name;
    }

    /**
     * Get ID of action.<br>
     * CN:获得虚拟输入法的消息ID。
     * @return ID of action.
     */
    public int getId()
    {
        return mId;
    }

    /**
     * 设置虚拟输入法的消息ID
     * @param id - 消息ID
     */
    public void setId(int id)
    {
        this.mId = id;
    }

    /**
     * 获得虚拟输入法的消息名称
     * @return - 虚拟你输入法的消息名称称
     */
    public String getName()
    {
        return mName;
    }

    /**
     * 设置虚拟输入法的消息名称
     * @param name - 消息名称
     */
    public void setName(String name)
    {
        this.mName = name;
    }

    /**
     * 获取本消息的回复消息ID
     * @return - 回复本消息的消息ID
     */
    public int getResponseId()
    {
        return mResponseId;
    }

    /**
     * 设置回应消息ID
     * @param responseId - 回应消息ID
     */
    public void setResponseId(int responseId)
    {
        this.mResponseId = responseId;
    }

    /**
     * 获取回应消息的flag值（通常是yes 或者,代表有回应或者无回应）
     * @return - 回复消息的flag值，yes或者no
     */
    public String getResponseFlag()
    {
        return mResponseFlag;
    }

    /**
     * 设置回复消息的flag值，yes 或者no
     * @param responseFlag - 回复消息的flag值
     */
    public void setResponseFlag(String responseFlag)
    {
        this.mResponseFlag = responseFlag;
    }

    /**
     * 增加消息参数
     * @param argument - 消息参数
     */
    public void addArgument(Argument argument)
    {

        mArgumentList.add(argument);
    }

    /**
     * Get argument of index in list.<br>
     * CN:获取消息的第index参数。
     * @param index - index of argument in list.<br>
     *        CN:虚拟输入法的第index参数。
     * @return argument.
     */
    public Argument getArgument(int index)
    {
        if (index >= mArgumentList.size())
        {
            return null;
        }
        return mArgumentList.get(index);
    }

    /**
     * 获取本条消息的参数列表
     * @return - 本条消息的参数列表
     */
    public ArrayList<Argument> getArgumentList()
    {
        return mArgumentList;
    }

}
