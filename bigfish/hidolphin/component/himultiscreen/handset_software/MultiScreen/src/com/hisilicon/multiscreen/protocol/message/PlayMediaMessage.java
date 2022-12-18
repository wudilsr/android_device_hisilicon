/*
 * Play media message
 * | Media Type (int) | Length (int) | URL (String UTF-8) |
 */
package com.hisilicon.multiscreen.protocol.message;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Message class of play Media.<br>
 * CN:播放媒体的消息类.
 */
public class PlayMediaMessage extends PushMessage
{

    /**
     * Type of video message.<br>
     * CN:视屏消息类型.
     */
    public final static int MEDIA_TYPE_VEDIO = 1;

    /**
     * Type of audio message.<br>
     * CN:音频消息类型.
     */
    public final static int MEDIA_TYPE_AUDIO = 2;

    /**
     * Type of image message.<br>
     * CN:图片消息类型.
     */
    public final static int MEDIA_TYPE_IMAGE = 3;

    private int mMediaType;

    private String mUrl;

    /**
     * Set the media type.<br>
     * CN:设置媒体类型.
     * @param type - media type.<br>
     *        CN:媒体类型.
     */
    public void setMediaType(int type)
    {
        mMediaType = type;
    }

    /**
     * Get the media type.<br>
     * CN:获取媒体类型.
     * @return - media type.<br>
     *         CN:媒体类型.
     */
    public int getMediaType()
    {
        return mMediaType;
    }

    /**
     * Set the url of media.<br>
     * CN:设置媒体url.
     * @param url - url of media.<br>
     *        CN:媒体url.
     */
    public void setUrl(String url)
    {
        mUrl = url;
    }

    /**
     * Get the url of media.<br>
     * CN:获取媒体url.
     * @return - url of media.<br>
     *         CN:媒体url.
     */
    public String getUrl()
    {
        return mUrl;
    }

    @Override
    public void sendBody(DataOutputStream out) throws IOException
    {
        out.writeInt(mMediaType);
        if (null != mUrl)
        {
            byte[] data = mUrl.getBytes("UTF-8");
            out.writeInt(data.length);
            out.write(data);
        }
        else
        {
            out.write(0); // Means length = 0
        }
        out.flush();
    }

    @Override
    public void readBody(DataInputStream in) throws IOException
    {
        mMediaType = in.readInt();
        int len = in.readInt();
        if (len > 0)
        {
            byte[] data = new byte[len];

            // Read data use buffer
            byte[] buf = new byte[len];
            for (int p = 0; p < len;)
            {
                int c = in.read(buf, 0, buf.length);
                System.arraycopy(buf, 0, data, p, c);
                p += c;
            }
            mUrl = new String(data, "UTF-8");
            buf = null;
        }
        else
        {
            mUrl = null;
        }
    }
}
