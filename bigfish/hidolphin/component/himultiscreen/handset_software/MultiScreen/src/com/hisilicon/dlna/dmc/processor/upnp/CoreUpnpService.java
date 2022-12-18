package com.hisilicon.dlna.dmc.processor.upnp;

import java.net.NetworkInterface;
import java.util.ArrayList;
import java.util.List;

import org.teleal.cling.UpnpService;
import org.teleal.cling.UpnpServiceConfiguration;
import org.teleal.cling.UpnpServiceImpl;
import org.teleal.cling.android.AndroidUpnpServiceConfiguration;
import org.teleal.cling.android.AndroidWifiSwitchableRouter;
import org.teleal.cling.controlpoint.ControlPoint;
import org.teleal.cling.model.ModelUtil;
import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.LocalDevice;
import org.teleal.cling.model.meta.RemoteDevice;
import org.teleal.cling.model.types.ServiceType;
import org.teleal.cling.model.types.UDAServiceType;
import org.teleal.cling.model.types.UDN;
import org.teleal.cling.protocol.ProtocolFactory;
import org.teleal.cling.registry.Registry;
import org.teleal.cling.registry.RegistryListener;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.transport.Router;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiManager.WifiLock;
import android.os.AsyncTask;
import android.os.IBinder;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;

import com.hisilicon.dlna.dmc.processor.impl.DMSProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.LocalDMRProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.LocalDMSProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.RemoteDMRProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor.DMRProcessorListener;
import com.hisilicon.dlna.dmc.processor.interfaces.DMSProcessor;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentNode;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentTree;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.MediaInitException;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.MediaServer;
import com.hisilicon.dlna.dmc.receiver.NetworkStateReceiver;
import com.hisilicon.dlna.dmc.receiver.NetworkStateReceiver.RouterStateListener;
import com.hisilicon.dlna.dmc.utility.GlobalCache;

public class CoreUpnpService extends Service {
	public final static String AIRSHARE_EXIT = "AIRSHARE_EXIT";
	public final static String PLAYLIST_CHANGED = "PLAYLIST_CHANGED";
	private static MediaServer mediaServer;
	/**
	 * 媒体文件是否已准备好
	 */
	private static boolean mediaPrepared = false;
	/**
	 * 媒体文件是否发布到Server
	 */
	private static boolean serverPrepared = false;
	/**
	 * 媒体文件是否正在准备中
	 */
	private static boolean isBusySharingContent = false;
	/**
	 * 爱分享是否已成功加载文件
	 */
	private static boolean isAirShare = false;
	
	private UDN m_localDMS_UDN = null;
	private UDN m_localDMR_UDN = null;
	
	@SuppressWarnings("rawtypes")
	private Device currentDMS;
	@SuppressWarnings("rawtypes")
	private Device currentDMR;
	
	private DMSProcessor dmsProcessor;
	private DMRProcessor dmrProcessor;
	/**
	 * UPNP 服务是否已启动
	 */
	private volatile boolean isInitialized;
	private UpnpService upnpService;
	
	private CoreUpnpServiceBinder upnpBinder = new CoreUpnpServiceBinder();
	
	private CoreUpnpServiceListener upnpServiceListener;
	private WifiLock wifiLock;
	
	private WifiManager wifiManager;
	private ConnectivityManager connectivityManager;
	
	private NetworkStateReceiver networkReceiver;
	
	private RegistryListener registryListener;
	private WakeLock serviceWakeLock;
	
	private List<DMRProcessorListener> dmrListeners;

	@Override
	public void onCreate() {
		super.onCreate();
		isInitialized = false;

		dmrListeners = new ArrayList<DMRProcessor.DMRProcessorListener>();

		PowerManager mgr = (PowerManager) getSystemService(Context.POWER_SERVICE);
		serviceWakeLock = mgr.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, this.getClass().getCanonicalName());
		serviceWakeLock.acquire();

		wifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
		connectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
		
