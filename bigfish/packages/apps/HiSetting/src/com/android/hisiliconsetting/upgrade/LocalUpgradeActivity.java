package com.android.hisiliconsetting.upgrade;

import android.app.Activity;
import android.os.Bundle;

import com.android.hisiliconsetting.R;

public class LocalUpgradeActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.local_upgrade_main);
    }
}