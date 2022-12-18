package com.explorer.common;

import android.app.AlertDialog;
import android.content.Context;
import android.view.KeyEvent;

public class NewCreateDialog extends AlertDialog {

	public NewCreateDialog(Context context) {
		super(context);
	}

	public boolean onKeyDown(int keyCode, KeyEvent event) {
		switch (keyCode) {
		case KeyEvent.KEYCODE_DPAD_LEFT:
			getButton(BUTTON_POSITIVE).requestFocus();
			return true;

		case KeyEvent.KEYCODE_DPAD_RIGHT:
			getButton(BUTTON_NEGATIVE).requestFocus();
			return true;
		default:
			break;
		}

		return super.onKeyDown(keyCode, event);
	}

}
