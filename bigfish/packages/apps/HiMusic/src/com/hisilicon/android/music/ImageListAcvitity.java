package com.hisilicon.android.music;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;

import android.app.ListActivity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

public class ImageListAcvitity extends ListActivity {

	private ListView mPlayListView;
	private TextView mTitleView;
	public SimpleAdapter listItemAdapter;
	private String[] imageType = { "BMP", "JPG", "DNG", "JFIF", "JPEG", "PNG",
			"WBMP", "GIF", "TIF", "JPE", "TIFF" };
	ArrayList<HashMap<String, Object>> listItem;

	private String currPlayPath;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		setContentView(R.layout.sub_list);
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.title);

		Intent intent = getIntent();

		currPlayPath = intent.getStringExtra("path");

		mPlayListView = (ListView) findViewById(android.R.id.list);
		mTitleView = (TextView) findViewById(R.id.left_text);

		listItem = new ArrayList<HashMap<String, Object>>();
		listItemAdapter = new SimpleAdapter(this, listItem,
				R.layout.list_items_image, new String[] { "ItemImage",
						"ItemTitle", "ItemText" }, new int[] { R.id.ItemImage,
						R.id.ItemTitle, R.id.ItemText });

		this.setListAdapter(listItemAdapter);
		updateSubList(currPlayPath);
		mPlayListView.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> parent, View view,
					int position, long id) {
				if (listItem != null && listItem.get(position) != null
						&& listItem.get(position).get("ItemText") != null) {
					String path = listItem.get(position).get("ItemText")
							.toString();

					File f = new File(path);
					if (f.isFile()) {
						if (isImageFile(f)) {
							Intent backIntent = new Intent(ImageListAcvitity.this, MediaPlaybackActivity.class);
							backIntent.putExtra("path", path);
							backIntent.putExtra("fromMusic", true);
							backIntent.setData(Uri.fromFile(f));
							setResult(RESULT_OK, backIntent);
							finish();
						} else {
							Toast.makeText(ImageListAcvitity.this,
									"Please Choose Image File !",
									Toast.LENGTH_SHORT).show();
						}
					} else if (f.isDirectory()) {
						updateSubList(path);
					}
				}
			}
		});
	}

	private boolean isImageFile(File f) {
		String name = f.getName();
		String type = name.substring(name.lastIndexOf(".") + 1);
		Log.i("huangcanbin", "*********** name = " + name);
		Log.i("huangcanbin", "*********** type = " + type);
		for (String str : imageType) {
			if (str.equals(type.toUpperCase())) {
				return true;
			}
		}
		return false;
	}

	public void updateSubList(String path) {
		listItem.clear();
		mTitleView.setText(path);

		File f = new File(path);
		HashMap<String, Object> temp_map = new HashMap<String, Object>();
		temp_map.put("ItemImage", R.drawable.folder_file);
		temp_map.put("ItemTitle", "..");
		if (path.equals("/mnt"))
			temp_map.put("ItemText", "/mnt");
		else
			temp_map.put("ItemText", f.getParentFile());
		listItem.add(temp_map);

		File[] files = f.listFiles();
		if (files == null)
			return;

		for (int i = 0; i < files.length; i++) {
			if (files[i].isFile()) {
				HashMap<String, Object> map = new HashMap<String, Object>();
				map.put("ItemImage", R.drawable.textfile);
				map.put("ItemTitle", files[i].getName());
				map.put("ItemText", files[i].getPath());
				if (files[i].canRead())
					listItem.add(map);
			} else if (files[i].isDirectory()) {
				HashMap<String, Object> map = new HashMap<String, Object>();
				map.put("ItemImage", R.drawable.folder_file);
				map.put("ItemTitle", files[i].getName());
				map.put("ItemText", files[i].getPath());
				if (files[i].canRead())
					listItem.add(map);
			}
		}
		Collections.sort(listItem, new MyComparator());
		((SimpleAdapter) getListView().getAdapter()).notifyDataSetChanged();
		mPlayListView.setSelection(0);
		mPlayListView.requestFocus();
	}

	private class MyComparator implements Comparator<HashMap<String, Object>> {

		@Override
		public int compare(HashMap<String, Object> o1,
				HashMap<String, Object> o2) {
			int id1 = (Integer) o1.get("ItemImage");
			int id2 = (Integer) o2.get("ItemImage");
			String name1 = ((String) o1.get("ItemTitle")).toUpperCase();
			String name2 = ((String) o2.get("ItemTitle")).toUpperCase();
			if (id1 == id2) {
				return name1.compareTo(name2);
			} else {
				if (id1 == R.drawable.folder_file)
					return -1;
				else
					return 1;
			}
		}
	}
}