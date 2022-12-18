package com.hisilicon.dlna.dmc.gui.activity;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.types.UDN;
import org.teleal.cling.support.model.item.AudioItem;
import org.teleal.cling.support.model.item.ImageItem;
import org.teleal.cling.support.model.item.MusicTrack;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.provider.MediaStore;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.gui.browse.files.DeviceAccessBroadcast;
import com.hisilicon.dlna.dmc.gui.customview.DMSBrowseView;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.DMRProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.interfaces.UpnpProcessor.DevicesListener;
import com.hisilicon.dlna.dmc.processor.interfaces.UpnpProcessor.SystemListener;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.multiscreen.mybox.MyApp;
import com.hisilicon.multiscreen.mybox.R;

public class DMSBrowseActivity extends Activity{
	private Activity activity;
	private DMSBrowseView dmsBrowseView;
	private RelativeLayout browseLayout;
	private ImageView rc_quickPlayPause;
	public static boolean firstLoad = true;

	private Handler myHandler = new Handler();
//	private boolean connectStatue = false;
//	private DeviceAccessBroadcast receiver;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		activity = this;
		super.onCreate(savedInstanceState);
		System.out.println("------------ DMSBrowseActivity DMSB-------------");
		MyApp.setSTBIP(getIntent().getStringExtra("STBIP"));
//		connectStatue = getIntent().getBooleanExtra("ConnectStatue", false);
//		if(!connectStatue){
//			UpnpProcessorImpl.getSington().removeAllRemoteDevices();
//		}
//		System.out.println("The connectStatue is:" + connectStatue);
		setContentView(R.layout.activity_dmsbrowse);

		rc_quickPlayPause = (ImageView) findViewById(R.id.rc_quickPlayPause);
		browseLayout = (RelativeLayout) findViewById(R.id.browse_layout);

		
		
		dmsBrowseView = new DMSBrowseView(activity);
		browseLayout.addView(dmsBrowseView);
		startRunnable();
//		myHandler.postDelayed(runnable, 100);
		
