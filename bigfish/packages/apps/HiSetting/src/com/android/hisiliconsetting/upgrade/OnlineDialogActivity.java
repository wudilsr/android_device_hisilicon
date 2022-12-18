package com.android.hisiliconsetting.upgrade;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.Executors;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.os.IBinder;
import android.os.ServiceManager;
import android.os.StatFs;
import android.os.storage.IMountService;
import android.os.storage.StorageManager;
import android.os.storage.StorageVolume;
import android.view.Display;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;
import com.hisilicon.android.hisysmanager.HiSysManager;
import com.android.hisiliconsetting.R;

public class OnlineDialogActivity extends Activity implements OnClickListener {

    private final String ZIP_NAME = "update.zip";

    private final int GB_2_BYTE = 1024 * 1024 * 1024;
    private final int MB_2_BYTE = 1024 * 1024;
    private final int KB_2_BYTE = 1024;

    private final int STATE_NO_USB = 0;
    private final int STATE_USB_NO_SPACE = 1;
    private final int STATE_USB_HAS_SPACE = 2;

    private final int SHOW_INFO_LAYOUT = 0;
    private final int SHOW_PROGRESS_LAYOUT = 1;
    private final int SHOW_REBOOT_LAYOUT = 2;

    private final int DOWNLOAD_FAIL = 0;
    private final int DOWNLOAD_SUCCESS = 1;

    private int state;
    private int showLayout;
    private long totalSize;

    private RelativeLayout showInfo;
    private RelativeLayout showProgress;
    private RelativeLayout showReboot;
    private ProgressBar progressBar;
    private TextView progressTextView;
    private TextView systemVersion_view;
    private TextView latestVersion_view;
    private TextView versionInfo_view;
    private Button btn_download;
    private Button btn_reboot;

    private UpgradeEntity mUpgradeEntity;

    private String systemVersion;
    private String targetVersion;
    private String targetpath;
    private String fileSize;
    private String changePartition;
    private String description;
    private String availablePath;

    private StorageManager mStorageManager;
    private StorageVolume[] storageVolumes;
    private String[] devicePath;

