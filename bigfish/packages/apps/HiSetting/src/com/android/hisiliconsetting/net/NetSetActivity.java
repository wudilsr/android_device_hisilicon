package com.android.hisiliconsetting.net;

import com.android.hisiliconsetting.R;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.RelativeLayout;

public class NetSetActivity extends Activity{
    private String TAG = "NetSetActivity";
    private RelativeLayout mEtherLayout = null;
    private RelativeLayout mWifiLayout = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(TAG, "onCreate");
        setContentView(R.layout.net_set_main);
        mEtherLayout = (RelativeLayout)findViewById(R.id.net_set_main_ethenet);
        mWifiLayout = (RelativeLayout)findViewById(R.id.net_set_main_wifi);
        mEtherLayout.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick(View v) {
        Log.d(TAG, "onClick");
        Intent intent = new Intent();
        intent.setClass(NetSetActivity.this, EthernetActivity.class);
        startActivity(intent);
        }
        });
        mWifiLayout.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick(View v) {
        Log.d(TAG, "onClick");
        Intent intent = new Intent();
        intent.setClass(NetSetActivity.this, WifiActivity.class);
        startActivity(intent);
        }
        });
    }

}
