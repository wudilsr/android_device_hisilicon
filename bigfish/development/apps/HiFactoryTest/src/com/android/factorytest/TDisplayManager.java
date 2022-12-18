package com.android.factorytest;

import com.hisilicon.android.HiDisplayManager;

public class TDisplayManager {

    public static final int HDMI = 0;
    public static final int AV = 1;

    public static final int DISABLE = 0;
    public static final int ENABLE = 1;

    private HiDisplayManager mDispManager;

    public TDisplayManager() {
        mDispManager = new HiDisplayManager();
    }

    // 设置显示输出模式为AV输出
    public void setAvOutputDispMode() {
        mDispManager.setOutputEnable(HDMI, DISABLE);
        mDispManager.setOutputEnable(AV, ENABLE);
    }

    // 设置显示输出模式为HDMI输出
    public void setHDMIOutputDispMode() {
        mDispManager.setOutputEnable(AV, DISABLE);
        mDispManager.setOutputEnable(HDMI, ENABLE);
    }

    public boolean isHdmiOutputMode() {
        return ENABLE == mDispManager.getOutputEnable(HDMI);
    }

}