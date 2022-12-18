package com.hisilicon.android.hiRMService;

public class CompleteEntity extends UpgradeEntity {
    private String minVersion;
    private String maxVersion;

    public String getMinVersion() {
        return minVersion;
    }

    public void setMinVersion(String minVersion) {
        this.minVersion = minVersion;
    }

    public String getMaxVersion() {
        return maxVersion;
    }

    public void setMaxVersion(String maxVersion) {
        this.maxVersion = maxVersion;
    }

}