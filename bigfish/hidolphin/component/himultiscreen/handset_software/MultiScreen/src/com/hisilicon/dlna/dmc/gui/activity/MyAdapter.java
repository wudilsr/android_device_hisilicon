package com.hisilicon.dlna.dmc.gui.activity;

import java.util.ArrayList;
import java.util.List;

import android.widget.BaseAdapter;

public abstract class MyAdapter<T> extends BaseAdapter {
	/**
	 * 此类将对List的操作封装起来
	 */
	private List<T> itemList;
	private boolean mNotifyOnChange = true;
	
	public MyAdapter() {
		itemList = new ArrayList<T>();
	}

	public void setNotifyOnChange(boolean notifyOnChange) {
        mNotifyOnChange = notifyOnChange;
    }

	public void setItemList(List<T> list) {
		clear();
		if(null != list) itemList.addAll(list);
		
		if (mNotifyOnChange) notifyDataSetChanged();
	}
	
	public List<T> getItemList() {
		return itemList;
	}
	
	public void add(T item) {
		if(itemList.contains(item)) {
			int position = itemList.indexOf(item);
			itemList.remove(position);
			itemList.add(position, item);
		} else {
			itemList.add(item);
		}
//		if (mNotifyOnChange) notifyDataSetChanged();
	}
	
	public void insert(T item, int position) {
		if (itemList.contains(item))
			itemList.remove(item);
		itemList.add(position, item);
		if (mNotifyOnChange) notifyDataSetChanged();
	}
	
	public void remove(T item) {
		itemList.remove(item);
		if (mNotifyOnChange) notifyDataSetChanged();
	}

	public void clear() {
		itemList.clear();
		notifyDataSetChanged();
	}
	
	@Override
	public int getCount() {
		return itemList.size();
	}

	@Override
	public T getItem(int position) {
		if(position<0||position>=itemList.size())
			return null;
		return itemList.get(position);
	}

	@Override
	public long getItemId(int position) {
		return position;
	}

}
