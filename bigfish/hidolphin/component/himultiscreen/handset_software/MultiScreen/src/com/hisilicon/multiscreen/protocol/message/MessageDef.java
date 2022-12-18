package com.hisilicon.multiscreen.protocol.message;

import com.hisilicon.multiscreen.upnputils.UpnpMultiScreenDeviceInfo;

/**
 * Message define.<br>
 * CN:消息定义类，用于常量定义。<br>
 * MTSC means MultiScreen.<br>
 */
public class MessageDef
{
    /**
     * MultiScreen service keyboard type.<br>
     * 多屏服务模拟键盘类型。
     */
    public static final int KEYBOARD_SERVICE_ID = 0;

    /**
     * MultiScreen service touch type.<br>
     * 多屏服务模拟触屏类型。
     */
    public static final int TOUCH_SERVICE_ID = 1;

    /**
     * MultiScreen service mouse type.<br>
     * 多屏服务模拟鼠标类型。
     */
    public static final int MOUSE_SERVICE_ID = 2;

    /**
     * MultiScreen service g-sensor type.<br>
     * CN:多屏服务模拟体感类型。
     */
    public static final int GSENSOR_SERVICE_ID = 3;

    /**
     * Name of MultiScreen check network service.<br>
     * CN:多屏网络状态检查服务名称。
     */
    public static final String CHECK_NETWORK_SERVICE_NAME = "checknetwork";

    /**
     * Name of MultiScreen RemoteVinput service.<br>
     * CN:多屏远程控制服务名称。
     */
    public static final String VINPUT_SERVICE_NAME =
        UpnpMultiScreenDeviceInfo.VAR_VINPUT_SERVER_URI;

    /**
     * Name of MultiScreen keyboard service.<br>
     * CN:多屏键盘服务名称。
     */
    public static final String KEYBOARD_SERVICE_NAME =
        UpnpMultiScreenDeviceInfo.VAR_VINPUT_SERVER_URI;

    /**
     * Name of MultiScreen touch service.<br>
     * CN:多屏触摸服务名称。
     */
    public static final String TOUCH_SERVICE_NAME = UpnpMultiScreenDeviceInfo.VAR_VINPUT_SERVER_URI;

    /**
     * Name of MultiScreen mouse service.<br>
     * CN:多屏鼠标服务名称。
     */
    public static final String MOUSE_SERVICE_NAME = UpnpMultiScreenDeviceInfo.VAR_VINPUT_SERVER_URI;

    /**
     * Name of MultiScreen PushServer service.<br>
     * 多屏推送服务名称。
     */
    public static final String PUSHSERVER_SERVICE_NAME = "pushserver";

    /**
     * Name of MultiScreen g-sensor service.<br>
     * CN:多屏体感服务名称。
     */
    public static final String GSENSOR_SERVICE_NAME =
        UpnpMultiScreenDeviceInfo.VAR_GSENSOR_SERVER_URI; // "gsensor";

    /**
     * Name of access control on server.<br>
     */
    public static final String ACCESS_CONTROL_SERVER_NAME = "access_control_server";

    /**
     * Name of access control on client.<br>
     */
    public static final String ACCESS_CONTROL_CLIENT_NAME = "access_control_client";

    /**
     * Name of VIme control on server.<br>
     */
    public static final String VIME_SERVER_CONTROL_NAME =
        UpnpMultiScreenDeviceInfo.VAR_VIME_CONTROL_SERVER_URI; // "vime_server_control";

    /**
     * Name of VIme control on client.<br>
     */
    public static final String VIME_CLIENT_CONTROL_NAME = "vime_client_control";

    /**
     * Name of VIme transfer on server.<br>
     */
    public static final String VIME_SERVER_TRANSFER =
        UpnpMultiScreenDeviceInfo.VAR_VIME_DATA_SERVER_URI; // "vime_server_transfer";

    /**
     * Port of check network.<br>
     */
    public static final String CHECK_NETWORK_PORT = "8821";

    public static final String VINPUT_PORT = "8822";

    public static final String PUSHSERVER_PORT = "8867";

    public static final String GSENSOR_PORT = "11021";

    public static final String ACCESS_CONTROL_SERVER_PORT = "8025";

    public static final String ACCESS_CONTROL_CLIENT_PORT = "8026";

