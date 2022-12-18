package com.hisilicon.dlna.player;

import java.util.Timer;
import java.util.TimerTask;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

/**
 * @author gui_xiangbo <br>
 *         CN:计时器 <br>
 */
public class TimerManager
{
    public static final int SHOW_CHANNEL_ACTION = 0;
    public static final int SHOW_HOME_MENU_ACTION = 1;

    public static final int CHANNEL_VIEW_TIME_OUT = 5000;
    public static final int SETTING_VIEW_TIME_OUT = 5000;
    public static final int HOME_MENU_TIME_OUT = 5000;

    private static TimerManager mInstance;
    private Timer mTimer;
    private PlayerInterface mIPlay;

    private TimerManager()
    {
    }

    /**
     * 单例模式 获取时间管理对象的实例
     *
     * @return
     */
    public static TimerManager getInstance()
    {

        if (mInstance == null)
        {
            mInstance = new TimerManager();
        }
        return mInstance;
    }

    /**
     * 接受到消息后使用Handler对当前View进行更新
     */
    Handler handler = new Handler()
    {
        public void handleMessage(Message msg)
        {
            if (mIPlay != null)
            {
                Log.d("TimerManager", "-----hideView---");
                mIPlay.hideView();
            }
            super.handleMessage(msg);
        }
    };

    /**
     * 启动计时器
     *
     * @param aTimeLong
     * @param aTimerScheduleInterface
     */
    public void startTimer(int aTimeLong, PlayerInterface amMediaPlay)
    {
        mIPlay = amMediaPlay;
        if (mTimer == null)
        {
            mTimer = new Timer();
        }
        Log.e("TimerManager", "-----strat a schedule---");
        mTimer.schedule(new MyTimerTask(), aTimeLong);
    }

    /**
     * 停止计时器
     */
    public void closeTimer()
    {

        if (mTimer != null)
        {
            mTimer.cancel();
            mTimer = null;
        }
        mIPlay = null;
    }

    /**
     * Reset the timer
     * @param aTimeLong
     */
    public void resetTimer(int aTimeLong)
    {
        if (mTimer != null)
        {
            mTimer.cancel();
            mTimer = null;
        }

        if (mTimer == null)
        {
            mTimer = new Timer();
        }
        mTimer.schedule(new MyTimerTask(), aTimeLong);
    }

    /**
     * 定时的给Handler发送更新View的消息
     * @author gui_xiangbo
     */
    public class MyTimerTask extends TimerTask
    {
        public void run()
        {
            Message message = new Message();
            // message.what = mActionType;
            handler.sendMessage(message);
            if (mTimer != null)
            {
                mTimer.cancel();
                mTimer = null;
            }
        }
    };
}
