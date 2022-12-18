package com.hisilicon.multiscreen.protocol.remote;

import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.message.PlayMediaMessage;
import com.hisilicon.multiscreen.protocol.message.PushMessageHead;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Remote Media control class.<br>
 * CN:远程媒体控制类。
 * @see RemoteControlCenter
 */
public class RemoteMedia
{

    private HiDeviceInfo mDevice = null;

    private RemotePushing mRemotePushing = null;

    /**
     * Constructor. Create a remote Media handler based on DeviceInfo.<br>
     * CN:构造函数，通过DeviceInfo对象新建远程Media控制类。
     * @param deviceInfo - device information.<br>
     *        CN:输入的DeviceInfo对象。
     */

    public RemoteMedia(HiDeviceInfo deviceInfo)
    {
        mDevice = deviceInfo;
        mRemotePushing = new RemotePushing(mDevice);
    }

    protected void destroy()
    {

    }


    /**
     * Reset HiDevice info.
     * CN:重置多屏设备信息。
     * @param deviceInfo HiDevice
     */
    protected void resetDevice(HiDeviceInfo deviceInfo)
    {
        mDevice = deviceInfo;
        mRemotePushing.resetDevice(deviceInfo);
    }

    /*
     * Commented by d47906 protected boolean getNetworkState() { return isAlive;
     * }
     * protected void setNetworkState(boolean isAlive) { this.isAlive = isAlive;
     * }
     * protected void sendKeepAliveMsg() throws Exception {
     * //Log.e(TAG,"send keep alive"); if(SocketUtils.mediaOut!=null) {
     * SocketUtils.mediaOut.writeInt(RemoteControlCenter.SEND_KEEP_ALIVE);
     * SocketUtils.mediaOut.write(HISI_FLAG.getBytes());
     * SocketUtils.mediaOut.flush(); } }
     * protected void sendKeepMediaAlive() throws Exception { isAlive = false;
     * Log.e(TAG,"send keep alive"); // send 5 times to avoid package missing
     * for(int i=0;i<5;i++) { sendKeepAliveMsg(); Thread.sleep(1000); } }
     */

    /*
     * Commented by d47906, Get media info is not implemented protected void
     * returnPlayingInfo (MediaInfo info) { if(getPlayInfo!=null) {
     * getPlayInfo.returnPlayingInfo(true, info); } }
     */

    /**
     * Play Media with the given url.<br>
     * CN:远程播放指定的媒体。
     * @param type - Media's type.<br>
     *        CN:媒体的类型。
     * @param url - URL.<br>
     *        CN:播放媒体的URL。
     */
    public void playMedia(int type, String url)
    {
        try
        {
            PushMessageHead head = new PushMessageHead();
            head.setType(PushMessageHead.PLAY_MEDIA);

            PlayMediaMessage msg = new PlayMediaMessage();
            msg.setHead(head);
            msg.setMediaType(type);
            msg.setUrl(url);
            mRemotePushing.pushing(msg);

        }
        catch (Exception e)
        {
            LogTool.e(e.getMessage());
        }
    }

    /**
     * 获取视频相关信息,异步函数 收到信息后,回调给调用者,需要调用者实现callback函数
     * @param programCode : 视频标识或者url
     * @param callback
     */
    /*
     * Not need callback public void getMediaInfo(String
     * programCode,GetPlayInfoCallback callback) { this.getPlayInfo = callback;
     * sendGetPlayInfo(programCode);
     * }
     */

    /*
     * Commented by d47906, 2012-7-28 private void sendGetPlayInfo(String
     * programCode) { try { Log.e(TAG, "send get media info:"+programCode); //
     * SocketUtils.mediaOut.writeInt(RemoteControlCenter.GET_MEIDA_INFO); //
     * SocketUtils.mediaOut.write(HISI_FLAG.getBytes()); byte [] buf =
     * programCode.getBytes(); // SocketUtils.mediaOut.writeInt(buf.length); //
     * SocketUtils.mediaOut.write(buf); // SocketUtils.mediaOut.flush();
     * //FIXME get media info
     * this.msgHead.setType(RemoteControlCenter.GET_MEIDA_INFO);
     * playMediaMsg.setHead(msgHead); playMediaMsg.setUrl(programCode);
     * mRemotePushing.pushing(playMediaMsg);
     * }catch(Exception e) { e.printStackTrace(); } }
     */

}
