/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.ahplayer;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import android.content.Context;
public class ahplayerConfig{
    public String     HWDECODING = "<HWDECODING>";
    public String     VIDEOFPS = "<VIDEOFPS>";
    public String     EPGURL = "<EPGURL>";
    public String     AHSMONITOR = "<AHSMONITOR>";
    public String     PLAYINGSPEED = "<PLAYINGSPEED>";
    private File dir;
    public String ahplayerConfigPath;
    private String filename = "PlayerConfig.txt";
    private Context mContext;
    public ahplayerConfig(Context context)
    {
        mContext = context;
        dir = context.getFilesDir();
        ahplayerConfigPath = dir.getParent() + "/files/" + filename;
    }
    public String getValueByOptionName(String configPath,String optionName,String defaultValue)
    {
        String ret = defaultValue;
        try {
            File file = new File(configPath);
            if(file.exists())
            {
                String temp = "";
                FileInputStream fis = mContext.openFileInput(filename);
                InputStreamReader isr = new InputStreamReader(fis);
                BufferedReader br = new BufferedReader(isr);
                for (int j = 1; (temp = br.readLine()) != null
                        && !temp.equals(optionName); j++) {
                }
                if(temp == null)
                {
                    ret = defaultValue;
                }
                else
                {
                    temp = br.readLine();
                    if(temp!=null)
                    {
                        ret = temp;
                    }
                    else
                    {
                        ret = defaultValue;
                    }
                }
                br.close();
            }
            else
            {
                ret = defaultValue;
            }
        } catch (IOException e) {
            ahplayerMessageBox.show(mContext, "Error", e.getMessage());
        }
        return ret;
    }
    public void config(String configPath,String optionName,String optionValue)
    {
        String temp = "";
        try {
            File file = new File(configPath);
            if(file.exists())
            {
                FileInputStream fis = mContext.openFileInput(filename);
                InputStreamReader isr = new InputStreamReader(fis);
                BufferedReader br = new BufferedReader(isr);
                StringBuffer buf = new StringBuffer();


                for (int j = 1; (temp = br.readLine()) != null
                        && !temp.equals(optionName); j++) {
                    buf = buf.append(temp);
                    buf = buf.append(System.getProperty("line.separator"));
                }
                if(temp == null)
                {
                    buf = buf.append(optionName);
                    buf = buf.append(System.getProperty("line.separator"));
                }
                else
                {
                    buf = buf.append(temp);
                    buf = buf.append(System.getProperty("line.separator"));
                    br.readLine();
                }
                buf = buf.append(optionValue);
                while ((temp = br.readLine()) != null) {
                    buf = buf.append(System.getProperty("line.separator"));
                    buf = buf.append(temp);
                }

                br.close();
                FileOutputStream fos = mContext.openFileOutput(filename, 2);
                PrintWriter pw = new PrintWriter(fos);
                pw.write(buf.toString().toCharArray());
                pw.flush();
                pw.close();
            }
            else
            {
                FileOutputStream fos = mContext.openFileOutput(filename, 2);
                PrintWriter pw = new PrintWriter(fos);
                pw.write(optionName);
                pw.write(System.getProperty("line.separator"));
                pw.write(optionValue);
                pw.write(System.getProperty("line.separator"));
                pw.flush();
                pw.close();
            }
        } catch (IOException e) {
            ahplayerMessageBox.show(mContext, "Error", e.getMessage());
        }
    }
}