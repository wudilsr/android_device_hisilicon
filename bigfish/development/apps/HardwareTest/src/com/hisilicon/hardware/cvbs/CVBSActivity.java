package com.hisilicon.hardware.cvbs;

import android.content.Intent;
import android.graphics.Rect;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

import com.hisilicon.android.HiDisplayManager;
import com.hisilicon.hardware.CommonActivity;
import com.hisilicon.hardware.util.SelectFileAcvitity;
import com.hisilicon.hardwaretest.R;
import com.hisilicon.android.hisysmanager.HiSysManager;

public class CVBSActivity extends CommonActivity implements OnClickListener,
        OnItemSelectedListener {

    // 闅愯棌鍥惧舰灞�
    private final String HIDE_VIEW = "system echo hide > /proc/msp/hifb0";
    // 鏄剧ず鍥惧舰灞�
    private final String SHOW_VIEW = "system echo show > /proc/msp/hifb0";

    private final int REQUEST_CODE = 0;

    private Button btn_start_test;
    private Button btn_file_path;
    private TextView text_file_path;
    private Spinner spinner_display;

    // 鍒跺紡妯″紡
    private String[] displayArray;
    // 鐮佹祦鏂囦欢璺緞
    private String filePath;
    // 鍒跺紡閫夋嫨
    private int position = 0;
    // 娴嬭瘯鍓嶆樉绀哄埗寮�
    private int tempDisplayMode = 8;
    // 娴嬭瘯鍓嶆樉绀哄尯鍩�
    private Rect tempRect;

    private HiDisplayManager dManager;
    private boolean isTesting = false;
    private int testMode;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_cvbs);
        initView();
    }

    @Override
    protected void onResume() {
        if (isEmptyString(filePath))
            text_file_path.setText("");
        else
            text_file_path.setText(filePath);

        super.onResume();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.button_file_path:
            Intent intent = new Intent(CVBSActivity.this,
                    SelectFileAcvitity.class);
            intent.putExtra("path", getStoragePath());
            intent.putExtra("activity", "CVBSActivity");
            startActivityForResult(intent, REQUEST_CODE);
            break;
        case R.id.button_start_test:
            if (isEmptyString(filePath))
                showMessageDialog(R.string.select_file_first);
            else {
                testMode = getFileType(filePath);
                if (VIDEO_PLAY != testMode)
                    showMessageDialog(R.string.select_file_type1);
                else
                    startTSTest();
            }
            break;

        default:
            break;
        }
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position,
            long id) {
        this.position = position;
        TextView textView = (TextView) view;
        textView.setTextColor(getResources().getColor(android.R.color.white));
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (RESULT_OK == resultCode && REQUEST_CODE == requestCode) {
            filePath = data.getStringExtra("path");
            text_file_path.setText(filePath);
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (isTesting) {
            if (keyCode == KeyEvent.KEYCODE_BACK) {
                stopTSTest();
            }
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    protected void onStop() {
        stopTSTest();
        super.onStop();
    }

    private void initView() {
        displayArray = getResources()
                .getStringArray(R.array.display_mode_array);

        text_file_path = (TextView) findViewById(R.id.text_file_path);

        btn_start_test = (Button) findViewById(R.id.button_start_test);
        btn_start_test.setOnClickListener(this);

        btn_file_path = (Button) findViewById(R.id.button_file_path);
        btn_file_path.setOnClickListener(this);

        spinner_display = (Spinner) findViewById(R.id.spinner_display);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_spinner_item, displayArray);
        adapter.setDropDownViewResource(android.R.layout.simple_list_item_single_choice);
        spinner_display.setAdapter(adapter);
        spinner_display.setOnItemSelectedListener(this);

        dManager = new HiDisplayManager();
        tempDisplayMode = dManager.getFmt();
        tempRect = dManager.getOutRange();
    }

    private void startTSTest() {
        isTesting = true;
        btn_start_test.setFocusable(false);
        btn_start_test.setFocusableInTouchMode(false);

        dManager.setOutRange(0, 0, 0, 0);
        dManager.SaveParam();
        HiSysManager hisys = new HiSysManager();
        hisys.startTSTest(filePath,displayArray[position]);
 
    }

    private void stopTSTest() {
        isTesting = false;
        btn_start_test.setFocusable(true);
        btn_start_test.setFocusableInTouchMode(true);
        btn_start_test.requestFocus();
        HiSysManager hisys = new HiSysManager();
        hisys.stopTSTest();
        recoveryView();
    }

    private void recoveryView() {
        if (tempDisplayMode != dManager.getFmt()) {
            dManager.setFmt(tempDisplayMode);
            dManager.SaveParam();
        }
        if (tempRect != dManager.getOutRange()) {
            dManager.setOutRange(tempRect.left, tempRect.top, tempRect.right,
                    tempRect.bottom);
            dManager.SaveParam();
        }
    }

}