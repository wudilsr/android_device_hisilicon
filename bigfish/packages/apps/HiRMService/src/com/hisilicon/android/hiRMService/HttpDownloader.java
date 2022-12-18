package com.hisilicon.android.hiRMService;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;

public class HttpDownloader {
    private URL url = null;
    private Context context;
    private final String TAG = "HttpDownloader";

    public HttpDownloader(Context context) {
        this.context = context;
    }

    public boolean CheckNetWork() {
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
    @SuppressWarnings("finally")
    public int downFile(String urlStr, String path, String fileName) {
        Log.d(TAG, "in downFile");
        InputStream inputStream = null;
		boolean flag = false;
        int ret = -1;
        try {
            while (true) {
                if (CheckNetWork() == true) {
                    break;
                } else {
						flag = true;
                    Thread.sleep(500);
                }
            }
			if(flag)
                Thread.sleep(1000 * 10);
            FileUtil fileUtil = new FileUtil();
            fileUtil.delExistFile(new File(path, fileName).getPath());

            inputStream = getInputStreamFromUrl(urlStr);
            File resultFile = fileUtil.write2SDFromInput(path, fileName,
                    inputStream);
            if (null != resultFile) {
                ret = 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                inputStream.close();
            } catch (Exception e) {
                e.printStackTrace();
                return ret;
            }
            return ret;
        }
    }

    public InputStream getInputStream(String urlStr) {
        Log.d(TAG, "in getInputStream");
        InputStream inputStream = null;
		boolean flag = false;
        try {
            while (true) {
                if (CheckNetWork() == true) {
                    break;
                } else {
					flag = true;
                    Thread.sleep(500);
                }

            }
			if(flag)
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
        HttpURLConnection urlCon = (HttpURLConnection) url.openConnection();
        urlCon.setConnectTimeout(60000);
        urlCon.setReadTimeout(60000);
        InputStream inputStream = urlCon.getInputStream();
        return inputStream;

    }
}
