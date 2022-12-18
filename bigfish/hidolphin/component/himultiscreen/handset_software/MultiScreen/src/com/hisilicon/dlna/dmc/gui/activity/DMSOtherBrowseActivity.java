package com.hisilicon.dlna.dmc.gui.activity;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.LocalDevice;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.AudioItem;
import org.teleal.cling.support.model.item.ImageItem;
import org.teleal.cling.support.model.item.Item;
import org.teleal.cling.support.model.item.MusicTrack;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Rect;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.AbsListView;
import android.widget.AbsListView.OnScrollListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemLongClickListener;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.gui.customview.AdapterItem;
import com.hisilicon.dlna.dmc.gui.customview.BrowseImageAdapter;
import com.hisilicon.dlna.dmc.gui.customview.BrowseMusicAdapter;
import com.hisilicon.dlna.dmc.gui.customview.BrowseVideoAdapter;
import com.hisilicon.dlna.dmc.gui.customview.MediaType;
import com.hisilicon.dlna.dmc.processor.impl.DMSProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.LocalDMSProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.PlaylistProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMSProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMSProcessor.DMSProcessorListner;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.ChangeMode;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.PlaylistListener;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentTree;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.multiscreen.mybox.R;
import com.hisilicon.multiscreen.widget.SlidePushView;

public class DMSOtherBrowseActivity extends Activity {
	public static final String LONGCLICK = "LONGCLICK";
	
