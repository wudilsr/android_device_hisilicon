package com.hisilicon.miracast.activity;

import java.lang.ref.WeakReference;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import com.hisilicon.miracast.R;
import com.hisilicon.miracast.activity.base.BaseActivity;
import com.hisilicon.miracast.constant.MsgConst;
import com.hisilicon.miracast.util.AppUtil;
import com.hisilicon.miracast.util.LogUtil;
import com.hisilicon.miracast.util.ToastUtil;

public class WelcomeActivity extends BaseActivity
{
    private final boolean mIsNoGuide = true;

    /** duration for welcome animation */
    private static final long ANIM_DURATION = 0;

    private static final String SPF_NAME = "app_first_run";
    private static final String SPF_VALUE_FIRST_RUN = "first_run";

    private Handler mMainHandler;

    private Intent mIntent;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        LogUtil.v("");
        super.onCreate(savedInstanceState);

        initVariable();

        if (AppUtil.isAudioLibFound())
        {
            stopBackgroundMusic();
            checkAppFirstRun();
        }
        else
        {
            showNoAudioLibToast();
            finish();
        }
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

        doCleanup();
    }

    @Override
    protected void initVariable()
    {
        mMainHandler = new MainHandler(this);
        mIntent = new Intent();
    }

    private void doCleanup()
    {
        mMainHandler.removeMessages(MsgConst.MSG_WELCOME_GO);
    }

    private void showNoAudioLibToast()
    {
        final int showTime = 3000;
        ToastUtil.showToast(this, R.string.ToastNoAudioLib, showTime);
        LogUtil.e("no audio lib");
    }

    private void checkAppFirstRun()
    {
        SharedPreferences spf = getSharedPreferences(SPF_NAME, MODE_PRIVATE);

        boolean isFirstRun = spf.getBoolean(SPF_VALUE_FIRST_RUN, true);
        if (mIsNoGuide)
        {
            isFirstRun = false;
        }

        if (!isFirstRun)
        {
            mIntent.setClass(this, SettingActivity.class);
        }
        else
        {
            // if first run, show guide for user
            mIntent.setClass(this, GuideActivity.class);
            SharedPreferences.Editor editor = spf.edit();
            editor.putBoolean(SPF_VALUE_FIRST_RUN, false);
            editor.commit();
        }

        mMainHandler.sendEmptyMessageDelayed(MsgConst.MSG_WELCOME_GO, ANIM_DURATION);
    }

    private void go()
    {
        startActivity(mIntent);
        finish();
    }

    static class MainHandler extends Handler
    {
        final WeakReference<WelcomeActivity> mRef;

        public MainHandler(WelcomeActivity ori)
        {
            mRef = new WeakReference<WelcomeActivity>(ori);
        }

        @Override
        public void handleMessage(Message msg)
        {
            final WelcomeActivity ori = mRef.get();

            switch (msg.what)
            {
                case MsgConst.MSG_WELCOME_GO:
                    ori.go();
                    break;

                default:
                    break;
            }
        }
    }
}
