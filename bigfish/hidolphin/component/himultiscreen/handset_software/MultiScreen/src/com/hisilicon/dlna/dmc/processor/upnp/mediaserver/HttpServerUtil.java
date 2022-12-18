package com.hisilicon.dlna.dmc.processor.upnp.mediaserver;

import java.io.UnsupportedEncodingException;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.URL;
import java.net.URLEncoder;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.RemoteDevice;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.Res;

import android.database.Cursor;
import android.net.Uri;
import android.provider.MediaStore;

import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.MyApp;
import com.hisilicon.multiscreen.mybox.R;


public class HttpServerUtil {
	public final static String LOOP = "127.0.0.1";
	public static String HOST = LOOP;
	public static int PORT = 38523;

	public static void updateHostAddress(NetworkInterface ni) {
		HOST = getHostAddressFrom(ni);
	}
	
	/**
	 * NetworkInterface 接口中获取HOST地址
	 * 
	 */
	public static String getHostAddressFrom(NetworkInterface ni) {
		if (ni == null)
			return LOOP;
		List<InetAddress> inets = Collections.list(ni.getInetAddresses());
		for (InetAddress inet : inets) {
			if (inet instanceof Inet4Address) {
				return inet.getHostAddress();
			}
		}
		return LOOP;
	}
	
	public static String createLinkWithId(String id) {
		return new StringBuilder("http://")
		.append(HOST)
		.append(":")
		.append(PORT)
		.append("/")
		.append(id).toString();
	}
	
	public static String makeMediaId(String path) {
		if (null == path)
			return null;
		
		String uriPath = path;
		if (path.startsWith("/"))
			uriPath = path.substring(1);
		try {
			return URLEncoder.encode(uriPath, "utf-8");
		} catch (Exception e) {
			e.printStackTrace();
		}
		return uriPath;
	}
	
	public static boolean isSTBDMR(Device device) {
		if (device instanceof RemoteDevice)
		{
			URL descriptorURL = ((RemoteDevice) device).getIdentity().getDescriptorURL();

			if (descriptorURL.getHost().equals(MyApp.getSTBIP()))
			{
				return true;
			}
		}
		return false;
	}
	
	public static boolean isSTBMultiRoom(Device device) {
		if (device instanceof RemoteDevice)
		{
			URL descriptorURL = ((RemoteDevice) device).getIdentity().getDescriptorURL();

			if (descriptorURL.getHost().equals(MyApp.getSTBIP()) && device.getDetails().getFriendlyName().contains("HiMultiRoom"))
			{
				return true;
			}
		}
		return false;
	}
	
	public static boolean isRemoteMultiRoom(Device device) {
		if (device instanceof RemoteDevice)
		{
			if (device.getDetails().getFriendlyName().contains("HiMultiRoom"))
			{
				return true;
			}
		}
		return false;
	}

	public static boolean isImage(String title) {
		String images[] = Utility.getStringArray(R.array.dms_image_array);
		for (String image : images) {
			if (image.equalsIgnoreCase(title))
				return true;
		}
		return false;
	}
	
	public static boolean isVideo(String title) {
		String videos[] = Utility.getStringArray(R.array.dms_video_array);
		for (String video : videos) {
			if (video.equalsIgnoreCase(title))
				return true;
		}
		return false;
	}
	
	public static boolean isMusic(String title) {
		String musics[] = Utility.getStringArray(R.array.dms_music_array);
		for (String music : musics) {
			if (music.equalsIgnoreCase(title))
				return true;
		}
		return false;
	}
	
	public static boolean isLiveTV(String title) {
		if ("LiveTV".equalsIgnoreCase(title))
				return true;
		return false;
	}
	
	public static boolean isAllImages(String title) {
		List<String> list = Arrays.asList(Utility.getStringArray(R.array.dms_allimage_array));
		if (list.contains(title))
			return true;
		return false;
	}
	
	public static boolean isAllVideos(String title) {
		List<String> list = Arrays.asList(Utility.getStringArray(R.array.dms_allvideo_array));
		if (list.contains(title))
			return true;
		return false;
	}
	
	public static boolean isAllMusics(String title) {
		List<String> list = Arrays.asList(Utility.getStringArray(R.array.dms_allmusic_array));
		if (list.contains(title))
			return true;
		return false;
	}
	
	public static boolean isCamera(String title) {
		if (Utility.getString(R.string.camera).equals(title))
			return true;
		return false;
	}
	
	public static boolean mediaFromLocal(String url) {
		if (url == null)
			return false;
		
		Uri uri = Uri.parse(url);
		
		return mediaFromLocal(uri);
	}
	
	public static boolean mediaFromLocal(Uri uri) {
		return loopHost() || uriFromLoop(uri) || uriFromLocal(uri);
	}

	private static boolean loopHost() {
		return LOOP.equals(HttpServerUtil.HOST);
	}
	
	private static boolean uriFromLoop(Uri uri) {
		return uri != null && LOOP.equals(uri.getHost()) && HttpServerUtil.PORT == uri.getPort();
	}

	private static boolean uriFromLocal(Uri uri) {
		return uri != null && HttpServerUtil.HOST.equals(uri.getHost()) && HttpServerUtil.PORT == uri.getPort();
	}

	public static String getUrlFrom(DIDLObject didlObject) {
		List<Res> reses = didlObject.getResources();;
		return reses.isEmpty() ? "" : reses.get(0).getValue();
	}
	
	public static String[] queryImageThumbIdAndData(String[] selectionArgs) {
		Uri uri = MediaStore.Images.Thumbnails.EXTERNAL_CONTENT_URI;
		String[] projection = new String[]{
				MediaStore.Images.Thumbnails._ID,
				MediaStore.Images.Thumbnails.DATA,
		};
		String selection = MediaStore.Images.Thumbnails.IMAGE_ID + "=?";
		String[] str = queryThumbnail(uri, projection, selection, selectionArgs);
		return str;
	}
	
	public static String[] queryVideoThumbIdAndData(String[] selectionArgs) {
		Uri uri = MediaStore.Video.Thumbnails.EXTERNAL_CONTENT_URI;
		String[] projection = new String[]{
				MediaStore.Video.Thumbnails._ID,
				MediaStore.Video.Thumbnails.DATA,
		};
		String selection = MediaStore.Video.Thumbnails.VIDEO_ID + "=?";
		String[] str = queryThumbnail(uri, projection, selection, selectionArgs);
		return str;
	}
	
	public static String[] queryAudioThumbIdAndData(String[] selectionArgs) {
		Uri uri = MediaStore.Audio.Albums.EXTERNAL_CONTENT_URI;
		String[] projection = new String[]{
				MediaStore.Audio.Albums._ID,
				MediaStore.Audio.Albums.ALBUM_ART,
		};
		String selection = MediaStore.Audio.Albums._ID + "=?";
		String[] str = queryThumbnail(uri, projection, selection, selectionArgs);
		return str;
	}
	
	public static String[] queryThumbnail(Uri uri, String[] projection, String selection, String[] selectionArgs) {
		Cursor thumbCursor = MyApp.getResolver().query(uri, projection, selection, selectionArgs, null);
		String[] str = new String[2];
		if (thumbCursor != null && thumbCursor.getCount() != 0) {
			thumbCursor.moveToFirst();
			
			int columnId = thumbCursor.getColumnIndex(projection[0]);
			int columnData = thumbCursor.getColumnIndex(projection[1]);
			str[0] = thumbCursor.getLong(columnId) + "";
			str[1] = thumbCursor.getString(columnData);
		}
		if(null != thumbCursor)
			thumbCursor.close();
		return str;
	}
}
