package com.hisilicon.android.HiCustomizeSettings;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import com.hisilicon.android.hisysmanager.HiSysManager;

public class FlashInfo
{
    public static String getFlashInfo(int offset, int offlen){
        int len = 0;
        String str="";
        HiSysManager hisys = new HiSysManager();
        hisys.getFlashInfo("warpflag",offset,offlen);
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

    public static int setFlashInfo(int offset, int offlen, int info){
    	HiSysManager hisys = new HiSysManager();
        int ret = hisys.setFlashInfo("warpflag",offset,offlen,String.valueOf(info));
        return ret;
    }
}

