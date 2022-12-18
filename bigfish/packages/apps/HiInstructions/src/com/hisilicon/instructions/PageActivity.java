package com.hisilicon.instructions;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.widget.RelativeLayout;

public abstract class PageActivity extends Activity {
    private final String NETWORK_PACKAGE = "com.android.hisiliconsetting";
    private final String NETWORK_ACTIVITY = "com.android.hisiliconsetting.net.NetSetActivity";

    private RelativeLayout layout;
    private GestureDetector gestureDetector;

    private GestureDetector.OnGestureListener onGestureListener = new GestureDetector.SimpleOnGestureListener() {
        @Override
        public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX,
                float velocityY) {
            float x = e2.getX() - e1.getX();
            if (x < 0) {
                startNextActivity();
            } else if (x > 0) {
                startPrvActivity();
            }
            return true;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(getLayoutId());
        gestureDetector = new GestureDetector(PageActivity.this,
                onGestureListener);
        layout = (RelativeLayout) findViewById(R.id.layout);
        layout.addView(((MyApplication) getApplication()).getRelativeLayout(
                this, getPosition()));
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        gestureDetector.onTouchEvent(event);
        return super.onTouchEvent(event);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (KeyEvent.KEYCODE_BACK == keyCode) {
            return true;
        } else if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode) {
            startPrvActivity();
        } else if (KeyEvent.KEYCODE_DPAD_RIGHT == keyCode
                || KeyEvent.KEYCODE_DPAD_CENTER == keyCode) {
            startNextActivity();
        }
        return super.onKeyDown(keyCode, event);
    }

    public void checkNetWork() {
        ConnectivityManager connectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo info = connectivityManager.getActiveNetworkInfo();
        if (info == null || !info.isAvailable()) {
            try {
                Intent intent = new Intent();
                ComponentName componentName = new ComponentName(
                        NETWORK_PACKAGE, NETWORK_ACTIVITY);
                intent.setComponent(componentName);
                startActivity(intent);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public abstract int getLayoutId();

    public abstract int getPosition();

    public abstract void startPrvActivity();

    public abstract void startNextActivity();
}