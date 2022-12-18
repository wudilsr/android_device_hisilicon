package com.hisilicon.android.videoplayer.view;

import com.hisilicon.android.videoplayer.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.media.AudioManager;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnKeyListener;

public class VolumnSet extends View implements OnKeyListener
{
    Context context;

    int count = 15;
    Bitmap green = null;
    Bitmap black = null;
    Bitmap sound = null;
    Bitmap mute = null;
    int currAudio;
    int templeft;
    int currLeft;
    int currTop;
    Paint paint;

    public int getCurrAudio()
    {
        return currAudio;
    }

    public void setCurrAudio(int currAudio)
    {
        this.currAudio = currAudio;
    }

    public void setLeftAndTop(int left, int top)
    {
        this.templeft = left;
        this.currLeft = left;
        this.currTop = top;
    }

    public VolumnSet(Context context)
    {
        super(context);
        this.context = context;
        green = BitmapFactory.decodeResource(getResources(), R.drawable.volumn_green);
        black = BitmapFactory.decodeResource(getResources(), R.drawable.volumn_black);
        sound = BitmapFactory.decodeResource(getResources(), R.drawable.sound);
        mute  = BitmapFactory.decodeResource(getResources(), R.drawable.mute);
        paint = new Paint();
    }

    public VolumnSet(Context context, AttributeSet attrs)
    {
        super(context, attrs);
        this.context = context;
        green = BitmapFactory.decodeResource(getResources(), R.drawable.volumn_green);
        black = BitmapFactory.decodeResource(getResources(), R.drawable.volumn_black);
        sound = BitmapFactory.decodeResource(getResources(), R.drawable.sound);
        mute  = BitmapFactory.decodeResource(getResources(), R.drawable.mute);
        paint = new Paint();
    }

    protected void onDraw(Canvas canvas)
    {
        super.onDraw(canvas);
        if (currAudio == 0)
        {
            canvas.drawBitmap(mute, currLeft - 30, currTop - 5, paint);
        }
        else
        {
            canvas.drawBitmap(sound, currLeft - 30, currTop - 5, paint);
        }

        for (int i = 0; i < count; i++)
        {
            currLeft += 20;
            if (i < currAudio)
            {
                canvas.drawBitmap(green, currLeft, currTop, paint);
            }
            else
            {
                canvas.drawBitmap(black, currLeft, currTop, paint);
            }
        }

        currLeft = templeft;
    }

    public boolean onKey(View v, int keyCode, KeyEvent event)
    {
        return false;
    }
}
