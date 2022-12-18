package com.hisilicon.instructions;

import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class PageActivity5 extends PageActivity implements OnClickListener {
    private final String NETWORK_PACKAGE = "com.android.hisiliconsetting";
    private final String NETWORK_ACTIVITY = "com.android.hisiliconsetting.display.DisplaySetActivity";
    private Button btn_display;
    private boolean isSign;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        isSign = ((MyApplication) getApplication()).isSign();
        btn_display = (Button) findViewById(R.id.button_set_display);
        btn_display.setOnClickListener(this);
    }

    @Override
    public int getLayoutId() {
        return R.layout.page_activity_5;
    }

    @Override
    public int getPosition() {
        return 4;
    }

    @Override
    public void startPrvActivity() {
        Intent intent = new Intent(PageActivity5.this, PageActivity4.class);
        startActivity(intent);
        finish();
    }

    @Override
    public void startNextActivity() {
        if (isSign) {
            System.exit(0);
        } else {
            Intent intent = new Intent(PageActivity5.this, PageActivity6.class);
            startActivity(intent);
            finish();
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.button_set_display:
            Intent intent = new Intent();
            ComponentName componentName = new ComponentName(NETWORK_PACKAGE,
                    NETWORK_ACTIVITY);
            intent.setComponent(componentName);
            startActivity(intent);
            break;
        default:
            break;
        }
    }

}