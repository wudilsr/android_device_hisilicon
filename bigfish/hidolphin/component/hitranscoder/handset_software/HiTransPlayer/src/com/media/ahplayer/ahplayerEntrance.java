/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.ahplayer;

import java.io.IOException;

import com.media.libahplayer.libahplayerException;
import com.media.ahplayer.ahplayerMovieView;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.widget.ImageButton;

public class ahplayerEntrance extends Activity {
    private static final String     TAG = "ahplayerEntrance";
    private ImageButton            mInternetContent;
    private ImageButton            mLocalContent;
    private ImageButton            mSetting;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.ahplayer_entrance);
        mInternetContent = (ImageButton)findViewById(R.id.ibInternetContent);
        mLocalContent = (ImageButton)findViewById(R.id.ibLocalContent);
        mSetting = (ImageButton)findViewById(R.id.ibSetting);
        mInternetContent.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v)
            {
                Intent i = new Intent(ahplayerEntrance.this, ahplayerWebview.class);
                startActivity(i);
            }
        });
        mLocalContent.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v)
            {
                Intent i = new Intent(ahplayerEntrance.this, ahplayerExplorer.class);
                startActivity(i);
            }
        });
        mSetting.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v)
            {
                Intent i = new Intent(ahplayerEntrance.this, ahplayerSettings.class);
                startActivity(i);
            }
        });
    }

    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if(keyCode==KeyEvent.KEYCODE_BACK&&event.getRepeatCount()==0)
        {
            AlertDialog.Builder alertbBuilder=new AlertDialog.Builder(this);
            alertbBuilder.setTitle(getString(R.string.ETA_SAY)).setMessage(R.string.seeYou).setPositiveButton(getString(R.string.YES), new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int which) {
                        int nPid = android.os.Process.myPid();
                        android.os.Process.killProcess(nPid);
                        }
                }).setNegativeButton(getString(R.string.NO), new DialogInterface.OnClickListener() {

                        public void onClick(DialogInterface dialog, int which) {
                                dialog.cancel();
                        }
                }).create();
                alertbBuilder.show();
        }
        return true;
    }
}
