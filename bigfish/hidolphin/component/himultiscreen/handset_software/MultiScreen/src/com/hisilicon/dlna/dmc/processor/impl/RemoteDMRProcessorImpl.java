package com.hisilicon.dlna.dmc.processor.impl;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

import org.teleal.cling.controlpoint.ControlPoint;
import org.teleal.cling.model.ModelUtil;
import org.teleal.cling.model.action.ActionInvocation;
import org.teleal.cling.model.message.UpnpResponse;
import org.teleal.cling.model.meta.Action;
import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.Service;
import org.teleal.cling.model.types.ServiceType;
import org.teleal.cling.support.avtransport.callback.GetPositionInfo;
import org.teleal.cling.support.avtransport.callback.GetTransportInfo;
import org.teleal.cling.support.avtransport.callback.Pause;
import org.teleal.cling.support.avtransport.callback.Play;
import org.teleal.cling.support.avtransport.callback.Seek;
import org.teleal.cling.support.avtransport.callback.SetAVTransportURI;
import org.teleal.cling.support.avtransport.callback.Stop;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.PositionInfo;
import org.teleal.cling.support.model.SeekMode;
import org.teleal.cling.support.model.TransportInfo;
import org.teleal.cling.support.model.TransportState;
import org.teleal.cling.support.renderingcontrol.callback.GetVolume;
import org.teleal.cling.support.renderingcontrol.callback.SetVolume;

import android.util.Log;

import com.hisilicon.dlna.dmc.gui.activity.AppPreference;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem.Type;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;

public class RemoteDMRProcessorImpl implements DMRProcessor {
	private static final String TAG = RemoteDMRProcessorImpl.class.getName();

	private static final int UPDATE_INTERVAL = 1000;
	private static final int MAX_VOLUME = 100;
	private static final long SEEK_DELAY_INTERVAL = 200;
	private static final int AUTO_NEXT_DELAY = 4; // second

	@SuppressWarnings("rawtypes")
	private Device m_device;

	private ControlPoint m_controlPoint;

	@SuppressWarnings("rawtypes")
	private Service m_avtransportService = null;

	@SuppressWarnings("rawtypes")
	private Service m_renderingControl = null;

	private List<DMRProcessorListener> m_listeners;

	private int m_currentVolume;
	private int m_currentPosition;
	private TransportState m_currentState;
	private boolean m_isBusy = false;
	private boolean isSeeked = false;
	private volatile boolean imagePlay = false;
	private volatile boolean mediaPlay = false;
	private volatile boolean mediaNext = false;
	private volatile boolean mediaMiddleEnd = false;
	private boolean m_checkGetPositionInfo = false;
	private boolean m_checkGetTransportInfo = false;
	private boolean m_checkGetVolumeInfo = false;
	private int m_autoNextPending = AUTO_NEXT_DELAY;

