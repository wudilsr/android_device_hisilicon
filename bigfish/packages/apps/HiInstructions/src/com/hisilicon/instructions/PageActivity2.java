package com.hisilicon.instructions;

import android.content.Intent;
import android.os.Bundle;

public class PageActivity2 extends PageActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public int getLayoutId() {
        return R.layout.page_activity_2;
    }

    @Override
    public int getPosition() {
        return 1;
    }

    @Override
    public void startPrvActivity() {
        Intent intent = new Intent(PageActivity2.this, PageActivity1.class);
        startActivity(intent);
        finish();
    }

    @Override
    public void startNextActivity() {
        Intent intent = new Intent(PageActivity2.this, PageActivity3.class);
        startActivity(intent);
        finish();
    }
}