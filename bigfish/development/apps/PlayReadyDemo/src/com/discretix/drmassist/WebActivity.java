package com.discretix.drmassist;

import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.DownloadManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.AsyncTask;
import android.os.RemoteException;
import android.os.storage.StorageManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;
import android.os.storage.ExtraInfo;
import android.os.storage.IMountService;
import android.os.ServiceManager;
import android.content.ComponentName;
import android.net.WebAddress;
import android.webkit.CookieManager;
import android.os.Environment;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import java.io.File;
import java.io.FileNotFoundException;
import android.net.Uri;
import android.os.SystemProperties;
import android.widget.TextView.BufferType;
import android.database.Cursor;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.graphics.Bitmap;
import android.app.ProgressDialog;
import android.view.MotionEvent;
import android.view.KeyEvent;

import android.drm.DrmInfo;
import android.drm.DrmInfoRequest;
import android.drm.DrmManagerClient;
import com.discretix.drmactions.auxillary.Constants;
import com.discretix.drmactions.auxillary.Utilities;
import com.discretix.drmassist.VideoPlayer;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.net.URLConnection;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import android.os.StrictMode;
import android.os.StrictMode.ThreadPolicy;

public class WebActivity extends Activity
{
    private static final String TAG = "WebActivity";

    private WebView webView = null;

    private static final String ASF_PROTECTION_SYSTEM_IDENTIFIER_OBJECT_GUID = "79f049a40988642ab92e65be0885f95";

    private static final String ASF_CONTENT_PROTECTION_SYSTEM_MICROSOFT_PLAYREADY_GUID =
        "107063f4c33cd42b932b48adf3a6a54";

    private static ProgressDialog progressBar = null;

