package com.hisilicon.hardware.usb;

import java.util.ArrayList;
import java.util.List;

import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.hisilicon.hardware.CommonActivity;
import com.hisilicon.hardwaretest.R;
import com.hisilicon.android.hisysmanager.HiSysManager;

public class USBActivity extends CommonActivity implements OnClickListener {

    private final String cmd_1 = "system himm 0xf9890054 0x4900d";
    private final String cmd_2 = "system himm 0xf9890058 0x4900d";
    private final String cmd_3 = "system himm 0xf989005c 0x4900d";
    private final String cmd_4_1 = "system himm 0xf987c2c0 0x410E0002";
    private final String cmd_4_2 = "system himm 0xf987c2c0 0x10E0002";
    private final String cmd_5 = "system himm 0xf987c2c0 0x410E0002";
    private final String cmd_6_1 = "system himm 0xF9900174 2F100000";
    private final String cmd_6_2 = "system himm 0xF9900174 4F100000";
    private final String cmd_6_3 = "system himm 0xF9900174 8F100000";
    private final String cmd_6_4 = "system himm 0xF9900174 cF100000";
    private final String cmd_7_1 = "system himm 0xF9900174 2F350000";
    private final String cmd_7_2 = "system himm 0xF9900174 4F350000";
    private final String cmd_7_3 = "system himm 0xF9900174 8F350000";
    private final String cmd_7_4 = "system himm 0xF9900174 cF350000";
    private final String cmd_8_1 = "system himm 0xF9900174 2F5A0000";
    private final String cmd_8_2 = "system himm 0xF9900174 4F5A0000";
    private final String cmd_8_3 = "system himm 0xF9900174 8F5A0000";
    private final String cmd_8_4 = "system himm 0xF9900174 cF5A0000";

    private final String cmd_1_98M = "system himm 0xf9890054 0x4900d";
    private final String cmd_2_98M = "system himm 0xf9890058 0x4900d";
    private final String cmd_3_98M = "system himm 0xf9930054 0x4900d";
    private final String cmd_4_1_98M = "system himm 0xf98ac2c0 0x010E0002";
    private final String cmd_4_2_98M = "system himm 0xf98ac2c0 0x410E0002";
    private final String cmd_5_1_98M = "system himm 0xf98ac2c0 0x010E0002";
    private final String cmd_5_2_98M = "system himm 0xf98ac2c0 0x410E0002";

    private RelativeLayout layout_3;
    private Button usb_btn_1;// USB0
    private Button usb_btn_2;// USB1
    private Button usb_btn_3;// USB2
    private Button usb_btn_4;// CP0
    private Button usb_btn_5;// CP1
    private Button usb_btn_6;// 1.5G
    private Button usb_btn_7;// 3.0G
    private Button usb_btn_8;// 6.0G

