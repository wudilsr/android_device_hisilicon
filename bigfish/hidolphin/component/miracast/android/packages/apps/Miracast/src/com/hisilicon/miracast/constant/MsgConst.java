package com.hisilicon.miracast.constant;

public class MsgConst
{
    /* for WfdService */
    public static final int MSG_SERVICE_WIFI_P2P_STATE_CHANGED = 1001;
    public static final int MSG_SERVICE_WIFI_P2P_CONNECTION_CHANGED = 1002;
    public static final int MSG_SERVICE_WIFI_P2P_THIS_DEVICE_CHANGED = 1003;
    public static final int MSG_SERVICE_DISCONNECT_AP = 1004;
    public static final int MSG_SERVICE_WIFI_P2P_CONNECTING = 1005;

    /* for WelcomeActivity */
    public static final int MSG_WELCOME_GO = 1001;

    /* for SettingActivity */
    public static final int MSG_SETTING_START = 2001;
    public static final int MSG_SETTING_STOP = 2002;
    public static final int MSG_SETTING_UPDATE_UI = 2011;
    public static final int MSG_SETTING_DISPLAYSTART = 2031;

    /* for DisplayActivity */
    public static final int MSG_DISPLAY_START = 4001;
    public static final int MSG_DISPLAY_STOP = 4002;
    public static final int MSG_DISPLAY_HOME_STOP = 4003;

    public static final int MSG_DISPLAY_NETWORK_GREEN = 4004;
    public static final int MSG_DISPLAY_NETWORK_YELLOW = 4005;
    public static final int MSG_DISPLAY_NETWORK_RED = 4006;

    /* for SinkNative */
    public static final int MSG_NATIVE_WHAT_NETWORK_INTERRUPT = 3001;
    public static final int MSG_NATIVE_WHAT_UPDATE_LOST_PACKET = 3002;
    public static final int MSG_NATIVE_WHAT_SINK_KEEPALIVE_FAILED = 3003;
    public static final int MSG_NATIVE_WHAT_START_WFD_FINISHED = 3011;
    public static final int MSG_NATIVE_WHAT_STOP_WFD_FINISHED = 3012;
    public static final int MSG_NATIVE_ARG_NONE = 0;
    public static final int MSG_NATIVE_ARG_CONNECTION_FAILED = 3101;
    public static final int MSG_NATIVE_WHAT_PLATFORM_NO_SUPPORTED = 3201;
    public static final int MSG_NATIVE_WHAT_TVP_INIT_ERROR = 3301;
    public static final int MSG_NATIVE_WHAT_HDCP_INIT_ERROR = 3302;

    /*for wfd state*/
    public static final int MSG_WFD_CONNECTING = 5001;
    public static final int MSG_WFD_CONNECTED = 5002;
    public static final int MSG_WFD_PLAYING = 5003;
    public static final int MSG_WFD_DISCONNECTED = 5004;

}
