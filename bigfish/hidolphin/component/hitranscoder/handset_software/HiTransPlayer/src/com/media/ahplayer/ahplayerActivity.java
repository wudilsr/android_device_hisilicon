/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.ahplayer;

import java.io.IOException;
import com.media.libahplayer.libahplayer;
import com.media.libahplayer.libahplayerException;
import com.media.libahplayer.libahplayer.libahplayerListener;
import com.media.ahplayer.ahplayerMovieView;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnKeyListener;
import android.content.Intent;
import android.content.DialogInterface.OnClickListener;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.Toast;

public class ahplayerActivity extends Activity {
    private static final String     TAG = "ahplayerActivity";
    private static boolean                sLoaded = false;
    private static int                bHWDec = 0;
    private ahplayerMovieView     mMovieView;
    private ahplayerConfig config = null;
    String  mfilePath;
    private int mWindowWidth = 0;
    private int mWindowHeight = 0;
    private static final int PLAYER_ASR_CHANGE = 0x01;
    private Context mCtx;
    private ProgressDialog prgDlg;
    private Thread playerThread;
    LinearLayout endprog;

    private Object mSyncObj = new Object();

    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG, "onCreate()");
        super.onCreate(savedInstanceState);
        Intent i = getIntent();
        mfilePath = i.getStringExtra(getResources().getString(R.string.input_file));
        mCtx = this;
        getWindow().setSoftInputMode(
                WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
        if(mfilePath == null) {
            Log.d(TAG, "Not specified video file");
            finish();
        } else {
            requestWindowFeature(Window.FEATURE_NO_TITLE);
            getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
            getWindow().setFormat(PixelFormat.RGBA_8888);
            getWindow().setFlags(
                    WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
                    WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
            mWindowWidth = getWindowManager().getDefaultDisplay().getWidth();
            mWindowHeight = getWindowManager().getDefaultDisplay().getHeight();
            //getWindow().addFlags(WindowManager.LayoutParams.FLAG_DITHER);
            try {
                loadLibs();
                setContentView(R.layout.ahplayer_activity);
                config = new ahplayerConfig(this);
                mMovieView = (ahplayerMovieView)findViewById(R.id.MovieView01);
                endprog = (LinearLayout) findViewById(R.id.endprog);
                mMovieView.setViewSize(mWindowWidth,mWindowHeight);
                mMovieView.setMainHandler(mPlayerHandler);
                try {
                    mMovieView.setPlayerConfig(config.ahplayerConfigPath);
                    playerThread = new StartPlayerThread();
                    playerThread.start();
                    prgDlg = ProgressDialog.show(mCtx, "Movie",
                            "please waiting ...");
                    prgDlg.setCancelable(false);
                } catch (IllegalArgumentException e) {
                    Log.e(TAG, "Can't set video: " + e.getMessage());
                } catch (IllegalStateException e) {
                    Log.e(TAG, "Can't set video: " + e.getMessage());
                    libahplayerException ie =
                        new libahplayerException(libahplayerException.LEVEL_FATAL, "state error");
                    throw ie;
                }
            } catch (libahplayerException e) {
                Log.d(TAG, "Error when initializing libahplayer: " + e.getMessage());
                Message sendmsg = new Message();
                sendmsg.what = 29;
                mPlayerHandler.sendMessage(sendmsg);
            }
        }
    }

    protected void onPause() {
        Log.d(TAG, "onPause()");
        if(prgDlg!=null)
        {
            prgDlg.setCancelable(true);
            prgDlg.cancel();
        }
        release();

        super.onPause();
    }

    protected void onResume() {
        Log.d(TAG, "onResume()");
        super.onResume();
    }

    protected void onDestroy() {
        Log.d(TAG, "onDestroy()");
        super.onDestroy();
    }

    @Override
    protected void onStop() {
        // TODO Auto-generated method stub
        Log.d(TAG, "ahplayerActivity onStop");
        super.onStop();
    }

    private void release() {
        Log.d(TAG, "Synchronized release.");
        synchronized (mSyncObj) {
            if (mbStartFlag)
                mMovieView.release();
        }
        finish();
    }

    boolean mbStartFlag = false;

    class StartPlayerThread extends Thread
    {
        @Override
        public void run() {
            // TODO Auto-generated method stub
            try {
                mMovieView.SetPlayerListener(mPlayerListener);
                synchronized (mSyncObj) {
                    mbStartFlag = true;
                    mMovieView.openPlayer(mfilePath);
                }

            } catch (IllegalStateException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
                if (prgDlg != null)
                    prgDlg.cancel();
                Message sendmsg = new Message();
                sendmsg.what = 29;
                mPlayerHandler.sendMessage(sendmsg);
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            super.run();
        }
    }

    /**
     * loads all native libraries
     * @return true if all libraries was loaded, otherwise return false
     */
    private static boolean loadLibs() throws libahplayerException {
        if(sLoaded) {
            return true;
        }
        boolean err = false;
        int version = Integer.valueOf(android.os.Build.VERSION.SDK);
        try {
            if(bHWDec == 1)
            {
                System.loadLibrary("hwtest_jni");
            }
            else
            {
                if(version < 14)
                {
                    Log.e(TAG, "load libhi_ffmpeg.so");
                    System.loadLibrary("hi_ffmpeg");
                }
                else
                {
                    Log.e(TAG, "load libtest1_jni.so");
                    System.loadLibrary("test1_jni");
                }
                

            }
        } catch(UnsatisfiedLinkError e) {
            Log.d(TAG, "Error when Loading our lib: " + e.getMessage());
        }
        if(!err) {
            sLoaded = true;
        }
        return sLoaded;
    }
    /*
     * 0:full;1 tong bili fangda
     * */
    private void setDisplayMode(int mode)
    {
        int targetWidth = mMovieView.getViewWidth();
        int targetHeight = mMovieView.getViewHeight();
        int displayWidth = getWindowManager().getDefaultDisplay().getWidth();
        int displayHeight = getWindowManager().getDefaultDisplay().getHeight();
        double ard = (double) displayWidth / (double) displayHeight;
        double art = (double) targetWidth / (double) targetHeight;
        if (ard > art) {
            displayWidth = displayHeight * targetWidth / targetHeight;
        } else {
            displayHeight = displayWidth * targetHeight / targetWidth;
        }
        android.view.ViewGroup.LayoutParams lp = mMovieView.getLayoutParams();
        lp.width = displayWidth;
        lp.height = displayHeight;
        mMovieView.setLayoutParams(lp);
        mMovieView.invalidate();
    }

    libahplayerListener mPlayerListener = new libahplayerListener()
    {
        public void onError(libahplayer mplayer, String msg, Exception e) {
            // TODO Auto-generated method stub
            Log.e(TAG, "libahplayerListener onError");
            Message sendmsg = new Message();
            sendmsg.what = 30;
            Bundle data = new Bundle();
            data.putCharSequence("MSG", "Server error happened, please link again! ");
            sendmsg.setData(data);
            mPlayerHandler.sendMessage(sendmsg);
        }


        public void onPrepare(libahplayer mplayer) {
            // TODO Auto-generated method stub
            Message sendmsg = new Message();
            sendmsg.what = 40;
            mPlayerHandler.sendMessage(sendmsg);
        }

        public void onFinish(libahplayer mplayer) {
            // TODO Auto-generated method stub
            finish();
        }
        public void onRelease(libahplayer mplayer) {
            // TODO Auto-generated method stub
            Message sendmsg = new Message();
            sendmsg.what = 29;
            mPlayerHandler.sendMessage(sendmsg);
        }

        public void onStop(libahplayer mplayer) {
            // TODO Auto-generated method stub
        }

        public void onASRChange(libahplayer mplayer)
        {
            Log.e(TAG, "AHPlayer onASRChange");
            Message message = new Message();
            message.what = PLAYER_ASR_CHANGE;
            message.arg1 = mMovieView.getViewWidth();
            message.arg2 = mMovieView.getViewHeight();
            mPlayerHandler.sendMessage(message);
            Log.d(TAG, "Send ASRChange Event ");
        }
    };

    void playerActivityFinish() {
        finish();
    }

    void playerRelease() {
        Log.d(TAG, "playerRelease");
        endprog.setVisibility(1);
        synchronized (mSyncObj) {
            if (mbStartFlag)
                mMovieView.release();
        }
        endprog.setVisibility(0);
    }

    boolean bToastFlag = false;

    void checkCurState() {
        ahplayerMovieView.playerState state;
        state = mMovieView.getCurPlayerState();
        if (state != ahplayerMovieView.playerState.STATE_RUNNING
                && state != ahplayerMovieView.playerState.STATE_INIT) {
            try {
                if (!bToastFlag) {
                    Toast.makeText(mCtx, "initing, pls wait..",
                            Toast.LENGTH_SHORT).show();
                    bToastFlag = true;
                }
                Thread.sleep(50);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            mPlayerHandler.sendEmptyMessage(31);
        } else {
            playerRelease();
            if (prgDlg != null)
                prgDlg.cancel();
            playerActivityFinish();
        }
    }

    Handler mPlayerHandler   = new Handler()
    {
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case PLAYER_ASR_CHANGE:
                    Log.d(TAG, "changeASR ");
                    //mMovieView.changeASR();
                    mMovieView.update_surface_view();
                    Log.d(TAG, "invalidate ");
                    //mMovieView.invalidate();
                    break;

                case 29:
                    String tips = "Open a new program unsuccessfully, please try again!";
                playerRelease();
                    if(!isFinishing())
                        ahplayerMessageBox.show(mCtx, "tips", tips,
                                new OnClickListener()
                                {
                                    @Override
                                    public void onClick(DialogInterface dialog,
                                            int which)
                                    {
                                        // TODO Auto-generated method stub
                                        playerActivityFinish();
                                    }
                                });
                    break;

                case 30:
                    Bundle data = msg.getData();
                    String Errstr = data.getCharSequence("MSG").toString();
                playerRelease();
                if (!isFinishing())
                    ahplayerMessageBox.show(mCtx, "tips", Errstr,
                            new OnClickListener()
                            {
                                @Override
                                public void onClick(DialogInterface dialog,
                                        int which)
                                {
                                    // TODO Auto-generated method stub
                                    if (prgDlg != null)
                                        prgDlg.cancel();
                                    playerActivityFinish();
                                }
                            });
                break;

            case 31:
                checkCurState();
                break;

                case 40:
                    if(prgDlg != null)
                    {
                        prgDlg.setCancelable(true);
                        prgDlg.cancel();
                    }

                    break;
            }
            super.handleMessage(msg);
        }
    };

    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {
            // bLoopPlayback = false;
            Log.e(TAG, "back are pressed");
            mPlayerHandler.sendEmptyMessage(31);
        }
        return false;
    }
}
