package com.hisilicon.multiscreen.protocol.remote;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.UnknownHostException;

import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.message.AppListResponseMessage;
import com.hisilicon.multiscreen.protocol.message.DefaultResponseMessage;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.message.PushMessage;
import com.hisilicon.multiscreen.protocol.message.PushMessageHead;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Remote push control.<br>
 * CN:远端push控制接口类。
 */
public class RemotePushing
{

    /**
     * TCP connect timeout.<br>
     * CN:TCP连接超时。
     */
    private static final int SOCKET_CONNECT_TIME_OUT = 500;

    /**
     * Device information.<br>
     * CN:设备信息。
     */
    private HiDeviceInfo mDevice = null;

    /**
     * Constructor, Create a remote Pushing handler based on DeviceInfo.<br>
     * CN:构造函数，通过DeviceInfo对象新建远程Push控制类。
     * @param deviceInfo - device information.<br>
     *        CN:输入的DeviceInfo对象。
     */
    public RemotePushing(HiDeviceInfo deviceInfo)
    {
        if (deviceInfo == null)
        {
            LogTool.e("device info is null in remote pushing.");
        }
        else
        {
            resetDevice(deviceInfo);
        }
    }


    /**
     * Reset HiDevice info.
     * CN:重置多屏设备信息。
     * @param deviceInfo HiDevice
     */
    protected void resetDevice(HiDeviceInfo deviceInfo)
    {
        mDevice = deviceInfo;
    }

    /**
     * Push message to server and receive response from the server.<br>
     * CN:推送消息到服务器,并接收服务发回来的响应。
     * @param msg - Message to be pushed.<br>
     *        CN:推送的消息。
     * @return - Message of return.<br>
     *         CN:返回的消息。
     * @throws UnknownHostException - CN:指示主机IP地址无法确定而抛出的异常。
     * @throws IOException - CN:I/O异常。
     */
    public PushMessage pushing(PushMessage msg) throws UnknownHostException, IOException
    {
        String servIp = mDevice.getDeviceIP();

        Socket socket = new Socket();
        SocketAddress remoteAddr =
            new InetSocketAddress(servIp, mDevice
                .getService(MessageDef.PUSHSERVER_SERVICE_NAME).getServicePort());
        try
        {
            socket.connect(remoteAddr, SOCKET_CONNECT_TIME_OUT);
        }
        catch (IllegalArgumentException e)
        {
            socket.close();
            LogTool.e("Illegal Argument Exception.");
            return null;
        }
        catch (IOException e)
        {
            socket.close();
            LogTool.e("IO Exception");
            return null;
        }

        DataOutputStream out = new DataOutputStream(socket.getOutputStream());
        DataInputStream in = new DataInputStream(socket.getInputStream());

        msg.sendOutputMsg(out);

        // Receive response
        PushMessage response = null;
        PushMessageHead head = new PushMessageHead();
        head.readInputMsg(in);
        int type = head.getType();
        switch (type)
        {
            case PushMessageHead.GET_APPS_RESPONSE:
            {
                response = new AppListResponseMessage();
                response.setHead(head);
                response.readBody(in);
                break;
            }

            // Add different type of response message
            default:
            {
                response = new DefaultResponseMessage();
                response.readBody(in);
                break;
            }
        }

        out.close();
        in.close();
        socket.close();

        return response;
    }

}
