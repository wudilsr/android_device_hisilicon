package com.hisilicon.multiscreen.http;

/**
 * It receives XML message and HTTP request 's remote IP.<br>
 * when HiHttpServer receives HTTPRequest,it will pass XML message to <br>
 * the dealer who implements HttpRecvMsgListener,and then get return message.<br>
 * CN:XML消息接收和处理，并获得HTTP请求的远端IP<br>
 * 当HiHttpServer接收到消息后，会回调onHttpMsgReceived函数，将XML消息传递给处理模块,<br>
 * 处理模块在处理完毕消息后，将回应消息以返还值的形式传递给HttpServer。<br>
 * @since HiMultiScreen_V2.0.1.1
 */
public interface HiHttpRecvMsgListener
{
    String onHttpMsgReceived(byte[] message, String remoteIP);

}
