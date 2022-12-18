package com.hisilicon.multiscreen.http;

/**
 * HiHttp response class.<br>
 * CN:HiHttp 请求消息的回应类。
 * @since HiMultiScreen_V2.0.1.1
 */
public class HiHttpResponse
{
    private int mStatusCode = 0;

    private String mResponseMessage = null;

    private byte[] mMessage = new byte[0];

    /**
     * Empty constructor.<br>
     * CN:空构造函数
     */
    public HiHttpResponse()
    {

    }

    /**
     * Constructor.<br>
     * CN:构造函数
     * @param statusCode response status code.<br>
     *        CN:回应状态码.
     * @param body response entity message.<br>
     *        CN:回应的实体消息。
     */
    public HiHttpResponse(int statusCode, String body)
    {
        setStatusCode(statusCode);
        setResponseMessage(body);
    }

    /**
     * Constructor.<br>
     * CN:构造函数
     * @param statusCode response status code.<br>
     *        CN:回应状态码.
     * @param body response entity message.<br>
     *        CN:回应的实体消息。
     */
    public HiHttpResponse(int statusCode, byte[] body)
    {
        setStatusCode(statusCode);
        setMessage(body);
    }

    /**
     * Set response status code.<br>
     * CN:设置回应状态码。
     * @param statusCode - HTTP status code.
     */
    public void setStatusCode(int statusCode)
    {
        mStatusCode = statusCode;
    }

    /**
     * Get response status code.<br>
     * CN:获得回应状态码
     * @return HTTP status code.<br>
     *         返回HTTP服务器状态码。
     */
    public int getStatusCode()
    {
        return mStatusCode;
    }

    /**
     * Set HTTP response body.<br>
     * CN:设置回应消息的消息实体。<br>
     * @param responseMessage response body.<br>
     *        回应消息的消息体。
     */
    public void setResponseMessage(String responseMessage)
    {
        mResponseMessage = responseMessage;
    }

    /**
     * Get response body.<br>
     * CN:获得回应消息的消息实体。<br>
     * @return string of response message.
     */
    public String getResponseMessage()
    {
        return mResponseMessage;
    }

    /**
     * Set HTTP response body.<br>
     * CN:设置回应消息的消息实体。<br>
     * @param responseMessage response body.<br>
     *        回应消息的消息体。
     */
    public void setMessage(byte[] responseMessage)
    {
        mMessage = responseMessage;
    }

    /**
     * Get response body.<br>
     * CN:获得回应消息的消息实体。<br>
     * @return byte array of response.
     */
    public byte[] getMessage()
    {
        return mMessage;
    }

}
