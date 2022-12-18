package com.hisilicon.baidu.pcs.common;

import android.content.Context;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.baidu.pcs.R;

public class FileMToast extends Toast {

    private static FileMToast fileMToast;

    private FileMToast(Context context) {
        super(context);
    }

    public static FileMToast getInstance(Context context, int msgId) {
        return getInstance(context, context.getString(msgId));
    }

    public static FileMToast getInstance(Context context, String msg) {
        LinearLayout layout = (LinearLayout) LayoutInflater.from(context)
                .inflate(R.layout.view_toast, null);
        TextView toast_text = (TextView) layout.findViewById(R.id.no_file_id);
        toast_text.setTextColor(context.getResources().getColor(R.color.white));
        if (fileMToast == null) {
            fileMToast = new FileMToast(context);
            toast_text.setText(msg);
            fileMToast.setDuration(Toast.LENGTH_SHORT);
            fileMToast.setGravity(Gravity.CENTER_VERTICAL, 0, 0);
            fileMToast.setView(layout);
            fileMToast.show();
        } else {
            toast_text.setText(msg);
            fileMToast.setView(layout);
            fileMToast.show();
        }
        return fileMToast;
    }

}