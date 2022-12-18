package com.hisilicon.dlna.mediacenter;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.IOException;
import java.io.InputStream;
import java.io.BufferedInputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.HttpURLConnection;
import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.URL;
import java.text.DecimalFormat;
import android.content.BroadcastReceiver;
import com.hisilicon.dlna.file.AbstractFile;
import com.hisilicon.dlna.file.DMSDevice;
import com.hisilicon.dlna.file.DMSFile;
import com.hisilicon.dlna.file.FileType;
import com.hisilicon.dlna.file.util.MediaInfo;
import com.hisilicon.dlna.mediacenter.listener.NotifyType;
import com.hisilicon.dlna.mediacenter.listener.UpdateCompleteListener;
import com.hisilicon.dlna.listview.ListViewWithKeyEvent;
import com.hisilicon.dlna.listview.ListViewKeyListener;
import com.hisilicon.dlna.dmr.Constant;
import com.hisilicon.dlna.dmp.DMPManager;
import com.hisilicon.dlna.dmp.DMPNative;
import com.hisilicon.dlna.dmr.action.BaseAction;
import com.hisilicon.dlna.dmr.action.PlayAction;
import com.hisilicon.dlna.dmr.action.Controller;
import com.hisilicon.dlna.util.CommonDef;
import com.hisilicon.dlna.util.imagedecode.*;
import com.hisilicon.dlna.util.mediaplayer.MediaPlayerTemplate;
import com.hisilicon.android.mediaplayer.HiMediaPlayer;
import com.hisilicon.android.mediaplayer.HiMediaPlayerInvoke;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.graphics.Paint;
import android.graphics.PaintFlagsDrawFilter;
import android.graphics.PorterDuff.Mode;
import android.graphics.Rect;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnPreparedListener;
import android.media.MediaPlayer.OnInfoListener;
import android.media.AudioManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Message;
import android.os.Handler;
import android.os.Parcel;
import android.os.SystemClock;
import android.util.Log;
import android.view.KeyEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewTreeObserver.OnScrollChangedListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AbsListView;
import android.widget.AbsListView.OnScrollListener;
import android.widget.AdapterView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Toast;

/**
 * The main class of HiMediaCenter, cantains UI and handling of user interaction events
 * @author c00190074
 */

/**
 * HiMediaCenter的主类，负责界面的显示及用户交互事件的处理
 * @author c00190074
 */
public class MediaCenterActivity extends Activity implements UpdateCompleteListener
{
    private static final String TAG = "MediaCenterActivity";
    private static final int MAX_PIC_SIZE = 30 * 1024 * 1024;
    private static final int DEF_TEXTSIZE = 20;
    private static final int TIMEOUT = 10000;
    private FileExplore fileExplore;
    private ListViewWithKeyEvent listView;
    private SurfaceView surfaceView;
    private SurfaceView videoView;
    private int videoSurfaceFlag = 0; // 0:Created 1:Destroyed
    private DMPManager dmpManager;
    private DMPNative dmpNative;
    private Thread startDMPThread = null ;
    private TextView indexView;
    private ProgressBar loadIcon;
    private ProgressBar ProgressBarVideoPrepare;
    private Bitmap mBitmap;
    private MediaPlayerTemplate mediaPlayer;
    private Thread loadDevicePageThread;
    private Thread loadImageThread;
    private LoadVideoThread loadVideoThread;
    private Thread loadAudioThread;
    private Thread progressThread;
    private Thread updateNextPageThread;
    private Thread updateFileListThread;
    private Thread updateTopFileListThread;
    private int[] index = { 0, 0 };
    private TextView infoView;
    private String fileName;
    private String imageInfo;
    private String videoInfo;
    private String audioInfo;
    private ProgressBar videoBar;
    private TextView curTime;
    private TextView allTime;
    private TextView deviceNameView;
    private TextView pathView;
    private TextView fileNameView;
    private ImageView unSupportImageView;
    private TextView unSupportTextView;
    private TextView textView_videoPrepare;
    private TextView mTextVie_NetWork_Speed;
    private Bitmap albumPic;
    private Bitmap musicPic;
    private Bitmap mainPic;
    private Bitmap upnpPic = null;
    private Bitmap networkPic;
    private Bitmap nfsPic;
    private Bitmap localPic;
    private Bitmap unsupportedWindowImage;
    private Bitmap windowServerPic;
    private RootItem rootItem;
    private long loadId;
    private boolean canLoadTopList;
    private boolean topLoadFinish;
    private boolean loadNextPageFinish;
    private int listPos;
    private int selectDevicePos;
    private DisplayingImage displayingImage;
    private Timer timer;
    private long fileSize;
    private boolean isErrorHappen;
    private int sumIntTime;
    private PaintFlagsDrawFilter paintFilter = new PaintFlagsDrawFilter(0, Paint.ANTI_ALIAS_FLAG
            | Paint.FILTER_BITMAP_FLAG);
    private boolean isUnsupportShow = false;
    private boolean interruptVideoUnsupportShow = true;
    // FIXME isVideoClicked used to check if user clicked a video
    private boolean isVideoClicked = false;
    private Location mCurrentLocation = Location.ROOT;
    private NetworkReceiver mNetworkReceiver = new NetworkReceiver();
    private Timer networkTimer;
    private Timer mNetWorkSpeedTimer;
    private Context mContext;
    private DecodeMethod mDecodeMethod = null;

    /**
     * use this enum to choose which image to show when the activity is brought to foreground from
     * backgroud
     * @see SurfaceCallback#surfaceCreated
     */

    /**
     * 用于界面从后台转到前台时，SurfaceView要显示什么
     * @see SurfaceCallback#surfaceCreated()
     */
    enum DisplayingImage
    {
        ROOT,
        DEVICE,
        MUSIC,
        VIDEO,
        IMAGE,
        FOLDER
    }

    /**
     * update album image, when not exists, show the default image
     */

    /**
     * 更新专辑图片的Handler，如果没有，则显示默认图片
     */
    private Handler updateAlbumImageHandler = new Handler()
    {
        public void handleMessage(Message msg)
        {
            Log.d(TAG, "albumImage: " + msg.obj);
            albumPic = (Bitmap) msg.obj;
            if (msg.obj == null)
            {
                showImage(musicPic);
            }
            else
            {
                showImage((Bitmap) msg.obj);
            }
        }
    };

    /**
     * update UI components(SurfaceView, ListView)
     */

    /**
     * 更新各UI组件(SurfaceView, ListView)
     */
    private Handler updateHandler = new Handler()
    {
        public void handleMessage(Message msg)
        {
            switch ((NotifyType) msg.obj)
            {
                case DEVICE:
                    updateDevicePage();
                    mCurrentLocation = fileExplore.getLocation();
                    pathView.setText(getString(R.string.sourcePath));
                    break;
                case FILE:
                    updateFileList();
                    updatePathView();
                    mCurrentLocation = fileExplore.getLocation();
                    break;
                case NULL:
                    interruptAllThread();
                    if (timer != null)
                    {
                        timer.cancel();
                        timer = null;
                    }
                    Toast.makeText(MediaCenterActivity.this, R.string.subdir_is_null,
                            Toast.LENGTH_LONG).show();
                    hideLoadIcon();
                    listView.setCanMove(true);
                    // updateUPnPPage();
                    break;
                case NEXTPAGE:
                    updateFileList();
                    loadNextPageFinish = true;
                    break;
                case IMAGE:
                    showImage();
                    break;
                case IMAGEINFO:
                    if (imageInfo != null)
                    {
                        updateMediaInfo(fileName, imageInfo);
                    }
                    imageInfo = null;
                    break;
                case VIDEOINFO:
                    if (videoInfo != null)
                    {
                        updateMediaInfo(fileName, videoInfo);
                    }
                    videoInfo = null;
                    break;
                case AUDIOINFO:
                    if (audioInfo != null)
                    {
                        updateMediaInfo(fileName, audioInfo);
                    }
                    audioInfo = null;
                    break;
                case PROGRESS:
                    if (mediaPlayer != null && mediaPlayer.isPlaying())
                    {
                        int curIntTime = mediaPlayer.getCurrentPosition();
                        sumIntTime = mediaPlayer.getDuration();
                        curTime.setText(getStringTime(curIntTime));
                        allTime.setText(getStringTime(sumIntTime));
                        videoBar.setProgress(curIntTime);
                    }
                    break;
                case UNSUPPORT:
                    hideVideoPrepareProgress();
                    stopNetWorkSpeedTimer();
                    showUnSupport();
                    break;
                case SUPPORT:
                    hideUnSupport();
                    break;
                case TIMEOUT:
                    stopNetWorkSpeedTimer();
                    hideVideoPrepareProgress();
                    timeout();
                    break;
                case DMSDOWN:
                    dmsDown();
                    break;
                case SURFACERELEASE:
                    Toast.makeText(MediaCenterActivity.this, getString(R.string.surface_released),
                            Toast.LENGTH_SHORT).show();
                    break;
                case RECONECT:
                    Toast.makeText(MediaCenterActivity.this, getString(R.string.net_reconect),
                            Toast.LENGTH_SHORT).show();
                    updateUPnPPage();
                    break;
                case PREPAREPROGRESS:
                {
                    Log.d(TAG, "prepare progress " + msg.what);
                    if(msg.what == 100 || unSupportImageView.getVisibility() == View.VISIBLE)
                    {
                        hideVideoPrepareProgress();
                    }
                    else
                    {
                        showVideoPrepareProgress(msg.what);
                        startNetWorkSpeedTimer();
                    }
                    break;
                }
                case UPDATENETSPEED:
                {
                    int netWorkSpeed = getNetWorkSpeed(mediaPlayer);
                    if (netWorkSpeed > 0)
                    {
                        mTextVie_NetWork_Speed.setText(netWorkSpeed + "Kbps");
                        mTextVie_NetWork_Speed.setVisibility(View.VISIBLE);
                    }
                    else
                    {
                        mTextVie_NetWork_Speed.setVisibility(View.INVISIBLE);
                    }
                    break;
                }
                default:
                    break;
            }
        }
    };

    /**
     * when ThreadTimeout is timeout, this function will be called to handle the timeout event
     */
    /**
     * 当ThreadTimeout超时时，会调用此函数做一些超时处理
     */
    private void timeout()
    {
        Log.e(TAG, "time out");
        Toast.makeText(this, getString(R.string.timeout), Toast.LENGTH_SHORT).show();
        dmpManager.breakBrowse();
        updateUPnPPage();
    }

    /**
     * show the DMS device is down when exception occurs in reading from URLConnection
     */

    /**
     * 当在网格数据传输中连接出问题时，会调用此函数表示DMS设备已经关闭
     */
    private void dmsDown()
    {
        Log.e(TAG, "dms is down");
        Toast.makeText(this, getString(R.string.dms_down), Toast.LENGTH_SHORT).show();
        updateUPnPPage();
    }

    private void initPlayer()
    {
        mediaPlayer = new MediaPlayerTemplate<MediaPlayer>(new MediaPlayer());
        // mediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
        mediaPlayer.setOnErrorAdapter(new VideoPlayerErrorAdapter());
        mediaPlayer.setOnCompletionAdapter(new VideoPlayerCompleteAdapter());
        mediaPlayer.setOnPreparedAdapter(new VideoPlayerOnPreparedAdapter());
        mediaPlayer.setOnInfoAdapter(new VideoPlayerOnInfoAdapter());
    }

