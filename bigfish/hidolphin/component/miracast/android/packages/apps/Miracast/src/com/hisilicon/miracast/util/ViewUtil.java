package com.hisilicon.miracast.util;

import android.view.View;

public class ViewUtil
{
    public static void showView(View view)
    {
        view.setVisibility(View.VISIBLE);
    }

    public static void hideView(View view)
    {
        view.setVisibility(View.INVISIBLE);
    }

    public static void showView(View view, boolean isShown)
    {
        if (isShown)
        {
            showView(view);
        }
        else
        {
            hideView(view);
        }
    }

    public static void enableView(View view)
    {
        view.setEnabled(true);
    }

    public static void disableView(View view)
    {
        view.setEnabled(false);
    }

    public static void enableView(View view, boolean isEnabled)
    {
        if (isEnabled)
        {
            enableView(view);
        }
        else
        {
            disableView(view);
        }
    }
}
