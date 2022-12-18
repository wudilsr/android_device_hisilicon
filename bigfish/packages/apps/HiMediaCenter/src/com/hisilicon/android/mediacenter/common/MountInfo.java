package com.hisilicon.android.mediacenter.common;

import java.util.List;

import android.content.Context;
import android.os.IBinder;
import android.os.ServiceManager;
import android.os.storage.IMountService;
import android.util.Log;
import android.os.storage.StorageManager;
import android.os.storage.StorageVolume;
import android.preference.Preference;
import android.content.Context;
import java.io.*;
import com.hisilicon.android.hisysmanager.HiSysManager;
public class MountInfo {
	private static final String TAG = "MountInfo";
	public String[] path = new String[64];
	public int[] type = new int[64];
	public String[] label = new String[64];
	public String[] partition = new String[64];
	public int index = 0;
	private StorageManager mStorageManager = null;

	public MountInfo(Context context) {
		try {
			// support for DevType
			IBinder service = ServiceManager.getService("mount");
			if (service != null) {
				IMountService mountService = IMountService.Stub
						.asInterface(service);
				List<android.os.storage.ExtraInfo> mountList = mountService
						.getAllExtraInfos();

				// if(mStorageManager == null){
				// mStorageManager = (StorageManager)
				// context.getSystemService(Context.STORAGE_SERVICE);
				// }

				// StorageVolume[] storageVolumes ;
				// storageVolumes = mStorageManager.getVolumeList();
				// String[] devicePath = getDevicePath(storageVolumes);
				index = mountList.size();

				for (int i = 0; i < index; i++) {
					path[i] = mountList.get(i).mMountPoint;
					if (mountList.get(i).mLabel != null) {
						label[i] = mountList.get(i).mDiskLabel + ": "
								+ mountList.get(i).mLabel;
					} else {
						label[i] = mountList.get(i).mDiskLabel;
					}
					partition[i] = label[i];
					String typeStr = mountList.get(i).mDevType;
					if (path[i].contains("/mnt/nand")) {
						type[i] = 3;
					} else if (typeStr.equals("SDCARD")) {
						type[i] = 3;
					} else if (typeStr.equals("SATA")) {
						type[i] = 2;
					} else if (typeStr.equals("USB2.0")) {
						type[i] = 0;
					} else if (typeStr.equals("USB3.0")) {
						type[i] = 1;
					} else if (typeStr.equals("UNKOWN")) {
						type[i] = 4;
					} else if (typeStr.equals("CD-ROM")) {
                        type[i] = 5;
                    }
				}
			}

		} catch (Exception e) {
			System.out.println(e);
		}
	}

	public String getMountDevices(String path) {
		int start = 0;
		start = path.lastIndexOf("/");
		String mountPath = path.substring(start + 1);
		return mountPath;
	}

	private String[] getDevicePath(StorageVolume[] storageVolumes) {
		String[] tmpPath = new String[storageVolumes.length];
		for (int i = 0; i < storageVolumes.length; i++) {
			tmpPath[i] = getMountDevices(storageVolumes[i].getPath());
		}
		int count = storageVolumes.length;
		// delete repeat
		for (int i = 0; i < storageVolumes.length; i++) {
			for (int j = i + 1; j < storageVolumes.length; j++) {
				try {
					if (tmpPath[i] != null) {
						if (tmpPath[j].equals(tmpPath[i]) && tmpPath[j] != null) {
							tmpPath[j] = null;
							count--;
						}
					}
				} catch (Exception e) {

				}
			}
		}
		String[] path = new String[count];
		int j = 0;
		for (int i = 0; i < storageVolumes.length; i++) {
			if (tmpPath[i] != null) {
				path[j] = tmpPath[i];
				j++;
			}
		}
		// sort
		for (int i = 0; i < count; i++) {
			for (int k = i + 1; k < count; k++) {
				if (path[i].compareTo(path[k]) > 0) {
					String tmp = path[k];
					path[k] = path[i];
					path[i] = tmp;
				}
			}
		}
		return path;
	}

	private String getUpdateFilePath(StorageVolume[] storageVolumes,
			String fileSuffix) {
		if (storageVolumes != null && storageVolumes.length > 0) {
			for (int i = 0; i < storageVolumes.length; i++) {
				if (storageVolumes[i].getPath().contains(fileSuffix)) {
					return storageVolumes[i].getPath();
				}
			}
		}
		return "/mnt/nand";

	}


	public void isSata(int i) {
		HiSysManager hisys = new HiSysManager();
		hisys.isSata();
		String fileName = "/mnt/SATA.txt";
		File f = new File(fileName);
		long size = f.length();

		if (size > 0) {

			String out = "";
			out = readFile(fileName);

			String sataName = "";
			sataName = out.substring(out.lastIndexOf("/"));

			if (path[i].contains(sataName)) {
				type[i] = 0;

			} else {
				type[i] = 1;
			}
            if(f.exists())
               f.delete();
		} else {

			type[i] = 1;
			if(f.exists())
	           f.delete();

		}

	}

	public String readFile(String fileName) {
		String output = "";

		File file = new File(fileName);

		if (file.exists()) {
			if (file.isFile()) {

				try {

					// FileReader fr = new FileReader(file);
					BufferedReader input = new BufferedReader(new FileReader(
							file));
					// StringBuffer buffer = new StringBuffer();

					// buffer.append(input.readLine());
					// output = buffer.toString();
					output = input.readLine();

					input.close();
				} catch (IOException ioException) {
					System.err.println("File Error!");
				}

			}
		} else {
			System.err.println("File Does Not Exit!");
		}

		return output;
	}
}
