package com.hisilicon.multiscreen.mirror;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.ViewFlipper;

public class MirrorViewFlipper extends ViewFlipper
{

    public MirrorViewFlipper(Context context)
    {
        super(context);
    }

    public MirrorViewFlipper(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }

    @Override
    protected void onDetachedFromWindow()
    {
        try
        {
            super.onDetachedFromWindow();
        }
        catch (IllegalArgumentException e)
        {
            stopFlipping();
        }

    }

}
