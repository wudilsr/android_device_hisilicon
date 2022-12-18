package com.hisilicon.multiscreen.mybox;

import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;

import com.hisilicon.multiscreen.mybox.interfaces.RemoteSwipeCallback;

/**
 * CN：滑动模式方向的回调类。
 */
public class RemoteSwipeDetector implements OnTouchListener {
	private RemoteSwipeCallback callback;

	/**
	 * CN：滑动的最小距离必须大于80。
	 */
	private static final int MIN_DISTANCE = 80;

	private static final int DOWN_TIME = 3000;

	private float downX, upX;

	private float downY, upY;

	private boolean enabled = true;

	public RemoteSwipeDetector(RemoteSwipeCallback callback) {
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
			downY = event.getY();
			this.onDownPosition(downX, downY);
			return true;
		}
		case MotionEvent.ACTION_UP:
			upX = event.getX();
			upY = event.getY();

			float deltaX = downX - upX;
			float deltaY = downY - upY;
			if (event.getEventTime() - event.getDownTime() < DOWN_TIME) {

				if (Math.abs(deltaX) > MIN_DISTANCE && Math.abs(deltaX) > Math.abs(deltaY)) {
					if (deltaX < 0) {
						this.onLeftToRightSwipe();
					} else if (deltaX > 0) {
						this.onRightToLeftSwipe();
					}
				} else if (Math.abs(deltaY) > MIN_DISTANCE) {
					if (deltaY < 0) {
						this.onUpToDownSwipe();
					} else if (deltaY > 0) {
						this.onDownToUpSwipe();
					}
				} else {
					this.onTap();
				}
			}

			this.onUpPosition(upX, upY);
			return true;
		}
		return false;
	}

	/**
	 * CN：滑动模式点击按下的位置。
	 */
	private void onDownPosition(float x, float y) {
		if (enabled)
			callback.downPosition(x, y);
	}

	/**
	 * CN：滑动模式点击离开的位置。
	 */
	private void onUpPosition(float x, float y) {
		if (enabled)
			callback.upPosition(x, y);
	}

	/**
	 * CN：滑动模式右向左滑动。
	 */
	private void onRightToLeftSwipe() {
		if (enabled)
			callback.swipeRightToLeft();
	}

	/**
	 * CN：滑动模式左向右滑动。
	 */
	private void onLeftToRightSwipe() {
		if (enabled)
			callback.swipeLeftToRight();
	}

	/**
	 * CN：滑动模式上向下滑动。
	 */
	private void onUpToDownSwipe() {
		if (enabled)
			callback.swipeUpToDown();
	}

	/**
	 * CN：滑动模式下向上滑动。
	 */
	private void onDownToUpSwipe() {
		if (enabled)
			callback.swipeDownToUp();
	}

	/**
	 * CN：滑动模式确认点击的位置。
	 */
	private void onTap() {
		if (enabled)
			callback.onTap();
	}
}
