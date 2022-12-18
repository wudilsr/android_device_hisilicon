package com.hisilicon.hardware.util;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Locale;

import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import com.hisilicon.hardware.cvbs.CVBSActivity;
import com.hisilicon.hardware.hdmi.HDMIActivity;
import com.hisilicon.hardwaretest.R;

public class SelectFileAcvitity extends ListActivity {

    private ListView listView;
    private TextView titleView;
    public SimpleAdapter adapter;
    ArrayList<HashMap<String, Object>> listItem;

    private String currPath;
    private String activityName;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
        setContentView(R.layout.select_file_list);
        getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE,
                R.layout.select_file_title);

        Intent intent = getIntent();

        currPath = intent.getStringExtra("path");
        activityName = intent.getStringExtra("activity");

        listView = (ListView) findViewById(android.R.id.list);
        titleView = (TextView) findViewById(R.id.text_title);

        listItem = new ArrayList<HashMap<String, Object>>();
        adapter = new SimpleAdapter(this, listItem,
                R.layout.select_file_list_item, new String[] { "image_view",
                        "text_file_name" }, new int[] { R.id.image_view,
                        R.id.text_file_name });

        this.setListAdapter(adapter);
        updateSubList(currPath);
        listView.setOnItemClickListener(new OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view,
                    int position, long id) {
                if (listItem != null && listItem.get(position) != null
                        && listItem.get(position).get("text_file_path") != null) {
                    String path = listItem.get(position).get("text_file_path")
                            .toString();

                    File f = new File(path);
                    if (f.isFile()) {
                        Intent intent = null;
                        if (activityName.equals("HDMIActivity"))
                            intent = new Intent(SelectFileAcvitity.this,
                                    HDMIActivity.class);
                        else
                            intent = new Intent(SelectFileAcvitity.this,
                                    CVBSActivity.class);
                        intent.putExtra("path", path);
                        setResult(RESULT_OK, intent);
                        finish();
                    } else {
                        updateSubList(path);
                    }
                }
            }
        });
    }

    public void updateSubList(String path) {
        listItem.clear();
        titleView.setText(path);

        File f = new File(path);
        HashMap<String, Object> temp_map = new HashMap<String, Object>();
        temp_map.put("image_view", R.drawable.folder_file);
        temp_map.put("text_file_name", "..");
        if (path.equals("/mnt"))
            temp_map.put("text_file_path", "/mnt");
        else
            temp_map.put("text_file_path", f.getParentFile());
        listItem.add(temp_map);

        File[] files = f.listFiles();
        if (files == null)
            return;

        for (int i = 0; i < files.length; i++) {
            if (files[i].isFile()) {
                HashMap<String, Object> map = new HashMap<String, Object>();
                map.put("image_view", R.drawable.text_file);
                map.put("text_file_name", files[i].getName());
                map.put("text_file_path", files[i].getPath());
                if (files[i].canRead())
                    listItem.add(map);
            } else if (files[i].isDirectory()) {
                HashMap<String, Object> map = new HashMap<String, Object>();
                map.put("image_view", R.drawable.folder_file);
                map.put("text_file_name", files[i].getName());
                map.put("text_file_path", files[i].getPath());
                if (files[i].canRead())
                    listItem.add(map);
            }
        }
        Collections.sort(listItem, new MyComparator());
        ((SimpleAdapter) getListView().getAdapter()).notifyDataSetChanged();
        listView.setSelection(0);
        listView.requestFocus();
    }

    private class MyComparator implements Comparator<HashMap<String, Object>> {

        @Override
        public int compare(HashMap<String, Object> o1,
                HashMap<String, Object> o2) {
            int id1 = (Integer) o1.get("image_view");
            int id2 = (Integer) o2.get("image_view");
            String name1 = ((String) o1.get("text_file_name"))
                    .toUpperCase(Locale.getDefault());
            String name2 = ((String) o2.get("text_file_name"))
                    .toUpperCase(Locale.getDefault());
            if (id1 == id2) {
                return name1.compareTo(name2);
            } else {
                if (id1 == R.drawable.folder_file)
                    return -1;
                else
                    return 1;
            }
        }
    }
}