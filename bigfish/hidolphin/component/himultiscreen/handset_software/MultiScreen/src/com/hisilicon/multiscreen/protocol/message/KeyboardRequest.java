package com.hisilicon.multiscreen.protocol.message;

import java.nio.ByteBuffer;

/**
 * Virtual Keyboard request class.<br>
 * CN:虚拟按键请求类.
 */

public class KeyboardRequest extends Request
{
    /**
     * Length of keyboard message.<br>
     * CN:键盘消息长度。
     */
    private static final short KEYBOARD_MESSAGE_LENGTH = 22;

    /**
     * Even type for keyboard.<br>
     * CN:键盘事件类型。
     */
    private static final short KEYBOARD_EVEN_TYPE = 0x107;

    /**
     * Value of key.<br>
     * CN:键值。
     */
    private int mKeyValue = 0;

    /**
     * Up or down state.<br>
     * CN:按键抬起或按下状态。
     */
    private int mUpdownState = 0; // down or up

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
     * CN:构造函数.
     * @param key - key value.<br>
     *        CN:键值.
     * @param state - state value.<br>
     *        CN:按下的状态.
     */
    public KeyboardRequest(int key, int state)
    {
        super();
        setData(key, state);

        initHead();
        initBuf();
    }

    private void initHead()
    {
        head.setMsgType(MessageDef.MTSC_MSGTYPE_KEYBOARD);
        head.setSendModlueName(MessageDef.MTSC_MODULE_RC_APP);
        head.setRcvModlueName(MessageDef.MTSC_MODULE_RC_CENTER);
        head.setMsgLen(KEYBOARD_MESSAGE_LENGTH);
        head.setRsv((short) 0);
        head.setRsvTwo((short) 0);
    }

    private void initBuf()
    {
        mBuf = ByteBuffer.allocate(KEYBOARD_MESSAGE_LENGTH);
        mBuf.clear();
        mBuf.put(head.getBytes());
        mMsg = new byte[KEYBOARD_MESSAGE_LENGTH];
    }

    public void setData(int key, int state)
    {
        setKey(key);
        setState(state);
    }

    /**
     * Set keyboard value.<br>
     * CN:设置键值.
     * @param key - keyboard value.<br>
     *        CN:键值.
     */
    public void setKey(int key)
    {
        mKeyValue = key;
    }

    /**
     * Set keyboard up/down status.<br>
     * CN:设置按键状态.
     * @param type - keyboard status.<br>
     *        CN:按键状态.
     */
    public void setState(int type)
    {
        mUpdownState = type;
    }

    /**
     * Get keyboard value.<br>
     * CN:获取键值.
     * @return - keyboard value.<br>
     *         CN:键值.
     */
    public int getKey()
    {
        return mKeyValue;
    }

    /**
     * Get keyboard status.<br>
     * CN:获取按键状态.
     * @return - keyboard status.<br>
     *         CN:按键状态.
     */
    public int getState()
    {
        return mUpdownState;
    }

    @Override
    public byte[] getBytes()
    {
        if (mBuf != null && mMsg != null)
        {
            // Fill message header
            // mBuf.put(head.getBytes());
            mBuf.position(MSGHeadObject.MESSAGE_HEAD_LENGTH);

            mBuf.putShort(Short.reverseBytes(KEYBOARD_EVEN_TYPE));
            mBuf.putInt(Integer.reverseBytes(getKey()));
            mBuf.putInt(Integer.reverseBytes(getState()));

            // Log.e("KeyboardRequest", "UDP msgLen=" + msg.length +
            // ",buf.capacity()=" + buf.capacity());
            mBuf.rewind();
            mBuf.get(mMsg, 0, mMsg.length);

            // Log.e("KeyboardRequest", "after get UDP msgLen=" +
            // msg.length);
        }
        return mMsg;
    }
}
