package com.hisilicon.baidu.pcs;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemLongClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.GridView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import com.baidu.pcs.BaiduPCSActionInfo.PCSCommonFileInfo;
import com.baidu.pcs.BaiduPCSActionInfo.PCSFileFromToInfo;
import com.baidu.pcs.BaiduPCSActionInfo.PCSFileFromToResponse;
import com.baidu.pcs.BaiduPCSActionInfo.PCSFileInfoResponse;
import com.baidu.pcs.BaiduPCSActionInfo.PCSListInfoResponse;
import com.baidu.pcs.BaiduPCSActionInfo.PCSQuotaResponse;
import com.baidu.pcs.BaiduPCSActionInfo.PCSSimplefiedResponse;
import com.hisilicon.baidu.pcs.common.Common;
import com.hisilicon.baidu.pcs.common.FileAdapter;
import com.hisilicon.baidu.pcs.common.FileAdapter.ViewHolder;
import com.hisilicon.baidu.pcs.common.FileMToast;
import com.hisilicon.baidu.pcs.common.FileUtil;
import com.hisilicon.baidu.pcs.common.FileUtil.EditDialogListener;
import com.hisilicon.baidu.pcs.common.MountInfo;

public class MainActivity extends CommonActivity implements OnClickListener,
        OnItemClickListener, OnItemSelectedListener, OnItemLongClickListener {

    private final int OPEN = 0;
    private final int MOVE = 1;
    private final int DELETE = 2;
    private final int DOWNLOAD = 3;

    private final int MENU_NEW = 0;
    private final int MENU_SEARCH = 1;
    private final int MENU_SHOW_STYLE = 2;
    private final int MENU_ACCOUNT_INFO = 3;
    private final int MENU_LOGOUT = 4;

    private final int LIST_VIEW = 0;
    private final int GRID_VIEW = 1;

    private final int REQUEST_MOVE = 0;
    private final int REQUEST_MOVES = 1;

    private FileAdapter adapter;
    private ListView mListView;
    private GridView mGridView;

    private LinearLayout selectLayout;
    private LinearLayout btnSelect;

    private TextView pathText;
    private TextView countText;

    private Button btnMove;
    private Button btnDelete;
    private Button btnSelectAll;
    private Button btnSelectNone;

    private boolean isExit;
    private boolean isChoise;
    private boolean isSearch;

    private int curPosition;
    private int layoutPosition;

    private String mbOauth;
    private String curPath;

    private List<Boolean> selectInfo;
    private List<PCSCommonFileInfo> infos;
    private List<PCSFileFromToInfo> tempMoves;
    private PCSFileFromToInfo tempMove;

    private TabMenu.MenuBodyAdapter bodyAdapter;
    private TabMenu.MenuTitleAdapter titleAdapter;
    private TabMenu tabMenu;

    private Handler handler = new Handler() {
        public void handleMessage(Message msg) {
            hideProgress();
            switch (msg.what) {

            case WHAT_EXIT:
                isExit = false;
                break;

            case WHAT_GET_QUOTA:
                PCSQuotaResponse quotaRes = (PCSQuotaResponse) msg.obj;
                showQuoteInfo(quotaRes);
                break;

            case WHAT_LOGIN:
                apiLogin();
                break;

            case WHAT_REFRESH_LIST:
                apiGetFileList(curPath);
                break;

            case WHAT_MOVE:
                isChoise = false;
                PCSFileFromToResponse moveRes = (PCSFileFromToResponse) msg.obj;
                if (moveRes.status.errorCode == 0) {
                    curPosition = 0;
                    apiGetFileList(curPath);
                } else {
                    showToast(R.string.msg_move_error);
                    refreshView();
                }
                break;

            case WHAT_DELETE:
                isChoise = false;
                PCSSimplefiedResponse deleteRes = (PCSSimplefiedResponse) msg.obj;
                if (deleteRes.errorCode == 0) {
                    curPosition = 0;
                    apiGetFileList(curPath);
                } else {
                    showToast(R.string.msg_delete_error);
                    refreshView();
                }
                break;

            case WHAT_DOWNLOAD:
                PCSSimplefiedResponse downloadRes = (PCSSimplefiedResponse) msg.obj;
                if (downloadRes.errorCode == 0)
                    showToast(R.string.msg_success_download);
                else
                    showToast(R.string.msg_fail_download);
                break;

            case WHAT_SEARCH:
                PCSListInfoResponse searchRes = (PCSListInfoResponse) msg.obj;
                if (searchRes.status.errorCode == 0) {
                    infos = searchRes.list;
                    isSearch = true;
                    curPosition = 0;
                    refreshView();
                }
                break;

            case WHAT_GET_LIST:
                PCSListInfoResponse listRes = (PCSListInfoResponse) msg.obj;
                Log.i("huangcanbin", "*********** errorCode = "
                        + listRes.status.errorCode);
                Log.i("huangcanbin", "*********** msg = "
                        + listRes.status.message);
                if (listRes.status.errorCode == 0) {
                    curPath = getCurPath();
                    curPosition = 0;
                    infos = listRes.list;
                    for (int i = 0; i < infos.size(); i++) {
                        if (infos.get(i).path.equals(curPath)) {
                            curPosition = i;
                            break;
                        }
                    }
                    refreshView();
                }
                break;
            case WHAT_MKDIR:
                PCSFileInfoResponse mkdirRes = (PCSFileInfoResponse) msg.obj;
                if (mkdirRes.status.errorCode == 0)
                    apiGetFileList(curPath);
                else
                    showToast(R.string.msg_fail_creat);
                break;

            default:
                break;
            }
        };
    };

    private void init() {
        mbOauth = getMbOauth();

        mListView = (ListView) findViewById(R.id.listFile);
        mGridView = (GridView) findViewById(R.id.gridFile);
        selectLayout = (LinearLayout) findViewById(R.id.select_layout);
        btnSelect = (LinearLayout) findViewById(R.id.btnSelect);

        pathText = (TextView) findViewById(R.id.path_text);
        countText = (TextView) findViewById(R.id.count_text);

        btnMove = (Button) findViewById(R.id.btn_move);
        btnDelete = (Button) findViewById(R.id.btn_delete);
        btnSelectAll = (Button) findViewById(R.id.btn_select_all);
        btnSelectNone = (Button) findViewById(R.id.btn_select_none);

        mListView.setOnItemSelectedListener(this);
        mListView.setOnItemClickListener(this);
        mListView.setOnItemLongClickListener(this);
        mGridView.setOnItemSelectedListener(this);
        mGridView.setOnItemClickListener(this);
        mGridView.setOnItemLongClickListener(this);

        btnMove.setOnClickListener(this);
        btnDelete.setOnClickListener(this);
        btnSelectAll.setOnClickListener(this);
        btnSelectNone.setOnClickListener(this);

        setViewLayout(LIST_VIEW);
    }

    private void intMenu() {
        titleAdapter = new TabMenu.MenuTitleAdapter(this, new String[] { " " },
                16, 0xFF222222, Color.LTGRAY, Color.WHITE);
        String[] menuOptions = getResources().getStringArray(R.array.menu);
        int[] menuDrawableIDs = new int[] { R.drawable.menu_new,
                R.drawable.menu_search, R.drawable.menu_style,
                R.drawable.menu_info, R.drawable.menu_logout };
        bodyAdapter = new TabMenu.MenuBodyAdapter(this, menuOptions,
                menuDrawableIDs, 13, 0xFFFFFFFF);

        Drawable griDrawable = getResources().getDrawable(
                R.drawable.gridview_item_selector);
        tabMenu = new TabMenu(MainActivity.this, griDrawable,
                new TitleClickEvent(), new BodyClickEvent(), titleAdapter,
                0x55123456, R.style.PopupAnimation);

        tabMenu.update();
        tabMenu.SetTitleSelect(0);
        tabMenu.SetBodyAdapter(bodyAdapter);
    }

    private void showOperationDialog(final PCSCommonFileInfo fileInfo) {
        LayoutInflater factory = LayoutInflater.from(MainActivity.this);
        View v = factory.inflate(R.layout.view_select, null);
        ListView listView = (ListView) v.findViewById(R.id.lvSambaServer);
        final AlertDialog dialog = new AlertDialog.Builder(MainActivity.this)
                .create();
        dialog.setView(v);
        dialog.show();
        ArrayList<String> filterList = new ArrayList<String>();
        String[] filterString = getResources()
                .getStringArray(R.array.operation);
        for (String string : filterString) {
            filterList.add(string);
        }
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(
                MainActivity.this, android.R.layout.simple_list_item_1,
                filterList);
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> arg0, View arg1,
                    int position, long arg3) {
                operationFile(fileInfo, position);
                dialog.dismiss();
            }
        });
    }

    private boolean hasSelectItem() {
        for (int i = 0; i < selectInfo.size(); i++) {
            if (selectInfo.get(i))
                return true;
        }
        return false;
    }

    private void operationFile(PCSCommonFileInfo fileInfo, int operation) {
        final String path = fileInfo.path;
        Intent intent = null;

        switch (operation) {

        case OPEN:
            intent = new Intent();
            Uri uri = Uri.parse(getRequestUri(path));
            String type = FileUtil.getFileType(path);
            Log.i(TAG, "=======> path : " + path);
            Log.i(TAG, "=======> uri = " + uri);
            Log.i(TAG, "=======> type = " + type);
            if ("video/*".equals(type)) {
                try {
                    intent.setClassName("com.hisilicon.android.videoplayer",
                            "com.hisilicon.android.videoplayer.activity.VideoActivity");
                    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    intent.setDataAndType(uri, type);
                    startActivity(intent);
                } catch (Exception e) {
                    showToast(R.string.open_error);
                    e.printStackTrace();
                }
            } else if ("audio/*".equals(type)) {
                intent.setClassName("com.hisilicon.android.gallery3d",
                        "com.hisilicon.android.gallery3d.app.MovieActivity");
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                intent.setDataAndType(uri, type);
                startActivity(intent);
            } else if ("image/*".equals(type)) {
                intent.setAction(Intent.ACTION_VIEW);
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                intent.setDataAndType(uri, type);
                startActivity(intent);
            } else {
                showToast(R.string.open_error);
            }
            break;

        case MOVE:
            tempMove = new PCSFileFromToInfo();
            tempMove.from = path;
            intent = new Intent(MainActivity.this, SelectFileAcvitity.class);
            intent.putExtra("mbOauth", mbOauth);
            startActivityForResult(intent, REQUEST_MOVE);
            break;

        case DELETE:
            showDialog(R.string.msg_delete,
                    new DialogInterface.OnClickListener() {

                        @Override
                        public void onClick(DialogInterface arg0, int arg1) {
                            apiDeleteFile(path);
                        }
                    });
            break;

        case DOWNLOAD:
            MountInfo info = new MountInfo();
            String mountpath = "/storage/emulated/0";
            for (int i = 0; i < info.index; i++) {
                if (info.path[i] != null && (info.path[i].contains("/mnt"))) {
                    mountpath = info.path[i];
                    break;
                }
            }
            File downloadDir = new File(mountpath, "HiBaiDu_Download");
            if (!downloadDir.exists())
                downloadDir.mkdir();
            String fileName = path.substring(path.lastIndexOf("/") + 1);
            apiDownloadFile(path, downloadDir.getPath() + "/" + fileName);
            break;

        default:
            break;
        }
    }

    private void selectAll(boolean select) {
        for (int i = 0; i < selectInfo.size(); i++) {
            selectInfo.set(i, select);
        }
        refreshView();
    }

    private void showLayoutDialog() {
        LayoutInflater factory = LayoutInflater.from(MainActivity.this);
        View v = factory.inflate(R.layout.view_select, null);
        ListView listView = (ListView) v.findViewById(R.id.lvSambaServer);
        final AlertDialog dialog = new AlertDialog.Builder(this).create();
        dialog.setView(v);
        dialog.show();

        String[] filterString = getResources().getStringArray(
                R.array.show_method);
        ArrayList<String> filterList = new ArrayList<String>();
        for (String string : filterString) {
            filterList.add(string);
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_single_choice, filterList);
        listView.setAdapter(adapter);
        listView.setChoiceMode(ListView.CHOICE_MODE_SINGLE);
        listView.setItemChecked(layoutPosition, true);
        listView.setSelection(layoutPosition);
        listView.setOnItemClickListener(new OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> group, View v, int position,
                    long id) {
                layoutPosition = position;
                setViewLayout(layoutPosition);
                dialog.dismiss();
            }
        });
    }

    private void setViewLayout(int position) {
        if (LIST_VIEW == position) {
            mListView.setVisibility(View.VISIBLE);
            mGridView.setVisibility(View.GONE);
            adapter = new FileAdapter(this, infos, R.layout.view_list_item);
            mListView.setAdapter(adapter);
        } else if (GRID_VIEW == position) {
            mListView.setVisibility(View.GONE);
            mGridView.setVisibility(View.VISIBLE);
            adapter = new FileAdapter(this, infos, R.layout.view_grid_item);
            mGridView.setAdapter(adapter);
        }
    }

    private boolean isExists(String filePath) {
        for (PCSCommonFileInfo fileInfo : infos) {
            if (fileInfo.isDir) {
                if (fileInfo.path.equals(filePath))
                    return true;
            }
        }
        return false;
    }

    private String getAbsPath(String from, String to) {
        return to + "/" + from.substring(from.lastIndexOf("/") + 1);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
        if (TextUtils.isEmpty(mbOauth))
            apiLogin();
        else
            apiGetFileList(Common.ROOT_PATH);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

        switch (keyCode) {

        case KeyEvent.KEYCODE_BACK:
            String path = pathText.getText().toString().trim();
            if (isChoise) {
                isChoise = false;
                refreshView();
                return true;
            } else if (isSearch) {
                isSearch = false;
                apiGetFileList(curPath);
                return true;
            } else if (!Common.ROOT_PATH.equals(path)) {
                String parentPath = path.substring(0, path.lastIndexOf("/"));
                apiGetFileList(parentPath);
                return true;
            } else if (!isExit) {
                isExit = true;
                showToast(R.string.quit_app);
                handler.sendEmptyMessageDelayed(WHAT_EXIT, 2000);
                return true;
            }
            break;

        case KeyEvent.KEYCODE_MENU:
            if (!isChoise) {
                intMenu();
                if (tabMenu != null) {
                    tabMenu.showAtLocation(findViewById(R.id.root_view),
                            Gravity.BOTTOM, 0, 0);
                }
            }
            return true;

        default:
            break;
        }

        return super.onKeyDown(keyCode, event);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {

        case R.id.btn_move:
            if (!hasSelectItem()) {
                showToast(R.string.select_first);
                return;
            }
            tempMoves = new ArrayList<PCSFileFromToInfo>();
            for (int i = 0; i < infos.size(); i++) {
                if (selectInfo.get(i)) {
                    PCSFileFromToInfo info = new PCSFileFromToInfo();
                    info.from = infos.get(i).path;
                    tempMoves.add(info);
                }
            }
            Intent intent = new Intent(MainActivity.this,
                    SelectFileAcvitity.class);
            intent.putExtra("mbOauth", mbOauth);
            startActivityForResult(intent, REQUEST_MOVES);
            break;

        case R.id.btn_delete:
            if (!hasSelectItem()) {
                showToast(R.string.select_first);
                return;
            }
            final List<String> paths = new ArrayList<String>();
            for (int i = 0; i < infos.size(); i++) {
                if (selectInfo.get(i)) {
                    paths.add(infos.get(i).path);
                }
            }
            showDialog(R.string.msg_delete,
                    new DialogInterface.OnClickListener() {

                        @Override
                        public void onClick(DialogInterface dialog, int position) {
                            apiDeleteFile(paths);
                        }
                    });
            break;

        case R.id.btn_select_all:
            selectAll(true);
            break;

        case R.id.btn_select_none:
            selectAll(false);
            break;

        default:
            break;
        }
    }

    @Override
    public void onItemClick(AdapterView<?> group, View v, int position, long id) {
        if (!isChoise) {
            PCSCommonFileInfo fileInfo = infos.get(position);
            if (fileInfo.isDir) {
                apiGetFileList(fileInfo.path);
            } else {
                showOperationDialog(fileInfo);
            }
        } else {
            selectInfo.set(position, !selectInfo.get(position));
            ViewHolder holder = (ViewHolder) v.getTag();
            holder.setSelect(selectInfo.get(position));
        }
    }

    @Override
    public void onItemSelected(AdapterView<?> group, View v, int position,
            long id) {
        if (!isChoise) {
            curPosition = position;
            countText.setText((position + 1) + "/" + infos.size());
        }
    }

    @Override
    public void onNothingSelected(AdapterView<?> group) {
    }

    @Override
    public boolean onItemLongClick(AdapterView<?> parent, View view,
            int position, long id) {
        if (!isChoise) {
            curPosition = position;
            isChoise = true;
            selectInfo = new ArrayList<Boolean>();
            for (int i = 0; i < infos.size(); i++) {
                selectInfo.add(i == position);
            }
            refreshView();
        }
        return true;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (null == data || Common.RESULT_CANCLE == resultCode) {
            return;
        } else if (Common.RESULT_ERROR == resultCode) {
            showPermissionDialog();
            return;
        }
        String to = data.getStringExtra("path");
        if (REQUEST_MOVE == requestCode && RESULT_OK == resultCode) {
            tempMove.to = getAbsPath(tempMove.from, to);
            apiMoveFile(tempMove);
        } else if (REQUEST_MOVES == requestCode && RESULT_OK == resultCode) {
            tempMoves = new ArrayList<PCSFileFromToInfo>();
            for (int i = 0; i < infos.size(); i++) {
                if (selectInfo.get(i)) {
                    PCSFileFromToInfo info = new PCSFileFromToInfo();
                    info.from = infos.get(i).path;
                    info.to = getAbsPath(info.from, to);
                    tempMoves.add(info);
                }
            }
            apiMoveFile(tempMoves);
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    protected void refreshView() {
        if (isChoise) {
            countText.setVisibility(View.GONE);
            btnSelect.setVisibility(View.VISIBLE);
            selectLayout.setVisibility(View.VISIBLE);
            adapter.refreshList(infos, selectInfo);
        } else {
            countText.setVisibility(View.VISIBLE);
            btnSelect.setVisibility(View.GONE);
            selectLayout.setVisibility(View.GONE);
            adapter.refreshList(infos, null);
            mListView.setSelection(curPosition);
            mGridView.setSelection(curPosition);
        }

        pathText.setText(curPath);
        if (infos.size() == 0) {
            countText.setText("0/0");
        }
    }

    @Override
    protected Handler getHandler() {
        return handler;
    }

    private class TitleClickEvent implements OnItemClickListener {
        @Override
        public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
                long arg3) {
            tabMenu.SetTitleSelect(arg2);
            tabMenu.SetBodyAdapter(bodyAdapter);
        }
    }

    private class BodyClickEvent implements OnItemClickListener {
        @Override
        public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
                long arg3) {
            if (tabMenu.isShowing())
                tabMenu.dismiss();
            switch (arg2) {
            case MENU_NEW:
                FileUtil.showEditDialog(MainActivity.this,
                        getString(R.string.new_dir), R.string.name_empty,
                        new EditDialogListener() {

                            @Override
                            public void doFinishEdit(String text) {
                                String newPath = curPath + "/" + text;
                                if (isExists(newPath))
                                    FileMToast.getInstance(MainActivity.this,
                                            R.string.has_exist);
                                else
                                    apiMakeDir(newPath);
                            }
                        });
                break;

            case MENU_SEARCH:
                FileUtil.showEditDialog(MainActivity.this,
                        getString(R.string.input_keyword), R.string.edit_empty,
                        new EditDialogListener() {

                            @Override
                            public void doFinishEdit(String text) {
                                apiSearch(curPath, text);
                            }
                        });
                break;

            case MENU_SHOW_STYLE:
                showLayoutDialog();
                break;

            case MENU_ACCOUNT_INFO:
                apiGetQuota();
                break;

            case MENU_LOGOUT:
                showAccountInfo();
                break;

            default:
                break;
            }
        }
    }

}