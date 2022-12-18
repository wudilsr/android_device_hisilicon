package com.hisilicon.multiscreen.mybox;

import org.cybergarage.upnp.Device;

import android.app.Activity;
import android.graphics.drawable.BitmapDrawable;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.PopupWindow;


/**
 * CN:设备列表的显示，通过几成popwindow实现
 */
public class DeviceListShow extends PopupWindow {

	/**
	 * CN:设备列表显示布局。
	 */
	private LinearLayout mDevice_list_layout;

	/**
	 * CN:取消按钮。
	 */
	private Button mDevice_cancel;
	
	private ClickCallback clickCallback;

	/**
	 * activity of this.
	 */
	private Activity mContext;


	public static ListView listView;

	int[] location = new int[2];
	int x1, y1;

	/**
	 * CN:设备列表的适配器。
	 */
	private PopAdapter adapter;

	/**
	 * init view.
	 */
	public DeviceListShow(Activity context, ClickCallback newClickCallback) {
		super(context);
		this.clickCallback = newClickCallback;
		mContext = context;

		View view = LayoutInflater.from(mContext).inflate(R.layout.popmenu,null);

		mDevice_list_layout = (LinearLayout) view.findViewById(R.id.device_list_layout);

		mDevice_cancel = (Button) view.findViewById(R.id.device_cancel);
		mDevice_cancel.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				dismiss();
			}
		});

		this.setContentView(view);
		this.setWidth(LayoutParams.FILL_PARENT);
		this.setHeight(LayoutParams.FILL_PARENT);
		this.setFocusable(true);
		this.setTouchable(true);
		this.setOutsideTouchable(true);
		this.update();
		this.setBackgroundDrawable(new BitmapDrawable());

		listView = (ListView) view.findViewById(R.id.device_list);
		adapter = new PopAdapter(mContext);
		listView.setAdapter(adapter);
		listView.setItemsCanFocus(false);
		
		/**
		 * CN:列表中item点击事件。
		 */
		listView.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> parent, View view,
					int position, long id) {

				Device mDevice = (Device) adapter.getItem(position);

				if (clickCallback != null)
					clickCallback.clickItem(mDevice);

			}
		});

		/**
		 * CN:点击布局以为的地方会dismiss这个view。
		 */
		view.setOnTouchListener(new View.OnTouchListener() {

			public boolean onTouch(View v, MotionEvent event) {

				mDevice_list_layout.getLocationInWindow(location);
				x1 = location[0];
				y1 = location[1];

				int y = (int) event.getY();
				if (event.getAction() == MotionEvent.ACTION_UP) {
					if (y < y1 || y > y1 + mDevice_list_layout.getHeight()) {
						dismiss();
					}
				}
				return true;
			}
		});

	}

	/**
	 * CN:设备点击回调。
	 */
	public interface ClickCallback {
		void clickItem(Device device);
	}

	/**
	 * CN:更新设备列表。
	 */
	public void updateAdapter() {

		if (listView != null) {
            if (adapter == null)
            {
                adapter = new PopAdapter(mContext);
            }
            adapter.resetData();
            listView.setAdapter(adapter);
            adapter.notifyDataSetChanged();
		}
	}

}
