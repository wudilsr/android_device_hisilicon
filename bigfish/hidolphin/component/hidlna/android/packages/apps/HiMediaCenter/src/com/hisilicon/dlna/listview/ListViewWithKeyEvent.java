package com.hisilicon.dlna.listview;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.ListView;

public class ListViewWithKeyEvent extends ListView
{
    private static final String TAG = "ListViewWithKeyEvent";
    private boolean canListViewMove = false;

    public void setCanMove(boolean canListViewMove)
    {
        this.canListViewMove = canListViewMove;
    }

    private List<ListViewKeyListener> keyListeners = new ArrayList<ListViewKeyListener>();

    public ListViewWithKeyEvent(Context context)
    {
        super(context);
    }

    public ListViewWithKeyEvent(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }

    public ListViewWithKeyEvent(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
    }

    public void addKeyEventListener(ListViewKeyListener listener)
    {
        keyListeners.add(listener);
    }

    public void removeKeyEventListener(ListViewKeyListener listener)
    {
        keyListeners.remove(listener);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        Log.d(TAG, "onKeyDown keyCode=" + keyCode);
        if (keyCode == KeyEvent.KEYCODE_DPAD_UP)
        {
            if (!canListViewMove)
            {
                return true;
            }
        }
        if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN)
        {
            if (!canListViewMove)
            {
                return true;
            }
        }
        for (ListViewKeyListener listener : keyListeners)
        {
            listener.onListViewKeyDown(keyCode, event);
        }
        if (keyCode == KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE)
        {
            // shield the play button
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onKeyMultiple(int keyCode, int repeatCount, KeyEvent event)
    {
        Log.d(TAG, "onKeyMultiple");
        for (ListViewKeyListener listener : keyListeners)
        {
            listener.onListViewKeyMultiple(keyCode, repeatCount, event);
        }
        return super.onKeyMultiple(keyCode, repeatCount, event);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
        Log.d(TAG, "onKeyUp");
        for (ListViewKeyListener listener : keyListeners)
        {
            listener.onListViewKeyUp(keyCode, event);
        }
        return super.onKeyUp(keyCode, event);
    }

}
