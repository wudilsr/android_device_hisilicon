package com.hisilicon.hardware.hdmi;

import java.util.ArrayList;
import java.util.HashMap;

import android.app.AlertDialog;
import android.content.Context;
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.View;
import android.view.View.OnKeyListener;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;
import android.widget.ListView;
import android.widget.TextView;

import com.hisilicon.hardwaretest.R;

public class HDMITestDialog {

    private Context context;
    private AlertDialog dialog;
    private ListAdapter adapter;

    public HDMITestDialog(Context context) {
        this.context = context;
        this.adapter = new ListAdapter(context);
    }

    public AlertDialog showMenuDialog(OnKeyListener listener) {
        View view = View.inflate(context, R.layout.hdmi_test_dialog, null);
        ListView listView = (ListView) view.findViewById(R.id.list_view);
        listView.setAdapter(adapter);
        listView.setOnKeyListener(listener);

        AlertDialog.Builder builder = new AlertDialog.Builder(context,
                R.style.DialogStyle);
        builder.setView(view);
        dialog = builder.create();
        dialog.getWindow()
                .setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
        dialog.show();

        // set dialog size and position.
        WindowManager.LayoutParams params = dialog.getWindow().getAttributes();
        WindowManager manager = (WindowManager) context
                .getSystemService(Context.WINDOW_SERVICE);
        DisplayMetrics metrics = new DisplayMetrics();
        manager.getDefaultDisplay().getMetrics(metrics);
        params.width = (int) (metrics.widthPixels * 0.35);
        params.height = (int) (metrics.heightPixels * 0.4);
        params.x = 600;
        params.y = -400;
        params.alpha = 0.9f;
        dialog.getWindow().setAttributes(params);
        return dialog;
    }

    public AlertDialog showMessageDialog(String title, String message) {
        TextView textView = new TextView(context);
        textView.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,
                LayoutParams.MATCH_PARENT));
        textView.setGravity(Gravity.CENTER_VERTICAL);
        textView.setTextSize(15);
        textView.setText(message);
        textView.setPadding(20, 20, 0, 20);

        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle(title);
        builder.setView(textView);
        builder.setNegativeButton("OK", null);

        AlertDialog dialog = builder.create();
        dialog.getWindow()
                .setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
        dialog.setCanceledOnTouchOutside(false);
        dialog.setCancelable(false);
        dialog.show();

        WindowManager.LayoutParams params = dialog.getWindow().getAttributes();
        WindowManager manager = (WindowManager) context
                .getSystemService(Context.WINDOW_SERVICE);
        DisplayMetrics metrics = new DisplayMetrics();
        manager.getDefaultDisplay().getMetrics(metrics);
        params.width = (int) (metrics.widthPixels * 0.5);
        dialog.getWindow().setAttributes(params);
        return dialog;
    }

    public void dismiss() {
        if (null != dialog)
            dialog.dismiss();
    }

    public void refreshView(ArrayList<HashMap<String, String>> list) {
        adapter.refreshView(list);
    }

}