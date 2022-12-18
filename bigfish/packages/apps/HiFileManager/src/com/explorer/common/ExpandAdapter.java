package com.explorer.common;

import java.util.List;
import java.util.Map;

import android.app.Activity;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.BaseExpandableListAdapter;
import android.widget.TextView;

public class ExpandAdapter extends BaseExpandableListAdapter {

	Activity activity;
	List<GroupInfo> group;
	// List<Map<String, String>> child;

	final static String MOUNT_NAME = "mountName";
	final static String MOUNT_LABLE = "mountLable";

	public ExpandAdapter(Activity activity, List<GroupInfo> group) {
		this.activity = activity;
		this.group = group;
		// this.child = child;
	}

	public Object getChild(int groupPosition, int childPosition) {

		return null;
	}

	public long getChildId(int groupPosition, int childPosition) {

		return 0;
	}

	public View getChildView(int groupPosition, int childPosition,
			boolean isLastChild, View convertView, ViewGroup parent) {
		Map<String, String> map = group.get(groupPosition).getChildList()
				.get(childPosition);
		String str = map.get(MOUNT_NAME) + map.get(MOUNT_LABLE);
		return getGenericView(str, 0);
	}

	public int getChildrenCount(int groupPosition) {

		return group.get(groupPosition).getChildList().size();
	}

	public Object getGroup(int groupPosition) {

		return null;
	}

	public int getGroupCount() {

		return group.size();
	}

	public long getGroupId(int groupPosition) {

		return 0;
	}

	/**
	 * father index
	 */
	public View getGroupView(int groupPosition, boolean isExpanded,
			View convertView, ViewGroup parent) {
		String str = group.get(groupPosition).getName();
		return getGenericView(str, 1);
	}

	public TextView getGenericView(String s, int flag) {
		AbsListView.LayoutParams lp = new AbsListView.LayoutParams(
				ViewGroup.LayoutParams.MATCH_PARENT, 64);

		TextView text = new TextView(activity);
		text.setLayoutParams(lp);
		text.setGravity(Gravity.CENTER_VERTICAL | Gravity.LEFT);
		if (flag == 0) {
			text.setPadding(100, 0, 0, 0);
			text.setTextSize(26);
		} else {
			text.setPadding(60, 0, 0, 0);
			text.setTextSize(28);
		}
		text.setText(s);
		return text;
	}

	public boolean hasStableIds() {

		return false;
	}

	public boolean isChildSelectable(int groupPosition, int childPosition) {

		return true;
	}
}
