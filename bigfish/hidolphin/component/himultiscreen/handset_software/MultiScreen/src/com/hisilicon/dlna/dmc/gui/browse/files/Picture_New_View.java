package com.hisilicon.dlna.dmc.gui.browse.files;

import java.util.HashMap;
import java.util.List;

import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.item.ImageItem;
import org.teleal.cling.support.model.item.Item;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Rect;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AbsListView.OnScrollListener;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemLongClickListener;
import android.widget.AbsListView;
import android.widget.FrameLayout;
import android.widget.GridView;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.gui.activity.LiveTVActivity;
import com.hisilicon.dlna.dmc.gui.activity.PlayingImageActivity;
import com.hisilicon.dlna.dmc.gui.browse.files.FileData.LoadComplete;
import com.hisilicon.dlna.dmc.gui.customview.AdapterItem;
import com.hisilicon.dlna.dmc.processor.impl.PlaylistProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.multiscreen.mybox.DeviceDiscoveryActivity;
import com.hisilicon.multiscreen.mybox.R;
import com.hisilicon.multiscreen.widget.SlidePushView;

public class Picture_New_View{
	private View view;
	private GridView mGridView;
	private BrowseImageAdapter_New imageAdapter_new;
	private Context context;
	private FileData fileData;
	private FrameLayout rc_dms_picture_bottom_layout;
	private SlidePushView slidePushView;
	private FileLongClickCallBack mFileLongClickCallBack;
	private Handler progressHandler; //progressHandler.sendEmptyMessage(2);

	public Picture_New_View(Context context, SlidePushView slidePushView, FileLongClickCallBack mFileLongClickCallBack, Handler handler) {
		System.out.println("-------------Picture_New_View-------------");
		this.context = context;
		this.slidePushView = slidePushView;
		// TODO Auto-generated constructor stub
		view = View.inflate(context, R.layout.dlna_pictures_new_layout, null);
		this.mFileLongClickCallBack = mFileLongClickCallBack;
		progressHandler = handler;
		initView();
	}

	public void setFileLongClickCallBack(FileLongClickCallBack mFileLongClickCallBack){
		this.mFileLongClickCallBack = mFileLongClickCallBack;
	}

	public void setSlidePushView(SlidePushView slidePushView){
		this.slidePushView = slidePushView;
	}

	public View getView(){
		return view;
	}

	public BrowseImageAdapter_New getAdapter(){
		return imageAdapter_new;
	}

	private void initView(){
		mGridView = (GridView)view.findViewById(R.id.dms_image_gv);
		imageAdapter_new = new BrowseImageAdapter_New(context, mGridView);
		mGridView.setAdapter(imageAdapter_new);
		mGridView.setOnItemClickListener(new PicItemClickListener());
		mGridView.setOnItemLongClickListener(new PicItemLongClickListener());
		fileDataDo();
		mGridView.setOnScrollListener(new PicOnScrollListener());
		rc_dms_picture_bottom_layout = (FrameLayout) view.findViewById(R.id.rc_dms_picture_bottom_layout);
		rc_dms_picture_bottom_layout.setOnClickListener(new FoldersClickListener());
		rc_dms_picture_bottom_layout.setVisibility(View.GONE);
	}

	private void fileDataDo(){
		if(fileData==null)
			fileData = new FileData(context, imageAdapter_new, new FileDataLoad());
		fileData.getData();
	}

	private class FileDataLoad implements LoadComplete{

		@Override
		public void success() {
			// TODO Auto-generated method stub
			progressHandler.sendEmptyMessage(2);
		}

	}

	private class PicItemClickListener implements OnItemClickListener{

		@Override
		public void onItemClick(AdapterView<?> parent, View view, int position,
				long id) {
			view.setBackgroundResource(R.drawable.bg_dms_item_press);
			// TODO Auto-generated method stub
			if(fileData!=null){
				final Object object =imageAdapter_new.getItem(position);

				setAllItem(imageAdapter_new.getItemList());
				addToPlaylistAndPlay(object);

				Intent intent = new Intent(context, PlayingImageActivity.class);
				intent.putExtra("LONGCLICK", false);
				context.startActivity(intent);

			}
		}

