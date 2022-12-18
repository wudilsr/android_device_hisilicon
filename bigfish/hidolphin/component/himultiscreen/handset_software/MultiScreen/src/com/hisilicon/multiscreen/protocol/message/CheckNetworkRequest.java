package com.hisilicon.multiscreen.protocol.message;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Class of check network request.<br>
 * CN:网络检查请求类。
 */
public class CheckNetworkRequest
{
    /**
     * Tag of check network request.<br>
     */
    private short mTag;

    /**
     * Number of check network request.<br>
     */
    private int mNumber;

    /**
     * Data length of CheckNetworkRequest.<br>
     * CN:网络状态检查类的字节长度。
     */
    public static final int DATA_LENGTH = (Short.SIZE + Integer.SIZE) / 8;

    /**
     * Number of bits in one byte.<br>
     * CN:一个字节包含的位数量。
     */
    private static final int BIT_NUMBER_IN_BYTE = 8;

    /**
     * Length of bytes of tag in check message.<br>
     * CN:网络检查消息的TAG参数字节长度。
     */
    private static final int CHECK_TAG_LENGTH = (Short.SIZE) / BIT_NUMBER_IN_BYTE;

    /**
     * Length of bytes of number in check message.<br>
     * CN:网络监察消息的NUMBER参数字节长度。
     */
    private static final int CHECK_NUMBER_LENGTH = (Integer.SIZE) / BIT_NUMBER_IN_BYTE;

    /**
     * Default constructor.<br>
     * CN:构造函数。
     */
    public CheckNetworkRequest()
    {
        mTag = (short) 0;
        mNumber = 0;
    }

    /**
     * Constructor with tag and request number.<br>
     * CN:构造函数。
     * @param tag - type tag.<br>
     *        CN:类型标签。
     * @param number - request number.<br>
     *        CN:请求号。
     */
    public CheckNetworkRequest(short tag, int number)
    {
        mTag = tag;
        mNumber = number;
    }

    /**
     * Get type tag.<br>
     * CN:获取类型标签。
     * @return - type tag.<br>
     *         CN:类型标签。
     */
    public short getTag()
    {
        return mTag;
    }

    /**
     * Set type tag.<br>
     * CN:设置类型标签。
     * @param tag - type tag.<br>
     *        CN:类型标签。
     */
    public void setTag(short tag)
    {
        mTag = tag;
    }

    /**
     * Get request number.<br>
     * CN:获取请求号。
     * @return - request number.<br>
     *         CN:请求号。
     */
    public int getNumber()
    {
        return mNumber;
    }

    /**
     * Set request number.<br>
     * CN:设置请求号。
     * @param number - request number.<br>
     *        CN:请求号。
     */
    public void setNumber(int number)
    {
        mNumber = number;
    }

    /**
     * Link check message to byte array.<br>
     * CN:连接检查消息转换成字节数组。
     * @return - byte array.<br>
     *         CN:字节数组。
     */
    public byte[] getData()
    {
        ByteBuffer buf = ByteBuffer.allocate(DATA_LENGTH);
        byte[] msg = new byte[DATA_LENGTH];

        buf.putShort(mTag);
        buf.putInt(mNumber);

        if (buf != null && msg != null)
        {
            buf.rewind();
            buf.get(msg, 0, msg.length);
            buf.clear();
        }
        return msg;
    }

    /**
     * Byte array to link check message.<br>
     * CN:字节数组转换为网络检查请求对象。
     * @param data - byte array.<br>
     *        CN:字节数组。
     * @return - link check message.<br>
     *         CN:网络检查请求对象。
     */
    public CheckNetworkRequest getCheckNetworkRequestfromBytes(byte[] data)
    {
        if (data != null)
        {
            CheckNetworkRequest request;
            int tagLength = CHECK_TAG_LENGTH;
            int numberLength = CHECK_NUMBER_LENGTH;
            byte[] tagData = new byte[tagLength];
            byte[] numberData = new byte[numberLength];

            try
            {
                // CN:读取数据包tag字段，类型为short
                System.arraycopy(data, 0, tagData, 0, tagLength);
                InputStream inputStreamTag = new ByteArrayInputStream(tagData);
                DataInputStream inTag = new DataInputStream(inputStreamTag);
                short tag;

                tag = inTag.readShort();

                // CN:读取数据包mNumber字段，类型为int
                System.arraycopy(data, tagLength, numberData, 0, numberLength);
                InputStream inputStreamNumber = new ByteArrayInputStream(numberData);
                DataInputStream inNumber = new DataInputStream(inputStreamNumber);
                int number;

                number = inNumber.readInt();

                request = new CheckNetworkRequest(tag, number);

                inTag.close();
                inNumber.close();

                return request;

            }
            catch (IOException e)
            {
                LogTool.e("IO Exception");
            }
        }

        return null;
    }
}
