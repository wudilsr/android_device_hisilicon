/**
 *
 */
package com.hisilicon.multiscreen.protocol.message;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Push server message class.<br>
 * CN:pushServer消息抽象类。已经由协议实现，为兼容媒体推送暂时保留。
 *
 */
public abstract class PushMessage {

    protected PushMessageHead mHead;

    /**
     * Set the head of message.<br>
     * CN:设置消息头.
     * @param h - head of message.<br>
     * CN:消息头.
     */
    public void setHead(PushMessageHead h) {
        mHead = h;
    }

    /**
     * Get the head of message.<br>
     * CN:获取消息头.
     * @return - head of message.<br>
     * CN:消息头.
     */
    public PushMessageHead getHead() {
        return mHead;
    }

    /**
     * Send message.<br>
     * CN:发送消息.
     * @param out - output Stream.<br>
     * CN:输出流.
     * @throws IOException - IOException.<br>
     * CN:发送消息时可能的IO异常
     */
    public abstract void sendBody(DataOutputStream out) throws IOException;
    /**
     * Read message.<br>
     * CN:读取消息.
     * @param in - input stream.<br>
     * CN:输入流
     * @throws IOException - IOException.<br>
     * CN:读取消息时可能的IO异常.
     */
    public abstract void readBody(DataInputStream in) throws IOException;

    /**
     * Send message with head.<br>
     * CN:发送包含头的消息.
     * @param out - output stream.<br>
     * CN:输出流.
     * @throws IOException - IOException.<br>
     * CN:发送消息时可能的IO异常.
     */
    public void sendOutputMsg(DataOutputStream out) throws IOException {
        if (null == mHead) {
            // FIXME Add error processing
            return;
        }

        mHead.sendOutputMsg(out);
        sendBody(out);
    }

}
