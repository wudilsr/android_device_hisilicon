package com.hisilicon.instructions;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

public class MainActivity extends Activity {

    private final int PAGE_NO = 6;
    private MyApplication application;
    private boolean isSign;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        application = (MyApplication) getApplication();
        queryIsSign();
    }

    private void queryIsSign() {
        isSign = true;
        application.setPageNo(PAGE_NO - 1);
        application.setSign(isSign);
        Intent intent = new Intent(MainActivity.this, PageActivity1.class);
        startActivity(intent);
        finish();
    }

}