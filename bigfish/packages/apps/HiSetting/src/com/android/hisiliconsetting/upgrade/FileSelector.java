package com.android.hisiliconsetting.upgrade;

import java.io.File;
import java.util.List;

import com.android.hisiliconsetting.R;

import android.os.storage.IMountService;
import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class FileSelector extends Dialog {
    private String TAG = "FileSelector";
    private Context mContext;
    private List<android.os.storage.ExtraInfo> mMountList;
    private ListView mListView;
    private OnOperateCallback mCall;

    public static interface OnOperateCallback {
        public void callBack(String type);
    }

    public FileSelector(Context context, int theme, OnOperateCallback call) {
        super(context, theme);
        mContext = context;
        mCall = call;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mount_dialog_view);
        InitData();
        mListView = (ListView) findViewById(R.id.menu_list);
        mListView.setSelected(false);
        mListView.setAdapter(new menuAdapter());
        mListView.setOnItemClickListener(new ItemOnClickListener());

    }

    private class menuAdapter extends BaseAdapter {

        @Override
        public int getCount() {
            return mMountList.size();
        }

        @Override
        public Object getItem(int position) {
            return mMountList.get(position);
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            menuitem item = null;
            if (convertView == null) {
                item = new menuitem();
                convertView = LayoutInflater.from(mContext).inflate(
                        R.layout.mount_item, null);
                item.text = (TextView) convertView.findViewById(R.id.menu_item);
                convertView.setTag(item);
            } else {
                item = (menuitem) convertView.getTag();
            }

            item.text.setText(mMountList.get(position).mDiskLabel);
            return convertView;
        }

    }

    private class ItemOnClickListener implements OnItemClickListener {
        @Override
        public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
                long arg3) {
            String path = mMountList.get(arg2).mMountPoint;
            if (CheckUpdateFile(path)) {
                dismiss();
                if (mCall != null)
                    mCall.callBack(path);
            } else {
                ShowToast(R.string.local_no_update);
            }
        }

    }

    private class menuitem {
        TextView text;
    }

    private void InitData() {
        try {
            IBinder service = ServiceManager.getService("mount");
            if (service != null) {
                IMountService mountService = IMountService.Stub
                        .asInterface(service);
                mMountList = mountService.getAllExtraInfos();
                Log.i(TAG, mMountList.get(0).toString());
                Log.i(TAG, mMountList.get(0).mDiskLabel);
                Log.i(TAG, mMountList.get(0).mMountPoint);

            }
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    private boolean CheckUpdateFile(String path) {
        File file = new File(path + "/update.zip");

        try {
            if (file.exists()) {
                return true;
            }
        } catch (Exception e) {
            return false;
        }
        return false;

    }

    public void ShowToast(int stringid) {
        Toast toast = Toast.makeText(mContext, mContext.getResources()
                .getString(stringid), Toast.LENGTH_SHORT);
        toast.show();

    }
}