/*
 * Launch android application message.
 * Start with message length, an integer, follow with application name, encoding by UTF-8
 * | Length(int) | application name (String UTF-8) |
 */
package com.hisilicon.multiscreen.protocol.message;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 *
 * @deprecated
 * CN:用于启动安卓应用程序的消息类，消息包含数据长度、安卓应用程序名称
 *
 */
public class AppLaunchMessage extends PushMessage {

    private String mAppName;

    /**
     * Set app name.<br>
     * CN:设置应用程序名称.
     * @param name - application name.<br>
     * CN:应用程序名称.
     */
    public void setApplicationName(String name) {
        mAppName = name;
    }

    /**
     * Get Application Name.<br>
     * CN:获取应用程序名称.
     * @return - application name.<br>
     * CN:应用程序名称.
     */
    public String getApplicationName() {
        return mAppName;
    }

    @Override
    public void sendBody(DataOutputStream out) throws IOException {
        if (null != mAppName) {
            byte[] data = mAppName.getBytes("UTF-8");
            out.writeInt(data.length);
            out.write(data);
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

            mAppName = new String(data, "UTF-8");
        } else {
            mAppName = null;
        }
    }

    /*
     * Commented by d47906 public void print() { super.print();
     * Log.e("APPLaunch","nameLenth="+nameLenth); Log.e("APPLaunch","name="+new
     * String(name)); }
     */
}
