package com.hisilicon.android.hiRMService;

public class AppEntity {

    public String packageName;
    public int launchCount;
    public long usageTime;

    @Override
    public String toString() {
        StringBuffer sb = new StringBuffer();
        sb.append("PackageName : ").append(packageName).append("\n");
        sb.append("Count = ").append(launchCount).append("\t");
        sb.append("Time = ").append(usageTime).append("\n\n\n");
        return sb.toString();
    }

}