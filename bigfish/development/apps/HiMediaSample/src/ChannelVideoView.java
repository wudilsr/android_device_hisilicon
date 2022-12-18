package com.HiMediaSample;

import java.io.IOException;

import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Parcel;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.MediaController.MediaPlayerControl;

public class ChannelVideoView extends SurfaceView implements MediaPlayerControl {
	public static final int MEDIAINFO_PLAYER_DESTROYED = 3000;
	private static final int CMD_STOP_FASTPLAY = 199;
	private boolean mIsPrepared;
	public static MediaPlayer mMediaPlayer = null;

	private int mSeekWhenPrepared;
	private MediaPlayer.OnCompletionListener mOnCompletionListener;
	private MediaPlayer.OnErrorListener mOnErrorListener;
//	private MediaPlayer.OnFastBackwordCompleteListener mOnFastBackwordCompleteListener;
	private MediaPlayer.OnPreparedListener mOnPreparedListener;
	private MediaPlayer.OnInfoListener mOnInfoListener;
	private MediaPlayer.OnSeekCompleteListener mOnSeekCompleteListener;

	public static void create() {
		mMediaPlayer = new MediaPlayer();
	}

	public static MediaPlayer getMediaPlayer() {
		return mMediaPlayer;
	}

	private MediaPlayer.OnBufferingUpdateListener mBufferingUpdateListener = new MediaPlayer.OnBufferingUpdateListener() {
		public void onBufferingUpdate(MediaPlayer paramMediaPlayer, int paramInt) {
			mCurrentBufferPercentage = paramInt;
		}
	};

	private MediaPlayer.OnCompletionListener mCompletionListener = new MediaPlayer.OnCompletionListener() {
		public void onCompletion(MediaPlayer paramMediaPlayer) {
			if (mOnCompletionListener != null)
				mOnCompletionListener.onCompletion(mMediaPlayer);
		}
	};

	private Context mContext;
	private int mCurrentBufferPercentage;
	private int mDuration;
	private MediaPlayer.OnErrorListener mErrorListener = new MediaPlayer.OnErrorListener() {
		public boolean onError(MediaPlayer paramMediaPlayer, int paramInt1, int paramInt2) {
			if ((mOnErrorListener != null) && (mOnErrorListener.onError(mMediaPlayer, paramInt1, paramInt2))) {
				return false;
			} else if (getWindowToken() == null) {
				return true;
			}
			return false;
		}
	};
/*
	private MediaPlayer.OnFastBackwordCompleteListener mFastBackwordCompleteListener = new MediaPlayer.OnFastBackwordCompleteListener() {
		public void onFastBackwordComplete(MediaPlayer paramMediaPlayer) {
			if (mOnFastBackwordCompleteListener != null)
				mOnFastBackwordCompleteListener.onFastBackwordComplete(mMediaPlayer);
		}
	};
*/
	MediaPlayer.OnPreparedListener mPreparedListener = new MediaPlayer.OnPreparedListener() {
		public void onPrepared(MediaPlayer paramMediaPlayer) {
			mIsPrepared = true;
			if (mOnPreparedListener != null) {
				mOnPreparedListener.onPrepared(mMediaPlayer);
			} else {
				mVideoWidth = paramMediaPlayer.getVideoWidth();
				mVideoHeight = paramMediaPlayer.getVideoHeight();
				if ((mVideoWidth != 0) && (mVideoHeight != 0)) {
					getHolder().setFixedSize(mVideoWidth, mVideoHeight);
					if (mSeekWhenPrepared != 0) {
						mMediaPlayer.seekTo(mSeekWhenPrepared);
						mSeekWhenPrepared = 0;
					}
					if (!mStartWhenPrepared)
						;
					else {
						mMediaPlayer.start();
						mStartWhenPrepared = false;
					}

				} else {
					// Log.e(TAG, "(mVideoWidth == 0) || (mVideoHeight == 0)");
					if (mSeekWhenPrepared != 0) {
						mMediaPlayer.seekTo(mSeekWhenPrepared);
						mSeekWhenPrepared = 0;
					}
					if (!mStartWhenPrepared)
						;
					else {
						mMediaPlayer.start();
						mStartWhenPrepared = false;
					}
				}
			}
		}
	};

	SurfaceHolder.Callback mSHCallback = new SurfaceHolder.Callback() {
		public void surfaceChanged(SurfaceHolder paramSurfaceHolder, int paramInt1, int paramInt2, int paramInt3) {
			if ((mMediaPlayer != null) && (mIsPrepared) && (mVideoWidth == paramInt2) && (mVideoHeight == paramInt3)
					&& (mSeekWhenPrepared != 0)) {
				mMediaPlayer.seekTo(mSeekWhenPrepared);
				mSeekWhenPrepared = 0;
			}
		}

		public void surfaceCreated(SurfaceHolder paramSurfaceHolder) {
			mSurfaceHolder = paramSurfaceHolder;
			openVideo();
		}

		public void surfaceDestroyed(SurfaceHolder paramSurfaceHolder) {
			destroyPlayer();
		}
	};

