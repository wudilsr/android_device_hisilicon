package com.hisilicon.dlna.player;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.app.ActivityManager;
import android.app.AlertDialog;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.PaintFlagsDrawFilter;
import android.graphics.PixelFormat;
import android.graphics.PorterDuff.Mode;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.media.AudioManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.os.SystemClock;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.animation.AnimationUtils;
import android.widget.ImageButton;
import android.widget.ImageSwitcher;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ViewSwitcher;

import com.hisilicon.dlna.dmp.*;
import com.hisilicon.dlna.dmr.*;
import com.hisilicon.dlna.dmr.action.*;
import com.hisilicon.dlna.file.DMSFile;
import com.hisilicon.dlna.file.FileType;
import com.hisilicon.dlna.file.LocalFile;
import com.hisilicon.dlna.player.DecodeImageThread.DecodeError;
import com.hisilicon.dlna.util.CommonDef;

public class ImagePlayerSubWnd extends PlayerSubWnd implements PlayerInterface,
        DecodeFinishListener
{
    private static final String TAG = "ImagePlayerSubWnd";

    private static final int MESSAGE_LOADFAIL = 0;
    private static final int MESSAGE_LOADFINISH = 1;
    private static final int MESSAGE_LOADCHANGEIMAGE = 2;
    private static final int MESSAGE_SHOW_TOAST_GET_PLAYLIST_FAIL = 3;
    private static final int MESSAGE_OUTOFMEMORY = 4;
    private static final int MESSAGE_CONNECT_TIMEOUT = 5;
    private static final int MESSAGE_FAILED_GET_FILE = 6;
    private static final int SLIDE_FINISH = 101;
    private static final int SLIDE_FAIL = 102;
    private static final int SHOW_LOADING = 0x105;
    private static final int HIDE_LOADING = 0x106;
    private static final int WAITE_CREATE_FINISH_COUNT = 200;

    private IPlayerMainWnd mIPlayerMainWnd = null;
    private Context mContext = null;
    private View mParentView = null;

    private AlertDialog.Builder alertUnsupportDialogBuilder;
    private AlertDialog.Builder alertOutOfMemoryDialogBuilder;
    private AlertDialog.Builder alertConnectTimeoutDialogBuilder;
    private AlertDialog.Builder alertFailedGetFileDialogBuilder;
    String filePath = null;
    int fileType;
    Timer hide_timer = new Timer();
    Timer stopAction_timer = new Timer();
    private TimerManager mTimerManager;
    private FetchPlayListThread fetchPlayListThread = null;

    private SurfaceView mSurfaceView;
    private boolean isViewSurfaceCreated = false;
    private SurfaceView miniView;
    private String photoName;
    private TextView name_tv = null;
    private TextView date_tv = null;
    private TextView speedText = null;
    private Bitmap mBitmap;
    private BitmapDrawable mBitmapDrawable;
    private ImageButton backBtn = null;
    private ImageButton previousBtn = null;
    private ImageButton nextBtn = null;
    private ImageButton antiClockRotateBtn = null;
    private ImageButton clockRotateBtn = null;
    private ImageButton zoomBtn = null;
    private ImageButton slideSpeedBtn = null;
    private ImageView slideView = null;
    private RotateAngle rotateAngle = RotateAngle.ANGLE0;
    private ZoomTimes zoomTimes = ZoomTimes.ORIGIN;
    private ImageButton playBtn = null;
    private Timer slideTimer = null;
    private SlideSpeed slideSpeed = SlideSpeed.NORMAL;
    private boolean isSlideRunning = false;
    private LinearLayout inforbar_top = null;
    private LinearLayout inforbar_bottom = null;
    private int x, y;
    private float be;
    private PaintFlagsDrawFilter paintFilter = new PaintFlagsDrawFilter(0, Paint.ANTI_ALIAS_FLAG
            | Paint.FILTER_BITMAP_FLAG);

    private String str_photoName = null;
    private String str_photoResolution = null;
    private String str_photoDate = null;
    private String str_photoType = null;
    private boolean PHOTO_SHOWN = true;
    private boolean isGif = false;
    private Controller mController = Controller.DMP;
    // private SetURLAction pa;
    private SetURLAction sa;
    private PlayAction pa;
    private DMSFile mDMSFile = null;
    private IDMRServer dmrServer;
    private List<String> playlist = new ArrayList<String>();
    private List<DMSFile> dms_files = new ArrayList<DMSFile>();
    // private IDMRPlayerCallback callback;
    private float miniRatioX;
    private float miniRatioY;
    private Rect originSize;
    private ImageSwitcher imageSwitcher;
    private ImageFactory imageFactory;
    private View cur_focus_bottom = null; // tianjia@20120419
    private Thread loadImageThread;
    private DecodeImageThread decodeThread;
    private boolean isInfoBarVisible = true;
    private boolean isPlayOrientationNext = true;
    private boolean isNeedImageLoadHandler = true;
    private View mLoadingView;
    private SetURLAction setActionRecode = null;
    private SetURLAction setActionRecodeTemp = null;
    private final Lock setActionRecodeMutex = new ReentrantLock(true);

    private AudioManager audioManager = null;
    private int dmrCurrentState = Constant.DMR_STATE_NO_MEDIA_PRESENT;

    private boolean mIsInited = false;
    private String mContentType = null;
    private long mContentLength = 0;

    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        super.onCreateView(inflater, container, savedInstanceState);
        mParentView = inflater.inflate(R.layout.imagelayout, container, false);
        Log.e(TAG, "===== mParentView=" + mParentView);
        mContext = inflater.getContext();

        mTimerManager = TimerManager.getInstance();
        mLoadingView = mParentView.findViewById(R.id.loading_spinner_img);
        mLoadingView.setVisibility(View.GONE);

        imageSwitcher = (ImageSwitcher) mParentView.findViewById(R.id.imageSwitcher);
        imageSwitcher.setOnClickListener(new MouseClickListener());
        imageFactory = new ImageFactory();
        imageSwitcher.setFactory(imageFactory);
        imageSwitcher.setInAnimation(AnimationUtils.loadAnimation(mContext, R.anim.slide_alpha_in));
        imageSwitcher.setOutAnimation(AnimationUtils
                .loadAnimation(mContext, R.anim.slide_alpha_out));

        BaseAction actionClass = (BaseAction) getActivity().getIntent().getSerializableExtra(
                Constant.FILE_PLAY_PATH);
        setBaseAction(actionClass);

        String contentType = (String)this.getActivity().getIntent()
                .getSerializableExtra(Constant.FILE_CONTENT_TYPE);
        if(null != contentType)
        {
            setContentType(contentType.toLowerCase());
        }

        String contentLengthString = (String)this.getActivity().getIntent()
                .getSerializableExtra(Constant.FILE_CONTENT_LENGTH);
        long contentLength = 0;
        if(contentLengthString != null)
            contentLength = Long.parseLong(contentLengthString);
        Log.d(TAG," content type : " + contentType + "length : " + contentLength);
        setContentLength(contentLength);

        initAlertDialog();

        audioManager = (AudioManager) mContext.getSystemService(Service.AUDIO_SERVICE);
        decodeThread = new DecodeImageThread();
        decodeThread.registerFinishListener(this);
        decodeThread.start();
        mSurfaceView = (SurfaceView) mParentView.findViewById(R.id.myView);
        isViewSurfaceCreated = false;
        mSurfaceView.setOnClickListener(new MouseClickListener());
        mSurfaceView.getHolder().addCallback(new SurfaceCallback());
        miniView = (SurfaceView) mParentView.findViewById(R.id.miniView);
        miniView.setVisibility(View.GONE);
        miniView.getHolder().addCallback(new MiniSurfaceCallback());
        miniView.setZOrderOnTop(true);
        miniView.getHolder().setFormat(PixelFormat.TRANSPARENT);
        originSize = new Rect();

        if (mController == Controller.DMR)
        {
            try
            {
                dmrServer.registerPlayerController(new DMRPlayerController());
            }
            catch (Exception e)
            {
                Log.e(TAG, "dmr callback", e);
            }
        }

        initialView();

        mIsInited = true;
        return mParentView;
    }

    public void onResume()
    {
        Log.d(TAG, "onResume " + this.toString() + ",zhl time=" + SystemClock.elapsedRealtime());
        super.onResume();
        isNeedImageLoadHandler = true;
        Log.d(TAG, "onResume() end");
    }

    /**
     * when some other app block this activity, call finish to kill this activity
     */

    /**
     * 当Activity到后台时，调用finish结束应用
     */
    public void onPause()
    {
        Log.d(TAG, "onPause " + this.toString() + ",zhl time=" + SystemClock.elapsedRealtime());
        mIsInited = false;
        decodeThread.unregisterFinishListener(ImagePlayerSubWnd.this);
        decodeThread.quit();

        if (dmrCurrentState != Constant.DMR_STATE_STOPPED)
        {
            stopNotify();
            // Avoid repeatedly sending stop
        }
        else
        {
            Log.d(TAG, "Image Already in Stop,don't send stop action");
        }


        if (null != dmrServer)
        {
            try
            {
                dmrServer.unregisterPlayerController();
            }
            catch (RemoteException e)
            {
                Log.e(TAG, "onPause unregisterPlayerController", e);
            }
            dmrServer = null;
        }

        cancelSlide();

        playlist.clear();
        dms_files.clear();
        if (loadImageThread != null)
        {
            loadImageThread.interrupt();
        }
        loadImageThread = null;

        if (mBitmap != null && !mBitmap.isRecycled())
        {
            mBitmap.recycle();
            mBitmap = null;
            System.gc();
        }
        if (fetchPlayListThread != null && fetchPlayListThread.isAlive())
        {
            fetchPlayListThread.interruptThread();
            fetchPlayListThread.registerEventCallback(null);
            fetchPlayListThread.interrupt();
        }
        fetchPlayListThread = null;
        hideLoadingBar();
        isNeedImageLoadHandler = false;
        warningShowDismiss();
        super.onPause();
    }

    public void onDestroy()
    {
        Log.d(TAG, "onDestroy()");
        super.onDestroy();
    }

    public KeyDoResult keyUpDispatch(int keyCode, KeyEvent event)
    {
        Log.d(TAG, "onKeyUp keyCode:" + keyCode);
        switch (keyCode)
        {
            case KeyEvent.KEYCODE_DPAD_LEFT: // 方向键左，图片切换至上一张
                if (inforbar_top.getVisibility() == View.VISIBLE)
                    break;
            case KeyEvent.KEYCODE_PAGE_UP: // previous item
                // add by c00190074 在放大过程中屏蔽上一张下一张
                if (zoomTimes != ZoomTimes.ORIGIN)
                {
                    break;
                }
                showPrevious();
                break;
            case KeyEvent.KEYCODE_DPAD_RIGHT: // 方向键右，图片切换至下一张
                if (inforbar_top.getVisibility() == View.VISIBLE)
                    break;
            case KeyEvent.KEYCODE_PAGE_DOWN:
                // add by c00190074 在放大过程中屏蔽上一张下一张
                if (zoomTimes != ZoomTimes.ORIGIN)
                {
                    break;
                }
                showNext();
                break;
            case KeyEvent.KEYCODE_BACK:
                if (isInfoBarVisible)
                {
                    Log.d(TAG, "info bar visible");
                    hideView();
                    return KeyDoResult.DO_OVER;
                }
                if (zoomTimes != ZoomTimes.ORIGIN)
                {
                    showImage();
                    return KeyDoResult.DO_OVER;
                }
                break;
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
                if (isSlideRunning)
                {
                    cancelSlide();
                }
                else
                {
                    restartSlide();
                }
                break;
            default:
                break;
        }
        return KeyDoResult.DO_NOTHING;
    }

    public KeyDoResult keyDownDispatch(int keyCode, KeyEvent event)
    {
        if (keyCode == KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE)
        {
            // shield play button
            return KeyDoResult.DO_OVER;
        }
        if (keyCode == KeyEvent.KEYCODE_MEDIA_STOP)
        {
            cancelSlide();
            closeMainActivity(false);
            return KeyDoResult.DO_OVER;
        }

        if (mBitmap == null || inforbar_bottom.getVisibility() == View.VISIBLE)
        {
            return KeyDoResult.DO_NOTHING;
        }
        if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN)
        {
            if (mBitmap.getHeight() * zoomTimes.getValue() * be > mSurfaceView.getHeight())
            {
                if (y + mSurfaceView.getHeight() < mBitmap.getHeight() * zoomTimes.getValue() * be - 10)
                {
                    y += 10;
                    moveView();
                }
            }
        }
        else if (keyCode == KeyEvent.KEYCODE_DPAD_UP)
        {
            if (mBitmap.getHeight() * zoomTimes.getValue() * be > mSurfaceView.getHeight())
            {
                if (y > 10)
                {
                    y -= 10;
                    moveView();
                }
            }
        }
        else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT)
        {
            if (mBitmap.getWidth() * zoomTimes.getValue() * be > mSurfaceView.getWidth())
            {
                if (x > 10)
                {
                    x -= 10;
                    moveView();
                }
            }
        }
        else if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT)
        {
            if (mBitmap.getWidth() * zoomTimes.getValue() * be > mSurfaceView.getWidth())
            {
                if (x + mSurfaceView.getWidth() < mBitmap.getWidth() * zoomTimes.getValue() * be - 10)
                {
                    x += 10;
                    moveView();
                }
            }
        }
        return KeyDoResult.DO_NOTHING;
    }

    /**
     * update UI components(SurfaceView, ListView...)
     */

    /**
     * 更新各UI组件(SurfaceView, ListView...)
     */
    private Handler imageLoadHandler = new Handler()
    {
        public void handleMessage(Message msg)
        {
            if(!isNeedImageLoadHandler)
            {
                Log.d(TAG,"no need dispatchMessage:" + msg.what);
                return;
            }
            switch (msg.what)
            {
                case MESSAGE_LOADFINISH:
                    showImage();
                    break;
                case MESSAGE_LOADFAIL:
                    warningShowUnsupport();
                    break;
                case MESSAGE_LOADCHANGEIMAGE:
                    showChangedImage();
                    break;
                case MESSAGE_SHOW_TOAST_GET_PLAYLIST_FAIL:
                    Toast.makeText(mContext, R.string.fail_get_playlist, Toast.LENGTH_LONG).show();
                    break;
                case MESSAGE_OUTOFMEMORY:
                    hideLoadingBar();
                    dialogOutOfMemory = alertOutOfMemoryDialogBuilder.create();
                    dialogOutOfMemory.show();
                    PHOTO_SHOWN = true;
                    break;
                case MESSAGE_CONNECT_TIMEOUT:
                    hideLoadingBar();
                    dialogConnectTimeout = alertConnectTimeoutDialogBuilder.create();
                    dialogConnectTimeout.show();
                    PHOTO_SHOWN = true;
                    break;
                case MESSAGE_FAILED_GET_FILE:
                    hideLoadingBar();
                    dialogFailedGetFile = alertFailedGetFileDialogBuilder.create();
                    dialogFailedGetFile.show();
                    PHOTO_SHOWN = true;
                    break;
                case SHOW_LOADING:
                    mLoadingView.setVisibility(View.VISIBLE);
                    break;
                case HIDE_LOADING:
                    mLoadingView.setVisibility(View.GONE);
                    break;
            }
        }
    };

    private void showLoadingBar()
    {
        imageLoadHandler.sendEmptyMessage(SHOW_LOADING);
    }

    private void hideLoadingBar()
    {
        imageLoadHandler.sendEmptyMessage(HIDE_LOADING);
    }

    private Rect getDstRect()
    {
        Rect dstRect = new Rect();
        int x = (mSurfaceView.getWidth() - mBitmap.getWidth()) / 2;
        int y = (mSurfaceView.getHeight() - mBitmap.getHeight()) / 2;
        x = (x > 0) ? x : 0;
        y = (y > 0) ? y : 0;
        boolean isVertical = mBitmap.getWidth() * 1.0 / mBitmap.getHeight() < mSurfaceView.getWidth()
                * 1.0 / mSurfaceView.getHeight();
        if (!isVertical)
        {
            if (x > 0)
            {
                dstRect.left = x;
                dstRect.right = x + mBitmap.getWidth();
                dstRect.top = y;
                dstRect.bottom = y + mBitmap.getHeight();
            }
            else
            {
                // 这时图片有可能比画布大
                dstRect.left = 0;
                dstRect.right = mSurfaceView.getWidth();
                int newHeight = (int) (mSurfaceView.getWidth() * 1.0 * mBitmap.getHeight() / mBitmap
                        .getWidth());
                be = mSurfaceView.getWidth() / (float) mBitmap.getWidth();
                dstRect.top = (mSurfaceView.getHeight() - newHeight) / 2;
                dstRect.bottom = dstRect.top + newHeight;
            }
        }
        else
        {
            if (y > 0)
            {
                dstRect.top = y;
                dstRect.bottom = y + mBitmap.getHeight();
                dstRect.left = x;
                dstRect.right = x + mBitmap.getWidth();
            }
            else
            {
                dstRect.top = 0;
                dstRect.bottom = mSurfaceView.getHeight();
                int newWidth = (int) (mSurfaceView.getHeight() * 1.0 * mBitmap.getWidth() / mBitmap
                        .getHeight());
                be = mSurfaceView.getHeight() / (float) mBitmap.getHeight();
                dstRect.left = (mSurfaceView.getWidth() - newWidth) / 2;
                dstRect.right = dstRect.left + newWidth;
            }
        }
        return dstRect;
    }

    /**
     * call this funciton to display image when decoding process is finished
     */

    /**
     * 在解码完成时，调用此函数显示图片
     */
    private void showImage()
    {
        this.x = 0;
        this.y = 0;
        miniView.setVisibility(View.GONE);
        if (mController == Controller.DMR)
        {
            if (dmrServer != null)
            {
                try
                {
                    if (dmrCurrentState == Constant.DMR_STATE_PLAYING)
                    {
                        dmrServer.getDMRCallback().playNotify();
                    }
                    else
                    {
                        Log.d(TAG, "dmrCurrentState is not PLAYING,so do not send playnotify");
                    }
                }
                catch (RemoteException e)
                {
                    Log.e(TAG, "playNotify", e);
                }
            }
        }

        if (mBitmap == null)
        {
            return;
        }

        be = 1;
        zoomTimes = ZoomTimes.ORIGIN;
        rotateAngle = RotateAngle.ANGLE0;
        hideLoadingBar();
        Rect srcRect = new Rect(0, 0, mBitmap.getWidth(), mBitmap.getHeight());
        Rect dstRect = getDstRect();

        /*
         * originSize.left = x; originSize.top = y; originSize.right = x+mBitmap.getWidth();
         * originSize.bottom = y+mBitmap.getHeight();
         */
        originSize = dstRect;
        SurfaceHolder holder = mSurfaceView.getHolder();
        Canvas canvas = holder.lockCanvas();
        if (canvas != null)
        {
            canvas.setDrawFilter(paintFilter);
            canvas.drawARGB(255, 0, 0, 0);
            canvas.drawBitmap(mBitmap, srcRect, dstRect, null);
            holder.unlockCanvasAndPost(canvas);
        }
        mSurfaceView.setVisibility(View.VISIBLE);
        updatePhotoInfo();
        PHOTO_SHOWN = true;
        //if have SetURI stored, display the last image pushed by DMR
        setActionRecodeMutex.lock();
        setActionRecodeTemp = setActionRecode;
        SetContentTitle(setActionRecodeTemp,null);
        setActionRecode = null;
        setActionRecodeMutex.unlock();
        if (setActionRecodeTemp != null )
        {
            mController = setActionRecodeTemp.getController();
            if (mController == Controller.DMR && dmrServer == null)
            {
                if (ServiceManager.checkService("dmr") != null)
                {
                    dmrServer = IDMRServer.Stub.asInterface(ServiceManager
                            .getService("dmr"));
                }
            }
            isGif = false;
            cancelSlide();
            initialView();
            filePath = setActionRecodeTemp.getUrl();
            Log.d(TAG, "start play " + filePath);
            playlist.clear();
            playlist.add(filePath);
            PlayList.getinstance().setlist(playlist, 0);
            dmrCurrentState = Constant.DMR_STATE_STOPPED;
            photoPlay();
        }
    }

    /**
     * when zoom in/zoom out image, call this function to show zoomed image
     */

    /**
     * 当放大缩小图片时，调用此函数显示放大缩小后的图片
     */
    private void showChangedImage()
    {
        x = 0;
        y = 0;
        if (mBitmap == null)
        {
            return;
        }
        hideLoadingBar();
        double imagex = (mBitmap.getWidth() * zoomTimes.getValue() * be - mSurfaceView.getWidth()) > 0 ? (mBitmap
                .getWidth() * zoomTimes.getValue() * be - mSurfaceView.getWidth()) / 2
                : 0;
        double imagey = (mBitmap.getHeight() * zoomTimes.getValue() * be - mSurfaceView.getHeight()) > 0 ? (mBitmap
                .getHeight() * zoomTimes.getValue() * be - mSurfaceView.getHeight()) / 2
                : 0;
        Log.d(TAG, "imagex=" + imagex);
        Log.d(TAG, "imagey=" + imagey);
        this.x = (int) imagex;
        this.y = (int) imagey;
        moveView();
        mSurfaceView.setVisibility(View.VISIBLE);
        updatePhotoInfo();
    }

    /**
     * caculate coordinates of image showing rect
     */

    /**
     * 计算图片显示的位置
     */
    private Rect caculateChangedPos()
    {
        double xcoor = 0;
        double ycoor = 0;
        if (mSurfaceView.getWidth() > mBitmap.getWidth())
        {
            xcoor = (mSurfaceView.getWidth() - mBitmap.getWidth()) / 2;
        }
        if (mSurfaceView.getHeight() > mBitmap.getHeight())
        {
            ycoor = (mSurfaceView.getHeight() - mBitmap.getHeight()) / 2;
        }
        int left = (int) xcoor;
        int top = (int) ycoor;
        int right = (int) (mSurfaceView.getWidth() - xcoor);
        int bottom = (int) (mSurfaceView.getHeight() - ycoor);
        Rect rectDst = new Rect(left, top, right, bottom);
        return rectDst;
    }

    private void destroyActivity()
    {
        cancelSlide();
        closeMainActivity(false);
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
            isViewSurfaceCreated = true;
            if (mBitmap != null && !mBitmap.isRecycled())
            {
                Log.d(TAG, "showImage");
                showImage();
            }
        }

        public void surfaceDestroyed(SurfaceHolder holder)
        {
            Log.d(TAG, "surfaceDestroyed");
            isViewSurfaceCreated = false;
        }
    }

    /**
     * call this function to start decoding image
     */

    /**
     * 调用此函数开始解码图片
     */
    protected void photoPlay()
    {
        if (getActivity().isFinishing())
        {
            return;
        }
        hideLoadingBar();
        if (dmrServer != null)
        {
            try
            {
                dmrServer.getDMRCallback().openNotify();
            }
            catch (RemoteException e)
            {
                Log.e(TAG, "openNotify", e);
            }
        }
        showLoadingBar();

        if (loadImageThread != null)
        {
            loadImageThread.interrupt();
            loadImageThread = null;
        }
        loadImageThread = new LoadImageThread();
        loadImageThread.start();
    }

    /**
     * initial some controls for current activity
     */
    /**
     * 初始化一些当前activity的控件
     */
    private void initialView()
    {
        name_tv = (TextView) mParentView.findViewById(R.id.name_textView);
        date_tv = (TextView) mParentView.findViewById(R.id.date_textView);
        backBtn = (ImageButton) mParentView.findViewById(R.id.back_imageButton);
        previousBtn = (ImageButton) mParentView.findViewById(R.id.pre_imageButton);
        nextBtn = (ImageButton) mParentView.findViewById(R.id.next_imageButton);
        antiClockRotateBtn = (ImageButton) mParentView
                .findViewById(R.id.anticlockrotate_imageButton);
        clockRotateBtn = (ImageButton) mParentView.findViewById(R.id.imageButton4);
        RotateListener rotateListner = new RotateListener();
        antiClockRotateBtn.setOnClickListener(rotateListner);
        clockRotateBtn.setOnClickListener(rotateListner);
        zoomBtn = (ImageButton) mParentView.findViewById(R.id.zoomout_imageButton);
        ZoomListener zoomListner = new ZoomListener();
        zoomBtn.setOnClickListener(zoomListner);
        playBtn = (ImageButton) mParentView.findViewById(R.id.play_imageButton);
        playBtn.setOnClickListener(new SlideListener());
        speedText = (TextView) mParentView.findViewById(R.id.speedText);
        switch (slideSpeed)
        {
            case NORMAL:
                speedText.setText(getString(R.string.speed_normal));
                break;
            case FAST:
                speedText.setText(getString(R.string.speed_fast));
                break;
            case SLOW:
                speedText.setText(getString(R.string.speed_slow));
                break;
        }
        speedText.setVisibility(View.VISIBLE);
        slideView = (ImageView) mParentView.findViewById(R.id.imageView3);
        slideSpeedBtn = (ImageButton) mParentView.findViewById(R.id.slide_speed);
        slideSpeedBtn.setOnClickListener(new SlideSpeedListener());
        inforbar_top = (LinearLayout) mParentView.findViewById(R.id.inforbarToplinearLayout);
        inforbar_bottom = (LinearLayout) mParentView.findViewById(R.id.inforbarBottomlinearLayout);

        if (mController == Controller.DMR)
        {
            playBtn.setEnabled(false);
            // playBtn.setBackgroundResource(R.drawable.play_disable);
            slideSpeedBtn.setEnabled(false);
            // slideSpeedBtn.setBackgroundResource(R.drawable.photo_speed_disable);
            previousBtn.setEnabled(false);
            // previousBtn.setBackgroundResource(R.drawable.previous_disable);
            nextBtn.setEnabled(false);
            // nextBtn.setBackgroundResource(R.drawable.next_disable);
            antiClockRotateBtn.setNextFocusLeftId(R.id.back_imageButton);
            backBtn.setNextFocusLeftId(R.id.zoomout_imageButton);
            backBtn.setNextFocusRightId(R.id.anticlockrotate_imageButton);
            zoomBtn.setNextFocusRightId(R.id.back_imageButton);
            antiClockRotateBtn.requestFocus();
        }
        else
            nextBtn.requestFocus();

        backBtn.setOnClickListener(new ImageButton.OnClickListener()
        {
            public void onClick(View v)
            {
                cancelSlide();
                closeMainActivity(false);
            }
        });

        previousBtn.setOnClickListener(new ImageButton.OnClickListener()
        {
            public void onClick(View v)
            {
                Log.d(TAG, "previous photo");
                showPrevious();
            }
        });

        nextBtn.setOnClickListener(new ImageButton.OnClickListener()
        {
            public void onClick(View v)
            {
                Log.d(TAG, "next photo");
                showNext();
            }
        });
    }

    /**
     * play the next image
     */
    /**
     * 播放下一张图片
     */
    private void showNext()
    {
        if (mController == Controller.DMR)
        {
            Toast.makeText(mContext, R.string.dmr_not_allow_next, Toast.LENGTH_SHORT).show();
            return;
        }
        isPlayOrientationNext = true;
        PlayList.getinstance().movenext();
        if (isSlideRunning)
        {
            cancelSlide();
        }
        else
        {
            // isGif = false;
            miniView.setVisibility(View.GONE);
            photoPlay();
        }
    }

    /**
     * play the previous image
     */
    /**
     * 播放上一张图片
     */
    private void showPrevious()
    {
        if (mController == Controller.DMR)
        {
            Toast.makeText(mContext, R.string.dmr_not_allow_pre, Toast.LENGTH_SHORT).show();
            return;
        }
        isPlayOrientationNext = false;
        PlayList.getinstance().moveprev();
        if (isSlideRunning)
        {
            cancelSlide();
        }
        else
        {
            // isGif = false;
            miniView.setVisibility(View.GONE);
            photoPlay();
        }
    }

    /**
     * show the status bar
     */

    /**
     * 显示状态栏
     */
    protected void showView()
    {
        isInfoBarVisible = true;
        inforbar_top.setVisibility(View.VISIBLE);
        inforbar_bottom.setVisibility(View.VISIBLE);
        if (cur_focus_bottom != null)
        {// tianjia@20120419
            if (mController != Controller.DMR)
            {
                cur_focus_bottom.requestFocus();
            }
        }
        else
        {
            if (mController == Controller.DMR)
                antiClockRotateBtn.requestFocus();
            else
                nextBtn.requestFocus();
        }
    }

    Bitmap getBitmap(String url, int filetype)
    {
        if (filetype == Constant.FILE_TYPE_LOCAL_IMAGE)
        {
            Log.d(TAG, "local file: " + url);
            try
            {
                return BitmapFactory.decodeFile(filePath);
            }
            catch (OutOfMemoryError e)
            {
                Log.e(TAG, "decodeFile", e);
            }
            return null;
        }

        URL myFileUrl = null;
        try
        {
            Log.d(TAG, "myFileUrl:" + url);
            myFileUrl = new URL(url);
        }
        catch (MalformedURLException e)
        {
            Log.e(TAG, "new URL", e);
            if (isSlideRunning)
            {
                slideHandler.sendEmptyMessage(SLIDE_FAIL);
            }
            else
            {
                imageLoadHandler.sendEmptyMessage(MESSAGE_LOADFAIL);
            }
            return null;
        }

        try
        {
            String type = "";
            long size = 0;

            if(Controller.DMP == mController)
            {
                long oldTimeMillis = System.currentTimeMillis();
                String headerString = DMPNative.getInstance().HI_DmpGetHead(url);
                if(null != headerString)
                {
                    Pattern pServ = Pattern.compile("content-type: (.+)");
                    Matcher mServ = pServ.matcher((CharSequence) headerString.toLowerCase());
                    if (mServ.find())
                    {
                        type = mServ.group(1);
                        Log.d(TAG, "content-type:" + type);
                    }
                    else
                    {
                        Log.d(TAG, "content-type: not matcher");
                    }

                    pServ = Pattern.compile("content-length: ([0-9]*)");
                    mServ = pServ.matcher((CharSequence) headerString.toLowerCase());
                    if (mServ.find())
                    {
                        size = Long.parseLong(mServ.group(1));
                        Log.d(TAG, "content-length:" + mServ.group(1));
                    }
                    else
                    {
                        Log.d(TAG, "content-length: not matcher");
                    }
                }
                else
                {
                    Log.e(TAG, "headerString is null");
                    if (isSlideRunning)
                    {
                        slideHandler.sendEmptyMessage(SLIDE_FAIL);
                    }
                    else
                    {
                        imageLoadHandler.sendEmptyMessage(MESSAGE_LOADFAIL);
                    }
                    return null;
                }
                long currentTimeMillis = System.currentTimeMillis() - oldTimeMillis;
                Log.d(TAG, "http connect used time:" + currentTimeMillis);
                Log.d(TAG, "type is " + type);
                Log.d(TAG, "length: " + size);

            }
            else
            {
                type = mContentType;
                size = mContentLength;
            }

            if (type == null)
            {
                Log.e(TAG, "type is null");
                size = 1;
            }
            else
            {
                Log.d(TAG, "image --type--" + type);
                if (type.contains(":"))
                {
                    str_photoType = type.split(":")[0];
                }
                else
                {
                    str_photoType = type;
                }
            }
            Log.d(TAG, "--size--" + size);
            if (Controller.DMP == mController)
            {
                if (!dms_files.isEmpty())
                {
                    long newsize = dms_files.get(PlayList.getinstance().getPosition())
                            .getFileSize();
                    Log.d(TAG, "--size from dms--" + newsize);
                    if (newsize > size)
                    {
                        size = (int) newsize;
                    }
                }
                else if (mDMSFile != null && PlayList.getinstance().getLength() == 1)
                {
                    long newsize = mDMSFile.getFileSize();
                    Log.d(TAG, "---size from dms---" + newsize);
                    if (newsize > size)
                    {
                        size = (int) newsize;
                    }
                }
            }
            decodeThread.decode(myFileUrl, mSurfaceView.getWidth(), mSurfaceView.getHeight(),(int)mContentLength);
        }
        catch (Exception e)
        {
            Log.e(TAG, "getBitmap()", e);
            imageLoadHandler.sendEmptyMessage(MESSAGE_FAILED_GET_FILE);
        }
        return null;
    }

    private String getFileSize(int length)
    {
        if (length >= 1073741824)
        {
            DecimalFormat dt = new DecimalFormat("#.###");
            return dt.format((float) length / 1073741824) + "GB";
        }
        else if (length >= 1048576)
        {
            DecimalFormat dt = new DecimalFormat("#.###");
            return dt.format((float) length / 1048576) + "MB";
        }
        else if (length >= 1024)
        {
            DecimalFormat dt = new DecimalFormat("#.###");
            return dt.format((float) length / 1024) + "KB";
        }
        else
        {
            return String.valueOf(length) + "B";
        }
    }

    /**
     * when decoding thread completes the decoding, decoding thread will call this callback function
     * to notify UI thread
     */

    /**
     * 当解码线程结束后，会调用此回调函数通知UI线程
     */
    public void onDecodeFinish(Bitmap bitmap, ImageInfo info, DecodeError error)
    {
        if (isSlideRunning)
        {
            Log.d(TAG, "isSlideRunning");
            if (bitmap == null)
            {
                slideHandler.sendEmptyMessage(SLIDE_FAIL);
                return;
            }
            str_photoResolution = info.getResolution();
            mBitmap = bitmap;
            mBitmapDrawable = new BitmapDrawable(mBitmap);
            mBitmapDrawable.setTargetDensity(mContext.getResources().getDisplayMetrics());
            slideHandler.sendEmptyMessage(SLIDE_FINISH);
            return;
        }
        if (error == DecodeError.NOERROR)
        {
            Log.d(TAG, "decode success: " + bitmap);
            if (bitmap == null)
            {
                imageLoadHandler.sendEmptyMessage(MESSAGE_LOADFAIL);
                return;
            }

            synchronized(ImagePlayerSubWnd.this)
            {
                if (null != mBitmap && !mBitmap.isRecycled())
                {
                    mBitmap.recycle();
                }
                mBitmap = bitmap;
            }
            str_photoResolution = info.getResolution();
            if (!isSlideRunning)
            {
                Message msg = new Message();
                msg.what = MESSAGE_LOADFINISH;
                imageLoadHandler.sendMessage(msg);
            }
        }
        else if (error == DecodeError.OUTOFMEMORY)
        {
            if (!isSlideRunning)
            {
                imageLoadHandler.sendEmptyMessage(MESSAGE_OUTOFMEMORY);
            }
        }
        else if (error == DecodeError.FAILEDTOGETFILE)
        {
            imageLoadHandler.sendEmptyMessage(MESSAGE_FAILED_GET_FILE);
        }
        else
        {
            Log.d(TAG, "decode fail");
            if (!isSlideRunning)
            {
                imageLoadHandler.sendEmptyMessage(MESSAGE_LOADFAIL);
            }
        }
    }

    /**
     * a loading image thread
     */

    /**
     * 加载图片的线程
     */
    class LoadImageThread extends Thread
    {
        public void run()
        {
            if (!PHOTO_SHOWN)
            {
                return;
            }
            // if the surface of view not create,then wait
            int n = 0;
            while ((!isViewSurfaceCreated) && (n < WAITE_CREATE_FINISH_COUNT))
            {
                n++;
                Log.i(TAG, "wiate surface create finish n=" + n);
                SystemClock.sleep(10);
            }
            Log.i(TAG, "surface isViewSurfaceCreated=" + isViewSurfaceCreated
                    + ",mSurfaceView.getWidth()=" + mSurfaceView.getWidth());
            mTimerManager.closeTimer();
            mTimerManager.startTimer(TimerManager.HOME_MENU_TIME_OUT, ImagePlayerSubWnd.this);
            Log.d(TAG, "loading...");
            PHOTO_SHOWN = false;
            warningShowDismiss();
            getBitmap(PlayList.getinstance().getcur(), fileType);
            Log.d(TAG, "load end");
        }
    }


    /**
     * Show a dialog that prompts the unsupported file
     */
    /**
     * 弹出对话框，提示不支持的文件
     */
    private AlertDialog dialogShowUnsupport = null;
    private AlertDialog dialogOutOfMemory = null;
    private AlertDialog dialogConnectTimeout = null;
    private AlertDialog dialogFailedGetFile = null;

    private void warningShowUnsupport()
    {
        try
        {
            Thread.sleep(1000); // tianjia:t00204177 DTS2012101902914
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
        hideLoadingBar();
        cancelSlide();
        dialogShowUnsupport = alertUnsupportDialogBuilder.create();
        if (getActivity() == null)
        {
            Log.e(TAG, "ImagePlayerSubWnd Activity is null");
        }
        else if (getActivity() != null && !getActivity().isFinishing())
        {
            dialogShowUnsupport.show();
        }
        PHOTO_SHOWN = true; // tianjia:t00204177 for show a unsupported file but
                            // can't show next
                            // pushed photo.
    }

    /**
     * Close the dialog that prompts the unsupported file
     */
    /**
     * 关闭提示不支持文件的对话框
     */
    private void warningShowDismiss()
    {
        if (dialogShowUnsupport != null)
        {
            dialogShowUnsupport.dismiss();
        }
        if (dialogOutOfMemory != null)
        {
            dialogOutOfMemory.dismiss();
        }
        if (dialogConnectTimeout != null)
        {
            dialogConnectTimeout.dismiss();
        }
        if (dialogFailedGetFile != null)
        {
            dialogFailedGetFile.dismiss();
        }
    }

    /**
     * Update the image information on the interface
     */
    /**
     * 更新界面上的图片详细信息
     */
    private void updatePhotoInfo()
    {
        Log.d(TAG, "updatePhotoInfo");
        if (mController == Controller.DMP)
        {
            if (!dms_files.isEmpty())
                str_photoName = dms_files.get(PlayList.getinstance().getPosition()).getName();
            else
                str_photoName = mDMSFile.getName();
        }
        else if (mController == Controller.DMR)
        {
            str_photoName = photoName;
        }

        if (str_photoName == null)
            name_tv.setText(R.string.unknown);
        else
            name_tv.setText(str_photoName);

        if (str_photoResolution == null)
            date_tv.setText(R.string.unknown);
        else
            date_tv.setText(str_photoResolution);

        // 非幻灯片模式下，gif图片需要disable三个button
        if (!isSlideRunning)
        {
            // if (isGif) {
            // antiClockRotateBtn.setEnabled(false);
            // clockRotateBtn.setEnabled(false);
            // zoomBtn.setEnabled(false);
            // if (mController == Controller.DMR) {
            // backBtn.setNextFocusRightId(R.id.back_imageButton);
            // backBtn.setNextFocusLeftId(R.id.back_imageButton);
            // backBtn.requestFocus();
            // } else {
            // slideSpeedBtn.setNextFocusRightId(R.id.back_imageButton);
            // backBtn.setNextFocusLeftId(R.id.slide_speed);
            // }
            // } else {
            antiClockRotateBtn.setEnabled(true);
            clockRotateBtn.setEnabled(true);
            zoomBtn.setEnabled(true);
            slideSpeedBtn.setNextFocusRightId(R.id.anticlockrotate_imageButton);
            backBtn.setNextFocusLeftId(R.id.zoomout_imageButton);
            // }
        }
    }

    enum RotateAngle
    {
        ANGLE0(0),
        ANGLE90(90),
        ANGLE180(180),
        ANGLE270(270);
        private int value;

        private RotateAngle(int value)
        {
            this.value = value;
        }

        public int getValue()
        {
            return value;
        }

        public RotateAngle pre()
        {
            if (this == ANGLE0)
            {
                return ANGLE270;
            }
            else if (this == ANGLE90)
            {
                return ANGLE0;
            }
            else if (this == ANGLE180)
            {
                return ANGLE90;
            }
            else if (this == ANGLE270)
            {
                return ANGLE180;
            }
            else
            {
                return ANGLE0;
            }
        }

        public RotateAngle next()
        {
            if (this == ANGLE0)
            {
                return ANGLE90;
            }
            else if (this == ANGLE90)
            {
                return ANGLE180;
            }
            else if (this == ANGLE180)
            {
                return ANGLE270;
            }
            else if (this == ANGLE270)
            {
                return ANGLE0;
            }
            else
            {
                return ANGLE0;
            }
        }
    }

    enum ZoomTimes
    {
        ORIGIN(1),
        OneAndAHalf(1.5),
        TWICE(2);
        private double value;

        private ZoomTimes(double value)
        {
            this.value = value;
        }

        public double getValue()
        {
            return value;
        }

        public ZoomTimes next()
        {
            if (this == ORIGIN)
            {
                return OneAndAHalf;
            }
            else if (this == OneAndAHalf)
            {
                return TWICE;
            }
            else if (this == TWICE)
            {
                return ORIGIN;
            }
            else
            {
                return ORIGIN;
            }
        }
    }

    enum SlideSpeed
    {
        SLOW(10000),
        NORMAL(5000),
        FAST(3000);
        private long value;

        private SlideSpeed(long value)
        {
            this.value = value;
        }

        public long getValue()
        {
            return value;
        }

        public SlideSpeed next()
        {
            SlideSpeed speed = NORMAL;
            switch (this)
            {
                case SLOW:
                    speed = NORMAL;
                    break;
                case NORMAL:
                    speed = FAST;
                    break;
                case FAST:
                    speed = SLOW;
            }
            return speed;
        }
    }

    class RotateListener implements ImageButton.OnClickListener
    {
        public void onClick(View v)
        {
            cancelSlide();
            if (mBitmap == null)
            {
                return;
            }
            miniView.setVisibility(View.GONE);
            if (v.getId() == antiClockRotateBtn.getId())
            {
                Log.d(TAG, "anticlock");
                // rotateAngle = rotateAngle.next();
                rotateAngle = RotateAngle.ANGLE270;
            }
            else if (v.getId() == clockRotateBtn.getId())
            {
                Log.d(TAG, "clock");
                rotateAngle = RotateAngle.ANGLE90;
            }
            else
            {
                Log.e(TAG, "wrong rotate button");
                return;
            }
            Matrix matrix = new Matrix();
            matrix.setRotate(rotateAngle.getValue());
            // mBitmap = Bitmap.createBitmap(mBitmap, 0, 0, mBitmap.getWidth(),
            // mBitmap.getHeight(), matrix, true);
            Bitmap bitmap = null;
            synchronized(ImagePlayerSubWnd.this)
            {
                try
                {
                    bitmap = Bitmap.createBitmap(mBitmap, 0, 0, mBitmap.getWidth(),
                            mBitmap.getHeight(), matrix, true);
                }
                catch (OutOfMemoryError e)
                {
                    Log.e(TAG, "createBitmap", e);
                    imageLoadHandler.sendEmptyMessage(MESSAGE_OUTOFMEMORY);
                    return;
                }
                if (mBitmap != null && !mBitmap.isRecycled())
                {
                    mBitmap.recycle();
                    mBitmap = null;
                }
                mBitmap = bitmap;
            }
            originSize = caculateChangedPos();
            // imageLoadHandler.sendEmptyMessage(MESSAGE_LOADCHANGEIMAGE);
            zoomTimes = ZoomTimes.ORIGIN;
            imageLoadHandler.sendEmptyMessage(MESSAGE_LOADFINISH);
        }
    }

    class ZoomListener implements ImageButton.OnClickListener
    {
        public void onClick(View v)
        {
            if (v.getId() == zoomBtn.getId())
            {
                cancelSlide();
                miniView.setVisibility(View.VISIBLE);
                zoomTimes = zoomTimes.next();
            }
            else
            {
                return;
            }
            if (zoomTimes == ZoomTimes.ORIGIN)
            {
                x = 0;
                y = 0;
                miniView.setVisibility(View.GONE);
            }
            if (mBitmap != null)
            {
                imageLoadHandler.sendEmptyMessage(MESSAGE_LOADCHANGEIMAGE);
            }
            else
            {
                Log.e(TAG,"mBitmap is null,so cant to zoom in/zoom out image");
            }
        }
    }

    private void moveView()
    {
        double zoomValue = zoomTimes.getValue() * be;
        double xcoor = 0;
        double ycoor = 0;
        if (mSurfaceView.getWidth() > mBitmap.getWidth() * zoomValue)
        {
            xcoor = (mSurfaceView.getWidth() - mBitmap.getWidth() * zoomValue) / 2;
        }
        if (mSurfaceView.getHeight() > mBitmap.getHeight() * zoomValue)
        {
            ycoor = (mSurfaceView.getHeight() - mBitmap.getHeight() * zoomValue) / 2;
        }

        double srcRightCoor = (x + mSurfaceView.getWidth()) / zoomValue;
        if (srcRightCoor > mBitmap.getWidth())
        {
            srcRightCoor = mBitmap.getWidth();
        }

        double srcBottomCoor = (y + mSurfaceView.getHeight()) / zoomValue;
        if (srcBottomCoor > mBitmap.getHeight())
        {
            srcBottomCoor = mBitmap.getHeight();
        }

        int left = (int) (x / zoomValue);
        int top = (int) (y / zoomValue);
        int right = (int) srcRightCoor;
        int bottom = (int) srcBottomCoor;
        Rect rectSrc = new Rect(left, top, right, bottom);

        left = (int) xcoor;
        top = (int) ycoor;
        right = (int) (mSurfaceView.getWidth() - xcoor);
        bottom = (int) (mSurfaceView.getHeight() - ycoor);
        Rect rectDst = new Rect(left, top, right, bottom);
        Canvas canvas = mSurfaceView.getHolder().lockCanvas();
        if (canvas != null)
        {
            canvas.setDrawFilter(paintFilter);
            canvas.drawARGB(255, 0, 0, 0);
            canvas.drawBitmap(mBitmap, rectSrc, rectDst, null);
            mSurfaceView.getHolder().unlockCanvasAndPost(canvas);
        }
        if (miniView.getVisibility() == View.VISIBLE)
        {
            Log.d(TAG, "miniView");
            miniRatioX = miniView.getWidth() * 1.0f / mSurfaceView.getWidth();
            miniRatioY = miniView.getHeight() * 1.0f / mSurfaceView.getHeight();

            int miniLeft = (int) (originSize.left * miniRatioX);
            int miniTop = (int) (originSize.top * miniRatioY);
            int miniRight = (int) (originSize.right * miniRatioX);
            int miniBottom = (int) (originSize.bottom * miniRatioY);
            Rect miniSrcRect = new Rect(0, 0, mBitmap.getWidth(), mBitmap.getHeight());
            Rect miniDstRect = new Rect(miniLeft, miniTop, miniRight, miniBottom);
            Paint selectRectPaint = new Paint();
            selectRectPaint.setColor(Color.WHITE);
            selectRectPaint.setStyle(Style.STROKE);
            selectRectPaint.setStrokeWidth(4);

            int selectLeft = (int) (miniLeft - rectDst.left * miniRatioX);
            // 表示图像左边超过边界,则<br>
            if (rectSrc.left != 0)
            {
                selectLeft = (int) (miniLeft + rectSrc.left * miniRatioX * be);
            }

            int selectRight = (int) (miniRight + (mSurfaceView.getWidth() - rectDst.right) * miniRatioX);
            if (rectSrc.right != mBitmap.getWidth())
            {
                selectRight = (int) (miniLeft + rectSrc.right * miniRatioX * be);
            }

            int selectTop = (int) (miniTop + rectSrc.top * miniRatioY * be);
            if (rectSrc.top == 0)
            {
                Log.d(TAG, "top=0");
                selectTop = (int) (miniTop - rectDst.top * miniRatioY);
            }

            int selectBottom = (int) (miniTop + rectSrc.bottom * miniRatioY * be);
            if (rectSrc.bottom == mBitmap.getHeight())
            {
                Log.d(TAG, "bottom=0");
                selectBottom = (int) (miniBottom + (mSurfaceView.getHeight() - rectDst.bottom)
                        * miniRatioY);
            }

            RectF selectRect = new RectF(selectLeft, selectTop, selectRight, selectBottom);
            Canvas miniCanvas = miniView.getHolder().lockCanvas();
            if (miniCanvas != null)
            {
                miniCanvas.setDrawFilter(paintFilter);
                miniCanvas.drawColor(Color.TRANSPARENT, Mode.CLEAR);
                miniCanvas.drawARGB(100, 255, 255, 255);
                miniCanvas.drawBitmap(mBitmap, miniSrcRect, miniDstRect, null);
                miniCanvas.drawRect(selectRect, selectRectPaint);
                miniView.getHolder().unlockCanvasAndPost(miniCanvas);
            }
        }
    }

    class SlideListener implements ImageView.OnClickListener
    {
        public void onClick(View v)
        {
            if (isSlideRunning)
            {
                cancelSlide();
            }
            else
            {
                restartSlide();
            }
        }
    }

    private Handler slideHandler = new Handler()
    {
        public void handleMessage(Message msg)
        {
            imageSwitcher.setVisibility(View.VISIBLE);
            mSurfaceView.setVisibility(View.GONE);
            miniView.setVisibility(View.GONE);
            slideTimer.schedule(new SlideTask(), slideSpeed.getValue());
            switch (msg.what)
            {
                case SLIDE_FINISH:
                    imageSwitcher.setImageDrawable(mBitmapDrawable);
                    updatePhotoInfo();
                    break;
                case SLIDE_FAIL:
                    Toast.makeText(mContext, getString(R.string.imageIsNull), Toast.LENGTH_SHORT)
                            .show();
                    break;
            }
        }
    };

    class SlideTask extends TimerTask
    {
        public void run()
        {
            if (!(mLoadingView.getVisibility() == View.VISIBLE))
            {
                // isGif = false;
                PlayList.getinstance().movenext();
                getBitmap(PlayList.getinstance().getcur(), fileType);
            }
        }
    }

    private void setRotateZoomEnable(boolean isEnable)
    {
        if (isEnable)
        {
            antiClockRotateBtn.setEnabled(true);
            clockRotateBtn.setEnabled(true);
            zoomBtn.setEnabled(true);
            antiClockRotateBtn.setBackgroundResource(R.drawable.anticlockwise_btn_src);
            clockRotateBtn.setBackgroundResource(R.drawable.clockwise_btn_src);
            zoomBtn.setBackgroundResource(R.drawable.zoomout_btn_src);
        }
        else
        {
            antiClockRotateBtn.setEnabled(false);
            clockRotateBtn.setEnabled(false);
            zoomBtn.setEnabled(false);
            antiClockRotateBtn.setBackgroundResource(R.drawable.photo_anticlockwise_disable);
            clockRotateBtn.setBackgroundResource(R.drawable.photo_clockwise_disable);
            zoomBtn.setBackgroundResource(R.drawable.photo_zoomout_disable);
        }
    }

    /**
     * start slide playing
     */

    /**
     * 开启幻灯片播放
     */
    private void restartSlide()
    {
        if (Controller.DMR == mController)
        {
            return;
        }
        if (slideTimer != null)
        {
            slideTimer.cancel();
        }
        hideLoadingBar();
        imageSwitcher.reset();
        isSlideRunning = true;
        setBlack4IVSlide();
        imageFactory.destroyDrawingCache();
        slideTimer = new Timer();
        slideTimer.schedule(new SlideTask(), slideSpeed.getValue());
        setRotateZoomEnable(false);
        playBtn.setBackgroundResource(R.drawable.pause_button);
        slideView.setBackgroundResource(R.drawable.play_unfocus);
        slideView.setVisibility(View.VISIBLE);
        speedText.setVisibility(View.VISIBLE);
        slideSpeedBtn.setNextFocusRightId(R.id.back_imageButton);// tianjia@20120419
        backBtn.setNextFocusLeftId(R.id.slide_speed);// tianjia@20120419
    }

    /**
     * cancel slide playing
     */

    /**
     * 结束幻灯片播放
     */
    private void cancelSlide()
    {
        // if(Controller.DMR == mController)
        // return;

        if (slideTimer != null)
        {
            slideTimer.cancel();
        }
        isSlideRunning = false;
        slideTimer = null;
        setRotateZoomEnable(true);
        playBtn.setBackgroundResource(R.drawable.play_button);
        slideView.setBackgroundResource(R.drawable.pause_unfocus);
        slideView.setVisibility(View.VISIBLE);
        // imageSwitcher.setVisibility(View.GONE);
        imageSwitcher.setVisibility(View.GONE);
        mSurfaceView.setVisibility(View.VISIBLE);
        slideSpeedBtn.setNextFocusRightId(R.id.anticlockrotate_imageButton);// tianjia@20120419
        backBtn.setNextFocusLeftId(R.id.zoomout_imageButton);// tianjia@20120419
    }

    class MiniSurfaceCallback implements SurfaceHolder.Callback
    {
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
        {
            Log.d(TAG, "mini surfaceChanged");
        }

        public void surfaceCreated(SurfaceHolder holder)
        {
            Log.d(TAG, "mini surfaceCreate");
            if (mBitmap != null && !mBitmap.isRecycled())
            {
                showChangedImage();
            }
            else
            {
                // } else if (mBitmap != null && !isGif) {
                showImage();
            }
        }

        public void surfaceDestroyed(SurfaceHolder holder)
        {
            Log.d(TAG, "mini surfaceDestroyed");
        }

    }

    class ImageFactory implements ViewSwitcher.ViewFactory
    {
        private ImageView imageView;

        public View makeView()
        {
            imageView = new ImageView(mContext);
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
            imageView.setLayoutParams(new ImageSwitcher.LayoutParams(LayoutParams.FILL_PARENT,
                    LayoutParams.FILL_PARENT));
            return imageView;
        }

        public void destroyDrawingCache()
        {
            imageView.destroyDrawingCache();
        }

        public void setImageDrawable(Drawable drawable)
        {
            imageView.setImageDrawable(drawable);
        }
    }

    class SlideSpeedListener implements ImageView.OnClickListener
    {
        public void onClick(View v)
        {
            slideSpeed = slideSpeed.next();
            switch (slideSpeed)
            {
                case NORMAL:
                    speedText.setText(getString(R.string.speed_normal));
                    break;
                case FAST:
                    speedText.setText(getString(R.string.speed_fast));
                    break;
                case SLOW:
                    speedText.setText(getString(R.string.speed_slow));
                    break;
            }
            if (isSlideRunning)
            {
                cancelSlide();
                restartSlide();
            }
        }
    }

    /**
     * Hide the infobar and menubar
     */
    /**
     * 用于隐藏信息栏和控制栏
     */
    public void hideView()
    {
        isInfoBarVisible = false;
        cur_focus_bottom = inforbar_bottom.findFocus();// tianjia@20120419
        if (inforbar_top.getVisibility() == View.VISIBLE)
        {
            inforbar_top.setVisibility(View.GONE);
            inforbar_bottom.setVisibility(View.GONE);
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
            case 111: // KeyEvent.KEYCODE_ESCAPE
                isValidKey = true;
                break;
        }
        if (!isValidKey)
        {
            return KeyDoResult.DO_OVER;
        }
        if (inforbar_top.getVisibility() == RelativeLayout.VISIBLE)
        {
            mTimerManager.resetTimer(TimerManager.HOME_MENU_TIME_OUT);
        }
        else if (event.getAction() == KeyEvent.ACTION_UP)
        {
            int kc = event.getKeyCode();
            if (ZoomTimes.ORIGIN != zoomTimes && kc != KeyEvent.KEYCODE_DPAD_CENTER
                    && kc != KeyEvent.KEYCODE_PAGE_DOWN && kc != KeyEvent.KEYCODE_PAGE_UP)
                return KeyDoResult.DO_NOTHING;
            // 快捷键－－上下切换，播放暂停，不显示菜单栏
            if (kc != KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE && kc != KeyEvent.KEYCODE_PAGE_DOWN
                    && kc != KeyEvent.KEYCODE_PAGE_UP && kc != KeyEvent.KEYCODE_BACK
                    && kc != KeyEvent.KEYCODE_DPAD_LEFT && kc != KeyEvent.KEYCODE_DPAD_RIGHT
                    && kc != 111) // KeyEvent.KEYCODE_ESCAPE
            {
                if(isInfoBarVisible)
                {
                    showView();
                    mTimerManager.startTimer(TimerManager.HOME_MENU_TIME_OUT, this);
                }
                else
                {
                    showView();
                    mTimerManager.startTimer(TimerManager.HOME_MENU_TIME_OUT, this);
                    return KeyDoResult.DO_OVER;
                }
            }
        }

        return KeyDoResult.DO_NOTHING;
    }

    /*
     * 幻灯片重新播放时，需要先把ImageView设黑，否则 显示的是当初暂停时残留的图片。
     */
    private void setBlack4IVSlide()
    {
        ColorDrawable cd = new ColorDrawable(0xff000000);
        imageFactory.setImageDrawable(cd);
    }

    class MouseClickListener implements View.OnClickListener
    {
        public void onClick(View v)
        {
            Log.d(TAG, "onClick");
            showView();
            mTimerManager.startTimer(TimerManager.HOME_MENU_TIME_OUT, ImagePlayerSubWnd.this);
        }
    }

    /**
     * 初始化一系列的alertDialog
     */
    private void initAlertDialog()
    {
        alertUnsupportDialogBuilder = new AlertDialog.Builder(mContext).setTitle(R.string.error).setMessage(
                R.string.unsupport_file);
        alertUnsupportDialogBuilder.setPositiveButton(R.string.ok, new DialogInterface.OnClickListener()
        {
            public void onClick(DialogInterface dialog, int whichButton)
            {
                handleClickAlertWindow();
            }
        });
        alertUnsupportDialogBuilder.setOnCancelListener(new DialogInterface.OnCancelListener()
        {
            public void onCancel(DialogInterface dialogInterface)
            {
                destroyActivity();
            }
        });

        alertOutOfMemoryDialogBuilder = new AlertDialog.Builder(mContext).setTitle(R.string.error)
                .setMessage(R.string.outofmemory);
        alertOutOfMemoryDialogBuilder.setPositiveButton(R.string.ok,
                new DialogInterface.OnClickListener()
                {
                    public void onClick(DialogInterface dialog, int whichButton)
                    {
                        handleClickAlertWindow();
                    }
                });
        alertOutOfMemoryDialogBuilder.setOnCancelListener(new DialogInterface.OnCancelListener()
        {
            public void onCancel(DialogInterface dialogInterface)
            {
                destroyActivity();
            }
        });

        alertConnectTimeoutDialogBuilder = new AlertDialog.Builder(mContext).setTitle(
                R.string.error).setMessage(R.string.connect_timeout);
        alertConnectTimeoutDialogBuilder.setPositiveButton(R.string.ok,
                new DialogInterface.OnClickListener()
                {
                    public void onClick(DialogInterface dialog, int whichButton)
                    {
                        connectTimeoutClickAlertWindow();
                    }
                });
        alertConnectTimeoutDialogBuilder.setOnCancelListener(new DialogInterface.OnCancelListener()
        {
            public void onCancel(DialogInterface dialogInterface)
            {
                destroyActivity();
            }
        });

        alertFailedGetFileDialogBuilder = new AlertDialog.Builder(mContext)
                .setTitle(R.string.error).setMessage(R.string.failed_get_file);
        alertFailedGetFileDialogBuilder.setPositiveButton(R.string.ok,
                new DialogInterface.OnClickListener()
                {
                    public void onClick(DialogInterface dialog, int whichButton)
                    {
                        handleClickAlertWindow();
                        // connectTimeoutClickAlertWindow();
                    }
                });
        alertFailedGetFileDialogBuilder.setOnCancelListener(new DialogInterface.OnCancelListener()
        {
            public void onCancel(DialogInterface dialogInterface)
            {
                destroyActivity();
            }
        });

    }

    private void handleClickAlertWindow()
    {

        if (isSlideRunning)
        {
            slideHandler.sendEmptyMessage(SLIDE_FAIL);
            return;
        }
        if (PlayList.getinstance().getLength() > 1)
        {
            if (isPlayOrientationNext)
            {
                PlayList.getinstance().movenext();
            }
            else
            {
                PlayList.getinstance().moveprev();
            }
            PHOTO_SHOWN = true;
            photoPlay();
        }
        else
            destroyActivity();
    }

    private void connectTimeoutClickAlertWindow()
    {
        if (isSlideRunning)
        {
            slideHandler.sendEmptyMessage(SLIDE_FAIL);
            return;
        }
        hideLoadingBar();
        cancelSlide();
        handleClickAlertWindow();
       // PHOTO_SHOWN = true;
    }

    class UpdatePlayListEventCallback implements FetchPlayListThread.EventCallback
    {

        public void fileAddedNotify(DMSFile file)
        {
            Log.d(TAG, "and file =" + file.getUrl());
        }

        public void deviceNotFountNotify()
        {
            imageLoadHandler.sendEmptyMessage(MESSAGE_SHOW_TOAST_GET_PLAYLIST_FAIL);
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

    public void setBaseAction(BaseAction actionClass)
    {
        warningShowDismiss();
        if (mLoadingView.getVisibility() == View.VISIBLE)
        {
            Log.e(TAG, "image is loading, ignore show this photo");
            if (actionClass instanceof PlayAction)
            {
                PlayAction action = (PlayAction) actionClass;
                if (mController == action.getController())
                {
                    if (PlayList.getinstance().getcur().equals(action.getUrl()))
                    {
                        dmrCurrentState = Constant.DMR_STATE_PLAYING;
                        if (mController == Controller.DMR)
                        {
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
                        Log.e(TAG, "set dmrCurrentState=" + dmrCurrentState);
                    }
                }
            }
            //push picture caused DMR blocked, need call openNotify
            if (actionClass instanceof SetURLAction)
            {
                Log.d(TAG, "image is loading, openNotify");
                if (mController == Controller.DMR)
                {
                    if (dmrServer != null)
                    {
                        try
                        {
                            setActionRecodeMutex.lock();
                            setActionRecode = (SetURLAction)actionClass;
                            setActionRecodeMutex.unlock();
                            dmrServer.getDMRCallback().openNotify();
                        }
                        catch (RemoteException e)
                        {
                            Log.e(TAG, "playNotify", e);
                        }
                    }
                }
            }
            return;
        }
        dmrServer = null;
        if (fetchPlayListThread != null && fetchPlayListThread.isAlive())
        {
            fetchPlayListThread.interruptThread();
            fetchPlayListThread.registerEventCallback(null);
            fetchPlayListThread.interrupt();
        }
        fetchPlayListThread = null;
        if (mController == Controller.DMR)
        {
            dmrCurrentState = Constant.DMR_STATE_STOPPED;
            stopNotify();
        }

        if (actionClass instanceof SetURLAction)
        {
            sa = (SetURLAction) actionClass;
            pa = null;
            mController = sa.getController();
            dmrCurrentState = Constant.DMR_STATE_STOPPED;
            setActionRecodeMutex.lock();
            setActionRecode = null;
            setActionRecodeMutex.unlock();
            Log.d(TAG, "dmrCurrentState = Constant.DMR_STATE_STOPPED");
        }else if (actionClass instanceof PlayAction)
        {
            pa = (PlayAction) actionClass;
            sa = null;
            mController = pa.getController();
            dmrCurrentState = Constant.DMR_STATE_PLAYING;
            Log.d(TAG, "dmrCurrentState = Constant.DMR_STATE_PLAYING");
        }
        Log.d(TAG, "controller: " + mController);
        if (mController == Controller.DMR)
        {
            if (isSlideRunning)
            {
                cancelSlide();
            }
            initialView();
            if (ServiceManager.checkService("dmr") == null)
            {
                Toast.makeText(mContext, "dmr binder is not in ServiceManager", 3);
                cancelSlide();
                closeMainActivity(false);
            }
            else
            {
                dmrServer = IDMRServer.Stub.asInterface(ServiceManager.getService("dmr"));
            }
            if (pa != null)
            {
                filePath = pa.getUrl();
            }
            else
            {
                filePath = sa.getUrl();
            }
            SetContentTitle(sa,pa);
            playlist.clear();
            playlist.add(filePath);
            PlayList.getinstance().setlist(playlist, 0);
        }
        else if (mController == Controller.DMP)
        {
            playlist.clear();
            if (null != pa)
            {
                mDMSFile = (DMSFile) pa.getFile();
                filePath = mDMSFile.getUrl();
                playlist.add(filePath);
                PlayList.getinstance().setlist(playlist, 0);
                fetchPlayListThread = new FetchPlayListThread(mContext,mDMSFile, FileType.IMAGE, playlist,
                        dms_files);
                fetchPlayListThread.registerEventCallback(new UpdatePlayListEventCallback());
                fetchPlayListThread.start();
            }
            else
            {
                Log.e(TAG, "pa == null;DMP");
                return;
            }
        }
        else if (mController == Controller.LOCAL)
        {
            playlist.clear();
            if (null != pa)
            {
                LocalFile localFile = (LocalFile) pa.getFile();
                filePath = localFile.getFile().getAbsolutePath();
                playlist.add(filePath);
                PlayList.getinstance().setlist(playlist, 0);
            }
            else
            {
                Log.e(TAG, "pa == null,LOCAL");
                return;
            }
        }
        fileType = Constant.FILE_TYPE_IMAGE_BY_DMC;

        imageSwitcher.setVisibility(View.GONE);
        photoPlay();
    }

    class DMRPlayerController extends IDMRPlayerController.Stub
    {
        public int dmcPlayAction(String mURL)
        {
            Log.d(TAG, "playAction");
            filePath = mURL;
            if (null != mIPlayerMainWnd)
            {
                mIPlayerMainWnd.cancelDelayCloseActivity();//slove play - stop - play,the activity is going to destory,play failed
            }
            if (mController == Controller.DMR)
            {
                if(CommonDef.isSupportCertification())
                {
                    playlist.clear();
                    playlist.add(filePath);
                    PlayList.getinstance().setlist(playlist, 0);
                    if (dmrCurrentState == Constant.DMR_STATE_PAUSED_PLAYBACK)
                         return 0;
                    else if (dmrCurrentState == Constant.DMR_STATE_STOPPED ||
                        dmrCurrentState == Constant.DMR_STATE_PLAYING)
                    {
                        photoPlay();
                    }
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
            dmrCurrentState = Constant.DMR_STATE_PLAYING;
            Log.d(TAG, "ev_play_playing:" + filePath);
            return 0;
        }

        public int dmcPauseAction()
        {
            Log.d(TAG, "pauseAction");
            dmrCurrentState = Constant.DMR_STATE_PAUSED_PLAYBACK;
            return 0;
        }

        public int dmcStopAction()
        {
             Log.d(TAG, "stopAction");
             dmrCurrentState = Constant.DMR_STATE_STOPPED;
             stopNotify();
             closeMainActivity(true);
             return 0;
        }

        public int dmcSeekAction(int mode, int type , String data , String mURL)
        {
            Log.d(TAG, "seek action");
            return 0;
        }

        public int getDuration()
        {
            // int duration = 0;
            // if (mediaPlayer != null) {
            // duration = mediaPlayer.getDuration();
            // }
            return 0;
        }

        public int getCurrentPosition()
        {
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

    private void closeMainActivity(boolean isDelay)
    {
        if (null != mIPlayerMainWnd)
        {
            mIPlayerMainWnd.closeActivity(isDelay);
        }
    }

    public void setContentType(String ContentType)
    {
        mContentType = ContentType;
    }

    public void setContentLength(long length)
    {
        mContentLength = length;
    }

    public void SetContentTitle(SetURLAction Sa, PlayAction Pa)
    {
        if (Pa != null && null != Pa.getFileInfo())
        {
            photoName = pa.getFileInfo().getTitle();
        }
        else if (Sa != null && null != Sa.getFileInfo())
        {
            photoName = Sa.getFileInfo().getTitle();
        }
        else
        {
            photoName = "Unknown";
        }
    }
}
