package com.hisilicon.android.videoplayer.activity;

import java.io.IOException;
import java.util.List;
import java.util.ArrayList;

import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.PixelFormat;
import android.media.AudioManager;

import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnInfoListener;
import android.media.MediaPlayer.OnPreparedListener;
import android.media.MediaPlayer.OnSeekCompleteListener;
import com.hisilicon.android.mediaplayer.HiMediaPlayerInvoke;
import com.hisilicon.android.mediaplayer.HiMediaPlayer;
import com.hisilicon.android.mediaplayer.HiMediaPlayerDefine;

import com.hisilicon.android.videoplayer.R;
import com.hisilicon.android.videoplayer.util.Common;
import com.hisilicon.android.videoplayer.util.Constants;

import android.net.Uri;
import android.os.Parcel;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.MediaController;
import android.widget.MediaController.MediaPlayerControl;

public class HisiVideoView extends SurfaceView implements MediaPlayerControl
{
    private String TAG = "HisiVideoView";

    private Context mContext;

    private Uri mUri;
    private int mDuration;

    private SurfaceHolder mSurfaceHolder = null;
    public MediaPlayer mMediaPlayer = null;
    private boolean mIsPrepared;
    private int mVideoWidth;
    private int mVideoHeight;
    private int mSurfaceWidth;
    private int mSurfaceHeight;

    private OnCompletionListener mOnCompletionListener;

    private MediaPlayer.OnPreparedListener mOnPreparedListener;
    private int mCurrentBufferPercentage;
    private OnErrorListener mOnErrorListener;
    private OnInfoListener mOn3DModeReceivedListener;
    private boolean mStartWhenPrepared;
    private int mSeekWhenPrepared;
    private String ratioValue = null;
    private String cvrsValue = null;

    private int mSubtitleNumber;

    private int mExtSubtitleNumber;

    private int mAudioTrackNumber;

    private int mSelectSubtitleId = 0;

    private int mSelectAudioTrackId = 0;

    private int mSelectAudioChannelId = 0;

    private List <String> mSubtitleLanguageList;

    private List <String> mExtraSubtitleList;

    private List <String> mAudioTrackLanguageList;

    private List <String> mAudioFormatList;

    private List <String> mAudioSampleRateList;

    private List <String> mAudioChannelList;

    public String[] mSubFormat = {"ASS", "LRC", "SRT", "SMI", "SUB", "TXT", "PGS", "DVB", "DVD"};

    private final static String IMEDIA_PLAYER = "android.media.IMediaPlayer";

    private Surface mSubSurface;

    private final boolean DEBUG = false;

    public int getVideoWidth()
    {
        return mVideoWidth;
    }

    public int getVideoHeight()
    {
        return mVideoHeight;
    }

    public void setVideoScale(int width, int height)
    {
        LayoutParams lp = getLayoutParams();

        lp.width = width;
        mVideoWidth = width;

        lp.height = height;
        mVideoHeight = height;

        setLayoutParams(lp);
    }

    public HisiVideoView(Context context)
    {
        super(context);
        mContext = context;
        initVideoView();
    }

    public HisiVideoView(Context context, AttributeSet attrs)
    {
        this(context, attrs, 0);
        mContext = context;
        initVideoView();
    }

