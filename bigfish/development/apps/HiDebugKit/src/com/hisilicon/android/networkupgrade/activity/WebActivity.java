package com.hisilicon.android.networkupgrade.activity;

import java.util.ArrayList;
import java.util.concurrent.Executors;
import java.util.List;

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
import android.provider.Settings.System;
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

import com.hisilicon.android.networkupgrade.R;
import com.hisilicon.android.hisysmanager.HiSysManager;
public class WebActivity extends Activity
{
    private static final String TAG = "NetworkUpgrade";
    private StorageManager mStorageManager   = null;
    private DownloadManager mDownloadManager = null;

    private String mSystemUpgrade = "System Upgrade";

    private long mDownloadID = -1;
    private String mDownloadPath = null;//"/storage/emulated/0";
    private String mDownloadFile = null;//"/storage/emulated/0/update.zip";

    private WebView webView = null;
    private ProgressDialog progressBar = null;

    private float downloadProcess;

    private boolean downloadFile(final String downloadUrl)
    {
        if (null != downloadUrl)
        {
            Log.d(TAG, "the url is " + downloadUrl);

            String urlName = "";
            String urlType = "";
            int _Index = downloadUrl.lastIndexOf("/");

            if (_Index != -1)
            {
                urlName = downloadUrl.substring(_Index + 1, downloadUrl.length());
            }
            else
            {
                return false;
            }

            if (urlName != null)
            {
                _Index = urlName.lastIndexOf(".");

                if (_Index != -1)
                {
                    urlType = urlName.substring(_Index + 1, urlName.length());
                }
                else
                {
                    return false;
                }
            }

            if (urlType.equals("zip"))
            {
                Log.d(TAG, "the file is " + urlName);

                File file = new File(mDownloadFile);
                if (file.exists())
                {
                    file.delete();
                }

                progressBar.setMessage("  "+urlName);

                final DownloadManager.Request dmReq = new DownloadManager.Request(Uri.parse(downloadUrl));

                dmReq.setMimeType("application/zip");

                dmReq.setDestinationInExternalPublicDir("", urlName);
                WebAddress webAddress;
                try
                {
                    webAddress = new WebAddress(downloadUrl);
                    webAddress.setPath(encodePath(webAddress.getPath()));
                } catch (Exception e) {
                    Log.e("downloadFile", "Exception trying to parse url:" + downloadUrl);
                    return false;
                }
                dmReq.setDescription(webAddress.getHost());
                dmReq.addRequestHeader("cookie", null);
                dmReq.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED);

                dmReq.setShowRunningNotification(true);
                dmReq.setVisibleInDownloadsUi(true);
                mDownloadID = mDownloadManager.enqueue(dmReq);
                new DownloadFile().executeOnExecutor(Executors.newCachedThreadPool(), "");

                return true;
            }
            else
            {
                Log.e("downloadFile", "error type:" + urlType);
                return false;
            }
        }

