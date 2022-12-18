package com.hisilicon.hardware.hdmi;

import android.content.Intent;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.MediaController;

import com.hisilicon.hardware.CommonActivity;
import com.hisilicon.hardwaretest.R;
import com.hisilicon.android.hisysmanager.HiSysManager;
public class HDMITestActivity extends CommonActivity implements
        OnCompletionListener {
    private String filePath;
    private int testMode;
    private FullScreenVideoView videoView;
    private MediaController media;
    private MediaPlayer player;
    private HiSysManager mhisys;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Intent intent = getIntent();
        testMode = intent.getIntExtra("testMode", VIDEO_PLAY);
        filePath = intent.getStringExtra("filePath");
        if (isEmptyString(filePath)) {
            finish();
            return;
        }
        mhisys = new HiSysManager();
        mhisys.adjustDevState("/proc/msp/pm_core","volt=1140");
        setContentView(R.layout.hdmi_test_activity);
        initView();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (KeyEvent.KEYCODE_MENU == keyCode) {
            Intent intent = new Intent(HDMITestActivity.this,
                    HDMITestService.class);
            startService(intent);
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    public void onCompletion(MediaPlayer player) {
        videoView.start();
    }

    @Override
    protected void onDestroy() {
        Intent intent = new Intent(HDMITestActivity.this, HDMITestService.class);
        stopService(intent);
        if (null != player) {
            player.release();
        }
        mhisys.adjustDevState("/proc/msp/pm_core","volt=0");
        super.onDestroy();
    }

    private void initView() {
        videoView = (FullScreenVideoView) findViewById(R.id.video_view);

        if (VIDEO_PLAY == testMode) {
            media = new MediaController(this);
            media.setVisibility(View.GONE);

            videoView.setVisibility(View.VISIBLE);
            videoView.setOnCompletionListener(this);
            videoView.setMediaController(media);
            videoView.setVideoPath(filePath);
            videoView.start();
        } else {
            videoView.setVisibility(View.GONE);
            player = new MediaPlayer();
            try {
                player.setDataSource(filePath);
                player.setLooping(true);
                player.prepare();
                player.start();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

}
