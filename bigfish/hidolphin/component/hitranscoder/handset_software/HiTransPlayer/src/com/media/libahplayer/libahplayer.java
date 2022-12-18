/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.libahplayer;

import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.PowerManager;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
//import android.media.AudioManager;

import java.io.File;
import java.io.IOException;
import java.lang.ref.WeakReference;
/**
 *
 * low delay client player class
 * @author l00203185
 *
 */
public class libahplayer
{
    private static final int MEDIA_NOP = 0; // interface test message
    private static final int MEDIA_PREPARED = 1;
    private static final int MEDIA_PLAYBACK_INFO = 2;
    private static final int MEDIA_BUFFERING_UPDATE = 3;
    private static final int MEDIA_SEEK_COMPLETE = 4;
    private static final int MEDIA_SET_VIDEO_SIZE = 5;
    private static final int MEDIA_ERROR = 100;
    private static final int MEDIA_INFO = 200;
    private static final int MEDIA_ASR_CHANGE = 300;
    private final static String         TAG = "MediaPlayer";

    private int                         mNativeContext; // accessed by native methods
    //private int                         mListenerContext; // accessed by native methods
    private Surface                     mSurface; // accessed by native methods
    private int mNativeSurfaceTexture;  // accessed by native methods
    private SurfaceHolder                  mSurfaceHolder;
    private static AudioTrack                     mAudioTrack = null;
    private PowerManager.WakeLock         mWakeLock = null;
    private boolean                     mScreenOnWhilePlaying;
    private boolean                     mStayAwake;
    private boolean                     mSuspended;
    private static libahplayerListener mLibahplayerListener;
    private File dir;
    private String path;
    private String filename = "PlayerConfig.txt";
    static {
        native_init();
    }
    /**
     * Called from native code when an interesting event happens.  This method
     * just uses the EventHandler system to post the event back to the main app thread.
     * We use a weak reference to the original MediaPlayer object so that the native
     * code is safe from the object disappearing from underneath it.  (This is
     * the cookie passed to native_setup().)
     */
    private static void postEventFromNative(Object mediaplayer_ref,
                                            int what, int arg1, int arg2, Object obj)
    {
        switch(what) {
        case MEDIA_INFO_FRAMERATE_VIDEO:
            Log.d(TAG, "Video fps:" + arg1);
            break;
        case MEDIA_INFO_FRAMERATE_AUDIO:
            Log.d(TAG, "Audio fps:" + arg1);
            break;
        case MEDIA_PLAYBACK_INFO:
            switch(arg1)
            {
                case MEDIA_PLAYBACK_COMPLETED:
                    Log.d(TAG,"Playback Complete~");
                    libahplayer tmpPlayer = (libahplayer)((WeakReference)mediaplayer_ref).get();
                    tmpPlayer.suspend();
                    if(mLibahplayerListener != null)
                    {
                        mLibahplayerListener.onStop((libahplayer)((WeakReference)mediaplayer_ref).get());
                    }
                    break;
                case MEDIA_PLAYBACK_PREPARED:
                    Log.d(TAG,"Playback Prepared~");
                    if(mLibahplayerListener != null)
                    {
                        mLibahplayerListener.onPrepare((libahplayer)((WeakReference)mediaplayer_ref).get());
                    }
                    break;
            }
            break;
        case MEDIA_ERROR:
            switch (arg1)
            {
                case MEDIA_ERROR_UNKNOWN:
                    {
                        //mLibahplayerListener.onError((libahplayer)((WeakReference)mediaplayer_ref).get(),"libahPlayer Error~", new Exception("libahPlayer Error~"));
                    }
                    break;
                case MEDIA_ERROR_SERVER_DIED:
                    Log.d(TAG,"libahPlayer Error MEDIA_ERROR_SERVER_DIED~");

                    if(mLibahplayerListener != null)
                    {
                        Log.d(TAG,"libahPlayer onError ~");
                        mLibahplayerListener.onError((libahplayer)((WeakReference)mediaplayer_ref).get(),"libahPlayer Error~", new Exception("libahPlayer Error~"));
                    }
                    break;

                            default:
                                break;
            }
            break;
        case MEDIA_ASR_CHANGE:
        if(mLibahplayerListener != null)
        {
                mLibahplayerListener.onASRChange((libahplayer)((WeakReference)mediaplayer_ref).get());
        }
        }
    }

