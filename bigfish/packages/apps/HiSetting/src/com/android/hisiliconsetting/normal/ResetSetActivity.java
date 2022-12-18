package com.android.hisiliconsetting.normal;

import java.util.List;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.ProgressDialog;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import com.android.hisiliconsetting.CommonDialog;
import com.android.hisiliconsetting.CommonDialog.OnCallback;
import com.android.hisiliconsetting.R;
import com.hisilicon.android.hisysmanager.HiSysManager;

public class ResetSetActivity extends Activity implements OnClickListener {

    private RelativeLayout layoutDeleteApp;
    private ImageView imageSwith;
    private Button btnReset;
    private boolean deleteApp = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.reset_set_main);
        initView();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.btn_reset:
            showRecoverDialog();
            break;
        case R.id.layout_delete_app:
            if (deleteApp) {
                deleteApp = false;
                imageSwith
                        .setBackgroundResource(R.drawable.setting_second_switch_close);
            } else {
                deleteApp = true;
                imageSwith
                        .setBackgroundResource(R.drawable.setting_second_switch_open);
            }
            break;
        default:
            break;
        }
    }

    private void initView() {
        layoutDeleteApp = (RelativeLayout) findViewById(R.id.layout_delete_app);
        btnReset = (Button) findViewById(R.id.btn_reset);
        imageSwith = (ImageView) findViewById(R.id.reset_switch_btn);

        layoutDeleteApp.setOnClickListener(this);
        btnReset.setOnClickListener(this);

    }

    private void showRecoverDialog() {
        CommonDialog dialog = new CommonDialog(this,
                android.R.style.Theme_Translucent_NoTitleBar_Fullscreen,
                new MyOnCallback());
        dialog.show();
        if (deleteApp) {
            dialog.SetText(getResources().getString(
                    R.string.normal_recovery_hint));
        } else {
            dialog.SetText(getResources().getString(R.string.normal_clear_data));
        }
    }

    private void clearApp() {
        PackageManager pManager = getPackageManager();
        ActivityManager aManager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
        List<PackageInfo> infos = pManager.getInstalledPackages(0);
        for (PackageInfo packageInfo : infos) {
            String packageName = packageInfo.packageName;
            if (!getApplicationInfo().packageName.equals(packageName)
                    && !"android.app.AlertDialog".equals(packageName)) {
                aManager.clearApplicationUserData(packageName, null);
                pManager.deleteApplicationCacheFiles(packageName, null);
            }
        }
    }

    private void deleteApp() {
        HiSysManager hisys = new HiSysManager();
        hisys.reset();
        ResetSetActivity.this.sendBroadcast(new Intent("android.intent.action.MASTER_CLEAR"));
    }

    private class MyOnCallback implements OnCallback {

        @Override
        public void OkcallBack() {
            if (deleteApp)
                deleteApp();
            else {
                ProgressDialog.show(ResetSetActivity.this, null,
                        getResources()
                                .getString(R.string.normal_recovery_msg_7));
                new Thread(new Runnable() {

                    @Override
                    public void run() {
                        clearApp();
                    }
                }).start();
            }
        }

        @Override
        public void CancelcallBack() {

        }

		@Override
		public void MidcallBack() {
			// TODO Auto-generated method stub
		}
    }
}
