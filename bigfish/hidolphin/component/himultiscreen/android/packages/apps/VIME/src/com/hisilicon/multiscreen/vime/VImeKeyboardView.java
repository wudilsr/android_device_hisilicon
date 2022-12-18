package com.hisilicon.multiscreen.vime;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

import android.content.Context;
import android.inputmethodservice.Keyboard;
import android.inputmethodservice.KeyboardView;
import android.inputmethodservice.Keyboard.Key;
import android.util.AttributeSet;
import android.view.MotionEvent;

/**
 * The class is the keyboardView's implementation of virtual IME. <br>
 * CN:该类是虚拟输入法键盘视图的实现。
 */
public class VImeKeyboardView extends KeyboardView
{

    static final int KEYCODE_OPTIONS = -100;

    public VImeKeyboardView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }

    public VImeKeyboardView(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
    }

    @Override
    public boolean onTouchEvent(MotionEvent me)
    {
        LogTool.v("on Touch Event");
        return true;
    }

    @Override
    protected boolean onLongPress(Key key)
    {
        if (key.codes[0] == Keyboard.KEYCODE_CANCEL)
        {
            LogTool.v(" getOnKeyboardActionListener()");
            getOnKeyboardActionListener().onKey(KEYCODE_OPTIONS, null);
            return true;
        }
        else
        {
            LogTool.v("super.onLongPress(key)");
            return super.onLongPress(key);
        }
    }

}
