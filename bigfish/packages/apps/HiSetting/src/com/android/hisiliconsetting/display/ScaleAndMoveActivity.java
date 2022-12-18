package com.android.hisiliconsetting.display;

import com.android.hisiliconsetting.R;
import com.hisilicon.android.HiDisplayManager;

import android.app.Activity;
import android.content.Context;
import android.graphics.Rect;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class ScaleAndMoveActivity extends Activity implements OnClickListener {
    private String TAG = "ScaleAndMoveActivity";
    private FrameLayout mRootLayout = null;
    private RelativeLayout scaleLayout = null;
    private TextView mScale_title = null,mScale_title_hint = null,mScale_introduce = null;
    private TextView mPercent = null;
    private TextView mScale_ok = null;
    private ImageView mMove_r = null,mMove_l = null,mMove_up = null,mMove_down = null;
    private final int mDelayTime = 300;
    private int mMove_step = 4;
    private int mScale_hstep = 4;
    private int mScale_wstep = 6;
    private int mWMax_margin = 200;
    private int mHMax_margin = 180;
    private int screenWidth;
    private int screenHeight;
    private int top_margin = 0;
    private int left_margin = 0;
    private int right_margin = 0;
    private int bottom_margin = 0;
    private LinearLayout.LayoutParams mParams = null;
    private ScaleType mType = ScaleType.SCALE;
    private HiDisplayManager mDisplayManager = null;
    private final int REFRESH_UI = 0;
    private final int REFRESH_LAYOUT = 1;
    private final int REFRESH_ARROW = 2;
    private enum ScaleType{
        SCALE,
        MOVE,
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.scale_set_main);
        WindowManager wManager = (WindowManager)getSystemService(Context.WINDOW_SERVICE);
         Display display = wManager.getDefaultDisplay();
         screenWidth = display.getWidth();
         screenHeight = display.getHeight();
         DisplayMetrics dm = new DisplayMetrics();
         dm = getResources().getDisplayMetrics();
         float density  = dm.density;        // ÆÁÄ»ÃÜ¶È£¨ÏñËØ±ÈÀý£º0.75/1.0/1.5/2.0£©
         int densityDPI = dm.densityDpi;
         Log.i(TAG, "density= "+density);
         Log.i(TAG, "densityDPI= "+densityDPI);
         Log.i(TAG, "screenWidth= "+screenWidth);
         Log.i(TAG, "screenHeight= "+screenHeight);
//         mWMax_margin = (int)(screenWidth*mMaxScale);
//         mHMax_margin = (int)(screenHeight*mMaxScale);
//         int margin_w = (int)(screenWidth*mScale_step);
//         int margin_h = (int)(screenHeight*mScale_step);
//         mWMax_margin = mWMax_margin - (mWMax_margin%margin_w)-margin_w;
//         mHMax_margin = mHMax_margin - (mHMax_margin%margin_h)-margin_h;
//         Log.i(TAG, "mWMax_margin= "+mWMax_margin);
//         Log.i(TAG, "mHMax_margin= "+mHMax_margin);
         mDisplayManager = new HiDisplayManager();
         InitUi();
    }
    @Override
    protected void onResume() {
        super.onResume();
        Rect rect = new Rect();
        rect = mDisplayManager.getOutRange();
        Log.i(TAG, "rect="+rect.left+" "+rect.top+" "+rect.right+" "+rect.bottom+" "+rect.height()+" "+rect.width());
        left_margin = rect.left;
        top_margin = rect.top;
        right_margin= rect.right;
        bottom_margin = rect.bottom;
        //mDisplayManager.setOutRange(0, 0, 0, 0);
        mPercent.setText(R.string.scale_title);
       //mhandler.sendEmptyMessage(REFRESH_LAYOUT);

    }
    private void InitUi(){
        mRootLayout = (FrameLayout)findViewById(R.id.scale_set_layout);
        mRootLayout.setOnKeyListener(new LayoutListener());
        mParams = (LinearLayout.LayoutParams)mRootLayout.getLayoutParams();
        mScale_title = (TextView)findViewById(R.id.scale_set_main_text);
        mScale_title_hint = (TextView)findViewById(R.id.scale_set_main_hint);
        mScale_introduce = (TextView)findViewById(R.id.scale_introduce_two);
        mScale_ok = (TextView)findViewById(R.id.scale_set_OK);
        mPercent = (TextView)findViewById(R.id.scale_set_count);
        mMove_r = (ImageView)findViewById(R.id.move_set_right);
        mMove_l = (ImageView)findViewById(R.id.move_set_left);
        mMove_up = (ImageView)findViewById(R.id.move_set_up);
        mMove_down = (ImageView)findViewById(R.id.move_set_down);
        scaleLayout = (RelativeLayout) findViewById(R.id.scale_set_count_layout);
        mMove_r.setOnClickListener(this);
        mMove_l.setOnClickListener(this);
        mMove_up.setOnClickListener(this);
        mMove_down.setOnClickListener(this);
        scaleLayout.setOnClickListener(this);
    }
    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.move_set_left:
            setLeft();
            break;
        case R.id.move_set_right:
            setRight();
            break;
        case R.id.move_set_up:
            setUp();
            break;
        case R.id.move_set_down:
            setDown();
            break;
        case R.id.scale_set_count_layout:
            setAttributes();
            break;
        default:
            break;
    }
    }
    private Handler mhandler = new Handler(){
        public void handleMessage(Message msg) {
        switch (msg.what) {
        case REFRESH_UI:
        ReFreshUi(mType);
        break;
        case REFRESH_LAYOUT:
//        mParams.topMargin = top_margin;
//        mParams.leftMargin = left_margin;
//        mParams.bottomMargin = bottom_margin;
//        mParams.rightMargin = right_margin;
        //mPercent.setText(String.valueOf(mScaleNum)+"%");
        //mRootLayout.setLayoutParams(mParams);
        if(top_margin<0)
        top_margin=0;
        if(left_margin<0)
        left_margin = 0;
        if(right_margin<0)
        right_margin = 0;
        if(bottom_margin<0)
        bottom_margin = 0;
        mDisplayManager.setOutRange(left_margin, top_margin, right_margin, bottom_margin);
        if(mType==ScaleType.MOVE)
        ArrowShow(true);
        break;
        case REFRESH_ARROW:
        ArrowFresh(msg.arg1);
        break;
        default:
        break;
        }
        }
    };
    private class LayoutListener implements OnKeyListener{
        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
        if(event.getAction()==KeyEvent.ACTION_DOWN){
        switch (keyCode) {
        case KeyEvent.KEYCODE_DPAD_CENTER:
        case KeyEvent.KEYCODE_ENTER:
        setAttributes();
        break;
        case KeyEvent.KEYCODE_BACK:
        //if(top_margin!=mOldRange.top||left_margin!=mOldRange.left||right_margin!=mOldRange.width||bottom_margin!=mOldRange.height)
        if(top_margin<0)
        top_margin=0;
        if(left_margin<0)
        left_margin = 0;
        if(right_margin<0)
        right_margin = 0;
        if(bottom_margin<0)
        bottom_margin = 0;
        Log.i(TAG, "setOutRange="+left_margin+" "+top_margin+" "+right_margin+" "+bottom_margin);
        mDisplayManager.setOutRange(left_margin, top_margin, right_margin, bottom_margin);
        mDisplayManager.SaveParam();
        break;
        case KeyEvent.KEYCODE_DPAD_LEFT:
            setLeft();
//        if(left_margin<0)
//        left_margin = 0;
        break;
        case KeyEvent.KEYCODE_DPAD_RIGHT:
           setRight();
//           if(right_margin<0)
//           right_margin = 0;
        break;
        case KeyEvent.KEYCODE_DPAD_DOWN://small
            setDown();
//           if(bottom_margin<0)
//           bottom_margin = 0;
        break;
        case KeyEvent.KEYCODE_DPAD_UP://big
            setUp();
//           if(top_margin<0)
//           top_margin = 0;
        break;
        default:
        break;
        }

        }
        return false;
        }

    }
    private void ReFreshUi(ScaleType type){
        if(type==ScaleType.MOVE){
        mScale_title.setText(R.string.move_title);
        mScale_title_hint.setText(R.string.move_title_hint);
        mScale_introduce.setText(R.string.move_introduce_two);
        mScale_ok.setText(R.string.move_OK);
        ArrowShow(true);
        }else{
        mScale_title.setText(R.string.scale_title);
        mScale_title_hint.setText(R.string.scale_title_hint);
        mScale_introduce.setText(R.string.scale_introduce_two);
        mScale_ok.setText(R.string.scale_OK);
        ArrowShow(false);
        }
    }
    private void ArrowFresh(int keycode){
        switch (keycode) {
        case KeyEvent.KEYCODE_DPAD_UP:
         mMove_up.setBackgroundResource(R.drawable.arrow_normal_up);
        break;
        case  KeyEvent.KEYCODE_DPAD_DOWN:
        mMove_down.setBackgroundResource(R.drawable.arrow_normal_down);
        break;
        case  KeyEvent.KEYCODE_DPAD_LEFT:
        mMove_l.setBackgroundResource(R.drawable.arrow_normal_left);
        break;
        case  KeyEvent.KEYCODE_DPAD_RIGHT:
        mMove_r.setBackgroundResource(R.drawable.arrow_normal_right);
        break;
        default:
        break;
        }
    }
    private void ArrowShow(Boolean show){
        if(show){
        if(left_margin>mWMax_margin){
        mMove_r.setVisibility(View.INVISIBLE);
        }else{
        mMove_r.setVisibility(View.VISIBLE);
        }
        if(right_margin>mWMax_margin){
        mMove_l.setVisibility(View.INVISIBLE);
        }else{
        mMove_l.setVisibility(View.VISIBLE);
        }
        }else{
        mMove_r.setVisibility(View.INVISIBLE);
        mMove_l.setVisibility(View.INVISIBLE);
        }
    }
    public class Rectangle
    {
        public int left;
        public int top;
        public int width;
        public int height;

        public Rectangle(int left,int top,int width,int height)
        {
            this.left = left;
            this.top = top;
            this.width = width;
            this.height = height;
        }
        public Rectangle()
        {
            this.left = 0;
            this.top = 0;
            this.width = 0;
            this.height = 0;
        }
        public boolean equals(Object obj)
        {
            Rectangle r = (Rectangle) obj;
            if (r != null)
            {
                return left == r.left && top == r.top && width == r.width && height == r.height;
            }
            return false;
        }
    }
    private void setLeft() {
        if (mType == ScaleType.MOVE) {
            if (right_margin < mWMax_margin) {
                left_margin = left_margin - mMove_step;
                right_margin = right_margin + mMove_step;
                Log.i(TAG, "left_margin= " + left_margin);
                Log.i(TAG, "right_margin= " + right_margin);
                mhandler.sendEmptyMessage(REFRESH_LAYOUT);
                mMove_l.setBackgroundResource(R.drawable.arrow_focus_left);
                Message msg = new Message();
                msg.what = REFRESH_ARROW;
                msg.arg1 = KeyEvent.KEYCODE_DPAD_LEFT;
                mhandler.sendMessageDelayed(msg, mDelayTime);
            }
        }
    }
    private void setRight() {
        if (mType == ScaleType.MOVE) {
            if (left_margin < mWMax_margin) {
                left_margin = left_margin + mMove_step;
                right_margin = right_margin - mMove_step;
                Log.i(TAG, "left_margin= " + left_margin);
                Log.i(TAG, "right_margin= " + right_margin);
                mhandler.sendEmptyMessage(REFRESH_LAYOUT);
                mMove_r.setBackgroundResource(R.drawable.arrow_focus_right);
                Message msg = new Message();
                msg.what = REFRESH_ARROW;
                msg.arg1 = KeyEvent.KEYCODE_DPAD_RIGHT;
                mhandler.sendMessageDelayed(msg, mDelayTime);
            }
        }
    }
    private void setDown() {
        if (mType == ScaleType.SCALE) {
            if (left_margin < mWMax_margin) {
                top_margin = top_margin + mScale_hstep;
                bottom_margin = bottom_margin + mScale_hstep;
                left_margin = left_margin + mScale_wstep;
                right_margin = right_margin + mScale_wstep;
                if (left_margin > mWMax_margin)
                    left_margin = mWMax_margin;
                if (right_margin > mWMax_margin)
                    right_margin = mWMax_margin;
                Log.i(TAG, "left_margin= " + left_margin);
                Log.i(TAG, "top_margin= " + top_margin);
            }
        } else {
            if (top_margin < mHMax_margin) {
                Log.i(TAG, "left_margin = " + left_margin);
                top_margin = top_margin + mMove_step;
                bottom_margin = bottom_margin - mMove_step;
                Log.i(TAG, "bottom_margin= " + bottom_margin);
                Log.i(TAG, "top_margin= " + top_margin);
            }
        }
        mhandler.sendEmptyMessage(REFRESH_LAYOUT);
        mMove_down.setBackgroundResource(R.drawable.arrow_focus_down);
        mhandler.removeMessages(REFRESH_ARROW);
        Message msg = new Message();
        msg.what = REFRESH_ARROW;
        msg.arg1 = KeyEvent.KEYCODE_DPAD_DOWN;
        mhandler.sendMessageDelayed(msg, mDelayTime);
    }
    private void setUp() {
        if (mType == ScaleType.SCALE) {
            if (top_margin > 0 || bottom_margin > 0 || left_margin > 0
                    || right_margin > 0) {
                top_margin = top_margin - mScale_hstep;
                bottom_margin = bottom_margin - mScale_hstep;
                left_margin = left_margin - mScale_wstep;
                right_margin = right_margin - mScale_wstep;
                if (top_margin < 0)
                    top_margin = 0;
                if (bottom_margin < 0)
                    bottom_margin = 0;
                if (right_margin < 0)
                    right_margin = 0;
                if (left_margin < 0)
                    left_margin = 0;
            }
        } else {
            if (bottom_margin < mHMax_margin) {
                top_margin = top_margin - mMove_step;
                bottom_margin = bottom_margin + mMove_step;
                Log.i(TAG, "bottom_margin= " + bottom_margin);
                Log.i(TAG, "top_margin= " + top_margin);
            }
        }
        mhandler.sendEmptyMessage(REFRESH_LAYOUT);
        mMove_up.setBackgroundResource(R.drawable.arrow_focus_up);
        Message msg = new Message();
        msg.what = REFRESH_ARROW;
        msg.arg1 = KeyEvent.KEYCODE_DPAD_UP;
        mhandler.sendMessageDelayed(msg, mDelayTime);
    }
    private void setAttributes() {
        if (mType == ScaleType.SCALE) {
            mType = ScaleType.MOVE;
            mPercent.setText(R.string.move_title);
            ArrowShow(true);
        } else {
            mType = ScaleType.SCALE;
            mPercent.setText(R.string.scale_title);
            ArrowShow(false);
        }
        mhandler.sendEmptyMessage(REFRESH_UI);
    }
}
