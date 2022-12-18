package com.hisilicon.android.gallery3d.app;

import java.io.File;
import java.lang.reflect.Constructor;
import java.util.ArrayList;
import java.util.Random;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Button;
import android.widget.PopupWindow;
import android.widget.Spinner;
import android.widget.TextView;

import com.hisilicon.android.ALog;
import com.hisilicon.android.HiAnimation;
import com.hisilicon.android.HiCenterAnimation;
import com.hisilicon.android.HiImageView;
import com.hisilicon.android.HiInAnimation;
import com.hisilicon.android.HiRotateAnimation;
import com.hisilicon.android.HiShutterAnimation;
import com.hisilicon.android.HiTransAnimation;
import com.hisilicon.android.HiTurnPageAnimation;
import com.hisilicon.android.gallery3d.R;
import com.hisilicon.android.gallery3d.common.Utils;
import com.hisilicon.android.gallery3d.data.ContentListener;
import com.hisilicon.android.gallery3d.data.MediaItem;
import com.hisilicon.android.gallery3d.data.MediaObject;
import com.hisilicon.android.gallery3d.data.MediaSet;
import com.hisilicon.android.gallery3d.data.Path;
import com.hisilicon.android.gallery3d.list.ImageFileListService;
import com.hisilicon.android.gallery3d.list.MusicModel;
import com.hisilicon.android.gallery3d.ui.Texture;
import com.hisilicon.android.gallery3d.util.Future;
import com.hisilicon.android.gallery3d.util.FutureListener;
import com.hisilicon.android.gallery3d.util.Log;
import com.hisilicon.android.gallery3d.app.HiAnimationAdapter;

public class HiAnimationActivity extends AbstractGalleryActivity implements AnimationListener{
    /** Called when the activity is first created. */
    private String TAG = "HiAnimationActivity";
    public static final String KEY_SET_PATH = "media-set-path";
    public static final String KEY_ITEM_PATH = "media-item-path";
    public static final String KEY_PHOTO_INDEX = "photo-index";
    public static final String KEY_RANDOM_ORDER = "random-order";
    public static final String KEY_REPEAT = "repeat";

    private  static final int  ANIMATION_TIME = 5000; // 3 seconds
    private int ANIMATION_ACTION = 0;
    private int SHOW_TIME = 5000;//5 seconds
    private int index = 0;
    private static final int MSG_LOAD_NEXT_BITMAP = 1;
    private static final int MSG_SHOW_PENDING_BITMAP = 2;
    private static final int SHOW_POPWIND = 3;
    private boolean fromMusic = false;
    public static interface Model {
        public void pause();

        public void resume();

        public Future<Slide> nextSlide(FutureListener<Slide> listener);
    }

    public static class Slide {
        public Bitmap bitmap;
        public MediaItem item;
        public int index;

        public Slide(MediaItem item, int index, Bitmap bitmap) {
            this.bitmap = bitmap;
            this.item = item;
            this.index = index;
        }
    }
    private Handler mHandler;
    private Model mModel;
    private Slide mPendingSlide = null;
    private Slide mNextSlide = null;
    private boolean mIsActive = false;
    private GalleryContext mActivity = null;
    private HiImageView aView = null;
    private PopupWindow mPopwind = null;
    public  ImageFileListService mediaFileListService = null;
    public String mSrc_path = null;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        aView = new HiImageView(this);
        getWindow().setFlags(
                WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(aView);
        mActivity = (GalleryContext) getAndroidContext();
        mHandler = new Handler() {
        @Override
            public void handleMessage(Message message) {
                switch (message.what) {
                    case MSG_SHOW_PENDING_BITMAP:
                        showPendingBitmap();
                        break;
                    case MSG_LOAD_NEXT_BITMAP:
                        loadNextBitmap();
                        break;
                    case SHOW_POPWIND:
        ShowPop();
        break;
                    default: throw new AssertionError();
                }
            }
        };
        mediaFileListService = GalleryAppImpl.mediaFileListService;
        Bundle date = getIntent().getExtras();
        fromMusic = getIntent().getBooleanExtra("fromMusic",false);
        initializeData(date);
        InitPopWindow(this);
        mSrc_path = mediaFileListService.getCurrPath();
        Log.d(TAG, "current path="+mSrc_path);
    }

