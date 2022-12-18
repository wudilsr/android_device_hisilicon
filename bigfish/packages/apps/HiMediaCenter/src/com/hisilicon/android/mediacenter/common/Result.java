package com.hisilicon.android.mediacenter.common;

import android.util.Log;

import java.io.File;

public class Result {

	private String currentPath;
	private File[] currentFileArray;
	private int index;

	public int getIndex() {
		return index;
	}

	public void setIndex(int index) {
		this.index = index;
	}

	public String getCurrentPath() {
		return currentPath;
	}

	public void setCurrentPath(String currentPath) {
		this.currentPath = currentPath;
	}

	public File[] getCurrentFileArray() {
		return currentFileArray;
	}

	public void setCurrentFileArray(File[] currentFileArray) {
		this.currentFileArray = currentFileArray;
	}

	public void show() {
		Log.w("currentPath", " = " + currentPath);
		if (currentFileArray != null) {
			Log.w("currentFileArray", " = " + currentFileArray.length);
		} else {
			Log.w("currentFileArray", " = NULL");
		}
		Log.w("index", " = " + index);
	}
}
