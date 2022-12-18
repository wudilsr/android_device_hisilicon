package com.hisilicon.miracast.util;

import android.content.Context;
import android.widget.Toast;

public class ToastUtil
{
    public static final int TOAST_DEFAULT_DURATION = 1000;

    public static void showToast(Context context, int msg)
    {
        showToast(context, context.getString(msg));
    }

    public static void showToast(Context context, int msg, int duration)
    {
        showToast(context, context.getString(msg), duration);
    }

    public static void showToast(Context context, String msg)
    {
        Toast.makeText(context, msg, TOAST_DEFAULT_DURATION).show();
    }

    public static void showToast(Context context, String msg, int duration)
    {
        Toast.makeText(context, msg, duration).show();
    }
}
