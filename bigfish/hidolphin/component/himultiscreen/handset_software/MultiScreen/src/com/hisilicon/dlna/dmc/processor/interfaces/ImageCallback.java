package com.hisilicon.dlna.dmc.processor.interfaces;

import android.graphics.Bitmap;

public interface ImageCallback {

	public void imageLoaded(Bitmap bitmap, String imageLink);
}