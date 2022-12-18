package com.hisilicon.dlna.dmc.gui.activity;

import java.net.URI;
import java.util.List;

import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.Icon;
import org.teleal.cling.model.meta.LocalDevice;
import org.teleal.cling.model.meta.RemoteDevice;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.Item;
import org.teleal.cling.support.model.item.VideoItem;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.FrameLayout;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.RelativeLayout.LayoutParams;

import com.hisilicon.dlna.dmc.gui.customview.AdapterItem;
import com.hisilicon.dlna.dmc.processor.impl.ImageCallbackImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.ImageCallback;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentTree;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.R;

public class LiveTVAdapter extends AbsListViewAdapter<AdapterItem> {
	private Context context;
	private LayoutInflater m_inflater = null;
	private static Bitmap BM_VIDEO;

	public LiveTVAdapter(Context theContext) {
		context = theContext;
		m_inflater = (LayoutInflater) theContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		if (BM_VIDEO == null || BM_VIDEO.isRecycled())
			BM_VIDEO = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_video_default);
	}

	@Override
	public void notifyVisibleItemChanged(AbsListView absListView) {
		int start = absListView.getFirstVisiblePosition() < getCount() ? absListView.getFirstVisiblePosition() : getCount() - 1;
		int end = absListView.getLastVisiblePosition() < getCount() ? absListView.getLastVisiblePosition() : getCount() - 1;
		for (int i = start; i <= end; i++)
		{
			View view = absListView.getChildAt(i - start);
			if (0 <= i && i < getCount())
				absListView.getAdapter().getView(i, view, absListView);
		}

	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		if (convertView == null || convertView instanceof ProgressBar)
		{
			convertView = m_inflater.inflate(R.layout.dlna_dms_livetv_item, null, false);
		}

		if (position % 2 == 0) {
			convertView.setBackgroundResource(R.drawable.bg_dms_item_odd);
		} else {
			convertView.setBackgroundResource(R.drawable.bg_dms_item_even);
		}

		if (convertView.getTag() == null)
		{
			setViewHolder(convertView);
		}

		final ViewHolder holder = (ViewHolder) convertView.getTag();

		AdapterItem adapterItem = getItem(position);

		Object object = adapterItem.getData();
		if (object instanceof Device)
		{
			initDeviceItem((Device) object, holder);
		}
		else if (object instanceof DIDLObject)
		{

			DIDLObject didlObject = (DIDLObject) object;

			if (didlObject.getId().equals("-1"))
			{
				return m_inflater.inflate(R.layout.dlna_dms_loadmoreitem, null);
			}
			else
			{
				initDIDLObject(position, didlObject, holder);
			}
		}

		return convertView;
	}

	private void setViewHolder(View view)
	{
		ViewHolder viewHolder = new ViewHolder();
		viewHolder.view = view;
		viewHolder.icon_layout = (FrameLayout) view.findViewById(R.id.icon_layout);
		viewHolder.icon = (ImageView) view.findViewById(R.id.icon);
		viewHolder.icon_box = (ImageView) view.findViewById(R.id.icon_box);
		viewHolder.title_layout = (LinearLayout) view.findViewById(R.id.title_layout);
		viewHolder.title = (TextView) view.findViewById(R.id.title);
		viewHolder.subtitle = (TextView) view.findViewById(R.id.subtitle);
		viewHolder.right_arrow = (ImageView) view.findViewById(R.id.right_arrow);
		view.setTag(viewHolder);
	}

	private class ViewHolder {
		View view;
		FrameLayout icon_layout;
		ImageView icon;
		ImageView icon_box;
		LinearLayout title_layout;
		TextView title;
		TextView subtitle;
		ImageView right_arrow;
	}

	@SuppressWarnings("rawtypes")
	private void initDeviceItem(final Device device, final ViewHolder holder)
	{
		holder.subtitle.setVisibility(View.GONE);
		holder.right_arrow.setVisibility(View.GONE);

		holder.icon.setTag("");
		holder.icon.setImageResource(R.drawable.icon);

		if (device instanceof LocalDevice)
		{
			holder.title.setText(R.string.myphone);
		}
		else
		{
			holder.title.setText(Utility.getDMSToastName(device.getDetails().getFriendlyName()));
			loadDeviceIcon(device, holder);
		}
	}

	@SuppressWarnings("rawtypes")
	private void loadDeviceIcon(final Device device, final ViewHolder holder)
	{
		String iconUrl = getDeviceIconUrl(device);

		if (null == iconUrl)
			return;

		final RemoteDevice remoteDevice = (RemoteDevice) device;

		String urlString = new StringBuilder()
		.append(remoteDevice.getIdentity().getDescriptorURL().getProtocol())
		.append("://")
		.append(remoteDevice.getIdentity().getDescriptorURL().getAuthority())
		.append(iconUrl).toString();

		holder.icon.setTag(urlString);
		ImageCallback callback = new ImageCallbackImpl(holder.icon);
		Bitmap catchBitmap = ThumbnailGenerator.getInstance().returnBitMap(urlString, callback);
		if (catchBitmap !=null && !catchBitmap.isRecycled())
		{
			holder.icon.setImageBitmap(catchBitmap);
		}
	}

	private String getDeviceIconUrl(final Device device)
	{
		final Icon[] icons = device.getIcons();
		if (icons != null && icons.length > 0 && icons[0] != null && icons[0].getUri() != null)
		{
			if (icons[0].getUri().getPath() != null && !icons[0].getUri().getPath().equals(""))
				return icons[0].getUri().toString();
		}
		return null;
	}

	private void initDIDLObject(int position, DIDLObject object, ViewHolder holder) {

		if (object instanceof Container)
		{
			initContainer(position, (Container) object, holder);
		}
		else if (object instanceof VideoItem)
		{
			initVideoItem(position, object, holder);
		}
	}

	private void initContainer(int position, Container container, ViewHolder holder)
	{
		holder.icon.setTag("");
		holder.icon.setImageBitmap(BM_VIDEO);

		RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(BM_VIDEO.getWidth(), BM_VIDEO.getHeight());
		holder.icon_layout.setLayoutParams(layoutParams);

		FrameLayout.LayoutParams frameParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
		holder.icon.setLayoutParams(frameParams);
		holder.icon_box.setLayoutParams(frameParams);

		holder.title_layout.setOrientation(LinearLayout.HORIZONTAL);
		holder.title.setText(container.getTitle());
		holder.subtitle.setText(" (" + container.getChildCount() + ")");

		loadFirstItemThumb(position, container, holder);
	}

	private void loadFirstItemThumb(int position, Container object, ViewHolder holder) {
		List<Item> items = object.getItems();

		Device device = UpnpProcessorImpl.getSington().getCurrentDMS();

		if (device instanceof LocalDevice && items.isEmpty()) {
			Container container = ContentTree.getContainer(object.getId());

			if (container == null)
				return;

			items = container.getItems();
		}

		if (!items.isEmpty()) {
			Item item = items.get(0);
			loadVideoThumb(position, item, holder);
		}
	}

	private void loadVideoThumb(int position, DIDLObject object, ViewHolder holder) {
		String objectUrl = HttpServerUtil.getUrlFrom(object);
		if (HttpServerUtil.mediaFromLocal(objectUrl)) {
			try{
				loadLocalVideo(object, holder, objectUrl);
				return;
			}
			catch (Exception ex)
			{
			}
		}

		URI uri = object.getFirstPropertyValue(DIDLObject.Property.UPNP.ALBUM_ART_URI.class);
		if (null != uri)
		{
			objectUrl = uri.toString();
			loadImage(position, holder, objectUrl);
		}
	}

	private void loadLocalVideo(DIDLObject object, ViewHolder holder,
			String objectUrl) {
		long videoId = Long.parseLong(object.getId());
		holder.icon.setTag(objectUrl);
		ImageCallback callback = new ImageCallbackImpl(holder.icon);
		ThumbnailGenerator.getInstance().returnLocalVideoThumb(videoId, objectUrl, callback);
	}

	private void loadImage(int position, ViewHolder holder, String objectUrl) {
		holder.icon.setTag(objectUrl);
		ImageCallback callback = new ImageCallbackImpl(holder.icon);
		ThumbnailGenerator.getInstance().returnImage(position, objectUrl, callback);
	}

	private void initVideoItem(int position, DIDLObject object, ViewHolder holder)
	{
		holder.right_arrow.setVisibility(View.GONE);
		holder.icon_layout.setVisibility(View.GONE);
		holder.subtitle.setVisibility(View.GONE);

		holder.icon.setTag("");

		GridView.LayoutParams layoutParams = new GridView.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, BM_VIDEO.getHeight());
		holder.view.setLayoutParams(layoutParams);

		holder.title.setText(object.getTitle());

		loadVideoThumb(position, object, holder);
	}


}
