package com.hisilicon.multiscreen.protocol.message;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Default response message.<br>
 * CN:默认响应消息类.
 */
public class DefaultResponseMessage extends PushMessage
{

    /**
     * Default response message.<br>
     * CN:默认响应消息.
     */
    public int mCode = 0;

    /**
     * Set response message.<br>
     * CN:设置响应消息.
     * @param code - response message.<br>
     * CN:响应消息.
     */
    public void setCode(int code)
    {
        mCode = code;
    }

    /**
     * Get response message.<br>
     * CN:获取响应消息.
     * @return - response message.<br>
     * CN:响应消息.
     */
    public int getCode()
    {
        return mCode;
    }

    /* (non-Javadoc)
     * @see com.hisilicon.multiscreen.service.PushMessage#sendBody(java.io.DataOutputStream)
     */
    @Override
    public void sendBody(DataOutputStream out) throws IOException
    {
        out.writeInt(mCode);
        out.flush();
    }

    /* (non-Javadoc)
     * @see com.hisilicon.multiscreen.service.PushMessage#readBody(java.io.DataInputStream)
     */
    @Override
    public void readBody(DataInputStream in) throws IOException
    {
        mCode = in.readInt();
    }

}
