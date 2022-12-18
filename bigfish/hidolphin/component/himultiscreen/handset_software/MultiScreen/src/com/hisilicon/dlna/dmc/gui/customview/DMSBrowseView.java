package com.hisilicon.dlna.dmc.gui.customview;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.LocalDevice;
import org.teleal.cling.model.meta.RemoteDevice;
import org.teleal.cling.model.types.UDN;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.AudioItem;
import org.teleal.cling.support.model.item.ImageItem;
import org.teleal.cling.support.model.item.Item;
import org.teleal.cling.support.model.item.MusicTrack;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Rect;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v4.view.ViewPager.OnPageChangeListener;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AbsListView.OnScrollListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemLongClickListener;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.gui.activity.AppPreference;
import com.hisilicon.dlna.dmc.gui.activity.DMSBrowseActivity;
import com.hisilicon.dlna.dmc.gui.activity.DMSOtherBrowseActivity;
import com.hisilicon.dlna.dmc.gui.activity.PlayingImageActivity;
import com.hisilicon.dlna.dmc.gui.activity.PlayingMusicActivity;
import com.hisilicon.dlna.dmc.gui.activity.PlayingVideoActivity;
import com.hisilicon.dlna.dmc.gui.browse.files.BrowseImageAdapter_New;
import com.hisilicon.dlna.dmc.gui.browse.files.FileData;
import com.hisilicon.dlna.dmc.gui.browse.files.NativeImageLoader;
import com.hisilicon.dlna.dmc.gui.browse.files.Picture_New_View;
import com.hisilicon.dlna.dmc.gui.browse.files.Picture_New_View.FileLongClickCallBack;
import com.hisilicon.dlna.dmc.processor.impl.PlaylistProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMSProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMSProcessor.DMSProcessorListner;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.ChangeMode;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.PlaylistListener;
import com.hisilicon.dlna.dmc.processor.interfaces.UpnpProcessor.DevicesListener;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentTree;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.R;
import com.hisilicon.multiscreen.widget.BottomLineImageView;
import com.hisilicon.multiscreen.widget.SlidePushView;

public class DMSBrowseView extends LinearLayout {

	public static final String LONGCLICK = "LONGCLICK";

	private static final String IMAGE = "IMAGE";
	private static final String VIDEO = "VIDEO";
	private static final String MUSIC = "MUSIC";
	private static final String CAMERA_IMAGE = "CAMERA_IMAGE";
	private static final String CAMERA_VIDEO = "CAMERA_VIDEO";
	private static final String CAMERA_MUSIC = "CAMERA_MUSIC";
	private static final String ALL_IMAGE = "ALL_IMAGE";
	private static final String ALL_VIDEO = "ALL_VIDEO";
	private static final String ALL_MUSIC = "ALL_MUSIC";

	/**
	 * 存放图片、视频、音乐root目录及所有图片、所有视频、所有音乐目录的ID
	 */
	private HashMap<String, String> rootFloor = new HashMap<String, String>();
	/**
	 * 存放图片、视频、音乐root目录的Container，key为ID，对应rootFloor ID，value为Container
	 */
	private HashMap<String, DIDLObject> firstFloor = new HashMap<String, DIDLObject>();
	/**
	 * 看来没必要
	 */
	private HashMap<String, Map<String, List<? extends DIDLObject>>> secondFloor = new HashMap<String, Map<String, List<? extends DIDLObject>>>();

	private BrowseState imageBrowseState = BrowseState.UNKOWN;
	private BrowseState videoBrowseState = BrowseState.UNKOWN;
	private BrowseState musicBrowseState = BrowseState.UNKOWN;

	private ArrayList<String> image_traceID = new ArrayList<String>();
	private ArrayList<String> video_traceID = new ArrayList<String>();
	private ArrayList<String> music_traceID = new ArrayList<String>();

	private boolean m_loadMore;
	private volatile boolean isStop = false;

	private ViewPager viewPager;
	private BottomLineImageView imageView;
	private List<View> views;

	private DMSDeviceAdapter dmsDeviceAdapter;
	private BrowseImageAdapter imageAdapter;
	private BrowseVideoAdapter videoAdapter;
	private BrowseMusicAdapter musicAdapter;

	private FrameLayout rc_dms_picture_bottom_layout;
	private FrameLayout rc_dms_video_bottom_layout;
	private FrameLayout rc_dms_music_bottom_layout;
	private LinearLayout rc_dms_shuffle_play_layout;
	private GridView imageGridView;
	private GridView videoGridView;
	private GridView musicGridView;
	private View rc_dms_devices_layout;
	private GridView rc_dms_devices;
	private Button rc_dms_devices_back;

	private LinearLayout rc_dmstitle_header_layout;
	private TextView rc_dms_header_title;
	private SlidePushView slidePushView;
	private ImageView rc_slide_area;
	private volatile boolean isLongClick = false;
	private AdapterItem item;
	private Context context;
	private View imageLayout_new, imageLayout, videoLayout, musicLayout;
	//	private static Picture_New_View mPicture_New_View;

	@SuppressWarnings("rawtypes")
	public DMSBrowseView(Context context) {
		super(context);
		this.context = context;
		ThumbnailGenerator.getInstance().restore();

		((LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE)).inflate(R.layout.dlna_dms_browseview, this);

		if(context instanceof DMSBrowseActivity) {
			rc_dmstitle_header_layout = (LinearLayout) ((Activity) context).findViewById(R.id.rc_dmstitle_header_layout);
			rc_dms_header_title = (TextView) ((Activity) context).findViewById(R.id.rc_dms_header_title);
			slidePushView = (SlidePushView) ((Activity) context).findViewById(R.id.slidePushView);
			rc_dmstitle_header_layout.setOnClickListener(dmsShowOrHideClick);
		}
		progressShow();
		initDeviceView();

		clearAllTraceID();
		UpnpProcessorImpl.getSington().addDevicesListener(upnpListener);

		imageAdapter = new BrowseImageAdapter(context);
		imageAdapter.setNotifyOnChange(false);

		videoAdapter = new BrowseVideoAdapter(context);
		videoAdapter.setNotifyOnChange(false);

		musicAdapter = new BrowseMusicAdapter(context);
		musicAdapter.setNotifyOnChange(false);


		initTabView();
		initViewPager();

		//		deviceBrowse(UpnpProcessorImpl.getSington().getCurrentDMS());


	}

	private void clearAllTraceID() {
		image_traceID.clear();
		image_traceID.add("-1");

		video_traceID.clear();
		video_traceID.add("-1");

		music_traceID.clear();
		music_traceID.add("-1");
	}

	private OnClickListener rc_dms_bottom_listener = new OnClickListener() {

		@Override
		public void onClick(View v) {
			Intent intent = new Intent(getContext(), DMSOtherBrowseActivity.class);

			switch(v.getId()) {
			case R.id.rc_dms_picture_bottom_layout:
				Bundle bundle = new Bundle();
				bundle.putStringArrayList("traceID", image_traceID);
				bundle.putSerializable("mediaType", MediaType.IMAGE);
				intent.putExtras(bundle);
				break;
			case R.id.rc_dms_video_bottom_layout:
				bundle = new Bundle();
				bundle.putStringArrayList("traceID", video_traceID);
				bundle.putSerializable("mediaType", MediaType.VIDEO);
				intent.putExtras(bundle);
				break;
			case R.id.rc_dms_music_bottom_layout:
				bundle = new Bundle();
				bundle.putStringArrayList("traceID", music_traceID);
				bundle.putSerializable("mediaType", MediaType.MUSIC);
				intent.putExtras(bundle);
				break;
			}
			getContext().startActivity(intent);

		}
	};

