package com.hisilicon.dlna.dmc.processor.interfaces;

import org.teleal.cling.model.message.UpnpResponse;
import org.teleal.cling.model.meta.Action;

import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;

public interface DMRProcessor {

	void setURIandPlay(PlaylistItem item);

	void play();

	void pause();

	void stop();

	void seek(String position);

	void setVolume(int newVolume);

	int getVolume();

	int getMaxVolume();

	void addListener(DMRProcessorListener listener);

	void removeListener(DMRProcessorListener listener);

	void dispose();

	String getName();

	String getCurrentTrackURI();

	void setRunning(boolean running);

	PlaylistItem getCurrentItem();
	
	public interface DMRProcessorListener {
		void onUpdatePosition(long current, long max);

		void onPaused();

		void onStoped();

		void onPlaying();

		void onMiddleEndEvent();
		
		void onErrorEvent(String error);
		
		void onCompleted();

		@SuppressWarnings("rawtypes")
		void onActionFail(Action actionCallback, UpnpResponse response, final String cause);
	}

}
