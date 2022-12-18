package com.hisilicon.instructions;

import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class PageActivity4 extends PageActivity implements OnClickListener {
    private final String NETWORK_PACKAGE = "com.android.hisiliconsetting";
    private final String NETWORK_ACTIVITY = "com.android.hisiliconsetting.net.NetSetActivity";
    private Button btn_network;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        btn_network = (Button) findViewById(R.id.button_set_network);
        btn_network.setOnClickListener(this);
    }

    @Override
    public int getLayoutId() {
        return R.layout.page_activity_4;
    }

    @Override
    public int getPosition() {
        return 3;
    }

    @Override
    public void startPrvActivity() {
        Intent intent = new Intent(PageActivity4.this, PageActivity3.class);
        startActivity(intent);
        finish();
    }

    @Override
    public void startNextActivity() {
        Intent intent = new Intent(PageActivity4.this, PageActivity5.class);
        startActivity(intent);
        finish();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.button_set_network:
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