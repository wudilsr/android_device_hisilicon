package com.hisilicon.dlna.dmc.processor.upnp.mediaserver;

import java.io.File;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.teleal.cling.model.ModelUtil;
import org.teleal.cling.support.model.DIDLAttribute;
import org.teleal.cling.support.model.DIDLContent;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.PersonWithRole;
import org.teleal.cling.support.model.ProtocolInfo;
import org.teleal.cling.support.model.Res;
import org.teleal.cling.support.model.WriteStatus;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.AudioItem;
import org.teleal.cling.support.model.item.ImageItem;
import org.teleal.cling.support.model.item.Item;
import org.teleal.cling.support.model.item.VideoItem;
import org.teleal.common.util.MimeType;

import android.database.Cursor;
import android.net.Uri;
import android.provider.MediaStore;
import android.provider.MediaStore.Audio.GenresColumns;
import android.util.Log;

import com.hisilicon.dlna.dmc.gui.activity.AppPreference;
import com.hisilicon.dlna.dmc.processor.impl.PlaylistManager;
import com.hisilicon.dlna.dmc.processor.model.LocalAudio;
import com.hisilicon.dlna.dmc.processor.model.LocalPhoto;
import com.hisilicon.dlna.dmc.processor.model.LocalVideo;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.utility.Utility;
import com.hisilicon.multiscreen.mybox.MyApp;
import com.hisilicon.multiscreen.mybox.R;

public class ContentTree {

	public final static String ROOT_ID = "0";
	public final static String VIDEO_ID = "1";
	public final static String AUDIO_ID = "2";
	public final static String IMAGE_ID = "3";
	public final static String ALL_VIDEO_ID = "4";
	public final static String ALL_AUDIO_ID = "5";
	public final static String ALL_IMAGE_ID = "6";
	public final static String VIDEO_FOLDER_ID = "7";
	public final static String AUDIO_FOLDER_ID = "8";
	public final static String IMAGE_FOLDER_ID = "9";
	public final static String PLAYLIST_ID = "10";
	public final static String VIDEO_FOLDER_PREFIX = "video_folder_";
	public final static String AUDIO_FOLDER_PREFIX = "audio_folder_";
	public final static String IMAGE_FOLDER_PREFIX = "image_folder_";
	
	private static HashMap<String, ContentNode> contentMap = new HashMap<String, ContentNode>();

	private static ContentNode rootNode = createRootNode();
	
	private static List<LocalPhoto> photos = new ArrayList<LocalPhoto>();
	private static List<LocalVideo> videos = new ArrayList<LocalVideo>();
	private static List<LocalAudio> audios = new ArrayList<LocalAudio>();

	private static volatile boolean isStopLoading = false;

	public static void clear()
	{
		rootNode = createRootNode();
	}

	protected static ContentNode createRootNode() {
		// create root container
		contentMap.clear();
		Container root = new Container();
		root.setClazz(new DIDLObject.Class("object.container"));
		root.setId(ROOT_ID);
		root.setParentID("-1");
		root.setTitle(AppPreference.getDLNACreater() + " root directory");
		root.setCreator(AppPreference.getDLNACreater());
		root.setRestricted(true);
		root.setSearchable(true);
		root.setWriteStatus(WriteStatus.NOT_WRITABLE);
		root.setChildCount(0);
		ContentNode rootNode = new ContentNode(ROOT_ID, root);
		contentMap.put(ROOT_ID, rootNode);
		
		addRootContainer(rootNode);
		
		return rootNode;
	}
	
	private static void addRootContainer(ContentNode rootNode) {
		Container imagesContainer = createImagesRootContainer();
		rootNode.getContainer().addContainer(imagesContainer);
		rootNode.getContainer().setChildCount(rootNode.getContainer().getChildCount() + 1);
		
		Container videosContainer = createVideosRootContainer();
		rootNode.getContainer().addContainer(videosContainer);
		rootNode.getContainer().setChildCount(rootNode.getContainer().getChildCount() + 1);
		
		Container audiosContainer = createAudiosRootContainer();
		rootNode.getContainer().addContainer(audiosContainer);
		rootNode.getContainer().setChildCount(rootNode.getContainer().getChildCount() + 1);
	}
	
