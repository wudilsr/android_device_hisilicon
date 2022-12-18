package com.hisilicon.dlna.dmc.gui.activity;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import org.teleal.cling.model.message.UpnpResponse;
import org.teleal.cling.model.meta.Action;
import org.teleal.cling.model.meta.Device;

import android.app.Activity;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v4.view.ViewPager.OnPageChangeListener;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationUtils;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.gui.browse.files.MyImageView;
import com.hisilicon.dlna.dmc.gui.browse.files.NativeImageLoader;
import com.hisilicon.dlna.dmc.gui.customview.DMSBrowseView;
import com.hisilicon.dlna.dmc.gui.customview.NowPlayingImageControlView;
import com.hisilicon.dlna.dmc.gui.customview.TouchImageView;
import com.hisilicon.dlna.dmc.processor.impl.LocalDMRProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.RemoteDMRProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor.DMRProcessorListener;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.ChangeMode;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.PlaylistListener;
import com.hisilicon.dlna.dmc.processor.interfaces.SwipeCallback;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.utility.Cache;
import com.hisilicon.dlna.dmc.utility.MyException;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.R;

public class PlayingImageActivity extends Activity {
	private Activity activity;
	private NowPlayingImageControlView m_rendererControl;
	private TextView m_viewFlipper;
	private TouchImageView m_image;
	private FrameLayout m_content;
	private ViewPager image_ViewPager;
	private RelativeLayout rc_playing_top;
	private View device_not_found_layout;
	private SwipeDetector m_swipeDetector;
	private volatile boolean isStop = false;
	private AsyncTask<PlaylistItem, Void, Bitmap> m_loadingImageTask;
	private Handler myHandler = new Handler();

	private ThumbnailGenerator thumbGenerator = ThumbnailGenerator.getInstance();
	private Cache cache = null;
	private PlaylistItem currentItem;
	private List<ImageView> views;
	private int currentViewPagerIndex;
	private boolean isLoadingbusy = false;
	private boolean isLongClick = false;
	private Toast mToast = null;
	private boolean stopLoading = false;
	private boolean isFirst = true;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		activity = this;
		isLongClick = getIntent().getBooleanExtra(DMSBrowseView.LONGCLICK, false);
		thumbGenerator.restore();
		mToast = new Toast(this.getApplicationContext());
		cache = new Cache(6);
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_playingimage);
		initializeComponents();
	}

	public void initializeComponents() {
		m_rendererControl = (NowPlayingImageControlView) findViewById(R.id.rendererControlView);
		m_swipeDetector = new SwipeDetector(new SwipeCallbackImpl());

		m_content = (FrameLayout) findViewById(R.id.rc_content);
		rc_playing_top = (RelativeLayout) findViewById(R.id.rc_playing_top);
		device_not_found_layout = findViewById(R.id.device_not_found_layout);

		m_image = (TouchImageView) findViewById(R.id.image);
		m_image.setDrawingCacheEnabled(false);
		m_image.setMaxZoom(4f);
		m_image.setOnTouchListener(m_swipeDetector);
		m_image.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				toggleItemInfo();
			}
		});

		views = new ArrayList<ImageView>();
		image_ViewPager = (ViewPager) findViewById(R.id.image_ViewPager);
