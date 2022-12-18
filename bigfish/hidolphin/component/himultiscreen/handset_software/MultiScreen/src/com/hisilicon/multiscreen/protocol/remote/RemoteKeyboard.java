package com.hisilicon.multiscreen.protocol.remote;

import java.net.DatagramSocket;
import java.net.SocketException;

import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.ServiceInfo;
import com.hisilicon.multiscreen.protocol.message.KeyInfo;
import com.hisilicon.multiscreen.protocol.message.KeyboardRequest;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.UDPClient;

/**
 * Remote keyboard event response class, offer the interface for sending
 * keyboard event.<br>
 * CN:远端键盘按键事件响应类,提供交互接口。
 * @see RemoteControlCenter
 */
public class RemoteKeyboard
{
    private HiDeviceInfo mDevice = null;

    private KeyboardRequest mRequest = null;

    private DatagramSocket mSocket = null;

    /**
     * Constructor. create a remote Keyboard handler based on DeviceInfo.<br>
     * CN:构造函数，通过DeviceInfo对象新建远程Keyboard控制类。
     * @param deviceInfo - device information.<br>
     *        CN:输入的DeviceInfo对象。
     */
    public RemoteKeyboard(HiDeviceInfo deviceInfo)
    {
        if (deviceInfo == null)
        {
            LogTool.e("device info is null in remote keyboard.");
        }
        else
        {
            resetDevice(deviceInfo);
        }
    }

    /**
     * Destroy remote keyboard.
     */
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
            mRequest = new KeyboardRequest(KeyInfo.KEYCODE_0, KeyInfo.KEY_EVENT_UP);
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
     * Send keyboard's down or up event.<br>
     * CN:发送键盘按键down/up事件。
     * @param keycode - key code.<br>
     *        CN:按键键值。
     * @param event_type - KeyInfo.KEY_EVENT_UP / KeyInfo.KEY_EVENT_DOWN.<br>
     *        CN:事件类型。
     */
    public void sendDownOrUpKeyCode(int keycode, short event_type)
    {
        // 服务端jni打开设备，替换framework
        if ((event_type == KeyInfo.KEY_EVENT_DOWN) || (event_type == KeyInfo.KEY_EVENT_UP))
        {
            sendToVirtualDriver(keycode, event_type);
        }
    }

