package com.hisilicon.dlna.dmc.gui.activity;

import java.net.URI;

import org.teleal.cling.model.message.UpnpResponse;
import org.teleal.cling.model.meta.Action;
import org.teleal.cling.model.meta.Device;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.item.AudioItem;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.hisilicon.dlna.dmc.gui.customview.DMSBrowseView;
import com.hisilicon.dlna.dmc.gui.customview.NowPlayingMusicControlView;
import com.hisilicon.dlna.dmc.processor.impl.ImageCallbackImpl;
import com.hisilicon.dlna.dmc.processor.impl.LocalDMRProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.PlaylistManager;
import com.hisilicon.dlna.dmc.processor.impl.RemoteDMRProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor.DMRProcessorListener;
import com.hisilicon.dlna.dmc.processor.interfaces.ImageCallback;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.ChangeMode;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.PlaylistListener;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.CoreUpnpService;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.R;
import com.hisilicon.multiscreen.widget.VerticalSeekBar;
import com.hisilicon.multiscreen.widget.VerticalSeekBar.OnVerticalSeekBarChangeListener;

public class PlayingMusicActivity extends Activity {
	private Activity activity;

	private int m_playingState;
	private static final int STATE_PLAYING = 0;
	private static final int STATE_PAUSE = 1;
	private static final int STATE_STOP = 2;

	private NowPlayingMusicControlView m_rendererControl;
	private TextView m_viewFlipper;
	private RelativeLayout rc_playing_top;
	private LinearLayout device_not_found_layout;

	private volatile boolean isStop = false;
	private LinearLayout rc_music_volume;
	private VerticalSeekBar m_sb_volume;
	private ImageView shuffleImage;

	private LinearLayout rc_album_art_default_layout;
	private ImageView rc_album_art_default;
	private TextView rc_singer;
	private LinearLayout rc_dmr_pushing;
	private TextView rc_dmr_name;
	
	private PlayHandler myPlayHandler = new PlayHandler();

	/*public static LinearLayout rc_album_lyric_default_layout;
	private LyricView rc_album_lyric_default;*/

	private PlaylistItem currentItem;

	private Handler myHandler = new Handler();

