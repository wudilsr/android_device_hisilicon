package com.hisilicon.dlna.dmc.processor.impl;

import android.graphics.Bitmap;
import android.widget.ImageView;

import com.hisilicon.dlna.dmc.processor.interfaces.ImageCallback;

public class ImageCallbackImpl implements ImageCallback {

	private ImageView mImageView;
	private String id;

	public ImageCallbackImpl(ImageView imageView) {
		mImageView = imageView;
	}

	public ImageCallbackImpl(ImageView imageView, String id) {
		mImageView = imageView;
		this.id = id;
	}

	@Override
	public void imageLoaded(Bitmap bitmap, String imageLink) {

		if(null != mImageView && null != bitmap && !bitmap.isRecycled() && null != imageLink && imageLink.equals(mImageView.getTag()))
		{
//			if(id!=null)
//				PictureData.addPicture(id, bitmap);
			mImageView.setImageBitmap(bitmap);
		}
	}

}