	private PlaylistItem m_currentItem;
	private UpdateThread m_updateThread = null;

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
			while (running) {
				if (m_avtransportService == null)
					return;
				if (!m_checkGetPositionInfo) {
					m_checkGetPositionInfo = true;
					m_controlPoint.execute(new GetPositionInfo(m_avtransportService) {

						@SuppressWarnings("rawtypes")
						@Override
						public void failure(ActionInvocation invocation, UpnpResponse response, String defaultMsg) {
							fireOnFailEvent(invocation.getAction(), response, defaultMsg);
							m_checkGetPositionInfo = false;
						}

						@SuppressWarnings("rawtypes")
						@Override
						public void received(ActionInvocation invocation, PositionInfo positionInfo) {
							m_currentPosition = (int) positionInfo.getTrackElapsedSeconds();
							fireUpdatePositionEvent(positionInfo.getTrackElapsedSeconds(), positionInfo.getTrackDurationSeconds());
							m_checkGetPositionInfo = false;
						}
					});

				}

				if (!m_checkGetTransportInfo) {
					m_checkGetTransportInfo = true;
					m_controlPoint.execute(new GetTransportInfo(m_avtransportService) {
						@SuppressWarnings("rawtypes")
						@Override
						public void failure(ActionInvocation invocation, UpnpResponse operation, String defaultMsg) {
							fireOnFailEvent(invocation.getAction(), operation, defaultMsg);
							m_checkGetTransportInfo = false;
						}

						@SuppressWarnings("rawtypes")
						@Override
						public void received(ActionInvocation invocation, TransportInfo transportInfo) {
							m_currentState = transportInfo.getCurrentTransportState();
							switch (transportInfo.getCurrentTransportState()) {
							case PLAYING:
							{
								m_currentItem.setPlayStatue(1);
								fireOnPlayingEvent();
								break;
							}
							case PAUSED_PLAYBACK:
							{
								m_currentItem.setPlayStatue(2);
								fireOnPausedEvent();
								break;
							}
							case STOPPED:
							{
								m_currentItem.setPlayStatue(0);
								//								System.out.println("----STOPPED----");
								fireOnStopedEvent();

								if (mediaNext)
								{
									System.out.println("----STOPPED---- fireOnEndTrackEvent");
									fireOnEndTrackEvent();
								}
								else
								{
									//									System.out.println("----STOPPED---- fireOnMiddleEndEvent");
									fireOnMiddleEndEvent();
								}
								break;
							}
							default:
								break;
							}
							m_checkGetTransportInfo = false;
						}

					});
				}
				if (m_renderingControl != null && !m_checkGetVolumeInfo) {
					m_checkGetVolumeInfo = true;
					m_controlPoint.execute(new GetVolume(m_renderingControl) {
						@SuppressWarnings("rawtypes")
						@Override
						public void failure(ActionInvocation invocation, UpnpResponse operation, String defaultMsg) {
							fireOnFailEvent(invocation.getAction(), operation, defaultMsg);
							m_checkGetVolumeInfo = false;
						}

						@SuppressWarnings("rawtypes")
						@Override
						public void received(ActionInvocation actionInvocation, int currentVolume) {
							m_currentVolume = currentVolume;
							//							System.out.println("The currentVolume is:" + m_currentVolume);
							m_checkGetVolumeInfo = false;
						}
					});
				}

				try {
					Thread.sleep(UPDATE_INTERVAL);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}

	@SuppressWarnings("rawtypes")
	public RemoteDMRProcessorImpl(Device dmr, ControlPoint controlPoint) {
		m_device = dmr;
		m_controlPoint = controlPoint;
		m_avtransportService = m_device.findService(new ServiceType("schemas-upnp-org", "AVTransport"));
		m_renderingControl = m_device.findService(new ServiceType("schemas-upnp-org", "RenderingControl"));
		if (m_renderingControl != null && (m_renderingControl.getAction("SetVolume") == null || m_renderingControl.getAction("GetVolume") == null))
			m_renderingControl = null;
		m_listeners = new ArrayList<DMRProcessor.DMRProcessorListener>();
		m_currentItem = new PlaylistItem();
		m_updateThread = new UpdateThread();
	}

	@SuppressWarnings("rawtypes")
	@Override
	public void play() {
		if (m_controlPoint == null || m_avtransportService == null)
			return;
		m_isBusy = true;
		Play play = new Play(m_avtransportService) {

			@Override
			public void success(ActionInvocation invocation) {
				super.success(invocation);

				int position = AppPreference.getPlayPosition();
				if (position != 0) {
					playingSeek(ModelUtil.toTimeString(position));
					AppPreference.setPlayPosition(0);
				}
				m_isBusy = false;
				imagePlay = true;
			}

			@Override
			public void failure(ActionInvocation invocation, UpnpResponse response, String defaultMsg) {
				fireOnFailEvent(invocation.getAction(), response, defaultMsg);
				int position = AppPreference.getPlayPosition();
				if (position != 0) {
					playingSeek(ModelUtil.toTimeString(position));
					AppPreference.setPlayPosition(0);
				}
				m_isBusy = false;
				imagePlay = true;
			}

		};

		m_controlPoint.execute(play);
	}

	private void playingSeek(final String time) {
		Thread thread = new Thread(new Runnable() {

			@Override
			public void run() {
				while(!isSeeked) {
					try {
						TimeUnit.SECONDS.sleep(1);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}

					if(m_isBusy)
						continue;

					if (m_controlPoint == null || m_avtransportService == null)
						continue;

					Action action = m_avtransportService.getAction("GetTransportInfo");
					if(null == action){
						continue;
					}

					m_isBusy = true;
					GetTransportInfo getTransportInfo = new GetTransportInfo(m_avtransportService) {
						@SuppressWarnings("rawtypes")
						@Override
						public void failure(ActionInvocation invocation, UpnpResponse operation, String defaultMsg) {
							m_isBusy = false;
						}

						@SuppressWarnings("rawtypes")
						@Override
						public void received(ActionInvocation invocation, TransportInfo transportInfo) {
							switch (transportInfo.getCurrentTransportState()) {
							case PLAYING:
								seek(time);
								isSeeked = true;
								break;
							}
							m_isBusy = false;
						}

					};
					m_controlPoint.execute(getTransportInfo);
				}

			}
		});

		thread.start();
	}

	@SuppressWarnings("rawtypes")
	@Override
	public void pause() {
		if (m_controlPoint == null || m_avtransportService == null)
			return;
		m_isBusy = true;
		Pause pause = new Pause(m_avtransportService) {

			@Override
			public void success(ActionInvocation invocation) {
				super.success(invocation);
				m_isBusy = false;
				// m_state = PAUSE;
			}

			@Override
			public void failure(ActionInvocation invocation, UpnpResponse response, String defaultMsg) {
				fireOnFailEvent(invocation.getAction(), response, defaultMsg);
				m_isBusy = false;
			}

		};
		m_controlPoint.execute(pause);
	}

	@SuppressWarnings("rawtypes")
	@Override
	public void stop() {
		if (m_controlPoint == null || m_avtransportService == null)
			return;
		m_isBusy = true;

		if (m_currentPosition != 0)
			AppPreference.setPlayPosition(m_currentPosition);

		Stop stop = new Stop(m_avtransportService) {
			@Override
			public void success(ActionInvocation invocation) {
				super.success(invocation);
				fireUpdatePositionEvent(0, 0);
				m_isBusy = false;
				// m_state = STOP;
			}

			@Override
			public void failure(ActionInvocation invocation, UpnpResponse response, String defaultMsg) {
				fireOnFailEvent(invocation.getAction(), response, defaultMsg);
				m_isBusy = false;
			}
		};

		m_controlPoint.execute(stop);
	}

	@Override
	public void addListener(DMRProcessorListener listener) {
		synchronized (m_listeners) {
			if (!m_listeners.contains(listener))
				m_listeners.add(listener);
			if (m_avtransportService == null)
				fireOnErrorEvent("Cannot get service on this device");
		}
	}

	@Override
	public void removeListener(DMRProcessorListener listener) {
		synchronized (m_listeners) {
			m_listeners.remove(listener);
		}
	}

	@SuppressWarnings("rawtypes")
	private void fireOnFailEvent(Action action, UpnpResponse response, String message) {
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onActionFail(action, response, message);
			}
		}
	}

	private void fireUpdatePositionEvent(long current, long max) {
		if (m_isBusy)
			return;

		if ((max > 0 && max <= 5) || (max > 5 && max - current <= 5))
		{
			mediaNext = true;
		}

		if (max > 0 && current > 0)
		{
			mediaPlay = true;
		}

		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onUpdatePosition(current, max);
			}
		}
	}

	private void fireOnStopedEvent() {
		if (m_isBusy)
			return;
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onStoped();
			}
		}
	}

	private void fireOnPausedEvent() {
		if (m_isBusy)
			return;
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onPaused();
			}
		}
	}

	private void fireOnPlayingEvent() {
		if (m_isBusy)
			return;
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onPlaying();
			}
		}
	}

	private void fireOnEndTrackEvent() {
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onCompleted();
			}
		}
		/**
		PlaylistProcessor m_playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (m_isBusy || m_playlistProcessor == null)
			return;
		PlaylistItem currentItem = m_playlistProcessor.getCurrentItem();
		if (AppPreference.getAutoNext()) {
			if (currentItem != null && (currentItem.getType() == Type.IMAGE_LOCAL || currentItem.getType() == Type.IMAGE_REMOTE))
				return;
			Log.e(TAG, "onEndTrack, m_autoNextPending = " + m_autoNextPending);
			if (m_autoNextPending <= 0) {
				Log.e(TAG, "Call playlist next");
				m_playlistProcessor.next();
				m_autoNextPending = AUTO_NEXT_DELAY;
			} else {
				--m_autoNextPending;
			}
		}*/
	}

	private void fireOnMiddleEndEvent() {
		if (m_isBusy)
			return;

		if (mediaMiddleEnd)
			return;

		PlaylistProcessor m_playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (m_playlistProcessor == null)
			return;
		PlaylistItem currentItem = m_playlistProcessor.getCurrentItem();
		if (currentItem == null)
			return;

		boolean isImage = currentItem.getType() == Type.IMAGE_LOCAL || currentItem.getType() == Type.IMAGE_REMOTE;

		if ((!mediaPlay && !isImage) || (!imagePlay && isImage))
			return;

		mediaMiddleEnd = true;
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onMiddleEndEvent();
			}
		}
	}

	private void fireOnErrorEvent(String error) {
		synchronized (m_listeners) {
			for (DMRProcessorListener listener : m_listeners) {
				listener.onErrorEvent(error);
			}
		}
	}

	@Override
	public void dispose() {
		stop();

		if (m_updateThread != null)
			m_updateThread.stopThread();

		isSeeked = true;

		synchronized (m_listeners) {
			m_listeners.clear();
		}
	}

	public void seek(String position) {
		m_isBusy = true;
		@SuppressWarnings("rawtypes")
		Seek seek = new Seek(m_avtransportService, SeekMode.REL_TIME, position) {
			@Override
			public void success(ActionInvocation invocation) {
				super.success(invocation);
				m_isBusy = false;
				try {
					Thread.sleep(SEEK_DELAY_INTERVAL);
					m_isBusy = false;
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void failure(ActionInvocation invocation, UpnpResponse reponse, String defaultMsg) {
				m_isBusy = false;
			}
		};
		m_controlPoint.execute(seek);
	}

	@SuppressWarnings("rawtypes")
	@Override
	public void setVolume(int newVolume) {
		if (m_renderingControl != null) {
			m_isBusy = true;
			m_controlPoint.execute(new SetVolume(m_renderingControl, newVolume) {
				@Override
				public void success(ActionInvocation invocation) {
					super.success(invocation);
					m_isBusy = false;
				}

				@Override
				public void failure(ActionInvocation invocation, UpnpResponse operation, String defaultMsg) {
					fireOnFailEvent(invocation.getAction(), operation, defaultMsg);
					m_isBusy = false;
				}
			});
		}
	}

	@Override
	public int getVolume() {
		return m_currentVolume;
	}

	@Override
	public int getMaxVolume() {
		return MAX_VOLUME;
	}

	@Override
	public String getName() {
		return m_device != null ? m_device.getDetails().getFriendlyName() : "NULL";
	}
	@Override
	public String getCurrentTrackURI() {
		return null == m_currentItem ? "" : (m_currentItem.getData() instanceof DIDLObject ? HttpServerUtil.getUrlFrom((DIDLObject) m_currentItem.getData()) : m_currentItem.getUrl());
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

	@Override
	public void setURIandPlay(final PlaylistItem item) {
		System.out.println("---come into setURIandPlay---");
		imagePlay = false;
		mediaPlay = false;
		mediaNext = false;
		mediaMiddleEnd = false;
		m_autoNextPending = AUTO_NEXT_DELAY;
		if (item == null) {
			m_currentItem = null;
			stop();
			return;
		}
		item.setRemotePlay(true);
		/**
		if(itemId!=null){
			System.out.println("is not null");
			if(!itemId.equals(item.getId())){
				System.out.println("itemId not equal it id itemId:" + itemId + "  item id:" + item.getId());
				AppPreference.setPlayPosition(0);
				m_currentPosition = 0;
				itemId = item.getId();
			}
		}else{
			AppPreference.setPlayPosition(0);
			m_currentPosition = 0;
			itemId = item.getId();
		}*/

		final String url = item.getUrl();
		m_autoNextPending = AUTO_NEXT_DELAY;
		if (m_controlPoint == null || m_avtransportService == null){
			return;
		}
		if (m_currentItem != null && m_currentItem.equals(item) && m_currentState != TransportState.STOPPED)
			return;

		System.out.println("----remot start play----");
		m_isBusy = true;

		m_currentItem = item;
		System.out.println("The metaData:"+item.getMetaData());
		System.out.println("The url12 is:" + url);
		new Thread(new Runnable() {

			@Override
			public void run() {
				setUriAndPlay(url, item.getMetaData());
//				setAVTransportURIAndPlay(url, metaData)
			}

		}).start();
		//		setUriAndPlay(url, item.getMetaData());
	}

	@SuppressWarnings("rawtypes")
	private void setUriAndPlay(final String url, final String metaData) {
		synchronized (m_currentItem) {
			Stop stop = new Stop(m_avtransportService) {

				@Override
				public void success(ActionInvocation invocation) {
					super.success(invocation);
					fireUpdatePositionEvent(0, 0);

					setAVTransportURIAndPlay(url, metaData);

					m_isBusy = false;
				}

				@Override
				public void failure(ActionInvocation invocation, UpnpResponse response, String defaultMsg) {
					fireUpdatePositionEvent(0, 0);

					setAVTransportURIAndPlay(url, metaData);

					m_isBusy = false;
				}
			};
			m_controlPoint.execute(stop);
		}
	}

	private void setAVTransportURIAndPlay(final String url, final String metaData) {
		m_controlPoint.execute(new SetAVTransportURI(m_avtransportService, url, metaData) {
			@Override
			public void success(ActionInvocation invocation) {
				super.success(invocation);
				play();
			}

			@Override
			public void failure(ActionInvocation invocation, UpnpResponse response, String defaultMsg) {
				fireUpdatePositionEvent(0, 0);
				System.out.println("The failure defaultMsg:" + defaultMsg); 
				fireOnFailEvent(invocation.getAction(), response, defaultMsg);

				m_isBusy = false;
			}
		});
	}

	@Override
	public PlaylistItem getCurrentItem() {
		return m_currentItem;
	}
}