    private String deviceType;
    private boolean isDevice_98M;
    private boolean hasClickCP1;
    private HiSysManager mhisys;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_usb);
        initView();
        mhisys = new HiSysManager();
    }

    @Override
    public void onClick(View v) {
        List<String> cmds = new ArrayList<String>();
        switch (v.getId()) {

        case R.id.usb_btn_1:
            showDialog();
            if (isDevice_98M)
                cmds.add(cmd_1_98M);
            else
                cmds.add(cmd_1);
            break;

        case R.id.usb_btn_2:
            showDialog();
            if (isDevice_98M)
                cmds.add(cmd_2_98M);
            else
                cmds.add(cmd_2);
            break;

        case R.id.usb_btn_3:
            showDialog();
            if (isDevice_98M)
                cmds.add(cmd_3_98M);
            else
                cmds.add(cmd_3);
            break;

        case R.id.usb_btn_4:
            if (isDevice_98M) {
                cmds.add(cmd_4_1_98M);
                cmds.add(cmd_4_2_98M);
            } else {
                cmds.add(cmd_4_1);
                cmds.add(cmd_4_2);
            }
            usb_btn_4.setVisibility(View.GONE);
            usb_btn_5.setVisibility(View.VISIBLE);
            usb_btn_5.requestFocus();
            break;

        case R.id.usb_btn_5:
            if (hasClickCP1) {
                if (isDevice_98M) {
                    for (int i = 0; i < 8; i++) {
                        cmds.add(cmd_5_1_98M);
                        cmds.add(cmd_5_2_98M);
                    }
                } else {
                    for (int i = 0; i < 8; i++) {
                        cmds.add(cmd_5);
                    }
                }
            } else {
                hasClickCP1 = true;
                if (isDevice_98M) {
                    cmds.add(cmd_5_1_98M);
                    cmds.add(cmd_5_2_98M);
                } else {
                    cmds.add(cmd_5);
                }
            }
            break;

        case R.id.usb_btn_6:
            cmds.add(cmd_6_1);
            cmds.add(cmd_6_2);
            cmds.add(cmd_6_3);
            cmds.add(cmd_6_4);
            break;

        case R.id.usb_btn_7:
            cmds.add(cmd_7_1);
            cmds.add(cmd_7_2);
            cmds.add(cmd_7_3);
            cmds.add(cmd_7_4);
            break;

        case R.id.usb_btn_8:
            cmds.add(cmd_8_1);
            cmds.add(cmd_8_2);
            cmds.add(cmd_8_3);
            cmds.add(cmd_8_4);
            break;

        default:
            break;
        }
        excuteCmdTest(cmds);
    }

    @Override
    protected void onDestroy() {
        List<String> cmds = new ArrayList<String>();
        if (isDevice_98M) {
            for (int i = 0; i < 7; i++) {
                cmds.add(cmd_5_1_98M);
                cmds.add(cmd_5_2_98M);
            }
        } else {
            for (int i = 0; i < 7; i++) {
                cmds.add(cmd_5);
            }
        }
        excuteCmdTest(cmds);
        super.onDestroy();
    }

    private void showDialog() {
        showLoadingDialog(getString(R.string.dialog_title),
                getString(R.string.usb_sending), new OnCancelListener() {

                    @Override
                    public void onCancel(DialogInterface arg0) {
                        Toast.makeText(USBActivity.this,
                                getString(R.string.usb_cancel_send),
                                Toast.LENGTH_SHORT).show();
                    }
                });
    }

    private void initView() {
        deviceType = getIntent().getStringExtra("deviceType");
        isDevice_98M = DEVICE_98M.equals(deviceType);

        layout_3 = (RelativeLayout) findViewById(R.id.layout3);

        usb_btn_1 = (Button) findViewById(R.id.usb_btn_1);
        usb_btn_2 = (Button) findViewById(R.id.usb_btn_2);
        usb_btn_3 = (Button) findViewById(R.id.usb_btn_3);
        usb_btn_4 = (Button) findViewById(R.id.usb_btn_4);
        usb_btn_5 = (Button) findViewById(R.id.usb_btn_5);
        usb_btn_6 = (Button) findViewById(R.id.usb_btn_6);
        usb_btn_7 = (Button) findViewById(R.id.usb_btn_7);
        usb_btn_8 = (Button) findViewById(R.id.usb_btn_8);

        usb_btn_1.setOnClickListener(this);
        usb_btn_2.setOnClickListener(this);
        usb_btn_3.setOnClickListener(this);
        usb_btn_4.setOnClickListener(this);
        usb_btn_5.setOnClickListener(this);
        usb_btn_6.setOnClickListener(this);
        usb_btn_7.setOnClickListener(this);
        usb_btn_8.setOnClickListener(this);

        usb_btn_5.setVisibility(View.GONE);
        if (isDevice_98M)
            layout_3.setVisibility(View.GONE);
    }

    private void excuteCmdTest(final List<String> cmds) {
        if (null == cmds || cmds.size() == 0)
            return;
        new Thread(new Runnable() {

            @Override
            public void run() {
                for (String cmd : cmds) {
                    mhisys.setHimm(cmd);
                }
            }
        }).start();
    }

}