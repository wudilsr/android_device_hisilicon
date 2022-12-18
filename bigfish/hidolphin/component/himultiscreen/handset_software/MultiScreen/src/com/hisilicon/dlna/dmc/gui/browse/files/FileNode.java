package com.hisilicon.dlna.dmc.gui.browse.files;

import java.io.Serializable;

import org.teleal.cling.support.model.item.ImageItem;

public class FileNode implements Serializable {
	private static final long serialVersionUID = 1L;
	private PictureNode picNode;
	private ImageItem imageItem;
	
	public FileNode(PictureNode picNode, ImageItem imageItem){
		this.picNode = picNode;
		this.imageItem = imageItem;
	}
	
	public PictureNode getPictureNode() {
		return picNode;
	}
	public void setPictureNode(PictureNode picNode) {
		this.picNode = picNode;
	}
	public ImageItem getImageItem() {
		return imageItem;
	}
	public void setImageItem(ImageItem imageItem) {
		this.imageItem = imageItem;
	}

}
