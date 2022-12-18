package com.hisilicon.dlna.dmc.gui.browse.files;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Point;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.FrameLayout;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.hisilicon.dlna.dmc.gui.browse.files.NativeImageLoader.NativeImageCallBack;
import com.hisilicon.multiscreen.mybox.R;

public class FolderAdapter extends BaseAdapter{
	private Point mPoint = new Point(0, 0);//用来封装ImageView的宽和高的对象
	private List<FolderBean> folders = new ArrayList<FolderBean>();
	private Context context;
	private LayoutInflater m_inflater = null;
	private Bitmap BM_IMAGE;
	private GridView mGridView;
	
	public FolderAdapter(Context context, GridView mGridView){
		this.context = context;
		this.mGridView = mGridView;
		m_inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		if (BM_IMAGE == null || BM_IMAGE.isRecycled()){
			BM_IMAGE = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_image_default);
			mPoint.set(BM_IMAGE.getWidth(), BM_IMAGE.getHeight());
		}
	}
	
	public void addFolderBeans(final List<FolderBean> folders){
		if(folders==null)
			return;
		this.folders = folders;
	}

	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return folders.size();
	}

	@Override
	public Object getItem(int position) {
		// TODO Auto-generated method stub
		return folders.get(position);
	}

	@Override
	public long getItemId(int position) {
		// TODO Auto-generated method stub
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		// TODO Auto-generated method stub
		final ViewHolder viewHolder;
		if(convertView==null){
			convertView = m_inflater.inflate(R.layout.dlna_dms_browseimage_item, null, false);
			viewHolder = new ViewHolder();
			viewHolder.item = (ImageView) convertView.findViewById(R.id.icon);
			viewHolder.item_box = (ImageView) convertView.findViewById(R.id.icon_box);
			viewHolder.icon_layout = (FrameLayout) convertView.findViewById(R.id.icon_layout);
			viewHolder.folderName = (TextView) convertView.findViewById(R.id.title);
			viewHolder.count = (TextView) convertView.findViewById(R.id.subtitle);
			initItem(viewHolder);
			convertView.setTag(viewHolder);
		}else{
			viewHolder = (ViewHolder) convertView.getTag();
			viewHolder.item.setImageBitmap(BM_IMAGE);
		}
		if (position % 2 == 0) {
			convertView.setBackgroundResource(R.drawable.bg_dms_item_even);
		} else {
			convertView.setBackgroundResource(R.drawable.bg_dms_item_odd);
		}
		FolderBean folderBean = folders.get(position);
		if(folderBean==null)
			return null;
		viewHolder.folderName.setText(folderBean.getFolderName());
		viewHolder.count.setText(" (" + folderBean.getFileCounts() + ")");
		String picUrl = folderBean.getTopImagePath();
		viewHolder.item.setTag(picUrl);
		Bitmap bitmap = NativeImageLoader.getInstance().loadNativeImage(picUrl, mPoint, new NativeImageCallBack() {

			@Override
			public void onImageLoader(Bitmap bitmap, String path) {
				// TODO Auto-generated method stub
				ImageView mImageView = (ImageView) mGridView.findViewWithTag(path);
				if(bitmap != null && !bitmap.isRecycled() && mImageView != null){
					mImageView.setImageBitmap(bitmap);
				}
			}});
		if(bitmap != null&&!bitmap.isRecycled()){
			viewHolder.item.setImageBitmap(bitmap);
		}else{
			viewHolder.item.setImageBitmap(BM_IMAGE);
		}
		return convertView;
	}
	
	private class ViewHolder {
		ImageView item;
		ImageView item_box;
		FrameLayout icon_layout;
		TextView folderName;
		TextView count;
	}
	
	private void initItem(ViewHolder holder){
		RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(BM_IMAGE.getWidth(), BM_IMAGE.getHeight());
		holder.icon_layout.setLayoutParams(layoutParams);
		FrameLayout.LayoutParams frameParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
		holder.item.setLayoutParams(frameParams);
		holder.item_box.setLayoutParams(frameParams);
	}

}
