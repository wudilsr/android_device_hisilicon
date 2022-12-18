package com.hisilicon.dlna.dmc.processor.impl;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

import org.teleal.cling.model.ModelUtil;
import org.teleal.cling.support.model.DIDLObject;

import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnPreparedListener;
import android.media.MediaPlayer.OnSeekCompleteListener;
import android.view.SurfaceHolder;

import com.hisilicon.dlna.dmc.gui.activity.AppPreference;
import com.hisilicon.dlna.dmc.gui.customview.LocalMediaPlayer;
import com.hisilicon.dlna.dmc.gui.customview.LocalMediaPlayer.ViewChange;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem.Type;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;

public class LocalDMRProcessorImpl implements DMRProcessor {
	private static final int SLEEP_INTERVAL = 1000;
	
	private static final int STATE_PLAYING = 0;
	private static final int STATE_STOPED = 1;
	private static final int STATE_PAUSED = 2;
	private static String itemId = null;
	private int m_currentState;
	
	private List<DMRProcessorListener> m_listeners;
	public static  LocalMediaPlayer m_player;
	private SurfaceHolder m_holder = null;
	
	private PlaylistItem m_currentItem;
	
	private AudioManager m_audioManager;
	private int m_maxVolume;
	private int m_currentPosition;
	
	
	private UpdateThread m_updateThread;
	private boolean isSeeked;
	
	public static void setItemId(String id){
		itemId = id;
	}

	private class UpdateThread extends Thread {

		private boolean running = false;

		public UpdateThread() {
			running = true;
		}

		public void stopThread() {
			running = false;
			this.interrupt();
		}

		@Override
		public void run() {
			while (running && m_player != null) {
				try {
					if (m_player != null && m_player.isPlaying()) {
						int currentPosition = (int) (m_player.getCurrentPosition() / 1000);
						m_currentPosition = currentPosition;
						int duration = m_player.getDuration() / 1000;
						
						fireUpdatePositionEvent(currentPosition, duration);
						m_currentState = STATE_PLAYING;
					}
					switch (m_currentState) {
					case STATE_PLAYING:
						m_currentItem.setPlayStatue(1);
						fireOnPlayingEvent();
						break;
					case STATE_PAUSED:
						m_currentItem.setPlayStatue(2);
						fireOnPausedEvent();
						break;
					case STATE_STOPED:
						m_currentItem.setPlayStatue(0);
						fireOnStopedEvent();
						break;
					}
					try {
						Thread.sleep(SLEEP_INTERVAL);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					if (!running)
						break;
				} catch (Exception ex) {
					ex.printStackTrace();
					running = false;
					if (m_player != null) {
						try {
							m_player.reset();
							m_player.release();
						} catch (Exception e) {

						} finally {
							m_player = null;
						}
					}
					fireOnStopedEvent();
					PlaylistProcessor m_playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
					if (m_playlistProcessor != null)
						m_playlistProcessor.next();
					break;
				}
			}
		}
	}

	public LocalDMRProcessorImpl(Context context) {
		m_listeners = new ArrayList<DMRProcessor.DMRProcessorListener>();
		m_currentItem = new PlaylistItem();
		m_audioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
		m_maxVolume = m_audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
		m_updateThread = new UpdateThread();
		m_updateThread.start();
	}

