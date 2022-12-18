package com.hisilicon.miracast.activity;

import com.hisilicon.miracast.R;
import com.hisilicon.miracast.activity.base.BaseActivity;
import com.hisilicon.miracast.constant.IntentConst;
import com.hisilicon.miracast.util.LogUtil;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.ViewGroup.LayoutParams;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ViewFlipper;

public class SupportedDevicesActivity extends BaseActivity
{
    private Activity mActivity;
    private LayoutInflater mInflater;
    private FrameLayout mMain;
    private LinearLayout mGroups;
    private ImageView[] mImageViews;
    private int mCurrentPage;
    private int mPagesCount;
    private ViewFlipper mViewFlipper;
    private GestureDetector mGestureDetector;
    private boolean mIsExitByBackKey = false;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        LogUtil.v("");
        super.onCreate(savedInstanceState);
        initView();
    }

    @Override
    protected void onStart()
    {
        LogUtil.v("");
        super.onStart();
    }

    @Override
    protected void onRestart()
    {
        LogUtil.v("");
        super.onRestart();
    }

    @Override
    protected void onResume()
    {
        LogUtil.v("");
        super.onResume();
    }

    @Override
    protected void onPause()
    {
        LogUtil.v("");
        super.onPause();
        if (!mIsExitByBackKey)
        {
            sendBroadcastFinishHelp();
            finish();
        }
    }

    @Override
    protected void onStop()
    {
        LogUtil.v("");
        super.onStop();
    }

    @Override
    protected void onDestroy()
    {
        LogUtil.v("");
        super.onDestroy();
    }

    @Override
    protected void initView()
    {
        LogUtil.v("");
        mActivity = this;
        mInflater = LayoutInflater.from(this);
        mMain = (FrameLayout) mInflater.inflate(R.layout.activity_help, null);
        mGroups = (LinearLayout) mMain.findViewById(R.id.viewGroup);
        mViewFlipper = (ViewFlipper) mMain.findViewById(R.id.viewflipper);
        mCurrentPage = 0;

        mViewFlipper.addView(mInflater.inflate(R.layout.activity_devices, null));
        mViewFlipper.setAutoStart(false);
        mPagesCount = mViewFlipper.getChildCount();
        LogUtil.v("mPagesCount = " + mPagesCount);

        mImageViews = new ImageView[mPagesCount];
        for (int i = 0; i < mPagesCount; i++)
        {
            ImageView iv = new ImageView(this);
            iv.setLayoutParams(new LayoutParams(20, 20));
            mImageViews[i] = iv;
            mGroups.addView(mImageViews[i]);
        }
        updateImgViewGroups();
        mGestureDetector = new GestureDetector(this, onGestureListener);
        setContentView(mMain);
    }

    private void sendBroadcastFinishHelp()
    {
        LogUtil.d("");
        sendBroadcast(new Intent(IntentConst.ACTION_FINISH_HELP));
    }

    protected void updateImgViewGroups()
    {
        LogUtil.v("");
        for (int i = 0; i < mPagesCount; i++)
        {
            mImageViews[mCurrentPage].setBackgroundResource(R.drawable.page_indicator_focused);
            if (mCurrentPage != i)
            {
                mImageViews[i].setBackgroundResource(R.drawable.page_indicator);
            }
        }
    }

    protected GestureDetector.OnGestureListener onGestureListener = new GestureDetector.SimpleOnGestureListener() {
        @Override
        public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
            float x = e2.getX() - e1.getX();
            if (x < 0) {
                if (mCurrentPage == mPagesCount - 1)
                    return false;
                Animation lInAnim = AnimationUtils.loadAnimation(mActivity, R.anim.push_left_in);
                Animation lOutAnim = AnimationUtils.loadAnimation(mActivity, R.anim.push_left_out);
                mViewFlipper.setInAnimation(lInAnim);
                mViewFlipper.setOutAnimation(lOutAnim);
                mViewFlipper.showNext();
                mCurrentPage++;
            } else if (x > 0) {
                if (mCurrentPage == 0)
                    return false;
                Animation rInAnim = AnimationUtils.loadAnimation(mActivity, R.anim.push_right_in);
                Animation rOutAnim = AnimationUtils.loadAnimation(mActivity, R.anim.push_right_out);
                mViewFlipper.setInAnimation(rInAnim);
                mViewFlipper.setOutAnimation(rOutAnim);
                mViewFlipper.showPrevious();
                mCurrentPage--;
            }
            updateImgViewGroups();
            return true;
        }
    };

    @Override
    public boolean onTouchEvent(MotionEvent event)
    {
        LogUtil.v("");
        return mGestureDetector.onTouchEvent(event);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        if (KeyEvent.KEYCODE_BACK == keyCode) {
            mIsExitByBackKey = true;
            Intent intent = new Intent();
            intent.setClass(SupportedDevicesActivity.this, SettingActivity.class);
            startActivity(intent);
            finish();
            return true;
        } else if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode) {
            if (mCurrentPage == 0)
                return false;
            Animation rInAnim = AnimationUtils.loadAnimation(mActivity, R.anim.push_right_in);
            Animation rOutAnim = AnimationUtils.loadAnimation(mActivity, R.anim.push_right_out);
            mViewFlipper.setInAnimation(rInAnim);
            mViewFlipper.setOutAnimation(rOutAnim);
            mViewFlipper.showPrevious();
            mCurrentPage--;
        } else if (KeyEvent.KEYCODE_DPAD_RIGHT == keyCode
                || KeyEvent.KEYCODE_DPAD_CENTER == keyCode) {
            if (mCurrentPage == mPagesCount - 1)
                return false;
            Animation lInAnim = AnimationUtils.loadAnimation(mActivity, R.anim.push_left_in);
            Animation lOutAnim = AnimationUtils.loadAnimation(mActivity, R.anim.push_left_out);
            mViewFlipper.setInAnimation(lInAnim);
            mViewFlipper.setOutAnimation(lOutAnim);
            mViewFlipper.showNext();
            mCurrentPage++;
        }
        updateImgViewGroups();
        return super.onKeyUp(keyCode, event);
    }

}