package com.hisilicon.multiscreen.widget;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.drawable.BitmapDrawable;
import android.util.AttributeSet;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;

import com.hisilicon.dlna.dmc.utility.Utility;

public class BottomLineImageView extends ImageView {
	private int tabCount = 3;
	private int position;
	private float offset;
	private float bottom_line_width;

	public BottomLineImageView(Context context) {
		super(context);
	}

	public BottomLineImageView(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	public BottomLineImageView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
	}

	@Override
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		
		Bitmap bitmap = ((BitmapDrawable) getDrawable()).getBitmap();
		bottom_line_width = bitmap.getWidth();

		offset = 1.0f * (Utility.getScreenWidth() / tabCount - bottom_line_width) / 2;

		Matrix matrix = new Matrix();
		matrix.postTranslate(offset * 2, 0);
		setImageMatrix(matrix);// 设置动画初始位置
	}
	
	public void initTabCount(int count) {
		tabCount = count;
	}
	
	public int getCurrentPosition() {
		return position;
	}

	public void translateToPosition(int arg0) {
		float one = offset * 2 + bottom_line_width ;//偏移量
		
		Animation animation = new TranslateAnimation(one * position, one * arg0, 0, 0);
		
		position = arg0;
		
		animation.setFillAfter(true);// True:图片停在动画结束位置
		animation.setDuration(300);
		startAnimation(animation);
	}
}
