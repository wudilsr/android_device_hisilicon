package com.hisilicon.android.music;

import java.util.ArrayList;
import java.util.HashMap;

import com.hisilicon.android.music.MediaPlaybackActivity.MyServiceConnection;

import android.app.ListActivity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AbsListView;
import android.widget.AbsListView.OnScrollListener;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.AdapterView.OnItemClickListener;

public class FileListAcvitity extends ListActivity {

    private MediaFileList mediaFileList;
    private ListView mPlayListView;
    public ArrayList<MusicModel> currList;
    public SimpleAdapter listItemAdapter;
    ArrayList<HashMap<String, Object>> listItem;
    public static MediaFileListService mediaFileListService = null;
    public MyServiceConnection conn = null;
    private String currPlayPath;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // TODO Auto-generated method stub
        super.onCreate(savedInstanceState);
        setContentView(R.layout.media_picker_activity);

        Intent intent = getIntent();
        mediaFileList = intent.getParcelableExtra("MediaFileList");
        currPlayPath = intent.getStringExtra("path");
        if (mediaFileList != null && mediaFileList.getId() == 1) {
            Intent service = new Intent(Constants.ACTION);
            conn = new MyServiceConnection();
            FileListAcvitity.this.bindService(service, conn,
                    Context.BIND_AUTO_CREATE);
        }

        mPlayListView = getListView();
        mPlayListView.setSelector(R.drawable.list_selector_background);
        listItem = new ArrayList<HashMap<String, Object>>();
        listItemAdapter = new SimpleAdapter(this, listItem,
                R.layout.list_items, new String[] { "ItemImage", "ItemTitle",
                        "ItemText" }, new int[] { R.id.ItemImage,
                        R.id.ItemTitle, R.id.ItemText });
        mPlayListView.setOnItemClickListener(new OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view,
                    int position, long id) {
                // TODO Auto-generated method stubif(mService == null)
                String filename = currList.get(position).getPath();
                try {
                    Intent intent = new Intent();
                    Uri path = Uri.parse(filename);
                    intent.setData(path);
                    intent.setClassName("com.hisilicon.android.music",
                            "com.hisilicon.android.music.MediaPlaybackActivity");
                    intent.setDataAndType(intent.getData(), "audio/*");
                    intent.putExtra("path", filename);
                    startActivity(intent);
                } catch (Exception ex) {
                    Log.d("MediaPlaybackActivity", "couldn't start: " + ex);
                }
                finish();
            }
        });
        mPlayListView.setAdapter(listItemAdapter);

        mPlayListView.setOnScrollListener(new OnScrollListener() {
            @Override
            public void onScrollStateChanged(AbsListView view, int scrollState) {
                // TODO Auto-generated method stub
                mediaFileListService.getList();
                if (null != mediaFileListService
                        && null != mediaFileListService.getList()) {
                    if (mediaFileListService.getList().size() > currList.size()) {
                        updtaePlayList();
                    }
                }
            }

            @Override
            public void onScroll(AbsListView view, int firstVisibleItem,
                    int visibleItemCount, int totalItemCount) {
                // TODO Auto-generated method stub

            }
        });
    }

    public void updtaePlayList(String path) {
        for (int i = 0; i < currList.size(); i++) {
            HashMap<String, Object> map = new HashMap<String, Object>();
            if (path != null && path.equals(currList.get(i).getPath())) {
                map.put("ItemImage", R.drawable.indicator_ic_mp_playing_large);
                getListView().setSelection(i);
                Message msg = new Message();
                msg.what = 1;
                msg.arg1 = i;
                mHandler.sendMessage(msg);
            } else {
                map.put("ItemImage", R.drawable.ic_tab_albums_unselected);
            }
            map.put("ItemTitle", currList.get(i).getTitle());
            map.put("ItemText", currList.get(i).getPath());
            listItem.add(map);
        }
        ((SimpleAdapter) getListView().getAdapter()).notifyDataSetChanged();
    }

    public void updtaePlayList() {
        for (int i = 0; i < mediaFileListService.getList().size(); i++) {
            HashMap<String, Object> map = new HashMap<String, Object>();
            map.put("ItemTitle", currList.get(i).getTitle());
            map.put("ItemText", currList.get(i).getPath());
            listItem.add(map);
        }
        ((SimpleAdapter) getListView().getAdapter()).notifyDataSetChanged();
    }

    public class MyServiceConnection implements ServiceConnection {
        public void onServiceConnected(ComponentName arg0, IBinder service) {
            mediaFileListService = ((MediaFileListService.MyBinder) service)
                    .getService();
            currList = mediaFileListService.getList();
            updtaePlayList(currPlayPath);
        }

        public void onServiceDisconnected(ComponentName arg0) {

        }
    }

    @Override
    protected void onStart() {
        // TODO Auto-generated method stub
        super.onStart();
    }

    @Override
    protected void onStop() {
        // TODO Auto-generated method stub
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        super.onDestroy();
        if (conn != null) {
            unbindService(conn);
            stopService(new Intent(Constants.ACTION));
        }
    }

    @Override
    protected void onResume() {
        // TODO Auto-generated method stub
        super.onResume();
    }

    @Override
    protected void onPause() {
        // TODO Auto-generated method stub
        super.onPause();
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        // TODO Auto-generated method stub
        return super.dispatchKeyEvent(event);
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        // TODO Auto-generated method stub
        return super.dispatchTouchEvent(ev);
    }

    Handler mHandler = new Handler() {

        public void handleMessage(Message msg) {
            switch (msg.what) {

            case 1:
                int i = msg.arg1;
                getListView().setSelection(i);
                getListView().invalidateViews();
            }
        };
    };
}
