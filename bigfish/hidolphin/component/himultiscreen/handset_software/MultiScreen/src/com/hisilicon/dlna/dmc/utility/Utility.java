package com.hisilicon.dlna.dmc.utility;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.ArrayList;

import org.teleal.cling.support.contentdirectory.DIDLParser;
import org.teleal.cling.support.model.DIDLAttribute;
import org.teleal.cling.support.model.DIDLContent;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.ProtocolInfo;
import org.teleal.cling.support.model.Res;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.AudioItem;
import org.teleal.cling.support.model.item.ImageItem;
import org.teleal.cling.support.model.item.Item;
import org.teleal.cling.support.model.item.VideoItem;
import org.teleal.common.util.MimeType;

import android.content.Context;
import android.content.res.Resources;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Environment;
import android.util.DisplayMetrics;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.multiscreen.mybox.MyApp;
import com.hisilicon.multiscreen.mybox.R;

public class Utility {
	public static final String SDCARD_ROOT = Environment.getExternalStorageDirectory().getAbsolutePath();
	public static final String CACHE_ROOT = MyApp.getApplication().getCacheDir().getAbsolutePath();

	private static final String TAG = Utility.class.getName();
	private static final int baseHeight = 1280;
	private static final int baseWidth = 720;

	public static int getBaseHeight() {
		return baseHeight;
	}
	
	public static int getBaseWidth() {
		return baseWidth;
	}

	public static int getScreenWidth() {
		WindowManager windowManager = (WindowManager) MyApp.getApplication().getSystemService(Context.WINDOW_SERVICE);
		DisplayMetrics dm = new DisplayMetrics();
		windowManager.getDefaultDisplay().getMetrics(dm);
		
		return dm.widthPixels;
	}

	public static int getScreenHeight() {
		WindowManager windowManager = (WindowManager) MyApp.getApplication().getSystemService(Context.WINDOW_SERVICE);
		DisplayMetrics dm = new DisplayMetrics();
		windowManager.getDefaultDisplay().getMetrics(dm);
		
		return dm.heightPixels;
	}

	public static float getScreenDensity() {
		WindowManager windowManager = (WindowManager) MyApp.getApplication().getSystemService(Context.WINDOW_SERVICE);
		DisplayMetrics dm = new DisplayMetrics();
		windowManager.getDefaultDisplay().getMetrics(dm);
		
		return dm.density;
	}

	public static int getMaxImageDimension() {
		int height = getScreenHeight();
		int width = getScreenWidth();
		return height > width ? height : width;
	}
	
	public static int getImageDimension() {
		return getMaxImageDimension() / 2;
	}
	
	public static int getSmallImageDimension() {
		return getImageDimension() / 2;
	}

	public static String getDMRPushName(String dmrName) {
		return  getString(R.string.nowpushing_left) + getDeviceFriendlyName(dmrName) + getString(R.string.nowpushing_right);
	}
	
	public static String getDMSToastName(String dmsName) {
		return  getDeviceFriendlyName(dmsName) + " " + getString(R.string.device_online);
	}
	
	public static String getDeviceFriendlyName(String deviceFriendlyName) {
		String friendlyName = deviceFriendlyName;
		int lastIndex = deviceFriendlyName.lastIndexOf(":");
		if (lastIndex > 0) {
			if (deviceFriendlyName.endsWith(":")) {
				friendlyName = deviceFriendlyName.substring(0, lastIndex);
				lastIndex = friendlyName.lastIndexOf(":");
			}
			if (lastIndex > 0) {
				friendlyName = friendlyName.substring(lastIndex + 1);
			}
		}
		
		return friendlyName;
	}

	public static float getScaleWithBaseScreen() {
		int height = getScreenHeight();
		int width = getScreenWidth();
		if (height > width) {
			float heightScale = 1.0f * height / baseHeight;
			float widthScale = 1.0f * width / baseWidth;
			return heightScale < widthScale ? heightScale : widthScale;
		} else {
			float heightScale = 1.0f * width / baseHeight;
			float widthScale = 1.0f * height / baseWidth;
			return heightScale < widthScale ? heightScale : widthScale;
		}
	}
	
	public static float getWidthScaleWithBaseScreen(int width) {
		int h = getScreenHeight();
		int w = getScreenWidth();
		if (h > w) {
			return (1.0f * width * w / baseWidth);
		} else {
			return (1.0f * width * h / baseWidth);
		}
	}

	public static String getString(int resId) {
		return MyApp.getApplication().getString(resId);
	}
	
	public static String[] getStringArray(int resId) {
		return MyApp.getApplication().getResources().getStringArray(resId);
	}
	
	public static void downToast(Toast toast, Context context, int resId){
		downToast(toast, context, context.getString(resId));
	}
	
	public static void downToast(Toast toast, Context context, String msg){
		
		TextView text = new TextView(context);
		text.setText(msg);
		
		LinearLayout layout = new LinearLayout(context.getApplicationContext());  
		layout.setGravity(Gravity.CENTER);
		layout.setBackgroundResource(android.R.drawable.toast_frame);
		layout.addView(text);   
		
		toast.setView(layout);
		toast.setGravity(Gravity.BOTTOM, 0, 100);
		toast.show();
	}

	/**
	 * 
	 * @param unit:TypedValue.COMPLEX_UNIT_PX dip
	 * @param size
	 * @param context
	 * @return
	 */
	public static float getRawSize(int unit, float size, Context context) { 
		Resources r; 

		if (context == null) 
			r = Resources.getSystem(); 
		else 
			r = context.getResources(); 

		return TypedValue.applyDimension(unit, size, r.getDisplayMetrics()); 
	}

