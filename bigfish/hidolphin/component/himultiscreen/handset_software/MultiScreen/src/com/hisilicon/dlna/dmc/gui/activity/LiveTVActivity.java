package com.hisilicon.dlna.dmc.gui.activity;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.types.UDN;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.Item;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationUtils;
import android.widget.AbsListView;
import android.widget.AbsListView.OnScrollListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.GridView;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.gui.customview.AdapterItem;
import com.hisilicon.dlna.dmc.gui.customview.BrowseState;
import com.hisilicon.dlna.dmc.processor.impl.PlaylistProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMSProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMSProcessor.DMSProcessorListner;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.UpnpProcessor.DevicesListener;
import com.hisilicon.dlna.dmc.processor.interfaces.UpnpProcessor.SystemListener;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem.ViewMode;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.MyApp;
import com.hisilicon.multiscreen.mybox.R;

public class LiveTVActivity extends Activity {
	private static final String LIVETV = "LIVETV";
	
	/**
	 * 存放LiveTV root目录的ID
	 */
	private HashMap<String, String> rootFloor = new HashMap<String, String>();
	/**
	 * 存放LiveTV root目录的Container，key为ID，对应rootFloor里的ID，value为Container
	 */
	private HashMap<String, DIDLObject> firstFloor = new HashMap<String, DIDLObject>();
	
	private ArrayList<String> m_traceID;

	private BrowseState liveTVBrowseState = BrowseState.UNKOWN;
	
	private Activity activity;
	
	private LiveTVAdapter m_adapter;
	private GridView m_gridView;
	private View livetv_not_found_layout;
	private TextView livetv_not_found;
	private boolean m_loadMore = false;
	
