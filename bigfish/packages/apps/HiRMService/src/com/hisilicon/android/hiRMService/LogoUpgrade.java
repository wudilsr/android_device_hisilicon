package com.hisilicon.android.hiRMService;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.xmlpull.v1.XmlPullParser;

import android.app.DownloadManager;
import android.content.Context;
import android.util.Xml;

public class LogoUpgrade extends Upgrade {

    private static final String INTRA_NET_PATH = "no";//set path for download XML file
    private final String FILE_NAME = "logo.img";
    private final String PREFERENCES_NAME = "logo";

    public LogoUpgrade(Context context, DownloadManager mDownloadManager) {
        super(context, mDownloadManager);
    }



    @Override
    public String getIntraNetPath() {
        return INTRA_NET_PATH;
    }

    @Override
    public String getFileName() {
        return FILE_NAME;
    }

    @Override
    public String getPreferencesName() {
        return PREFERENCES_NAME;
    }

    @Override
    public List<UpgradeEntity> parse(InputStream is) throws Exception {
        XmlPullParser parser = Xml.newPullParser();
        parser.setInput(is, "UTF-8");

        List<UpgradeEntity> entitys = null;
        UpgradeEntity entity = null;

        int eventType = parser.getEventType();
        while (eventType != XmlPullParser.END_DOCUMENT) {
            switch (eventType) {
            case XmlPullParser.START_DOCUMENT:
                entitys = new ArrayList<UpgradeEntity>();
                break;
            case XmlPullParser.START_TAG:
                if (parser.getName().equals("LogoUpgrade")) {
                    entity = new UpgradeEntity();
                    break;
                } else if (parser.getName().equals("FilePath")) {
                    eventType = parser.next();
                    entity.setFilePath(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("ReleaseTime")) {
                    eventType = parser.next();
                    entity.setReleaseTime(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("FileSize")) {
                    eventType = parser.next();
                    entity.setFileSize(parser.getText().trim());
                    break;
                }
                break;
            case XmlPullParser.END_TAG:
                if (parser.getName().equals("LogoUpgrade")) {
                    entitys.add(entity);
                    entity = null;
                }
                break;
            }
            eventType = parser.next();
        }
        is.close();
        return entitys;
    }
}