	private boolean isLongClick = false;
	private boolean isMiddleEnd = false;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		activity = this;
		isLongClick = getIntent().getBooleanExtra(DMSBrowseView.LONGCLICK,
				false);
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_playingmusic);
		initializeComponents();
	}

	public void initializeComponents() {
		m_rendererControl = (NowPlayingMusicControlView) findViewById(R.id.rendererControlView);
		rc_playing_top = (RelativeLayout) findViewById(R.id.rc_playing_top);
		device_not_found_layout = (LinearLayout) findViewById(R.id.device_not_found_layout);
		m_viewFlipper = (TextView) findViewById(R.id.viewFlipper);

		rc_album_art_default_layout = (LinearLayout) findViewById(R.id.rc_album_art_default_layout);
		rc_album_art_default = (ImageView) findViewById(R.id.rc_album_art_default);
		rc_singer = (TextView) findViewById(R.id.rc_singer);
		rc_dmr_pushing = (LinearLayout) findViewById(R.id.rc_dmr_pushing);
		rc_dmr_name = (TextView) findViewById(R.id.rc_dmr_name);

		/*rc_album_lyric_default_layout = (LinearLayout) findViewById(R.id.rc_album_lyric_default_layout);
		rc_album_lyric_default = (LyricView) findViewById(R.id.rc_album_lyric_default);
*/
		rc_music_volume = (LinearLayout) findViewById(R.id.rc_music_volume);
		m_sb_volume = (VerticalSeekBar) findViewById(R.id.sb_volume);
		m_sb_volume.setOnSeekBarChangeListener(onSeekListener);
		rc_playing_top.setBackgroundResource(R.drawable.header_green_toolbar);

		shuffleImage = (ImageView) findViewById(R.id.rc_music_shuffle);
		shuffleImage.setOnClickListener(shuffleClick);
		if (AppPreference.getShuffle())
		{
			shuffleImage.setImageResource(R.drawable.rc_shuffle_pressed);
		}
		else
		{
			shuffleImage.setImageResource(R.drawable.rc_shuffle_normal);
		}
		
		updateItemInfo();
	}

	public void showWarnLayout() {
		if (device_not_found_layout == null)
			return;
		Animation animation = AnimationUtils.loadAnimation(activity,
				R.anim.up_slidein);
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
		Animation animation = AnimationUtils.loadAnimation(activity,
				R.anim.up_slideout);
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
				((ImageView) findViewById(R.id.rc_push)).setImageResource(R.drawable.rc_push_music_down);
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
			((ImageView) findViewById(R.id.rc_push)).setImageResource(R.drawable.rc_push_music_up);
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

	public void onBackClick(View view) {
		finish();
	}

	private OnClickListener shuffleClick = new OnClickListener() {

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
	};

	private PlaylistListener m_playlistListener = new PlaylistListener() {

		public void onItemChanged(PlaylistItem item, final ChangeMode changeMode) {
			if (isStop)
				return;
			updateItemInfo();
//			runOnUiThread(new Runnable() {
//
//				@Override
//				public void run() {
//					updateItemInfo();
//
//				}
//			});

		}

	};

	public void updateItemInfo() {
		System.out.println("---updateItemInfo---");
		DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
//		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington()
//				.getPlaylistProcessor();
		if (isLongClick)
		{
			System.out.println("-----Long click-----");
			Device device = UpnpProcessorImpl.getSington().getCurrentDMR();

			if (device == null)
			{
				if (dmrProcessor != null) {
					dmrProcessor.setRunning(false);
					dmrProcessor.stop();
				}
				warnLayoutFlash();
				// rc_dmr_name.setText(Utility.getDMRPushName(dmrProcessor.getName()));
				rc_dmr_pushing.setVisibility(View.VISIBLE);
				rc_album_art_default_layout.setVisibility(View.GONE);
				rc_singer.setVisibility(View.GONE);

				((ImageView) findViewById(R.id.rc_push))
				.setImageResource(R.drawable.rc_push_music_up);

				PlaylistProcessor playlistProcessor = UpnpProcessorImpl
						.getSington().getPlaylistProcessor();
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

		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington()
				.getPlaylistProcessor();
		if (playlistProcessor == null)
			return;
		currentItem = playlistProcessor.getCurrentItem();
		if (currentItem == null) {
			dmrProcessor.stop();
			return;
		}

		m_viewFlipper.setText(currentItem.getTitle());
		m_sb_volume.setMax(dmrProcessor.getMaxVolume());
		m_sb_volume.setProgress(dmrProcessor.getVolume());

		if (dmrProcessor instanceof RemoteDMRProcessorImpl) {
			System.out.println("--------remot--------");
			isLongClick = false;
			dmrProcessor.setRunning(true);

			rc_dmr_name.setText(Utility.getDMRPushName(dmrProcessor.getName()));
			rc_dmr_pushing.setVisibility(View.VISIBLE);
			rc_album_art_default_layout.setVisibility(View.GONE);
			rc_singer.setVisibility(View.GONE);

			((ImageView) findViewById(R.id.rc_push))
					.setImageResource(R.drawable.rc_push_music_down);
			LocalDMRProcessorImpl.setItemId(playlistProcessor.getCurrentItem().getId());
//			AppPreference.setPlayPosition(0);
		} else {
			System.out.println("--------local--------");
			rc_dmr_pushing.setVisibility(View.GONE);
			rc_album_art_default_layout.setVisibility(View.VISIBLE);
			rc_singer.setVisibility(View.VISIBLE);
			((ImageView) findViewById(R.id.rc_push))
					.setImageResource(R.drawable.rc_push_music_up);

			rc_album_art_default.setImageResource(R.drawable.rc_album_art_default);

			Object object = currentItem.getData();
			if (object instanceof AudioItem) {
				AudioItem audio = (AudioItem) object;
				rc_singer.setText(audio.getCreator());

				URI uri = audio
						.getFirstPropertyValue(DIDLObject.Property.UPNP.ALBUM_ART_URI.class);
				if (null != uri) {
					String objectUrl = uri.toString();
					rc_album_art_default.setTag(objectUrl);
					ImageCallback callback = new ImageCallbackImpl(
							rc_album_art_default);
					Bitmap cachedImage = ThumbnailGenerator.getInstance()
							.returnBitMap(objectUrl, callback);

					if (null != cachedImage && !cachedImage.isRecycled())
						rc_album_art_default.setImageBitmap(cachedImage);
				}
			}
//			RemoteDMRProcessorImpl.setItemId(currentItem.getId());
		}

		System.out.println("The title is:" + currentItem.getTitle());
		dmrProcessor.setURIandPlay(currentItem);
		
		//SerchLrc(currentItem.getUrl());
		addItemToPlaylist();
		if(DMSBrowseActivity.firstLoad){
			DMSBrowseActivity.firstLoad = false;
			System.out.println("-----is first load pic----");
			updateItemInfo();
		}
	}

	private void addItemToPlaylist() {
		PlaylistManager.insertPlaylistItem(currentItem);
		sendBroadcast(new Intent(CoreUpnpService.PLAYLIST_CHANGED));
	}

	public void onVolumeClick(View view) {
		if (m_sb_volume.isShown()) {
			rc_music_volume.setBackgroundDrawable(null);
			m_sb_volume.setVisibility(View.GONE);
		} else {
			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington()
					.getDMRProcessor();
			if (dmrProcessor != null) {
				m_sb_volume.setMax(dmrProcessor.getMaxVolume());
				m_sb_volume.setProgress(dmrProcessor.getVolume());
			}
			rc_music_volume.setBackgroundResource(R.drawable.rc_volume_bg);
			m_sb_volume.setVisibility(View.VISIBLE);
			mVolumeHandler.sendEmptyMessageDelayed(1, 3000);
		}
	}
	
	private Handler mVolumeHandler = new Handler(){
		public static final int DISMISS_VOLUME = 1;

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			switch(msg.what){
			case DISMISS_VOLUME:
				if (m_sb_volume.isShown()) {
					rc_music_volume.setBackgroundDrawable(null);
					m_sb_volume.setVisibility(View.GONE);
				} 
				break;
			}
		}
		
	};
	
	private OnVerticalSeekBarChangeListener onSeekListener = new OnVerticalSeekBarChangeListener() {

		@Override
		public void onProgressChanged(VerticalSeekBar vBar, int progress,
				boolean fromUser) {

		}

		@Override
		public void onStartTrackingTouch(VerticalSeekBar vBar) {

		}

		@Override
		public void onStopTrackingTouch(VerticalSeekBar vBar) {
			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington()
					.getDMRProcessor();
			if (dmrProcessor == null)
				return;
			dmrProcessor.setVolume(vBar.getProgress());
		}
	};

	@Override
	protected void onResume() {
		super.onResume();
		isStop = false;
		UpnpProcessorImpl.getSington().addDMRListener(m_dmrListener);
		UpnpProcessorImpl.getSington().addPlaylistListener(m_playlistListener);
	}

	@Override
	protected void onPause() {
		super.onPause();
		isStop = true;
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
			if(currentItem!=null)
				currentItem.setPlayStatue(2);
			m_rendererControl.m_dmrListener.onPaused();
		}

		@Override
		public void onMiddleEndEvent() {
//			isMiddleEnd = true;
			System.out.println("come into onMiddleEndEvent");
//			onPlaying();
//			m_rendererControl.m_dmrListener.onPlaying();
//			updateItemInfo();
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
		public void onActionFail(Action actionCallback, final UpnpResponse response, final String cause) {
		}

		@Override
		public void onCompleted() {
			// TODO Auto-generated method stub
			System.out.println("----music completed----");
			myPlayHandler.sendEmptyMessage(PlayHandler.PLAY_NEXT);
		}
	};
	
	private class PlayHandler extends Handler{
		public final static int PLAY_NEXT = 1;

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			switch(msg.what){
				case PLAY_NEXT:
					PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
					if (playlistProcessor != null){
						playlistProcessor.next();
						LocalDMRProcessorImpl.setItemId(playlistProcessor.getCurrentItem().getId());
					}
//					updateItemInfo();
				break;
			}
		}
		
	}

	@Override
	public void onBackPressed() {
		finish();
	}

	public void toggleItemInfo() {
		if (m_rendererControl != null)
			if (m_rendererControl.isShown()) {
				m_rendererControl.setVisibility(View.GONE);
				rc_playing_top.setVisibility(View.GONE);
			} else {
				m_rendererControl.setVisibility(View.VISIBLE);
				rc_playing_top.setVisibility(View.VISIBLE);
			}
	}

	/*public void SerchLrc(String url) {

		String lrc = null;

		URL uri = null;

		if (url != null) {
			try {
				uri = new URL(url);
				lrc = uri.getPath();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		lrc = lrc.substring(0, lrc.length() - 4).trim() + ".lrc".trim();
		rc_album_lyric_default_layout.setVisibility(View.VISIBLE);
		LyricView.read(lrc);
		rc_album_lyric_default.setOffsetY(350);
	}

	Handler mHandler = new Handler();
	Runnable mUpdateResults = new Runnable() {
		public void run() {
			rc_album_lyric_default.invalidate(); // 更新视图
		}
	};

	private DMRProcessorListener m_dmrListener = new DMRProcessorListener() {

		@Override
		public void onUpdatePosition(final long current, final long max) {

			final String currentText = ModelUtil.toTimeString(current);
			final String maxText = ModelUtil.toTimeString(max);
			activity.runOnUiThread(new Runnable() {

				@Override
				public void run() {
					try {
						Thread.sleep(100);
						if (m_playingState == STATE_PLAYING) {
							rc_album_lyric_default.setOffsetY(rc_album_lyric_default
									.getOffsetY()
									- rc_album_lyric_default.SpeedLrc());
							rc_album_lyric_default.SelectIndex((int) current);

							mHandler.post(mUpdateResults);
						}
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			});
		}

		@Override
		public void onStoped() {
			m_playingState = STATE_STOP;

		}

		@Override
		public void onPlaying() {
			m_playingState = STATE_PLAYING;

		}

		@Override
		public void onPaused() {
			m_playingState = STATE_PAUSE;

		}

		@Override
		public void onErrorEvent(final String error) {
			UpnpProcessorImpl.getSington().refreshDevicesList();

			activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Toast.makeText(activity, error, Toast.LENGTH_LONG).show();
				}
			});
		}

		@SuppressWarnings("rawtypes")
		@Override
		public void onActionFail(Action actionCallback,
				final UpnpResponse response, final String cause) {
		}
	};*/
}
