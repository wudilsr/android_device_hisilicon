package com.hisilicon.dlna.dmc.gui.activity;

import android.widget.AbsListView;

public abstract class AbsListViewAdapter<T> extends MyAdapter<T> {

	public abstract void notifyVisibleItemChanged(AbsListView absListView);

}
