package com.hisilicon.multiscreen.http;

import org.cybergarage.multiscreenhttp.HTTPRequest;
import org.cybergarage.multiscreenhttp.HTTPRequestListener;
import org.cybergarage.multiscreenhttp.HTTPResponse;
import org.cybergarage.multiscreenhttp.HTTPServerList;
import org.cybergarage.multiscreenhttp.HTTPStatus;
import org.cybergarage.multiscreenutil.Debug;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * HiHTTPServer class is used to transfer message between STB and Phone. when
 * use the class ,the caller should implement HTTPRequestListener class and
 * define the HTTP server port.<br>
 * CN:MultiScreenHTTPServer类，用于消息传输。
 * 使用该类时，调用者实现注册监听类HTTPRequestListener，并自定义HTTP端口。
 * @since HiMultiScreen_V2.0.1.1
 */
public class HiHttpServer implements HTTPRequestListener
{

    /**
     * The minimal socket which the user can use.<br>
     * CN:用户可以使用的最小socket端口。
     */
    public static final int MIN_USER_PORT = 1024;

    /**
     * The maximal socket port which the user can use.<br>
     * CN:用户可以使用的最大socket端口。
     */
    public static final int MAX_USER_PORT = 49151;

    /**
     * HTTP server default port.<br>
     * CN:HTTP服务器缺省端口。
     */
    public static final int HTTP_SERVER_DEFAULT_PORT = 80;

    /**
     * HTTP server default time out.<br>
     * CN:HTTP服务器的缺省超时时间。
     */
    public static final int HTTP_SERVER_DEFAULT_TIME_OUT = 1000;

    /**
     * It defines the HTTP server's port.<br>
     * CN:定义HTTP 服务器的端口。
     */
    private int mServerPort = HTTP_SERVER_DEFAULT_PORT;

    private int mSocketTimeOut = HTTP_SERVER_DEFAULT_TIME_OUT;

    /**
     * It defines the listener who deals the HTTPRequest message.<br>
     * CN:当HTTP Server接收到消息后，会回调该监听对象，获取消息，并发出回应消息。
     */
    private HiHttpRecvMsgListener mHiHttpRecvMsgListener = null;

    private HTTPServerList mHttpServerList = null;

    /**
     * It is a constructor method.<br>
     * CN:构造方法。
     * @param port user defines a HTTP server's port.<br>
     *        CN:用户自定义HTTP Server的端口。
     * @param listener user should implements a HttpRecvMsgListener object.<br>
     *        CN:用户需要实现HttpRecvMsgListener对象。
     */
    public HiHttpServer(int port, HiHttpRecvMsgListener listener) throws HiHttpException
    {
        setServerPort(port);
        setHttpRecvMsgListener(listener);
    }

    /**
     * It is a empty constructor method.<br>
     * CN:空构造方法。
     */
    public HiHttpServer()
    {

    }

    /**
     * Set HiHttpServer's port.<br>
     * CN:设置HiHttpServer端口。
     * @param port User defines the HTTP Server's port.<br>
     *        the range of the port is 1024 to 49151.<br>
     *        CN:用户自定义HTTP Server端口。
     */
    public void setServerPort(int port) throws HiHttpException
    {
        if ((port < MIN_USER_PORT) || (port > MAX_USER_PORT))
        {
            throw new HiHttpException("wrong port range!");
        }

        mServerPort = port;
    }

    /**
     * To get server port.
     * @return it will return the HTTP Server's port.<br>
     *         CN:返回用户定义的HTTP Server的端口。
     */
    public int getServerPort()
    {
        return mServerPort;
    }

    /**
     * Set listener.<br>
     * CN:设置消息监听对象。<br>
     * @param listener user implements a HTTPRequestListener object and pass to
     *        HTTP Server.<br>
     *        CN: 用户实现HttpRecvMsgListener对象，并传递给HTTP Server。
     */
    public void setHttpRecvMsgListener(HiHttpRecvMsgListener listener)
    {
        mHiHttpRecvMsgListener = listener;
    }

    /**
     * Get HttpRecvMsgListener object.<br>
     * CN:获得用户定义的HttpRecvMsgListener对象。
     * @return it will return HttpRecvMsgListener object.<br>
     *         CN:返回用户定义的HttpRecvMsgListener对象。
     */
    public HiHttpRecvMsgListener getHttpRecvMsgListener()
    {
        return mHiHttpRecvMsgListener;
    }

    /**
     * Use the specified port and the HTTPRequestListener listener,to start HTTP
     * Server.<br>
     * CN:使用用户设置的端口和HTTPRequestListener监听器，开启HTTP Server。
     */
    public void startServer()
    {
        if (mHttpServerList == null)
        {
            mHttpServerList = new HTTPServerList();
        }

        if (mHttpServerList.open(mServerPort, mSocketTimeOut) == true)
        {
            mHttpServerList.addRequestListener(this);
            mHttpServerList.start();
        }
        else
        {
            // It is BindException, don't start server again.
            LogTool.e("Fail to open HttpServerList, it is BindException.");
        }
    }

    /**
     * Use it to stop HTTP server.<br>
     * CN:停止HTTP Server。
     */
    public void stopServer()
    {
        if (mHttpServerList != null)
        {
            mHttpServerList.close();
            mHttpServerList.stop();
            // FIXME CN:不要置空，HTTP还没完全停止时，可能收到消息被使用该listener。
            // mHiHttpRecvMsgListener = null;
            mHttpServerList.clear();
            mHttpServerList = null;
        }
    }

    /**
     * It implements HTTPRequestListener interface.<br>
     * CN:实现了HTTPRequestListener接口。<br>
     * @param httpReq - the remote request message.<br>
     *        CN:远程HTTP 请求消息。
     */
    public void httpRequestReceived(HTTPRequest httpReq)
    {
        String sendMsg = null;

        if (mHiHttpRecvMsgListener == null)
        {
            throw new HiHttpException("HttpRecvMsgListener is null!");
        }

        // comment for get remote IP will block several seconds on android 2.3
        // remote IP is no use on client APP.
        // String socketAddr =
        // httpReq.getSocket().getSocket().getRemoteSocketAddress().toString();
        // String remoteIP = HostNetInterface.uri2Ip(socketAddr);

        String remoteIP = null;
        sendMsg = mHiHttpRecvMsgListener.onHttpMsgReceived(httpReq.getContent(), remoteIP);

        if (sendMsg == null)
        {
            throw new HiHttpException("http Response is null!");
        }

        HTTPResponse httpRes = new HTTPResponse();
        httpRes.setStatusCode(HTTPStatus.OK);
        httpRes.setVersion("1.0");
        httpRes.setConnection("close");
        httpRes.setContent(sendMsg);

        httpReq.post(httpRes);
    }

    /**
     * Set the socket maximal time out,in milliseconds.<br>
     * CN:设置socket最大超时时间,以毫秒为单位。
     * @param timeOut - time in milliseconds.<br>
     *        CN:超时时间，以毫秒为单位。
     */
    public void setSocketTimeOut(int timeOut)
    {
        mSocketTimeOut = timeOut;

    }

    /**
     * Get the socket maximal time out.<br>
     * CN:获得最大超时时间。
     * @return Returns the time, in milliseconds.<br>
     *         CN:返回超时时间，以毫秒为单位。
     */
    public int getSocketTimeOut()
    {
        return mSocketTimeOut;
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
