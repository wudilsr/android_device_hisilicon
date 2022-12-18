package com.hisilicon.android.errorreport;

import android.util.Log;

import net.lingala.zip4j.core.ZipFile;
import net.lingala.zip4j.exception.ZipException;
import net.lingala.zip4j.model.ZipParameters;
import net.lingala.zip4j.util.Zip4jConstants;

public class ZipUtil {

	public ZipUtil() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param source 要压缩文件所在的文件夹的绝对路径
	 * @param dest 压缩后的文件路径(包含文件名)如: c:/temp/abc.zip
	 * @return 压缩成功返回 0 ; 反之,返回 -1
	 */
	public static int addFoldToZip(String source, String dest) {

		if (source == null || dest == null) {
			return -1;
		}
		try {
			ZipFile zipFile = new ZipFile(dest);
//			zipFile.setRunInThread(true);
			ZipParameters zipParameters = new ZipParameters();
			zipParameters.setCompressionMethod(Zip4jConstants.COMP_DEFLATE);
			zipParameters.setCompressionLevel(Zip4jConstants.DEFLATE_LEVEL_NORMAL);
			zipFile.addFolder(source, zipParameters);
		} catch (ZipException e) {
			Log.d("com.hisilicon.android.utils.ZipUtil",
					"Add Fold To Zip Failure");
			return -1;
		}

		return 0;
	}


}
