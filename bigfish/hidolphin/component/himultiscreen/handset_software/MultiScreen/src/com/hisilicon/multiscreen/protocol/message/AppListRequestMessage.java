/*
 * Request android application list message.
 * | Length(int) | request command (String UTF-8) |
 */
package com.hisilicon.multiscreen.protocol.message;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Request message of getting application list.<br>
 * CN:请求安卓应用程序列表的信息类.
 */
public class AppListRequestMessage extends PushMessage {

    private String mCommand;

    /**
     * Set command.<br>
     * CN:设置控制消息.
     * @param cmd - command.<br>
     * CN:控制消息.
     */
    public void setCommand(String cmd) {
        mCommand = cmd;
    }

    /**
     * Get command.<br>
     * CN:获取控制消息.
     * @return - command.<br>
     * CN:控制消息。
     */
    public String getCommand() {
        return mCommand;
    }

    /* (non-Javadoc)
     * @see com.hisilicon.multiscreen.service.PushMessage#sendOutputMsg(java.io.DataOutputStream)
     */
    @Override
    public void sendBody(DataOutputStream out) throws IOException {
        if (null != mCommand) {
            byte[] data = mCommand.getBytes("UTF-8");
            out.writeInt(data.length);
            out.write(data);
            out.flush();
        }
    }

    /* (non-Javadoc)
     * @see com.hisilicon.multiscreen.service.PushMessage#readInputMsg(java.io.DataInputStream)
     */
    @Override
    public void readBody(DataInputStream in) throws IOException {
        int len = in.readInt();
        if (len > 0) {
            byte[] data = new byte[len];
            byte[] buf = new byte[len];
            for (int p = 0; p < len; ) {
                int c = in.read(buf, 0, buf.length);
                System.arraycopy(buf, 0, data, p, c);
                p += c;
            }
            buf = null;
            mCommand = new String(data, "UTF-8");
        } else {
            mCommand = null;
        }

    }

}
