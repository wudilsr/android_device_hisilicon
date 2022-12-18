package com.hisilicon.instructions;

import android.content.Intent;
import android.os.Bundle;

public class PageActivity1 extends PageActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public int getLayoutId() {
        return R.layout.page_activity_1;
    }

    @Override
    public int getPosition() {
        return 0;
    }

    @Override
    public void startPrvActivity() {

    }

    @Override
    public void startNextActivity() {
        Intent intent = new Intent(PageActivity1.this, PageActivity2.class);
        startActivity(intent);
        finish();
    }

}