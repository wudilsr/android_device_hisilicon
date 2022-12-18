package com.hisilicon.multiscreen.widget;

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

    private Bitmap originalBitmap;

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

        Bitmap bitmap =
            BitmapFactory.decodeStream(getResources().openRawResource(
                R.drawable.remote_touch_arrow_left));

        drawLeft(bitmap);
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

        Bitmap bitmap =
            BitmapFactory.decodeStream(getResources().openRawResource(
                R.drawable.remote_touch_arrow_right));

        drawRight(bitmap);
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
        Bitmap bitmap =
            BitmapFactory.decodeStream(getResources().openRawResource(
                R.drawable.remote_touch_arrow_up));

        drawUp(bitmap);
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

        Bitmap bitmap =
            BitmapFactory.decodeStream(getResources().openRawResource(
                R.drawable.remote_touch_arrow_down));

        drawDown(bitmap);
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

        Bitmap bitmap =
            BitmapFactory.decodeStream(getResources().openRawResource(
                R.drawable.remote_touch_arrow_ok));
        drawOk(bitmap);
    }

    private void drawOk(Bitmap bitmap)
    {
        touch_x -= bitmap.getWidth() / 2;
        touch_y -= bitmap.getHeight() / 2;

        drawBitmap(bitmap);
    }

    private void drawBitmap(Bitmap bitmap)
    {
        recycle(originalBitmap);

        originalBitmap = Bitmap.createBitmap(getWidth(), getHeight(), Config.ARGB_8888);

        Paint paint = new Paint();

        Canvas canvas = new Canvas(originalBitmap);

        canvas.drawBitmap(bitmap, touch_x, touch_y, paint);

        recycle(bitmap);

        setImageBitmap(originalBitmap);
    }

    public void touchClearShow()
    {
        setImageBitmap(null);
        recycle(originalBitmap);
    }

    private void recycle(Bitmap bitmap)
    {
        if (bitmap != null && !bitmap.isRecycled())
        {
            bitmap.recycle();
            bitmap = null;
        }
    }
}
