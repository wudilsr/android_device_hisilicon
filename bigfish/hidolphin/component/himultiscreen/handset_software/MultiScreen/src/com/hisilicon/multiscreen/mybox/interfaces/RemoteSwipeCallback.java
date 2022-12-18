package com.hisilicon.multiscreen.mybox.interfaces;

public interface RemoteSwipeCallback {
	void downPosition(float x, float y);
	void upPosition(float x, float y);
	void swipeRightToLeft();
	void swipeLeftToRight();
	void swipeUpToDown();
	void swipeDownToUp();
	void onTap();
}
