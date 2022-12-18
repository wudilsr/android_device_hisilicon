package com.hisilicon.android.mediacenter.common;

import java.util.List;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.CheckedTextView;

import com.hisilicon.android.mediacenter.R;

/**
 * data adapter
 * 
 * provide data for the list of thumbnail
 */
public class RemoveFilterAdapter extends BaseAdapter {
	LayoutInflater inflater;

	private List<String> list = null;

	/**
	 * @param context
	 *            //page
	 * @param list
	 *            //file list
	 * @param fileString
	 *            //file path
	 * @param layout
	 *            //data container layout
	 */
	public RemoveFilterAdapter(CommonActivity context, List<String> list) {
		inflater = LayoutInflater.from(context);
		this.list = list;
	}

	/* the number of data containers */
	/* CNcomment: 获得容器中数据的数目 */

	public int getCount() {
		return list.size();
	}

	/* for each option object container */
	/* CNcomment:获得容器中每个选项对象 */

	public Object getItem(int position) {
		return list.get(position);
	}

	/* for each option object container ID */
	/* CNcomment: 获得容器中每个选项对象的ID */

	public long getItemId(int position) {
		return position;
	}

	/* assignment for each option object */
	/* CNcomment: 为每个选项对象赋值 */

	public View getView(final int position, View convertView, ViewGroup parent) {
		// control container
		final ViewHolder holder;
		/*
		 * according to the view whether there is to initialize the controls in
		 * each data container
		 */
		/* CNcomment: 根据视图是否存在 初始化每个数据容器中的控件 */

		if (convertView == null) {
			holder = new ViewHolder();
			convertView = inflater.inflate(R.layout.control_row, null);
			holder.check = (CheckedTextView) convertView
					.findViewById(R.id.check);
			convertView.setTag(holder);
		} else {
			holder = (ViewHolder) convertView.getTag();
		}

		holder.check.setText(list.get(position));

		return convertView;
	}

	/**
	 * control container class
	 */
	private static class ViewHolder {
		/**
		 * @brief : eliminating redundant code
		 */
		private CheckedTextView check;
	}

}
