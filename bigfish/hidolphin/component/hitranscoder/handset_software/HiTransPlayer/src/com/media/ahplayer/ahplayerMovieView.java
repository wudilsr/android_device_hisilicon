/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.ahplayer;

import java.io.IOException;

import com.media.libahplayer.libahplayer;
import com.media.libahplayer.AHSMonitorInfo;
import com.media.libahplayer.libahplayer.libahplayerListener;

import android.content.Context;
import android.graphics.PixelFormat;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.WindowManager;
import android.view.ViewGroup.LayoutParams;
import android.widget.MediaController;
import android.widget.MediaController.MediaPlayerControl;

/**
 * 播放器视频播放窗口render 类，继承自SurfaceView, Android图像显示组件
 * @author l00203185
 *
 */
/**
 * the render class of player video display, inherit from surfaceView,
 * the Android component of display
 */
public class ahplayerMovieView extends SurfaceView {
    private static final String     TAG = "FFMpegMovieViewAndroid";

    private Context                    mContext;
    public libahplayer            mPlayer = null;
    public SurfaceHolder            mSurfaceHolder = null;
    private MediaController            mMediaController = null;
    private int viewWidth;
    private int viewHeight;
    private static boolean bUsingAspectRatio = false;
    private static libahplayerListener mListener;
    private Handler mHandler;
    private boolean mbSurfCreated =false;;
    public ahplayerMovieView(Context context) {
        super(context);
        initVideoView(context);
    }

