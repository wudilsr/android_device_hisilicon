package com.hisilicon.dlna.dmc.gui.customview;

import java.net.URI;

import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.item.ImageItem;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.FrameLayout;
import android.widget.Gallery;
import android.widget.ImageView;
import android.widget.ProgressBar;

import com.hisilicon.dlna.dmc.gui.activity.AbsListViewAdapter;
import com.hisilicon.dlna.dmc.processor.impl.ImageCallbackImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.ImageCallback;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.multiscreen.mybox.R;

public class PlayingImageAdapter extends AbsListViewAdapter<PlaylistItem> {
	private Context context;
	private LayoutInflater m_inflater = null;
	private static Bitmap BM_IMAGE;
	private int currentPosition = 0;

	public PlayingImageAdapter(Context theContext) {
		context = theContext;
		m_inflater = (LayoutInflater) theContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		if (BM_IMAGE == null || BM_IMAGE.isRecycled())
			BM_IMAGE = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_container_image_default);
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
	
	public void setCurrentPosition(int position) {
		currentPosition = position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		if (convertView == null || convertView instanceof ProgressBar)
		{
			convertView = m_inflater.inflate(R.layout.dlna_dms_playingimage_item, null, false);
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
				if (didlObject instanceof ImageItem)
				{
					initImageItem(position, didlObject, holder);
				}
			}
		}

		return convertView;
	}

	private void setViewHolder(View view)
	{
		ViewHolder viewHolder = new ViewHolder();
		viewHolder.parent = view;
		viewHolder.icon_layout = (FrameLayout) view.findViewById(R.id.icon_layout);
		viewHolder.icon = (ImageView) view.findViewById(R.id.icon);
		viewHolder.icon_box = (ImageView) view.findViewById(R.id.icon_box);
		view.setTag(viewHolder);
	}

	private class ViewHolder {
		View parent;
		FrameLayout icon_layout;
		ImageView icon;
		ImageView icon_box;
	}

	@SuppressWarnings("deprecation")
	private void initImageItem(int position, DIDLObject object, ViewHolder holder)
	{
		holder.icon.setTag("");
		holder.icon.setImageBitmap(BM_IMAGE);

		if (currentPosition == position)
		{
			Gallery.LayoutParams layoutParams = new Gallery.LayoutParams(BM_IMAGE.getWidth() + 20, BM_IMAGE.getHeight() + 20);
			holder.icon_layout.setLayoutParams(layoutParams);
		}
		else
		{
			Gallery.LayoutParams layoutParams = new Gallery.LayoutParams(BM_IMAGE.getWidth(), BM_IMAGE.getHeight());
			holder.icon_layout.setLayoutParams(layoutParams);
		}

		FrameLayout.LayoutParams frameParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
		holder.icon.setLayoutParams(frameParams);
		holder.icon_box.setLayoutParams(frameParams);

		loadImageThumb(position, object, holder);
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

	private void loadLocalImage(int position, DIDLObject object, ViewHolder holder, String objectUrl) {
		long videoId = Long.parseLong(object.getId());
		holder.icon.setTag(objectUrl);
		ImageCallback callback = new ImageCallbackImpl(holder.icon);
		ThumbnailGenerator.getInstance().returnLocalImageThumb(position, videoId, objectUrl, callback);
	}

	private void loadImage(int position, ViewHolder holder, String objectUrl) {
		holder.icon.setTag(objectUrl);
		ImageCallback callback = new ImageCallbackImpl(holder.icon);
		ThumbnailGenerator.getInstance().returnThumbImage(position, objectUrl, callback);
	}
}
