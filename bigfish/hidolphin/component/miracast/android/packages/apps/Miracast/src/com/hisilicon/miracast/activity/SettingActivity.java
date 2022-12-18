package com.hisilicon.miracast.activity;

import java.lang.ref.WeakReference;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.hisilicon.miracast.R;
import com.hisilicon.miracast.activity.base.BaseActivity;
import com.hisilicon.miracast.constant.IntentConst;
import com.hisilicon.miracast.constant.MsgConst;
import com.hisilicon.miracast.model.WfdModel;
import com.hisilicon.miracast.service.WfdService;
import com.hisilicon.miracast.util.AppUtil;
import com.hisilicon.miracast.util.DialogUtil;
import com.hisilicon.miracast.util.LogUtil;
import com.hisilicon.miracast.util.ViewUtil;
import com.hisilicon.miracast.util.ToastUtil;
import com.hisilicon.miracast.widget.DotsMarqueeTextView;

public final class SettingActivity extends BaseActivity
{
    /* view */
    private TextView mTvDeviceName;
    private TextView mTvDeviceConnection;
    private DotsMarqueeTextView mTvDotsMarquee;
    private ProgressBar mPbWaiting;
    private Button mBUserGuide;
    private Button mBSupportedDevices;

    /* dialog */
    private ProgressDialog mProgressDialog;

    /* wfd */
    private WfdModel mWfdModel;
    private BroadcastReceiver mWfdReceiver;

    private Handler mMainHandler;

    /* service */
    private ServiceConnection mConnection;
    private Messenger mMessenger;
    private boolean mIsBound = false;