    /**
     * Send keyboard's click event.<br>
     * CN:发送键盘单次点击事件,down&up事件。
     * @param keycode - key code.<br>
     *        CN:按键键值。
     * @see KeyInfo
     */
    public void sendDownAndUpKeyCode(int keycode)
    {
        int key_value = -1;
        boolean shift_press = false;
        // Send shift key cause to key code.
        // CN:某些键值需要添加Shift。
        switch (keycode)
        {
            case KeyInfo.KEYCODE_A:
                key_value = KeyInfo.KEYCODE_a;
                shift_press = true;
                break;

            // ---------- ! start --------
            case KeyInfo.KEYCODE_B:
                key_value = KeyInfo.KEYCODE_b;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_C:
                key_value = KeyInfo.KEYCODE_c;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_D:
                key_value = KeyInfo.KEYCODE_d;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_E:
                key_value = KeyInfo.KEYCODE_e;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_F:
                key_value = KeyInfo.KEYCODE_f;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_G:
                key_value = KeyInfo.KEYCODE_g;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_H:
                key_value = KeyInfo.KEYCODE_h;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_I:
                key_value = KeyInfo.KEYCODE_i;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_J:
                key_value = KeyInfo.KEYCODE_j;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_K:
                key_value = KeyInfo.KEYCODE_k;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_L:
                key_value = KeyInfo.KEYCODE_l;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_M:
                key_value = KeyInfo.KEYCODE_m;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_N:
                key_value = KeyInfo.KEYCODE_n;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_O:
                key_value = KeyInfo.KEYCODE_o;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_P:
                key_value = KeyInfo.KEYCODE_p;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_Q:
                key_value = KeyInfo.KEYCODE_q;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_R:
                key_value = KeyInfo.KEYCODE_r;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_S:
                key_value = KeyInfo.KEYCODE_s;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_T:
                key_value = KeyInfo.KEYCODE_t;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_U:
                key_value = KeyInfo.KEYCODE_u;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_V:
                key_value = KeyInfo.KEYCODE_v;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_W:
                key_value = KeyInfo.KEYCODE_w;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_X:
                key_value = KeyInfo.KEYCODE_x;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_Y:
                key_value = KeyInfo.KEYCODE_y;
                shift_press = true;
                break;

            case KeyInfo.KEYCODE_Z:
                key_value = KeyInfo.KEYCODE_z;
                shift_press = true;
                break;

            // ---------- ~ start --------
            case KeyInfo.KEYCODE_REVERSE:
                key_value = KeyInfo.KEYCODE_GRAVE;
                shift_press = true;
                break;

            // ---------- ! start --------
            case KeyInfo.KEYCODE_SIGH:
                key_value = KeyInfo.KEYCODE_1;
                shift_press = true;
                break;

            // ---------- @ start --------
            case KeyInfo.KEYCODE_AT:
                key_value = KeyInfo.KEYCODE_2;
                shift_press = true;
                break;

            // ---------- # start --------
            case KeyInfo.KEYCODE_WELL:
                key_value = KeyInfo.KEYCODE_3;
                shift_press = true;
                break;

            // ---------- $ start --------
            case KeyInfo.KEYCODE_DOLLAR:
                key_value = KeyInfo.KEYCODE_4;
                shift_press = true;
                break;

            // ---------- % start --------
            case KeyInfo.KEYCODE_PERCENT:
                key_value = KeyInfo.KEYCODE_5;
                shift_press = true;
                break;

            // ---------- ^ start --------
            case KeyInfo.KEYCODE_AND:
                key_value = KeyInfo.KEYCODE_6;
                shift_press = true;
                break;

            // ---------- & start --------
            case KeyInfo.KEYCODE_ANDD:
                key_value = KeyInfo.KEYCODE_7;
                shift_press = true;
                break;

            // ---------- * start --------
            case KeyInfo.KEYCODE_STAR:
                key_value = KeyInfo.KEYCODE_8;
                shift_press = true;
                break;

            // ---------- ( start --------
            case KeyInfo.KEYCODE_LEFTBRACKET:
                key_value = KeyInfo.KEYCODE_9;
                shift_press = true;
                break;

            // ---------- ) start --------
            case KeyInfo.KEYCODE_RIGHTBRACKET:
                key_value = KeyInfo.KEYCODE_0;
                shift_press = true;
                break;

            // ---------- _ start --------
            case KeyInfo.KEYCODE_UNDERLINE:
                key_value = KeyInfo.KEYCODE_MINUS;
                shift_press = true;
                break;

            // ---------- + start --------
            case KeyInfo.KEYCODE_ADD:
                key_value = KeyInfo.KEYCODE_EQUALS;
                shift_press = true;
                break;

            // ---------- ? start --------
            case KeyInfo.KEYCODE_ASK:
                key_value = KeyInfo.KEYCODE_SLASH;
                shift_press = true;
                break;

            // ---------- { start --------
            case KeyInfo.KEYCODE_LEFT_BIG_BRACKET:
                key_value = KeyInfo.KEYCODE_LEFT_BRACKET;
                shift_press = true;
                break;

            // ---------- : start --------
            case KeyInfo.KEYCODE_COLON:
                key_value = KeyInfo.KEYCODE_SEMICOLON;
                shift_press = true;
                break;

            // ---------- " start --------
            case KeyInfo.KEYCODE_DOUBLE_QUOTATION:
                key_value = KeyInfo.KEYCODE_APOSTROPHE;
                shift_press = true;
                break;

            // ---------- | start --------
            case KeyInfo.KEYCODE_OR:
                key_value = KeyInfo.KEYCODE_BACKSLASH;
                shift_press = true;
                break;

            // ---------- } start --------
            case KeyInfo.KEYCODE_RIGHT_BIG_BRACKET:
                key_value = KeyInfo.KEYCODE_RIGHT_BRACKET;
                shift_press = true;
                break;

            // ---------- < start --------
            case KeyInfo.KEYCODE_LESS_THAN:
                key_value = KeyInfo.KEYCODE_COMMA;
                shift_press = true;
                break;

            // ---------- > start --------
            case KeyInfo.KEYCODE_BIG_THAN:
                key_value = KeyInfo.KEYCODE_DOT;
                shift_press = true;
                break;

            default:
                key_value = keycode;
                break;
        }

        if (true == shift_press)
        {
            sendToVirtualDriver(KeyInfo.KEYCODE_SHIFT_LEFT, KeyInfo.KEY_EVENT_DOWN);
            sendToVirtualDriver(key_value, KeyInfo.KEY_EVENT_DOWN);
            sendToVirtualDriver(key_value, KeyInfo.KEY_EVENT_UP);
            sendToVirtualDriver(KeyInfo.KEYCODE_SHIFT_LEFT, KeyInfo.KEY_EVENT_UP);
        }
        else
        {
            sendToVirtualDriver(key_value, KeyInfo.KEY_EVENT_DOWN);
            sendToVirtualDriver(key_value, KeyInfo.KEY_EVENT_UP);
        }
    }

    /**
     * Send keyboard's down & up event.<br>
     * CN:发送键盘按键down&up事件。
     * @param keycode - key code.<br>
     *        CN:键值。
     * @param updownState - key's status.<br>
     *        CN:按键状态。
     * */
    private void sendToVirtualDriver(int keycode, short updownState)
    {
        if (mDevice == null)
        {
            LogTool.e("mDevice is null");
            return;
        }

        String ip = mDevice.getDeviceIP();
        ServiceInfo service = mDevice.getService(MessageDef.KEYBOARD_SERVICE_NAME);

        if (ip == null || service == null)
        {
            return;
        }
        else
        {
            int port = service.getServicePort();
            mRequest.setData(keycode, updownState);
            UDPClient.send(mSocket, ip, port, mRequest);
        }
    }
}
