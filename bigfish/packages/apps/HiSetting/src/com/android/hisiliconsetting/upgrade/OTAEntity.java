package com.android.hisiliconsetting.upgrade;

public class OTAEntity extends UpgradeEntity {

    private static final long serialVersionUID = 1L;
    private String currentVersion;

    public String getCurrentVersion() {
        return currentVersion;
    }

    public void setCurrentVersion(String currentVersion) {
        this.currentVersion = currentVersion;
    }

}