    private static final int MEDIA_PLAYBACK_PREPARED = 1;
    private static final int MEDIA_PLAYBACK_COMPLETED = 0;


    /** Unspecified media player error.
     * @see android.media.MediaPlayer.OnErrorListener
     */
    public static final int MEDIA_ERROR_UNKNOWN = 1;

    /** Media server died. In this case, the application must release the
     * MediaPlayer object and instantiate a new one.
     * @see android.media.MediaPlayer.OnErrorListener
     */
    public static final int MEDIA_ERROR_SERVER_DIED = 100;

    /** The video is streamed and its container is not valid for progressive
     * playback i.e the video's index (e.g moov atom) is not at the start of the
     * file.
     * @see android.media.MediaPlayer.OnErrorListener
     */
    public static final int MEDIA_ERROR_NOT_VALID_FOR_PROGRESSIVE_PLAYBACK = 200;


    /** Unspecified media player info.
     * @see android.media.MediaPlayer.OnInfoListener
     */
    public static final int MEDIA_INFO_UNKNOWN = 1;

    /** The video is too complex for the decoder: it can't decode frames fast
     *  enough. Possibly only the audio plays fine at this stage.
     * @see android.media.MediaPlayer.OnInfoListener
     */
    public static final int MEDIA_INFO_VIDEO_TRACK_LAGGING = 700;

    /** Bad interleaving means that a media has been improperly interleaved or
     * not interleaved at all, e.g has all the video samples first then all the
     * audio ones. Video is playing but a lot of disk seeks may be happening.
     * @see android.media.MediaPlayer.OnInfoListener
     */
    public static final int MEDIA_INFO_BAD_INTERLEAVING = 800;

    /** The media cannot be seeked (e.g live stream)
     * @see android.media.MediaPlayer.OnInfoListener
     */
    public static final int MEDIA_INFO_NOT_SEEKABLE = 801;

    /** A new set of metadata is available.
     * @see android.media.MediaPlayer.OnInfoListener
     */
    public static final int MEDIA_INFO_METADATA_UPDATE = 802;

    public static final int MEDIA_INFO_FRAMERATE_VIDEO = 900;
    public static final int MEDIA_INFO_FRAMERATE_AUDIO = 901;

    /**
     * constructor of player , with para weak reference of player to native
     */
    public libahplayer() {
        /* Native setup requires a weak reference to our object.
         * It's easier to create it here than in C++.
         */
        mAudioTrack = null;
        mLibahplayerListener = null;
        mSuspended = false;
        native_setup(new WeakReference<libahplayer>(this));
    }
    /**
     * interface for event response of main thread
     * @author x54178
     *
     */
    public interface libahplayerListener {
        public void onPrepare(libahplayer mplayer);
        public void onStop(libahplayer mplayer);
        public void onRelease(libahplayer mplayer);
        public void onError(libahplayer mplayer,String msg, Exception e);
        public void onASRChange(libahplayer mplayer);
        public void onFinish(libahplayer mplayer);
    }

    /**
     *
     * @param listener
    /**
     * @param listener: object of event handlr of main thread
     */
    public void setLibahplayerListener(libahplayerListener listener)
    {
        mLibahplayerListener = listener;
    }


    /**
     * Sets the SurfaceHolder to use for displaying the video portion of the media.
     * This call is optional. Not calling it when playing back a video will
     * result in only the audio track being played.
     *
     * @param sh the SurfaceHolder to use for video display
     * @throws IOException
     */
    public void setDisplay(SurfaceHolder sh) throws IOException {
        mSurfaceHolder = sh;
        if (sh != null) {
            mSurface = sh.getSurface();
        } else {
            mSurface = null;
        }
        String osVersion = android.os.Build.VERSION.SDK;
        Log.e(TAG, osVersion);
        _setVideoSurface(mSurface,Integer.valueOf(osVersion));
        //_setVideoSurface(mSurface);
        stayAwake(true);
        setScreenOnWhilePlaying(true);
        updateSurfaceScreenOn();
    }

