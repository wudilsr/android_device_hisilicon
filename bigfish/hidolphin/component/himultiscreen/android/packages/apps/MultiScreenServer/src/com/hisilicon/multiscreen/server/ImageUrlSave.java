package com.hisilicon.multiscreen.server;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

import android.net.Uri;
import android.util.Log;

/**
 * ImageUrlSave.<br>
 * 2012-8-6 modified - get type from URL for saving image data in the file.
 */
public class ImageUrlSave
{

    private byte[] imageData = null;

    /**
     * 存储图片，放在服务端本地临时文件 save image as temporary file in local path.
     * @param img_url - 图片URL
     * @return - 存储图片的URI，失败返回空 URI of image file, or null if it's failed
     */
    public Uri getImagePath(String img_url)
    {

        Long time1 = System.currentTimeMillis();
        File file;

        // url2bytes
        imageData = loadImageUrl(img_url);
        String strMIME = getMIME(img_url);

        if (imageData == null)
        {
            LogTool.e("imageData is null");
            return null;
        }
        if (strMIME == null)
        {
            /**
             * 获取文件类型失败 getting MIME of file fail
             */
            LogTool.e("get type of file failed");
            return null;
        }

        String fileType = strMIME.replace("image/", "");
        try
        {
            file = File.createTempFile("pic", "." + fileType);
            if (file.delete() == false)
            {
                 LogTool.e("create files failed");
            }
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
            /**
             * 建立临时文件失败，手动建立文件 create file failed, and create it manually
             */
            file = new File("/mnt/sdcard/pic" + time1 + "." + "jpg");
            LogTool.e("create temp file failed");

        }
        LogTool.i("create temp file success");
        /**
         * 写入文件 save bytes in file
         */
        LogTool.d("file.getPath()=" + file.getPath());
        if (!writeFile(file.getPath(), imageData))
        {
            // file.toURI().toURL().getPath()
            /**
             * 写入失败返回空 return null if it's failed
             */
            return null;

        }
        return Uri.fromFile(file);
    }

    /**
     * URL转字节 image URL to bytes
     * @param url - 图片URL
     * @return - 图片字节数据 number of bytes of image
     */
    private byte[] loadImageUrl(String url)
    {
        URL link;
        try
        {
            link = new URL(url);

        }
        catch (MalformedURLException e)
        {
            LogTool.e(e.getMessage());
            return null;
        }

        HttpURLConnection con;
        byte[] image = null;
        try
        {
            con = (HttpURLConnection) link.openConnection();
            if (null == con)
            {
                LogTool.e("openConnection is null");
                return null;
            }
            con.setDoInput(true);
            con.setConnectTimeout(5000);
            con.setRequestMethod("GET");
            if (con.getResponseCode() != 200)
            {
                LogTool.e("get response code is not 200");
                return null;
            }
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
            return null;
        }

        InputStream is;
        try
        {
            is = con.getInputStream();
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
            con.disconnect();
            return null;
        }

        ByteArrayOutputStream out = new ByteArrayOutputStream();
        try
        {
            int readlen = 0;
            int totalLen = 0;
            byte[] buffer = new byte[4096];
            while (readlen != -1)
            {
                readlen = is.read(buffer);
                totalLen += readlen;
                out.write(buffer, 0, readlen);
            }
            image = out.toByteArray();
            LogTool.v("get bitmap length:" + image.length + ", totalLen" + totalLen);
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }

        try
        {
            out.close();
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }
        try
        {
            is.close();
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }
        con.disconnect();

        return image;
    }

    /**
     * 获取URL的MIME类型 get MIME of URL
     * @param strUrl - URL
     * @return - MIME
     */
    public String getMIME(String strUrl)
    {
        URL url;

        try
        {
            url = new URL(strUrl);
        }
        catch (MalformedURLException e1)
        {
            LogTool.e(e1.getMessage());
            return null;
        }

        try
        {
            HttpURLConnection urlconnection = (HttpURLConnection) url.openConnection();
            if (null == urlconnection)
            {
                LogTool.e("urlconnection is null");
                return null;
            }
            urlconnection.setConnectTimeout(3000);
            urlconnection.setRequestMethod("GET");
            urlconnection.connect();
            if (urlconnection.getResponseCode() == 200)
            {
                /**
                 * 根据URL猜测文件类型MIME get content type(MIME) of file in URL
                 */
                return urlconnection.getContentType();
            }
            urlconnection.disconnect();
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }
        return null;
    }

    /**
     * 写入文件 write file
     * @param fileName - 写入路径 path fo file
     * @param data - 数据
     * @return - 成功标识 true mains successful or false mains failed
     */
    private boolean writeFile(String fileName, byte[] data)
    {
        FileOutputStream fout;
        boolean result = true;
        try
        {
            fout = new FileOutputStream(fileName);
        }
        catch (FileNotFoundException e)
        {
            LogTool.e(e.getMessage());
            return false;
        }

        try
        {
            fout.write(data);
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
            result = false;
        }
        try
        {
            fout.close();
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
            result = false;
        }
        return result;
    }

}
