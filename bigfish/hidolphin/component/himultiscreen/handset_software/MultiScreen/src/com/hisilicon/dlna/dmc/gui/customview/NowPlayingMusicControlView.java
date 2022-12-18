package com.hisilicon.dlna.dmc.gui.customview;

import org.teleal.cling.model.ModelUtil;
import org.teleal.cling.model.message.UpnpResponse;
import org.teleal.cling.model.meta.Action;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
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
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.R;

public class NowPlayingMusicControlView extends LinearLayout {
	protected static final String TAG = NowPlayingMusicControlView.class.getName();
	private int m_playingState;
	private static final int STATE_PLAYING = 0;
	private static final int STATE_PAUSE = 1;
	private static final int STATE_STOP = 2;
	
	private boolean m_isSeeking = false;
	
	private TextView m_tv_current;
	private TextView m_tv_max;
	private ImageView m_btn_playPause, m_btn_next, m_btn_prev;
	private SeekBar m_sb_duration;
	private LinearLayout m_ll_seekControl;
	
	public NowPlayingMusicControlView(Context context) {
		super(context);
		initComponents();
	}

	public NowPlayingMusicControlView(Context context, AttributeSet attrs) {
		super(context, attrs);
		initComponents();
	}
	
	private void initComponents() {
		((LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE)).inflate(R.layout.playingmusic_control, this);
		
		m_tv_current = (TextView) findViewById(R.id.tv_current);
		m_tv_max = (TextView) findViewById(R.id.tv_max);

		m_btn_prev = (ImageView) findViewById(R.id.rc_previous);
		m_btn_prev.setOnClickListener(onPrevClick);
		m_btn_playPause = (ImageView) findViewById(R.id.rc_playorpause);
		m_btn_playPause.setOnClickListener(onPlayPauseClick);
		m_btn_next = (ImageView) findViewById(R.id.rc_next);
		m_btn_next.setOnClickListener(onNextClick);
		
		LinearLayout rc_music_bottom_layout = (LinearLayout) findViewById(R.id.rc_music_bottom_layout);
		int padding = (int) Utility.getWidthScaleWithBaseScreen(60);
		rc_music_bottom_layout.setPadding(padding, 0, padding, 0);
		
		ImageView rc_music_button_line = (ImageView) findViewById(R.id.rc_music_button_line);
		int margin = (int) Utility.getWidthScaleWithBaseScreen(50);
		LinearLayout.LayoutParams layoutParams = (LayoutParams) rc_music_button_line.getLayoutParams();
		layoutParams.leftMargin = margin;
		layoutParams.rightMargin = margin;
		rc_music_button_line.setLayoutParams(layoutParams);

		m_sb_duration = (SeekBar) findViewById(R.id.sb_duration);
		m_sb_duration.setOnSeekBarChangeListener(onSeekListener);

		m_ll_seekControl = (LinearLayout) findViewById(R.id.ll_seekControl);
	}
	
	private OnClickListener onPlayPauseClick = new OnClickListener() {

		@Override
		public void onClick(View v) {
			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
			switch (m_playingState) {
			case STATE_PAUSE:
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
	
	private OnClickListener onNextClick = new OnClickListener() {

		@Override
		public void onClick(View v) {
			doNext();
		}
	};
	
	private void doNext() {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (playlistProcessor != null)
			playlistProcessor.next();
	}

	private OnClickListener onPrevClick = new OnClickListener() {

		@Override
		public void onClick(View v) {
			doPrev();
		}
	};
	
	private void doPrev() {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (playlistProcessor != null)
			playlistProcessor.previous();
	}
	
	private OnSeekBarChangeListener onSeekListener = new OnSeekBarChangeListener() {

		@Override
		public void onStopTrackingTouch(SeekBar seekBar) {
			m_isSeeking = false;
			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
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
		public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
			if (seekBar.equals(m_sb_duration))
				m_tv_current.setText(ModelUtil.toTimeString(m_sb_duration.getProgress()));
		}
	};
	
	public DMRProcessorListener m_dmrListener = new DMRProcessorListener() {

		@Override
		public void onUpdatePosition(final long current, final long max) {
			if (m_isSeeking)
				return;
			final String currentText = ModelUtil.toTimeString(current);
			final String maxText = ModelUtil.toTimeString(max);
			((Activity) getContext()).runOnUiThread(new Runnable() {

				@Override
				public void run() {
					m_tv_current.setText(currentText);
					m_tv_max.setText(maxText);
					m_sb_duration.setMax((int) max);
					m_sb_duration.setProgress((int) current);
					m_sb_duration.invalidate();
				}
			});
		}

		@Override
		public void onStoped() {
			m_playingState = STATE_STOP;
			((Activity) getContext()).runOnUiThread(new Runnable() {

				@Override
				public void run() {
					m_btn_playPause.setImageDrawable(getContext().getResources().getDrawable(R.drawable.rc_media_pause));
					m_sb_duration.setProgress(0);
				}
			});
		}

		@Override
		public void onPlaying() {
			m_playingState = STATE_PLAYING;
			((Activity) getContext()).runOnUiThread(new Runnable() {

				@Override
				public void run() {
					m_btn_playPause.setImageDrawable(getContext().getResources().getDrawable(R.drawable.rc_media_play));
				}
			});

		}

		@Override
		public void onPaused() {
			m_playingState = STATE_PAUSE;
			((Activity) getContext()).runOnUiThread(new Runnable() {

				@Override
				public void run() {
					m_btn_playPause.setImageDrawable(getContext().getResources().getDrawable(R.drawable.rc_media_pause));
				}
			});

		}

		@Override
		public void onMiddleEndEvent() {
			
		};

		@Override
		public void onErrorEvent(final String error) {
			UpnpProcessorImpl.getSington().refreshDevicesList();

			Log.e(TAG, "error = " + error);

			((Activity) getContext()).runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Toast.makeText(getContext(), error, Toast.LENGTH_LONG).show();
				}
			});
		}

		@SuppressWarnings("rawtypes")
		@Override
		public void onActionFail(Action actionCallback, final UpnpResponse response, final String cause) {
		}

		@Override
		public void onCompleted() {
			// TODO Auto-generated method stub
			
		}
	};
}
