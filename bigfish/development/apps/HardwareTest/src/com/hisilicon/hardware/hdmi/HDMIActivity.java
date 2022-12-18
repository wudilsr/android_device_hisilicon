package com.hisilicon.hardware.hdmi;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import com.hisilicon.hardware.CommonActivity;
import com.hisilicon.hardware.util.Common;
import com.hisilicon.hardware.util.SelectFileAcvitity;
import com.hisilicon.hardwaretest.R;
import com.hisilicon.android.HiDisplayManager;
import android.os.SystemProperties;

public class HDMIActivity extends CommonActivity implements OnClickListener {

    private Button btn_start_test;
    private Button btn_file_path;
    private TextView text_file_path;
    private String filePath;
    private int testMode;
    private HiDisplayManager dManager;
    private int mHdcp_enable = 0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_hdmi);
        dManager = new HiDisplayManager();
        mHdcp_enable = dManager.getOptimalFormatEnable();
        SystemProperties.set("persist.sys.hdcp.auth","1");
        initView();
    }

    @Override
    protected void onResume() {
        if(mHdcp_enable==1){
            dManager.setOptimalFormatEnable(0);
        }
        if (isEmptyString(filePath))
            text_file_path.setText("");
        else
            text_file_path.setText(filePath);

        super.onResume();
    }
    @Override
    protected void onDestroy() {
        dManager.setOptimalFormatEnable(mHdcp_enable);
        SystemProperties.set("persist.sys.hdcp.auth","0");
        super.onDestroy();
    }

    @Override
    public void onClick(View v) {
        Intent intent = null;
        switch (v.getId()) {
        case R.id.button_file_path:
            intent = new Intent(HDMIActivity.this, SelectFileAcvitity.class);
            intent.putExtra("path", getStoragePath());
            intent.putExtra("activity", "HDMIActivity");
            startActivityForResult(intent, Common.REQUEST_CODE);
            break;
        case R.id.button_start_test:
            if (isEmptyString(filePath))
                showMessageDialog(R.string.select_file_first);
            else {
                testMode = getFileType(filePath);
                if (NORMAL_PLAY == testMode)
                    showMessageDialog(R.string.select_file_type2);
                else {
                    intent = new Intent(HDMIActivity.this,
                            HDMITestActivity.class);
                    intent.putExtra("filePath", filePath);
                    intent.putExtra("testMode", testMode);
                    startActivity(intent);
                }
            }
            break;
        default:
            break;
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (RESULT_OK == resultCode && Common.REQUEST_CODE == requestCode) {
            filePath = data.getStringExtra("path");
            text_file_path.setText(filePath);
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    private void initView() {
        text_file_path = (TextView) findViewById(R.id.text_file_path);
        btn_start_test = (Button) findViewById(R.id.button_start_test);
        btn_file_path = (Button) findViewById(R.id.button_file_path);
        btn_start_test.setOnClickListener(this);
        btn_file_path.setOnClickListener(this);
    }

}