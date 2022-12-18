package com.hisilicon.multiscreen.widget;

import java.io.File;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.widget.ImageView;

import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.multiscreen.mybox.MyApp;
import com.hisilicon.multiscreen.mybox.R;

public class SlidePushView extends ImageView {
	private Bitmap originalBitmap;
//	private static Bitmap mask = null;

	public SlidePushView(Context context) {
		super(context);
	}

	public SlidePushView(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	public SlidePushView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
	}

	@Override
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
	}
	
	public void drawImageSlideView(Bitmap bitmap, int[] location, Rect frame) {
		try {
			System.out.println("The slidePushView-->01");
			originalBitmap = Bitmap.createBitmap(getWidth(), getHeight(), Config.ARGB_8888);
			System.out.println("The slidePushView-->02");
			Paint paint = new Paint();
			System.out.println("The slidePushView-->03");
			Canvas canvas = new Canvas(originalBitmap);
			System.out.println("The slidePushView-->04");
			Bitmap mask = null;
			if (mask == null || mask.isRecycled()){
				mask = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.mask);
				System.out.println("The slidePushView-->05");
//				mask = setWidthAndHeight(mask, getWidth(), getHeight());
			}
			System.out.println("The slidePushView-->1");
			canvas.drawBitmap(mask, 0, 0, paint);
			recycle(mask);
			int bitmapX = location[0];
			int bitmapY = location[1] - frame.top;
			if (bitmap != null && !bitmap.isRecycled())
				canvas.drawBitmap(bitmap, bitmapX, bitmapY, paint);
			recycle(bitmap);
			Bitmap rc_tv_small = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.rc_tv_small);
			int tv_smallX = (frame.right - frame.left) / 2 - rc_tv_small.getWidth() / 2;
			int tv_smallY = 20;
			canvas.drawBitmap(rc_tv_small, tv_smallX, tv_smallY, paint);
			recycle(rc_tv_small);

			Bitmap dlna_slide_big_uparrow = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.dlna_slide_big_uparrow);
			int big_uparrowX = bitmapX + (bitmap.getWidth() - dlna_slide_big_uparrow.getWidth()) / 2;
			int big_uparrowY = bitmapY - dlna_slide_big_uparrow.getHeight();
			canvas.drawBitmap(dlna_slide_big_uparrow, big_uparrowX, big_uparrowY, paint);
			recycle(dlna_slide_big_uparrow);

			Bitmap dlna_slide_pushguide = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.dlna_slide_pushguide);

			int pushguideX = bitmapX + bitmap.getWidth() + 5;
			int pushguideY = bitmapY + (bitmap.getHeight() - dlna_slide_pushguide.getHeight()) / 2;
			canvas.drawBitmap(dlna_slide_pushguide, pushguideX, pushguideY, paint);
			recycle(dlna_slide_pushguide);

			Bitmap dlna_slide_small_uparrow = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.dlna_slide_small_uparrow);

			int small_uparrowX = bitmapX + bitmap.getWidth();
			int small_uparrowY = pushguideY - dlna_slide_small_uparrow.getHeight();
			canvas.drawBitmap(dlna_slide_small_uparrow, small_uparrowX, small_uparrowY, paint);
			recycle(dlna_slide_small_uparrow);

			setImageBitmap(originalBitmap);
		} catch (Exception ex) {
		} catch (Error er) {
			System.gc();
		}
	}

	private Bitmap setWidthAndHeight(Bitmap bt, int screenWidth, int screenHeight){
		if(bt==null)
			return null;
		int width = bt.getWidth();
		int height = bt.getHeight();
		// 设置想要的大小
		//        int newWidth = 500;
		//        int newHeight = 400;

		// 计算缩放比例
		float scaleWidth = ((float) screenWidth) / width;
		float scaleHeight = ((float) screenHeight) / height;

		// 取得想要缩放的matrix参数
		Matrix matrix = new Matrix();
		matrix.postScale(scaleWidth, scaleHeight);

		// 得到新的图片
		return Bitmap.createBitmap(bt, 0, 0, width, height, matrix, true);
	}

	public void drawVideoSlideView(Bitmap bitmap, int[] location, Rect frame) {
		try {
			originalBitmap = Bitmap.createBitmap(getWidth(), getHeight(), Config.ARGB_8888);

			Paint paint = new Paint();

			Canvas canvas = new Canvas(originalBitmap);
			Bitmap mask = null;
			if (mask == null || mask.isRecycled()){
				mask = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.mask);
//				mask = setWidthAndHeight(mask, getWidth(), getHeight());
			}
			canvas.drawBitmap(mask, 0, 0, paint);
			recycle(mask);
			int bitmapX = location[0];
			int bitmapY = location[1] - frame.top;
			if (bitmap != null && !bitmap.isRecycled())
				canvas.drawBitmap(bitmap, bitmapX, bitmapY, paint);
			recycle(bitmap);

			Bitmap rc_tv_small = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.rc_tv_small);

			int tv_smallX = (frame.right - frame.left) / 2 - rc_tv_small.getWidth() / 2;
			int tv_smallY = 20;
			canvas.drawBitmap(rc_tv_small, tv_smallX, tv_smallY, paint);
			recycle(rc_tv_small);

			Bitmap dlna_slide_big_uparrow = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.dlna_slide_big_uparrow);

			int big_uparrowX = bitmapX + bitmap.getWidth() / 2 - dlna_slide_big_uparrow.getWidth();
			int big_uparrowY = bitmapY - dlna_slide_big_uparrow.getHeight();
			canvas.drawBitmap(dlna_slide_big_uparrow, big_uparrowX, big_uparrowY, paint);
			recycle(dlna_slide_big_uparrow);

			Bitmap dlna_slide_small_downarrow = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.dlna_slide_small_downarrow);

			int small_uparrowX = big_uparrowX + dlna_slide_big_uparrow.getWidth();
			int small_uparrowY = bitmapY - dlna_slide_small_downarrow.getHeight();
			canvas.drawBitmap(dlna_slide_small_downarrow, small_uparrowX + 10, small_uparrowY - 10, paint);
			recycle(dlna_slide_small_downarrow);

			Bitmap dlna_slide_pushguide = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.dlna_slide_pushguide);

			int pushguideX = small_uparrowX + dlna_slide_small_downarrow.getWidth() / 2 - 20;
			int pushguideY = small_uparrowY - dlna_slide_pushguide.getHeight();
			canvas.drawBitmap(dlna_slide_pushguide, pushguideX, pushguideY, paint);
			recycle(dlna_slide_pushguide);



			setImageBitmap(originalBitmap);
		} catch (Exception ex) {
		} catch (Error er) {
			System.gc();
		}
	}

	public void drawMusicSlideView(Bitmap bitmap, int[] location, Rect frame) {
		try {
			originalBitmap = Bitmap.createBitmap(getWidth(), getHeight(), Config.ARGB_8888);

			Paint paint = new Paint();

			Canvas canvas = new Canvas(originalBitmap);
			Bitmap mask = null;
			if (mask == null || mask.isRecycled()){
				mask = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.mask);
//				mask = setWidthAndHeight(mask, getWidth(), getHeight());
			}
			canvas.drawBitmap(mask, 0, 0, paint);
			recycle(mask);
			int bitmapX = location[0];
			int bitmapY = location[1] - frame.top;
			if (bitmap != null && !bitmap.isRecycled())
				canvas.drawBitmap(bitmap, bitmapX, bitmapY, paint);
			recycle(bitmap);

			Bitmap rc_tv_small = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.rc_tv_small);

			int tv_smallX = (frame.right - frame.left) / 2 - rc_tv_small.getWidth() / 2;
			int tv_smallY = 20;
			canvas.drawBitmap(rc_tv_small, tv_smallX, tv_smallY, paint);
			recycle(rc_tv_small);

			Bitmap dlna_slide_big_uparrow = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.dlna_slide_big_uparrow);

			int big_uparrowX = bitmapX + bitmap.getWidth() / 2 - dlna_slide_big_uparrow.getWidth();
			int big_uparrowY = bitmapY - dlna_slide_big_uparrow.getHeight();
			canvas.drawBitmap(dlna_slide_big_uparrow, big_uparrowX, big_uparrowY, paint);
			recycle(dlna_slide_big_uparrow);

			Bitmap dlna_slide_small_downarrow = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.dlna_slide_small_downarrow);

			int small_uparrowX = big_uparrowX + dlna_slide_big_uparrow.getWidth();
			int small_uparrowY = bitmapY - dlna_slide_small_downarrow.getHeight();
			canvas.drawBitmap(dlna_slide_small_downarrow, small_uparrowX + 10, small_uparrowY - 10, paint);
			recycle(dlna_slide_small_downarrow);

			Bitmap dlna_slide_pushguide = BitmapFactory.decodeResource(MyApp.getApplication().getResources(), R.drawable.dlna_slide_pushguide);

			int pushguideX = small_uparrowX + dlna_slide_small_downarrow.getWidth() / 2 - 20;
			int pushguideY = small_uparrowY - dlna_slide_pushguide.getHeight();
			canvas.drawBitmap(dlna_slide_pushguide, pushguideX, pushguideY, paint);
			recycle(dlna_slide_pushguide);



			setImageBitmap(originalBitmap);
		} catch (Exception ex) {
		} catch (Error er) {
			System.gc();
		}
	}

	public void touchClearShow() {
		setImageBitmap(null);
		recycle(originalBitmap);
	}

	private void recycle(Bitmap bitmap) {
		if (bitmap != null && !bitmap.isRecycled()) {
			bitmap.recycle();
		}
	}
}
