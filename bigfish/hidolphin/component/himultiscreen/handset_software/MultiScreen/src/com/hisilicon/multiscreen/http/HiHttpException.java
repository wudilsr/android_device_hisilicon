package com.hisilicon.multiscreen.http;

/**
 * it define the HTTP Server's special exception.<br>
 * for example, if user define HTTP Server port less than zero ,it will throws
 * the HttpException.<br>
 * CN:定义HTTP Server本身会有的一些Exception 例如，如果用户定义的HTTP Server的端口小于0的话，就会抛出该异常。
 * @since HiMultiScreen_V2.0.1.1
 *
 */
public class HiHttpException extends RuntimeException
{
    private static final long serialVersionUID = 123456L;

    public HiHttpException(String msg)
    {
        super(msg);
    }
}
