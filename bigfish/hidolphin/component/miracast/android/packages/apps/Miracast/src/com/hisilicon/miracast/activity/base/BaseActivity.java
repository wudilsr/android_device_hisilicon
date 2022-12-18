package com.hisilicon.miracast.activity.base;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

public class BaseActivity extends Activity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
    }

    protected void initView()
    {

    }

    protected void initVariable()
    {

    }

    protected void stopBackgroundMusic()
    {
        Intent intent = new Intent("com.android.music.musicservicecommand");
        intent.putExtra("command", "stop");
        sendBroadcast(intent);

        intent = new Intent("com.android.music.musicservicecommand");
        intent.putExtra("command", "stop");
        sendBroadcast(intent);

        intent = new Intent("com.hisilicon.android.music.musicservicecommand");
        intent.putExtra("command", "stop");
        sendBroadcast(intent);
    }
}