    final Handler mHandler = new Handler()
    {
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
            case 0:
                {
                    Context mContext = WebActivity.this;
                    progressBar = new ProgressDialog(mContext);
                    progressBar.setTitle(mContext.getString(R.string.app_name));
                    progressBar.setMessage(mContext.getString(R.string.acquireright));
                    progressBar.setCancelable(true);
                    progressBar.show();
                    break;
                }
            case 1:
                {
                    progressBar.dismiss();
                    Toast tmpToast = Toast.makeText(WebActivity.this, "Download Manifest Failed!",Toast.LENGTH_SHORT);
                    tmpToast.show();
                    break;
                }
            case 2:
                {
                    progressBar.dismiss();
                    Toast tmpToast = Toast.makeText(WebActivity.this, "DRM Header Is NULL!",Toast.LENGTH_SHORT);
                    tmpToast.show();
                    break;
                }
            case 3:
                {
                    progressBar.dismiss();
                    Toast tmpToast = Toast.makeText(WebActivity.this, "AcquireRights Success!",Toast.LENGTH_SHORT);
                    tmpToast.show();
                    break;
                }
            case 4:
                {
                    progressBar.dismiss();
                    Toast tmpToast = Toast.makeText(WebActivity.this, "AcquireRights Failed!",Toast.LENGTH_SHORT);
                    tmpToast.show();
                    break;
                }
            }
        }
    };

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.web);

        webView = (WebView)findViewById(R.id.webView);

        webView.getSettings().setJavaScriptEnabled(true);

        //webView.loadUrl("http://10.157.186.84/v5/");

        webView.loadUrl("http://playready.directtaps.net/smoothstreaming/");

        webView.setWebViewClient(new WebViewClient()
                                 {
                                     @Override
                                     public void onPageStarted(WebView view, String url, Bitmap favicon)
                                     {
                                         super.onPageStarted(view, url, favicon);

                                         //progressBar.show();
                                         //Toast.makeText(WebActivity.this, "onPageStarted", 5).show();
                                     }

                                     @Override
                                     public boolean shouldOverrideUrlLoading(WebView view, String url)
                                     {
                                         Log.i(TAG, "url:" + url);
                                         playFile(url);

                                         //return super.shouldOverrideUrlLoading(view, url);
                                         return true;
                                     }

                                     @Override
                                     public void onPageFinished(WebView view, String url)
                                     {
                                         super.onPageFinished(view, url);

                                         //progressBar.dismiss();
                                         //Toast.makeText(WebActivity.this, "onPageFinished", 5).show();
                                     }

                                     @Override
                                     public void onReceivedError(WebView view, int errorCode,
                                                                 String description, String failingUrl)
                                     {
                                         super.onReceivedError(view, errorCode, description, failingUrl);

                                         //progressBar.dismiss();
                                         Toast.makeText(WebActivity.this, "Web Error", 5).show();
                                     }
                                 });
    }

    private void playFile(final String playUrl)
    {
        if (null != playUrl)
        {
            Log.d(TAG, "the url is " + playUrl);
            String urlName = "";
            String urlType = "";
            int _Index = playUrl.lastIndexOf(".");

            if (_Index != -1)
            {
                urlType = playUrl.substring(_Index + 1, playUrl.length());
            }
            else
            {
                return;
            }

            Log.d(TAG, "urlType:" + urlType);

            if (urlType.toLowerCase().equals("ism/manifest"))
            {
                urlName = playUrl;
                urlType ="ismv";

                mThread parseThread = new mThread(urlName,urlType);
                parseThread.start();
            }
        }
    }

    private String parseHeaderObject(String path)
    {
        try
        {
            URL url = new URL(path);

            HttpURLConnection conn = (HttpURLConnection)url.openConnection();

            conn.connect();

            int length = conn.getContentLength();
            InputStream input = conn.getInputStream();

            Log.i("AcquireRights", "------------InputStream---------");
            Log.i("AcquireRights", "length:" + length);

            int count = 0;
            byte bufsize[] = new byte[100];

            input.read(bufsize, 0, 16);

            int numread = input.read(bufsize, 0, 8);

            String size = "";

            Log.i("AcquireRights", "numread:" + numread);

            for (int i = 0, j = numread - 1; i < numread; i++, j--)
            {
                //Log.i("AcquireRights", " " + Integer.toHexString(bufsize[i] & 0xff));
                size += Integer.toHexString(bufsize[j] & 0xff);
            }

            int objectSize = Integer.valueOf(size, 16);
            Log.i("AcquireRights", "objectsize:" + objectSize);

            input.read(bufsize, 0, 6);

            byte buf[] = new byte[objectSize - 16 - 8 - 6];

            input.read(buf, 0, objectSize - 16 - 8 - 6);

            return parseDrmHeaderObject(buf, objectSize - 16 - 8 - 6);
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    private String parseDrmHeaderObject(byte buf[], int len)
    {
        int dataNum = len;
        int offset = 0;

        while (offset < dataNum)
        {
            byte bufID[] = new byte[16];
            System.arraycopy(buf, offset, bufID, 0, 16);
            int bufIDLength = bufID.length;
            String bufIDStr = "";

            Log.i("AcquireRights", "bufIDLength:" + bufIDLength);

            for (int i = 0; i < bufIDLength; i++)
            {
                bufIDStr += Integer.toHexString(bufID[i] & 0xff);
            }

            byte bufSize[] = new byte[8];
            System.arraycopy(buf, offset + 16, bufSize, 0, 8);
            int bufSizeLength = bufSize.length;
            String bufSizeStr = "";

            for (int j = bufSizeLength - 1; j >= 0; j--)
            {
                bufSizeStr += Integer.toHexString(bufSize[j] & 0xff);
            }

            int ObjectSize = Integer.valueOf(bufSizeStr, 16);

            Log.i("AcquireRights", "bufIDStr: " + bufIDStr);
            Log.i("AcquireRights", "offset: " + offset + " objectsize: " + ObjectSize);

            if (bufIDStr.equals(ASF_PROTECTION_SYSTEM_IDENTIFIER_OBJECT_GUID))
            {
                byte drmCheck[] = new byte[16];
                System.arraycopy(buf, offset + 24, drmCheck, 0, 16);
                int drmCheckLength = drmCheck.length;
                String drmCheckStr = "";
                for (int i = 0; i < drmCheckLength; i++)
                {
                    drmCheckStr += Integer.toHexString(drmCheck[i] & 0xff);
                }

                Log.i("AcquireRights", "drmCheckStr: " + drmCheckStr);
                if (drmCheckStr.equals(ASF_CONTENT_PROTECTION_SYSTEM_MICROSOFT_PLAYREADY_GUID))
                {
                    byte drmHeaderLength[] = new byte[2];
                    System.arraycopy(buf, offset + 56, drmHeaderLength, 0, 2);
                    String drmHeaderLengthStr = Integer.toHexString(drmHeaderLength[1]
                                                                    & 0xff)
                                                + Integer.toHexString(drmHeaderLength[0] & 0xff);
                    int drmHeaderSize = Integer.valueOf(drmHeaderLengthStr, 16);
                    Log.i("AcquireRights", "drmHeaderSize: " + drmHeaderSize);
                    byte drmHeader[] = new byte[drmHeaderSize];
                    System.arraycopy(buf, offset + 58, drmHeader, 0, drmHeaderSize);
                    char drmHeaderResult[] = new char[drmHeaderSize / 2];
                    int i = 0;
                    for (int j = 0; j < drmHeader.length; i++, j += 2)
                    {
                        drmHeaderResult[i] = (char)(drmHeader[j] & 0xff);
                    }

                    /*try
                    {
                        String Result = new String(drmHeader,"UTF-16");
                        Log.i("AcquireRights","drmHeader:");
                        Log.i("AcquireRights",""+Result);
                    }
                    catch(IOException e)
                    {
                        e.printStackTrace();
                    }*/

                    String Result = String.valueOf(drmHeaderResult);
                    return Result;
                }
                else
                {
                    Log.e("AcquireRights", "IT'S NOT MICROSOFT PLAYREADY PROTECTION SYSTEM!");
                }

                return null;
            }

            offset += ObjectSize;
        }

        return null;
    }

    /**http download*/
    private static boolean httpDownload(String httpUrl,String saveFile)
    {
        ThreadPolicy tp = ThreadPolicy.LAX;
	 StrictMode.setThreadPolicy(tp);

        int bytesum = 0;
        int byteread = 0;

        URL url = null;
	 try
        {
            url = new URL(httpUrl);
	 }
        catch (MalformedURLException e1)
        {
            e1.printStackTrace();
	     return false;
	 }

        URLConnection conn = null;
        InputStream inStream = null;
        FileOutputStream fs = null;
        try
        {
            conn = url.openConnection();
            inStream = conn.getInputStream();
            fs = new FileOutputStream(saveFile);

            byte[] buffer = new byte[1204];
            while ((byteread = inStream.read(buffer)) != -1)
            {
                bytesum += byteread;
                Log.i(TAG, "Downloaded : " + bytesum);
                fs.write(buffer, 0, byteread);
            }
            return true;
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
            return false;
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return false;
        }
        finally
        {
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

    private class mThread extends Thread
    {
        String url;
        String type;

        public mThread(String url,String type)
        {
            this.url = url;
            this.type = type;
        }
        @Override
        public void run()
        {
            ThreadPolicy tp = ThreadPolicy.LAX;
            StrictMode.setThreadPolicy(tp);

            Log.i("AcquireRights", "mThread start!");

            Context mContext = WebActivity.this;

            Message msg = mHandler.obtainMessage(0);
            mHandler.sendMessage(msg);

            final String downloadPath = getCacheDir().getPath() + "/app.ismc";

	     File f = new File(downloadPath);
	     boolean ret1 = f.setReadable(true, false);
	     boolean ret2 = f.setWritable(true, false);
	     Log.i(TAG, "File:setReadable:" + ret1 + "   setWritable: " + ret2);

	     if (!httpDownload(url, downloadPath))
            {
                Log.i(TAG, "Download Manfest Failed!");
                msg = mHandler.obtainMessage(1);
                mHandler.sendMessage(msg);
                return;
	     }

           DrmManagerClient drmClient_header = new DrmManagerClient(WebActivity.this);
	     DrmInfoRequest request_header = new DrmInfoRequest(DrmInfoRequest.TYPE_RIGHTS_ACQUISITION_INFO, Utilities.extension2mimeType(this.type.toLowerCase()));
	     DrmInfo response_header;
	     String HeaderStr = null;

	     request_header.put(Constants.DRM_ACTION, Constants.DRM_ACTION_GET_DRM_HEADER);
	     request_header.put(Constants.DRM_DATA, downloadPath);

	     // get header
	     response_header = drmClient_header.acquireDrmInfo(request_header);
	     drmClient_header.release();
	     if ( null == response_header || !response_header.get(Constants.DRM_STATUS).equals("ok") )
	     {
	        Log.e(TAG, "Get DRM Header Failed!");
              msg = mHandler.obtainMessage(2);
              mHandler.sendMessage(msg);
              VideoPlayer.play(WebActivity.this, this.url);
		 return;
	     }
	     HeaderStr = (String)response_header.get(Constants.DRM_DATA);

            //String HeaderStr = parseHeaderObject(this.url);
            Log.i("AcquireRights", "DrmHeaderResult:");
            Log.i("AcquireRights", "" + HeaderStr);

            DrmInfoRequest request = new DrmInfoRequest(DrmInfoRequest.TYPE_RIGHTS_ACQUISITION_INFO,
                                                        Utilities.extension2mimeType(this.type.toLowerCase()));
            DrmManagerClient drmClient = new DrmManagerClient(WebActivity.this);

            //prepare generate license challenge

            request.put(Constants.DRM_ACTION, Constants.DRM_OP_CODE_RIGHTS_GENERATE_LIC_CHALLENGE);

            request.put(Constants.DRM_HEADER, HeaderStr);

            DrmInfo response = drmClient.acquireDrmInfo(request);

            if ((null == response) || !response.get(Constants.DRM_STATUS).equals("ok"))
            {
                Log.e("AcquireRights", "DrmManagerClient::AcquireRights failed");
                msg = mHandler.obtainMessage(4);
                mHandler.sendMessage(msg);
                return;
            }

            Log.i("AcquireRights", "acquireDrmInfo returned " + response.get(Constants.DRM_STATUS));

            String challenge = response.get(Constants.DRM_DATA).toString();
            String laUrl = response.get(Constants.LA_URL).toString();

            if (laUrl.isEmpty() || challenge.isEmpty())
            {
                Log.e("AcquireRights","DrmManagerClient::AcquireRights failed, laUrl or chanllenge are invalid");
                msg = mHandler.obtainMessage(4);
                mHandler.sendMessage(msg);
                return;
            }

            // send to server
            Log.i("AcquireRights", " LA_URL = " + laUrl);

            try
            {
                URL obj;
                obj = new URL(laUrl);
                HttpURLConnection con = (HttpURLConnection) obj.openConnection();

                //add reuqest header
                con.setRequestMethod("POST");
                con.setRequestProperty("Content-Type", "text/xml; charset=utf-8");
                con.setRequestProperty("SOAPAction",
                                       "http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense");

                // Send post request
                con.setDoOutput(true);
                DataOutputStream wr = new DataOutputStream(con.getOutputStream());
                wr.writeBytes(challenge);
                wr.flush();
                wr.close();

                int responseCode = con.getResponseCode();
                //System.out.println("\nSending 'POST' request to URL : " + laUrl);
                //System.out.println("Response Code : " + responseCode);

                if (responseCode != 200)
                {
                    msg = mHandler.obtainMessage(4);
                    mHandler.sendMessage(msg);
                    return;
                }

                //process response
                BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
                String inputLine;
                StringBuffer Httpresponse = new StringBuffer();

                while ((inputLine = in.readLine()) != null)
                {
                    Httpresponse.append(inputLine);
                }

                in.close();
                con.disconnect();

                //print result
                //System.out.println(Httpresponse.toString());
                request.put(Constants.DRM_ACTION, Constants.DRM_ACTION_PROCESS_LIC_RESPONSE);
                request.put(Constants.DRM_DATA, Httpresponse.toString());

                response = drmClient.acquireDrmInfo(request);

                if ((null == response) || !response.get(Constants.DRM_STATUS).equals("ok"))
                {
                    Log.e("AcquireRights","DrmManagerClient::AcquireRights process license response failed");
                    msg = mHandler.obtainMessage(4);
                    mHandler.sendMessage(msg);
                    return;
                }

                Log.i("AcquireRights", "acquireDrmInfo returned "+response.get(Constants.DRM_STATUS));

                if(response.get(Constants.DRM_DATA) == null)
                {
                    Log.i("AcquireRights","response.get(Constants.DRM_DATA) == null");
                    msg = mHandler.obtainMessage(3);
                    mHandler.sendMessage(msg);
                    VideoPlayer.play(WebActivity.this, this.url);
                    return;
                }
                // send Ack to server
                String ack = response.get(Constants.DRM_DATA).toString();

                if (ack.length() == 0)
                {
                    msg = mHandler.obtainMessage(3);
                    mHandler.sendMessage(msg);
                    VideoPlayer.play(WebActivity.this, this.url);
                    return;
                }

                Log.i("AcquireRights", "acquireDrmInfo requires to send ack");
                HttpURLConnection con2 = (HttpURLConnection) obj.openConnection();

                //add reuqest header
                con2.setRequestMethod("POST");
                con2.setRequestProperty("Content-Type", "text/xml; charset=utf-8");
                // Send post request
                con2.setDoOutput(true);

                DataOutputStream wr2 = new DataOutputStream(con2.getOutputStream());
                wr2.writeBytes(ack);
                wr2.flush();
                wr2.close();

                responseCode = con2.getResponseCode();
                //System.out.println("\nSending 'POST' request to URL : " + laUrl);
                //System.out.println("Response Code : " + responseCode);

                if (responseCode != 200)
                {
                    msg = mHandler.obtainMessage(4);
                    mHandler.sendMessage(msg);
                    return;
                }

                //process response
                BufferedReader in2 = new BufferedReader(
                    new InputStreamReader(con2.getInputStream()));
                String inputLine2;
                StringBuffer Httpresponse2 = new StringBuffer();

                while ((inputLine2 = in2.readLine()) != null)
                {
                    Httpresponse2.append(inputLine2);
                }

                in2.close();
                con2.disconnect();

                // process ack response
                request.put(Constants.DRM_ACTION, Constants.DRM_ACTION_PROCESS_LIC_ACK_RESPONSE);
                request.put(Constants.DRM_DATA, Httpresponse2.toString());

                response = drmClient.acquireDrmInfo(request);

                if ((null == response) || !response.get(Constants.DRM_STATUS).equals("ok"))
                {
                    Log.e("AcquireRights", "DrmManagerClient::AcquireRights process ack response failed");
                    msg = mHandler.obtainMessage(4);
                    mHandler.sendMessage(msg);
                    return;
                }

                Log.i("AcquireRights", "acquireDrmInfo returned " + response.get(Constants.DRM_STATUS));
            } catch (MalformedURLException e1) {
                e1.printStackTrace();
            } catch (IOException e1) {
                e1.printStackTrace();
            }

            Log.i("AcquireRights", "DrmManagerClient::AcquireRights AcquireRights SUCCESS");
            msg = mHandler.obtainMessage(3);
            mHandler.sendMessage(msg);

            VideoPlayer.play(WebActivity.this, this.url);
        }
    };

    @Override
    protected void onResume()
    {
        super.onResume();
    }

    @Override
    protected void onPause()
    {
        super.onPause();
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
    }
}
