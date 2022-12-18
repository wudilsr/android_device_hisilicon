package com.hisilicon.android.flashInfo;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import com.hisilicon.android.hisysmanager.HiSysManager;

public class FlashInfo
{
    public String getFlashInfo(int offset, int offlen){
        int len = 0;
        String str="";

        HiSysManager hiSysManager = new HiSysManager();
        hiSysManager.getFlashInfo("deviceinfo", offset, offlen);

        try {
            File file=new File("/mnt/mtdinfo");
            FileInputStream is=new FileInputStream(file);
            int size=is.available();
            byte[] buffer=new byte[size];
            is.read(buffer);
            str=new String(buffer,"UTF-8");
            is.close();
            file.delete();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return str;
    }

    public int setFlashInfo(int offset, int offlen, String info){
        HiSysManager hiSysManager = new HiSysManager();
        return hiSysManager.setFlashInfo("deviceinfo", offset, offlen, info);
    }

}