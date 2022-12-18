package com.hisilicon.dlna.dmc.processor.impl;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.item.AudioItem;

import com.hisilicon.dlna.dmc.gui.activity.AppPreference;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem.Type;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem.ViewMode;

public class PlaylistProcessorImpl implements PlaylistProcessor {
	private List<PlaylistItem> m_playlistItems;
	private int m_currentItemIdx = -1;
	private List<PlaylistListener> m_listeners;
	private static Random RANDOM = new Random(System.currentTimeMillis());;

	public PlaylistProcessorImpl() {
		m_playlistItems = new ArrayList<PlaylistItem>();
		m_listeners = new ArrayList<PlaylistProcessor.PlaylistListener>();
	}

	@Override
	public int getSize() {
		return m_playlistItems.size();
	}

	@Override
	public void next() {
		if (AppPreference.getShuffle() && isMusic())
			nextShuffle();
		else
			nextNormal();
	}
	
	private boolean isMusic() {
		return getCurrentItem() != null && getCurrentItem().getData() instanceof AudioItem;
	}

	private void nextNormal() {
		List<PlaylistItem> playlistItems = getAllItems();
		if (playlistItems.size() == 0)
			return;
		int currentIdx = playlistItems.indexOf(m_playlistItems.get(m_currentItemIdx));
		++currentIdx;
		if (currentIdx >= playlistItems.size())
			currentIdx = 0;
		m_currentItemIdx = m_playlistItems.indexOf(playlistItems.get(currentIdx));
		fireOnItemChangedEvent(ChangeMode.NEXT);
	}

	private void nextShuffle() {
		List<PlaylistItem> playlistItems = getAllItems();
		if (playlistItems.size() == 0)
			return;
		if (playlistItems.size() != 1) {
			int currentIdx = playlistItems.indexOf(m_playlistItems.get(m_currentItemIdx));
			int newIdx = currentIdx;
			while (newIdx == currentIdx)
				newIdx = RANDOM.nextInt(playlistItems.size());
			m_currentItemIdx = m_playlistItems.indexOf(playlistItems.get(newIdx));
		}
		fireOnItemChangedEvent(ChangeMode.NEXT);
	}

	private void fireOnItemChangedEvent(ChangeMode changeMode) {
		if (m_currentItemIdx < 0 || m_currentItemIdx >= m_playlistItems.size())
			return;
		synchronized (m_listeners) {
			for (PlaylistListener listener : m_listeners) {
				listener.onItemChanged(m_playlistItems.get(m_currentItemIdx), changeMode);
			}
		}
	}

	@Override
	public void previous() {
		List<PlaylistItem> playlistItems = getAllItems();
		if (playlistItems.size() == 0)
			return;
		int currentIdx = playlistItems.indexOf(m_playlistItems.get(m_currentItemIdx));
		--currentIdx;
		if (currentIdx < 0)
			currentIdx = playlistItems.size() - 1;
		m_currentItemIdx = m_playlistItems.indexOf(playlistItems.get(currentIdx));
		fireOnItemChangedEvent(ChangeMode.PREV);
	}

	@Override
	public PlaylistItem getCurrentItem() {
		if (m_currentItemIdx == -1) {
			return null;
		}

		if (m_playlistItems.size() > 0 && m_currentItemIdx < m_playlistItems.size()) {
			return m_playlistItems.get(m_currentItemIdx);
		}
		return null;
	}

	@Override
	public int setCurrentItem(int idx) {
		if (0 <= idx && idx < m_playlistItems.size()) {
			m_currentItemIdx = idx;
			fireOnItemChangedEvent(ChangeMode.UNKNOW);
			return m_currentItemIdx;
		}
		return -1;
	}

	@Override
	public int setCurrentItem(PlaylistItem item) {
		synchronized (m_playlistItems) {
			m_currentItemIdx = m_playlistItems.indexOf(item);
			fireOnItemChangedEvent(ChangeMode.UNKNOW);
			return m_currentItemIdx;
		}
	}

	@Override
	public PlaylistItem addItem(PlaylistItem item) {
		synchronized (m_playlistItems) {
			if (m_playlistItems.contains(item))
				return item;
			
			m_playlistItems.add(item);
			if (m_playlistItems.size() == 1) {
				m_currentItemIdx = 0;
			}
			return item;
		}
	}

	@Override
	public PlaylistItem removeItem(PlaylistItem item) {
		synchronized (m_playlistItems) {
			int itemIdx = -1;
			if ((itemIdx = m_playlistItems.indexOf(item)) >= 0) {
				m_playlistItems.remove(item);
				DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
				if (dmrProcessor != null && dmrProcessor.getCurrentTrackURI().equals(item.getUrl())) {
					dmrProcessor.stop();
				}
				if (itemIdx == m_currentItemIdx)
					m_currentItemIdx = 0;
				return item;
			}
			return null;
		}
	}
	
	@Override
	public void setItems(List<PlaylistItem> list) {
		synchronized (m_playlistItems) {
			m_currentItemIdx = -1;
			m_playlistItems.clear();
			if (null != list) {
				m_playlistItems.addAll(list);
			}
		}
	}

	@Override
	public List<PlaylistItem> getAllItems() {
		return m_playlistItems;
	}

	@Override
	public PlaylistItem addDIDLObject(DIDLObject object) {
		return addItem(PlaylistItem.createFromDLDIObject(object));
	}

	@Override
	public PlaylistItem removeDIDLObject(DIDLObject object) {
		return removeItem(PlaylistItem.createFromDLDIObject(object));
	}
	
	@Override
	public PlaylistItem getItemAt(int idx) {
		return m_playlistItems.get(idx);
	}

	@Override
	public void addListener(PlaylistListener listener) {
		synchronized (m_listeners) {
			if (!m_listeners.contains(listener))
				m_listeners.add(listener);
		}
	}

	@Override
	public void removeListener(PlaylistListener listener) {
		synchronized (m_listeners) {
			if (!m_listeners.contains(listener))
				m_listeners.remove(listener);
		}
	}

	@Override
	public int getCurrentItemIndex() {
		return m_currentItemIdx;
	}
	
	@Override
	public List<PlaylistItem> getItemsByViewMode(ViewMode viewMode) {
		List<PlaylistItem> result = new ArrayList<PlaylistItem>();
		switch (viewMode) {
		case ALL:
			return m_playlistItems;
		case AUDIO_ONLY:
			for (PlaylistItem item : m_playlistItems) {
				if (item.getType().equals(Type.AUDIO_LOCAL) || item.getType().equals(Type.AUDIO_REMOTE))
					result.add(item);
			}
			break;
		case IMAGE_ONLY:
			for (PlaylistItem item : m_playlistItems) {
				if (item.getType().equals(Type.IMAGE_LOCAL) || item.getType().equals(Type.IMAGE_REMOTE))
					result.add(item);
			}
			break;
		case VIDEO_ONLY:
			for (PlaylistItem item : m_playlistItems) {
				if (item.getType().equals(Type.VIDEO_LOCAL) || item.getType().equals(Type.VIDEO_REMOTE))
					result.add(item);
			}
			break;
		}
		return result;
	}

	@Override
	public void updateForViewMode() {
		List<PlaylistItem> playlistItems = getAllItems();
		m_currentItemIdx = playlistItems.size() > 0 ? m_playlistItems.indexOf(playlistItems.get(0)) : -1;
	}

}