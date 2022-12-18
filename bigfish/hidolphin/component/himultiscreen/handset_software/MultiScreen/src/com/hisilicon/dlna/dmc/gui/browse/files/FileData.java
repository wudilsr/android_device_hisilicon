package com.hisilicon.dlna.dmc.gui.browse.files;

import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.InetAddress;
import java.net.URLEncoder;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.teleal.cling.support.contentdirectory.DIDLParser;
import org.teleal.cling.support.model.DIDLContent;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.Res;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.AudioItem;
import org.teleal.cling.support.model.item.ImageItem;
import org.teleal.cling.support.model.item.Item;
import org.teleal.cling.support.model.item.VideoItem;
import org.teleal.common.util.MimeType;

import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem.Type;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.MyApp;

import android.content.ContentResolver;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;

public class FileData {
	private Context mContext;
	public static HashMap<String, List<FileNode>> mGruopMap = new HashMap<String, List<FileNode>>();
	private List<PictureNode> pictures = new ArrayList<PictureNode>();
	private List<ImageItem> imageItems = new ArrayList<ImageItem>();
	private Handler myHandler = new Handler();
	private final static int SCAN_OK = 1;
	private BrowseImageAdapter_New adapter;
	private InetAddress IP;
	private LoadComplete mLoadComplete;
	private String HOST;
	private final String PORT = "38523";

	public FileData(Context context, BrowseImageAdapter_New adapter, LoadComplete mLoadComplete){
		mContext = context;
		this.adapter = adapter;
		try {
			IP = getLocalIpAddress();
			HOST = new StringBuilder("http:/")
			.append(IP)
			.append(":")
			.append(PORT)
			.append("/").toString();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		this.mLoadComplete = mLoadComplete;
	}

	public List<PictureNode> getPictures(){
		return pictures;
	}

	public HashMap<String, List<FileNode>> getFolders(){
		return mGruopMap;
	}

	private Handler mHandler = new Handler(){

		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			switch (msg.what) {
			case SCAN_OK:
				System.out.println("---------SCAN_OK---------");
				if(adapter!=null&&pictures!=null){
					System.out.println("The pictures size is:" + pictures.size());
					adapter.setList(pictures);
					adapter.notifyDataSetChanged();
					mLoadComplete.success();
//					Thread thread = new CreatImageItemsThread();
//					thread.start();
				}
				break;
			}
		}

	};

	public void getData(){
		new Thread(new Runnable() {

			@Override
			public void run() {
				Uri mImageUri = MediaStore.Images.Media.EXTERNAL_CONTENT_URI;
				ContentResolver mContentResolver = mContext.getContentResolver();

				//只查询jpeg和png的图片
				Cursor mCursor = mContentResolver.query(mImageUri, null,
						MediaStore.Images.Media.MIME_TYPE + "=? or "
								+ MediaStore.Images.Media.MIME_TYPE + "=?",
								new String[] { "image/jpeg", "image/png" }, MediaStore.Images.Media.DATE_MODIFIED);

				if(mCursor == null){
					return;
				}
				pictures.clear();
				imageItems.clear();
				mGruopMap.clear();
				while (mCursor.moveToNext()) {
					//获取图片的路径
					String path = mCursor.getString(mCursor
							.getColumnIndex(MediaStore.Images.Media.DATA));

					//获取该图片的父路径名
					String parentName = new File(path).getParentFile().getName();
					PictureNode picNode = new PictureNode();
					picNode.setPath(path);
					picNode.setId(mCursor.getLong(mCursor.getColumnIndex(MediaStore.Images.Media._ID)));
					picNode.setTitle(new File(path).getName());
					picNode.setMimeType(mCursor.getString(mCursor.getColumnIndexOrThrow(MediaStore.Images.Media.MIME_TYPE)));
					picNode.setSize(mCursor.getLong(mCursor.getColumnIndexOrThrow(MediaStore.Images.Media.SIZE)));
					
					if(pictures.size()<=100)
						pictures.add(picNode);
					if(pictures.size()==100)
					{
						//通知Handler扫描图片完成
						mHandler.sendEmptyMessage(SCAN_OK);
					}
					ImageItem it = createImageItem(picNode);
					imageItems.add(it);
					//					adapter.add(createFromDLDIObject(createImageItem(path, count)));
					//根据父路径名将图片放入到mGruopMap中
					if (!mGruopMap.containsKey(parentName)) {
						List<FileNode> chileList = new ArrayList<FileNode>();
						chileList.add(new FileNode(picNode, it));
						
						mGruopMap.put(parentName, chileList);
					} else {
						mGruopMap.get(parentName).add(new FileNode(picNode, it));
					}
				}

				mCursor.close();
			}
		}).start();
		
	}