    public static final String VIME_SERVER_CONTROL_PORT = "2015";

    public static final String VIME_CLIENT_CONTROL_PORT = "2016";

    public static final String VIME_SERVER_TRANSFER_PORT = "2019";

    /**
     * The service name of this port is device name.<br>
     * CN:用值对应的服务名称为设备名称。
     */
    public static final String DEVICE_NAME_PORT = "-1";

    /**
     * Message type, unused.<br>
     * CN:消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_AcessDeviceStatus = 0x001;

    /**
     * Keyboard type.<br>
     * CN:键盘类型。
     */
    public static final short MTSC_MSGTYPE_KEYBOARD = 0x002;

    /**
     * Mouse type.<br>
     * CN:鼠标类型。
     */
    public static final short MTSC_MSGTYPE_MOUSE = 0x003;

    /**
     * Touch type.<br>
     * CN:触摸类型
     */
    public static final short MTSC_MSGTYPE_TOUCH = 0x004;

    /**
     * Message type, unused.<br>
     * CN:消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_FILE_PLAY_GET = 0x005;

    /**
     * Message type, unused.<br>
     * 消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_FILE_PLAY_RESPONSE = 0x006;

    /**
     * Message type, unused.<br>
     * 消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_FILE_PLAY_SET = 0x007;

    /**
     * Message type, unused.<br>
     * 消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_FILE_PLAY_SETRP = 0x008;

    /**
     * Message type, unused.<br>
     * 消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_SENSOR_NOTIFY = 0x009;

    /**
     * Message type, unused.<br>
     * 消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_IPTV_CHANEL_GETALL = 0x00A;

    /**
     * Message type, unused.<br>
     * 消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_IPTV_CHANEL_UPDATE = 0x00B;

    /**
     * Message type, unused.<br>
     * 消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_IPTV_PLAYLIST_GETALL = 0x00c;

    /**
     * Message type, unused.<br>
     * 消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_IPTV_CHANLE_SWITCH = 0x00d;

    /**
     * Message type, unused.<br>
     * 消息类型，未使用。
     */
    public static final short MTSC_MSGTYPE_IPTV_CLOSE = 0x00f;

    /**
     * Client module of MultiScreen.<br>
     * CN:多屏客户端模块。
     */
    public static final short MTSC_MODULE_RC_APP = 0x0001; // RC_APP模块

    /**
     * Control center of MultiScreen.<br>
     * CN:多屏模块控制中心。
     */
    public static final short MTSC_MODULE_RC_CENTER = 0x0002; // 多屏模块控制中心

    /**
     * Module name, unused.<br>
     * CN:模块名称，未使用。
     */
    public static final short MTSC_MODULE_UI_CENTER = 0x0003; // 华为JAVA消息中心

    /**
     * Module name, unused.<br>
     * 模块名称，未使用。
     */
    public static final short MTSC_MODULE_DRIVER_CENTER = 0x0004; // 华为MTSC驱动消息中心

    /**
     * Module name, unused.<br>
     * 模块名称，未使用。
     */
    public static final short MTSC_MODULE_TEST_CENTER = 0x0005; // 华为MTSC测试中心

    /**
     * Module name, unused.<br>
     * 模块名称，未使用。
     */
    public static final short MTSC_MODULE_FEMTO = 0x0010; // 华为Femto模块

    /**
     * Module name, unused.<br>
     * 模块名称，未使用。
     */
    public static final short MTSC_MODULE_WIID = 0x0011; // 华为WIID模块

    /**
     * Module name, unused.<br>
     * 模块名称，未使用。
     */
    public static final short MTSC_MODULE_VIDEOPHONE = 0x0012; // 华为VideoPhone模块

