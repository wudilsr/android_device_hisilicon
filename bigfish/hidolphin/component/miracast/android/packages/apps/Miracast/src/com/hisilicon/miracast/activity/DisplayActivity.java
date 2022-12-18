package com.hisilicon.miracast.activity;

import java.lang.ref.WeakReference;

import android.app.AlertDialog;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.view.KeyEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.Window;
import android.widget.TextView;
import android.widget.ImageView;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;

import com.hisilicon.miracast.R;
import com.hisilicon.miracast.activity.base.BaseActivity;
import com.hisilicon.miracast.constant.IntentConst;
import com.hisilicon.miracast.constant.MsgConst;
import com.hisilicon.miracast.model.WfdModel;
import com.hisilicon.miracast.service.WfdService;
import com.hisilicon.miracast.util.DialogUtil;
import com.hisilicon.miracast.util.LogUtil;
import com.hisilicon.miracast.util.ToastUtil;
import com.hisilicon.miracast.util.ViewUtil;

public final class DisplayActivity extends BaseActivity
{
    /* view */
    private SurfaceView mSvDisplay;
    private TextView mTvLostPacket;
    private boolean mIsInfoShown = false;
    private ImageView mNetWorkStateImg;
    /* wfd */
    private WfdModel mWfdModel;
    private BroadcastReceiver mWfdReceiver;

    /* service */
    private ServiceConnection mConnection;
    private Messenger mMessenger;
    private boolean mIsBound = false;
    private boolean mIsHomeBack = true;

    private NetworkState mNetworkState = NetworkState.green;

    private enum NetworkState
    {
        green, yellow, red
    }

