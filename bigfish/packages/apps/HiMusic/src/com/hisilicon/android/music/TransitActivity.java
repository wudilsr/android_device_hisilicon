package com.hisilicon.android.music;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class TransitActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // TODO Auto-generated method stub
        super.onCreate(savedInstanceState);
        Intent intent = new Intent();
        intent.setClassName("com.hisilicon.android.music",
                "com.hisilicon.android.music.MediaFileListService");
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.setDataAndType(getIntent().getData(), getIntent().getType());
        intent.putExtra("sortCount", getIntent().getIntExtra("sortCount", -1));
        startService(intent);
        TransitActivity.this.finish();
    }
}
