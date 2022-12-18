/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.ahplayer;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.util.Arrays;
import java.util.Comparator;

//import com.media.libhaveplayer.FFMpeg;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.app.ListActivity;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.View.OnClickListener;
import android.view.inputmethod.EditorInfo;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView.AdapterContextMenuInfo;
import android.widget.TextView.OnEditorActionListener;
import android.widget.SimpleCursorAdapter;
import android.widget.Toast;

public class ahplayerExplorer extends Activity{

    //private static final String TAG = "ahplayerExplorer";

    private    EditText        mMovieURL;
    private Button            mStartPlay;
    private Context           mCtx;

    private final String PREFERNAME = "HisiUrl";
    private final String URLNAME = "MovUrl";
    private static final String[] exts = new String[] {
        ".mp4",
        ".flv",
        ".avi",
        ".3gp",
        ".ts",
        ".wmv",
        ".mp3",
        ".264",
        ".hevc"
    };
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mCtx = this;
        setContentView(R.layout.ahplayer_explorer);
        mMovieURL = (EditText)findViewById(R.id.input_url);
        mMovieURL.setText(getLastTimeUrl());
        mMovieURL.setOnEditorActionListener(new OnEditorActionListener() {

            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                // TODO Auto-generated method stub
                if(actionId == EditorInfo.IME_ACTION_DONE)
                {
                    storeUrl(v.getText().toString());
                }
                return false;
            }
        });
        mStartPlay = (Button)findViewById(R.id.start_play);
        mStartPlay.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                // TODO Auto-generated method stub
                String inputUrl = mMovieURL.getText().toString();
                Log.e("ahplayer", "input url:"+inputUrl);
                if(inputUrl.length() == 0)
                {
                    /*do nothing*/
                    String msgStr = getString(R.string.url_input);
                    ahplayerMessageBox.show(mCtx, "Tips", msgStr);
                }
                else
                {
                    if(!isLaunched)
                    {
                        Log.e("ahplayer", "start player !!!!!");
                        isLaunched = true;
                        storeUrl(inputUrl);
                        startPlayer(inputUrl);
                    }
                }
            }
        });
    }
    private boolean isLaunched = false;

    @Override
    protected void onResume() {
        // TODO Auto-generated method stub
        isLaunched = false;
        super.onResume();
    }

    private void storeUrl(String url)
    {
        SharedPreferences iprefdata = getSharedPreferences(PREFERNAME, MODE_PRIVATE);
        Editor iEdit = iprefdata.edit();
        iEdit.putString(URLNAME, url);
        iEdit.commit();

    }
    private String getLastTimeUrl()
    {
        String iUrl;
        Editor iEdit;
        SharedPreferences iprefdata;

        iprefdata = getSharedPreferences(PREFERNAME, MODE_PRIVATE);
        iEdit = iprefdata.edit();
        iUrl = iprefdata.getString(URLNAME, "noexist");
        if(iUrl.equalsIgnoreCase("noexist"))
        {
            iUrl = "rtsp://10.161.179.233:4098/hisi";
            iEdit.putString(URLNAME, iUrl);
            iEdit.commit();
        }
        return iUrl;
    }
    void Copy(String oldPath,     String newPath)
    {
        try
        {
            int     bytesum     =     0;
            int     byteread     =     0;
            File     oldfile     =     new     File(oldPath);
            if(oldfile.exists())
            {
                InputStream     inStream     =     new     FileInputStream(oldfile);
                FileOutputStream     fs     =     new     FileOutputStream(newPath);
                byte[]     buffer     =     new     byte[1444];
                while     (     (byteread     =     inStream.read(buffer))     !=     -1)
                {
                    bytesum     +=     byteread;
                    fs.write(buffer,     0,     byteread);
                }
                inStream.close();
            }
        }
        catch     (Exception     e)
        {
            ahplayerMessageBox.show(this, "Error", e.getMessage());
        }
    }
    protected static boolean checkExtension(File file) {
        for(int i=0;i<exts.length;i++) {
            if(file.getName().indexOf(exts[i]) > 0) {
                return true;
            }
        }
        return true;
    }

    private void sortFilesByDirectory(File[] files) {
        Arrays.sort(files, new Comparator<File>() {

            public int compare(File f1, File f2) {
                return Long.valueOf(f1.length()).compareTo(f2.length());
            }

        });
    }

    private void startPlayer(String filePath) {
        Intent i = new Intent(this, ahplayerActivity.class);
        i.putExtra(getResources().getString(R.string.input_file), filePath);
        startActivity(i);
        Log.e("Explorer:", "startPlayer End");
    }
}
