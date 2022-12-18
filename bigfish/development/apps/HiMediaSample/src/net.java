//target name

// add new line for test the icp-dkit

package com.HiMediaSample;


import android.app.Activity;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnBufferingUpdateListener;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnPreparedListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnVideoSizeChangedListener;
import android.media.MediaPlayer.OnInfoListener;
import android.os.Bundle;
import android.os.Parcel;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.Surface;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ListView;
import android.view.View;
import android.util.Log;
import android.app.Dialog;
import java.lang.reflect.Method;
import android.media.TimedText;
import android.media.MediaPlayer.TrackInfo;
import android.graphics.PixelFormat;

//support windows adjust
import android.view.Window;
import android.view.WindowManager;
import android.os.Parcel;
import android.view.KeyEvent;
import com.HiMediaSample.MenuListAdapter;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView;
import com.HiMediaSample.InvokeTestCase;
public class net
    extends Activity
    implements OnCompletionListener,
    OnBufferingUpdateListener,
    SurfaceHolder.Callback,
    OnPreparedListener,
    OnVideoSizeChangedListener,
    OnErrorListener,
    OnInfoListener

{
    private String LOG_TAG = "MediaPlayer";
    private String path = "";
    private String path2 = "";


    private int chCount = 0;

    private int chIndex = 0;//from first channel

    private Dialog menuDialog    = null;
    private Dialog menuDialog2    = null;
    private Dialog menuDialog3    = null;
    private MediaPlayer mMediaPlayer;

    private SurfaceView mPreview;

    private SurfaceHolder holder;
    private SurfaceView mPreview_subtitle;
    private SurfaceHolder holder_subtitle;
    private InvokeTestCase mInvokeTest;
    float volume = (float)0.0;
    private String[] menuItems;
    private String[] menuItems2;
    private String[] menuItems3;
    private MenuClickSwitch mMenuClick = null;
    private static final String STRATEGY_3D = "3DSTRATEGY";
    private static final String UA_TAG = "UA";
    private static final String REFERER_TAG = "REFERER";
    private static final String NOT_SUPPORT_BT_TAG = "NBT_SUPPORT";
    private static final String VSO_TAG = "SETVSO";

    @Override
    public void onCreate(Bundle icicle)
    {
        super.onCreate(icicle);
        //Set Full screen
        final Window win = getWindow();
        win.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
            WindowManager.LayoutParams.FLAG_FULLSCREEN);
        requestWindowFeature(Window.FEATURE_NO_TITLE);

        //Set view from ./ideoview.xml
        //otherwise R.layout.* looking for res folder
        setContentView(R.layout.net);
        mPreview = (SurfaceView) findViewById(R.id.surface_view);

        holder = mPreview.getHolder();
        holder.addCallback(this);
        holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
                //holder.setType(SurfaceHolder.SURFACE_TYPE_NORMAL);
                holder.setFormat(PixelFormat.RGBA_8888);
        //Set media controller if necessary

        mPreview_subtitle = (SurfaceView) findViewById(R.id.surface_view_subtitle);
        holder_subtitle = mPreview_subtitle.getHolder();
        //holder_subtitle.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
                holder_subtitle.setType(SurfaceHolder.SURFACE_TYPE_NORMAL);
                holder_subtitle.setFormat(PixelFormat.RGBA_8888);
        path = getIntent().getDataString();
    }
    public void onVideoSizeChanged(MediaPlayer mp, int width, int height)
    {
        Log.e(LOG_TAG, "onVideoSizeChanged called");
    }

    public boolean onError(MediaPlayer mp, int what, int extra)
    {
        switch (what)
        {
            case 1:
            {
                Log.e(LOG_TAG, "unknow error,extra data is " + extra);
                break;
            }
        }
        return true;
    }

    public boolean onInfo(MediaPlayer mp, int what, int extra)
    {
        switch (what)
        {
            case 3:
            {
                Log.e(LOG_TAG, "first frame message,time is " + extra);
                break;
            }
        }
        return true;
    }

    public void onDestroy( )
    {
        Log.e(LOG_TAG,"before set looping ==================================================>Destory");
        super.onDestroy();

        mMediaPlayer.stop();
        mMediaPlayer.release();
    }

    public void onPrepared(MediaPlayer mediaplayer)
    {
        startVideoPlayback(mediaplayer);
        TrackInfo[] mtrackInfo = mMediaPlayer.getTrackInfo();
        for(int i =0;i < mtrackInfo.length ;i++)
        {
            Log.e("TIMO","track :"+i+",type=" +mtrackInfo[i].getTrackType() );
        }

        mMediaPlayer.setOnTimedTextListener(new MediaPlayer.OnTimedTextListener() {

            @Override
            public void onTimedText(MediaPlayer mp, TimedText text) {
                int mpos;
                mpos = mMediaPlayer.getCurrentPosition();
                if(text != null) {
                    String plainText = text.getText();
                    if(plainText != null) {
                        Log.e("TIMO TimedTextTest,mpos="+mpos,",plainText: "+plainText.trim());
                    }else {
                        Log.e("TIMO TimedTextTest","plainText is null!");
                    }
                } else {
                    Log.d("TIMO TimedTextTest","TimedText is null!");
                }
            }
        });

        int textTrackIndex = findSubTrackIndex(TrackInfo.MEDIA_TRACK_TYPE_TIMEDTEXT, mtrackInfo);

        if(textTrackIndex > 0)
        {
            mMediaPlayer.selectTrack(textTrackIndex);
        }
    }

    private void startVideoPlayback(MediaPlayer mediaplayer)
    {
        holder.setFixedSize(480, 320);
        mediaplayer.start();
    }


    //@Override
    public void onCompletion(MediaPlayer arg0)
    {
        // TODO Auto-generated method stub
        Log.e(LOG_TAG, "------------------------------------------------------------------DVBPlay onCompletion");
        try
        {
            mMediaPlayer.stop();
            mMediaPlayer.reset();
            mMediaPlayer.setDataSource(path);
            Surface surface;
            if (holder_subtitle != null)
            {
                surface = holder_subtitle.getSurface();
                Log.e(LOG_TAG, "-------------TestCMD_SET_SUB_SURFACE called");
                mInvokeTest.TestCMD_SET_SUB_SURFACE(surface);
            }
            mMediaPlayer.prepareAsync();
            mMediaPlayer.setOnPreparedListener(this);

        }
        catch (Exception e)
        {
           Log.e(LOG_TAG, "error: " + e.getMessage(), e);
        }

    }
    public void surfaceCreated(SurfaceHolder holder)
    {
        Log.e(LOG_TAG, "-------------surfaceCreated called");
        try
        {

            // Create a new media player and set the listeners
            mMediaPlayer = new MediaPlayer();
            mMenuClick = new MenuClickSwitch(mMediaPlayer, this);
            mInvokeTest = new InvokeTestCase(mMediaPlayer, this);
            mMediaPlayer.setDataSource(path);
            mMediaPlayer.setDisplay(holder);
            String str3DStragegy = getIntent().getStringExtra(STRATEGY_3D);
            int n3DStrategy = 1;
            if (null != str3DStragegy)
            {
                n3DStrategy = Integer.parseInt(str3DStragegy);
                Log.e(LOG_TAG, "get 3d strategy " + n3DStrategy);
            }
            mInvokeTest.TestSet3DStrategy(n3DStrategy);

            String strNBTSupport = getIntent().getStringExtra(NOT_SUPPORT_BT_TAG);
            int mNBTSupport = 0;
            if(null != strNBTSupport)
            {
                mNBTSupport = Integer.parseInt(getIntent().getStringExtra(NOT_SUPPORT_BT_TAG));
                if(1 == mNBTSupport)
                    mInvokeTest.TestSetNotSupportByteRange();
            }
            Log.e(LOG_TAG, "mNBTSupport IS " + mNBTSupport);

            String mstrUA = getIntent().getStringExtra(UA_TAG);
            if(null != mstrUA)
            {
                mInvokeTest.TestSetUserAgent(mstrUA);
            }
            Log.e(LOG_TAG, "UA IS " + mstrUA);

            String mstrRefer = getIntent().getStringExtra(REFERER_TAG);
            if(null != mstrRefer)
            {
                mInvokeTest.TestSetReferer(mstrRefer);
            }
            Log.e(LOG_TAG, "REFERER IS " + mstrRefer);

            String strVSO = getIntent().getStringExtra(VSO_TAG);
            if(null != strVSO)
            {
                mInvokeTest.TestSetVideoSurfaceOutput();
            }
            Log.e(LOG_TAG, "Video Surface out IS " + strVSO);

            Surface surface;
            if (holder_subtitle != null)
            {
                surface = holder_subtitle.getSurface();
                Log.e(LOG_TAG, "-------------TestCMD_SET_SUB_SURFACE called");
                mInvokeTest.TestCMD_SET_SUB_SURFACE(surface);
            }

            mMediaPlayer.prepareAsync();
            mMediaPlayer.setOnBufferingUpdateListener(this);
            mMediaPlayer.setOnInfoListener(this);
            mMediaPlayer.setOnErrorListener(this);
            mMediaPlayer.setOnCompletionListener(this);
            mMediaPlayer.setOnPreparedListener(this);
            mMediaPlayer.setOnVideoSizeChangedListener(this);
            mMediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);

        }
        catch (Exception e)
        {
            Log.e(LOG_TAG, "error: " + e.getMessage(), e);
        }
    }

    private int findSubTrackIndex(int mediaTrackType, TrackInfo[] trackInfo) {
        int index = -1;
        for (int i = 0; i < trackInfo.length; i++) {
            if (trackInfo[i].getTrackType() == mediaTrackType) {
                return i;
            }
        }
        return index;
    }

    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
    {
        // TODO Auto-generated method stub

    }

    /**
     * @param holder
     * @author  h63590
     */
    public void surfaceDestroyed(SurfaceHolder holder)
    {
        // TODO Auto-generated method stub

    }
    public void onBufferingUpdate(MediaPlayer arg0, int percent)
    {
        Log.e(LOG_TAG, "onBufferingUpdate percent:" + percent);

    }
    private final static String IMEDIA_PLAYER = "android.media.IMediaPlayer";
     @Override
        public boolean onKeyDown(int keyCode, KeyEvent event) {
                Log.e(LOG_TAG, "onKeyDown======== " + keyCode);
            switch (keyCode) {
                case KeyEvent.KEYCODE_1://Middle mouse_key
                    popUpMenuDialog();
                    break;
                case KeyEvent.KEYCODE_2:
                    popUpMenuDialog2();
                    break;
                case KeyEvent.KEYCODE_3:
                    popUpMenuDialog3();
                break;
                case KeyEvent.KEYCODE_DPAD_UP://key_up
                    volume+=0.1;
                    if(volume>=1.0) volume=(float)1.0;

                    mMediaPlayer.setVolume(volume,volume);
                    break;
                //case KeyEvent.KEYCODE_BACK: //Mouse_Right
                //case KeyEvent.KEYCODE_DPAD_UP://key_up
                case KeyEvent.KEYCODE_DPAD_DOWN://Key_down
                    volume-=0.1;
                    if(volume<=0.0) volume=(float)0.0;
                    mMediaPlayer.setVolume(volume,volume);

                    break;

                //case KeyEvent.KEYCODE_DPAD_LEFT://key_left
                //case KeyEvent.KEYCODE_DPAD_RIGHT://key_right
                //case KeyEvent.KEYCODE_ENTER://key_center
                default:
                    break;
            }

            return super.onKeyDown(keyCode, event);
        }

    private OnItemClickListener itemClickListener = new OnItemClickListener()
    {
        public void onItemClick(AdapterView < ? > arg0, View arg1, int position,
                                long arg3)
        {
            mMenuClick.MenuClickPerform(position);
        }
    };

    private OnItemClickListener itemClickListener2 = new OnItemClickListener()
    {
        public void onItemClick(AdapterView < ? > arg0, View arg1, int position,
                                long arg3)
        {
            mMenuClick.MenuClickPerform2(position);

            Log.e(LOG_TAG, "invoke cmd: " + position);
            if(position == 10) //CMD_GET_VIDEO_FREEZE_MODE
            {
                try
                {
                    mMediaPlayer.stop(); //show video frezze
                    mMediaPlayer.reset();
                    mMediaPlayer.setDataSource(path);
                    mMediaPlayer.prepareAsync();
                }
                catch (Exception e)
                {
                    Log.e(LOG_TAG, "error: " + e.getMessage(), e);
                }
            }
        }
    };

    private OnItemClickListener itemClickListener3 = new OnItemClickListener()
    {
        public void onItemClick(AdapterView < ? > arg0, View arg1, int position,
                                long arg3)
        {
            mMenuClick.MenuClickPerform3(position);

        }
    };

    private void popUpMenuDialog()
    {
        menuItems = getResources().getStringArray(R.array.Test_Invoke_1);
        ListView menuList = new ListView(this);
        menuList.setAdapter(new MenuListAdapter(this, menuItems, 0, 9, true,0));
        menuList.setOnItemClickListener(itemClickListener);
        menuList.setBackgroundResource(R.drawable.dialog_background_selector);
        menuList.setSelector(getResources().getDrawable(R.drawable.item_background_selector));
        menuDialog = getDefaultSettingDialog(R.string.video_control_menu,menuList);
        setDialogWidth(menuDialog, 1280, 0, -120);
        menuDialog.show();
    }

    private void popUpMenuDialog2()
    {
        menuItems2 = getResources().getStringArray(R.array.Test_Invoke_2);
        ListView menuList = new ListView(this);
        menuList.setAdapter(new MenuListAdapter(this, menuItems2, 0, 9, true,0));
        menuList.setOnItemClickListener(itemClickListener2);
        menuList.setBackgroundResource(R.drawable.dialog_background_selector);
        menuList.setSelector(getResources().getDrawable(R.drawable.item_background_selector));
        menuDialog2 = getDefaultSettingDialog(R.string.video_control_menu, menuList);
        setDialogWidth(menuDialog2, 1280, 0, -120);
        menuDialog2.show();
    }

    private void popUpMenuDialog3()
    {
        menuItems3 = getResources().getStringArray(R.array.Test_Invoke_3);
        ListView menuList = new ListView(this);
        menuList.setAdapter(new MenuListAdapter(this, menuItems3, 0, 9, true,0));
        menuList.setOnItemClickListener(itemClickListener3);
        menuList.setBackgroundResource(R.drawable.dialog_background_selector);
        menuList.setSelector(getResources().getDrawable(R.drawable.item_background_selector));
        menuDialog3 = getDefaultSettingDialog(R.string.video_control_menu,menuList);
        setDialogWidth(menuDialog3, 1280, 0, -120);
        menuDialog3.show();
    }

    private Dialog getDefaultSettingDialog(int pTitleId, View pView)
    {
        Dialog _Dialog = new Dialog(this, R.style.styleDialog);
        if(pTitleId != -1)
            _Dialog.setTitle(pTitleId);
        _Dialog.setContentView(pView);

        return _Dialog;
    }

    private void setDialogWidth(Dialog dialog, int screenWidth, int x, int y)
    {
        WindowManager.LayoutParams params = dialog.getWindow().getAttributes();
        if(screenWidth == 640)
        {
            params.width = screenWidth / 2;
            params.x = x-150;
            params.y = y;
        }
        else if(screenWidth == 960)
        {
            params.width = screenWidth / 2;
            params.x = x+150;
            params.y = y-60;
        }
        dialog.getWindow().setAttributes(params);
    }
}
