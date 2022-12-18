package com.hisilicon.dlna.player;

import android.widget.SeekBar;
import android.view.MotionEvent;
import android.util.AttributeSet;
import android.content.Context;
import android.view.KeyEvent;

public class NewSeekBar extends SeekBar
{
    private boolean canMove;

    public NewSeekBar(Context context)
    {
        super(context);
    }

    public NewSeekBar(Context context, AttributeSet attrs)
    {
        super(context, attrs, android.R.attr.seekBarStyle);
    }

    public NewSeekBar(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
    }

    public void setCanMove(boolean canMove)
    {
        this.canMove = canMove;
    }

    public boolean onTouchEvent(MotionEvent event)
    {
        if (canMove)
        {
            return super.onTouchEvent(event);
        }
        else
        {
            return false;
        }
    }

    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT || keyCode == KeyEvent.KEYCODE_DPAD_RIGHT)
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
