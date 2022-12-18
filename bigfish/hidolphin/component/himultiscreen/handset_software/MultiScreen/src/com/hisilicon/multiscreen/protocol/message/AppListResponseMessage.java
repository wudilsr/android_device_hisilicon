/*
 * Response android application list message.
 * | Length (int) | Application List (byte array) |
 */
package com.hisilicon.multiscreen.protocol.message;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Response message class of getting android application list.<br>
 * CN:对安卓应用程序列表请求的响应消息类.
 */
public class AppListResponseMessage extends PushMessage {

    private byte[] mContent;

    /**
     * Set response message.<br>
     * CN:设置响应信息.
     * @param content -  response message.<br>
     * CN:响应信息.
     */
    public void setContent(byte[] content) {
        mContent = content;
    }

    /**
     * Get response message.<br>
     * CN:获取响应信息
     * @return - response message.<br>
     * CN:响应信息.
     */
    public byte[] getContent() {
        return mContent;
    }

    @Override
    public void sendBody(DataOutputStream out) throws IOException {
        if (null != mContent) {
            out.writeInt(mContent.length);
            out.write(mContent);
            out.flush();
        }
    }

    @Override
    public void readBody(DataInputStream in) throws IOException {
        int len = in.readInt();
        if (len > 0) {
            byte[] data = new byte[len];

            // Read data use buffer
            byte[] buf = new byte[1024];
            for (int p = 0; p < len; ) {
                int c = in.read(buf, 0, buf.length);
                System.arraycopy(buf, 0, data, p, c);
                p += c;
            }

            mContent = data;
        } else {
            mContent = null;
        }
    }

    /*
     * Commented by d47906 public void print() { super.print();
     * Log.e("APPLIST","bodyLenth="+bodyLenth); Log.e("APPLIST","body="+new
     * String(body)); }
     */
}