    public ahplayerMovieView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
        initVideoView(context);
    }

    public ahplayerMovieView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        initVideoView(context);
    }

    public enum playerState {
        STATE_BASE, STATE_INIT, STATE_PREPARED, STATE_RUNNING, STATE_RELEASED
    }

    public playerState getCurPlayerState() {
        return mPlayerState;
    }

    public playerState mPlayerState = playerState.STATE_RELEASED;

    public void openPlayer(String path) throws IllegalStateException, IOException, InterruptedException
    {
        int iSleepTimes = 0;
        while(!mbSurfCreated)
        {
            Thread.sleep(50);
            Log.e(TAG, "surface have not been inited");
            if(iSleepTimes > 10)
            {
                throw new IllegalStateException();
            }
            iSleepTimes++;
        }
        setVideoPath(path);
        setVideoDisplayMode(0);
        prepareVideo();
        if(mPlayerState == playerState.STATE_PREPARED)
        {
            startVideo();
            mPlayerState = playerState.STATE_RUNNING;
        }
        else
        {
            Log.e(TAG, "startVideo current state is not OK");
        }
    }
    /**
     * 初始化player对象实例，并设置surface 事件处理函数
     * @param context Activity上下文
     */
    /**
     * init the instance of player, and set the event handlr
     * of surface
     * @param context of Activity
     */
    private void initVideoView(Context context) {
        mContext = context;

        mPlayer = new libahplayer();
        getHolder().addCallback(mSHCallback);
    }

    public void setMainHandler(Handler handr)
    {
        mHandler = handr;
    }

    /**
     * 配置视频高宽
     * @param width 宽度
     * @param height 高度
     */
    /**
     * config video width and height
     * @param width width
     * @param height height
     */
    public void setViewSize(int width,int height)
    {
        viewWidth = width;
        viewHeight = height;
    }
    /**
     * 获取视频宽度
     * @return 视频宽度
     */
    public int getViewWidth()
    {
        return mPlayer.getVideoWidth()/32*32;
    }
    /**
     * 获取视频高度
     * @return 视频高度
     */
    public int getViewHeight()
    {
        return mPlayer.getVideoHeight();
    }
    /**
     * 设置视频源
     * @param filePath 服务端源URL
     * @throws IllegalArgumentException 参数异常
     * @throws IllegalStateException 状态异常
     * @throws IOException 存取异常
     */
    public void setVideoPath(String filePath) throws IllegalArgumentException, IllegalStateException, IOException {
        Log.e(TAG, "setDataSource start: ");
        mPlayer.setDataSource(filePath);
        Log.e(TAG, "setDataSource end: ");
    }
    /**
     * 当前无用
     * @param mode
     * @throws IllegalArgumentException
     * @throws IllegalStateException
     * @throws IOException
     */
    public void setVideoDisplayMode(int mode) throws IllegalArgumentException, IllegalStateException, IOException {
        mPlayer.setVideoDisplayMode(mode);
    }

    /**
     * 配置config文件路径
     * @param Config 配置文件路径
     */
    /**
     * set dir of config file
     * @param Config dir of config file
     */
    public void setPlayerConfig(String Config)
    {
        mPlayer.setPlayerConfig(Config);
    }

    public void update_surface_view()
    {
        Log.e(TAG, "update_surface_view");
        if(mPlayer.getVideoWidth()!=0 && mPlayer.getVideoHeight() != 0)
        {
            Log.e(TAG,"player width : "+mPlayer.getVideoWidth()+"height:" +
                    mPlayer.getVideoHeight());
            mSurfaceHolder.setFixedSize(mPlayer.getVideoWidth()/16*16,mPlayer.getVideoHeight());
            double art = 0;
            if(bUsingAspectRatio)
            {
                float aspectRatio = mPlayer.getVideoAspectRatio();
                Log.e(TAG,"aspectRatio : "+aspectRatio);
                art = aspectRatio;//2.2
            }
            if(!bUsingAspectRatio ||(art < 0.001))
            {
                int targetWidth = mPlayer.getVideoWidth()/32*32;
                int targetHeight = mPlayer.getVideoHeight();
                art = (double)targetWidth/targetHeight;
            }
            LayoutParams lp = this.getLayoutParams();

            int displayWidth = viewWidth;//((WindowManager) getWindowToken()).getDefaultDisplay().getWidth();
            int displayHeight = viewHeight;//((WindowManager) getWindowToken()).getDefaultDisplay().getHeight();
            double ard = (double) displayWidth / (double) displayHeight;
            if (ard > art) {
                displayWidth = (int) (displayHeight * art);
            }
            else {
                displayHeight = (int) (displayWidth/art);
            }

            lp.width = displayWidth;
            lp.height = displayHeight;
            Log.e(TAG,"video width : "+mPlayer.getVideoWidth()+"height:" +
                    mPlayer.getVideoHeight()+"update width: "+displayWidth+"height:"
                    +displayHeight);
            this.setLayoutParams(lp);
            this.invalidate();
        }
    }
    /**
     * initzialize player
     * @throws IOException,
     */
    private void prepareVideo() throws IOException, IllegalStateException
    {
            mPlayer.setDisplay(mSurfaceHolder);
            Log.e(TAG, "prepare start: ");
            mPlayer.prepare();
            Log.e(TAG, "prepare end: ");
            mPlayerState = playerState.STATE_PREPARED;
    }

    private void startVideo() {
        Log.d(TAG, "mPlayer.start start");
        mPlayer.start();
    }

    public void release() {
        Log.d(TAG, "releasing player");
        mPlayer.suspend();
        mPlayer.release();
        mPlayerState = playerState.STATE_RELEASED;
        Log.d(TAG, "released");
    }

    public boolean changeASR()
    {
        Log.d(TAG, "MovieView changeASR: " + mPlayer.getVideoWidth()/32*32 + " " + mPlayer.getVideoHeight());
        mSurfaceHolder.setFixedSize(mPlayer.getVideoWidth()/32*32,mPlayer.getVideoHeight());
        return true;
    }

    SurfaceHolder.Callback mSHCallback = new SurfaceHolder.Callback() {
        public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
            Log.e(TAG, "surfaceChanged ");
            //update_surface_view();
            Log.e(TAG, "surface resolution: " + w +"   "+h+"   "+format);
        }

        public void surfaceCreated(SurfaceHolder holder) {
            Log.e(TAG, "surfaceCreated start");
            mSurfaceHolder = holder;
            mSurfaceHolder.setFormat(PixelFormat.RGB_565);
            mPlayerState = playerState.STATE_INIT;
            mbSurfCreated = true;
            Log.e(TAG, "surfaceCreated end");
        }

        public void surfaceDestroyed(SurfaceHolder holder) {
            Log.e(TAG, "surfaceDestroyed start");
            if(mPlayerState != playerState.STATE_RELEASED)
            {
                release();
                //if(mPlayer!= null && mListener!= null)
                 //   mListener.onFinish(mPlayer);
                // after we return from this we can't use the surface any more
                mSurfaceHolder = null;
                mMediaController = null;
                mbSurfCreated = false;
            }
            Log.e(TAG, "surfaceDestroyed end");
        }
    };

    public void SetPlayerListener(libahplayerListener listener)
    {
        mPlayer.setLibahplayerListener(listener);
        mListener = listener;
    }
}
