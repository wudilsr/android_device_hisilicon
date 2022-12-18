package com.hisilicon.android.videoplayer.view;

import com.hisilicon.android.videoplayer.R;
import com.hisilicon.android.videoplayer.util.Common;

import android.content.Context;
import android.view.MotionEvent;
import android.view.KeyEvent;
import android.util.AttributeSet;
import android.util.Log;
import android.widget.SeekBar;


public class MySeekBar extends SeekBar
{
    private boolean canMove;

    public MySeekBar(Context context)
    {
        super(context);
    }

    public MySeekBar(Context context, AttributeSet attrs)
    {
        super(context, attrs, android.R.attr.seekBarStyle);
    }

    public MySeekBar(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
    }

    public void setCanMove(boolean canMove)
    {
        this.canMove = canMove;
    }

    public boolean onTouchEvent(MotionEvent event)
    {
        return super.onTouchEvent(event);
    }
    public synchronized void setProgress(int progress)
    {
        super.setProgress(progress);
        invalidate();
    }
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if ((keyCode == KeyEvent.KEYCODE_DPAD_LEFT) || (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT))
        {
            if (canMove)
            {
                return super.onKeyDown(keyCode, event);
            }
            else
            {
                return false;
            }
        }

        return super.onKeyDown(keyCode, event);
    }
}
