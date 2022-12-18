package com.hisilicon.dlna.dmc.gui.browse.files;

import java.util.ArrayList;
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
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.AbsListView.OnScrollListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemLongClickListener;
import android.widget.AbsListView;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.gui.activity.PlayingImageActivity;
import com.hisilicon.dlna.dmc.gui.customview.AdapterItem;
import com.hisilicon.dlna.dmc.processor.impl.PlaylistProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem.Type;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.R;
import com.hisilicon.multiscreen.widget.SlidePushView;

public class FilesActivity extends Activity{
	private GridView mGridView;
	private String folderName;
	private List<ImageItem> imageItems = new ArrayList<ImageItem>();
	private List<PictureNode> paths = new ArrayList<PictureNode>();
	private BrowseImageAdapter_New adapter;
	private Context context;
	private AdapterItem item;
	private ImageView rc_slide_area;
	private SlidePushView slidePushView;
	private boolean isLongClick = false;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.dlna_dms_folder_files);
		context = this;
		folderName = getIntent().getStringExtra("FolderTitle");
		if(FileData.mGruopMap!=null){
			List<FileNode> nodes = FileData.mGruopMap.get(folderName);
			getImageItems(nodes);
		}
		initView();
	}

	private void initView(){
		TextView title = (TextView)findViewById(R.id.rc_dms_folder_title);
		rc_slide_area = (ImageView) findViewById(R.id.rc_slide_area);
		rc_slide_area.setOnTouchListener(new SlideAreaTouchListener());
		slidePushView = (SlidePushView) ((Activity) context).findViewById(R.id.slidePushView);
		title.setText(folderName);
		mGridView = (GridView)findViewById(R.id.dms_file_gv);
		adapter = new BrowseImageAdapter_New(this, mGridView);
		adapter.setList(paths);
		mGridView.setAdapter(adapter);
		mGridView.setOnItemClickListener(new FileItemClickListener());
		mGridView.setOnItemLongClickListener(new FileItemLongClickListener());
		mGridView.setOnScrollListener(new PicOnScrollListener());
		Thread thread = new CreatImageItemsThread();
		thread.start();

	}
	
	private void getImageItems(List<FileNode> nodes){
		if(nodes==null)
			return;
		for(FileNode node:nodes){
			imageItems.add(node.getImageItem());
			paths.add(node.getPictureNode());
		}
	}

	private class SlideAreaTouchListener implements OnTouchListener{
		private int MIN_DISTANCE = 100;
		private float downY, upY, moveY;

		@Override
		public boolean onTouch(View v, MotionEvent event) {
//			System.out.println("Slide touch listener!!");

			if (!isLongClick) {
				try {
					mGridView.dispatchTouchEvent(event);
				} catch (Exception ex){
				}
				if (event.getAction() == MotionEvent.ACTION_DOWN) {
					downY = event.getY();;
					moveY = event.getY();
				}
				return true;
			}

			switch (event.getAction()) {
			case MotionEvent.ACTION_DOWN: {
				downY = event.getY();;
				moveY = event.getY();
				break;
			}
			case MotionEvent.ACTION_MOVE: {
				final float preY = moveY;
				float nowY = event.getY();
				moveY = nowY;

				float deltaY = nowY - preY;
				this.onDeltaY((int) deltaY);
				break;
			}
			case MotionEvent.ACTION_UP:
				upY = event.getY();

				float deltaY = downY - upY;
				if (Math.abs(deltaY) > MIN_DISTANCE)
				{
					if (deltaY < 0)
					{
						this.onUpToDownSlide();
					}
					else if (deltaY > 0)
					{
						this.onDownToUpSlide();
					}
				}
				else
				{
					this.onTap();
				}
				break;
			}

			return true;
		}

		private void onDeltaY(int deltaY) {
			int left = slidePushView.getLeft();
			int right = slidePushView.getRight();
			int top = slidePushView.getTop();
			int bottom = slidePushView.getBottom();

			slidePushView.layout(left , top + deltaY, right , bottom + deltaY);
		}

		private void onDownToUpSlide() {
			updatePlaylistAndPlay(item, true);
			slidePushView.touchClearShow();
			isLongClick = false;
		}

		private void onUpToDownSlide() {
			slidePushView.touchClearShow();
			isLongClick = false;
		}

		private void onTap() {
			isLongClick = false;
			slidePushView.touchClearShow();
		} 
	}
	
	
	private class FileItemClickListener implements OnItemClickListener{

		@Override
		public void onItemClick(AdapterView<?> parent, View view, int position,
				long id) {
			view.setBackgroundResource(R.drawable.bg_dms_item_press);
			// TODO Auto-generated method stub
			final Object object =adapter.getItem(position);

			setAllItem(adapter.getItemList());
			addToPlaylistAndPlay(object);

			Intent intent = new Intent(context, PlayingImageActivity.class);
			intent.putExtra("LONGCLICK", false);
			context.startActivity(intent);
		}

	}

	private class FileItemLongClickListener implements OnItemLongClickListener{

		@Override
		public boolean onItemLongClick(AdapterView<?> parent, View view,
				int position, long id) {
			// TODO Auto-generated method stub
			isLongClick = true;
			item = adapter.getItem(position);
			if(item==null)
				return true;
			Object object = item.getData();
			if (!(object instanceof Item))
				return true;
			Rect frame = new Rect();     
			((Activity) context).getWindow().getDecorView().getWindowVisibleDisplayFrame(frame);
			try{
				view.destroyDrawingCache();
				view.setDrawingCacheEnabled(true);
				Bitmap bitmap = Bitmap.createBitmap(view.getDrawingCache());

				int location[] = new int[2];
				view.getLocationInWindow(location);
				slidePushView.drawImageSlideView(bitmap, location, frame);
			}catch(Exception e){
				
			}catch(Error ex) {
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
				adapter.setState(false);
				adapter.notifyDataSetChanged();
//				int first = view.getFirstVisiblePosition(); 
//				int count = view.getChildCount(); 
				break;   
			case OnScrollListener.SCROLL_STATE_TOUCH_SCROLL: 
				adapter.setState(true);
				break; 
			case OnScrollListener.SCROLL_STATE_FLING: 
				adapter.setState(true);
				break; 
			default: 
				break; 
			}
		}

		@Override
		public void onScroll(AbsListView view, int firstVisibleItem,
				int visibleItemCount, int totalItemCount) {
			// TODO Auto-generated method stub
			
		}
	}
	
	private void setAllItem(List list) {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (null == playlistProcessor) {
			playlistProcessor = new PlaylistProcessorImpl();
			UpnpProcessorImpl.getSington().setPlaylistProcessor(playlistProcessor);
		}
		playlistProcessor.setItems(list);

	}

	private void updatePlaylistAndPlay(AdapterItem item, boolean isLongClick) {
		Object object = item.getData();
		setAllItem(adapter.getItemList());
		addToPlaylistAndPlay(item);
		Intent intent = new Intent(context, PlayingImageActivity.class);
		intent.putExtra("LONGCLICK", isLongClick);
		context.startActivity(intent);
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


	private class CreatImageItemsThread extends Thread{

		@Override
		public void run() {
			// TODO Auto-generated method stub
			super.run();
			for(ImageItem item:imageItems){
				adapter.add(createFromDLDIObject(item));
			}
		}

	}

	private PlaylistItem createFromDLDIObject(DIDLObject object) {
		PlaylistItem item = new PlaylistItem(object);

		item.setId(object.getId());
		item.setTitle(object.getTitle());

		String url = HttpServerUtil.getUrlFrom(object);
		item.setUrl(url);

		boolean isLocal = HttpServerUtil.mediaFromLocal(url);
		if (isLocal) {
			item.setType(Type.IMAGE_LOCAL);
		} else
			item.setType(Type.IMAGE_REMOTE);

		item.setMetaData(Utility.createMetaData(object));

		return item;
	}

	public void onBackClick(View view) {
		finish();
	}

}
