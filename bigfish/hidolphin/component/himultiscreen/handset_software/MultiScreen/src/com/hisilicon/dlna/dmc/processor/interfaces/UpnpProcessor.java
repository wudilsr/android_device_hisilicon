package com.hisilicon.dlna.dmc.processor.interfaces;

import java.util.Collection;
import java.util.List;

import org.teleal.cling.controlpoint.ControlPoint;
import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.types.UDN;
import org.teleal.cling.registry.Registry;

import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor.DMRProcessorListener;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor.PlaylistListener;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.MediaInitException;

public interface UpnpProcessor {
	void addDevicesListener(DevicesListener listener);

	void removeDevicesListener(DevicesListener listener);

	void addSystemListener(SystemListener listener);

	void addDMRListener(DMRProcessorListener listener);

	void removeDMRListener(DMRProcessorListener listener);

	void addPlaylistListener(PlaylistListener listener);

	void removePlaylistListener(PlaylistListener listener);

	void removeSystemListener(SystemListener listener);

	void bindUpnpService();

	void unbindUpnpService();
	
	void removeAllRemoteDevices();

	void stopLoading();

	void setCurrentDMS(UDN uDN);

	void setLiveTV(UDN uDN);

	void stbOnline(UDN uDN);

	void setCurrentDMR(UDN uDN);
	
	void refreshDevice(UDN uDN);

	void refreshDevicesList();

	void updateOrCreateShareContent() throws MediaInitException;
	
	void updateOrCreateShareAMContent() throws MediaInitException;

	Registry getRegistry();

	@SuppressWarnings("rawtypes")
	Device getCurrentDMS();

	@SuppressWarnings("rawtypes")
	Device getCurrentDMR();

	PlaylistProcessor getPlaylistProcessor();

	@SuppressWarnings("rawtypes")
	Collection<Device> getDMSList();

	@SuppressWarnings("rawtypes")
	Collection<Device> getDMRList();
	
	void setDMSDevice(Device device);
	
	List<Device> getDMSDevices();

	ControlPoint getControlPoint();

	DMSProcessor getDMSProcessor();

	DMRProcessor getDMRProcessor();

	void setPlaylistProcessor(PlaylistProcessor playlistProcessor);

	void setDMSExproted(boolean value);

	public interface DevicesListener {

		@SuppressWarnings("rawtypes")
		void onDeviceAdded(Device device);

		@SuppressWarnings("rawtypes")
		void onDeviceRemoved(Device device);
		
		@SuppressWarnings("rawtypes")
		void onDeviceUpdate(Device device);

		void onDMSChanged();

		void onDMRChanged();

	}

	public interface SystemListener {
		void onStartComplete();

		void onStartFailed();

		void onNetworkChanged();

		void onRouterError(String cause);

		void onRouterEnabledEvent();

		void onRouterDisabledEvent();
	}

}
