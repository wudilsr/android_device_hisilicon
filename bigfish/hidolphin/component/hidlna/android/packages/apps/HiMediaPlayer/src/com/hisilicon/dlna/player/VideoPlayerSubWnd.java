package com.hisilicon.dlna.player;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;
import java.text.NumberFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.app.AlertDialog;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.PixelFormat;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.os.Parcel;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.os.SystemClock;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.dlna.dmr.DMRNative;
import com.hisilicon.dlna.dmr.Constant;
import com.hisilicon.dlna.dmr.IDMRPlayerController;
import com.hisilicon.dlna.dmr.IDMRServer;
import com.hisilicon.dlna.dmr.action.BaseAction;
import com.hisilicon.dlna.dmr.action.Controller;
import com.hisilicon.dlna.dmr.action.PlayAction;
import com.hisilicon.dlna.dmr.action.SeekAction;
import com.hisilicon.dlna.dmr.action.SetMuteAction;
import com.hisilicon.dlna.dmr.action.SetVolAction;
import com.hisilicon.dlna.file.DMSFile;
import com.hisilicon.dlna.file.FileType;
import com.hisilicon.dlna.file.LocalFile;
import com.hisilicon.dlna.file.util.MediaInfo;
import com.hisilicon.dlna.file.util.MediaInfo.MusicInfo;
import com.hisilicon.dlna.player.PlayerSubWnd.enFormatMsgNetwork;
import com.hisilicon.dlna.util.CommonDef;
import com.hisilicon.dlna.dmr.action.*;
import com.hisilicon.android.mediaplayer.HiMediaPlayer;
import com.hisilicon.android.mediaplayer.HiMediaPlayerInvoke;

/**
 * gui_xiangbo <br>
 * CN:视频播放 <br>
 */
public class VideoPlayerSubWnd extends PlayerSubWnd implements PlayerInterface
{
    private static final String TAG = "VideoPlayerSubWnd";

    private static final int TIMEOUT = 5000;
    private static final long SEEK_TIMEOUT_SECONDS = 3l;
    private static final long SURFACE_CREATE_TIMEOUT_SECONDS = 5l;

    private IPlayerMainWnd mIPlayerMainWnd = null;
    private Context mContext = null;
    private View mParentView = null;
    private static final int BUFFER_TIME_START_LINE = 3000;
    private static final int BUFFER_TIME_ENOUGH_LINE = 10000;
    private static final int BUFFER_TIME_FULL_LINE = 60000;

    private SetURLAction mSetURLAction;
    private PlayAction mPlayAction;
    private SeekAction mSeekAction;
    private AlertDialog.Builder alertDialogBuilder;
    private LinearLayout mControlBar;
    private LinearLayout mTitleBar;
    private ImageView mPlayPauseButton;
    private ImageView imgPlayPrev;
    private ImageView imgPlayStop;
    private ImageView imgPlayNext;
    private ImageView miniPlayMode;
    private ImageView imgRepeatMode;
    private NewSeekBar mSeekBar;
    private TextView mCurrentTimeTextView;
    private TextView mDurationTextView;
    private TextView txtMediaTitle;
    private TextView mSeekTimeTextView;
    private TextView mBufferingProgressTextView;
    private TextView mTextView_url;
    private TextView mTextVie_NetWork_Speed;
    private ProgressBar mProgressBar;
    private TimerManager mTimerManager;
    private IDMRServer dmrServer = null;
    private TextView controlTips = null;
    private boolean mIsInited = false;
    private boolean isPauseForBufferEmpty = false;
    private boolean isSeekBarMoving = false;
    private boolean isSeeking = false;
    private boolean isLoadingShowing = false;
    private boolean isPrepared = false;
    private boolean isPaused = false;
    private boolean isStarted = false;
    private boolean isPrepareProgressFull = false;
    private int mDuration;
    private int currentBufferingPos;
    private Timer mUpdateCurrentPositionTimer;
    // private Timer mHideTitleBarTimer;
    private BufferStatus mBufferStatus = BufferStatus.Empty;
    private HandlerThread mediaPlayerHandlerThread;
    private Handler mediaPlayerHandler = null;
    private MediaPlayerUtil.Status mediaPlayerStatus = MediaPlayerUtil.Status.Idle;
    private Lock seekLock = new ReentrantLock();
    private Condition seekCondition = seekLock.newCondition();

    public static final int DMC_PALYER = 1;
    public static final int LOCAL_PALYER = 2;
    public static final int MSG_LOADING = 99;
    public static final int MSG_SETINFO = 98;

    Intent curIntent = null;
    MediaPlayer mediaPlayer = null;
    SurfaceView mSurfaceView = null;
    SurfaceHolder surfaceHolder;
    private Controller mController = null;
    private DMSFile mDMSFile = null;
    private FetchPlayListThread fetchPlayListThread = null;

    private String mUrl = null;
    int fileType = 0;
    boolean SEEKING = false;
    private boolean exceptionStopped = false;
    private PlayMode mPlayMode = PlayMode.NORMAL;
    private Timer stopAction_timer = new Timer();
    private Timer mBufferTimer;
    private Timer mNetWorkSpeedTimer;
    // private boolean stopNotifyFlag = false;
    private String fileAllStringTime = null;
    private boolean isResetting = false;

    private static final int TIME_PROGRESS_UPDATE = 0x100;
    private static final int UPDATE_VIDEO_INFO = 0x101;
    private static final int SHOW_TOAST_GET_PLAYLIST_FAIL = 0x102;
    private static final int SHOW_UNSUPPORT_DIALOG = 0x103;
    private static final int NETWORK_DOWN = 0x104;

    int fileAllTime = 0;
    private String errUrl = "";
    private List<String> playlist = new ArrayList<String>();
    private List<DMSFile> dms_files = new ArrayList<DMSFile>();

    private View cur_focus_bottom = null; // tianjia@20120419
    private Timer mNetworkTimer;

    private AudioManager audioManager = null;
    private boolean seekDelayFlag = false;
    private static final int PREPARE_FINISH = 0x301;
    private int dmrPreState = Constant.DMR_STATE_NO_MEDIA_PRESENT;
    private int dmrCurrentState = Constant.DMR_STATE_NO_MEDIA_PRESENT;
    private Object mLockObject = new Object();
    private String contenttype;
    private long contentlength;

    private boolean mSurfaceCreated = false;
    private Lock mSurfaceLock = new ReentrantLock();
    private Condition mSurfaceCondition = mSurfaceLock.newCondition();

    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        super.onCreateView(inflater, container, savedInstanceState);
        mParentView = inflater.inflate(R.layout.videoplay, container, false);
        View v = mParentView;
        mContext = inflater.getContext();

        mProgressBar = (ProgressBar) v.findViewById(R.id.progressBar1);
        mProgressBar.setVisibility(View.INVISIBLE);
        mBufferingProgressTextView = (TextView) v.findViewById(R.id.textView_bp);
        mBufferingProgressTextView.setVisibility(View.GONE);
        mTextView_url = (TextView) v.findViewById(R.id.TextView_url);
        mTextView_url.setVisibility(View.GONE);
        mTextVie_NetWork_Speed = (TextView) v.findViewById(R.id.TextVie_NetWork_Speed);
        waitForHide();
        mTimerManager = TimerManager.getInstance();
        audioManager = (AudioManager) mContext.getSystemService(Service.AUDIO_SERVICE);
        alertDialogBuilder = new AlertDialog.Builder(mContext).setTitle(R.string.error).setMessage(
                R.string.unsupport_file);
        alertDialogBuilder.setPositiveButton(R.string.ok, new DialogInterface.OnClickListener()
        {
            public void onClick(DialogInterface dialog, int whichButton)
            {
                exceptionStopped = false;
                if (PlayList.getinstance().getLength() > 1)
                        playNext();
            }
        });
        alertDialogBuilder.setOnCancelListener(new DialogInterface.OnCancelListener()
        {
            public void onCancel(DialogInterface dialogInterface)
            {
                exceptionStopped = false;
                if (PlayList.getinstance().getLength() > 1)
                        playNext();
            }
        });

        Settings.init(mContext);
        BaseAction action = (BaseAction) this.getActivity().getIntent()
                .getSerializableExtra(Constant.FILE_PLAY_PATH);
        setBaseAction(action);

