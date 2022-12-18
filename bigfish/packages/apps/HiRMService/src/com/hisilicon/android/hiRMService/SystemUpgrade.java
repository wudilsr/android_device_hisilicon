package com.hisilicon.android.hiRMService;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.xmlpull.v1.XmlPullParser;

import android.app.AlertDialog;
import android.app.DownloadManager;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.DialogInterface.OnKeyListener;
import android.content.Intent;
import android.net.Uri;
import android.net.WebAddress;
import android.os.Build;
import android.os.Environment;
import android.os.Handler;
import android.os.IBinder;
import android.os.ServiceManager;
import android.os.SystemProperties;
import android.os.StatFs;
import android.os.storage.IMountService;
import android.os.storage.StorageManager;
import android.os.storage.StorageVolume;
import android.util.Log;
import android.util.Xml;
import android.view.KeyEvent;
import android.view.WindowManager;

public class SystemUpgrade {

    private final String SYSTEM_VERSION = "ro.build.description";
    private final String INTRA_NET_PATH = "no";//set path for download XML file
    private final String TAG = "SystemUpgrade";
    private final String XML_NAME = "upgrade.xml";
    private final String ZIP_NAME = "update.zip";

    private final int COMPLETEUPGRADE = 1;
    private final int OTAUPGRADE = 2;

    private final int WHAT_USB_CHECK = 1;
    private final int WHAT_USB_DOWNLOAD_FAIL = 2;
    private final int WHAT_USB_DOWNLOAD_SUCCESS = 3;
    private final int WHAT_SD_NO_SPACE = 4;

    private final int STATE_NO_USB = 1;
    private final int STATE_USB_NO_SPACE = 2;
    private final int STATE_USB_HAS_SPACE = 3;

    private final int GB_2_BYTE = 1024 * 1024 * 1024;
    private final int MB_2_BYTE = 1024 * 1024;
    private final int KB_2_BYTE = 1024;

    private final DecimalFormat DOUBLE_DECIMAL_FORMAT = new DecimalFormat(
            "0.##");

    private Context context;
    private DownloadManager mDownloadManager;
    private List<OTAEntity> otaUpgrades = null;
    private List<CompleteEntity> completeUpgrades = null;
    private OTAEntity otaUpgrade = null;
    private CompleteEntity completeUpgrade = null;
    private InputStream is = null;

    private int flag = 0;
    private long downloadID_xml;
    private long downloadID_zip;

    private String systemVersion;
    private String latestVersion;
    private String targetVersion;
    private String targetpath;
    private String fileSize;
    private String sdcardPath;
    private String changePartition;
    private String compulsoryUpgrade;
    private String releaseTime;
    private String description;
    private String availablePath;
    private int state = 0;
    private int XMLID = 0;

    private StorageManager mStorageManager;
    private StorageVolume[] storageVolumes;
    private String[] devicePath;
    private Handler handler = new Handler() {
        public void handleMessage(android.os.Message msg) {
            int what = msg.what;
            switch (what) {
            case WHAT_USB_CHECK:
                switch (state) {
                case STATE_NO_USB:
                    showUSBDialog(getString(R.string.no_usb));
                    break;
                case STATE_USB_NO_SPACE:
                    StringBuffer sb = new StringBuffer();
                    sb.append(getString(R.string.usb_no_space));
                    sb.append(fileSize).append("\n\n");
                    sb.append(getString(R.string.dialog_message));
                    showUSBDialog(sb.toString());
                    break;
                case STATE_USB_HAS_SPACE:
                    downloadUpgradeToUsb();
                    break;

                default:
                    break;
                }
                break;
            case WHAT_USB_DOWNLOAD_FAIL:
                Log.i(TAG, "******************** download fail ");
                StringBuffer sb = new StringBuffer();
                sb.append(getString(R.string.dialog_message2));
                sb.append("\n\n");
                sb.append(getString(R.string.dialog_message3));
                showUSBDialog(sb.toString());
                break;
            case WHAT_USB_DOWNLOAD_SUCCESS:
                Log.i(TAG, "******************** download finish ");
                Intent upgrade = new Intent(context, UpgradeActivity.class);
                upgrade.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                upgrade.putExtra("info", getInfo());
                upgrade.putExtra("path", availablePath);
                context.startActivity(upgrade);
                break;
            case WHAT_SD_NO_SPACE:
                Log.i(TAG, "******************** sdcard has no space ");
                showSdcarsNoSpaceDialog();
                break;
            default:
                break;
            }

        }
    };

