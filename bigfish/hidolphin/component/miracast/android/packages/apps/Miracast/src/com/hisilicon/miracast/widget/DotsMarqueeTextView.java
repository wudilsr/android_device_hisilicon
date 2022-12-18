package com.hisilicon.miracast.widget;

import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.TextView;

import com.hisilicon.miracast.util.LogUtil;

public class DotsMarqueeTextView extends TextView
{
    private String[] mDots =
    { ".", "..", "..." };
    private int mIndex = -1;

    private Timer mTimer;

    private final Object mLock = new Object();

    public DotsMarqueeTextView(Context context)
    {
        super(context);
    }

    public DotsMarqueeTextView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }

    public DotsMarqueeTextView(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
    }

    @Override
    public void invalidate()
    {
        super.invalidate();

        int tempIndex = 0;
        if (mDots != null)
        {
            synchronized (mLock)
            {
                if ((mIndex >= 0) && (mIndex < 3))
                {
                    tempIndex = mIndex;
                }
            }
            setText(mDots[tempIndex]);
        }
    }

    public void startMarquee()
    {
        if (mTimer == null)
        {
            LogUtil.d("");
            mTimer = new Timer();
            TimerTask task = new TimerTask()
            {
                @Override
                public void run()
                {
                    synchronized (mLock)
                    {
                        mIndex++;
                        mIndex %= 3;
                    }

                    postInvalidate();
                }
            };

            // delay 1sec, period 0.7sec, it's empirical value
            mTimer.schedule(task, 1000, 700);
        }
    }

    public void stopMarquee()
    {
        if (mTimer != null)
        {
            LogUtil.d("");
            mTimer.cancel();
            mTimer = null;

            synchronized (mLock)
            {
                mIndex = -1;
            }
        }
    }
}
