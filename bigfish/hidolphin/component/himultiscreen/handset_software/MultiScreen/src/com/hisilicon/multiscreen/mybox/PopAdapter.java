package com.hisilicon.multiscreen.mybox;

import java.util.HashMap;

import org.cybergarage.upnp.Device;

import android.app.Activity;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.hisilicon.dlna.dmc.gui.activity.MyAdapter;
import com.hisilicon.multiscreen.protocol.utils.HostNetInterface;
import com.hisilicon.multiscreen.upnputils.MultiScreenDeviceList;

/**
 * CN：设备列表的适配器。
 */
public class PopAdapter extends MyAdapter<Device> {

	private HashMap<String, Integer> hashmap = null;
	public static Activity mActivity;
	MultiScreenDeviceList devList = null;

	public PopAdapter(Activity context) {
		super();
		mActivity = context;
		hashmap = new HashMap<String, Integer>();
		resetData();
	}

    public void resetData()
    {
        super.clear();
        hashmap.clear();
        devList = MultiScreenControlService.getInstance().getDeviceDiscover().getDeviceList();
        if (devList != null)
        {
            for (int i = 0; i < devList.size(); i++)
            {
                Device device = devList.getDevice(i);
                String str = device.getFriendlyName();
                Integer lis = hashmap.get(str);
                if (lis == null)
                {
                    hashmap.put(str, 1);
                }
                else
                {
                    hashmap.put(str, lis + 1);
                }
                add(device);
            }
        }
    }

	public View getView(int position, View convertView, ViewGroup parent) {
		// TODO Auto-generated method stub
		ViewHolder holder;
		if (convertView == null) {
			convertView = LayoutInflater.from(mActivity).inflate(R.layout.pomenu_item, null);
			holder = new ViewHolder();
			convertView.setTag(holder);
			holder.llItem = (LinearLayout) convertView.findViewById(R.id.item_ll);
			holder.groupItem = (TextView) convertView.findViewById(R.id.device_name);
		} else {
			holder = (ViewHolder) convertView.getTag();
		}

		holder.groupItem.setGravity(Gravity.CENTER);

		Device device = getItem(position);
		String name = device.getFriendlyName();
		
		if (hashmap.get(name) > 0) {
			name += "  "+ HostNetInterface.uri2Ip(device.getLocation());
		}
		if(name!=null){
			if(DeviceDiscoveryActivity.save_ip!=null&&name.contains(DeviceDiscoveryActivity.save_ip)){
				holder.llItem.setBackgroundResource(R.drawable.device_btn_list_foucs);
			}else{
				holder.llItem.setBackgroundResource(R.drawable.device_btn_list);
			}
		}
		holder.groupItem.setText(name);
		return convertView;
	}

	private final class ViewHolder {
		LinearLayout llItem;
		TextView groupItem;
	}
}
