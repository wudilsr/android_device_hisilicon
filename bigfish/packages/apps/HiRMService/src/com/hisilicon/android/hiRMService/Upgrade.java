package com.hisilicon.android.hiRMService;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import android.app.AlertDialog;
import android.app.DownloadManager;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.net.Uri;
import android.net.WebAddress;
import android.os.Build;
import android.os.Environment;
import android.os.Handler;
import android.os.StatFs;
import android.os.SystemProperties;
import android.util.Log;
import android.view.WindowManager;
import android.widget.Toast;

public abstract class Upgrade {
    private final String TAG = "Upgrade";
    private final String SYSTEM_VERSION = "ro.build.description";

    private final int STATE_NO_SPACE = 1;
    private final int GB_2_BYTE = 1024 * 1024 * 1024;
    private final int MB_2_BYTE = 1024 * 1024;
    private final int KB_2_BYTE = 1024;

    private Context context;
    private DownloadManager mDownloadManager;

    private InputStream inputStream = null;
    private List<UpgradeEntity> entitys = null;

    private long downloadID;
    private int XMLID = 0;

    private String sdcardPath;
    private String targetpath;
    private String fileSize;
    private String releaseTime;

    private Handler handler = new Handler() {
        public void handleMessage(android.os.Message msg) {
            int what = msg.what;
            switch (what) {
            case STATE_NO_SPACE:
                showDialog();
                break;

            default:
                break;
            }
        };
    };

    public long getDownloadID() {
        return downloadID;
    }

    public String getReleaseTime() {
        return releaseTime;
    }

    public String getSdcardPath() {
        return sdcardPath;
    }


    public abstract String getIntraNetPath();

    public abstract String getFileName();

    public abstract String getPreferencesName();

    public abstract List<UpgradeEntity> parse(InputStream is) throws Exception;

    public Upgrade(Context context, DownloadManager mDownloadManager) {
        this.context = context;
        this.mDownloadManager = mDownloadManager;
        this.sdcardPath = Environment.getExternalStorageDirectory().getPath();
    }

    public void downloadNextXML() {
        XMLID++;
        downloadXML(false);
    }

