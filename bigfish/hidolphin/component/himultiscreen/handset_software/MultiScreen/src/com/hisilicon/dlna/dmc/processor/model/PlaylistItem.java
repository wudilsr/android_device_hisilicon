package com.hisilicon.dlna.dmc.processor.model;

import java.net.URI;
import java.net.URLDecoder;

import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.item.AudioItem;
import org.teleal.cling.support.model.item.ImageItem;
import org.teleal.cling.support.model.item.VideoItem;

import com.hisilicon.dlna.dmc.gui.customview.AdapterItem;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;
import com.hisilicon.dlna.dmc.utility.Utility;

public class PlaylistItem extends AdapterItem {
	public enum Type {
		VIDEO_LOCAL, AUDIO_LOCAL, IMAGE_LOCAL, AUDIO_REMOTE, VIDEO_REMOTE, IMAGE_REMOTE, UNKNOW,
	}

	private String id;
	private String url;
	private String title;
	private Type type;
	private String metadata;
	private int playStatue = 0;  //0:stop 1:play 2:pause
	private boolean remotePlay = false;

	public PlaylistItem() {
		super(null);
		this.id = "-1";
		this.url = "";
		this.title = "";
		this.type = Type.UNKNOW;
		this.metadata = "";
	}
	
	public PlaylistItem(Object data) {
		super(data);
		this.id = "-1";
		this.url = "";
		this.title = "";
		this.type = Type.UNKNOW;
		this.metadata = "";
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getId() {
		return id;
	}

	public boolean isRemotePlay() {
		return remotePlay;
	}

	public void setRemotePlay(boolean remotePlay) {
		this.remotePlay = remotePlay;
	}

	public String getUrl() {
		if (fromLocalType()) {
			String current;
			try {
//				System.out.println("The url 1 is:" + url);
//				String decodeUrl = URLDecoder.decode(url, "utf-8");
				String decodeUrl= url;
//				System.out.println("The url 2 is:" + decodeUrl);
				URI uri = URI.create(decodeUrl);
				String media_id = HttpServerUtil.makeMediaId(uri.getPath());
				current = HttpServerUtil.createLinkWithId(media_id);
				return current;
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return url;
	}

	public boolean fromLocalType() {
		return type == Type.IMAGE_LOCAL || type == Type.VIDEO_LOCAL || type == Type.AUDIO_LOCAL;
	}

	public void setUrl(String url) {
		this.url = url;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public Type getType() {
		return type;
	}

	public void setType(Type type) {
		this.type = type;
	}

	public String getMetaData() {
		if ("".equals(metadata))
			return Utility.createMetaData(title, type, url);
		return metadata;
	}

	public void setMetaData(String metadata) {
		this.metadata = metadata;
	}

	public int getPlayStatue() {
		return playStatue;
	}

	public void setPlayStatue(int playStatue) {
		this.playStatue = playStatue;
	}

	@Override
	public boolean equals(Object o) {
		if (!(o instanceof PlaylistItem))
			return false;
		PlaylistItem other = (PlaylistItem) o;
		return super.equals(other) && other.url.equals(this.url) && other.type.equals(this.type) && other.title.equals(this.title);
	}

	public static PlaylistItem createFromDLDIObject(DIDLObject object) {
		PlaylistItem item = new PlaylistItem(object);

		item.setId(object.getId());
		item.setTitle(object.getTitle());

		String url = HttpServerUtil.getUrlFrom(object);
		item.setUrl(url);

		boolean isLocal = HttpServerUtil.mediaFromLocal(url);

		if (object instanceof AudioItem) {
			if (isLocal) {
				item.setType(Type.AUDIO_LOCAL);
			} else
				item.setType(Type.AUDIO_REMOTE);
		} else if (object instanceof VideoItem) {
			if (isLocal) {
				item.setType(Type.VIDEO_LOCAL);
			} else
				item.setType(Type.VIDEO_REMOTE);
		} else if (object instanceof ImageItem) {
			if (isLocal) {
				item.setType(Type.IMAGE_LOCAL);
			} else
				item.setType(Type.IMAGE_REMOTE);
		} else {
			item.setType(Type.UNKNOW);
		}
		
		item.setMetaData(Utility.createMetaData(object));
		
		return item;
	}
	
	public enum ViewMode {
		ALL("All items", "All"), AUDIO_ONLY("Audio only", "Audio"), VIDEO_ONLY("Video only", "Video"), IMAGE_ONLY(
				"Image only", "Image");
		String viewMode = "";
		String compactString;

		ViewMode(String viewMode, String compactString) {
			this.viewMode = viewMode;
			this.compactString = compactString;
		}

		public String getString() {
			return viewMode;
		}

		public String getCompactString() {
			return compactString;
		}

		public boolean compatibleWith(Type type) {
			if (this.equals(ALL))
				return true;
			switch (type) {
			case AUDIO_LOCAL:
			case AUDIO_REMOTE:
				return this.equals(AUDIO_ONLY);
			case VIDEO_LOCAL:
			case VIDEO_REMOTE:
				return this.equals(VIDEO_ONLY);
			case IMAGE_LOCAL:
			case IMAGE_REMOTE:
				return this.equals(IMAGE_ONLY);
			default:
				return false;
			}
		}
	}
}