    private boolean mIsExitOnV5 = true;
    private boolean mFirstTimeExit = true;
    private boolean mIsHomeBack = false;
    private boolean mIsEnterGuidePage = false;
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        LogUtil.v("");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_setting);

        initView();
        initVariable();
        initReceiver();
        bindWfdService();
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
        mIsExitOnV5 = true;
        mIsEnterGuidePage = false;
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
        LogUtil.d("mIsEnterGuidePage = " + mIsEnterGuidePage);
        if (mIsExitOnV5 && !mIsEnterGuidePage)
        {
            doDestroy();
            finish();
        }
    }

    private void doDestroy()
    {
        hideWaitingDialog();
        unBindWfdService();
        destroyReceiver();
        doCleanup();
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
        LogUtil.d("mIsHomeBack = " + mIsHomeBack);
        if (mIsExitOnV5 || mIsHomeBack)
        {
            doDestroy();
        }

    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
        LogUtil.d(String.valueOf(keyCode));

        switch (keyCode)
        {

            case KeyEvent.KEYCODE_BACK:
                // for Android 4.2 only
                // does not call onStop & onDestroy
                //mIsExitOnV5 = true;
                LogUtil.d("mIsBound = " + mIsBound);
                if (mIsBound && mFirstTimeExit)
                {
                    mFirstTimeExit = false;
                    notifyStop();
                }
                return true;

            case KeyEvent.KEYCODE_INFO:
                showAboutDialog();
                break;

            default:
                break;
        }

        return super.onKeyUp(keyCode, event);
    }

    private void showWifiP2pOnDialog()
    {
        LogUtil.d("");
        if (mProgressDialog == null)
        {
            mProgressDialog =
                DialogUtil.getCommonProgressDialog(this, R.string.DialogTitleWifiP2pOn,
                                                   R.string.DialogMessageWaiting);
            mProgressDialog.show();
        }
    }

    private void showWifiP2pOffDialog()
    {
        LogUtil.d("");
        if (mProgressDialog == null)
        {
            mProgressDialog =
                DialogUtil.getCommonProgressDialog(this, R.string.DialogTitleWifiP2pOff,
                                                   R.string.DialogMessageWaiting);
            mProgressDialog.show();
        }
    }

    private void hideWaitingDialog()
    {
        LogUtil.d("");
        if (mProgressDialog != null)
        {
            mProgressDialog.dismiss();
            mProgressDialog = null;
        }
    }

    private void showAboutDialog()
    {
        LogUtil.d("");
        AlertDialog.Builder builder =
            DialogUtil.getCommonDialogBuilder(this, R.string.DialogTitleAboutMiracast, "version "
                                              + AppUtil.getVersionInfo(getApplicationContext()));
        builder.setPositiveButton(android.R.string.ok, null);
        builder.show();
    }

    private void showTurnOffAPToast()
    {
        ToastUtil.showToast(this, R.string.ToastTurnoffConnectedAp);
    }

    @Override
    protected void initView()
    {
        mTvDeviceName = (TextView) findViewById(R.id.tv_device_name);
        mTvDeviceConnection = (TextView) findViewById(R.id.tv_device_connection);
        mTvDotsMarquee = (DotsMarqueeTextView) findViewById(R.id.tv_dots_marquee);
        mPbWaiting = (ProgressBar) findViewById(R.id.pb_waiting);
        mBUserGuide = (Button) findViewById(R.id.bt_user_guide);
        mBUserGuide.setOnClickListener(new Button.OnClickListener()
        {
            public void onClick(View v)
            {
                Intent intent = new Intent();
                intent.setClass(SettingActivity.this, HelpActivity.class);
                mIsEnterGuidePage = true;
                startActivity(intent);
            }
        });

        mBSupportedDevices = (Button) findViewById(R.id.bt_supported_devices);
        mBSupportedDevices.setOnClickListener(new Button.OnClickListener()
        {
            public void onClick(View v)
            {
                Intent intent = new Intent();
                intent.setClass(SettingActivity.this, SupportedDevicesActivity.class);
                mIsEnterGuidePage = true;
                startActivity(intent);
            }
        });
    }

    @Override
    protected void initVariable()
    {
        mMainHandler = new MainHandler(this);
    }

    private void initReceiver()
    {
        LogUtil.d("");
        final IntentFilter filter = new IntentFilter();
        filter.addAction(IntentConst.ACTION_WFD_CHANGED);
        filter.addAction(IntentConst.ACTION_FINISH_SETTING);
        filter.addAction(IntentConst.ACTION_FINISH_WFD_INIT);
        filter.addAction(IntentConst.ACTION_HOME_FINISH_SETTING);
        filter.addAction(IntentConst.ACTION_FINISH_HELP);
        filter.addAction(IntentConst.ACTION_SHOW_TOAST);
        filter.addAction(IntentConst.ACTION_SHOW_TURN_ON_DIALOG);
        filter.addAction(IntentConst.ACTION_SHOW_TURN_OFF_DIALOG);
        filter.addAction(IntentConst.ACTION_HIDE_DIALOG);
        mWfdReceiver = new WfdReceiver();
        registerReceiver(mWfdReceiver, filter);
    }

    private void destroyReceiver()
    {
        LogUtil.d("");
        if (mWfdReceiver != null)
        {
            unregisterReceiver(mWfdReceiver);
            mWfdReceiver = null;
        }
    }

    private void doCleanup()
    {
        LogUtil.d("");
        if (mTvDotsMarquee != null)
        {
            mTvDotsMarquee.stopMarquee();
            mTvDotsMarquee = null;
        }
    }

    private void bindWfdService()
    {
        final Intent intent = new Intent(this, WfdService.class);
        mConnection = new WfdServiceConnection();
        bindService(intent, mConnection, Context.BIND_AUTO_CREATE);
    }

    private void unBindWfdService()
    {
        if (mIsBound)
        {
            unbindService(mConnection);
            mMessenger = null;
            mIsBound = false;
        }
    }

    private void notify(int what)
    {
        final Message msg = Message.obtain();
        msg.what = what;

        if (mMessenger != null)
        {
            try
            {
                mMessenger.send(msg);
            }
            catch (RemoteException e)
            {
                LogUtil.e(e.toString());
            }
        }
    }

    private void notifyStart()
    {
        notify(MsgConst.MSG_SETTING_START);
    }

    private void notifyStop()
    {
        notify(MsgConst.MSG_SETTING_STOP);
    }

    private void notifyDisplayStart()
    {
        notify(MsgConst.MSG_SETTING_DISPLAYSTART);
    }

    private void sendMsgUpdateUI()
    {
        mMainHandler.sendEmptyMessage(MsgConst.MSG_SETTING_UPDATE_UI);
    }

    private void updateUI()
    {
        String connection = "";
        int color = getResources().getColor(R.color.azure);
        String na = getString(R.string.TextNotAvailable);
        String deviceName = na;
        boolean isShowProgress = false;
        boolean isShowDots = false;

        if (mWfdModel.isWifiP2pEnabled())
        {
            deviceName = mWfdModel.getDeviceName();

            if (mWfdModel.isWifiP2pConnected())
            {
                connection = getString(R.string.TextWifiP2pConnected);
                color = getResources().getColor(R.color.chartreuse);
                // hide progress bar when wfd start finish
                isShowProgress = !mWfdModel.isWfdStarted();
                isShowDots = false;
            }
            else if (mWfdModel.isWifiP2pConnecting())
            {
                connection = getString(R.string.TextWifiP2pConnecting);
                color = getResources().getColor(R.color.chartreuse);
                isShowProgress = true;
                isShowDots = false;
            }
            else
            {
                connection = getString(R.string.TextWifiP2pDisconnected);
                isShowProgress = false;
                isShowDots = true;
            }
        }

        if (mWfdModel.isExitingFromMiracast())
        {
            connection = getString(R.string.TextWifiP2pExit);
            color = getResources().getColor(R.color.chartreuse);
            isShowProgress = true;
            isShowDots = false;
        }

        mTvDeviceConnection.setTextColor(color);
        mTvDeviceConnection.setText(connection);
        mTvDeviceName.setText(deviceName);

        if (mTvDotsMarquee != null)
        {
            if (isShowDots)
            {
                mTvDotsMarquee.startMarquee();
            }
            else
            {
                mTvDotsMarquee.stopMarquee();
            }
        }

        if (mPbWaiting != null)
        {
            ViewUtil.showView(mPbWaiting, isShowProgress);
        }

        if (mTvDotsMarquee != null)
        {
            ViewUtil.showView(mTvDotsMarquee, isShowDots);
        }
    }

    class WfdReceiver extends BroadcastReceiver
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            final String action = intent.getAction();
            LogUtil.d(action);

            if (IntentConst.ACTION_WFD_CHANGED.equals(action))
            {
                mWfdModel = (WfdModel) intent.getSerializableExtra(IntentConst.EXTRA_WFD_MODEL);
                sendMsgUpdateUI();
            }
            else if (IntentConst.ACTION_FINISH_SETTING.equals(action))
            {
                finish();
            }
            else if (IntentConst.ACTION_FINISH_WFD_INIT.equals(action))
            {
                mIsExitOnV5 = false;

                notifyDisplayStart();
            }
            else if (IntentConst.ACTION_HOME_FINISH_SETTING.equals(action))
            {
                mIsHomeBack = true;
                finish();
            }
            else if (IntentConst.ACTION_FINISH_HELP.equals(action))
            {
                LogUtil.d("mIsExitOnV5 = " + mIsExitOnV5);
                if (mIsExitOnV5)
                {
                    finish();
                }
            }
            else if (IntentConst.ACTION_SHOW_TOAST.equals(action))
            {
                showTurnOffAPToast();
            }
            else if (IntentConst.ACTION_SHOW_TURN_ON_DIALOG.equals(action))
            {
                showWifiP2pOnDialog();
            }
            else if (IntentConst.ACTION_SHOW_TURN_OFF_DIALOG.equals(action))
            {
                showWifiP2pOffDialog();
            }
            else if (IntentConst.ACTION_HIDE_DIALOG.equals(action))
            {
                hideWaitingDialog();
            }
        }
    }

    static class MainHandler extends Handler
    {
        final WeakReference<SettingActivity> mRef;

        public MainHandler(SettingActivity ori)
        {
            mRef = new WeakReference<SettingActivity>(ori);
        }

        @Override
        public void handleMessage(Message msg)
        {
            final SettingActivity ori = mRef.get();

            switch (msg.what)
            {
                case MsgConst.MSG_SETTING_UPDATE_UI:
                    ori.updateUI();
                    break;

                default:
                    break;
            }
        }
    }

    class WfdServiceConnection implements ServiceConnection
    {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service)
        {
            mMessenger = new Messenger(service);
            mIsBound = true;

            notifyStart();
        }

        @Override
        public void onServiceDisconnected(ComponentName name)
        {
            mIsBound = false;
        }
    }

}
