package com.hisilicon.multiscreen.mybox;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.RelativeLayout;

/**
 * CN:遥控器按键模式界面。
 */
public class RemoteKeyboardView extends RelativeLayout {

	/**
	 * CN:按键模式确认按钮。
	 */
	public Button mRemote_keyboard_ok;
	
	/**
	 * CN:按键模式向上按钮。
	 */
	public Button mRemote_keyboard_up;
	
	/**
	 * CN:按键模式向左按钮。
	 */
	public Button mRemote_keyboard_left;
	
	/**
	 * CN:按键模式向右按钮。
	 */
	public Button mRemote_keyboard_right;
	
	/**
	 * CN:按键模式向下按钮。
	 */
	public Button mRemote_keyboard_down;
	public Button mRemote_keyboard_btn;

	public RelativeLayout mRemote_keyboard_layout;

	/**
	 * context of this.
	 */
	private Context mContext;

	public RemoteKeyboardView(Context context) {
		super(context);
		mContext = context;

	}

	public RemoteKeyboardView(Context context, AttributeSet attrs) {
		super(context, attrs);
		this.mContext = context;
		initViews(context);

	}

	/**
	 * init view.
	 */
	public void initViews(Context context) {

		View view = LayoutInflater.from(mContext).inflate(
				R.layout.mybox_remote_keyboard, this);

		mRemote_keyboard_ok = (Button) view.findViewById(R.id.remote_keyboard_ok);
		mRemote_keyboard_up = (Button) view.findViewById(R.id.remote_keyboard_up);
		mRemote_keyboard_left = (Button) view.findViewById(R.id.remote_keyboard_left);
		mRemote_keyboard_right = (Button) view.findViewById(R.id.remote_keyboard_right);
		mRemote_keyboard_down = (Button) view.findViewById(R.id.remote_keyboard_down);
		mRemote_keyboard_layout = (RelativeLayout) view.findViewById(R.id.remote_keyboard_layout);
		mRemote_keyboard_btn = (Button) view.findViewById(R.id.remote_keyboard_btn);

	}

}
