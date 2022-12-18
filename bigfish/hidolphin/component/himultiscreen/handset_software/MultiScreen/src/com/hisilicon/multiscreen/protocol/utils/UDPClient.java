package com.hisilicon.multiscreen.protocol.utils;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

import com.hisilicon.multiscreen.protocol.message.Request;

/**
 * Class for sending request object out using UDP in byte array form.<br>
 * CN:请求对象转换为字节数组，并发送UDP包.
 */
public class UDPClient
{
    /**
     * Send vinput message out.<br>
     * CN:发送 vinput的UDP请求消息.
     * @param s - DatagramSocket.<br>
     *        CN:DatagramSocket对象.
     * @param remoteHostIp - IP address of remote host.<br>
     *        CN:远程主机IP地址.
     * @param ServicePort - Port of remote host.<br>
     *        CN:远程服务端口号.
     * @param req - Request.<br>
     *        CN:请求对象.
     */
    public static void send(DatagramSocket s, String remoteHostIp, int ServicePort, Request req)
    {
        if (s != null)
        {
            int server_port = ServicePort;
            InetAddress local = null;
            try
            {
                local = InetAddress.getByName(remoteHostIp);
                DatagramPacket p =
                    new DatagramPacket(req.getBytes(), req.getHead().getMsgLen(), local,
                        server_port);
                s.send(p);
            }
            catch (UnknownHostException e)
            {
                LogTool.e(e.getMessage());
            }
            catch (IOException e)
            {
                LogTool.e(e.getMessage());
            }
        }
        else
        {
            LogTool.e("Socket is null!");
        }
    }

    /**
     * send gsensor udp request
     */
    /*
     * Commented by d47906, 2012-7-28, moved to RemoteSensor class public static
     * void send(DatagramSocket s, String remoteHostIp, int port, int eventType,
     * float pointX, float pointY, float pointZ) { int server_port =
     * port;//11021;// 绑定的端口号 InetAddress local = null; try { // 换成服务器端IP local
     * = InetAddress.getByName(remoteHostIp); } catch (UnknownHostException e) {
     * e.printStackTrace(); } byte[] msg = new
     * DataToByte().getMsgByteArray(eventType, pointX, pointY, pointZ);
     * DatagramPacket p = new DatagramPacket(msg, msg.length, local,
     * server_port); try { s.send(p); } catch (IOException e) {
     * e.printStackTrace(); } }
     */

    /*
     * public byte[] floatToByte(float v) { ByteBuffer bb =
     * ByteBuffer.allocate(4); byte[] ret = new byte[4]; FloatBuffer fb =
     * bb.asFloatBuffer(); fb.put(v); bb.get(ret); return ret; }
     */

}
