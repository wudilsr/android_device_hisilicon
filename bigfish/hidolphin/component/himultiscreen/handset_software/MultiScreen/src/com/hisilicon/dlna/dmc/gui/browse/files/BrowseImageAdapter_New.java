package com.hisilicon.dlna.dmc.gui.browse.files;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.List;

import org.teleal.cling.support.model.DIDLObject;

import android.content.AsyncQueryHandler;
import android.content.AsyncTaskLoader;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Point;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.FrameLayout;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import com.hisilicon.dlna.dmc.gui.activity.AbsListViewAdapter;
import com.hisilicon.dlna.dmc.gui.browse.files.NativeImageLoader.NativeImageCallBack;
import com.hisilicon.dlna.dmc.processor.impl.ImageCallbackImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.ImageCallback;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.multiscreen.mybox.R;

public class BrowseImageAdapter_New extends AbsListViewAdapter<PlaylistItem>{
	private Point mPoint = new Point(0, 0);//用来封装ImageView的宽和高的对象
	private List<PictureNode> files = new ArrayList<PictureNode>();
	private LayoutInflater m_inflater = null;
	private Context context;
	private GridView mGridView;
	private Bitmap BM_IMAGE;
	private boolean mBusy = false;

	public BrowseImageAdapter_New(Context context, GridView mGridView){
		this.context = context;
		m_inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		this.mGridView = mGridView;
		if (BM_IMAGE == null || BM_IMAGE.isRecycled()){
			BM_IMAGE = BitmapFactory.decodeResource(context.getResources(), R.drawable.browse_image_default);
			mPoint.set(BM_IMAGE.getWidth(), BM_IMAGE.getHeight());
		}
	}

	public void setList(List<PictureNode> list){
		files = list;
	}
	