    /** Called when the activity is first created. */
    public void onCreate(Bundle savedInstanceState)
    {
        Log.d(TAG, "onCreate");
        super.onCreate(savedInstanceState);
        mContext = this;
        dmpNative = DMPNative.getInstance();
        dmpManager = new DMPManager(DMPNative.getInstance());
        registerNetworkReceiver();
        register();
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        Window wnd = getWindow();
        if (null == wnd)
        {
            Log.e(TAG,"onCreate getWindow is null");
        }else
        {
            wnd.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        }
        setContentView(R.layout.main);
        fileExplore = new FileExplore();

        listView = (ListViewWithKeyEvent) findViewById(R.id.listView1);
        listView.addKeyEventListener(new ListViewListener());
        listView.setCanMove(true);
        surfaceView = (SurfaceView) findViewById(R.id.surfaceView1);
        surfaceView.setZOrderOnTop(true);
        surfaceView.getHolder().setFormat(PixelFormat.TRANSPARENT);
        surfaceView.getHolder().addCallback(new SurfaceCallback());
        videoView = (SurfaceView) findViewById(R.id.surfaceView2);
        videoView.getHolder().addCallback(new VideoSurfaceCallback());
        indexView = (TextView) findViewById(R.id.textView3);
        loadIcon = (ProgressBar) findViewById(R.id.progressBar1);
        ProgressBarVideoPrepare = (ProgressBar) findViewById(R.id.ProgressBarVideoPrepare);
        textView_videoPrepare = (TextView) findViewById(R.id.textView_videoPrepare);
        mTextVie_NetWork_Speed = (TextView) findViewById(R.id.textView_net_speed);
        infoView = (TextView) findViewById(R.id.textView4);
        fileNameView = (TextView) findViewById(R.id.textView12);

        videoBar = (ProgressBar) findViewById(R.id.progressBar2);
        videoBar.setVisibility(View.INVISIBLE);
        curTime = (TextView) findViewById(R.id.textView10);
        curTime.setVisibility(View.INVISIBLE);
        allTime = (TextView) findViewById(R.id.textView11);
        allTime.setVisibility(View.INVISIBLE);

        unSupportImageView = (ImageView) findViewById(R.id.imageView1);
        unSupportTextView = (TextView) findViewById(R.id.textView1);
        initPlayer();

        musicPic = BitmapFactory.decodeResource(getResources(), R.drawable.album);
        mainPic = BitmapFactory.decodeResource(getResources(), R.drawable.bigfolder);
        networkPic = BitmapFactory.decodeResource(getResources(), R.drawable.window_network);
        upnpPic = BitmapFactory.decodeResource(getResources(), R.drawable.window_upnp);
        nfsPic = BitmapFactory.decodeResource(getResources(), R.drawable.window_nfs);
        localPic = BitmapFactory.decodeResource(getResources(), R.drawable.window_local);
        unsupportedWindowImage = BitmapFactory.decodeResource(getResources(),
                R.drawable.window_unsupport);
        windowServerPic = BitmapFactory.decodeResource(getResources(), R.drawable.window_dmsserver);

        hideUnSupport();

        deviceNameView = (TextView) findViewById(R.id.textView2);
        pathView = (TextView) findViewById(R.id.textView5);
        showLoadIcon();
        displayingImage = DisplayingImage.ROOT;
        loadNextPageFinish = true;
        updateUPnPPage();
        rootItem = RootItem.NETWORK;
        setTextSize();
        DecodeUtil.HI_ImageDeocde_Init();
    }

    /**
     * Setting fixed size font in xml doesn't work, so do it in code
     */

    /**
     * 因为在配置文件里设置固定字体在改变系统字体时，字体大小还会变化，所以在此处设置固定字体
     */
    private void setTextSize()
    {
        indexView.setTextSize(DEF_TEXTSIZE);
        infoView.setTextSize(15);
        fileNameView.setTextSize(15);
        curTime.setTextSize(DEF_TEXTSIZE);
        allTime.setTextSize(DEF_TEXTSIZE);
        unSupportTextView.setTextSize(DEF_TEXTSIZE);
        deviceNameView.setTextSize(DEF_TEXTSIZE);
        pathView.setTextSize(DEF_TEXTSIZE);
        ((TextView) findViewById(R.id.textView6)).setTextSize(15);
        ((TextView) findViewById(R.id.textView7)).setTextSize(15);
        ((TextView) findViewById(R.id.textView8)).setTextSize(15);
        ((TextView) findViewById(R.id.textView9)).setTextSize(15);
        ((TextView) findViewById(R.id.moreText)).setTextSize(15);
    }

    /**
     * show category bitmap in mini window, such as Network, Upnp...
     */

    /**
     * 在小窗口显示类别图片，如网络，UPNP等
     */
    private void showImage(RootItem item)
    {
        showImage(upnpPic);
        // switch(item) {
        // case NETWORK:
        // showImage(networkPic);
        // break;
        // case UPNP:
        // showImage(upnpPic);
        // break;
        // case NFS:
        // showImage(nfsPic);
        // break;
        // case LOCAL:
        // showImage(localPic);
        // break;
        // }
    }

    /**
     * 在小窗口中显示图片
     * @param bitmap 要显示的图片
     */
    private void showImage(Bitmap bitmap)
    {
        if (null == bitmap)
        {
            return;
        }
        videoView.setVisibility(View.GONE);
        surfaceView.setVisibility(View.VISIBLE);
        int surfaceWidth = surfaceView.getWidth();
        int surfaceHeight = surfaceView.getHeight();
        int bitmapWidth = bitmap.getWidth();
        int bitmapHeigth = bitmap.getHeight();
        Log.d(TAG, "bitmap width: " + bitmapWidth);
        Log.d(TAG, "bitmap height: " + bitmapHeigth);
        int x = (surfaceWidth - bitmapWidth) / 2;
        x = (x > 0) ? x : 0;
        int y = (surfaceHeight - bitmapHeigth) / 2;
        y = (y > 0) ? y : 0;
        SurfaceHolder holder = surfaceView.getHolder();
        try
        {
            Canvas canvas = holder.lockCanvas();
            if (canvas != null)
            {
                canvas.setDrawFilter(paintFilter);
                canvas.drawColor(Color.TRANSPARENT, Mode.CLEAR);
                canvas.drawBitmap(bitmap, x, y, null);
                holder.unlockCanvasAndPost(canvas);
            }
            else
            {
                Log.d(TAG, "canvas == null");
            }
        }
        catch (Exception e)
        {
            Log.e(TAG, "lockCanvas", e);
        }
    }

    /**
     * alert the user with unsupported view
     */

    /**
     * 遇到不支持的图片时，调用此函数在界面上显示不支持提示用户
     */
    private void showUnSupport()
    {
        unSupportImageView.setVisibility(View.VISIBLE);
        unSupportTextView.setVisibility(View.VISIBLE);
        showImage(unsupportedWindowImage);
    }

    /**
     * hide unsupported view when watch the next item
     */
    /**
     * 在浏览下一个资源时，隐藏上一次显示的不支持的提示
     */
    private void hideUnSupport()
    {
        unSupportImageView.setVisibility(View.INVISIBLE);
        unSupportTextView.setVisibility(View.INVISIBLE);
    }

    /**
     * show folder image in mini window
     */

    /**
     * 在小窗口显示文件夹图标
     */
    private void showMainPic()
    {
        if (mainPic != null)
        {
            showImage(mainPic);
        }
    }

    /**
     * show the default music image
     */

    /**
     * 在音乐界面显示默认图标
     */
    private void showMusicPic()
    {
        if (musicPic != null)
        {
            showImage(musicPic);
        }
    }

    /**
     * format the time to 00:00:00
     */

    /**
     * 格式化时间为00:00:00格式
     */
    private String getStringTime(int time)
    {
        int seconds = time / 1000;
        int minites = seconds / 60;
        seconds = seconds % 60;
        int hours = minites / 60;
        minites = minites % 60;
        return hours + ":" + ((minites < 10) ? "0" : "") + minites + ":"
                + ((seconds < 10) ? "0" : "") + seconds;
    }

    protected void onPause()
    {
        Log.d(TAG, "onPause");
        super.onPause();
        // isGifShow = false; //t00204177 for DTS2012122507391 no response.
        if (unSupportImageView.getVisibility() == View.VISIBLE)
        {
            isUnsupportShow = true;
        }
        listPos = listView.getSelectedItemPosition();
        interruptSomeThread();
        joinSomeThread();
        //interruptAllThread();
        if (mediaPlayer != null)
        {
            mediaPlayer.release();
            mediaPlayer = null;
        }
        stopNetWorkSpeedTimer();
        hideVideoPrepareProgress();
    }

    protected void onResume()
    {
        Log.d(TAG, "onResume");
        super.onResume();
        isVideoClicked = false;
        listView.setCanMove(true);
        if (mediaPlayer == null)
        {
            initPlayer();
        }
    }

    protected void onRestart()
    {
        Log.d(TAG, "onRestart");
        super.onRestart();
    }

    protected void onDestroy()
    {
        Log.d(TAG, "onDestroy()");
        super.onDestroy();
        DecodeUtil.HI_ImageDeocde_DeInit();
        unregisterNetworkReceiver();
        unregisterReceiver(netStateChangeReceiver);
        if (mBitmap != null && !mBitmap.isRecycled())
        {
            mBitmap.recycle();
            mBitmap = null;
        }
        musicPic.recycle();
        mainPic.recycle();
        networkPic.recycle();
        nfsPic.recycle();
        upnpPic.recycle();
        localPic.recycle();
        joinSomeThread();
        interruptSomeThread();
        // interruptAllThread();
        try
        {
            Log.d(TAG, "onDestroy before destroy");
            dmpManager.destroy();
            Log.d(TAG, "onDestroy end destroy");
        }
        catch (Exception e)
        {
            Log.e(TAG, "onDestroy dmpManager.destroy()", e);
        }
    }

    /**
     * update the index view in HiMediaCenter
     */

    /**
     * 更新HiMediaCenter主界面上资源索引
     */
    private void updateIndexView(int index, int total)
    {
        this.index[0] = index;
        this.index[1] = total;
        indexView.setText("" + (index + 1) + "/" + total);
    }

    /**
     * update media info in UI
     * @param fileName file name
     * @param info detail info of the media
     */

    /**
     * 更新界面上的媒体信息
     * @param fileName 文件名称
     * @param info 详细信息
     */
    private void updateMediaInfo(String fileName, String info)
    {
        fileNameView.setText(getString(R.string.mediaName) + fileName);
        infoView.setText(info);
    }

    /**
     * update the path in UI
     */

    /**
     * 更新界面上的路径显示
     */
    private void updatePathView()
    {
        Log.d(TAG, "updatePathView");
        AbstractFile focusFile = fileExplore.getFocusFile();
        if (focusFile != null)
        {
            Log.d(TAG, "focusFile.name=" + focusFile.getName());
            AbstractFile afile = focusFile.getParentFile();
            if (null != afile)
            {
                String path = fileExplore.getPath(afile);
                pathView.setText(path);
            }
            else if (focusFile instanceof DMSFile)
            {
                DMSDevice device = ((DMSFile) focusFile).getDevice();
                if (device != null)
                {
                    pathView.setText(device.getName());
                }
            }
        }
        else
        {
            AbstractFile fileParen = fileExplore.getParent();
            if (null != fileParen)
            {
                Log.d(TAG, "this dir is empty");
                String path = fileExplore.getPath(fileParen);
                pathView.setText(path);
            }
        }
        if (rootItem != null)
        {
            deviceNameView.setText(getString(rootItem.getNameId()));
        }
        else
        {
            deviceNameView.setText(R.string.mediaType);
        }
    }

    /**
     * update index of resources, total num is unchanging
     */

    /**
     * 更新资源索引，总数目不变
     */
    private void updateIndexView(int index)
    {
        this.index[0] = index;
        indexView.setText("" + (index + 1) + "/" + this.index[1]);
    }

    /**
     * show loading icon
     */

    /**
     * 显示Loading图标
     */
    private void showLoadIcon()
    {
        loadIcon.setVisibility(View.VISIBLE);
    }

    /**
     * hide loading icon
     */

    /**
     * 隐藏Loading图标
     */
    private void hideLoadIcon()
    {
        loadIcon.setVisibility(View.INVISIBLE);
    }

    private void showVideoPrepareProgress(int progress)
    {
        if(progress < 0)
        {
            textView_videoPrepare.setText("0%");
        }
        else if(progress > 100)
        {
            textView_videoPrepare.setText("100%");
        }
        else
        {
            textView_videoPrepare.setText(progress + "%");
        }
        ProgressBarVideoPrepare.setVisibility(View.VISIBLE);
        textView_videoPrepare.setVisibility(View.VISIBLE);
    }

    private void startNetWorkSpeedTimer()
    {
        if(null == mNetWorkSpeedTimer)
        {
            mNetWorkSpeedTimer = new Timer();
            mNetWorkSpeedTimer.schedule(new UpdateNetWorkSpeedTimerTask(), 500, 1000);
        }
    }

