package com.hisilicon.baidu.pcs;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.WindowManager.LayoutParams;
import android.widget.TextView;

import com.baidu.oauth.BaiduOAuth;
import com.baidu.oauth.BaiduOAuth.BaiduOAuthResponse;
import com.baidu.pcs.BaiduPCSActionInfo.PCSCommonFileInfo;
import com.baidu.pcs.BaiduPCSActionInfo.PCSFileFromToInfo;
import com.baidu.pcs.BaiduPCSActionInfo.PCSFileFromToResponse;
import com.baidu.pcs.BaiduPCSActionInfo.PCSFileInfoResponse;
import com.baidu.pcs.BaiduPCSActionInfo.PCSListInfoResponse;
import com.baidu.pcs.BaiduPCSActionInfo.PCSQuotaResponse;
import com.baidu.pcs.BaiduPCSActionInfo.PCSSimplefiedResponse;
import com.baidu.pcs.BaiduPCSClient;
import com.baidu.pcs.BaiduPCSStatusListener;
import com.hisilicon.baidu.pcs.common.Common;
import com.hisilicon.baidu.pcs.common.FileMToast;
import com.hisilicon.baidu.pcs.common.FileUtil;

public abstract class CommonActivity extends Activity {

    protected final String TAG = "CommonActivity";

    protected final int WHAT_EXIT = 1;
    protected final int WHAT_LOGIN = 2;
    protected final int WHAT_MKDIR = 3;
    protected final int WHAT_MOVE = 4;
    protected final int WHAT_DELETE = 5;
    protected final int WHAT_SEARCH = 6;
    protected final int WHAT_DOWNLOAD = 7;
    protected final int WHAT_GET_QUOTA = 8;
    protected final int WHAT_GET_LIST = 9;
    protected final int WHAT_REFRESH_LIST = 10;

    private final String KEY_OAUTH = "oauth";
    private final String KEY_ACCOUNT = "account";

    private BaiduPCSClient api;
    private Handler handler;

    private ProgressDialog progress;
    private MyProgressBar progressBar;
    private Dialog downloadDialog;

    private String userName;
    private String mbOauth;
    private String curPath;

    protected String getMbOauth() {
        return mbOauth;
    }

    protected String getCurPath() {
        return curPath;
    }

    protected abstract void refreshView();

