package com.hisilicon.miracast.ndk;

import java.lang.ref.WeakReference;

import android.os.Handler;
import android.os.Message;

public final class SinkNative
{
    private static SinkNative sInstance;
    private static Handler sHandler;
    private ISinkListener mListener;

    /**
     * Sink listener interface.
     */
    public interface ISinkListener
    {
        public void onMessageReceived(Message msg);
    }

    static
    {
        System.loadLibrary("sink_jni");
    }

    private SinkNative()
    {
        sHandler = new WorkHandler(this);
        nativeSetup();
    }

    /**
     * Singleton Pattern.
     * @return SinkNative instance
     */
    public static SinkNative getInstance()
    {
        if (sInstance == null)
        {
            sInstance = new SinkNative();
        }

        return sInstance;
    }

    /**
     * Initialize sink business.
     * @param ip source IP address
     * @param port source port number
     */
    public native void initSink(String ip, int port);

    /**
     * Release sink.
     */
    public native void releaseSink();

    /**
     * Start sink.
     */
    public native void startSink();

    /**
     * Stop sink.
     */
    public native void stopSink();

    /**
    * choose hdcp mode
    */
    public native void setHdcpMode(int mode);

    /**
     * Initialize player.
     */
    public native void initPlayer();

    private native void nativeSetup();

    private static void postEventFromNative(int what, int arg1, int arg2)
    {
        // LogUtil.d("");
        Message msg = Message.obtain();
        msg.what = what;
        msg.arg1 = arg1;
        msg.arg2 = arg2;
        sHandler.sendMessage(msg);
    }

    /**
     * Set listener to notify.
     * @param listener listener which to be notified
     */
    public void setListener(ISinkListener listener)
    {
        mListener = listener;
    }

    /**
     * Remove listener.
     */
    public void removeListener()
    {
        mListener = null;
    }

    /**
     * Notify message to listener.
     * @param msg message to notify
     */
    private void notifyListener(Message msg)
    {
        // LogUtil.d("");
        if (mListener != null)
        {
            mListener.onMessageReceived(msg);
        }
    }

    private static class WorkHandler extends Handler
    {
        final WeakReference<SinkNative> mRef;

        public WorkHandler(SinkNative ori)
        {
            mRef = new WeakReference<SinkNative>(ori);
        }

        @Override
        public void handleMessage(Message msg)
        {
            final SinkNative ori = mRef.get();
            Message newMsg = Message.obtain();
            newMsg.copyFrom(msg);
            ori.notifyListener(newMsg);
        }
    }
}
