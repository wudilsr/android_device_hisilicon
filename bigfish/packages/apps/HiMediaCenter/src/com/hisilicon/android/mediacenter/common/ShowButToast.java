package com.hisilicon.android.mediacenter.common;

import android.content.Context;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.android.mediacenter.R;

public class ShowButToast extends Toast {

	private ShowButToast(Context context) {
		super(context);
	}

	private static ShowButToast fileMToast;

	public static ShowButToast getInstance(Context context, String res) {
		LinearLayout layout = (LinearLayout) LayoutInflater.from(context)
				.inflate(R.layout.toast_text, null);
		TextView toast_text = (TextView) layout.findViewById(R.id.no_file_id);
		toast_text.setTextSize(18);
		if (fileMToast == null) {
			fileMToast = new ShowButToast(context);
			toast_text.setText(res);
			fileMToast.setDuration(Toast.LENGTH_SHORT);
			fileMToast.setGravity(Gravity.CENTER | Gravity.RIGHT, 0, -195);
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
