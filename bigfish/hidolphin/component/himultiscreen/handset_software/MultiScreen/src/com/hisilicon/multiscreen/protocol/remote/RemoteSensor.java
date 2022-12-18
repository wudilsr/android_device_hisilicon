package com.hisilicon.multiscreen.protocol.remote;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.FloatBuffer;

import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Remote sensor control class.<br>
 * CN:远端sensor控制接口类。
 */
public class RemoteSensor
{
    /**
     * Sensor type - acceleration.<br>
     * CN:体感类型-加速度
     */
    public static final int SENSOR_TYPE_ACCELEROMETER = 1;

    /**
     * Sensor type - geomagnetic field.<br>
     * CN:体感类型-地磁场
     */
    public static final int SENSOR_TYPE_MAGNETIC_FIELD = 2;

    /**
     * Sensor type - orientation.<br>
     * CN:体感类型-方向
     */
    public static final int SENSOR_TYPE_ORIENTATION = 3;

    /**
     * Sensor type - gyroscope.<br>
     */
    public static final int SENSOR_TYPE_GYROSCOPE = 4;

    /**
     * Sensor type - temperature.<br>
     * CN:体感类型-温度
     */
    public static final int SENSOR_TYPE_TEMPERATURE = 7;

    /**
     * Length of sensor message.<br>
     * CN:体感消息长度。
     */
    private static final short SENSOR_MESSAGE_LENGTH = 18;

    /**
     * Buffer size of data for remote sensor.<br>
     * CN:体感数据使用的缓冲区大小。
     */
    private static final int BUFFER_SIZE = SENSOR_MESSAGE_LENGTH;

    private HiDeviceInfo mDevice = null;

    private DatagramSocket mSocket = null;

    private DatagramPacket dataPacket = null;

    private InetAddress mAddress = null;

    private int mPort = 11021;

    private ByteBuffer mByteBuffer = null;

    private byte[] mSendMsg = null;

    private static final int FLOAT_LENGTH = 4;

    /**
     * ByteBuffer for transform float to bytes.<br>
     */
    private ByteBuffer mTransByteBuffer = ByteBuffer.allocate(FLOAT_LENGTH);

    private byte[] mFloatBytes = new byte[FLOAT_LENGTH];

    /**
     * Constructor, Create a remote Sensor handler based on DeviceInfo.<br>
     * CN:构造函数，通过DeviceInfo对象新建远程Sensor控制类.
     * @param deviceInfo - device information.<br>
     *        CN:输入的DeviceInfo对象.
     */
    public RemoteSensor(HiDeviceInfo deviceInfo)
    {
        mByteBuffer = ByteBuffer.allocate(BUFFER_SIZE);
        mSendMsg = new byte[SENSOR_MESSAGE_LENGTH];

        if (deviceInfo == null)
        {
            LogTool.e("device info is null in remote sensor.");
        }
        else
        {
            resetDevice(deviceInfo);
        }
    }

    /**
     * Close socket, disable sensor event.<br>
     * CN:关闭socket，禁止发送传感器数据.
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
        if (mDevice.getService(MessageDef.GSENSOR_SERVICE_NAME) == null)
        {
            LogTool.e("gsensor service port is not obtained");
        }
        else
        {
            // Get service port, 11021 as default
            mPort = mDevice.getService(MessageDef.GSENSOR_SERVICE_NAME).getServicePort();
        }

        try
        {
            // 换成服务器端IP
            mAddress = InetAddress.getByName(mDevice.getDeviceIP());
        }
        catch (UnknownHostException e)
        {
            LogTool.e(e.getMessage());
        }

        if (dataPacket == null)
        {
            byte[] msgByte = new byte[SENSOR_MESSAGE_LENGTH];
            dataPacket = new DatagramPacket(msgByte, 0, SENSOR_MESSAGE_LENGTH, mAddress, mPort);
        }
        else
        {
            dataPacket.setAddress(mAddress);
            dataPacket.setPort(mPort);
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
     * Send sensor event to server.<br>
     * CN:发送sensor事件信息,在服务端响应.
     * @param sensorType -
     *        RemoteSensor.SENSORS_ACCECTRTION/ORIENTAION/MAGNETIC_FIELD
     *        /TEMPRATURE.<br>
     *        CN:体感类型.
     * @param sendX - offset of x-axis.<br>
     *        CN:X轴位移.
     * @param sendY - offset of y-axis.<br>
     *        CN:Y轴位移.
     * @param sendZ - offset of z-axis.<br>
     *        CN:Z轴位移.
     */
    public void sendSensorEvent(int sensorType, float sendX, float sendY, float sendZ)
    {
        if (mDevice == null || mAddress == null)
        {
            // LogTool.d("mDevice is null.");
        }
        else
        {
            // 转换成字节，逆序
            // mSendMsg = getDataInByteOrder(sensorType, sendX, sendY, sendZ);
            mSendMsg = getBytes(sensorType, sendX, sendY, sendZ);
            dataPacket.setData(mSendMsg, 0, mSendMsg.length);

            try
            {
                if (mSocket != null)
                {
                    mSocket.send(dataPacket);
                }
                else
                {
                    LogTool.d("mSocket is null.");
                    mSocket = new DatagramSocket();
                }
            }
            catch (IOException e)
            {
                LogTool.e(e.getMessage());
            }
        }
    }

