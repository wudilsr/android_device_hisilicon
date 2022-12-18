package com.hisilicon.multiscreen.mybox;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;
import java.util.Timer;
import java.util.TimerTask;

import com.hisilicon.multiscreen.mirror.MirrorView;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * FPS control service. control fps of mirror.<br>
 * CN:控制服务，负责保活和控制帧率。
 */
public class MirrorfpsControl
{
    private MirrorView mMirrorView = null;

    private long LOOP_TIME = 6 * 1000;

    private Timer mMirrorFpsControlTimer = null;

    private MirrorFpsControlTask mMirrorFpsControlTask = null;

    DatagramSocket socket = null;

    InetAddress mHostAddress = null;

    ByteBuffer mFpsData = null;

    DatagramPacket mPacket = null;

    private MultiScreenControlService mMultiScreenControlService = null;

    /**
     * Construction of mirror fpg control.<br>
     * CN:构造传屏帧率控制。
     */
    public MirrorfpsControl()
    {
        mMultiScreenControlService = MultiScreenControlService.getInstance();
    }

    /**
     * start service.<br>
     * 开启控制服务.
     */
    public void start(MirrorView mirrorView)
    {
        mMirrorView = mirrorView;
        if (mMirrorFpsControlTimer == null)
        {
            mMirrorFpsControlTask = new MirrorFpsControlTask();
            mMirrorFpsControlTimer = new Timer();
            mMirrorFpsControlTimer.schedule(mMirrorFpsControlTask, 0, LOOP_TIME);
        }
    }

    /**
     * stop service.<br>
     * 关闭控制服务.
     */
    public void stop()
    {
        if (mMirrorFpsControlTimer != null)
        {
            mMirrorFpsControlTimer.cancel();
            mMirrorFpsControlTimer = null;
        }
    }

    class MirrorFpsControlTask extends TimerTask
    {
        /**
         * FPS control of mirror.<br>
         * CN:传屏帧率控制。
         */
        private int mFps = 10;

        @Override
        public void run()
        {

            // 通过调用JNI返回帧率统计结果，把此帧率发送给STB端
            // get the FPS from JNI , send the FPS to STB
            if (mMirrorView == null)
            {
                LogTool.e("MirrorView is null.");
                return;
            }
            else
            {
                mFps = mMirrorView.getdecodefps();
            }

            if ((mFps > 20) || (mFps < 0))
            {
                return;
            }

            mMultiScreenControlService.setMirrorParameter(("fps=" + mFps), 1);
        }
    }

}
