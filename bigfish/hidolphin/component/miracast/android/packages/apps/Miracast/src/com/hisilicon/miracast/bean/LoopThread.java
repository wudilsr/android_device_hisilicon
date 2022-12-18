package com.hisilicon.miracast.bean;

import android.os.Looper;

import com.hisilicon.miracast.util.LogUtil;

public class LoopThread extends Thread
{
    private Looper mLooper = null;
    private final Object mLock = new Object();

    public LoopThread(String name)
    {
        super(name);
        setPriority(Thread.MIN_PRIORITY);
        start();

        synchronized (mLock)
        {
            while (mLooper == null)
            {
                try
                {
                    mLock.wait();
                }
                catch (InterruptedException e)
                {
                    LogUtil.e(e.toString());
                }
            }
        }
    }

    @Override
    public void run()
    {
        synchronized (mLock)
        {
            Looper.prepare();
            mLooper = Looper.myLooper();
            mLock.notifyAll();
        }
        Looper.loop();
    }

    public Looper getLooper()
    {
        return mLooper;
    }

    public void quit()
    {
        if (mLooper != null)
        {
            mLooper.quit();
            mLooper = null;
        }
    }
}
