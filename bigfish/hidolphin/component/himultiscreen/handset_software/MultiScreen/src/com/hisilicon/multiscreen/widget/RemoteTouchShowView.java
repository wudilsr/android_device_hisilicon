package com.hisilicon.multiscreen.widget;

import java.lang.ref.SoftReference;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.widget.ImageView;

import com.hisilicon.multiscreen.mybox.R;

public class RemoteTouchShowView extends ImageView
{
    private int touch_x;

    private int touch_y;

    private SoftReference<Bitmap> originalBitmap;

    public RemoteTouchShowView(Context context)
    {
        super(context);
    }

    public RemoteTouchShowView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }

    public void touchShowLeft(int x, int y)
    {
        touch_x = x;
        touch_y = y;

        SoftReference<Bitmap> bitmap = new SoftReference<Bitmap>(
            BitmapFactory.decodeStream(getResources().openRawResource(
                R.drawable.remote_touch_arrow_left)));
        if(bitmap != null)
            drawLeft(bitmap.get());
    }

    private void drawLeft(Bitmap bitmap)
    {
        touch_x -= bitmap.getWidth();
        touch_y -= bitmap.getHeight() / 2;

        drawBitmap(bitmap);
    }

    public void touchShowRight(int x, int y)
    {
        touch_x = x;
        touch_y = y;

        SoftReference<Bitmap> bitmap =new SoftReference<Bitmap>(
            BitmapFactory.decodeStream(getResources().openRawResource(
                R.drawable.remote_touch_arrow_right)));
        if(bitmap != null)
            drawRight(bitmap.get());
    }

    private void drawRight(Bitmap bitmap)
    {
        touch_y -= bitmap.getHeight() / 2;

        drawBitmap(bitmap);
    }

    public void touchShowUp(int x, int y)
    {
        touch_x = x;
        touch_y = y;
        SoftReference<Bitmap> bitmap =new SoftReference<Bitmap>(
            BitmapFactory.decodeStream(getResources().openRawResource(
                R.drawable.remote_touch_arrow_up)));
        if(bitmap != null)
            drawUp(bitmap.get());
    }

    private void drawUp(Bitmap bitmap)
    {
        touch_x -= bitmap.getWidth() / 2;
        touch_y -= bitmap.getHeight();

        drawBitmap(bitmap);
    }

    public void touchShowDown(int x, int y)
    {
        touch_x = x;
        touch_y = y;

        SoftReference<Bitmap> bitmap =new SoftReference<Bitmap>(
            BitmapFactory.decodeStream(getResources().openRawResource(
                R.drawable.remote_touch_arrow_down)));
        if(bitmap != null)
            drawDown(bitmap.get());
    }

    private void drawDown(Bitmap bitmap)
    {
        touch_x -= bitmap.getWidth() / 2;

        drawBitmap(bitmap);
    }

    public void touchShowOk(int x, int y)
    {
        touch_x = x;
        touch_y = y;

        SoftReference<Bitmap> bitmap =new SoftReference<Bitmap>(
            BitmapFactory.decodeStream(getResources().openRawResource(
                R.drawable.remote_touch_arrow_ok)));

        if(bitmap != null)
            drawOk(bitmap.get());
    }

    private void drawOk(Bitmap bitmap)
    {
        touch_x -= bitmap.getWidth() / 2;
        touch_y -= bitmap.getHeight() / 2;

        drawBitmap(bitmap);
    }

    private void drawBitmap(Bitmap bitmap)
    {
        if(originalBitmap != null)
            recycle(originalBitmap.get());

        originalBitmap = new SoftReference<Bitmap>(Bitmap.createBitmap(getWidth(), getHeight(), Config.ARGB_8888));

        if(originalBitmap != null)
        {
            Paint paint = new Paint();

            Canvas canvas = new Canvas(originalBitmap.get());

            canvas.drawBitmap(bitmap, touch_x, touch_y, paint);

            recycle(bitmap);

            setImageBitmap(originalBitmap.get());
        }

    }

    public void touchClearShow()
    {
        setImageBitmap(null);
        if(originalBitmap != null)
            recycle(originalBitmap.get());
    }

    private void recycle(Bitmap bitmap)
    {
        if (bitmap != null && !bitmap.isRecycled())
        {
            bitmap.recycle();
            bitmap = null;
        }
        System.gc();
    }
}