    private void stopNetWorkSpeedTimer()
    {
        if (null != mNetWorkSpeedTimer)
        {
            mNetWorkSpeedTimer.cancel();
            mNetWorkSpeedTimer = null;
            mTextVie_NetWork_Speed.setText("0Kbps");
            mTextVie_NetWork_Speed.setVisibility(View.INVISIBLE);
        }
    }

    private void hideVideoPrepareProgress()
    {
        textView_videoPrepare.setText("0%");
        ProgressBarVideoPrepare.setVisibility(View.INVISIBLE);
        textView_videoPrepare.setVisibility(View.INVISIBLE);
    }
    /**
     * jump to the top level(Network, Upnp...)
     */

    /**
     * 跳转到最顶层，(网络、Upnp...)
     */
    //private void updateRootList()
    private void updateUPnPPage()
    {
        Log.d(TAG, "updateUPnPPage");
        interruptAllThread();
        listView.setCanMove(true);
        fileExplore.unInitExplore();
        hideLoadIcon();
        hideUnSupport();
        if (mediaPlayer != null && mediaPlayer.isPlaying())
        {
            mediaPlayer.stop();
            mediaPlayer.reset();
        }
        ArrayList<HashMap<String, Object>> listItem = new ArrayList<HashMap<String, Object>>();
        List<RootItem> rootItems = fileExplore.getRootList();
        Log.d(TAG, "rootItems.size()=" + rootItems.size());
        for (RootItem item : rootItems)
        {
            HashMap<String, Object> map = new HashMap<String, Object>();
            map.put("name", getString(item.getNameId()));
            map.put("image", item.getDrawableId());
            listItem.add(map);
        }
        String[] itemType = { "name", "image" };
        int[] itemPos = { R.id.ItemName, R.id.ItemImage };
        SimpleAdapter adapter = new SimpleAdapter(this, listItem, R.layout.list_items, itemType,
                itemPos);
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new UPnPPageClickListener());
        listView.setOnItemSelectedListener(new UPnPPageSelectedListener());
        listView.requestFocus();
        listView.setSelection(0);
        hideInfo();
        showImage(RootItem.UPNP);
        pathView.setText(R.string.sourcePath);
        updateIndexView(0, 1); // RootItem.values().length
    }

    /**
     * update device list(second level)
     */
    /**
     * 更新设备列表，即第二层目录
     */
    //private void updateTopLevelList()
    private void updateDevicePage()
    {
        Log.d(TAG, "updateDevicePage()");
        listView.setCanMove(true);
        if (timer != null)
        {
            timer.cancel();
            timer = null;
        }
        hideLoadIcon();
        hideInfo();
        ArrayList<HashMap<String, Object>> listItem = new ArrayList<HashMap<String, Object>>();
        if (fileExplore.getExplore() instanceof UpnpExplore)
        {
            List<DMSDevice> deviceList = ((UpnpExplore) fileExplore.getExplore()).getDeviceList();
            Log.d(TAG, "deviceList.size():" + deviceList.size());
            if (deviceList.size() == 0)
            {
                canLoadTopList = false;
                AlertDialog dialog = new AlertDialog.Builder(MediaCenterActivity.this)
                        .setTitle(getString(R.string.NoDMS))
                        .setMessage(getString(R.string.tryLater))
                        .setPositiveButton(getString(R.string.quit),
                                new DialogInterface.OnClickListener()
                                {
                                    public void onClick(DialogInterface dialogInterface, int i)
                                    {
                                        // MediaCenterActivity.this.finish();
                                        updateUPnPPage();
                                    }
                                }).create();
                dialog.setOnCancelListener(new DialogInterface.OnCancelListener()
                {
                    public void onCancel(DialogInterface dialogInterface)
                    {
                        updateUPnPPage();
                    }
                });
                dialog.show();
                return;
            }
            updateIndexView(0, deviceList.size());
            for (DMSDevice device : deviceList)
            {
                HashMap<String, Object> map = new HashMap<String, Object>();
                map.put("name", device.getName());
                map.put("image", R.drawable.icon_dmsserver);
                listItem.add(map);
            }
        }
        String[] itemType = { "name", "image" };
        int[] itemPos = { R.id.ItemName, R.id.ItemImage };
        SimpleAdapter adapter = new SimpleAdapter(this, listItem, R.layout.list_items, itemType,
                itemPos);
        listView.setAdapter(adapter);
        showImage(windowServerPic);
        listView.setOnItemClickListener(new DeviceClickListener());
        listView.setOnItemSelectedListener(new DeviceSelectListener());
        if (selectDevicePos < listView.getCount())
        {
            listView.setSelection(selectDevicePos);
        }
    }