    public void downloadXML(boolean reset) {
        if (reset == true) {
            XMLID = 0;
        }
        String xmlPath = null;
        if (XMLID == 0) {
            xmlPath = getIntraNetPath();
        } else {
            return;
        }
        try {
            HttpDownloader downloader = new HttpDownloader(context);
            inputStream = downloader.getInputStream(xmlPath);
            if (inputStream == null) {
                downloadNextXML();
            } else {
                if (hasUpgradeVersion()) {
                    if (getAppSize(fileSize) < getAvailaleSize()) {
                        try {
                            downloadFile(targetpath);
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    } else {
                        handler.sendEmptyMessage(STATE_NO_SPACE);
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            downloadNextXML();
        }
    }

    public boolean hasUpgradeVersion() throws Exception {
        entitys = parse(inputStream);

        UpgradeEntity entity_tmp;
        String latestVersion;
        String version_temp;
        String version_now = getVersion();

        if (null != entitys && entitys.size() > 0) {
            entity_tmp = entitys.get(0);
            latestVersion = entity_tmp.getReleaseTime();
        } else {
            return false;
        }

        for (int i = 1; i < entitys.size(); i++) {
            version_temp = entitys.get(i).getReleaseTime();
            if (compare(latestVersion, version_temp) == -1) {
                latestVersion = version_temp;
                entity_tmp = entitys.get(i);
            }
        }
        if (compare(version_now, latestVersion) == -1) {
            targetpath = entity_tmp.getFilePath();
            fileSize = entity_tmp.getFileSize();
            releaseTime = entity_tmp.getReleaseTime();
            return true;
        }
        return false;
    }

    public void downloadFile(String downloadUrl) throws Exception {
        Log.d(TAG, "in downloadFile");
        if (null != downloadUrl) {
            final DownloadManager.Request dmReq = new DownloadManager.Request(
                    Uri.parse(downloadUrl));
            WebAddress webAddress = new WebAddress(downloadUrl);
            webAddress.setPath(encodePath(webAddress.getPath()));
            dmReq.setDescription(webAddress.getHost());
            dmReq.addRequestHeader("cookie", null);
            dmReq.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED);
            if (downloadUrl.toLowerCase().endsWith(".img")) {
                dmReq.setMimeType("application/img");
            } else {
                dmReq.setMimeType("application/zip");
            }
            File file = new File(sdcardPath, getFileName());
            if (file.exists()) {
                file.delete();
            }

            dmReq.setDestinationInExternalPublicDir("", getFileName());

            new Thread("update download") {
                public void run() {
                    downloadID = mDownloadManager.enqueue(dmReq);
                }
            }.start();
        }
    }

    public static String encodePath(String path) {
        char[] chars = path.toCharArray();

        boolean needed = false;
        for (char c : chars) {
            if ((c == '[') || (c == ']')) {
                needed = true;
                break;
            }
        }

        if (needed == false) {
            return path;
        }

        StringBuilder sb = new StringBuilder("");
        for (char c : chars) {
            if ((c == '[') || (c == ']')) {
                sb.append('%');
                sb.append(Integer.toHexString(c));
            } else {
                sb.append(c);
            }
        }

        return sb.toString();
    }

    public long getAvailaleSize() {
        StatFs stat = new StatFs(sdcardPath);
        long blockSize = stat.getBlockSize();
        long availableBlocks = stat.getAvailableBlocks();
        return availableBlocks * blockSize;
    }

    public long getAllSize() {
        StatFs stat = new StatFs(sdcardPath);
        long blockSize = stat.getBlockSize();
        long allBlocks = stat.getBlockCount();
        return allBlocks * blockSize;
    }

    public long getAppSize(String fileSize) {
        String size;
        if (fileSize.toUpperCase().endsWith("GB")) {
            size = fileSize.substring(0, fileSize.length() - 2);
            return (long) (Double.parseDouble(size) * GB_2_BYTE);
        } else if (fileSize.toUpperCase().endsWith("MB")) {
            size = fileSize.substring(0, fileSize.length() - 2);
            return (long) (Double.parseDouble(size) * MB_2_BYTE);
        } else if (fileSize.toUpperCase().endsWith("KB")) {
            size = fileSize.substring(0, fileSize.length() - 2);
            return (long) (Double.parseDouble(size) * KB_2_BYTE);
        } else if (fileSize.toUpperCase().endsWith("B")) {
            size = fileSize.substring(0, fileSize.length() - 1);
            return (long) (Double.parseDouble(size));
        } else {
            return 0;
        }
    }

    public int compare(String str1, String str2) {
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
        Date date1;
        Date date2;
        try {
            date1 = format.parse(str1);
            date2 = format.parse(str2);
            return date1.compareTo(date2);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    public void setVersion(String version) {
        SharedPreferences preferences = context.getSharedPreferences("upgrade",
                Context.MODE_PRIVATE);
        Editor editor = preferences.edit();
        editor.putString(getPreferencesName(), version);
        editor.commit();
    }

    public String getVersion() {
        SharedPreferences preferences = context.getSharedPreferences("upgrade",
                Context.MODE_PRIVATE);
        String version = preferences.getString(getPreferencesName(), null);
        if (null == version) {
            VersionInfo info = new VersionInfo(SystemProperties.get(SYSTEM_VERSION));
            SimpleDateFormat format1 = new SimpleDateFormat("yyyyMMdd");
            Date date = null;
            try {
                date = format1.parse(info.versionDate);
            } catch (Exception e) {
                e.printStackTrace();
            }
            SimpleDateFormat format2 = new SimpleDateFormat("yyyy-MM-dd");
            version = format2.format(date);
        }
        return version;
    }

    public class VersionInfo {
        String versionDate;
        String versionFlag;

        public VersionInfo(String version) {
            String versionInfo[] = version.split(" ");
            String versionInfo_part[] = versionInfo[3].split("\\.");
            for (int i = 0; i < versionInfo.length; i++) {
                Log.d(TAG, "versionInfo[i] = " + versionInfo[i]);
            }
            for (int i = 0; i < versionInfo_part.length; i++) {
                Log.d(TAG, "" + versionInfo_part[i]);
            }
            versionDate = versionInfo_part[2];
            versionFlag = versionInfo_part[3];
        }
    }

    private void showDialog() {
        StringBuffer sb = new StringBuffer();
        sb.append(context.getResources().getString(R.string.sd_no_space));
        sb.append(fileSize).append("\n");

        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle(getPreferencesName()
                + context.getResources().getString(R.string.upgrade));
        builder.setNegativeButton("OK", null);
        builder.setMessage(sb.toString());

        AlertDialog ad = builder.create();
        ad.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
        ad.setCanceledOnTouchOutside(false);
        ad.setCancelable(false);
        ad.show();
    }
}