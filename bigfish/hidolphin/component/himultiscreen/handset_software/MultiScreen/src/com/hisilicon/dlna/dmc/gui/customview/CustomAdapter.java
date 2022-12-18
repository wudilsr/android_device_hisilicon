package com.hisilicon.dlna.dmc.gui.customview;

import java.net.URI;
import java.util.List;

import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.Icon;
import org.teleal.cling.model.meta.LocalDevice;
import org.teleal.cling.model.meta.RemoteDevice;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.Res;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.AudioItem;
import org.teleal.cling.support.model.item.ImageItem;
import org.teleal.cling.support.model.item.Item;
import org.teleal.cling.support.model.item.MusicTrack;
import org.teleal.cling.support.model.item.VideoItem;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.hisilicon.dlna.dmc.gui.activity.AbsListViewAdapter;
import com.hisilicon.dlna.dmc.processor.impl.ImageCallbackImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.ImageCallback;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentNode;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentTree;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.MyApp;
import com.hisilicon.multiscreen.mybox.R;

public class CustomAdapter extends AbsListViewAdapter<AdapterItem> {
	private LayoutInflater m_inflater = null;
	private MediaType type;
	private static Bitmap BM_IMAGE;
	private static Bitmap BM_IMAGE_LARGE;
	private static Bitmap BM_VIDEO;
	private static Bitmap BM_AUDIO;
	private boolean isOtherBrowse = false;