//    private void playLiveTVPlayChannel(AbstractFile file)
//    {
//        if (null == file)
//        {
//            return;
//        }
//        BaseAction playAction = new PlayAction(Controller.DMP, file);
//
//        Intent intent = new Intent();
//        intent.setAction(Constant.START_PLAYER_ACTIVITY_ACTION);
//        intent.putExtra("action", playAction);
//        MediaCenterActivity.this.sendBroadcast(intent);
//    }

    /**
     * update file list
     */
    /**
     * 更新文件列表
     */
    private void updateFileList()
    {
        if (timer != null)
        {
            timer.cancel();
            timer = null;
        }
        hideUnSupport();
        hideInfo();
        listView.setCanMove(true);
        listView.requestFocus();
        Log.d(TAG, "updateFileList()");
        hideLoadIcon();
        ArrayList<HashMap<String, Object>> listItem = new ArrayList<HashMap<String, Object>>();
        List<AbstractFile> fileList = fileExplore.getFileList();
        HashMap<String, Object> map = new HashMap<String, Object>();
        map.put("name", "..");
        map.put("image", R.drawable.folder);
        listItem.add(map);
        if (fileList != null)
        {
//            try
//            // add for LiveTV 20131023
//            {
//                AbstractFile fileParent = fileExplore.getParent();
//                if (null != fileParent && fileParent.getName().equals("LiveTV"))
//                {
//                    AbstractFile file = null;
//                    for (int i = 0; i < fileList.size(); i++)
//                    {
//                        if (fileList.get(i).getFileType() == FileType.VIDEO)
//                        {
//                            file = fileList.get(i);
//                            break;
//                        }
//                    }
//                    if (null != file)
//                    {
//                        playLiveTVPlayChannel(file);
//                    }
//                }
//            }
//            catch (Exception e)
//            {
//                // TODO Auto-generated catch block
//                e.printStackTrace();
//            }

            for (AbstractFile file : fileList)
            {
                map = new HashMap<String, Object>();
                switch (file.getFileType())
                {
                    case DIRECTORY:
                        map.put("image", R.drawable.folder);
                        break;
                    case AUDIO:
                        map.put("image", R.drawable.music);
                        break;
                    case VIDEO:
                        map.put("image", R.drawable.video);
                        break;
                    case IMAGE:
                        map.put("image", R.drawable.image);
                        break;
                }
                map.put("name", file.getName());
                listItem.add(map);
            }
        }
        String[] itemType = { "image", "name" };
        int[] itemPos = { R.id.ItemImage, R.id.ItemName };
        SimpleAdapter adapter = new SimpleAdapter(this, listItem, R.layout.list_items, itemType,
                itemPos);
        listView.setAdapter(adapter);
        showMainPic();
        listView.setOnItemClickListener(new FileClickListener());
        listView.setOnItemSelectedListener(new FileSelectListener());
        listView.setOnScrollListener(new FileOnScrollListener());
        listView.setSelection(listPos);
        if (fileList != null)
        { // Resolve NullPointerException by fileList
            updateIndexView(0, fileList.size());
        }
    }

    /**
     * start DMP Server
     */

    /**
     * 开启DMP服务
     */
    class StartDMPServerThread extends Thread
    {
        public void run()
        {
            try
            {
                Log.d(TAG, "before create");
                dmpManager.create(mContext);
                Log.d(TAG, "end create");
            }
            catch (Exception e)
            {
                Log.e(TAG, "dmpManager.create()", e);
            }
        }
    }

    /**
     * stop DMP Server
     */

    /**
     * 关闭DMP服务
     */
    class StopDMPServerThread extends Thread
    {
        public void run()
        {
            try
            {
                Log.d(TAG, "before destroy");
                dmpManager.destroy();
                Log.d(TAG, "end destroy");
            }
            catch (Exception e)
            {
                Log.e(TAG, "dmpManager.destroy()", e);
            }
        }
    }

    /**
     * The thread of updating device list
     */

    /**
     * 更新设备列表的线程
     */
    //class UpdateTopListThread extends ThreadTimeout
    class UpdateDevicePageThread extends ThreadTimeout
    {
        public void run()
        {
            super.run();
            Log.d(TAG, "UpdateDevicePageThread");
            canLoadTopList = true;
            while (startDMPThread != null && startDMPThread.isAlive())
            {
                try
                {
                    Thread.sleep(500);
                }
                catch (Exception e)
                {
                    Log.e(TAG, "sleep()", e);
                }
            }
            while (canLoadTopList)
            {
                topLoadFinish = false;
                Log.d(TAG, "load device");
                fileExplore.updateTopList();
                try
                {
                    Thread.sleep(5000);
                }
                catch (Exception e)
                {
                    Log.e(TAG, "sleep", e);
                    return;
                }
                while (!topLoadFinish)
                {
                    try
                    {
                        Thread.sleep(1000);
                    }
                    catch (Exception e)
                    {
                        Log.e(TAG, "sleep UpdateDevicePageThread", e);
                        return;
                    }
                }
                Log.e(TAG, "call server call back");
                break;
            }
        }
    }

    /**
     * update the top file list of one device
     */

    /**
     * 更新设备下的第一层目录
     */
    class UpdateTopFileListThread extends ThreadTimeout
    {
        private DMSDevice device;

        public UpdateTopFileListThread(DMSDevice device)
        {
            this.device = device;
        }

        public void run()
        {
            super.run();
            fileExplore.gotoTop(device);
        }
    }

    /**
     * Thread of updating file list
     */

    /**
     * 更新文件列表的线程
     */
    class UpdateFileListThread extends ThreadTimeout
    {
        private AbstractFile focusFile;

        public UpdateFileListThread(AbstractFile focusFile)
        {
            this.focusFile = focusFile;
        }

        public void run()
        {
            super.run();
            fileExplore.setFocusFile(focusFile);
            fileExplore.gotoSubDir();
        }
    }

    /**
     * Thread of updating next page
     */

    /**
     * 更新下一页的线程
     */
    class UpdateNextPageThread extends ThreadTimeout
    {
        public void run()
        {
            super.run();
            loadNextPageFinish = false;
            fileExplore.gotoNextPage();
            while (!loadNextPageFinish)
            {
                try
                {
                    Thread.sleep(1000);
                }
                catch (Exception e)
                {
                    Log.e(TAG, "sleep", e);
                }
            }
        }
    }

    /**
     * Thread of updating parent dirs
     */

    /**
     * 更新上级目录列表的线程
     */
    class UpdateParentDirThread extends ThreadTimeout
    {
        public void run()
        {
            super.run();
            fileExplore.gotoParent();
        }
    }

    /**
     * Callback when completion of update, used by XXXExplore
     */

    /**
     * 更新完成回调，供XXXExplore使用
     */
    public void updateCompleteNotify(NotifyType type)
    {
        Message msg = new Message();
        switch (type)
        {
            case DEVICE:
                topLoadFinish = true;
                msg.obj = NotifyType.DEVICE;
                updateHandler.sendMessage(msg);
                break;
            case FILE:
                msg.obj = NotifyType.FILE;
                updateHandler.sendMessage(msg);
                break;
            case NEXTPAGE:
                msg.obj = NotifyType.NEXTPAGE;
                updateHandler.sendMessage(msg);
                break;
            case NULL:
                msg.obj = NotifyType.NULL;
                updateHandler.sendMessage(msg);
                break;
            default:
                Log.e(TAG, "type not support: " + type);
                break;
        }
    }

    /**
     * listener for click device item
     */

    /**
     * 点击设备项的监听
     */
    class DeviceClickListener implements OnItemClickListener
    {

        public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3)
        {
            Log.d(TAG, "click " + arg2);
            // FIXME for mouse click, update mini window with folder image
            displayingImage = DisplayingImage.FOLDER;
            canLoadTopList = false;
            listView.setCanMove(false);
            updateIndexView(arg2);
            if (fileExplore.getExplore() instanceof UpnpExplore)
            {

                DMSDevice device = ((UpnpExplore) (fileExplore.getExplore())).getDeviceList().get(
                        arg2);
                if (device != null)
                {
                    if (updateTopFileListThread != null && updateTopFileListThread.isAlive())
                    {
                        Log.d(TAG, "already loading");
                        Toast.makeText(MediaCenterActivity.this, R.string.already_loading,
                                Toast.LENGTH_SHORT).show();
                        return;
                    }
                    if (loadDevicePageThread != null && loadDevicePageThread.isAlive())
                    {
                        loadDevicePageThread.interrupt();
                        loadDevicePageThread = null;
                    }
                    showLoadIcon();
                    updateTopFileListThread = new UpdateTopFileListThread(device);
                    updateTopFileListThread.start();
                }
            }

        }
    }

    void updateFileSelectIndex(int arg2)
    {
        List<AbstractFile> lstFiles = fileExplore.getFileList();
        if (lstFiles == null || lstFiles.size() == 0)
        { // DTS2012112200286
            Log.e(TAG, "no file. Location:" + fileExplore.getLocation());
            updateIndexView(-1, 0);
            return;
        }
        if (arg2 == 0)
        {
            displayingImage = DisplayingImage.FOLDER;
            showMainPic();
            AbstractFile file = lstFiles.get(0);
            if (file instanceof DMSFile)
            {
                int sum = ((DMSFile) file).getSumNumOfSubFiles();
                int index = -1;
                updateIndexView(index, sum);
            }
            return;
        }
        else if (lstFiles.size() >= arg2)
        {
            arg2--;
            AbstractFile focusFile = lstFiles.get(arg2);
            if (focusFile.getFileType() == FileType.DIRECTORY)
            {
                displayingImage = DisplayingImage.FOLDER;
                showMainPic();
            }
            if (focusFile instanceof DMSFile)
            {
                int sum = ((DMSFile) focusFile).getSumNumOfSubFiles();
                int index = ((DMSFile) focusFile).getOffset();
                updateIndexView(index, sum);
            }
        }
    }

    /**
     * listener for clicking file item
     */

    /**
     * 点击文件时的监听
     */
    class FileClickListener implements OnItemClickListener
    {
        public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3)
        {
            Log.d(TAG, "click file " + arg2);
            listView.setCanMove(false);
            updateFileSelectIndex(arg2);
            listPos = 0;
            if (arg2 == 0)
            {
                if (fileExplore.getLocation() == Location.TOP)
                {
                    loadDevicePageThread = new UpdateDevicePageThread();
                    loadDevicePageThread.start();
                    canLoadTopList = true;
                }
                else
                {
                    new UpdateParentDirThread().start();
                }
                showLoadIcon();
                return;
            }
            arg2--;
            List<AbstractFile> lstFiles = fileExplore.getFileList();
            if ((null == lstFiles) || (lstFiles.size() <= arg2))
            {
                Log.e(TAG, "list index is larger than size");
                return;
            }
            AbstractFile file = lstFiles.get(arg2);
            if (file.getFileType() == FileType.DIRECTORY)
            {
                showLoadIcon();
                // need
                if (updateFileListThread != null && updateFileListThread.isAlive())
                {
                    Log.d(TAG, "loading thread is already running");
                    Toast.makeText(MediaCenterActivity.this, R.string.already_loading,
                            Toast.LENGTH_SHORT).show();
                    return;
                }
                // for mouse click, update mini window with folder image
                displayingImage = DisplayingImage.FOLDER;
                updateFileListThread = new UpdateFileListThread(file);
                updateFileListThread.start();
            }
            if (file instanceof DMSFile && file.getFileType() != FileType.DIRECTORY)
            {
                if (file.getFileType() == FileType.VIDEO && mediaPlayer != null)
                {
                    isVideoClicked = true;
                    mediaPlayer.stop();
                    mediaPlayer.reset();
                }
                BaseAction playAction = new PlayAction(Controller.DMP, file);
                Log.d(TAG, "send broadcast with DMSFile");

                Intent intent = new Intent();
                intent.setAction(Constant.START_PLAYER_ACTIVITY_ACTION);
                intent.putExtra("action", playAction);

                DMSFile dmsfile = (DMSFile)file;
                String contentType = null;
                String contentLength = null;
                String type = dmpNative.HI_DmpGetHead(dmsfile.getUrl());
                Log.d(TAG,"Head:"+type);
                if (null != type)
                {
                    Pattern pServ = Pattern.compile("[Cc][Oo][Nn][Tt][Ee][Nn][Tt]-[Tt][Yy][Pp][Ee]: (.+)");
                    Matcher mServ = pServ.matcher((CharSequence) type);
                    if (mServ.find())
                    {
                        Log.d(TAG, "CONTENT-TYPE:" + mServ.group(1));
                        contentType = mServ.group(1);
                    }
                    else
                    {
                        Log.d(TAG, "CONTENT-TYPE: not matcher");
                    }

                    pServ = Pattern.compile("[Cc][Oo][Nn][Tt][Ee][Nn][Tt]-[LL][Ee][Nn][Gg][Tt][Hh]: ([0-9]*)");
                    mServ = pServ.matcher((CharSequence) type);
                    if (mServ.find())
                    {
                        Log.d(TAG, "CONTENT-LENGTH:" + mServ.group(1));
                        contentLength = mServ.group(1);
                    }
                    else
                    {
                        Log.d(TAG, "CONTENT-LENGTH: not matcher");
                    }
                }
                intent.putExtra("ContentType",contentType);
                intent.putExtra("ContentLength",contentLength);
                CommonDef.sendBroadcastEx(MediaCenterActivity.this, intent);
            }
        }
    }

    class DeviceSelectListener implements OnItemSelectedListener
    {
        public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3)
        {
            displayingImage = DisplayingImage.DEVICE;
            showImage(windowServerPic);
            updateIndexView(arg2);
            selectDevicePos = arg2;
        }

        public void onNothingSelected(AdapterView<?> arg0)
        {
            // 鑻ユ槸浠�箞閮芥病閫変腑锛岄粯璁ょ涓�釜
            showMainPic();
            updateIndexView(0);
        }
    }

    /**
     * listener for selecting file item, when one item is select, previewing is starting
     */

    /**
     * 文件被选中时的监听，此时开始预览
     */
    class FileSelectListener implements OnItemSelectedListener
    {
        public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3)
        {
            if (networkTimer != null)
            {
                networkTimer.cancel();
                networkTimer = null;
            }
            // isGifShow = false;
            interruptVideoUnsupportShow = true;
            hideUnSupport();
            interruptAllThread();
            hideInfo();

            if (mediaPlayer != null && mediaPlayer.isPlaying())
            {
                mediaPlayer.stop();
                mediaPlayer.reset();
            }
            loadId = System.currentTimeMillis();
            List<AbstractFile> lstFiles = fileExplore.getFileList();
            if (lstFiles == null || lstFiles.size() == 0)
            { // DTS2012112200286
                Log.e(TAG, "no file. Location:" + fileExplore.getLocation());
                updateIndexView(-1, 0);
                return;
            }

            if (arg2 == 0)
            {
                // 鐖剁洰褰�
                displayingImage = DisplayingImage.FOLDER;
                showMainPic();
                AbstractFile file = lstFiles.get(0);
                if (file instanceof DMSFile)
                {
                    int sum = ((DMSFile) file).getSumNumOfSubFiles();
                    int index = -1;
                    updateIndexView(index, sum);
                }
                return;
            }

            //The array index, subtract 1
            AbstractFile focusFile = lstFiles.get(arg2 - 1);
            if (focusFile.getFileType() == FileType.DIRECTORY)
            {
                displayingImage = DisplayingImage.FOLDER;
                showMainPic();
            }
            if (focusFile instanceof DMSFile)
            {
                int sum = ((DMSFile) focusFile).getSumNumOfSubFiles();
                int index = ((DMSFile) focusFile).getOffset();
                updateIndexView(index, sum);
            }
            switch (focusFile.getFileType())
            {
                case IMAGE:
                    displayingImage = DisplayingImage.IMAGE;
                    videoBar.setVisibility(View.INVISIBLE);
                    curTime.setVisibility(View.INVISIBLE);
                    allTime.setVisibility(View.INVISIBLE);
                    if (focusFile instanceof DMSFile)
                    {
                        String url = ((DMSFile) focusFile).getUrl();
                        Log.d(TAG, "image url:" + url);
                        if (loadImageThread != null && loadImageThread.isAlive())
                        {
                            loadImageThread.interrupt();
                            loadImageThread = null;
                        }
                        loadImageThread = new LoadImageThread(focusFile.getName(), url,
                                focusFile.getFileSize(), loadId);
                        loadImageThread.start();
                    }
                    break;
                case VIDEO:
                    displayingImage = DisplayingImage.VIDEO;
                    videoBar.setVisibility(View.VISIBLE);
                    curTime.setVisibility(View.VISIBLE);
                    allTime.setVisibility(View.VISIBLE);
                    if (focusFile instanceof DMSFile)
                    {
                        String url = ((DMSFile) focusFile).getUrl();
                        Log.d(TAG, "video url:" + url);
                        if (progressThread != null && progressThread.isAlive())
                        {
                            progressThread.interrupt();
                            progressThread = null;
                        }
                        if (loadVideoThread != null && loadVideoThread.isAlive())
                        {
                            loadVideoThread.interruptThread();
                            loadVideoThread.interrupt();
                            loadVideoThread = null;
                        }
                        loadVideoThread = null;
                        videoView.setVisibility(View.VISIBLE);
                        surfaceView.setVisibility(View.INVISIBLE);
                        fileSize = focusFile.getFileSize();
                        loadVideoThread = new LoadVideoThread(focusFile.getName(), url,
                                focusFile.getFileSize(), loadId);
                        loadVideoThread.start();
                        interruptVideoUnsupportShow = false;
                    }
                    break;
                case AUDIO:
                    displayingImage = DisplayingImage.MUSIC;
                    showMusicPic();
                    videoBar.setVisibility(View.INVISIBLE);
                    curTime.setVisibility(View.INVISIBLE);
                    allTime.setVisibility(View.INVISIBLE);
                    if (focusFile instanceof DMSFile)
                    {
                        String url = ((DMSFile) focusFile).getUrl();
                        String album = ((DMSFile) focusFile).getAlbum();
                        String artist = ((DMSFile) focusFile).getArtist();
                        String genre = ((DMSFile) focusFile).getGenre();
                        String date = ((DMSFile) focusFile).getDate();
                        String albumArtURI = ((DMSFile) focusFile).getAlbumArtURI();
                        Log.d(TAG, "audio url:" + url);
                        if (loadAudioThread != null && loadAudioThread.isAlive())
                        {
                            loadAudioThread.interrupt();
                            loadAudioThread = null;
                        }
                        loadAudioThread = new LoadAudioThread(focusFile.getName(), url, album,
                                artist, date, genre, albumArtURI, loadId);
                        loadAudioThread.start();
                    }
                    break;
            }
        }

        public void onNothingSelected(AdapterView<?> arg0)
        {
            Log.d(TAG, "onNothingSelected");
            List<AbstractFile> lstFiles = fileExplore.getFileList();
            if ((null == lstFiles) || (lstFiles.size() <= 0))
            {
                return;
            }
            AbstractFile focusFile = lstFiles.get(0);
            // fileExplore.setFocusFile(focusFile);
            if (focusFile instanceof DMSFile)
            {
                int sum = ((DMSFile) focusFile).getSumNumOfSubFiles();
                updateIndexView(0, sum);
            }
        }
    }

    class FileOnScrollListener implements OnScrollListener
    {

        @Override
        public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount,
                int totalItemCount)
        {
            // TODO Auto-generated method stub
            listView.requestFocusFromTouch();
        }

        @Override
        public void onScrollStateChanged(AbsListView view, int scrollState)
        {
            // TODO Auto-generated method stub

            if (scrollState == OnScrollListener.SCROLL_STATE_IDLE)
            {

                listView.setSelection(view.getFirstVisiblePosition());

                if (canLoadTopList)
                {
                    return;
                }

                int listViewCount = view.getCount();// listView.getCount();
                int listViewPos = view.getLastVisiblePosition();// listView.getSelectedItemPosition();

                if (listViewPos == listViewCount - 1)
                {
                    List<AbstractFile> lstFiles = fileExplore.getFileList();
                    if ((null != lstFiles) && (lstFiles.size() > 0))
                    {
                        AbstractFile file = lstFiles.get(0);
                        int sum = ((DMSFile) file).getSumNumOfSubFiles();
                        Log.d(TAG, "listViewCount=" + listViewCount);
                        Log.d(TAG, "listViewPos=" + listViewPos);
                        Log.d(TAG, "sum=" + sum);
                        if (listViewCount < sum)
                        {
                            if (!loadNextPageFinish)
                            {
                                showLoadIcon();
                                return;
                            }
                            updateNextPageThread = new UpdateNextPageThread();
                            updateNextPageThread.start();
                            listPos = listViewPos + 1;
                        }
                    }
                }
            }
        }

    }

    /**
     * show the decode image
     */

    /**
     * 显示解出来的图片
     */
    synchronized private void showImage()
    {
        if (mBitmap == null)
        {
            Log.e(TAG, "mBitmap is null");
            return;
        }
        surfaceView.setVisibility(View.VISIBLE);
        videoView.setVisibility(View.INVISIBLE);

        // float bex = surfaceView.getWidth()/(float)mBitmap.getWidth();
        // float bey = surfaceView.getHeight()/(float)mBitmap.getHeight();
        // float be = 1;
        // if (bex > 1 && bey > 1) {
        // be = 1;
        // } else {
        // be = Math.min(bex, bey);
        // }
        // Matrix m = new Matrix();
        // m.postScale(be,be);

        double bitmapWH = mBitmap.getWidth() * 1.0 / mBitmap.getHeight();
        double surfaceWH = surfaceView.getWidth() * 1.0 / surfaceView.getHeight();
        int x = 0;
        int y = 0;
        if (bitmapWH < surfaceWH)
        {
            // 高占主导
            Log.d(TAG, "height is big");
            y = (surfaceView.getHeight() - mBitmap.getHeight()) / 2;
            y = y > 0 ? y : 0;
            // x = (int)(y*bitmapWH);
            x = (int) ((surfaceView.getWidth() - (surfaceView.getHeight() - 2 * y) * bitmapWH) / 2);
            Log.d(TAG, "xx: " + x + ",yy: " + y);
        }
        else
        {
            // 宽占主导
            Log.d(TAG, "width is big");
            x = (surfaceView.getWidth() - mBitmap.getWidth()) / 2;
            x = x > 0 ? x : 0;
            if (bitmapWH < 0.01)
            {
                y = 0;
            }
            else
            {
                y = (int) ((surfaceView.getHeight() - (surfaceView.getWidth() - 2 * x) / bitmapWH) / 2);
            }
            Log.d(TAG, "xx: " + x + ",yy: " + y);
        }

        Rect srcRect = new Rect(0, 0, mBitmap.getWidth(), mBitmap.getHeight());
        Rect destRect = new Rect(x, y, surfaceView.getWidth() - x, surfaceView.getHeight() - y);
        SurfaceHolder holder = surfaceView.getHolder();
        Canvas canvas = holder.lockCanvas();
        if (canvas != null)
        {
            if (mBitmap != null)
            {
                canvas.setDrawFilter(paintFilter);
                canvas.drawColor(Color.TRANSPARENT, Mode.CLEAR);
                canvas.drawBitmap(mBitmap, srcRect, destRect, null);
            }
            holder.unlockCanvasAndPost(canvas);
        }
    }

    /**
     * decode image from url
     */

    /**
     * 从url中解图片
     */
    synchronized private void loadImage(String name, String url, long fileSize, long myLoadId)
    {
        if (mBitmap != null && !mBitmap.isRecycled())
        {
            mBitmap.recycle();
            mBitmap = null;
        }
        if (mediaPlayer != null && mediaPlayer.isPlaying())
        {
            mediaPlayer.stop();
            mediaPlayer.reset();
        }
        mBitmap = getBitmapThumbnail(name, url, fileSize,myLoadId);
        try
        {
            Thread.sleep(100);
        }
        catch (Exception e)
        {
            return;
        }
        Log.d(TAG, "loadImage url is changed ,myLoadId: " + myLoadId + " loadId:" + loadId);
        if(myLoadId != loadId)
        {
            return;
        }
        if (mBitmap == null)
        {
            Message msg = new Message();
            msg.obj = NotifyType.UNSUPPORT;
            updateHandler.sendMessage(msg);
        }
        else
        {
            Message msg = new Message();
            msg.obj = NotifyType.IMAGE;
            updateHandler.sendMessage(msg);
            Message supportmsg = new Message();
            supportmsg.obj = NotifyType.SUPPORT;
            updateHandler.sendMessage(supportmsg);
        }
    }

    /**
     * Thread of decoding image
     */

    /**
     * 解码图片的线程
     */
    class LoadImageThread extends Thread
    {
        private String name;
        private String url;
        private long fileSize;
        private long myLoadId;

        public LoadImageThread(String name, String url, long fileSize, long myLoadId)
        {
            this.name = name;
            this.url = url;
            this.fileSize = fileSize;
            this.myLoadId = myLoadId;
        }

        public void run()
        {
            try
            {
                Thread.sleep(100);
            }
            catch (Exception e)
            {
                Log.e(TAG, "sleep", e);
                return;
            }
            if (myLoadId != loadId)
            {
                Log.d(TAG, "LoadImageThread url is changed ,myLoadId: " + myLoadId + " loadId:" + loadId);
                return;
            }
            loadImage(name, url, fileSize , myLoadId);
        }
    }

    /**
     * the main function of decoding image
     */

    /**
     * 解码图片主函数
     */
    private Bitmap getBitmapThumbnail(String name, String url, long fileSize, long myLoadId)
    {
        if (url == null || url.length() == 0)
        {
            Log.e(TAG, "url is null");
            return null;
        }
        if (myLoadId != loadId)
        {
            Log.d(TAG, "getBitmapThumbnail url is changed ,myLoadId: " + myLoadId + " loadId:" + loadId);
            return null;
        }
        Bitmap bitmap = null;
        try
        {
            URL imageUrl = new URL(url);
            long size = 0;
            long oldTimeMillis = System.currentTimeMillis();
            String headerString = dmpNative.HI_DmpGetHead(url);
            if(null != headerString)
            {
                Pattern pServ = Pattern.compile("content-length: ([0-9]*)");
                Matcher mServ = pServ.matcher((CharSequence) headerString.toLowerCase());
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
            }
            long currentTimeMillis = System.currentTimeMillis() - oldTimeMillis;
            Log.d(TAG, "http connect used time:" + currentTimeMillis);
            Log.d(TAG, "length: " + size);

            size = (int) (size > fileSize ? size : fileSize);
            if (size > MAX_PIC_SIZE)
            {
                Message msg = new Message();
                msg.obj = NotifyType.UNSUPPORT;
                updateHandler.sendMessage(msg);
                return null;
            }

            Log.d(TAG, " use decodeStream");
            mDecodeMethod = new DecodeStreamMethod(imageUrl, 0,surfaceView.getWidth(),
                    surfaceView.getHeight());

            try
            {
                mDecodeMethod.prepare();
            }
            catch (DecodeException e)
            {
                Log.e(TAG, "mDecodeMethod.prepare()", e);
                if(null != mDecodeMethod)
                {
                    mDecodeMethod.interrupt();
                    mDecodeMethod = null;
                }
                Message msg = new Message();
                msg.obj = NotifyType.UNSUPPORT;
                updateHandler.sendMessage(msg);
                return null;
            }
            fileName = name;
            imageInfo = getString(R.string.imageResolution)
                    + (mDecodeMethod.getImageWidth() + "x" + mDecodeMethod.getImageHeight()) + "\n"
                    + getString(R.string.mediaSize) + formatFileSize(size);
            Message msg = new Message();
            msg.obj = NotifyType.IMAGEINFO;
            updateHandler.sendMessage(msg);
            try
            {
                bitmap = mDecodeMethod.decode();
            }
            catch (DecodeException e)
            {
                Log.e(TAG, "mDecodeMethod.decode()", e);
                msg = new Message();
                msg.obj = NotifyType.UNSUPPORT;
                updateHandler.sendMessage(msg);
                return null;
            }
        }
        catch (MalformedURLException e)
        {
            Log.e(TAG, "url: " + url, e);
            Message msg = new Message();
            msg.obj = NotifyType.UNSUPPORT;
            updateHandler.sendMessage(msg);
            return null;
        }
        catch (IOException e)
        {
            Log.e(TAG, "getBitmap()", e);
            Message msg = new Message();
            msg.obj = NotifyType.DMSDOWN;
            updateHandler.sendMessage(msg);
        }
        return bitmap;
    }

    /**
     * Thread of loading video
     */

    /**
     * 加载视频的线程
     */
    class LoadVideoThread extends Thread
    {
        private String name;
        private String url;
        private long myLoadId;
        private boolean mIsInterrupted;

        public LoadVideoThread(String name, String url, long fileSize, long myLoadId)
        {
            this.name = name;
            this.url = url;
            this.myLoadId = myLoadId;
            mIsInterrupted = false;
        }

        /**
         * Interrupt the search thread.<br>
         * CN: 打断搜索线程
         */
        public void interruptThread()
        {
            mIsInterrupted = true;
            if (mediaPlayer != null)
            {
                try
                {
                    mediaPlayer.reset();
                }
                catch (Exception e)
                {
                    Log.e(TAG, "mediaPlayer.reset error:" + e);
                }
            }
            hideVideoPrepareProgress();
        }

        public void run()
        {
            stopBackgroundMusic();
            Message msgPrePar = new Message();
            msgPrePar.obj = NotifyType.PREPAREPROGRESS;
            msgPrePar.what = 0;
            updateHandler.sendMessage(msgPrePar);
            try
            {
                if (mediaPlayer != null)
                {
                    mediaPlayer.reset();
                }
            }
            catch (Exception e)
            {
                Log.e(TAG, "mediaPlayer.reset()", e);
            }

            SystemClock.sleep(2000);
            if (mIsInterrupted)
            {
                Log.v(TAG,"is rrupted,url="+url);
                return;
            }
            if (myLoadId != loadId)
            {
                return;
            }
            if (mBitmap != null && !mBitmap.isRecycled())
            {
                mBitmap.recycle();
                mBitmap = null;
            }
            SurfaceHolder holder = videoView.getHolder();
            if (mediaPlayer == null)
            {
                return;
            }
            fileName = name;

            if (mIsInterrupted)
            {
                Log.v(TAG, "is rrupted,url=" + url);
                return;
            }
            Log.d(TAG, "LoadVideoThread url: " + url);
            // If you include the "dtcp1port=4999" said multiroom DTCP-IP, multiroom DTCP-IP does
            // not need to set the URL and play, has begun to play directly
            // Other DHCP-IP, you need to set the URL and ...
            boolean isDtcpItem = false;
            if (!url.contains("dtcp1port=4999"))
            {
                long getHeadusedTime0 = System.currentTimeMillis();
                String type = dmpNative.HI_DmpGetHead(url);
                long getHeadusedTime1 = System.currentTimeMillis();
                Log.d(TAG, "HI_DmpGetHead usedtime:" + String.valueOf(getHeadusedTime1 - getHeadusedTime0) + "ms");
                Log.d(TAG, "type HI_DmpGetHead:" + type);
                Log.d(TAG, "type HI_DmpGetHead: end <<=====================");
                if (null != type)
                {
                    if (type.contains("application/x-dtcp1"))
                    {
                        isDtcpItem = true;
                        Pattern pServ = Pattern.compile("DTCP1PORT=([0-9]+)");
                        Matcher mServ = pServ.matcher((CharSequence) type);
                        if (mServ.find())
                        {
                            url = url + "&dtcp1port=" + mServ.group(1);
                            Log.d(TAG, "url with DTCP1PORT :" + url);
                        }
                        else
                        {
                            Log.d(TAG, "Not find DTCP1PORT");
                        }
                        pServ = Pattern.compile("CONTENT-TYPE: (.+)");
                        mServ = pServ.matcher((CharSequence) type);
                        if (mServ.find())
                        {
                            Log.d(TAG, "CONTENT-TYPE:" + mServ.group(1));
                        }
                        else
                        {
                            Log.d(TAG, "CONTENT-TYPE: not matcher");
                        }

                        pServ = Pattern.compile("CONTENT-LENGTH: ([0-9]*)");
                        mServ = pServ.matcher((CharSequence) type);
                        if (mServ.find())
                        {
                            Log.d(TAG, "CONTENT-LENGTH:" + mServ.group(1));
                        }
                        else
                        {
                            Log.d(TAG, "CONTENT-LENGTH: not matcher");
                        }
                    }
                    else
                    {
                        isDtcpItem = false;
                    }
                }
            }

            try
            {
                if (mediaPlayer != null)
                {
                    Log.d(TAG, "setDataSource() url = " + url);
                    if (isDtcpItem)
                    {
                        mediaPlayer.setDataSource("dtcp:" + url);
                    }
                    else
                    {
                        mediaPlayer.setDataSource(url);
                    }
                }
            }
            catch (Exception e)
            {
                if (mediaPlayer != null)
                {
                    mediaPlayer.reset();
                }
                Log.e(TAG, "setDataSource()", e);
                return;
            }
            try
            {
                if (videoSurfaceFlag == 1)
                {
                    Log.e(TAG, "The videoView surface has been released");
                    Message msg = new Message();
                    msg.obj = NotifyType.SURFACERELEASE;
                    updateHandler.sendMessage(msg);
                    return;
                }
                else
                {
                    holder.setFormat(PixelFormat.RGBA_8888);
                    mediaPlayer.setDisplay(holder);
                    if (mediaPlayer.getMediaPlayer() instanceof HiMediaPlayer)
                    {
                        int xy[] = new int[2];
                        surfaceView.getLocationOnScreen(xy);
                        ((HiMediaPlayer) (mediaPlayer.getMediaPlayer())).setVideoRange(xy[0],
                                xy[1], surfaceView.getWidth(), surfaceView.getHeight());
                    }
                }
            }
            catch (IllegalStateException e)
            {
                Log.e(TAG, "setDisplay", e);
                return;
            }
            if (mIsInterrupted)
            {
                Log.e(TAG, "before prepare rrupted");
                return;
            }
            try
            {
                if (mediaPlayer != null)
                {
                    mediaPlayer.prepareAsync();
                }
            }
            catch (Exception e)
            {
                Log.e(TAG, "prepare()", e);
                return;
            }
        }
    }

    /**
     * Thread of updating playing video
     */

    /**
     * 更新播放时间的线程
     */
    class ProgressThread extends Thread
    {
        public void run()
        {
            while (!Thread.currentThread().isInterrupted())
            {
                if (mediaPlayer == null || !mediaPlayer.isPlaying())
                {
                    return;
                }
                Message msg = new Message();
                msg.obj = NotifyType.PROGRESS;
                if (mediaPlayer.getCurrentPosition() == mediaPlayer.getDuration())
                {
                    updateHandler.sendMessage(msg);
                    return;
                }
                updateHandler.sendMessage(msg);
                try
                {
                    Thread.sleep(1000);
                }
                catch (Exception e)
                {
                    Log.e(TAG, "sleep", e);
                    return;
                }
                try
                {
                    if (!mediaPlayer.isPlaying())
                    {
                        continue;
                    }
                }
                catch (IllegalStateException e)
                {
                    Log.e(TAG, "isPlaying", e);
                    return;
                }
            }
        }
    }

    /**
     * OnCompletionListener of video play
     */

    /**
     * 视频播放的onCompletionListener
     */
    class VideoPlayerCompleteAdapter extends MediaPlayerTemplate.OnCompletionAdapter
    {
        public <MediaPlayer_T> void onCompletionAdapter(MediaPlayer_T mp)
        {
            Log.d(TAG, "onCompletion()");
            // mp.reset();
            if (isErrorHappen)
            {
                isErrorHappen = false;
                return;
            }
            curTime.setText(getStringTime(sumIntTime));
            allTime.setText(getStringTime(sumIntTime));
            videoBar.setProgress(sumIntTime);
            stopNetWorkSpeedTimer();
        }
    }

    class VideoPlayerOnInfoAdapter extends MediaPlayerTemplate.OnInfoAdapter
    {
        public <MediaPlayer_T> boolean onInfoAdapter(MediaPlayer_T mp, int what, int extra)
        {
            Log.d(TAG, "onInfo.what=" + what + ",extra=" + extra);
            if (what == 1002 && extra == 0)
            { // MeidaPlayer.MEDIA_INFO_NETWORK ,extra=0 means network is down
                Log.d(TAG, "schedule to finish because network is down");
                if (networkTimer == null)
                {
                    networkTimer = new Timer();
                    networkTimer.schedule(new NetworkTimerTask(), TIMEOUT);
                }
            }
            else if (what == 1002 && extra == 4)
            { // MediaPlayer.MEDIA_INFO_NETWORK ,extra=4 means network is up
                Log.d(TAG, "cancel schedule to finish");
                if (networkTimer != null)
                {
                    networkTimer.cancel();
                    networkTimer = null;
                }
            }
            else if(HiMediaPlayer.MEDIA_INFO_PREPARE_PROGRESS == what)
            {
                Message msg = new Message();
                msg.obj = NotifyType.PREPAREPROGRESS;
                msg.what = extra;
                updateHandler.sendMessage(msg);
            }
            return true;
        }
    }

    /**
     * OnErrorListener of video play
     */

    /**
     * 视频播放的OnErrorListener
     */
    class VideoPlayerErrorAdapter extends MediaPlayerTemplate.OnErrorAdapter
    {
        public <MediaPlayer_T> boolean onErrorAdapter(MediaPlayer_T mp, int what, int extra)
        {
            Log.d(TAG, "onError(what=" + what + ",extra=" + extra + ")");
            isErrorHappen = true;
            if (!interruptVideoUnsupportShow && !isVideoClicked)
            {
                hideVideoPrepareProgress();
                showUnSupport();
            }
            stopNetWorkSpeedTimer();
            mediaPlayer.reset();
            return false;
        }
    }

    /**
     * OnPreparedListener of video play
     */
    /**
     * 视频播放的OnPreparedListener
     */
    class VideoPlayerOnPreparedAdapter extends MediaPlayerTemplate.OnPreparedAdapter
    {
        public <MediaPlayer_T> void onPreparedAdapter(MediaPlayer_T mp)
        {
            videoInfo = getString(R.string.video) + MediaInfo.getVideoFormat(mediaPlayer) + " "
                    + getString(R.string.audio) + MediaInfo.getAudioFormat(mediaPlayer) + "\n"
                    + getString(R.string.mediaSize) + formatFileSize(fileSize);
            Log.d(TAG, "video info:" + videoInfo);
            Message msg = new Message();
            msg.obj = NotifyType.VIDEOINFO;
            updateHandler.sendMessage(msg);
            Log.d(TAG, "sendMessage");
            try
            {
                mediaPlayer.start();
                progressThread = new ProgressThread();
                progressThread.start();
                videoBar.setMax(mediaPlayer.getDuration());
            }
            catch (Exception e)
            {
                Log.e(TAG, "mediaPlayer.start()", e);
            }
        }
    }

    /**
     * Thread of loading audio item, just load info, not play
     */

    /**
     * 加载音频的Thread，只加载信息，不播放
     */
    class LoadAudioThread extends Thread
    {
        private String name;
        private String url;
        private String album;
        private String artist;
        private String date;
        private String genre;
        private String albumArtURI;
        private long myLoadId;
        private boolean isInterrupt;

        public LoadAudioThread(String name, String url, String album, String artist, String date,
                String genre, String albumArtURI, long myLoadId)
        {
            this.name = name;
            this.url = url;
            this.album = album;
            this.artist = artist;
            this.date = date;
            this.genre = genre;
            this.albumArtURI = albumArtURI;
            this.myLoadId = myLoadId;
            this.isInterrupt = false;
        }

        public void run()
        {
            try
            {
                Thread.sleep(500);
            }
            catch (Exception e)
            {
                Log.e(TAG, "sleep", e);
                return;
            }
            if (myLoadId != loadId)
            {
                return;
            }
            if(this.isInterrupt)
            {
                return;
            }
            try
            {
                URL audioUrl = new URL(url);
                long size = 0;
                long oldTimeMillis = System.currentTimeMillis();
                String headerString = dmpNative.HI_DmpGetHead(url);
                if(null != headerString)
                {
                    Pattern pServ = Pattern.compile("content-length: ([0-9]*)");
                    Matcher mServ = pServ.matcher((CharSequence) headerString.toLowerCase());
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
                }
                long currentTimeMillis = System.currentTimeMillis() - oldTimeMillis;
                Log.d(TAG, "http connect used time:" + currentTimeMillis);
                Log.d(TAG, "length: " + size);
                fileName = name;
                audioInfo = getString(R.string.musicAlbum) + getFixLengthStr(album, 20) + "\n"
                        + getString(R.string.musicGenre) + getFixLengthStr(genre, 20) + "\n"
                        + getString(R.string.musicArtist) + getFixLengthStr(artist, 20) + "\n"
                        + getString(R.string.musicDate) + getFixLengthStr(date, 20) + "\n"
                        + getString(R.string.mediaSize) + formatFileSize(size);
                Message msg = new Message();
                msg.obj = NotifyType.AUDIOINFO;
                updateHandler.sendMessage(msg);
                Bitmap albumImage = getAlbumImage(albumArtURI);
                if(this.isInterrupt)
                {
                    return;
                }
                msg = new Message();
                msg.obj = albumImage;
                updateAlbumImageHandler.sendMessage(msg);
            }
            catch (MalformedURLException e)
            {
                Log.e(TAG, "url: " + url, e);
                Message msg = new Message();
                msg.obj = NotifyType.UNSUPPORT;
                updateHandler.sendMessage(msg);
            }
            catch (Exception e)
            {
                Log.e(TAG, "open connection", e);
                Message msg = new Message();
                msg.obj = NotifyType.DMSDOWN;
                updateHandler.sendMessage(msg);
            }
        }

        public void interrupt()
        {
            super.interrupt();
            this.isInterrupt = true;
        }
    }

    public boolean dispatchKeyEvent(KeyEvent event)
    {
        int keyCode = event.getKeyCode();
        int action = event.getAction();
        Log.d(TAG, "dispatchKeyEvent: " + keyCode);

        // for the loading status, keydown should return
        if (loadIcon.getVisibility() == View.VISIBLE
                && keyCode == KeyEvent.KEYCODE_BACK
                && action == KeyEvent.ACTION_DOWN)
        {
            Log.d(TAG, "gotoTop fileExplore.getLocation():" + mCurrentLocation);
            if (mCurrentLocation == Location.TOPLEVEL)
            {
                if (updateTopFileListThread != null && updateTopFileListThread.isAlive())
                {
                    Log.d(TAG, "gotoTop updateTopFileListThread.interrupt()");
                    updateTopFileListThread.interrupt();
                    updateTopFileListThread = null;
                    hideLoadIcon();
                    listView.setCanMove(true);
                    return true;
                }
            }
            else if (mCurrentLocation == Location.TOP)
            {
                if (updateTopFileListThread != null && updateTopFileListThread.isAlive())
                {
                    Log.d(TAG, "gotoTop updateTopFileListThread.interrupt()");
                    updateTopFileListThread.interrupt();
                    updateTopFileListThread = null;
                    hideLoadIcon();
                    listView.setCanMove(true);
                    return true;
                }
                if (loadDevicePageThread != null && loadDevicePageThread.isAlive())
                {
                    Log.d(TAG, "loadDevicePageThread.interrupt()");
                    loadDevicePageThread.interrupt();
                    loadDevicePageThread= null;
                    hideLoadIcon();
                    listView.setCanMove(true);
                    return true;
                }
            }
            return true;
        }

        // for the loading status, keydown should return
        if (loadIcon.getVisibility() == View.VISIBLE)
            return true;

        if (keyCode == KeyEvent.KEYCODE_BACK && action == KeyEvent.ACTION_DOWN)
        {
            Log.d(TAG, "KeyEvent.KEYCODE_BACK");
            Log.d(TAG, "location=" + fileExplore.getLocation());
            videoView.setVisibility(View.INVISIBLE);
            surfaceView.setVisibility(View.VISIBLE);
            stopNetWorkSpeedTimer();
            if (fileExplore.getExplore() == null)
            {
                Log.d(TAG, "finish()");
                this.finish();
            }
            else if (fileExplore.getLocation() == Location.TOPLEVEL)
            {
                Log.d(TAG, "updateRoot");
                updateUPnPPage();
            }
            else if (fileExplore.getLocation() == Location.TOP)
            {
                loadDevicePageThread = new UpdateDevicePageThread();
                loadDevicePageThread.start();
                canLoadTopList = true;
            }
            else
            {
                Log.d(TAG, "gotoParent");
                new UpdateParentDirThread().start();
                showLoadIcon();
            }
            return true;
        }
        return super.dispatchKeyEvent(event);
    }

    /**
     * KeyListener of ListView, is used to update next page when user presses KEYCODE_DPAD_DOWN and
     * cursor locates at bottom of ListView
     */

    /**
     * ListView的按键监听，作用是判断用户是否在光标已经到最下面一项还按遥控器上的向下键，如果是这种情况，加载下一页
     */
    class ListViewListener implements ListViewKeyListener
    {
        public void onListViewKeyDown(int keyCode, KeyEvent keyEvent)
        {
            Log.d(TAG, "key " + keyCode + " down");
            if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN)
            {
                if (canLoadTopList)
                {
                    return;
                }
                int listViewCount = listView.getCount();
                int listViewPos = listView.getSelectedItemPosition();
                if (listViewPos == listViewCount - 1)
                {
                    List<AbstractFile> lstFiles = fileExplore.getFileList();
                    if (null != lstFiles && lstFiles.size() > 0)
                    {
                        AbstractFile file = lstFiles.get(0);
                        int sum = ((DMSFile) file).getSumNumOfSubFiles();
                        Log.d(TAG, "listViewCount=" + listViewCount);
                        Log.d(TAG, "listViewPos=" + listViewPos);
                        Log.d(TAG, "sum=" + sum);
                        if (listViewCount < sum)
                        {
                            if (!loadNextPageFinish)
                            {
                                showLoadIcon();
                                return;
                            }
                            updateNextPageThread = new UpdateNextPageThread();
                            updateNextPageThread.start();
                            listPos = listViewPos + 1;
                        }
                        else
                        {
                            listPos = 0;
                            listView.setSelection(listPos);
                        }
                    }
                }
            }
        }

        public void onListViewKeyUp(int keyCode, KeyEvent keyEvent)
        {
        }

        public void onListViewKeyMultiple(int keyCode, int repeatCount, KeyEvent event)
        {
        }
    }

    /**
     * The callback of SurfaceView that shows video
     */

    /**
     * 显示视频的SurfaceView的Callback
     */
    class VideoSurfaceCallback implements SurfaceHolder.Callback
    {
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
        {
            Log.d(TAG, "video surface changed");
        }

        public void surfaceCreated(SurfaceHolder holder)
        {
            videoSurfaceFlag = 0;
            Log.d(TAG, "video surface create:" + videoSurfaceFlag);
        }

        public void surfaceDestroyed(SurfaceHolder holder)
        {
            videoSurfaceFlag = 1;
            Log.d(TAG, "video surface destroy:" + videoSurfaceFlag);
        }
    }

    /**
     * The callback of SurfaceView that shows image
     */

    /**
     * 显示图片的SurfaceView的Callback
     */
    class SurfaceCallback implements SurfaceHolder.Callback
    {
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
        {
            Log.d(TAG, "surfaceChanged");
        }

        public void surfaceCreated(SurfaceHolder holder)
        {
            Log.d(TAG, "surfaceCreate");
            if (displayingImage == null)
            {
                Log.e(TAG, "displayingImage is null");
                return;
            }
            switch (displayingImage)
            {
                case ROOT:
                    showImage(rootItem);
                    break;
                case DEVICE:
                    showImage(windowServerPic);
                    break;
                case IMAGE:
                    if (mBitmap != null && !isUnsupportShow)
                    {
                        showImage();
                    }
                    else if (isUnsupportShow)
                    {
                        showImage(unsupportedWindowImage);
                    }
                    else
                    {
                        Log.d(TAG, "unknown type image");
                    }
                    break;
                case MUSIC:
                    if (albumPic == null)
                    {
                        showMusicPic();
                    }
                    else
                    {
                        showImage(albumPic);
                    }
                    break;
                case VIDEO:
                    if (isUnsupportShow)
                    {
                        showImage(unsupportedWindowImage);
                    }
                    break;
                case FOLDER:
                    showMainPic();
                    break;
                default:
                    Log.e(TAG, "no match");
            }
            isUnsupportShow = false;
        }

        public void surfaceDestroyed(SurfaceHolder holder)
        {
            Log.d(TAG, "surfaceDestroyed");
        }
    }

    /**
     * Return whether the network is up, when the network is down, DMP Server will not be started
     */

    /**
     * 判断网络是否连通，如果不连通，则不启动DMP服务
     */
    private boolean isNetworkEnable()
    {
        if (isAPStateOn())
        {// AP is on, can start DLNA
            return true;
        }

        ConnectivityManager networkManager = (ConnectivityManager) this
                .getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo info = networkManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
        if (info != null && info.isConnected())
        {
            return true;
        }
        info = networkManager.getNetworkInfo(ConnectivityManager.TYPE_WIMAX);
        if (info == null)
        {
            // FIXME there is no defination for TYPE_ETHERNET, so use number 9
            info = networkManager.getNetworkInfo(9); // TYPE_ETHERNET = 9 for ics
        }
        if (info != null && info.isConnected())
        {
            return true;
        }
        return false;
    }

    private Boolean isAPStateOn()
    {
        WifiManager wifiManager = (WifiManager) this.getSystemService(Context.WIFI_SERVICE);
        if (wifiManager == null)
        {
            return false;
        }
        if (wifiManager.getWifiApState() == WifiManager.WIFI_AP_STATE_ENABLED)
            return true;
        else
            return false;
    }

    /**
     * Return the fixed length string
     * @param src source string
     * @param maxLen fixed length
     * @return the string after interception
     */

    /**
     * 返回固定长度的字符串
     * @src 原始字符串
     * @maxLen 固定长度
     * @return 截取后的字符串
     */
    private String getFixLengthStr(String src, int maxLen)
    {
        if (src.length() < maxLen)
        {
            return src;
        }
        else
        {
            return src.substring(0, maxLen - 3) + "...";
        }
    }

    /**
     * Format the file size
     */

    /**
     * 格式化文件大小
     */
    private String formatFileSize(long size)
    {
        DecimalFormat numFormat = new DecimalFormat("0.00");
        if (size > 1024 * 1024 * 1024)
        {
            return "" + numFormat.format(size * 1.0 / (1024 * 1024 * 1024)) + "G";
        }
        else if (size > 1024 * 1024)
        {
            return "" + numFormat.format(size * 1.0 / (1024 * 1024)) + "M";
        }
        else
        {
            return "" + numFormat.format(size * 1.0 / 1024) + "K";
        }
    }

    /**
     * wait some thread finish
     */

    /**
     * 等待这些线程结束
     */
    private void joinSomeThread()
    { // DTS2012112905757,DTS2012120200318
        try
        {
            //if (loadImageThread != null && loadImageThread.isAlive())
            //{
            //    loadImageThread.join();
            //}
            if (loadVideoThread != null && loadVideoThread.isAlive())
            {
                loadVideoThread.interruptThread();
                loadVideoThread.join();
            }
            if (loadAudioThread != null && loadAudioThread.isAlive())
            {
                loadAudioThread.join();
            }
        }
        catch (Exception e)
        {
            Log.e(TAG, "joinSomeThread", e);
        }
    }

    /**
     * interrupt some thread
     */

    /**
     * 打断部分线程
     */
    private void interruptSomeThread()
    { // DTS2012112905757,DTS2012120200318
        if (loadImageThread != null && loadImageThread.isAlive())
        {
            loadImageThread.interrupt();
        }
        loadImageThread = null;
        if (startDMPThread != null && startDMPThread.isAlive())
        {
            startDMPThread.interrupt();
        }
        startDMPThread = null;
        if (loadDevicePageThread != null && loadDevicePageThread.isAlive())
        {
            loadDevicePageThread.interrupt();
        }
        loadDevicePageThread = null;
        if (progressThread != null && progressThread.isAlive())
        {
            progressThread.interrupt();
        }
        progressThread = null;
        if (updateNextPageThread != null && updateNextPageThread.isAlive())
        {
            updateNextPageThread.interrupt();
        }
        updateNextPageThread = null;
    }

    /**
     * interrupt all thread
     */

    /**
     * 打断所有线程
     */
    private void interruptAllThread()
    {
        if (startDMPThread != null && startDMPThread.isAlive())
        {
            startDMPThread.interrupt();
        }
        startDMPThread = null;
        if (loadDevicePageThread != null && loadDevicePageThread.isAlive())
        {
            loadDevicePageThread.interrupt();
        }
        loadDevicePageThread = null;
        if (loadImageThread != null && loadImageThread.isAlive())
        {
            loadImageThread.interrupt();
        }
        loadImageThread = null;
        if (loadVideoThread != null && loadVideoThread.isAlive())
        {
            loadVideoThread.interruptThread();
            loadVideoThread.interrupt();
        }
        loadVideoThread = null;
        if (loadAudioThread != null && loadAudioThread.isAlive())
        {
            loadAudioThread.interrupt();
        }
        loadAudioThread = null;
        if (progressThread != null && progressThread.isAlive())
        {
            progressThread.interrupt();
        }
        progressThread = null;
        if (updateNextPageThread != null && updateNextPageThread.isAlive())
        {
            updateNextPageThread.interrupt();
        }
        updateNextPageThread = null;
    }

    /**
     * Listener for clicking the top level item(Network, Upnp...)
     */

    /**
     * 点击最顶层(Network, UPNP...)的监听
     */
    //class TopClickListener implements OnItemClickListener
    class UPnPPageClickListener implements OnItemClickListener
    {
        public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3)
        {
            RootItem selectedItem = fileExplore.getRootList().get(arg2);
            rootItem = selectedItem;
            switch (selectedItem)
            {
                case UPNP:
                    if (!isNetworkEnable())
                    {
                        AlertDialog dialog = new AlertDialog.Builder(MediaCenterActivity.this)
                                .setTitle(getString(R.string.networkDisable))
                                .setMessage(getString(R.string.connectNetwork))
                                .setPositiveButton(getString(R.string.quit),
                                        new DialogInterface.OnClickListener()
                                        {
                                            public void onClick(DialogInterface dialogInterface,
                                                    int i)
                                            {
                                                // MediaCenterActivity.this.finish();
                                                updateUPnPPage();
                                            }
                                        }).create();
                        dialog.setOnCancelListener(new DialogInterface.OnCancelListener()
                        {
                            public void onCancel(DialogInterface d)
                            {
                                Log.e(TAG, "AlertDialog.onCancel");
                                // MediaCenterActivity.this.finish();
                                updateUPnPPage();
                            }
                        });
                        dialog.show();
                        break;
                    }
                    else
                    {
                        if( startDMPThread != null )
                        {
                            Log.d(TAG,"DMP have been started already");
                        }
                        else
                        {
                            Log.d(TAG,"DMP enter start process");
                            startDMPThread = new StartDMPServerThread();
                            startDMPThread.start();

                            displayingImage = DisplayingImage.DEVICE;
                            fileExplore.initExplore(new UpnpExplore(MediaCenterActivity.this));
                            loadDevicePageThread = new UpdateDevicePageThread();
                            loadDevicePageThread.start();
                            canLoadTopList = true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    /**
     * Listener for selecting top category
     */

    /**
     * 顶层类别被选中的监听
     */
    //class TopSelectedListener implements OnItemSelectedListener
    class UPnPPageSelectedListener implements OnItemSelectedListener
    {

        public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3)
        {
            updateIndexView(arg2, 1); // RootItem.values().length
            RootItem selectedItem = fileExplore.getRootList().get(arg2);
            if (selectedItem != null)
            {
                showImage(selectedItem);
                deviceNameView.setText(getString(selectedItem.getNameId()));
            }
        }

        public void onNothingSelected(AdapterView<?> arg0)
        {
            showImage(RootItem.NETWORK);
        }
    }

    /**
     * hide the detail info
     */

    /**
     * 隐藏详细信息
     */
    private void hideInfo()
    {
        fileNameView.setText(getString(R.string.mediaInfo));
        infoView.setText("");
        videoBar.setVisibility(View.INVISIBLE);
        videoBar.setProgress(0);
        curTime.setVisibility(View.INVISIBLE);
        curTime.setText("0:00:00");
        allTime.setVisibility(View.INVISIBLE);
        allTime.setText("0:00:00");
    }

    /**
     * Thread contains timeout function, if one thread want to use timeout function, extends this
     * class and call parent's run method in its run method
     */

    /**
     * 超时线程，如果某个线程要用到超时，继承此类，并在run函数里调用父类的run方法
     */
    class ThreadTimeout extends Thread
    {
        private long timeout;

        public ThreadTimeout()
        {
            timeout = 8000;
            timer = new Timer();
        }

        public ThreadTimeout(long timeout)
        {
            this.timeout = timeout;
            timer = new Timer();
        }

        class TimeoutHandler extends TimerTask
        {
            public void run()
            {
                ThreadTimeout.this.interrupt();
                interruptAllThread();
                Message msg = new Message();
                msg.obj = NotifyType.TIMEOUT;
                updateHandler.sendMessage(msg);
            }
        }

        public void run()
        {
            if (timer != null)
                timer.schedule(new TimeoutHandler(), timeout);
        }

        public void cancel()
        {
            Log.d(TAG, "ThreadTimeout cancel");
            if (timer != null)
                timer.cancel();
            timer = null;
        }

        public void interrupt()
        {
            Log.d(TAG, "ThreadTimeout interrupt");
            if(null != dmpManager)
            {
                dmpManager.breakBrowse();
            }
            this.cancel();
            fileExplore.breakBrowse();
            super.interrupt();
        }
    }

    /**
     * stop background music
     */

    /**
     * 停止后台播放
     */
    private void stopBackgroundMusic()
    {
        Intent intent = new Intent();
        intent.setAction("com.android.music.musicservicecommand.pause");
        intent.putExtra("command", "pause");
        CommonDef.sendBroadcastEx(this,intent);
    }

    /**
     * get album image
     */

    /**
     * 获取专辑图片
     */
    private Bitmap getAlbumImage(String url)
    {
        Log.d(TAG, "getAlbumImage(" + url + ")");
        Bitmap bitmap = null;
        try
        {
            URL urlObj = new URL(url);
            HttpURLConnection conn = (HttpURLConnection) urlObj.openConnection();
            InputStream inputStream = conn.getInputStream();
            try
            {
                bitmap = BitmapFactory.decodeStream(inputStream);
            }
            catch (OutOfMemoryError e1)
            {
                Log.e(TAG, "getAlbumImage", e1);
            }
            conn.disconnect();
            inputStream.close();
        }
        catch (Exception e)
        {
            Log.e(TAG, "getAlbumImage", e);
        }
        return bitmap;
    }

    private void registerNetworkReceiver()
    {
        IntentFilter filter = new IntentFilter();
        filter.addAction("android.net.conn.LINK_STATE_CHANGED");
        filter.addAction("android.net.ethernet.ETHERNET_STATE_CHANGE");
        filter.addAction("android.net.ethernet.STATE_CHANGE");
        registerReceiver(mNetworkReceiver, filter);
    }

    private void unregisterNetworkReceiver()
    {
        unregisterReceiver(mNetworkReceiver);
    }

    class NetworkReceiver extends BroadcastReceiver
    {
        public void onReceive(Context context, Intent intent)
        {
            Log.d(TAG, "NetworkReceiver.onReceiver, action=" + intent.getAction());
            String action = intent.getAction();
            /*
             * for android 2.2 ConnectivityManager.ACTION_LINK_STATE_CHANGED =
             * "android.net.conn.LINK_STATE_CHANGED" public static final String EXTRA_LINK_CONNECTED
             * = "connected"; for android 4.0 EthernetManager.ETHERNET_STATE_CHANGED_ACTION =
             * "android.net.ethernet.ETHERNET_STATE_CHANGE"
             * EthernetManager.NETWORK_STATE_CHANGED_ACTION = "android.net.ethernet.STATE_CHANGE"
             * String EXTRA_ETHERNET_STATE= "ethernet_state"; public static final int
             * ETHERNET_STATE_DISABLED = 0; public static final int ETHERNET_STATE_ENABLED = 1;
             * public static final int ETHERNET_STATE_UNKNOWN = 2;
             */
            if (null != action)
            {
                if (action.equals("android.net.conn.LINK_STATE_CHANGED"))
                {
                    int linkNum = intent.getIntExtra("connected", 1);
                    if (linkNum > 1)
                    {
                        // network has at least one link
                        Log.d(TAG, "ACTION_LINK_STATE_CHANGED >1");
                    }
                    else if (!isWifiConnected())
                    {
                        // network is dislinked
                        Log.d(TAG, "ACTION_LINK_STATE_CHANGED");
                        handleNetworkInterrupt();
                    }
                }
                else if (action.equals("android.net.ethernet.ETHERNET_STATE_CHANGE")
                        || action.equals("android.net.ethernet.STATE_CHANGE"))
                {
                    if (action.equals("android.net.ethernet.ETHERNET_STATE_CHANGE"))
                    {
                        int status = intent.getIntExtra("ethernet_state", 2);
                        if (status == 0 || status == 4)
                        {// connected
                        }
                        else if (status == 1 && !isWifiConnected())
                        {// connect failed
                            Log.d(TAG, "EthernetManager: ethernet connect failed");
                            handleNetworkInterrupt();
                        }
                        else if ((status == 2 || status == 6) && !isWifiConnected())
                        {// disconnected
                            Log.d(TAG, "EthernetManager: ethernet disconnected");
                            handleNetworkInterrupt();
                        }
                        else
                        {// unknown
                        }
                    }
                    else
                    {
                        // nothing to do
                        Log.d(TAG, "EthernetManager.NETWORK_STATE_CHANGED_ACTION");
                    }
                }
            }
            else
            {
                Log.e(TAG, "get action  is null");
            }
        }
    }

    private boolean isWifiConnected()
    {
        ConnectivityManager connectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo wifiInfo = connectivityManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
        return (null != wifiInfo) ? wifiInfo.isConnected() : false;
    }

    private void handleNetworkInterrupt()
    {
        Toast.makeText(this, R.string.network_interruption, Toast.LENGTH_SHORT).show();
        if (mediaPlayer != null && mediaPlayer.isPlaying())
        {
            mediaPlayer.stop();
            mediaPlayer.reset();
            stopNetWorkSpeedTimer();
        }
    }

    class NetworkTimerTask extends TimerTask
    {
        public void run()
        {
            Message msg = new Message();
            msg.obj = NotifyType.TIMEOUT;
            updateHandler.sendMessage(msg);
            if (mediaPlayer != null)
            {// DTS2012071300148 :stop play if return to rootlist.
                mediaPlayer.reset();
            }
        }
    }

    /*
     * change IP restart DMP Manager
     */
    private String oldIPValue = null;
    private String newIPValue = null;
    Timer restartDMPManager = null;
    RestartDMPManagerTimeTask restartDMPManagerTimeTask = null;
    private NetStateChangeReceiver netStateChangeReceiver;

    private void register()
    {
        IntentFilter netStateChangeFilter = new IntentFilter();
        netStateChangeFilter.addAction("android.net.conn.CONNECTIVITY_CHANGE");
        netStateChangeReceiver = new NetStateChangeReceiver();
        registerReceiver(netStateChangeReceiver, netStateChangeFilter);
    }

    class NetStateChangeReceiver extends BroadcastReceiver
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            String action = intent.getAction();
            if ((null != action)
                    && (action.equalsIgnoreCase("android.net.conn.CONNECTIVITY_CHANGE")))
            {
                boolean networkstatus = isNetworkEnable();
                if (networkstatus == true)
                {
                    newIPValue = getHostIpAddress();
                    Log.d(TAG, "newIPValue= " + newIPValue);
                    Log.d(TAG, "oldIPValue = " + oldIPValue);
                    if (newIPValue != null && !newIPValue.equals(oldIPValue))
                    {// network IP Changed
                        Log.d(TAG, "IP Change");
                        if (oldIPValue != null)
                        {
                            Log.d(TAG, "reconnect Network,restartDMPManager");
                            restartDMPManager();
                        }
                        oldIPValue = getHostIpAddress();
                        Log.d(TAG, "oldIPValue after = " + oldIPValue);
                    }
                }
            }
        }
    }

    private String getHostIpAddress()
    {
        try
        {
            Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces();
            if (en == null)
            {
                return null;
            }
            while (en.hasMoreElements())
            {
                NetworkInterface intf = en.nextElement();
                for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr
                        .hasMoreElements();)
                {
                    InetAddress inetAddress = enumIpAddr.nextElement();
                    if (!inetAddress.isLoopbackAddress())
                    {
                        String ipaddress = String.format("%s", inetAddress.getHostAddress());
                        if (isIPAddress(ipaddress))
                        {
                            return ipaddress;
                        }
                    }
                }
            }
        }
        catch (SocketException ex)
        {
            Log.e(TAG, "getHostIpAddress()", ex);
        }
        return null;
    }

    private boolean isIPAddress(String ip)
    {
        Pattern p = Pattern
                .compile("([0-9]|[0-9]\\d|1\\d{2}|2[0-1]\\d|25[0-5])(\\.(\\d|[0-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])){3}");
        Matcher m = p.matcher(ip);
        boolean match = m.matches();
        if (!match)
        {
            return false;
        }
        return true;
    }

    private class RestartDMPManagerTimeTask extends TimerTask
    {
        @Override
        public void run()
        {
            restartDMPAction();
        }
    }

    private synchronized void restartDMPManager()
    {
        if (restartDMPManager != null)
        {
            restartDMPManager.cancel();
            restartDMPManager = null;
        }
        if (restartDMPManagerTimeTask != null)
        {
            restartDMPManagerTimeTask.cancel();
            restartDMPManagerTimeTask = null;
        }

        if (restartDMPManager == null)
        {
            restartDMPManager = new Timer();
        }

        if (restartDMPManagerTimeTask == null)
        {
            restartDMPManagerTimeTask = new RestartDMPManagerTimeTask();
        }

        if (restartDMPManager != null && restartDMPManagerTimeTask != null)
            restartDMPManager.schedule(restartDMPManagerTimeTask, 2000);
    }

    private void restartDMPAction()
    {
        boolean networkstatus = isNetworkEnable();
        if (networkstatus != true)
        {
            Log.d(TAG, "return restartDMP()");
            return;
        }
        Log.d(TAG, "do reatart DMP Action");
        interruptAllThread();
        try
        {
            Log.d(TAG, "before destroy");
            dmpManager.destroy();
            Log.d(TAG, "end destroy,start create");
            dmpManager.create(mContext);
            Log.d(TAG, "end create");
            Thread.sleep(1000);
        }
        catch (Exception e)
        {
            Log.e(TAG, "dmpManager destroy and start", e);
        }

        Message msg = new Message();
        msg.obj = NotifyType.RECONECT;
        updateHandler.sendMessage(msg);
    }

    private int getNetWorkSpeed(MediaPlayerTemplate mediaPlayer)
    {
        if (mediaPlayer == null)
        {
            return -1;
        }
        ;
        Parcel request = Parcel.obtain();
        request.writeInterfaceToken("android.media.IMediaPlayer");
        request.writeInt(HiMediaPlayerInvoke.CMD_GET_DOWNLOAD_SPEED); // CMD_GET_DOWNLOAD_SPEED 311
        Parcel reply = Parcel.obtain();
        try
        {
            mediaPlayerInvoke((MediaPlayer)mediaPlayer.getMediaPlayer(), request, reply);
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

    class UpdateNetWorkSpeedTimerTask extends TimerTask
    {
        public void run()
        {
            Message msg = updateHandler.obtainMessage(0, NotifyType.UPDATENETSPEED);
            updateHandler.sendMessage(msg);
        }
    }

    private void mediaPlayerInvoke(MediaPlayer mediaPlayer, Parcel request, Parcel reply)
            throws NoSuchMethodException, IllegalArgumentException, IllegalAccessException,
            InvocationTargetException
    {
        Class<MediaPlayer> mediaPlayerClass = MediaPlayer.class;
        Method invokeMethod = mediaPlayerClass.getMethod("invoke", Parcel.class, Parcel.class);
        invokeMethod.invoke(mediaPlayer, request, reply);
    }
}