	public static CheckResult checkItemURL(PlaylistItem item) {
		CheckResult result = new CheckResult(item, false);
		try {
			HttpURLConnection connection = (HttpURLConnection) new URL(item.getUrl()).openConnection();
			connection.setConnectTimeout(3000);
			connection.setRequestMethod("HEAD");
			result.setReachable(connection.getResponseCode() == HttpURLConnection.HTTP_OK);
		} catch (Exception ex) {
			Log.w(TAG, "check fail, url = " + item.getUrl());
		}

		return result;
	}

	public static boolean checkURL(String url) {
		if (url == null || url.trim().equals("")) {
			return false;
		}

		try {
			HttpURLConnection connection = (HttpURLConnection) new URL(url).openConnection();
			connection.setConnectTimeout(3000);
			connection.setRequestMethod("HEAD");
			return connection.getResponseCode() == HttpURLConnection.HTTP_OK;
		} catch (Exception ex) {
			Log.w(TAG, "check fail, url = " + url);
		}

		return false;
	}

	public static String createMetaData(String title, PlaylistItem.Type type, String url) {
		Item item = null;
		Res res = new Res(new ProtocolInfo("*:*:*:*"), 0l, url);
		switch (type) {
		case AUDIO_LOCAL:
		case AUDIO_REMOTE:
			item = new AudioItem("0", "0", title, "", res);
			break;
		case VIDEO_LOCAL:
		case VIDEO_REMOTE:
			item = new VideoItem("0", "0", title, "", res);
			break;
		case IMAGE_LOCAL:
		case IMAGE_REMOTE:
			item = new ImageItem("0", "0", title, "", res);
			break;
		default:
			break;
		}
		return createMetaData(item);
	}

	public static String createVideoMetaData(String title, String url, String thumbUrl) {
		Res res = new Res(new ProtocolInfo("*:*:*:*"), 0l, url);
		Item item = new VideoItem("0", "0", title, "", res);
		if (thumbUrl != null && thumbUrl.trim().equals(""))
			addObjectAlbumArtProperty(item, thumbUrl);
		return createMetaData(item);
	}

	public static void addObjectAlbumArtProperty(DIDLObject didlobject, String link)
	{
		try {
			URI uri = new URI(link);
			ArrayList arraylist = new ArrayList();
			arraylist.add(new DIDLObject.Property.DLNA.PROFILE_ID(new DIDLAttribute("urn:schemas-dlna-org:metadata-1-0/", "dlna", "PNG_TN")));
			didlobject.addProperty(new DIDLObject.Property.UPNP.ALBUM_ART_URI(uri, arraylist));
		} catch (URISyntaxException e) {
			e.printStackTrace();
		}
	}

	public static String createMetaData(DIDLObject didlObject) {
		if (didlObject != null) {
			DIDLParser ps = new DIDLParser();
			DIDLContent ct = new DIDLContent();

			if (didlObject instanceof Item) {
				ct.addItem((Item) didlObject);
			} else if (didlObject instanceof Container) {
				ct.addContainer((Container) didlObject);
			}

			try {
				return ps.generate(ct);
			} catch (Exception e) {
				return "";
			}
		} else {
			return "";
		}
	}

	public static DIDLContent createDIDL(String MetaData) {
		DIDLParser parser = new DIDLParser(); 
		try {
			return parser.parse(MetaData);
		} catch (Exception e) {
			return null;
		}
	}

	public static MimeType getMimeType(Item item) {
		ProtocolInfo protocolInfo = item.getFirstResource().getProtocolInfo();
		return protocolInfo.getContentFormatMimeType();
	}

	public static class CheckResult {
		private PlaylistItem item;
		private boolean reachable;

		public CheckResult(PlaylistItem item, boolean reachable) {
			this.item = item;
			this.reachable = reachable;
		}

		public PlaylistItem getItem() {
			return item;
		}

		public void setItem(PlaylistItem item) {
			this.item = item;
		}

		public boolean isReachable() {
			return reachable;
		}

		public void setReachable(boolean reachable) {
			this.reachable = reachable;
		}

	}
	
	public static long timeStringToMinute(String s) {
    	if (null == s)
    		return 0;
        String[] split = s.split(":");
        if (split.length == 1) {
        	return 0;
        } else if (split.length == 2) {
        	try{
    			return Integer.parseInt(split[0]);
    		}catch(Exception ex){
    			ex.printStackTrace();
    		}
        } else if (split.length >= 3) {
        	try{
    			long hour = Integer.parseInt(split[0]);
    			long minite = Integer.parseInt(split[1]);

    			return hour * 60 + minite;
    		}catch(Exception ex){
    			ex.printStackTrace();
    		}
        }
        return 0;
    }
	
	public static final byte[] readStreamAsByte(InputStream inputStream) throws MyException
	{
		try {
			ByteArrayOutputStream output = new ByteArrayOutputStream();
			byte[] bytes = new byte[8192];
			int len = -1;
			while ((len = inputStream.read(bytes)) != -1) {
				output.write(bytes, 0, len);
			}	
			inputStream.close();
			output.flush();
			output.close();
			return output.toByteArray();
		} catch (Exception ex) {
			throw new MyException(ex);
		} catch (Error ex) {
			throw new MyException(ex);
		}
	}
	
	public static boolean isNetWork(Context context){
		ConnectivityManager connectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);  
		if (connectivityManager != null){
			NetworkInfo[] info = connectivityManager.getAllNetworkInfo(); 
			if (info != null) {
				for (int i = 0; i < info.length; i++) {
					if (info[i].getState() == NetworkInfo.State.CONNECTED) {
						return true; 
					} 
				} 
			}
		} 
		return false;
	}
}