//		ImageView view1 = (ImageView) getLayoutInflater().inflate(R.layout.rc_touchimage, null);
//		ImageView view2 = (ImageView) getLayoutInflater().inflate(R.layout.rc_touchimage, null);
//		ImageView view3 = (ImageView) getLayoutInflater().inflate(R.layout.rc_touchimage, null);

		MyImageView view1 = (MyImageView) getLayoutInflater().inflate(R.layout.rc_touchimage, null);
		MyImageView view2 = (MyImageView) getLayoutInflater().inflate(R.layout.rc_touchimage, null);
		MyImageView view3 = (MyImageView) getLayoutInflater().inflate(R.layout.rc_touchimage, null);
		views.add(view1);
		views.add(view2);
		views.add(view3);

		currentViewPagerIndex = getPlaylistCurrentIndex();

		image_ViewPager.setAdapter(new ViewPagerAdapter());
		image_ViewPager.setCurrentItem(currentViewPagerIndex);
		image_ViewPager.setOnPageChangeListener(new ViewPageChangeListener());
		image_ViewPager.setOnTouchListener(new OnTouchListener() {
			private int MIN_DISTANCE = 100;
			private final int DOWN_TIME = 700;
			private float downX, upX;
			@Override
			public boolean onTouch(View arg0, MotionEvent event) {
				switch (event.getAction()) {
				case MotionEvent.ACTION_DOWN: {
					downX = event.getX();
					break;
				}
				case MotionEvent.ACTION_UP:
					upX = event.getX();
					float deltaX = downX - upX;
					if (event.getEventTime() - event.getDownTime() < DOWN_TIME) {

						if (Math.abs(deltaX) < MIN_DISTANCE) {
							toggleItemInfo();
							if (m_rendererControl != null)
								m_rendererControl.onTab(downLoad);
						}
					}
					break;
				}
				return false;
			}
		});

		m_viewFlipper = (TextView) findViewById(R.id.viewFlipper);

		updateItemInfo();
	}

	class ViewPagerAdapter extends PagerAdapter{

		@Override
		public void destroyItem(ViewGroup container, int position, Object object) {
		}


		@Override
		public Object instantiateItem(ViewGroup container, int position) {
			container.removeView(getViewPagerAbsoluteView(position));
			container.addView(getViewPagerAbsoluteView(position));

			return getViewPagerAbsoluteView(position);  
		}


		@Override
		public int getCount() {
			PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
			if (playlistProcessor == null)
				return 0;
			return playlistProcessor.getSize();
		}

		@Override
		public boolean isViewFromObject(View arg0, Object arg1) {
			return arg0 == arg1;
		}
	}

	class ViewPageChangeListener implements OnPageChangeListener {

		@Override
		public void onPageScrollStateChanged(int state) {

		}

		@Override
		public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {
		}

		@Override
		public void onPageSelected(int position) {
			PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
			if (playlistProcessor != null)
			{

				int temp = currentViewPagerIndex;
				currentViewPagerIndex = position;

				if (getViewPageAbsoluteIndex(temp + 1) == getViewPageAbsoluteIndex(position))
				{
					int nextItem = getPlaylistNextIndex();

					playlistProcessor.setCurrentItem(nextItem);
				}
				else
				{
					int prevItem = getPlaylistPreIndex();

					playlistProcessor.setCurrentItem(prevItem);
				}
			}

			m_rendererControl.onGoneThumb();
		}
	}

	private ImageView getViewPagerAbsoluteView(int position ) {
		int absoluteIndex = getViewPageAbsoluteIndex(position);
		return (ImageView) views.get(absoluteIndex);
	}

	private int getViewPageAbsoluteIndex(int position) {
		return (views.size() + position) % views.size();
	}

	private int getPlaylistCurrentIndex() {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();

		if (playlistProcessor == null)
			return 0;

		int itemIndex = playlistProcessor.getCurrentItemIndex();

		return itemIndex;
	}

	private int getPlaylistNextIndex() {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();

		if (playlistProcessor == null)
			return 0;

		int size = playlistProcessor.getSize();
		int itemIndex = playlistProcessor.getCurrentItemIndex();

		if (itemIndex + 1 > size - 1)
			return 0;

		return itemIndex + 1;
	}

	private int getPlaylistPreIndex() {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();

		if (playlistProcessor == null)
			return 0;

		int size = playlistProcessor.getSize();
		int itemIndex = playlistProcessor.getCurrentItemIndex();

		if (itemIndex - 1 < 0)
			return size - 1;

		return itemIndex - 1;
	}

	private void loadNextItem() {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (playlistProcessor == null)
			return;

		ImageView nextView = getViewPagerAbsoluteView(currentViewPagerIndex + 1);

		PlaylistItem nextItem = playlistProcessor.getItemAt(getPlaylistNextIndex());

		loadImage(nextView, nextItem);
	}

	private void loadPreItem() {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (playlistProcessor == null)
			return;

		ImageView preView = getViewPagerAbsoluteView(currentViewPagerIndex - 1);

		PlaylistItem prevItem = playlistProcessor.getItemAt(getPlaylistPreIndex());

		loadImage(preView, prevItem);
	}

	public void showWarnLayout() {
		if (device_not_found_layout == null)
			return;
		Animation animation = AnimationUtils.loadAnimation(activity, R.anim.up_slidein);
		animation.setAnimationListener(new AnimationListener() {

			@Override
			public void onAnimationStart(Animation animation) {
			}

			@Override
			public void onAnimationRepeat(Animation animation) {
			}

			@Override
			public void onAnimationEnd(Animation animation) {
				device_not_found_layout.clearAnimation();
				device_not_found_layout.setVisibility(View.VISIBLE);
			}
		});
		device_not_found_layout.startAnimation(animation);

	}

	public void hideWarnLayout() {
		if (device_not_found_layout == null)
			return;
		Animation animation = AnimationUtils.loadAnimation(activity, R.anim.up_slideout);
		animation.setAnimationListener(new AnimationListener() {

			@Override
			public void onAnimationStart(Animation animation) {
			}

			@Override
			public void onAnimationRepeat(Animation animation) {
			}

			@Override
			public void onAnimationEnd(Animation animation) {
				device_not_found_layout.clearAnimation();
				device_not_found_layout.setVisibility(View.GONE);
			}
		});
		device_not_found_layout.startAnimation(animation);
	}

	public void onPushClick(View view) {
		DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();

		if (dmrProcessor instanceof LocalDMRProcessorImpl)
		{
			Device device = UpnpProcessorImpl.getSington().getCurrentDMR();
			if (device != null)
			{
				m_content.findViewById(R.id.loading_icon).setVisibility(View.VISIBLE);
				UpnpProcessorImpl.getSington().setCurrentDMR(device.getIdentity().getUdn());
				updateItemInfo();
				((ImageView) findViewById(R.id.rc_push)).setImageResource(R.drawable.rc_push_down);
				myHandler.postDelayed(hideLoading, 1000);
			}
			else
			{
				warnLayoutFlash();
			}
		}
		else
		{
			m_content.findViewById(R.id.loading_icon).setVisibility(View.VISIBLE);
			UpnpProcessorImpl.getSington().setCurrentDMR(null);
			updateItemInfo();
			((ImageView) findViewById(R.id.rc_push)).setImageResource(R.drawable.rc_push_up);
			myHandler.postDelayed(hideLoading, 1000);
		}

	}

	private Runnable hideLoading = new Runnable() {

		@Override
		public void run() {
			//			m_content.findViewById(R.id.loading_icon).setVisibility(View.GONE);
		}

	};

	private void warnLayoutFlash() {
		if (device_not_found_layout == null)
			return;
		myHandler.removeCallbacks(hideRunnable);
		showWarnLayout();
		myHandler.postDelayed(hideRunnable, 1000);
	}

	private Runnable hideRunnable = new Runnable() {

		@Override
		public void run() {
			hideWarnLayout();
		}

	};

	public void onBackClick(View view) {
		endActivity();
	}

	private void endActivity() {
		removePlaylistListener();
		finish();
	}

	private PlaylistListener m_playlistListener = new PlaylistListener() {

		public void onItemChanged(PlaylistItem item, final ChangeMode changeMode) {
			cancelLoadingTask();

			if (isStop)
				return;

			//			runOnUiThread(new Runnable() {
			//
			//				@Override
			//				public void run() {
			updateItemInfo();
			m_swipeDetector.setEnable(true);

			//				}
			//			});

		}

	};

	private void cancelLoadingTask() {
		try {
			stopLoading = true;
			if (m_loadingImageTask != null && !m_loadingImageTask.isCancelled())
				m_loadingImageTask.cancel(true);
			m_loadingImageTask = null;
		} catch (Exception ex) {

		}
	}

	public void doNext() {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (playlistProcessor != null)
			playlistProcessor.next();
	}

	public void doPrev() {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (playlistProcessor != null)
			playlistProcessor.previous();
	}

	public void updateItemInfo() {
		DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();

		if (isLongClick)
		{
			System.out.println("--come into picture long click--");
			Device device = UpnpProcessorImpl.getSington().getCurrentDMR();

			if (device == null)
			{
				System.out.println("---the device is null---");
				if (dmrProcessor != null)
				{
					dmrProcessor.setRunning(false);
					dmrProcessor.stop();
				}

				warnLayoutFlash();

				ImageView image = (ImageView) findViewById(R.id.rc_push);
				image.setImageResource(R.drawable.rc_push_up);

				PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
				if (playlistProcessor == null)
					return;
				currentItem = playlistProcessor.getCurrentItem();
				if (currentItem == null) {
					dmrProcessor.stop();
					return;
				}
				m_viewFlipper.setText(currentItem.getTitle());

				int itemIndex = playlistProcessor.getCurrentItemIndex();
				int maxSize = playlistProcessor.getSize();
				m_viewFlipper.setText((itemIndex + 1) + " / " + maxSize);

				m_content.findViewById(R.id.loading_icon).setVisibility(View.VISIBLE);

				loadImage(getViewPagerAbsoluteView(currentViewPagerIndex), currentItem);

				//				waitingLoadPreAndNext();
				return;
			}
			else
			{
				System.out.println("---the device is not null---");
				UpnpProcessorImpl.getSington().setCurrentDMR(device.getIdentity().getUdn());
				dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
			}

		}
		if (dmrProcessor == null)
		{
			System.out.println("The dmrProcessor is null!!");
			UpnpProcessorImpl.getSington().setCurrentDMR(null);
			dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
		}



		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (playlistProcessor == null)
			return;
		currentItem = playlistProcessor.getCurrentItem();
		if (currentItem == null) {
			dmrProcessor.stop();
			return;
		}
		m_viewFlipper.setText(currentItem.getTitle());

		int itemIndex = playlistProcessor.getCurrentItemIndex();
		int maxSize = playlistProcessor.getSize();
		m_viewFlipper.setText((itemIndex + 1) + " / " + maxSize);

		if (dmrProcessor instanceof RemoteDMRProcessorImpl)
		{
			isLongClick = false;
			System.out.println("remote DMR");
			dmrProcessor.setRunning(true);
			ImageView image = (ImageView) findViewById(R.id.rc_push);
			image.setImageResource(R.drawable.rc_push_down);
		}
		else
		{
			System.out.println("local DMR");
			ImageView image = (ImageView) findViewById(R.id.rc_push);
			image.setImageResource(R.drawable.rc_push_up);
		}
		dmrProcessor.setURIandPlay(currentItem);

		m_content.findViewById(R.id.loading_icon).setVisibility(View.VISIBLE);
		if(m_loadingImageTask!=null && ItemUrl!=null){
			if(!ItemUrl.equals(currentItem.getUrl()))
				loadImage(getViewPagerAbsoluteView(currentViewPagerIndex), currentItem);
		}else{
			loadImage(getViewPagerAbsoluteView(currentViewPagerIndex), currentItem);
		}

		if(DMSBrowseActivity.firstLoad){
			DMSBrowseActivity.firstLoad = false;
			System.out.println("-----is first load pic----");
			updateItemInfo();
		}

		//		waitingLoadPreAndNext();
	}

	private void waitingLoadPreAndNext() {

		new Thread(new Runnable() {

			@Override
			public void run() {
				waiting();

				beginLoadPreAndNext();

			}

		}).start();

	}

	private void waiting() {
		while(isLoadingbusy) {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	private void beginLoadPreAndNext() {
		runOnUiThread(new Runnable() {

			@Override
			public void run() {
				loadNextItem();

				new Thread(new Runnable() {

					@Override
					public void run() {
						waiting();

						beginLoadPre();
					}

				}).start();
			}

		});
	}

	private void beginLoadPre() {
		runOnUiThread(new Runnable() {

			@Override
			public void run() {
				loadPreItem();
			}
		});
	}

	private boolean downLoad = false;
	private String ItemUrl = null;
	//	private Bitmap picBitmap;
	private void loadImage(final ImageView imageView, final PlaylistItem item) {
		System.out.println("-----------Come into load image-----------");
		isLoadingbusy = true;
//		imageView.setImageResource(R.drawable.browse_image_default);
		cancelLoadingTask();
		m_loadingImageTask = new AsyncTask<PlaylistItem, Void, Bitmap>() {

			protected void onPreExecute() {
				downLoad = true;
				m_content.findViewById(R.id.loading_icon).setVisibility(View.VISIBLE);
				imageView.setImageResource(R.drawable.browse_image_default);

			};

			@Override
			protected Bitmap doInBackground(PlaylistItem... params) {

				PlaylistItem item = params[0];

				String url = item.getUrl();
				ItemUrl = url;
				Bitmap picBitmap = cache.getBitmap(url);
				//				Bitmap picBitmap = PictureData.getPicture(url);;

				if (picBitmap != null && !picBitmap.isRecycled()) {
					System.out.println("Bitmap is not null!!!" + url);
					return picBitmap;
				}else{
					System.out.println("Bitmap is null!!!" + url);
				}

				if (item.fromLocalType()) {
					int count = 0;
					do{
						if(isCancelled())
							return null;
						count++;
						picBitmap = getLocalBitmap(url, item);
//						picBitmap = getLocalBitmap(item);
					}while(picBitmap==null && count<=1);

					/**
					Uri uri = Uri.parse(url);
					String path = uri.getPath();
					if (path != null) {
						try {
							bitmap = thumbGenerator.decodeFileBitmap(new File(path), Utility.getBaseWidth(), Utility.getBaseHeight());
							System.out.println("The bitmap1:" + bitmap );

							if (bitmap != null && !bitmap.isRecycled()) {
								int degree = ThumbnailGenerator.getPhotoDegree(path);
								bitmap =  ThumbnailGenerator.rotateBitmap(bitmap, degree);
								if (bitmap != null && !bitmap.isRecycled()) {
									cache.putToCache(url, bitmap);
									return bitmap;
								}
							}
						} catch (MyException e) {
							try {
								Thread.sleep(100);
							} catch (InterruptedException e1) {
								e1.printStackTrace();
							}

							try {
								bitmap = thumbGenerator.decodeFileBitmap(new File(path), Utility.getBaseWidth(), Utility.getBaseHeight());

								if (bitmap != null && !bitmap.isRecycled()) {
									int degree = ThumbnailGenerator.getPhotoDegree(path);
									bitmap =  ThumbnailGenerator.rotateBitmap(bitmap, degree);
									if (bitmap != null && !bitmap.isRecycled()) {
										cache.putToCache(url, bitmap);
										return bitmap;
									}
								}
							} catch (MyException ex) {
								e.printStackTrace();
							}
						}
					}
					 */
				}else{
					int count = 0;
					do{
						if(isCancelled())
							return null;
						count++;
						picBitmap = getBitmap(url, item);
					}while(picBitmap==null && count<=1);
				}


				/**
				File tmpFile = new File(Utility.CACHE_ROOT + File.separator + url.lastIndexOf("/"));

				try {
					readTo(url, tmpFile);
					try {
						bitmap = thumbGenerator.decodeFileBitmap(tmpFile, Utility.getBaseWidth(), Utility.getBaseHeight());
						if (bitmap != null && !bitmap.isRecycled()) {
							PictureData.addPicture(item.getId(), bitmap);
//							cache.putToCache(item.getId(), bitmap);
							return bitmap;
						}
					} catch (Throwable th) {
						System.gc();
						try {
							bitmap = thumbGenerator.decodeFileBitmap(tmpFile, Utility.getBaseWidth(), Utility.getBaseHeight());
							if (bitmap != null && !bitmap.isRecycled()) {
								PictureData.addPicture(item.getId(), bitmap);
//								cache.putToCache(item.getId(), bitmap);
								return bitmap;
							}
						} catch (Throwable th1) {
							System.gc();
						}
					}
				} catch (Throwable th) {
					System.gc();

					if(!stopLoading) {
						try {
							Thread.sleep(200);
						} catch (InterruptedException e) {
						}

						try {
							readTo(url, tmpFile);
							try {
								bitmap = thumbGenerator.decodeFileBitmap(tmpFile, Utility.getBaseWidth(), Utility.getBaseHeight());
								if (bitmap != null && !bitmap.isRecycled()) {
//									cache.putToCache(item.getId(), bitmap);
									PictureData.addPicture(item.getId(), bitmap);
									return bitmap;
								}
							} catch (Throwable th1) {
								System.gc();
								try {
									bitmap = thumbGenerator.decodeFileBitmap(tmpFile, Utility.getBaseWidth(), Utility.getBaseHeight());
									if (bitmap != null && !bitmap.isRecycled()) {
//										cache.putToCache(item.getId(), bitmap);
										PictureData.addPicture(item.getId(), bitmap);
										return bitmap;
									}
								} catch (Throwable th2) {
									System.gc();
								}
							}
						} catch (Throwable th1) {
							System.gc();
						}
					}
				} finally {
					tmpFile.delete();
				}*/
				return picBitmap;
			}

			@Override
			protected void onPostExecute(Bitmap result) {
				ItemUrl = null;
				m_content.findViewById(R.id.loading_icon).setVisibility(View.GONE);
				downLoad = false;
				if (result == null || result.isRecycled()) {
					Utility.downToast(mToast, activity, R.string.image_loading_error);
				} else {
					imageView.setImageBitmap(result);
				}
				isLoadingbusy = false;
			}

			@Override
			protected void onCancelled() {
				// TODO Auto-generated method stub
				//				super.onCancelled();
				ItemUrl = null;
				downLoad = false;
				System.out.println("Cancell this pic load!!!");
			}


		};
		m_loadingImageTask.execute(item);
	}

	private Bitmap getLocalBitmap(String url, PlaylistItem item){
		System.out.println("______Get Local Bitmap______");
		Bitmap bitmap = null;
		Uri uri = Uri.parse(url);
		String path = uri.getPath();
		if (path != null) {
			try {
				bitmap = thumbGenerator.decodeFileBitmap(new File(path), Utility.getBaseWidth(), Utility.getBaseHeight());

				if (bitmap != null && !bitmap.isRecycled()) {
					//					int degree = ThumbnailGenerator.getPhotoDegree(path);
					//					bitmap =  ThumbnailGenerator.rotateBitmap(bitmap, degree);
//					if (bitmap != null && !bitmap.isRecycled()) {
						cache.putToCache(url, bitmap);
						return bitmap;
//					}
				}
			} catch (MyException e) {
				e.printStackTrace();
			}
		}
		return bitmap;
	}

	private Bitmap getLocalBitmap(PlaylistItem item){
		String path = item.getId();
		Bitmap bitmap = null;
		if (path != null) {
			try {
				bitmap = NativeImageLoader.getInstance().decodeThumbBitmapForFile(path, 720, 480);

				if (bitmap != null && !bitmap.isRecycled()) {
					//					int degree = ThumbnailGenerator.getPhotoDegree(path);
					//					bitmap = NativeImageLoader.getInstance().decodeThumbBitmapForFile(path, 720, 480);
					//					bitmap =  ThumbnailGenerator.rotateBitmap(bitmap, degree);
					if (bitmap != null && !bitmap.isRecycled()) {
						cache.putToCache(path, bitmap);
						return bitmap;
					}
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return bitmap;
	}

	private Bitmap getBitmap(String url, PlaylistItem item){
		System.out.println("______Get Bitmap______");
		File tmpFile = new File(Utility.CACHE_ROOT + File.separator + url.lastIndexOf("/"));
		Bitmap bitmap;
		try {
			readTo(url, tmpFile);
			bitmap = thumbGenerator.decodeFileBitmap(tmpFile, Utility.getBaseWidth(), Utility.getBaseHeight());
			if (bitmap != null && !bitmap.isRecycled()) {
				//				PictureData.addPicture(url, bitmap);
				cache.putToCache(url, bitmap);
				return bitmap;
			}
		} catch (Error e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			tmpFile.delete();
		}
		return null;
	}

	public byte[] getBytes(InputStream is) throws Exception{  
		ByteArrayOutputStream bos = new ByteArrayOutputStream();  
		byte[] buffer = new byte[1024];  
		int len = 0;  
		while((len = is.read(buffer))!=-1){  
			bos.write(buffer, 0, len);  
		}  
		is.close();  
		bos.flush();  
		byte[] result = bos.toByteArray();  
		System.out.println(new String(result));  
		return  result;  
	}  

	public void getResponseStr(String path, File file) throws Exception {
		//		InputStream inputStream = new URL(path).openStream();
		URL url = new URL(path);  
		HttpURLConnection conn =  (HttpURLConnection) url.openConnection();  
		conn.setRequestMethod("GET");  
		conn.setConnectTimeout(3000);  
		//获取服务器返回回来的流   
		//		InputStream is = conn.getInputStream();
		readStream(conn.getInputStream(), file);
		//		byte[] imagebytes = getBytes(is);  
		//		Bitmap bitmap = BitmapFactory.decodeByteArray(imagebytes, 0, imagebytes.length);  
	}  


	private void readTo(final String urlStr, final File file) throws Error, Exception
	{
		stopLoading = false;
		try {
			getResponseStr(urlStr, file);
			if(stopLoading){
				throw new Exception("stopLoading this image");
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		//		URL url = new URL(urlStr); 
		//		URLConnection urlConnection = (URLConnection) url.openConnection(); 
		//		urlConnection.connect();
		//		readStream(urlConnection.getInputStream(), file);
	}

	public void readStream(InputStream inputstream, File file)throws Exception, Error
	{
		if (inputstream == null)
			throw new Exception("stream is null");
		BufferedInputStream inputBuffer = null;
		BufferedOutputStream outputBuffer = null;
		try{
			inputBuffer = new BufferedInputStream(inputstream);

			if (file.exists()){
				file.delete();
				file.createNewFile();
			}else{
				file.createNewFile();
			}

			outputBuffer = new BufferedOutputStream(new FileOutputStream(file));
			byte[] arrayOfByte = new byte[524288];

			int len = -1;
			while((len = inputBuffer.read(arrayOfByte)) != -1){
				if(stopLoading){
					throw new Exception("stopLoading this image");
				}
				outputBuffer.write(arrayOfByte, 0, len);
			}
			outputBuffer.flush();

		}catch(Exception ex){
			throw new Exception(ex);
		}catch(Error err){
			System.gc();
			throw new Error(err);
		}finally{
			if (null != outputBuffer) 
				outputBuffer.close();
			if(null != inputBuffer)
				inputBuffer.close();
			if (null != inputstream) 
				inputstream.close();
		}
	}

	@Override
	protected void onResume() {
		super.onResume();
		isStop = false;
		addPlaylistListener();
		UpnpProcessorImpl.getSington().addDMRListener(m_dmrListener);
	}

	@Override
	protected void onPause() {
		super.onPause();
		isStop = true;
		removePlaylistListener();
		UpnpProcessorImpl.getSington().removeDMRListener(m_dmrListener);
	}

	private DMRProcessorListener m_dmrListener = new DMRProcessorListener() {

		@Override
		public void onUpdatePosition(final long current, final long max) {
		}

		@Override
		public void onStoped() {
		}

		@Override
		public void onPlaying() {
		}

		@Override
		public void onPaused() {
		}

		@Override
		public void onMiddleEndEvent() {
			System.out.println("---- pic come into onMiddleEndEvent----");
			runOnUiThread(new Runnable() {
				public void run() {
					onPushClick(null);
				}
			});
		};

		@Override
		public void onErrorEvent(final String error) {

		}

		@SuppressWarnings("rawtypes")
		@Override
		public void onActionFail(Action actionCallback, final UpnpResponse response, final String cause) {
		}

		@Override
		public void onCompleted() {
			// TODO Auto-generated method stub
			System.out.println("----pic play completed-----");
		}
	};

	public void removePlaylistListener() {
		UpnpProcessorImpl.getSington().removePlaylistListener(m_playlistListener);
	}

	public void addPlaylistListener() {
		UpnpProcessorImpl.getSington().addPlaylistListener(m_playlistListener);
	}

	@Override
	public void onBackPressed() {
		endActivity();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		destroy();

		m_rendererControl.onDestroy();

		stopPlayer();
	}

	private void destroy() {
		new Thread(new Runnable() {

			@Override
			public void run() {
				activity.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						for (ImageView view : views)
						{
							view.setImageDrawable(null);
						}
					}
				});

				cache.clear();
			}
		}).start();
	}

	private void stopPlayer() {
		DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
		if (dmrProcessor != null) {
			dmrProcessor.stop();
		}
	}

	public void toggleItemInfo() {
		if (rc_playing_top.isShown()) {
			System.out.println("-----------show to gone-----------");
			rc_playing_top.setVisibility(View.GONE);
			getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
		} else {
			System.out.println("-----------gone to show-----------");
			if(!downLoad){
				rc_playing_top.setVisibility(View.VISIBLE);
				getWindow().clearFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
			}
		}
	}

	private class SwipeCallbackImpl implements SwipeCallback {

		@Override
		public void swipeToNext() {
			doNext();
		}

		@Override
		public void swipeToPrevious() {
			doPrev();
		}

		@Override
		public void onTap() {
			toggleItemInfo();
			m_rendererControl.onTab(downLoad);
		}
	}
}