    /**
     * interface of Audio Track to writing in pcm audio data
     * @param byteArray PCM data
     */
    private static void writePCM(byte[] byteArray)
    {
        //Log.d(TAG,"writePCM "+ byteArray.length);
        if(mAudioTrack!= null && AudioTrack.PLAYSTATE_PLAYING == mAudioTrack.getPlayState())
            mAudioTrack.write(byteArray, 0, byteArray.length);
        //Log.d(TAG,"writePCM OK");
    }
    /**
     * config attributes of AudioTrack and run it.
     * @param streamType eg:STREAM_VOICE_CALL, STREAM_SYSTEM, STREAM_RING, STREAM_MUSIC and STREAM_ALARM
     * @param sampleRate eg:48000,44100etc.
     * @param channelConfig channel num eg:1,2,5 etc
     * @param bytesPerSample bandwidth eg: 2,3 etc
     * @param trackMode    file or stream
     * @return broadcast delay
     */
    private static int configATrack(int streamType, int sampleRate, int channelConfig,int bytesPerSample,int trackMode )
    {
        int latency = 0;
        int chanConfig = (channelConfig == 2)?(AudioFormat.CHANNEL_CONFIGURATION_MONO):(AudioFormat.CHANNEL_CONFIGURATION_STEREO);
        // Get the AudioTrack minimum buffer size
        int iMinBufSize = AudioTrack.getMinBufferSize(sampleRate,
                chanConfig,bytesPerSample);
        Log.d(TAG,"iMinBufSize" + iMinBufSize);
        if ( iMinBufSize == AudioTrack.ERROR_BAD_VALUE || iMinBufSize == AudioTrack.ERROR )
        {
            return 0;
        }
        // Constructor a AudioTrack object
        try
        {
            mAudioTrack = new AudioTrack(streamType, sampleRate,
                    chanConfig,
                    bytesPerSample,
                      iMinBufSize*4,
                      trackMode
                      );
            Log.d(TAG,"mAudioTrack OK" + streamType + sampleRate + chanConfig + bytesPerSample + iMinBufSize*2 + trackMode);
            mAudioTrack.play();
            latency = (int) (iMinBufSize*4.0*1000/bytesPerSample/sampleRate/channelConfig);
            Log.d(TAG,"mAudioTrack play OK");
        }
        catch (IllegalArgumentException iae)
        {
            Log.d(TAG,"new AudioTrack Exceeption:" + iae.toString());
        }
        return latency;
    }
    /**
     *
     **/
    /**
     * Start play service.
     * @throws IllegalStateException if it is called in an invalid state
     */
    public  void start() throws IllegalStateException {
        //stayAwake(true);
        if(mAudioTrack != null)
        {
            mAudioTrack.play();
        }
        _start();
    }

    /**
     * Stops playback after playback has been stopped or paused.
     *
     * @throws IllegalStateException if the internal player engine has not been
     * initialized.
     */
    public void stop() throws IllegalStateException {
        //stayAwake(false);
        suspend();
    }


    /**
     * current no use
     * @throws IllegalStateException if the internal player engine has not been
     * initialized.
     */
    public void pause() throws IllegalStateException {
        //stayAwake(false);
        if(mAudioTrack != null)
        {
            mAudioTrack.pause();
        }
        _pause();
    }

    /**
     * Set the low-level power management behavior for this MediaPlayer.  This
     * can be used when the MediaPlayer is not playing through a SurfaceHolder
     * set with {@link #setDisplay(SurfaceHolder)} and thus can use the
     * high-level {@link #setScreenOnWhilePlaying(boolean)} feature.
     *
     * <p>This function has the MediaPlayer access the low-level power manager
     * service to control the device's power usage while playing is occurring.
     * The parameter is a combination of {@link android.os.PowerManager} wake flags.
     * Use of this method requires {@link android.Manifest.permission#WAKE_LOCK}
     * permission.
     * By default, no attempt is made to keep the device awake during playback.
     *
     * @param context the Context to use
     * @param mode    the power/wake mode to set
     * @see android.os.PowerManager
     */