		private void setAllItem(List list) {
			PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
			if (null == playlistProcessor) {
				playlistProcessor = new PlaylistProcessorImpl();
				UpnpProcessorImpl.getSington().setPlaylistProcessor(playlistProcessor);
			}
			playlistProcessor.setItems(list);

			//			PlaylistItem playlistItem = playlistProcessor.getItemAt(playlistProcessor.getSize() - 1);
			//			if (playlistItem.getTitle().equals(Utility.getString(R.string.load_more_result)))
			//				playlistProcessor.removeItem(playlistItem);
		}

		private void addToPlaylistAndPlay(Object object) {
			PlaylistItem added = null;
			if (object instanceof PlaylistItem) {
				added = (PlaylistItem) object;
			}

			PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
			if (null == playlistProcessor) {
				playlistProcessor = new PlaylistProcessorImpl();
				UpnpProcessorImpl.getSington().setPlaylistProcessor(playlistProcessor);
			}

			if (added == null && object instanceof ImageItem) {
				added = playlistProcessor.addDIDLObject((DIDLObject) object);
			}

			if (added != null) {
				playlistProcessor.setCurrentItem(added);

			} else {
				Toast.makeText(context, R.string.an_error_occurs_try_again_later, Toast.LENGTH_SHORT).show();
			}
		}

	}

	private class PicItemLongClickListener implements OnItemLongClickListener{

		@Override
		public boolean onItemLongClick(AdapterView<?> parent, View view,
				int position, long id) {
			// TODO Auto-generated method stub
			System.out.println("COme into pic item long click!");
			AdapterItem item = imageAdapter_new.getItem(position);
			mFileLongClickCallBack.update(true, item);
			Object object = item.getData();
			if (!(object instanceof Item))
				return true;
			Rect frame = new Rect();     
			((Activity) context).getWindow().getDecorView().getWindowVisibleDisplayFrame(frame);

			try {
				view.destroyDrawingCache();
				view.setDrawingCacheEnabled(true);
				Bitmap bitmap = Bitmap.createBitmap(view.getDrawingCache());

				int location[] = new int[2];
				view.getLocationInWindow(location);

				slidePushView.drawImageSlideView(bitmap, location, frame);

			} catch(Exception ex) {
			} catch(Error ex) {
				System.gc();
			}
			return false;
		}

	}

	private class PicOnScrollListener implements OnScrollListener{

		@Override
		public void onScrollStateChanged(AbsListView view, int scrollState) {
			switch (scrollState) { 
			case OnScrollListener.SCROLL_STATE_IDLE: //Idle态，进行实际数据的加载显示 
				imageAdapter_new.setState(false);
				imageAdapter_new.notifyDataSetChanged();
//				int first = view.getFirstVisiblePosition(); 
//				int count = view.getChildCount(); 
				break;   
			case OnScrollListener.SCROLL_STATE_TOUCH_SCROLL: 
				imageAdapter_new.setState(true);
				break; 
			case OnScrollListener.SCROLL_STATE_FLING: 
				imageAdapter_new.setState(true);
				break; 
			default: 
				break; 
			}
		}

		@Override
		public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) {
			if (rc_dms_picture_bottom_layout != null&&fileData.getFolders().size()>1)
				if (firstVisibleItem < 1) {
					rc_dms_picture_bottom_layout.setVisibility(View.VISIBLE);
				} else if (firstVisibleItem > 1) {
					rc_dms_picture_bottom_layout.setVisibility(View.GONE);
				}
			//			imageAdapter_new.notifyVisibleItemChanged(mGridView);
		}
	};

	private class FoldersClickListener implements OnClickListener{

		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			//			HashMap<String, List<FileNode>> folders = fileData.getFolders();
			Intent intent = new Intent(context, FoldersActivity.class);
			//			Bundle mBundle = new Bundle();  
			//			mBundle.putSerializable("FOLDERS",folders); 
			//			intent.putExtras(mBundle);
			context.startActivity(intent);
		}

	}

	public interface FileLongClickCallBack{
		public void update(boolean isLongClick, AdapterItem item);
	}

}
