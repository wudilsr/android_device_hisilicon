package com.hisilicon.android.hiRMService;

public class SuspendMode {
    public boolean enableFlag;
    public boolean lockFlag;
    
    public SuspendMode() {
        enableFlag = false;
        lockFlag = false;
    }
    public boolean getEnableFlag() {
        return enableFlag;
    }
    public void setEnableFlag(boolean enableFlag) {
        this.enableFlag = enableFlag;
    }
    public boolean getLockFlag() {
        return lockFlag;
    }
    public void setLockFlag(boolean lockFlag) {
        this.lockFlag = lockFlag;
    }
}