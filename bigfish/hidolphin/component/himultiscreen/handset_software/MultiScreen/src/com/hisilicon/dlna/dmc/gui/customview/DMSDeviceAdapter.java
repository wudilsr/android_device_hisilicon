package com.hisilicon.dlna.dmc.gui.customview;

import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.LocalDevice;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.hisilicon.dlna.dmc.gui.activity.AbsListViewAdapter;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.R;

@SuppressWarnings("rawtypes")
public class DMSDeviceAdapter extends AbsListViewAdapter<Device> {
	private LayoutInflater m_inflater = null;
	private int selPosition = 0;
	private String deviceName;

	public DMSDeviceAdapter(Context context) {
		m_inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
	}
	
	public void setSelPosition(int position){
		selPosition = position;
	}
	
	public void setDeviceName(String deviceName){
		this.deviceName = deviceName;
	}

	@Override
	public void notifyVisibleItemChanged(AbsListView absListView) {
		
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		if (convertView == null)
		{
			convertView = m_inflater.inflate(R.layout.dlna_dms_deviceitem, null, false);
		}

		if (convertView.getTag() == null)
		{
			setViewHolder(convertView);
		}

		final ViewHolder holder = (ViewHolder) convertView.getTag();
		
		Device device = getItem(position);
//		String title = Utility.getDeviceFriendlyName(device.getDetails().getFriendlyName());
		holder.rc_device_name.setText(Utility.getDeviceFriendlyName(device.getDetails().getFriendlyName()));
//		UpnpProcessorImpl.getSington().getCurrentDMS().getDetails().getFriendlyName();
//		if(device.getDetails().getFriendlyName().equals(UpnpProcessorImpl.getSington().getCurrentDMS().getDetails().getFriendlyName())){
//			holder.rc_device_ll.setBackgroundResource(R.drawable.device_btn_list_foucs);
//		}else{
//			holder.rc_device_ll.setBackgroundResource(R.drawable.device_btn_list);
//		}
		
		if(position==selPosition)
			holder.rc_device_ll.setBackgroundResource(R.drawable.device_btn_list_foucs);
		else
			holder.rc_device_ll.setBackgroundResource(R.drawable.device_btn_list);
		if (device instanceof LocalDevice)
		{
			holder.rc_device_name.setText(R.string.myphone);
		}
		
		return convertView;
	}

	public void setViewHolder(View view)
	{
		ViewHolder viewHolder = new ViewHolder();
		viewHolder.view = view;
		viewHolder.rc_device_name = (TextView) view.findViewById(R.id.rc_device_name);
		viewHolder.rc_device_ll = (LinearLayout)view.findViewById(R.id.rc_device_ll);
		view.setTag(viewHolder);
	}

	private class ViewHolder {
		View view;
		TextView rc_device_name;
		LinearLayout rc_device_ll;
	}
}
