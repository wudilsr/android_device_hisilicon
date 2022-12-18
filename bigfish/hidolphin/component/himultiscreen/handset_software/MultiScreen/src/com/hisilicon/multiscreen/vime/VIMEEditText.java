package com.hisilicon.multiscreen.vime;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.EditText;

/**
 * VIME EditText.<br>
 * CN:可编辑VIME文本框。
 */
public class VIMEEditText extends EditText
{
    private EditTextWatcher mEtWatcher = null;

    public VIMEEditText(Context context)
    {
        super(context);
    }

    public VIMEEditText(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }

    public VIMEEditText(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
    }

    /**
     * Add watcher of edit text.<br>
     * CN:添加文本框观察者。
     * @param watcher
     */
    public void addWatcher(EditTextWatcher watcher)
    {
        mEtWatcher = watcher;
    }

    @Override
    public void onTextChanged(CharSequence text, int start, int lengthBefore, int lengthAfter)
    {
        if (mEtWatcher != null)
        {
            mEtWatcher.onTextChanged(text, start, lengthBefore, lengthAfter);
        }
    }

    @Override
    protected void onSelectionChanged(int selStart, int selEnd)
    {
        if (mEtWatcher != null)
        {
            mEtWatcher.onSelectionChanged(selStart, selEnd);
        }
    }
}
