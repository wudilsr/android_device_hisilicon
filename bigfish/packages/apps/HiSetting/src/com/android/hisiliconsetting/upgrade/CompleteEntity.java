package com.android.hisiliconsetting.upgrade;

public class CompleteEntity extends UpgradeEntity {

    private static final long serialVersionUID = 1L;
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