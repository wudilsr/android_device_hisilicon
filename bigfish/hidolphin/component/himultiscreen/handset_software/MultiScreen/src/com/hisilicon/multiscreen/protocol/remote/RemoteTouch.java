package com.hisilicon.multiscreen.protocol.remote;

import java.net.DatagramSocket;
import java.net.SocketException;

import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.ServiceInfo;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.message.TouchRequest;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.UDPClient;

/**
 * Remote Touch event response class, offer the interface for sending keyboard
 * Touch.<br>
 * CN:远端触摸屏事件响应控制类.
 */
public class RemoteTouch
{

    private HiDeviceInfo mDevice = null;

    private DatagramSocket mSocket = null;

    /**
     * Constructor. create a remote Touch handler based on DeviceInfo.<br>
     * CN:构造函数，通过DeviceInfo对象新建远程Touch控制类.
     * @param deviceInfo - device information.<br>
     *        CN:输入的DeviceInfo对象.
     */
    public RemoteTouch(HiDeviceInfo deviceInfo)
    {
        if (deviceInfo == null)
        {
            LogTool.e("device info is null in remote touch.");
        }
        else
        {
            resetDevice(deviceInfo);
        }
    }

    /**
     * Destroy remote touch.<br>
     * CN:销毁远程触控。
     */
    public void destroy()
    {
        if (mSocket != null)
        {
            mSocket.close();
            mSocket = null;
        }
    }

    /**
     * Reset HiDevice info. CN:重置多屏设备信息。
     * @param deviceInfo HiDevice
     */
    protected void resetDevice(HiDeviceInfo deviceInfo)
    {
        mDevice = deviceInfo;

        if (mSocket == null)
        {
            try
            {
                mSocket = new DatagramSocket();
            }
            catch (SocketException e)
            {
                LogTool.e(e.getMessage());
            }
        }
        else if (mSocket.isClosed())
        {
            try
            {
                mSocket = new DatagramSocket();
            }
            catch (SocketException e)
            {
                LogTool.e(e.getMessage());
            }
        }
    }

    /**
     * Send MultiTouch event.<br>
     * CN:发送多点触摸数据.
     * @param mtInfo - MultiTouchInfo.<br>
     *        CN:多点触摸请求对象.
     */
    public void sendMultiTouchEvent(TouchRequest mtInfo)
    {
        String ip = mDevice.getDeviceIP();
        ServiceInfo service = mDevice.getService(MessageDef.TOUCH_SERVICE_NAME);
        if (ip == null || service == null)
        {
            return;
        }
        else
        {
            int port = service.getServicePort();
            UDPClient.send(mSocket, ip, port, mtInfo);
        }
    }
}
