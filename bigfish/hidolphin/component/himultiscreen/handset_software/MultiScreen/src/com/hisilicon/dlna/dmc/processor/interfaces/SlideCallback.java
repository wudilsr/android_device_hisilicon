package com.hisilicon.dlna.dmc.processor.interfaces;

import android.view.MotionEvent;
import android.view.View;

public interface SlideCallback {
	boolean onTouch(View view, MotionEvent event);
	void deltaY(int delta);
	void slideUpToDown();
	void slideDownToUp();
	void onTap();
}
