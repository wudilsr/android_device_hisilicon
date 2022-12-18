package com.hisilicon.dlna.dmc.gui.activity;

import java.io.File;

import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.item.ImageItem;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.processor.impl.PlaylistProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentTree;
import com.hisilicon.dlna.dmc.utility.MyException;
import com.hisilicon.dlna.dmc.utility.ThumbnailGenerator;
import com.hisilicon.multiscreen.mybox.R;

public class PhotoPickerActivity extends Activity {
	public static final String SDCARD_ROOT = Environment
			.getExternalStorageDirectory().getAbsolutePath();
	public static final String CAMERA_CATCH_PATH = new StringBuilder()
			.append(SDCARD_ROOT).append("/Hisi/photo/").toString();
	public static final String CAMERA_PHOTO_KEY = "CAMERA_PHOTO_KEY";

	public static final String PHOTO_PICKER_INTENT_KEY = "PHOTO_PICKER_INTENT_KEY";

	public static final int PHOTO_PICKER_FROM_CAMERA = 2011;
	public static final int VIDEO_PICKER_FROM_CAMERA = 2012;

	private Activity activity;
	private String photoPath;
	private ImageView preview_photo;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		activity = this;
		super.onCreate(savedInstanceState);
		setContentView(R.layout.camera_capture);
		preview_photo = (ImageView) findViewById(R.id.preview_photo);

		photoPath = getIntent().getStringExtra(PHOTO_PICKER_INTENT_KEY);

		onPushClick(null);
	}

	public void onPushClick(View view) {
		if (photoPath == null || photoPath.equals("")) {
			Toast.makeText(this, R.string.file_pick_error, Toast.LENGTH_LONG)
					.show();
			finish();
			return;
		}
		PlaylistProcessor processor = UpnpProcessorImpl.getSington()
				.getPlaylistProcessor();

		if (null == processor) {
			processor = new PlaylistProcessorImpl();
			UpnpProcessorImpl.getSington().setPlaylistProcessor(processor);
		}

		DIDLObject object = ContentTree.getImageItemFromPath(photoPath);
		if (object == null) {
			finish();
		} else {

			processor.setItems(null);
			PlaylistItem item = processor.addDIDLObject(object);
			UpnpProcessorImpl.getSington().getPlaylistProcessor()
					.setCurrentItem(item);

			if (object instanceof ImageItem) {
				Intent intent = new Intent(activity, PlayingImageActivity.class);
				activity.startActivity(intent);
			}

			activity.finish();
		}
	}

	public void onBackClick(View view) {
		finish();
	}

	private void updateImage(String path) throws MyException {

		if (path == null || path.equals("")) {
			Toast.makeText(this, R.string.file_pick_error, Toast.LENGTH_LONG)
					.show();
			finish();
			return;
		}

		Bitmap bitmap = ThumbnailGenerator.getInstance().decodeFileBitmap(
				new File(path));

		if (bitmap != null && !bitmap.isRecycled()) {
			int degree = ThumbnailGenerator.getPhotoDegree(path);
			bitmap = ThumbnailGenerator.rotateBitmap(bitmap, degree);
		}

		if (bitmap != null && !bitmap.isRecycled())
			preview_photo.setImageBitmap(bitmap);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
	}
}