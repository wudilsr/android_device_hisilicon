package com.hisilicon.uvmos.monitor;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import android.content.Intent;

public class Util {

    public static final String DIR_PATH_1 = "/data/UV-MOS";
    public static final String DIR_PATH_2 = "/data/sme";
    public static final String FILE_PATH_INPUT = "/data/UV-MOS/UvMOSInputPara";
    public static final String FILE_PATH_ENTER = "/data/sme/PlayEnterFile.log";
    public static final String FILE_PATH_QUIT = "/data/sme/PlayQuitFile.log";

    public static final String M_MEDIA_PLAY_ACTION = "MEDIA_PLAY_UVMOS_MONITOR_MESSAGE";
    public static final String M_VIDEO_INFO = "Hiplayer_Video_Info";
    public static final String M_MESSAGE_STATUS = "PLAYER_STATUS";
    public static final String M_MESSAGE_PLAY_PREPARE = "UVMOS_PLAY_PREPARE";
    public static final String M_MESSAGE_PLAY_START = "UVMOS_PLAY_START";
    public static final String M_MESSAGE_PLAY_COMPLETE = "UVMOS_PLAY_COMPLETE";
    public static final String M_MESSAGE_VIDEO_INFO = "UVMOS_VIDEO_INFO";
    public static final String M_BUFFER_START = "UVMOS_BUFFER_START";
    public static final String M_BUFFER_END = "UVMOS_BUFFER_END";
    public static final String M_SEEK_START = "UVMOS_SEEK_START";
    public static final String M_SEEK_END = "UVMOS_SEEK_COMPLETE";
    public static final String M_PLAYER_TYPE = "PlayerType";
    public static final String M_BUFFER_START_TIME = "StallingHappenTime";
    public static final String M_BUFFER_END_TIME = "StallingRestoreTime";
    public static final String M_SEEK_START_TIME = "SeekStartTime";
    public static final String M_SEEK_END_TIME = "SeekCompleteTime";
    public static final String M_SESSION_ID = "ID";// int
    public static final String M_URL = "VideoURL";// string
    public static final String M_START_TIME = "StartPlayTime";// int
    public static final String M_STOP_TIME = "StopPlayTime";// int
    public static final String M_VIDEO_RATE = "VideoRate";// long
    public static final String M_PLAY_TIME = "DisplayFirstFrameTime";// int
    public static final String M_MEDIA_WIDTH = "MediaWidthResolution";// long
    public static final String M_MEDIA_HEIGHT = "MediaHeightResolution";// long
    public static final String M_FRAME_RATE = "FrameRate";// int
    public static final String M_ENCODE_TYPE = "EncodeType";// string

    private static final SimpleDateFormat format = new SimpleDateFormat(
            "yyyy-MM-dd HH:mm:ss.SSS", Locale.getDefault());

    public static String formatTime(Intent intent, String key) {
        long time = -1;
        if (null != intent) {
            time = intent.getLongExtra(key, System.currentTimeMillis());
        }
        return formatTime(time);
    }

    public static String formatTime(long time) {
        try {
            Date date = new Date(time);
            return formatTime(date);
        } catch (Exception e) {
        }
        return formatTime(new Date(System.currentTimeMillis()));
    }

    public static String formatTime(Date date) {
        return format.format(date);
    }

    public static void createFile(String fileName) {
        try {
            File file = new File(fileName);
            if (file.exists()) {
                file.delete();
            }
            file.createNewFile();
            chmod(fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void initFile() {
        try {
            File dirPath1 = new File(DIR_PATH_1);
            if (!dirPath1.exists()) {
                dirPath1.mkdirs();
                chmod(DIR_PATH_1);
            }

            File dirPath2 = new File(DIR_PATH_2);
            if (!dirPath2.exists()) {
                dirPath2.mkdirs();
                chmod(DIR_PATH_2);
            }

            File enterFile = new File(FILE_PATH_ENTER);
            if (enterFile.exists()) {
                enterFile.delete();
            }
            enterFile.createNewFile();
            chmod(FILE_PATH_ENTER);

            File quitFile = new File(FILE_PATH_QUIT);
            if (quitFile.exists()) {
                quitFile.delete();
            }
            quitFile.createNewFile();
            chmod(FILE_PATH_QUIT);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void clearInputFile() {
        File parentFile = new File(DIR_PATH_1);
        if (parentFile.exists()) {
            File[] files = parentFile.listFiles();
            for (File file : files) {
                file.delete();
            }
        }
    }

    public static boolean writeFile(String filePath, String content,
            boolean append) {
        if (isEmpty(content)) {
            return false;
        }
        FileWriter fileWriter = null;
        try {
            makeDirs(filePath);
            chmod(filePath);
            fileWriter = new FileWriter(filePath, append);
            fileWriter.write(content);
            fileWriter.close();
            return true;
        } catch (IOException e) {
            throw new RuntimeException("IOException occurred. ", e);
        } finally {
            if (fileWriter != null) {
                try {
                    fileWriter.close();
                } catch (IOException e) {
                    throw new RuntimeException("IOException occurred. ", e);
                }
            }
        }
    }

    private static void chmod(String filePath) {
        try {
            String command = "chmod 777 " + filePath;
            Runtime runtime = Runtime.getRuntime();
            runtime.exec(command);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static boolean makeDirs(String filePath) {
        String folderName = getFolderName(filePath);
        if (isEmpty(folderName)) {
            return false;
        }

        File folder = new File(folderName);
        return (folder.exists() && folder.isDirectory()) ? true : folder
                .mkdirs();
    }

    private static String getFolderName(String filePath) {

        if (isEmpty(filePath)) {
            return filePath;
        }

        int filePosi = filePath.lastIndexOf(File.separator);
        return (filePosi == -1) ? "" : filePath.substring(0, filePosi);
    }

    private static boolean isEmpty(CharSequence str) {
        return (str == null || str.length() == 0);
    }

}