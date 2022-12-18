package com.hisilicon.multiscreen.upnputils;

import org.cybergarage.upnp.device.ST;

public class UpnpMultiScreenDeviceInfo
{
    /**
     * MultiScreen device type.<br>
     * "urn:schemas-upnp-org:device:HiMultiScreenServerDevice:1"
     */
    public static final String MULTISCREEN_DEVICE_TYPE = ST.MULTISCREEN_DEVICE;

    /**
     * MultiScreen Access type.<br>
     */
    public static final String MULTISCREEN_SERVICE_ACCESS_TYPE =
        "urn:schemas-upnp-org:service:AccessControlServer:1";

    /**
     * MultiScreen vinput service type.<br>
     */
    public static final String MULTISCREEN_SERVICE_VINPUT_TYPE =
        "urn:schemas-upnp-org:service:VinputControlServer:1";

    /**
     * MultiScreen sensor service type.<br>
     */
    public static final String MULTISCREEN_SERVICE_GSENSOR_TYPE =
        "urn:schemas-upnp-org:service:GsensorControlServer:1";

    /**
     * MultiScreen mirror service type.<br>
     */
    public static final String MULTISCREEN_SERVICE_MIRROR_TYPE =
        "urn:schemas-upnp-org:service:MirrorControlServer:1";

    /**
     * MultiScreen VIME service type.<br>
     */
    public static final String MULTISCREEN_SERVICE_VIME_TYPE =
        "urn:schemas-upnp-org:service:VIMEControlServer:1";

    /**
     * MultiScreen VIME service type.<br>
     */
    public static final String MULTISCREEN_SERVICE_REMOTE_APP_TYPE =
        "urn:schemas-upnp-org:service:RemoteAppControlServer:1";

    /**
     * Action name of access hello.<br>
     */
    public static final String ACTION_ACCESS_HELLO = "Hello";

    /**
     * Action name of access byebye.<br>
     */
    public static final String ACTION_ACCESS_BYEBYE = "Byebye";

    /**
     * Action name of access ping..<br>
     */
    public static final String ACTION_ACCESS_PING = "Ping";

    /**
     * Action name of start gsensor.<br>
     */
    public static final String ACTION_GSENSOR_START = "StartGsensor";

    /**
     * Action name of stop gsensor.<br>
     */
    public static final String ACTION_GSENSOR_STOP = "StopGsensor";

    /**
     * Action name of set mirror parameter.<br>
     */
    public static final String ACTION_MIRROR_SET_PARAMETER = "SetMirrorParameter";

    /**
     * Action name of set start mirror.<br>
     */
    public static final String ACTION_MIRROR_START = "StartMirror";

    /**
     * Action name of set stop mirror.<br>
     */
    public static final String ACTION_MIRROR_STOP = "StopMirror";

    /**
     * Action name of start remote app.<br>
     */
    public static final String ACTION_REMOTE_APP_START = "StartRemoteApp";

    /**
     * Action name of stop remote app.<br>
     */
    public static final String ACTION_REMOTE_APP_STOP = "StopRemoteApp";

    /**
     * Action name of start VIME control server.<br>
     */
    public static final String ACTION_VIME_START = "StartVIMEControlServer";

    /**
     * Action name of stop VIME control server.<br>
     */
    public static final String ACTION_VIME_STOP = "StopVIMEControlServer";

    /**
     * Action name of set VIME parameter.<br>
     */
    public static final String ACTION_VIME_SET_PARAMETER = "SetVIMEParameter";

    /**
     * Action name of start vinput.<br>
     */
    public static final String ACTION_VINPUT_START = "StartVinput";

    /**
     * Action name of stop vinput.<br>
     */
    public static final String ACTION_VINPUT_STOP = "StopVinput";

    /**
     * State variable of client id.<br>
     */
    public static final String VAR_CLIENT_ID = "HI_UPNP_VAR_CLIENTID";

    /**
     * State variable of protocol info.<br>
     */
    public static final String VAR_VAR_PROTOCOL_INFO = "HI_UPNP_VAR_ProtocolInfo";

    /**
     * State variable of access remote list.<br>
     */
    public static final String VAR_ACCESS_REMOTE_LIST = "HI_UPNP_VAR_AccessRemoteList";

    /**
     * State variable of vinput server uri.<br>
     */
    public static final String VAR_VINPUT_SERVER_URI = "HI_UPNP_VAR_VinpuServerURI";

    /**
     * State variable of gsensor server uri.<br>
     */
    public static final String VAR_GSENSOR_SERVER_URI = "HI_UPNP_VAR_GsensorServerURI";

    /**
     * State variable of vime control server uri.<br>
     */
    public static final String VAR_VIME_CONTROL_SERVER_URI = "HI_UPNP_VAR_VIMEControlServerURI";

    /**
     * State variable of vime data server uri.<br>
     */
    public static final String VAR_VIME_DATA_SERVER_URI = "HI_UPNP_VAR_VIMEDataServerURI";

    /**
     * State variable of vime parameter.<br>
     */
    public static final String VAR_VIME_PARAMETER = "HI_UPNP_VAR_VIMEParameter";

    /**
     * State variable of mirror parameter.<br>
     */
    public static final String VAR_MIRROR_PARAMETER = "HI_UPNP_VAR_MirrorParameter";

    /**
     * Argument of remote id in action.<br>
     */
    public static final String ARG_REMOTE_ID = "RemoteID";

    /**
     * Argument in hello action of access.<br>
     */
    public static final String ARG_REMOTE_IP = "RemoteIP";

    /**
     * Argument in hello action of access.<br>
     */
    public static final String ARG_CLIENT_VERSION = "Version";

    /**
     * Argument in hello action of DeviceInfo.<br>
     */
    public static final String ARG_HANDSET_DEVICEINFO = "DeviceInfo";

    /**
     * Argument in hello action of android sdk version.<br>
     */
    public static final String ARG_HANDSET_SDK_VERSION = "SDKVersion";

    /**
     * Out argument in hello action of DeviceInfo.<br>
     */
    public static final String ARG_SUPPORT_VIDEO = "SupportVideo";

    /**
     * Out argument in hello action of current remote id.<br>
     */
    public static final String ARG_CURRENT_REMOTE_ID = "CurrentRemoteID";

    /**
     * Argument in ping action of access.<br>
     */
    public static final String ARG_PING_TIME = "PingTime";

    /**
     * Argument in set parameter action of VIME.<br>
     */
    public static final String ARG_VIME_PARAMETER = "VIMEParameter";

    /**
     * Argument of set parameter action of Mirror.<br>
     */
    public static final String ARG_MIRROR_PARAMETER = "MirrorParameter";
}
