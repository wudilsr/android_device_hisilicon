package com.hisilicon.multiscreen.http;

import org.cybergarage.multiscreenhttp.HTTP;
import org.cybergarage.multiscreenhttp.HTTPRequest;
import org.cybergarage.multiscreenhttp.HTTPResponse;
import org.cybergarage.multiscreenutil.Debug;



/**
 * HiHttpClient for sending message CN :用于各个模块发送消息。
 * @since HiMultiScreen_V2.0.1.1
 */
public class HiHttpClient
{
    private String mHostIp = null;

    private int mPort = 80;

    private int mTimeout = 2000;

    /**
     * Empty Constructor.<br>
     * CN:空构造。
     */
    public HiHttpClient()
    {

    }

    /**
     * Constructor.<br>
     * CN:构造方法。<br>
     * @param hostIp - host IP of the remote device. CN:远程设备的主机IP
     * @param port - port of the remote device. CN:远程主机端口。
     * @param timeOut - time out of the sending message. CN:发送消息超时时间设置。
     */
    public HiHttpClient(String hostIp, int port, int timeOut)
    {
        mHostIp = hostIp;
        mPort = port;
        mTimeout = timeOut;
    }

    /**
     * Set host IP.<br>
     * CN:设置远程IP地址。<br>
     * @param hostIp - host IP of remote device. CN:远程设备的IP地址。
     */
    public void setHostIp(String hostIp)
    {
        mHostIp = hostIp;
    }

    /**
     * Get remote device IP.<br>
     * CN:获得远程设备IP地址。<br>
     * @return host IP of the remote device.
     */
    public String getHostIp()
    {
        return mHostIp;
    }

    /**
     * Set remote device message port.<br>
     * CN:设置远端设备接收消息的端口。<br>
     * @param port - port of the remote device receiving message.<br>
     */
    public void setPort(int port)
    {
        mPort = port;
    }

    /**
     * Get remote device receiving message port.<br>
     * CN:获得远程设备的消息接收端口。
     * @return port of remote.
     */
    public int getPort()
    {
        return mPort;
    }

    /**
     * Set time out of receiving message .<br>
     * CN:设置接收消息的超时时间。<br>
     * @param timeOut - time out of receiving message.
     */
    public void setTimeOut(int timeOut)
    {
        mTimeout = timeOut;
    }

    /**
     * Get time out of receiving message .<br>
     * CN:获得接收消息的超时时间。<br>
     * @return time out of receiving message.
     */
    public int getTimeOut()
    {
        return mTimeout;
    }

    /**
     * Client sends message to HTTP server.<br>
     * CN:主动发送消息。
     * @param host - host IP. CN:主机IP地址。
     * @param port - host port. CN:主机端口。
     * @param timeOut - time out of sending message. CN:设置消息发送的超时时间。
     * @param msg - request message CN:请求消息。
     * @return if the status code is 404 or 500,it shows that the HTTP Server is
     *         not been started or has error!<br>
     *         CN:如果返回的状态码是404或者500说明Server端可能没有起来。
     */
    public HiHttpResponse sendRequest(String host, int port, int timeOut, byte[] msg)
    {
        HiHttpResponse retHiResponse = null;
        HTTPResponse retHttpResponse = null;

        if ((msg == null) || (msg.length == 0))
        {
            return getWrongEmptyResponse(HiHttpStatusCode.NOT_FOUND);
        }

        if (host == null)
        {
            return getWrongEmptyResponse(HiHttpStatusCode.INTERNAL_SERVER_ERROR);
        }

        HTTPRequest request = new HTTPRequest();
        request.setMethod(HTTP.POST);
        request.setURI("/");
        request.setVersion("1.0");
        request.setConnection("close");
        request.setContent(msg);
        retHttpResponse = request.post(host, port, timeOut);

        retHiResponse =
            new HiHttpResponse(retHttpResponse.getStatusCode(), retHttpResponse.getContent());
        retHiResponse.setResponseMessage(retHttpResponse.getContentString());
        //LogTool.v("sendRequest=" + request.toString());
        //LogTool.v("getResponse=" + retHttpResponse.toString());
        return retHiResponse;

    }

    /**
     * Client sends message to HTTP server.<br>
     * CN:主动发送消息
     * @param msg request message CN:请求消息
     * @return if the status code is 404 or 500,it shows that the HTTP Server is
     *         not been started or has error!<br>
     *         CN:如果返回的状态码是404或者500说明Server端可能没有起来。
     */
    public HiHttpResponse sendRequest(byte[] msg)
    {
        HiHttpResponse retHiResponse = null;
        HTTPResponse retHttpResponse = null;

        if ((msg == null) || (msg.length == 0))
        {
            return getWrongEmptyResponse(HiHttpStatusCode.NOT_FOUND);
        }

        if (mHostIp == null)
        {
            return getWrongEmptyResponse(HiHttpStatusCode.INTERNAL_SERVER_ERROR);
        }

        HTTPRequest request = new HTTPRequest();
        request.setMethod(HTTP.POST);
        request.setURI("/");
        request.setVersion("1.0");
        request.setConnection("close");
        request.setContent(msg);
        retHttpResponse = request.post(mHostIp, mPort, mTimeout);

        retHiResponse =
            new HiHttpResponse(retHttpResponse.getStatusCode(), retHttpResponse.getContent());
        retHiResponse.setResponseMessage(retHttpResponse.getContentString());
        //LogTool.v("sendRequest=" + request.toString());
        //LogTool.v("getResponse=" + retHttpResponse.toString());

        return retHiResponse;
    }

    /**
     * Client sends message to HTTP server.<br>
     * CN:主动发送消息。
     * @param msg - request message CN:请求消息
     * @return if the status code is 404 or 500,it shows that the HTTP Server is
     *         not been started or has error!<br>
     *         CN:如果返回的状态码是404或者500说明Server端可能没有起来。
     */
    public HiHttpResponse sendRequest(String msg)
    {
        HiHttpResponse retHiResponse = null;
        HTTPResponse retHttpResponse = null;

        if (msg == null)
        {
            return getWrongEmptyResponse(HiHttpStatusCode.NOT_FOUND);
        }

        if (mHostIp == null)
        {
            return getWrongEmptyResponse(HiHttpStatusCode.INTERNAL_SERVER_ERROR);
        }
        HTTPRequest request = new HTTPRequest();
        request.setMethod(HTTP.POST);
        request.setURI("/");
        request.setVersion("1.0");
        request.setConnection("close");
        request.setContent(msg);
        retHttpResponse = request.post(mHostIp, mPort, mTimeout);

        retHiResponse =
            new HiHttpResponse(retHttpResponse.getStatusCode(), retHttpResponse.getContent());
        retHiResponse.setResponseMessage(retHttpResponse.getContentString());
        // LogTool.v("sendRequest=" + request.toString());
        // LogTool.v("getResponse=" + retHttpResponse.toString());

        return retHiResponse;
    }

    private HiHttpResponse getWrongEmptyResponse(int statusCode)
    {
        HiHttpResponse retHiResponse = null;
        String msg = null;
        retHiResponse = new HiHttpResponse(statusCode, msg);

        return retHiResponse;
    }

    /**
     * Start debug module.<br>
     * CN:启动调试模块。
     */
    public void debugOn()
    {
        Debug.on();
    }

    /**
     * Stop debug module.<br>
     * CN:停止调试模块。
     */
    public void debugOff()
    {
        Debug.off();
    }
}