    public HisiVideoView(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
        mContext = context;
        initVideoView();
    }

    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec)
    {
        int width  = getDefaultSize(mVideoWidth, widthMeasureSpec);
        int height = getDefaultSize(mVideoHeight, heightMeasureSpec);

        setMeasuredDimension(width, height);
    }

    public int resolveAdjustedSize(int desiredSize, int measureSpec)
    {
        int result   = desiredSize;
        int specMode = MeasureSpec.getMode(measureSpec);
        int specSize = MeasureSpec.getSize(measureSpec);

        switch (specMode)
        {
        case MeasureSpec.UNSPECIFIED:

            result = desiredSize;
            break;

        case MeasureSpec.AT_MOST:

            result = Math.min(desiredSize, specSize);
            break;

        case MeasureSpec.EXACTLY:

            result = specSize;
            break;
        }

        return result;
    }

    private void initVideoView()
    {
        mVideoWidth  = 0;
        mVideoHeight = 0;
        getHolder().addCallback(mSHCallback);
        getHolder().setType(SurfaceHolder.SURFACE_TYPE_NORMAL);
        getHolder().setFormat(PixelFormat.RGBA_8888);
        setFocusable(true);
        setFocusableInTouchMode(true);
        requestFocus();
    }

    public void setVideoPath(String path)
    {
        path = Common.transferredMeaning(path);
        setVideoURI(Uri.parse(path));
    }

    public void setVideoURI(Uri uri)
    {
        mUri = uri;
        mStartWhenPrepared = false;
        mSeekWhenPrepared = 0;
        openVideo();
        requestLayout();
        invalidate();
    }

    private void setSubtitleSurfaceInvoke(final Surface surface)
    {
        int ret = -1;
        Parcel request = Parcel.obtain();
        Parcel reply = Parcel.obtain();

        request.writeInterfaceToken(IMEDIA_PLAYER);
        request.writeInt(HiMediaPlayerInvoke.CMD_SET_SUB_SURFACE);
        int temp = request.dataPosition();

        if (surface != null)
        {
            surface.writeToParcel(request, 1);
        }
        request.setDataPosition(temp);
        if (DEBUG) Log.i(TAG, " parcel offset " + request.dataPosition() + " is " + request.readString());
        if (DEBUG) Log.i(TAG, " parcel offset " + request.dataPosition() + " is " + request.readStrongBinder());
        request.setDataPosition(temp);
        surface.readFromParcel(request);
        if (DEBUG) Log.i(TAG, " parcel offset " + request.dataPosition() + " is " + surface);

        invoke(request, reply);
        request.setDataPosition(temp);
        surface.readFromParcel(request);
        if (DEBUG) Log.i(TAG, " parcel offset " + request.dataPosition() + " is " + surface);
        reply.setDataPosition(0);
        ret = reply.readInt();
        if (ret != 0){
            Log.e(TAG, "Subtitle Invoke call set failed , ret = " + ret);
        }else
            Log.i(TAG, "Subtitle Invoke Sucessfull !");

        request.recycle();
        reply.recycle();
    }

    public void stopPlayback()
    {
        if (mMediaPlayer != null)
        {
            mMediaPlayer.stop();
            mMediaPlayer.release();
            mMediaPlayer = null;
        }
    }

    public void intVideoValue()
    {
        String[] cloumns = new String[] {
            "value", "flag"
        };

        String[] args = new String[] {
            "14",
            "15"
        };

        ContentResolver cr = mContext.getContentResolver();
        Uri uri  = Uri.parse(Constants.CONTENT_URI);
        Cursor c = null;
        try
        {
            c = cr.query(uri, cloumns, " id in (?,?) ", args, null);
            if ((c != null) && (c.getCount() > 0))
            {
                while (c.moveToNext())
                {
                    String flag = c.getString(c.getColumnIndex("flag"));
                    if (flag.equals("1"))
                    {
                        ratioValue = c.getString(c.getColumnIndex("value"));
                    }
                    else
                    {
                        cvrsValue = c.getString(c.getColumnIndex("value"));
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            if (c != null)
            {
                c.close();
                c = null;
            }
        }
    }

    public void setSubtitleSurface(Surface SubSurface)
    {
        mSubSurface = SubSurface;
    }

    private void openVideo()
    {
        intVideoValue();

        if ((mUri == null) || (mSurfaceHolder == null))
        {
            if (DEBUG) Log.i(TAG, " openVideo return ! ");
            return;
        }

        if (mMediaPlayer != null)
        {
            mMediaPlayer.reset();
            Log.i(TAG, "DataSource :" + mUri);
            try
            {
                mIsPrepared = false;
                mDuration = -1;
                mCurrentBufferPercentage = 0;
                mSelectSubtitleId = 0;
                mSelectAudioTrackId = 0;
                mMediaPlayer.setDataSource(mContext, mUri);

                Surface mSurface;
                mSurface = mSurfaceHolder.getSurface();
                int[] location = new int[2];
                getLocationOnScreen(location);

                int mX, mY, mW, mH;
                if (null != mSurface)
                {
                    mX = location[0];
                    mY = location[1];
                    mW = mVideoWidth;
                    mH = mVideoHeight;
                    // this function not found if MediaPlayer
                    //mMediaPlayer.setVideoRange(mX, mY, mW, mH);
                }
                if(VideoActivity.mFormatAdaption == 1)
                {
                    setStereoStrategy(HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_24FPS_MASK);
                }
                //Subtitle Invoke Call
                if (mSubSurface != null)
                {
                   setSubtitleSurfaceInvoke(mSubSurface);
                }
                else
                {
                    Log.e(TAG, "Error : Before call Subtitle Invoke , the Subtitle Surface is null!");
                }
                if (VideoActivity.m3DMVCAdapte == 1)
                {
                    if (VideoActivity.mFormatAdaption == 1)
                    {
                        setStereoStrategy(HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_ADAPT_MASK+
                                          HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_24FPS_MASK);
                    }
                    else
                    {
                        setStereoStrategy(HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_ADAPT_MASK);
                    }
                }
                else
                {
                    if (VideoActivity.mFormatAdaption == 1)
                    {
                        setStereoStrategy(HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_2D_MASK+
                                          HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_24FPS_MASK);
                    }
                    else
                    {
                        setStereoStrategy(HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_2D_MASK);
                    }
                }
                mMediaPlayer.prepareAsync();
            }
            catch (IOException ex) {
                Log.w(TAG, "Unable to open content: " + mUri, ex);
                return;
            }
            catch (IllegalArgumentException ex) {
                Log.w(TAG, "Unable to open content: " + mUri, ex);
                return;
            }
            return;
        }

        try
        {
            mMediaPlayer = new MediaPlayer();
            mMediaPlayer.setOnPreparedListener(mPreparedListener);
            mMediaPlayer.setOnVideoSizeChangedListener(mSizeChangedListener);
            mMediaPlayer.setOnSeekCompleteListener(mOnSeekCompleteListener);
            mIsPrepared = false;
            mDuration = -1;
            mMediaPlayer.setOnCompletionListener(mCompletionListener);
            mMediaPlayer.setOnInfoListener(m3DModeReceivedListener);
            mMediaPlayer.setOnErrorListener(mErrorListener);
            mMediaPlayer.setOnBufferingUpdateListener(mBufferingUpdateListener);
            mCurrentBufferPercentage = 0;
            mSelectSubtitleId = 0;
            mSelectAudioTrackId = 0;
            mSelectAudioChannelId = 0;
            Log.i(TAG, "DataSource :" + mUri);
            mMediaPlayer.setDataSource(mContext, mUri);
            mSurfaceHolder.setFixedSize(getVideoWidth(), getVideoHeight());
            mMediaPlayer.setDisplay(mSurfaceHolder);
            Surface mSurface;
            mSurface = mSurfaceHolder.getSurface();
            //Subtitle Invoke Call
            if (mSubSurface != null)
            {
               setSubtitleSurfaceInvoke(mSubSurface);
            }
            else
            {
                Log.e(TAG, "Error : Before call Subtitle Invoke , the Subtitle Surface is null!");
            }

            int[] location = new int[2];
            getLocationOnScreen(location);

            int mX, mY, mW, mH;
            if (null != mSurface)
            {
                mX = location[0];
                mY = location[1];
                mW = mVideoWidth;
                mH = mVideoHeight;
                // this function not found if MediaPlayer
                //mMediaPlayer.setVideoRange(mX, mY, mW, mH);
            }

            if(VideoActivity.mFormatAdaption == 1)
            {
                setStereoStrategy(HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_24FPS_MASK);
            }
            //mMediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
            //mMediaPlayer.setScreenOnWhilePlaying(true);
            if (VideoActivity.m3DMVCAdapte == 1)
            {
                    if (VideoActivity.mFormatAdaption == 1)
                    {
                        setStereoStrategy(HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_ADAPT_MASK+
                                          HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_24FPS_MASK);
                    }
                    else
                    {
                        setStereoStrategy(HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_ADAPT_MASK);
                    }
            }
            else
            {
                    if (VideoActivity.mFormatAdaption == 1)
                    {
                        setStereoStrategy(HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_2D_MASK+
                                          HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_24FPS_MASK);
                    }
                    else
                    {
                        setStereoStrategy(HiMediaPlayerDefine.DEFINE_STEREOVIDEO_STRATEGY_2D_MASK);
                    }
            }
            mMediaPlayer.prepareAsync();
        } catch (IOException ex) {
            Log.w(TAG, "Unable to open content: " + mUri, ex);
            return;
        } catch (IllegalArgumentException ex) {
            Log.w(TAG, "Unable to open content: " + mUri, ex);
            return;
        }
    }

    MediaPlayer.OnVideoSizeChangedListener mSizeChangedListener =
        new MediaPlayer.OnVideoSizeChangedListener()
    {
        public void onVideoSizeChanged(MediaPlayer mp, int width, int height)
        {
            if ((mVideoWidth != 0) && (mVideoHeight != 0))
            {}
        }
    };

    MediaPlayer.OnPreparedListener mPreparedListener = new MediaPlayer.OnPreparedListener()
    {
        public void onPrepared(MediaPlayer mp)
        {
            mIsPrepared = true;
            if (mOnPreparedListener != null)
            {
                mOnPreparedListener.onPrepared(mMediaPlayer);
                return;
            }

            mVideoWidth  = mp.getVideoWidth();
            mVideoHeight = mp.getVideoHeight();

            if ((mVideoWidth != 0) && (mVideoHeight != 0))
            {
                getHolder().setFixedSize(mVideoWidth, mVideoHeight);

                if (mSeekWhenPrepared != 0)
                {
                    mMediaPlayer.seekTo(mSeekWhenPrepared);
                    mSeekWhenPrepared = 0;
                }

                if (mStartWhenPrepared)
                {
                    mMediaPlayer.start();
                    mStartWhenPrepared = false;
                }
            }
            else
            {
                if (mSeekWhenPrepared != 0)
                {
                    mMediaPlayer.seekTo(mSeekWhenPrepared);
                    mSeekWhenPrepared = 0;
                }

                if (mStartWhenPrepared)
                {
                    mMediaPlayer.start();
                    mStartWhenPrepared = false;
                }
            }
        }
    };

    private MediaPlayer.OnCompletionListener mCompletionListener =
        new MediaPlayer.OnCompletionListener()
    {
        public void onCompletion(MediaPlayer mp)
        {
            if (mOnCompletionListener != null)
            {
                mOnCompletionListener.onCompletion(mMediaPlayer);
            }
        }
    };

	private MediaPlayer.OnSeekCompleteListener mOnSeekCompleteListener =
        new MediaPlayer.OnSeekCompleteListener()
    {
        public void onSeekComplete(MediaPlayer mp)
        {
            if (mOnSeekCompleteListener != null)
            {
                mOnSeekCompleteListener.onSeekComplete(mMediaPlayer);
            }
        }
    };

    private MediaPlayer.OnInfoListener m3DModeReceivedListener =
        new MediaPlayer.OnInfoListener()
    {
        public boolean onInfo(MediaPlayer mp, int what, int extra)
        {
            if (mOn3DModeReceivedListener != null)
            {
                return mOn3DModeReceivedListener.onInfo(mMediaPlayer, what, extra);
            }

            return false;
        }
    };

    private MediaPlayer.OnErrorListener mErrorListener =
        new MediaPlayer.OnErrorListener()
    {
        public boolean onError(MediaPlayer mp, int framework_err, int impl_err)
        {
            Log.d(TAG, "Error: " + framework_err + "," + impl_err);

            if (mOnErrorListener != null)
            {
                if (mOnErrorListener.onError(mMediaPlayer, framework_err, impl_err))
                {
                    return true;
                }
            }

            if (getWindowToken() != null)
            {}

            return true;
        }
    };

    private MediaPlayer.OnBufferingUpdateListener mBufferingUpdateListener =
        new MediaPlayer.OnBufferingUpdateListener()
    {
        public void onBufferingUpdate(MediaPlayer mp, int percent)
        {
            mCurrentBufferPercentage = percent;
        }
    };

    public void setOnPreparedListener(MediaPlayer.OnPreparedListener l)
    {
        mOnPreparedListener = l;
    }

    public void setOnCompletionListener(OnCompletionListener l)
    {
        mOnCompletionListener = l;
    }

	public void setOnSeekCompleteListener(OnSeekCompleteListener l)
    {
        mOnSeekCompleteListener = l;
    }

    public void setOn3DModeReceivedListener(OnInfoListener l)
    {
        mOn3DModeReceivedListener = l;
    }

    public void setOnErrorListener(OnErrorListener l)
    {
        mOnErrorListener = l;
    }

    SurfaceHolder.Callback mSHCallback = new SurfaceHolder.Callback()
    {
        public void surfaceChanged(SurfaceHolder holder, int format,
                                   int w, int h)
        {
            mSurfaceWidth  = w;
            mSurfaceHeight = h;
            if ((mMediaPlayer != null) && mIsPrepared && (mVideoWidth == w) && (mVideoHeight == h))
            {
                if (mSeekWhenPrepared != 0)
                {
                    mMediaPlayer.seekTo(mSeekWhenPrepared);
                    mSeekWhenPrepared = 0;
                }
            }
        }

        public void surfaceCreated(SurfaceHolder holder)
        {
            mSurfaceHolder = holder;
            openVideo();
        }

        public void surfaceDestroyed(SurfaceHolder holder)
        {
            destroyPlayer();
        }
    };

    public void invoke(Parcel request, Parcel reply)
    {
        if ((mMediaPlayer != null))
        {
            mMediaPlayer.invoke(request, reply);
        }
    }

    public void resume()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            play();
            Common.isResume = true;
        }
    }

    public void play()
    {
        Parcel requestParcel = Parcel.obtain();

        requestParcel.writeInterfaceToken(IMEDIA_PLAYER);
        requestParcel.writeInt(HiMediaPlayerInvoke.CMD_SET_STOP_FASTPLAY);
        Parcel replyParcel = Parcel.obtain();
        invoke(requestParcel, replyParcel);

        requestParcel.recycle();
        replyParcel.recycle();
    }

    public void start()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            mMediaPlayer.start();
            mStartWhenPrepared = false;
        }
        else
        {
            mStartWhenPrepared = true;
        }
    }
    public void reset()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            mMediaPlayer.reset();
        }
    }
    public void pause()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            if (mMediaPlayer.isPlaying())
            {
                mMediaPlayer.pause();
            }
        }

        mStartWhenPrepared = false;
    }

    public int getDuration()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            if (mDuration > 0)
            {
                return mDuration;
            }

            mDuration = mMediaPlayer.getDuration();
            return mDuration;
        }

        mDuration = -1;
        return mDuration;
    }

    public int getCurrentPosition()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            return mMediaPlayer.getCurrentPosition();
        }

        return 0;
    }

    public void seekTo(int msec)
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            mMediaPlayer.seekTo(msec);
        }
        else
        {
            mSeekWhenPrepared = msec;
        }
    }

    public void setSpeed(int speed)
    {
        int flag = 0;

        if ((mMediaPlayer != null) && mIsPrepared)
        {

            if(speed == 1)
            {
                flag = HiMediaPlayerInvoke.CMD_SET_STOP_FASTPLAY;
            }
            else if (speed == 2 || speed == 4 || speed == 8 || speed == 16 || speed == 32)
            {
                flag = HiMediaPlayerInvoke.CMD_SET_FORWORD;
            }
            else if (speed == -2 || speed == -4 || speed == -8 || speed == -16 || speed == -32)
            {
                flag  = HiMediaPlayerInvoke.CMD_SET_REWIND;
                speed = -speed;
            }
            else
            {
                Log.e(TAG,"setSpeed error:"+speed);
            }
            excuteCommand(flag, speed, false);
        }
    }

    private int excuteCommand(int pCmdId, int pArg, boolean pIsGet)
    {
        Parcel Request = Parcel.obtain();
        Parcel Reply = Parcel.obtain();

        Request.writeInterfaceToken(IMEDIA_PLAYER);
        Request.writeInt(pCmdId);
        Request.writeInt(pArg);

        invoke(Request, Reply);

        if (pIsGet)
        {
            Reply.readInt();
        }

        int Result = Reply.readInt();

        Request.recycle();
        Reply.recycle();

        return Result;
    }

    public boolean isPlaying()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            return mMediaPlayer.isPlaying();
        }

        return false;
    }

    public int getBufferPercentage()
    {
        if (mMediaPlayer != null)
        {
            return mCurrentBufferPercentage;
        }

        return 0;
    }

    public int setStereoVideoFmt(int inVideoFmt)
    {
        if (mMediaPlayer != null)
        {
            return setStereoVideoFmtInvoke(inVideoFmt);
        }
        Log.e(TAG, "setStereoVideoFmt mMediaPlayer == null, return -1");
        return -1;
    }

    public int setStereoStrategy(int strategy)
    {
        if (mMediaPlayer != null)
        {
            return setStereoStrategyInvoke(strategy);
        }
        Log.e(TAG, "setStereoStrategy mMediaPlayer == null , return -1");
        return -1;
    }

    public int setStereoStrategyInvoke(int strategy)
    {
        int ret = -1;
        if (mMediaPlayer != null)
        {
            Parcel request = Parcel.obtain();
            Parcel reply = Parcel.obtain();
            request.writeInterfaceToken(IMEDIA_PLAYER);
            request.writeInt(HiMediaPlayerInvoke.CMD_SET_3D_STRATEGY);
            request.writeInt(strategy);

            invoke(request, reply);
            reply.setDataPosition(0);
            ret = reply.readInt();

            if (ret != 0)
                Log.e(TAG, "setStereoStrategyInvoke Failed !");

            request.recycle();
            reply.recycle();
        }
        return ret;
    }

    public int setStereoVideoFmtInvoke(int inVideoFmt)
    {
        int ret = -1;
        if (mMediaPlayer != null)
        {
            Parcel request = Parcel.obtain();
            Parcel reply = Parcel.obtain();
            request.writeInterfaceToken(IMEDIA_PLAYER);
            request.writeInt(HiMediaPlayerInvoke.CMD_SET_3D_FORMAT);
            request.writeInt(inVideoFmt);

            invoke(request, reply);
            reply.setDataPosition(0);
            ret = reply.readInt();

            if (ret != 0)
                Log.e(TAG, "setStereoVideoFmtInvoke Failed !");

            request.recycle();
            reply.recycle();
        }
        return ret;
    }


    public Parcel getMediaInfo()
    {
        if (mMediaPlayer != null)
        {
            int flag = HiMediaPlayerInvoke.CMD_GET_FILE_INFO;
            Parcel Request = Parcel.obtain();
            Parcel Reply = Parcel.obtain();

            Request.writeInterfaceToken(IMEDIA_PLAYER);
            Request.writeInt(flag);

            invoke(Request, Reply);

            Reply.setDataPosition(0);

            Request.recycle();

            return Reply;

        }
        return null;
    }
    public int setVideoCvrs(int flag)
    {
        if (mMediaPlayer != null)
        {
            Parcel Request = Parcel.obtain();
            Parcel Reply = Parcel.obtain();

            Request.writeInterfaceToken(IMEDIA_PLAYER);
            Request.writeInt(HiMediaPlayerInvoke.CMD_SET_VIDEO_CVRS);
            Request.writeInt(flag);

            invoke(Request, Reply);

            Reply.readInt();

            int Result = Reply.readInt();

            Request.recycle();
            Reply.recycle();

            return Result;
        }

        return -1;
    }
    public synchronized List <String> getAudioInfoList()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            Parcel _Request = Parcel.obtain();
            Parcel _Reply = Parcel.obtain();

            _Request.writeInterfaceToken(IMEDIA_PLAYER);
            _Request.writeInt(HiMediaPlayerInvoke.CMD_GET_AUDIO_INFO);

            mMediaPlayer.invoke(_Request, _Reply);

            List <String> _AudioInfoList = new ArrayList <String>();

            // for get
            _Reply.readInt();
            int _Num = _Reply.readInt();
            String _Language = "";
            String _Format = "";
            String _SampleRate = "";
            String _Channel = "";

            for (int i = 0; i < _Num; i++)
            {
                _Language = _Reply.readString();
                if (_Language == null || _Language.equals("und"))
                {
                    _Language = "";
                }

                _AudioInfoList.add(_Language);

                _Format = Integer.toString(_Reply.readInt());
                _AudioInfoList.add(_Format);

                _SampleRate = Integer.toString(_Reply.readInt());
                _AudioInfoList.add(_SampleRate);

                int _ChannelNum = _Reply.readInt();
                switch (_ChannelNum)
                {
                case 0:
                case 1:
                case 2:
                    _Channel = _ChannelNum + ".0";
                    break;
                default:
                    _Channel = (_ChannelNum - 1) + ".1";
                    break;
                }

                _AudioInfoList.add(_Channel);
            }

            _Request.recycle();
            _Reply.recycle();

            return _AudioInfoList;
        }

        return null;
    }

    public int getAudioTrackNumber()
    {
        return mAudioTrackNumber;
    }

    public void setAudioTrackNumber(int pAudioTrackNumber)
    {
        mAudioTrackNumber = pAudioTrackNumber;
    }

    public int getSelectAudioTrackId()
    {
        return mSelectAudioTrackId;
    }

    public void setSelectAudioTrackId(int pSelectAudioTrackId)
    {
        mSelectAudioTrackId = pSelectAudioTrackId;
    }

    public int getSelectAudioChannelId()
    {
        return mSelectAudioChannelId;
    }

    public void setSelectAudioChannelId(int pSelectAudioChannelId)
    {
        mSelectAudioChannelId = pSelectAudioChannelId;
    }

    public List <String> getAudioTrackLanguageList()
    {
        return mAudioTrackLanguageList;
    }

    public void setAudioTrackLanguageList(List < String > pAudioTrackLanguageList)
    {
        mAudioTrackLanguageList = pAudioTrackLanguageList;
    }

    public List <String> getAudioFormatList()
    {
        return mAudioFormatList;
    }

    public void setAudioFormatList(List < String > pAudioFormatList)
    {
        mAudioFormatList = pAudioFormatList;
    }

    public List <String> getAudioSampleRateList()
    {
        return mAudioSampleRateList;
    }

    public void setAudioSampleRateList(List < String > pAudioSampleRateList)
    {
        mAudioSampleRateList = pAudioSampleRateList;
    }

    public List <String> getAudioChannelList()
    {
        return mAudioChannelList;
    }

    public int setAudioTrackPid(int pAudioId)
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            return setAudioTrack(pAudioId);
        }

        return -1;
    }

    public int setAudioTrack(int track)
    {
        int flag = HiMediaPlayerInvoke.CMD_SET_AUDIO_TRACK_PID;

        return excuteCommand(flag, track, false);
    }


    public int getAudioChannelPid()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            Parcel _Request = Parcel.obtain();
            Parcel _Reply = Parcel.obtain();

            _Request.writeInterfaceToken(IMEDIA_PLAYER);
            _Request.writeInt(HiMediaPlayerInvoke.CMD_GET_AUDIO_CHANNEL_MODE);

            mMediaPlayer.invoke(_Request, _Reply);

            _Reply.setDataPosition(0);
            _Reply.readInt();
            int ChannelPid = _Reply.readInt();

            _Request.recycle();
            _Reply.recycle();

            return ChannelPid;
        }

        return -1;
    }

    public int setAudioChannelPid(int pAudioChannelId)
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            return setAudioChannel(pAudioChannelId);
        }

        return -1;
    }

    public int setAudioChannel(int channel)
    {
        int flag = HiMediaPlayerInvoke.CMD_SET_AUDIO_CHANNEL_MODE;

        return excuteCommand(flag, channel, false);
    }


    public void setAudioChannelList(List < String > pAudioChannelList)
    {
        mAudioChannelList = pAudioChannelList;
    }

    public List <String> getInternalSubtitleLanguageInfoList()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            Parcel _Request = Parcel.obtain();
            Parcel _Reply = Parcel.obtain();

            _Request.writeInterfaceToken(IMEDIA_PLAYER);
            _Request.writeInt(HiMediaPlayerInvoke.CMD_GET_SUB_INFO);

            mMediaPlayer.invoke(_Request, _Reply);

            List <String> _LanguageList = new ArrayList <String>();

            // for get
            _Reply.readInt();
            int _Num = _Reply.readInt();
            String _Language = "";
            String _SubFormat = "";
            int _IsExt = 0;

            for (int i = 0; i < _Num; i++)
            {
                _Reply.readInt();
                _IsExt = _Reply.readInt();
                _Language = _Reply.readString();
                _SubFormat = mSubFormat[_Reply.readInt()];
                if (_Language == null  || _Language.equals("-"))
                {
                    _Language = "";
                }
                if (_IsExt == 0)
                {
                    _LanguageList.add(_SubFormat);
                    _LanguageList.add(_Language);
                }
            }

            _Request.recycle();
            _Reply.recycle();

            return _LanguageList;
        }

        return new ArrayList <String>();
    }

    public int setDolbyCertification(int start,int end)
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            Parcel _Request = Parcel.obtain();
            Parcel _Reply = Parcel.obtain();

            _Request.writeInterfaceToken(IMEDIA_PLAYER);
            _Request.writeInt(HiMediaPlayerInvoke.CMD_SET_AVSYNC_START_REGION);
            _Request.writeInt(start);
            _Request.writeInt(end);

            mMediaPlayer.invoke(_Request, _Reply);

            _Reply.setDataPosition(0);
            int  result  = _Reply.readInt();

            _Request.recycle();
            _Reply.recycle();

            return result;
        }

        return -1;
    }

    public int setDolbyDacDectUnable(int unable)
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            Parcel _Request = Parcel.obtain();
            Parcel _Reply = Parcel.obtain();

            _Request.writeInterfaceToken(IMEDIA_PLAYER);
            _Request.writeInt(HiMediaPlayerInvoke.CMD_SET_DAC_DECT_ENABLE);
            _Request.writeInt(unable);

            mMediaPlayer.invoke(_Request, _Reply);
            _Reply.setDataPosition(0);
            int  result  = _Reply.readInt();

            _Request.recycle();
            _Reply.recycle();

            return result;
        }

        return -1;
    }

    public List <String> getExtSubtitleLanguageInfoList()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            Parcel _Request = Parcel.obtain();
            Parcel _Reply = Parcel.obtain();

            _Request.writeInterfaceToken(IMEDIA_PLAYER);
            _Request.writeInt(HiMediaPlayerInvoke.CMD_GET_SUB_INFO);

            mMediaPlayer.invoke(_Request, _Reply);

            List <String> _LanguageList = new ArrayList <String>();

            // for get
            _Reply.readInt();
            int _Num = _Reply.readInt();
            String _Language = "";
            String _SubFormat = "";
            int _IsExt = 0;

            for (int i = 0; i < _Num; i++)
            {
                _Reply.readInt();
                _IsExt = _Reply.readInt();
                _Language = _Reply.readString();
                _SubFormat = mSubFormat[_Reply.readInt()];
                if (_Language == null || _Language.equals("-"))
                {
                    _Language = "";
                }
                if (_IsExt == 1)
                {
                    _LanguageList.add(_SubFormat);
                    _LanguageList.add(_Language);
                }
            }

            _Request.recycle();
            _Reply.recycle();

            return _LanguageList;
        }

        return new ArrayList <String>();
    }

    public int getSubtitleNumber()
    {
        return mSubtitleNumber;
    }

    public void setSubtitleNumber(int pSubtitleNumber)
    {
        mSubtitleNumber = pSubtitleNumber;
    }

    public int getExtSubtitleNumber()
    {
        return mExtSubtitleNumber;
    }

    public void setExtSubtitleNumber(int pExtSubtitleNumber)
    {
        mExtSubtitleNumber = pExtSubtitleNumber;
    }

    public int getSelectSubtitleId()
    {
        return mSelectSubtitleId;
    }

    public void setSelectSubtitleId(int pSelectSubtitleId)
    {
        mSelectSubtitleId = pSelectSubtitleId;
    }

    public List <String> getSubtitleLanguageList()
    {
        return mSubtitleLanguageList;
    }

    public void setSubtitleLanguageList(List < String > pSubtitleLanguageList)
    {
        mSubtitleLanguageList = pSubtitleLanguageList;
    }

    public List <String> getExtraSubtitleList()
    {
        return mExtraSubtitleList;
    }

    public void setExtraSubtitleList(List < String > pExtraSubtitleList)
    {
        mExtraSubtitleList = pExtraSubtitleList;
    }

    public int enableSubtitle(int enable)
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            return enableSubtitleInvoke(enable);
        }

        return -1;
    }

    public int enableSubtitleInvoke(int enable)
    {
        int flag = HiMediaPlayerInvoke.CMD_SET_SUB_DISABLE;

        return excuteCommand(flag, enable, false);
    }


    public int setSubVertical(int position)
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            return setSubVerticalInvoke(position);
        }

        return -1;
    }

    public int setSubVerticalInvoke(int position)
    {
        int flag = HiMediaPlayerInvoke.CMD_SET_SUB_FONT_VERTICAL;

        return excuteCommand(flag, position, false);
    }


    public int getSubtitleId()
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            Parcel Request = Parcel.obtain();
            Parcel Reply = Parcel.obtain();

            Request.writeInterfaceToken(IMEDIA_PLAYER);
            Request.writeInt(HiMediaPlayerInvoke.CMD_GET_SUB_ID);

            invoke(Request, Reply);

            Reply.readInt();
            int Result = Reply.readInt();

            Request.recycle();
            Reply.recycle();

            return Result;
        }

        return -1;
    }

    public int setSubtitleId(int pSubtitleId)
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            return setSubTrack(pSubtitleId);
        }

        return -1;
    }

    public int setSubTrack(int track)
    {
        int flag = HiMediaPlayerInvoke.CMD_SET_SUB_ID;

        return excuteCommand(flag, track, false);
    }


    public int setSubtitlePath(String pPath)
    {
        if ((mMediaPlayer != null) && mIsPrepared)
        {
            return setSubPath(pPath);
        }

        return -1;
    }

    public int setSubPath(String path)
    {
        int flag = HiMediaPlayerInvoke.CMD_SET_SUB_EXTRA_SUBNAME;
        Parcel Request = Parcel.obtain();
        Parcel Reply = Parcel.obtain();

        Request.writeInterfaceToken(IMEDIA_PLAYER);
        Request.writeInt(flag);
        Request.writeString(path);

        invoke(Request, Reply);

        int Result = Reply.readInt();

        Request.recycle();
        Reply.recycle();

        return Result;
    }


    public boolean canPause()
    {
        return false;
    }

    public boolean canSeekBackward()
    {
        return false;
    }

    public boolean canSeekForward()
    {
        return false;
    }

    public void destroyPlayer()
    {
        if (mSurfaceHolder != null)
        {
            mSurfaceHolder = null;
        }

        if (mMediaPlayer != null)
        {
            mMediaPlayer.reset();
            mMediaPlayer.release();
            mMediaPlayer = null;
        }
    }
    public int getAudioSessionId() {
        return 0;
    }
}
