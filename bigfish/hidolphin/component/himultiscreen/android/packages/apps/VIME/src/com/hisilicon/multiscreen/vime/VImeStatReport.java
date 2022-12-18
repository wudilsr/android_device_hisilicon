package com.hisilicon.multiscreen.vime;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

import com.hisilicon.multiscreen.protocol.server.IMultiScreenManagerVIme;
import com.hisilicon.multiscreen.protocol.server.VImeStatusObserver;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;
import com.hisilicon.multiscreen.protocol.utils.VImeStatusDefine;

/**
 * Class for VIME communicates with MultiScreen server.<br>
 * CN:用于VIME与多屏服务通信的类。
 */
public class VImeStatReport
{
    /**
     * Default client port of VIME.<br>
     * CN:默认VIME客户端的端口。
     */
    public static final int VIME_CLIENT_DEFAULT_PORT = 2016;

    /** Context the VImeStatReport rely on.<br>
     * CN:VIME依赖的上下文环境。
     *  */
    private Context mContext = null;

    /** Record virtual IME's status.<br>
     * CN:虚拟输入法状态记录。
     * */
    private VImeStatusObserver mObserver = null;

    /** Remote client's IP<br>
     * CN:远端客户端的ip.<br>
     * */
    private String mRemoteIP = null;

    /** Remote client's port <br>
     * CN:远端客户端的端口。
     * */
    private int mRemotePort = VIME_CLIENT_DEFAULT_PORT;

    /**
     * VIme's control interface <br>
     * VIme的控制接口
     */
    private IMultiScreenManagerVIme mIMultiScreenManagerVIme = null;

    /**
     * Construct method of VImeStatReport <br>
     * CN:状态报告类构造方法
     * @param context context of input method service.<br>
     *        CN:输入法服务的上下文
     */
    public VImeStatReport(Context context, IMultiScreenManagerVIme managerVIme)
    {
        super();
        this.mContext = context;
        this.mObserver = new VImeStatusObserver();
        this.mIMultiScreenManagerVIme = managerVIme;
    }

    /**
     * Broadcast Receiver of VIME Control module<br>
     * CN:接收VIME控制模块的广播接收者。
     */
    private BroadcastReceiver mVImeReceiver = new BroadcastReceiver()
    {
        public void onReceive(Context context, Intent intent)
        {
            String action = intent.getAction();

            if (MultiScreenIntentAction.CHECK_VIME_STATUS.equals(action))
            {
                responseCheck(mObserver.getVImeStatus());
            }
            else if (MultiScreenIntentAction.SEND_REMOTE_DEVICE_INFO.equals(action))
            {
                mRemoteIP = intent.getStringExtra("remoteIP");
                mRemotePort = intent.getIntExtra("remotePort", VIME_CLIENT_DEFAULT_PORT);
                boolean isEnableFromClient = intent.getBooleanExtra("enableFromclient", false);

                mContext.removeStickyBroadcast(intent);
                if (isEnableFromClient)
                {
                    mIMultiScreenManagerVIme.enableVIMENotify();
                }
                LogTool.v("receive client IP" + mRemoteIP);
                LogTool.v("receive client port" + mRemotePort);
                LogTool.v("receive isEnableFromClient" + isEnableFromClient);
            }
            else if (MultiScreenIntentAction.ACTION_NOTIFY_NEW_PHONE_ACCESS.equals(action))
            {
                mRemoteIP = intent.getStringExtra("phoneIP");
                mIMultiScreenManagerVIme.closeKeyboard();

                LogTool.v("receive phoneIP" + mRemoteIP);
            }
            else if (MultiScreenIntentAction.VIME_SERVER_CLOSE_KEYBOARD.equals(action))
            {
                mIMultiScreenManagerVIme.closeKeyboard();
            }
            else if (MultiScreenIntentAction.VIME_ABNORMAL_START.equals(action))
            {
                LogTool.e("abnormal start vime");
                mIMultiScreenManagerVIme.closeKeyboard();
                mIMultiScreenManagerVIme.switchToDefaultIME();
            }

        }

    };

