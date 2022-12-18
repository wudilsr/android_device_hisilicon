package com.hisilicon.multiscreen.protocol.message;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Message head of push server.<br>
 * CN:PushServer消息头信息类.
 *
 */
public class PushMessageHead {

    private static final int PUSH_MSG_BASE = 0x300;

    /**
     * Default message type.<br>
     * CN:默认消息类型.
     */
    public static final int DEFAULT_RESPONSE     = PUSH_MSG_BASE + 1; //与客户端发送的类型对应
    /**
     * Request type of getting application list message.<br>
     * CN:请求APP列表消息类型.
     */
    public static final int GET_APPS_REQUEST     = PUSH_MSG_BASE + 2;
    /**
     * Response type of getting application list message.<br>
     * CN:响应APP列表请求消息类型
     */
    public static final int GET_APPS_RESPONSE     = PUSH_MSG_BASE + 3;
    /**
     * Message type of launching application.<br>
     * CN:启动APP消息类型.
     */
    public static final int LAUNCH_APP             = PUSH_MSG_BASE + 4;
    /**
     * Message type of playing meida.<br>
     * CN:推送多媒体消息类型.
     */
    public static final int PLAY_MEDIA             = PUSH_MSG_BASE + 5;

    /* Not implements
    public static final int GET_MEIDA_INFO = PUSH_MSG_BASE + 5;
    public static final int RES_MEIDA_INFO = PUSH_MSG_BASE + 6;
    public static final int SEND_KEEP_ALIVE = PUSH_MSG_BASE + 7;
    public static final int RES_KEEP_ALIVE = PUSH_MSG_BASE + 8;
    public static final int LEAVE_NETWORK = PUSH_MSG_BASE + 9;
    */

    protected int mMsgType;

    /**
     * Set media type.<br>
     * CN:设置媒体类型.
     * @param type - media type.<br>
     * CN:媒体类型.
     */
    public void setType(int type) {
        mMsgType = type;
    }

    /**
     * Get media type.<br>
     * CN:获取消息类型.
     * @return - media type.<br>
     * CN:消息类型.
     */
    public int getType() {
        return mMsgType;
    }

    /**
     * Send message type out.<br>
     * CN:发送消息类型.
     * @param out - output stream.<br>
     * CN:输出流.
     * @throws IOException - 发送消息时可能产生的IO异常
     */
    public void sendOutputMsg(DataOutputStream out) throws IOException {
        if (out != null) {
            out.writeInt(mMsgType);
        }
    }

    /**
     * Read message type in.<br>
     * CN:读取消息类型.
     * @param input - input stream.<br>
     * CN:输入流.
     * @throws IOException - 读取消息时可能产生的IO异常
     */
    public void readInputMsg(DataInputStream input) throws IOException {
        if (input != null) {
            mMsgType = input.readInt();
        }
    }

    /*
     * Commented by d47906, should be redirect public void print() {
     * Log.e("DTVPlayerEGG","msgType="+msgType); }
     */
}
