package com.hisilicon.android.videoplayer.bd;

import java.io.File;

import android.util.Log;

import com.hisilicon.android.hidvdinfo.HiDVDInfo;

public class DVDInfo
{
	private static final String TAG = "DVDInfo";

	private HiDVDInfo mHiDVDInfo;

	private boolean DEBUG = false;

	public DVDInfo()
	{
		mHiDVDInfo = new HiDVDInfo();
	}

	/**
	 * Check the DVD information.
	 * CN:检查蓝光信息
	 *
	 * @param pPath
	 *        CN:蓝光目录路径
	 * @return Command execution results 0- DVD directory not 0- not DVD directory
	 *         CN:命令执行结果 0-是蓝光目录 非0-不是蓝光目录
	 */
	public synchronized int checkDiscInfo(String pPath)
	{
		int _Result = 0;
		mHiDVDInfo.openDVD(pPath);
		_Result = mHiDVDInfo.checkDiscInfo();
		mHiDVDInfo.closeDVD();

		return _Result;
	}

	/**
	 * check is DVD or not.
	 * CN:是否是蓝光文件
	 *
	 * @param pPath
	 *        CN:蓝光目录路径
	 * @return true - 是 false - 否
	 */
	public boolean isDVDFile(String pPath)
	{
		if(DEBUG)
		Log.v(TAG, "path is " + pPath);

		/*if (!hasDVDDir(pPath))
		{
			return false;
		}*/

		if (checkDiscInfo(pPath) < 0)
		{
			return false;
		}

		return true;
	}

	/**
	 * Check the DVD directory
	 * 是否包含BDMV目录
	 *
	 * @param pPath
	 *        CN:蓝光目录路径
	 * @return true - 是 false - 否
	 */
	public boolean hasDVDDir(String pPath)
	{
		File _File = new File(pPath);

		if (!_File.exists())
		{
			return false;
		}

		File[] _Files = _File.listFiles();

		if (_Files == null)
		{
			return false;
		}

		for (int i = 0; i < _Files.length; i++)
		{
			if (_Files[i].getName().equalsIgnoreCase("BDMV"))
			{
				return true;
			}
		}

		return false;
	}
}
