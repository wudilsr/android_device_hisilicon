package com.hisilicon.multiscreen.mybox;

import android.content.Context;

import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;

import android.widget.GridView;
import android.widget.LinearLayout;

/**
 * CN:设备连接的子界面。
 */
public class DeviceChildView extends LinearLayout {

	public Integer[] mImageIds = { //R.drawable.device_live_tv,
			//R.drawable.device_airsharing, 
			R.drawable.device_telecontroller,
			R.drawable.device_image_control };

	public String[] mtags = null;

	public String[] mtags_info = null;

	/**
	 * CN:未连接显示布局。
	 */
	public LinearLayout mDevice_no_connect;

	/**
	 * CN:连接显示布局。
	 */
	public LinearLayout mDevice_connect;

	public GridView mDevice_gridview;

	/**
	 * Context of this.
	 */
	private Context mContext;

	
	public DeviceChildView(Context context) {
		super(context);
		mContext = context;

	}

	public DeviceChildView(Context context, AttributeSet attrs) {
		super(context, attrs);
		this.mContext = context;
		initViews(context);

	}

	/**
	 * Init view.
	 */
	public void initViews(Context context) {

		View view = LayoutInflater.from(mContext).inflate(R.layout.device_child, this);

		mtags = this.getResources().getStringArray(R.array.mtags);
		mtags_info = this.getResources().getStringArray(R.array.mtags_info);

		mDevice_no_connect = (LinearLayout) findViewById(R.id.device_no_connect);
		mDevice_connect = (LinearLayout) findViewById(R.id.device_connect);
		mDevice_gridview = (GridView) findViewById(R.id.device_gridview);

	}

}
