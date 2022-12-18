package com.hisilicon.multiscreen.protocol.message;

import java.nio.ByteBuffer;
import java.util.ArrayList;

/**
 * Request class of Touch.<br>
 * CN:多点触摸类。
 */
public class TouchRequest extends Request
{
    /**
     * Max finger number.<br>
     * CN:最大手指数量。
     */
    public static final int MAX_FINGER_NUM = 5;

    /**
     * Length of touch message.<br>
     * CN:触摸数据长度。
     */
    private static final short TOUCH_MESSAGE_LENGTH = 76;

    /**
     * Finger pressed value.<br>
     * CN:手指按下的值。
     */
    private static final int PRESSED_VALUE = 1;

    /**
     * Finger up value.<br>
     * CN:手指抬起的值。
     */
    private static final int FINGER_UP_VALUE = 0;

    /**
     * Number of fingers.<br>
     * CN:手指数量。
     */
    private int mFingerNum = 0;

    /**
     * List of fingers.<br>
     * CN:手指信息列表。
     */
    private ArrayList<FingerInfo> mFingers = new ArrayList<FingerInfo>();

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
     */
    public TouchRequest()
    {
        super();
        initHead();
        initBuf();
    }

    private void initHead()
    {
        head.setMsgType(MessageDef.MTSC_MSGTYPE_TOUCH);
        head.setSendModlueName(MessageDef.MTSC_MODULE_RC_APP);
        head.setRcvModlueName(MessageDef.MTSC_MODULE_RC_CENTER);
        head.setMsgLen(TOUCH_MESSAGE_LENGTH);
        head.setRsv((short) 0);
        head.setRsvTwo((short) 0);
    }

    private void initBuf()
    {
        mBuf = ByteBuffer.allocate(TOUCH_MESSAGE_LENGTH);
        mBuf.clear();
        mBuf.put(head.getBytes());
        mMsg = new byte[head.getMsgLen()];

        for (int i = 0; i < MAX_FINGER_NUM; i++)
        {
            mFingers.add(new FingerInfo());
        }
        // Default number of fingers supported.
        setFingerNum(2);
    }

    /**
     * Set the number of fingers.<br>
     * CN:设置触摸手指数量。
     * @param num - number of fingers.<br>
     *        CN:手指数量。
     */
    public void setFingerNum(int num)
    {
        mFingerNum = num;
    }

    /**
     * Get the number of fingers.<br>
     * CN:获取手指数量。
     * @return - number of fingers.<br>
     *         CN:手指数量。
     */
    public int getFingerNum()
    {
        return mFingerNum;
    }

    /**
     * Set finger information array.<br>
     * CN:设置触摸手指对象数组。
     * @param fingers - finger information array.<br>
     *        CN:手指对象数组。
     */
    public void setFingers(ArrayList<FingerInfo> fingers)
    {
        this.mFingers = fingers;
    }

    /**
     * Get finger information array.<br>
     * CN:获取手指对象数组。
     * @return - finger information array.<br>
     *         CN:手指对象数组。
     */
    public ArrayList<FingerInfo> getFingers()
    {
        return mFingers;
    }

    /**
     * Set finger information.<br>
     * CN:设置手指信息。
     * @param index - index of finger.<br>
     *        CN:手指对象编号。
     * @param x - coordinate of x-axis.<br>
     *        CN:x轴坐标。
     * @param y - coordinate of y-axis.<br>
     *        CN:y轴坐标。
     * @param press - press status.<br>
     *        CN:按压状态。
     */
    public void setFingerInfo(int index, int x, int y, boolean press)
    {
        if (index < MAX_FINGER_NUM)
        {
            FingerInfo info = mFingers.get(index);
            info.setX(x);
            info.setY(y);
            info.setPress(press);
        }
    }

    /**
     * Get finger information.<br>
     * CN:获取单个手指对象。
     * @param index - index of finger.<br>
     *        CN:手指对象编号。
     * @return - finger information.<br>
     *         CN:手指对象。
     */
    public FingerInfo getFingerInfo(int index)
    {
        return mFingers.get(index);
    }

    @Override
    public byte[] getBytes()
    {
        if ((mBuf != null) && (mMsg != null))
        {
            // Fill message header
            // mBuf.put(head.getBytes());
            mBuf.position(MSGHeadObject.MESSAGE_HEAD_LENGTH);

            mBuf.putInt(Integer.reverseBytes(getFingerNum()));
            for (int i = 0; i < TouchRequest.MAX_FINGER_NUM; i++)
            {
                if (i < getFingerNum())
                {
                    FingerInfo fin = getFingerInfo(i);
                    mBuf.putInt(Integer.reverseBytes(fin.getX()));
                    mBuf.putInt(Integer.reverseBytes(fin.getY()));
                    mBuf.putInt(Integer.reverseBytes(fin.getPress() ? PRESSED_VALUE
                        : FINGER_UP_VALUE));
                }
                else
                {
                    mBuf.putInt(0);
                    mBuf.putInt(0);
                    mBuf.putInt(0);
                }
            }

            mBuf.rewind();
            mBuf.get(mMsg, 0, mMsg.length);
        }
        return mMsg;
    }
}
