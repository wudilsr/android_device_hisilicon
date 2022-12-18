package com.hisilicon.dlna.dmc.gui.activity;

import org.teleal.cling.model.message.UpnpResponse;
import org.teleal.cling.model.meta.Action;
import org.teleal.cling.model.meta.Device;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationUtils;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.TextView;

import com.hisilicon.dlna.dmc.gui.customview.DMSBrowseView;
import com.hisilicon.dlna.dmc.gui.customview.LocalMediaPlayer;
import com.hisilicon.dlna.dmc.gui.customview.LocalMediaPlayer.ViewChange;
import com.hisilicon.dlna.dmc.gui.customview.NowPlayingVideoControlView;
import com.hisilicon.dlna.dmc.processor.impl.LocalDMRProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.PlaylistManager;
import com.hisilicon.dlna.dmc.processor.impl.RemoteDMRProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor.DMRProcessorListener;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.ChangeMode;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.PlaylistListener;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.CoreUpnpService;
import com.hisilicon.dlna.dmc.utility.PrefConfig;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.R;

public class PlayingVideoActivity extends Activity {
	private Activity activity;
	private NowPlayingVideoControlView m_rendererControl;
	private TextView m_viewFlipper;
	private SurfaceView m_surface;
	private boolean m_isPausing;
	private FrameLayout m_content;
	private RelativeLayout rc_playing_top;
	private LinearLayout device_not_found_layout;
	private ImageView rc_push;
	private LinearLayout rc_dmr_pushing;
	private TextView rc_dmr_name;

	private volatile boolean isStop = false;
	private Handler myHandler = new Handler();
	
	private PlaylistItem currentItem;
	