        return false;
    }

    private BroadcastReceiver mDownloadReciver = new BroadcastReceiver()
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            if (intent.getAction().equals(DownloadManager.ACTION_DOWNLOAD_COMPLETE))
            {
                Bundle extras = intent.getExtras();
                if (mDownloadID == extras.getLong(DownloadManager.EXTRA_DOWNLOAD_ID))
                {
                    Log.d(TAG, "the update.zip donwloaded");
                    String name = checkDownloadSuccess();
                    if (!name.equals(""))
                    {
                        Toast tmpToast = Toast.makeText(WebActivity.this, R.string.network_upgrade_download_success,
                                                        Toast.LENGTH_SHORT);
                        tmpToast.show();

                        File file1 = new File(mDownloadFile);

                        File file2 = new File(name);
                        if (file2.exists() && !name.equals(mDownloadFile))
                        {
                            file2.renameTo(file1);
                            file2.delete();
                        }

                            Log.i(TAG,"update check success");
                            HiSysManager hisys = new HiSysManager();
                            hisys.upgrade(mDownloadPath);
                            Intent newIntent = new Intent("android.intent.action.MASTER_CLEAR");
                            newIntent.putExtra("mount_point", mDownloadPath);
                            sendBroadcast(newIntent);
                    }

                    progressBar.dismiss();
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

        mDownloadPath = Environment.getExternalStorageDirectory().getPath();
        mDownloadFile = Environment.getExternalStorageDirectory().getPath()+"/update.zip";

        webView = (WebView)findViewById(R.id.webView);

        progressBar = new ProgressDialog(WebActivity.this);
        progressBar.setIndeterminate(false);
        progressBar.setCancelable(false);
        progressBar.setTitle(getString(R.string.network_upgrade_begin_download));
        progressBar.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
        progressBar.setMax(100);

        webView.getSettings().setJavaScriptEnabled(true);

        webView.loadUrl("http://10.67.212.148/v5/");

        webView.setWebViewClient(new WebViewClient()
                                 {
                                     @Override
                                     public void onPageStarted(WebView view, String url, Bitmap favicon)
                                     {
                                         super.onPageStarted(view, url, favicon);

                                         //progressBar.show();
                                         //Toast.makeText(WebActivity.this, "onPageStarted", 2).show();
                                     }

                                     @Override
                                     public boolean shouldOverrideUrlLoading(WebView view, String url)
                                     {
                                         Log.i(TAG, "url:" + url);
                                         downloadFile(url);

                                         return super.shouldOverrideUrlLoading(view, url);
                                     }

                                     @Override
                                     public void onPageFinished(WebView view, String url)
                                     {
                                         super.onPageFinished(view, url);

                                         //progressBar.dismiss();
                                         //Toast.makeText(WebActivity.this, "onPageFinished", 2).show();
                                     }

                                     @Override
                                     public void onReceivedError(WebView view, int errorCode,
                                                                 String description, String failingUrl)
                                     {
                                         super.onReceivedError(view, errorCode, description, failingUrl);

                                         //progressBar.dismiss();
                                         Toast.makeText(WebActivity.this, "onReceivedError", 2).show();
                                     }
                                 });
        mDownloadManager = (DownloadManager)getSystemService(DOWNLOAD_SERVICE);

        IntentFilter filter = new IntentFilter(DownloadManager.ACTION_DOWNLOAD_COMPLETE);
        registerReceiver(mDownloadReciver, filter);
    }

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
        if (mDownloadReciver != null)
        {
            unregisterReceiver(mDownloadReciver);
        }

        super.onDestroy();
    }

    private String encodePath(String path)
    {
        char[] chars = path.toCharArray();

        boolean needed = false;
        for (char c : chars)
        {
            if ((c == '[') || (c == ']'))
            {
                needed = true;
                break;
            }
        }

        if (needed == false)
        {
            return path;
        }

        StringBuilder sb = new StringBuilder("");
        for (char c : chars)
        {
            if ((c == '[') || (c == ']'))
            {
                sb.append('%');
                sb.append(Integer.toHexString(c));
            }
            else
            {
                sb.append(c);
            }
        }

        return sb.toString();
    }

    private String checkDownloadSuccess()
    {
        String bRet = "";

        Log.i(TAG, "checkDownload mDownloadID:" + mDownloadID);
        try
        {
            Cursor c = mDownloadManager.query(new DownloadManager.Query().setFilterById(mDownloadID));
            if (null != c)
            {
                c.moveToFirst();
                int iStatus = c.getInt(c.getColumnIndex(DownloadManager.COLUMN_STATUS));
                if (DownloadManager.STATUS_SUCCESSFUL == iStatus)
                {
                    bRet = c.getString(c.getColumnIndex(DownloadManager.COLUMN_LOCAL_FILENAME));
                    Log.i(TAG, "checkDownloadSuccess File:" + bRet);
                    return bRet;
                }

                c.close();
            }
        } catch (Exception ex) {
            Log.i(TAG, "checkDownloadFailed");
        }

        return bRet;
    }


    private class DownloadFile extends AsyncTask <String, Integer, String>
    {
        @Override
        protected String doInBackground(String...sUrl)
        {
            try
            {
                while(true)
                {
                    Cursor c = mDownloadManager.query(new DownloadManager.Query().setFilterById(mDownloadID));
                    if (null != c)
                    {
                        c.moveToFirst();

                        int currentByte = c.getInt(c.getColumnIndex(DownloadManager.COLUMN_BYTES_DOWNLOADED_SO_FAR));

                        int totalByte = c.getInt(c.getColumnIndex(DownloadManager.COLUMN_TOTAL_SIZE_BYTES));

                        c.close();

                        downloadProcess = (float)currentByte / totalByte;

                        downloadProcess = (int)(downloadProcess*100);

                        Log.i(TAG,"downloadProcess:"+downloadProcess);

                        if(currentByte == totalByte)
                            break;

                        Thread.sleep(2000);

                        progressBar.setProgress((int)downloadProcess);

                    }
                }
                return null;
            }
            catch (Exception ex)
            {
                Log.i(TAG, "checkDownloadFailed");
            }
            return null;
        }

        @Override
        protected void onPreExecute()
        {
            super.onPreExecute();
            progressBar.show();
        }
        @Override
        protected void onProgressUpdate(Integer...progress)
        {
            super.onProgressUpdate(progress);
            progressBar.setProgress((int)downloadProcess);
        }
    }
}