	private static Container createImagesRootContainer() {
		Container imageContainer = new Container(ContentTree.IMAGE_ID,
				ContentTree.ROOT_ID, Utility.getString(R.string.image), AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container.storageFolder"), 0);
		imageContainer.setRestricted(true);
		imageContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		
		ContentTree.addNode(ContentTree.IMAGE_ID, new ContentNode(ContentTree.IMAGE_ID, imageContainer));
		
		addImageRootContainer(imageContainer);
				
		return imageContainer;
	}
	
	private static void addImageRootContainer(Container container) {
		Container imagesContainer = getOrCreateImageFolderLevelContainer();
		container.addContainer(imagesContainer);
		container.setChildCount(container.getChildCount() + 1);
		
		Container allImagesFolderContainer = createAllImageLevelContainer();
		container.addContainer(allImagesFolderContainer);
		container.setChildCount(container.getChildCount() + 1);
	}
	
	/**
	 * 
	 * 获取或创建图片的“文件夹”目录
	 */
	private static Container getOrCreateImageFolderLevelContainer() {
		Container imageContainer = getContainer(IMAGE_FOLDER_ID);
		if (imageContainer != null)
			return imageContainer;
		imageContainer = new Container(ContentTree.IMAGE_FOLDER_ID,
				ContentTree.IMAGE_ID, Utility.getString(R.string.folder), AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container.storageFolder"), 0);
		imageContainer.setRestricted(true);
		imageContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		
		ContentTree.addNode(ContentTree.IMAGE_FOLDER_ID, new ContentNode(ContentTree.IMAGE_FOLDER_ID, imageContainer));
		
		return imageContainer;
	}
	
	/**
	 * 
	 * 创建“所有图片”目录
	 */
	private static Container createAllImageLevelContainer() {
		Container allPhotosContainer = new Container(ContentTree.ALL_IMAGE_ID,
				ContentTree.IMAGE_ID, Utility.getString(R.string.allimage), AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container"), 0);
		allPhotosContainer.setRestricted(true);
		allPhotosContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		ContentTree.addNode(ContentTree.ALL_IMAGE_ID, new ContentNode(ContentTree.ALL_IMAGE_ID, allPhotosContainer));
		return allPhotosContainer;
	}
	
	private static Container createVideosRootContainer() {
		Container videoContainer = new Container();
		videoContainer.setClazz(new DIDLObject.Class("object.container"));
		videoContainer.setId(ContentTree.VIDEO_ID);
		videoContainer.setParentID(ContentTree.ROOT_ID);
		videoContainer.setTitle(Utility.getString(R.string.video));
		videoContainer.setRestricted(true);
		videoContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		videoContainer.setChildCount(0);
		ContentTree.addNode(ContentTree.VIDEO_ID, new ContentNode(ContentTree.VIDEO_ID, videoContainer));
		
		addVideoRootContainer(videoContainer);
		
		return videoContainer;
	}
	
	private static void addVideoRootContainer(Container container) {
		Container videosContainer = getOrCreateVideoFolderLevelContainer();
		container.addContainer(videosContainer);
		container.setChildCount(container.getChildCount() + 1);
		
		Container allVideosFolderContainer = createAllVideoLevelContainer();
		container.addContainer(allVideosFolderContainer);
		container.setChildCount(container.getChildCount() + 1);
	}
	
	/**
	 * 
	 * 获取或创建视频的“文件夹”目录
	 */
	private static Container getOrCreateVideoFolderLevelContainer() {
		Container videoContainer = getContainer(VIDEO_FOLDER_ID);
		if (videoContainer != null)
			return videoContainer;
		videoContainer = new Container(ContentTree.VIDEO_FOLDER_ID,
				ContentTree.VIDEO_ID, Utility.getString(R.string.folder), AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container.storageFolder"), 0);
		videoContainer.setRestricted(true);
		videoContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		
		ContentTree.addNode(ContentTree.VIDEO_FOLDER_ID, new ContentNode(ContentTree.VIDEO_FOLDER_ID, videoContainer));
		
		return videoContainer;
	}
	
	/**
	 * 
	 * 创建“所有视频”目录
	 */
	private static Container createAllVideoLevelContainer() {
		Container allVideosContainer = new Container(ContentTree.ALL_VIDEO_ID,
				ContentTree.VIDEO_ID, Utility.getString(R.string.allvideo), AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container"), 0);
		allVideosContainer.setRestricted(true);
		allVideosContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		ContentTree.addNode(ContentTree.ALL_VIDEO_ID, new ContentNode(ContentTree.ALL_VIDEO_ID, allVideosContainer));
		return allVideosContainer;
	}
	
	private static Container createAudiosRootContainer() {
		Container audioContainer = new Container(ContentTree.AUDIO_ID,
				ContentTree.ROOT_ID, Utility.getString(R.string.music), AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container"), 0);
		audioContainer.setRestricted(true);
		audioContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		ContentTree.addNode(ContentTree.AUDIO_ID, new ContentNode(ContentTree.AUDIO_ID, audioContainer));
		
		addAudioRootContainer(audioContainer);
		
		return audioContainer;
	}
	
	private static void addAudioRootContainer(Container container) {
		Container audiosContainer = getOrCreateMusicFolderLevelContainer();
		container.addContainer(audiosContainer);
		container.setChildCount(container.getChildCount() + 1);
		
		Container allAudiosFolderContainer = createAllMusicLevelContainer();
		container.addContainer(allAudiosFolderContainer);
		container.setChildCount(container.getChildCount() + 1);
	}
	
	/**
	 * 
	 * 获取或创建音乐的“文件夹”目录
	 */
	private static Container getOrCreateMusicFolderLevelContainer() {
		Container audioContainer = getContainer(AUDIO_FOLDER_ID);
		if (audioContainer != null)
			return audioContainer;
		Container imageContainer = new Container(AUDIO_FOLDER_ID,
				AUDIO_ID, Utility.getString(R.string.folder), AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container.storageFolder"), 0);
		imageContainer.setRestricted(true);
		imageContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		
		ContentTree.addNode(AUDIO_FOLDER_ID, new ContentNode(AUDIO_FOLDER_ID, imageContainer));
		
		return imageContainer;
	}
	
	/**
	 * 
	 * 创建“所有音乐”目录
	 */
	private static Container createAllMusicLevelContainer() {
		Container allAudioContainer = new Container(ALL_AUDIO_ID,
				AUDIO_ID, Utility.getString(R.string.allmusic), AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container"), 0);
		allAudioContainer.setRestricted(true);
		allAudioContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		ContentTree.addNode(ALL_AUDIO_ID, new ContentNode(ALL_AUDIO_ID, allAudioContainer));
		return allAudioContainer;
	}

	public static ContentNode getRootNode() {
		return rootNode;
	}

	public static ContentNode getNode(String id) {
		if( contentMap.containsKey(id)) 
			return contentMap.get(id);
		return null;
	}

	public static boolean hasNode(String id) {
		return contentMap.containsKey(id);
	}

	public static void addNode(String id, ContentNode node) {
		contentMap.put(id, node);
	}

	public static Container getContainer(String id) {
		ContentNode contentNode = ContentTree.getNode(id);
		if (contentNode != null)
			return contentNode.getContainer();
		return null;
	}

	public static void initAllMedia() throws MediaInitException
	{
		isStopLoading = false;

		try
		{
			initPhotos();
			initVideos();
			initAudios();
		}
		catch (MediaInitException ex)
		{
			photos.clear();
			videos.clear();
			audios.clear();

			throw new MediaInitException(ex);
		}
	}
	
	public static void initAudioAndMusic()throws MediaInitException
	{
		isStopLoading = false;

		try
		{
			initPhotos();
			initVideos();
			initAudios();
		}
		catch (MediaInitException ex)
		{
			photos.clear();
			videos.clear();
			audios.clear();

			throw new MediaInitException(ex);
		}
	}
	
	public static void initPhotos() throws MediaInitException {
		Uri uri = android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI;
		try
		{
			createPhotos(uri);
		}
		catch(MediaInitException exception)
		{
			throw new MediaInitException(exception);
		}
		catch(Exception exception)
		{
			Log.w("photo init", new StringBuilder().append("Could not load phone photos from ").append(uri.toString()).toString(), exception);
		}
	}
	
	public static void createPhotos(Uri uri) throws MediaInitException {
		photos.clear();
		
		Calendar calendar = Calendar.getInstance();
		
		String[] imageColumns = {MediaStore.Images.Media._ID,
				MediaStore.Images.Media.TITLE, MediaStore.Images.Media.DATA,
				MediaStore.Images.Media.MIME_TYPE, MediaStore.Images.Media.SIZE,
				MediaStore.Images.Media.DISPLAY_NAME,
				MediaStore.Images.Media.DATE_ADDED};
		Cursor cursor = MyApp.getResolver().query(uri, imageColumns, null, null, MediaStore.Images.Media.DATE_TAKEN + " COLLATE LOCALIZED DESC");
		if (cursor.moveToFirst()) {
			do {
				whetherStopLoading();

				long id = cursor.getLong(cursor
								.getColumnIndex(MediaStore.Images.Media._ID));
				String title = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Images.Media.TITLE));
				String displayName = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Images.Media.DISPLAY_NAME));
				String creator = "unkown";
				String filePath = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Images.Media.DATA));
				String mimeType = cursor
						.getString(cursor
								.getColumnIndexOrThrow(MediaStore.Images.Media.MIME_TYPE));
				long size = cursor.getLong(cursor
						.getColumnIndexOrThrow(MediaStore.Images.Media.SIZE));
				
				LocalPhoto photo = new LocalPhoto();
				photo.setId(id);
				photo.setTitle(title);
				photo.setMimeType(mimeType);
				photo.setPath(filePath);
				photo.setSize(size);
				File file = new File(photo.getPath());
				if(file.exists() && file.isFile() && file.getParentFile() != null) {
					photo.setDateCreated(file.lastModified());
					photo.setFolder(file.getParentFile().getName());
					
					calendar.setTimeInMillis(photo.getDateCreated());
					
					photo.setYear(String.valueOf(calendar.get(Calendar.YEAR)));
					photo.setMonth(String.format("%02d", calendar.get(Calendar.MONTH)));
					photo.setDay(String.valueOf(calendar.get(Calendar.DAY_OF_MONTH)));
				}
				else{
					photo.setYear("1970");
					photo.setMonth("01");
					photo.setFolder("[Unknown]");

				}

				/**
				String[] thumbnail = HttpServerUtil.queryImageThumbIdAndData(new String[] {id + ""});
				
				if (thumbnail[1] != null)
				{
					File thumbnailFile  = new File(thumbnail[1]);
					if(thumbnailFile.exists() && thumbnailFile.isFile())
					{
						photo.setThumbPath(thumbnail[1]);
						try {
							photo.setThumbId(Long.parseLong(thumbnail[0]));
						} catch (Exception e) {
						}
					}
				}
				*/
				
				createPhotoAlbumDir(photo);
				createAllPhotoDir(photo);
				photos.add(photo);
			} while (cursor.moveToNext());
		}
	}
	
	public static void initVideos() throws MediaInitException {
		Uri uri = android.provider.MediaStore.Video.Media.EXTERNAL_CONTENT_URI;
		try
		{
			createVideos(uri);
		}
		catch(MediaInitException exception)
		{
			throw new MediaInitException(exception);
		}
		catch(Exception exception)
		{
			Log.w("audio init", (new StringBuilder()).append("Could not load phone audios from ").append(uri.toString()).toString(), exception);
		}
	}
	
	private static void createVideos(Uri uri) throws MediaInitException {
		videos.clear();
		
		Calendar calendar = Calendar.getInstance();
		
		String[] videoColumns = {MediaStore.Video.Media._ID,
				MediaStore.Video.Media.TITLE, MediaStore.Video.Media.DATA,
				MediaStore.Video.Media.ARTIST,
				MediaStore.Video.Media.MIME_TYPE, MediaStore.Video.Media.SIZE,
				MediaStore.Video.Media.DURATION,
				MediaStore.Video.Media.RESOLUTION,
				MediaStore.Video.Media.DISPLAY_NAME,
				MediaStore.Video.Media.DATE_ADDED};
		Cursor cursor = MyApp.getResolver().query(uri, videoColumns, null, null, MediaStore.Video.Media.DATE_TAKEN + " COLLATE LOCALIZED DESC");
		if (cursor.moveToFirst()) {
			do {
				whetherStopLoading();

				long id = cursor.getLong(cursor
								.getColumnIndex(MediaStore.Video.Media._ID));
				String title = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Video.Media.TITLE));
				String displayName = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Video.Media.DISPLAY_NAME));
				String creator = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Video.Media.ARTIST));
				String filePath = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Video.Media.DATA));
				String mimeType = cursor
						.getString(cursor
								.getColumnIndexOrThrow(MediaStore.Video.Media.MIME_TYPE));
				long size = cursor.getLong(cursor
						.getColumnIndexOrThrow(MediaStore.Video.Media.SIZE));
				long duration = cursor
						.getLong(cursor
								.getColumnIndexOrThrow(MediaStore.Video.Media.DURATION));
				String resolution = cursor
						.getString(cursor
								.getColumnIndexOrThrow(MediaStore.Video.Media.RESOLUTION));

				LocalVideo localVideo = new LocalVideo();
				localVideo.setId(id);
				localVideo.setTitle(title);
				localVideo.setMimeType(mimeType);
				localVideo.setArtist(creator);
				localVideo.setPath(filePath);
				localVideo.setSize(size);
				localVideo.setResolution(resolution);
				localVideo.setDuration(duration);
				File file = new File(localVideo.getPath());
				if(file.exists() && file.isFile() && file.getParentFile() != null) {
					localVideo.setDateCreated(file.lastModified());
					localVideo.setFolder(file.getParentFile().getName());
					
					calendar.setTimeInMillis(localVideo.getDateCreated());
					localVideo.setYear(String.valueOf(calendar.get(Calendar.YEAR)));
					int mon = calendar.get(Calendar.MONTH);
					String month = String.valueOf(mon);
					if(mon < 9){
						month = "0" + mon;
					}
					localVideo.setMonth(month);
					localVideo.setDay(String.valueOf(calendar.get(Calendar.DAY_OF_MONTH)));
				}
				else {
					if(localVideo.getYear() == null)
						localVideo.setYear("1970");
					if(localVideo.getMonth() == null)
						localVideo.setMonth("01");
					if(localVideo.getFolder() == null)
						localVideo.setFolder("[Unknown]");

				}

				String[] thumbnail = HttpServerUtil.queryVideoThumbIdAndData(new String[] {id + ""});

				if (thumbnail[1] != null)
				{
					 File thumbnailFile  = new File(thumbnail[1]);
					 if(thumbnailFile.exists() && thumbnailFile.isFile())
					 {
						 localVideo.setThumbPath(thumbnail[1]);
						 try {
							 localVideo.setThumbId(Long.parseLong(thumbnail[0]));
						 } catch (Exception e) {
						 }
					 }
				}
				
				createVideoAlbumDir(localVideo);
				createAllVideoDir(localVideo);
				videos.add(localVideo);
			} while (cursor.moveToNext());
		}
	}
	
	public static void initAudios() throws MediaInitException {
		Uri uri = android.provider.MediaStore.Audio.Media.EXTERNAL_CONTENT_URI;
		try
		{
			createAudios(uri);
		}
		catch(MediaInitException exception)
		{
			throw new MediaInitException(exception);
		}
		catch(Exception exception)
		{
			Log.w("audio init", (new StringBuilder()).append("Could not load phone audios from ").append(uri.toString()).toString(), exception);
		}
	}
	
	private static void createAudios(Uri uri) throws MediaInitException {
		audios.clear();

		String[] audioColumns = {MediaStore.Audio.Media._ID,
				MediaStore.Audio.Media.TITLE, MediaStore.Audio.Media.DATA,
				MediaStore.Audio.Media.ARTIST,
				MediaStore.Audio.Media.MIME_TYPE, MediaStore.Audio.Media.SIZE,
				MediaStore.Audio.Media.DURATION, MediaStore.Audio.Media.ALBUM,
				MediaStore.Audio.Media.ALBUM_ID, MediaStore.Audio.Media.DISPLAY_NAME,
				MediaStore.Audio.Media.DATE_ADDED};
		Cursor cursor = MyApp.getResolver().query(uri, audioColumns, null, null, MediaStore.Audio.Media.DATE_ADDED + " COLLATE LOCALIZED DESC");
		if (cursor.moveToFirst()) {
			do {
				whetherStopLoading();

				long id = cursor.getLong(cursor
								.getColumnIndex(MediaStore.Audio.Media._ID));
				String title = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Audio.Media.TITLE));
				String displayName = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Audio.Media.DISPLAY_NAME));
				String creator = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Audio.Media.ARTIST));
				String filePath = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Audio.Media.DATA));
				String mimeType = cursor
						.getString(cursor
								.getColumnIndexOrThrow(MediaStore.Audio.Media.MIME_TYPE));
				long size = cursor.getLong(cursor
						.getColumnIndexOrThrow(MediaStore.Audio.Media.SIZE));
				long duration = cursor
						.getLong(cursor
								.getColumnIndexOrThrow(MediaStore.Audio.Media.DURATION));
				String album = cursor.getString(cursor
						.getColumnIndexOrThrow(MediaStore.Audio.Media.ALBUM));
				long album_id = cursor.getLong(cursor
								.getColumnIndex(MediaStore.Audio.Media.ALBUM_ID));

				LocalAudio localAudio = new LocalAudio();
				localAudio.setId(id);
				localAudio.setTitle(title);
				localAudio.setMimeType(mimeType);
				localAudio.setPath(filePath);
				localAudio.setSize(size);
				localAudio.setDuration(duration);
				localAudio.setArtist(creator);
				localAudio.setAlbum(album);
				localAudio.setAlbumId(album_id);
				File file = new File(localAudio.getPath());
				if(file.exists() && file.isFile() && file.getParentFile() != null) {
					localAudio.setFolder(file.getParentFile().getName());
				} else {
					localAudio.setFolder("[Unknown]");
				}
				
				String genres = getGenres(id);
				localAudio.setGenre(genres);
				
				String albumArtPath = getAlbumArt((int) album_id);
				if (albumArtPath != null ) {
					File albumArtFile = new File(albumArtPath);
					if(albumArtFile.exists() && albumArtFile.isFile()) {
						localAudio.setAlbumArt(albumArtPath);
					}
				}
				
				createAudioAlbumDir(localAudio);
				createAllAudioDir(localAudio);
				audios.add(localAudio);
			} while (cursor.moveToNext());
		}
	}
	
	public static String getGenres(long audioId){
		Uri uri = Uri.parse("content://media/external/audio/media/" + audioId+ "/genres");
		Cursor c = MyApp.getResolver().query(uri, new String[]{android.provider.MediaStore.Audio.GenresColumns.NAME}, null, null, null);
		String genre = null;
		if(c.moveToFirst()){
			genre = c.getString(c.getColumnIndex(GenresColumns.NAME));
		}
		if (c != null)
			c.close();
		c = null;
		return genre;
	}
	
	private static String getAlbumArt(int albumid) {
		String strAlbums = "content://media/external/audio/albums";
		String[] projection = new String[] {android.provider.MediaStore.Audio.AlbumColumns.ALBUM_ART };
		Cursor cur = MyApp.getResolver().query(Uri.parse(strAlbums + "/" + Integer.toString(albumid)),
				projection, null, null, null);
		String strPath = null;
		if (cur.getCount() > 0 && cur.getColumnCount() > 0) {
			cur.moveToNext();
			strPath = cur.getString(0);
		}
		if (cur != null)
			cur.close();
		cur = null;
		return strPath;
	}
	
	public static void initPlaylist() {
		List<PlaylistItem> playlistItems = PlaylistManager.getAllPlaylistItem();
		System.out.println("The playlistItems size is:" + playlistItems.size());
		Container playlistContainer = getOrCreatePlaylistContainer();
		for (PlaylistItem playlistItem : playlistItems) {
			try {
				DIDLContent didlObject = Utility.createDIDL(playlistItem.getMetaData());
				Item item = didlObject.getItems().get(0);
				Res res = item.getFirstResource();
				if (playlistItem.fromLocalType()) {
					res.setValue(playlistItem.getUrl());
				}
				playlistContainer.addItem(item);
				playlistContainer.setChildCount(playlistContainer.getChildCount() + 1);
			} catch (Exception ex) {
			}
		}
	}
	
	private static Container getOrCreatePlaylistContainer() {
		Container playlistContainer = getContainer(PLAYLIST_ID);
		if (playlistContainer != null)
			return playlistContainer;
		playlistContainer = new Container(PLAYLIST_ID,
				AUDIO_FOLDER_ID, Utility.getString(R.string.playlist), AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container.storageFolder"), 0);
		playlistContainer.setRestricted(true);
		playlistContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		
		ContentTree.addNode(PLAYLIST_ID, new ContentNode(PLAYLIST_ID, playlistContainer));
		
		Container audioFolder = getOrCreateMusicFolderLevelContainer();
		audioFolder.addContainer(playlistContainer);
		audioFolder.setChildCount(audioFolder.getChildCount() + 1);
		return playlistContainer;
	}
	
	public static void createPhotosAlbumsDir() throws MediaInitException {
		isStopLoading = false;

		Iterator<LocalPhoto> it = photos.iterator();
		System.out.println("Come into createPhotosAlbumsDir start--><");
		while(it.hasNext()) {
			whetherStopLoading();

			LocalPhoto localPhoto = it.next();
			createPhotoAlbumDir(localPhoto);
//			createAllPhotoDir(localPhoto);
		}
		System.out.println("Come into createPhotosAlbumsDir end--><");
	}

	public static void createAllPhotoDir(LocalPhoto localPhoto) {
		Container allPhotosContainer = getOrAddNewAllImageFolderContainer();
		
		createPhoto(allPhotosContainer, localPhoto);
	}
	
	private static Container getOrAddNewAllImageFolderContainer() {
		Container folderContainer = getContainer(ALL_IMAGE_ID);
		if (folderContainer != null)
			return folderContainer;
		
		Container container = createAllImageLevelContainer();
		
		Container imagesContainer = getNode(IMAGE_ID).getContainer();
		if (imagesContainer == null)
			imagesContainer = createImagesRootContainer();
		imagesContainer.addContainer(container);
		imagesContainer.setChildCount(imagesContainer.getChildCount() + 1);
		
		return container;
	}
	
	private static void createPhotoAlbumDir(LocalPhoto localPhoto) {
		String folderStr = localPhoto.getFolder();
		String folder_id = IMAGE_FOLDER_PREFIX + folderStr;
		
		Container folderContainer = getOrAddNewImageFolderContainer(folder_id, folderStr);
		
		createPhoto(folderContainer, localPhoto);
	}

	private static void createPhoto(Container folderContainer, LocalPhoto localPhoto) {
		long photo_id = localPhoto.getId();
		String item_id = HttpServerUtil.makeMediaId(localPhoto.getPath());
		String link = HttpServerUtil.createLinkWithId(item_id);

		Res res = new Res(MimeType.valueOf(localPhoto.getMimeType()), localPhoto.getSize(), link);

		ImageItem imageItem = new ImageItem(photo_id + "", folderContainer.getId(), localPhoto.getTitle(), "unkonwn", res);

		String thumb_id = HttpServerUtil.makeMediaId(localPhoto.getThumbPath());
		if (null != thumb_id) {
			String thumbLink = HttpServerUtil.createLinkWithId(thumb_id);
			addObjectAlbumArtProperty(imageItem, thumbLink);
		}

		folderContainer.addItem(imageItem);
		folderContainer.setChildCount(folderContainer.getChildCount() + 1);
		ContentTree.addNode(localPhoto.getPath() + "", new ContentNode(localPhoto.getPath() + "", imageItem, localPhoto.getPath()));
	}

	private static Container getOrAddNewImageFolderContainer(String id, String title) {
		Container folderContainer = getContainer(id);
		if (folderContainer != null)
			return folderContainer;
		
		return addNewImageFolderContainer(id, title);
	}

	private static Container addNewImageFolderContainer(String id, String title) {
		Container folderContainer = new Container(id,
				ContentTree.IMAGE_FOLDER_ID, title, AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container.storageFolder"), 0);
		folderContainer.setRestricted(true);
		folderContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		ContentTree.addNode(id, new ContentNode(id, folderContainer));
		
		Container imageContainer = ContentTree.getNode(IMAGE_FOLDER_ID).getContainer();
		imageContainer.addContainer(folderContainer);
		imageContainer.setChildCount(imageContainer.getChildCount() + 1);
		
		return folderContainer;
	}

	public static void createVideosAlbumsDir() throws MediaInitException {
		isStopLoading = false;

		Iterator<LocalVideo> it = videos.iterator();
		while(it.hasNext()) {
			whetherStopLoading();
			
			LocalVideo localVideo = it.next();
			createVideoAlbumDir(localVideo);
			createAllVideoDir(localVideo);
		}
	}
	
	private static void createVideoAlbumDir(LocalVideo localVideo) {
		String folderStr = localVideo.getFolder();
		String folder_id = VIDEO_FOLDER_PREFIX + folderStr;
		
		Container folderContainer = getOrAddNewVideoFolderContainer(folder_id, folderStr);
		
		createVideo(folderContainer, localVideo);
	}

	private static Container getOrAddNewVideoFolderContainer(String id, String title) {
		Container folderContainer = getContainer(id);
		if (folderContainer != null)
			return folderContainer;
		
		return addNewVideoFolderContainer(id, title);
	}

	private static Container addNewVideoFolderContainer(String id, String title) {
		Container folderContainer = new Container(id,
				ContentTree.VIDEO_FOLDER_ID, title, AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container.storageFolder"), 0);
		folderContainer.setRestricted(true);
		folderContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		ContentTree.addNode(id, new ContentNode(id, folderContainer));
		
		Container videoContainer = ContentTree.getNode(VIDEO_FOLDER_ID).getContainer();
		videoContainer.addContainer(folderContainer);
		videoContainer.setChildCount(videoContainer.getChildCount() + 1);
		
		return folderContainer;
	}
	
	public static void createAllVideoDir(LocalVideo localVideo) {
		Container allVideosContainer = getOrAddNewAllVideoFolderContainer();
		
		createVideo(allVideosContainer, localVideo);
	}
	
	private static Container getOrAddNewAllVideoFolderContainer() {
		Container folderContainer = getContainer(ALL_VIDEO_ID);
		if (folderContainer != null)
			return folderContainer;
		
		Container container = createAllVideoLevelContainer();
		Container imagesContainer = getNode(VIDEO_ID).getContainer();
		if (imagesContainer == null)
			imagesContainer = createImagesRootContainer();
		imagesContainer.addContainer(container);
		imagesContainer.setChildCount(imagesContainer.getChildCount() + 1);
		
		return container;
	}
	
	private static void createVideo(Container videoContainer, LocalVideo localVideo) {
		long video_id = localVideo.getId();
		String item_id = HttpServerUtil.makeMediaId(localVideo.getPath());
		String link = HttpServerUtil.createLinkWithId(item_id);
		
		Res res = new Res(MimeType.valueOf(localVideo.getMimeType()), localVideo.getSize(), ModelUtil.toTimeString(localVideo.getDuration()/1000), 0L, link);
		
		VideoItem videoItem = new VideoItem(video_id + "", videoContainer.getId(), localVideo.getTitle(), localVideo.getArtist(), res);
		
		String thumb_id = HttpServerUtil.makeMediaId(localVideo.getThumbPath());
		if (null != thumb_id) {
			String thumbLink = HttpServerUtil.createLinkWithId(thumb_id);
			addObjectAlbumArtProperty(videoItem, thumbLink);
		}

		videoContainer.addItem(videoItem);
		videoContainer.setChildCount(videoContainer.getChildCount() + 1);
		ContentTree.addNode(localVideo.getPath() + "", new ContentNode(localVideo.getPath() + "", videoItem, localVideo.getPath()));
	}
	
	public static void createAudiosAlbumsDir() throws MediaInitException {
		isStopLoading = false;

		Iterator<LocalAudio> it = audios.iterator();
		while(it.hasNext()) {
			whetherStopLoading();

			LocalAudio localAudio = it.next();
			createAudioAlbumDir(localAudio);
			createAllAudioDir(localAudio);
		}
	}
	
	private static void createAudioAlbumDir(LocalAudio localAudio) {
		String folderStr = localAudio.getFolder();
		String folder_id = AUDIO_FOLDER_PREFIX + folderStr;
		
		Container folderContainer = getOrAddNewAudioFolderContainer(folder_id, folderStr);
		
		createAudio(folderContainer, localAudio);
	}

	private static void createAudio(Container folderContainer, LocalAudio localAudio) {
		long audio_id = localAudio.getId();
		String item_id = HttpServerUtil.makeMediaId(localAudio.getPath());
		String link = HttpServerUtil.createLinkWithId(item_id);

		Res res = new Res(MimeType.valueOf(localAudio.getMimeType()), localAudio.getSize(), ModelUtil.toTimeString(localAudio.getDuration()/1000), 0L,link);

		AudioItem audioItem = new AudioItem(audio_id + "", folderContainer.getId(), localAudio.getTitle(), localAudio.getArtist(), res);
		audioItem.addProperty(new DIDLObject.Property.UPNP.ARTIST(new PersonWithRole(localAudio.getArtist())));
		audioItem.addProperty(new DIDLObject.Property.UPNP.ALBUM(localAudio.getAlbum()));
		audioItem.addProperty(new DIDLObject.Property.UPNP.GENRE(localAudio.getGenre()));
		
		String thumb_id = HttpServerUtil.makeMediaId(localAudio.getAlbumArt());
		if (null != thumb_id) {
			String thumbLink = HttpServerUtil.createLinkWithId(thumb_id);
			addObjectAlbumArtProperty(audioItem, thumbLink);
		}

		folderContainer.addItem(audioItem);
		folderContainer.setChildCount(folderContainer.getChildCount() + 1);
		ContentTree.addNode(localAudio.getPath() + "", new ContentNode(localAudio.getPath() + "", audioItem, localAudio.getPath()));
	}

	private static Container getOrAddNewAudioFolderContainer(String id, String title) {
		Container folderContainer = getContainer(id);
		if (folderContainer != null)
			return folderContainer;
		
		return addNewAudioFolderContainer(id, title);
	}

	private static Container addNewAudioFolderContainer(String id, String title) {
		Container folderContainer = new Container(id,
				ContentTree.AUDIO_FOLDER_ID, title, AppPreference.getDLNACreater(),
				new DIDLObject.Class("object.container.storageFolder"), 0);
		folderContainer.setRestricted(true);
		folderContainer.setWriteStatus(WriteStatus.NOT_WRITABLE);
		ContentTree.addNode(id, new ContentNode(id, folderContainer));
		
		Container audioContainer = ContentTree.getNode(AUDIO_FOLDER_ID).getContainer();
		audioContainer.addContainer(folderContainer);
		audioContainer.setChildCount(audioContainer.getChildCount() + 1);
		
		return folderContainer;
	}

	public static void createAllAudioDir(LocalAudio localAudio) {
		Container allAudiosContainer = getOrAddNewAllAudioFolderContainer();
		
		createAudio(allAudiosContainer, localAudio);
	}
	
	private static Container getOrAddNewAllAudioFolderContainer() {
		Container folderContainer = getContainer(ALL_AUDIO_ID);
		if (folderContainer != null)
			return folderContainer;
		
		Container container = createAllMusicLevelContainer();
		Container imagesContainer = getNode(AUDIO_ID).getContainer();
		if (imagesContainer == null)
			imagesContainer = createImagesRootContainer();
		imagesContainer.addContainer(container);
		imagesContainer.setChildCount(imagesContainer.getChildCount() + 1);
		
		return container;
	}
	
	private static void addObjectAlbumArtProperty(DIDLObject didlobject, String link)
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
	
	public static DIDLObject getImageItemFromPath(String path) {
		String type = "image/*";
		if (path.startsWith("/sdcard"))
			path = "/mnt/sdcard" + path.substring(7);
		File subFile = new File(path);
		
		String item_id = HttpServerUtil.makeMediaId(path);
		String link = HttpServerUtil.createLinkWithId(item_id);
		
		ImageItem imageItem = new ImageItem("0/3/" + subFile.getName(), IMAGE_FOLDER_PREFIX + subFile.getParent(), subFile.getName(),
				AppPreference.getDLNACreater(), new Res(new ProtocolInfo("http-get:*:" + type + ":" + "*"), subFile.length(), link));
		ContentTree.addNode(subFile.getAbsolutePath(), new ContentNode(subFile.getAbsolutePath(), imageItem, subFile.getAbsolutePath()));
		
		return imageItem;
	}
	
	public static DIDLObject getVideoItemFromPath(String path) {
		String type = "video/*";
		if (path.startsWith("/sdcard"))
			path = "/mnt/sdcard" + path.substring(7);
		File subFile = new File(path);
		
		String item_id = HttpServerUtil.makeMediaId(path);
		String link = HttpServerUtil.createLinkWithId(item_id);
		
		VideoItem videoItem = new VideoItem("0/2/" + subFile.getName(), VIDEO_FOLDER_PREFIX + subFile.getParent(), subFile.getName(),
				AppPreference.getDLNACreater(), new Res(new ProtocolInfo("http-get:*:" + type + ":" + "*"), subFile.length(), link));
		ContentTree.addNode(subFile.getAbsolutePath(), new ContentNode(subFile.getAbsolutePath(), videoItem, subFile.getAbsolutePath()));
		
		return videoItem;
	}
	
	public static DIDLObject getAudioItemFromPath(String path) {
		String type = "audio/*";
		if (path.startsWith("/sdcard"))
			path = "/mnt/sdcard" + path.substring(7);
		File subFile = new File(path);
		
		String item_id = HttpServerUtil.makeMediaId(path);
		String link = HttpServerUtil.createLinkWithId(item_id);
		
		AudioItem audioItem = new AudioItem("0/1/" + subFile.getName(), AUDIO_FOLDER_PREFIX + subFile.getParent(), subFile.getName(),
				AppPreference.getDLNACreater(), new Res(new ProtocolInfo("http-get:*:" + type + ":" + "*"), subFile.length(), link));
		ContentTree.addNode(subFile.getAbsolutePath(), new ContentNode(subFile.getAbsolutePath(), audioItem, subFile.getAbsolutePath()));
		
		return audioItem;
	}
	
	public static void stopLoading() {
		isStopLoading = true;
	}

	private static void whetherStopLoading() throws MediaInitException {
		if (isStopLoading)
			throw new MediaInitException("media stop loading");
	}
}
