package com.hisilicon.android.videoplayer.util;

import com.hisilicon.android.videoplayer.R;

import android.content.Context;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;


public class MyToast extends Toast {

       private MyToast(Context context) {
               super(context);
       }

       private static MyToast mToast;

       public static MyToast getInstance(Context context, String res) {
               LinearLayout layout = (LinearLayout) LayoutInflater.from(context)
                               .inflate(R.layout.toast_text, null);
               TextView toast_text = (TextView) layout.findViewById(R.id.no_file_id);
               if (mToast == null) {
                       mToast = new MyToast(context);
                       toast_text.setText(res);
                       mToast.setDuration(Toast.LENGTH_SHORT);
                       mToast.setGravity(Gravity.CENTER_VERTICAL, 0, 0);
                       mToast.setView(layout);
                       mToast.show();
               } else {
                       toast_text.setText(res);
                       mToast.setView(layout);
                       mToast.show();
               }
               return mToast;
       }
}
