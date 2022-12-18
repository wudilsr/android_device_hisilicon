package com.hisilicon.android.videoplayer.utility;

import android.view.View;

public class ViewTool
{
    public static void showView(View pView)
    {
        pView.setVisibility(View.VISIBLE);
    }

    public static void hideView(View pView)
    {
        pView.setVisibility(View.INVISIBLE);
    }

    public static void enableClick(View pView)
    {
        pView.setClickable(true);
    }

    public static void disableClick(View pView)
    {
        pView.setClickable(false);
    }

    public static boolean getClickable(View pView)
    {
        return pView.isClickable();
    }

    public static void enableFocus(View pView)
    {
        pView.setFocusable(true);
    }

    public static void disableFocus(View pView)
    {
        pView.setFocusable(false);
    }

    public static void requestFocus(View pView)
    {
        pView.requestFocus();
    }
}
