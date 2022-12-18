package com.hisilicon.hardware;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.SystemProperties;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

import com.hisilicon.hardware.cvbs.CVBSActivity;
import com.hisilicon.hardware.hdmi.HDMIActivity;
import com.hisilicon.hardware.usb.USBActivity;
import com.hisilicon.hardwaretest.R;

public class MainActivity extends CommonActivity implements OnClickListener {

    private Button btn_hdmi_test;
    private Button btn_cvbs_test;
    private Button btn_usb_test;

    private String deviceType;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.btn_hdmi_test:
            AlertDialog.Builder build = new Builder(MainActivity.this);
            build.setMessage(getResources().getString(R.string.hdmi_msg));
            build.setTitle(getResources().getString(R.string.dialog_title));
            build.setPositiveButton(getResources().getString(R.string.hdmi_ok), new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface arg0, int arg1) {
                    Intent intent = null;
                    intent = new Intent(MainActivity.this, HDMIActivity.class);
                    startActivity(intent);
               }
			});
            build.setNegativeButton(getResources().getString(R.string.hdmi_cancle), new DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface arg0, int arg1) {
					arg0.dismiss();
				}
			});
            build.create().show();
            break;
        case R.id.btn_cvbs_test:
            Intent intent = null;
            intent = new Intent(MainActivity.this, CVBSActivity.class);
            startActivity(intent);
            break;
        case R.id.btn_usb_test:
            Intent intent1 = null;
            intent1 = new Intent(MainActivity.this, USBActivity.class);
            intent1.putExtra("deviceType", deviceType);
            startActivity(intent1);
            break;

        default:
            break;
        }
    }

    private void initView() {
        deviceType = SystemProperties.get(PROPERTY_PATH);

        btn_hdmi_test = (Button) findViewById(R.id.btn_hdmi_test);
        btn_cvbs_test = (Button) findViewById(R.id.btn_cvbs_test);
        btn_usb_test = (Button) findViewById(R.id.btn_usb_test);

        btn_hdmi_test.setOnClickListener(this);
        btn_cvbs_test.setOnClickListener(this);
        btn_usb_test.setOnClickListener(this);
        if ("Hi3798MV100".equals(deviceType))
            btn_usb_test.setText(getString(R.string.usb_test_1));
        else
            btn_usb_test.setText(getString(R.string.usb_test_2));
    }

}