	private OnClickListener dmsShowOrHideClick = new OnClickListener() {

		@Override
		public void onClick(View v) {
			if (rc_dms_devices_layout != null) {
				if (rc_dms_devices_layout.isShown()) {
					rc_dms_devices_layout.setVisibility(View.GONE);
				} else {
					rc_dms_devices_layout.setVisibility(View.VISIBLE);
				}
			}

		}
	}; 

	private void initDeviceView() {
		rc_dms_devices_layout = findViewById(R.id.rc_dms_devices_layout);
		rc_dms_devices = (GridView) findViewById(R.id.rc_dms_devices);
		rc_dms_devices_back = (Button) findViewById(R.id.rc_dms_devices_back);
		rc_dms_devices_back.setOnClickListener(dmsShowOrHideClick);
		dmsDeviceAdapter = new DMSDeviceAdapter(getContext());
		rc_dms_devices.setAdapter(dmsDeviceAdapter);
		rc_dms_devices.setOnItemClickListener(deviceItemClick);
	}

	private void initViewPager() {
		rc_slide_area = (ImageView) findViewById(R.id.rc_slide_area);
		rc_slide_area.setOnTouchListener(new OnTouchListener() {
			private int MIN_DISTANCE = 100;
			private float downY, upY, moveY;

			@Override
			public boolean onTouch(View v, MotionEvent event) {
				//				System.out.println("Slide touch listener!!");
				if (rc_dms_devices_layout.isShown()) {
					rc_dms_devices_layout.setVisibility(View.GONE);
				}

				if (!isLongClick) {
					try {
						viewPager.dispatchTouchEvent(event);
					} catch (Exception ex){
					}
					if (event.getAction() == MotionEvent.ACTION_DOWN) {
						downY = event.getY();;
						moveY = event.getY();
					}
					return true;
				}

				switch (event.getAction()) {
				case MotionEvent.ACTION_DOWN: {
					downY = event.getY();;
					moveY = event.getY();
					break;
				}
				case MotionEvent.ACTION_MOVE: {
					final float preY = moveY;
					float nowY = event.getY();
					moveY = nowY;

					float deltaY = nowY - preY;
					this.onDeltaY((int) deltaY);
					break;
				}
				case MotionEvent.ACTION_UP:
					upY = event.getY();

					float deltaY = downY - upY;
					if (Math.abs(deltaY) > MIN_DISTANCE)
					{
						if (deltaY < 0)
						{
							this.onUpToDownSlide();
						}
						else if (deltaY > 0)
						{
							this.onDownToUpSlide();
						}
					}
					else
					{
						this.onTap();
					}
					break;
				}

				return true;
			}

			private void onDeltaY(int deltaY) {
				int left = slidePushView.getLeft();
				int right = slidePushView.getRight();
				int top = slidePushView.getTop();
				int bottom = slidePushView.getBottom();

				slidePushView.layout(left , top + deltaY, right , bottom + deltaY);
			}

			private void onDownToUpSlide() {
				updatePlaylistAndPlay(item, true);
				slidePushView.touchClearShow();
				isLongClick = false;
			}

			private void onUpToDownSlide() {
				slidePushView.touchClearShow();
				isLongClick = false;
			}

			private void onTap() {
				isLongClick = false;
				slidePushView.touchClearShow();
			} 
		});

		viewPager = (ViewPager) findViewById(R.id.vPager);
		views = new ArrayList<View>();
		imageLayout = View.inflate(getContext(), R.layout.dlna_pictures_layout, null);
		videoLayout = View.inflate(getContext(), R.layout.dlna_videos_layout, null);
		musicLayout = View.inflate(getContext(), R.layout.dlna_musics_layout, null);

		imageGridView = (GridView) imageLayout.findViewById(R.id.dms_image_browsing);
		imageGridView.setAdapter(imageAdapter);
		imageGridView.setOnItemClickListener(imageItemClick);
		imageGridView.setOnItemLongClickListener(itemLongClickListener);
		imageGridView.setOnScrollListener(imageScrollListener);
		rc_dms_picture_bottom_layout = (FrameLayout) imageLayout.findViewById(R.id.rc_dms_picture_bottom_layout);
		rc_dms_picture_bottom_layout.setOnClickListener(rc_dms_bottom_listener);
		rc_dms_picture_bottom_layout.setVisibility(View.GONE);

		videoGridView = (GridView) videoLayout.findViewById(R.id.dms_video_browsing);
		videoGridView.setAdapter(videoAdapter);
		videoGridView.setOnItemClickListener(videoItemClick);
		videoGridView.setOnItemLongClickListener(itemLongClickListener);
		videoGridView.setOnScrollListener(videoScrollListener);
		rc_dms_video_bottom_layout = (FrameLayout) videoLayout.findViewById(R.id.rc_dms_video_bottom_layout);
		rc_dms_video_bottom_layout.setOnClickListener(rc_dms_bottom_listener);
		rc_dms_video_bottom_layout.setVisibility(View.GONE);

		musicGridView = (GridView) musicLayout.findViewById(R.id.dms_music_browsing);
		musicGridView.setAdapter(musicAdapter);
		musicGridView.setOnItemClickListener(musicItemClick);
		musicGridView.setOnItemLongClickListener(itemLongClickListener);
		musicGridView.setOnScrollListener(musicScrollListener);
		rc_dms_music_bottom_layout = (FrameLayout) musicLayout.findViewById(R.id.rc_dms_music_bottom_layout);
		rc_dms_music_bottom_layout.setOnClickListener(rc_dms_bottom_listener);
		rc_dms_music_bottom_layout.setVisibility(View.GONE);
		rc_dms_shuffle_play_layout = (LinearLayout) musicLayout.findViewById(R.id.rc_dms_shuffle_play_layout);
		rc_dms_shuffle_play_layout.setVisibility(View.GONE);
		final ImageView shuffleImage = (ImageView) musicLayout.findViewById(R.id.rc_music_shuffle);
		if (AppPreference.getShuffle()) {
			shuffleImage.setImageResource(R.drawable.rc_shuffle_pressed);
		} else {
			shuffleImage.setImageResource(R.drawable.rc_shuffle_normal);
		}
		shuffleImage.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				if (AppPreference.getShuffle())
				{
					shuffleImage.setImageResource(R.drawable.rc_shuffle_normal);
					AppPreference.setShuffle(false);
				}
				else
				{
					shuffleImage.setImageResource(R.drawable.rc_shuffle_pressed);
					AppPreference.setShuffle(true);
				}			
			}
		});

		/******4/18
		if(mPicture_New_View==null){
			System.out.println("mPicture_New_View is null!!");
			mPicture_New_View = new Picture_New_View(context, slidePushView, new FileLongClickCallBack() {

				@Override
				public void update(boolean islongClick, AdapterItem adapterItem) {
					// TODO Auto-generated method stub
					isLongClick = islongClick;
					item = adapterItem;
				}
			}, progressHandler);
		}else{
			System.out.println("mPicture_New_View is not null!!");
			mPicture_New_View.setSlidePushView(slidePushView);
			mPicture_New_View.setFileLongClickCallBack(new FileLongClickCallBack() {

				@Override
				public void update(boolean islongClick, AdapterItem adapterItem) {
					// TODO Auto-generated method stub
					isLongClick = islongClick;
					item = adapterItem;
				}
			});
		}
		imageLayout_new = mPicture_New_View.getView();
		 */
		/******
		Device cDevice = UpnpProcessorImpl.getSington().getCurrentDMS();
		if(cDevice instanceof LocalDevice||cDevice==null){
			System.out.println("Current cDevice is local!!!");
			views.add(imageLayout_new);
		}else{
			System.out.println("Current cDevice is local!!!");
			views.add(imageLayout);
		}
		 */

		views.add(imageLayout);
		views.add(videoLayout);
		views.add(musicLayout);
		viewPager.setAdapter(new ViewPagerAdapter(views));
		viewPager.setCurrentItem(0);  
		viewPager.setOnPageChangeListener(new ViewPageChangeListener());
	}

	private void initTabView() {
		//页卡滑动下滑线
		imageView = (BottomLineImageView) findViewById(R.id.iv_bottom_line);
		imageView.initTabCount(3);

		ImageView imageTab = (ImageView) findViewById(R.id.rc_share_picture_tab);
		ImageView videoTab = (ImageView) findViewById(R.id.rc_share_video_tab);
		ImageView musicTab = (ImageView) findViewById(R.id.rc_share_music_tab);

		imageTab.setOnClickListener(new OnClickTab(MediaType.IMAGE));
		videoTab.setOnClickListener(new OnClickTab(MediaType.VIDEO));
		musicTab.setOnClickListener(new OnClickTab(MediaType.MUSIC));
	}

	class OnClickTab implements OnClickListener {
		private MediaType mediaType = MediaType.IMAGE;

		OnClickTab(MediaType mediaType){
			this.mediaType = mediaType;
		}
		@Override
		public void onClick(View v) {
			if (mediaType == MediaType.IMAGE) {
				imageAdapter.notifyVisibleItemChanged(imageGridView);
			} else if (mediaType == MediaType.VIDEO) {
				videoAdapter.notifyVisibleItemChanged(videoGridView);
			} else if (mediaType == MediaType.MUSIC) {
				musicAdapter.notifyVisibleItemChanged(musicGridView);
			}
			viewPager.setCurrentItem(mediaType.toInt());
		}
	}

	class ViewPagerAdapter extends PagerAdapter{
		private List<View> listViews;

		ViewPagerAdapter(List<View> listViews){
			this.listViews = listViews ;

		}

		@Override
		public void destroyItem(ViewGroup container, int position, Object object) {
			container.removeView(listViews.get(position));
		}


		@Override
		public Object instantiateItem(ViewGroup container, int position) {
			container.addView(listViews.get(position),0);
			return listViews.get(position);
		}


		@Override
		public int getCount() {
			return listViews.size();
		}

		@Override
		public boolean isViewFromObject(View arg0, Object arg1) {
			return arg0 == arg1;
		}
	}

	class ViewPageChangeListener implements OnPageChangeListener {

		@Override
		public void onPageScrollStateChanged(int state) {
			if (state == 1) {
				if (viewPager.getCurrentItem() == 0) {
					videoAdapter.notifyVisibleItemChanged(videoGridView);
				} else if (viewPager.getCurrentItem() == 1) {
					imageAdapter.notifyVisibleItemChanged(imageGridView);
					musicAdapter.notifyVisibleItemChanged(musicGridView);
				} else {
					videoAdapter.notifyVisibleItemChanged(videoGridView);
				}
			}
		}

		@Override
		public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {
		}

		@Override
		public void onPageSelected(int arg0) {
			imageView.translateToPosition(arg0);
		}
	}

	public void progressDismiss() {
		progressHandler.sendEmptyMessage(2);
		//		findViewById(R.id.progress_layout).setVisibility(View.GONE);
	}

	public void progressShow() {
		progressHandler.sendEmptyMessage(1);
		//		findViewById(R.id.progress_layout).setVisibility(View.VISIBLE);
	}

	private Handler progressHandler = new Handler(){
		public static final int SHOW = 1;
		public static final int DISMISS = 2;

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			switch(msg.what){
			case SHOW:
				findViewById(R.id.progress_layout).setVisibility(View.VISIBLE);
				break;
			case DISMISS:
				findViewById(R.id.progress_layout).setVisibility(View.GONE);
				break;
			}
		}

	};

	public boolean progressIsShow() {
		return findViewById(R.id.progress_layout).isShown();
	}

	public void updateDMSDevice() {
		Device currentDMS = UpnpProcessorImpl.getSington().getCurrentDMS();
		if (currentDMS != null)
		{
			System.out.println("The dms add currentDMS");
			UDN udn = currentDMS.getIdentity().getUdn();
			UpnpProcessorImpl.getSington().setCurrentDMS(udn);
		}

		for (Device device : UpnpProcessorImpl.getSington().getDMSList()) {
			System.out.println("The dms 1 device name:" + device.getDetails().getFriendlyName());
			addAdapterDMS(device);
		}
		deviceBrowse(UpnpProcessorImpl.getSington().getCurrentDMS());
	}

	/**
	 * 找出机顶盒端DMR设备并绑定
	 */
	public void updateDMRDevice() {
		Device dmrDevice = UpnpProcessorImpl.getSington().getCurrentDMR();
		if (HttpServerUtil.isSTBDMR(dmrDevice))
			return;
		System.out.println("Dmr 123 list size is:" + UpnpProcessorImpl.getSington().getDMRList().size());
		for (Device device : UpnpProcessorImpl.getSington().getDMRList())
		{
			if (HttpServerUtil.isSTBDMR(device))
			{
				System.out.println("123Find connect device!!");
				UDN udn = device.getIdentity().getUdn();
				UpnpProcessorImpl.getSington().stbOnline(udn);
				return;
			}
		}
	}

	private OnScrollListener imageScrollListener = new OnScrollListener() {

		@Override
		public void onScrollStateChanged(AbsListView view, int scrollState) {
			switch (scrollState) {
			case AbsListView.OnScrollListener.SCROLL_STATE_FLING:
			case AbsListView.OnScrollListener.SCROLL_STATE_TOUCH_SCROLL:
				ThumbnailGenerator.getInstance().lock();
				break;
			case AbsListView.OnScrollListener.SCROLL_STATE_IDLE:
				unlockImage();
				break;
			default:
				break;
			}
		}

		@Override
		public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) {
			if (rc_dms_picture_bottom_layout != null && (rootFloor.get(ALL_IMAGE) != null || rootFloor.get(CAMERA_IMAGE) != null))
				if (firstVisibleItem < 1) {
					rc_dms_picture_bottom_layout.setVisibility(View.VISIBLE);
				} else if (firstVisibleItem > 1) {
					rc_dms_picture_bottom_layout.setVisibility(View.GONE);
				}
			try {
				if (hasMoreItems(firstVisibleItem, visibleItemCount, totalItemCount) && lastImageItemIsMark(firstVisibleItem, visibleItemCount)) {
					doLoadMoreImageItems();
				}
			} catch (Exception ex) {

			}
		}
	};

	public void unlockImage() {
		int start = imageGridView.getFirstVisiblePosition();
		int end = imageGridView.getLastVisiblePosition();
		if(end >= imageAdapter.getCount()) {
			end = imageAdapter.getCount() -1;
		}
		ThumbnailGenerator.getInstance().setLoadLimit(start, end + 3);
		ThumbnailGenerator.getInstance().unlock();
	}

	private OnScrollListener videoScrollListener = new OnScrollListener() {

		@Override
		public void onScrollStateChanged(AbsListView view, int scrollState) {
		}

		@Override
		public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) {
			if (rc_dms_video_bottom_layout != null && (rootFloor.get(ALL_VIDEO) != null || rootFloor.get(CAMERA_VIDEO) != null))
				if (firstVisibleItem < 1) {
					rc_dms_video_bottom_layout.setVisibility(View.VISIBLE);
				} else if (firstVisibleItem > 1) {
					rc_dms_video_bottom_layout.setVisibility(View.GONE);
				}
			try {
				if (hasMoreItems(firstVisibleItem, visibleItemCount, totalItemCount) && lastVideoItemIsMark(firstVisibleItem, visibleItemCount)) {
					doLoadMoreVideoItems();
				}
			} catch (Exception ex) {

			}
		}
	};

	private OnScrollListener musicScrollListener = new OnScrollListener() {

		@Override
		public void onScrollStateChanged(AbsListView view, int scrollState) {
		}

		@Override
		public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) {
			if (rc_dms_music_bottom_layout != null && (rootFloor.get(ALL_MUSIC) != null || rootFloor.get(CAMERA_MUSIC) != null))
				if (firstVisibleItem < 1) {
					rc_dms_music_bottom_layout.setVisibility(View.VISIBLE);
				} else if (firstVisibleItem > 1){
					rc_dms_music_bottom_layout.setVisibility(View.GONE);
				}
			try {
				if (hasMoreItems(firstVisibleItem, visibleItemCount, totalItemCount) && lastMusicItemIsMark(firstVisibleItem, visibleItemCount)) {
					doLoadMoreMusicItems();
				}
			} catch (Exception ex) {

			}
		}
	};

	private boolean hasMoreItems(int firstVisibleItem, int visibleItemCount, int totalItemCount) {
		return UpnpProcessorImpl.getSington().getDMSProcessor() != null
				&& !progressIsShow()
				&& firstVisibleItem + visibleItemCount == totalItemCount;
	}

	private boolean lastImageItemIsMark(int firstVisibleItem, int visibleItemCount) {
		Object object = imageAdapter.getItem(firstVisibleItem + visibleItemCount - 1).getData();
		return object instanceof DIDLObject && ((DIDLObject) object).getId().equals("-1");
	}

	private boolean lastVideoItemIsMark(int firstVisibleItem, int visibleItemCount) {
		Object object = imageAdapter.getItem(firstVisibleItem + visibleItemCount - 1).getData();
		return object instanceof DIDLObject && ((DIDLObject) object).getId().equals("-1");
	}

	private boolean lastMusicItemIsMark(int firstVisibleItem, int visibleItemCount) {
		Object object = imageAdapter.getItem(firstVisibleItem + visibleItemCount - 1).getData();
		return object instanceof DIDLObject && ((DIDLObject) object).getId().equals("-1");
	}

	private void doLoadMoreImageItems() {
		progressShow();

		browseMore(image_traceID.get(image_traceID.size() - 1), imageAdapter.getCount(), imageBrowseListener);
	}

	private void doLoadMoreVideoItems() {
		progressShow();

		browseMore(video_traceID.get(video_traceID.size() - 1), videoAdapter.getCount(), videoBrowseListener);
	}

	private void doLoadMoreMusicItems() {
		progressShow();

		browseMore(music_traceID.get(music_traceID.size() - 1), musicAdapter.getCount(), musicBrowseListener);
	}

	private OnItemClickListener deviceItemClick = new OnItemClickListener() {

		@SuppressWarnings("rawtypes")
		@Override
		public void onItemClick(AdapterView<?> adapter, View view, int position, long arg3) {
			/**4/18
			rc_dms_devices_layout.setVisibility(View.GONE);

			Device item = dmsDeviceAdapter.getItem(position);

			if (item instanceof LocalDevice){
				System.out.println("It's localDevice");
				views.clear();
				views.add(imageLayout_new);
				views.add(videoLayout);
				views.add(musicLayout);
				viewPager.setAdapter(new ViewPagerAdapter(views));
				viewPager.setCurrentItem(0); 
				imageView.translateToPosition(0);
				viewPager.setOnPageChangeListener(new ViewPageChangeListener());
				UDN udn = item.getIdentity().getUdn();
				UpnpProcessorImpl.getSington().setCurrentDMS(udn);
				dmsDeviceAdapter.setSelPosition(position);
				dmsDeviceAdapter.notifyDataSetChanged();
				updateHeaderTitle();
				deviceBrowse(item);
			}else{
				System.out.println("It's not localDevice");
				viewPager.removeAllViews();
				views.clear();
				views.add(imageLayout);
				views.add(videoLayout);
				views.add(musicLayout);
				viewPager.setAdapter(new ViewPagerAdapter(views));
				viewPager.setCurrentItem(0); 
				imageView.translateToPosition(0);
				viewPager.setOnPageChangeListener(new ViewPageChangeListener());
				UDN udn = item.getIdentity().getUdn();
				UpnpProcessorImpl.getSington().setCurrentDMS(udn);
				dmsDeviceAdapter.setSelPosition(position);
				dmsDeviceAdapter.notifyDataSetChanged();

				updateHeaderTitle();

				ThumbnailGenerator.getInstance().restore();

				deviceBrowse(item);
			}
			 */
			rc_dms_devices_layout.setVisibility(View.GONE);

			Device item = dmsDeviceAdapter.getItem(position);
			UDN udn = item.getIdentity().getUdn();
			UpnpProcessorImpl.getSington().setCurrentDMS(udn);

			dmsDeviceAdapter.notifyDataSetChanged();

			updateHeaderTitle();

			ThumbnailGenerator.getInstance().restore();

			deviceBrowse(item);
		}
	};

	public void deviceBrowse(Device device) {

		deviceBrowseClear();

		deviceBrowseStart(device);
	}

	private void deviceBrowseClear() {
		clearAllTraceID();

		rootFloor.clear();
		firstFloor.clear();
		secondFloor.clear();

		if (rc_dms_picture_bottom_layout != null)
			rc_dms_picture_bottom_layout.setVisibility(View.GONE);
		if (rc_dms_video_bottom_layout != null)
			rc_dms_video_bottom_layout.setVisibility(View.GONE);
		if (rc_dms_music_bottom_layout != null)
			rc_dms_music_bottom_layout.setVisibility(View.GONE);
		if (rc_dms_shuffle_play_layout != null)
			rc_dms_shuffle_play_layout.setVisibility(View.GONE);

		if(imageAdapter!=null)
			imageAdapter.clear();
		if(videoAdapter!=null)
			videoAdapter.clear();
		if(musicAdapter!=null)
			musicAdapter.clear();
	}

	private void deviceBrowseStart(Device device) {
		DMSProcessor dmsProcessor = UpnpProcessorImpl.getSington().getDMSProcessor();
		if (dmsProcessor != null) {
			m_loadMore = false;
			dmsProcessor.browse("0", 0, AppPreference.getMaxItemPerLoad(), deviceBrowseListener);
		} else {
		}
	}

	private OnItemLongClickListener itemLongClickListener = new OnItemLongClickListener(){

		@Override
		public boolean onItemLongClick(AdapterView<?> parent, View view, final int position, long id) {
			isLongClick = true;
			System.out.println("Come into long click!");
			switch(parent.getId()) {
			case R.id.dms_image_browsing:
				item = imageAdapter.getItem(position);
				break;
			case R.id.dms_video_browsing:
				item = videoAdapter.getItem(position);
				break;
			case R.id.dms_music_browsing:
				item = musicAdapter.getItem(position);
				break;
			}

			Object object = item.getData();
			if (!(object instanceof Item))
				return true;
			Rect frame = new Rect();     
			((Activity) getContext()).getWindow().getDecorView().getWindowVisibleDisplayFrame(frame);

			try {
				view.destroyDrawingCache();
				view.setDrawingCacheEnabled(true);
				Bitmap bitmap = Bitmap.createBitmap(view.getDrawingCache());

				int location[] = new int[2];
				view.getLocationInWindow(location);

				switch(parent.getId()) {
				case R.id.dms_image_browsing:
					System.out.println("Come into slidePushView");
					slidePushView.drawImageSlideView(bitmap, location, frame);
					break;
				case R.id.dms_video_browsing:
					slidePushView.drawVideoSlideView(bitmap, location, frame);
					break;
				case R.id.dms_music_browsing:
					slidePushView.drawMusicSlideView(bitmap, location, frame);
					break;
				}

			} catch(Exception ex) {
			} catch(Error ex) {
				System.gc();
			}

			return false;
		}
	};

	private OnItemClickListener imageItemClick = new OnItemClickListener() {

		@SuppressWarnings("rawtypes")
		@Override
		public void onItemClick(AdapterView<?> adapter, View view, int position, long arg3) {
			view.setBackgroundResource(R.drawable.bg_dms_item_press);
			AdapterItem item = imageAdapter.getItem(position);
			final Object object = item.getData();
			if (object instanceof Container) {
				progressShow();
				imageBrowse(((Container) object).getId(), 0);
			} else if (object instanceof Item) {
				updatePlaylistAndPlay(item, false);
			}

		}
	};

	private OnItemClickListener videoItemClick = new OnItemClickListener() {

		@SuppressWarnings("rawtypes")
		@Override
		public void onItemClick(AdapterView<?> adapter, View view, int position, long arg3) {

			int locate = adapter.getChildCount();
			for(int i=0; i<locate; i++){
				if (position % 2 == 0) {
					adapter.getChildAt(i).setBackgroundResource(R.drawable.bg_dms_item_odd);
				} else {
					adapter.getChildAt(i).setBackgroundResource(R.drawable.bg_dms_item_even);
				}
			}

			view.setBackgroundResource(R.drawable.bg_dms_item_press);
			AdapterItem item = videoAdapter.getItem(position);
			final Object object = item.getData();
			if (object instanceof Container) {
				progressShow();
				videoBrowse(((Container) object).getId(), 0);
			} else if (object instanceof Item) {
				updatePlaylistAndPlay(item, false);
			}
		}
	};

	private OnItemClickListener musicItemClick = new OnItemClickListener() {

		@SuppressWarnings("rawtypes")
		@Override
		public void onItemClick(AdapterView<?> adapter, View view, int position, long arg3) {
			view.setBackgroundResource(R.drawable.bg_dms_item_press);
			AdapterItem item = musicAdapter.getItem(position);
			final Object object = item.getData();
			if (object instanceof Container) {
				progressShow();
				musicBrowse(((Container) object).getId(), 0);
			} else if (object instanceof Item) {
				updatePlaylistAndPlay(item, false);
			}
		}
	};

	private void imageBrowse(String id, int startIndex) {
		image_traceID.add(id);
		browse(id, startIndex,  AppPreference.getMaxItemPerLoad(), imageBrowseListener);
	}

	private void videoBrowse(String id, int startIndex) {
		video_traceID.add(id);
		browse(id, startIndex, AppPreference.getMaxItemPerLoad(), videoBrowseListener);
	}

	private void musicBrowse(String id, int startIndex) {
		music_traceID.add(id);
		browse(id, startIndex, AppPreference.getMaxItemPerLoad(), musicBrowseListener);
	}

	private void browse(String id, int startIndex, int maxResult, DMSProcessorListner m_browseListener) {
		DMSProcessor dmsProcessor = UpnpProcessorImpl.getSington().getDMSProcessor();
		if (dmsProcessor != null) {
			m_loadMore = false;
			dmsProcessor.browse(id, startIndex, maxResult, m_browseListener);
		}
	}

	private void browseMore(String id, int startIndex, DMSProcessorListner m_browseListener) {
		DMSProcessor dmsProcessor = UpnpProcessorImpl.getSington().getDMSProcessor();
		if (dmsProcessor != null) {
			m_loadMore = true;
			dmsProcessor.browse(id, startIndex, AppPreference.getMaxItemPerLoad(), m_browseListener);
		}
	}

	private void runOnUiThread(Runnable runnable) {
		((Activity) getContext()).runOnUiThread(runnable);
	}

	private void updatePlaylistAndPlay(AdapterItem item, boolean isLongClick) {
		Object object = item.getData();

		if (((Item) object).getId().equals("-1")) {
			doLoadMoreImageItems();
			return;
		}


		System.out.println("---come into updatePlaylistAndPlay---");
		Device cDevice = UpnpProcessorImpl.getSington().getCurrentDMS();

		if (object instanceof ImageItem) {
			/** 4/18
			if(cDevice instanceof LocalDevice){
				setAllItem(mPicture_New_View.getAdapter().getItemList());
			}else{
				setAllItem(imageAdapter.getItemList());
			}
			 */

			setAllItem(imageAdapter.getItemList());
			addToPlaylistAndPlay(item);

			Intent intent = new Intent(getContext(), PlayingImageActivity.class);
			intent.putExtra(LONGCLICK, isLongClick);
			getContext().startActivity(intent);
		} else if (object instanceof AudioItem || object instanceof MusicTrack) {
			setAllItem(musicAdapter.getItemList());
			addToPlaylistAndPlay(item);

			Intent intent = new Intent(getContext(), PlayingMusicActivity.class);
			intent.putExtra(LONGCLICK, isLongClick);
			getContext().startActivity(intent);
		} else {
			setAllItem(videoAdapter.getItemList());
			addToPlaylistAndPlay(item);

			Intent intent = new Intent(getContext(), PlayingVideoActivity.class);
			intent.putExtra(LONGCLICK, isLongClick);
			getContext().startActivity(intent);
		}
	}

	private void setAllItem(List list) {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (null == playlistProcessor) {
			playlistProcessor = new PlaylistProcessorImpl();
			UpnpProcessorImpl.getSington().setPlaylistProcessor(playlistProcessor);
		}
		playlistProcessor.setItems(list);

		PlaylistItem playlistItem = playlistProcessor.getItemAt(playlistProcessor.getSize() - 1);
		if (playlistItem.getTitle().equals(Utility.getString(R.string.load_more_result)))
			playlistProcessor.removeItem(playlistItem);
	}

	private void addToPlaylistAndPlay(AdapterItem object) {
		PlaylistItem added = null;
		if (object instanceof PlaylistItem) {
			added = (PlaylistItem) object;
		}

		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (null == playlistProcessor) {
			playlistProcessor = new PlaylistProcessorImpl();
			UpnpProcessorImpl.getSington().setPlaylistProcessor(playlistProcessor);
		}

		if (added == null && object.getData() instanceof DIDLObject) {
			added = playlistProcessor.addDIDLObject((DIDLObject) object.getData());
		}

		if (added != null) {
			playlistProcessor.setCurrentItem(added);

			if (added.getData() instanceof AudioItem)
				musicAdapter.notifyVisibleItemChanged(musicGridView);
		} else {
			Toast.makeText(getContext(), R.string.an_error_occurs_try_again_later, Toast.LENGTH_SHORT).show();
		}
	}

	private DMSProcessorListner deviceBrowseListener = new DMSProcessorListner() {

		@Override
		public void onBrowseFail(String message) {
			deviceBrowseFailure(message);
		}

		@Override
		public void onBrowseComplete(String objectID, boolean haveNext, Map<String, List<? extends DIDLObject>> result) {
			deviceBrowseSuccess(result);

		}

		private void deviceBrowseFailure(String message) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					progressDismiss();
				}

			});
		}

		/**
		 * 
		 * 将获取的媒体筛选出图片，视频，音乐，将他们的ID放入rootFloor，ID对应的Container放入firstFloor
		 */
		private void deviceBrowseSuccess(final Map<String, List<? extends DIDLObject>> result) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {

					List<? extends DIDLObject> containers = result.get("Containers");

					for (DIDLObject didlObject : containers)
					{
						String id = didlObject.getId();
						String title = didlObject.getTitle();

						if (HttpServerUtil.isImage(title))
						{
							rootFloor.put(IMAGE, id);
							firstFloor.put(id, didlObject);
						}
						else if (HttpServerUtil.isVideo(title))
						{
							rootFloor.put(VIDEO, id);
							firstFloor.put(id, didlObject);
						}
						else if (HttpServerUtil.isMusic(title))
						{
							rootFloor.put(MUSIC, id);
							firstFloor.put(id, didlObject);
						}
						else
						{
							firstFloor.put(id, didlObject);
						}
					}

					rootFloorBrowse();
				}
			});
		}

		/**
		 * 浏览root目录图片，视频，音乐的下一级内容
		 */
		private void rootFloorBrowse() {
			rootImageBrowse();

			new Thread(new Runnable() {

				@Override
				public void run() {
					rootImageBrowseWaiting();

					if (BrowseState.FAILURE == imageBrowseState) {
						rootImageBrowse();
						rootImageBrowseWaiting();
					}

					rootFloorVideoAndMusicBrowse();
				}

			}).start();

		}

		/**
		 * 浏览root目录下图片的下一级内容
		 */
		private void rootImageBrowse() {
			Thread thread = new Thread(new Runnable() {

				@Override
				public void run() {
					String id = rootFloor.get(IMAGE);
					if (id != null) {
						imageBrowseState = BrowseState.UNKOWN;

						imageBrowse(id, 0);
					} else {
						imageBrowseState = BrowseState.VOID;
						progressDismiss();
					}
				}
			});
			thread.start();
		}

		private void rootImageBrowseWaiting() {
			while(BrowseState.UNKOWN == imageBrowseState) {
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}

		private void rootFloorVideoAndMusicBrowse() {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					rootVideoBrowse();

					new Thread(new Runnable() {

						@Override
						public void run() {
							rootVideoBrowseWaiting();

							if (BrowseState.FAILURE == videoBrowseState) {
								rootVideoBrowse();

								rootVideoBrowseWaiting();
							}

							rootFloorMusicBrowse();
						}

					}).start();
				}

			});
		}

		/**
		 * 浏览root目录下视频的下一级内容
		 */
		private void rootVideoBrowse() {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					String id = rootFloor.get(VIDEO);
					if (id != null) {
						videoBrowseState = BrowseState.UNKOWN;

						videoBrowse(id, 0);
					} else {
						videoBrowseState = BrowseState.VOID;
					}
				}
			});
		}

		private void rootVideoBrowseWaiting() {
			while(BrowseState.UNKOWN == videoBrowseState) {
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}

		private void rootFloorMusicBrowse() {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					rootMusicBrowse();

					new Thread(new Runnable() {

						@Override
						public void run() {
							rootMusicBrowseWaiting();

							if (BrowseState.FAILURE == musicBrowseState) {
								rootMusicBrowse();

								rootMusicBrowseWaiting();
							}

							/**
							 * 如果DMS没有图片，视频，音乐目录提示没有内容
							 */
							runOnUiThread(new Runnable() {

								@Override
								public void run() {
									if (imageBrowseState == BrowseState.VOID && videoBrowseState == BrowseState.VOID && musicBrowseState == BrowseState.VOID) {
										Toast.makeText(getContext(), R.string.dms_no_findcontent, Toast.LENGTH_SHORT).show();
									}
								}
							});
						}

					});
				}
			});
		}

		/**
		 * 浏览root目录下音乐的下一级内容
		 */
		private void rootMusicBrowse() {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					String id = rootFloor.get(MUSIC);
					if (id != null) {
						musicBrowseState = BrowseState.UNKOWN;

						musicBrowse(id, 0);
					} else {
						musicBrowseState = BrowseState.VOID;
					}
				}
			});
		}

		private void rootMusicBrowseWaiting() {
			while(BrowseState.UNKOWN == musicBrowseState) {
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	};

	/**
	 * 图片浏览回调
	 */
	private DMSProcessorListner imageBrowseListener = new DMSProcessorListner() {

		@Override
		public void onBrowseFail(String message) {
			imageBrowseState = BrowseState.FAILURE;

			imageBrowseFailure(message);
		}

		private void imageBrowseFailure(String message) {
			image_traceID.remove(image_traceID.size() - 1);

			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					progressDismiss();
				}
			});
		}

		@Override
		public void onBrowseComplete(String objectID, boolean haveNext, Map<String, List<? extends DIDLObject>> result) {
			imageBrowseState = BrowseState.SUCCESS;

			imageBrowseSuccess(objectID, haveNext, result);
		}

		private void imageBrowseSuccess(final String objectID, final boolean haveNext, final Map<String, List<? extends DIDLObject>> result) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					if (m_loadMore) {
						imageAdapter.remove(imageAdapter.getItem(imageAdapter.getCount() - 1));
						imageAdapter.notifyDataSetChanged();
					} else {
						setNewPictureAdapter();
					}

					secondFloor.put(objectID, result);

					List<? extends DIDLObject> containers = result.get("Containers");
					List<? extends DIDLObject> items = result.get("Items");

					boolean isBrowseAllImage = false;
					/**
					 * 浏览“所有图片”目录内容
					 */
					if(firstFloor.containsKey(objectID) && objectID.equals(image_traceID.get(image_traceID.size() - 1)) && !containers.isEmpty())
					{
						Device device = UpnpProcessorImpl.getSington().getCurrentDMS();
						String cameraID = ContentTree.IMAGE_FOLDER_PREFIX + Utility.getString(R.string.camera);
						Container cameraContainer = ContentTree.getContainer(cameraID);

						if (device instanceof LocalDevice && cameraContainer != null && cameraContainer.getChildCount() != null && cameraContainer.getChildCount() != 0)
						{
							if (rc_dms_picture_bottom_layout != null)
								rc_dms_picture_bottom_layout.setVisibility(View.VISIBLE);

							imageBrowse(cameraID, 0);

							rootFloor.put(ALL_IMAGE, cameraID);

							isBrowseAllImage = true;
						}
						else
						{
							for (DIDLObject container : containers)
							{
								String id = container.getId();
								String title = container.getTitle();

								if (HttpServerUtil.isAllImages(title))
								{
									if (rc_dms_picture_bottom_layout != null)
										rc_dms_picture_bottom_layout.setVisibility(View.VISIBLE);

									imageBrowse(id, 0);

									rootFloor.put(ALL_IMAGE, id);

									isBrowseAllImage = true;
									break;
								}
							}
						}
					}

					if (!isBrowseAllImage)
					{
//						boolean isPhoto = false;
						for (DIDLObject container : containers)
						{
//							if("photo".equals(container.getTitle())){
//								System.out.println("The folder is:" + container.getTitle());
//								isPhoto = true;
//							}
							imageAdapter.add(PlaylistItem.createFromDLDIObject(container));
						}

						if (!items.isEmpty())
						{
							imageGridView.setNumColumns(4);

//							if(isPhoto){
							
								for (DIDLObject item : items)
								{
									imageAdapter.add(PlaylistItem.createFromDLDIObject(item));
								}
//							}
							
						}

						progressDismiss();
					}

					System.out.println("The haveNext:" + haveNext);
					if (haveNext) {
						Item item = new Item();
						item.setTitle(getContext().getString(R.string.load_more_result));
						item.setId("-1");
						imageAdapter.add(PlaylistItem.createFromDLDIObject(item));
					}
					System.out.println("The pictures size is:" + imageAdapter.getItemList().size());
					imageAdapter.notifyVisibleItemChanged(imageGridView);
				}
			});
		}
	};

	/**
	 * 视频浏览回调
	 */
	private DMSProcessorListner videoBrowseListener = new DMSProcessorListner() {

		@Override
		public void onBrowseFail(String message) {
			videoBrowseState = BrowseState.FAILURE;

			videoBrowseFailure(message);
		}

		private void videoBrowseFailure(String message) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					progressDismiss();
					video_traceID.remove(video_traceID.size() - 1);
				}
			});
		}

		@Override
		public void onBrowseComplete(String objectID, boolean haveNext, Map<String, List<? extends DIDLObject>> result) {
			videoBrowseState = BrowseState.SUCCESS;

			videoBrowseSuccess(objectID, haveNext, result);
		}

		private void videoBrowseSuccess(final String objectID, final boolean haveNext, final Map<String, List<? extends DIDLObject>> result) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					if (m_loadMore) {
						videoAdapter.remove(videoAdapter.getItem(videoAdapter.getCount() - 1));
						videoAdapter.notifyDataSetChanged();
					} else {
						setNewVideoAdapter();
					}

					secondFloor.put(objectID, result);

					List<? extends DIDLObject> containers = result.get("Containers");
					List<? extends DIDLObject> items = result.get("Items");

					boolean isBrowseAllVideo = false;
					if (firstFloor.containsKey(objectID) && objectID.equals(video_traceID.get(video_traceID.size() - 1)) && !containers.isEmpty())
					{
						String cameraID = ContentTree.VIDEO_FOLDER_PREFIX + Utility.getString(R.string.camera);
						Device device = UpnpProcessorImpl.getSington().getCurrentDMS();
						Container cameraContainer = ContentTree.getContainer(cameraID);

						if (device instanceof LocalDevice && cameraContainer != null && cameraContainer.getChildCount() != null && cameraContainer.getChildCount() != 0) {

							if (rc_dms_video_bottom_layout != null)
								rc_dms_video_bottom_layout.setVisibility(View.VISIBLE);

							videoBrowse(cameraID, 0);

							rootFloor.put(ALL_VIDEO, cameraID);

							isBrowseAllVideo = true;
						}
						else
						{
							for (DIDLObject container : containers)
							{
								String id = container.getId();
								String title = container.getTitle();
								if (HttpServerUtil.isAllVideos(title))
								{
									if (rc_dms_video_bottom_layout != null)
										rc_dms_video_bottom_layout.setVisibility(View.VISIBLE);

									videoBrowse(id, 0);

									rootFloor.put(ALL_VIDEO, id);

									isBrowseAllVideo = true;
									break;
								}
							}
						}
					}

					if (!isBrowseAllVideo)
					{
						for (DIDLObject container : containers)
						{
							videoAdapter.add(PlaylistItem.createFromDLDIObject(container));
						}

						for (DIDLObject item : items)
						{
							videoAdapter.add(PlaylistItem.createFromDLDIObject(item));
						}

						//						progressDismiss();
					}

					if (haveNext) {
						Item item = new Item();
						item.setTitle(getContext().getString(R.string.load_more_result));
						item.setId("-1");
						videoAdapter.add(PlaylistItem.createFromDLDIObject(item));
					}

					videoAdapter.notifyVisibleItemChanged(videoGridView);
				}
			});
		}
	};

	/**
	 * 音乐浏览回调
	 */
	private DMSProcessorListner musicBrowseListener = new DMSProcessorListner() {

		@Override
		public void onBrowseFail(String message) {
			musicBrowseState = BrowseState.FAILURE;

			musicBrowseFailure(message);
		}

		private void musicBrowseFailure(String message) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					progressDismiss();
					music_traceID.remove(music_traceID.size() - 1);
				}
			});
		}

		@Override
		public void onBrowseComplete(String objectID, boolean haveNext, Map<String, List<? extends DIDLObject>> result) {
			musicBrowseState = BrowseState.SUCCESS;

			musicBrowseSuccess(objectID, haveNext, result);
		}

		private void musicBrowseSuccess(final String objectID, final boolean haveNext, final Map<String, List<? extends DIDLObject>> result) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					if (m_loadMore) {
						musicAdapter.remove(musicAdapter.getItem(musicAdapter.getCount() - 1));
						musicAdapter.notifyDataSetChanged();
					} else {
						setNewMusicAdapter();
					}

					secondFloor.put(objectID, result);

					List<? extends DIDLObject> containers = result.get("Containers");
					List<? extends DIDLObject> items = result.get("Items");

					boolean isBrowseAllMusic = false;
					if (firstFloor.containsKey(objectID) && objectID.equals(music_traceID.get(music_traceID.size() - 1)) && !containers.isEmpty())
					{
						for (DIDLObject container : containers)
						{
							String id = container.getId();
							String title = container.getTitle();
							if (HttpServerUtil.isAllMusics(title))
							{
								if (rc_dms_music_bottom_layout != null)
									rc_dms_music_bottom_layout.setVisibility(View.VISIBLE);
								if (rc_dms_shuffle_play_layout != null)
									rc_dms_shuffle_play_layout.setVisibility(View.VISIBLE);

								musicBrowse(id, 0);

								rootFloor.put(ALL_MUSIC, id);

								isBrowseAllMusic = true;
								break;
							}
						}
					}

					if (!isBrowseAllMusic)
					{
						for (DIDLObject container : containers)
						{
							musicAdapter.add(PlaylistItem.createFromDLDIObject(container));
						}

						for (DIDLObject item : items)
						{
							musicAdapter.add(PlaylistItem.createFromDLDIObject(item));
						}

						//						progressDismiss();
					}

					if (haveNext) {
						Item item = new Item();
						item.setTitle(getContext().getString(R.string.load_more_result));
						item.setId("-1");
						musicAdapter.add(PlaylistItem.createFromDLDIObject(item));
					}

					musicAdapter.notifyVisibleItemChanged(musicGridView);
				}
			});
		}
	};

	private DevicesListener upnpListener = new DevicesListener() {

		@SuppressWarnings("rawtypes")
		@Override
		public void onDeviceAdded(Device device) {
			if (device.getType().getNamespace().equals("schemas-upnp-org")) {
				if (device.getType().getType().equals("MediaServer")) {
					addDMS(device);
				}
			}
		}

		@SuppressWarnings("rawtypes")
		@Override
		public void onDeviceRemoved(Device device) {
			if (device.getType().getNamespace().equals("schemas-upnp-org")) {
				if (device.getType().getType().equals("MediaServer")) {
					removeDMS(device);
				}
			}
		}

		@Override
		public void onDMSChanged() {
		}

		@Override
		public void onDMRChanged() {
		}

		@Override
		public void onDeviceUpdate(Device device) {
			// TODO Auto-generated method stub

		}
	};

	@SuppressWarnings("rawtypes")
	private void addDMS(final Device device) {
		runOnUiThread(new Runnable() {

			@Override
			public void run() {
				synchronized (dmsDeviceAdapter) {
					addAdapterDMS(device);
					Toast.makeText(getContext(), Utility.getDMSToastName(device.getDetails().getFriendlyName()), Toast.LENGTH_SHORT).show();
				}
			}

		});
	}

	private void addAdapterDMS(final Device device) {
		//		System.out.println("The dms name is:" + device.getDetails().getFriendlyName());
		//		List<Device> devices = dmsDeviceAdapter.getItemList();
		//		for(Device item:devices){
		//			if(item.getDetails().getFriendlyName().equals(device.getDetails().getFriendlyName())){
		//				dmsDeviceAdapter.getItemList().remove(item);
		//				break;
		//			}
		//		}
		if (device instanceof LocalDevice)
		{
			System.out.println("The dms is local dms");
			if (UpnpProcessorImpl.getSington().getCurrentDMS() == null)
			{
				UDN udn = device.getIdentity().getUdn();
				UpnpProcessorImpl.getSington().setCurrentDMS(udn);
			}
			dmsDeviceAdapter.insert(device, 0);
		}
		else
		{
			dmsDeviceAdapter.add(device);
		}
	}

	private void myAddAdapterDMS(final Device device){
		System.out.println("The dms name2 is:" + device.getDetails().getFriendlyName());
		List<Device> devices = dmsDeviceAdapter.getItemList();
		for(Device item:devices){
			if(item.getDetails().getFriendlyName().equals(device.getDetails().getFriendlyName())){
				System.out.println("The dms 2 return:" + device.getDetails().getFriendlyName());
				return;
			}
		}
		if (device instanceof LocalDevice)
		{
			System.out.println("The dms2 is local dms");
			if (UpnpProcessorImpl.getSington().getCurrentDMS() == null)
			{
				UDN udn = device.getIdentity().getUdn();
				UpnpProcessorImpl.getSington().setCurrentDMS(udn);
			}
			dmsDeviceAdapter.insert(device, 0);
		}
		else
		{
			dmsDeviceAdapter.add(device);
		}
	}

	@SuppressWarnings("rawtypes")
	private void removeDMS(final Device device) {
		runOnUiThread(new Runnable() {

			@Override
			public void run() {
				synchronized (dmsDeviceAdapter) {
					dmsDeviceAdapter.remove(device);
				}
			}
		});
	}

	public void onResume() {
		unlockImage();
		//		deviceBrowse(UpnpProcessorImpl.getSington().getCurrentDMS());
		//		updateGridView();
		updateHeaderTitle();

		isStop = false;
		UpnpProcessorImpl.getSington().addPlaylistListener(m_playlistListener);
		if(musicAdapter!=null&&musicGridView!=null)
			musicAdapter.notifyVisibleItemChanged(musicGridView);
	}

	private void updateGridView() {
		imageAdapter.notifyVisibleItemChanged(imageGridView);
		videoAdapter.notifyVisibleItemChanged(videoGridView);
		musicAdapter.notifyVisibleItemChanged(musicGridView);
	}

	/**
	 * 刷新 title所显示DMS设备
	 */
	private void updateHeaderTitle() {
		if (rc_dms_header_title != null) {
			if (UpnpProcessorImpl.getSington().getCurrentDMS() instanceof RemoteDevice) {
				Device device = UpnpProcessorImpl.getSington().getCurrentDMS();
				rc_dms_header_title.setText(Utility.getDeviceFriendlyName(device.getDetails().getFriendlyName()));
			} else {
				rc_dms_header_title.setText(R.string.myphone);
			}
		}
	}

	public void onPause() {
		isStop = true;
		UpnpProcessorImpl.getSington().removePlaylistListener(m_playlistListener);
	}

	protected PlaylistListener m_playlistListener = new PlaylistListener() {

		@Override
		public void onItemChanged(PlaylistItem item, ChangeMode changeMode) {

			playlistItemChanged(item, changeMode);
		}
	};

	protected void playlistItemChanged(final PlaylistItem item, final ChangeMode changeMode) {
		if (isStop)
			return;

		final DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();

		if (dmrProcessor == null)
			return;

		if (item == null) {
			dmrProcessor.stop();
			return;
		}

		if (item.getData() instanceof AudioItem) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					if (ChangeMode.UNKNOW != changeMode)
						dmrProcessor.setURIandPlay(item);
					musicAdapter.notifyDataSetChanged();
				}
			});
		}
	}

	public void onDestroy() {
		UpnpProcessorImpl.getSington().removeDevicesListener(upnpListener);
		UpnpProcessorImpl.getSington().setPlaylistProcessor(null);

		imageAdapter.clear();
		imageAdapter = null;
		videoAdapter.clear();
		videoAdapter = null;
		musicAdapter.clear();
		musicAdapter = null;
		NativeImageLoader.getInstance().clearCache();
	}

	private void setNewPictureAdapter() {
		imageAdapter = new BrowseImageAdapter(getContext());
		imageAdapter.setNotifyOnChange(false);
		if (null != imageGridView) {
			imageGridView.setNumColumns(1);
			imageGridView.setAdapter(imageAdapter);
		}
	}

	private void setNewVideoAdapter() {
		videoAdapter = new BrowseVideoAdapter(getContext());
		videoAdapter.setNotifyOnChange(false);
		if (null != videoGridView) {
			videoGridView.setNumColumns(1);
			videoGridView.setAdapter(videoAdapter);
		}
	}

	private void setNewMusicAdapter() {
		musicAdapter = new BrowseMusicAdapter(getContext());
		musicAdapter.setNotifyOnChange(false);
		if (null != musicGridView) {
			musicGridView.setNumColumns(1);
			musicGridView.setAdapter(musicAdapter);
		}
	}

	public boolean backTo() {
		return upOneLevel();
	}

	private boolean upOneLevel() {
		progressShow();

		if (UpnpProcessorImpl.getSington().getDMSProcessor() != null) {

			if (imageView.getCurrentPosition() == 0 && rootFloor.get(ALL_IMAGE) == null)
			{
				return UpnpProcessorImpl.getSington().getDMSProcessor().back(image_traceID, AppPreference.getMaxItemPerLoad(), imageBrowseListener);
			}
			else if(imageView.getCurrentPosition() == 1 && rootFloor.get(ALL_VIDEO) == null)
			{
				return UpnpProcessorImpl.getSington().getDMSProcessor().back(video_traceID, AppPreference.getMaxItemPerLoad(), videoBrowseListener);
			}
			else if(imageView.getCurrentPosition() == 2 && rootFloor.get(ALL_MUSIC) == null)
			{
				return UpnpProcessorImpl.getSington().getDMSProcessor().back(music_traceID, AppPreference.getMaxItemPerLoad(), musicBrowseListener);
			}
		}
		return false;
	}
}
