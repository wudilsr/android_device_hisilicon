package com.google.android.exoplayer.demo;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;

import android.content.Context;
import android.os.Build;
import android.util.Log;

public class SystemUtils {
    private static final String TAG = "SystemUtils";
    private Context mContext = null;

    // Productor_Model_Designer_Chip_AndroidVersion
    public static String OTT_LETV_C1S = "LETV_C1S_AMLOGIC_AML8726-MX_4.1.2";
    public static String OTT_KAIBOER_C9 = "KAIBOER_C9_ROCKCHIP_RK3066_4.1.1";
    public static String OTT_KAIBOER_F4 = "KAIBOER_F4_ROCKCHIP_RK3188_4.2.2";

    public String DEVICE_MODEL = getDeviceModel();

    private static SystemUtils mInstanse = null;

    public static SystemUtils getInstanse(Context context) {
        if (mInstanse == null) {
            mInstanse = new SystemUtils(context);
        }
        return mInstanse;
    }

    private SystemUtils(Context context) {
        mContext = context;
    }

    private static long getTotalCpuTime() { // 获取系统总CPU使用时间
        String[] cpuInfos = null;
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(
                    new FileInputStream("/proc/stat")), 1000);
            String load = reader.readLine();
            reader.close();
            cpuInfos = load.split(" ");
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        long totalCpu = Long.parseLong(cpuInfos[2])
                + Long.parseLong(cpuInfos[3]) + Long.parseLong(cpuInfos[4])
                + Long.parseLong(cpuInfos[6]) + Long.parseLong(cpuInfos[5])
                + Long.parseLong(cpuInfos[7]) + Long.parseLong(cpuInfos[8]);
        return totalCpu;
    }

    private static long getAppCpuTime() { // 获取应用占用的CPU时间
        String[] cpuInfos = null;
        try {
            int pid = android.os.Process.myPid();
            BufferedReader reader = new BufferedReader(new InputStreamReader(
                    new FileInputStream("/proc/" + pid + "/stat")), 1000);
            String load = reader.readLine();
            reader.close();
            cpuInfos = load.split(" ");
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        long appCpuTime = Long.parseLong(cpuInfos[13])
                + Long.parseLong(cpuInfos[14]) + Long.parseLong(cpuInfos[15])
                + Long.parseLong(cpuInfos[16]);
        return appCpuTime;
    }

    private long getAppCpuRate() {

        long appCpuTime = getAppCpuTime();
        long totalCpuTime = getTotalCpuTime();
        Log.d(TAG, "appCpuTime: " + appCpuTime + ", totalCpuTime: " + totalCpuTime);

        return appCpuTime * 100 / totalCpuTime;
    }

    private int getCpuInfo() {
        BufferedReader reader = null;
        String[] strings = null;

        String processName = "mediaserver";
        if (DEVICE_MODEL.equals(OTT_LETV_C1S)) {
            processName = mContext.getPackageName();
        }

        /*try {
            final Process m_process = Runtime.getRuntime().exec("/system/bin/top -d 1 -n 1 | grep " + processName);
            reader = new BufferedReader(new InputStreamReader(m_process.getInputStream()), 8192);
            String line;
            while ((line = reader.readLine()) != null) {
                Log.d(TAG, line);
                //line = line.trim();
                if (line.contains(processName)) {
                    Log.d(TAG, "Found cpu usage: " + line);
                    strings = line.split(" ");
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                reader = null;
            }
        }*/

        if (strings != null && strings.length > 0) {
            for (int i = 0; i < strings.length; i++){
                if (strings[i].contains("%")) {
                    String rate = strings[i].substring(0, strings[i].indexOf("%"));
                    return Integer.parseInt(rate);
                }
            }
        }

        return 0;
    }

    private int getMemoryInfo() {
        BufferedReader reader = null;
        String[] strings = null;

        String processName = "mediaserver";
        if (DEVICE_MODEL.equals(OTT_LETV_C1S)) {
            processName = mContext.getPackageName();
        }

        try {
            // should android.permission.DUMP and system app
            final Process m_process = Runtime.getRuntime().exec("/system/bin/dumpsys meminfo | grep " + processName);
            reader = new BufferedReader(new InputStreamReader(m_process.getInputStream()), 8192);
            String line;
            while ((line = reader.readLine()) != null) {
                Log.d(TAG, line);
                //line = line.trim();
                if (line.contains(processName)) {
                    Log.d(TAG, "Found memory usage: " + line);
                    strings = line.split(" ");
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                reader = null;
            }
        }

        if (strings != null && strings.length > 0) {
            return Integer.parseInt(strings[0]);
        }

        return 0;
    }


    public HashMap<String, Integer> getTopInfo() {
        BufferedReader reader = null;
        String[] strings = null;
        HashMap<String, Integer> infos = new HashMap<String, Integer>();

        String processName = mContext.getPackageName();
        /*String execName = "/system/bin/top -d 0.2 -n 1 -m 5";

        try {
            final Process m_process = Runtime.getRuntime().exec(execName);
            reader = new BufferedReader(new InputStreamReader(m_process.getInputStream()), 8192);
            String line;
            while ((line = reader.readLine()) != null) {
                //Log.d(TAG, line);
                //line = line.trim();
                if (line.contains(processName)) {
                    //Log.d(TAG, "Found usage: " + line);
                    strings = line.split(" ");
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                reader = null;
            }
        }*/

        if (strings != null && strings.length > 0) {
            int i = 0;

            //get cpuRate
            for (i = 0; i < strings.length; i++) {
                if (strings[i].contains("%")) {
                    String rate = strings[i].substring(0, strings[i].indexOf("%"));
                    infos.put("cpu", Integer.parseInt(rate));
                    //Log.d(TAG, "rate " + i +" "+ rate + " " + strings.length);
                    break;
                }
            }

            //get vss
            for (i = 0; i < strings.length; i++) {
                if (strings[i].contains("K")) {
                    String vss = strings[i].substring(0, strings[i].indexOf("K"));
                    infos.put("vss", Integer.parseInt(vss));
                    //Log.d(TAG, "vss " + i +" "+ vss + " " + strings.length);
                    break;
                }
            }

            // get rss
            for (i++; i < strings.length; i++) {
                if (strings[i].contains("K")) {
                    String rss = strings[i].substring(0, strings[i].indexOf("K"));
                    infos.put("rss", Integer.parseInt(rss));
                    //Log.d(TAG, "rss " + i +" "+ rss + " " + strings.length);
                    break;
                }
            }
        } else {
            //Log.w(TAG, execName + " return no valid infos.");
            infos.put("cpu", 0);
            infos.put("vss", 0);
            infos.put("rss", 0);
        }

        return infos;
    }

    private String getDeviceModel() {
        String device = Build.HOST + "_" + Build.BRAND + "_" + Build.MODEL + "_" + Build.VERSION.RELEASE;
        if (device.equals("letv-00_MBX_AMLOGIC8726MX_4.1.2")) {
            device = OTT_LETV_C1S;
        } else if (device.equals("acer_rk30sdk_KIUI_4.1.1")) {
            device = OTT_KAIBOER_C9;
        } else if (device.equals("acer_rk31sdk_KIUI-3188_4.2.2")) {
            device = OTT_KAIBOER_F4;
        }

        Log.d(TAG, "==============================================");
        Log.d(TAG, "Device: " + device);
        Log.d(TAG, "==============================================");

        return device;
    }
}
