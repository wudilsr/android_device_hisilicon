package com.hisilicon.baidu.pcs;

import java.util.ArrayList;
import java.util.List;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager.LayoutParams;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

import com.baidu.pcs.BaiduPCSActionInfo.PCSCommonFileInfo;
import com.baidu.pcs.BaiduPCSActionInfo.PCSListInfoResponse;
import com.hisilicon.baidu.pcs.common.Common;
import com.hisilicon.baidu.pcs.common.FileAdapter;

public class SelectFileAcvitity extends CommonActivity implements
        OnClickListener, OnItemClickListener {

    private Button btnConfirm;
    private Button btnCancle;
    private TextView titleView;
    private ListView listView;

    private Intent resIntent;
    private FileAdapter adapter;
    private List<PCSCommonFileInfo> infos;

    private int curPosition;

    private String mbOauth;
    private String curPath;

    private Handler handler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
            case WHAT_GET_LIST:
                hideProgress();
                PCSListInfoResponse listRes = (PCSListInfoResponse) msg.obj;
                if (listRes.status.errorCode == 0) {
                    curPath = getCurPath();
                    curPosition = 0;
                    infos = folderFilter(listRes.list);
                    for (int i = 0; i < infos.size(); i++) {
                        if (infos.get(i).path.equals(curPath)) {
                            curPosition = i;
                            break;
                        }
                    }
                    refreshView();
                }

            default:
                break;
            }
        };
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        resIntent = new Intent(SelectFileAcvitity.this, MainActivity.class);
        mbOauth = getMbOauth();
        if (TextUtils.isEmpty(mbOauth)) {
            setResult(Common.RESULT_ERROR, resIntent);
            finish();
            return;
        }

        setContentView(R.layout.select_file_list);

        DisplayMetrics dm = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm);
        LayoutParams params = getWindow().getAttributes();
        params.gravity = Gravity.CENTER;
        params.height = (int) (dm.heightPixels * 0.8);
        params.width = (int) (dm.widthPixels * 0.7);
        getWindow().setAttributes(params);

        btnConfirm = (Button) findViewById(R.id.btn_confirm);
        btnCancle = (Button) findViewById(R.id.btn_cancle);
        titleView = (TextView) findViewById(R.id.text_title);
        listView = (ListView) findViewById(R.id.list_view);

        btnConfirm.setOnClickListener(this);
        btnCancle.setOnClickListener(this);
        listView.setOnItemClickListener(this);
        infos = new ArrayList<PCSCommonFileInfo>();
        adapter = new FileAdapter(this, infos, R.layout.view_list_item);
        listView.setAdapter(adapter);

        apiGetFileList(Common.ROOT_PATH);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            if (TextUtils.isEmpty(curPath) || Common.ROOT_PATH.equals(curPath)) {
                setResult(Common.RESULT_CANCLE, resIntent);
                finish();
            } else {
                String parentPath = curPath.substring(0,
                        curPath.lastIndexOf("/"));
                apiGetFileList(parentPath);
                return true;
            }
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {

        case R.id.btn_confirm:
            resIntent.putExtra("path", curPath);
            setResult(RESULT_OK, resIntent);
            finish();
            break;

        case R.id.btn_cancle:
            setResult(Common.RESULT_CANCLE, resIntent);
            finish();
            break;

        default:
            break;
        }
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position,
            long id) {
        switch (parent.getId()) {

        case R.id.list_view:
            apiGetFileList(infos.get(position).path);
            break;

        default:
            break;
        }
    }

    @Override
    public void refreshView() {
        adapter.refreshList(infos, null);
        titleView.setText(curPath);
        listView.setSelection(curPosition);
    }

    @Override
    protected Handler getHandler() {
        return handler;
    }

}