    /**
     * Operate type, unused.<br>
     * CN:操作类型，未使用。
     */
    public static final short MSG_TYPE_SENSOR = 0x01;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short MSG_TYPE_CELLID = 0x02;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short MSG_CUITYPE_VIDEO = 0x03;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short MSG_CUITYPE_WEB = 0x04;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short MSG_CUITYPE_APP = 0x05;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short SENSOR_CHANGE_DATA = 0x001;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short SENSOR_ACRRACY_DATA = 0x002;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short FILE_PLAY_GET_ALL = 0x300;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short FILE_PLAY_RESPONSE_ALL = 0x301;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short FILE_PALY_SET_VOLUM = 0x307;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short FILE_PLAY_SET_TIME = 0x308;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short FILE_PLAY_SET_MUTE = 0x309;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short FILE_PLAY_STATUS_PALYING = 0x320;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short FILE_PLAY_STATUS_PAUSE = 0x321;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short FILE_PLAY_STATUS_STOP = 0x322;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short FILE_PLAY_STATUS_NOMEDIA = 0x322;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short ACESSDEVICE_LEAVE_NETWORK = 0x0400;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short ACESSDEVICE_JOIN_NETWORK = 0x0401;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short ACESSDEVICE_LIVE_PACKAGE = 0x0402;

    /**
     * Operate type, unused.<br>
     * 操作类型，未使用。
     */
    public static final short MTSC_DEVICE_SEARCH = 0x2012;

    // CN:消息码。

    /**
     * Message code of Touch, unused.<br>
     * CN:触摸Touch消息码，未使用。
     */
    public static final int UPDATE_SENSOR_ICON = 0x2001;

    /**
     * Message code of Touch, unused.<br>
     * CN:触摸Touch消息码，未使用。
     */
    public static final int SHOW_CONNECT_STATUS = 0x2002;

    /**
     * Message code of Remote Control, unused.<br>
     * CN:遥控器Remote消息码，未使用。
     */
    public static final int MSG_UPDATE_INITIAL_MSG = 0x3001;

    /**
     * Message code of Remote Control, unused.<br>
     * CN:遥控器Remote消息码，未使用。
     */
    public static final int MSG_UPDATE_SETRP_MSG = 0x3002;

    /**
     * Delay of handling message.<br>
     */
    public static final long DELAY_MILLIS = 50;

    /**
     * Message code of Remote Control, unused.<br>
     * CN:遥控器Remote消息码，未使用。
     */
    public static final int MTSC_VOICE_CHANGE = 0x3003;

    /**
     * Message code of handle device list update.<br>
     */
    public static final int MSG_DEVICE_IP_LIST_UPDATE = 1;

    public static final int MSG_CANNOT_VISIT_DEVICE = MSG_DEVICE_IP_LIST_UPDATE + 1;

    public static final int MSG_IP_ADDRESS_INVALID = MSG_DEVICE_IP_LIST_UPDATE + 2;

    public static final int MSG_AUTO_CONNECT_DEVICE = MSG_DEVICE_IP_LIST_UPDATE + 3;

    public static final int DEVICE_INFO = MSG_DEVICE_IP_LIST_UPDATE + 4;

    public static final int EXIT_APP = MSG_DEVICE_IP_LIST_UPDATE + 5;

    public static final int MSG_GOTO_REMOTE_TOUCH = MSG_DEVICE_IP_LIST_UPDATE + 6;

    public static final int MSG_GOTO_AIRMOUSE = MSG_DEVICE_IP_LIST_UPDATE + 7;

    public static final int MSG_GOTO_REMOTE_KEY = MSG_DEVICE_IP_LIST_UPDATE + 8;

    public static final int MSG_GOTO_MIRROR_SENSOR = MSG_DEVICE_IP_LIST_UPDATE + 9;

    /**
     * CN:2s内连按两次返回键退出应用。
     */
    public static final int BACK_PRESSED_MILLIS = 2000;

    /**
     * Intent name of remote status.<br>
     */
    public static final String INTENT_REMOTE_STATUS = "REMOTE_STATUS";

    public static final int REMOTE_TOUCH = 1;

    public static final int REMOTE_AIRMOUSE = REMOTE_TOUCH + 1;

    public static final int REMOTE_KEY = REMOTE_TOUCH + 2;

    public static final int REMOTE_GAME = REMOTE_TOUCH + 3;

    /**
     * Intent name of mirror activity.<br>
     */
    public static final String INTENT_MIRROR_STATUS = "MIRROR_STATUS";

    /**
     * Intent value of mirror default.<br>
     */
    public static final int MIRROR_STATUS_DEFAULT = 1;

    /**
     * Intent value of mirror with sensor.<br>
     */
    public static final int MIRROR_STATUS_SENSOR = MIRROR_STATUS_DEFAULT + 1;
}
