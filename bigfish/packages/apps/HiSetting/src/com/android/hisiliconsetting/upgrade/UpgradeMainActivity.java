package com.android.hisiliconsetting.upgrade;

import java.io.File;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.RelativeLayout;
import android.widget.Toast;
import com.hisilicon.android.hisysmanager.HiSysManager;
import com.android.hisiliconsetting.CommonDialog;
import com.android.hisiliconsetting.R;
import com.android.hisiliconsetting.CommonDialog.OnCallback;

public class UpgradeMainActivity extends Activity implements OnClickListener {
    private final static String TAG = "UpgradeMainActivity";
    private RelativeLayout localLayout;
    private RelativeLayout onlineLayout;
    private String mpath = null;
    private static ProgressDialog progressBar = null;
    private static checkUpdateThread mThread = null;
    private Context mcontent = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.upgrade_main);
        mcontent = this;
        localLayout = (RelativeLayout) findViewById(R.id.upgrade_local);
        onlineLayout = (RelativeLayout) findViewById(R.id.upgrade_online);
        localLayout.setOnClickListener(this);
        onlineLayout.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        Intent intent = null;
        switch (v.getId()) {
        case R.id.upgrade_local:
            FileSelector menu = new FileSelector(this,
                    android.R.style.Theme_Translucent_NoTitleBar_Fullscreen,
                    new FileSelector.OnOperateCallback() {
                        @Override
                        public void callBack(String path) {
                            mpath = path;
                            ShowRecoverDialog();
                        }
                    });
            menu.show();
            break;
        case R.id.upgrade_online:
            intent = new Intent(UpgradeMainActivity.this,
                    OnlineUpgradeActivity.class);
            startActivity(intent);
            break;
        default:
            break;
        }
    }

    final Handler mHandler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
            case 0: {
                String path = (String) msg.obj;
                progressBar = new ProgressDialog(mcontent);
                progressBar.setTitle(UpgradeMainActivity.this
                        .getString(R.string.file_check));
                progressBar.setMessage(UpgradeMainActivity.this
                        .getString(R.string.file_checking));
                progressBar.setCancelable(false);
                progressBar.show();
                mThread = new checkUpdateThread(path);
                mThread.start();
                break;
            }
            case 1: {
                int result = msg.arg1;
                String path = (String) msg.obj;
                progressBar.dismiss();
                if (result == 0) {
                        HiSysManager hisys = new HiSysManager();
                        hisys.upgrade(path);
                    Intent intent = new Intent(
                            "android.intent.action.MASTER_CLEAR");
                    intent.putExtra("mount_point", path);
                    mcontent.sendBroadcast(intent);
                } else if (result == -1) {
                    Toast tmpToast = Toast.makeText(mcontent,
                            R.string.file_check_failed, Toast.LENGTH_SHORT);
                    tmpToast.show();
                }
                break;
            }
            }
        }
    };

    private void ShowRecoverDialog() {
        CommonDialog dialog = new CommonDialog(this,
                android.R.style.Theme_Translucent_NoTitleBar_Fullscreen,
                new OnCallback() {
                    @Override
                    public void OkcallBack() {
                        Message msg = mHandler.obtainMessage(0);
                        msg.obj = mpath;
                        mHandler.sendMessage(msg);
                    }

                    @Override
                    public void CancelcallBack() {
                        // TODO Auto-generated method stub

                    }

					@Override
					public void MidcallBack() {
						// TODO Auto-generated method stub
					}
                });
        dialog.show();
        dialog.setCancelable(false);
        dialog.SetTitle(getResources().getString(R.string.local_title_hint));
        dialog.SetText(getResources().getString(R.string.local_title_confirm));
    }

    private class checkUpdateThread extends Thread {
        public String updatePath = null;

        public checkUpdateThread(String path) {
            this.updatePath = path;
        }

        public void run() {
            checkUpdateFile(updatePath);
        }
    }

    public void checkUpdateFile(String updatePath) {
        File file = new File(updatePath + "/update.zip");
            Log.i(TAG, "CAUpdateFile Check Success!");
            Message msg = mHandler.obtainMessage(1);
            msg.arg1 = 0;
            msg.obj = updatePath;
            mHandler.sendMessage(msg);
        
    }
}