	public CustomAdapter(Context context, MediaType type) {
		this.type = type;
		m_inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		if (BM_IMAGE == null || BM_IMAGE.isRecycled())
			BM_IMAGE = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_container_image_default);
		if (BM_IMAGE_LARGE == null || BM_IMAGE_LARGE.isRecycled())
			BM_IMAGE_LARGE = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_image_default);
		if (BM_VIDEO == null || BM_VIDEO.isRecycled())
			BM_VIDEO = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_video_default);
		if (BM_AUDIO == null || BM_AUDIO.isRecycled())
			BM_AUDIO = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_music_default);

	}
	
	public void setOtherBrowse(boolean isOtherBrowse) {
		this.isOtherBrowse = isOtherBrowse;
	}

	@SuppressWarnings("rawtypes")
	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		if (convertView == null || convertView instanceof ProgressBar)
		{
			convertView = m_inflater.inflate(R.layout.dlna_dms_browseview_item, null, false);
		}
		
		if (position % 2 == 0) {
			convertView.setBackgroundResource(R.drawable.bg_dms_item_even);
		} else {
			convertView.setBackgroundResource(R.drawable.bg_dms_item_odd);
		}

		if (convertView.getTag() == null)
		{
			setViewHolder(convertView);
		}

		final ViewHolder holder = (ViewHolder) convertView.getTag();

		final AdapterItem adapterItem = getItem(position);

		Object object = adapterItem.getData();

		convertView.setPadding(0, 0, 0, 0);
		if (object instanceof Device)
		{
			convertView.setPadding(10, 0, 0, 0);
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

	public void setViewHolder(View view)
	{
		ViewHolder viewHolder = new ViewHolder();
		viewHolder.parent = view;
		viewHolder.name_play_layout = (RelativeLayout) view.findViewById(R.id.name_play_layout);
		viewHolder.title_layout = (LinearLayout) view.findViewById(R.id.title_layout);
		viewHolder.name = (TextView) view.findViewById(R.id.name);
		viewHolder.subname = (TextView) view.findViewById(R.id.subname);
		viewHolder.icon = (ImageView) view.findViewById(R.id.icon);
		viewHolder.music_num = (TextView) view.findViewById(R.id.music_num);
		viewHolder.playing = (ImageView) view.findViewById(R.id.playing);
		view.setTag(viewHolder);
	}

	@SuppressWarnings("rawtypes")
	private void initDeviceItem(final Device device, final ViewHolder holder)
	{
		holder.subname.setVisibility(View.GONE);
		holder.playing.setVisibility(View.GONE);

		if (device instanceof LocalDevice)
		{
			holder.name.setText(R.string.myphone);
			holder.icon.setTag("");
			holder.icon.setImageResource(R.drawable.icon);
		}
		else
		{
			holder.name.setText(device.getDetails().getFriendlyName());
			holder.icon.setTag("");
			holder.icon.setImageResource(R.drawable.icon);
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

	private void initDIDLObject(int position, DIDLObject object, ViewHolder holder)
	{
		if (object.getId().equals("-1"))
		{
			holder.icon.setTag("");
			holder.icon.setVisibility(View.GONE);
			holder.name.setText(object.getTitle());
			holder.playing.setVisibility(View.GONE);
			return;
		}
		holder.icon.setVisibility(View.VISIBLE);

		if (object instanceof Container)
		{
			initContainer(position, (Container) object, holder);
		}
		else
		{
			holder.subname.setVisibility(View.VISIBLE);
			holder.playing.setVisibility(View.GONE);
			
			if (MediaType.VIDEO.equals(type)) {
				holder.icon.setImageBitmap(BM_VIDEO);
				holder.icon.setLayoutParams(new RelativeLayout.LayoutParams(BM_VIDEO.getWidth(), BM_VIDEO.getHeight()));
			} else if (MediaType.MUSIC.equals(type)) {
				holder.icon.setImageBitmap(BM_AUDIO);
				holder.icon.setLayoutParams(new RelativeLayout.LayoutParams(BM_AUDIO.getWidth(), BM_AUDIO.getHeight()));
			} else if (MediaType.IMAGE.equals(type)) {
				holder.icon.setImageBitmap(BM_IMAGE_LARGE);
				holder.icon.setLayoutParams(new RelativeLayout.LayoutParams(BM_IMAGE_LARGE.getWidth(), BM_IMAGE_LARGE.getHeight()));
			} else if (MediaType.LIVETV.equals(type)) {
				holder.icon.setVisibility(View.GONE);
				holder.subname.setVisibility(View.GONE);
				holder.parent.setLayoutParams(new GridView.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, BM_VIDEO.getHeight()));
			}
			
			String objectUrl = HttpServerUtil.getUrlFrom(object);

			if (object instanceof AudioItem || object instanceof MusicTrack)
			{
				initMusicItem(position, object, holder);
				
				DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
				if (dmrProcessor != null && objectUrl.equals(dmrProcessor.getCurrentTrackURI()))
				{
					holder.playing.setVisibility(View.VISIBLE);
					holder.name.setTextColor(MyApp.getApplication().getResources().getColor(R.color.green));
					holder.subname.setTextColor(MyApp.getApplication().getResources().getColor(R.color.green_subtext));
				}
				else
				{
					holder.playing.setVisibility(View.GONE);
					holder.name.setTextColor(MyApp.getApplication().getResources().getColor(R.color.black));
					holder.subname.setTextColor(MyApp.getApplication().getResources().getColor(R.color.dms_subtext_color));
				}
			}
			else if (object instanceof VideoItem)
			{
				initVideoItem(position, object, holder);
			}
			else if (object instanceof ImageItem)
			{
				initImageItem(position, object, holder);
			}

		}
	}

	private void initContainer(int position, Container container, ViewHolder holder)
	{
		holder.icon.setTag("");
		holder.subname.setVisibility(View.VISIBLE);
		holder.subname.setText(" (" + container.getChildCount() + ")");
		holder.subname.setTextSize(20);
		
		holder.title_layout.setOrientation(LinearLayout.HORIZONTAL);
		
		String title = container.getTitle();
		holder.name.setText(title);
		
		if (isOtherBrowse) {
			if (MediaType.MUSIC.equals(type)) {
				holder.subname.setVisibility(View.GONE);
				holder.music_num.setVisibility(View.VISIBLE);
				holder.music_num.setText(container.getChildCount() + Utility.getString(R.string.music_num));
				
				Device currentDMS = UpnpProcessorImpl.getSington().getCurrentDMS();
				if (currentDMS instanceof LocalDevice) {
					if (!title.equals(Utility.getString(R.string.playlist)))
						holder.icon.setVisibility(View.GONE);
				}
			}
			holder.playing.setVisibility(View.VISIBLE);
			holder.playing.setImageResource(R.drawable.rc_right_arrow);
		} else {
			holder.music_num.setVisibility(View.GONE);
			holder.playing.setVisibility(View.GONE);
		}
		
		if (MediaType.VIDEO.equals(type)) {
			holder.icon.setImageBitmap(BM_VIDEO);
			holder.icon.setLayoutParams(new RelativeLayout.LayoutParams(BM_VIDEO.getWidth(), BM_VIDEO.getHeight()));
		} else if (MediaType.MUSIC.equals(type)) {
			holder.icon.setImageBitmap(BM_AUDIO);
			holder.icon.setLayoutParams(new RelativeLayout.LayoutParams(BM_AUDIO.getWidth(), BM_AUDIO.getHeight()));
			GridView.LayoutParams layoutParams = new GridView.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, BM_AUDIO.getHeight());
			holder.parent.setLayoutParams(layoutParams);
		} else if (MediaType.IMAGE.equals(type)) {
			holder.icon.setImageBitmap(BM_IMAGE);
			holder.icon.setLayoutParams(new RelativeLayout.LayoutParams(BM_IMAGE.getWidth(), BM_IMAGE.getHeight()));
		} else if (MediaType.LIVETV.equals(type)) {
			holder.icon.setVisibility(View.GONE);
			holder.subname.setVisibility(View.GONE);
			GridView.LayoutParams layoutParams = new GridView.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, BM_VIDEO.getHeight());
			holder.parent.setLayoutParams(layoutParams);
		}
		
		loadFirstItemThumb(position, container, holder);
	}
	
	private void loadFirstItemThumb(int position, Container object, ViewHolder holder) {
		List<Item> items = object.getItems();
		Device device = UpnpProcessorImpl.getSington().getCurrentDMS();
		if (device instanceof LocalDevice && items.isEmpty()) {
			ContentNode contentNode = ContentTree.getNode(object.getId());
			if (contentNode == null)
				return;
			Container container = contentNode.getContainer();
			if (container == null)
				return;
			items = container.getItems();
		}
		
		if (!items.isEmpty()) {
			Item item = items.get(0);
			if (item instanceof AudioItem)
				loadMusicAlbumArt(position, item, holder);
			else if (item instanceof VideoItem)
				loadVideoThumb(position, item, holder);
			else if (item instanceof ImageItem)
				loadImageThumb(position, item, holder);
		}
	}
	
	private void loadMusicAlbumArt(int position, DIDLObject object, ViewHolder holder) {
		URI uri = object.getFirstPropertyValue(DIDLObject.Property.UPNP.ALBUM_ART_URI.class);
		if (null != uri)
		{
			String objectUrl = uri.toString();
			loadImage(position, holder, objectUrl);
		}
	}
	
	private void loadImage(int position, ViewHolder holder, String objectUrl) {
		holder.icon.setTag(objectUrl);
		ImageCallback callback = new ImageCallbackImpl(holder.icon);
		ThumbnailGenerator.getInstance().returnImage(position, objectUrl, callback);
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
	
	private void loadImageThumb(int position, DIDLObject object, ViewHolder holder) {
		String objectUrl = HttpServerUtil.getUrlFrom(object);
		if (HttpServerUtil.mediaFromLocal(objectUrl)) {
			try{
				loadLocalImage(position, object, holder, objectUrl);
				return;
			}
			catch (Exception ex)
			{
			}
		}
		
		URI uri = object.getFirstPropertyValue(DIDLObject.Property.UPNP.ALBUM_ART_URI.class);
		if (null != uri)
			objectUrl = uri.toString();
		loadImage(position, holder, objectUrl);
	}
	
	private void loadLocalImage(int position, DIDLObject object, ViewHolder holder,
			String objectUrl) {
		long videoId = Long.parseLong(object.getId());
		holder.icon.setTag(objectUrl);
		ImageCallback callback = new ImageCallbackImpl(holder.icon);
		ThumbnailGenerator.getInstance().returnLocalImageThumb(position, videoId, objectUrl, callback);
	}

	private void initMusicItem(int position, DIDLObject object, ViewHolder holder)
	{
		holder.icon.setTag("");
		holder.icon.setImageBitmap(BM_AUDIO);
		holder.name.setText(object.getTitle());
		holder.subname.setText(object.getCreator());

		loadMusicAlbumArt(position, object, holder);
	}
	
	private void initVideoItem(int position, DIDLObject object, ViewHolder holder)
	{
		holder.icon.setTag("");
		holder.icon.setImageBitmap(BM_VIDEO);
		holder.name.setText(object.getTitle());
		Res res = object.getFirstResource();
		String time = res != null ? res.getDuration() : "";
		holder.subname.setText(Utility.timeStringToMinute(time) + Utility.getString(R.string.minute));
		
		loadVideoThumb(position, object, holder);
	}

	private void initImageItem(int position, DIDLObject object, ViewHolder holder)
	{
		holder.icon.setTag("");
		holder.icon.setImageBitmap(BM_IMAGE);
		holder.name_play_layout.setVisibility(View.GONE);

		loadImageThumb(position, object, holder);
	}

	private void initPlaylistItem(PlaylistItem object, ViewHolder holder, int position)
	{
		holder.name.setText(object.getTitle());
		String imageUrl = object.getUrl();
		switch (object.getType()) {
		case AUDIO_LOCAL:
		case AUDIO_REMOTE:
			holder.icon.setTag("");
			holder.icon.setImageBitmap(BM_AUDIO);
			
			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
			if (dmrProcessor != null && imageUrl.equals(dmrProcessor.getCurrentTrackURI())) {
				holder.playing.setVisibility(View.VISIBLE);
			} else {
				holder.playing.setVisibility(View.GONE);
			}
			break;
		case VIDEO_LOCAL:
		case VIDEO_REMOTE:
			holder.icon.setTag("");
			holder.icon.setImageBitmap(BM_VIDEO);
			holder.playing.setVisibility(View.GONE);
			break;
		case IMAGE_LOCAL:
		case IMAGE_REMOTE: {
			holder.playing.setVisibility(View.GONE);
			
			holder.icon.setTag(imageUrl);
			holder.icon.setImageBitmap(BM_IMAGE);
			ImageCallback callback = new ImageCallbackImpl(holder.icon);
			Bitmap cachedImage = ThumbnailGenerator.getInstance().returnBitMap(imageUrl, callback);

			if (null != cachedImage && !cachedImage.isRecycled())
				holder.icon.setImageBitmap(cachedImage);
			break;
		}
		default:
			holder.icon.setTag("");
			break;
		}
	}

	private class ViewHolder {
		View parent;
		RelativeLayout name_play_layout;
		LinearLayout title_layout;
		TextView name;
		TextView subname;
		ImageView icon;
		TextView music_num;
		ImageView playing;
	}

	@Override
	public void notifyVisibleItemChanged(AbsListView gridView)
	{
		int start = gridView.getFirstVisiblePosition() < getCount() ? gridView.getFirstVisiblePosition() : getCount() - 1;
		int end = gridView.getLastVisiblePosition() < getCount() ? gridView.getLastVisiblePosition() : getCount() - 1;
		for (int i = start; i <= end; i++)
		{
			View view = gridView.getChildAt(i - start);
			if (0 <= i && i < getCount())
				gridView.getAdapter().getView(i, view, gridView);
		}
	}
}
