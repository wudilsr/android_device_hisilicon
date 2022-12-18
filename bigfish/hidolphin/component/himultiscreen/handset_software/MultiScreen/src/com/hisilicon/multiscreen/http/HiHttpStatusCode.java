package com.hisilicon.multiscreen.http;

/**
 * Define the HTTP Server message's status code.<br>
 * CN:定义HTTP Server消息的状态码信息。<br>
 */
public class HiHttpStatusCode
{

    /**
     * The request has been successfully . a desired response header or data
     * body<br>
     * will be returned with this response.<br>
     * CN:请求已成功，请求所希望的响应头或数据体将随此响应返回。<br>
     */
    public static final int OK = 200;

    /**
     * Request fails, the client connection may be error.<br>
     * CN:请求失败，客户端连接出错。<br>
     */
    public static final int NOT_FOUND = 404;

    /**
     * Server may be error.<br>
     * CN:服务器出错。<br>
     */
    public static final int INTERNAL_SERVER_ERROR = 500;

    /**
     * Parse the Status code.<br>
     * CN:给出状态码的解释。
     * @param code - Status code.<br>
     *        CN:状态码。
     * @return explanation for code.
     */
    public static final String code2String(int code)
    {
        switch (code)
        {

            case OK:
                return "OK";

            case NOT_FOUND:
                return "Not Found";

            case INTERNAL_SERVER_ERROR:
                return "Internal Server Error";
            default:
                return "Unknown Code (" + code + ")";
        }
    }
}
