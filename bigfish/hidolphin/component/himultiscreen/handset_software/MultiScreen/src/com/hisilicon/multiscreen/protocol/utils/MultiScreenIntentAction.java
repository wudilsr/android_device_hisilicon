package com.hisilicon.multiscreen.protocol.utils;

/**
 * Definition of broadcast id <br>
 * CN:广播id的定义。
 * @since MultiScreen V2.0.1.1
 */
public class MultiScreenIntentAction
{

    /**
     * Notify to close all activities.<br>
     * CN:广播通知关闭所有Activity<br>
     */
    public static final String ACTION_NOTIFY_FINISH_ALL_ACTIVITY =
        "hiandroid.intent.action.FINISH_ALL";

    /**
     * Notify other modules,new handhold device accesses.<br>
     * CN:通知其他组件，新的设备接入了。<br>
     */
    public static final String ACTION_NOTIFY_NEW_PHONE_ACCESS =
        "hiandroid.intent.action.NEW_PHONE_COME";

    /**
     * Notify STB that the current connecting phone has been left.<br>
     * CN:通知STB，当前的连接的客户端设备离开。<br>
     */
    public static final String ACTION_NOTIFY_OLD_PHONE_LEAVE =
        "hiandroid.intent.action.OLD_PHONE_LEAVE";

    /**
     * Notify multiscreen server has started <br>
     * CN:多屏服务开启完毕的通知id
     */
    public static final String MULITSCREEN_SERVER_START = "hiandroid.multiscreen.started";

    /**
     * Notify multiscreen server has stopped <br>
     * CN:多屏服务关闭完毕的通知id
     */
    public static final String MULITSCREEN_SERVER_STOP = "hiandroid.multiscreen.stopped";

    /**
     * Id for notify VIME at ready status <br>
     * CN: 虚拟输入法处于ready状态的通知id
     * */
    public static final String VIME_SWITCH_TO_READY = "hiandroid.vime.switch.ready";

    /**
     * Id for notify VIME at Init status <br>
     * CN: 虚拟输入法处于Init状态的通知id
     * */
    public static final String VIME_SWITCH_TO_INIT = "hiandroid.vime.switch.init";

    /**
     * Id for notify VIME at input status <br>
     * CN: 虚拟输入法处于input状态的通知id
     * */
    public static final String VIME_SWITCH_TO_INPUT = "hiandroid.vime.switch.input";

    /**
     * Id for notify VIME at DeInit status <br>
     * CN: 虚拟输入法处于DeInit状态的通知id
     * */
    public static final String VIME_SWITCH_TO_DEINIT = "hiandroid.vime.switch.deinit";

    /**
     * Id for notify VIME close tip keyboard <br>
     * CN: 虚拟输入法处于DeInit状态的通知id
     * */
    public static final String VIME_SERVER_CLOSE_KEYBOARD = "hiandroid.vime.close.keyboard";

    /**
     * Notify id for check VIME status <br>
     * CN: 查询虚拟输入法状态的通知id
     * */
    public static final String CHECK_VIME_STATUS = "hiandroid.check.vime.status";

    /**
     * Response id for check VIME status <br>
     * CN: 检查虚拟输入法状态的回应通知id
     * */
    public static final String RET_CHECK_VIME_STATUS = "hiandroid.return.vime.status";

    /**
     * Id for sending client's device Info <br>
     * CN: 发送客户端设备信息给虚拟输入法的id
     * */
    public static final String SEND_REMOTE_DEVICE_INFO = "hiandroid.send.client.deviceInfo";

    /**
     * Id for sending client's device Info <br>
     * CN: 发送客户端设备信息给虚拟输入法的id
     * */
    public static final String VIME_ABNORMAL_START = "hiandroid.vime.abnormal.start";

    /**
     * Id for notify VIme's switch status on hand device<br>
     * CN: 通知更改在手持设备侧虚拟输入法的开关状态
     * */
    public static final String SWITCH_VIME_SETTING = "hiandroid.vimestatus.switch";

    /**
     * Id for notify VIme enable fail<br>
     * CN: 虚拟输入法使能失败通知id
     * */
    public static final String FAIL_ENABLE = "hiandroid.vime.fail";

    // public static final String NETWORK_NOTWELL =
    // "android.intent.action.netWorkNotWell";

    /**
     * Id for notify network lost<br>
     * CN: 网络中断的通知id
     * */
    public static final String NETWORK_LOST = "hiandroid.notify.networklost";

    // public static final String GRABED_BY_OTHER =
    // "android.intent.action.grab";

    /**
     * Id for notify end input from hand device <br>
     * CN: 结束输入来自手持设备侧的通知id
     */
    public static final String END_INPUT_BY_PHONE = "hiandroid.vime.endinput.phone";

    /**
     * Id for notify end input from STB <br>
     * CN: 结束输入来自STB侧的通知id
     */
    public static final String END_INPUT_BY_STB = "hiandroid.vime.endinput.stb";

}
