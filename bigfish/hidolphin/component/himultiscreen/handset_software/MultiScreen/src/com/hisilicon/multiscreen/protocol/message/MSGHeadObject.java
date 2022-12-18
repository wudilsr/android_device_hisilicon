package com.hisilicon.multiscreen.protocol.message;

import java.nio.ByteBuffer;

/**
 * Head of request Message, used for virtual keyboard, touch, Mouse and so on.<br>
 * CN:请求的头数据类，用于虚拟键盘、触摸、鼠标等。
 */
public class MSGHeadObject
{
    /**
     * Head size is 12 bytes.<br>
     * CN:数据头长度为12字节。
     */
    public static final int MESSAGE_HEAD_LENGTH = 12;

    /**
     * Model name of message source.<br>
     * CN:数据源模块名。
     */
    private short s16sndModuleName = 0;

    /**
     * Model name of message receiver.<br>
     * CN:数据接收模块名。
     */
    private short s16rcvModuleName = 0;

    /**
     * Message type.<br>
     * CN:数据类型。
     */
    private short s16msgType = 0;

    /**
     * Length of message.<br>
     * CN:数据长度。
     */
    private short s16usMsglen = 0;

    /**
     * First reserve field.<br>
     * CN:保留一。
     */
    private short s16usRsv = 0;

    /**
     * Second reserve field.<br>
     * CN:保留二。
     */
    private short s16usRsvTwo = 0;

    /**
     * Byte buffer of message head.<br>
     */
    private ByteBuffer mHeadBuf = null;

    /**
     * Constructor.<br>
     * CN:构造函数。
     */
    public MSGHeadObject()
    {
        s16sndModuleName = 0;
        s16rcvModuleName = 0;
        s16msgType = 0;
        s16usMsglen = 0;
        s16usRsv = 0;
        s16usRsvTwo = 0;
        mHeadBuf = ByteBuffer.allocate(MESSAGE_HEAD_LENGTH);
    }

    /**
     * Set the name of send module.<br>
     * CN:设置发送模块名。
     * @param name - name of send module.<br>
     *        CN:发送模块名。
     */
    public void setSendModlueName(short name)
    {
        s16sndModuleName = name;
    }

    /**
     * Set the name of receive module.<br>
     * CN:设置接收模块名。
     * @param name - name of receive module.<br>
     *        CN:接收模块名。
     */
    public void setRcvModlueName(short name)
    {
        s16rcvModuleName = name;
    }

    /**
     * Set the type of message.<br>
     * CN:设置消息类型。
     * @param msgType - type of message.<br>
     *        CN:消息类型。
     */
    public void setMsgType(short msgType)
    {
        s16msgType = msgType;
    }

    /**
     * Set the length of message.<br>
     * CN:设置消息长度。
     * @param msgLen - length of message.<br>
     *        CN:消息长度。
     */
    public void setMsgLen(short msgLen)
    {
        s16usMsglen = msgLen;
    }

    /**
     * Set the reserve member rsv.<br>
     * CN:设置保留字段一。
     * @param rsv - reserve member rsv.<br>
     *        CN:保留字段一。
     */
    public void setRsv(short rsv)
    {
        s16usRsv = rsv;
    }

    /**
     * Set the reserve member rsvTwo.<br>
     * CN:设置保留字段二。
     * @param rsvTwo - reserve member rsvTwo.<br>
     *        CN:保留字段二。
     */
    public void setRsvTwo(short rsvTwo)
    {
        s16usRsvTwo = rsvTwo;
    }

    /**
     * Get the name of send module.<br>
     * CN:获取发送模块名。
     * @return - name of send module.<br>
     *         CN:接收模块名。
     */
    public short getSendModlueName()
    {
        return s16sndModuleName;
    }

    /**
     * Get the name of receive module.<br>
     * CN:获取接收模块名。
     * @return - name of receive module.<br>
     *         CN:接收模块名。
     */
    public short getRcvModlueName()
    {
        return s16rcvModuleName;
    }

    /**
     * Get the message type.<br>
     * CN:获取消息类型。
     * @return - message type.<br>
     *         CN:消息类型。
     */
    public short getMsgType()
    {
        return s16msgType;
    }

    /**
     * Get the message length.<br>
     * CN:获取消息长度。
     * @return - message length.<br>
     *         CN:消息长度。
     */
    public short getMsgLen()
    {
        return s16usMsglen;
    }

    /**
     * Get the reserve member s16usRsv.<br>
     * CN:获取保留字段一。
     * @return - reserve member s16usRsv.<br>
     *         CN:保留字段一。
     */
    public short getRsv()
    {
        return s16usRsv;
    }

    /**
     * Get the reserve member s16usRsvTwo.<br>
     * CN:获取保留字段二。
     * @return - reserve member s16usRsvTwo.<br>
     *         CN:保留字段二。
     */
    public short getRsvTwo()
    {
        return s16usRsvTwo;
    }

    /**
     * Get the byte array of Head class, the byte order of member variable is in
     * reserve mode.<br>
     * CN:获取头的字节数组，成员的字节序逆序。
     * @return - byte array of Head class.<br>
     *         CN:头德字节数组。
     */
    public byte[] getBytes()
    {
        mHeadBuf.rewind();
        mHeadBuf.putShort(Short.reverseBytes(s16sndModuleName));
        mHeadBuf.putShort(Short.reverseBytes(s16rcvModuleName));
        mHeadBuf.putShort(Short.reverseBytes(s16msgType));
        mHeadBuf.putShort(Short.reverseBytes(s16usMsglen));
        mHeadBuf.putShort(Short.reverseBytes(s16usRsv));
        mHeadBuf.putShort(Short.reverseBytes(s16usRsvTwo));

        return mHeadBuf.array();
    }
}
