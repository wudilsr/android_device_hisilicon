package com.hisilicon.android.mediacenter.bd;

import java.io.File;

import android.util.Log;

import com.hisilicon.android.hidvdinfo.HiDVDInfo;

public class DVDInfo {
	private static final String TAG = "DVDInfo";

	private HiDVDInfo mHiDVDInfo;

	private boolean DEBUG = false;

	public DVDInfo() {
		mHiDVDInfo = new HiDVDInfo();
	}

	public synchronized int checkDiscInfo(String pPath) {
		int _Result = 0;
		int m = mHiDVDInfo.openDVD(pPath);
		_Result = mHiDVDInfo.checkDiscInfo();
		mHiDVDInfo.closeDVD();

		return _Result;
	}

	public boolean isDVDFile(String pPath) {
		if (DEBUG)
			Log.v(TAG, "path is " + pPath);

		/*if (!hasBDMVDir(pPath)) {
			return false;
		}*/

		if (checkDiscInfo(pPath) < 0) {
			return false;
		}

		return true;
	}

	public boolean hasBDMVDir(String pPath) {
		File _File = new File(pPath);

		if (!_File.exists()) {
			return false;
		}

		File[] _Files = _File.listFiles();

		if (_Files == null) {
			return false;
		}

		for (int i = 0; i < _Files.length; i++) {
			if (_Files[i].getName().equalsIgnoreCase("BDMV")) {
				return true;
			}
		}

		return false;
	}
}
