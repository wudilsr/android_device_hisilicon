package com.hisilicon.dlna.dmc.gui.customview;

import java.net.URI;
import java.util.List;

import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.LocalDevice;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.AudioItem;
import org.teleal.cling.support.model.item.Item;

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
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.hisilicon.dlna.dmc.gui.activity.AbsListViewAdapter;
import com.hisilicon.dlna.dmc.processor.impl.ImageCallbackImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.ImageCallback;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentTree;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.MyApp;
import com.hisilicon.multiscreen.mybox.R;

public class BrowseMusicAdapter extends AbsListViewAdapter<PlaylistItem> {
	private Context context;
	private LayoutInflater m_inflater = null;
	private static Bitmap BM_MUSIC;

	public BrowseMusicAdapter(Context theContext) {
		context = theContext;
		m_inflater = (LayoutInflater) theContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		if (BM_MUSIC == null || BM_MUSIC.isRecycled())
			BM_MUSIC = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_music_default);
	}

	@Override
	public void notifyVisibleItemChanged(AbsListView absListView)
	{
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
			convertView = m_inflater.inflate(R.layout.dlna_dms_browsemusic_item, null, false);
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

		PlaylistItem playlistItem = getItem(position);

		Object object = playlistItem.getData();

		if (object instanceof DIDLObject) {

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
		viewHolder.title = (TextView) view.findViewById(R.id.title);
		viewHolder.subtitle = (TextView) view.findViewById(R.id.subtitle);
		viewHolder.music_num = (TextView) view.findViewById(R.id.music_num);
		viewHolder.right_arrow = (ImageView) view.findViewById(R.id.right_arrow);
		view.setTag(viewHolder);
	}

	private class ViewHolder {
		View view;
		FrameLayout icon_layout;
		ImageView icon;
		ImageView icon_box;
		TextView title;
		TextView subtitle;
		TextView music_num;
		ImageView right_arrow;
	}

	private void initDIDLObject(int position, DIDLObject object, ViewHolder holder) {

		if (object instanceof Container)
		{
			initContainer(position, (Container) object, holder);
		}
		else if (object instanceof AudioItem)
		{
			initMusicItem(position, object, holder);

			String objectUrl = HttpServerUtil.getUrlFrom(object);

			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();

			if (dmrProcessor != null && objectUrl.equals(dmrProcessor.getCurrentTrackURI()))
			{
				holder.right_arrow.setVisibility(View.VISIBLE);
				holder.right_arrow.setImageResource(R.drawable.rc_music_quick_play_item_bg);
				holder.title.setTextColor(MyApp.getApplication().getResources().getColor(R.color.green));
				holder.subtitle.setTextColor(MyApp.getApplication().getResources().getColor(R.color.green_subtext));
			}
			else
			{
				holder.right_arrow.setVisibility(View.GONE);
				holder.title.setTextColor(MyApp.getApplication().getResources().getColor(R.color.black));
				holder.subtitle.setTextColor(MyApp.getApplication().getResources().getColor(R.color.dms_subtext_color));
			}
		}
	}

	private void initContainer(int position, Container container, ViewHolder holder)
	{
		holder.icon_layout.setVisibility(View.GONE);
		holder.subtitle.setVisibility(View.GONE);

		holder.icon.setTag("");

		String title = container.getTitle();

		Device currentDMS = UpnpProcessorImpl.getSington().getCurrentDMS();
		if (currentDMS instanceof LocalDevice && title.equals(Utility.getString(R.string.playlist))) {
			holder.icon_layout.setVisibility(View.VISIBLE);
			holder.icon.setImageBitmap(BM_MUSIC);

			RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(BM_MUSIC.getWidth(), BM_MUSIC.getHeight());
			holder.icon_layout.setLayoutParams(layoutParams);

			FrameLayout.LayoutParams frameParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
			holder.icon.setLayoutParams(frameParams);
			holder.icon_box.setLayoutParams(frameParams);
		} else {
			GridView.LayoutParams layoutParams = new GridView.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, BM_MUSIC.getHeight());
			holder.view.setLayoutParams(layoutParams);
		}

		holder.title.setText(title);

		holder.music_num.setText(container.getChildCount() + Utility.getString(R.string.music_num));

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
			loadMusicAlbumArt(position, item, holder);
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
		ThumbnailGenerator.getInstance().returnImage(objectUrl, callback);
	}

	private void initMusicItem(int position, DIDLObject object, ViewHolder holder)
	{
		holder.icon.setTag("");
		holder.icon.setImageBitmap(BM_MUSIC);

		RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(BM_MUSIC.getWidth(), BM_MUSIC.getHeight());
		holder.icon_layout.setLayoutParams(layoutParams);

		FrameLayout.LayoutParams frameParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
		holder.icon.setLayoutParams(frameParams);
		holder.icon_box.setLayoutParams(frameParams);

		holder.title.setText(object.getTitle());
		holder.subtitle.setText(object.getCreator());

		loadMusicAlbumArt(position, object, holder);
	}
}