		initializedUpnpService();
	}
	
	private void initializedUpnpService() {
		try {
			upnpService = new UpnpServiceImpl(createConfiguration(wifiManager)) {
				@Override
				protected Router createRouter(ProtocolFactory protocolFactory, Registry registry) {
					AndroidWifiSwitchableRouter router = CoreUpnpService.this.createRouter(getConfiguration(), protocolFactory,
							wifiManager, connectivityManager);
					networkReceiver = new NetworkStateReceiver(router, new RouterStateListener() {

						@Override
						public void onRouterError(String cause) {
							if (upnpServiceListener != null)
								upnpServiceListener.onRouterError("No network found");
						}

						@Override
						public void onNetworkChanged(NetworkInterface ni) {
							try
							{
								changedNetWork();
							}
							catch (MediaInitException e)
							{
								e.printStackTrace();
							}
							
							if (upnpServiceListener != null) {
								upnpServiceListener.onNetworkChanged(ni);
							}
						}

						@Override
						public void onRouterEnabled() {
							if (upnpServiceListener != null)
								upnpServiceListener.onRouterEnabled();
						}

						@Override
						public void onRouterDisabled() {
							if (upnpServiceListener != null)
								upnpServiceListener.onRouterDisabled();
						}
					});
					if (!ModelUtil.ANDROID_EMULATOR) {
						IntentFilter filter = new IntentFilter();
						filter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);
						filter.addAction("android.net.wifi.WIFI_AP_STATE_CHANGED");
						registerReceiver(networkReceiver, filter);
					}
					return router;
				}
			};
			isInitialized = true;
		} catch (Exception ex) {
			isInitialized = false;
		}

		if (isInitialized) {
			// prevent wifi sleep when screen
			wifiLock = wifiManager.createWifiLock(3, "UpnpWifiLock");
			wifiLock.acquire();

			startLocalDMS();

			dmrListeners.clear();
		}
		
		IntentFilter filter = new IntentFilter();
		filter.addAction(AIRSHARE_EXIT);
		filter.addAction(PLAYLIST_CHANGED);
		registerReceiver(changedReceiver, filter);
	}

	protected AndroidUpnpServiceConfiguration createConfiguration(WifiManager wifiManager) {
		return new AndroidUpnpServiceConfiguration(wifiManager, connectivityManager) {
			@Override
			public ServiceType[] getExclusiveServiceTypes() {
				return new ServiceType[] { new UDAServiceType("AVTransport"), new UDAServiceType("ContentDirectory"),
						new UDAServiceType("RenderingControl") };
			}
		};
	}

	protected AndroidWifiSwitchableRouter createRouter(UpnpServiceConfiguration configuration, ProtocolFactory protocolFactory,
			WifiManager wifiManager, ConnectivityManager connectivityManager) {
		return new AndroidWifiSwitchableRouter(configuration, protocolFactory, wifiManager, connectivityManager);
	}
	
	private void changedNetWork() throws MediaInitException
	{
		if (isAirShare)
		{
			serverPrepared = false;
			ContentTree.clear();

			prepareShareContent();
		}
	}

	@Override
	public void onDestroy() {
		try {
			serviceWakeLock.release();
			unregisterReceiver();

			if (dmsProcessor != null)
				dmsProcessor.dispose();

			if (dmrProcessor != null)
				dmrProcessor.dispose();
			releaseWifiLock();

			GlobalCache.clear();

			if (upnpService != null) {
				new AsyncTask<Void, Void, Void>() {

					@Override
					protected Void doInBackground(Void... params) {
						try {
							upnpService.getRegistry().removeAllLocalDevices();
							upnpService.getRegistry().removeAllRemoteDevices();
							upnpService.getRegistry().removeListener(registryListener);
							upnpService.shutdown();
							upnpService = null;
						} catch (Exception ex) {
							ex.printStackTrace();
						}
						return null;
					}

					protected void onPostExecute(Void result) {

					};
				}.execute(new Void[] {});
			}
		} finally {
			android.os.Process.killProcess(android.os.Process.myPid());
		}
	}

	private void unregisterReceiver() {
		try {
			if (networkReceiver != null)
				unregisterReceiver(networkReceiver);
		} catch (Exception ex) {

		}
		try {
			unregisterReceiver(changedReceiver);
		} catch (Exception ex) {

		}
	}

	private void releaseWifiLock() {
		if (wifiLock != null)
			try {
				wifiLock.release();
			} catch (Exception ex) {
				ex.printStackTrace();
			}
	}

	@Override
	public IBinder onBind(Intent intent) {
		return upnpBinder;
	}

	public class CoreUpnpServiceBinder extends android.os.Binder {

		public boolean isInitialized() {
			return isInitialized;
		}

		public DMSProcessor getDMSProcessor() {
			return dmsProcessor;
		}

		public DMRProcessor getDMRProcessor() {
			return dmrProcessor;
		}

		public void setCurrentDMS(UDN uDN) {
			m_localDMS_UDN = uDN;

			dmsProcessor = null;

			currentDMS = upnpService.getRegistry().getDevice(uDN, true);
			
			if (currentDMS instanceof RemoteDevice) {
				dmsProcessor = new DMSProcessorImpl(currentDMS, getControlPoint());
			} else if (currentDMS instanceof LocalDevice) {
				dmsProcessor = new LocalDMSProcessorImpl();
			} else {
				dmsProcessor = null;
			}
		}

		public void setLiveTV(UDN uDN) {
			Device liveTVDevice = upnpService.getRegistry().getDevice(uDN, true);
			
			if (liveTVDevice instanceof RemoteDevice) {
				dmsProcessor = new DMSProcessorImpl(liveTVDevice, getControlPoint());
			} else {
				dmsProcessor = null;
			}
		}

		public void stbOnline(UDN uDN) {
			m_localDMR_UDN = uDN;

			currentDMR = upnpService.getRegistry().getDevice(uDN, true);
		}

		public void setCurrentDMR(UDN uDN) {
			m_localDMR_UDN = uDN;

			if (dmrProcessor != null)
				dmrProcessor.dispose();
			
			if (uDN == null)
			{
				dmrProcessor = new LocalDMRProcessorImpl(CoreUpnpService.this);;
				
				synchronized (dmrListeners)
				{
					for (DMRProcessorListener listener : dmrListeners)
						dmrProcessor.addListener(listener);
				}

				return;
			}

			currentDMR = upnpService.getRegistry().getDevice(uDN, true);

			if (dmrProcessor != null && currentDMR instanceof RemoteDevice)
			{
				dmrProcessor = new RemoteDMRProcessorImpl(currentDMR, getControlPoint());

				synchronized (dmrListeners)
				{
					for (DMRProcessorListener listener : dmrListeners)
						dmrProcessor.addListener(listener);
				}
				
//				PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
//				if (playlistProcessor != null)
//					dmrProcessor.setURIandPlay(playlistProcessor.getCurrentItem());

			}
			else
			{
				dmrProcessor = new LocalDMRProcessorImpl(CoreUpnpService.this);;
				
				synchronized (dmrListeners) {
					for (DMRProcessorListener listener : dmrListeners)
						dmrProcessor.addListener(listener);
				}
			}
		}
		
		@SuppressWarnings("rawtypes")
		public Device getCurrentDMS() {
			return currentDMS;
		}

		@SuppressWarnings("rawtypes")
		public Device getCurrentDMR() {
			return currentDMR;
		}

		public UpnpService get() {
			return upnpService;
		}

		public UpnpServiceConfiguration getConfiguration() {
			return upnpService != null ? upnpService.getConfiguration() : null;
		}

		public Registry getRegistry() {
			return upnpService != null ? upnpService.getRegistry() : null;
		}

		public ControlPoint getControlPoint() {
			return upnpService != null ? upnpService.getControlPoint() : null;
		}

		public void setProcessor(CoreUpnpServiceListener listener) {
			upnpServiceListener = listener;
		}

		public void addRegistryListener(RegistryListener listener) {
			registryListener = listener;
			upnpService.getRegistry().addListener(listener);
		}

		public void setDMSExported(boolean value) {
			
		}

		public void addDMRListener(DMRProcessorListener listener) {
			synchronized (dmrListeners) {
				if (!dmrListeners.contains(listener))
					dmrListeners.add(listener);
				if (dmrProcessor != null)
					dmrProcessor.addListener(listener);
			}
		}

		public void removeDMRListener(DMRProcessorListener listener) {
			synchronized (dmrListeners) {
				dmrListeners.remove(listener);
				if (dmrProcessor != null)
					dmrProcessor.removeListener(listener);
			}
		}
		
		public void updateOrCreateShareContent() throws MediaInitException {
			prepareShareContent(); 
			isAirShare = true;
		}
		
		public void updateOrCreateShareAMContent() throws MediaInitException {
			preareShareAMContent(); 
			isAirShare = true;
		}

		public void stopLoading() {
			ContentTree.stopLoading();
		}
	}
	
	@SuppressWarnings("unchecked")
	private void startLocalDMS() {
		try {
			mediaServer = new MediaServer(this);

			Registry localRegistry = upnpService.getRegistry();
			LocalDevice localLocalDevice = mediaServer.getDevice();
			localRegistry.addDevice(localLocalDevice);

//			refreshShareContent();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
	
	private void prepareShareContent() throws MediaInitException
	{
		if (!isBusySharingContent)
		{
			prepareMediaServer();//new RefreshContentThread().start();
		}
	}
	
	private void preareShareAMContent() throws MediaInitException
	{
		if (!isBusySharingContent)
		{
			prepareAMMediaServer();//new RefreshContentThread().start();
		}
	}

	class RefreshContentThread extends Thread 
	{
		public void run()
		{
			try
			{
				if (!isBusySharingContent)
				{
					prepareMediaServer();
				}
			}
			catch (MediaInitException e)
			{
				e.printStackTrace();
			}
		}
	}
	
	private synchronized void prepareMediaServer() throws MediaInitException
	{
		isBusySharingContent = true;
		try
		{
			if (serverPrepared)
				return;
			ContentTree.clear();
			
			System.out.println("Come into initPlaylist--><");
			ContentTree.initPlaylist();

			if (!mediaPrepared)
			{
				System.out.println("Come into mediaPrepared--><");
				ContentTree.initAllMedia();
				mediaPrepared = true;
			}
			else
			{
				System.out.println("Come into media not Prepared--><");
				// Image Container
				ContentTree.createPhotosAlbumsDir();

				// Video Container
				ContentTree.createVideosAlbumsDir();

				// Audio Container
				ContentTree.createAudiosAlbumsDir();
			}
			
			serverPrepared = true;
		}
		catch(MediaInitException ex)
		{
			ex.printStackTrace();
			throw new MediaInitException(ex);
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
		}
		finally
		{
			isBusySharingContent = false;
		}
	}
	
	private synchronized void prepareAMMediaServer() throws MediaInitException
	{
		isBusySharingContent = true;
		try
		{
			System.out.println("The serverPrepared is:" + serverPrepared);
			if (serverPrepared)
				return;
			ContentTree.clear();

			System.out.println("Come into mediaPrepared1--><");
			ContentTree.initPlaylist();

			if (!mediaPrepared)
			{
				System.out.println("Come into mediaPrepared2--><");
				ContentTree.initAudioAndMusic();
				mediaPrepared = true;
			}
			else
			{
				System.out.println("Come into prepareAMMediaServer--><");
				// Image Container
				ContentTree.createPhotosAlbumsDir();

				// Video Container
				ContentTree.createVideosAlbumsDir();

				// Audio Container
				ContentTree.createAudiosAlbumsDir();
			}
			System.out.println("Come into prepareAMMediaServer end--><");
			serverPrepared = true;
		}
		catch(MediaInitException ex)
		{
			ex.printStackTrace();
			throw new MediaInitException(ex);
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
		}
		finally
		{
			isBusySharingContent = false;
		}
	}
	
	private BroadcastReceiver changedReceiver = new BroadcastReceiver() {

		@Override
		public void onReceive(Context context, Intent intent) {
			if (intent.getAction().equals(AIRSHARE_EXIT)) {
				onDestroy();
				return;
			}
			ContentNode node = ContentTree.getNode(ContentTree.PLAYLIST_ID);
			if (node != null) {
				Container playlistContainer = node.getContainer();
				playlistContainer.getContainers().clear();
				playlistContainer.getItems().clear();
				playlistContainer.setChildCount(0);
				
				ContentTree.initPlaylist();
			}
		}
		
	};
	
	public interface CoreUpnpServiceListener {
		void onNetworkChanged(NetworkInterface ni);

		void onRouterError(String message);

		void onRouterDisabled();

		void onRouterEnabled();
	}
}
