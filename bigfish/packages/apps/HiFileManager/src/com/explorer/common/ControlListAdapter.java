package com.explorer.common;

import java.io.File;
import java.util.List;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.CheckedTextView;

import com.explorer.R;

/**
 * data adapter
 */
public class ControlListAdapter extends BaseAdapter {
	// file list
	private List<File> list;

	LayoutInflater inflater;

	CommonActivity context;

	public List<File> getList() {
		return list;
	}

	/**
	 * @param context
	 * @param list
	 * @param fileString
	 *            //file path
	 * @param layout
	 */
	public ControlListAdapter(CommonActivity context, List<File> list) {
		/**
		 * initalization parameters
		 */
		this.list = list;
		inflater = LayoutInflater.from(context);
		this.context = context;
	}

	/**
	 * the number of data containers
	 */

	public int getCount() {
		return list.size();
	}

	/**
	 * for each option object container
	 */

	public Object getItem(int position) {
		return list.get(position);
	}

	/**
	 * access to each option in the container object ID
	 */

	public long getItemId(int position) {
		return position;
	}

	/**
	 * assignment for each option object
	 */

	public View getView(final int position, View convertView, ViewGroup parent) {
		// control container
		final ViewHolder holder;

		/*
		 * According to the view whether there is to initialize the controls in
		 * each data container
		 */
		/* CNcomment: 根据视图是否存在 初始化每个数据容器中的控件 */

		if (convertView == null) {
			holder = new ViewHolder();
			convertView = inflater.inflate(R.layout.control_row, null);
			holder.checkedTxt = (CheckedTextView) convertView
					.findViewById(R.id.check);
			convertView.setTag(holder);
		} else {
			holder = (ViewHolder) convertView.getTag();
		}

		final File f;
		f = list.get(position);
		String f_type = FileUtil.getMIMEType(f, context);
		// Adaptation different picture file types
		if (f.isFile()) {
			if ("audio/*".equals(f_type)) {
				holder.checkedTxt.setCompoundDrawablesWithIntrinsicBounds(
						R.drawable.mp3file, 0, 0, 0);
			} else if ("video/*".equals(f_type)) {
				holder.checkedTxt.setCompoundDrawablesWithIntrinsicBounds(
						R.drawable.vediofile, 0, 0, 0);
			} else if ("apk/*".equals(f_type)) {
				holder.checkedTxt.setCompoundDrawablesWithIntrinsicBounds(
						R.drawable.list, 0, 0, 0);
			} else if ("image/*".equals(f_type)) {
				holder.checkedTxt.setCompoundDrawablesWithIntrinsicBounds(
						R.drawable.imgfile, 0, 0, 0);
			} else {
				holder.checkedTxt.setCompoundDrawablesWithIntrinsicBounds(
						R.drawable.otherfile, 0, 0, 0);
			}
		}
		// File type data icon
		else {
			holder.checkedTxt.setCompoundDrawablesWithIntrinsicBounds(
					R.drawable.folder_file, 0, 0, 0);
		}

		holder.checkedTxt.setTextSize(28);
		/* The file name character length of more than 64, ticker display */
		/* CNcomment: 文件名字符长度超过64,跑马灯显示 */
		if (f.getName().length() > 66) {
			holder.checkedTxt.setText(f.getName().substring(0, 55) + "...");
		} else {
			holder.checkedTxt.setText(f.getName());
		}
		return convertView;
	}

	/**
	 * the type of control container
	 */
	private static class ViewHolder {
		private CheckedTextView checkedTxt;
	}

}
