package com.hisilicon.multiscreen.protocol.remote;

import com.hisilicon.multiscreen.protocol.HiDeviceInfo;

/**
 * Remote control center of MultiScreen.<br>
 * CN:多屏远程控制中心。
 */
public class RemoteControlCenter
{
    private HiDeviceInfo mHiDevice = null;

    private RemoteKeyboard mKeyboard = null;

    private RemoteTouch mTouch = null;

    private RemoteMouse mMouse = null;

    private RemoteSensor mSensor = null;

    private RemoteMedia mRemoteMedia = null;

    private RemoteSpeech mRemoteSpeech = null;

    /**
     * Create an instance of remote control center.<br>
     * CN:创建一个RemoteControlCenter实例 以实现远程连接,及获取远程控制实例。
     * @param device - device information.
     */
    public RemoteControlCenter(HiDeviceInfo device)
    {
        mHiDevice = device;
    }

    /**
     * Reset remote control center with new device info.<br>
     * CN:当Device信息变更时，重置RemoteControlCenter。
     * @param device
     */
    public void reset(HiDeviceInfo device)
    {
        mHiDevice = device;
        getRemoteKeyboard().resetDevice(device);
        getRemoteTouch().resetDevice(device);
        getRemoteMouse().resetDevice(device);
        getRemoteSensor().resetDevice(device);
        getRemoteSpeechControl().resetDevice(device);
        getRemoteMedia().resetDevice(device);
    }

    /**
     * Get the device's IP address.<br>
     * CN:获取设备IP地址。
     * @return - IP address.<br>
     *         CN:IP地址。
     */
    public String getDeviceIP()
    {
        return mHiDevice.getDeviceIP();
    }

    /**
     * Get a keyboard handler which can be used for access keyboard's interface.<br>
     * CN:返回一个远程键盘实例 以访问keyboard相关接口。
     * @return - Remote Keyboard handler.<br>
     *         CN:返回一个keyboard远程控制实例。
     */
    public RemoteKeyboard getRemoteKeyboard()
    {
        if (mKeyboard == null)
        {
            mKeyboard = new RemoteKeyboard(mHiDevice);
        }

        return mKeyboard;
    }

    /**
     * Get remote touch.<br>
     * CN:返回一个RemoteTouch实例，以访问Touch相关接口。
     * @return RemoteTouch.<br>
     *         返回一个Touch远程控制实例。
     */
    public RemoteTouch getRemoteTouch()
    {
        if (mTouch == null)
        {
            mTouch = new RemoteTouch(mHiDevice);
        }

        return mTouch;
    }

    /**
     * Get a Remote Mouse handler which can be used for access RemoteMouse's
     * interface.<br>
     * CN:返回一个getRemoteMouse实例 以访问Mouse相关接口。
     * @return RemoteMouse - Remote Mouse handler.<br>
     *         CN:返回一个Mouse远程控制实例。
     */
    public RemoteMouse getRemoteMouse()
    {
        if (mMouse == null)
        {
            mMouse = new RemoteMouse(mHiDevice);
        }

        return mMouse;
    }

    /**
     * Get a Remote Sensor handler which can be used for access RemoteSensor's
     * interface.<br>
     * CN:返回一个RemoteSensor实例 以访问Sensor相关接口。
     * @return RemoteSensor - Remote Sensor handler.<br>
     *         CN:返回一个Sensor远程控制实例。
     */
    public RemoteSensor getRemoteSensor()
    {
        if (mSensor == null)
        {
            mSensor = new RemoteSensor(mHiDevice);
        }

        return mSensor;
    }

    /**
     * Get a Remote speech which can be used for access remote speech interface<br>
     * CN:返回一个Remote speech相关接口。
     * @return Remote Speech handler.<br>
     *         CN:返回一个RemoteSpeech控制实例。
     */
    public RemoteSpeech getRemoteSpeechControl()
    {
        if (mRemoteSpeech == null)
        {
            mRemoteSpeech = new RemoteSpeech(mHiDevice);
        }

        return mRemoteSpeech;
    }

    /**
     * Get a Remote Media handler which can be used for access RemoteMedia's
     * interface.<br>
     * CN:返回一个getRemoteMedia实例 以访问Media相关接口。
     * @return RemoteMedia - Remote Media handler.<br>
     *         CN:返回一个Media远程控制实例。
     */
    public RemoteMedia getRemoteMedia()
    {
        if (mRemoteMedia == null)
        {
            mRemoteMedia = new RemoteMedia(mHiDevice);
        }

        return mRemoteMedia;
    }

    /**
     * Check status of remote control center.<br>
     * CN:检查RemoteControl状态。
     * @return - true if center is destroyed
     * @deprecated judge the state in control service.
     * @see MultiScreenControlService
     */
    public boolean isDestroyed()
    {
        if (mHiDevice == null)
        {
            return true;
        }

        return false;
    }

    /**
     * Destroy remote control center.<br>
     * CN:销毁服务。<br>
     * Destroy mHiDevice, it can not be reused.<br>
     * CN:销毁多屏设备信息，不可重用。
     */
    public void destroy()
    {
        destroyKeyboard();
        destroyTouch();
        destroyMouse();
        destroySensor();
        destroyRemoteMedia();
        destroyRemoteSpeech();

        mHiDevice = null;
    }

    /**
     * Destroy keyboard.<br>
     * CN:销毁键盘。
     */
    private void destroyKeyboard()
    {
        if (mKeyboard != null)
        {
            mKeyboard.destroy();
            mKeyboard = null;
        }
    }

    /**
     * Destroy touch.<br>
     * CN:销毁触摸。
     */
    private void destroyTouch()
    {
        if (mTouch != null)
        {
            mTouch.destroy();
            mTouch = null;
        }
    }

    /**
     * Destroy mouse.<br>
     * CN:销毁鼠标。
     */
    private void destroyMouse()
    {
        if (mMouse != null)
        {
            mMouse.destroy();
            mMouse = null;
        }
    }

    /**
     * Destroy sensor.<br>
     * CN:销毁体感。
     */
    private void destroySensor()
    {
        if (mSensor != null)
        {
            mSensor.destroy();
            mSensor = null;
        }
    }

    /**
     * Destroy remote media.<br>
     * CN:销毁媒体推送。
     */
    private void destroyRemoteMedia()
    {
        if (mRemoteMedia != null)
        {
            mRemoteMedia.destroy();
            mRemoteMedia = null;
        }
    }

    /**
     * Destroy remote speech.<br>
     * CN:销毁语音控制。
     */
    private void destroyRemoteSpeech()
    {
        if (mRemoteSpeech != null)
        {
            mRemoteSpeech.destroy();
            mRemoteSpeech = null;
        }
    }
}
