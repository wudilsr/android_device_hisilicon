package com.hisilicon.dlna.dmc.gui.customview;

import org.teleal.cling.model.ModelUtil;
import org.teleal.cling.model.message.UpnpResponse;
import org.teleal.cling.model.meta.Action;

import android.app.Activity;
import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor.DMRProcessorListener;
import com.hisilicon.multiscreen.mybox.R;
import com.hisilicon.multiscreen.widget.VerticalSeekBar;
import com.hisilicon.multiscreen.widget.VerticalSeekBar.OnVerticalSeekBarChangeListener;

public class NowPlayingVideoControlView extends LinearLayout {

	private int m_playingState;
	private static final int STATE_PLAYING = 0;
	private static final int STATE__PAUSE = 1;
	private static final int STATE_STOP = 2;

	private boolean m_isSeeking = false;

	private TextView m_tv_current;
	private TextView tv_slash;
	private TextView m_tv_max;
	private ImageView m_btn_playPause;
	private LinearLayout rc_video_volume_layout;
	private ImageView volume;
	private VerticalSeekBar m_sb_volume;
	private SeekBar m_sb_duration;
	private UIHandler myUIHandler = new UIHandler();

	public NowPlayingVideoControlView(Context context) {
		super(context);
		initComponents();
	}

	public NowPlayingVideoControlView(Context context, AttributeSet attrs) {
		super(context, attrs);
		initComponents();
	}

	private void initComponents() {
		((LayoutInflater) getContext().getSystemService(
				Context.LAYOUT_INFLATER_SERVICE)).inflate(
				R.layout.playingvideo_control, this);

		m_tv_current = (TextView) findViewById(R.id.tv_current);
		tv_slash = (TextView) findViewById(R.id.tv_slash);
		m_tv_max = (TextView) findViewById(R.id.tv_max);

		m_btn_playPause = (ImageView) findViewById(R.id.rc_playorpause);
		m_btn_playPause.setOnClickListener(onPlayPauseClick);

		volume = (ImageView) findViewById(R.id.volume);
		volume.setOnClickListener(onVolumeClick);
		rc_video_volume_layout = (LinearLayout) findViewById(R.id.rc_video_volume_layout);
		m_sb_volume = (VerticalSeekBar) findViewById(R.id.sb_volume);
		m_sb_volume.setOnSeekBarChangeListener(onVolumeSeekListener);
		m_sb_duration = (SeekBar) findViewById(R.id.sb_duration);
		m_sb_duration.setOnSeekBarChangeListener(onSeekListener);

	}

	private OnClickListener onVolumeClick = new OnClickListener() {

		@Override
		public void onClick(View v) {
			System.out.println("come into onVolumeClick!!");
			if (m_sb_volume.isShown()) {
				m_sb_volume.setVisibility(View.INVISIBLE);
				rc_video_volume_layout.setBackgroundDrawable(null);
			} else {
				m_sb_volume.setVisibility(View.VISIBLE);
				rc_video_volume_layout
						.setBackgroundResource(R.drawable.rc_volume_bg);
				mVolumeHandler.sendEmptyMessageDelayed(1, 3000);
			}
		}
	};
	
