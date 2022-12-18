package com.hisilicon.dlna.dmc.processor.impl;

import java.net.NetworkInterface;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import org.teleal.cling.controlpoint.ControlPoint;
import org.teleal.cling.model.message.header.UDNHeader;
import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.LocalDevice;
import org.teleal.cling.model.meta.RemoteDevice;
import org.teleal.cling.model.types.DeviceType;
import org.teleal.cling.model.types.UDN;
import org.teleal.cling.registry.Registry;
import org.teleal.cling.registry.RegistryListener;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;

import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor.DMRProcessorListener;
import com.hisilicon.dlna.dmc.processor.interfaces.DMSProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.PlaylistListener;
import com.hisilicon.dlna.dmc.processor.interfaces.UpnpProcessor;
import com.hisilicon.dlna.dmc.processor.upnp.CoreUpnpService;
import com.hisilicon.dlna.dmc.processor.upnp.CoreUpnpService.CoreUpnpServiceBinder;
import com.hisilicon.dlna.dmc.processor.upnp.CoreUpnpService.CoreUpnpServiceListener;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.MediaInitException;
import com.hisilicon.multiscreen.mybox.MyApp;

public class UpnpProcessorImpl implements UpnpProcessor, RegistryListener, CoreUpnpServiceListener {
	private static UpnpProcessor upnpProcessor;

	private CoreUpnpServiceBinder upnpService;
	private PlaylistProcessor playlistProcessor;

	private List<DevicesListener> devicesListeners;
	private List<SystemListener> systemListeners;
	private List<PlaylistListener> playlistListeners;

	private ServiceConnection serviceConnection;
	private List<Device> devices = new ArrayList<Device>();

	private UpnpProcessorImpl() {
		systemListeners = new ArrayList<SystemListener>();
		devicesListeners = new ArrayList<DevicesListener>();
		playlistListeners = new ArrayList<PlaylistProcessor.PlaylistListener>();
	}

	public static UpnpProcessor getSington() {
		if (upnpProcessor == null)
			upnpProcessor = new UpnpProcessorImpl();
		return upnpProcessor;
	}


	public void bindUpnpService() {
		serviceConnection = new ServiceConnection() {

			public void onServiceDisconnected(ComponentName name) {
				upnpService = null;
			}

			public void onServiceConnected(ComponentName name, IBinder service) {
				upnpService = (CoreUpnpServiceBinder) service;
				if (upnpService.isInitialized()) {
					upnpService.addRegistryListener(UpnpProcessorImpl.this);

					fireOnStartCompleteEvent();

					upnpService.setProcessor(UpnpProcessorImpl.this);
					upnpService.getControlPoint().search();
				} else {
					fireOnStartFailedEvent();
				}
			}
		};

		Intent intent = new Intent(MyApp.getApplication(), CoreUpnpService.class);
		MyApp.getApplication().bindService(intent, serviceConnection, Context.BIND_AUTO_CREATE);
	}

