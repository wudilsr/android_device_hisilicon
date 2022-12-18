package com.hisilicon.multiscreen.mirror;

import java.lang.ref.WeakReference;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.PixelFormat;
import android.media.AudioFormat;
import android.media.AudioTrack;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.ViewGroup.LayoutParams;

import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.mybox.MultiSettingActivity;
import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Class mirrorView, be used to show mirror-screen on client.<br>
 * CN:mirrorView类，用于客户端传屏显示。
 */
public class MirrorView extends SurfaceView
{
    /**
     * Surface holder.
     */
    public SurfaceHolder mSurfaceHolder = null;

    /**
     * True if screen is on while playing.
     */
    public boolean mIsOnWhilePlaying = false;

    /**
     * Surface of surfaceView.
     */
    public Surface mSurface = null;

    /**
     * Ip of access stb
     */
    private String mAccessIp = null;

    /**
     * Context mirror view rely on.
     */
    private Context mContext = null;

    /**
     * Audio track for play audio.
     */
    private static AudioTrack mAudioTrack = null;

    /**
     * Last open surface type.
     */
    private static String sLastSurfaceType = null;

    /**
     * Native context for save mirror player.
     */
    private int mNativeContext; // accessed by native methods

    /**
     * Surface view width.
     */
    private int viewWidth;

    /**
     * Surface view height.
     */
    private int viewHeight;

    /**
     * Constructor of mirrorView, to initialize SurfaceView.<br>
     * CN:构造函数，初始化SurfaceVIew。
     * @param context
     */
    public MirrorView(Context context)
    {
        super(context);
        initSurfaceView(context);
    }

    /**
     * Constructor.<br>
     * @param context
     * @param attrs
     */
    public MirrorView(Context context, AttributeSet attrs)
    {
        super(context, attrs, 0);
        initSurfaceView(context);
    }

    /**
     * Constructor.<br>
     * @param context
     * @param attrs
     * @param defStyle
     */
    public MirrorView(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
        initSurfaceView(context);
    }

    /**
     * To initialize SurfaceView.<br>
     * CN:初始化SurfaceVIew。
     * @param context
     */
    public void initSurfaceView(Context context)
    {
        HiDeviceInfo device = MultiScreenControlService.getInstance().getHiDevice();
        if (device != null)
        {
            mAccessIp = device.getDeviceIP();
        }
        else
        {
            mAccessIp = "127.0.0.1";
        }
        mContext = context;
        nativeSetup(new WeakReference<MirrorView>(this));
        getHolder().addCallback(mSHCallback);
    }

    public void setViewSize(int width, int height)
    {
        viewWidth = width;
        viewHeight = height;
    }

    public void update_view_size()
    {
        LayoutParams lp = this.getLayoutParams();
        lp.width = viewWidth;
        lp.height = viewHeight;
        this.setLayoutParams(lp);
        this.invalidate();
    }

    /**
     * Implement SurfaceHolder interface to receive information about changes to
     * the surface.<br>
     * CN:实现接口SurfaceHolder，用于接收Surface信息。
     */
    SurfaceHolder.Callback mSHCallback = new SurfaceHolder.Callback()
    {
        public void surfaceChanged(SurfaceHolder holder, int format, int w, int h)
        {
            /*
             * Renew surface when the surface changed. the work has been done in
             * libmirror_jni.so.<br> CN:更新surface当其发生变化时，已经在libmirror_jni.so中完成。
             */
        }

        public void surfaceCreated(SurfaceHolder holder)
        {
            LogTool.v("surfaceCreated start");
            mSurfaceHolder = holder;
            mSurfaceHolder.setFormat(PixelFormat.RGB_565);
            openSurface();
            LogTool.v("surfaceCreated end");
        }

        public void surfaceDestroyed(SurfaceHolder holder)
        {
            LogTool.v("surfaceDestroyed start");
            destroySurface();
            // after we return from this we can't use the surface any more
            mSurfaceHolder = null;
            LogTool.v("surfaceDestroyed end");
        }
    };

    /**
     * Pass the surface object to JNI and set keep screen on when the surface is
     * created.<br>
     * Surface建立时，将surface对象传入JNI，并保持屏幕打开。
     */
    private void openSurface()
    {
        if (mSurfaceHolder != null)
        {
            mSurface = mSurfaceHolder.getSurface();
        }
        else
        {
            mSurface = null;
        }
        String osVersion = android.os.Build.VERSION.SDK;
        LogTool.v("osVersion: " + osVersion);

        // Type of video.
        String type = MultiScreenControlService.getInstance().getSupportVideoType();
        if (type.equalsIgnoreCase(MultiScreenControlService.VIDEO_H264_TYPE))
        {
            startH264Surface(mSurface, Integer.valueOf(osVersion), mAccessIp);
        }
        else
        {
            startMirrorSurface(mSurface, Integer.valueOf(osVersion), mAccessIp);
        }
        // set last open surface type
        sLastSurfaceType = type;

        // Status of audio.
        startAudio(new WeakReference<MirrorView>(this));
        if (MultiScreenControlService.getInstance().isAudioPlay())
        {
            configAudio(MultiScreenControlService.AUDIO_PLAY);
        }
        else
        {
            configAudio(MultiScreenControlService.AUDIO_PAUSE);
        }

        setScreenOnWhilePlaying(true);
    }

