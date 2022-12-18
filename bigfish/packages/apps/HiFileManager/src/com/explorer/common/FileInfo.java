package com.explorer.common;

public class FileInfo {

	private String lastModifyTime;

	private String fileName;

	private String fileSize;

	private String filtType;

	public String getLastModifyTime() {
		return lastModifyTime;
	}

	public void setLastModifyTime(String lastModifyTime) {
		this.lastModifyTime = lastModifyTime;
	}

	public String getFileName() {
		return fileName;
	}

	public void setFileName(String fileName) {
		this.fileName = fileName;
	}

	public String getFileSize() {
		return fileSize;
	}

	public void setFileSize(String fileSize) {
		this.fileSize = fileSize;
	}

	public String getFiltType() {
		return filtType;
	}

	public void setFiltType(String filtType) {
		this.filtType = filtType;
	}
}