	private class CreatImageItemsThread extends Thread{

		@Override
		public void run() {
			// TODO Auto-generated method stub
			super.run();
			PlaylistItem playlistItem = null;
			for(ImageItem item:imageItems){
				playlistItem = new PlaylistItem(item);

				playlistItem.setId(item.getId());
				playlistItem.setTitle(item.getTitle());

				String url = HttpServerUtil.getUrlFrom(item);
				playlistItem.setUrl(url);
				playlistItem.setType(Type.IMAGE_LOCAL);
//				boolean isLocal = HttpServerUtil.mediaFromLocal(url);
//				if (isLocal) {
//					playlistItem.setType(Type.IMAGE_LOCAL);
//				} else
//					playlistItem.setType(Type.IMAGE_REMOTE);

//				playlistItem.setMetaData(Utility.createMetaData(item));
				adapter.add(playlistItem);
				playlistItem = null;
			}
		}
		
	}

	private ImageItem createImageItem(String path, int count){
		String decodeUrl=null;
		ImageItem item = new ImageItem();
		item.setId(path);
		item.setTitle(new File(path).getName());
		List<Res> resources = new ArrayList<Res>();
		Res res = new Res();
		if(path.startsWith("/")){
			path = path.replaceFirst("/", "");
		}
		try {
			decodeUrl = URLEncoder.encode(path,"utf-8");
//			decodeUrl = "http:/" + IP + ":38523/" + decodeUrl;
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		res.setValue(decodeUrl);
		resources.add(res);
		item.setResources(resources);
		return item;
	}
	
	private ImageItem createImageItem(PictureNode node){
		long pic_id = node.getId();
		String item_id = HttpServerUtil.makeMediaId(node.getPath());
//		String link = HttpServerUtil.createLinkWithId(item_id);
		String link = HOST + item_id;
//		System.out.println("The link is:" + link);
		Res res = new Res(MimeType.valueOf(node.getMimeType()), node.getSize(), link);
		return new ImageItem(pic_id+"", "0", node.getTitle(), "unkonwn", res);
	} 

	private PlaylistItem createFromDLDIObject(DIDLObject object) {
		PlaylistItem item = new PlaylistItem(object);

		item.setId(object.getId());
		item.setTitle(object.getTitle());

		String url = HttpServerUtil.getUrlFrom(object);
		item.setUrl(url);

		boolean isLocal = HttpServerUtil.mediaFromLocal(url);
		if (isLocal) {
			item.setType(Type.IMAGE_LOCAL);
		} else
			item.setType(Type.IMAGE_REMOTE);

		item.setMetaData(Utility.createMetaData(object));

		return item;
	}

	private InetAddress getLocalIpAddress() throws UnknownHostException {
		WifiManager wifiManager = (WifiManager) mContext.getSystemService(mContext.WIFI_SERVICE);
		WifiInfo wifiInfo = wifiManager.getConnectionInfo();
		int ipAddress = wifiInfo.getIpAddress();
		return InetAddress.getByName(String.format("%d.%d.%d.%d",
				(ipAddress & 0xff), (ipAddress >> 8 & 0xff),
				(ipAddress >> 16 & 0xff), (ipAddress >> 24 & 0xff)));
	}
	
	public interface LoadComplete{
		public void success();
	}
}