        runningFlag = true;
        mIsInited = true;
        return v;
    }

    public KeyDoResult keyDownDispatch(int keyCode, KeyEvent event)
    {
        Log.d(TAG, "onKeyDown keyCode=" + keyCode);
        if (keyCode == KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE)
        {
            // shield play button
            return KeyDoResult.DO_OVER;
        }
        if (keyCode == KeyEvent.KEYCODE_BACK)
        {
            // stopNotifyFlag = true;
            if (mTitleBar.getVisibility() == View.VISIBLE)
            {
                hideView();
                return KeyDoResult.DO_OVER;
            }
        }
        return KeyDoResult.DO_NOTHING;
    }

    @Override
    public KeyDoResult keyUpDispatch(int keyCode, KeyEvent event)
    {
        // Log.d(TAG, "onKeyUp keyCode: " + keyCode + ", event: " + event);
        if (!mSeekBar.hasFocus() && isSeekBarMoving)
        {
            isSeekBarMoving = false;
            mSeekTimeTextView.setText("");
        }
        switch (keyCode)
        {
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
                Log.d(TAG, "isPaused: " + isPaused);
                if (isPaused)
                {
                    playerResume();
                    dmrPreState = dmrCurrentState;
                    dmrCurrentState = Constant.DMR_STATE_PLAYING;
                }
                else
                {
                    if (isStarted)
                    {
                        // player is started once.
                        isPauseForBufferEmpty = false;
                    }
                    playerPause();
                }
                break;
            case KeyEvent.KEYCODE_MEDIA_STOP:
                // stopNotifyFlag = true;
                closeMainActivity(false);
                break;
            case KeyEvent.KEYCODE_PAGE_UP: // previous item
                if (mController == Controller.DMR)
                {
                    Toast.makeText(mContext, R.string.dmr_not_allow_pre, Toast.LENGTH_SHORT).show();
                    break;
                }
                PlayList.getinstance().moveprev();
                mUrl = PlayList.getinstance().getcur();
                play(mUrl);
                break;
            case KeyEvent.KEYCODE_PAGE_DOWN: // next item
                if (mController == Controller.DMR)
                {
                    Toast.makeText(mContext, R.string.dmr_not_allow_next, Toast.LENGTH_SHORT)
                            .show();
                    break;
                }
                PlayList.getinstance().movenext();
                mUrl = PlayList.getinstance().getcur();
                play(mUrl);
                break;
            default:
                break;
        }
        return KeyDoResult.DO_NOTHING;
    }

    public void onResume()
    {
        Log.d(TAG, "onResume()");
        super.onResume();
        mediaPlayer = new MediaPlayer();
        mediaPlayer.setOnPreparedListener(new OnPreparedListener());
        mediaPlayer.setOnErrorListener(new OnErrorListener());
        mediaPlayer.setOnCompletionListener(mCompletionListener);
        mediaPlayer.setOnBufferingUpdateListener(new OnBufferingUpdateListener());
        mediaPlayer.setOnInfoListener(new OnInfoListener());
        mediaPlayer.setOnSeekCompleteListener(new OnSeekCompleteListener());
        mediaPlayerHandlerThread = new HandlerThread("mediaplayer");
        mediaPlayerHandlerThread.start();
        mediaPlayerHandler = new MediaPlayerHandler(mediaPlayerHandlerThread.getLooper());
        Message msg = mediaPlayerHandler.obtainMessage(0, Action.InitPlayer);
        mediaPlayerHandler.sendMessage(msg);
        mNetWorkSpeedTimer = new Timer();
        mNetWorkSpeedTimer.schedule(new UpdateNetWorkSpeedTimerTask(), 500, 1000);
    }

    public void onPause()
    {
        Log.d(TAG, "onPause " + this.toString() + ",zhl time=" + SystemClock.elapsedRealtime());
        mIsInited = false;
        if (null == mediaPlayer)
        {
            return;
        }

        // only destroy mediaPlayer here
        if (mUpdateCurrentPositionTimer != null)
        {
            mUpdateCurrentPositionTimer.cancel();
            mUpdateCurrentPositionTimer = null;
        }
        // remove all action in queue
        mediaPlayerHandler.removeCallbacksAndMessages(null);
        mediaPlayerHandler = null;
        if (mediaPlayerHandlerThread != null)
        {
            boolean isQuit = mediaPlayerHandlerThread.quit();
            if (isQuit)
            {
                Log.d(TAG, "MediaPlayerHandlerThread quit success");
                try
                {
                    mediaPlayerHandlerThread.join();
                }
                catch (InterruptedException e)
                {
                    Log.e(TAG, "interrupted join", e);
                }
            }
            else
            {
                Log.e(TAG, "MediaPlayerHandlerThread quit fail");
            }
        }
        Log.d(TAG, "before mediaPlayer.release()");
        mediaPlayerStatus = MediaPlayerUtil.Status.End;
        mediaPlayer.release();
        mediaPlayer = null;
        Log.d(TAG, "after mediaPlayer.release()");
        // if(mController == Controller.DMR && stopNotifyFlag == true)

        stopNotify();

        if (null != dmrServer)
        {
            try
            {
                dmrServer.unregisterPlayerController();
            }
            catch (Exception e)
            {
                Log.d(TAG, "onPause() unregisterPlayerController");
            }
            dmrServer = null;
        }
        if (null != mNetWorkSpeedTimer)
        {
            mNetWorkSpeedTimer.cancel();
            mNetWorkSpeedTimer = null;
        }
        if (null != mBufferTimer)
        {
            mBufferTimer.cancel();
            mBufferTimer = null;
        }

        runningFlag = false;
        if (fetchPlayListThread != null && fetchPlayListThread.isAlive())
        {
            fetchPlayListThread.interruptThread();
            fetchPlayListThread.registerEventCallback(null);
            fetchPlayListThread.interrupt();
            fetchPlayListThread = null;
        }
        Log.d(TAG, "onPause() end");
        super.onPause();
    }

    public void onDestroy()
    {
        Log.d(TAG, "onDestroy " + this.toString());
        super.onDestroy();
    }

    /**
     * Hide the infobar and menubar
     */
    /**
     * 用于隐藏信息栏和控制栏
     */
    public void hideView()
    {

        Log.d(TAG, "hideView");
        cur_focus_bottom = mControlBar.findFocus();// tianjia@20120419
        if (mTitleBar.getVisibility() == RelativeLayout.VISIBLE)
        {
            Log.d(TAG, "VISIBLE ");
            mTitleBar.setVisibility(RelativeLayout.INVISIBLE);
            mControlBar.setVisibility(RelativeLayout.INVISIBLE);
        }
    }

    /**
     * Show the infobar and menubar
     */
    /**
     * 用于显示信息栏和控制栏
     */
    public void showView()
    {
        if (mTitleBar.getVisibility() == RelativeLayout.INVISIBLE)
        {
            mTitleBar.setVisibility(RelativeLayout.VISIBLE);
            mControlBar.setVisibility(RelativeLayout.VISIBLE);
            if (cur_focus_bottom != null)
            {// tianjia@20120419
                cur_focus_bottom.requestFocus();
            }
            else
            {
                mPlayPauseButton.requestFocus();
            }

        }
    }

    // add time to show progress 2011-7-7
    Timer mTimer = new Timer();

    /**
     * update UI components(TextView, ListView...)
     */
    /**
     * 更新各UI组件(TextView, ListView...)
     */
    Handler mHandler = new Handler()
    {
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case UPDATE_VIDEO_INFO:
                    updateVideoInfo();
                    break;
                case SHOW_TOAST_GET_PLAYLIST_FAIL:
                    Toast.makeText(mContext, R.string.fail_get_playlist, Toast.LENGTH_LONG).show();
                    break;
                case SHOW_UNSUPPORT_DIALOG:
                    if (alertDialogBuilder != null)
                    {
                        alertDialogBuilder.show();
                    }
                    break;
                case NETWORK_DOWN:
                    Toast.makeText(mContext, R.string.network_shutdown, Toast.LENGTH_SHORT).show();
                    break;
            }
            super.handleMessage(msg);
            return;
        }
    };

    /**
     * Convert seconds from value to string
     *
     * @param millSeconds
     * @return
     */
    /**
     * 把秒数从数值转换成字符串
     *
     * @param millSeconds
     * @return
     */
    String timeFromIntToString(int millSeconds)
    {
        int hour = 0;
        int minute = 0;
        int second = 0;
        String strHour;
        String strMinute;
        String strSecond;
        NumberFormat format = NumberFormat.getInstance();

        second = millSeconds / 1000;

        if (second > 60)
        {
            minute = second / 60;
            second = second % 60;
        }

        if (minute > 60)
        {
            hour = minute / 60;
            minute = minute % 60;
        }

        format.setMaximumIntegerDigits(2);
        format.setMinimumIntegerDigits(2);
        strSecond = format.format(second);
        strMinute = format.format(minute);
        strHour = format.format(hour);

        return (strHour + ":" + strMinute + ":"  + strSecond);
    }

    long timeFormStringToInt(String timeString)
    {
        String strTimeFormat = "HH:mm:ss";
        SimpleDateFormat sdf = new SimpleDateFormat(strTimeFormat);
        try
        {
            return sdf.parse(timeString).getTime();
        }
        catch (Exception e)
        {
            Log.e(TAG, "timeFormStringToInt", e);
        }
        return 0;
    }
    /**
     * OnCompletionAdapter of video play
     */
    /**
     * 视频播放的onCompletionAdapter
     */
    MediaPlayer.OnCompletionListener mCompletionListener = new MediaPlayer.OnCompletionListener()
    {
        public void onCompletion(MediaPlayer mp)
        {
            Log.d(TAG, "onCompletion mUrl :" + mUrl);
            if (mTimer != null)
            {
                mTimer.cancel();
                mTimer = null;
            }
            if (mNetworkTimer != null)
            {
                mNetworkTimer.cancel();
                mNetworkTimer = null;
            }

            if (exceptionStopped)
            {
                Log.e(TAG, "player stopped exceptionally");
                exceptionStopped = false;
                return;
            }

            errUrl = "";

            if (mController == Controller.DMR)
            {
                Log.d(TAG, "Video Controller == DMR,exit.");
                dmrPreState = dmrCurrentState;
                dmrCurrentState = Constant.DMR_STATE_STOPPED;
                stopNotify();
                showView();
                closeMainActivity(true);
                return;
            }
            switch (mPlayMode)
            {
                case NORMAL:
                    if (PlayList.getinstance().getPosition() != PlayList.getinstance().getLength() - 1)
                        playNext();
                    else
                    {
                        dmrPreState = dmrCurrentState;
                        dmrCurrentState = Constant.DMR_STATE_STOPPED;
                        mDuration = 0;
                        showTitleBarAndProgressBar();
                        stopNotify();
                        showView();
                        closeMainActivity(true);
                    }
                    break;
                case REPEAT_ONE:
                    play(mUrl);
                    break;
                case REPEAT_ALL:
                    playNext();
                    break;
            }
        }
    };

    // add by l00136619 2011-4-13 start
    public static boolean runningFlag = false;

    public static boolean isRunning()
    {
        return runningFlag;
    }

    /**
     * initial some controls for current activity
     */
    /**
     * 初始化一些当前activity的控件
     */
    public void init(View v)
    {
        if (false == runningFlag)
        {
            mSurfaceView = (SurfaceView) v.findViewById(R.id.Surface);
            mSurfaceView.setOnClickListener(new MouseClickListener());
            surfaceHolder = mSurfaceView.getHolder();
            surfaceHolder.addCallback(new SurfaceCallback());
            surfaceHolder.setFixedSize(getActivity().getWindowManager().getDefaultDisplay()
                    .getWidth(), getActivity().getWindowManager().getDefaultDisplay().getHeight());

            surfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_NORMAL);
            surfaceHolder.setFormat(PixelFormat.RGBA_8888);
            mControlBar = (LinearLayout) v.findViewById(R.id.lnrlyt_media_ctrl);
            mTitleBar = (LinearLayout) v.findViewById(R.id.rellyt_media_title);
            mPlayPauseButton = (ImageView) v.findViewById(R.id.img_start_pause);
            imgPlayPrev = (ImageView) v.findViewById(R.id.img_play_prev);
            imgPlayStop = (ImageView) v.findViewById(R.id.img_play_stop);
            imgPlayNext = (ImageView) v.findViewById(R.id.img_play_next);
            imgRepeatMode = (ImageView) v.findViewById(R.id.img_repeat_mode);
            mSeekTimeTextView = (TextView) v.findViewById(R.id.v_seektime_textView);
            mSeekTimeTextView.setTextSize(15);

            mSeekBar = (NewSeekBar) v.findViewById(R.id.skbar_play_progress);
            mSeekBar.setCanMove(true);
            mCurrentTimeTextView = (TextView) v.findViewById(R.id.txt_play_time);
            mDurationTextView = (TextView) v.findViewById(R.id.txt_play_sum_time);
            txtMediaTitle = (TextView) v.findViewById(R.id.txt_media_title);
            miniPlayMode = (ImageView) v.findViewById(R.id.img_repeat_status);
            mPlayPauseButton.requestFocus();
            mPlayPauseButton.setOnClickListener(listener);
            imgPlayPrev.setOnClickListener(listener);
            imgPlayStop.setOnClickListener(listener);
            imgPlayNext.setOnClickListener(listener);
            imgRepeatMode.setOnClickListener(listener);
        }

        mSeekTimeTextView.setText("");

        if (Controller.DMR == mController)
        {
            imgPlayPrev.setEnabled(false);
            imgPlayPrev.setBackgroundResource(R.drawable.previous_disable);
            imgPlayNext.setEnabled(false);
            imgPlayNext.setBackgroundResource(R.drawable.next_disable);
            imgPlayStop.setNextFocusRightId(R.id.img_start_pause);
            mPlayPauseButton.setNextFocusLeftId(R.id.img_play_stop);
            imgRepeatMode.setEnabled(false); // tianjia@20100419
        }
        else
            restoreSettings();

        if (null != mUrl)
        {
            showTitleBarAndProgressBar();
        }

        if (null != mediaPlayerHandler)
        {
            mediaPlayerHandler.removeMessages(0, Action.InitPlayer);
            Message msg = mediaPlayerHandler.obtainMessage(0, Action.InitPlayer);
            mediaPlayerHandler.sendMessage(msg);
        }

        if (true == runningFlag)
        {
            return;
        }

        mPlayPauseButton.setOnFocusChangeListener(new OnFocusChangeListener()
        {

            public void onFocusChange(View arg0, boolean arg1)
            {
                if (arg1)
                {
                    if (mediaPlayer == null )
                    {
                        return;
                    }
                    if (mediaPlayer.isPlaying())
                    {
                        mPlayPauseButton.setImageResource(R.drawable.pause_button);
                    }
                    else
                    {
                        mPlayPauseButton.setImageResource(R.drawable.play_button);
                    }
                }
                else
                {
                    if (mediaPlayer == null )
                    {
                        return;
                    }
                    if (mediaPlayer.isPlaying())
                    {
                        mPlayPauseButton.setImageResource(R.drawable.pause_button);
                    }
                    else
                    {
                        mPlayPauseButton.setImageResource(R.drawable.play_button);
                    }
                }
            }
        });

        mSeekBar.setOnSeekBarChangeListener(new OnSeekBarChangeListener());
        mSeekBar.setOnClickListener(new OnSeekBarClickListener());

    }

    /**
     * restore the configuration
     */
    /**
     * 读取保存的配置文件
     */
    private void restoreSettings()
    {
        int pi = Settings.getParaInt(Settings.VIDEO_PLAYMODE);
        if (Settings.playmode_repeat_one == pi)
        {
            setPlaymodeRepeatOne(false);
        }
        else if (Settings.playmode_repeat_all == pi)
        {
            setPlaymodeRepeatAll(false);
        }
    }

    /**
     * Any key operation will delay control bar hidden
     */
    /**
     * 任何按键操作都延迟控制栏隐藏
     */
    public KeyDoResult dispatchKeyEvent(KeyEvent event)
    {
        boolean isValidKey = false;
        switch (event.getKeyCode())
        {
            case KeyEvent.KEYCODE_DPAD_CENTER:
            case KeyEvent.KEYCODE_DPAD_LEFT:
            case KeyEvent.KEYCODE_DPAD_RIGHT:
            case KeyEvent.KEYCODE_DPAD_UP:
            case KeyEvent.KEYCODE_DPAD_DOWN:
            case KeyEvent.KEYCODE_PAGE_DOWN:
            case KeyEvent.KEYCODE_PAGE_UP:
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
            case KeyEvent.KEYCODE_MEDIA_STOP:
            case KeyEvent.KEYCODE_BACK:
            case KeyEvent.KEYCODE_MENU:
            case KeyEvent.KEYCODE_VOLUME_DOWN:
            case KeyEvent.KEYCODE_VOLUME_UP:
            case KeyEvent.KEYCODE_INFO:
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_VOLUME_MUTE:
            case 111: // KeyEvent.KEYCODE_ESCAPE
                isValidKey = true;
                break;
        }
        if (!isValidKey)
        {
            return KeyDoResult.DO_OVER;
        }

        if (mTitleBar.getVisibility() == RelativeLayout.VISIBLE)
        {
            mTimerManager.resetTimer(TimerManager.HOME_MENU_TIME_OUT);
        }
        if (mControlBar.getVisibility() == View.VISIBLE)
        {
            waitForHide();
        }
        else if (event.getAction() == 1)
        {
            int kc = event.getKeyCode();
            // 快捷键－－上下切换，播放暂停，不显示菜单栏
            if (kc != KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE && kc != KeyEvent.KEYCODE_PAGE_DOWN
                    && kc != KeyEvent.KEYCODE_PAGE_UP && kc != KeyEvent.KEYCODE_BACK && kc != 111) // KeyEvent.KEYCODE_ESCAPE
            {
                showView();
                mTimerManager.startTimer(TimerManager.HOME_MENU_TIME_OUT, this);
            }
        }

        return KeyDoResult.DO_NOTHING;
    }

    /**
     * OnClickListener for buttons on menubar
     */
    /**
     * 界面按钮的监听，响应Button的点击
     */
    OnClickListener listener = new OnClickListener()
    {

        public void onClick(View view)
        {
            if (mTitleBar.getVisibility() == RelativeLayout.VISIBLE)
            {
                mTimerManager.resetTimer(TimerManager.HOME_MENU_TIME_OUT);
            }
            else
            {
                hideView();
                mTimerManager.startTimer(TimerManager.HOME_MENU_TIME_OUT, VideoPlayerSubWnd.this);
            }
            switch (view.getId())
            {
                case R.id.img_start_pause:
                    Log.d(TAG, "img_start_pause");
                    if (isPaused)
                    {
                        playerResume();
                        dmrPreState = dmrCurrentState;
                        dmrCurrentState = Constant.DMR_STATE_PLAYING;
                    }
                    else
                    {
                        if (isStarted)
                        {
                            isPauseForBufferEmpty = false;
                        }
                        playerPause();
                    }
                    break;
                case R.id.img_play_prev:
                    Log.d(TAG, "img_play_prev");
                    PlayList.getinstance().moveprev();
                    mUrl = PlayList.getinstance().getcur();
                    play(mUrl);
                    break;
                case R.id.img_play_stop:
                    Log.d(TAG, "img_play_stop");
                    closeMainActivity(false);
                    break;
                case R.id.img_play_next:
                    Log.d(TAG, "img_play_next");
                    PlayList.getinstance().movenext();
                    mUrl = PlayList.getinstance().getcur();
                    play(mUrl);
                    break;
                case R.id.img_repeat_mode:
                    switch (mPlayMode)
                    {
                        case NORMAL:
                            setPlaymodeRepeatOne(true);
                            break;
                        case REPEAT_ONE:
                            setPlaymodeRepeatAll(true);
                            break;
                        case REPEAT_ALL:
                            setPlaymodeNormal(true);
                            break;
                    }
                    break;
            }
        }
    };

    /**
     * set the PlayMode to normal
     *
     * @param toSave if true, saved in configuration
     */
    /**
     * 把视频的播放模式设为normal
     *
     * @param toSave 如果为真，则保存到配置文件中
     */
    private void setPlaymodeNormal(boolean toSave)
    {
        mPlayMode = PlayMode.NORMAL;
        miniPlayMode.setVisibility(View.GONE);
        if (toSave)
            Settings.putParaInt(Settings.VIDEO_PLAYMODE, Settings.playmode_normal);
    }

    /**
     * set the PlayMode to repeat one
     *
     * @param toSave if true, saved in configuration
     */
    /**
     * 把视频的播放模式设为单曲循环
     *
     * @param toSave 如果为真，则保存到配置文件中
     */
    private void setPlaymodeRepeatOne(boolean toSave)
    {
        mPlayMode = PlayMode.REPEAT_ONE;
        miniPlayMode.setBackgroundResource(R.drawable.repeat_one_status);
        miniPlayMode.setVisibility(View.VISIBLE);
        if (toSave)
            Settings.putParaInt(Settings.VIDEO_PLAYMODE, Settings.playmode_repeat_one);
    }

    /**
     * set the PlayMode to repeat all
     *
     * @param toSave if true, saved in configuration
     */
    /**
     * 把视频的播放模式设为所有循环
     *
     * @param toSave 如果为真，则保存到配置文件中
     */
    private void setPlaymodeRepeatAll(boolean toSave)
    {
        mPlayMode = PlayMode.REPEAT_ALL;
        miniPlayMode.setBackgroundResource(R.drawable.repeat_all_status);
        miniPlayMode.setVisibility(View.VISIBLE);
        if (toSave)
            Settings.putParaInt(Settings.VIDEO_PLAYMODE, Settings.playmode_repeat_all);
    }

    /**
     * Update the video information on the interface
     */
    /**
     * 更新界面上的视频详细信息
     */
    private void updateVideoInfo()
    {
        String name = "";
        if (mController == Controller.DMP)
        {
            if (!dms_files.isEmpty())
                name = dms_files.get(PlayList.getinstance().getPosition()).getName();
            else
                name = mDMSFile.getName();
        }
        else if (Controller.DMR == mController)
        {
            if (mPlayAction != null && mPlayAction.getFileInfo() != null)
            {
                name = mPlayAction.getFileInfo().getTitle();
            }
            if (name == null)
            {
                MusicInfo mMusicInfo = MediaInfo.getMusicInfo(mediaPlayer);
                name = mMusicInfo.title;
            }
            if (null == name)
            {
                name = getResources().getString(R.string.unknown);
            }
        }

        Log.d(TAG, "updateVideoInfo: " + name);
        if (name.length() == 0)
            txtMediaTitle.setText(R.string.unknown);
        else
            txtMediaTitle.setText(name);
    }


    /**
     * play the next item
     */
    /**
     * 播放下一曲
     */
    private void playNext()
    {
        PlayList.getinstance().movenext();
        mUrl = PlayList.getinstance().getcur();
        play(mUrl);
    }

    private SeekAction.SeekMode seekModeHandler = SeekAction.SeekMode.DLNA_SEEK_MODE_ABS_COUNT;
    private String dataHandler = null;
    private Handler seekDelayHandler = new Handler()
    {
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case PREPARE_FINISH:
                    Log.d(TAG, "tianjia PREPARE_FINISH ");
                    if (seekDelayFlag == true && dataHandler != null)
                    {
                        seekTo(seekModeHandler, dataHandler);
                    }
                    seekDelayFlag = false;
                    dataHandler = null;
                    break;
                default:
                    break;
            }
            super.handleMessage(msg);
        }

    };

    private void seekTo(SeekAction.SeekMode mode, String data)
    {
        Log.d(TAG, "seek mode:" + mode + ",data:" + data);
        //  此处相对时间绝对时间反的才能正常使用<br>
        try
        {
            if (mode == SeekAction.SeekMode.DLNA_SEEK_MODE_ABS_TIME)
            {
                /*
                 * 解决腾讯视频无法seek,改为与REL_TIME同样的处理方法 int negative = 1; if (data.startsWith("-")) {
                 * negative = -1; } String[] timeStr = data.split(":|\\."); int msec =
                 * Integer.parseInt(timeStr[0]) * 60 * 60 * 1000 + Integer.parseInt(timeStr[1]) *
                 * negative * 60 * 1000 + Integer.parseInt(timeStr[2]) * negative * 1000; if
                 * (timeStr.length == 4) { msec += Integer.parseInt(timeStr[3]) * negative; } int
                 * nowTime = mediaPlayer.getCurrentPosition(); mediaPlayer.seekTo(nowTime + msec);
                 * isSeeking = true; 解决腾讯视频无法seek
                 */
                String[] timeStr = data.split(":|\\.");
                int msec = Integer.parseInt(timeStr[0]) * 60 * 60 * 1000
                        + Integer.parseInt(timeStr[1]) * 60 * 1000 + Integer.parseInt(timeStr[2])
                        * 1000;
                if (timeStr.length == 4)
                {
                    msec += Integer.parseInt(timeStr[3]);
                }
                playerSeekTo(msec);
            }
            else if (mode == SeekAction.SeekMode.DLNA_SEEK_MODE_REL_TIME)
            {
                String[] timeStr = data.split(":|\\.");
                int msec = Integer.parseInt(timeStr[0]) * 60 * 60 * 1000
                        + Integer.parseInt(timeStr[1]) * 60 * 1000 + Integer.parseInt(timeStr[2])
                        * 1000;
                if (timeStr.length == 4)
                {
                    msec += Integer.parseInt(timeStr[3]);
                }
                playerSeekTo(msec);
            }
            else if (mode == SeekAction.SeekMode.DLNA_SEEK_MODE_ABS_COUNT)
            {
                long pos = Long.parseLong(data);
                seekToPosition(pos);
            }
            else if (mode == SeekAction.SeekMode.DLNA_SEEK_MODE_REL_COUNT)
            {
                // 还未找到按相对位置seek<br>
            }
            else
            {
                Log.e(TAG, "seek mode is not found. mode=" + mode);
            }
        }
        catch (NumberFormatException e)
        {
            Log.e(TAG, "error in parseInt, seek to the begin", e);
            playerSeekTo(0);
            return;
        }
    }

    private void seekToPosition(long pos)
    {
        Log.d(TAG, "seekToPosition(" + pos + ")");
        Parcel request = Parcel.obtain();
        Parcel reply = Parcel.obtain();
        int low = (int) (pos & 0xFFFFFFFF);
        int high = (int) (pos >> 32);
        request.writeInterfaceToken("android.media.IMediaPlayer");
        request.writeInt(HiMediaPlayerInvoke.CMD_SET_SEEK_POS);
        request.writeInt(high);
        request.writeInt(low);
        mediaPlayer.invoke(request, reply);
        request.recycle();
        reply.recycle();
    }

    private void setVolume(int num)
    {
        AudioUtil.setVolume(audioManager, num);
    }

    class DMRPlayerController extends IDMRPlayerController.Stub
    {
        public int dmcPlayAction(String mURL)
        {
            Log.e(TAG, "EV_PLAY_PLAYing in dmrCurrentState=" + dmrCurrentState
                                    + ",isPrepared=" + isPrepared);
            if (dmrCurrentState == Constant.DMR_STATE_PAUSED_PLAYBACK)
                playerResume();
            else if (dmrCurrentState == Constant.DMR_STATE_PLAYING)
                return 0;
            else if (dmrCurrentState == Constant.DMR_STATE_STOPPED)
            {
                if (isPrepared)
                {
                    Message startMessage = mediaPlayerHandler.obtainMessage(0,
                                            Action.StartPlayer);
                    mediaPlayerHandler.sendMessage(startMessage);
                }
                else
                {
                    mUrl = mURL;
                    play(mUrl);
                }
            }
            dmrPreState = dmrCurrentState;
            dmrCurrentState = Constant.DMR_STATE_PLAYING;
            Log.e(TAG, "EV_PLAY_PLAYing out dmrCurrentState=" + dmrCurrentState);
            return 0;
        }

        public int dmcPauseAction()
        {
            isPauseForBufferEmpty = false;
            playerPause();
            dmrPreState = dmrCurrentState;
            dmrCurrentState = Constant.DMR_STATE_PAUSED_PLAYBACK;
            return 0;
        }

        public int dmcStopAction()
        {
            Log.d(TAG, "EV_PLAY_STOPPED");
            if (Constant.DMR_STATE_STOPPED == dmrCurrentState)
            {
                Log.e(TAG, " alread in stop so not stop");
                stopNotify();
                closeMainActivity(true);
                return 0;
            }
            dmrPreState = dmrCurrentState;
            dmrCurrentState = Constant.DMR_STATE_STOPPED;
            playerStop();
            //showView();
            closeMainActivity(true);
            return 0;
        }

        public int dmcSeekAction(int mode, int type , String data , String mURL)
        {
            Log.d(TAG, "seek action");
            SeekAction.SeekMode seekMode = SeekAction.SeekMode.getSeekModeByValue(mode);
            if (dmrCurrentState == Constant.DMR_STATE_STOPPED)
            {
                mUrl = mURL;
                if (isPrepared == false)
                {
                    play(mUrl);
                    Log.e(TAG, "the mediaPlayer isn't ready, can't seek...");
                    seekModeHandler = seekMode;
                    dataHandler = data;
                    seekDelayFlag = true;
                    return 1;
                }
                else
                {
                    seekTo(seekMode, data);
                }
            }
            else if (dmrCurrentState == Constant.DMR_STATE_PLAYING)
            {
                if (isPrepared)
                {
                    seekTo(seekMode, data);
                }
                else
                {
                    seekModeHandler = seekMode;
                    dataHandler = data;
                    seekDelayFlag = true;
                    Log.d(TAG, "isPrepared in false ");
                    return 1;
                }
            }
            else if (dmrCurrentState == Constant.DMR_STATE_TRANSITIONING)
            {
                seekModeHandler = seekMode;
                dataHandler = data;
                seekDelayFlag = true;
            }
            else if (dmrCurrentState == Constant.DMR_STATE_PAUSED_PLAYBACK)
            {
                if (isPrepared)
                {
                    seekTo(seekMode, data);
                }
                else
                {
                    seekModeHandler = seekMode;
                    dataHandler = data;
                    seekDelayFlag = true;
                    Log.d(TAG, "isPrepared in false ");
                    return 1;
                }
            }

            if (dmrCurrentState != Constant.DMR_STATE_TRANSITIONING)
            {
                Log.d(TAG, "dmrCurrentState status " + dmrCurrentState);
                dmrPreState = dmrCurrentState;
            }
            else
            {
                Log.d(TAG, "Constant.DMR_STATE_TRANSITIONING");
            }

            dmrCurrentState = Constant.DMR_STATE_TRANSITIONING;
            return 0;
        }

        public int getDuration()
        {
            // int duration = 0;
            // if (mediaPlayer != null && isStarted) {
            // duration = mediaPlayer.getDuration();
            // }
            return mDuration;
        }

        public int getCurrentPosition()
        {
            if (mediaPlayer != null && isPrepared)
            {
                return mediaPlayer.getCurrentPosition();
            }
            return 0;
        }

        public int getVolume()
        {
            return AudioUtil.getVolume(audioManager);
        }

        public int dmcSetVol(int num)
        {
            if (audioManager != null)
            {
                AudioUtil.setVolume(audioManager, num);
            }
            return 0;
        }

        public int dmcSetMute(boolean isMute)
        {
            if (audioManager != null)
            {
                AudioUtil.setMute(audioManager, isMute);
            }
            return 0;
        }
    }

    class MouseClickListener implements View.OnClickListener
    {
        public void onClick(View v)
        {
            Log.d(TAG, "onClick");
            showView();
            mTimerManager.startTimer(TimerManager.HOME_MENU_TIME_OUT, VideoPlayerSubWnd.this);
        }
    }

    class UpdatePlayListEventCallback implements FetchPlayListThread.EventCallback
    {

        public void fileAddedNotify(DMSFile file)
        {
        }

        public void deviceNotFountNotify()
        {
            mHandler.sendEmptyMessage(SHOW_TOAST_GET_PLAYLIST_FAIL);
            playlist.add(mDMSFile.getUrl());
        }

        public void currentIndexNotify(int index)
        {
            PlayList.getinstance().setlist(playlist, index);
        }

        public void finishNotify()
        {
            PlayList.getinstance().setlist(playlist, PlayList.getinstance().getPosition());
        }
    }

    enum PrepareStatus
    {
        NotPrepare,
        Preparing,
        PrepareFail,
        PrepareSucces
    }

    enum BufferStatus
    {
        Empty,
        Start,
        Enough,
        Full,
        Finish,
        End, //MediaPlayer has only Start,End
    }

    enum Action
    {
        TimeUpdate,
        HideTitleBar,
        PausePlayer,
        PausePlayerWithOutNotify,
        ResumePlayer,
        BufferUpdate,
        SHOW_NETWORK_DOWN_TOAST,
        ShowTitleBar,
        ShowTitleBarAndProgressBar,
        StartPlayer,
        StartPlayerWithOutNotify,
        InitPlayer,
        StopPlayer,
        GetDuration,
        SeekToPlayer,
        SHOW_BINDSERVICE_FAIL_TOAST,
        UpdateBufferingProgress,
        UpdateNetWorkSpeed,
        HideBufferingProgressBar,
        UpdatePrepareProgress
    }

    private void play(String url)
    {
        Log.d(TAG, "play url function");
        isPrepared = false;
        isStarted = false;
        isPrepareProgressFull = false;
        mDuration = 0;
        mUrl = url;
        mediaPlayerHandler.removeCallbacksAndMessages(null);
        showTitleBarAndProgressBar();
        mediaPlayerHandler.removeMessages(0, Action.InitPlayer);
        Message msg = mediaPlayerHandler.obtainMessage(0, Action.InitPlayer);
        mediaPlayerHandler.sendMessageDelayed(msg, 300);
    }

    private void playerPause()
    {
        Log.d(TAG, "playerPause");
        if (isPrepared && isStarted)
        {
            //  for fixed "onError what=-2147483648"
            try
            {
                Thread.sleep(600);
            }
            catch (InterruptedException e)
            {
                Log.e(TAG, "sleep", e);
            }
            Message msg = mediaPlayerHandler.obtainMessage(0, Action.PausePlayer);
            mediaPlayerHandler.sendMessage(msg);
            dmrPreState = dmrCurrentState;
            dmrCurrentState = Constant.DMR_STATE_PAUSED_PLAYBACK;
        }
        else
        {
            Log.e(TAG, "can't pause before prepare finish");
        }
    }

    private void playerResume()
    {
        Log.d(TAG, "playerResume");
        mediaPlayerHandler.removeMessages(0, Action.ResumePlayer);
        mediaPlayerHandler.sendMessage(mediaPlayerHandler.obtainMessage(0, Action.ResumePlayer));
    }

    private void playerStart()
    {
        Log.d(TAG, "playerStart");
        mediaPlayerHandler.removeMessages(0, Action.StartPlayer);
        Message startMessage = mediaPlayerHandler.obtainMessage(0, Action.StartPlayer);
        mediaPlayerHandler.sendMessage(startMessage);
    }

    private void playerStop()
    {
        Log.d(TAG, "playerStop");
        isStarted = false;
        isPrepareProgressFull = false;
        if (mUpdateCurrentPositionTimer != null)
        {
            mUpdateCurrentPositionTimer.cancel();
            mUpdateCurrentPositionTimer = null;
        }
        Message msg = mediaPlayerHandler.obtainMessage(0, Action.StopPlayer);
        mediaPlayerHandler.sendMessage(msg);
    }

    private void playerSeekTo(int msec)
    {
        Log.d(TAG, "playerSeekTo(" + msec + ")");
        if (isPrepared)
        {
            Message msg = mediaPlayerHandler.obtainMessage(msec, Action.SeekToPlayer);
            mediaPlayerHandler.sendMessage(msg);
            //showTitleBarAndProgressBar();
            if (dmrCurrentState != Constant.DMR_STATE_TRANSITIONING)
            {
                dmrPreState = dmrCurrentState;
            }
            //showTitleBar();
            //Message msgShowTitleBar = mediaPlayerHandler.obtainMessage(0, Action.ShowTitleBar);
            //mediaPlayerHandler.sendMessage(msgShowTitleBar);
        }
        else
        {
            Log.e(TAG, "can't seekTo before prepare finish");
        }
    }

    private void waitForHide()
    {
        if (mController == Controller.DMR)
        {
            mUIHandler.removeCallbacksAndMessages(Action.HideTitleBar);
            mUIHandler.sendMessageDelayed(mUIHandler.obtainMessage(0, Action.HideTitleBar), 3000l);
        }
    }

    private void hideTitleBar()
    {
        if (mTitleBar.getVisibility() == View.VISIBLE)
        {
            mTitleBar.setVisibility(View.INVISIBLE);
            mControlBar.setVisibility(View.INVISIBLE);
        }
        if (mBufferTimer != null)
        {
            Log.d(TAG, "mBufferTimer cancel");
            mBufferTimer.cancel();
            mBufferTimer = null;
        }
    }

    private void showTitleBar()
    {
        if (mTitleBar.getVisibility() == View.INVISIBLE)
        {
            mTitleBar.setVisibility(View.VISIBLE);
            mControlBar.setVisibility(View.VISIBLE);
        }
    }

    private void showTitleBarAndProgressBar()
    {
        {
            Message msg = mUIHandler.obtainMessage(0, Action.ShowTitleBarAndProgressBar);
            mUIHandler.sendMessage(msg);
            Log.d(TAG, "ShowTitleBarAndProgressBar");
            if (mBufferTimer == null)
            {
                Log.d(TAG, "new mBufferTimer");
                mBufferTimer = new Timer();
                mBufferTimer.schedule(new UpdateBufferTimerTask(), 0, 200);
            }
        }
    }

    private void updataBufferProgress()
    {
        Log.d(TAG, "sendMessage UpdateBufferingProgress");
        Message msg = mUIHandler.obtainMessage(0, Action.UpdateBufferingProgress);
        mUIHandler.sendMessage(msg);
    }

    public static String getDtcpUrl(String url)
    {
        if (url.contains("dtcp1port=4999"))
        {
            String tempurl = "dtcp:" + url;
            return tempurl;
        }
        DMRNative dmrNative = DMRNative.getInstance();
        String type = dmrNative.HI_DmrGetHead(url);
        if (null != type)
        {
            if (type.contains("application/x-dtcp1"))
            {
                Pattern pServ = Pattern.compile("DTCP1PORT=([0-9]+)");
                Matcher mServ = pServ.matcher((CharSequence) type);
                if (mServ.find())
                {
                    String tempurl = "dtcp:" + url + "&dtcp1port=" + mServ.group(1);
                    Log.d(TAG, "url with DTCP1PORT :" + tempurl);
                    return tempurl;
                }
                else
                {
                    Log.d(TAG, "Not find DTCP1PORT");
                }
            }
            Log.d(TAG, "type: " + type);
        }
        else
        {
            Log.d(TAG, "getDtcpUrl fail type is null");
        }
        return url;
    }

    class MediaPlayerHandler extends Handler
    {

        public MediaPlayerHandler(Looper looper)
        {
            super(looper);
        }

        public void handleMessage(Message msg)
        {
            super.handleMessage(msg);
            if (null == mediaPlayer)
            {
                Log.e(TAG,"[MediaPlayerHandler][handleMessage] mediaPlayer is null");
                return;
            }
            Action action = (Action) msg.obj;
            switch (action)
            {
                case TimeUpdate:
                {
                    try
                    {
                        int currentPosition = mediaPlayer.getCurrentPosition();
                        mUIHandler.sendMessage(mUIHandler.obtainMessage(currentPosition,
                                Action.TimeUpdate));
                    }
                    catch (IllegalStateException e)
                    {
                        Log.e(TAG, "mediaPlayer.getCurrentPosition()", e);
                    }
                    break;
                }
                case PausePlayer:
                    if (mediaPlayerStatus.validAction(MediaPlayerUtil.Action.pause))
                    {
                        mediaPlayer.pause();
                        isPaused = true;
                        mediaPlayerStatus = MediaPlayerUtil.Status.Paused;
                        mUIHandler.sendMessage(mUIHandler.obtainMessage(0, Action.PausePlayer));
                        pauseNotify();
                    }
                    else
                    {
                        Log.e(TAG, "pause()invalid status: " + mediaPlayerStatus);
                    }
                    break;
                case PausePlayerWithOutNotify:
                    if (mediaPlayerStatus.validAction(MediaPlayerUtil.Action.pause))
                    {
                        mediaPlayer.pause();
                        isPaused = true;
                        mediaPlayerStatus = MediaPlayerUtil.Status.Paused;
                        mUIHandler.sendMessage(mUIHandler.obtainMessage(0, Action.PausePlayer));
                    }
                    else
                    {
                        Log.e(TAG, "pause() invalid status: " + mediaPlayerStatus);
                    }
                    break;
                case ResumePlayer:
                    if (mediaPlayerStatus.validAction(MediaPlayerUtil.Action.start))
                    {
                        mediaPlayer.start();
                        isPaused = false;
                        mediaPlayerStatus = MediaPlayerUtil.Status.Started;
                        // update ui
                        mUIHandler.sendMessage(mUIHandler.obtainMessage(0, Action.ResumePlayer));
                        isStarted = true;
                        startNotify();
                    }
                    else
                    {
                        Log.e(TAG, "start() invalid status: " + mediaPlayerStatus);
                    }
                    break;
                case StartPlayer:
                    if (isPrepared)
                    {
                        if (mediaPlayerStatus.validAction(MediaPlayerUtil.Action.start))
                        {
                            setHiPlayerTimerProc("before mediaPlayer start");
                            mediaPlayer.start();
                            isPaused = false;
                            mediaPlayerStatus = MediaPlayerUtil.Status.Started;
                            // update ui
                            mUIHandler
                                    .sendMessage(mUIHandler.obtainMessage(0, Action.ResumePlayer));
                            isStarted = true;
                            startNotify();
                        }
                        else
                        {
                            Log.e(TAG, "start() invalid status: " + mediaPlayerStatus);
                        }
                    }
                    else
                    {
                        Log.e(TAG, "can't resume before prepare finish");
                    }
                    break;
                case StartPlayerWithOutNotify:
                    Log.d(TAG, " StartPlayerWithOutNotify isPrepared=" + isPrepared
                            + ",mediaPlayerStatus=" + mediaPlayerStatus);
                    if (isPrepared)
                    {
                        if (mediaPlayerStatus.validAction(MediaPlayerUtil.Action.start))
                        {
                            setHiPlayerTimerProc("before PlayerStart noNotify");
                            mediaPlayer.start();
                            isPaused = false;
                            mediaPlayerStatus = MediaPlayerUtil.Status.Started;
                            // update ui
                            mUIHandler
                                    .sendMessage(mUIHandler.obtainMessage(0, Action.ResumePlayer));
                            isStarted = true;
                        }
                        else
                        {
                            Log.e(TAG, "start()invalid status: " + mediaPlayerStatus);
                        }
                    }
                    else
                    {
                        Log.e(TAG, "can't resume before prepare finish");
                    }
                    break;
                case InitPlayer:
                    synchronized (mLockObject)
                    {
                        Log.d(TAG, "InitPlayer dmrCurrentState=" + dmrCurrentState);
                        isPrepared = false;
                        isStarted = false;
                        isPrepareProgressFull = false;
                        isPaused = false;
                        bufferCleared();
                        isResetting = true;
                        setHiPlayerTimerProc("before reset");
                        mediaPlayer.reset();
                        setHiPlayerTimerProc("after reset");
                        isResetting = false;
                        mediaPlayerStatus = MediaPlayerUtil.Status.Idle;
                        mBufferStatus = BufferStatus.Empty;
                        try
                        {
                            String playerUrl = dropRangeToken(mUrl);
                            playerUrl = getDtcpUrl(playerUrl);
                            setHiPlayerTimerProc("playurl:"  + playerUrl);
                            mediaPlayer.setDataSource(playerUrl);
                            Log.v(TAG, "playerUrl = " + playerUrl);
                            Log.v(TAG, "mUrl=" + mUrl);
                            if (!playerUrl.equals(mUrl))
                            {
                                int ret = byteRangeInvoke();
                                Log.v(TAG, "playerUrl no Rang = " + playerUrl);
                                Log.v(TAG, "byteRangeInvoke ret = " + ret);
                            }
                            // mediaPlayer.setDataSource(mUrl);
                            mediaPlayerStatus = MediaPlayerUtil.Status.Initialized;
                        }
                        catch (IllegalArgumentException e)
                        {
                            Log.e(TAG, "IllegalArgument,mediaPlayer.setDataSource(" + mUrl + ")");
                        }
                        catch (SecurityException e)
                        {
                            Log.e(TAG, "SecurityException, mediaPlayer.setDataSource(" + mUrl + ")");
                        }
                        catch (IllegalStateException e)
                        {
                            Log.e(TAG, "IllegalState,mediaPlayer.setDataSource(" + mUrl + ")");
                        }
                        catch (IOException e)
                        {
                            Log.e(TAG, "IOException,mediaPlayer.setDataSource(" + mUrl + ")");
                        }
                        if (mediaPlayerStatus.validAction(MediaPlayerUtil.Action.prepareAsync))
                        {
                            Log.d(TAG, "before prepare");
                            setHiPlayerTimerProc("before prepare");
                            mediaPlayer.prepareAsync();
                            mediaPlayerStatus = MediaPlayerUtil.Status.Preparing;
                        }
                        else
                        {
                            Log.e(TAG, "can't prepareAsync mediaPlayerStatus: " + mediaPlayerStatus);
                        }
                        long nanoTimeouts = TimeUnit.SECONDS.toNanos(SURFACE_CREATE_TIMEOUT_SECONDS);
                        mSurfaceLock.lock();
                        try {
                            while((!mSurfaceCreated) && nanoTimeouts > 0) {
                                Log.d(TAG, "wait surfaceCreated");
                                nanoTimeouts = mSurfaceCondition.awaitNanos(nanoTimeouts);
                            }
                        } catch(InterruptedException e) {
                            Log.e(TAG, "awaitNanos", e);
                        } finally {
                            mSurfaceLock.unlock();
                        }
                        if (!mSurfaceCreated) {
                            Log.e(TAG, "surface not ready");
                            break;
                        }
                        mediaPlayer.setDisplay(mSurfaceView.getHolder());
                    }
                    break;
                case StopPlayer:
                    Log.d(TAG, "StopPlayer mediaPlayerStatus= " + mediaPlayerStatus);
                    if (mediaPlayerStatus.validAction(MediaPlayerUtil.Action.stop))
                    {
                        Log.e(TAG, "StopPlayer stop ");
                        mediaPlayer.stop();

                        //loading icon didn't hide, when loading is showing and video changed to the next.
                        Message hideLoadIcon = mUIHandler.obtainMessage(0, Action.HideBufferingProgressBar);
                        mUIHandler.sendMessage(hideLoadIcon);

                        mediaPlayerStatus = MediaPlayerUtil.Status.Stopped;
                        isPrepared = false;
                        stopNotify();
                    }
                    else
                    {
                        if (MediaPlayerUtil.Status.Stopped == mediaPlayerStatus)
                        {
                            Log.e(TAG, "stop()again");
                            stopNotify();
                        }
                        Log.e(TAG, "stop()invalid status: " + mediaPlayerStatus);
                    }
                    break;
                case SeekToPlayer:
                    if (mediaPlayerStatus.validAction(MediaPlayerUtil.Action.seekTo))
                    {
                        seekLock.lock();
                        try
                        {
                            isSeeking = true;
                            setHiPlayerTimerProc("before seek");
                            mediaPlayer.seekTo(msg.what);
                            long nanoTimeouts = TimeUnit.SECONDS.toNanos(SEEK_TIMEOUT_SECONDS);
                            while (isSeeking && nanoTimeouts > 0)
                            {
                                Log.e(TAG, "wait seekComplete");
                                nanoTimeouts = seekCondition.awaitNanos(nanoTimeouts);
                            }
                            if (isSeeking)
                            {
                                Log.e(TAG, "seek timeout, time: " + SEEK_TIMEOUT_SECONDS);
                                isSeeking = false; // timout
                            }
                        }
                        catch (InterruptedException e)
                        {
                            Log.e(TAG, "wait seekTo complete interrupted", e);
                        }
                        finally
                        {
                            seekLock.unlock();
                        }
                    }
                    else
                    {
                        Log.e(TAG, "seekTo()invalid status: " + mediaPlayerStatus);
                    }
                case GetDuration:
                    mDuration = mediaPlayer.getDuration();
                    if(mDuration != 0)
                    {
                        fileAllStringTime = timeFromIntToString(mDuration);
                    }
                    else
                    {
                        mDuration = (int)timeFormStringToInt(fileAllStringTime);
                        fileAllStringTime = timeFromIntToString(mDuration);
                    }
                    break;
                default:
                    break;
            }
        }
    };

    private Handler mUIHandler = new Handler()
    {

        @Override
        public void handleMessage(Message msg)
        {
            super.handleMessage(msg);
            Action action = (Action) msg.obj;
            switch (action)
            {
                case TimeUpdate:
                    int currentPosition = msg.what;
                    if (!isSeekBarMoving)
                    {
                        mSeekBar.setProgress(Math.round(currentPosition * 1.0f / mDuration * 100));
                    }
                    String currentTimeString = timeFromIntToString(currentPosition);
                    mCurrentTimeTextView.setText(currentTimeString);
                    mDurationTextView.setText(fileAllStringTime);
                    break;
                case PausePlayer:
                    mPlayPauseButton.setImageResource(R.drawable.play_button);
                    break;
                case ResumePlayer:
                    mPlayPauseButton.setImageResource(R.drawable.pause_button);
                    isLoadingShowing = false;
                    mProgressBar.setVisibility(View.GONE);
                    mBufferingProgressTextView.setVisibility(View.GONE);
                    break;
                case HideTitleBar:
                    // isLoadingShowing = false;
                    // mProgressBar.setVisibility(View.GONE);
                    // mBufferingProgressTextView.setVisibility(View.GONE);
                    if(isStarted && isPrepareProgressFull)
                    {
                        hideTitleBar();
                    }
                    else
                    {
                        //Log.d(TAG, "palyer is no Started waitForHide ");
                        waitForHide();
                    }
                    break;
                case BufferUpdate:
                    if (msg.what != currentBufferingPos)
                    {
                        currentBufferingPos = msg.what;
                        mSeekBar.setSecondaryProgress(msg.what);
                    }
                    break;
                case SHOW_NETWORK_DOWN_TOAST:
                    if (msg.what == 1)
                    {
                        Toast.makeText(mContext, R.string.network_connect_failed,
                                Toast.LENGTH_SHORT).show();
                    }
                    else if (msg.what == 2 || msg.what == 0)
                    {
                        Toast.makeText(mContext, R.string.network_timeout, Toast.LENGTH_SHORT)
                                .show();
                    }
                    else if (msg.what == 3)
                    {
                        Toast.makeText(mContext, R.string.network_disconnect, Toast.LENGTH_SHORT)
                                .show();
                    }
                    else if (msg.what == 4)
                    {
                        Toast.makeText(mContext, R.string.network_not_found, Toast.LENGTH_SHORT)
                                .show();
                    }
                    break;
                case ShowTitleBar:
                    showTitleBar();
                    waitForHide();
                    break;
                case ShowTitleBarAndProgressBar:
                    mProgressBar.setVisibility(View.VISIBLE);
                    if (mBufferingProgressTextView.getVisibility() != View.VISIBLE)
                    {
                        mBufferingProgressTextView.setText("0%");
                        mBufferingProgressTextView.setVisibility(View.VISIBLE);
                    }
                    showTitleBar();
                    waitForHide();
                    break;
                case HideBufferingProgressBar:
                    isLoadingShowing = false;
                    mProgressBar.setVisibility(View.GONE);
                    mBufferingProgressTextView.setVisibility(View.GONE);
                    break;
                case UpdateBufferingProgress:
                    Log.d(TAG, "UpdateBufferingProgress isLoadingShowing = " + isLoadingShowing);
                    if (isLoadingShowing)
                    {
                        int bufferedMS = getBufferedTime(mediaPlayer);
                        Log.d(TAG, "UpdateBufferingProgress bufferedMS = " + bufferedMS);
                        String perc = "0%";
                        if (bufferedMS >= BUFFER_TIME_ENOUGH_LINE)
                        {
                            perc = "100%";
                        }
                        else if (bufferedMS >= 0)
                        {
                            NumberFormat nf = NumberFormat.getPercentInstance();
                            perc = nf.format(bufferedMS / (BUFFER_TIME_ENOUGH_LINE * 1.0));
                        }
                        Log.d(TAG, "mBufferingProgressTextView settext " + perc);
                        mBufferingProgressTextView.setText(perc);
                    }
                    break;
                case UpdateNetWorkSpeed:
                {
                    int netWorkSpeed = getNetWorkSpeed(mediaPlayer);
                    if (netWorkSpeed >= 0)
                    {
                        mTextVie_NetWork_Speed.setText(netWorkSpeed + "Kbps");
                    }
                    break;
                }
                case UpdatePrepareProgress:
                {
                    int prepareProgress = msg.what;
                    if(100 == prepareProgress)
                    {
                        isPrepareProgressFull = true;
                    }
                    else
                    {
                        isPrepareProgressFull = false;
                    }
                    mBufferingProgressTextView.setText(prepareProgress + "%");
                    break;
                }
                default:
                    break;
            }
        }
    };

    private void setBufferUnderrun(MediaPlayer mediaPlayer, int type)
    {
        if (mediaPlayer == null)
        {
            return;
        }
        Parcel request = Parcel.obtain();
        request.writeInterfaceToken("android.media.IMediaPlayer");
        request.writeInt(HiMediaPlayerInvoke.CMD_SET_BUFFER_UNDERRUN); // CMD_GET_BUFFER_STATUS 316
        request.writeInt(type);
        Parcel reply = Parcel.obtain();
        try
        {
            mediaPlayerInvoke(mediaPlayer, request, reply);
        }
        catch (IllegalArgumentException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (NoSuchMethodException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (IllegalAccessException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (InvocationTargetException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        int ret = reply.readInt();
        Log.d(TAG, "setBufferUnderrun return:" + ret);
        request.recycle();
        reply.recycle();
    }

    private int setBufferTimeConfig(MediaPlayer mp,
            int start, int enough, int full)
    {
        int flag = HiMediaPlayerInvoke.CMD_SET_BUFFERTIME_CONFIG;
        Parcel Request = Parcel.obtain();
        Parcel Reply = Parcel.obtain();

        Request.writeInterfaceToken("android.media.IMediaPlayer");
        Request.writeInt(flag);
        Request.writeInt(full);
        Request.writeInt(start);
        Request.writeInt(enough);
        Request.writeInt(12000);

        try {
            mediaPlayerInvoke(mp, Request, Reply);
        } catch (IllegalArgumentException e) {
            Log.e(TAG, "MediaPlayer.invoke", e);
        } catch (NoSuchMethodException e) {
            Log.e(TAG, "MediaPlayer.invoke", e);
        } catch (IllegalAccessException e) {
            Log.e(TAG, "MediaPlayer.invoke", e);
        } catch (InvocationTargetException e) {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        int result = Reply.readInt();

        Request.recycle();
        Reply.recycle();

        return result;
    }




    private int getBufferedTime(MediaPlayer mediaPlayer)
    {
        if (mediaPlayer == null)
        {
            return -1;
        }
        Parcel request = Parcel.obtain();
        request.writeInterfaceToken("android.media.IMediaPlayer");
        request.writeInt(HiMediaPlayerInvoke.CMD_GET_BUFFER_STATUS); // CMD_GET_BUFFER_STATUS 310
        Parcel reply = Parcel.obtain();
        try
        {
            mediaPlayerInvoke(mediaPlayer, request, reply);
        }
        catch (IllegalArgumentException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (NoSuchMethodException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (IllegalAccessException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (InvocationTargetException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        int ret = reply.readInt();
        int size = reply.readInt();
        int time = reply.readInt();
        Log.d(TAG, "getBufferStatus ret:" + ret + ",size:" + size + ",time:" + time);
        request.recycle();
        reply.recycle();
        return time;
    }

    private int getNetWorkSpeed(MediaPlayer mediaPlayer)
    {
        if (mediaPlayer == null)
        {
            return -1;
        }
        Parcel request = Parcel.obtain();
        request.writeInterfaceToken("android.media.IMediaPlayer");
        request.writeInt(HiMediaPlayerInvoke.CMD_GET_DOWNLOAD_SPEED); // CMD_GET_DOWNLOAD_SPEED 311
        Parcel reply = Parcel.obtain();
        try
        {
            mediaPlayerInvoke(mediaPlayer, request, reply);
        }
        catch (IllegalArgumentException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (NoSuchMethodException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (IllegalAccessException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (InvocationTargetException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        int ret = reply.readInt();
        int speed = reply.readInt() / 8 / 1024;
        Log.d(TAG, "getNetWorkSpeed ret:" + ret + ",speed:" + speed);
        request.recycle();
        reply.recycle();
        return speed;
    }

    private String dropRangeToken(String strUrl)
    {
        if (mediaPlayer == null)
        {
            return strUrl;
        }
        if (strUrl.contains("?range=no"))
        {
            return strUrl.substring(0, strUrl.lastIndexOf("?range=no"))
                    + strUrl.substring(strUrl.lastIndexOf("?range=no") + "?range=no".length());
        }
        else
        {
            return strUrl;
        }
    }

    private int byteRangeInvoke()
    {
        if (!CommonDef.isSupportCertification())
        {
            Log.d(TAG, "Not set seekno becase no suppport certification");
            return 0;
        }
        Parcel requestParcel = Parcel.obtain();
        requestParcel.writeInterfaceToken("android.media.IMediaPlayer");
        requestParcel.writeInt(HiMediaPlayerInvoke.CMD_SET_NOT_SUPPORT_BYTERANGE); // CMD_SET_NOT_SUPPORT_BYTERANGE
        requestParcel.writeInt(1); //Parameter for CMD_SET_NOT_SUPPORT_BYTERANGE
        Parcel replayParcel = Parcel.obtain();
        try
        {
            mediaPlayerInvoke(mediaPlayer, requestParcel, replayParcel);
        }
        catch (IllegalArgumentException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (NoSuchMethodException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (IllegalAccessException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        catch (InvocationTargetException e)
        {
            Log.e(TAG, "MediaPlayer.invoke", e);
        }
        int ret = replayParcel.readInt();
        requestParcel.recycle();
        replayParcel.recycle();
        return ret;
    }

    private void mediaPlayerInvoke(MediaPlayer mediaPlayer, Parcel request, Parcel reply)
            throws NoSuchMethodException, IllegalArgumentException, IllegalAccessException,
            InvocationTargetException
    {
        Class<MediaPlayer> mediaPlayerClass = MediaPlayer.class;
        Method invokeMethod = mediaPlayerClass.getMethod("invoke", Parcel.class, Parcel.class);
        invokeMethod.invoke(mediaPlayer, request, reply);
    }

    class NetworkTimerTask extends TimerTask
    {
        private int extra;

        public NetworkTimerTask(int extra)
        {
            super();
            this.extra = extra;
        }

        public void run()
        {
            Log.d(TAG, "network down, ready to finish");
            Message msg = mUIHandler.obtainMessage(extra, Action.SHOW_NETWORK_DOWN_TOAST);
            mUIHandler.sendMessage(msg);
            closeMainActivity(false);
        }
    }

    private void closeMainActivity(boolean isDelay)
    {
        if (null != mIPlayerMainWnd)
        {
            mIPlayerMainWnd.closeActivity(isDelay);
        }
    }

    class SurfaceCallback implements SurfaceHolder.Callback
    {
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
        {
            Log.d(TAG, "surfaceChanged");
        }

        public void surfaceCreated(SurfaceHolder holder)
        {
            Log.d(TAG, "surfaceCreate");
            if (null != mUrl)
            {
                showTitleBarAndProgressBar();
            }
            // mediaPlayerHandler.removeMessages(0, Action.InitPlayer);
            // Message msg = mediaPlayerHandler.obtainMessage(0, Action.InitPlayer);
            // mediaPlayerHandler.sendMessage(msg);
            try {
                mSurfaceLock.lock();
                mSurfaceCreated = true;
                mSurfaceCondition.signal();
            } finally {
                mSurfaceLock.unlock();
            }

        }

        public void surfaceDestroyed(SurfaceHolder holder)
        {
            Log.d(TAG, "surfaceDestroyed");
            try {
                mSurfaceLock.lock();
                mSurfaceCreated = false;
                mSurfaceCondition.signal();
            } finally {
                mSurfaceLock.unlock();
            }
        }
    }

    class OnPreparedListener implements MediaPlayer.OnPreparedListener
    {

        @Override
        public void onPrepared(MediaPlayer mp)
        {
            setHiPlayerTimerProc("after prepare");
            Log.d(TAG, "onPrepared() dmrCurrentState=" + dmrCurrentState);
            isPrepared = true;
            mediaPlayerHandler.removeMessages(0, Action.InitPlayer);
            mediaPlayerStatus = MediaPlayerUtil.Status.Prepared;
            mediaPlayerHandler.sendMessage(mediaPlayerHandler.obtainMessage(0, Action.GetDuration));
            if (dmrCurrentState == Constant.DMR_STATE_PLAYING)
            {
                playerStart();
            }
            else
            {
                mediaPlayerHandler.sendMessage(mediaPlayerHandler.obtainMessage(0,
                        Action.StartPlayerWithOutNotify));
                mediaPlayerHandler.sendMessage(mediaPlayerHandler.obtainMessage(0,
                        Action.PausePlayerWithOutNotify));
            }
            seekDelayHandler.sendEmptyMessage(PREPARE_FINISH);// seek delay
            // prepareLock.lock();
            // try {
            // prepareStatus = PrepareStatus.PrepareSucces;
            // prepareCondition.signal();
            // } finally {
            // prepareLock.unlock();
            // }

            if (setBufferTimeConfig(mp,
                        BUFFER_TIME_START_LINE,
                        BUFFER_TIME_ENOUGH_LINE,
                        BUFFER_TIME_FULL_LINE) == -1) {
                Log.e(TAG, "setBufferTimeConfig return false");
            }

            setBufferUnderrun(mp, 1);
            // mDuration = mp.getDuration();
            // mDurationTextView.setText(timeFromIntToString(mDuration));
            mHandler.sendEmptyMessage(UPDATE_VIDEO_INFO);
            if (mUpdateCurrentPositionTimer == null)
            {
                mUpdateCurrentPositionTimer = new Timer();
                mUpdateCurrentPositionTimer.scheduleAtFixedRate(new TimerTask()
                {

                    @Override
                    public void run()
                    {
                        Message msg = mediaPlayerHandler.obtainMessage(0, Action.TimeUpdate);
                        mediaPlayerHandler.sendMessage(msg);
                    }
                }, 0, 1000);
            }
        }
    }

    class UpdateBufferTimerTask extends TimerTask
    {
        public void run()
        {
            updataBufferProgress();
        }
    }

    class UpdateNetWorkSpeedTimerTask extends TimerTask
    {
        public void run()
        {
            Message msg = mUIHandler.obtainMessage(0, Action.UpdateNetWorkSpeed);
            mUIHandler.sendMessage(msg);
        }
    }

    class OnErrorListener implements MediaPlayer.OnErrorListener
    {

        @Override
        public boolean onError(MediaPlayer mp, int what, int extra)
        {
            Log.e(TAG, "onError what=" + what + " extra=" + extra);
            if (what == MediaPlayer.MEDIA_ERROR_UNKNOWN && extra == 0)
            {
                Toast.makeText(mContext, R.string.media_error_unknow, Toast.LENGTH_SHORT).show();
               // if (mController == Controller.DMP)
               // {//DMP play next music,but DMR close Activity
               //     playNext();
               //     return true;
               // }
            }
            synchronized (mLockObject)
            {//add mLockObject for TQE, isResetting is locked
                if (isResetting)
                {
                    return true;
                }
                else
                {
                    closeMainActivity(false);
                }
            }
            return false;
        }
    }

    class OnInfoListener implements MediaPlayer.OnInfoListener
    {

        @Override
        public boolean onInfo(MediaPlayer mp, int what, int extra)
        {
            Log.d(TAG, "onInfo(what=" + what + ", extra=" + extra + ")");

            if (HiMediaPlayer.MEDIA_INFO_NETWORK == what)
            {
                if ((extra == enFormatMsgNetwork.FORMAT_MSG_NETWORK_ERROR_CONNECT_FAILED.ordinal())
                        || (enFormatMsgNetwork.FORMAT_MSG_NETWORK_ERROR_DISCONNECT.ordinal() == extra)
                        || (enFormatMsgNetwork.FORMAT_MSG_NETWORK_ERROR_NOT_FOUND.ordinal() == extra)
                        || (enFormatMsgNetwork.FORMAT_MSG_NETWORK_ERROR_UNKNOWN.ordinal() == extra)
                        || (enFormatMsgNetwork.FORMAT_MSG_NETWORK_ERROR_TIMEOUT.ordinal() == extra))
                {
                    Log.d(TAG, "schedule to finish because network is down");
                    if (mNetworkTimer == null)
                    {
                        mNetworkTimer = new Timer();
                        mNetworkTimer.schedule(new NetworkTimerTask(extra), TIMEOUT);
                    }
                }
                else if (enFormatMsgNetwork.FORMAT_MSG_NETWORK_NORMAL.ordinal() == extra)
                {
                    Log.d(TAG, "cancel schedule to finish");
                    if (mNetworkTimer != null)
                    {
                        mNetworkTimer.cancel();
                        mNetworkTimer = null;
                    }
                }
            }
            else if (MediaPlayer.MEDIA_INFO_BUFFERING_START == what)
            {
                // Buffer Start
                Log.d(TAG, "buffer start");
                mBufferStatus = BufferStatus.Start;
                isLoadingShowing = true;
                showTitleBarAndProgressBar();
            }
            else if (MediaPlayer.MEDIA_INFO_BUFFERING_END == what)
            {
                // Buffer End
                Log.d(TAG, "buffer enough");
                mBufferStatus = BufferStatus.End;
                Message msg = mUIHandler.obtainMessage(0, Action.HideBufferingProgressBar);
                mUIHandler.sendMessage(msg);
                isLoadingShowing = false;
            }
            else if(HiMediaPlayer.MEDIA_INFO_PREPARE_PROGRESS == what)
            {
                Log.d(TAG, "prepare progress " + extra);
                Message msg = mUIHandler.obtainMessage(0, Action.UpdatePrepareProgress);
                msg.what = extra;
                mUIHandler.sendMessage(msg);
            }
            return false;
        }

    }


    class OnSeekBarChangeListener implements SeekBar.OnSeekBarChangeListener
    {

        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser)
        {
            if (fromUser)
            {
                isSeekBarMoving = true;
                mSeekTimeTextView.setVisibility(View.VISIBLE);
                mSeekTimeTextView.setText(timeFromIntToString((int) (mDuration * progress * 0.01)));
            }
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar)
        {
            Log.d(TAG, "begin to seek");
            isSeekBarMoving = true;
            mSeekTimeTextView.setVisibility(View.VISIBLE);
        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar)
        {
            Log.d(TAG, "seek end");
            isSeekBarMoving = false;
            mSeekTimeTextView.setVisibility(View.INVISIBLE);
            playerSeekTo((int) (seekBar.getProgress() * 0.01 * mDuration));
        }

    }

    class OnSeekBarClickListener implements View.OnClickListener
    {

        @Override
        public void onClick(View v)
        {
            if (isSeekBarMoving && !isSeeking)
            {
                isSeekBarMoving = false;
                mSeekTimeTextView.setVisibility(View.INVISIBLE);
                playerSeekTo((int) (mSeekBar.getProgress() * 0.01 * mDuration));
                mSeekBar.setCanMove(false);
            }
        }

    }

    class OnFocusChangeListener implements View.OnFocusChangeListener
    {

        @Override
        public void onFocusChange(View v, boolean hasFocus)
        {
            if (!hasFocus)
            {
                isSeekBarMoving = false;
            }
        }

    }

    class OnSeekCompleteListener implements MediaPlayer.OnSeekCompleteListener
    {

        @Override
        public void onSeekComplete(MediaPlayer mp)
        {
            Log.d(TAG, "onSeekComplete dmrCurrentState=" + dmrCurrentState+",isPauseForBufferEmpty="+isPauseForBufferEmpty);
            setHiPlayerTimerProc("after seek");
            bufferCleared();

            seekLock.lock();
            try
            {
                isSeeking = false;
                seekCondition.signal();
                mSeekBar.setCanMove(true);
            }
            finally
            {
                seekLock.unlock();
            }
            Log.d(TAG, "onSeekComplete again dmrPreState=" + dmrPreState);
            if (Constant.DMR_STATE_STOPPED == dmrCurrentState)
            {
                Log.d(TAG, "onSeekComplete but current is stop so do nothing");
                return;
            }
            if (seekDelayFlag == true && dataHandler != null)
            {
                seekTo(seekModeHandler, dataHandler);
            }
            seekDelayFlag = false;
            dataHandler = null;
            if (dmrPreState == Constant.DMR_STATE_STOPPED)
            {
                stopNotify();
                dmrCurrentState = Constant.DMR_STATE_STOPPED;
            }
            else if (dmrPreState == Constant.DMR_STATE_PLAYING)
            {
                startNotify();
                dmrCurrentState = Constant.DMR_STATE_PLAYING;
            }
            else if (dmrPreState == Constant.DMR_STATE_PAUSED_PLAYBACK)
            {
                pauseNotify();
                dmrCurrentState = Constant.DMR_STATE_PAUSED_PLAYBACK;
            }
            dmrPreState = Constant.DMR_STATE_TRANSITIONING;
            // don't start when onSeekComplete
            // playerResume();
        }

    }

    class OnBufferingUpdateListener implements MediaPlayer.OnBufferingUpdateListener
    {

        @Override
        public void onBufferingUpdate(MediaPlayer mp, int percent)
        {
            // Log.d(TAG, "onBufferingUpdate: "+percent);
            Message msg = mUIHandler.obtainMessage(percent, Action.BufferUpdate);
            mUIHandler.sendMessage(msg);
        }

    }

    private void startNotify()
    {
        Log.d(TAG, "enter startNotify");
        if (mController != Controller.DMR)
        {
            return;
        }
        if (dmrServer != null)
        {
            try
            {
                dmrServer.getDMRCallback().playNotify();
            }
            catch (RemoteException e)
            {
                Log.e(TAG, "playNotify", e);
            }
        }
    }

    private void stopNotify()
    {
        if (mController != Controller.DMR)
        {
            return;
        }
        if (dmrServer != null)
        {
            try
            {
                dmrServer.getDMRCallback().stopNotify();
            }
            catch (RemoteException e)
            {
                Log.e(TAG, "stopNotify", e);
            }
        }
    }

    private void pauseNotify()
    {
        if (mController != Controller.DMR)
        {
            return;
        }
        if (dmrServer != null)
        {
            try
            {
                dmrServer.getDMRCallback().pauseNotify();
            }
            catch (RemoteException e)
            {
                Log.e(TAG, "pauseNotify", e);
            }
        }
    }

    private void bufferCleared()
    {
        if (isPauseForBufferEmpty)
        {
            if (mediaPlayerStatus.validAction(MediaPlayerUtil.Action.start))
            {
                playerResume();
            }
        }
    }

    @Override
    public FileType getSubWndType()
    {
        return null;
    }

    @Override
    public void setMainWnd(IPlayerMainWnd parent)
    {
        mIPlayerMainWnd = parent;
    }

    @Override
    public boolean isInited()
    {
        return mIsInited;
    }

    public void setBaseAction(BaseAction action)
    {
        if (fetchPlayListThread != null && fetchPlayListThread.isAlive())
        {
            fetchPlayListThread.interruptThread();
            fetchPlayListThread.registerEventCallback(null);
            fetchPlayListThread.interrupt();
        }
        fetchPlayListThread = null;

        if ((mController == Controller.DMR) && (mediaPlayerStatus.validAction(MediaPlayerUtil.Action.stop))
             && (dmrCurrentState != Constant.DMR_STATE_PAUSED_PLAYBACK) && (!isSeeking))
        {
            if (mUpdateCurrentPositionTimer != null)
            {
                mUpdateCurrentPositionTimer.cancel();
                mUpdateCurrentPositionTimer = null;
            }

            dmrPreState = dmrCurrentState;
            dmrCurrentState = Constant.DMR_STATE_STOPPED;
            if(null != mediaPlayer) //TODO why mediaPlayer is null sometimes.
            {
                mediaPlayer.stop();
            }
            mediaPlayerStatus = MediaPlayerUtil.Status.Stopped;
            isPrepared = false;
            stopNotify();
            Log.d(TAG,"setBaseAction stop");
        }

        Log.d(TAG, "setBaseAction action=" + action);
        Log.d(TAG, "setBaseAction ,dmrCurrentState=" + dmrCurrentState);
        if (action instanceof PlayAction)
        {
            if(isSeeking)
            {
                Log.d(TAG, "isSeeking ,don't play util seek complete.");
                return;
            }
            mPlayAction = (PlayAction) action;// getIntent().getSerializableExtra(Constant.FILE_PLAY_PATH);
            if (dmrCurrentState == Constant.DMR_STATE_PAUSED_PLAYBACK)
            {
                String strUrl = mPlayAction.getUrl();
                if (strUrl.equals(mUrl))
                {
                    playerResume();
                    dmrPreState = dmrCurrentState;
                    dmrCurrentState = Constant.DMR_STATE_PLAYING;
                    return;
                }
            }
            dmrCurrentState = Constant.DMR_STATE_STOPPED;
            playlist.clear();
            Log.d(TAG, "mPlayAction.getController():" + mPlayAction.getController());
            mController = mPlayAction.getController();
            mSetURLAction = null;
            mSeekAction = null;
            dmrPreState = Constant.DMR_STATE_STOPPED;
            dmrCurrentState = Constant.DMR_STATE_PLAYING;
        }
        else if (action instanceof SeekAction)
        {
            dmrCurrentState = Constant.DMR_STATE_STOPPED;
            playlist.clear();
            mSeekAction = (SeekAction) action;// getIntent().getSerializableExtra(Constant.FILE_PLAY_PATH);
            mController = mSeekAction.getController();
            Log.d(TAG, "mSeekAction.getController():" + mSeekAction.getController());
            mPlayAction = null;
            mSetURLAction = null;
            seekModeHandler = mSeekAction.getMode();
            dataHandler = mSeekAction.getData();
            seekDelayFlag = true;
        }
        else if (action instanceof SetURLAction)
        {
            dmrCurrentState = Constant.DMR_STATE_STOPPED;
            playlist.clear();
            Log.d(TAG, "SetURLAction");
            mSetURLAction = (SetURLAction) action;// getIntent().getSerializableExtra(Constant.FILE_PLAY_PATH);
            mController = mSetURLAction.getController();
            mPlayAction = null;
            mSeekAction = null;
        }
        else
        {
            Log.d(TAG, "sa.BaseAction():");
        }

        Log.d(TAG, "current controller: " + mController);
        if (mController == Controller.DMR)
        {
            if (null == dmrServer)
            {
                if (ServiceManager.checkService("dmr") == null)
                {
                    Log.d(TAG, "dmr service is not exist");
                    Toast.makeText(mContext, "dmr binder is not in ServiceManager", Toast.LENGTH_LONG).show();
                    closeMainActivity(false);
                }
                else
                {
                    Log.d(TAG, "dmr service is exist");
                    dmrServer = IDMRServer.Stub.asInterface(ServiceManager.getService("dmr"));
                }
                if (dmrServer != null)
                {
                    try
                    {
                        dmrServer.registerPlayerController(new DMRPlayerController());
                    }
                    catch (RemoteException e)
                    {
                        Log.e(TAG, "registerPlayerController", e);
                    }
                }
            }
            if (mPlayAction != null)
            {
                mUrl = mPlayAction.getUrl();
                fileAllStringTime = mPlayAction.getFileInfo().getDuration();
            }
            else if (mSeekAction != null)
                mUrl = mSeekAction.getUrl();
            else if (mSetURLAction != null)
                mUrl = mSetURLAction.getUrl();

            playlist.add(mUrl);
            PlayList.getinstance().setlist(playlist, 0);

        }
        else if (mController == Controller.DMP)
        {
            if (null != mPlayAction)
            {
                mDMSFile = (DMSFile) mPlayAction.getFile();
                mUrl = mDMSFile.getUrl();
                playlist.add(mUrl);
                PlayList.getinstance().setlist(playlist, 0);
                fetchPlayListThread = new FetchPlayListThread(mContext,mDMSFile, FileType.VIDEO, playlist,
                        dms_files);
                fetchPlayListThread.registerEventCallback(new UpdatePlayListEventCallback());
                fetchPlayListThread.start();
                dmrCurrentState = Constant.DMR_STATE_PLAYING;
            }
            else
            {
                Log.e(TAG, "DMP:mPlayAction is null");
            }
        }
        else if (mController == Controller.LOCAL)
        {
            if (null != mPlayAction)
            {
                LocalFile localFile = (LocalFile) mPlayAction.getFile();
                if (localFile != null)
                {
                    mUrl = localFile.getFile().getAbsolutePath();
                    playlist.add(mUrl);
                    PlayList.getinstance().setlist(playlist, 0);
                }
            }
            else
            {
                Log.e(TAG, "local :mPlayAction is null");
            }
        }

        Log.d(TAG, "play url: " + mUrl);
        this.init(mParentView);
        mediaPlayerStatus = MediaPlayerUtil.Status.Idle;
    }
    public void setContentType(String ContentType)
    {
        contenttype = ContentType;
    }

    public void setContentLength(long length)
    {
        contentlength = length;
    }

    private void setHiPlayerTimerProc(String action)
    {
       if (mController != Controller.DMR)
       {
           return;
       }
       if (dmrServer != null)
       {
           try
           {
               Log.d(TAG, "VideoPlayerSubWnd setHiPlayerTimerProc: " + action);
               dmrServer.getDMRCallback().setProcValue("PlayerTimer", action,
                                new SimpleDateFormat("HH:mm:ss.SSS").format(new Date()));
           }
           catch (RemoteException e)
           {
               Log.e(TAG, "setHiPlayerTimerProc", e);
           }
       }
    }
}
