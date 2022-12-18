package com.hisilicon.dlna.dmc.processor.interfaces;

import java.util.List;

import org.teleal.cling.support.model.DIDLObject;

import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem.ViewMode;

public interface PlaylistProcessor {
	void next();

	void previous();

	void addListener(PlaylistListener listener);

	void removeListener(PlaylistListener listener);

	int setCurrentItem(int index);

	int setCurrentItem(PlaylistItem item);
	
	PlaylistItem getCurrentItem();
	
	PlaylistItem getItemAt(int index);

	PlaylistItem addItem(PlaylistItem item);

	PlaylistItem addDIDLObject(DIDLObject object);

	PlaylistItem removeItem(PlaylistItem item);

	PlaylistItem removeDIDLObject(DIDLObject object);
	
	void setItems(List<PlaylistItem> list);

	int getSize();

	List<PlaylistItem> getAllItems();

	public interface PlaylistListener {
		void onItemChanged(PlaylistItem item, ChangeMode changeMode);
	}

	int getCurrentItemIndex();
	
	List<PlaylistItem> getItemsByViewMode(ViewMode viewMode);

	void updateForViewMode();

	public enum ChangeMode {
		NEXT, PREV, RANDOM, UNKNOW
	}
}
