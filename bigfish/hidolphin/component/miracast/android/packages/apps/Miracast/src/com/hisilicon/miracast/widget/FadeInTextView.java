package com.hisilicon.miracast.widget;

import android.content.Context;
import android.util.AttributeSet;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.TextView;

import com.hisilicon.miracast.R;

public class FadeInTextView extends TextView
{
    private Animation mFadeInAnim;

    public FadeInTextView(Context context)
    {
        super(context);
        init(context);
    }

    public FadeInTextView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
        init(context);
    }

    public FadeInTextView(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
        init(context);
    }

    private void init(Context context)
    {
        mFadeInAnim = AnimationUtils.loadAnimation(context, R.anim.fade_in);
    }

    @Override
    public void setText(CharSequence text, BufferType type)
    {
        if (!getText().equals(text))
        {
            if (mFadeInAnim != null)
            {
                startAnimation(mFadeInAnim);
            }
        }

        super.setText(text, type);
    }
}