    public void setWakeMode(Context context, int mode) {
        boolean washeld = false;
        if (mWakeLock != null) {
            if (mWakeLock.isHeld()) {
                washeld = true;
                mWakeLock.release();
            }
            mWakeLock = null;
        }

        PowerManager pm = (PowerManager)context.getSystemService(Context.POWER_SERVICE);
        mWakeLock = pm.newWakeLock(mode|PowerManager.ON_AFTER_RELEASE, libahplayer.class.getName());
        mWakeLock.setReferenceCounted(false);
        if (washeld) {
            mWakeLock.acquire();
        }
    }


    /**
     * Control whether we should use the attached SurfaceHolder to keep the
     * screen on while video playback is occurring.  This is the preferred
     * method over {@link #setWakeMode} where possible, since it doesn't
     * require that the application have permission for low-level wake lock
     * access.
     *
     * @param screenOn Supply true to keep the screen on, false to allow it
     * to turn off.
     */
    public void setScreenOnWhilePlaying(boolean screenOn) {
        if (mScreenOnWhilePlaying != screenOn) {
            mScreenOnWhilePlaying = screenOn;
            updateSurfaceScreenOn();
        }
    }


    private void stayAwake(boolean awake) {
        if (mWakeLock != null) {
            if (awake && !mWakeLock.isHeld()) {
                mWakeLock.acquire();
            } else if (!awake && mWakeLock.isHeld()) {
                mWakeLock.release();
            }
        }
        mStayAwake = awake;
        updateSurfaceScreenOn();
    }



    /**
     * set surface display , not interupt by sleep of phone/pad
     */
    private void updateSurfaceScreenOn() {
        if (mSurfaceHolder != null) {
            mSurfaceHolder.setKeepScreenOn(mScreenOnWhilePlaying && mStayAwake);
        }
    }


    /**
     * Update the MediaPlayer ISurface. Call after updating mSurface.
     */
    private native void _setVideoSurface(Surface surface,int apiVersion) throws IOException;
    //private native void _setVideoSurface(Surface surface) throws IOException;
    /**
     * Sets the data source (file-path or http/rtsp URL) to use.
     *
     * @param path the path of the file you want to play
     * @throws IllegalStateException if it is called in an invalid state
     */
    public native void setDataSource(String path) throws IOException, IllegalArgumentException, IllegalStateException;

    /**
     * Prepares the player for playback, synchronously.
     *
     * After setting the datasource and the display surface, you need to either
     * call prepare(). For files, it is OK to call prepare(),
     * which blocks until MediaPlayer is ready for playback.
     *
     * @throws IllegalStateException if it is called in an invalid state
     */
    public native void prepare() throws IOException, IllegalStateException;

    /**
     * start play
     */
    private native void _start() throws IllegalStateException;
    /**
     *
     * @throws IllegalStateException
     */
    private native void _stop() throws IllegalStateException;
    /**
     *
     * @throws IllegalStateException
     */
    private native void _pause() throws IllegalStateException;

    /**
     * Returns the width of the video.
     *
     * @return the width of the video, or 0 if there is no video,
     * no display surface was set, or the width has not been determined
     * yet.
     */
    public native int getVideoWidth();

    /**
     * Returns the height of the video.
     *
     * @return the height of the video, or 0 if there is no video,
     * no display surface was set, or the height has not been determined
     * yet. The OnVideoSizeChangedListener can be registered via
     * {@link #setOnVideoSizeChangedListener(OnVideoSizeChangedListener)}
     * to provide a notification when the height is available.
     */
    public native int getVideoHeight();
    /**
     * no use
     * @return
     */
    public native float getVideoAspectRatio();
    /**
     * no use
     * Checks whether the MediaPlayer is playing.
     *
     * @return true if currently playing, false otherwise
     */
    public native boolean isPlaying();

    /**
     * no use
     * Seeks to specified time position.
     *
     * @param msec the offset in milliseconds from the start to seek to
     * @throws IllegalStateException if the internal player engine has not been
     * initialized
     */
    public native void seekTo(int msec) throws IllegalStateException;

