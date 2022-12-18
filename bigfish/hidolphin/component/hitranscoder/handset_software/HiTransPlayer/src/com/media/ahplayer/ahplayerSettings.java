/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.ahplayer;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

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
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ImageButton;

public class ahplayerSettings extends Activity {
    private static final String     TAG = "ahplayerSettings";
    private CheckBox            cbHWDecoder;
    private CheckBox            cbOpenAHSMonitor;
    private EditText            etFPS;
    private EditText            etWebServerIP;
    private EditText            etPlayingSpeed;
    private Button            mOK;
    private int mHWDecoding = 0;
    private String mVideoFPS = null;
    private String mEPGURL = null;
    private String mPlayingSpeed = null;
    private ahplayerConfig config = null;
    private int mAHSMonitor = 1;
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.ahplayer_settings);
        config = new ahplayerConfig(this);
        cbHWDecoder = (CheckBox)findViewById(R.id.HWDecoder);
        cbOpenAHSMonitor = (CheckBox)findViewById(R.id.CBOpenMonitor);
        mOK = (Button)findViewById(R.id.OK);
        etFPS = (EditText)findViewById(R.id.EditTextVideoFPS);
        etWebServerIP = (EditText)findViewById(R.id.EditTextWebServerIP);
        etPlayingSpeed = (EditText)findViewById(R.id.PlayingSpeedET);
        mHWDecoding =Integer.valueOf(config.getValueByOptionName(config.ahplayerConfigPath,config.HWDECODING,"0"));
        mAHSMonitor = Integer.valueOf(config.getValueByOptionName(config.ahplayerConfigPath,config.AHSMONITOR,"0"));
        if(mHWDecoding == 1)
        {
            cbHWDecoder.setChecked(true);
        }
        else
        {
            cbHWDecoder.setChecked(false);
        }
        if(mAHSMonitor == 1)
        {
            cbOpenAHSMonitor.setChecked(true);
        }
        else
        {
            cbOpenAHSMonitor.setChecked(false);
        }
        etFPS.setText(config.getValueByOptionName(config.ahplayerConfigPath,config.VIDEOFPS,"0"));
        etWebServerIP.setText(config.getValueByOptionName(config.ahplayerConfigPath,config.EPGURL,"http://192.168.1.18/epg.html"));
        etPlayingSpeed.setText(config.getValueByOptionName(config.ahplayerConfigPath,config.PLAYINGSPEED,"100"));
        mOK.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v)
            {
                if(cbHWDecoder.isChecked())
                {
                    mHWDecoding = 1;
                }
                else
                {
                    mHWDecoding = 0;
                }
                if(cbOpenAHSMonitor.isChecked())
                {
                    mAHSMonitor = 1;
                }
                else
                {
                    mAHSMonitor = 0;
                }
                mVideoFPS = etFPS.getText().toString();
                mEPGURL = etWebServerIP.getText().toString();
                mPlayingSpeed = etPlayingSpeed.getText().toString();
                Integer speed = Integer.valueOf(mPlayingSpeed);
                if(speed >200)
                {
                    speed =200;
                }
                else if(speed < 50)
                {
                    speed = 50;
                }
                mPlayingSpeed = speed.toString();
                config.config(config.ahplayerConfigPath,config.HWDECODING,Integer.toString(mHWDecoding));
                config.config(config.ahplayerConfigPath,config.VIDEOFPS,mVideoFPS);
                config.config(config.ahplayerConfigPath,config.EPGURL,mEPGURL);
                config.config(config.ahplayerConfigPath,config.PLAYINGSPEED,mPlayingSpeed);
                config.config(config.ahplayerConfigPath,config.AHSMONITOR,Integer.toString(mAHSMonitor));
                finish();
            }
        });
    }
}