    /**
     * Convert sensor event to byte array.<br>
     * CN:将体感事件转换为字节数组.
     * @param eventType - sensor event type.<br>
     *        CN:体感事件类型.
     * @param pointX - offset of x-axis.<br>
     *        CN:X轴位移.
     * @param pointY - offset of y-axis.<br>
     *        CN:Y轴位移.
     * @param pointZ - offset of z-axis.<br>
     *        CN:Z轴位移.
     * @return - byte array of sensor event message.<br>
     *         CN:返回体感消息的字节数组.
     */
    private byte[] getBytes(int eventType, float pointX, float pointY, float pointZ)
    {
        if (mByteBuffer != null && mSendMsg != null)
        {
            mByteBuffer.putShort((short) 0);
            mByteBuffer.putShort(Short.reverseBytes((short) eventType));
            mByteBuffer.putShort((short) 0);
            mByteBuffer.put(floatToByteL(pointX));
            mByteBuffer.put(floatToByteL(pointY));
            mByteBuffer.put(floatToByteL(pointZ));

            // LogTool.d("UDP msgLen=" + mMsg.length + ",buf.capacity()=" +
            // mBuf.capacity());
            mByteBuffer.rewind();
            // mByteBuffer.get(mSendMsg, 0, mSendMsg.length);
            mByteBuffer.get(mSendMsg);
            mByteBuffer.clear();
        }
        return mSendMsg;
    }

    /**
     * @deprecated Get data in byte oder.<br>
     *             CN:获取正确字节序的数据。
     * @param eventType - type of sensor.
     * @param pointX - x value.
     * @param pointY - y value.
     * @param pointZ - z value.
     * @return - byte array.
     */
    private byte[] getDataInByteOrder(int eventType, float pointX, float pointY, float pointZ)
    {
        int index = 0;
        byte[] msgByte = new byte[SENSOR_MESSAGE_LENGTH];
        byte[] temp = new byte[4];

        for (int i = 0; i < 2; i++)
        {
            msgByte[index] = (byte) 0x00;
            index++;
        }

        temp = intToByteL(eventType);
        for (int i = 0; i < 2; i++)
        {
            msgByte[index] = temp[i];
            index++;
        }
        for (int i = 0; i < 2; i++)
        {
            msgByte[index] = (byte) 0x00;
            index++;
        }

        temp = floatToByteL(pointX);
        for (int i = 0; i < 4; i++)
        {
            msgByte[index] = temp[i];
            index++;
        }
        temp = floatToByteL(pointY);
        for (int i = 0; i < 4; i++)
        {
            msgByte[index] = temp[i];
            index++;
        }
        temp = floatToByteL(pointZ);
        for (int i = 0; i < 4; i++)
        {
            msgByte[index] = temp[i];
            index++;
        }
        return msgByte;

    }

    // // CN:int 转化为字节数组。
    // private int intToByte(byte[] bytebuffer, int intValue) {
    //
    // bytebuffer[0] = (byte) ((intValue & 0xFF000000) >> 24);
    // bytebuffer[1] = (byte) ((intValue & 0x00FF0000) >> 16);
    // bytebuffer[2] = (byte) ((intValue & 0x0000FF00) >> 8);
    // bytebuffer[3] = (byte) ((intValue & 0x000000FF));
    // return 4;
    // }
    //
    // // CN:int 转化为字节数组。
    // private byte[] intToByte(int intValue) {
    // byte[] result = new byte[4];
    // result[0] = (byte) ((intValue & 0xFF000000) >> 24);
    // result[1] = (byte) ((intValue & 0x00FF0000) >> 16);
    // result[2] = (byte) ((intValue & 0x0000FF00) >> 8);
    // result[3] = (byte) ((intValue & 0x000000FF));
    // return result;
    // }

    /**
     * CN:int转化为字节数组, 逆序。
     * @param intValue
     * @return
     */
    private byte[] intToByteL(int intValue)
    {
        byte[] result = new byte[4];
        result[0] = (byte) ((intValue & 0x000000FF));
        result[1] = (byte) ((intValue & 0x0000FF00) >> 8);
        result[2] = (byte) ((intValue & 0x00FF0000) >> 16);
        result[3] = (byte) ((intValue & 0xFF000000) >> 24);
        return result;
    }

    // /**
    // * CN:float转byte[]。
    // * @param bytebuffer
    // * @param floatValue
    // * @return
    // */
    // private int floatToByte(byte[] bytebuffer, float floatValue)
    // {
    // ByteBuffer bb = ByteBuffer.allocate(4);
    // FloatBuffer fb = bb.asFloatBuffer();
    // fb.put(floatValue);
    // bb.get(bytebuffer);
    // return 4;
    // }

    /**
     * CN:float转byte[], 逆序。
     * @param inputVal
     * @return
     */
    private byte[] floatToByteL(float inputVal)
    {
        FloatBuffer floatBuffer = mTransByteBuffer.asFloatBuffer();
        floatBuffer.put(inputVal);

        mTransByteBuffer.rewind();
        mTransByteBuffer.get(mFloatBytes);
        mFloatBytes[0] ^= mFloatBytes[3];
        mFloatBytes[3] ^= mFloatBytes[0];
        mFloatBytes[0] ^= mFloatBytes[3];
        mFloatBytes[1] ^= mFloatBytes[2];
        mFloatBytes[2] ^= mFloatBytes[1];
        mFloatBytes[1] ^= mFloatBytes[2];
        mTransByteBuffer.clear();

        return mFloatBytes;
    }

    // // float转byte[]
    // private byte[] floatToByte(float v) {
    // ByteBuffer bb = ByteBuffer.allocate(4);
    // byte[] ret = new byte[4];
    // FloatBuffer fb = bb.asFloatBuffer();
    // fb.put(v);
    // bb.get(ret);
    // return ret;
    // }
}