    private boolean mIsRcvNwPoorMsg = false;
    private boolean mIsHandling = false;
    private Thread mNetworkChangeThread = null;
    private Handler mMainHandler;
    private boolean mIsInterrptThread = false;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        LogUtil.v("");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display);

        Window curWindow = getWindow();
        if (curWindow == null)
        {
            return;
        }
        View dectorView = curWindow.getDecorView();
        if (dectorView == null)
        {
            return;
        }
        else
        {
            dectorView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_LOW_PROFILE);
        }
        initView();

        initCheckNetworkState();
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

        showSurface();
        initReceiver();
        bindWfdService();
    }

    @Override
    protected void onPause()
    {
        LogUtil.v("");
        super.onPause();
        LogUtil.v("mIsHomeBack = " + mIsHomeBack);
        if (mIsHomeBack)
        {
            notifyHomeStop();
        }
        unBindWfdService();
        destroyReceiver();
        hideSurface();
        destroyThread();
        finish();
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
    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
        LogUtil.d(String.valueOf(keyCode));

        switch (keyCode)
        {
            case KeyEvent.KEYCODE_BACK:
                showExitDialog();
                return true;

            case KeyEvent.KEYCODE_INFO:
                toggleInfoShowing();
                break;

            default:
                break;
        }

        return super.onKeyUp(keyCode, event);
    }

    private void showExitDialog()
    {
        LogUtil.d("");
        AlertDialog.Builder builder =
            DialogUtil.getCommonDialogBuilder(this, R.string.DialogTitleConfirmExit,
                R.string.DialogMessageConfirmExit);
        builder.setPositiveButton(R.string.TextYes, new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
                mIsHomeBack = false;
                finish();
            }
        });
        builder.setNegativeButton(R.string.TextNo, null);
        builder.show();
    }

    @Override
    protected void initView()
    {
        mSvDisplay = (SurfaceView) findViewById(R.id.sv_display);
        mTvLostPacket = (TextView) findViewById(R.id.tv_lost_packet);
        mNetWorkStateImg = (ImageView) findViewById(R.id.iv_network_state);

        mSvDisplay.getHolder().addCallback(new SurfaceCallback());

        mIsInfoShown = (mTvLostPacket.getVisibility() == View.VISIBLE);
    }

    private void initReceiver()
    {
        LogUtil.d("");
        final IntentFilter filter = new IntentFilter();
        filter.addAction(IntentConst.ACTION_FINISH_DISPLAY);
        filter.addAction(IntentConst.ACTION_WFD_CHANGED);
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

    private void destroyThread()
    {
        try
        {
            if ((mNetworkChangeThread != null) && (mNetworkChangeThread.isAlive()))
            {
                mIsInterrptThread = true;
                mNetworkChangeThread.join();
                mNetworkChangeThread = null;
            }
        }
        catch (InterruptedException e)
        {
            LogUtil.e(e.toString());
        }

        mIsRcvNwPoorMsg = false;
        mIsHandling = false;
    }

    private void showSurface()
    {
        LogUtil.d("");
        ViewUtil.showView(mSvDisplay);
    }

    private void hideSurface()
    {
        LogUtil.d("");
        ViewUtil.hideView(mSvDisplay);
    }

    private void bindWfdService()
    {
        final Intent intent = new Intent(this, WfdService.class);
        mConnection = new WfdServiceConnection();
        bindService(intent, mConnection, Context.BIND_IMPORTANT);
    }

    private void unBindWfdService()
    {
        if (mIsBound)
        {
            notifyStop();

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
        notify(MsgConst.MSG_DISPLAY_START);
    }

    private void notifyStop()
    {
        notify(MsgConst.MSG_DISPLAY_STOP);
    }

    private void notifyHomeStop()
    {
        notify(MsgConst.MSG_DISPLAY_HOME_STOP);
    }

    private void showSorryToast()
    {
        ToastUtil.showToast(this, R.string.ToastSorryForNetwork);
    }

    private void toggleInfoShowing()
    {
        mIsInfoShown = !mIsInfoShown;
        ViewUtil.showView(mTvLostPacket, mIsInfoShown);
    }

    private void handleGreenState()
    {
        mIsHandling = true;

        if (mNetworkState == NetworkState.green)
        {
            mNetworkState = NetworkState.yellow;
            mMainHandler.sendEmptyMessage(MsgConst.MSG_DISPLAY_NETWORK_YELLOW);
            handleYellowState();
        }
    }

    private void handleYellowState()
    {
        mIsRcvNwPoorMsg = false;

        if (!mIsInterrptThread)
        {
            delayXXXSeconds();

            if (mIsRcvNwPoorMsg)
            {
                mNetworkState = NetworkState.red;
                mMainHandler.sendEmptyMessage(MsgConst.MSG_DISPLAY_NETWORK_RED);
                handleRedState();
            }
            else
            {
                mNetworkState = NetworkState.green;
                mMainHandler.sendEmptyMessage(MsgConst.MSG_DISPLAY_NETWORK_GREEN);
            }
        }
    }

    private void handleRedState()
    {
        mIsRcvNwPoorMsg = false;

        if (!mIsInterrptThread)
        {
            delayXXXSeconds();

            if (mIsRcvNwPoorMsg)
            {
                handleRedState();
            }
            else
            {
                mNetworkState = NetworkState.yellow;
                mMainHandler.sendEmptyMessage(MsgConst.MSG_DISPLAY_NETWORK_YELLOW);
                handleYellowState();
            }
        }
    }

    private void setNetworkGreen()
    {
        mNetWorkStateImg.setImageResource(R.drawable.iv_network_green);
    }

    private void setNetworkYellow()
    {
        mNetWorkStateImg.setImageResource(R.drawable.iv_network_yellow);
    }

    private void setNetworkRed()
    {
        mNetWorkStateImg.setImageResource(R.drawable.iv_network_red);
    }

    private void initCheckNetworkState()
    {
        setNetworkGreen();
        mMainHandler = new MainHandler(this);
    }

    private void delayXXXSeconds()
    {
        int timer = 0;

        //delay 3 secodes
        while (timer < 10)
        {
            try
            {
                Thread.sleep(300);
                timer++;
            }
            catch(Exception e)
            {
                LogUtil.e(e.toString());
            }

            if (mIsInterrptThread)
            {
                break;
            }
        }
    }

    class NetWorkChangeThread implements Runnable
    {
        @Override
        public void run()
        {
            try
            {
                handleGreenState();
            }
            catch (Exception e)
            {
                LogUtil.e(e.toString());
            }
        }
    }

    class MainHandler extends Handler
    {
        final WeakReference<DisplayActivity> mRef;

        public MainHandler(DisplayActivity ori)
        {
            mRef = new WeakReference<DisplayActivity>(ori);
        }

        @Override
        public void handleMessage(Message msg)
        {
            final DisplayActivity ori = mRef.get();

            switch (msg.what)
            {
                case MsgConst.MSG_DISPLAY_NETWORK_GREEN:
                {
                    ori.setNetworkGreen();
                    ori.destroyThread();
                    break;
                }

                case MsgConst.MSG_DISPLAY_NETWORK_YELLOW:
                {
                    ori.setNetworkYellow();
                    break;
                }

                case MsgConst.MSG_DISPLAY_NETWORK_RED:
                {
                    ori.setNetworkRed();
                    break;
                }

                default:
                    break;
            }
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
                int lostPacket = mWfdModel.getLostPacket();
                mTvLostPacket.setText(String.valueOf(lostPacket));
                if (lostPacket > 3)
                {
                    mIsRcvNwPoorMsg = true;

                    if (!mIsHandling)
                    {
                        mNetworkChangeThread = new Thread(new NetWorkChangeThread());
                        mNetworkChangeThread.start();
                        mIsInterrptThread = false;
                    }
                }
            }
            else if (IntentConst.ACTION_FINISH_DISPLAY.equals(action))
            {
                mIsHomeBack = false;
                destroyThread();
                finish();
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

    class SurfaceCallback implements SurfaceHolder.Callback
    {
        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
        {
            LogUtil.d("");
        }

        @Override
        public void surfaceCreated(SurfaceHolder holder)
        {
            LogUtil.d("");
            holder.setType(SurfaceHolder.SURFACE_TYPE_HISI_TRANSPARENT);
        }

        @Override
        public void surfaceDestroyed(SurfaceHolder holder)
        {
            LogUtil.d("");
        }
    }
}