    /**
     * no use
     * Gets the current playback position.
     *
     * @return the current position in milliseconds
     */
    public native int getCurrentPosition();

    /**
     * no use
     * Gets the duration of the file.
     *
     * @return the duration in milliseconds
     */
    public native int getDuration();
    /**
     * empty
     */
    private native void _release();
    /**
     * no use
     * empty
     */
    private native void _reset();


    /**
     * suspend or resume, resume are empty, suspend is function of destroy
     * @return Error Code of mediaplayer
     */
    private native int native_suspend_resume(boolean isSuspend);


    /**
     * no use,empty
     */
    public native void setAudioStreamType(int streamtype);



    private static native final void native_init() throws RuntimeException;
    /**
     * create mediaplayer.
     * @param mediaplayer_this: the reference of the java object,using by jni for callback
     */
    private native final void native_setup(Object mediaplayer_this);
    private native final void native_finalize();

    /**
     * no use
     * @param mode:
     *   ** 0
         * Scale in X and Y independently, so that src matches dst exactly.
         * This may change the aspect ratio of the src.
         *
         ** 1
         * Compute a scale that will maintain the original src aspect ratio,
         * but will also ensure that src fits entirely inside dst. At least one
         * axis (X or Y) will fit exactly. kStart aligns the result to the
         * left and top edges of dst.
         *
         ** 2
         * Compute a scale that will maintain the original src aspect ratio,
         * but will also ensure that src fits entirely inside dst. At least one
         * axis (X or Y) will fit exactly. The result is centered inside dst.
         *
         ** 3
         * Compute a scale that will maintain the original src aspect ratio,
         * but will also ensure that src fits entirely inside dst. At least one
         * axis (X or Y) will fit exactly. kEnd aligns the result to the
         * right and bottom edges of dst.
         *
     * @throws IOException
     * @throws IllegalStateException
     */
    public native void setVideoDisplayMode(int mode) throws IOException, IllegalStateException;

    /*
     * call before player setdatasource but after new libahplayer
     * */
    public native void setPlayerConfig(String playerConfig);

    /*
     * call before player setdatasource but after new libahplayer
     * */
    public native int native_getAHSData(Object info,int lastTimeSec);

    /**
     * set screen  not always in light
     */
    public void release() {
        stayAwake(false);
        updateSurfaceScreenOn();
        _release();
    }

    /**
     * empty realize
     */
    public void reset() {
        //stayAwake(false);
        _reset();
    }

    /**
     * Suspends the MediaPlayer. The only methods that may be called while
     * suspended are {@link #reset()}, {@link #release()} and {@link #resume()}.
     * MediaPlayer will release its hardware resources as far as
     * possible and reasonable. A successfully suspended MediaPlayer will
     * cease sending events.
     * If suspension is successful, this method returns true, otherwise
     * false is returned and the player's state is not affected.
     * @hide
     */
    public boolean suspend() {
        if(mSuspended)
            return true;
        mSuspended = true;
        if(mAudioTrack != null)
        mAudioTrack.stop();
        if (native_suspend_resume(true) < 0) {
            return false;
        }
        Log.d(TAG, "suspend OK");
        if(mAudioTrack != null)
            mAudioTrack.release();
        mAudioTrack = null;
        return true;
    }

    /**
     * Resumes the MediaPlayer. Only to be called after a previous (successful)
     * call to {@link #suspend()}.
     * MediaPlayer will return to a state close to what it was in before
     * suspension.
     * @hide
     */
    public boolean resume() {
        if(mAudioTrack != null)
        mAudioTrack.play();
        if (native_suspend_resume(false) < 0) {
            return false;
        }
        return true;
    }
    public AHSMonitorInfo getAHSData(int lastTimeSec)
    {
        AHSMonitorInfo info = new AHSMonitorInfo();
        int ret = native_getAHSData(info,lastTimeSec);
        if(ret == 0)
        {
            return info;
        }
        else
        {
            return null;
        }
    }
    protected void finalize() { native_finalize(); }

}
