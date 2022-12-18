package com.hisilicon.baidu.pcs.common;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.baidu.pcs.BaiduPCSActionInfo.PCSCommonFileInfo;
import com.hisilicon.baidu.pcs.R;

public class FileAdapter extends BaseAdapter {

    private Context context;
    private List<PCSCommonFileInfo> list;
    private List<Boolean> selectInfo;
    private int layout;

    private Bitmap apkFile;
    private Bitmap audioFile;
    private Bitmap vedioFile;
    private Bitmap imageFile;
    private Bitmap folderFile;
    private Bitmap otherFile;
    private Bitmap checkOn;
    private Bitmap checkOff;

    public FileAdapter(Context context, List<PCSCommonFileInfo> list, int layout) {

        this.context = context;
        this.layout = layout;
        if (null == list)
            this.list = new ArrayList<PCSCommonFileInfo>();
        else
            this.list = list;

        apkFile = getbitmap(R.drawable.icon_apk_file);
        audioFile = getbitmap(R.drawable.icon_audio_file);
        vedioFile = getbitmap(R.drawable.icon_vedio_file);
        imageFile = getbitmap(R.drawable.icon_image_file);
        folderFile = getbitmap(R.drawable.icon_folder_file);
        otherFile = getbitmap(R.drawable.icon_other_file);
        checkOn = getbitmap(R.drawable.icon_check_on);
        checkOff = getbitmap(R.drawable.icon_check_off);
    }

    private Bitmap getbitmap(int id) {
        return BitmapFactory.decodeResource(context.getResources(), id);
    }

    public void refreshList(List<PCSCommonFileInfo> list,
            List<Boolean> selectInfo) {
        if (null != list) {
            this.list = list;
            this.selectInfo = selectInfo;
            notifyDataSetChanged();
        }
    };

    @Override
    public int getCount() {
        return list.size();
    }

    @Override
    public Object getItem(int position) {
        return list.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View v, ViewGroup group) {
        ViewHolder holder;
        PCSCommonFileInfo fileInfo = list.get(position);
        if (v == null) {
            holder = new ViewHolder();
            v = LayoutInflater.from(context).inflate(layout, null);
            holder.text = (TextView) v.findViewById(R.id.text);
            holder.icon = (ImageView) v.findViewById(R.id.image_Icon);
            holder.selectIcon = (ImageView) v.findViewById(R.id.select_image);
            v.setTag(holder);
        } else {
            holder = (ViewHolder) v.getTag();
        }

        String fileName = fileInfo.path.substring(fileInfo.path
                .lastIndexOf("/") + 1);
        String type = FileUtil.getFileType(fileName);

        if (fileInfo.isDir) {
            holder.icon.setImageBitmap(folderFile);
        } else if ("audio/*".equals(type)) {
            holder.icon.setImageBitmap(audioFile);
        } else if ("video/*".equals(type) || "video/iso".equals(type)) {
            holder.icon.setImageBitmap(vedioFile);
        } else if ("apk/*".equals(type)) {
            holder.icon.setImageBitmap(apkFile);
        } else if ("image/*".equals(type)) {
            holder.icon.setImageBitmap(imageFile);
        } else {
            holder.icon.setImageBitmap(otherFile);
        }

        if (null == selectInfo || selectInfo.size() == 0) {
            holder.selectIcon.setVisibility(View.GONE);
        } else {
            holder.selectIcon.setVisibility(View.VISIBLE);
            if (selectInfo.get(position))
                holder.selectIcon.setImageBitmap(checkOn);
            else
                holder.selectIcon.setImageBitmap(checkOff);
        }

        holder.text.setText(fileName);
        return v;
    }

    public class ViewHolder {
        public TextView text;
        public ImageView icon;
        public ImageView selectIcon;

        public void setSelect(boolean isSelect) {
            if (isSelect)
                selectIcon.setImageBitmap(checkOn);
            else
                selectIcon.setImageBitmap(checkOff);
        }
    }

}