	private Handler myHandler = new Handler();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		activity = this;
		MyApp.setSTBIP(getIntent().getStringExtra("STBIP"));
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_livetv);
		
		m_traceID = new ArrayList<String>();
		m_traceID.add("-1"); 

		m_adapter = new LiveTVAdapter(activity);
		livetv_not_found_layout = findViewById(R.id.livetv_not_found_layout);
		livetv_not_found = (TextView) findViewById(R.id.livetv_not_found);
		m_gridView = (GridView) findViewById(R.id.dms_livetv_browsing);
		m_gridView.setAdapter(m_adapter);
		m_gridView.setOnItemClickListener(m_itemClick);
		m_gridView.setOnScrollListener(browseScrollListener);
		
		if (MyApp.getSTBIP().equals("STBIP")) {
			myHandler.removeCallbacks(hideRunnable);
			livetv_not_found.setText(R.string.remote_device_not_found);
			showWarnLayout();
			myHandler.postDelayed(hideRunnable, 1000);
			return;
		}

		myHandler.postDelayed(runnable, 100);
	}
	
	public void showWarnLayout() {
		if (livetv_not_found_layout == null)
			return;
		Animation animation = AnimationUtils.loadAnimation(activity, R.anim.up_slidein);
		animation.setAnimationListener(new AnimationListener() {

			@Override
			public void onAnimationStart(Animation animation) {
			}

			@Override
			public void onAnimationRepeat(Animation animation) {
			}

			@Override
			public void onAnimationEnd(Animation animation) {
				livetv_not_found_layout.clearAnimation();
				livetv_not_found_layout.setVisibility(View.VISIBLE);
			}
		});
		livetv_not_found_layout.startAnimation(animation);

	}
	
	private Runnable hideRunnable = new Runnable() {

		@Override
		public void run() {
			hideWarnLayout();
		}

	};

	public void hideWarnLayout() {
		if (livetv_not_found_layout == null)
			return;
		Animation animation = AnimationUtils.loadAnimation(activity, R.anim.up_slideout);
		animation.setAnimationListener(new AnimationListener() {

			@Override
			public void onAnimationStart(Animation animation) {
			}

			@Override
			public void onAnimationRepeat(Animation animation) {
			}

			@Override
			public void onAnimationEnd(Animation animation) {
				livetv_not_found_layout.clearAnimation();
				livetv_not_found_layout.setVisibility(View.GONE);
			}
		});
		livetv_not_found_layout.startAnimation(animation);
	}
	
	private Runnable runnable = new Runnable() {

		@Override
		public void run() {
			if(!Utility.isNetWork(LiveTVActivity.this))
				Toast.makeText(LiveTVActivity.this, R.string.toast_KeepAlive_packet_loss, Toast.LENGTH_LONG).show();
			else{
				progressShow();
				UpnpProcessorImpl.getSington().addDevicesListener(upnpListener);
				UpnpProcessorImpl.getSington().addSystemListener(systemListener);
				UpnpProcessorImpl.getSington().bindUpnpService();
			}
		}
	};
	
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

	private Runnable canConnectDevice = new Runnable() {

		@Override
		public void run() {
			progressDismiss();
			myHandler.removeCallbacks(hideRunnable);
			showWarnLayout();
			myHandler.postDelayed(hideRunnable, 1000);
		}
	};
	
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
		
		public void loadImage() {
			int start = m_gridView.getFirstVisiblePosition();
			int end = m_gridView.getLastVisiblePosition();
			if(end >= m_adapter.getCount()) {
				end = m_adapter.getCount() -1;
			}
			ThumbnailGenerator.getInstance().setLoadLimit(start, end + 3);
			ThumbnailGenerator.getInstance().unlock();
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
	
	private void doLoadMoreItems() {
		progressShow();
		
		browseMore(m_traceID.get(m_traceID.size() - 1), m_adapter.getCount(), liveTVBrowseListener);
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

	@Override
	protected void onDestroy() {
		super.onDestroy();
		UpnpProcessorImpl.getSington().removeSystemListener(systemListener);
		UpnpProcessorImpl.getSington().removeDevicesListener(upnpListener);
		UpnpProcessorImpl.getSington().unbindUpnpService();
	}
	
	private SystemListener systemListener = new SystemListener() {

		@Override
		public void onStartFailed() {
		}

		@Override
		public void onStartComplete() {
//			Toast.makeText(activity, R.string.start_connect_onlivetv, Toast.LENGTH_SHORT).show();

			updateDMSDevice();

			myHandler.postDelayed(canConnectDevice, 15000);
		}

		@Override
		public void onRouterError(String cause) {

		}

		@Override
		public void onRouterEnabledEvent() {

		}

		@Override
		public void onRouterDisabledEvent() {

		}

		@Override
		public void onNetworkChanged() {
			new Thread(new Runnable() {

				@Override
				public void run() {
					UpnpProcessorImpl.getSington().refreshDevicesList();
				}
			}).start();
		}
	};
	
	public void updateDMSDevice() {
		
		for (Device device : UpnpProcessorImpl.getSington().getDMSList()) {
			addAdapterDMS(device);
		}
	}
	
	private void deviceBrowse(Device device) {
		progressShow();
		
		deviceBrowseClear();

		deviceBrowseStart(device);
	}
	
	private void deviceBrowseClear() {
		
		rootFloor.clear();
		firstFloor.clear();

		m_adapter.clear();
	}

	private void deviceBrowseStart(Device device) {
		DMSProcessor dmsProcessor = UpnpProcessorImpl.getSington().getDMSProcessor();
		if (dmsProcessor != null) {
			m_loadMore = false;
			dmsProcessor.browse("0", 0, AppPreference.getMaxItemPerLoad(), deviceBrowseListener);
		} else {
			progressDismiss();
		}
	}
	
	private DMSProcessorListner deviceBrowseListener = new DMSProcessorListner() {

		@Override
		public void onBrowseFail(String message) {
			deviceBrowseFailure(message);
		}

		@Override
		public void onBrowseComplete(String objectID, boolean haveNext, Map<String, List<? extends DIDLObject>> result) {
			deviceBrowseSuccess(result);

		}

		private void deviceBrowseFailure(String message) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					progressDismiss();
				}

			});
		}

		/**
		 * 
		 * 将获取的媒体筛选出直播LiveTV，将他们的ID放入rootFloor，ID对应的Container放入firstFloor
		 */
		private void deviceBrowseSuccess(final Map<String, List<? extends DIDLObject>> result) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					List<? extends DIDLObject> containers = result.get("Containers");

					for (DIDLObject didlObject : containers)
					{
						String id = didlObject.getId();
						String title = didlObject.getTitle();

						if (HttpServerUtil.isLiveTV(title))
						{
							rootFloor.put(LIVETV, id);
							firstFloor.put(id, didlObject);
							break;
						}
					}

					rootFloorBrowse();
				}
			});
		}

		/**
		 * 浏览root目录LiveTV的下一级内容
		 */
		private void rootFloorBrowse() {
			rootLiveTVBrowse();

			new Thread(new Runnable() {

				@Override
				public void run() {
					rootLiveTVBrowseWaiting();

					if (BrowseState.FAILURE == liveTVBrowseState) {
						rootLiveTVBrowse();
						rootLiveTVBrowseWaiting();
					}

					if (BrowseState.FAILURE == liveTVBrowseState) {
						activity.runOnUiThread(new Runnable() {
							
							@Override
							public void run() {
								Toast.makeText(activity, R.string.dms_no_findcontent, Toast.LENGTH_SHORT).show();
								
							}
						});
					}
				}

			}).start();

		}

		private void rootLiveTVBrowse() {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					String id = rootFloor.get(LIVETV);
					if (id != null) {
						liveTVBrowseState = BrowseState.UNKOWN;
						
						liveTVBrowse(id, 0);
					} else {
						liveTVBrowseState = BrowseState.VOID;
						progressDismiss();
					}
				}
			});
		}

		private void rootLiveTVBrowseWaiting() {
			while(BrowseState.UNKOWN == liveTVBrowseState) {
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}

	};
	
	/**
	 * 直播浏览回调
	 */
	private DMSProcessorListner liveTVBrowseListener = new DMSProcessorListner() {

		@Override
		public void onBrowseFail(String message) {
			liveTVBrowseState = BrowseState.FAILURE;

			liveTVBrowseFailure(message);
		}

		private void liveTVBrowseFailure(String message) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					progressDismiss();
				}
			});
		}

		@Override
		public void onBrowseComplete(String objectID, boolean haveNext, Map<String, List<? extends DIDLObject>> result) {
			liveTVBrowseState = BrowseState.SUCCESS;

			liveTVBrowseSuccess(objectID, haveNext, result);
		}

		private void liveTVBrowseSuccess(final String objectID, final boolean haveNext, final Map<String, List<? extends DIDLObject>> result) {
			runOnUiThread(new Runnable() {

				@Override
				public void run() {
					if (m_loadMore) {
						m_adapter.remove(m_adapter.getItem(m_adapter.getCount() - 1));
						m_adapter.notifyDataSetChanged();
					} else {
						setNewAdapter();
					}

					List<? extends DIDLObject> containers = result.get("Containers");
					List<? extends DIDLObject> items = result.get("Items");

					for (DIDLObject container : containers)
					{
						m_adapter.add(PlaylistItem.createFromDLDIObject(container));
					}

					List<PlaylistItem> playlistItems = new ArrayList<PlaylistItem>();
					for (DIDLObject item : items)
					{
						PlaylistItem playlistItem = PlaylistItem.createFromDLDIObject(item);
						playlistItems.add(playlistItem);
						m_adapter.add(playlistItem);
					}

					if (!m_loadMore) {
						setAllItem(playlistItems);
						PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
						List<PlaylistItem> list = playlistProcessor.getItemsByViewMode(ViewMode.VIDEO_ONLY);
						if (!list.isEmpty()) {
							PlaylistItem playlistItem = list.get(0);
							toPlay(playlistItem.getUrl());
						}
					}

					progressDismiss();

					if (haveNext) {
						Item item = new Item();
						item.setTitle(activity.getString(R.string.load_more_result));
						item.setId("-1");
						m_adapter.add(PlaylistItem.createFromDLDIObject(item));
					}

					m_adapter.notifyVisibleItemChanged(m_gridView);
				}
			});
		}
	};
	
	private void setAllItem(List list) {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (null == playlistProcessor) {
			playlistProcessor = new PlaylistProcessorImpl();
			UpnpProcessorImpl.getSington().setPlaylistProcessor(playlistProcessor);
		}
		playlistProcessor.setItems(list);
		
		if (playlistProcessor.getSize() > 0) {
			PlaylistItem playlistItem = playlistProcessor.getItemAt(playlistProcessor.getSize() - 1);
			if (playlistItem.equals(Utility.getString(R.string.load_more_result)))
				playlistProcessor.removeItem(playlistItem);
		}
		
	}
	
	private void toPlay(String uriString) {
		ComponentName component = new ComponentName("me.abitno.vplayer.t", "me.abitno.vplayer.VideoActivity");
		
		Intent intent = new Intent();
		intent.setComponent(component);
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_WHEN_TASK_RESET);
		intent.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
		intent.setDataAndType(Uri.parse(uriString), "video/*");
		try {
			startActivity(intent);
		} catch (Exception e) {
			Toast.makeText(activity, R.string.please_install_vplayer, Toast.LENGTH_SHORT).show();
		}
	}
	
	private DevicesListener upnpListener = new DevicesListener() {

		@SuppressWarnings("rawtypes")
		@Override
		public void onDeviceAdded(Device device) {
			if (device.getType().getNamespace().equals("schemas-upnp-org")) {
				if (device.getType().getType().equals("MediaServer")) {
					addDMS(device);
				}
			}
		}

		@SuppressWarnings("rawtypes")
		@Override
		public void onDeviceRemoved(Device device) {
			if (device.getType().getNamespace().equals("schemas-upnp-org")) {
				if (device.getType().getType().equals("MediaServer")) {
					removeDMS(device);
				}
			}
		}

		@Override
		public void onDMSChanged() {
		}

		@Override
		public void onDMRChanged() {
		}

		@Override
		public
		void onDeviceUpdate(Device device) {
			// TODO Auto-generated method stub
			
		}
	};
	
	@SuppressWarnings("rawtypes")
	private void addDMS(final Device device) {
		runOnUiThread(new Runnable() {

			@Override
			public void run() {
				synchronized (m_adapter) {
					addAdapterDMS(device);
				}
			}

		});
	}

	@SuppressWarnings("rawtypes")
	private void addAdapterDMS(final Device device) {

		if (HttpServerUtil.isSTBMultiRoom(device)) {
			myHandler.removeCallbacks(canConnectDevice);

			UDN udn = device.getIdentity().getUdn();
			UpnpProcessorImpl.getSington().setLiveTV(udn);

			DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington().getDMRProcessor();
			if (dmrProcessor != null) {
				dmrProcessor.setRunning(false);
			}

			Toast.makeText(activity, R.string.start_search_livetv_channel, Toast.LENGTH_SHORT).show();
			
			deviceBrowse(device);

		}

	}

	@SuppressWarnings("rawtypes")
	private void removeDMS(final Device device) {
		runOnUiThread(new Runnable() {

			@Override
			public void run() {
				synchronized (m_adapter) {
					m_adapter.remove(new AdapterItem(device));
				}
			}
		});
	}
	
	private OnItemClickListener m_itemClick = new OnItemClickListener() {

		@SuppressWarnings("rawtypes")
		@Override
		public void onItemClick(AdapterView<?> adapter, View view, int position, long arg3) {
			AdapterItem item = m_adapter.getItem(position);
			if (item.getData() instanceof Device) {
				UDN udn = ((Device) item.getData()).getIdentity().getUdn();
				UpnpProcessorImpl.getSington().setCurrentDMS(udn);
				
				deviceBrowse((Device) item.getData());
				
			} else {
				final DIDLObject object = (DIDLObject) item.getData();
				if (object instanceof Container) {
					liveTVBrowse(object.getId(), 0);
				} else if (object instanceof Item) {
					if (object.getId().equals("-1")) {
						browseMore(object.getId(), m_adapter.getCount(), liveTVBrowseListener);
					} else {
						setAllItem(m_adapter.getItemList());
						String url = HttpServerUtil.getUrlFrom(object);
						toPlay(url);
					}
				}
			}
		}

	};
	
	private void setNewAdapter() {
		m_adapter.clear();
		m_gridView.setAdapter(m_adapter);
	}
	
	private void liveTVBrowse(String id, int startIndex) {
		m_traceID.add(id);
		browse(id, startIndex, AppPreference.getMaxItemPerLoad(), liveTVBrowseListener);
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
	
	public void onBackClick(View view) {
		onBack();
	}
	
	@Override
	public void onBackPressed() {
		if (!upOneLevel()) {
			super.onBackPressed();
		}
	}
	
	private void onBack() {
		boolean isConsume = upOneLevel();
		if (!isConsume)
			finish();
	}
	
	private boolean upOneLevel() {
		progressShow();
		if (UpnpProcessorImpl.getSington().getDMSProcessor() != null && m_traceID.size() > 2) {
			UpnpProcessorImpl.getSington().getDMSProcessor().back(m_traceID, AppPreference.getMaxItemPerLoad(), liveTVBrowseListener);
			return true;
		}
		return false;
	}
}
