package com.hisilicon.dlna.dmc.gui.customview;

import android.view.MotionEvent;
import android.view.View;

import com.hisilicon.dlna.dmc.processor.interfaces.SlideCallback;

public class SlideDetector implements View.OnTouchListener {
	private SlideCallback callback;
	private static final int MIN_DISTANCE = 100;
	private static final int DOWN_TIME = 700;
	private float downY, upY, moveY;
	private boolean enabled = true;
	
	public SlideDetector(SlideCallback callback) {
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
			downY = event.getY();;
			moveY = event.getY();
			break;
		}
		case MotionEvent.ACTION_MOVE: {
			final float preY = moveY;
			float nowY = event.getY();
			moveY = nowY;
			
			if(preY == 0)
				break;
			
			float deltaY = nowY - preY;
			this.onDeltaY((int) deltaY);
			break;
		}
		case MotionEvent.ACTION_UP:
			upY = event.getY();

			float deltaY = downY - upY;
			if (event.getEventTime() - event.getDownTime() < DOWN_TIME)
			{
				if (Math.abs(deltaY) > MIN_DISTANCE)
				{
					if (deltaY < 0)
					{
						this.onUpToDownSlide();
					}
					else if (deltaY > 0)
					{
						this.onDownToUpSlide();
					}
				}
				else
				{
					this.onTap();
				}
			}
			break;
		}
		
		return this.onSlideTouch(v, event);
	}
	
	private boolean onSlideTouch(View view, MotionEvent event) {
		if (enabled)
			return callback.onTouch(view, event);
		return true;
	}
	
	private void onDeltaY(int y) {
		if (enabled)
			callback.deltaY(y);
	}

	private void onDownToUpSlide() {
		if (enabled)
			callback.slideDownToUp();
	}

	private void onUpToDownSlide() {
		if (enabled)
			callback.slideUpToDown();
	}

	private void onTap() {
		if (enabled)
			callback.onTap();
	}
}