	private Activity activity;
	private AbsListViewAdapter<PlaylistItem> m_adapter;
	private ArrayList<String> m_traceID;
	private HashMap<String, String> titleMap;
	private MediaType mediaType;
	private TextView rc_dms_header_title;
	private GridView m_gridView;
	private SlidePushView slidePushView;
	private ImageView rc_slide_area;
	private String id = "";
	private boolean m_loadMore = false;
	private volatile boolean isStop = false;
	private volatile boolean isLongClick = false;
	private PlaylistItem item;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		activity = this;
		ThumbnailGenerator.getInstance().restore();
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_dmsbrowseother);

		Intent intent = getIntent();
		Bundle bundle = intent.getExtras();
		mediaType = (MediaType) bundle.getSerializable("mediaType");
		ArrayList<String> temp_traceID = bundle.getStringArrayList("traceID");

		m_traceID = new ArrayList<String>();
		m_traceID.add("-1");
		titleMap = new HashMap<String, String>();
		
		m_adapter = newAdapter(activity, mediaType);

		rc_dms_header_title = (TextView) findViewById(R.id.rc_dms_header_title);
		m_gridView = (GridView) findViewById(R.id.dms_other_browsing);
		m_gridView.setAdapter(m_adapter);
		m_gridView.setOnItemClickListener(m_itemClick);
		m_gridView.setOnItemLongClickListener(itemLongClickListener);
		m_gridView.setOnScrollListener(browseScrollListener);
		slidePushView = (SlidePushView) findViewById(R.id.slidePushView);
		
		init();
		
		progressShow();

		Device device = UpnpProcessorImpl.getSington().getCurrentDMS();
		if (device != null && device instanceof LocalDevice) {
			if (MediaType.IMAGE == mediaType) {
				id = ContentTree.IMAGE_FOLDER_ID;
			} else if (MediaType.VIDEO == mediaType) {
				id = ContentTree.VIDEO_FOLDER_ID;
			} else if (MediaType.MUSIC == mediaType) {
				id = ContentTree.AUDIO_FOLDER_ID;
			}
			mediaBrowse(id, 0);
		} else {
			if (temp_traceID.size() > 1) {
				id = temp_traceID.get(1);
				mediaBrowse(id, 0);
			}
		}
		
		if (MediaType.IMAGE == mediaType) {
			titleMap.put(id, getString(R.string.dms_picture_other));
		} else if (MediaType.VIDEO == mediaType) {
			titleMap.put(id, getString(R.string.dms_video_other));
		} else if (MediaType.MUSIC == mediaType) {
			titleMap.put(id, getString(R.string.dms_music_playlist));
		}
		
		rc_dms_header_title.setText(titleMap.get(id));
	}
	
	private OnScrollListener browseScrollListener = new OnScrollListener() {

		@Override
		public void onScrollStateChanged(AbsListView view, int scrollState) {
			switch (scrollState) {
			case AbsListView.OnScrollListener.SCROLL_STATE_FLING:
			case AbsListView.OnScrollListener.SCROLL_STATE_TOUCH_SCROLL:
				ThumbnailGenerator.getInstance().lock();
				break;
			case AbsListView.OnScrollListener.SCROLL_STATE_IDLE:
				loadImage();
				break;
			default:
				break;
			}
		}
		
		@Override
		public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) {
			try {
				if (hasMoreItems(firstVisibleItem, visibleItemCount, totalItemCount) && lastImageItemIsMark(firstVisibleItem, visibleItemCount)) {
					doLoadMoreItems();
				}
			} catch (Exception ex) {

			}
		}
	};
	
	public void loadImage() {
		int start = m_gridView.getFirstVisiblePosition();
		int end = m_gridView.getLastVisiblePosition();
		if(end >= m_adapter.getCount()) {
			end = m_adapter.getCount() -1;
		}
		ThumbnailGenerator.getInstance().setLoadLimit(start, end + 3);
		ThumbnailGenerator.getInstance().unlock();
	}
	
	private void doLoadMoreItems() {
		progressShow();
		
		browseMore(m_traceID.get(m_traceID.size() - 1), m_adapter.getCount(), browseListener);
	}
	
	private void mediaBrowse(String id, int startIndex) {
		m_traceID.add(id);
		browse(id, startIndex, AppPreference.getMaxItemPerLoad(), browseListener);
	}
	
	private void browse(String id, int startIndex, int maxResult, DMSProcessorListner m_browseListener) {
		DMSProcessor dmsProcessor = UpnpProcessorImpl.getSington().getDMSProcessor();
		if (dmsProcessor != null) {
			m_loadMore = false;
			dmsProcessor.browse(id, startIndex, maxResult, m_browseListener);
		}
	}
	
	private void browseMore(String id, int startIndex, DMSProcessorListner m_browseListener) {
		DMSProcessor dmsProcessor = UpnpProcessorImpl.getSington().getDMSProcessor();
		if (dmsProcessor != null) {
			m_loadMore = true;
			dmsProcessor.browse(id, startIndex, AppPreference.getMaxItemPerLoad(), m_browseListener);
		}
	}
	
	private boolean hasMoreItems(int firstVisibleItem, int visibleItemCount, int totalItemCount) {
		return UpnpProcessorImpl.getSington().getDMSProcessor() != null
				&& !progressIsShow()
				&& firstVisibleItem + visibleItemCount == totalItemCount;
	}

	private boolean lastImageItemIsMark(int firstVisibleItem, int visibleItemCount) {
		Object object = m_adapter.getItem(firstVisibleItem + visibleItemCount - 1).getData();
		return object instanceof DIDLObject && ((DIDLObject) object).getId().equals("-1");
	}
	
	private void init() {
		rc_slide_area = (ImageView) findViewById(R.id.rc_slide_area);
		rc_slide_area.setOnTouchListener(new OnTouchListener() {
			private int MIN_DISTANCE = 100;
			private float downY, upY, moveY;
			
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				
				if (!isLongClick) {
					try {
						m_gridView.dispatchTouchEvent(event);
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
		});
	}
	
	private AbsListViewAdapter<PlaylistItem> newAdapter(Activity activity, MediaType mediaType) {
		if (MediaType.IMAGE == mediaType) {
			return new BrowseImageAdapter(activity);
		} else if (MediaType.MUSIC == mediaType) {
			return new BrowseMusicAdapter(activity);
		} else {
			return new BrowseVideoAdapter(activity);
		} 
	}
	
	private void progressDismiss() {
		runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				findViewById(R.id.progress_layout).setVisibility(View.GONE);
			}
		});
		
	}

	private void progressShow() {
		runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				findViewById(R.id.progress_layout).setVisibility(View.VISIBLE);
			}
		});
	}

	private boolean progressIsShow() {
		return findViewById(R.id.progress_layout).isShown();
	}
	
	private DMSProcessorListner browseListener = new DMSProcessorListner() {

		@Override
		public void onBrowseFail(String message) {
			browseFailure(message);
		}

		private void browseFailure(String message) {
			m_traceID.remove(m_traceID.size() - 1);
			progressDismiss();
		}

		@Override
		public void onBrowseComplete(String objectID, boolean haveNext, Map<String, List<? extends DIDLObject>> result) {
			browseSuccess(objectID, haveNext, result);
		}

		private void browseSuccess(final String objectID, final boolean haveNext, final Map<String, List<? extends DIDLObject>> result) {
			activity.runOnUiThread(new Runnable() {

				@Override
				public void run() {
					if (m_loadMore) {
						m_adapter.remove(m_adapter.getItem(m_adapter.getCount() - 1));
						m_adapter.notifyDataSetChanged();
					} else {
						setNewAdapter();
					}

					for (DIDLObject container : result.get("Containers")) {
						String title = container.getTitle();
						
						if(m_traceID.size() == 2 && HttpServerUtil.isCamera(title)) {
							if (UpnpProcessorImpl.getSington().getDMSProcessor() instanceof LocalDMSProcessorImpl)
								continue;
						}
						
						if (m_traceID.size() == 2 && HttpServerUtil.isAllImages(title) || HttpServerUtil.isAllVideos(title) || HttpServerUtil.isAllMusics(title)) {
							if (UpnpProcessorImpl.getSington().getDMSProcessor() instanceof DMSProcessorImpl)
								continue;
						}
								
						m_adapter.add(PlaylistItem.createFromDLDIObject(container));
					}

					for (DIDLObject item : result.get("Items")) {
						if (item instanceof ImageItem) {
							m_gridView.setNumColumns(4);
						}
						m_adapter.add(PlaylistItem.createFromDLDIObject(item));
					}

					if (haveNext) {
						Item item = new Item();
						item.setTitle(getString(R.string.load_more_result));
						item.setId("-1");
						m_adapter.add(PlaylistItem.createFromDLDIObject(item));
					}

					progressDismiss();

					m_adapter.notifyVisibleItemChanged(m_gridView);
				}
			});
		}
	};
	
	private void setNewAdapter() {
		m_adapter.clear();
		m_gridView.setNumColumns(1);
		m_gridView.setAdapter(m_adapter);
	}
	
	private OnItemClickListener m_itemClick = new OnItemClickListener() {

		@SuppressWarnings("rawtypes")
		@Override
		public void onItemClick(AdapterView<?> adapter, View view, int position, long arg3) {
			view.setBackgroundResource(R.drawable.bg_dms_item_press);
			PlaylistItem item = m_adapter.getItem(position);
			final Object object = item.getData();
			if (object instanceof Container) {
				id = ((Container) object).getId();
				String title = ((Container) object).getTitle();
				
				titleMap.put(id, title);
				
				rc_dms_header_title.setText(title);
				
				progressShow();
				
				mediaBrowse(((Container) object).getId(), 0);
			} else if (object instanceof Item) {
				updatePlaylistAndPlay(item, false);
			}
			
		}
	};
	
	private OnItemLongClickListener itemLongClickListener = new OnItemLongClickListener() {

		@Override
		public boolean onItemLongClick(AdapterView<?> parent, View view, final int position, long id) {
			isLongClick = true;
			
			item = m_adapter.getItem(position);
			
			Object object = item.getData();
			if (!(object instanceof Item))
				return true;
			Rect frame = new Rect();     
           activity.getWindow().getDecorView().getWindowVisibleDisplayFrame(frame);
            
            try {
            	view.destroyDrawingCache();
            	view.setDrawingCacheEnabled(true);
            	Bitmap bitmap = Bitmap.createBitmap(view.getDrawingCache());

            	int location[] = new int[2];
            	view.getLocationInWindow(location);

            	if (MediaType.IMAGE == mediaType) {
            		slidePushView.drawImageSlideView(bitmap, location, frame);
    			} else if (MediaType.VIDEO == mediaType) {
    				slidePushView.drawVideoSlideView(bitmap, location, frame);
    			} else if (MediaType.MUSIC == mediaType) {
    				slidePushView.drawMusicSlideView(bitmap, location, frame);
    			}
            	
            } catch(Exception ex) {
            } catch(Error ex) {
            	System.gc();
            }
            
			return false;
		}
	};
	
	private void updatePlaylistAndPlay(AdapterItem item, boolean isLongClick) {
		Object object = item.getData();
		
		setAllItem(m_adapter.getItemList());
		addToPlaylistAndPlay(item);
		
		if (object instanceof ImageItem) {
			Intent intent = new Intent(activity, PlayingImageActivity.class);
			intent.putExtra(LONGCLICK, isLongClick);
			activity.startActivity(intent);
		} else if (object instanceof AudioItem || object instanceof MusicTrack) {
			Intent intent = new Intent(activity, PlayingMusicActivity.class);
			intent.putExtra(LONGCLICK, isLongClick);
			activity.startActivity(intent);
		} else {
			Intent intent = new Intent(activity, PlayingVideoActivity.class);
			intent.putExtra(LONGCLICK, isLongClick);
			activity.startActivity(intent);
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

	private void addToPlaylistAndPlay(AdapterItem object) {
		PlaylistItem added = null;
		if (object instanceof PlaylistItem) {
			added = (PlaylistItem) object;
		}
		
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (null == playlistProcessor) {
			playlistProcessor = new PlaylistProcessorImpl();
			UpnpProcessorImpl.getSington().setPlaylistProcessor(playlistProcessor);
		}
		
		if (added == null && object.getData() instanceof DIDLObject) {
			added = playlistProcessor.addDIDLObject((DIDLObject) object.getData());
		}
		
		if (added != null) {
			playlistProcessor.setCurrentItem(added);
			
			if (added.getData() instanceof AudioItem)
				m_adapter.notifyVisibleItemChanged(m_gridView);
		} else {
			Toast.makeText(activity, R.string.an_error_occurs_try_again_later, Toast.LENGTH_SHORT).show();
		}
	}
	
	@Override
	public void onResume() {
		super.onResume();
		isStop = false;
		loadImage();
		m_adapter.notifyVisibleItemChanged(m_gridView);
		UpnpProcessorImpl.getSington().addPlaylistListener(m_playlistListener);
	}

	@Override
	public void onPause() {
		super.onPause();
		isStop = true;
		UpnpProcessorImpl.getSington().removePlaylistListener(m_playlistListener);
	}
	
	protected PlaylistListener m_playlistListener = new PlaylistListener() {

		@Override
		public void onItemChanged(PlaylistItem item, ChangeMode changeMode) {
			playlistItemChanged(item, changeMode);
		}
	};

	protected void playlistItemChanged(final PlaylistItem item, final ChangeMode changeMode) {
		if (isStop)
			return;

		final DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
		if (dmrProcessor == null)
			return;

		if (item == null) {
			dmrProcessor.stop();
			return;
		}

		if (item.getData() instanceof AudioItem || item.getData() instanceof MusicTrack) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					if (ChangeMode.UNKNOW != changeMode)
						dmrProcessor.setURIandPlay(item);
					m_adapter.notifyDataSetChanged();
				}
			});
		}
	}
	
	@Override
	public void onBackPressed() {
		dmsBrowseBack();
	}

	public void onBackClick(View view) {
		dmsBrowseBack();
	}
	
	private void dmsBrowseBack() {
		boolean isConsume = upOneLevel();
		if (!isConsume)
			finish();
	}
	
	private boolean upOneLevel() {
		progressShow();

		if (UpnpProcessorImpl.getSington().getDMSProcessor() != null && m_traceID.size() > 2) {
			final String parentID = m_traceID.get(m_traceID.size() - 2);
			
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					rc_dms_header_title.setText(titleMap.get(parentID));
				}
			});
			
			UpnpProcessorImpl.getSington().getDMSProcessor().back(m_traceID, AppPreference.getMaxItemPerLoad(), browseListener);

			return true;
		}
		return false;
	}
}
