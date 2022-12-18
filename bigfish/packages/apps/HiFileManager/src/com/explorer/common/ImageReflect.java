package com.explorer.common;

/**
 * 图片处理类
 */
import java.io.InputStream;

import android.R.integer;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.LinearGradient;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.PorterDuff.Mode;
import android.graphics.PorterDuffXfermode;
import android.graphics.Shader.TileMode;
import android.graphics.drawable.Drawable;
import android.util.Log;
import android.view.View;
import android.view.View.MeasureSpec;

public class ImageReflect {
	private static int reflectImageHeight = 100;// 图片的高度

	/**
	 * 将View视图装换为图片
	 *
	 * @param view
	 * @return
	 */
	public static Bitmap convertViewToBitmap(Context context, int img_id) {

		Resources res = context.getResources();
		Bitmap bmp = BitmapFactory.decodeResource(res, img_id);
		return bmp;

	}

	public static Bitmap convertViewToBitmap(View view) {

		view.measure(MeasureSpec.makeMeasureSpec(0, MeasureSpec.UNSPECIFIED), MeasureSpec.makeMeasureSpec(0, MeasureSpec.UNSPECIFIED));
		view.layout(0, 0, view.getMeasuredWidth(), view.getMeasuredHeight());
		view.buildDrawingCache();
		Bitmap bitmap = view.getDrawingCache();
		return bitmap;
	}

	public static Bitmap createReflectedImage(Bitmap bitmap, int reflectHeight) {

		int width = bitmap.getWidth();

		int height = bitmap.getHeight();
		if (height <= reflectHeight) {
		return null;

		}

		Matrix matrix = new Matrix();

		matrix.preScale(1, -1);

		Bitmap reflectionImage = Bitmap.createBitmap(bitmap, 0, height - reflectHeight, width, reflectHeight, matrix, true);

		Bitmap bitmapWithReflection = Bitmap.createBitmap(width, reflectHeight, Config.ARGB_8888);
		Canvas canvas = new Canvas(bitmapWithReflection);
		canvas.drawBitmap(reflectionImage, 0, 0, null);
		LinearGradient shader = new LinearGradient(0, 0, 0, bitmapWithReflection.getHeight()

		, 0x80ffffff, 0x00ffffff, TileMode.CLAMP);

		Paint paint = new Paint();
		paint.setShader(shader);

		paint.setXfermode(new PorterDuffXfermode(Mode.DST_IN));
		canvas.drawRect(0, 0, width, bitmapWithReflection.getHeight(), paint);
		return bitmapWithReflection;

	}

	/**
	 * 创建一个处理好的图片，包括边框渐变色以及图片交互的一些效果。
	 *
	 * @param bitmap
	 * @param cutHeight
	 * @return
	 */
	public static Bitmap createCutReflectedImage(Bitmap bitmap, int cutHeight, int imgWidth) {

		int width = bitmap.getWidth();
		// int width = imgWidth;

		int height = bitmap.getHeight();

		Log.i("ImageReflect", "***********width  图片的宽度***************" + width);
		Log.i("ImageReflect", "***********Height  图片的高度***************" + height);

		int totleHeight = reflectImageHeight + cutHeight;

		if (height <= totleHeight) {
		return null;
		}

		Matrix matrix = new Matrix();

		matrix.preScale(1, -1);

		System.out.println(height - reflectImageHeight - cutHeight);
		Bitmap reflectionImage = Bitmap.createBitmap(bitmap, 0, height - reflectImageHeight - cutHeight, width, reflectImageHeight, matrix, true);

		Bitmap bitmapWithReflection = Bitmap.createBitmap(width, reflectImageHeight, Config.ARGB_8888);
		Canvas canvas = new Canvas(bitmapWithReflection);
		canvas.drawBitmap(reflectionImage, 0, 0, null);
		LinearGradient shader = new LinearGradient(0, 0, 0, bitmapWithReflection.getHeight()

		, 0x80ffffff, 0x00ffffff, TileMode.CLAMP);

		Paint paint = new Paint();
		paint.setShader(shader);

		paint.setXfermode(new PorterDuffXfermode(Mode.DST_IN));
		canvas.drawRect(0, 0, width, bitmapWithReflection.getHeight(), paint);
		if (!reflectionImage.isRecycled()) {
		reflectionImage.recycle();
		}

		System.gc();
		return bitmapWithReflection;

	}

	public static Bitmap createReflectedImage(Bitmap originalImage) {
		int width = originalImage.getWidth();
		int height = originalImage.getHeight();
		Matrix matrix = new Matrix();
		// 实现图片翻转90度
		matrix.preScale(1, -1);
		// 创建倒影图片（是原始图片的一半大小）
		Bitmap reflectionImage = Bitmap.createBitmap(originalImage, 0, height / 2, width, height / 2, matrix, false);
		// 创建总图片（原图片 + 倒影图片）
//		Bitmap finalReflection = Bitmap.createBitmap(width, (height + height / 2), Config.ARGB_8888);
		Bitmap finalReflection = Bitmap.createBitmap(width, (height / 2), Config.ARGB_8888);
		// 创建画布
		Canvas canvas = new Canvas(finalReflection);
//		canvas.drawBitmap(originalImage, 0, 0, null);
		// 把倒影图片画到画布上
//		canvas.drawBitmap(reflectionImage, 0, height + 1, null);
		canvas.drawBitmap(reflectionImage, 0, 0, null);
		Paint shaderPaint = new Paint();
		// 创建线性渐变LinearGradient对象
//		LinearGradient shader = new LinearGradient(0, originalImage.getHeight(), 0, finalReflection.getHeight() + 1, 0x70ffffff, 0x00ffffff, TileMode.MIRROR);
		LinearGradient shader = new LinearGradient(0, 0, 0, finalReflection.getHeight(), 0x80ffffff, 0x00ffffff, TileMode.CLAMP);
		shaderPaint.setShader(shader);
		shaderPaint.setXfermode(new PorterDuffXfermode(Mode.DST_IN));
		// 画布画出反转图片大小区域，然后把渐变效果加到其中，就出现了图片的倒影效果。
//		canvas.drawRect(0, height + 1, width, finalReflection.getHeight(), shaderPaint);
		canvas.drawRect(0, 0, width, finalReflection.getHeight(), shaderPaint);
		return finalReflection;
	}

}
