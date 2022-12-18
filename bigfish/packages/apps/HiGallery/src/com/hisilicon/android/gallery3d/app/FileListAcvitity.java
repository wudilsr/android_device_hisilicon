package com.hisilicon.android.gallery3d.app;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.io.File;

import com.hisilicon.android.gallery3d.R;

import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.Display;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.widget.AdapterView;
import android.widget.TextView;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.AdapterView.OnItemClickListener;
public class FileListAcvitity extends ListActivity {
    private ListView mPlayListView;
    private TextView mTitleView;
    public SimpleAdapter listItemAdapter;
    ArrayList<HashMap<String, Object>> listItem;
    private String currPlayPath;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
        setContentView(R.layout.sub_list);
        getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.title);

        WindowManager m = getWindowManager();
        Display d = m.getDefaultDisplay();
        LayoutParams p = getWindow().getAttributes();
        p.height = (int) (d.getHeight() * 0.8);
        p.width = (int) (d.getWidth() * 0.7);
        getWindow().setAttributes(p);
        Intent intent = getIntent();
        currPlayPath = intent.getStringExtra("path");
        mPlayListView = (ListView)findViewById(android.R.id.list);
        mTitleView = (TextView)findViewById(R.id.left_text);

        listItem = new ArrayList<HashMap<String, Object>>();
        listItemAdapter = new SimpleAdapter(this, listItem,
                R.layout.list_items, new String[] { "ItemImage", "ItemTitle",
                        "ItemText" }, new int[] { R.id.ItemImage,
                        R.id.ItemTitle, R.id.ItemText });
        this.setListAdapter(listItemAdapter);
        mPlayListView.setOnItemClickListener(new OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view,
                    int position, long id)
                {
                    if(listItem != null && listItem.get(position) != null && listItem.get(position).get("ItemText") != null)
                    {
                        String path = listItem.get(position).get("ItemText").toString();

                        File f = new File(path);
                        if(f.isFile())
                        {
        if(isMusicFile(f.getPath())){
        Intent data=new Intent();
                                data.putExtra("subPath", path);
                                setResult(0, data);
                                finish();
        }
                        }
                        else if(f.isDirectory())
                        {
                            updateSubList(path);
                        }
                    }
                }
        });
        mhandler.sendEmptyMessage(100);
    }
    private Handler mhandler = new Handler(){
        public void handleMessage(Message msg) {
        if(msg.what==100){
         updateSubList(currPlayPath);
        }
        }
    };
    public void updateSubList(String path) {
        listItem.clear();
        mTitleView.setText(path);
        File f = new File(path);
        HashMap<String, Object> temp_map = new HashMap<String, Object>();
        temp_map.put("ItemImage",R.drawable.folder_file);
        temp_map.put("ItemTitle", "..");
        if(path.equals("/mnt"))
            temp_map.put("ItemText", "/mnt");
        else
            temp_map.put("ItemText", f.getParentFile());
        listItem.add(temp_map);

        File[] files = f.listFiles();
        if(files == null)
            return;

        for (int i = 0; i < files.length; i++)
        {
            if(files[i].isFile())
            {
                HashMap<String, Object> map = new HashMap<String, Object>();
                map.put("ItemImage",R.drawable.textfile);
                map.put("ItemTitle", files[i].getName());
                map.put("ItemText", files[i].getPath());
                if(files[i].canRead())
                    listItem.add(map);
            }
            else if(files[i].isDirectory())
            {
                HashMap<String, Object> map = new HashMap<String, Object>();
                map.put("ItemImage",R.drawable.folder_file);
                map.put("ItemTitle", files[i].getName());
                map.put("ItemText", files[i].getPath());
                if(files[i].canRead())
                    listItem.add(map);
            }
        }
        ((SimpleAdapter) getListView().getAdapter()).notifyDataSetChanged();
        mPlayListView.setSelection(0);
        mPlayListView.requestFocus();
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onStop() {
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        return super.dispatchKeyEvent(event);
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        return super.dispatchTouchEvent(ev);
    }
    private boolean isMusicFile(String path){
        Boolean ret = false;
        String filename = path;
        String dex = filename.substring(
                filename.lastIndexOf(".") + 1,
                filename.length());
        dex = dex.toUpperCase();
        SharedPreferences musicShare = getSharedPreferences(
                "AUDIO", Context.MODE_WORLD_READABLE);
        String musicSuffix = musicShare.getString(dex, "");
        if(!musicSuffix.equals("")){
        ret = true;
        }
        return ret;
    }
}