	MediaPlayer.OnVideoSizeChangedListener mSizeChangedListener = new MediaPlayer.OnVideoSizeChangedListener() {
		public void onVideoSizeChanged(MediaPlayer paramMediaPlayer, int paramInt1, int paramInt2) {
			if ((mVideoWidth != 0) && (mVideoHeight != 0))
				;
		}
	};
	private boolean mStartWhenPrepared;
	private SurfaceHolder mSurfaceHolder = null;
	private Uri mUri;
	private int mVideoHeight;
	private int mVideoWidth;

	public ChannelVideoView(Context paramContext) {
		super(paramContext);
		mContext = paramContext;
		initVideoView();
	}

	public ChannelVideoView(Context paramContext, AttributeSet paramAttributeSet) {
		this(paramContext, paramAttributeSet, 0);
		mContext = paramContext;
		initVideoView();
	}

	public ChannelVideoView(Context paramContext, AttributeSet paramAttributeSet, int paramInt) {
		super(paramContext, paramAttributeSet, paramInt);
		mContext = paramContext;
		initVideoView();
	}

	@SuppressWarnings("deprecation")
	private void initVideoView() {
		mVideoWidth = 0;
		mVideoHeight = 0;
		getHolder().addCallback(mSHCallback);
		getHolder().setType(0);
		getHolder().setFormat(1);
		setFocusable(true);
		setFocusableInTouchMode(true);
		requestFocus();
	}

	private void openVideo() {

	    try {
			if ((mUri == null) || (mSurfaceHolder == null))
				;
			else {
				Intent localIntent1 = new Intent("com.android.music.musicservicecommand");
				localIntent1.putExtra("command", "pause");
				mContext.sendBroadcast(localIntent1);
				Intent localIntent2 = new Intent("com.android.music.videoOpened");
				localIntent2.putExtra("flag", "true");
				mContext.sendBroadcast(localIntent2);
				//mMediaPlayer.stop();
				//Thread.sleep(1000);
				mMediaPlayer.reset();
				mMediaPlayer.release();
				if (mOnInfoListener != null) {
					mOnInfoListener.onInfo(mMediaPlayer, MEDIAINFO_PLAYER_DESTROYED, 0);
				}

				mMediaPlayer = new MediaPlayer();
				openVideo2();
			}
	    }
	    catch (Exception e) {
            e.printStackTrace();
        }
	}