	private Handler mVolumeHandler = new Handler(){
		public static final int DISMISS_VOLUME = 1;

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			switch(msg.what){
			case DISMISS_VOLUME:
				if (m_sb_volume.isShown()) {
					m_sb_volume.setVisibility(View.INVISIBLE);
					rc_video_volume_layout.setBackgroundDrawable(null);
				} 
				break;
			}
		}
		
	};

	public void dismissVolume() {
		m_sb_volume.setVisibility(View.INVISIBLE);
		rc_video_volume_layout.setBackgroundDrawable(null);
	}

	private OnClickListener onPlayPauseClick = new OnClickListener() {

		@Override
		public void onClick(View v) {
			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington()
					.getDMRProcessor();
			switch (m_playingState) {
			case STATE__PAUSE:
			case STATE_STOP:
				if (dmrProcessor != null)
					dmrProcessor.play();
				break;
			case STATE_PLAYING:
				if (dmrProcessor != null)
					dmrProcessor.pause();
				break;
			default:
				break;
			}
		}
	};

	private OnSeekBarChangeListener onSeekListener = new OnSeekBarChangeListener() {

		@Override
		public void onStopTrackingTouch(SeekBar seekBar) {
			m_isSeeking = false;
			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington()
					.getDMRProcessor();
			if (dmrProcessor == null)
				return;
			if (seekBar.equals(m_sb_duration)) {
				dmrProcessor.seek(ModelUtil.toTimeString(seekBar.getProgress()));
			} else {
				dmrProcessor.setVolume(seekBar.getProgress());
			}
		}

		@Override
		public void onStartTrackingTouch(SeekBar seekBar) {
			m_isSeeking = true;

		}

		@Override
		public void onProgressChanged(SeekBar seekBar, int progress,
				boolean fromUser) {
			if (seekBar.equals(m_sb_duration))
				m_tv_current.setText(ModelUtil.toTimeString(m_sb_duration
						.getProgress()));
		}
	};

	private OnVerticalSeekBarChangeListener onVolumeSeekListener = new OnVerticalSeekBarChangeListener() {

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

	public DMRProcessorListener m_dmrListener = new DMRProcessorListener() {

		@Override
		public void onUpdatePosition(final long current, final long max) {
			if (m_isSeeking)
				return;
			final String currentText = ModelUtil.toTimeString(current);
			final String maxText = ModelUtil.toTimeString(max);
//			System.out.println("The currentText:" + currentText + " maxText:" + maxText);
			((Activity) getContext()).runOnUiThread(new Runnable() {

				@Override
				public void run() {
					m_tv_current.setText(currentText);
					tv_slash.setVisibility(View.VISIBLE);
					m_tv_max.setText(maxText);
					m_sb_duration.setMax((int) max);
					m_sb_duration.setProgress((int) current);
					m_sb_duration.invalidate();
					DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington()
							.getDMRProcessor();
					if (dmrProcessor != null) {
						m_sb_volume.setMax(dmrProcessor.getMaxVolume());
//						System.out.println("Come into set volume progress:" + dmrProcessor.getVolume());
						m_sb_volume.setProgress(dmrProcessor.getVolume());
					}
				}
			});
		}

		@Override
		public void onStoped() {
			m_playingState = STATE_STOP;
			myUIHandler.sendEmptyMessage(myUIHandler.STOP);
			/**
			((Activity) getContext()).runOnUiThread(new Runnable() {

				@Override
				public void run() {
					m_btn_playPause.setImageDrawable(getContext()
							.getResources().getDrawable(
									R.drawable.rc_video_pause));
					m_sb_duration.setProgress(0);
				}
			});*/
		}

		@Override
		public void onPlaying() {
			m_playingState = STATE_PLAYING;
			myUIHandler.sendEmptyMessage(myUIHandler.PLAY);
			/**
			((Activity) getContext()).runOnUiThread(new Runnable() {

				@Override
				public void run() {
					m_btn_playPause.setImageDrawable(getContext()
							.getResources().getDrawable(
									R.drawable.rc_video_play));
				}
			});*/

		}

		@Override
		public void onPaused() {
			m_playingState = STATE__PAUSE;
			myUIHandler.sendEmptyMessage(myUIHandler.PAUSE);
			/**
			((Activity) getContext()).runOnUiThread(new Runnable() {

				@Override
				public void run() {
					m_btn_playPause.setImageDrawable(getContext()
							.getResources().getDrawable(
									R.drawable.rc_video_pause));
				}
			});*/

		}

		@Override
		public void onMiddleEndEvent() {
			
		};

		@Override
		public void onErrorEvent(final String error) {
			UpnpProcessorImpl.getSington().refreshDevicesList();

			((Activity) getContext()).runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Toast.makeText(getContext(), error, Toast.LENGTH_LONG)
							.show();
				}
			});
		}

		@SuppressWarnings("rawtypes")
		@Override
		public void onActionFail(Action actionCallback,
				final UpnpResponse response, final String cause) {
		}

		@Override
		public void onCompleted() {
			// TODO Auto-generated method stub
			
		}
	};
	
	private class UIHandler extends Handler{
		public static final int PAUSE = 1;
		public static final int STOP = 2;
		public static final int PLAY = 3;

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			switch(msg.what){
			case PAUSE:
				m_btn_playPause.setImageDrawable(getContext()
						.getResources().getDrawable(
								R.drawable.rc_video_pause));
				break;
			case STOP:
				m_btn_playPause.setImageDrawable(getContext()
						.getResources().getDrawable(
								R.drawable.rc_video_pause));
				m_sb_duration.setProgress(0);
				break;
			case PLAY:
				m_btn_playPause.setImageDrawable(getContext()
						.getResources().getDrawable(
								R.drawable.rc_video_play));
				break;
			}
		}
		
	}
}
