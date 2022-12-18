package com.hisilicon.dlna.dmc.gui.browse.files;

public class FolderBean {
	/**
	 * 文件夹的第一张图片路径
	 */
	private String topImagePath;
	/**
	 * 文件夹名
	 */
	private String folderName; 
	
	private int fileCounts;

	public String getTopImagePath() {
		return topImagePath;
	}

	public void setTopImagePath(String topImagePath) {
		this.topImagePath = topImagePath;
	}

	public String getFolderName() {
		return folderName;
	}

	public void setFolderName(String folderName) {
		this.folderName = folderName;
	}

	public int getFileCounts() {
		return fileCounts;
	}

	public void setFileCounts(int fileCounts) {
		this.fileCounts = fileCounts;
	}
	
	
}