    private void initializeData(Bundle data) {
        boolean random = data.getBoolean(KEY_RANDOM_ORDER, false);
        String mediaPath = data.getString(KEY_SET_PATH);
        Log.d(TAG, "mediaPath= "+mediaPath);
        mediaPath = FilterUtils.newFilterPath(mediaPath, FilterUtils.FILTER_IMAGE_ONLY);
        MediaSet mediaSet = getGalleryApplication().getDataManager().getMediaSet(mediaPath);
        if (random) {
            boolean repeat = data.getBoolean(KEY_REPEAT);
            mModel = new HiAnimationAdapter(mActivity, new ShuffleSource(mediaSet, repeat), 0, null);
        } else {
            int index = data.getInt(KEY_PHOTO_INDEX);
            String itemPath = data.getString(KEY_ITEM_PATH);
            Path path = itemPath != null ? Path.fromString(itemPath) : null;
            boolean repeat = data.getBoolean(KEY_REPEAT);
            mModel = new HiAnimationAdapter(mActivity, new SequentialSource(mediaSet,repeat),index, path);
        }
    }
    private void showPendingBitmap() {
        Slide slide = mPendingSlide;
        if (slide == null) {
            if (mIsActive) {
               finish();
            }
            return;
        }
        if(mNextSlide==null){
        mNextSlide = slide;
        aView.setImageBitmap(mNextSlide.bitmap);
        mHandler.sendEmptyMessage(MSG_LOAD_NEXT_BITMAP);
        }else{
                aView.startAnimation(getAnimation());
        mNextSlide = mPendingSlide;
        }
    }
    private HiAnimation getAnimation(){
        HiAnimation animation = null;
        if(ANIMATION_ACTION==0){
        String className[] = {"HiTurnPageAnimation", "HiRotateAnimation", "HiShutterAnimation",  "HiInAnimation", "HiTransAnimation", "HiCenterAnimation"};
            try{
                String classname = "com.hisilicon.android."+className[index%className.length];
                ALog.e(TAG, "1 do animation "+classname);
                Class<?> aniClass = Class.forName(classname);
                Constructor<?> aniCons = aniClass.getConstructor(Bitmap.class, Bitmap.class);
                animation = (HiAnimation)aniCons.newInstance(mNextSlide.bitmap, mPendingSlide.bitmap);
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
            if(index<Integer.MAX_VALUE -1){
        index++;
            }else{
        index=0;
            }

        }else{
        switch (ANIMATION_ACTION) {
        case 1://trun page
        try {
        animation = (HiAnimation)new HiTurnPageAnimation(mNextSlide.bitmap,mPendingSlide.bitmap);
        } catch (Exception e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
        }
        break;
        case 2://shutter
        try {
        animation = (HiAnimation)new HiShutterAnimation(mNextSlide.bitmap,mPendingSlide.bitmap);
        } catch (Exception e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
        }
        break;
        case 3://alpha
        try {
        animation = (HiAnimation)new HiTransAnimation(mNextSlide.bitmap,mPendingSlide.bitmap);
        } catch (Exception e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
        }
        break;
        case 4://center
        try {
        animation = (HiAnimation)new HiCenterAnimation(mNextSlide.bitmap,mPendingSlide.bitmap);
        } catch (Exception e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
        }
        break;
        case 5://silde
        try {
        animation = (HiAnimation)new HiInAnimation(mNextSlide.bitmap,mPendingSlide.bitmap);
        } catch (Exception e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
        }
        break;
        case 6://Rotate
        try {
        animation = (HiAnimation)new HiRotateAnimation(mNextSlide.bitmap,mPendingSlide.bitmap);
        } catch (Exception e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
        }
        break;
        default:
        break;
        }
        }
        animation.setAnimationListener(this);
        animation.setDuration(ANIMATION_TIME);
        return animation;
    }
    private void loadNextBitmap() {
        Log.d(TAG, "loadNextBitmap()");
        mModel.nextSlide(new FutureListener<Slide>() {
            public void onFutureDone(Future<Slide> future) {
                mPendingSlide = future.get();
                mHandler.sendEmptyMessage(MSG_SHOW_PENDING_BITMAP);
            }
        });
    }
    private static MediaItem findMediaItem(MediaSet mediaSet, int index) {
        for (int i = 0, n = mediaSet.getSubMediaSetCount(); i < n; ++i) {
            MediaSet subset = mediaSet.getSubMediaSet(i);
            int count = subset.getTotalMediaItemCount();
            if (index < count) {
                return findMediaItem(subset, index);
            }
            index -= count;
        }
        ArrayList<MediaItem> list = mediaSet.getMediaItem(index, 1);
        return list.isEmpty() ? null : list.get(0);
    }
    private static class ShuffleSource implements HiAnimationAdapter.ShowSource {
        private static final int RETRY_COUNT = 5;
        private final MediaSet mMediaSet;
        private final Random mRandom = new Random();
        private int mOrder[] = new int[0];
        private final boolean mRepeat;
        private long mSourceVersion = MediaSet.INVALID_DATA_VERSION;
        private int mLastIndex = -1;

        public ShuffleSource(MediaSet mediaSet, boolean repeat) {
            mMediaSet = Utils.checkNotNull(mediaSet);
            mRepeat = repeat;
        }

        public int findItemIndex(Path path, int hint) {
            return hint;
        }

        public MediaItem getMediaItem(int index) {
            if (!mRepeat && index >= mOrder.length) return null;
            if (mOrder.length == 0) return null;
            mLastIndex = mOrder[index % mOrder.length];
            MediaItem item = findMediaItem(mMediaSet, mLastIndex);
            for (int i = 0; i < RETRY_COUNT && item == null; ++i) {
                 mLastIndex = mRandom.nextInt(mOrder.length);
                item = findMediaItem(mMediaSet, mLastIndex);
            }
            return item;
        }

        public long reload() {
            long version = mMediaSet.reload();
            if (version != mSourceVersion) {
                mSourceVersion = version;
                int count = mMediaSet.getTotalMediaItemCount();
                if (count != mOrder.length) generateOrderArray(count);
            }
            return version;
        }

        private void generateOrderArray(int totalCount) {
            if (mOrder.length != totalCount) {
                mOrder = new int[totalCount];
                for (int i = 0; i < totalCount; ++i) {
                    mOrder[i] = i;
                }
            }
            for (int i = totalCount - 1; i > 0; --i) {
                Utils.swap(mOrder, i, mRandom.nextInt(i + 1));
            }
            if (mOrder[0] == mLastIndex && totalCount > 1) {
                Utils.swap(mOrder, 0, mRandom.nextInt(totalCount - 1) + 1);
            }
        }

        public void addContentListener(ContentListener listener) {
            mMediaSet.addContentListener(listener);
        }

        public void removeContentListener(ContentListener listener) {
            mMediaSet.removeContentListener(listener);
        }
    }
    private static class SequentialSource implements HiAnimationAdapter.ShowSource {
        private static final int DATA_SIZE = 32;

        private ArrayList<MediaItem> mData = new ArrayList<MediaItem>();
        private int mDataStart = 0;
        private long mDataVersion = MediaObject.INVALID_DATA_VERSION;
        private final MediaSet mMediaSet;
        private final boolean mRepeat;

        public SequentialSource(MediaSet mediaSet, boolean repeat) {
            mMediaSet = mediaSet;
            mRepeat = repeat;
        }

        public int findItemIndex(Path path, int hint) {
            return mMediaSet.getIndexOfItem(path, hint);
        }

        public MediaItem getMediaItem(int index) {
            int dataEnd = mDataStart + mData.size();

            if (mRepeat) {
                int count = mMediaSet.getMediaItemCount();
                if (count == 0) return null;
                index = index % count;
            }
            if (index < mDataStart || index >= dataEnd) {
                mData = mMediaSet.getMediaItem(index, DATA_SIZE);
                mDataStart = index;
                dataEnd = index + mData.size();
            }

            return (index < mDataStart || index >= dataEnd) ? null : mData.get(index - mDataStart);
        }

        public long reload() {
            long version = mMediaSet.reload();
            if (version != mDataVersion) {
                mDataVersion = version;
                mData.clear();
            }
            return mDataVersion;
        }

        public void addContentListener(ContentListener listener) {
            mMediaSet.addContentListener(listener);
        }

        public void removeContentListener(ContentListener listener) {
            mMediaSet.removeContentListener(listener);
        }
    }
    public void onAnimationEnd(Animation animation) {
        mHandler.sendEmptyMessageDelayed(MSG_LOAD_NEXT_BITMAP,SHOW_TIME);
    }

    public void onAnimationRepeat(Animation animation) {
    }

    public void onAnimationStart(Animation animation) {
    }
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if(keyCode==KeyEvent.KEYCODE_MENU&&event.getAction()==KeyEvent.ACTION_DOWN){
        ShowPop();
        return true;
        }
        return super.onKeyDown(keyCode, event);
    }
    @Override
    protected void onResume() {
        super.onResume();
         Log.d(TAG, "onResume()");
         mIsActive = true;
         mModel.resume();

         if (mPendingSlide != null) {
             showPendingBitmap();
         } else {
            loadNextBitmap();
         }
    }
    @Override
    protected void onPause() {
        super.onPause();
        mIsActive = false;
        mModel.pause();
        mHandler.removeMessages(MSG_LOAD_NEXT_BITMAP);
        mHandler.removeMessages(MSG_SHOW_PENDING_BITMAP);
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
    private void InitPopWindow(Context context){
        Spinner animation = null;
        Spinner duration = null;
        Button music_bn = null;
        TextView music_tx = null;
        LayoutInflater inflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View root = inflater.inflate(R.layout.animation_set, null);
        animation = (Spinner)root.findViewById(R.id.anmation_spinner);
        duration = (Spinner)root.findViewById(R.id.duration_spinner);
        music_bn = (Button)root.findViewById(R.id.music_selete);
        music_tx = (TextView)root.findViewById(R.id.music_text);
        if(fromMusic){
        music_bn.setVisibility(View.GONE);
        music_tx.setVisibility(View.GONE);
        }
        duration.setSelection(2);//5000sec
        animation.setOnItemSelectedListener(new OnItemSelectedListener() {
        @Override
        public void onItemSelected(AdapterView<?> arg0, View arg1,
        int arg2, long arg3) {
        ANIMATION_ACTION = arg2;
        }

        @Override
        public void onNothingSelected(AdapterView<?> arg0) {
        // TODO Auto-generated method stub

        }
        });
        duration.setOnItemSelectedListener(new OnItemSelectedListener() {
        @Override
        public void onItemSelected(AdapterView<?> arg0, View arg1,
        int arg2, long arg3) {
        SHOW_TIME = (arg2+3)*1000;
        }
        @Override
        public void onNothingSelected(AdapterView<?> arg0) {

        }
        });
        music_bn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				int index = mSrc_path.lastIndexOf("/");
				String path = mSrc_path.substring(0, index);
				Intent intent = new Intent();
				intent.setClass(HiAnimationActivity.this,FileListAcvitity.class);
				intent.putExtra("path", path);
				startActivityForResult(intent,0);
				mPopwind.dismiss();
			}
		});
        mPopwind = new PopupWindow(root, 340, 380, true);
        mPopwind.setBackgroundDrawable(new BitmapDrawable());
    }
    private void ShowPop(){
        if(mPopwind!=null){
        if(mPopwind.isShowing()){
        mPopwind.dismiss();
        }else{
        mPopwind.showAtLocation(aView, Gravity.CENTER, 0, 0);
        }
        }
    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode==0&&data!=null){
            String path = data.getStringExtra("subPath");
            Log.d(TAG, "get onActivityResult ="+path);
            Intent service = new Intent(mActivity.getAndroidContext(),BackgroundMusicService.class);
            stopService(service);
            newInitMusicList(path);
        }else{
             Log.d(TAG, "get onActivityResult null");
        }
    }
    private void newInitMusicList(String path){
        MusicModel musicModel = null;
        mediaFileListService.getMusicList().clear();
        int musicIdIndex = 0;
        int newindex = 0;
        File indexfile = new File(path);
        File fileMusicDir = new File(path).getParentFile();
        if (fileMusicDir != null && fileMusicDir.exists()
                && fileMusicDir.isDirectory()) {
            File[] fileMusics = fileMusicDir.listFiles();
            for (int j = 0; j < fileMusics.length; j++) {
                    if (fileMusics[j].isFile()) {
                        String filename = fileMusics[j].getName();
                        String dex = filename.substring(
                                filename.lastIndexOf(".") + 1,
                                filename.length());
                        dex = dex.toUpperCase();
                        SharedPreferences musicShare = getSharedPreferences(
                                "AUDIO", Context.MODE_WORLD_READABLE);
                        String musicSuffix = musicShare.getString(dex, "");
                        if (!musicSuffix.equals("")) {
                            Log.d(TAG, "musicfilename=" + filename);
                            musicModel = new MusicModel();
                            musicModel.setPath(fileMusics[j].getPath());
                            musicModel.setTitle(filename);
                            musicModel.setSize(fileMusics[j].length());
                            musicModel.setAddedTime(fileMusics[j]
                                    .lastModified());
                            musicModel.setId(musicIdIndex);
                            if(filename.equals(indexfile.getName())){
                                Log.d(TAG, "find out=" + filename+musicIdIndex);
                                newindex = musicIdIndex;
                            }
                            musicIdIndex++;
                            mediaFileListService.getMusicList().add(musicModel);
                    }
                }
            }
        }
        Intent service = new Intent(mActivity.getAndroidContext(),
	             BackgroundMusicService.class);
        service.putExtra("music_index", newindex);
        startService(service);
    }
}
