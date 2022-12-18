package com.hisilicon.android.hiRMService;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.TextView;
import com.hisilicon.android.hisysmanager.HiSysManager;
public class UpgradeActivity extends Activity {
    private Button upGrade;
    private TextView systemVersion_view;
    private TextView latestVersion_view;
    private TextView versionInfo_view;
    private String[] info;
    private String mDownloadPath;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
        setContentView(R.layout.activity_main);
        getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE,
                R.layout.titlebar);
        Intent intent = getIntent();
        if (null == intent) {
            finish();
        } else {
            info = intent.getStringArrayExtra("info");
            mDownloadPath = intent.getStringExtra("path");
        }
        if (null == info || null == mDownloadPath) {
            finish();
        }
        init();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {
            return true;
        }
        if (keyCode == KeyEvent.KEYCODE_HOME && event.getRepeatCount() == 0) {
            return true;
        }
        if (keyCode == KeyEvent.KEYCODE_SETTINGS && event.getRepeatCount() == 0) {
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }

    private void init() {
        systemVersion_view = (TextView) findViewById(R.id.systemVersion);
        latestVersion_view = (TextView) findViewById(R.id.latestVersion);
        versionInfo_view = (TextView) findViewById(R.id.versionInfo);

        upGrade = (Button) findViewById(R.id.download_upgrade);
        upGrade.setOnClickListener(upGradeListener);
        upGrade.requestFocus();

        systemVersion_view.setText(info[0]);
        latestVersion_view.setText(info[1]);
        versionInfo_view.setText(info[4]);
    }

    OnClickListener upGradeListener = new OnClickListener() {

        @Override
        public void onClick(View v) {
                HiSysManager hisys = new HiSysManager();
                hisys.upgrade(mDownloadPath);
            Intent newIntent = new Intent("android.intent.action.MASTER_CLEAR");
            newIntent.putExtra("mount_point", mDownloadPath);
            sendBroadcast(newIntent);
        }
    };
}