	/**
	 * add by csy
	 */
	private void openVideo2() {

		try {
			mMediaPlayer.setOnPreparedListener(mPreparedListener);
			mMediaPlayer.setOnVideoSizeChangedListener(mSizeChangedListener);
			mIsPrepared = false;
			// Log.e(TAG, "reset duration to -1 in openVideo");
			mDuration = -1;
			mMediaPlayer.setOnCompletionListener(mCompletionListener);
//			mMediaPlayer.setOnFastBackwordCompleteListener(mFastBackwordCompleteListener);
			mMediaPlayer.setOnErrorListener(mErrorListener);// MediaPlayer.MEDIA_INFO_BUFFER_

			mMediaPlayer.setOnBufferingUpdateListener(mBufferingUpdateListener);
			mMediaPlayer.setOnInfoListener(mOnInfoListener);
			mMediaPlayer.setOnSeekCompleteListener(mOnSeekCompleteListener);

			mCurrentBufferPercentage = 0;

			mSurfaceHolder.setFixedSize(getVideoWidth(), getVideoHeight());
			mMediaPlayer.setDisplay(mSurfaceHolder);

			mMediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
			mMediaPlayer.setDataSource(mContext, mUri);
			mMediaPlayer.setScreenOnWhilePlaying(true);
			mMediaPlayer.prepareAsync();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public boolean canPause() {
		return false;
	}

	public boolean canSeekBackward() {
		return false;
	}

	public boolean canSeekForward() {
		return false;
	}

	public void destroyPlayer() {
		if (mSurfaceHolder != null) {
			mSurfaceHolder = null;
			Intent localIntent = new Intent("com.android.music.videoOpened");
			localIntent.putExtra("flag", "false");
			mContext.sendBroadcast(localIntent);
		}
		if (mMediaPlayer != null) {
			mMediaPlayer.reset();
			mMediaPlayer.release();
			mMediaPlayer = null;
		}
	}

	public int getBufferPercentage() {
		int i = 0;
		if (mMediaPlayer != null) {
			if (mCurrentBufferPercentage != 0) {
				i = mCurrentBufferPercentage;
			} else {
				i = 0;
			}
		}
		return i;
	}

	public int getCurrentPosition() {
		int i = 0;
		if ((mMediaPlayer != null) && (mIsPrepared)) {
			i = mMediaPlayer.getCurrentPosition();
		}
		return i;
	}
	public int getAudioSessionId(){
		return 0;
		}
	public int getDuration() {
		int i = 0;
		if ((mMediaPlayer != null) && (mIsPrepared)) {
			mDuration = mMediaPlayer.getDuration();
			if (mDuration > 0)
				i = mDuration;
			else {
				mDuration = -1;
				i = mDuration;
			}
		} else {
			i = -1;
		}
		return i;
	}

	public int getVideoHeight() {
		return mVideoHeight;
	}

	public int getVideoWidth() {
		return mVideoWidth;
	}


	public int invoke(Parcel paramParcel1, Parcel paramParcel2) {
		int i = 0;
		if ((mMediaPlayer != null) && (mIsPrepared)) {
//			i = mMediaPlayer.invoke(paramParcel1, paramParcel2);
		}
		return i;
	}

	public boolean isPlaying() {
		boolean bool = false;
		if ((mMediaPlayer != null) && (mIsPrepared)) {
			bool = mMediaPlayer.isPlaying();
		}
		return bool;
	}

	protected void onMeasure(int paramInt1, int paramInt2) {
		int i = getDefaultSize(mVideoWidth, paramInt1);
		int j = getDefaultSize(mVideoHeight, paramInt2);
		setMeasuredDimension(i, j);
	}

	public void pause() {
		if ((mMediaPlayer != null) && (mIsPrepared) && (mMediaPlayer.isPlaying()))
			mMediaPlayer.pause();
		mStartWhenPrepared = false;
	}

	public void play() {
		Parcel localParcel = Parcel.obtain();
		localParcel.writeInterfaceToken("android.media.IMediaPlayer");
		localParcel.writeInt(CMD_STOP_FASTPLAY);
		invoke(localParcel, Parcel.obtain());
		localParcel.recycle();
	}

	public int resolveAdjustedSize(int paramInt1, int paramInt2) {
		int i = paramInt1;
		int j = View.MeasureSpec.getMode(paramInt2);
		int k = View.MeasureSpec.getSize(paramInt2);
		switch (j) {
		case MeasureSpec.UNSPECIFIED:
			i = paramInt1;
			break;
		case MeasureSpec.AT_MOST:
			i = Math.min(paramInt1, k);
			break;
		case MeasureSpec.EXACTLY:
			i = k;
			break;
		default:
			break;
		}
		return i;
	}

	public void resume() {
		if ((mMediaPlayer != null) && (mIsPrepared))
			play();
	}

	public void seekTo(int paramInt) {
		if ((mMediaPlayer != null) && (mIsPrepared))
			mMediaPlayer.seekTo(paramInt);
		else {
			mSeekWhenPrepared = paramInt;
		}
	}

	public void setOnCompletionListener(MediaPlayer.OnCompletionListener paramOnCompletionListener) {
		mOnCompletionListener = paramOnCompletionListener;
	}

	public void setOnErrorListener(MediaPlayer.OnErrorListener paramOnErrorListener) {
		mOnErrorListener = paramOnErrorListener;
	}
/*
	public void setOnFastBackwordCompleteListener(MediaPlayer.OnFastBackwordCompleteListener paramOnFastBackwordCompleteListener) {
		mOnFastBackwordCompleteListener = paramOnFastBackwordCompleteListener;
	}
*/
	public void setOnPreparedListener(MediaPlayer.OnPreparedListener paramOnPreparedListener) {
		mOnPreparedListener = paramOnPreparedListener;
	}

	public void setOnInfoListener(MediaPlayer.OnInfoListener  paramOnInfoListener) {
		mOnInfoListener = paramOnInfoListener;
	}

	public void setSeekCompleteListener(MediaPlayer.OnSeekCompleteListener  paramOnInfoListener) {
		mOnSeekCompleteListener = paramOnInfoListener;
	}

	public void setVideoPath(String paramString) {
		if (paramString == null)
			return;
		setVideoURI(Uri.parse(paramString));
	}

	public void setVideoScale(int paramInt1, int paramInt2) {
		ViewGroup.LayoutParams localLayoutParams = getLayoutParams();
		localLayoutParams.height = paramInt2;
		localLayoutParams.width = paramInt1;
		setLayoutParams(localLayoutParams);
	}

	public void setVideoURI(Uri paramUri) {
		mUri = paramUri;
		mStartWhenPrepared = false;
		mSeekWhenPrepared = 0;
		openVideo();

		requestLayout();
		invalidate();
	}


	public void start() {
		// Log.e(TAG, "-------start start----------------");
		if ((mMediaPlayer != null) && (mIsPrepared)) {
			mMediaPlayer.start();
			mStartWhenPrepared = false;
		} else {
			mStartWhenPrepared = true;
		}
		// Log.e(TAG, "-------start end----------------");

		return;
	}

	public void stopPlayback() {
		if (mMediaPlayer != null) {
			mMediaPlayer.stop();
			mMediaPlayer.release();
			mMediaPlayer = null;
		}
	}

	public void switchPlayback(String path) {
		if (mMediaPlayer != null) {
			mMediaPlayer.reset();
			try {
				mMediaPlayer.setDataSource(path);
				mMediaPlayer.prepare();
				mMediaPlayer.start();
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
			} catch (SecurityException e) {
				e.printStackTrace();
			} catch (IllegalStateException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

}