    public long getDownloadID_xml() {
        return downloadID_xml;
    }

    public long getDownloadID_zip() {
        return downloadID_zip;
    }

    public String getSdcardPath() {
        return sdcardPath;
    }

    public void downloadNextXML() {
        XMLID++;
        downloadXML(false);
    }

    public void downloadXML(boolean reset) {
        Log.d(TAG, "in downloadXML");
        if (reset == true) {
            XMLID = 0;
        }
        String xmlPath = null;
        if (XMLID == 0) {
            xmlPath = INTRA_NET_PATH;
        } else {
            return;
        }
        try {
            // downloadFile(xmlPath);
            HttpDownloader downloader = new HttpDownloader(context);
            is = downloader.getInputStream(xmlPath);
            if (is == null) {
                downloadNextXML();
            } else {
                if (hasUpgradeVersion()) {
                    downloadZip();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            downloadNextXML();
        }
    }

    public void downloadZip() {
        Log.d(TAG, "in downloadZip");
        if ("true".equals(changePartition)) {
            Log.d(TAG, "***************** change partition upgrade !");
            getUSBList();
            if (devicePath.length == 0) {
                Log.i(TAG, "******************** STATE_NO_USB");
                state = STATE_NO_USB;
            } else if (!usbHasSpace()) {
                Log.i(TAG, "******************** STATE_USB_NO_SPACE");
                state = STATE_USB_NO_SPACE;
            } else {
                Log.i(TAG, "******************** STATE_USB_HAS_SPACE");
                state = STATE_USB_HAS_SPACE;
            }
            handler.sendEmptyMessage(WHAT_USB_CHECK);
        } else {
            if (getAppSize(fileSize) < getAvailaleSize(sdcardPath)) {
                try {
                    downloadFile(targetpath);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            } else {
                handler.sendEmptyMessage(WHAT_SD_NO_SPACE);
            }
        }
    }

    public SystemUpgrade(Context context, DownloadManager mDownloadManager) {
        this.context = context;
        this.mDownloadManager = mDownloadManager;
        this.sdcardPath = Environment.getExternalStorageDirectory().getPath();
        this.mStorageManager = (StorageManager) context.getSystemService(Context.STORAGE_SERVICE);
    }

    public boolean hasUpgradeVersion() throws Exception {
        parse();

        systemVersion = SystemProperties.get(SYSTEM_VERSION);
        if(null == systemVersion || "".equals(systemVersion))
            return false;
        Log.d(TAG, "************curVersion = " + systemVersion);
        UpgradeEntity mUpgradeEntity = null;
        OTAEntity mOTAEntity = null;
        VersionInfo version_now = new VersionInfo(systemVersion);
        CompleteEntity mCompleteEntity = null;
        VersionInfo ota_version_latest = null;
        VersionInfo com_version_latest = null;

        VersionInfo version_cur;
        VersionInfo version_min;
        VersionInfo version_target;
        VersionInfo version_max;
        boolean otaCompulsoryUpgrade = false;
        boolean comCompulsoryUpgrade = false;
        if (null != otaUpgrades && otaUpgrades.size() > 0) {
            for (int i = 0; i < otaUpgrades.size(); i++) {
                version_cur = new VersionInfo(otaUpgrades.get(i)
                        .getCurrentVersion());
                if (version_now.compare(version_cur) != 0) {
                    otaUpgrades.remove(i);
                    i--;
                }
            }
            if (otaUpgrades.size() > 0) {
                for (int i = 0; i < otaUpgrades.size(); i++) {
                    if ("true"
                            .equals(otaUpgrades.get(i).getCompulsoryUpgrade())) {
                        otaCompulsoryUpgrade = true;
                        break;
                    }
                }
            }

        }
        if (null != completeUpgrades && completeUpgrades.size() > 0) {
            for (int i = 0; i < completeUpgrades.size(); i++) {
                version_min = new VersionInfo(completeUpgrades.get(i)
                        .getMinVersion());
                version_target = new VersionInfo(completeUpgrades.get(i)
                        .getTargetVersion());
                version_max = new VersionInfo(completeUpgrades.get(i)
                        .getMaxVersion());
                if (version_now.compare(version_min) == -1
                        || version_now.compare(version_target) != -1
                        || version_now.compare(version_max) == 1) {
                    completeUpgrades.remove(i);
                    i--;
                }
            }
            if (completeUpgrades.size() > 0) {
                for (int i = 0; i < completeUpgrades.size(); i++) {
                    if ("true".equals(completeUpgrades.get(i)
                            .getCompulsoryUpgrade())) {
                        comCompulsoryUpgrade = true;
                        break;
                    }
                }
            }
        }
        if (otaCompulsoryUpgrade || comCompulsoryUpgrade) {
            if (null != otaUpgrades && otaUpgrades.size() > 0) {
                mOTAEntity = otaUpgrades.get(0);
                ota_version_latest = new VersionInfo(
                        mOTAEntity.getTargetVersion());
                for (int i = 1; i < otaUpgrades.size(); i++) {
                    version_cur = new VersionInfo(otaUpgrades.get(i)
                            .getTargetVersion());
                    if (ota_version_latest.compare(version_cur) == -1) {
                        mOTAEntity = otaUpgrades.get(i);
                        ota_version_latest = new VersionInfo(
                                mOTAEntity.getTargetVersion());
                    }
                }
            }
            if (null != completeUpgrades && completeUpgrades.size() > 0) {
                mCompleteEntity = completeUpgrades.get(0);
                com_version_latest = new VersionInfo(
                        mCompleteEntity.getTargetVersion());
                for (int i = 1; i < completeUpgrades.size(); i++) {
                    version_target = new VersionInfo(completeUpgrades.get(i)
                            .getTargetVersion());
                    if (com_version_latest.compare(version_target) == -1) {
                        mCompleteEntity = completeUpgrades.get(i);
                        com_version_latest = new VersionInfo(
                                mCompleteEntity.getTargetVersion());
                    }
                }
            }
        } else {
            return false;
        }

        if (null == mOTAEntity && null == mCompleteEntity) {
            return false;
        } else if (null != mOTAEntity && null == mCompleteEntity) {
            mUpgradeEntity = mOTAEntity;
        } else if (null == mOTAEntity && null != mCompleteEntity) {
            mUpgradeEntity = mCompleteEntity;
        } else if (null != mOTAEntity && null != mCompleteEntity) {
            if (ota_version_latest.compare(com_version_latest) == 1) {
                mUpgradeEntity = mOTAEntity;
            } else {
                mUpgradeEntity = mCompleteEntity;
            }
        }
        targetVersion = mUpgradeEntity.getTargetVersion();
        targetpath = mUpgradeEntity.getFilePath();
        fileSize = mUpgradeEntity.getFileSize();
        changePartition = mUpgradeEntity.getChangePartition();
        releaseTime = mUpgradeEntity.getReleaseTime();
        description = mUpgradeEntity.getDescription();
        return true;
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
            if (downloadUrl.toLowerCase().endsWith(".xml")) {
                dmReq.setMimeType("application/xml");

                File file = new File(sdcardPath, XML_NAME);
                if (file.exists()) {
                    file.delete();
                }

                dmReq.setDestinationInExternalPublicDir("", XML_NAME);

                new Thread("update download") {
                    public void run() {
                        downloadID_xml = mDownloadManager.enqueue(dmReq);
                    }
                }.start();
            } else if (downloadUrl.toLowerCase().endsWith(".zip")) {
                dmReq.setMimeType("application/zip");
                File file = new File(sdcardPath, ZIP_NAME);
                if (file.exists()) {
                    file.delete();
                }

                dmReq.setDestinationInExternalPublicDir("", ZIP_NAME);

                new Thread("update download") {
                    public void run() {
                        downloadID_zip = mDownloadManager.enqueue(dmReq);
                    }
                }.start();
            }
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

    public void parse() throws Exception {
        XmlPullParser parser = Xml.newPullParser();
        parser.setInput(is, "UTF-8");

        int eventType = parser.getEventType();
        while (eventType != XmlPullParser.END_DOCUMENT) {
            switch (eventType) {
            case XmlPullParser.START_DOCUMENT:
                otaUpgrades = new ArrayList<OTAEntity>();
                completeUpgrades = new ArrayList<CompleteEntity>();
                break;
            case XmlPullParser.START_TAG:
                if (parser.getName().equals("CompleteUpgrade")) {
                    completeUpgrade = new CompleteEntity();
                    flag = COMPLETEUPGRADE;
                    break;
                } else if (parser.getName().equals("MinVersion")) {
                    eventType = parser.next();
                    completeUpgrade.setMinVersion(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("MaxVersion")) {
                    eventType = parser.next();
                    completeUpgrade.setMaxVersion(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("TargetVersion")
                        && (flag == COMPLETEUPGRADE)) {
                    eventType = parser.next();
                    completeUpgrade.setTargetVersion(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("Description")
                        && (flag == COMPLETEUPGRADE)) {
                    eventType = parser.next();
                    completeUpgrade.setDescription(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("FilePath")
                        && (flag == COMPLETEUPGRADE)) {
                    eventType = parser.next();
                    completeUpgrade.setFilePath(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("ReleaseTime")
                        && (flag == COMPLETEUPGRADE)) {
                    eventType = parser.next();
                    completeUpgrade.setReleaseTime(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("FileSize")
                        && (flag == COMPLETEUPGRADE)) {
                    eventType = parser.next();
                    completeUpgrade.setFileSize(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("ChangePartition")
                        && (flag == COMPLETEUPGRADE)) {
                    eventType = parser.next();
                    completeUpgrade.setChangePartition(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("CompulsoryUpgrade")
                        && (flag == COMPLETEUPGRADE)) {
                    eventType = parser.next();
                    completeUpgrade.setCompulsoryUpgrade(parser.getText()
                            .trim());
                    break;
                }

                if (parser.getName().equals("OTAUpgrade")) {
                    otaUpgrade = new OTAEntity();
                    flag = OTAUPGRADE;
                    break;
                } else if (parser.getName().equals("CurrentVersion")) {
                    eventType = parser.next();
                    otaUpgrade.setCurrentVersion(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("TargetVersion")
                        && (flag == OTAUPGRADE)) {
                    eventType = parser.next();
                    otaUpgrade.setTargetVersion(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("Description")
                        && (flag == OTAUPGRADE)) {
                    eventType = parser.next();
                    otaUpgrade.setDescription(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("FilePath")
                        && (flag == OTAUPGRADE)) {
                    eventType = parser.next();
                    otaUpgrade.setFilePath(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("ReleaseTime")
                        && (flag == OTAUPGRADE)) {
                    eventType = parser.next();
                    otaUpgrade.setReleaseTime(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("FileSize")
                        && (flag == OTAUPGRADE)) {
                    eventType = parser.next();
                    otaUpgrade.setFileSize(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("CompulsoryUpgrade")
                        && (flag == OTAUPGRADE)) {
                    eventType = parser.next();
                    otaUpgrade.setCompulsoryUpgrade(parser.getText().trim());
                    break;
                }
                break;
            case XmlPullParser.END_TAG:
                if (parser.getName().equals("OTAUpgrade")) {
                    otaUpgrades.add(otaUpgrade);
                    otaUpgrade = null;
                }
                if (parser.getName().equals("CompleteUpgrade")) {
                    completeUpgrades.add(completeUpgrade);
                    completeUpgrade = null;
                }
                break;
            }
            eventType = parser.next();
        }
        is.close();
    }

    public long getAvailaleSize(String path) {
        StatFs stat = new StatFs(path);
        long blockSize = stat.getBlockSize();
        long availableBlocks = stat.getAvailableBlocks();
        return availableBlocks * blockSize;
    }

    public long getAllSize(String path) {
        StatFs stat = new StatFs(path);
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

    public String[] getInfo() {
        String[] info = { systemVersion, targetVersion, releaseTime, fileSize,
                description };
        return info;
    }

    private void downloadUpgradeToUsb() {
        new Thread(new Runnable() {

            @Override
            public void run() {
                HttpDownloader download = new HttpDownloader(context);
                int result = download.downFile(targetpath, availablePath,
                        ZIP_NAME);
                if (result == 0) {
                    handler.sendEmptyMessage(WHAT_USB_DOWNLOAD_SUCCESS);
                } else {
                    handler.sendEmptyMessage(WHAT_USB_DOWNLOAD_FAIL);
                }
            }
        }).start();
    }

    private void showSdcarsNoSpaceDialog() {
        StringBuffer sb = new StringBuffer();
        sb.append(getString(R.string.sd_no_space));
        sb.append(fileSize).append("\n\n");
        sb.append(getString(R.string.dialog_message));

        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle(getString(R.string.system_upgrade));
        builder.setNegativeButton(getString(R.string.btn_confirm), null);
        builder.setMessage(sb.toString());

        AlertDialog ad = builder.create();
        ad.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
        ad.setCanceledOnTouchOutside(false);
        ad.setCancelable(false);
        ad.show();
    }

    private void showUSBDialog(String str) {
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle(getString(R.string.change_upgrade));
        builder.setNegativeButton(getString(R.string.btn_confirm),
                new UsbUpgradeListener());
        builder.setMessage(str);
        AlertDialog ad = builder.create();
        ad.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
        ad.setCanceledOnTouchOutside(false);
        ad.setCancelable(false);
        ad.show();
    }

    private boolean usbHasSpace() {
        for (int i = 0; i < devicePath.length; i++) {
            String usbPath = devicePath[i];
            File usbFile = new File(usbPath);
            if (usbFile.canWrite()
                    && getAppSize(fileSize) <= getAvailaleSize(usbPath)) {
                availablePath = usbPath;
                            return true;
                        }
        }
        return false;
                    }
    private String getString(int id) {
        return context.getResources().getString(id);
                }
    private void getUSBList() {
        try {
            devicePath = null;
            IBinder service = ServiceManager.getService("mount");
            if (service != null) {
                IMountService mountService = IMountService.Stub
                        .asInterface(service);
                List<android.os.storage.ExtraInfo> mountList = mountService
                        .getAllExtraInfos();
                storageVolumes = mStorageManager.getVolumeList();
                devicePath = getDevicePath(storageVolumes);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private String[] getDevicePath(StorageVolume[] storages) {
        String[] tmpPath = new String[storages.length];
        int count = storages.length;
        Pattern p = Pattern.compile("/mnt/sd[a-z]/");
        Matcher m = null;
        for (int i = 0; i < storages.length; i++) {
            String path = storages[i].getPath();
            m = p.matcher(path);
            if (m.find()) {
                tmpPath[i] = path;
            } else {
                count--;
            }
            }
        for (int i = 0; i < storages.length; i++) {
            for (int j = i + 1; j < storages.length; j++) {
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
        for (int i = 0; i < storages.length; i++) {
            if (tmpPath[i] != null) {
                path[j] = tmpPath[i];
                j++;
            }
        }
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

        public int compare(VersionInfo version_compare) {
            if (parseLong(this.versionDate) < parseLong(version_compare.versionDate)) {
                return -1;
            } else if (parseLong(this.versionDate) > parseLong(version_compare.versionDate)) {
                return 1;
            } else if (parseLong(this.versionDate) == parseLong(version_compare.versionDate)) {
                if (parseLong(this.versionFlag) < parseLong(version_compare.versionFlag)) {
                    return -1;
                } else if (parseLong(this.versionFlag) > parseLong(version_compare.versionFlag)) {
                    return 1;
                }
            }
            return 0;
        }

        private long parseLong(String string) {
            return Long.parseLong(string);
        }
    }

    public class UsbUpgradeListener implements
            android.content.DialogInterface.OnClickListener {

        @Override
        public void onClick(DialogInterface dialog, int which) {
            new Thread(new Runnable() {

                @Override
                public void run() {
                    for (int i = 0; i < 10; i++) {
                        try {
                            getUSBList();
                            if (devicePath.length == 0) {
                                state = STATE_NO_USB;
                            } else if (usbHasSpace()) {
                                    state = STATE_USB_HAS_SPACE;
                                break;
                                } else {
                                    state = STATE_USB_NO_SPACE;
                                break;
                            }
                            Thread.sleep(3000);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                    handler.sendEmptyMessage(WHAT_USB_CHECK);
                }
            }).start();
        }
    }
}