    private boolean isDownload;
    private boolean activityStop;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
        setContentView(R.layout.upgrade_dialog);
        getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE,
                R.layout.upgrade_titlebar);
        Intent intent = getIntent();
        if (null == intent) {
            finish();
        } else {
            systemVersion = intent.getStringExtra("version");
            mUpgradeEntity = (UpgradeEntity) intent
                    .getSerializableExtra("entity");
            if (null == systemVersion || null == mUpgradeEntity) {
                finish();
            }
        }
        init();
    }

    @Override
    protected void onResume() {
        super.onResume();
        activityStop = false;
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.button_download:
            downloadZip();
            break;
        case R.id.button_reboot:
            reboot();
            break;
        default:
            break;
        }
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK
                || keyCode == KeyEvent.KEYCODE_HOME
                || keyCode == KeyEvent.KEYCODE_SETTINGS) {
            if (isDownload) {
                return true;
            }
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    protected void onStop() {
        super.onStop();
        activityStop = true;
    }

    private void init() {
        mStorageManager = (StorageManager) getSystemService(Context.STORAGE_SERVICE);

        targetVersion = mUpgradeEntity.getTargetVersion();
        targetpath = mUpgradeEntity.getFilePath();
        fileSize = mUpgradeEntity.getFileSize();
        changePartition = mUpgradeEntity.getChangePartition();
        description = mUpgradeEntity.getDescription();

        showInfo = (RelativeLayout) findViewById(R.id.show_info_layout);
        showProgress = (RelativeLayout) findViewById(R.id.show_progress_layout);
        showReboot = (RelativeLayout) findViewById(R.id.show_reboot_layout);

        progressBar = (ProgressBar) findViewById(R.id.progress_bar);
        progressTextView = (TextView) findViewById(R.id.progress_text_view);
        systemVersion_view = (TextView) findViewById(R.id.systemVersion);
        latestVersion_view = (TextView) findViewById(R.id.latestVersion);
        versionInfo_view = (TextView) findViewById(R.id.versionInfo);

        systemVersion_view.setText(systemVersion);
        latestVersion_view.setText(targetVersion);
        versionInfo_view.setText(description);

        btn_download = (Button) findViewById(R.id.button_download);
        btn_reboot = (Button) findViewById(R.id.button_reboot);
        btn_download.setOnClickListener(this);
        btn_reboot.setOnClickListener(this);

        Display display = getWindowManager().getDefaultDisplay();
        LayoutParams params = getWindow().getAttributes();
        params.height = (int) (display.getHeight() * 0.7);
        params.width = (int) (display.getWidth() * 0.8);
        getWindow().setAttributes(params);

        showLayout = SHOW_INFO_LAYOUT;
        showLayout();
    }

    private void showLayout() {
        showInfo.setVisibility(View.GONE);
        showProgress.setVisibility(View.GONE);
        showReboot.setVisibility(View.GONE);
        switch (showLayout) {
        case SHOW_INFO_LAYOUT:
            showInfo.setVisibility(View.VISIBLE);
            btn_download.requestFocus();
            break;
        case SHOW_PROGRESS_LAYOUT:
            showProgress.setVisibility(View.VISIBLE);
            break;
        case SHOW_REBOOT_LAYOUT:
            showReboot.setVisibility(View.VISIBLE);
            btn_reboot.requestFocus();
            break;
        default:
            break;
        }
    }

    private void reboot() {
        HiSysManager hisys = new HiSysManager();
        hisys.upgrade(availablePath);
        Intent newIntent = new Intent("android.intent.action.MASTER_CLEAR");
        newIntent.putExtra("mount_point", availablePath);
        sendBroadcast(newIntent);
    }

    public void downloadZip() {
        if ("true".equals(changePartition)) {
            getUSBList();
            if (devicePath.length == 0) {
                state = STATE_NO_USB;
            } else if (!usbHasSpace()) {
                state = STATE_USB_NO_SPACE;
            } else {
                state = STATE_USB_HAS_SPACE;
            }
            checkState();
        } else {
            if (getAppSize(fileSize) < getAvailaleSize(getSdCardPath())) {
                try {
                    availablePath = getSdCardPath();
                    File file = new File(availablePath, ZIP_NAME);
                    if (file.exists()) {
                        file.delete();
                    }
                    downloadUpgradeFile();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            } else {
                StringBuffer sb = new StringBuffer();
                sb.append(getString(R.string.upgrade_sd_no_space));
                sb.append(fileSize).append("\n\n");
                sb.append(getString(R.string.upgrade_message2));
                showInfoDialog(sb.toString());
            }
        }
    }

    private void checkState() {
        switch (state) {
        case STATE_NO_USB:
            showInfoDialog(getString(R.string.upgrade_no_usb));
            break;
        case STATE_USB_NO_SPACE:
            StringBuffer sb = new StringBuffer();
            sb.append(getString(R.string.upgrade_usb_no_space));
            sb.append(fileSize).append("\n\n");
            sb.append(getString(R.string.upgrade_message2));
            showInfoDialog(sb.toString());
            break;
        case STATE_USB_HAS_SPACE:
            downloadUpgradeFile();
            break;
        }
    }

    private void downloadUpgradeFile() {
        showLayout = SHOW_PROGRESS_LAYOUT;
        showLayout();
        new Thread(new Runnable() {

            @Override
            public void run() {
                MyAsyncTask task = new MyAsyncTask();
                task.executeOnExecutor(Executors.newCachedThreadPool(), targetpath);
            }
        }).start();
    }

    private String getSdCardPath() {
        return Environment.getExternalStorageDirectory().getPath();
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

    public long getAvailaleSize(String path) {
        StatFs stat = new StatFs(path);
        long blockSize = stat.getBlockSize();
        long availableBlocks = stat.getAvailableBlocks();
        return availableBlocks * blockSize;
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

    private void showInfoDialog(String str) {
        AlertDialog.Builder builder = new AlertDialog.Builder(
                getApplicationContext());
        builder.setTitle(getString(R.string.upgrade_title));
        builder.setNegativeButton(getString(R.string.upgrade_btn_confirm), null);
        builder.setMessage(str);
        AlertDialog ad = builder.create();
        ad.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
        ad.show();
        finish();
    }

    private class MyAsyncTask extends AsyncTask<String, Integer, Integer> {

        @Override
        protected Integer doInBackground(String... params) {
            OutputStream os = null;
            InputStream is = null;
            int result = DOWNLOAD_FAIL;
            int readedLength = -1;
            long downloadSize = 0;
            try {
                isDownload = true;
                while (true) {
                    if (CheckNetWork() == true) {
                        break;
                    } else {
                        Thread.sleep(500);
                    }
                }
                is = getInputStream(params[0]);
                os = getOutputStream();
                byte buffer[] = new byte[4 * 1024];
                while ((readedLength = is.read(buffer)) != -1) {
                    os.write(buffer, 0, readedLength);
                    downloadSize += readedLength;
                    publishProgress((int) (downloadSize * 100 / totalSize));
                }
                os.flush();
                result = DOWNLOAD_SUCCESS;
            } catch (Exception e) {
                result = DOWNLOAD_FAIL;
                e.printStackTrace();
            } finally {
                try {
                    os.close();
                    is.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
            return result;
        }

        @Override
        protected void onProgressUpdate(Integer... values) {
            super.onProgressUpdate(values);
            progressBar.setProgress(values[0]);
            progressTextView.setText(values[0] + "%");
        }

        @Override
        protected void onPostExecute(Integer result) {
            super.onPostExecute(result);
            switch (result) {
            case DOWNLOAD_SUCCESS:
                showLayout = SHOW_REBOOT_LAYOUT;
                showLayout();
                if (activityStop) {
                    try {
                        ComponentName componentName = new ComponentName(
                                "com.android.hisiliconsetting",
                                "com.android.hisiliconsetting.upgrade.OnlineDialogActivity");
                        Intent intent = new Intent();
                        intent.setComponent(componentName);
                        startActivity(intent);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                break;
            case DOWNLOAD_FAIL:
                isDownload = false;
                StringBuffer sb = new StringBuffer();
                sb.append(getString(R.string.upgrade_message3));
                sb.append("\n\n");
                sb.append(getString(R.string.upgrade_message4));
                showInfoDialog(sb.toString());
            default:
                break;
            }
        }

        private boolean CheckNetWork() {
            ConnectivityManager connectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkInfo info = connectivityManager.getActiveNetworkInfo();
            if (info == null || !info.isAvailable()) {
                return false;
            } else {
                return true;
            }
        }

        private InputStream getInputStream(String fileUrl) throws Exception {
            InputStream is = null;
            URL url = new URL(fileUrl);
            HttpURLConnection urlCon = (HttpURLConnection) url.openConnection();
            urlCon.setConnectTimeout(60 * 1000);
            urlCon.setReadTimeout(60 * 1000);
            is = urlCon.getInputStream();
            totalSize = urlCon.getContentLength();
            return is;
        }

        private OutputStream getOutputStream() throws IOException {
            OutputStream os = null;
            File file = new File(availablePath, ZIP_NAME);
            if (file.exists())
                file.delete();
            file.createNewFile();
            os = new FileOutputStream(file);
            return os;
        }
    }
}
