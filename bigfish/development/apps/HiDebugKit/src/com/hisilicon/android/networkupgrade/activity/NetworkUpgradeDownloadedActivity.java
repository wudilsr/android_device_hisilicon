package com.hisilicon.android.networkupgrade.activity;

import android.app.Activity;
import android.app.DownloadManager;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.util.Log;
import android.widget.Toast;
import android.provider.Settings.System;
import com.hisilicon.android.networkupgrade.R;
import com.hisilicon.android.hisysmanager.HiSysManager;
public class NetworkUpgradeDownloadedActivity extends Activity
{
    private static final String TAG = "NetworkUpgradeDownloadedActivity";
    private long mDownloadID = -1;
    private String mDownloadPath = "/mnt/sdcard";
    private long mLogoID = -1;
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        // TODO Auto-generated method stub
        super.onCreate(savedInstanceState);

        Intent intent = getIntent();

        /*String FILENAME = "download_info";
        SharedPreferences prf = getPreferences(MODE_PRIVATE);
        String s = prf.getString(FILENAME, null);*/

        if (checkDownloadSuccess())
        {
            Toast tmpToast = Toast.makeText(this, R.string.network_upgrade_download_success, Toast.LENGTH_SHORT);
		tmpToast.show();

		    HiSysManager hisys = new HiSysManager();
            hisys.upgrade(mDownloadPath);
            Intent newIntent = new Intent("android.intent.action.MASTER_CLEAR");
            newIntent.putExtra("mount_point", mDownloadPath);
            sendBroadcast(newIntent);
        }
        else
        {
            Toast tmpToast = Toast.makeText(this, R.string.network_upgrade_download_failed, Toast.LENGTH_SHORT);
		tmpToast.show();
            /*setContentView(R.layout.net_upgrade_download_error);
            Button btnOk = (Button) this.findViewById(R.id.network_upgrade_err_okay);
            btnOk.setOnClickListener(new View.OnClickListener()
                                     {
                                         @Override
                                         public void onClick(View arg0)
                                         {
                                             // TODO Auto-generated method stub
                                             finish();
                                         }
                                     }
            );*/
        }
    }

    private boolean checkDownloadSuccess()
    {
        boolean bRet = false;

        DownloadManager mgr = (DownloadManager)getSystemService(DOWNLOAD_SERVICE);

        Log.i("checkDownloadSuccess", "mDownloadID:" + mDownloadID);
        try
        {
            Cursor c = mgr.query(new DownloadManager.Query().setFilterById(mDownloadID));
            if (null != c)
            {
                c.moveToFirst();
                int iStatus = c.getInt(c.getColumnIndex(DownloadManager.COLUMN_STATUS));
                if (DownloadManager.STATUS_SUCCESSFUL == iStatus)
                {
                    bRet = true;
                }

                c.close();
            }
        } catch (Exception ex) {
            Log.i("checkDownloadSuccess", "");
        }

        return bRet;
    }
}
