package com.hisilicon.android.videoplayer.utility;

import java.io.File;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.net.URLConnection;
import java.net.MalformedURLException;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.ArrayList;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;
import android.os.StrictMode;
import android.os.StrictMode.ThreadPolicy;

/**
 * Query subtitle information according to file hash and file name
 * @author tobyPan
 *
 */
public class ShooterHttpDownload {
	private static final String TAG = "ShooterHttpDownload";
	private DownloadResultListener mDownloadListener = null;
	private HttpDownloadThread mHttpDownloadThread = null;

	public ShooterHttpDownload(DownloadResultListener ls){
		mDownloadListener = ls;
	}

	public void httpDownloadSubTitie(String url, String path){
             mHttpDownloadThread = new HttpDownloadThread(url, path);
		mHttpDownloadThread.start();
	}

       public void stopDownloadSubTitie(){
             if(mHttpDownloadThread != null)
		    mHttpDownloadThread.stop();
	}
	private class HttpDownloadThread extends Thread
       {
		private String mURL = "";
		private String mPath = "";

		HttpDownloadThread(String url, String path)
             {
			this.mURL = url;
			this.mPath = path;
		}

		/**
		 * Trust every server - don't check for any certificate
		 */
		private void trustAllHosts()
		{
			final String TAG = "trustAllHosts";
			// Create a trust manager that does not validate certificate chains
			TrustManager[] trustAllCerts = new TrustManager[] { new X509TrustManager()
			{

				public java.security.cert.X509Certificate[] getAcceptedIssuers() {
					return new java.security.cert.X509Certificate[] {};
				}

				public void checkClientTrusted(X509Certificate[] chain, String authType) throws CertificateException {
					Log.i(TAG, "checkClientTrusted");
				}

				public void checkServerTrusted(X509Certificate[] chain, String authType) throws CertificateException {
					Log.i(TAG, "checkServerTrusted");
				}
			} };

			// Install the all-trusting trust manager
			try
			{
				SSLContext sc = SSLContext.getInstance("TLS");
				sc.init(null, trustAllCerts, new java.security.SecureRandom());
				HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());
			}
                    catch (Exception e)
                    {
				e.printStackTrace();
			}
		}

		@Override
		public void run()
		{
		       trustAllHosts();

                    File file = new File(mPath);
                    if(file.exists())
                        file.delete();

                    Log.i(TAG,"mURL:"+mURL);
                    Log.i(TAG,"mPath:"+mPath);

                    ThreadPolicy tp = ThreadPolicy.LAX;
                    StrictMode.setThreadPolicy(tp);

                    int bytesum = 0;
                    int byteread = 0;

                    URL url = null;
                    try
                    {
                        url = new URL(mURL);
                    }
                    catch (MalformedURLException e)
                    {
                        e.printStackTrace();
                        return;
                    }

                    URLConnection conn = null;
                    InputStream inStream = null;
                    FileOutputStream fs = null;
                    try
                    {
                        conn = url.openConnection();
                        inStream = conn.getInputStream();
                        fs = new FileOutputStream(mPath);

                        byte[] buffer = new byte[1204];
                        while ((byteread = inStream.read(buffer)) != -1)
                        {
                            bytesum += byteread;
                            Log.i(TAG, "Downloaded:" + bytesum);
                            fs.write(buffer, 0, byteread);
                        }
                        return;
                    }
                    catch (FileNotFoundException e)
                    {
                        mPath = null;
                        e.printStackTrace();
                        return;
                    }
                    catch (IOException e)
                    {
                        mPath = null;
                        e.printStackTrace();
                        return;
                    }
                    finally
                    {
                        mDownloadListener.onDownloadResult(mPath);
                        try
                        {
                            if (fs != null)
                            {
                                fs.close();
                                fs = null;
                            }
                        }
                        catch (IOException e)
                        {
                            e.printStackTrace();
                        }
                    }
		}
	}

	public static interface DownloadResultListener{
		void onDownloadResult(String path);
	}
}
