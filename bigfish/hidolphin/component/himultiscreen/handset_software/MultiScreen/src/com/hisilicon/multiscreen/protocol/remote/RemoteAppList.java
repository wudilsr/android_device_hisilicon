package com.hisilicon.multiscreen.protocol.remote;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerConfigurationException;

import org.xml.sax.SAXException;

import com.hisilicon.multiscreen.http.HiHttpClient;
import com.hisilicon.multiscreen.http.HiHttpResponse;
import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.message.Action;
import com.hisilicon.multiscreen.protocol.message.AppInfo;
import com.hisilicon.multiscreen.protocol.message.Argument;
import com.hisilicon.multiscreen.protocol.message.ArgumentValue;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.SaxXmlUtil;

/**
 * Remote application class.<br>
 * CN:远程应用类。
 */
public class RemoteAppList
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
     * Application List.<br>
     * CN:APP应用列表.
     */
    public ArrayList<AppInfo> mAppList = new ArrayList<AppInfo>();

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
    public RemoteAppList(HiDeviceInfo deviceInfo)
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
     * Clear application list.<br>
     * CN:清除列表。
     */
    public void destroy()
    {
        mAppList.clear();
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
     * Launch application on STB.<br>
     * CN:启动STB上的应用。
     * @param packagName - package name of application CN:应用程序APP的名称.
     */
    public void launchApp(String packagName)
    {
        Action updateAction = getLaunchAppAction(new Action(), packagName);
        sendRequestAction(updateAction);
    }

    /**
     * Update application list by new request.<br>
     * CN:用新的请求更新应用列表。
     */
    public void updateAppList()
    {
        Action updateAction = getUpdateAppListAction(new Action());
        Action responseAction = null;
        AppInfo appInfo = null;
        mAppList.clear();

        responseAction = sendRequestAction(updateAction);

        if (responseAction == null)
        {
            LogTool.e("response action is null.");
            return;
        }
        else if (responseAction.getId() == Action.ACTION_ID_REMOTE_APP_RET_UPDATE_LIST)
        {
            for (Argument arg : responseAction.getArgumentList())
            {
                appInfo = new AppInfo();
                appInfo.setAppName((String) arg.getArgumentValue(0).getVaule());
                appInfo.setPackageName((String) arg.getArgumentValue(1).getVaule());
                appInfo.setPackageIndex((Integer) arg.getArgumentValue(2).getVaule());
                byte[] icon = (byte[]) arg.getArgumentValue(3).getVaule();
                appInfo.setPackageIcon(icon);
                mAppList.add(appInfo);
            }
        }
    }

    /**
     * Get update application list action.<br>
     * CN:获取更新应用列表消息。
     * @param action - object of Action
     * @return action of updating application list
     */
    private Action getUpdateAppListAction(Action action)
    {
        Argument argument = new Argument();
        ArgumentValue argumentValue = null;
        argumentValue = new ArgumentValue("reserve", 0);
        argument.addArgumentValue(argumentValue);

        action.setId(Action.ACTION_ID_REMOTE_APP_UPDATE_LIST);
        action.setName("getAppList");
        action.setResponseFlag("yes");
        action.setResponseId(Action.ACTION_ID_REMOTE_APP_RET_UPDATE_LIST);
        action.addArgument(argument);

        return action;
    }

    private Action getLaunchAppAction(Action action, String packageName)
    {
        Argument argument = new Argument();
        ArgumentValue argumentValue = null;
        argumentValue = new ArgumentValue("PackageName", packageName);
        argument.addArgumentValue(argumentValue);

        action.setId(Action.ACTION_ID_REMOTE_APP_LAUNCH);
        action.setName("launchAPP");
        action.setResponseFlag("yes");
        action.setResponseId(Action.ACTION_ID_REMOTE_APP_RET_LAUNCH);
        action.addArgument(argument);

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
