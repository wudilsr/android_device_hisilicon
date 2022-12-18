package com.hisilicon.multiscreen.server;

/**
 * MultiScreen device's definitions class related to upnp.<br>
 * CN:与upnp相关的多屏设备定义类。
 */
public class UpnpMultiScreenDeviceInfo
{
    /**
     * Separator between variables.<br>
     * CN:变量分隔符。
     */
    public static final String VAR_SEPARATOR = ",";

    /**
     * MultiScreen device type .<br>
     * CN:多屏设备类型。
     */
    public static final String MULTISCREEN_DEVICE_TYPE = "HiMultiScreenServerDevice:1";

    /**
     * MultiScreen Access service type. <br>
     * CN:多屏接入服务类型。
     */
    public static final String MULTISCREEN_SERVICE_ACCESS_TYPE = "AccessControlServer:1";

    /**
     * MultiScreen vinput service type. <br>
     * CN:多屏vinput服务类型。
     */
    public static final String MULTISCREEN_SERVICE_VINPUT_TYPE = "VinputControlServer:1";

    /**
     * MultiScreen sensor service type <br>
     * CN:多屏sensor服务类型。
     */
    public static final String MULTISCREEN_SERVICE_GSENSOR_TYPE = "GsensorControlServer:1";

    /**
     * MultiScreen mirror service type <br>
     * CN:多屏mirror服务类型。
     */
    public static final String MULTISCREEN_SERVICE_MIRROR_TYPE = "MirrorControlServer:1";

    /**
     * MultiScreen Remote app service type <br>
     * CN:多屏remote app服务类型。
     */
    public static final String MULTISCREEN_SERVICE_REMOTE_APP_TYPE = "RemoteAppControlServer:1";

    /**
     * MultiScreen VIME service type <br>
     * CN:多屏VIME服务类型。<br>
     */
    public static final String MULTISCREEN_SERVICE_VIME_TYPE = "VIMEControlServer:1";

    /**
     * State variable name of vinput server's uri.<br>
     * CN:Vinput 服务的状态变量uri。
     */
    public static final String VAR_VINPUT_SERVER_URI = "HI_UPNP_VAR_VinpuServerURI";

    /**
     * State variable name of gsensor server's uri.<br>
     * CN:sensor 服务uri的状态变量名。
     */
    public static final String VAR_GSENSOR_SERVER_URI = "HI_UPNP_VAR_GsensorServerURI";

    /**
     * State variable name of VIME control server's uri.<br>
     * CN:VIME控制服务uri的状态变量名。
     */
    public static final String VAR_VIME_CONTROL_SERVER_URI = "HI_UPNP_VAR_VIMEControlServerURI";

    /**
     * State variable name of VIME data server's uri.<br>
     * CN:VIME数据服务uri的状态变量名。
     */
    public static final String VAR_VIME_DATA_SERVER_URI = "HI_UPNP_VAR_VIMEDataServerURI";

    /**
     * Default supply service list.<br>
     * CN:默认提供的服务列表。
     * @return The device supply multiscreen services.<br>
     *         CN:设备提供的多屏服务。
     */
    public static final String defaultServiceList()
    {
        StringBuilder servicesStrBuilder = new StringBuilder();
        servicesStrBuilder.append(MULTISCREEN_SERVICE_ACCESS_TYPE);
        servicesStrBuilder.append(VAR_SEPARATOR);
        servicesStrBuilder.append(MULTISCREEN_SERVICE_MIRROR_TYPE);
        servicesStrBuilder.append(VAR_SEPARATOR);
        servicesStrBuilder.append(MULTISCREEN_SERVICE_VINPUT_TYPE);
        servicesStrBuilder.append(VAR_SEPARATOR);
        servicesStrBuilder.append(MULTISCREEN_SERVICE_VIME_TYPE);
        servicesStrBuilder.append(VAR_SEPARATOR);
        servicesStrBuilder.append(MULTISCREEN_SERVICE_GSENSOR_TYPE);
        servicesStrBuilder.append(VAR_SEPARATOR);
        servicesStrBuilder.append(MULTISCREEN_SERVICE_REMOTE_APP_TYPE);
        return servicesStrBuilder.toString();
    }

}
