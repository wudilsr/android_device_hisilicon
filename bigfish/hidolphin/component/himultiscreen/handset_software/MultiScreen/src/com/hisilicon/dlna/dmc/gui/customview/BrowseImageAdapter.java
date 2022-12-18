package com.hisilicon.dlna.dmc.gui.customview;

import java.net.URI;
import java.util.List;

import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.LocalDevice;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.ImageItem;
import org.teleal.cling.support.model.item.Item;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Point;
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

import com.hisilicon.dlna.dmc.gui.activity.AbsListViewAdapter;
import com.hisilicon.dlna.dmc.gui.browse.files.NativeImageLoader;
import com.hisilicon.dlna.dmc.gui.browse.files.NativeImageLoader.NativeImageCallBack;
import com.hisilicon.dlna.dmc.processor.impl.ImageCallbackImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.ImageCallback;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentTree;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.multiscreen.mybox.R;

public class BrowseImageAdapter extends AbsListViewAdapter<PlaylistItem> {
	private Context context;
	private LayoutInflater m_inflater = null;
	private static Bitmap BM_IMAGE;
	private static Bitmap BM_IMAGE_CONTAINER;
	private Point mPoint = new Point(0, 0);//用来封装ImageView的宽和高的对象

	public BrowseImageAdapter(Context theContext) {
		context = theContext;
		m_inflater = (LayoutInflater) theContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		if (BM_IMAGE == null || BM_IMAGE.isRecycled()){
			BM_IMAGE = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_image_default);
			mPoint.set(BM_IMAGE.getWidth(), BM_IMAGE.getHeight());
		}
		if (BM_IMAGE_CONTAINER == null || BM_IMAGE_CONTAINER.isRecycled())
			BM_IMAGE_CONTAINER = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_container_image_default);
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
			convertView = m_inflater.inflate(R.layout.dlna_dms_browseimage_item, null, false);
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
				if (didlObject instanceof ImageItem) {
					GridView gridview = (GridView) parent;
					gridview.setPadding(5, 5, 5, 5);
					gridview.setHorizontalSpacing(4);
					gridview.setVerticalSpacing(4);

					holder.view.setPadding(0, 0, 0, 0);
				} else {
					GridView gridview = (GridView) parent;
					gridview.setPadding(0, 5, 0, 5);
					gridview.setHorizontalSpacing(0);
					gridview.setVerticalSpacing(0);
					
					holder.view.setPadding(5, 3, 5, 3);
				}

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

	private void initDIDLObject(int position, DIDLObject object, ViewHolder holder) {

		if (object instanceof Container)
		{
			initContainer(position, (Container) object, holder);
		}
		else if (object instanceof ImageItem)
		{
			initImageItem(position, object, holder);
		}
	}

	private void initContainer(int position, Container container, ViewHolder holder)
	{
		holder.icon.setTag("");
		holder.icon.setImageBitmap(BM_IMAGE_CONTAINER);

		RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(BM_IMAGE_CONTAINER.getWidth(), BM_IMAGE_CONTAINER.getHeight());
		holder.icon_layout.setLayoutParams(layoutParams);

		FrameLayout.LayoutParams frameParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
		holder.icon.setLayoutParams(frameParams);
		holder.icon_box.setLayoutParams(frameParams);

		String title = container.getTitle();
		holder.title.setText(title);
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
			loadImageThumb(position, item, holder);
		}
	}

	private void initImageItem(int position, DIDLObject object, ViewHolder holder)
	{
		holder.title_layout.setVisibility(View.GONE);
		holder.right_arrow.setVisibility(View.GONE);

		holder.icon.setTag("");
		holder.icon.setImageBitmap(BM_IMAGE);

		RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(BM_IMAGE.getWidth(), BM_IMAGE.getHeight());
		holder.icon_layout.setLayoutParams(layoutParams);

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
		loadImage(position, holder, objectUrl, object.getId());
	}

	private void loadLocalImage(int position, DIDLObject object, ViewHolder holder, String objectUrl) {
		long videoId = Long.parseLong(object.getId());
		holder.icon.setTag(objectUrl);
		ImageCallback callback = new ImageCallbackImpl(holder.icon);
		ThumbnailGenerator.getInstance().returnLocalImageThumb(position, videoId, objectUrl, callback);
	}
	
	private void loadPic(String picUrl, final ImageView mImageView){
		Bitmap bitmap = NativeImageLoader.getInstance().loadNativeImage(picUrl, mPoint, new NativeImageCallBack() {

			@Override
			public void onImageLoader(Bitmap bitmap, String path) {
				// TODO Auto-generated method stub
//				ImageView mImageView = (ImageView) mGridView.findViewWithTag(path);
				if(bitmap != null && !bitmap.isRecycled() && mImageView != null){
					mImageView.setImageBitmap(bitmap);
				}
			}});
		if(bitmap != null&&!bitmap.isRecycled()){
			mImageView.setImageBitmap(bitmap);
		}else{
			mImageView.setImageBitmap(BM_IMAGE);
		}
	}

	private void loadImage(int position, ViewHolder holder, String objectUrl, String id) {
		holder.icon.setTag(objectUrl);
		ImageCallback callback = new ImageCallbackImpl(holder.icon, id);
		ThumbnailGenerator.getInstance().returnImage(position, objectUrl, callback);
	}
	
}
