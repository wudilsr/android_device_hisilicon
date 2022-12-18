package com.hisilicon.android.hiRMService;

public class OTAEntity extends UpgradeEntity {
    private String currentVersion;

    public String getCurrentVersion() {
        return currentVersion;
    }

    public void setCurrentVersion(String currentVersion) {
        this.currentVersion = currentVersion;
    }

}