package com.hisilicon.multiscreen.protocol.remote;

import java.net.DatagramSocket;
import java.net.SocketException;

import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.message.KeyInfo;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.message.MouseRequest;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.UDPClient;

/**
 * Remote Mouse control class.<br>
 * CN:远端鼠标控制接口类.
 */
public class RemoteMouse
{
    /**
     * Mouse event type - wheel down.<br>
     * CN:鼠标事件类型 - 滚轮向下。
     */
    public static final int MOUSE_WHEEL_DOWN = 0;

    /**
     * Mouse event type - wheel up.<br>
     * CN:鼠标事件类型 - 滚轮向上。
     */
    public static final int MOUSE_WHEEL_UP = 2;

    // clickType
    /**
     * Mouse event type - move.<br>
     * CN:鼠标事件类型 - 移动。
     */
    public static final short MOUSE_ACTION_MOVE = 0x100;

    /**
     * Mouse event type - right click.<br>
     * CN:鼠标事件类型 - 右键单击。
     */
    public static final short MOUSE_RIGHT_SINGLE_CLICK = 0x201;

    /**
     * Mouse event type - right double click.<br>
     * CN:鼠标事件类型 - 右键双击。
     */
    public static final short MOUSE_RIGHT_DOUBLE_CLICK = 0x202;

    /**
     * Mouse event type - right down.<br>
     * CN:鼠标事件类型 - 右键按下。
     */
    public static final short MOUSE_RIGHT_DOWN = 0x203;

    /**
     * Mouse event type - right up.<br>
     * CN:鼠标事件类型 - 右键释放。
     */
    public static final short MOUSE_RIGHT_UP = 0x204;

    /**
     * Mouse event type - move with right down.<br>
     * CN:鼠标事件类型 - 右键按下移动。
     */
    public static final short MOUSE_RGIHT_DOWN_MOVE = 0x205;

    /**
     * Mouse event type - left click.<br>
     * CN:鼠标事件类型 - 左键单击。
     */
    public static final short MOUSE_LEFT_SINGLE_CLICK = 0x301;

    /**
     * Mouse event type - left double click.<br>
     * CN:鼠标事件类型 - 左键双击。
     */
    public static final short MOUSE_LEFT_DOUBLE_CLICK = 0x302;

    /**
     * Mouse event type - left down.<br>
     * CN:鼠标事件类型 - 左键按下。
     */
    public static final short MOUSE_LEFT_DOWN = 0x303;

    /**
     * Mouse event type - left up.<br>
     * CN:鼠标事件类型 - 左键释放。
     */
    public static final short MOUSE_LEFT_UP = 0x304;

    /**
     * Mouse event type - move with left down.<br>
     * CN:鼠标事件类型 - 左键按下移动。
     */
    public static final short MOUSE_LEFT_DOWN_MOVE = 0x305;

    /**
     * Mouse event type - wheel.<br>
     * CN:鼠标事件类型 - 滚轮。
     */
    public static final short MOUSE_WHEEL = 0x306;

    /**
     * Value of mouse wheel down.<br>
     */
    private static final float MOUSE_WHEEL_DOWN_VALUE = -10L;

    /**
     * Value of mouse wheel up.<br>
     */
    private static final float MOUSE_WHEEL_UP_VALUE = 10L;

    private HiDeviceInfo mDevice;

    private MouseRequest mRequest = null;

    private DatagramSocket mSocket = null;

    /**
     * Constructor, Create a remote Mouse handler based on DeviceInfo.<br>
     * CN:构造函数，通过DeviceInfo对象新建远程Mouse控制类.
     * @param deviceInfo - device information.<br>
     *        CN:输入的DeviceInfo对象.
     */
    public RemoteMouse(HiDeviceInfo deviceInfo)
    {
        if (deviceInfo == null)
        {
            LogTool.e("device info is null in remote mouse.");
        }
        else
        {
            resetDevice(deviceInfo);
        }
    }

    protected void destroy()
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

        if (mRequest == null)
        {
            mRequest = new MouseRequest(MOUSE_ACTION_MOVE, 0, 0);
        }

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
     * Send mouse move event, make the cursor move with the mouse event.<br>
     * CN:发送鼠标移动事件,实现光标的移动.
     * @param event_type - RemoteMouse.MOUSE_ACTION_MOVE/MOUSE_RGIHT_DOWN_MOVE/
     *        MOUSE_LEFT_DOWN_MOVE.<br>
     *        CN:事件类型.
     * @param sendX - offset of x-axis.<br>
     *        CN:x轴偏移.
     * @param sendY - offset of y-axis.<br>
     *        CN:y轴偏移.
     */
    public void sendMouseMoveEvent(int event_type, float sendX, float sendY)
    {
        if (mDevice == null)
        {
            LogTool.e("mDevice is null");
            return;
        }

        mRequest.setData((short) event_type, sendX, sendY);
        UDPClient.send(mSocket, mDevice.getDeviceIP(),
            mDevice.getService(MessageDef.MOUSE_SERVICE_NAME).getServicePort(), mRequest);
    }

    /**
     * Send mouse click event, actualize the mouse click.<br>
     * CN:发送鼠标点击事件,实现鼠标的点击.
     * @param event_type - RemoteMouse.MOUSE_RIGHT_SINGLE_CLICK/
     *        MOUSE_LEFT_SINGLE_CLICK.<br>
     *        CN:事件类型.
     */
    public void sendMouseClickEvent(int event_type)
    {
        if (mDevice == null)
        {
            LogTool.e("mDevice is null");
            return;
        }

        if (event_type != MOUSE_RIGHT_SINGLE_CLICK)
        {
            // 左键单击
            mRequest.setData((short) event_type, 0, 0);
            UDPClient.send(mSocket, mDevice.getDeviceIP(),
                mDevice.getService(MessageDef.MOUSE_SERVICE_NAME).getServicePort(), mRequest);
        }
        else
        {
            // 右键单击
            MultiScreenControlService.getInstance().getRemoteControlCenter().getRemoteKeyboard()
                .sendDownAndUpKeyCode(KeyInfo.KEYCODE_BACK);
        }
    }

    /**
     * Send wheel event.<br>
     * CN:发送鼠标滚轮事件到单板,响应鼠标事件
     * @param WheelEvent -
     *        RemoteMouse.MOUSE_WHEEL_DOWN/RemoteMouse.MOUSE_WHEEL_UP
     */
    public void sendMouseWheelEvent(int WheelEvent)
    {
        if (mDevice == null)
        {
            LogTool.e("mDevice is null");
            return;
        }

        mRequest.setData(MOUSE_WHEEL, 0, 0);
        // CN:滚轮事件，服务端读取dx值作为滚轮偏移量。
        if (WheelEvent == MOUSE_WHEEL_DOWN)
        {
            mRequest.setDx(MOUSE_WHEEL_DOWN_VALUE);
        }
        else if (WheelEvent == MOUSE_WHEEL_UP)
        {
            mRequest.setDx(MOUSE_WHEEL_UP_VALUE);
        }

        UDPClient.send(mSocket, mDevice.getDeviceIP(),
            mDevice.getService(MessageDef.MOUSE_SERVICE_NAME).getServicePort(), mRequest);
    }

}
