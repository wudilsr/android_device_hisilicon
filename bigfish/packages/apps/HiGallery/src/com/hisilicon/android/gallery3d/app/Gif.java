package com.hisilicon.android.gallery3d.app;

import java.io.FileNotFoundException;
import android.app.Activity;
import android.content.ContentResolver;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.widget.Toast;
import android.view.MotionEvent;

import com.hisilicon.android.gallery3d.R;

public class Gif extends Activity {
    private GifView gv;
    private RefreshThread mThread;
    private HandlerThread mGifThread = new HandlerThread("GifThread");
    private Handler mGifHandler = null;
    private final static int SHOW_GIF = 0;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.gif_view);
        gv = (GifView)findViewById(R.id.gif1);
        mGifThread.start();
        mGifHandler = new Handler(mGifThread.getLooper()) {
            @Override
            public void handleMessage(Message msg) {
                switch (msg.what) {
                    case SHOW_GIF:
                        showGif();
                        break;
                }
            }
        };
        mGifHandler.sendEmptyMessage(SHOW_GIF);
    }

    class RefreshThread extends Thread {
        public void run() {
            while (!Thread.interrupted()) {
                try {
                    gv.postInvalidate();
                    Thread.sleep(gv.gHelper.nextDelay());
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (mThread != null ) {
            mThread.interrupt();
            mThread = null;
        }
        mGifThread.quit();
        mGifThread = null;
        mGifHandler = null;
        finish();
    }

    public boolean onTouchEvent(MotionEvent event) {
        if(MotionEvent.ACTION_DOWN==event.getAction() || MotionEvent.ACTION_MOVE==event.getAction())
        {
            finish();
        }
        return super.onTouchEvent(event);
    }

    private void showGif() {
        try {
            gv.setSrc(getContentResolver().openInputStream(getIntent().getData()));
        }
        catch (OutOfMemoryError e)
        {
           e.printStackTrace();
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        try {
            mThread = new RefreshThread();mThread.setName("RefreshThread");
            mThread.start();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
