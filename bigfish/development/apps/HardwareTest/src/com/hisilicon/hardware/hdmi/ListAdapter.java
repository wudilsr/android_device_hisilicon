package com.hisilicon.hardware.hdmi;

import java.util.ArrayList;
import java.util.HashMap;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;

import com.hisilicon.hardware.util.Common;

public class ListAdapter extends BaseAdapter {

    private Context context;
    private ArrayList<HashMap<String, String>> list;

    public ListAdapter(Context context) {
        this.context = context;
        this.list = new ArrayList<HashMap<String, String>>();
    }

    public void refreshView(ArrayList<HashMap<String, String>> list) {
        this.list = list;
        this.notifyDataSetChanged();
    }

    @Override
    public int getCount() {
        return list.size();
    }

    @Override
    public Object getItem(int position) {
        return list.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewItem view = null;
        if (position < getCount() - 2) {
            if (null != convertView
                    && (Integer) convertView.getTag() == ViewItem.TYPE_1) {
                view = (ViewItem) convertView;
            } else {
                view = new ViewItem(context, ViewItem.TYPE_1);
                view.setTag(ViewItem.TYPE_1);
            }
        } else {
            if (null != convertView
                    && (Integer) convertView.getTag() == ViewItem.TYPE_2) {
                view = (ViewItem) convertView;
            } else {
                view = new ViewItem(context, ViewItem.TYPE_2);
                view.setTag(ViewItem.TYPE_2);
            }
        }
        view.setTitle(list.get(position).get(Common.TITLE));
        view.setMessage(list.get(position).get(Common.MESSAGE));
        return view;
    }

}