	public void setState(Boolean state){
		mBusy = state;
	}

	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return files.size();
	}

	@Override
	public long getItemId(int position) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		// TODO Auto-generated method stub
		final ViewHolder viewHolder;
		if (convertView == null){
			convertView = m_inflater.inflate(R.layout.dlna_pictures_show, null);
			viewHolder = new ViewHolder();
			viewHolder.item = (ImageView) convertView.findViewById(R.id.picutres_show_item);
			viewHolder.item_box = (ImageView) convertView.findViewById(R.id.new_icon_box);
			viewHolder.icon_layout = (FrameLayout) convertView.findViewById(R.id.new_icon_layout);
			viewHolder.item.setImageBitmap(BM_IMAGE);
			initItem(viewHolder);
			convertView.setTag(viewHolder);
		}else{
			viewHolder = (ViewHolder) convertView.getTag();
			viewHolder.item.setImageBitmap(BM_IMAGE);
		}
		String picUrl = files.get(position).getPath();
		viewHolder.item.setTag(picUrl);
		
		if(!mBusy){
			loadPic(picUrl, viewHolder.item);
		}else{
			
		}
		
		/**
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
		 */

		/**
		try{
			loadPicture(position, picUrl, viewHolder.item);
		}catch(Exception e){
			System.out.println("COme into load pic exception!!!");
			//			loadPicture(position, picUrl, viewHolder.item);
		}
		*/
		return convertView;
	}
	
	private void loadPic(String picUrl, ImageView item){
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
			item.setImageBitmap(bitmap);
		}else{
			item.setImageBitmap(BM_IMAGE);
		}
	}

	private class ViewHolder {
		ImageView item;
		ImageView item_box;
		FrameLayout icon_layout;
	}

	private void initItem(ViewHolder holder){
		RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(BM_IMAGE.getWidth(), BM_IMAGE.getHeight());
		holder.icon_layout.setLayoutParams(layoutParams);
		FrameLayout.LayoutParams frameParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
		holder.item.setLayoutParams(frameParams);
		holder.item_box.setLayoutParams(frameParams);
	}

	@Override
	public void notifyVisibleItemChanged(AbsListView absListView) {
		// TODO Auto-generated method stub
	}

	private List<AsyncLoadImageTask> taskList = new ArrayList<AsyncLoadImageTask>();
	/***********************************************分割线**************************************************/
	private void loadPicture(int position, String picUrl, ImageView item){
		//首先我们先通过cancelPotentialLoad方法去判断imageview是否有线程正在为它加载图片资源，
		//如果有现在正在加载，那么判断加载的这个图片资源（url）是否和现在的图片资源一样，不一样则取消之前的线程（之前的下载线程作废）。
		//见下面cancelPotentialLoad方法代码
		if (cancelPotentialLoad(picUrl, item)) {
			AsyncLoadImageTask task = new AsyncLoadImageTask(item);
			LoadedDrawable loadedDrawable = new LoadedDrawable(task);
			item.setImageDrawable(loadedDrawable);
			taskList.add(task);
			try{
				task.execute(position);
			}catch(Exception e){}

		} 
	}

	//加载图片的异步任务        
	private class AsyncLoadImageTask extends AsyncTask<Integer, Void, Bitmap>{
		private String url = null;
		private final WeakReference<ImageView> imageViewReference;

		public AsyncLoadImageTask(ImageView imageview) {
			super();
			// TODO Auto-generated constructor stub
			imageViewReference = new WeakReference<ImageView>(imageview);
		}

		@Override
		protected Bitmap doInBackground(Integer... params) {
			// TODO Auto-generated method stub
			Bitmap bitmap = null;
			//                    this.url = mList.get(params[0]);  
			this.url = files.get(params[0]).getPath();
			bitmap = getBitmapFromUrl(url);
			NativeImageLoader.getInstance().addBitmapToMemoryCache(url, bitmap);
			return bitmap;
		}

		@Override
		protected void onPostExecute(Bitmap resultBitmap) {
			// TODO Auto-generated method stub
			if(isCancelled()){
				resultBitmap = null;
			}
			if(imageViewReference != null){
				ImageView imageview = imageViewReference.get();
				AsyncLoadImageTask loadImageTask = getAsyncLoadImageTask(imageview);
				if (this == loadImageTask) {
					imageview.setImageBitmap(resultBitmap);
					//					imageview.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
				}
			}
			super.onPostExecute(resultBitmap);
		}                                                        
	}


	private boolean cancelPotentialLoad(String url,ImageView imageview){
		AsyncLoadImageTask loadImageTask = getAsyncLoadImageTask(imageview);

		if(taskList.size()>=90){
			for(int i=0; i<=20;i++){
				taskList.get(0).cancel(true);
				taskList.remove(0);
			}
		}

		if (loadImageTask != null) {
			String bitmapUrl = loadImageTask.url;
			if ((bitmapUrl == null) || (!bitmapUrl.equals(url))) {
				loadImageTask.cancel(true);                        
			} else {
				// 相同的url已经在加载中.
				return false;
			}
		}
		return true;

	}

	//当 loadImageTask.cancel(true)被执行的时候，则AsyncLoadImageTask 就会被取消，
	//当AsyncLoadImageTask 任务执行到onPostExecute的时候，如果这个任务加载到了图片，
	//它也会把这个bitmap设为null了。 
	//getAsyncLoadImageTask代码如下：
	private AsyncLoadImageTask getAsyncLoadImageTask(ImageView imageview){
		if (imageview != null) {
			Drawable drawable = imageview.getDrawable();
			if (drawable instanceof LoadedDrawable) {
				LoadedDrawable loadedDrawable = (LoadedDrawable)drawable;
				return loadedDrawable.getLoadImageTask();
			}
		}
		return null;
	}

	//该类功能为：记录imageview加载任务并且为imageview设置默认的drawable
	public static class LoadedDrawable extends ColorDrawable{
		private final WeakReference<AsyncLoadImageTask> loadImageTaskReference;

		public LoadedDrawable(AsyncLoadImageTask loadImageTask) {
			super(Color.TRANSPARENT);
			loadImageTaskReference =
					new WeakReference<AsyncLoadImageTask>(loadImageTask);
		}

		public AsyncLoadImageTask getLoadImageTask() {
			return loadImageTaskReference.get();
		}

	}

	private Bitmap getBitmapFromUrl(String url){
		Bitmap bt = NativeImageLoader.getInstance().getBitmapFromMemCache(url);
		if(bt!=null)
			return bt;
		return NativeImageLoader.getInstance().decodeThumbBitmapForFile(url, BM_IMAGE.getWidth(), BM_IMAGE.getHeight());
	}
}
