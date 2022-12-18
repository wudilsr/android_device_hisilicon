package com.explorer.common;

import android.content.Context;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.explorer.R;

public class FileMToast extends Toast {

	private FileMToast(Context context) {
		super(context);
	}

	private static FileMToast fileMToast;

	public static FileMToast getInstance(Context context, String res) {
		LinearLayout layout = (LinearLayout) LayoutInflater.from(context)
				.inflate(R.layout.toast_text, null);
		TextView toast_text = (TextView) layout.findViewById(R.id.no_file_id);
		if (fileMToast == null) {
			fileMToast = new FileMToast(context);
			toast_text.setText(res);
			fileMToast.setDuration(Toast.LENGTH_SHORT);
			fileMToast.setGravity(Gravity.CENTER_VERTICAL, 0, 0);
			fileMToast.setView(layout);
			fileMToast.show();
		} else {
			toast_text.setText(res);
			fileMToast.setView(layout);
			fileMToast.show();
		}
		return fileMToast;
	}
}
