package com.android.hisiliconsetting.upgrade;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;

public class HttpDownloader {

    private final String TAG = "HttpDownloader";
    private Context context;
    private URL url = null;
    private HttpURLConnection urlCon;
    private boolean isCheckNetWork = true;

    public HttpDownloader(Context context) {
        this.context = context;
    }

    private boolean CheckNetWork() {
        ConnectivityManager connectivityManager = (ConnectivityManager) context
                .getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo info = connectivityManager.getActiveNetworkInfo();
        if (info == null || !info.isAvailable()) {
            return false;
        } else {
            return true;
        }
    }

    /**
     * @param urlStr
     * @param path
     * @param fileName
     * @return 0-success,-1-fail,1-existed
     */
    public int downFile(String urlStr, String path, String fileName) {
        Log.d(TAG, "in downFile");
        boolean flag = false;
        InputStream is = null;
        int ret = -1;
        try {
            while (isCheckNetWork) {
                if (CheckNetWork() == true) {
                    break;
                } else {
                    flag = true;
                    Thread.sleep(500);
                }
            }
            if (flag)
                Thread.sleep(1000 * 10);

            if(isCheckNetWork){
                is = getInputStreamFromUrl(urlStr);
                File resultFile = write2SDFromInput(path, fileName, is);
                if (null != resultFile) {
                    ret = 0;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                is.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return ret;
    }

    public InputStream getInputStream(String urlStr) {
        Log.d(TAG, "in getInputStream");
        boolean flag = false;
        InputStream inputStream = null;
        try {
            while (true) {
                if (CheckNetWork() == true) {
                    break;
                } else {
                    flag = true;
                    Thread.sleep(500);
                }

            }
            if (flag)
                Thread.sleep(1000 * 10);
            inputStream = getInputStreamFromUrl(urlStr);

        } catch (Exception e) {
            e.printStackTrace();
            inputStream = null;
        }
        return inputStream;
    }

    public InputStream getInputStreamFromUrl(String urlStr)
            throws MalformedURLException, IOException {
        url = new URL(urlStr);
        urlCon = (HttpURLConnection) url.openConnection();
        urlCon.setConnectTimeout(60 * 1000);
        urlCon.setReadTimeout(60 * 1000);
        InputStream inputStream = urlCon.getInputStream();
        return inputStream;

    }

    public File write2SDFromInput(String path, String fileName,
            InputStream input) {
        File file = null;
        OutputStream os = null;
        int size = 0;
        try {
            file = new File(path, fileName);
            if (file.exists())
                file.delete();
            file.createNewFile();
            os = new FileOutputStream(file);
            byte buffer[] = new byte[4 * 1024];
            while ((size = input.read(buffer)) != -1) {
                os.write(buffer, 0, size);
            }
            os.flush();
        } catch (Exception e) {
            file.delete();
            file = null;
            e.printStackTrace();
        } finally {
            try {
                os.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return file;
    }

    public void disConnect() {
        isCheckNetWork = false;
        if (null != urlCon)
            urlCon.disconnect();
    }
}