package com.google.android.exoplayer.demo;

import java.io.File;
import java.io.FilenameFilter;
import java.util.Arrays;
import java.util.Comparator;

import com.google.android.exoplayer.util.Util;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Environment;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.AdapterView.OnItemClickListener;

public class LocalFileAdapter extends BaseAdapter implements OnItemClickListener {
    private static final String TAG = "LocalFileAdapter";

    private Context mContext;
    private File mCurrentDirectory;
    private File[] mFileList = null;

    public LocalFileAdapter(Context context) {
        this.mContext = context;

        File SDCardDirectory = Environment.getExternalStorageDirectory();
        updateListAdapter(SDCardDirectory);
    }

    @Override
    public int getCount() {
        if (mFileList != null) {
            return mFileList.length;
        }
        return 0;
    }

    @Override
    public Object getItem(int position) {
        if (mFileList != null && position < mFileList.length) {
            return mFileList[position];
        }
        return null;
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        //Log.d(TAG, "position = " + position);
        if (mFileList == null || position >= mFileList.length) {
            return null;
        }

        View itemView = convertView;
        if (itemView == null) {
            itemView = LayoutInflater.from(mContext).inflate(android.R.layout.simple_list_item_1, null, false);
        }

        File item = mFileList[position];
        ((TextView) itemView).setText(item.getName());

        return itemView;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position,
    long id) {
        if (mFileList == null || position >= mFileList.length) {
            return;
        }

        File file = mFileList[position];
        if (file.isDirectory()) {
            updateListAdapter(file);
        } else if (isSupportedVideoFiles(file.getName())
        || isSupportedAudioFiles(file.getName())) {
            Intent intent = new Intent(mContext, PlayerActivity.class)
                .setData(Uri.parse(file.getAbsolutePath()))
                .putExtra(PlayerActivity.CONTENT_TYPE_EXTRA, Util.TYPE_OTHER);
            mContext.startActivity(intent);
        } else if (file.getName().toLowerCase().endsWith(".yuv")) {
            Intent intent = new Intent(mContext, EncodeActivity.class)
                .setData(Uri.parse(file.getAbsolutePath()));
            EncodeActivity.filePath = file.getAbsolutePath();
            EncodeActivity.fileNameYUV = file.getName();

            mContext.startActivity(intent);
        }
    }

public void updateListAdapter(final File directory) {
    //Runnable runnable = new Runnable() {
    //  public void run() {
            if (!directory.isDirectory()) {
                return;
            }

            mCurrentDirectory = directory;

            mFileList = null;
            if (directory.canRead()) {
                mFileList = directory.listFiles(new FileShowFilter());
                Arrays.sort(mFileList, new ComparatorByName());
            }

            notifyDataSetChanged();

            Activity activity = (Activity)mContext;
            TextView currentPath = (TextView) activity.findViewById(R.id.currentpath);
            currentPath.setText(directory.getPath());
            currentPath.setAllCaps(false);
            currentPath.setVisibility(View.VISIBLE);

            ListView sampleList = (ListView) activity.findViewById(R.id.sample_list);
            sampleList.setSelection(0);
    //  }
    //};
    //new Thread(runnable).start();
}

    class FileShowFilter implements FilenameFilter {
        @Override
        public boolean accept(File file, String filename) {
        String path = file.getAbsolutePath();
        EncodeActivity.dirPath = path;
        File subFile = new File(path + "/" + filename);

        if (subFile.isHidden()) return false;
        if (subFile.isDirectory()) return true;
        if (subFile.isFile()) return true;
        return false;
        }
    }

    class ComparatorByName implements Comparator<File> {
        @Override
        public int compare(File file1, File file2) {
        if (file1.isDirectory() && file2.isFile()) {
            return -1;
        }
        if (file1.isFile() && file2.isDirectory()) {
            return 1;
        }
        long diff = file1.getName().compareToIgnoreCase(file2.getName());
        if (diff > 0) {
            return 1;
        } else if (diff < 0) {
            return -1;
        }
        return 0;
        }
    }

    private boolean isSupportedVideoFiles(String fileName) {
    if (fileName != null) {
        String str = fileName.toLowerCase();
        if (str.endsWith(".mp4") || str.endsWith(".mkv") ||
            str.endsWith(".3gp") || str.endsWith(".avi") ||
            str.endsWith(".wmv") || str.endsWith(".flv") ||
            str.endsWith(".mpg") || str.endsWith(".mpeg") ||
            str.endsWith(".asf") || str.endsWith(".mov") ||
            str.endsWith(".webm") || str.endsWith(".ts") ||
            str.endsWith(".rmvb") || str.endsWith(".rm")) {
            return true;
            }
        }
        return false;
    }

    private boolean isSupportedAudioFiles(String fileName) {
    if (fileName != null) {
        String str = fileName.toLowerCase();
        if (str.endsWith(".mp3") || str.endsWith(".wma") ||
            str.endsWith(".aac") || str.endsWith(".amr")) {
            return true;
            }
        }
        return false;
    }

    public boolean onKeyDown(int keyCode, KeyEvent event) {
    if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {
        if (mCurrentDirectory.getParent() != null) {
            updateListAdapter(mCurrentDirectory.getParentFile());
            return true;
        }
    }

    return false;
    }

}
