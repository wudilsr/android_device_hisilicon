package com.hisilicon.dlna.dmc.processor.upnp.mediaserver;

import java.io.IOException;
import java.net.URI;

import org.teleal.cling.binding.annotations.AnnotationLocalServiceBinder;
import org.teleal.cling.model.DefaultServiceManager;
import org.teleal.cling.model.ValidationException;
import org.teleal.cling.model.meta.DeviceDetails;
import org.teleal.cling.model.meta.DeviceIdentity;
import org.teleal.cling.model.meta.Icon;
import org.teleal.cling.model.meta.LocalDevice;
import org.teleal.cling.model.meta.LocalService;
import org.teleal.cling.model.meta.ManufacturerDetails;
import org.teleal.cling.model.meta.ModelDetails;
import org.teleal.cling.model.types.DeviceType;
import org.teleal.cling.model.types.UDADeviceType;
import org.teleal.cling.model.types.UDN;

import android.content.Context;
import android.os.Build;
import android.util.Log;

import com.hisilicon.dlna.dmc.gui.activity.AppPreference;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.R;

public class MediaServer {
	private final static String LOGTAG = MediaServer.class.getName();
	
	private final static String deviceType = "MediaServer";
	private final static int version = 1;
	private final static String modelNumber = "v1";
	
	private String friendlyName;
	private String manufacturer;
	private UDN udn;
	
	private LocalService<LocalContentDirectoryService> contentDirectoryService;
	private LocalDevice localDevice;
	private HttpServer httpServer;
	
	public MediaServer(Context context) throws ValidationException {
		friendlyName = AppPreference.getFriendlyName() + "-" + deviceType;
		manufacturer = AppPreference.getManufacturer();
		
		String deviceName = Build.MODEL.toUpperCase() + " " + Build.DEVICE.toUpperCase() + " - DMS";
		udn = UDN.uniqueSystemIdentifier(deviceName + friendlyName);
		
		DeviceType type = new UDADeviceType(deviceType, version);

		DeviceDetails details = new DeviceDetails(friendlyName,
				new ManufacturerDetails(manufacturer),
				new ModelDetails(deviceName, deviceName + " MediaServer for Android", modelNumber));

		contentDirectoryService = new AnnotationLocalServiceBinder().read(LocalContentDirectoryService.class); 
		contentDirectoryService.setManager(new DefaultServiceManager<LocalContentDirectoryService>(contentDirectoryService, LocalContentDirectoryService.class));
		
		LocalService<LocalConnectionManagerService> connectionManager = new AnnotationLocalServiceBinder().read(LocalConnectionManagerService.class);
        connectionManager.setManager(new DefaultServiceManager<LocalConnectionManagerService>(connectionManager, LocalConnectionManagerService.class));

        try {
			Icon icon = new Icon("image/png", 48, 48, 8, URI.create(""), Utility.readStreamAsByte(context.getResources().openRawResource(R.raw.icon)));
			localDevice = new LocalDevice(new DeviceIdentity(udn), type, details, icon, new LocalService[] { contentDirectoryService, connectionManager });
		} catch (Exception e) {
			localDevice = new LocalDevice(new DeviceIdentity(udn), type, details, new LocalService[] { contentDirectoryService, connectionManager });
		}
		
		//start http server
		try {
			httpServer = new HttpServer(HttpServerUtil.PORT);
		}
		catch (Exception ioe )
		{
			ioe.printStackTrace();
			System.err.println( "Couldn't start server:\n" + ioe );
			System.exit( -1 );
		}
		
		Log.v(LOGTAG, "Started Http Server on port " + HttpServerUtil.PORT);
	}
	
	public LocalService getLocalService() {
		return contentDirectoryService;
	}

	public LocalDevice getDevice() {
		return localDevice;
	}
	
	public void stopHttpServer() {
		httpServer.stop();
	}
}
