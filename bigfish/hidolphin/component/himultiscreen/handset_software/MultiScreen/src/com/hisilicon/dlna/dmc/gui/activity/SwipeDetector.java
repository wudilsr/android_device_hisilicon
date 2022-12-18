package com.hisilicon.dlna.dmc.gui.activity;

import android.view.MotionEvent;
import android.view.View;

import com.hisilicon.dlna.dmc.processor.interfaces.SwipeCallback;

public class SwipeDetector implements View.OnTouchListener {
	private SwipeCallback callback;
	private static final int MIN_DISTANCE = 100;
	private static final int DOWN_TIME = 700;
	private float downX, upX;
	private boolean enabled = true;

	public SwipeDetector(SwipeCallback callback) {
		this.callback = callback;
	}

	public void setEnable(boolean enabled) {
		this.enabled = enabled;
	}

	public boolean isEnabled() {
		return enabled;
	}

	public boolean onTouch(View v, MotionEvent event) {
		switch (event.getAction()) {
		case MotionEvent.ACTION_DOWN: {
			downX = event.getX();
			return true;
		}
		case MotionEvent.ACTION_UP:
			upX = event.getX();

			float deltaX = downX - upX;
			if (event.getEventTime() - event.getDownTime() < DOWN_TIME) {

				if (Math.abs(deltaX) > MIN_DISTANCE) {
					if (deltaX < 0) {
						this.onLeftToRightSwipe();
					} else if (deltaX > 0) {
						this.onRightToLeftSwipe();
					}
				} else {
					this.onTap();
				}
			}
			return true;
		}
		return false;
	}

	private void onRightToLeftSwipe() {
		if (enabled)
			callback.swipeToNext();
	}

	private void onLeftToRightSwipe() {
		if (enabled)
			callback.swipeToPrevious();
	}

	private void onTap() {
		if (enabled)
			callback.onTap();
	}
}