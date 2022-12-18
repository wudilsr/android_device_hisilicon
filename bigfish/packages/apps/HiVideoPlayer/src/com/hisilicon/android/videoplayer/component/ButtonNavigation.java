package com.hisilicon.android.videoplayer.component;

import android.content.Context;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;

import com.hisilicon.android.videoplayer.R;

public class ButtonNavigation extends Button
{
    private Context mContext;

    public ButtonNavigation(Context pContext)
    {
        super(pContext);
        mContext = pContext;
    }

    public ButtonNavigation(Context pContext, AttributeSet pAttrs)
    {
        super(pContext, pAttrs);
        mContext = pContext;
    }

    public ButtonNavigation(Context pContext, AttributeSet pAttrs, int pDefStyle)
    {
        super(pContext, pAttrs, pDefStyle);
        mContext = pContext;
    }

    @Override
    protected void onFocusChanged(boolean pFocused, int pDirection, Rect pPreviouslyFocusedRect)
    {
        if (pFocused)
        {
            if ((pDirection != FOCUS_LEFT) && (pDirection != FOCUS_RIGHT)
                && (pDirection != FOCUS_UP) && (pDirection != FOCUS_DOWN))
            {
                return;
            }

            Animation _AnimRollover = null;

            if ((pDirection == FOCUS_LEFT) || (pDirection == FOCUS_RIGHT))
            {
                _AnimRollover = AnimationUtils.loadAnimation(mContext, R.anim.rollover_horizontal);
            }
            else if ((pDirection == FOCUS_UP) || (pDirection == FOCUS_DOWN))
            {
                _AnimRollover = AnimationUtils.loadAnimation(mContext, R.anim.rollover_vertical);
            }

            _AnimRollover.setFillAfter(true);
            startAnimation(_AnimRollover);
        }

        super.onFocusChanged(pFocused, pDirection, pPreviouslyFocusedRect);
    }
}