    protected abstract Handler getHandler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mbOauth = getPreferences(KEY_OAUTH);
        userName = getPreferences(KEY_ACCOUNT);
        handler = getHandler();
    }

    protected boolean checkPermission() {
        if (!checkNetWork()) {
            showToast(R.string.network_error);
            return false;
        }
        if (TextUtils.isEmpty(mbOauth)) {
            showPermissionDialog();
            return false;
        }
        if (null == api) {
            api = new BaiduPCSClient();
            api.setAccessToken(mbOauth);
        }
        return true;
    }

    protected List<PCSCommonFileInfo> folderFilter(List<PCSCommonFileInfo> list) {
        List<PCSCommonFileInfo> listInfo = new ArrayList<PCSCommonFileInfo>();
        if (null != list && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                if (list.get(i).isDir) {
                    listInfo.add(list.get(i));
                }
            }
        }
        return listInfo;
    }

    protected String getRequestUri(String source) {
        if ((source != null)) {
            StringBuffer uri = new StringBuffer();
            uri.append("https://pcs.baidu.com/rest/2.0/pcs/stream?method=download&access_token=");
            uri.append(mbOauth);
            uri.append("&path=");
            uri.append(source);
            return uri.toString();
        }
        return null;
    }

    protected LayoutParams setDisplay(Dialog dialog, float h, float w) {
        DisplayMetrics dm = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm);
        LayoutParams params = dialog.getWindow().getAttributes();
        params.gravity = Gravity.CENTER;
        if (0f != h)
            params.height = (int) (dm.heightPixels * h);
        if (0f != w)
            params.width = (int) (dm.widthPixels * w);
        return params;
    }

    protected void showToast(int msgId) {
        FileMToast.getInstance(CommonActivity.this, msgId);
    }

    protected void hideProgress() {
        if (null != progress && progress.isShowing())
            progress.dismiss();
    }

    protected void showProgress(String msg) {
        if (null == progress) {
            progress = new ProgressDialog(CommonActivity.this);
            progress.setCancelable(false);
        }
        progress.setMessage(msg);
        progress.show();
    }

    protected void showDownloadDialog() {
        progressBar = new MyProgressBar(this);
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle(getString(R.string.title_tips));
        builder.setView(progressBar);
        builder.setCancelable(false);
        builder.setPositiveButton(getString(R.string.download_bk),
                new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int position) {
                        dialog.dismiss();
                    }
                });
        downloadDialog = builder.create();
        downloadDialog.show();
    }

    protected void showPermissionDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle(getString(R.string.title_tips));
        builder.setMessage(getString(R.string.msg_no_permission));
        builder.setCancelable(false);
        builder.setPositiveButton(getString(R.string.btn_confirm),
                new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int position) {
                        apiLogin();
                    }
                });
        builder.create().show();
    }

    protected void showDialog(int msgId,
            DialogInterface.OnClickListener listener) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle(getString(R.string.title_tips));
        builder.setMessage(getString(msgId));
        builder.setPositiveButton(getString(R.string.btn_confirm), listener);
        builder.setNegativeButton(getString(R.string.btn_cancle), null);
        builder.create().show();
    }

    protected void showQuoteInfo(PCSQuotaResponse info) {
        if (null == info || info.status.errorCode != 0) {
            showToast(R.string.quota_error);
        } else {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle(getString(R.string.quota_info));

            View v = LayoutInflater.from(this).inflate(R.layout.view_quota,
                    null);
            TextView total = (TextView) v.findViewById(R.id.quota_total);
            TextView used = (TextView) v.findViewById(R.id.quota_used);
            TextView available = (TextView) v
                    .findViewById(R.id.quota_available);
            total.setText(FileUtil.fileSizeMsg(info.total));
            used.setText(FileUtil.fileSizeMsg(info.used));
            available.setText(FileUtil.fileSizeMsg(info.total - info.used));
            builder.setView(v);
            builder.setPositiveButton(getString(R.string.btn_confirm), null);
            Dialog dialog = builder.create();
            dialog.show();
            dialog.getWindow().setAttributes(setDisplay(dialog, 0f, 0.5f));
        }
    }

    protected void showAccountInfo() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle(getString(R.string.account_info));

        View v = LayoutInflater.from(this).inflate(R.layout.view_account, null);
        TextView text = (TextView) v.findViewById(R.id.account);
        if (TextUtils.isEmpty(userName))
            userName = getString(R.string.no_account);
        text.setText(userName);
        builder.setView(v);
        builder.setPositiveButton(getString(R.string.btn_logout),
                new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        showDialog(R.string.msg_logout,
                                new DialogInterface.OnClickListener() {

                                    @Override
                                    public void onClick(DialogInterface dialog,
                                            int position) {
                                        apiLogout();
                                    }
                                });
                    }
                });
        builder.setNegativeButton(getString(R.string.btn_cancle), null);
        Dialog dialog = builder.create();
        dialog.show();

        dialog.getWindow().setAttributes(setDisplay(dialog, 0f, 0.65f));
    }

    protected void setPreferences(String key, String value) {
        SharedPreferences preferences = getSharedPreferences(Common.SHARED_PRE,
                Activity.MODE_PRIVATE);
        SharedPreferences.Editor editor = preferences.edit();
        editor.putString(key, value);
        editor.commit();
    }

    protected String getPreferences(String key) {
        SharedPreferences preferences = getSharedPreferences(Common.SHARED_PRE,
                Activity.MODE_PRIVATE);
        return preferences.getString(key, "");
    }

    protected boolean checkNetWork() {
        ConnectivityManager connectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo info = connectivityManager.getActiveNetworkInfo();
        if (info != null && info.isAvailable())
            return true;
        return false;
    }

    protected void sendMessage(int what, Object obj) {
        Message msg = new Message();
        msg.what = what;
        msg.obj = obj;
        handler.sendMessage(msg);
    }

    protected void apiLogin() {
        BaiduOAuth oauthClient = new BaiduOAuth();
        oauthClient.startOAuth(this, Common.API_KEY,
                new BaiduOAuth.OAuthListener() {
                    @Override
                    public void onException(String msg) {
                        showToast(R.string.msg_login_error);
                        finish();
                    }

                    @Override
                    public void onComplete(BaiduOAuthResponse response) {
                        if (null != response) {
                            mbOauth = response.getAccessToken();
                            userName = response.getUserName();
                            Log.i(TAG, "Token=" + mbOauth + ",User=" + userName);
                            setPreferences(KEY_OAUTH, mbOauth);
                            setPreferences(KEY_ACCOUNT, userName);
                            apiGetFileList(Common.ROOT_PATH);
                        } else {
                            showToast(R.string.msg_login_error);
                            apiLogin();
                        }
                    }

                    @Override
                    public void onCancel() {
                        showToast(R.string.msg_login_error);
                        finish();
                    }
                });
    }

    protected void apiLogout() {
        new Thread(new Runnable() {

            @Override
            public void run() {
                BaiduOAuth oauth = new BaiduOAuth();
                oauth.logout(mbOauth);
                setPreferences(KEY_OAUTH, "");
                setPreferences(KEY_ACCOUNT, "");
                api = null;
                handler.sendEmptyMessage(WHAT_LOGIN);
            }
        }).start();
    }

    protected void apiMakeDir(final String path) {
        if (checkPermission()) {
            new Thread(new Runnable() {

                @Override
                public void run() {
                    PCSFileInfoResponse res = api.makeDir(path);
                    sendMessage(WHAT_MKDIR, res);
                }
            }).start();
        }
    }

    protected void apiGetFileList(final String path) {
        if (checkPermission()) {
            showProgress(getString(R.string.msg_loading));
            new Thread(new Runnable() {

                @Override
                public void run() {
                    PCSListInfoResponse res = api.list(path, "name", "asc");
                    if (res.status.errorCode == 0)
                        curPath = path;
                    sendMessage(WHAT_GET_LIST, res);
                }
            }).start();
        }
    }

    protected void apiSearch(final String path, final String key) {
        if (checkPermission()) {
            showProgress(getString(R.string.msg_loading));
            new Thread(new Runnable() {

                @Override
                public void run() {
                    PCSListInfoResponse res = api.search(path, key, true);
                    sendMessage(WHAT_SEARCH, res);
                }
            }).start();
        }
    }

    protected void apiGetQuota() {

        if (checkPermission()) {
            new Thread(new Runnable() {

                @Override
                public void run() {
                    PCSQuotaResponse res = api.quota();
                    sendMessage(WHAT_GET_QUOTA, res);
                }
            }).start();
        }
    }

    protected void apiMoveFile(final List<PCSFileFromToInfo> list) {
        if (checkPermission()) {
            new Thread(new Runnable() {

                @Override
                public void run() {
                    PCSFileFromToResponse res = api.move(list);
                    sendMessage(WHAT_MOVE, res);
                }
            }).start();
        }
    }

    protected void apiMoveFile(final PCSFileFromToInfo info) {
        if (checkPermission()) {
            new Thread(new Runnable() {

                @Override
                public void run() {
                    PCSFileFromToResponse res = api.move(info.from, info.to);
                    sendMessage(WHAT_MOVE, res);
                }
            }).start();
        }
    }

    protected void apiDeleteFile(final String path) {
        if (checkPermission()) {
            new Thread(new Runnable() {

                @Override
                public void run() {
                    PCSSimplefiedResponse res = api.deleteFile(path);
                    sendMessage(WHAT_DELETE, res);
                }
            }).start();
        }
    }

    protected void apiDeleteFile(final List<String> paths) {
        if (checkPermission()) {
            new Thread(new Runnable() {

                @Override
                public void run() {
                    PCSSimplefiedResponse res = api.deleteFiles(paths);
                    sendMessage(WHAT_DELETE, res);
                }
            }).start();
        }
    }

    protected void apiDownloadFile(final String from, final String to) {
        if (checkPermission()) {
            showDownloadDialog();
            new Thread(new Runnable() {

                @Override
                public void run() {
                    PCSSimplefiedResponse res = api.downloadFileFromStream(
                            from, to, downloadListener);
                    sendMessage(WHAT_DOWNLOAD, res);
                }
            }).start();
        }
    }

    protected BaiduPCSStatusListener downloadListener = new BaiduPCSStatusListener() {

        @Override
        public void onProgress(long bytes, long total) {
            if (null == progressBar)
                return;

            final int progress = (int) ((bytes * 100 / total));
            handler.post(new Runnable() {
                public void run() {
                    progressBar.setProgress(progress);
                    progressBar.setText(progress + "%");
                    if (progress >= 100 && null != downloadDialog)
                        downloadDialog.dismiss();
                }
            });
        }
    };

}