	@Override
	public void setURIandPlay(final PlaylistItem item) {
		System.out.println("---come into setURIandPlay---");
		System.out.println("------Position:" + AppPreference.getPlayPosition());
		if (item == null) {
			m_currentItem = null;
			stop();
			return;
		}
			if(itemId!=null){
//				System.out.println("is not null");
				if(!itemId.equals(item.getId())){
					if(item.isRemotePlay()){
						itemId = item.getId();
						item.setRemotePlay(false);
					}else{
//						System.out.println("itemId not equal it id itemId:" + itemId + "  item id:" + item.getId());
						AppPreference.setPlayPosition(0);
						m_currentPosition = 0;
						itemId = item.getId();
					}
				}
			}else{
				AppPreference.setPlayPosition(0);
				itemId = item.getId();
			}
		
//		if(m_currentState==STATE_PLAYING)
//			item.setPlayStatue(1);
//		else if(m_currentState==STATE_PAUSED)
//			item.setPlayStatue(2);
//		else if(m_currentState==STATE_STOPED)
//			item.setPlayStatue(0);
		if (m_currentItem != null && m_currentItem.equals(item) && m_currentState != STATE_STOPED)
			return;
		
		System.out.println("----second way----");
		m_currentItem = item;
		
		setRunning(true);
		
		switch (m_currentItem.getType()) {
		case IMAGE_LOCAL:
		case IMAGE_REMOTE:
		case UNKNOW:
			stop();
			break;
		default:
//			new Thread(new Runnable() {
//
//				@Override
//				public void run() {
					stop();
//			clearPlay();
						m_player = new LocalMediaPlayer();
						m_player.setDisplay(m_holder);
						m_player.setOnPreparedListener(m_preparedListener);
						m_player.setOnCompletionListener(m_completeListener);
						m_player.setOnErrorListener(m_onErrorListener);
						m_player.setScreenOnWhilePlaying(true);
						m_player.setOnSeekCompleteListener(new SeekCompleteListener());
						synchronized (m_currentItem)
						{
							try
							{
								if (m_player != null)
								{
									m_player.setDataSource(m_currentItem.getUrl());
									m_player.prepareAsync();

//									int position = AppPreference.getPlayPosition();
//									System.out.println("The position:" + position);
//									if (position > 0)
//									{
//										playingSeek(ModelUtil.toTimeString(position));
//										AppPreference.setPlayPosition(0);
//									}
								}

							}catch (Exception e){
								e.printStackTrace();
							}
						}
					
//				}
//			}).start();
			break;
		}
	}
	
	private class SeekCompleteListener implements OnSeekCompleteListener{

		@Override
		public void onSeekComplete(MediaPlayer mp) {
			// TODO Auto-generated method stub
//			mp.start();
		}
		
	}

	private OnPreparedListener m_preparedListener = new OnPreparedListener() {

		@Override
		public void onPrepared(MediaPlayer mp) {
//			if (item.equals(m_currentItem))
//			{
			/**
				System.out.println("---equal-m_currentItem--");
				synchronized (m_currentItem)
				{
					try
					{
						if (m_player != null)
						{
							m_player.setDataSource(m_currentItem.getUrl());
							m_player.prepareAsync();

							int position = AppPreference.getPlayPosition();
							System.out.println("The position:" + position);
							if (position > 0)
							{
								playingSeek(ModelUtil.toTimeString(position));
								AppPreference.setPlayPosition(0);
							}
						}

					}catch (Exception e){
						e.printStackTrace();
					}
				}*/
//			}
			int position = AppPreference.getPlayPosition();
			System.out.println("The position:" + position);
			if (position > 0)
			{
				playingSeek(ModelUtil.toTimeString(position));
//				AppPreference.setPlayPosition(0);
			}
			m_currentItem.setPlayStatue(1);
			mp.start();
			setRunning(true);
			m_currentState = STATE_PLAYING;
		}

	};

	private OnCompletionListener m_completeListener = new OnCompletionListener() {

		@Override
		public void onCompletion(MediaPlayer mp) {
			mp.reset();
			AppPreference.setPlayPosition(0);
			m_currentPosition = 0;
			fireOnCompleteEvent();
//			PlaylistProcessor m_playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
//			if (m_playlistProcessor != null && AppPreference.getAutoNext())
//				m_playlistProcessor.next();
		}
	};

	private OnErrorListener m_onErrorListener = new OnErrorListener() {

		@Override
		public boolean onError(MediaPlayer mp, int what, int extra) {
			if (m_player != null) {
				m_player.reset();
				m_player.release();
				m_player = null;
				setRunning(false);
			}

			PlaylistProcessor m_playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
			if (m_playlistProcessor != null)
				m_playlistProcessor.next();

			return true;
		}
	};

