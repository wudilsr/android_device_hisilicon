package com.hisilicon.android.hiRMService;

public class UpgradeEntity {
    private String targetVersion;
    private String description;
    private String filePath;
    private String releaseTime;
    private String fileSize;
    private String changePartition;
    private String compulsoryUpgrade;

    public String getTargetVersion() {
        return targetVersion;
    }

    public void setTargetVersion(String targetVersion) {
        this.targetVersion = targetVersion;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getFilePath() {
        return filePath;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }

    public String getReleaseTime() {
        return releaseTime;
    }

    public void setReleaseTime(String releaseTime) {
        this.releaseTime = releaseTime;
    }

    public String getFileSize() {
        return fileSize;
    }

    public void setFileSize(String fileSize) {
        this.fileSize = fileSize;
    }

    public String getChangePartition() {
        return changePartition;
    }

    public void setChangePartition(String changePartition) {
        this.changePartition = changePartition;
    }

    public String getCompulsoryUpgrade() {
        return compulsoryUpgrade;
    }
    public void setCompulsoryUpgrade(String compulsoryUpgrade) {
        this.compulsoryUpgrade = compulsoryUpgrade;
    }
}