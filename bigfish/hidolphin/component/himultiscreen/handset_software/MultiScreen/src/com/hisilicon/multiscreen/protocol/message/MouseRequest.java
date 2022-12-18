package com.hisilicon.multiscreen.protocol.message;

import java.nio.ByteBuffer;

/**
 * Request class of Mouse.<br>
 * CN:模拟鼠标请求类.
 */
public class MouseRequest extends Request
{
    /**
     * Mouse message length.<br>
     * CN:鼠标请求数据长度。
     */
    private static final short MOUSE_MESSAGE_LENGTH = 22;

    /**
     * Click type of mouse.<br>
     * CN:鼠标点击事件类型。
     */
    private short mClickType;

    /**
     * X offset value.<br>
     * CN:X偏移量。
     */
    private float mDx;

    /**
     * Y offset value.<br>
     * CN:Y偏移量。
     */
    private float mDy;

    /**
     * Byte buffer for handling message.<br>
     */
    private ByteBuffer mBuf = null;

    /**
     * Message for sending.<br>
     */
    private byte[] mMsg = null;

    /**
     * Constructor.<br>
     * CN:构造函数。
     * @param clickType - type of click event.<br>
     *        CN:鼠标事件类型。
     * @param dx - offset of x-axis.<br>
     *        CN:x轴偏移量。
     * @param dy - offset of y-axis.<br>
     *        CN:y轴偏移量。
     */
    public MouseRequest(short clickType, float dx, float dy)
    {
        super();
        setData(clickType, dx, dy);
        initHead();
        initBuf();
    }

    private void initHead()
    {
        head.setMsgType(MessageDef.MTSC_MSGTYPE_MOUSE);
        head.setSendModlueName(MessageDef.MTSC_MODULE_RC_APP);
        head.setRcvModlueName(MessageDef.MTSC_MODULE_RC_CENTER);
        head.setMsgLen(MOUSE_MESSAGE_LENGTH);
        head.setRsv((short) 0);
        head.setRsvTwo((short) 0);
    }

    private void initBuf()
    {
        mBuf = ByteBuffer.allocate(MOUSE_MESSAGE_LENGTH);
        mBuf.clear();
        mBuf.put(head.getBytes());
        mMsg = new byte[MOUSE_MESSAGE_LENGTH];
    }

    /**
     * Set data of mouse request.<br>
     * @param clickType
     * @param dx
     * @param dy
     */
    public void setData(short clickType, float dx, float dy)
    {
        setMouseClickType(clickType);
        setDx(dx);
        setDy(dy);
    }

    /**
     * Set type of Mouse click.<br>
     * CN:设置鼠标事件类型。
     * @param type - type of Mouse click.<br>
     *        CN:鼠标事件类型。
     */
    public void setMouseClickType(short type)
    {
        mClickType = type;
    }

    /**
     * Get type of Mouse click.<br>
     * CN:获取鼠标事件类型。
     * @return - type of Mouse click.<br>
     *         CN:鼠标事件类型。
     */
    public short getMouseClickType()
    {
        return mClickType;
    }

    /**
     * Set the offset of x-axis and y-axis.<br>
     * CN:设置x、y轴偏移量。
     * @param dx - offset of x-axis.<br>
     *        CN:x轴偏移量。
     * @param dy - offset of y-axis.<br>
     *        CN:y轴偏移量。
     */
    public void setDxDy(float dx, float dy)
    {
        mDx = dx;
        mDy = dy;
    }

    /**
     * Set the offset of x-axis.<br>
     * CN:设置x轴偏移量。
     * @param dx - CN:x轴偏移量。
     */
    public void setDx(float dx)
    {
        mDx = dx;
    }

    /**
     * Set the offset of y-axis.<br>
     * CN:设置y轴偏移量。
     * @param dy - CN:y轴偏移量。
     */
    public void setDy(float dy)
    {
        mDy = dy;
    }

    /**
     * Get the offset of x-axis.<br>
     * CN:获取x轴偏移量。
     * @return - CN:x轴偏移量。
     */
    public float getDx()
    {
        return mDx;
    }

    /**
     * Get the offset of y-axis.<br>
     * CN:获取y轴偏移量。
     * @return - offset of y-axis.<br>
     *         CN:y轴偏移量。
     */
    public float getDy()
    {
        return mDy;
    }

    @Override
    public byte[] getBytes()
    {
        if (mBuf != null && mMsg != null)
        {
            // Fill message header
            // mBuf.put(head.getBytes());
            // CN:消息头构造时建立，不变化。
            mBuf.position(MSGHeadObject.MESSAGE_HEAD_LENGTH);

            mBuf.putShort(Short.reverseBytes(getMouseClickType()));
            mBuf.putInt(Integer.reverseBytes((int) getDx()));
            mBuf.putInt(Integer.reverseBytes((int) getDy()));

            // Log.d("MouseRequest", "UDP msgLen=" + msg.length +
            // ",buf.capacity()=" + buf.capacity());

            mBuf.rewind();
            mBuf.get(mMsg);
            // Log.d("MouseRequest", "after get UDP msgLen=" + msg.length);
        }
        return mMsg;
    }
}