    /**
     * Destroy surface.<br>
     * CN:销毁Surface。
     */
    @SuppressLint("NewApi")
    private void destroySurface()
    {
        if (mAudioTrack != null)
        {
            mAudioTrack.stop();
            mAudioTrack.release();
            mAudioTrack = null;
        }

        if (sLastSurfaceType.equalsIgnoreCase(MultiScreenControlService.VIDEO_H264_TYPE))
        {
            destroyH264Surface();
        }
        else
        {
            destroyMirrorSurface();
        }

        mSurface.release();
        mSurface = null;
    }

    /**
     * Set screen on while playing.<br>
     * CN:设置屏幕打开。
     * @param screenOn - screen on status
     */
    private void setScreenOnWhilePlaying(boolean screenOn)
    {
        if (mIsOnWhilePlaying != screenOn)
        {
            mIsOnWhilePlaying = screenOn;
            updateSurfaceScreenOn();
        }
    }

    /**
     * Update surface screen on.<br>
     * CN:更新屏幕打开状态。
     */
    private void updateSurfaceScreenOn()
    {
        if (mSurfaceHolder != null)
        {
            mSurfaceHolder.setKeepScreenOn(mIsOnWhilePlaying);
        }
    }

    /**
     * interface of Audio Track to writing in pcm audio data
     * @param byteArray PCM data
     */
    private static void writePCM(byte[] byteArray)
    {
        // Log.d(TAG,"writePCM "+ byteArray.length);
        if (mAudioTrack != null && AudioTrack.PLAYSTATE_PLAYING == mAudioTrack.getPlayState())
            mAudioTrack.write(byteArray, 0, byteArray.length);
        // Log.d(TAG,"writePCM OK");
    }

    /**
     * config attributes of AudioTrack and run it.
     * @param streamType eg:STREAM_VOICE_CALL, STREAM_SYSTEM, STREAM_RING,
     *        STREAM_MUSIC and STREAM_ALARM
     * @param sampleRate eg:48000,44100etc.
     * @param channelConfig channel num eg:1,2,5 etc
     * @param bytesPerSample bandwidth eg: 2,3 etc
     * @param trackMode file or stream
     * @return broadcast delay
     */
    private static int configATrack(int streamType, int sampleRate, int channelConfig,
        int bytesPerSample, int trackMode)
    {
        int latency = 0;
        int chanConfig =
            (channelConfig == 2) ? (AudioFormat.CHANNEL_CONFIGURATION_MONO)
                : (AudioFormat.CHANNEL_CONFIGURATION_STEREO);
        // Get the AudioTrack minimum buffer size
        int iMinBufSize = AudioTrack.getMinBufferSize(sampleRate, chanConfig, bytesPerSample);
        LogTool.d("iMinBufSize" + iMinBufSize);
        if (iMinBufSize == AudioTrack.ERROR_BAD_VALUE || iMinBufSize == AudioTrack.ERROR)
        {
            return 0;
        }
        // Constructor a AudioTrack object
        try
        {
            mAudioTrack =
                new AudioTrack(streamType, sampleRate, chanConfig, bytesPerSample, iMinBufSize * 4,
                    trackMode);
            LogTool.d("mAudioTrack OK" + streamType + sampleRate + chanConfig + bytesPerSample
                + iMinBufSize * 2 + trackMode);
            mAudioTrack.play();
            latency =
                (int) (iMinBufSize * 4.0 * 1000 / bytesPerSample / sampleRate / channelConfig);
            LogTool.d("mAudioTrack play OK");
        }
        catch (IllegalArgumentException iae)
        {
            LogTool.d("new AudioTrack Exceeption:" + iae.toString());
        }
        return latency;
    }

    /**
     * JNI function, start mirror with the surface object and ANDROID API
     * version.<br>
     * CN:JNI函数，设置surface对象和ANDROID API版本，并开启传屏。
     * @param surface - surface object
     * @param apiVersion - ANDROID API version
     */
    public native void startMirrorSurface(Surface surface, int apiVersion, String stbIp);

    /**
     * JNI function, destroy surface.<br>
     * CN:JNI函数，销毁surface。
     */
    public native void destroyMirrorSurface();

    /**
     * JNI function, get the FPS.<br>
     * CN:JNI函数，获取客户端支持的帧率。
     * @param return the FPS
     */
    public native int getdecodefps();

    /**
     * JNI function, start audio.<br>
     * CN:JNI函数，开启音频传输。
     * @param mirrorview_this
     */
    public native void startAudio(Object mirrorview_this);

    /**
     * JNI function, config Audio.<br>
     * CN:JNI函数,配置Audio的play 或者pause。
     * @param playFlag 0 means pause audio, 1 means play audio.
     */
    public native void configAudio(int playFlag);

    /**
     * JNI function, start mirror player.<br>
     * CN:JNI函数, 启动mirror player。
     * @param surface surface object.
     * @param apiVersion ANDROID API
     * @param stbIp stb ip address.
     */
    public native void startH264Surface(Surface surface, int apiVersion, String stbIp);

    /**
     * JNI function, destroy h264 surface.<br>
     * CN:JNI函数, 销毁h264 surface。
     */
    public native void destroyH264Surface();

    /**
     * JNI function, set up mirror player.<br>
     * CN:JNI函数, 初始化mirror player。
     * @param mirrorview_this mirror view.
     */
    public native void nativeSetup(Object mirrorview_this);
}
