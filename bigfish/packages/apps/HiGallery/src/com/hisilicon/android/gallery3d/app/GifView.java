package com.hisilicon.android.gallery3d.app;

import java.io.InputStream;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

import com.hisilicon.android.gallery3d.app.*;

public class GifView extends View {
    GifOpenHelper gHelper;
    Bitmap bmp;
    public static boolean ready = false;

    // construct - refer for java
    public GifView(Context context) {
        super(context);
        // TODO Auto-generated constructor stub
        init();

    }

    // construct - refer for xml
    public GifView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();

    }

    public void init() {
        // do some initial
        ready = false;
    }

    @Override
        protected void onSizeChanged(int w, int h, int oldw, int oldh) {
            // TODO Auto-generated method stub
            super.onSizeChanged(w, h, oldw, oldh);
        }
    public void setSrc(InputStream is) {
        gHelper = new GifOpenHelper();
        gHelper.read(is);
        bmp = gHelper.getFrame(0);
        ready = true;
    }

    protected void onDraw(Canvas canvas) {
        // TODO Auto-generated method stub
        if (!ready) {
            return;
        }
        super.onDraw(canvas);
        int vwidth = this.getWidth();
        int vheight = this.getHeight();

        int width = bmp.getWidth();
        int height = bmp.getHeight();

        canvas.drawBitmap(bmp, (vwidth - width) / 2, (vheight - height) / 2, new Paint());

        //bmp.recycle();
        bmp = gHelper.nextBitmap();
    }
}
