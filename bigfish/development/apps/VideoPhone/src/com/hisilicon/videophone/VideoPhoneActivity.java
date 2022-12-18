package com.hisilicon.videophone;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.animation.AlphaAnimation;
import android.view.animation.AnimationSet;
import android.view.animation.TranslateAnimation;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.ctcims.avcodec.PhonePlayer;

public class VideoPhoneActivity extends Activity implements OnClickListener {

    private final String TAG = "MainActivity";

    private Button btnExit;
    private ImageView imageArrow;
    private TextView textLocalIp;
    private TextView textRemoteIp;

    private String remoteIP;
    private String localIP;
    private int resolution;
    private int videoPort;
    private int audioPort;

    private int winWidth;
    private int winHeight;
    private int localWidth;
    private int localHeight;
    private int localX;
    private int localY;
    private int ret = 0;

    private PhonePlayer phonePlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (!hasExtra())
            finish();

        setContentView(R.layout.video_phone_view);
        phonePlayer = new PhonePlayer();
        initView();
        initDisplay();
        initPhoneVideo();
    }

    @Override
    protected void onPause() {
        phonePlayer.videoStop();
        phonePlayer.audioStop();
        phonePlayer.deInitVideo();
        phonePlayer.deInitAudio();
        phonePlayer.AVDeinit();
        super.onPause();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        return true;
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.btn_exit:
            finish();
            break;

        default:
            break;
        }
    }

    private boolean hasExtra() {
        Intent intent = getIntent();
        resolution = intent.getIntExtra("resolution", -1);
        videoPort = intent.getIntExtra("videoPort", -1);
        audioPort = intent.getIntExtra("audioPort", -1);
        remoteIP = intent.getStringExtra("remoteIP");
        localIP = intent.getStringExtra("localIP");
        Log.i(TAG, "********** resolution = " + resolution);
        Log.i(TAG, "********** videoPort = " + videoPort);
        Log.i(TAG, "********** audioPort = " + audioPort);
        Log.i(TAG, "********** remoteIP = " + remoteIP);
        Log.i(TAG, "********** localIP = " + localIP);
        if (resolution == -1 || videoPort == -1 || audioPort == -1
                || isEmpty(remoteIP) || isEmpty(localIP))
            return false;
        return true;
    }

    private void initView() {
        btnExit = (Button) findViewById(R.id.btn_exit);
        btnExit.setOnClickListener(this);

        textLocalIp = (TextView) findViewById(R.id.text_local_ip);
        textRemoteIp = (TextView) findViewById(R.id.text_remote_ip);
        textLocalIp.setText(localIP);
        textRemoteIp.setText(remoteIP);

        imageArrow = (ImageView) findViewById(R.id.image_arrow);

        AlphaAnimation alpha = new AlphaAnimation(0.3f, 1f);
        alpha.setRepeatCount(Integer.MAX_VALUE);

        TranslateAnimation tran = new TranslateAnimation(-30f, 30f, 0f, 0f);
        tran.setRepeatCount(Integer.MAX_VALUE);

        AnimationSet set = new AnimationSet(true);
        set.addAnimation(alpha);
        set.addAnimation(tran);
        set.setDuration(1500);
        set.setStartTime(0);
        imageArrow.startAnimation(set);
    }

    private void initDisplay() {
        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
        winHeight = metrics.heightPixels;
        winWidth = metrics.widthPixels;
        localWidth = winWidth;
        localHeight = winHeight;
        while (localWidth > 280) {
            localWidth = (int) (localWidth * 0.98);

        }
        while (localHeight > 250) {
            localHeight = (int) (localHeight * 0.98);
        }
        localX = winWidth - localWidth - 50;
        localY = winHeight - localHeight - 50;
    }

    private void initPhoneVideo() {
        phonePlayer.AVInit();
        phonePlayer.initVideo(resolution, localX, localY, localWidth, localHeight, 0, 0, 1280, 720, 0, 30);
        phonePlayer.showWindow(2, 2);
        phonePlayer.videoStart(localIP + "\n", videoPort, remoteIP + "\n", videoPort, 30, 118, 5000000, 60);
        phonePlayer.initAudio();
        phonePlayer.audioStart(localIP + "\n", audioPort, remoteIP + "\n", audioPort);
    }

    private boolean isEmpty(String str) {
        return null == str || "".equals(str);
    }

}