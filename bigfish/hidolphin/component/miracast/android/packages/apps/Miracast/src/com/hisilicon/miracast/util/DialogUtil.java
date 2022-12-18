package com.hisilicon.miracast.util;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.view.WindowManager;

public class DialogUtil
{
    public static AlertDialog.Builder getCommonDialogBuilder(Context context, int titleId, int msgId)
    {
        return getCommonDialogBuilder(context, context.getString(titleId), context.getString(msgId));
    }

    public static AlertDialog.Builder getCommonDialogBuilder(Context context, String title,
        int msgId)
    {
        return getCommonDialogBuilder(context, title, context.getString(msgId));
    }

    public static AlertDialog.Builder getCommonDialogBuilder(Context context, int titleId,
        String msg)
    {
        return getCommonDialogBuilder(context, context.getString(titleId), msg);
    }

    public static AlertDialog.Builder getCommonDialogBuilder(Context context, String title,
        String msg)
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle(title);
        builder.setMessage(msg);
        return builder;
    }

    public static ProgressDialog getCommonProgressDialog(Context context, int titleId, int msgId)
    {
        return getCommonProgressDialog(context, context.getString(titleId),
            context.getString(msgId));
    }

    public static ProgressDialog getCommonProgressDialog(Context context, String title, int msgId)
    {
        return getCommonProgressDialog(context, title, context.getString(msgId));
    }

    public static ProgressDialog getCommonProgressDialog(Context context, int titleId, String msg)
    {
        return getCommonProgressDialog(context, context.getString(titleId), msg);
    }

    public static ProgressDialog getCommonProgressDialog(Context context, String title, String msg)
    {
        ProgressDialog dialog = new ProgressDialog(context);
        dialog.setTitle(title);
        dialog.setMessage(msg);
        return dialog;
    }

    public static void setDialogForService(Dialog dialog)
    {
        dialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
    }

    public static void showServiceDialog(Dialog dialog)
    {
        setDialogForService(dialog);
        dialog.show();
    }
}