	private boolean isLongClick = false;
	private volatile boolean isFirstChange = false;
	private boolean isMiddleEnd = false;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		activity = this;
		isLongClick = getIntent().getBooleanExtra(DMSBrowseView.LONGCLICK, false);
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_playingvideo);
		initializeComponents();
	}

	public void initializeComponents() {
		m_rendererControl = (NowPlayingVideoControlView) findViewById(R.id.rendererControlView);
		m_content = (FrameLayout) findViewById(R.id.rc_content);
		
		boolean isPlayFirst = PrefConfig.getBooleanPreferences("isPlayFirst");
		if (!isPlayFirst) {
			setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
			m_content.setLayoutParams(new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
			final LinearLayout rc_video_guid_layout = (LinearLayout) findViewById(R.id.rc_video_guid_layout);
			rc_video_guid_layout.setOnTouchListener(new OnTouchListener() {
				
				@Override
				public boolean onTouch(View v, MotionEvent event) {
					rc_video_guid_layout.removeAllViews();
					return true;
				}
			});
			((LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE)).inflate(R.layout.playingvideo_guide_land, rc_video_guid_layout);
			PrefConfig.setBooleanPreferences("isPlayFirst", true);
		}

		rc_playing_top = (RelativeLayout) findViewById(R.id.rc_playing_top);
		device_not_found_layout = (LinearLayout) findViewById(R.id.device_not_found_layout);
		rc_push = (ImageView) findViewById(R.id.rc_push);
		
		rc_dmr_pushing = (LinearLayout) findViewById(R.id.rc_dmr_pushing);
		rc_dmr_pushing.setOnTouchListener(slideTouch);
		rc_dmr_name = (TextView) findViewById(R.id.rc_dmr_name);

		m_surface = (SurfaceView) findViewById(R.id.surface);
		m_content.setOnTouchListener(slideTouch);
		m_surface.getHolder().addCallback(m_surfaceCallback);
		m_surface.getHolder().setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);

		m_viewFlipper = (TextView) findViewById(R.id.viewFlipper);

		updateItemInfo();
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

	public void onPushClick(final View view) {
		DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
		if (dmrProcessor instanceof LocalDMRProcessorImpl)
		{
			Device device = UpnpProcessorImpl.getSington().getCurrentDMR();
			if (device != null)
			{
				((ImageView) findViewById(R.id.rc_push)).setImageResource(R.drawable.rc_push_down);
				UpnpProcessorImpl.getSington().setCurrentDMR(device.getIdentity().getUdn());
				updateItemInfo();
			}
			else
			{
				warnLayoutFlash();
			}
		}
		else
		{
			((ImageView) findViewById(R.id.rc_push)).setImageResource(R.drawable.rc_push_up);
			UpnpProcessorImpl.getSington().setCurrentDMR(null);
			updateItemInfo();
		}
	}
	
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
	
	public void onResizeClick(View view) {
		if (getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT)
		{
			setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
			m_content.setLayoutParams(new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
		}
		else
		{
			setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
			m_content.setLayoutParams(new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, 180));
		}
	}
	
	public void onBackClick(View view) {
		finish();
	}
	
	private OnTouchListener slideTouch = new OnTouchListener() {
		private static final int MIN_DISTANCE = 100;
		private static final int DOWN_TIME = 700;
		private float upX, downX, moveX, toX;
		
		@Override
		public boolean onTouch(View v, MotionEvent event) {
			switch (event.getAction()) {
			case MotionEvent.ACTION_DOWN: {
				downX = event.getX();
				moveX = downX;
				return true;
			}
			case MotionEvent.ACTION_MOVE: {
				toX = event.getX();
				
				float deltaX = moveX - toX;
				
				if (event.getEventTime() - event.getDownTime() < DOWN_TIME)
					if (Math.abs(deltaX) > MIN_DISTANCE) {
						SeekBar duration = (SeekBar) findViewById(R.id.sb_duration);
						if (duration != null)
							return duration.onTouchEvent(event);
					}
				return true;
			}
			case MotionEvent.ACTION_UP: {
				upX = event.getX();

				float deltaX = downX - upX;
				if (event.getEventTime() - event.getDownTime() < DOWN_TIME)
					if (Math.abs(deltaX) < MIN_DISTANCE) {
						toggleItemInfo();
					} else {
						SeekBar duration = (SeekBar) findViewById(R.id.sb_duration);
						if (duration != null)
							return duration.onTouchEvent(event);
					}
				return true;
			}
			}
			return false;
		}
	};

	private PlaylistListener m_playlistListener = new PlaylistListener() {

		public void onItemChanged(PlaylistItem item, final ChangeMode changeMode) {
			if (isStop)
				return;
			/**
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					updateItemInfo();

				}
			});
			*/
		}

	};

	public void updateItemInfo() {
//		System.out.println("-----updateItemInfo-----");
		DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();

		if (isLongClick)
		{
			Device device = UpnpProcessorImpl.getSington().getCurrentDMR();

			if (device == null)
			{
				if (dmrProcessor != null) {
					dmrProcessor.setRunning(false);
					dmrProcessor.stop();
				}

				warnLayoutFlash();
				((ImageView) findViewById(R.id.rc_push)).setImageResource(R.drawable.rc_push_up);
				m_surface.setVisibility(View.GONE);
				rc_dmr_pushing.setVisibility(View.VISIBLE);

				PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
				if (playlistProcessor == null)
					return;
				currentItem = playlistProcessor.getCurrentItem();
				if (currentItem != null) {
					m_viewFlipper.setText(currentItem.getTitle());
				}

				currentItem = null;

				return;
			}
			else
			{
				UpnpProcessorImpl.getSington().setCurrentDMR(device.getIdentity().getUdn());
				dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
			}
			AppPreference.setPlayPosition(0);
			PlaylistProcessor playlistProcessor = UpnpProcessorImpl
					.getSington().getPlaylistProcessor();
			LocalDMRProcessorImpl.setItemId(playlistProcessor.getCurrentItem().getId());
		}
		
		if (dmrProcessor == null)
		{
			UpnpProcessorImpl.getSington().setCurrentDMR(null);
			dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
		}

//		isLongClick = false;
			
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (playlistProcessor == null)
			return;
		currentItem = playlistProcessor.getCurrentItem();
		if (currentItem == null) {
			dmrProcessor.stop();
			return;
		}
		
		m_viewFlipper.setText(currentItem.getTitle());

		if (dmrProcessor instanceof RemoteDMRProcessorImpl) {
			isLongClick = false;
			((ImageView) findViewById(R.id.rc_push)).setImageResource(R.drawable.rc_push_down);
			dmrProcessor.setRunning(true);
			m_surface.setVisibility(View.GONE);
			rc_dmr_name.setText(Utility.getDMRPushName(dmrProcessor.getName()));
			rc_dmr_pushing.setVisibility(View.VISIBLE);
		} else {
			((ImageView) findViewById(R.id.rc_push)).setImageResource(R.drawable.rc_push_up);
			m_surface.setVisibility(View.VISIBLE);
			rc_dmr_pushing.setVisibility(View.GONE);
		}

		updateSurfaceView();
		dmrProcessor.setURIandPlay(currentItem);
		if(DMSBrowseActivity.firstLoad){
			DMSBrowseActivity.firstLoad = false;
			System.out.println("-----is first load pic----");
			updateItemInfo();
		}
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		isStop = false;
		m_isPausing = false;
		UpnpProcessorImpl.getSington().addDMRListener(m_dmrListener);
		UpnpProcessorImpl.getSington().addPlaylistListener(m_playlistListener);
		updateSurfaceView();
	}

	@Override
	protected void onPause() {
		super.onPause();
		isStop = true;
		m_isPausing = true;
		updateSurfaceView();
		UpnpProcessorImpl.getSington().removeDMRListener(m_dmrListener);
		UpnpProcessorImpl.getSington().removePlaylistListener(m_playlistListener);
	}

	private DMRProcessorListener m_dmrListener = new DMRProcessorListener() {

		@Override
		public void onUpdatePosition(final long current, final long max) {
			m_rendererControl.m_dmrListener.onUpdatePosition(current, max);
		}

		@Override
		public void onStoped() {
			if(currentItem!=null)
				currentItem.setPlayStatue(0);
			m_rendererControl.m_dmrListener.onStoped();
		}

		@Override
		public void onPlaying() {
//			System.out.println("***onPlaying***");
			if (isMiddleEnd)
			{
				isMiddleEnd = false;
				DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
				if (dmrProcessor == null)
					return;
				dmrProcessor.pause();
			}
			if(currentItem!=null)
				currentItem.setPlayStatue(1);
			m_rendererControl.m_dmrListener.onPlaying();
		}

		@Override
		public void onPaused() {
//			System.out.println("***onPaused***");
			if(currentItem!=null)
				currentItem.setPlayStatue(2);
			m_rendererControl.m_dmrListener.onPaused();
		}

		@Override
		public void onMiddleEndEvent() {
			isMiddleEnd = true;
			finish();
//			runOnUiThread(new Runnable() {
//				public void run() {
//					onPushClick(null);
//				}
//			});
		}

		@Override
		public void onErrorEvent(final String error) {
			m_rendererControl.m_dmrListener.onErrorEvent(error);
		}

		@SuppressWarnings("rawtypes")
		@Override
		public void onActionFail(Action actionCallback,
				final UpnpResponse response, final String cause) {
		}

		@Override
		public void onCompleted() {
			// TODO Auto-generated method stub
			finish();
		}

	};

	@Override
	public void onBackPressed() {
		finish();
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		stopPlayer();
	}

	private void stopPlayer() {
		DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
		if (dmrProcessor instanceof LocalDMRProcessorImpl) {
			dmrProcessor.stop();
		}
	}

	private void updateSurfaceView() {
		try {
			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
			if (dmrProcessor instanceof LocalDMRProcessorImpl) {
				LocalDMRProcessorImpl localDMR = (LocalDMRProcessorImpl) dmrProcessor;
				if (m_isPausing) {
					localDMR.setHolder(null, null);
					localDMR.pause();
				} else {
					if (m_surface.getVisibility() == View.GONE) {
						localDMR.setHolder(null, null);
					} else {
						LocalMediaPlayer.surface_width = m_content.getWidth();
						LocalMediaPlayer.surface_height = m_content.getHeight();
						localDMR.setHolder(m_surface.getHolder(), new ViewChange() {

							@Override
							public void change(int target_width, int target_height) {
								if (!isFirstChange)
								{
									isFirstChange = true;
									resizeSurfaceView(LocalMediaPlayer.surface_width, LocalMediaPlayer.surface_height, LocalMediaPlayer.video_width, LocalMediaPlayer.video_height);
								}
								
							}
							
						});
					}
				}
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	private SurfaceHolder.Callback m_surfaceCallback = new Callback() {

		@Override
		public void surfaceDestroyed(SurfaceHolder holder) {
			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
			if (dmrProcessor instanceof LocalDMRProcessorImpl) {
				LocalDMRProcessorImpl localDMR = (LocalDMRProcessorImpl) dmrProcessor;
				localDMR.setHolder(null, null);
			}
		}

		@Override
		public void surfaceCreated(SurfaceHolder holder) {
			updateSurfaceView();
		}

		@Override
		public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
			updateSurfaceView();
		}
	};

	public void toggleItemInfo() {
		if (m_rendererControl != null)
			if (m_rendererControl.isShown()) {
				m_rendererControl.setVisibility(View.GONE);
				rc_playing_top.setVisibility(View.GONE);
				m_rendererControl.dismissVolume();
				getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
			} else {
				getWindow().clearFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
				m_rendererControl.setVisibility(View.VISIBLE);
				rc_playing_top.setVisibility(View.VISIBLE);
			}
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);

		int surface_width = m_content.getWidth();
		int surface_height = m_content.getHeight();

		int video_width = LocalMediaPlayer.video_width;
		int video_height = LocalMediaPlayer.video_height;

		if (Configuration.ORIENTATION_PORTRAIT == newConfig.orientation && m_content.getHeight() < m_content.getWidth())
		{
			surface_width = m_content.getHeight();
			surface_height = m_content.getWidth();
		}
		else if (Configuration.ORIENTATION_LANDSCAPE == newConfig.orientation && m_content.getHeight() > m_content.getWidth())
		{
			surface_width = m_content.getHeight();
			surface_height = m_content.getWidth();
		}

		resizeSurfaceView(surface_width, surface_height, video_width, video_height);

	}

	private void resizeSurfaceView(int surface_width, int surface_height, int video_width, int video_height)
	{
		if (surface_width != 0 && surface_width != 0 && video_width != 0 && video_height != 0)
		{
			float scale_width = (float) video_width / surface_width;
			float scale_height = (float) video_height / surface_height;

			float max_scale = scale_width > scale_height ? scale_width : scale_height;

			int target_width = (int) (video_width / max_scale);
			int target_height = (int) (video_height / max_scale);

			FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(target_width, target_height);
			layoutParams.gravity = Gravity.CENTER;
			m_surface.setLayoutParams(layoutParams);
		}
	}

	@Override
	public void finish() {
		// TODO Auto-generated method stub
		super.finish();
		AppPreference.setPlayPosition(0);
	}
	
	
}