		//		mMultiScreenControlService = MultiScreenControlService.getInstance();
//		receiver = new DeviceAccessBroadcast();
//		registerReceiver(receiver, new IntentFilter("com.device.access"));
//		if(connectStatue)
//			dmsBrowseView.updateDMRDevice();
		//		registerReceiver(receiver, new IntentFilter(DeviceDiscoveryActivity.DEVICE_DISCONNECT));
	}

	/**
	 * CN: 绑定DLNA服务
	 */
	
	private void startRunnable(){
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				System.out.println("Come into runnable!");
				UpnpProcessorImpl.getSington().addSystemListener(systemListener);
				UpnpProcessorImpl.getSington().bindUpnpService(); 
			}
		}).start();
	}
	private Runnable runnable = new Runnable() {

		@Override
		public void run() {
			System.out.println("Come into runnable!");
			//			DMSBrowseData.addSystemListener(systemListener);
			//			DMSBrowseData.addDeviceListener(deviceListener);
			//			dmsBrowseView.updateDMRDevice();
			//			dmsBrowseView.updateDMSDevice();
			//			DMSBrowseData.getInstance();
			UpnpProcessorImpl.getSington().addDevicesListener(new MyDeviceListener());
			UpnpProcessorImpl.getSington().addSystemListener(systemListener);
			UpnpProcessorImpl.getSington().bindUpnpService(); 
		}
	};

	private SystemListener systemListener = new SystemListener() {

		@Override
		public void onStartFailed() {
		}

		@Override
		public void onStartComplete() {
			new Thread(new Runnable() {

				@Override
				public void run() {

					try
					{
						System.out.println("Come into updateOrCreateShareAMContent--><");
						UpnpProcessorImpl.getSington().updateOrCreateShareContent();

						runOnUiThread(new Runnable() {

							@Override
							public void run() {
//								if(connectStatue)
									dmsBrowseView.updateDMRDevice();
								dmsBrowseView.updateDMSDevice();
							}
						});
					}
					catch (Exception e)
					{
						e.printStackTrace();
					}

				}
			}).start();
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

	@Override
	protected void onResume() {
		super.onResume();
		updateQuickPalyPause();
		dmsBrowseView.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();
		dmsBrowseView.onPause();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		try {
			AppPreference.setPlayPosition(0);
			UpnpProcessorImpl.getSington().removeSystemListener(systemListener);
			dmsBrowseView.onDestroy();
			stopDMR();
		} finally {
//			UpnpProcessorImpl.getSington().removeAllRemoteDevices();
			UpnpProcessorImpl.getSington().unbindUpnpService();
		}
//		unregisterReceiver(receiver);
	}

	/**
	 * CN:停止播放的媒体
	 */
	private void stopDMR() {
		DMRProcessor dmrProcessor = UpnpProcessorImpl.getSington()
				.getDMRProcessor();
		if (dmrProcessor != null)
			dmrProcessor.dispose();
	}

	private void updateQuickPalyPause() {
		PlaylistItem item = getCurrentPlaylistItem();
		if (item == null || item.getData() instanceof ImageItem) {
			rc_quickPlayPause.setVisibility(View.GONE);
		} else {
			if(item.getPlayStatue()==0||item.getPlayStatue()==2)
				rc_quickPlayPause.setVisibility(View.GONE);
			else
				rc_quickPlayPause.setVisibility(View.VISIBLE);
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
		UpnpProcessorImpl.getSington().stopLoading();

		boolean isBack = dmsBrowseView.backTo();
		if (!isBack) {
			finish();
		}
	}

	public void onTakePhotoClick(View view) {
		pickPhotoFromCamera();
	}

	private void pickPhotoFromCamera() {
		if (!Environment.MEDIA_MOUNTED.equals(Environment
				.getExternalStorageState())) {
			Toast.makeText(activity, R.string.sdcard_not_found,
					Toast.LENGTH_LONG).show();
			return;
		}
		startTakePhoto();

	}

	private void startTakePhoto() {
		try {
			Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE, null);

			File photoPath = new File(PhotoPickerActivity.CAMERA_CATCH_PATH);
			photoPath.mkdirs();
			File photo = new File(photoPath, new SimpleDateFormat(
					"yyMMddHHmmss").format(new Date()) + ".jpg");
			try {
				if (!photo.exists())
					photo.createNewFile();
			} catch (IOException e) {
				e.printStackTrace();
			}

			AppPreference.setCameraCachePath(photo.getAbsolutePath());

			Uri photoUri = Uri.fromFile(photo);

			intent.putExtra(MediaStore.EXTRA_OUTPUT, photoUri);
			intent.putExtra(MediaStore.EXTRA_VIDEO_QUALITY, 100);

			startActivityForResult(intent,
					PhotoPickerActivity.PHOTO_PICKER_FROM_CAMERA);

		} catch (ActivityNotFoundException e) {
			Toast.makeText(activity, R.string.photoPickerNotFound,
					Toast.LENGTH_LONG).show();
		}
	}

	private void videoMethod() {

		Intent intent = new Intent(MediaStore.ACTION_VIDEO_CAPTURE);
		intent.putExtra(MediaStore.EXTRA_VIDEO_QUALITY, 0);
		startActivityForResult(intent,
				PhotoPickerActivity.VIDEO_PICKER_FROM_CAMERA);

	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (resultCode == Activity.RESULT_OK) {
			doPhoto(requestCode, data);

		}
		super.onActivityResult(requestCode, resultCode, data);
	}

	private void doPhoto(int requestCode, Intent data) {

		switch (requestCode) {
		case PhotoPickerActivity.PHOTO_PICKER_FROM_CAMERA:

			String photoPath = AppPreference.getCameraCachePath();
			if (photoPath == null || "".equals(photoPath)) {
				Toast.makeText(this, R.string.file_pick_error,
						Toast.LENGTH_LONG).show();
				finish();
				return;
			}

			AppPreference.setCameraCachePath("");

			Intent intent = new Intent(activity, PhotoPickerActivity.class);
			intent.putExtra(PhotoPickerActivity.PHOTO_PICKER_INTENT_KEY,
					photoPath);
			startActivity(intent);

			break;

		default:
			break;
		}

	}

	public void onPlayPauseClick(View view) {
		PlaylistItem item = getCurrentPlaylistItem();
		if (item == null)
			return;
		Object object = item.getData();
		if (object instanceof ImageItem) {
			Intent intent = new Intent(activity, PlayingImageActivity.class);
			activity.startActivity(intent);
		} else if (object instanceof AudioItem || object instanceof MusicTrack) {
			Intent intent = new Intent(activity, PlayingMusicActivity.class);
			activity.startActivity(intent);
		} else {
			Intent intent = new Intent(activity, PlayingVideoActivity.class);
			activity.startActivity(intent);
		}
	}

	private PlaylistItem getCurrentPlaylistItem() {
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington()
				.getPlaylistProcessor();
		if (playlistProcessor == null)
			return null;
		return playlistProcessor.getCurrentItem();
	}

	/**
	BroadcastReceiver receiver = new BroadcastReceiver(){

		@Override
		public void onReceive(Context context, Intent intent) {
			if(intent.getAction().equals(DeviceDiscoveryActivity.DEVICE_DISCONNECT)){
				UpnpProcessorImpl.getSington().removeAllRemoteDevices();
			}else if(intent.getAction().equals(DeviceDiscoveryActivity.DEVICE_CONNECT)){
				UpnpProcessorImpl.getSington().bindUpnpService();
			}
		}
	};
	 */

	private class MyDeviceListener implements DevicesListener{

		@Override
		public
		void onDeviceAdded(Device device) {
			// TODO Auto-generated method stub
			System.out.println("------Come into MyDeviceListener->" + device.getDetails().getFriendlyName());
			if (device.getType().getNamespace().equals("schemas-upnp-org")) {
				if (device.getType().getType().equals("MediaRenderer")) {
					System.out.println("--Come into DMR device add->" + device.getDetails().getFriendlyName());
					addSTBDMR(device);
				}
			}
		}

		@Override
		public
		void onDeviceRemoved(Device device) {
			// TODO Auto-generated method stub

		}

		@Override
		public void onDMSChanged() {
			// TODO Auto-generated method stub

		}

		@Override
		public void onDMRChanged() {
			// TODO Auto-generated method stub

		}
		
		@Override
		public void onDeviceUpdate(Device device) {
			// TODO Auto-generated method stub
			if (device.getType().getNamespace().equals("schemas-upnp-org")) {
				if (device.getType().getType().equals("MediaRenderer")) {
					System.out.println("--Come into DMR device onDeviceUpdate->" + device.getDetails().getFriendlyName());
					updateSTBDMR(device);
				}
			}
		}
		
		private void addSTBDMR(Device device) {
			Device dmrDevice = UpnpProcessorImpl.getSington().getCurrentDMR();
			if (HttpServerUtil.isSTBDMR(dmrDevice))
				return;

			if (HttpServerUtil.isSTBDMR(device))
			{
				UDN udn = device.getIdentity().getUdn();
				UpnpProcessorImpl.getSington().stbOnline(udn);
			}
		}

		private void updateSTBDMR(Device device){
			Device dmrDevice = UpnpProcessorImpl.getSington().getCurrentDMR();
			if (HttpServerUtil.isSTBDMR(dmrDevice))
				return;

			if (HttpServerUtil.isSTBDMR(device))
			{
				UDN udn = device.getIdentity().getUdn();
				UpnpProcessorImpl.getSington().stbOnline(udn);
			}
		}
		
	}
}