	public void unbindUpnpService() {
		try {
			if (serviceConnection != null) {
				try {
					MyApp.getApplication().unbindService(serviceConnection);
				} catch (Exception ex) {
					ex.printStackTrace();
				}
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	public void removeAllRemoteDevices(){
		try{
			if(upnpService!=null)
				upnpService.getRegistry().removeAllRemoteDevices();
		}catch(Exception e){
			e.printStackTrace();
		}
	}

	@Override
	public void updateOrCreateShareContent() throws MediaInitException {
		if (upnpService != null) {
			upnpService.updateOrCreateShareContent();
		}
	}

	public void updateOrCreateShareAMContent() throws MediaInitException {
		if (upnpService != null) {
			upnpService.updateOrCreateShareAMContent();
		}
	}

	public void searchAll() {
		if (upnpService != null) {
			upnpService.getRegistry().removeAllRemoteDevices();
			upnpService.getControlPoint().search();
		}
	}

	public void addDevicesListener(DevicesListener listener) {
		synchronized (devicesListeners) {
			if (!devicesListeners.contains(listener)) {
				devicesListeners.add(listener);
			}
		}
	}
	
	public void removeDevicesListener(DevicesListener listener) {
		synchronized (devicesListeners) {
			if (devicesListeners.contains(listener)) {
				devicesListeners.remove(listener);
			}
		}
	}

	public Registry getRegistry() {
		return upnpService.getRegistry();
	}

	public ControlPoint getControlPoint() {
		return upnpService != null ? upnpService.getControlPoint() : null;
	}

	private void fireOnStartCompleteEvent() {
		if (systemListeners != null)
			synchronized (systemListeners) {
				for (SystemListener listener : systemListeners) {
					if (listener != null)
						listener.onStartComplete();
				}
			}
	}

	private void fireOnStartFailedEvent() {
		if (systemListeners != null)
			synchronized (systemListeners) {
				for (SystemListener listener : systemListeners) {
					if (listener != null)
						listener.onStartFailed();
				}
			}
	}

	private void fireOnRouterErrorEvent(String cause) {
		if (systemListeners != null)
			synchronized (systemListeners) {
				for (SystemListener listener : systemListeners) {
					if (listener != null)
						listener.onRouterError(cause);
				}
			}
	}

	private void fireOnNetworkChangedEvent() {
		if (systemListeners != null)
			synchronized (systemListeners) {
				for (SystemListener listener : systemListeners) {
					if (listener != null)
						listener.onNetworkChanged();
				}
			}
	}

	private void fireOnRouterDisabledEvent() {
		if (systemListeners != null)
			synchronized (systemListeners) {
				for (SystemListener listener : systemListeners) {
					if (listener != null)
						listener.onRouterDisabledEvent();
				}
			}
	}

	private void fireOnRouterEnabledEvent() {
		if (systemListeners != null)
			synchronized (systemListeners) {
				for (SystemListener listener : systemListeners) {
					if (listener != null)
						listener.onRouterEnabledEvent();
				}
			}
	}

	@Override
	public void remoteDeviceDiscoveryStarted(Registry registry, RemoteDevice device) {
	}

	@Override
	public void remoteDeviceDiscoveryFailed(Registry registry, RemoteDevice device, Exception ex) {
	}

	@Override
	public void remoteDeviceAdded(Registry registry, RemoteDevice device) {
		System.out.println("Come into remoteDeviceAdded!!" + device.getDetails().getFriendlyName());
		if (device.getType().getNamespace().equals("schemas-upnp-org")) {
			if (device.getType().getType().equals("MediaRenderer")) {
				addSTBDMR(device);
			}
		}

		fireDeviceAddedEvent(device);
	}

	private void addSTBDMR(Device device) {
		System.out.println("Come into addSTBDMR device");
		Device dmrDevice = UpnpProcessorImpl.getSington().getCurrentDMR();
		URL url = ((RemoteDevice) device).getIdentity().getDescriptorURL();
		System.out.println("The device port is:" + url.getPort());
		if (HttpServerUtil.isSTBDMR(dmrDevice)){
			System.out.println("addSTBDMR It is not null device's name:" + dmrDevice.getDetails().getFriendlyName());
			return;
		}
		System.out.println("addSTBDMR Dmr list size is:" + UpnpProcessorImpl.getSington().getDMRList().size());
		if (HttpServerUtil.isSTBDMR(device))
		{
			UDN udn = device.getIdentity().getUdn();
			UpnpProcessorImpl.getSington().stbOnline(udn);
		}
	}

	@Override
	public void remoteDeviceUpdated(Registry registry, RemoteDevice device) {
		System.out.println("Come into remoteDeviceUpdated!!" + device.getDetails().getFriendlyName());
		fireDeviceUpdateEvent(device);
	}

	@Override
	public void remoteDeviceRemoved(Registry registry, RemoteDevice device) {
		System.out.println("Come into remoteDeviceRemoved!!" + device.getDetails().getFriendlyName());
		if (device.getType().getNamespace().equals("schemas-upnp-org")) {
			if (device.getType().getType().equals("MediaRenderer")) {
				removeSTBDMR(device);
			}
		}

		fireDeviceRemovedEvent(device);
	}

	private void removeSTBDMR(Device device) {
		if (HttpServerUtil.isSTBDMR(device))
		{
			UpnpProcessorImpl.getSington().setCurrentDMR(null);
		}
	}

	@Override
	public void localDeviceAdded(Registry registry, LocalDevice device) {
		System.out.println("Come into localDeviceAdded!!" + device.getDetails().getFriendlyName());
		fireDeviceAddedEvent(device);
	}

	@Override
	public void localDeviceRemoved(Registry registry, LocalDevice device) {
		System.out.println("Come into localDeviceRemoved!!" + device.getDetails().getFriendlyName());
		fireDeviceRemovedEvent(device);
	}

	@Override
	public void beforeShutdown(Registry registry) {
	}

	@Override
	public void afterShutdown() {
	}

	@SuppressWarnings("rawtypes")
	private void fireDeviceAddedEvent(Device device) {
		if (devicesListeners != null)
			synchronized (devicesListeners) {
				for (DevicesListener listener : devicesListeners) {
					if (listener != null)
						listener.onDeviceAdded(device);
				}
			}
	}
	
	private void fireDeviceUpdateEvent(Device device) {
		if (devicesListeners != null)
			synchronized (devicesListeners) {
				for (DevicesListener listener : devicesListeners) {
					if (listener != null)
						listener.onDeviceUpdate(device);
				}
			}
	}

	@SuppressWarnings("rawtypes")
	private void fireDeviceRemovedEvent(Device device) {
		if (devicesListeners != null)
			synchronized (devicesListeners) {
				for (DevicesListener listener : devicesListeners) {
					if (listener != null)
						listener.onDeviceRemoved(device);
				}
			}
	}

	private void fireOnDMSChangedEvent() {
		if (devicesListeners != null)
			synchronized (devicesListeners) {
				for (DevicesListener listener : devicesListeners) {
					if (listener != null)
						listener.onDMSChanged();
				}
			}
	}

	private void fireOnDMRChangedEvent() {
		if (devicesListeners != null)
			synchronized (devicesListeners) {
				for (DevicesListener listener : devicesListeners) {
					if (listener != null)
						listener.onDMRChanged();
				}
			}
	}

	@SuppressWarnings("rawtypes")
	@Override
	public Collection<Device> getDMSList() {
		if (upnpService != null)
			return upnpService.getRegistry().getDevices(new DeviceType("schemas-upnp-org", "MediaServer"));
		return new ArrayList<Device>();
	}

	@SuppressWarnings("rawtypes")
	@Override
	public Collection<Device> getDMRList() {
		if (upnpService != null)
			return upnpService.getRegistry().getDevices(new DeviceType("schemas-upnp-org", "MediaRenderer"));
		return new ArrayList<Device>();
	}

	@SuppressWarnings("rawtypes")
	@Override
	public void setCurrentDMS(UDN uDN) {
		//		Device currentDMS = upnpService.getCurrentDMS();
		//		Device newDMS = upnpService.getRegistry().getDevice(uDN, true);
		//
		//		if (currentDMS == null || (newDMS != null && !newDMS.getIdentity().equals(currentDMS.getIdentity()))) {
		//			upnpService.setCurrentDMS(uDN);
		//		}
		upnpService.setCurrentDMS(uDN);
		fireOnDMSChangedEvent();
	}

	@SuppressWarnings("rawtypes")
	@Override
	public void setLiveTV(UDN uDN) {
		upnpService.setLiveTV(uDN);
	}

	@Override
	public void stbOnline(UDN uDN) {
		upnpService.stbOnline(uDN);
	}

	@SuppressWarnings("rawtypes")
	@Override
	public void setCurrentDMR(UDN uDN) {
		//		Device currentDMR = upnpService.getCurrentDMR();
		//		Device newDMR = upnpService.getRegistry().getDevice(uDN, true);
		//
		//		if (newDMR == null || currentDMR == null || !newDMR.getIdentity().equals(currentDMR.getIdentity())) {
		//			upnpService.setCurrentDMR(uDN);
		//		}
		if(upnpService!=null){
			upnpService.setCurrentDMR(uDN);
			fireOnDMRChangedEvent();
		}else{
//			bindUpnpService();
		}

	}

	@SuppressWarnings("rawtypes")
	@Override
	public Device getCurrentDMS() {
		return upnpService != null ? upnpService.getCurrentDMS() : null;
	}

	@SuppressWarnings("rawtypes")
	@Override
	public Device getCurrentDMR() {
		return upnpService != null ? upnpService.getCurrentDMR() : null;
	}

	@Override
	public PlaylistProcessor getPlaylistProcessor() {
		return playlistProcessor;
	}

	@Override
	public DMSProcessor getDMSProcessor() {
		return upnpService != null ? upnpService.getDMSProcessor() : null;
	}

	@Override
	public DMRProcessor getDMRProcessor() {
		return upnpService != null ? upnpService.getDMRProcessor() : null;
	}

	@Override
	public void onNetworkChanged(NetworkInterface ni) {
		fireOnNetworkChangedEvent();
	}

	@Override
	public void onRouterError(String message) {
		fireOnRouterErrorEvent(message);
	}

	@Override
	public void onRouterDisabled() {
		fireOnRouterDisabledEvent();
	}

	@Override
	public void onRouterEnabled() {
		fireOnRouterEnabledEvent();
	}

	@Override
	public void setPlaylistProcessor(PlaylistProcessor processor) {
		playlistProcessor = processor;

		if (processor == null)
		{
			playlistListeners.clear();
		} 
		else
		{
			synchronized (playlistListeners) {
				for (PlaylistListener listener : playlistListeners)
					playlistProcessor.addListener(listener);
			}
		}
	}

	@Override
	public void addSystemListener(SystemListener listener) {
		synchronized (systemListeners) {
			if (!systemListeners.contains(listener))
				systemListeners.add(listener);
		}
	}

	@Override
	public void removeSystemListener(SystemListener listener) {
		synchronized (systemListeners) {
			if (systemListeners.contains(listener))
				systemListeners.remove(listener);
		}

	}

	@Override
	public void refreshDevicesList() {
		if (upnpService != null) {
			upnpService.getRegistry().removeAllRemoteDevices();
			upnpService.getControlPoint().search();
		}
	}

	@Override
	public void refreshDevice(UDN udn) {
		if (upnpService != null && udn != null) {
			upnpService.getRegistry().removeDevice(udn);
			upnpService.getControlPoint().search(new UDNHeader(udn));
		}
	}

	@Override
	public void setDMSExproted(boolean value) {
		if (upnpService != null)
			upnpService.setDMSExported(value);
	}

	@Override
	public void addDMRListener(DMRProcessorListener listener) {
		if (upnpService != null)
			upnpService.addDMRListener(listener);
	}

	@Override
	public void removeDMRListener(DMRProcessorListener listener) {
		if (upnpService != null)
			upnpService.removeDMRListener(listener);
	}

	@Override
	public void addPlaylistListener(PlaylistListener listener) {
		synchronized (playlistListeners) {
			if (!playlistListeners.contains(listener))
				playlistListeners.add(listener);
			if (playlistProcessor != null)
				playlistProcessor.addListener(listener);
		}
	}

	@Override
	public void removePlaylistListener(PlaylistListener listener) {
		synchronized (playlistListeners) {
			playlistListeners.remove(listener);
			if (playlistProcessor != null)
				playlistProcessor.removeListener(listener);
		}
	}

	@Override
	public void stopLoading() {
		if (upnpService != null)
			upnpService.stopLoading();
	}

	@Override
	public void setDMSDevice(Device device){
		for(Device item:devices){
			if(item.getDetails().getFriendlyName().equals(device.getDetails().getFriendlyName()))
				return;
		}
		devices.add(device);
	}

	@Override
	public List<Device> getDMSDevices(){
		return devices;
	}

}
