package com.android.hisiliconsetting.upgrade;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.xmlpull.v1.XmlPullParser;

import android.app.Activity;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.SystemProperties;
import android.util.Log;
import android.util.Xml;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.android.hisiliconsetting.R;

public class OnlineUpgradeActivity extends Activity {

    private final String TAG = "OnlineUpgradeActivity";
    private final String SYSTEM_VERSION = "ro.build.description";
    private final String INTRA_NET_PATH = "no";

    private final int WHAT_HAS_NOT_UPGRADE = 1;
    private final int WHAT_HAS_UPGRADE = 2;
    private final int WHAT_HAS_NOT_NETWORK = 3;
    private final int COMPLETEUPGRADE = 1;
    private final int OTAUPGRADE = 2;
    private int flag = 0;
    private int XMLID = 0;

    private List<OTAEntity> otaUpgrades;
    private List<CompleteEntity> completeUpgrades;
    private UpgradeEntity mUpgradeEntity;
    private CompleteEntity completeUpgrade;
    private OTAEntity otaUpgrade;
    private InputStream is;
    private HttpDownloader downloader;

    private TextView textView;
    private ProgressBar progressBar;
    private String systemVersion;
    private boolean isFinish = false;

    private Handler handler = new Handler() {
        public void handleMessage(android.os.Message msg) {
            int what = msg.what;
            switch (what) {
            case WHAT_HAS_NOT_UPGRADE:
                textView.setVisibility(View.VISIBLE);
                progressBar.setVisibility(View.GONE);
                break;
            case WHAT_HAS_UPGRADE:
                textView.setVisibility(View.GONE);
                progressBar.setVisibility(View.GONE);
                Intent upgrade = new Intent(OnlineUpgradeActivity.this,
                        OnlineDialogActivity.class);
                upgrade.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
                upgrade.putExtra("entity", mUpgradeEntity);
                upgrade.putExtra("version", systemVersion);
                startActivity(upgrade);
                break;
            case WHAT_HAS_NOT_NETWORK:
                if(null == is){
                    downloader.disConnect();
                    textView.setVisibility(View.VISIBLE);
                    textView.setText(getResources().getString(R.string.upgrade_message9));
                    progressBar.setVisibility(View.GONE);
                }
            default:
                break;
            }

        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.online_upgrade_main);

        downloader = new HttpDownloader(OnlineUpgradeActivity.this);
        textView = (TextView) findViewById(R.id.online_text);
        progressBar = (ProgressBar) findViewById(R.id.online_progress_bar);
        checkUpgrade();
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (isFinish)
            finish();
        isFinish = true;
    }

    @Override
    protected void onDestroy() {
        downloader.disConnect();
        super.onDestroy();
    }

    private void checkUpgrade() {
        new Thread(new Runnable() {

            @Override
            public void run() {
                downloadXML(true);
            }
        }).start();
        handler.sendEmptyMessageDelayed(WHAT_HAS_NOT_NETWORK, 1000 * 10);
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
            handler.sendEmptyMessage(WHAT_HAS_NOT_UPGRADE);
            return;
        }
        try {
            // downloadFile(xmlPath);
            is = downloader.getInputStream(xmlPath);
            if (is == null) {
                downloadNextXML();
            } else {
                if (hasUpgradeVersion()) {
                    handler.sendEmptyMessage(WHAT_HAS_UPGRADE);
                } else {
                    handler.sendEmptyMessage(WHAT_HAS_NOT_UPGRADE);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            downloadNextXML();
        }
    }

    public boolean hasUpgradeVersion() throws Exception {
        parse();

        systemVersion = SystemProperties.get(SYSTEM_VERSION);
        if(null == systemVersion || "".equals(systemVersion))
            return false;
        Log.d(TAG, "************curVersion = " + systemVersion);
        VersionInfo version_now = new VersionInfo(systemVersion);
        OTAEntity mOTAEntity = null;
        CompleteEntity mCompleteEntity = null;
        VersionInfo ota_version_latest = null;
        VersionInfo com_version_latest = null;

        if (null != otaUpgrades && otaUpgrades.size() > 0) {
            VersionInfo version_cur;
            for (int i = 0; i < otaUpgrades.size(); i++) {
                version_cur = new VersionInfo(otaUpgrades.get(i)
                        .getCurrentVersion());
                if (version_now.compare(version_cur) != 0) {
                    otaUpgrades.remove(i);
                    i--;
                }
            }
            if (otaUpgrades.size() > 0) {
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

        }
        if (null != completeUpgrades && completeUpgrades.size() > 0) {
            VersionInfo version_min;
            VersionInfo version_target;
            VersionInfo version_max;
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
        return true;
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
}