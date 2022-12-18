package com.hisilicon.multiscreen.mybox;

import android.content.Context;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.widget.Gallery;

public class GuideGallery extends Gallery {
	/**
	 * Constructor.
	 * 
	 * @param context
	 * @param attrs
	 */
	public GuideGallery(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	@Override
	public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX,
			float velocityY) {
		if (isScrollingLeft(e1, e2)) {
			return onKeyLeft();
		} else {
			return onKeyRight();
		}
	}
	
	public boolean isScrollingLeft(MotionEvent e1, MotionEvent e2) {
		return e2.getX() > e1.getX();
	}
	
	public boolean onKeyLeft() {
		return onKeyDown(KeyEvent.KEYCODE_DPAD_LEFT, null);
	}
	
	public boolean onKeyRight() {
		return onKeyDown(KeyEvent.KEYCODE_DPAD_RIGHT, null);
	}
}