	@Override
	public void play() {
		try {
			if (m_player != null)
				m_player.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private void playingSeek(final String time) {
//		Thread thread = new Thread(new Runnable() {
//			
//			@Override
//			public void run() {
//				while(!isSeeked) {
					try {
						TimeUnit.SECONDS.sleep(1);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					
//					if (m_currentState == STATE_PLAYING) {
						seek(time);
						isSeeked = true;
//						break;
//					}
					
//				}
				
//			}
//		});
		
//		thread.start();
	}

	@Override
	public void pause() {
		if (m_player != null && m_player.isPlaying())
			try {
				if (m_currentPosition != 0)
					AppPreference.setPlayPosition(m_currentPosition);
				m_player.pause();
				m_currentState = STATE_PAUSED;
			} catch (Exception ex) {
				ex.printStackTrace();
			}
	}

	@Override
	public void stop() {
		if (m_player != null)
		{
			try
			{
				if (m_currentPosition != 0)
					AppPreference.setPlayPosition(m_currentPosition);
				m_currentItem.setPlayStatue(0);
				m_player.reset();
				m_player.release();
				m_player = null;
				m_currentState = STATE_STOPED;
			}
			catch (Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	
	private void clearPlay(){
		if (m_player != null)
		{
			try
			{
				m_player.reset();
				m_player.release();
				m_player = null;
				m_currentState = STATE_STOPED;
			}
			catch (Exception e)
			{
				e.printStackTrace();
			}
		}
	}

	@Override
	public void seek(String position) {
		try {
			long miliSec = ModelUtil.fromTimeString(position) * 1000;
			m_player.seekTo((int) miliSec);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	@Override
	public void setVolume(int newVolume) {
		try {
			m_audioManager.setStreamVolume(AudioManager.STREAM_MUSIC, newVolume, AudioManager.FLAG_VIBRATE);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	@Override
	public int getVolume() {
		return m_audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
	}

	@Override
	public int getMaxVolume() {
		return m_maxVolume;
	}

	@Override
	public void addListener(DMRProcessorListener listener) {
		synchronized (m_listeners) {
			if (m_listeners.contains(listener)) {
				m_listeners.remove(listener);
			}
			m_listeners.add(listener);
			setRunning(true);
		}
	}

	@Override
	public void removeListener(DMRProcessorListener listener) {
		synchronized (m_listeners) {
			m_listeners.remove(listener);
		}
	}

	@Override
	public void dispose() {
		synchronized (m_listeners) {
			m_listeners.clear();
		}
		
		stop();
			
		isSeeked = true;
		
		if (m_updateThread != null) {
			m_updateThread.stopThread();
			m_updateThread = null;
		}
	}

	@Override
	public String getName() {
		return "Local Player";
	}

	@Override
	public String getCurrentTrackURI() {
		return m_currentItem != null ? (m_currentItem.getData() instanceof DIDLObject ? HttpServerUtil.getUrlFrom((DIDLObject) m_currentItem.getData()) : m_currentItem.getUrl()) : "";
	}

	@Override
	public void setRunning(boolean running) {
		if (m_updateThread != null) {
			m_updateThread.stopThread();
			m_updateThread = null;
		}
		
		if (running) {
			m_updateThread = new UpdateThread();
			m_updateThread.start();
		}
	}

	private void fireUpdatePositionEvent(long current, long max) {
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onUpdatePosition(current, max);
			}
		}
	}

	private void fireOnStopedEvent() {
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onStoped();
			}
		}
	}
	
	private void fireOnCompleteEvent(){
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onCompleted();
			}
		}
	}

	private void fireOnPausedEvent() {
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onPaused();
			}
		}
	}

	private void fireOnPlayingEvent() {
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onPlaying();
			}
		}
	}

	public void setHolder(SurfaceHolder holder, ViewChange playBack) {
		m_holder = holder;
		if (m_player != null) {
			m_player.setDisplay(holder, playBack);
			m_player.scaleContent();
		}
	}

	@Override
	public PlaylistItem getCurrentItem() {
		return m_currentItem;
	}
}
