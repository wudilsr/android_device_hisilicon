/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.ahplayer;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.view.KeyEvent;

public class ahplayerMessageBox {

    public static void show(Context context, String title, String msg) {
        new AlertDialog.Builder(context)
        .setMessage(msg)
        .setTitle(title)
        .setCancelable(true)
        .setNeutralButton(android.R.string.ok,
           new DialogInterface.OnClickListener() {
           public void onClick(DialogInterface dialog, int whichButton){}
           })
        .show();
    }

    public static void show(Context context, String title, String msg,
            DialogInterface.OnClickListener listener)
    {
        new AlertDialog.Builder(context).setMessage(msg).setTitle(title)
                .setCancelable(false)
                .setNeutralButton(android.R.string.ok, listener).show()
                .setOnKeyListener(new DialogInterface.OnKeyListener()
                {
                    @Override
                    public boolean onKey(DialogInterface dialog, int keyCode, KeyEvent event)
                    {
                        // TODO Auto-generated method stub
                        return true;
                    }
                });
    }
    public static void show(Context context, Exception ex) {
        show(context, "Error", ex.getMessage());
    }

}
