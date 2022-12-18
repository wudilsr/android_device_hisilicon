package com.hisilicon.android;

import android.app.Activity;
import android.content.Context;
import android.graphics.*;
import android.graphics.drawable.GradientDrawable;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Scroller;
import android.view.View.OnClickListener;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.Animation;
import java.lang.reflect.Constructor;
import android.view.KeyEvent;

public class HiAnimationActivity extends Activity implements OnClickListener, AnimationListener, Runnable{
    /** Called when the activity is first created. */
    private String TAG = "HiAnimationActivity";
    private Paint mPaint;
    private Bitmap[] b;
    private int index = 0;
    private HiImageView aView = null;
    private int bmpcount = 4;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        HiImageView v;
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        v = new HiImageView(this);
        aView = v;
        b = new Bitmap[bmpcount];

        int[] bmpids = {
            R.drawable.p1,
            R.drawable.p2,
            R.drawable.p3,
            R.drawable.p4,};

        for(int i=0;i<bmpcount;i++)
        {
            b[i] = BitmapFactory.decodeResource(getResources(), bmpids[i]);
        }

        v.setImageBitmap(b[0]);
        v.setOnClickListener(this);
        getWindow().setFlags(
                WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
            setContentView(v);
    }

    public void run()
    {
        String className[] = {"HiRotateAnimation","HiReelAnimation","HiTurnPageAnimation", "HiShutterAnimation",  "HiInAnimation", "HiTransAnimation", "HiCenterAnimation"};

        try{
            String classname = "com.hisilicon.android."+className[index%className.length];
            ALog.e(TAG, "1 do animation "+classname);
            Class<?> aniClass = Class.forName(classname);
            Constructor<?> aniCons = aniClass.getConstructor(Bitmap.class, Bitmap.class);

            HiAnimation a = null;
            a = (HiAnimation)aniCons.newInstance(b[index%bmpcount], b[(index+1)%bmpcount]);
            a.setAnimationListener(this);
            aView.startAnimation(a);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        index++;
    }

    public void onAnimationEnd(Animation animation) {
        aView.post(this);
    }

    public void onAnimationRepeat(Animation animation) {
    }

    public void onAnimationStart(Animation animation) {
    }

    public void onClick(View v) {
        v.post(this);
    }

    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if(KeyEvent.KEYCODE_DPAD_CENTER == keyCode)
        {
            aView.post(this);
        }
        return super.onKeyDown(keyCode, event);
    }
}


