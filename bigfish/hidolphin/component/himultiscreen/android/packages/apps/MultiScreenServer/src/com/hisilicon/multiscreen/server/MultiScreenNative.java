package com.hisilicon.multiscreen.server;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Native invoke class.<br>
 * CN:本地回调类。
 */
public class MultiScreenNative
{
    /**
     * Single instance.<br>
     * CN:单例。
     */
    private static MultiScreenNative sInstance = null;

    /**
     * Native method callback.<br>
     * CN:本地方法回调。
     */
    private static MultisScreenNativeCallback mCallback = null;

    static
    {
        LogTool.i("load multiscreendevice");
        System.loadLibrary("multiscreendevice");
    }

    /**
     * Constructor method.<br>
     * CN:构造方法。
     */
    public MultiScreenNative()
    {
    }

    /**
     * Get instance method. CN:获得类单例的方法。
     * @return single instance of the class.<br>
     *         CN: 该类的单例。
     */
    public static MultiScreenNative getInstance()
    {
        if (sInstance == null)
        {
            sInstance = new MultiScreenNative();
        }

        return sInstance;
    }

    /**
     * Get native callback.<br>
     * CN:得到native回调。
     * @return MultisScreenNativeCallback
     */
    public MultisScreenNativeCallback getCallBack()
    {
        return mCallback;
    }

    /**
     * Set native callback.<br>
     * CN:设置本地回调。
     * @param callback CN:回调接口。
     */
    public void setCallback(MultisScreenNativeCallback callback)
    {
        mCallback = callback;
    }

    /**
     * Callback method for native call java method.<br>
     * CN: 本地调用java方法的回调方法。
     * @param cmdID command id.<br>
     *        CN：方法id.
     * @param param command parameter.<br>
     *        CN:命令参数。
     * @param reserveParam reserve parameter.<br>
     *        CN:预留参数。
     * @return return value of callback.<br>
     *         CN:回调执行的返回值。
     */
    public static int nativeInvoke(int cmdID, String param, String reserveParam)
    {
        return mCallback.nativeInvoke(cmdID, param, reserveParam);
    }

    /**
     * Native method for initializing device.<br>
     * CN:初始化多屏设备本地方法。
     */
    public native void MultiScreenNativeInit();

    /**
     * Native method for start device.<br>
     * 多屏设备启动的本地方法。
     * @param serviceList. CN:服务列表。
     * @param friendlyName. CN:设备易记名称。
     * @return return value. CN:方法执行的返回值。
     */
    public native int MultiScreenDeviceStart(String serviceList, String friendlyName, String netType);

    /**
     * Native method for stop device.<br>
     * CN:多屏设备关闭的本地方法。
     * @return return value.<br>
     *         CN:方法执行的返回值。
     */
    public native int MultiScreenDeviceStop();

    /**
     * It is a native method to notify client that server is manual off. And
     * client will exit.<br>
     * CN:通知客户端多屏服务被手动关闭，需自动退出。
     * @return result.<br>
     *         CN:通知是否成功。
     */
    public native int MultiScreenNotifyManualOff();

    /**
     * Native method for suspend device.<br>
     * CN:待机处理。
     */
    public native int MultiScreenNativeSuspend();

    /**
     * Native method for scene recognition.<br>
     * CN:STB场景识别。
     * @param sceneType CN:场景类型。
     * @return result.
     */
    public native int native_MultiScreenNotifySceneRecognition(String sceneType);
}