    /**
     * Start notify status of virtual IME <br>
     * CN: 停止虚拟输入法状态通知
     */
    public void startReport()
    {
        mObserver.setVImeStatus(VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INIT);
        IntentFilter filter = new IntentFilter();
        filter.addAction(MultiScreenIntentAction.CHECK_VIME_STATUS);
        filter.addAction(MultiScreenIntentAction.SEND_REMOTE_DEVICE_INFO);
        filter.addAction(MultiScreenIntentAction.ACTION_NOTIFY_NEW_PHONE_ACCESS);
        filter.addAction(MultiScreenIntentAction.VIME_SERVER_CLOSE_KEYBOARD);
        filter.addAction(MultiScreenIntentAction.VIME_ABNORMAL_START);
        mContext.registerReceiver(mVImeReceiver, filter);
    }

    /**
     * Stop notify status of virtual IME <br>
     * CN: 停止虚拟输入法状态通知
     */
    public void stopReport()
    {
        mContext.unregisterReceiver(mVImeReceiver);
    }

    /**
     * Broadcast current Virtual IME status to MultiScreen Service <br>
     * 广播virtual IME的状态给多屏服务
     */
    public void reportVIMEStatus(String vimeStatus)
    {
        Intent statusIntent = new Intent();
        statusIntent.setAction(vimeStatus);
        mContext.sendBroadcast(statusIntent);
    }

    /**
     * Status of Virtual IME response to MultiScreen service'check <br>
     * CN: 回应多屏服务查询虚拟输入法状态
     * @param status current status of virtual IME <br>
     *        CN:虚拟输入法当期状态
     */
    public void responseCheck(VImeStatusDefine.VimeStatus status)
    {
        mObserver.setVImeStatus(status);
        switch (status)
        {
            case VIME_SERVER_STATUS_INPUT:
                reportVIMEStatus(MultiScreenIntentAction.VIME_SWITCH_TO_INPUT);
                break;

            case VIME_SERVER_STATUS_READY:
                reportVIMEStatus(MultiScreenIntentAction.VIME_SWITCH_TO_READY);

            case VIME_SERVER_STATUS_INIT:

                break;

            case VIME_SERVER_STATUS_DEINIT:
                reportVIMEStatus(MultiScreenIntentAction.VIME_SWITCH_TO_DEINIT);
                break;

            default:
                break;
        }
    }

    /**
     * @deprecated
     * @return
     */
    public Context getContext()
    {
        return mContext;
    }

    /**
     * Set the context that the VImeStatReport rely on. <br>
     * 设置VImeStatReport运行所依赖的context。
     * @param context
     */
    public void setContext(Context context)
    {
        this.mContext = context;
    }

    /**
     * Get the client device's IP which virtual IME to connect. <br>
     * CN:获得虚拟输入法所要连接的客户端的IP。
     * @return the connected device's IP. <br>
     *         CN:所要连接的设备的IP。
     */
    public String getRemoteIP()
    {
        return mRemoteIP;
    }

    /**
     * Set the client device's IP which virtual IME to connect.<br>
     * CN:设置虚拟输入法连接的客户端的IP地址。
     * @param remoteIP the connected device's IP .<br>
     *        CN:所要连接的设备的IP。
     */
    public void setRemoteIP(String remoteIP)
    {
        this.mRemoteIP = remoteIP;
    }

    /**
     * Get the client device's port which virtual IME to connect. <br>
     * CN:获得虚拟输入法所要连接的客户端的Port。
     * @return the connected device's port. <br>
     *         CN:所要连接的设备的Port
     */
    public int getRemotePort()
    {
        return mRemotePort;
    }

    /**
     * Set the client device's IP which virtual IME to connect<br>
     * CN:设置虚拟输入法连接的客户端的IP地址
     * @param remoteIP the connected device's port. <br>
     *        CN:所要连接的设备的port。
     */
    public void setRemotePort(int remotePort)
    {
        this.mRemotePort = remotePort;
    }

}
